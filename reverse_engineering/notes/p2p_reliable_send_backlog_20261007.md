# BZRNet P2P reliable-send backlog: why 3+ player games "lose" every update

2026-10-07, GOG 2.2.301 (`battlezone98redux.exe`, image base 0x00400000).
Fix: `src/patches/p2p_reliable_send_fix.cpp`, `[Network] ReliableSendBacklogFix`.
The three sites are registered in `scripts/patches.json` and `include/patches.h`;
the normal patch engine scans unique signatures, verifies original bytes and
writes while other threads are suspended. No address fallback is used.

## Symptom

Four-player co-op runs on one PC, through the OpenShim relay, showed links at
100% loss and climbing ping in the scoreboard, mostly between guests. The
relay forwarded every datagram (0 drops), yet clients logged hundreds of

    BZRNet P2P Dropping Packet Type 0 For Client S... (Packet #222 received, #0 expected)

per link. Long-standing player reports of severe lag with three or more
players match the same signature.

## Native mechanism

Per-peer state (pointer held in the address map at `BZRNet+0xC18`):

| Offset | Meaning |
|---|---|
| `+0x00` | connection state; 8 = connected |
| `+0x19` | a packet arrived since the last retry pass |
| `+0x1A` | retransmit-pending flag (the "backlog gate") |
| `+0x20` | next retry deadline |
| `+0x84` | next sequence expected from this peer |
| `+0x88` | next sequence this side will stamp |
| `+0xA4` | outbound reliable queue (std::list) |

Header: byte 0 flags (`0x80` reliable, `0x40` last fragment), byte 1 low
nibble kind (0 data, 3/4/5 connect, 6 nak/ack, 7 keepalive), bytes 2-9 a
timestamp, `+0x0A` u32 BE sequence stamp, `+0x0E` u32 BE ack (receiver's `+0x84`).

* **Send, `0x0075BEB0`.** A reliable message is split into fragments of at
  most 0x5AA bytes. Each is stamped with `+0x88`, appended to the queue and
  then sent at once **unless** `0x0075C72A movzx edx, byte [peer+0x1A]` /
  `0x0075C730 jne` skips it. `+0x88` advances either way. Unreliable packets
  are stamped with the current `+0x88` and never queued.
* **Retry pump, `0x0075AAF0` case 8.** When the deadline passes and `+0x19`
  is set: if the queue is non-empty it sets `+0x1A = 1` and resends queued
  fragments within `5000 / n` bytes (`0x0075B7E1 mov eax, 0x1388 / div`;
  `n` is the size of a list at `BZRNet+0x60`, read as the peer count: the
  largest pass seen with three peers was 1629 bytes, under 5000/3), then
  re-arms the deadline 2500 ms out (`0x0075BD19 push 0x9C4`). `+0x1A` is
  cleared only by a pass that finds the queue empty or nothing received since
  the last pass (`0x0075BD5F`). A send arms the first retry 1000 ms out
  (`0x0075C9A6 push 0x3E8`).
* **Receive, `0x0075D800`.** A data packet is accepted only when its stamp
  equals `+0x84` (connect packets with stamp 0 excepted); a reliable one then
  sets `+0x84 = stamp + 1`. Anything else is dropped and logged; for
  unreliable packets the log prints the expected value as **0** regardless,
  which is why the logs read "#0 expected" and looked like a sequence reset.

Put together: once a retry pass has run for a peer, every new reliable
fragment waits for the next pump, while every unreliable update is stamped
past it and therefore rejected. If the game queues reliable traffic faster
than the pump drains it, the queue is never empty when the pump looks and the
link stays in that state for the rest of the match. More players mean more
reliable traffic per link and a smaller per-peer retry budget.

## Evidence

`p2p_reliable_backlog_replay.py` replays a run's `relay-trace.jsonl` through
the accept rule above and compares with the clients' logs. On
`cr-misn05-win-Overridemisn05-coop-Skipperhost-4p-20261007-191204`:

| Link | Predicted drops (reliable/unreliable) | Native logged | Reliable msgs held back | Median / max hold |
|---|---|---|---|---|
| c2->c1 | 749 (16/733) | 748 | 133/386 | 0.57 s / 1.01 s |
| c1->c2 | 600 (16/584) | 600 | 161/386 | 0.49 s / 1.01 s |
| c2->c0 | 143 (16/127) | 140 | 177/404 | 0.01 s / 0.14 s |
| c3->c1 | 98 (37/61) | 97 | 246/961 | 0.11 s / 0.41 s |
| c3->c2 | 74 (39/35) | 74 | 437/1193 | 0.36 s / 1.02 s |
| c3->c0 | 71 (7/64) | 71 | 296/418 | 0.14 s / 0.43 s |
| c1->c0 | 49 (16/33) | 49 | 47/402 | 0.01 s / 0.02 s |
| host->guests | 0-1 | 0-1 | 0 | - |

The model reproduces the native counts to within three packets per link, and
almost all drops are unreliable updates stamped past held reliable messages.
The worst stock run (`...-4p-20261007-181309`, no relay trace) shows the same
signature on host->c3: about 55 unreliable drops per second, i.e. every update,
from mission start to the end.

## Fix

`ReliableSendBacklogFix` NOPs the `jne` at `0x0075C730` (27-byte signature from
`0x0075C71B`, unique in the image). A new fragment is always sent once
immediately; it stays queued and is retransmitted exactly as before until
acknowledged. Only sending timing changes: the wire format and receiver are
untouched, so stock peers interoperate. Kill switch
`OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX=1` for A/B runs.

`ReliableFirstRetryMs` / `ReliableRetryIntervalMs` expose the two retry timers
(stock 1000 / 2500 ms). They only matter on genuinely lossy links: a lost
reliable fragment still blocks later updates until it is resent. Stock by
default until lower values are qualified.

## Live validation

The same four-player `misn05 four-services` scenario completed with maximum
network capture on GOG 2.2.301. The DLL, CR/EXU content, server, DX9 renderer
and stock 1000/2500 ms timers were identical; only the backlog kill switch
changed. Both runs passed all 14 gameplay steps and 22 checks, including
all-to-all pings, replicated respawn handles/positions and mission results.

| Measure across all 12 directed links | Fix on | Stock gate |
|---|---:|---:|
| Rejected unreliable updates / future-stamped gaps | 0 | 75 |
| Reliable messages held before first send | 0 / 10,934 | 71 / 11,487 |
| Longest held reliable message | 0 ms | 27 ms |
| Duplicate reliable retransmits | 188 | 101 |
| GPU resets | 0 | 0 |

The native health gate passed both runs because it detects sustained
rejection, while these stock gaps were brief (at most 13 rejects in its
window). A health pass therefore does not mean zero rejected updates; the
replay's unreliable-gap count is the stricter backlog acceptance measure.
Duplicate reliable retransmits are reported separately from position loss.
The local evidence is under `C:\BZRCoop\runs\netfix-{on,off}-services-dx9-20261007-validation`.

An earlier fix-on DX11 attempt authenticated all four clients, then one
client crashed during a GPU driver reset. That incomplete run is excluded
from qualification. DX9 avoided the reset in the completed A/B; graphics
device restore remains a separate engine task.

## Remaining qualification

* Full four-client scenario matrix: two passes of nine cases with the fix on,
  then the same two passes with the kill switch. The focused A/B above is
  complete; matrix results will be recorded separately.
* WAN behaviour with real loss, and a qualified lower retry timer.
* Steam build: same layout is expected but unverified; a signature mismatch
  leaves stock behaviour.
