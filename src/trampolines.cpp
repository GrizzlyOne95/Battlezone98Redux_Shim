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
        pushad
        push name
        call LogHit
        add  esp, 4
        popad

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
        pushad
        push name
        call LogHit
        add  esp, 4
        popad

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
        pushad
        push name
        call LogHit
        add  esp, 4
        popad

        call edx
        mov  eax, [ebp - 0xA4]
        mov  ecx, eax
        call RestoreMapListVisibleIndex
        push 0x930
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
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_Probe_MapSorting()
{
    static const char* name = "Trampoline_Probe_MapSorting";
    __asm
    {
        pushad
        push name
        call LogHit
        add  esp, 4
        popad

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
        pushad
        push name
        call LogHit
        add  esp, 4
        popad

        push edx
        push 0x20
        push 0
        jmp  [g_RetAddr_Probe_MapFilter1]
    }
}

} // namespace BZROpenShim
