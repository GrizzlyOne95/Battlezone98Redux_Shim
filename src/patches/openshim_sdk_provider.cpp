// OpenShim SDK provider.
//
// This is the runtime side of the export boundary: winmm.dll exports thunks,
// and this table is what they forward to. It belongs with the OpenShim
// runtime, so when the runtime moves to plugins/openshim.dll this file moves
// with it and the bootstrap picks the table up through
// OpenShimSdkProvider_GetTable instead of the direct call below.
//
// The 52 bodies below were lifted verbatim out of winmm_proxy.cpp, which now
// holds only real WinMM forwarding. That is what breaks the
// winmm_proxy.cpp -> bzr_hooks.cpp dependency: the marshalling that needed
// bzr_hooks lives here, on the runtime side, instead of in the proxy.

#include "openshim_sdk_bridge.h"
#include "winmm_proxy.h"
#include "bzr_hooks.h"
#include "shim_log.h"
#include <cstdio>

namespace
{
    void LogHudBridgeCall(const char* functionName, const char* spriteName)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "%s sprite=%s",
            functionName ? functionName : "<null>",
            spriteName ? spriteName : "<null>");
    }

    void LogHudBridgeResult(const char* functionName, const char* spriteName, BOOL result)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "%s sprite=%s => %s",
            functionName ? functionName : "<null>",
            spriteName ? spriteName : "<null>",
            result ? "true" : "false");
    }
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnderAttackAlertMode(int mode)
{
    return BZROpenShim::SetUnderAttackAlertModeFromBridge(mode) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetTargetReticlePopupMode(int mode)
{
    return BZROpenShim::SetTargetReticlePopupModeFromBridge(mode) ? TRUE : FALSE;
}

extern "C" DWORD WINAPI OpenShimImpl_GetUnitVoThrottle()
{
    return BZROpenShim::GetUnitVoThrottleFromBridge();
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnitVoThrottle(DWORD milliseconds)
{
    return BZROpenShim::SetUnitVoThrottleFromBridge(milliseconds) ? TRUE : FALSE;
}

extern "C" DWORD WINAPI OpenShimImpl_GetUnitVoQueueDepth()
{
    return BZROpenShim::GetUnitVoQueueDepthFromBridge();
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnitVoQueueDepth(DWORD depth)
{
    return BZROpenShim::SetUnitVoQueueDepthFromBridge(depth) ? TRUE : FALSE;
}

extern "C" DWORD WINAPI OpenShimImpl_GetUnitVoQueueStaleMs()
{
    return BZROpenShim::GetUnitVoQueueStaleMsFromBridge();
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnitVoQueueStaleMs(DWORD milliseconds)
{
    return BZROpenShim::SetUnitVoQueueStaleMsFromBridge(milliseconds) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetUnitVoMuted()
{
    return BZROpenShim::GetUnitVoMutedFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnitVoMuted(BOOL muted)
{
    return BZROpenShim::SetUnitVoMutedFromBridge(muted != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetBomberAiRangeEnabled(BOOL enabled)
{
    return BZROpenShim::SetBomberAiRangeEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetHowitzerVolleyEnabled(BOOL enabled)
{
    return BZROpenShim::SetHowitzerVolleyEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetWeaponMaskCarrierBiasEnabled(BOOL enabled)
{
    return BZROpenShim::SetWeaponMaskCarrierBiasEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetAiOdfGameplayTuningEnabled(BOOL enabled)
{
    return BZROpenShim::SetAiOdfGameplayTuningEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetAiUnitTuning(void* objectPtr,
                                                        float engageRange,
                                                        float weaponRangeMin,
                                                        float retargetPeriod)
{
    return BZROpenShim::SetAiUnitTuningFromBridge(objectPtr, engageRange, weaponRangeMin, retargetPeriod)
               ? TRUE
               : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetAiUnitTuningV2(void* objectPtr,
                                                          float engageRange,
                                                          float weaponRangeMin,
                                                          float retargetPeriod,
                                                          float kiteDesiredRange,
                                                          float kiteEnterRange,
                                                          float kiteExitRange,
                                                          BOOL kitePreserveLos)
{
    return BZROpenShim::SetAiUnitTuningFromBridge(objectPtr,
                                                  engageRange,
                                                  weaponRangeMin,
                                                  retargetPeriod,
                                                  kiteDesiredRange,
                                                  kiteEnterRange,
                                                  kiteExitRange,
                                                  kitePreserveLos != FALSE)
               ? TRUE
               : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetAiUnitTuningV3(void* objectPtr,
                                                          float engageRange,
                                                          float weaponRangeMin,
                                                          float retargetPeriod,
                                                          float kiteDesiredRange,
                                                          float kiteEnterRange,
                                                          float kiteExitRange,
                                                          BOOL kitePreserveLos,
                                                          float kiteStrafe,
                                                          float kiteSwitchPeriod)
{
    return BZROpenShim::SetAiUnitTuningFromBridge(objectPtr,
                                                  engageRange,
                                                  weaponRangeMin,
                                                  retargetPeriod,
                                                  kiteDesiredRange,
                                                  kiteEnterRange,
                                                  kiteExitRange,
                                                  kitePreserveLos != FALSE,
                                                  kiteStrafe,
                                                  kiteSwitchPeriod)
               ? TRUE
               : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_ClearAiUnitTuning(void* objectPtr)
{
    return BZROpenShim::ClearAiUnitTuningFromBridge(objectPtr) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_ClearAllAiUnitTuning()
{
    return BZROpenShim::ClearAllAiUnitTuningFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetTurretAimPitchEnabled(BOOL enabled)
{
    return BZROpenShim::SetTurretAimPitchEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetAttackRevealEnabled(BOOL enabled)
{
    return BZROpenShim::SetAttackRevealEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetRawMouseInputEnabled()
{
    return BZROpenShim::GetRawMouseInputEnabledFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetRawMouseInputEnabled(BOOL enabled)
{
    return BZROpenShim::SetRawMouseInputEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetJumpSnipeCrouchEnabled(BOOL enabled)
{
    return BZROpenShim::SetJumpSnipeCrouchEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetShotConvergence()
{
    return BZROpenShim::GetShotConvergenceFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetShotConvergence(BOOL enabled)
{
    return BZROpenShim::SetShotConvergenceFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetPlayerReticleShotConvergence()
{
    return BZROpenShim::GetPlayerReticleShotConvergenceFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetPlayerReticleShotConvergence(BOOL enabled)
{
    return BZROpenShim::SetPlayerReticleShotConvergenceFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" float WINAPI OpenShimImpl_GetSmartReticleRange()
{
    return BZROpenShim::GetSmartReticleRangeFromBridge();
}

extern "C" BOOL WINAPI OpenShimImpl_SetSmartReticleRange(float range)
{
    return BZROpenShim::SetSmartReticleRangeFromBridge(range) ? TRUE : FALSE;
}

extern "C" float WINAPI OpenShimImpl_GetRadarSizeScale()
{
    return BZROpenShim::GetRadarSizeScaleFromBridge();
}

extern "C" BOOL WINAPI OpenShimImpl_SetRadarSizeScale(float scale)
{
    return BZROpenShim::SetRadarSizeScaleFromBridge(scale) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetScrapPilotHudTopLefts(
    int* scrapLeft, int* scrapTop, int* pilotLeft, int* pilotTop)
{
    return BZROpenShim::GetScrapPilotHudTopLeftsFromBridge(
        scrapLeft, scrapTop, pilotLeft, pilotTop) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetScrapPilotHudTopLefts(
    int scrapLeft, int scrapTop, int pilotLeft, int pilotTop)
{
    return BZROpenShim::SetScrapPilotHudTopLeftsFromBridge(
        scrapLeft, scrapTop, pilotLeft, pilotTop) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_RestoreScrapPilotHudStock()
{
    return BZROpenShim::RestoreScrapPilotHudStockFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetGlobalTurbo()
{
    return BZROpenShim::GetGlobalTurboFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetGlobalTurbo(BOOL enabled)
{
    return BZROpenShim::SetGlobalTurboFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_HasUnitTurboHooks()
{
    return BZROpenShim::HasUnitTurboHooksFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetUnitTurbo(DWORD handle)
{
    return BZROpenShim::GetUnitTurboFromBridge(handle) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_SetUnitTurbo(DWORD handle, BOOL enabled)
{
    return BZROpenShim::SetUnitTurboFromBridge(handle, enabled != FALSE) ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_ResetMissionHookOverrides()
{
    return BZROpenShim::ResetMissionHookOverridesFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_IsMissionSimulationActive()
{
    return BZROpenShim::IsMissionSimulationActiveFromBridge() ? TRUE : FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetHudSpriteRect(LPCSTR name, int* x, int* y, int* w, int* h)
{
    LogHudBridgeCall("OpenShimGetHudSpriteRect", name);
    const BOOL result = BZROpenShim::GetHudSpriteRectFromBridge(name, x, y, w, h) ? TRUE : FALSE;
    if (result)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "OpenShimGetHudSpriteRect sprite=%s => true rect=(%d,%d,%d,%d)",
            name ? name : "<null>",
            x ? *x : 0,
            y ? *y : 0,
            w ? *w : 0,
            h ? *h : 0);
    }
    else
    {
        LogHudBridgeResult("OpenShimGetHudSpriteRect", name, result);
    }
    return result;
}

extern "C" BOOL WINAPI OpenShimImpl_SetHudSpriteRect(LPCSTR name, int x, int y, int w, int h)
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimSetHudSpriteRect sprite=%s rect=(%d,%d,%d,%d)",
        name ? name : "<null>",
        x,
        y,
        w,
        h);
    const BOOL result = BZROpenShim::SetHudSpriteRectFromBridge(name, x, y, w, h) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimSetHudSpriteRect", name, result);
    return result;
}

extern "C" BOOL WINAPI OpenShimImpl_SetHudSpriteVisible(LPCSTR name, BOOL visible)
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimSetHudSpriteVisible sprite=%s visible=%s",
        name ? name : "<null>",
        visible ? "true" : "false");
    const BOOL result = BZROpenShim::SetHudSpriteVisibleFromBridge(name, visible != FALSE) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimSetHudSpriteVisible", name, result);
    return result;
}

extern "C" BOOL WINAPI OpenShimImpl_RestoreHudSprite(LPCSTR name)
{
    LogHudBridgeCall("OpenShimRestoreHudSprite", name);
    const BOOL result = BZROpenShim::RestoreHudSpriteFromBridge(name) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimRestoreHudSprite", name, result);
    return result;
}

extern "C" BOOL WINAPI OpenShimImpl_RestoreAllHudSprites()
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimRestoreAllHudSprites");
    const BOOL result = BZROpenShim::RestoreAllHudSpritesFromBridge() ? TRUE : FALSE;
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimRestoreAllHudSprites => %s",
        result ? "true" : "false");
    return result;
}

extern "C" BOOL WINAPI OpenShimImpl_SetMusicTrack(int index)
{
    typedef void (__cdecl* StartMusicFn)(long, int);
    static StartMusicFn pStartMusic = reinterpret_cast<StartMusicFn>(0x00406670);

    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "music",
        "OpenShimSetMusicTrack index=%d",
        index);

    __try
    {
        pStartMusic(0, index);
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Error,
            "music",
            "OpenShimSetMusicTrack failed to call StartMusic (index=%d)",
            index);
        return FALSE;
    }
}

extern "C" BOOL WINAPI OpenShimImpl_StopMusic()
{
    static bool logged = false;
    if (!logged)
    {
        logged = true;
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "music",
            "OpenShimStopMusic: stub/fail closed");
    }
    return FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_PauseMusic()
{
    static bool logged = false;
    if (!logged)
    {
        logged = true;
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "music",
            "OpenShimPauseMusic: stub/fail closed");
    }
    return FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_ResumeMusic()
{
    static bool logged = false;
    if (!logged)
    {
        logged = true;
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "music",
            "OpenShimResumeMusic: stub/fail closed");
    }
    return FALSE;
}

extern "C" BOOL WINAPI OpenShimImpl_GetMusicTrack(int* outIndex)
{
    static bool logged = false;
    if (!logged)
    {
        logged = true;
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "music",
            "OpenShimGetMusicTrack: stub/fail closed");
    }
    if (outIndex)
    {
        *outIndex = -1;
    }
    return FALSE;
}

// Implementations that live in their own subsystems.
namespace BZROpenShim { extern "C" int32_t __cdecl OpenShimImpl_CaptureDeveloperSnapshot(OpenShimDeveloperSnapshot* outSnapshot); }
extern "C" DWORD WINAPI OpenShimImpl_GetActiveRendererBackend(void);
namespace BZROpenShim { extern "C" const OpenShimApiV2* __cdecl OpenShimImpl_GetApi(uint32_t requestedVersion); }
namespace BZROpenShim { extern "C" uint32_t __cdecl OpenShimImpl_GetBzrDistribution(void); }
extern "C" DWORD WINAPI OpenShimImpl_GetEffectiveRenderProfile(void);
extern "C" UINT WINAPI OpenShimImpl_GetRenderApiVersion(void);
extern "C" DWORD WINAPI OpenShimImpl_GetRenderCapabilities(void);
extern "C" UINT WINAPI OpenShimImpl_GetRenderEffectApiVersion(void);
extern "C" BOOL WINAPI OpenShimImpl_GetRenderEffectStatus(DWORD effectId, BZROpenShim::RenderEffects::Abi::StatusV1* status, DWORD statusSize);
extern "C" DWORD WINAPI OpenShimImpl_GetRequestedContentRenderProfile(void);
extern "C" DWORD WINAPI OpenShimImpl_GetUserRenderProfile(void);
namespace BZROpenShim { extern "C" int32_t __cdecl OpenShimImpl_LogDeveloperSnapshot(void); }
extern "C" DWORD WINAPI OpenShimImpl_RequestRenderProfile(DWORD profileRequest);
extern "C" BOOL WINAPI OpenShimImpl_ResetRenderEffects(void);
namespace BZROpenShim { extern "C" int32_t __cdecl OpenShimImpl_ResolveLocalFirstPersonEntity(void** outEntity, uint64_t* outGeneration); }
extern "C" DWORD WINAPI OpenShimImpl_SetBZRNetNickname(LPCSTR nickname);
extern "C" DWORD WINAPI OpenShimImpl_SetRenderEffectEnabled(DWORD effectId, BOOL enabled);
extern "C" DWORD WINAPI OpenShimImpl_SetRenderEffectFloat(DWORD effectId, DWORD paramId, float value);
extern "C" BOOL WINAPI OpenShimImpl_SupportsRenderProfile(DWORD profile);

namespace
{
    // Legacy v1 C++ API, adapted to the table's plain-C signatures.
    uint32_t __cdecl LegacyGetShimVersion()
    {
        return BZROpenShim::GetShimVersion();
    }
    int32_t __cdecl LegacyIsCompatibleGameVersion()
    {
        return BZROpenShim::IsCompatibleGameVersion() ? 1 : 0;
    }
    int32_t __cdecl LegacyIsPatchingComplete()
    {
        return BZROpenShim::IsPatchingComplete() ? 1 : 0;
    }
    uint32_t __cdecl LegacyGetAppliedPatchCount()
    {
        return BZROpenShim::GetAppliedPatchCount();
    }
    uint32_t __cdecl LegacyGetBzrDistribution()
    {
        return static_cast<uint32_t>(BZROpenShim::GetBzrDistribution());
    }
}

namespace
{
    // Static, so installing it is a pointer store with no allocation and no
    // loader work -- safe to do from DllMain while this TU still ships
    // inside winmm.dll.
    const OpenShimSdkProviderTable g_ProviderTable = {
        .structSize = sizeof(OpenShimSdkProviderTable),
        .OpenShimImpl_CaptureDeveloperSnapshot = BZROpenShim::OpenShimImpl_CaptureDeveloperSnapshot,
        .OpenShimImpl_ClearAiUnitTuning = OpenShimImpl_ClearAiUnitTuning,
        .OpenShimImpl_ClearAllAiUnitTuning = OpenShimImpl_ClearAllAiUnitTuning,
        .OpenShimImpl_GetActiveRendererBackend = OpenShimImpl_GetActiveRendererBackend,
        .OpenShimImpl_GetApi = BZROpenShim::OpenShimImpl_GetApi,
        .OpenShimImpl_GetBzrDistribution = BZROpenShim::OpenShimImpl_GetBzrDistribution,
        .OpenShimImpl_GetEffectiveRenderProfile = OpenShimImpl_GetEffectiveRenderProfile,
        .OpenShimImpl_GetGlobalTurbo = OpenShimImpl_GetGlobalTurbo,
        .OpenShimImpl_GetHudSpriteRect = OpenShimImpl_GetHudSpriteRect,
        .OpenShimImpl_GetMusicTrack = OpenShimImpl_GetMusicTrack,
        .OpenShimImpl_GetPlayerReticleShotConvergence = OpenShimImpl_GetPlayerReticleShotConvergence,
        .OpenShimImpl_GetRadarSizeScale = OpenShimImpl_GetRadarSizeScale,
        .OpenShimImpl_GetRawMouseInputEnabled = OpenShimImpl_GetRawMouseInputEnabled,
        .OpenShimImpl_GetRenderApiVersion = OpenShimImpl_GetRenderApiVersion,
        .OpenShimImpl_GetRenderCapabilities = OpenShimImpl_GetRenderCapabilities,
        .OpenShimImpl_GetRenderEffectApiVersion = OpenShimImpl_GetRenderEffectApiVersion,
        .OpenShimImpl_GetRenderEffectStatus = OpenShimImpl_GetRenderEffectStatus,
        .OpenShimImpl_GetRequestedContentRenderProfile = OpenShimImpl_GetRequestedContentRenderProfile,
        .OpenShimImpl_GetScrapPilotHudTopLefts = OpenShimImpl_GetScrapPilotHudTopLefts,
        .OpenShimImpl_GetShotConvergence = OpenShimImpl_GetShotConvergence,
        .OpenShimImpl_GetSmartReticleRange = OpenShimImpl_GetSmartReticleRange,
        .OpenShimImpl_GetUnitTurbo = OpenShimImpl_GetUnitTurbo,
        .OpenShimImpl_GetUnitVoMuted = OpenShimImpl_GetUnitVoMuted,
        .OpenShimImpl_GetUnitVoQueueDepth = OpenShimImpl_GetUnitVoQueueDepth,
        .OpenShimImpl_GetUnitVoQueueStaleMs = OpenShimImpl_GetUnitVoQueueStaleMs,
        .OpenShimImpl_GetUnitVoThrottle = OpenShimImpl_GetUnitVoThrottle,
        .OpenShimImpl_GetUserRenderProfile = OpenShimImpl_GetUserRenderProfile,
        .OpenShimImpl_HasUnitTurboHooks = OpenShimImpl_HasUnitTurboHooks,
        .OpenShimImpl_IsMissionSimulationActive = OpenShimImpl_IsMissionSimulationActive,
        .OpenShimImpl_LogDeveloperSnapshot = BZROpenShim::OpenShimImpl_LogDeveloperSnapshot,
        .OpenShimImpl_PauseMusic = OpenShimImpl_PauseMusic,
        .OpenShimImpl_RequestRenderProfile = OpenShimImpl_RequestRenderProfile,
        .OpenShimImpl_ResetMissionHookOverrides = OpenShimImpl_ResetMissionHookOverrides,
        .OpenShimImpl_ResetRenderEffects = OpenShimImpl_ResetRenderEffects,
        .OpenShimImpl_ResolveLocalFirstPersonEntity = BZROpenShim::OpenShimImpl_ResolveLocalFirstPersonEntity,
        .OpenShimImpl_RestoreAllHudSprites = OpenShimImpl_RestoreAllHudSprites,
        .OpenShimImpl_RestoreHudSprite = OpenShimImpl_RestoreHudSprite,
        .OpenShimImpl_RestoreScrapPilotHudStock = OpenShimImpl_RestoreScrapPilotHudStock,
        .OpenShimImpl_ResumeMusic = OpenShimImpl_ResumeMusic,
        .OpenShimImpl_SetAiOdfGameplayTuningEnabled = OpenShimImpl_SetAiOdfGameplayTuningEnabled,
        .OpenShimImpl_SetAiUnitTuning = OpenShimImpl_SetAiUnitTuning,
        .OpenShimImpl_SetAiUnitTuningV2 = OpenShimImpl_SetAiUnitTuningV2,
        .OpenShimImpl_SetAiUnitTuningV3 = OpenShimImpl_SetAiUnitTuningV3,
        .OpenShimImpl_SetAttackRevealEnabled = OpenShimImpl_SetAttackRevealEnabled,
        .OpenShimImpl_SetBZRNetNickname = OpenShimImpl_SetBZRNetNickname,
        .OpenShimImpl_SetBomberAiRangeEnabled = OpenShimImpl_SetBomberAiRangeEnabled,
        .OpenShimImpl_SetGlobalTurbo = OpenShimImpl_SetGlobalTurbo,
        .OpenShimImpl_SetHowitzerVolleyEnabled = OpenShimImpl_SetHowitzerVolleyEnabled,
        .OpenShimImpl_SetHudSpriteRect = OpenShimImpl_SetHudSpriteRect,
        .OpenShimImpl_SetHudSpriteVisible = OpenShimImpl_SetHudSpriteVisible,
        .OpenShimImpl_SetJumpSnipeCrouchEnabled = OpenShimImpl_SetJumpSnipeCrouchEnabled,
        .OpenShimImpl_SetMusicTrack = OpenShimImpl_SetMusicTrack,
        .OpenShimImpl_SetPlayerReticleShotConvergence = OpenShimImpl_SetPlayerReticleShotConvergence,
        .OpenShimImpl_SetRadarSizeScale = OpenShimImpl_SetRadarSizeScale,
        .OpenShimImpl_SetRawMouseInputEnabled = OpenShimImpl_SetRawMouseInputEnabled,
        .OpenShimImpl_SetRenderEffectEnabled = OpenShimImpl_SetRenderEffectEnabled,
        .OpenShimImpl_SetRenderEffectFloat = OpenShimImpl_SetRenderEffectFloat,
        .OpenShimImpl_SetScrapPilotHudTopLefts = OpenShimImpl_SetScrapPilotHudTopLefts,
        .OpenShimImpl_SetShotConvergence = OpenShimImpl_SetShotConvergence,
        .OpenShimImpl_SetSmartReticleRange = OpenShimImpl_SetSmartReticleRange,
        .OpenShimImpl_SetTargetReticlePopupMode = OpenShimImpl_SetTargetReticlePopupMode,
        .OpenShimImpl_SetTurretAimPitchEnabled = OpenShimImpl_SetTurretAimPitchEnabled,
        .OpenShimImpl_SetUnderAttackAlertMode = OpenShimImpl_SetUnderAttackAlertMode,
        .OpenShimImpl_SetUnitTurbo = OpenShimImpl_SetUnitTurbo,
        .OpenShimImpl_SetUnitVoMuted = OpenShimImpl_SetUnitVoMuted,
        .OpenShimImpl_SetUnitVoQueueDepth = OpenShimImpl_SetUnitVoQueueDepth,
        .OpenShimImpl_SetUnitVoQueueStaleMs = OpenShimImpl_SetUnitVoQueueStaleMs,
        .OpenShimImpl_SetUnitVoThrottle = OpenShimImpl_SetUnitVoThrottle,
        .OpenShimImpl_SetWeaponMaskCarrierBiasEnabled = OpenShimImpl_SetWeaponMaskCarrierBiasEnabled,
        .OpenShimImpl_StopMusic = OpenShimImpl_StopMusic,
        .OpenShimImpl_SupportsRenderProfile = OpenShimImpl_SupportsRenderProfile,
        .legacyGetShimVersion = LegacyGetShimVersion,
        .legacyIsCompatibleGameVersion = LegacyIsCompatibleGameVersion,
        .legacyIsPatchingComplete = LegacyIsPatchingComplete,
        .legacyGetAppliedPatchCount = LegacyGetAppliedPatchCount,
        .legacyGetBzrDistribution = LegacyGetBzrDistribution,
    };
}

extern "C" __declspec(dllexport) const OpenShimSdkProviderTable* __cdecl
OpenShimSdkProvider_GetTable(void)
{
    return &g_ProviderTable;
}

namespace BZROpenShim::SdkProvider
{
    // Transitional: the provider is still linked into winmm.dll, so the
    // bootstrap installs it directly. Once this file ships in
    // plugins/openshim.dll, delete this and have the bootstrap call
    // SdkBridge::InstallProviderFromModule(plugin) after the plugin loads.
    bool InstallBuiltIn()
    {
        return BZROpenShim::SdkBridge::InstallProvider(&g_ProviderTable);
    }
}
