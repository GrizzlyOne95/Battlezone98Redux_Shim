// Render-effect intent: the boundary between mission intent and renderer
// implementation.
//
// A mission says "I would like SSAO, strength 0.65". OpenShim decides whether
// that is possible on the current renderer and build, owns every D3D11 and
// Ogre resource required to do it, and reports back honestly. Companions never
// receive an SRV, a D3D11 object, an Ogre compositor handle, or a shader name.
//
// This header is the stable contract. It is deliberately free of <Windows.h>,
// of any engine type and of any renderer type, so the whole decision layer can
// be unit tested on a host with no game present. The winmm exports that
// marshal it live in src/patches/render_effect_intent_exports.cpp.
//
// Mirrored independently by ExtraUtilities' src/RenderEffectBridge.h; do not
// link companions against these headers and DO NOT RENUMBER ANYTHING BELOW.
//
// ---------------------------------------------------------------------------
// Current state: this is intent plumbing only.
//
// No effect has a renderer implementation yet - scene depth is still being
// qualified (PR #191, Docs/DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md once it
// lands) - so every effect reports supported = false, reason = NotImplemented.
//
// That is deliberate and it is useful: a mission written against this today
// behaves correctly - it asks, it is told no, it carries on - and starts
// working the moment a provider registers, with no change on either side.
// ---------------------------------------------------------------------------

#pragma once

#include <cstdint>

namespace BZROpenShim::RenderEffects
{
    namespace Abi
    {
        constexpr uint32_t kRenderEffectApiVersion = 1;

        // Effect identifiers. Append only.
        constexpr uint32_t kEffectSsao = 1u;
        constexpr uint32_t kEffectDepthHaze = 2u;
        constexpr uint32_t kEffectSoftParticles = 3u;

        // Parameter identifiers. Semantic, never implementation detail: there
        // is deliberately no way to name a shader constant, a sampler slot or
        // a compositor pass from outside.
        constexpr uint32_t kParamStrength = 1u;
        constexpr uint32_t kParamRadius = 2u;
        constexpr uint32_t kParamFadeStart = 3u;
        constexpr uint32_t kParamFadeEnd = 4u;
        constexpr uint32_t kParamQuality = 5u;

        // Why an effect is in the state it is in. Callers must treat an
        // unrecognised value as "not effective, reason unknown".
        constexpr uint32_t kReasonEffective = 0u;
        constexpr uint32_t kReasonNotRequested = 1u;
        constexpr uint32_t kReasonUnsupportedRenderer = 2u;   // e.g. running DX9
        constexpr uint32_t kReasonSceneDepthUnavailable = 3u; // depth not readable
        constexpr uint32_t kReasonUnsupportedBuild = 4u;      // build not qualified
        constexpr uint32_t kReasonNotImplemented = 5u;        // no provider registered
        constexpr uint32_t kReasonUnknownEffect = 6u;
        constexpr uint32_t kReasonPending = 7u;               // accepted, not yet applied

        // Results of the two setters.
        constexpr uint32_t kResultAccepted = 0u;
        constexpr uint32_t kResultRejectedEffect = 1u;
        constexpr uint32_t kResultRejectedParam = 2u;
        constexpr uint32_t kResultRejectedValue = 3u;

        constexpr uint32_t kStatusVersion = 1u;

        // POD, explicitly sized and versioned, no STL, no pointers. `size` is
        // set by the CALLER to sizeof(StatusV1) so a newer OpenShim can grow
        // this struct without breaking an older companion.
        //
        // The three flags are int32_t rather than bool because this crosses a
        // DLL boundary between independently compiled modules, and Win32 BOOL
        // is what the companion side will be holding.
        struct StatusV1
        {
            uint32_t size;
            uint32_t version;
            int32_t requested;
            int32_t supported;
            int32_t effective;
            uint32_t reasonCode;
        };

        static_assert(sizeof(StatusV1) == 24, "StatusV1 is a fixed 24-byte POD");
    }

    // How a renderer feature plugs itself in.
    //
    // Nothing here is registered today. When the DX11 scene-depth work
    // produces a real SSAO pass, it registers one of these and every layer
    // above - the exports, the companion bridge, the mission script - starts
    // working without an ABI change.
    //
    // Every callback may be invoked from the thread that called the export, so
    // an implementation that must touch renderer state is responsible for
    // deferring to the engine thread itself. Callbacks are invoked WITHOUT the
    // intent lock held, so a provider may call back into this module.
    struct Provider
    {
        // Is this effect possible at all right now? Cheap; called per status
        // query.
        bool (*IsSupported)(void* context) = nullptr;

        // Consulted only when IsSupported() is false, or when supported and
        // requested but not yet effective. Must return one of the kReason*
        // codes; anything else is normalised to kReasonNotImplemented.
        uint32_t (*UnsupportedReason)(void* context) = nullptr;

        // Push the current intent down. Only called when IsSupported().
        void (*ApplyEnabled)(void* context, bool enabled) = nullptr;
        void (*ApplyFloat)(void* context, uint32_t paramId, float value) = nullptr;

        // Is it actually running right now? "Requested and supported" is not
        // the same as "on screen this frame".
        bool (*IsEffective)(void* context) = nullptr;

        void* context = nullptr;
    };

    // Registers (or replaces) the implementation of one effect. Returns false
    // for an unknown effect id or an incomplete provider.
    bool RegisterProvider(uint32_t effectId, const Provider& provider);

    // Drops a provider. Stored intent is kept: if the same effect is
    // registered again the request is still there to be applied.
    bool UnregisterProvider(uint32_t effectId);

    uint32_t GetApiVersion();

    // Records that a mission wants this effect on or off. Intent is stored
    // whether or not the effect is currently possible, so kResultAccepted
    // means "recorded", NOT "it is now running". Ask for the status to learn
    // that; the two are deliberately not conflated.
    uint32_t SetEnabled(uint32_t effectId, bool enabled);

    // Records a tuning value. The value is validated and clamped to the
    // parameter's range before being stored or pushed.
    uint32_t SetFloat(uint32_t effectId, uint32_t paramId, float value);

    // Reads back the requested / supported / effective triple. Returns false
    // if `status` is null or `status->size` is too small to hold a V1.
    bool GetStatus(uint32_t effectId, Abi::StatusV1* status);

    // Drops every stored request and pushes "off" to anything registered.
    // Mission-scoped: one mission must not leak renderer requests into the
    // next.
    void Reset();

    // Test seam. Forgets providers as well as intent.
    void ResetForTesting();

    // Exposed for tests and for providers that want to honour the same ranges.
    float ClampParameter(uint32_t paramId, float value);
    bool IsKnownEffect(uint32_t effectId);
    bool IsKnownParameter(uint32_t paramId);
}
