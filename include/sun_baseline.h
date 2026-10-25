#pragma once

// Enhanced sun lighting baseline: pure policy.
//
// The Enhanced render profile was calibrated against Campaign Reimagined,
// whose Lua pushes a sun power scale and a per-world colour grade through
// EXU. Stock maps never ran that Lua, so they drew the Enhanced shaders with
// stock sun values. pilot_flashlight.cpp applies this calibration natively,
// once, to the terrain sun (terrain_masterlight) the frame it appears, in the
// Enhanced profile only. Anything EXU/Lua writes afterwards still wins, and
// the sun rebuild restore carries the baseline across engine sun rebuilds.
//
// Kept free of Windows and of Ogre so tests/sun_baseline_tests.cpp can
// exercise it on the host. Configuration: [SunBaseline] in openshim.ini.

#include "shadow_far_distance.h"

#include <string>
#include <string_view>

namespace openshim::sunbaseline
{

// Per-world calibration. A mul of 1 and a floor of 0 leave a channel alone.
struct WorldSunBaseline
{
    float powerScale;
    float ambientMul[3];
    float ambientFloor[3];
    float diffuseMul[3];
    float diffuseFloor[3];
    float specularMul[3];
    float specularFloor[3];
};

// The Campaign Reimagined day calibration this matches.
inline constexpr WorldSunBaseline kDefaultBaseline = {
    1.15f,
    { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
};

// Titan: a warm, lower-power sun with floored colours.
inline constexpr WorldSunBaseline kTitanBaseline = {
    0.95f,
    { 1.10f, 0.78f, 0.42f }, { 0.34f, 0.23f, 0.11f },
    { 1.15f, 0.80f, 0.42f }, { 0.86f, 0.60f, 0.30f },
    // (1.00, 0.76, 0.46) * 0.80
    { 0.80f, 0.608f, 0.368f }, { 0.42f, 0.30f, 0.17f },
};

// Moon-class worlds (Moon, Europa, Io): a brighter sun and a cooler,
// dimmer ambient.
inline constexpr WorldSunBaseline kMoonClassBaseline = {
    1.32f,
    // (0.64, 0.68, 0.82) * 0.70
    { 0.448f, 0.476f, 0.574f }, { 0.0f, 0.0f, 0.0f },
    { 1.20f, 1.16f, 1.08f }, { 0.0f, 0.0f, 0.0f },
    // (1.30, 1.26, 1.18) * 1.08
    { 1.404f, 1.3608f, 1.2744f }, { 0.0f, 0.0f, 0.0f },
};

// `code` is the lowercase two-letter world prefix from the terrain detail
// atlas ("ti", "mn", ...); empty or unknown gets the default.
inline const WorldSunBaseline& BaselineForWorldCode(std::string_view code)
{
    if (code == "ti")
        return kTitanBaseline;
    if (code == "mn" || code == "eu" || code == "io")
        return kMoonClassBaseline;
    return kDefaultBaseline;
}

// Colour channels are clamped to this after grading.
inline constexpr float kColourMin = 0.0f;
inline constexpr float kColourMax = 4.0f;

// Accepted PowerScale override range; anything else is ignored as invalid.
inline constexpr float kMinPowerScale = 0.0f;
inline constexpr float kMaxPowerScale = 8.0f;

struct SunBaselineConfig
{
    bool enabled = true;
    bool worldColorGrading = true;
    bool hasPowerScale = false;
    float powerScale = 0.0f;
    bool hasShadowFar = false;
    float shadowFar = 0.0f;
};

// The light fields the baseline reads and writes. Ambient alpha and the
// light direction are never touched, so they are not carried.
struct SunLightStateLike
{
    float diffuse[3];
    float specular[3];
    float ambient[3];
    float powerScale;
    float shadowFar;
};

// Bits of the changed-fields mask. The runtime keeps its own field enum with
// the same values and static_asserts the match.
enum : unsigned
{
    kFieldDiffuse = 1u << 0,
    kFieldSpecular = 1u << 1,
    kFieldPowerScale = 1u << 3,
    kFieldShadowFar = 1u << 4,
    kFieldAmbient = 1u << 5,
};

namespace detail
{

inline float GradeChannel(float stock, float mul, float floorValue)
{
    float value = stock * mul;
    if (value < floorValue)
        value = floorValue;
    if (!(value >= kColourMin))  // also catches NaN
        value = kColourMin;
    if (value > kColourMax)
        value = kColourMax;
    return value;
}

inline bool GradeColour(const float stock[3], const float mul[3], const float floorValue[3],
                        float out[3])
{
    bool changed = false;
    for (int i = 0; i < 3; ++i)
    {
        out[i] = GradeChannel(stock[i], mul[i], floorValue[i]);
        if (out[i] != stock[i])
            changed = true;
    }
    return changed;
}

inline bool IsBlank(const std::string& text)
{
    for (const char c : text)
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            return false;
    return true;
}

}  // namespace detail

// Computes the calibrated sun from the engine's stock values. `out` starts as
// a copy of `stock`; `changedFieldsMask` names the fields whose value differs
// from stock, which are the only ones the runtime writes (and later reverts).
inline void ComputeBaseline(const SunBaselineConfig& config,
                            const WorldSunBaseline& world,
                            const SunLightStateLike& stock,
                            SunLightStateLike& out,
                            unsigned& changedFieldsMask)
{
    out = stock;
    changedFieldsMask = 0;

    out.powerScale = config.hasPowerScale ? config.powerScale : world.powerScale;
    if (out.powerScale != stock.powerScale)
        changedFieldsMask |= kFieldPowerScale;

    if (config.worldColorGrading)
    {
        if (detail::GradeColour(stock.ambient, world.ambientMul, world.ambientFloor, out.ambient))
            changedFieldsMask |= kFieldAmbient;
        if (detail::GradeColour(stock.diffuse, world.diffuseMul, world.diffuseFloor, out.diffuse))
            changedFieldsMask |= kFieldDiffuse;
        if (detail::GradeColour(stock.specular, world.specularMul, world.specularFloor,
                                out.specular))
            changedFieldsMask |= kFieldSpecular;
    }

    if (config.hasShadowFar)
    {
        out.shadowFar = config.shadowFar;
        if (out.shadowFar != stock.shadowFar)
            changedFieldsMask |= kFieldShadowFar;
    }
}

// Reads [SunBaseline]. The callables are
//   bool getString(const char* key, std::string& out)  -- true when present
//   bool getBool(const char* key, bool& out)           -- true when present
//   void onInvalid(const char* key)                    -- called per bad number
// A blank or absent PowerScale means the per-world table; a blank or absent
// ShadowFarDistance leaves the engine's value alone. An unparsable or
// out-of-range number is reported and then treated as absent.
template <typename GetString, typename GetBool, typename OnInvalid>
SunBaselineConfig ParseSunBaselineConfig(GetString&& getString, GetBool&& getBool,
                                         OnInvalid&& onInvalid)
{
    SunBaselineConfig config;

    bool flag = true;
    if (getBool("Enabled", flag))
        config.enabled = flag;
    flag = true;
    if (getBool("WorldColorGrading", flag))
        config.worldColorGrading = flag;

    std::string text;
    if (getString("PowerScale", text) && !detail::IsBlank(text))
    {
        float value = 0.0f;
        if (openshim::shadow::detail::ParseDistance(text.c_str(), value) &&
            value >= kMinPowerScale && value <= kMaxPowerScale)
        {
            config.hasPowerScale = true;
            config.powerScale = value;
        }
        else
        {
            onInvalid("PowerScale");
        }
    }

    text.clear();
    if (getString("ShadowFarDistance", text) && !detail::IsBlank(text))
    {
        float value = 0.0f;
        if (openshim::shadow::detail::ParseDistance(text.c_str(), value) &&
            value >= openshim::shadow::kMinFarDistance &&
            value <= openshim::shadow::kMaxFarDistance)
        {
            config.hasShadowFar = true;
            config.shadowFar = value;
        }
        else
        {
            onInvalid("ShadowFarDistance");
        }
    }

    return config;
}

}  // namespace openshim::sunbaseline
