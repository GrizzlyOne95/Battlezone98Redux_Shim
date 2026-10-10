# BZRNet P2P early unreliable receive — 2026-10-10

GOG 2.2.301 (`battlezone98redux.exe`, image base 0x00400000).
Patch: `src/patches/p2p_early_unreliable_receive.cpp`, policy
`include/p2p_early_unreliable_policy.h`, `[Network] EarlyUnreliableAccept`
(default **on** since the 2026-10-10 live matrices; see Decision). Sites registered in
`scripts/patches.json` / `include/patches.h` as `P2P Early Unreliable Drop Log`
and `P2P Early Unreliable Deliver`; both signatures are unique in the shipped
image and installed together or not at all.

## Why: the receiver half of the stall

`p2p_reliable_send_backlog_20261007.md` fixed the sender-side gate that kept a
busy link permanently stalled. Under real loss the 2026-10-09 battle A/B still
failed the native rejection-frequency gate with the backlog fix on: rejection
on 1/12 links (seed 12) with short modeled gaps of 86-120 ms, and up to
558-714 ms worst modeled blackout. The cause is the receive rule itself:

* `0x0075D800` accepts a data packet only when its stamp (`+0x0A`) equals
  `peer+0x84`, the next reliable stamp expected.
* Senders stamp unreliable updates with their *next* reliable stamp
  (`peer+0x88`), so an update is acceptable only once every earlier reliable
  fragment has arrived.

One lost reliable fragment therefore discards every following position update
on that link until the retransmit lands: one round trip after the receiver's
NAK in the best case, the 1000/2500 ms retry timers when the NAK is lost or
rejected too. On WAN round trips the best case alone is 100-300 ms per lost
reliable fragment.

## Native drop path (connected peer)

Frame (EBP of `0x0075D800`): stamp `[ebp-0x15C]`, ack `[ebp-0x174]`, peer
`[ebp-0x134]`, `this` `[ebp-0x138]`, reliable flag `[ebp-0x13A]` (byte0 &
0x80), kind `[ebp-0x139]` (byte1 & 0x0F), final-fragment flag `[ebp-0x151]`
(byte0 & 0x40).

| Address | Instruction / effect |
|---|---|
| `0x0075D9DC` | connect kinds 3-5 with stamp 0 skip the stamp check |
| `0x0075DA0E` | `cmp stamp, [peer+0x84]` / `je 0x0075DB9B` accept |
| `0x0075DA1A` | pop queue entries below the cumulative ack (runs on drops too) |
| `0x0075DA70` | kinds 6 (NAK/ACK) and 7 (keepalive) return silently |
| `0x0075DA8D` | `cmp [0x008EDA28],0` / `je 0x0075DB32` — log gate (**site A**) |
| `0x0075DA9A` | `"Dropping Packet Type %u ... (#%ld received, #%ld expected)"`; expected prints 0 for unreliable |
| `0x0075DB32` | `0x0075A490(..., kind 6, peer+0x88, peer+0x84)`: the NAK; `peer+0x18=0`, `peer+0x19=1` |
| `0x0075DB96` | `jmp 0x0075EE69` return (**site B**) |
| `0x0075DB9B` | accept: reliable only `peer+0x84 = stamp+1`, `peer+0x18=1`; `peer+0x19=1`; `jmp 0x0075DEEF` |
| `0x0075DEEF` | cumulative-ack loop again, then `switch(kind)` |
| `0x0075DF6C` | case 0: an unreliable packet proceeds only if `peer+0x98` (reassembly `std::vector`, `0x0041FC90` = `empty()`) is empty; append; deliver via `0x00758C90` on the 0x40 flag |
| case 6 | `peer+0x20/+0x24` = now: the NAK makes the sender's retry pump resend immediately |

## Patch

