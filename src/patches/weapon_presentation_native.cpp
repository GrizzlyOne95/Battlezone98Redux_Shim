#include "weapon_presentation_native.h"
#include "weapon_presentation_call_bridges.h"
#include "weapon_presentation_native_policy.h"
#include "weapon_presentation_hooks.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "openshim_preset_migration.h"
#include "shim_log.h"

#include <Windows.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <cstring>
#include <filesystem>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace WP = WeaponPresentation;
        namespace Policy = WP::NativePolicy;
        namespace Bridges = WP::NativeBridges;

        // Static instructions/ABI are qualified against the hash below.
        // Static analysis cannot qualify engine thread ordering, Ogre/native
        // lifetime, renderer visibility or model reload. This is deliberately
        // closed until those actual Windows tests have been recorded.
        constexpr bool kNativePresentationLiveQualified = false;
        constexpr char kGogSha256[] =
            "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413";

        // Released-layout contracts; instruction sites are catalogued in
        // scripts/patches.json, never used as addresses here.
        constexpr size_t kWeaponClass = 8;
        constexpr size_t kWeaponObject = 0x10;
        constexpr size_t kWeaponRoot = 0x18;
        constexpr size_t kWeaponMountWorld = 0x28;
        constexpr size_t kClassParent = 8;
        constexpr size_t kWeaponClassName = 0x18;
        constexpr size_t kObjectClassName = 0x30;
        constexpr size_t kCarrier = 0x1a0;
        constexpr size_t kCarrierSlots = 0x18;
        constexpr size_t kMatrix = 0x20;
        constexpr size_t kFlags = 0x14;
        constexpr uint32_t kDeadFlag = 0x200;
        constexpr size_t kRenderBackReference = 0x68;
        constexpr size_t kMaxValueBytes = 128;

        using RawGet = const char* (__thiscall*)(void*, uint32_t, uint32_t);
        using RenderFind = void* (__cdecl*)(const char*);
        using RenderBuild = void* (__thiscall*)(void*, void**, const WP::Matrix*);
        using RenderUpdate = void (__thiscall*)(void**, const WP::Matrix*);
        using RenderDetach = void (__thiscall*)(void**, const WP::Matrix*, float);
        using WeaponCtor = void* (__thiscall*)(void*, void*, void*);
        using WeaponDtor = void (__thiscall*)(void*);
        using Simulate = void (__cdecl*)(float);
        using SetWeapon = void (__thiscall*)(void*, int, void*);
        using ModelPose = void (__cdecl*)(void*, const WP::Matrix*);

        RawGet g_RawGet = nullptr;
        RenderFind g_RenderFind = nullptr;
        RenderUpdate g_RenderUpdate = nullptr;
        RenderDetach g_RenderDetach = nullptr;
        WeaponCtor g_WeaponCtor = nullptr;
        WeaponDtor g_WeaponDtor = nullptr;
        Simulate g_Simulate = nullptr;
        SetWeapon g_SetWeapon = nullptr;
        ModelPose g_ModelPose = nullptr;
        InlineDetour32 g_CtorDetour, g_DtorDetour, g_SimDetour, g_SlotDetour, g_ModelDetour;
        std::atomic<bool> g_Ready{ false };
        bool g_InstallAttempted = false;
        std::atomic<bool> g_ThreadMismatchLogged{ false };
        volatile LONG g_EngineThread = 0;
        size_t g_SceneDepth = 0;
        uint64_t g_LifetimeSerial = 0;
        uint64_t g_SimulationSerial = 0;
        WP::Settings g_Settings;

        template<class T> bool Read(const void* pointer, size_t offset, T& out) noexcept
        {
            if (!pointer) return false;
            __try
            {
                std::memcpy(&out, static_cast<const unsigned char*>(pointer) + offset, sizeof(T));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        uint64_t NextLifetime() noexcept
        {
            return g_LifetimeSerial == std::numeric_limits<uint64_t>::max()
                ? 0 : ++g_LifetimeSerial;
        }

        bool EngineThread() noexcept
        {
            const DWORD current = GetCurrentThreadId();
            const LONG owner = InterlockedCompareExchange(&g_EngineThread, static_cast<LONG>(current), 0);
            if (!owner || current == static_cast<DWORD>(owner)) return true;
            if (!g_ThreadMismatchLogged.exchange(true))
            {
                LogShimA(LogLevel::Warn, "WEAPONFX", "producer thread differs; presentation stood down");
            }
            return false;
        }

        bool EnsureRuntime() noexcept;

        WP::Runtime* ActiveRuntime() noexcept
        {
            return g_Ready && EngineThread() && g_SceneDepth == 0 && EnsureRuntime()
                ? TryGetSingleplayerWeaponPresentationRuntime() : nullptr;
        }

        void WaitForInstallation()
        {
            if (!g_Ready)
            {
                // Install holds the outer code lock through trampoline pointer
                // publication. A thread resumed after an individual code write
                // must not call a not-yet-published original pointer.
                HookEngine::CodePatchLock lock;
            }
        }

        struct ClassFlash { uint64_t name = 0; WP::FlashConfig config; };
        struct CraftConfig { uint64_t name = 0; std::array<std::optional<WP::MeshId>, 5> nodes; };
        struct WeaponState
        {
            uint64_t lifetime = 0;
            uint64_t shot = 0;
            WP::BindingToken token;
            WP::Identity owner;
            WP::Identity node;
            void* root = nullptr;
            void* object = nullptr;
            WP::Matrix correction = WeaponConvergence::Identity();
        };
        struct NodeState
        {
            void* root = nullptr;
            WP::MeshId id = {};
            WP::Matrix rest = WeaponConvergence::Identity();
            bool supported = true;
        };
        using NodeKey = std::pair<WP::Identity, WP::Identity>;
        std::unordered_map<void*, ClassFlash> g_FlashClasses;
        std::unordered_map<void*, CraftConfig> g_CraftClasses;
        std::unordered_map<void*, WeaponState> g_Weapons;
        std::map<NodeKey, NodeState> g_Nodes;
        std::unordered_map<uintptr_t, NodeKey> g_NodeByAddress;

        enum class ValueStatus { Missing, Present, Invalid };
        // Copy while Redux's own scope is alive. No parser string escapes it.
        ValueStatus ReadValue(void* scope, uint32_t section, uint32_t key,
            char (&out)[kMaxValueBytes]) noexcept
        {
            __try
            {
                const char* value = g_RawGet(scope, section, key);
                if (!value) return ValueStatus::Missing;
                for (size_t i = 0; i < kMaxValueBytes; ++i)
                {
                    out[i] = value[i];
                    if (!out[i]) return ValueStatus::Present;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            out[0] = 0;
            return ValueStatus::Invalid;
        }

        void __cdecl ObserveWeaponClass(void* scope, void* objectClass) noexcept
        {
            if (!g_Ready || !EngineThread() || !scope || !objectClass) return;
            g_FlashClasses.erase(objectClass); // failed/reloaded read cannot retain stale configuration
            try
            {
                ClassFlash result;
                void* parent = nullptr;
                if (!Read(objectClass, kWeaponClassName, result.name) ||
                    !Read(objectClass, kClassParent, parent)) return;
                WP::FlashConfig inherited;
                auto found = g_FlashClasses.find(parent);
                uint64_t parentName = 0;
                if (found != g_FlashClasses.end() && Read(parent, kWeaponClassName, parentName) &&
                    parentName == found->second.name) inherited = found->second.config;
                char name[kMaxValueBytes] = {}, duration[kMaxValueBytes] = {};
                const auto ns = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash("flashName"), name);
                const auto ds = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash("flashDuration"), duration);
                const auto parsedName = Policy::Name(name);
                std::optional<std::string_view> nameValue;
                std::optional<float> durationValue;
                if (ns != ValueStatus::Missing)
                    nameValue = ns == ValueStatus::Present && parsedName && parsedName->size() < 64
                        ? *parsedName : std::string_view{};
                if (ds != ValueStatus::Missing)
                    durationValue = ds == ValueStatus::Present ? Policy::Duration(duration)
                        : std::numeric_limits<float>::quiet_NaN();
                result.config = WP::ResolveFlashConfig(inherited, nameValue, durationValue);
                if (g_FlashClasses.size() < WP::kMaxBindings || g_FlashClasses.count(objectClass))
                    g_FlashClasses.insert_or_assign(objectClass, std::move(result));
            }
            catch (...) {} // ODF extension allocation must never abort stock loading
        }

        void __cdecl ObserveCraftClass(void* scope, void* objectClass) noexcept
        {
            if (!g_Ready || !EngineThread() || !scope || !objectClass) return;
            g_CraftClasses.erase(objectClass);
            try
            {
                CraftConfig result;
                if (!Read(objectClass, kObjectClassName, result.name)) return;
                constexpr std::array<std::string_view, 5> keys =
                    { "recoilName1", "recoilName2", "recoilName3", "recoilName4", "recoilName5" };
                for (size_t i = 0; i < keys.size(); ++i)
                {
                    char value[kMaxValueBytes] = {};
                    if (ReadValue(scope, Policy::Hash("CraftClass"), Policy::Hash(keys[i]), value) !=
                        ValueStatus::Present) continue;
                    const auto name = Policy::Name(value);
                    if (name) result.nodes[i] = WP::ParseMeshId(*name);
                }
                if (g_CraftClasses.size() < WP::kMaxBindings || g_CraftClasses.count(objectClass))
                    g_CraftClasses.insert_or_assign(objectClass, std::move(result));
            }
            catch (...) {}
        }

        bool ReadMesh(uintptr_t address, WP::MeshNodeView& node, void*)
        {
            void* ptr = reinterpret_cast<void*>(address);
            uint32_t flags = 0;
            return Read(ptr, kFlags, flags) && !(flags & kDeadFlag) &&
                Read(ptr, 8, node.id) && Read(ptr, 0x80, node.child) && Read(ptr, 0x7c, node.sibling);
        }

        bool LiveOwner(const WP::Identity& owner, void* root) noexcept
        {
            void* object = reinterpret_cast<void*>(owner.address);
            int handle = 0;
            void* currentRoot = nullptr;
            uint32_t flags = 0;
            return owner.Valid() && TryGetGameObjectHandleValue(object, handle) &&
                static_cast<uint32_t>(handle) == owner.lifetime &&
                GameObjectFromHandleGog(handle) == object &&
                TryGetGameObjectObj76(object, currentRoot) && currentRoot == root &&
                Read(root, kFlags, flags) && !(flags & kDeadFlag);
        }

        bool CurrentWeaponPose(void* weapon, const WeaponState& state, WP::Matrix& pose) noexcept
        {
            void* root = nullptr;
            void* object = nullptr;
            WP::Matrix local, mount;
            if (!LiveOwner(state.owner, state.root) || !Read(weapon, kWeaponRoot, root) ||
                root != state.root || !Read(weapon, kWeaponObject, object) || object != state.object ||
                !Read(object, kMatrix, local) || !Read(weapon, kWeaponMountWorld, mount) ||
                !WP::ValidPose(local) || !WP::ValidPose(mount)) return false;
            pose = WeaponConvergence::Multiply(local, mount);
            return WP::ValidPose(pose);
        }

        void ReleaseWeapon(WeaponState& state) noexcept
        {
            if (auto* runtime = TryGetSingleplayerWeaponPresentationRuntime())
                runtime->Release(state.token);
            state.token = {};
            state.shot = 0;
            state.node = {};
        }

        bool ReadObjectClass(void* object, void*& objectClass) noexcept
        {
            __try
            {
                void* sub = static_cast<unsigned char*>(object) + kGameObjectClassSubObjOffset;
                using GetClass = void* (__thiscall*)(void*);
                auto vtable = *reinterpret_cast<void***>(sub);
                objectClass = reinterpret_cast<GetClass>(vtable[0])(sub);
                return objectClass != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        void BindRecoil(void* weapon, WeaponState& state, WP::BindRequest& request)
        {
            if (!g_Settings.meshRecoil) return;
            void* owner = reinterpret_cast<void*>(state.owner.address);
            void* carrier = nullptr;
            void* objectClass = nullptr;
            if (!Read(owner, kCarrier, carrier) || !ReadObjectClass(owner, objectClass)) return;
            const auto config = g_CraftClasses.find(objectClass);
            uint64_t name = 0;
            if (config == g_CraftClasses.end() || !Read(objectClass, kObjectClassName, name) ||
                name != config->second.name) return;
            int selected = -1;
            for (int slot = 0; slot < 5; ++slot)
            {
                void* candidate = nullptr;
                if (!Read(carrier, kCarrierSlots + slot * sizeof(void*), candidate)) return;
                if (candidate == weapon)
                {
                    if (selected != -1) return; // ambiguous native slot identity
                    selected = slot;
                }
            }
            if (selected < 0 || !config->second.nodes[selected]) return;
            const auto id = *config->second.nodes[selected];
            const auto found = WP::FindMeshNode(reinterpret_cast<uintptr_t>(state.root), id, ReadMesh, nullptr);
            WP::Matrix rest;
            if (found.status != WP::MeshLookupStatus::Found ||
                !Read(reinterpret_cast<void*>(found.node), kMatrix, rest) || !WP::ValidPose(rest)) return;
            auto index = g_NodeByAddress.find(found.node);
            if (index != g_NodeByAddress.end())
            {
                auto old = g_Nodes.find(index->second);
                if (index->second.first == state.owner && old != g_Nodes.end() &&
                    old->second.root == state.root && old->second.id == id && old->second.supported)
                    state.node = index->second.second;
                else return; // lifetime/reload disagreement must be qualified, never guessed
            }
            else
            {
                if (g_Nodes.size() >= WP::kMaxBindings) return;
                const auto generation = NextLifetime();
                if (!generation) return;
                state.node = { found.node, generation };
                const NodeKey key = { state.owner, state.node };
                g_Nodes.emplace(key, NodeState{ state.root, id, rest, true });
                try { g_NodeByAddress.emplace(found.node, key); }
                catch (...) { g_Nodes.erase(key); state.node = {}; throw; }
            }
            request.recoil = WP::RecoilBinding{ state.node, rest };
        }

        void __cdecl ObserveShot(void* weapon, const WP::Matrix* finalPose,
            void* ownerRoot, void* ordnance) noexcept
        {
            auto* runtime = ActiveRuntime();
            if (!runtime || !ordnance || !weapon || !finalPose) return;
            try
            {
                auto found = g_Weapons.find(weapon);
                if (found == g_Weapons.end()) return; // constructor/lifetime seam was missed
                auto& state = found->second;
                WP::Matrix committed;
                if (!Read(finalPose, 0, committed) || !WP::ValidPose(committed)) return;
                if (!state.token.Valid())
                {
                    void* object = nullptr;
                    int handle = 0;
                    if (!Read(weapon, kWeaponRoot, state.root) || state.root != ownerRoot ||
                        !Read(weapon, kWeaponObject, state.object) ||
                        !TryGetGameObjectFromObj76(state.root, object) ||
                        !TryGetGameObjectHandleValue(object, handle)) return;
                    state.owner = { reinterpret_cast<uintptr_t>(object), static_cast<uint32_t>(handle) };
                    if (!LiveOwner(state.owner, state.root)) return;
                    WP::BindRequest request;
                    request.owner = state.owner;
                    request.weapon = { reinterpret_cast<uintptr_t>(weapon), state.lifetime };
                    void* objectClass = nullptr;
                    uint64_t name = 0;
                    if (Read(weapon, kWeaponClass, objectClass))
                    {
                        const auto config = g_FlashClasses.find(objectClass);
                        if (config != g_FlashClasses.end() && Read(objectClass, kWeaponClassName, name) &&
                            name == config->second.name) request.flash = config->second.config;
                    }
                    BindRecoil(weapon, state, request);
                    const auto token = runtime->Bind(request);
                    if (!token) return;
                    state.token = *token;
                }
                WP::Matrix current;
                if (!CurrentWeaponPose(weapon, state, current) || state.root != ownerRoot)
                { ReleaseWeapon(state); return; }
                state.correction = WeaponConvergence::Multiply(committed, WeaponConvergence::Invert(current));
                if (!WP::ValidPose(state.correction) || state.shot == std::numeric_limits<uint64_t>::max())
                { ReleaseWeapon(state); return; }
                const auto shot = runtime->Fire(state.token, ++state.shot, committed);
                if (!shot.observed) ReleaseWeapon(state); // session/scene epoch changed
            }
            catch (...) {} // native shot was already built; cosmetics cannot undo it
        }

        // Native calls are isolated from C++ objects requiring unwinding.
        bool CreateNativeFlash(const char* name, const WP::Matrix* pose, void** storage) noexcept
        {
            __try
            {
                void* objectClass = g_RenderFind(name);
                if (!objectClass) return false;
                const auto table = *reinterpret_cast<void***>(objectClass);
                reinterpret_cast<RenderBuild>(table[2])(objectClass, storage, pose);
                return *storage != nullptr &&
                    *reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) == storage;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool UpdateNativeFlash(void** storage, const WP::Matrix* pose) noexcept
        {
            __try
            {
                if (!*storage) return true;
                if (*reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) != storage)
                    return false;
                g_RenderUpdate(storage, pose); // exact same slot, never a stack-local back-reference
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool DetachNativeFlash(void** storage) noexcept
        {
            __try
            {
                if (!*storage) return true;
                if (*reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) != storage)
                    return false;
                g_RenderDetach(storage, nullptr, 0.0f); // native list retains ownership
                return *storage == nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool WriteModelPose(void* node, const WP::Matrix* pose) noexcept
        {
            __try { g_ModelPose(node, pose); return true; }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        class NativeBackend final : public WP::Backend
        {
        public:
            bool CreateFlash(std::string_view effect, const WP::Matrix& pose, void*& storage) noexcept override
            {
                if (storage || effect.empty() || effect.size() >= 64 || !WP::ValidPose(pose)) return false;
                char name[64] = {};
                std::memcpy(name, effect.data(), effect.size());
                return CreateNativeFlash(name, &pose, &storage);
            }
            bool UpdateFlash(void*& storage, const WP::Matrix& pose) noexcept override
            { return WP::ValidPose(pose) && UpdateNativeFlash(&storage, &pose); }
            bool DetachFlash(void*& storage) noexcept override
            { return DetachNativeFlash(&storage); }
            bool ApplyRecoil(const WP::Identity& owner, const WP::Identity& node,
                const WP::Matrix& visual) noexcept override
            {
                try
                {
                    const auto found = g_Nodes.find({ owner, node });
                    if (found == g_Nodes.end() || !LiveOwner(owner, found->second.root)) return true;
                    const auto match = WP::FindMeshNode(reinterpret_cast<uintptr_t>(found->second.root),
                        found->second.id, ReadMesh, nullptr);
                    if (match.status != WP::MeshLookupStatus::Found || match.node != node.address) return true;
                    WP::Matrix current;
                    if (!Read(reinterpret_cast<void*>(node.address), kMatrix, current) || !WP::ValidPose(current))
                        return false;
                    const auto& rest = found->second.rest;
                    if (!found->second.supported || current.positionX != rest.positionX ||
                        current.positionY != rest.positionY || current.positionZ != rest.positionZ)
                    {
                        found->second.supported = false;
                        return WriteModelPose(reinterpret_cast<void*>(node.address), &current);
                    }
                    return WP::ValidPose(visual) && WriteModelPose(reinterpret_cast<void*>(node.address), &visual);
                }
                catch (...) { return false; }
            }
        };
        NativeBackend g_Backend; // must survive outstanding native back-references until process exit

        bool EnsureRuntime() noexcept
        {
            static bool registered = false;
            if (!registered)
            {
                try { registered = RegisterQualifiedWeaponPresentationBackend(g_Backend, g_Settings); }
                catch (...) { return false; }
            }
            return registered;
        }

        void* __fastcall WeaponCtorHook(void* weapon, void*, void* object, void* objectClass)
        {
            WaitForInstallation();
            if (g_Ready && EngineThread())
            {
                const auto previous = g_Weapons.find(weapon);
                if (previous != g_Weapons.end())
                {
                    ReleaseWeapon(previous->second);
                    g_Weapons.erase(previous);
                    RefreshWeaponPresentationState();
                }
            }
            void* result = g_WeaponCtor(weapon, object, objectClass);
            if (g_Ready && EngineThread() && result)
            {
                try
                {
                    const auto lifetime = NextLifetime();
                    if (lifetime && g_Weapons.size() < WP::kMaxBindings)
                    {
                        WeaponState state; state.lifetime = lifetime;
                        g_Weapons.insert_or_assign(result, state);
                    }
                }
                catch (...) {}
            }
            return result;
        }

        void __fastcall WeaponDtorHook(void* weapon, void*)
        {
            WaitForInstallation();
            if (g_Ready && EngineThread())
            {
                auto found = g_Weapons.find(weapon);
                if (found != g_Weapons.end()) { ReleaseWeapon(found->second); g_Weapons.erase(found); }
                RefreshWeaponPresentationState(); // detach before original native object destruction
            }
            g_WeaponDtor(weapon);
        }

        void __cdecl SimulationHook(float dt)
        {
            WaitForInstallation();
            if (auto* runtime = ActiveRuntime())
            {
                if (g_SimulationSerial != std::numeric_limits<uint64_t>::max())
                    runtime->BeginSimulationStep(++g_SimulationSerial, dt);
            }
            g_Simulate(dt); // no dt from render or wall clock
        }

        void __fastcall SetWeaponHook(void* carrier, void*, int slot, void* weapon)
        {
            WaitForInstallation();
            void* previous = nullptr;
            if (g_Ready && EngineThread() && slot >= 0 && slot < 5 &&
                Read(carrier, kCarrierSlots + slot * sizeof(void*), previous) && previous != weapon)
            {
                auto found = g_Weapons.find(previous);
                if (found != g_Weapons.end()) ReleaseWeapon(found->second);
                RefreshWeaponPresentationState();
            }
            g_SetWeapon(carrier, slot, weapon);
        }

        void __cdecl ModelPoseHook(void* node, const WP::Matrix* nativePose)
        {
            WaitForInstallation();
            if (!g_Ready || !EngineThread()) { g_ModelPose(node, nativePose); return; }
            auto index = g_NodeByAddress.find(reinterpret_cast<uintptr_t>(node));
            if (index != g_NodeByAddress.end())
            {
                if (auto* runtime = ActiveRuntime())
                {
                    const auto key = index->second;
                    auto record = g_Nodes.find(key);
                    WP::Matrix copy, visual;
                    if (record != g_Nodes.end() && record->second.supported &&
                        LiveOwner(key.first, record->second.root) && Read(nativePose, 0, copy))
                    {
                        const auto& rest = record->second.rest;
                        if (copy.positionX != rest.positionX || copy.positionY != rest.positionY ||
                            copy.positionZ != rest.positionZ || !WP::ValidPose(copy))
                        { record->second.supported = false; g_ModelPose(node, nativePose); return; }
                        if (runtime->SetRecoilPose(key.first, key.second, copy) &&
                            runtime->TryGetVisualRecoilPose(key.first, key.second, visual))
                        { g_ModelPose(node, &visual); return; }
                    }
                }
            }
            g_ModelPose(node, nativePose); // gameplay input is never modified
        }

        bool ExactGogImage()
        {
            wchar_t path[32768] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, static_cast<DWORD>(std::size(path)));
            if (!length || length >= std::size(path)) return false;
            std::string hash;
            return TryComputeFileSha256Hex(std::filesystem::path(path), hash) && hash == kGogSha256;
        }

        bool ReplaceCall(uint32_t site, void* target, void* original)
        {
            uint8_t bytes[5] = {};
            if (!HookEngine::ReadMemory(site, bytes, sizeof(bytes)) || bytes[0] != 0xe8 ||
                HookEngine::ResolveRelCallTarget(site) != original) return false;
            auto payload = HookEngine::MakeJmp5Payload(site, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)));
            payload[0] = 0xe8;
            return HookEngine::ApplyPatch({ site, HookEngine::PatchType::BYTES, std::move(payload),
                "Weapon presentation scoped call", true, std::vector<uint8_t>(bytes, bytes + 5) });
        }

        bool InstallCandidate()
        {
            // Resolve all semantic sites first. Partial install leaves observers
            // stood down; every already installed wrapper still forwards stock.
            const uint32_t ctor = HookEngine::ResolveNamedAddress("WeaponPresentation::WeaponCtor");
            const uint32_t dtor = HookEngine::ResolveNamedAddress("WeaponPresentation::WeaponDtor");
            const uint32_t sim = HookEngine::ResolveNamedAddress("WeaponPresentation::SimulationPass");
            const uint32_t slot = HookEngine::ResolveNamedAddress("WeaponPresentation::SetWeapon");
            const uint32_t model = HookEngine::ResolveNamedAddress("WeaponPresentation::ModelPose");
            const uint32_t fire = HookEngine::ResolveNamedAddress("WeaponPresentation::CannonShotCall");
            const uint32_t weaponPop = HookEngine::ResolveNamedAddress("WeaponPresentation::WeaponClassPopCall");
            const uint32_t craftPop = HookEngine::ResolveNamedAddress("WeaponPresentation::CraftClassPopCall");
            const uint32_t factory = HookEngine::ResolveNamedAddress("WeaponPresentation::OrdnanceFactory");
            const uint32_t pop = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
            const uint32_t rawGet = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
            const uint32_t find = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderFind");
            const uint32_t update = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderUpdate");
            const uint32_t detach = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderDetach");
            if (!ctor || !dtor || !sim || !slot || !model || !fire || !weaponPop || !craftPop ||
                !factory || !pop || !rawGet || !find || !update || !detach) return false;
            if (HookEngine::ResolveRelCallTarget(fire) != reinterpret_cast<void*>(factory) ||
                HookEngine::ResolveRelCallTarget(weaponPop) != reinterpret_cast<void*>(pop) ||
                HookEngine::ResolveRelCallTarget(craftPop) != reinterpret_cast<void*>(pop)) return false;
            g_RawGet = reinterpret_cast<RawGet>(rawGet);
            g_RenderFind = reinterpret_cast<RenderFind>(find);
            g_RenderUpdate = reinterpret_cast<RenderUpdate>(update);
            g_RenderDetach = reinterpret_cast<RenderDetach>(detach);
            Bridges::Configure(reinterpret_cast<Bridges::Factory>(factory), reinterpret_cast<Bridges::PopScope>(pop),
                ObserveShot, ObserveWeaponClass, ObserveCraftClass);
            constexpr uint8_t ctorBytes[] = { 0x55, 0x8b, 0xec, 0x81, 0xec, 0xe4, 0x00, 0x00, 0x00 };
            constexpr uint8_t commonBytes[] = { 0x55, 0x8b, 0xec, 0x83, 0xec, 0x18 };
            constexpr uint8_t dtorBytes[] = { 0x55, 0x8b, 0xec, 0x83, 0xec, 0x1c };
            constexpr uint8_t slotBytes[] = { 0x55, 0x8b, 0xec, 0x51, 0x89, 0x4d, 0xfc };
            constexpr uint8_t modelBytes[] = { 0x55, 0x8b, 0xec, 0x83, 0xec, 0x3c };
            if (!InstallInlineDetour32(g_CtorDetour, ctor, reinterpret_cast<void*>(WeaponCtorHook), 9,
                    ctorBytes, sizeof(ctorBytes))) return false;
            g_WeaponCtor = reinterpret_cast<WeaponCtor>(g_CtorDetour.trampoline);
            if (!InstallInlineDetour32(g_DtorDetour, dtor, reinterpret_cast<void*>(WeaponDtorHook), 6,
                    dtorBytes, sizeof(dtorBytes))) return false;
            g_WeaponDtor = reinterpret_cast<WeaponDtor>(g_DtorDetour.trampoline);
            if (!InstallInlineDetour32(g_SimDetour, sim, reinterpret_cast<void*>(SimulationHook), 6,
                    commonBytes, sizeof(commonBytes))) return false;
            g_Simulate = reinterpret_cast<Simulate>(g_SimDetour.trampoline);
            if (!InstallInlineDetour32(g_SlotDetour, slot, reinterpret_cast<void*>(SetWeaponHook), 7,
                    slotBytes, sizeof(slotBytes))) return false;
            g_SetWeapon = reinterpret_cast<SetWeapon>(g_SlotDetour.trampoline);
            if (!InstallInlineDetour32(g_ModelDetour, model, reinterpret_cast<void*>(ModelPoseHook), 6,
                    modelBytes, sizeof(modelBytes))) return false;
            g_ModelPose = reinterpret_cast<ModelPose>(g_ModelDetour.trampoline);
            if (!ReplaceCall(fire, reinterpret_cast<void*>(Bridges::CannonOrdnanceCallBridge), reinterpret_cast<void*>(factory)) ||
                !ReplaceCall(weaponPop, reinterpret_cast<void*>(Bridges::WeaponClassScopePopBridge), reinterpret_cast<void*>(pop)) ||
                !ReplaceCall(craftPop, reinterpret_cast<void*>(Bridges::CraftClassScopePopBridge), reinterpret_cast<void*>(pop))) return false;
            g_Ready = true;
            return true;
        }
    }

    void InstallWeaponPresentationNativeIfRequested() noexcept
    {
        HookEngine::CodePatchLock lock;
        if (g_InstallAttempted) return;
        g_InstallAttempted = true;
        try
        {
            TryGetUserConfigBool("SinglePlayer", "MuzzleFlash", g_Settings.muzzleFlash);
            TryGetUserConfigBool("SinglePlayer", "MeshRecoil", g_Settings.meshRecoil);
            if (!g_Settings.muzzleFlash && !g_Settings.meshRecoil) return;
            if (!kNativePresentationLiveQualified)
            {
                LogShimA(LogLevel::Warn, "WEAPONFX", "native candidate inactive: Windows lifetime/order qualification pending");
                return;
            }
            if (!g_MissionSeamInstalled || !ExactGogImage() || !InstallCandidate())
                LogShimA(LogLevel::Warn, "WEAPONFX", "native candidate inactive: build/site/lifecycle guard failed");
        }
        catch (...) { LogShimA(LogLevel::Warn, "WEAPONFX", "native candidate installation failed; stock firing retained"); }
    }

    void RefreshWeaponPresentationNativePoses() noexcept
    {
        auto* runtime = ActiveRuntime();
        if (!runtime) return;
        try
        {
            for (auto& entry : g_Weapons)
            {
                auto& state = entry.second;
                if (!state.token.Valid()) continue;
                WP::Matrix current;
                if (!CurrentWeaponPose(entry.first, state, current)) { ReleaseWeapon(state); continue; }
                const auto muzzle = WeaponConvergence::Multiply(state.correction, current);
                if (!runtime->SetMuzzlePose(state.token, muzzle)) { ReleaseWeapon(state); continue; }
                if (state.node.Valid())
                {
                    WP::Matrix local;
                    auto node = g_Nodes.find({ state.owner, state.node });
                    if (node == g_Nodes.end() || !node->second.supported ||
                        !Read(reinterpret_cast<void*>(state.node.address), kMatrix, local) ||
                        !runtime->SetRecoilPose(state.owner, state.node, local))
                        ReleaseWeapon(state);
                }
            }
        }
        catch (...) {}
    }

    void RetireWeaponPresentationNativeBindings() noexcept
    {
        if (!g_Ready || !EngineThread()) return;
        for (auto& entry : g_Weapons) ReleaseWeapon(entry.second);
        // Keep node records through the restoration pass and through failed
        // restoration retries; only actual outer scene destruction forgets them.
    }

    void WeaponPresentationNativeSceneBegin() noexcept
    {
        if (g_Ready && EngineThread()) ++g_SceneDepth;
    }

    void WeaponPresentationNativeSceneComplete() noexcept
    {
        if (!g_Ready || !EngineThread() || !g_SceneDepth) return;
        if (--g_SceneDepth == 0)
        {
            g_Nodes.clear();
            g_NodeByAddress.clear();
        }
    }

    bool WeaponPresentationNativeThreadAllowed() noexcept
    {
        return !g_Ready || EngineThread();
    }
}
