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
Maximum mix `battle-load-20261009-131010-mixed160-b16-p128` passed all 32 checks
and native health: 160 vehicles, 16 nav beacons, 128 ammo/repair powerups,
60 sustained simulation seconds and steady-load fraction 1. Host created 198
vehicles, recorded 39 natural deaths, 157 new observed scrap handles, 25 ammo
rises and 36 health rises. Pickup peak was 114; 88 disappeared, without assuming
every disappearance was collection. All four peers converged to zero AI/pilots/
staged extras after measurement. Four clean captures had zero drops/truncation;
128 restored targets independently matched, with no game processes remaining.

The 160 run matched all 57,709 source TX / relay decisions / socket submissions
across 12 links, with no missing outcome, send exception or source-byte mismatch.
Target RX matched 57,651 copies; 58 gaps included seven within broad combat sample
bounds and five in the conservative post-ramp window (three reliable, two
unreliable). Fifty followed the final RX on the target P2P socket generation;
causality remains unresolved. Complete binary RX also lacks the missing bytes.
Queue wait p95 0.113 ms/max 0.420 ms; send call p95 0.043 ms/max 0.241 ms.
Submission is not proof of delivery or game acceptance.

The sampled post-ramp window spans 55.0 seconds: 543.8 kbps relay ingress versus
148.9 kbps empty-map idle, excluding UDP/IP headers. Host CPU averaged 1.03 core
over the broader combat samples, versus 0.38 in the 80 run; simulation/wall ratios
remained 0.999–1.001 across the four clients. Different object populations,
nondeterministic combat and shared-PC/RDP conditions limit causal comparisons.
Viewed 160 combat screenshots were black or stale/partial lobby surfaces;
PrintWindow images do not qualify visual rendering or FPS. Gameplay evidence
comes from native probes/captures. No cascading gameplay/network failure was
observed in this clean run; impaired battles, WAN, rendering and soak remain open.


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
| `BZR-OpenShim-battleload` | `agent/network-battle-load` | mixed-object implementation `2f9e2914`; prior startup/audio `6cc3abf6`, based on co-op `34a3b799` |
| `Battlezone98Redux_DedicatedServer-observability` | `agent/network-startup-observability` | `fcc350dde528d0f7348a75c75a459ee474fd8848`; based on relay impairment `2c1522f` |
| `BZR-OpenShim-netfix` | `agent/net-impairment-matrix` | previous qualification `9856af9c`; mixed 40/80 evidence checkpoint `d44e13c4`, followed by this maximum-load update |

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
and mixed 40/80/160 native runs passed. Source/content hashes are retained privately.

## Previous accepted evidence to retain

The objective/services A/B matrix is still
`C:\BZRCoop\runs\netimpair-matrix-20261009-091255` (20/20 scored).
Independent comparison:
`C:\BZRCoop\runs\network-qualification-control-20261009-071830\comparison.md`.
Fix ON gameplay passed 9/10, stock 5/10. Modeled blackout was lower in all
matched cases, but overall acceptance remains FAIL from an ON fallback-respawn
coordination failure; long 5% stalls also remain. Do not overwrite these scores
with partial startup/battle evidence. All 80 captures in that matrix had clean
shutdown provenance; the historical unclean startup captures do not change that fact.

## Resume sequence

1. Read applicable AGENTS and deployment/Lua references. Preserve task branches.
   Use BZRHarness machine lock, BZR_FORCE_WINDOWED=1 and Stop-BZRGame -Id -NoForce.
   The phone RDP display was 600x1284; reuse the qualified reversible private
   renderer/control setup, never normal-install fullscreen experiments. Input
   helpers require Windows PowerShell 5.1, not PowerShell 7.
2. Latest maximum mixed 160 control `131010` is complete and restored. Verify
   latest pointers/status and no active game before another launch. Preserve
   failed `124452` separately from passed mixed 40/80/160 evidence.
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
## Battle loss continuation — 2026-10-09

Planned repeated A/B: 80 vehicles, 16 nav beacons, 64 ammo/repair pickups,
60 sustained simulation seconds, 3% relay loss with seeds 12 and 112, alternating
fix ON / stock OFF. Native arm logs and complete captures are required; relay
model blackout is separate from observed native gameplay/acceptance.

First control `battle-loss-control-20261009-132800` stopped after its first ON
run: host co-op readiness remained false for 120 seconds despite completed
native sync, four valid player handles and ready guests. Impairment was never
applied; no combat ran. Retain **INCOMPLETE**, not impaired acceptance. All
41,599 decisions/submissions/source TX matched on 12 links; no host RX gap in
first five simulation seconds. This does not explain admission state. Four
captures closed cleanly; all 128 restored targets independently verified.
Raw admission fields are now collected on a roster-readiness timeout.
Diagnostic matrix `battle-loss-control-20261009-135530` stopped after the third
arm hit another pre-impairment admission failure; see the continuation below.

