# In-mission text entry and keyboard prompt focus

Research date: 2026-10-07. **A solid static signal was found:** the first focused node in the engine's legacy text-editor list. Both multiplayer chat and the ally/unally team-number prompt use this list. These are distinct from the lobby's `cUI_TextEntry` named `chatEntry`.

**Evidence limits:** verified below means released-executable instructions, their Ghidra decompilation, source/configuration inspection, or explicitly identified synthetic tests. No game was launched, instrumented, or given input during this task. Live client validation remains pending. The cause of the reported invisible Enter chat line and the intermittent network `GameKey` omissions is **not conclusively established**.

## Examined build and method

| Item | Identity |
|---|---|
| Executable, read only | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe` |
| Windows version / architecture | `2.2.301` / PE32 x86 |
| Size | 5,425,152 bytes |
| SHA-256 | `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413` |
| Preferred image base | `0x00400000` |
| PE timestamp | `0x58D9D6CC` (2017-03-28 03:21:48 UTC) |
| EXU source snapshot | `agent/coop-comms-pings`, HEAD `dfb5070d956585b9004a30eec1d89e70fe1eea60`; origin `https://github.com/GrizzlyOne95/ExtraUtilities` |

Addresses are preferred-image **VAs**, not file offsets; subtract `0x00400000` for RVAs. Semantic labels in this document describe observed behavior and do not assert private-PDB symbol identities.

The existing Ghidra corpus under the sibling OpenShim checkout was searched and read at `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps`. Relevant files are named `FUN_<VA>-<VA>.c`. Its findings were checked against the installed released executable with Python `pefile` and Capstone x86 instruction decoding, including the actual call sites, structure offsets, flag mask, callback assignments, and global operands. No project lock was broken, no private PDB was used to transfer addresses, and no decompiler output or binary is included in this document.

The sibling research [COOP_MESSAGE_SUPPRESSION.md](COOP_MESSAGE_SUPPRESSION.md) was read when it appeared. Its alliance-input path agrees with this investigation. Message suppression and input capture are separate features; neither is implemented by changing the other.

## Verified keyboard-focus signal

| VA / offset | Meaning and evidence |
|---|---|
| `0x02CC1B40` | Global head pointer of the legacy text-editor linked list. Read at `0x00823CE6`; constructor publishes the new head at `0x00823314`. |
| List node `+0x00` | Next node; lookup follows it at `0x00823CF3`. |
| List node `+0x04` | Previous node, established by the 12-byte node allocator at `0x00824540`. EXU does not need this member. |
| List node `+0x08` | Editor payload pointer; loaded at `0x00823D01`. |
| Editor `+0x120` | 32-bit flags; loaded at `0x00823D0A`. Bit `0x100` means keyboard focus, bit `0x01` means visible, bit `0x200` requests a redraw. |
| `0x00823CE0` | Focus lookup: returns the **first list node** whose editor flags contain `0x100`, or null. The mask is applied at `0x00823D10`. |
| `0x00823390` | Focus setter. Enabling focus clears `0x100` from all list entries, then sets it on the requested editor. Also drains queued `WM_KEYDOWN` and `WM_CHAR` messages. |
| `0x00823330` | Visibility setter; changes bit `0x01` independently of focus. |
| `0x02A1748C` | Global **node pointer** for the in-mission chat editor. Published at `0x0062434D`, cleared at `0x006246FA`. |
| `0x0260D184` | Global **node pointer** for the shared ally/unally editor. Published at `0x0046CCDE`, cleared at `0x0046CE31`. |

The editor payload is allocated as 300 bytes (`0x12C`) by `0x00824230`. Construction at `0x008231C0` initializes its buffer and callbacks and links it into the list using `0x00824540`. The text buffer starts at payload `+0x10` and spans `0xF0` bytes. The prefix length is at `+0x108`, the current text/cursor indices at `+0x10C`/`+0x110`, the submit/cancel callback at `+0x124`, and an optional up/down callback at `+0x128`.

