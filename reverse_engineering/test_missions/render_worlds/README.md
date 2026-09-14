# Per-world renderer benchmark maps

Four fixed scenes on Moon, Mars, Venus and Titan, for the Phase 0 visual
benchmark. They are **lcbench** — the same `.hg2` heightfield, the same `.mat`
material grid, the same `.lgt` lightmap, the same mission script and the same
spawn point — with only the `.trn` swapped.

That is the whole design. Holding the geometry fixed is what lets a difference
between two captures be attributed to the planet (atlas, palette, sky, fog,
sun) rather than to the terrain under it. The same ridge and the same tank
formation appear in all four, so they can be compared frame to frame.

Because the payload is shared, only the four `.trn` files are committed here.
`scripts\Install-RenderWorldMaps.ps1` composes the rest from the
`live_combat_scaling` fixture at install time, which also means these worlds
cannot drift away from the scene lcbench itself measures.

## Install and run

```
powershell -ExecutionPolicy Bypass -File scripts\Install-RenderWorldMaps.ps1
powershell -ExecutionPolicy Bypass -File reverse_engineering\run_live_combat_benchmark.ps1 -World mars
```

The package installs to `addon\lcbworld\`. Missions are `lcbmoon.bzn`,
`lcbmars.bzn`, `lcbvenus.bzn`, `lcbtitan.bzn` — launch any of them directly
from the game for manual work. `-World` records itself in each run's
`metadata.json`, so a capture can never be mistaken for a different planet.

`Install-RenderWorldMaps.ps1 -SunTime 0300` rewrites `[NormalView] Time` in
every installed `.trn`. BZ reads it as a HHMM clock and places the sun from
it, so that is the grazing-angle sweep — the condition the `N.V` diffuse
repair and the shadow bias were fixed for. Without it each world keeps its own
authored time.

## What varies, and why each world is here

| World | Sun | Visibility | Atlas | Why it earns a slot |
| --- | --- | --- | --- | --- |
| Moon | 0900 | 250, no fog | `mn` | Airless. No atmospheric term to hide a lighting error, and the IBL floor makes "no direct light" a deeper hole than anywhere else — the harshest test for the black pools. |
| Mars | 0900 | 250, fog from 120 | `ma` | Atmosphere plus clouds and a sky texture. The ordinary case. |
| Venus | 1200 | **100**, fog from 30 | `ve` | Dense short-range fog, and the only one of the four whose atlas carries a real `EmissiveMap` (`venus_atlas_e.dds`) rather than `black.dds` — so it is the only world here that exercises terrain glow. |
| Titan | 1100 | 250, fog from 100 | `ti` | Clouds, a sky texture *and* a star layer with Saturn. Lowest sun-intensity terrain of the four. |

Venus's stock `[LightningBolt]` block is deliberately **not** included. It
fires on a random 5–30 s timer and adds a dynamic light, which is authentic
Venus and poison for a frame-time capture. Paste it back from
`Edit\trn\venus.trn` if a capture is specifically about that effect.

## The two rules a world file has to obey

Both failures are silent, which is why `scripts\Test-RenderWorldMaps.ps1`
checks them mechanically rather than leaving them to review.

1. **The texture-type index set must be `{0,3,4,5,6}`.** `lcbench.mat` was
   authored on Moon, which declares exactly those five. A world that declares
   fewer leaves whatever cells named the missing type pointing at nothing.
   Mars, Venus and Titan therefore re-map their own tiles onto Moon's indices
   rather than using their stock index sets.

2. **Every `.map` name must appear in that world's
   `<xx>_detail_atlas.csv`.** The name is a key into the atlas, not a file on
   disk. A name outside the CSV resolves to the atlas's default tile and the
   terrain still renders — just wrong, and only in the places that used the
   missing tile. Several names that appear in stock `.trn` files are *not* in
   the corresponding CSV (`ma03ca0.map`, for one), so "a stock map uses it" is
   not sufficient evidence.

```
powershell -ExecutionPolicy Bypass -File scripts\Test-RenderWorldMaps.ps1
```

Run it after any edit here. It reads the installed atlases, so it is checking
what the game can actually resolve rather than a copy of the vocabulary.

## Verified

All four load under DX11 Enhanced on the GOG install and render their own
planet: `Get-RenderEvidence.ps1` reports `capture state is coherent`, and the
Ogre log shows the expected `<world>_atlas_d/n/s.dds` loading with no missing
material or texture. The captures are in the Phase 0 closeout.
