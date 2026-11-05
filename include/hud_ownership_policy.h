// Scoped renderer ownership shared with optional EXU clients. No saved settings.
#pragma once
#include <cstdint>
namespace BZROpenShim::HudOwnership
{
    constexpr uint32_t Hull=1, Ammo=2, Weapons=4, Scrap=8, Radar=16, Commands=32;
    constexpr uint32_t All=Hull|Ammo|Weapons|Scrap|Radar|Commands;
    constexpr bool Valid(uint32_t mask) noexcept { return (mask&~All)==0; }
    constexpr bool Claimed(uint32_t mask,uint32_t area) noexcept { return (mask&area)!=0; }
}
