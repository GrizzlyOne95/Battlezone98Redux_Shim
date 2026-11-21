// rts_range_labels.cpp
// BZR Open Shim - RTS range ring labels. Draws each published ring's name
// ("WEAPON RANGE", "RADAR RANGE", "MINE TRIGGER", "ARTILLERY RANGE") one
// letter at a time along the ring's projected arc, in the ring's colour,
// centred on the part of the ring nearest the bottom of the screen. Letters
// stay upright. Text uses the same stock HUD text call as the producer rally
// label and badges (HudGaugeOverlay); world points are projected with the
// stock camera record (ProducerRallyPolicy::ProjectToScreen), read as
// producer_badges.cpp does. Reads only; nothing is sent or saved.
// Placement maths and hide rules: include/rts_range_rings_policy.h.
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "openshim_l10n_text.h"
#include "producer_rally_policy.h"
#include "rts_range_labels.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>

using BZROpenShim::L10n::ShimText;

namespace BZROpenShim::Hooks
{
    namespace
    {
        namespace RR = RtsRangeRings;

        constexpr const char* kComponent = "rtsrangelabels";
        using FnCameraRecord = const uint8_t*(__cdecl*)();

        // Camera record, as producer_rally_points.cpp / producer_badges.cpp.
        constexpr size_t kCameraMatrixOffset = 0x40;
        constexpr size_t kCameraTranslationOffset = kCameraMatrixOffset + 0x28;
        constexpr size_t kViewRecordCurrentViewOffset = 8;
        constexpr size_t kViewRecordCameraValidBackOffset = 0x20;

        uint32_t g_CameraRecordAddr = 0;
        uint32_t g_ViewRecordAddr = 0;
        bool g_BindAttempted = false;
        bool g_Bound = false;
        bool g_PainterSet = false;

        SRWLOCK g_Lock = SRWLOCK_INIT;
        RangeLabelRing g_Rings[RR::kMaxLabelRings];
        size_t g_RingCount = 0;
        std::atomic<bool> g_Active{false};

        // Painter scratch, frame thread only (kept off the painter's stack).
        RR::NearItem g_Items[RR::kMaxLabelRings];
        RR::ScreenPoint g_Screen[RR::kLabelArcPoints];
        float g_GlyphW[RR::kMaxLabelChars];
        RR::GlyphPos g_Glyph[RR::kMaxLabelChars];
        float g_CharW[128];
        float g_CharH = 0.0f;

        bool BindRows()
        {
            if (g_BindAttempted)
                return g_Bound;
            g_BindAttempted = true;
            const HookEngine::EngineRow rows[] = {
                {"GetCameraRecord", &g_CameraRecordAddr},
                {"ViewRecord", &g_ViewRecordAddr},
            };
            g_Bound = HookEngine::BindEngineRows("RTS range labels", rows) && HudGaugeOverlay::Ensure();
            LogShimA(g_Bound ? LogLevel::Info : LogLevel::Warn, kComponent, "[RTSRANGE] labels %s",
                     g_Bound ? "installed" : "unavailable (camera rows or HUD overlay); no labels");
            return g_Bound;
        }

