# Handoff: chat / ally-prompt detection + LockAllies (CR co-op)

Written 2026-10-07. For the next agent. Read `TEXT_ENTRY_STATE.md` (Codex's RE)
and `HANDOFF_PDA_CONTROLS.md` first.

## Goal (user's request)

"Implement both (LockAllies) and the text entry active check":

1. Typing in chat (or the ally/unally team-number box) must not trigger CR's
   co-op keys (J ping, X PDA toggle, [ ] / arrows).
2. Y/U must not open the stock ally box in co-op (alliances are fixed).

## State: done, live-validated, committed (2026-10-07)

`coop-text-entry` passed 7/7 with no script errors on either client
(`C:\BZRCoopuns\cr-misn03-coop-text-entry-20261007-150741`). Committed and
pushed on the three agent branches below. Remaining open item: LockAllies is
never unlocked at mission end (effect on later non-CR MP games unchecked).
The "In flight" and "Next steps" sections below are historical.

### ExtraUtilities: branch `agent/text-entry-state` (created from `agent/coop-comms-pings`, uncommitted)
- Codex's work, copied from its scratch copy `Build\text-entry-state\` (Codex's
  sandbox couldn't write `.git`). 10 files: `src/Game/game_state.cpp/.h`,
  `src/Util/IO.cpp/.h`, `src/luaexport.cpp`, `Definitions/ExtraUtils.lua`,
  `exu.json`, `profiles/bzr_2.2.301.json`, `src/Util/BzrBuildProfile.generated.h`,
  `src/Util/EngineAddresses.generated.h`.
- New Lua: `exu.IsTextEntryActive()`, `exu.IsAllyPromptOpen()`,
  `exu.GetTextEntryDebugState()` (`ok`, `textEntryActive`, `chatOpen`,
  `allyPromptOpen`, node/flag diagnostics). Read-only walk of the engine's
  legacy text-editor list (head `0x02CC1B40`, focus bit `0x100` at payload
  `+0x120`), SEH-guarded, 64-node cap, gated on three optional profile anchors.
- Reviewed by me: looks correct. `Release\exu.dll` rebuilt with MSBuild (OK).
- Codex's validation: catalog 113 MATCH, synthetic smoke test passed. Codex's
  process (task bvye8vrc8) may still be finishing its log; its output is done.

### Campaign-Reimagined: branch `agent/coop-comms-pings` (uncommitted)
- `Scripts/PersistentConfig.lua`: new `PersistentConfig._IsTextEntryActive()`
  (pcall, false on older EXU). `_PollNetworkGameKeys(typing)` tracks key state
  but queues nothing while typing. `UpdateInputs` returns early while typing,
  after keeping `InputState.last_toggle_state` current for X.
- `Scripts/CRCoop.lua`: `CRCoop.Update` calls `pcall(LockAllies, true)` every
  5 s in network games (`ALLY_LOCK_INTERVAL`, `nextAllyLock`, reset in
  Initialize). Reason: Redux ignores LockAllies from Start; the gate
  (`0x0260D5EC`) is a per-client engine global, so every client sets it.
- `Docs/COOP_COMMS_PINGS.md`: chat-gap paragraph rewritten for the new behavior.
- Unverified: whether `LockAllies` survives into later non-CR MP games in the
  same process (no unlock on mission end). Check if it matters.

### BZR-OpenShim-coopflow: branch `agent/coop-mission-flow` (uncommitted)
- New `coopflow/scenarios/coop-text-entry.ps1` (misn03, real keys):
  probe present + `ok=true` on both clients → Y/U open nothing under the lock,
  hosts still allied → guest unlocks (`LockAllies(false)`), Y opens the ally
  box, J/X inside it do nothing, Esc closes → Enter (fallback `) opens chat,
  J/X ignored, Esc closes → J pings again after chat closes. Puts a guest-owned
  avtank in the guest reticle so J would otherwise ping.
- `coopflow/README.md`: case row added.
- `coopflow/TEXT_ENTRY_STATE.md`: Codex's write-up (new, uncommitted).
- Override regenerated: `overrides\coop-comms` (CR working tree + new exu.dll).

## In flight when this was written

A live run was started:
`scratchpad\run-pda.ps1 -Log scratchpad\te1.log -Scenario coop-text-entry`
(scratchpad = `%LOCALAPPDATA%\Temp\claude\C--Program-Files--x86--GOG-Galaxy-Games-Battlezone-98-Redux\46264f78-30f9-4494-89a7-3d6c09e3085c\scratchpad`).
It had produced no step results yet. Its run folder will be under
`C:\BZRCoop\runs\cr-misn03-coop-text-entry-*`. Test clients in
`C:\BZRCoop\instances` may be force-killed if it hangs.

## Next steps

1. Read the run result. Rerun with (from the coopflow repo, PS 5.1, with
   `env -u PSModulePath` if launched from bash/pwsh):
   `reverse_engineering\Run-BZRCoopMission.ps1 -Mission misn03 -Scenario coop-text-entry -ContentOverride reverse_engineering\coopflow\overrides\coop-comms`
2. Likely trouble spots:
   - Probe `ok=false` → the profile anchors don't match at runtime; check
     `GetTextEntryDebugState()` and the anchors in `profiles/bzr_2.2.301.json`.
   - Neither Enter nor ` opens chat (seen before: Enter showed no chat line).
     Codex lists the engine gates in TEXT_ENTRY_STATE.md ("Why Enter showed no
     visible chat line"). If chat cannot be opened in the test clients, mark
     that step `-Soft` and say so; the ally-box step still proves the probe.
   - The ally-box step races CR's 5 s re-lock; if Y opens nothing after
     `LockAllies(false)`, retry the press immediately or stub the re-lock.
   - Whether `IsAlly(handle, handle)` exists in BZR Lua (alliance check in the
     LockAllies step); swap it if it errors.
3. When it passes, commit on the three agent branches (never main), with
   `Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`, and push. PRs and
   merges need the user.
4. Update `HANDOFF_PDA_CONTROLS.md` line 18 ("Chat is not guarded") to point here.

## Rules (from memory / earlier handoffs)

- Never launch while the user's own game runs (`Get-Process battlezone98redux`).
- Only test clients in `C:\BZRCoop\instances`; never the main GOG/Steam game.
- Commit only on `agent/*` branches; canonical CR checkout only, no worktrees.
- Don't resize client windows. Never use `$h`/`$g` in scenarios (PowerShell
  variable names ignore case, so they clobber `$H`/`$G`); never dot-source
  `BZRHarness.ps1` from a scenario.

## Also pending (not started)

- Stock message suppression ("Team 5's ship destroyed"): design in
  `COOP_MESSAGE_SUPPRESSION.md` (OpenShim filter + EXU binding + CR opt-in).
- Per-mission respawn rally points (`CRCoop.Initialize({ rallyPoints = ... })`).
