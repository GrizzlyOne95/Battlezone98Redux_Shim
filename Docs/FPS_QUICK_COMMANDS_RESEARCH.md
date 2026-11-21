# FPS quick-commands: research (work queue item 8)

Research only; nothing is built. Sources: the GOG 2.2.301 decompile (private
corpus), the shipping GOG `input.map` / `gamekey.map`, and the OpenShim tree
at `595aaea72`. Claims not read from code are marked UNVERIFIED.

## The idea

In the cockpit (not satellite), one key gives a common order to the selected
units, instead of walking the number-key command menu.

## What stock already does

- **Menu path.** A digit key calls `ControlPanel::DispatchMode` 0x004A7140,
  which runs each selected unit's `ExecuteMode` (vtable +0x2C)
  (`FUN_004a7140.c` 12-24; `Docs/RTS_COMMANDS.md`). Object and ground orders
  end in `BroadcastCommand` 0x004A7050 (object) / 0x004A70C0 (point), which
  call `GameObject::SetCommand` 0x004DBD60 / 0x004DBE70 per selected unit
  (`FUN_004a70c0.c` 9-13; `Docs/RTS_ORDER_QUEUE.md`).
- **Command ids** (`Docs/RTS_ORDER_QUEUE.md` lines 17-18): Stop 2, Go 3,
  Attack 4, Follow 5, Pickup 7, Dropoff 8, Get Repair 10, Get Reload 11,
  Defend 15. Attack, Follow and Defend take an object; Go takes a point.
- **One-key reticle orders already exist.** Space (`menu_press`, "Reticle
  Command") issues the highlighted command at the reticle, and Alt
  (`alt_press`) does the same for the object under the reticle
  (`FUN_004a08e0.c` 542-593; `Docs/PRODUCER_RALLY_POINTS.md` line 34; `Docs/RTS_ORDER_QUEUE.md` line 87). So
  "go where I'm aiming" is already one key after selecting a group.
- **Today's key counts in the cockpit:** group (F1-F7) + Follow Me (mode 2,
  `include/rts_commands_policy.h` 40) is 2 keys. Defend / Attack open a
  target submenu: about 3 keys plus a reticle pick.

## What OpenShim already has to build on

All in `src/patches/rts_commands.cpp`:

- Key capture: `FilterKeyMessage` (WndProc subclass + `PeekMessageA` hook)
  sets a flag; the action runs at frameStarted. Gated on
  `WorldInteractive()`, not in the editor or a text field. Rebindable rows
  under Options > Input > RTS Actions.
- Order helpers: `SafeSetCommand` (line 422), `SafeSetCommandObj`
  (line 407); `HoldSelection()` is the template loop (selection, own team,
  `CanCommand`, unit takes the mode, then set the command). Hold is gated
  single-player by `IsSinglePlayerSession()` (call in `HoldAvailableNow`, line 1014).
- The player's own target: `GameObject +0x21C` (`ObjectLayout::kGameObjectTargetHandle`, `include/bzr_object_layout.h` 88; read in `DoRemoteTarget`, `rts_commands.cpp` 1176).
- No new engine addresses are needed.

## Lua alternative

The mission callback `GameKey(key)` (`Docs/BZR_LUA_AGENT_REFERENCE.md`
line 490) plus `SelectedObjects()`, `GetTarget`, `Follow`, `Defend`,
`Attack`, `Stop` could do it in CR's Lua. Against it: it only works in
missions that load the script, has no Options rebind row, Lua `SetCommand`
applies on a later AI tick with no ping or order-queue clearing
(`Docs/NATIVE_HOLD_DEFEND_FOLLOW.md`), and whether `GameKey` fires for keys
`input.map` binds is UNVERIFIED. Native is the better fit for a general
feature.

## Free keys (checked in the shipping GOG maps, 2026-11-18)

- **Bound in the cockpit:** every digit, F1-F12 (F8-F12 are weapon slots,
  so F11/F12 are **not** free), A-H, K, L, N, P-T, W, Space, Tab, Alt,
  Insert, KeypadEnter, the grey arrows, GreyPlus/Minus, GreyInsert, Alt,
  GreyDelete. `gamekey.map` adds I, M, O, R, U, Y, punctuation and several
  Ctrl/Alt/Shift+F chords.
