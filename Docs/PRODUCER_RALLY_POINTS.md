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

- **The key is rebindable.** `[Gameplay] RallyKey` (default `V`) is one key
  with no modifier: a plain press arms/cancels, Shift+key clears; this
  document says "V" for the default. Rebind it in Options > Input > RTS
  Actions, row "Rally Point" (reserved command `OpenShim:RallyKey`): the
  capture applies live (`SetRallyKeyText`), is written to openshim.ini with
  the same rollback on a write failure as the Quick Save/Quick Load rows, and
  shows a note when a stock gamekey.map action uses the same key (with an
  eligible producer selected the rally key takes it). Refused (the editor
  says why; in the ini the value falls back to V with a `[RALLY]` log line):
  any modifier, digits 0-9, F1-F10, Space, Tab, Alt, Enter, Esc, anything
  `ParseChord` does not know, and a key that is a Shift-only QuickSave or
  QuickLoad chord (Shift+key is the clear). The check runs both ways: the
  QuickSave rows refuse Shift plus the rally key, and the rally key is
  re-checked after the QuickSave chords load. An extended key (Insert, Home,
  arrows, ...) does not match its numpad twin. Ctrl+key and Alt+key are never
  ours, so a Ctrl chord on the same key (the default Ctrl+Home) is fine.
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
  orders, a V key and the label "Rally" sit on the "TAB Cancel" line,
  right-aligned to the scrap-cost column (the wider label's right edge is the
  right edge of a two-digit cost). While set mode is armed for the selection
  (V would cancel it) the label reads "Cancel". The placement uses the wider
  of "Rally" and "Cancel" and both start at the same x, so the key and the
  line do not move when it changes. Same font and colour (`HudColorWhite`) as the
  stock rows; the key sits `CommandMenuKeyInset` left of the label as on the
  stock rows. If the localized TAB label is too long to leave two insets of
  room before the key, the row moves just under the menu underlay's bottom
  edge (one inset clear, never above one row pitch under TAB); at 400 px wide
  or less, where the stock panel draws no underlay, it goes one row pitch
  under TAB. If the underlay cannot be read, or the row would leave the
  screen, it is not drawn. The log names the placement each time it changes
  (`command panel row on the TAB line` / `under the menu underlay` /
  `one row under TAB` / `hidden`).
  The cap shows the bound key's name ("V", "F11", "Ins", "PgUp", "Right";
  `RallyKeyCapName`). A mod's `key_V` HUD sprite is used only while the bound
  key is V and the sprite loads with a material;
  otherwise OpenShim draws the cap: `key_0`'s size (9x9 atlas units times the
  UI scale) for a one-character name, widened for a longer one to the
  measured text plus two reference units of padding a side (`KeyCapWidthPx`;
  the padding is a choice, not read from key_TAB/key_SPACE: UNVERIFIED), and
  `ChoosePanelRowLayout` takes that width (`keyWidthPx`) when placing the row.
  The cap is filled opaque white with `HudFillRect` with its corners notched
  by one unit, one `HudSpriteZ` step behind a black name in the stock HUD
  font, centred on it. The font colour is saved before the row is drawn and
  restored after it, also when a draw faults. It sits where the stock caps sit: right edge at the
  label x minus `CommandMenuKeyInset`, centred on the row y. No sprite asset
  ships (see "key sprites" under Addresses for why). Display only: the engine hit-tests rows 0-12, so
  the row cannot be clicked. Not drawn in the alternate (touch) command
  layout, while EXU owns the command presentation, in the editor, or with the
  feature off. It fades with the panel when `CommandHudFade` is on.
- **SPACE row in set mode:** while set mode is armed and the selection is
  still the armed one (the same test the confirm uses, so the label and the
  click agree), the stock SPACE row reads "Rally" instead of "Go To". Only the one Localize call that labels the
  SPACE row is redirected, and only the key "Go To" while armed is replaced;
  if `CommandMenuSpaceLabelLocalizeCall` does not bind, the row stays "Go To"
  (logged).
