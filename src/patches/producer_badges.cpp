// producer_badges.cpp
// BZR Open Shim - producer build badges. [Gameplay] RtsProducerBadges,
// default OFF. While on, every own-team producer (Recycler, Factory, Armory,
// Construction Rig) that is building something gets a small HUD badge a bit
// above it: the unit name of the item (ODF unitName, as the rally label) and
// the stock build progress in whole percent ("Tank 45%"). Same look as the
// producer "Rally" label.
// Read-only: it writes nothing the game reads, so it runs in multiplayer too.
// Engine facts and limits: Docs/PRODUCER_BADGES.md. Rules and layout:
// include/producer_badges_policy.h.
//
// Engine touch points (all reads):
//   * Producer vtables (RecyclerVtable, FactoryVtable, ArmoryVtable,
//     ConstructionRigVtable). Slot 7 (+0x1C) is the stock build-progress
//     getter, float __thiscall(this): Producer::GetBuildProgress 0x005AFA10;
//     the rig overrides it (0x0049CCF0).
//   * Building: +0x300 is the class being built (a rig with +0x3BC set uses
//     the class at +0x370). GameObjectClass ODF name: char[8] at class +0x30.
//   * Object vector (GameObject::objectList), team +0x174, network replica
//     byte +0x80 == 2, dead flag 0x200 in obj76 (+0xF4) flags (+0x14).
//   * The main camera record, as producer_rally_points.cpp reads it (a
//     minimal copy of that read: the rally module binds its camera rows only
//     while it is installed).
// Threads: the scan and the name lookup run on the frame/game thread at 5 Hz
// (the lookup reads files and allocates); the HUD painter runs on the same
// thread inside the HUD pass, copies the table under a lock and re-reads the
// live progress and position every frame.
#include <cmath>

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "kill_ticker.h"
#include "patcher.h"
#include "producer_badges_policy.h"
#include "producer_rally_policy.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <string>

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Policy = ProducerBadgesPolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCameraRecord = const uint8_t*(__cdecl*)();
        using FnProgress = float(__thiscall*)(void* self);

        constexpr size_t kProgressSlot = 7;
        constexpr size_t kBuildClassOffset = 0x300;
        constexpr size_t kRigBuildFlagOffset = 0x3BC;
        constexpr size_t kRigBuildClassOffset = 0x370;
        constexpr size_t kClassOdfOffset = 0x30;
        constexpr size_t kOwnershipOffset = 0x80; // == 2: network replica
        constexpr uint8_t kReplicaOwnership = 2;
        constexpr size_t kObj76FlagsOffset = 0x14;
        constexpr uint32_t kObj76DeadFlag = 0x200;
        constexpr size_t kMaxObjects = 4096;

        // Camera record, as producer_rally_points.cpp.
        constexpr size_t kCameraMatrixOffset = 0x40;
        constexpr size_t kCameraTranslationOffset = kCameraMatrixOffset + 0x28;
        constexpr size_t kViewRecordCurrentViewOffset = 8;
        constexpr size_t kViewRecordCameraValidBackOffset = 0x20;

        constexpr ULONGLONG kScanPeriodMs = 200;
        constexpr ULONGLONG kTableMaxAgeMs = 1000;
        constexpr int kMaxInstallAttempts = 40;
        constexpr int kLogBudget = 64;
        constexpr uint32_t kTextColor = 0xFF60FF60;  // the rally label
        constexpr uint32_t kPanelColor = 0x90000000; // the rally label
        constexpr size_t kNameCacheSize = 32;

        uint32_t g_ObjectListGlobal = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_CameraRecordAddr = 0;
        uint32_t g_ViewRecordAddr = 0;
        uint32_t g_RecyclerVtable = 0;
        uint32_t g_FactoryVtable = 0;
        uint32_t g_ArmoryVtable = 0;
        uint32_t g_RigVtable = 0;
        FnGetObj g_FnGetObj = nullptr;

        bool g_ConfigRead = false;
        std::atomic<bool> g_Enabled{ false };
        int g_InstallState = 0; // 0 trying, 1 ready, -1 gave up; game thread only
        int g_InstallAttempts = 0;
        bool g_PainterSet = false;
        ULONGLONG g_LastScan = 0;
        int g_LogBudget = kLogBudget;

        // Game thread only.
        Policy::Entry g_Work[Policy::kMaxBadges];
        size_t g_WorkCount = 0;
        struct NameCacheEntry
        {
            char odf[Policy::kOdfChars + 1];
            char label[Policy::kLabelChars];
        };
        NameCacheEntry g_NameCache[kNameCacheSize];
        size_t g_NameCacheCount = 0;
        void* g_Scratch[kMaxObjects] = {};

        struct Published
        {
            ULONGLONG takenAt = 0;
            size_t count = 0;
            Policy::Entry entries[Policy::kMaxBadges];
        };
        SRWLOCK g_Lock = SRWLOCK_INIT;
        Published g_Published;

        // ---- fault-safe reads (no C++ objects, so __try is legal) ----------

        uint32_t ReadU32(uintptr_t address)
        {
            if (address < 0x10000)
                return 0;
            __try
            {
                return *reinterpret_cast<const uint32_t*>(address);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool ReadInt(uintptr_t address, int& out)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                out = *reinterpret_cast<const int*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* SafeGetObj(uint32_t handle)
        {
            if (!g_FnGetObj || handle == 0)
                return nullptr;
            __try
            {
                return g_FnGetObj(handle);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        uint32_t SafeGetHandle(void* obj)
        {
            const auto fn = reinterpret_cast<FnGetHandle>(g_GameObjectGetHandleAddr);
            if (!fn || !obj)
                return 0;
            __try
            {
                return fn(obj);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        size_t SnapshotObjects(void** out, size_t capacity)
        {
            if (!g_ObjectListGlobal)
                return 0;
            size_t count = 0;
            __try
            {
                const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_ObjectListGlobal);
                if (!vec)
                    return 0;
                void* const* first = *reinterpret_cast<void* const* const*>(vec);
                void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                if (!first || last < first)
                    return 0;
                const size_t available = static_cast<size_t>(last - first);
                if (available > kMaxObjects)
                    return 0;
                for (size_t i = 0; i < available && count < capacity; ++i)
                {
                    if (first[i])
                        out[count++] = first[i];
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
            return count;
        }

        bool IsProducerVtable(uint32_t vtable)
        {
            return vtable != 0 && (vtable == g_RecyclerVtable || vtable == g_FactoryVtable ||
                                   vtable == g_ArmoryVtable || vtable == g_RigVtable);
        }

        // The class being built, or 0 when idle or unreadable.
        uint32_t BuildClassOf(const uint8_t* obj, uint32_t vtable)
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            const bool isRig = vtable == g_RigVtable;
            const uint32_t at300 = ReadU32(base + kBuildClassOffset);
            const uint32_t at3BC = isRig ? ReadU32(base + kRigBuildFlagOffset) : 0;
            const uint32_t at370 = isRig ? ReadU32(base + kRigBuildClassOffset) : 0;
            const uint32_t cls = Policy::BuildingClass(isRig, at300, at3BC, at370);
            return cls >= 0x10000 ? cls : 0;
        }

        // One object: a live, local producer of `userTeam` that is building.
        bool ReadCandidate(void* object, int userTeam, Policy::Candidate& out)
        {
            __try
            {
                const uint8_t* const obj = static_cast<const uint8_t*>(object);
                const uint32_t vtable = *reinterpret_cast<const uint32_t*>(obj);
                if (!IsProducerVtable(vtable) ||
                    *reinterpret_cast<const int32_t*>(obj + kGameObjectActualTeamOffset) != userTeam ||
                    obj[kOwnershipOffset] == kReplicaOwnership)
                    return false;
                const uint8_t* const obj76 = *reinterpret_cast<const uint8_t* const*>(obj + kGameObjectObjOffset);
                if (obj76 && (*reinterpret_cast<const uint32_t*>(obj76 + kObj76FlagsOffset) & kObj76DeadFlag))
                    return false;
                const uint32_t cls = BuildClassOf(obj, vtable);
                if (cls == 0)
                    return false;
                char raw[Policy::kOdfChars] = {};
                std::memcpy(raw, reinterpret_cast<const void*>(static_cast<uintptr_t>(cls) + kClassOdfOffset),
                            sizeof(raw));
                Policy::CopyOdf(raw, sizeof(raw), out.odf);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The frame's live read of one badge: still a producer and still
        // building; progress from the stock getter (vtable slot 7).
        bool ReadLive(void* object, float& progress)
        {
            __try
            {
                const uint8_t* const obj = static_cast<const uint8_t*>(object);
                const uint32_t vtable = *reinterpret_cast<const uint32_t*>(obj);
                if (!IsProducerVtable(vtable) || BuildClassOf(obj, vtable) == 0)
                    return false;
                const auto fn = *reinterpret_cast<const FnProgress*>(static_cast<uintptr_t>(vtable) +
                                                                      kProgressSlot * sizeof(void*));
                progress = Policy::ClampProgress(fn(object));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadCamera(ProducerRallyPolicy::CameraProjection& cam)
        {
            if (!g_CameraRecordAddr || !g_ViewRecordAddr)
                return false;
            __try
            {
                const int view = *reinterpret_cast<const int*>(g_ViewRecordAddr + kViewRecordCurrentViewOffset);
                if (view != 0 && view != 1 && view != 2 && view != 7)
                    return false;
                if (*reinterpret_cast<const int*>(g_ViewRecordAddr - kViewRecordCameraValidBackOffset) == 0)
                    return false;
                const uint8_t* record = reinterpret_cast<FnCameraRecord>(g_CameraRecordAddr)();
                if (!record)
                    return false;
                const float* head = reinterpret_cast<const float*>(record);
                cam.centerX = head[0];
                cam.centerY = head[1];
                cam.scaleX = head[2];
                cam.scaleY = head[3];
                std::memcpy(cam.rot, record + kCameraMatrixOffset, sizeof(cam.rot));
                std::memcpy(cam.trans, record + kCameraTranslationOffset, sizeof(cam.trans));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // ---- install ---------------------------------------------------------

        bool TryInstall()
        {
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                return false;
            const HookEngine::EngineRow rows[] = {
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "GetCameraRecord", &g_CameraRecordAddr },
                { "ViewRecord", &g_ViewRecordAddr },
                { "RecyclerVtable", &g_RecyclerVtable },
                { "FactoryVtable", &g_FactoryVtable },
                { "ArmoryVtable", &g_ArmoryVtable },
                { "ConstructionRigVtable", &g_RigVtable },
            };
            if (!HookEngine::BindEngineRows("Producer badges", rows))
                return false;
            g_ObjectListGlobal = HookEngine::ResolveNamedAddress("GameObject::objectList");
            if (g_GameObjectGetHandleAddr == 0 || g_ObjectListGlobal == 0)
            {
                Log(L"[BADGES] GetHandle or object list unresolved; badges inert\n");
                return false;
            }
            g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
            return true;
        }

        // Game thread. Bounded retries (on Steam a row can be a page SteamStub
        // has not finished with); Ensure() is game-thread only.
        bool EnsureInstalled()
        {
            if (g_InstallState != 0)
                return g_InstallState > 0;
            ++g_InstallAttempts;
            if (TryInstall())
            {
                if (!HudGaugeOverlay::Ensure())
                {
                    g_InstallState = -1;
                    MarkOptionHookFailed("RtsProducerBadges",
                                         "Unavailable: the HUD overlay did not hook on this game build (see openshim.log).");
                    Log(L"[BADGES] HUD overlay unavailable; badges inert\n");
                    return false;
                }
                g_InstallState = 1;
                ClearOptionHookFailed("RtsProducerBadges");
                Log(L"[BADGES] installed (attempt %d)\n", g_InstallAttempts);
                return true;
            }
            MarkOptionHookFailed("RtsProducerBadges",
                                 "Unavailable: Producer Badges did not bind on this game build (see openshim.log).");
            if (g_InstallAttempts >= kMaxInstallAttempts)
            {
                g_InstallState = -1;
                Log(L"[BADGES] engine rows did not bind after %d attempts; badges inert\n", g_InstallAttempts);
            }
            return false;
        }

        // ---- the scan (game thread) ------------------------------------------

        void* UserObject()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            return slot ? reinterpret_cast<void*>(ReadU32(slot)) : nullptr;
        }

        bool HudContextOk()
        {
            if (!UserObject() || IsPauseMenuOpen())
                return false;
            const ShellUiState ui = ReadShellUiState();
            if (!ui.readable)
                return false;
            return !(ui.wrapperActive && ui.screenPresent && IsNonGameplayScreenType(ui.screenType));
        }

        void Publish(const Policy::Entry* entries, size_t count, ULONGLONG now)
        {
            AcquireSRWLockExclusive(&g_Lock);
            g_Published.takenAt = now;
            g_Published.count = count;
            for (size_t i = 0; i < count; ++i)
                g_Published.entries[i] = entries[i];
            ReleaseSRWLockExclusive(&g_Lock);
        }

        // Display name of an ODF: cached; the lookup reads files and
        // allocates, so it runs here on the game thread only.
        void ResolveLabel(Policy::Entry& entry)
        {
            for (size_t i = 0; i < g_NameCacheCount; ++i)
            {
                if (_stricmp(g_NameCache[i].odf, entry.odf) == 0)
                {
                    std::memcpy(entry.label, g_NameCache[i].label, sizeof(entry.label));
                    return;
                }
            }
            std::string name;
            try
            {
                name = KillTicker::LookupUnitName(entry.odf);
            }
            catch (...)
            {
                name.clear();
            }
            Policy::FormatLabel(name.c_str(), entry.odf, entry.label, sizeof(entry.label));
            // A failed lookup shows the ODF name now and is retried next scan.
            if (!name.empty() && g_NameCacheCount < kNameCacheSize)
            {
                NameCacheEntry& slot = g_NameCache[g_NameCacheCount++];
                std::memcpy(slot.odf, entry.odf, sizeof(slot.odf));
                std::memcpy(slot.label, entry.label, sizeof(slot.label));
            }
        }

        void LogChange(Policy::Change change, const Policy::Entry& entry)
        {
            if (g_LogBudget <= 0)
                return;
            --g_LogBudget;
            if (change == Policy::Change::Removed)
                Log(L"[BADGES] badge off handle=0x%08X odf=%hs\n", entry.handle, entry.odf);
            else
                Log(L"[BADGES] badge on handle=0x%08X odf=%hs\n", entry.handle, entry.odf);
        }

        void Scan(ULONGLONG now)
        {
            void* const user = UserObject();
            int userTeam = 0;
            if (!user || !HudContextOk() || !ReadInt(reinterpret_cast<uintptr_t>(user) + kGameObjectActualTeamOffset, userTeam))
            {
                if (g_WorkCount != 0)
                    g_WorkCount = Policy::Reconcile(g_Work, g_WorkCount, nullptr, 0, LogChange);
                Publish(g_Work, g_WorkCount, now);
                return;
            }
            Policy::Candidate found[Policy::kMaxBadges];
            size_t foundCount = 0;
            const size_t n = SnapshotObjects(g_Scratch, kMaxObjects);
            for (size_t i = 0; i < n && foundCount < Policy::kMaxBadges; ++i)
            {
                Policy::Candidate c;
                if (!ReadCandidate(g_Scratch[i], userTeam, c))
                    continue;
                c.handle = SafeGetHandle(g_Scratch[i]);
                if (c.handle == 0)
                    continue;
                found[foundCount++] = c;
            }
            g_WorkCount = Policy::Reconcile(g_Work, g_WorkCount, found, foundCount, LogChange);
            for (size_t i = 0; i < g_WorkCount; ++i)
                if (g_Work[i].label[0] == '\0')
                    ResolveLabel(g_Work[i]);
            Publish(g_Work, g_WorkCount, now);
        }

        // ---- the painter (frame thread, inside the HUD pass) ---------------

        // Backing-panel half width: the measured text when the frame offers a
        // sane measure, else a per-glyph estimate.
        int PanelHalfWidth(const HudGaugeOverlay::Frame& frame, const char* text) noexcept
        {
            float w = 0.0f, h = 0.0f;
            if (frame.measure && frame.style)
            {
                __try
                {
                    frame.measure(frame.style, text, &w, &h);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    w = 0.0f;
                }
            }
            if (std::isfinite(w) && w > 0.0f && w < 400.0f)
                return static_cast<int>(w * 0.5f) + 6;
            return static_cast<int>(std::strlen(text)) * 4 + 6;
        }

        // Last logged progress quarter per badge (frame thread only).
        struct ProgressLog
        {
            uint32_t handle;
            int quarter;
        };
        ProgressLog g_ProgressLog[16] = {};

        // Logs each badge's progress when it enters a new quarter (0-4).
        void LogProgress(uint32_t handle, float progress)
        {
            const int quarter = static_cast<int>(progress * 4.0f);
            ProgressLog* slot = nullptr;
            for (ProgressLog& p : g_ProgressLog)
            {
                if (p.handle == handle)
                {
                    slot = &p;
                    break;
                }
                if (!slot && p.handle == 0)
                    slot = &p;
            }
            if (!slot)
                slot = &g_ProgressLog[handle % 16];
            if (slot->handle == handle && slot->quarter == quarter)
                return;
            *slot = { handle, quarter };
            if (g_LogBudget <= 0)
                return;
            --g_LogBudget;
            Log(L"[BADGES] progress handle=0x%08X pct=%d\n", handle, Policy::ProgressPercent(progress));
        }

        bool PaintBadges(const HudGaugeOverlay::Frame& frame) noexcept
        {
            if (!g_Enabled.load(std::memory_order_acquire))
                return true;
            static Published snap; // frame thread only; keeps the painter's stack small
            AcquireSRWLockShared(&g_Lock);
            snap = g_Published;
            ReleaseSRWLockShared(&g_Lock);
            if (snap.count == 0 || GetTickCount64() - snap.takenAt > kTableMaxAgeMs)
                return true;
            ProducerRallyPolicy::CameraProjection cam;
            if (!ReadCamera(cam))
                return true;

            for (size_t i = 0; i < snap.count; ++i)
            {
                const Policy::Entry& entry = snap.entries[i];
                void* const obj = SafeGetObj(entry.handle);
                float progress = 0.0f;
                float pos[3] = {};
                if (!obj || !ReadLive(obj, progress) || !TryGetGameObjectWorldPosition(obj, pos))
                    continue;
                LogProgress(entry.handle, progress);
                float sx = 0.0f, sy = 0.0f;
                if (!ProducerRallyPolicy::ProjectToScreen(cam, pos, sx, sy) ||
                    !ProducerRallyPolicy::OnScreen(sx, sy, frame.viewW, frame.viewH))
                    continue;
                char text[Policy::kLabelChars + 8];
                Policy::FormatBadgeText(entry.label, Policy::ProgressPercent(progress), text, sizeof(text));
                const Policy::Layout l = Policy::ComputeLayout(static_cast<int>(sx), static_cast<int>(sy),
                                                               PanelHalfWidth(frame, text));
                if (!HudGaugeOverlay::DrawPanelText(frame, l.panel.x1, l.panel.y1, l.panel.x2, l.panel.y2,
                                                    kPanelColor, l.textX, l.textY, text, kTextColor, 1))
                    return false;
            }
            return true;
        }
    }

    void ReloadProducerBadgesConfig()
    {
        bool value = false;
        const bool enabled = TryGetUserConfigBool("Gameplay", "RtsProducerBadges", value) ? value : false;
        if (!g_ConfigRead || enabled != g_Enabled.load(std::memory_order_relaxed))
            Log(L"[BADGES] enabled=%hs\n", enabled ? "yes" : "no");
        g_ConfigRead = true;
        g_Enabled.store(enabled, std::memory_order_release);
    }

    // World render tick (frame/game thread).
    void TickProducerBadges()
    {
        if (!g_ConfigRead)
            ReloadProducerBadgesConfig();
        if (!g_Enabled.load(std::memory_order_acquire))
        {
            if (g_PainterSet)
            {
                HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::ProducerBadges, nullptr);
                g_PainterSet = false;
                g_WorkCount = Policy::Reconcile(g_Work, g_WorkCount, nullptr, 0, LogChange);
                Publish(g_Work, 0, 0);
            }
            return;
        }
        const ULONGLONG now = GetTickCount64();
        if (now - g_LastScan < kScanPeriodMs)
            return;
        g_LastScan = now;
        if (!EnsureInstalled())
            return;
        if (!g_PainterSet)
        {
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::ProducerBadges, &PaintBadges);
            g_PainterSet = true;
        }
        Scan(now);
    }

    // Mission end/load: drop the old mission's badges and cached names.
    void ResetProducerBadges()
    {
        g_WorkCount = 0;
        g_NameCacheCount = 0;
        g_LastScan = 0;
        for (ProgressLog& p : g_ProgressLog)
            p = {};
        g_LogBudget = kLogBudget;
        Publish(g_Work, 0, 0);
    }
}
