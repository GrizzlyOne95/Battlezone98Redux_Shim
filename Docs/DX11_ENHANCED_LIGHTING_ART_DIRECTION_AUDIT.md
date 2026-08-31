# DX11 Enhanced lighting art-direction audit

Date: 2026-08-30

## Outcome

The supplied Mars and Moon comparisons exposed two separate Enhanced-only
problems. They did not justify a global exposure, tone-map, material, or mission
retune.

- Mars fog was an sRGB/linear boundary error. The mission-authored display RGB
  fog constant entered a linear-light atmosphere and was encoded again at the
  output. The fix decodes that constant before atmosphere integration.
- Lunar terrain was lifted mainly by a fixed neutral diffuse IBL floor. The fix
  scales only terrain diffuse IBL from the authored fog transition range, a
  mission-agnostic proxy for atmospheric support. Direct light, object IBL,
  terrain specular IBL, emissives, Default, and Retro are unchanged.

The active shipped content remains owned by Campaign Reimagined. OpenShim keeps
the equivalent `OSE_` shader mirror synchronized and owns the native diagnostic.

## Evidence and pipeline

The review used the supplied `enhanced`, `redux`, `retrohorizon`,
`enhancedhorizon`, and `reduxhorizon` captures; the CR/EXU/OpenShim sources; the
live GOG runtime; Ogre exports from the shipped `OgreMain.dll`; and the runtime
logs.

| Stage | Proven owner/behavior |
|---|---|
| Mission/TRN | `FogStart`, `FogEnd`, `Intensity`, `Ambient`, and palette are authored per map. The reviewed TRNs do not carry explicit fog RGB. |
| Campaign environment | CR's `Environment.lua` selects environment defaults/presets and calls EXU's fog/ambient/sun setters. |
| Native scene state | EXU writes Ogre scene fog and ambient values without an sRGB conversion. |
| Material binding | Active GOG logs compile `CR_BaseEN*` and `CR_TerrainEN*`; the live content is CR's shader set, not OpenShim's future stock-material retrofit. |
| Shader constants | Ogre binds `fog_colour`, `fog_params`, `derived_ambient_light_colour`, and derived light arrays. |
| Enhanced working space | COLOR textures are decoded, lighting/atmosphere is evaluated in linear space, and RGB is encoded once to an ordinary `R8G8B8A8_UNORM` target. No hardware sRGB or gamma stage was observed. |

There is no Enhanced exposure or tone-mapping operator in this path. The
ordinary UNORM target clamps the encoded result.

## Mars fog qualification

The live Mars state was:

- authored fog RGB: `(0.65, 0.45, 0.25)`;
- fog start/end: `120 / 250`;
- derived scene ambient reaching the shader: `(0.20, 0.20, 0.20)`;
- active scheme: `en-high-noshadow`.

Before correction, treating `(0.65, 0.45, 0.25)` as linear and applying the
final output transfer produces approximately `(0.826657, 0.701411, 0.537099)`.
That is the pale cream/tan seen in the supplied Enhanced comparison. Decoding
the authored constant produces shader-linear `(0.380056, 0.170645, 0.050876)`;
after the deliberately weak ambient atmosphere term and the one final encode,
the base non-sunward result is `(0.658583, 0.463555, 0.276363)`, close to the
authored rust colour.

Classification: **color-space mismatch**, not authored-data drift, excess
ambient, bloom, tone mapping, exposure, or hardware sRGB.

## Lunar ambient qualification

The supplied Enhanced lunar comparison showed broadly lifted blue-gray valleys
and weaker ridge separation. Mission `Ambient=0` ruled out a mission-data
ambient increase as the sole owner, and near terrain before fog onset ruled out
fog as the sole owner. The Enhanced terrain shader supplied a fixed neutral
diffuse irradiance intensity of `0.20` even on long-range/airless environments.

The new multiplier is:

```text
support = saturate(abs(fog inverse range) * 160)
terrain diffuse IBL scale = lerp(0.15, 1.0, support)
```

This is deliberately continuous and environment-sensitive. A short, dense Mars
transition reaches `1.0`; long transitions reduce the neutral terrain fill;
missing/disabled fog retains a `0.15` safety floor. The live Moon probe reported
`175 / 540` and therefore `0.522603`. The adjustment does not branch on mission,
planet, texture, or palette names.

Classification: **fixed terrain diffuse-IBL floor**, with atmospheric fog still
responsible for the far-field convergence. Scene ambient and fog remain useful
secondary contributors and are now exposed by the diagnostic.

## Scope and invariants

- Fog decode is compiled only under the existing Enhanced per-pixel
  linear-light guard.
- Terrain IBL scaling is inside the Enhanced terrain IBL path only.
- Base/object diffuse and specular IBL are unchanged.
- Terrain specular IBL is unchanged.
- Direct lights, emissives, PSSM/shadow selection, materials, mission/TRN files,
  UI, Default, Retro, DX9, and GL are unchanged.
- Campaign Reimagined's validator requires the authored-fog decode and still
  rejects direct decoding of the raw `fogColour` engine identifier or any data
  texture.

## Diagnostic

Enable either:

```ini
[Diagnostics]
TraceDX11EnhancedLighting = 1
```

or `OPENSHIM_TRACE_DX11_ENHANCED_LIGHTING=1`.

`[DX11FOG]` records only on initialization, material-scheme change, or effective
value change. It reports authored fog RGB, the shader-linear value, derived
ambient, the atmosphere ambient contribution, corrected and untreated expected
output RGB, fog density/start/end/inverse range, and the terrain diffuse-IBL
scale. It is off by default and does not alter rendering.

## Validation

- Campaign Reimagined shader validator: **208/208 SM4 compilations passed**,
  including all 108 linear-light/radial-fog combinations and all 66 terrain
  normal diagnostic permutations.
- OpenShim Release/Win32: **built successfully**.
- OpenShim tests: **17/17 passed**.
- GOG windowed runtime: Mars `misn04.bzn` and Moon `misn02b.bzn` reached
  simulation, compiled the changed shaders after a cache-fingerprint mismatch,
  produced captures, emitted the expected `[DX11FOG]` states, and shut down via
  `Stop-BZRGame`.
- Default/Retro isolation is enforced by the compile/preprocess matrix. The
  review supplied a Retro comparison; no Retro shader or material was changed.

The automated captures are useful runtime proof but are not locked-camera art
comparisons: their starting HUD/camera states differ from the supplied frames.
A final human art-direction pass should recapture the original viewpoints on
Mars and Moon before release. No Workshop publication was performed.