Earlier services fallback failure `netfix-on-four-services-i4-p1-20261009-081632`
assigned relative +8-second deadlines independently, spreading deaths by about
0.8 seconds. A 1-second outage overlapped deaths; c0–c2 placed near the old c3
replica, while c3 used the rally. This supports a test-coordination/stale-replica
ambiguity, not a proven send-fix regression. Preserve the original FAIL.
The separate `misn05-four-services-diagnostic.ps1` scenario arms and acknowledges
one absolute simulation deadline before release. Bounded candidate snapshots
bracket the original respawn Update, with native lives and handle transitions;
no selection policy changes. Observed handle age is not private eligibility
age, and a shared deadline does not prove peers observed every death in time.
Local Lua tests pass deadline/release guards, life/handle transitions, bounded
pagination, vector encoding and callback restoration; PS5.1 syntax passed.
The native diagnostic launched at 14:14 CDT; see the continuation below.

## Loss-pair checkpoint and handshake logging - 2026-10-09 14:14 CDT

Matrix `battle-loss-control-20261009-135530` stopped after 3 of 4 planned arms.
First ON/OFF pair (seed 12) completed 80 AI, 16 beacons, 64 powerups and 60
sustained simulation seconds. Both gameplay and cleanup passed; both native
health checks failed from sustained sequence rejection. Scorer `IMPAIRED_OK`
means complete impaired gameplay evidence, not native-health acceptance.

Equal 55.371-second conservative post-ramp windows give modeled blackout
0.6334 versus 17.1155 seconds per directed-link minute, fix ON versus stock;
worst modeled intervals 558 versus 4,125 ms. The model preserves pre-window
sequence state and uses relay decisions/scheduled delays, not observed native
acceptance. Native logs independently show sustained rejection on 1 versus 11
of 12 directed links during post-ramp combat. This is one completed pair;
same configured seed with differing traffic is not the same packet-drop schedule.
The repeated comparison remains incomplete and previous 20-run services FAIL
and 9/10 versus 5/10 gameplay totals are unchanged.

Exact relay audits: ON 57,224 decisions, 1,719 intentional drops, 55,505
forwarded/submitted; OFF 47,305 decisions, 1,417 drops, 45,888
forwarded/submitted. Source TX bytes and every submission match across 12
links, with four clean complete captures each. Additional target RX deficits
excluding intentional drops are 86/87; 80/72 occur beyond target final P2P RX.
Conservative post-ramp deficits are 1/11 (ON reliable; OFF 9 unreliable,
2 reliable). Duplicate identical expected copies can establish a deficit
without uniquely identifying which occurrence was missing. Submission is
not delivery. Private raw captures and phase-aware audits stay outside Git.

Third ON arm (seed 112) never applied impairment or ran combat. Host had all
four valid handles; one guest (team 4) had protocol version 1 but ready=false
on host, while all three guests reported ready and missionStarted. No native
RX deficit occurred in first five simulation seconds. Preserve INCOMPLETE:
these flags suggest a readiness-reset/handshake ordering race, not proof of
packet loss. Four captures clean; 41,609 forwarded/submitted match source TX,
64 additional RX gaps, 49 beyond target final P2P RX. All 128 original targets
independently restored with zero mismatch and zero remaining games at 14:11.

The test-only CRFlowProbe now logs before/after Initialize, player callbacks,
Q/K Receive and MarkMissionStarted, with raw readiness/protocol/handle fields
and native hosting/team. It avoids identity getters that resolve/cache IDs or
refresh registry handles. Observations are guarded; original callbacks run
once, preserve nil-bearing result tuples and propagate original errors.
Lua 5.1 probe regression: 33 checks passed, including observer-failure isolation.
No CR admission or respawn selection policy was changed.

Native `respawn-fallback-commondeadline-20261009-141300` launched under control
`respawn-diagnostic-control-20261009-141300` at 14:14 CDT with unchanged policy.
All owners acknowledge one held deadline, then the outage generation is reset
and a new common deadline targets its first drop interval before release.
Actual native kill/life timestamps and relay drop timestamps must confirm
alignment; a configured deadline alone cannot qualify overlap. Keep its final
verdict and restoration pending until the controller exits.

## Synchronized fallback diagnostic - 2026-10-09 14:19 CDT

`respawn-fallback-commondeadline-20261009-141300` completed **PASS**, 14 steps,
24 checks, native rejection-health pass, clean shutdown and independent
128-target restoration (zero mismatch, zero games remaining). Fix ON was
verified; no admission or respawn selection policy changed. This separate
reproduction does not overwrite the earlier sequential-deadline FAIL.

