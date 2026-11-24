// Per-faction construction blob and portal blob render effects
// ([Display] FactionConstructionBlobs).
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
//   PortalBlob vtable 0x00891F04, same slots: PreLoad 0x006607F0, Control
//   0x00660910, Submit 0x00660A80. AddBlob 0x00660960 (__thiscall this,
//   sphere*, t, char in) appends {x,y,z,radius,scale,in} (0x18 bytes) to the
//   list at this+0x28 while the end pointer at this+0x1A8 is below this+0x1A8
//   (16 entries); Submit draws blobInTexture (+0x1AC) when in != 0, else
//   blobOutTexture (+0x1B0). The three AddBlob calls (all with ecx = the
//   static PortalBlob) are REL32-wrapped through thunks that pass the
//   caller's owner: the object handle at [ebp+8] of the two effect helpers
//   0x005CDBB0 (out) / 0x005CDC40 (in), and the portal at [ebp-0x1C] of
//   0x00660080.
//
// The update wrappers see which list slot a build appended, look up the
// render for that slot (faction, or portal in/out) and keep one pooled engine
// render per build at the blob centre. Submit draws the stock sprite only for
// entries without a live render (compact, draw, restore). Control releases
// renders whose build added no blob in the last pass. Renders use the same
// engine render contract as muzzleRender (WeaponPresentation::RenderFind/
// Update/Detach rows; build through the class vtable +0x08; back-reference at
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
        constexpr const char* kPortalPreLoadPatch = "Portal Blob Render PreLoad VTable Hook";
        constexpr const char* kPortalControlPatch = "Portal Blob Render Control VTable Hook";
        constexpr const char* kPortalSubmitPatch = "Portal Blob Render Submit VTable Hook";
        constexpr const char* kPortalOutPatch = "Portal Blob Render Out Effect Tag";
        constexpr const char* kPortalInPatch = "Portal Blob Render In Effect Tag";
        constexpr const char* kPortalUpdatePatch = "Portal Blob Render Portal Update Tag";

        constexpr size_t kListOffset = 0x28;
        constexpr size_t kEntryCount = 16; // both emitters
        constexpr size_t kMaxEntrySize = 0x18;
        constexpr size_t kMaxKeys = kKeyCount > kPortalKeyCount ? kKeyCount : kPortalKeyCount;
        constexpr size_t kMaxSlots = kFactionCount + 1; // factions + other
        constexpr size_t kProducerClassOffset = 0x300;
        constexpr size_t kRigClassOffset = 0x370;
        constexpr size_t kClassOdfNameOffset = 0x30;
        constexpr size_t kRenderBackReference = 0x68;
        constexpr size_t kPortalInFlagOffset = 0x14;
        // Call-site offsets inside the verified caller rows (E8 address - row).
        constexpr uint32_t kPortalOutSiteOffset = 0x77;    // 0x005CDC27 - 0x005CDBB0
        constexpr uint32_t kPortalInSiteOffset = 0x77;     // 0x005CDCB7 - 0x005CDC40
        constexpr uint32_t kPortalUpdateSiteOffset = 0x1E5; // 0x00660265 - 0x00660080

        using Matrix = WeaponConvergence::Matrix;
        using FnThis = void(__thiscall*)(void* self);
        using FnSubmit = void(__thiscall*)(void* self, void* camera);
        using FnUpdate = void(__thiscall*)(void* self, float dt);
        using FnAddBlob = void(__thiscall*)(void* self, const float* sphere, float t, int in);
        using RenderFind = void*(__cdecl*)(const char*);
        using RenderBuild = void*(__thiscall*)(void*, void**, const Matrix*);
        using RenderUpdate = void(__thiscall*)(void**, const Matrix*);
        using RenderDetach = void(__thiscall*)(void**, const Matrix*, float);

        RenderFind g_RenderFind = nullptr;
        RenderUpdate g_RenderUpdate = nullptr;
        RenderDetach g_RenderDetach = nullptr;

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

        // A tag marks one list slot whose stock sprite a live render replaces.
        // It holds the entry's x and scale bits as written, so a slot reused
        // by a build the wrappers did not see no longer matches and draws stock.
        struct Tag
        {
            bool suppress;
            uint32_t xBits;
            uint32_t scaleBits;
        };

        // One blob emitter (ConstructionBlob or PortalBlob): its layout, its
        // resolved render names and its pool. Static objects: the engine
        // writes back-references into the pool slots.
        struct Emitter
        {
            const char* tag;        // log component
            const char* odf;
            size_t endOffset;       // end pointer; also the list's end
            size_t entrySize;
            size_t keyCount;
            const char* const* keys;
            size_t slotCount;       // slot s uses key 1+s when present, else key 0

            uint32_t preLoad = 0, control = 0, submit = 0;
            bool installed = false;
            bool controlLive = false; // renders are only made once Control (which releases them) has run
            bool configLoaded = false;
            char names[kMaxKeys][kMaxRenderName + 1] = {};
            int effect[kMaxSlots] = { -1, -1, -1, -1, -1 };
            uint32_t createsLogged = 0, releasesLogged = 0;
            BlobRenderPool<kEntryCount> pool;
            Tag tags[kEntryCount] = {};
            uint8_t saved[kEntryCount * kMaxEntrySize] = {};
            void* blob = nullptr;
            // Thread that runs the emitter's hooks; teardown on any other
            // thread must not touch native renders.
            DWORD engineThreadId = 0;
            BlobRenderBackend backend = {};

            uint8_t* End(uint8_t* self) const { return *reinterpret_cast<uint8_t**>(self + endOffset); }
        };

        bool BackendCreate(void* context, int effect, const BlobPose& pose, void** storage)
        {
            Emitter& e = *static_cast<Emitter*>(context);
            if (effect < 0 || effect >= static_cast<int>(e.keyCount) || !e.names[effect][0])
                return false;
            const Matrix m = PoseMatrix(pose);
            const bool created = CreateNative(e.names[effect], &m, storage);
            if (e.createsLogged < 6)
            {
                ++e.createsLogged;
                LogShimA(created ? LogLevel::Info : LogLevel::Warn, e.tag,
                         "render %s effect=%s at %.1f,%.1f,%.1f",
                         created ? "created" : "declined (stock sprite)", e.names[effect], pose.x, pose.y, pose.z);
            }
            return created;
        }

        bool BackendUpdate(void*, void** storage, const BlobPose& pose)
        {
            const Matrix m = PoseMatrix(pose);
            return UpdateNative(storage, &m);
        }

        bool BackendDetach(void* context, void** storage)
        {
            Emitter& e = *static_cast<Emitter*>(context);
            const bool detached = DetachNative(storage);
            if (e.releasesLogged < 6)
            {
                ++e.releasesLogged;
                LogShimA(detached ? LogLevel::Info : LogLevel::Warn, e.tag,
                         "render released detached=%d", detached ? 1 : 0);
            }
            return detached;
        }

        Emitter g_Cnst{ "CNSTBLOB", "cnstblob.odf", 0x168, 0x14, kKeyCount, kRenderKeys, kFactionCount + 1 };
        Emitter g_Port{ "PORTBLOB", "portblob.odf", 0x1A8, 0x18, kPortalKeyCount, kPortalRenderKeys, 2 };

        // Construction-only engine rows.
        uint32_t g_ProducerUpdateBuildAddress = 0;
        uint32_t g_RigUpdateUnbuildAddress = 0;
        FnUpdate g_ProducerOriginal = nullptr;
        FnUpdate g_RigOriginal = nullptr;
        // Portal-only engine rows.
        uint32_t g_PortalAddBlobAddress = 0;
        uint32_t g_PortalOutEffectAddress = 0;
        uint32_t g_PortalInEffectAddress = 0;
        uint32_t g_PortalUpdateAddress = 0;
        FnAddBlob g_PortalAddBlob = nullptr;

        // Resolves the parsed names and maps each slot to an effect id
        // (index into e.names, -1 = stock sprite). Returns true on a change.
        template<size_t N>
        bool ApplyKeys(Emitter& e, const RenderKeysN<N>& keys)
        {
            char names[kMaxKeys][kMaxRenderName + 1] = {};
            for (size_t k = 0; k < N; ++k)
            {
                const std::string& name = keys.value[k];
                if (name.empty())
                    continue;
                if (ResolvesNative(name.c_str()))
                    std::memcpy(names[k], name.c_str(), name.size() + 1);
                else
                    LogShimA(LogLevel::Warn, e.tag, "%s=\"%s\" is not a render resource; stock sprite instead",
                             e.keys[k], name.c_str());
            }
            for (size_t k = 0; k < N; ++k)
                if (keys.present[k] && keys.value[k].empty())
                    LogShimA(LogLevel::Info, e.tag, "%s is empty or invalid; stock sprite", e.keys[k]);

            int effect[kMaxSlots] = { -1, -1, -1, -1, -1 };
            for (size_t s = 0; s < e.slotCount; ++s)
            {
                const size_t k = (1 + s < N && keys.present[1 + s]) ? 1 + s : 0;
                effect[s] = names[k][0] ? static_cast<int>(k) : -1;
            }
            const bool changed = std::memcmp(names, e.names, sizeof(names)) != 0 ||
                                 std::memcmp(effect, e.effect, sizeof(effect)) != 0;
            std::memcpy(e.names, names, sizeof(names));
            std::memcpy(e.effect, effect, sizeof(effect));
            return changed;
        }

        const char* Label(const Emitter& e, size_t slot)
        {
            const int effect = e.effect[slot];
            return effect < 0 ? "stock" : e.names[effect];
        }

        void LoadConfig(Emitter& e)
        {
            e.configLoaded = true;
            std::string text;
            const bool read = OdfReadItemText(e.odf, text);
            if (&e == &g_Cnst)
            {
                const bool changed = ApplyKeys(e, read ? ParseOdf(text) : RenderKeys{});
                if (changed || !read)
                    LogShimA(LogLevel::Info, e.tag, "blob renders odf=%s a=%s s=%s c=%s b=%s other=%s",
                             read ? "read" : "unreadable", Label(e, 0), Label(e, 1), Label(e, 2), Label(e, 3),
                             Label(e, kFactionCount));
            }
            else
            {
                const bool changed = ApplyKeys(e, read ? ParsePortalOdf(text) : PortalRenderKeys{});
                if (changed || !read)
                    LogShimA(LogLevel::Info, e.tag, "portal blob renders odf=%s in=%s out=%s",
                             read ? "read" : "unreadable", Label(e, PortalSlot(true)), Label(e, PortalSlot(false)));
            }
        }

        bool AnyRender(const Emitter& e)
        {
            for (size_t s = 0; s < e.slotCount; ++s)
                if (e.effect[s] >= 0)
                    return true;
            return false;
        }

        // Called after the stock code may have appended one entry at `before`.
        void TagAppended(Emitter& e, uint8_t* blob, uint8_t* before, uintptr_t owner, uintptr_t target, int effect)
        {
            uint8_t* after = e.End(blob);
            if (after != before + e.entrySize || before < blob + kListOffset || after > blob + e.endOffset)
                return;
            const size_t slot = static_cast<size_t>(before - (blob + kListOffset)) / e.entrySize;
            if (slot >= kEntryCount)
                return;
            Tag& tag = e.tags[slot];
            std::memcpy(&tag.xBits, before, 4);
            std::memcpy(&tag.scaleBits, before + 0x10, 4);
            BlobPose pose{};
            std::memcpy(&pose, before, sizeof(pose));
            tag.suppress = effect >= 0 && e.pool.Touch(e.backend, owner, target, effect, pose);
        }

        // ---- shared PreLoad / Control / Submit ----------------------------
        void PreLoad(Emitter& e, void* self)
        {
            e.blob = self;
            e.engineThreadId = GetCurrentThreadId();
            e.pool.ReleaseAll(e.backend);
            e.pool.Forget();
            for (Tag& tag : e.tags)
                tag = Tag{};
            reinterpret_cast<FnThis>(e.preLoad)(self);
            LoadConfig(e);
        }

        void Control(Emitter& e, void* self)
        {
            e.blob = self;
            e.engineThreadId = GetCurrentThreadId();
            e.controlLive = true;
            e.pool.EndPass(e.backend);
            reinterpret_cast<FnThis>(e.control)(self);
        }

        // No C++ objects with destructors here: the __finally restore needs SEH.
        void Submit(Emitter& e, void* self, void* camera)
        {
            const auto original = reinterpret_cast<FnSubmit>(e.submit);
            uint8_t* blob = static_cast<uint8_t*>(self);
            e.blob = self;
            if (!e.configLoaded)
                LoadConfig(e);
            const size_t size = e.entrySize;
            uint8_t* const list = blob + kListOffset;
            uint8_t* const end = e.End(blob);
            if (!AnyRender(e) || end <= list || end > blob + e.endOffset)
            {
                original(self, camera);
                return;
            }
            const size_t count = static_cast<size_t>(end - list) / size;
            bool suppress[kEntryCount] = {};
            bool any = false;
            for (size_t i = 0; i < count && i < kEntryCount; ++i)
            {
                const Tag& tag = e.tags[i];
                const uint8_t* entry = list + i * size;
                suppress[i] = tag.suppress && std::memcmp(&tag.xBits, entry, 4) == 0 &&
                              std::memcmp(&tag.scaleBits, entry + 0x10, 4) == 0;
                any |= suppress[i];
            }
            if (!any || count > kEntryCount)
            {
                original(self, camera);
                return;
            }
            std::memcpy(e.saved, list, count * size);
            __try
            {
                size_t kept = 0;
                for (size_t i = 0; i < count; ++i)
                    if (!suppress[i])
                        std::memcpy(list + (kept++) * size, e.saved + i * size, size);
                *reinterpret_cast<uint8_t**>(blob + e.endOffset) = list + kept * size;
                if (kept)
                    original(self, camera);
            }
            __finally
            {
                std::memcpy(list, e.saved, count * size);
                *reinterpret_cast<uint8_t**>(blob + e.endOffset) = end;
            }
        }

        // ---- construction blob --------------------------------------------
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
                return g_Cnst.effect[slot < 0 ? kFactionCount : static_cast<size_t>(slot)];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        void TaggedUpdate(FnUpdate original, void* self, float dt, size_t classOffset)
        {
            uint8_t* blob = static_cast<uint8_t*>(g_Cnst.blob);
            uint8_t* before = blob ? g_Cnst.End(blob) : nullptr;
            original(self, dt);
            if (!blob || !g_Cnst.controlLive || !AnyRender(g_Cnst))
                return;
            uintptr_t target = 0;
            const int effect = EffectFor(self, classOffset, target);
            TagAppended(g_Cnst, blob, before, reinterpret_cast<uintptr_t>(self), target, effect);
        }

        void __fastcall PreLoadHook(void* self, void*) { PreLoad(g_Cnst, self); }
        void __fastcall ControlHook(void* self, void*) { Control(g_Cnst, self); }
        void __fastcall SubmitHook(void* self, void*, void* camera) { Submit(g_Cnst, self, camera); }

        void __fastcall ProducerUpdateBuildHook(void* self, void*, float dt)
        {
            TaggedUpdate(g_ProducerOriginal, self, dt, kProducerClassOffset);
        }

        void __fastcall RigUpdateUnbuildHook(void* self, void*, float dt)
        {
            TaggedUpdate(g_RigOriginal, self, dt, kRigClassOffset);
        }

        // ---- portal blob --------------------------------------------------
        // site: 0 out effect, 1 in effect, 2 portal update. The build key is
        // (owner, site and in flag), so in and out blobs of one owner are
        // separate builds.
        void PortalAdd(void* blob, uintptr_t owner, uintptr_t site, const float* sphere, float t, int in)
        {
            uint8_t* self = static_cast<uint8_t*>(blob);
            const bool known = self && self == g_Port.blob;
            uint8_t* before = known ? g_Port.End(self) : nullptr;
            g_PortalAddBlob(blob, sphere, t, in);
            if (!known || !g_Port.controlLive || !AnyRender(g_Port) || !owner)
                return;
            uint8_t* after = g_Port.End(self);
            if (after != before + g_Port.entrySize || before < self + kListOffset)
                return;
            // The in flag as stored is what Submit reads to pick the sprite.
            const bool storedIn = before[kPortalInFlagOffset] != 0;
            const int effect = g_Port.effect[PortalSlot(storedIn)];
            TagAppended(g_Port, self, before, owner, (site << 1) | (storedIn ? 1u : 0u), effect);
        }

        void __fastcall PortalAddOutHook(void* blob, uintptr_t owner, const float* sphere, float t, int in)
        {
            PortalAdd(blob, owner, 0, sphere, t, in);
        }
        void __fastcall PortalAddInHook(void* blob, uintptr_t owner, const float* sphere, float t, int in)
        {
            PortalAdd(blob, owner, 1, sphere, t, in);
        }
        void __fastcall PortalAddUpdateHook(void* blob, uintptr_t owner, const float* sphere, float t, int in)
        {
            PortalAdd(blob, owner, 2, sphere, t, in);
        }

        // Entry contract at each wrapped call (bytes checked through the
        // engine rows' guards and the site offset): ecx = the PortalBlob,
        // [esp] = return into the caller, [esp+4] sphere*, [esp+8] t,
        // [esp+0xC] in; the callee pops 12 bytes (__thiscall, 3 stack args).
        // The caller has an ebp frame. Each thunk loads the owner into edx and
        // tail-jumps into a __fastcall hook with the same three stack
        // arguments, which also pops 12 bytes and returns to the caller.
        //   0x005CDBB0 / 0x005CDC40: param_1 (object handle) at [ebp+8],
        //     read by "8B 45 08 50" at +0x10 and never written.
        //   0x00660080: this stored by "89 4D E4" at +0x10 and reloaded by
        //     "8B 55 E4" at 0x00660246 just before the call.
        __declspec(naked) void PortalAddOutThunk()
        {
            __asm
            {
                mov edx, [ebp + 8]
                jmp PortalAddOutHook
            }
        }
        __declspec(naked) void PortalAddInThunk()
        {
            __asm
            {
                mov edx, [ebp + 8]
                jmp PortalAddInHook
            }
        }
        __declspec(naked) void PortalAddUpdateThunk()
        {
            __asm
            {
                mov edx, [ebp - 0x1C]
                jmp PortalAddUpdateHook
            }
        }

        void __fastcall PortalPreLoadHook(void* self, void*) { PreLoad(g_Port, self); }
        void __fastcall PortalControlHook(void* self, void*) { Control(g_Port, self); }
        void __fastcall PortalSubmitHook(void* self, void*, void* camera) { Submit(g_Port, self, camera); }

        bool IsConstructionName(const char* name)
        {
            return std::strcmp(name, kPreLoadPatch) == 0 || std::strcmp(name, kControlPatch) == 0 ||
                   std::strcmp(name, kSubmitPatch) == 0 || std::strcmp(name, kProducerPatch) == 0 ||
                   std::strcmp(name, kRigPatch) == 0;
        }

        bool IsPortalName(const char* name)
        {
            return std::strcmp(name, kPortalPreLoadPatch) == 0 || std::strcmp(name, kPortalControlPatch) == 0 ||
                   std::strcmp(name, kPortalSubmitPatch) == 0 || std::strcmp(name, kPortalOutPatch) == 0 ||
                   std::strcmp(name, kPortalInPatch) == 0 || std::strcmp(name, kPortalUpdatePatch) == 0;
        }

        void LogDecision(const Emitter& e, int& last, bool enabled, int decision)
        {
            if (decision == last)
                return;
            last = decision;
            LogShimA(LogLevel::Info, e.tag, "FactionConstructionBlobs=%d -> %s", enabled ? 1 : 0,
                     decision == 1 ? "hooks queued" : decision == 2 ? "engine rows unbound; stock" : "off (stock)");
        }
    }

    bool IsPatchName(const char* name)
    {
        return name && (IsConstructionName(name) || IsPortalName(name));
    }

    bool ShouldInstall()
    {
        static int s_lastCnst = -1;
        static int s_lastPort = -1;
        g_Cnst.backend = { BackendCreate, BackendUpdate, BackendDetach, &g_Cnst };
        g_Port.backend = { BackendCreate, BackendUpdate, BackendDetach, &g_Port };
        bool enabled = false;
        TryGetUserConfigBool(Hooks::kUserConfigDisplaySection, "FactionConstructionBlobs", enabled);
        bool cnst = false, port = false;
        if (enabled)
        {
            const uint32_t find = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderFind");
            const uint32_t update = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderUpdate");
            const uint32_t detach = HookEngine::ResolveNamedAddress("WeaponPresentation::RenderDetach");
            if (find && update && detach)
            {
                g_RenderFind = reinterpret_cast<RenderFind>(find);
                g_RenderUpdate = reinterpret_cast<RenderUpdate>(update);
                g_RenderDetach = reinterpret_cast<RenderDetach>(detach);
                const HookEngine::EngineRow cnstRows[] = {
                    {"ConstructionBlobPreLoad", &g_Cnst.preLoad},
                    {"ConstructionBlobControl", &g_Cnst.control},
                    {"ConstructionBlobSubmit", &g_Cnst.submit},
                    {"ProducerUpdateBuild", &g_ProducerUpdateBuildAddress},
                    {"ConstructionRigUpdateUnbuild", &g_RigUpdateUnbuildAddress},
                };
                cnst = HookEngine::BindEngineRows("FactionConstructionBlobs", cnstRows);
                const HookEngine::EngineRow portRows[] = {
                    {"PortalBlobPreLoad", &g_Port.preLoad},
                    {"PortalBlobControl", &g_Port.control},
                    {"PortalBlobSubmit", &g_Port.submit},
                    {"PortalBlobAddBlob", &g_PortalAddBlobAddress},
                    {"PortalBlobOutEffect", &g_PortalOutEffectAddress},
                    {"PortalBlobInEffect", &g_PortalInEffectAddress},
                    {"PortalUpdateBlob", &g_PortalUpdateAddress},
                };
                port = HookEngine::BindEngineRows("FactionConstructionBlobs portal blob", portRows);
            }
        }
        g_Cnst.installed = cnst;
        g_Port.installed = port;
        LogDecision(g_Cnst, s_lastCnst, enabled, !enabled ? 0 : (cnst ? 1 : 2));
        LogDecision(g_Port, s_lastPort, enabled, !enabled ? 0 : (port ? 1 : 2));
        return cnst || port;
    }

    bool ShouldInstallRow(const char* name)
    {
        if (!name)
            return false;
        if (IsConstructionName(name))
            return g_Cnst.installed;
        if (IsPortalName(name))
            return g_Port.installed;
        return false;
    }

    uint32_t DwordTarget(const char* name)
    {
        using HookFn = void(__fastcall*)(void*, void*);
        using SubmitFn = void(__fastcall*)(void*, void*, void*);
        const auto hook = [](HookFn fn) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(fn)); };
        const auto submit = [](SubmitFn fn) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(fn)); };
        if (!name)
            return 0;
        if (std::strcmp(name, kPreLoadPatch) == 0 && g_Cnst.preLoad)
            return hook(PreLoadHook);
        if (std::strcmp(name, kControlPatch) == 0 && g_Cnst.control)
            return hook(ControlHook);
        if (std::strcmp(name, kSubmitPatch) == 0 && g_Cnst.submit)
            return submit(SubmitHook);
        if (std::strcmp(name, kPortalPreLoadPatch) == 0 && g_Port.preLoad)
            return hook(PortalPreLoadHook);
        if (std::strcmp(name, kPortalControlPatch) == 0 && g_Port.control)
            return hook(PortalControlHook);
        if (std::strcmp(name, kPortalSubmitPatch) == 0 && g_Port.submit)
            return submit(PortalSubmitHook);
        return 0;
    }

    uint32_t Rel32Target(const char* name, void* original, uint32_t callSite)
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
        // Portal sites: the call must target AddBlob and sit at its checked
        // offset in the guarded caller, whose frame the thunk reads.
        if (name && target && g_PortalAddBlobAddress && target == g_PortalAddBlobAddress)
        {
            using Thunk = void (*)();
            Thunk thunk = nullptr;
            if (std::strcmp(name, kPortalOutPatch) == 0 && g_PortalOutEffectAddress &&
                callSite == g_PortalOutEffectAddress + kPortalOutSiteOffset)
                thunk = PortalAddOutThunk;
            else if (std::strcmp(name, kPortalInPatch) == 0 && g_PortalInEffectAddress &&
                     callSite == g_PortalInEffectAddress + kPortalInSiteOffset)
                thunk = PortalAddInThunk;
            else if (std::strcmp(name, kPortalUpdatePatch) == 0 && g_PortalUpdateAddress &&
                     callSite == g_PortalUpdateAddress + kPortalUpdateSiteOffset)
                thunk = PortalAddUpdateThunk;
            if (thunk)
            {
                g_PortalAddBlob = reinterpret_cast<FnAddBlob>(original);
                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thunk));
            }
        }
        LogShimA(LogLevel::Warn, name && IsPortalName(name) ? "PORTBLOB" : "CNSTBLOB",
                 "%s identity failed original=%p site=0x%08X; leaving stock call",
                 name ? name : "?", original, callSite);
        return 0;
    }

    void SceneTeardown() noexcept
    {
        for (Emitter* e : { &g_Cnst, &g_Port })
            if (e->installed && (!e->engineThreadId || e->engineThreadId == GetCurrentThreadId()))
                e->pool.ReleaseAll(e->backend);
    }
}
