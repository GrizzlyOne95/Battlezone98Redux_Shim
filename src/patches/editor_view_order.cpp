// editor_view_order.cpp
// BZR Open Shim - overhead-editor display order compatibility fix
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Redux transposed two DisplayInterface::AddView priority constants for the
// overhead view (view 3, Shift+F10), which breaks editor object placement while
// the simulation is running.
//
// The mechanism, verified against the 1.5 decompile and the shipped Redux exe:
//
//   * Reticle::Simulate runs only from Simulate()'s arcade branch -- that is,
//     only in editor mode -- and nulls reticle.groundPos on every simulated
//     frame whenever the current view is not one of the cockpit-style views.
//     Both builds do this; it is not the defect.
//   * OverView::Render republishes groundPos = &overView.where.
//   * ControlPanel::Render consumes it: the build-menu keypress always plays
//     mnu_clik.wav, but only calls GameObjectClass::Build when groundPos is
//     non-null.
//
// AddView(view, priority) inserts into a per-view list sorted ascending, so the
// lower priority renders first. 1.5 registers OverView at priority 0 and
// ControlPanel at priority 1, so the producer runs before the consumer. Redux
// has them the other way around, so the consumer reads the null that
// Reticle::Simulate wrote earlier in the same frame: the key clicks and nothing
// is placed. Pausing appears to fix it only because Simulate() stops running,
// so nothing nulls the pointer -- which is also why the cursor freezes.
//
// Both writes must land together. Changing only one produces a priority tie,
// and AddViewRender appends on ties, so the resulting order would depend on
// global-constructor order rather than on either constant. The guards are
// therefore checked for both sites before either is written.
//
// Timing: these are global constructors reached from _initterm before main.
// RunPatcher runs on the patch thread after WaitForSignature, far too late, so
// this is applied synchronously from DllMain. The Windows loader runs DllMain
// for statically imported DLLs before the executable's entry point, so the
// ordering is guaranteed by the loader rather than being a race.
//
// This also means the usual single-player gate cannot be enforced here: no
// network state exists yet. The ini key is opt-in and defaults off, and the
// change restores stock 1.5 ordering rather than inventing new behavior, but a
// multiplayer session with it enabled does move when ControlPanel::Render emits
// its commands within the frame. That is documented alongside the key.

