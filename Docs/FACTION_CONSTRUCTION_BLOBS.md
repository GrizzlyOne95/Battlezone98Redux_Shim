# Per-faction construction blobs

Setting `openshim.ini` `[Display] FactionConstructionBlobs = 1` (default `0`) lets a mod replace
the stock construction puff with a render effect, chosen per faction. The puff is drawn over a
build in progress.

With the setting off, nothing is installed. The patch rows are dropped before the batch, so the
exe stays byte-identical. The feature is display only, because the blob list and renders are
local render state, so it also runs in multiplayer. A restart is required.

## Mod side

Optional keys in `cnstblob.odf`, section `[ConstructionBlob]`, next to the stock ones:

```ini
[ConstructionBlob]
blobTexture  = "bpuff.0"          ; stock sprite: the fallback
blobFrames   = 14
blobVariance = 3
blobRender   = "cnstbl.render"    ; default for every faction (optional)
blobRenderA  = "cnstbla.render"   ; American  (ODF names starting with a)
blobRenderS  = "cnstbls.render"   ; Soviet    (s)
blobRenderC  = ""                 ; Chinese   (c): empty forces the stock puff
blobRenderB  = "cnstblb.render"   ; Black Dog (b)
```

How the keys are read:

- **Faction.** The faction is the first letter of the ODF being built: the producer's build
  class, or the constructor's target.
- **Value.** Each value names an engine render resource (`file.section`), the same kind as
  `muzzleRender` (see `Docs/ODF_MUZZLE_FLASH.md`).
  - A name is 1 to 63 printable characters, with no spaces or quotes.
  - Names resolve once, when the mission loads (ConstructionBlob PreLoad).
- **Fallbacks:**
  - A faction's own key wins, even when it is empty.
  - Otherwise the faction uses `blobRender`.
  - An absent, empty or invalid name keeps the stock sprite.
  - So does a name that is not a render. It is logged as `[CNSTBLOB] ... is not a render
    resource`.

### Render file format

A render is an ODF whose sections each have a `renderBase`. The section that the key names is
the root. This one-layer example is enough:

```ini
// cnstbla.odf  ->  blobRenderA = "cnstbla.render"
[Render]
renderBase = "draw_multi"
renderCount = 2
renderName1 = "cnstbla.mist"
renderName2 = "cnstbla.light"

[Mist]
renderBase = "draw_twirl_trail"
emitDelay = 0.03
emitVelocity = "0.0 2.0 0.0"
emitVariance = "3.0 2.0 3.0"
emitLife = 1.2
textureName = "cnstbla_mist"       ; Ogre material name (BZSprite/Additive)
startColor = "255 255 255 200"
finishColor = "255 255 255 0"
startRadius = 1.5
finishRadius = 4.0
animateTime = 1.2
rotationRate = 1.5

[Light]
renderBase = "draw_light"
startColor = "90 160 255 255"
finishColor = "90 160 255 255"
startRadius = 18.0
finishRadius = 18.0
attenuateQuadratic = 1.0
lensFlare = false
```

- `textureName` is an Ogre material name. Add a material such as
  `material cnstbla_mist : BZSprite/Additive { set_texture_alias DiffuseMap cnstbla_mist.png }`.
- For a 16-frame puff sheet (4x4 grid), slice it into a sprite table instead. Add one
  `"cnstbla.N" cnstbla_mist x y w h ...` row per frame, and draw with a sprite-based
  `renderBase`.
- Grayscale-on-black art is meant for additive materials. Tint it with `startColor` /
  `finishColor`.

## Runtime behaviour

The feature keeps one pooled render instance per active build (owner + target). The pool holds
16 instances, which is the stock list capacity.

- **Placement.** The render is created at the first blob of a build and moved to the blob's
  sphere centre each pass. That blob's stock sprite is suppressed.
- **Release.** A build that adds no blob in a simulation pass is released at the next
  ConstructionBlob Control. That covers a finished or cancelled build and a dead owner. Scene
  teardown and mission load release everything.
