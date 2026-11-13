# Producer rally points

`[Gameplay] ProducerRallyPoints` (default ON; Options page Controls, row
"Rally Points"). Source: `src/patches/producer_rally_points.cpp`, pure logic in
`include/producer_rally_policy.h` (tests: `tests/producer_rally_policy_tests.cpp`).
Log tag `[RALLY]`.

Status: static analysis only. **UNVERIFIED at runtime**; not live-tested yet.
Addresses were read from the shipping GOG 2.2.301 exe; the expected bytes in
`scripts/patches.json` were taken from the same exe, and the vtable slots are
checked by `scripts/audit_vtable_hooks.py`.

## Behaviour

- Select a Recycler or Factory (yours, or several) and press **V**: each
  selected Recycler/Factory gets a rally point at the terrain point under the
  reticle. Pressing V again moves it.
- **Shift+V** clears the rally of the selected producers.
- Each unit the producer finishes afterwards is given a Go order (CMD_GO = 3)
  to the rally point. Scavengers, constructors (ConstructionRig), units that
  cannot be commanded, and units that already have an order are skipped.
- **Marker:** while a producer with a rally is selected (as in BZCC), the HUD
  shows a small square with the label "Rally" at the rally point and a dotted
  line from the producer to it. It is hidden when the point is behind the
  camera or off screen, and outside the views the stock reticle draws in. The
  marker is drawn only: no game object, nothing saved, no nav slot used.
- The rally goes away when the producer dies, when the mission ends or is
  reloaded, or when the feature is switched off. Rallies are not saved.
- V passes through untouched when: no eligible producer is selected, the map
  editor is active, Ctrl or Alt is held, the feature is off, the session is
  multiplayer, the pause menu or a shell screen is up, or there is no world.
  Autorepeat presses (lParam bit 30) do nothing; a WM_KEYUP is swallowed only
  when its WM_KEYDOWN was.
- With no ground under the reticle, V is swallowed (an eligible producer was
  selected) but sets nothing; the log says so.

## Hooks

| Hook | Kind | Notes |
|---|---|---|
| Recycler/Factory FinishBuild | vtable slot 42 (RecyclerVtable 0x00886454 slot at 0x008864FC; FactoryVtable 0x00879388 slot at 0x00879430) | calls stock, then orders the returned unit. Producer base (0x0088616C) and ConstructionRig (0x00877A3C) copies stay stock. All or nothing, RTTI checked. |
| Game window | `SetWindowLongPtrA(GWLP_WNDPROC)` subclass | reacts only to WM_KEYDOWN/WM_KEYUP with VK `V`; everything else goes to `CallWindowProcA(previous)`. |
| PeekMessageA | IAT patch | the main-loop tick: applies the queued V request and drops dead producers (every 250 ms). |
| HUD gauge overlay | painter slot `RallyMarker` in `hud_gauge_overlay.h` | draws the marker after the stock scrap/pilot gauge, the same paint point the autosave notice and kill ticker use. |

The WndProc only records the request (an atomic). The PeekMessageA tick also
runs inside nested modal loops (FUN_005d4690 lines 25-62 into FUN_00434600,
FUN_005d42e0, FUN_005d4a60), including while the pause menu is open, so it
touches game state (applying V, the liveness check, clearing on stand-down)
only while `WorldInteractive()` is true; otherwise a queued press is dropped
and the rest waits (`PlanTick` in the policy header). The table is shared with
the HUD painter under an SRW lock.

The marker is optional: if the camera rows or the HUD overlay do not bind,
rallies still work and the log says the marker is hidden.

### Coexistence with other subclasses and IAT hooks

The quicksave Ctrl+F5/F9 subclass and `background_run.cpp` each subclass the
same window independently and chain to the previous procedure. None of them
unhooks, so install order does not matter: whichever is outermost sees the
message first and forwards anything it does not own. Rally owns only VK `V`
without Ctrl/Alt, so it never competes with Ctrl+F5/F9. The PeekMessageA IAT
patch chains in the same way with background_run and UiPerf (UiPerf restores
with a compare-and-swap, so it does not drop a later hook).

## Addresses and evidence (GOG 2.2.301)

