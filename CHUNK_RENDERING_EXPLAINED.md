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

The uninstaller removes the deployed OpenShim proxy DLL and its co-deployed
`patches.json`; it intentionally leaves user configuration and logs alone.

There is no `PersistentConfig.Initialize -> EnsureBundledOpenShimInstalled` mission
path anymore, and no mission restart is required just to stage a bundled DLL. The
installer is the deployment authority; the runtime only validates what is present
when the game starts.

For current platform-specific commands and DLL-only/asset-pack behavior, treat
`README.md` as the user-facing source of truth.

---

## Current status

- Vehicles: working when compatible chunk assets are detected.
- Buildings: working, including the previously-broken faction-twin buildings
  (correct chunk shapes; twin *textures* are the documented limitation above).
- Pilots: working for all four, via hand-named piece meshes.
- Generic fallback: covers remaining identified edge cases so chunk rendering does
  not silently disappear when a specific source piece is unavailable.
- DLL-only OpenShim: supported; chunk rendering remains safely unavailable without
  the compatible asset pack while unrelated native fixes continue to operate.
- Deployment: installer/uninstaller scripts are the supported installation path;
  mission Lua no longer self-installs or stages `winmm.dll`.
