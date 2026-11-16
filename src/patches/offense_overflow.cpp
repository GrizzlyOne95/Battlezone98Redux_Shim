// offense_overflow.cpp
// BZR Open Shim - more than 10 offensive units, kept in F1-F7 groups (the
// BZCC model), and a member list for each group. Single player only.
//
//   [Gameplay] ExtendedUnitCap (default OFF)
//     * Build gate: Producer::UpdateModeList enables a build entry only when
//       FirstEmptySlot finds a team slot. With the offense slots (5-14) full,
//       the redirected call answers "free" for the user's team when
//       auto-group has a keyed group for the class's ODF; the new unit joins
//       it (AutoGroupOnUnitBuilt runs whenever this is on). A slotless unit
//       is expected to take a freed slot later (UNVERIFIED; see the doc).
//     * TeamHasFreeSlot: a grouped craft of the user's team counts as
//       slotted at both call sites.
//   [Gameplay] GroupMemberMenu (default ON)
//     * Pressing an F-key while its group is exactly the selection opens the
//       group's member list: the stock unit list (keys 1-0) over the first
//       ten live members, swapped into team slots 5-14 for the ControlPanel
//       render only and put back after it (contextual_hud's render scope).
//     * Ctrl+category labels read "All Offense" etc. while nothing is
//       selected.
//     * With ExtendedUnitCap also on, Ctrl+Offense selects the grouped
//       offense craft that hold no team slot as well.
// Rules: include/offense_overflow_policy.h. Evidence and limits:
// Docs/PRODUCER_RALLY_POINTS.md ("Extended unit cap", "Group member list").
// Every address is a scripts/patches.json row; each part binds its own rows
// and stays stock (option marked unavailable) when they do not match.
#include "auto_group_policy.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "contextual_hud.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "offense_overflow_policy.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <string>

