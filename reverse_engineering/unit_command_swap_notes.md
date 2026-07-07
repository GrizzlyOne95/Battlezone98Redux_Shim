## Unit Command Swap RE Notes

Date: 2026-03-16

Goal: determine how stock unit command menu entries are selected, why
`cvfigh.odf` swaps `Hunt` to `Cloak`, and whether the game already supports
arbitrary per-unit command injection with custom text and Lua dispatch.

### Scope

Compared and inspected:

- `<USER_HOME>\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\ODF\svfigh.odf`
- `<USER_HOME>\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\ODF\cvfigh.odf`
- `<GAME_ROOT>\battlezone98redux.exe`
- `<GAME_ROOT>\battlezone98redux.pdb`
- `<USER_HOME>\Downloads\Battlezone 98 Redux\battlezone98redux.exe`
- `<USER_HOME>\Documents\GIT\ExtraUtilities-G1`
- `<USER_HOME>\Documents\GIT\Battlezone98Redux_Shim\reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full`

### ODF Findings

Relevant command-side delta between `svfigh.odf` and `cvfigh.odf`:

- `cvfigh.odf` has `CraftClass.cloakAllowed = "True"`
- `svfigh.odf` does not

There is no generic command list field in these ODFs. Neither file contains
anything resembling:

- command slot definitions
- custom command labels
- command callbacks
- script function names

`user1Msg` exists on both units, but that is only a voice-message slot. It is
not evidence of a user-definable command button.

### EXE String Findings

Both the GOG and Steam executables contain the same stock command label block in
`.rdata`, including:

- `No Action`
- `Go To Geyser`
- `Go To Nav`
- `Hunt`
- `Scavenge`
- `Build`
- `Recycle`
- `Attack`
- `Defend`
- `Follow Close`
- `Follow`
- `Select`
- `Cancel`
- `Back`
- `Decloak`
- `Cloak`

They also contain the cloaking-related runtime strings:

- `cloakAllowed`
- `cloakState`
- `cloakTime`
- `forceCloak`
- `SetCloaked`
- `SetDecloaked`
- `EnableCloaking`

This is consistent with native cloaking support and a fixed stock command text
table.

### PDB Findings

Useful global symbols:

- `COMMAND_TEXT`
- `MODE_TEXT`
- `TITLE_TEXT`
- `buildMenu`

Useful command/menu-related functions:

- `PathDisplay::DrawCommandMenu`
- `ControlPanel::SetModeMenu`
- `ControlPanel::SetCommand`
- `ControlPanel::BroadcastCommand`
- `ActionMode::GetCommand`
- `GameObject::UpdateModeList`
- `GameObject::SetActiveMode`
- `Craft::GetCommand`
- `Craft::SetActiveMode`
- `Wingman::UpdateModeList`
- `Wingman::SetActiveMode`
- `HoverCraft::UpdateModeList`
- `Howitzer::UpdateModeList`
- `Scavenger::UpdateModeList`
- `Producer::UpdateModeList`
- `ModeList::RemoveAllModes`

Useful command and mode constants:

- `MODE_HUNT = 13`
- `CMD_HUNT = 20`
- `MODE_LIST_SPECIALS = 21`
- `MENU_SPECIALS = 4`

Important negative finding:

- no `MODE_CLOAK`
- no `CMD_CLOAK`
- no `MODE_DECLOAK`
- no `CMD_DECLOAK`

Important message-only finding:

- `USER1_MSG` exists, but as `UnitMsg`
- `SELECT_USER1_MSG` exists, but as `UnitMsg`
- there is no corresponding `MODE_USER1` or `CMD_USER1`

That means `Cloak`/`Decloak` are not exposed as their own stock mode or AI
command enum values. The likely implementation is a class-specific substitution
of an existing mode slot, not a generic new command definition.

### Legacy BZ1 Decompile Cross-Check

