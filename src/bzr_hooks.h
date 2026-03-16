#pragma once

#include <cstdint>
#include "bzr_string.h"

namespace BZROpenShim
{
    // Runtime-resolved BZR pointers and helpers.
    void ResolveBzrHooks(bool isSteam);
    void InitBzrHookStrings();
    void SetProducerBuildMenuOriginal(void* target);

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
    void __cdecl AutoSaveButtonOnClickLoad();
    void AutoSaveLoadButtonCreateFromFrame(void* frameBase);
    void __cdecl EngineFlameHoverCraftEmitHook(void* managerPtr, const void* transform, uint32_t scaleBits, void* craftPtr);
    void __fastcall EngineFlameControlHook(void* thisPtr, void* edx);
    void __fastcall EngineFlameSubmitHook(void* thisPtr, void* edx, void* camera);

    // Custom /help + /ban command intercept.
    bool __cdecl HandleCommandHelpBan(uint16_t id, const char* cmd);

    // Map filter helpers (rel32 patch target).
    uint32_t __fastcall MapFilters6Rel32(void* thisPtr, void* edx);
    uint32_t __cdecl ChunkRenderResolveHook(void* objectPtr, uint32_t variant);
    void* __cdecl ProducerBuildMenuCallHook(void* producerPtr, int slot, int flags);
    void __cdecl MapFilterOnScrollUp();
    void __cdecl MapFilterOnScrollDown();
    void __cdecl MapFilters1Rebuild(void* listPtr);
    void __cdecl MapFilters2Filter(void* listPtr, BzrString* filter);
    void __cdecl ApplyWeaponMaskCarrierBiasForCraft(void* craft);
    void __cdecl TraceArtilleryMaskFromProcess(void* process);

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
    extern float g_TurretAimPitchMultiplier;

    // Map filter state flags recovered from the reference patch analysis.
    extern uint8_t g_MapFilterFlag11;
    extern uint8_t g_MapFilterFlag12;
    extern void* g_BzrFn_MapFilter8Check;
    extern void* g_BzrFn_MapFilterCreate;
    extern void* g_MapFilterListPtr;
    extern const char* (__cdecl* g_BzrFn_Localize)(const char* section, const char* key);

    // Direct call targets for Vehicle Mod Fix 1/4 stub.
    extern void* g_BzrFn_VehicleFixPre;
    extern void* g_BzrFn_VehicleFixOrig;

    // Empty strings used by BZRNET integration calls.
    extern BzrString g_BzrnetLabel1;
    extern BzrString g_BzrnetLabel2;
    extern BzrString g_BzrnetLabel3;
    extern BzrString g_BzrnetLabel4;
}
