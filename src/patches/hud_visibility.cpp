// hud_visibility.cpp
// BZR Open Shim - Ctrl+= hides all HUD for screenshots
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Stock switch. DAT_008EAAB0 (catalog "HudDisplayInterfaceFlag") is the
// stock show-HUD switch: the NO_HUD_VIEW view (Shift+F5, action 3 in the
// action table at 0x008EB088) clears it at 0x0061AB78, the Options HUD on/off
// box writes it at 0x007AF3A5, and the HUD pass FUN_00617600 draws the HUD
// element list (FUN_004b6f10 -> FUN_004b6db0, each element's vtable slot 6:
// ScrapGauge, CockpitRadar, MapRadar, ControlPanel, ...) only while it is
// non-zero (cmp at 0x00617635, guarded by "HudDisplayInterfaceGate").
// Reticle (FUN_005bc170), TargetCam (FUN_005dde00) and SniperInterface
// (FUN_005d6530) test it themselves. It is not written to any config file
// (only read from render.cfg [Debug] HUD at FUN_0077e490), so holding it at 0
// changes nothing persistent. Writing it directly, instead of switching to
// the NO_HUD view, leaves the camera and cockpit alone.
//
// Typing. A focused legacy text editor (in-mission chat, ally prompt) owns
// the keyboard: the stock WndProc FUN_00619340 asks FUN_00823ce0 for the
// first focused editor and hands it the key (reverse_engineering/coopflow/
// TEXT_ENTRY_STATE.md). That lookup ("LegacyTextEditorFocusLookup") is
// called here too, and while it returns a node Ctrl+= is left to the game.
//
// Keys are filtered like quicksave.cpp: a subclass of the game window plus
// the exe's PeekMessageA import (the drain loop in FUN_00619be0 removes
// queued keyboard messages itself). The decision is HudVisibilityPolicy.

