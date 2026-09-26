// Pure DX11 legacy material compatibility policy. No Win32, no Ogre, no
// process state: deterministic functions of their inputs for unit tests.

#include "dx11_legacy_material_compat.h"

#include <cctype>
#include <cstdio>

namespace BZROpenShim::RenderProfiles::Dx11Compat
{
    namespace
    {
        std::string_view TrimAscii(std::string_view text) noexcept
        {
            size_t begin = 0;
            while (begin < text.size() &&
                   (text[begin] == ' ' || text[begin] == '\t' ||
                    text[begin] == '\r' || text[begin] == '\n'))
            {
                ++begin;
            }
            size_t end = text.size();
            while (end > begin &&
                   (text[end - 1] == ' ' || text[end - 1] == '\t' ||
                    text[end - 1] == '\r' || text[end - 1] == '\n'))
            {
                --end;
            }
            return text.substr(begin, end - begin);
        }

        char ToLowerChar(char c) noexcept
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        bool StartsWithLower(std::string_view lower, std::string_view prefix) noexcept
        {
            return lower.size() >= prefix.size() &&
                   lower.substr(0, prefix.size()) == prefix;
        }

        bool ContainsLower(std::string_view lower, std::string_view needle) noexcept
        {
            return lower.find(needle) != std::string_view::npos;
        }

        struct FamilyPrefix
        {
            const char* prefix; // already lowercase
            const char* compatVs;
            const char* compatPs;
        };

        // Table-driven, case-insensitive. Prefixes (not exact names) so
        // HLSL/CG/ASM spelling variants of the same BZR family all resolve.
        // Compat names are owned by openshim_dx11_fixedfunc.program.
        constexpr FamilyPrefix kFamilyPrefixes[] = {
            { "effect_vertex", "OSE_Compat_Effect_vertex", "OSE_Compat_Effect_fragment" },
            { "effect_fragment", "OSE_Compat_Effect_vertex", "OSE_Compat_Effect_fragment" },
            { "effect_pixel", "OSE_Compat_Effect_vertex", "OSE_Compat_Effect_fragment" },
            { "textured_vertex", "OSE_Compat_Textured_vertex", "OSE_Compat_Textured_fragment" },
            { "textured_fragment", "OSE_Compat_Textured_vertex", "OSE_Compat_Textured_fragment" },
            { "textured_pixel", "OSE_Compat_Textured_vertex", "OSE_Compat_Textured_fragment" },
            { "untextured_vertex", "OSE_Compat_Untextured_vertex", "OSE_Compat_Untextured_fragment" },
            { "untextured_fragment", "OSE_Compat_Untextured_vertex", "OSE_Compat_Untextured_fragment" },
            { "untextured_pixel", "OSE_Compat_Untextured_vertex", "OSE_Compat_Untextured_fragment" },
            { "sky_vertex", "OSE_Compat_Sky_vertex", "OSE_Compat_Sky_fragment" },
            { "sky_fragment", "OSE_Compat_Sky_vertex", "OSE_Compat_Sky_fragment" },
            { "sky_pixel", "OSE_Compat_Sky_vertex", "OSE_Compat_Sky_fragment" },
            { "base_vertex", "OSE_Compat_Base_vertex", "OSE_Compat_Base_fragment" },
            { "base_fragment", "OSE_Compat_Base_vertex", "OSE_Compat_Base_fragment" },
            { "base_pixel", "OSE_Compat_Base_vertex", "OSE_Compat_Base_fragment" },
            { "simple_one_tex_vertex", "OSE_Compat_SimpleOneTex_vertex", "OSE_Compat_SimpleOneTex_fragment" },
            { "simple_one_tex_fragment", "OSE_Compat_SimpleOneTex_vertex", "OSE_Compat_SimpleOneTex_fragment" },
            { "simple_one_tex_pixel", "OSE_Compat_SimpleOneTex_vertex", "OSE_Compat_SimpleOneTex_fragment" },
            // Unreachable in practice, and deliberately kept anyway.
            // IsExcludedFromSynthesis() rejects the "ui_" needle on the
            // program name, so every input that matches these three prefixes
            // is declined as excluded-class and falls back to stock before it
            // can be instantiated -- which is the correct outcome, because the
            // stock UI family is exactly what these would be standing in for.
            // They stay so the table is a complete statement of the family
            // map, and so a future narrowing of the exclusion list does not
            // silently leave UI materials with no adapter. Do not read a
            // rendering symptom on a UI, HUD or radar surface as coming from
            // here: check the log for "reason=excluded-class" first.
            { "ui_vertex", "OSE_Compat_Ui_vertex", "OSE_Compat_Ui_fragment" },
            { "ui_fragment", "OSE_Compat_Ui_vertex", "OSE_Compat_Ui_fragment" },
            { "ui_pixel", "OSE_Compat_Ui_vertex", "OSE_Compat_Ui_fragment" },
            { "terrain_vertex", "OSE_Compat_Terrain_vertex", "OSE_Compat_Terrain_fragment" },
            { "terrain_fragment", "OSE_Compat_Terrain_vertex", "OSE_Compat_Terrain_fragment" },
            { "terrain_pixel", "OSE_Compat_Terrain_vertex", "OSE_Compat_Terrain_fragment" },
        };

