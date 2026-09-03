// walker_cockpit_trace.cpp -- walker first-person cockpit jitter instrument.
//
// Answers one question: walking the chain
//     vehicle world node -> cockpit ("_c") node -> POV bone -> camera
// which link FIRST contains the discontinuity that is visible as cockpit jitter?
//
// Method notes (these are load-bearing; see walker_cockpit_trace.h):
//
//  1. Frame-synchronous capture. Samples are taken inside
//     SceneManager::_renderScene, so every link in the chain is read at the
//     same point of the same frame, and the camera that actually renders the
//     frame is handed to us. The previous iteration of this file sampled from a
//     60Hz worker thread while the render thread was mutating the scene graph,
//     which fabricates discontinuities.
//
//  2. Identity by pointer, not by name. Live SceneManager entity pointers are
//     matched against the fields of the local user GameObject to discover the
//     object -> render bridge -> Ogre::Entity chain at runtime. The previous
//     iteration matched hardcoded "avwalk_c"/"svwalk_c" mesh names and, because
//     it also never resolved its Ogre exports, discovered nothing at all.
//
//  3. Jerk, not delta. Jitter is a per-frame discontinuity. A transform in
//     smooth motion has a large but near-constant frame delta; the jittering
//     one shows a spike in |delta(n) - delta(n-1)|. Reporting raw deltas would
//     rank a fast-but-smooth link above a slow-but-broken one. Each link tracks
//     its own peak jerk and the frame it occurred on, so the summary ranks the
//     chain directly.
//
// Verified live GOG 2.2.301 seams reused here:
//   main + 0x00517AFC        -> GameObject::userObject   (bzr_hooks kHeadlightUserObjectRva 0x00917AFC)
//   0x00920EA0 + 0x08        -> Ogre::SceneManager*      (bzr_hooks.cpp:2042)
//   MSVC RTTI complete-object-locator walk for class identity (pilot_fp_animation_trace.cpp)
//
// Ogre binding rule: OpenShim does not link OgreMain.lib. Virtual methods are
// called through the pinned 1.10 headers (vtable dispatch needs no import);
// non-virtual methods MUST go through exports resolved by decorated name.
// Calling a non-virtual Ogre method through the header is a link error.

#include "walker_cockpit_trace.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <intrin.h>
#include <process.h>

#include <atomic>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