Site A (13 bytes) jumps to a thunk that skips only the drop log when the
policy will deliver the packet, and otherwise repeats the stock compare and
branch exactly. Site B (5 bytes) runs after the stock NAK has been sent and
continues at `0x0075DEEF` for the same packets instead of returning. The
policy (`ShouldDeliver`) requires kind 0, reliable clear, final fragment set,
reassembly empty and `stamp - peer+0x84` in 1..4096 (u32 modular).

Unchanged: `peer+0x84` (never written for unreliable packets), reliable
ordering and reassembly, cumulative ACK processing, NAK emission, retry
timers and wire format. Stale updates (stamp behind expected) stay dropped,
so an update sent before a reliable message the receiver already holds is
never applied after it. Receiver-side only, so mixed stock peers are
unaffected. Both resume targets and the log-level address are read from the
verified signature bytes, not hard-coded.

Semantic change to qualify: an update sent *after* a reliable message that is
still being retransmitted may now be applied before that reliable message.
Original BZ 1.5 ran on DirectPlay, where guaranteed and non-guaranteed
messages were not mutually ordered, so the game layer is expected to tolerate
this, but that has not been proven for Redux. Live object-creation churn under
loss (the battle workload) is the qualifying test.

## Evidence status

* Static: decompile and disassembly of `0x0075D800` above; both signatures
  unique in the GOG image; compiled thunks disassembled from the Release DLL
  (decision, stock-compare fallback and branch targets as designed).
* Unit: `tests/p2p_early_unreliable_policy_tests.cpp` (window bounds,
  stale/reliable/non-final/partial-reassembly/kind rejection, u32 wrap).
* Release Win32 build and full CTest pass; INI tests pass.
* Live four-client A/B: matrix `retry-battle-matrix-20261010-0035` below.

## Live A/B at 3% loss — 2026-10-10

Private control `early-battle-control-20261010-0035`, matrix
`retry-battle-matrix-20261010-0035` (verdict PASS). Four clients on one PC
through the relay, backlog fix ON and stock 1000/2500 timers in every arm,
`loss=3,seed=212`, 80 fighting AI, 16 beacons, 64 powerups, 60 steady
simulation seconds; two passes with arm order reversed. Each arm's INI value
and the per-client `[P2PRECV]` armed/absent log lines were verified by the
scorer. Instance files were restored and hash-verified after the matrix; no
game process remained.

| Arm | EarlyUnreliableAccept | Native unreliable rejections | Native reliable rejections | Delivered early | Native health | Gameplay/cleanup |
|---|---|---:|---:|---:|---|---|
| 1 | 0 | 1,074 | 3,235 | 0 | FAIL | PASS |
| 2 | 1 | **0** | 3,282 | 1,404 | **pass** | PASS |
| 3 | 1 | **0** | 3,212 | 997 | **pass** | PASS |
| 4 | 0 | 1,143 | 3,193 | 0 | FAIL | PASS |

Native rejections are `Dropping Packet Type 0` lines in the four clients'
`BZLogger.txt`; unreliable ones print `#0 expected`, reliable ones the actual
expected stamp. All four arms: IMPAIRED_OK, zero crashes and GPU events, zero
Lua/engine script errors. Whole-trace relay replay of each arm's own traffic
gives stock-rule blackout 2.16-2.91 s per directed-link minute (worst
4.9-7.5 s) and early-rule blackout 0 s with zero rejected updates; the replay
uses relay forwarding order, not native acceptance.

Reading: every unreliable rejection was of the kind this patch targets, and
with it on none remained; the sustained-rejection gate that failed every
earlier impaired battle (including both backlog-fix-ON pairs of 2026-10-09)
passed in both ON arms. Reliable out-of-order rejections are unchanged: the
native receiver has no reorder buffer, so fragments behind a lost one are
dropped and retransmitted. Gameplay (deaths, scrap, pickups, cleanup across
four peers) passed with updates able to precede an earlier reliable message
under constant creation/destruction churn; no divergence check beyond the
existing battle assertions was run.

## Clean link and bandwidth limit — 2026-10-10

