#pragma once

// Shadow far distance policy for the PSSM receiver.
//
// Kept free of Windows and of Ogre so it can be exercised on the host by
// tests/shadow_far_distance_tests.cpp. bzr_hooks.cpp reads the configured
// string, asks this what to write, and re-issues the game's own setter.
//
// The defect (reverse_engineering/shadow_cutoff_root_cause_20260825.md):
//
//   FUN_00680fe0 calls SceneManager::setShadowFarDistance(128.0) for every
//   shadow quality. Ogre's Focused/LiSPSM fit -- which PSSM uses -- clips the
//   cascade intersection body at that distance, so cascade 3's fitted
//   projection only covers receivers out to ~128 m. The receiver shader
//   nevertheless selects cascade 3 out to the 256 m outer split, so between
//   128 and 256 m the sample lands outside the border-clamped shadow map,
//   returns the white border, and the pixel reads fully lit.
//
//   The result is a hard shadow terminator at 128 m with nothing behind it.
//   It is most visible inside the player headlight's pool, because that light
//   has range 600 and the DX11 receiver stamps the sun's PSSM factor onto
//   every light's attenuation -- so the terminator is lit from both sides.
//
// The correction is one CPU-side value: make the clip match what the shader
// already trusts. It changes no split distance, no shader, no material, and
// no light.
//
// What it costs: cascade 3's fit covers twice the ground at the same texel
// budget, so its effective resolution halves. That is a real trade -- crisper
// shadows that stop dead at 128 m, against softer ones that reach the split
// the renderer was always designed around. The hard terminator is the worse
// artifact, and the Enhanced v2 receiver's terminal fade (the last 24 units
// ramp to lit) only becomes meaningful once coverage actually reaches it.

#include <cmath>
#include <cstddef>

namespace openshim::shadow
{

// Written by FUN_00680fe0 for every PSSM quality.
inline constexpr float kStockFarDistance = 128.0f;

// Cascade 3's outer split, as the receiver shader's pssmSplitPoints declares
// it (0.1 / 16 / 64 / 256). The fix tracks this, not the shadow quality byte:
// the stock constant is written identically for every quality, so keying off
// quality would invent a coupling the engine does not have.
inline constexpr float kOuterSplitDistance = 256.0f;

// Below 16 m nothing in this engine's scale is a meaningful shadow distance,
// and above 4096 m the fit degenerates.
inline constexpr float kMinFarDistance = 16.0f;
inline constexpr float kMaxFarDistance = 4096.0f;

enum class FarDistanceSource
{
    Default,      // nothing configured: the fix applies at the outer split
    Configured,   // an explicit in-range distance
    OptedOut,     // explicitly asked for stock behaviour
    Rejected,     // present but unusable; treated as opt-out, and logged
};

struct FarDistanceDecision
{
    // 0.0f means "do not re-issue the setter" -- the stock 128 stands.
    float distance = 0.0f;
    FarDistanceSource source = FarDistanceSource::Default;

    bool ShouldOverride() const { return distance > 0.0f; }
};

namespace detail
{

inline bool EqualsIgnoreCase(const char* text, const char* literal)
{
    if (text == nullptr || literal == nullptr)
        return false;
    for (;; ++text, ++literal)
    {
        const char a = (*text >= 'A' && *text <= 'Z')
            ? static_cast<char>(*text - 'A' + 'a') : *text;
        const char b = (*literal >= 'A' && *literal <= 'Z')
            ? static_cast<char>(*literal - 'A' + 'a') : *literal;
        if (a != b)
            return false;
        if (a == '\0')
            return true;
    }
}

// Deliberately not strtof: this has to behave identically regardless of the
// process locale. A comma decimal separator has bitten this codebase before.
inline bool ParseDistance(const char* text, float& out)
{
    if (text == nullptr || *text == '\0')
        return false;

    const char* p = text;
    while (*p == ' ' || *p == '\t')
        ++p;

    bool negative = false;
    if (*p == '+' || *p == '-')
    {
        negative = (*p == '-');
        ++p;
    }

    bool sawDigit = false;
    double value = 0.0;
    while (*p >= '0' && *p <= '9')
    {
        value = value * 10.0 + static_cast<double>(*p - '0');
        sawDigit = true;
        ++p;
    }
    if (*p == '.')
    {
        ++p;
        double scale = 0.1;
        while (*p >= '0' && *p <= '9')
        {
            value += static_cast<double>(*p - '0') * scale;
            scale *= 0.1;
            sawDigit = true;
            ++p;
        }
    }
    while (*p == ' ' || *p == '\t')
        ++p;

    if (!sawDigit || *p != '\0')
        return false;

    out = static_cast<float>(negative ? -value : value);
    return std::isfinite(out);
}

}  // namespace detail

// `configured` is the raw setting text, or nullptr/"" when nothing is set.
//
// Absent means the fix applies. That is the point of shipping it: the stock
// 128 is the defect, not a baseline worth defaulting to. "stock", "off" and
// the literal stock value are the ways to ask for the old behaviour back.
inline FarDistanceDecision DecideFarDistance(const char* configured)
{
    FarDistanceDecision decision;

    if (configured == nullptr || *configured == '\0')
    {
        decision.distance = kOuterSplitDistance;
        decision.source = FarDistanceSource::Default;
        return decision;
    }

    if (detail::EqualsIgnoreCase(configured, "stock") ||
        detail::EqualsIgnoreCase(configured, "off") ||
        detail::EqualsIgnoreCase(configured, "0"))
    {
        decision.source = FarDistanceSource::OptedOut;
        return decision;
    }

    float value = 0.0f;
    if (!detail::ParseDistance(configured, value))
    {
        decision.source = FarDistanceSource::Rejected;
        return decision;
    }

    // Asking for exactly the stock distance is a request for stock behaviour,
    // not a malformed value. Re-issuing the setter with 128 would be a no-op
    // that still installs a detour, which is a worse way to say "no".
    if (value == kStockFarDistance)
    {
        decision.source = FarDistanceSource::OptedOut;
        return decision;
    }

    if (value < kMinFarDistance || value > kMaxFarDistance)
    {
        decision.source = FarDistanceSource::Rejected;
        return decision;
    }

    decision.distance = value;
    decision.source = FarDistanceSource::Configured;
    return decision;
}

inline const char* SourceName(FarDistanceSource source)
{
    switch (source)
    {
    case FarDistanceSource::Default:    return "default";
    case FarDistanceSource::Configured: return "configured";
    case FarDistanceSource::OptedOut:   return "opted-out";
    case FarDistanceSource::Rejected:   return "rejected";
    }
    return "unknown";
}

}  // namespace openshim::shadow
