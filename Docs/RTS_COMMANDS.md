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
| Build at Nav | `RtsBuildAtNav` (on) | stock menu keys (Go To Nav, then the nav) | Runs for local rigs (UNVERIFIED live) |

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

Hold registers `SetAiHold(handle, true)` (Docs/NATIVE_HOLD_DEFEND_FOLLOW.md),
then gives `GameObject::SetCommand(CMD_DEFEND)` 0x004DBCE0 (who = 0, the same
as Lua `Defend(h, 0)`). It goes to the selected own commandable units with a
Defend entry; others are skipped. The hold goes first so a unit the native
hold refuses keeps its orders; if the order then fails the hold is dropped.
The native hold needs the SitTask DoState hook and the DoSubTask
retarget-period hooks (`ai_native_orders.cpp` `AiHoldHooksReady`). Without
them neither path issues anything, the Shift+Defend click opens the stock
submenu, and the Hold option reads Unavailable.

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

## Build at Nav

With a building picked on a selected Construction Rig, the unit menu's Go To
Nav entry (mode 10) reads "Build at Nav". It still opens the stock nav
submenu, and picking a nav there gives the rig BUILD at that nav. Rows:
`ControlPanelNavPickBroadcastCall` and `ConstructionRigGetCommandPos` (new),
plus `ControlPanelBroadcastCommandObj`, `GameObjectSetCommandObj`,
`GameObjectSetCommandWhere`, `ControlPanelSelectNone` and
`ConstructionRigVtable` (existing rows, bound again into this part's own
copies).

**Picked.** A selected, commandable object counts as a picked rig when all of
these hold (`PickedBuildClass`):

- its vtable is `ConstructionRigVtable` 0x00877994 (RTTI checked at install);
- it is on the player's team and is not a remote replica (GameObject
  `+0x80` byte != 2, i.e. DistributedObject `+0x68` with that base at
  GameObject `+0x18`; FUN_004b9830.c line 4, and `kGoObjectTypeOffset` in
  `producer_rally_points.cpp`);
- `+0x228 == 0` and the active ModeList mode is above 0x1A: the stock hover
  test (FUN_0049d230.c line 36; disasm 0x0049D251, 0x0049D28D);
- the drop class `+0x370` equals that active mode. ConstructionRig
  SetActiveMode writes both together (FUN_0049d0e0.c lines 12-13). Nothing
  found clears `+0x370` on cancel, so it alone is not enough, and a PRODMENU
  submenu stub never reaches the stock SetActiveMode
  (`producer_build_menu.cpp` `TryHandleProducerMenuMode`).

**Label.** The existing label redirect at 0x004A57BE (`ModeLabelThunk`, see
Hold) returns `ShimText("openshim_ui:rts_build_at_nav_label", "Build at Nav")`
for mode 10 while the option is active and the selection holds a picked rig.
That redirect is installed by the Hold part, so Build at Nav also needs that
part's rows (`GameObjectSetCommand`, `PlayGlobalSound`,
`ControlPanelDefendClickSoundCall`, `UiLocalize`), whatever `RtsHold` is set
to.

**Opening the submenu is stock.** The mode-10 click (`cmp [ebp-0x28C],0xA` at
0x004A502A) only plays a sound and sets `+0x117C` to the nav submenu
(FUN_004a08e0.c lines 1359-1362). It issues no order and never reaches
DispatchMode, so the rig keeps its pick.

**The pick.** The nav slots 0x23..0x2C (FUN_004a08e0.c line 1255) end in
`BroadcastCommand(3, nav)` and `SelectNone` (lines 1270-1271; 0x004A4A75 and
0x004A4A80). The row checks all 35 bytes from 0x004A4A64 (a single match in
the image), and each redirect checks its E8 target (0x004A7050, 0x004A6D50).
SelectNone is redirected first and the pick only after it; the option is
available only when both are in. `NavPickHook`:

1. Not CMD_GO, the option off, or no picked rig in the selection: the stock
   BroadcastCommand.
