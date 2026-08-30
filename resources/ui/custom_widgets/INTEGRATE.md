# Wiring the dynamic decoration into current OpenShim

This is written against current `main`'s `src/patches/bzr_options_ui.cpp` API shape.
The existing file already has the safe pieces we need:

- `CreateInputBindingUiOverlay(...)` creates a passive `cUI_Overlay` and assigns a texture.
- the current full-screen visual overlays are parented to `screen` (`visualParent`), not `Middle_Overlay`, because overlay coordinates follow a different path on this screen;
- buttons/labels remain on the validated `Middle_Overlay` control parent;
- visibility and lifetime are explicitly reset when the host screen is reconstructed.

The decoration kit should use that exact overlay path. Do not create decorative buttons or another active full-screen view.

## 1. Include the geometry helper

Near the other local includes in `bzr_options_ui.cpp`:

```cpp
#include "uidcor.h"
```

Add `uidcor.cpp` to the Win32 project, or make the helper header-only if preferred.

## 2. Track the passive decorative children

Alongside the existing `g_InputBindingUiBackdrop` / `g_InputBindingUiFrame` state:

```cpp
static std::array<void*, kUiDecorMaxPanelPieces> g_InputBindingUiDecor = {};
static std::array<void*, kUiDecorMaxPanelPieces> g_ShimSettingsUiDecor = {};
```

If header/content frames are kept separate, use two arrays per page. The hard bound stays tiny and deterministic.

Reset them with the rest of each page's visual state:

```cpp
g_InputBindingUiDecor.fill(nullptr);
g_ShimSettingsUiDecor.fill(nullptr);
```

and include them in the existing visibility loops:

```cpp
for (void* view : g_InputBindingUiDecor)
    SetInputBindingUiViewActive(view, visible);
```

Same for the settings page.

## 3. Create descriptors through the existing overlay constructor

Add this local adapter beside `CreateInputBindingUiOverlay`:

```cpp
static size_t CreateInputBindingUiDecor(
    std::array<void*, kUiDecorMaxPanelPieces>& slots,
    void* visualParent,
    const char* namePrefix,
    unsigned screenTag,
    const UiDecorPanelDesc& desc)
{
    UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
    const size_t count = BuildUiDecorPanel(desc, pieces, kUiDecorMaxPanelPieces);
    if (count == 0)
        return 0;

    for (size_t index = 0; index < count; ++index)
    {
        char controlName[96] = {};
        std::snprintf(controlName, sizeof(controlName), "%s_%08X_%02u",
                      namePrefix,
                      screenTag,
                      static_cast<unsigned>(index));

        const UiDecorPiece& piece = pieces[index];
        CreateInputBindingUiOverlay(slots[index],
                                    visualParent,
                                    controlName,
                                    piece.texture,
                                    piece.rect.x,
                                    piece.rect.y,
                                    piece.rect.width,
                                    piece.rect.height,
                                    0x60);
    }

    for (size_t index = count; index < slots.size(); ++index)
        SetInputBindingUiViewActive(slots[index], false);

    return count;
}
```

Why this adapter matters: it reuses the exact allocation, child ownership, texture assignment, flags and active-state mechanism already proven by the current OpenShim options pages.

## 4. Derive the frame from live layout constants

For the input/keybinding page, the current layout uses:

```text
left column base     258
right column base    740
row start            308
row pitch             38
row height            30
button offset        292
button width         175
rows per column       10
```

So do not hard-code a screenshot-sized background. Derive the content bounds:

```cpp
constexpr float kDecorPad = 18.0f;
constexpr float kContentLeft = kRowLeftBaseX - kDecorPad;
constexpr float kContentRight =
    kRowRightBaseX + kRowButtonOffsetX + kRowCompactButtonW + kDecorPad;
constexpr float kContentTop = kRowY - kDecorPad;
constexpr float kContentBottom =
    kRowY + (static_cast<float>(kInputBindingUiRowsPerColumn - 1) * kRowStep) +
    kRowButtonH + kDecorPad;

UiDecorPanelDesc content = {};
content.rect = {
    kContentLeft,
    kContentTop,
    kContentRight - kContentLeft,
    kContentBottom - kContentTop
};
content.flags = UI_DECOR_TECH; // border only if existing black backdrop stays

CreateInputBindingUiDecor(g_InputBindingUiDecor,
                          visualParent,
                          "OpenShimInputDecor",
                          screenTag,
                          content);
```

If the full-screen `blackui.png` backdrop remains, omit `UI_DECOR_FILL`; this keeps the new frame decorative and avoids layering opaque rectangles over the existing page.

For the settings page, calculate the same rectangle from its own `kRowLeftBaseX`, `kRowRightBaseX`, `kRowY`, `kRowStep`, `kRowButtonOffsetX`, button width and rows-per-column constants. When a future page exposes fewer visible rows, use the actual visible-row count to calculate the bottom edge.

## 5. Header and separators

Use the quieter stock-derived header primitive around the three text lines:

```cpp
UiDecorPiece headerPieces[kUiDecorMaxPanelPieces] = {};
const UiDecorRect headerRect = {
    kHeaderX - 12.0f,
    kHeaderY - 10.0f,
    kHeaderW + 24.0f,
    (kPageY + kPageH) - kHeaderY + 20.0f
};
const size_t headerCount =
    BuildUiDecorHeader(headerRect, headerPieces, kUiDecorMaxPanelPieces);
```

Feed those descriptors through the same `CreateInputBindingUiOverlay` adapter. Keep the technical `mp1on` diagonals on the larger content region only; Redux's stock UI is asymmetric and restrained, not covered in ornamental corners everywhere.

A toolbar separator can be one `BuildUiDecorSeparator(...)` descriptor spanning the navigation controls. Open brackets are available for column/group emphasis where a full frame feels too boxed-in.

## 6. Asset location

Install the PNGs in the same resource group as the stock UI textures, e.g. the game's `BZ_ASSETS_CORE/common/ui` during local qualification. All texture stems are <= 8 characters.

```text
uibg.png
uitl.png
uitr.png
uibl.png
uibr.png
uitop.png
uibot.png
uileft.png
uiright.png
uitrch.png
uiblch.png
```

## 7. Qualification gate

Before enabling by default:

1. Open stock Options -> Input repeatedly and confirm Back/Joystick still receive clicks.
2. Open OpenShim Settings repeatedly and confirm all row hover/click callbacks fire once.
3. Switch Settings -> Input -> Back -> Options several times to exercise reconstructed/reused screen addresses.
4. Confirm old decorative pointers are cleared by the same reset/dtor path as the existing visuals.
5. Test 16:9 at 1080p and 4K. Geometry is in the existing 1440x1080 logical space, so the assembled frame must stay aligned with its controls.
6. Test a page with fewer rows and confirm the computed content frame shrinks rather than leaving a large empty fixed background.
7. Exit with either custom page active and confirm no shutdown fault.
