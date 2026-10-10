# CR co-op: stock network message suppression

Research date: 2026-10-07. Research and design only; no implementation or game launch.

## Recommendation

Use a **default-off, mission-scoped OpenShim presentation policy**, exposed through a thin EXU Lua binding and explicitly enabled by CR on **every co-op client**. Preserve all Lua `DisplayMessage` calls and all player chat. Suppress messages by their **native source**, not by English text, team number, color, or a `[CO-OP]` prefix allowlist.

The smallest identified native implementation needs two interception points:

1. The stock formatted system-message function at GOG VA `0x0056FCB0`, with an explicit exemption for the stock Lua `DisplayMessage` caller and a catalog of qualified stock callers.
2. The stock notification broadcaster at `0x00572DA0`, limited to its qualified alliance/CTF announcement callers. Ordinary public chat uses the same packet type through a different producer, so filtering that packet type at receive time would break chat.

If “alliance prompts” also includes the **team-number input box**, that is a separate UI path at `0x0046CD10`. Neither of the two message hooks hides that box. CR can use its existing fixed-alliance policy plus a correctly timed `LockAllies(true)`, or request a separate scoped prompt suppression option. Do not silently change alliance gameplay just to hide an announcement.

This recommendation follows repository ownership: OpenShim owns low-level hooks and patch policy; EXU owns the reusable Lua/native API and Lua-state lifetime; CR owns activation and campaign behavior. An EXU-only implementation is technically plausible and has fewer integration files, but should not duplicate OpenShim's ownership of these hooks.

## Evidence and limits

**Verified here** means read from the named source file, CSV, or the installed released executable using PE parsing and x86 disassembly. **Inference/design** means a proposed behavior or an interpretation that still needs runtime confirmation. No live argument traces, screenshots, two-client tests, or Steam/Wine/Proton qualification were performed.

The user-reported unwanted lines are the runtime observation motivating this investigation. The lists below are a complete grouped inventory of the **direct callers found for the identified system-message function and notification broadcaster**, plus related localized/UI strings. They are not a claim that every conditional multiplayer line appears during `misn03`, or that every possible indirect/UI path has been runtime enumerated.

Addresses are preferred-image **VAs**, not file offsets or RVAs. For the examined image, subtract `0x00400000` to obtain the RVA. Semantic names such as “system-message formatter” below describe the verified instructions; they are not claimed PDB symbol names. No private PDB or decompiler corpus was used or copied.

### Source identities

| Source | Identity at inspection |
|---|---|
| OpenShim checkout | `C:\Users\iestu\Documents\GIT\BZR-OpenShim-coopflow`; origin `https://github.com/GrizzlyOne95/Battlezone98Redux_Shim.git`; branch `agent/coop-mission-flow`; HEAD `7b7d6ef4e321e0abb86f14db065ff9f4100c449e` |
| EXU checkout | `C:\Users\iestu\Documents\GIT\ExtraUtilities`; origin `https://github.com/GrizzlyOne95/ExtraUtilities`; branch `agent/coop-comms-pings`; HEAD `19165e8b7ab0ef56364b4cc54933751a6104d3dc` |
| CR checkout | `C:\Users\iestu\Documents\GIT\Campaign-Reimagined`; origin `https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined.git`; branch `agent/coop-comms-pings`; HEAD `c223077425a89159dd4a2c601c6bdc50e43662f5` |
| Released executable | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe`; PE version `2.2.301`; 5,425,152 bytes; image base `0x00400000`; PE timestamp `0x58D9D6CC`; SHA-256 `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413` |
| Localization table | Same install, `localization_table.csv`; 111,216 bytes; SHA-256 `6ff8c44448a53b09dbe949448c7f114537438cef2fff090ca62a97ad2f1b35b3` |

The checkouts contain other agents' work and were read as working trees, not assumed to be clean snapshots. Changes observed during inspection were left alone. Read-only Git queries used command-local `safe.directory` overrides for the sibling checkouts; no Git configuration, branch, index, or history was changed.

Methods: `rg` searches and file reads; `python -B -` scripts supplied on stdin using `pefile` and `capstone`; executable/string-table hashing; `.text` relative-call and tail-jump searches followed by disassembly of the relevant sites. No analysis project, extraction output, or scratch script was written. The only research artifact written is this file.

## 1. Where the messages come from

### The shared message-line path

**Verified:** stock Lua and native multiplayer notices converge on the same control:

```text
Lua DisplayMessage(text)
  registration pair at 0x00872220
    name string 0x0087CD40 -> Lua C binding 0x00505350
  call 0x00505369 -> formatted system-message function 0x0056FCB0
    safe "%s" format at 0x00879854; return address 0x0050536E
  vsnprintf-style formatting into a 0x400-byte local buffer
  call 0x0056FCFF -> message router 0x00624550(sender = 0, text)
  system branch -> append 0x00821390 -> common append 0x00821450
    control pointer in global 0x00920168

