# Network impairment qualification, 2026-10-09

## Completed: the 20-run loss/burst comparison

Final continuation: `C:\BZRCoop\runs\netimpair-matrix-20261009-091255\summary.md`,
20/20 scored, **acceptance FAIL**. Fix ON passed gameplay in 9/10 runs; stock
passed 5/10. The one ON failure is the services fallback-respawn assertion
under `outage=1000/20000,seed=13`; do not erase it or call the matrix PASS.

Independent comparison and capture audit:
`C:\BZRCoop\runs\network-qualification-control-20261009-071830\comparison.md`
and `final_capture_provenance_audit_091255.md` (JSON evidence alongside each).
All twenty source scores replay exactly, all twelve directed links per run
were impaired and dropped traffic, and all eighty client captures have exact
shutdown sizes and no ring overflow. All intended ON/OFF patch states match.
No crash or GPU event occurred in the twenty retained gameplay attempts.

| Profile | ON gameplay passes | OFF gameplay passes | Source blackout ON/OFF s/link-minute | Equal-active-window ON/OFF |
|---|---:|---:|---:|---:|
| 1% loss | 2/2 | 0/2 | 0.5198 / 19.1288 | 0.1612 / 29.5568 |
| 3% loss | 2/2 | 0/2 | 1.1008 / 24.0738 | 1.1822 / 28.7135 |
| 5% loss | 2/2 | 1/2 | 2.6801 / 20.7726 | 3.2923 / 25.1444 |
| 1 s / 20 s outage | 1/2 | 2/2 | 1.4003 / 10.1170 | 1.9014 / 11.0118 |
| 200 ms / 5 s outage | 2/2 | 2/2 | 1.4009 / 21.9860 | 1.7987 / 25.0221 |

The no-worse blackout criterion passes for every profile and every matched
case, for both source and equal-exposure supplements. This supports a better
complete-session result with the fix, not isolation of impairment-triggered
damage: eight OFF runs already carried blackouts into the impairment window.
Four failed OFF controls have only 16.7-33.2 seconds of active impairment;
equal exposure clips later ON behavior. There is one seed per profile/case,
all ON runs precede OFF, and identical seeds do not impose identical loss
decisions when traffic differs. Health was PASS in 6/10 ON and 0/10 OFF runs;
health failure remains reported separately from impaired gameplay acceptance.

The fresh ON win case at 5% loss had a 14.391-second active c0-to-c2 blackout
(08:49:02.836-08:49:17.227 Central), and a concurrent 13.583-second c0-to-c3
interval. Accepted-update silence reached 14.469 seconds. These recovered
before mission success. This is a repeat of the long loss-case behavior seen
on the full console; improving average blackout time does not eliminate it.

Focused c0-to-c2 trace/native-log diagnosis shows a recovery cascade, not a
single packet missing for fourteen seconds. Reliable sequence 582 was dropped
at 08:49:02.822 and resent/forwarded 116 ms later. During the modeled blackout
the receiver advances through 293 reliable sequences (582-874), while rejecting
785 unreliable updates. Native logs also show reliable 604 rejected while
expecting 582 and 651 rejected while expecting 604. Some subsequent head
sequences had originally been forwarded but require another retry after the
earlier hole; eleven head-wait stages last approximately 1.02-1.12 seconds.
Repeated relay loss contributes too. Retry bursts are typically 1190-1243 wire
bytes / 19-25 fragments, consistent with a bounded retry-drain path. The relay
cannot prove when the sender processed each ACK or which retry-pump branch ran;
this is not proof of a new sender-starvation bug.

The ON fallback failure shows a death-coordination/visibility race: four owner
deaths spanned 749 ms across a one-second outage. The host chose BZRCoop4 as a
living teammate 591 ms before logging that player's death. The harness arms
separate client-local deadlines, waits for native life decrement rather than
completed placement, then assumes everyone used the rally. The product policy
prefers a locally living teammate and has no acknowledged all-dead barrier.
An instrumented common-deadline reproduction is needed before attributing
this result to the backlog fix. `lastRespawn.pos.valid=false` is a vector
serialization limitation in the probe, not proof of invalid player placement.
The matching stock retry passed this check; the ON failure remains FAIL.

