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

`KillMethod = 'fire'` was tried as a more natural kill: c1 gets an AI gunner
that shoots the deployed Splinter. In `mpbugs-spl3-fire-1` and `-2` the gunner
never damaged it (150 health throughout) before the Splinter ran out about
5 s after deploy, so the case stops early with that message. The kill runs
use the default `KillMethod = 'damage'` (Lua `Damage`).

## Fix: `[Fixes] SplinterSync` (default on)

`src/patches/mp_splinter_sync.cpp`. Each peer still runs its own copy, but
the copies now agree on where the Splinter deployed and when it died.

- **Deploy.** The `SprayBomb::Hit` Build call (`005DB37F`) is already wrapped
  for the emitter owner fix. The wrapper now also calls into SplinterSync
  before and after the build. The peer that launched the Splinter broadcasts
  an `SD` message with the bomb's launch key (source and order id, `+0x7C`
  and `+0x7E`) and its deploy position. A peer that receives it moves its own
  copy there (posit at `obj76+0x48`, then `GameObject::UpdatePosition`
  `004DB100`). If the message arrives before that peer has built its copy,
  the copy is built at the launcher's position.
- **Kill.** When a deployed Splinter dies from damage (flags `0x01000000`, as
  opposed to exhaustion, which sets only `0x200`), that peer broadcasts an
  `SK` message with the same key. Every other peer marks its copy dead
  (`0x01000200`) and does not send the kill back. A kill that arrives before
  the copy is built is kept for 60 s and applied when it is built.
- The SprayBuilding destructor (vtable `008881EC` slot 0, `005DA680`) is
  patched to forget a copy when it is freed.

Messages go through `Net::BroadcastSend` (`00575890`). `Net::Receive`
(`00570500`) now goes through a shared tag dispatcher
(`src/patches/net_tag_dispatch.cpp`), which the `ME` mission-end sync uses too.

Limits: a peer that lags still deploys late, though at the launcher's
position. The shards stay per peer and random, so the damage itself is not
synchronized. The large divergence seen without the fix (87.8 m on c2) did
not happen in the runs below, so the move has only been seen correcting
offsets of about half a metre. Unpatched peers neither send nor apply the messages.

Off switch: `[Fixes] SplinterSync = 0`, or
`OPENSHIM_DISABLE_MP_SPLINTER_SYNC=1`. The Weapons case's `-Expect Stock` arm
turns it off. Under `-Expect Fixed`, the case also checks that every peer's
copy ended within 1.5 s of the kill and deployed within 2 m of the launcher's.

## Results with the fix

```
Run-BZRMpBugs.ps1 -Case Weapons -Clients 3 -Expect Fixed -ScenarioArgs @{ Weapon = 'splinter'; KillSplinter = 'receiver' }
```

| Run | Finding |
| --- | --- |
| `mpbugs-spl3-fixed-kill-1` | **Pass.** c1 sent the kill at 18:10:50.805 (log time). c0 applied it 6 ms later and c2 32 ms later. All three copies lived 0.38 to 0.45 s, against about 5 s without the fix. c1 and c2 moved their copies about 0.5 m onto the launcher's position. |
| `mpbugs-spl3-fixed-none-1` | **Pass.** No kill. All three copies deployed within 2 m of the launcher's and ran their full 5.0 s life. |
| `mpbugs-spl3-fixed-kill-2` | Not run: client 0's lobby websocket closed with 1006 before the match (a launch failure, not a Splinter result). |
| `mpbugs-spl3-fixed-kill-3` | **Pass** (the repeat of `-2`). c1 sent the kill at 18:20:03.638. c0 applied it 3 ms later and c2 27 ms later. The copies lived 0.10 to 0.16 s. |