Native kill/snipe/eject/building notice formatter 0x00626130
  -> 0x0056FCB0 -> the identical sender-zero route/control

Received public chat
  receive-dispatch call 0x005710DD -> 0x00624550(actual player ID, text)
  player branch -> common append 0x00821450, same control 0x00920168
```

The router's player branch performs mute checks and selects player-message colors; the sender-zero branch uses the system-message setting. Both also forward to `0x007A47B0`. That second function logs `Chat Message: %s\n` (string `0x0089F004`) and stores chat history. It is not the sole HUD append point.

The control is created by the initialization code around `0x006242E4` and stored at `0x00920168`. Its common append routine maintains a text-line buffer. This establishes that these are message-line/chat-window messages, not the mission objective panel. `Docs/BZR_LUA_AGENT_REFERENCE.md:382,410` independently identifies `DisplayMessage` as local chat-window output.

CR uses that native path: `Scripts/CRCoopComms.lua:33-34` prefixes notices with `[CO-OP] ` and calls its injected message function; `Scripts/CRCoop.lua:188` supplies `DisplayMessage(text)`. `PersistentConfig.lua` also emits `[CO-OP]` feedback. CR's `misn03.lua:996,1011` has unprefixed admission/rejoin warnings that should remain visible too.

### “Team 5's ship destroyed” is assembled, not one localized format

**Verified:** `0x00626130` accepts killed team, killer team, a one-byte event discriminator, and a pilot-related flag. It resolves a human team to its player name via the team/player table at `0x009180E8`. If the team has no player entry, it uses:

- `Localize("multi_three", "team")` at calls `0x006261AB` / `0x0062624C`; key strings `0x0088D7B4` / `0x008757B0`.
- Format `%s %d` at `0x0088D7AC` to create `Team 5` in English.
- Localized event fragments, formatted through `%s%s` (`0x0088D944`), `%s%s %s` (`0x0088D94C`), or `%s%s %s %s` (`0x0088D7A0`).

Thus `Team 5` + `multi_message:ship_destroyed` yields the reported line. There is no verified single localization key containing `Team %d's ship destroyed`. AI teams can reach this path; restricting suppression to human victims would miss the motivating problem.

The event branches compare `'P'` (pilot killed), `'B'` (building), `'S'` (snipe), and `'E'` (ejection); the remaining branch formats ship destruction. The pilot-related flag selects whether to include `s_pilot`. Killer team greater than zero selects an attributed variant.

The local producer `0x00626470` constructs a `0x4B4D` notification word (little-endian bytes `MK`), calls the formatter at `0x00626506`, then sends the six-byte notification at `0x0062651B`. The receive dispatcher at `0x00570500` recognizes that word and calls the same formatter at `0x00570E44`. Direct callers of the producer occur at `0x0047F310`, `0x004AAE7B`, `0x004ABDE1`, `0x00573B96`, and `0x005A0FCB`.

**Design implication:** suppress the presentation call, not the kill packet, death simulation, or score updates. The examined `0x00626130` body resolves names and emits text; `0x00626470` also sends network traffic and must continue executing.

### Localization loading

**Verified:** the table is a loose file in the install root, with header:

`Key~English~French~German~Spanish~Italian~Russian~Portuguese`

IDs are textual `section:key` values. `0x0081CB40` is the section/key lookup function, using the localization map at `0x0260C1B8`. The loader at `0x0081C650` references `localization_table.csv` at `0x008A1E38`; it also has a platform-dependent `localization_table_mbl.csv` alternative at `0x008A1E1C`. The multiplayer text initializer around `0x006269xx` caches localized fragment pointers in globals.

**Unverified:** whether a CR-local replacement CSV overrides that loose root file, precisely when the table reloads, and how empty CSV cells behave. No mod precedence or empty-string experiment was run. Do not assume a per-mission CSV replacement works.

### Stock kill/death-related fragment inventory

All CSV line numbers below refer to the examined root table. The “key address” is the executable string passed to localization; the cached pointer is a runtime data slot, not the address of the translated text.

| Localization ID | English fragment | CSV line | Key VA / cached pointer slot |
|---|---|---:|---|
| `multi_three:team` | `Team` | 133 | `0x008757B0` (section `0x0088D7B4`) |
| `multi_message:ejected` | ` ejected` | 72 | `0x0088D888` / `0x008EC730` |
| `multi_message:ship_destroyed_by` | `'s ship destroyed by ` | 73 | `0x0088D8E0` / `0x008EC73C` |
| `multi_message:pilot_destroyed_by` | `'s pilot destroyed by ` | 74 | `0x0088D8CC` / `0x008EC740` |
| `multi_message:killed` | ` killed ` | 75 | `0x0088D834` / `0x008EC734` |
| `multi_message:killed_by` | ` killed by ` | 76 | `0x0088D828` / `0x008EC790` |
| `multi_message:ship_destroyed` | `'s ship destroyed` | 78 | `0x0088D8A4` / `0x008EC738` |
| `multi_message:s_pilot` | `'s pilot ` | 82 | `0x0088D990` / `0x008EC754` |
| `multi_message:sniped` | ` sniped ` | 83 | `0x0088D7CC` / `0x008EC770` |
| `multi_message:sniped_by` | `Sniped by ` | 84 | `0x0088D984` / `0x008EC728` |
| `multi_message:building_destroyed_by` | `'s building destroyed by` | 102 | `0x0088D8B4` / `0x008EC780` |
| `multi_message:building_destroyed` | `'s building destroyed` | 103 | `0x0088D890` / `0x008EC72C` |

