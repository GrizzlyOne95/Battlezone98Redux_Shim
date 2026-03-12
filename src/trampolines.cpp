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
#include "bzr_hooks.h"

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
// Map Filters 3/8
// Site: 0x0079D6B1
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapFilters3()
{
    static const char* name = "Trampoline_MapFilters3";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  ebp, esp
        mov  ecx, dword ptr ds:[0x00945564]
        mov  byte ptr [g_MapFilterFlag12], 0x1
        jmp  [g_RetAddr_MapFilters3]
    }
}

// -----------------------------------------------------------------------
// Map Filters 4/8
// Site: 0x0079D691
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapFilters4()
{
    static const char* name = "Trampoline_MapFilters4";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  ebp, esp
        mov  ecx, dword ptr ds:[0x00945564]
        mov  byte ptr [g_MapFilterFlag12], 0x0
        jmp  [g_RetAddr_MapFilters4]
    }
}

// -----------------------------------------------------------------------
// Map Filters 5/8
// Site: 0x00799116
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapFilters5()
{
    static const char* name = "Trampoline_MapFilters5";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        // Build the filter list via engine helper.
        push edx
        push 0x20
        push offset MapFilterOnScrollDown
        push offset MapFilterOnScrollUp
        push ecx
        xorps xmm0, xmm0
        movss dword ptr [esp], xmm0
        push ecx
        movss xmm0, dword ptr ds:[0x008A2B08]
        movss dword ptr [esp], xmm0
        push ecx
        movss xmm0, dword ptr ds:[0x008A2A5C]
        movss dword ptr [esp], xmm0
        push ecx
        movss xmm0, dword ptr ds:[0x008A2AA0]
        movss dword ptr [esp], xmm0
        push dword ptr ds:[0x0089E8C8]
        mov  ecx, [ebp - 0xBC]
        call dword ptr [g_BzrFn_MapFilterCreate]
        mov  [ebp - 0x1B4], eax
        mov  [g_MapFilterListPtr], eax
        jmp  [g_RetAddr_MapFilters5]
    }
}

// -----------------------------------------------------------------------
// Map Filters 7/8
// Site: 0x007998AB
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapFilters7()
{
    static const char* name = "Trampoline_MapFilters7";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  byte ptr [g_MapFilterFlag11], 0x1
        mov  eax, [ebp - 0x44]
        mov  ecx, [eax + 0x17C]
        jmp  [g_RetAddr_MapFilters7]
    }
}

// -----------------------------------------------------------------------
// Map Filters 8/8
// Site: 0x007997A9
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapFilters8()
{
    static const char* name = "Trampoline_MapFilters8";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        movzx eax, byte ptr [g_MapFilterFlag11]
        test eax, eax
        jz   mf8_check
        mov  byte ptr [g_MapFilterFlag11], 0x0
        mov  eax, [ebp - 0x8]
        mov  ecx, [eax + 0x164]
        jmp  [g_RetAddr_MapFilters8_A]

    mf8_check:
        mov  eax, [ebp - 0x8]
        mov  ecx, [eax + 0x164]
        call dword ptr [g_BzrFn_MapFilter8Check]
        mov  [ebp - 0x1], al
        movzx ecx, byte ptr [ebp - 0x1]
        test ecx, ecx
        jz   mf8_false
        jmp  [g_RetAddr_MapFilters8_B]
    mf8_false:
        jmp  [g_RetAddr_MapFilters8_C]
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

// -----------------------------------------------------------------------
// Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3)
// Site: 0x00766C4A (CALL 0x00481AF0)
// Stub mirrors _bzcp.dll: call 0x481EA0, then original 0x481AF0, then jump
// to return address after the original stack cleanup.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_VehicleListModFix1()
{
    static const char* name = "Trampoline_VehicleListModFix1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        pop  dword ptr [ebp - 4]
        push dword ptr [ebp - 4]
        call dword ptr [g_BzrFn_VehicleFixPre]
        push dword ptr [ebp - 4]
        call dword ptr [g_BzrFn_VehicleFixOrig]
        add  esp, 4
        jmp  [g_RetAddr_VehicleListModFix1]
    }
}

// -----------------------------------------------------------------------
// Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3)
// Site: 0x00798BD9 (PUSH ECX)
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_VehicleListModFix4()
{
    static const char* name = "Trampoline_VehicleListModFix4";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  [g_VehicleListParam], ecx
        call VehicleListModFix4Helper
        jmp  [g_RetAddr_VehicleListModFix4]
    }
}

