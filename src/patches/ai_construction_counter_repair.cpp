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
                if (team < 0 || team >= static_cast<int>(kTeamCount))
                    return;
                // AI exists, this team is AI-controlled and its table is live.
                if (*reinterpret_cast<const uint32_t*>(g_TeamTableAddr) == 0)
                    return;
                if (*reinterpret_cast<const uint8_t*>(g_ControlAddr + static_cast<uintptr_t>(team) * kTeamControlStride) == 0)
                    return;
                if (reinterpret_cast<const int*>(g_AllocatedAddr)[team] != 1)
                    return;
                int* table = reinterpret_cast<int* const*>(g_CountsAddr)[team];
                if (!table || table[prereq] <= 0)
                    return;

                const int before = table[prereq];
                reinterpret_cast<FnConstructEnd>(g_EndAddr)(team, prereq);
                ++g_Corrections;

                const DWORD now = GetTickCount();
                if (g_LastLogTick == 0 || now - g_LastLogTick >= kLogIntervalMs)
                {
                    Log(L"[AICOUNTER] Producer destroyed mid-build: ended construction team=%d prereq=%u count %d -> %d (corrections=%u, +%u since last log)\n",
                        team, static_cast<unsigned>(prereq), before, table[prereq], g_Corrections, g_SuppressedSinceLog);
                    g_LastLogTick = now;
                    g_SuppressedSinceLog = 0;
                }
                else
                {
                    ++g_SuppressedSinceLog;
                }
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

                uint32_t fnUnit = 0, fnBuild = 0, fnDtor = 0;
                const HookEngine::EngineRow rows[] = {
                    { "AiBuildConstructUnit", &fnUnit },
                    { "AiBuildConstructBuild", &fnBuild },
                    { "AiBuildAttachmentDtor", &fnDtor },
                    { "AIBuildConstructionEnd", &g_EndAddr },
                    { "AiConstructionCounts", &g_CountsAddr },
                    { "AiConstructionAllocated", &g_AllocatedAddr },
                    { "AiTeamData", &g_ControlAddr },
                    { "AiTeamTable", &g_TeamTableAddr },
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
            Log(L"[AICOUNTER] AI construction counter repair %hs (single-player only; ends the per-team per-type count when a producer dies mid-build)\n",
                g_Enabled ? "active" : "off");
        }
    }
}