`pilot_destroyed_by` is loaded into a cache slot, but the examined pilot branch uses `s_pilot` plus `killed`/`killed_by` instead. Treat presence in the table as distinct from verified use by this formatter. Case, spacing, and translation grammar are engine/table behavior; avoid reconstructing these strings in a filter.

The formatter's nine calls to `0x0056FCB0` are `0x006262C5`, `0x006262FA`, `0x0062633F`, `0x0062636D`, `0x006263B8`, `0x006263ED`, `0x00626410`, `0x00626434`, `0x0062644E`.

### Other stock network-game output: complete direct-call inventory

The `.text` search found **49 direct calls** to `0x0056FCB0`: one Lua caller, nine calls in the kill formatter above, and the 39 calls grouped below. No direct tail jump to it was found. “Possible in co-op” is conditional: connection faults, departure, and native multiplayer limits can expose paths that normal campaign play does not exercise.

| Category / text or ID | Producer function VA | Calls to `0x0056FCB0` | Evidence / scope |
|---|---|---|---|
| Spawn failures: `multi_error:no_spawn_avail`, `no_spawn_points` | `0x0056C320`, `0x0056ECE0` | `0x0056C4AE`, `0x0056C4DE`, `0x0056EE13`, `0x0056EE43` | CSV 312 / 311; map/start/respawn errors |
| Four CTF flag-loss announcements | `0x0056D9E0` | `0x0056DD2A`, `0x0056DD92`, `0x0056DDFA`, `0x0056DE62` | Keys `team_1_flag_1`, `team_1_flag_2`, `team_2_flag_1`, `team_2_flag_2`, key VAs `0x008838C0`, `0x008838D8`, `0x00883908`, `0x008838F8`; CTF-only logic |
| `Time Has Run Out` | `0x0056D9E0` | `0x0056DECA` | Literal `0x00883974`; stock mode/time limit |
| `Team 2 has lost its flags, Score 1 for team 1`; inverse | `0x0056D9E0` | `0x0056DF48`, `0x0056DFD2` | Literals `0x00883944`, `0x00883990`; CTF score/result announcements |
| `%s MAY BE CHEATING`; unknown-player variant | Receive dispatcher `0x00570500` | `0x00570F01`, `0x00570F10` | Literals `0x00883E60`, `0x00883E44` |
| `multi_message:host_kicked`, `host_autokicked` | Receive dispatcher `0x00570500` | `0x005713BB`, `0x005714A6` | CSV 104 / 105; key VAs `0x00883EA4`, `0x00883E94` |
| `multi_message:locked`, `unlocked` | Receive dispatcher `0x00570500` | `0x00571525`, `0x00571564` | CSV 97 / 98; key VAs `0x00883EBC`, `0x00883EB0` |
| Ping diagnostic lines | `0x00571E20` | `0x00571EA3`, `0x0057234B` | Format VAs `0x00883D50`, `0x00883FA8`; `PONG RECEIVED` diagnostics, not normal campaign notices |
| Bandwidth diagnostic | `0x005732D0` | `0x00573776` | `Bandwidth = %lu, used rate = %lu`, literal `0x00884194`; debug-gated |
| `%s` + `multi_message:defeated` | `0x00574CB0` | `0x00574F48` | CSV 77; key `0x00884834`, format `%s %s` at `0x00884840` |
| `multi_message:autokick` + player name | `0x00576A70` | `0x00576B24` | CSV 88; key `0x00884720` |
| `multi_message:start_lagging`, `stop_lagging` | `0x00576B70` | `0x00576CF9`, `0x00576DB6` | CSV 86 / 87; keys `0x0088472C`, `0x008846F8`; `%s is lagging` / `%s stopped lagging` |
| `multi_message:player_joined` | `0x00578500` | `0x00578567` | CSV 80; key `0x0088491C`; format `%s: %s (%ld,%d)` at `0x008849B8` |
| `multi_error:player_kick`; `multi_message:host_autokicked`, `player_left` | `0x00578640` | `0x00578699`, `0x005786FB`, `0x00578739` | CSV 300 / 105 / 81; keys `0x008849C8`, `0x00883E94`, `0x00884944`; leave uses same join/leave format |
| `multi_message:host` | `0x00578760`, `0x005788E0` | `0x0057884F`, `0x00578926` | CSV 85, `You have been elected host`; key `0x00884A48`; latter format `%s: %s => %s` at `0x00884A38` |
| Ordnance timing diagnostics | `0x00584620` | `0x00584748`, `0x00584AE1` | `Now = %f Ordnance = %f`, `Future ordnance = %f`; literals `0x00884DC4`, `0x00884DDC`; debug-gated |
| `multi_error:version_mismatch`, `no_net_response`, `fail_join_game` | `0x00617110` | `0x006171D4`, `0x0061722A`, `0x0061728D`, `0x0061731D`, `0x006173C5` | CSV 291 / 286 / 303; keys `0x0088B408`, `0x0088B3CC`, `0x0088B33C`; join/fault paths |
| `multi_error:game_lost` | `0x00618130` | `0x006181BC` | CSV 307; key `0x0088B5A4`; connection loss |
| `multi_error:fail_join_game` | `0x006185F0` | `0x00618788` | CSV 303; key `0x0088B33C` |

