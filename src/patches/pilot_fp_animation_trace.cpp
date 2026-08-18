#include "pilot_fp_animation_trace.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>

#include <array>
#include <atomic>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "pilot-fp-anim";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "TracePilotFPAnimations";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_TRACE_PILOT_FP_ANIMATIONS";
        constexpr DWORD kPollSleepMs = 25;
        constexpr size_t kMaxBindings = 64;

        using FnEntityGetAnimationState = void* (__thiscall*)(void*, const std::string&);
        using FnEntityGetMesh = const void* (__thiscall*)(void*);
        using FnResourceGetName = const std::string& (__thiscall*)(void*);
        using FnAnimationSetEnabled = void(__thiscall*)(void*, bool);
        using FnAnimationSetLoop = void(__thiscall*)(void*, bool);
        using FnAnimationSetTimePosition = void(__thiscall*)(void*, float);
        using FnAnimationSetWeight = void(__thiscall*)(void*, float);
        using FnAnimationAddTime = void(__thiscall*)(void*, float);

        struct PointerPatch
        {
            void** slot = nullptr;
            void* original = nullptr;
        };

        struct Rel32Patch
        {
            uint8_t* operand = nullptr;
            int32_t original = 0;
        };

        struct ExportMatch
        {
            std::string name;
            void* address = nullptr;
        };

        struct TraceBinding
        {
            std::atomic<void*> state{ nullptr };
            void* entity = nullptr;
            char animation[64] = {};
            char mesh[64] = {};
        };

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_HooksInstalled{ false };
        uintptr_t g_WorkerThread = 0;

        std::mutex g_PatchMutex;
        std::vector<PointerPatch> g_PointerPatches;
        std::vector<Rel32Patch> g_Rel32Patches;

        std::mutex g_BindingMutex;
        std::array<TraceBinding, kMaxBindings> g_Bindings{};

        FnEntityGetAnimationState g_RealEntityGetAnimationState = nullptr;
        FnEntityGetMesh g_EntityGetMesh = nullptr;
        FnResourceGetName g_ResourceGetName = nullptr;
        FnAnimationSetEnabled g_RealAnimationSetEnabled = nullptr;
        FnAnimationSetLoop g_RealAnimationSetLoop = nullptr;
        FnAnimationSetTimePosition g_RealAnimationSetTimePosition = nullptr;
        FnAnimationSetWeight g_RealAnimationSetWeight = nullptr;
        FnAnimationAddTime g_RealAnimationAddTime = nullptr;

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
                kEnvironmentSwitch,
                envValue,
                static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);

            const std::string iniPath = GetOpenShimIniPath();
            return GetPrivateProfileIntA(kIniSection, kIniKey, 1, iniPath.c_str()) != 0;
        }

        void* ReadFirstPointer(const void* address)
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
            return OgreRuntime::ContainsAddress(ReadFirstPointer(object));
        }

        bool IsPilotFpMeshName(const std::string& meshName)
        {
            std::string normalized;
            normalized.reserve(meshName.size());
            for (char ch : meshName)
            {
                char out = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                if (out == '\\')
                    out = '/';
                normalized.push_back(out);
            }

            const size_t slash = normalized.find_last_of('/');
            const std::string base = slash == std::string::npos
                ? normalized
                : normalized.substr(slash + 1);
            return base == "aspilo_fp.mesh" || base == "aspilo_fp";
        }

        bool TryGetPilotFpMeshName(void* entity, std::string& meshName)
        {
            if (!entity || !g_EntityGetMesh || !g_ResourceGetName)
                return false;

            const void* meshPtrRef = g_EntityGetMesh(entity);
            if (!meshPtrRef)
                return false;

            // Ogre::Entity::getMesh returns const MeshPtr&. The retail BZR Ogre
            // is not assumed ABI-identical to upstream, so do not dereference an
            // Ogre::MeshPtr type here. We only read the shared pointer's first
            // pointer-sized field, then require the pointee to have an OgreMain
            // vtable before invoking the semantically resolved Resource::getName.
            // If the retail shared-pointer representation ever differs, this
            // diagnostic simply declines to bind the entity.
            void* mesh = ReadFirstPointer(meshPtrRef);
            if (!LooksLikeOgreObject(mesh))
                return false;

            const std::string& resolvedName = g_ResourceGetName(mesh);
            if (!IsPilotFpMeshName(resolvedName))
                return false;

            meshName = resolvedName;
            return true;
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

        void RegisterBinding(void* state, void* entity, const std::string& animation, const std::string& mesh)
        {
            if (!state)
                return;

            bool logged = false;
            {
                std::lock_guard<std::mutex> lock(g_BindingMutex);
                TraceBinding* selected = nullptr;
                for (TraceBinding& binding : g_Bindings)
                {
                    if (binding.state.load(std::memory_order_acquire) == state)
                    {
                        selected = &binding;
                        break;
                    }
                    if (!selected && binding.state.load(std::memory_order_acquire) == nullptr)
                        selected = &binding;
                }

                if (!selected)
                {
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[FPAnim] binding table full; state=0x%p entity=0x%p anim=%s",
                        state,
                        entity,
                        animation.c_str());
                    return;
                }

                const bool changed =
                    selected->state.load(std::memory_order_acquire) != state ||
                    selected->entity != entity ||
                    std::strcmp(selected->animation, animation.c_str()) != 0;

                // Publish the pointer last so the hot-path readers never observe
                // a partially updated name/entity tuple.
                selected->state.store(nullptr, std::memory_order_release);
                selected->entity = entity;
                CopyText(selected->animation, sizeof(selected->animation), animation.c_str());
                CopyText(selected->mesh, sizeof(selected->mesh), mesh.c_str());
                selected->state.store(state, std::memory_order_release);
                logged = changed;
            }

            if (logged)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[FPAnim] entity=0x%p mesh=%s anim=%s state=0x%p bound=1",
                    entity,
                    mesh.c_str(),
                    animation.c_str(),
                    state);
            }
        }

        void UnregisterBinding(void* state)
        {
            if (!state)
                return;
            for (TraceBinding& binding : g_Bindings)
            {
                if (binding.state.load(std::memory_order_acquire) == state)
                {
                    binding.state.store(nullptr, std::memory_order_release);
                    return;
                }
            }
        }

        bool FindBinding(void* state, void*& entity, char* animation, size_t animationSize, char* mesh, size_t meshSize)
        {
            if (!state)
                return false;

            for (TraceBinding& binding : g_Bindings)
            {
                if (binding.state.load(std::memory_order_acquire) != state)
                    continue;

                entity = binding.entity;
                CopyText(animation, animationSize, binding.animation);
                CopyText(mesh, meshSize, binding.mesh);
                return binding.state.load(std::memory_order_acquire) == state;
            }
            return false;
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
                {
                    continue;
                }

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
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[FPAnim] %s export match count=%u token=%s; trace observer disabled",
                    label,
                    static_cast<unsigned>(matches.size()),
                    token);
                return nullptr;
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] resolved %s export=%s address=0x%p",
                label,
                matches[0].name.c_str(),
                matches[0].address);
            return matches[0].address;
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

            std::lock_guard<std::mutex> lock(g_PatchMutex);
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

                    const intptr_t delta =
                        reinterpret_cast<uint8_t*>(replacement) - (code + i + 5);
                    if (delta < INT32_MIN || delta > INT32_MAX)
                        continue;

                    const int32_t newRelative = static_cast<int32_t>(delta);
                    if (!WriteRel32(code + i + 1, newRelative))
                        continue;

                    g_Rel32Patches.push_back({ code + i + 1, relative });
                    ++patched;
                    i += 4;
                }
            }

            if (patched)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[FPAnim] %s direct-call observers installed=%u",
                    label,
                    static_cast<unsigned>(patched));
            }
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
            std::lock_guard<std::mutex> lock(g_PatchMutex);
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
                    g_PointerPatches.push_back({ slot, target });
                    ++patched;
                }
            }

            if (patched)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[FPAnim] %s IAT observers installed=%u",
                    label,
                    static_cast<unsigned>(patched));
            }
            return patched;
        }

        size_t InstallExeObserver(void* target, void* replacement, const char* label)
        {
            HMODULE executable = GetModuleHandleA(nullptr);
            return PatchDirectCallsInModule(executable, target, replacement, label) +
                PatchIatEntriesByTarget(executable, target, replacement, label);
        }

        void LogBoundMutation(void* state, const char* field, const char* value)
        {
            void* entity = nullptr;
            char animation[64] = {};
            char mesh[64] = {};
            if (!FindBinding(state, entity, animation, sizeof(animation), mesh, sizeof(mesh)))
                return;

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] entity=0x%p mesh=%s anim=%s state=0x%p %s=%s",
                entity,
                mesh,
                animation,
                state,
                field,
                value);
        }

        void LogBoundFloat(void* state, const char* field, float value)
        {
            void* entity = nullptr;
            char animation[64] = {};
            char mesh[64] = {};
            if (!FindBinding(state, entity, animation, sizeof(animation), mesh, sizeof(mesh)))
                return;

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] entity=0x%p mesh=%s anim=%s state=0x%p %s=%.6f",
                entity,
                mesh,
                animation,
                state,
                field,
                static_cast<double>(value));
        }

        void* __fastcall HookEntityGetAnimationState(void* self, void*, const std::string& animationName)
        {
            if (!g_RealEntityGetAnimationState)
                return nullptr;

            void* state = g_RealEntityGetAnimationState(self, animationName);
            if (!g_Enabled.load(std::memory_order_relaxed) || !state)
                return state;

            std::string meshName;
            if (TryGetPilotFpMeshName(self, meshName))
                RegisterBinding(state, self, animationName, meshName);
            else
                UnregisterBinding(state);

            return state;
        }

        void __fastcall HookAnimationSetEnabled(void* self, void*, bool enabled)
        {
            if (!g_RealAnimationSetEnabled)
                return;
            g_RealAnimationSetEnabled(self, enabled);
            if (g_Enabled.load(std::memory_order_relaxed))
                LogBoundMutation(self, "enabled", enabled ? "1" : "0");
        }

        void __fastcall HookAnimationSetLoop(void* self, void*, bool loop)
        {
            if (!g_RealAnimationSetLoop)
                return;
            g_RealAnimationSetLoop(self, loop);
            if (g_Enabled.load(std::memory_order_relaxed))
                LogBoundMutation(self, "loop", loop ? "1" : "0");
        }

        void __fastcall HookAnimationSetTimePosition(void* self, void*, float timePosition)
        {
            if (!g_RealAnimationSetTimePosition)
                return;
            g_RealAnimationSetTimePosition(self, timePosition);
            if (g_Enabled.load(std::memory_order_relaxed))
                LogBoundFloat(self, "time", timePosition);
        }

        void __fastcall HookAnimationSetWeight(void* self, void*, float weight)
        {
            if (!g_RealAnimationSetWeight)
                return;
            g_RealAnimationSetWeight(self, weight);
            if (g_Enabled.load(std::memory_order_relaxed))
                LogBoundFloat(self, "weight", weight);
        }

        void __fastcall HookAnimationAddTime(void* self, void*, float offset)
        {
            if (!g_RealAnimationAddTime)
                return;
            g_RealAnimationAddTime(self, offset);
            if (g_Enabled.load(std::memory_order_relaxed))
                LogBoundFloat(self, "dt", offset);
        }

        bool InstallObservers()
        {
            if (!OgreRuntime::IsLoaded())
                return false;

            void* getAnimationState = FindUniqueFunctionExport(
                "getAnimationState@Entity@Ogre@@",
                "Entity::getAnimationState");
            void* getMesh = FindUniqueFunctionExport(
                "getMesh@Entity@Ogre@@",
                "Entity::getMesh");
            void* getResourceName = FindUniqueFunctionExport(
                "getName@Resource@Ogre@@",
                "Resource::getName");
            void* setEnabled = FindUniqueFunctionExport(
                "setEnabled@AnimationState@Ogre@@",
                "AnimationState::setEnabled");
            void* setLoop = FindUniqueFunctionExport(
                "setLoop@AnimationState@Ogre@@",
                "AnimationState::setLoop");
            void* setTimePosition = FindUniqueFunctionExport(
                "setTimePosition@AnimationState@Ogre@@",
                "AnimationState::setTimePosition");
            void* setWeight = FindUniqueFunctionExport(
                "setWeight@AnimationState@Ogre@@",
                "AnimationState::setWeight");
            void* addTime = FindUniqueFunctionExport(
                "addTime@AnimationState@Ogre@@",
                "AnimationState::addTime");

            if (!getAnimationState || !getMesh || !getResourceName ||
                !setEnabled || !setLoop || !setTimePosition || !setWeight || !addTime)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[FPAnim] one or more required retail Ogre exports were unavailable; trace remains fail-closed");
                return false;
            }

            g_RealEntityGetAnimationState = reinterpret_cast<FnEntityGetAnimationState>(getAnimationState);
            g_EntityGetMesh = reinterpret_cast<FnEntityGetMesh>(getMesh);
            g_ResourceGetName = reinterpret_cast<FnResourceGetName>(getResourceName);
            g_RealAnimationSetEnabled = reinterpret_cast<FnAnimationSetEnabled>(setEnabled);
            g_RealAnimationSetLoop = reinterpret_cast<FnAnimationSetLoop>(setLoop);
            g_RealAnimationSetTimePosition = reinterpret_cast<FnAnimationSetTimePosition>(setTimePosition);
            g_RealAnimationSetWeight = reinterpret_cast<FnAnimationSetWeight>(setWeight);
            g_RealAnimationAddTime = reinterpret_cast<FnAnimationAddTime>(addTime);

            const size_t getStateHooks = InstallExeObserver(
                getAnimationState,
                reinterpret_cast<void*>(&HookEntityGetAnimationState),
                "Entity::getAnimationState");
            const size_t enabledHooks = InstallExeObserver(
                setEnabled,
                reinterpret_cast<void*>(&HookAnimationSetEnabled),
                "AnimationState::setEnabled");
            const size_t loopHooks = InstallExeObserver(
                setLoop,
                reinterpret_cast<void*>(&HookAnimationSetLoop),
                "AnimationState::setLoop");
            const size_t timeHooks = InstallExeObserver(
                setTimePosition,
                reinterpret_cast<void*>(&HookAnimationSetTimePosition),
                "AnimationState::setTimePosition");
            const size_t weightHooks = InstallExeObserver(
                setWeight,
                reinterpret_cast<void*>(&HookAnimationSetWeight),
                "AnimationState::setWeight");
            const size_t addTimeHooks = InstallExeObserver(
                addTime,
                reinterpret_cast<void*>(&HookAnimationAddTime),
                "AnimationState::addTime");

            if (getStateHooks == 0)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[FPAnim] Entity::getAnimationState has no exact executable call/IAT site; cannot identify AnimationState ownership safely");
                return false;
            }

            const size_t mutationHooks =
                enabledHooks + loopHooks + timeHooks + weightHooks + addTimeHooks;
            if (mutationHooks == 0)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[FPAnim] no AnimationState mutation call/IAT sites were found; trace remains fail-closed");
                return false;
            }

            g_HooksInstalled.store(true, std::memory_order_release);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] observers active getState=%u enabled=%u loop=%u time=%u weight=%u addTime=%u; target mesh=aspilo_fp.mesh",
                static_cast<unsigned>(getStateHooks),
                static_cast<unsigned>(enabledHooks),
                static_cast<unsigned>(loopHooks),
                static_cast<unsigned>(timeHooks),
                static_cast<unsigned>(weightHooks),
                static_cast<unsigned>(addTimeHooks));
            return true;
        }

        unsigned __stdcall TraceThreadProc(void*)
        {
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] enabled; read-only trace waiting for OgreMain.dll (target aspilo_fp.mesh)");

            bool attempted = false;
            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                if (!attempted && OgreRuntime::IsLoaded())
                {
                    attempted = true;
                    InstallObservers();
                }
                Sleep(kPollSleepMs);
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[FPAnim] reporter stopped (installed hooks now pass-through until process exit)");
            return 0;
        }
    }

    bool IsPilotFpAnimationTraceRequested()
    {
        return TraceRequested();
    }

    void InitializePilotFpAnimationTrace()
    {
        if (!TraceRequested())
            return;
        if (g_WorkerThread)
            return;

        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Enabled.store(true, std::memory_order_release);
        g_WorkerThread = _beginthreadex(
            nullptr,
            0,
            TraceThreadProc,
            nullptr,
            0,
            nullptr);

        if (!g_WorkerThread)
        {
            g_Enabled.store(false, std::memory_order_release);
            LogShimA(
                LogLevel::Warn,
                kComponent,
                "[FPAnim] failed to start trace worker (err=%lu)",
                GetLastError());
        }
    }

    void ShutdownPilotFpAnimationTrace()
    {
        g_Enabled.store(false, std::memory_order_release);
        g_ShutdownRequested.store(true, std::memory_order_release);

        if (g_WorkerThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_WorkerThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_WorkerThread));
            g_WorkerThread = 0;
        }
    }
}
