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
        // Two texture units sharing UV set 0: stage 0 modulate, stage 1
        // modulate or alpha_blend (IsSupportedTwoStageCombo). Appended so the
        // existing values keep their meaning.
        FixedFuncTextured2,
    };

    const char* LegacyPassKindName(LegacyPassKind kind) noexcept;
    const char* CompatPathName(CompatPath path) noexcept;

    // Ogre::LayerBlendOperationEx / LayerBlendSource values (OgreBlendMode.h,
    // Ogre 1.10). The runtime reads them from a TextureUnitState's
    // LayerBlendModeEx; tests use them directly.
    namespace BlendOpEx
    {
        constexpr int Source1 = 0;
        constexpr int Modulate = 2;
        constexpr int Add = 5;
        constexpr int BlendTextureAlpha = 10;
    }
    namespace BlendSource
    {
        constexpr int Current = 0;
        constexpr int Texture = 1;
    }

    // One fixed-function texture stage as the fixed pipeline ran it.
    // known=false when the runtime could not read it; an unknown stage is
    // never supported.
    struct TextureStageDesc
    {
        bool known = false;
        int colourOp = -1;
        int colourSrc1 = -1;
        int colourSrc2 = -1;
        int alphaOp = -1;
        int alphaSrc1 = -1;
        int alphaSrc2 = -1;
        unsigned texCoordSet = 0;
    };

    // The material-script colour_op shorthands, recognised from the expanded
    // operation Ogre stores (TextureUnitState::setColourOperation).
    enum class StageCombine : uint8_t
    {
        Modulate = 0,       // colour_op modulate (the default)
        Add,                // colour_op add
        Replace,            // colour_op replace
        AlphaBlendTexture,  // colour_op alpha_blend: lerp(current, tex, tex.a)
        Unsupported,
    };

    const char* StageCombineName(StageCombine combine) noexcept;
    StageCombine ClassifyStageColour(const TextureStageDesc& stage) noexcept;
    // Alpha is supported only in its default form, texture * current.
    bool IsDefaultStageAlpha(const TextureStageDesc& stage) noexcept;

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
        // Per-stage combine state read from the pass. Drives the two-unit
        // decision; the one-unit path keeps its historical modulate
        // assumption (colorOp0) so existing content does not change path.
        std::vector<TextureStageDesc> stages;
    };

    // The bounded two-unit support set: exactly two stages, both read, both
    // on UV set 0, default alpha on both, stage 0 modulate, stage 1 modulate
    // or alpha_blend. That is what shipped content uses: ISDF Chronicles'
    // rain family (xrain, xrainL/R: a scrolling streak texture masked by
    // colour_op alpha_blend) and plain detail/overlay modulation. Anything
    // else stays declined rather than guessed.
    bool IsSupportedTwoStageCombo(const LegacyPassDesc& desc) noexcept;

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

    // Stage-explicit form of the above. MapLegacyFamilyProgram infers the
    // stage from the spelling, which is right for "Effect_vertexHLSL" and
    // wrong for stage-agnostic family names such as "simple_one_tex" -- there
    // the heuristic falls through to the fragment adapter, and binding a
    // fragment adapter as a vertex program is silently fatal on D3D11. The
    // runtime always knows which stage it is filling, so it asks for it.
    bool MapLegacyFamilyProgramForStage(std::string_view legacyName,
                                        bool wantVertex,
                                        std::string& outCompat);

    // Material classes this layer must never synthesize onto, however the
    // ladder classified them.
    //
    // Found the hard way on a live DX11 run (2026-09-19): the resolver
    // reached a UI material through the en-high-pssm scheme miss, remapped
    // the UI_vertex/UI_fragment family, and synthesized onto it. The process
    // did not survive. Two separate guards were missing and both are here
    // now, because either alone would have prevented it:
    //
    //   1. The material's own name could not be read -- it logged as
    //      "<unknown>". A pointer this layer cannot even get Resource::getName
    //      off is not a pointer it should be calling createTechnique on.
    //      That check lives at the call site, since it needs the live ABI.
    //   2. UI, overlay, cursor, font, HUD and cockpit surfaces are listed as
    //      out of scope in Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md, and
    //      that exclusion was never implemented. This is it.
    //
    // Matched case-insensitively against the material name and against both
    // program names, because either can identify the class.
    bool IsExcludedFromSynthesis(std::string_view materialName,
                                 const LegacyPassDesc& desc) noexcept;

    // Compat program names owned by openshim_dx11_fixedfunc.program.
    const char* FixedFuncTexturedVertex() noexcept;
    const char* FixedFuncTexturedFragment() noexcept;
    const char* FixedFuncUntexturedVertex() noexcept;
    const char* FixedFuncUntexturedFragment() noexcept;
    const char* FixedFuncTextured2Vertex() noexcept;
    // Fragment program for a supported stage-1 combine, else nullptr.
    const char* FixedFuncTextured2Fragment(StageCombine stage1) noexcept;

    LegacyPassKind ClassifyLegacyPass(const LegacyPassDesc& desc) noexcept;

    // Bounded fixed-function support set for Phase 2. 0 units always
    // supported; 1 unit for modulate/replace/add/alpha_blend (case-insensitive,
    // alpha_blend covers the common alpha cases). 2+ units and exotic
    // combine ops return false here; the two-unit path is decided from the
    // stages read off the pass instead (IsSupportedTwoStageCombo).
    bool IsSupportedFixedFuncCombo(int textureUnits,
                                   std::string_view colorOp0) noexcept;

    // The program pair a synthesized compatibility technique must bind for a
    // chosen path. Returns false for the paths that synthesize nothing
    // (KeepNative, SkipShaderless): the runtime must not mutate the material
    // in those cases.
    //
    // Both stages are always filled on success, because a D3D11 pass with one
    // stage bound and the other empty is exactly the shaderless-draw failure
    // this ladder exists to remove -- half a remap is worse than none. A pass
    // that names a family on only one stage takes that family's adapter for
    // both (they are authored as pairs); the generic fixed-function adapter
    // of the matching texturing stands in only when neither stage resolves.
    bool ResolveCompatPrograms(CompatPath path,
                               const LegacyPassDesc& desc,
                               std::string& outVertex,
                               std::string& outFragment);

    // Vertex elements the renderable that triggered synthesis actually
    // supplies. D3D11 builds an input layout by matching every element of the
    // bound vertex shader's input signature against the mesh's vertex
    // declaration, and throws (D3D11VertexDeclaration::getILayoutByShader,
    // "Unable to set D3D11 vertex declaration") on the first one it cannot
    // find. That exception escapes Root::renderOneFrame every frame; the game
    // answers each one by stepping a quality level down (0x007AE480) and quits
    // with "complete render failure" once there is nothing left to lower.
    //
    // known=false means the runtime could not read the declaration (no
    // renderable, or the read faulted). The safe reading of "unknown" is "no
    // vertex colour": dropping COLOR0 only loses a tint, while requiring it on
    // a mesh without it is fatal. TEXCOORD0 is assumed present when unknown,
    // because a textured pass on untextured geometry is not something a
    // fixed-function author ships and dropping it would blank every texture.
    struct VertexInputs
    {
        bool known = false;
        bool position = true;
        bool diffuse = false;
        bool texcoord0 = true;
    };

    enum class VertexInputFit : uint8_t
    {
        Unchanged = 0,  // the resolved vertex program already matches
        Adapted,        // swapped for an input-reduced OSE_FixedFunc variant
        Unsatisfiable,  // no variant can bind (no POSITION): fail closed
    };

    const char* VertexInputFitName(VertexInputFit fit) noexcept;

    // Rewrites a resolved compat vertex program (OSE_FixedFunc_* or
    // OSE_Compat_*) to the variant whose input signature is a subset of the
    // renderable's elements. Every variant keeps the output signature of the
    // entry point it stands in for, so the paired fragment program is never
    // touched. Programs this layer does not own come back Unchanged.
    VertexInputFit FitVertexProgramToInputs(std::string_view resolvedVertex,
                                            const VertexInputs& inputs,
                                            std::string& outVertex);

    // "position,diffuse,texcoord0" / "unknown" -- for [DX11COMPAT] lines.
    std::string DescribeVertexInputs(const VertexInputs& inputs);

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
        // Techniques actually synthesized onto a live material, and attempts
        // that failed and were negative-cached. Distinct from the path
        // counters above, which count decisions rather than mutations.
        uint64_t techniquesInstantiated = 0;
        uint64_t instantiationFailures = 0;
    };

    std::string FormatCompatSummary(const CompatCounters& counters);
} // namespace BZROpenShim::RenderProfiles::Dx11Compat