The original phone matrix `081632` stopped at run 14 before impairment when
the host landed on Mods instead of the lounge. Its failed attempt is retained.
The final continuation carries scores 1-13 byte-for-byte and records an
explicitly renamed fresh run-14 retry; runs 15-20 were then completed.
Control: `C:\BZRCoop\runs\network-qualification-control-20261009-091255`.
All 128 backup targets/absence states independently match after restoration;
the install renderer retains its original hash and no game remains running.

## Completed: the tooling qualification

Four internal windowed DX9 GOG clients, private loopback relay, fix ON,
stock 1000/2500 ms reliable retry timers, scenario
`misn05 four-services Override=misn05-coop`, profile `loss=3,seed=12`.

Evidence: `C:\BZRCoop\runs\netimpair-matrix-20261009-020111\summary.md`.
The score is `IMPAIRED_OK`, matrix acceptance PASS (1/1). All 14 scenario
steps completed. Gameplay and capture checks passed; the generic native-health
check failed and remains reported, as expected when intentional loss causes
sequence rejection. No crashes or GPU driver events were recorded.

- Final counter snapshot: 40,037 matched, 1,240 dropped (3.097% loss).
- Complete trace: 47,966 impaired datagrams, 1,464 drops (3.052% loss).
  The trace continues after the counter snapshot through graceful shutdown.
- All twelve directed links had matched traffic and dropped datagrams.
- All four captures shut down cleanly with zero dropped capture events.
- Receiver replay: 3,995 future-stamped rejected updates; 124 rejection
  blackouts totaling 16.806 link-seconds; ten at least 500 ms; maximum
  2,631 ms on c3 to c2. Independent replay reproduced every saved link score.
- The reported normalized rate is 0.7406 blackout seconds/link-minute. Its
  denominator uses the complete 113.459-second trace, including approximately
  24.58 seconds before impairment. Independent replay clipped to the
  pre-shutdown impairment counter snapshot measures 84.246 seconds of active
  impairment, 8.844 blackout link-seconds (0.524891 s/link-minute), and a
  907 ms maximum. Whole-trace and active-window metrics answer different
  questions; shutdown traffic remains in the original scorer's values.

These blackouts model sequence rejection, from the first future-stamped
unreliable update to the next accepted update. They do not measure all silence
caused by loss or directly measure displayed player motion. One fix-ON run
qualifies the tooling; it does not establish superiority over the OFF control.

## Setup findings and sweep status

Instance0 retained an incomplete DX9 video-mode name and a single-player
bookmark from prior DX11 testing. The run wrapper backs up and normalizes the
DX9 mode and disables `[Startup] AllowStartupAutoLoad` in all four instances.
It deploys the complete matching OpenShim load chain using the repository
deployment script. These changes are temporary and restored with SHA-256
verification. The first two attempts failed before applying impairment.

On the unlocked full console, the `071841` attempt again loaded the old
single-player bookmark: the native bookmark check ran before the asynchronous
startup suppression installed. The next wrapper therefore also backs up and
temporarily removes `Save/auto.sav`, `Save/auto2.sav` and `auto.label.txt`, and
sets `[AutoSave] Enabled=0` in the disposable clients. Existing slots are restored
and newly created slots removed at completion. No native build changed.

Fresh sweep: `C:\BZRCoop\runs\netimpair-matrix-20261009-072736`.
Control, verified backup manifest and restoration status:
`C:\BZRCoop\runs\network-qualification-control-20261009-072725`.
All ten fix-ON runs completed `IMPAIRED_OK` with gameplay PASS, complete
captures, and no crash/GPU event. At the first stock launch, the user connected
by phone RDP and the mode changed to 600x1284. The four clients crashed in
renderer startup before impairment; run 11 is `INCOMPLETE` and the matrix
stopped with its ten completed ON runs preserved. The wrapper restored and
verified its files. This matrix cannot establish an ON/OFF comparison.

The ON win case at 5% loss had a genuine in-mission modeled update blackout:
c0 to c2, 12.936 seconds (07:59:34.994 to 07:59:47.930 Central), plus a
concurrent 10.842-second c2 to c0 interval. Native receive rejection corroborates
both links. The longest accepted-update gap was 13.068 seconds. Both recovered
before mission win and the counter snapshot; this is not a shutdown artifact.

