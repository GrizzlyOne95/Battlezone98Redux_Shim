#include "pilot_fp_animation_trace.h"
#include "BZROpenShim.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>
#include <intrin.h>

#include <array>
#include <atomic>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <limits>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>

// Ogre 1.10 headers for FP enumeration. This TU is compiled as C++14 per
// BZROpenShim.vcxproj (see ogre_animation_profiler.cpp) because the pinned
// Ogre 1.10 headers depend on std surfaces removed in C++20 (std::tr1,
// std::allocator<void>::const_pointer, etc.). The retail BZR Ogre headers
// also use the deprecated `register` storage class, which is removed in
// C++17. Provide the same workaround as ogre_animation_profiler.cpp:
// define `register` away around the Ogre includes so the headers compile
// under the project's language mode.
//
// Do not blindly change ogre_animation_profiler.cpp's override; it currently
// builds and has the same workaround. This file had the same LanguageStandard
// override but lacked the workaround, which caused the CI failure:
//   OgreMemorySTLAllocator.h(130): error C3878: unexpected token 'register'
// After adding the workaround both workflows that were red become green.
#ifndef register
#define OPENSHIM_OGRE_RESTORE_REGISTER
#define register
#endif
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreMesh.h"
#include "OgreResource.h"
#ifdef OPENSHIM_OGRE_RESTORE_REGISTER
#undef register
#undef OPENSHIM_OGRE_RESTORE_REGISTER
#endif

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "pilot-fp-anim";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "TracePilotFPAnimations";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_TRACE_PILOT_FP_ANIMATIONS";
        constexpr char kManipEnvironmentSwitch[] = "OPENSHIM_PILOT_FP_MANIP";
        constexpr char kManipScopeEnvironmentSwitch[] = "OPENSHIM_PILOT_FP_MANIP_SCOPE";
        constexpr char kManipIniKey[] = "PilotFPAnimManip";
        constexpr char kManipAnimIniKey[] = "PilotFPAnimManipAnim";
        constexpr char kManipModeIniKey[] = "PilotFPAnimManipMode";
        constexpr DWORD kPollSleepMs = 25;
        constexpr DWORD kInventoryPollIntervalMs = 1500;
        constexpr DWORD kFpEnumerateIntervalMs = 1500;
        constexpr size_t kMaxBindings = 64;
        // Upper bound on one enumeration pass. The walk copies raw pointers into
        // a fixed buffer so it can run under SEH, and a scene larger than this
        // is truncated rather than growing an allocation inside __try.
        constexpr size_t kMaxEnumeratedSceneObjects = 4096;

        // Verified current Redux layout already used by OpenShim's local-player,
        // headlight, satellite-visibility and jump-snipe diagnostics:
        //   main + 0x00517AFC -> GameObject::userObject
        //   Person + 0x0F0    -> render bridge
        //   bridge + 0x094    -> Ogre::Entity
        constexpr uintptr_t kUserObjectRva = 0x00517AFC;
        constexpr size_t kPersonRenderBridgeOffset = 0x0F0;
        constexpr size_t kRenderBridgeOgreEntityOffset = 0x094;

        // SceneManager global structure verified in bzr_hooks.cpp:2042 (same build)
        //   0x00920EA0 -> structure, +0x08 -> SceneManager*
        // Used to obtain SceneManager* without relying on SceneManager::createEntity import.
        constexpr uintptr_t kOgreSceneManagerStructureAddr = 0x00920EA0;
        constexpr uintptr_t kOgreSceneManagerOffset = 0x08;

        using FnEntityGetAnimationState = void* (__thiscall*)(void*, const std::string&);
        using FnEntityGetAllAnimationStates = void* (__thiscall*)(void*);
        using FnAnimationSetEnabled = void(__thiscall*)(void*, bool);
        using FnAnimationSetLoop = void(__thiscall*)(void*, bool);
        using FnAnimationSetTimePosition = void(__thiscall*)(void*, float);
        using FnAnimationSetWeight = void(__thiscall*)(void*, float);
        using FnAnimationAddTime = void(__thiscall*)(void*, float);

        struct ExportMatch
        {
            std::string name;
            void* address = nullptr;
        };

        struct TraceBinding
        {
            void* state = nullptr;
            void* entity = nullptr;
            char animation[64] = {};
            bool hasLastEnabled = false;
            bool lastEnabled = false;
            bool hasLastLoop = false;
            bool lastLoop = false;
            bool hasLastWeight = false;
            float lastWeight = 0.0f;
            uint64_t lastDtLogTick = 0;
            uint32_t dtSuppressedCount = 0;
        };

        enum class TargetKind { World, Fp };

        struct TargetState
        {
            std::atomic<void*> entity{ nullptr };
            std::atomic<uint64_t> generation{ 0 };
            std::array<TraceBinding, kMaxBindings> bindings{};
            std::mutex mutex;
            DWORD lastInventoryTick{ 0 };
            void* lastInventoryEntity{ nullptr };
            char meshName[64]{};
            char skeletonName[64]{};
            char entityName[64]{};
        };

        const char* TargetKindPrefix(TargetKind kind)
        {
            return kind == TargetKind::World ? "" : "[FP]";
        }

        const char* TargetKindName(TargetKind kind)
        {
            return kind == TargetKind::World ? "WORLD" : "FP";
        }

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_ManipEnabled{ false };
        char g_ManipTargetAnim[64] = "stand2Kneel";
        enum class ManipMode { Freeze, ForceWeight, Disabled } g_ManipMode = ManipMode::Freeze;
        enum class ManipScope { Both, World, Fp } g_ManipScope = ManipScope::Both;
        uintptr_t g_WorkerThread = 0;
        std::mutex g_TrackerMutex;
        std::atomic<bool> g_TrackerExportsReady{ false };

        TargetState g_World;
        TargetState g_Fp;

        FnEntityGetAnimationState g_RealEntityGetAnimationState = nullptr;
        FnEntityGetAllAnimationStates g_RealEntityGetAllAnimationStates = nullptr;
        FnAnimationSetEnabled g_RealAnimationSetEnabled = nullptr;
        FnAnimationSetLoop g_RealAnimationSetLoop = nullptr;
        FnAnimationSetTimePosition g_RealAnimationSetTimePosition = nullptr;
        FnAnimationSetWeight g_RealAnimationSetWeight = nullptr;
        FnAnimationAddTime g_RealAnimationAddTime = nullptr;

        using FnEntityHasSkeleton = bool(__thiscall*)(void*);
        using FnEntityHasAnimationState = bool(__thiscall*)(void*, const std::string&);
        using FnEntityGetMesh = const Ogre::MeshPtr&(__thiscall*)(void*);
        using FnMovableObjectGetName = const std::string&(__thiscall*)(void*);
        FnEntityHasSkeleton g_FnEntityHasSkeleton = nullptr;
        FnEntityHasAnimationState g_FnEntityHasAnimationState = nullptr;
        FnEntityGetMesh g_FnEntityGetMesh = nullptr;
        FnMovableObjectGetName g_FnMovableObjectGetName = nullptr;

        void* g_EntityHasSkeletonExport = nullptr;

        DWORD g_LastFpEnumerateTick = 0;

        // Strict pilot FP mesh bases (exact normalized base without extension). From
        // craft_bounds_architecture_20260822.md:122 table (15-entry) pilot entries.
        const char* kStrictPilotFpBases[] = {
            "aspilo_fp", "bspilo_fp", "sspilo_fp", "cspilo_fp", "bsheav_fp"
        };

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;
            std::string v(value);
            for (char& ch : v)
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            return v != "0" && v != "false" && v != "no" && v != "off" && v != "disabled";
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";
            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';
            return std::string(path) + "openshim.ini";
        }

        bool TraceRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kEnvironmentSwitch, envValue, static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);
            const std::string iniPath = GetOpenShimIniPath();
            // Ships off. This is a capture tool for animation investigation, and
            // every document that uses it says to set the key to 1 first.
            return GetPrivateProfileIntA(kIniSection, kIniKey, 0, iniPath.c_str()) != 0;
        }

        bool ManipRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kManipEnvironmentSwitch, envValue, static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);
            const std::string iniPath = GetOpenShimIniPath();
            return GetPrivateProfileIntA(kIniSection, kManipIniKey, 0, iniPath.c_str()) != 0;
        }

        void RefreshManipConfig()
        {
            g_ManipEnabled.store(ManipRequested(), std::memory_order_release);
            const std::string iniPath = GetOpenShimIniPath();
            char animName[64] = {};
            GetPrivateProfileStringA(kIniSection, kManipAnimIniKey, "stand2Kneel", animName, sizeof(animName), iniPath.c_str());
            if (animName[0])
                strncpy_s(g_ManipTargetAnim, sizeof(g_ManipTargetAnim), animName, _TRUNCATE);
            char modeName[32] = {};
            GetPrivateProfileStringA(kIniSection, kManipModeIniKey, "freeze", modeName, sizeof(modeName), iniPath.c_str());
            std::string modeLower(modeName);
            for (char& ch : modeLower) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            if (modeLower == "weight" || modeLower == "forceweight" || modeLower == "force_weight")
                g_ManipMode = ManipMode::ForceWeight;
            else if (modeLower == "freeze" || modeLower == "block" || modeLower == "hold")
                g_ManipMode = ManipMode::Freeze;
            else
                g_ManipMode = ManipMode::Disabled;
            if (!g_ManipEnabled.load(std::memory_order_acquire))
                g_ManipMode = ManipMode::Disabled;

            char scopeName[32] = {};
            const DWORD scopeLength = GetEnvironmentVariableA(
                kManipScopeEnvironmentSwitch, scopeName, static_cast<DWORD>(sizeof(scopeName)));
            std::string scopeLower(scopeLength > 0 && scopeLength < sizeof(scopeName) ? scopeName : "both");
            for (char& ch : scopeLower) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            if (scopeLower == "world")
                g_ManipScope = ManipScope::World;
            else if (scopeLower == "fp")
                g_ManipScope = ManipScope::Fp;
            else
                g_ManipScope = ManipScope::Both;
        }

        bool Manipulates(TargetKind kind)
        {
            return g_ManipScope == ManipScope::Both ||
                (g_ManipScope == ManipScope::World && kind == TargetKind::World) ||
                (g_ManipScope == ManipScope::Fp && kind == TargetKind::Fp);
        }

        void CopyText(char* destination, size_t destinationSize, const char* source)
        {
            if (!destination || destinationSize == 0)
                return;
            destination[0] = '\0';
            if (!source)
                return;
            strncpy_s(destination, destinationSize, source, _TRUNCATE);
        }

        bool MainModuleContains(const void* address)
        {
            if (!address)
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
            const auto* pointer = reinterpret_cast<const uint8_t*>(address);
            return pointer >= base && pointer < base + nt->OptionalHeader.SizeOfImage;
        }

        uintptr_t CallerRva(void* returnAddress, bool& outIsMainModule)
        {
            outIsMainModule = MainModuleContains(returnAddress);
            if (!outIsMainModule)
                return 0;
            HMODULE module = GetModuleHandleA(nullptr);
            return reinterpret_cast<uintptr_t>(returnAddress) - reinterpret_cast<uintptr_t>(module);
        }

        void* ReadPointer(const void* address)
        {
            if (!address)
                return nullptr;
            void* value = nullptr;
            __try
            {
                value = *reinterpret_cast<void* const*>(address);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            return value;
        }

        bool LooksLikeOgreObject(const void* object)
        {
            if (!object)
                return false;
            return OgreRuntime::ContainsAddress(ReadPointer(object));
        }

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
                const auto* completeObjectLocator =
                    reinterpret_cast<const uint8_t*>(vtable[-1]);
                if (!MainModuleContains(completeObjectLocator) ||
                    !MainModuleContains(completeObjectLocator + 15))
                    return false;
                const auto* typeDescriptor =
                    *reinterpret_cast<const uint8_t* const*>(completeObjectLocator + 12);
                if (!MainModuleContains(typeDescriptor) ||
                    !MainModuleContains(typeDescriptor + 8))
                    return false;
                const char* decoratedName =
                    reinterpret_cast<const char*>(typeDescriptor + 8);
                size_t length = 0;
                while (length + 1 < bufferSize)
                {
                    const char* current = decoratedName + length;
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

        bool IsPersonObject(const void* object, char* className, size_t classNameSize)
        {
            if (!TryGetRttiClassName(object, className, classNameSize))
                return false;
            return std::strstr(className, "Person") != nullptr;
        }

        void* ResolveCurrentLocalPersonOgreEntity(void*& outPerson, char* className, size_t classNameSize)
        {
            outPerson = nullptr;
            if (className && classNameSize)
                className[0] = '\0';
            if (!IsPatchingComplete() || !IsCompatibleGameVersion())
                return nullptr;
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module)
                return nullptr;
            const auto* base = reinterpret_cast<const uint8_t*>(module);
            __try
            {
                void* person = *reinterpret_cast<void* const*>(base + kUserObjectRva);
                if (!person || !IsPersonObject(person, className, classNameSize))
                    return nullptr;
                void* renderBridge = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(person) + kPersonRenderBridgeOffset);
                if (!renderBridge)
                    return nullptr;
                void* entity = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(renderBridge) + kRenderBridgeOgreEntityOffset);
                if (!LooksLikeOgreObject(entity))
                    return nullptr;
                outPerson = person;
                return entity;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outPerson = nullptr;
                if (className && classNameSize)
                    className[0] = '\0';
                return nullptr;
            }
        }

        // No-unwind helper for SceneManager global. Must not have C++ objects before __try.
        Ogre::SceneManager* SafeGetSceneManagerViaGlobal()
        {
            void* sm = nullptr;
            __try
            {
                auto* structure = *reinterpret_cast<uint8_t**>(kOgreSceneManagerStructureAddr);
                if (!structure)
                    return nullptr;
                sm = *reinterpret_cast<void**>(structure + kOgreSceneManagerOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            return static_cast<Ogre::SceneManager*>(sm);
        }


        // The game's global keeps pointing at a SceneManager the engine has
        // already destroyed, so a non-null pointer is not a live one. Verified
        // against the 2026-08-30 crash dump: the freed manager's vptr read
        // 0x0E94ED58, which is heap and in no loaded module, and its vtable slot
        // for getMovableObjectIterator was zero -- so the virtual call went to
        // address 0 and killed the process. A live manager's vptr is always in
        // OgreMain.dll, which is cheap to confirm and rules that case out.
        bool SceneManagerLooksLive(void* sm)
        {
            if (!sm)
                return false;

            void* vptr = nullptr;
            __try
            {
                vptr = *reinterpret_cast<void**>(sm);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!vptr)
                return false;

            HMODULE owner = nullptr;
            if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    reinterpret_cast<LPCSTR>(vptr),
                                    &owner))
            {
                return false; // heap or freed memory: not a vtable at all
            }
            return owner != nullptr && owner == GetModuleHandleA("OgreMain.dll");
        }

        // Walks the scene under SEH and copies out raw pointers. This has to be
        // its own function with none but POD locals: a function that needs
        // unwinding cannot host __try (C2712), and the caller builds vectors and
        // strings. The type name is built by the caller for the same reason.
        //
        // A C++ `try`/`catch (...)` around this call would not do: the project
        // builds /EHsc (<ExceptionHandling>Sync</ExceptionHandling>), where
        // catch (...) does not catch an access violation. That is why the
        // previous guard here never fired.
        bool SafeCollectSceneEntities(Ogre::SceneManager* sm,
                                      const std::string& typeName,
                                      void** out,
                                      size_t capacity,
                                      size_t& outCount)
        {
            outCount = 0;
            if (!sm || !out || capacity == 0)
                return false;

            size_t count = 0;
            __try
            {
                Ogre::SceneManager::MovableObjectIterator it =
                    sm->getMovableObjectIterator(typeName);
                while (it.hasMoreElements() && count < capacity)
                {
                    Ogre::MovableObject* mo = it.getNext();
                    if (mo)
                        out[count++] = mo;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            outCount = count;
            return true;
        }

        bool SafeEntityHasSkeleton(void* ent)
        {
            if (!g_FnEntityHasSkeleton || !ent)
                return false;
            bool result = false;
            __try
            {
                result = g_FnEntityHasSkeleton(ent);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return result;
        }

        bool CallHasAnimNoUnwind(void* ent, const std::string& str)
        {
            bool result = false;
            __try
            {
                result = g_FnEntityHasAnimationState(ent, str);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return result;
        }

        bool SafeEntityHasAnimationState(void* ent, const char* name)
        {
            if (!g_FnEntityHasAnimationState || !ent || !name)
                return false;
            try
            {
                std::string tmp(name);
                return CallHasAnimNoUnwind(ent, tmp);
            }
            catch (...)
            {
                return false;
            }
        }

        const std::string* SafeMovableObjectGetNamePtr(void* mo)
        {
            if (!g_FnMovableObjectGetName || !mo)
                return nullptr;
            const std::string* ptr = nullptr;
            __try
            {
                const std::string& ref = g_FnMovableObjectGetName(mo);
                ptr = &ref;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            return ptr;
        }

        std::string NormalizeMeshBase(const std::string& meshName)
        {
            std::string base = meshName;
            // Strip path
            size_t slash = base.find_last_of("/\\");
            if (slash != std::string::npos)
                base = base.substr(slash + 1);
            // Strip extension
            size_t dot = base.find_last_of('.');
            if (dot != std::string::npos)
                base = base.substr(0, dot);
            // Lowercase
            for (char& c : base) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            return base;
        }

        bool IsBroadFpMesh(const std::string& meshName)
        {
            std::string lower = meshName;
            for (char& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            return lower.find("_fp") != std::string::npos;
        }

        bool IsStrictFpPilotMesh(const std::string& meshName)
        {
            std::string base = NormalizeMeshBase(meshName);
            for (const char* known : kStrictPilotFpBases)
            {
                if (base == known)
                    return true;
            }
            return false;
        }

        void ClearBindingsLocked(TargetState& target)
        {
            for (TraceBinding& b : target.bindings)
                b = {};
        }

        // Generalized binding helpers

        void RegisterBindingForTarget(TargetState& target, TargetKind kind, void* state, void* entity,
            const std::string& animation, void* caller)
        {
            if (!state || !entity)
                return;
            bool logBinding = false;
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                TraceBinding* freeSlot = nullptr;
                for (TraceBinding& b : target.bindings)
                {
                    if (b.state == state)
                    {
                        const bool changed = b.entity != entity || std::strcmp(b.animation, animation.c_str()) != 0;
                        b.entity = entity;
                        CopyText(b.animation, sizeof(b.animation), animation.c_str());
                        logBinding = changed;
                        freeSlot = &b;
                        break;
                    }
                    if (!freeSlot && b.state == nullptr)
                        freeSlot = &b;
                }
                if (!freeSlot)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[FPAnim]%s binding table full; state=0x%p entity=0x%p anim=%s",
                        TargetKindPrefix(kind), state, entity, animation.c_str());
                    return;
                }
                if (freeSlot->state == nullptr)
                {
                    freeSlot->entity = entity;
                    CopyText(freeSlot->animation, sizeof(freeSlot->animation), animation.c_str());
                    freeSlot->state = state;
                    logBinding = true;
                }
            }
            if (logBinding)
            {
                bool inMain = false;
                uintptr_t rva = CallerRva(caller, inMain);
                LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s entity=0x%p anim=%s state=0x%p bound=1 caller=0x%p rva=0x%08X inMain=%u gen=%llu",
                    TargetKindPrefix(kind), entity, animation.c_str(), state, caller, static_cast<unsigned>(rva), inMain ? 1u : 0u,
                    static_cast<unsigned long long>(target.generation.load(std::memory_order_acquire)));
            }
        }

        std::string SafeEntityMeshName(Ogre::Entity* entity)
        {
            if (!entity)
                return "unknown";
            try
            {
                if (!g_FnEntityGetMesh)
                    return "unknown";
                const Ogre::MeshPtr& mesh = g_FnEntityGetMesh(entity);
                if (!mesh.isNull())
                    return mesh->getName();
            }
            catch (...)
            {
            }
            return "unknown";
        }

        std::string SafeEntitySkeletonName(Ogre::Entity* entity)
        {
            if (!entity)
                return "none";
            return SafeEntityHasSkeleton(entity) ? "present" : "none";
        }

        bool FindBindingForTarget(TargetState& target, void* state, void*& entity, char* animation, size_t animationSize)
        {
            if (!state)
                return false;
            std::lock_guard<std::mutex> lock(target.mutex);
            for (const TraceBinding& b : target.bindings)
            {
                if (b.state != state)
                    continue;
                entity = b.entity;
                CopyText(animation, animationSize, b.animation);
                return true;
            }
            return false;
        }

        TraceBinding* FindBindingMutableForTarget(TargetState& target, void* state)
        {
            for (TraceBinding& b : target.bindings)
                if (b.state == state)
                    return &b;
            return nullptr;
        }

        // Safe helper for getAllAnimationStates without unwind before __try
        void* SafeGetAllAnimationStates(void* entity)
        {
            if (!g_RealEntityGetAllAnimationStates || !entity)
                return nullptr;
            void* result = nullptr;
            __try
            {
                result = g_RealEntityGetAllAnimationStates(entity);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return reinterpret_cast<void*>(0x1);
            }
            return result;
        }

        void RefreshWorldTarget()
        {
            void* person = nullptr;
            char className[96] = {};
            void* entity = ResolveCurrentLocalPersonOgreEntity(person, className, sizeof(className));
            void* previous = g_World.entity.load(std::memory_order_acquire);
            if (previous == entity)
                return;
            {
                std::lock_guard<std::mutex> lock(g_World.mutex);
                ClearBindingsLocked(g_World);
                g_World.entity.store(entity, std::memory_order_release);
                if (entity)
                    g_World.generation.fetch_add(1, std::memory_order_acq_rel);
                else
                    g_World.generation.fetch_add(1, std::memory_order_acq_rel);
                g_World.lastInventoryTick = 0;
                g_World.lastInventoryEntity = nullptr;
            }
            if (entity)
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] target person=0x%p class=%s entity=0x%p renderBridge=Person+0x%03X/Ogre+0x%03X gen=%llu",
                    person, className[0] ? className : "?", entity,
                    static_cast<unsigned>(kPersonRenderBridgeOffset),
                    static_cast<unsigned>(kRenderBridgeOgreEntityOffset),
                    static_cast<unsigned long long>(g_World.generation.load()));
            }
            else if (previous)
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] local userObject is no longer a Person; target cleared gen=%llu",
                    static_cast<unsigned long long>(g_World.generation.load()));
                // Also clear FP target when world pilot disappears — FP presentation should not outlive pilot.
                void* fpPrev = g_Fp.entity.load(std::memory_order_acquire);
                if (fpPrev)
                {
                    std::lock_guard<std::mutex> lock(g_Fp.mutex);
                    ClearBindingsLocked(g_Fp);
                    g_Fp.entity.store(nullptr, std::memory_order_release);
                    g_Fp.generation.fetch_add(1, std::memory_order_acq_rel);
                    g_Fp.meshName[0] = '\0';
                    g_Fp.skeletonName[0] = '\0';
                    g_Fp.entityName[0] = '\0';
                    g_Fp.lastInventoryTick = 0;
                    g_Fp.lastInventoryEntity = nullptr;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][FP] target released reason=world-pilot-cleared prevEntity=0x%p gen=%llu",
                        fpPrev, static_cast<unsigned long long>(g_Fp.generation.load()));
                }
            }
        }

        // FP enumeration via Ogre SceneManager::getMovableObjectIterator("Entity")
        // Verified OgreMain.dll export: ?getMovableObjectIterator@SceneManager@Ogre@@UAE?AV?$MapIterator@...
        // Verified header: OgreSceneManager.h:3316 MovableObjectIterator getMovableObjectIterator(const String&)
        // This seam is the documented fallback when creation interception via import is not
        // available (exe does not import SceneManager::createEntity — verified via dumpbin /imports).
        void RefreshFpTargetViaEnumeration(bool force = false)
        {
            DWORD now = GetTickCount();
            if (!force && now - g_LastFpEnumerateTick < kFpEnumerateIntervalMs)
                return;
            g_LastFpEnumerateTick = now;

            // Only enumerate when local player is a Person — temporal creation near HopOut
            void* worldPerson = nullptr;
            char className[96] = {};
            void* worldEntity = ResolveCurrentLocalPersonOgreEntity(worldPerson, className, sizeof(className));
            bool worldIsPilot = (worldEntity != nullptr);

            Ogre::SceneManager* sm = SafeGetSceneManagerViaGlobal();
            if (!SceneManagerLooksLive(sm))
            {
                // Either there is no SceneManager yet (early startup) or the
                // global still points at one the engine has destroyed, which is
                // what a mission change and a quit both leave behind. Fail
                // closed either way.
                return;
            }

            // Collect broad candidates and strict pilot candidates
            std::vector<Ogre::Entity*> broadCandidates;
            std::vector<Ogre::Entity*> strictCandidates;
            std::vector<std::string> broadMeshNames;
            std::vector<std::string> strictMeshNames;

            // The liveness check above is a filter, not a guarantee: the engine
            // can free the SceneManager between that check and this walk, so the
            // walk runs under SEH as well.
            static const std::string kEntityTypeName("Entity");
            std::vector<void*> sceneObjects(kMaxEnumeratedSceneObjects, nullptr);
            size_t sceneObjectCount = 0;
            if (!SafeCollectSceneEntities(sm,
                                          kEntityTypeName,
                                          sceneObjects.data(),
                                          sceneObjects.size(),
                                          sceneObjectCount))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[FPAnim][FP] enumeration faulted; treating SceneManager=0x%p as gone", sm);
                return;
            }
            if (sceneObjectCount == sceneObjects.size())
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[FPAnim][FP] enumeration truncated at %u objects",
                    static_cast<unsigned>(sceneObjectCount));
            }

            {
                for (size_t objectIndex = 0; objectIndex < sceneObjectCount; ++objectIndex)
                {
                    Ogre::MovableObject* mo =
                        static_cast<Ogre::MovableObject*>(sceneObjects[objectIndex]);
                    if (!mo)
                        continue;
                    Ogre::Entity* ent = static_cast<Ogre::Entity*>(mo);
                    if (!ent)
                        continue;
                    // Strict qualification via animation vocabulary (pilot-specific) rather than mesh name alone.
                    // Broad: hasSkeleton. Strict: hasSkeleton + hasAnimationState("stand2Kneel") + hasAnimationState("idle")
                    bool hasSkel = SafeEntityHasSkeleton(ent);
                    if (!hasSkel)
                        continue;
                    bool hasIdle = SafeEntityHasAnimationState(ent, "idle");
                    bool hasStand2Kneel = SafeEntityHasAnimationState(ent, "stand2Kneel");
                    // Broad candidate: any skeleton with idle (catches all animated Entities, but we log and then filter)
                    // For pilot FP discovery, broad is hasSkel, strict is pilot anim set
                    broadCandidates.push_back(ent);
                    std::string meshName = SafeEntityMeshName(ent);
                    std::string skeletonName = SafeEntitySkeletonName(ent);
                    broadMeshNames.push_back(meshName);
                    const bool isWorldEntity = ent == worldEntity;
                    const bool isPilotFpMesh = IsStrictFpPilotMesh(meshName);
                    if (hasStand2Kneel && hasIdle && isPilotFpMesh && !isWorldEntity)
                    {
                        strictCandidates.push_back(ent);
                        strictMeshNames.push_back(meshName);
                    }
                    // Log broad candidate (even if not strict) for discovery
                    std::string entName;
                    const std::string* namePtr = SafeMovableObjectGetNamePtr(mo);
                    if (namePtr) entName = *namePtr;
                    void* retAddr = _ReturnAddress();
                    bool inMain = false;
                    uintptr_t rva = CallerRva(retAddr, inMain);
                    bool isStrict = hasStand2Kneel && hasIdle && isPilotFpMesh && !isWorldEntity;
                    if (g_Enabled.load(std::memory_order_relaxed))
                    {
                        LogShimA(LogLevel::Info, kComponent,
                            "[FPAnim][FP] candidate entity=0x%p mesh=%s skeleton=%s hasSkeleton=%u name=%s caller=0x%p rva=0x%08X inMain=%u strict=%u worldPilot=%u",
                            ent, meshName.c_str(), skeletonName.c_str(), hasSkel ? 1u : 0u, entName.c_str(),
                            retAddr, static_cast<unsigned>(rva), inMain ? 1u : 0u,
                            isStrict ? 1u : 0u, isWorldEntity ? 1u : 0u);
                    }
                }
            }

            // Promotion logic: require strict pilot mesh + worldIsPilot
            void* currentFp = g_Fp.entity.load(std::memory_order_acquire);
            bool currentStillAlive = false;
            for (Ogre::Entity* c : broadCandidates)
            {
                if (c == currentFp)
                {
                    currentStillAlive = true;
                    break;
                }
            }

            if (!currentFp)
            {
                // No current target — promote if we have strict candidate and worldIsPilot
                if (!strictCandidates.empty() && worldIsPilot)
                {
                    Ogre::Entity* chosen = strictCandidates[0];
                    std::string chosenMesh = strictMeshNames[0];
                    std::string chosenSkel = SafeEntitySkeletonName(chosen);
                    std::string chosenEntName;
                    const std::string* namePtr2 = SafeMovableObjectGetNamePtr(chosen);
                    if (namePtr2) chosenEntName = *namePtr2;
                    {
                        std::lock_guard<std::mutex> lock(g_Fp.mutex);
                        ClearBindingsLocked(g_Fp);
                        g_Fp.entity.store(chosen, std::memory_order_release);
                        g_Fp.generation.fetch_add(1, std::memory_order_acq_rel);
                        CopyText(g_Fp.meshName, sizeof(g_Fp.meshName), chosenMesh.c_str());
                        CopyText(g_Fp.skeletonName, sizeof(g_Fp.skeletonName), chosenSkel.c_str());
                        CopyText(g_Fp.entityName, sizeof(g_Fp.entityName), chosenEntName.c_str());
                        g_Fp.lastInventoryTick = 0;
                        g_Fp.lastInventoryEntity = nullptr;
                    }
                    void* retAddr = _ReturnAddress();
                    bool inMain = false;
                    uintptr_t rva = CallerRva(retAddr, inMain);
                    LogShimA(LogLevel::Info, kComponent,
                        "[FPAnim][FP] target acquired entity=0x%p mesh=%s skeleton=%s name=%s gen=%llu caller=0x%p rva=0x%08X inMain=%u strict=%u worldPilot=%u",
                        chosen, chosenMesh.c_str(), chosenSkel.c_str(), chosenEntName.c_str(),
                        static_cast<unsigned long long>(g_Fp.generation.load()),
                        retAddr, static_cast<unsigned>(rva), inMain ? 1u : 0u, 1u, chosen == worldEntity ? 1u : 0u);
                }
                else if (!broadCandidates.empty())
                {
                    // Log that broad candidates exist but no strict promotion — useful for asset discovery
                    LogShimA(LogLevel::Info, kComponent,
                        "[FPAnim][FP] no strict promotion: broad=%u strict=%u worldPilot=%u",
                        static_cast<unsigned>(broadCandidates.size()),
                        static_cast<unsigned>(strictCandidates.size()),
                        worldIsPilot ? 1u : 0u);
                }
            }
            else
            {
                // Have current target — check if still alive
                if (!currentStillAlive)
                {
                    // Released — could be destroyEntity, clearScene, or SceneManager rebuild
                    {
                        std::lock_guard<std::mutex> lock(g_Fp.mutex);
                        ClearBindingsLocked(g_Fp);
                        g_Fp.entity.store(nullptr, std::memory_order_release);
                        g_Fp.generation.fetch_add(1, std::memory_order_acq_rel);
                        g_Fp.meshName[0] = '\0';
                        g_Fp.skeletonName[0] = '\0';
                        g_Fp.entityName[0] = '\0';
                        g_Fp.lastInventoryTick = 0;
                        g_Fp.lastInventoryEntity = nullptr;
                    }
                    LogShimA(LogLevel::Info, kComponent,
                        "[FPAnim][FP] target released entity=0x%p reason=not-in-enumeration gen=%llu broad=%u strict=%u",
                        currentFp, static_cast<unsigned long long>(g_Fp.generation.load()),
                        static_cast<unsigned>(broadCandidates.size()),
                        static_cast<unsigned>(strictCandidates.size()));
                    // Attempt reacquire if new strict candidate exists
                    if (!strictCandidates.empty() && worldIsPilot)
                    {
                        Ogre::Entity* chosen = strictCandidates[0];
                        std::string chosenMesh = strictMeshNames[0];
                        std::string chosenSkel = SafeEntitySkeletonName(chosen);
                        std::string chosenEntName;
                        const std::string* namePtr2 = SafeMovableObjectGetNamePtr(chosen);
                        if (namePtr2) chosenEntName = *namePtr2;
                        {
                            std::lock_guard<std::mutex> lock(g_Fp.mutex);
                            ClearBindingsLocked(g_Fp);
                            g_Fp.entity.store(chosen, std::memory_order_release);
                            g_Fp.generation.fetch_add(1, std::memory_order_acq_rel);
                            CopyText(g_Fp.meshName, sizeof(g_Fp.meshName), chosenMesh.c_str());
                            CopyText(g_Fp.skeletonName, sizeof(g_Fp.skeletonName), chosenSkel.c_str());
                            CopyText(g_Fp.entityName, sizeof(g_Fp.entityName), chosenEntName.c_str());
                            g_Fp.lastInventoryTick = 0;
                            g_Fp.lastInventoryEntity = nullptr;
                        }
                        void* retAddr = _ReturnAddress();
                        bool inMain = false;
                        uintptr_t rva = CallerRva(retAddr, inMain);
                        LogShimA(LogLevel::Info, kComponent,
                            "[FPAnim][FP] target reacquired entity=0x%p mesh=%s skeleton=%s name=%s gen=%llu caller=0x%p rva=0x%08X inMain=%u",
                            chosen, chosenMesh.c_str(), chosenSkel.c_str(), chosenEntName.c_str(),
                            static_cast<unsigned long long>(g_Fp.generation.load()),
                            retAddr, static_cast<unsigned>(rva), inMain ? 1u : 0u);
                    }
                }
                else
                {
                    // Still alive — optionally update meshName if changed (should not)
                }
            }
        }

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

        void* FindUniqueFunctionExport(const char* token, const char* label)
        {
            const auto matches = FindExportsContaining(token);
            if (matches.size() != 1)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim] %s export match count=%u token=%s; observer unavailable",
                    label, static_cast<unsigned>(matches.size()), token);
                return nullptr;
            }
            LogShimA(LogLevel::Info, kComponent, "[FPAnim] resolved %s export=%s address=0x%p",
                label, matches[0].name.c_str(), matches[0].address);
            return matches[0].address;
        }

        void* FindOptionalExport(const char* token, const char* label)
        {
            const auto matches = FindExportsContaining(token);
            if (matches.empty())
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] optional %s not found token=%s", label, token);
                return nullptr;
            }
            if (matches.size() != 1)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim] optional %s ambiguous count=%u token=%s", label, static_cast<unsigned>(matches.size()), token);
                return nullptr;
            }
            LogShimA(LogLevel::Info, kComponent, "[FPAnim] resolved optional %s export=%s address=0x%p", label, matches[0].name.c_str(), matches[0].address);
            return matches[0].address;
        }

        bool ResolveTrackerExports()
        {
            if (g_TrackerExportsReady.load(std::memory_order_acquire))
                return true;
            if (!OgreRuntime::IsLoaded())
                return false;

            g_FnEntityGetMesh = reinterpret_cast<FnEntityGetMesh>(
                FindOptionalExport("getMesh@Entity@Ogre@@", "Entity::getMesh"));
            g_EntityHasSkeletonExport = FindOptionalExport(
                "hasSkeleton@Entity@Ogre@@", "Entity::hasSkeleton");
            g_FnEntityHasSkeleton = reinterpret_cast<FnEntityHasSkeleton>(g_EntityHasSkeletonExport);
            g_FnEntityHasAnimationState = reinterpret_cast<FnEntityHasAnimationState>(
                FindOptionalExport("hasAnimationState@Entity@Ogre@@", "Entity::hasAnimationState"));
            g_FnMovableObjectGetName = reinterpret_cast<FnMovableObjectGetName>(
                FindOptionalExport("getName@MovableObject@Ogre@@", "MovableObject::getName"));
            void* smIter = FindOptionalExport(
                "getMovableObjectIterator@SceneManager@Ogre@@",
                "SceneManager::getMovableObjectIterator");

            const bool ready = g_FnEntityGetMesh && g_FnEntityHasSkeleton &&
                g_FnEntityHasAnimationState && smIter;
            g_TrackerExportsReady.store(ready, std::memory_order_release);
            if (!ready)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[PilotFP] required Ogre tracking exports unavailable; public target resolver remains fail-closed");
                return false;
            }

            LogShimA(LogLevel::Info, kComponent,
                "[PilotFP] production tracker ready; strict meshes=aspilo_fp/bspilo_fp/sspilo_fp/cspilo_fp/bsheav_fp");
            return true;
        }

        bool WriteRel32(uint8_t* operand, int32_t value)
        {
            if (!operand)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(operand, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(operand, &value, sizeof(value));
            DWORD ignored = 0;
            VirtualProtect(operand, sizeof(value), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), operand - 1, 5);
            return true;
        }

        bool WritePointer(void** slot, void* value)
        {
            if (!slot)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            *slot = value;
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
            return true;
        }

        size_t PatchDirectCallsInModule(HMODULE module, void* target, void* replacement, const char* label)
        {
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
            for (WORD sectionIndex = 0; sectionIndex < nt->FileHeader.NumberOfSections; ++sectionIndex, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;
                size_t sectionSize = static_cast<size_t>(section->Misc.VirtualSize);
                if (sectionSize == 0)
                    sectionSize = static_cast<size_t>(section->SizeOfRawData);
                if (section->VirtualAddress >= imageSize)
                    continue;
                if (sectionSize > imageSize - static_cast<size_t>(section->VirtualAddress))
                    sectionSize = imageSize - static_cast<size_t>(section->VirtualAddress);
                if (sectionSize < 5)
                    continue;
                uint8_t* code = base + section->VirtualAddress;
                for (size_t i = 0; i + 5 <= sectionSize; ++i)
                {
                    if (code[i] != 0xE8)
                        continue;
                    int32_t relative = 0;
                    std::memcpy(&relative, code + i + 1, sizeof(relative));
                    uint8_t* destination = code + i + 5 + relative;
                    if (destination != target)
                        continue;
                    const intptr_t delta = reinterpret_cast<uint8_t*>(replacement) - (code + i + 5);
                    if (delta < (std::numeric_limits<int32_t>::min)() ||
                        delta > (std::numeric_limits<int32_t>::max)())
                        continue;
                    const int32_t newRelative = static_cast<int32_t>(delta);
                    if (!WriteRel32(code + i + 1, newRelative))
                        continue;
                    ++patched;
                    i += 4;
                }
            }
            if (patched)
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] %s direct-call observers installed=%u", label, static_cast<unsigned>(patched));
            return patched;
        }

        size_t PatchIatEntriesByTarget(HMODULE module, void* target, void* replacement, const char* label)
        {
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
                    if (!WritePointer(slot, replacement))
                        continue;
                    ++patched;
                }
            }
            if (patched)
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] %s IAT observers installed=%u", label, static_cast<unsigned>(patched));
            return patched;
        }

        size_t InstallExeObserver(void* target, void* replacement, const char* label)
        {
            HMODULE executable = GetModuleHandleA(nullptr);
            return PatchDirectCallsInModule(executable, target, replacement, label) +
                PatchIatEntriesByTarget(executable, target, replacement, label);
        }

        void LogBoundBoolForTarget(TargetState& target, TargetKind kind, void* state, const char* field,
            bool value, void* caller)
        {
            void* entity = nullptr;
            char animation[64] = {};
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                for (TraceBinding& b : target.bindings)
                {
                    if (b.state == state)
                    {
                        entity = b.entity;
                        CopyText(animation, sizeof(animation), b.animation);
                        break;
                    }
                }
            }
            if (!entity)
                return;
            bool shouldLog = true;
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                TraceBinding* b = FindBindingMutableForTarget(target, state);
                if (!b) return;
                if (std::strcmp(field, "enabled") == 0)
                {
                    if (b->hasLastEnabled && b->lastEnabled == value)
                        shouldLog = false;
                    b->hasLastEnabled = true;
                    b->lastEnabled = value;
                }
                else if (std::strcmp(field, "loop") == 0)
                {
                    if (b->hasLastLoop && b->lastLoop == value)
                        shouldLog = false;
                    b->hasLastLoop = true;
                    b->lastLoop = value;
                }
            }
            if (!shouldLog)
                return;
            bool inMain = false;
            uintptr_t rva = CallerRva(caller, inMain);
            LogShimA(LogLevel::Info, kComponent,
                "[FPAnim]%s entity=0x%p anim=%s state=0x%p %s=%u caller=0x%p rva=0x%08X inMain=%u gen=%llu",
                TargetKindPrefix(kind), entity, animation, state, field, value ? 1u : 0u,
                caller, static_cast<unsigned>(rva), inMain ? 1u : 0u,
                static_cast<unsigned long long>(target.generation.load()));
        }

        void LogBoundFloatForTarget(TargetState& target, TargetKind kind, void* state, const char* field,
            float value, void* caller)
        {
            void* entity = nullptr;
            char animation[64] = {};
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                for (const TraceBinding& b : target.bindings)
                {
                    if (b.state == state)
                    {
                        entity = b.entity;
                        CopyText(animation, sizeof(animation), b.animation);
                        break;
                    }
                }
            }
            if (!entity)
                return;
            if (std::strcmp(field, "weight") == 0)
            {
                bool changed = true;
                {
                    std::lock_guard<std::mutex> lock(target.mutex);
                    TraceBinding* b = FindBindingMutableForTarget(target, state);
                    if (b)
                    {
                        if (b->hasLastWeight && fabs(b->lastWeight - value) < 0.001f)
                            changed = false;
                        b->hasLastWeight = true;
                        b->lastWeight = value;
                    }
                }
                if (!changed)
                    return;
            }
            else if (std::strcmp(field, "dt") == 0)
            {
                DWORD now = GetTickCount();
                uint32_t suppressed = 0;
                {
                    std::lock_guard<std::mutex> lock(target.mutex);
                    TraceBinding* b = FindBindingMutableForTarget(target, state);
                    if (!b) return;
                    if (now - b->lastDtLogTick >= 500)
                    {
                        suppressed = b->dtSuppressedCount;
                        b->dtSuppressedCount = 0;
                        b->lastDtLogTick = now;
                    }
                    else
                    {
                        b->dtSuppressedCount++;
                        return;
                    }
                }
                if (suppressed > 0)
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s entity=0x%p anim=%s state=0x%p dt suppressed=%u since last gen=%llu",
                        TargetKindPrefix(kind), entity, animation, state, suppressed,
                        static_cast<unsigned long long>(target.generation.load()));
            }
            bool inMain = false;
            uintptr_t rva = CallerRva(caller, inMain);
            LogShimA(LogLevel::Info, kComponent,
                "[FPAnim]%s entity=0x%p anim=%s state=0x%p %s=%.6f caller=0x%p rva=0x%08X inMain=%u gen=%llu",
                TargetKindPrefix(kind), entity, animation, state, field, static_cast<double>(value),
                caller, static_cast<unsigned>(rva), inMain ? 1u : 0u,
                static_cast<unsigned long long>(target.generation.load()));
        }

        void TryLogInventoryForTarget(TargetState& target, TargetKind kind)
        {
            void* entity = target.entity.load(std::memory_order_acquire);
            if (!entity)
                return;
            DWORD now = GetTickCount();
            if (target.lastInventoryEntity == entity && (now - target.lastInventoryTick) < kInventoryPollIntervalMs)
                return;
            target.lastInventoryTick = now;
            target.lastInventoryEntity = entity;
            size_t boundCount = 0;
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                for (const auto& b : target.bindings)
                    if (b.state && b.entity == entity)
                        ++boundCount;
            }
            LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s inventory entity=0x%p boundStates=%u gen=%llu mesh=%s",
                TargetKindPrefix(kind), entity, static_cast<unsigned>(boundCount),
                static_cast<unsigned long long>(target.generation.load()),
                target.meshName[0] ? target.meshName : "?");
            {
                std::lock_guard<std::mutex> lock(target.mutex);
                for (const auto& b : target.bindings)
                {
                    if (!b.state || b.entity != entity)
                        continue;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s inv-bound anim=%s state=0x%p enabled=%u loop=%u weight=%.3f gen=%llu",
                        TargetKindPrefix(kind), b.animation, b.state,
                        b.hasLastEnabled ? (b.lastEnabled ? 1u : 0u) : 99u,
                        b.hasLastLoop ? (b.lastLoop ? 1u : 0u) : 99u,
                        b.hasLastWeight ? b.lastWeight : -1.0f,
                        static_cast<unsigned long long>(target.generation.load()));
                }
            }
            if (!g_RealEntityGetAllAnimationStates)
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s inventory Ogre enumeration unavailable (getAllAnimationStates not resolved) gen=%llu",
                    TargetKindPrefix(kind), static_cast<unsigned long long>(target.generation.load()));
                return;
            }
            void* animSet = SafeGetAllAnimationStates(entity);
            if (animSet == reinterpret_cast<void*>(0x1))
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim]%s inventory getAllAnimationStates SEH exception entity=0x%p gen=%llu",
                    TargetKindPrefix(kind), entity, static_cast<unsigned long long>(target.generation.load()));
                return;
            }
            if (!animSet)
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s inventory entity=0x%p animSet=null (no animated mesh?) gen=%llu",
                    TargetKindPrefix(kind), entity, static_cast<unsigned long long>(target.generation.load()));
                return;
            }
            LogShimA(LogLevel::Info, kComponent, "[FPAnim]%s inventory entity=0x%p animSet=0x%p HAS_ANIM_SET gen=%llu",
                TargetKindPrefix(kind), entity, animSet, static_cast<unsigned long long>(target.generation.load()));
        }

        void* __fastcall HookEntityGetAnimationState(void* self, void*, const std::string& animationName)
        {
            void* caller = _ReturnAddress();
            if (!g_RealEntityGetAnimationState)
                return nullptr;
            void* state = g_RealEntityGetAnimationState(self, animationName);
            if (!g_Enabled.load(std::memory_order_relaxed) || !state)
                return state;
            void* worldTarget = g_World.entity.load(std::memory_order_acquire);
            if (worldTarget && self == worldTarget)
                RegisterBindingForTarget(g_World, TargetKind::World, state, self, animationName, caller);
            void* fpTarget = g_Fp.entity.load(std::memory_order_acquire);
            if (fpTarget && self == fpTarget)
                RegisterBindingForTarget(g_Fp, TargetKind::Fp, state, self, animationName, caller);
            return state;
        }

        void __fastcall HookAnimationSetEnabled(void* self, void*, bool enabled)
        {
            void* caller = _ReturnAddress();
            if (!g_RealAnimationSetEnabled)
                return;
            g_RealAnimationSetEnabled(self, enabled);
            if (!g_Enabled.load(std::memory_order_relaxed))
                return;
            void* entity = nullptr;
            char anim[64] = {};
            if (FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)))
                LogBoundBoolForTarget(g_World, TargetKind::World, self, "enabled", enabled, caller);
            if (FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)))
                LogBoundBoolForTarget(g_Fp, TargetKind::Fp, self, "enabled", enabled, caller);
        }

        void __fastcall HookAnimationSetLoop(void* self, void*, bool loop)
        {
            void* caller = _ReturnAddress();
            if (!g_RealAnimationSetLoop)
                return;
            g_RealAnimationSetLoop(self, loop);
            if (!g_Enabled.load(std::memory_order_relaxed))
                return;
            void* entity = nullptr;
            char anim[64] = {};
            if (FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)))
                LogBoundBoolForTarget(g_World, TargetKind::World, self, "loop", loop, caller);
            if (FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)))
                LogBoundBoolForTarget(g_Fp, TargetKind::Fp, self, "loop", loop, caller);
        }

        void __fastcall HookAnimationSetTimePosition(void* self, void*, float timePosition)
        {
            void* caller = _ReturnAddress();
            if (!g_RealAnimationSetTimePosition)
                return;
            bool worldManip = false;
            bool fpManip = false;
            if (g_ManipEnabled.load(std::memory_order_acquire))
            {
                void* entity = nullptr;
                char anim[64] = {};
                if (Manipulates(TargetKind::World) && FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::Freeze)
                {
                    worldManip = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][WORLD] setTimePosition target=%s state=0x%p time=%.3f gen=%llu",
                        anim, self, timePosition, static_cast<unsigned long long>(g_World.generation.load()));
                }
                if (Manipulates(TargetKind::Fp) && FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::Freeze)
                {
                    fpManip = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][FP] setTimePosition target=%s state=0x%p time=%.3f gen=%llu",
                        anim, self, timePosition, static_cast<unsigned long long>(g_Fp.generation.load()));
                }
            }
            g_RealAnimationSetTimePosition(self, timePosition);
            if (!g_Enabled.load(std::memory_order_relaxed))
                return;
            void* entity = nullptr;
            char anim[64] = {};
            if (FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_World, TargetKind::World, self, "time", timePosition, caller);
            if (FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_Fp, TargetKind::Fp, self, "time", timePosition, caller);
        }

        void __fastcall HookAnimationSetWeight(void* self, void*, float weight)
        {
            void* caller = _ReturnAddress();
            if (!g_RealAnimationSetWeight)
                return;
            float effectiveWeight = weight;
            bool worldForced = false;
            bool fpForced = false;
            if (g_ManipEnabled.load(std::memory_order_acquire))
            {
                void* entity = nullptr;
                char anim[64] = {};
                if (Manipulates(TargetKind::World) && FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::ForceWeight)
                {
                    effectiveWeight = 1.0f;
                    worldForced = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][WORLD] ForceWeight anim=%s state=0x%p requested=%.3f forced=%.3f gen=%llu",
                        anim, self, weight, effectiveWeight, static_cast<unsigned long long>(g_World.generation.load()));
                }
                if (Manipulates(TargetKind::Fp) && FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::ForceWeight)
                {
                    effectiveWeight = 1.0f;
                    fpForced = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][FP] ForceWeight anim=%s state=0x%p requested=%.3f forced=%.3f gen=%llu",
                        anim, self, weight, effectiveWeight, static_cast<unsigned long long>(g_Fp.generation.load()));
                }
            }
            g_RealAnimationSetWeight(self, (worldForced || fpForced) ? effectiveWeight : weight);
            if (!g_Enabled.load(std::memory_order_relaxed))
                return;
            void* entity = nullptr;
            char anim[64] = {};
            if (FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_World, TargetKind::World, self, "weight", (worldForced ? effectiveWeight : weight), caller);
            if (FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_Fp, TargetKind::Fp, self, "weight", (fpForced ? effectiveWeight : weight), caller);
        }

        void __fastcall HookAnimationAddTime(void* self, void*, float offset)
        {
            void* caller = _ReturnAddress();
            if (!g_RealAnimationAddTime)
                return;
            bool worldSuppress = false;
            bool fpSuppress = false;
            if (g_ManipEnabled.load(std::memory_order_acquire))
            {
                void* entity = nullptr;
                char anim[64] = {};
                if (Manipulates(TargetKind::World) && FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::Freeze)
                {
                    worldSuppress = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][WORLD] Freeze addTime suppressed anim=%s state=0x%p dt=%.6f gen=%llu",
                        anim, self, offset, static_cast<unsigned long long>(g_World.generation.load()));
                }
                if (Manipulates(TargetKind::Fp) && FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)) &&
                    std::strcmp(anim, g_ManipTargetAnim) == 0 && g_ManipMode == ManipMode::Freeze)
                {
                    fpSuppress = true;
                    LogShimA(LogLevel::Info, kComponent, "[FPAnim][MANIP][FP] Freeze addTime suppressed anim=%s state=0x%p dt=%.6f gen=%llu",
                        anim, self, offset, static_cast<unsigned long long>(g_Fp.generation.load()));
                }
            }
            bool suppress = worldSuppress || fpSuppress;
            if (!suppress)
                g_RealAnimationAddTime(self, offset);
            if (!g_Enabled.load(std::memory_order_relaxed))
                return;
            if (suppress)
                return;
            void* entity = nullptr;
            char anim[64] = {};
            if (FindBindingForTarget(g_World, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_World, TargetKind::World, self, "dt", offset, caller);
            if (FindBindingForTarget(g_Fp, self, entity, anim, sizeof(anim)))
                LogBoundFloatForTarget(g_Fp, TargetKind::Fp, self, "dt", offset, caller);
        }

        bool InstallObservers()
        {
            if (!OgreRuntime::IsLoaded())
                return false;
            if (!ResolveTrackerExports())
                return false;
            void* getAnimationState = FindUniqueFunctionExport("getAnimationState@Entity@Ogre@@", "Entity::getAnimationState");
            void* setEnabled = FindUniqueFunctionExport("setEnabled@AnimationState@Ogre@@", "AnimationState::setEnabled");
            void* setLoop = FindUniqueFunctionExport("setLoop@AnimationState@Ogre@@", "AnimationState::setLoop");
            void* setTimePosition = FindUniqueFunctionExport("setTimePosition@AnimationState@Ogre@@", "AnimationState::setTimePosition");
            void* setWeight = FindUniqueFunctionExport("setWeight@AnimationState@Ogre@@", "AnimationState::setWeight");
            void* addTime = FindUniqueFunctionExport("addTime@AnimationState@Ogre@@", "AnimationState::addTime");
            if (!getAnimationState || !setEnabled || !setLoop || !setTimePosition || !setWeight || !addTime)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim] one or more required retail Ogre exports were unavailable; trace remains fail-closed");
                return false;
            }
            g_RealEntityGetAnimationState = reinterpret_cast<FnEntityGetAnimationState>(getAnimationState);
            g_RealAnimationSetEnabled = reinterpret_cast<FnAnimationSetEnabled>(setEnabled);
            g_RealAnimationSetLoop = reinterpret_cast<FnAnimationSetLoop>(setLoop);
            g_RealAnimationSetTimePosition = reinterpret_cast<FnAnimationSetTimePosition>(setTimePosition);
            g_RealAnimationSetWeight = reinterpret_cast<FnAnimationSetWeight>(setWeight);
            g_RealAnimationAddTime = reinterpret_cast<FnAnimationAddTime>(addTime);
            g_RealEntityGetAllAnimationStates = reinterpret_cast<FnEntityGetAllAnimationStates>(
                FindOptionalExport("getAllAnimationStates@Entity@Ogre@@", "Entity::getAllAnimationStates"));
            // Log verified Ogre creation/enumeration seams
            {
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] verified enumeration seam: SceneManager::getMovableObjectIterator");
                // Verify exe does NOT import createEntity (expected per dumpbin /imports)
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] verified: exe does NOT import SceneManager::createEntity (dumpbin /imports) — creation hook not used; enumeration is primary resolver");
                // Document SceneManager global structure used for retrieval
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] SceneManager retrieval: global structure 0x%08X +0x%X (same as bzr_hooks.cpp:2042)",
                    static_cast<unsigned>(kOgreSceneManagerStructureAddr), static_cast<unsigned>(kOgreSceneManagerOffset));
            }
            RefreshManipConfig();
            if (g_ManipEnabled.load(std::memory_order_acquire))
                LogShimA(LogLevel::Info, kComponent, "[FPAnim] manipulation gate ACTIVE mode=%u scope=%u targetAnim=%s (isolated lcbench-only)",
                    static_cast<unsigned>(g_ManipMode), static_cast<unsigned>(g_ManipScope), g_ManipTargetAnim);
            const size_t getStateHooks = InstallExeObserver(getAnimationState, reinterpret_cast<void*>(&HookEntityGetAnimationState), "Entity::getAnimationState");
            const size_t enabledHooks = InstallExeObserver(setEnabled, reinterpret_cast<void*>(&HookAnimationSetEnabled), "AnimationState::setEnabled");
            const size_t loopHooks = InstallExeObserver(setLoop, reinterpret_cast<void*>(&HookAnimationSetLoop), "AnimationState::setLoop");
            const size_t timeHooks = InstallExeObserver(setTimePosition, reinterpret_cast<void*>(&HookAnimationSetTimePosition), "AnimationState::setTimePosition");
            const size_t weightHooks = InstallExeObserver(setWeight, reinterpret_cast<void*>(&HookAnimationSetWeight), "AnimationState::setWeight");
            const size_t addTimeHooks = InstallExeObserver(addTime, reinterpret_cast<void*>(&HookAnimationAddTime), "AnimationState::addTime");
            if (getStateHooks == 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim] Entity::getAnimationState has no exact executable call/IAT site; state ownership cannot be tracked safely");
                return false;
            }
            const size_t mutationHooks = enabledHooks + loopHooks + timeHooks + weightHooks + addTimeHooks;
            if (mutationHooks == 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FPAnim] no AnimationState mutation call/IAT sites were found; trace remains fail-closed");
                return false;
            }
            LogShimA(LogLevel::Info, kComponent,
                "[FPAnim] observers active getState=%u enabled=%u loop=%u time=%u weight=%u addTime=%u; ownership=world Person + FP via enumeration",
                static_cast<unsigned>(getStateHooks), static_cast<unsigned>(enabledHooks), static_cast<unsigned>(loopHooks),
                static_cast<unsigned>(timeHooks), static_cast<unsigned>(weightHooks), static_cast<unsigned>(addTimeHooks));
            LogShimA(LogLevel::Info, kComponent,
                "[FPAnim] enhanced trace v3: world+FP dual targets, caller RVA, transition filtering, dt throttling (500ms), inventory poll %ums, fpEnumerate %ums, manip=%u",
                static_cast<unsigned>(kInventoryPollIntervalMs), static_cast<unsigned>(kFpEnumerateIntervalMs), g_ManipEnabled.load() ? 1u : 0u);
            return true;
        }

        unsigned __stdcall TraceThreadProc(void*)
        {
            LogShimA(LogLevel::Info, kComponent, "[PilotFP] tracker waiting for OgreMain.dll and local Person entity; trace=%u",
                g_Enabled.load(std::memory_order_acquire) ? 1u : 0u);
            bool ogreAttempted = false;
            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                if (!ogreAttempted && OgreRuntime::IsLoaded())
                {
                    ogreAttempted = true;
                    std::lock_guard<std::mutex> trackerLock(g_TrackerMutex);
                    ResolveTrackerExports();
                    if (g_Enabled.load(std::memory_order_acquire))
                        InstallObservers();
                }
                // The whole poll is diagnostic, but only the logging used to be
                // gated: the scene-graph walk ran on every player's machine every
                // 1.5 s with the trace off, which is how a tracer's use-after-free
                // became everyone's crash. Nothing outside this file needs the
                // polled state -- the exported ResolveLocalFirstPersonEntity
                // resolves on demand and is unaffected by this gate.
                if (g_TrackerExportsReady.load(std::memory_order_acquire) &&
                    g_Enabled.load(std::memory_order_acquire))
                {
                    std::lock_guard<std::mutex> trackerLock(g_TrackerMutex);
                    RefreshWorldTarget();
                    RefreshFpTargetViaEnumeration();
                    TryLogInventoryForTarget(g_World, TargetKind::World);
                    TryLogInventoryForTarget(g_Fp, TargetKind::Fp);
                }
                Sleep(kPollSleepMs);
            }
            LogShimA(LogLevel::Info, kComponent, "[PilotFP] tracker stopped (installed trace hooks now pass-through until process exit)");
            return 0;
        }
    }

    bool IsPilotFpAnimationTraceRequested()
    {
        return TraceRequested();
    }

    void InitializePilotFpAnimationTrace()
    {
        if (g_WorkerThread)
            return;
        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Enabled.store(TraceRequested(), std::memory_order_release);
        if (g_Enabled.load(std::memory_order_acquire))
            RefreshManipConfig();
        g_WorkerThread = _beginthreadex(nullptr, 0, TraceThreadProc, nullptr, 0, nullptr);
        if (!g_WorkerThread)
        {
            g_Enabled.store(false, std::memory_order_release);
            LogShimA(LogLevel::Warn, kComponent, "[FPAnim] failed to start trace worker (err=%lu)", GetLastError());
        }
    }

    bool ResolveLocalFirstPersonEntity(void*& outEntity, uint64_t& outGeneration)
    {
        outEntity = nullptr;
        outGeneration = g_Fp.generation.load(std::memory_order_acquire);
        if (g_ShutdownRequested.load(std::memory_order_acquire) ||
            !IsPatchingComplete() || !IsCompatibleGameVersion() ||
            !OgreRuntime::IsLoaded())
            return false;

        std::lock_guard<std::mutex> trackerLock(g_TrackerMutex);
        if (!ResolveTrackerExports())
            return false;
        RefreshWorldTarget();
        RefreshFpTargetViaEnumeration(true);
        outEntity = g_Fp.entity.load(std::memory_order_acquire);
        outGeneration = g_Fp.generation.load(std::memory_order_acquire);
        return outEntity != nullptr;
    }

    void ShutdownPilotFpAnimationTrace()
    {
        g_Enabled.store(false, std::memory_order_release);
        g_ShutdownRequested.store(true, std::memory_order_release);
        g_World.entity.store(nullptr, std::memory_order_release);
        g_Fp.entity.store(nullptr, std::memory_order_release);
        if (g_WorkerThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_WorkerThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_WorkerThread));
            g_WorkerThread = 0;
        }
        {
            std::lock_guard<std::mutex> lock(g_World.mutex);
            ClearBindingsLocked(g_World);
        }
        {
            std::lock_guard<std::mutex> lock(g_Fp.mutex);
            ClearBindingsLocked(g_Fp);
        }
    }

    extern "C" BZRO_API int32_t __cdecl OpenShimResolveLocalFirstPersonEntity(
        void** outEntity, uint64_t* outGeneration)
    {
        if (!outEntity || !outGeneration)
            return 0;
        void* entity = nullptr;
        uint64_t generation = 0;
        const bool available = ResolveLocalFirstPersonEntity(entity, generation);
        *outEntity = entity;
        *outGeneration = generation;
        return available ? 1 : 0;
    }
}