2. Otherwise, for each commandable selected unit (the stock gate, vtable
   +0x38; FUN_004a7050.c lines 11-13):
   - not a picked rig: the stock per-unit `GameObject::SetCommand(3, nav)`
     0x004DBD60;
   - a picked rig whose picked entry is disabled: refused (the build menu
     disables what the team cannot afford);
   - otherwise `ConstructionRig::GetCommand(&navPos)` 0x0049D230 (thiscall,
     ret 4). It sets the drop matrix `+0x378` with the player's facing
     (`SetConstructionMatrix` 0x0049CF90, FUN_0049d230.c line 39; the height
     comes from the terrain), runs CanBuildHere 0x00466E50 (line 48: blocked
     cells, slope variance, overlap with buildings and turrets) and, for
     COMM/TURR/SHLD, requires a friendly power plant in range (lines 56-81).
     8 (CMD_DROPOFF, 0x0049D4E2) means valid; anything else is refused.
   - On 8: `GameObject::SetCommand(0x15 CMD_BUILD, &navPos, class, 0)`
     0x004DBE70. It builds the AiPath from the rig to the nav itself
     (FUN_004dbe70.c lines 26-37), so `where` is never 0. RigProcess drops a
     BUILD without one (FUN_0049dc90.c lines 64-74, `case 0x15`). This is
     the call the AI and Lua BuildAt use (1.5 `Units_SOrderConstruct`).
3. Any refusal plays `mnu_buzz.wav`, the stock "cannot drop here" click
   (FUN_004a08e0.c line 564), and logs (budgeted) the rig and the reason.
4. When rigs were refused and nothing else was ordered
   (`KeepSelectionAfterNavPick`), the SelectNone that follows is skipped, so
   the selection, pick included, survives and the player can pick another
   nav. Otherwise SelectNone runs as in stock.
5. Ping: a build pings the nav once as CMD_BUILD (yellow). With no build, the
   GO to the other units pings green, as the stock broadcast would.

**Facing.** The player's, as the stock hover quad shows it (GetCommand line
39). Navs carry an arbitrary yaw, so their own facing is not used.

**After the build.** SelectNone calls the rig's Deselect, which PRODMENU
forwards to ConstructionRig::Deselect 0x0049CCD0 (clears the ModeList active
slot), so the pick should be gone when the rig is selected again
(UNVERIFIED live). A rig that is reselected and given a new pick before it
starts building gets a new drop matrix from the hover query, as with a
stock drop (UNVERIFIED which placement wins).

**Affordability.** Refused while the picked entry is disabled. Whether the
rig's UpdateModeList refreshes the enabled bit while the rig stays selected,
and how Producer start handles a team that cannot pay when the rig arrives,
are UNVERIFIED.

**BZP caveat.** BZP's SBPAi.lua (lines 772-790) notes that a BUILD issued
while the rig was on GO "will not stop at its destination", and forces STOP
within 80 m. The cause is UNVERIFIED (BuildGoto 0x0049E3D0 stage logic, or a
stale current order); see checklist item 16.

**Multiplayer (UNVERIFIED live).** Only local rigs are ordered (never a
replica), and the stock human drop gives the same `SetCommand(where)` on the
owner, so no new packet is sent: 0x004DBE70 forwards to the network only
for a replica (FUN_004dbe70.c lines 40-42). Whether the drop matrix and
class reach the other machines before the building replicates is
UNVERIFIED; live-test host and client.

## Command pings for unit-menu orders

`rts_markers.cpp` pings orders where `ControlPanel::BroadcastCommand` runs.
A unit-menu pick (Follow, Get Repair, Get Reload, Rescue, Recycle, and the
smart modes) goes through `DispatchMode` and the unit's `ExecuteMode`
instead, so `DispatchHook` snapshots each selected unit's pending order
(`GameObject +0xC8..+0xD7`: flag, what, who handle, path; FUN_004dbd60.c
lines 20-34) before the pick and, after it, calls
`NotifyRtsMarkersCommand(what, who)` once, for the first own unit whose
order changed and names a target object. The smart Defend-target pick
(`BroadcastHook`) skips the stock BroadcastCommand, so it calls the same
entry once. `RtsCommandPings` and the local-panel gate apply as for the
broadcast pings. An order without a target object (Hunt) gets no ping.

