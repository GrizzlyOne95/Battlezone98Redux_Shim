# Multiplayer battle-load qualification — 2026-10-09

Status: native startup and natural combat now run on all four clients.
Mixed 40/80/160 battles passed, including beacons, pickups and complete cleanup. The first combat run's cleanup FAIL
remains separate evidence. This extends
the objective/services impairment suite with natural AI combat and object churn.
It does not change client retry timers, packet ordering, or server defaults.

## Reproducible scenario

`Run-BZRBattleLoad.ps1 -Units 40 -Seconds 60` stages `nbattle.bzn` over the
repository's authored `lcbench` terrain. Requires the four prepared private
`C:\BZRCoop\instances` clients, EXU/CRCoop content, windowed rendering and the
existing private network control setup. It is a separate multiplayer test map,
not a campaign mission with objectives skipped. The normal game install and CR
source/content remain unchanged.

- Humans on teams 1–4 observe two host-owned AI armies on reserved teams 5–6.
- Tanks/fighters use native `Attack` AI, ordinary health/ammo and natural deaths.
- Four units spawn per quarter-second into distinct vacant army slots; retarget
  only when the victim dies. Requested duration starts after the full population
  first assembles; ramp has a separate 30-second limit.
- Replacements sustain the requested load; maximum 160 active and 640 cumulative
  spawns prevent an unbounded test. Scrap is left to native gameplay.
- No scripted damage, kills, health/ammo refill, or removal during measurement.
  Removal is a separate post-measurement host cleanup/convergence check.
- Each client samples AI/scrap counts. Scrap uses exact `classLabel == "scrap"`
  over `AllObjects`, including zero-health pieces. `scrapObserved` is unique
  census-observed handles within 600 m of the arena, not an exact native creation
  total. Baseline handles are excluded. Measured peaks freeze at workload end.
- Host evidence must include ammo consumption, damage, deaths and natural scrap.
  Requested load must reach 75%; at least 75% of steady host samples must retain
  that load. Guests must observe both armies, at least 50% load and new scrap.
- Opt-in `-Beacons 8 -Powerups 32` stages native `apcamr` nav pods and alternating
  `apammo`/`aprepa` pickups. Caps are 16 beacons and 128 pickups. Extras and AI
  share the four-creations/quarter-second budget. Spawn ownership is asserted;
  all guests must observe extras. Native pickups may replenish health/ammo;
  their disappearance is not proof of collection. Metrics record natural rises.
- Vehicle census now counts the four tested vehicle ODFs separately from
  ejected pilots. Post-measurement cleanup snapshots all reserved-team craft
  before removing them, including native pilots, plus surviving staged extras.

Evidence: `battle-samples.jsonl`, `battle-summary.json`, `flow-summary.json/.md`,
four-client screenshots, archived native captures/logs, relay/protocol traces,
native-network-health report and hashed source/content/display provenance.
CPU totals, working set, simulation clocks/update counts and probe command
latency are diagnostics, not renderer FPS. Four processes share one machine;
no WAN, multi-PC, or independent GPU performance acceptance is implied.

## Progress and runs

| Run/control | Result | Meaning |
|---|---|---|
| `battle-control-20261009-100420` / `battle-load-20261009-100420-smoke20` | preflight stopped | Harness only accepted missions already in campaign content. No game launched; 128 backed-up targets restored/verified. Preflight now accepts a mission Lua supplied by a valid override. |
| `battle-control-20261009-100650` / `battle-load-20261009-100650-smoke20` | lobby selection failed | All four authenticated. Display name placed the new map below the visible searched rows. No combat started. Display name now sorts first. Restored/verified. |
| `battle-control-20261009-101002` / `battle-load-20261009-101002-smoke20` | native map load failed | All four selected/launched the map; native loader rejected craft-state fields inherited by generated start markers (`battle_spawn1 skipped pilot class`, failed to load game files). Replaced the marker with the validated authored co-op `pspwn_1` template. No combat started; restored/verified. |
| `battle-control-20261009-101530` / `battle-load-20261009-101530-smoke20` | lobby selection failed | New map was already selected; harness required a changed settings version and then walked away from it. Missing/comma-only vehicle descriptions also appeared. No combat. Independent review found marker-coordinate regexes also overwrote orientation/velocity; fixed before the next launch. Restored/verified. |
| `battle-control-20261009-102214` / `battle-load-20261009-102214-smoke20` | native startup failed | Lobby and map load passed, but all four stayed at frame/time zero in Connecting 1 of 4. Host reported Network Start Sync Failure after 90 seconds. No combat began. Graceful close left four hidden processes; the user authorized terminating only those four PIDs. Independent audit verified all 128 restored targets and zero remaining game processes. |

