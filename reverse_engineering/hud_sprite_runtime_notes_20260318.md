# HUD Sprite Runtime Notes

Date: 2026-03-18

## Scope

Goal: confirm whether Battlezone 98 Redux still keeps the old `spritea.st`
HUD sprite table live at runtime, and identify a safe OpenShim bridge for
runtime HUD sprite rect mutation instead of texture swapping.

Primary use case:

- hide the stock `scrap_panel` and `pilot_panel` backplates without forcing a
  HUD texture swap, so player HUD mods stay intact

Secondary use case:

- future runtime swapping of other HUD sprite rects for legacy/modern UI
  layouts

## Confirmed Runtime Findings

### Static executable strings

In the Steam executable:

- `scrap_panel` at `0x00485D20`
- `sscrap_panel` at `0x00485D2C`
- `spritea.st` at `0x004917D4`
- `"Main sprite table \"spritea\" not found. Most sprites will be missing.\n"`
  at `0x004917F0`

That lines up with the earlier repo-side note in
[`multiplayer_vehicle_flags_notes.md`](C:/Users/iestu/Documents/GIT/BZR-OpenShim/reverse_engineering/multiplayer_vehicle_flags_notes.md)
that referenced `_spriteTable`, `_spriteTableSize`, and
`_ReadSpriteTableFile`.

### Name lookup helper

Live disassembly in a mission confirmed:

- `0x0068BED0` is a sprite-name lookup helper
- it reads sprite count from `0x00920F00`
- it walks a `0x20`-byte fixed-string table at `0x00920F08`
- it returns a sprite ID/index for a supplied name

Relevant live IDs in the mission sample:

- `0x109` = `scrap_panel`
- `0x10A` = `pilot_panel`
- `0x10B` = `sscrap_panel`
- `0x10C` = `spilot_panel`
- `0x10D` = `fscrap_panel`
- `0x10E` = `fpilot_panel`

The mission HUD init path around `0x005C6C60` also pushes those names
directly, which confirms these are the stock runtime HUD sprite entries rather
than dead strings.

### Live rect table

In the mission process, the matching rect records were found at:

- `0x025FB480` = ID `0x109` = `scrap_panel`
- `0x025FB4A0` = ID `0x10A` = `pilot_panel`
- `0x025FB4C0` = ID `0x10B` = `sscrap_panel`
- `0x025FB4E0` = ID `0x10C` = `spilot_panel`
- `0x025FB500` = ID `0x10D` = `fscrap_panel`
- `0x025FB520` = ID `0x10E` = `fpilot_panel`

Record stride is `0x20` bytes.

Observed layout:

- `+0x00` unknown pointer/reference
- `+0x04` unknown pointer/reference
- `+0x08` `x` as `int16`
- `+0x0A` `y` as `int16`
- `+0x0C` `w` as `int16`
- `+0x0E` `h` as `int16`
- `+0x10` `u0` float
- `+0x14` `v0` float
- `+0x18` `u1` float
- `+0x1C` `v1` float

The stock pilot/scrap panel rects were live exactly as:

- `scrap_panel`: `660, 960, 180, 64`
- `pilot_panel`: `844, 960, 180, 64`
- `sscrap_panel`: `660, 960, 180, 64`
- `spilot_panel`: `844, 960, 180, 64`
- `fscrap_panel`: `660, 960, 180, 64`
- `fpilot_panel`: `844, 960, 180, 64`

For that run, the rect table base derived cleanly as:

- `0x025F9360`

via:

- `0x025FB480 - (0x109 * 0x20) = 0x025F9360`

No stable global owner pointer for that dynamic rect table was pinned yet, so
the initial bridge discovers it by scanning committed readable memory for the
known pilot/scrap pattern and validating the full six-entry cluster.

## OpenShim Implementation

Bridge surface added in `src\winmm_proxy.cpp` and `src\winmm.def`:

- `OpenShimSetHudSpriteRect(name, x, y, w, h)`
- `OpenShimSetHudSpriteVisible(name, visible)`
- `OpenShimRestoreHudSprite(name)`
- `OpenShimRestoreAllHudSprites()`

Native implementation lives in `src\bzr_hooks.cpp`.

Behavior:

- sprite IDs are resolved from the live name table
- rect-table base is discovered once per runtime and cached
- original rects are cached on first mutation for each sprite
- `visible=false` currently hides by zeroing width and height
- `visible=true` restores the last non-hidden rect snapshot
- restore APIs write the cached original stock rect back

This is enough for the intended pilot/scrap backplate suppression path without
swapping HUD textures.

## Notes

- `0x0068BED0` had already been used in OpenShim for the engine-flame texture
  lookup path. The HUD work confirms that helper is really a generic
  fixed-string name lookup over a runtime table, not something flame-specific.
- The current hide/show path does not use a dedicated hidden flag because that
  flag has not been identified yet.
- If a future pass finds the rect-table owner/global directly, the current
  scanner can be replaced with a direct pointer fetch.
