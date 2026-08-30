#include "ui_decor.h"

#include <cassert>
#include <cstring>

using namespace BZROpenShim;

namespace
{
    constexpr float kLogicalWidth = 1440.0f;
    constexpr float kLogicalHeight = 1080.0f;
    constexpr float kPageCenterX = kLogicalWidth * 0.5f;

    float Right(const UiDecorRect& rect)
    {
        return rect.x + rect.width;
    }

    float Bottom(const UiDecorRect& rect)
    {
        return rect.y + rect.height;
    }

    float CenterX(const UiDecorRect& rect)
    {
        return rect.x + rect.width * 0.5f;
    }

    bool Contains(const UiDecorRect& outer, const UiDecorRect& inner)
    {
        return inner.x >= outer.x && inner.y >= outer.y &&
               Right(inner) <= Right(outer) && Bottom(inner) <= Bottom(outer);
    }

    // The three bands stack without touching and share one centre line. The
    // header is allowed to be narrower -- the stock frame's corner brackets
    // pinch that band -- but it may never be wider than the body column.
    void VerifyPanelStack(const UiOptionsPageLayout& layout)
    {
        assert(CenterX(layout.headerPanel) == kPageCenterX);
        assert(CenterX(layout.toolbarPanel) == kPageCenterX);
        assert(CenterX(layout.contentPanel) == kPageCenterX);

        assert(layout.toolbarPanel.x == layout.contentPanel.x);
        assert(layout.toolbarPanel.width == layout.contentPanel.width);
        assert(layout.headerPanel.width <= layout.toolbarPanel.width);

        assert(Bottom(layout.headerPanel) < layout.toolbarPanel.y);
        assert(Bottom(layout.toolbarPanel) < layout.contentPanel.y);

        // Header text stays inside the narrow column, which is what keeps it
        // clear of the stock brackets on both sides.
        assert(Contains(layout.headerPanel, layout.title));
        assert(Contains(layout.headerPanel, layout.statusLine1));
        assert(Contains(layout.headerPanel, layout.statusLine2));
        assert(Contains(layout.headerPanel, layout.contextLine1));
        assert(Contains(layout.headerPanel, layout.contextLine2));

        // Five lines run in order and never overlap. Both wrapped pairs get a
        // full-height second line, so a wrapped string cannot land on top of
        // the pair below it.
        assert(Bottom(layout.title) <= layout.statusLine1.y);
        assert(Bottom(layout.statusLine1) <= layout.statusLine2.y);
        assert(Bottom(layout.statusLine2) <= layout.contextLine1.y);
        assert(Bottom(layout.contextLine1) <= layout.contextLine2.y);
        assert(layout.statusLine1.height == layout.statusLine2.height);
        assert(layout.contextLine1.height == layout.contextLine2.height);
        assert(layout.statusLine2.height >= 26.0f);
        assert(layout.contextLine2.height >= 26.0f);

        // Every header line shares the wrap width, or the two halves of a
        // wrapped string would break against different budgets.
        assert(layout.headerTextWidth == layout.title.width);
        assert(layout.headerTextWidth == layout.statusLine1.width);
        assert(layout.headerTextWidth == layout.statusLine2.width);
        assert(layout.headerTextWidth == layout.contextLine1.width);
        assert(layout.headerTextWidth == layout.contextLine2.width);

        // The masks have to cover every panel or a lit strip of the stock page
        // shows through at a panel edge.
        assert(Contains(layout.topMask, layout.headerPanel));
        assert(Contains(layout.topMask, layout.toolbarPanel));
        assert(Contains(layout.contentMask, layout.contentPanel));
    }

