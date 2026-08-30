# OpenShim options-page tile kit

Four flat tiles that the injected Settings and Keybind pages
(`src/patches/bzr_options_ui.cpp`) apply to widgets they create at runtime.
This is **not** a replacement screen background.

Regenerate with `python mkui.py`. `scripts/Deploy-OpenShim.ps1` copies all four
into `BZ_ASSETS_CORE/common/ui/CustomWidgets/` and hash-verifies them, so a
clean install cannot fall back to missing-texture panels.

| Asset | Colour | Used by |
|---|---|---|
| `uiline.png` | `(0,127,0)` | the four border bars of a panel outline |
| `uiplate.png` | `(0,43,0)` | the row label field |
| `uibtn.png` | `(0,84,0)` | value buttons and toolbar buttons, idle |
| `uibtnhv.png` | `(0,127,0)` | the same buttons, hovered or pressed |

## Why they are flat

The engine stretches a widget texture to the widget rect. Any border or motif
baked into the art is distorted by that stretch, in proportion to how far the
rect's aspect is from the source's. The stock `mpcron.png` plate is 578x68 with
a diagonal highlight down its left edge; drawn into a 210x36 value button that
highlight lands squashed underneath the value text, which is what made the row
values look crowded. A flat fill cannot distort.

So the tiles carry no border and no corner treatment. Separation comes from
tonal value -- the label field is darker than the button next to it -- and from
the gaps in `BuildUiOptionsPageLayout`. Panel frames are drawn as four separate
1-colour bars rather than as a stretched frame texture, for the same reason.

Every colour above is sampled from the shipped Redux UI art (`common/ui`:
`newon.png`, `mp1on.png`, `mpcron.png`, `mpcrclk.png`, and
`Options/keyOptions_center.png`), so the pages stay inside the stock palette
without copying stock pixels.

## Two things that cost a test cycle

**Sample what you crop.** The first version of this kit was eleven crops of the
stock border art. They loaded and drew correctly and were still invisible: the
crops came from the dark side of the source, so `uibg.png` peaked at RGB 3 and
the border tiles at 45, against a black backdrop. Check the pixels you shipped,
not just that the file loaded.

**Frames go on the control parent, not on an overlay.** Overlay views take a
different coordinate path on this screen. The full-bleed backdrop, the stock
frame and the two masks are overlays parented to `screen`, and they work --
but they are all full-width, where a wrong coordinate space is invisible. The
panel frames were overlays too, and a 2026-08-30 capture had all eleven of
their textures load and then rasterize nothing: the panel edges sampled pure
`(0,0,0)`. They are now built from the same button-backed plate the row
backdrops use, parented to `Middle_Overlay`, which lands exactly on its layout
rect. `CreateInputBindingUiPageDecor` logs `pieces=created/requested` so an
empty frame can be told apart from one the renderer dropped.

## Input safety

Decoration stays passive and stays out from under the controls. Panels are
outlines -- four bars, no fill -- so nothing decorative covers a rect that has
to take a click, and they are created before every label and button on the page
so they sit behind them. Do not add a filled panel over the row grid.
