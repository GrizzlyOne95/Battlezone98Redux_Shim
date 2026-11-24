// Per-faction construction blob render effects ([Display] FactionConstructionBlobs).
//
// GOG 2.2.301 layout (Docs/FACTION_CONSTRUCTION_BLOBS.md has the sources):
//   ConstructionBlob vtable 0x008778A0: +0x08 PreLoad 0x0049BF60,
//   +0x18 Control 0x0049C050 (resets the list once per simulation pass),
//   +0x20 Submit 0x0049C150. AddBlob 0x0049C0A0 appends {x,y,z,radius,scale}
//   (0x14 bytes) to the list at this+0x28 while the end pointer at this+0x168
//   is below this+0x168 (16 entries).
//   Producer::UpdateBuild 0x005AEE30 (build class at this+0x300) and
//   ConstructionRig::UpdateUnbuild 0x0049CDF0 (target class at this+0x370) are
//   the only AddBlob callers; each has one caller, which these REL32 rows wrap.
//
// The update wrappers see which list slot a build appended, look up the
// render for the built object's faction and keep one pooled engine render per
// build at the blob centre. Submit draws the stock sprite only for entries
// without a live render (compact, draw, restore). Control releases renders
// whose build added no blob in the last pass. Renders use the same engine
// render contract as muzzleRender (WeaponPresentation::RenderFind/Update/
// Detach rows; build through the class vtable +0x08; back-reference at
// render+0x68). Nothing allocates per frame.

#include "construction_blob_faction.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "odf_item_hooks.h"
#include "shim_log.h"
#include "bzr_hooks_internal.h"
#include "weapon_convergence.h"

#include <Windows.h>
#include <cstring>
#include <string>

namespace BZROpenShim::ConstructionBlobFaction
{
    namespace
    {
        constexpr const char* kPreLoadPatch = "Construction Blob Faction PreLoad VTable Hook";
        constexpr const char* kControlPatch = "Construction Blob Faction Control VTable Hook";
        constexpr const char* kSubmitPatch = "Construction Blob Faction Submit VTable Hook";
        constexpr const char* kProducerPatch = "Construction Blob Faction Producer Build Tag";
        constexpr const char* kRigPatch = "Construction Blob Faction Rig Unbuild Tag";

        constexpr size_t kListOffset = 0x28;
        constexpr size_t kEndOffset = 0x168;
        constexpr size_t kEntrySize = 0x14;
        constexpr size_t kEntryCount = (kEndOffset - kListOffset) / kEntrySize; // 16
        constexpr size_t kProducerClassOffset = 0x300;
        constexpr size_t kRigClassOffset = 0x370;
        constexpr size_t kClassOdfNameOffset = 0x30;
        constexpr size_t kRenderBackReference = 0x68;

        using Matrix = WeaponConvergence::Matrix;
        using FnThis = void(__thiscall*)(void* self);
        using FnSubmit = void(__thiscall*)(void* self, void* camera);
        using FnUpdate = void(__thiscall*)(void* self, float dt);
        using RenderFind = void*(__cdecl*)(const char*);
        using RenderBuild = void*(__thiscall*)(void*, void**, const Matrix*);
        using RenderUpdate = void(__thiscall*)(void**, const Matrix*);
        using RenderDetach = void(__thiscall*)(void**, const Matrix*, float);

        uint32_t g_PreLoadAddress = 0;
        uint32_t g_ControlAddress = 0;
        uint32_t g_SubmitAddress = 0;
        uint32_t g_ProducerUpdateBuildAddress = 0;
        uint32_t g_RigUpdateUnbuildAddress = 0;
        FnUpdate g_ProducerOriginal = nullptr;
        FnUpdate g_RigOriginal = nullptr;
        RenderFind g_RenderFind = nullptr;
        RenderUpdate g_RenderUpdate = nullptr;
        RenderDetach g_RenderDetach = nullptr;
        bool g_Installed = false;
        // Renders are only made once Control (which releases them) has run.
        bool g_ControlLive = false;

