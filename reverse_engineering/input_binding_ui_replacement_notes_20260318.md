# Native Input Binding UI Replacement

Date: 2026-03-18

Goal: replace the stock Redux input-keybinding screen with a simple full-list UI
that keeps the stock background and shell flow, but exposes all practical
bindings through the game's existing native key capture and save paths.

## Summary

Current conclusion:

- the stock Redux input system is broader than the visible options screen
- the current options screen is the main limitation
- OpenShim is the correct home for a full replacement UI

The cleanest implementation path is:

1. keep the stock options-screen entry/background/screen singleton
2. suppress or bypass the stock fixed child-widget layout for the input page
3. inject a simple generated list of label/value boxes using native UI helpers
4. route assignment through the stock key-capture logic
5. persist through the stock `input.map` and `gamekey.map` writers

This avoids inventing a new config format and keeps compatibility with the
existing native input pipeline.

## Key Findings

### 1. The visible UI is hardcoded, not data-driven

The old input options screen is a fixed native dialog with hand-built controls.
The decompile at:

- [InputConfigDlgProc-00577848.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/InputConfigDlgProc-00577848.c)

shows explicit creation of stock widgets like:

- `Strafe Left`
- `Strafe Right`
- `Jump`
- `Forward`
- `Backward`
- `Pitch Up`
- `Pitch Down`
- `Turn Left`
- `Turn Right`
- `Fire`
- `Weapon`

and explicit `read_text_label("input_config", ...)` label loads for those exact
entries.

This matches the current Redux behavior: only a small curated set of bindings
is editable through the UI even though the live input tables are larger.

### 2. The engine already has native reassignment plumbing

The stock native flow already includes:

- one-key capture via
  [GetOneKey-004bd7dc.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/GetOneKey-004bd7dc.c)
- modifier collection via
  [StoreGameKey-004bd422.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/StoreGameKey-004bd422.c)
- stock `KeyConfig` validation via
  [set_key-0056fc32.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/set_key-0056fc32.c)
- live UI label update plus file write via
  [SetKeyInput-00573e4b.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/SetKeyInput-00573e4b.c)

The stock input page is therefore mostly a thin GUI wrapper over reusable
native key-config helpers.

### 3. `input.map` and `gamekey.map` are separate systems

The live install under:

- [input.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map)
- [gamekey.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/gamekey.map)

confirms two distinct mapping layers:

- `input.map` for live control-channel bindings such as movement, weapons,
  jump, editor controls, and menu-control channels
- `gamekey.map` for higher-level chorded game actions like pause, chat,
  save/load, overview, and edit-mode toggles

Examples from the live files:

- [input.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L204)
  `throttle_up`
- [input.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L262)
  `strafe_left`
- [input.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L268)
  `jump`
- [input.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L288)
  `weapon_cycle`
