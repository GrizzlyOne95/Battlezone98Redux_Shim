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

- Select a Recycler or Factory (yours, or several) and press **V** to arm
  **rally set mode**. While it is armed the engine's own ground reticle and
  order line show the target exactly as for a Go order; the stock confirm key
  (`menu_press`, "Reticle Command", normally Space) sets the rally of every
  selected Recycler/Factory at that ground point and ends the mode. V again
  cancels. Setting a new rally moves the old one.
- While armed, aiming at an object gives no command (no attack/follow orders),
  and the confirm issues no order and sends nothing over the network. Stock
  then deselects (SelectNone after a ground command), as after any Go.
  Ground under a unit or building cannot be picked: Reticle::Simulate drops
  the ground point whenever the reticle is on an object.
- The mode is cancelled when the selection changes in any way (it must stay
  exactly the units selected at V), when the mission ends or the sim is left,
  when the in-game editor opens, when the feature is switched off, and by
  Shift+V.
- **Fallback:** if any of the three command hooks below is missing on a build
  (signature or prologue mismatch), V keeps the original behaviour: it sets
  the rally at once to the terrain point under the reticle. The log says
  `[RALLY] set mode unavailable (command hooks installed mask=...)` once, on
  the first V.
- **Shift+V** clears the rally of the selected producers.
- **Command panel row:** while a Recycler or Factory of yours is selected
  (the V key gate's test) and the stock green command panel shows its unit
  orders, a 14th row sits under "TAB Cancel": a key box reading V and the
  label "Rally Point", or "Cancel Rally" while set mode is armed. Same font,
  colour (`HudColorWhite`), x anchor and row pitch as the SPACE/ALT/TAB rows.
  If a mod adds a `key_V` HUD sprite it is drawn the stock way; otherwise the
  box is an outline the size of `key_TAB` (atlas size times the UI scale) with
  the V centred in it. Display only: the engine hit-tests rows 0-12, so the row
  cannot be clicked. Not drawn in the alternate (touch) command layout, while
  EXU owns the command presentation, in the editor, or with the feature off.
  It fades with the panel when `CommandHudFade` is on.
- Each unit the producer finishes afterwards is given a Go order (CMD_GO = 3)
  to the rally point. Scavengers, constructors (ConstructionRig), units that
  cannot be commanded, and units that already have an order are skipped.
- **Beacon:** while a producer with a rally is selected (as in BZCC), the
  stock nav beacon mesh (`apcamr.mesh`) stands at the rally point in the 3D
  world, spinning slowly (1 rad/s, the beacon's own `omegaSpin`). It is an
  Ogre scene node and entity only: no game object, no collision, nothing
  saved, no nav slot used, no effect on the simulation.
- **Recycler vs Factory:** the beacon's lamp is green for a Recycler and amber
  for a Factory. Same geometry; the Factory uses its own generated mesh
  `rally/v1/openshim_rally_beacon_fac.mesh` whose lamp submesh is the material
  `openshim_rally_beacon_lamp_fac` (textures `openshim_rally_beacon_lamp_fac_d.tga`
  and `_e.tga`, written with the other beacon materials; the frame and the
  specular map are shared). The type is the producer's vtable
  (`ProducerKindOf`, the same Recycler/Factory vtable test as
  `IsHookedProducer`); anything else keeps green. A beacon slot handed a
  producer of the other type is destroyed and re-made with the right mesh.
  The stock-mesh fallback has one look (once it is in use, generated meshes
  are re-made as stock). A payload directory that overrides
  `openshim_rally_beacon.material` must also define
  `openshim_rally_beacon_lamp_fac`, or the Factory lamp renders white. The HUD label reads the producer's ODF
  `[GameObjectClass] unitName` (`KillTicker::LookupUnitName`, resolved in the beacon tick and cached per
  ODF; the HUD painter only reads the cache and measures the text for the
  backing panel)
  plus " rally", e.g. "Recycler rally" / "Factory rally": printable ASCII only,
  at most 20 name characters, with the generic "Rally" when the unitName is
  empty or unreadable. The pure rules are in `producer_rally_policy.h`.
- **HUD marker:** a dotted line from the producer to the rally point and the
  label ("<unitName> rally", see above) under it, so the beacon reads as a rally and not as a stock
  nav. When there is no beacon for that rally (the mesh could not be created,
  or more than 8 rallied producers are selected), a small square is drawn at
  the point too. The HUD parts are hidden when the point is behind the camera
  or off screen, and outside the views the stock reticle draws in.
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
| PeekMessageA | IAT patch | the main-loop tick: applies the queued V request, cancels set mode when the selection changed, and drops dead producers (every 250 ms). |
| Ground-aim GetCommand 0x0045BD80 | JMP5 entry detour, patches.json `Producer Rally Ground Command Hook` | thiscall `(const VECTOR_3D* where)`, ret 4; 6-byte prologue `55 8B EC 83 EC 0C` relocated to a trampoline. Returns CMD_GO (3) while armed with the armed selection, so `Reticle::Simulate` hands a Go to the ControlPanel and the stock reticle and order line draw. |
| Object-aim GetCommand 0x0045BBE0 | JMP5 entry detour, `Producer Rally Object Command Hook` | thiscall `(GameObject* target)`, ret 4; prologue `55 8B EC 83 EC 10`. Returns 0 while armed. |
| ControlPanel::BroadcastCommand 0x004A70C0 | JMP5 entry detour, `Producer Rally Broadcast Command Hook` | thiscall `(int what, const VECTOR_3D* where)`, ret 8; prologue `55 8B EC 83 EC 0C`. While armed, a CMD_GO with a ground point on the global ControlPanel sets the rally and returns without the stock body (no SetCommand). |
| Command panel row | `ContextualHud::RegisterCommandPanelPostDraw` (contextual_hud.cpp owns ControlPanel render slot 6, `HudFadeCommandRenderSlot` 0x00877E68) | registered from the game thread the first time the feature is active, so with rally off the slot stays stock. The wrapper refuses unless the slot holds 0x004A08E0; then there is no row (logged). The callback runs after the stock render, inside the fade scope and SEH. |
| HUD gauge overlay | painter slot `RallyMarker` in `hud_gauge_overlay.h` | draws the marker after the stock scrap/pilot gauge, the same paint point the autosave notice and kill ticker use. |
| ChunkEffect::Simulate (existing hook) | `TickProducerRallyMeshes()` after `TickShellCasings` in `ChunkEffectSimulateHook` | places, shows and hides the beacons. |
| Ogre scene teardown (existing hooks, `lifecycle_seams.cpp`) | clearScene / destroyAllMovableObjects: `ForgetProducerRallyMeshes`; destroyAllEntities: `DestroyProducerRallySceneObjects` | the same seams the shell casings use. |

The WndProc only records the request (an atomic). The PeekMessageA tick also
runs inside nested modal loops (FUN_005d4690 lines 25-62 into FUN_00434600,
FUN_005d42e0, FUN_005d4a60), including while the pause menu is open, so it
touches game state (applying V, the liveness check, clearing on stand-down)
only while `WorldInteractive()` is true; otherwise a queued press is dropped
and the rest waits (`PlanTick` in the policy header). The table is shared with
the HUD painter under an SRW lock.

The marker is optional: if the camera rows or the HUD overlay do not bind,
rallies still work and the log says the marker is hidden.

### The 3D beacon

- Mesh: `apcamr.mesh`, the stock nav beacon. Stock `apcamr.odf` (classLabel
  `camerapod`, unitName "Nav", `omegaSpin = 1.0`; text copy in
  `Battlezone_Source\BZ1\1.5\Battlezone_Install\stock\apcamr.odf`) has
  baseName `apcamr`; Redux ships `BZ_ASSETS/common/models/apcamr.mesh` with
  `apcamr.skeleton` and `pc/materials/apcamr.material`, and a GOG
  `BZOgreLogfile.log` shows `Mesh: Loading apcamr.mesh.` during a mission.
  Read with the BZ98RBlenderToolKit serializer: AABB y from 0.0015 to 4.66, so
  the origin is at the base and the node sits at the rally point unlifted.
- Objects: up to 8 node+entity pairs, made lazily with
  `CreateShimOwnedStockMeshObject` (`chunk_proxy_render.cpp`: the shim-owned
  mesh helper without the chunk payload group, since the mesh is in an engine
  group) and reused. Shown and placed with `SetShimOwnedObjectTransform`,
  hidden with `HideShimOwnedEntity`.
- Space: render = (x - ox, y - oy, -z - oz) with the origin from the
  `WorldRenderOrigin` row, via `ShellCasings::SimToRenderPoint`
  (`include/shell_casing_physics.h`), the shell casings' conversion.
- Thread and timing: every create, move, hide and destroy runs on the game
  thread: the tick in ChunkEffect::Simulate (the point the shell casings and
  skinned gibs use), `ResetProducerRallyPoints` (SetRunning "left
  simulation", the Lua mission reset, the feature revert) and Ogre's scene
  teardown. Never from the WndProc or the HUD painter. The one patch-thread
  caller is the startup revert (`ResolveBzrHooks` →
  `RevertRegisteredFeaturesToBaseline`), which runs before any beacon exists.
  While the pause menu is open the beacon is left as it was (no spin).
  A failed transform destroys that beacon; three failures fall back to the HUD
  square for the rest of the process.
- Lifetime: `ResetProducerRallyPoints` destroys the beacons (only when their
  scene manager is the live one) and forgets them; clearScene and
  destroyAllMovableObjects forget them (Ogre frees them); destroyAllEntities
  destroys them first, as for the casing pool. A changed scene manager makes
  the tick forget the old pointers. Nothing is kept across missions.
- Fail closed: no new engine address (Ogre exports by name and the existing
  `WorldRenderOrigin` row). If the entity cannot be created, the log says
  `[RALLY] rally beacon mesh apcamr.mesh could not be created; HUD marker only`
  once, no beacon is tried again in that process, and the HUD square returns.
- Bounds: not touched. Mesh bounds are shared with the stock nav beacons, and
  Redux sets craft meshes to infinite bounds at runtime, so the beacons may be
  submitted to every camera; at most 8 small entities.

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
| Producer Rally Broadcast Command Hook | 0x004A70C0 | `FUN_004a70c0-004a70c0.c` lines 9-13: selection count at `CP+0x188`, handles at `CP+0x1C+4i`, GetObj, CanCommand (vtable `+0x38`, slot 14), then SetCommand. The rally uses the same selection walk and gate. Called from ControlPanel::Render `FUN_004a08e0-004a08e0.c` lines 571 and 586 with `(cmdButton what CP+0x111C, where CP+0x1124)` on `menu_press` (`DAT_0091988e`, line 542), line 592 then calls SelectNone `FUN_004a6d50`; also line 664 and OverView `FUN_00587ef0-00587ef0.c` line 211. Disassembly: `ret 8` at 0x004A7134. |
| Producer Rally Ground Command Hook | 0x0045BD80 | `FUN_0045bd80-0045bd80.c` lines 9-24: with a selection (`DAT_00978fa8`) the first selected object's vtable `+0x30(where)`, else ControlPanel mode 1 gives 3. Reticle::Simulate `FUN_005ba560-005ba560.c` lines 159-163 call it with the ground hit (`+0xA8`) and line 171 passes the result to `FUN_004a71e0` (cmdButton what/where, `FUN_004a71e0-004a71e0.c` lines 11-12). Disassembly: `mov ecx,0x91553F` before both calls (0x005BAA39, 0x005885E7), `ret 4` at 0x0045BDEA. |
| Producer Rally Object Command Hook | 0x0045BBE0 | `FUN_0045bbe0-0045bbe0.c` lines 11-14: the first selected object's vtable `+0x34(target)`. Called by Reticle::Simulate `FUN_005ba560-005ba560.c` line 167 with the aimed object. Disassembly: `ret 4` at 0x0045BD70. |
| InputEditModeFlag | 0x009181B8 | `FUN_005b0920-005b0920.c` lines 7-8 store `(param == 1)`; editor enter `FUN_004c82d0-004c82d0.c` line 6 passes 1, editor exit `FUN_004c8310-004c8310.c` line 13 passes 0; `FUN_005b08b0-005b08b0.c` lines 10-11 turn it into the EditMode input-program bit. |
| ControlPanelGlobal | 0x00978E20 | data; the selection walk above reads it. |
| ReticleGlobal (existing row) | 0x025CE6D0 | `+0xA8` is the ground-hit VECTOR pointer, null without a terrain hit. Reticle::Simulate passes it to the ControlPanel as the command "where" at 0x005BAA8A-0x005BAAA3 (disassembly; stored at `CP+0x1124`). This is the stock command-targeting ground hit, not a new raycast. |
| GetCameraRecord (existing row) | 0x00439E60 | `FUN_00439e60-00439e60.c` line 5 returns `&DAT_008eaae0`. The stock reticle projects with it in `FUN_005bc170-005bc170.c`: line 56 gets the record, line 61 multiplies by the matrix at record `+0x40`, line 78 requires depth > 0.0001, lines 79 and 81 compute `x = rec[2]*vx/vz + rec[0]` and `y = rec[3]*vy/vz + rec[1]`. Matrix product (translation as doubles at matrix `+0x28`): `FUN_0081fe60-0081fe60.c` lines 28-36. `ProjectToScreen` repeats this arithmetic. |
| ViewRecord (existing row) | 0x008EAAD0 | `+8` is Current_View (`DAT_008eaad8`); `FUN_005bc170-005bc170.c` line 54 draws the reticle only in views 0, 1, 2 and 7, and the marker uses the same set. |

| CommandMenuRowAnchors (new) | 0x009174E8 | `FUN_0049f9e0-0049f9e0.c` lines 57-69: 13 rows, x = row left + offsets, y = (top + 1 + bottom) / 2 with top = base + (i+1)*pitch, so the pitch is constant. Lines 88-100: ALT is row 11 (0x00917540/44), TAB row 12 (0x00917548/4C), and `PTR_DAT_008e7c8c` (the TAB draw pointer) holds 0x00917548 in the exe. New row: x = TAB x, y = TAB y + (TAB y - ALT y). |
| CommandMenuKeyInset (new) | 0x008E7BD0 | `FUN_0049f9e0-0049f9e0.c` line 51 (= UI scale x * 4). Every key sprite goes to `x - inset`: `FUN_004a08e0-004a08e0.c` lines 698-701 (TAB) and 1383-1386 (unit rows). |
| HudFeedbackSprite (existing) | 0x0068C560 | `FUN_0068c560-0068c560.c`: size = atlas w/h (sprite record +0xC/+0xE) times the UI scale; flag 0x20000 right-aligns x, 0x40000 centres y (h >> 1). Used for a mod's `key_V` with the stock flags 0x60001 and scale 0. |
| HudFadeFont (existing) | 0x00689D10 | cdecl (font, pane, x, y, text): `add esp,0x14` after each call in Render (0x004A210B, 0x004A274F). The decompile drops the text argument at lines 711 and 1402. |
| CommandMenuTextHeight (new) | 0x00689A70 | body `9.0 * [0x02BF0420]`, returned with `fld` (ST0), no arguments read. Render centres the TAB label with it: `FUN_004a08e0-004a08e0.c` lines 707-711, `y - height/2`. |
| CommandMenuTextMeasure (new) | 0x00689AB0 | `FUN_00689ab0-00689ab0.c`: (font, text, float* w, float* h). Render measures the SPACE label with it (lines 605-609). Used only to centre the V. |
| UiFontContext / HudColorWhite / HudPaneBuffer (existing) | 0x0091552C / 0x0091755C / 0x00917580 | Render sets the label colour with `FUN_00689950(*0x0091552C, *0x0091755C)` (line 706; the decompile names it `_Init_atomic_counter`); its body is `mov [arg0], arg1`, so the font object's first dword is the colour, which the rally code writes directly. The pane is `*0x00917580`. |
| CommandMenuAltLayoutFlag (existing) | 0x00915567 | `FUN_004a08e0-004a08e0.c` lines 402-410: the `menuunderlay` frame is drawn only when this byte is 0 (and the view is wider than 400); lines 1383 and 698-699 draw key sprites only then. The row is skipped when it is non-zero. |
| Unit-command state | ControlPanel +0x11A0 == 4 | `FUN_004a08e0-004a08e0.c` lines 1313-1314: set in the branch taken when `DAT_00919875 == 0` and selection count `+0x188 > 0`. Render writes the field only while `FUN_00417c70()` (the user object, `GameObject::userObject` 0x00917AFC) is non-null (lines 367-368), so the row requires a user object and `DAT_00919875 == 0` (`CommandMenuUnitBranchInput`) too. The field is written only on the normal path (lines 815, 1013, 1208, 1314, 1501, 1663, 1876), so the row also requires a selection and an eligible producer. |
| key sprites | `key_V` (absent in stock), `key_TAB` | stock exe strings hold `key_SPC`, `key_TAB`, `key_ALT` and `key_0`..`key_9`, no `key_V`; names are looked up at run time with `FUN_0068bed0` (`g_BzrFn_HudSpriteLookup`), and the size is read from the HUD sprite rect table (`TryGetHudSpriteCurrentRecord`). |

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
- The beacon looks the same as a stock nav beacon; the HUD label tells them
  apart. No tint.
- While the game is paused the beacons stay as they were (the tick is the
  simulation's).
- Single player only (FeatureTier::SinglePlayer).

## Live test checklist (UNVERIFIED)

- The log shows the three `Producer Rally * Command Hook installed` lines and
  "rally set mode available".
- With a Factory selected, V logs `set mode armed (1 producers)`; aiming at
  the ground then shows the stock ground reticle and the order line from the
  Factory, exactly like a tank's Go. Space sets the rally (log `rally set via
  reticle at x,z`), the beacon appears there, no order is given to the
  Factory, and the selection is cleared.
- V again while armed cancels (log `set mode cancelled (V)`); the reticle is
  back to stock.
- While armed, aiming at an enemy or a friendly unit shows no attack/follow
  command, and Space on it does nothing.
- Selecting another unit, deselecting, Shift+V, restarting the mission and
  leaving to the shell each cancel the mode.
- With a tank and the Factory selected together, V arms; Space sets the
  Factory's rally and the tank gets no order.
- The satellite/overview map: armed Space or click on the map sets the rally
  the same way (OverView calls the same functions).
- V with a Factory selected shows the "Rally" marker under the reticle,
  only while that Factory is selected, with a dotted line from it.
- A spinning nav beacon stands on the ground at the rally point (not floating,
  not sunk, not mirrored to another spot), textured (not flat grey), only
  while that Factory is selected, with no square under the label. Deselecting
  hides it; selecting again shows it. The log has no "could not be created"
  line.
- A Recycler's beacon lamp is green and a Factory's amber; the labels read
  "Recycler rally" / "Factory rally" (each ODF's unitName), falling back to
  "Rally" only if the unitName cannot be read. Select both at once: two
  beacons with the two colours. Mod ODFs with another unitName show it.
- The beacon has no collision (a tank drives through it) and is not
  targetable or on radar.
- After a mission restart, a save load and a return to the shell and back,
  V again shows a beacon, and no crash or Ogre error mentions apcamr.
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
- Command panel row: the log has `command panel row registered` and one of
  `uses the key_V sprite` / `draws its own key box`. With a Factory selected
  the panel shows "V Rally Point" under "TAB Cancel": the label lines up with
  SPACE/ALT/TAB, the key box lines up with theirs and is about their size,
  and the pitch matches. V turns it to "Cancel Rally"; V again or Space turns
  it back. With a tank only, or nothing, selected there is no row.
- Underlay: `menuunderlay` is a fixed-size sprite drawn for 13 rows, so the
  14th row may sit below the green background. Check at 1080p and 1440p and
  at the smallest UI scale whether it is inside, half inside or outside; record
  which.
- With `CommandHudFade=1` the row fades and reappears with the panel; with
  it off the slot wrapper is in (log `render slot wrapper installed`) and the
  panel looks and behaves as stock. With rally off at startup the log has no
  `render slot wrapper installed` line (fade also off).
- Alternate (touch) command layout: no row.
- EXU with its command presentation on: no row.
