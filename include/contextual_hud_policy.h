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
        // pinned: bit per Group; a set bit counts as interaction this sample.
        void Observe(uint64_t identity, const std::array<uint64_t, kGroups>& values, uint64_t now, size_t count = kGroups,
            uint32_t pinned = 0)
        {
            if (!identity) { Reset(); return; }
            if (identity != owner) { Reset(); owner = identity; }
            for (size_t i = 0; i < std::min(count, kGroups); ++i) groups[i].Observe(values[i], now, (pinned >> i) & 1u);
        }
    };
    constexpr uint32_t Bit(Group group) { return 1u << static_cast<size_t>(group); }
    // Radar pin. Classify by the contact's perceived team only, so a
    // disguised/hidden team is never revealed by the HUD staying solid.
    // enemyTeams: bit t set when the native relation calls team t an enemy.
    inline bool EnemyContact(int perceivedTeam, uint32_t enemyTeams)
    {
        return perceivedTeam > 0 && perceivedTeam < 16 && ((enemyTeams >> perceivedTeam) & 1u) != 0;
    }
    // The command panel shows a build list only while every selected unit
    // is a producer (Recycler/Factory/Armory/Constructor). isProducer(i)
    // classifies selection slot i; doubt answers false (not pinned).
    constexpr int kMaxSelected = 91;
    template<class IsProducer>
    bool ProductionMenuOpen(int selected, IsProducer&& isProducer)
    {
        if (selected <= 0 || selected > kMaxSelected) return false;
        for (int i = 0; i < selected; ++i)
            if (!isProducer(i)) return false;
        return true;
    }
    // Producer identity by exact primary vtable. Zero entries never match.
    inline bool IsProducerVtable(uintptr_t vtable, const std::array<uintptr_t, 4>& producers)
    {
        if (!vtable) return false;
        for (const auto candidate : producers)
            if (candidate && candidate == vtable) return true;
        return false;
    }
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
