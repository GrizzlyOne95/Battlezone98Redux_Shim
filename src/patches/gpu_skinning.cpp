// gpu_skinning.cpp
// BZR Open Shim - experimental hardware skinning for skeletal craft (DX11).
//
// Ogre 1.10 already supports hardware skinning: an Entity whose materials'
// vertex programs all declare includes_skeletal_animation skips
// Mesh::softwareVertexBlend, renders its original vertex data (which carries
// the compiled BLENDINDICES/BLENDWEIGHT elements) and supplies the bone
// palette through world_matrix_array_3x4. Stock materials have no such
// programs, so this file builds them at runtime:
//
//  - per (source material, weights per vertex) a material clone whose every
//    supported pass binds a skinned twin of its installed HLSL vertex program
//    (see gpu_skinning_hlsl.h), with world-dependent auto constants remapped
//    to their world-space equivalents, because under hardware skinning the
//    "world" matrix Ogre supplies is bone 0's;
//  - a skinned shadow caster program on each pass, merged by Ogre's
//    deriveShadowCasterPass in place of the stock caster vertex program, or,
//    for a technique that names its own shadow_caster_material, a skinned
//    clone of that material put in the clone technique's place;
//  - a bone palette sized per entity (64, 128 or 256 bones).
//
// An entity is switched only when every sub-entity converts and Ogre then
// reports hardware animation enabled; otherwise its stock materials return.
// A clone material rendered with CPU-blended vertices would transform them
// twice, so converted entities are re-verified at the start of every frame,
// before anything renders. Any fault latches the feature off for the process.
#include "gpu_skinning.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "gpu_skinning_hlsl.h"
#include "memory_access.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <new>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        using Hooks::ResolveOgreProc;

        constexpr const char* kComponent = "gpu-skinning";
        constexpr const char* kCloneRoot = "OpenShim/GpuSkin/";
        constexpr const char* kProgramRoot = "OpenShim/GpuSkinVP/";
        // SceneManager::setShadowTextureCasterMaterial target used by the exe.
        constexpr const char* kCasterMaterialName = "Ogre/DepthShadowmap/Caster/Float";
        // Palette capacities the generated programs come in.
        // world_matrix_array_3x4 writes one 3x4 per bone matrix without a
        // bounds check, so an entity only ever gets a palette at least as big
        // as its bone count. 64 covers every stock craft and keeps their
        // program and clone names; larger skeletons (ISDF Chronicles'
        // ivatank has 79) get the next size up instead of the CPU. 256 is
        // Ogre's OGRE_MAX_NUM_BONES and 768 float4 fit an SM4 constant buffer.
        constexpr int kPaletteSizes[] = { 64, 128, 256 };
        // Ogre::SharedPtrInfo::useCount in the shipped OgreMain.dll (see
        // ogre_script_import_cache.cpp), not the header's +4.
        constexpr size_t kSharedPtrUseCountOffset = 0x14;
        // New entities are picked up this often; converted ones are verified
        // every frame.
        constexpr uint32_t kConvertIntervalFrames = 15;
        constexpr int kGpuProgramTypeVertex = 0;

        // Ogre::AutoConstantType values used below (OgreGpuProgramParams.h, 1.10).
        constexpr int kActWorldMatrixArray3x4 = 4;

        // Ogre::VertexElementSemantic / VertexElementType.
        constexpr int kVesBlendWeights = 2;
        constexpr int kVesBlendIndices = 3;
        constexpr int kVetFloat1 = 0;
        constexpr int kVetFloat4 = 3;
        constexpr int kVetUByte4 = 9;

        struct SharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };

        // Ogre::GpuProgramParameters::AutoConstantEntry (20 bytes on x86).
        struct AutoConstantEntry
        {
            int paramType;
            uint32_t physicalIndex;
            uint32_t elementCount;
            uint32_t data;
            uint16_t variability;
        };

        using FnSingleton = void* (__cdecl*)();
        using FnVoid = void(__thiscall*)(void*);
        using FnBool = bool(__thiscall*)(void*);
        using FnU16 = uint16_t(__thiscall*)(void*);
        using FnU32 = uint32_t(__thiscall*)(void*);
        using FnInt = int(__thiscall*)(void*);
        using FnPtrAt16 = void* (__thiscall*)(void*, uint16_t);
        using FnPtrAt32 = void* (__thiscall*)(void*, uint32_t);
        using FnStringRef = const std::string* (__thiscall*)(void*);
        using FnSharedRef = const SharedPtr* (__thiscall*)(void*);
        using FnSharedByValue = SharedPtr* (__thiscall*)(void*, SharedPtr*);
        using FnSetString = void(__thiscall*)(void*, const std::string&);
        using FnSetStringBool = void(__thiscall*)(void*, const std::string&, bool);
        using FnSetBool = void(__thiscall*)(void*, bool);
        using FnGetByName = SharedPtr* (__thiscall*)(void*, SharedPtr*, const std::string&, const std::string&);
        using FnCloneMaterial = SharedPtr* (__thiscall*)(void*, SharedPtr*, const std::string&, bool, const std::string&);
        using FnCreateProgram = SharedPtr* (__thiscall*)(void*, SharedPtr*, const std::string&, const std::string&, const std::string&, int);
        using FnGetParameter = std::string* (__thiscall*)(void*, std::string*, const std::string&);
        using FnSetParameter = bool(__thiscall*)(void*, const std::string&, const std::string&);
        using FnSetMaterial = void(__thiscall*)(void*, const SharedPtr&);
        using FnCopyMatching = void(__thiscall*)(void*, const void*);
        using FnGetAutoEntry = AutoConstantEntry* (__thiscall*)(void*, uint32_t);
        using FnSetNamedAuto = void(__thiscall*)(void*, const std::string&, int, uint32_t);
        using FnFindNamedConstant = const void* (__thiscall*)(void*, const std::string&, bool);
        using FnFindElement = const void* (__thiscall*)(void*, int, uint16_t);
        using FnElementType = int(__thiscall*)(const void*);
        using FnFrameListener = void(__thiscall*)(void*, void*);

        struct OgreApi
        {
            FnSingleton rootSingleton = nullptr;
            FnFrameListener addFrameListener = nullptr;
            FnSingleton materialManager = nullptr;
            FnSingleton programManager = nullptr;
            FnGetByName getMaterialByName = nullptr;
            FnGetByName getProgramByName = nullptr;
            FnSetString removeResource = nullptr;
            FnCloneMaterial cloneMaterial = nullptr;
            FnStringRef resourceName = nullptr;
            FnStringRef resourceGroup = nullptr;
            FnSetBool loadResource = nullptr;
            FnU16 getNumTechniques = nullptr;
            FnU16 getNumSupportedTechniques = nullptr;
            FnPtrAt16 getTechnique = nullptr;
            FnBool techniqueSupported = nullptr;
            FnU16 techniqueSchemeIndex = nullptr;
            FnU16 techniqueLodIndex = nullptr;
            FnU16 getNumPasses = nullptr;
            FnPtrAt16 getPass = nullptr;
            FnSharedByValue getShadowCasterMaterial = nullptr;
            FnBool hasVertexProgram = nullptr;
            FnSharedRef getVertexProgram = nullptr;
            FnSharedByValue getVertexProgramParameters = nullptr;
            FnSetStringBool setVertexProgram = nullptr;
            FnStringRef getShadowCasterVertexProgramName = nullptr;
            FnStringRef getShadowReceiverVertexProgramName = nullptr;
            FnSetString setShadowCasterVertexProgram = nullptr;
            FnSharedByValue getShadowCasterVertexProgramParameters = nullptr;
            FnSharedRef unifiedDelegate = nullptr;
            FnStringRef programSource = nullptr;
            FnSetString setProgramSource = nullptr;
            FnBool programSkeletal = nullptr;
            FnSetBool setProgramSkeletal = nullptr;
            FnBool programCompileError = nullptr;
            FnGetParameter getParameter = nullptr;
            FnSetParameter setParameter = nullptr;
            FnCreateProgram createProgram = nullptr;
            FnU32 getAutoConstantCount = nullptr;
            FnGetAutoEntry getAutoConstantEntry = nullptr;
            FnCopyMatching copyMatchingNamedConstants = nullptr;
            FnSetNamedAuto setNamedAutoConstant = nullptr;
            FnFindNamedConstant findNamedConstant = nullptr;
            FnBool entityInitialised = nullptr;
            FnBool entityHasSkeleton = nullptr;
            FnBool entityHasVertexAnimation = nullptr;
            FnBool entityHardwareAnimation = nullptr;
            FnU16 entityBoneMatrices = nullptr;
            FnInt entitySoftwareRequests = nullptr;
            FnSharedRef entityMesh = nullptr;
            FnU32 entitySubEntityCount = nullptr;
            FnPtrAt32 entitySubEntity = nullptr;
            FnSharedRef subEntityMaterial = nullptr;
            FnSetMaterial subEntitySetMaterial = nullptr;
            FnPtrAt16 meshVertexDataByTrackHandle = nullptr;
            FnFindElement findElementBySemantic = nullptr;
            FnElementType elementType = nullptr;
        };

        OgreApi g_ogre;
        bool g_apiResolved = false;
        bool g_apiAvailable = false;

        // Process-lifetime latch: a fault anywhere turns the feature off until
        // the game restarts.
        std::atomic<bool> g_failed{false};
        // True between mission start and end when the setting was on, the
        // renderer is Direct3D 11 and the API resolved.
        std::atomic<bool> g_active{false};
        bool g_listenerInstalled = false;
        // Set once the setting has been read for the current mission.
        bool g_missionEvaluated = false;
        uint32_t g_generation = 0;
        uint32_t g_frame = 0;

        enum class Reject : int
        {
            NotInitialised,
            NoSkeleton,
            VertexAnimation,
            TooManyBones,
            SoftwareRequests,
            NoMesh,
            NoBlendData,
            BlendFormat,
            CloneFailed,
            ShadowCasterMaterial,
            NoVertexProgram,
            ProgramNotHlsl4,
            ProgramAlreadySkeletal,
            ProgramReceiverOverride,
            ProgramCasterOverride,
            TransformRefused,
            CompileError,
            WorldAutoConstant,
            BonesUniformMissing,
            TechniqueLostSupport,
            HardwareNotEnabled,
            Count,
        };

        const char* RejectName(Reject reason)
        {
            switch (reason)
            {
            case Reject::NotInitialised: return "not-initialised";
            case Reject::NoSkeleton: return "no-skeleton";
            case Reject::VertexAnimation: return "vertex-animation";
            case Reject::TooManyBones: return "too-many-bones";
            case Reject::SoftwareRequests: return "software-requests";
            case Reject::NoMesh: return "no-mesh";
            case Reject::NoBlendData: return "no-blend-data";
            case Reject::BlendFormat: return "blend-format";
            case Reject::CloneFailed: return "clone-failed";
            case Reject::ShadowCasterMaterial: return "technique-shadow-caster-material";
            case Reject::NoVertexProgram: return "no-vertex-program";
            case Reject::ProgramNotHlsl4: return "program-not-hlsl-sm4";
            case Reject::ProgramAlreadySkeletal: return "program-already-skeletal";
            case Reject::ProgramReceiverOverride: return "pass-shadow-receiver-program";
            case Reject::ProgramCasterOverride: return "pass-shadow-caster-program";
            case Reject::TransformRefused: return "transform-refused";
            case Reject::CompileError: return "compile-error";
            case Reject::WorldAutoConstant: return "world-auto-constant";
            case Reject::BonesUniformMissing: return "bones-uniform-missing";
            case Reject::TechniqueLostSupport: return "technique-lost-support";
            case Reject::HardwareNotEnabled: return "hardware-not-enabled";
            default: return "?";
            }
        }

        struct Stats
        {
            uint32_t converted = 0;
            uint32_t reverted = 0;
            uint32_t reconverted = 0;
            uint32_t clones = 0;
            uint32_t programs = 0;
            uint32_t programsReused = 0;
            uint32_t rejects[static_cast<int>(Reject::Count)] = {};
        };
        Stats g_stats;

        struct ConversionError
        {
            Reject reason = Reject::CloneFailed;
            std::string detail;
        };

        // Per source material + weight count: the clone name, or empty after a
        // failure (so a refused material is not retried every scan).
        struct CloneRecord
        {
            std::string cloneName;
            SharedPtr clone;
            ConversionError error;
        };
        std::unordered_map<std::string, CloneRecord> g_clones;
        // Per concrete program + weight count + role: generated program name,
        // or empty after a failure.
        std::unordered_map<std::string, std::pair<std::string, ConversionError>> g_programs;
        std::unordered_set<std::string> g_loggedRejects;

        struct EntityRecord
        {
            std::vector<std::string> originals;
            std::vector<std::string> clones;
            std::vector<int> weights;
        };
        std::unordered_map<void*, EntityRecord> g_converted;
        std::unordered_set<void*> g_rejected;

        // Bridge root -> VirtualQuery verdict. Querying every root every frame
        // cost ~7% of an 80-craft frame. A readable root stays trusted while it
        // keeps appearing (SEH still guards the reads); an unreadable one is
        // re-queried on convert passes. Roots unseen for a frame are dropped.
        struct RootProbe
        {
            bool readable = false;
            uint32_t seenFrame = 0;
        };
        std::unordered_map<void*, RootProbe> g_rootProbes;

        // Caster material pass whose vertex program the skinned caster twins,
        // and whose parameters seed each skinned caster's.
        void* g_casterPass = nullptr;
        SharedPtr g_casterMaterial;
        // Offset of Technique::mShadowCasterMaterial, read from the exported
        // getter's code (Ogre exports no setter); 0 when the code does not
        // match, which keeps techniques with a caster material on the CPU.
        size_t g_techniqueCasterOffset = 0;

        int PaletteFor(int boneMatrices)
        {
            for (int size : kPaletteSizes)
            {
                if (boneMatrices <= size)
                    return size;
            }
            return 0;
        }

        // "w4" for the stock 64-bone palette, "w4b128" otherwise; used in
        // cache keys and in generated program and clone names.
        std::string VariantTag(int weights, int palette)
        {
            std::string tag = "w" + std::to_string(weights);
            if (palette != kPaletteSizes[0])
                tag += "b" + std::to_string(palette);
            return tag;
        }

        // ------------------------------------------------------------------
        // Ogre SharedPtr reference helpers (see terrain_proxy.cpp: the raw ABI
        // calls do not run SharedPtr's copy constructor or destructor).

        void AddRef(const SharedPtr& pointer)
        {
            if (!pointer.rep || !pointer.info)
                return;
            auto* count = reinterpret_cast<volatile LONG*>(
                reinterpret_cast<uint8_t*>(pointer.info) + kSharedPtrUseCountOffset);
            InterlockedIncrement(count);
        }

        // Drops a reference the caller owns. Never drops the last one, so it
        // cannot free; an object that would need freeing is leaked instead.
        void Release(SharedPtr& pointer)
        {
            if (pointer.rep && pointer.info)
            {
                auto* count = reinterpret_cast<volatile LONG*>(
                    reinterpret_cast<uint8_t*>(pointer.info) + kSharedPtrUseCountOffset);
                if (InterlockedCompareExchange(count, 0, 0) > 1)
                    InterlockedDecrement(count);
            }
            pointer = {};
        }

        std::string GetParameter(void* object, const char* name)
        {
            alignas(std::string) unsigned char storage[sizeof(std::string)];
            std::string* value = g_ogre.getParameter(
                object, reinterpret_cast<std::string*>(storage), std::string(name));
            std::string result = std::move(*value);
            value->~basic_string();
            return result;
        }

        std::string NameOf(void* resource)
        {
            const std::string* name = resource ? g_ogre.resourceName(resource) : nullptr;
            return name ? *name : std::string();
        }

        bool StartsWith(const std::string& text, const char* prefix)
        {
            return text.compare(0, std::strlen(prefix), prefix) == 0;
        }

        bool RttiContains(const void* object, const char* needle)
        {
            char buffer[128];
            const char* name = Hooks::TryGetRttiClassName(object, buffer, sizeof(buffer));
            return name && std::strstr(name, needle) != nullptr;
        }

        void LogRejectOnce(const std::string& key, Reject reason, const std::string& detail)
        {
            if (g_loggedRejects.size() > 256 || !g_loggedRejects.insert(key).second)
                return;
            LogShimA(LogLevel::Info, kComponent, "[GPUSKIN] stays on CPU: %s reason=%s %s",
                key.c_str(), RejectName(reason), detail.c_str());
        }

        // ------------------------------------------------------------------

        // Technique::getShadowCasterMaterial in the shipped OgreMain.dll is,
        // after the incremental-link jmp thunk:
        //   push ebp; mov ebp,esp; push ecx; mov eax,[ebp+8];
        //   mov edx,[ecx+N]; mov ecx,[ecx+N+4]; ...
        // i.e. a by-value copy of the SharedPtr member at N. Anything else
        // returns 0 and caster materials keep their technique on the CPU.
        size_t DecodeCasterMaterialOffset(const void* getter)
        {
            const uint8_t* code = static_cast<const uint8_t*>(getter);
            __try
            {
                for (int hops = 0; code && code[0] == 0xE9 && hops < 4; ++hops)
                {
                    int32_t rel = 0;
                    std::memcpy(&rel, code + 1, sizeof(rel));
                    code = code + 5 + rel;
                }
                static const uint8_t kPrologue[] = { 0x55, 0x8B, 0xEC, 0x51, 0x8B, 0x45, 0x08, 0x8B, 0x51 };
                if (!code || std::memcmp(code, kPrologue, sizeof(kPrologue)) != 0)
                    return 0;
                const uint8_t offset = code[9];
                if (code[10] != 0x8B || code[11] != 0x49 || code[12] != static_cast<uint8_t>(offset + 4) ||
                    offset < 0x10 || offset >= 0x7C)
                {
                    return 0;
                }
                return offset;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool ResolveApi()
        {
            if (g_apiResolved)
                return g_apiAvailable;
            g_apiResolved = true;

#define OS_STR "?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@"
            OgreApi& o = g_ogre;
            o.rootSingleton = ResolveOgreProc<FnSingleton>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            o.addFrameListener = ResolveOgreProc<FnFrameListener>("?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
            o.materialManager = ResolveOgreProc<FnSingleton>("?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            o.programManager = ResolveOgreProc<FnSingleton>("?getSingletonPtr@HighLevelGpuProgramManager@Ogre@@SAPAV12@XZ");
            o.getMaterialByName = ResolveOgreProc<FnGetByName>(
                "?getByName@MaterialManager@Ogre@@QAE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV" OS_STR "0@Z");
            o.getProgramByName = ResolveOgreProc<FnGetByName>(
                "?getByName@HighLevelGpuProgramManager@Ogre@@QAE?AV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@ABV" OS_STR "0@Z");
            o.removeResource = ResolveOgreProc<FnSetString>("?remove@ResourceManager@Ogre@@UAEXABV" OS_STR "@Z");
            o.cloneMaterial = ResolveOgreProc<FnCloneMaterial>(
                "?clone@Material@Ogre@@QBE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV" OS_STR "_N0@Z");
            o.resourceName = ResolveOgreProc<FnStringRef>("?getName@Resource@Ogre@@UBEABV" OS_STR "XZ");
            o.resourceGroup = ResolveOgreProc<FnStringRef>("?getGroup@Resource@Ogre@@UBEABV" OS_STR "XZ");
            o.loadResource = ResolveOgreProc<FnSetBool>("?load@Resource@Ogre@@UAEX_N@Z");
            o.getNumTechniques = ResolveOgreProc<FnU16>("?getNumTechniques@Material@Ogre@@QBEGXZ");
            o.getNumSupportedTechniques = ResolveOgreProc<FnU16>("?getNumSupportedTechniques@Material@Ogre@@QBEGXZ");
            o.getTechnique = ResolveOgreProc<FnPtrAt16>("?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
            o.techniqueSupported = ResolveOgreProc<FnBool>("?isSupported@Technique@Ogre@@QBE_NXZ");
            o.techniqueSchemeIndex = ResolveOgreProc<FnU16>("?_getSchemeIndex@Technique@Ogre@@QBEGXZ");
            o.techniqueLodIndex = ResolveOgreProc<FnU16>("?getLodIndex@Technique@Ogre@@QBEGXZ");
            o.getNumPasses = ResolveOgreProc<FnU16>("?getNumPasses@Technique@Ogre@@QBEGXZ");
            o.getPass = ResolveOgreProc<FnPtrAt16>("?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
            o.getShadowCasterMaterial = ResolveOgreProc<FnSharedByValue>(
                "?getShadowCasterMaterial@Technique@Ogre@@QBE?AV?$SharedPtr@VMaterial@Ogre@@@2@XZ");
            o.hasVertexProgram = ResolveOgreProc<FnBool>("?hasVertexProgram@Pass@Ogre@@QBE_NXZ");
            o.getVertexProgram = ResolveOgreProc<FnSharedRef>(
                "?getVertexProgram@Pass@Ogre@@QBEABV?$SharedPtr@VGpuProgram@Ogre@@@2@XZ");
            o.getVertexProgramParameters = ResolveOgreProc<FnSharedByValue>(
                "?getVertexProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            o.setVertexProgram = ResolveOgreProc<FnSetStringBool>(
                "?setVertexProgram@Pass@Ogre@@QAEXABV" OS_STR "_N@Z");
            o.getShadowCasterVertexProgramName = ResolveOgreProc<FnStringRef>(
                "?getShadowCasterVertexProgramName@Pass@Ogre@@QBEABV" OS_STR "XZ");
            o.getShadowReceiverVertexProgramName = ResolveOgreProc<FnStringRef>(
                "?getShadowReceiverVertexProgramName@Pass@Ogre@@QBEABV" OS_STR "XZ");
            o.setShadowCasterVertexProgram = ResolveOgreProc<FnSetString>(
                "?setShadowCasterVertexProgram@Pass@Ogre@@QAEXABV" OS_STR "@Z");
            o.getShadowCasterVertexProgramParameters = ResolveOgreProc<FnSharedByValue>(
                "?getShadowCasterVertexProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            o.unifiedDelegate = ResolveOgreProc<FnSharedRef>(
                "?_getDelegate@UnifiedHighLevelGpuProgram@Ogre@@QBEABV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@XZ");
            o.programSource = ResolveOgreProc<FnStringRef>("?getSource@GpuProgram@Ogre@@UBEABV" OS_STR "XZ");
            o.setProgramSource = ResolveOgreProc<FnSetString>("?setSource@GpuProgram@Ogre@@UAEXABV" OS_STR "@Z");
            o.programSkeletal = ResolveOgreProc<FnBool>("?isSkeletalAnimationIncluded@GpuProgram@Ogre@@UBE_NXZ");
            o.setProgramSkeletal = ResolveOgreProc<FnSetBool>("?setSkeletalAnimationIncluded@GpuProgram@Ogre@@UAEX_N@Z");
            o.programCompileError = ResolveOgreProc<FnBool>("?hasCompileError@GpuProgram@Ogre@@UBE_NXZ");
            o.getParameter = ResolveOgreProc<FnGetParameter>(
                "?getParameter@StringInterface@Ogre@@UBE?AV" OS_STR "ABV34@@Z");
            o.setParameter = ResolveOgreProc<FnSetParameter>(
                "?setParameter@StringInterface@Ogre@@UAE_NABV" OS_STR "0@Z");
            o.createProgram = ResolveOgreProc<FnCreateProgram>(
                "?createProgram@HighLevelGpuProgramManager@Ogre@@QAE?AV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@ABV" OS_STR "00W4GpuProgramType@2@@Z");
            o.getAutoConstantCount = ResolveOgreProc<FnU32>("?getAutoConstantCount@GpuProgramParameters@Ogre@@QBEIXZ");
            o.getAutoConstantEntry = ResolveOgreProc<FnGetAutoEntry>(
                "?getAutoConstantEntry@GpuProgramParameters@Ogre@@QAEPAVAutoConstantEntry@12@I@Z");
            o.copyMatchingNamedConstants = ResolveOgreProc<FnCopyMatching>(
                "?copyMatchingNamedConstantsFrom@GpuProgramParameters@Ogre@@QAEXABV12@@Z");
            o.setNamedAutoConstant = ResolveOgreProc<FnSetNamedAuto>(
                "?setNamedAutoConstant@GpuProgramParameters@Ogre@@QAEXABV" OS_STR "W4AutoConstantType@12@I@Z");
            o.findNamedConstant = ResolveOgreProc<FnFindNamedConstant>(
                "?_findNamedConstantDefinition@GpuProgramParameters@Ogre@@QBEPBUGpuConstantDefinition@2@ABV" OS_STR "_N@Z");
            o.entityInitialised = ResolveOgreProc<FnBool>("?isInitialised@Entity@Ogre@@QBE_NXZ");
            o.entityHasSkeleton = ResolveOgreProc<FnBool>("?hasSkeleton@Entity@Ogre@@QBE_NXZ");
            o.entityHasVertexAnimation = ResolveOgreProc<FnBool>("?hasVertexAnimation@Entity@Ogre@@QBE_NXZ");
            o.entityHardwareAnimation = ResolveOgreProc<FnBool>("?isHardwareAnimationEnabled@Entity@Ogre@@QAE_NXZ");
            o.entityBoneMatrices = ResolveOgreProc<FnU16>("?_getNumBoneMatrices@Entity@Ogre@@QBEGXZ");
            o.entitySoftwareRequests = ResolveOgreProc<FnInt>("?getSoftwareAnimationRequests@Entity@Ogre@@QBEHXZ");
            o.entityMesh = ResolveOgreProc<FnSharedRef>("?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ");
            o.entitySubEntityCount = ResolveOgreProc<FnU32>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            o.entitySubEntity = ResolveOgreProc<FnPtrAt32>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            o.subEntityMaterial = ResolveOgreProc<FnSharedRef>(
                "?getMaterial@SubEntity@Ogre@@UBEABV?$SharedPtr@VMaterial@Ogre@@@2@XZ");
            o.subEntitySetMaterial = ResolveOgreProc<FnSetMaterial>(
                "?setMaterial@SubEntity@Ogre@@QAEXABV?$SharedPtr@VMaterial@Ogre@@@2@@Z");
            o.meshVertexDataByTrackHandle = ResolveOgreProc<FnPtrAt16>(
                "?getVertexDataByTrackHandle@Mesh@Ogre@@QAEPAVVertexData@2@G@Z");
            o.findElementBySemantic = ResolveOgreProc<FnFindElement>(
                "?findElementBySemantic@VertexDeclaration@Ogre@@UBEPBVVertexElement@2@W4VertexElementSemantic@2@G@Z");
            o.elementType = ResolveOgreProc<FnElementType>("?getType@VertexElement@Ogre@@QBE?AW4VertexElementType@2@XZ");
#undef OS_STR

            const void* const required[] = {
                o.rootSingleton, o.addFrameListener, o.materialManager, o.programManager,
                o.getMaterialByName, o.getProgramByName, o.removeResource, o.cloneMaterial,
                o.resourceName, o.resourceGroup, o.loadResource, o.getNumTechniques,
                o.getNumSupportedTechniques, o.getTechnique, o.techniqueSupported,
                o.techniqueSchemeIndex, o.techniqueLodIndex, o.getNumPasses,
                o.getPass, o.getShadowCasterMaterial, o.hasVertexProgram, o.getVertexProgram,
                o.getVertexProgramParameters, o.setVertexProgram, o.getShadowCasterVertexProgramName,
                o.getShadowReceiverVertexProgramName, o.setShadowCasterVertexProgram,
                o.getShadowCasterVertexProgramParameters, o.unifiedDelegate, o.programSource,
                o.setProgramSource, o.programSkeletal, o.setProgramSkeletal,
                o.programCompileError, o.getParameter, o.setParameter, o.createProgram,
                o.getAutoConstantCount, o.getAutoConstantEntry, o.copyMatchingNamedConstants,
                o.setNamedAutoConstant, o.findNamedConstant, o.entityInitialised, o.entityHasSkeleton,
                o.entityHasVertexAnimation, o.entityHardwareAnimation, o.entityBoneMatrices,
                o.entitySoftwareRequests, o.entityMesh, o.entitySubEntityCount, o.entitySubEntity,
                o.subEntityMaterial, o.subEntitySetMaterial, o.meshVertexDataByTrackHandle,
                o.findElementBySemantic, o.elementType,
            };
            size_t missing = 0;
            for (const void* proc : required)
            {
                if (!proc)
                    ++missing;
            }
            g_apiAvailable = missing == 0;
            if (g_apiAvailable)
                g_techniqueCasterOffset = DecodeCasterMaterialOffset(reinterpret_cast<const void*>(o.getShadowCasterMaterial));
            if (!g_apiAvailable)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[GPUSKIN] disabled: %zu required OgreMain exports missing", missing);
            }
            return g_apiAvailable;
        }

        // ------------------------------------------------------------------
        // Auto constants. Under hardware skinning Ogre's "world" matrix is
        // bone 0, and the skinned position is already in world space, so every
        // world-relative binding becomes its world-space (identity world)
        // equivalent. Bindings that need the real world matrix are refused.

        int RemapAutoConstant(int type)
        {
            switch (type)
            {
            case 24: return 16;  // worldviewproj -> viewproj
            case 20: return 8;   // worldview -> view
            case 21: return 9;   // inverse_worldview -> inverse_view
            case 22: return 10;  // transpose_worldview -> transpose_view
            case 23: return 11;  // inverse_transpose_worldview -> inverse_transpose_view
            case 25: return 17;  // inverse_worldviewproj -> inverse_viewproj
            case 26: return 18;  // transpose_worldviewproj -> transpose_viewproj
            case 27: return 19;  // inverse_transpose_worldviewproj -> inverse_transpose_viewproj
            case 82: return 80;  // texture_worldviewproj -> texture_viewproj
            case 83: return 81;  // texture_worldviewproj_array -> texture_viewproj_array
            case 86: return 84;  // spotlight_worldviewproj -> spotlight_viewproj
            case 87: return 85;  // spotlight_worldviewproj_array -> spotlight_viewproj_array
            case 45: return 44;  // light_position_object_space -> light_position
            case 48: return 47;  // light_direction_object_space -> light_direction
            case 60: return 59;  // light_position_object_space_array -> light_position_array
            case 63: return 62;  // light_direction_object_space_array -> light_direction_array
            case 79: return 78;  // camera_position_object_space -> camera_position
            case 131: return 130; // lod_camera_position_object_space -> lod_camera_position
            case 0: case 1: case 2: case 3:  // world matrix family
            case 4: case 5: case 6: case 7:  // world matrix arrays (already skinned)
            case 50: case 65:                // light distance in object space
                return -1;
            default:
                return type;
            }
        }

        bool PrepareParameters(void* params, ConversionError& error)
        {
            if (!params)
            {
                error = { Reject::BonesUniformMissing, "no parameters" };
                return false;
            }
            const uint32_t count = g_ogre.getAutoConstantCount(params);
            for (uint32_t i = 0; i < count; ++i)
            {
                AutoConstantEntry* entry = g_ogre.getAutoConstantEntry(params, i);
                if (!entry)
                    continue;
                const int mapped = RemapAutoConstant(entry->paramType);
                if (mapped < 0)
                {
                    error = { Reject::WorldAutoConstant, "auto=" + std::to_string(entry->paramType) };
                    return false;
                }
                // Variability stays: the world-relative types are per-object,
                // a superset of the global ones they become.
                entry->paramType = mapped;
            }
            const std::string bones = GpuSkinning::kBonePaletteUniform;
            if (!g_ogre.findNamedConstant(params, bones, false))
            {
                error = { Reject::BonesUniformMissing, "" };
                return false;
            }
            g_ogre.setNamedAutoConstant(params, bones, kActWorldMatrixArray3x4, 0);
            return true;
        }

        // ------------------------------------------------------------------
        // Programs.

        // The HLSL program that carries source: unified programs delegate.
        void* ConcreteProgram(void* program)
        {
            if (!program)
                return nullptr;
            if (RttiContains(program, "UnifiedHighLevelGpuProgram@Ogre"))
            {
                const SharedPtr* delegate = g_ogre.unifiedDelegate(program);
                return delegate ? delegate->rep : nullptr;
            }
            return program;
        }

        // Returns the skinned twin's name, creating and compiling it once.
        std::string SkinnedProgramFor(void* program, int weights, int palette, ConversionError& error)
        {
            void* concrete = ConcreteProgram(program);
            if (!concrete)
            {
                error = { Reject::NoVertexProgram, "no delegate" };
                return {};
            }
            const std::string concreteName = NameOf(concrete);
            const std::string tag = VariantTag(weights, palette);
            const std::string key = concreteName + "|" + tag;
            const auto cached = g_programs.find(key);
            if (cached != g_programs.end())
            {
                error = cached->second.second;
                return cached->second.first;
            }

            auto fail = [&](Reject reason, const std::string& detail) {
                error = { reason, concreteName + " " + detail };
                g_programs[key] = { std::string(), error };
                return std::string();
            };

            // The class, not getLanguage: the export is GpuProgram's own
            // implementation ("asm"), and a direct call skips the override.
            if (!RttiContains(concrete, "D3D11HLSLProgram"))
                return fail(Reject::ProgramNotHlsl4, "class");
            const std::string target = GetParameter(concrete, "target");
            if (target.rfind("vs_4", 0) != 0 && target.rfind("vs_5", 0) != 0)
                return fail(Reject::ProgramNotHlsl4, "target=" + target);
            if (g_ogre.programSkeletal(concrete))
                return fail(Reject::ProgramAlreadySkeletal, "");
            const std::string* source = g_ogre.programSource(concrete);
            if (!source || source->empty())
                return fail(Reject::TransformRefused, "no source");

            const std::string entry = GetParameter(concrete, "entry_point");
            const std::string defines = GetParameter(concrete, "preprocessor_defines");
            const GpuSkinning::SkinnedSourceResult skinned =
                GpuSkinning::MakeSkinnedVertexSource(*source, entry, weights, palette, defines);
            if (!skinned.ok)
                return fail(Reject::TransformRefused, skinned.error);

            const std::string columnMajor = GetParameter(concrete, "column_major_matrices");
            char hash[17];
            sprintf_s(hash, "%016llx", GpuSkinning::HashText(
                skinned.source + "\n" + target + "\n" + entry + "\n" + defines + "\n" + columnMajor));
            const std::string name = std::string(kProgramRoot) + tag + "/" + hash;

            void* manager = g_ogre.programManager();
            if (!manager)
                return fail(Reject::CompileError, "no program manager");
            const std::string& group = *g_ogre.resourceGroup(concrete);

            SharedPtr existing;
            g_ogre.getProgramByName(manager, &existing, name, group);
            if (existing.rep)
            {
                const bool usable = !g_ogre.programCompileError(existing.rep);
                Release(existing);
                if (!usable)
                    return fail(Reject::CompileError, name);
                ++g_stats.programsReused;
                g_programs[key] = { name, ConversionError{} };
                return name;
            }

            SharedPtr created;
            g_ogre.createProgram(manager, &created, name, group, std::string("hlsl"), kGpuProgramTypeVertex);
            if (!created.rep)
                return fail(Reject::CompileError, "create failed");
            g_ogre.setProgramSource(created.rep, skinned.source);
            bool parametersSet =
                g_ogre.setParameter(created.rep, std::string("target"), target) &&
                g_ogre.setParameter(created.rep, std::string("entry_point"), entry);
            if (!defines.empty())
                parametersSet = g_ogre.setParameter(created.rep, std::string("preprocessor_defines"), defines) && parametersSet;
            if (!columnMajor.empty())
                parametersSet = g_ogre.setParameter(created.rep, std::string("column_major_matrices"), columnMajor) && parametersSet;
            g_ogre.setProgramSkeletal(created.rep, true);
            if (parametersSet)
                g_ogre.loadResource(created.rep, false);
            const bool compiled = parametersSet && !g_ogre.programCompileError(created.rep);
            Release(created);
            if (!compiled)
                return fail(Reject::CompileError, name + " from " + concreteName);

            ++g_stats.programs;
            LogShimA(LogLevel::Info, kComponent,
                "[GPUSKIN] program %s from %s weights=%d bones=%d position=%s normal=%s",
                name.c_str(), concreteName.c_str(), weights, palette,
                skinned.positionParam.c_str(),
                skinned.normalParam.empty() ? "-" : skinned.normalParam.c_str());
            g_programs[key] = { name, ConversionError{} };
            return name;
        }

        bool EnsureCasterPass()
        {
            if (g_casterPass)
                return true;
            void* manager = g_ogre.materialManager();
            if (!manager)
                return false;
            SharedPtr material;
            g_ogre.getMaterialByName(manager, &material, std::string(kCasterMaterialName), std::string("Autodetect"));
            if (!material.rep)
                return false;
            void* technique = g_ogre.getNumTechniques(material.rep) > 0
                ? g_ogre.getTechnique(material.rep, 0) : nullptr;
            void* pass = technique && g_ogre.getNumPasses(technique) > 0
                ? g_ogre.getPass(technique, 0) : nullptr;
            if (!pass || !g_ogre.hasVertexProgram(pass))
            {
                Release(material);
                return false;
            }
            // Keep the reference: the pass must outlive every clone using it.
            g_casterMaterial = material;
            g_casterPass = pass;
            return true;
        }

        // `asCaster` converts a pass of a technique's custom shadow caster
        // material: Ogre renders that pass itself as the caster, so it gets no
        // caster program of its own.
        bool ConvertPass(void* pass, int weights, int palette, bool asCaster, ConversionError& error)
        {
            if (!g_ogre.hasVertexProgram(pass))
            {
                error = { Reject::NoVertexProgram, "" };
                return false;
            }
            if (!g_ogre.getShadowReceiverVertexProgramName(pass)->empty())
            {
                error = { Reject::ProgramReceiverOverride, "" };
                return false;
            }
            if (!g_ogre.getShadowCasterVertexProgramName(pass)->empty())
            {
                error = { Reject::ProgramCasterOverride, "" };
                return false;
            }
            const SharedPtr* program = g_ogre.getVertexProgram(pass);
            const std::string skinnedName = SkinnedProgramFor(program ? program->rep : nullptr, weights, palette, error);
            if (skinnedName.empty())
                return false;

            if (asCaster)
            {
                g_ogre.setVertexProgram(pass, skinnedName, false);
                SharedPtr params;
                g_ogre.getVertexProgramParameters(pass, &params);
                const bool ready = PrepareParameters(params.rep, error);
                Release(params);
                return ready;
            }

            if (!EnsureCasterPass())
            {
                error = { Reject::NoVertexProgram, std::string("caster material ") + kCasterMaterialName };
                return false;
            }
            const SharedPtr* casterProgram = g_ogre.getVertexProgram(g_casterPass);
            const std::string casterName = SkinnedProgramFor(casterProgram ? casterProgram->rep : nullptr, weights, palette, error);
            if (casterName.empty())
                return false;

            // Pass::setVertexProgram rebuilds the parameters for the new
            // program and copies every matching named constant and auto
            // binding across (GpuProgramUsage::recreateParameters).
            g_ogre.setVertexProgram(pass, skinnedName, false);
            SharedPtr params;
            g_ogre.getVertexProgramParameters(pass, &params);
            const bool mainReady = PrepareParameters(params.rep, error);
            Release(params);
            if (!mainReady)
                return false;

            g_ogre.setShadowCasterVertexProgram(pass, casterName);
            SharedPtr casterParams;
            g_ogre.getShadowCasterVertexProgramParameters(pass, &casterParams);
            SharedPtr stockCasterParams;
            g_ogre.getVertexProgramParameters(g_casterPass, &stockCasterParams);
            bool casterReady = false;
            if (casterParams.rep && stockCasterParams.rep)
            {
                g_ogre.copyMatchingNamedConstants(casterParams.rep, stockCasterParams.rep);
                casterReady = PrepareParameters(casterParams.rep, error);
            }
            else
            {
                error = { Reject::BonesUniformMissing, "caster parameters" };
            }
            Release(stockCasterParams);
            Release(casterParams);
            return casterReady;
        }

        // ------------------------------------------------------------------
        // Materials.

        void RemoveMaterial(const std::string& name)
        {
            void* manager = g_ogre.materialManager();
            if (manager)
                g_ogre.removeResource(manager, name);
        }

        // Points a clone technique at a skinned caster material. The getter
        // must agree with the decoded slot before and after the write.
        bool SetTechniqueCasterMaterial(void* technique, const SharedPtr& material)
        {
            if (g_techniqueCasterOffset == 0 || !material.rep)
                return false;
            auto* slot = reinterpret_cast<SharedPtr*>(static_cast<uint8_t*>(technique) + g_techniqueCasterOffset);
            SharedPtr before;
            g_ogre.getShadowCasterMaterial(technique, &before);
            const bool slotMatches = before.rep == slot->rep && before.info == slot->info;
            Release(before);
            if (!slotMatches)
                return false;
            AddRef(material);
            SharedPtr old = *slot;
            *slot = material;
            Release(old);
            SharedPtr after;
            g_ogre.getShadowCasterMaterial(technique, &after);
            const bool written = after.rep == material.rep;
            Release(after);
            return written;
        }

        // ------------------------------------------------------------------
        // Instanced twins, for gpu_instancing.cpp. Each clone gets a second
        // clone whose eligible passes bind an instanced variant of their
        // skinned programs (a 256-bone palette indexed from a per-instance
        // base). A twin is never bound to an entity: the instancing layer
        // reaches it only through g_twinPasses, at draw time.

        constexpr const char* kTwinRoot = "OpenShim/GpuInst/";
        constexpr int kInstancedMaxBones = 256;

        // Ogre::GpuConstantDefinition (x86): the fields read here.
        struct GpuConstantDefinition
        {
            int constType;
            uint32_t physicalIndex;
            uint32_t logicalIndex;
            uint32_t elementSize;
            uint32_t arraySize;
        };

        struct TwinApi
        {
            FnBool hasFragmentProgram = nullptr;
            FnSharedByValue getFragmentProgramParameters = nullptr;
            FnBool iteratePerLight = nullptr;
            FnBool isTransparent = nullptr;
            FnU16 startLight = nullptr;
            FnU32 lightMask = nullptr;
        };
        TwinApi g_twinApi;
        bool g_twinApiResolved = false;
        bool g_twinApiAvailable = false;

        // Read with the mission's other settings.
        bool g_buildTwins = false;

        struct TwinRecord
        {
            std::string name;
            SharedPtr material;
        };
        // By clone name.
        std::unordered_map<std::string, TwinRecord> g_twins;
        struct TwinPass
        {
            void* pass;
            GpuSkinningTwinLights lights;
        };
        // Clone pass -> twin pass, for every pass that has a usable twin.
        std::unordered_map<const void*, TwinPass> g_twinPasses;
        // Skinned program name -> instanced program name, or empty after a failure.
        std::unordered_map<std::string, std::string> g_instancedPrograms;

        struct TwinStats
        {
            uint32_t twins = 0;
            uint32_t passes = 0;
            uint32_t refusedPasses = 0;
            uint32_t failedTwins = 0;
        };
        TwinStats g_twinStats;

        bool ResolveTwinApi()
        {
            if (g_twinApiResolved)
                return g_twinApiAvailable;
            g_twinApiResolved = true;
            TwinApi& t = g_twinApi;
            t.hasFragmentProgram = ResolveOgreProc<FnBool>("?hasFragmentProgram@Pass@Ogre@@QBE_NXZ");
            t.getFragmentProgramParameters = ResolveOgreProc<FnSharedByValue>(
                "?getFragmentProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            t.iteratePerLight = ResolveOgreProc<FnBool>("?getIteratePerLight@Pass@Ogre@@QBE_NXZ");
            t.isTransparent = ResolveOgreProc<FnBool>("?isTransparent@Pass@Ogre@@QBE_NXZ");
            // Optional: without them every twin compares whole light lists.
            t.startLight = ResolveOgreProc<FnU16>("?getStartLight@Pass@Ogre@@QBEGXZ");
            t.lightMask = ResolveOgreProc<FnU32>("?getLightMask@Pass@Ogre@@QBEIXZ");
            g_twinApiAvailable = t.hasFragmentProgram && t.getFragmentProgramParameters &&
                t.iteratePerLight && t.isTransparent;
            if (!g_twinApiAvailable)
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] twins disabled: OgreMain exports missing");
            return g_twinApiAvailable;
        }

        // Auto constants whose value depends on the renderable being drawn
        // (Ogre's GPV_PER_OBJECT set plus the object-space light and texture
        // projections, which read the world matrix). One instanced draw
        // supplies the leader's value for every instance, so a pass using
        // any of them, other than the palette itself, cannot be instanced.
        bool IsObjectDependentAuto(int type)
        {
            switch (type)
            {
            case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27:
            case 45: case 48: case 50: case 60: case 63: case 65:
            case 79: case 82: case 83: case 86: case 87:
            case 88: case 120: case 131:
                return true;
            default:
                return false;
            }
        }

        // `palette` is the bone palette's physical index, or null when the
        // parameters must have no per-object binding at all.
        bool ParametersInstanceable(void* params, const uint32_t* palette, std::string& detail)
        {
            const uint32_t count = g_ogre.getAutoConstantCount(params);
            for (uint32_t i = 0; i < count; ++i)
            {
                const AutoConstantEntry* entry = g_ogre.getAutoConstantEntry(params, i);
                if (!entry || !IsObjectDependentAuto(entry->paramType))
                    continue;
                if (palette && entry->paramType == kActWorldMatrixArray3x4 && entry->physicalIndex == *palette)
                    continue;
                detail = "auto=" + std::to_string(entry->paramType);
                return false;
            }
            return true;
        }

        // Widens `use` to the light list entries these parameters read
        // (AutoConstantType, OgreGpuProgramParams.h 1.10). Indexed values read
        // entry `data`; arrays read the first `data` entries. Object-space
        // light values never get here: IsObjectDependentAuto refuses them.
        void AccumulateLightUse(void* params, GpuSkinningTwinLights& use)
        {
            const uint32_t count = params ? g_ogre.getAutoConstantCount(params) : 0;
            for (uint32_t i = 0; i < count; ++i)
            {
                const AutoConstantEntry* entry = g_ogre.getAutoConstantEntry(params, i);
                if (!entry)
                    continue;
                uint32_t depth = 0;
                switch (entry->paramType)
                {
                case 38:   // light_count
                    use.count = true;
                    break;
                case 40: case 41: case 42: case 43: case 44: case 46: case 47: case 49:
                case 51: case 52: case 53: case 70: case 71: case 74: case 75: case 77:
                case 84: case 132:
                    depth = entry->data + 1;
                    break;
                case 54: case 55: case 56: case 57: case 58: case 59: case 61: case 62:
                case 64: case 66: case 67: case 72: case 73: case 76: case 85:
                    depth = entry->data;
                    break;
                default:
                    // A type newer than ACT_LIGHT_CUSTOM may be per light.
                    if (entry->paramType > 132)
                    {
                        depth = 0xFFFF;
                        use.count = true;
                    }
                    break;
                }
                if (depth > use.depth)
                    use.depth = static_cast<uint16_t>(depth > 0xFFFF ? 0xFFFF : depth);
            }
        }

        bool PrepareInstancedParameters(void* params, std::string& detail)
        {
            const std::string bones = GpuSkinning::kBonePaletteUniform;
            const auto* palette = params
                ? static_cast<const GpuConstantDefinition*>(g_ogre.findNamedConstant(params, bones, false))
                : nullptr;
            if (!palette || palette->arraySize < static_cast<uint32_t>(kInstancedMaxBones * 3))
            {
                detail = "palette";
                return false;
            }
            // Re-issue the binding so its element count covers the wider array.
            g_ogre.setNamedAutoConstant(params, bones, kActWorldMatrixArray3x4, 0);
            return ParametersInstanceable(params, &palette->physicalIndex, detail);
        }

        // Returns the instanced variant of one of this file's skinned
        // programs, creating and compiling it once; empty on refusal.
        std::string InstancedProgramFor(void* program, std::string& detail)
        {
            void* concrete = ConcreteProgram(program);
            const std::string skinnedName = NameOf(concrete);
            if (!concrete || !StartsWith(skinnedName, kProgramRoot))
            {
                detail = "not a skinned program";
                return {};
            }
            const auto cached = g_instancedPrograms.find(skinnedName);
            if (cached != g_instancedPrograms.end())
            {
                if (cached->second.empty())
                    detail = "program refused earlier";
                return cached->second;
            }
            std::string& slot = g_instancedPrograms[skinnedName];

            const std::string* source = g_ogre.programSource(concrete);
            const GpuSkinning::SkinnedSourceResult instanced = source
                ? GpuSkinning::MakeInstancedSkinnedVertexSource(*source, kInstancedMaxBones)
                : GpuSkinning::SkinnedSourceResult{};
            if (!instanced.ok)
            {
                detail = skinnedName + " " + (source ? instanced.error : std::string("no source"));
                return {};
            }
            const std::string target = GetParameter(concrete, "target");
            const std::string entry = GetParameter(concrete, "entry_point");
            const std::string defines = GetParameter(concrete, "preprocessor_defines");
            const std::string columnMajor = GetParameter(concrete, "column_major_matrices");
            char hash[17];
            sprintf_s(hash, "%016llx", GpuSkinning::HashText(
                instanced.source + "\n" + target + "\n" + entry + "\n" + defines + "\n" + columnMajor));
            const std::string name = std::string(kProgramRoot) + "inst/" + hash;

            void* manager = g_ogre.programManager();
            if (!manager)
            {
                detail = "no program manager";
                return {};
            }
            const std::string& group = *g_ogre.resourceGroup(concrete);
            SharedPtr existing;
            g_ogre.getProgramByName(manager, &existing, name, group);
            if (existing.rep)
            {
                const bool usable = !g_ogre.programCompileError(existing.rep);
                Release(existing);
                if (!usable)
                {
                    detail = "compile error " + name;
                    return {};
                }
                slot = name;
                return name;
            }

            SharedPtr created;
            g_ogre.createProgram(manager, &created, name, group, std::string("hlsl"), kGpuProgramTypeVertex);
            if (!created.rep)
            {
                detail = "create failed " + name;
                return {};
            }
            g_ogre.setProgramSource(created.rep, instanced.source);
            bool parametersSet =
                g_ogre.setParameter(created.rep, std::string("target"), target) &&
                g_ogre.setParameter(created.rep, std::string("entry_point"), entry);
            if (!defines.empty())
                parametersSet = g_ogre.setParameter(created.rep, std::string("preprocessor_defines"), defines) && parametersSet;
            if (!columnMajor.empty())
                parametersSet = g_ogre.setParameter(created.rep, std::string("column_major_matrices"), columnMajor) && parametersSet;
            g_ogre.setProgramSkeletal(created.rep, true);
            if (parametersSet)
                g_ogre.loadResource(created.rep, false);
            const bool compiled = parametersSet && !g_ogre.programCompileError(created.rep);
            Release(created);
            if (!compiled)
            {
                detail = "compile error " + name + " from " + skinnedName;
                return {};
            }
            LogShimA(LogLevel::Info, kComponent, "[GPUINST] program %s from %s", name.c_str(), skinnedName.c_str());
            slot = name;
            return name;
        }

        // Rebinds one twin pass to instanced programs. The pass starts as an
        // exact copy of the clone's.
        bool ConvertTwinPass(void* pass, GpuSkinningTwinLights& lights, std::string& detail)
        {
            if (g_twinApi.iteratePerLight(pass) || g_twinApi.isTransparent(pass))
            {
                detail = "per-light or transparent pass";
                return false;
            }
            if (g_twinApi.hasFragmentProgram(pass))
            {
                SharedPtr fragmentParams;
                g_twinApi.getFragmentProgramParameters(pass, &fragmentParams);
                const bool ok = fragmentParams.rep && ParametersInstanceable(fragmentParams.rep, nullptr, detail);
                Release(fragmentParams);
                if (!ok)
                {
                    detail = "fragment " + detail;
                    return false;
                }
            }
            const SharedPtr* program = g_ogre.getVertexProgram(pass);
            const std::string instanced = InstancedProgramFor(program ? program->rep : nullptr, detail);
            if (instanced.empty())
                return false;

            const std::string casterSkinned = *g_ogre.getShadowCasterVertexProgramName(pass);
            void* manager = g_ogre.programManager();
            SharedPtr casterProgram;
            if (manager && !casterSkinned.empty())
                g_ogre.getProgramByName(manager, &casterProgram, casterSkinned, std::string("Autodetect"));
            const std::string casterInstanced = casterProgram.rep
                ? InstancedProgramFor(casterProgram.rep, detail) : std::string();
            Release(casterProgram);
            if (casterInstanced.empty())
            {
                detail = "caster " + detail;
                return false;
            }

            // As in ConvertPass, rebinding recreates the parameters and copies
            // every matching constant and auto binding across.
            g_ogre.setVertexProgram(pass, instanced, false);
            SharedPtr params;
            g_ogre.getVertexProgramParameters(pass, &params);
            const bool mainReady = PrepareInstancedParameters(params.rep, detail);
            Release(params);
            if (!mainReady)
                return false;

            g_ogre.setShadowCasterVertexProgram(pass, casterInstanced);
            SharedPtr casterParams;
            g_ogre.getShadowCasterVertexProgramParameters(pass, &casterParams);
            const bool casterReady = PrepareInstancedParameters(casterParams.rep, detail);
            if (!casterReady)
            {
                Release(casterParams);
                detail = "caster " + detail;
                return false;
            }

            // Ogre filters the light list itself when a pass starts past the
            // first light or masks lights; batching then keys on all of it.
            if (!g_twinApi.startLight || !g_twinApi.lightMask ||
                g_twinApi.startLight(pass) != 0 || g_twinApi.lightMask(pass) != 0xFFFFFFFFu)
            {
                Release(casterParams);
                return true;
            }
            lights.depth = 0;
            lights.count = false;
            AccumulateLightUse(casterParams.rep, lights);
            Release(casterParams);
            g_ogre.getVertexProgramParameters(pass, &params);
            AccumulateLightUse(params.rep, lights);
            Release(params);
            if (g_twinApi.hasFragmentProgram(pass))
            {
                SharedPtr fragmentParams;
                g_twinApi.getFragmentProgramParameters(pass, &fragmentParams);
                AccumulateLightUse(fragmentParams.rep, lights);
                Release(fragmentParams);
            }
            return true;
        }

        void BuildInstancedTwin(const CloneRecord& record)
        {
            if (!g_buildTwins || !record.clone.rep || g_twins.count(record.cloneName) || !ResolveTwinApi())
                return;
            TwinRecord& twin = g_twins[record.cloneName];
            twin.name = std::string(kTwinRoot) + record.cloneName.substr(std::strlen(kCloneRoot));
            g_ogre.cloneMaterial(record.clone.rep, &twin.material, twin.name, false, std::string());
            if (!twin.material.rep)
            {
                ++g_twinStats.failedTwins;
                LogRejectOnce("twin:" + record.cloneName, Reject::CloneFailed, "instanced twin clone failed");
                return;
            }

            std::vector<std::pair<const void*, TwinPass>> pairs;
            uint16_t supported = 0;
            const uint16_t techniques = g_ogre.getNumTechniques(record.clone.rep);
            for (uint16_t t = 0; t < techniques; ++t)
            {
                void* cloneTechnique = g_ogre.getTechnique(record.clone.rep, t);
                void* twinTechnique = g_ogre.getTechnique(twin.material.rep, t);
                if (!cloneTechnique || !twinTechnique || !g_ogre.techniqueSupported(cloneTechnique))
                    continue;
                ++supported;
                const uint16_t passes = g_ogre.getNumPasses(cloneTechnique);
                if (g_ogre.getNumPasses(twinTechnique) != passes)
                    continue;
                for (uint16_t p = 0; p < passes; ++p)
                {
                    void* clonePass = g_ogre.getPass(cloneTechnique, p);
                    void* twinPass = g_ogre.getPass(twinTechnique, p);
                    std::string detail;
                    TwinPass converted{ twinPass, {} };
                    if (clonePass && twinPass && ConvertTwinPass(twinPass, converted.lights, detail))
                    {
                        pairs.emplace_back(clonePass, converted);
                        continue;
                    }
                    ++g_twinStats.refusedPasses;
                    if (g_loggedRejects.size() <= 256 && g_loggedRejects.insert("twin-pass:" + detail).second)
                    {
                        LogShimA(LogLevel::Info, kComponent, "[GPUINST] pass not instanced: %s pass=%u/%u %s",
                            record.cloneName.c_str(), t, p, detail.c_str());
                    }
                }
            }

            g_ogre.loadResource(twin.material.rep, false);
            if (pairs.empty() || g_ogre.getNumSupportedTechniques(twin.material.rep) != supported)
            {
                if (!pairs.empty())
                {
                    ++g_twinStats.failedTwins;
                    LogShimA(LogLevel::Info, kComponent, "[GPUINST] twin %s lost technique support",
                        twin.name.c_str());
                }
                Release(twin.material);
                RemoveMaterial(twin.name);
                return;
            }
            for (const auto& pair : pairs)
                g_twinPasses[pair.first] = pair.second;
            ++g_twinStats.twins;
            g_twinStats.passes += static_cast<uint32_t>(pairs.size());
        }

        void ReleaseTwins()
        {
            g_twinPasses.clear();
            for (auto& entry : g_twins)
            {
                if (!entry.second.material.rep)
                    continue;
                Release(entry.second.material);
                RemoveMaterial(entry.second.name);
            }
            g_twins.clear();
            g_instancedPrograms.clear();
        }

        // Returns the clone (borrowed) for a source material, or null. With
        // `asCaster` the source is a technique's shadow_caster_material and
        // the clone's passes become skinned casters.
        const CloneRecord* CloneFor(void* source, int weights, int palette, bool asCaster, ConversionError& error)
        {
            const std::string sourceName = NameOf(source);
            const std::string tag = VariantTag(weights, palette);
            const std::string key = (asCaster ? "caster:" : "") + sourceName + "|" + tag;
            const auto cached = g_clones.find(key);
            if (cached != g_clones.end())
            {
                error = cached->second.error;
                return cached->second.clone.rep ? &cached->second : nullptr;
            }

            CloneRecord& record = g_clones[key];
            auto fail = [&](const ConversionError& why) -> const CloneRecord* {
                if (record.clone.rep)
                {
                    Release(record.clone);
                    RemoveMaterial(record.cloneName);
                }
                record.cloneName.clear();
                record.error = why;
                error = why;
                return nullptr;
            };

            record.cloneName = std::string(kCloneRoot) + std::to_string(g_generation) +
                "/" + tag + (asCaster ? "/caster/" : "/") + sourceName;
            void* manager = g_ogre.materialManager();
            if (!manager)
                return fail({ Reject::CloneFailed, "no material manager" });
            g_ogre.cloneMaterial(source, &record.clone, record.cloneName, false, std::string());
            if (!record.clone.rep)
                return fail({ Reject::CloneFailed, record.cloneName });

            uint16_t supported = 0;
            std::unordered_set<uint32_t> selectable;
            const uint16_t techniques = g_ogre.getNumTechniques(record.clone.rep);
            for (uint16_t t = 0; t < techniques; ++t)
            {
                void* technique = g_ogre.getTechnique(record.clone.rep, t);
                if (!technique || !g_ogre.techniqueSupported(technique))
                    continue;
                ++supported;
                // Ogre picks the first supported technique per scheme and LOD;
                // a later one (ISDFC's fixed-function DX9 fallbacks) never
                // draws while that one stays supported, which the
                // stillSupported check below enforces.
                const uint32_t slot = (static_cast<uint32_t>(g_ogre.techniqueSchemeIndex(technique)) << 16) |
                    g_ogre.techniqueLodIndex(technique);
                if (!selectable.insert(slot).second)
                    continue;
                SharedPtr casterMaterial;
                g_ogre.getShadowCasterMaterial(technique, &casterMaterial);
                if (casterMaterial.rep)
                {
                    // Ogre draws the caster material's own first pass as this
                    // technique's shadow caster, so it must skin too.
                    const std::string casterName = NameOf(casterMaterial.rep);
                    if (asCaster)
                    {
                        Release(casterMaterial);
                        return fail({ Reject::ShadowCasterMaterial, "nested " + casterName });
                    }
                    ConversionError why;
                    const CloneRecord* caster = CloneFor(casterMaterial.rep, weights, palette, true, why);
                    Release(casterMaterial);
                    if (!caster)
                    {
                        return fail({ Reject::ShadowCasterMaterial,
                            casterName + " " + RejectName(why.reason) + ":" + why.detail });
                    }
                    if (!SetTechniqueCasterMaterial(technique, caster->clone))
                        return fail({ Reject::ShadowCasterMaterial, casterName + " slot" });
                }

                const uint16_t passes = g_ogre.getNumPasses(technique);
                for (uint16_t p = 0; p < passes; ++p)
                {
                    void* pass = g_ogre.getPass(technique, p);
                    ConversionError why;
                    if (!pass || !ConvertPass(pass, weights, palette, asCaster, why))
                        return fail(why);
                }
            }
            if (supported == 0)
                return fail({ Reject::TechniqueLostSupport, "no supported technique" });

            // Edits marked the clone for recompilation; loading compiles it,
            // and a skinned program that is unsupported drops its technique.
            g_ogre.loadResource(record.clone.rep, false);
            const uint16_t stillSupported = g_ogre.getNumSupportedTechniques(record.clone.rep);
            if (stillSupported != supported)
            {
                return fail({ Reject::TechniqueLostSupport,
                    std::to_string(stillSupported) + "/" + std::to_string(supported) });
            }

            ++g_stats.clones;
            record.error = {};
            error = {};
            // Caster clones (from #538) never had twins; keep it that way.
            if (!asCaster)
                BuildInstancedTwin(record);
            return &record;
        }

        // ------------------------------------------------------------------
        // Entities.

        // Weights per vertex from the sub-entity's skinned vertex data, or 0.
        int WeightsForSubEntity(void* mesh, uint32_t index, ConversionError& error)
        {
            void* vertexData = g_ogre.meshVertexDataByTrackHandle(mesh, static_cast<uint16_t>(index + 1));
            if (!vertexData)
                vertexData = g_ogre.meshVertexDataByTrackHandle(mesh, 0);
            void* declaration = vertexData
                ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(vertexData) + sizeof(void*))
                : nullptr;
            const void* weights = declaration ? g_ogre.findElementBySemantic(declaration, kVesBlendWeights, 0) : nullptr;
            const void* indices = declaration ? g_ogre.findElementBySemantic(declaration, kVesBlendIndices, 0) : nullptr;
            if (!weights || !indices)
            {
                error = { Reject::NoBlendData, "" };
                return 0;
            }
            const int weightType = g_ogre.elementType(weights);
            const int indexType = g_ogre.elementType(indices);
            if (indexType != kVetUByte4 || weightType < kVetFloat1 || weightType > kVetFloat4)
            {
                error = { Reject::BlendFormat,
                    "weights=" + std::to_string(weightType) + " indices=" + std::to_string(indexType) };
                return 0;
            }
            return weightType - kVetFloat1 + 1;
        }

        bool EntityEligible(void* entity, ConversionError& error)
        {
            if (!g_ogre.entityInitialised(entity))
                error = { Reject::NotInitialised, "" };
            else if (!g_ogre.entityHasSkeleton(entity))
                error = { Reject::NoSkeleton, "" };
            else if (g_ogre.entityHasVertexAnimation(entity))
                error = { Reject::VertexAnimation, "" };
            else if (PaletteFor(g_ogre.entityBoneMatrices(entity)) == 0)
                error = { Reject::TooManyBones, std::to_string(g_ogre.entityBoneMatrices(entity)) };
            else if (g_ogre.entitySoftwareRequests(entity) > 0)
                error = { Reject::SoftwareRequests, "" };
            else
                return true;
            return false;
        }

        void SetSubEntityMaterialByName(void* subEntity, const std::string& name)
        {
            void* manager = g_ogre.materialManager();
            SharedPtr material;
            if (manager)
                g_ogre.getMaterialByName(manager, &material, name, std::string("Autodetect"));
            if (material.rep)
                g_ogre.subEntitySetMaterial(subEntity, material);
            Release(material);
        }

        void RevertEntity(void* entity, const EntityRecord& record)
        {
            const uint32_t count = g_ogre.entitySubEntityCount(entity);
            for (uint32_t i = 0; i < count && i < record.originals.size(); ++i)
            {
                void* sub = g_ogre.entitySubEntity(entity, i);
                if (!sub)
                    continue;
                if (NameOf(g_ogre.subEntityMaterial(sub)->rep) != record.originals[i])
                    SetSubEntityMaterialByName(sub, record.originals[i]);
            }
        }

        // Converts every sub-entity not already on its clone. `record` holds
        // the stock names; a sub-entity whose current material is neither its
        // recorded clone nor a clone at all was re-assigned by the game.
        bool ConvertEntity(void* entity, EntityRecord& record, ConversionError& error)
        {
            if (!EntityEligible(entity, error))
                return false;
            const SharedPtr* mesh = g_ogre.entityMesh(entity);
            if (!mesh || !mesh->rep)
            {
                error = { Reject::NoMesh, "" };
                return false;
            }
            const uint32_t count = g_ogre.entitySubEntityCount(entity);
            if (count == 0)
            {
                error = { Reject::NoMesh, "no sub-entities" };
                return false;
            }
            const int palette = PaletteFor(g_ogre.entityBoneMatrices(entity));
            if (record.originals.size() != count)
            {
                record = {};
                record.originals.resize(count);
                record.clones.resize(count);
                record.weights.resize(count);
            }

            struct Pending
            {
                void* sub;
                const CloneRecord* clone;
            };
            std::vector<Pending> pending;
            for (uint32_t i = 0; i < count; ++i)
            {
                void* sub = g_ogre.entitySubEntity(entity, i);
                const SharedPtr* current = sub ? g_ogre.subEntityMaterial(sub) : nullptr;
                if (!current || !current->rep)
                {
                    error = { Reject::NoMesh, "sub-entity without material" };
                    return false;
                }
                const std::string currentName = NameOf(current->rep);
                if (!record.clones[i].empty() && currentName == record.clones[i])
                    continue;
                if (StartsWith(currentName, kCloneRoot))
                {
                    // Another entity's clone, or one from an earlier mission.
                    error = { Reject::CloneFailed, "foreign clone " + currentName };
                    return false;
                }
                const int weights = WeightsForSubEntity(mesh->rep, i, error);
                if (weights == 0)
                    return false;
                const CloneRecord* clone = CloneFor(current->rep, weights, palette, false, error);
                if (!clone)
                {
                    error.detail = currentName + " " + error.detail;
                    return false;
                }
                record.originals[i] = currentName;
                record.clones[i] = clone->cloneName;
                record.weights[i] = weights;
                pending.push_back({ sub, clone });
            }

            for (const Pending& item : pending)
                g_ogre.subEntitySetMaterial(item.sub, item.clone->clone);

            // Ogre decides from the materials now bound; anything short of
            // full hardware animation must not keep a skinned material.
            if (!g_ogre.entityHardwareAnimation(entity))
            {
                RevertEntity(entity, record);
                error = { Reject::HardwareNotEnabled, "" };
                return false;
            }
            return true;
        }

        bool EntityOnClones(void* entity, const EntityRecord& record)
        {
            const uint32_t count = g_ogre.entitySubEntityCount(entity);
            if (count != record.clones.size())
                return false;
            for (uint32_t i = 0; i < count; ++i)
            {
                void* sub = g_ogre.entitySubEntity(entity, i);
                const SharedPtr* current = sub ? g_ogre.subEntityMaterial(sub) : nullptr;
                if (!current || current->rep == nullptr || NameOf(current->rep) != record.clones[i])
                    return false;
            }
            return true;
        }

        void CountReject(void* entity, const ConversionError& error)
        {
            ++g_stats.rejects[static_cast<int>(error.reason)];
            char key[64];
            sprintf_s(key, "entity=%p", entity);
            LogRejectOnce(RejectName(error.reason) + std::string(":") + error.detail, error.reason, key);
        }

        bool IsPointerShaped(const void* candidate)
        {
            const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
            return address >= 0x00010000 && (address % sizeof(void*)) == 0;
        }

        // The same OBJ76 reads as Hooks::CaptureChunkBridgeSnapshot: the
        // direct bridge root at +0xF0, and the legacy owner (+0x8C)'s +0xF0.
        void ReadBridgeRoots(const uint8_t* obj76, void*& directRoot, void*& ownerRoot)
        {
            directRoot = nullptr;
            ownerRoot = nullptr;
            __try
            {
                void* const root = *reinterpret_cast<void* const*>(obj76 + 0xF0);
                if (IsPointerShaped(root))
                    directRoot = root;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            __try
            {
                void* const owner = *reinterpret_cast<void* const*>(obj76 + 0x8C);
                if (IsPointerShaped(owner))
                {
                    void* const root = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(owner) + 0xF0);
                    if (IsPointerShaped(root))
                        ownerRoot = root;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool ReadRootEntity(const void* root, void*& entity)
        {
            __try
            {
                entity = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(root) + 0x94);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                entity = nullptr;
                return false;
            }
        }

        void* ResolveRootEntity(void* root, uint32_t frame, bool convertPass)
        {
            if (!root)
                return nullptr;
            auto [it, inserted] = g_rootProbes.try_emplace(root);
            RootProbe& probe = it->second;
            if (inserted || (!probe.readable && convertPass))
                probe.readable = MemoryAccess::IsReadable(root, 0xA8 + sizeof(void*));
            probe.seenFrame = frame;
            void* entity = nullptr;
            if (probe.readable && !ReadRootEntity(root, entity))
                probe.readable = false;
            return entity;
        }

        void ScanFrame()
        {
            static void* s_objects[Hooks::kGameObjectArenaSlotCapacity];
            const size_t total =
                Hooks::CollectLiveGameObjectsFromArena(s_objects, Hooks::kGameObjectArenaSlotCapacity);
            const uint32_t frame = g_frame;
            const bool convertPass = (g_frame++ % kConvertIntervalFrames) == 0;

            std::unordered_set<void*> live;
            live.reserve(total * 2);
            for (size_t index = 0; index < total; ++index)
            {
                void* obj76 = nullptr;
                if (!Hooks::TryGetGameObjectObj76(s_objects[index], obj76) || !obj76)
                    continue;
                void* directRoot = nullptr;
                void* ownerRoot = nullptr;
                ReadBridgeRoots(static_cast<const uint8_t*>(obj76), directRoot, ownerRoot);
                void* const candidates[] = {
                    ResolveRootEntity(directRoot, frame, convertPass),
                    ResolveRootEntity(ownerRoot, frame, convertPass),
                };
                for (void* entity : candidates)
                {
                    if (!entity || !live.insert(entity).second)
                        continue;

                    const auto converted = g_converted.find(entity);
                    if (converted != g_converted.end())
                    {
                        if (EntityOnClones(entity, converted->second))
                            continue;
                        // The game re-assigned a material since last frame:
                        // convert the newcomer or put the whole entity back.
                        ConversionError error;
                        if (ConvertEntity(entity, converted->second, error))
                        {
                            ++g_stats.reconverted;
                            continue;
                        }
                        RevertEntity(entity, converted->second);
                        ++g_stats.reverted;
                        CountReject(entity, error);
                        g_converted.erase(converted);
                        g_rejected.insert(entity);
                        continue;
                    }
                    if (!convertPass || g_rejected.count(entity) != 0)
                        continue;
                    char rtti[64];
                    const char* className = Hooks::TryGetRttiClassName(entity, rtti, sizeof(rtti));
                    if (!className || std::strcmp(className, ".?AVEntity@Ogre@@") != 0)
                    {
                        g_rejected.insert(entity);
                        continue;
                    }

                    EntityRecord record;
                    ConversionError error;
                    if (ConvertEntity(entity, record, error))
                    {
                        if (g_stats.converted == 0)
                        {
                            LogShimA(LogLevel::Info, kComponent,
                                "[GPUSKIN] first entity on hardware skinning: %s (%zu sub-entities)",
                                record.clones.empty() ? "?" : record.clones[0].c_str(), record.clones.size());
                        }
                        ++g_stats.converted;
                        g_converted.emplace(entity, std::move(record));
                    }
                    else
                    {
                        CountReject(entity, error);
                        g_rejected.insert(entity);
                    }
                }
            }

            // Entities no longer in the arena are not touched again: their
            // pointers may be dangling, and a reused address starts fresh.
            for (auto it = g_converted.begin(); it != g_converted.end();)
                it = live.count(it->first) ? std::next(it) : g_converted.erase(it);
            for (auto it = g_rootProbes.begin(); it != g_rootProbes.end();)
                it = it->second.seenFrame == frame ? std::next(it) : g_rootProbes.erase(it);
            if (convertPass)
            {
                for (auto it = g_rejected.begin(); it != g_rejected.end();)
                    it = live.count(*it) ? std::next(it) : g_rejected.erase(it);
            }
        }

        void Disable(const char* why)
        {
            g_failed.store(true, std::memory_order_release);
            g_active.store(false, std::memory_order_release);
            LogShimA(LogLevel::Error, kComponent,
                "[GPUSKIN] disabled for this session: %s (converted=%u)", why, g_stats.converted);
        }

        bool ScanFrameCxx()
        {
            try
            {
                ScanFrame();
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // No destructible locals: SEH and C++ unwinding do not mix in one frame.
        void ScanFrameGuarded()
        {
            bool ok = false;
            __try
            {
                ok = ScanFrameCxx();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            if (!ok)
                Disable("fault during entity scan");
        }

        // Ogre::FrameListener, laid out to its vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor. Root fires
        // frameStarted from renderOneFrame before any scene rendering.
        class FrameListener
        {
        public:
            virtual bool frameStarted(const void*)
            {
                if (g_active.load(std::memory_order_acquire) && !g_failed.load(std::memory_order_acquire))
                    ScanFrameGuarded();
                return true;
            }
            virtual bool frameRenderingQueued(const void*) { return true; }
            virtual bool frameEnded(const void*) { return true; }
            virtual ~FrameListener() = default;
        };
        FrameListener g_listener;

        void LogMissionSummary()
        {
            std::string rejects;
            for (int i = 0; i < static_cast<int>(Reject::Count); ++i)
            {
                if (g_stats.rejects[i] == 0)
                    continue;
                if (!rejects.empty())
                    rejects += ",";
                rejects += RejectName(static_cast<Reject>(i));
                rejects += "=" + std::to_string(g_stats.rejects[i]);
            }
            LogShimA(LogLevel::Info, kComponent,
                "[GPUSKIN] mission summary: converted=%u reconverted=%u reverted=%u clones=%u programs=%u reused=%u rejects={%s}",
                g_stats.converted, g_stats.reconverted, g_stats.reverted, g_stats.clones,
                g_stats.programs, g_stats.programsReused, rejects.c_str());
            if (g_buildTwins)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[GPUINST] twin summary: twins=%u passes=%u refused_passes=%u failed=%u",
                    g_twinStats.twins, g_twinStats.passes, g_twinStats.refusedPasses, g_twinStats.failedTwins);
            }
        }

        void ReleaseMissionStateCxx()
        {
            try
            {
                // Twins first: the instancing layer must find nothing once
                // the clones they copy are gone.
                ReleaseTwins();
                for (auto& entry : g_clones)
                {
                    if (!entry.second.clone.rep)
                        continue;
                    Release(entry.second.clone);
                    // Live entities keep their own reference to the clone.
                    RemoveMaterial(entry.second.cloneName);
                }
            }
            catch (...)
            {
                Disable("fault releasing mission clones");
            }
            g_clones.clear();
            g_programs.clear();
            g_converted.clear();
            g_rejected.clear();
            g_rootProbes.clear();
        }

        // Default ON. An explicit ini value wins; otherwise a set
        // OPENSHIM_GPU_SKINNING (0 or 1) decides, so A/B scripts keep working.
        bool ReadEnabledSetting()
        {
            bool enabled = true;
            if (TryGetUserConfigBool("Experimental", "GpuSkinning", enabled))
                return enabled;
            char value[16] = {};
            if (GetEnvironmentVariableA("OPENSHIM_GPU_SKINNING", value, sizeof(value)) == 0)
                return true;
            return EnvFlagEnabled("OPENSHIM_GPU_SKINNING");
        }

        bool ReadInstancingSetting()
        {
            bool enabled = false;
            if (TryGetUserConfigBool("Experimental", "GpuInstancing", enabled))
                return enabled;
            return EnvFlagEnabled("OPENSHIM_GPU_INSTANCING");
        }
    }

    bool GpuSkinningInstancingActive()
    {
        return g_buildTwins && g_active.load(std::memory_order_acquire) &&
            !g_failed.load(std::memory_order_acquire);
    }

    void* GpuSkinningInstancedTwinPass(const void* pass, GpuSkinningTwinLights* lights)
    {
        if (!GpuSkinningInstancingActive())
            return nullptr;
        const auto twin = g_twinPasses.find(pass);
        if (twin == g_twinPasses.end())
            return nullptr;
        *lights = twin->second.lights;
        return twin->second.pass;
    }

    uint32_t GpuSkinningGeneration()
    {
        return g_generation;
    }

    void GpuSkinningNotifyMissionRunStateChanged(bool running)
    {
        if (!running)
        {
            g_missionEvaluated = false;
            if (!g_active.exchange(false))
                return;
            LogMissionSummary();
            ReleaseMissionStateCxx();
            return;
        }

        g_missionEvaluated = true;
        if (g_failed.load(std::memory_order_acquire) || !ReadEnabledSetting())
            return;
        if (RenderProfiles::IdentifyActiveRenderSystem() != 1)
        {
            LogShimA(LogLevel::Info, kComponent, "[GPUSKIN] enabled but renderer is not Direct3D 11; CPU skinning kept");
            return;
        }
        if (!ResolveApi())
            return;
        ++g_generation;
        g_stats = {};
        g_buildTwins = ReadInstancingSetting();
        g_twinStats = {};
        g_loggedRejects.clear();
        g_frame = 0;
        g_active.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent, "[GPUSKIN] enabled for mission generation %u", g_generation);
    }

    void GpuSkinningRenderFrameTick()
    {
        // A mission started from the command line is already RUN_STARTED
        // when the transition seam installs, so no start notification comes;
        // the first world render of a mission stands in for it.
        if (!g_missionEvaluated)
            GpuSkinningNotifyMissionRunStateChanged(true);
        if (g_listenerInstalled || !g_active.load(std::memory_order_acquire))
            return;
        g_listenerInstalled = true;
        void* root = g_ogre.rootSingleton ? g_ogre.rootSingleton() : nullptr;
        if (!root)
        {
            Disable("Ogre Root unavailable");
            return;
        }
        g_ogre.addFrameListener(root, &g_listener);
        LogShimA(LogLevel::Info, kComponent, "[GPUSKIN] frame listener installed");
    }
}
