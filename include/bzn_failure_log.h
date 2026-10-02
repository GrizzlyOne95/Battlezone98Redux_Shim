// Correlate Redux's terse mission-load failure with its last object message.
// Pure text parsing so the runtime diagnostic can be tested without the game.
#pragma once

#include <cstddef>
#include <limits>
#include <string_view>

namespace BZROpenShim::BznFailureLog
{
    struct Result
    {
        bool failed = false;
        bool hasObjectIndex = false;
        size_t objectIndex = 0;
    };

    inline Result Parse(std::string_view log)
    {
        constexpr std::string_view failure =
            "Quiting Game because failed to load game files";
        constexpr std::string_view missionLoad = "Sim Startup: Mission Load";
        constexpr std::string_view objectPrefix = "(obj #";

        const size_t failureAt = log.rfind(failure);
        if (failureAt == std::string_view::npos)
            return {};

        // A prior failed mission must not be attributed to a later normal
        // quit in the same process.
        const size_t latestLoad = log.rfind(missionLoad);
        if (latestLoad != std::string_view::npos && latestLoad > failureAt)
            return {};

        Result result{};
        result.failed = true;
        const size_t objectAt = log.rfind(objectPrefix, failureAt);
        if (objectAt == std::string_view::npos ||
            (latestLoad != std::string_view::npos && objectAt < latestLoad))
            return result;

        size_t cursor = objectAt + objectPrefix.size();
        size_t value = 0;
        bool sawDigit = false;
        while (cursor < failureAt && log[cursor] >= '0' && log[cursor] <= '9')
        {
            const size_t digit = static_cast<size_t>(log[cursor] - '0');
            if (value > (std::numeric_limits<size_t>::max() - digit) / 10)
                return result;
            value = value * 10 + digit;
            sawDigit = true;
            ++cursor;
        }
        if (!sawDigit || cursor >= failureAt || log[cursor] != ')')
            return result;

        result.hasObjectIndex = true;
        result.objectIndex = value;
        return result;
    }
}
