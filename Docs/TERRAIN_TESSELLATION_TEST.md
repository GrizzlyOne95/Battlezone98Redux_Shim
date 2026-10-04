# Native terrain tessellation submission test

Experimental, default off, zero displacement by default. This establishes whether the
released DX11 renderer can tessellate Redux's existing terrain buffers. It does
not add smoother hills or surface relief. Collision, placement, pathfinding,
terrain data, and networking are unchanged.
The optional [micro relief prototype](TERRAIN_MICRO_RELIEF_TEST.md) adds bounded
visual surface detail through `-MicroRelief`.

## Scope

The test discovers a native cluster through the existing exact-build terrain
hooks, validates its triangle indices and three vertex streams, and stages hull
and domain programs on a private material clone. After compilation and runtime
DXBC interface audits pass, it attaches those programs to compatible passes of
the **original shared terrain material**. Every cluster using that material is
affected; the discovery cluster is not an isolation boundary.

Assigning the clone to the discovered Entity did not produce a patch submission
in the initial tests. Updating the shared material did. Cached renderable/material
references are a plausible explanation; the exact native submission owner has
not been established by this experiment.

The original VS and PS remain active. The domain shader interpolates their
existing clip position, COLOR0, atlas UV, normal, view position and depth. It
does not read a displacement texture, alter render bounds, add another entity,
or change terrain vertex/index buffers. Recognized per-pixel terrain passes,
including single-shadow and PSSM receivers, are specialized. Their existing
shadow coordinates are interpolated unchanged. Glow, shadow casters, vertex lighting,
DX9, and incompatible/custom shader interfaces retain their existing programs.

Executable/Ogre identity checks reuse the terrain subsystem's gates. A separate
released DX11 renderer hash check guards the shader/buffer export ABI. The
actual device must provide feature level 11_0. Missing exports, missing source,
unsupported compilation, existing tessellation programs, or mismatched runtime
VS/HS/DS registers decline installation. The shared pass settings are restored
before the test resources are removed at the mission lifecycle seam.

## Run

Build Release/Win32 first. Use the normal GOG test installation with the
Enhanced profile and a compatible per-pixel terrain technique.

```powershell
python scripts/Test-TerrainTessellationShaders.py
./reverse_engineering/run_terrain_tessellation_test.ps1 -Factor 1 -RunSeconds 65 -Deploy
./reverse_engineering/run_terrain_tessellation_test.ps1 -Factor 2 -Wireframe -RunSeconds 65 -Deploy
```

The harness serializes launches, forces windowed DX11, deploys the complete load
chain, stops its own PID gracefully, restores its environment/configuration,
and writes fresh-PID evidence under ignored `build/terrain-tessellation/run-*`.
Advance a waiting briefing with Space. `-Mission` accepts another map;
`-Editor` adds `/edit` for a map suitable for the editor. It refuses an existing
game session. It never closes another session to acquire the machine.

The environment-only controls are:

| Variable | Default | Accepted values |
|---|---|---|
| `OPENSHIM_TERRAIN_TESSELLATION_TEST` | off | truthy enables |
| `OPENSHIM_TERRAIN_TESSELLATION_FACTOR` | 2 | 1, 2, 4 |
| `OPENSHIM_TERRAIN_TESSELLATION_WIREFRAME` | off | truthy enables |

The test disables the separate terrain proxy/HD/semantic experiments for its
process. No persistent INI setting is added.

## Evidence and limits

The shader check compiles 110 shaders: ten declared terrain permutations,
baseline factors 1/2/4 and micro relief factors 2/4. It checks semantic names, indices, types, registers and masks
across VS -> HS -> DS using OGRE-compatible compiler flags. Runtime compilation
is audited separately. `SV_POSITION`'s system-value tag is normalized only at
the intermediate control-point interface; final domain output is checked.
Generated program names include source and compile-definition hashes because
the released Ogre microcode cache is name-keyed. A pass-order change must not
reuse another permutation's compiled bytecode.

The GPU observer brackets an operation between successive native topology
selections after the complete input-assembler state is bound. It uses only
immediate contexts and nonblocking pipeline-statistics readback, with at most
16 tessellated samples. It requires a pixel shader and an RGBA scene target,
excluding depth-only and single-channel shadow targets. It does not replace changing COM draw wrappers. The
query covers a submission region, not a guaranteed single draw; auxiliary work
between topology selections can contribute to the counters.
Failed pixel/coverage samples advance through later terrain operations so
the first occluded cluster is not repeatedly sampled on successive frames.

The harness requires 12,800 IA patches, positive hull/domain activity, at least
1,024 pixel invocations and 128 clipped primitives, material restoration and clean exit.
That proves submission/rasterization, not image parity, good winding on every
pass, performance, or game integration.

Local Windows/GOG 2.2.301 evidence on 2026-10-03:

| Run | IA primitives | Hull invocations | Domain invocations | Clipped primitives | Pixel invocations |
|---|---:|---:|---:|---:|---:|
| Ordinary terrain control | 12,800 | 0 | 0 | 12,574 | 0 |
| Factor 1, solid, PID 6084 | 12,800 | 12,800 | 38,400 | 259 | 1,158 |
| Factor 2, wireframe, PID 12500 | 12,800 | 12,800 | 89,600 | 138 | 103 |
| Factor 2, shadow receivers, clockwise, PID 58756 | 12,800 | 12,800 | 89,600 | 34,125 | 1,293,619 |
| Factor 1, shadow receivers, clockwise, PID 62524 | 12,800 | 12,800 | 38,400 | 12,800 | 41,131 |

These initial runs covered only no-shadow passes and did **not** establish a
visible change to the main terrain. The user reported unchanged terrain despite
those small pixel counts. Adding shadow-receiver coverage initially exposed
stale cached bytecode; definition-specific program names fixed that mismatch.
Clockwise tessellator output and all 27 compatible shared passes produced an
obvious terrain wireframe in the live GOG window (PID 59368). The initial
statistics observer also sampled shadow work, so those counters are not a
main-view acceptance measure. The revised observer's factor-2 run (PID 58756)
recorded substantial rasterization and passed the harness; this is submission
evidence in addition to the directly observed wireframe, not a substitute for
looking at the rendered image. Release/Win32 and all 73 CTest tests passed.
The final factor-1 solid run (PID 62524) also passed the revised submission
gate and rendered ordinary solid terrain; a quantitative parity comparison
remains a separate gate.

Remaining gates include a locked-camera image comparison, wider map/edge
sweeps, deformation and full rebuilds, A -> B -> A,
profile/quality changes, device recreation, and Steam/Proton/Wine coverage.
The separate [micro relief test](TERRAIN_MICRO_RELIEF_TEST.md) now adds bounded
static displacement and updates render bounds/normals; the user confirmed
stable ground in the corrected local GOG camera-motion test. Adaptive factors,
authored height art and broader qualification remain future work.
See [the research](TERRAIN_VISUAL_TESSELLATION_RESEARCH.md).