There is a table inconsistency worth preserving in the evidence: CSV lines 314-317 put the four CTF flag-loss keys under **`multi_error`**, but the examined caller asks for **`multi_message`**. Their intended English text is `Team 1/2 has lost flag 1/2`; exact runtime output for these mismatched lookups was not tested. Do not invent a missing `multi_message` row as verified data.

`multi_message:you_win` (CSV 79), `game_over` (107), and `players` (108) exist as result/UI text. Their presence does not establish an additional message-line call in the inventory above. Stock kills/deaths/lives/time/ping/loss **scoreboard labels** are separate: `multi_common:player`, `died`, `kill`, `life`, `time`, `ping`, `loss` at CSV 416, 421-424, 417, 427; the label initializer around `0x006269xx` loads them. Suppression should not remove the scoreboard or change its counters.

### Alliance output is partly UI and partly chat-attributed notification

**Verified:** these strings are executable literals, not entries found in the inspected localization table:

| Text | String VA | Producer/path |
|---|---|---|
| `Ally with team #: ` | `0x00875570` | `0x0046CD10`, calls UI label setter `0x00823470` at `0x0046CDB3` |
| `Unally with team #: ` | `0x00875558` | Same team-number input UI |
| `Ally with team %d` | `0x00875544` | Submit callback `0x0046CED0`; announcement call `0x0046CF33` -> `0x00572DA0` |
| `UnAlly with team %d` | `0x0087558C` | Same callback; announcement call `0x0046CF60` -> `0x00572DA0` |

The input initializer `0x0046CC80` registers the submit callback at `0x0046CCC4`. Native key handling calls the prompt opener at `0x0061DE4B` / `0x0061DE60`. The working-tree harness README also identifies **Y** as the stock online ally key; that key observation was not rerun here.

The submit callback first sends the alliance operation through `0x0046CE50` and changes the local alliance through `0x004DFDF0` / `0x004DFE30`, then emits the text announcement. Those gameplay operations are separate from the announcement and must continue if only messages are suppressed.

`0x00572DA0` packages the formatted announcement with word `0x4350` (little-endian `PC`) and sends it at `0x00572E6F`. Its nine direct callers are the two alliance sites above plus the seven CTF/time/score sites `0x0056DD1B`, `0x0056DD83`, `0x0056DDEB`, `0x0056DE53`, `0x0056DEBD`, `0x0056DF3B`, `0x0056DFC5`.

**Crucial verified distinction:** the receive dispatcher recognizes `0x4350` at `0x00570A10`, reaches `0x00571048`, formats `<player> text`, then calls `0x00624550` at `0x005710DD` with the real sender ID. **Ordinary public player chat also constructs `0x4350`**, in the separate chat-input producer `0x006247A0`, at `0x00624D49`. It locally echoes via `0x00624710` and sends through the player-chat transport. Therefore:

- Passing every nonzero sender preserves chat but also preserves stock alliance/CTF echoes.
- Dropping all received `PC` packets destroys ordinary public chat.
- Suppressing the known stock announcement producer/callers preserves normal chat production and reception, even when a player literally types `Ally with team 5`.
- Both clients must have the policy active. A legacy peer can still originate stock `PC` text indistinguishable from public chat at the receiver. Do not “fix” that by text matching.

### Chat controls and lobby text: inventory boundaries

User-initiated chat commands have their own local output through `0x00624710` (which uses the local player ID), or direct text append for `/help`. Stock command responses include:

- `/mute`, `/unmute`: `multi_message:muted`, `unmuted` (CSV 89-90).
- `/kick`: `kicked`, `only_host_kick` (49, 94).
- `/system`, `/system on`, `/nosystem`, `/system off`: `system_on`, `system_off` (95-96).
- `/lock`, `/unlock`: `locked`, `unlocked`, `only_host_lock`, `only_host_unlock` (97-100).
- Unknown slash command: `unknown_command` (101); `/help` directly lists the command syntax.

