# Network impairment test plan (handoff)

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

Update 2026-10-09: the four-client 3% loss tooling qualification passed
(`IMPAIRED_OK`, gameplay PASS, complete captures, no crash/GPU event).
The 20-run sweep initially stopped before impairment when the desktop
changed to a 600-pixel-wide RDP mode; the session later disconnected. It later
completed ten fix-ON runs on the full console in `netimpair-matrix-20261009-072736`,
all gameplay PASS / `IMPAIRED_OK`, before phone RDP interrupted the first stock
launch. A separate phone-display qualification passed. The matched 20-run
sweep completed through continuation `netimpair-matrix-20261009-091255`: ON
gameplay 9/10, stock 5/10; ON blackout time lower in all profiles and matched
cases. Acceptance remains FAIL due to the ON services fallback-respawn race.
The long 5% loss update stall remains. Draft tooling PRs are #417/#418 in OpenShim
and #8 in DedicatedServer.
See `p2p_network_impairment_validation_20261009.md` for evidence, setup
corrections, display compatibility and dead-peer scenario findings.

Status 2026-10-08: the tooling is built, unit-tested and pushed. No impaired
live run has completed yet. This document is for the agent who runs it.

## Why

The P2P reliable-send backlog fix (`p2p_reliable_send_backlog_20261007.md`,
`p2p_reliable_send_validation_20261008.md`) passed a 36-run four-player A/B
on a clean loopback network. The Steam roadmap still lists these as open:
controlled loss and burst testing, qualifying lower retry timers,
AutoKickLoss and dead-peer behaviour, whether receive reordering helps, and
multi-PC/Steam acceptance. A clean loopback can't answer any of them. The
private relay is on every peer stream of a 4-client loopback run (12
directed links, verified from a matrix run's relay trace), so it can stand
in for a bad network without a packet-filter driver. Installing one would
mean a download and a system change, which needs the user's permission.

## What exists

| Piece | Repo / branch | Commit |
|---|---|---|
| Relay impairment (`relay_impairment.py`, `server.py` hook, `--impair`, `POST/GET /relay/impairment`, `relay_impairment_test.py`, README section) | `Battlezone98Redux_DedicatedServer` `agent/relay-impairment` (on top of `agent/relay-bounded-pair-ports`) | 3bd6d17, 2c1522f |
| Harness: `Run-BZRCoopMission.ps1 -Impair`, `Set-CRFlowImpairment` (BZRCoopMission.ps1), scenario `coopflow/scenarios/peer-blackout.ps1` | OpenShim `agent/four-client-coop` (worktree `Documents\GIT\BZR-OpenShim-coopflow`) | 34a3b799 |
| Matrix `-Impair`/`-Cases`, impairment-aware scorer (delivery-order replay, update blackouts, `IMPAIRED_OK`, `aggregate_impaired`), tests | OpenShim `agent/net-impairment-matrix` (worktree `Documents\GIT\BZR-OpenShim-netfix`, branched from PR #415) | 51c526aa |

Tooling is now in draft OpenShim PRs #417/#418 and DedicatedServer PR #8.
The objective/services suite qualified the capture pipeline; its acceptance
failures and remaining blackout limits are documented above and in the results.

### Impairment spec (relay_impairment.py)

Comma-separated, all keys optional:

- `seed=N`: decisions are deterministic for a given spec, seed and traffic.
- `loss=P`, `dup=P`, `reorder=P`: percent.
- `reorder_ms=MS`: default 30.
- `outage=D/T`: drop everything for D ms out of every T ms. The first outage
  starts T-D ms after the impairment is applied.
- `delay=MS` and `jitter=MS`: each stream stays in order unless `reorder=`
  picks a datagram.
- `rate=KBPS` with `queue=MS` (default 200): a per-player uplink cap shared
  across that player's streams, with tail drop.
- `peer=A|B` with `dir=both|from|to`: user id or BZRNet name.
- `for=S`: clears itself after S seconds.

Example: `loss=100,peer=<name>,for=20` blackholes one player.

The relay trace gets these records:

- `disposition: dropped_impair_<loss|outage|queue>` for each dropped datagram.
- `impairment: {delaysMs, reordered}` for each delayed or duplicated one.
- `impairment_set`, `impairment_cleared` and `impairment_expired` events.

### Scorer additions (p2p_netfix_score.py)

- **Delivery-order replay.** Each link is replayed in the order the receiver
  got it. Relay drops are left out (they already were), and every copy is
  placed at `tsUnixMs + delayMs`.
- **Update blackout.** Runs from the first unreliable update a receiver
  rejects as future-stamped until it next accepts one from that peer. This
  is how long that peer looks frozen.
- **Blackout fields.** Per link: `blackouts`, `blackoutTotalMs`,
  `blackoutMaxMs` and `blackoutsOver500Ms`. Per run: `maxBlackoutMs` and
  `blackoutSPerLinkMinute`.
- **Classes.** A run that passes its gameplay checks under impairment is
  `IMPAIRED_OK`. An impaired run without relay counters, or one where the
  relay matched nothing, is `INCOMPLETE`.
- **Acceptance (`aggregate_impaired`).** Every fix-ON run must be
  `IMPAIRED_OK`, and no stock run may hit INCOMPLETE, CRASH, GPU or
  ARM_MISMATCH. A stock run that fails its gameplay checks counts as
  evidence, not a failure.
- **Summary table.** Per profile and arm: relay drop %, gaps per 1000
  reliable messages, blackout s per link-minute, blackouts of 500 ms or more
  per link-minute, and the longest blackout.

## Before running

1. **A live, unlocked desktop is required.** The first trial
   (`C:\BZRCoop\runs\netimpair-matrix-20261008-114949`) failed with
   "Failed to init 3D hardware acceleration": the user's session 1 was
   disconnected and the lock screen was up. Check with `query session`.
   Never `tscon` the session to the console without asking; that unlocks the
   physical screen.
2. **Never launch while the user's own game runs.** The matrix preflight
   refuses. Stop internal clients through BZRHarness with `-NoForce`. Never
   force-kill the game; prior authorization covered only four historical PIDs.
3. **Instances on DX9.** Use `[Graphics] Renderer=DX9` and `ogre.cfg`
   Direct3D9. DX11 with four clients hits NVIDIA TDRs at mission load.
4. **Load-chain match.** The preflight requires each instance's
   `plugins\openshim.dll` to be byte-identical to
   `BZR-OpenShim-netfix\bin\Release\plugins\openshim.dll`.
   - The Release build there is current (PR #415 tip: the backlog fix and
     D3D11 buffer restore).
   - The instances were put back to their previous DLL (hash 12C7763B44A5,
     backup in `C:\BZRCoop\backups\impair-matrix-dll-backup-20261008`).
   - Back the DLLs up and copy the Release DLL into all four instances again,
     then restore them when finished.
5. **Pass `-ServerRepo`.** Point it at a checkout of `agent/relay-impairment`,
   such as `Documents\GIT\Battlezone98Redux_DedicatedServer-bounded-pairports`.
   The default `Battlezone98Redux_DedicatedServer` checkout is on
   `agent/four-client-relay`, which has no impairment support. The preflight
   rejects a server without `relay_impairment.py`.
6. **Launching from Bash or PowerShell 7.** Run the matrix in Windows
   PowerShell 5.1 with the machine `PSModulePath`. An inherited pwsh module
   path breaks `Get-FileHash`. Pass arrays with `-Command`, not `-File`
   (`-File` turns `'a','b'` into one string):

   ```powershell
   $env:PSModulePath = [Environment]::GetEnvironmentVariable('PSModulePath','Machine')
   & "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -ExecutionPolicy Bypass -Command "& 'C:\Users\iestu\Documents\GIT\BZR-OpenShim-netfix\reverse_engineering\Run-NetfixStressMatrix.ps1' -DryRun -Passes 1 -Only 'four-services','Skipper=host' -Impair 'loss=1,seed=11','loss=3,seed=12','outage=1000/20000,seed=13' -ServerRepo 'C:\Users\iestu\Documents\GIT\Battlezone98Redux_DedicatedServer-bounded-pairports'; exit `$LASTEXITCODE"
   ```

7. **Never contact the official lobby with test identities.** The harness
   uses its own private 127.0.0.1 server; keep it that way.

## Step 0: qualify the tooling (one run)

- **Run.** `-Arms on -Only 'four-services' -Impair 'loss=3,seed=12' -Passes 1`.
- **Check:**
  - The run log prints `[impair] seed=12,loss=3` right after the roster
    check.
  - `relay-impairment-final.json` exists with `matched` above 0 and
    `dropped_loss` at about 3% of matched.
  - `relay-trace.jsonl` has `dropped_impair_loss` rows.
  - The score has blackout fields.
- **If the scenario times out at 3% loss,** that is a finding, not a tooling
  bug. Look at which `Wait-CRFlow` step failed and at the blackout figures
  for the links involved.
- **Also confirm that `peer=` matches.** `peer-blackout.ps1` takes the
  subject's name from `session.json` `clients[].authenticatedAs` (the
  "Authenticated to BZRNet As X" log line). It assumes the server knows that
  string as the user's id, name or player name, which has not been verified.
  The scenario throws "dropped nothing" if the match fails. If it does, read
  `/lobbies` for the user ids and change the label lookup.

## Experiments, in priority order

### 1. Loss and burst sweep, fix ON vs stock

- **Run.** `-Passes 1` (then 2 for anything interesting),
  `-Only 'four-services','Skipper=host'`, `-Impair 'loss=1,seed=11',
  'loss=3,seed=12','loss=5,seed=14','outage=1000/20000,seed=13',
  'outage=200/5000,seed=15'`. That is 2 cases × 5 profiles × 2 arms = 20
  runs, about 2.5–3 h. The previous 36-run matrix took about 3 h.
- **Question.** Does the fix still beat stock under loss, and does it ever
  hurt? Under loss, more reliable messages are in flight while a retransmit
  is pending.
- **Compare.** Blackout s per link-minute, blackouts of 500 ms or more per
  link-minute, and the longest blackout.
- **Expectation.** A lost reliable message costs roughly the 1000 ms first
  retry plus one RTT on that link. Stock also stalls every send behind it.
- **Accept.** Every fix-ON run is `IMPAIRED_OK`, and fix-ON blackout time is
  no worse than stock's in every profile.

### 2. Lower retry timers (needs code)

- **Today.** The timers are `[Network] ReliableFirstRetryMs=1000` and
  `ReliableRetryIntervalMs=2500` (patches.json "P2P Reliable Send Backlog"
  plus two retry-timer entries; `ConfigureP2PReliablePatches` in
  patcher.cpp). The matrix preflight refuses any instance that overrides
  them.
- **Add a timer arm,** for example `-Timers '1000/2500','300/800','150/400'`:
  - Write the keys into each instance's `openshim.ini` per run and restore
    them afterwards.
  - Record the values in `matrix.json` and in each score.
  - Check the active values in each client's `openshim.log`, the way
    `fix_state` checks the fix.
- **Run** the arm under the loss profiles from experiment 1, with the fix ON
  only.
- **Watch for:**
  - Shorter blackouts, without extra duplicate retransmits flooding the
    links (`duplicateReliable` per 1000 reliable messages).
  - Duplicates or extra drops when `rate=` caps the link (add
    `rate=256,queue=200`).
- **Ship a lower default only if** every profile improves and the clean
  (no-impairment) matrix still passes 18/18.

### 3. Latency, jitter and reordering

- **Profiles:**
  - `delay=50,jitter=10`
  - `delay=150,jitter=40`
  - `delay=300,jitter=80`
  - `delay=80,jitter=20,reorder=2,reorder_ms=40`
  - `delay=80,jitter=20,reorder=5,reorder_ms=80`
- **Question.** OpenShim's packet reorder buffer (`net_optimizer.cpp`,
  `enablePacketReorder`, off by default; ring in `include/net_reorder_core.h`)
  was never qualified against real reordering. Run reorder profiles with it
  off and on. That needs an arm like the timer arm, writing the
  `[OpenShimSocket]` keys `EnablePacketReorder` (default 0),
  `EnableAdaptivePacketReorder` (1), `PacketReorderWindowMs`,
  `PacketReorderDepth` and `PacketReorderPeers` (net_optimizer.cpp, around
  line 887).
- **Turn it on by default only if** it cuts future-stamped gaps and
  blackouts under reordering and costs nothing on the clean matrix.

### 4. Dead player and auto-kick (`peer-blackout`)

- **Cases.** `-Cases 'misn05 peer-blackout Override=misn05-coop
  BlackoutSeconds=5', '... BlackoutSeconds=20', '... BlackoutSeconds=60'`,
  both arms, and no `-Impair`: the scenario applies its own.
- **The scenario checks that:**
  - the other three players keep exchanging pings while the subject is dark;
  - everyone reaches everyone again within `RecoverySeconds` (default 60);
  - every client still lists four players.
- **Find:**
  - The threshold where the game drops the subject (AutoKickLoss; its
    units are unknown).
  - Whether the subject's recovery depends on the fix. After a long outage
    the subject's peers all have retransmits pending, and stock holds every
    send behind them.
  - What a rejoin looks like.
- **Use `Subject=2`** as well. A guest losing its link to the host and to the
  other guests may differ by link kind (host to guest was worst in the
  backlog matrix).
- **Native evidence.** Grep each client's BZLogger for player-drop/kick
  lines.
- **Known context.** `Docs/NETCODE_UPSTREAM_PARITY.md` ("Open caveats")
  says `AutoKickLoss = 200` is probably unreachable, so ping is the only
  dead-peer detector and a truly dead peer may never be kicked. Its units
  are unknown. That doc's proposed experiment (`AutoKickPing = 60000`,
  `AutoKickLoss = 5` vs `50`) can now run here: set the host's values
  through the session settings, run `peer-blackout` with a short blackout,
  and see whether and when the subject is kicked.

### 5. Bandwidth cap and the bandwidth governor

- **Profiles.** `rate=128,queue=300` and `rate=64,queue=500`, for all players
  or for one with `peer=`.
- **Question.** `MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md` says
  `Net::AdjustBandwidth @004ddd94` walks down to its floor and never
  recovers. Apply the cap mid-run with `Set-CRFlowImpairment`, clear it
  60 s later, and check whether the native send rate (relay trace bytes per
  second per link) climbs back.
- **Needs a small scenario** (or `-Scenario play` with `-KeepRunning` and
  manual `Set-CRFlowImpairment` calls) to time the cap.

### 6. Duplicates and oversize packets

- **Run.** `dup=5` and `dup=20`. Duplicates must stay harmless: the scorer
  counts duplicate reliables, and gameplay must still pass.
- **Also check** OpenShim's reorder path oversize handling (#369, 64 KiB
  per-thread buffer, `reason=oversize`) with the reorder buffer on.

