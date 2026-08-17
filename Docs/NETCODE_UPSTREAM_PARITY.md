# Netcode parity with PiercingXX/battlezone-netcode-patch

Comparison performed 2026-08-17 against upstream `622fb74` (V5.3), the
`dsound`/`winmm` proxy pair in that repository, its `shared/` header set, and
its `CHANGELOG.md` release history back through V4.9.

Upstream ships **no licence file**. Its findings — addresses, measured values,
observed failure modes — are facts about the game and are used here with
attribution. Its source is not copied: everything below is implemented against
OpenShim's own INI/config layer in OpenShim's own style. Where a behaviour is
adopted the reasoning is restated in our comment, so the code stands on its own
if the upstream repository ever disappears.

## What OpenShim already had

- Governor cold-start poke (`GovernorStart`), signature-gated on the same
  unique 15-byte `.text` pattern.
- The four auto-kick globals, already on the V4.9/V5.2 relaxed preset
  (`60000 / 2000 / 200 / 60000`) — the values upstream converged back to after
  V5.0's tightening ejected a live tester twice in one evening.
- Receive-side packet reordering, wake thread, send duplication, DSCP marking,
  socket buffer floors, raw buffer-log ring, BZRNet WebSocket capture.
- Structured BZRNet trace (`bzrnet_trace.cpp`), which upstream has no
  equivalent of.

## Ported

### 1. The six missing `[Net]` globals

The single largest gap. OpenShim wrote 4 of the game's 10 `[Net]` tunables; the
governor and bandwidth half — `MinBandwidth`, `MaxBandwidth`, `UpCount`,
`DownCount`, `MaxPing`, `MaxPingsLost` — was left to `net.ini`, and upstream
established that `net.ini` does not reliably reach the game: BZLogger reports
`MOD FOUND net.ini` while the values in it are demonstrably not applied, because
only the session's *active* mod is parsed, and a copy in the game folder root is
ignored outright.

Evidence the file was not being applied, from the 2026-08-12 `xxMonke1.bzn`
match: the governor took 54 consecutive `DownCount` steps over 107 seconds and
bottomed out at 4,150 → 4,000 B/s. 4000 is the **stock** floor;
`net.ini` documented 16000. The match then spent its worst two minutes at a
budget an order of magnitude under what the link carried.

New `[OpenShimSocket]` keys in `net.ini`, all under a `NetTune` master with the
same "0 = leave the game's value alone" convention the auto-kick keys use:

| key | default | why |
|---|---|---|
| `NetMinBandwidth` | 16000 | Makes the collapse above survivable, and lifts the floor clear of the 4000 cold-start sentinel |
| `NetMaxBandwidth` | 320000 | Effectively uncapped. V5.0's 64000 sat *below* the 86k–224k B/s the storms measured, so the governor fought real traffic for whole matches |
| `NetUpCount` | 100 | Recovery step |
| `NetDownCount` | 50 | Back-off step. At the old 50/200 the governor fell −203 B/s/s and climbed +40.5 — five to one, so a two-minute collapse needed nine minutes to undo |
| `NetMaxPing` | 450 | Stock 300 turns a jitter spike into a rate cut into more queueing into a bigger spike |
| `NetMaxPingsLost` | 0 (leave alone) | No evidence a change helps |

### 2. Per-global sanity gating

Previously the auto-kick thread wrote its four addresses blind. Each entry now
reads the live value on first contact and **vetoes itself permanently** if that
value is outside a plausible range for the tunable, rather than scribbling on
whatever now lives there. A game update that moves `.data` degrades to "feature
stands down and says so" instead of corrupting unrelated state.

The value found before the first write is logged, which is also how the
phase-dependence upstream documented gets confirmed on our build — several of
these globals read differently at the menu than in-match.

### 3. Cold-start sentinel classification

A real defect in our code, not just a missing feature. `GovernorPatchThread`
poked the target on **every** read of exactly 4000, on the assumption that the
ramp moves off 4000 immediately and never returns to it exactly. The 2026-08-12
collapse falsified that: thirteen minutes into a match the governor walked *down*
onto the sentinel, the watcher read it as a match start, and the rate jumped 10x
mid-fight with nobody asking. Every floor hit was also counted as a match —
upstream's analyzer reported 32 "matches" for an evening that had three.