- **Taken by OpenShim:** X, Z, J, B, Shift+T, Shift+X, Shift+J
  (`Docs/RTS_COMMANDS.md`), V and Shift+V (rally,
  `Docs/PRODUCER_RALLY_POINTS.md` 45-51), Ctrl+Home / Ctrl+End
  (QuickSave, `openshim.ini` `[QuickSave]`).
- **Free single keys:** the numpad digits, and the grey Home / End / PgUp /
  PgDn block (laptops often lack both).

### Modifier chords

- **Shift+letter does not hide the stock action.** The game reads its
  `input.map` keys through OIS/DirectInput: `OIS.dll` imports `DINPUT8`
  and `DirectInput8Create` and has `Win32Keyboard`, and the exe adds raw
  input (`RegisterRawInputDevices`). DirectInput does not see window
  messages, so the RTS filter swallowing `WM_KEYDOWN` cannot stop a stock
  bind. The `input.map` blocks decide: `strafe_left` (A), `strafe_right`
  (D), `throttle_down` (S), `pitch_down` (F) and `frontal_target` (T)
  exclude only `EditMode`/`ControlMode`, not `LeftShift`. Shift+D therefore
  gives the order and also strafes for as long as D is down. Only blocks
  with `- keyboard LeftShift` (the `group_select_N` keys, `eject`) ignore
  Shift. (`Docs/RTS_COMMANDS.md` says Shift+T keeps stock T from running;
  by the same reasoning that is likely wrong. It is UNVERIFIED live.)
- **Alt is out:** `alt_press` issues the reticle command on the Alt press
  itself, before any letter.
- **Ctrl is out:** `cmd_multi` (multi-select), Ctrl+B ejects (`eject`
  binds B with LeftControl), Ctrl+F1..F7 bind groups, `gamekey.map` takes
  Ctrl+A/C/E/O/P/R/S, and OpenShim's rule is that Ctrl and Alt chords are
  never taken by RTS keys.
- **Usable chords.** A Shift chord is clean only on a letter with no stock
  in-play bind. Those are J, X and Z, and OpenShim already uses them plain.
  Shift+Z is free; Shift+J and Shift+X are taken. The key latch already
  acts only on a fresh keydown (lParam bit 30), so a held movement key
  never fires an order.

## Recommended v1

Native, in `rts_commands.cpp`, on the existing key path, default OFF:

| Order | Call | Default key |
| --- | --- | --- |
| Follow Me | `SetCommandObj(5, player)` | Numpad 1 |
| Defend Me | `SetCommandObj(15, player)` | Numpad 2 |
| Attack My Target | `SetCommandObj(4, player target +0x21C)` | Numpad 3 |
| Stop | `SetCommand(2)` | Numpad 0 |

The numpad has no stock bind at all, so nothing else fires. All four are
rebindable under Options > Input > RTS Actions (grey Home/End/PgUp/PgDn
for laptops). Shift+F/D/A/S was proposed first and dropped: see
"Modifier chords".

- Applies to the current selection (F1-F7 first), so each order is 2 keys.
  The selection is kept, as Hold does.
- Each unit is filtered as `HoldSelection` does (own team, `CanCommand`,
  the unit's ModeList has the mode); empty selection or no target plays
  the stock buzz.
- Calls the existing order-queue clear and command-ping notify, so pings
  and queues behave as for menu orders.
- Single player first (like Hold); multiplayer after a host + client live
  test of `SetCommand` on owned units (0x004DBE70 forwards only replicas,
  `FUN_004dbe70.c` 40-42, so locally owned units should need no packet,
  UNVERIFIED live).
- Size: about 150-250 lines plus policy-header key ids, host tests, Options
  and localisation rows.

Not in v1: "go to aim" (Space does it), whole-group variants, a radial menu.

## Open questions for the user

1. Keys: the numpad (proposed), the grey Home/End/PgUp/PgDn block, or
   Shift+F/D/A/S, accepting that the stock strafe, throttle or pitch also
   moves the ship while the key is down?
2. Single player only for v1?
3. Is Attack My Target wanted, given Alt already orders on the reticle
   object? (The player's target and the reticle object differ.)
4. Defend Me as CMD_DEFEND on the player, or is Z (Hold) enough?