#include "editor_view_order.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        // Each site is `push <priority> ; push 3 ; mov ecx,[ebp-0x10] ; call AddView`.
        // The guard spans the whole sequence including the call displacement to
        // DisplayInterface::AddView (0x004B6940), so a build whose layout moved
        // cannot land this on some unrelated push.
        constexpr size_t kSiteGuardLength = 12;
        constexpr size_t kPriorityOperandOffset = 1;

        // OverView::OverView -> AddView(view 3, priority 1). 1.5 uses 0.
        constexpr uintptr_t kOverViewRegisterAddr = 0x0058755Eu;
        constexpr uint8_t kOverViewExpected[kSiteGuardLength] = {
            0x6A, 0x01, 0x6A, 0x03, 0x8B, 0x4D, 0xF0, 0xE8, 0xD6, 0xF3, 0xF2, 0xFF
        };
        constexpr uint8_t kOverViewLegacyPriority = 0x00;

        // ControlPanel ctor -> AddView(view 3, priority 0). 1.5 uses 1.
        constexpr uintptr_t kControlPanelRegisterAddr = 0x0049F95Cu;
        constexpr uint8_t kControlPanelExpected[kSiteGuardLength] = {
            0x6A, 0x00, 0x6A, 0x03, 0x8B, 0x4D, 0xF0, 0xE8, 0xD8, 0x6F, 0x01, 0x00
        };
        constexpr uint8_t kControlPanelLegacyPriority = 0x01;

        constexpr bool kEditorPlacementOrderEnabledDefault = true;

        bool GuardMatches(uintptr_t address, const uint8_t* expected)
        {
            __try
            {
                return std::memcmp(reinterpret_cast<const void*>(address), expected, kSiteGuardLength) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool WritePriorityByte(uintptr_t address, uint8_t value)
        {
            auto* operand = reinterpret_cast<uint8_t*>(address + kPriorityOperandOffset);

            DWORD oldProtect = 0;
            if (!VirtualProtect(operand, sizeof(*operand), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *operand = value;
            FlushInstructionCache(GetCurrentProcess(), operand, sizeof(*operand));

            DWORD ignored = 0;
            VirtualProtect(operand, sizeof(*operand), oldProtect, &ignored);
            return true;
        }

        // Deliberately self-contained. This runs inside DllMain, before the
        // shim's normal config plumbing exists, so it resolves the same file
        // the rest of the shim uses (openshim.ini beside the executable)
        // without depending on any of that machinery being initialized.
        bool ReadEnabledFromUserConfig()
        {
            char exePath[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, exePath, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return kEditorPlacementOrderEnabledDefault;

            char* lastBackslash = std::strrchr(exePath, '\\');
            if (!lastBackslash)
                return kEditorPlacementOrderEnabledDefault;
            *(lastBackslash + 1) = '\0';

            char iniPath[MAX_PATH] = {};
            if (_snprintf_s(iniPath, sizeof(iniPath), _TRUNCATE, "%sopenshim.ini", exePath) < 0)
                return kEditorPlacementOrderEnabledDefault;

            // A sentinel default reliably detects a missing key: a present key
            // (even blank) never yields the sentinel byte.
            constexpr char kUnsetSentinel[] = "\x01__openshim_unset__";
            char value[64] = {};
            GetPrivateProfileStringA("General", "EditorOverheadPlacementOrder", kUnsetSentinel,
                                     value, static_cast<DWORD>(sizeof(value)), iniPath);
            if (value[0] == '\0' || std::strcmp(value, kUnsetSentinel) == 0)
                return kEditorPlacementOrderEnabledDefault;

            for (char* c = value; *c != '\0'; ++c)
                *c = static_cast<char>(std::tolower(static_cast<unsigned char>(*c)));

            return std::strcmp(value, "1") == 0 || std::strcmp(value, "true") == 0 ||
                   std::strcmp(value, "on") == 0 || std::strcmp(value, "yes") == 0 ||
                   std::strcmp(value, "enabled") == 0;
        }
    }

    void ApplyEditorOverheadPlacementOrderFix()
    {
        if (!ReadEnabledFromUserConfig())
            return;

        const bool overViewOk = GuardMatches(kOverViewRegisterAddr, kOverViewExpected);
        const bool controlPanelOk = GuardMatches(kControlPanelRegisterAddr, kControlPanelExpected);

        // Fail closed as a pair. A half-applied swap ties the two priorities,
        // and the tie resolves by constructor order, which is neither the stock
        // behavior nor the 1.5 behavior.
        if (!overViewOk || !controlPanelOk)
        {
            LogShimA(LogLevel::Warn, "editorview",
                     "Overhead placement order not applied: guard mismatch (overView=%s controlPanel=%s)",
                     overViewOk ? "ok" : "mismatch",
                     controlPanelOk ? "ok" : "mismatch");
            return;
        }

        if (!WritePriorityByte(kOverViewRegisterAddr, kOverViewLegacyPriority))
        {
            LogShimA(LogLevel::Error, "editorview",
                     "Overhead placement order not applied: write failed at 0x%08X",
                     static_cast<unsigned>(kOverViewRegisterAddr));
            return;
        }

        if (!WritePriorityByte(kControlPanelRegisterAddr, kControlPanelLegacyPriority))
        {
            // Put the first site back so the pair stays consistent rather than
            // leaving both interfaces on priority 0.
            WritePriorityByte(kOverViewRegisterAddr, kOverViewExpected[kPriorityOperandOffset]);
            LogShimA(LogLevel::Error, "editorview",
                     "Overhead placement order not applied: write failed at 0x%08X (reverted first site)",
                     static_cast<unsigned>(kControlPanelRegisterAddr));
            return;
        }

        LogShimA(LogLevel::Info, "editorview",
                 "Overhead placement order restored to 1.5 (OverView priority 0, ControlPanel priority 1)");
    }
}
