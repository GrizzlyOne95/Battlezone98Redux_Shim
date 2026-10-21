#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "openshim_env_config.h"
#include "patcher.h"
#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

// AttackTask::DoState (0x00478A50) starts every call by asking
// UnitTask::NearestVehicle (0x00463FC0) for the closest vehicle to its craft
// and storing the answer in the task's avoidObj (+0x7C). That scan walks the
// whole object list and is a third of AttackTask's cost (0.27 of 0.75 ms a
// frame at 80 craft), but the answer is read only by DoGoto, DoFollow and
// UpdateSpecial, and most combat states call none of them that frame.
//
// OPENSHIM_AI_LAZY_NEAREST=1 defers the scan: the prolog call stores null and
// remembers its arguments, and the scan runs with those same arguments when
// one of the three readers is about to run. Exactness rests on three facts,
// checked against the GOG image (see
// reverse_engineering/attacktask_exact_optimisation_20261021.md):
//  - every path from DoState's entry to a reader passes the prolog call;
//  - avoidObj is read only by those three UnitTask methods, and every call
//    of them on an AttackTask is one of the five sites patched here, all
//    inside DoState, so an unresolved null is never read;
//  - NearestVehicle is pure (no RNG, no writes), and nothing between the
//    prolog and DoGoto/DoFollow moves an object or edits the object list.
// UpdateSpecial runs after UpdateWeapon has fired, so a call whose task has a
// special weapon (+0xB8, the only case where UpdateSpecial reads avoidObj)
// keeps the stock eager scan.
//
// Laziness is SinglePlayer-tier: it stands down in a network game.
// OPENSHIM_AI_LAZY_NEAREST=verify keeps the stock eager scan and re-runs it
// at every reader, counting answers that differ, to test the third fact live.
namespace BZROpenShim::Hooks
{
    namespace
    {
        using FnNearestVehicle = void*(__cdecl*)(void* craft, const void* position);

        enum class LazyNearestMode
        {
            Off,
            Lazy,
            Verify,
        };

        enum ReaderSite
        {
            kReaderDoGoto,
            kReaderDoFollow,
            kReaderUpdateSpecial,
            kReaderSiteCount,
        };
        // The thunks push these as literals.
        static_assert(kReaderDoGoto == 0 && kReaderDoFollow == 1 && kReaderUpdateSpecial == 2,
                      "reader site numbering is baked into the thunks");

        constexpr size_t kTaskAvoidObjOffset = 0x7C;
        constexpr size_t kTaskSpecialWeaponOffset = 0xB8;
        constexpr ULONGLONG kReportIntervalMs = 5000;

        LazyNearestMode g_Mode = LazyNearestMode::Off;
        std::atomic<bool> g_LazyActive{ false };
        bool g_Installed = false;

        uintptr_t g_NearestVehicleAddr = 0;
        uintptr_t g_DoGotoAddr = 0;
        uintptr_t g_DoFollowAddr = 0;
        uintptr_t g_UpdateSpecialAddr = 0;

        // DoState is not re-entrant and runs on the game thread only, so one
        // record is enough: the prolog arguments of the call in progress.
        struct PendingScan
        {
            uint8_t* task;
            void* craft;
            const void* position;
        };
        PendingScan g_Pending = {};

        struct Counters
        {
            unsigned long eager;
            unsigned long deferred;
            unsigned long resolved[kReaderSiteCount];
            unsigned long verified;
            unsigned long mismatched[kReaderSiteCount];
        };
        Counters g_Counters = {};
        ULONGLONG g_WindowStartMs = 0;

        void* ReadTaskPointer(const uint8_t* task, size_t offset)
        {
            void* value = nullptr;
            std::memcpy(&value, task + offset, sizeof(value));
            return value;
        }