- **ALT row:** not relabelled. In set mode it cannot hold Go: its command
  (ControlPanel `+0x112C`) is written only by `AltCommand` 0x004A72A0, from
  Targeting::Simulate 0x005DEAE0 each tick with the object-aim GetCommand
  result, which the object command hook makes 0 (No Action) while armed (see
  the ALT row under Addresses).
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
- **HUD marker:** the
  label ("<unitName> rally", see above) just under the rally point (no line
  from the producer), so the beacon reads as a rally and not as a stock
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
| Game window | `SetWindowLongPtrA(GWLP_WNDPROC)` subclass | reacts only to WM_KEYDOWN/WM_KEYUP with the rally key (VK `V` by default); everything else goes to `CallWindowProcA(previous)`. |
| PeekMessageA | IAT patch | the main-loop tick: applies the queued V request, cancels set mode when the selection changed, and drops dead producers (every 250 ms). |
| Ground-aim GetCommand 0x0045BD80 | JMP5 entry detour, patches.json `Producer Rally Ground Command Hook` | thiscall `(const VECTOR_3D* where)`, ret 4; 6-byte prologue `55 8B EC 83 EC 0C` relocated to a trampoline. Returns CMD_GO (3) while armed with the armed selection, so `Reticle::Simulate` hands a Go to the ControlPanel and the stock reticle and order line draw. |
| Object-aim GetCommand 0x0045BBE0 | JMP5 entry detour, `Producer Rally Object Command Hook` | thiscall `(GameObject* target)`, ret 4; prologue `55 8B EC 83 EC 10`. Returns 0 while armed. |
| ControlPanel::BroadcastCommand 0x004A70C0 | JMP5 entry detour, `Producer Rally Broadcast Command Hook` | thiscall `(int what, const VECTOR_3D* where)`, ret 8; prologue `55 8B EC 83 EC 0C`. While armed, a CMD_GO with a ground point on the global ControlPanel sets the rally and returns without the stock body (no SetCommand). |
| Command panel row | `ContextualHud::RegisterCommandPanelPostDraw` (contextual_hud.cpp owns ControlPanel render slot 6, `HudFadeCommandRenderSlot` 0x00877E68) | registered from the game thread the first time the feature is active, so with rally off the slot stays stock. The wrapper refuses unless the slot holds 0x004A08E0; then there is no row (logged). The callback runs after the stock render, inside the fade scope and SEH. |
| SPACE row label | REL32 call redirect at 0x004A207C, patches.json `CommandMenuSpaceLabelLocalizeCall` | the `call Localize` (0x0081CB40) that labels the SPACE row; the redirect returns "Rally" when `ArmedAndMatching()` (feature active, set mode armed, selection unchanged) and the key is "Go To", and otherwise calls the original target decoded from the verified call bytes. Applied with `HookEngine::ApplyPatch` like the MP ready explainer's call redirect. No bind or a refused patch: stock label. |
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
message first and forwards anything it does not own. Rally owns only the rally key (VK `V` by default)
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