using BZROpenShim::L10n::ShimFormat;

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace Policy = OffenseOverflowPolicy;

        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnCanCommand = bool(__thiscall*)(void* obj);
        using FnGetClass = void*(__thiscall*)(void* sub);
        using FnGetTeam = void*(__cdecl*)();
        using FnFirstEmptySlot = int(__thiscall*)(void* team, int minSlot, int maxSlot);
        using FnTeamHasFreeSlot = bool(__cdecl*)(void* team, void* obj);
        using FnSelectType = void(__thiscall*)(void* panel, int item);
        using FnSelectNone = void(__thiscall*)(void* panel);
        using FnSetSelected = void(__thiscall*)(void* obj, bool on);
        using FnLocalize = const char*(__cdecl*)(const char* section, const char* key);

        // ControlPanel fields (FUN_004a6a50 lines 19-21, FUN_004a6d50,
        // FUN_004a08e0 lines 503-540; ControlPanelGlobal row).
        constexpr size_t kSelectListOffset = 0x1C;
        constexpr size_t kSelectNumOffset = 0x188;
        constexpr size_t kGroupListOffset = 0x18C;
        constexpr size_t kGroupStride = 0x16C;
        constexpr size_t kGroupNumOffset = 0xFC4;
        constexpr size_t kCurrentItemOffset = 0x117C;
        constexpr size_t kItemSelectedOffset = 0x1188;
        constexpr int kGroupCount = 10;
        constexpr int kGroupCapacity = 0x16C / 4;
        static_assert(kGroupCapacity == Policy::kSelectCapacity, "selectList and a group hold 91 handles");
        // HudFadeCommandInputs +0x20: group_select_0..9 (0x00919890).
        constexpr size_t kGroupSelectInputOffset = 0x20;
        constexpr size_t kCanCommandSlot = 14;
        // GameObjectClass +0x13C: the class's first team slot (FUN_005ae660
        // line 69, FUN_00464140 line 18).
        constexpr size_t kClassMinSlotOffset = 0x13C;
        // GameObjectClass +0x30: the ODF name, char[8] (TryGetCraftOdfName).
        constexpr size_t kClassOdfOffset = 0x30;
        constexpr size_t kClassOdfChars = kGameObjectClassOdfNameMax;
        static_assert(kClassOdfChars < AutoGroupPolicy::kOdfBufferSize, "ODF name fits the auto-group buffer");
        // Call-site rows: the E8 is this far into each row.
        constexpr uint32_t kGateCallOffset = 0x76;
        constexpr uint32_t kFreeSlotCall1Offset = 0xD;
        constexpr uint32_t kFreeSlotCall2Offset = 0xE;
        constexpr uint32_t kSelectTypeCallOffset = 0xD;
        constexpr uint32_t kLabelCallOffset = 0x13;
        constexpr int kMaxInstallAttempts = 40;

        // Shared rows.
        uint32_t g_ControlPanelAddr = 0;
        uint32_t g_ControlPanelVtableAddr = 0;
        uint32_t g_GetObjAddr = 0;
        uint32_t g_GetTeamAddr = 0;
        uint32_t g_TeamGetSlotAddr = 0;
        uint32_t g_MenuItemsAddr = 0;
        // ExtendedUnitCap.
        uint32_t g_GateRowAddr = 0;
        uint32_t g_FirstEmptySlotAddr = 0;
        uint32_t g_HasFreeSlotAddr = 0;
        uint32_t g_HasFreeSlotRow1Addr = 0;
        uint32_t g_HasFreeSlotRow2Addr = 0;
        // GroupMemberMenu.
        uint32_t g_RenderAddr = 0;
        uint32_t g_InputsAddr = 0;
        uint32_t g_CmdMultiAddr = 0;
        uint32_t g_GroupKeyLoopAddr = 0;
        uint32_t g_SelectNoneAddr = 0;
        uint32_t g_SelectTypeAddr = 0;
        uint32_t g_SelectTypeRowAddr = 0;
        uint32_t g_SetSelectedAddr = 0;
        uint32_t g_LabelRowAddr = 0;
        uint32_t g_LocalizeAddr = 0;

        FnGetObj g_FnGetObj = nullptr;
        FnGetTeam g_FnGetTeam = nullptr;
        FnFirstEmptySlot g_FnFirstEmptySlot = nullptr;
        FnTeamHasFreeSlot g_FnTeamHasFreeSlot = nullptr;
        FnSelectType g_FnSelectType = nullptr;
        FnSelectNone g_FnSelectNone = nullptr;
        FnSetSelected g_FnSetSelected = nullptr;
        FnLocalize g_FnLocalize = nullptr;

        bool g_ConfigRead = false;
        bool g_ExtendedEnabled = false;
        bool g_MemberEnabled = true;
        // Part readiness (patch thread, then read-only).
        bool g_SharedReady = false;
        bool g_GateReady = false;
        bool g_FreeSlotReady = false;
        bool g_MemberReady = false;
        bool g_SelectAllReady = false;
        bool g_LabelReady = false;
        std::atomic<bool> g_ScopePending{ false };
        std::atomic<bool> g_ScopeFailed{ false };

        std::atomic<bool> g_ExtendedActive{ false };
        std::atomic<bool> g_MemberActive{ false };
        std::atomic<bool> g_SelectAllActive{ false };
        std::atomic<bool> g_LabelActive{ false };
        std::atomic<int> g_MemberGroup{ -1 };
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

        bool WriteBytes(uintptr_t address, const void* data, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(reinterpret_cast<void*>(address), data, size);
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

        // GameObjectClass through the class sub-object's vtable[0]
        // (GameObject +0x18), the path TryGetCraftOdfName and the stock
        // TeamHasFreeSlot (FUN_00464140 lines 15-17) use.
        uintptr_t SafeGetClass(void* obj)
        {
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

        bool SafeSelectNone(void* panel)
        {
            if (!g_FnSelectNone)
                return false;
            __try
            {
                g_FnSelectNone(panel);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetSelected(void* obj)
        {
            if (!g_FnSetSelected)
                return false;
            __try
            {
                g_FnSetSelected(obj, true);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsPlayerTeam(void* obj)
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            void* const player = slot ? ReadPtr(slot) : nullptr;
            int team = -1;
            int playerTeam = -2;
            return obj && player &&
                   ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                   ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                   team == playerTeam;
        }

        bool IsCraft(void* obj)
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(reinterpret_cast<uintptr_t>(obj)));
            return vtable != 0 && VtableDerivesFrom(vtable, ".?AVCraft@@");
        }

        bool ControlPanelIdentityOk()
        {
            const uintptr_t vtable = reinterpret_cast<uintptr_t>(ReadPtr(g_ControlPanelAddr));
            return vtable != 0 && vtable == g_ControlPanelVtableAddr &&
                   VtableTypeNameMatches(vtable, ".?AVControlPanel@@");
        }

        // One stored group's handles; returns the count (0 on a failed read).
        int ReadGroup(int group, uint32_t (&handles)[kGroupCapacity])
        {
            int stored = 0;
            if (!ReadInt(g_ControlPanelAddr + kGroupNumOffset + 4 * static_cast<size_t>(group), stored) || stored <= 0)
                return 0;
            if (stored > kGroupCapacity)
                stored = kGroupCapacity;
            if (!ReadBytes(g_ControlPanelAddr + kGroupListOffset + kGroupStride * static_cast<size_t>(group), handles,
                           static_cast<size_t>(stored) * 4))
                return 0;
            return stored;
        }

        bool HandleInAnyGroup(uint32_t handle)
        {
            for (int g = 0; g < kGroupCount; ++g)
            {
                uint32_t handles[kGroupCapacity];
                const int n = ReadGroup(g, handles);
                for (int i = 0; i < n; ++i)
                    if (handles[i] == handle)
                        return true;
            }
            return false;
        }

        // The members stock SelectGroup would select (FUN_004a6dd0 lines
        // 14-24: live and commandable), limited to the player's team.
        // Fills handles and objects; returns the count.
        int GroupMembers(int group, uint32_t (&handles)[kGroupCapacity], void* (&objects)[kGroupCapacity])
        {
            uint32_t stored[kGroupCapacity];
            const int n = ReadGroup(group, stored);
            int live = 0;
            for (int i = 0; i < n; ++i)
            {
                void* const obj = SafeGetObj(stored[i]);
                if (!obj || !IsPlayerTeam(obj) || !SafeCanCommand(obj))
                    continue;
                handles[live] = stored[i];
                objects[live] = obj;
                ++live;
            }
            return live;
        }

        int ReadSelection(void* panel, uint32_t (&handles)[Policy::kSelectCapacity])
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(panel);
            int n = 0;
            if (!ReadInt(base + kSelectNumOffset, n) || n <= 0)
                return 0;
            if (n > Policy::kSelectCapacity)
                n = Policy::kSelectCapacity;
            return ReadBytes(base + kSelectListOffset, handles, static_cast<size_t>(n) * 4) ? n : 0;
        }

        // ---- part 1: the build gate ----------------------------------------

        bool ReadClassOdf(void* cls, char (&out)[AutoGroupPolicy::kOdfBufferSize])
        {
            out[0] = '\0';
            char raw[kClassOdfChars] = {};
            if (!cls || !ReadBytes(reinterpret_cast<uintptr_t>(cls) + kClassOdfOffset, raw, sizeof(raw)))
                return false;
            size_t i = 0;
            for (; i < kClassOdfChars && raw[i] != '\0'; ++i)
                out[i] = raw[i];
            out[i] = '\0';
            return out[0] != '\0';
        }

        int __cdecl BuildGateDecide(void* team, int minSlot, int maxSlot, void* cls)
        {
            const int stock = g_FnFirstEmptySlot(team, minSlot, maxSlot);
            if (stock != -1 || !g_ExtendedActive.load(std::memory_order_acquire) ||
                minSlot != Policy::kOffenseMinSlot || maxSlot != Policy::kOffenseMaxSlot)
                return stock;
            void* const userTeamPtr = SafeUserTeam();
            const bool userTeam = team != nullptr && team == userTeamPtr;
            char odf[AutoGroupPolicy::kOdfBufferSize] = {};
            const bool odfRead = userTeam && ReadClassOdf(cls, odf);
            const bool canPlace = odfRead && AutoGroupCanPlace(odf);
            const bool opens = Policy::BuildGateOpens(stock, minSlot, maxSlot, true, userTeam, canPlace);
            // One line per change of outcome (UpdateModeList runs every
            // frame), so a refused gate says which check refused it.
            static int s_lastOutcome = -1;
            const int outcome = (userTeam ? 1 : 0) | (odfRead ? 2 : 0) | (canPlace ? 4 : 0);
            if (outcome != s_lastOutcome)
            {
                s_lastOutcome = outcome;
                LogBudgeted(L"[OVERFLOW] build gate %ls: userTeam=%d (team %p, user %p) odf='%hs' canPlace=%d\n",
                            opens ? L"open" : L"refused", userTeam ? 1 : 0, team, userTeamPtr, odf,
                            canPlace ? 1 : 0);
            }
            if (!opens)
                return stock;
            return minSlot; // the caller only compares with -1
        }

#if defined(_M_IX86)
        // Entered in place of `call TeamFirstEmptySlot` at 0x005AE982
        // (thiscall: ecx = team, [esp+4] min, [esp+8] max, ret 8); ebp is
        // still Producer::UpdateModeList's frame, where the build entry's
        // class is [[ebp-0x10] + [ebp-0xC]*4] (ProducerModeListFirstEmptySlotCall).
        __declspec(naked) void BuildGateThunk()
        {
            __asm
            {
                mov eax, dword ptr [ebp - 0x10]
                mov edx, dword ptr [ebp - 0x0C]
                mov eax, dword ptr [eax + edx * 4]
                push eax
                push dword ptr [esp + 0x0C]
                push dword ptr [esp + 0x0C]
                push ecx
                call BuildGateDecide
                add esp, 0x10
                ret 8
            }
        }
#endif

        // ---- part 3: TeamHasFreeSlot ---------------------------------------

        bool __cdecl TeamHasFreeSlotHook(void* team, void* obj)
        {
            const bool stock = g_FnTeamHasFreeSlot(team, obj);
            if (stock || !g_ExtendedActive.load(std::memory_order_acquire))
                return stock;
            const bool userTeam = team != nullptr && team == SafeUserTeam();
            const bool craft = userTeam && obj && IsPlayerTeam(obj) && IsCraft(obj);
            const uint32_t handle = craft ? SafeGetHandle(obj) : 0;
            const bool grouped = handle != 0 && HandleInAnyGroup(handle);
            return Policy::TeamHasFreeSlotOverride(stock, true, userTeam, craft, grouped);
        }

        // ---- part 4: the member list ---------------------------------------

        struct Injection
        {
            bool active = false;
            void** slots = nullptr; // &team[kOffenseMinSlot]
            void* saved[Policy::kOffenseSlotCount] = {};
            void* injected[Policy::kOffenseSlotCount] = {};
        };
        Injection g_Injection; // frame thread only

        bool InjectSlots(void** slots, void* (&savedOut)[Policy::kOffenseSlotCount],
                         void* const (&injected)[Policy::kOffenseSlotCount])
        {
            __try
            {
                for (int i = 0; i < Policy::kOffenseSlotCount; ++i)
                    savedOut[i] = slots[i];
                for (int i = 0; i < Policy::kOffenseSlotCount; ++i)
                    slots[i] = injected[i];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        int RestoreInjected(void** slots, void* const (&saved)[Policy::kOffenseSlotCount],
                            void* const (&injected)[Policy::kOffenseSlotCount])
        {
            __try
            {
                return Policy::RestoreSlots(slots, saved, injected);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // The ControlPanel render's pre-call (frame thread).
        bool MemberBeforeRender(void* panel)
        {
            g_Injection.active = false;
            const int open = g_MemberGroup.load(std::memory_order_acquire);
            const bool active = g_MemberActive.load(std::memory_order_acquire);
            if ((!active && open < 0) || reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return false;

            const uintptr_t base = reinterpret_cast<uintptr_t>(panel);
            Policy::MemberFrameInput in;
            in.active = active;
            in.memberGroup = open;
            uint8_t keys[kGroupCount] = {};
            uint8_t multi = 0;
            if (!ReadInt(base + kCurrentItemOffset, in.currentItem) || !ReadInt(base + kSelectNumOffset, in.selectNum) ||
                !ReadBytes(g_InputsAddr + kGroupSelectInputOffset, keys, sizeof(keys)) ||
                !ReadBytes(g_CmdMultiAddr, &multi, 1))
            {
                in.active = false;
            }
            in.cmdMulti = multi != 0;
            // The first set byte, as the stock loop takes it (line 529).
            for (int g = 0; g < kGroupCount && in.pressedGroup < 0; ++g)
                if (keys[g] != 0)
                    in.pressedGroup = g;

            uint32_t handles[kGroupCapacity];
            void* objects[kGroupCapacity];
            int members = 0;
            if (in.active && in.pressedGroup >= 0 && in.pressedGroup < Policy::kKeyedGroupCount && !in.cmdMulti &&
                in.selectNum > 0)
            {
                members = GroupMembers(in.pressedGroup, handles, objects);
                uint32_t selection[Policy::kSelectCapacity];
                const int selected = ReadSelection(panel, selection);
                in.selectionIsGroup = Policy::SameHandleSet(selection, selected, handles, members);
            }
            if (open >= 0 && open < Policy::kKeyedGroupCount && !in.selectionIsGroup)
            {
                members = GroupMembers(open, handles, objects);
                in.memberLiveCount = members;
            }

            const Policy::MemberFrame frame = Policy::DecideMemberFrame(in);
            switch (frame.action)
            {
            case Policy::MemberAction::None:
                return false;
            case Policy::MemberAction::Exit:
                g_MemberGroup.store(-1, std::memory_order_release);
                return false;
            case Policy::MemberAction::Enter:
            {
                // Consume the press so the stock loop does not reselect the
                // group, then put the panel on item 0 with nothing selected.
                const uint8_t zero = 0;
                const int item = Policy::kOffenseItem;
                const int bit = 1 << Policy::kOffenseItem;
                if (!WriteBytes(g_InputsAddr + kGroupSelectInputOffset + static_cast<size_t>(frame.group), &zero, 1) ||
                    !SafeSelectNone(panel) || !WriteBytes(base + kCurrentItemOffset, &item, sizeof(item)) ||
                    !WriteBytes(base + kItemSelectedOffset, &bit, sizeof(bit)))
                {
                    g_MemberGroup.store(-1, std::memory_order_release);
                    return false;
                }
                g_MemberGroup.store(frame.group, std::memory_order_release);
                LogBudgeted(L"[OVERFLOW] member list for group index %d (%d live)\n", frame.group, members);
                break;
            }
            case Policy::MemberAction::Show:
                break;
            }

            void* const team = SafeUserTeam();
            if (!team)
                return false;
            void* injected[Policy::kOffenseSlotCount];
            Policy::FillMemberSlots(objects, members, injected);
            void** const slots = reinterpret_cast<void**>(team) + Policy::kOffenseMinSlot;
            if (!InjectSlots(slots, g_Injection.saved, injected))
                return false;
            std::memcpy(g_Injection.injected, injected, sizeof(injected));
            g_Injection.slots = slots;
            g_Injection.active = true;
            return true;
        }

        // The ControlPanel render's after-call: always runs once the pre-call
        // changed the slots, also when a fault unwinds through the render.
        void MemberAfterRender(void*)
        {
            if (!g_Injection.active)
                return;
            g_Injection.active = false;
            const int kept = RestoreInjected(g_Injection.slots, g_Injection.saved, g_Injection.injected);
            if (kept != 0)
                LogBudgeted(L"[OVERFLOW] member list restore: %d team slot(s) %ls\n", kept < 0 ? 0 : kept,
                            kept < 0 ? L"faulted" : L"changed during the render were kept");
        }

        // ---- part 5: Ctrl+Offense ------------------------------------------

        void AppendGroupedOffense(void* panel)
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(panel);
            uint32_t selection[Policy::kSelectCapacity] = {};
            int count = 0;
            if (!ReadInt(base + kSelectNumOffset, count) || count < 0 || count > Policy::kSelectCapacity ||
                !ReadBytes(base + kSelectListOffset, selection, static_cast<size_t>(count) * 4))
                return;
            const int before = count;
            for (int g = 0; g < kGroupCount && count < Policy::kSelectCapacity; ++g)
            {
                uint32_t handles[kGroupCapacity];
                const int n = ReadGroup(g, handles);
                for (int i = 0; i < n && count < Policy::kSelectCapacity; ++i)
                {
                    void* const obj = SafeGetObj(handles[i]);
                    if (!obj || !IsPlayerTeam(obj) || !IsCraft(obj))
                        continue;
                    const uintptr_t cls = SafeGetClass(obj);
                    int minSlot = -1;
                    if (cls == 0 || !ReadInt(cls + kClassMinSlotOffset, minSlot) || minSlot != Policy::kOffenseMinSlot ||
                        !SafeCanCommand(obj))
                        continue;
                    const uint32_t handle = SafeGetHandle(obj);
                    const int next = Policy::AppendUnique(selection, count, Policy::kSelectCapacity, handle);
                    if (next == count)
                        continue;
                    // As stock SelectType does (FUN_004a6a50 lines 17-21).
                    if (!SafeSetSelected(obj) ||
                        !WriteBytes(base + kSelectListOffset + 4 * static_cast<size_t>(count), &handle, 4) ||
                        !WriteBytes(base + kSelectNumOffset, &next, sizeof(next)))
                        return;
                    count = next;
                }
            }
            if (count != before)
                LogBudgeted(L"[OVERFLOW] Ctrl+Offense added %d grouped unit(s)\n", count - before);
        }

        void __fastcall SelectTypeHook(void* panel, void*, int item)
        {
            g_FnSelectType(panel, item);
            if (item == Policy::kOffenseItem && g_SelectAllActive.load(std::memory_order_acquire) &&
                reinterpret_cast<uintptr_t>(panel) == g_ControlPanelAddr)
                AppendGroupedOffense(panel);
        }

        // ---- part 6: the Ctrl category labels ------------------------------

        constexpr int kRelabelItems = 3;
        constexpr size_t kLabelChars = 64;
        char g_LabelSource[kRelabelItems][kLabelChars] = {};
        char g_LabelText[kRelabelItems][kLabelChars] = {};

        // ShimFormat allocates; nothing may throw into the engine.
        bool FormatAllLabel(const char* stock, char (&out)[kLabelChars])
        {
            try
            {
                const std::string text = ShimFormat("openshim_ui:overflow_all_category", "All %s", stock);
                strncpy_s(out, text.c_str(), _TRUNCATE);
                return out[0] != '\0';
            }
            catch (...)
            {
                return false;
            }
        }

        const char* __cdecl CategoryLabelDecide(const char* section, const char* key, void* panel, int item)
        {
            const char* const stock = g_FnLocalize(section, key);
            if (!stock || !g_LabelActive.load(std::memory_order_acquire) ||
                reinterpret_cast<uintptr_t>(panel) != g_ControlPanelAddr)
                return stock;
            const uintptr_t base = reinterpret_cast<uintptr_t>(panel);
            int selectNum = 0;
            int currentItem = 0;
            uint8_t multi = 0;
            if (!ReadInt(base + kSelectNumOffset, selectNum) || !ReadInt(base + kCurrentItemOffset, currentItem) ||
                !ReadBytes(g_CmdMultiAddr, &multi, 1))
                return stock;
            if (!Policy::ShouldRelabelCategory(true, multi != 0, selectNum, currentItem, item) || item >= kRelabelItems)
                return stock;
            char source[kLabelChars] = {};
            if (!ReadBytes(reinterpret_cast<uintptr_t>(stock), source, 1))
                return stock;
            strncpy_s(source, stock, _TRUNCATE);
            if (std::strcmp(source, g_LabelSource[item]) != 0 || g_LabelText[item][0] == '\0')
            {
                if (!FormatAllLabel(source, g_LabelText[item]))
                    return stock;
                std::memcpy(g_LabelSource[item], source, sizeof(source));
            }
            return g_LabelText[item];
        }

#if defined(_M_IX86)
        // Entered in place of `call UiLocalize` at 0x004A6989 (cdecl,
        // [esp+4] "names", [esp+8] the MENU_ITEM name); ebp is still
        // ControlPanel::Render's frame: item [ebp-0x248], this [ebp-0x244]
        // (ControlPanelCategoryLabelLocalizeCall, HudFadeCommandRender).
        __declspec(naked) void CategoryLabelThunk()
        {
            __asm
            {
                mov eax, dword ptr [ebp - 0x248]
                mov ecx, dword ptr [ebp - 0x244]
                push eax
                push ecx
                push dword ptr [esp + 0x10]
                push dword ptr [esp + 0x10]
                call CategoryLabelDecide
                add esp, 0x10
                ret
            }
        }
#endif

        // ---- install -------------------------------------------------------

        // Redirects the E8 call at `site` to `target` when it still calls
        // `expectedCallee`. Returns the original callee on success, 0 else.
        uint32_t RedirectCall(uint32_t site, const void* target, uint32_t expectedCallee, const char* name)
        {
            uint8_t original[5] = {};
            if (!ReadBytes(site, original, sizeof(original)) || original[0] != 0xE8)
                return 0;
            int32_t rel = 0;
            std::memcpy(&rel, original + 1, sizeof(rel));
            const uint32_t callee = site + 5 + static_cast<uint32_t>(rel);
            if (callee != expectedCallee)
            {
                Log(L"[OVERFLOW] %hs: call at 0x%08X goes to 0x%08X, not 0x%08X; left stock\n", name, site, callee,
                    expectedCallee);
                return 0;
            }
            HookEngine::PatchDef patch;
            patch.address = site;
            patch.type = HookEngine::PatchType::REL32;
            patch.name = name;
            patch.verified = true;
            patch.expected_original.assign(original, original + sizeof(original));
            const int32_t newRel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) -
                                   static_cast<int32_t>(site + 5);
            patch.payload.assign(5, 0);
            patch.payload[0] = 0xE8;
            std::memcpy(patch.payload.data() + 1, &newRel, sizeof(newRel));
            if (!HookEngine::ApplyPatch(patch))
            {
                Log(L"[OVERFLOW] %hs: patch refused\n", name);
                return 0;
            }
            return callee;
        }

        bool InstallShared()
        {
            if (g_SharedReady)
                return true;
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
                return false;
            const HookEngine::EngineRow rows[] = {
                { "ControlPanelGlobal", &g_ControlPanelAddr },
                { "ControlPanelVtable", &g_ControlPanelVtableAddr },
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "HudFadeGetTeam", &g_GetTeamAddr },
                // Guards: team slots at Team +0, MENU_ITEM[0] = slots 5-14.
                { "TeamGetSlot", &g_TeamGetSlotAddr },
                { "ControlPanelMenuItems", &g_MenuItemsAddr },
            };
            if (!HookEngine::BindEngineRows("Offense overflow", rows))
                return false;
            if (g_GameObjectGetHandleAddr == 0 || !ControlPanelIdentityOk())
            {
                LogBudgeted(L"[OVERFLOW] GetHandle unresolved or ControlPanel identity failed; not installed\n");
                return false;
            }
            g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
            g_FnGetTeam = reinterpret_cast<FnGetTeam>(g_GetTeamAddr);
            g_SharedReady = true;
            return true;
        }

        void InstallExtended()
        {
#if defined(_M_IX86)
            if (!g_GateReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ProducerModeListFirstEmptySlotCall", &g_GateRowAddr },
                    { "TeamFirstEmptySlot", &g_FirstEmptySlotAddr },
                };
                if (HookEngine::BindEngineRows("Extended unit cap build gate", rows))
                {
                    g_FnFirstEmptySlot = reinterpret_cast<FnFirstEmptySlot>(g_FirstEmptySlotAddr);
                    g_GateReady = RedirectCall(g_GateRowAddr + kGateCallOffset, &BuildGateThunk, g_FirstEmptySlotAddr,
                                               "Producer::UpdateModeList/FirstEmptySlot (overflow)") != 0;
                }
            }
            // Each site is bound and redirected once: a redirected site no
            // longer matches its row bytes, so a retry must not re-bind it.
            // A site that went in stays a stock pass-through while inactive.
            static bool s_freeSlotSite1 = false;
            static bool s_freeSlotSite2 = false;
            if (!g_FreeSlotReady && !s_freeSlotSite1)
            {
                const HookEngine::EngineRow rows[] = {
                    { "TeamHasFreeSlot", &g_HasFreeSlotAddr },
                    { "TeamHasFreeSlotGetEmptyVehicleCall", &g_HasFreeSlotRow1Addr },
                };
                if (HookEngine::BindEngineRows("Extended unit cap free slot (vehicle)", rows))
                {
                    g_FnTeamHasFreeSlot = reinterpret_cast<FnTeamHasFreeSlot>(g_HasFreeSlotAddr);
                    s_freeSlotSite1 = RedirectCall(g_HasFreeSlotRow1Addr + kFreeSlotCall1Offset,
                                                   reinterpret_cast<const void*>(&TeamHasFreeSlotHook),
                                                   g_HasFreeSlotAddr, "GetEmptyVehicle/TeamHasFreeSlot (overflow)") != 0;
                }
            }
            if (!g_FreeSlotReady && s_freeSlotSite1 && !s_freeSlotSite2)
            {
                const HookEngine::EngineRow rows[] = {
                    { "TeamHasFreeSlotCountCall", &g_HasFreeSlotRow2Addr },
                };
                if (HookEngine::BindEngineRows("Extended unit cap free slot (count)", rows))
                    s_freeSlotSite2 = RedirectCall(g_HasFreeSlotRow2Addr + kFreeSlotCall2Offset,
                                                   reinterpret_cast<const void*>(&TeamHasFreeSlotHook),
                                                   g_HasFreeSlotAddr, "FUN_004798D0/TeamHasFreeSlot (overflow)") != 0;
            }
            g_FreeSlotReady = s_freeSlotSite1 && s_freeSlotSite2;
#endif
        }

        void InstallMember()
        {
#if defined(_M_IX86)
            if (!g_MemberReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "HudFadeCommandRender", &g_RenderAddr },
                    { "HudFadeCommandInputs", &g_InputsAddr },
                    { "CommandMenuUnitBranchInput", &g_CmdMultiAddr },
                    { "ControlPanelGroupKeyLoop", &g_GroupKeyLoopAddr },
                    { "ControlPanelSelectNone", &g_SelectNoneAddr },
                };
                if (HookEngine::BindEngineRows("Group member list", rows))
                {
                    g_FnSelectNone = reinterpret_cast<FnSelectNone>(g_SelectNoneAddr);
                    g_MemberReady = true;
                    g_ScopePending.store(true, std::memory_order_release);
                }
            }
            if (g_MemberReady && !g_LabelReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelCategoryLabelLocalizeCall", &g_LabelRowAddr },
                    { "UiLocalize", &g_LocalizeAddr },
                };
                if (HookEngine::BindEngineRows("Group member list Ctrl labels", rows))
                {
                    g_FnLocalize = reinterpret_cast<FnLocalize>(g_LocalizeAddr);
                    g_LabelReady = RedirectCall(g_LabelRowAddr + kLabelCallOffset, &CategoryLabelThunk,
                                                g_LocalizeAddr, "ControlPanel::Render/category label (overflow)") != 0;
                }
            }
            if (g_MemberReady && !g_SelectAllReady)
            {
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelSelectType", &g_SelectTypeAddr },
                    { "ControlPanelSelectTypeCall", &g_SelectTypeRowAddr },
                    { "GameObjectSetSelected", &g_SetSelectedAddr },
                };
                if (HookEngine::BindEngineRows("Ctrl+Offense grouped units", rows))
                {
                    g_FnSelectType = reinterpret_cast<FnSelectType>(g_SelectTypeAddr);
                    g_FnSetSelected = reinterpret_cast<FnSetSelected>(g_SetSelectedAddr);
                    g_SelectAllReady = RedirectCall(g_SelectTypeRowAddr + kSelectTypeCallOffset,
                                                    reinterpret_cast<const void*>(&SelectTypeHook), g_SelectTypeAddr,
                                                    "ControlPanel::Render/SelectType (overflow)") != 0;
                }
            }
