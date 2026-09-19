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

// Reading the export table, this currently appears as
//   OpenShimGetRenderEffectApiVersion = _OpenShimGetRenderApiVersion@0
// sharing an RVA with the render-profile version export. That is not a
// mis-wired .def: both functions compile to `mov eax, 1; ret`, so /OPT:ICF
// folds them. Behaviour is correct, and they separate on their own as soon as
// either version constant moves. Do not "fix" it by perturbing the code.
extern "C" UINT WINAPI OpenShimGetRenderEffectApiVersion()
{
    return static_cast<UINT>(GetApiVersion());
}

extern "C" DWORD WINAPI OpenShimSetRenderEffectEnabled(DWORD effectId, BOOL enabled)
{
    return static_cast<DWORD>(
        SetEnabled(static_cast<uint32_t>(effectId), enabled != FALSE));
}

extern "C" DWORD WINAPI OpenShimSetRenderEffectFloat(DWORD effectId, DWORD paramId, float value)
{
    return static_cast<DWORD>(
        SetFloat(static_cast<uint32_t>(effectId), static_cast<uint32_t>(paramId), value));
}

// `statusSize` is what the CALLER believes the struct is. It is written into
// the struct before the call is forwarded so a future, larger StatusV2 can be
// distinguished from a V1 without another export.
extern "C" BOOL WINAPI OpenShimGetRenderEffectStatus(
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
extern "C" BOOL WINAPI OpenShimResetRenderEffects()
{
    Reset();
    return TRUE;
}