The exact-match legacy BZ1 decompile is not the same executable as Redux, so
this is supporting evidence rather than a direct BZR proof. It does, however,
show the same named control flow very clearly:

- `Wingman::UpdateModeList` calls `ModeList::SetMode(..., 7, 0x0D, true)`,
  `ModeList::SetMode(..., 8, 0x10, true)`, and
  `ModeList::SetMode(..., 9, 0x11, true)`
- `Wingman::SetActiveMode` does:
  - `mode 0x0D -> GameObject::SetCommand(CMD_HUNT)`
  - `mode 0x10 -> GameObject::SetCommand(CMD_FORMATION, userObject)`
  - everything else falls through to `Craft::SetActiveMode`
- `Craft::SetActiveMode` handles stock craft modes like follow, repair,
  reload, rescue, and recycle, but not `Hunt`
- `ActionMode::GetCommand` defers to the currently selected object's virtual
  command resolver when something is selected

That legacy control flow strongly reinforces the Redux/PDB interpretation:
`Hunt` is a stock wingman mode slot, and swapping it is fundamentally a native
mode-slot substitution problem, not a data-driven custom-command system.

### Interpretation

The stock command menu appears to be built from a fixed native mode system:

1. a class-specific `UpdateModeList` decides which stock modes are available
2. `PathDisplay::DrawCommandMenu` renders labels from static native text tables
3. `SetActiveMode` and `ActionMode::GetCommand` translate the selected mode into
   stock game behavior

The `cvfigh` `Hunt -> Cloak` behavior is therefore most likely:

- not a generic ODF-defined command
- not a Lua callback hook
- not a new enum entry
- a hardcoded native substitution in `Wingman` / `Craft` menu logic that checks
  cloaking capability and current cloak state

Given the absence of `MODE_CLOAK` and `CMD_CLOAK`, the game is probably
re-using the `Hunt` slot and changing its display/action conditionally for
cloak-capable craft.

### Extra Utilities Findings

Current Extra Utilities exposure does not include command-menu mutation.

The native headers and Lua exports currently expose control-panel selection
helpers only:

- `SelectAdd`
- `SelectOne`
- `SelectNone`

I did not find an existing EXU Lua callback for:

- command menu opened
- command button selected
- custom command registration
- dynamic command text injection

### Practical Implications

#### What already exists natively

- fixed stock mode list
- fixed stock command text tables
- per-class menu construction via `UpdateModeList`
- per-class activation via `SetActiveMode`
- hardcoded cloaking support

#### What does not appear to exist

- arbitrary ODF-defined command buttons
- custom command labels per unit
- generic Lua-backed command callbacks
- a stock `MODE_USER1` / `CMD_USER1` feature for the menu

### Most Realistic Patch Paths

#### Limited slot-swap feature

Feasible with native hooks.

Approach:

1. hook `UpdateModeList` for the relevant class
2. reuse one of the stock mode slots already understood by the menu
3. hook `SetActiveMode` or `ActionMode::GetCommand`
4. dispatch to Lua when that mode is chosen
5. override displayed text by patching the command text lookup or table entry

This would support something like:

- replace `Hunt` with a custom label and behavior
- replace `Back` or another situational slot for special units

#### Fully generic "add arbitrary extra buttons"

Possible, but significantly larger.

You would likely need to patch:

- mode-list construction
- button layout / count assumptions
- command-text lookup
- input dispatch
- mode-to-command translation

That is a deeper UI and control-panel patch, not a small ODF or Lua extension.

### Best Native Hook Targets

Most promising targets for a first custom-command prototype:

- `Wingman::UpdateModeList`
- `Wingman::SetActiveMode`
- `Craft::SetActiveMode`
- `ActionMode::GetCommand`
- `ControlPanel::SetModeMenu`
- `PathDisplay::DrawCommandMenu`

### Current Best Answer

The stock `cvfigh` command swap is not evidence of a generic command-definition
system. It is evidence of a hardcoded native command substitution path tied to
cloaking capability.

