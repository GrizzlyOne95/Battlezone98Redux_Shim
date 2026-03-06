// scroll_helper.h
// BZR Open Shim - map list state helpers for the _bzcp.dll hop-fix pipeline
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from the Ghidra-confirmed _bzcp.dll helpers:
//   FUN_1000CAF0 - save selected entry + visible row
//   FUN_1000CB40 - restore selected entry after rebuild
//   FUN_1000CCA0 - replay native row-step calls to restore the viewport

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
    // BZR.exe entry points used by the hop-fix pipeline.
    inline void (*g_BZRFnPtr_HopFix1)() = nullptr;      // 0x005D4260
    inline void (*g_BZRFnPtr_HopFix2)() = nullptr;      // 0x007CAFA0
    inline void (*g_BZRFn_MapListStepDown)() = nullptr; // 0x007CB540
    inline void (*g_BZRFn_MapListRedraw)() = nullptr;   // 0x007A4260

    // BZR.exe globals used by the same pipeline.
    inline void** g_MapListObject = nullptr;      // 0x0094555C
    inline void** g_MapListScrollState = nullptr; // 0x00945578
    inline void** g_MapListRedrawState = nullptr; // 0x00945574

    inline int32_t g_SavedVisibleIndex = -1;
    inline char g_SavedSelectedEntry[260] = {};
    inline uint32_t g_SavedSelectedEntryLen = 0;

    struct GameString32
    {
        union
        {
            char inline_buffer[16];
            const char* heap_ptr;
        };
        uint32_t size;
        uint32_t capacity;
    };
    static_assert(sizeof(GameString32) == 24, "Unexpected MSVC x86 string layout");

    template <typename T>
    inline bool TryReadValue(const void* address, T& out)
    {
        __try
        {
            out = *reinterpret_cast<const volatile T*>(address);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            std::memset(&out, 0, sizeof(out));
            return false;
        }
    }

    inline bool TryCopyBytes(const void* src, void* dst, size_t len)
    {
        __try
        {
            std::memcpy(dst, src, len);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            std::memset(dst, 0, len);
            return false;
        }
    }

    inline bool TryGetListState(void* map_list_ctx, uintptr_t& list_state)
    {
        list_state = 0;
        if (!map_list_ctx)
            return false;
        return TryReadValue(reinterpret_cast<uint8_t*>(map_list_ctx) + 0x1C8, list_state) &&
               list_state != 0;
    }

    inline bool TryGetSelectionState(void* map_list_ctx, uintptr_t& selection_state)
    {
        selection_state = 0;
        if (!map_list_ctx)
            return false;
        return TryReadValue(reinterpret_cast<uint8_t*>(map_list_ctx) + 0x17C, selection_state) &&
               selection_state != 0;
    }

    inline bool TryGetEntrySpan(void* map_list_ctx, uint8_t*& begin, uint8_t*& end, uintptr_t& viewport)
    {
        begin = nullptr;
        end = nullptr;
        viewport = 0;

        uintptr_t list_state = 0;
        if (!TryGetListState(map_list_ctx, list_state))
            return false;

        uintptr_t begin_ptr = 0;
        uintptr_t end_ptr = 0;
        if (!TryReadValue(reinterpret_cast<void*>(list_state), begin_ptr) ||
            !TryReadValue(reinterpret_cast<uint8_t*>(list_state) + 0x04, end_ptr))
            return false;

        if (end_ptr < begin_ptr)
            return false;

        begin = reinterpret_cast<uint8_t*>(begin_ptr);
        end = reinterpret_cast<uint8_t*>(end_ptr);
        TryReadValue(reinterpret_cast<uint8_t*>(list_state) + 0x2C, viewport);
        return true;
    }

    inline bool TryGetSelectedIndex(void* map_list_ctx, int32_t& selected_index)
    {
        selected_index = -1;
        uintptr_t selection_state = 0;
        if (!TryGetSelectionState(map_list_ctx, selection_state))
            return false;
        return TryReadValue(reinterpret_cast<uint8_t*>(selection_state) + 0x14C, selected_index);
    }

    inline int32_t CountEntries(uint8_t* begin, uint8_t* end, size_t stride)
    {
        if (!begin || !end || end < begin || stride == 0)
            return 0;

        const size_t bytes = static_cast<size_t>(end - begin);
        if ((bytes % stride) != 0)
            return 0;

        return static_cast<int32_t>(bytes / stride);
    }

    inline bool TryReadEntryString(const void* entry_ptr, char* out, size_t out_cap, uint32_t& out_len)
    {
        out_len = 0;
        if (!entry_ptr || !out || out_cap == 0)
            return false;

        out[0] = '\0';

        GameString32 str = {};
        if (!TryCopyBytes(entry_ptr, &str, sizeof(str)))
            return false;

        if (str.size == 0)
            return true;
        if (str.size >= out_cap)
            return false;

        if (str.capacity > 0x0F)
        {
            if (!str.heap_ptr || !TryCopyBytes(str.heap_ptr, out, str.size))
                return false;
        }
        else
        {
            std::memcpy(out, str.inline_buffer, str.size);
        }

        out[str.size] = '\0';
        out_len = str.size;
        return true;
    }

    inline void __cdecl CallSelectEntry(void* selection_this, int32_t index)
    {
        if (!g_BZRFnPtr_HopFix2 || !selection_this)
            return;

        auto fn = g_BZRFnPtr_HopFix2;
        __try
        {
            __asm
            {
                mov ecx, selection_this
                mov eax, index
                push eax
                call fn
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[WARN] CallSelectEntry failed for this=0x%08X index=%d\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(selection_this)),
                index);
        }
    }

    inline void __cdecl StepMapListDownAndRedraw()
    {
        void* scroll_this = nullptr;
        void* redraw_holder = nullptr;
        void* redraw_this = nullptr;

        if (g_MapListScrollState)
            TryReadValue(g_MapListScrollState, scroll_this);
        if (g_MapListRedrawState)
        {
            if (TryReadValue(g_MapListRedrawState, redraw_holder) && redraw_holder)
                TryReadValue(redraw_holder, redraw_this);
        }

        auto fnDown = g_BZRFn_MapListStepDown;
        if (fnDown && scroll_this)
        {
            __try
            {
                __asm
                {
                    mov ecx, scroll_this
                    call fnDown
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[WARN] StepMapListDownAndRedraw step-down fault\n");
                return;
            }
        }

        auto fnRedraw = g_BZRFn_MapListRedraw;
        if (fnRedraw && redraw_this)
        {
            __try
            {
                __asm
                {
                    mov ecx, redraw_this
                    call fnRedraw
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[WARN] StepMapListDownAndRedraw redraw fault\n");
            }
        }
    }

    inline void __fastcall SaveMapListSelection(void* map_list_ctx)
    {
        static int s_logBudget = 10;

        g_SavedVisibleIndex = -1;
        g_SavedSelectedEntry[0] = '\0';
        g_SavedSelectedEntryLen = 0;

        if (!map_list_ctx)
            return;

        uint8_t* begin = nullptr;
        uint8_t* end = nullptr;
        uintptr_t viewport = 0;
        if (!TryGetEntrySpan(map_list_ctx, begin, end, viewport))
            return;

        if (viewport)
        {
            int32_t visible_index = -1;
            if (TryReadValue(reinterpret_cast<uint8_t*>(viewport) + 0x150, visible_index) &&
                visible_index >= 0)
            {
                g_SavedVisibleIndex = visible_index;
            }
        }

        int32_t selected_index = -1;
        if (!TryGetSelectedIndex(map_list_ctx, selected_index))
            return;

        const int32_t count = CountEntries(begin, end, 0x18);
        if (selected_index < 0 || selected_index >= count)
            return;

        if (!TryReadEntryString(begin + (selected_index * 0x18),
                                g_SavedSelectedEntry,
                                sizeof(g_SavedSelectedEntry),
                                g_SavedSelectedEntryLen))
        {
            g_SavedSelectedEntry[0] = '\0';
            g_SavedSelectedEntryLen = 0;
            return;
        }

        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[HOP1] saved index=%d visible=%d entry=%hs\n",
                selected_index,
                g_SavedVisibleIndex,
                g_SavedSelectedEntry);
        }
    }

    inline void __fastcall RestoreMapListSelection(void* map_list_ctx)
    {
        static int s_logBudget = 10;

        if (!map_list_ctx)
            return;

        uintptr_t selection_state = 0;
        if (!TryGetSelectionState(map_list_ctx, selection_state))
            return;

        uint8_t* begin = nullptr;
        uint8_t* end = nullptr;
        uintptr_t viewport = 0;
        if (!TryGetEntrySpan(map_list_ctx, begin, end, viewport))
            return;

        const int32_t count = CountEntries(begin, end, 0x18);
        if (count <= 0)
            return;

        int32_t selected_index = 0;
        bool matched = false;

        if (g_SavedSelectedEntryLen != 0)
        {
            char candidate[260] = {};
            uint32_t candidate_len = 0;
            for (int32_t i = 0; i < count; ++i)
            {
                if (!TryReadEntryString(begin + (i * 0x18), candidate, sizeof(candidate), candidate_len))
                    continue;
                if (candidate_len != g_SavedSelectedEntryLen)
                    continue;
                if (std::memcmp(candidate, g_SavedSelectedEntry, candidate_len) == 0)
                {
                    selected_index = i;
                    matched = true;
                    break;
                }
            }
        }

        CallSelectEntry(reinterpret_cast<void*>(selection_state), selected_index);

        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[HOP2] restore matched=%d index=%d entry=%hs\n",
                matched ? 1 : 0,
                selected_index,
                g_SavedSelectedEntryLen ? g_SavedSelectedEntry : "<first>");
        }
    }

    inline void __fastcall RestoreMapListVisibleIndex(void* map_list_ctx)
    {
        static int s_logBudget = 10;

        const int32_t saved_visible_index = g_SavedVisibleIndex;
        g_SavedVisibleIndex = -1;

        if (!map_list_ctx || saved_visible_index < 0)
            return;

        uint8_t* begin = nullptr;
        uint8_t* end = nullptr;
        uintptr_t viewport = 0;
        if (!TryGetEntrySpan(map_list_ctx, begin, end, viewport) || !viewport)
            return;

        uintptr_t rows_begin = 0;
        uintptr_t rows_end = 0;
        if (!TryReadValue(reinterpret_cast<uint8_t*>(viewport) + 0x168, rows_begin) ||
            !TryReadValue(reinterpret_cast<uint8_t*>(viewport) + 0x16C, rows_end) ||
            rows_end < rows_begin)
            return;

        const size_t bytes = static_cast<size_t>(rows_end - rows_begin);
        if ((bytes % 0x1C) != 0)
            return;

        const int32_t row_count = static_cast<int32_t>(bytes / 0x1C);
        if (saved_visible_index >= row_count)
            return;

        constexpr int32_t kMaxReplay = 256;
        const int32_t replay_count =
            (saved_visible_index > kMaxReplay) ? kMaxReplay : saved_visible_index;

        for (int32_t i = 0; i < replay_count; ++i)
            StepMapListDownAndRedraw();

        if (s_logBudget > 0)
        {
            --s_logBudget;
            Log(L"[HOP3] restored visible=%d rows=%d replayed=%d\n",
                saved_visible_index,
                row_count,
                replay_count);
        }
    }

} // namespace BZROpenShim
