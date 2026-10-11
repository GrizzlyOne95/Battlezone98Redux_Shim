# How Destruction "Chunks" Were Brought Back — A Plain-English Writeup

*Audience: anyone mildly technical. No reverse-engineering background assumed.*

## The one-sentence version

When a vehicle or building dies in Battlezone 98 Redux, the original 1998 engine
shattered it into little flying mesh **chunks**. Redux kept the game logic that
spawns those chunks but never draws them, so deaths looked flat. OpenShim (a small
`winmm.dll` that loads alongside the game) reconnects the spawn logic to the
renderer and feeds it replacement chunk meshes, so things visibly blow apart again.

---

## Background: what a "chunk" is

In the 1998 game, every craft and building had a **destruction model** — a version
of its 3D model pre-cut into pieces (a tank's radar mast, hull panels, tracks; a
building's walls and roof). On death the engine spawned each piece as a short-lived
physics object that tumbled away. Redux (the modern remaster) rebuilt the renderer
on top of the Ogre 3D engine. The death logic survived the port, but the piece of
code that actually *submitted* those pieces to be drawn did not. The objects existed
in memory, moved correctly, and were never rendered — invisible confetti.

## The three problems we had to solve

Getting chunks back on screen meant solving three separate things:

1. **Catch the moment a chunk is born.** The engine still creates chunk objects
   internally. We hook the internal "create chunk" and "fragment object" functions
   so OpenShim gets a callback every time one appears.

2. **Figure out *what* the chunk is.** A raw chunk object just says "I am piece
   `SCZ11RAD` of something." We have to map that back to a real craft ("that's the
   radar dish of the Scion tank") so we can load the right-looking mesh for it.

3. **Actually draw it.** Redux never routes world objects through Ogre's normal
   scene graph, so simply creating an Ogre object isn't enough — nothing would
   submit it each frame. We hook the game's own per-frame render-queue function and
   append our chunk meshes to it so they're drawn like any other world object, in
   the correct position relative to the map.

Once those three are in place, deaths shatter again.

---

## Identity: the hard part

Step 2 — "what is this chunk?" — is where most of the real work went.

### Vehicles: easy

A dying vehicle is a live game object with a known model name, so we can look up its
piece list directly and load the matching chunk meshes. Vehicles worked almost
immediately.

### Buildings: no ID tag

Building chunks are different. The internal building node has **no back-link to the
game object that owns it** — the field that would point to "this belongs to that
power plant" is empty. So a building chunk arrives anonymous.

We work around it by snapshotting identity from the **fragment root** (the top of
the shatter tree) at the instant the building is torn apart, then handing that
identity down to each piece as it's created. This happens on a single thread in a
tight sequence, so the "who is dying" context is reliably available while the pieces
spawn.

### Faction twins: the genuinely unsolvable-at-runtime case

Some buildings come in matched pairs — one per faction — that are *geometrically
identical* and even share the same internal piece names (e.g. the two power plants
`abspow` / `bbspow`; also the two turrets, storage, and comm towers). When such a
building dies, the only identity we can recover is the shared piece name, which maps
to **both** twins. We can't tell which faction's version died.

Our resolver handles this by trying every craft the piece name maps to and using the
first one whose mesh file exists on disk. Because the two twin folders ship *the same
piece filenames*, the chunk shape is always correct. The catch: the pick is
alphabetical, so it always grabs the first faction's **texture**. Result: a
second-faction building can shatter into correctly-shaped chunks wearing the wrong
faction's skin.

**This is a known, documented limitation, not a bug we can patch at the current
layer.** Fixing it properly requires deeper reverse-engineering to recover the dying
building's true identity before the shatter — a separate, larger task. Hangar
buildings, for what it's worth, are *not* affected: their piece names are
faction-prefixed (`abh11*` vs `bbh11*`), so each resolves to its own textures.

### Pilots

Ejected/dead pilots shatter into body pieces. These needed hand-built mesh copies
named after the legacy skeleton pieces (pelvis→`ctr`, spine→`trs`, head→`hed`, and so
on). Each pilot uses a slightly different naming prefix, and two of the four pilots
have no head piece at all. Once the files were named to match, pilots shatter
correctly.

### Generic fallback

Anything we still can't identify (odd edge cases, missing source pieces) falls back
to a small set of neutral debris meshes, chosen deterministically so the same object
always breaks apart the same way. Nothing ever silently fails to render.

---

## A couple of sharp edges worth knowing

- **Object recycling.** The engine reuses memory addresses for new objects. Our
  caches are keyed by address, so we validate the cached piece name against the live
  one and throw the cache entry away on a mismatch. Without this, a fresh chunk could
  briefly inherit the *previous* object's identity — tanks wearing another tank's
  panels in big battles.

- **Don't add material files to the chunk folders.** The chunk mesh folders are
  registered as Ogre resource locations. Dropping a `.material` file in one that
  redefines a name the game already uses crashes the game at startup. Payload folders
  may only define brand-new names.

---

## What ships, and how it is installed now

OpenShim is no longer installed by mission Lua. Runtime deployment and asset-backed
features are deliberately separate:

1. **OpenShim runtime** — `winmm.dll`, `scripts/patches.json`, configuration, and
   the release-bundled compatibility resources are installed by the supported
   installer scripts. On Windows, `scripts/install_windows.ps1` downloads the
   versioned `OpenShim-Suite.zip`, verifies its published SHA-256, detects supported
   Steam/GOG installs, and deploys the suite beside the game. Linux/Proton uses the
   corresponding Linux installer path documented in `README.md`.
2. **Chunk mesh assets** — destruction meshes and their manifest are asset-backed
   content. They are supplied by a compatible OpenShim/Campaign Reimagined asset
   package rather than by the DLL-only runtime itself.
3. **Capability detection** — OpenShim validates the installed asset pack through
   `OpenShimAssets.ini` and resource probing. `ChunkMeshes=1` in configuration does
   not force the feature on when compatible mesh resources are absent.

That separation is intentional. A stock 2.2.301 installation can run OpenShim as a
DLL-only native patch and still receive engine, gameplay, multiplayer, UI, and
diagnostic fixes. Death-chunk rendering becomes available only when the compatible
chunk payload is detected.

### Windows install / uninstall

The supported Windows install command is:

```powershell
irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_windows.ps1 | iex
```

The supported Windows uninstall command is:

```powershell
irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_windows.ps1 | iex
```

The uninstaller removes everything the installer deployed: the three-binary
load chain, `patches.json`, the Enhanced renderer resources and asset manifest,
the UI widget tiles, and the installer's own backups. It intentionally leaves
`openshim.ini`, `net.ini`, and logs alone. `scripts/uninstall_linux.sh` is the
Proton twin.

There is no `PersistentConfig.Initialize -> EnsureBundledOpenShimInstalled` mission
path anymore, and no mission restart is required just to stage a bundled DLL. The
installer is the deployment authority; the runtime only validates what is present
when the game starts.

For current platform-specific commands and DLL-only/asset-pack behavior, treat
`README.md` as the user-facing source of truth.

---

## Skinned gibs (people)

Pilots, soldiers and zombies are skinned models, so the legacy "one chunk per
node" split only ever gave them crude stand-in pieces. With `[General]
SkinnedGibs = 1` (the default when the key is absent) OpenShim handles a
person's death itself:

1. **Catch the death.** `ChunkEffect::FullFragmentObject` is detoured whenever
   SkinnedGibs is on (GOG only; byte-guarded). If the fragment root is a
   `.?AVPerson@@`'s own object tree, the hook snapshots the person's world
   entity *before* the engine shreds the tree: its parent node's world
   position/orientation/scale and every bone's current derived pose and
   inverse bind pose. Anything that is not a person passes straight through.
2. **Split the body once per model.** `NativeChunks::ExtractGibs` reads the
   person's own `.mesh` and `.skeleton` and cuts them the way
   `scripts/export_gib_payloads.py` does: each triangle goes to its dominant
   bone, small bones (fingers, toes, clavicles, nubs...) roll up into their
   parent, the weapon submesh becomes one piece, and every cut is closed with a
   torn-flesh cap: concentric rings that follow the cut's own shape (a thin
   dark skin edge, a pale fat band, then muscle to a slightly bulged centre;
   cuts through limbs and the neck end the muscle in an ivory bone ring around a
   dark marrow core), with smooth normals and planar UVs. Each zone is its own
   submesh with its own material (`openshim_gib_flesh` for the muscle,
   `openshim_gib_flesh_skin/_fat/_bone/_marrow` for the rest). The rim is the
   cut itself; inner rings keep each rim point's ray, are Laplacian-smoothed and
   never reach the ring outside them, so there are no folds, and every triangle
   is validated (a loop that folds is retried with weaker inset and smoothing,
   then keeps a plain fan, as do tiny, very large, very non-planar or
   non-star-shaped loops). The small ragged offsets hash the welded positions,
   so a cut looks the same on every run. The result is cached under
   `openshim/cache/chunks/gibs/v5/<hash>/` (vehicle caches are untouched; the
   startup prune deletes the superseded `gibs/v1/` tree). An
   authored split (`<payload dir>/<mesh basename>/gibs.txt` plus its meshes,
   written by the script) takes precedence over the runtime one.
3. **Pose, launch, simulate.** Each piece is spawned exactly where that limb
   was on the death frame and launched with the legacy chunk numbers (random
   ×10 per axis, +5 up, a kick away from the body's origin, the body's own
   velocity, random spin). OpenShim integrates them itself from the engine's
   chunk tick: gravity, a soft thud on the terrain (low bounce, high friction),
   lie still for `SkinnedGibsLinger` seconds, sink, disappear. At most
   `SkinnedGibsMax` gibs live at once; the oldest resting one is recycled
   first.
4. **No double bodies.** The body mesh is hidden, and the engine's own legacy
   chunks for that death keep simulating (their smoke and pops are unchanged)
   but the chunk renderer is told not to draw them. Nothing in the engine's
   chunk state is written.

The cut faces need no asset pack: OpenShim writes
`openshim_gib_flesh.material` (the muscle, white, wet, one texture unit),
`openshim_gib_flesh_zones.material` (skin, fat, bone, marrow as plain colours)
and a procedural, tileable 256x256 `openshim_gib_flesh.tga` (elongated muscle
bundles with pale perimysium lines, fibre striation, sparse fat marbling and a
few thin vessels, in deep red-brown) into the cache root before the payload
resource group starts. Hue lives in the texture and the material colours, not in
vertex colours: every DX11 path reads a packed vertex colour as raw RGBA (the
exported `D3D11Mappings::get(VertexElementType)` maps VET_COLOUR, _ARGB and
_ABGR all to R8G8B8A8_UNORM) while the stock and compatibility programs swizzle
with `.bgra`, so red would draw blue on whichever path does not. Each file is
regenerated when the version in its first line is stale; a file without that
marker is the user's and is left alone. The DX11 fixed-function compatibility
layer (`[Fixes] DX11LegacyMaterialCompat`) instantiates these passes (one
texture unit, modulate, or untextured); it does not evaluate dynamic lights or
specular, which is why the zone colours and texture carry the shading. A pack can
restyle the muscle by shipping its own `openshim_gib_flesh.material` (and the
other zones with `openshim_gib_flesh_zones.material`) at the top of a chunk payload directory
(`<mod>/chunkMeshes/` or `BZ_ASSETS/common/models/OpenShimChunkPayloads/`);
the generated copy then steps aside so the name is never defined twice.

Live test: `pwsh -File reverse_engineering/run_lcgibs.ps1` loads the lcbench world with
a debug-only Lua overlay (`reverse_engineering/test_missions/lcbench_gibs/gibs.lua`)
that spawns the four stock pilots and kills them one by one. It needs
`[General] SkinnedGibs = 1`; add `[Diagnostics] TraceSkinnedGibs = 1` for per-gib lines.

`SkinnedGibs = 0` restores exactly the previous behaviour. Set
`[Diagnostics] TraceSkinnedGibs = 1` for one log line per gib.

---

## Current status

- Vehicles: working when compatible chunk assets are detected.
- Buildings: working, including the previously-broken faction-twin buildings
  (correct chunk shapes; twin *textures* are the documented limitation above).
- Pilots: working for all four, via hand-named piece meshes.
- People (any Person model): SkinnedGibs replaces the body chunks with posed,
  capped limb gibs generated from the skinned mesh; verified offline on the
  ISDF Chronicles pilot (12 gibs, identical to the Python exporter), awaiting
  in-game confirmation.
- Generic fallback: covers remaining identified edge cases so chunk rendering does
  not silently disappear when a specific source piece is unavailable.
- DLL-only OpenShim: supported; chunk rendering remains safely unavailable without
  the compatible asset pack while unrelated native fixes continue to operate.
- Deployment: installer/uninstaller scripts are the supported installation path;
  mission Lua no longer self-installs or stages `winmm.dll`.