        bool LookupFamily(std::string_view lowerName,
                          const char*& outVs,
                          const char*& outPs) noexcept
        {
            for (const FamilyPrefix& entry : kFamilyPrefixes)
            {
                if (StartsWithLower(lowerName, entry.prefix))
                {
                    outVs = entry.compatVs;
                    outPs = entry.compatPs;
                    return true;
                }
            }
            // simple_one_tex without an explicit stage infix (e.g. mod
            // authors shortening to SimpleOneTexVS): decide by stage hint.
            if (StartsWithLower(lowerName, "simple_one_tex"))
            {
                if (ContainsLower(lowerName, "vertex") || ContainsLower(lowerName, "vs"))
                {
                    outVs = "OSE_Compat_SimpleOneTex_vertex";
                    outPs = "OSE_Compat_SimpleOneTex_fragment";
                    return true;
                }
                if (ContainsLower(lowerName, "fragment") ||
                    ContainsLower(lowerName, "pixel") ||
                    ContainsLower(lowerName, "ps") || ContainsLower(lowerName, "frag"))
                {
                    outVs = "OSE_Compat_SimpleOneTex_vertex";
                    outPs = "OSE_Compat_SimpleOneTex_fragment";
                    return true;
                }
            }
            return false;
        }

        bool IsNativeProgramName(std::string_view name) noexcept
        {
            // OSE_Compat_*/OSE_FixedFunc_* are ours; *HLSL4/*SM4*/*SM5* spell
            // native DX11 delegates. Checked on the lowercase copy by callers.
            if (ContainsLower(name, "ose_compat_") || ContainsLower(name, "ose_fixedfunc_"))
            {
                return true;
            }
            if (ContainsLower(name, "hlsl4") || ContainsLower(name, "sm4") ||
                ContainsLower(name, "sm5") || ContainsLower(name, "vs_4_") ||
                ContainsLower(name, "ps_4_") || ContainsLower(name, "vs_5_") ||
                ContainsLower(name, "ps_5_"))
            {
                return true;
            }
            return false;
        }

        std::string SanitizeKeyChar(char c)
        {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') || c == '_' || c == '-' || c == '.')
            {
                return std::string(1, c);
            }
            return "_";
        }
    } // namespace

    const char* LegacyPassKindName(LegacyPassKind kind) noexcept
    {
        switch (kind)
        {
        case LegacyPassKind::NativeDx11: return "native";
        case LegacyPassKind::TrueFixedFunction: return "fixedfunc";
        case LegacyPassKind::KnownLegacyFamily: return "family-remap";
        case LegacyPassKind::UnknownCustom: return "unknown-custom";
        }
        return "unknown";
    }

    const char* CompatPathName(CompatPath path) noexcept
    {
        switch (path)
        {
        case CompatPath::KeepNative: return "native";
        case CompatPath::FamilyRemap: return "family-remap";
        case CompatPath::FixedFuncTextured: return "fixedfunc-textured";
        case CompatPath::FixedFuncUntextured: return "fixedfunc-untextured";
        case CompatPath::AggressiveGeneric: return "aggressive-generic";
        case CompatPath::SkipShaderless: return "skip";
        case CompatPath::FixedFuncTextured2: return "fixedfunc-textured2";
        case CompatPath::SuppressPass: return "suppress";
        }
        return "skip";
    }

    const char* StageCombineName(StageCombine combine) noexcept
    {
        switch (combine)
        {
        case StageCombine::Modulate: return "modulate";
        case StageCombine::Add: return "add";
        case StageCombine::Replace: return "replace";
        case StageCombine::AlphaBlendTexture: return "alpha_blend";
        case StageCombine::Unsupported: return "unsupported";
        }
        return "unsupported";
    }

    StageCombine ClassifyStageColour(const TextureStageDesc& stage) noexcept
    {
        if (!stage.known)
        {
            return StageCombine::Unsupported;
        }
        const bool texOverCurrent = stage.colourSrc1 == BlendSource::Texture &&
                                    stage.colourSrc2 == BlendSource::Current;
        const bool currentOverTex = stage.colourSrc1 == BlendSource::Current &&
                                    stage.colourSrc2 == BlendSource::Texture;
        switch (stage.colourOp)
        {
        case BlendOpEx::Modulate:
            // Commutative, so either operand order is the same combine.
            return (texOverCurrent || currentOverTex) ? StageCombine::Modulate
                                                      : StageCombine::Unsupported;
        case BlendOpEx::Add:
            return (texOverCurrent || currentOverTex) ? StageCombine::Add
                                                      : StageCombine::Unsupported;
        case BlendOpEx::Source1:
            return stage.colourSrc1 == BlendSource::Texture
                ? StageCombine::Replace
                : StageCombine::Unsupported;
        case BlendOpEx::BlendTextureAlpha:
            // src1 * tex.a + src2 * (1 - tex.a); only the texture-over-current
            // order is what colour_op alpha_blend produces.
            return texOverCurrent ? StageCombine::AlphaBlendTexture
                                  : StageCombine::Unsupported;
        default:
            return StageCombine::Unsupported;
        }
    }

