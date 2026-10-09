# Network battle-load checkpoint — 2026-10-09

Battle-load update 2026-10-09: the corrected multiplayer setup reaches native
four-client combat. The first 20-unit run failed cleanup of three ejected pilots;
retain that FAIL. The corrected census/cleanup and mixed object creation passed
local tests. Both mixed runs passed all 32 checks and native health: 40 vehicles,
8 nav beacons and 32 ammo/repair powerups (`125735`), then 80 vehicles, 16 beacons
and 64 powerups (`130310`), each sustained for 60 simulation seconds. The 80 run
recorded 23 natural deaths, 100 new observed scrap handles, 15 ammo rises and
15 health rises. All clients cleaned up, four captures closed cleanly with zero
capture drops, and 128 restored targets were independently verified for each run.
Maximum mix `battle-load-20261009-131010-mixed160-b16-p128` is running: 160 vehicles,
16 beacons, 128 powerups. Check its control status before launching another run.

Server observability `fcc350d` matched all 45,774 / 50,585 relay decisions to
byte-identical source TX and socket submissions across all 12 links in the
40 / 80 runs, with no send exceptions or missing outcomes. Target RX gaps were
64 / 54 copies, including 8 / 5 within the periodic combat sample bounds.
Conservative post-ramp windows excluding the finished sample contain 6 / 2 gaps;
the two 80-unit gaps are unreliable. These windows span 55.9 / 56.4 seconds.
Most gaps cluster around socket shutdown; whole-run ratios are not steady-battle
loss rates. Guest shutdown logs include WSARecvFrom 10054 and closesocket 10038;
causality remains unresolved. Submission proves sendto returned, not delivery
or native acceptance. Private phase/socket-aware audits retain exact missing
copies. Battle details and resume instructions are in the battle branch's
`network_battle_load_validation_20261009.md` and `NETWORK_BATTLE_LOAD_HANDOFF_20261009.md`.

Continuation: the generator now uses `MultSTMission`, matching the working
co-op BZN, instead of single-player `LuaMission`. Spawn powerup state is preserved.
The first-update role gate and an opt-in zero-audio-endpoint RDP mode are added.
The phone desktop was subsequently unlocked; startup passed in `124452`.
The latest run includes nav pods and pickups with bounded shared creation budget,
host locality assertions, guest visibility and post-measurement cleanup.

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

## Retained failed startup evidence and recovery

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
of an already-selected map. The earlier generator normalized mass_inv to 0
instead of the template's 1e30; that extra edit has now been removed.

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

Continuation controls: `battle-control-20261009-123027` stopped after client 0
authenticated because RDP has zero active render audio endpoints. No map/battle
phase ran; client exited gracefully and files restored. Control `123310` stopped
at locked-desktop preflight, before deployment; no corresponding smoke run exists.
The failed auth run selects server fcc350d but cannot qualify native correlation.
Retain both setup failures separately.

Completed first combat: `C:\BZRCoop\runs\battle-load-20261009-124452-smoke20`.
Control `battle-control-20261009-124452` restored 128 targets, independently audited.
Host observed 509 health-decrease samples, 678 ammo-decrease samples, 27 vehicles
created, 7 deaths and 28 unique observed scrap handles. Original peak23 includes
ejected pilots, so is not a pure vehicle metric. All combat/guest checks passed;
cleanup failed with aspilo×1/sspilo×2 alive. Keep overall FAIL. Its full reports,
clean native logs, relay-correlation-audit.json/.md and 71-gap packet details
remain private in the run directory. Submitted p95 queue wait 0.105 ms/send call
0.042 ms. All 120 periodic audio samples had muted sessions; this run's audio
evidence passed. Earlier zero-endpoint preconditions were separate failures.

Mixed workload implementation: up to 16 `apcamr` beacons and 128 alternating
`apammo`/`aprepa` pickups, sharing a maximum of four creations per 0.25 simulation
seconds with vehicles. No scripted damage or refill. Host locality is asserted;
all guests must see both object families. AI vehicle census excludes ejected
pilots. Cleanup snapshots all reserved-team craft before removal, then removes
surviving staged extras while preserving human observers. Local regressions
and mixed 40/80 native runs passed. Source/content hashes are retained privately.

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
2. Check maximum mixed 160 control `131010` first; do not interrupt its clients
   or launch another session. Review combat, beacon/pickup visibility, locality,
   cleanup and native capture/correlation results. Preserve failed124452.
3. Require the pilot/extra cleanup regression to converge on all four peers.
   Preserve all source/native/content hashes and restore/audit on each exit.
4. After maximum mixed 160, run matched 80-unit fix ON/OFF at 3% loss with
   repeated passes. Separate runs retain each verdict.
   Add equal-population idle/moving controls before attributing growth to combat.
5. Separate follow-ups: scavengers/collection, artillery/projectiles, soak,
   bandwidth caps and multi-PC/WAN. CPU/probe/simulation samples are not FPS.

Battle entry point: `reverse_engineering\Run-BZRBattleLoad.ps1 -Units 20 -Seconds 45`
requires the external private control/deployment setup, not a bare launch.
The phone control enables `-AllowNoAudioEndpoint` to tolerate zero render
endpoints if they recur. Completed combat runs observed available, muted sessions
and qualified their audio evidence. Actual zero-endpoint samples mark audio
timing unqualified; available sessions are still muted. Missing sessions with active endpoints still
fail. Preserve this audio condition for subsequent battle CPU controls; do not
compare it directly with prior audio-enabled CPU measurements.
The final evidence checker retains complete clean-capture gates, rejects missing
audio provenance/samples and persisted watcher errors, and reports audio timing
separately. Watcher failures are recorded before throw; mission polling detects
coordinator exit while unexpected clients remain alive. Eight sanitized evidence
tests pass with Windows PowerShell 5.1. Audio is sampled every five seconds,
not continuously monitored. Run `reverse_engineering\Test-BZRCoopDiagnosticEvidence.ps1`
with Windows PowerShell 5.1 for those gates; it launches no game.
Local tests: `lua test_battle.lua nbattle.lua` from the battleload directory; Python
`test_prepare_battle_map.py` and `test_report_battle.py` from that directory.
Server tests: `python relay_observability_test.py`, `relay_impairment_test.py`,
`relay_faultinject_test.py`, `relay_pair_ports_test.py`, `network_capture_test.py`,
and `python -m unittest relay_bounded_pair_ports_test`.
