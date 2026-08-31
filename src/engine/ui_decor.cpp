#include "ui_decor.h"

namespace BZROpenShim
{
    namespace
    {
        // Flat single-colour tiles; see resources/ui/custom_widgets/mkui.py.
        constexpr const char* kLineTexture = "uiline.png";

        // Both pages are centred on the 1440 px logical screen.
        constexpr float kPageCenterX = 720.0f;

        // Two column widths, both centred. The header band overlaps the stock
        // frame's corner brackets -- measured from keyOptions_center.png, the
        // clear span is only x 236..1203 at y=160 -- so header text is held to
        // the narrow column. Below y=280 the frame opens up to x 71..1368, so
        // the toolbar and row grid use the wide column.
        constexpr float kHeaderWidth = 1030.0f;
        constexpr float kBodyWidth = 1140.0f;
        constexpr float kHeaderX = kPageCenterX - kHeaderWidth * 0.5f;
        constexpr float kBodyX = kPageCenterX - kBodyWidth * 0.5f;

        // Header text is inset far enough to clear the brackets on both sides.
        constexpr float kHeaderTextInset = 32.0f;
        constexpr float kPlateInset = 15.0f;
        constexpr float kColumnGap = 20.0f;

        constexpr float kHeaderY = 132.0f;
        constexpr float kHeaderHeight = 184.0f;
        constexpr float kToolbarPanelY = 328.0f;
        constexpr float kToolbarPanelHeight = 64.0f;
        constexpr float kContentTop = 404.0f;

        // The stock face renders about 26 logical px tall; a 22 px line box
        // crowds the glyphs against the next line.
        constexpr float kHeaderLineHeight = 28.0f;
        constexpr float kTitleHeight = 32.0f;
        // Offsets from kHeaderY. Title, then the hover-description pair, then
        // the static help pair, with a gap between the two pairs.
        constexpr float kTitleOffset = 12.0f;
        constexpr float kStatusOffset = 48.0f;
        constexpr float kContextOffset = 110.0f;

        constexpr float kRowPitch = 42.0f;
        constexpr float kRowHeight = 36.0f;
        // The widest keybind action ("Toggle Map Elevation") and the widest
        // binding ("Tab + Ctrl | EditMode") both have to render un-truncated,
        // which is what the wide column buys.
        constexpr float kRowLabelWidth = 320.0f;
        constexpr float kRowValueOffsetX = 325.0f;
        constexpr float kRowValueWidth = 210.0f;
        constexpr float kRowPlateInsetX = 10.0f;
        constexpr float kRowFootprintWidth =
            kRowValueOffsetX + kRowValueWidth + kRowPlateInsetX;

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
        const float thickness = kUiDecorBorderThickness;
        if (!outPieces || outCapacity < kUiDecorMaxPanelPieces ||
            desc.rect.width < thickness * 4.0f || desc.rect.height < thickness * 4.0f)
        {
            return 0;
        }

        UiDecorPiece* cursor = outPieces;
        size_t remaining = outCapacity;
        const float x = desc.rect.x;
        const float y = desc.rect.y;
        const float w = desc.rect.width;
        const float h = desc.rect.height;

        // Top and bottom run the full width; the side bars sit between them so
        // the four bars meet at the corners without overlapping.
        Push(cursor, remaining, kLineTexture, x, y, w, thickness);
        Push(cursor, remaining, kLineTexture, x, y + h - thickness, w, thickness);
        Push(cursor, remaining, kLineTexture, x, y + thickness,
             thickness, h - 2.0f * thickness);
        Push(cursor, remaining, kLineTexture, x + w - thickness, y + thickness,
             thickness, h - 2.0f * thickness);

        return kUiDecorMaxPanelPieces;
    }

