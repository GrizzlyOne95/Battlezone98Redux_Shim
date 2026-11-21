# Stock Battlezone 98 Redux key bindings

Date: 2026-11-20
Purpose: find free keys for OpenShim and EXU feature work. A key listed as free below has no stock binding in either game file, is not on the 1998 card, and was not found as a hotkey in OpenShim `src/` or `Docs/`.

## Sources

1. **1998 retail keyboard reference card.** Transcribed by the user. Cited below as "card".
2. **Game files, read only.** The stock dump at `C:\Users\iestu\Documents\BZR_moved_out_20261112\StockODFFiles` contains no `input.map` or `gamekey.map`, and its zip has none either. The files were read from the Steam install instead:
   - `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\input.map` (572 lines, mtime 2026-10-24). Cited as `input.map:N`.
   - `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\gamekey.map` (58 lines, header "BattleZone 98 Redux Keyboard Mapping File"). Cited as `gamekey.map:N`. This is the Redux key file for the non-control actions (views, pause, chat, debug, save), so it covers most card rows that `input.map` does not.
   - `temp.map` is a second copy of `input.map` with one difference (see "Redux differences"). `inputmbl.map` (566 lines) was not diffed line by line.
3. **OpenShim source and docs** (`C:\Users\iestu\Documents\GIT\BZR-OpenShim\src` and `Docs`), searched for existing hotkeys. Cited where used.

**Caveats**
- No pristine copy of the game files exists in the dump, so I cannot prove the install files are unmodified. Both files are dated 2026-10-24, the same day as `openshim.ini.bak-20261024-*` in the install.
- `input.map` uses `+` and `-` lines (for example `+ keyboard`, `- program EditMode`). The file does not document what `-` means. I report the lines as written and have not assumed the semantics.
- Stock keys with no `LeftShift` exclusion (for example `strafe_right` on D, `frontal_target` on T) may also fire when Shift is held, depending on how the engine matches modifiers. Modifier combinations below are therefore only free when the base key has no binding or has an explicit exclusion.

## Card vs game files

