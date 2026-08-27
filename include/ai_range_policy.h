#pragma once

#include <algorithm>
#include <cmath>

namespace BZROpenShim
{
    namespace AiRangePolicy
    {
        struct Inputs
        {
            float closeRange = 0.0f;
            float range = 0.0f;
            float time = 0.0f;
            bool hasOuterRangeFloor = false;
            float outerRangeFloor = 0.0f;
            bool hasCloseRangeFloor = false;
            float closeRangeFloor = 0.0f;
        };

        struct Result
        {
            float closeRange = 0.0f;
            float range = 0.0f;
            float time = 0.0f;
            float appliedOuterRangeFloor = 0.0f;
            float appliedCloseRangeFloor = 0.0f;
            bool rangeChanged = false;
            bool closeRangeChanged = false;
            bool timeChanged = false;
        };

        inline bool AccumulatePositiveFloor(bool& hasFloor,
                                            float& floor,
                                            float candidate)
        {
            if (!std::isfinite(candidate) || candidate <= 0.0f)
                return false;

            if (!hasFloor || candidate > floor)
                floor = candidate;
            hasFloor = true;
            return true;
        }

        inline Result Apply(const Inputs& inputs)
        {
            Result result = {};
            result.closeRange = inputs.closeRange;
            result.range = inputs.range;
            result.time = inputs.time;

            const bool haveOuterFloor =
                inputs.hasOuterRangeFloor &&
                std::isfinite(inputs.outerRangeFloor) &&
                inputs.outerRangeFloor > 0.0f;
            if (haveOuterFloor)
            {
                result.appliedOuterRangeFloor = inputs.outerRangeFloor;
                if (std::isfinite(result.range) && result.range < inputs.outerRangeFloor)
                {
                    result.range = inputs.outerRangeFloor;
                    result.rangeChanged = true;
                }
            }

            bool haveUsableCloseFloor = false;
            if (inputs.hasCloseRangeFloor &&
                std::isfinite(inputs.closeRangeFloor) &&
                inputs.closeRangeFloor > 0.0f &&
                std::isfinite(result.range) &&
                result.range > 0.0f)
            {
                // UnitTask requires a non-empty firing window. Preserve the
                // stock outer weapon range and cap the authored too-close
                // threshold just inside it.
                const float maximumCloseFloor = result.range * 0.9f;
                if (std::isfinite(maximumCloseFloor) && maximumCloseFloor > 0.0f)
                {
                    result.appliedCloseRangeFloor =
                        (std::min)(inputs.closeRangeFloor, maximumCloseFloor);
                    haveUsableCloseFloor = true;
                    if (std::isfinite(result.closeRange) &&
                        result.closeRange < result.appliedCloseRangeFloor)
                    {
                        result.closeRange = result.appliedCloseRangeFloor;
                        result.closeRangeChanged = true;
                    }
                }
            }

            if ((haveOuterFloor || haveUsableCloseFloor) &&
                (!std::isfinite(result.time) || result.time <= 0.0f))
            {
                result.time = 1.0f;
                result.timeChanged = true;
            }

            return result;
        }
    }
}
