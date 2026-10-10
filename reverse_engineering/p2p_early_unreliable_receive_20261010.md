# BZRNet P2P early unreliable receive — 2026-10-10

GOG 2.2.301 (`battlezone98redux.exe`, image base 0x00400000).
Patch: `src/patches/p2p_early_unreliable_receive.cpp`, policy
`include/p2p_early_unreliable_policy.h`, `[Network] EarlyUnreliableAccept`
(default **off** until live-qualified). Sites registered in
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

Live A/B: matrix 3 (`1000/2500+early` vs `1000/2500+early+nak`), scored with
the new `reliableDelivery` (p50/p95/p99, retransmit copies, reliable bytes)
and `nakAcceptance` fields.

Open before a default flip: mixed stock/patched peers, longer sessions,
WAN round trips.
