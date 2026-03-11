// trampolines.cpp
// BZR Open Shim - clean-room replacement trampolines
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from analysis of _bzcp.dll (bzcp_hopfix_decompiled.txt,
// HOPFIX_ANALYSIS.md, FINAL_RE_REPORT.md).  All logic is described in
// terms of the *purpose* of each operation, not copied bytes.

#include "trampolines.h"
#include "patches.h"
#include "scroll_helper.h"

// We compile this as 32-bit (/arch:IA32) -- same as BZR.exe

namespace BZROpenShim
{

// -----------------------------------------------------------------------
// Hop-Fix 1/3
// Purpose: Preserve the map list context pointer before a refresh.
// Source reconstruction: HOPFIX_ANALYSIS.md "Hook 1"
// Original bytes at 0x79B85F: 8B 45 FC 8B 88 [38 01 00 00]
//   MOV EAX,[EBP-4]           ; get map list context (3 bytes)
//   MOV ECX,[EAX+0x138]       ; access list data (6 bytes, we overwrite 2)
// The JMP overwrites 5 bytes, so we must execute both instructions here.
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

        // Clean-room equivalent of _bzcp trampoline block.
        mov  eax, [ebp - 4]          // 8B 45 FC
        mov  [ebp - 4], eax          // 89 45 FC
        mov  ecx, [ebp - 4]          // 8B 4D FC
        // _bzcp calls an internal helper here (FUN_1000caf0); omitted in minimal hop-fix mode.
        mov  eax, [ebp - 4]
        mov  ecx, [eax + 0x138]
        
        // Call the BZR function pointer
        call [g_BZRFnPtr_HopFix1]
        jmp  [g_RetAddr_HopFix1]
    }
}

// -----------------------------------------------------------------------
// Hop-Fix 2/3
// Purpose: Replay the original call sequence at the patch site in a safe detour.
// Source bytes at 0x00799279 (first 19 bytes):
//   PUSH 0
//   MOV EAX,[EBP-0xA4]
//   MOV ECX,[EAX+0x17C]
//   CALL <target>
// We patch 5 bytes, then execute the full intended sequence here and return
// to site+0x13.
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

        // Replay original instructions / call context exactly.
        push 0
        mov  eax, [ebp - 0xA4]
        mov  ecx, [eax + 0x17C]
        call [g_BZRFnPtr_HopFix2]
        jmp  [g_RetAddr_HopFix2]
    }
}

// -----------------------------------------------------------------------
// Hop-Fix 3/3
// Purpose: Restore scroll position after map list rebuild.
// Source reconstruction: HOPFIX_ANALYSIS.md "Hook 3" + FINAL_RE_REPORT.md
// Original bytes at 0x799377: FF D2 68 30 09
//   CALL EDX                  ; call dynamic function (2 bytes)
//   PUSH 0x930                ; (5 bytes, we overwrite first 3 bytes: 68 30 09)
// The JMP overwrites 5 bytes, so we must execute both instructions here.
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

        // Re-execute the original instructions we overwrote
        call edx                       // FF D2

        // Steam build: skip scroll restore helpers entirely.
        cmp  byte ptr [g_EnableScrollRestore], 0
        je   skip_restore

        // Capture likely list context for thiscall scroll routines.
        mov  eax, [ebp - 0xA4]
        mov  ecx, [eax + 0x17C]
        mov  dword ptr [g_HopFix3Context], ecx
        
        // Custom scroll restore logic with frame-based delta reconstruction.
        mov  eax, [ebp - 0xA4]         // fallback
        push eax
        push ebp
        call SelectHopFix3DeltaFromFrame
        add  esp, 8
        push eax
        push dword ptr [g_HopFix3Context]
        call ConsumeSavedScrollDelta
        add  esp, 8
        mov  ecx, eax
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