    bool IsDefaultStageAlpha(const TextureStageDesc& stage) noexcept
    {
        return stage.known && stage.alphaOp == BlendOpEx::Modulate &&
               ((stage.alphaSrc1 == BlendSource::Texture &&
                 stage.alphaSrc2 == BlendSource::Current) ||
                (stage.alphaSrc1 == BlendSource::Current &&
                 stage.alphaSrc2 == BlendSource::Texture));
    }

    bool IsSupportedTwoStageCombo(const LegacyPassDesc& desc) noexcept
    {
        if (desc.textureUnits != 2 || desc.stages.size() != 2)
        {
            return false;
        }
        const TextureStageDesc& s0 = desc.stages[0];
        const TextureStageDesc& s1 = desc.stages[1];
        if (!s0.known || !s1.known || s0.texCoordSet != 0 || s1.texCoordSet != 0)
        {
            return false;
        }
        if (!IsDefaultStageAlpha(s0) || !IsDefaultStageAlpha(s1))
        {
            return false;
        }
        if (ClassifyStageColour(s0) != StageCombine::Modulate)
        {
            return false;
        }
        return FixedFuncTextured2Fragment(ClassifyStageColour(s1)) != nullptr;
    }

    CompatConfig DefaultCompatConfig() noexcept
    {
        return CompatConfig{};
    }

    bool ParseCompatFlag(std::string_view raw, bool defaultValue) noexcept
    {
        const std::string_view text = TrimAscii(raw);
        if (text.empty())
        {
            return defaultValue;
        }
        std::string lower;
        lower.reserve(text.size());
        for (char c : text)
        {
            lower.push_back(ToLowerChar(c));
        }
        const std::string_view v(lower);
        if (v == "1" || v == "true" || v == "on" || v == "yes" || v == "enabled")
        {
            return true;
        }
        if (v == "0" || v == "false" || v == "off" || v == "no" || v == "disabled")
        {
            return false;
        }
        return defaultValue;
    }

    bool IsDx11SupportedShaderTarget(std::string_view target) noexcept
    {
        std::string lower;
        lower.reserve(target.size());
        for (char c : TrimAscii(target))
        {
            lower.push_back(ToLowerChar(c));
        }
        const std::string_view v(lower);
        if (v.empty())
        {
            return false;
        }
        if (v == "vs_4_0" || v == "ps_4_0" || v == "vs_5_0" || v == "ps_5_0" ||
            v == "vs_4_0_level_9_1" || v == "ps_4_0_level_9_1" ||
            v == "vs_4_0_level_9_3" || v == "ps_4_0_level_9_3")
        {
            return true;
        }
        // Ogre language names are never DX11 HLSL targets on their own; the
        // unified delegates resolve per-backend, so only explicit sm4/sm5
        // targets count here. glsl/glsles/cg/arbvp and sm1-sm3 are legacy.
        return false;
    }

