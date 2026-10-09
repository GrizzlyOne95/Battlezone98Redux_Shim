# Network battle-load checkpoint — 2026-10-09

The battle fixture and reporting tools are implemented and locally tested.
Native qualification is blocked before the first simulation frame; no battle,
destruction, scrap or battle performance acceptance is claimed. Server socket
submission logging is implemented and tested, but not yet exercised by native
clients. All four internal clients are stopped and all 128 backed-up targets
were independently verified restored. Resume from this checkpoint.

## Source checkpoints

| Worktree under `C:\Users\iestu\Documents\GIT` | Branch | Checkpoint |
|---|---|---|
| `BZR-OpenShim-battleload` | `agent/network-battle-load` | implementation `677cccb0`, followed by this handoff/report-test checkpoint; based on co-op `34a3b799` |
| `Battlezone98Redux_DedicatedServer-observability` | `agent/network-startup-observability` | `fcc350dde528d0f7348a75c75a459ee474fd8848`; based on relay impairment `2c1522f` |
| `BZR-OpenShim-netfix` | `agent/net-impairment-matrix` | previous qualification `9856af9c`, followed by checkpoint updates to plan/results/roadmap |

These are task branches; no merge, release or public server deployment occurred.
The unrelated untracked `BZR-OpenShim-netfix\build-tests` directory is preserved.
Existing draft PRs: OpenShim #417/#418 and DedicatedServer #8. The new battle
and observability branches are separate continuations.

## What is built and verified

`Run-BZRBattleLoad.ps1` stages `nbattle` on the existing authored `lcbench`
terrain, copied byte-for-byte. Host-owned tank/fighter armies on teams 5/6 use
native Attack, damage, ammo, deaths and scrap. Humans 1–4 observe. Replacements
sustain load, bounded at 160 active and 640 cumulative creations. Measurement
starts after ramp; cleanup occurs afterward. Four-client population/activity
assertions, CPU/simulation/probe samples and twelve-link relay reporting are
implemented. Configuration is repeatable; native combat is not deterministic.

Lua fixture tests passed authority, bounded creation, 160 distinct positions,
640 churn cap, natural damage/ammo/death accounting, exact zero-health scrap,
baseline exclusion, frozen end peaks and no early cleanup. Python map tests
passed marker basis/motion/team/sequence/mission references and unchanged
terrain bytes. Report tests passed twelve links, drops, payload retry identity,
CPU/rates and missing-window rejection. PowerShell syntax checks passed.

Server `fcc350d` adds opt-in decision-to-socket submission correlation:
packetId, copyIndex/count, route/user/lobby/socket identity, queueWaitMs,
schedulerLagMs, scheduledDelayMs, sendCallMs and outcome. Async socket errors
explicitly have unknown packet correlation. Delayed callbacks after trace
close are guarded; closing skips retain counters; sync exceptions rethrow.
Opaque datagram bytes remain unchanged. New send events omit replay route
fields so replay scoring does not duplicate submissions. `submitted` means
DatagramTransport.sendto returned, possibly buffered; it cannot prove delivery.

Server validation passed 8 focused observability tests, 8 impairment groups,
5 fault-injection groups, 12 bounded pair-port tests, full pair-port suite and
6 capture tests on ephemeral loopback. Existing writers flush per record;
earlier zero-size tool reads were not evidence of a missing flush bug.

## Latest live evidence and recovery

Control: `C:\BZRCoop\runs\battle-control-20261009-102214`.
Run: `C:\BZRCoop\runs\battle-load-20261009-102214-smoke20`.
Map/source snapshot: corresponding `battle-load-20261009-102214-smoke20-map`.
Pointers: `C:\BZRCoop\runs\latest-battle-control.txt` / `latest-battle-run.txt`.

All four selected and loaded the map on a clean relay. Lobby passed in 34.2 s;
CRFlow attached at frame/time zero. First roster command timed out after 20 s,
before BattleBegin. Native host Sync Start at 10:24:45.099 Central failed after
90 s. All twelve links forwarded; no injected drops or script/file-load error
explains the stall. Host repeatedly emitted startup `53 53 01`, with no 18-byte
`50 53` spawn-coordinate packet or `53 53 02`/`04` progression. The validated
co-op control completes sync in 249 ms and emits that progression. Peers have
SyncInAt/SyncOutAckAt zero. Check native spawn registration/eligibility first;
legacy semantic research suggests this packet depends on an eligible spawn,
but the current Redux causal branch has not been proved.

