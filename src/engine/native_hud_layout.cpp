#include "native_hud_layout.h"

#include <cmath>
#include <cstring>
#include <limits>

namespace BZROpenShim::NativeHud
{
    namespace
    {
        bool Coordinate(int64_t value) noexcept
        {
            return value >= -kCoordinateLimit && value <= kCoordinateLimit;
        }

        bool MapAxis(int input, int from, int fromSize, int to, int toSize, int& output) noexcept
        {
            const double value = to + (static_cast<double>(input) - from) * toSize / fromSize;
            const double rounded = std::round(value);
            if (!std::isfinite(rounded) || rounded < -kCoordinateLimit || rounded > kCoordinateLimit)
                return false;
            output = static_cast<int>(rounded);
            return true;
        }
    }

    bool ParseMeter(const char* name, Meter& meter) noexcept
    {
        if (!name) return false;
        if (std::strcmp(name, "hull") == 0) { meter = Meter::Hull; return true; }
        if (std::strcmp(name, "ammo") == 0) { meter = Meter::Ammo; return true; }
        return false;
    }

    uint32_t Capability(Meter meter) noexcept
    {
        const auto index = static_cast<uint32_t>(meter);
        return index < static_cast<uint32_t>(Meter::Count) ? 1u << index : 0;
    }

    bool ValidRect(const Rect& rect) noexcept
    {
        return rect.w > 0 && rect.h > 0 && rect.w <= kDimensionLimit && rect.h <= kDimensionLimit &&
            Coordinate(rect.x) && Coordinate(rect.y) &&
            Coordinate(static_cast<int64_t>(rect.x) + rect.w) &&
            Coordinate(static_cast<int64_t>(rect.y) + rect.h);
    }

    bool InferFullRect(const Clip& clip, int relativeY, Rect& full) noexcept
    {
        if (relativeY > 0 || relativeY < -kDimensionLimit ||
            !Coordinate(clip.left) || !Coordinate(clip.top) ||
            !Coordinate(clip.right) || !Coordinate(clip.bottom)) return false;
        const int64_t width = static_cast<int64_t>(clip.right) - clip.left + 1;
        const int64_t top = static_cast<int64_t>(clip.top) + relativeY;
        const int64_t height = static_cast<int64_t>(clip.bottom) - top + 1;
        if (width <= 0 || width > kDimensionLimit || height <= 0 || height > kDimensionLimit ||
            static_cast<int64_t>(clip.top) > static_cast<int64_t>(clip.bottom) + 1 ||
            !Coordinate(top)) return false;
        const Rect candidate{clip.left, static_cast<int>(top), static_cast<int>(width), static_cast<int>(height)};
        if (!ValidRect(candidate)) return false;
        full = candidate;
        return true;
    }

    bool RenderPlan::MapPoint(const Point& input, Point& output) const noexcept
    {
        if (!ValidRect(source) || !ValidRect(target)) return false;
        Point candidate;
        if (!MapAxis(input.x, source.x, source.w, target.x, target.w, candidate.x) ||
            !MapAxis(input.y, source.y, source.h, target.y, target.h, candidate.y)) return false;
        output = candidate;
        return true;
    }

    bool RenderPlan::MapClip(const Clip& input, Clip& output) const noexcept
    {
        // Clip must belong to this full meter. Empty native clips remain empty,
        // including when rounding a nearly empty fill down to zero target rows.
        if (!ValidRect(source) || !ValidRect(target) || input.left < source.x ||
            input.right >= source.x + source.w || input.top < source.y ||
            input.bottom >= source.y + source.h || input.left > input.right ||
            static_cast<int64_t>(input.top) > static_cast<int64_t>(input.bottom) + 1) return false;
        Point first, past;
        if (!MapPoint({input.left, input.top}, first) ||
            !MapPoint({input.right + 1, input.bottom + 1}, past)) return false;
        output = {first.x, first.y, past.x - 1, past.y - 1};
        return true;
    }

    bool RenderPlan::MapSprite(const Sprite& input, Sprite& output) const noexcept
    {
        if (!ValidRect(source) || !ValidRect(target) || !std::isfinite(input.x) ||
            !std::isfinite(input.y) || !std::isfinite(input.w) || !std::isfinite(input.h) ||
            input.w <= 0 || input.h <= 0) return false;
        const double scaleX = static_cast<double>(target.w) / source.w;
        const double scaleY = static_cast<double>(target.h) / source.h;
        const Sprite candidate{target.x + (input.x - source.x) * scaleX,
            target.y + (input.y - source.y) * scaleY, input.w * scaleX, input.h * scaleY};
        if (!std::isfinite(candidate.x) || !std::isfinite(candidate.y) ||
            !std::isfinite(candidate.w) || !std::isfinite(candidate.h) ||
            std::abs(candidate.x) > kCoordinateLimit || std::abs(candidate.y) > kCoordinateLimit ||
            std::abs(candidate.x + candidate.w) > kCoordinateLimit ||
            std::abs(candidate.y + candidate.h) > kCoordinateLimit) return false;
        output = candidate;
        return true;
    }

    bool Layout::Supported(Meter meter) const noexcept
    {
        return (m_capabilities & Capability(meter)) != 0;
    }

    void Layout::SetAdapterCapabilities(uint32_t capabilities) noexcept
    {
        const uint32_t supported = capabilities & kAllCapabilities;
        if (supported == m_capabilities) return;
        m_capabilities = supported;
        ResetMission();
    }

    void Layout::ResetMission() noexcept
    {
        m_meters = {};
        ++m_epoch;
        m_sequence = 0;
    }

    Frame Layout::BeginFrame() noexcept
    {
        for (auto& meter : m_meters) meter.hasStock = false;
        return {m_epoch, ++m_sequence};
    }

    bool Layout::Observe(Meter meter, Frame frame, Rect stock, RenderPlan& plan) noexcept
    {
        if (!Supported(meter) || frame.epoch != m_epoch || frame.sequence != m_sequence ||
            frame.sequence == 0 || !ValidRect(stock)) return false;
        auto& state = m_meters[static_cast<std::size_t>(meter)];
        state.stock = stock;
        state.hasStock = true;
        plan = {stock, state.hasRequest ? state.requested : stock, state.visible};
        return true;
    }

    bool Layout::GetRect(Meter meter, bool stock, Rect& rect) const noexcept
    {
        if (!Supported(meter)) return false;
        const auto& state = m_meters[static_cast<std::size_t>(meter)];
        if (!state.hasStock) return false;
        rect = stock || !state.hasRequest ? state.stock : state.requested;
        return true;
    }

    bool Layout::SetRect(Meter meter, Rect rect) noexcept
    {
        if (!Supported(meter) || !ValidRect(rect)) return false;
        auto& state = m_meters[static_cast<std::size_t>(meter)];
        state.requested = rect;
        state.hasRequest = true;
        return true;
    }

    bool Layout::SetVisible(Meter meter, bool visible) noexcept
    {
        if (!Supported(meter)) return false;
        m_meters[static_cast<std::size_t>(meter)].visible = visible;
        return true;
    }

    bool Layout::Restore(Meter meter) noexcept
    {
        if (!Supported(meter)) return false;
        auto& state = m_meters[static_cast<std::size_t>(meter)];
        state.hasRequest = false;
        state.visible = true;
        return true;
    }

    bool Layout::RestoreAll() noexcept
    {
        if (!m_capabilities) return false;
        for (uint32_t index = 0; index < static_cast<uint32_t>(Meter::Count); ++index)
            Restore(static_cast<Meter>(index));
        return true;
    }
}
