# Multiplayer Vehicle Flags Notes

## Question

Did legacy Battlezone's player-selected multiplayer vehicle flags survive in Redux, and what is the most feasible way to restore them?

## Short Answer

Yes, the legacy flag feature was not removed wholesale.

- The old shell selection UI appears to be gone in Redux.
- The runtime flag display path appears to still exist in the Redux codebase family.
- Redux still carries flag-related strings, globals, and `FlagDisplay` PDB symbols.
- The safest restore path is likely:
  1. add a new lobby-side selector UI in OpenShim,
  2. scan a user flag folder from the shim/config side,
  3. convert arbitrary source images into the legacy network-safe packed flag format,
  4. upload that packed flag to the player's net data,
  5. reuse the surviving in-game flag renderer if it still fires.

## Legacy BZ1 Findings

The exact-match legacy corpus still exposes the full feature stack.

### Legacy selection and persistence UI

- `FlagList::FlagList`
  - File: `legacy_bz1_exact_full/.../FlagList-00550d25.c`
  - Scans `flag????.bmp`
  - Sets `Net::pcFlagName`
  - Builds the picker UI
- `PlayerNameList::ChangeFlag`
  - File: `legacy_bz1_exact_full/.../ChangeFlag-005562f4.c`
  - Stores the chosen filename
- Legacy wildcard asset loading string:
  - `flag????.bmp`

### Legacy upload path

- `SetMyFlag`
  - File: `legacy_bz1_exact_full/.../SetMyFlag-004de815.c`
  - Reads the selected file from `Net::pcFlagName`
  - Pulls BMP bits directly from the file
  - Uploads them with `dpSetPlayerData(..., 0xd, ..., 0x100, ...)`

Important details from the decompile:

- It expects a BMP whose `biBitCount` at offset `0x1c` is `1`
- It copies packed bitmap bits into the player's `flagBuf`
- This strongly suggests the net payload is a compact 1-bit monochrome mask rather than a full-color texture

### Legacy runtime retrieval and render

- `NetPlayer::GetFlag`
  - File: `legacy_bz1_exact_full/.../GetFlag-004e0ef8.c`
  - Fetches player flag data from player net data
- `FlagDisplay::GenerateFlags`
  - File: `legacy_bz1_exact_full/.../GenerateFlags-004ce8b8.c`
  - Converts packed flag bits into colored pixels inside `spriteTable`
- `FlagDisplay::Submit`
  - File: `legacy_bz1_exact_full/.../Submit-004cea9b.c`
  - Draws the generated sprites above nearby vehicles with `DrawScaledSprite`

This is important: the legacy in-game flag display is sprite-based, not mesh-based.

## Redux Findings

The Redux best-effort corpus and installed game data still contain significant flag remnants.

### Strong evidence the runtime feature family still exists

- Redux PDB reference still includes:
  - `FlagDisplay.obj`
  - `FlagDisplay::PreLoad`
  - `FlagDisplay::PostRun`
  - `FlagDisplay::GenerateFlags`
  - `FlagDisplay::Submit`
  - `SetMyFlag`
- Redux PDB/global data still includes:
  - `flagDisplay`
  - `Net::pcFlagName`
  - `Net::FlagLimit`
  - `_spriteTable`
  - `_spriteTableSize`
- Redux PDB/public functions still includes:
  - `_DrawScaledSprite`
  - `_ReadSpriteTableFile`

This strongly suggests the in-game flag display path still belongs to the surviving sprite compatibility layer, even though Redux uses Ogre at the top level.

### Strong evidence the old UI/file-picker path was trimmed or is no longer exposed

In the Redux best-effort corpus, I did not find legacy-style exports for:

- `FlagList`
- `PlayerNameList::ChangeFlag`
- `NetPlayer::GetFlag`
- `reload_flags`
- `flag????.bmp`

That points to "runtime remnants still present, old picker UI removed or no longer exported cleanly."

### Installed game data still carries flag artifacts

From the local GOG install:

- `localization_table.csv` still contains:
  - `multi_three:flag_limit`
  - `multi_error:team_1_flag_1`
  - `multi_error:team_1_flag_2`
  - `multi_error:team_2_flag_1`
  - `multi_error:team_2_flag_2`
