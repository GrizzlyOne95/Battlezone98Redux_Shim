#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

namespace BZROpenShim::EnhancedLights
{
    inline constexpr std::size_t kEnhancedHighBudget = 24;
    inline constexpr std::size_t kEnhancedMediumBudget = 8;
    inline constexpr std::size_t kEnhancedLowBudget = 1;
    inline constexpr float kDefaultRetentionBonus = 0.05f;

    struct Vec3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Colour3
    {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };

    enum class LightType : std::uint8_t
    {
        Point = 0,
        Directional = 1,
        Spot = 2,
    };

    // Renderer-neutral snapshot of the Ogre values that CR's Enhanced shader
    // actually consumes. stableId should be derived from the Ogre light name;
    // opaque is carried through for the runtime bridge and is never ranked.
    struct Candidate
    {
        std::uint64_t stableId = 0;
        std::uintptr_t opaque = 0;
        LightType type = LightType::Point;
        Vec3 position = {};
        Vec3 direction = { 0.0f, 0.0f, -1.0f };
        Colour3 diffuse = {};
        Colour3 specular = {};
        float powerScale = 1.0f;
        float range = 0.0f;
        float attenuationConstant = 1.0f;
        float attenuationLinear = 0.0f;
        float attenuationQuadratic = 0.0f;
        float spotInnerCos = 1.0f;
        float spotOuterCos = 0.0f;
        float spotFalloff = 1.0f;
    };

    struct RankConfig
    {
        std::size_t budget = kEnhancedHighBudget;
        float retentionBonus = kDefaultRetentionBonus;
    };

    struct RankedCandidate
    {
        Candidate light = {};
        float rawInfluence = 0.0f;
        float effectiveInfluence = 0.0f;
        float surfaceDistance = 0.0f;
        bool retained = false;
        std::size_t originalOrder = 0;
    };

    struct SelectionStats
    {
        std::size_t candidates = 0;
        std::size_t selected = 0;
        std::size_t replacements = 0;
        float cutoffInfluence = 0.0f;
    };

    std::uint64_t StableLightId(std::string_view name);

    // Returns zero for every stock/Classic scheme. This is the shared guard
    // used by the runtime hook and isolation tests.
    std::size_t BudgetForEnhancedScheme(std::string_view scheme);

    // Matches the current CR direct-light model: derived diffuse/specular
    // intensity, Ogre constant/linear/quadratic attenuation, object-bound
    // distance, and the shader's smooth spotlight cone.
    float EstimateInfluence(const Candidate& light,
                            const Vec3& objectCenter,
                            float objectRadius,
                            float* outSurfaceDistance = nullptr);

    // Directional lights retain their producer order so the primary sun stays
    // at slot zero. Local lights are deterministically sorted by estimated
    // contribution; a small previous-selection bonus supplies cutoff
    // hysteresis without preventing a meaningfully stronger light replacing a
    // weak one.
    std::vector<RankedCandidate> RankCandidates(
        std::span<const Candidate> candidates,
        const Vec3& objectCenter,
        float objectRadius,
        std::span<const std::uint64_t> previouslySelected,
        const RankConfig& config = {});

    SelectionStats MeasureSelection(
        std::span<const RankedCandidate> ranked,
        std::span<const std::uint64_t> previouslySelected,
        std::size_t budget);
}
