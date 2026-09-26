// Stable optional OpenShim fog-wake ABI v1. Keep the EXU copy byte-identical.
// Values only: never pass Lua, game, Ogre, STL objects or ownership across DLLs.
#pragma once
#include <cstdint>
namespace FogWakeApi {
constexpr std::uint32_t Version = 1;
#pragma pack(push, 4)
struct Config {
    std::uint32_t size = sizeof(Config), version = Version;
    float centerX = 0, baseY = 0, centerZ = 0;
    float width = 384, cellSize = 4, height = 8;
    float wakeRadius = 9, recoverySeconds = 12, windX = 0, windZ = 0;
    float density = .35f, colorR = .7f, colorG = .75f, colorB = .8f;
};
struct Status {
    std::uint32_t size = sizeof(Status), version = Version;
    std::uint32_t supported = 0, configured = 0, renderReady = 0;
    std::uint32_t emitterCount = 0, activeCells = 0;
    float maxClearance = 0;
    std::uint32_t renderedBillboards = 0;
};
#pragma pack(pop)
static_assert(sizeof(Config) == 64, "Fog Config ABI");
static_assert(sizeof(Status) == 36, "Fog Status ABI");
// Every operation returns 1 on success, 0 on rejection/unavailability.
using ConfigureFn = std::int32_t (__cdecl*)(const Config*);
using UpdateFn = std::int32_t (__cdecl*)(double);
using ObserveFn = std::int32_t (__cdecl*)(std::uint32_t, float, float, float);
using RemoveFn = std::int32_t (__cdecl*)(std::uint32_t);
using ResetFn = std::int32_t (__cdecl*)();
using StatusFn = std::int32_t (__cdecl*)(Status*);
// Configure replaces the bank and enables it. Reset disables and clears it.
// Update uses mission simulation seconds, BEFORE Observe calls for that tick.
// Observe identifiers are positive Lua-assigned tokens, never native handles.
// Status renderReady means renderer resources exist, not merely API support.
}