Preserve these deliberate chat interactions in the proposed policy. They are not automatic combat/campaign noise. Chat addressing labels `to_message`, `from_message`, `to_allies_message`, `to_all_message`, `broadcast_message` are CSV 47-48 and 91-93; keep them.

The table also contains legacy/lobby status and error text: `system_slow`, `system_merge`, `system_best`, `only_ckick`, `send_buffer_full`, `success`, `fail` (35-41); `player_named` + `left_room`/`entered_room`, `you_are_host`, `file_differs` (42-46); `kick_room`, `lost_game_connect`, `lost_room_connect` (50-52); player-info prompts/fields/actions (53-65); `creating_player`, `joining_game`, `unknown`, `enter_room_name`, `system_server`, `high_end_one` (66-71); `rebuilding_room` (106), `no inet`, `no auth` (109-110). These are verified table entries, **not verified additional in-mission HUD producers**. Keep the policy off in lobby/menu states; changing their strings globally would affect unrelated networking UI.

### Scrap

**Verified negative finding:** no scrap-transfer/receipt message was found in the inspected `multi_message` table or the direct system-message/broadcast callers above. Do not claim a Redux equivalent of some other Battlezone version's “gave scrap” notice without a trace.

The executable does contain `Team 1 Scrap: %ld/%ld` (`0x00885288`, reference `0x005978DC`) and `Team 2 Scrap: %ld/%ld` (`0x00885240`, reference `0x00597C64`). Their code formats text and calls the drawing path `0x004C0100` (e.g. `0x00597CBC`), rather than the message router. Nearby literals include `Add Scrap` / `Sub Scrap`. **Inference:** these belong to a diagnostic/management display, not a transient network message. The ordinary scrap gauge and resource state are outside the proposed suppression policy. Additional runtime scrap notices, if reported, need a new source trace before expanding the filter.

## 2. Suppression options and risks

| Option | What is verified / feasible | Risks and assessment |
|---|---|---|
| Mission Lua / stock API | The stock Lua reference lists `DisplayMessage`, alliances, `Send`/`Receive`, and network predicates, but no documented switch for stock notices. Replacing Lua's global `DisplayMessage` cannot intercept native producers. | No verified Lua-only solution. Disabling multiplayer or changing death/alliance mechanics would break co-op rather than just suppress presentation. |
| Stock `/nosystem` or `/system off` | Parser at `0x006247A0` recognizes the commands and writes zero to global `0x008EC708` at `0x00624B8C`; `/system` or `/system on` writes one at `0x00624B2A`. Router test at `0x00624629` gates all sender-zero messages. | **Reject for this task:** stock Lua `DisplayMessage` is sender zero too, so CR notices disappear. Player-attributed alliance echoes survive. `DisplayMessage("/nosystem")` only displays text; it does not execute chat input. No stock Lua setter for this gate was verified. |
| `LockAllies(true)` | Lua registration `0x00871E38` -> binding `0x00501CB0` -> `0x005C9450` -> setter `0x0046CE10` for prompt gate `0x0260D5EC`. Prompt opener tests that gate at `0x0046CD20`. | Can prevent the ally/unally input UI, not kills/joins/deaths. Reference documents that invoking it from `Start()` has no effect in Redux; apply after startup and validate. This changes permitted player actions, so keep it separate from pure presentation suppression. |
| CR data files: blank localized fragments | The relevant fragments are in the root multilingual CSV and several pointers are cached. | Blank suffixes still leave player/team names; name fallback still leaves `%d`; formatting adds spaces and may consume a HUD line. Empty-cell semantics and mod override precedence are unverified. Whole-table replacement affects all missions/languages, and cannot remove hard-coded alliance strings or CTF literals. **Not recommended.** |
| CR `.cfg` / HUD replacement | No relevant message-source switch was found in inspected network/config/API surfaces. The same control renders both desired and unwanted text. | Hiding/removing the control hides chat and CR. A HUD lifetime/layout change is broader and riskier than producer filtering. Absence from the searched files is not proof that no undocumented engine setting exists. |
| Existing EXU kill-message API | `src/Patches/KillMessages.cpp:37,94,115`; `exu.SetCustomKillMessage(team, name)` only replaces team/player name buffers. Export registration at `src/luaexport.cpp:894-895`; definitions at `Definitions/ExtraUtils.lua:2168-2175`. | **Not a suppression API.** Setting names to empty strings still leaves event fragments. Does not cover joins, alliance, host, lag, or mode notices. |
| New EXU native filter | EXU already has checked patches, build qualification, Lua lifetime cleanup, and the kill-name hook. A mission-only API could drive the two proposed source filters directly. | Needs new targets in `exu.json`/profiles, qualification, explicit cleanup, and safe DLL unload. Do not overlap/bypass the existing kill-name hook at `0x0062627F`. EXU-only is viable if ownership is deliberately assigned there; avoid parallel OpenShim/EXU implementations. |
| OpenShim patch + EXU binding + CR opt-in | Existing SDK bridge and lifecycle seams provide the appropriate dependency direction. Two native sources cover the observed system path plus stock chat-attributed broadcasts. | Preferred. More cross-repository integration than EXU-only, but centralizes hook/build policy. Must default off, identify CR opt-in separately from network state, reset reliably, preserve varargs ABI, and handle startup ordering. A global INI toggle or “all network games” rule is not sufficient. |

