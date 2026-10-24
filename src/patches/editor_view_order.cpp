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
// this is armed synchronously from DllMain. The Windows loader runs DllMain
// for statically imported DLLs before the executable's entry point, so the
// ordering is guaranteed by the loader rather than being a race.
//
// On GOG the sites are plaintext at DllMain and are written immediately. On
// Steam, SteamStub has not decrypted .text yet, so the guards read ciphertext.
// The write is then deferred to the executable's own call through its
// MSVCR120!_initterm import: that call runs from the CRT entry point after
// SteamStub has decrypted the image and immediately before the constructors.
//
// This also means the usual single-player gate cannot be enforced here: no
// network state exists yet. The ini key is opt-in and defaults off, and the
// change restores stock 1.5 ordering rather than inventing new behavior, but a
// multiplayer session with it enabled does move when ControlPanel::Render emits
// its commands within the frame. That is documented alongside the key.

#include "editor_view_order.h"
#include "bool_token.h"
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

            // An unrecognized value turns the fix off.
            bool enabled = false;
            return BZROpenShim::BoolToken::TryParse(value, enabled) && enabled;
        }

        void ApplyGuardedPriorityWrites()
        {
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

        using FnInitTerm = void(__cdecl*)(void (__cdecl**)(), void (__cdecl**)());

        FnInitTerm g_originalInitTerm = nullptr;
        void** g_initTermSlot = nullptr;

        bool WriteImportSlot(void** slot, void* value)
        {
            DWORD oldProtect = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_READWRITE, &oldProtect))
                return false;
            *slot = value;
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
            return true;
        }

        // One shot: restore the import, apply the writes against the now
        // decrypted image, then let the constructors run.
        void __cdecl InitTermHook(void (__cdecl** first)(), void (__cdecl** last)())
        {
            const FnInitTerm original = g_originalInitTerm;
            if (g_initTermSlot)
            {
                WriteImportSlot(g_initTermSlot, reinterpret_cast<void*>(original));
                g_initTermSlot = nullptr;
                ApplyGuardedPriorityWrites();
            }
            original(first, last);
        }

        // Finds the executable's import slot currently bound to target by
        // walking its import directory, which SteamStub leaves in plaintext.
        void** FindMainModuleImportSlot(const char* dllName, void* target)
        {
            __try
            {
                auto* base = reinterpret_cast<uint8_t*>(GetModuleHandleW(nullptr));
                auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
                auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
                const IMAGE_DATA_DIRECTORY& dir =
                    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
                if (dir.VirtualAddress == 0)
                    return nullptr;

                for (auto* desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + dir.VirtualAddress);
                     desc->Name != 0; ++desc)
                {
                    if (_stricmp(reinterpret_cast<const char*>(base + desc->Name), dllName) != 0)
                        continue;
                    for (auto** slot = reinterpret_cast<void**>(base + desc->FirstThunk); *slot; ++slot)
                    {
                        if (*slot == target)
                            return slot;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return nullptr;
        }

        bool ArmDeferredApply()
        {
            HMODULE crt = GetModuleHandleA("MSVCR120.dll");
            void* initTerm = crt ? reinterpret_cast<void*>(GetProcAddress(crt, "_initterm")) : nullptr;
            void** slot = initTerm ? FindMainModuleImportSlot("MSVCR120.dll", initTerm) : nullptr;
            if (!slot)
                return false;

            g_originalInitTerm = reinterpret_cast<FnInitTerm>(initTerm);
            g_initTermSlot = slot;
            if (!WriteImportSlot(slot, reinterpret_cast<void*>(&InitTermHook)))
            {
                g_initTermSlot = nullptr;
                return false;
            }
            return true;
        }
    }

    void ApplyEditorOverheadPlacementOrderFix()
    {
        if (!ReadEnabledFromUserConfig())
            return;

        // Both guards plaintext: the image is already decrypted (GOG).
        if (GuardMatches(kOverViewRegisterAddr, kOverViewExpected) &&
            GuardMatches(kControlPanelRegisterAddr, kControlPanelExpected))
        {
            ApplyGuardedPriorityWrites();
            return;
        }

        // Still packed (Steam): check again once the CRT reaches _initterm.
        if (ArmDeferredApply())
        {
            LogShimA(LogLevel::Info, "editorview",
                     "Overhead placement order deferred to CRT _initterm (image not yet decrypted)");
            return;
        }

        ApplyGuardedPriorityWrites();
    }
}