Matrix `retry-battle-matrix-20261010-0052` (control
`early-battle-control-20261010-0052`, verdict PASS, restored), same battle
case, one pass:

| Impairment | EarlyUnreliableAccept | Class | Native unreliable rejections | Native health | Modeled stock blackout s/link-min (max ms) | Duplicates / reliable |
|---|---|---|---:|---|---|---|
| clean | 1 | STRICT_PASS | 0 | pass | 0 | 144 / 8,674 |
| clean | 0 | STRICT_PASS | 0 | pass | 0 | 18 / 8,125 |
| `loss=3,rate=256,queue=200,seed=213` | 1 | IMPAIRED_OK | **0** | **pass** | 4.33 (10,898) replay only | 6,134 / 6,968 |
| `loss=3,rate=256,queue=200,seed=213` | 0 | IMPAIRED_OK | 1,666 | FAIL | 4.25 (13,350) | 5,609 / 6,578 |

The clean link is unaffected (nothing is ever ahead, so the patch never
fires). At 256 kbit/s with a 200-packet queue, stock blanks a peer's updates
for 13 s at worst; with the patch no update was rejected. The duplicate column
shows retransmit traffic dominating a rate-limited link under either rule;
that is the retry pump, not this patch.

## Early NAK receive (`[Network] EarlyNakAccept`)

The reliable path still recovers slowly. Relay analysis of matrix 1: reliable
delivery delay p95 1.8-3.0 s, p99 4.3-6.1 s; drop-to-retransmit p50 50-60 ms
but p90 1.0-1.5 s. The cause is the NAK itself. A NAK (kind 6, sent at
`0x0075DB32` on every drop) is stamped with the requester's next reliable
stamp (`peer+0x88`), and `0x0075DA70`-`0x0075DA88` silently returns for any
kind 6/7 whose stamp is not exactly `peer+0x84`. With reliable traffic in
flight both ways that almost never holds: 4,236 of 4,661 NAKs in matrix-1 arm 2
were ahead and dropped. Lost reliables therefore wait for the sender's
1000 ms (`back.time + 1000`, send path `0x0075C990`) or 2500 ms re-arm
(pump `0x0075AAF0` case 8) instead of one round trip. An ideal reorder buffer
would cut p95 only to about 1.3-1.9 s by the same replay, so the NAK is the
larger lever.

Patch: site `P2P Early NAK Accept` (5-byte JMP at `0x0075DA88`, sharing the
drop-log pattern at a disjoint offset). For kind 6 stamped 1-4096 ahead of
`peer+0x84` (`ShouldAcceptNak`) the thunk continues at `0x0075DBC5`, the
stock accept tail: `peer+0x19 = 1` (the pump resends only to a peer heard from
since its last pass), the cumulative-ack loop, then case 6, which sets the
retry deadline `peer+0x20/+0x24` to now. Everything else returns as stock.
`peer+0x84` is never written, kind 7 stays dropped, and the resend is still
bounded by the pump's 5000 bytes / peer-count budget per pass. Receiver-side
only. Logs `[P2PRECV] Early NAK receive armed` and throttled
`Accepted early NAKs: total=N`. Default off; kill switch
`OPENSHIM_DISABLE_EARLY_NAK_ACCEPT`.

### Live A/B, ungated — matrix `retry-battle-matrix-20261010-0706`

Control `nak-battle-control-20261010-0706`; `1000/2500+early` vs
`1000/2500+early+nak`, same battle case. Pass 1 completed; pass 2 stopped when
client 1 failed to authenticate at launch (harness, before any game traffic);
instances restored. Delay = first relay arrival of a reliable stamp to its
in-order forward (relay model, stock reorder rule).

