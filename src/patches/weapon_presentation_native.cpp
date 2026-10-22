#include "weapon_presentation_native.h"
#include "weapon_presentation_call_bridges.h"
#include "weapon_presentation_native_policy.h"
#include "odf_flash_bridge.h"
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
        // lifetime, renderer visibility or model reload. This broader/legacy
        // activation gate stays closed; settings allow the bounded authored
        // ODF experimental path below, still exact-GOG/SP and byte guarded.
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
        std::atomic<bool> g_ClassReady{ false };
        uint32_t g_WeaponScopeSite = 0;
        std::atomic<bool> g_ThreadMismatchLogged{ false };
        volatile LONG g_EngineThread = 0;
        size_t g_SceneDepth = 0;
        uint64_t g_LifetimeSerial = 0;
        uint64_t g_SimulationSerial = 0;
        WP::Settings g_Settings;
        bool g_AuthoredOdfOnly = true;
        bool g_MeshFlashUnavailableLogged = false;
        bool g_RenderUnavailableLogged = false;
        unsigned g_RenderCreates = 0, g_RenderDetaches = 0;

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

        int WriteMuzzlePoint(float* out, const WP::Matrix& pose) noexcept
        {
            __try
            {
                out[0] = static_cast<float>(pose.positionX);
                out[1] = static_cast<float>(pose.positionY);
                out[2] = static_cast<float>(pose.positionZ);
                return 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
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

        struct ClassFlash
        {
            uint64_t name = 0;
            WP::FlashConfig config;
            bool renderOffsetDefaulted = false; // render offset came from the mesh offset, not muzzleRenderOffset
        };
        struct RecoilSlot
        {
            std::optional<WP::MeshId> node;
            bool animationPresent = false;
            WP::AnimationBinding animation;
            float distance = WP::kRecoilKick;
            float returnSpeed = WP::kRecoilReturnSpeed;
            std::optional<WeaponConvergence::Vec3> flashOffset; // craft override, valid only
        };
        struct CraftConfig { uint64_t name = 0; std::array<RecoilSlot, 5> slots; };
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

        // EXU owns Ogre animation/FPS target resolution. Resolve per operation
        // while holding a module reference; never retain a callback across an
        // EXU mission unload. No LoadLibrary or hard-coded content paths.
        int ExuAnimation(const WP::Identity& owner, const std::string& clip,
            bool cockpit, int mode, float time, float* length = nullptr) noexcept
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExW(0, L"exu.dll", &module)) return mode == 2 ? 1 : 0;
            using Call = int (__cdecl*)(uint32_t, const char*, int, int, float, float*);
            auto call = reinterpret_cast<Call>(GetProcAddress(module, "EXU_OdfRecoilAnimation"));
            if (!call) call = reinterpret_cast<Call>(GetProcAddress(module, "_EXU_OdfRecoilAnimation"));
            const int result = call ? call(static_cast<uint32_t>(owner.lifetime), clip.c_str(),
                cockpit ? 1 : 0, mode, time, length) : (mode == 2 ? 1 : 0);
            FreeLibrary(module);
            return result;
        }
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
            if (!g_ClassReady) { HookEngine::CodePatchLock lock; }
            if (!g_ClassReady || !EngineThread() || !scope || !objectClass) return;
            char casing[kMaxValueBytes] = {};
            const auto casingStatus = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash("casingType"), casing);
            char casingMesh[kMaxValueBytes] = {};
            const auto meshStatus = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash("casingMesh"), casingMesh);
            ObserveShellCasingClass(objectClass, casingStatus == ValueStatus::Missing ? nullptr : casing,
                meshStatus == ValueStatus::Missing ? nullptr : meshStatus == ValueStatus::Present ? casingMesh : "\"");
            if (!g_Ready) return;
            g_FlashClasses.erase(objectClass); // failed/reloaded read cannot retain stale configuration
            try
            {
                ClassFlash result;
                void* parent = nullptr;
                if (!Read(objectClass, kWeaponClassName, result.name) ||
                    !Read(objectClass, kClassParent, parent)) return;
                WP::FlashConfig inherited;
                bool inheritedRenderDefaulted = false;
                auto found = g_FlashClasses.find(parent);
                uint64_t parentName = 0;
                if (found != g_FlashClasses.end() && Read(parent, kWeaponClassName, parentName) &&
                    parentName == found->second.name)
                {
                    inherited = found->second.config;
                    inheritedRenderDefaulted = found->second.renderOffsetDefaulted;
                }
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
                constexpr std::array<std::string_view, 7> meshKeys = {
                    "flashMesh", "flashMaterial", "flashDuration", "flashScale", "flashEndScale", "flashOffset", "flashRoll"};
                std::array<std::array<char, kMaxValueBytes>, 7> meshValues{};
                std::array<std::optional<std::string_view>, 7> meshFields;
                for (size_t i = 0; i < meshKeys.size(); ++i)
                {
                    // ReadValue takes a fixed native buffer; its owned copy is
                    // kept alive through the complete policy parse below.
                    char raw[kMaxValueBytes] = {};
                    const auto status = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash(meshKeys[i]), raw);
                    if (status == ValueStatus::Missing) continue;
                    std::memcpy(meshValues[i].data(), raw, sizeof(raw));
                    meshFields[i] = status == ValueStatus::Present ? std::string_view(meshValues[i].data()) : std::string_view("\"");
                }
                if (inherited.IsMesh() || meshFields[0])
                {
                    result.config = Policy::ResolveMeshFlashConfig(inherited, {meshFields[0], meshFields[1], meshFields[2],
                        meshFields[3], meshFields[4], meshFields[5], meshFields[6]});
                    const auto requestedName = meshFields[0] ? Policy::Name(*meshFields[0]) : std::nullopt;
                    const bool explicitOff = requestedName && requestedName->empty();
                    char odf[9] = {};
                    std::memcpy(odf, &result.name, 8);
                    if (result.config.IsMesh())
                        LogShimA(LogLevel::Info, "WEAPONFX", "ODF=%s flashMesh=%s duration=%.3f scale=%.2f->%.2f",
                            odf, result.config.mesh.c_str(), result.config.duration, result.config.startScale, result.config.finishScale);
                    else if (!explicitOff)
                        LogShimA(LogLevel::Warn, "WEAPONFX", "ODF=%s mesh flash settings rejected; check resource names, duration, scale, offset and roll", odf);
                }
                if (g_AuthoredOdfOnly && !result.config.IsMesh()) result.config = {};
                // Explicit weapon ODF render effects are independent of the
                // mesh channel. Never reinterpret legacy flashName as opt-in.
                constexpr std::array<std::string_view, 3> renderKeys = {
                    "muzzleRender", "muzzleRenderDuration", "muzzleRenderOffset"};
                std::array<std::array<char, kMaxValueBytes>, 3> renderValues{};
                std::array<std::optional<std::string_view>, 3> renderFields;
                for (size_t i = 0; i < renderKeys.size(); ++i)
                {
                    char raw[kMaxValueBytes] = {};
                    const auto status = ReadValue(scope, Policy::Hash("WeaponClass"), Policy::Hash(renderKeys[i]), raw);
                    if (status == ValueStatus::Missing) continue;
                    std::memcpy(renderValues[i].data(), raw, sizeof(raw));
                    renderFields[i] = status == ValueStatus::Present ? std::string_view(renderValues[i].data()) : std::string_view("\"");
                }
                result.config.muzzleRender = Policy::ResolveMuzzleRenderConfig(inherited.muzzleRender,
                    {renderFields[0], renderFields[1], renderFields[2]}, result.config.offset);
                result.renderOffsetDefaulted = result.config.muzzleRender.Valid() && !renderFields[2] &&
                    (!inherited.muzzleRender.Valid() || inheritedRenderDefaulted);
                if (result.config.muzzleRender.Valid())
                {
                    char odf[9] = {}; std::memcpy(odf, &result.name, 8);
                    const auto& render = result.config.muzzleRender;
                    LogShimA(LogLevel::Info, "WEAPONFX", "ODF=%s muzzleRender=%s duration=%.3f offset=%.2f,%.2f,%.2f",
                        odf, render.effect.c_str(), render.duration, render.offset.x, render.offset.y, render.offset.z);
                }
                else if (renderFields[0] || renderFields[1] || renderFields[2])
                {
                    const auto requestedRender = renderFields[0] ? Policy::Name(*renderFields[0]) : std::nullopt;
                    if (!requestedRender || !requestedRender->empty())
                        LogShimA(LogLevel::Warn, "WEAPONFX", "weapon muzzleRender rejected; check name, duration and offset; mesh/recoil remain independent");
                }
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
                for (size_t i = 0; i < result.slots.size(); ++i)
                {
                    auto& slot = result.slots[i];
                    const auto suffix = std::to_string(i + 1);
                    auto readNumber = [&](const char* prefix, float fallback) {
                        char raw[kMaxValueBytes] = {};
                        const auto status = ReadValue(scope, Policy::Hash("CraftClass"),
                            Policy::Hash(std::string(prefix) + suffix), raw);
                        return status == ValueStatus::Missing ? fallback : Policy::Duration(raw);
                    };
                    slot.distance = readNumber("recoilDistance", WP::kRecoilKick);
                    slot.returnSpeed = readNumber("recoilReturn", WP::kRecoilReturnSpeed);
                    slot.animation.playbackRate = readNumber("recoilPlaybackRate", 1);
                    char value[kMaxValueBytes] = {};
                    if (ReadValue(scope, Policy::Hash("CraftClass"), Policy::Hash("recoilName" + suffix), value) ==
                        ValueStatus::Present)
                    {
                        const auto name = Policy::Name(value);
                        if (name) slot.node = WP::ParseMeshId(*name);
                    }
                    if (ReadValue(scope, Policy::Hash("CraftClass"), Policy::Hash("flashOffset" + suffix), value) !=
                        ValueStatus::Missing)
                    {
                        slot.flashOffset = Policy::Offset(value);
                        if (!slot.flashOffset)
                        {
                            char odf[9] = {}; std::memcpy(odf, &result.name, 8);
                            LogShimA(LogLevel::Warn, "WEAPONFX", "ODF=%s flashOffset%s rejected; expected \"right up forward\" within -20..20; weapon flashOffset kept", odf, suffix.c_str());
                        }
                    }
                    const auto animStatus = ReadValue(scope, Policy::Hash("CraftClass"),
                        Policy::Hash("recoilAnimation" + suffix), value);
                    slot.animationPresent = animStatus != ValueStatus::Missing;
                    if (animStatus == ValueStatus::Present)
                    {
                        const auto name = Policy::Name(value);
                        if (name) slot.animation.clip = *name;
                    }
                    if (ReadValue(scope, Policy::Hash("CraftClass"), Policy::Hash("recoilCockpit" + suffix), value) !=
                        ValueStatus::Missing)
                    {
                        const auto flag = Policy::Trim(value);
                        if (flag == "0" || flag == "false") slot.animation.cockpit = false;
                        else if (flag != "1" && flag != "true") slot.animation.playbackRate = 0;
                    }
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

        void BindRecoil(void* weapon, WeaponState& state, WP::BindRequest& request, bool renderOffsetDefaulted)
        {
            if (!g_Settings.meshRecoil && !g_Settings.muzzleFlash) return;
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
            if (selected < 0) return;
            const auto& slot = config->second.slots[selected];
            if (slot.flashOffset && g_Settings.muzzleFlash)
                WP::NativePolicy::ApplyCraftFlashOffset(request.flash, renderOffsetDefaulted, *slot.flashOffset);
            if (!g_Settings.meshRecoil) return;
            if (slot.animationPresent)
            {
                auto animation = slot.animation;
                // An explicit clip wins even if unavailable: never silently
                // slide a barrel that an authored animation was meant to own.
                animation.length = 1;
                if (!animation.Valid() || !ExuAnimation(state.owner, animation.clip, false, 0, 0, &animation.length)) return;
                if (animation.Valid()) request.animation = std::move(animation);
                return;
            }
            if (!slot.node) return;
            if (!std::isfinite(slot.distance) || slot.distance <= 0 || slot.distance > 10 ||
                !std::isfinite(slot.returnSpeed) || slot.returnSpeed <= 0 || slot.returnSpeed > 100) return;
            const auto id = *slot.node;
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
            request.recoil = WP::RecoilBinding{ state.node, rest, slot.distance, slot.returnSpeed };
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
                    bool renderDefaulted = false;
                    if (Read(weapon, kWeaponClass, objectClass))
                    {
                        const auto config = g_FlashClasses.find(objectClass);
                        if (config != g_FlashClasses.end() && Read(objectClass, kWeaponClassName, name) &&
                            name == config->second.name)
                        {
                            request.flash = config->second.config;
                            renderDefaulted = config->second.renderOffsetDefaulted;
                        }
                    }
                    BindRecoil(weapon, state, request, renderDefaulted);
                    const auto token = runtime->Bind(request);
                    if (!token) return;
                    state.token = *token;
                    LogShimA(LogLevel::Info, "WEAPONFX", "presentation bound handle=%u recoil=%s clip=%s flashMesh=%s flashOffset=%.2f,%.2f,%.2f",
                        static_cast<unsigned>(state.owner.lifetime), request.animation ? "animation" : request.recoil ? "node" : "none",
                        request.animation ? request.animation->clip.c_str() : "", request.flash.mesh.c_str(),
                        request.flash.offset.x, request.flash.offset.y, request.flash.offset.z);
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
            bool CreateMeshFlash(const WP::FlashConfig& config, const WP::Identity& owner,
                const WP::Matrix& pose, float remaining, WP::MeshFlashToken& token) noexcept override
            {
                if (token || !config.IsMesh() || !config.Valid() || !WP::ValidPose(pose) || remaining < 0.005f) return false;
                BzrOdfFlashBridge::Spec spec;
                spec.cookie = NextLifetime();
                if (!spec.cookie) return false;
                spec.owner = static_cast<uint32_t>(owner.lifetime);
                spec.mesh = config.mesh.c_str(); spec.material = config.material.c_str();
                const float values[12] = {pose.rightX, pose.rightY, pose.rightZ, pose.upX, pose.upY, pose.upZ,
                    pose.frontX, pose.frontY, pose.frontZ, static_cast<float>(pose.positionX),
                    static_cast<float>(pose.positionY), static_cast<float>(pose.positionZ)};
                std::copy(std::begin(values), std::end(values), spec.pose);
                spec.duration = remaining; spec.startScale = config.startScale; spec.finishScale = config.finishScale;
                spec.rollRadians = config.rollDegrees * 0.01745329251994329577f;
                HMODULE module = nullptr;
                if (!GetModuleHandleExW(0, L"exu.dll", &module))
                {
                    if (!g_MeshFlashUnavailableLogged)
                        LogShimA(LogLevel::Warn, "WEAPONFX", "mesh flashes need the companion EXU loaded by this mission; recoil remains independent");
                    g_MeshFlashUnavailableLogged = true;
                    return false;
                }
                using Spawn = uint32_t (__cdecl*)(const BzrOdfFlashBridge::Spec*);
                auto spawn = reinterpret_cast<Spawn>(GetProcAddress(module, "EXU_SpawnOdfFlash"));
                if (!spawn) spawn = reinterpret_cast<Spawn>(GetProcAddress(module, "_EXU_SpawnOdfFlash"));
                if (spawn) token.id = spawn(&spec);
                if (token.id) token.cookie = spec.cookie;
                FreeLibrary(module);
                if (!token && !g_MeshFlashUnavailableLogged)
                    LogShimA(LogLevel::Warn, "WEAPONFX", "EXU mesh flash declined mesh=%s; verify companion export, assets and exu.log", config.mesh.c_str());
                if (!token) g_MeshFlashUnavailableLogged = true;
                return static_cast<bool>(token);
            }
            bool CancelMeshFlash(WP::MeshFlashToken& token) noexcept override
            {
                HMODULE module = nullptr;
                if (!token || !GetModuleHandleExW(0, L"exu.dll", &module)) { token = {}; return true; }
                using Cancel = int (__cdecl*)(uint32_t, uint64_t);
                auto cancel = reinterpret_cast<Cancel>(GetProcAddress(module, "EXU_CancelOdfFlash"));
                if (!cancel) cancel = reinterpret_cast<Cancel>(GetProcAddress(module, "_EXU_CancelOdfFlash"));
                const bool done = cancel && cancel(token.id, token.cookie);
                FreeLibrary(module);
                if (done) token = {};
                return done;
            }
            bool ApplyAnimation(const WP::Identity& owner, const WP::AnimationBinding& animation,
                float time, bool active) noexcept override
            {
                if (animation.cockpit)
                    ExuAnimation(owner, animation.clip, true, active ? 1 : 2, time);
                return ExuAnimation(owner, animation.clip, false, active ? 1 : 2, time) != 0;
            }
            bool CreateFlash(std::string_view effect, const WP::Matrix& pose, void*& storage) noexcept override
            {
                if (storage || effect.empty() || effect.size() >= 64 || !WP::ValidPose(pose)) return false;
                char name[64] = {};
                std::memcpy(name, effect.data(), effect.size());
                const bool created = CreateNativeFlash(name, &pose, &storage);
                if (created && ++g_RenderCreates <= 3)
                    LogShimA(LogLevel::Info, "WEAPONFX", "muzzle render created effect=%s count=%u", name, g_RenderCreates);
                else if (!created && !g_RenderUnavailableLogged)
                {
                    LogShimA(LogLevel::Warn, "WEAPONFX", "muzzle render declined effect=%s; check mod ODF render resource; mesh/recoil remain independent", name);
                    g_RenderUnavailableLogged = true;
                }
                return created;
            }
            bool UpdateFlash(void*& storage, const WP::Matrix& pose) noexcept override
            { return WP::ValidPose(pose) && UpdateNativeFlash(&storage, &pose); }
            bool DetachFlash(void*& storage) noexcept override
            {
                const bool detached = DetachNativeFlash(&storage);
                if (detached && ++g_RenderDetaches <= 3)
                    LogShimA(LogLevel::Info, "WEAPONFX", "muzzle render detached count=%u", g_RenderDetaches);
                return detached;
            }
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

        bool InstallCasingClassObserver()
        {
            const uint32_t site = HookEngine::ResolveNamedAddress("WeaponPresentation::WeaponClassPopCall");
            const uint32_t pop = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
            const uint32_t raw = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
            if (!site || !pop || !raw || HookEngine::ResolveRelCallTarget(site) != reinterpret_cast<void*>(pop)) return false;
            g_RawGet = reinterpret_cast<RawGet>(raw);
            Bridges::Configure(nullptr, reinterpret_cast<Bridges::PopScope>(pop), nullptr, ObserveWeaponClass, nullptr);
            // Configure must retain the already-qualified shared factory.
            if (!ReplaceCall(site, reinterpret_cast<void*>(Bridges::WeaponClassScopePopBridge), reinterpret_cast<void*>(pop))) return false;
            g_WeaponScopeSite = site;
            g_ClassReady = true;
            return true;
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
            const uint32_t fire = Bridges::ShotSite(false);
            const uint32_t machineFire = Bridges::ShotSite(true);
            const uint32_t weaponPop = g_WeaponScopeSite ? g_WeaponScopeSite :
                HookEngine::ResolveNamedAddress("WeaponPresentation::WeaponClassPopCall");
            const uint32_t craftPop = HookEngine::ResolveNamedAddress("WeaponPresentation::CraftClassPopCall");
            const uint32_t factory = HookEngine::ResolveNamedAddress("WeaponPresentation::OrdnanceFactory");
            const uint32_t pop = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
            const uint32_t rawGet = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
            const uint32_t find = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderFind");
            const uint32_t update = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderUpdate");
            const uint32_t detach = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderDetach");
            if (!ctor || !dtor || !sim || !slot || !model || !fire || !machineFire || !weaponPop || !craftPop ||
                !factory || !pop || !rawGet || !find || !update || !detach) return false;
            if (HookEngine::ResolveRelCallTarget(fire) != GetShellCasingShotBridgeAddress() ||
                HookEngine::ResolveRelCallTarget(machineFire) != GetShellCasingShotBridgeAddress() ||
                HookEngine::ResolveRelCallTarget(weaponPop) != (g_ClassReady ?
                    reinterpret_cast<void*>(Bridges::WeaponClassScopePopBridge) : reinterpret_cast<void*>(pop)) ||
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
            if ((!g_ClassReady && !ReplaceCall(weaponPop, reinterpret_cast<void*>(Bridges::WeaponClassScopePopBridge), reinterpret_cast<void*>(pop))) ||
                !ReplaceCall(craftPop, reinterpret_cast<void*>(Bridges::CraftClassScopePopBridge), reinterpret_cast<void*>(pop))) return false;
            g_ClassReady = true;
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
            const bool casings = IsShellCasingsEnabled();
            if (!casings && !g_Settings.muzzleFlash && !g_Settings.meshRecoil) return;
            if (!ExactGogImage()) return;
            // Independent from presentation/backend readiness. A failed flash
            // install cannot prevent ODF energy weapons from opting out of brass.
            if (casings)
                LogShimA(LogLevel::Info, "SHELLCASINGS", "ODF casingType observer ready=%d", InstallCasingClassObserver());
            if (!g_Settings.muzzleFlash && !g_Settings.meshRecoil) return;
            // Settings are the master switches, including for developer runs.
            // The bounded authored-ODF path has its own exact-GOG/SP guards;
            // blanket/legacy flashName activation remains unqualified.
            g_AuthoredOdfOnly = !kNativePresentationLiveQualified;
            LogShimA(LogLevel::Warn, "WEAPONFX", "authored ODF presentation requested; GOG/SP cannon+machinegun, MuzzleFlash=%d MeshRecoil=%d; assets/config required",
                g_Settings.muzzleFlash, g_Settings.meshRecoil);
            if (!g_MissionSeamInstalled || !InstallCandidate())
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

    // Optional read-only presentation bridge. The point uses precisely the
    // current, corrected firing mount used by the native muzzle flash adapter.
    // O(1) carrier-slot lookup; no object/weapon enumeration or native mutation.
    extern "C" __declspec(dllexport) int __cdecl OpenShimGetWeaponMuzzle(
        uint32_t handle, int slot, float* outPosition) noexcept
    {
        if (!outPosition || slot < 0 || slot >= 5 || !ActiveRuntime() || !EngineThread()) return 0;
        void* owner = GameObjectFromHandleGog(static_cast<int>(handle));
        void* carrier = nullptr;
        void* weapon = nullptr;
        if (!owner || !Read(owner, kCarrier, carrier) || !carrier ||
            !Read(carrier, kCarrierSlots + slot * sizeof(void*), weapon)) return 0;
        const auto found = g_Weapons.find(weapon);
        if (found == g_Weapons.end() || found->second.owner.lifetime != handle ||
            found->second.owner.address != reinterpret_cast<uintptr_t>(owner) || !found->second.token.Valid()) return 0;
        WP::Matrix pose;
        if (!CurrentWeaponPose(weapon, found->second, pose)) return 0;
        pose = WeaponConvergence::Multiply(found->second.correction, pose);
        if (!WP::ValidPose(pose)) return 0;
        return WriteMuzzlePoint(outPosition, pose);
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