Decompile paths are relative to
`Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps\`.

| patches.json row | Address | Evidence |
|---|---|---|
| ProducerFinishBuild | 0x005AF160 | `FUN_005af160-005af160.c`: new object cleared at line 50 and set from Build at lines 53 and 153; AiMission add at lines 162-163; `+0x300` cleared at line 167. The decompile shows `void`, but the exe loads eax from `[ebp-0x160]` (the new object) at 0x005AF790 before the only `ret` at 0x005AF7A5. thiscall, no arguments. |
| GameObjectSetCommandWhere | 0x004DBE70 | `FUN_004dbe70-004dbe70.c` lines 23-25 (`+0xC8`=0, `+0xCC`=what, `+0xD0`=0), 33-37 (AiPath at `+0xD4` built from the position), 38-39 (param at `+0xE0/+0xE4`). thiscall, `ret 0x10`. |
| (stock caller) | 0x004A70C0 | `FUN_004a70c0-004a70c0.c` lines 9-13: selection count at `CP+0x188`, handles at `CP+0x1C+4i`, GetObj, CanCommand (vtable `+0x38`, slot 14), then SetCommand. The rally uses the same selection walk and gate. |
| InputEditModeFlag | 0x009181B8 | `FUN_005b0920-005b0920.c` lines 7-8 store `(param == 1)`; editor enter `FUN_004c82d0-004c82d0.c` line 6 passes 1, editor exit `FUN_004c8310-004c8310.c` line 13 passes 0; `FUN_005b08b0-005b08b0.c` lines 10-11 turn it into the EditMode input-program bit. |
| ControlPanelGlobal | 0x00978E20 | data; the selection walk above reads it. |
| ReticleGlobal (existing row) | 0x025CE6D0 | `+0xA8` is the ground-hit VECTOR pointer, null without a terrain hit. Reticle::Simulate passes it to the ControlPanel as the command "where" at 0x005BAA8A-0x005BAAA3 (disassembly; stored at `CP+0x1124`). This is the stock command-targeting ground hit, not a new raycast. |
| GetCameraRecord (existing row) | 0x00439E60 | `FUN_00439e60-00439e60.c` line 5 returns `&DAT_008eaae0`. The stock reticle projects with it in `FUN_005bc170-005bc170.c`: line 56 gets the record, line 61 multiplies by the matrix at record `+0x40`, line 78 requires depth > 0.0001, lines 79 and 81 compute `x = rec[2]*vx/vz + rec[0]` and `y = rec[3]*vy/vz + rec[1]`. Matrix product (translation as doubles at matrix `+0x28`): `FUN_0081fe60-0081fe60.c` lines 28-36. `ProjectToScreen` repeats this arithmetic. |
| ViewRecord (existing row) | 0x008EAAD0 | `+8` is Current_View (`DAT_008eaad8`); `FUN_005bc170-005bc170.c` line 54 draws the reticle only in views 0, 1, 2 and 7, and the marker uses the same set. |

`input.map` binds V only under the EditMode program (`edit_vertflip`, and
`edit_paste` = Ctrl+V); V has no gameplay binding.

Every required row is bound through `BindEngineRows`; any mismatch, a
non-0x00400000 image base, an RTTI mismatch, or a slot that holds neither stock
nor the hook leaves the feature uninstalled and marks the Options row failed.
The hooks install even when the ini value is 0, so the Options row can turn it
on live. Install runs once per process.

## Known limits

- The ground hit comes from the smart reticle, whose ray stops at about 200 m;
  a point further away cannot be picked.
- Up to 32 rallies at once; past that, V on a new producer is ignored (logged).
- Not saved: a loaded game has no rallies.
- The dotted line needs the producer's position on screen; when the producer
  is behind the camera only the marker is drawn.
- Single player only (FeatureTier::SinglePlayer).

## Live test checklist (UNVERIFIED)

- V with a Factory selected shows the "Rally" marker under the reticle,
  only while that Factory is selected, with a dotted line from it.
- The marker sits on the rally point (the camera record's pixel space is the
  same as the HUD text pane's) in cockpit, chase and satellite views, and
  hides when you turn away.
- A new tank drives to the rally; a new scavenger and a new constructor do not.
- V again moves the rally; Shift+V clears it; destroying the producer clears it.
- A freshly built unit has `nextCmd.what == 0` after FinishBuild (else every
  unit reads "already ordered") and CanCommand is true for it.
- V in the map editor still flips; Ctrl+V still pastes.
- Pressing V and opening the pause menu at once does nothing later.
- Nothing happens in multiplayer.
- The game window is found by its title ("Battlezone 98 Redux").
