// Copyright (C) 2026 GrizzlyOne95
// Engine-independent screen-space intent and render adapter for native meters.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace BZROpenShim::NativeHud
{
    enum class Meter : uint32_t { Hull = 0, Ammo = 1, Count = 2 };
    constexpr uint32_t kHullCapability = 1u;
    constexpr uint32_t kAmmoCapability = 2u;
    constexpr uint32_t kAllCapabilities = kHullCapability | kAmmoCapability;
    constexpr int kCoordinateLimit = 65535;
    constexpr int kDimensionLimit = 16384;

    // Physical viewport pixels; width/height are counts, not inclusive edges.
    struct Rect { int x = 0, y = 0, w = 0, h = 0; };
    // The native pane uses inclusive edges. top == bottom + 1 is an empty bar.
    struct Clip { int left = 0, top = 0, right = -1, bottom = -1; };
    struct Point { int x = 0, y = 0; };
    struct Sprite { double x = 0, y = 0, w = 0, h = 0; };

    bool ParseMeter(const char* name, Meter& meter) noexcept;
    bool ValidRect(const Rect& rect) noexcept;
    uint32_t Capability(Meter meter) noexcept;

    // Recover the full vertical bar before native fill clipping: its submit Y
    // is the negative number of missing rows relative to the advanced pane.
    bool InferFullRect(const Clip& clip, int relativeY, Rect& full) noexcept;

    struct RenderPlan
    {
        Rect source;
        Rect target;
        bool visible = true;

        // Transform already resolved screen-space positions, never design
        // coordinates or atlas UVs. Clip and sprite use the same full-bar map.
        bool MapClip(const Clip& input, Clip& output) const noexcept;
        bool MapPoint(const Point& input, Point& output) const noexcept;
        bool MapSprite(const Sprite& input, Sprite& output) const noexcept;
    };

    struct Frame
    {
        uint64_t epoch = 0;
        uint64_t sequence = 0;
    };

    // No engine pointers, allocation, hooking, or Windows dependency. The
    // runtime serializes access; a qualified adapter supplies each stock frame.
    class Layout
    {
    public:
        uint32_t Capabilities() const noexcept { return m_capabilities; }
        // INTERNAL adapter boundary, not a public SDK permission switch. No
        // production caller enables it until native byte/ABI qualification.
        void SetAdapterCapabilities(uint32_t capabilities) noexcept;
        void ResetMission() noexcept;
        Frame BeginFrame() noexcept;
        bool Observe(Meter meter, Frame frame, Rect stock, RenderPlan& plan) noexcept;
        bool GetRect(Meter meter, bool stock, Rect& rect) const noexcept;
        bool SetRect(Meter meter, Rect rect) noexcept;
        bool SetVisible(Meter meter, bool visible) noexcept;
        bool Restore(Meter meter) noexcept;
        bool RestoreAll() noexcept;

    private:
        struct State
        {
            Rect stock;
            Rect requested;
            bool hasStock = false;
            bool hasRequest = false;
            bool visible = true;
        };
        bool Supported(Meter meter) const noexcept;
        std::array<State, static_cast<std::size_t>(Meter::Count)> m_meters{};
        uint32_t m_capabilities = 0;
        uint64_t m_epoch = 1;
        uint64_t m_sequence = 0;
    };
}
