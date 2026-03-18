// trampolines.cpp
// BZR Open Shim - clean-room replacement trampolines
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from analysis of the reference patch behavior and the
// GOG v2.2.301 executable.
// All logic is described in terms of the purpose of each operation, not
// copied bytes.

#include "trampolines.h"
#include "patches.h"
#include "scroll_helper.h"
#include "bzr_hooks.h"

// We compile this as 32-bit (/arch:IA32) -- same as BZR.exe

namespace BZROpenShim
{

namespace
{
    enum MapRefreshTraceSite : int
    {
        kTraceHopFix1 = 1,
        kTraceHopFix3 = 2,
        kTraceMapListFixSupport1 = 3,
        kTraceMapSorting = 4,
        kTraceProbeMapFilter1 = 5,
        kTraceProbeMapListFix1 = 6,
        kTraceProbeMapListFix2 = 7,
        kTraceMapFilters5 = 8,
        kTraceMapFilters7 = 9,
        kTraceMapFilters8 = 10,
    };

    static void __cdecl TraceMapRefreshSiteFrame(int site, void* frame_ebp)
    {
        switch (site)
        {
        case kTraceHopFix1: TraceMapRefreshFrame(L"HopFix1", frame_ebp); break;
        case kTraceHopFix3: TraceMapRefreshFrame(L"HopFix3", frame_ebp); break;
        case kTraceMapListFixSupport1: TraceMapRefreshFrame(L"MapListFixSupport1", frame_ebp); break;
        case kTraceMapSorting: TraceMapRefreshFrame(L"MapSorting", frame_ebp); break;
        case kTraceProbeMapFilter1: TraceMapRefreshFrame(L"Probe_MapFilter1", frame_ebp); break;
        case kTraceProbeMapListFix1: TraceMapRefreshFrame(L"Probe_MapListFix1", frame_ebp); break;
        case kTraceProbeMapListFix2: TraceMapRefreshFrame(L"Probe_MapListFix2", frame_ebp); break;
        case kTraceMapFilters5: TraceMapRefreshFrame(L"MapFilters5", frame_ebp); break;
        case kTraceMapFilters7: TraceMapRefreshFrame(L"MapFilters7", frame_ebp); break;
        case kTraceMapFilters8: TraceMapRefreshFrame(L"MapFilters8", frame_ebp); break;
        default: break;
        }
    }

    enum ManualRefreshSupportPhase : int
    {
        kRefreshSupportEnter = 1,
        kRefreshSupportHandled = 2,
        kRefreshSupportFallback = 3,
    };

    static const wchar_t* ManualRefreshSupportPhaseName(int phase)
    {
        switch (phase)
        {
        case kRefreshSupportEnter: return L"enter";
        case kRefreshSupportHandled: return L"handled";
        case kRefreshSupportFallback: return L"fallback";
        default: return L"unknown";
        }
    }

    static void __cdecl TraceManualRefreshSupport(
        int phase,
        void* frame_ebp,
        void* ctx,
        int32_t delta,
        int32_t helperResult)
    {
        static long s_budget = 160;
        const long remaining = InterlockedDecrement(&s_budget);
        if (remaining < 0)
            return;

        auto* base = reinterpret_cast<uint8_t*>(frame_ebp);
        void* parent = nullptr;
        void* arg8 = nullptr;
        void* localMinus4 = nullptr;
        void* localMinus44 = nullptr;
        void* localMinusA4 = nullptr;
        void* mapObj = nullptr;
        int32_t d94 = 0;
        int32_t d98 = 0;

        if (base)
        {
            TryReadPtr(base + 0x00, parent);
            TryReadPtr(base + 0x08, arg8);
            TryReadPtr(base - 0x04, localMinus4);
            TryReadPtr(base - 0x44, localMinus44);
            TryReadPtr(base - 0xA4, localMinusA4);
            TryReadI32(base - 0x94, d94);
            TryReadI32(base - 0x98, d98);
        }

        __try
        {
            if (g_MapListObject)
                mapObj = *g_MapListObject;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            mapObj = nullptr;
        }

        Log(L"[REFRESHDBG] phase=%ls frame=0x%08X ctx=0x%08X arg8=0x%08X parent=0x%08X m4=0x%08X m44=0x%08X ma4=0x%08X d94=%d d98=%d delta=%d helper=%d hopCtx=0x%08X mapObj=0x%08X savedIdx=%d savedState=%d haveSaved=%d\n",
            ManualRefreshSupportPhaseName(phase),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(frame_ebp)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ctx)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(arg8)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parent)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(localMinus4)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(localMinus44)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(localMinusA4)),
            d94,
            d98,
            delta,
            helperResult,
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_HopFix3Context)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mapObj)),
            g_SavedMapIndex,
            g_SavedScrollState,
            g_HaveSavedScrollState ? 1 : 0);

        TraceMapRefreshFrame(L"ManualRefreshSupport", frame_ebp);
        if (ctx)
            TraceMapRefreshContext(L"ManualRefreshSupport", ctx);
    }
}

