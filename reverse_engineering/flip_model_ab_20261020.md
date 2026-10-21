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
| Console pacing A/B (lcbench combat 40, crwx; windowed + fullscreen) | done 2026-10-20 at the physical console: no gain windowed; exclusive fullscreen was black, now falls back (see Console results) |

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

## Console results (2026-10-20, physical console)

240 Hz monitor, `-PresentMon -Repeat 2`, VSync=Yes, windowed 1920x1080,
fullscreen 2560x1440, 10 s skipped. Snapshot `snapshots/flip_model_ab/20261020_184659`.

| run | flip active | fps | p50 / p90 / p99 ms | pacing median abs dt delta | uneven pairs | present modes |
|---|---|---|---|---|---|---|
| lcbench_windowed_stock_r1 | False | 184.0 | 5.26 / 6.82 / 8.18 | 0.24 ms | 0.2% | Composed: Flip:8554 |
| lcbench_windowed_flip_r1 | True | 177.5 | 5.33 / 6.61 / 10.04 | 0.21 ms | 0.3% | Composed: Flip:8189 |
| lcbench_windowed_flip_r2 | True | 179.9 | 5.32 / 7.18 / 8.61 | 0.22 ms | 0.2% | Composed: Flip:8306 |
| lcbench_windowed_stock_r2 | False | 130.4 | 7.46 / 9.56 / 11.29 | 0.28 ms | 0.2% | Composed: Flip:6009 |
| lcbench_fullscreen_stock_r1 | False | 138.3 | 6.62 / 9.56 / 11.26 | 0.22 ms | 0.2% | Hardware: Independent Flip:6523 |
| lcbench_fullscreen_flip_r1 | True | 125.3 | 7.47 / 9.84 / 11.56 | 0.25 ms | 0.2% |  |
| lcbench_fullscreen_flip_r2 | True | 125.9 | 7.60 / 9.21 / 10.93 | 0.32 ms | 0.2% |  |
| lcbench_fullscreen_stock_r2 | False | 153.8 | 6.47 / 7.63 / 9.50 | 0.21 ms | 0.2% | Hardware: Independent Flip:7263 |
| crwx_windowed_stock_r1 | False | 235.6 | 4.21 / 4.59 / 5.56 | 0.26 ms | 0.1% | Composed: Flip:21293 |
| crwx_windowed_flip_r1 | True | 235.9 | 4.20 / 4.77 / 6.12 | 0.38 ms | 0.1% | Composed: Flip:21274 |
| crwx_windowed_flip_r2 | True | 236.0 | 4.21 / 4.52 / 4.96 | 0.25 ms | 0.1% | Composed: Flip:21275 |
| crwx_windowed_stock_r2 | False | 235.6 | 4.20 / 4.48 / 4.87 | 0.22 ms | 0.1% | Composed: Flip:21314 |
| crwx_fullscreen_stock_r1 | False | 328.7 | 2.95 / 3.24 / 3.70 | 0.10 ms | 0.1% | Hardware: Independent Flip:30069 |
| crwx_fullscreen_flip_r1 | True | 284.3 | 3.37 / 3.86 / 4.76 | 0.11 ms | 0.1% |  |
| crwx_fullscreen_flip_r2 | True | 274.8 | 3.46 / 4.18 / 4.75 | 0.11 ms | 0.0% |  |
| crwx_fullscreen_stock_r2 | False | 319.0 | 3.04 / 3.53 / 4.05 | 0.12 ms | 0.0% | Hardware: Independent Flip:29183 |

- **Windowed: no gain.** Windows 11 already presents the stock blt chain as
  `Composed: Flip`, so both arms reach the compositor the same way. fps, p99
  and pacing differ by less than the repeat-to-repeat noise (stock lcbench
  alone moved 184 → 130 fps between repeats).
- **VSync caps flip.** crwx windowed sits at 236 fps in both arms, the 240 Hz
  cap; lcbench never reaches 240, so the cap does not apply there.
- **Exclusive fullscreen flip was broken.** The waitable chain is refused
  (`0x887A0001`), the plain flip chain is created with `DXGI_STATUS_OCCLUDED`
  (`0x087A0001`), and every Present returns `DXGI_ERROR_INVALID_CALL`
  (`first present: ... hr=0x887A0001`): a black screen while the game keeps
  simulating, so the fullscreen flip rows above (no PresentMon present mode)
  are invalid. Stock fullscreen already runs as `Hardware: Independent Flip`,
  the best path DXGI offers. `IneligibleReason` now keeps Ogre's chain when
  `Windowed` is FALSE. Live check (`20261020_191313`, crwx fullscreen, flip
  arm): `kept Ogre's swap chain ... exclusive fullscreen`, 330.6 fps,
  `Hardware: Independent Flip:10505`.
- **Unrelated, open:** stock exclusive fullscreen crwx runs at 319-329 fps on
  the 240 Hz monitor with VSync=Yes, so VSync does not cap exclusive
  fullscreen. Not investigated here.
- Not covered: switching a windowed flip chain to fullscreen at runtime
  (`SetFullscreenState`) was not exercised.

Verdict: keep `DxgiFlipModel = 0`. It is safe windowed and now falls back in
exclusive fullscreen, but it buys nothing measurable on Windows 11.

## Console runs (how to repeat)

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
