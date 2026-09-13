#pragma once

namespace BZROpenShim
{
    // Repairs the multiplayer Create Game vehicle preview on Direct3D11, where
    // the craft panel renders black.
    //
    // cUI_Multiplayer_VehicleSelect (FUN_007A9590) configures the preview
    // viewport at render-globals 0x00920EA0 +0x24 -- clear colour, black
    // background, overlays off, setShadowsEnabled(false), visibility mask 8 --
    // but never calls setMaterialScheme. The viewport therefore keeps Ogre's
    // default scheme, reported by the RTShaderSystem as
    // "ShaderGeneratorDefaultScheme". No BZ material declares that name, so
    // Ogre falls back to the material's FIRST technique, and BZBase.material
    // opens with "scheme high-pssm".
    //
    // That PSSM technique's vertex shader consumes texWorldViewProj1..3, the
    // shadow texture projections. Shadows are disabled for this viewport, so
    // the shadow setup never runs and those auto-params arrive as NaN. The
    // pixel shader then writes NaN, and a UNORM render target stores NaN as
    // zero -- a black panel.
    //
    // Confirmed from a RenderDoc capture of a broken frame: wvpMat finite,
    // texWorldViewProj1..3 NaN, and pixel history reporting
    // shaderOut = [nan, nan, nan, 0] with the depth test passed and nothing
    // culled, scissored or discarded. Direct3D9 never takes the sm4 path and
    // is unaffected.
    //
    // The repair pins that one viewport to the matching "-noshadow" scheme,
    // which selects a technique that never reads those matrices. Called once
    // per rendered frame; cheap and latched when the setting is off.
    // Controlled by [Fixes] MpVehiclePreviewShadowScheme.
    void MpVehiclePreviewFixTick();
}
