# Splinter in multiplayer: runs of 2026-10-27

Players report two Splinter problems in multiplayer. Each guest seems to get its
own copy, so the damage escalates. A deployed Splinter also cannot be destroyed.
The Weapons case of `Run-BZRMpBugs.ps1` now tests both, with three clients. The
static analysis is in [MPAUTH_SPLINTER_STATIC_ANALYSIS.md](MPAUTH_SPLINTER_STATIC_ANALYSIS.md).

```
Run-BZRMpBugs.ps1 -Case Weapons -Clients 3 -Expect Stock -ScenarioArgs @{ Weapon = 'splinter' }
Run-BZRMpBugs.ps1 -Case Weapons -Clients 3 -Expect Stock -ScenarioArgs @{ Weapon = 'splinter'; KillSplinter = 'receiver' }
```

`KillSplinter` is `none`, `launcher` or `receiver`. With `receiver`, client c1
calls `BugKillSplinter()` every 200 ms until it finds a deployed Splinter. That
call applies 100000 damage to every live Splinter on c1. The case logs each
peer's `GetTime()` at that moment, so every peer's lifetime can be measured
against the kill on its own clock.

## Results

| Run | Finding |
| --- | --- |
| `mpbugs-spl3-killrcv-1` | **The kill does not propagate.** c1 killed its deployed Splinter (`FEA00017`, 150 health) at 10.48 s, and its copy ended at once. The copies on the launcher (c0) and on c2 ran their full life: they ended 4.42 s and 4.11 s after the kill, at about 5.0 s each. On every peer the object was neither local nor remote. |
| `mpbugs-spl3-none-1` | **Every peer deploys its own copy, and they can diverge.** c0 and c1 deployed within 0.1 m and 2 ms of each other. c2 deployed 87.8 m away, 5.2 s later. One 12 m witness on c2 lost 46.7 health, and nothing on c0 or c1 was hit. A peer that lags the launcher deploys its Splinter somewhere else, and only that peer runs it. |
| `mpbugs-spl3-killl-1` | Not run: client 2 exited before lobby auth (a launch failure, not a Splinter result). |

Why the kill has no effect elsewhere: the deployed Splinter is built by each
peer's own spraybomb simulation, with no network identity. Damage on one peer
reaches only that peer's copy. A player who destroys the Splinter sees it
disappear, while it keeps firing on every other machine. For the units each
of those machines owns, the shards still hit.

Why the damage looks like it escalates: each copy damages the units its own
peer simulates. When the copies sit in different places, the Splinter hits in
several places at once across the match, one per peer that deployed
elsewhere. Each guest adds another copy.

The ring witnesses could not measure the escalation directly. They take
almost no shard damage, and the launcher's target took none: the Splinter
seems to pick targets, not hit everything in range. So the per-ring loss
ratio stays null, and that check is only an observation for now.

## Fix directions (not built)

- **Send the kill.** When a peer destroys a deployed Splinter, broadcast its
  launch identity, and have every peer remove the matching copy.
- **Launcher-authoritative deploy.** Only the launcher builds the deployed
  Splinter, as a networked object. This fixes both the divergence and the
  kill, but it is a larger change to the spraybomb create path.