        bool ReadCamera(ProducerRallyPolicy::CameraProjection& cam)
        {
            if (!g_CameraRecordAddr || !g_ViewRecordAddr)
                return false;
            __try
            {
                const int view = *reinterpret_cast<const int*>(g_ViewRecordAddr + kViewRecordCurrentViewOffset);
                if (view != 0 && view != 1 && view != 2 && view != 7)
                    return false;
                if (*reinterpret_cast<const int*>(g_ViewRecordAddr - kViewRecordCameraValidBackOffset) == 0)
                    return false;
                const uint8_t* record = reinterpret_cast<FnCameraRecord>(g_CameraRecordAddr)();
                if (!record)
                    return false;
                const float* head = reinterpret_cast<const float*>(record);
                cam.centerX = head[0];
                cam.centerY = head[1];
                cam.scaleX = head[2];
                cam.scaleY = head[3];
                std::memcpy(cam.rot, record + kCameraMatrixOffset, sizeof(cam.rot));
                std::memcpy(cam.trans, record + kCameraTranslationOffset, sizeof(cam.trans));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        const char* LabelText(RR::Kind kind)
        {
            const char* text = "";
            switch (kind)
            {
            case RR::Kind::Artillery:
                text = ShimText("openshim_ui:rts_range_label_artillery", "ARTILLERY RANGE");
                break;
            case RR::Kind::Weapon:
                text = ShimText("openshim_ui:rts_range_label_weapon", "WEAPON RANGE");
                break;
            case RR::Kind::Radar:
                text = ShimText("openshim_ui:rts_range_label_radar", "RADAR RANGE");
                break;
            case RR::Kind::Mine:
                text = ShimText("openshim_ui:rts_range_label_mine", "MINE TRIGGER");
                break;
            }
            return text ? text : "";
        }

        // One glyph's measured width in px; cached for the frame.
        float GlyphWidth(const HudGaugeOverlay::Frame& frame, unsigned char c) noexcept
        {
            if (c >= 128)
                c = '?';
            if (g_CharW[c] >= 0.0f)
                return g_CharW[c];
            char text[2] = {static_cast<char>(c), 0};
            float w = 0.0f, h = 0.0f;
            if (frame.measure && frame.style)
            {
                __try
                {
                    frame.measure(frame.style, text, &w, &h);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    w = 0.0f;
                    h = 0.0f;
                }
            }
            if (!(std::isfinite(w) && w > 0.0f && w < 100.0f))
                w = 7.0f; // per-glyph estimate when the measure is unusable
            if (std::isfinite(h) && h > 0.0f && h < 100.0f && g_CharH <= 0.0f)
                g_CharH = h;
            g_CharW[c] = w;
            return w;
        }

        bool PaintLabels(const HudGaugeOverlay::Frame& frame) noexcept
        {
            if (!g_Active.load(std::memory_order_acquire))
                return true;
            ProducerRallyPolicy::CameraProjection cam;
            if (!ReadCamera(cam))
                return true;
            for (float& w : g_CharW)
                w = -1.0f;
            g_CharH = 0.0f;
            const float viewW = static_cast<float>(frame.viewW);
            const float viewH = static_cast<float>(frame.viewH);

            AcquireSRWLockShared(&g_Lock);
            bool ok = true;
            // Nearest rings first: smallest absolute view depth of the ring
            // centre (a big ring centred just behind the camera can still
            // show its arc, so it is not dropped, but it does not jump the
            // queue with a negative depth either).
            size_t itemCount = 0;
            for (size_t i = 0; i < g_RingCount; ++i)
            {
                const double x = g_Rings[i].centre[0], y = g_Rings[i].centre[1], z = g_Rings[i].centre[2];
                const double depth = cam.rot[2] * x + cam.rot[5] * y + cam.rot[8] * z + cam.trans[2];
                g_Items[itemCount].distance = static_cast<float>(std::fabs(depth));
                g_Items[itemCount++].id = i;
            }
            const size_t kept = RR::KeepNearest(g_Items, itemCount, RR::kMaxLabels);
            for (size_t k = 0; k < kept && ok; ++k)
            {
                const RangeLabelRing& ring = g_Rings[g_Items[k].id];
                const char* text = LabelText(ring.kind);
                size_t glyphs = std::strlen(text);
                if (glyphs == 0)
                    continue;
                if (glyphs > RR::kMaxLabelChars)
                    glyphs = RR::kMaxLabelChars;
                for (size_t g = 0; g < glyphs; ++g)
                    g_GlyphW[g] = GlyphWidth(frame, static_cast<unsigned char>(text[g]));
                for (size_t p = 0; p < RR::kLabelArcPoints; ++p)
                {
                    RR::ScreenPoint& sp = g_Screen[p];
                    sp.valid = ProducerRallyPolicy::ProjectToScreen(cam, ring.arc[p], sp.x, sp.y);
                }
                if (RR::PlaceArcText(g_Screen, RR::kLabelArcPoints, g_GlyphW, glyphs, viewW, viewH, g_Glyph) !=
                    RR::LabelResult::Placed)
                    continue;
                const float height = g_CharH > 0.0f ? g_CharH : 14.0f;
                for (size_t g = 0; g < glyphs && ok; ++g)
                {
                    if (text[g] == ' ')
                        continue;
                    char one[2] = {text[g], 0};
                    // Centred on the arc, then lowered so the letters sit
                    // just outside the ring on its near side.
                    const int x = static_cast<int>(g_Glyph[g].x - g_GlyphW[g] * 0.5f);
                    const int y = static_cast<int>(g_Glyph[g].y - height * 0.5f + height * 0.6f);
                    ok = HudGaugeOverlay::DrawPanelText(frame, 0, 0, -1, -1, 0, x, y, one, ring.argb, 0);
                }
            }
            ReleaseSRWLockShared(&g_Lock);
            return ok;
        }
    }

    void PublishRangeLabels(const RangeLabelRing* rings, size_t count)
    {
        if (count > RR::kMaxLabelRings)
            count = RR::kMaxLabelRings;
        if (count == 0)
        {
            if (g_Active.load(std::memory_order_acquire))
            {
                g_Active.store(false, std::memory_order_release);
                AcquireSRWLockExclusive(&g_Lock);
                g_RingCount = 0;
                ReleaseSRWLockExclusive(&g_Lock);
            }
            return;
        }
        if (!g_PainterSet && BindRows())
        {
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::RangeLabels, &PaintLabels);
            g_PainterSet = true;
        }
        if (!g_PainterSet)
            return;
        AcquireSRWLockExclusive(&g_Lock);
        for (size_t i = 0; i < count; ++i)
            g_Rings[i] = rings[i];
        g_RingCount = count;
        ReleaseSRWLockExclusive(&g_Lock);
        g_Active.store(true, std::memory_order_release);
    }
}