        void MaybeReport()
        {
            const ULONGLONG now = GetTickCount64();
            if (!g_WindowStartMs)
                g_WindowStartMs = now;
            if (now - g_WindowStartMs < kReportIntervalMs)
                return;
            const Counters& c = g_Counters;
            if (g_Mode == LazyNearestMode::Verify)
            {
                Log(L"[AILAZY] verify window=%llums prologs=%lu checks=%lu mismatches goto=%lu follow=%lu special=%lu\n",
                    now - g_WindowStartMs, c.eager, c.verified,
                    c.mismatched[kReaderDoGoto], c.mismatched[kReaderDoFollow],
                    c.mismatched[kReaderUpdateSpecial]);
            }
            else
            {
                Log(L"[AILAZY] window=%llums eager=%lu deferred=%lu resolved goto=%lu follow=%lu special=%lu\n",
                    now - g_WindowStartMs, c.eager, c.deferred,
                    c.resolved[kReaderDoGoto], c.resolved[kReaderDoFollow],
                    c.resolved[kReaderUpdateSpecial]);
            }
            g_Counters = {};
            g_WindowStartMs = now;
        }

        // Replaces the prolog's call; its return value is what DoState
        // stores in avoidObj.
        void* __cdecl NearestVehicleProlog(void* craft, const void* position, uint8_t* task)
        {
            MaybeReport();
            const FnNearestVehicle nearest = reinterpret_cast<FnNearestVehicle>(g_NearestVehicleAddr);
            if (g_Mode == LazyNearestMode::Lazy &&
                g_LazyActive.load(std::memory_order_relaxed) &&
                !ReadTaskPointer(task, kTaskSpecialWeaponOffset))
            {
                g_Pending = { task, craft, position };
                ++g_Counters.deferred;
                return nullptr;
            }
            ++g_Counters.eager;
            g_Pending = g_Mode == LazyNearestMode::Verify
                            ? PendingScan{ task, craft, position }
                            : PendingScan{};
            return nearest(craft, position);
        }

        void __cdecl BeforeAvoidObjReader(uint8_t* task, int site)
        {
            if (!task || task != g_Pending.task)
                return;
            const FnNearestVehicle nearest = reinterpret_cast<FnNearestVehicle>(g_NearestVehicleAddr);
            if (g_Mode == LazyNearestMode::Verify)
            {
                ++g_Counters.verified;
                if (nearest(g_Pending.craft, g_Pending.position) !=
                    ReadTaskPointer(task, kTaskAvoidObjOffset))
                {
                    ++g_Counters.mismatched[site];
                }
                return;
            }
            // UpdateSpecial reads avoidObj only with a special weapon, which
            // the prolog already sent down the eager path.
            if (site == kReaderUpdateSpecial && !ReadTaskPointer(task, kTaskSpecialWeaponOffset))
                return;
            void* value = nearest(g_Pending.craft, g_Pending.position);
            std::memcpy(task + kTaskAvoidObjOffset, &value, sizeof(value));
            ++g_Counters.resolved[site];
            g_Pending = {};
        }

        // The prolog call site pushes (position, craft) and keeps the task at
        // [ebp-4] of DoState's frame (the verified bytes before the call).
        __declspec(naked) void NearestVehiclePrologThunk()
        {
            __asm
            {
                mov eax, [ebp - 4]
                push eax                        // task
                push dword ptr [esp + 0x0C]     // position
                push dword ptr [esp + 0x0C]     // craft
                call NearestVehicleProlog
                add esp, 0x0C
                ret
            }
        }

        // Reader call sites: thiscall, task in ecx, no stack arguments.
        __declspec(naked) void DoGotoThunk()
        {
            __asm
            {
                push ecx
                push 0                   // kReaderDoGoto
                push ecx
                call BeforeAvoidObjReader
                add esp, 8
                pop ecx
                jmp dword ptr [g_DoGotoAddr]
            }
        }

        __declspec(naked) void DoFollowThunk()
        {
            __asm
            {
                push ecx
                push 1                   // kReaderDoFollow
                push ecx
                call BeforeAvoidObjReader
                add esp, 8
                pop ecx
                jmp dword ptr [g_DoFollowAddr]
            }
        }

        __declspec(naked) void UpdateSpecialThunk()
        {
            __asm
            {
                push ecx
                push 2                   // kReaderUpdateSpecial
                push ecx
                call BeforeAvoidObjReader
                add esp, 8
                pop ecx
                jmp dword ptr [g_UpdateSpecialAddr]
            }
        }

