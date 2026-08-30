# OpenShim stock-derived dynamic UI decoration kit

This pack is deliberately **not** a replacement screen background. It is a set of small passive image pieces for OpenShim to compose at runtime around its existing native controls.

## Art-direction contract

The visible pixels come only from the supplied Redux `common/ui` textures:

- `blackui.png` — panel fill
- `newon.png` — frame corners and straight borders
- `mp1on.png` — the distinctive diagonal technical ornaments

The extraction script does not redraw, recolor, blur, anti-alias, or synthesize decoration. On border/ornament crops it only makes the original flat button-fill color transparent so the stock `blackui` backing can show through. This keeps the line weights, green values, corner treatment and diagonal motif identical to shipped UI artwork.

## Runtime assets

All game-facing filename stems are 8 characters or fewer.

| Asset | Purpose |
|---|---|
| `uibg.png` | exact 4x4 stock black UI fill |
| `uitl.png` / `uitr.png` | upper corners |
| `uibl.png` / `uibr.png` | lower corners |
| `uitop.png` / `uibot.png` | stretchable horizontal runs |
| `uileft.png` / `uiright.png` | stretchable vertical runs |
| `uitrch.png` | stock `mp1on` upper-right technical ornament |
| `uiblch.png` | stock `mp1on` lower-left technical ornament |

## OpenShim integration

`src/uidcor.*` only calculates texture + rectangle descriptors. This is intentional: the current OpenShim Options/Input code already has the proven Redux cUI allocation, parent, ownership and lifetime path. Do **not** introduce a second cUI object creator here.

A screen integrates it approximately as follows, using its existing passive backdrop/image creation helper:

```cpp
UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
UiDecorPanelDesc panel = {};
panel.rect = { 420.0f, 255.0f, 820.0f, 290.0f };
panel.flags = UI_DECOR_DEFAULT;

const size_t count = BuildUiDecorPanel(panel, pieces, kUiDecorMaxPanelPieces);
for (size_t i = 0; i < count; ++i)
{
    // Use the SAME passive cUI image/backdrop constructor and validated
    // Middle_Overlay parent already used by bzr_options_ui.cpp.
    CreateExistingOpenShimPassiveImage(pieces[i].texture, pieces[i].rect);
}
```

The placeholder function above is intentionally not compiled into the kit; wire the descriptors into the existing proven helper in `bzr_options_ui.cpp` rather than guessing another Redux ABI path.

### Recommended screen structure

For the current two-column pages, build three panels dynamically:

1. header/status panel — derived from actual header label/status bounds;
2. navigation strip panel — derived from first/last navigation button bounds;
3. content panel — derived from the visible row bounds, with the technical ornament flag enabled.

The content panel height should be computed from `visibleRows * rowPitch + padding`, so pages with fewer rows shrink naturally. Keybindings can use one outer panel or two column panels without new textures.

## Input safety

Decoration must remain passive. Do not create a new full-bleed active `cUI_View` surface over stock controls. Mount decorative children beneath the interactive OpenShim buttons/labels on the already validated `Middle_Overlay` host, following the current OpenShim Native UI lifetime rules.

## Validation

`preview.png` deliberately composes the same pieces at three unrelated sizes. The stock `newon.png` and `mp1on.png` controls are embedded alongside them for direct visual-language comparison.