The sentinel is now classified by how it was arrived at. A match start writes
4000 over a value that has been sitting still; a collapse arrives from within
`kGovDescentBand` (2000 B/s) above it, off a value that lasted less than
`kGovDescentMs` (30 s). Both still get the poke — the alternative is a match that
spends its life at 4 kB/s — but they log and count separately as `cold-start` and
`floor-rescue`, and the rescue is rate-limited so a governor parked on the floor
reports once rather than ten times a second.

It is the *previous* value's lifetime that decides, not the age of the change
into the sentinel: that change is always "just now" whichever thing happened.

### 4. Outbound burst measurement

Nothing in OpenShim measured its own outbound behaviour. Every UDP send path now
feeds a one-second window tracking peak packets/sec, peak bytes/sec, and how many
windows ran above 100 packets/sec (the game's steady rate is ~30). Reported every
30 s and summarised at shutdown, with the trailing window closed first — a burst
that ends the traffic is exactly the case worth catching and would otherwise
never be accounted.

This is the number that separates a healthy session from a storm at a glance:

| | healthy (8-12) | storm (8-15/16) |
|---|---|---|
| peak packets/sec | 175–442 | 1,646–4,186 |
| burst seconds | 3–10 | 283–1,914 |
| packets/session | 27k | 100k–389k |

Measure-only. No pacing or smoothing is applied.

## Deliberately not ported

**The duplicate/retransmit suppressor (`shared/send_dampen.h`).** Upstream ships
it **off by default** and V5.3 reverted the one release that turned it on. The
reasoning is sound and worth recording: a replay of logged sends showed 63.9–69.0%
of datagrams were redundant copies, but a replay has no loss model. The engine's
frame-locked resend is its *only* loss recovery, and on a lossy link the
suppressor cannot tell a redundant copy from the copy that would have delivered.
Suppressed recovery means reliable messages stall, queues back up, the engine
generates more traffic, and the storm feeds itself. OpenShim's own `SendDup` is
disabled for the mirror-image reason.

**Per-peer RTT sampling (`shared/net_rtt.h`).** Genuinely useful — it closes a
loop inside one clock by timing our own sequence numbers against the peer's ack
field, with Karn's algorithm discarding ambiguous samples. Not ported because it
requires committing to a wire-header layout (`ack` at offset 14) that OpenShim's
`bzrnet_protocol.cpp` has not independently confirmed, and a mis-parsed offset
produces plausible-looking numbers rather than an obvious failure. Worth doing
after the header is verified against our own capture.

**Send pacing (`shared/send_pace.h`).** Off by default upstream, with no evidence
yet that it is needed. The measurement half of it is ported (above); the token
bucket is not.

**`MaxPingsLost`.** Left at the game's value by both projects.

## Open caveats, restated

`AutoKickLoss = 200` is very likely unreachable — the write-up for the
2026-08-15 collapse records the scoreboard at 100% loss with nothing kicking,
which is only possible if the loss predicate could not fire at all. Under this
preset **ping is the sole detector, and ping cannot detect a peer whose ping loop
has stopped answering**, so a peer that goes truly dead will sit in the match
until someone aborts. That is a deliberate trade: false kicks were hurting real
players every session, the zombie match has been seen once. `AutoKickLoss = 50`
re-arms the reflex.

The units of `AutoKickLoss` are still unestablished — "200 is unreachable" is
inference from that observation, not a measurement. Settling it is what would let
one preset cover both failure modes instead of choosing between them. The
experiment: host one session with `AutoKickPing = 60000` (disabling the ping
predicate) and `AutoKickLoss = 5`. Healthy players kicked at 5 but not at 50
means the units are percentage.

None of the six new globals has been exercised in a live match from OpenShim. The
addresses and ranges come from upstream's field work; the signature gate and the
per-entry veto are what stand between a wrong address and a corrupted game. The
first live session should be read for `net_globals:` lines — specifically whether
any entry vetoed, and what each global held before the first write.