    void VerifyRowGrid(const UiOptionsPageLayout& layout, size_t rowsPerColumn)
    {
        // Rows sit inside the content panel's padding, clear of the border bars.
        assert(layout.rowStartY == layout.contentPanel.y + kUiDecorPanelPadding);
        assert(kUiDecorPanelPadding > kUiDecorBorderThickness);
        const float lastRowBottom = rowsPerColumn == 0
            ? layout.rowStartY
            : layout.rowStartY + static_cast<float>(rowsPerColumn - 1) * layout.rowPitch +
                  layout.rowHeight;
        assert(lastRowBottom <= Bottom(layout.contentPanel) - kUiDecorPanelPadding);
        assert(layout.rowPitch > layout.rowHeight); // rows never touch

        const float plateWidth =
            layout.rowValueOffsetX + layout.rowValueWidth + layout.rowPlateInsetX;
        const float leftPlateX = layout.rowLeftX - layout.rowPlateInsetX;
        const float rightPlateX = layout.rowRightX - layout.rowPlateInsetX;

        // Both plates sit inside the content panel with equal side margins, and
        // the columns do not touch.
        assert(leftPlateX > layout.contentPanel.x);
        assert(rightPlateX > leftPlateX + plateWidth);
        assert(rightPlateX + plateWidth < Right(layout.contentPanel));
        const float leftMargin = leftPlateX - layout.contentPanel.x;
        const float rightMargin = Right(layout.contentPanel) - (rightPlateX + plateWidth);
        assert(leftMargin == rightMargin);
        assert(leftMargin > kUiDecorBorderThickness);

        // A label and its value button share a row without overlapping, and the
        // fitted text widths stop short of both boxes.
        assert(layout.rowLabelWidth <= layout.rowValueOffsetX);
        assert(layout.rowLabelTextWidth < layout.rowLabelWidth);
        assert(layout.rowValueTextWidth < layout.rowValueWidth);
        assert(layout.rowLabelYInset > 0.0f);
        assert(layout.rowLabelYInset < layout.rowHeight);

        // The label field is the half that was truncating actions such as
        // "Flip Tile Horizontally", so it must stay the wider of the two.
        assert(layout.rowLabelTextWidth > layout.rowValueTextWidth);
    }

    void VerifyToolbar(const UiOptionsPageLayout& layout,
                       const float* widths,
                       size_t count,
                       size_t rightAlignedFrom)
    {
        UiDecorRect rects[8] = {};
        assert(count <= 8);
        assert(LayoutUiToolbarRow(layout, widths, count, rightAlignedFrom, rects, 8) == count);

        for (size_t index = 0; index < count; ++index)
        {
            assert(rects[index].width == widths[index]);
            assert(rects[index].height == layout.toolbarHeight);
            assert(rects[index].y == layout.toolbarY);
            assert(rects[index].x >= layout.toolbarLeftX);
            assert(Right(rects[index]) <= layout.toolbarRightX);
            // Buttons live inside the toolbar panel, clear of its border bars.
            assert(rects[index].y > layout.toolbarPanel.y + kUiDecorBorderThickness);
            assert(Bottom(rects[index]) <
                   Bottom(layout.toolbarPanel) - kUiDecorBorderThickness);
            if (index > 0)
                assert(rects[index].x >= Right(rects[index - 1]) + layout.toolbarGap);
        }

        // The row is flush with both insets: left group starts at the left one,
        // right group ends at the right one.
        assert(rects[0].x == layout.toolbarLeftX);
        assert(Right(rects[count - 1]) == layout.toolbarRightX);
    }

    // Every framed panel is an outline of four bars that meet at the corners
    // and leave the interior untouched, so no decoration is laid under a
    // control that has to be clicked.
    void VerifyPanelOutline(const UiDecorPanelDesc& panel)
    {
        UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
        assert(BuildUiDecorPanel(panel, pieces, kUiDecorMaxPanelPieces) ==
               kUiDecorMaxPanelPieces);

        const float t = kUiDecorBorderThickness;
        float coveredArea = 0.0f;
        for (const UiDecorPiece& piece : pieces)
        {
            assert(piece.texture != nullptr);
            assert(std::strcmp(piece.texture, "uiline.png") == 0);
            assert(piece.rect.width > 0.0f && piece.rect.height > 0.0f);
            assert(Contains(panel.rect, piece.rect));
            // Each bar is thin in exactly one axis: nothing fills the panel.
            assert(piece.rect.width == t || piece.rect.height == t);
            coveredArea += piece.rect.width * piece.rect.height;
        }

        // Four bars, no double-covered corner: the outline costs exactly its
        // own perimeter, never the panel's area.
        const float perimeterArea =
            2.0f * panel.rect.width * t + 2.0f * (panel.rect.height - 2.0f * t) * t;
        assert(coveredArea == perimeterArea);
        assert(coveredArea < panel.rect.width * panel.rect.height);

        // The interior clears the border on every side.
        const UiDecorRect interior = {
            panel.rect.x + t, panel.rect.y + t,
            panel.rect.width - 2.0f * t, panel.rect.height - 2.0f * t
        };
        for (const UiDecorPiece& piece : pieces)
        {
            const bool overlaps =
                piece.rect.x < Right(interior) && Right(piece.rect) > interior.x &&
                piece.rect.y < Bottom(interior) && Bottom(piece.rect) > interior.y;
            assert(!overlaps);
        }
    }