#endif
        }

        bool ExtendedReady()
        {
            return g_SharedReady && g_GateReady && g_FreeSlotReady && AutoGroupNewUnitsReady();
        }

        bool MemberPartsReady()
        {
            return g_SharedReady && g_MemberReady && g_LabelReady && g_SelectAllReady;
        }
    }

    // Exported to auto_group_new_units.cpp and group_strip.cpp.
    bool OffenseOverflowExtendsAutoGroup()
    {
        return g_ExtendedEnabled && ExtendedReady() && IsSinglePlayerSession();
    }

    int OffenseOverflowMemberGroup()
    {
        return g_MemberGroup.load(std::memory_order_acquire);
    }

    void ReloadOffenseOverflowConfig()
    {
        bool value = false;
        g_ExtendedEnabled = TryGetUserConfigBool("Gameplay", "ExtendedUnitCap", value) ? value : false;
        value = true;
        g_MemberEnabled = TryGetUserConfigBool("Gameplay", "GroupMemberMenu", value) ? value : true;
        if (!g_ConfigRead)
            Log(L"[OVERFLOW] Baseline ExtendedUnitCap=%hs GroupMemberMenu=%hs (SP-only)\n",
                g_ExtendedEnabled ? "yes" : "no", g_MemberEnabled ? "yes" : "no");
        g_ConfigRead = true;
        RefreshOffenseOverflowState();
    }

    // Patch thread, from InstallAiTuningHooksIfPossible. Retried until every
    // part binds or kMaxInstallAttempts passes have run (on Steam a row can
    // be a page SteamStub has not finished with).
    void InstallOffenseOverflowIfPossible()
    {
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (!g_ConfigRead)
            ReloadOffenseOverflowConfig();
        ++s_attempts;
        if (InstallShared())
        {
            InstallExtended();
            InstallMember();
        }
        const bool extended = ExtendedReady();
        const bool member = MemberPartsReady();
        if (extended)
            ClearOptionHookFailed("ExtendedUnitCap");
        else
            MarkOptionHookFailed("ExtendedUnitCap",
                                 "Unavailable: Extended Unit Cap did not hook on this game build (see openshim.log).");
        // A render scope failure (TickOffenseOverflow) keeps its own mark.
        if (member)
        {
            if (!g_ScopeFailed.load(std::memory_order_acquire))
                ClearOptionHookFailed("GroupMemberMenu");
        }
        else
            MarkOptionHookFailed("GroupMemberMenu",
                                 "Unavailable: Group Member Menu did not hook on this game build (see openshim.log).");
        if ((extended && member) || s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[OVERFLOW] install %hs after %d attempt(s): build gate %hs, free slot %hs, member list %hs, "
                L"Ctrl labels %hs, Ctrl+Offense %hs\n",
                (extended && member) ? "complete" : "gave up", s_attempts, g_GateReady ? "yes" : "no",
                g_FreeSlotReady ? "yes" : "no", g_MemberReady ? "yes" : "no", g_LabelReady ? "yes" : "no",
                g_SelectAllReady ? "yes" : "no");
        }
        RefreshOffenseOverflowState();
    }

    // Frame/game thread (beside TickGroupStrip): attaches the member list's
    // render scope once, the first time the feature is active.
    void TickOffenseOverflow()
    {
        if (!g_ScopePending.load(std::memory_order_acquire) || !g_MemberActive.load(std::memory_order_acquire))
            return;
        if (!g_ScopePending.exchange(false, std::memory_order_acq_rel))
            return;
        if (ContextualHud::RegisterCommandPanelRenderScope(&MemberBeforeRender, &MemberAfterRender))
            Log(L"[OVERFLOW] member list render scope registered\n");
        else
        {
            Log(L"[OVERFLOW] command panel render scope unavailable; member list off\n");
            g_ScopeFailed.store(true, std::memory_order_release);
            MarkOptionHookFailed("GroupMemberMenu",
                                 "Unavailable: the command panel render slot is not available (see openshim.log).");
        }
    }

    void RefreshOffenseOverflowState()
    {
        const bool sp = IsSinglePlayerSession();
        const bool extended = g_ExtendedEnabled && ExtendedReady() && sp;
        const bool member = g_MemberEnabled && MemberPartsReady() && sp;
        if (extended != g_ExtendedActive.load(std::memory_order_acquire) ||
            member != g_MemberActive.load(std::memory_order_acquire))
            Log(L"[OVERFLOW] ExtendedUnitCap %hs, GroupMemberMenu %hs\n", extended ? "active" : "off",
                member ? "active" : "off");
        g_ExtendedActive.store(extended, std::memory_order_release);
        g_MemberActive.store(member, std::memory_order_release);
        g_LabelActive.store(member, std::memory_order_release);
        g_SelectAllActive.store(member && extended, std::memory_order_release);
        if (!member)
            g_MemberGroup.store(-1, std::memory_order_release);
        // ExtendedUnitCap implies auto-group.
        RefreshAutoGroupNewUnitsState();
    }

    // Mission end/load: close any member list.
    void ResetOffenseOverflow()
    {
        g_MemberGroup.store(-1, std::memory_order_release);
        g_LogBudget = 32;
        RefreshOffenseOverflowState();
    }
}
