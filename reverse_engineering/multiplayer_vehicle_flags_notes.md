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