// The pinned BZR Ogre 1.10 headers use the `register` storage class, removed in
// C++17, and this TU is built as C++14 for the same reason
// ogre_animation_profiler.cpp / pilot_fp_animation_trace.cpp are.
#ifndef register
#define OPENSHIM_OGRE_RESTORE_REGISTER
#define register
#endif
#include "OgreBone.h"
#include "OgreCamera.h"
#include "OgreEntity.h"
#include "OgreFrameListener.h"
#include "OgreMesh.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreSkeletonInstance.h"
#ifdef OPENSHIM_OGRE_RESTORE_REGISTER
#undef register
#undef OPENSHIM_OGRE_RESTORE_REGISTER
#endif

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "walker-cockpit";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "WalkerCockpitTrace";
        constexpr char kEnvSwitch[] = "OPENSHIM_WALKER_TRACE";

        constexpr uintptr_t kUserObjectRva = 0x00517AFC;
        constexpr uintptr_t kSceneManagerStructureAddr = 0x00920EA0;
        constexpr size_t kSceneManagerOffset = 0x08;

        // Field-scan windows for object -> bridge -> Entity discovery. Person is
        // +0x0F0 -> bridge, bridge +0x094 -> Entity, but Craft/Walker need not
        // share that layout, so the offsets are discovered and then logged.
        constexpr size_t kObjectScanBytes = 0x400;
        constexpr size_t kBridgeScanBytes = 0x200;

        // Verified GameObject -> render owner -> Ogre::Entity chain, shared by
        // every GameObject subclass including Walker. Taken from
        // bzr_hooks.cpp:2484 (kGameObjectRenderOwnerOffset /
        // kRenderOwnerOgreEntityOffset), itself verified against
        // ExtraUtilities' BZR::GameObject::GetOgreEntity.
        //
        // This is the primary resolver. The pointer scan below is retained only
        // as a diagnostic fallback: matching object fields against the live
        // "Entity" iterator turned out to be unreliable here because the
        // vehicle's entity is not always present in that snapshot, and a blind
        // scan latched a RenderableTileCluster instead.
        constexpr size_t kGameObjectRenderOwnerOffset = 0xF0;
        constexpr size_t kRenderOwnerOgreEntityOffset = 0x94;

        constexpr DWORD kResolveRetryMs = 500;

        // ---- chain links -------------------------------------------------
        enum SlotId
        {
            SLOT_VEH_LOCAL = 0,
            SLOT_VEH_DERIVED,
            SLOT_CKP_LOCAL,
            SLOT_CKP_DERIVED,
            SLOT_POV_LOCAL,
            SLOT_POV_DERIVED,
            SLOT_CAM_DERIVED,
            SLOT_COUNT
        };

        const char* const kSlotNames[SLOT_COUNT] = {
            "veh.local", "veh.derived",
            "ckp.local", "ckp.derived",
            "pov.local", "pov.derived",
            "cam.derived"
        };

        struct Sample
        {
            bool valid;
            float p[3];
            float q[4];
        };

        struct SlotTrack
        {
            bool hasPrev;
            bool hasPrevDelta;
            float prevP[3];
            float prevQ[4];
            float prevDp;
            float prevDq;
            float maxJerkP;
            float maxJerkQ;
            uint64_t maxJerkPFrame;
            uint64_t maxJerkQFrame;
            uint64_t samples;
        };

        // ---- resolved Ogre exports (non-virtual only) --------------------
        using FnEntityGetMesh = const Ogre::MeshPtr& (__thiscall*)(void*);
        using FnEntityHasSkeleton = bool(__thiscall*)(void*);
        using FnEntityGetSkeleton = Ogre::SkeletonInstance* (__thiscall*)(void*);
        using FnNodeGetName = const Ogre::String& (__thiscall*)(void*);
        using FnCameraGetDerivedPosition = const Ogre::Vector3& (__thiscall*)(void*);
        using FnCameraGetDerivedOrientation = const Ogre::Quaternion& (__thiscall*)(void*);
        using FnRootGetSingletonPtr = Ogre::Root* (__cdecl*)();
        using FnRootFrameListener = void(__thiscall*)(void*, void*);
        // Node/SceneNode/Skeleton/MovableObject accessors are virtual, but they
        // are resolved and called through their exported addresses rather than
        // dispatched through the headers' vtables. The pinned 1.10 headers do
        // NOT share vtable indices with the shipped OgreMain.dll: dispatching
        // Node::getParent through the header returned the Entity pointer
        // instead of the parent node, and walking that fabricated chain
        // corrupted the stack into a STATUS_STACK_BUFFER_OVERRUN fail-fast.
        // Calling the exported implementation directly is index-independent.
        using FnNodeGetParent = Ogre::Node* (__thiscall*)(void*);
        using FnNodeVector = const Ogre::Vector3& (__thiscall*)(void*);
        using FnNodeQuat = const Ogre::Quaternion& (__thiscall*)(void*);
        using FnNodeCount = unsigned short(__thiscall*)(void*);
        using FnNodeGetChild = Ogre::Node* (__thiscall*)(void*, unsigned short);
        using FnNodeGetAttached = Ogre::MovableObject* (__thiscall*)(void*, unsigned short);
        using FnSkeletonGetBone = Ogre::Bone* (__thiscall*)(void*, unsigned short);
        using FnMovableParentNode = Ogre::SceneNode* (__thiscall*)(void*);
        using FnMovableGetName = const Ogre::String& (__thiscall*)(void*);

        FnEntityGetMesh g_EntityGetMesh = nullptr;
        FnEntityHasSkeleton g_EntityHasSkeleton = nullptr;
        FnEntityGetSkeleton g_EntityGetSkeleton = nullptr;
        FnNodeGetName g_NodeGetName = nullptr;
        FnCameraGetDerivedPosition g_CameraGetDerivedPosition = nullptr;
        FnCameraGetDerivedOrientation g_CameraGetDerivedOrientation = nullptr;
        FnRootGetSingletonPtr g_RootGetSingletonPtr = nullptr;
        FnRootFrameListener g_RootAddFrameListener = nullptr;
        FnRootFrameListener g_RootRemoveFrameListener = nullptr;
        FnNodeGetParent g_NodeGetParent = nullptr;
        FnNodeVector g_NodeGetPosition = nullptr;
        FnNodeVector g_NodeGetDerivedPosition = nullptr;
        FnNodeQuat g_NodeGetOrientation = nullptr;
        FnNodeQuat g_NodeGetDerivedOrientation = nullptr;
        FnNodeCount g_NodeNumChildren = nullptr;
        FnNodeGetChild g_NodeGetChild = nullptr;
        FnNodeCount g_SceneNodeNumAttached = nullptr;
        FnNodeGetAttached g_SceneNodeGetAttached = nullptr;
        FnNodeCount g_SkeletonGetNumBones = nullptr;
        FnSkeletonGetBone g_SkeletonGetBone = nullptr;
        FnMovableParentNode g_MovableParentSceneNode = nullptr;
        FnMovableGetName g_MovableGetName = nullptr;

        // SceneManager::_renderScene is the capture point. Cameras are NOT in
        // the movable-object collections in Ogre 1.x (they live in the
        // SceneManager's own mCameras map), so enumerating "Camera" movables
        // returned nothing. _renderScene is handed the camera that actually
        // renders the frame, which is both the identity we need and an exactly
        // frame-ordered sample point.
        using FnRenderScene = void(__fastcall*)(void*, void*, Ogre::Camera*, void*, bool);
        void* g_RenderSceneExport = nullptr;
        FnRenderScene g_RealRenderScene = nullptr;
        void** g_RenderSceneSlot = nullptr;

        // Writer attribution for the camera position. Camera::setPosition is
        // exported and called from the executable, so its direct call sites can
        // be redirected to an observer that records the caller RVA. This is what
        // turns "the camera moved on a frame the cockpit did not" into a named
        // writer.
        using FnCamSetPosV = void(__fastcall*)(void*, void*, const Ogre::Vector3*);
        using FnCamSetPos3 = void(__fastcall*)(void*, void*, float, float, float);
        FnCamSetPosV g_RealCamSetPosV = nullptr;
        FnCamSetPos3 g_RealCamSetPos3 = nullptr;
        FnCamSetPosV g_RealNodeSetPosV = nullptr;
        FnCamSetPos3 g_RealNodeSetPos3 = nullptr;
        std::atomic<uintptr_t> g_LastCamWriterRva{ 0 };
        std::atomic<unsigned> g_CamWritesSinceFrame{ 0 };

        struct WriterCount { uintptr_t rva; uint64_t count; };
        WriterCount g_CamWriters[32] = {};
        WriterCount g_VehNodeWriters[32] = {};
        WriterCount g_CkpNodeWriters[32] = {};
        std::mutex g_WriterMutex;


        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ExportsReady{ false };
        std::atomic<bool> g_ListenerInstalled{ false };
        std::atomic<uint64_t> g_Frame{ 0 };

        std::mutex g_Mutex;
        char g_Case[48] = "none";

        // Resolved target identity (guarded by g_Mutex).
        void* g_UserObject = nullptr;
        char g_UserClass[128] = {};
        Ogre::Entity* g_VehEntity = nullptr;
        Ogre::SceneNode* g_VehNode = nullptr;
        Ogre::Entity* g_CkpEntity = nullptr;
        Ogre::SceneNode* g_CkpNode = nullptr;
        Ogre::Node* g_PovBone = nullptr;
        Ogre::Camera* g_Camera = nullptr;
        char g_VehMesh[64] = {};
        char g_CkpMesh[64] = {};
        char g_PovName[64] = {};
        char g_CamName[64] = {};
        uint64_t g_Generation = 0;
        DWORD g_LastResolveAttempt = 0;

        SlotTrack g_Track[SLOT_COUNT] = {};

        // ================= low-level safe access =========================

        bool IsTruthy(const char* v)
        {
            if (!v || !*v)
                return false;
            return !(std::strcmp(v, "0") == 0 || _stricmp(v, "false") == 0 ||
                _stricmp(v, "no") == 0 || _stricmp(v, "off") == 0);
        }

        bool Requested()
        {
            char env[64] = {};
            const DWORD len = GetEnvironmentVariableA(kEnvSwitch, env, sizeof(env));
            if (len > 0 && len < sizeof(env))
                return IsTruthy(env);
            char path[MAX_PATH] = {};
            if (GetModuleFileNameA(nullptr, path, MAX_PATH) > 0)
            {
                char* slash = std::strrchr(path, '\\');
                if (slash)
                    *(slash + 1) = '\0';
                std::string ini = std::string(path) + "openshim.ini";
                // Fail-closed: this is an investigation instrument, not a shipped
                // feature. It must never run on a normal player's machine.
                return GetPrivateProfileIntA(kIniSection, kIniKey, 0, ini.c_str()) != 0;
            }
            return false;
        }

        // No C++ objects requiring unwind may appear in a function using SEH.
        bool SafeReadPtr(const void* address, void** out)
        {
            if (!address || !out)
                return false;
            __try
            {
                *out = *reinterpret_cast<void* const*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool MainModuleContains(const void* p)
        {
            if (!p)
                return false;
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module)
                return false;
            const auto* base = reinterpret_cast<const uint8_t*>(module);
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;
            const auto* q = reinterpret_cast<const uint8_t*>(p);
            return q >= base && q < base + nt->OptionalHeader.SizeOfImage;
        }

        uintptr_t CallerRva(void* returnAddress, bool& outInMain)
        {
            outInMain = MainModuleContains(returnAddress);
            if (!outInMain)
                return 0;
            return reinterpret_cast<uintptr_t>(returnAddress) -
                reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
        }

        void RecordNodeWriterIfTracked(void* node, void* returnAddress)
        {
            bool cockpit = false;
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                if (node == g_CkpNode)
                    cockpit = true;
                else if (node != g_VehNode)
                    return;
            }
            bool inMain = false;
            const uintptr_t rva = CallerRva(returnAddress, inMain);
            std::lock_guard<std::mutex> lock(g_WriterMutex);
            for (auto& entry : (cockpit ? g_CkpNodeWriters : g_VehNodeWriters))
            {
                if (entry.rva == rva) { ++entry.count; return; }
                if (entry.rva == 0) { entry.rva = rva; entry.count = 1; return; }
            }
        }

        void RecordCameraWriter(void* returnAddress)
        {
            bool inMain = false;
            const uintptr_t rva = CallerRva(returnAddress, inMain);
            g_LastCamWriterRva.store(rva, std::memory_order_relaxed);
            g_CamWritesSinceFrame.fetch_add(1, std::memory_order_relaxed);
            std::lock_guard<std::mutex> lock(g_WriterMutex);
            for (auto& entry : g_CamWriters)
            {
                if (entry.rva == rva) { ++entry.count; return; }
                if (entry.rva == 0) { entry.rva = rva; entry.count = 1; return; }
            }
        }

        bool IsReadableRegion(const void* p, size_t bytes)
        {
            if (!p)
                return false;
            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(p, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT)
                return false;
            const DWORD readable = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
                PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
            if ((mbi.Protect & readable) == 0)
                return false;
            if (mbi.Protect & PAGE_GUARD)
                return false;
            const auto* start = reinterpret_cast<const uint8_t*>(mbi.BaseAddress);
            const auto* end = start + mbi.RegionSize;
            const auto* q = reinterpret_cast<const uint8_t*>(p);
            return q + bytes <= end;
        }

        bool LooksLikeOgreObject(const void* object)
        {
            void* vptr = nullptr;
            if (!object || !IsReadableRegion(object, sizeof(void*)))
                return false;
            if (!SafeReadPtr(object, &vptr))
                return false;
            return OgreRuntime::ContainsAddress(vptr);
        }

        // MSVC RTTI complete-object-locator walk (same shape as pilot trace).
        bool TryGetRttiClassName(const void* object, char* buffer, size_t bufferSize)
        {
            if (!object || !buffer || bufferSize == 0)
                return false;
            buffer[0] = '\0';
            __try
            {
                auto** vtable = *reinterpret_cast<void*** const*>(object);
                if (!vtable || !MainModuleContains(vtable))
                    return false;
                const auto* locator = reinterpret_cast<const uint8_t*>(vtable[-1]);
                if (!MainModuleContains(locator) || !MainModuleContains(locator + 15))
                    return false;
                const auto* descriptor = *reinterpret_cast<const uint8_t* const*>(locator + 12);
                if (!MainModuleContains(descriptor) || !MainModuleContains(descriptor + 8))
                    return false;
                const char* decorated = reinterpret_cast<const char*>(descriptor + 8);
                size_t length = 0;
                while (length + 1 < bufferSize)
                {
                    const char* current = decorated + length;
                    if (!MainModuleContains(current))
                        return false;
                    const char ch = *current;
                    buffer[length++] = ch;
                    if (ch == '\0')
                        return true;
                }
                buffer[bufferSize - 1] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                buffer[0] = '\0';
                return false;
            }
        }

        Ogre::SceneManager* SafeGetSceneManager()
        {
            void* structure = nullptr;
            void* manager = nullptr;
            if (!SafeReadPtr(reinterpret_cast<const void*>(kSceneManagerStructureAddr), &structure))
                return nullptr;
            if (!structure)
                return nullptr;
            if (!SafeReadPtr(reinterpret_cast<const uint8_t*>(structure) + kSceneManagerOffset, &manager))
                return nullptr;
            if (!manager || !OgreRuntime::ContainsAddress(*reinterpret_cast<void**>(manager)))
                return nullptr;
            return reinterpret_cast<Ogre::SceneManager*>(manager);
        }

        void* SafeGetUserObject()
        {
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module)
                return nullptr;
            void* object = nullptr;
            if (!SafeReadPtr(reinterpret_cast<const uint8_t*>(module) + kUserObjectRva, &object))
                return nullptr;
            return object;
        }

        void CopyText(char* destination, size_t size, const char* source)
        {
            if (!destination || size == 0)
                return;
            destination[0] = '\0';
            if (!source)
                return;
            strncpy_s(destination, size, source, _TRUNCATE);
        }

        // ================= export resolution =============================

        struct ExportMatch
        {
            std::string name;
            void* address;
        };

        std::vector<ExportMatch> FindExportsContaining(const char* token)
        {
            std::vector<ExportMatch> matches;
            if (!token || !*token)
                return matches;
            HMODULE module = GetModuleHandleA("OgreMain.dll");
            if (!module)
                return matches;
            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return matches;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return matches;
            const IMAGE_DATA_DIRECTORY& directory =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
            if (!directory.VirtualAddress || !directory.Size)
                return matches;
            auto* exports = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(base + directory.VirtualAddress);
            auto* names = reinterpret_cast<DWORD*>(base + exports->AddressOfNames);
            auto* ordinals = reinterpret_cast<WORD*>(base + exports->AddressOfNameOrdinals);
            auto* functions = reinterpret_cast<DWORD*>(base + exports->AddressOfFunctions);
            for (DWORD i = 0; i < exports->NumberOfNames; ++i)
            {
                const char* name = reinterpret_cast<const char*>(base + names[i]);
                if (!name || std::strstr(name, token) == nullptr)
                    continue;
                const WORD ordinal = ordinals[i];
                if (ordinal >= exports->NumberOfFunctions)
                    continue;
                const DWORD functionRva = functions[ordinal];
                if (functionRva >= directory.VirtualAddress &&
                    functionRva < directory.VirtualAddress + directory.Size)
                    continue;
                void* address = base + functionRva;
                if (OgreRuntime::ContainsAddress(address))
                    matches.push_back({ name, address });
            }
            return matches;
        }

        void* FindExport(const char* token, const char* label)
        {
            const auto matches = FindExportsContaining(token);
            if (matches.size() != 1)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[WALKID] export %s ambiguous/missing count=%u token=%s",
                    label, static_cast<unsigned>(matches.size()), token);
                return nullptr;
            }
            LogShimA(LogLevel::Info, kComponent, "[WALKID] resolved %s -> 0x%p", label, matches[0].address);
            return matches[0].address;
        }

        bool ResolveExports()
        {
            if (g_ExportsReady.load(std::memory_order_acquire))
                return true;
            if (!OgreRuntime::IsLoaded())
                return false;

            // Non-virtual members only. Everything else is called through the
            // headers by vtable dispatch. Tokens are the full decorated names
            // where an overload set would otherwise be ambiguous.
            g_EntityGetMesh = reinterpret_cast<FnEntityGetMesh>(
                FindExport("?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ", "Entity::getMesh"));
            g_EntityHasSkeleton = reinterpret_cast<FnEntityHasSkeleton>(
                FindExport("?hasSkeleton@Entity@Ogre@@QBE_NXZ", "Entity::hasSkeleton"));
            g_EntityGetSkeleton = reinterpret_cast<FnEntityGetSkeleton>(
                FindExport("?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ", "Entity::getSkeleton"));
            g_NodeGetName = reinterpret_cast<FnNodeGetName>(
                FindExport("?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
                    "Node::getName"));
            g_CameraGetDerivedPosition = reinterpret_cast<FnCameraGetDerivedPosition>(
                FindExport("?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ", "Camera::getDerivedPosition"));
            g_CameraGetDerivedOrientation = reinterpret_cast<FnCameraGetDerivedOrientation>(
                FindExport("?getDerivedOrientation@Camera@Ogre@@QBEABVQuaternion@2@XZ", "Camera::getDerivedOrientation"));
            g_RootGetSingletonPtr = reinterpret_cast<FnRootGetSingletonPtr>(
                FindExport("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ", "Root::getSingletonPtr"));
            g_RootAddFrameListener = reinterpret_cast<FnRootFrameListener>(
                FindExport("?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z", "Root::addFrameListener"));
            g_RootRemoveFrameListener = reinterpret_cast<FnRootFrameListener>(
                FindExport("?removeFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z", "Root::removeFrameListener"));
            g_NodeGetParent = reinterpret_cast<FnNodeGetParent>(
                FindExport("?getParent@Node@Ogre@@UBEPAV12@XZ", "Node::getParent"));
            g_NodeGetPosition = reinterpret_cast<FnNodeVector>(
                FindExport("?getPosition@Node@Ogre@@UBEABVVector3@2@XZ", "Node::getPosition"));
            g_NodeGetDerivedPosition = reinterpret_cast<FnNodeVector>(
                FindExport("?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ", "Node::_getDerivedPosition"));
            g_NodeGetOrientation = reinterpret_cast<FnNodeQuat>(
                FindExport("?getOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ", "Node::getOrientation"));
            g_NodeGetDerivedOrientation = reinterpret_cast<FnNodeQuat>(
                FindExport("?_getDerivedOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ", "Node::_getDerivedOrientation"));
            g_NodeNumChildren = reinterpret_cast<FnNodeCount>(
                FindExport("?numChildren@Node@Ogre@@UBEGXZ", "Node::numChildren"));
            g_NodeGetChild = reinterpret_cast<FnNodeGetChild>(
                FindExport("?getChild@Node@Ogre@@UBEPAV12@G@Z", "Node::getChild"));
            g_SceneNodeNumAttached = reinterpret_cast<FnNodeCount>(
                FindExport("?numAttachedObjects@SceneNode@Ogre@@UBEGXZ", "SceneNode::numAttachedObjects"));
            g_SceneNodeGetAttached = reinterpret_cast<FnNodeGetAttached>(
                FindExport("?getAttachedObject@SceneNode@Ogre@@UAEPAVMovableObject@2@G@Z", "SceneNode::getAttachedObject"));
            g_SkeletonGetNumBones = reinterpret_cast<FnNodeCount>(
                FindExport("?getNumBones@Skeleton@Ogre@@UBEGXZ", "Skeleton::getNumBones"));
            g_SkeletonGetBone = reinterpret_cast<FnSkeletonGetBone>(
                FindExport("?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z", "Skeleton::getBone"));
            g_MovableParentSceneNode = reinterpret_cast<FnMovableParentNode>(
                FindExport("?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ", "MovableObject::getParentSceneNode"));
            g_MovableGetName = reinterpret_cast<FnMovableGetName>(
                FindExport("?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
                    "MovableObject::getName"));
            g_RenderSceneExport = FindExport(
                "?_renderScene@SceneManager@Ogre@@UAEXPAVCamera@2@PAVViewport@2@_N@Z",
                "SceneManager::_renderScene");

            const bool ready = g_EntityGetMesh && g_EntityHasSkeleton && g_EntityGetSkeleton &&
                g_NodeGetName && g_CameraGetDerivedPosition && g_CameraGetDerivedOrientation &&
                g_RootGetSingletonPtr && g_RootAddFrameListener && g_RootRemoveFrameListener &&
                g_NodeGetParent && g_NodeGetPosition && g_NodeGetDerivedPosition &&
                g_NodeGetOrientation && g_NodeGetDerivedOrientation && g_NodeNumChildren &&
                g_NodeGetChild && g_SceneNodeNumAttached && g_SceneNodeGetAttached &&
                g_SkeletonGetNumBones && g_SkeletonGetBone && g_MovableParentSceneNode &&
                g_MovableGetName && g_RenderSceneExport;
            g_ExportsReady.store(ready, std::memory_order_release);
            if (!ready)
                LogShimA(LogLevel::Warn, kComponent, "[WALKID] required exports unavailable; trace stays fail-closed");
            return ready;
        }

        // ================= Ogre accessors (guarded) ======================

        // MSVC forbids __try in any function that also needs C++ object
        // unwinding, so every guarded Ogre call is isolated in a raw helper and
        // the std::string/vector work happens in the caller.
        const char* SafeMeshNameRaw(Ogre::Entity* entity)
        {
            if (!entity || !g_EntityGetMesh || !LooksLikeOgreObject(entity))
                return nullptr;
            __try
            {
                const Ogre::MeshPtr& mesh = g_EntityGetMesh(entity);
                if (mesh.isNull())
                    return nullptr;
                return mesh->getName().c_str();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        const char* SafeNodeNameRaw(Ogre::Node* node)
        {
            if (!node || !g_NodeGetName || !LooksLikeOgreObject(node))
                return nullptr;
            __try
            {
                return g_NodeGetName(node).c_str();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        const char* SafeMovableNameRaw(Ogre::MovableObject* object)
        {
            if (!object || !g_MovableGetName || !LooksLikeOgreObject(object))
                return nullptr;
            __try
            {
                return g_MovableGetName(object).c_str();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        std::string SafeMeshName(Ogre::Entity* entity)
        {
            const char* raw = SafeMeshNameRaw(entity);
            return raw ? std::string(raw) : std::string();
        }

        std::string SafeNodeName(Ogre::Node* node)
        {
            const char* raw = SafeNodeNameRaw(node);
            return raw ? std::string(raw) : std::string();
        }

        std::string SafeMovableName(Ogre::MovableObject* object)
        {
            const char* raw = SafeMovableNameRaw(object);
            return raw ? std::string(raw) : std::string();
        }

        bool SafeNodeTransforms(Ogre::Node* node, Sample& local, Sample& derived)
        {
            local.valid = false;
            derived.valid = false;
            // A node pointer reached by walking a chain can be arbitrary garbage
            // (a bad parent link once yielded 0x00000001). SEH catches the read
            // fault, but making a virtual call through a junk vptr can corrupt
            // the stack before the fault is raised, which fails fast as
            // STATUS_STACK_BUFFER_OVERRUN and is not catchable. Verify the vptr
            // belongs to OgreMain before dispatching through it.
            if (!LooksLikeOgreObject(node) || !g_NodeGetPosition || !g_NodeGetOrientation ||
                !g_NodeGetDerivedPosition || !g_NodeGetDerivedOrientation)
                return false;
            __try
            {
                const Ogre::Vector3& lp = g_NodeGetPosition(node);
                const Ogre::Quaternion& lq = g_NodeGetOrientation(node);
                local.p[0] = lp.x; local.p[1] = lp.y; local.p[2] = lp.z;
                local.q[0] = lq.x; local.q[1] = lq.y; local.q[2] = lq.z; local.q[3] = lq.w;
                local.valid = true;

                const Ogre::Vector3& dp = g_NodeGetDerivedPosition(node);
                const Ogre::Quaternion& dq = g_NodeGetDerivedOrientation(node);
                derived.p[0] = dp.x; derived.p[1] = dp.y; derived.p[2] = dp.z;
                derived.q[0] = dq.x; derived.q[1] = dq.y; derived.q[2] = dq.z; derived.q[3] = dq.w;
                derived.valid = true;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                local.valid = false;
                derived.valid = false;
                return false;
            }
        }

        bool SafeCameraTransform(Ogre::Camera* camera, Sample& derived)
        {
            derived.valid = false;
            if (!camera || !g_CameraGetDerivedPosition || !g_CameraGetDerivedOrientation)
                return false;
            if (!LooksLikeOgreObject(camera))
                return false;
            __try
            {
                const Ogre::Vector3& p = g_CameraGetDerivedPosition(camera);
                const Ogre::Quaternion& q = g_CameraGetDerivedOrientation(camera);
                derived.p[0] = p.x; derived.p[1] = p.y; derived.p[2] = p.z;
                derived.q[0] = q.x; derived.q[1] = q.y; derived.q[2] = q.z; derived.q[3] = q.w;
                derived.valid = true;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                derived.valid = false;
                return false;
            }
        }

        Ogre::SceneNode* SafeParentSceneNode(Ogre::MovableObject* object)
        {
            if (!g_MovableParentSceneNode || !LooksLikeOgreObject(object))
                return nullptr;
            Ogre::SceneNode* node = nullptr;
            __try
            {
                node = g_MovableParentSceneNode(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                node = nullptr;
            }
            return node;
        }

        Ogre::Node* SafeNodeParent(Ogre::Node* node)
        {
            if (!g_NodeGetParent || !LooksLikeOgreObject(node))
                return nullptr;
            __try
            {
                return g_NodeGetParent(node);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool SafeNodeCounts(Ogre::SceneNode* node, unsigned short* attached, unsigned short* children)
        {
            *attached = 0;
            *children = 0;
            if (!g_SceneNodeNumAttached || !g_NodeNumChildren || !LooksLikeOgreObject(node))
                return false;
            __try
            {
                *attached = g_SceneNodeNumAttached(node);
                *children = g_NodeNumChildren(node);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                *attached = 0;
                *children = 0;
                return false;
            }
        }

        Ogre::MovableObject* SafeAttachedObject(Ogre::SceneNode* node, unsigned short index)
        {
            if (!g_SceneNodeGetAttached || !LooksLikeOgreObject(node))
                return nullptr;
            __try
            {
                return g_SceneNodeGetAttached(node, index);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        Ogre::Node* SafeChildNode(Ogre::SceneNode* node, unsigned short index)
        {
            if (!g_NodeGetChild || !LooksLikeOgreObject(node))
                return nullptr;
            __try
            {
                return g_NodeGetChild(node, index);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool SafeHasSkeleton(Ogre::Entity* entity)
        {
            if (!entity || !g_EntityHasSkeleton || !LooksLikeOgreObject(entity))
                return false;
            __try
            {
                return g_EntityHasSkeleton(entity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        Ogre::SkeletonInstance* SafeGetSkeleton(Ogre::Entity* entity)
        {
            if (!entity || !g_EntityGetSkeleton || !LooksLikeOgreObject(entity))
                return nullptr;
            __try
            {
                return g_EntityGetSkeleton(entity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        unsigned short SafeNumBones(Ogre::SkeletonInstance* skeleton)
        {
            if (!g_SkeletonGetNumBones || !LooksLikeOgreObject(skeleton))
                return 0;
            __try
            {
                return g_SkeletonGetNumBones(skeleton);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        Ogre::Bone* SafeGetBone(Ogre::SkeletonInstance* skeleton, unsigned short index)
        {
            if (!g_SkeletonGetBone || !LooksLikeOgreObject(skeleton))
                return nullptr;
            __try
            {
                return g_SkeletonGetBone(skeleton, index);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        Ogre::Entity* ResolveObjectEntityDirect(const void* object)
        {
            if (!object)
                return nullptr;
            void* owner = nullptr;
            void* entity = nullptr;
            if (!SafeReadPtr(reinterpret_cast<const uint8_t*>(object) + kGameObjectRenderOwnerOffset, &owner))
                return nullptr;
            if (!owner)
                return nullptr;
            if (!SafeReadPtr(reinterpret_cast<const uint8_t*>(owner) + kRenderOwnerOgreEntityOffset, &entity))
                return nullptr;
            if (!LooksLikeOgreObject(entity))
                return nullptr;
            return static_cast<Ogre::Entity*>(entity);
        }

        // ================= identity discovery ============================

        struct EntityRecord
        {
            Ogre::Entity* entity;
            std::string mesh;
            std::string name;
        };

        void CollectEntities(Ogre::SceneManager* manager, std::vector<EntityRecord>& out)
        {
            if (!manager)
                return;
            try
            {
                Ogre::SceneManager::MovableObjectIterator it =
                    manager->getMovableObjectIterator("Entity"); // virtual
                while (it.hasMoreElements())
                {
                    Ogre::MovableObject* movable = it.getNext();
                    if (!movable || !LooksLikeOgreObject(movable))
                        continue;
                    auto* entity = static_cast<Ogre::Entity*>(movable);
                    EntityRecord record;
                    record.entity = entity;
                    record.mesh = SafeMeshName(entity);
                    record.name = SafeMovableName(movable);
                    out.push_back(record);
                }
            }
            catch (...)
            {
            }
        }

        void CollectCameras(Ogre::SceneManager* manager, std::vector<Ogre::Camera*>& out,
            std::vector<std::string>& names)
        {
            if (!manager)
                return;
            try
            {
                Ogre::SceneManager::MovableObjectIterator it =
                    manager->getMovableObjectIterator("Camera"); // virtual
                while (it.hasMoreElements())
                {
                    Ogre::MovableObject* movable = it.getNext();
                    if (!movable || !LooksLikeOgreObject(movable))
                        continue;
                    out.push_back(static_cast<Ogre::Camera*>(movable));
                    names.push_back(SafeMovableName(movable));
                }
            }
            catch (...)
            {
            }
        }

        struct ScanHit
        {
            size_t objectOffset;
            size_t bridgeOffset; // SIZE_MAX when the entity is held directly
            void* entity;
        };

        // Pure-C body: no C++ objects, safe to wrap in SEH.
        bool ScanFieldsForPointer(const uint8_t* block, size_t blockBytes,
            void* const* wanted, size_t wantedCount, size_t* outOffset, void** outHit)
        {
            __try
            {
                for (size_t offset = 0; offset + sizeof(void*) <= blockBytes; offset += sizeof(void*))
                {
                    void* value = *reinterpret_cast<void* const*>(block + offset);
                    if (!value)
                        continue;
                    for (size_t i = 0; i < wantedCount; ++i)
                    {
                        if (wanted[i] == value)
                        {
                            *outOffset = offset;
                            *outHit = value;
                            return true;
                        }
                    }
                }
                return false;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadFieldPointers(const uint8_t* block, size_t blockBytes, void** out, size_t* outCount)
        {
            __try
            {
                size_t count = 0;
                for (size_t offset = 0; offset + sizeof(void*) <= blockBytes; offset += sizeof(void*))
                    out[count++] = *reinterpret_cast<void* const*>(block + offset);
                *outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                *outCount = 0;
                return false;
            }
        }

        // Discovers object -> [bridge] -> Ogre::Entity without hardcoding offsets.
        bool FindOwnedEntity(const void* object, const std::vector<EntityRecord>& entities, ScanHit& hit)
        {
            if (!object || entities.empty())
                return false;
            if (!IsReadableRegion(object, kObjectScanBytes))
                return false;

            std::vector<void*> wanted;
            wanted.reserve(entities.size());
            for (const EntityRecord& record : entities)
                wanted.push_back(record.entity);

            // Direct hold.
            size_t offset = 0;
            void* found = nullptr;
            if (ScanFieldsForPointer(reinterpret_cast<const uint8_t*>(object), kObjectScanBytes,
                wanted.data(), wanted.size(), &offset, &found))
            {
                hit.objectOffset = offset;
                hit.bridgeOffset = static_cast<size_t>(-1);
                hit.entity = found;
                return true;
            }

            // One level of indirection through a render bridge.
            std::vector<void*> fields(kObjectScanBytes / sizeof(void*), nullptr);
            size_t fieldCount = 0;
            if (!ReadFieldPointers(reinterpret_cast<const uint8_t*>(object), kObjectScanBytes,
                fields.data(), &fieldCount))
                return false;

            for (size_t i = 0; i < fieldCount; ++i)
            {
                void* candidate = fields[i];
                if (!candidate || MainModuleContains(candidate))
                    continue;
                if (!IsReadableRegion(candidate, kBridgeScanBytes))
                    continue;
                if (ScanFieldsForPointer(reinterpret_cast<const uint8_t*>(candidate), kBridgeScanBytes,
                    wanted.data(), wanted.size(), &offset, &found))
                {
                    hit.objectOffset = i * sizeof(void*);
                    hit.bridgeOffset = offset;
                    hit.entity = found;
                    return true;
                }
            }
            return false;
        }

        bool NameLooksLikePov(const std::string& name)
        {
            std::string lower = name;
            for (char& c : lower)
                c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            return lower.find("pov") != std::string::npos;
        }

        // Logs the full bone inventory and returns the POV bone when present.
        Ogre::Node* DumpSkeletonAndFindPov(Ogre::Entity* entity, const char* label, char* outName, size_t outNameSize)
        {
            if (!entity)
                return nullptr;
            if (!SafeHasSkeleton(entity))
            {
                LogShimA(LogLevel::Info, kComponent, "[WALKID] %s has no skeleton", label);
                return nullptr;
            }

            Ogre::SkeletonInstance* skeleton = SafeGetSkeleton(entity);
            if (!skeleton)
                return nullptr;

            const unsigned short count = SafeNumBones(skeleton);
            LogShimA(LogLevel::Info, kComponent, "[WALKID] %s skeleton=0x%p bones=%u", label, skeleton, count);

            Ogre::Node* pov = nullptr;
            for (unsigned short i = 0; i < count; ++i)
            {
                Ogre::Bone* bone = SafeGetBone(skeleton, i);
                if (!bone)
                    continue;
                const std::string name = SafeNodeName(bone);
                Ogre::Node* parent = SafeNodeParent(bone);
                const std::string parentName = parent ? SafeNodeName(parent) : std::string("<root>");
                LogShimA(LogLevel::Info, kComponent, "[WALKID] %s bone[%u] name=%s parent=%s ptr=0x%p",
                    label, i, name.c_str(), parentName.c_str(), bone);
                if (!pov && NameLooksLikePov(name))
                {
                    pov = bone;
                    CopyText(outName, outNameSize, name.c_str());
                }
            }
            return pov;
        }

        void DumpNodeChainUpwards(Ogre::Node* node, const char* label)
        {
            int guard = 0;
            Ogre::Node* current = node;
            while (current && guard++ < 16)
            {
                Sample local = {};
                Sample derived = {};
                SafeNodeTransforms(current, local, derived);
                const std::string name = SafeNodeName(current);
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKID] %s chain[%d] node=0x%p name=%s local=(%.4f,%.4f,%.4f) derived=(%.4f,%.4f,%.4f) dq=(%.4f,%.4f,%.4f,%.4f)",
                    label, guard - 1, current, name.c_str(),
                    local.p[0], local.p[1], local.p[2],
                    derived.p[0], derived.p[1], derived.p[2],
                    derived.q[0], derived.q[1], derived.q[2], derived.q[3]);
                current = SafeNodeParent(current);
            }
        }

        // Walks the node subtree and reports every attached entity. This is how
        // the cockpit "_c" entity is found -- as an actual runtime child of the
        // vehicle node, rather than by assuming a mesh naming convention.
        // Budget for one identity dump. The live scene carries 400+ entities and
        // an unbudgeted walk would bury the per-frame capture in the same log.
        int g_SubtreeBudget = 0;

        void DumpSubtree(Ogre::SceneNode* node, int depth, int maxDepth, Ogre::Entity* exclude,
            Ogre::Entity** outCockpit, Ogre::SceneNode** outCockpitNode)
        {
            if (!node || depth > maxDepth || g_SubtreeBudget <= 0)
                return;
            --g_SubtreeBudget;
            unsigned short attached = 0;
            unsigned short children = 0;
            if (!SafeNodeCounts(node, &attached, &children))
                return;

            const std::string nodeName = SafeNodeName(node);
            Sample local = {};
            Sample derived = {};
            SafeNodeTransforms(node, local, derived);
            LogShimA(LogLevel::Info, kComponent,
                "[WALKID] subtree d=%d node=0x%p name=%s attached=%u children=%u local=(%.4f,%.4f,%.4f) derived=(%.4f,%.4f,%.4f)",
                depth, node, nodeName.c_str(), attached, children,
                local.p[0], local.p[1], local.p[2],
                derived.p[0], derived.p[1], derived.p[2]);

            for (unsigned short i = 0; i < attached; ++i)
            {
                Ogre::MovableObject* movable = SafeAttachedObject(node, i);
                if (!movable)
                    continue;
                const std::string movableName = SafeMovableName(movable);
                std::string mesh = SafeMeshName(static_cast<Ogre::Entity*>(movable));
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKID] subtree d=%d   attached=0x%p name=%s mesh=%s",
                    depth, movable, movableName.c_str(), mesh.c_str());
                // A distinct skinned entity under the vehicle node that is not
                // the vehicle entity itself is the cockpit candidate.
                if (outCockpit && !*outCockpit && movable != exclude && !mesh.empty())
                {
                    *outCockpit = static_cast<Ogre::Entity*>(movable);
                    if (outCockpitNode)
                        *outCockpitNode = node;
                }
            }

            for (unsigned short i = 0; i < children; ++i)
            {
                Ogre::Node* child = SafeChildNode(node, i);
                if (child)
                    DumpSubtree(static_cast<Ogre::SceneNode*>(child), depth + 1, maxDepth,
                        exclude, outCockpit, outCockpitNode);
            }
        }

        // Established empirically, not assumed. Enumerating the live scene while
        // cycling possession showed:
        //   - every walker's "<veh>_c" cockpit entity exists for the whole
        //     mission, but sits DETACHED (parent scene node == null);
        //   - exactly one cockpit entity at a time is attached, and it is the
        //     possessed vehicle's;
        //   - the cockpit node is NOT a child of the vehicle node -- it is a
        //     separate first-person cockpit node that entities are swapped onto
        //     (0x1DB9D478 in the reference capture).
        // That is why walking the vehicle node's subtree found no cockpit. The
        // attachment state is therefore the reliable discriminator, and the
        // "<veh>_c" name is only used to prefer the expected match.
        Ogre::Entity* FindCockpitEntity(const std::vector<EntityRecord>& entities,
            const std::string& vehicleMesh, Ogre::SceneNode** outNode)
        {
            if (outNode)
                *outNode = nullptr;

            std::string expected;
            const size_t dot = vehicleMesh.find_last_of('.');
            if (dot != std::string::npos)
                expected = vehicleMesh.substr(0, dot) + "_c" + vehicleMesh.substr(dot);

            Ogre::Entity* fallback = nullptr;
            Ogre::SceneNode* fallbackNode = nullptr;
            for (const EntityRecord& record : entities)
            {
                if (record.mesh.size() < 8)
                    continue;
                const bool cockpitLike =
                    record.mesh.find("_c.mesh") != std::string::npos;
                if (!cockpitLike)
                    continue;
                Ogre::SceneNode* node = SafeParentSceneNode(record.entity);
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKID] cockpit candidate entity=0x%p mesh=%s node=0x%p attached=%u expected=%u",
                    record.entity, record.mesh.c_str(), node, node ? 1u : 0u,
                    (!expected.empty() && record.mesh == expected) ? 1u : 0u);
                if (!node)
                    continue;
                if (!expected.empty() && record.mesh == expected)
                {
                    if (outNode)
                        *outNode = node;
                    return record.entity;
                }
                if (!fallback)
                {
                    fallback = record.entity;
                    fallbackNode = node;
                }
            }
            if (fallback && outNode)
                *outNode = fallbackNode;
            return fallback;
        }

        void ResetTracking()
        {
            std::memset(g_Track, 0, sizeof(g_Track));
        }

        // Full identity resolution for the currently possessed object.
        bool ResolveIdentity()
        {
            void* userObject = SafeGetUserObject();
            if (!userObject)
                return false;

            Ogre::SceneManager* manager = SafeGetSceneManager();
            if (!manager)
                return false;

            char className[128] = {};
            TryGetRttiClassName(userObject, className, sizeof(className));

            std::vector<EntityRecord> entities;
            CollectEntities(manager, entities);
            if (entities.empty())
                return false;

            // Match against skinned entities first. A raw pointer scan over a
            // 1KB object window will otherwise latch the first coincidental
            // pointer -- the first attempt matched a RenderableTileCluster
            // terrain entity and then walked a garbage node chain into a
            // fail-fast. Vehicles and their cockpits are skinned; terrain
            // clusters, billboards and effects are not, so requiring a skeleton
            // removes essentially every false positive. The unfiltered pass is
            // kept as a fallback so an unskinned target still resolves rather
            // than silently reporting nothing.
            ScanHit hit = {};
            const char* resolvedVia = "direct";
            Ogre::Entity* direct = ResolveObjectEntityDirect(userObject);
            if (direct)
            {
                hit.objectOffset = kGameObjectRenderOwnerOffset;
                hit.bridgeOffset = kRenderOwnerOgreEntityOffset;
                hit.entity = direct;
            }
            else
            {
                resolvedVia = "scan";
                std::vector<EntityRecord> skinned;
                for (const EntityRecord& record : entities)
                {
                    if (SafeHasSkeleton(record.entity))
                        skinned.push_back(record);
                }
                if (!FindOwnedEntity(userObject, skinned, hit) &&
                    !FindOwnedEntity(userObject, entities, hit))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "[WALKID] user object 0x%p class=%s: +0x%X->+0x%X chain empty and no scan match among %u live (%u skinned)",
                        userObject, className,
                        static_cast<unsigned>(kGameObjectRenderOwnerOffset),
                        static_cast<unsigned>(kRenderOwnerOgreEntityOffset),
                        static_cast<unsigned>(entities.size()),
                        static_cast<unsigned>(skinned.size()));
                    return false;
                }
            }

            if (!LooksLikeOgreObject(hit.entity) ||
                !LooksLikeOgreObject(SafeParentSceneNode(static_cast<Ogre::Entity*>(hit.entity))))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[WALKID] rejected match entity=0x%p via=%s (no valid parent scene node)",
                    hit.entity, resolvedVia);
                return false;
            }

            auto* vehicleEntity = static_cast<Ogre::Entity*>(hit.entity);
            const std::string vehicleMesh = SafeMeshName(vehicleEntity);
            Ogre::SceneNode* vehicleNode = SafeParentSceneNode(vehicleEntity);

            LogShimA(LogLevel::Info, kComponent,
                "[WALKID] ===== identity gen=%llu case=%s =====",
                static_cast<unsigned long long>(g_Generation + 1), g_Case);
            LogShimA(LogLevel::Info, kComponent,
                "[WALKID] userObject=0x%p class=%s -> entity=0x%p mesh=%s via objOff=0x%X bridgeOff=%s node=0x%p via=%s",
                userObject, className, vehicleEntity, vehicleMesh.c_str(),
                static_cast<unsigned>(hit.objectOffset),
                hit.bridgeOffset == static_cast<size_t>(-1) ? "direct" : "set",
                vehicleNode, resolvedVia);
            if (hit.bridgeOffset != static_cast<size_t>(-1))
                LogShimA(LogLevel::Info, kComponent, "[WALKID]   bridge chain: object+0x%X -> bridge+0x%X -> Entity",
                    static_cast<unsigned>(hit.objectOffset), static_cast<unsigned>(hit.bridgeOffset));

            DumpNodeChainUpwards(vehicleNode, "veh");

            Ogre::Entity* cockpitEntity = nullptr;
            Ogre::SceneNode* cockpitNode = nullptr;
            g_SubtreeBudget = 64;
            DumpSubtree(vehicleNode, 0, 4, vehicleEntity, &cockpitEntity, &cockpitNode);

            // The cockpit lives on its own node, so the subtree walk will not
            // find it; resolve it from the live entity set by attachment state.
            if (!cockpitEntity)
            {
                cockpitEntity = FindCockpitEntity(entities, vehicleMesh, &cockpitNode);
                if (cockpitEntity)
                {
                    LogShimA(LogLevel::Info, kComponent,
                        "[WALKID] cockpit resolved entity=0x%p mesh=%s node=0x%p (separate FP cockpit node)",
                        cockpitEntity, SafeMeshName(cockpitEntity).c_str(), cockpitNode);
                    DumpNodeChainUpwards(cockpitNode, "ckp");
                }
            }

            // The cockpit may not be parented under the vehicle node at all. If
            // the subtree walk found nothing, fall back to the live entity list
            // and report every skinned entity so the real relationship is
            // visible rather than assumed.
            char povName[64] = {};
            Ogre::Node* pov = DumpSkeletonAndFindPov(vehicleEntity, "veh", povName, sizeof(povName));
            char cockpitPovName[64] = {};
            if (cockpitEntity)
            {
                Ogre::Node* cockpitPov = DumpSkeletonAndFindPov(cockpitEntity, "ckp", cockpitPovName, sizeof(cockpitPovName));
                if (cockpitPov)
                {
                    pov = cockpitPov;
                    CopyText(povName, sizeof(povName), cockpitPovName);
                }
            }

            std::vector<Ogre::Camera*> cameras;
            std::vector<std::string> cameraNames;
            CollectCameras(manager, cameras, cameraNames);
            Ogre::Camera* camera = cameras.empty() ? nullptr : cameras[0];
            std::string cameraName = cameraNames.empty() ? std::string() : cameraNames[0];
            for (size_t i = 0; i < cameras.size(); ++i)
            {
                Sample derived = {};
                SafeCameraTransform(cameras[i], derived);
                Ogre::SceneNode* node = SafeParentSceneNode(cameras[i]);
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKID] camera[%u]=0x%p name=%s node=0x%p derived=(%.4f,%.4f,%.4f)",
                    static_cast<unsigned>(i), cameras[i], cameraNames[i].c_str(), node,
                    derived.p[0], derived.p[1], derived.p[2]);
            }

            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                g_UserObject = userObject;
                CopyText(g_UserClass, sizeof(g_UserClass), className);
                g_VehEntity = vehicleEntity;
                g_VehNode = vehicleNode;
                g_CkpEntity = cockpitEntity;
                g_CkpNode = cockpitNode ? cockpitNode : SafeParentSceneNode(cockpitEntity);
                g_PovBone = pov;
                g_Camera = camera;
                CopyText(g_VehMesh, sizeof(g_VehMesh), vehicleMesh.c_str());
                CopyText(g_CkpMesh, sizeof(g_CkpMesh), cockpitEntity ? SafeMeshName(cockpitEntity).c_str() : "");
                CopyText(g_PovName, sizeof(g_PovName), povName);
                CopyText(g_CamName, sizeof(g_CamName), cameraName.c_str());
                ++g_Generation;
                ResetTracking();
            }

            LogShimA(LogLevel::Info, kComponent,
                "[WALKID] RESOLVED veh=%s ckp=%s pov=%s cam=%s",
                vehicleMesh.c_str(),
                cockpitEntity ? SafeMeshName(cockpitEntity).c_str() : "<none>",
                povName[0] ? povName : "<none>",
                cameraName.empty() ? "<none>" : cameraName.c_str());
            return true;
        }

        // ================= per-frame capture =============================

        float PosDistance(const float a[3], const float b[3])
        {
            const float dx = a[0] - b[0];
            const float dy = a[1] - b[1];
            const float dz = a[2] - b[2];
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }

        float QuatAngle(const float a[4], const float b[4])
        {
            float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
            dot = std::fabs(dot);
            if (dot > 1.0f)
                dot = 1.0f;
            return 2.0f * std::acos(dot);
        }

        void UpdateSlot(SlotId slot, const Sample& sample, uint64_t frame, float& outDp, float& outDq,
            float& outJerkP, float& outJerkQ)
        {
            outDp = 0.0f;
            outDq = 0.0f;
            outJerkP = 0.0f;
            outJerkQ = 0.0f;
            if (!sample.valid)
                return;
            SlotTrack& track = g_Track[slot];
            ++track.samples;
            if (track.hasPrev)
            {
                outDp = PosDistance(sample.p, track.prevP);
                outDq = QuatAngle(sample.q, track.prevQ);
                if (track.hasPrevDelta)
                {
                    outJerkP = std::fabs(outDp - track.prevDp);
                    outJerkQ = std::fabs(outDq - track.prevDq);
                    if (outJerkP > track.maxJerkP)
                    {
                        track.maxJerkP = outJerkP;
                        track.maxJerkPFrame = frame;
                    }
                    if (outJerkQ > track.maxJerkQ)
                    {
                        track.maxJerkQ = outJerkQ;
                        track.maxJerkQFrame = frame;
                    }
                }
                track.prevDp = outDp;
                track.prevDq = outDq;
                track.hasPrevDelta = true;
            }
            std::memcpy(track.prevP, sample.p, sizeof(track.prevP));
            std::memcpy(track.prevQ, sample.q, sizeof(track.prevQ));
            track.hasPrev = true;
        }

        double FrameDeltaSeconds()
        {
            static LARGE_INTEGER frequency = {};
            static LARGE_INTEGER previous = {};
            if (frequency.QuadPart == 0)
                QueryPerformanceFrequency(&frequency);
            LARGE_INTEGER now = {};
            QueryPerformanceCounter(&now);
            double dt = 0.0;
            if (previous.QuadPart != 0 && frequency.QuadPart != 0)
                dt = static_cast<double>(now.QuadPart - previous.QuadPart) /
                    static_cast<double>(frequency.QuadPart);
            previous = now;
            return dt;
        }

        void OnFrame(Ogre::Camera* frameCamera)
        {
            if (!g_Enabled.load(std::memory_order_acquire))
                return;
            const float timeSinceLastFrame = static_cast<float>(FrameDeltaSeconds());

            void* userObject = SafeGetUserObject();
            bool needResolve = false;
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                needResolve = (!g_VehEntity || userObject != g_UserObject);
            }
            if (needResolve)
            {
                const DWORD now = GetTickCount();
                if (now - g_LastResolveAttempt >= kResolveRetryMs)
                {
                    g_LastResolveAttempt = now;
                    ResolveIdentity();
                }
                return;
            }

            Ogre::SceneNode* vehicleNode = nullptr;
            Ogre::SceneNode* cockpitNode = nullptr;
            Ogre::Node* pov = nullptr;
            Ogre::Camera* camera = nullptr;
            char vehicleMesh[64] = {};
            char currentCase[48] = {};
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                vehicleNode = g_VehNode;
                cockpitNode = g_CkpNode;
                pov = g_PovBone;
                g_Camera = frameCamera;
                camera = frameCamera;
                CopyText(vehicleMesh, sizeof(vehicleMesh), g_VehMesh);
                CopyText(currentCase, sizeof(currentCase), g_Case);
            }

            Sample samples[SLOT_COUNT] = {};
            Sample local = {};
            Sample derived = {};

            if (SafeNodeTransforms(vehicleNode, local, derived))
            {
                samples[SLOT_VEH_LOCAL] = local;
                samples[SLOT_VEH_DERIVED] = derived;
            }
            if (SafeNodeTransforms(cockpitNode, local, derived))
            {
                samples[SLOT_CKP_LOCAL] = local;
                samples[SLOT_CKP_DERIVED] = derived;
            }
            if (SafeNodeTransforms(pov, local, derived))
            {
                samples[SLOT_POV_LOCAL] = local;
                samples[SLOT_POV_DERIVED] = derived;
            }
            SafeCameraTransform(camera, samples[SLOT_CAM_DERIVED]);

            const uint64_t frame = g_Frame.fetch_add(1);

            float dp[SLOT_COUNT] = {};
            float dq[SLOT_COUNT] = {};
            float jp[SLOT_COUNT] = {};
            float jq[SLOT_COUNT] = {};
            for (int i = 0; i < SLOT_COUNT; ++i)
                UpdateSlot(static_cast<SlotId>(i), samples[i], frame, dp[i], dq[i], jp[i], jq[i]);

            // _renderScene runs once per camera per viewport, so shadow and RTT
            // passes appear here too and a naive frame-to-frame delta would mix
            // camera streams and manufacture jerk. The camera pointer is logged
            // so deltas can be recomputed per stream; full orientations are
            // logged for the same reason.
            char cameraName[64] = {};
            CopyText(cameraName, sizeof(cameraName),
                SafeMovableName(static_cast<Ogre::MovableObject*>(frameCamera)).c_str());

            // One line per frame per link. At ~60fps a 20s case is ~1200 lines,
            // which is what resolving a single-frame discontinuity requires.
            LogShimA(LogLevel::Info, kComponent,
                "[WALKF] f=%llu dt=%.5f case=%s veh=%s "
                "vehD=(%.4f,%.4f,%.4f) dP=%.5f dQ=%.5f jP=%.5f jQ=%.5f | "
                "ckpL=(%.4f,%.4f,%.4f) dP=%.5f jP=%.5f | "
                "ckpD=(%.4f,%.4f,%.4f) dP=%.5f dQ=%.5f jP=%.5f jQ=%.5f | "
                "povL=(%.4f,%.4f,%.4f) dP=%.5f jP=%.5f | "
                "povD=(%.4f,%.4f,%.4f) dP=%.5f dQ=%.5f jP=%.5f jQ=%.5f | "
                "camD=(%.4f,%.4f,%.4f) dP=%.5f dQ=%.5f jP=%.5f jQ=%.5f | v=%u%u%u%u%u%u%u "
                "camPtr=0x%p camName=%s vehQ=(%.5f,%.5f,%.5f,%.5f) ckpQ=(%.5f,%.5f,%.5f,%.5f) camQ=(%.5f,%.5f,%.5f,%.5f) "
                "camWriter=0x%08X camWrites=%u",
                static_cast<unsigned long long>(frame), timeSinceLastFrame, currentCase, vehicleMesh,
                samples[SLOT_VEH_DERIVED].p[0], samples[SLOT_VEH_DERIVED].p[1], samples[SLOT_VEH_DERIVED].p[2],
                dp[SLOT_VEH_DERIVED], dq[SLOT_VEH_DERIVED], jp[SLOT_VEH_DERIVED], jq[SLOT_VEH_DERIVED],
                samples[SLOT_CKP_LOCAL].p[0], samples[SLOT_CKP_LOCAL].p[1], samples[SLOT_CKP_LOCAL].p[2],
                dp[SLOT_CKP_LOCAL], jp[SLOT_CKP_LOCAL],
                samples[SLOT_CKP_DERIVED].p[0], samples[SLOT_CKP_DERIVED].p[1], samples[SLOT_CKP_DERIVED].p[2],
                dp[SLOT_CKP_DERIVED], dq[SLOT_CKP_DERIVED], jp[SLOT_CKP_DERIVED], jq[SLOT_CKP_DERIVED],
                samples[SLOT_POV_LOCAL].p[0], samples[SLOT_POV_LOCAL].p[1], samples[SLOT_POV_LOCAL].p[2],
                dp[SLOT_POV_LOCAL], jp[SLOT_POV_LOCAL],
                samples[SLOT_POV_DERIVED].p[0], samples[SLOT_POV_DERIVED].p[1], samples[SLOT_POV_DERIVED].p[2],
                dp[SLOT_POV_DERIVED], dq[SLOT_POV_DERIVED], jp[SLOT_POV_DERIVED], jq[SLOT_POV_DERIVED],
                samples[SLOT_CAM_DERIVED].p[0], samples[SLOT_CAM_DERIVED].p[1], samples[SLOT_CAM_DERIVED].p[2],
                dp[SLOT_CAM_DERIVED], dq[SLOT_CAM_DERIVED], jp[SLOT_CAM_DERIVED], jq[SLOT_CAM_DERIVED],
                samples[0].valid ? 1u : 0u, samples[1].valid ? 1u : 0u, samples[2].valid ? 1u : 0u,
                samples[3].valid ? 1u : 0u, samples[4].valid ? 1u : 0u, samples[5].valid ? 1u : 0u,
                samples[6].valid ? 1u : 0u,
                frameCamera, cameraName,
                samples[SLOT_VEH_DERIVED].q[0], samples[SLOT_VEH_DERIVED].q[1],
                samples[SLOT_VEH_DERIVED].q[2], samples[SLOT_VEH_DERIVED].q[3],
                samples[SLOT_CKP_DERIVED].q[0], samples[SLOT_CKP_DERIVED].q[1],
                samples[SLOT_CKP_DERIVED].q[2], samples[SLOT_CKP_DERIVED].q[3],
                samples[SLOT_CAM_DERIVED].q[0], samples[SLOT_CAM_DERIVED].q[1],
                samples[SLOT_CAM_DERIVED].q[2], samples[SLOT_CAM_DERIVED].q[3],
                static_cast<unsigned>(g_LastCamWriterRva.load(std::memory_order_relaxed)),
                g_CamWritesSinceFrame.exchange(0, std::memory_order_relaxed));
        }

        void LogSummary(const char* reason)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            LogShimA(LogLevel::Info, kComponent,
                "[WALKSUM] ===== %s case=%s veh=%s ckp=%s pov=%s cam=%s frames=%llu =====",
                reason, g_Case, g_VehMesh, g_CkpMesh[0] ? g_CkpMesh : "<none>",
                g_PovName[0] ? g_PovName : "<none>", g_CamName[0] ? g_CamName : "<none>",
                static_cast<unsigned long long>(g_Frame.load()));
            {
                std::lock_guard<std::mutex> writerLock(g_WriterMutex);
                struct WriterTable { const char* label; const WriterCount* table; };
                const WriterTable tables[] = {
                    { "cameraWriter", g_CamWriters },
                    { "vehNodeWriter", g_VehNodeWriters },
                    { "ckpNodeWriter", g_CkpNodeWriters },
                };
                for (const WriterTable& t : tables)
                {
                    for (size_t i = 0; i < 32; ++i)
                    {
                        if (t.table[i].rva == 0)
                            break;
                        LogShimA(LogLevel::Info, kComponent,
                            "[WALKSUM] %s callerRVA=0x%08X calls=%llu",
                            t.label, static_cast<unsigned>(t.table[i].rva),
                            static_cast<unsigned long long>(t.table[i].count));
                    }
                }
            }
            for (int i = 0; i < SLOT_COUNT; ++i)
            {
                const SlotTrack& track = g_Track[i];
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKSUM] slot=%-12s samples=%llu maxJerkPos=%.6f @f=%llu maxJerkRot=%.6f @f=%llu",
                    kSlotNames[i], static_cast<unsigned long long>(track.samples),
                    track.maxJerkP, static_cast<unsigned long long>(track.maxJerkPFrame),
                    track.maxJerkQ, static_cast<unsigned long long>(track.maxJerkQFrame));
            }
        }

        // Frame capture is installed by replacing SceneManager::_renderScene in
        // the live SceneManager's vtable. The slot index is found by scanning
        // the vtable for the exported implementation address rather than being
        // hardcoded, because the pinned Ogre headers do not share vtable
        // indices with the shipped OgreMain.dll (dispatching Node::getParent
        // through the header returned an Entity pointer).
        void __fastcall HookRenderScene(void* self, void* edx, Ogre::Camera* camera,
            void* viewport, bool includeOverlays)
        {
            OnFrame(camera);
            if (g_RealRenderScene)
                g_RealRenderScene(self, edx, camera, viewport, includeOverlays);
        }

        bool PatchVtableSlot(void* instance, void* target, void* replacement,
            void*** outSlot, void** outOriginal)
        {
            if (!instance || !target || !replacement)
                return false;
            void** vtable = nullptr;
            if (!SafeReadPtr(instance, reinterpret_cast<void**>(&vtable)))
                return false;
            if (!vtable || !OgreRuntime::ContainsAddress(vtable))
                return false;
            for (size_t i = 0; i < 256; ++i)
            {
                void* entry = nullptr;
                if (!SafeReadPtr(&vtable[i], &entry))
                    break;
                if (!entry || !OgreRuntime::ContainsAddress(entry))
                    continue;
                if (entry != target)
                    continue;
                DWORD oldProtect = 0;
                if (!VirtualProtect(&vtable[i], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                    return false;
                vtable[i] = replacement;
                DWORD ignored = 0;
                VirtualProtect(&vtable[i], sizeof(void*), oldProtect, &ignored);
                FlushInstructionCache(GetCurrentProcess(), &vtable[i], sizeof(void*));
                *outSlot = &vtable[i];
                *outOriginal = target;
                LogShimA(LogLevel::Info, kComponent,
                    "[WALKID] _renderScene hooked at vtable slot %u (0x%p)", static_cast<unsigned>(i), &vtable[i]);
                return true;
            }
            LogShimA(LogLevel::Warn, kComponent,
                "[WALKID] _renderScene export 0x%p not present in SceneManager vtable; capture unavailable", target);
            return false;
        }

        void __fastcall HookNodeSetPosV(void* self, void* edx, const Ogre::Vector3* position)
        {
            RecordNodeWriterIfTracked(self, _ReturnAddress());
            if (g_RealNodeSetPosV)
                g_RealNodeSetPosV(self, edx, position);
        }

        void __fastcall HookNodeSetPos3(void* self, void* edx, float x, float y, float z)
        {
            RecordNodeWriterIfTracked(self, _ReturnAddress());
            if (g_RealNodeSetPos3)
                g_RealNodeSetPos3(self, edx, x, y, z);
        }

        void __fastcall HookCamSetPosV(void* self, void* edx, const Ogre::Vector3* position)
        {
            RecordCameraWriter(_ReturnAddress());
            if (g_RealCamSetPosV)
                g_RealCamSetPosV(self, edx, position);
        }

        void __fastcall HookCamSetPos3(void* self, void* edx, float x, float y, float z)
        {
            RecordCameraWriter(_ReturnAddress());
            if (g_RealCamSetPos3)
                g_RealCamSetPos3(self, edx, x, y, z);
        }

        bool WriteRel32(uint8_t* operand, int32_t value)
        {
            DWORD oldProtect = 0;
            if (!VirtualProtect(operand, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(operand, &value, sizeof(value));
            DWORD ignored = 0;
            VirtualProtect(operand, sizeof(value), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), operand - 1, 5);
            return true;
        }

        // Redirect every direct E8 call to `target` inside the executable.
        // Same technique as pilot_fp_animation_trace.cpp's InstallExeObserver.
        size_t PatchDirectCalls(void* target, void* replacement, const char* label)
        {
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module || !target || !replacement)
                return 0;
            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;
            const size_t imageSize = nt->OptionalHeader.SizeOfImage;
            auto* section = IMAGE_FIRST_SECTION(nt);
            size_t patched = 0;
            for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;
                size_t size = section->Misc.VirtualSize ? section->Misc.VirtualSize : section->SizeOfRawData;
                if (section->VirtualAddress >= imageSize)
                    continue;
                if (size > imageSize - section->VirtualAddress)
                    size = imageSize - section->VirtualAddress;
                uint8_t* code = base + section->VirtualAddress;
                for (size_t o = 0; o + 5 <= size; ++o)
                {
                    if (code[o] != 0xE8)
                        continue;
                    int32_t rel = 0;
                    std::memcpy(&rel, code + o + 1, sizeof(rel));
                    if (code + o + 5 + rel != target)
                        continue;
                    const intptr_t delta = reinterpret_cast<uint8_t*>(replacement) - (code + o + 5);
                    if (delta < INT32_MIN || delta > INT32_MAX)
                        continue;
                    if (WriteRel32(code + o + 1, static_cast<int32_t>(delta)))
                    {
                        ++patched;
                        o += 4;
                    }
                }
            }
            LogShimA(LogLevel::Info, kComponent, "[WALKID] %s direct-call observers installed=%u",
                label, static_cast<unsigned>(patched));
            return patched;
        }

        // Calls from the executable into an OgreMain export normally go through
        // the import table (call dword ptr [__imp_X]), not a relative E8 call,
        // so patching E8 sites alone finds nothing. Redirect the IAT slot too.
        size_t PatchIatEntries(void* target, void* replacement, const char* label)
        {
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module || !target || !replacement)
                return 0;
            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;
            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress)
                return 0;
            size_t patched = 0;
            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            for (; descriptor->Name; ++descriptor)
            {
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                for (; thunk->u1.Function; ++thunk)
                {
                    void** slot = reinterpret_cast<void**>(&thunk->u1.Function);
                    if (*slot != target)
                        continue;
                    DWORD oldProtect = 0;
                    if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                        continue;
                    *slot = replacement;
                    DWORD ignored = 0;
                    VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
                    ++patched;
                }
            }
            LogShimA(LogLevel::Info, kComponent, "[WALKID] %s IAT observers installed=%u",
                label, static_cast<unsigned>(patched));
            return patched;
        }

        void InstallCameraWriterObservers()
        {
            // The camera may be moved via its parent SceneNode rather than
            // Camera::setPosition, so observe the node writers as well and keep
            // only the writes that land on the nodes this trace is tracking.
            void* nodeSetPosV = FindExport("?setPosition@Node@Ogre@@UAEXABVVector3@2@@Z", "Node::setPosition(Vector3)");
            void* nodeSetPos3 = FindExport("?setPosition@Node@Ogre@@UAEXMMM@Z", "Node::setPosition(f,f,f)");
            g_RealNodeSetPosV = reinterpret_cast<FnCamSetPosV>(nodeSetPosV);
            g_RealNodeSetPos3 = reinterpret_cast<FnCamSetPos3>(nodeSetPos3);
            if (nodeSetPosV)
                PatchIatEntries(nodeSetPosV, reinterpret_cast<void*>(&HookNodeSetPosV), "Node::setPosition(Vector3)");
            if (nodeSetPos3)
                PatchIatEntries(nodeSetPos3, reinterpret_cast<void*>(&HookNodeSetPos3), "Node::setPosition(f,f,f)");

            void* setPosV = FindExport("?setPosition@Camera@Ogre@@QAEXABVVector3@2@@Z", "Camera::setPosition(Vector3)");
            void* setPos3 = FindExport("?setPosition@Camera@Ogre@@QAEXMMM@Z", "Camera::setPosition(f,f,f)");
            if (setPosV)
            {
                g_RealCamSetPosV = reinterpret_cast<FnCamSetPosV>(setPosV);
                PatchDirectCalls(setPosV, reinterpret_cast<void*>(&HookCamSetPosV), "Camera::setPosition(Vector3)");
                PatchIatEntries(setPosV, reinterpret_cast<void*>(&HookCamSetPosV), "Camera::setPosition(Vector3)");
            }
            if (setPos3)
            {
                g_RealCamSetPos3 = reinterpret_cast<FnCamSetPos3>(setPos3);
                PatchDirectCalls(setPos3, reinterpret_cast<void*>(&HookCamSetPos3), "Camera::setPosition(f,f,f)");
                PatchIatEntries(setPos3, reinterpret_cast<void*>(&HookCamSetPos3), "Camera::setPosition(f,f,f)");
            }
        }

        bool InstallListener()
        {
            if (g_ListenerInstalled.load(std::memory_order_acquire))
                return true;
            if (!g_RenderSceneExport)
                return false;
            Ogre::SceneManager* manager = SafeGetSceneManager();
            if (!manager)
                return false;
            void* original = nullptr;
            if (!PatchVtableSlot(manager, g_RenderSceneExport,
                reinterpret_cast<void*>(&HookRenderScene), &g_RenderSceneSlot, &original))
                return false;
            g_RealRenderScene = reinterpret_cast<FnRenderScene>(original);
            InstallCameraWriterObservers();
            g_ListenerInstalled.store(true, std::memory_order_release);
            LogShimA(LogLevel::Info, kComponent, "[WALKID] frame capture armed on SceneManager=0x%p", manager);
            return true;
        }

        unsigned __stdcall ArmWorker(void*)
        {
            // The listener can only be attached once Ogre::Root exists. Wait for
            // it, arm, and exit -- all capture then happens on the render thread.
            for (int attempt = 0; attempt < 600; ++attempt)
            {
                if (!g_Enabled.load(std::memory_order_acquire))
                    return 0;
                if (ResolveExports() && InstallListener())
                    return 0;
                Sleep(500);
            }
            LogShimA(LogLevel::Warn, kComponent, "[WALKID] gave up arming frame listener after 300s");
            return 0;
        }
    } // namespace

    void InitializeWalkerCockpitTrace()
    {
        if (!Requested())
            return;
        g_Enabled.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent, "[WALKID] walker cockpit trace enabled");
        HANDLE thread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, ArmWorker, nullptr, 0, nullptr));
        if (thread)
            CloseHandle(thread);
        else
            g_Enabled.store(false, std::memory_order_release);
    }

    void ShutdownWalkerCockpitTrace()
    {
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        LogSummary("shutdown");
        g_Enabled.store(false, std::memory_order_release);
        if (g_ListenerInstalled.load(std::memory_order_acquire) && g_RenderSceneSlot && g_RealRenderScene)
        {
            DWORD oldProtect = 0;
            if (VirtualProtect(g_RenderSceneSlot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
            {
                *g_RenderSceneSlot = reinterpret_cast<void*>(g_RealRenderScene);
                DWORD ignored = 0;
                VirtualProtect(g_RenderSceneSlot, sizeof(void*), oldProtect, &ignored);
            }
            g_ListenerInstalled.store(false, std::memory_order_release);
        }
    }

    // Declared inside the namespace so the anonymous-namespace state is
    // reachable; extern "C" still exports them under their plain names.

    // Phase tag from the Lua/EXU bench, so native frames correlate with the
    // scripted test phase (stabilize / forward / rotate / aim / slope).
    // Setting a case also emits and resets the running summary, so each phase
    // gets its own peak-jerk ranking rather than one blended figure.
    extern "C" __declspec(dllexport) void __cdecl OpenShimSetWalkerCase(const char* name)
    {
        if (!name)
            return;
        if (g_Enabled.load(std::memory_order_acquire))
            LogSummary("case-end");
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            CopyText(g_Case, sizeof(g_Case), name);
            ResetTracking();
        }
        LogShimA(LogLevel::Info, kComponent, "[WALKID] case set to %s", name);
    }

    extern "C" __declspec(dllexport) void __cdecl OpenShimWalkerTraceSummary(const char* reason)
    {
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        LogSummary(reason ? reason : "requested");
    }
}