        LazyNearestMode ReadMode()
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_AI_LAZY_NEAREST", value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return LazyNearestMode::Off;
            if (_stricmp(value, "verify") == 0)
                return LazyNearestMode::Verify;
            if (strcmp(value, "1") == 0 || _stricmp(value, "on") == 0 || _stricmp(value, "true") == 0)
                return LazyNearestMode::Lazy;
            return LazyNearestMode::Off;
        }
    }

    void RefreshAttackTaskLazyNearestState()
    {
        g_LazyActive.store(g_Installed && g_Mode == LazyNearestMode::Lazy && IsSinglePlayerSession(),
                           std::memory_order_relaxed);
    }

    void InstallAttackTaskLazyNearestIfRequested()
    {
        static bool s_done = false;
        if (s_done)
            return;
        s_done = true;
        g_Mode = ReadMode();
        if (g_Mode == LazyNearestMode::Off)
            return;

        uint32_t nearest = 0, doGoto = 0, doFollow = 0, updateSpecial = 0;
        uint32_t prologSite = 0, gotoA = 0, gotoB = 0, gotoC = 0, followSite = 0, specialSite = 0;
        const HookEngine::EngineRow rows[] = {
            { "UnitTaskNearestVehicle", &nearest },
            { "UnitTaskDoGoto", &doGoto },
            { "UnitTaskDoFollow", &doFollow },
            { "UnitTaskUpdateSpecial", &updateSpecial },
            { "AttackTaskNearestVehicleCall", &prologSite },
            { "AttackTaskDoGotoCallA", &gotoA },
            { "AttackTaskDoGotoCallB", &gotoB },
            { "AttackTaskDoGotoCallC", &gotoC },
            { "AttackTaskDoFollowCall", &followSite },
            { "AttackTaskUpdateSpecialCall", &specialSite },
        };
        if (!HookEngine::BindEngineRows("AttackTask lazy NearestVehicle", rows))
            return;
        g_NearestVehicleAddr = nearest;
        g_DoGotoAddr = doGoto;
        g_DoFollowAddr = doFollow;
        g_UpdateSpecialAddr = updateSpecial;

        // Each row starts at the instruction before its call: the prolog row
        // at "mov ecx,[ebp-4]; mov edx,[ecx+0x10]; push edx", the reader rows
        // at "mov ecx,[ebp-4]".
        struct Site
        {
            uintptr_t call;
            uintptr_t stock;
            uintptr_t thunk;
        };
        const Site sites[] = {
            // Readers first: until the prolog is redirected nothing is pending,
            // so a reader thunk alone changes nothing.
            { gotoA + 3u, doGoto, reinterpret_cast<uintptr_t>(&DoGotoThunk) },
            { gotoB + 3u, doGoto, reinterpret_cast<uintptr_t>(&DoGotoThunk) },
            { gotoC + 3u, doGoto, reinterpret_cast<uintptr_t>(&DoGotoThunk) },
            { followSite + 3u, doFollow, reinterpret_cast<uintptr_t>(&DoFollowThunk) },
            { specialSite + 3u, updateSpecial, reinterpret_cast<uintptr_t>(&UpdateSpecialThunk) },
            { prologSite + 7u, nearest, reinterpret_cast<uintptr_t>(&NearestVehiclePrologThunk) },
        };
        size_t redirected = 0;
        for (; redirected < _countof(sites); ++redirected)
        {
            if (!RedirectCallTarget(sites[redirected].call, sites[redirected].stock, sites[redirected].thunk))
                break;
        }
        if (redirected != _countof(sites))
        {
            for (size_t i = redirected; i-- > 0;)
                RedirectCallTarget(sites[i].call, sites[i].thunk, sites[i].stock);
            Log(L"[AILAZY] call site 0x%08X did not match; restored %u site(s), stock kept\n",
                static_cast<uint32_t>(sites[redirected].call), static_cast<unsigned>(redirected));
            return;
        }
        g_Installed = true;
        RefreshAttackTaskLazyNearestState();
        if (g_Mode == LazyNearestMode::Verify)
            Log(L"[AILAZY] AttackTask NearestVehicle: verify (stock eager scan, re-checked at each reader)\n");
        else
            Log(L"[AILAZY] AttackTask NearestVehicle: lazy (single-player gate %hs)\n",
                g_LazyActive.load(std::memory_order_relaxed) ? "open" : "closed");
    }
}
