#pragma once

#include <cstdint>
#include "bzr_string.h"

namespace BZROpenShim
{
    // Stable status returned by the optional OpenShimSetBZRNetNickname bridge.
    // Keep numeric values stable because companion DLLs resolve the C export
    // dynamically and intentionally do not link against OpenShim internals.
    enum class BzrNetNicknameResult : uint32_t
    {
        AppliedLive = 0,
        StoredForNextConnection = 1,
        InvalidNickname = 2,
        UnsupportedBuild = 3,
        NativeStateInvalid = 4,
        PersistenceFailed = 5,
    };

    BzrNetNicknameResult SetBzrNetNicknameFromBridge(const char* nickname);
    // Runtime-resolved BZR pointers and helpers.
    void ResolveBzrHooks(bool isSteam);
    void RetryDeferredRuntimeHooks();
    bool AreInputBindingUiHooksInstalled();
    bool AreRequiredDeferredRuntimeHooksInstalled();
    void InitBzrHookStrings();
    void SetProducerBuildMenuOriginal(void* target);
    void FlushChunkFragmentEventsForShutdown();

    // Wire up the GOG-build player-handle lookup. Only call this once the exact
    // GOG executable has been confirmed (e.g. by SHA-256), because the address
    // is a build constant. Without it TryGetLocalPlayerWorldPosition below can
    // never succeed unless the jump-sniping probe happens to be enabled.
    void ResolveLocalPlayerLookupForVerifiedGogBuild();

