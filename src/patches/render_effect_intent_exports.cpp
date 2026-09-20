// winmm bridge exports for the render-effect intent layer.
//
// This file is only marshalling: Win32 types in, plain types out, straight
// into src/engine/render_effect_intent.cpp. All of the decision-making lives
// there so it can be tested without Windows. See include/render_effect_intent.h
// for the contract, and note that no effect has a renderer implementation yet -
// these exports exist so the mission-facing side can be built and shipped
// against a stable ABI before the renderer work lands.

#include "render_effect_intent.h"

#include <Windows.h>

namespace
{
    using namespace BZROpenShim::RenderEffects;
}

// This used to share an RVA with the render-profile version export, showing up
// as `OpenShimGetRenderEffectApiVersion = _OpenShimGetRenderApiVersion@0`:
// both compiled to `mov eax, 1; ret`, so /OPT:ICF folded them. That was always
// correct, just confusing to read.
//
// It no longer happens. The exported names are forwarding thunks in
// openshim_sdk_thunks.cpp now, and each one loads a different provider-table
// slot, so there is nothing identical left to fold. The implementations below
// may still fold with each other, but they are not exported, so the export
// table shows two distinct RVAs. Either way, do not perturb the code to
// influence it.
extern "C" UINT WINAPI OpenShimImpl_GetRenderEffectApiVersion()
{
    return static_cast<UINT>(GetApiVersion());
}

extern "C" DWORD WINAPI OpenShimImpl_SetRenderEffectEnabled(DWORD effectId, BOOL enabled)
{
    return static_cast<DWORD>(
        SetEnabled(static_cast<uint32_t>(effectId), enabled != FALSE));
}

extern "C" DWORD WINAPI OpenShimImpl_SetRenderEffectFloat(DWORD effectId, DWORD paramId, float value)
{
    return static_cast<DWORD>(
        SetFloat(static_cast<uint32_t>(effectId), static_cast<uint32_t>(paramId), value));
}

// `statusSize` is what the CALLER believes the struct is. It is written into
// the struct before the call is forwarded so a future, larger StatusV2 can be
// distinguished from a V1 without another export.
extern "C" BOOL WINAPI OpenShimImpl_GetRenderEffectStatus(
    DWORD effectId,
    Abi::StatusV1* status,
    DWORD statusSize)
{
    if (status == nullptr || statusSize < sizeof(Abi::StatusV1))
    {
        return FALSE;
    }

    status->size = static_cast<uint32_t>(statusSize);
    return GetStatus(static_cast<uint32_t>(effectId), status) ? TRUE : FALSE;
}

// Mission-scoped teardown. A companion calls this when a mission ends so one
// mission's renderer requests cannot leak into the next.
extern "C" BOOL WINAPI OpenShimImpl_ResetRenderEffects()
{
    Reset();
    return TRUE;
}
