#include "enhanced_light_selection.h"

#include <chrono>
#include <cstdio>
#include <random>
#include <vector>

int main()
{
    using namespace BZROpenShim::EnhancedLights;
    constexpr int iterations = 20000;
    const std::size_t counts[] = { 8, 16, 32, 64, 128 };
    const std::size_t budgets[] = { 8, 16, 24, 32 };
    std::mt19937 random(0xB298u);
    std::uniform_real_distribution<float> position(-100.0f, 100.0f);
    std::uniform_real_distribution<float> intensity(0.05f, 8.0f);

    std::puts("candidates,budget,iterations,total_ms,us_per_selection");
    for (const std::size_t count : counts)
    {
        std::vector<Candidate> lights;
        lights.reserve(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            Candidate light = {};
            light.stableId = 1000 + i;
            light.opaque = 1000 + i;
            light.type = i == 0 ? LightType::Directional
                : (i % 5 == 0 ? LightType::Spot : LightType::Point);
            light.position = { position(random), position(random) * 0.2f, position(random) };
            const float value = intensity(random);
            light.diffuse = { value, value * 0.8f, value * 0.6f };
            light.specular = light.diffuse;
            light.direction = { 0.0f, 0.0f, -1.0f };
            light.range = 160.0f;
            light.attenuationConstant = 1.0f;
            light.attenuationQuadratic = 0.002f;
            light.spotInnerCos = 0.94f;
            light.spotOuterCos = 0.75f;
            light.spotFalloff = 1.5f;
            lights.push_back(light);
        }

        for (const std::size_t budget : budgets)
        {
            std::vector<std::uint64_t> previous;
            const auto begin = std::chrono::steady_clock::now();
            std::uint64_t checksum = 0;
            for (int iteration = 0; iteration < iterations; ++iteration)
            {
                const auto ranked = RankCandidates(
                    lights, {}, 3.0f, previous, { budget, 0.05f });
                previous.clear();
                const std::size_t selected = std::min(budget, ranked.size());
                for (std::size_t i = 0; i < selected; ++i)
                {
                    previous.push_back(ranked[i].light.stableId);
                    checksum ^= ranked[i].light.stableId + static_cast<std::uint64_t>(iteration);
                }
            }
            const auto end = std::chrono::steady_clock::now();
            const double milliseconds =
                std::chrono::duration<double, std::milli>(end - begin).count();
            std::printf("%zu,%zu,%d,%.3f,%.4f # %llu\n",
                count, budget, iterations, milliseconds,
                milliseconds * 1000.0 / static_cast<double>(iterations),
                static_cast<unsigned long long>(checksum));
        }
    }
    return 0;
}
