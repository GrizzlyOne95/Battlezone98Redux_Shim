#include "ui_decor.h"

#include <cstdio>
#include <cstring>
#include "test_check.h"

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
        CHECK(CenterX(layout.headerPanel) == kPageCenterX);
        CHECK(CenterX(layout.toolbarPanel) == kPageCenterX);
        CHECK(CenterX(layout.contentPanel) == kPageCenterX);

        CHECK(layout.toolbarPanel.x == layout.contentPanel.x);
        CHECK(layout.toolbarPanel.width == layout.contentPanel.width);
        CHECK(layout.headerPanel.width <= layout.toolbarPanel.width);

        CHECK(Bottom(layout.headerPanel) < layout.toolbarPanel.y);
        CHECK(Bottom(layout.toolbarPanel) < layout.contentPanel.y);

        // Header text stays inside the narrow column, which is what keeps it
        // clear of the stock brackets on both sides.
        CHECK(Contains(layout.headerPanel, layout.title));
        CHECK(Contains(layout.headerPanel, layout.statusLine1));
        CHECK(Contains(layout.headerPanel, layout.statusLine2));
        CHECK(Contains(layout.headerPanel, layout.contextLine1));
        CHECK(Contains(layout.headerPanel, layout.contextLine2));

        // Five lines run in order and never overlap. Both wrapped pairs get a
        // full-height second line, so a wrapped string cannot land on top of
        // the pair below it.
        CHECK(Bottom(layout.title) <= layout.statusLine1.y);
        CHECK(Bottom(layout.statusLine1) <= layout.statusLine2.y);
        CHECK(Bottom(layout.statusLine2) <= layout.contextLine1.y);
        CHECK(Bottom(layout.contextLine1) <= layout.contextLine2.y);
        CHECK(layout.statusLine1.height == layout.statusLine2.height);
        CHECK(layout.contextLine1.height == layout.contextLine2.height);
        CHECK(layout.statusLine2.height >= 26.0f);
        CHECK(layout.contextLine2.height >= 26.0f);

        // Every header line shares the wrap width, or the two halves of a
        // wrapped string would break against different budgets.
        CHECK(layout.headerTextWidth == layout.title.width);
        CHECK(layout.headerTextWidth == layout.statusLine1.width);
        CHECK(layout.headerTextWidth == layout.statusLine2.width);
        CHECK(layout.headerTextWidth == layout.contextLine1.width);
        CHECK(layout.headerTextWidth == layout.contextLine2.width);

        // The masks have to cover every panel or a lit strip of the stock page
        // shows through at a panel edge.
        CHECK(Contains(layout.topMask, layout.headerPanel));
        CHECK(Contains(layout.topMask, layout.toolbarPanel));
        CHECK(Contains(layout.contentMask, layout.contentPanel));
    }

    void VerifyRowGrid(const UiOptionsPageLayout& layout, size_t rowsPerColumn)
    {
        // Rows sit inside the content panel's padding, clear of the border bars.
        CHECK(layout.rowStartY == layout.contentPanel.y + kUiDecorPanelPadding);
        CHECK(kUiDecorPanelPadding > kUiDecorBorderThickness);
        const float lastRowBottom = rowsPerColumn == 0
            ? layout.rowStartY
            : layout.rowStartY + static_cast<float>(rowsPerColumn - 1) * layout.rowPitch +
                  layout.rowHeight;
        CHECK(lastRowBottom <= Bottom(layout.contentPanel) - kUiDecorPanelPadding);
        CHECK(layout.rowPitch > layout.rowHeight); // rows never touch

        const float plateWidth = layout.rowPlateWidth;
        const float leftPlateX = layout.rowLeftX - layout.rowPlateInsetX;
        const float rightPlateX = layout.rowRightX - layout.rowPlateInsetX;
        const float leftValueX = layout.rowLeftX + layout.rowValueOffsetX;
        const float rightValueX = layout.rowRightX + layout.rowValueOffsetX;
        const float leftFootprintRight = leftValueX + layout.rowValueWidth;
        const float rightFootprintRight = rightValueX + layout.rowValueWidth;

        // Both complete rows sit inside the content panel with equal side
        // margins, and the columns do not touch.
        CHECK(leftPlateX > layout.contentPanel.x);
        CHECK(rightPlateX > leftFootprintRight);
        CHECK(rightFootprintRight < Right(layout.contentPanel));
        const float leftMargin = leftPlateX - layout.contentPanel.x;
        const float rightMargin = Right(layout.contentPanel) - rightFootprintRight;
        CHECK(leftMargin == rightMargin);
        CHECK(leftMargin > kUiDecorBorderThickness);

        // The decorative button-backed plate must not overlap the interactive
        // value button. Redux tests children in reverse draw order; overlap here
        // makes the plate paint over and consume clicks meant for the value.
        CHECK(leftPlateX + plateWidth <= leftValueX);
        CHECK(rightPlateX + plateWidth <= rightValueX);

        // A label and its value button share a row without overlapping, and
        // fitted text widths stop short of both boxes.
        CHECK(layout.rowLabelWidth <= layout.rowValueOffsetX);
        CHECK(layout.rowLabelTextWidth < layout.rowLabelWidth);
        CHECK(layout.rowValueTextWidth < layout.rowValueWidth);
        CHECK(layout.rowLabelYInset > 0.0f);
        CHECK(layout.rowLabelYInset < layout.rowHeight);

        // The label field is the half that was truncating actions such as
        // "Flip Tile Horizontally", so it must stay the wider of the two.
        CHECK(layout.rowLabelTextWidth > layout.rowValueTextWidth);
    }

    void VerifyToolbar(const UiOptionsPageLayout& layout,
                       const float* widths,
                       size_t count,
                       size_t rightAlignedFrom)
    {
        UiDecorRect rects[8] = {};
        CHECK(count <= 8);
        CHECK(LayoutUiToolbarRow(layout, widths, count, rightAlignedFrom, rects, 8) == count);

        for (size_t index = 0; index < count; ++index)
        {
            CHECK(rects[index].width == widths[index]);
            CHECK(rects[index].height == layout.toolbarHeight);
            CHECK(rects[index].y == layout.toolbarY);
            CHECK(rects[index].x >= layout.toolbarLeftX);
            CHECK(Right(rects[index]) <= layout.toolbarRightX);
            // Buttons live inside the toolbar panel, clear of its border bars.
            CHECK(rects[index].y > layout.toolbarPanel.y + kUiDecorBorderThickness);
            CHECK(Bottom(rects[index]) <
                   Bottom(layout.toolbarPanel) - kUiDecorBorderThickness);
            if (index > 0)
                CHECK(rects[index].x >= Right(rects[index - 1]) + layout.toolbarGap);
        }

        // The row is flush with both insets: left group starts at the left one,
        // right group ends at the right one.
        CHECK(rects[0].x == layout.toolbarLeftX);
        CHECK(Right(rects[count - 1]) == layout.toolbarRightX);
    }

    // Every framed panel is an outline of four bars that meet at the corners
    // and leave the interior untouched, so no decoration is laid under a
    // control that has to be clicked.
    void VerifyPanelOutline(const UiDecorPanelDesc& panel)
    {
        UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
        CHECK(BuildUiDecorPanel(panel, pieces, kUiDecorMaxPanelPieces) ==
               kUiDecorMaxPanelPieces);

        const float t = kUiDecorBorderThickness;
        float coveredArea = 0.0f;
        for (const UiDecorPiece& piece : pieces)
        {
            CHECK(piece.texture != nullptr);
            CHECK(std::strcmp(piece.texture, "uiline.png") == 0);
            CHECK(piece.rect.width > 0.0f && piece.rect.height > 0.0f);
            CHECK(Contains(panel.rect, piece.rect));
            // Each bar is thin in exactly one axis: nothing fills the panel.
            CHECK(piece.rect.width == t || piece.rect.height == t);
            coveredArea += piece.rect.width * piece.rect.height;
        }

        // Four bars, no double-covered corner: the outline costs exactly its
        // own perimeter, never the panel's area.
        const float perimeterArea =
            2.0f * panel.rect.width * t + 2.0f * (panel.rect.height - 2.0f * t) * t;
        CHECK(coveredArea == perimeterArea);
        CHECK(coveredArea < panel.rect.width * panel.rect.height);

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
            CHECK(!overlaps);
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
        CHECK(BuildUiOptionsPagePanels(layout, panels, kUiDecorPanelsPerOptionsPage) ==
               kUiDecorPanelsPerOptionsPage);
        // Only the toolbar and row grid are framed; framing the header would
        // draw across the stock corner brackets.
        CHECK(panels[0].rect.y == layout.toolbarPanel.y);
        CHECK(panels[1].rect.y == layout.contentPanel.y);
        for (const UiDecorPanelDesc& panel : panels)
        {
            CHECK(panel.rect.y >= Bottom(layout.headerPanel));
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
    CHECK(BuildUiDecorPanel(tiny, scratch, kUiDecorMaxPanelPieces) == 0);

    UiDecorPanelDesc ordinary = {};
    ordinary.rect = { 0.0f, 0.0f, 1140.0f, 446.0f };
    CHECK(BuildUiDecorPanel(ordinary, scratch, kUiDecorMaxPanelPieces - 1) == 0);
    CHECK(BuildUiDecorPanel(ordinary, nullptr, kUiDecorMaxPanelPieces) == 0);

    UiDecorPanelDesc panelScratch[kUiDecorPanelsPerOptionsPage] = {};
    const UiOptionsPageLayout probe = BuildUiOptionsPageLayout(8);
    CHECK(BuildUiOptionsPagePanels(probe, panelScratch,
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
    CHECK(tallest.topMask.x >= 71.0f);
    CHECK(Right(tallest.contentMask) <= 1368.0f);
    CHECK(Bottom(tallest.contentMask) <= 940.0f);
    CHECK(tallest.topMask.y >= 0.0f);
    CHECK(Right(tallest.contentMask) <= kLogicalWidth);
    CHECK(Bottom(tallest.contentMask) <= kLogicalHeight);

    if (OpenShimTest::FailureCount() == 0)
        std::printf("ui_decor_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
