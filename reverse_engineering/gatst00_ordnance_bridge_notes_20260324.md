# `gatst00` ordnance bridge notes

## Goal

Trace how stock ordnance like `rocket.odf` with `shotGeometry = "gatst00.geo"`
gets from legacy geometry into the Redux/Ogre render path.

## Asset anchor

- `rocket.odf` uses `shotGeometry = "gatst00.geo"`.
- `gatst00.mesh` exists as a same-basename Ogre asset.

That suggests a basename bridge rather than a submesh-name bridge.

## Key class layout evidence

`OrdnanceClass` contains:

- `ord` at `+0x30`
- `ent` at `+0x34`
- `freeOrd` at `+0x38`

See:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/llvm/pretty_classes.txt`
  around lines `14850-14873`

`Ordnance` contains live Ogre pointers:

- `OgreEntity` at `+0xd4`
- `OgreNode` at `+0xd8`
- `OgreSkeleton` at `+0xdc`

See:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/llvm/pretty_classes.txt`
  around lines `14833-14838`

`tagENTITY` contains the Ogre-side basename and filename fields:

- `OgreEntityBaseName[16]` at `+0xc4`
- `OgreFilename[16]` at `+0xd4`
- live Ogre pointers immediately after that

See:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/llvm/pretty_classes.txt`
  around lines `231794-231798`

## Geometry load path

`FUN_004e3290` is the generic "add geometry by name" helper.

It:

- normalizes the geometry name
- calls `FUN_004e3810`
- stores the resolved legacy geometry handle

See:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_004e3290-004e3290.c`
  lines `23-52`

`FUN_004e3810` is the legacy `.geo` cache loader already identified earlier.

## Ordnance class build path

`FUN_00586440` is from `fun3d\\OrdnanceClass.cpp` and is the important class-side
builder.

It does three critical things:

1. Creates `freeOrd` and `ord` objects with `FUN_0062ccc0`.
2. Reads the `shotGeometry` config string into `local_24`, and if present calls
   `FUN_004e3290(local_40[0xc], local_24, 0, 0)` to load the legacy `.geo`.
3. Creates the class entity bridge with `FUN_0062c4a0(...)`, stores it in
   `local_40[0xd]`, strips the geometry extension, and writes the stripped
   basename into the entity.

See:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_00586440-00586440.c`
  lines `68-71`
- same file lines `82-99`
- same file lines `100-129`

Interpretation:

- `local_40[0xc]` lines up with `OrdnanceClass::ord`
- `local_40[0xd]` lines up with `OrdnanceClass::ent`
- `local_40[0xe]` lines up with `OrdnanceClass::freeOrd`

So the stock ordnance path is:

`shotGeometry string` -> `legacy geometry object` -> `class entity bridge`

not:

`legacy GEO directly renders itself`

## Runtime build / clone path

`FUN_00586ff0` is also from `fun3d\\OrdnanceClass.cpp`.

It:

- allocates or reuses a `freeOrd` object
- clones the previously loaded `ord` geometry into the live object with
  `FUN_004e3430`
- initializes runtime state and returns the built ordnance object

See:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_00586ff0-00586ff0.c`
  lines `10-39`
- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_004e3430-004e3430.c`
  lines `11-25`

This means the live ordnance instance inherits geometry from the class-side
`ord` object, while the class also keeps a separate entity bridge carrying the
Ogre basename.

## Entity creation bridge

`FUN_0062c4a0` creates the entity record from a legacy object/geometry holder.

It:

- allocates a new entity slot
- links it to the source object in `*local_8 = param_1`
- computes bounds and radius
- calls follow-up entity setup routines

See:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_0062c4a0-0062c4a0.c`
  lines `23-58`

## Working conclusion

For stock ordnance like `gatst00`:

1. `shotGeometry = "gatst00.geo"` is loaded through the generic legacy geometry
   cache path.
2. `OrdnanceClass` creates a separate entity bridge object.
3. The stripped basename from `gatst00.geo` is copied onto that entity bridge.
4. The renderer can then use the entity basename to resolve the Ogre-side asset
   (`gatst00.mesh`) without needing any fragment-name or submesh-name lookup.

## Why this matters for chunks

This confirms Redux already has a stock bridge for standalone legacy geometry
objects that works by entity/basename, not by direct legacy rendering.

That supports the chunk conclusion:

- `gatst00` works because it is a standalone geometry basename
- `AGR11BDA`-style VDF fragments do not, because they are child GEO identities
  inside a parent asset and do not naturally become standalone entity basenames

So chunk restoration still needs a different bridge:

- native chunk simulation stays as-is
- fragment GEO identity must be mapped into the parent Ogre asset
- then a shim proxy can render the right fragment

## Shim application

The closest stock analogue we can reuse in OpenShim is not the standalone
`gatst00` basename itself, but the owner-side entity naming pattern.

Practical implication:

- when a live native chunk is tracked, probe the chunk owner's `GameObject`
  bridge for its `ownerEntity`
- read the owner's inline entity basename or filename fields
- synthesize the proof mesh name from that owner-side identity
- use that owner-derived mesh name for the Ogre proxy, falling back to the
  hardcoded proof mesh only when the probe fails

That pushes the chunk test path closer to stock ordnance behavior:

- stock ordnance: `shotGeometry` basename copied onto `tagENTITY`
- chunk proof path: owner entity basename or filename copied into shim slot
  state, then used to choose the mesh proxy

This is still not the final fragment renderer because it does not yet isolate a
submesh like `AGR11BDA`, but it is a stronger proof path than a permanently
hardcoded `avtank.mesh` special case.