- `packaged_mods/819834262/flags.bmp` still exists
- Core UI assets still include:
  - `rflagon.png`
  - `rflagclk.png`
  - `aflagon.png`
  - `aflagclk.png`

Those UI PNGs appear tied to mode/filter UI, not necessarily the in-world player flags, but they confirm flag-related assets were never fully stripped from the Redux content set.

## Practical Implication

The best restore path probably does **not** start with Ogre world meshes.

The legacy system drew flags from packed player data into `spriteTable`, then rendered those sprites in-world. Redux still appears to ship the same family of sprite/runtime support symbols.

So the likely first implementation path is:

1. restore a way to pick a flag in the lobby,
2. restore or replace the upload path for player flag data,
3. verify whether the surviving `FlagDisplay` render path still lights up automatically.

Only if step 3 fails do we need a deeper Ogre-specific world-render replacement.

## Recommended Implementation Path

### 1. Add a lobby selector in OpenShim

OpenShim already injects multiplayer UI controls:

- ban button host/client hooks
- map filter controls
- native button/label constructors
- child attachment into existing lobby parents

This makes the lobby shell the best place to restore flag selection.

Suggested first-pass UI:

- one compact `Flag` button or `F` button near the existing map/lobby control cluster
- two cycle buttons or a click-to-cycle button
- a text label showing the current selected flag name

A file browser is possible later, but not required for the first pass.

### 2. Use a shim-managed flag folder, not Ogre resource loading, for source art

Recommended folder:

- `<shim config dir>/flags/`

Scan for:

- `*.png`
- `*.bmp`
- optionally `*.tga`

Why this is better than relying on Ogre resource groups:

- the lobby selector needs filesystem discovery anyway
- the network payload is not an Ogre texture; it is a compact packed mask
- conversion and validation belong on the shim side
- arbitrary texture loading through Ogre does not solve the networking/data-format problem

Ogre resource groups may still be useful later for shell preview polish, but they are not the core requirement.

### 3. Convert arbitrary art into the legacy packed format

This is the most important missing piece.

Instead of requiring users to author exact legacy 1-bpp BMPs, the shim should:

- load the source image
- resize to the expected small flag size
- convert to grayscale
- threshold or dither to 1-bit
- pack bits row-by-row into the legacy blob
- zero-pad or fill the engine buffer size expected by the upload path

Benefits:

- modern user-friendly input files
- deterministic network-safe payload
- no dependence on the old `flag????.bmp` workflow

### 4. Upload the packed flag to player net data

There are two likely approaches:

#### Preferred

Call the surviving Redux `SetMyFlag` path after populating the expected path/global state.

#### Fallback

Reimplement the legacy upload behavior in Shim by locating and calling the equivalent Redux networking/player-data functions directly.

Even if the old picker UI is gone, the presence of `SetMyFlag` strings/symbols suggests the upload path may still exist.

### 5. Verify whether in-game render already works

If the packed flag data reaches the player's runtime state, the existing `FlagDisplay` path may already:

- fetch the data,
- generate colored sprite pixels,
- and draw flags above vehicles.

If that works, the feature restoration is mostly a lobby/UI/upload task.

If it does not work, the next RE target is:

- where `flagDisplay` is registered and submitted during multiplayer rendering,
- whether that callsite is gated off in Redux,
- whether a small shim hook can re-enable it.

## Likely First Deliverable

The most realistic first shippable version is:

- shim-managed `flags/` folder
- lobby cycle/select UI
- config-persisted selected flag
- upload packed flag on lobby enter / selection change / player readiness
- validate whether flags appear in live multiplayer matches

That avoids overcommitting to an Ogre mesh implementation before proving the legacy sprite path is truly dead.

## Current Working Conclusion

The feature looks recoverable.

The evidence currently favors:

- UI path removed
- runtime path partially preserved
- sprite-based in-world rendering likely still available through Redux's compatibility systems

That makes this a good OpenShim restoration target, and probably a significantly smaller project than inventing a completely new Ogre world-space flag renderer from scratch.

## Implementation Progress

### 2026-03-17 first pass in OpenShim

Groundwork has started in `src/bzr_hooks.cpp`:

- added shim-side flag catalog discovery under `.\\flags\\`
- added persisted selection file `.\\flags.cfg`
- added support for source file discovery for:
  - `.bmp`
  - `.png`
  - `.tga`
  - `.jpg`
  - `.jpeg`
- added a minimal multiplayer lobby `F` button beside the existing ban button injection
- clicking the button cycles the saved selection and updates a tooltip summary

Current status of that first pass:

- selection/catalog/config groundwork: implemented
- lobby selector button: implemented
- image conversion to legacy packed 1-bit net payload: not implemented yet
- upload to player net data: not implemented yet
- confirmation that surviving Redux `FlagDisplay` path still renders uploaded data: not implemented yet

This is intentionally a low-risk foothold so the next step can focus on the real technical question:

- can we feed a packed flag blob into the surviving Redux multiplayer player-data path and get in-world rendering "for free"?

## 2026-07-12 Redux renderer reconstruction

Deeper comparison with the exact legacy decompile showed that the earlier
"rendering for free" conclusion was too optimistic:

- Redux `FlagDisplay::PreLoad` sets its atlas index to zero and allocates no
  replacement texture atlas.
- Redux `FlagDisplay::GenerateFlags` no longer expands masks or assigns
  `NetPlayer::flagIndex` values.
- The surviving `Submit` routine is consequently gated off by zero display
  and player indices.
- Redux's `FlagDisplay` fields moved from legacy offsets `+0x10/+0x14` to
  `+0x28/+0x2C` behind the larger `GameFeature` base.

OpenShim now supplies the missing rendering stage directly through Ogre:

- hooks the surviving `FlagDisplay::Submit` vtable slot for correct render
  timing while preserving the original call;
- reads the replicated 256-byte mask from each team's player-data slot `0x0D`;
- generates a transparent 64x32 TGA and unlit alpha material per distinct
  payload hash;
- creates pooled, world-space Ogre billboard sets using those materials;
- mirrors the legacy eligible-class, object-state, 100-unit range, height,
  and terrain line-of-sight filters;
- forgets all scene-owned billboard pointers before Ogre scene teardown and
  recreates them lazily in the next match;
- overwrites slot `0x0D` directly on every lobby selection change because
  Redux's `SetMyFlag` returns early after the first payload already exists.

This implementation deliberately avoids inserting synthetic records into the
fixed Redux sprite table. The feature remains environment-gated for its first
live host/client validation pass.

### 2026-03-17 test path added in OpenShim

The next pass is now implemented for GOG as a real test path:

- selected source art is resized to the legacy flag dimensions:
  - `64 x 32`
  - `1-bpp`
  - `256-byte` payload
- OpenShim writes generated debug artifacts to:
  - `.\\flags\\_generated\\openshim_selected_flag.bmp`
  - `.\\flags\\_generated\\openshim_selected_flag.bin`
- the shim then pushes the generated payload into player data slot `0x0D`
- after upload, the shim best-effort marks `flagDisplay` dirty so the surviving runtime path can regenerate textures

The current GOG test implementation uses real runtime behavior observed in the EXE, not the earlier unreliable PDB function RVA for `SetMyFlag`.

Observed GOG helper call chain from the real wrapper around the flag path:

- `0x00572D90`
  - local player ID getter used immediately before player lookup
- `0x005771B0`
  - player lookup helper already reused by the ban work
- `0x00575570`
  - player-data setter used with slot `0x0D`

That means the first end-to-end test path no longer depends on recovering the exact exported `SetMyFlag` entrypoint. It uses the verified player-data write route directly.

Current limitations of the test path:

- GOG only for actual upload
- Steam currently only stages/generated the legacy artifacts and reports that apply still needs revalidation
- `flagDisplay` refresh is still best-effort until live runtime validation confirms the exact dirty/update trigger

## 2026-07-17 lobby crash + non-rendering fixes

Live-session logs (`logs/openshim_crash.log`, `logs/winmm_shim.log`) showed the
"click the flag button" lobby error and no in-world flags. Root causes found and
fixed in `src/patches/bzr_hooks.cpp`:

1. **Wild-pointer write (the lobby crash).** `kFlagDisplayAddr` was the stale
   advisory-PDB value `0x006DDD34`, which lands inside `.text` on the live GOG
   exe. `MarkFlagDisplayDirty()` wrote `1` to `+0x2C` of it → first-chance
   `0xC0000005` write faults at `0x006DDD60` (three in the crash log, plus 19x
   "Failed to mark flag display dirty" in winmm_shim.log). Re-derived the real
   live `flagDisplay` global by content:
   - dynamic initializer `0x00406B80`: `mov ecx, 0x9B60CC ; call 0x4D1C10`
     (the FlagDisplay ctor; stores vtable `0x00879984`, whose slot 8 is the
     already-verified `Submit` `0x004D1C80`).
   - net player-data dispatcher `0x00574EE5` and shell teardown `0x0056FC8F`
     both call a FlagDisplay method with the same `ecx = 0x9B60CC` when data
     slot `0x0D` (the flag payload) changes.
   - `FlagDisplay::PreLoad` `0x004D1C50` writes `+0x28 = 0` (flagIndex) and the
     `+0x2C` byte `= 0` (makeTexture), confirming the two field offsets.
   New constant: `kFlagDisplayAddr = 0x009B60CC` (in `.data`, writable). The
   AV is gone and the makeTexture dirty flag now lands on the real object.

2. **Overflowing lobby error text.** The status/summary strings were long
   sentences rendered into a fixed-width lobby tooltip label (why the user
   could not read the whole message). Shortened every `g_SelectedFlagStatus`
   and `GetSelectedFlagSummary()` to compact phrases.

3. **Lobby apply always "failed".** Pre-session there is no local `NetPlayer`
   yet, so both apply paths necessarily failed and surfaced scary status text.
   `PrimeSelectedFlagForTesting` / `UpdateFlagSelectionUiLabel` now skip the
   upload attempt when `TryGetLocalPlayerForFlags` returns none and simply show
   "Applies at match start."; the real upload runs from the in-game
   `ui_create`/`ui_update` pass once the player object exists.

4. **Renderer never observed drawing.** Added one-time diagnostics so a session
   log proves which stage the pipeline reaches: `Submit dispatch observed`,
   `renderer sees replicated flag payload(s) team(s)=…`, `payload(s) but no
   local user object/position yet`. Crucially, whether Redux's surviving
   GameFeature loop still dispatches `FlagDisplay::Submit` in live MP was never
   confirmed — so `MaybeDriveMultiplayerFlagRenderFallback()` now drives the
   same Ogre renderer from the per-sim-tick hook whenever Submit has not fired
   within 2 s, logging `Submit not dispatching; driving … from sim tick`.

Also fixed unrelated log spam that was drowning these lines: the HUD sprite
lookup now memoizes ids (was rescanning the 956-entry name table and logging
6x/sec), and "Sprite hidden" only logs on the hide transition, not every
1 s re-enforcement tick.

### In-world readback still under investigation (2026-07-17)

Live log after the address fix: no more faults, payload uploads
(`ui_create applied legacy fallback payload bytes=256 slot=0x0D`), Submit hook
installs and `FlagDisplay::Submit dispatch observed` — but the renderer's
`renderer sees replicated flag payload(s)` line never fires, so
`TryCopyMultiplayerFlagPayload` reads nothing from any team slot. Disassembly of
the engine flag path:

- `FlagDisplay::Submit` (0x004D1C80) early-outs on view mode 9/0xA and on
  `this+0x28 (flagIndex) == 0`, then reads each team's flag from
  `netPlayerByTeam[team] + 0x50` (a baked sprite index) — Redux's stubbed
  `GenerateFlags` never sets +0x50, which is why the native display is dead.
  Our Ogre renderer ignores +0x50 and reads the raw 256-byte mask instead.
- `SetMyFlag` (0x0056FA50) resolves the local player exactly like our upload:
  `GetLocalPlayerNetId` (0x00572D90) → `BanLookup` (0x005771B0, registry
  0x009C8FB8), then stores the mask via `SetFlagBuffer` (0x00575810) at
  `NetPlayer + 0x1C`. So our upload target is engine-correct.
