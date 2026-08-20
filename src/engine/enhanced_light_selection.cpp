#include "enhanced_light_selection.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_set>

namespace BZROpenShim::EnhancedLights
{
    namespace
    {
        constexpr float kEpsilon = 1.0e-6f;

        float Saturate(float value)
        {
            return std::clamp(value, 0.0f, 1.0f);
        }

        float Luminance(const Colour3& colour)
        {
            return std::max(0.0f,
                colour.r * 0.2126f + colour.g * 0.7152f + colour.b * 0.0722f);
        }

        Vec3 Subtract(const Vec3& a, const Vec3& b)
        {
            return { a.x - b.x, a.y - b.y, a.z - b.z };
        }

        float Dot(const Vec3& a, const Vec3& b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        float Length(const Vec3& value)
        {
            return std::sqrt(std::max(Dot(value, value), 0.0f));
        }

        Vec3 Normalize(const Vec3& value)
        {
            const float length = Length(value);
            if (length <= kEpsilon)
                return {};
            const float inverse = 1.0f / length;
            return { value.x * inverse, value.y * inverse, value.z * inverse };
        }
    }

    std::uint64_t StableLightId(std::string_view name)
    {
        constexpr std::uint64_t kOffsetBasis = 14695981039346656037ull;
        constexpr std::uint64_t kPrime = 1099511628211ull;
        std::uint64_t hash = kOffsetBasis;
        for (const unsigned char byte : name)
        {
            hash ^= byte;
            hash *= kPrime;
        }
        return hash;
    }

    std::size_t BudgetForEnhancedScheme(std::string_view scheme)
    {
        if (!scheme.starts_with("en-"))
            return 0;
        if (scheme.starts_with("en-high"))
            return kEnhancedHighBudget;
        if (scheme.starts_with("en-medium"))
            return kEnhancedMediumBudget;
        return kEnhancedLowBudget;
    }

    float EstimateInfluence(const Candidate& light,
                            const Vec3& objectCenter,
                            float objectRadius,
                            float* outSurfaceDistance)
    {
        if (light.type == LightType::Directional)
        {
            if (outSurfaceDistance)
                *outSurfaceDistance = 0.0f;
            return std::numeric_limits<float>::infinity();
        }

        const Vec3 centerToLight = Subtract(light.position, objectCenter);
        const float centerDistance = Length(centerToLight);
        const float surfaceDistance = std::max(centerDistance - std::max(objectRadius, 0.0f), 0.0f);
        if (outSurfaceDistance)
            *outSurfaceDistance = surfaceDistance;

        if (light.range > 0.0f && surfaceDistance > light.range)
            return 0.0f;

        const float denominator = light.attenuationConstant
            + surfaceDistance * (light.attenuationLinear
                + surfaceDistance * light.attenuationQuadratic);
        const float distanceAttenuation = Saturate(1.0f / std::max(denominator, kEpsilon));

        float spotAttenuation = 1.0f;
        if (light.type == LightType::Spot)
        {
            const Vec3 pixelToLight = Normalize(centerToLight);
            const Vec3 oppositeDirection = Normalize(
                { -light.direction.x, -light.direction.y, -light.direction.z });
            const float cone = Dot(pixelToLight, oppositeDirection);
            const float coneRange = std::max(light.spotInnerCos - light.spotOuterCos, kEpsilon);
            const float spotMask = Saturate((cone - light.spotOuterCos) / coneRange);
            const float power = std::max(light.spotFalloff, 1.0f);
            spotAttenuation = std::pow(std::max(spotMask, 1.0e-4f), power);
        }

        const float authoredIntensity = std::max(
            Luminance(light.diffuse), Luminance(light.specular));
        const float scaledIntensity = authoredIntensity * std::max(light.powerScale, 0.0f);
        const float influence = scaledIntensity * distanceAttenuation * spotAttenuation;
        return std::isfinite(influence) ? std::max(influence, 0.0f) : 0.0f;
    }

    std::vector<RankedCandidate> RankCandidates(
        std::span<const Candidate> candidates,
        const Vec3& objectCenter,
        float objectRadius,
        std::span<const std::uint64_t> previouslySelected,
        const RankConfig& config)
    {
        std::unordered_set<std::uint64_t> previousSet;
        previousSet.reserve(previouslySelected.size());
        previousSet.insert(previouslySelected.begin(), previouslySelected.end());

        std::vector<RankedCandidate> ranked;
        ranked.reserve(candidates.size());
        for (std::size_t index = 0; index < candidates.size(); ++index)
        {
            RankedCandidate entry = {};
            entry.light = candidates[index];
            entry.originalOrder = index;
            entry.rawInfluence = EstimateInfluence(
                entry.light, objectCenter, objectRadius, &entry.surfaceDistance);
            entry.retained = previousSet.contains(entry.light.stableId);
            entry.effectiveInfluence = entry.rawInfluence;
            if (entry.retained && std::isfinite(entry.effectiveInfluence))
            {
                entry.effectiveInfluence *= 1.0f + std::max(config.retentionBonus, 0.0f);
            }
            ranked.push_back(entry);
        }

        // Stable sort intentionally preserves the producer order of directional
        // lights. Redux/CR expect the PSSM sun to remain the first light.
        std::stable_sort(ranked.begin(), ranked.end(),
            [](const RankedCandidate& a, const RankedCandidate& b)
            {
                const bool aDirectional = a.light.type == LightType::Directional;
                const bool bDirectional = b.light.type == LightType::Directional;
                if (aDirectional != bDirectional)
                    return aDirectional;
                if (aDirectional)
                    return false;
                if (a.effectiveInfluence != b.effectiveInfluence)
                    return a.effectiveInfluence > b.effectiveInfluence;
                if (a.rawInfluence != b.rawInfluence)
                    return a.rawInfluence > b.rawInfluence;
                if (a.light.stableId != b.light.stableId)
                    return a.light.stableId < b.light.stableId;
                return a.originalOrder < b.originalOrder;
            });

        return ranked;
    }

    SelectionStats MeasureSelection(
        std::span<const RankedCandidate> ranked,
        std::span<const std::uint64_t> previouslySelected,
        std::size_t budget)
    {
        SelectionStats stats = {};
        stats.candidates = ranked.size();
        stats.selected = std::min(budget, ranked.size());
        if (stats.selected > 0)
            stats.cutoffInfluence = ranked[stats.selected - 1].rawInfluence;

        std::unordered_set<std::uint64_t> previousSet;
        previousSet.reserve(previouslySelected.size());
        previousSet.insert(previouslySelected.begin(), previouslySelected.end());
        for (std::size_t i = 0; i < stats.selected; ++i)
        {
            if (!previousSet.contains(ranked[i].light.stableId))
                ++stats.replacements;
        }
        return stats;
    }
}