#include "hud_visibility.h"
#include "hud_visibility_policy.h"
#include "game_state.h"
#include "hook_engine.h"
#include "iat_patch.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::HudVisibility
{
    namespace
    {
        namespace Policy = HudVisibilityPolicy;

        using FocusLookupFn = void*(__cdecl*)();
        using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);

        // Keys are only taken while the world is updating.
        constexpr ULONGLONG kTickFreshMs = 500;

        std::atomic<bool> g_hidden{false};
        std::atomic<bool> g_toggleRequested{false};
        std::atomic<ULONGLONG> g_lastTickMs{0};

        // Main (window/frame) thread only.
        Policy::KeyLatch g_latch;
        Policy::StockSwitch g_stock;
        int g_bindState = 0; // 0 untried, 1 bound, -1 unavailable
        uint32_t g_flagAddr = 0;
        uint32_t g_focusLookupAddr = 0;

        HWND g_window = nullptr;
        WNDPROC g_prevWndProc = nullptr;
        bool g_subclassAttempted = false;
        bool g_peekAttempted = false;
        PFN_PeekMessageA g_realPeekMessageA = nullptr;

        bool Bind()
        {
            if (g_bindState == 0)
            {
                uint32_t gate = 0;
                const HookEngine::EngineRow rows[] = {
                    { "HudDisplayInterfaceFlag", &g_flagAddr },
                    { "HudDisplayInterfaceGate", &gate },
                    { "LegacyTextEditorFocusLookup", &g_focusLookupAddr },
                };
                g_bindState = HookEngine::BindEngineRows("HUD visibility", rows) ? 1 : -1;
                if (g_bindState < 0)
                {
                    g_flagAddr = 0;
                    g_focusLookupAddr = 0;
                    LogShimA(LogLevel::Warn, "hudvisibility",
                             "Ctrl+= HUD toggle unavailable: engine rows did not bind");
                }
            }
            return g_bindState > 0;
        }

        bool ReadStockSwitch(int& value) noexcept
        {
            if (!g_flagAddr)
                return false;
            __try
            {
                value = *reinterpret_cast<const volatile int*>(g_flagAddr);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void WriteStockSwitch(int value) noexcept
        {
            if (!g_flagAddr)
                return;
            __try
            {
                *reinterpret_cast<volatile int*>(g_flagAddr) = value;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool CallFocusLookup(uint32_t address) noexcept
        {
            __try
            {
                return reinterpret_cast<FocusLookupFn>(address)() != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return true;
            }
        }

        Policy::Gate ReadGate()
        {
            Policy::Gate gate;
            gate.worldTicking =
                GetTickCount64() - g_lastTickMs.load(std::memory_order_relaxed) <= kTickFreshMs;
            if (!gate.worldTicking)
                return gate;
            const ShellUiState ui = ReadShellUiState();
            gate.shellReadable = ui.readable;
            gate.shellScreenUp = ui.wrapperActive || ui.screenPresent;
            gate.textEditorFocused = TextEditorFocused();
            return gate;
        }

        // True when the message must be dropped.
        bool FilterKeyMessage(UINT msg, WPARAM, LPARAM lParam)
        {
            if (msg != Policy::kWmKeyDown && msg != Policy::kWmKeyUp && msg != Policy::kWmSysKeyDown &&
                msg != Policy::kWmSysKeyUp)
                return false;
            const auto bits = static_cast<unsigned long>(lParam);
            Policy::KeyMessage key;
            key.msg = msg;
            key.scanCode = (bits >> 16) & 0xFFu;
            key.extended = (bits & (1UL << 24)) != 0;
            if (!Policy::IsChordKey(key))
                return false;
            key.autorepeat = (bits & (1UL << 30)) != 0;
            key.ctrl = GetKeyState(VK_CONTROL) < 0;
            key.shift = GetKeyState(VK_SHIFT) < 0;
            key.alt = GetKeyState(VK_MENU) < 0;

            // The game-state reads only matter for a fresh Ctrl+= press.
            const bool freshChord = (msg == Policy::kWmKeyDown || msg == Policy::kWmSysKeyDown) &&
                                    !key.autorepeat && key.ctrl && !key.shift && !key.alt;
            const bool gateOpen = freshChord && g_bindState > 0 && Policy::GateOpen(ReadGate());
            const Policy::KeyAction action = Policy::Decide(key, gateOpen, g_latch);
            if (action == Policy::KeyAction::Pass)
                return false;
            if (action == Policy::KeyAction::SwallowToggle)
                g_toggleRequested.store(true, std::memory_order_release);
            return true;
        }

        LRESULT CALLBACK HudVisibilityWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
        {
            if (FilterKeyMessage(msg, w, l))
                return 0;
            return g_prevWndProc ? CallWindowProcA(g_prevWndProc, h, msg, w, l) : DefWindowProcA(h, msg, w, l);
        }

        BOOL WINAPI HudVisibilityPeekMessageA(LPMSG msg, HWND hwnd, UINT minFilter, UINT maxFilter, UINT remove)
        {
            for (;;)
            {
                const BOOL got = g_realPeekMessageA
                    ? g_realPeekMessageA(msg, hwnd, minFilter, maxFilter, remove)
                    : FALSE;
                if (!got || !msg || (remove & PM_REMOVE) == 0 ||
                    !FilterKeyMessage(msg->message, msg->wParam, msg->lParam))
                {
                    return got;
                }
            }
        }

        struct FindCtx
        {
            HWND found = nullptr;
        };

        BOOL CALLBACK FindGameWindowCb(HWND h, LPARAM context)
        {
            char title[256] = {};
            GetWindowTextA(h, title, sizeof(title));
            if (std::strstr(title, "Battlezone 98 Redux"))
            {
                reinterpret_cast<FindCtx*>(context)->found = h;
                return FALSE;
            }
            return TRUE;
        }

        void EnsureKeyFilters()
        {
            if (!g_peekAttempted)
            {
                g_peekAttempted = true;
                const IatPatch::Result result = IatPatch::PatchImportFromAnyDll(
                    GetModuleHandleW(nullptr), "PeekMessageA",
                    reinterpret_cast<void*>(&HudVisibilityPeekMessageA),
                    reinterpret_cast<void**>(&g_realPeekMessageA));
                if (result != IatPatch::Result::Patched)
                    LogShimA(LogLevel::Warn, "hudvisibility",
                             "PeekMessageA import not patched; a Ctrl+= queued behind another key can reach the game");
            }

            if (g_window || g_subclassAttempted)
                return;
            FindCtx ctx;
            EnumThreadWindows(GetCurrentThreadId(), FindGameWindowCb, reinterpret_cast<LPARAM>(&ctx));
            if (!ctx.found)
                return; // try again next tick
            g_subclassAttempted = true;
            SetLastError(ERROR_SUCCESS);
            const auto prev = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(
                ctx.found, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&HudVisibilityWndProc)));
            if (!prev && GetLastError() != ERROR_SUCCESS)
            {
                LogShimA(LogLevel::Warn, "hudvisibility", "Could not subclass the game window (error=%lu)",
                         GetLastError());
                return;
            }
            g_prevWndProc = prev;
            g_window = ctx.found;
            LogShimA(LogLevel::Info, "hudvisibility", "%s HUD toggle active (hwnd=%p previous=%p)",
                     Policy::kChordText, ctx.found, prev);
        }

        void SetHidden(bool hide)
        {
            int current = 0;
            const bool readable = ReadStockSwitch(current);
            if (hide)
            {
                Policy::Hide(g_stock, readable, current);
                int write = 0;
                if (readable && Policy::Enforce(g_stock, current, write))
                    WriteStockSwitch(write);
            }
            else
            {
                int write = 0;
                if (Policy::Show(g_stock, readable ? current : -1, write))
                    WriteStockSwitch(write);
            }
            g_hidden.store(hide, std::memory_order_release);
            LogShimA(LogLevel::Info, "hudvisibility", "HUD %s (stock switch %s)", hide ? "hidden" : "shown",
                     readable ? "driven" : "unreadable");
        }
    }

    // Unknown reads as "an editor has focus": the key then stays the game's.
    // Shared with rts_commands.cpp; the row is bound on first use, apart from
    // the HUD switch rows, so a HUD-row miss does not take the check down.
    bool TextEditorFocused() noexcept
    {
        uint32_t address = g_focusLookupAddr;
        if (!address)
        {
            try
            {
                address = HookEngine::EngineAddress("LegacyTextEditorFocusLookup");
            }
            catch (...)
            {
                address = 0;
            }
            if (!address)
                return true;
            g_focusLookupAddr = address;
        }
        return CallFocusLookup(address);
    }

    bool IsHidden() noexcept
    {
        return g_hidden.load(std::memory_order_acquire);
    }

    void Tick() noexcept
    {
        g_lastTickMs.store(GetTickCount64(), std::memory_order_relaxed);
        if (!Bind())
            return;
        EnsureKeyFilters();

        if (g_toggleRequested.exchange(false, std::memory_order_acq_rel))
            SetHidden(!g_hidden.load(std::memory_order_acquire));

        int current = 0;
        int write = 0;
        if (g_stock.hidden && ReadStockSwitch(current) && Policy::Enforce(g_stock, current, write))
            WriteStockSwitch(write);
    }

    void ResetMission() noexcept
    {
        g_toggleRequested.store(false, std::memory_order_relaxed);
        if (!g_hidden.load(std::memory_order_acquire) && !g_stock.hidden)
            return;
        SetHidden(false);
    }
}