Continuation runs: `battle-control-20261009-123027` stopped after client 0
authenticated because RDP has zero active render audio endpoints; the client
exited gracefully and files restored. No lobby/map/combat phase ran.
`battle-control-20261009-123310` stopped at locked-desktop preflight before
deployment. No clients launched and no corresponding smoke directory exists.

`battle-load-20261009-124452-smoke20`: corrected multiplayer class progressed
through spawn packets and native sync; four-client roster passed. The 45-second
combat generated 27 vehicles, seven natural deaths, 509 health-decrease samples,
678 ammo-decrease samples and 28 host census-observed new scrap handles. All
three guests saw both armies and new scrap. The original census included pilots
(peak 23), so that peak is not a pure vehicle count. Cleanup failed with one
NSDF and two Soviet ejected pilots remaining. Overall **FAIL**, retained as such.
All 25 checks otherwise passed, native health passed, all four captures ended
cleanly with zero dropped capture events, and all 128 targets independently
verified restored with no remaining clients.

Cleanup/census regression now passes locally, including preserving human
observers and a shared creation budget for 80 vehicles/8 beacons/32 pickups.
`battle-load-20261009-125735-mixed40-b8-p32` passed all five steps and 32 checks:
40 vehicles, 8 nav beacons, 32 powerups, 60 sustained simulation seconds. Cleanup
converged in two seconds. Host observed 23 deaths, 85 new scrap handles, eight
ammo rises and eight health rises; 25 pickups disappeared (not all necessarily
collected). Load fraction was 1. All four native health/capture checks passed;
128 restored targets independently verified. Relay ingress averaged 513.9 kbps
over the 55.9-second sampled sustained window versus 148.1 kbps empty-map idle;
this combines more objects and combat, not an isolated combat cost. Server
45,774 decisions/source TX/submissions matched; 64 target RX gaps remain
unexplained. Private audit preserves them, no zero-delivery-loss claim.

`battle-load-20261009-130310-mixed80-b16-p64` passed all 32 checks: 80 vehicles,
16 beacons and 64 powerups, 60 sustained simulation seconds, load fraction 1.
Host created 103 vehicles, observed 23 deaths, 100 new scrap handles, 15 ammo
rises and 15 health rises. Pickup peak was 61; 47 disappeared, which is not proof
that each was collected. All four peers cleaned up; native health passed and
four clean captures had zero capture drops. Independent restore: 128 targets,
zero mismatches, no games remaining. Relay ingress averaged 527.9 kbps over
56.4 sampled sustained seconds versus 147.6 kbps empty-map idle, with all 12 links.
This changes both population and combat, so it does not isolate combat cost.

Phase-aware audits for mixed 40 / 80 matched every source TX, relay decision
and submitted outcome: 45,774 / 50,585 copies. Target RX gaps were 64 / 54;
only 8 / 5 fell within periodic combat sample bounds. Conservative inner windows
exclude ramp and the final finished sample: 6 / 2 gaps, with the two 80-unit
gaps both unreliable. These are sampled bounds, not exact 60-second intervals.
Most occurred around
socket shutdown. Do not characterize whole-run ratios as steady-combat loss.
Shutdown includes guest WSARecvFrom 10054 and closesocket 10038; causal attribution
remains open. No zero-loss or delivery guarantee follows from submission logging.

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

The Lua fixture passed authority restrictions, bounded frame spawning,
native damage/ammo/death accounting, exact zero-health scrap classification,
and prohibition of cleanup during the measured phase. Additional checks passed
160 distinct initial positions and the 640-creation cap under rapid attrition.
PowerShell syntax and map staging passed. Python map regression verifies all
four native marker bases, translations, zero motion, team/sequence/mission
references, and byte-identical copies of the existing authored terrain.
The report regression also passed twelve-link accounting, drop reasons,
payload-identical retries despite changed headers, CPU/rate calculations and
rejection of missing measurement windows.

