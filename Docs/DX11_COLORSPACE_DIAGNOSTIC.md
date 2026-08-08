# OpenShim DX11 Color-Space Diagnostic

This is an opt-in, diagnostic-only observer for Battlezone 98 Redux 2.2.301's Ogre Direct3D 11 renderer. It exists to prove the live D3D11 resource/view formats used by BZR before any gamma/sRGB rendering change is attempted.

It does **not** enable Ogre hardware gamma, replace resources, modify shaders, alter render-target state, or change DX9 behavior.

## Enable

Environment variable:

```text
OPENSHIM_TRACE_DX11_COLORSPACE=1
```

or `openshim.ini`:

```ini
[Diagnostics]
TraceDX11ColorSpace=1
```

If neither is set, the probe is inactive.

## What is captured

When `RenderSystem_Direct3D11.dll` is actually loaded and creates a D3D11 device, OpenShim observes public D3D11/DXGI calls and writes records prefixed with:

```text
[DX11 ColorSpace]
```

The capture includes, when available:

- D3D11 device/feature-level activation;
- active D3D11 viewport dimensions;
- swapchain format and dimensions;
- `IDXGISwapChain3` color-space state where supported;
- backbuffer resource format;
- RTV resource and view formats independently;
- texture creation format/dimensions/mips/array/cube state;
- actual pixel-shader SRV bindings, including both underlying resource format and SRV view format;
- typeless, `_SRGB`, and floating-point classification;
- DSV/depth formats;
- intermediate render-target bindings.

The shader-resource binding records include Campaign Reimagined register hints for the current SM4 Enhanced base/terrain layouts. These hints are variant-dependent context, not an invented resource name.

D3D object debug names are logged when the retail renderer assigned them; they are not assumed to exist.

## Why resource and view formats are both required

Ogre 1.10's normal D3D11 texture path selects `_SRGB` formats when per-texture hardware gamma is enabled. Conversely, its render-window path can leave the swapchain/backbuffer resource as ordinary UNORM while creating an `_SRGB` RTV when render-window hardware gamma is enabled.

Therefore none of these alone are sufficient:

- DDS file header;
- swapchain format;
- texture resource format;
- material script syntax.

The diagnostic records the actual view used by the GPU at the binding point.

## Safety / bounded logging

The probe waits briefly for the DX11 renderer module. If it is not observed, it exits without installing D3D11 hooks, which keeps DX9 runs untouched.

Observation records are deduplicated and capped by category. Once a cap is reached, one warning is emitted and additional records in that category are suppressed. This prevents ordinary per-frame rebinding from creating an unbounded log.

The observer uses public D3D11/DXGI COM ABI methods rather than guessed Ogre object layouts. If a vtable implementation does not match the already-observed BZR device/factory implementation, that hook is not chained and the probe fails closed for that object.

## Required proof run

1. Enable the diagnostic.
2. Start BZR in Direct3D 11.
3. Load a Campaign Reimagined Enhanced High mission with PSSM/static IBL active.
4. View representative terrain, a normal/specular object, and an emissive object.
5. Exit normally.
6. Preserve the OpenShim log and matching `BZOgreLogfile` from the same run.
7. Extract all `[DX11 ColorSpace]` lines.
8. Record both resource and SRV formats for representative color/data resources and both backbuffer resource and RTV formats.

Do not describe the pipeline as proven linear/nonlinear until that capture exists.

See Campaign Reimagined `Docs/DX11_COLOR_SPACE_AUDIT.md` for the resource classification, evidence table, and the gate for the later Enhanced-only linear-light experiment.