// -----------------------------------------------------------------------
// Hop-Fix 1/3
// Purpose: Save the selected entry and visible row before the list rebuild.
// Reverse-engineering-confirmed reference pipeline:
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

        pushad
        push ebp
        push kTraceHopFix1
        call TraceMapRefreshSiteFrame
        add  esp, 8
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
// Reverse-engineering-confirmed reference trampoline:
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
// Reverse-engineering-confirmed helper replays the native list-step
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

        pushad
        push ebp
        push kTraceHopFix3
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

        call edx
        mov  eax, [ebp - 0xA4]
        mov  [ebp - 4], eax
        mov  ecx, [ebp - 4]
        call RestoreMapListVisibleIndex
        push 0x930                     // 68 30 09 00 00
        jmp  [g_RetAddr_HopFix3]
    }
}

// -----------------------------------------------------------------------
// Map List Fix Support 1/3
// Site: 0x00799774
// Purpose: mirror the reference patch's manual-refresh scroll path.
// The helper consumes the saved row delta when possible; otherwise we fall
// back to the original 0x007A3BD0 call using the outer frame context at [ebp].
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_MapListFixSupport1()
{
    static const char* name = "Trampoline_MapListFixSupport1";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        pushad
        push ebp
        push kTraceMapListFixSupport1
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

        // Manual refresh does not appear to flow through HopFix1 on Steam, so
        // capture the current selection/scroll state explicitly here.
        pushad
        push ecx
        call SaveMapListSelection
        push dword ptr [esp]
        call CaptureScrollStateFromContext
        add  esp, 4
        pop  ecx
        popad

        pushad
        push -1
        push dword ptr [ebp + 8]
        push ecx
        push ebp
        push kRefreshSupportEnter
        call TraceManualRefreshSupport
        add  esp, 20
        popad

        mov  [ebp - 4], ecx
        mov  eax, [ebp + 8]
        mov  [ebp - 4], eax
        push eax
        mov  ecx, [ebp - 4]
        call ScrollUpdateHelper
        test eax, eax
        jne  support1_handled

        pushad
        push eax
        push dword ptr [ebp + 8]
        push dword ptr [ebp - 4]
        push ebp
        push kRefreshSupportFallback
        call TraceManualRefreshSupport
        add  esp, 20
        popad

        mov  ecx, [ebp]
        mov  ecx, [ecx + 0x1C8]
        call [g_BZRFn_MapListFixSupport1]
        jmp  support1_done

    support1_handled:
        pushad
        push eax
        push dword ptr [ebp + 8]
        push dword ptr [ebp - 4]
        push ebp
        push kRefreshSupportHandled
        call TraceManualRefreshSupport
        add  esp, 20
        popad

    support1_done:
        jmp  [g_RetAddr_MapListFixSupport1]
    }
}