- [gamekey.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/gamekey.map#L24)
  `PAUSE_GAME`
- [gamekey.map](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/gamekey.map#L31)
  `CHAT_SENDTOALL`

Practical implication:

- a full replacement UI should probably expose two sections or tabs
- replacing only the stock `input.map` page would still leave many reserved or
  hardcoded user-visible actions outside the UI

### 4. `KeyConfig` is broader than the stock screen

The old decompile shows:

- [set_defaults-0056facc.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/set_defaults-0056facc.c#L14)

with `this->nKeyCount = 0x3e`, meaning the stock key-config table already
tracks many more entries than the tiny fixed input page displays.

The GOG PDB also exposes native names for this area:

- `cUI_OptionsInput::PopulateUI`
- `cUI_OptionsInput::KeyReleased`
- `cUI_OptionsInput::Click_ResetDefaults`
- `KeyConfig::set_defaults`
- `KeyConfig::set_key`
- `KeyConfig::write_key`
- `_read_input_map_key`
- `_write_input_map_key`
- `_StoreGameKey`

Relevant `llvm-pdbutil` excerpts:

```text
?PopulateUI@cUI_OptionsInput@@QAEXXZ
  flags = function, addr = 0001:1995440

?KeyReleased@cUI_OptionsInput@@UAE_NAAUtagMSG@@@Z
  flags = function, addr = 0001:1994000

?Click_ResetDefaults@cUI_OptionsInput@@QAEXXZ
  flags = function, addr = 0001:1986128

?set_key@KeyConfig@@QAEHPAD0@Z
  flags = function, addr = 0001:1175120

?write_key@KeyConfig@@QAEHPAD@Z
  flags = function, addr = 0001:1174544

_read_input_map_key
  flags = function, addr = 0001:1403520

_write_input_map_key
  flags = function, addr = 0001:1402832

_StoreGameKey
  flags = function, addr = 0001:1414608
```

Command used:

```powershell
& 'C:\Program Files\LLVM\bin\llvm-pdbutil.exe' dump --publics `
  'C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb' |
  Select-String -Pattern 'OptionsInput|KeyConfig|read_input_map_key|write_input_map_key|StoreGameKey'
```

That is strong evidence that the correct high-level patch target is the native
`cUI_OptionsInput` screen rather than a lower-level blind UI hack.

### 5. The stock options singletons are still named in the PDB

The GOG PDB confirms these globals:

- `sOptionsInput`
- `sOptionsParent`
- `sOptionsPlay`

Commands used:

```powershell
& 'C:\Program Files\LLVM\bin\llvm-pdbutil.exe' dump --globals --global-name=sOptionsInput `
  'C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb'

& 'C:\Program Files\LLVM\bin\llvm-pdbutil.exe' dump --globals --global-name=sOptionsParent `
  'C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb'

& 'C:\Program Files\LLVM\bin\llvm-pdbutil.exe' dump --globals --global-name=sOptionsPlay `
  'C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb'
```

The shared options/pause singleton cluster was already corroborated in:

- [pause_menu_notes.md](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/pause_menu_notes.md)

This is useful because it suggests the replacement should attach to the stock
options-input screen lifecycle rather than trying to fake a completely separate
shell page.

### 6. The current Redux binary still carries the same stock input-screen strings

String scanning against the live Steam executable at:

- [battlezone98redux.exe](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/battlezone98redux.exe)

shows the current build still includes:

- `input_config`
- `keyBindForward`
- `keyBindJump`
- `keyBindWeapon`
- `alreadyBound`
- `reserved_key`
- `message_one`
- `message_two`

That strongly suggests Redux still uses the old fixed input screen design,
even if class layouts or surrounding codegen changed somewhat from the legacy
corpus.

### 7. OpenShim already has the right native UI helper layer

OpenShim already resolves and uses stock UI constructors and child insertion in:

- [bzr_hooks.cpp](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/src/bzr_hooks.cpp#L4669)

Relevant helpers already in the shim:

- button ctor
- label ctor
- texture setters
- button label setter
- hover/click callback setters
- add-child helper
- dialog enable/advance helpers

OpenShim also already injects stock-style UI into live screens for:

- ban buttons
- flag selection UI
- autosave load button

Example implementation:

- [AutoSaveLoadButtonCreate](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/src/bzr_hooks.cpp#L6688)

This matters because the replacement input screen can follow an established
repo pattern:

- hook stock screen lifecycle
- create native button/label children
- wire native click callbacks
- reuse existing game assets and localization

### 8. 2026-03-23 recovery update: the PDB public method addresses were misleading

The shipped GOG PDB still helps with class names and singleton discovery, but
its public `cUI_OptionsInput` method addresses did not correspond to reliable
hook entries for the live Redux binary.

String-xref recovery against the GOG executable showed that the real stock input
screen construction path is:

- `FUN_007b25b0`

That function:

- sets `cUI_OptionsInput::vftable`
- stores the singleton at `DAT_009455b8`
- creates the `ioptions_center.png` overlay
- creates the fixed `Back`, `Joystick`, `Defaults`, and stock key-bind buttons
- resolves the expected localization keys:
  - `input_config`
  - `alreadyBound`
  - `reserved_key`
  - `message_one`
  - `message_two`
  - `keyBindForward`
  - `keyBindJump`
  - `keyBindWeapon`

Immediate practical implication:

- the first live replacement hook should target the recovered constructor path
  at `0x007B25B0`, not the earlier PDB-derived `0x005E82B0` placeholder

## Current Constraints

### Reserved entries

`KeyConfig::set_key` rejects assignment when `nReserved != 0`:

- [set_key-0056fc32.c](/C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/set_key-0056fc32.c#L74)

This should be treated as a product decision:

- either preserve stock reserved entries
- or deliberately unlock some/all of them in the replacement UI

### Duplicate-key rejection

`KeyConfig::set_key` also rejects duplicate key-name reuse before rewriting an
entry. The stock UI string `alreadyBound` matches that behavior.

If the replacement UI wants to preserve stock semantics, it should keep the
same duplicate-check behavior instead of silently allowing conflicts.

### `input.map` has nontrivial shapes

Some live commands have:

- multiple lines
- mouse and keyboard variants
- modifier requirements
- more than one positive binding

Examples:

- [weapon_fire](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L276)
- [weapon_cycle](/C:/Users/istuart/Documents/Battlezone%2098%20Redux/input.map#L288)

This means the first replacement UI should probably define a limited policy for
each row, for example:

- show the primary positive keyboard binding only
- preserve any existing mouse or negative-modifier lines
- rewrite only the chosen positive keyboard token

That matches the stock helper behavior more closely than trying to normalize
the whole file immediately.

### EXU does not currently follow remapped actions

Extra Utilities `GetGameKey()` is raw `GetAsyncKeyState` against VK names:

- [IO.cpp](/C:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/IO.cpp#L24)
- [IO.h](/C:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/IO.h#L37)

So a native full-rebind UI will not automatically update addon scripts that ask
for keys like `"J"` or `"CTRL"`.

That is not a blocker for the UI replacement itself, but it does mean a later
mapped-action API may be desirable if addon-side features should honor remaps.

## Likely Patch Home

Best current patch home:

- OpenShim native hook on the stock `cUI_OptionsInput` screen

Best first native targets:

1. `cUI_OptionsInput::PopulateUI`
2. `cUI_OptionsInput::KeyReleased`
3. stock key read/write helpers already validated in the legacy corpus

Current best replacement seam:

- `cUI_OptionsInput::PopulateUI` looks like the best first hook site for
  replacing stock child construction while preserving the stock screen object,
  background, and shell navigation.
- `cUI_OptionsInput::KeyReleased` is the best companion site if the replacement
  list reuses the screen's own "waiting for key" state and wants to stay inside
  stock input-page message flow.
- `cUI_OptionsInput::Click_ResetDefaults` should be reused or mirrored so the
  replacement screen still honors the stock reset path.

High-level replacement strategy:

1. let the stock options shell reach the input page normally
2. intercept the input page population path
3. either:
   - block stock child creation and build our own rows
   - or immediately hide/disable stock child controls and add our own
4. keep the stock background and parent screen
5. wire clicks into the stock key-capture/save logic

## First Implementation Shape

The first practical version should stay intentionally simple:

- keep the existing background art
- keep a `Back` button
- keep a `Defaults` button
- create a scrollable flat list of:
  - label text
  - current binding value
  - optional reserved marker
- start with `input.map` keyboard-oriented bindings only
- defer `gamekey.map` to a second page if needed

Suggested first row set:

- movement and combat rows that already work in the stock screen
- then add the missing practical `input.map` keyboard rows:
  - group selection
  - center player/recycler
  - menu navigation
  - jump
  - eject
  - abandon
  - deploy
  - cloak
  - drop/cycle beacon
  - weapon-link/select slots
  - overview camera keys

After that, add a second list/page for `gamekey.map` actions like:

- pause
- chat
- save/load
- overview
- info/objectives display
- edit-mode toggle

## Live Row Inventory

A quick parse of the current live install shows:

- `input.map`: 93 unique command blocks
- `gamekey.map`: 36 unique action names

This matters because the first replacement UI does not need to guess whether
there are "a few more" hidden rows. There are enough rows that a generated list
or paged list is clearly the right shape.

### `input.map` practical categories

The live `input.map` rows fall into three useful groups for the first UI pass.

Group 1: simple keyboard-first rows

- one positive keyboard token
- zero or more negative program/modifier guards
- good first candidates for direct editing

Examples:

- `throttle_up`
- `throttle_down`
- `strafe_left`
- `strafe_right`
- `jump`
- `weapon_link`
- `abandon`
- `cloak`
- `deploy`
- `drop_beacon`
- `cycle_beacon`

Group 2: keyboard rows with multiple positive keyboard tokens

- these need policy, because the file currently encodes more than one positive
  keyboard line for the same logical row

Examples:

- `menu_up`
- `menu_down`
- `eject`
- `zoom_factor_plus`
- `zoom_factor_minus`
- `edit_copy`
- `edit_paste`
- `edit_undo`
- `edit_maptype`

Group 3: mixed mouse/keyboard or analog-heavy rows

- these need special handling or should be deferred in the first pass

Examples:

- `cmd_x`
- `cmd_y`
- `cmd_lclick`
- `cmd_rclick`
- `menu_pos`
- `menu_next`
- `menu_back`
- `steer`
- `pitch`
- `weapon_fire`
- `weapon_cycle`
- `weapon_special`
- `edit_lmouse`
- `edit_rmouse`

Recommended first-pass UI rule:

- expose Group 1 broadly
- expose selected Group 2 rows only when a clear "primary key" policy is
  defined
- defer Group 3 until the replacement keyboard list is stable

### `gamekey.map` practical categories

The live `gamekey.map` action list is smaller and more uniform than `input.map`.
Most entries are simple chord bindings and are good candidates for a second
replacement page after the keyboard-first `input.map` page works.

Special cases with more than one chord currently defined:

- `PAUSE_GAME`
- `CHAT_SENDTOALL`
- `ALLIE_TOGGLE`
- `UNALLIE_TOGGLE`

Recommended first-pass `gamekey.map` rule:

- render one row per action
- show all currently defined chords in the value column
- either:
  - edit only the first chord in the first pass
  - or open a secondary "manage chords" popup later

## Open Questions

1. Whether the current Steam 2.2.301 `cUI_OptionsInput` method bodies still
   match the legacy GOG semantics closely enough for direct inline detours.
2. Whether the replacement should call the stock reset-default handler directly
   or reproduce defaults from `KeyboardDefaultList`.
3. Whether the first UI should be:
   - one long list
   - or two tabs/pages for `input.map` vs `gamekey.map`
4. Whether any stock rows intentionally remain reserved.

## Immediate Next Steps

1. Recover the current Steam/GOG patch-safe entry site for
   `cUI_OptionsInput::PopulateUI`.
2. Identify the safest place to suppress stock input-page widget construction
   while leaving the parent options screen intact.
3. Build a small shim-owned row model:
   - command name
   - display label key
   - current binding text
   - reserved flag
   - map family (`input` or `gamekey`)
4. Reuse the existing shim UI constructors to render a minimal scrolling list.
5. Route reassignment into the stock key-capture helpers.

## Repo Status

As of this note, no replacement input-screen hook has been implemented yet.

This file is the first running design log for that work and should be extended
as hook sites, screen ownership, and row-model decisions are validated.
