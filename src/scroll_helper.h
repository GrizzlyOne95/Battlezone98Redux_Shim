// scroll_helper.h / scroll_helper.cpp
// BZR Open Shim - scroll state helper
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from HOPFIX analysis notes and validated against the game
// executable.
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
#include <cstring>
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
    inline void (*g_BZRFn_MapListFixSupport1)() = nullptr;
    inline void* g_HopFix3Context = nullptr;
    inline int32_t g_SavedScrollState = 0;
    inline bool g_HaveSavedScrollState = false;

    // Global map list object pointer (hop-fix 2)
    inline void**   g_MapListObject     = nullptr;

    // BZR.exe function pointer for hop-fix 1 indirect call
    inline void (*g_BZRFnPtr_HopFix1)() = nullptr;

    // BZR.exe function pointer for hop-fix 2 internal call
    inline void (*g_BZRFnPtr_HopFix2)() = nullptr;
    inline void (*g_BZRFnPtr_HopFix3Step)() = nullptr;

    // Steam build uses different internal addresses for scroll helpers.
    // When false, HopFix3 will skip scroll-restore helpers entirely.
    inline bool g_EnableScrollRestore = true;

    // Saved map-list selection (clean-room replacement for DAT_1002A1C8 / 1002A1EC)
    inline int32_t g_SavedMapIndex = -1;
    inline char g_SavedMapName[256] = {};
    inline uint32_t g_SavedMapNameLen = 0;
    inline volatile long g_MapRefreshTraceSequence = 0;

    inline bool TryReadI32(const void* p, int32_t& out);
    inline void __cdecl TraceMapRefreshFrame(const wchar_t* tag, void* frame_base);
    inline void __cdecl TraceMapRefreshContext(const wchar_t* tag, void* this_ptr);

    inline bool IsMapRefreshTraceEnabled()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            // Default-on for current Steam map refresh debugging; callers can
            // still disable with OPENSHIM_TRACE_MAP_REFRESH=0.
            s_cached = 1;
            char value[8] = {};
            DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_MAP_REFRESH", value, static_cast<DWORD>(sizeof(value)));
            if (len > 0 && len < sizeof(value))
            {
                s_cached = (value[0] != '0') ? 1 : 0;
            }
            else
            {
                ZeroMemory(value, sizeof(value));
                len = GetEnvironmentVariableA("OPENSHIM_TRACE_STEAM_MAP_REFRESH", value, static_cast<DWORD>(sizeof(value)));
                if (len > 0 && len < sizeof(value))
                    s_cached = (value[0] != '0') ? 1 : 0;
            }
        }
        return s_cached != 0;
    }

    inline uint32_t NextMapRefreshTraceSequence()
    {
        return static_cast<uint32_t>(InterlockedIncrement(&g_MapRefreshTraceSequence));
    }

    inline void TraceMapRefreshPhase(
        const wchar_t* phase,
        void* ptr0 = nullptr,
        void* ptr1 = nullptr,
        int32_t value0 = 0,
        int32_t value1 = 0)
    {
        if (!IsMapRefreshTraceEnabled())
            return;

        const uint32_t seq = NextMapRefreshTraceSequence();
        Log(L"[MAPTRACE] #%u phase=%ls ptr0=0x%08X ptr1=0x%08X value0=%d value1=%d savedIdx=%d savedState=%d haveSaved=%d savedName=%hs\n",
            seq,
            phase ? phase : L"<null>",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr0)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr1)),
            value0,
            value1,
            g_SavedMapIndex,
            g_SavedScrollState,
            g_HaveSavedScrollState ? 1 : 0,
            g_SavedMapNameLen ? g_SavedMapName : "");
    }

    inline bool TryReadPtr(const void* p, void*& out)
    {
        __try
        {
            out = *reinterpret_cast<void* const*>(p);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out = nullptr;
            return false;
        }
    }

    inline bool TryReadU32(const void* p, uint32_t& out)
    {
        __try
        {
            out = *reinterpret_cast<const volatile uint32_t*>(p);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out = 0;
            return false;
        }
    }

    inline const char* ResolveEntryString(const uint8_t* entry, uint32_t& out_len)
    {
        out_len = 0;
        if (!entry) return nullptr;

        uint32_t len = 0;
        uint32_t cap = 0;
        if (!TryReadU32(entry + 0x10, len)) return nullptr;
        if (!TryReadU32(entry + 0x14, cap)) return nullptr;

        const char* src = reinterpret_cast<const char*>(entry);
        if (cap > 0x0F)
        {
            void* ptr = nullptr;
            if (!TryReadPtr(entry, ptr)) return nullptr;
            src = reinterpret_cast<const char*>(ptr);
        }

        out_len = len;
        return src;
    }

    inline void SetSavedMapName(const char* value, uint32_t len)
    {
        if (!value || len == 0)
        {
            g_SavedMapName[0] = '\0';
            g_SavedMapNameLen = 0;
            return;
        }

        const uint32_t copyLen = (len >= sizeof(g_SavedMapName))
            ? (sizeof(g_SavedMapName) - 1)
            : len;
        memcpy(g_SavedMapName, value, copyLen);
        g_SavedMapName[copyLen] = '\0';
        g_SavedMapNameLen = copyLen;
    }

    inline void SetSavedMapNameLiteral(const char* value)
    {
        SetSavedMapName(value, value ? static_cast<uint32_t>(strlen(value)) : 0);
    }

    // -----------------------------------------------------------------------
    // Hop-Fix 1 helper: capture selected entry + index.
    // Mirrors the reference patch semantics in clean-room form.
    // ECX = map list context pointer.
    // -----------------------------------------------------------------------
    extern "C" inline void __fastcall SaveMapListSelection(void* ctx)
    {
        if (!ctx) return;

        static int s_logBudget = 6;
        if (IsMapRefreshTraceEnabled())
            TraceMapRefreshContext(L"SaveMapListSelection_enter", ctx);
        uint8_t* base = reinterpret_cast<uint8_t*>(ctx);

        // Resolve list root at [ctx + 0x1C8]
        void* listRootRaw = nullptr;
        if (!TryReadPtr(base + 0x1C8, listRootRaw) || !listRootRaw) return;
        void** listRoot = reinterpret_cast<void**>(listRootRaw);

        void* beginRaw = nullptr;
        void* endRaw = nullptr;
        if (!TryReadPtr(listRoot, beginRaw) || !beginRaw) return;
        if (!TryReadPtr(listRoot + 1, endRaw) || !endRaw) return;

        uint8_t* begin = reinterpret_cast<uint8_t*>(beginRaw);
        uint8_t* end = reinterpret_cast<uint8_t*>(endRaw);
        if (end < begin) return;
        const int32_t entryCount = static_cast<int32_t>((end - begin) / 0x18);
        if (entryCount <= 0) return;

        // Saved index from [listRoot[0x0B] + 0x150]
        int32_t savedIndex = -1;
        __try
        {
            uint8_t* listState = reinterpret_cast<uint8_t*>(listRoot[0x0B]);
            if (listState)
                TryReadI32(listState + 0x150, savedIndex);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            savedIndex = -1;
        }
        g_SavedMapIndex = savedIndex;

        // Selected entry index from [ctx + 0x17C] + 0x14C
        void* ctx17c = nullptr;
        if (!TryReadPtr(base + 0x17C, ctx17c) || !ctx17c) return;
        int32_t selIndex = 0;
        if (!TryReadI32(reinterpret_cast<uint8_t*>(ctx17c) + 0x14C, selIndex))
            return;

        // On Steam, ctx17c+0x14C often remains at the first entry while the
        // actual selected/visible map index advances via listState+0x150.
        // Prefer the latter when it points at a valid entry so the saved name
        // matches the same row we later restore.
        int32_t entryIndex = -1;
        if (savedIndex >= 0 && savedIndex < entryCount)
            entryIndex = savedIndex;
        else if (selIndex >= 0 && selIndex < entryCount)
            entryIndex = selIndex;
        else
            return;

        uint8_t* entry = begin + (entryIndex * 0x18);
        uint32_t entryLen = 0;
        const char* entryStr = ResolveEntryString(entry, entryLen);
        if (!entryStr || entryLen == 0) return;

        const uint32_t copyLen = (entryLen >= sizeof(g_SavedMapName)) ? (sizeof(g_SavedMapName) - 1) : entryLen;
        __try
        {
            SetSavedMapName(entryStr, copyLen);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            g_SavedMapName[0] = '\0';
            g_SavedMapNameLen = 0;
        }

        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[HOP1] saved index=%d sel=%d entry=%d name=%hs\n",
                g_SavedMapIndex, selIndex, entryIndex, g_SavedMapName);
        }
        if (IsMapRefreshTraceEnabled())
        {
            TraceMapRefreshPhase(L"SelectionSaved", ctx, ctx17c, g_SavedMapIndex, entryIndex);
            TraceMapRefreshContext(L"SaveMapListSelection_exit", ctx);
        }
    }

    // -----------------------------------------------------------------------
    // Hop-Fix 2 helper: reselect entry by saved name.
    // Mirrors the reference patch semantics in clean-room form.
    // ECX = map list object (this-ptr).
    // -----------------------------------------------------------------------
    extern "C" inline void __fastcall RestoreMapListSelection(void* this_ptr)
    {
        if (!this_ptr) return;
        if (IsMapRefreshTraceEnabled())
            TraceMapRefreshContext(L"RestoreMapListSelection_enter", this_ptr);

        if (g_SavedMapNameLen == 0)
            SetSavedMapNameLiteral("All Maps");

        // Resolve list root at [this + 0x1C8]
        uint8_t* base = reinterpret_cast<uint8_t*>(this_ptr);
        void* listRootRaw = nullptr;
        if (!TryReadPtr(base + 0x1C8, listRootRaw) || !listRootRaw) return;
        void** listRoot = reinterpret_cast<void**>(listRootRaw);

        void* beginRaw = nullptr;
        void* endRaw = nullptr;
        if (!TryReadPtr(listRoot, beginRaw)) return;
        if (!TryReadPtr(listRoot + 1, endRaw)) return;
        if (!beginRaw || !endRaw) return;

        uint8_t* begin = reinterpret_cast<uint8_t*>(beginRaw);
        uint8_t* end = reinterpret_cast<uint8_t*>(endRaw);
        if (end < begin) return;
        const int32_t entryCount = static_cast<int32_t>((end - begin) / 0x18);
        if (entryCount <= 0)
            return;

        int32_t foundIndex = -1;
        const int32_t savedIndex = g_SavedMapIndex;

        if (savedIndex >= 0 && savedIndex < entryCount)
        {
            uint8_t* entry = begin + (savedIndex * 0x18);
            uint32_t entryLen = 0;
            const char* entryStr = ResolveEntryString(entry, entryLen);
            if (entryStr && entryLen == g_SavedMapNameLen &&
                memcmp(entryStr, g_SavedMapName, entryLen) == 0)
            {
                foundIndex = savedIndex;
            }
        }

        if (foundIndex < 0)
        {
            uint8_t* entry = begin;
            for (; entry != end; entry += 0x18)
            {
                uint32_t entryLen = 0;
                const char* entryStr = ResolveEntryString(entry, entryLen);
                if (!entryStr || entryLen == 0) continue;

                if (entryLen == g_SavedMapNameLen &&
                    memcmp(entryStr, g_SavedMapName, entryLen) == 0)
                {
                    foundIndex = static_cast<int32_t>((entry - begin) / 0x18);
                    break;
                }
            }
        }

        int32_t targetIndex = 0;
        if (foundIndex >= 0)
        {
            targetIndex = foundIndex;
        }
        else if (savedIndex >= 0)
        {
            targetIndex = (savedIndex < entryCount) ? savedIndex : (entryCount - 1);
        }

        if (!g_BZRFnPtr_HopFix2) return;

        void* selectThis = nullptr;
        if (!TryReadPtr(base + 0x17C, selectThis) || !selectThis)
            return;

        void (*fn)() = g_BZRFnPtr_HopFix2;
        __try
        {
            __asm
            {
                mov ecx, selectThis
                push targetIndex
                call fn
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[WARN] RestoreMapListSelection call failed\n");
        }
        if (IsMapRefreshTraceEnabled())
        {
            TraceMapRefreshPhase(L"SelectionRestored", this_ptr, selectThis, targetIndex, foundIndex);
            Log(L"[MAPTRACE] RestoreMapListSelection targetIndex=%d foundIndex=%d savedIndex=%d this=0x%08X\n",
                targetIndex,
                foundIndex,
                savedIndex,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)));
            TraceMapRefreshContext(L"RestoreMapListSelection_exit", this_ptr);
        }
    }

    // -----------------------------------------------------------------------
    // Hop-Fix 3 helper: restore visible row index by replaying list-step calls.
    // Mirrors the reference patch semantics in clean-room form.
    // ECX = map list context pointer (frame-local).
    // -----------------------------------------------------------------------
    extern "C" inline void __fastcall RestoreMapListVisibleIndex(void* ctx)
    {
        if (!ctx) return;
        if (!g_BZRFnPtr_HopFix3Step) return;
        if (IsMapRefreshTraceEnabled())
            TraceMapRefreshContext(L"RestoreMapListVisibleIndex_enter", ctx);

        int32_t saved = g_SavedMapIndex;
        if (saved < 0)
            return;

        uint8_t* base = reinterpret_cast<uint8_t*>(ctx);
        void* listRootRaw = nullptr;
        void* listInnerRaw = nullptr;
        int32_t spanStart = 0;
        int32_t spanEnd = 0;
        int32_t count = 0;
        if (!TryReadPtr(base + 0x1C8, listRootRaw) || !listRootRaw)
            goto done;

        if (!TryReadPtr(reinterpret_cast<uint8_t*>(listRootRaw) + 0x2C, listInnerRaw) || !listInnerRaw)
            goto done;

        if (!TryReadI32(reinterpret_cast<uint8_t*>(listInnerRaw) + 0x168, spanStart))
            goto done;
        if (!TryReadI32(reinterpret_cast<uint8_t*>(listInnerRaw) + 0x16C, spanEnd))
            goto done;

        count = (spanEnd - spanStart) / 0x1C;
        if (saved >= count)
            goto done;

        if (saved > 0)
        {
            void (*fn)() = g_BZRFnPtr_HopFix3Step;
            for (int32_t i = 0; i < saved; ++i)
            {
                __try { fn(); }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[WARN] RestoreMapListVisibleIndex step failed\n");
                    break;
                }
            }
        }

    done:
        if (IsMapRefreshTraceEnabled())
        {
            TraceMapRefreshPhase(L"VisibleRowRestoreDone", ctx, listInnerRaw, saved, count);
            Log(L"[MAPTRACE] RestoreMapListVisibleIndex done saved=%d count=%d ctx=0x%08X\n",
                saved,
                count,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ctx)));
            TraceMapRefreshContext(L"RestoreMapListVisibleIndex_exit", ctx);
        }
        g_SavedMapIndex = -1;
    }

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
        if (IsMapRefreshTraceEnabled())
        {
            TraceMapRefreshPhase(L"ScrollUpdateHelper", this_ptr, g_HopFix3Context, scroll_delta, static_cast<int32_t>(state));
            Log(L"[MAPTRACE] ScrollUpdateHelper delta=%d this=0x%08X state=%u hopCtx=0x%08X\n",
                scroll_delta,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)),
                state,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_HopFix3Context)));
            TraceMapRefreshContext(L"ScrollUpdateHelper", this_ptr);
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
            if (!g_BZRFn_ScrollUp)
                return 0;

            auto fnUp = g_BZRFn_ScrollUp;
            bool handled = false;
            for (int i = 0; i < rows; ++i)
            {
                __try
                {
                    // Steam's UI scroll helpers behave like plain callbacks here;
                    // forcing ECX causes an immediate fault in the manual-refresh path.
                    fnUp();
                    handled = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[WARN] ScrollUpdateHelper ScrollUp fault (row %d)\n", i);
                    return handled ? 1 : 0;
                }
            }
            return handled ? 1 : 0;
        }
        else if (scroll_delta > 0)
        {
            int rows = (scroll_delta - 1) / 120 + 1;
            if (rows > kMaxRows) rows = kMaxRows;
            Log(L"[SCROLL] Down: delta=%d, rows=%d\n", scroll_delta, rows);
            if (!g_BZRFn_ScrollDown)
                return 0;

            auto fnDown = g_BZRFn_ScrollDown;
            bool handled = false;
            for (int i = 0; i < rows; ++i)
            {
                __try
                {
                    fnDown();
                    handled = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[WARN] ScrollUpdateHelper ScrollDown fault (row %d)\n", i);
                    return handled ? 1 : 0;
                }
            }
            return handled ? 1 : 0;
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

    inline void __cdecl TraceMapRefreshFrame(const wchar_t* tag, void* frame_base)
    {
        if (!IsMapRefreshTraceEnabled() || !frame_base)
            return;

        const uint32_t seq = NextMapRefreshTraceSequence();
        auto* base = reinterpret_cast<uint8_t*>(frame_base);
        void* parent = nullptr;
        void* arg8 = nullptr;
        void* m4 = nullptr;
        void* m8 = nullptr;
        void* m44 = nullptr;
        void* ma4 = nullptr;
        void* globalMapObj = nullptr;
        int32_t d94 = 0;
        int32_t d98 = 0;
        int32_t da4 = 0;

        TryReadPtr(base + 0x00, parent);
        TryReadPtr(base + 0x08, arg8);
        TryReadPtr(base - 0x04, m4);
        TryReadPtr(base - 0x08, m8);
        TryReadPtr(base - 0x44, m44);
        TryReadPtr(base - 0xA4, ma4);
        TryReadI32(base - 0x94, d94);
        TryReadI32(base - 0x98, d98);
        TryReadI32(base - 0xA4, da4);

        __try
        {
            if (g_MapListObject)
                globalMapObj = *g_MapListObject;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            globalMapObj = nullptr;
        }

        Log(L"[MAPTRACE] #%u %ls frame=0x%08X parent=0x%08X arg8=0x%08X m4=0x%08X m8=0x%08X m44=0x%08X ma4=0x%08X d94=%d d98=%d da4=%d savedIdx=%d savedState=%d haveSaved=%d mapObj=0x%08X\n",
            seq,
            tag ? tag : L"<null>",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(frame_base)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(arg8)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m4)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m8)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m44)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ma4)),
            d94,
            d98,
            da4,
            g_SavedMapIndex,
            g_SavedScrollState,
            g_HaveSavedScrollState ? 1 : 0,
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(globalMapObj)));
        if (g_SavedMapNameLen > 0)
        {
            Log(L"[MAPTRACE] #%u %ls savedName=%hs len=%u\n",
                seq,
                tag ? tag : L"<null>",
                g_SavedMapName,
                g_SavedMapNameLen);
        }
    }

    inline void __cdecl TraceMapRefreshContext(const wchar_t* tag, void* this_ptr)
    {
        if (!IsMapRefreshTraceEnabled() || !this_ptr)
            return;

        const uint32_t seq = NextMapRefreshTraceSequence();
        auto* base = reinterpret_cast<uint8_t*>(this_ptr);
        void* ctx17c = nullptr;
        void* listRootRaw = nullptr;
        void* beginRaw = nullptr;
        void* endRaw = nullptr;
        void* listInnerRaw = nullptr;
        int32_t selIndex = 0;
        int32_t spanStart = 0;
        int32_t spanEnd = 0;
        uint32_t scrollState = 0;
        const bool hasScrollState = QueryScrollStateWithContext(this_ptr, scrollState);

        TryReadPtr(base + 0x17C, ctx17c);
        TryReadPtr(base + 0x1C8, listRootRaw);
        if (ctx17c)
            TryReadI32(reinterpret_cast<uint8_t*>(ctx17c) + 0x14C, selIndex);

        if (listRootRaw)
        {
            auto* listRoot = reinterpret_cast<void**>(listRootRaw);
            TryReadPtr(listRoot, beginRaw);
            TryReadPtr(listRoot + 1, endRaw);
            TryReadPtr(reinterpret_cast<uint8_t*>(listRootRaw) + 0x2C, listInnerRaw);
        }

        if (listInnerRaw)
        {
            TryReadI32(reinterpret_cast<uint8_t*>(listInnerRaw) + 0x168, spanStart);
            TryReadI32(reinterpret_cast<uint8_t*>(listInnerRaw) + 0x16C, spanEnd);
        }

        Log(L"[MAPTRACE] #%u %ls this=0x%08X ctx17c=0x%08X listRoot=0x%08X begin=0x%08X end=0x%08X inner=0x%08X sel=%d spanStart=%d spanEnd=%d scrollState=%u haveState=%d\n",
            seq,
            tag ? tag : L"<null>",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ctx17c)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listRootRaw)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(beginRaw)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(endRaw)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listInnerRaw)),
            selIndex,
            spanStart,
            spanEnd,
            scrollState,
            hasScrollState ? 1 : 0);
    }

    inline void __cdecl CaptureScrollStateFromContext(void* this_ptr)
    {
        static int s_logBudget = 10;
        uint32_t state = 0;
        if (!QueryScrollStateWithContext(this_ptr, state))
            return;
        g_SavedScrollState = static_cast<int32_t>(state);
        g_HaveSavedScrollState = true;
        if (IsMapRefreshTraceEnabled())
        {
            TraceMapRefreshContext(L"CaptureScrollState", this_ptr);
            TraceMapRefreshPhase(L"ScrollStateCaptured", this_ptr, nullptr, g_SavedScrollState, static_cast<int32_t>(state));
            Log(L"[MAPTRACE] capture savedScrollState=%d this=0x%08X\n",
                g_SavedScrollState,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this_ptr)));
        }
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

    // Selects HopFix2 this-pointer using the reference patch's global map object.
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