    bool EqualsNoCase(std::string_view a, std::string_view b) noexcept
    {
        if (a.size() != b.size())
        {
            return false;
        }
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (ToLowerChar(a[i]) != ToLowerChar(b[i]))
            {
                return false;
            }
        }
        return true;
    }

    std::string ToLowerCopy(std::string_view text)
    {
        std::string out;
        out.reserve(text.size());
        for (char c : text)
        {
            out.push_back(ToLowerChar(c));
        }
        return out;
    }

    bool MapLegacyFamilyProgram(std::string_view legacyName,
                                std::string& outCompat)
    {
        outCompat.clear();
        const std::string lower = ToLowerCopy(TrimAscii(legacyName));
        if (lower.empty() || IsNativeProgramName(lower))
        {
            return false;
        }
        const char* vs = nullptr;
        const char* ps = nullptr;
        if (!LookupFamily(lower, vs, ps))
        {
            return false;
        }
        // Stage-aware: vertex-ish names map to the VS, everything else to PS.
        // Pixel/fragment aliases both resolve to the fragment adapter.
        if (ContainsLower(lower, "vertex") || ContainsLower(lower, "_vs") ||
            (ContainsLower(lower, "vs") && !ContainsLower(lower, "ps")))
        {
            // Prefer an explicit vertex hint; "vs" alone is ambiguous (it
            // appears in no other family infix), so treat bare-vs as vertex.
            if (ContainsLower(lower, "fragment") || ContainsLower(lower, "pixel") ||
                ContainsLower(lower, "ps") || ContainsLower(lower, "frag"))
            {
                // Name carries both hints (rare); fragment wins for safety
                // because over-eager vertex mapping would drop color ops.
                outCompat.assign(ps);
            }
            else
            {
                outCompat.assign(vs);
            }
        }
        else
        {
            outCompat.assign(ps);
        }
        return true;
    }

    bool IsKnownLegacyFamilyProgram(std::string_view legacyName) noexcept
    {
        const std::string lower = ToLowerCopy(TrimAscii(legacyName));
        if (lower.empty() || IsNativeProgramName(lower))
        {
            return false;
        }
        const char* vs = nullptr;
        const char* ps = nullptr;
        return LookupFamily(lower, vs, ps);
    }

    bool MapLegacyFamilyProgramForStage(std::string_view legacyName,
                                        bool wantVertex,
                                        std::string& outCompat)
    {
        outCompat.clear();
        const std::string lower = ToLowerCopy(TrimAscii(legacyName));
        if (lower.empty() || IsNativeProgramName(lower))
        {
            return false;
        }
        const char* vs = nullptr;
        const char* ps = nullptr;
        if (!LookupFamily(lower, vs, ps))
        {
            return false;
        }
        outCompat.assign(wantVertex ? vs : ps);
        return true;
    }

    bool IsExcludedFromSynthesis(std::string_view materialName,
                                 const LegacyPassDesc& desc) noexcept
    {
        // Screen-space and interface surfaces. These are drawn through paths
        // that assume their own material state, they are reached during
        // startup before the scene exists, and nothing in the Enhanced or
        // fixed-function ladder is meant for them.
        static constexpr const char* kExcluded[] = {
            "ui_", "/ui", "ui/", "uitexmat", "overlay", "cursor", "font",
            "hud", "minimap", "radar", "scope", "cockpit", "stdquad",
            "compositor", "rtt", "shadowcaster", "sprite",
        };

        auto hits = [](std::string_view text) noexcept {
            if (text.empty())
            {
                return false;
            }
            for (const char* needle : kExcluded)
            {
                if (ContainsLower(text, needle))
                {
                    return true;
                }
            }
            return false;
        };

        const std::string material = ToLowerCopy(TrimAscii(materialName));
        const std::string vs = ToLowerCopy(TrimAscii(desc.vertexProgram));
        const std::string ps = ToLowerCopy(TrimAscii(desc.fragmentProgram));
        return hits(material) || hits(vs) || hits(ps);
    }

    const char* FixedFuncTexturedVertex() noexcept
    {
        return "OSE_FixedFunc_Textured_vertex";
    }

    const char* FixedFuncTexturedFragment() noexcept
    {
        return "OSE_FixedFunc_Textured_fragment";
    }

    const char* FixedFuncUntexturedVertex() noexcept
    {
        return "OSE_FixedFunc_Untextured_vertex";
    }

    const char* FixedFuncUntexturedFragment() noexcept
    {
        return "OSE_FixedFunc_Untextured_fragment";
    }

    bool ResolveCompatPrograms(CompatPath path,
                               const LegacyPassDesc& desc,
                               std::string& outVertex,
                               std::string& outFragment)
    {
        outVertex.clear();
        outFragment.clear();

        // Texturing decides which fixed-function adapter fills a stage the
        // family table cannot. A true fixed-function pass reports its unit
        // count directly; a programmable pass that lost one stage keeps
        // whatever units it declared, so the same test holds for both.
        const bool textured = desc.textureUnits > 0;
        const char* const ffVertex = textured ? FixedFuncTexturedVertex()
                                              : FixedFuncUntexturedVertex();
        const char* const ffFragment = textured ? FixedFuncTexturedFragment()
                                                : FixedFuncUntexturedFragment();

        switch (path)
        {
        case CompatPath::FamilyRemap:
            // Own name first. Failing that, the other stage's name still
            // identifies the family, and the adapters are authored as pairs --
            // OSE_Compat_Effect_vertex belongs with OSE_Compat_Effect_fragment
            // far more than a generic fixed-function vertex does. Only when
            // neither stage names a known family does the generic adapter
            // stand in.
            if (!(desc.hasVertexRef &&
                  MapLegacyFamilyProgramForStage(desc.vertexProgram, true,
                                                 outVertex)) &&
                !(desc.hasFragmentRef &&
                  MapLegacyFamilyProgramForStage(desc.fragmentProgram, true,
                                                 outVertex)))
            {
                outVertex.assign(ffVertex);
            }
            if (!(desc.hasFragmentRef &&
                  MapLegacyFamilyProgramForStage(desc.fragmentProgram, false,
                                                 outFragment)) &&
                !(desc.hasVertexRef &&
                  MapLegacyFamilyProgramForStage(desc.vertexProgram, false,
                                                 outFragment)))
            {
                outFragment.assign(ffFragment);
            }
            return true;

        case CompatPath::FixedFuncTextured:
            outVertex.assign(FixedFuncTexturedVertex());
            outFragment.assign(FixedFuncTexturedFragment());
            return true;

        case CompatPath::FixedFuncUntextured:
            outVertex.assign(FixedFuncUntexturedVertex());
            outFragment.assign(FixedFuncUntexturedFragment());
            return true;

        case CompatPath::AggressiveGeneric:
            // Unknown custom semantics: the generic adapter is an explicit
            // approximation, so it follows the observed texturing rather than
            // any name.
            outVertex.assign(ffVertex);
            outFragment.assign(ffFragment);
            return true;

        case CompatPath::FixedFuncTextured2:
        {
            if (!IsSupportedTwoStageCombo(desc))
            {
                return false;
            }
            const char* fragment =
                FixedFuncTextured2Fragment(ClassifyStageColour(desc.stages[1]));
            outVertex.assign(FixedFuncTextured2Vertex());
            outFragment.assign(fragment);
            return true;
        }

        case CompatPath::SuppressPass:
            outVertex.assign(FixedFuncSuppressVertex());
            outFragment.assign(FixedFuncSuppressFragment());
            return true;

        case CompatPath::KeepNative:
        case CompatPath::SkipShaderless:
        default:
            return false;
        }
    }

    const char* FixedFuncTextured2Vertex() noexcept
    {
        return "OSE_FixedFunc_Textured2_vertex";
    }

    const char* FixedFuncTextured2Fragment(StageCombine stage1) noexcept
    {
        switch (stage1)
        {
        case StageCombine::Modulate: return "OSE_FixedFunc_Textured2_fragment_modulate";
        case StageCombine::Add: return "OSE_FixedFunc_Textured2_fragment_add";
        case StageCombine::AlphaBlendTexture: return "OSE_FixedFunc_Textured2_fragment_alphablend";
        case StageCombine::Replace:
        case StageCombine::Unsupported:
        default:
            // Replace on stage 1 discards stage 0 entirely; no shipped
            // material does it, so it stays out of the support set.
            return nullptr;
        }
    }

    const char* FixedFuncSuppressVertex() noexcept
    {
        return "OSE_FixedFunc_Suppress_vertex";
    }

    const char* FixedFuncSuppressFragment() noexcept
    {
        return "OSE_FixedFunc_Suppress_fragment";
    }

    namespace
    {
        constexpr NativeInputGuard kNativeInputGuards[] = {
            { "Glow/Null", "Untextured_vertex", "Untextured_fragment",
              "OSE_FixedFunc_Untextured_vertex_novc", "black-glow-mask" },
        };
    }

    size_t NativeInputGuardCount() noexcept
    {
        return sizeof(kNativeInputGuards) / sizeof(kNativeInputGuards[0]);
    }

    const NativeInputGuard* NativeInputGuardAt(size_t index) noexcept
    {
        return index < NativeInputGuardCount() ? &kNativeInputGuards[index]
                                               : nullptr;
    }

    const NativeInputGuard* FindNativeInputGuard(std::string_view material) noexcept
    {
        for (const NativeInputGuard& guard : kNativeInputGuards)
        {
            if (material == guard.material)
            {
                return &guard;
            }
        }
        return nullptr;
    }

    std::string FormatNativeInputGuardLog(const NativeInputGuard& guard,
                                          std::string_view action)
    {
        std::string act(action);
        if (act.empty())
        {
            act = "applied";
        }
        char buf[512] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s native-input-guard vs=%s -> %s reason=%s action=%s",
                      guard.material, guard.expectVertex, guard.replacementVertex,
                      guard.reason, act.c_str());
        return std::string(buf);
    }

    std::string FormatSuppressedLog(std::string_view material,
                                    std::string_view reason,
                                    const LegacyPassDesc& desc)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        std::string stages;
        for (const TextureStageDesc& s : desc.stages)
        {
            if (!stages.empty())
            {
                stages += ',';
            }
            if (!s.known)
            {
                stages += "unread";
                continue;
            }
            stages += StageCombineName(ClassifyStageColour(s));
            if (!IsDefaultStageAlpha(s))
            {
                stages += "+alpha";
            }
            if (s.texCoordSet != 0)
            {
                char uv[16] = {};
                std::snprintf(uv, sizeof(uv), "@uv%u", s.texCoordSet);
                stages += uv;
            }
        }
        if (stages.empty())
        {
            stages = "none";
        }
        std::string why(reason);
        if (why.empty())
        {
            why = "unsupported";
        }
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s path=suppress reason=%s passes=%d units=%d stages=%s action=skip-draw",
                      mat.c_str(), why.c_str(), desc.passCount,
                      desc.textureUnits, stages.c_str());
        return std::string(buf);
    }

    const char* VertexInputFitName(VertexInputFit fit) noexcept
    {
        switch (fit)
        {
        case VertexInputFit::Unchanged: return "unchanged";
        case VertexInputFit::Adapted: return "adapted";
        case VertexInputFit::Unsatisfiable: return "unsatisfiable";
        }
        return "unsatisfiable";
    }

    VertexInputFit FitVertexProgramToInputs(std::string_view resolvedVertex,
                                            const VertexInputs& inputs,
                                            std::string& outVertex)
    {
        outVertex.assign(resolvedVertex.data(), resolvedVertex.size());
        const std::string lower = ToLowerCopy(TrimAscii(resolvedVertex));
        // Only our own adapters have known input signatures. Anything else
        // (a native delegate, a future program) is left exactly as resolved.
        if (!StartsWithLower(lower, "ose_fixedfunc_") &&
            !StartsWithLower(lower, "ose_compat_"))
        {
            return VertexInputFit::Unchanged;
        }
        if (!inputs.position)
        {
            // Every variant reads POSITION; nothing can bind.
            outVertex.clear();
            return VertexInputFit::Unsatisfiable;
        }

        // Two entry points back every adapter (openshim_dx11_fixedfunc-sm4.hlsl):
        // fixedfunc_untextured_vertex reads POSITION+COLOR0, fixedfunc_vertex
        // reads POSITION+COLOR0+TEXCOORD0. The Untextured family is the only
        // one on the untextured entry; the family define is informational, so
        // an input-reduced generic variant is an exact stand-in.
        const bool untexturedEntry = ContainsLower(lower, "untextured");
        const bool diffuse = inputs.known && inputs.diffuse;
        const bool texcoord = !inputs.known || inputs.texcoord0;

        // The suppress pair reads POSITION only and binds on anything.
        if (StartsWithLower(lower, "ose_fixedfunc_suppress"))
        {
            return VertexInputFit::Unchanged;
        }
        // Two-stage entry: both stages sample UV set 0, so there is no
        // meaningful UV-less variant. Without TEXCOORD0 it cannot bind.
        if (StartsWithLower(lower, "ose_fixedfunc_textured2"))
        {
            if (!texcoord)
            {
                outVertex.clear();
                return VertexInputFit::Unsatisfiable;
            }
            if (diffuse)
            {
                return VertexInputFit::Unchanged;
            }
            outVertex.assign("OSE_FixedFunc_Textured2_vertex_novc");
            return VertexInputFit::Adapted;
        }

        const char* variant = nullptr;
        if (untexturedEntry)
        {
            if (diffuse)
            {
                return VertexInputFit::Unchanged;
            }
            variant = "OSE_FixedFunc_Untextured_vertex_novc";
        }
        else
        {
            if (diffuse && texcoord)
            {
                return VertexInputFit::Unchanged;
            }
            if (!diffuse && texcoord)
            {
                variant = "OSE_FixedFunc_Textured_vertex_novc";
            }
            else if (diffuse)
            {
                variant = "OSE_FixedFunc_Textured_vertex_nouv";
            }
            else
            {
                variant = "OSE_FixedFunc_Textured_vertex_novc_nouv";
            }
        }
        outVertex.assign(variant);
        return VertexInputFit::Adapted;
    }

    std::string DescribeVertexInputs(const VertexInputs& inputs)
    {
        if (!inputs.known)
        {
            return "unknown";
        }
        std::string out;
        auto add = [&out](bool present, const char* name) {
            if (!present)
            {
                return;
            }
            if (!out.empty())
            {
                out += ',';
            }
            out += name;
        };
        add(inputs.position, "position");
        add(inputs.diffuse, "diffuse");
        add(inputs.texcoord0, "texcoord0");
        return out.empty() ? std::string("none") : out;
    }

    LegacyPassKind ClassifyLegacyPass(const LegacyPassDesc& desc) noexcept
    {
        if (!desc.hasVertexRef && !desc.hasFragmentRef)
        {
            return LegacyPassKind::TrueFixedFunction;
        }

        // Any referenced stage with an unsupported (or missing) target, or a
        // known-legacy name, keeps the pass out of the native set. A missing
        // target on a referenced program is unsupported: DX11 needs both
        // stages bound with compilable targets.
        bool anyUnsupported = false;
        bool anyKnownFamily = false;

        // The runtime does not resolve targets, so a pass this layer already
        // converted (OSE_FixedFunc_*/OSE_Compat_*, all vs_4_0/ps_4_0) would
        // otherwise read as "unsupported custom" on the next scheme miss.
        auto ownProgram = [](const std::string& name, const std::string& target) {
            if (!target.empty())
            {
                return false;
            }
            const std::string lower = ToLowerCopy(TrimAscii(name));
            return StartsWithLower(lower, "ose_fixedfunc_") ||
                   StartsWithLower(lower, "ose_compat_");
        };

        if (desc.hasVertexRef)
        {
            const bool targetOk = IsDx11SupportedShaderTarget(desc.vertexTarget) ||
                                  ownProgram(desc.vertexProgram, desc.vertexTarget);
            std::string mapped;
            // Map check is case-insensitive and also verifies the name is
            // not already a native OSE_*/SM4 delegate.
            const bool known = IsKnownLegacyFamilyProgram(desc.vertexProgram);
            if (!targetOk || known)
            {
                anyUnsupported = true;
            }
            if (known)
            {
                anyKnownFamily = true;
            }
            (void)mapped;
        }
        if (desc.hasFragmentRef)
        {
            const bool targetOk = IsDx11SupportedShaderTarget(desc.fragmentTarget) ||
                                  ownProgram(desc.fragmentProgram, desc.fragmentTarget);
            const bool known = IsKnownLegacyFamilyProgram(desc.fragmentProgram);
            if (!targetOk || known)
            {
                anyUnsupported = true;
            }
            if (known)
            {
                anyKnownFamily = true;
            }
        }
        // Half-bound passes (one stage missing) are never native on D3D11:
        // the rendersystem throws without BOTH shaders.
        if (!desc.hasVertexRef || !desc.hasFragmentRef)
        {
            anyUnsupported = true;
        }

        if (!anyUnsupported)
        {
            return LegacyPassKind::NativeDx11;
        }
        if (anyKnownFamily)
        {
            return LegacyPassKind::KnownLegacyFamily;
        }
        return LegacyPassKind::UnknownCustom;
    }

    bool IsSupportedFixedFuncCombo(int textureUnits,
                                   std::string_view colorOp0) noexcept
    {
        if (textureUnits < 0)
        {
            return false;
        }
        if (textureUnits == 0)
        {
            return true;
        }
        if (textureUnits == 1)
        {
            const std::string lower = ToLowerCopy(TrimAscii(colorOp0));
            if (lower.empty() || lower == "modulate" || lower == "replace" ||
                lower == "add" || lower == "alpha_blend")
            {
                return true;
            }
            return false;
        }
        return false;
    }

    CompatPath DecideCompatPath(LegacyPassKind kind,
                                const LegacyPassDesc& desc,
                                const CompatConfig& config,
                                bool resourcesAvailable) noexcept
    {
        if (kind == LegacyPassKind::NativeDx11)
        {
            return CompatPath::KeepNative;
        }
        if (!resourcesAvailable)
        {
            return CompatPath::SkipShaderless;
        }
        switch (kind)
        {
        case LegacyPassKind::KnownLegacyFamily:
            return config.compatEnabled ? CompatPath::FamilyRemap
                                        : CompatPath::SkipShaderless;
        case LegacyPassKind::TrueFixedFunction:
            if (!config.compatEnabled)
            {
                return CompatPath::SkipShaderless;
            }
            // Synthesis retargets one-pass techniques only. A multi-pass
            // fixed-function technique is suppressed when that is the only
            // way to keep it from drawing shaderless.
            if (desc.passCount > 1)
            {
                return desc.fallbackShaderless ? CompatPath::SuppressPass
                                               : CompatPath::SkipShaderless;
            }
            if (desc.textureUnits <= 0)
            {
                return CompatPath::FixedFuncUntextured;
            }
            if (IsSupportedFixedFuncCombo(desc.textureUnits, desc.colorOp0))
            {
                return CompatPath::FixedFuncTextured;
            }
            if (IsSupportedTwoStageCombo(desc))
            {
                return CompatPath::FixedFuncTextured2;
            }
            // Unsupported combine: aggressive generic is the only
            // best-effort render left. Failing that, declining is only safe
            // when Ogre has a programmable technique to fall back to; if
            // every fallback is shaderless the draw must be suppressed, or
            // D3D11 throws on it every frame.
            if (config.aggressiveEnabled)
            {
                return CompatPath::AggressiveGeneric;
            }
            return desc.fallbackShaderless ? CompatPath::SuppressPass
                                           : CompatPath::SkipShaderless;
        case LegacyPassKind::UnknownCustom:
            return config.aggressiveEnabled ? CompatPath::AggressiveGeneric
                                            : CompatPath::SkipShaderless;
        case LegacyPassKind::NativeDx11:
        default:
            return CompatPath::KeepNative;
        }
    }

    size_t SelectSourceTechniqueIndex(
        const std::vector<TechniqueCandidate>& candidates,
        std::string_view requestedScheme,
        unsigned short requestedLod) noexcept
    {
        if (candidates.empty())
        {
            return kNoSourceTechnique;
        }
        const std::string reqLower = ToLowerCopy(requestedScheme);
        const std::string_view req(reqLower);

        auto schemeEquals = [](std::string_view a, std::string_view b) {
            if (a.size() != b.size())
            {
                return false;
            }
            for (size_t i = 0; i < a.size(); ++i)
            {
                char ca = (a[i] >= 'A' && a[i] <= 'Z') ? static_cast<char>(a[i] - 'A' + 'a') : a[i];
                char cb = (b[i] >= 'A' && b[i] <= 'Z') ? static_cast<char>(b[i] - 'A' + 'a') : b[i];
                if (ca != cb)
                {
                    return false;
                }
            }
            return true;
        };

        // 1. exact scheme + exact LOD (support ignored: semantic template).
        for (const auto& c : candidates)
        {
            if (schemeEquals(ToLowerCopy(c.scheme), req) && c.lod == requestedLod)
            {
                return c.index;
            }
        }
        // 2. exact scheme + closest LOD (lowest absolute distance, ties to
        //    the lower LOD which is the higher-detail fallback).
        {
            const TechniqueCandidate* best = nullptr;
            unsigned bestDist = 0xFFFFu;
            for (const auto& c : candidates)
            {
                if (!schemeEquals(ToLowerCopy(c.scheme), req))
                {
                    continue;
                }
                const unsigned dist = (c.lod > requestedLod)
                    ? static_cast<unsigned>(c.lod - requestedLod)
                    : static_cast<unsigned>(requestedLod - c.lod);
                if (best == nullptr || dist < bestDist ||
                    (dist == bestDist && c.lod < best->lod))
                {
                    best = &c;
                    bestDist = dist;
                }
            }
            if (best != nullptr)
            {
                return best->index;
            }
        }
        // 3. base/default/blank scheme + requested or closest LOD.
        {
            const TechniqueCandidate* exact = nullptr;
            const TechniqueCandidate* closest = nullptr;
            unsigned bestDist = 0xFFFFu;
            for (const auto& c : candidates)
            {
                const std::string lower = ToLowerCopy(c.scheme);
                const bool isBase = lower.empty() || lower == "default" || lower == "base";
                if (!isBase)
                {
                    continue;
                }
                if (c.lod == requestedLod && exact == nullptr)
                {
                    exact = &c;
                }
                const unsigned dist = (c.lod > requestedLod)
                    ? static_cast<unsigned>(c.lod - requestedLod)
                    : static_cast<unsigned>(requestedLod - c.lod);
                if (closest == nullptr || dist < bestDist ||
                    (dist == bestDist && c.lod < closest->lod))
                {
                    closest = &c;
                    bestDist = dist;
                }
            }
            if (exact != nullptr)
            {
                return exact->index;
            }
            if (closest != nullptr)
            {
                return closest->index;
            }
        }
        // 4. first technique as the last semantic template.
        return candidates.front().index;
    }

    std::string BuildCompatCacheKey(std::string_view material,
                                    std::string_view requestedScheme,
                                    unsigned short lodIndex,
                                    size_t sourceTechnique,
                                    std::string_view variant)
    {
        std::string key;
        key.reserve(material.size() + requestedScheme.size() + variant.size() + 32);
        auto appendSanitized = [&key](std::string_view text) {
            for (char c : text)
            {
                key += SanitizeKeyChar(c);
            }
        };
        appendSanitized(TrimAscii(material));
        key += '|';
        appendSanitized(TrimAscii(requestedScheme));
        key += '|';
        char lodBuf[16] = {};
        std::snprintf(lodBuf, sizeof(lodBuf), "%u", static_cast<unsigned>(lodIndex));
        key += lodBuf;
        key += '|';
        char srcBuf[32] = {};
        std::snprintf(srcBuf, sizeof(srcBuf), "%zu", sourceTechnique);
        key += srcBuf;
        key += '|';
        appendSanitized(TrimAscii(variant));
        return key;
    }

    std::string FormatCompatAppliedLog(std::string_view material,
                                       std::string_view source,
                                       CompatPath path,
                                       bool cached)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        std::string src(source);
        if (src.empty())
        {
            src = "default/0";
        }
        char buf[512] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s source=%s path=%s cached=%d",
                      mat.c_str(), src.c_str(), CompatPathName(path),
                      cached ? 1 : 0);
        return std::string(buf);
    }

    std::string FormatFamilyRemapLog(std::string_view material,
                                     std::string_view family,
                                     std::string_view fromVs,
                                     std::string_view fromPs)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        std::string fam(family);
        if (fam.empty())
        {
            fam = "legacy";
        }
        std::string vs(fromVs);
        if (vs.empty())
        {
            vs = "<none>";
        }
        std::string ps(fromPs);
        if (ps.empty())
        {
            ps = "<none>";
        }
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s path=family-remap family=%s vs=%s ps=%s",
                      mat.c_str(), fam.c_str(), vs.c_str(), ps.c_str());
        return std::string(buf);
    }

    std::string FormatUnsupportedLog(std::string_view material,
                                     std::string_view vsName,
                                     std::string_view psName,
                                     bool aggressiveAvailable)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        std::string vs(vsName);
        if (vs.empty())
        {
            vs = "<none>";
        }
        std::string ps(psName);
        if (ps.empty())
        {
            ps = "<none>";
        }
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s unsupported custom programs vs=%s ps=%s action=%s",
                      mat.c_str(), vs.c_str(), ps.c_str(),
                      aggressiveAvailable ? "aggressive-fallback" : "skip");
        return std::string(buf);
    }

    std::string FormatShaderlessSkippedLog(std::string_view material,
                                           unsigned technique,
                                           unsigned pass,
                                           std::string_view vsName,
                                           std::string_view psName)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        std::string vs(vsName);
        if (vs.empty())
        {
            vs = "<none>";
        }
        std::string ps(psName);
        if (ps.empty())
        {
            ps = "<none>";
        }
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] skipped shaderless draw material=%s technique=%u pass=%u vs=%s ps=%s",
                      mat.c_str(), technique, pass, vs.c_str(), ps.c_str());
        return std::string(buf);
    }

    std::string FormatRtssUnavailableLog(std::string_view material)
    {
        std::string mat(material);
        if (mat.empty())
        {
            mat = "<unknown>";
        }
        char buf[384] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] material=%s rtss=generator-unavailable action=skip",
                      mat.c_str());
        return std::string(buf);
    }

    std::string FormatCompatSummary(const CompatCounters& counters)
    {
        char buf[512] = {};
        std::snprintf(buf, sizeof(buf),
                      "[DX11COMPAT] summary native=%llu family=%llu fixedfunc=%llu rtss=%llu aggressive=%llu unsupported=%llu skipped=%llu instantiated=%llu instantiate-failed=%llu",
                      static_cast<unsigned long long>(counters.nativeSupported),
                      static_cast<unsigned long long>(counters.familyRemaps),
                      static_cast<unsigned long long>(counters.fixedFuncGenerated),
                      static_cast<unsigned long long>(counters.rtssGenerated),
                      static_cast<unsigned long long>(counters.aggressiveFallbacks),
                      static_cast<unsigned long long>(counters.unsupportedCustom),
                      static_cast<unsigned long long>(counters.shaderlessSkipped),
                      static_cast<unsigned long long>(counters.techniquesInstantiated),
                      static_cast<unsigned long long>(counters.instantiationFailures));
        return std::string(buf);
    }
} // namespace BZROpenShim::RenderProfiles::Dx11Compat
