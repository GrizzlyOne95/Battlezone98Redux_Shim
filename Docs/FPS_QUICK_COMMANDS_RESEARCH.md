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

- **Shift+letter works.** The RTS filter swallows the chord's keydown, its
  autorepeats and its keyup, so the letter's stock action does not fire
  (Shift+T leaves T's `frontal_target` alone; `Docs/RTS_COMMANDS.md`
  "Keys"). Stock binds Shift only as a menu modifier and on
  Shift+F1..F11 in `gamekey.map`; Shift+F-keys are blocked
  (`Docs/OFFENSIVE_UNIT_SLOT_CAP.md` 158).
- **Alt is out:** `alt_press` issues the reticle command on the Alt press
  itself, before any letter.
- **Ctrl is out:** `cmd_multi` (multi-select), Ctrl+B ejects (`eject`
  binds B with LeftControl), Ctrl+F1..F7 bind groups, `gamekey.map` takes
  Ctrl+A/C/E/O/P/R/S, and OpenShim's rule is that Ctrl and Alt chords are
  never taken by RTS keys.
- **Shift+letter catch.** The mnemonic letters (A, D, S, F) are movement
  and pitch keys. A pilot holding D to strafe who then presses Shift gets
  Shift+D autorepeats. The filter must act only on a fresh keydown (lParam
  bit 30 clear) and must not swallow a key whose plain keydown went to the
  game, or the strafe would stick. This needs a live check.

## Recommended v1

Native, in `rts_commands.cpp`, on the existing key path, default OFF:

| Order | Call | Default key | Fallback (numpad) |
| --- | --- | --- | --- |
| Follow Me | `SetCommandObj(5, player)` | Shift+F | Numpad 1 |
| Defend Me | `SetCommandObj(15, player)` | Shift+D | Numpad 2 |
| Attack My Target | `SetCommandObj(4, player target +0x21C)` | Shift+A | Numpad 3 |
| Stop | `SetCommand(2)` | Shift+S | Numpad 0 |

All four are rebindable under Options > Input > RTS Actions, so a player
can move them to the numpad or the grey block.

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

1. Keys: Shift+F/D/A/S (proposed; works without a numpad), the numpad, or
   no defaults (rebind only)?
2. Single player only for v1?
3. Is Attack My Target wanted, given Alt already orders on the reticle
   object? (The player's target and the reticle object differ.)
4. Defend Me as CMD_DEFEND on the player, or is Z (Hold) enough?
