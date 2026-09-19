#pragma once

// DX11 legacy material compatibility policy.
//
// Pure engine module: no Win32, no Ogre, no process state. Every decision here
// is a deterministic function of its inputs so the compatibility ladder can be
// unit-tested without launching the game (see
// tests/dx11_legacy_material_compat_tests.cpp).
//
// Ownership split (see Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md):
//   this module - classification of legacy passes, known-family remap table,
//                 safe/aggressive policy, cache-key construction,
//                 source-technique selection, config defaults/parsing,
//                 fixed-function support set, diagnostic string builders.
//   runtime     - Ogre ABI resolution, technique instantiation/caching,
//                 once-only logging, counters, shaderless-draw guard wiring.
//                 Lives in src/patches/ogre_render_profile.cpp.

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace BZROpenShim::RenderProfiles::Dx11Compat
{
    // Compatibility classification for a single legacy pass.
    enum class LegacyPassKind : uint8_t
    {
        NativeDx11 = 0,      // every referenced program is DX11-usable
        TrueFixedFunction,   // no vertex AND no fragment program reference
        KnownLegacyFamily,    // SM2/SM3-only ref matching a known BZR family
        UnknownCustom,        // unsupported program outside the known table
    };

    // Ordered resolver outcome. Mirrors the doc ladder Level 0..5:
    // KeepNative (L0), FamilyRemap (L1), FixedFunc* (L2), AggressiveGeneric
    // (L4, opt-in), SkipShaderless (L5 guard / fail-closed).
    // RTSS (L3) is reported as FixedFunc* when the runtime proves it can
    // generate the technique; until then it degrades to SkipShaderless with
    // a distinct reason (see FormatRtssUnavailableLog).
    enum class CompatPath : uint8_t
    {
        KeepNative = 0,
        FamilyRemap,
        FixedFuncTextured,
        FixedFuncUntextured,
        AggressiveGeneric,
        SkipShaderless,
    };

    const char* LegacyPassKindName(LegacyPassKind kind) noexcept;
    const char* CompatPathName(CompatPath path) noexcept;

    // Minimal programmable-pass description. The runtime fills this from the
    // narrow Ogre ABI (hasVertexProgram/hasFragmentProgram + program names +
    // targets where resolvable); tests construct it directly.
    struct LegacyPassDesc
    {
        bool hasVertexRef = false;
        bool hasFragmentRef = false;
        std::string vertexProgram;
        std::string vertexTarget;
        std::string fragmentProgram;
        std::string fragmentTarget;
        // Fixed-function texture state observed on the source pass. Bounded
        // support set (doc Level 2): 0 units always, 1 unit for the common
        // color ops below, anything else is logged once as unsupported.
        int textureUnits = 0;
        std::string colorOp0; // modulate|replace|add|alpha_blend (any case)
    };

    struct CompatConfig
    {
        bool compatEnabled = true;
        bool guardEnabled = true;
        bool aggressiveEnabled = false;
    };

    CompatConfig DefaultCompatConfig() noexcept;

    // Accepts the same boolean tokens as the rest of openshim.ini
    // (1/true/on/yes/enabled vs 0/false/off/no/disabled, case-insensitive,
    // ASCII-trimmed). Unknown text returns defaultValue.
    bool ParseCompatFlag(std::string_view raw, bool defaultValue) noexcept;

    // DX11-usable shader targets. Covers the SM4 family Ogre's D3D11
    // rendersystem accepts (vs_4_0/ps_4_0, feature-level 9.x variants,
    // vs_5_0/ps_5_0). Everything else with a program reference (vs_1_x,
    // vs_2_x, vs_3_0/ps_3_0, arbvp/cg/fp/vp, empty handled by callers) is a
    // legacy target. Case-insensitive.
    bool IsDx11SupportedShaderTarget(std::string_view target) noexcept;

    bool EqualsNoCase(std::string_view a, std::string_view b) noexcept;
    std::string ToLowerCopy(std::string_view text);

    // Known BZR/legacy program-family remap. Case-insensitive, prefix-based so
    // HLSL/CG/ASM spelling variants of the same family all resolve. Returns
    // true and fills outCompat (e.g. "OSE_Compat_Effect_vertex") on match.
    // Never rewrites files on disk; the runtime clones pass state and swaps
    // only the program reference.
    bool MapLegacyFamilyProgram(std::string_view legacyName,
                                std::string& outCompat);
    bool IsKnownLegacyFamilyProgram(std::string_view legacyName) noexcept;

    // Compat program names owned by openshim_dx11_fixedfunc.program.
    const char* FixedFuncTexturedVertex() noexcept;
    const char* FixedFuncTexturedFragment() noexcept;
    const char* FixedFuncUntexturedVertex() noexcept;
    const char* FixedFuncUntexturedFragment() noexcept;

    LegacyPassKind ClassifyLegacyPass(const LegacyPassDesc& desc) noexcept;

    // Bounded fixed-function support set for Phase 2. 0 units always
    // supported; 1 unit for modulate/replace/add/alpha_blend (case-insensitive,
    // alpha_blend covers the common alpha cases). Multi-texture and exotic
    // combine ops return false so the caller logs once instead of guessing.
    bool IsSupportedFixedFuncCombo(int textureUnits,
                                   std::string_view colorOp0) noexcept;

    // Pure policy: which resolver path a classified pass takes.
    // resourcesAvailable=false forces SkipShaderless for every non-native
    // pass (fail closed to guard + one startup warning, never a half-working
    // technique).
    CompatPath DecideCompatPath(LegacyPassKind kind,
                                const LegacyPassDesc& desc,
                                const CompatConfig& config,
                                bool resourcesAvailable = true) noexcept;

    // Source-technique selection policy (doc: exact scheme+LOD, exact scheme+
    // closest LOD, base/default/blank scheme, first as last resort). Pure
    // index model so tests can cover it without Ogre.
    struct TechniqueCandidate
    {
        std::string scheme;
        unsigned short lod = 0;
        size_t index = 0;
        bool supported = false;
    };

    // Returns the candidate INDEX value (not the vector position) of the best
    // semantic source, or kNoSourceTechnique when candidates is empty.
    constexpr size_t kNoSourceTechnique = static_cast<size_t>(-1);
    size_t SelectSourceTechniqueIndex(
        const std::vector<TechniqueCandidate>& candidates,
        std::string_view requestedScheme,
        unsigned short requestedLod) noexcept;

    // Stable cache key equivalent to
    // (material identity, requested scheme, lod, source technique,
    //  compatibility variant). Only ASCII alphanumerics plus _ - . survive;
    // everything else folds to '_' so keys are filesystem/log safe.
    std::string BuildCompatCacheKey(std::string_view material,
                                    std::string_view requestedScheme,
                                    unsigned short lodIndex,
                                    size_t sourceTechnique,
                                    std::string_view variant);

    // Bounded diagnostic builders. All output is single-line ASCII of the
    // form "[DX11COMPAT] ..." suitable for once-only logging.
    std::string FormatCompatAppliedLog(std::string_view material,
                                       std::string_view source,
                                       CompatPath path,
                                       bool cached);
    std::string FormatFamilyRemapLog(std::string_view material,
                                     std::string_view family,
                                     std::string_view fromVs,
                                     std::string_view fromPs);
    std::string FormatUnsupportedLog(std::string_view material,
                                     std::string_view vsName,
                                     std::string_view psName,
                                     bool aggressiveAvailable);
    std::string FormatShaderlessSkippedLog(std::string_view material,
                                           unsigned technique,
                                           unsigned pass,
                                           std::string_view vsName,
                                           std::string_view psName);
    std::string FormatRtssUnavailableLog(std::string_view material);

    // Engine-independent counters for exit/summary logging.
    struct CompatCounters
    {
        uint64_t nativeSupported = 0;
        uint64_t familyRemaps = 0;
        uint64_t fixedFuncGenerated = 0;
        uint64_t rtssGenerated = 0;
        uint64_t aggressiveFallbacks = 0;
        uint64_t unsupportedCustom = 0;
        uint64_t shaderlessSkipped = 0;
    };

    std::string FormatCompatSummary(const CompatCounters& counters);
} // namespace BZROpenShim::RenderProfiles::Dx11Compat