Earlier 100420/100650/101002/101530 attempts respectively failed preflight,
map selection, native marker load and selection. All retained separately in
`network_battle_load_validation_20261009.md`; none ran combat. Corrections
include authored pspw marker template, explicit coordinate fields preserving
basis/velocity, pilot description/VXT, matching terrain names and recognition
of an already-selected map. Current generator also normalizes mass_inv to 0
instead of the template's 1e30: minimize template edits in the next check.

Graceful close and WM_QUIT left hidden PIDs 53528/49284/11900/47036. The user
explicitly authorized terminating those four only; they were identity-checked
and terminated. This exception does not authorize forced future shutdowns.
`independent-restoration-audit.json` verifies all 128 expected hashes/absence
states, gamesRemaining 0. Control status records restored true. No new live
launch occurred during checkpoint saving.

The run contains flow summaries, screenshots, server log, relay/protocol traces
(trace runId e3b05f53b943), source provenance and live shutdown copies. Four
locked live bzrnet_trace copies were empty placeholders, not valid captures;
the live manifest is annotated accordingly. Separate `terminated-copy` logs
and manifest preserve final available logs after termination, marked unclean.
Raw captures remain private local artifacts, never public Git content.

## Previous accepted evidence to retain

The objective/services A/B matrix is still
`C:\BZRCoop\runs\netimpair-matrix-20261009-091255` (20/20 scored).
Independent comparison:
`C:\BZRCoop\runs\network-qualification-control-20261009-071830\comparison.md`.
Fix ON gameplay passed 9/10, stock 5/10. Modeled blackout was lower in all
matched cases, but overall acceptance remains FAIL from an ON fallback-respawn
coordination failure; long 5% stalls also remain. Do not overwrite these scores
with partial startup/battle evidence. All 80 captures in that matrix had clean
shutdown provenance; latest unclean battle captures do not change that fact.

## Resume sequence

1. Read applicable AGENTS and deployment/Lua references. Preserve task branches.
   Use BZRHarness machine lock, BZR_FORCE_WINDOWED=1 and Stop-BZRGame -Id -NoForce.
   The phone RDP display was 600x1284; reuse the qualified reversible private
   renderer/control setup, never normal-install fullscreen experiments. Input
   helpers require Windows PowerShell 5.1, not PowerShell 7.
2. Compare generated marker eligibility/registration with the validated authored
   co-op template and terrain elevation, minimizing changed native fields.
   Add a first-role/update/native-sync gate before issuing probe roster commands
   so startup failure receives its own diagnosis. Avoid increasing timeouts as
   a substitute for fixing startup.
3. Run a validated co-op control using the observability server branch to qualify
   native decision/socket correlation, then retry 20 AI / 45 seconds clean.
   Preserve all source/native/content hashes and restore/audit on each exit.
4. Require actual native combat, natural deaths/scrap and host/guest convergence.
   Then run 40/80 clean and matched 80-unit fix ON/OFF at 3% loss, repeated passes.
   Add equal-population idle/moving controls before attributing growth to combat.
5. Separate follow-ups: scavengers/collection, artillery/projectiles, soak,
   bandwidth caps and multi-PC/WAN. CPU/probe/simulation samples are not FPS.

Battle entry point: `reverse_engineering\Run-BZRBattleLoad.ps1 -Units 20 -Seconds 45`
requires the external private control/deployment setup, not a bare launch.
Local tests: Lua `test_battle.lua` from the battleload directory; Python
`test_prepare_battle_map.py` and `test_report_battle.py` from that directory.
Server tests: `python relay_observability_test.py`, `relay_impairment_test.py`,
`relay_faultinject_test.py`, `relay_pair_ports_test.py`, `network_capture_test.py`,
and `python -m unittest relay_bounded_pair_ports_test`.
