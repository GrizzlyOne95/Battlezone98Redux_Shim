#pragma once

#include <cmath>
#include <cstdint>
#include <unordered_map>

namespace BZROpenShim::UnitDamage
{
    // A pool address alone is not identity: the engine reuses it after death.
    // The full handle includes the allocation generation. Lua APIs and damage
    // dispatch run on the simulation thread; this table never calls Lua.
    class Policy
    {
        struct Entry { uint32_t handle; float multiplier; };
        std::unordered_map<uintptr_t, Entry> entries;
    public:
        bool Set(uintptr_t object, uint32_t handle, float multiplier)
        {
            if (!object || !handle || !std::isfinite(multiplier) ||
                multiplier < 0.0f || multiplier > 1.0f) return false;
            if (multiplier == 1.0f) { entries.erase(object); return true; }
            if (entries.size() >= 4096 && !entries.contains(object)) return false;
            entries.insert_or_assign(object, Entry{handle, multiplier});
            return true;
        }
        float Get(uintptr_t object, uint32_t handle) const noexcept
        {
            const auto it = entries.find(object);
            return it != entries.end() && it->second.handle == handle
                ? it->second.multiplier : 1.0f;
        }
        float Apply(uintptr_t object, uint32_t handle, float damage) const noexcept
        {
            if (!std::isfinite(damage) || damage <= 0.0f) return damage;
            return damage * Get(object, handle);
        }
        void Clear(uint32_t handle)
        {
            for (auto it = entries.begin(); it != entries.end();)
                if (it->second.handle == handle) it = entries.erase(it);
                else ++it;
        }
        void Reset() noexcept { entries.clear(); }
        bool Empty() const noexcept { return entries.empty(); }
    };
}
