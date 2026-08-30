#include "ui_decor.h"

#include <cassert>
#include <cstring>

using namespace BZROpenShim;

namespace
{
    float Right(const UiDecorRect& rect)
    {
        return rect.x + rect.width;
    }

    float Bottom(const UiDecorRect& rect)
    {
        return rect.y + rect.height;
    }

    bool Contains(const UiDecorRect& outer, const UiDecorRect& inner)
    {
        return inner.x >= outer.x && inner.y >= outer.y &&
               Right(inner) <= Right(outer) && Bottom(inner) <= Bottom(outer);
    }

    // Every OpenShim page is one panel column, so the three panels share an
    // edge and nothing text-bearing may sit outside its own panel.
    void VerifyPanelStack(const UiOptionsPageLayout& layout)
    {
        assert(layout.headerPanel.x == layout.toolbarPanel.x);
        assert(layout.headerPanel.x == layout.contentPanel.x);
        assert(layout.headerPanel.width == layout.toolbarPanel.width);
        assert(layout.headerPanel.width == layout.contentPanel.width);

        assert(Bottom(layout.headerPanel) < layout.toolbarPanel.y);
        assert(Bottom(layout.toolbarPanel) < layout.contentPanel.y);

        assert(Contains(layout.headerPanel, layout.title));
        assert(Contains(layout.headerPanel, layout.statusLine1));
        assert(Contains(layout.headerPanel, layout.statusLine2));
        assert(Contains(layout.headerPanel, layout.contextLine));

        // Header lines run in order and never overlap: the stock face renders
        // taller than the old 22 px line box, which is what clipped the third
        // line into the panel border.
        assert(Bottom(layout.title) <= layout.statusLine1.y);
        assert(Bottom(layout.statusLine1) <= layout.statusLine2.y);
        assert(Bottom(layout.statusLine2) <= layout.contextLine.y);
        assert(layout.statusLine1.height >= 26.0f);
        assert(layout.contextLine.height >= 26.0f);
        assert(layout.headerTextWidth <= layout.title.width);

        // The masks have to cover every panel or a lit strip of the stock page
        // shows through at a panel edge.
        assert(Contains(layout.topMask, layout.headerPanel));
        assert(Contains(layout.topMask, layout.toolbarPanel));
        assert(Contains(layout.contentMask, layout.contentPanel));
    }

    void VerifyRowGrid(const UiOptionsPageLayout& layout, size_t rowsPerColumn)
    {
        // The first and last rows stay clear of the native 72 px top-right and
        // 36 px bottom-left ornaments.
        assert(layout.rowStartY >= layout.contentPanel.y + kUiDecorTechTopRightHeight);
        const float lastRowBottom = rowsPerColumn == 0
            ? layout.rowStartY
            : layout.rowStartY + static_cast<float>(rowsPerColumn - 1) * layout.rowPitch +
                  layout.rowHeight;
        assert(lastRowBottom <=
               Bottom(layout.contentPanel) - kUiDecorTechBottomLeftHeight);
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

        // A label and its value button share a row without overlapping, and the
        // fitted text widths stop short of both boxes.
        assert(layout.rowLabelWidth <= layout.rowValueOffsetX);
        assert(layout.rowLabelTextWidth < layout.rowLabelWidth);
        assert(layout.rowValueTextWidth < layout.rowValueWidth);
        assert(layout.rowLabelYInset > 0.0f);
        assert(layout.rowLabelYInset < layout.rowHeight);
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
            // Buttons live inside the toolbar panel, with air above and below.
            assert(rects[index].y > layout.toolbarPanel.y);
            assert(Bottom(rects[index]) < Bottom(layout.toolbarPanel));
            if (index > 0)
                assert(rects[index].x >= Right(rects[index - 1]) + layout.toolbarGap);
        }

        // The row is flush with both insets: left group starts at the left one,
        // right group ends at the right one.
        assert(rects[0].x == layout.toolbarLeftX);
        assert(Right(rects[count - 1]) == layout.toolbarRightX);
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
    }
}

int main()
{
    UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
    UiDecorPanelDesc content = {};
    content.rect = { 0.0f, 0.0f, 1030.0f, 530.0f };
    content.flags = UI_DECOR_DEFAULT;
    assert(BuildUiDecorPanel(content, pieces, kUiDecorMaxPanelPieces) == 11);
    assert(std::strcmp(pieces[0].texture, "uibg.png") == 0);
    assert(std::strcmp(pieces[9].texture, "uitrch.png") == 0);
    assert(std::strcmp(pieces[10].texture, "uiblch.png") == 0);

    UiDecorPiece headerPieces[kUiDecorMaxPanelPieces] = {};
    assert(BuildUiDecorHeader({ 0.0f, 0.0f, 1000.0f, 120.0f },
                              headerPieces,
                              kUiDecorMaxPanelPieces) == 9);

    // A panel too small for its own corner tiles emits nothing rather than
    // overlapping art.
    UiDecorPanelDesc tiny = {};
    tiny.rect = { 0.0f, 0.0f, 40.0f, 40.0f };
    assert(BuildUiDecorPanel(tiny, headerPieces, kUiDecorMaxPanelPieces) == 0);
    assert(BuildUiDecorPanel(content, headerPieces, 4) == 0);

    // Settings page: Back, Check for Updates | page caption, Prev, Next.
    static const float kSettingsToolbar[] = { 140.0f, 210.0f, 130.0f, 110.0f, 110.0f };
    VerifyLayout(8, kSettingsToolbar, 5, 2);

    // Keybind page: Back, Reset, Controls, RTS Actions | Prev, Next, Refresh.
    static const float kInputToolbar[] =
        { 120.0f, 190.0f, 150.0f, 160.0f, 90.0f, 90.0f, 120.0f };
    VerifyLayout(10, kInputToolbar, 7, 4);

    // The taller page must not push its content off the 1080 px logical screen.
    const UiOptionsPageLayout tallest = BuildUiOptionsPageLayout(10);
    assert(Bottom(tallest.contentMask) <= 1080.0f);
    assert(tallest.topMask.x >= 0.0f);
    assert(Right(tallest.contentMask) <= 1440.0f);

    return 0;
}
