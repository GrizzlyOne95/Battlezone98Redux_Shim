# Automatic Ogre destruction pieces

`[General] ChunkMeshes` now generates render meshes from the dying object's
original Ogre mesh and skeleton. It no longer requires an external chunk
payload pack. Existing packs remain a fallback for unsupported source assets.

The legacy engine still creates the physical fragments and controls their
velocity, collision and lifetime. OpenShim reads the source entity's actual
resource name and group, extracts bone groups from serialized vertex/index
streams, and renders those groups on the existing physical fragments. A face
belongs to exactly one group, including faces crossing groups or carrying
multiple bone weights. The strongest aggregate weight wins, with stable ties.
Unweighted faces belong to the unique skeleton root when one exists.

Generated static meshes retain materials, normal/tangent/color/UV streams and
use the skeleton's derived bind pivot. They are cached automatically under
`openshim/cache/chunks/native/v3/<content fingerprint>/<bone>.mesh`. The user
does not need an exporter or a separate asset pack. The fingerprint includes
both source resources, and the per-mission lookup is cleared at initialization.

Skeleton quaternions are decoded from Ogre's serialized `x,y,z,w` order before
deriving parent rotations, scales and translations. The local 1.0.0.45 fix
corrects child pivots that were previously mirrored or displaced, causing wings
and building parts to orbit an invisible center. Cache version 3 regenerates
pieces automatically; version 2 output is ignored. This change runs during
cached mesh preparation, with no new per-frame work or physics changes.

Only the fragment's own geometry name can select a generated group. Unnamed
nodes and empty groups cannot borrow sibling geometry or another craft's mesh.
Exporters' numeric duplicate bone suffixes are accepted only when there is
one possible match. Stock explosion chunklets remain a separate engine effect.

If extraction or group lookup fails, small stock debris provides the final
render fallback. OpenShim emits the two canonical stock chunklet shapes already
embedded in its renderer into `openshim/cache/chunks/fallback/v1/`. They use
the game's `scarpmat2` material and need no skeleton or external asset pack.
Selection is deterministic; named `chunk1`/`chunk2` keep their matching shapes.
Supported model pieces take precedence, and unsupported models can still use
authored craft-specific payloads. Small static stock shapes take precedence
over arbitrary generic debris from packs; those remain a last resort if the
generated fallback cache cannot be written. This adds no physics
objects and does not change fragment count, velocity or lifetime. Cache-write
failures back off until the next mission and leave stock effects intact.

## Gameplay performance

Generated stock fallback shapes use the existing shared generic-debris batch,
after their exact resource names, sizes and content hashes have been verified.
This avoids a separate render Entity and shadow passes for each tiny fallback
bit. The batch retains the existing unit-scale guard and rehydrates Entities
when batching is unavailable. Custom vehicle pieces keep their own geometry
and materials; they are never classified as generic debris.

The world render queue owns proxy submission while its callback is active.
Flame submission stops adding the same pieces again, and resumes as a fallback
if the world driver stops running. Each camera/material traversal still gets
its own submission. Tracking reuses the payload captured at fragment creation,
after checking its live geometry identity, instead of rebuilding resource
candidate lists on every simulation update. Named stock chunklets take a direct
two-template lookup; anonymous fragments take the static stock batch.
Ordinary lifecycle logging is limited to 12 samples and fragment-tree logging
to 16 samples, avoiding thousands of synchronous writes during destruction.
Explicit diagnostic budgets and verbose capture remain available.

Native output has a versioned, content-validated index. Valid caches skip
extraction and file writes. Cache validation runs at startup before gameplay,
with limits of 128 models, 8,192 piece names and 64 MiB of payload reads. Only
names and triangle counts remain in memory across mission changes. Source
resource fingerprints still prevent one mod from borrowing another's pieces.
An incomplete or corrupt cache regenerates safely. Unsupported source meshes
and failed writes are remembered for the current mission instead of retried
for every fragment.

On a genuinely new model, extraction remains a one-time first-use operation.
Faces are grouped in one pass rather than rescanned for every skeleton bone;
the skeleton-link lookup skips vertex-buffer parsing. Rendering remains bounded
by the existing 256-slot cap, with no additional simulation objects or changes
to fragment lifetimes. Extra visible geometry can still have a rendering cost;
this is not a promise of zero overhead for arbitrary assets and hardware.

## Compatibility and limits

- Reads little-endian Ogre mesh versions 1.41, 1.8 and 1.100, and skeleton
  versions 1.10 and 1.80. Uses the shipped Ogre DLL's exported functions and
  its two-word SharedPtr / DataStream ABI; no replacement Ogre is loaded.