    void VerifyLayout(size_t rowsPerColumn,
                      const float* toolbarWidths,
                      size_t toolbarCount,
                      size_t rightAlignedFrom)
    {
        const UiOptionsPageLayout layout = BuildUiOptionsPageLayout(rowsPerColumn);
        VerifyPanelStack(layout);
        VerifyRowGrid(layout, rowsPerColumn);
        VerifyToolbar(layout, toolbarWidths, toolbarCount, rightAlignedFrom);

        UiDecorPanelDesc panels[kUiDecorPanelsPerOptionsPage] = {};
        assert(BuildUiOptionsPagePanels(layout, panels, kUiDecorPanelsPerOptionsPage) ==
               kUiDecorPanelsPerOptionsPage);
        // Only the toolbar and row grid are framed; framing the header would
        // draw across the stock corner brackets.
        assert(panels[0].rect.y == layout.toolbarPanel.y);
        assert(panels[1].rect.y == layout.contentPanel.y);
        for (const UiDecorPanelDesc& panel : panels)
        {
            assert(panel.rect.y >= Bottom(layout.headerPanel));
            VerifyPanelOutline(panel);
        }
    }
}

int main()
{
    // A panel too small to hold two borders emits nothing rather than
    // overlapping bars, and an undersized buffer is refused outright.
    UiDecorPiece scratch[kUiDecorMaxPanelPieces] = {};
    UiDecorPanelDesc tiny = {};
    tiny.rect = { 0.0f, 0.0f, 8.0f, 8.0f };
    assert(BuildUiDecorPanel(tiny, scratch, kUiDecorMaxPanelPieces) == 0);

    UiDecorPanelDesc ordinary = {};
    ordinary.rect = { 0.0f, 0.0f, 1140.0f, 446.0f };
    assert(BuildUiDecorPanel(ordinary, scratch, kUiDecorMaxPanelPieces - 1) == 0);
    assert(BuildUiDecorPanel(ordinary, nullptr, kUiDecorMaxPanelPieces) == 0);

    UiDecorPanelDesc panelScratch[kUiDecorPanelsPerOptionsPage] = {};
    const UiOptionsPageLayout probe = BuildUiOptionsPageLayout(8);
    assert(BuildUiOptionsPagePanels(probe, panelScratch,
                                    kUiDecorPanelsPerOptionsPage - 1) == 0);

    // Settings page: Back, Check for Updates | page caption, Prev, Next.
    static const float kSettingsToolbar[] = { 140.0f, 210.0f, 130.0f, 110.0f, 110.0f };
    VerifyLayout(8, kSettingsToolbar, 5, 2);

    // Keybind page: Back, Reset, Controls, RTS Actions | Prev, Next, Refresh.
    static const float kInputToolbar[] =
        { 120.0f, 190.0f, 150.0f, 160.0f, 90.0f, 90.0f, 120.0f };
    VerifyLayout(10, kInputToolbar, 7, 4);

    // The taller page must not push its content off the logical screen, and
    // must stay inside the band the stock frame leaves clear (x 71..1368,
    // y up to ~940, measured from keyOptions_center.png).
    const UiOptionsPageLayout tallest = BuildUiOptionsPageLayout(10);
    assert(tallest.topMask.x >= 71.0f);
    assert(Right(tallest.contentMask) <= 1368.0f);
    assert(Bottom(tallest.contentMask) <= 940.0f);
    assert(tallest.topMask.y >= 0.0f);
    assert(Right(tallest.contentMask) <= kLogicalWidth);
    assert(Bottom(tallest.contentMask) <= kLogicalHeight);

    return 0;
}