The temporary minimum-width renderer adaptation subsequently qualified on the
phone RDP session: `C:\BZRCoop\runs\netimpair-matrix-20261009-081107`, PASS,
all 14 steps and 22 checks, no crash/GPU event, twelve impaired links, all four
captures complete. Snapshot loss was 3.0965%; active-window maximum blackout
314 ms, rate 0.504085 s/link-minute. All four actual client areas and all 172
archived screenshots measured 1008x720 on the 600x1284 desktop. The original
renderer SHA-256 `822d26ca4b9cce82ddd2fca5e31e7d3a0cd8d05032130a987830143e3d0f95e1`
became `39a5fc90c8a7545c523901a5b6c1a9e62ca237730d0bfce58ae1120a12bd7bc4`
in the four disposable copies only. The wrapper restored and verified them.

A fresh matched 20-run sweep started under that qualified setup:
`C:\BZRCoop\runs\netimpair-matrix-20261009-081632`, control
`C:\BZRCoop\runs\network-qualification-control-20261009-081629`.
Both ON and OFF arms use the same renderer adaptation and window setup;
Original full-console ON results remain separate evidence. The completed
continuation and acceptance limits are documented above.

Draft tooling PRs opened after qualification: OpenShim matrix/scorer
[#417](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/417),
four-client harness
[#418](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/418), and
DedicatedServer impairment
[#8](https://github.com/GrizzlyOne95/Battlezone98Redux_DedicatedServer/pull/8).
The matrix is stacked on #415; the server is stacked on the published
`agent/relay-bounded-pair-ports` branch.

The 20-run loss/burst sweep was started after qualification at
`C:\BZRCoop\runs\netimpair-matrix-20261009-020541`. Its first client failed
before authentication, and the matrix stopped at 1/20 INCOMPLETE. This is an
infrastructure failure, not an impaired-network result: the desktop changed
from console to a 600-by-1284 RDP display. Direct3D9 advertises only that mode;
the shipped Ogre renderer filters out modes narrower than 640 pixels.

A subsequent exact-mode retry also failed before applying impairment.
At that point the session disconnected/locked; it was later resumed as above.
No session transfer or physical-screen unlock was performed.

Private control scripts, backup manifest, restoration status and setup logs:
`C:\BZRCoop\runs\network-qualification-control-20261009-015153`.
A guarded, reversible renderer adaptation is prepared there to lower only
Ogre's two display-mode minimum width comparisons from 640 to 512 in the
four disposable renderer copies when the active display is narrower than 640.
It was later qualified in the separate phone-display run described above.
The original install renderer is unchanged. If used, its original/patched
hashes and scope are written to each run's `display-compatibility.json`;
do not describe those runs as using an unmodified stock renderer.

## Before the dead-peer lane

The live `authenticatedAs` label is `user_id:player_name`, while server
impairment matching accepts the user ID or name separately. The current
`peer-blackout` scenario would match no traffic when given the composite label;
resolve the verified user ID from the private session/server metadata first.
Also preserve expiry counters: the relay clears current counters after `for=`
expires; a long ping wait can otherwise falsely report that nothing dropped.
The `impairment_expired` trace event retains the previous totals.

## Next

Instrument and reproduce the fallback-respawn race with an acknowledged common
deadline, then qualify faster reliable retry timer arms and investigate the
remaining long 5% loss blackouts. Add a measured pre-impairment baseline and
actual relay-send timestamps before isolating impairment-triggered damage.
Client candidates are `1000/2500` versus `300/800` (optionally `150/400`), with
duplicate/bandwidth-cap checks; bounded future-reliable buffering may avoid
retransmitting fragments already delivered ahead of an earlier hole. Preserve
sequence/application ordering and wire compatibility. Add queue age, retry-burst
and ACK-progress diagnostics before altering the retry budget. Server tooling
should retain expired impairment-generation counters and expose unambiguous
peer IDs so dead-peer tests cannot silently match nothing.
Retry/reorder defaults remain unchanged; lower-timer, reordering, dead-peer,
bandwidth, robustness, soak, real WAN and other-platform lanes remain open.
