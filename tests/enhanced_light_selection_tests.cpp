#include "enhanced_light_selection.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <span>
#include <unordered_set>
#include <vector>

namespace
{
    using namespace BZROpenShim::EnhancedLights;

    [[noreturn]] void Fail(const char* message)
    {
        std::fprintf(stderr, "enhanced_light_selection_tests: %s\n", message);
        std::exit(1);
    }

    void Require(bool condition, const char* message)
    {
        if (!condition)
            Fail(message);
    }

    Candidate MakePoint(std::uint64_t id, float x, float intensity,
                        float range = 200.0f, float quadratic = 0.01f)
    {
        Candidate light = {};
        light.stableId = id;
        light.opaque = static_cast<std::uintptr_t>(id);
        light.type = LightType::Point;
        light.position = { x, 0.0f, 0.0f };
        light.diffuse = { intensity, intensity, intensity };
        light.specular = light.diffuse;
        light.range = range;
        light.attenuationConstant = 1.0f;
        light.attenuationQuadratic = quadratic;
        return light;
    }

    Candidate MakeSun()
    {
        Candidate light = {};
        light.stableId = 1;
        light.opaque = 1;
        light.type = LightType::Directional;
        light.diffuse = { 2.0f, 2.0f, 2.0f };
        return light;
    }

    std::vector<std::uint64_t> SelectedIds(
        std::span<const RankedCandidate> ranked, std::size_t budget)
    {
        std::vector<std::uint64_t> ids;
        const std::size_t selected = std::min(budget, ranked.size());
        ids.reserve(selected);
        for (std::size_t i = 0; i < selected; ++i)
            ids.push_back(ranked[i].light.stableId);
        return ids;
    }

    std::vector<std::uint64_t> StockDistanceSelection(
        std::span<const Candidate> candidates, const Vec3& center, std::size_t budget)
    {
        std::vector<const Candidate*> sorted;
        sorted.reserve(candidates.size());
        for (const Candidate& light : candidates)
            sorted.push_back(&light);
        std::stable_sort(sorted.begin(), sorted.end(),
            [&center](const Candidate* a, const Candidate* b)
            {
                if (a->type == LightType::Directional || b->type == LightType::Directional)
                    return a->type == LightType::Directional && b->type != LightType::Directional;
                const auto distanceSq = [&center](const Candidate* light)
                {
                    const float x = light->position.x - center.x;
                    const float y = light->position.y - center.y;
                    const float z = light->position.z - center.z;
                    return x * x + y * y + z * z;
                };
                return distanceSq(a) < distanceSq(b);
            });

        std::vector<std::uint64_t> ids;
        for (std::size_t i = 0; i < std::min(budget, sorted.size()); ++i)
            ids.push_back(sorted[i]->stableId);
        return ids;
    }

    std::size_t Churn(std::span<const std::uint64_t> previous,
                      std::span<const std::uint64_t> current)
    {
        std::unordered_set<std::uint64_t> prior(previous.begin(), previous.end());
        std::size_t replacements = 0;
        for (const std::uint64_t id : current)
        {
            if (!prior.contains(id))
                ++replacements;
        }
        return replacements;
    }

    void TestStableHash()
    {
        Require(StableLightId("headlight_01") == StableLightId("headlight_01"),
            "stable name hash changed between identical inputs");
        Require(StableLightId("headlight_01") != StableLightId("headlight_02"),
            "distinct light names collided in basic test");
    }

    void TestSchemeIsolation()
    {
        Require(BudgetForEnhancedScheme("en-high-pssm") == 24,
            "Enhanced High PSSM budget was not 24");
        Require(BudgetForEnhancedScheme("en-medium") == 8,
            "Enhanced Medium budget was not 8");
        Require(BudgetForEnhancedScheme("en-low-noshadow") == 1,
            "Enhanced Low budget was not 1");
        Require(BudgetForEnhancedScheme("high-pssm") == 0,
            "Classic High crossed the Enhanced scheme guard");
        Require(BudgetForEnhancedScheme("medium") == 0,
            "Classic Medium crossed the Enhanced scheme guard");
        Require(BudgetForEnhancedScheme("") == 0,
            "empty/stock scheme crossed the Enhanced scheme guard");
    }

    void TestUnderBudgetAndContributionRanking()
    {
        const Vec3 center = {};
        std::vector<Candidate> lights = {
            MakeSun(),
            MakePoint(2, 5.0f, 0.5f),
            MakePoint(3, 25.0f, 12.0f),
            MakePoint(4, 12.0f, 1.0f),
        };
        const auto ranked = RankCandidates(lights, center, 1.0f, {}, { 24, 0.05f });
        Require(ranked.size() == lights.size(), "under-budget candidates were dropped");
        Require(ranked[0].light.type == LightType::Directional, "sun did not remain first");
        Require(ranked[1].light.stableId == 3,
            "distant strong light did not beat weaker attenuation result");
    }

    void TestSpotConeAndFiniteAttenuationCases()
    {
        Candidate spot = MakePoint(10, 10.0f, 5.0f);
        spot.type = LightType::Spot;
        spot.direction = { 1.0f, 0.0f, 0.0f };
        spot.spotInnerCos = 0.95f;
        spot.spotOuterCos = 0.80f;
        spot.spotFalloff = 2.0f;
        spot.attenuationConstant = 0.0f;
        spot.attenuationQuadratic = 0.0f;

        const float behind = EstimateInfluence(spot, {}, 0.0f);
        spot.direction = { -1.0f, 0.0f, 0.0f };
        const float forward = EstimateInfluence(spot, {}, 0.0f);
        Require(std::isfinite(behind) && std::isfinite(forward),
            "zero attenuation denominator produced a non-finite influence");
        Require(forward > behind * 1000.0f, "spotlight cone did not reject rear influence");
    }

