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
* Live four-client A/B: pending (see `p2p_retry_timing_validation_20261009.md`
  for the matrix tooling; arms `1000/2500` vs `1000/2500+early`).