| Key | Card action | input.map action name and file:line | Match |
|---|---|---|---|
| Esc | Game options menu | `MAIN_MENU` gamekey.map:27 | yes (game calls it main menu) |
| Pause | Pause game | `PAUSE_GAME` gamekey.map:25 | yes |
| F1-F7 | Quick keys (select group) | `group_select_0..6` input.map:161-194 (F1 at :162 ... F7 at :192), each with `- keyboard LeftShift` | yes |
| Ctrl+F1-F7 | Assign selected units to quick key | none in input.map or gamekey.map. OpenShim docs say `BindGroup` in code (`Docs/OFFENSIVE_UNIT_SLOT_CAP.md:154`) | yes: the `cmd_multi` (Control) modifier plus the group key, handled in code, not a separate map line |
| F8-F12 | Select weapon hardpoint | `weapon_select_0..4` input.map:313-336 (F8 at :314 ... F12 at :334), each with `- keyboard LeftShift` | yes |
| Ctrl+F8..F12 | Group weapon hardpoints (card prints "F1") | none found in either file or OpenShim docs | missing (card typo likely F12) |
| 1-0 | Active command interface menus | `mode_select_0..9` input.map:68-106 (Zero at :69, One at :73, ... Nine at :105) | yes |
| Tab | Cancel selected command menu | `menu_back` input.map:139-142 (Tab at :140) | yes |
| - | Zoom (card: "-" / "+" zoom in/out) | `zoom_factor_minus` input.map:415-421 (GreyMinus :416, Minus :420) | yes (keys match; zoom direction not stated in file) |
| + | Zoom | `zoom_factor_plus` input.map:406-412 (GreyPlus :407, Equal :411) | yes (keys match; direction not stated in file) |
| I | Get info on object under reticle | `TOGGLE_INFO_DISPLAY` gamekey.map:52. Note input.map:502 binds I to `edit_eyedropper` in EditMode only | yes (card's "verify" resolved) |
| O | Review mission objectives | `TOGGLE_OBJECTIVES_DISPLAY` gamekey.map:53 | yes |
| P | Drop nav beacon | `drop_beacon` input.map:373-376 (P at :374) | yes |
| Q | Forward (slow) | `throttle_up` input.map:204-207 (Q at :205) | yes |
| W | Forward | `turbo` input.map:198-201 (W at :199, labelled "DIGITAL THROTTLE TURBO") | differs (card: forward; file: turbo) |
| E | Jump | `jump` input.map:268-272 (E at :269, excludes LeftControl at :270) | yes |
| R | Repeat radio transmission | `REPEAT_AUDIO` gamekey.map:54. Also `center_recycler` input.map:60-64 (R at :61, ControlMode) | differs (R bound twice; card matches gamekey only) |
| T | Target enemy on/off; turn off nav beacon | `frontal_target` input.map:367-370 (T at :368). Nav-beacon-off binding not in either file | yes (partial) |
| Caps Lock | Toggle radar/map | `RADAR_TOGGLE` gamekey.map:35 | yes |
| A | Strafe left | `strafe_left` input.map:262-265 (A at :263) | yes |
| S | Stop and back | `throttle_down` input.map:209-213 (S at :211) | yes |
| D | Strafe right | `strafe_right` input.map:256-259 (D at :257) | yes |
| F | Pitch up | `pitch_down` input.map:249-252 (F at :250) | differs (card: F up; file: F is pitch down) |
| C | Pitch down | `pitch_up` input.map:243-246 (C at :244). C is also `center_player` at :54 | differs (card: C down; file: C is pitch up) |
| H | Hop out | `abandon` input.map:348-351 (H at :349) | yes |
| K | Deploy/pack up deployable vehicles | `deploy` input.map:359-363 (K at :361) | yes |
| N | Select next nav beacon | `cycle_beacon` input.map:379-382 (N at :380) | yes |
| M | Multiplayer info | `SCORE_TOGGLE` gamekey.map:34 (card says multiplayer info; file calls it score toggle) | yes (name differs) |
| Shift (hold) | Mouse control of menu | `menu_pos` input.map:109-113 (mouse VertVel :110, LeftShift :111); `menu_cycle` input.map:144-147 | yes |
| Space | Smart reticle command | `menu_press` input.map:150-152 (Space at :151) | yes |
| Alt | Smart reticle command on selected target | `alt_press` input.map:155-157 (Alt at :156) | yes |
| Ctrl | Select multiple units | `cmd_multi` input.map:47-50 (Control at :48) | yes |
| Ctrl+B | Bail out of vehicle | `eject` input.map:340-345 (B at :341, LeftControl at :342) | yes (file name is "eject") |
| Ctrl+C | Chat in multiplayer | `CHAT_SENDTOALL` gamekey.map:33 | yes |
| Shift+F1 | Cockpit and HUD view | `COCKPIT_VIEW` gamekey.map:10 | yes |
| Shift+F2 | HUD only | `NO_COCKPIT_VIEW` gamekey.map:11 | yes |
| Shift+F3 | Over vehicle | `FRONT_VIEW` gamekey.map:12 | yes |
| Shift+F4 | External camera | `TRACK_VIEW` gamekey.map:13 | yes |
| Shift+F5 | No HUD or cockpit | `NO_HUD_VIEW` gamekey.map:14 | yes |
| Alt+X | Exit mission | `EXIT_SIM_QUIT` gamekey.map:26 | yes |
| Arrow keys | External camera controls | `track_pitch_plus/minus` and `track_yaw_plus/minus` are on the grey (keypad) arrows: input.map:386-403 (GreyUp :387, GreyDown :392, GreyRight :397, GreyLeft :402). Plain arrows are steering: `steer_right` :223-226, `steer_left` :229-232 | differs (card: arrows; file: grey arrows for camera, plain arrows for steering) |

Result: 35 yes, 5 differs, 1 missing (41 card rows).

## Redux differences

Bindings in the game files that are not on the card, or that differ from it.

**Changed or conflicting with the card**
- W is `turbo` (input.map:199), not forward. In `temp.map`, the same action is on `Period` (see below).
- F and C are swapped for pitch. File: C = pitch up (input.map:244), F = pitch down (input.map:250). Card: F up, C down.
- R is bound twice: `REPEAT_AUDIO` (gamekey.map:54) and `center_recycler` (input.map:61, ControlMode). Both are stock.
- C is bound twice: `pitch_up` (input.map:244) and `center_player` (input.map:54, ControlMode).
- Arrow keys are split: grey arrows control the external camera (input.map:387-402). Plain arrows steer (input.map:224, :230).
- Ctrl+F8-F12 (group hardpoints) is on the card but in neither file. Ctrl+F1-F7 (assign) works through the `cmd_multi` modifier in code (`Docs/OFFENSIVE_UNIT_SLOT_CAP.md:154`).

**In input.map, not on the card**
- Mouse: `cmd_x`/`cmd_y` (input.map:5-14), left and right click and hold (:17-38), `menu_next`/`menu_back` on mouse (:127-137), `weapon_fire` on LeftBtn (:276-280), `weapon_cycle` on RightBtn (:288-292), `weapon_special` on MiddleBtn (:306-310).
- `weapon_fire` on Insert (input.map:282-285).
- `weapon_cycle` on KeypadEnter (input.map:294-297).
- `weapon_link` on L (input.map:300-303).
- `cloak` on G (input.map:354-357).
- `cmd_delete` on GreyDelete (input.map:41-44).
- `zoom_factor_reset` on GreyInsert (input.map:424-426).
- `throttle` analog `steer` (input.map:217-220) and `pitch` analog on VertPos (input.map:236-240, with `- keyboard Tab` at :239).
- The whole EditMode block, input.map:430-567 (terrain editor keys: E, R, V, H, P, S, C, D, A, W, Tab, Ctrl+C/V/Z, arrows, I). Several share keys with control-mode actions (for example R, H, P, C, W, Tab, I).

**In gamekey.map, not on the card**
- Views: Shift+F9 `TWO_D_VIEW` (:15), Shift+F10 `OVER_VIEW` (:16), Shift+F11 `FREE_EYE_VIEW` (:18).
- `TOGGLE_OVERVIEW` on Backspace (:19), `TOGGLE_ARCADE_MODE` Ctrl+A (:21), `SAVE_SCREEN` Ctrl+P (:22), `PAUSE_GAME` Alt+P (:24), `SAVE_GAME` Ctrl+S (:28), `LOAD_GAME` Ctrl+O (:29).
- Chat: Enter (:31) and backtick (:32).
- `TOGGLE_FRAMERATE` Alt+F (:37), `TOGGLE_NETDEBUG` Alt+N (:38), `MONO_DEBUG_*` on Ctrl+/ and `.` `,` `'` `;` (:39-43), `ADVANCE_VAR` `\`, `INC_VAR` `]`, `DEC_VAR` `[` (:45-47).
- `TOGGLE_EDITMODE` Ctrl+E (:49), `TOGGLE_FPS` Ctrl+R (:50).
- `ALLIE_TOGGLE` Ctrl+[ (:56), `UNALLIE_TOGGLE` Ctrl+] (:57), `ALLIE_TOGGLE` Y (:58), `UNALLIE_TOGGLE` U (:59).

**temp.map** (same directory) matches input.map line for line except `turbo` (binding line about 163), which is `Period` instead of `W`. Its origin is unknown.

## Keys free in stock

"Free" means no binding in input.map, gamekey.map, or the card. Keys bound only in EditMode are treated as taken.

**Taken by OpenShim (found in src or Docs)**
- Shift+V, Shift+T, Shift+X, Shift+J, Shift+number, Shift+Defend, Shift+Space: RTS commands (`Docs/RTS_COMMANDS.md:10-14`, `Docs/RTS_ORDER_QUEUE.md:104`).
- Shift+Alt and Ctrl+Space: `Docs/RTS_ORDER_QUEUE.md:105`, `:164`.
- Ctrl+1, Ctrl+Offense: `Docs/RTS_COMMANDS.md:57`, `Docs/OFFENSIVE_UNIT_SLOT_CAP.md:155`.
- Ctrl+Home and Ctrl+End: autosave (`src/patches/autosave.cpp:1011`, `Docs/autosave.md:100-101`).
- Ctrl+R FPS counter: `Docs/CONTEXTUAL_HUD.md:403`, and stock (gamekey.map:50).
- Ctrl+V and Shift+Insert: `Docs/PRODUCER_RALLY_POINTS.md:304`, `:376`.
- Ctrl+F5 and Ctrl+F9 quicksave: `Docs/PRODUCER_RALLY_POINTS.md:257` (stock behaviour, not in gamekey.map).
- Ctrl+F11 and Shift+F11 free camera: stock, `src/patches/mp_block_freecam.cpp:4`, `src/patches/bzr_options_registry.inc:1015`.
- Shift+C: no hotkey found. The only "FollowCamera" hits are `TerrainProxyFollowCamera` config keys (`src/patches/terrain_proxy.cpp:908`). Shift+C is free in both the game files and OpenShim, but see caveat.

**Candidate free keys**
- Bare letters: J, X, Z. Z is also `edit_undo` (input.map:470-472) in EditMode, and Alt+X is stock exit.
- Bare keys: Home, End, Page Up, Page Down, Delete (main block). Not referenced in either file. Key names for these are unverified.
- Numeric keypad: digits and GreyHome, GreyEnd, GreyPageUp, GreyPageDown. Not referenced in either file. Key names are unverified. Keypad digits may share physical keys with the grey arrows when NumLock is off.
- Print Screen, Scroll Lock, Num Lock, `/` bare (Ctrl+/ is taken by `MONO_DEBUG_TOGGLE`, gamekey.map:39).
- Shift+F6, Shift+F7, Shift+F8, Shift+F12. The F-key groups and weapon selects carry `- keyboard LeftShift` exclusions (input.map:163, :315, :335), so Shift+F6-F8 and F12 are not claimed by stock input. Shift+F9-F11 are taken (gamekey.map:15-18).
- Shift+letter: no exclusions on letter bindings, so Shift+letter may still trigger the base action. Shift+C is the only one checked, and it is free as noted above. Verify the engine's modifier matching before using Shift+letter.

**Not free**
- Any Alt+letter: `alt_press` on Alt (input.map:155-157) has no exclusions. Alt+X and Alt+F4 are taken by exit and Windows.
- Any Ctrl+letter with a bare base binding: the same no-exclusion caveat applies. Ctrl+A, Ctrl+B, Ctrl+C, Ctrl+E, Ctrl+O, Ctrl+P, Ctrl+R, Ctrl+S, Ctrl+[, Ctrl+] are taken by stock.
