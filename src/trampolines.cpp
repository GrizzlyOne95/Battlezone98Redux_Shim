// trampolines.cpp
// BZR Open Shim - clean-room replacement trampolines
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from analysis of _bzcp.dll and the GOG v2.2.301 executable.
// All logic is described in terms of the purpose of each operation, not
// copied bytes.

#include "trampolines.h"
#include "patches.h"
#include "scroll_helper.h"

// We compile this as 32-bit (/arch:IA32) -- same as BZR.exe

namespace BZROpenShim
{

// -----------------------------------------------------------------------
// Hop-Fix 1/3
// Purpose: Save the selected entry and visible row before the list rebuild.
// Ghidra-confirmed _bzcp pipeline:
//   Hook 1 -> FUN_1000CAF0 -> original call at 0x005D4260
// The JMP overwrites:
//   MOV EAX,[EBP-4]
//   MOV ECX,[EAX+0x138] (partially)
// We execute the save helper first, then replay the original call setup.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_HopFix1()
{
    static const char* name = "Trampoline_HopFix1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  eax, [ebp - 4]          // 8B 45 FC
        mov  [ebp - 4], eax          // 89 45 FC
        mov  ecx, [ebp - 4]
        call SaveMapListSelection
        mov  eax, [ebp - 4]
        mov  ecx, [eax + 0x138]
        call [g_BZRFnPtr_HopFix1]
        jmp  [g_RetAddr_HopFix1]
    }
}

// -----------------------------------------------------------------------
// Hop-Fix 2/3
// Purpose: Reselect the saved entry after the list rebuild completes.
// Ghidra-confirmed _bzcp trampoline:
//   MOV EAX,[0x0094555C]
//   MOV ECX,[EAX]
//   CALL restore-selection helper
// The helper itself issues the equivalent of the original select-by-index call.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_HopFix2()
{
    static const char* name = "Trampoline_HopFix2";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  eax, [g_MapListObject]
        test eax, eax
        jz   hop2_done
        mov  ecx, [eax]
        test ecx, ecx
        jz   hop2_done
        call RestoreMapListSelection
hop2_done:
        jmp  [g_RetAddr_HopFix2]
    }
}

// -----------------------------------------------------------------------
// Hop-Fix 3/3
// Purpose: Restore the visible row after the selection has been restored.
// Ghidra-confirmed _bzcp helper FUN_1000CCA0 replays the native list-step
// function once per saved visible row and then returns to the original flow.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_HopFix3()
{
    static const char* name = "Trampoline_HopFix3";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        call edx
        // Re-execute the original instructions we overwrote
        call edx                       // FF D2

        // Steam build: skip scroll restore helpers entirely.
        cmp  byte ptr [g_EnableScrollRestore], 0
        je   skip_restore

        // Capture likely list context for thiscall scroll routines.
        mov  eax, [ebp - 0xA4]
        mov  ecx, eax
        call RestoreMapListVisibleIndex
        push 0x930
        call ScrollUpdateHelper

    skip_restore:
        push 0x930                     // 68 30 09 00 00
        jmp  [g_RetAddr_HopFix3]
    }
}

// -----------------------------------------------------------------------
// Probe: refresh/map-sorting path candidate (historical _bzcp patch site)
// Site: 0x007680D6
// Original bytes:
//   89 4D F8          mov [ebp-0x08], ecx
//   0F B6 45 FF       movzx eax, byte ptr [ebp-0x01]
// We overwrite first 5 bytes, so replay both instructions and return to +7.
//
// NOTE: The scroll-state capture previously read [ebp-0xA4] / [eax+0x17C]
// which are GOG-specific stack frame offsets.  On Steam builds the layout
// differs, so dereferencing them crashed (0xc0000005).
// We now attempt the capture in a SEH-protected helper; if the offsets are
// wrong the capture is silently skipped — the hop-fix still works, it just
// won't know the pre-refresh scroll position for this path.
// -----------------------------------------------------------------------

// Safe helper called from asm — SEH-protected so we never crash
static void __cdecl SafeCapture_MapSorting(void* frame_ebp)
{
    __try
    {
        auto base = reinterpret_cast<uint8_t*>(frame_ebp);
        // Try reading the map list context the same way HopFix3 does
        void* ctx_outer = *reinterpret_cast<void**>(base - 0xA4);
        if (!ctx_outer) return;
        void* ctx_inner = *reinterpret_cast<void**>(
            reinterpret_cast<uint8_t*>(ctx_outer) + 0x17C);
        if (!ctx_inner) return;
        CaptureScrollStateFromContext(ctx_inner);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // Offsets don't match this build — silently skip
    }
}

void __declspec(naked) __cdecl Trampoline_Probe_MapSorting()
{
    static const char* name = "Trampoline_Probe_MapSorting";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        // Try to capture scroll state via SEH-protected helper
        pushad
        push ebp
        call SafeCapture_MapSorting
        add  esp, 4
        popad

        // Replay the original instructions we overwrote
        mov  [ebp - 8], ecx
        movzx eax, byte ptr [ebp - 1]
        jmp  [g_RetAddr_Probe_MapSorting]
    }
}

// -----------------------------------------------------------------------
// Probe: refresh/filter path candidate
// Site: 0x00799116
// Original bytes: 52 6A 20 6A 00
//   push edx
//   push 0x20
//   push 0x00
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_Probe_MapFilter1()
{
    static const char* name = "Trampoline_Probe_MapFilter1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        push edx
        push 0x20
        push 0
        jmp  [g_RetAddr_Probe_MapFilter1]
    }
}

// -----------------------------------------------------------------------
// Probe: MapListFix1 path (potential manual refresh)
// Site: 0x00799774
// Original bytes: 89 4D FC 8B 45 = mov [ebp-4], ecx; mov eax, [ebp-4]
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_Probe_MapListFix1()
{
    static const char* name = "Trampoline_Probe_MapListFix1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  [ebp - 4], ecx
        mov  eax, [ebp - 4]
        jmp  [g_RetAddr_Probe_MapListFix1]
    }
}

// -----------------------------------------------------------------------
// Probe: MapListFix2 path (potential manual refresh)
// Site: 0x007997A9
// Original bytes: 8B 45 F8 8B 88 = mov eax, [ebp-8]; mov ecx, [eax+8]
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_Probe_MapListFix2()
{
    static const char* name = "Trampoline_Probe_MapListFix2";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  eax, [ebp - 8]
        mov  ecx, [eax + 8]
        jmp  [g_RetAddr_Probe_MapListFix2]
    }
}

// -----------------------------------------------------------------------
// Version Notice patch
// Site: 0x0062480B
// Original bytes: 68 3C D5 88 00   (push <version string ptr>)
// We replace the pushed pointer with our transparency-tagged string.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_VersionNotice()
{
    static const char* name = "Trampoline_VersionNotice";
    static const char kVersionTag[] = "2.2.301 + OpenShim";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        push offset kVersionTag
        jmp  [g_RetAddr_VersionNotice]
    }
}

} // namespace BZROpenShim