The existing EXU hook is cataloged as `Callbacks::KillMessageHook = 0x0062627F` in `exu.json:1131` and `src/Util/EngineAddresses.generated.h:480`. Its exact eight original bytes are `8B 55 A8 C6 44 15 B4 00`, also present in the released executable. It modifies the 32-character name buffers after their construction. Leaving that hook intact and filtering downstream avoids competing patches.

## 3. Recommended design contract

### Ownership and activation

**Proposed names, not existing APIs:** `exu.SetStockNetworkMessagesSuppressed(enabled)` plus a capability/status query. Implement the low-level provider in OpenShim; EXU parses Lua arguments, checks the live provider, passes the Lua generation/mission ownership, and releases the request when that state closes. Return explicit unavailable/inactive status on an unsupported build or missing provider; leave stock behavior intact and record one diagnostic rather than crash the mission.

`ExtraUtilities/src/OpenShimBridge.h:28` already resolves exports through the loaded `winmm.dll` and checks provider liveness. OpenShim's `include/openshim_sdk_bridge.h` and `include/openshim_sdk_exports.inc` require append-only provider ABI changes. Do not rely on a bootstrap export alone as proof that the provider is live.

CR should opt in from the shared co-op setup, with an explicit CR co-op presentation policy. Every local peer must call it; it is not an authority-only operation and does not need Lua `Send` replication. Gate activation on **both** CR's opt-in and native network-game state. The stock `IsNetGame` registration at `0x00872210` binds `0x00505310`, which calls `0x00571C40`; qualify the native predicate before using it.

Use `CRCoop.Initialize` as the shared idempotent setup location, with the capability passed through the existing EXU integration. `misn03` already requires EXU at line 9, performs a network-only early startup operation at lines 13-16, and initializes CRCoop at line 835. To minimize initial notice leakage, request suppression at the earliest opted-in mission root setup after EXU loads, then reaffirm it in `Initialize`. Avoid making `require("CRCoop")` alone a global suppression trigger: CR's persistent configuration also loads that module.

**Startup limitation, not verified behavior:** a Lua setter cannot retrospectively remove notices appended before it runs. CR already documents callbacks arriving before `Start()` (`CRCoop.lua:157-159`), but this research did not establish the exact ordering of native join messages versus Lua loading. Capture the initial join/load interval. If a strict “no stock line even during load” requirement exposes that gap, extend the gate to a qualified mission-load seam using explicit CR co-op metadata before append, rather than globally suppressing lobby notices or guessing from `misn03` alone. Do not clear the shared chat buffer to erase earlier lines.

### Native source policy

For `0x0056FCB0`, use an entry trampoline that can inspect the original caller without consuming the variable arguments:

- Inactive, single-player, unsupported, or stale-generation request: tail-call the original.
- Stock Lua caller return address `0x0050536E`: always tail-call the original. This preserves **all** Lua text, including `[CO-OP]` notices, unprefixed CR warnings, and diagnostic `DisplayMessage` output.
- Qualified stock system-notice caller: suppress the HUD append. Cover all 48 non-Lua direct call sites inventoried above if the intended policy is “only campaign messages plus chat.” Keep fault/debug information available in diagnostics; do not silence unrelated modal error handling.
- Unknown caller: pass through and diagnose for later qualification. Do not turn a missing classification into dropped user text.

Treat this as a source classification before formatting/output. Do not build a fake generic C++ forwarding call for arbitrary varargs: preserve the original stack/calling convention and instruction boundaries. Do not parse the final localized sentence. Address comparisons must use resolved build-relative sites, not feature-local absolute literals.

For `0x00572DA0`, suppress only the nine qualified native stock announcement callers while the gate is active. Let any unknown caller proceed. The function is a presentation-only notification wrapper in the examined image; alliance state and the CTF result operations remain in their callers. This intentionally prevents those stock **text** packets from being produced, while preserving gameplay packets, mission Lua `Send` traffic, and ordinary chat's separate producer.

This source-based design preserves public/allies/private chat verbatim, including chat text that equals a stock notice or starts with `[CO-OP]`. It does not require players' chat to carry a campaign prefix. With an older/unmodified peer, stock chat-attributed announcements can leak through; capability checks on both clients should make that limitation visible to testers without filtering their chat.

