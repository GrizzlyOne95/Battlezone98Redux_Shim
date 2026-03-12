#pragma once

#include <cstdint>
#include "bzr_string.h"

namespace BZROpenShim
{
    // Runtime-resolved BZR pointers and helpers.
    void ResolveBzrHooks();
    void InitBzrHookStrings();

    // Vehicle list mod fix helpers (rel32 patch target + helper for jmp stub).
    void __fastcall VehicleListModFix2(void* thisPtr, void* edx, BzrString* name);
    void VehicleListModFix4Helper();

    // Ban button helpers and callbacks.
    void BanButtonCreateHost();
    void BanButtonCreateClient();
    void __cdecl BanButtonOnClickHost();
    void __cdecl BanButtonOnClickClient();
    void __cdecl BanButtonOnHoverHost(void* param);
    void __cdecl BanButtonOnHoverClient(void* param);

    // Shared state for trampolines.
    extern void* g_VehicleListContext;
    extern void* g_VehicleListParam;

    extern void* g_BzrnetHostObj;
    extern void* g_BzrnetClientObj;

    extern void* g_BanParentHost;
    extern void* g_BanParentClient;
    extern void* g_BanButtonHost;
    extern void* g_BanButtonClient;
    extern void* g_BanLabelHost;
    extern void* g_BanLabelClient;

    extern uint32_t g_BanFlag;
    extern float g_BanX;
    extern float g_BanY;

    // Direct call targets for Vehicle Mod Fix 1/4 stub.
    extern void* g_BzrFn_VehicleFixPre;
    extern void* g_BzrFn_VehicleFixOrig;

    // Empty strings used by BZRNET integration calls.
    extern BzrString g_BzrnetLabel1;
    extern BzrString g_BzrnetLabel2;
    extern BzrString g_BzrnetLabel3;
    extern BzrString g_BzrnetLabel4;
}
