# Network impairment qualification, 2026-10-09

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
  24.58 seconds before impairment. The impaired interval is 88.901 seconds.

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

The 20-run loss/burst sweep was started after qualification at
`C:\BZRCoop\runs\netimpair-matrix-20261009-020541`. Its first client failed
before authentication, and the matrix stopped at 1/20 INCOMPLETE. This is an
infrastructure failure, not an impaired-network result: the desktop changed
from console to a 600-by-1284 RDP display. Direct3D9 advertises only that mode;
the shipped Ogre renderer filters out modes narrower than 640 pixels.

A subsequent exact-mode retry also failed before applying impairment.
The current session then disconnected/locked. The full sweep remains pending.
No session transfer or physical-screen unlock was performed.

Private control scripts, backup manifest, restoration status and setup logs:
`C:\BZRCoop\runs\network-qualification-control-20261009-015153`.
A guarded, reversible renderer adaptation is prepared there to lower only
Ogre's two display-mode minimum width comparisons from 640 to 512 in the
four disposable renderer copies when the active display is narrower than 640.
It has not yet been used in a completed live run and must be qualified first.
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

On a live unlocked desktop, qualify the current display setup, then complete
the planned two cases by five impairment profiles by two arms (20 runs).
Report gameplay acceptance and the ON/OFF blackout comparison separately.
Retry/reorder defaults remain unchanged; lower-timer, reordering, dead-peer,
bandwidth, robustness, soak, real WAN and other-platform lanes remain open.
