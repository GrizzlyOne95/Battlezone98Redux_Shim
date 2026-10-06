// scrap_pilot_hud.cpp
// BZR Open Shim - scrap/pilot HUD legacy layout (Display tier): baseline
// capture, UI-scale inversion, command-menu anchor, legacy plate draw hooks
// and colours, and its bridge accessors, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Scrap/pilot HUD geometry. The stock layout builder at 0x005C6CF0
        // recomputes every one of these whenever the viewport or the UI-scale
        // setting changes; the gauge draw at 0x005C6F70 then consumes them.
        // With (sx, sy) the live UI scale pair and W the viewport width:
        //   scrapPanel = (W/2 - 88*sx, 5*sy)   pilotPanel = (W/2, 5*sy)
        //   scrapTitle = scrapPanel + (50*sx,  5*sy)
        //   scrapValue = scrapPanel + (50*sx, 14*sy)
        //   pilotTitle = pilotPanel + (40*sx,  5*sy)
        //   pilotValue = pilotPanel + (40*sx, 14*sy)
        // The four text points come first so the existing group helpers and the
        // mod bridge keep addressing scrap as group 0/1 and pilot as group 2/3;
        // the two backplate sprite anchors follow. Each point is an int x with
        // its y at +4.
        //
        // Every engine address this file uses comes from the ScrapHud*,
        // CommandMenu*, CommandUi*, HudViewport*, HudColor*, HudFillRect and
        // HudSpriteSubmit engine_addresses rows in scripts/patches.json, bound
        // all or nothing on first use, so a new game build is carried across
        // by reverse_engineering/build_port instead of by editing this file.
        // Code rows guard the pristine bytes of sites legacy mode rewrites, so
        // binding happens before any rewrite and is not repeated.
        struct ScrapHudAddresses
        {
            uint32_t points[6] = {};          // scrap title, scrap value, pilot title, pilot value, scrap plate, pilot plate
            uint32_t commandMenuRowRects = 0;
            uint32_t commandUiBoundsLeft = 0;
            uint32_t commandUiUnderlaySpriteId = 0;
            uint32_t commandMenuAltLayoutFlag = 0;
            uint32_t viewportWidth = 0;
            uint32_t viewportHeight = 0;
            uint32_t colorWhite = 0, colorBlue = 0, colorGreen = 0;
            uint32_t fillRect = 0;
            uint32_t spriteSubmit = 0;
            uint32_t scrapPanelSubmitCall = 0, pilotPanelSubmitCall = 0;
            uint32_t colorLoad[4] = {};       // scrap title, scrap value, pilot title, pilot value
            uint32_t alignPush[4] = {};
            // The submit CALLs as found, so turning legacy mode off restores
            // exactly what was there.
            uint8_t scrapPanelSubmitOriginal[5] = {};
            uint8_t pilotPanelSubmitOriginal[5] = {};
        };

        static ScrapHudAddresses g_ScrapHud;

        static bool ScrapHudAddressesBound()
        {
            static const bool bound = [] {
                ScrapHudAddresses& a = g_ScrapHud;
                const HookEngine::EngineRow rows[] = {
                    { "ScrapHudScrapTitlePoint", &a.points[0] },
                    { "ScrapHudScrapValuePoint", &a.points[1] },
                    { "ScrapHudPilotTitlePoint", &a.points[2] },
                    { "ScrapHudPilotValuePoint", &a.points[3] },
                    { "ScrapHudScrapPanelPoint", &a.points[4] },
                    { "ScrapHudPilotPanelPoint", &a.points[5] },
                    { "CommandMenuRowRects", &a.commandMenuRowRects },
                    { "CommandUiBoundsLeft", &a.commandUiBoundsLeft },
                    { "CommandUiUnderlaySpriteId", &a.commandUiUnderlaySpriteId },
                    { "CommandMenuAltLayoutFlag", &a.commandMenuAltLayoutFlag },
                    { "HudViewportWidth", &a.viewportWidth },
                    { "HudViewportHeight", &a.viewportHeight },
                    { "HudColorWhite", &a.colorWhite },
                    { "HudColorBlue", &a.colorBlue },
                    { "HudColorGreen", &a.colorGreen },
                    { "HudFillRect", &a.fillRect },
                    { "HudSpriteSubmit", &a.spriteSubmit },
                    { "ScrapHudScrapPanelSubmitCall", &a.scrapPanelSubmitCall },
                    { "ScrapHudPilotPanelSubmitCall", &a.pilotPanelSubmitCall },
                    { "ScrapHudScrapTitleColorLoad", &a.colorLoad[0] },
                    { "ScrapHudScrapValueColorLoad", &a.colorLoad[1] },
                    { "ScrapHudPilotTitleColorLoad", &a.colorLoad[2] },
                    { "ScrapHudPilotValueColorLoad", &a.colorLoad[3] },
                    { "ScrapHudScrapTitleAlignPush", &a.alignPush[0] },
                    { "ScrapHudScrapValueAlignPush", &a.alignPush[1] },
                    { "ScrapHudPilotTitleAlignPush", &a.alignPush[2] },
                    { "ScrapHudPilotValueAlignPush", &a.alignPush[3] },
                };
                if (!HookEngine::BindEngineRows("Scrap/pilot HUD", rows))
                    return false;
                // The guard bytes just matched, so these are the stock CALLs.
                return HookEngine::ReadMemory(a.scrapPanelSubmitCall, a.scrapPanelSubmitOriginal,
                                              sizeof(a.scrapPanelSubmitOriginal)) &&
                       HookEngine::ReadMemory(a.pilotPanelSubmitCall, a.pilotPanelSubmitOriginal,
                                              sizeof(a.pilotPanelSubmitOriginal));
            }();
            return bound;
        }

        constexpr size_t kScrapPilotHudScrapPanelPoint = 4;

        constexpr size_t kScrapPilotHudPilotPanelPoint = 5;

        // The legacy layout is BZ 1.5's, reproduced in UI design space, where
        // one unit is one pixel at scale 1. The two games share that space: the
        // command menu occupies design x 10..156 in Redux (built at 0x0049F9E0
        // from left 10 and width 23 + 4 + 120 = 147) and in BZ 1.5, so one BZ
        // 1.5 pixel is one Redux design unit and the whole 1.5 gauge transfers
        // unchanged. It therefore holds the same relationship to the command
        // menu at every resolution and UI scale.
        //
        // From the shipped 1.5 build, with the plate origin at 166, 0:
        //   SCRAP_PANEL_POS (166,  0)   SCRAP_TITLE_POS (171, 11)
        //   SCRAP_GAUGE_POS (171, 21)   PILOT_PANEL_POS (166, 34)
        //   PILOT_TITLE_POS (171, 38)   PILOT_GAUGE_POS (171, 48)
        // The y values are static data in bzone.exe and each x comes from that
        // global's dynamic initializer. SCRAP_PANEL_POS.y is 0: PILOT_PANEL_POS
        // sits at 34, which is exactly the scrap plate's height, so the two
        // plates stack flush from the top of the screen.
        constexpr double kLegacyScrapPilotHudDesignGap = 9.0;   // 166 - 157

        constexpr double kLegacyScrapPilotHudDesignLeft = 166.0;

        constexpr int kLegacyScrapPlateY = 0;

        constexpr int kLegacyPilotPlateY = 34;

        constexpr int kLegacyTextInsetX = 5;                    // 171 - 166

        constexpr int kLegacyScrapTitleY = 11;

        constexpr int kLegacyScrapValueY = 21;

        constexpr int kLegacyPilotTitleY = 38;

        constexpr int kLegacyPilotValueY = 48;

        constexpr int kLegacyScrapPilotHudBlockWidth = 58;

        constexpr int kLegacyScrapPilotHudBlockHeight = 60;     // 34 + 26

        // Live command menu row rects, 13 x {left, top, right, bottom}, rebuilt
        // by 0x0049F9E0 on every viewport/UI-scale change. Anchoring to row 0's
        // right edge keeps the gauge clamped to the menu even if a mod or a
        // later patch moves it; the design constant above is the fallback for
        // when the rects have not been built yet.
        // The row rects are the menu's content box; the frame drawn behind it
        // is a separate sprite and is wider. CommandUI::Render at 0x004A08E0
        // submits that frame as
        //   x = bounds.left - (int)(sx * 18)
        //   w = (int)(((spriteWidth + 110) * sx) / 2)
        // where bounds.left (0x0260D748, cached by 0x0049F9E0) is the title
        // row's left, design 10. So the frame starts 8 design units off the
        // left edge of the screen, and because the +110 bias is not the
        // matching 8 units on the right, it also runs past the 157-unit row
        // right edge. BZ 1.5's gauge sat 9 units right of its menu with no
        // frame to clear, so measuring that same 9 from whichever edge is
        // further right keeps the stock spacing where the frame is narrow and
        // stops the block landing on the frame where it is not.
        //
        // The frame is only submitted for viewports wider than 400 and only in
        // the normal menu layout (0x00915567 == 0). The alt layout draws no
        // frame, and its wider 156-unit rows already come through the live row
        // rect.
        constexpr double kCommandUiUnderlayLeftInset = 18.0;

        constexpr int kCommandUiUnderlayWidthBias = 110;

        constexpr int kCommandUiUnderlayMinViewportWidth = 400;

        // Stock layout literals from 0x005C6CF0, used to recover the live UI
        // scale from a freshly built stock layout. The engine's own scale
        // globals at 0x02BF041C are transient render state that only holds the
        // HUD scale inside the HUD draw, so they cannot be sampled from a tick.
        constexpr double kScrapPilotHudStockHalfBlock = 88.0;   // pilotPanelX - scrapPanelX

        constexpr double kScrapPilotHudStockValueDrop = 14.0;   // scrapValueY - scrapPanelY

        constexpr ScrapPilotHudPlateRun kScrapPlateRuns[] = {
            {  0,  9,  0, 29 }, {  9, 10,  0, 35 }, { 10, 11,  0, 41 },
            { 11, 12,  0, 46 }, { 12, 13,  0, 49 }, { 13, 14,  0, 52 },
            { 14, 15,  0, 54 }, { 15, 16,  0, 56 }, { 16, 17,  0, 57 },
            { 17, 25,  0, 58 }, { 25, 26,  0, 57 }, { 26, 27,  0, 56 },
            { 27, 28,  0, 54 }, { 28, 29,  0, 52 }, { 29, 30,  0, 49 },
            { 30, 31,  0, 46 }, { 31, 32,  0, 41 }, { 32, 33,  0, 35 },
            { 33, 34,  0, 29 },
        };

        constexpr ScrapPilotHudPlateRun kPilotPlateRuns[] = {
            {  0,  2,  0, 29 }, {  2,  3,  0, 35 }, {  3,  4,  0, 41 },
            {  4,  5,  0, 46 }, {  5,  6,  0, 49 }, {  6,  7,  0, 52 },
            {  7,  8,  0, 54 }, {  8,  9,  0, 56 }, {  9, 10,  0, 57 },
            { 10, 18,  0, 58 }, { 18, 19,  0, 57 }, { 19, 20,  0, 56 },
            { 20, 21,  0, 54 }, { 21, 22,  0, 52 }, { 22, 23,  0, 49 },
            { 23, 24,  0, 46 }, { 24, 25,  1, 41 }, { 25, 26,  2, 35 },
        };

        constexpr ScrapPilotHudPlate kScrapPlate = {
            kScrapPlateRuns, sizeof(kScrapPlateRuns) / sizeof(kScrapPlateRuns[0])
        };

        constexpr ScrapPilotHudPlate kPilotPlate = {
            kPilotPlateRuns, sizeof(kPilotPlateRuns) / sizeof(kPilotPlateRuns[0])
        };

        // Legacy mode hides Redux's blue-tinted backplate art and draws the 1.5
        // plates in its place. The stock atlas has no opaque black region to
        // repoint the sprite UVs at, so each run is a filled quad through the
        // engine's own 2D rect helper.
        //
        // Both backplates are submitted by
        //   FUN_0068CA30(buffer, material, spriteId, x, y, w, h, 1, 0)
        // where MSVC reuses the seven arguments already pushed for the
        // preceding FUN_004D9B40 call and cleans all nine with one `add esp,
        // 0x24`. Detouring the two submit sites lands the plate at exactly the
        // stock backplate's z, one step behind the strings, with no separate
        // z bookkeeping. The submitted sprite is zero-sized by then (the rect
        // bridge hid it), so forwarding to the original draws nothing.
        // FUN_0068AC50 only rescales alpha for modes 2/3/5, so mode 0 passes the
        // colour through untouched.
        constexpr uint32_t kLegacyScrapPilotHudPlateColor = 0xFF000000u;

        constexpr int kHudFillPassthroughMode = 0;

        // Redux passes DisplayInterface::colorWhite for all four scrap/pilot
        // strings; BZ 1.5's ScrapGauge::Render used colorBlue for scrap and
        // colorGreen for pilots. The palette globals are written by the Redux
        // port of LoadInterfaceColors at 0x004B6720.
        // Each of the four gauge strings is drawn by one FUN_004C0100 call whose
        // colour arrives as `mov reg, [colorWhite]` and whose horizontal
        // alignment arrives as a `push 1` immediate (centre on x). Legacy mode
        // rewrites the colour operand and flips the alignment to 0, which makes
        // x the string's left edge -- BZ 1.5 drew these left-aligned at
        // plate + 5. Guard on whole instructions, not bare operands.
        // Instruction shapes of the four sites; addresses are g_ScrapHud's
        // colorLoad[i] / alignPush[i] for the same index.
        struct ScrapPilotHudTextSite
        {
            uint8_t colorOpcode[2];
            size_t colorOpcodeLen;
            bool legacyBlue;   // scrap strings blue, pilot strings green
        };

        constexpr ScrapPilotHudTextSite kScrapPilotHudTextSites[] = {
            { { 0xA1, 0x00 }, 1, true },   // scrap title: mov eax, [colour]
            { { 0x8B, 0x15 }, 2, true },   // scrap value: mov edx, [colour]
            { { 0x8B, 0x15 }, 2, false },  // pilot title: mov edx, [colour]
            { { 0x8B, 0x0D }, 2, false },  // pilot value: mov ecx, [colour]
        };

        constexpr uint8_t kScrapPilotHudTextCentreAlign[2] = { 0x6A, 0x01 };

        constexpr uint8_t kScrapPilotHudTextLeftAlign[2] = { 0x6A, 0x00 };

        // Fast enough that a mission load or a resolution/UI-scale change does
        // not leave the stock top-centre layout on screen long enough to read
        // as a pop. The steady-state tick is a 12-int read and a compare; it
        // only writes when the engine has rebuilt the layout underneath us.
        constexpr ULONGLONG kScrapPilotHudRefreshMs = 200;

        static bool g_ScrapPilotHudBaselineCaptured = false;

        static std::array<int, kScrapPilotHudValueCount> g_ScrapPilotHudBaseline = {};

        static bool g_ScrapPilotHudMissionOverrideActive = false;

        static std::array<int, kScrapPilotHudValueCount> g_ScrapPilotHudMissionOverride = {};

        // What we last wrote into the engine globals. Anything else showing up
        // there means the engine rebuilt the layout, which is the only reliable
        // signal that the viewport or the UI scale changed.
        static bool g_ScrapPilotHudLastWrittenValid = false;

        static std::array<int, kScrapPilotHudValueCount> g_ScrapPilotHudLastWritten = {};

        bool g_ScrapPilotHudPanelOverrideActive = false;

        bool g_ScrapPilotHudPanelOverrideVisible = true;

        static int g_ScrapPilotHudPanelsVisibleApplied = -1;  // -1 = not applied yet

        static bool g_ScrapPilotHudLegacyColorsActive = false;

        static bool g_ScrapPilotHudColorGuardMismatchLogged = false;

        static bool g_ScrapPilotHudPlateHookActive = false;

        static bool g_ScrapPilotHudPlateGuardMismatchLogged = false;

        // UI scale the current layout was built at. The engine's own w/h reach
        // the submit hook as zero because the sprite is hidden, and its scale
        // globals are transient, so the layout pass publishes what it used.
        static double g_ScrapPilotHudPlateScaleX = 0.0;

        static double g_ScrapPilotHudPlateScaleY = 0.0;

        static int g_ScrapPilotHudLoggedAnchorLeft = -1;

        static bool TryReadScrapPilotHudLayout(std::array<int, kScrapPilotHudValueCount>& out)
        {
            __try
            {
                size_t index = 0;
                for (const uint32_t point : g_ScrapHud.points)
                {
                    const int x = *reinterpret_cast<const int*>(point);
                    const int y = *reinterpret_cast<const int*>(point + 4);
                    if (x < -4096 || x > 16384 || y < -4096 || y > 16384)
                        return false;
                    out[index++] = x;
                    out[index++] = y;
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Re-reads the engine layout and adopts it as the stock baseline unless
        // it is byte-for-byte what we last wrote. The engine silently rebuilds
        // everything from 0x005C6CF0 on a viewport or UI-scale change, so this
        // is what lets the legacy anchor re-derive itself instead of translating
        // stale numbers forever.
        static bool TryCaptureScrapPilotHudBaseline(
            std::array<int, kScrapPilotHudValueCount>& outLive)
        {
            if (!TryReadScrapPilotHudLayout(outLive))
                return false;

            bool anyNonZero = false;
            for (const int value : outLive)
                anyNonZero = anyNonZero || value != 0;
            if (!anyNonZero)
                return false;

            if (g_ScrapPilotHudLastWrittenValid && outLive == g_ScrapPilotHudLastWritten)
                return g_ScrapPilotHudBaselineCaptured;

            g_ScrapPilotHudBaseline = outLive;
            g_ScrapPilotHudBaselineCaptured = true;
            return true;
        }

        static bool TryCaptureScrapPilotHudBaseline()
        {
            std::array<int, kScrapPilotHudValueCount> live = {};
            return TryCaptureScrapPilotHudBaseline(live);
        }

        // Recovers the live UI scale from a stock layout by inverting the two
        // literals the stock builder used. The horizontal term is exact; the
        // vertical one sums two truncated engine terms, so it can read low by
        // up to ~0.15. The HUD scale is set as a uniform pair at 0x0049F9E0, so
        // snap the vertical term back onto the exact horizontal one whenever
        // they agree to within that truncation window.
        static bool TryGetScrapPilotHudUiScale(
            const std::array<int, kScrapPilotHudValueCount>& stockLayout,
            double& outScaleX,
            double& outScaleY)
        {
            const int scrapPanelX = stockLayout[kScrapPilotHudScrapPanelPoint * 2];
            const int scrapPanelY = stockLayout[kScrapPilotHudScrapPanelPoint * 2 + 1];
            const int pilotPanelX = stockLayout[kScrapPilotHudPilotPanelPoint * 2];
            const int scrapValueY = stockLayout[3];
            outScaleX = (pilotPanelX - scrapPanelX) / kScrapPilotHudStockHalfBlock;
            outScaleY = (scrapValueY - scrapPanelY) / kScrapPilotHudStockValueDrop;
            if (std::fabs(outScaleY - outScaleX) <= 0.5)
                outScaleY = outScaleX;
            return outScaleX > 0.05 && outScaleY > 0.05;
        }

        static bool TryReadScrapPilotHudViewport(int& outWidth, int& outHeight)
        {
            __try
            {
                const int width = *reinterpret_cast<const int*>(g_ScrapHud.viewportWidth);
                const int height = *reinterpret_cast<const int*>(g_ScrapHud.viewportHeight);
                if (width <= 0 || height <= 0 || width > 16384 || height > 16384)
                    return false;
                outWidth = width;
                outHeight = height;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Right edge of the command menu's first row, in screen pixels.
        static bool TryGetCommandMenuRightEdge(int viewportWidth, int& outRight)
        {
            __try
            {
                const int* rect = reinterpret_cast<const int*>(g_ScrapHud.commandMenuRowRects);
                const int left = rect[0];
                const int right = rect[2];
                if (left < 0 || right <= left || right >= viewportWidth)
                    return false;
                outRight = right;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Read together so the SEH frame stays in a function that needs no
        // unwinding.
        static bool TryReadCommandUiUnderlayGlobals(int& outSpriteId, int& outBoundsLeft)
        {
            __try
            {
                if (*reinterpret_cast<const char*>(g_ScrapHud.commandMenuAltLayoutFlag) != '\0')
                    return false;
                outSpriteId = *reinterpret_cast<const int*>(g_ScrapHud.commandUiUnderlaySpriteId);
                outBoundsLeft = *reinterpret_cast<const int*>(g_ScrapHud.commandUiBoundsLeft);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Right edge of the command menu's frame sprite, in screen pixels,
        // rebuilt exactly as 0x004A08E0 submits it. The sprite rect table this
        // reads is the same one FUN_0068F090 indexes, so the width is the one
        // the engine will use.
        static bool TryGetCommandUiUnderlayRightEdge(int viewportWidth, double scale, int& outRight)
        {
            if (viewportWidth <= kCommandUiUnderlayMinViewportWidth)
                return false;

            int spriteId = 0;
            int boundsLeft = 0;
            if (!TryReadCommandUiUnderlayGlobals(spriteId, boundsLeft))
                return false;
            // Zero until CommandUI::Render has picked an underlay for the
            // current state.
            if (spriteId <= 0)
                return false;

            HudSpriteRectRecord record = {};
            if (!TryGetHudSpriteCurrentRecord(spriteId, record) || record.w <= 0)
                return false;

            const int left =
                boundsLeft - static_cast<int>(scale * kCommandUiUnderlayLeftInset);
            const int width = static_cast<int>(
                ((record.w + kCommandUiUnderlayWidthBias) * scale) / 2.0);
            if (width <= 0)
                return false;

            const int right = left + width;
            if (right >= viewportWidth)
                return false;

            outRight = right;
            return true;
        }

        static int GetLegacyScrapPilotHudLeft(double scale)
        {
            int viewportWidth = 0;
            int viewportHeight = 0;
            int rowRight = 0;
            if (TryReadScrapPilotHudViewport(viewportWidth, viewportHeight) &&
                TryGetCommandMenuRightEdge(viewportWidth, rowRight))
            {
                int underlayRight = 0;
                const bool haveUnderlay =
                    TryGetCommandUiUnderlayRightEdge(viewportWidth, scale, underlayRight);
                const int menuRight =
                    (haveUnderlay && underlayRight > rowRight) ? underlayRight : rowRight;
                const int left = menuRight + 1 +
                    static_cast<int>(std::lround(kLegacyScrapPilotHudDesignGap * scale));

                // Only on a real move: the layout tick runs five times a second.
                if (g_ScrapPilotHudLoggedAnchorLeft != left)
                {
                    g_ScrapPilotHudLoggedAnchorLeft = left;
                    Log(L"[HUD] Scrap/pilot anchor left=%d scale=%.3f rows-right=%d frame-right=%d\n",
                        left,
                        scale,
                        rowRight,
                        haveUnderlay ? underlayRight : -1);
                }
                return left;
            }
            return static_cast<int>(std::lround(kLegacyScrapPilotHudDesignLeft * scale));
        }

        static void ClampScrapPilotHudLayoutToViewport(
            std::array<int, kScrapPilotHudValueCount>& layout,
            int blockLeft,
            int blockTop,
            int blockRight,
            int blockBottom)
        {
            int viewportWidth = 0;
            int viewportHeight = 0;
            if (!TryReadScrapPilotHudViewport(viewportWidth, viewportHeight))
                return;

            int shiftX = 0;
            int shiftY = 0;
            if (blockRight > viewportWidth)
                shiftX = viewportWidth - blockRight;
            if (blockLeft + shiftX < 0)
                shiftX = -blockLeft;
            if (blockBottom > viewportHeight)
                shiftY = viewportHeight - blockBottom;
            if (blockTop + shiftY < 0)
                shiftY = -blockTop;
            if (shiftX == 0 && shiftY == 0)
                return;

            for (size_t index = 0; index + 1 < layout.size(); index += 2)
            {
                layout[index] += shiftX;
                layout[index + 1] += shiftY;
            }
        }

        // Rebuilds BZ 1.5's gauge in design units at the live UI scale, anchored
        // to the command menu. The stock intra-group offsets are not reused:
        // 1.5's plates are a different size and its strings sit at different
        // insets, so every point is placed from the 1.5 constants.
        static std::array<int, kScrapPilotHudValueCount> BuildScrapPilotHudIniLayout()
        {
            std::array<int, kScrapPilotHudValueCount> desired = g_ScrapPilotHudBaseline;
            if (!g_ScrapPilotHudLegacyLayoutEnabled)
                return desired;

            double scaleX = 0.0;
            double scaleY = 0.0;
            if (!TryGetScrapPilotHudUiScale(desired, scaleX, scaleY))
                return desired;
            g_ScrapPilotHudPlateScaleX = scaleX;
            g_ScrapPilotHudPlateScaleY = scaleY;

            const int left = GetLegacyScrapPilotHudLeft(scaleX);
            const int top = 0;
            const auto atX = [&](int units)
            {
                return left + static_cast<int>(std::lround(units * scaleX));
            };
            const auto atY = [&](int units)
            {
                return top + static_cast<int>(std::lround(units * scaleY));
            };

            desired[0] = atX(kLegacyTextInsetX);
            desired[1] = atY(kLegacyScrapTitleY);
            desired[2] = atX(kLegacyTextInsetX);
            desired[3] = atY(kLegacyScrapValueY);
            desired[4] = atX(kLegacyTextInsetX);
            desired[5] = atY(kLegacyPilotTitleY);
            desired[6] = atX(kLegacyTextInsetX);
            desired[7] = atY(kLegacyPilotValueY);
            desired[kScrapPilotHudScrapPanelPoint * 2] = atX(0);
            desired[kScrapPilotHudScrapPanelPoint * 2 + 1] = atY(kLegacyScrapPlateY);
            desired[kScrapPilotHudPilotPanelPoint * 2] = atX(0);
            desired[kScrapPilotHudPilotPanelPoint * 2 + 1] = atY(kLegacyPilotPlateY);

            ClampScrapPilotHudLayoutToViewport(
                desired,
                atX(0),
                atY(0),
                atX(kLegacyScrapPilotHudBlockWidth),
                atY(kLegacyScrapPilotHudBlockHeight));
            return desired;
        }

        static bool TryWriteScrapPilotHudLayout(
            const std::array<int, kScrapPilotHudValueCount>& desired)
        {
            __try
            {
                size_t index = 0;
                for (const uint32_t point : g_ScrapHud.points)
                {
                    *reinterpret_cast<int*>(point) = desired[index++];
                    *reinterpret_cast<int*>(point + 4) = desired[index++];
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void GetScrapPilotHudGroupTopLeft(
            const std::array<int, kScrapPilotHudValueCount>& layout,
            size_t firstPoint,
            int& outLeft,
            int& outTop)
        {
            const size_t first = firstPoint * 2;
            outLeft = layout[first];
            outTop = layout[first + 1];
            const size_t second = first + 2;
            outLeft = (std::min)(outLeft, layout[second]);
            outTop = (std::min)(outTop, layout[second + 1]);
        }

        using FnHudFillRect = void(__cdecl*)(
            void* buffer, int x1, int y1, int x2, int y2, uint32_t color, int mode);
        using FnHudSpriteSubmit = void(__cdecl*)(
            void* buffer, void* material, int spriteId,
            int x, int y, int w, int h, int a, int b);

        // Draws one BZ 1.5 plate, run by run, at the live UI scale. Runs abut
        // exactly because each edge is rounded the same way, and the fill is
        // inclusive of x2/y2. This runs at the stock backplate's submit point,
        // so the ambient sprite z is already the one-step-behind value the
        // strings are drawn in front of.
        static void DrawScrapPilotHudPlate(
            void* buffer, size_t panelPoint, const ScrapPilotHudPlate& plate)
        {
            if (!g_ScrapPilotHudLegacyLayoutEnabled || !buffer)
                return;
            const double scaleX = g_ScrapPilotHudPlateScaleX;
            const double scaleY = g_ScrapPilotHudPlateScaleY;
            if (scaleX <= 0.05 || scaleY <= 0.05)
                return;

            __try
            {
                const uint32_t point = g_ScrapHud.points[panelPoint];
                const int originX = *reinterpret_cast<const int*>(point);
                const int originY = *reinterpret_cast<const int*>(point + 4);
                const auto fill = reinterpret_cast<FnHudFillRect>(g_ScrapHud.fillRect);
                for (size_t index = 0; index < plate.runCount; ++index)
                {
                    const ScrapPilotHudPlateRun& run = plate.runs[index];
                    const int x1 = originX + static_cast<int>(std::lround(run.x0 * scaleX));
                    const int x2 = originX + static_cast<int>(std::lround(run.x1 * scaleX)) - 1;
                    const int y1 = originY + static_cast<int>(std::lround(run.y0 * scaleY));
                    const int y2 = originY + static_cast<int>(std::lround(run.y1 * scaleY)) - 1;
                    if (x2 < x1 || y2 < y1)
                        continue;
                    fill(buffer, x1, y1, x2, y2,
                         kLegacyScrapPilotHudPlateColor, kHudFillPassthroughMode);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void __cdecl ScrapPanelSubmitHook(
            void* buffer, void* material, int spriteId,
            int x, int y, int w, int h, int a, int b)
        {
            DrawScrapPilotHudPlate(buffer, kScrapPilotHudScrapPanelPoint, kScrapPlate);
            reinterpret_cast<FnHudSpriteSubmit>(g_ScrapHud.spriteSubmit)(
                buffer, material, spriteId, x, y, w, h, a, b);
        }

        static void __cdecl PilotPanelSubmitHook(
            void* buffer, void* material, int spriteId,
            int x, int y, int w, int h, int a, int b)
        {
            DrawScrapPilotHudPlate(buffer, kScrapPilotHudPilotPanelPoint, kPilotPlate);
            reinterpret_cast<FnHudSpriteSubmit>(g_ScrapHud.spriteSubmit)(
                buffer, material, spriteId, x, y, w, h, a, b);
        }

        static bool WriteScrapPilotHudSubmitCall(uintptr_t callAddr, const void* target)
        {
            uint8_t patch[5] = { 0xE8 };
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) -
                static_cast<int32_t>(callAddr + sizeof(patch));
            std::memcpy(patch + 1, &relative, sizeof(relative));
            return WritePatchBytes(callAddr, patch, sizeof(patch));
        }

        // Retargets the two backplate submit calls at the stock sprite draw so
        // legacy mode can put the BZ 1.5 plate down in their place.
        static void SetScrapPilotHudPlateHookActive(bool active)
        {
            if (active == g_ScrapPilotHudPlateHookActive)
                return;

            if (active)
            {
                if (!ExpectedBytesMatchAt(
                        g_ScrapHud.scrapPanelSubmitCall,
                        g_ScrapHud.scrapPanelSubmitOriginal,
                        sizeof(g_ScrapHud.scrapPanelSubmitOriginal)) ||
                    !ExpectedBytesMatchAt(
                        g_ScrapHud.pilotPanelSubmitCall,
                        g_ScrapHud.pilotPanelSubmitOriginal,
                        sizeof(g_ScrapHud.pilotPanelSubmitOriginal)))
                {
                    if (!g_ScrapPilotHudPlateGuardMismatchLogged)
                    {
                        g_ScrapPilotHudPlateGuardMismatchLogged = true;
                        Log(L"[HUD] Scrap/pilot plate submit sites do not match; "
                            L"legacy layout runs without a backing plate\n");
                    }
                    return;
                }

                if (!WriteScrapPilotHudSubmitCall(
                        g_ScrapHud.scrapPanelSubmitCall,
                        reinterpret_cast<const void*>(&ScrapPanelSubmitHook)))
                {
                    return;
                }
                if (!WriteScrapPilotHudSubmitCall(
                        g_ScrapHud.pilotPanelSubmitCall,
                        reinterpret_cast<const void*>(&PilotPanelSubmitHook)))
                {
                    WritePatchBytes(
                        g_ScrapHud.scrapPanelSubmitCall,
                        g_ScrapHud.scrapPanelSubmitOriginal,
                        sizeof(g_ScrapHud.scrapPanelSubmitOriginal));
                    return;
                }
            }
            else
            {
                if (!WritePatchBytes(
                        g_ScrapHud.scrapPanelSubmitCall,
                        g_ScrapHud.scrapPanelSubmitOriginal,
                        sizeof(g_ScrapHud.scrapPanelSubmitOriginal)) ||
                    !WritePatchBytes(
                        g_ScrapHud.pilotPanelSubmitCall,
                        g_ScrapHud.pilotPanelSubmitOriginal,
                        sizeof(g_ScrapHud.pilotPanelSubmitOriginal)))
                {
                    return;
                }
            }

            g_ScrapPilotHudPlateHookActive = active;
            g_ScrapPilotHudPlateGuardMismatchLogged = false;
            Log(L"[HUD] Scrap/pilot legacy plate %hs\n",
                active ? "installed" : "removed");
        }

        // Restores BZ 1.5's text treatment for the four gauge strings: the
        // scrap-blue / pilot-green split Redux dropped in favour of colorWhite,
        // and left alignment so the layout's x is the string's left edge the
        // way 1.5's Font_Print_String took it. Reverting writes both back.
        static void SetScrapPilotHudLegacyColorsActive(bool active)
        {
            if (active == g_ScrapPilotHudLegacyColorsActive)
                return;

            const uint8_t* expectedAlign =
                active ? kScrapPilotHudTextCentreAlign : kScrapPilotHudTextLeftAlign;
            const uint8_t* desiredAlign =
                active ? kScrapPilotHudTextLeftAlign : kScrapPilotHudTextCentreAlign;

            const auto legacyColorFor = [](const ScrapPilotHudTextSite& site) {
                return site.legacyBlue ? g_ScrapHud.colorBlue : g_ScrapHud.colorGreen;
            };

            for (size_t i = 0; i < std::size(kScrapPilotHudTextSites); ++i)
            {
                const ScrapPilotHudTextSite& site = kScrapPilotHudTextSites[i];
                uint8_t expected[6] = {};
                size_t expectedLen = 0;
                for (size_t index = 0; index < site.colorOpcodeLen; ++index)
                    expected[expectedLen++] = site.colorOpcode[index];
                const uint32_t currentOperand = active ? g_ScrapHud.colorWhite : legacyColorFor(site);
                std::memcpy(expected + expectedLen, &currentOperand, sizeof(currentOperand));
                expectedLen += sizeof(currentOperand);

                if (!ExpectedBytesMatchAt(g_ScrapHud.colorLoad[i], expected, expectedLen) ||
                    !ExpectedBytesMatchAt(g_ScrapHud.alignPush[i], expectedAlign, 2))
                {
                    if (!g_ScrapPilotHudColorGuardMismatchLogged)
                    {
                        g_ScrapPilotHudColorGuardMismatchLogged = true;
                        Log(L"[HUD] Scrap/pilot text site 0x%08X does not match; leaving stock\n",
                            g_ScrapHud.colorLoad[i]);
                    }
                    return;
                }
            }

            for (size_t i = 0; i < std::size(kScrapPilotHudTextSites); ++i)
            {
                const ScrapPilotHudTextSite& site = kScrapPilotHudTextSites[i];
                const uint32_t operand = active ? legacyColorFor(site) : g_ScrapHud.colorWhite;
                uint8_t operandBytes[sizeof(operand)] = {};
                std::memcpy(operandBytes, &operand, sizeof(operand));
                if (!WritePatchBytes(
                        g_ScrapHud.colorLoad[i] + site.colorOpcodeLen,
                        operandBytes,
                        sizeof(operandBytes)))
                {
                    return;
                }
                if (!WritePatchBytes(g_ScrapHud.alignPush[i], desiredAlign, 2))
                    return;
            }

            g_ScrapPilotHudLegacyColorsActive = active;
            g_ScrapPilotHudColorGuardMismatchLogged = false;
            Log(L"[HUD] Scrap/pilot text %hs\n",
                active ? "legacy (scrap blue / pilot green, left aligned)"
                       : "stock (white, centred)");
        }

        void RefreshScrapPilotHudLayout()
        {
            if (!ScrapHudAddressesBound()) return;
            const ULONGLONG now = GetTickCount64();
            if (g_ScrapPilotHudLastRefreshTick != 0 &&
                now - g_ScrapPilotHudLastRefreshTick < kScrapPilotHudRefreshMs)
            {
                return;
            }
            g_ScrapPilotHudLastRefreshTick = now;

            std::array<int, kScrapPilotHudValueCount> live = {};
            if (!TryCaptureScrapPilotHudBaseline(live) && !g_ScrapPilotHudBaselineCaptured)
                return;

            const std::array<int, kScrapPilotHudValueCount> desired =
                g_ScrapPilotHudMissionOverrideActive
                    ? g_ScrapPilotHudMissionOverride
                    : BuildScrapPilotHudIniLayout();
            if (live != desired)
            {
                if (!TryWriteScrapPilotHudLayout(desired))
                    return;
                g_ScrapPilotHudLastWritten = desired;
                g_ScrapPilotHudLastWrittenValid = true;
            }

            // Legacy mode hides Redux's own blue backplate art; the submit hook
            // draws BZ 1.5's plain black plate in its place. Reassert a hide on
            // every tick (the engine can rebuild the rect records) but a show
            // only on a change, since the show path logs per sprite.
            const bool panelsVisible = g_ScrapPilotHudPanelOverrideActive
                ? g_ScrapPilotHudPanelOverrideVisible
                : !g_ScrapPilotHudLegacyLayoutEnabled;
            const int panelsVisibleState = panelsVisible ? 1 : 0;
            // The engine's own rect table starts visible, so "not applied yet"
            // is already the visible state and needs no reassert.
            const int appliedState = g_ScrapPilotHudPanelsVisibleApplied < 0
                ? 1
                : g_ScrapPilotHudPanelsVisibleApplied;
            if (appliedState != panelsVisibleState || !panelsVisible)
            {
                SetStockScrapPilotPanelsVisible(panelsVisible);
                g_ScrapPilotHudPanelsVisibleApplied = panelsVisibleState;
            }

            SetScrapPilotHudLegacyColorsActive(g_ScrapPilotHudLegacyLayoutEnabled);
            SetScrapPilotHudPlateHookActive(g_ScrapPilotHudLegacyLayoutEnabled);
        }

        void RevertScrapPilotHudToBaseline()
        {
            if (!ScrapHudAddressesBound()) return;
            g_ScrapPilotHudMissionOverrideActive = false;
            g_ScrapPilotHudPanelOverrideActive = false;
            // Leave the applied panel-visibility state alone: a mission that hid
            // the backplates must still be seen as a hidden->visible transition
            // so the restore actually runs.
            g_ScrapPilotHudLastRefreshTick = 0;
            RefreshScrapPilotHudLayout();
        }
    }

    using namespace Hooks;

    bool GetScrapPilotHudTopLeftsFromBridge(
        int* scrapLeft,
        int* scrapTop,
        int* pilotLeft,
        int* pilotTop)
    {
        if (!ScrapHudAddressesBound()) return false;
        if (!scrapLeft || !scrapTop || !pilotLeft || !pilotTop)
            return false;
        if (!g_ScrapPilotHudBaselineCaptured && !TryCaptureScrapPilotHudBaseline())
            return false;

        const std::array<int, kScrapPilotHudValueCount> layout =
            g_ScrapPilotHudMissionOverrideActive
                ? g_ScrapPilotHudMissionOverride
                : BuildScrapPilotHudIniLayout();
        GetScrapPilotHudGroupTopLeft(layout, 0, *scrapLeft, *scrapTop);
        GetScrapPilotHudGroupTopLeft(layout, 2, *pilotLeft, *pilotTop);
        return true;
    }

    bool SetScrapPilotHudTopLeftsFromBridge(
        int scrapLeft,
        int scrapTop,
        int pilotLeft,
        int pilotTop)
    {
        if (!ScrapHudAddressesBound()) return false;
        constexpr int kMinHudCoordinate = -4096;
        constexpr int kMaxHudCoordinate = 16384;
        const int values[] = { scrapLeft, scrapTop, pilotLeft, pilotTop };
        for (const int value : values)
        {
            if (value < kMinHudCoordinate || value > kMaxHudCoordinate)
                return false;
        }
        if (!g_ScrapPilotHudBaselineCaptured && !TryCaptureScrapPilotHudBaseline())
            return false;

        std::array<int, kScrapPilotHudValueCount> desired =
            g_ScrapPilotHudMissionOverrideActive
                ? g_ScrapPilotHudMissionOverride
                : BuildScrapPilotHudIniLayout();
        int currentScrapLeft = 0;
        int currentScrapTop = 0;
        int currentPilotLeft = 0;
        int currentPilotTop = 0;
        GetScrapPilotHudGroupTopLeft(
            desired, 0, currentScrapLeft, currentScrapTop);
        GetScrapPilotHudGroupTopLeft(
            desired, 2, currentPilotLeft, currentPilotTop);

        if (g_ScrapPilotHudMissionOverrideActive &&
            currentScrapLeft == scrapLeft && currentScrapTop == scrapTop &&
            currentPilotLeft == pilotLeft && currentPilotTop == pilotTop)
        {
            return true;
        }

        const int scrapOffsetX = scrapLeft - currentScrapLeft;
        const int scrapOffsetY = scrapTop - currentScrapTop;
        const int pilotOffsetX = pilotLeft - currentPilotLeft;
        const int pilotOffsetY = pilotTop - currentPilotTop;
        // The backplate sprite anchors travel with the strings they sit behind,
        // so a mod that repositions the gauge keeps its background.
        const size_t scrapPoints[] = { 0, 1, kScrapPilotHudScrapPanelPoint };
        const size_t pilotPoints[] = { 2, 3, kScrapPilotHudPilotPanelPoint };
        for (const size_t point : scrapPoints)
        {
            desired[point * 2] += scrapOffsetX;
            desired[point * 2 + 1] += scrapOffsetY;
        }
        for (const size_t point : pilotPoints)
        {
            desired[point * 2] += pilotOffsetX;
            desired[point * 2 + 1] += pilotOffsetY;
        }

        g_ScrapPilotHudMissionOverride = desired;
        g_ScrapPilotHudMissionOverrideActive = true;
        g_ScrapPilotHudLastRefreshTick = 0;
        RefreshScrapPilotHudLayout();
        return true;
    }

    bool RestoreScrapPilotHudStockFromBridge()
    {
        if (!ScrapHudAddressesBound()) return false;
        if (!g_ScrapPilotHudBaselineCaptured && !TryCaptureScrapPilotHudBaseline())
            return false;
        g_ScrapPilotHudMissionOverride = g_ScrapPilotHudBaseline;
        g_ScrapPilotHudMissionOverrideActive = true;
        g_ScrapPilotHudLastRefreshTick = 0;
        RefreshScrapPilotHudLayout();
        return true;
    }
}
