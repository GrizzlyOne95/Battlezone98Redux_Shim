# P2P reliable retry: ping-adaptive wait (2026-11-07)

GOG Redux 2.2.301. Decompile citations refer to the private ghidrecomp corpus
(`bzr_gog_best_effort`). Disassembly facts come from the shipping GOG exe.

## Why

A co-op guest session on 2026-11-07 (Steam BZLogger, misn2bcr, about 350 ms ping)
ran with OpenShim's shortened timers: first retry 300 ms, retry interval 800 ms.
A first retry shorter than the round trip resends every reliable packet before
its ACK can arrive, and the pump resends the whole unacked queue (go-back-N).
That costs upload on exactly the links that can least afford it.

## Timer sites

- First retry, in send `FUN_0075BEB0`: `push 0; push 0x3E8; lea ecx,[ebp-0x104];
  call FUN_0075FE50` at 0x0075C9A4..0x0075C9B1 (disassembly).
- Retry interval, in pump `FUN_0075AAF0`: `push 0; push 0x9C4; lea ecx,[ebp-0x2E4];
  call FUN_0075FE50` at 0x0075BD17..0x0075BD24 (disassembly; `FUN_0075fe50(0x9c4,0)`
  at decompile line 593).
- `FUN_0075FE50` is `__thiscall(this, lo_ms, hi_ms)`. It multiplies by 1000
  (`__allmul(param_2,param_3,1000,0)`) and stores the deadline (decompile lines 10-12).

## Ping source

- `FUN_00576280` (decompile lines 7-16) writes one pong sample into a ring of 10
  entries of 0x1C bytes at Player+0x98. +0x9C holds the delay, and +0x94 is the
  sample count, capped at 10.
- Its only caller is the pong handler `FUN_00571e20:76`. The delay argument is
  `param_4 - *param_3` (receive time minus the echoed send time), which the debug
  print at line 69 labels "NET DELAY FROM PING". So +0x9C is the round trip, not
  the one-way delay.
- The send time is stored at Player+0x4C when the ping goes out
  (`FUN_00576480:35-36`, `FUN_00822e10(1)`). Both times come from `FUN_00822e60`,
  which converts performance-counter ticks to milliseconds (`FUN_006c9a10`:
  ticks / (freq/1000)). So the RTT is in ms.
- `FUN_00576b70:109-111` pings every player except the local id `DAT_009180d4`.
  A guest therefore measures its own RTT to every peer, not only the host.
- `FUN_00575f80` averages the ring (lines 10-13). The host's packet-interval
  governor `FUN_005732d0:43-53` takes the max of that average over all players.

## Thread and transport

`FUN_00764f50` picks the transport from `DAT_008f0470` (decompile lines 36-262).
Value 1 builds `CSteamP2P` (`FUN_00763940:15`), 2 and 3 build `CGalaxyP2P`
(`FUN_00763460:16`), and 4 builds `BZRNetP2P` (`FUN_0075a2b0:16`, vtable
0x0089BE78). The result goes to `DAT_0094547c` in every case.
`FUN_00764d80:15-20` defaults the value to 4; only the `-net:steam|gog|cp|bzr`
command-line switch changes it (`FUN_007d5120:98-124` -> `FUN_00764b20:5`).
The user's Steam BZLogger shows `Command-Line: /nointro` (2026-11-07), so Steam
and GOG players both run `BZRNetP2P` and the patched sites apply to both.
`CSteamP2P` has its own vtable 0x0089C11C (pump 0x00763AB0, send 0x00763E60) and
is not patched; it runs only under `-net:steam`.

The retry pump is slot +8 of the `BZRNetP2P` vtable (0x0089BE80 = 0x0075AAF0;
0x0089BE84 = send 0x0075BEB0, read from the exe). Net update `FUN_005715d0`
calls the governor at line 48 and then `FUN_00764a10` at line 49, which calls
`(*DAT_0094547c + 8)()`. So the pump and the player list share the game thread.

## Change

Each timer's `call FUN_0075FE50` is redirected to a naked stub that passes the
transport peer in edx to a wrapper, which waits `max(configured, 1.5 x THIS
peer's RTT)`, capped at 10 s. Per-peer RTTs come from a table rebuilt at most
every 500 ms from the game's own averages (`FUN_00577b50` walk +
`FUN_00575f80`, address read from Player+0x30). A peer with no matching Player,
or a matched RTT of 0, falls back to the worst RTT. On low ping the configured
value wins, so nothing changes. The ini key `[Network] ReliableRetryAdaptToPing=0`
turns it off. The periodic log line reports matched and fallback counts, which
show live whether the address match works.

## Per-peer wait (implemented)

- Both timer sites can see the transport peer record. At the interval site,
  eax holds the peer from the iterator deref at 0x0075BD0E (`call 0x0042DA60`),
  and it is untouched until the helper call at 0x0075BD24 (`mov byte [eax+0x19],0`
  in between). At the first-retry site the peer is `[ebp-0x78]`: written at
  0x0075BFBD (address-matched peer) or 0x0075BFF0, read at 0x0075C990
  (`mov ecx,[ebp-0x78]; add ecx,0xA4`) and 0x0075C9D3 (deadline at peer+0x20).
  The pump writes the same +0x19 flag and +0x20 deadline, so both are the same
  record type (disassembly).
- The peer holds the remote address at peer+0x08: the send loop compares
  `iterator_deref()+8` with `FUN_0056f780` at 0x0075BFA1-0x0075BFA6.
- The Player holds the same address at Player+0x30..0x3C (`FUN_00575920:33-37`).
  It is filled from a member record's +0x08, with the id from its +0x28
  (`FUN_0056fd20:121-128` -> `FUN_00576600:37` -> `FUN_00575920`). The
  transport peer uses the same +0x08 address and +0x28 id layout.
- `FUN_0056f780` compares address dwords 0, 2 and 3 (dword 1 is skipped).
- Implementation: at each E8 call, a naked stub loads the peer into edx (`mov edx,eax`
  at the interval site; `mov edx,[ebp-0x78]` at the first-retry site) and jumps
  to `W(self, peer, lo, hi)`. W looks up that peer's RTT by matching peer+0x08
  against Player+0x30 (dwords 0, 2, 3) in a table rebuilt every 500 ms, and
  falls back to the max when no Player matches. The resolve patterns include the
  frame-proving bytes (`8D 8D C8 FE FF FF E8 ?? ?? ?? ??` + `C6 40 19 00` for the
  interval site; `8B 4D 88 81 C1 A4 00 00 00 E8 ?? ?? ?? ?? 89 85 44 FF FF FF`
  for the first-retry site) and are unique whole-image matches in the GOG exe.
- That a member record and its transport peer hold byte-identical addresses is
  inferred from the shared layout, not traced: UNVERIFIED. The max fallback
  covers a mismatch; the matched/fallback counters will show it live.

## Not yet measured

The size of the reduction in resends at 350 ms has not been measured live: UNVERIFIED.
