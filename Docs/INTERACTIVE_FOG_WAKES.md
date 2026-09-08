# Interactive ground fog wakes

Status (2026-09-07): simulation foundation implemented. No live vehicle sampling,
fog rendering, configuration toggle or EXU API is enabled yet. This is not a
released or visually qualified feature.

## First milestone

`include/fog_wake.h` and `src/engine/fog_wake.cpp` implement a platform-neutral
CPU clearance field in a fixed world-space rectangle. Cell centres store
clearance from zero (original fog) to one (cleared). Swept capsules connect
successive vehicle positions without gaps; a smooth radial edge softens the
corridor. Overlapping stamps take the maximum clearance, rather than accumulating
with the number of observations. Excessively long segments are rejected as
teleports. Wind transports clearance using bilinear backtracing; exponential
recovery restores undisturbed fog. Outside the region is zero clearance.

The default 128 x 128 grid at one metre per cell covers 128 x 128 metres. Two
float grids consume 128 KiB. Configuration caps each dimension at 1024. Updates
allocate no memory, and capsule stamping visits only a clipped bounding box.
Configuration allocates both buffers before replacing existing state; allocation
failure can throw and must be handled by the eventual runtime feature owner.

`Clearance()` exposes row-major samples for a future texture upload. It is not
a GPU texture or stable external ABI. All access must stay on one owner thread.
`Reset()` discards all disturbances; `Configure()` creates an empty region.

## Planned runtime contract

1. OpenShim owns a capability-gated runtime and all GPU resources. EXU will
   communicate mission intent; no new Lua API is claimed by this milestone.
2. Track valid vehicles and their prior world positions using qualified engine
   accessors. Clear tracking on destruction, handle reuse, session transitions,
   and teleports. A rejected sweep must still reseed the caller's prior position.
3. Advance recovery/wind, then stamp vehicle sweeps at a fixed simulation cadence.
   Render callbacks may execute for multiple cameras: never advance once per
   camera. Pause must freeze simulation time. Strength/width/height gating and
   optional stationary hover downwash belong to the emitter policy.
4. Start with one fixed fog bank. Moving a camera must not relocate its history.
   Scrolling/tiled fields, boundary crossfades and world-height profiles are later
   work. Radius should span multiple cells; sub-cell wakes may be undersampled.
5. Upload clearance once per update. A near-ground density function combines
   base fog, height, noise and `(1 - clearance)`. Integrate along the view ray up
   to opaque scene depth, not just at the visible surface position.
6. Qualify a scene-depth source and a pass before HUD/cockpit overlays. Coordinate
   stock fog so near fog is not already baked into the source colour. Transparent
   geometry, particles, water, alternate cameras and distant haze need explicit
   handling. Existing Ogre render hooks and terrain shader work are references,
   not proof that a suitable fog compositor insertion point has been verified.
7. Keep this optional and fail closed when rendering prerequisites are absent.
   Define DX9 fallback separately; do not assume DX11 integration proves it.

This foundation has wind drift and soft wake edges, but no vortices, displaced
density at wake edges, diffusion solver, terrain-height sampling, volumetric
lighting or particle curls. Semi-Lagrangian interpolation introduces numerical
diffusion and is not mass-conserving; fixed-step updates keep its look consistent.
Recovery without wind is independent of timestep partition.

## Validation

`fog_wake_tests` covers continuous sweeps, soft edges, idempotent overlap,
teleports, malformed inputs, invalid reconfiguration, exponential recovery,
timestep partition without wind, wind direction, outflow, bounds and reset.
It is registered in the shared CMake/CTest harness and the source is included in
the Win32 DLL project.

The simulation has no store, filesystem, loader, ABI or graphics dependency.
Windows Win32 Release unit tests pass. In-game Windows/GOG, Windows/Steam,
Linux/Steam Proton and Linux/GOG Wine/Proton rendering remain unverified. No
game deployment has been performed. Runtime qualification and tester validation
in affected lanes are required before release.
