// Generated from the shipped export definitions -- the single source of truth
// for winmm.dll's OpenShim* surface. Every consumer of this list (the export
// thunks, the provider table, and the drift test) expands the same entries, so
// a signature cannot disagree between them.
//
// OPENSHIM_SDK_EXPORT(ret, callconv, exported name, impl name, (params), (args), value-when-unavailable)
//
// OPENSHIM_SDK_EXPORT_NS covers the five exports declared inside namespace
// BZROpenShim in the public header; they are __cdecl, not WINAPI.

#ifndef OPENSHIM_SDK_EXPORT_NS
#define OPENSHIM_SDK_EXPORT_NS OPENSHIM_SDK_EXPORT
#define OPENSHIM_SDK_EXPORT_NS_WAS_DEFAULTED
#endif

OPENSHIM_SDK_EXPORT_NS(int32_t, __cdecl, OpenShimCaptureDeveloperSnapshot, OpenShimImpl_CaptureDeveloperSnapshot, (BZROpenShim::OpenShimDeveloperSnapshot* outSnapshot), (outSnapshot), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimClearAiUnitTuning, OpenShimImpl_ClearAiUnitTuning, (void* objectPtr), (objectPtr), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimClearAllAiUnitTuning, OpenShimImpl_ClearAllAiUnitTuning, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetActiveRendererBackend, OpenShimImpl_GetActiveRendererBackend, (void), (), 0)
OPENSHIM_SDK_EXPORT_NS(const BZROpenShim::OpenShimApiV2*, __cdecl, OpenShimGetApi, OpenShimImpl_GetApi, (uint32_t requestedVersion), (requestedVersion), nullptr)
OPENSHIM_SDK_EXPORT_NS(uint32_t, __cdecl, OpenShimGetBzrDistribution, OpenShimImpl_GetBzrDistribution, (void), (), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetEffectiveRenderProfile, OpenShimImpl_GetEffectiveRenderProfile, (void), (), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetGlobalTurbo, OpenShimImpl_GetGlobalTurbo, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetHudSpriteRect, OpenShimImpl_GetHudSpriteRect, (LPCSTR name, int* x, int* y, int* w, int* h), (name, x, y, w, h), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetMusicTrack, OpenShimImpl_GetMusicTrack, (int* outIndex), (outIndex), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetPlayerReticleShotConvergence, OpenShimImpl_GetPlayerReticleShotConvergence, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(float, WINAPI, OpenShimGetRadarSizeScale, OpenShimImpl_GetRadarSizeScale, (void), (), 0.0f)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetRawMouseInputEnabled, OpenShimImpl_GetRawMouseInputEnabled, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(UINT, WINAPI, OpenShimGetRenderApiVersion, OpenShimImpl_GetRenderApiVersion, (void), (), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetRenderCapabilities, OpenShimImpl_GetRenderCapabilities, (void), (), 0)
OPENSHIM_SDK_EXPORT(UINT, WINAPI, OpenShimGetRenderEffectApiVersion, OpenShimImpl_GetRenderEffectApiVersion, (void), (), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetRenderEffectStatus, OpenShimImpl_GetRenderEffectStatus, (DWORD effectId, BZROpenShim::RenderEffects::Abi::StatusV1* status, DWORD statusSize), (effectId, status, statusSize), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetRequestedContentRenderProfile, OpenShimImpl_GetRequestedContentRenderProfile, (void), (), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetScrapPilotHudTopLefts, OpenShimImpl_GetScrapPilotHudTopLefts, (int* scrapLeft, int* scrapTop, int* pilotLeft, int* pilotTop), (scrapLeft, scrapTop, pilotLeft, pilotTop), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetShotConvergence, OpenShimImpl_GetShotConvergence, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(float, WINAPI, OpenShimGetSmartReticleRange, OpenShimImpl_GetSmartReticleRange, (void), (), 0.0f)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetUnitTurbo, OpenShimImpl_GetUnitTurbo, (DWORD handle), (handle), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimGetUnitVoMuted, OpenShimImpl_GetUnitVoMuted, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetUnitVoQueueDepth, OpenShimImpl_GetUnitVoQueueDepth, (void), (), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetUnitVoQueueStaleMs, OpenShimImpl_GetUnitVoQueueStaleMs, (void), (), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetUnitVoThrottle, OpenShimImpl_GetUnitVoThrottle, (void), (), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimGetUserRenderProfile, OpenShimImpl_GetUserRenderProfile, (void), (), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimHasUnitTurboHooks, OpenShimImpl_HasUnitTurboHooks, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimIsMissionSimulationActive, OpenShimImpl_IsMissionSimulationActive, (void), (), FALSE)
OPENSHIM_SDK_EXPORT_NS(int32_t, __cdecl, OpenShimLogDeveloperSnapshot, OpenShimImpl_LogDeveloperSnapshot, (void), (), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimPauseMusic, OpenShimImpl_PauseMusic, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimRequestRenderProfile, OpenShimImpl_RequestRenderProfile, (DWORD profileRequest), (profileRequest), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimResetMissionHookOverrides, OpenShimImpl_ResetMissionHookOverrides, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimResetRenderEffects, OpenShimImpl_ResetRenderEffects, (void), (), FALSE)
OPENSHIM_SDK_EXPORT_NS(int32_t, __cdecl, OpenShimResolveLocalFirstPersonEntity, OpenShimImpl_ResolveLocalFirstPersonEntity, (void** outEntity, uint64_t* outGeneration), (outEntity, outGeneration), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimRestoreAllHudSprites, OpenShimImpl_RestoreAllHudSprites, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimRestoreHudSprite, OpenShimImpl_RestoreHudSprite, (LPCSTR name), (name), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimRestoreScrapPilotHudStock, OpenShimImpl_RestoreScrapPilotHudStock, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimResumeMusic, OpenShimImpl_ResumeMusic, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetAiOdfGameplayTuningEnabled, OpenShimImpl_SetAiOdfGameplayTuningEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetAiUnitTuning, OpenShimImpl_SetAiUnitTuning, (void* objectPtr, float engageRange, float weaponRangeMin, float retargetPeriod), (objectPtr, engageRange, weaponRangeMin, retargetPeriod), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetAiUnitTuningV2, OpenShimImpl_SetAiUnitTuningV2, (void* objectPtr, float engageRange, float weaponRangeMin, float retargetPeriod, float kiteDesiredRange, float kiteEnterRange, float kiteExitRange, BOOL kitePreserveLos), (objectPtr, engageRange, weaponRangeMin, retargetPeriod, kiteDesiredRange, kiteEnterRange, kiteExitRange, kitePreserveLos), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetAiUnitTuningV3, OpenShimImpl_SetAiUnitTuningV3, (void* objectPtr, float engageRange, float weaponRangeMin, float retargetPeriod, float kiteDesiredRange, float kiteEnterRange, float kiteExitRange, BOOL kitePreserveLos, float kiteStrafe, float kiteSwitchPeriod), (objectPtr, engageRange, weaponRangeMin, retargetPeriod, kiteDesiredRange, kiteEnterRange, kiteExitRange, kitePreserveLos, kiteStrafe, kiteSwitchPeriod), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetAttackRevealEnabled, OpenShimImpl_SetAttackRevealEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimSetBZRNetNickname, OpenShimImpl_SetBZRNetNickname, (LPCSTR nickname), (nickname), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetBomberAiRangeEnabled, OpenShimImpl_SetBomberAiRangeEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetGlobalTurbo, OpenShimImpl_SetGlobalTurbo, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetHowitzerVolleyEnabled, OpenShimImpl_SetHowitzerVolleyEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetHudSpriteRect, OpenShimImpl_SetHudSpriteRect, (LPCSTR name, int x, int y, int w, int h), (name, x, y, w, h), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetHudSpriteVisible, OpenShimImpl_SetHudSpriteVisible, (LPCSTR name, BOOL visible), (name, visible), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetJumpSnipeCrouchEnabled, OpenShimImpl_SetJumpSnipeCrouchEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetMusicTrack, OpenShimImpl_SetMusicTrack, (int index), (index), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetPlayerReticleShotConvergence, OpenShimImpl_SetPlayerReticleShotConvergence, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetRadarSizeScale, OpenShimImpl_SetRadarSizeScale, (float scale), (scale), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetRawMouseInputEnabled, OpenShimImpl_SetRawMouseInputEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimSetRenderEffectEnabled, OpenShimImpl_SetRenderEffectEnabled, (DWORD effectId, BOOL enabled), (effectId, enabled), 0)
OPENSHIM_SDK_EXPORT(DWORD, WINAPI, OpenShimSetRenderEffectFloat, OpenShimImpl_SetRenderEffectFloat, (DWORD effectId, DWORD paramId, float value), (effectId, paramId, value), 0)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetScrapPilotHudTopLefts, OpenShimImpl_SetScrapPilotHudTopLefts, (int scrapLeft, int scrapTop, int pilotLeft, int pilotTop), (scrapLeft, scrapTop, pilotLeft, pilotTop), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetShotConvergence, OpenShimImpl_SetShotConvergence, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetSmartReticleRange, OpenShimImpl_SetSmartReticleRange, (float range), (range), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetTargetReticlePopupMode, OpenShimImpl_SetTargetReticlePopupMode, (int mode), (mode), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetTurretAimPitchEnabled, OpenShimImpl_SetTurretAimPitchEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnderAttackAlertMode, OpenShimImpl_SetUnderAttackAlertMode, (int mode), (mode), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnitTurbo, OpenShimImpl_SetUnitTurbo, (DWORD handle, BOOL enabled), (handle, enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnitVoMuted, OpenShimImpl_SetUnitVoMuted, (BOOL muted), (muted), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnitVoQueueDepth, OpenShimImpl_SetUnitVoQueueDepth, (DWORD depth), (depth), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnitVoQueueStaleMs, OpenShimImpl_SetUnitVoQueueStaleMs, (DWORD milliseconds), (milliseconds), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetUnitVoThrottle, OpenShimImpl_SetUnitVoThrottle, (DWORD milliseconds), (milliseconds), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSetWeaponMaskCarrierBiasEnabled, OpenShimImpl_SetWeaponMaskCarrierBiasEnabled, (BOOL enabled), (enabled), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimStopMusic, OpenShimImpl_StopMusic, (void), (), FALSE)
OPENSHIM_SDK_EXPORT(BOOL, WINAPI, OpenShimSupportsRenderProfile, OpenShimImpl_SupportsRenderProfile, (DWORD profile), (profile), FALSE)

#ifdef OPENSHIM_SDK_EXPORT_NS_WAS_DEFAULTED
#undef OPENSHIM_SDK_EXPORT_NS
#undef OPENSHIM_SDK_EXPORT_NS_WAS_DEFAULTED
#endif
