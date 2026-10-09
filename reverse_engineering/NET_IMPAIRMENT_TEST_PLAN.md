# Network impairment test plan (handoff)

Update 2026-10-09: the four-client 3% loss tooling qualification passed
(`IMPAIRED_OK`, gameplay PASS, complete captures, no crash/GPU event).
The 20-run sweep initially stopped before impairment when the desktop
changed to a 600-pixel-wide RDP mode; the session later disconnected. It later
completed ten fix-ON runs on the full console in `netimpair-matrix-20261009-072736`,
all gameplay PASS / `IMPAIRED_OK`, before phone RDP interrupted the first stock
launch. A separate phone-display qualification passed, and a fresh matched
20-run sweep is running in `netimpair-matrix-20261009-081632`. Stock comparison
and full acceptance remain pending. Draft tooling PRs are #417/#418 in OpenShim
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

None of these branches has a PR yet. Open them once a live run has
qualified the tooling.

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
   refuses. Force-killing `C:\BZRCoop` test instances is fine; never kill
   the GOG or Steam game without asking.
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
