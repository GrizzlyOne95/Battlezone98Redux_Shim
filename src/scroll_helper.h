// scroll_helper.h / scroll_helper.cpp
// BZR Open Shim - scroll state helper
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from HOPFIX_ANALYSIS.md "Support Function (0x1000cd80)"
// and bzcp_hopfix_decompiled.txt.
//
// The original algorithm divides the scroll delta by 120 (one row height)
// to compute how many rows to scroll, then calls the BZR.exe scroll-up or
// scroll-down function that many times.

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <cstdint>
#include "patcher.h"

namespace BZROpenShim
{
    // -----------------------------------------------------------------------
    // BZR.exe scroll function pointers - resolved at patch time.
    // These point into BZR.exe's scroll-up and scroll-down handlers.
    // -----------------------------------------------------------------------
    inline void (*g_BZRFn_ScrollUp)()   = nullptr;
    inline void (*g_BZRFn_ScrollDown)() = nullptr;
    inline uint32_t (*g_BZRFn_GetScrollState)() = nullptr;
    inline void* g_HopFix3Context = nullptr;
    inline int32_t g_SavedScrollState = 0;
    inline bool g_HaveSavedScrollState = false;

    // Global map list object pointer (hop-fix 2)
    inline void**   g_MapListObject     = nullptr;

    // BZR.exe function pointer for hop-fix 1 indirect call
    inline void (*g_BZRFnPtr_HopFix1)() = nullptr;

    // BZR.exe function pointer for hop-fix 2 internal call
    inline void (*g_BZRFnPtr_HopFix2)() = nullptr;

    // Steam build uses different internal addresses for scroll helpers.
    // When false, HopFix3 will skip scroll-restore helpers entirely.
    inline bool g_EnableScrollRestore = true;