**Why this is keyboard capture, rather than just a visible widget:** the window procedure at `0x00619340` calls the focus lookup at `0x0061964E`. For a nonnull result it passes the node, message, and virtual key/character to `0x00823700` at `0x00619668`, then consumes the keyboard message. Without a focused editor it routes input to the normal keyboard pump at `0x00619BE0`. Input collection at `0x006210A0` independently calls the same lookup at `0x0062128A` and skips the keyboard device's normal collection operation while an editor is focused.

The list head and both editor node globals can remain nonnull while the editors are closed. They are **not open flags**. The `0x100` focus bit is the relevant condition; visibility or nonempty text alone is insufficient. Focus lookup itself does not require visibility, so EXU follows the same rule.

This is a shared focus signal for the legacy in-mission editors, **not a universal focus pointer for every Redux UI toolkit**. The lobby's `cUI_TextEntry::AppendChar` at `0x007CFA70` belongs to the newer shell UI. Existing `exu.IsGameUiOpen()` covers shell/menu suppression separately.

## Verified chat path

The installed GOG `gamekey.map` and both staged files under `C:\BZRCoop\instances\Instance0/Instance1\Battlezone 98 Redux` contain:

| Game-key action | Configured keys | Action number |
|---|---|---|
| `CHAT_SENDTOALL` | Enter, grave/backtick, Ctrl+C | `0x11` |
| `ALLIE_TOGGLE` | Y, Ctrl+[ | `0x12` |
| `UNALLIE_TOGGLE` | U, Ctrl+] | `0x13` |

The action-name table at `0x008EB088` supplies these action numbers. The key-name table at `0x008EADC0` maps `Enter` to internal key `0x0D`; case-insensitive parsing at `0x00620980` accepts all three chat bindings. It builds the action lookup at `0x00918850`. `CHAT_TOGGLE` also exists as action `0x10`, but is not bound in these inspected files; its handler toggles the chat history display through `0x00624690`, rather than opening input.

Chat initialization at `0x00624210` creates the history display at `0x00920168` and the legacy entry node at `0x02A1748C`. It installs submit callback `0x00624780` and recipient-cycle callback `0x00625070`; both assignments are present at `0x00624330`/`0x00624337`.

Action dispatcher `0x0061DC10`, case `0x11`, calls chat opener `0x00624380` in a network game. The opener builds recipients for all players (`0xFFFA`), allies (`0xFFF9`), and individual players; sets the recipient prefix; clears the editable text; makes the entry visible; clears ordinary held-key state with `0x00434F20`; and focuses the entry. Visibility and focus calls are at `0x0062450F` and `0x00624525`. The prefix is localized through `multi_message:to_all_message`, `to_allies_message`, and `to_message`.

While focused, `0x00823700` handles `WM_CHAR` values `0x20..0xFF` by inserting characters. Backspace/Delete and Left/Right/Home/End edit the line. Up/Down invoke `0x00625070`, cycling the recipient prefix while preserving the editable message. Enter invokes the submit callback with the editable text and returns completion status `2`. Escape clears the text, invokes the callback with null, and returns the same completion status. The window procedure removes focus on status `2`.

`0x00624780` passes the selected recipient and text to `0x006247A0`. That function clears visibility and focus before processing the message. Null/empty text therefore cancels without sending. Nonempty input handles slash commands or sends player chat. Teardown at `0x006246D0` removes the editor from the list and zeroes its node global.

### Why Enter showed no visible chat line

**Not resolved for the reported live clients.** Static evidence confirms that Enter is bound and has an opener; it does not establish what their pending input, focus, or renderer state was at the time. Do not infer that Enter is unbound or that the lobby `chatEntry` is the missing in-mission object.

Verified conditions that can distinguish the failure:

