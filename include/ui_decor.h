#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    struct UiDecorRect
    {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };

    struct UiDecorPiece
    {
        const char* texture = nullptr;
        UiDecorRect rect = {};
    };

    struct UiDecorPanelDesc
    {
        UiDecorRect rect = {};
    };

    // A panel is an outline: four border bars, no fill. The bars carry a flat
    // single-colour texture, so nothing in the art can be distorted by the
    // stretch to the bar rect, and no hit-testable surface is laid underneath
    // the row buttons.
    constexpr size_t kUiDecorMaxPanelPieces = 4;
    // Only the toolbar and the row grid are framed. The header sits in the
    // band where the stock screen's corner brackets intrude (measured: the
    // clear span at y=160 is x 236..1203), so a frame drawn around it would
    // cross the stock art.
    constexpr size_t kUiDecorPanelsPerOptionsPage = 2;
    constexpr size_t kUiDecorMaxOptionsPagePieces =
        kUiDecorMaxPanelPieces * kUiDecorPanelsPerOptionsPage;

    // Thickness of a panel's border bar, and the air between that border and
    // the first/last row inside it.
    constexpr float kUiDecorBorderThickness = 3.0f;
    constexpr float kUiDecorPanelPadding = 16.0f;

    size_t BuildUiDecorPanel(const UiDecorPanelDesc& desc,
                             UiDecorPiece* outPieces,
                             size_t outCapacity);

    // Shared 1440x1080 logical-space layout for the native Settings and
    // Keybind pages. Both pages are a centred stack of three bands: a header
    // (title, two wrapped status lines, two wrapped context lines), a toolbar,
    // and the row grid. The header is the narrower of the two column widths
    // because the stock frame pinches that band; the toolbar and row grid use
    // the full clear width below it. All three share the 720 px centre line.
    struct UiOptionsPageLayout
    {
        UiDecorRect topMask = {};
        UiDecorRect contentMask = {};
        UiDecorRect headerPanel = {};
        UiDecorRect toolbarPanel = {};
        UiDecorRect contentPanel = {};
        UiDecorRect title = {};
        UiDecorRect statusLine1 = {};
        UiDecorRect statusLine2 = {};
        UiDecorRect contextLine1 = {};
        UiDecorRect contextLine2 = {};
        // Widest text a header line may render before it has to wrap; every
        // header line is this wide, so both wrapped pairs break identically.
        float headerTextWidth = 0.0f;
        float toolbarY = 0.0f;
        float toolbarHeight = 0.0f;
        float toolbarLeftX = 0.0f;
        float toolbarRightX = 0.0f;
        float toolbarGap = 0.0f;
        float rowLeftX = 0.0f;
        float rowRightX = 0.0f;
        float rowStartY = 0.0f;
        float rowPitch = 0.0f;
        float rowHeight = 0.0f;
        float rowLabelYInset = 0.0f;
        float rowLabelWidth = 0.0f;
        float rowLabelTextWidth = 0.0f;
        float rowValueOffsetX = 0.0f;
        float rowValueWidth = 0.0f;
        float rowValueTextWidth = 0.0f;
        float rowPlateInsetX = 0.0f;
        // Width of the decorative label plate only. It must stop before the
        // value button so the engine's reverse child hit-test cannot let the
        // plate consume value/key-binding clicks.
        float rowPlateWidth = 0.0f;
    };

    UiOptionsPageLayout BuildUiOptionsPageLayout(size_t rowsPerColumn);

    // Fills outPanels with the panels that carry a drawn frame, in the order
    // they should be created. Returns the number written.
    size_t BuildUiOptionsPagePanels(const UiOptionsPageLayout& layout,
                                    UiDecorPanelDesc* outPanels,
                                    size_t outCapacity);

    // Places a toolbar row so no page has to carry hand-tuned x coordinates.
    // The first `rightAlignedFrom` entries pack left to right from the toolbar's
    // left inset; the rest pack right to left from its right inset, which is
    // where both pages keep their paging controls. Widths are used as given, so
    // a caller that over-subscribes the band gets overlapping rects rather than
    // silently rescaled buttons -- the geometry tests assert against that.
    // Returns the number of rects written.
    size_t LayoutUiToolbarRow(const UiOptionsPageLayout& layout,
                              const float* widths,
                              size_t count,
                              size_t rightAlignedFrom,
                              UiDecorRect* outRects,
                              size_t outCapacity);
}
