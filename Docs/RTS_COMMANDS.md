# RTS command extras

`src/patches/rts_commands.cpp`, rules in `include/rts_commands_policy.h`
(host tests: `tests/rts_commands_policy_tests.cpp`). Options: Controls >
RTS Commands. Keys: Options > Input > RTS Actions (written to
`[Gameplay] Rts*Key`, like `RallyKey`).

| Feature | `[Gameplay]` row | Key (default) | Multiplayer |
| --- | --- | --- | --- |
| Target a selected unit | `RtsRemoteTarget` (on) | Shift+`RtsRemoteTargetKey` (Shift+T) | Runs (UNVERIFIED live) |
| Target the next own building | `RtsRemoteTarget` (on) | `RtsBuildingCycleKey` (B) | Runs (UNVERIFIED live) |
| Mixed-selection menu | `RtsSmartCommandMenu` (on) | stock menu keys | Runs (UNVERIFIED live) |
| Repair/Reload for the units that need it | `RtsSmartRepairReload` (on) | stock menu keys | Runs (UNVERIFIED live) |
| Area select | `RtsAreaSelect` (on) | `RtsAreaSelectKey` (X), Shift+X wide | Runs (UNVERIFIED live) |
| Hold | `RtsHold` (2) | `RtsHoldKey` (Z); Shift on the Defend entry | Off (single player only) |

Every address is a `scripts/patches.json` `engine_addresses` row. Each part
binds its own rows (`HookEngine::BindEngineRows`), and each redirected call
also checks that its E8 still targets the expected callee. A part that fails
to bind stays stock, and its option row reads Unavailable
(`MarkOptionHookFailed`). The rows were checked against the shipped GOG
2.2.301 exe on 2026-11-16. Decompile line numbers refer to the GOG
ghidrecomp corpus
(`openshim_re_corpus/bzr_gog_best_effort/.../FUN_<addr>-<addr>.c`).

## The stock rule that changed

`ControlPanel::Render` (0x004A08E0, the ControlPanel vtable's slot 6) builds
the unit menu of a selection as follows:

1. It copies the first unit's ModeList (`GameObject +0x1A4`, FUN_0049f430)
   into `ControlPanel +0x113C`, then calls `ModeList::Intersect` 0x0049F270
   with each further unit's list (FUN_004a08e0.c lines 796-809; the call is
   on line 808 at 0x004A2E33).
2. `Intersect` clears every slot whose mode differs and ANDs the enabled
   masks (FUN_0049f270.c lines 8-13). Slot k's enabled bit is `1 << k`
   (FUN_0049f230.c line 7). The menu table at `+0x102C + (k-1)*0x18` is
   filled from slots 1-10 (FUN_004a6f70.c lines 10-13).
3. A pick (the mouse, or number key k) calls `ControlPanel::DispatchMode`
   0x004A7140 (FUN_004a08e0.c line 1377). That function calls each
   commandable unit's `ExecuteMode` (vtable +0x2C) and ANDs the results
   (FUN_004a7140.c lines 12-24). A true result deselects (SelectNone at
   0x004A513C).

So a Ctrl+1 group of a wingman, walker, APC and howitzer keeps only the
entries all four share in the same slot. The fixture in the tests uses those
four ModeLists, and it loses Hunt (13), Follow Close (16) and Defend (17).
Get Repair (5) and Get Reload (6) show only when every unit needs them.

With the options on, the merge call at 0x004A2E33 goes to `MergeHook`.
`MergeHook` runs the stock rule and then `SmartIntersect`. A slot holding a
"smart" mode in only one list, or the same smart mode in both, is kept, and
its enabled bits are ORed:

- `RtsSmartCommandMenu`: Hunt, Follow Close and Defend.
- `RtsSmartRepairReload`: Get Repair and Get Reload.

Other modes keep the stock rule. The dispatch call at 0x004A512A goes to
`DispatchHook`. A smart mode reaches only the commandable units whose own
ModeList holds it in an enabled slot (`SendModeToUnit`). Skipped units keep
their orders and count as accepted, so the selection still clears as in
stock. Every other mode calls the stock `DispatchMode`.