- If an editor already owns focus, Enter **submits/closes that editor**; it does not dispatch a new chat-open action.
- The normal action dispatcher requires a nonnull local user entity (`0x00920C78`) in a network game. Chat/ally cases also pass through `0x0062C850`: it follows the user object's first pointer, then a pointer at byte offset `0x88`, and tests bit `0x20` in the target's word at byte offset `0x114`. The precise gameplay meaning of that exclusion bit was not established here.
- `GameKey` callback delivery and stock action dispatch consume engine input state, not `GetAsyncKeyState`. A raw Enter press alone does not prove that action `0x11` was dispatched.
- Rendering at `0x00823D30` tests visibility bit `0x01`; its call from `0x00617600` is inside a successful render-setup branch. Focus/visibility and actual on-screen presentation can therefore be diagnosed separately.

**Inference to validate:** if `GetTextEntryDebugState()` reports `ok=true`, `chatOpen=true`, and `entryFlags` contains `0x01` after Enter, chat input opened despite an invisible line; investigate presentation. If it remains inactive, investigate input/action dispatch and its gates. The live procedure below captures this distinction without guessing the cause.

## Verified ally/unally prompt path

Initialization at `0x0046CC80` creates the node at `0x0260D184` and installs submit callback `0x0046CED0` at `0x0046CCC4`. Dispatcher cases `0x12` and `0x13` call opener `0x0046CD10` with `1` (ally) or `0` (unally), at `0x0061DE4B` and `0x0061DE60` respectively. Thus Y/Ctrl+[ opens ally, and U/Ctrl+] opens unally under the inspected mappings.

The opener is additionally gated by the value at `0x0260D5EC`: a nonzero value prevents opening. It stores the requested mode at `0x00917398`, assigns `Ally with team #: ` or `Unally with team #: `, clears input, enables visibility, clears ordinary key state, and enables focus. These mode/gate globals are **not keyboard-focus flags**.

Input uses the same `0x00823700` editor as chat, accepting ordinary characters rather than enforcing a digits-only filter. On Enter, `0x0046CED0` parses `atoi(text)` and accepts team numbers **1 through 15**. It requests the alliance operation through `0x0046CE50`, updates the local alliance through `0x004DFDF0`/`0x004DFE30`, and announces it through `0x00572DA0`. Invalid/empty input still closes the prompt. Escape supplies null and closes without changing alliances. Both visibility and focus are cleared by the callback. Teardown at `0x0046CE20` removes the node and clears the global.

Both modes share one editor, so `exu.IsAllyPromptOpen()` means **ally or unally team-number input currently has focus**. It does not mean alliances are unlocked, and it does not change alliance policy.

## Mission GameKey path: verified findings and remaining gap

The Lua bridge is `0x0050AA10`. When its mission Lua state exists and the 16-bit pending key at **`0x0091989C`** is nonzero, it formats a key string, looks up the mission's `GameKey`, and calls it if it is a function. It also stores `LastGameKey` and subsequently calls mission `Update`. Key names use a table at `0x00917B28`, with modifier bits `0x100` Ctrl, `0x200` Shift, `0x400` Alt, and a CapsLock case. This bridge does not contain a network-specific J/bracket/arrow allowlist.

Verified upstream path:

1. `0x00619BE0` processes ordinary key messages. Fresh key-down calls `0x00434B00`; repeat key-down does not enqueue another discrete key.
2. `0x00434B00` translates the virtual key using the 16-bit table at `0x008E7268`, attaches modifiers, and enqueues it in the 64-slot ring at `0x02CF4420`, with indices `0x0260C22C`/`0x0260C230`.
3. `0x00434740` fills initially unmapped punctuation using `MapVirtualKeyA(..., 2)` through `0x00619F40`. Zero punctuation entries in the on-disk table therefore do **not** prove runtime exclusion.
4. The keyboard API table at `0x008E75CC` has its `+0x18` key-reader slot at `0x008E75E4`, pointing to `0x00434A80`, which pops one ring entry or returns zero.
5. `0x006210A0` calls the selected keyboard device's `+0x18` slot at `0x00621566`, then stores the result at `0x0091989C` at `0x00621577`.
6. `0x0061DBA0` maps that key to stock actions using `0x006217F0` and dispatches through `0x0061DC10`. The Lua bridge separately sees the same global when its update runs.