For the optional alliance input UI, prefer the existing mission alliance lock if CR intends fixed alliances. Apply the documented post-start timing and test it independently. Otherwise a separately qualified prompt opener hook can hide the input UI under the same opt-in, without suppressing Enter/chat or the generic UI text-entry functions. Label this optional UI behavior separately in capabilities; do not report two message hooks as hiding the prompt box.

### Lifetime and failure behavior

- Default false for every new mission/Lua generation. Reset on mission exit, Lua-state closure, restart/new map, and provider shutdown, including abnormal client departure.
- Early setup may request the policy before simulation starts; retain only a request owned by the currently loading generation. Make the effective gate valid during the opted-in load/play interval, and clear it on exit. A simulation-active-only gate may leak pre-start lines; a process-wide persistent boolean can leak into the next single-player mission.
- EXU's `src/PublicAPI.cpp:144,165` already resets mission-scoped state and performs Lua-state cleanup; it resets custom kill names at line 157. `EXU_GetLuaStateGeneration` at line 207 supplies generation identity. Explicitly release the OpenShim policy there rather than depending on EXU unload.
- `src/patches/lifecycle_seams.cpp:327-408` already detects mission simulation transitions and notifies EXU. The SDK exports `OpenShimIsMissionSimulationActive` and `OpenShimResetMissionHookOverrides`; they are useful lifecycle surfaces, not existing message suppression functionality.
- Keep the current `0x008EC708` user setting untouched. Changing `/system` in chat should retain its stock semantics; the co-op policy adds source suppression, not a rewrite of the user's chat preferences. If the user manually hides system text, Lua DisplayMessage still follows that existing setting unless a separate requirement explicitly changes it.
- No work inside the hot-path hook should call mission Lua, allocate unbounded buffers, or acquire renderer/UI ownership. Optional development counters should record source, passed/dropped outcome, and generation, without flooding the HUD.

### Build and platform qualification

The addresses above are **static GOG evidence**, not deployable universal signatures. OpenShim must catalog sites/resolves in `scripts/patches.json`, document independent semantic identity, register actual patches in `include/patches.h` / `src/engine/patcher.cpp`, and fail closed on ambiguous matches or mismatched instructions. The two entry prologues are similar and are not adequate identity signatures by themselves.

If choosing EXU-only, put targets in `exu.json` and qualification profiles and regenerate the address header; do not add raw engine addresses to feature code. Never patch both repositories into the same target.

Future validation must follow `Docs/AGENT_PATCH_WORKFLOW.md`, including registration checks and the network baseline validator if network patch files change. Keep the load chain and deployed `patches.json` coherent. This design needs no new OS service, file lookup, or store-specific runtime path, but that does **not** prove compatibility. Qualify Windows/GOG, settled Windows/Steam, Steam/Proton, and GOG/Wine or Proton as required by `Docs/BZR_PLATFORM_COMPATIBILITY.md`. Leave unavailable lanes explicitly unverified. No deployment or release was performed here.

## 4. Two-client harness test plan

These are **future tests**, not commands executed during research. Use `reverse_engineering/coopflow/README.md` and the harness's isolated instances; keep the canonical CR checkout and live install untouched while another agent owns them.

Stage reviewed candidate CR scripts plus matching EXU/OpenShim artifacts as a content/instance override. `New-CRFlowOverride.ps1` can assemble changed CR content and extras, but it includes the working tree's other changes: review `OVERRIDE.txt` and pin the input snapshot. Its flat `-Extra` copy is not proof that every loader/plugin/config file reached its required instance location. Verify both clients' complete load chains, the actual selected provider, executable hash, and deployed `patches.json` before a run. Do not hand-copy one DLL and assume it is sufficient.

Start with a purpose-built future `coop-message-suppression` scenario on `misn03`, then the existing `win`, `lose-tower`, and `host-leaves` cases. Commands after implementation can follow:

```powershell
powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopMission.ps1 `
    -Mission misn03 -Scenario coop-message-suppression -ContentOverride <reviewed-folder>
powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopMission.ps1 `
    -Mission misn03 -Scenario win -ContentOverride <reviewed-folder>
```

The first scenario name does not exist as a result of this research. The runner supports a scenario path, so a reviewed test-only scenario need not be confused with shipped campaign content.