- The renderer reads `netPlayerByTeam` (0x009180E8), an array of `NetPlayer*`
  populated by 0x00577900 from a **different** registry (0x009C8FA0), keyed by
  each player's team byte at `+0x68`.

Open question: are the 0x9C8FB8 (BanLookup) and 0x9C8FA0 (by-team) objects the
same `NetPlayer` instances? If not, the mask lands where the renderer never
reads. Added a one-shot `[FLAGDIAG]` dump in `RenderMultiplayerFlags` that logs,
per team slot, ptr / id(+0x28) / teamByte(+0x68) / sprite(+0x50) / flagBuf(+0x1C)
/ slot-0x0D size, plus the local player and a direct `same=YES/NO` check.

**RESOLVED 2026-07-18.** The `[FLAGDIAG]` dump from a live load returned
`same=YES` (`byteam[1]=0x39E58868 == localPlayer=0x39E58868`), and
`[FLAG] renderer sees replicated flag payload(s) team(s)=1` fired. So the object
identity was never the problem — the two registries return the same NetPlayer
pool, the upload lands on the right object, and the renderer reads the mask back
correctly. The data path works end-to-end once the stale-address write fault was
fixed. (The `flagBuf=0 / slot0x0D=-1` in the diag line is timing: the one-shot
dump fires a couple frames before the ui_create/ui_update upload completes; the
one-shot "renderer sees" line fires once the payload arrives.)

**Why no flags were visible: the test was solo.** The renderer (like 1.5
`Submit`) skips the local craft, and AI/enemy units are not NetPlayers with flag
payloads, so a solo host has nothing on screen to attach a flag to. In-world
flags require a second human player. Not a bug — matches legacy design. A future
opt-in (`openshim.ini`) could also draw the local player's own flag for solo
self-verification.

## 2026-07-17 lobby flag preview (1.5 FlagList parity)

Decomp confirms two distinct legacy render paths, settling the "flags over your
own vehicle" question:

- `FlagDisplay::Submit` (1.5 0x004cea9b) skips the local craft:
  `(local_1c != local_30)` where `local_30 = GameObject::userObject`. So
  over-vehicle flags never draw over your own craft, 1.5 or Redux.
- `FlagList` (1.5 0x00550d25) — the multi-menu picker — scans `flag????.bmp`,
  writes the selection to `Net::pcFlagName`, and builds a `ShellBitmap` at a
  64x32 rect that `FlagList::BltBitmap` (0x00550e4d) blits into the menu. That
  is the menu preview users remember; OpenShim never reimplemented it.

Reimplemented that preview in `bzr_hooks.cpp`: `CreateFlagButtonCommon` now also
creates a non-interactive 64x32 tile above the "F" button. `WriteFlagPreviewPng`
renders the packed mask (white where set, over a translucent dark tile, row
order flipped to upright) to the **mod-adjacent generated flags dir**
`flags/_generated/openshim_flagprev_<flag>.png` — NOT the core BZ_ASSETS_CORE
tree, since the feature ships via the flags mod and generated art must stay out
of core game folders the mod does not own. That directory is registered as an
Ogre FileSystem resource location (`EnsureFlagPreviewResourceLocationRegistered`,
group "General") so the UI texture loader can still resolve the bare name. The
tile's texture is set via the same `SetTextureOff/Over/On` path; the name is
unique per flag so the engine's by-name texture cache maps each flag to its own
image. The preview reuses the F button's click/hover callbacks so both
+0x150/+0x154 slots stay non-null (the AutoSave null-slot crash class) and
clicking the tile also cycles. Refreshed on every cycle via
`UpdateFlagPreviewWidget`. Log lines: `[FLAG] registered lobby preview resource
location` and `[FLAG] wrote lobby preview`.

Caveat to confirm from the next log: the UI texture loader's resource group is a
function-pointer-table indirection (`[0x869ec0]` manager getter, name setter
`0x007D3FF0`) that resolved statically to code pointers, not a group string, so
whether "General" is the group it searches is unverified. If the tile stays
blank, the `[FLAG] wrote lobby preview` line will still be present (PNG created)
and the fix is to register the generated dir into the correct group (candidates:
the group holding `BZ_ASSETS_CORE/common/ui`, or the "Modable" mod group seen in
BZOgreLogfile) rather than "General".