Focused legacy entry routing bypasses normal key-message queuing and normal keyboard collection, explaining why the engine normally treats typing as editor input. EXU's raw `GetGameKey` polling bypasses those protections, which is why mission code needs the new focus check.

**The exact cause of intermittent J/[ ]/arrow/Enter callbacks in the reported network tests was not found.** The pending key is a single sample read on mission update, rather than a Lua event for every OS transition. Input/update scheduling, queued keys, local UI capture, or cinematic/menu consumers are possible contributors, but none was proven to cause those particular omissions. Retain the real-key probe in `scenarios/gamekey-names.ps1`; do not replace this gap with a claimed network key whitelist.

## Prepared EXU implementation and validation

Three Lua bindings were implemented in an isolated source copy:

- `exu.IsTextEntryActive()` — any focused legacy in-mission editor.
- `exu.IsAllyPromptOpen()` — the focused node is the ally/unally editor.
- `exu.GetTextEntryDebugState()` — `ok`, `textEntryActive`, `chatOpen`, `allyPromptOpen`, `focusedNode`, `focusedEntry`, `chatNode`, `allyNode`, `entryFlags`.

The C++ operations live in `src/Game/game_state.cpp/.h`, with thin bindings in `src/Util/IO.cpp/.h`, registration in `src/luaexport.cpp`, and declarations in `Definitions/ExtraUtils.lua`. Reads reproduce the engine's first-focused-node lookup, limit traversal to 64 nodes, reject invalid/misaligned/overflowing addresses, and run under `Seh::Filter`. Failures leave the entire snapshot false/zero and `ok=false`. An empty valid list produces `ok=true` with inactive state.

All addresses/signatures are in `exu.json` and the regenerated address header. Three optional, feature-specific profile anchors qualify the focus lookup and the chat/ally node publication sites. Each query requires the existing `RuntimeGate`, preferred image base, and all three fixed-address anchor matches before reading globals. No native calls, hooks, input writes, cached editor pointers, or initialization-time scans were added. Steam must have settled runtime bytes matching these anchors; Steam, Wine, and Proton live behavior remains untested.

**Git status and blocker:** this session grants read-only access to EXU's `.git`. Its initial `git switch -c agent/text-entry-state` failed with permission denied creating the branch lock. An external session subsequently created the requested branch from the recorded HEAD and copied the ten prepared source files into the main checkout; their bytes were verified identical to the scratch implementation. This session's explicit staging attempt still failed creating `.git/index.lock`, so the requested commit remains unperformed by this agent. `.claude/` was left untouched. The ignored `Build\text-entry-state` directory contains `text-entry-state.patch`, `task-files.json`, a guarded `Apply-And-Commit.ps1`, and `commit-message.txt` ending with the required `Co-Authored-By: Codex <noreply@openai.com>` line. No push or merge was performed.

Validation of that exact prepared source:

- `MSBuild.exe ExtraUtilities.sln /p:Configuration=Release /p:Platform=x86` — passed in both the prepared copy and main checkout. Main DLL: `C:\Users\iestu\Documents\GIT\ExtraUtilities\Release\exu.dll`; PE32 x86, all three binding names present, SHA-256 `b58261d590101edcf702f3d8089bdcccdb731d275a6feb90eeba32f1e006449a` at inspection.
- Catalog qualification against the examined executable — **113 MATCH, 0 relocated/missing/ambiguous**, including all six new signatures; profile qualification passed.
- Generated address/profile header checks — passed. Build qualification tooling's 12 tests — passed. Lua API parity, shared-document hashes, address census, and patch-preimage checks — passed.
- Synthetic x86 smoke executable compiled the actual `game_state.cpp` probe and populated only its own memory. Empty/inactive lists, chat/ally/other focus, first-node priority, the 64-node limit, cyclic/overlong lists, null/overflowing payloads, inaccessible memory caught by SEH, unsupported runtime, and changed identity bytes — passed. This is **not** a live Redux smoke test.
- Full `tools/validate_hardening.py` remains blocked by the **pre-existing** `src/Ogre/OgreNativeFontBridge.cpp:827` exception-filter violation. The baseline checkout was run before applying these changes and fails at the same location. That unrelated file was not changed.

