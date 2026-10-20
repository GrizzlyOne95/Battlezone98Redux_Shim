# DXGI flip-model A/B — 2026-10-20

Setting: `[Graphics] DxgiFlipModel = 0` (default) / `OPENSHIM_DXGI_FLIP_MODEL=1`
(the environment wins). Implementation: `src/patches/dxgi_flip_model.cpp`.
Driver: `reverse_engineering/run_flip_model_ab.ps1`.

## Status

| check | result |
|---|---|
| Flip chain builds on Redux's Ogre D3D11 window | yes: `FLIP_DISCARD buffers=2 (Ogre asked 1, swapEffect=0) format=28 waitable=yes msaaProxy=yes` |
| Ogre's FSAA 8x survives | yes, rendered into a proxy that is resolved at Present |
| VSync reaches the flip chain | yes: `first present: syncInterval=1 flags=0x0 hr=0x00000000` |
| Stock arm leaves the swap chain alone | yes, no `[DXGI Flip]` line beyond nothing-armed |
| crsetup.lua restored after the weather harness | byte-for-byte |
| **Console pacing A/B (lcbench combat 40, crwx; windowed + fullscreen)** | **not run yet; the user must be at the physical console** |

## Why the numbers below are not results

Every run so far was in an RDP session (`SM_REMOTESESSION`). The remote
compositor holds blt-model presents to about 30 Hz, and a flip chain in a
remote session has no real vblank to wait for. Both distort pacing, in
opposite directions. These are plumbing checks only.

Windowed, 1920x1080 requested (the RDP desktop clamped the client to
584x1080), VSync=Yes, crwx (CR Mars weather held at Severe), 10 s skipped:

| run | flip active | fps | p50 / p90 / p99 ms | median abs dt delta | uneven pairs |
|---|---|---|---|---|---|
| crwx windowed stock (RDP) | no | ~33 | 30.50 / 31.75 / 120.76 | 27.92 ms | 98.5% |
| crwx windowed flip (RDP)  | yes | 402 | 2.36 / 2.67 / 3.15 | 0.06 ms | 0.1% |

The flip arm running at 350-400 fps with `syncInterval=1` matters. If it does
the same at the console, flip model is losing VSync, which is a behaviour
change and not a pacing win. The first console run has to answer this before
anything else, ideally with `-PresentMon` so the present mode is recorded
(Hardware: Independent Flip / Composed: Flip / Composed: Copy).

## Console runs (to do)

At the physical console, with nothing else on screen:

```powershell
.\reverse_engineering\run_flip_model_ab.ps1 -PresentMon -Repeat 2
```

This covers stock and flip × windowed and fullscreen × lcbench and crwx, with
the arms interleaved and the first arm alternating between repeats. It takes
about 45 minutes. The script refuses to run over RDP unless
`-AllowRemoteSession` is passed (which also refuses fullscreen). It writes
`summary.md` under `snapshots/flip_model_ab/<stamp>/`. Copy that table here.

| run | flip active | present mode | p50 / p99 ms | median abs dt delta | uneven pairs |
|---|---|---|---|---|---|
| lcbench windowed stock | | | | | |
| lcbench windowed flip | | | | | |
| lcbench fullscreen stock | | | | | |
| lcbench fullscreen flip | | | | | |
| crwx windowed stock | | | | | |
| crwx windowed flip | | | | | |
| crwx fullscreen stock | | | | | |
| crwx fullscreen flip | | | | | |

## Confounders to record with the results

- Windows 11 "Optimizations for windowed games" (Settings > Display >
  Graphics) can already upgrade a windowed blt chain to flip. If PresentMon
  shows the stock windowed arm as `Composed: Flip` or `Independent Flip`, the
  windowed comparison measures only the waitable latency and the MSAA resolve.
- Fullscreen: Ogre creates the chain with `Windowed=FALSE`. Flip model in
  exclusive mode is a different path (DXGI may present it as Independent Flip
  anyway). The `active:` line records `windowed=`.
- maxLatency=1 with the waitable wait trades throughput for latency. A low
  p99 with lower fps is not a straight win; compare fps as well.
- The MSAA proxy adds a ResolveSubresource per frame. Stock does the same
  resolve inside DXGI for a multisampled blt chain, so the cost should be a
  wash, but it is new code on the hot path.

## Fail-closed behaviour

The rewrite keeps Ogre's chain unchanged (and logs `kept Ogre's swap chain`)
for an sRGB or other non-flip format, a missing output window, a non-D3D11
device, or no render-target usage. If the proxy or flip chain cannot be built,
or the swap-chain vtable cannot be patched, it falls back to the original
description. DX9 is never touched. If dxgi.dll's factory vtable is already
wrapped by an overlay, the factory hook refuses and logs `not armed`.
