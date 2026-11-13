// auto_group_new_units.cpp
// BZR Open Shim - auto-group newly built units. [Gameplay] AutoGroupNewUnits,
// default OFF, single player only. When the player's Recycler or Factory
// finishes a unit, it is added to an F1-F7 group (ported from BZCC's
// SetBestGroup): the first keyed group (0-6, the ones input.map binds) whose
// live members all have the same ODF and number fewer than 10, else the first
// empty keyed group, else none. The entry is appended to the stock ControlPanel group directly, so
// the group keys select it and the stock mission save keeps it.
// Addresses, evidence and limits: Docs/PRODUCER_RALLY_POINTS.md.
//
// Engine touch points:
//   * The Recycler/Factory FinishBuild slot-42 hook owned by
//     producer_rally_points.cpp (EnsureProducerFinishBuildHook); this file
//     only consumes it (AutoGroupOnUnitBuilt), it installs no hook of its own.
//   * ControlPanel (global 0x00978E20): groupNum[10] at +0xFC4, groupList at
//     +0x18C with 0x16C bytes (91 handles) per group. Written on the game
//     thread from inside FinishBuild, the thread the group keys run on.
#include "auto_group_policy.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
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
        namespace Policy = AutoGroupPolicy;

        using FnCanCommand = bool(__thiscall*)(void* obj);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);

        constexpr size_t kCanCommandSlot = 14;
        // ControlPanel groups (FUN_004a6f00 BindGroup lines 6-10).
        constexpr size_t kGroupNumOffset = 0xFC4;
        constexpr size_t kGroupListOffset = 0x18C;
        constexpr size_t kGroupStride = 0x16C;
        static_assert(kGroupListOffset + Policy::kGroupCount * kGroupStride == kGroupNumOffset,
                      "groupList ends where groupNum starts");
        static_assert(Policy::kGroupCapacity * 4 == static_cast<int>(kGroupStride), "91 handles per group");
        // GameObjectClass::sig/class id read by the stock IsBuilding
        // (0x006A0810: `cmp dword [eax+0x1C], 2`); 2 is the building id.
        constexpr int kBuildingClassId = 2;
        constexpr int kMaxInstallAttempts = 40;

        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_ControlPanelVtableAddr = 0;
        uint32_t g_GetObjAddr = 0;
        FnGetObj g_FnGetObj = nullptr;

        bool g_ConfigRead = false;
        bool g_Enabled = false;
        bool g_Ready = false;
        std::atomic<bool> g_Active{ false };
        volatile long g_LogBudget = 32;

        void LogBudgeted(const wchar_t* fmt, ...)
        {
            if (InterlockedDecrement(&g_LogBudget) < 0)
                return;
            wchar_t buffer[384];
            va_list args;
            va_start(args, fmt);
            _vsnwprintf_s(buffer, _TRUNCATE, fmt, args);
            va_end(args);
            Log(L"%ls", buffer);
        }

        // ---- fault-safe engine access (no C++ objects, so __try is legal) ----

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

        bool ReadHandles(uintptr_t address, uint32_t* out, int count)
        {
            if (address < 0x10000 || count < 0)
                return false;
            __try
            {
                std::memcpy(out, reinterpret_cast<const void*>(address), static_cast<size_t>(count) * 4);
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

        bool SafeCanCommand(void* obj)
        {
            void* vtable = ReadPtr(reinterpret_cast<uintptr_t>(obj));
            void* fn = vtable ? ReadPtr(reinterpret_cast<uintptr_t>(vtable) + kCanCommandSlot * sizeof(void*)) : nullptr;
            if (!fn)
                return false;
            __try
            {
                return reinterpret_cast<FnCanCommand>(fn)(obj);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // GameObject +0xF8: the object's GameObjectClass (the producer build
        // list at class +0x608 is read through it in FUN_005ae660 lines
        // 51-53). Used only for the building check; matching uses the ODF.
        uintptr_t ClassOf(void* obj)
        {
            return obj ? reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj) + kGameObjectClassOffset))
                       : 0;
        }

        bool IsBuildingClass(uintptr_t cls)
        {
            int id = 0;
            return cls != 0 && ReadInt(cls + kObjectClassTypeOffset, id) && id == kBuildingClassId;
        }

        bool IsPersonObject(void* obj)
        {
            char name[128] = {};
            const char* rtti = TryGetRttiClassName(obj, name, sizeof(name));
            return rtti && std::strstr(rtti, "Person") != nullptr;
        }

        void* UserObject()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            return slot ? ReadPtr(slot) : nullptr;
        }

        bool IsPlayerTeam(void* obj)
        {
            void* const player = UserObject();
            int team = -1;
            int playerTeam = -2;
            return obj && player &&
                   ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                   ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                   team == playerTeam;
        }

        // The global really is the ControlPanel: its vtable is the
        // ControlPanel vtable row and that vtable's RTTI says so.
        bool ControlPanelIdentityOk()
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(g_ControlPanelAddr));
            return vtable != 0 && vtable == g_ControlPanelVtableAddr &&
                   VtableTypeNameMatches(vtable, ".?AVControlPanel@@");
        }

        bool AppendToGroup(int group, int storedCount, uint32_t handle)
        {
            const uintptr_t numAddr = g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(group);
            const uintptr_t slotAddr = g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(group) +
                                       4 * static_cast<size_t>(storedCount);
            __try
            {
                // Same thread as the group keys; re-check the count we planned on.
                if (*reinterpret_cast<volatile int*>(numAddr) != storedCount)
                    return false;
                *reinterpret_cast<volatile uint32_t*>(slotAddr) = handle;
                *reinterpret_cast<volatile int*>(numAddr) = storedCount + 1;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void MarkFailed()
        {
            MarkOptionHookFailed("AutoGroupNewUnits",
                                 "Unavailable: Auto Group did not hook on this game build (see openshim.log).");
        }

        // One attempt at binding the rows and the shared hook. False leaves
        // the feature unready; the caller retries a bounded number of times.
        bool TryInstall()
        {
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                return false;
            const HookEngine::EngineRow rows[] = {
                { "ControlPanelGlobal", &g_ControlPanelAddr },
                { "ControlPanelVtable", &g_ControlPanelVtableAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
            };
            if (!HookEngine::BindEngineRows("Auto-group new units", rows))
                return false;
            if (g_GameObjectGetHandleAddr == 0)
            {
                LogBudgeted(L"[AUTOGROUP] GameObject::GetHandle unresolved; not installed\n");
                return false;
            }
            if (!ControlPanelIdentityOk())
            {
                LogBudgeted(L"[AUTOGROUP] ControlPanel identity check failed (global=0x%08X vtable row=0x%08X)\n",
                            g_ControlPanelAddr, g_ControlPanelVtableAddr);
                return false;
            }
            g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
            if (!EnsureProducerFinishBuildHook())
            {
                LogBudgeted(L"[AUTOGROUP] FinishBuild hook not installed\n");
                return false;
            }
            return true;
        }
    }

    void AutoGroupOnUnitBuilt(void* producer, void* built)
    {
        if (!g_Active.load(std::memory_order_acquire))
            return;

        Policy::BuiltUnit unit;
        unit.present = built != nullptr;
        uint32_t handle = 0;
        char unitOdf[Policy::kOdfBufferSize] = {};
        if (unit.present)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(built)));
            const uintptr_t cls = ClassOf(built);
            unit.playerTeam = IsPlayerTeam(built);
            unit.isScavenger = VtableTypeNameMatches(vtable, ".?AVScavenger@@");
            unit.isConstructor = VtableTypeNameMatches(vtable, ".?AVConstructionRig@@");
            unit.isPerson = IsPersonObject(built);
            unit.isBuilding = IsBuildingClass(cls);
            unit.canCommand = SafeCanCommand(built);
            handle = SafeGetHandle(built);
            unit.handleValid = handle != 0 && SafeGetObj(handle) == built;
            unit.odfKnown = TryGetCraftOdfName(built, unitOdf, sizeof(unitOdf));
        }
        const Policy::BuiltUnitVerdict verdict = Policy::ClassifyBuiltUnit(unit);
        if (verdict != Policy::BuiltUnitVerdict::Group)
        {
            // Other teams' builds are routine (AI producers); not worth a line.
            if (verdict != Policy::BuiltUnitVerdict::OtherTeam)
                LogBudgeted(L"[AUTOGROUP] producer 0x%08X built 0x%08X: %hs; not grouped\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producer)),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(built)),
                            Policy::DescribeVerdict(verdict));
            return;
        }

        Policy::GroupSummary groups[Policy::kGroupCount];
        for (int g = 0; g < Policy::kGroupCount; ++g)
        {
            int stored = 0;
            uint32_t handles[Policy::kGroupCapacity] = {};
            if (!ReadInt(g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(g), stored))
                return;
            if (stored < 0)
                stored = 0;
            if (stored > Policy::kGroupCapacity)
                stored = Policy::kGroupCapacity;
            if (!ReadHandles(g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(g), handles,
                             stored))
                return;
            groups[g] = Policy::SummarizeGroup(handles, stored, handle, unitOdf,
                                               [](uint32_t h, char* out, size_t outSize) {
                                                   void* member = SafeGetObj(h);
                                                   if (!member)
                                                       return false;
                                                   // Unreadable leaves `out` empty: never a match.
                                                   TryGetCraftOdfName(member, out, outSize);
                                                   return true;
                                               });
        }

        const Policy::GroupChoice choice = Policy::ChooseGroup(groups);
        bool added = false;
        if (choice.kind == Policy::ChoiceKind::Match || choice.kind == Policy::ChoiceKind::Empty)
            added = AppendToGroup(choice.group, groups[choice.group].storedCount, handle);
        const char* what = choice.kind == Policy::ChoiceKind::Match ? "joined"
                         : choice.kind == Policy::ChoiceKind::Empty ? "started"
                         : choice.kind == Policy::ChoiceKind::AlreadyGrouped ? "already in a group"
                                                                              : "no free group";
        // Index n is group_select_n in the stock input.map (F1 for 0).
        LogBudgeted(L"[AUTOGROUP] unit 0x%08X handle=0x%08X odf=%hs %hs group index %d%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(built)), handle, unitOdf, what, choice.group,
                    (choice.group >= 0 && !added) ? " (write failed)" : "");
    }

    void ReloadAutoGroupNewUnitsConfig()
    {
        bool value = false;
        g_Enabled = TryGetUserConfigBool("Gameplay", "AutoGroupNewUnits", value) ? value : false;
        if (!g_ConfigRead)
            Log(L"[AUTOGROUP] Baseline enabled=%hs (SP-only)\n", g_Enabled ? "yes" : "no");
        g_ConfigRead = true;
        RefreshAutoGroupNewUnitsState();
    }

    // Installed regardless of the ini value, so the Options row can turn the
    // feature on live; while it is off the consumer returns at once. Retried
    // until it binds or kMaxInstallAttempts passes have failed (on Steam a
    // row can be a page SteamStub has not finished with).
    void InstallAutoGroupNewUnitsIfPossible()
    {
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (!g_ConfigRead)
            ReloadAutoGroupNewUnitsConfig();
        ++s_attempts;
        if (TryInstall())
        {
            s_done = true;
            g_Ready = true;
            ClearOptionHookFailed("AutoGroupNewUnits");
            Log(L"[AUTOGROUP] installed (ControlPanel 0x%08X, attempt %d)\n", g_ControlPanelAddr, s_attempts);
            RefreshAutoGroupNewUnitsState();
            return;
        }
        g_ControlPanelAddr = 0;
        g_FnGetObj = nullptr;
        MarkFailed();
        if (s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[AUTOGROUP] gave up after %d attempts; feature unavailable\n", s_attempts);
        }
    }

    void RefreshAutoGroupNewUnitsState()
    {
        const bool want = g_Enabled && g_Ready && IsSinglePlayerSession();
        if (want != g_Active.load(std::memory_order_acquire))
        {
            g_Active.store(want, std::memory_order_release);
            Log(L"[AUTOGROUP] %hs\n", want ? "Active (SP-only)" : "Stood down");
        }
    }

    // Mission end/load. Nothing of ours to drop: the groups are the engine's.
    void ResetAutoGroupNewUnits()
    {
        g_LogBudget = 32;
        RefreshAutoGroupNewUnitsState();
    }
}
