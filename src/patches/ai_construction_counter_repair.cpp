// ai_construction_counter_repair.cpp
// BZR Open Shim - AIConstructionCounterRepair ([Fixes], single-player only):
// ends the AI "under construction" count when a producer is destroyed while
// it is building a unit, so the count cannot stay above zero for the rest of
// the mission and silence the build list for that unit type.
//
// The counters (Redux 2.2.301 decompile, battlezone98redux.exe-6777ca):
//   number_under_construction[team][prereq]  int table per team, pointer array
//                                            at 0x00930FC0 (FUN_00690630 callocs
//                                            each team's table)
//   facilities_under_construction[team]      int array at 0x02BFDFB0, moved with
//                                            the table by AIBuild_ConstructionBegin
//                                            / End (FUN_00690570 / FUN_006905d0)
// They are per team and per type, not two process-wide ints. The build list
// (FUN_006912b0) adds the table entry to the live object count before it
// compares against the wanted count, so one stuck entry stops that type.
//
// Unmatched path: the 1.5 AI_BuildingRemove ends the count when a building
// whose order is 3 (building a unit) is removed. Redux's BuildAttachment
// destructor (FUN_006a1940) has no such clause and FUN_0068fc60 (AI_UnitRemove)
// does not cover producers. Begin happens at FUN_00690fc0; End happens only
// when the unit object appears (FUN_0068fac0 from the UnitAttachment ctor).
//
// Fix (tier 1, exact): remember which prereq a producer record was last given
// (FUN_006a4230 / FUN_006a4380 returning 1). When that record is destroyed
// while its cached state (+0x20, refreshed from the live object each tick by
// FUN_006a1590) still reads 3, call the engine's own ConstructionEnd once. The
// call is skipped when the table entry is already 0, so it cannot go negative.
//
// Second leak (constructor buildings): the per-tick CNST check in
// FUN_006a3490 (decompile lines 37-48) releases a constructor once it goes
// idle. When the building was never placed (+0x38 == 0) it calls
// AI_BuildingStalled (FUN_0068fe40), which ends the count (FUN_0068fe40.c:8).
// When the building was placed (+0x38 != 0) it only calls
// AIBuild_UnassignedCCAdd (FUN_00690770) and clears the record, so every
// successful AI building leaves its count, and facilities_under_construction,
// at +1 for the rest of the mission (seen live with TraceAIBuildLedger: Begin
// for kind=1 prereqs with no End). Fix: redirect that call (0x006A35F5) to a
// stub that ends the count for (team = rec+0x10, prereq = rec+0x30) with the
// same guards, then calls the stock AIBuild_UnassignedCCAdd.
//
// Multiplayer: AI planning is part of the simulation and is not negotiated
// with peers, so the fix stands down in a network game like the other
// simulation-affecting [Fixes] entries.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <windows.h>
#include <cstdint>
#include <unordered_map>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            constexpr size_t kTeamCount = 16;
            constexpr uintptr_t kTeamControlStride = 0x1E0;
            constexpr uintptr_t kRecordStateOffset = 0x20;  // attachment + 0x20 == record + 0x1C
            constexpr int kStateBuilding = 3;
            constexpr DWORD kLogIntervalMs = 2000;

            using FnConstructEnd = void(__cdecl*)(int team, int prereq);
            using FnConstruct = int(__cdecl*)(void* record, void* typeInfo);
            using FnAttachDtor = void(__fastcall*)(void* self, void* edx);
            using FnCCAdd = void(__cdecl*)(void* teamAI, void* record);
            constexpr uintptr_t kCnstDoneCallOffset = 0x15;  // row start -> E8 of the CCAdd call

            // Prologues from the shipping exe; the guard rows in patches.json
            // pin the same bytes.
            const uint8_t kConstructPrologue[9] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x8B, 0x45, 0x08 };
            const uint8_t kDtorPrologue[7] = { 0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC };

            bool g_Enabled = false;
            bool g_Installed = false;
            bool g_ConfigRead = false;

            uint32_t g_CountsAddr = 0;      // int* [16]        (0x00930FC0)
            uint32_t g_AllocatedAddr = 0;   // int  [16]        (0x00930F80)
            uint32_t g_ControlAddr = 0;     // char [16*0x1E0]  (0x02CE9B18)
            uint32_t g_TeamTableAddr = 0;   // pointer variable (0x00920F04), non-null once AI exists
            uint32_t g_EndAddr = 0;
            uint32_t g_CCAddAddr = 0;       // AIBuild_UnassignedCCAdd (0x00690770)

            InlineDetour32 g_UnitDetour;
            InlineDetour32 g_BuildDetour;
            InlineDetour32 g_DtorDetour;
            FnConstruct g_OrigConstructUnit = nullptr;
            FnConstruct g_OrigConstructBuild = nullptr;
            FnAttachDtor g_OrigDtor = nullptr;

            // producer record -> prereq it was last assigned. Game thread only.
            std::unordered_map<uintptr_t, uint16_t> g_Pending;
            unsigned g_Corrections = 0;
            DWORD g_LastLogTick = 0;
            unsigned g_SuppressedSinceLog = 0;

            bool Active()
            {
                return g_Enabled && g_Installed && IsSinglePlayerSession();
            }

            void NotePending(void* record, uint16_t prereq)
            {
                if (record)
                    g_Pending[reinterpret_cast<uintptr_t>(record)] = prereq;
            }

            int __cdecl ConstructUnitHook(void* record, void* typeInfo)
            {
                const int result = g_OrigConstructUnit(record, typeInfo);
                if (result == 1 && record && typeInfo && Active())
                    NotePending(record, *reinterpret_cast<const uint16_t*>(static_cast<const uint8_t*>(typeInfo) + 0x5A));
                return result;
            }

            int __cdecl ConstructBuildHook(void* record, void* typeInfo)
            {
                const int result = g_OrigConstructBuild(record, typeInfo);
                if (result == 1 && record && typeInfo && Active())
                    NotePending(record, *reinterpret_cast<const uint16_t*>(typeInfo));
                return result;
            }

            // Ends one construction count with the guards both repairs share.
            // Returns the count before the call, or -1 when nothing was ended.
            int EndConstructionGuarded(int team, uint32_t prereq)
            {
                if (team < 0 || team >= static_cast<int>(kTeamCount) || prereq > 0xFFFFu)
                    return -1;
                // AI exists, this team is AI-controlled and its table is live.
                if (*reinterpret_cast<const uint32_t*>(g_TeamTableAddr) == 0)
                    return -1;
                if (*reinterpret_cast<const uint8_t*>(g_ControlAddr + static_cast<uintptr_t>(team) * kTeamControlStride) == 0)
                    return -1;
                if (reinterpret_cast<const int*>(g_AllocatedAddr)[team] != 1)
                    return -1;
                int* table = reinterpret_cast<int* const*>(g_CountsAddr)[team];
                if (!table || table[prereq] <= 0)
                    return -1;
                const int before = table[prereq];
                reinterpret_cast<FnConstructEnd>(g_EndAddr)(team, static_cast<int>(prereq));
                ++g_Corrections;
                return before;
            }

            void LogCorrection(const wchar_t* what, int team, uint32_t prereq, int before)
            {
                const DWORD now = GetTickCount();
                if (g_LastLogTick == 0 || now - g_LastLogTick >= kLogIntervalMs)
                {
                    const int after = reinterpret_cast<int* const*>(g_CountsAddr)[team][prereq];
                    Log(L"[AICOUNTER] %ls: ended construction team=%d prereq=%u count %d -> %d (corrections=%u, +%u since last log)\n",
                        what, team, static_cast<unsigned>(prereq), before, after, g_Corrections, g_SuppressedSinceLog);
                    g_LastLogTick = now;
                    g_SuppressedSinceLog = 0;
                }
                else
                {
                    ++g_SuppressedSinceLog;
                }
            }

            // Replaces the call to AIBuild_UnassignedCCAdd(teamAI, record) on
            // the "building placed" branch of the CNST idle check. Same cdecl
            // signature; the caller cleans the two arguments.
            void __cdecl ConstructorDoneCCAddHook(void* teamAI, void* record)
            {
                if (record && Active())
                {
                    const auto* rec = static_cast<const uint8_t*>(record);
                    const int team = static_cast<int>(*reinterpret_cast<const int8_t*>(rec + 0x10));
                    const uint32_t prereq = *reinterpret_cast<const uint32_t*>(rec + 0x30);
                    const int before = EndConstructionGuarded(team, prereq);
                    if (before >= 0)
                        LogCorrection(L"Constructor finished building", team, prereq, before);
                }
                reinterpret_cast<FnCCAdd>(g_CCAddAddr)(teamAI, record);
            }

            void RepairForRecord(void* attachment)
            {
                auto* base = static_cast<uint8_t*>(attachment);
                const auto it = g_Pending.find(reinterpret_cast<uintptr_t>(base + 4));
                if (it == g_Pending.end())
                    return;
                const uint16_t prereq = it->second;
                g_Pending.erase(it);

                if (*reinterpret_cast<const int*>(base + kRecordStateOffset) != kStateBuilding)
                    return;
                const int team = *reinterpret_cast<const int*>(base + 4);
                const int before = EndConstructionGuarded(team, prereq);
                if (before >= 0)
                    LogCorrection(L"Producer destroyed mid-build", team, prereq, before);
            }

            void __fastcall AttachDtorHook(void* self, void* edx)
            {
                if (self && g_Installed)
                {
                    if (Active())
                        RepairForRecord(self);
                    else
                        g_Pending.erase(reinterpret_cast<uintptr_t>(static_cast<uint8_t*>(self) + 4));
                }
                g_OrigDtor(self, edx);
            }

            bool InstallHooks()
            {
                if (g_Installed)
                    return true;

                uint32_t fnUnit = 0, fnBuild = 0, fnDtor = 0, cnstDone = 0;
                const HookEngine::EngineRow rows[] = {
                    { "AiBuildConstructUnit", &fnUnit },
                    { "AiBuildConstructBuild", &fnBuild },
                    { "AiBuildAttachmentDtor", &fnDtor },
                    { "AIBuildConstructionEnd", &g_EndAddr },
                    { "AiConstructionCounts", &g_CountsAddr },
                    { "AiConstructionAllocated", &g_AllocatedAddr },
                    { "AiTeamData", &g_ControlAddr },
                    { "AiTeamTable", &g_TeamTableAddr },
                    { "AIBuildUnassignedCCAdd", &g_CCAddAddr },
                    { "AiBuildCnstDoneCCAddCall", &cnstDone },
                };
                if (!HookEngine::BindEngineRows("AI construction counter repair", rows))
                    return false;

                bool ok = InstallInlineDetour32(g_UnitDetour, fnUnit, reinterpret_cast<void*>(ConstructUnitHook),
                                                sizeof(kConstructPrologue), kConstructPrologue, sizeof(kConstructPrologue),
                                                reinterpret_cast<void* volatile*>(&g_OrigConstructUnit));
                ok = ok && InstallInlineDetour32(g_BuildDetour, fnBuild, reinterpret_cast<void*>(ConstructBuildHook),
                                                 sizeof(kConstructPrologue), kConstructPrologue, sizeof(kConstructPrologue),
                                                 reinterpret_cast<void* volatile*>(&g_OrigConstructBuild));
                ok = ok && InstallInlineDetour32(g_DtorDetour, fnDtor, reinterpret_cast<void*>(AttachDtorHook),
                                                 sizeof(kDtorPrologue), kDtorPrologue, sizeof(kDtorPrologue),
                                                 reinterpret_cast<void* volatile*>(&g_OrigDtor));
                ok = ok && RedirectCallTarget(cnstDone + kCnstDoneCallOffset, g_CCAddAddr,
                                              reinterpret_cast<uintptr_t>(&ConstructorDoneCCAddHook));
                if (!ok)
                {
                    // A detour that did install keeps forwarding to its own
                    // trampoline; the hooks stay inert because g_Installed is false.
                    Log(L"[AICOUNTER] Detour install failed; construction counter repair disabled\n");
                    return false;
                }
                g_Installed = true;
                return true;
            }
        }

        void InitializeAiConstructionCounterRepairConfig()
        {
            if (g_ConfigRead)
                return;
            g_ConfigRead = true;

            // Exact fix, but not yet live-verified: default OFF until a repro
            // (kill a factory mid-build) confirms it. Read once at startup.
            bool cfg = false;
            g_Enabled = TryGetUserConfigBool(kUserConfigFixesSection, "AIConstructionCounterRepair", cfg) && cfg;
            if (EnvFlagEnabled("OPENSHIM_DISABLE_AI_CONSTRUCTION_COUNTER_REPAIR"))
                g_Enabled = false;
            if (g_Enabled && !InstallHooks())
                g_Enabled = false;
            Log(L"[AICOUNTER] AI construction counter repair %hs (single-player only; ends the per-team per-type count when a producer dies mid-build or a constructor finishes a building)\n",
                g_Enabled ? "active" : "off");
        }
    }
}