- **No respawning.** The feature never spawns a render per frame. If a create or update fails,
  or the render ends itself, the stock sprite is used for the rest of that build.
- **Looping.** Author the render so that it loops (an emitter, not a one-shot). A render with a
  finite life falls back to the stock puff once it ends.
- **ODF reads.** Reading `cnstblob.odf` uses the shared ODF item reader. If it is unavailable,
  the log shows `odf=unreadable` and every faction stays stock.
- **No progress scaling.** The render is not scaled by build progress. The muzzle render
  contract is qualified only for orthonormal poses, so a scaled basis is not passed. Author
  growth with `startRadius` / `finishRadius` instead.
- **Logging.** `[CNSTBLOB]` lines log three things, each once per change:
  - the gate decision
  - the resolved names per faction
  - the first few create and release events

## Engine side (GOG 2.2.301)

| What | Address | Source |
| --- | --- | --- |
| ConstructionBlob vtable | `0x008778A0` | `scripts/audit_vtable_hooks.py` finds one copy of each hooked slot |
| PreLoad, slot +0x08 | `0x0049BF60` | Decomp `FUN_0049bf60`: reads `cnstblob.odf` and blobTexture into `this+0x16C` |
| Control, slot +0x18 | `0x0049C050` | Decomp `FUN_0049c050`: `blobIndex` modulo `blobVariance`, resets the end pointer `this+0x168` to `this+0x28` |
| Submit, slot +0x20 | `0x0049C150` | Decomp `FUN_0049c150`: draws entries `this+0x28` up to `[this+0x168]` |
| AddBlob | `0x0049C0A0` | Decomp `FUN_0049c0a0`: appends a 0x14-byte `{x,y,z,r,scale}` entry while the end pointer is below `this+0x168` (16 entries) |
| Producer::UpdateBuild | `0x005AEE30` | Decomp `FUN_005aee30`: build class at `this+0x300`; one caller, at `0x005AD795` |
| ConstructionRig::UpdateUnbuild | `0x0049CDF0` | Decomp `FUN_0049cdf0`: target class at `this+0x370`; one caller, at `0x0049ED0B` |
| Render find / update / detach | `0x0044E4C0` / `0x0044DCA0` / `0x0044DC60` | Existing WeaponPresentation resolves (muzzleRender) |

These match BZ 1.5 `all_decompiled.c`:

- ConstructionBlob: lines 244718-244873 (Control at 244733)
- Producer::UpdateBuild: lines 216640-216666
- ConstructionRig::UpdateUnbuild: lines 153840-153866

The class offset `+0x370` is UNVERIFIED beyond that decompile. If it is wrong, the class is not
a valid ODF and that faction lookup returns stock.

## Hooks

- **Slot replacements.** PreLoad, Control and Submit are swapped in their vtable slots. Each swap
  is guarded by its stock pointer.
- **Call-site wraps.** The two update calls are REL32-wrapped, with an identity check against
  the `engine_addresses` rows.
- **Tagging.** Each update wrapper records the list slot that the stock code appended. If that
  build's faction has a render, it touches the pool and tags the slot as suppressed. The tag
  keeps the entry's x and scale bits, so a slot the wrapper did not see is drawn as stock.
- **Drawing.** Submit takes the fast path (one stock call) unless some entry is suppressed.
  Otherwise it compacts the kept entries, calls the stock Submit, and restores the list and the
  end pointer in a `__finally` block.
- **Memory.** No per-frame allocation and no layout change.

## Reusing it for the portal blob

The portal blob is `portblob.odf`. Redux PreLoad `FUN_006607f0` loads the `rpuff`/`bpuff`
sprites, and the portal blob is a sibling emitter with the same shape. To reuse this feature
for it:

1. Find the portal blob's vtable and its Control/Submit slots.
2. Find its add site(s).
3. Instantiate a second `BlobRenderPool`, with its own effect table read from `portblob.odf`.

The parser, the pool and the backend (`CreateNative` / `UpdateNative` / `DetachNative`) are
generic. This feature does not implement it.
