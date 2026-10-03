# ISDF Chronicles mission 14 performance

Local GOG 2.2.301 investigation, 2026-10-02. This records the first minute of
`isdfms14.bzn`, rather than a completed mission playthrough.

## Keep the distant terrain

The mission's `VisibilityRange=1500` prevents mountains appearing suddenly in
front of the sky. This is terrain visibility popping, not a sky depth defect.
The range, fog, sky materials and terrain geometry remain unchanged.

The existing terrain construction has no separate distant geometry LOD.
Reducing the range alone would restore the artifact. A future terrain LOD
must retain distant silhouettes, match the near mesh at its boundaries and
handle terrain deformation; changing the sky shader cannot supply missing
terrain geometry.

## Applied changes

* The recent-hit reticle callback reads fresh actual-team data under SEH and
  checks the existing GameObject-interface vtable identity on every call. Its
  already validated retail input is a live GameObject, so it no longer issues
  two `VirtualQuery` calls per displayed object. Untrusted handle and arena
  helpers retain their original checks. Team changes and target-policy overrides
  remain live; there is no object/team cache. Set
  `OPENSHIM_DISABLE_FAST_RETICLE_TEAM_READ=1` to restore the original read path.
* Chunk payload resource registration runs once in the existing Ogre world
  callback, before debris is active. Previously the first death recursively
  scanned the cache and payload directories during simulation. Failure retains
  the original first-use path. It introduces no periodic directory scan or
  additional physics objects. Set
  `OPENSHIM_DISABLE_CHUNK_RESOURCE_PREWARM=1` to restore first-use registration.
* The existing opt-in finite craft-bounds repair can replace the private
  main-view cull. It lets Ogre perform its own main and shadow-camera rejection.
  It affects only meshes given an infinite bound, uses twice the serialized
  asset half-extents around their centre and exempts dedicated cockpit meshes.
  Missing asset bounds retain stock behavior. Terrain bounds and legacy
  collision, AI, targeting and physics are separate and unchanged.

## Evidence and limits

The initial native sample placed roughly 73% of main-thread wall samples inside
Ogre frame rendering. Virtual-memory queries accounted for about 5.1% of leaf
samples; after the reticle change the measured share was 0.57%. These are
sampled shares, not additive timings. The sampler has truncated frame-pointer
walks and no final END record, so it cannot provide a complete call graph.

Temporary Lua wrappers measured about 0.133 ms per mission Update on average
over 5,259 calls. Their timer has millisecond resolution and they add overhead;
this is attribution, not an exact production Lua cost. No Lua update cadence or
mission objective was changed.

Diagnostic captures averaged about 1,710 indexed draws per frame before the
bounds repair and 1,422 afterwards. Repeated custom craft, ruins and scrap
contribute many submissions across normal, glow and shadow passes. Duplicate
animation counters include legitimate additional cameras and passes and do
not justify skipping pose updates.

The measured first-death hitch included Ogre recursive file enumeration and
resource-group initialization. Startup prewarming moved a 265 ms initialization
before the simulation-ready marker. A subsequent profiler-free 4K DX9 capture
had a 37.6 ms largest frame in the measured 5–50 second interval, compared with
roughly 290–300 ms in the preceding captures. This reduces the observed stall;
it does not guarantee hitch-free cold GPU/material loads or every mission.

Performance captures use 3840x2160, DX9, FSAA 0 and VSync off. Native and Lua
diagnostics are disabled for frame-time comparisons. Independent mission runs
have battle-timing variation, so the full local report keeps separate early
and later intervals. GPU execution time was not independently measured.
PresentMon recorded windowed CPU presentation intervals while the desktop was
locked. These measurements establish local CPU behavior, not visible gameplay
FPS or a GPU performance guarantee.

All 67 CTest checks pass, including neutral/enemy/unknown and changing-team
reads, actual-versus-perceived team separation, rejected vtables and inaccessible
memory. The complete three-DLL chain and matching patch catalog are deployed
and pass Windows verification. Steam, Proton and Wine were not exercised here.
Custom-model visual inspection was unavailable while Windows was locked;
satellite/cinematic views and save/load still need their existing qualification.

## Other useful work

1. Batch repeated ruin geometry while keeping each destructible game object
   and updating its visible representation when it is destroyed. Scrap needs
   equivalent pickup/removal handling; a permanent static copy would be wrong.
2. Give glow a distance/material policy that preserves emissive effects and
   their occlusion. Disabling the pass is a useful measurement but changes
   appearance and is not a production fix.
3. Investigate skeletal model LOD/GPU deformation for the heavier pilots and
   custom craft. Software deformation is a measurable cost; skipping valid
   shadow/glow pose updates is not a safe shortcut.
4. Add a distant terrain representation with continuous silhouette and boundary
   transitions, so keeping the horizon need not draw all distant geometry at
   the current detail level.