### 7. Malformed packets (needs code)

- **Needs a relay mode** that mangles a seeded fraction of datagrams to the
  chosen players. Today it never rewrites anything, and the module docstring
  promises that, so add a separate, clearly named mode. Mangling options:
  - truncate to below the 18-byte header;
  - truncate mid-payload;
  - flip bits after byte 18;
  - set impossible sequence numbers.
- **Run** with the receivers' `openshim_crash.log` and dumps watched. Any
  crash is a robustness bug in the native receive path.
- **This is our own clients on loopback only.** Never point it at anyone
  else's game.

### 8. Join/leave churn and a soak

- **Churn.** Guests repeatedly leave mid-mission (WM_CLOSE, as in
  `host-leaves.ps1`) and rejoin. Measure rejoin success and handle/memory
  growth on the host.
- **Soak.** A one-hour 4-player mission (`play` scenario plus a long wait) at
  `loss=1,delay=60,jitter=15`. Track private bytes and handle count per
  client every minute.

## Out of scope locally

- Multi-PC acceptance and real WAN paths.
- The Steam build (the backlog fix is only verified on GOG 2.2.301).
- Proton.

These need the user or other machines.

## Hand-back checklist

- Restore the instance `openshim.dll`s, and any ini keys a timer or reorder
  arm wrote, from your own backups.
- Put each matrix's `summary.md` path and its verdict in
  `p2p_reliable_send_validation_*.md`. Write a dated follow-up for anything
  that changes a default.
- Open PRs for the three branches above once step 0 passes. The server
  branch depends on `agent/relay-bounded-pair-ports` (and that on
  `agent/four-client-relay`); none of them has a PR yet.
- Update the Steam roadmap "Network reliability" entry (`Docs/STEAM_ROADMAP_BBCODE.txt`)
  for each open item closed.

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
