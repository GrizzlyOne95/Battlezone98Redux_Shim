#include "ui_decor.h"

namespace BZROpenShim
{
    namespace
    {
        constexpr float kCorner = 32.0f;
        constexpr float kEdge = 8.0f;
        constexpr float kTechRightWidth = 77.0f;
        constexpr float kTechRightHeight = kUiDecorTechTopRightHeight;
        constexpr float kTechLeftWidth = 77.0f;
        constexpr float kTechLeftHeight = kUiDecorTechBottomLeftHeight;

        // One 1030 px column shared by both pages, so the header, toolbar and
        // row grid line up as a single panel stack instead of three unrelated
        // rectangles.
        constexpr float kPanelX = 205.0f;
        constexpr float kPanelWidth = 1030.0f;
        // Text sits a corner tile in from the panel edge; the row plates, which
        // carry their own border art, only need to clear the 8 px edge run.
        constexpr float kTextInset = kCorner;
        constexpr float kPlateInset = 15.0f;
        constexpr float kColumnGap = 20.0f;

        constexpr float kHeaderY = 132.0f;
        constexpr float kHeaderHeight = 152.0f;
        constexpr float kToolbarPanelY = 296.0f;
        constexpr float kToolbarPanelHeight = 64.0f;
        constexpr float kContentTop = 372.0f;

        // Header lines are sized for the stock UI face, which renders about
        // 26 logical px tall: a 22 px line box crowds the glyphs against the
        // next line and against the panel border.
        constexpr float kHeaderLineHeight = 28.0f;
        constexpr float kTitleHeight = 30.0f;

        constexpr float kRowPitch = 42.0f;
        constexpr float kRowHeight = 36.0f;
        constexpr float kRowLabelWidth = 270.0f;
        constexpr float kRowValueOffsetX = 280.0f;
        constexpr float kRowValueWidth = 200.0f;
        constexpr float kRowPlateInsetX = 10.0f;
        constexpr float kRowPlateWidth = kRowValueOffsetX + kRowValueWidth + kRowPlateInsetX;

        // Clearance reserved inside the content panel for the two stock
        // ornaments, plus a little air so the first row is not welded to the
        // diagonal art.
        constexpr float kTopOrnamentClearance = kUiDecorTechTopRightHeight + 4.0f;
        constexpr float kBottomOrnamentClearance = kUiDecorTechBottomLeftHeight + 12.0f;

        bool Push(UiDecorPiece*& cursor,
                  size_t& remaining,
                  const char* texture,
                  float x,
                  float y,
                  float width,
                  float height)
        {
            if (!cursor || remaining == 0 || !texture || width <= 0.0f || height <= 0.0f)
                return false;

            cursor->texture = texture;
            cursor->rect = { x, y, width, height };
            ++cursor;
            --remaining;
            return true;
        }
    }

    size_t BuildUiDecorPanel(const UiDecorPanelDesc& desc,
                             UiDecorPiece* outPieces,
                             size_t outCapacity)
    {
        if (!outPieces || desc.rect.width < kCorner * 2.0f ||
            desc.rect.height < kCorner * 2.0f)
        {
            return 0;
        }

        const size_t required = 8u +
            ((desc.flags & UI_DECOR_FILL) ? 1u : 0u) +
            ((desc.flags & UI_DECOR_TECH) ? 2u : 0u);
        if (outCapacity < required)
            return 0;

        UiDecorPiece* cursor = outPieces;
        size_t remaining = outCapacity;
        const float x = desc.rect.x;
        const float y = desc.rect.y;
        const float width = desc.rect.width;
        const float height = desc.rect.height;

        if (desc.flags & UI_DECOR_FILL)
            Push(cursor, remaining, "uibg.png", x, y, width, height);

        Push(cursor, remaining, "uitl.png", x, y, kCorner, kCorner);
        Push(cursor, remaining, "uitr.png", x + width - kCorner, y, kCorner, kCorner);
        Push(cursor, remaining, "uibl.png", x, y + height - kCorner, kCorner, kCorner);
        Push(cursor, remaining, "uibr.png", x + width - kCorner, y + height - kCorner, kCorner, kCorner);
        Push(cursor, remaining, "uitop.png", x + kCorner, y, width - 2.0f * kCorner, kEdge);
        Push(cursor, remaining, "uibot.png", x + kCorner, y + height - kEdge,
             width - 2.0f * kCorner, kEdge);
        Push(cursor, remaining, "uileft.png", x, y + kCorner, kEdge,
             height - 2.0f * kCorner);
        Push(cursor, remaining, "uiright.png", x + width - kEdge, y + kCorner,
             kEdge, height - 2.0f * kCorner);

        if (desc.flags & UI_DECOR_TECH)
        {
            Push(cursor, remaining, "uitrch.png", x + width - kTechRightWidth, y,
                 kTechRightWidth, kTechRightHeight);
            Push(cursor, remaining, "uiblch.png", x, y + height - kTechLeftHeight,
                 kTechLeftWidth, kTechLeftHeight);
        }

        return required;
    }