All owners acknowledged deadline 77.585 simulation seconds. First kill times
77.615 / 77.614 / 77.614 / 77.616 span 2 ms, and all native life decrements
were observed at 77.647. Logged task completion at 14:18:01.378820-01.379820
CDT places deaths inside the aligned relay outage: 461 drops on all 12 links,
14:18:00.943473-01.884028. Wall mapping of the first kill is approximate
(one simulation frame before the task completion log), with ample overlap.

At the life decrement all clients still observed old remote pilots alive.
At placement 79.648-79.680, clients 0-2 saw invalid/nil old remote handles;
client 3 saw new live handles with observed unchanged age zero. All four
correctly chose rally (respawns=2, livesLeft=3), consistent with the service's
existing eight-second stable-handle eligibility rule. Observed age is not its
private timer. Common deaths do not imply instantaneous replica convergence.
This supports the earlier test timing ambiguity; it does not prove the old
failure had no product contribution or qualify all outage timing offsets.

Diagnostic observation had zero errors or transition drops, retaining all 12
transitions. Bounded periodic rings evicted 0/0/10/20 older samples while
retaining the placement and transition evidence. All four startup traces had
24 complete admission events: Initialize preceded accepted Q/K; no premature
acknowledgement/reset race reproduced in this launch. Earlier ready=false
failures still require their own event-order reproduction.

Continuation `battle-loss-continuation-control-20261009-142000` launched at
14:19 CDT with only the remaining seed-112 ON/OFF pair, indices 3/4. Run names
end in `142000`; previous `135530` failure is retained. Both continuation arms
use the same updated passive admission logger. Its latest Lua 5.1 suite has
34 checks, including explicit observer errors and exact return-value count.
Input provenance now includes probe SHA256; diagnostic metadata includes helper
SHA256. The first diagnostic's supplemental private provenance records the
probe byte match on all four instances and the metadata-only scenario change
between the pre-launch hash snapshot and execution. Inspect active status
before any further launch; continuation comparison and restoration are pending.

Independent diagnostic relay audit: 65,641 decisions = 60,817 forwarded and
submitted + 4,824 intentional outage drops across all generations. All 12
links match exact source TX bytes, with zero missing outcomes, exceptions or
socket errors. Four clean complete captures; 108 additional target RX deficits,
99 beyond final P2P RX and 9 earlier. None lies within the aligned outage to
placement window after intentional drops are excluded. Queue wait p99/max
0.165/267.886 ms (maximum before aligned deaths); send call p99/max
0.052/0.755 ms. These qualify capture/correlation, not OS delivery. Callback
restoration has source/finally/no-error execution evidence; direct callback
identity was not queried. Private `respawn-independent-audit.json` and
`admission-startup-audit.json` preserve the exact evidence.

## Completed paired battle comparison and analyzer correction - 2026-10-09

Latest state: both completed pairs are archived; no controller or game is
active. Continuation `142000` completed at 14:28 CDT. Its 128 restored targets
were independently rehashed at 18:04 CDT: zero mismatch and zero games.
Private `battle-loss-combined-20261009-142000` joins the four completed arms;
it retains source-control paths and the two INCOMPLETE startup attempts.
This is a completed paired comparison, not an uninterrupted four-run matrix.
The second pair uses passive admission logging in both arms. Native DLL,
server.py and battle workload bytes remain matched across completed arms.

| 3% loss seed | Matched post-ramp seconds | ON/OFF gameplay | ON/OFF rejection-frequency gate | Modeled blackout seconds/link-minute ON/OFF | Worst modeled blackout ms ON/OFF |
|---|---:|---|---|---:|---:|
| 12 | 55.371 | PASS/PASS | FAIL/FAIL | 0.6334 / 17.1155 | 558 / 4,125 |
| 112 | 55.544 | PASS/PASS | FAIL/FAIL | 0.5566 / 26.3344 | 714 / 8,563 |

All arms maintained 80 AI and staged 16 beacons plus 64 ammo/repair objects for 60
sustained simulation seconds, then converged on cleanup. Seed-112 ON/stock
recorded 32/29 natural vehicle deaths and 130/128 newly observed scrap handles.
Gameplay acceptance passes; native rejection-frequency acceptance remains
FAIL, so full network qualification is OPEN. The completed 20-run services
matrix retains its original FAIL and 9/10 versus 5/10 gameplay totals.

Native windows wholly within each conservative post-ramp interval affected
1/11 links (seed 12 ON/OFF) and 0/12 (seed 112 ON/OFF). The whole-mission gate
includes other phases. Same seeds with different native traffic do not select
identical packet drops. The replay measures forwarding-based sequence gaps,
not actual application acceptance; CPU/probe samples do not measure FPS.

