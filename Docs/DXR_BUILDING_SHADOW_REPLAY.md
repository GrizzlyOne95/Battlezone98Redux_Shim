# Native building sunlight shadow replay

Default-off development capture now exports selected stock building poses and
adds them as DXR occluders in a frozen scene replay. It produces a visible ground
shadow beside the hangar in GOG `misn03`. The live companion still consumes only
the leased terrain zone; building snapshots are never treated as live geometry.

## Capture contract

`-NativeBuildingSnapshot` in `tools/frame_bridge/Game-Smoke-Test.ps1` enables a
bounded scene inventory and building capture on the existing game-thread terrain
callback. It implies `-NativeEntityInventory` and `-NativeTerrainSnapshot`.
The underlying environment switches are `OPENSHIM_TERRAIN_GEOMETRY_ENTITIES=1`
and `OPENSHIM_TERRAIN_GEOMETRY_BUILDINGS=1`, with a nonempty geometry export prefix.
Normal launches leave both disabled. No additional address or hook is introduced.

The adapter retains the terrain exporter executable/Ogre/DX11 identity gates.
Released exported scene/node/entity APIs and the Entity primary ShadowCaster
vtable qualify traversal. Bounds are 8192 nodes, 4096 children per node, 256
attachments per node, 2048 entities, and 64 subentities per entity. Unexpected
foreign access faults decline and disable inventory for that session. No engine
pointer survives capture or crosses into the x64 helper. A foreign fault cannot
unwind C++ owners under `/EHsc`; this diagnostic path therefore avoids repeated
fault/retry leaks rather than claiming complete fault recovery.

Candidates are visible, shadow-casting stock `ab`/`sb` mesh names with zero mesh
animations. That selection does **not** prove immobility: skeleton poses still
change. Capture requires software animation, one actual SubEntity world
transform, indexed triangle lists without instancing, FLOAT3/FLOAT4 unit-W
positions, bounded stride/offset/ranges and 16/32-bit indices. The released draw
uses `indexStart` and `vertexStart`; the decoder preserves these and index order.
Actual `getRenderOperation` selects the current software pose buffer, rather
than an inferred bind pose. `getWorldTransforms` supplies its renderable matrix.
Up to one million expanded caster vertices and 256 submeshes are captured.

The active technique must have one unblended, depth-writing pass with always-pass
alpha, no hull/domain programs, and a Base/OSE_Base HLSL4 vertex delegate whose
source contains the stock position expression. This is a bounded stock capture
predicate, not proof of arbitrary custom shader position or opacity behavior.
Metadata explicitly records `foreignMaterialQualified=false`.

Each terrain revision receives `.entities.json`, `.buildings.bin`, and
`.buildings.bin.json` siblings. The binary uses the existing `BZRGEO1` owned
world-space triangle format, with PID, mission and integrity hash. Building
metadata records the observation QPC, submesh source/range/world transform,
`snapshotPoseOnly=true`, and `liveLifetimeQualified=false`. A building pose is
not synchronized to the final recorded color/depth frame. These files and game
mesh data stay in ignored local capture directories.

## Replay and receiver matching

The DXR diagnostic accepts an optional caster binary after its sunlight/mode
arguments. Receiver and caster binaries must have matching PID/mission, valid
headers and bounded combined size. Terrain vertices precede caster vertices in
one owned native BLAS. Closest camera hits on the caster suffix are rejected as
terrain receivers; sun rays may hit either prefix or suffix. Visible-depth
geometry remains excluded from sun occluders. AO can also see the new casters.
The debug mask disables AO and isolates sunlight visibility.

Native receiver matching now accounts for minimum-resolved MSAA depth coming
from another sample within the pixel. It derives a half-pixel axial-depth bound
from the actual native plane and neighboring projection rays, retaining depth
quantization checks and a two-meter maximum tolerance. Grazing/nonfinite cases
decline. The sun origin bias remains five centimeters. This improves flat-ground
coverage; general silhouettes, alpha coverage, smoke and material normals remain
unqualified. Preview still multiplies existing SDR lighting on blocked terrain;
it does not replace direct lighting or prevent doubled raster shadows.

After a harness capture, run from the worktree:

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 180 `
    -NativeBuildingSnapshot -TerrainShadows mask -NativeTerrainRefreshProbe
python tools/frame_bridge/Replay-Building-Shadows.py <capture-directory> --revision 2
```

The replay checks snapshot metadata, captured unit sunlight and camera ordering,
uses matched round-trippable scene camera floats, and executes four GPU passes:
terrain-only/terrain-plus-buildings in preview/mask modes. It writes PNGs, an
unchanged-color paired crop with an explicitly amplified delta, and a report
which declares replay-only, unsynchronized pose and incomplete scene coverage.

## Captured evidence

GOG PID 37688, `build/game-bridge-20261012-191216-570/`, captured 17 building
submeshes / 60776 triangles alongside 204800 terrain triangles. Sixty 1600x900
frames included 54 live terrain sunlight frames. Building replay added 4296
blocked mask pixels; the preview changed 4648 pixels by more than two levels,
maximum channel delta 31. Alpha was retained exactly. The paired crop was
inspected. This is native-geometry shadow evidence, not a live building demo.

The final refresh control, PID 39392,
`build/game-bridge-20261012-231035-257/`, imported 180 frames with 163 DXR frames,
156 native terrain sunlight frames, seven depth-only renewal frames, two
revisions and recovery after one invalidation. Revision two inventoried 196
nodes / 192 entities and captured the same 17 submeshes / 60776 triangles.
Both runs exited zero and restored all 60 deployment/configuration hashes.

On exact frame 180 inputs, terrain-only replay marked zero blocked pixels;
adding building poses marked **4293**. Preview changed 4619 pixels by more than
two levels, maximum channel delta 48, with exact alpha. The ungraded crop and
debug mask were inspected. Native sunlight is `(0.819152117, 0.573576510, 0)`.
The added-caster mask isolates sunlight; the preview difference also includes
any added native AO. No FPS or latency gain is measured.

Terrain hashes were unchanged across renewal. Building hashes changed from
7959863419307696940 to 18164656593772991556 even though all 17 world matrices
were identical. Fourteen submeshes, including the hangar, had identical position
payloads; three `abspow.mesh` submeshes changed software pose, with maximum world
vertex displacement about 13.87 meters. This concretely rules out treating a
stationary node or zero mesh animations as a live static-caster guarantee.

Initial attempts declined an incorrectly spelled hardware-animation export,
then all candidate materials while the source predicate expected whitespace
absent from actual stock shaders. Correcting the exported signature and folding
source whitespace produced the accepted captures. Missing building output now
fails the harness qualification rather than counting as success.

Win32 Release builds; 110 native CTest, eight x86 helper and eleven x64 helper/GPU
tests pass. Decoder tests exercise actual layout/index/affine semantics and
malformed input rejection. Hardware tests verify separate offscreen casters
produce the same sun shadow, caster geometry cannot become a terrain receiver,
and 2850 floor pixels match despite a real within-pixel MSAA depth offset.

Next work is per-object pose/deletion/visibility invalidation and synchronized
geometry updates before live caster submission. Moving units, other zones,
alpha materials, relief matching, denoising, reflections, GI, direct-light
replacement and Steam/Proton/Wine acceptance remain open. No helper or generated
geometry is shipped in the supported game bundle.