// -----------------------------------------------------------------------
// Map Sorting
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
        push kTraceMapSorting
        call TraceMapRefreshSiteFrame
        add  esp, 8
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

        pushad
        push ebp
        push kTraceProbeMapFilter1
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

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

        pushad
        push ebp
        push kTraceProbeMapListFix1
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

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

        pushad
        push ebp
        push kTraceProbeMapListFix2
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

        mov  eax, [ebp - 8]
        mov  ecx, [eax + 8]
        jmp  [g_RetAddr_Probe_MapListFix2]
    }
}

    // -----------------------------------------------------------------------
    // Map Filters 1/8
    // Site: 0x007A31D9
    // -----------------------------------------------------------------------
    void __declspec(naked) __cdecl Trampoline_MapFilters1()
    {
        static const char* name = "Trampoline_MapFilters1";
        __asm
        {
            pushfd
            pushad
            push name
            call LogHit
            add  esp, 4
            popad
            popfd

            mov  eax, [ebp - 0x1C4]
            push eax
            call MapFilters1Rebuild
            add  esp, 4
            jmp  [g_RetAddr_MapFilters1]
        }
    }

    // -----------------------------------------------------------------------
    // Map Filters 2/8
    // Site: 0x00752A82
    // -----------------------------------------------------------------------
    void __declspec(naked) __cdecl Trampoline_MapFilters2()
    {
        static const char* name = "Trampoline_MapFilters2";
        __asm
        {
            pushfd
            pushad
            push name
            call LogHit
            add  esp, 4
            popad
            popfd

            lea  eax, [ebp + 0x8]
            push eax
            push ecx
            call MapFilters2Filter
            add  esp, 8
            jmp  [g_RetAddr_MapFilters2]
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

        pushad
        push ebp
        push kTraceMapFilters5
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

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
        push 0x0089E8C8
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

        pushad
        push ebp
        push kTraceMapFilters7
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

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

        pushad
        push ebp
        push kTraceMapFilters8
        call TraceMapRefreshSiteFrame
        add  esp, 8
        popad

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
// Stub mirrors the reference patch: call 0x481EA0, then original 0x481AF0,
// then jump
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
// Joiner Event Hook
// Site: 0x0073F430
// Original: CALL 0x00742560
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_JoinerEventHook()
{
    static const char* name = "Trampoline_JoinerEventHook";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        call dword ptr [g_BZRFnPtr_JoinerEventOriginal]

        mov  eax, [ebp + 0x10]
        push eax
        mov  eax, [ebp + 0x0C]
        push eax
        mov  eax, [ebp + 0x08]
        push eax
        call HandleJoinerEvent
        add  esp, 12
        jmp  [g_RetAddr_JoinerEventHook]
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

// -----------------------------------------------------------------------
// AutoSave Load Button Hook
// Site: 0x0078B45A
// Replays: mov eax, [0x0091830C]
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_AutoSaveLoadButtonHook()
{
    static const char* name = "Trampoline_AutoSaveLoadButtonHook";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        mov  eax, [0x0091830C]
        pushad
        push ebp
        call AutoSaveLoadButtonCreateFromFrame
        add  esp, 4
        popad
        jmp  [g_RetAddr_AutoSaveLoadHook]
    }
}

void __declspec(naked) __cdecl Trampoline_RestartMissionPauseHook()
{
    __asm
    {
        jmp RestartMissionPauseHook
    }
}

void __declspec(naked) __cdecl Trampoline_RestartMissionFailureHook()
{
    __asm
    {
        jmp RestartMissionFailureHook
    }
}

// -----------------------------------------------------------------------
// TurretCraft aim pitch multiplier
// Site: 0x005F1838
// Original bytes: movss xmm0, [0x008A2584]  (0.5f)
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_TurretCraftAimPitchMultiplier()
{
    __asm
    {
        movss xmm0, dword ptr [g_TurretAimPitchMultiplier]
        jmp   [g_RetAddr_TurretCraftAimPitchMultiplier]
    }
}

// -----------------------------------------------------------------------
// TurretTank aim pitch multiplier
// Site: 0x005F561A
// Original bytes: movss xmm0, [0x008A2584]  (0.5f)
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_TurretTankAimPitchMultiplier()
{
    __asm
    {
        movss xmm0, dword ptr [g_TurretAimPitchMultiplier]
        jmp   [g_RetAddr_TurretTankAimPitchMultiplier]
    }
}

// -----------------------------------------------------------------------
// Team under-attack alert hooks
// Sites:
//   0x00494D35
//   0x0050E6DD
// Original block:
//   compare against 0x009173D0, play "cgrowl.wav", then set next alert time.
// We replace the whole block so the shim can honor campaign persistent config.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_UnderAttackAlertHook1()
{
    __asm
    {
        pushfd
        pushad
        push dword ptr [ebp - 1B8h]
        call HandleUnderAttackAlert
        add  esp, 4
        popad
        popfd
        jmp  [g_RetAddr_UnderAttackAlertHook1]
    }
}

void __declspec(naked) __cdecl Trampoline_UnderAttackAlertHook2()
{
    __asm
    {
        pushfd
        pushad
        push dword ptr [ebp - 1D0h]
        call HandleUnderAttackAlert
        add  esp, 4
        popad
        popfd
        jmp  [g_RetAddr_UnderAttackAlertHook2]
    }
}

void __declspec(naked) __cdecl Trampoline_OffensiveAttackRevealHook()
{
    __asm
    {
        mov  ecx, [ebp - 8]
        mov  edx, [ebp - 8]
        mov  eax, [edx + 1Ch]
        mov  [ecx + 24h], eax

        pushfd
        pushad
        push dword ptr [ebp - 8]
        call RevealProcessOwnerPerceivedTeamOnAttackStateEntry
        add  esp, 4
        popad
        popfd

        jmp  [g_RetAddr_OffensiveAttackRevealHook]
    }
}

void __declspec(naked) __cdecl Trampoline_TurretTankAttackRevealHook()
{
    __asm
    {
        mov  edx, [ebp - 8]
        mov  eax, [ebp - 8]
        mov  ecx, [eax + 1Ch]
        mov  [edx + 24h], ecx

        pushfd
        pushad
        push dword ptr [ebp - 8]
        call RevealProcessOwnerPerceivedTeamOnAttackStateEntry
        add  esp, 4
        popad
        popfd

        jmp  [g_RetAddr_TurretTankAttackRevealHook]
    }
}

// -----------------------------------------------------------------------
// HoverCraft Engine Flame Emit Hook
// Sites:
//   0x004EAD77
//   0x004EAFDE
// Original target:
//   EngineFlame::AddFlame(this=ecx, transform, scale)
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_EngineFlameHoverCraftEmit()
{
    __asm
    {
        mov  eax, [esp + 4]
        mov  edx, [esp + 8]
        push dword ptr [ebp - 0x698]
        push edx
        push eax
        push ecx
        call EngineFlameHoverCraftEmitHook
        add  esp, 16
        ret  8
    }
}

// -----------------------------------------------------------------------
// Artillery Weapon Mask Trace
// Site: first internal call inside ArtilleryProcess::DoAttack
// Replays: original helper call via g_BZRFnPtr_ArtilleryMaskTraceOriginal
// Purpose: temporary RE instrumentation to log process->me weapon-mask state
// without changing behavior.
// -----------------------------------------------------------------------
void __declspec(naked) __cdecl Trampoline_ArtilleryMaskTrace()
{
    static const char* name = "Trampoline_ArtilleryMaskTrace";
    __asm
    {
        pushfd
        pushad
        push name
        call LogHit
        add  esp, 4
        popad
        popfd

        pushfd
        pushad
        mov  eax, [ebp - 4]
        push eax
        call TraceArtilleryMaskFromProcess
        add  esp, 4
        popad
        popfd

        mov  ecx, [ebp - 4]
        call [g_BZRFnPtr_ArtilleryMaskTraceOriginal]
        jmp  [g_RetAddr_ArtilleryMaskTrace]
    }
}

void __declspec(naked) __cdecl Trampoline_DecodedWeaponMaskBias()
{
    __asm
    {
        push ecx
        call ApplyWeaponMaskCarrierBiasForCraft
        pop  ecx
        mov  eax, [ecx + 0x210]
        xor  eax, 0x33333333
        ret
    }
}

void __declspec(naked) __cdecl Trampoline_RawWeaponMaskBias()
{
    __asm
    {
        push ecx
        call ApplyWeaponMaskCarrierBiasForCraft
        pop  ecx
        mov  eax, [ecx + 0x210]
        ret
    }
}

} // namespace BZROpenShim