| Test | Stimulus and required result |
|---|---|
| Baseline | With policy off, capture actual unwanted team-5, human death/ejection, join/leave, and alliance output on both clients. Prove that the stimulus really exercises the source before claiming suppression. |
| AI deaths | Host creates/owns disposable enemy team-5+ craft/buildings and destroys them. No stock ship/building line on either client with policy on; native drop counters increase; object removal and mission progress still replicate. |
| Human deaths/ejection | Each client damages/ejects/destroys its own craft/pilot, one event at a time. Exercise attributed and unattributed deaths, snipe, and ejection using appropriate normal gameplay/test controls. No stock line on either client; existing lives/respawn behavior remains unchanged. A generic `kill()` alone does not prove the sniper branch. |
| CR output | Issue distinct `DisplayMessage("[CO-OP] host/guest sentinel")` locally on each client, and an unprefixed Lua sentinel. All appear. Then trigger real CR pings/rescue requests/replies so CR's transport makes the notices appear on the intended peers. |
| Chat | Type real public chat both directions, allies chat, and private chat. Check sender attribution, receipt, mute behavior, local echo, and chat entry closing. Repeat with `Team 5's ship destroyed`, `Ally with team 5`, `[CO-OP] ordinary chat`, and `%s %d` as literal chat text. All must work. Lua `Send` or `DisplayMessage` is not a substitute for testing native chat. |
| Alliance echoes | Trigger the stock ally/unally UI and submit a team, with the optional lock/prompt policy temporarily off if needed. The announcement is suppressed on both clients; ordinary chat with identical words is preserved; separate alliance operations still occur. Restore CR's normal human/enemy alliances after this isolated check. |
| Optional prompt policy | Press the stock alliance key after startup. The team-number box is absent if that option/lock is enabled. Enter, public chat, and CR's PDA still work. Test stock `LockAllies` timing separately. |
| Join/start | Capture both clients from lobby-to-mission transition through `Start`/first update. Check whether join notices append before activation. Classify a startup leak honestly and use the load-seam extension if required. Do not erase chat history to pass. |
| Departure/host migration | Existing `host-leaves` scenario: stock departure/host notices are hidden during co-op; guest still detects leader departure and executes CR's failure path. Register the expected host exit before closing it. Test guest departure separately. |
| Admission/rejoin | CR's own unprefixed admission warnings remain visible. The harness documents no supported late join/rejoin; use disposable negative tests and restart, not a claim that suppression adds late-join support. |
| Native limits / fault paths | Verify which stock time/score/defeat notices can actually occur with CR's mission mode and settings. A CTF-only line is not a required `misn03` runtime case. Native injection can test a classifier in isolation, but does not prove campaign reachability. Keep network failures diagnosable. |
| Reset | Disable/re-enable in a mission, restart, leave for lobby, load another co-op mission, and then load CR single-player in the same process. No stale generation or policy; single-player behavior and all Lua messages match baseline. Test an EXU module pinned by a consumer too, because unload alone is insufficient. |
| Other games / unsupported | Ordinary non-CR multiplayer and single-player retain stock notices; missing/old provider and mismatched-build cases remain stock and report unavailable rather than applying partial unsafe hooks. A mixed-client version test documents legacy `PC` leakage while chat remains intact. |

Use `Invoke-CRFlowStep` for named checks and screenshots, `Invoke-CRFlow` / `Wait-CRFlow` for local state, and actual key input for chat/alliance/PDA behavior. Follow ownership: host owns mission AI; each client owns its own player object. The working-tree input helpers support `Send-CRFlowKey ... -Focused` for keys that require real input; verify that reviewed helper version before relying on it.

**The existing probe is insufficient by itself to prove absence of native HUD lines.** `CRFlowProbe.lua:304` wraps the mission's `native` presentation function table. Stock engine kill/join/chat output does not originate in those Lua wrappers. Lua presentation parity or no `DisplayMessage` event does not prove no line was appended.

For the test build, capture source classifications/drop counts and actual common append events for control `0x00920168` (including originating caller and text). Correlate with both clients' `flow-shots` and chat logs. `BZChatLog.txt` alone is insufficient: it can contain history while HUD state differs, and chat text matching a stock sentence must remain. Use isolated stimuli so the native append stream distinguishes the typed-chat positive case from the stock-source negative case. A Lua sentinel verifies the native path, not just that Lua was called.

Keep full win/loss/result and world/presentation parity checks from the harness after the narrow checks. Evidence belongs under `C:\BZRCoop\runs\<run>\`: `flow-summary.md`, `flow-steps.jsonl`, `flow-shots\`, both `BZLogger.txt` files and the server log. Normal harness launches are serialized through `BZRHarness.ps1`; do not dot-source it again inside a scenario. Use `BZR_FORCE_WINDOWED=1` and close through `Stop-BZRGame -Id <pid> -NoForce`; never force-kill Redux.

## Outstanding verification before implementation is considered complete

1. Runtime-confirm the two message producers and the actual append stream on the installed GOG build, including the first join/load interval.
2. Confirm whether the user's alliance example means the transient echo, the input-box label, or both; the design explicitly covers the distinction.
3. Qualify native hook sites/callers and calling conventions, and prove no gameplay/transport side effects change except the selected stock announcement text packets.
4. Verify chat in all addressing modes and CR output without a prefix allowlist, lifecycle reset, and both clients' capabilities.
5. Investigate any additional observed scrap/score/status lines by source trace; the current inventory distinguishes message lines from gauges, scoreboards, result UI, and lobby text.
6. Complete the relevant Steam/Proton/Wine qualification before release; static GOG addresses are not cross-build proof.

No code, existing repository file, game data, configuration, branch, or deployment was changed by this research.