## Keys

- **Filters.** Keys are filtered as QuickSave does: a window-procedure
  subclass plus a `PeekMessageA` import hook. A latch swallows the
  autorepeats and the keyup of a swallowed keydown.
- **When they act.** Only in a live, interactive world: not in the pause
  menu, the shell, the map editor (`InputEditModeFlag`), or while a legacy
  text editor (in-mission chat, ally prompt) has focus
  (`LegacyTextEditorFocusLookup` 0x00823CE0, shared with the Ctrl+= HUD
  toggle as `HudVisibility::TextEditorFocused`; a failed bind or a fault
  counts as focused, so the key stays the game's). The world tick must have
  run in the last 500 ms. Ctrl and Alt chords are never taken.
- **Where they run.** The filter only queues the action. The actions change
  the selection (`SelectAdd` calls the object's OnSelect, vtable +0x20),
  the player's target and unit orders, so they run from
  `RunDeferredSceneMutations` at frameStarted, outside the render-queue
  traversal. Only while that drain is not installed do they run in the
  world render-queue tick, as the other drained features do.
- **Clashes.** A key equal to the Rally Point key is left to rally (rally
  wins). Rebinding refuses modifiers, digits, F1-F10, Space, Tab, Alt,
  Enter, Esc, the rally key, another RTS key, and, for the Shift actions, a
  Shift-only QuickSave chord. The other way round, rebinding the rally key
  refuses any RTS key, and rebinding QuickSave/QuickLoad refuses a chord an
  RTS filter takes (the plain key, or Shift+key for Shift+T and Shift+X).
  Binding a stock gamekey action to such a chord saves it with a warning
  that the RTS action takes it in missions.
- **Stock binds.** Stock binds X, Z and plain B to nothing (gamekey.map,
  input.map). F is pitch_down, which is why area select is on X.

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
7. Open the in-mission chat line (and the ally prompt) and type B, X, Z and
   Shift+T: every letter reaches the text and no RTS action fires.
8. Unit-menu Follow, Get Repair and Recycle each draw one yellow ping on
   their target; the smart Defend-target pick draws one too.
9. B cycle order: with three buildings built in a known order, B visits
   them newest first and wraps around (review N2).
10. Shift plus the Defend entry's number key (Shift+digit) holds and
    deselects exactly like the Shift+click, and with `RtsHold = 1` it opens
    the stock submenu (review N8).
11. Rebinding: the rally key refuses B; QuickSave refuses Shift+X; binding a
    stock action to X saves with the RTS clash warning.

### Build at Nav (not yet run)

12. Select a rig and pick a building: Go To Nav reads "Build at Nav". With
    no pick, or with the option off, it reads "Go To Nav". The submenu opens
    as in stock.
13. Valid nav (flat, clear, in power range for a gun tower): the rig drives
    to the nav and builds there, facing the way the player faced when
    picking; the menu deselects; one yellow ping on the nav. Repeat with the
    number keys instead of the mouse.
14. Invalid navs, each refused with the buzz while the selection (and the
    pick) stays, and `openshim.log` names the reason: a steep slope; a nav on
    top of an existing building; a gun tower, Comm Bunker or shield away
    from any power plant.
15. Mixed selection (a rig with a pick plus two wingmen): the wingmen go to
    the nav and the rig builds. With an invalid nav the wingmen still go,
    the rig buzzes, and the selection clears (stock).
16. BZP caveat: order the rig on a long Go, then Build at Nav while it is
    still moving. Does it stop and build at the nav, or overshoot?
17. After the build, reselect the rig: which build-menu entry is active?
    Pick a building and Build at Nav again before the first one finishes.
18. Affordability: pick a building, spend the scrap elsewhere until its
    entry greys out, then Build at Nav: refused. Also check what happens
    when the scrap drops after the order but before the rig arrives.
19. Multiplayer, host and client: each player's rig builds at a nav; the
    building appears on both machines in the same place, with the same
    facing.
20. After a refused and an accepted Build at Nav, look around the player:
    does the stock placement quad stay drawn at the nav (the hover query
    moves it there) until the next hover? Also check that a refused query
    does not move the rig's later stock drop.
