// career_kill_class.h
// BZR Open Shim - victim categories for the Career "kills by type" record.
//
// Pure policy, no engine access: maps a victim's engine classLabel (the
// gameplay category string at GameObjectClass+0x18) and, for the one label
// that is too coarse ("wingman"), its [GameObjectClass] unitName to one of ten
// buckets. The persisted key is profile.<key>.career.killsByClass.<KillClassKey>.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cctype>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <string_view>

namespace BZROpenShim::CareerKillClass
{
    enum class Category : unsigned char
    {
        Pilot,
        Tank,
        Fighter,
        Scout,
        Bomber,
        Turret,
        Artillery,
        Support,
        Building,
        Other,
    };

    inline constexpr size_t kCategoryCount = 10;

    inline const char* KillClassKey(Category category) noexcept
    {
        switch (category)
        {
        case Category::Pilot:     return "pilot";
        case Category::Tank:      return "tank";
        case Category::Fighter:   return "fighter";
        case Category::Scout:     return "scout";
        case Category::Bomber:    return "bomber";
        case Category::Turret:    return "turret";
        case Category::Artillery: return "artillery";
        case Category::Support:   return "support";
        case Category::Building:  return "building";
        case Category::Other:     break;
        }
        return "other";
    }

    namespace detail
    {
        inline std::string Lower(std::string_view text)
        {
            std::string out(text);
            for (char& c : out)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            return out;
        }

        inline bool OneOf(const std::string& value, std::initializer_list<const char*> names)
        {
            for (const char* name : names)
                if (value == name)
                    return true;
            return false;
        }
    }

    // Case-insensitive. Unknown or empty labels are Other.
    inline Category Categorize(std::string_view classLabel, std::string_view unitName)
    {
        const std::string label = detail::Lower(classLabel);
        if (label == "person")
            return Category::Pilot;
        if (label == "wingman")
        {
            const std::string name = detail::Lower(unitName);
            if (name.find("bomber") != std::string::npos) return Category::Bomber;
            if (name.find("fighter") != std::string::npos) return Category::Fighter;
            if (name.find("scout") != std::string::npos) return Category::Scout;
            return Category::Tank;
        }
        if (detail::OneOf(label, { "walker", "sav" }))
            return Category::Tank;
        if (detail::OneOf(label, { "turrettank", "turret" }))
            return Category::Turret;
        if (label == "howitzer")
            return Category::Artillery;
        if (detail::OneOf(label, { "apc", "constructionrig", "scavenger", "tug", "minelayer",
                                   "recycler", "factory", "armory" }))
            return Category::Support;
        if (detail::OneOf(label, { "i76building", "barracks", "commtower", "powerplant",
                                   "repairdepot", "scrapsilo", "supplydepot", "portal" }))
            return Category::Building;
        return Category::Other;
    }
}