    // Local-player world position from the simulation, not the render camera.
    // False when the player handle or object is not resolvable yet.
    bool TryGetLocalPlayerWorldPosition(float& x, float& y, float& z);

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
    // 1.5 used a left/right pair; OnClick* advances, OnClickPrev* steps back.
    void __cdecl FlagButtonOnClickHost();
    void __cdecl FlagButtonOnClickClient();
    void __cdecl FlagButtonOnClickPrevHost();
    void __cdecl FlagButtonOnClickPrevClient();
    void __cdecl FlagButtonOnHoverHost(void* param);
    void __cdecl FlagButtonOnHoverClient(void* param);
    void __cdecl NicknameEntryOnEnterHost();
    void __cdecl NicknameEntryOnEnterClient();
    void __cdecl NicknameEditOnClickHost();
    void __cdecl NicknameEditOnClickClient();
    void __cdecl NetRouteRefreshHost();
    void __cdecl NetRouteRefreshClient();
    void __cdecl AutoSaveButtonOnClickLoad();
    void AutoSaveLoadButtonCreateFromFrame(void* frameBase);
    void __fastcall RestartMissionPauseHook(void* thisPtr);
    void __fastcall RestartMissionFailureHook(void* thisPtr);
    void __cdecl EngineFlameHoverCraftEmitHook(void* managerPtr, const void* transform, uint32_t scaleBits, void* craftPtr);
    void __fastcall EngineFlameControlHook(void* thisPtr, void* edx);
    void __fastcall EngineFlameSubmitHook(void* thisPtr, void* edx, void* camera);
    void __fastcall ChunkEffectSimulateHook(void* thisPtr, void* edx, float dt);
    void __fastcall DynamicGeometryPrepareHook(void* thisPtr, void* edx);
    void __fastcall DynamicGeometrySetSquaredViewDepthHook(
        void* thisPtr, void* edx, float squaredViewDepth);
    void __fastcall DynamicGeometryAddRenderableHook(
        void* renderQueue, void* edx, void* renderable, uint8_t queueGroup);
    void __fastcall LegacyWorldUpdateRenderQueueHook(void* thisPtr, void* edx, void* renderQueue);
    void __cdecl HandleUnderAttackAlert(float currentTime);
    void __fastcall DamageRevealProbeHook(void* victim, void* edx, void* damage);
    void PrimeUnderAttackAlertConfig();
    bool SetUnderAttackAlertModeFromBridge(int mode);
    bool SetBomberAiRangeEnabledFromBridge(bool enabled);
    bool SetHowitzerVolleyEnabledFromBridge(bool enabled);
    bool SetWeaponMaskCarrierBiasEnabledFromBridge(bool enabled);
    bool SetAiOdfGameplayTuningEnabledFromBridge(bool enabled);
    bool SetAiUnitTuningFromBridge(void* objectPtr,
                                   float engageRange,
                                   float weaponRangeMin,
                                   float retargetPeriod,
                                   float kiteDesiredRange = -1.0f,
                                   float kiteEnterRange = -1.0f,
                                   float kiteExitRange = -1.0f,
                                   bool kitePreserveLos = false,
                                   float kiteStrafe = -1.0f,
                                   float kiteSwitchPeriod = -1.0f);
    bool ClearAiUnitTuningFromBridge(void* objectPtr);
    bool ClearAllAiUnitTuningFromBridge();
    // One-shot liveness telemetry for the AI-tuning detours (shutdown).
    void ReportAiHookLivenessStats();
    bool SetTurretAimPitchEnabledFromBridge(bool enabled);
    bool SetAttackRevealEnabledFromBridge(bool enabled);
    bool GetRawMouseInputEnabledFromBridge();
    bool SetRawMouseInputEnabledFromBridge(bool enabled);
    bool SetJumpSnipeCrouchEnabledFromBridge(bool enabled);
    bool GetShotConvergenceFromBridge();
    bool SetShotConvergenceFromBridge(bool enabled);
    bool GetPlayerReticleShotConvergenceFromBridge();
    bool SetPlayerReticleShotConvergenceFromBridge(bool enabled);
    float GetSmartReticleRangeFromBridge();
    bool SetSmartReticleRangeFromBridge(float range);
    bool GetScrapPilotHudTopLeftsFromBridge(
        int* scrapLeft, int* scrapTop, int* pilotLeft, int* pilotTop);
    bool SetScrapPilotHudTopLeftsFromBridge(
        int scrapLeft, int scrapTop, int pilotLeft, int pilotTop);
    bool RestoreScrapPilotHudStockFromBridge();
    bool GetGlobalTurboFromBridge();
    bool SetGlobalTurboFromBridge(bool enabled);
    bool HasUnitTurboHooksFromBridge();
    bool GetUnitTurboFromBridge(uint32_t handle);
    bool SetUnitTurboFromBridge(uint32_t handle, bool enabled);
    bool ResetMissionHookOverridesFromBridge();
    float __fastcall TargetReticlePopupRecentHitGetterHook(void* objectPtr, void* edx);
    void __cdecl RevealProcessOwnerPerceivedTeamOnAttackStateEntry(void* processPtr);
    void PrimeTargetReticlePopupConfig();
    bool SetTargetReticlePopupModeFromBridge(int mode);
    uint32_t GetUnitVoThrottleFromBridge();
    bool SetUnitVoThrottleFromBridge(uint32_t milliseconds);
    uint32_t GetUnitVoQueueDepthFromBridge();
    bool SetUnitVoQueueDepthFromBridge(uint32_t depth);
    uint32_t GetUnitVoQueueStaleMsFromBridge();
    bool SetUnitVoQueueStaleMsFromBridge(uint32_t milliseconds);
    bool GetUnitVoMutedFromBridge();
    bool SetUnitVoMutedFromBridge(bool muted);
    bool GetHudSpriteRectFromBridge(const char* name, int* outX, int* outY, int* outW, int* outH);
    bool SetHudSpriteRectFromBridge(const char* name, int x, int y, int w, int h);
    bool SetHudSpriteVisibleFromBridge(const char* name, bool visible);
    bool RestoreHudSpriteFromBridge(const char* name);
    bool RestoreAllHudSpritesFromBridge();

    // Custom /help + /ban command intercept.
    bool __cdecl HandleCommandHelpBan(uint16_t id, const char* cmd);
    void __cdecl HandleJoinerEvent(uint32_t lobby, uint32_t member, int changes);

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
    // AI weapon-mask hardpoint selection. Each replaces one call to a
    // __thiscall engine routine; the trampolines supply the third argument from
    // the patched routine's own stack frame.
    void* __cdecl OpenShimArtillerySelectWeapon(void* carrier, int slot, void* process);
    void* __cdecl OpenShimLayMinesGetWeapon(void* carrier, int slot, void* task);
    void __cdecl OpenShimLayMinesSetSelected(void* carrier, uint32_t mask, void* task);
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

    // Map filter state flags recovered from BZR.exe create-screen analysis.
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
