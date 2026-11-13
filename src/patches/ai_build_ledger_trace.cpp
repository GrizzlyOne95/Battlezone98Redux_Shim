// ai_build_ledger_trace.cpp
// BZR Open Shim - TraceAIBuildLedger ([Diagnostics], default OFF, read-only).
//
// Tests the "AI stops building after ~60 minutes" hypothesis (see
// reverse_engineering/notes/ai_long_game_build_stall_20261109.md, D1 and D2): that
// AIBuild_ConstructionBegin runs without a matching AIBuild_ConstructionEnd, so
// number_under_construction[team][prereq] only ever grows and the build list
// (HowMany + uc < wanted) goes quiet.
//
//   1. Ledger: one [AIBUILD] line per Begin (0x00690570) / End (0x006905D0) call,
//      logged after the original ran, with the counter value afterwards.
//   2. Every 10 s of wall time, per live AI team: sum of the counters, the rows
//      with counter > 0, facilities_under_construction and reserved-area slot
//      occupancy.
//   3. Producer::StartBuild (0x005AECB0) returning 0 when called by
//      Build_ConstructUnit / Build_ConstructBuild (candidate 3).
//
// Nothing here changes behaviour. Every read is bounds-checked against the
// verified table layouts; a byte mismatch at any hooked address stands it down.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <windows.h>
#include <intrin.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            constexpr int kTeamCount = 16;
            constexpr uintptr_t kTeamControlStride = 0x1E0;
            constexpr uintptr_t kPrereqStride = 0x9C;      // FUN_006a05c0: kind byte at +0
            constexpr int kReservedSlotsPerTeam = 0x20;    // FUN_00690870 pool
            constexpr unsigned kMaxLogLines = 20000;
            constexpr ULONGLONG kDumpIntervalMs = 10000;
            constexpr uintptr_t kBuildCallerLo = 0x006A4230; // Build_ConstructUnit .. Build_ConstructBuild
            constexpr uintptr_t kBuildCallerHi = 0x006A4500;

            using FnConstruction = void(__cdecl*)(int team, int prereq);
            using FnStartBuild = unsigned(__fastcall*)(void* self, void* edx, void* typeInfo);

            // Prologues from the shipping exe; the rows in patches.json pin the same bytes.
            const uint8_t kConstructionPrologue[6] = { 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08 };
            const uint8_t kStartBuildPrologue[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C };

            bool g_ConfigRead = false;
            bool g_Installed = false;

            uint32_t g_CountsAddr = 0;        // int* [16]            0x00930FC0
            uint32_t g_AllocatedAddr = 0;     // int  [16]            0x00930F80
            uint32_t g_ControlAddr = 0;       // char [16*0x1E0]      0x02CE9B18
            uint32_t g_TeamTableAddr = 0;     // pointer variable     0x00920F04
            uint32_t g_FacilitiesAddr = 0;    // int  [16]            0x02BFDFB0
            uint32_t g_ReservedAddr = 0;      // char [16*0x20]       0x02BFDDB0
            uint32_t g_PrereqTableAddr = 0;   // pointer variable     0x02CEB7E8
            uint32_t g_PrereqCountAddr = 0;   // int variable         0x02CEB7FC
            uint32_t g_TickAddr = 0;          // int variable         0x00931014

            InlineDetour32 g_BeginDetour;
            InlineDetour32 g_EndDetour;
            InlineDetour32 g_StartBuildDetour;
            FnConstruction g_OrigBegin = nullptr;
            FnConstruction g_OrigEnd = nullptr;
            FnStartBuild g_OrigStartBuild = nullptr;

            unsigned g_LinesLogged = 0;
            bool g_CapNoted = false;
            ULONGLONG g_LastDumpMs = 0;

            bool LineBudget()
            {
                if (g_LinesLogged < kMaxLogLines)
                {
                    ++g_LinesLogged;
                    return true;
                }
                if (!g_CapNoted)
                {
                    g_CapNoted = true;
                    Log(L"[AIBUILD] line cap (%u) reached; further output suppressed\n", kMaxLogLines);
                }
                return false;
            }

            uint32_t g_SizeAAddr = 0;         // int variable         0x009310C4
            uint32_t g_SizeBAddr = 0;         // int variable         0x02C00ABC

            // Readable rows: min(live prereq count, allocated table size). FUN_00690630
            // callocs (A + 1 + B) ints per team; the two may diverge if either term
            // changes after allocation, so never index past the smaller one.
            int ReadableRows()
            {
                const int count = *reinterpret_cast<const int*>(g_PrereqCountAddr);
                const int size = *reinterpret_cast<const int*>(g_SizeAAddr) + 1 +
                                 *reinterpret_cast<const int*>(g_SizeBAddr);
                return count < size ? count : size;
            }

            int ReadTick()
            {
                return *reinterpret_cast<const int*>(g_TickAddr);
            }

            int* TeamTable(int team)
            {
                if (team < 0 || team >= kTeamCount)
                    return nullptr;
                if (reinterpret_cast<const int*>(g_AllocatedAddr)[team] != 1)
                    return nullptr;
                return reinterpret_cast<int* const*>(g_CountsAddr)[team];
            }

            // Returns the prereq kind byte (0 unit, 1 building) or -1 if out of range.
            int PrereqKind(unsigned prereq)
            {
                const uint8_t* table = *reinterpret_cast<const uint8_t* const*>(g_PrereqTableAddr);
                const int count = *reinterpret_cast<const int*>(g_PrereqCountAddr);
                if (!table || count <= 0 || prereq >= static_cast<unsigned>(count))
                    return -1;
                return table[static_cast<uintptr_t>(prereq) * kPrereqStride];
            }

            void LogCall(char tag, int team, int prereq, void* caller)
            {
                if (!LineBudget())
                    return;
                const int* table = TeamTable(team);
                const int count = ReadableRows();
                int uc = 0;
                bool ucValid = false;
                if (table && prereq >= 0 && prereq < count)
                {
                    uc = table[prereq];
                    ucValid = true;
                }
                Log(L"[AIBUILD] %c team=%d prereq=%d kind=%d uc=%d%hs caller=0x%08X tick=%d\n",
                    tag, team, prereq, ucValid ? PrereqKind(static_cast<unsigned>(prereq)) : -1,
                    uc, ucValid ? "" : "(n/a)",
                    static_cast<unsigned>(reinterpret_cast<uintptr_t>(caller)), ReadTick());
            }

            void __cdecl BeginHook(int team, int prereq)
            {
                void* const caller = _ReturnAddress();
                g_OrigBegin(team, prereq);
                LogCall('B', team, prereq, caller);
            }

            void __cdecl EndHook(int team, int prereq)
            {
                void* const caller = _ReturnAddress();
                g_OrigEnd(team, prereq);
                LogCall('E', team, prereq, caller);
            }

            unsigned __fastcall StartBuildHook(void* self, void* edx, void* typeInfo)
            {
                void* const caller = _ReturnAddress();
                const unsigned result = g_OrigStartBuild(self, edx, typeInfo);
                const uintptr_t c = reinterpret_cast<uintptr_t>(caller);
                if ((result & 0xFF) == 0 && c >= kBuildCallerLo && c < kBuildCallerHi && LineBudget())
                {
                    // +0x300 = producer's current build (non-zero means already busy).
                    const uint32_t busy = self ? *reinterpret_cast<const uint32_t*>(static_cast<const uint8_t*>(self) + 0x300) : 0;
                    Log(L"[AIBUILD] S-FAIL producer=0x%08X type=0x%08X busy=%u caller=0x%08X tick=%d\n",
                        static_cast<unsigned>(reinterpret_cast<uintptr_t>(self)),
                        static_cast<unsigned>(reinterpret_cast<uintptr_t>(typeInfo)),
                        busy, static_cast<unsigned>(c), ReadTick());
                }
                return result;
            }

            void DumpTeam(int team)
            {
                const int* table = TeamTable(team);
                if (!table)
                    return;
                const int count = ReadableRows();
                int sum = 0;
                for (int p = 1; p < count; ++p)
                    sum += table[p];
                const int facilities = reinterpret_cast<const int*>(g_FacilitiesAddr)[team];
                int slots = 0;
                const uint8_t* flags = reinterpret_cast<const uint8_t*>(g_ReservedAddr) + team * kReservedSlotsPerTeam;
                for (int s = 0; s < kReservedSlotsPerTeam; ++s)
                    slots += flags[s] != 0;
                if (LineBudget())
                    Log(L"[AIBUILD] T team=%d sumUC=%d facilities=%d reserved=%d/%d tick=%d\n",
                        team, sum, facilities, slots, kReservedSlotsPerTeam, ReadTick());
                for (int p = 1; p < count; ++p)
                {
                    if (table[p] > 0 && LineBudget())
                        Log(L"[AIBUILD] R team=%d prereq=%d kind=%d uc=%d\n",
                            team, p, PrereqKind(static_cast<unsigned>(p)), table[p]);
                }
            }

            bool InstallHooks()
            {
                uint32_t fnBegin = 0, fnEnd = 0, fnStartBuild = 0;
                const HookEngine::EngineRow rows[] = {
                    { "AIBuildConstructionBegin", &fnBegin },
                    { "AIBuildConstructionEnd", &fnEnd },
                    { "ProducerStartBuild", &fnStartBuild },
                    { "AiConstructionCounts", &g_CountsAddr },
                    { "AiConstructionAllocated", &g_AllocatedAddr },
                    { "AiTeamData", &g_ControlAddr },
                    { "AiTeamTable", &g_TeamTableAddr },
                    { "AiFacilitiesUnderConstruction", &g_FacilitiesAddr },
                    { "AiReservedAreaFlags", &g_ReservedAddr },
                    { "AiPrereqTable", &g_PrereqTableAddr },
                    { "AiPrereqCount", &g_PrereqCountAddr },
                    { "AiTickCounter", &g_TickAddr },
                    { "AiCountsTableSizeA", &g_SizeAAddr },
                    { "AiCountsTableSizeB", &g_SizeBAddr },
                };
                if (!HookEngine::BindEngineRows("AI build ledger trace", rows))
                    return false;

                if (!ExpectedBytesMatchAt(fnBegin, kConstructionPrologue, sizeof(kConstructionPrologue)) ||
                    !ExpectedBytesMatchAt(fnEnd, kConstructionPrologue, sizeof(kConstructionPrologue)) ||
                    !ExpectedBytesMatchAt(fnStartBuild, kStartBuildPrologue, sizeof(kStartBuildPrologue)))
                {
                    Log(L"[AIBUILD] Hook site bytes do not match this build; trace stands down\n");
                    return false;
                }

                bool ok = InstallInlineDetour32(g_BeginDetour, fnBegin, reinterpret_cast<void*>(BeginHook),
                                                sizeof(kConstructionPrologue), kConstructionPrologue, sizeof(kConstructionPrologue),
                                                reinterpret_cast<void* volatile*>(&g_OrigBegin));
                ok = ok && InstallInlineDetour32(g_EndDetour, fnEnd, reinterpret_cast<void*>(EndHook),
                                                 sizeof(kConstructionPrologue), kConstructionPrologue, sizeof(kConstructionPrologue),
                                                 reinterpret_cast<void* volatile*>(&g_OrigEnd));
                ok = ok && InstallInlineDetour32(g_StartBuildDetour, fnStartBuild, reinterpret_cast<void*>(StartBuildHook),
                                                 sizeof(kStartBuildPrologue), kStartBuildPrologue, sizeof(kStartBuildPrologue),
                                                 reinterpret_cast<void* volatile*>(&g_OrigStartBuild));
                if (!ok)
                {
                    // Detours that did install keep forwarding to their trampolines;
                    // their hooks only log, and g_Installed stays false for the tick.
                    Log(L"[AIBUILD] Detour install failed; trace disabled\n");
                    return false;
                }
                return true;
            }
        }

        void InitializeAiBuildLedgerTraceConfig()
        {
            if (g_ConfigRead)
                return;
            g_ConfigRead = true;

            bool cfg = false;
            const bool wanted = TryGetUserConfigBool("Diagnostics", "TraceAIBuildLedger", cfg) && cfg;
            if (!wanted)
                return;
            g_Installed = InstallHooks();
            Log(L"[AIBUILD] AI build ledger trace %hs (read-only; Begin/End calls, 10 s counter dumps, StartBuild failures)\n",
                g_Installed ? "active" : "failed to install");
        }

        void TickAiBuildLedgerTrace()
        {
            if (!g_Installed)
                return;
            const ULONGLONG now = GetTickCount64();
            if (g_LastDumpMs != 0 && now - g_LastDumpMs < kDumpIntervalMs)
                return;
            g_LastDumpMs = now;
            // AI exists and this team is AI-controlled (same gate as the counter repair).
            if (*reinterpret_cast<const uint32_t*>(g_TeamTableAddr) == 0)
                return;
            for (int team = 0; team < kTeamCount; ++team)
            {
                if (*reinterpret_cast<const uint8_t*>(g_ControlAddr + static_cast<uintptr_t>(team) * kTeamControlStride) != 0)
                    DumpTeam(team);
            }
        }
    }
}