So if the goal is:

- "put arbitrary text in the menu"
- "show it only for specific units"
- "run Lua when pressed"

then the realistic path is a native shim / EXU patch that intercepts stock mode
selection and dispatch, not an ODF-only solution.

### 2026-07-07 Validation Against Full Decompiles

Validation inputs:

- fully decompiled 1.5 reference:
  `reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full`
- fully decompiled Redux reference:
  `<USER_HOME>\Documents\GIT\HoverZone\decompiled_bz_reference\_unzipped\Redux`
- repo Redux best-effort corpus:
  `reverse_engineering\workshop\global_decompile\bzr_gog_best_effort`

The 1.5 decompile directly confirms the original model:

- `Wingman::UpdateModeList` installs fixed modes `0x0D`, `0x10`, and `0x11`
  into fixed slots 7, 8, and 9.
- `Wingman::SetActiveMode` maps mode `0x0D` directly to
  `GameObject::SetCommand(CMD_HUNT)`.
- `Craft::SetActiveMode` still does not own `Hunt`; it handles follow, repair,
  reload, rescue, and recycle style craft commands.

The Redux full decompile is less symbol-rich, but it validates the same broad
architecture:

- `ActionMode::GetCommand` in the Redux best-effort corpus still resolves
  behavior through selected objects, current control-panel mode, and stock
  `CMD_*` values rather than a data-driven command registry.
- `PathDisplay` / `ControlPanel` paths still operate on fixed native menu and
  mode structures.
- The HoverZone Redux raw decompile contains fixed numeric mode-to-command
  dispatch examples, such as `FUN_00474b80`, where a switch case dispatches to
  command value `0x14` (`CMD_HUNT`). That function is an Armory-process path,
  not the Wingman menu hook target, so it is supporting evidence for the fixed
  dispatch model rather than proof of the Wingman slot itself.

Important caveat from this validation pass:

- The Redux Ghidra/PDB labels `Wingman_UpdateModeList = 0x0054CEE0` and
  `Wingman_SetActiveMode = 0x0054CF80` exist in the local project, but they are
  labels rather than usable function entries for the current analyzed Steam
  image. Static and runtime probes at those exact VAs did not decode as code.
  Treat those addresses as stale or mismatched labels, not patch targets.
- This strengthens the existing EXU design choice to signature-scan the live
  executable for the actual Hunt activation block instead of hardcoding a PDB
  address.

Net result: the prior conclusion holds. The evidence still points to fixed
native command/mode tables plus class-specific activation logic. Replacing an
existing stock slot, especially `Hunt`, is the practical patch path. Arbitrary
new button insertion still requires a deeper control-panel/path-display UI
patch.

### Implementation Status

As of 2026-03-16, the first EXU native pass now exists:

- `exu.ReplaceStockCmd(...)` registers a per-handle stock-slot replacement with
  a custom label and Lua callback
- EXU scans the live Redux executable for the `Wingman::SetActiveMode`
  `mode 0x0D -> CMD_HUNT` block and hooks the Hunt activation path directly
- if the selected unit has a registered `Hunt` replacement and the callback
  handles it, stock `CMD_HUNT` is suppressed before it is issued
- `exu.UpdateCommandReplacements()` remains in the mission update loop mainly
  to maintain the current contextual Hunt-label override and provide a fallback
  if the native signature ever fails to resolve

Current implementation limits remain:

- only the stock `Hunt` slot is auto-hooked
- the label override still works by retargeting the stock Hunt text pointer
  rather than patching `PathDisplay::DrawCommandMenu`
- there is still no generic arbitrary-button insertion

### Confidence / Caveat

The GOG PDB is coherent enough for names and structure, but it is not a
byte-perfect match for every executable address. Treat the symbol names as
semantic guidance. Any actual patch point should be revalidated directly
against the target binary before code is shipped.
