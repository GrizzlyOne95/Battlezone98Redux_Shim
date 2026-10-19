# How Redux poses legacy SDF/VDF animated parts

Redux keeps BZ1's ANIM chunk as the source of truth for moving parts: building doors, turret
heads, power-plant pistons, and the like. The `.skeleton` supplies only the bind pose and
the bone names. Its animation clips are never played. Addresses below are in the GOG
`battlezone98redux.exe`.

## Engine path

| Step | Address | What it does |
|------|---------|--------------|
| Bind | `FUN_0067e260` | For each GEO, looks up the skeleton bone **with the GEO's name**, marks it manually controlled, and stores it at node+0xC8. A GEO with no matching bone does not animate. |
| Per frame | `FUN_00681a00(node, M)` | Takes the part's interpolated ANIM matrix and converts it to a quaternion with `FUN_0081f1e0`. Writes bone orientation **(w, −x, y, z)** and position **(−px, py, pz)**. |
| Matrix → quat | `FUN_0081f1e0` | Standard Shepperd conversion. It takes the non-trace branch only when m0+m4+m8 ≤ 0, and both branches are correct. |
| Object root | `FUN_006802b0` / `FUN_00681610` | The whole object is mirrored in **Z**, not X. |

So part poses are mirrored in X (SDF → Ogre) on top of the `.skeleton` bind pose, while the root is
mirrored in Z.

## Key data

- Rotation keys are quaternions stored **(w, x, y, z)**.
- Position keys are in the parent's space and equal the GEO's `matrix2` position (`sbwpow`, `avrecy`).
- **Stock moving parts key rotation on every frame** and carry at least 2 position keys. The sparse
  doors in `abhang` are the outlier, so don't use them as the reference.
- Stock skeletons are rooted at `U3DMesh`. A custom skeleton rooted at the body GEO also works: both
  keep model-space vertices and parent-relative bone positions.

## When a custom animated part looks wrong

1. Dump 3+ working stock models first (`StockODFFiles\*.sdf`, `BZ_ASSETS\common\models\*.mesh`) and
   diff their conventions against yours (key density, key counts, bind pose):
   `python sdf_anim_tools.py anim <file.sdf>` and `python sdf_anim_tools.py bones <mesh> <skeleton>`.
2. **Check face orientation before blaming the animation.** A part that rotates past 90° exposes
   faces that were hidden at rest. If one of them is wound inward, it is back-face culled and the part
   seems to vanish or "draw in the wrong place". `python sdf_anim_tools.py faces <mesh> <skeleton> [bone]`
   flags faces whose normal points into the part. The test is exact for convex parts. Concave parts,
   and plates embedded in a surface (their hidden backs), also report legitimate hits.
3. Only then run in-game single-variable tests, at reduced swing angles (45°, 90°), to separate the
   swing direction from visibility.

Worked case (2026-10-19, prototype `avdropo` dropship ramp): runs 8–20 showed only a slab and a
small patch at the stern. The ANIM data and the swing direction were correct throughout. The ramp's
inner cap had been generated wound inward, so once the ramp was open the deck was culled, leaving
only the backs of the decal plates. Flipping those six triangles (and their normals and the tangent
`w`) fixed it.