Seed-112 ON: 56,284 decisions = 54,601 submitted + 1,683 intended drops.
Stock: 50,282 decisions = 48,782 submitted + 1,500 intended drops. Every source
TX byte and socket outcome matches across twelve links, with no correlation
errors, missing outcomes or submission failures, and four clean untruncated
captures with zero dropped capture events per arm. Additional target RX
record deficits excluding intended drops: 106/83; post-ramp 5/11 (ON 3
unreliable + 2 reliable; stock 8 unreliable + 3 reliable). Stock has no gaps
beyond its final target P2P RX, so the earlier runs' late-gap explanation
cannot be generalized. Two stock hashes each expected two copies but retained
one copy in both JSON and binary: a deficit is proven, its exact missing
occurrence is ambiguous. All 83 JSON deficits are also binary deficits; three
other datagrams occur in JSON without a binary match. Preserve this
capture discrepancy as open; complete ring retention is not proof that both
hooks recorded every event. Raw captures and exact deficit audits stay private.

The remaining ON seed-12 five-second frequency window was traced packet by
packet: all 36 rejected datagrams matched source TX, relay forwarding/socket
submission and target wire RX. Its 24 type-0 Drop lines printed expected=0,
but each preceding Received line had a nonzero expected sequence. Replay and
native expected sequences agreed; four short modeled gaps (94/86/120/94 ms)
explain repeated rejection without a continuous five-second blackout.

Server `native_network_health.py` now pairs only adjacent matching
Received/Drop records (same route/peer, sequence, type and complete header,
within 50 ms). It reports actual zero/nonzero/unknown expected counts and
flags-confirmed unreliable rejections. Unmatched records remain unknown.
Legacy fields, gate thresholds and all historical results are unchanged.
Fourteen sanitized regression tests pass; all legacy fields and statuses
match when reanalyzing every completed battle arm. New private diagnostic
reports preserve original native reports/scores. Counted printed-zero
rejections ON1/OFF1/ON2/OFF2 were 1,168/5,503/865/8,921; all paired to nonzero
actual expectations, with no unknowns. A printed zero cannot establish a
sequence reset, and a five-second frequency window is not blackout duration.

Next work: reproduce the intermittent host admission reset with the new
lifecycle trace; qualify lower retry timers (stock 1000/2500 versus 300/800)
with duplicate/bandwidth/ACK-progress checks; test equal-population idle/moving
controls and longer combat/collection workloads. Keep current retry defaults
until that evidence passes. WAN, Steam/Proton and renderer/FPS remain open.

## Retry comparison and admission race continuation - 2026-10-09

The netfix worktree adds `Run-P2PRetryBattleMatrix.ps1`, exact-byte temporary
timer backups/restoration and `score --timers` verification of all four archived
INIs and native apply logs. Stock 1000/2500 and 300/800 ms arms keep the backlog
fix ON, with 80 fighting units, 16 beacons and 64 powerups for 60 simulation
seconds under loss and rate-limited profiles. Native defaults remain stock.

Private attempts `182000` (DX9 device loss during RDP/direct sign-in transition),
`182600` (outer/coordinator nested-lock wait; no games launched), and `183000`
(host admission false before impairment) remain retained and unqualified.
Each outer restoration independently verified 128 targets, zero mismatch,
zero games. The last admission trace proves Q received/ACK sent before host
Initialize, which clears that guest's ready/handle while it stops Q retries.
Independent source-TX/socket-submission/target-RX evidence confirms Q/K arrival.

`Run-BZRCoopMission.ps1 -InheritedLaunchLockOwner` now verifies an explicit
live ancestor, matching environment and held common mutex before the coordinator
borrows the outer lock. KeepRunning/Attach/play are refused in this mode;
normal runs retain coordinator-owned locks. Real-child PowerShell tests pass
held-owner acceptance/wrong-free rejection; Release x86 CTest passes 79/79.
`Run-BZRBattleLoad.ps1 -CoopOverride` stages a private, hashed CRCoop test copy;
the immutable campaign release is not edited. The matrix retains the same
override hash across every arm and fails if it changes.

Canonical CR now guards early Q/K/P until Initialize finishes. Regression
reproduces the old early-ACK race and passes on the fix and respawn-enabled
test variant; registry/misn02b/misn03/misn04 checks pass. New private trial
`retry-battle-control-20261009-193200` / `retry-battle-matrix-20261009-193200`
is active with that exact admission-only diff (override SHA256
`438DA35AAD3EF65A45881784466EFCDE105CEB3C0ED1D22815D885B080880B4E`).
No completed timer comparison yet. Preserve original failed scores; compare
equal post-ramp exposure, duplicates/byte rates and cumulative wire seqB
progress, separately from native acceptance. Results belong in netfix
`p2p_retry_timing_validation_20261009.md`; raw captures remain private.