## Startup evidence and server logging

In failed startup run `102214`, all twelve relay links forwarded without injected loss;
the host repeatedly sent startup payload `53 53 01`, but the 18-byte `50 53`
spawn-coordinate message and `53 53 02`/`04` progression seen in the validated
co-op control were absent. Native peers remained at SyncInAt/SyncOutAckAt zero.
The generated map inherited single-player `LuaMission` from lcbench, whereas
the working co-op BZN uses `MultSTMission`. Multiplayer initialization assigns
native player spawns; this mission-class difference is the strongest identified
setup candidate. The generator now emits `MultSTMission` and preserves authored
`pspwn_1` spawn powerup state, including mass_inv's zero-mass sentinel. The map
test pins both. The corrected setup passed native startup in `124452`, including
spawn-coordinate packets and first updates on all four clients. This is not an
isolated mission-class-only A/B; no spawn-path requirement or server-delivery
failure has been established.

The roster gate now waits for the first mission-update role event before probe
commands, so native startup stalls receive a direct diagnostic. An explicit
`-AllowNoAudioEndpoint` test option permits muted-client runs with zero render
endpoints. Available sessions remain muted; missing sessions with active
endpoints still fail. Session/periodic logs record endpoint count and audio
timing qualification. The option is off by default; native audio configuration
is unchanged. Zero-endpoint runs cannot qualify audio timing or compare directly
with earlier audio-enabled CPU controls. Local syntax, map, Lua and report checks
pass; the unlocked phone RDP retry reached real combat.
Final evidence still requires complete clean captures and periodic audio
observations. Watcher errors are persisted before exit; a dead coordinator
fails mission polling while clients remain alive. Eight sanitized Windows
PowerShell 5.1 evidence tests pass default mute acceptance, explicit zero-device
audio-unqualified acceptance, and rejection of missing provenance, active-device
missing mute, watcher errors, absent samples and unclean captures. Five-second
audio observations do not prove continuous mute coverage.

DedicatedServer branch `agent/network-startup-observability`, commit `fcc350d`,
adds packet-correlated socket submission events, copy indexes, socket identity,
queue/scheduler delay, send-call duration and submitted/exception/closing
outcomes. Eight focused observability tests and the existing impairment,
fault-injection, bounded pair-port, full pair-port and capture suites passed.
A submitted event proves that
`sendto` returned, not OS delivery or peer acceptance. Opaque payload forwarding
is unchanged. Existing trace writers already flush every record.

Native logging qualification in `124452`: all 46,657 relay decisions match
46,657 submitted socket outcomes and byte-identical source TX captures across
all twelve links. No correlation mismatch, closing skip or send exception.
Queue wait p95 0.105 ms/max 0.304 ms; send call p95 0.042 ms/max 0.169 ms.
Target RX evidence matches 46,586 copies; 71 gaps span gameplay and remain
unexplained, also absent from binary receive evidence. Submission is not proof
of delivery or game acceptance. Private audit/gap artifacts live in that run.
All 120 periodic audio observations had muted sessions; this completed run's
audio evidence passed. Earlier zero-endpoint failures are separate runs.

Private evidence remains under `C:\BZRCoop\runs`; the latest control contains
`independent-restoration-audit.json`. The historical `102214` logs are unclean termination evidence. The completed
combat runs have separate clean captures; preserve each run's provenance.
See [checkpoint handoff](NETWORK_BATTLE_LOAD_HANDOFF_20261009.md) for recovery,
branches, artifact paths and next steps.

## Next qualification gates

Mixed 40/80/160 qualified destruction/scrap, beacons/pickups and host/guest
cleanup in clean same-PC runs. Next run matched 80-unit fix ON/OFF trials with
3% loss. Preserve the clean reference alongside loss runs. Add equal-population
idle/moving-only controls before attributing packet growth specifically to
combat instead of object count. Natural combat is repeatable configuration,
not bit-deterministic native simulation; repeated seeds/passes remain required.
Scrap collection/scavengers, artillery/projectile-heavy armies, sustained soak,
bandwidth caps and real WAN remain additional lanes. Do not claim these passed
from a tank/fighter run.

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