The Defend submenu's target pick calls `ControlPanel::BroadcastCommand(0xF,
target)` 0x004A7050 at 0x004A3688 (FUN_004a08e0.c line 946). With the smart
menu on it goes to `BroadcastHook`, which calls the stock per-unit
`GameObject::SetCommand(what, who)` 0x004DBD60 only for units with a Defend
entry. 0x004DBD60 is the same call BroadcastCommand makes, at 0x004A70AE
(byte scan of the exe).

The slot conflict rule: two different smart modes in the same slot cannot
both be kept, so that slot falls back to the stock rule (dropped). A smart
mode facing a non-smart mode takes the slot; stock would have dropped both.
The tests pin both cases.

## Target keys

- **Shift+T** cycles the player's target (`GameObject::SetTarget` 0x0049F450,
  the handle at `+0x21C`) through the selected own units, the player
  excluded, starting after the current target. The selection is untouched.
  The keydown is swallowed, so stock T (frontal_target) never runs and never
  clears the target. Plain T stays stock.
- **B** cycles through the player team's objects that derive from `Building`,
  plus Recycler, Factory and Armory (Construction Rig excluded). The list
  comes from a `GameObject::objectList` snapshot, newest first (handle
  sequence, `HandleSequence`).

## Area select (X / Shift+X)

- **Family.** The reticle object (`Reticle +0xAC`) when it is an own
  commandable unit with a family, else the first selected unit. Families
  (exact RTTI names): Combat (Wingman, APC, Walker), TurretTank, Howitzer,
  Minelayer, Scavenger, Tug.
- **Centre.** The reticle object, else the reticle ground point
  (`Reticle +0xA8`, a VECTOR_3D*), else the first selected unit.
  `Reticle::Simulate` (FUN_005ba560.c lines 150-179) picks only in camera
  modes 0, 1, 2 and 7 and zeroes both fields otherwise. In satellite view the
  centre therefore falls back to the first selected unit (satellite = mode 3
  is UNVERIFIED).
- **Adding.** Own commandable units of that family within 100 m (200 m with
  Shift) on the horizontal x/z plane are added nearest first through
  `ControlPanel::SelectAdd` 0x004A6C70, which has no duplicate or room check.
  So `PlanAreaAdd` skips units already selected and stops at 91
  (`selectList` capacity), and the live count is re-read before each add.

## Hold (Z, and Shift on the Defend entry)

Hold gives `GameObject::SetCommand(CMD_DEFEND)` 0x004DBCE0 (who = 0, the same
as Lua `Defend(h, 0)`), then `SetAiHold(handle, true)`
(Docs/NATIVE_HOLD_DEFEND_FOLLOW.md). It goes to the selected own commandable
units with a Defend entry; others are skipped.

- **Key path.** Keeps the selection.
- **Menu path.** Plays mnu_clik and deselects, as the other entries do.

**Why single player only.** The native hold table is process-local and not
saved, and peers never learn of it, so a held unit would act differently on
each machine. `RefreshRtsCommandsState` turns both paths off whenever
`IsSinglePlayerSession()` is false.

**Shift alternate (`RtsHold = 2`).** The swap is bound and confirmed in two
places:

- **Label.** The unit-menu entry label is
  `UiLocalize("names", modeName[mode])` at 0x004A57BE (FUN_004a08e0.c line
  1396; the row `ControlPanelModeLabelLocalizeCall` checks the bytes, and the
  E8 target 0x0081CB40). That call goes to `ModeLabelThunk`, which reads the
  mode from Render's frame (`[ebp-0x28C]`). It returns
  `ShimText("openshim_ui:rts_hold_label", "Hold")` only when the mode is
  Defend (17), Shift is down, the alternate is on and the session is single
  player. Otherwise it returns the stock string.
- **Click.** The Defend branch (`mode == 0x11`, FUN_004a08e0.c line 1370) is
  reached by both the mouse and the entry's number key. It calls
  `PlayGlobalSound("mnu_next.wav",0,0,0)` at 0x004A50B9, then sets the
  submenu and jumps to 0x004A5141. The row
  `ControlPanelDefendClickSoundCall` checks all 48 bytes, the `EB 6C` jump
  included. That call goes to `DefendClickThunk`. With Shift down it issues
  Hold, drops the return address and the four cdecl arguments, and resumes
  at 0x004A5141, so the submenu never opens. If no selected unit takes
  Defend, the stock submenu opens.
- **Never displaced.** No stock ModeList entry is replaced or displaced.
  CR's per-ODF Hunt->Hold replacement still works and does not conflict:
  that entry is a Hunt slot with its own mode, and this changes only how the
  Defend entry draws and clicks.
- **BZP.** BZP binds Shift+number to its line-up Go. With BZP loaded, Shift
  plus the Defend entry's number can fire both. Set `RtsHold = 1` (Options:
  Hold = Key Only) to keep only the Z key.

## Keys

- **Filters.** Keys are filtered as QuickSave does: a window-procedure
  subclass plus a `PeekMessageA` import hook. A latch swallows the
  autorepeats and the keyup of a swallowed keydown.
- **When they act.** Only in a live, interactive world: not in the pause
  menu, the shell, or the map editor (`InputEditModeFlag`). The world tick
  must have run in the last 500 ms. Ctrl and Alt chords are never taken.
- **Clashes.** A key equal to the Rally Point key is left to rally (rally
  wins). Rebinding refuses modifiers, digits, F1-F10, Space, Tab, Alt,
  Enter, Esc, the rally key, another RTS key, and, for the Shift actions, a
  Shift-only QuickSave chord.
- **Stock binds.** Stock binds X, Z and plain B to nothing (gamekey.map,
  input.map). F is pitch_down, which is why area select is on X.
- **Chat risk (UNVERIFIED).** Whether the game routes keys away while the
  multiplayer chat line is open has not been confirmed. Plain B, X or Z may
  act while typing in chat.

## Live checklist (not yet run)

1. Ctrl+1 group of wingman + walker + APC + howitzer: Hunt, Follow Close and
   Defend show; Hunt moves only the wingman; the walker and APC keep their
   orders.
2. Damage one unit: Get Repair shows and goes only to that unit.
3. Shift+T cycles the target over the selection; T still targets ahead.
   B cycles the buildings, newest first.
4. X adds same-type units within 100 m; Shift+X within 200 m; it also works
   in satellite view.
5. Z holds; with Shift held the Defend entry reads Hold, and clicking it
   (or pressing its number) holds and deselects.
6. In multiplayer, Hold is inert and the rest work.
