# DX11 Enhanced FXAA 3.11

## Scope

This is an **experimental DX11 Enhanced-only presentation feature**. The branch's reference `openshim.ini` enables it by default so DX11 Enhanced testing exercises the FXAA path, while the runtime still fails closed when the `DX11Enhanced/FXAA` key is absent. It is not part of the stock shader path.

Reference configuration:

```ini
[DX11Enhanced]
FXAA = 1
```

The environment fallback is `OPENSHIM_DX11_ENHANCED_FXAA=1`.

Only `RenderSystem_Direct3D11.dll` is observed or patched. DX9 is never hooked by this feature. An existing installation whose INI does not contain the `DX11Enhanced/FXAA` key remains unchanged; set `FXAA = 0` explicitly when testing ordinary/stock DX11. The current milestone intentionally has no general-purpose antialiasing toggle or renderer-wide quality menu.

Campaign Reimagined's intended test target is **DX11 Enhanced High** (`ENHigh*` / `ENHANCED_MODE`). Lower/shared shader delegates remain compatibility paths and are outside this experiment.

## Why FXAA 3.11

The removed prerelease BZR files already contain NVIDIA FXAA 3.11:

- `reverse_engineering/prerelease_2016/removed_files/Fxaa3_11.h`
- `reverse_engineering/prerelease_2016/removed_files/fxaa3.hlsl`
- `reverse_engineering/prerelease_2016/removed_files/fxaa3.material`
- `reverse_engineering/prerelease_2016/removed_files/fxaa3.compositor`

The old wrapper was Shader Model 3 (`FXAA_HLSL_3`, `ps_3_0`). This implementation keeps the 3.11 algorithm and the beta's fidelity target but replaces that obsolete wrapper with a Shader Model 5 integration:

- `FXAA_PC = 1`
- `FXAA_HLSL_5 = 1`
- `FXAA_GREEN_AS_LUMA = 1`
- `FXAA_QUALITY__PRESET = 39`
- beta tuning: subpixel `0.75`, edge threshold `0.063`, edge-threshold minimum `0.0625`
- `Texture2D` + `SamplerState`
- bilinear clamp sampling
- `vs_5_0` full-screen triangle using `SV_VertexID`
- `ps_5_0` FXAA quality pass

The original `Fxaa3_11.h` is embedded into `winmm.dll` as RCDATA and supplied to `D3DCompile` through an in-memory include handler. The algorithm is therefore not forked into a second copy.

## Render order and color space

FXAA filters the 3D scene only. Screen-space UI, text and the HUD are drawn after it and stay sharp.

OpenShim registers an `Ogre::RenderQueueListener` on the scene manager (`RenderGlobals` record +0x08) through OgreMain's exported `SceneManager::addRenderQueueListener`. The listener fires at the first render queue group of 60 or above, once per frame, and only while the main viewport (record +0x1C, compared with `RenderSystem::_getViewport()`) is rendering. Groups below 60 are world: sky, opaque world and cockpit, terrain, world sprites and, when no screen-space text intervenes, the transparent world group 95. Groups 60 and up are cUI widgets and text (60 + nesting depth) and the HUD (100). The sniper and target-camera viewports, shadow passes and the glow mask pass therefore never trigger it. At that point the pass:

1. reads the render target the main viewport is drawing into (the backbuffer, or Glow's `rt_output` while Glow is on);
2. captures every D3D11 state that the FXAA pass changes;
3. unbinds the game's render target;
4. copies or resolves that target into a single-sample shader-resource texture;
5. runs FXAA back into it with a full-screen triangle and no depth target;
6. unbinds the FXAA SRV; and
7. restores the captured game state, so Ogre draws the UI on top of the filtered scene.

The format check applies to the render target view's format (see below). Present only prepares the device resources and starts a new frame for the listener. The listener is registered once the scene manager exists, and again if the scene manager pointer ever changes; it is never removed, because the engine's scene manager outlives the swapchain hook.

If the Ogre exports or `RenderGlobals` cannot be resolved, or registration faults, OpenShim logs one warning and falls back to the original whole-frame pass immediately before `Present`, which also filters the HUD and text. Shell screens with no 3D viewport are not filtered.

FXAA 3.11 with `FXAA_GREEN_AS_LUMA` expects perceptual/non-linear LDR input. The first milestone therefore **fails closed unless the target is an ordinary 8-bit UNORM format**:

- `DXGI_FORMAT_R8G8B8A8_UNORM`
- `DXGI_FORMAT_B8G8R8A8_UNORM`
- `DXGI_FORMAT_B8G8R8X8_UNORM`

`*_SRGB`, typeless, 10-bit, floating-point, and other HDR/unknown targets are rejected rather than sampled through an implicit transfer-function conversion. This is intentional: an sRGB SRV would decode to linear light before FXAA and would violate the 3.11 integration guidance.

The pass also requires D3D feature level 11.0 or newer because the HLSL5 path uses gather operations.

## State and resize safety

The pass preserves/restores:

- render targets and depth-stencil view;
- blend/depth-stencil/rasterizer state;
- viewports;
- input layout and primitive topology;
- VS/PS/GS/HS/DS shaders and class instances;
- PS slot 0 SRV/sampler/constant buffer; and
- D3D11 predication.

No render-target, swapchain-backbuffer pointer or RTV is retained after the pass. That is required because outstanding backbuffer references can make `ResizeBuffers` fail during fullscreen/window-size transitions.

The intermediate SRV is recreated automatically when width, height, or presentation format changes.

## Runtime compiler

The HLSL wrapper and NVIDIA header are stored inside `winmm.dll`. The runtime loads `D3DCompile` dynamically from, in order:

1. `d3dcompiler_47.dll`
2. `d3dcompiler_46.dll`
3. `d3dcompiler_43.dll`

Nothing is loaded or compiled while FXAA is disabled. A missing compiler or shader compilation error disables the pass for that process and leaves normal presentation intact.

## Validation

Automated validation must establish both of these before runtime testing:

- the HLSL wrapper compiles as `VSMain / vs_5_0` and `PSMain / ps_5_0` against the exact removed-beta `Fxaa3_11.h`;
- the normal Release Win32 OpenShim build succeeds with the new native hook/resource code.

For the first in-game proof run:

1. select Campaign Reimagined **DX11 Enhanced High**;
2. use the branch reference `openshim.ini`, where `[DX11Enhanced] FXAA = 1` is already enabled;
3. clear Ogre's shader/microcode cache if the surrounding Enhanced shader work requires it;
4. launch a mission with strong diagonal geometry, terrain silhouettes, vehicle edges, wires/antennae, and HUD text;
5. confirm the OpenShim log reports the D3D11 renderer, swapchain attachment, accepted LDR format, and `preset=39` presentation resources;
6. compare identical camera positions with FXAA off/on; and
7. test alt-tab, fullscreen/windowed transitions, resolution changes, mission restart, and shutdown.

The critical visual checks are edge cleanup, excess softening of textures/HUD, thin-geometry loss, dark/non-green edge behavior from `GREEN_AS_LUMA`, and that HUD/UI text stays pixel-identical to an FXAA-off run (the scene pass excludes it).

## Deliberately deferred

This milestone does **not** add:

- FXAA to DX9;
- FXAA to ordinary/stock DX11 testing;
- a Low/High/Ultra selector;
- presets 12 or 29;
- SMAA/TAA/FSR/DLSS-style replacement AA;
- HDR/scRGB processing;
- a new Ogre compositor definition; or
- changes to stock BZR shader/material files.

Once preset 39's ordering and color-space behavior are proven in Enhanced High, quality selection can be considered separately without destabilizing the stock renderer paths.
