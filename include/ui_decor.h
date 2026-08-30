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

    enum UiDecorPanelFlags : uint32_t
    {
        UI_DECOR_FILL = 1u << 0,
        UI_DECOR_TECH = 1u << 1,
        UI_DECOR_DEFAULT = UI_DECOR_FILL | UI_DECOR_TECH,
    };

    struct UiDecorPanelDesc
    {
        UiDecorRect rect = {};
        uint32_t flags = UI_DECOR_DEFAULT;
    };

    // Fill + four corners + four edges + two asymmetric stock ornaments.
    constexpr size_t kUiDecorMaxPanelPieces = 11;
    constexpr size_t kUiDecorPanelsPerOptionsPage = 3;
    constexpr size_t kUiDecorMaxOptionsPagePieces =
        kUiDecorMaxPanelPieces * kUiDecorPanelsPerOptionsPage;

    // Native size of the two stock ornaments the content panel carries. Rows
    // must clear these bands or the diagonal art crosses the row text.
    constexpr float kUiDecorTechTopRightHeight = 72.0f;
    constexpr float kUiDecorTechBottomLeftHeight = 36.0f;

    size_t BuildUiDecorPanel(const UiDecorPanelDesc& desc,
                             UiDecorPiece* outPieces,
                             size_t outCapacity);

    size_t BuildUiDecorHeader(const UiDecorRect& rect,
                              UiDecorPiece* outPieces,
                              size_t outCapacity);

    // Shared 1440x1080 logical-space layout for the native Settings and
    // Keybind pages. Both pages are one 1030 px wide column of three stacked
    // panels: header (title + two wrapped status lines + one context line),
    // toolbar, and the row grid. Rows begin below the 72 px upper ornament and
    // finish above the 36 px lower ornament so decoration never crosses text.
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
        UiDecorRect contextLine = {};
        // Widest text a header line may render before it has to wrap or
        // ellipsize; the labels themselves are the full interior width.
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
    };

    UiOptionsPageLayout BuildUiOptionsPageLayout(size_t rowsPerColumn);

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
