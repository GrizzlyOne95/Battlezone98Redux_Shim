#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstddef>

namespace BZROpenShim::ContextualHud
{
    enum class Group : size_t { Weapons, Scrap, Pilots, Commands, Hull, Ammo, Radar, Count };
    constexpr size_t kGroups = static_cast<size_t>(Group::Count);
    struct GroupSettings { bool enabled = false; int idlePercent = 25; int delayMs = 2500; int fadeMs = 500; };
    struct Settings
    {
        std::array<GroupSettings, kGroups> groups{};
        bool radarCompassAlwaysVisible = false;
        bool Active() const { for (const auto& g : groups) if (g.enabled) return true; return false; }
    };
    struct Activity
    {
        bool observed = false;
        uint64_t value = 0, changedAt = 0;
        void Observe(uint64_t next, uint64_t now, bool interacting = false)
        {
            if (interacting || !observed || value != next || now < changedAt) changedAt = now;
            observed = true; value = next;
        }
        float Opacity(const GroupSettings& settings, uint64_t now) const
        {
            if (!settings.enabled || !observed || now < changedAt) return 1;
            const auto elapsed = now - changedAt;
            const auto hold = static_cast<uint64_t>(std::clamp(settings.delayMs, 0, 30000));
            if (elapsed <= hold) return 1;
            const float idle = std::clamp(settings.idlePercent, 0, 100) * 0.01f;
            if (settings.fadeMs <= 0) return idle;
            const float t = std::min(1.0f, static_cast<float>(elapsed - hold) / std::clamp(settings.fadeMs, 1, 5000));
            const float eased = t * t * (3 - 2 * t);
            return 1 - (1 - idle) * eased;
        }
    };
    struct State
    {
        uint64_t owner = 0;
        std::array<Activity, kGroups> groups{};
        void Reset() { *this = {}; }
        void Observe(uint64_t identity, const std::array<uint64_t, kGroups>& values, uint64_t now, size_t count = kGroups)
        {
            if (!identity) { Reset(); return; }
            if (identity != owner) { Reset(); owner = identity; }
            for (size_t i = 0; i < std::min(count, kGroups); ++i) groups[i].Observe(values[i], now);
        }
    };
    struct RadarContacts
    {
        static constexpr size_t Capacity = 256;
        std::array<uint32_t,Capacity> previous{}, current{};
        size_t previousCount = 0, count = 0;
        bool added = false, invalid = false;
        void Begin() { count = 0; added = invalid = false; }
        void Observe(uint32_t handle)
        {
            if (!handle) { invalid = true; return; }
            if (std::find(current.begin(),current.begin()+count,handle) != current.begin()+count) return;
            if (count == Capacity) { invalid = true; return; }
            current[count++] = handle;
            if (std::find(previous.begin(),previous.begin()+previousCount,handle) == previous.begin()+previousCount)
                added = true;
        }
        void Commit() { previous = current; previousCount = count; }
    };
    inline bool HullWarning(float health, float maximum)
    {
        // Invalid meters must remain visible, too.
        return !std::isfinite(health) || !std::isfinite(maximum) || maximum <= 0 ||
            health < 0 || health / maximum < 0.25f;
    }
    inline bool AmmoWarning(uint32_t ammo, uint32_t available, const std::array<uint32_t, 5>& costs)
    {
        uint32_t insufficient = 0;
        for (size_t i = 0; i < costs.size(); ++i)
            if (ammo < costs[i]) insufficient |= 1u << i;
        // Same all-available-weapons-unaffordable condition as native status.
        return insufficient != 0 && insufficient == available;
    }
    inline uint32_t ScaleAlpha(uint32_t color, float opacity)
    {
        if (!std::isfinite(opacity) || opacity >= 1) return color;
        const auto alpha = static_cast<uint32_t>(std::lround((color >> 24) * std::max(0.0f, opacity)));
        return (color & 0xFFFFFFu) | (alpha << 24);
    }
}