| Impairment | EarlyNakAccept | NAKs accepted | Reliable p95 / p99 / max ms | Unresolved stamps | Retransmit copies | Reliable bytes | Relay drop % | Native health |
|---|---|---:|---|---:|---:|---:|---:|---|
| `loss=3,seed=212` | 0 | 0 | 3,135 / 4,166 / 4,836 | 1,322 | 2,655 | 428 k | 3.08 | pass |
| `loss=3,seed=212` | 1 | 476 | **696 / 1,004 / 1,175** | 8 | 4,426 | 545 k | 3.12 | pass |
| `loss=3,rate=256,queue=200,seed=213` | 0 | 0 | 2,853 / 6,595 / 8,080 | 1,326 | 9,804 | 861 k | 11.46 | pass |
| `loss=3,rate=256,queue=200,seed=213` | 1 | 2,498 | **1,515 / 2,288 / 2,971** | 1,033 | 24,204 | 1,488 k | 18.67 | pass |

Gameplay PASS and IMPAIRED_OK in all four. Reliable tail latency falls 4x on
the lossy link and 2.5-3x on the rate-limited one. The cost is resend volume:
+27% reliable bytes at 3% loss, +73% (and more queue drops) at 256 kbit/s.
Cause: after one loss the requester drops and NAKs every following fragment,
all naming the same missing stamp, and each accepted NAK runs a full
go-back-N pass of the unacknowledged queue before the first retransmission
can land.

### NAK holdoff (`EarlyNakHoldoffMs`, default 300)

A NAK's header ack (`+0x0E`, frame `[ebp-0x174]`, decoded at `0x0075D8F8`)
is the requester's `peer+0x84`, i.e. the missing stamp. `NakGate` admits the
first early NAK per (peer, missing stamp), holds repeats of that stamp for the
holdoff, and admits a new missing stamp at once; a repeat after the holdoff
(lost retransmission) is admitted again. 32 peer slots, oldest evicted.
Held NAKs return as stock and are logged as `Held repeat NAKs: total=N`
(since the reorder hold below: `Held NAKs (reorder window or repeat): total=N`).

### Live A/B, gated — matrix `retry-battle-matrix-20261010-0926`

Control `nakgate-battle-control-20261010-0926`, verdict PASS, 8/8 runs,
restored. Two passes, arm order reversed; holdoff 300 ms (default).

| Impairment | EarlyNakAccept | Reliable p95 / p99 ms (p1, p2) | Unresolved stamps | Retransmit copies | Reliable bytes | NAKs admitted / held | Native health |
|---|---|---|---:|---:|---:|---|---|
| `loss=3,seed=212` | 0 | 2,718 / 5,590 · 2,232 / 4,056 | 1,220 · 1,074 | 2,648 · 2,378 | 427 k · 423 k | — | pass |
| `loss=3,seed=212` | 1 | **888 / 1,071 · 801 / 1,006** | 120 · 17 | 4,446 · 4,482 | 549 k · 561 k | 34/725 · 28/488 | pass |
| `loss=3,rate=256,queue=200,seed=213` | 0 | 2,904 / 4,048 · 2,254 / 3,233 | 1,697 · 1,693 | 10,289 · 10,247 | 928 k · 923 k | — | pass |
| `loss=3,rate=256,queue=200,seed=213` | 1 | **1,400 / 1,982 · 1,191 / 1,736** | 609 · 584 | 14,523 · 11,458 | 1,048 k · 947 k | 113/1,641 · 73/1,216 | pass |

Gameplay PASS, IMPAIRED_OK, zero crashes/GPU events in all eight. The gate
held 92-96% of early NAKs and kept the full latency gain of the ungated run
(p95 3x lower at 3% loss, ~2x at 256 kbit/s), while the rate-limited
resend-byte cost fell from +73% to +3-13% and relay queue drops from 18.7%
to 13.4% (vs 11.4% early-only). Admitted/held counts are the throttled
`[P2PRECV]` totals (final up to 5 s of counts can be missing). Most held
NAKs are the stock NAK that still precedes every early-delivered update
(site B runs after `0x0075DB32`), all naming the same missing stamp.

## WAN profile — 2026-10-10

