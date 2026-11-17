# RTS order queue (`[Gameplay] RtsOrderQueue`)

Default **off**, single player only. Source: `src/patches/rts_order_queue.cpp`, rules in
`include/rts_order_queue_policy.h`, chain drawing in `src/patches/rts_markers.cpp`.

## Behaviour

With a selection, hold the stock multi-select modifier (the game's own `cmd_multi` byte, so a
rebind is respected) and aim at something the Space or Alt button can order:

- The Space label and the Alt label read `Queue <label>` (`Queue Defend`, `Queue Go To`). The
  prefix is the localization key `openshim_ui:rts_order_queue_prefix`.
- Pressing the key does not broadcast. For each selected own commandable unit: if it is idle and
  has no queue the order is issued at once (the stock `SetCommand` wrappers); otherwise it is
  appended to that unit's queue. The stock click sound still plays; the stock `SelectNone` after
  the press is skipped so the player can chain more orders. A press without the modifier is stock
  (`SelectNone` included).
- Queueable: Go (3), Attack (4), Follow (5), Pickup (7), Dropoff (8), Get Repair (10), Get Reload
  (11), Defend (15). Never: Select (1; Shift+Space stays `SelectAdd`), No Dropoff (9), Stop (2),
  Build (21), anything else; those, and the null-target broadcasts, run stock.
- Caps: 8 entries per unit, 32 units with a queue. A press that cannot fit (any selected unit's
  queue full, or too few free unit slots) is refused for every unit: the stock `mnu_buzz.wav`
  plays, the selection is kept and `[ORDERQ] refused (full)` is logged.
- Drain: on the frame thread (`RunDeferredSceneMutations` at frameStarted, the same thread
  `rts_commands.cpp` issues its orders from; inline from the world render tick only while the
  scene-mutation drain is not installed), at most every 250 ms, for each unit with a queue that is
  idle (`RtsCommandsUnitIdle`: current and pending command records both none/select/stop), pop the
  next entry and issue it. At least 500 ms between two pops of one unit. An object entry whose
  target is gone is dropped and the next entry is tried in the same pass. Defend and Follow never
  go idle, so later entries simply wait.
- Rally keeps priority: while ProducerRallyPoints set mode is armed for the selection the SPACE
  label reads `Rally` and the press stays stock (`ProducerRallyConfirmPending`).

### Clearing a queue

| Event | Covered by |
|---|---|
| Unit dies / is gone / changes team | drain pass (`ObjectAlive`, `IsPlayerTeam`) |
| Plain order from the Space/Alt buttons | the press hooks, after the stock call |
| Any other player `BroadcastCommand` (object 0x004A7050 and ground 0x004A70C0 entry detours; OverView, submenu picks, the Defend/Nav submenus) | `NoteRtsOrderQueuePlainBroadcast` from the `rts_markers.cpp` listeners on those two detours (the ground one is skipped when rally set mode consumes the confirm, which orders nothing) |
| Unit-menu picks (`DispatchMode`), smart Defend pick, Build at Nav pick | `NoteRtsOrderQueuePlainOrder` from the `rts_commands.cpp` hooks |
| Mission load / reset | `ResetRtsOrderQueue` (feature registry revert) |
| Option turned off, or a network game | `RefreshRtsOrderQueueState` (feature registry MP gate, every 250 ms) |

Not covered (the queue then keeps running): an order given by a mission script or by Lua
(`SetCommand` from outside the listed paths), the digit-key unit menu entries that call
`ExecuteMode` while `RtsSmartCommandMenu`'s `DispatchHook` is not installed, and Stop given through
a path that does not reach one of the hooks above. Queue-issued orders do not pass through
`BroadcastCommand`, so they never clear their own queue.

### Multiplayer

Hard-gated to single player (`IsSinglePlayerSession()`); online the table is cleared and the label
and press stay stock. Nothing is sent over the network.

### Feedback

`rts_markers.cpp` draws, whenever the option is active (independent of `RtsWaypointLines`), for
each selected own unit with a queue: an amber line from where its current order ends (the unit's
position when it has none) through every queued point, one pool slot per leg (slots
`kFirstQueueLineSlot`, 48), and an amber ring on each distinct queued object target (16). Legs to
a gone object, or to an enemy the player cannot detect, are skipped. The ground-order ping of the
stock broadcast is not drawn for queued entries.

### Out of scope (v1)

- OverView (satellite) orders: not hooked (Shift there only affects `SELECT`); a plain order from
  it clears queues through the broadcast listener.
- The digit-key submenus (Defend / Attack / Go To Nav target picks, the unit menu): stock Shift
  already skips the unit branch of the digit menu; their picks are plain orders (clear).
- Other commands (Stop, Build, Hunt, Patrol, Recycle...), Select, null-target broadcasts.

## Engine facts

Addresses are the GOG Redux 2.2.301 image. "Line" cites `render_redux.c`, the Redux re-decompile of
`ControlPanel::Render` `FUN_004a08e0` (`reverse_engineering` corpus, not committed). Bytes were
read from the shipped exe and disassembled on 2026-11-17.

- SPACE press (`menu_press`, `DAT_0091988e`; lines 542-593): `cmdButton` is `{command +0x111C,
  object +0x1120, position +0x1124, colour +0x1128}`. Command 1 (Select) selects (lines 543-561);
  command 9 (No Dropoff) plays `mnu_buzz.wav` and broadcasts (lines 563-577); every other non-zero
  command plays `mnu_clik.wav` (0x004A1F34, line 579), then broadcasts and clears the selection
  (lines 580-592). Arms, verified in the bytes 0x004A1F50..0x004A1FDC: object arm
  `call 0x004A7050` at **0x004A1F7A** (`E8 D1 50 00 00`), ground arm `call 0x004A70C0` at
  **0x004A1FB0** (`E8 0B 51 00 00`), null arm `call 0x004A7050` at 0x004A1FCC (`E8 7F 50 00 00`,
  left stock), all joining at `call 0x004A6D50` (SelectNone) at **0x004A1FD7** (`E8 74 4D 00 00`).