| CommandMenuRowAnchors (new) | 0x009174E8 | `FUN_0049f9e0-0049f9e0.c` lines 57-69: 13 rows, x = row left + offsets, y = (top + 1 + bottom) / 2 with top = base + (i+1)*pitch, so the pitch is constant. Lines 88-100: ALT is row 11 (0x00917540/44), TAB row 12 (0x00917548/4C), and `PTR_DAT_008e7c8c` (the TAB draw pointer) holds 0x00917548 in the exe. The row uses TAB y; the pitch (TAB y - ALT y) sets the fallback places. |
| CommandMenuSpaceLabelLocalizeCall (new) | 0x004A207C | `FUN_004a08e0-004a08e0.c` line 604: `FUN_0081cb40("names", (&PTR_s_No_Action_008e7a18)[*(int*)(CP+0x111c) * 2])`. Disassembly 0x004A2069-0x004A2084: `mov edx,[ecx+0x111c]`; `mov eax,[edx*8+0x8e7a18]`; `push eax`; `push 0x87736c` ("names"); `call 0x81cb40` (`E8 BF AA 37 00`); `add esp,8`; `mov [ebp-0x388],eax`. The row's `expected` pins all 14 bytes from the call on. The ALT row (line 677) reads the same table with `mov ecx,[eax*8+0x8e7a18]` at 0x004A26B4, so this site is the SPACE row only. The table entry for CMD_GO (3) points at "Go To" (0x00877EAC). `FUN_0081cb40` is Localize, cdecl `(section, key)`, string in EAX (it logs "Localization system missing string" on a miss). |
| CommandMenuRowRects (existing) | 0x009173E8 | `FUN_0049f9e0-0049f9e0.c` lines 57-63: 13 x {left, top, right, bottom}. The classic layout draws the cost text left-aligned at `rect[row].right - (int)(scaleX * 20) - DAT_009173e0` (`FUN_004a08e0-004a08e0.c` lines 1436-1440, text from `sprintf("%02ld")` at line 1430) and a "P" (0x0087813C) at `right - (int)(scaleX * 6)` when `FUN_004e1c10` is non-zero (lines 1464-1480). `DAT_009173e0` is 0 in the classic layout (`FUN_0049f9e0-0049f9e0.c` line 43). The rally label's right edge is row 12's `right - (int)(scaleX * 20)` plus the measured width of "00". |
| CommandUiBoundsLeft (existing) / CommandUiUnderlaySpriteId (existing) / HudViewportWidth (existing) | 0x0260D748 / 0x009173E4 / 0x02CECEE0 | `FUN_004a08e0-004a08e0.c` lines 402-410: the underlay is drawn only when the viewport width is over 400 and the layout is classic, with `FUN_0068ca30(pane, ?, sprite, bounds.left - (int)(scaleX * 18), bounds.top, (int)((w + 0x6e) * scaleX / 2.0), (int)(h * scaleY / 2.0), 0, 0)`; h is `FUN_0068f0c0` (`FUN_0068f0c0-0068f0c0.c`: record +0xE, the rect table's h). Flags 0 leave x and y unadjusted (`FUN_0068ca30-0068ca30.c` lines 49-64), so the bottom edge is `bounds.top + (int)(h * scaleY / 2.0)`. The sprite id is picked each frame at lines 360-365; bounds are `{left, top, right, bottom}` (`FUN_0049f9e0-0049f9e0.c` line 101). HudViewportHeight (0x02CECEE4, existing) keeps the row on screen. |
| HudSpriteMaterialTable (new) | 0x025F8F38 | the HUD sprite records, stride 0x24, start 8 bytes before HudSpriteRectTable; +0 is the Ogre MaterialPtr. `FUN_0068b340-0068b340.c` lines 195-199 resolve each row's material with `Ogre::MaterialManager::getByName` and assign it with `FUN_00449910` (SharedPtr assignment); disassembly 0x0068B823-0x0068B830 (`imul ecx,[ebp-0x490],0x24`; `add ecx,0x25f8f38`; `call 0x449910`). The draws index the same base (`FUN_0068c560-0068c560.c` line 50, `FUN_0068ca30-0068ca30.c` line 48). A key_V row is drawn only when its pRep is non-null; what `FUN_0068c560` does with a null material is UNVERIFIED, which is why. pRep is the SharedPtr's first member (`third_party/ogre-1.10.0-bzr/_work/OgreMain/include/OgreSharedPtr.h` lines 133-134: `T* pRep; SharedPtrInfo* pInfo;`). |
| CommandMenuKeyInset (new) | 0x008E7BD0 | `FUN_0049f9e0-0049f9e0.c` line 51 (= UI scale x * 4). Every key sprite goes to `x - inset`: `FUN_004a08e0-004a08e0.c` lines 698-701 (TAB) and 1383-1386 (unit rows). |
| HudFeedbackSprite (existing) | 0x0068C560 | `FUN_0068c560-0068c560.c`: size = atlas w/h (sprite record +0xC/+0xE) times the UI scale (lines 55 and 65-66; scale 0 becomes 1, lines 51-53); flag 0x20000 right-aligns x (lines 56-63), 0x40000 centres y (h >> 1, lines 67-74). Used for a mod's `key_V` with the stock flags 0x60001 and scale 0; the drawn cap reproduces the same rect (`KeyBoxRect`). |
| HudFillRect (existing) | 0x0068AFB0 | `FUN_0068afb0-0068afb0.c`: clips, then `FUN_0068af70`, which passes `x2 + 1, y2 + 1` to the quad (`FUN_0068af70-0068af70.c` line 9), so the corners are inclusive. Mode 0 keeps the ARGB colour (autosave notice notes, `src/patches/autosave_notice.cpp`). Draws the cap. |
| HudSpriteZ (existing) | 0x00920EF4 | the 2D sprite depth; Render raises it by 0.04 around the underlay (`FUN_004a08e0-004a08e0.c` line 403) and the stock text call by 0.01 around its own background fill (existing row identity). The cap is filled at +0.01 and the value restored, as `hud_gauge_overlay.cpp` does for its text backings. |
| Text colour | font object +0 | the label colour is the font object's first dword (`FUN_00689950`, see UiFontContext below), so the glyph is drawn black (0xFF000000) and the label colour restored for the label. Colours are ARGB (`HudColorBlue` holds 0xFF007FFF). |
| HudFadeFont (existing) | 0x00689D10 | cdecl (font, pane, x, y, text): `add esp,0x14` after each call in Render (0x004A210B, 0x004A274F). The decompile drops the text argument at lines 711 and 1402. Draws the label and the cap's V. |
| CommandMenuTextHeight (new) | 0x00689A70 | body `9.0 * [0x02BF0420]`, returned with `fld` (ST0), no arguments read. Render centres the TAB label with it: `FUN_004a08e0-004a08e0.c` lines 707-711, `y - height/2`. |
| CommandMenuTextMeasure (new) | 0x00689AB0 | `FUN_00689ab0-00689ab0.c`: (font, text, float* w, float* h). Render measures the SPACE label with it (lines 605-609). Used to centre the V, and to measure "Rally", "Cancel" (the placement takes the wider), "00" and the localized TAB label (`Localize("names", "Cancel")`, the key Render passes at line 707, through `UiLocalize`) for the placement. Two digits: the cost is `sprintf("%02ld")` of class `+0x48` (`FUN_004e1b90-004e1b90.c` line 9; lowered by 2 or 1 by `DAT_025cfa1c`, lines 15-19), the highest stock `scrapCost` is 99 (the 1.5 stock ODFs in `Battlezone_Source` and CR's ODFs, scanned 2026-11-13; Redux's own ODFs sit in `bzone.zfs` and were not scanned, UNVERIFIED), and a wider cost would run into the stock "P" at `right - scaleX * 6` anyway. |
| UiLocalize (new) | 0x0081CB40 | Localize, cdecl `(section, key)`, string in EAX: callers pop 8 (`add esp,8` at 0x004A26C6) and store EAX (`mov [ebp-0x3c8],eax` at 0x004A26C9); `FUN_0081cb40-0081cb40.c` line 40 logs "Localization system missing string: " (the decompile types it `void`, line 2). `expected` is the 16-byte prologue with the stack-cookie load (`mov eax,[0x008E7000]`). Bound on its own after the panel rows: without it only the TAB width is unknown and the row goes under the underlay; the SPACE redirect does not use it. |
| ALT row (no row; not relabelled) | 0x004A26C1 | The ALT label is `Localize("names", table[CP+0x112C * 2])` (`FUN_004a08e0-004a08e0.c` line 677; disassembly `mov eax,[edx+0x112c]` 0x004A26AE, `call 0x81cb40` 0x004A26C1). `+0x112C` has two writers: 0x1D in `FUN_004a0160-004a0160.c` line 48 (an init, not Go) and `FUN_004a72a0-004a72a0.c` line 7 (AltCommand). AltCommand's only caller is `FUN_005deae0-005deae0.c` line 66, passing `FUN_0045bbe0` (the object-aim GetCommand, line 62; 1 becomes 0, lines 63-65). 0x005DEAE0 is slot 5 of `Targeting::vftable` (0x008884D8; pointer at 0x008884EC; RTTI `.?AVTargeting@@`); BZ 1.5's `Targeting::Simulate` (`Battlezone_Source/BZ1/1.5/functions/004d/004dc119_Targeting_Simulate.c` lines 69-74) is the same shape and calls `ActionMode::GetCommand` then `ControlPanel::AltCommand` every simulate. While `ArmedAndMatching()` the object hook returns 0, so the ALT row reads "No Action" from the next simulate on and can never be Go. That Redux runs this slot every tick is inferred from the 1.5 counterpart (UNVERIFIED in Redux). |
| UiFontContext / HudColorWhite / HudPaneBuffer (existing) | 0x0091552C / 0x0091755C / 0x00917580 | Render sets the label colour with `FUN_00689950(*0x0091552C, *0x0091755C)` (line 706; the decompile names it `_Init_atomic_counter`); its body is `mov [arg0], arg1`, so the font object's first dword is the colour, which the rally code writes directly. The pane is `*0x00917580`. |
| CommandMenuAltLayoutFlag (existing) | 0x00915567 | `FUN_004a08e0-004a08e0.c` lines 402-410: the `menuunderlay` frame is drawn only when this byte is 0 (and the view is wider than 400); lines 1383 and 698-699 draw key sprites only then. The row is skipped when it is non-zero. |
| Unit-command state | ControlPanel +0x11A0 == 4 | `FUN_004a08e0-004a08e0.c` lines 1313-1314: set in the branch taken when `DAT_00919875 == 0` and selection count `+0x188 > 0`. Render writes the field only while `FUN_00417c70()` (the user object, `GameObject::userObject` 0x00917AFC) is non-null (lines 367-368), so the row requires a user object and `DAT_00919875 == 0` (`CommandMenuUnitBranchInput`) too. The field is written only on the normal path (lines 815, 1013, 1208, 1314, 1501, 1663, 1876), so the row also requires a selection and an eligible producer. |
| key sprites | `key_V` (absent in stock), `key_0` | stock exe strings hold `key_SPC`, `key_TAB`, `key_ALT` and `key_0`..`key_9`, no `key_V`; names are looked up at run time with `FUN_0068bed0` (`g_BzrFn_HudSpriteLookup`), and the size is read from the HUD sprite rect table (`TryGetHudSpriteCurrentRecord`). The stock caps are opaque white with a black glyph (`BZ_ASSETS\pc\textures\MISC_DDS\sprite_n.dds`, material `sprite_n : BZSprite/AlphaHUDPixel` in `sprites.material`). Whether the key sprite call (flags 0x60001, colour index 1 through `FUN_0068f030`) tints that white is UNVERIFIED, so the drawn cap may differ slightly in shade from the stock ones. Why no OpenShim sprite ships: sprite tables are `bzfont.st`, `spritea.st` and every `*.sta` the engine file search finds (`FUN_0068b0e0-0068b0e0.c` lines 34-55); that search walks the engine file table (`FUN_008287d0-008287d0.c` lines 8-13), and the only loose-file root confirmed for it is `<game>\addon` (`FUN_00618ff0-00618ff0.c` lines 74-90, registered at `FUN_00820f10-00820f10.c` line 12 and `FUN_0076b7a0-0076b7a0.c` line 34). OpenShim does not write into `addon\`, and whether the OpenShim folders or CustomWidgets are in that table is UNVERIFIED, so a shipped `.sta` route is UNVERIFIED and was not taken. |

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
  only while that Factory is selected, with no line from the Factory to it.
- A spinning nav beacon stands on the ground at the rally point (not floating,
  not sunk, not mirrored to another spot), textured (not flat grey), only
  while that Factory is selected, with no square under the label. Deselecting
  hides it; selecting again shows it. The log has no "could not be created"
  line.
- Second launch (the generated material already on disk): the beacon is
  textured, and BZOgreLogfile.log has no `base object named "BZBase" not
  found` compiler error for `openshim_rally_beacon.material`. The generated
  script starts with `import * from "BZBase.material"` so it compiles whatever
  order the resource group parses it in; a payload override of the file should
  do the same.
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
- Rebinding: Options > Input > RTS Actions lists "Rally Point" with V. Press
  Ins on it: the status line says bound, the row reads the key, openshim.ini
  has `RallyKey = GreyInsert` (or the spelling the capture wrote), and with a
  Factory selected Ins arms set mode at once (no restart), V no longer does,
  Shift+Ins clears, and numpad 0 (NumLock off) is left to the game. The
  panel row cap reads "Ins", is wider than the 9-unit cap, the row stays
  clear of "Cancel" (or drops under the underlay), and the label and line
  keep their x. A one-letter key keeps the 9x9 cap; V with a `key_V` mod
  sprite uses the sprite, any other key the drawn cap. Try Shift+V, 5, F1
  and Space: each is refused with a reason and the old key stays. Make
  openshim.ini read-only and rebind: the status says the old key was kept and
  the key still works as before. Bind a key a stock action uses: the status
  names that action. A bad `RallyKey =` line in the ini logs `[RALLY]
  [Gameplay] RallyKey=... ignored` and V works.
- Pressing V and opening the pause menu at once does nothing later.
- Nothing happens in multiplayer.
- The game window is found by its title ("Battlezone 98 Redux").
- Command panel row: the log has `command panel row registered`,
  `draws its own key cap (key_0 size 9x9)`, and `command panel row on the TAB
  line`. With a Factory selected the panel shows "V Rally" on the "TAB Cancel"
  line, its right edge flush with the right edge of the scrap costs above it.
  The cap matches the stock number caps beside the unit rows: same size, white
  with notched corners, a black V that fits inside it, the same gap to its
  label and the same vertical centre. Record whether the font's V is too tall
  for the 9-unit cap at any UI scale. With a tank only, or nothing, selected
  there is no row. V turns the row label to "Cancel" without moving the key
  or the line; V again (or a confirm) turns it back to "Rally". After the row
  draws, the stock text after it keeps its colour.
- SPACE row: the log has `SPACE row reads Rally while set mode is armed`. V
  turns the SPACE row from "Go To" to "Rally"; V again or Space turns it back.
  With set mode off, other units selected show their stock SPACE labels.
  Armed, then the selection changed: SPACE shows the stock label again (set
  mode no longer applies to it). Armed with the selection unchanged, the ALT
  row reads "No Action".
- UiLocalize missing (rename the row in a test copy of patches.json): the
  SPACE row still reads "Rally" while armed, and the panel row goes
  `under the menu underlay`.
- Resolutions: check 640x480, 1024x768, 1080p, 1440p and 4K, and the
  smallest UI scale. At each the row is on the TAB line and clear of "Cancel",
  or (logged `under the menu underlay`) fully below the green underlay. Record
  which.
- Long TAB label: with a language whose "Cancel" is long (or a localization
  override), the row moves under the underlay and the log says so.
- With `CommandHudFade=1`, the cap fades with the panel like the stock caps
  (white and black both).
- With `CommandHudFade=1` the row fades and reappears with the panel; with
  it off the slot wrapper is in (log `render slot wrapper installed`) and the
  panel looks and behaves as stock. With rally off at startup the log has no
  `render slot wrapper installed` line (fade also off).
- Alternate (touch) command layout: no row.
- EXU with its command presentation on: no row.

# Auto-group new units

`[Gameplay] AutoGroupNewUnits` (default OFF; Options page Controls, row
"Auto Group"). Source: `src/patches/auto_group_new_units.cpp`, pure logic in
`include/auto_group_policy.h` (tests: `tests/auto_group_policy_tests.cpp`).
Log tag `[AUTOGROUP]`. Ported from BZCC's `SetBestGroup`
(`SetBestGroup-004da8b0.c` lines 19-26, `FirstMatchGroup-005a4e03.c` lines
14-18, `FirstEmptyGroup-005a4dd6.c` lines 14-16). Single player only
(FeatureTier::SinglePlayer). **UNVERIFIED at runtime.**

## Behaviour

When the player's Recycler or Factory finishes a unit, the unit is appended to
a stock number-key group:

1. the first keyed group (index 0-6) in which *every* live member has the
   new unit's ODF name (exact compare) and that has fewer than 10 live
   members;
2. otherwise the first keyed group with no live members (an all-dead group
   counts as empty);
3. otherwise nothing.

Only indices 0-6 are used: the stock `input.map` (GOG install, lines 159-194)
binds `group_select_0`..`group_select_6` to F1-F7, each with a
`- keyboard LeftShift` line; nothing selects 7-9. The every-member rule is
stricter than BZCC (which compares only the first member), so a mixed group
the player built by hand is never touched.

Skipped: other teams, a null unit, scavengers, constructors, pilots
(RTTI name contains `Person`), buildings (class id 2), units that cannot be
commanded, units whose ODF name cannot be read, and units already in any of
the ten groups. Dead handles are not counted and the
stored list is never compacted: stock already removes a deleted object from
every group, and stock SelectGroup skips dead handles. A group whose 91 stored
slots are used is skipped.

It consumes the rally's FinishBuild slot-42 hook (no hook of its own).
`EnsureProducerFinishBuildHook` installs that hook with its own copy of the
shared rows, so auto-group works with rally points off or unavailable; the
rally's behaviour is unchanged. Install retries up to 40 times; if a row, the
ControlPanel identity check or the hook fails, the Options row is marked
failed and rally points are unaffected.

Multiplayer: groups are local UI state and nothing is sent, so it is probably
safe, but FinishBuild may run for remote replicas and it is untested. Off in
MP for v1.

## Addresses and evidence (GOG 2.2.301)

| Fact | Evidence |
|---|---|
| ControlPanelGlobal 0x00978E20 is the ControlPanel | Only ctor call: static init 0x004054E0 (`mov ecx,0x978E20; call 0x0049F8E0`); the ctor stores vtable 0x00877E50 at 0x0049F918 (`FUN_0049f8e0` line 17); RTTI `.?AVControlPanel@@`. Checked at runtime (row `ControlPanelVtable`). |
| groupNum `+0xFC4` (int[10]), groupList `+0x18C`, 0x16C bytes (91 handles) per group | BindGroup `FUN_004a6f00` lines 7-10; SelectGroup `FUN_004a6dd0` lines 14-24. Both are called from `FUN_004a08e0` lines 530-537 (ControlPanel vtable slot 6) with `this` = ControlPanel (0x004A1D33, 0x004A1D5A). |
| Entries are handles | SelectGroup resolves each with GetObj (`FUN_004a6dd0` line 15) and copies it into selectList, which BroadcastCommand also resolves by handle. |
| Groups are saved | Mission save `FUN_005c7b90` line 118 calls `FUN_004a7440` (0x005C7E5D `mov ecx,0x978E20`), which writes `groupNum` (0x28 bytes) and `groupList` (0xE38 bytes) (lines 8-10). Load `FUN_005c7510` line 204 calls `FUN_004a73a0`; post-load `FUN_004a0160` lines 63-67 remaps the handles. |
| Dead objects leave groups | GameObject cleanup `FUN_004db780` line 14 calls `FUN_004a0710`, which removes the handle from every group (lines 27-37). |
| GameObjectClass at object `+0xF8` | `FUN_005ae660` lines 51-53 read the producer build list through `[this+0xF8]+0x608`. |
| Class id 2 = building | IsBuilding 0x006A0810 (`AI IsBuilding` row) opens with `cmp dword [class+0x1C], 2`. **UNVERIFIED** for craft: `odf_helpers.cpp` notes the `+0xF8` chain names a different class record for Craft. A misread only skips the unit (fails safe). |
| ODF name | `TryGetCraftOdfName` (`engine_flames.cpp`), GetClass vtable path, class `+0x30` char[8]; same reader for the unit and each live member. |

Decompile paths are relative to the corpus directory named above.

## Live test checklist (UNVERIFIED)

- With the setting on, a new tank from the Factory is selected by F(n+1),
  where n is the group index in the log. Whether selection is F-key alone or
  needs the LeftShift chord is not checked.
- A second tank of the same ODF joins the same group; an 11th goes to the
  next empty group; a different ODF starts its own group; a hand-made mixed
  group is left alone; nothing ever lands in groups 8-10.
- A scavenger, a constructor and a unit already bound to a group are not
  added.
- Save and load keep the group.
- The HUD group display (if any) shows the new member without a reselect.
- Nothing happens in multiplayer or with the setting off.

# Group strip

`[Gameplay] GroupStrip`, default ON, independent of `AutoGroupNewUnits`.
Code: `src/patches/group_strip.cpp`; rules and layout:
`include/group_strip_policy.h` (tests: `tests/group_strip_policy_tests.cpp`).

Stock Redux has no UI for number groups: in the decompile only init, save,
load, select and dead-unit removal touch the group arrays. The strip draws one
row next to the scrap/pilot gauge, for example
`F1 4xTank  F2 2xBomber  F3 3xTank+`:

- One entry for each of groups 0-6 (F1-F7) with at least one live member;
  dead handles are not counted. Groups 7-9 have no key and are not shown.
- The label is the first live member's ODF `unitName`, else its ODF name.
  `+` means another live member has a different class.
- Names are cut to 16, then 10, then 6 characters (`Assau.`), then left out,
  until the row fits. If even that is too wide, trailing groups are replaced
  by `...`.
- `x` instead of `×`: the HUD font's support for that character is unknown.
- Placement: on the gauge's top line, right of it, when every group fits there
  with names of at least 6 characters; else centred under the gauge. The
  strip must stay in the top third of the screen or it is not drawn. Spacing
  scales with the text height (640x480 to 4K).
- Hidden with no live group, with the pause menu or a non-gameplay shell
  screen up, without a player object, and in the shell (the snapshot is
  taken from the world render tick and is not drawn once older than 1 s).
- Multiplayer: shown. It only reads the local ControlPanel's groups and
  draws on the local HUD; nothing is written or sent.

Threads: the world render tick (`LegacyWorldUpdateRenderQueueHook`, frame and
game thread) takes a snapshot at 4 Hz: group counts, names, mixed flags and
the gauge's six live layout points. The `HudGaugeOverlay` painter
(`Slot::GroupStrip`) only copies that snapshot and calls the HUD text
measure and draw primitives. `HudGaugeOverlay::Ensure()` and the painter
are attached from that tick, which is the thread `Ensure()` requires.

## Addresses and evidence (GOG 2.2.301)

| Fact | Evidence |
|---|---|
| unitName is `char[0x20]` at GameObjectClass `+0x64` | GameObjectClass ctor `FUN_004e0450` line 89: `FUN_004cbc10(0xd3dd9cec, 0x45a8bc04, local_78 + 0x19, param_1 + 100)`; `FUN_004cbc10` passes size 0x20 to `FUN_00589a10`. The hash pair is BZ 1.5's `ParameterDB::Get(..., this->unitName, 0x20, ...)` (1.5 `all_decompiled.c` line 189463). Shipping exe 0x004E064F: `8B 55 8C 83 C2 64 52 68 04 BC A8 45` (`mov edx,[ebp-0x74]; add edx,0x64; push edx; push 0x45A8BC04`). Row `GroupStripUnitNameRead` guards those bytes; the strip stays down if they differ. |
| GameObjectClass of an object | GameObject `+0x18` sub-object, vtable[0] (the `TryGetCraftOdfName` path; its ODF at class `+0x30` matches `FUN_004e0450`'s `local_78[0xc] = param_2`). |
| Groups | ControlPanel `+0xFC4` / `+0x18C` / 0x16C stride; see "Auto-group new units" above. |
| Gauge plates | `FUN_005c6cf0` (layout): scrap plate x = `W/2 - 176s/2` (lines 20, 34), pilot plate x = `W/2` (line 39), both y = `10s/2` (lines 22, 47-48); scrap value y = plate y + `18s/2` + `10s/2` (line 38), a drop of 14s. `FUN_005c6f70` (draw) lines 50-52 and 75-77 draw each plate at `(spriteW * s / 2, spriteH * s / 2)`; with the alternate menu layout (line 72) the pilot plate follows the scrap plate instead of its own point. `scrap_panel`/`pilot_panel` are 180 x 64 in `spritea.st` (read from Campaign Reimagined's copy; the stock copy in `bzone.zfs` was not extracted). |
| Gauge rect used | From the six live `ScrapHud*Point` rows: s = (value y - plate y + 2) / 14 (never below the real scale); scrap plate reserves 180s x 32s, pilot plate 90s x 32s, each string +/-40s around its x and one text height below its y. At s = 1, 1280x720 (the stock plates span x 552-730, y 5-37) it reserves x 552-758, y 5-42. Without the rows: the stock formula with s = max(1, H/480). |

## Live test checklist (UNVERIFIED)

- The strip appears with one group bound and disappears when its last unit
  dies; counts drop as members die.
- A unit's `unitName` shows (for example "Tank" for `avtank`), not garbage;
  a hand-mixed group shows `+`.
- No overlap with the scrap/pilot plates at 640x480, 1280x720, 1920x1080 and
  3840x2160, and with `ScrapPilotHud = Legacy`. The assumed 180 x 64 plate
  size is from CR's sprite table.
- Nothing else of the stock HUD sits right of the gauge on its top line
  (objective/message text was not checked).
- Hidden in the pause menu, the shell, satellite view, cinematic cameras and
  with the HUD hidden. Satellite and cinematic views are not checked: the
  painter runs whenever the gauge draw function is called, including when
  that function skips its own drawing (`FUN_005c6f70` line 26).
- Shown in multiplayer; nothing in the session log changes.
