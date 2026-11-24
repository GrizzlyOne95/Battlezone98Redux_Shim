// auto_group_new_units.cpp
// BZR Open Shim - auto-group newly built units. [Gameplay] AutoGroupNewUnits,
// default OFF, single player only. When the player's Recycler or Factory
// finishes an Offense, Defense or Utility unit (the stock command-interface
// category its class's team-slot range falls in), it is added to an F1-F7
// group (ported from BZCC's
// SetBestGroup): the first keyed group (0-6, the ones input.map binds) whose
// live members all have the same ODF and number fewer than 10, else the first
// empty keyed group, else none. [Gameplay] ExtendedUnitCap (offense_overflow.cpp)
// turns this on too and asks AutoGroupCanPlace before it opens a build. The entry is appended to the stock ControlPanel group directly, so
// the group keys select it and the stock mission save keeps it. While one of
// those three category lists is open, the sort key (Y, seen by the rally
// window subclass) groups every ungrouped unit in it by the same rule.
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
        using FnGetClass = void*(__thiscall*)(void* sub);
        using FnGetTeam = void*(__cdecl*)();

        constexpr size_t kCanCommandSlot = 14;
        // ControlPanel groups (FUN_004a6f00 BindGroup lines 6-10).
        constexpr size_t kGroupNumOffset = 0xFC4;
        constexpr size_t kGroupListOffset = 0x18C;
        constexpr size_t kGroupStride = 0x16C;
        // ControlPanel currentItem (the open MENU_ITEM, -1 none) and
        // selectNum (FUN_004a6a50 line 21, FUN_004a08e0 lines 503-540).
        constexpr size_t kCurrentItemOffset = 0x117C;
        constexpr size_t kSelectNumOffset = 0x188;
        // GameObjectClass team-slot range (FUN_004db650 lines 14-23; -1 from
        // the class constructor FUN_004c12f0 lines 53-54).
        constexpr size_t kClassMinSlotOffset = 0x13C;
        constexpr size_t kClassMaxSlotOffset = 0x140;
        // MENU_ITEM {const char* name; int minSlot; int maxSlot;} (0x008E7990).
        constexpr size_t kMenuItemStride = 0xC;
        // Team slots are Team +0 (TeamGetSlot 0x005E0F70); MENU_ITEM ends at 44.
        constexpr int kTeamSlotCount = 45;
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
        uint32_t g_GetTeamAddr = 0;
        uint32_t g_TeamGetSlotAddr = 0;
        uint32_t g_MenuItemsAddr = 0;
        FnGetObj g_FnGetObj = nullptr;
        FnGetTeam g_FnGetTeam = nullptr;

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

        // GameObjectClass through the class sub-object's vtable[0] (GameObject
        // +0x18), the path TryGetCraftOdfName and the stock TeamHasFreeSlot
        // (FUN_00464140 lines 15-18, which reads +0x13C from it) use.
        uintptr_t SafeGetClass(void* obj)
        {
            if (!obj)
                return 0;
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

        void* SafeUserTeam()
        {
            if (!g_FnGetTeam)
                return nullptr;
            __try
            {
                return g_FnGetTeam();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
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

        // Writes `handle` at `writeIndex` and sets the count to writeIndex + 1.
        // writeIndex is storedCount to append, or 0 to rewrite an empty group
        // (dropping its dead entries, as stock BindGroup FUN_004a6f00 does).
        bool AppendToGroup(int group, int storedCount, int writeIndex, uint32_t handle)
        {
            const uintptr_t numAddr = g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(group);
            const uintptr_t slotAddr = g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(group) +
                                       4 * static_cast<size_t>(writeIndex);
            __try
            {
                // Same thread as the group keys; re-check the count we planned on.
                if (*reinterpret_cast<volatile int*>(numAddr) != storedCount)
                    return false;
                *reinterpret_cast<volatile uint32_t*>(slotAddr) = handle;
                *reinterpret_cast<volatile int*>(numAddr) = writeIndex + 1;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Every stored group against a unit (handle 0: membership not asked).
        bool SummarizeGroups(uint32_t handle, const char* unitOdf, Policy::GroupSummary (&groups)[Policy::kGroupCount])
        {
            for (int g = 0; g < Policy::kGroupCount; ++g)
            {
                int stored = 0;
                uint32_t handles[Policy::kGroupCapacity] = {};
                if (!ReadInt(g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(g), stored))
                    return false;
                if (stored < 0)
                    stored = 0;
                if (stored > Policy::kGroupCapacity)
                    stored = Policy::kGroupCapacity;
                if (!ReadHandles(g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(g), handles,
                                 stored))
                    return false;
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
            return true;
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
                { "HudFadeGetTeam", &g_GetTeamAddr },
                // Guards: team slots at Team +0, MENU_ITEM ranges 5-14/15-24/25-34.
                { "TeamGetSlot", &g_TeamGetSlotAddr },
                { "ControlPanelMenuItems", &g_MenuItemsAddr },
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
            g_FnGetTeam = reinterpret_cast<FnGetTeam>(g_GetTeamAddr);
            if (!EnsureProducerFinishBuildHook())
            {
                LogBudgeted(L"[AUTOGROUP] FinishBuild hook not installed\n");
                return false;
            }
            return true;
        }
        struct UnitRead
        {
            Policy::BuiltUnit unit;
            uint32_t handle = 0;
            int minSlot = -1;
            int maxSlot = -1;
            char odf[Policy::kOdfBufferSize] = {};
        };

        // Everything ClassifyBuiltUnit needs, read fault-safe from `obj`.
        void ReadUnit(void* obj, UnitRead& out)
        {
            out.unit.present = obj != nullptr;
            if (!obj)
                return;
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            out.unit.playerTeam = IsPlayerTeam(obj);
            out.unit.isCraft = VtableDerivesFrom(vtable, ".?AVCraft@@");
            out.unit.isScavenger = VtableTypeNameMatches(vtable, ".?AVScavenger@@");
            out.unit.isConstructor = VtableTypeNameMatches(vtable, ".?AVConstructionRig@@");
            out.unit.isPerson = IsPersonObject(obj);
            out.unit.isBuilding = IsBuildingClass(ClassOf(obj));
            const uintptr_t cls = SafeGetClass(obj);
            if (cls == 0 || !ReadInt(cls + kClassMinSlotOffset, out.minSlot) ||
                !ReadInt(cls + kClassMaxSlotOffset, out.maxSlot))
                out.minSlot = out.maxSlot = -1;
            out.unit.category = Policy::CommandCategory(out.minSlot, out.maxSlot);
            out.unit.canCommand = SafeCanCommand(obj);
            out.handle = SafeGetHandle(obj);
            out.unit.handleValid = out.handle != 0 && SafeGetObj(out.handle) == obj;
            out.unit.odfKnown = TryGetCraftOdfName(obj, out.odf, sizeof(out.odf));
        }

        // Places one eligible unit by the SetBestGroup rule.
        Policy::GroupChoice PlaceUnit(const UnitRead& u, bool& added)
        {
            added = false;
            Policy::GroupSummary groups[Policy::kGroupCount];
            if (!SummarizeGroups(u.handle, u.odf, groups))
                return Policy::GroupChoice{};
            const Policy::GroupChoice choice = Policy::ChooseGroup(groups);
            if (choice.kind == Policy::ChoiceKind::Match || choice.kind == Policy::ChoiceKind::Empty)
                added = AppendToGroup(choice.group, groups[choice.group].storedCount,
                                      choice.kind == Policy::ChoiceKind::Empty ? 0 : groups[choice.group].storedCount,
                                      u.handle);
            return choice;
        }

        const char* DescribeChoice(Policy::ChoiceKind kind)
        {
            return kind == Policy::ChoiceKind::Match ? "joined"
                 : kind == Policy::ChoiceKind::Empty ? "started"
                 : kind == Policy::ChoiceKind::AlreadyGrouped ? "already in a group"
                                                              : "no free group";
        }

        // The open category list's item (0-2), or -1 when the sort key does
        // not apply right now.
        int SortableMenuItem()
        {
            if (!g_Active.load(std::memory_order_acquire) || g_ControlPanelAddr == 0 || !ControlPanelIdentityOk())
                return -1;
            int currentItem = -1;
            int selectNum = 0;
            if (!ReadInt(g_ControlPanelAddr + kCurrentItemOffset, currentItem) ||
                !ReadInt(g_ControlPanelAddr + kSelectNumOffset, selectNum))
                return -1;
            return Policy::SortKeyApplies(true, currentItem, selectNum, OffenseOverflowMemberGroup()) ? currentItem
                                                                                                       : -1;
        }

        // Every unit in menu item `item`'s team slots, the ones the stock list
        // shows (SelectType FUN_004a6a50 lines 10-21 walks the same MENU_ITEM
        // range), placed unless it is already grouped.
        void SortCategory(int item)
        {
            void* const team = SafeUserTeam();
            int minSlot = -1;
            int maxSlot = -1;
            const uintptr_t entry = g_MenuItemsAddr + kMenuItemStride * static_cast<size_t>(item);
            if (!team || g_MenuItemsAddr == 0 || !ReadInt(entry + 4, minSlot) || !ReadInt(entry + 8, maxSlot) ||
                minSlot != Policy::kCategoryMinSlot[item] || maxSlot != Policy::kCategoryMaxSlot[item] ||
                maxSlot >= kTeamSlotCount)
            {
                LogBudgeted(L"[AUTOGROUP] sort %hs: team or menu range unreadable; nothing done\n",
                            Policy::CategoryName(item));
                return;
            }
            int grouped = 0, already = 0, skipped = 0, noGroup = 0;
            void* const* const slots = reinterpret_cast<void* const*>(team);
            for (int slot = minSlot; slot <= maxSlot; ++slot)
            {
                void* const obj = ReadPtr(reinterpret_cast<uintptr_t>(slots + slot));
                if (!obj)
                    continue;
                UnitRead u;
                ReadUnit(obj, u);
                const Policy::BuiltUnitVerdict verdict = Policy::ClassifyBuiltUnit(u.unit);
                if (verdict != Policy::BuiltUnitVerdict::Group)
                {
                    ++skipped;
                    Log(L"[AUTOGROUP] sort %hs: slot %d 0x%08X odf=%hs %hs; left alone\n",
                                Policy::CategoryName(item), slot,
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(obj)), u.odf,
                                Policy::DescribeVerdict(verdict));
                    continue;
                }
                bool added = false;
                const Policy::GroupChoice choice = PlaceUnit(u, added);
                if (choice.kind == Policy::ChoiceKind::AlreadyGrouped)
                    ++already;
                else if (added)
                {
                    ++grouped;
                    Log(L"[AUTOGROUP] sort %hs: slot %d handle=0x%08X odf=%hs %hs group index %d\n",
                                Policy::CategoryName(item), slot, u.handle, u.odf, DescribeChoice(choice.kind),
                                choice.group);
                }
                else
                    ++noGroup;
            }
            // Not budgeted: a press is the player's own, at most 11 lines,
            // and must not use up the FinishBuild lines' budget.
            Log(L"[AUTOGROUP] sort %hs: grouped %d, already grouped %d, skipped %d, no group %d\n",
                        Policy::CategoryName(item), grouped, already, skipped, noGroup);
        }
    }

    void AutoGroupOnUnitBuilt(void* producer, void* built)
    {
        if (!g_Active.load(std::memory_order_acquire))
            return;

        UnitRead u;
        ReadUnit(built, u);
        const Policy::BuiltUnitVerdict verdict = Policy::ClassifyBuiltUnit(u.unit);
        if (verdict != Policy::BuiltUnitVerdict::Group)
        {
            // Other teams' builds are routine (AI producers); not worth a line.
            if (verdict != Policy::BuiltUnitVerdict::OtherTeam)
                LogBudgeted(L"[AUTOGROUP] producer 0x%08X built 0x%08X odf=%hs class slots %d-%d: %hs; not grouped\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producer)),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(built)), u.odf, u.minSlot, u.maxSlot,
                            Policy::DescribeVerdict(verdict));
            return;
        }

        bool added = false;
        const Policy::GroupChoice choice = PlaceUnit(u, added);
        // Index n is group_select_n in the stock input.map (F1 for 0).
        LogBudgeted(L"[AUTOGROUP] unit 0x%08X handle=0x%08X odf=%hs (%hs) %hs group index %d%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(built)), u.handle, u.odf,
                    Policy::CategoryName(u.unit.category), DescribeChoice(choice.kind), choice.group,
                    (choice.group >= 0 && !added) ? " (write failed)" : "");
    }

    bool AutoGroupSortKeyApplies()
    {
        return SortableMenuItem() >= 0;
    }

    bool AutoGroupSortOpenCategory()
    {
        const int item = SortableMenuItem();
        if (item < 0)
            return false;
        SortCategory(item);
        return true;
    }

    // ExtendedUnitCap is only available once auto-group has hooked.
    bool AutoGroupNewUnitsReady()
    {
        return g_Ready;
    }

    // Asked by the ExtendedUnitCap build gate (offense_overflow.cpp) for a
    // full offense range: would a new `odf` unit get a group?
    bool AutoGroupCanPlace(const char* odf)
    {
        if (!g_Ready || !odf || odf[0] == '\0')
            return false;
        Policy::GroupSummary groups[Policy::kGroupCount];
        return SummarizeGroups(0, odf, groups) && Policy::CanPlace(groups);
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
        g_FnGetTeam = nullptr;
        MarkFailed();
        if (s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[AUTOGROUP] gave up after %d attempts; feature unavailable\n", s_attempts);
        }
    }

    void RefreshAutoGroupNewUnitsState()
    {
        // ExtendedUnitCap needs the grouping, so it switches this on as well.
        const bool want = (g_Enabled || OffenseOverflowExtendsAutoGroup()) && g_Ready && IsSinglePlayerSession();
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
