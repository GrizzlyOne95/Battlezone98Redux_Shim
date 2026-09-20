#pragma once

namespace BZROpenShim
{
    // Phase A of Docs/DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md: diagnostic
    // instrumentation that identifies D3D11 depth resources unambiguously.
    //
    // It records what CreateTexture2D was asked for, what depth-stencil views
    // were built over it, and which render targets were bound alongside it, so
    // the main gameplay depth surface can be told apart from shadow maps, the
    // satellite view, the scope and temporary RTTs from evidence rather than
    // from API convention.
    //
    // Observation only. Nothing here mutates a resource description, creates a
    // view, or touches a pipeline binding, because Phase A's own acceptance
    // criteria say not to: "do not mutate resource creation yet".
    //
    // Off unless asked for, and it is a qualification tool rather than
    // something to ship enabled:
    //
    //   [DX11Enhanced]
    //   SceneDepthDiagnostic = 1
    //
    // or OPENSHIM_DX11_SCENE_DEPTH_DIAG=1. A missing key fails closed, so stock
    // and Enhanced installs that have not opted in are untouched. Only
    // RenderSystem_Direct3D11.dll is watched; DX9 is never hooked.
    void InitializeDx11SceneDepth();

    // Stops the discovery and reporting worker and emits a final table. COM
    // vtable hooks installed earlier stay for process lifetime and become
    // pass-through once shutdown is set, which is the same discipline the
    // Enhanced FXAA path uses.
    void ShutdownDx11SceneDepth();
}