## How to validate live with the existing two-client harness

Coordinate with the agent owning the running session. Use the harness session from [README.md](README.md); do not launch another game or dot-source `BZRHarness.ps1` inside a scenario. The existing clients must load the new DLL through the owner agent's normal override/mission reload procedure. A DLL already loaded by their current Lua state will not acquire these bindings just because a new file was built.

Start by confirming availability on each client:

```powershell
Invoke-CRFlow 0 'return type(exu.IsTextEntryActive)'
Invoke-CRFlow 0 'return exu.GetTextEntryDebugState()'
```

Require a function and `ok=true`; repeat with client `1`. The state is local to each client, not replicated gameplay state. In ordinary gameplay both booleans should be false even if `chatNode`/`allyNode` are nonzero. While opening/closing prompts, wait at least an update before reading the snapshot.

| On the focused test client | Expected snapshot / queries |
|---|---|
| Baseline, no editor/menu | `ok=true`, `textEntryActive=false`, `chatOpen=false`, `allyPromptOpen=false` |
| `Send-CRFlowKey 0 0x0D -Focused` (Enter) | If action `0x11` opens chat: `IsTextEntryActive()=true`, `chatOpen=true`, ally false; `focusedNode == chatNode`; flags contain `0x100` and normally `0x01`. Record the snapshot even if no line is visible. |
| Escape (`0x1B`) after open chat | Capture false; cancellation must not send text. Escape first closes the editor rather than necessarily opening the pause menu. |
| Grave (`0xC0`) from baseline | Same chat-open state under the US layout; use this to compare with Enter. Test Ctrl+C manually if the current harness exposes only single-key presses. |
| Type J (`0x4A`), [, ], arrows while chat is open | Capture remains true; characters/caret/recipient changes belong to chat. Raw `GetGameKey` can still see held keys, so mission code must gate them. |
| Enter to submit, then read again | Capture false. A short ordinary message should appear on the other client; an empty line just closes. |
| Y (`0x59`) with alliances unlocked | Text capture true, `IsAllyPromptOpen()=true`, `chatOpen=false`; `focusedNode == allyNode`. |
| J followed by Enter in ally prompt | Capture stays true while typing; nonnumeric input closes without changing alliances. This avoids altering the co-op teams during the initial probe. |
| Y then Escape | Both queries return false after cancellation. |
| U (`0x55`) with alliances unlocked | Same ally-prompt state for unally mode; cancel with Escape. |
| Pause/options/shell pages | `IsGameUiOpen()` handles command suppression; do not treat this API as shell `cUI_TextEntry` focus detection. |

If CR has locked alliances, Y/U should leave the probe inactive; record that condition rather than declaring the detector broken. Any valid numeric alliance submission changes gameplay, so reserve that test for a session where the owner intends to test alliances.

For the Enter discrepancy, record the full snapshot after Enter, Escape, grave, Escape, and Y. If chat owns focus but is invisible, investigate its presentation. If Enter does not acquire focus but grave does, trace the pending key/action path; if neither opens but Y does, compare action `0x11` dispatch and chat initialization. Record `ok=false` separately as unsupported/failed probing, not an inactive editor.

Mission-side integration should guard **both callback commands and polled commands**, for example:

```lua
local entry = exu.GetTextEntryDebugState()
if not entry.ok or entry.textEntryActive or exu.IsGameUiOpen() then
    -- Skip local key commands; maintain/reset edge tracking as appropriate.
    return
end
-- Handle the mission's keys here.
```

This illustrates conservative handling of an unavailable probe. The boolean APIs return false on failure, consistent with existing state-query behavior; false alone does not distinguish unavailable from inactive. No Campaign Reimagined integration was changed in this task.