    UiOptionsPageLayout BuildUiOptionsPageLayout(size_t rowsPerColumn)
    {
        UiOptionsPageLayout layout = {};

        layout.headerPanel = { kHeaderX, kHeaderY, kHeaderWidth, kHeaderHeight };
        layout.toolbarPanel = { kBodyX, kToolbarPanelY, kBodyWidth, kToolbarPanelHeight };

        const float textX = kHeaderX + kHeaderTextInset;
        const float textWidth = kHeaderWidth - 2.0f * kHeaderTextInset;
        layout.headerTextWidth = textWidth;
        layout.title = { textX, kHeaderY + kTitleOffset, textWidth, kTitleHeight };
        layout.statusLine1 = { textX, kHeaderY + kStatusOffset, textWidth, kHeaderLineHeight };
        layout.statusLine2 = { textX, kHeaderY + kStatusOffset + kHeaderLineHeight,
                               textWidth, kHeaderLineHeight };
        layout.contextLine1 = { textX, kHeaderY + kContextOffset, textWidth, kHeaderLineHeight };
        layout.contextLine2 = { textX, kHeaderY + kContextOffset + kHeaderLineHeight,
                                textWidth, kHeaderLineHeight };

        layout.toolbarHeight = 42.0f;
        layout.toolbarY = kToolbarPanelY + (kToolbarPanelHeight - layout.toolbarHeight) * 0.5f;
        layout.toolbarLeftX = kBodyX + 25.0f;
        layout.toolbarRightX = kBodyX + kBodyWidth - 25.0f;
        layout.toolbarGap = 10.0f;

        layout.rowLeftX = kBodyX + kPlateInset + kRowPlateInsetX;
        layout.rowRightX = layout.rowLeftX + kRowFootprintWidth + kColumnGap;
        layout.rowPitch = kRowPitch;
        layout.rowHeight = kRowHeight;
        layout.rowLabelYInset = 4.0f;
        layout.rowLabelWidth = kRowLabelWidth;
        layout.rowLabelTextWidth = kRowLabelWidth - 12.0f;
        layout.rowValueOffsetX = kRowValueOffsetX;
        layout.rowValueWidth = kRowValueWidth;
        layout.rowValueTextWidth = kRowValueWidth - 16.0f;
        layout.rowPlateInsetX = kRowPlateInsetX;
        // The plate starts one inset before rowLeftX and ends one inset before
        // the value button. Leaving the two button-backed views disjoint is
        // required for both visible button art and reliable click dispatch.
        layout.rowPlateWidth = kRowValueOffsetX;

        const float rowBlockHeight = rowsPerColumn == 0
            ? 0.0f
            : static_cast<float>(rowsPerColumn - 1) * layout.rowPitch + layout.rowHeight;
        layout.rowStartY = kContentTop + kUiDecorPanelPadding;
        layout.contentPanel = {
            kBodyX,
            kContentTop,
            kBodyWidth,
            kUiDecorPanelPadding + rowBlockHeight + kUiDecorPanelPadding
        };

        // The masks blank the stock page underneath. They span the wider of the
        // two columns and run a little past every panel edge so no lit strip of
        // the stock screen shows through at a seam.
        constexpr float kMaskBleed = 16.0f;
        const float maskX = kBodyX - kMaskBleed;
        const float maskWidth = kBodyWidth + 2.0f * kMaskBleed;
        layout.topMask = {
            maskX,
            kHeaderY - kMaskBleed,
            maskWidth,
            kToolbarPanelY + kToolbarPanelHeight + kMaskBleed - (kHeaderY - kMaskBleed)
        };
        layout.contentMask = {
            maskX,
            kContentTop - kMaskBleed,
            maskWidth,
            layout.contentPanel.height + 2.0f * kMaskBleed
        };
        return layout;
    }

    size_t BuildUiOptionsPagePanels(const UiOptionsPageLayout& layout,
                                    UiDecorPanelDesc* outPanels,
                                    size_t outCapacity)
    {
        if (!outPanels || outCapacity < kUiDecorPanelsPerOptionsPage)
            return 0;

        outPanels[0].rect = layout.toolbarPanel;
        outPanels[1].rect = layout.contentPanel;
        return kUiDecorPanelsPerOptionsPage;
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