`delay=60,jitter=20,loss=2,reorder=1,seed=215` (about 120 ms round trip).

Harness caveat: the first two WAN matrices (`20261010-1034`, `-1051`) ran on
a relay whose delayed datagrams sharing one floored deadline left in timer-heap
order, not FIFO, so every resend burst arrived scrambled (DedicatedServer
`9eb491e` fixes it; regression in `relay_impairment_test.py`). Native receive
then accepted about one stamp per resend pass and stock collapsed (FLOW_FAIL,
cleanup never converged); early-only and early+NAK still passed gameplay,
but those runs are a stress result, not a WAN result. The scorer had a matching
flaw: rebuilding delivery from the millisecond trace stamp plus logged delay
could invert neighbours the relay sent at one deadline; `delivered()` now
applies the relay's per-stream floor (reorder-picked copies exempt).

Matrix `retry-battle-matrix-20261010-1112` (fixed relay, verdict PASS):

| Arm | Native unreliable rejections | Native stale dup / out-of-order drops | Reliable p95 / p99 / max ms | Unresolved stamps | Reliable bytes | Native health | Gameplay |
|---|---:|---|---|---:|---:|---|---|
| stock | 1,242 | 3,653 / 2,642 | 1,970 / 3,787 / 4,654 | 934 | 576 k | FAIL | PASS |
| `+early` | 30 | 4,187 / 2,887 | 2,699 / 4,046 / 5,158 | 891 | 615 k | pass | PASS |
| `+early+nak` | 27 | 6,225 / 3,911 | 1,934 / 2,606 / 3,036 | 360 | 878 k | pass | PASS |

At WAN round trips the early NAK helps the tail only modestly (p99 about
-35%) for +43% reliable bytes: a resend pass triggered by a NAK re-sends the
unacknowledged queue, much of which is still in flight one RTT later, and a
1% reorder NAKs datagrams that are not lost.

## NAK reorder hold (`EarlyNakReorderMs`; tried at 40, default 0 after the A/B) — 2026-10-10

Proposed after the WAN matrix: (1) act on a NAK only once its stamp has been
missing for about 40 ms, and (2) skip re-sending fragments still in flight.

(2) was dropped. The receive path keeps no reorder buffer: a reliable fragment
is accepted only when its stamp equals `peer+0x84`, so every fragment that
reaches the requester before the retransmission of the missing one is dropped
(and NAKed). Pump case 8 sends the queue front to back on one FIFO path, so
everything already in flight when the pass runs is ahead of the retransmitted
head and will be discarded. Re-sending it is required, not waste; skipping it
would only defer those fragments to the 2.5 s re-arm. The queue element does
carry its last send time (`+0x08/+0x0C`, rewritten by every pass), should a
selective scheme with a receiver-side buffer ever be considered.

(1) targets the passes that are pure waste:

* a datagram that is merely late or reordered (the WAN profile's 1% reorder):
  the requester NAKs once or twice naming it, the datagram lands, and its NAKs
  move on; stock-gate admission ran a full go-back-N pass on the first one;
* stale duplicates from a pass arriving after the requester has moved on: each
  is dropped and NAKed naming the *current* expected stamp, typically already
  in flight in the same burst; a new stamp was admitted at once, so a burst of
  duplicates chained passes.

`NakGate` now records when a stamp was first named and admits it only when a
NAK still names it `reorderMs` later; the requester NAKs every packet it drops,
so on a live link the confirming NAK arrives within a frame or two and a real
loss pays about `reorderMs` extra. A NAK naming a stamp behind the current one
(overtaken by a later NAK, within the 4096 window) is held instead of being
treated as new. Repeats after admission keep the 300 ms holdoff.
`EarlyNakReorderMs = 0` reproduces the previous gate except for that
stale-stamp rule. Armed line: `... reorder=40ms holdoff=300ms`. Matrix arms:
`+nak` (40) and `+nak0` (0).

### Live A/B — matrix `retry-battle-matrix-20261010-1300`

Control `nakhold-battle-control-20261010-1300`, one pass, classic battle
(80 host-owned AI, 16 beacons, 64 powerups, 60 s). Every run IMPAIRED_OK,
gameplay PASS, native health pass; instances restored and verified. Shot and
gap columns are from the `agent/netfix-hitreg-metrics` scorer (modelled
delivery; it replays the early rule and does not model the NAK gate).

| Impairment | Arm | Reliable p95 / p99 / max ms | Undelivered stamps | Reliable bytes | Shot packets lost | Update gaps >500 ms |
|---|---|---|---:|---:|---:|---:|
| `loss=3,seed=212` | `+early` | 2,419 / 3,693 / 4,365 | 1,182 | 402 k | 90 / 3,246 | 0 |
| | `+early+nak0` | **757 / 923 / 1,099** | 120 | 580 k | 108 / 3,252 | 6 |
| | `+early+nak` (40) | 1,090 / 1,772 / 1,975 | 460 | 617 k | 96 / 3,348 | 2 |
| `loss=3,rate=256,queue=200,seed=213` | `+early` | 3,529 / 4,722 / 7,233 | 1,308 | 1,375 k | 310 / 2,904 | 36 |
| | `+early+nak0` | **2,141 / 4,844 / 5,873** | 648 | 2,178 k | 315 / 3,027 | 45 |
| | `+early+nak` (40) | 2,629 / 8,110 / 8,516 | 839 | 3,531 k | 423 / 3,045 | 36 |
| WAN `delay=60,jitter=20,loss=2,reorder=1,seed=215` | `+early` | 2,650 / 4,572 / 5,452 | 1,066 | 569 k | 68 / 3,357 | 12 |
| | `+early+nak0` | **830 / 1,279 / 1,469** | 142 | 769 k | 63 / 3,018 | 2 |
| | `+early+nak` (40) | 1,326 / 2,423 / 2,858 | 705 | 657 k | 72 / 3,144 | 0 |

Verdict: the 40 ms hold is worse than no hold on reliable latency in every
profile (p99 about 2x, more undelivered stamps), cheaper in bytes only on WAN
(-15%) and far more expensive at 256 kbit/s (+62%), where the extra resend
volume also cost shot packets. Likely cause (hypothesis): a backlog drains in
several budget-limited passes, each advancing the missing stamp, and the hold
now delays every one of them by the window plus a confirming NAK. Default
changed to `EarlyNakReorderMs = 0`; the setting remains for experiments.
Single pass per cell, so treat byte differences under ~20% as noise.

Against the shipped default (`+early`), the old gate (`nak0`) still cuts
reliable p95 3x at 3% loss and WAN for +35-44% reliable bytes, and +58% at
256 kbit/s. None of the NAK arms moved shot-packet loss or update gaps
materially: those are unreliable traffic, fixed by `EarlyUnreliableAccept`.

## Decision

* `EarlyUnreliableAccept` default **on**: native health passes with it in
  every impaired profile (3% loss, 256 kbit/s, WAN) and fails without it; the
  clean link is unaffected; gameplay passed in every arm; receiver-only with an
  unchanged wire format, so mixed stock/patched sessions behave as before on
  stock receivers.
* `EarlyNakAccept` stays **opt-in** (holdoff 300 ms): reliable p95 3x lower on
  low-RTT lossy links for about +30% resend bytes, but on WAN the gain is small
  and the byte cost larger.

Soak, matrix `retry-battle-matrix-20261010-1130` (verdict PASS): the shipped
defaults (`1000/2500+early`) for 300 steady simulation seconds (~370 s
traced) per profile. `loss=3,seed=212`: native health pass, 0 native
unreliable rejections, gameplay PASS. WAN profile: native health pass, 110
unreliable rejections over the whole run, gameplay PASS. No crash or GPU
event.

Still open: real (non-loopback) WAN peers.
