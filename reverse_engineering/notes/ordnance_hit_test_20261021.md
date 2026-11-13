# Ordnance hit test and mesh-accurate impacts (2026-10-21)

Target build: GOG 2.2.301 (`battlezone98redux.exe`, unencrypted). Addresses are
absolute in that image. This note records addresses and behaviour only; no
decompiler output or PDB-derived data is reproduced here.

## Why impacts float

Shots are tested against bounding volumes, not triangles. For craft that volume is
one sphere around the whole object, so a shell that visibly flies a few metres over
a tank still counts as a hit. The engine reports the point where the shell crosses
that sphere, and the impact explosion spawns there. That is why sparks hang in the
air beside, in front of or above a hull.

## The shared hit test

Bullets and cannon shells go through one routine. Missiles reaching it through
the same simulate path is a working assumption here, not something confirmed
statically:

| Address | Role |
|---|---|
| `0x00480F40` | `Bullet::Collision` — `thiscall(this, float* t, double* endPos, float* normal)`, `ret 0xC` |
| `0x00480A30` | `IntersectGameObject` — the per-object volume walk Collision calls for each candidate |
| `0x00480627` | the call site inside `Bullet::Simulate` |
| `0x00479F30` | maps a hit obj76 root to its `GameObject` |

What Collision passes and gets back:

- It tests a **segment**, not a point. Start = the ordnance obj76 position
  (`[this+0x14]`; doubles at obj+0x48/+0x50/+0x58). The direction is
  `(endPos − start) / t`, so `t` is measured in velocity units, not metres.
- The candidate test uses the ordnance radius at obj76+0xAC, so shots are swept
  spheres.
- On a hit it shrinks `*t`, writes `endPos = start + t·dir` and the surface
  `normal`, and returns the root obj76 it hit. On a miss it returns 0.
- Owner skip: while byte `this+0xE0` is set, a candidate whose root equals
  `this+0xD8` is skipped. E0 clears once the shot's box stops overlapping its
  shooter. This keeps a fresh shot from hitting its own launcher.

What Simulate does with the result:

- It always moves the ordnance to `endPos`, hit or not.
- On a hit it calls `Hit` (vtable +0x14) with the `GameObject` and normal.
- `Hit` builds the impact explosion at `pos + 0.01·n`.

## Volumes tested

`IntersectGameObject` (`0x00480A30`) has two exclusive branches, chosen by the
collision entity's type at entity+0x24:

- **Type 3: per-part boxes.** It sweeps the shot's box against the object's
  boxes, then runs the per-part point test.
- **Anything else: one sphere.** The radius is entity+0x14 × 0.75, plus the
  ordnance radius. The hit `t` and `endPos` are where the swept centre crosses
  that sphere, and the normal is the radial direction.

Craft take the sphere branch. That has not been read off a live tank's type
field, but the live evidence leaves little doubt:

- With a close camera on one avtank shelling another, most impacts burst metres
  away from the hull, in front of it, beside it and above it.
- Only 11 of 119 engine hits (9%) touched the target's mesh, even with the cast
  extended 12 m past the engine point.
- A player aiming 4–5 m over a tank still scores hits while the shells visibly
  fly straight over.

The part tree that the mesh tier walks:

- child link +0x80, sibling link +0x7C;
- each part's matrix is relative to its parent (the root's matrix is world),
  with floats at +0x20..+0x43 (right/up/front) and the position at +0x48.

A mesh hit outside the sphere can never happen in this tier: the engine only
offers what the sphere caught.

## Where the impact position becomes the effect position

| Address | Role |
|---|---|
| `0x004CA0C1` | Explosion::Init, after splash damage is applied and before the render effect (class +0x64) and particle emitters read the explosion obj position |

At this site:

- `[ebp-0x98]` is the explosion; `[explosion+8]` is its class.
- The explosion obj76 is at explosion+0xC.
- The physics-kick centre used later by Explosion::Simulate is local obj+0xA0,
  transformed by the obj matrix.

Moving the obj position here moves what the player sees and leaves splash
damage untouched. Pulling obj+0xA0 back by the same offset keeps the kick
centre where it was.

## Multiplayer authority

Every machine simulates ordnance and its hits locally. Damage to a remote
object is gated in that object's `HitBy` on the owning machine. The
consequences:

- A purely visual change (moving the effect) cannot desync anything. It is MP-safe.
- Changing whether a shot hits changes local simulation and the owner's damage
  decision differently on each machine. It must be single-player only.

## ISDF Chronicles' geometry collision

ISDFC's vehicle-to-vehicle geometry contact tested **every pair of vehicles
every frame** against raw geometry, with no acceleration structure. In a busy
scene its own record put the cost at roughly 0.7 ms a frame. The lessons:

- Only test after a cheap broad phase has already said "hit".
- Never test triangles without a BVH.
- Cache the BVH per mesh.

## What OpenShim implements

`src/patches/mesh_impact.cpp`, geometry in `include/mesh_impact_geometry.h`.
patches.json rows: `BulletCollisionEntry` and `ExplosionInitEffectSite`.

1. Detour Collision. After the original returns a hit on a craft (kinds 1 and
   3–7), walk the root's part tree. Compose each part's world frame, then cast
   the same segment against that part's LOD0 triangles in part space through a
   BVH built once per geometry. The cache is keyed by the geometry pointer and
   validated by vertex count and a checksum.
   - Legacy geometry: vertex count at geo+4, float3 positions at +0xC, a face
     list at +0x14 (next at face+0x30, corner count at face+4, corner vertex
     index at face+0x40 + i·0x10). Faces are fanned into triangles.
2. **Visual tier**, `[Display] MeshAccurateImpacts`. For every engine hit on a craft:
   - Cast the shot line up to 12 m past the engine point. The engine point lies
     on the sphere, often short of the hull, and is often beyond this frame's step.
   - On a mesh hit, the effect goes to the surface point the shot strikes.
   - On a mesh miss (a sphere-only hit), the effect goes to the hull point
     nearest the engine point, within 10 m, using a closest-point query on the
     same BVHs.
   - At `0x004CA0C1` the explosion is moved only when its position is still the
     engine's (within 0.1 m).
   - Hit outcome, direct damage, splash and kick do not change, so the tier is
     MP-safe.
3. **Gameplay trial**, `[SinglePlayer] MeshAccurateHits`, gated off in network
   games:
   - A mesh hit rewrites `t`, `endPos` and `normal`.
   - A mesh miss re-runs the original with the missed root put in the owner-skip
     slot, so a craft behind it can still be hit. A second craft is
     mesh-tested too. A non-craft (building, terrain object) is returned as the
     engine found it.
   - A shot that misses every mesh flies on. This is the "between the cannon
     and the body" case.

Both tiers are off by default, GOG-only, and fail closed when the identity bytes
do not match.

## Live measurements (GOG, DX11, 1920×1080 windowed, background run)

Effect captures used lcbench `combat` (AI `Attack`, aimed fire) with a scratch
close camera on the target. The `firing` scenario is unsuitable: `FireAt` shoots
along the hull heading without aiming, so most shells hit the ground.

| Run | engine hits | mesh hits | snaps |
|---|---|---|---|
| combat, 4 avtanks, cockpit view, before the snap | 158 | 57 | — |
| combat, 2 avtanks, close camera, before the snap | 119 | 11 | — |
| combat, 2 avtanks, close camera, with the snap | 110 | 17 | 93 |

With the snap, every tested craft hit had its effect moved (110 of 110).

Frame times, lcbench at 40 avtanks, DX11, background run, PresentMon:

| Arm | combat mean / p95 / p99 ms | firing mean / p95 / p99 ms |
|---|---|---|
| base (both off) | 5.76 / 16.14 / 24.69 | 5.23 / 6.35 / 7.29 |
| visual | 5.17 / 5.63 / 6.04 | 5.34 / 6.57 / 7.44 |
| visual + gameplay | 5.22 / 5.88 / 6.30 | 5.44 / 6.22 / 7.14 |

The spread is run-to-run noise. The base combat tail and a single 435 ms
stall in the gameplay firing run are not attributable to the hook. Hook counts
at 40 avtanks: visual combat 700 engine hits, every effect moved (368 snaps),
average cast 5.4 µs. Gameplay combat: 1556 tested, 1069 passed through, average
cast 3.1 µs.

Cast cost: average 3–10 µs, maximum about 0.2 ms (the first BVH build). Six BVH
builds for avtank, 293 triangles, 0.18 ms total build time.

## Known limitations and a future gameplay tier

- The engine's craft sphere decides which craft are offered at all. A shot
  that grazes a long barrel outside the sphere is never tested. A full gameplay
  tier would need its own broad phase, such as a per-object mesh bound, swept
  against the shot.
- A snapped effect sits on the hull even when the shell visibly flew past.
  This matches what the engine already decided (it was a hit), but in the
  visual tier the shell's trail and the burst can disagree by a few metres.
- The gameplay mesh hit does not search for a nearer third object between the
  shooter and the mesh hit point.
- The explosion keeps the engine's normal for its orientation.
- No LOD selection call is made: the geometry currently attached to each part
  is cast.
- Missile coverage is unconfirmed. Proximity fuses and guidance do not pass
  through Collision in any case.