- Reads bytes directly into shim-owned buffers. Returning a large Ogre STL
  string to the newer shim CRT is unsafe because allocation alignment differs.
  Stream control blocks are released through the owning DLL's destructor and
  allocator.
- Requires triangle lists, float3 positions and a usable skeleton resource.
  The engine also needs native fragment nodes whose geometry names correspond
  to skeleton groups. A monolithic ungrouped mesh cannot acquire an authored
  physical fracture hierarchy from rendering data alone.
- Pieces use bind geometry, not a snapshot of the animated pose at death.
  Unsupported or malformed input fails closed and can use existing payloads.
  A recognized model's absent group uses only the stock debris fallback.
- Cache paths use the game installation root and safe normalized bone names.
  The Ogre group preserves active-mod resource selection. GOG Windows runtime
  is validated here; Steam, Proton and Wine were not exercised in this pass.

## Validation

The pivot correction (local 1.0.0.45) passed all 67 CTest checks, including
serialized Ogre identity/rotated quaternions and translated/scaled parent
hierarchies. The current ISDFC audit extracted 528 meshes; 27 lacked a usable
skeleton resource, and the existing old cockpit failed its bone-assignment
check. Offline Sabre wing pivots moved by 3.28 units and a recycler piece by
13.43 units. Corrected wing bounds agree with the engine's fragment-local
geometry, rather than retaining the displaced model-space centers.

A GOG DX9 probe destroyed a Sabre, recycler, ISDF/Scion buildings and a
skeletonless vehicle, assigned 86 native model pieces plus stock fallback
debris, and exited with code 0. DX11 completed the same five events and
assigned the same native pieces, but faulted during graphics shutdown. The
same exit fault and driver-thread stack reproduced with the previous
1.0.0.44 binaries; it remains a separate unresolved issue. This pass verifies
geometry and runtime binding; visual motion was not inspected. All temporary
mission files, mod selection and Ogre configuration were restored.

The pure extractor tests cover pivot rebasing, materials, rigid/soft/seam face
ownership, missing skeletons, endianness and every truncation of the fixture.
The full CTest suite passed (66 tests). An installed ISDF Chronicles asset
audit extracted 527 meshes, found 24 without an available skeleton link, and
rejected one old cockpit with invalid bone assignments. Live GOG DX11 tests
loaded generated stock and custom pieces, including a run with external
payload directories temporarily removed. Raw logs and the asset audit are
local evidence outside the public repository.

The stock-fallback regression passed with external payload directories removed:
the generated fallback shapes and native fvtank pieces both reached the live
Ogre render callbacks. The same bounded run destroyed a skeletonless zvtnk
vehicle and completed all four destruction events. The 66-test suite and
Windows deployment verification passed again for the fallback update.

The performance update (local 1.0.0.42) passed all 66 tests and live GOG
DX11/DX9 destruction probes. Each probe spawned 24 craft, then destroyed eight
at once in three waves. At 3840x2160, DX11 with 8x MSAA averaged 10.58 ms per
frame over the destruction interval with chunk meshes enabled, versus 7.63 ms
disabled; the enabled 95th percentile was 12.68 ms. DX9 without MSAA averaged
11.60 ms enabled versus 8.49 ms disabled. These are CPU presentation intervals,
not isolated GPU timings or a guarantee for other machines and missions.
The first burst still produced a 453 ms DX11 frame (196 ms with the feature
disabled), and a 403 ms DX9 frame. Cached preparation itself measured below
2 ms, so further investigation is required to attribute the remaining hitch.

Forced batch failure restored every logged eligible slot to an Entity, and
both generated stock shapes and native pieces reached actual Ogre/D3D draw
callbacks. This test deliberately enables diagnostics and is excluded from
timing comparisons. Captures with missing presentation events, incorrect
effective feature settings or incomplete mission startup are also excluded.

The mission 14 follow-up (local 1.0.0.44) attributed the first-death stall to
recursive Ogre resource discovery. Resource-group initialization now runs once
in the existing world callback before debris becomes active, retaining the
original first-use path if warming fails. A profiler-free 4K DX9 mission capture
reduced the largest measured gameplay frame from roughly 300 ms to 38 ms;
initialization itself took 265 ms during loading. This moves that work rather
than eliminating it. Shader/GPU uploads and cold extraction can still stall.

A cold-cache regression temporarily moved the entire generated native/v3 cache
aside. New fvtank, fvhsent and fvsentry pieces were generated after startup and
reached indexed Ogre/D3D draws through the already initialized resource group.
The original cache was restored afterwards. All 67 tests and the complete
Windows deployment check pass. See [mission 14 performance](ISDF14_PERFORMANCE.md)
for attribution, the separate reticle optimization and qualification limits.