// -----------------------------------------------------------------------
// BZRNET Integration Host
// Site: 0x00743C05
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_BzrnetHost()
{
    static const char* name = "Trampoline_BzrnetHost";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  byte ptr [ebp - 4], 0x0C
        lea  eax, [ebp - 0x100]
        push eax
        lea  ecx, [ebp - 0xB8]
        push ecx
        mov  edx, [ebp - 0x26C]
        mov  [g_BzrnetHostObj], edx
        add  edx, 0x28
        push edx
        mov  eax, [ebp - 0x26C]
        mov  edx, [eax]
        mov  ecx, [ebp - 0x26C]
        mov  eax, [edx + 0x1C]
        call eax

        cmp  dword ptr [g_BzrnetHostObj], 0
        je   host_done
        mov  eax, [g_BzrnetHostObj]
        mov  ecx, [eax]
        mov  edx, [ecx + 0x1C]
        mov  [ebp - 4], edx
        push offset g_BzrnetLabel2
        push offset g_BzrnetLabel1
        mov  eax, [g_BzrnetHostObj]
        add  eax, 0x28
        push eax
        mov  ecx, [g_BzrnetHostObj]
        call dword ptr [ebp - 4]

        mov  ecx, [g_BzrnetHostObj]
        mov  edx, [ecx]
        mov  eax, [edx + 0x1C]
        mov  [ebp - 8], eax
        push offset g_BzrnetLabel4
        push offset g_BzrnetLabel3
        mov  ecx, [g_BzrnetHostObj]
        add  ecx, 0x28
        push ecx
        mov  ecx, [g_BzrnetHostObj]
        call dword ptr [ebp - 8]
    host_done:
        jmp  [g_RetAddr_BzrnetHost]
    }
}

// -----------------------------------------------------------------------
// BZRNET Integration Client
// Site: 0x0073E71C
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_BzrnetClient()
{
    static const char* name = "Trampoline_BzrnetClient";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  byte ptr [ebp - 4], 0x07
        lea  ecx, [ebp - 0x40]
        push ecx
        lea  edx, [ebp - 0xA0]
        push edx
        mov  eax, [ebp - 0xBC]
        mov  [g_BzrnetClientObj], eax
        add  eax, 0x28
        push eax
        mov  ecx, [ebp - 0xBC]
        mov  edx, [ecx]
        mov  ecx, [ebp - 0xBC]
        mov  eax, [edx + 0x1C]
        call eax

        cmp  dword ptr [g_BzrnetClientObj], 0
        je   client_done
        mov  eax, [g_BzrnetClientObj]
        mov  ecx, [eax]
        mov  edx, [ecx + 0x1C]
        mov  [ebp - 4], edx
        push offset g_BzrnetLabel2
        push offset g_BzrnetLabel1
        mov  eax, [g_BzrnetClientObj]
        add  eax, 0x28
        push eax
        mov  ecx, [g_BzrnetClientObj]
        call dword ptr [ebp - 4]

        mov  ecx, [g_BzrnetClientObj]
        mov  edx, [ecx]
        mov  eax, [edx + 0x1C]
        mov  [ebp - 8], eax
        push offset g_BzrnetLabel4
        push offset g_BzrnetLabel3
        mov  ecx, [g_BzrnetClientObj]
        add  ecx, 0x28
        push ecx
        mov  ecx, [g_BzrnetClientObj]
        call dword ptr [ebp - 8]
    client_done:
        jmp  [g_RetAddr_BzrnetClient]
    }
}

// -----------------------------------------------------------------------
// Custom /help + /ban command handler
// Site: 0x0062480B
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_CommandHelp()
{
    static const char* name = "Trampoline_CommandHelp";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  edx, [ebp + 0x0C]
        movzx eax, byte ptr [ebp + 0x08]
        push edx
        push eax
        call HandleCommandHelpBan
        add  esp, 8
        test al, al
        jnz  cmd_handled
        jmp  [g_RetAddr_CommandHelpFallback]
    cmd_handled:
        jmp  [g_RetAddr_CommandHelpHandled]
    }
}

// -----------------------------------------------------------------------
// Ban Button Hook 1/2
// Site: 0x007D0A2F
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_BanButtonHook1()
{
    static const char* name = "Trampoline_BanButtonHook1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        movzx eax, byte ptr [ebp + 0x20]
        mov  [g_BanFlag], eax
        mov  ecx, [ebp + 8]
        mov  [g_BanParentHost], ecx
        movss xmm0, [ebp + 0x0C]
        movss [g_BanX], xmm0
        movss xmm0, [ebp + 0x10]
        movss [g_BanY], xmm0
        cmp  dword ptr [g_BanFlag], 0
        setne cl
        call BanButtonCreateHost
        mov  eax, [g_BanFlag]
        test eax, eax
        jmp  [g_RetAddr_BanHook1]
    }
}

// -----------------------------------------------------------------------
// Ban Button Hook 2/2
// Site: 0x007A6913
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_BanButtonHook2()
{
    static const char* name = "Trampoline_BanButtonHook2";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  ecx, [ebp - 0xD8]
        mov  [g_BanParentClient], ecx
        call BanButtonCreateClient
        mov  byte ptr [ebp - 4], 0xFF
        jmp  [g_RetAddr_BanHook2]
    }
}

} // namespace BZROpenShim
