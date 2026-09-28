#pragma once

// Size caps for the diagnostic files OpenShim writes while a profiler is on:
// the Ogre profiler's openshim_ogre_profile.csv and the native CPU sampler's
// openshim_cpu_samples_*.bin. Both used to grow without limit.
//
// Kept free of Windows so tests/diagnostic_output_cap_tests.cpp can run it on
// the host. C++14-compatible on purpose: the Ogre profiler translation unit
// that includes it is compiled as C++14 (see Plugin_OpenShim.vcxproj), so no
// nested namespace definitions and every static_assert carries a message.

#include <cstdint>

namespace BZROpenShim
{
namespace DiagnosticOutputCap
{
    constexpr uint64_t kBytesPerMiB = 1024ull * 1024ull;

    // Largest accepted value, in MiB (1 TiB). Anything larger is clamped.
    constexpr uint32_t kMaxCapMiB = 1024u * 1024u;

    // Ogre profiler CSV: one ~250-byte row per second, appended across
    // sessions. 64 MiB is roughly three days of continuous profiling. On
    // reaching it the file is rotated once (to *.prev.csv) and restarted.
    constexpr uint32_t kDefaultOgreCsvCapMiB = 64;

    // Native CPU sampler: about 150 KB/s at the default 1 kHz / depth 48 with
    // two busy threads (the 2026-08-23 Phase 2 calibration run), so 256 MiB is
    // roughly half an hour. On reaching it the sampling window closes and the
    // file is finalised normally (stats + end chunk), so it stays parseable.
    constexpr uint32_t kDefaultCpuSamplerCapMiB = 256;

    static_assert(kDefaultOgreCsvCapMiB <= kMaxCapMiB,
        "default Ogre CSV cap exceeds the accepted maximum");
    static_assert(kDefaultCpuSamplerCapMiB <= kMaxCapMiB,
        "default CPU sampler cap exceeds the accepted maximum");

    inline bool IsSpace(char c)
    {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    // Parses a whole number of MiB. Surrounding whitespace is allowed; any
    // other character (sign, decimal point, unit suffix) makes the value
    // invalid. Returns false for null, empty or invalid text. "0" is valid and
    // means "no cap". Values above kMaxCapMiB are clamped to it.
    inline bool TryParseCapMiB(const char* text, uint32_t& outMiB)
    {
        if (!text)
            return false;
        while (IsSpace(*text))
            ++text;
        if (*text < '0' || *text > '9')
            return false;

        uint64_t value = 0;
        while (*text >= '0' && *text <= '9')
        {
            if (value <= kMaxCapMiB)
                value = value * 10u + static_cast<uint64_t>(*text - '0');
            ++text;
        }
        while (IsSpace(*text))
            ++text;
        if (*text != '\0')
            return false;

        outMiB = value > kMaxCapMiB ? kMaxCapMiB : static_cast<uint32_t>(value);
        return true;
    }

    // Byte cap for a MiB setting; 0 stays 0 ("no cap").
    inline uint64_t CapBytesFromMiB(uint32_t mib)
    {
        return static_cast<uint64_t>(mib) * kBytesPerMiB;
    }

    // Resolves a cap from the first valid text, in priority order (e.g. the
    // environment, then openshim.ini). Invalid or missing text falls through.
    inline uint64_t ResolveCapBytes(
        const char* primaryText,
        const char* secondaryText,
        uint32_t defaultMiB)
    {
        uint32_t mib = 0;
        if (TryParseCapMiB(primaryText, mib))
            return CapBytesFromMiB(mib);
        if (TryParseCapMiB(secondaryText, mib))
            return CapBytesFromMiB(mib);
        return CapBytesFromMiB(defaultMiB);
    }

    // True once a file of `currentBytes` has reached a cap. A cap of 0 never
    // triggers.
    inline bool ReachedCap(uint64_t currentBytes, uint64_t capBytes)
    {
        return capBytes != 0 && currentBytes >= capBytes;
    }
} // namespace DiagnosticOutputCap
} // namespace BZROpenShim