        // Resolved render names per key (empty = stock sprite).
        char g_Names[kKeyCount][kMaxRenderName + 1] = {};
        // Effect id per faction slot (index into g_Names), -1 = stock sprite.
        int g_FactionEffect[kFactionCount] = { -1, -1, -1, -1 };
        int g_OtherEffect = -1; // ODF names starting with another letter
        bool g_ConfigLoaded = false;
        uint32_t g_ReleasesLogged = 0;

        // ---- engine render contract (same as muzzleRender) ----------------
        bool CreateNative(const char* name, const Matrix* pose, void** storage) noexcept
        {
            __try
            {
                void* objectClass = g_RenderFind(name);
                if (!objectClass)
                    return false;
                const auto table = *reinterpret_cast<void***>(objectClass);
                reinterpret_cast<RenderBuild>(table[2])(objectClass, storage, pose);
                return *storage != nullptr &&
                    *reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) == storage;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool UpdateNative(void** storage, const Matrix* pose) noexcept
        {
            __try
            {
                if (!*storage)
                    return true;
                if (*reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) != storage)
                    return false;
                g_RenderUpdate(storage, pose);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool DetachNative(void** storage) noexcept
        {
            __try
            {
                if (!*storage)
                    return true;
                if (*reinterpret_cast<void***>(static_cast<unsigned char*>(*storage) + kRenderBackReference) != storage)
                    return false;
                g_RenderDetach(storage, nullptr, 0.0f); // the engine list keeps ownership
                return *storage == nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool ResolvesNative(const char* name) noexcept
        {
            __try { return g_RenderFind(name) != nullptr; }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        Matrix PoseMatrix(const BlobPose& pose)
        {
            // Orthonormal, like every muzzleRender pose: the render contract is
            // only qualified for rigid transforms, so build progress is not
            // applied as a basis scale.
            Matrix m{};
            m.rightX = 1.0f;
            m.upY = 1.0f;
            m.frontZ = 1.0f;
            m.positionX = pose.x;
            m.positionY = pose.y;
            m.positionZ = pose.z;
            return m;
        }

        bool BackendCreate(void*, int effect, const BlobPose& pose, void** storage)
        {
            if (effect < 0 || effect >= static_cast<int>(kKeyCount) || !g_Names[effect][0])
                return false;
            const Matrix m = PoseMatrix(pose);
            const bool created = CreateNative(g_Names[effect], &m, storage);
            static uint32_t s_logged = 0;
            if (s_logged < 6)
            {
                ++s_logged;
                LogShimA(created ? LogLevel::Info : LogLevel::Warn, "CNSTBLOB",
                         "render %s effect=%s at %.1f,%.1f,%.1f",
                         created ? "created" : "declined (stock sprite)", g_Names[effect], pose.x, pose.y, pose.z);
            }
            return created;
        }

        bool BackendUpdate(void*, void** storage, const BlobPose& pose)
        {
            const Matrix m = PoseMatrix(pose);
            return UpdateNative(storage, &m);
        }

        bool BackendDetach(void*, void** storage)
        {
            const bool detached = DetachNative(storage);
            if (g_ReleasesLogged < 6)
            {
                ++g_ReleasesLogged;
                LogShimA(detached ? LogLevel::Info : LogLevel::Warn, "CNSTBLOB",
                         "render released detached=%d", detached ? 1 : 0);
            }
            return detached;
        }

        const BlobRenderBackend g_Backend = { BackendCreate, BackendUpdate, BackendDetach, nullptr };
        // Static: the engine writes back-references into these slots.
        BlobRenderPool<kEntryCount> g_Pool;

        void LoadConfig()
        {
            g_ConfigLoaded = true;
            std::string text;
            const bool read = OdfReadItemText("cnstblob.odf", text);
            const RenderKeys keys = read ? ParseOdf(text) : RenderKeys{};
            char names[kKeyCount][kMaxRenderName + 1] = {};
            for (size_t k = 0; k < kKeyCount; ++k)
            {
                const std::string& name = keys.value[k];
                if (name.empty())
                    continue;
                if (ResolvesNative(name.c_str()))
                    std::memcpy(names[k], name.c_str(), name.size() + 1);
                else
                    LogShimA(LogLevel::Warn, "CNSTBLOB",
                             "%s=\"%s\" is not a render resource; stock sprite instead",
                             kRenderKeys[k], name.c_str());
            }
            for (size_t k = 0; k < kKeyCount; ++k)
                if (keys.present[k] && keys.value[k].empty())
                    LogShimA(LogLevel::Info, "CNSTBLOB", "%s is empty or invalid; stock sprite", kRenderKeys[k]);

            auto effectFor = [&](int slot) {
                const size_t k = (slot >= 0 && keys.present[1 + slot]) ? 1 + slot : 0;
                return names[k][0] ? static_cast<int>(k) : -1;
            };
            int faction[kFactionCount];
            for (int f = 0; f < static_cast<int>(kFactionCount); ++f)
                faction[f] = effectFor(f);
            const int other = effectFor(-1);

            const bool changed = std::memcmp(names, g_Names, sizeof(names)) != 0 ||
                                 std::memcmp(faction, g_FactionEffect, sizeof(faction)) != 0 ||
                                 other != g_OtherEffect;
            std::memcpy(g_Names, names, sizeof(names));
            std::memcpy(g_FactionEffect, faction, sizeof(faction));
            g_OtherEffect = other;
            if (changed || !read)
            {
                auto label = [&](int effect) { return effect < 0 ? "stock" : g_Names[effect]; };
                LogShimA(LogLevel::Info, "CNSTBLOB",
                         "blob renders odf=%s a=%s s=%s c=%s b=%s other=%s",
                         read ? "read" : "unreadable", label(faction[0]), label(faction[1]),
                         label(faction[2]), label(faction[3]), label(other));
            }
        }

        bool AnyRender()
        {
            if (g_OtherEffect >= 0)
                return true;
            for (int e : g_FactionEffect)
                if (e >= 0)
                    return true;
            return false;
        }

        // Effect for the GameObjectClass* at owner+offset (first ODF letter),
        // and that class pointer as the build's target key.
        int EffectFor(void* owner, size_t classOffset, uintptr_t& target) noexcept
        {
            __try
            {
                const auto* klass = *reinterpret_cast<const uint8_t* const*>(
                    static_cast<const uint8_t*>(owner) + classOffset);
                target = reinterpret_cast<uintptr_t>(klass);
                if (!klass)
                    return -1;
                const int slot = FactionSlot(static_cast<char>(klass[kClassOdfNameOffset]));
                return slot < 0 ? g_OtherEffect : g_FactionEffect[slot];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // A tag marks one list slot whose stock sprite a live render replaces.
        // It holds the entry's x and scale bits as written, so a slot reused
        // by a build the wrappers did not see no longer matches and draws stock.
        struct Tag
        {
            bool suppress;
            uint32_t xBits;
            uint32_t scaleBits;
        };
        Tag g_Tags[kEntryCount] = {};
        // Thread that runs the ConstructionBlob hooks; teardown on any other
        // thread must not touch native renders.
        DWORD g_EngineThreadId = 0;
        uint8_t g_Saved[kEntryCount * kEntrySize] = {};
        void* g_Blob = nullptr;

        void TaggedUpdate(FnUpdate original, void* self, float dt, size_t classOffset)
        {
            uint8_t* blob = static_cast<uint8_t*>(g_Blob);
            uint8_t* before = blob ? *reinterpret_cast<uint8_t**>(blob + kEndOffset) : nullptr;
            original(self, dt);
            if (!blob || !g_ControlLive || !AnyRender())
                return;
            uint8_t* after = *reinterpret_cast<uint8_t**>(blob + kEndOffset);
            if (after != before + kEntrySize || before < blob + kListOffset || after > blob + kEndOffset)
                return;
            uintptr_t target = 0;
            const int effect = EffectFor(self, classOffset, target);
            const size_t slot = static_cast<size_t>(before - (blob + kListOffset)) / kEntrySize;
            Tag& tag = g_Tags[slot];
            std::memcpy(&tag.xBits, before, 4);
            std::memcpy(&tag.scaleBits, before + 0x10, 4);
            BlobPose pose{};
            std::memcpy(&pose, before, sizeof(pose));
            tag.suppress = effect >= 0 &&
                g_Pool.Touch(g_Backend, reinterpret_cast<uintptr_t>(self), target, effect, pose);
        }

        void __fastcall PreLoadHook(void* self, void*)
        {
            g_Blob = self;
            g_EngineThreadId = GetCurrentThreadId();
            g_Pool.ReleaseAll(g_Backend);
            g_Pool.Forget();
            for (Tag& tag : g_Tags)
                tag = Tag{};
            reinterpret_cast<FnThis>(g_PreLoadAddress)(self);
            LoadConfig();
        }

        void __fastcall ControlHook(void* self, void*)
        {
            g_Blob = self;
            g_EngineThreadId = GetCurrentThreadId();
            g_ControlLive = true;
            g_Pool.EndPass(g_Backend);
            reinterpret_cast<FnThis>(g_ControlAddress)(self);
        }

        void __fastcall ProducerUpdateBuildHook(void* self, void*, float dt)
        {
            TaggedUpdate(g_ProducerOriginal, self, dt, kProducerClassOffset);
        }

        void __fastcall RigUpdateUnbuildHook(void* self, void*, float dt)
        {
            TaggedUpdate(g_RigOriginal, self, dt, kRigClassOffset);
        }

        // No C++ objects with destructors here: the __finally restore needs SEH.
        void __fastcall SubmitHook(void* self, void*, void* camera)
        {
            const auto original = reinterpret_cast<FnSubmit>(g_SubmitAddress);
            uint8_t* blob = static_cast<uint8_t*>(self);
            g_Blob = self;
            if (!g_ConfigLoaded)
                LoadConfig();
            uint8_t* const list = blob + kListOffset;
            uint8_t* const end = *reinterpret_cast<uint8_t**>(blob + kEndOffset);
            if (!AnyRender() || end <= list || end > blob + kEndOffset)
            {
                original(self, camera);
                return;
            }
            const size_t count = static_cast<size_t>(end - list) / kEntrySize;
            bool suppress[kEntryCount] = {};
            bool any = false;
            for (size_t i = 0; i < count; ++i)
            {
                const Tag& tag = g_Tags[i];
                const uint8_t* entry = list + i * kEntrySize;
                suppress[i] = tag.suppress && std::memcmp(&tag.xBits, entry, 4) == 0 &&
                              std::memcmp(&tag.scaleBits, entry + 0x10, 4) == 0;
                any |= suppress[i];
            }
            if (!any)
            {
                original(self, camera);
                return;
            }
            std::memcpy(g_Saved, list, count * kEntrySize);
            __try
            {
                size_t kept = 0;
                for (size_t i = 0; i < count; ++i)
                    if (!suppress[i])
                        std::memcpy(list + (kept++) * kEntrySize, g_Saved + i * kEntrySize, kEntrySize);
                *reinterpret_cast<uint8_t**>(blob + kEndOffset) = list + kept * kEntrySize;
                if (kept)
                    original(self, camera);
            }
            __finally
            {
                std::memcpy(list, g_Saved, count * kEntrySize);
                *reinterpret_cast<uint8_t**>(blob + kEndOffset) = end;
            }
        }
    }

    bool IsPatchName(const char* name)
    {
        return name && (std::strcmp(name, kPreLoadPatch) == 0 || std::strcmp(name, kControlPatch) == 0 ||
                        std::strcmp(name, kSubmitPatch) == 0 || std::strcmp(name, kProducerPatch) == 0 ||
                        std::strcmp(name, kRigPatch) == 0);
    }

    bool ShouldInstall()
    {
        static int s_lastDecision = -1;
        bool enabled = false;
        TryGetUserConfigBool(Hooks::kUserConfigDisplaySection, "FactionConstructionBlobs", enabled);
        bool bound = false;
        if (enabled)
        {
            const HookEngine::EngineRow rows[] = {
                {"ConstructionBlobPreLoad", &g_PreLoadAddress},
                {"ConstructionBlobControl", &g_ControlAddress},
                {"ConstructionBlobSubmit", &g_SubmitAddress},
                {"ProducerUpdateBuild", &g_ProducerUpdateBuildAddress},
                {"ConstructionRigUpdateUnbuild", &g_RigUpdateUnbuildAddress},
            };
            const uint32_t find = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderFind");
            const uint32_t update = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderUpdate");
            const uint32_t detach = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderDetach");
            bound = find && update && detach && HookEngine::BindEngineRows("FactionConstructionBlobs", rows);
            if (bound)
            {
                g_RenderFind = reinterpret_cast<RenderFind>(find);
                g_RenderUpdate = reinterpret_cast<RenderUpdate>(update);
                g_RenderDetach = reinterpret_cast<RenderDetach>(detach);
            }
        }
        const int decision = !enabled ? 0 : (bound ? 1 : 2);
        g_Installed = decision == 1;
        if (decision != s_lastDecision)
        {
            s_lastDecision = decision;
            LogShimA(LogLevel::Info, "CNSTBLOB", "FactionConstructionBlobs=%d -> %s",
                     enabled ? 1 : 0,
                     decision == 1 ? "hooks queued" : decision == 2 ? "engine rows unbound; stock" : "off (stock)");
        }
        return decision == 1;
    }

    uint32_t DwordTarget(const char* name)
    {
        using HookFn = void(__fastcall*)(void*, void*);
        using SubmitFn = void(__fastcall*)(void*, void*, void*);
        if (name && std::strcmp(name, kPreLoadPatch) == 0 && g_PreLoadAddress)
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(static_cast<HookFn>(PreLoadHook)));
        if (name && std::strcmp(name, kControlPatch) == 0 && g_ControlAddress)
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(static_cast<HookFn>(ControlHook)));
        if (name && std::strcmp(name, kSubmitPatch) == 0 && g_SubmitAddress)
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(static_cast<SubmitFn>(SubmitHook)));
        return 0;
    }

    uint32_t Rel32Target(const char* name, void* original)
    {
        using UpdateFn = void(__fastcall*)(void*, void*, float);
        const uintptr_t target = reinterpret_cast<uintptr_t>(original);
        if (name && std::strcmp(name, kProducerPatch) == 0 && target && target == g_ProducerUpdateBuildAddress)
        {
            g_ProducerOriginal = reinterpret_cast<FnUpdate>(original);
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(static_cast<UpdateFn>(ProducerUpdateBuildHook)));
        }
        if (name && std::strcmp(name, kRigPatch) == 0 && target && target == g_RigUpdateUnbuildAddress)
        {
            g_RigOriginal = reinterpret_cast<FnUpdate>(original);
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(static_cast<UpdateFn>(RigUpdateUnbuildHook)));
        }
        LogShimA(LogLevel::Warn, "CNSTBLOB", "%s identity failed original=%p; leaving stock call",
                 name ? name : "?", original);
        return 0;
    }

    void SceneTeardown() noexcept
    {
        if (g_Installed && (!g_EngineThreadId || g_EngineThreadId == GetCurrentThreadId()))
            g_Pool.ReleaseAll(g_Backend);
    }
}