    // -----------------------------------------------------------------------
    // ScrollUpdateHelper
    // Reconstructed from HOPFIX_ANALYSIS.md support function
    // Original algorithm:
    //   - get current scroll state; if 0, return 0
    //   - if delta < 0: rows = (-delta-1)/120+1, call scroll_up rows times
    //   - if delta > 0: rows = (delta-1)/120+1, call scroll_down rows times
    // -----------------------------------------------------------------------
    inline int32_t __fastcall ScrollUpdateHelper(int32_t scroll_delta)
    {
        void* this_ptr = g_HopFix3Context;
        if (!this_ptr && g_MapListObject)
        {
            __try { this_ptr = *g_MapListObject; }
            __except (EXCEPTION_EXECUTE_HANDLER) { this_ptr = nullptr; }
        }

        uint32_t state = 1;
        if (g_BZRFn_GetScrollState && this_ptr)
        {
            auto fnState = g_BZRFn_GetScrollState;
            __try
            {
                __asm
                {
                    mov ecx, this_ptr
                    call fnState
                    mov state, eax
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[WARN] ScrollUpdateHelper GetScrollState fault\n");
                return 0;
            }
            if (state == 0) return 0;
        }

        // Guard against bogus pointer-like deltas from uncertain stack reconstruction.
        // Large magnitudes here can trigger millions of scroll calls and crash in BZR.
        constexpr int32_t kMaxDeltaMagnitude = 4096;
        constexpr int32_t kMaxRows = 64;
        if (scroll_delta < -kMaxDeltaMagnitude || scroll_delta > kMaxDeltaMagnitude)
        {
            Log(L"[WARN] ScrollUpdateHelper rejected suspicious delta=%d\n", scroll_delta);
            return 0;
        }

        if (scroll_delta < 0)
        {
            int rows = ((-scroll_delta) - 1) / 120 + 1;
            if (rows > kMaxRows) rows = kMaxRows;
            Log(L"[SCROLL] Up: delta=%d, rows=%d\n", scroll_delta, rows);
            if (g_BZRFn_ScrollUp)
            {
                auto fnUp = g_BZRFn_ScrollUp;
                for (int i = 0; i < rows; ++i)
                {
                    __try
                    {
                        __asm
                        {
                            mov ecx, this_ptr
                            call fnUp
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        Log(L"[WARN] ScrollUpdateHelper ScrollUp fault (row %d)\n", i);
                        break;
                    }
                }
            }
            return 1;
        }
        else if (scroll_delta > 0)
        {
            int rows = (scroll_delta - 1) / 120 + 1;
            if (rows > kMaxRows) rows = kMaxRows;
            Log(L"[SCROLL] Down: delta=%d, rows=%d\n", scroll_delta, rows);
            if (g_BZRFn_ScrollDown)
            {
                auto fnDown = g_BZRFn_ScrollDown;
                for (int i = 0; i < rows; ++i)
                {
                    __try
                    {
                        __asm
                        {
                            mov ecx, this_ptr
                            call fnDown
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        Log(L"[WARN] ScrollUpdateHelper ScrollDown fault (row %d)\n", i);
                        break;
                    }
                }
            }
        }
        return 1;
    }

    inline int32_t Abs32(int32_t v)
    {
        return (v < 0) ? -v : v;
    }

    inline bool TryReadI32(const void* p, int32_t& out)
    {
        __try
        {
            out = *reinterpret_cast<const volatile int32_t*>(p);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out = 0;
            return false;
        }
    }

    inline bool QueryScrollStateWithContext(void* this_ptr, uint32_t& out_state)
    {
        if (!g_BZRFn_GetScrollState || !this_ptr)
            return false;

        auto fnState = g_BZRFn_GetScrollState;
        uint32_t state = 0;
        __try
        {
            __asm
            {
                mov ecx, this_ptr
                call fnState
                mov state, eax
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
        out_state = state;
        return true;
    }

    inline void __cdecl CaptureScrollStateFromContext(void* this_ptr)
    {
        static int s_logBudget = 10;
        uint32_t state = 0;
        if (!QueryScrollStateWithContext(this_ptr, state))
            return;
        g_SavedScrollState = static_cast<int32_t>(state);
        g_HaveSavedScrollState = true;
        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[REFRESH] captured scroll state=%u this=0x%08X\n",
                state,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)));
        }
    }

    inline int32_t __cdecl ConsumeSavedScrollDelta(void* this_ptr, int32_t fallback_delta)
    {
        // The probe's GetScrollState function address (0x007D3360) appears to be 
        // wrong for Steam, causing captured state to be garbage (pointer values).
        // However, HOP3 already correctly extracts scroll delta from the frame [EBP-0x94].
        // So we skip the restore and let HOP3's frame-based delta handle it.
        
        if (g_HaveSavedScrollState)
        {
            // Check if saved state looks valid (small positive number, not a pointer)
            if (g_SavedScrollState > 0 && g_SavedScrollState < 10000)
            {
                uint32_t current = 0;
                if (QueryScrollStateWithContext(this_ptr, current))
                {
                    int32_t delta = g_SavedScrollState - static_cast<int32_t>(current);
                    g_HaveSavedScrollState = false;
                    Log(L"[REFRESH] restore delta: saved=%d current=%u delta=%d\n",
                        g_SavedScrollState, current, delta);
                    return delta;
                }
            }
            Log(L"[REFRESH] skipping invalid captured state=%d (using frame delta=%d)\n", 
                g_SavedScrollState, fallback_delta);
            g_HaveSavedScrollState = false;
        }
        
        // Use the frame-based delta from HOP3 instead
        return fallback_delta;
    }

    // Attempt to reconstruct the intended HopFix3 scroll delta from frame locals.
    // Current evidence on Steam v2.2.301 shows EBP-0x94 as the stable delta field.
    inline int32_t __cdecl SelectHopFix3DeltaFromFrame(void* frame_base, int32_t fallback_delta)
    {
        static int s_logBudget = 6;

        struct Candidate { int32_t off; int32_t val; bool ok; };
        Candidate cands[] =
        {
            { -0xA4, 0, false }, { -0xA8, 0, false }, { -0xA0, 0, false },
            { -0x9C, 0, false }, { -0x98, 0, false }, { -0x94, 0, false },
            { -0x90, 0, false }, { -0x8C, 0, false }, { -0x88, 0, false },
            // Additional candidates for manual refresh
            { -0x80, 0, false }, { -0x7C, 0, false }, { -0x78, 0, false },
            { -0x74, 0, false }, { -0x70, 0, false }, { -0x6C, 0, false },
            { -0x68, 0, false }, { -0x64, 0, false }, { -0x60, 0, false },
        };

        auto base = reinterpret_cast<uint8_t*>(frame_base);
        for (auto& c : cands)
        {
            c.ok = TryReadI32(base + c.off, c.val);
        }

        int32_t chosen = fallback_delta;
        bool chosenFromHeuristic = false;

        // Primary candidate observed in runtime traces.
        if (cands[5].ok && cands[5].val != 0 && Abs32(cands[5].val) <= 4096)
        {
            chosen = cands[5].val; // EBP-0x94
            chosenFromHeuristic = true;
        }

        // Fallback: first sane candidate from the probe set.
        if (!chosenFromHeuristic)
        {
            for (const auto& c : cands)
            {
                if (!c.ok) continue;
                if (c.val == 0) continue;
                if (Abs32(c.val) <= 4096)
                {
                    chosen = c.val;
                    chosenFromHeuristic = true;
                    break;
                }
            }
        }

        // Last resort: look for larger values (more scrolled = larger position)
        if (!chosenFromHeuristic)
        {
            int32_t maxVal = 0;
            for (const auto& c : cands)
            {
                if (!c.ok) continue;
                if (c.val > maxVal && c.val < 50000)
                {
                    maxVal = c.val;
                }
            }
            if (maxVal > 0)
            {
                chosen = maxVal;
                chosenFromHeuristic = true;
            }
        }

        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[HOP3] frame=0x%08X fallback=%d chosen=%d (%hs)\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(frame_base)),
                fallback_delta,
                chosen,
                chosenFromHeuristic ? "heuristic" : "fallback");
            Log(L"[HOP3] cand -A4=%d -A8=%d -A0=%d -9C=%d -98=%d -94=%d -90=%d -8C=%d -88=%d\n",
                cands[0].val, cands[1].val, cands[2].val, cands[3].val, cands[4].val,
                cands[5].val, cands[6].val, cands[7].val, cands[8].val);
            Log(L"[HOP3] cand2 -80=%d -7C=%d -78=%d -74=%d -70=%d -6C=%d\n",
                cands[9].val, cands[10].val, cands[11].val, cands[12].val,
                cands[13].val, cands[14].val);
        }

        return chosen;
    }

    // Helper used by Trampoline_HopFix2 (C++ callable from asm)
    // Called with ECX = *g_MapListObject (the map list vtable ptr or this-ptr).
    // g_BZRFnPtr_HopFix2 is a __thiscall method; ECX must be set before call.
    // We pass the ecx value explicitly so the helper can set it up.
    inline void __cdecl HopFix2_Helper(void* this_ptr)
    {
        void* global_this = nullptr;
        __try
        {
            if (g_MapListObject)
                global_this = *g_MapListObject;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            global_this = nullptr;
        }

        Log(L"[HIT]  HopFix2_Helper this=0x%08X fn=0x%08X mapObjPtr=0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BZRFnPtr_HopFix2)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_MapListObject)));
        Log(L"[HIT]  HopFix2_Helper mapObjValue=0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(global_this)));
        if (!g_BZRFnPtr_HopFix2 || !this_ptr) return;

        __try
        {
            // Probe pointer readability before calling into game code.
            volatile uint32_t probe = *reinterpret_cast<volatile uint32_t*>(this_ptr);
            (void)probe;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[WARN] HopFix2_Helper invalid this_ptr: 0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)));
            return;
        }

        void (*fn)() = g_BZRFnPtr_HopFix2;
        __try
        {
            __asm
            {
                mov ecx, this_ptr
                call fn
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[WARN] HopFix2_Helper callee raised exception\n");
        }
    }

    // Selects HopFix2 this-pointer using the _bzcp-style global map object.
    // If unavailable, returns null and caller skips the helper call.
    inline void* __cdecl SelectHopFix2This(void* stack_this)
    {
        (void)stack_this;
        void* global_this = nullptr;
        __try
        {
            if (g_MapListObject)
                global_this = *g_MapListObject;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            global_this = nullptr;
        }

        return global_this;
    }

} // namespace BZROpenShim