    void TestHysteresisAndMajorReplacement()
    {
        const Vec3 center = {};
        std::vector<Candidate> frame = {
            MakeSun(),
            MakePoint(20, 1.0f, 2.0f, 100.0f, 0.0f),
            MakePoint(21, 1.0f, 2.04f, 100.0f, 0.0f),
        };
        const std::vector<std::uint64_t> previous = { 1, 20 };
        auto ranked = RankCandidates(frame, center, 0.0f, previous, { 2, 0.05f });
        auto selected = SelectedIds(ranked, 2);
        Require(selected[1] == 20,
            "near-equal cutoff candidate defeated the configured retention bonus");

        frame[2].diffuse = { 3.0f, 3.0f, 3.0f };
        frame[2].specular = frame[2].diffuse;
        ranked = RankCandidates(frame, center, 0.0f, previous, { 2, 0.05f });
        selected = SelectedIds(ranked, 2);
        Require(selected[1] == 21, "meaningfully stronger explosion failed to replace retained light");

        frame.erase(frame.begin() + 1);
        ranked = RankCandidates(frame, center, 0.0f, previous, { 2, 0.05f });
        selected = SelectedIds(ranked, 2);
        Require(std::find(selected.begin(), selected.end(), 20) == selected.end(),
            "removed light lingered in selection history");
    }

    void TestDeterminismAcrossContainerOrder()
    {
        const Vec3 center = {};
        std::vector<Candidate> a = {
            MakeSun(), MakePoint(30, 10.0f, 2.0f), MakePoint(31, -10.0f, 2.0f),
            MakePoint(32, 10.0f, 2.0f), MakePoint(33, -10.0f, 2.0f),
        };
        std::vector<Candidate> b = a;
        std::reverse(b.begin() + 1, b.end());
        const auto rankedA = RankCandidates(a, center, 0.0f, {}, { 5, 0.0f });
        const auto rankedB = RankCandidates(b, center, 0.0f, {}, { 5, 0.0f });
        Require(SelectedIds(rankedA, 5) == SelectedIds(rankedB, 5),
            "local-light order depends on incidental candidate container order");
    }

    void TestCombatChurn()
    {
        const Vec3 center = {};
        std::vector<Candidate> base;
        base.push_back(MakeSun());
        for (std::uint64_t i = 0; i < 30; ++i)
        {
            const float distance = 18.0f + static_cast<float>(i % 12) * 0.025f;
            // Twenty-three strong locals fill the Enhanced budget after the sun.
            // Seven weak tail lights remain plausible by distance but irrelevant
            // by actual contribution.
            const float intensity = i < 23 ? 4.0f + static_cast<float>(i) * 0.03f : 0.08f;
            base.push_back(MakePoint(100 + i, distance, intensity, 80.0f, 0.003f));
        }

        std::mt19937 random(0xB298u);
        std::uniform_real_distribution<float> noise(-0.12f, 0.12f);
        std::vector<std::uint64_t> stock8Previous;
        std::vector<std::uint64_t> stock24Previous;
        std::vector<std::uint64_t> v2Previous;
        std::size_t stock8Churn = 0;
        std::size_t stock24Churn = 0;
        std::size_t v2Churn = 0;

        for (int frameIndex = 0; frameIndex < 180; ++frameIndex)
        {
            std::vector<Candidate> frame = base;
            for (std::size_t i = 1; i < frame.size(); ++i)
                frame[i].position.x += noise(random);
            std::shuffle(frame.begin() + 1, frame.end(), random);

            const auto stock8 = StockDistanceSelection(frame, center, 8);
            const auto stock24 = StockDistanceSelection(frame, center, 24);
            const auto ranked = RankCandidates(frame, center, 2.0f, v2Previous, { 24, 0.05f });
            const auto v2 = SelectedIds(ranked, 24);
            if (frameIndex > 0)
            {
                stock8Churn += Churn(stock8Previous, stock8);
                stock24Churn += Churn(stock24Previous, stock24);
                v2Churn += Churn(v2Previous, v2);
            }
            stock8Previous = stock8;
            stock24Previous = stock24;
            v2Previous = v2;
        }

        Require(stock8Churn > 100, "synthetic 8-light reference did not exercise churn");
        Require(stock24Churn > 100, "actual High 24/25 cutoff did not exercise churn");
        Require(v2Churn * 10 < stock24Churn,
            "24-light relevance selection did not materially reduce High cutoff churn");
        std::printf("combat_churn stock8=%zu stock24=%zu enhanced24=%zu frames=180\n",
            stock8Churn, stock24Churn, v2Churn);
    }
}

int main()
{
    TestStableHash();
    TestSchemeIsolation();
    TestUnderBudgetAndContributionRanking();
    TestSpotConeAndFiniteAttenuationCases();
    TestHysteresisAndMajorReplacement();
    TestDeterminismAcrossContainerOrder();
    TestCombatChurn();
    std::puts("enhanced_light_selection_tests: PASS");
    return 0;
}
