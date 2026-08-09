#include "terrain_proxy.h"

#include "bzr_options_ui.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <bcrypt.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kExpectedExeSha256[] =
            "8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413";
        constexpr char kExpectedOgreSha256[] =
            "E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45";
        constexpr uintptr_t kPreferredImageBase = 0x00400000;
        constexpr uintptr_t kZoneConstructVa = 0x007778B0;
        constexpr uintptr_t kZoneProcessVa = 0x00778450;
        constexpr uintptr_t kTerrainWordAtVa = 0x004C0FE0;
        constexpr uintptr_t kAtlasRectAtVa = 0x0050CE10;
        constexpr uintptr_t kTerrainManagerVa = 0x0077C670;
        constexpr uintptr_t kTileIndexAtVa = 0x00780DC0;
        constexpr uintptr_t kMixAtVa = 0x00780E40;
        constexpr uintptr_t kTerrainOriginXVa = 0x02CE99C0;
        constexpr uintptr_t kTerrainOriginZVa = 0x02CD9984;

        constexpr size_t kZoneMeshPtrBase = 0x000;
        constexpr size_t kZoneNodeBase = 0x080;
        constexpr size_t kZoneEntityBase = 0x0C0;
        constexpr size_t kZoneXOffset = 0x240;
        constexpr size_t kZoneZOffset = 0x244;
        constexpr size_t kHeightDirtyOffset = 0x250;
        constexpr size_t kHeightDirtyNextOffset = 0x260;
        constexpr size_t kFullDirtyOffset = 0x270;
        constexpr size_t kClusterXStride = 0x20;
        constexpr size_t kClusterZStride = 0x08;
        constexpr uint32_t kExpectedVertices = 9409;
        constexpr uint32_t kExpectedIndices = 38400;
        constexpr int kClusterAxisCount = 4;

        struct Vector3
        {
            float x;
            float y;
            float z;
        };

        struct Quaternion
        {
            float w;
            float x;
            float y;
            float z;
        };

        struct AxisAlignedBox
        {
            Vector3 minimum;
            Vector3 maximum;
            int extent;
        };

        struct OgreSharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };

        struct VertexDataPrefix
        {
            void* manager;
            void* declaration;
            void* binding;
            uint8_t deleteDeclarationAndBinding;
            uint8_t padding0D[3];
            uint32_t vertexStart;
            uint32_t vertexCount;
        };

        struct IndexDataPrefix
        {
            OgreSharedPtr indexBuffer;
            uint32_t indexStart;
            uint32_t indexCount;
        };

        struct RenderOperation
        {
            VertexDataPrefix* vertexData;
            int operationType;
            uint8_t useIndexes;
            uint8_t padding09[3];
            IndexDataPrefix* indexData;
            const void* sourceRenderable;
            uint32_t numberOfInstances;
            uint8_t renderToVertexBuffer;
            uint8_t globalInstancingAvailable;
            uint8_t padding1A[2];
        };

        struct AtlasRect
        {
            float u;
            float v;
            float w;
            float h;
        };

        static_assert(sizeof(OgreSharedPtr) == 8, "Redux Ogre SharedPtr ABI changed");
        static_assert(sizeof(VertexDataPrefix) == 24, "Redux Ogre VertexData ABI changed");
        static_assert(sizeof(IndexDataPrefix) == 16, "Redux Ogre IndexData ABI changed");
        static_assert(sizeof(RenderOperation) == 28, "Redux Ogre RenderOperation ABI changed");
        static_assert(sizeof(AxisAlignedBox) == 28, "Redux Ogre AxisAlignedBox ABI changed");

        struct TerrainConfig
        {
            bool proxyEnabled = false;
            bool proxyVisible = true;
            bool semanticCapture = false;
            bool semanticDumpJson = true;
            int zoneOrdinal = -1;
            int clusterOrdinal = -1;
            int zoneX = INT_MIN;
            int zoneZ = INT_MIN;
            int clusterX = INT_MIN;
            int clusterZ = INT_MIN;
            Vector3 offset = {};
        };

        struct ProxyState
        {
            bool selected = false;
            bool proxyCreated = false;
            void* zone = nullptr;
            void* sceneManager = nullptr;
            void* sourceMesh = nullptr;
            void* sourceEntity = nullptr;
            void* sourceNode = nullptr;
            void* proxyMesh = nullptr;
            void* proxyEntity = nullptr;
            void* proxyNode = nullptr;
            int zoneOrdinal = -1;
            int zoneX = 0;
            int zoneZ = 0;
            int clusterOrdinal = -1;
            int clusterX = 0;
            int clusterZ = 0;
            uint32_t semanticHash = 0;
            uint32_t rebuildCount = 0;
            std::string sourceMeshName;
            std::string proxyMeshName;
            std::string proxyEntityName;
            std::string proxyNodeName;
            std::string materialName;
        };

        // Although the decompiler labels this as void, the placement-new
        // caller consumes EAX and stores it in the manager's zone table.
        // Preserve the native constructor's machine-level `this` return.
        using FnZoneConstruct = void* (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t);
        using FnZoneProcess = void(__thiscall*)(void*);
        using FnMeshClone = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&);
        using FnCreateEntityFromMesh = void* (__thiscall*)(
            void*, const std::string&, const OgreSharedPtr&);
        using FnGetResourceName = const std::string* (__thiscall*)(void*);
        using FnGetNumSubMeshes = uint16_t(__thiscall*)(void*);
        using FnGetSubEntity = void* (__thiscall*)(void*, uint32_t);
        using FnGetRenderOperation = void(__thiscall*)(void*, RenderOperation&);
        using FnGetMaterialName = const std::string* (__thiscall*)(void*);
        using FnSetMaterialName = void(__thiscall*)(void*, const std::string&, const std::string&);
        using FnGetBuffer = const OgreSharedPtr* (__thiscall*)(void*, uint16_t);
        using FnGetVertexSize = uint32_t(__thiscall*)(void*);
        using FnGetNumVertices = uint32_t(__thiscall*)(void*);
        using FnGetIndexSize = uint32_t(__thiscall*)(void*);
        using FnGetNumIndexes = uint32_t(__thiscall*)(void*);
        using FnGetBufferSize = uint32_t(__thiscall*)(void*);
        using FnCopyBufferData = void(__thiscall*)(void*, void*);
        using FnGetParentSceneNode = void* (__thiscall*)(void*);
        using FnGetVector3 = const Vector3* (__thiscall*)(void*);
        using FnGetQuaternion = const Quaternion* (__thiscall*)(void*);
        using FnCreateChildSceneNode = void* (__thiscall*)(
            void*, const std::string&, const Vector3&, const Quaternion&);
        using FnSetNodeScale = void(__thiscall*)(void*, const Vector3&);
        using FnAttachObject = void(__thiscall*)(void*, void*);
        using FnSetVisible = void(__thiscall*)(void*, bool);
        using FnSetCastShadows = void(__thiscall*)(void*, bool);
        using FnSetRenderQueueGroup = void(__thiscall*)(void*, uint8_t);
        using FnDestroySceneNode = void(__thiscall*)(void*, void*);
        using FnGetBounds = const AxisAlignedBox* (__thiscall*)(void*);
        using FnSetBounds = void(__thiscall*)(void*, const AxisAlignedBox&, bool);
        using FnGetRadius = float(__thiscall*)(void*);
        using FnSetRadius = void(__thiscall*)(void*, float);
        using FnGetMeshManager = void* (__cdecl*)();
        using FnRemoveResource = void(__thiscall*)(void*, const std::string&);
        using FnTerrainWordAt = uint16_t* (__cdecl*)(int, int);
        using FnTerrainManager = void* (__cdecl*)();
        using FnAtlasRectAt = const AtlasRect* (__thiscall*)(void*, uint32_t);
        using FnTileIndexAt = uint8_t(__cdecl*)(int, int);
        using FnMixAt = int(__cdecl*)(int, int);

        struct OgreApi
        {
            FnMeshClone cloneMesh = nullptr;
            FnCreateEntityFromMesh createEntity = nullptr;
            FnGetResourceName getResourceName = nullptr;
            FnGetNumSubMeshes getNumSubMeshes = nullptr;
            FnGetSubEntity getSubEntity = nullptr;
            FnGetRenderOperation getRenderOperation = nullptr;
            FnGetMaterialName getMaterialName = nullptr;
            FnSetMaterialName setMaterialName = nullptr;
            FnGetBuffer getBuffer = nullptr;
            FnGetVertexSize getVertexSize = nullptr;
            FnGetNumVertices getNumVertices = nullptr;
            FnGetIndexSize getIndexSize = nullptr;
            FnGetNumIndexes getNumIndexes = nullptr;
            FnGetBufferSize getBufferSize = nullptr;
            FnCopyBufferData copyBufferData = nullptr;
            FnGetParentSceneNode getParentSceneNode = nullptr;
            FnGetVector3 getNodePosition = nullptr;
            FnGetQuaternion getNodeOrientation = nullptr;
            FnGetVector3 getNodeScale = nullptr;
            FnCreateChildSceneNode createChildSceneNode = nullptr;
            FnSetNodeScale setNodeScale = nullptr;
            FnAttachObject attachObject = nullptr;
            FnSetVisible setVisible = nullptr;
            FnSetCastShadows setCastShadows = nullptr;
            FnSetRenderQueueGroup setRenderQueueGroup = nullptr;
            FnDestroySceneNode destroySceneNode = nullptr;
            FnGetBounds getBounds = nullptr;
            FnSetBounds setBounds = nullptr;
            FnGetRadius getRadius = nullptr;
            FnSetRadius setRadius = nullptr;
            FnGetMeshManager getMeshManager = nullptr;
            FnRemoveResource removeResource = nullptr;
        };

        TerrainConfig g_config;
        ProxyState g_proxy;
        OgreApi g_ogre;
        InlineDetour32 g_zoneConstructDetour;
        InlineDetour32 g_zoneProcessDetour;
        FnZoneConstruct g_originalZoneConstruct = nullptr;
        FnZoneProcess g_originalZoneProcess = nullptr;
        FnTerrainWordAt g_terrainWordAt = nullptr;
        FnTerrainManager g_terrainManager = nullptr;
        FnAtlasRectAt g_atlasRectAt = nullptr;
        FnTileIndexAt g_tileIndexAt = nullptr;
        FnMixAt g_mixAt = nullptr;
        uintptr_t g_mainBase = 0;
        std::atomic<bool> g_active{ false };
        std::atomic<bool> g_shutdown{ false };
        HANDLE g_worker = nullptr;
        std::mutex g_mutex;
        std::unordered_map<void*, int> g_zoneOrdinals;
        int g_nextZoneOrdinal = 0;
        uint32_t g_resourceSerial = 0;
        std::atomic<uint32_t> g_nullZoneDispatchCount{ 0 };
        int g_teardownDepth = 0;
        bool g_teardownIncludesClear = false;

        uintptr_t Rebase(uintptr_t preferredVa)
        {
            return g_mainBase + (preferredVa - kPreferredImageBase);
        }

        bool IsEnvEnabled(const char* name)
        {
            char value[16] = {};
            const DWORD length = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            return length > 0 && length < sizeof(value) && value[0] != '0';
        }

        std::filesystem::path GetIniPath()
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};
            return std::filesystem::path(path).parent_path() / L"openshim.ini";
        }

        float ReadIniFloat(const wchar_t* path, const char* key, float fallback)
        {
            char value[64] = {};
            char fallbackText[64] = {};
            sprintf_s(fallbackText, "%.9g", static_cast<double>(fallback));
            GetPrivateProfileStringA(
                "Terrain", key, fallbackText, value, static_cast<DWORD>(sizeof(value)),
                std::filesystem::path(path).string().c_str());
            char* end = nullptr;
            const float parsed = std::strtof(value, &end);
            return end != value && *end == '\0' ? parsed : fallback;
        }

        TerrainConfig ReadConfig()
        {
            TerrainConfig config;
            const std::filesystem::path ini = GetIniPath();
            const std::string iniText = ini.string();
            config.proxyEnabled = GetPrivateProfileIntA("Terrain", "TerrainProxyEnabled", 0, iniText.c_str()) != 0;
            config.proxyVisible = GetPrivateProfileIntA("Terrain", "TerrainProxyVisible", 1, iniText.c_str()) != 0;
            config.semanticCapture = GetPrivateProfileIntA("Terrain", "TerrainSemanticCapture", 0, iniText.c_str()) != 0;
            config.semanticDumpJson = GetPrivateProfileIntA("Terrain", "TerrainSemanticDumpJson", 1, iniText.c_str()) != 0;
            config.zoneOrdinal = GetPrivateProfileIntA("Terrain", "TerrainProxyZone", -1, iniText.c_str());
            config.clusterOrdinal = GetPrivateProfileIntA("Terrain", "TerrainProxyCluster", -1, iniText.c_str());
            config.zoneX = GetPrivateProfileIntA("Terrain", "TerrainProxyZoneX", INT_MIN, iniText.c_str());
            config.zoneZ = GetPrivateProfileIntA("Terrain", "TerrainProxyZoneZ", INT_MIN, iniText.c_str());
            config.clusterX = GetPrivateProfileIntA("Terrain", "TerrainProxyClusterX", INT_MIN, iniText.c_str());
            config.clusterZ = GetPrivateProfileIntA("Terrain", "TerrainProxyClusterZ", INT_MIN, iniText.c_str());
            config.offset.x = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetX", 0.0f);
            config.offset.y = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetY", 0.0f);
            config.offset.z = ReadIniFloat(ini.c_str(), "TerrainProxyOffsetZ", 0.0f);
            if (IsEnvEnabled("OPENSHIM_TERRAIN_PROXY"))
                config.proxyEnabled = true;
            if (IsEnvEnabled("OPENSHIM_TERRAIN_SEMANTIC_CAPTURE"))
                config.semanticCapture = true;
            return config;
        }

        bool ComputeSha256(const wchar_t* path, std::string& outHash)
        {
            outHash.clear();
            HMODULE bcrypt = LoadLibraryW(L"bcrypt.dll");
            if (!bcrypt)
                return false;

            const auto openProvider = reinterpret_cast<decltype(&BCryptOpenAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptOpenAlgorithmProvider"));
            const auto getProperty = reinterpret_cast<decltype(&BCryptGetProperty)>(
                GetProcAddress(bcrypt, "BCryptGetProperty"));
            const auto createHash = reinterpret_cast<decltype(&BCryptCreateHash)>(
                GetProcAddress(bcrypt, "BCryptCreateHash"));
            const auto hashData = reinterpret_cast<decltype(&BCryptHashData)>(
                GetProcAddress(bcrypt, "BCryptHashData"));
            const auto finishHash = reinterpret_cast<decltype(&BCryptFinishHash)>(
                GetProcAddress(bcrypt, "BCryptFinishHash"));
            const auto destroyHash = reinterpret_cast<decltype(&BCryptDestroyHash)>(
                GetProcAddress(bcrypt, "BCryptDestroyHash"));
            const auto closeProvider = reinterpret_cast<decltype(&BCryptCloseAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptCloseAlgorithmProvider"));
            if (!openProvider || !getProperty || !createHash || !hashData || !finishHash ||
                !destroyHash || !closeProvider)
            {
                FreeLibrary(bcrypt);
                return false;
            }

            BCRYPT_ALG_HANDLE algorithm = nullptr;
            BCRYPT_HASH_HANDLE hash = nullptr;
            HANDLE file = INVALID_HANDLE_VALUE;
            bool ok = false;
            do
            {
                if (openProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0) < 0)
                    break;
                DWORD objectBytes = 0;
                DWORD hashBytes = 0;
                DWORD resultBytes = 0;
                if (getProperty(algorithm, BCRYPT_OBJECT_LENGTH,
                        reinterpret_cast<PUCHAR>(&objectBytes), sizeof(objectBytes), &resultBytes, 0) < 0 ||
                    getProperty(algorithm, BCRYPT_HASH_LENGTH,
                        reinterpret_cast<PUCHAR>(&hashBytes), sizeof(hashBytes), &resultBytes, 0) < 0 ||
                    hashBytes != 32)
                {
                    break;
                }
                std::vector<uint8_t> object(objectBytes);
                std::array<uint8_t, 32> digest = {};
                if (createHash(algorithm, &hash, object.data(), objectBytes, nullptr, 0, 0) < 0)
                    break;
                file = CreateFileW(path, GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
                if (file == INVALID_HANDLE_VALUE)
                    break;
                std::array<uint8_t, 64 * 1024> buffer = {};
                for (;;)
                {
                    DWORD read = 0;
                    if (!ReadFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &read, nullptr))
                        break;
                    if (read == 0)
                    {
                        if (finishHash(hash, digest.data(), hashBytes, 0) < 0)
                            break;
                        std::ostringstream text;
                        text << std::uppercase << std::hex << std::setfill('0');
                        for (uint8_t byte : digest)
                            text << std::setw(2) << static_cast<unsigned>(byte);
                        outHash = text.str();
                        ok = true;
                        break;
                    }
                    if (hashData(hash, buffer.data(), read, 0) < 0)
                        break;
                }
            } while (false);

            if (file != INVALID_HANDLE_VALUE)
                CloseHandle(file);
            if (hash)
                destroyHash(hash);
            if (algorithm)
                closeProvider(algorithm, 0);
            FreeLibrary(bcrypt);
            return ok;
        }

        bool VerifyModuleHash(HMODULE module, const char* expected, std::string& actual)
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(module, path, MAX_PATH);
            return length > 0 && length < MAX_PATH && ComputeSha256(path, actual) && actual == expected;
        }

        template <typename T>
        T Resolve(HMODULE module, const char* name)
        {
            return reinterpret_cast<T>(GetProcAddress(module, name));
        }

        bool ResolveOgreApi(HMODULE module)
        {
            g_ogre.cloneMesh = Resolve<FnMeshClone>(module,
                "?clone@Mesh@Ogre@@QAE?AV?$SharedPtr@VMesh@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.createEntity = Resolve<FnCreateEntityFromMesh>(module,
                "?createEntity@SceneManager@Ogre@@UAEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$SharedPtr@VMesh@Ogre@@@2@@Z");
            g_ogre.getResourceName = Resolve<FnGetResourceName>(module,
                "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_ogre.getNumSubMeshes = Resolve<FnGetNumSubMeshes>(module, "?getNumSubMeshes@Mesh@Ogre@@QBEGXZ");
            g_ogre.getSubEntity = Resolve<FnGetSubEntity>(module, "?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            g_ogre.getRenderOperation = Resolve<FnGetRenderOperation>(module,
                "?getRenderOperation@SubEntity@Ogre@@UAEXAAVRenderOperation@2@@Z");
            g_ogre.getMaterialName = Resolve<FnGetMaterialName>(module,
                "?getMaterialName@SubEntity@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_ogre.setMaterialName = Resolve<FnSetMaterialName>(module,
                "?setMaterialName@Entity@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_ogre.getBuffer = Resolve<FnGetBuffer>(module,
                "?getBuffer@VertexBufferBinding@Ogre@@UBEABVHardwareVertexBufferSharedPtr@2@G@Z");
            g_ogre.getVertexSize = Resolve<FnGetVertexSize>(module, "?getVertexSize@HardwareVertexBuffer@Ogre@@QBEIXZ");
            g_ogre.getNumVertices = Resolve<FnGetNumVertices>(module, "?getNumVertices@HardwareVertexBuffer@Ogre@@QBEIXZ");
            g_ogre.getIndexSize = Resolve<FnGetIndexSize>(module, "?getIndexSize@HardwareIndexBuffer@Ogre@@QBEIXZ");
            g_ogre.getNumIndexes = Resolve<FnGetNumIndexes>(module, "?getNumIndexes@HardwareIndexBuffer@Ogre@@QBEIXZ");
            g_ogre.getBufferSize = Resolve<FnGetBufferSize>(module, "?getSizeInBytes@HardwareBuffer@Ogre@@QBEIXZ");
            g_ogre.copyBufferData = Resolve<FnCopyBufferData>(module, "?copyData@HardwareBuffer@Ogre@@UAEXAAV12@@Z");
            g_ogre.getParentSceneNode = Resolve<FnGetParentSceneNode>(module,
                "?getParentSceneNode@SceneNode@Ogre@@QBEPAV12@XZ");
            g_ogre.getNodePosition = Resolve<FnGetVector3>(module, "?getPosition@Node@Ogre@@UBEABVVector3@2@XZ");
            g_ogre.getNodeOrientation = Resolve<FnGetQuaternion>(module, "?getOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ");
            g_ogre.getNodeScale = Resolve<FnGetVector3>(module, "?getScale@Node@Ogre@@UBEABVVector3@2@XZ");
            g_ogre.createChildSceneNode = Resolve<FnCreateChildSceneNode>(module,
                "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABVVector3@2@ABVQuaternion@2@@Z");
            g_ogre.setNodeScale = Resolve<FnSetNodeScale>(module, "?setScale@Node@Ogre@@UAEXABVVector3@2@@Z");
            g_ogre.attachObject = Resolve<FnAttachObject>(module, "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            g_ogre.setVisible = Resolve<FnSetVisible>(module, "?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            g_ogre.setCastShadows = Resolve<FnSetCastShadows>(module, "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
            g_ogre.setRenderQueueGroup = Resolve<FnSetRenderQueueGroup>(module, "?setRenderQueueGroup@Entity@Ogre@@UAEXE@Z");
            g_ogre.destroySceneNode = Resolve<FnDestroySceneNode>(module, "?destroySceneNode@SceneManager@Ogre@@UAEXPAVSceneNode@2@@Z");
            g_ogre.getBounds = Resolve<FnGetBounds>(module, "?getBounds@Mesh@Ogre@@QBEABVAxisAlignedBox@2@XZ");
            g_ogre.setBounds = Resolve<FnSetBounds>(module, "?_setBounds@Mesh@Ogre@@QAEXABVAxisAlignedBox@2@_N@Z");
            g_ogre.getRadius = Resolve<FnGetRadius>(module, "?getBoundingSphereRadius@Mesh@Ogre@@QBEMXZ");
            g_ogre.setRadius = Resolve<FnSetRadius>(module, "?_setBoundingSphereRadius@Mesh@Ogre@@QAEXM@Z");
            g_ogre.getMeshManager = Resolve<FnGetMeshManager>(module, "?getSingletonPtr@MeshManager@Ogre@@SAPAV12@XZ");
            g_ogre.removeResource = Resolve<FnRemoveResource>(module,
                "?remove@ResourceManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

            const void* const required[] = {
                reinterpret_cast<void*>(g_ogre.cloneMesh), reinterpret_cast<void*>(g_ogre.createEntity),
                reinterpret_cast<void*>(g_ogre.getResourceName), reinterpret_cast<void*>(g_ogre.getNumSubMeshes),
                reinterpret_cast<void*>(g_ogre.getSubEntity), reinterpret_cast<void*>(g_ogre.getRenderOperation),
                reinterpret_cast<void*>(g_ogre.getMaterialName), reinterpret_cast<void*>(g_ogre.setMaterialName),
                reinterpret_cast<void*>(g_ogre.getBuffer), reinterpret_cast<void*>(g_ogre.getVertexSize),
                reinterpret_cast<void*>(g_ogre.getNumVertices), reinterpret_cast<void*>(g_ogre.getIndexSize),
                reinterpret_cast<void*>(g_ogre.getNumIndexes), reinterpret_cast<void*>(g_ogre.getBufferSize),
                reinterpret_cast<void*>(g_ogre.copyBufferData), reinterpret_cast<void*>(g_ogre.getParentSceneNode),
                reinterpret_cast<void*>(g_ogre.getNodePosition), reinterpret_cast<void*>(g_ogre.getNodeOrientation),
                reinterpret_cast<void*>(g_ogre.getNodeScale), reinterpret_cast<void*>(g_ogre.createChildSceneNode),
                reinterpret_cast<void*>(g_ogre.setNodeScale), reinterpret_cast<void*>(g_ogre.attachObject),
                reinterpret_cast<void*>(g_ogre.setVisible), reinterpret_cast<void*>(g_ogre.setCastShadows),
                reinterpret_cast<void*>(g_ogre.setRenderQueueGroup), reinterpret_cast<void*>(g_ogre.getBounds),
                reinterpret_cast<void*>(g_ogre.setBounds), reinterpret_cast<void*>(g_ogre.getRadius),
                reinterpret_cast<void*>(g_ogre.setRadius), reinterpret_cast<void*>(g_ogre.getMeshManager),
                reinterpret_cast<void*>(g_ogre.removeResource)
            };
            for (const void* function : required)
                if (!function)
                    return false;
            return true;
        }

        bool SafeReadZoneInt(void* zone, size_t offset, int& value)
        {
            __try
            {
                value = *reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadZoneByte(void* zone, size_t offset, uint8_t& value)
        {
            __try
            {
                value = *reinterpret_cast<const uint8_t*>(reinterpret_cast<const uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadZonePointer(void* zone, size_t offset, void*& value)
        {
            __try
            {
                value = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(zone) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeReadIntAddress(uintptr_t address, int& value)
        {
            __try
            {
                value = *reinterpret_cast<const int*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* SafeGetSceneManager()
        {
            __try
            {
                void* structure = *reinterpret_cast<void**>(Rebase(0x00920EA0));
                return structure
                    ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(structure) + 8)
                    : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool ReleaseCloneHandoff(OgreSharedPtr& pointer)
        {
            if (!pointer.rep || !pointer.info)
                return true;
            __try
            {
                auto* count = reinterpret_cast<volatile LONG*>(
                    reinterpret_cast<uint8_t*>(pointer.info) + sizeof(void*));
                const LONG current = InterlockedCompareExchange(count, 0, 0);
                if (current <= 1)
                    return false;
                InterlockedDecrement(count);
                pointer.rep = nullptr;
                pointer.info = nullptr;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ParseTerrainMeshName(const std::string& name, int& zoneX, int& zoneZ, int& clusterX, int& clusterZ)
        {
            int consumed = 0;
            return sscanf_s(name.c_str(), "RenderableTileCluster_%dx%d_%dx%d%n",
                &zoneX, &zoneZ, &clusterX, &clusterZ, &consumed) == 4 &&
                consumed == static_cast<int>(name.size());
        }

        bool GetEntityOperation(void* entity, RenderOperation& operation, void*& subEntity)
        {
            operation = {};
            subEntity = nullptr;
            if (!entity)
                return false;
            subEntity = g_ogre.getSubEntity(entity, 0);
            if (!subEntity)
                return false;
            g_ogre.getRenderOperation(subEntity, operation);
            return operation.vertexData && operation.indexData;
        }

        bool GetVertexBuffer(const RenderOperation& operation, uint16_t slot, void*& buffer)
        {
            buffer = nullptr;
            if (!operation.vertexData || !operation.vertexData->binding)
                return false;
            const OgreSharedPtr* pointer = g_ogre.getBuffer(operation.vertexData->binding, slot);
            if (!pointer || !pointer->rep)
                return false;
            buffer = pointer->rep;
            return true;
        }

        bool ValidateTerrainOperation(void* mesh, void* entity, const char* role)
        {
            if (!mesh || !entity || g_ogre.getNumSubMeshes(mesh) != 1)
                return false;
            RenderOperation operation = {};
            void* subEntity = nullptr;
            if (!GetEntityOperation(entity, operation, subEntity) ||
                operation.operationType != 4 || !operation.useIndexes ||
                operation.vertexData->vertexCount != kExpectedVertices ||
                operation.indexData->indexCount != kExpectedIndices)
            {
                return false;
            }

            static constexpr uint32_t expectedStrides[] = { 16, 4, 4 };
            for (uint16_t slot = 0; slot < 3; ++slot)
            {
                void* buffer = nullptr;
                if (!GetVertexBuffer(operation, slot, buffer) ||
                    g_ogre.getVertexSize(buffer) != expectedStrides[slot] ||
                    g_ogre.getNumVertices(buffer) < kExpectedVertices ||
                    g_ogre.getBufferSize(buffer) < expectedStrides[slot] * kExpectedVertices)
                {
                    return false;
                }
            }
            void* indexBuffer = operation.indexData->indexBuffer.rep;
            if (!indexBuffer || g_ogre.getIndexSize(indexBuffer) != 2 ||
                g_ogre.getNumIndexes(indexBuffer) < kExpectedIndices ||
                g_ogre.getBufferSize(indexBuffer) < kExpectedIndices * 2)
            {
                return false;
            }
            LogShimA(LogLevel::Info, "terrain-proxy",
                "[TERRAIN-PROXY] %s validated vertices=%u indices=%u topology=triangle-list strides=16/4/4",
                role, kExpectedVertices, kExpectedIndices);
            return true;
        }

        bool MatchSelection(int zoneOrdinal, int zoneX, int zoneZ, int clusterX, int clusterZ)
        {
            const int clusterOrdinal = clusterX * kClusterAxisCount + clusterZ;
            if (g_config.zoneOrdinal >= 0 && zoneOrdinal != g_config.zoneOrdinal)
                return false;
            if (g_config.clusterOrdinal >= 0 && clusterOrdinal != g_config.clusterOrdinal)
                return false;
            if (g_config.zoneX != INT_MIN && zoneX != g_config.zoneX)
                return false;
            if (g_config.zoneZ != INT_MIN && zoneZ != g_config.zoneZ)
                return false;
            if (g_config.clusterX != INT_MIN && clusterX != g_config.clusterX)
                return false;
            if (g_config.clusterZ != INT_MIN && clusterZ != g_config.clusterZ)
                return false;
            if (g_config.clusterOrdinal < 0 && g_config.clusterX == INT_MIN && g_config.clusterZ == INT_MIN)
                return clusterOrdinal == 0;
            return true;
        }

        void RemoveProxyMeshResource()
        {
            if (g_proxy.proxyMeshName.empty() || !g_ogre.getMeshManager || !g_ogre.removeResource)
                return;
            try
            {
                void* manager = g_ogre.getMeshManager();
                if (manager)
                    g_ogre.removeResource(manager, g_proxy.proxyMeshName);
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] failed removing mesh resource name=\"%s\"",
                    g_proxy.proxyMeshName.c_str());
            }
        }

        void ResetSelectedState()
        {
            g_proxy = {};
            g_zoneOrdinals.clear();
            g_nextZoneOrdinal = 0;
        }

        bool CreateProxy()
        {
            if (!g_config.proxyEnabled || g_proxy.proxyCreated)
                return g_proxy.proxyCreated;
            if (!g_proxy.sourceMesh || !g_proxy.sourceEntity || !g_proxy.sourceNode || !g_proxy.sceneManager)
                return false;
            try
            {
                if (!ValidateTerrainOperation(g_proxy.sourceMesh, g_proxy.sourceEntity, "stock cluster"))
                {
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] stock geometry contract mismatch; feature disabled for selected cluster");
                    return false;
                }

                const uint32_t serial = ++g_resourceSerial;
                char identity[128] = {};
                sprintf_s(identity, "z%d_%d/c%d_%d/%u", g_proxy.zoneX, g_proxy.zoneZ,
                    g_proxy.clusterX, g_proxy.clusterZ, serial);
                g_proxy.proxyMeshName = std::string("OpenShim/TerrainProxy/Mesh/") + identity;
                g_proxy.proxyEntityName = std::string("OpenShim/TerrainProxy/Entity/") + identity;
                g_proxy.proxyNodeName = std::string("OpenShim/TerrainProxy/Node/") + identity;

                OgreSharedPtr clone;
                const std::string group = "General";
                g_ogre.cloneMesh(g_proxy.sourceMesh, &clone, g_proxy.proxyMeshName, group);
                if (!clone.rep || !clone.info)
                    return false;
                g_proxy.proxyMesh = clone.rep;
                g_proxy.proxyEntity = g_ogre.createEntity(g_proxy.sceneManager, g_proxy.proxyEntityName, clone);
                if (!g_proxy.proxyEntity)
                {
                    ReleaseCloneHandoff(clone);
                    RemoveProxyMeshResource();
                    return false;
                }
                if (!ReleaseCloneHandoff(clone))
                    LogShimA(LogLevel::Warn, "terrain-proxy", "[TERRAIN-PROXY] retained clone handoff reference for safety");

                void* stockSubEntity = g_ogre.getSubEntity(g_proxy.sourceEntity, 0);
                const std::string* material = stockSubEntity ? g_ogre.getMaterialName(stockSubEntity) : nullptr;
                if (!material || material->empty())
                    return false;
                g_proxy.materialName = *material;
                const std::string autodetect = "Autodetect";
                g_ogre.setMaterialName(g_proxy.proxyEntity, g_proxy.materialName, autodetect);
                g_ogre.setCastShadows(g_proxy.proxyEntity, false);
                g_ogre.setRenderQueueGroup(g_proxy.proxyEntity, 0x28);
                g_ogre.setVisible(g_proxy.proxyEntity, g_config.proxyVisible);

                void* parent = g_ogre.getParentSceneNode(g_proxy.sourceNode);
                const Vector3* stockPosition = g_ogre.getNodePosition(g_proxy.sourceNode);
                const Quaternion* stockOrientation = g_ogre.getNodeOrientation(g_proxy.sourceNode);
                const Vector3* stockScale = g_ogre.getNodeScale(g_proxy.sourceNode);
                if (!parent || !stockPosition || !stockOrientation || !stockScale)
                    return false;
                Vector3 proxyPosition = *stockPosition;
                proxyPosition.x += g_config.offset.x;
                proxyPosition.y += g_config.offset.y;
                proxyPosition.z += g_config.offset.z;
                g_proxy.proxyNode = g_ogre.createChildSceneNode(
                    parent, g_proxy.proxyNodeName, proxyPosition, *stockOrientation);
                if (!g_proxy.proxyNode)
                    return false;
                g_ogre.setNodeScale(g_proxy.proxyNode, *stockScale);
                g_ogre.attachObject(g_proxy.proxyNode, g_proxy.proxyEntity);
                if (!ValidateTerrainOperation(g_proxy.proxyMesh, g_proxy.proxyEntity, "proxy cluster"))
                    return false;

                g_proxy.proxyCreated = true;
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] proxy created mesh=\"%s\" entity=\"%s\" material=\"%s\" worldPosition=(%.3f,%.3f,%.3f) visible=%d",
                    g_proxy.proxyMeshName.c_str(), g_proxy.proxyEntityName.c_str(),
                    g_proxy.materialName.c_str(), static_cast<double>(proxyPosition.x),
                    static_cast<double>(proxyPosition.y), static_cast<double>(proxyPosition.z),
                    g_config.proxyVisible ? 1 : 0);
                return true;
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] OGRE exception while creating proxy; stock terrain remains active");
                return false;
            }
        }

        bool RefreshProxyBuffers()
        {
            if (!g_proxy.proxyCreated || !g_proxy.sourceEntity || !g_proxy.proxyEntity)
                return false;
            try
            {
                RenderOperation source = {};
                RenderOperation destination = {};
                void* sourceSubEntity = nullptr;
                void* destinationSubEntity = nullptr;
                if (!GetEntityOperation(g_proxy.sourceEntity, source, sourceSubEntity) ||
                    !GetEntityOperation(g_proxy.proxyEntity, destination, destinationSubEntity) ||
                    source.vertexData->vertexCount != destination.vertexData->vertexCount ||
                    source.indexData->indexCount != destination.indexData->indexCount)
                {
                    return false;
                }

                // Slot 0 and the index buffer are immutable for ordinary terrain
                // rebuilds. Slots 1 and 2 contain packed UV/normal and height.
                for (uint16_t slot : { static_cast<uint16_t>(1), static_cast<uint16_t>(2) })
                {
                    void* sourceBuffer = nullptr;
                    void* destinationBuffer = nullptr;
                    if (!GetVertexBuffer(source, slot, sourceBuffer) ||
                        !GetVertexBuffer(destination, slot, destinationBuffer) ||
                        g_ogre.getBufferSize(sourceBuffer) != g_ogre.getBufferSize(destinationBuffer))
                    {
                        return false;
                    }
                    g_ogre.copyBufferData(destinationBuffer, sourceBuffer);
                }

                const AxisAlignedBox* bounds = g_ogre.getBounds(g_proxy.sourceMesh);
                if (bounds)
                    g_ogre.setBounds(g_proxy.proxyMesh, *bounds, false);
                g_ogre.setRadius(g_proxy.proxyMesh, g_ogre.getRadius(g_proxy.sourceMesh));
                const std::string* material = g_ogre.getMaterialName(sourceSubEntity);
                if (material && *material != g_proxy.materialName)
                {
                    g_proxy.materialName = *material;
                    const std::string autodetect = "Autodetect";
                    g_ogre.setMaterialName(g_proxy.proxyEntity, g_proxy.materialName, autodetect);
                }
                ++g_proxy.rebuildCount;
                if (g_proxy.rebuildCount <= 8)
                {
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] rebuild mirrored count=%u zone=(%d,%d) cluster=(%d,%d)",
                        g_proxy.rebuildCount, g_proxy.zoneX, g_proxy.zoneZ,
                        g_proxy.clusterX, g_proxy.clusterZ);
                }
                return true;
            }
            catch (...)
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] rebuild copy failed; disabling proxy visibility");
                try
                {
                    g_ogre.setVisible(g_proxy.proxyEntity, false);
                }
                catch (...)
                {
                }
                return false;
            }
        }

        bool ReadTerrainSemantic(int terrainX, int terrainZ, uint16_t& word,
            uint8_t& tileIndex, AtlasRect& rect)
        {
            __try
            {
                uint16_t* wordPointer = g_terrainWordAt(terrainX, terrainZ);
                void* manager = g_terrainManager();
                if (!wordPointer || !manager)
                    return false;
                word = *wordPointer;
                tileIndex = g_tileIndexAt(terrainX, terrainZ);
                const int accessorMix = g_mixAt(terrainX, terrainZ);
                if (accessorMix != static_cast<int>((word >> 4) & 0xF))
                    return false;
                const AtlasRect* activeRect = g_atlasRectAt(manager, tileIndex);
                if (!activeRect)
                    return false;
                rect = *activeRect;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        std::filesystem::path SemanticOutputPath()
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return L"terrain_semantic.json";
            return std::filesystem::path(path).parent_path() / L"terrain_semantic.json";
        }

        void CaptureSemantics(bool forceLog)
        {
            if (!g_config.semanticCapture || !g_proxy.selected)
                return;
            int originX = 0;
            int originZ = 0;
            if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), originX) ||
                !SafeReadIntAddress(Rebase(kTerrainOriginZVa), originZ))
                return;

            struct Cell
            {
                int x;
                int z;
                int terrainX;
                int terrainZ;
                uint16_t word;
                uint8_t tileIndex;
                AtlasRect rect;
            };
            std::array<Cell, 256> cells = {};
            uint32_t hash = 2166136261u;
            size_t count = 0;
            for (int z = 0; z < 16; ++z)
            {
                for (int x = 0; x < 16; ++x)
                {
                    Cell& cell = cells[count];
                    cell.x = x;
                    cell.z = z;
                    cell.terrainX = g_proxy.zoneX * 256 + originX - 128 +
                        (g_proxy.clusterX * 16 + x) * 4;
                    cell.terrainZ = g_proxy.zoneZ * 256 + originZ - 128 +
                        (g_proxy.clusterZ * 16 + z) * 4;
                    if (!ReadTerrainSemantic(cell.terrainX, cell.terrainZ, cell.word,
                            cell.tileIndex, cell.rect))
                    {
                        LogShimA(LogLevel::Warn, "terrain-semantic",
                            "[TERRAIN-SEMANTIC] capture failed cell=(%d,%d); stock rendering continues", x, z);
                        return;
                    }
                    const uint8_t bytes[] = {
                        static_cast<uint8_t>(cell.word & 0xFF), static_cast<uint8_t>(cell.word >> 8),
                        cell.tileIndex
                    };
                    for (uint8_t byte : bytes)
                    {
                        hash ^= byte;
                        hash *= 16777619u;
                    }
                    ++count;
                }
            }
            if (!forceLog && hash == g_proxy.semanticHash)
                return;
            g_proxy.semanticHash = hash;

            if (g_config.semanticDumpJson)
            {
                const std::filesystem::path outputPath = SemanticOutputPath();
                std::ofstream output(outputPath, std::ios::trunc);
                if (output)
                {
                    output << std::setprecision(9);
                    output << "{\n"
                        << "  \"schema\": \"bzr-openshim-terrain-semantic-v1\",\n"
                        << "  \"zone\": " << g_proxy.zoneOrdinal << ",\n"
                        << "  \"zoneX\": " << g_proxy.zoneX << ",\n"
                        << "  \"zoneZ\": " << g_proxy.zoneZ << ",\n"
                        << "  \"cluster\": " << g_proxy.clusterOrdinal << ",\n"
                        << "  \"clusterX\": " << g_proxy.clusterX << ",\n"
                        << "  \"clusterZ\": " << g_proxy.clusterZ << ",\n"
                        << "  \"sampleConvention\": {\"localU\": \"qx / 5.0\", \"localV\": \"qz / 5.0\", \"qxRange\": [0, 5], \"qzRange\": [0, 5]},\n"
                        << "  \"cells\": [\n";
                    for (size_t i = 0; i < count; ++i)
                    {
                        const Cell& cell = cells[i];
                        const unsigned typeA = (cell.word >> 12) & 0xF;
                        const unsigned typeB = (cell.word >> 8) & 0xF;
                        const unsigned mix = (cell.word >> 4) & 0xF;
                        const unsigned variant = cell.word & 0x3;
                        const unsigned lookupIndex = typeA * 64 + typeB * 8 + variant * 2 + ((mix >> 3) & 1);
                        output << "    {\"cellX\": " << cell.x
                            << ", \"cellZ\": " << cell.z
                            << ", \"terrainX\": " << cell.terrainX
                            << ", \"terrainZ\": " << cell.terrainZ
                            << ", \"terrainWord\": " << cell.word
                            << ", \"typeA\": " << typeA
                            << ", \"typeB\": " << typeB
                            << ", \"mix\": " << mix
                            << ", \"orientation\": " << (mix & 7)
                            << ", \"variant\": " << variant
                            << ", \"lookupIndex\": " << lookupIndex
                            << ", \"tileIndex\": " << static_cast<unsigned>(cell.tileIndex)
                            << ", \"atlasRect\": {\"u\": " << cell.rect.u
                            << ", \"v\": " << cell.rect.v
                            << ", \"w\": " << cell.rect.w
                            << ", \"h\": " << cell.rect.h << "}}";
                        output << (i + 1 == count ? "\n" : ",\n");
                    }
                    output << "  ]\n}\n";
                    output.close();
                    LogShimA(LogLevel::Info, "terrain-semantic",
                        "[TERRAIN-SEMANTIC] captured cells=%zu json=written path=\"%s\"",
                        count, outputPath.string().c_str());
                }
                else
                {
                    LogShimA(LogLevel::Warn, "terrain-semantic",
                        "[TERRAIN-SEMANTIC] json write failed path=\"%s\"",
                        outputPath.string().c_str());
                }
            }
            else
            {
                LogShimA(LogLevel::Info, "terrain-semantic",
                    "[TERRAIN-SEMANTIC] captured cells=%zu json=disabled", count);
            }
        }

        bool ObserveZone(void* zone)
        {
            if (!zone || g_proxy.selected)
                return g_proxy.selected;
            int zoneX = 0;
            int zoneZ = 0;
            if (!SafeReadZoneInt(zone, kZoneXOffset, zoneX) ||
                !SafeReadZoneInt(zone, kZoneZOffset, zoneZ))
                return false;
            int zoneOrdinal = 0;
            const auto existing = g_zoneOrdinals.find(zone);
            if (existing != g_zoneOrdinals.end())
                zoneOrdinal = existing->second;
            else
            {
                zoneOrdinal = g_nextZoneOrdinal++;
                g_zoneOrdinals.emplace(zone, zoneOrdinal);
            }

            for (int clusterX = 0; clusterX < kClusterAxisCount; ++clusterX)
            {
                for (int clusterZ = 0; clusterZ < kClusterAxisCount; ++clusterZ)
                {
                    if (!MatchSelection(zoneOrdinal, zoneX, zoneZ, clusterX, clusterZ))
                        continue;
                    const size_t meshOffset = kZoneMeshPtrBase + clusterX * kClusterXStride + clusterZ * kClusterZStride;
                    const size_t pointerOffset = clusterX * 0x10 + clusterZ * 4;
                    void* mesh = nullptr;
                    void* entity = nullptr;
                    void* node = nullptr;
                    if (!SafeReadZonePointer(zone, meshOffset, mesh) ||
                        !SafeReadZonePointer(zone, kZoneEntityBase + pointerOffset, entity) ||
                        !SafeReadZonePointer(zone, kZoneNodeBase + pointerOffset, node) ||
                        !mesh || !entity || !node)
                    {
                        return false;
                    }
                    const std::string* meshName = nullptr;
                    try
                    {
                        meshName = g_ogre.getResourceName(mesh);
                    }
                    catch (...)
                    {
                        return false;
                    }
                    int nameZoneX = 0;
                    int nameZoneZ = 0;
                    int nameClusterX = 0;
                    int nameClusterZ = 0;
                    if (!meshName || !ParseTerrainMeshName(*meshName, nameZoneX, nameZoneZ, nameClusterX, nameClusterZ) ||
                        nameZoneX != zoneX || nameZoneZ != zoneZ ||
                        nameClusterX != clusterX || nameClusterZ != clusterZ)
                    {
                        LogShimA(LogLevel::Warn, "terrain-proxy",
                            "[TERRAIN-PROXY] native identity validation failed; selected cluster skipped");
                        return false;
                    }
                    void* sceneManager = SafeGetSceneManager();
                    if (!sceneManager)
                        return false;

                    g_proxy.selected = true;
                    g_proxy.zone = zone;
                    g_proxy.sceneManager = sceneManager;
                    g_proxy.sourceMesh = mesh;
                    g_proxy.sourceEntity = entity;
                    g_proxy.sourceNode = node;
                    g_proxy.zoneOrdinal = zoneOrdinal;
                    g_proxy.zoneX = zoneX;
                    g_proxy.zoneZ = zoneZ;
                    g_proxy.clusterOrdinal = clusterX * kClusterAxisCount + clusterZ;
                    g_proxy.clusterX = clusterX;
                    g_proxy.clusterZ = clusterZ;
                    g_proxy.sourceMeshName = *meshName;
                    LogShimA(LogLevel::Info, "terrain-proxy",
                        "[TERRAIN-PROXY] selected zone=%d nativeZone=(%d,%d) cluster=%d nativeCluster=(%d,%d) mesh=\"%s\"",
                        zoneOrdinal, zoneX, zoneZ, g_proxy.clusterOrdinal, clusterX, clusterZ,
                        g_proxy.sourceMeshName.c_str());
                    CreateProxy();
                    CaptureSemantics(true);
                    return true;
                }
            }
            return false;
        }

        void* __fastcall ZoneConstructHook(
            void* zone, void*, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
        {
            void* constructedZone = zone;
            if (g_originalZoneConstruct)
                constructedZone = g_originalZoneConstruct(zone, a, b, c, d);
            if (!g_active.load(std::memory_order_acquire) || g_shutdown.load())
                return constructedZone;
            std::lock_guard<std::mutex> lock(g_mutex);
            ObserveZone(zone);
            return constructedZone;
        }

        void __fastcall ZoneProcessHook(void* zone, void*)
        {
            // FUN_00778450 immediately reads zone+0x270. A null entry means
            // the manager's zone table has already been corrupted or is not
            // ready, so forwarding it can only AV. This is a bounded fail-soft
            // backstop; healthy runs must leave the counter at zero.
            if (!zone)
            {
                const uint32_t count = g_nullZoneDispatchCount.fetch_add(
                    1, std::memory_order_relaxed) + 1;
                if (count <= 4)
                {
                    LogShimA(LogLevel::Warn, "terrain-proxy",
                        "[TERRAIN-PROXY] skipped invalid null zone rebuild dispatch count=%u",
                        count);
                }
                return;
            }

            bool selectedZone = false;
            bool fullDirty = false;
            bool heightDirty = false;
            int clusterX = 0;
            int clusterZ = 0;
            if (g_active.load(std::memory_order_acquire) && !g_shutdown.load())
            {
                std::lock_guard<std::mutex> lock(g_mutex);
                selectedZone = g_proxy.selected && g_proxy.zone == zone;
                if (selectedZone)
                {
                    clusterX = g_proxy.clusterX;
                    clusterZ = g_proxy.clusterZ;
                    const size_t index = static_cast<size_t>(clusterX * 4 + clusterZ);
                    uint8_t full = 0;
                    uint8_t height = 0;
                    uint8_t nextHeight = 0;
                    SafeReadZoneByte(zone, kFullDirtyOffset + index, full);
                    SafeReadZoneByte(zone, kHeightDirtyOffset + index, height);
                    SafeReadZoneByte(zone, kHeightDirtyNextOffset + index, nextHeight);
                    fullDirty = full != 0;
                    heightDirty = height != 0 || nextHeight != 0;
                }
            }

            if (g_originalZoneProcess)
                g_originalZoneProcess(zone);
            if (!g_active.load(std::memory_order_acquire) || g_shutdown.load())
                return;
            std::lock_guard<std::mutex> lock(g_mutex);
            if (!g_proxy.selected)
                ObserveZone(zone);
            if (selectedZone && g_proxy.zone == zone && (fullDirty || heightDirty))
            {
                if (g_config.proxyEnabled)
                {
                    if (!g_proxy.proxyCreated)
                        CreateProxy();
                    if (g_proxy.proxyCreated)
                        RefreshProxyBuffers();
                }
                if (fullDirty)
                    CaptureSemantics(false);
            }
        }

        bool InstallHooks()
        {
            g_mainBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
            if (!g_mainBase)
                return false;
            static const uint8_t expectedEntry[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            const uintptr_t constructor = Rebase(kZoneConstructVa);
            const uintptr_t process = Rebase(kZoneProcessVa);
            if (!ExpectedBytesMatchAt(constructor, expectedEntry, sizeof(expectedEntry)) ||
                !ExpectedBytesMatchAt(process, expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] released function entry bytes mismatched; Phase 2 unavailable");
                return false;
            }
            if (!InstallInlineDetour32(g_zoneConstructDetour, constructor,
                    reinterpret_cast<void*>(ZoneConstructHook), sizeof(expectedEntry),
                    expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] hook install failed; Phase 2 remains inert");
                return false;
            }
            g_originalZoneConstruct = reinterpret_cast<FnZoneConstruct>(g_zoneConstructDetour.trampoline);

            // Assign the first trampoline before attempting the second detour.
            // If the second install fails, the process-lifetime constructor
            // detour remains a transparent call-through while g_active is false.
            if (!InstallInlineDetour32(g_zoneProcessDetour, process,
                    reinterpret_cast<void*>(ZoneProcessHook), sizeof(expectedEntry),
                    expectedEntry, sizeof(expectedEntry)))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] rebuild hook install failed; constructor observation remains inert");
                return false;
            }
            g_originalZoneProcess = reinterpret_cast<FnZoneProcess>(g_zoneProcessDetour.trampoline);
            g_terrainWordAt = reinterpret_cast<FnTerrainWordAt>(Rebase(kTerrainWordAtVa));
            g_terrainManager = reinterpret_cast<FnTerrainManager>(Rebase(kTerrainManagerVa));
            g_atlasRectAt = reinterpret_cast<FnAtlasRectAt>(Rebase(kAtlasRectAtVa));
            g_tileIndexAt = reinterpret_cast<FnTileIndexAt>(Rebase(kTileIndexAtVa));
            g_mixAt = reinterpret_cast<FnMixAt>(Rebase(kMixAtVa));
            g_active.store(true, std::memory_order_release);
            return true;
        }

        DWORD WINAPI WorkerProc(void*)
        {
            HMODULE executable = GetModuleHandleW(nullptr);
            std::string exeHash;
            if (!VerifyModuleHash(executable, kExpectedExeSha256, exeHash))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] exact executable build not validated sha256=%s; Phase 2 unavailable",
                    exeHash.empty() ? "<unavailable>" : exeHash.c_str());
                return 0;
            }
            LogShimA(LogLevel::Info, "terrain-proxy", "[TERRAIN-PROXY] exact executable build validated");

            HMODULE ogre = nullptr;
            for (int attempt = 0; attempt < 600 && !g_shutdown.load(); ++attempt)
            {
                ogre = GetModuleHandleW(L"OgreMain.dll");
                if (ogre)
                    break;
                Sleep(100);
            }
            if (!ogre || g_shutdown.load())
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] OgreMain.dll unavailable; Phase 2 not installed");
                return 0;
            }
            std::string ogreHash;
            if (!VerifyModuleHash(ogre, kExpectedOgreSha256, ogreHash))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] exact Ogre build not validated sha256=%s; Phase 2 unavailable",
                    ogreHash.empty() ? "<unavailable>" : ogreHash.c_str());
                return 0;
            }
            if (!ResolveOgreApi(ogre))
            {
                LogShimA(LogLevel::Warn, "terrain-proxy",
                    "[TERRAIN-PROXY] required Ogre exports unresolved; Phase 2 unavailable");
                return 0;
            }
            if (InstallHooks())
            {
                LogShimA(LogLevel::Info, "terrain-proxy",
                    "[TERRAIN-PROXY] hooks installed constructor=0x%08X rebuild=0x%08X",
                    static_cast<unsigned>(Rebase(kZoneConstructVa)),
                    static_cast<unsigned>(Rebase(kZoneProcessVa)));
            }
            return 0;
        }
    }

    void InitializeTerrainProxyPhase2()
    {
        if (g_worker || g_active.load())
            return;
        g_config = ReadConfig();
        if (!g_config.proxyEnabled && !g_config.semanticCapture)
            return;
        g_shutdown.store(false);
        LogShimA(LogLevel::Info, "terrain-proxy",
            "[TERRAIN-PROXY] phase2 initialized proxy=%d semantic=%d (features default off)",
            g_config.proxyEnabled ? 1 : 0, g_config.semanticCapture ? 1 : 0);
        g_worker = CreateThread(nullptr, 0, WorkerProc, nullptr, 0, nullptr);
        if (!g_worker)
            LogShimA(LogLevel::Warn, "terrain-proxy", "[TERRAIN-PROXY] discovery worker creation failed");
    }

    void ShutdownTerrainProxyPhase2()
    {
        g_shutdown.store(true);
        g_active.store(false);
        if (g_worker)
        {
            WaitForSingleObject(g_worker, 2000);
            CloseHandle(g_worker);
            g_worker = nullptr;
        }
        std::lock_guard<std::mutex> lock(g_mutex);
        ResetSelectedState();
    }

    void TerrainProxySceneTeardownBegin(void* sceneManager, bool clearScene)
    {
        if (!g_active.load() || g_shutdown.load())
            return;
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_proxy.selected || (g_proxy.sceneManager && g_proxy.sceneManager != sceneManager))
            return;
        ++g_teardownDepth;
        g_teardownIncludesClear = g_teardownIncludesClear || clearScene;
    }

    void TerrainProxySceneTeardownComplete(void* sceneManager, bool clearScene)
    {
        if (!g_active.load() || g_shutdown.load())
            return;
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_proxy.selected || (g_proxy.sceneManager && g_proxy.sceneManager != sceneManager) || g_teardownDepth <= 0)
            return;
        g_teardownIncludesClear = g_teardownIncludesClear || clearScene;
        --g_teardownDepth;
        if (g_teardownDepth != 0)
            return;
        if (!g_teardownIncludesClear && g_proxy.proxyNode && g_ogre.destroySceneNode)
        {
            try
            {
                g_ogre.destroySceneNode(sceneManager, g_proxy.proxyNode);
            }
            catch (...)
            {
            }
        }
        RemoveProxyMeshResource();
        LogShimA(LogLevel::Info, "terrain-proxy",
            "[TERRAIN-PROXY] scene resources released reason=%s",
            g_teardownIncludesClear ? "clearScene" : "destroyAllMovableObjects");
        g_teardownIncludesClear = false;
        ResetSelectedState();
    }
}