- ALT press (`alt_press`, `DAT_0091988f`; lines 656-670): click sound 0x004A2595 (`push
  0x871B0C` "mnu_clik.wav" shape, string address not read: UNVERIFIED), object arm 0x004A25DB
  (`E8 70 4A 00 00` -> 0x004A7050), ground arm 0x004A2611 (`E8 AA 4A 00 00` -> 0x004A70C0), null
  arm 0x004A262D (`E8 1E 4A 00 00`, left stock), SelectNone 0x004A2638 (`E8 13 47 00 00` ->
  0x004A6D50).
- `BroadcastCommand(what, GameObject*)` 0x004A7050 and `(what, const VECTOR_3D*)` 0x004A70C0
  (thiscall, ret 8): loop `selectNum` (+0x188) over `selectList` (+0x1C), `GetObj` 0x004DA060,
  `CanCommand` (vtable +0x38), then `GameObject::SetCommand(what, who)` 0x004DBD60 or
  `SetCommand(what, where, int64 selectNum)` 0x004DBE70 (bytes 0x004A7079..0x004A70AE and
  0x004A70E9..0x004A712A). The queue uses the same two calls and passes `selectNum` as the ground
  param exactly as stock does.
- Labels: SPACE `call Localize 0x0081CB40` at 0x004A207C (already redirected by
  ProducerRallyPoints; the queue chains in its hook), ALT at **0x004A26C1** (`E8 7A A4 37 00`,
  lines 604 and 677). Returning a pointer to a static buffer is safe: the string is held in a
  frame local and drawn at once (lines 604-612), never freed.
- Shift: the stock Shift state is the byte `cmd_multi` at 0x00919875 (`CommandMenuUnitBranchInput`),
  the same one Render, OverView and `Reticle::Simulate` read. With a selection Shift does not change
  which command the button offers (`Reticle::Simulate` `FUN_005ba560` lines 148-174 chooses the
  reticle object with the selected leader excluded only without the modifier; `ActionMode::GetCommand`
  asks the selected unit's class virtuals, which do not read it; the per-class virtuals were not
  swept: UNVERIFIED), so Defend on an own building is reachable under Shift as without it.
- Idle: `GameObject` current command record +0xA8 and pending +0xC8, `what` at +4; idle means both
  none, select or stop (`RtsCommandsPolicy::IsIdle`; the idle-unit alert already relies on it).
  SetCommand writes the pending record immediately, so a unit just ordered reads busy at once
  (matches the alert's behaviour; no separate in-flight tracking is kept).
- Thread: `RunDeferredSceneMutations` is the Ogre frameStarted listener on the game's main thread;
  `rts_commands.cpp` already issues `SetCommand` (Hold) and `SelectAdd` from it.

## Hook sites (`scripts/patches.json`, `engine_addresses`)

| Row | Address | Verified bytes |
|---|---|---|
| `ControlPanelCmdObjBroadcastCall` | 0x004A1F7A | `E8 D1 50 00 00 EB 50 8B` |
| `ControlPanelCmdWhereBroadcastCall` | 0x004A1FB0 | `E8 0B 51 00 00 EB 1A 6A` |
| `ControlPanelCmdSelectNoneCall` | 0x004A1FD7 | `E8 74 4D 00 00 C7 85 60 FD FF FF 00` |
| `ControlPanelAltObjBroadcastCall` | 0x004A25DB | `E8 70 4A 00 00 EB 50 8B` |
| `ControlPanelAltWhereBroadcastCall` | 0x004A2611 | `E8 AA 4A 00 00 EB 1A 6A` |
| `ControlPanelAltSelectNoneCall` | 0x004A2638 | `E8 13 47 00 00 0F B6 15 67 55 91 00` |
| `CommandMenuAltLabelLocalizeCall` | 0x004A26C1 | `E8 7A A4 37 00 83 C4 08 89 85 38 FC FF FF` |

All are REL32 call redirects (`RedirectCall`), each re-reading and comparing the bytes first, and the
option is marked unavailable (`MarkOptionHookFailed`) unless every site, the SPACE label chain and
the shared `rts_commands.cpp` rows are in place. The ground sites' callee is read from the verified
rel32 (0x004A70C0) instead of an engine row: that function's entry is detoured by
ProducerRallyPoints, so a byte row there would read as a mismatch.

## Log lines (`[ORDERQ]`, budgeted, reset on mission reset)

`rows bound`, `<site>: redirected`, `install complete|gave up`, `active=<0|1> (option, hooks, single
player)` (change-only), `queued handle= cmd= depth=`, `issued handle= cmd= (idle, now|from queue)`,
`dropped handle= cmd= target= (gone)`, `cleared handle= entries= (<reason>)` / `cleared all`,
`refused (full)`.

## Live test checklist (not yet run)

1. Option on, SP mission: select a tank, give a Go, hold Shift, aim at an own building: the Space
   label reads `Queue Defend`, Space queues, the selection stays, an amber line runs from the Go
   destination to the building with a ring on it.
2. The tank reaches the Go point and starts defending (`[ORDERQ] issued ... (from queue)`).
3. A plain order, Stop through the menu, or the tank dying clears the queue.
4. Rally set mode armed with a Recycler selected: the label reads `Rally`, the press sets the rally.
5. Shift+Space on a select button still adds to the selection.