    size_t BuildUiDecorHeader(const UiDecorRect& rect,
                              UiDecorPiece* outPieces,
                              size_t outCapacity)
    {
        UiDecorPanelDesc desc = {};
        desc.rect = rect;
        desc.flags = UI_DECOR_FILL;
        return BuildUiDecorPanel(desc, outPieces, outCapacity);
    }

    UiOptionsPageLayout BuildUiOptionsPageLayout(size_t rowsPerColumn)
    {
        UiOptionsPageLayout layout = {};

        layout.headerPanel = { kPanelX, kHeaderY, kPanelWidth, kHeaderHeight };
        layout.toolbarPanel = { kPanelX, kToolbarPanelY, kPanelWidth, kToolbarPanelHeight };

        const float textX = kPanelX + kTextInset;
        const float textWidth = kPanelWidth - 2.0f * kTextInset;
        layout.headerTextWidth = textWidth;
        layout.title = { textX, kHeaderY + 12.0f, textWidth, kTitleHeight };
        layout.statusLine1 = { textX, kHeaderY + 52.0f, textWidth, kHeaderLineHeight };
        layout.statusLine2 = { textX, kHeaderY + 84.0f, textWidth, kHeaderLineHeight };
        layout.contextLine = { textX, kHeaderY + 116.0f, textWidth, kHeaderLineHeight };

        layout.toolbarHeight = 42.0f;
        layout.toolbarY = kToolbarPanelY + (kToolbarPanelHeight - layout.toolbarHeight) * 0.5f;
        layout.toolbarLeftX = kPanelX + 25.0f;
        layout.toolbarRightX = kPanelX + kPanelWidth - 25.0f;
        layout.toolbarGap = 10.0f;

        layout.rowLeftX = kPanelX + kPlateInset + kRowPlateInsetX;
        layout.rowRightX = layout.rowLeftX + kRowPlateWidth + kColumnGap;
        layout.rowPitch = kRowPitch;
        layout.rowHeight = kRowHeight;
        layout.rowLabelYInset = 4.0f;
        layout.rowLabelWidth = kRowLabelWidth;
        layout.rowLabelTextWidth = kRowLabelWidth - 12.0f;
        layout.rowValueOffsetX = kRowValueOffsetX;
        layout.rowValueWidth = kRowValueWidth;
        layout.rowValueTextWidth = kRowValueWidth - 16.0f;
        layout.rowPlateInsetX = kRowPlateInsetX;

        const float rowBlockHeight = rowsPerColumn == 0
            ? 0.0f
            : static_cast<float>(rowsPerColumn - 1) * layout.rowPitch + layout.rowHeight;
        layout.rowStartY = kContentTop + kTopOrnamentClearance;
        layout.contentPanel = {
            kPanelX,
            kContentTop,
            kPanelWidth,
            kTopOrnamentClearance + rowBlockHeight + kBottomOrnamentClearance
        };

        // The masks blank the stock page underneath; they run a little wider and
        // taller than the panels so no unmasked seam shows at a panel edge.
        constexpr float kMaskBleed = 16.0f;
        layout.topMask = {
            kPanelX - kMaskBleed,
            kHeaderY - kMaskBleed,
            kPanelWidth + 2.0f * kMaskBleed,
            kToolbarPanelY + kToolbarPanelHeight + kMaskBleed - (kHeaderY - kMaskBleed)
        };
        layout.contentMask = {
            kPanelX - kMaskBleed,
            kContentTop - kMaskBleed,
            kPanelWidth + 2.0f * kMaskBleed,
            layout.contentPanel.height + 2.0f * kMaskBleed
        };
        return layout;
    }

    size_t LayoutUiToolbarRow(const UiOptionsPageLayout& layout,
                              const float* widths,
                              size_t count,
                              size_t rightAlignedFrom,
                              UiDecorRect* outRects,
                              size_t outCapacity)
    {
        if (!widths || !outRects || count == 0 || outCapacity < count)
            return 0;
        if (rightAlignedFrom > count)
            rightAlignedFrom = count;

        float cursor = layout.toolbarLeftX;
        for (size_t index = 0; index < rightAlignedFrom; ++index)
        {
            outRects[index] = { cursor, layout.toolbarY, widths[index], layout.toolbarHeight };
            cursor += widths[index] + layout.toolbarGap;
        }

        float rightCursor = layout.toolbarRightX;
        for (size_t index = count; index > rightAlignedFrom; --index)
        {
            const size_t slot = index - 1;
            rightCursor -= widths[slot];
            outRects[slot] = { rightCursor, layout.toolbarY, widths[slot], layout.toolbarHeight };
            rightCursor -= layout.toolbarGap;
        }

        return count;
    }
}
