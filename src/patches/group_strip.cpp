// group_strip.cpp
// BZR Open Shim - HUD group strip. [Gameplay] GroupStrip, default ON.
// Stock Redux shows nothing about the F1-F7 unit groups; this draws one
// BZCC-style row next to the scrap/pilot gauge, e.g.
// "F1 4xTank  F2 2xBomber  F5 1xTurret+". Read-only: it never writes a group,
// a game object or anything the simulation reads, so it also runs in
// multiplayer (the groups are the local ControlPanel's).
// Rules and layout: include/group_strip_policy.h. Evidence and limits:
// Docs/PRODUCER_RALLY_POINTS.md ("Group strip").
//
// Engine touch points (all reads):
//   * ControlPanel (global 0x00978E20): groupNum[10] at +0xFC4, groupList at
//     +0x18C with 0x16C bytes per group (the layout auto_group_new_units.cpp
//     documents; ControlPanelGlobal/ControlPanelVtable rows).
//   * GameObject +0x18 vtable[0] -> GameObjectClass (TryGetCraftOdfName's
//     path); GameObjectClass +0x64 is unitName
//     char[0x20], guarded by the GroupStripUnitNameRead code row.
//   * The six ScrapHud*Point rows, the gauge's live draw positions.
// Threads: the snapshot is taken at 4 Hz on the frame/game thread from the
// world render tick; the HUD painter (same thread, inside the HUD pass) only
// reads the snapshot and the HUD text primitives.
#include <cmath>

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "game_state.h"
#include "group_strip_policy.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Policy = GroupStripPolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);

        // ControlPanel groups (FUN_004a6f00 BindGroup lines 6-10), the same
        // layout auto_group_new_units.cpp writes.
        constexpr size_t kGroupNumOffset = 0xFC4;
        constexpr size_t kGroupListOffset = 0x18C;
        constexpr size_t kGroupStride = 0x16C;
        static_assert(kGroupListOffset + 10 * kGroupStride == kGroupNumOffset, "groupList ends where groupNum starts");
        static_assert(Policy::kGroupCapacity * 4 == static_cast<int>(kGroupStride), "91 handles per group");
        // GameObjectClass::unitName (FUN_004e0450 line 89; GOG 0x004E064F
        // `mov edx,[ebp-0x74]; add edx,0x64; push edx; push 0x45A8BC04`).
        constexpr size_t kClassUnitNameOffset = 0x64;
        constexpr size_t kUnitNameChars = 0x20;

        constexpr ULONGLONG kSnapshotPeriodMs = 250;
        // A snapshot older than this is not drawn (the world stopped
        // rendering, so the tick stopped).
        constexpr ULONGLONG kSnapshotMaxAgeMs = 1000;
        constexpr int kMaxInstallAttempts = 40;
        constexpr uint32_t kPanelColor = 0x8C000000u;
        constexpr uint32_t kTextColor = 0xFFD1FFD1u;

        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_ControlPanelVtableAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_UnitNameReadAddr = 0;
        uint32_t g_GaugePointAddrs[Policy::kGaugePointCount] = {};
        bool g_GaugePointsBound = false;
        FnGetObj g_FnGetObj = nullptr;

        bool g_ConfigRead = false;
        std::atomic<bool> g_Enabled{ true };
        int g_InstallState = 0; // 0 trying, 1 ready, -1 gave up; game thread only
        int g_InstallAttempts = 0;
        bool g_PainterSet = false;
        ULONGLONG g_LastSnapshot = 0;

        struct Snapshot
        {
            bool visible = false;
            ULONGLONG takenAt = 0;
            size_t count = 0;
            Policy::StripGroup groups[Policy::kKeyedGroupCount];
            bool gaugeKnown = false;
            int gaugePoints[Policy::kGaugePointCount * 2] = {};
        };

        SRWLOCK g_SnapshotLock = SRWLOCK_INIT;
        Snapshot g_Snapshot;

        // ---- fault-safe reads (no C++ objects, so __try is legal) ----------

        void* ReadPtr(uintptr_t address)
        {
            if (address < 0x10000)
                return nullptr;
            __try
            {
                return *reinterpret_cast<void* const*>(address);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool ReadBytes(uintptr_t address, void* out, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(out, reinterpret_cast<const void*>(address), size);
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

        bool ControlPanelIdentityOk()
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(g_ControlPanelAddr));
            return vtable != 0 && vtable == g_ControlPanelVtableAddr &&
                   VtableTypeNameMatches(vtable, ".?AVControlPanel@@");
        }

        bool TryInstall()
        {
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                return false;
            const HookEngine::EngineRow rows[] = {
                { "ControlPanelGlobal", &g_ControlPanelAddr },
                { "ControlPanelVtable", &g_ControlPanelVtableAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                // Code guard only: the bytes prove unitName is at class +0x64.
                { "GroupStripUnitNameRead", &g_UnitNameReadAddr },
            };
            if (!HookEngine::BindEngineRows("Group strip", rows))
                return false;
            if (!ControlPanelIdentityOk())
            {
                Log(L"[GROUPSTRIP] ControlPanel identity check failed (global=0x%08X vtable row=0x%08X)\n",
                    g_ControlPanelAddr, g_ControlPanelVtableAddr);
                return false;
            }
            g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);

            // Optional: without the live points the strip assumes the stock
            // gauge position (EstimatedStockGaugeRect).
            const HookEngine::EngineRow points[] = {
                { "ScrapHudScrapTitlePoint", &g_GaugePointAddrs[0] },
                { "ScrapHudScrapValuePoint", &g_GaugePointAddrs[1] },
                { "ScrapHudPilotTitlePoint", &g_GaugePointAddrs[2] },
                { "ScrapHudPilotValuePoint", &g_GaugePointAddrs[3] },
                { "ScrapHudScrapPanelPoint", &g_GaugePointAddrs[4] },
                { "ScrapHudPilotPanelPoint", &g_GaugePointAddrs[5] },
            };
            g_GaugePointsBound = HookEngine::BindEngineRows("Group strip gauge points", points);
            if (!g_GaugePointsBound)
                Log(L"[GROUPSTRIP] gauge point rows did not bind; assuming the stock gauge position\n");
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
                    MarkOptionHookFailed("GroupStrip",
                                         "Unavailable: the HUD overlay did not hook on this game build (see openshim.log).");
                    Log(L"[GROUPSTRIP] HUD overlay unavailable; strip hidden\n");
                    return false;
                }
                g_InstallState = 1;
                ClearOptionHookFailed("GroupStrip");
                Log(L"[GROUPSTRIP] installed (ControlPanel 0x%08X, gauge points %hs, attempt %d)\n",
                    g_ControlPanelAddr, g_GaugePointsBound ? "live" : "estimated", g_InstallAttempts);
                return true;
            }
            g_ControlPanelAddr = 0;
            g_FnGetObj = nullptr;
            MarkOptionHookFailed("GroupStrip",
                                 "Unavailable: Group Strip did not bind on this game build (see openshim.log).");
            if (g_InstallAttempts >= kMaxInstallAttempts)
            {
                g_InstallState = -1;
                Log(L"[GROUPSTRIP] gave up after %d attempts; strip unavailable\n", g_InstallAttempts);
            }
            return false;
        }

        // ---- the snapshot (game thread) ------------------------------------

        // The object's GameObjectClass through its class sub-object's
        // vtable[0] (GameObject +0x18), the path TryGetCraftOdfName uses. Not
        // the raw +0xF8 pointer: odf_helpers.cpp found that names another
        // record for Craft.
        uintptr_t SafeGetClass(void* obj)
        {
            using FnGetClass = void*(__thiscall*)(void*);
            void* const sub = reinterpret_cast<uint8_t*>(obj) + kGameObjectClassSubObjOffset;
            void* const vtable = ReadPtr(reinterpret_cast<uintptr_t>(sub));
            void* const fn = vtable ? ReadPtr(reinterpret_cast<uintptr_t>(vtable)) : nullptr;
            if (!fn)
                return 0;
            __try
            {
                return reinterpret_cast<uintptr_t>(reinterpret_cast<FnGetClass>(fn)(sub));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool ResolveMember(uint32_t handle, Policy::MemberInfo& info)
        {
            void* const obj = SafeGetObj(handle);
            if (!obj)
                return false;
            const uintptr_t cls = SafeGetClass(obj);
            info.classKey = cls;
            char unitName[kUnitNameChars] = {};
            const bool haveName = cls >= 0x10000 && ReadBytes(cls + kClassUnitNameOffset, unitName, sizeof(unitName));
            char odf[16] = {};
            TryGetCraftOdfName(obj, odf, sizeof(odf));
            Policy::ChooseDisplayName(haveName ? unitName : nullptr, sizeof(unitName), odf, info.name,
                                      sizeof(info.name));
            return true;
        }

        void* UserObject()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            return slot ? ReadPtr(slot) : nullptr;
        }

        // Gameplay with the HUD up: a player object, no pause menu, no shell
        // screen over the world (the rally points' WorldInteractive test).
        bool HudContextOk()
        {
            if (!UserObject() || IsPauseMenuOpen())
                return false;
            const ShellUiState ui = ReadShellUiState();
            if (!ui.readable)
                return false;
            return !(ui.wrapperActive && ui.screenPresent && IsNonGameplayScreenType(ui.screenType));
        }

        void Publish(const Snapshot& snap)
        {
            AcquireSRWLockExclusive(&g_SnapshotLock);
            g_Snapshot = snap;
            ReleaseSRWLockExclusive(&g_SnapshotLock);
        }

        void TakeSnapshot(ULONGLONG now)
        {
            Snapshot snap;
            snap.takenAt = now;
            if (!HudContextOk() || !ControlPanelIdentityOk())
            {
                Publish(snap);
                return;
            }
            for (int g = 0; g < Policy::kKeyedGroupCount; ++g)
            {
                int stored = 0;
                uint32_t handles[Policy::kGroupCapacity] = {};
                if (!ReadBytes(g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(g), &stored,
                               sizeof(stored)))
                {
                    Publish(Snapshot{});
                    return;
                }
                if (stored <= 0)
                    continue;
                if (stored > Policy::kGroupCapacity)
                    stored = Policy::kGroupCapacity;
                if (!ReadBytes(g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(g), handles,
                               static_cast<size_t>(stored) * 4))
                {
                    Publish(Snapshot{});
                    return;
                }
                const Policy::StripGroup group = Policy::SummarizeGroup(
                    g, handles, stored, [](uint32_t h, Policy::MemberInfo& info) { return ResolveMember(h, info); });
                if (group.liveCount > 0)
                    snap.groups[snap.count++] = group;
            }
            if (g_GaugePointsBound)
            {
                bool ok = true;
                for (size_t p = 0; p < Policy::kGaugePointCount && ok; ++p)
                {
                    int xy[2] = {};
                    ok = ReadBytes(g_GaugePointAddrs[p], xy, sizeof(xy)) && xy[0] > -4096 && xy[0] < 16384 &&
                         xy[1] > -4096 && xy[1] < 16384;
                    snap.gaugePoints[p * 2] = xy[0];
                    snap.gaugePoints[p * 2 + 1] = xy[1];
                }
                snap.gaugeKnown = ok;
            }
            snap.visible = snap.count != 0;
            Publish(snap);
        }

        // ---- the painter (frame thread, inside the HUD pass) ---------------

        // True when the text has a size. `faulted` is set only by a fault: a
        // zero size (fonts reloading after a resolution change or device
        // reset) just skips the frame, and must not turn the slot off.
        bool Measure(const HudGaugeOverlay::Frame& frame, const char* text, int& w, int& h, bool& faulted) noexcept
        {
            float fw = 0.0f, fh = 0.0f;
            __try
            {
                frame.measure(frame.style, text, &fw, &fh);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                faulted = true;
                return false;
            }
            if (!std::isfinite(fw) || !std::isfinite(fh))
                return false;
            w = static_cast<int>(fw + 0.999f);
            h = static_cast<int>(fh + 0.999f);
            return w > 0 && h > 0;
        }

        bool PaintStrip(const HudGaugeOverlay::Frame& frame) noexcept
        {
            if (!g_Enabled.load(std::memory_order_acquire))
                return true;
            Snapshot snap;
            AcquireSRWLockShared(&g_SnapshotLock);
            snap = g_Snapshot;
            ReleaseSRWLockShared(&g_SnapshotLock);
            if (!snap.visible || snap.count == 0 || GetTickCount64() - snap.takenAt > kSnapshotMaxAgeMs)
                return true;

            int sampleW = 0, textH = 0;
            bool faulted = false;
            if (!Measure(frame, "F1 0x", sampleW, textH, faulted))
                return !faulted;
            const Policy::Rect gauge = snap.gaugeKnown
                ? Policy::GaugeRectFromPoints(snap.gaugePoints, textH)
                : Policy::EstimatedStockGaugeRect(frame.viewW, frame.viewH);

            char text[Policy::kTextBufferSize] = {};
            bool measureFailed = false;
            const Policy::Layout layout = Policy::ChooseLayout(
                snap.groups, snap.count, frame.viewW, frame.viewH, gauge, textH,
                [&](const char* t, int& w, int& h) {
                    if (Measure(frame, t, w, h, faulted))
                        return true;
                    measureFailed = true;
                    return false;
                },
                text, sizeof(text));
            if (measureFailed)
                return !faulted; // a zero size skips this frame only
            if (layout.placement == Policy::Placement::None || text[0] == '\0')
                return true;
            return HudGaugeOverlay::DrawPanelText(frame, layout.panel.x1, layout.panel.y1, layout.panel.x2,
                                                  layout.panel.y2, kPanelColor, layout.textX, layout.textY, text,
                                                  kTextColor, 0);
        }
    }

    void ReloadGroupStripConfig()
    {
        bool value = true;
        const bool enabled = TryGetUserConfigBool("Gameplay", "GroupStrip", value) ? value : true;
        if (!g_ConfigRead || enabled != g_Enabled.load(std::memory_order_relaxed))
            Log(L"[GROUPSTRIP] enabled=%hs\n", enabled ? "yes" : "no");
        g_ConfigRead = true;
        g_Enabled.store(enabled, std::memory_order_release);
    }

    // World render tick (frame/game thread).
    void TickGroupStrip()
    {
        if (!g_ConfigRead)
            ReloadGroupStripConfig();
        if (!g_Enabled.load(std::memory_order_acquire))
        {
            if (g_PainterSet)
            {
                HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::GroupStrip, nullptr);
                g_PainterSet = false;
                Publish(Snapshot{});
            }
            return;
        }
        const ULONGLONG now = GetTickCount64();
        if (now - g_LastSnapshot < kSnapshotPeriodMs)
            return;
        g_LastSnapshot = now;
        if (!EnsureInstalled())
            return;
        if (!g_PainterSet)
        {
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::GroupStrip, &PaintStrip);
            g_PainterSet = true;
        }
        TakeSnapshot(now);
    }

    // Mission end/load: drop the old mission's snapshot.
    void ResetGroupStrip()
    {
        Publish(Snapshot{});
        g_LastSnapshot = 0;
    }
}
