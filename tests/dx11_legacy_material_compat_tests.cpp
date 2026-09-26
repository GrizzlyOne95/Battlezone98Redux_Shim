// DX11 legacy material compatibility policy tests. Pure logic: no engine,
// no game. Build+run via scripts/run_render_profile_tests.ps1 and CTest.

#include "dx11_legacy_material_compat.h"

#include <cstdio>
#include <cstring>
#include <string>

using namespace BZROpenShim::RenderProfiles::Dx11Compat;

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }

    void ExpectContains(const std::string& haystack, const char* needle,
                        const char* what)
    {
        if (haystack.find(needle) == std::string::npos)
        {
            std::printf("  FAIL: %s ('%s' missing '%s')\n", what,
                        haystack.c_str(), needle);
            ++g_failures;
        }
    }

    LegacyPassDesc FixedFuncDesc(int units, const char* op = "modulate")
    {
        LegacyPassDesc d;
        d.textureUnits = units;
        d.colorOp0 = (op != nullptr) ? op : "";
        return d;
    }

    LegacyPassDesc ProgramDesc(const char* vs, const char* vsTarget,
                               const char* ps, const char* psTarget)
    {
        LegacyPassDesc d;
        if (vs != nullptr)
        {
            d.hasVertexRef = true;
            d.vertexProgram = vs;
            d.vertexTarget = (vsTarget != nullptr) ? vsTarget : "";
        }
        if (ps != nullptr)
        {
            d.hasFragmentRef = true;
            d.fragmentProgram = ps;
            d.fragmentTarget = (psTarget != nullptr) ? psTarget : "";
        }
        return d;
    }
}

void TestSupportedTargets()
{
    std::printf("TestSupportedTargets\n");
    ExpectTrue(IsDx11SupportedShaderTarget("vs_4_0"), "vs_4_0 supported");
    ExpectTrue(IsDx11SupportedShaderTarget("ps_4_0"), "ps_4_0 supported");
    ExpectTrue(IsDx11SupportedShaderTarget("vs_5_0"), "vs_5_0 supported");
    ExpectTrue(IsDx11SupportedShaderTarget("ps_5_0"), "ps_5_0 supported");
    ExpectTrue(IsDx11SupportedShaderTarget("VS_4_0"), "case-insensitive");
    ExpectTrue(IsDx11SupportedShaderTarget("vs_4_0_level_9_1"), "fl9.1 vs");
    ExpectTrue(IsDx11SupportedShaderTarget("ps_4_0_level_9_3"), "fl9.3 ps");
    ExpectTrue(!IsDx11SupportedShaderTarget("vs_3_0"), "vs_3_0 legacy");
    ExpectTrue(!IsDx11SupportedShaderTarget("ps_3_0"), "ps_3_0 legacy");
    ExpectTrue(!IsDx11SupportedShaderTarget("vs_2_0"), "vs_2_0 legacy");
    ExpectTrue(!IsDx11SupportedShaderTarget("arbvp1"), "arbvp legacy");
    ExpectTrue(!IsDx11SupportedShaderTarget("cg"), "cg legacy");
    ExpectTrue(!IsDx11SupportedShaderTarget(""), "empty unsupported");
    ExpectTrue(!IsDx11SupportedShaderTarget("glsl"), "glsl not an HLSL target");
}

void TestParseCompatFlag()
{
    std::printf("TestParseCompatFlag\n");
    ExpectTrue(ParseCompatFlag("1", false), "1 true");
    ExpectTrue(ParseCompatFlag("true", false), "true");
    ExpectTrue(ParseCompatFlag("ON", false), "on case-insensitive");
    ExpectTrue(ParseCompatFlag(" yes ", false), "trimmed yes");
    ExpectTrue(ParseCompatFlag("enabled", false), "enabled");
    ExpectTrue(!ParseCompatFlag("0", true), "0 false");
    ExpectTrue(!ParseCompatFlag("off", true), "off");
    ExpectTrue(!ParseCompatFlag("No", true), "no");
    ExpectTrue(!ParseCompatFlag("disabled", true), "disabled");
    ExpectTrue(ParseCompatFlag("bogus", true), "unknown keeps true default");
    ExpectTrue(!ParseCompatFlag("bogus", false), "unknown keeps false default");
    ExpectTrue(ParseCompatFlag("", true), "empty keeps default");
    const CompatConfig defaults = DefaultCompatConfig();
    ExpectTrue(defaults.compatEnabled, "compat default on");
    ExpectTrue(defaults.guardEnabled, "guard default on");
    ExpectTrue(!defaults.aggressiveEnabled, "aggressive default off");
}

void TestFamilyMapping()
{
    std::printf("TestFamilyMapping\n");
    std::string out;
    ExpectTrue(MapLegacyFamilyProgram("Effect_vertexHLSL", out) &&
                   out == "OSE_Compat_Effect_vertex",
               "effect vs maps");
    ExpectTrue(MapLegacyFamilyProgram("Effect_fragmentHLSL", out) &&
                   out == "OSE_Compat_Effect_fragment",
               "effect ps maps");
    ExpectTrue(MapLegacyFamilyProgram("TEXTURED_VERTEXHLSL", out) &&
                   out == "OSE_Compat_Textured_vertex",
               "case-insensitive textured vs");
    ExpectTrue(MapLegacyFamilyProgram("untextured_fragmenthlsl", out) &&
                   out == "OSE_Compat_Untextured_fragment",
               "untextured ps maps");
    ExpectTrue(MapLegacyFamilyProgram("Sky_vertexHLSL", out) &&
                   out == "OSE_Compat_Sky_vertex",
               "sky vs maps");
    ExpectTrue(MapLegacyFamilyProgram("simple_one_tex_fragmentHLSL", out) &&
                   out == "OSE_Compat_SimpleOneTex_fragment",
               "simple_one_tex ps maps");
    ExpectTrue(MapLegacyFamilyProgram("UI_vertexHLSL", out) &&
                   out == "OSE_Compat_Ui_vertex",
               "ui vs maps");
    ExpectTrue(MapLegacyFamilyProgram("Base_pixelHLSL", out) &&
                   out == "OSE_Compat_Base_fragment",
               "base pixel alias maps to fragment");
    ExpectTrue(IsKnownLegacyFamilyProgram("Effect_vertexHLSL"),
               "known family recognized");
    ExpectTrue(!IsKnownLegacyFamilyProgram("ModWaterVS"),
               "unknown custom not known");
    // Native delegates must never remap: they are already DX11-usable.
    ExpectTrue(!MapLegacyFamilyProgram("OSE_Compat_Effect_vertex", out),
               "own compat output not remapped");
    ExpectTrue(!MapLegacyFamilyProgram("OSE_BaseHighNoShadow_vertexHLSL4", out),
               "native HLSL4 not remapped");
    ExpectTrue(!MapLegacyFamilyProgram("ModWaterVS", out),
               "unknown custom not remapped");
    ExpectTrue(!MapLegacyFamilyProgram("", out), "empty not remapped");
}

void TestClassification()
{
    std::printf("TestClassification\n");
    ExpectTrue(ClassifyLegacyPass(FixedFuncDesc(0)) ==
                   LegacyPassKind::TrueFixedFunction,
               "no programs is fixed function");
    ExpectTrue(ClassifyLegacyPass(FixedFuncDesc(1)) ==
                   LegacyPassKind::TrueFixedFunction,
               "texture state alone is still fixed function");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("Effect_vertexHLSL", "vs_3_0",
                                              "Effect_fragmentHLSL",
                                              "ps_3_0")) ==
                   LegacyPassKind::KnownLegacyFamily,
               "sm3 effect family classifies as known");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("Effect_vertexHLSL", "",
                                              "Effect_fragmentHLSL", "")) ==
                   LegacyPassKind::KnownLegacyFamily,
               "known names classify even without targets");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("ModWaterVS", "vs_3_0",
                                              "ModWaterPS", "ps_3_0")) ==
                   LegacyPassKind::UnknownCustom,
               "unknown sm3 classifies custom");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("OSE_BaseHighNoShadow_vertexHLSL4",
                                              "vs_4_0",
                                              "OSE_BaseHighNoShadow_fragmentHLSL4",
                                              "ps_4_0")) ==
                   LegacyPassKind::NativeDx11,
               "sm4 native classifies native");
    // Half-bound passes are never native on D3D11 (needs BOTH shaders).
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("Effect_vertexHLSL", "vs_3_0",
                                              nullptr, nullptr)) !=
                   LegacyPassKind::NativeDx11,
               "vertex-only is not native");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("ModWaterVS", "vs_3_0", nullptr,
                                              nullptr)) ==
                   LegacyPassKind::UnknownCustom,
               "single unknown stage is custom");
}

void TestFixedFuncSupport()
{
    std::printf("TestFixedFuncSupport\n");
    ExpectTrue(IsSupportedFixedFuncCombo(0, ""), "0 units always");
    ExpectTrue(IsSupportedFixedFuncCombo(0, "weird"), "0 units ignores op");
    ExpectTrue(IsSupportedFixedFuncCombo(1, "modulate"), "modulate");
    ExpectTrue(IsSupportedFixedFuncCombo(1, "MODULATE"), "case-insensitive");
    ExpectTrue(IsSupportedFixedFuncCombo(1, "replace"), "replace");
    ExpectTrue(IsSupportedFixedFuncCombo(1, "add"), "add");
    ExpectTrue(IsSupportedFixedFuncCombo(1, "alpha_blend"), "alpha_blend");
    ExpectTrue(IsSupportedFixedFuncCombo(1, ""), "empty op defaults");
    ExpectTrue(!IsSupportedFixedFuncCombo(1, "dotproduct"),
               "exotic combine unsupported");
    ExpectTrue(!IsSupportedFixedFuncCombo(2, "modulate"), "multi-texture out");
    ExpectTrue(!IsSupportedFixedFuncCombo(-1, ""), "negative rejected");
}

void TestDecidePaths()
{
    std::printf("TestDecidePaths\n");
    CompatConfig on;
    on.compatEnabled = true;
    on.guardEnabled = true;
    on.aggressiveEnabled = false;

    LegacyPassDesc native;
    native.hasVertexRef = true;
    native.hasFragmentRef = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::NativeDx11, native, on) ==
                   CompatPath::KeepNative,
               "native keeps native");

    LegacyPassDesc prog;
    prog.hasVertexRef = true;
    prog.hasFragmentRef = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::KnownLegacyFamily, prog, on) ==
                   CompatPath::FamilyRemap,
               "known family remaps when enabled");
    CompatConfig off = on;
    off.compatEnabled = false;
    ExpectTrue(DecideCompatPath(LegacyPassKind::KnownLegacyFamily, prog, off) ==
                   CompatPath::SkipShaderless,
               "known family skips when compat off");

    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction,
                                FixedFuncDesc(0), on) ==
                   CompatPath::FixedFuncUntextured,
               "0 units untextured");
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction,
                                FixedFuncDesc(1, "modulate"), on) ==
                   CompatPath::FixedFuncTextured,
               "1 unit modulate textured");
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction,
                                FixedFuncDesc(2, "modulate"), on) ==
                   CompatPath::SkipShaderless,
               "multi-texture skips without aggressive");
    CompatConfig aggro = on;
    aggro.aggressiveEnabled = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction,
                                FixedFuncDesc(2, "modulate"), aggro) ==
                   CompatPath::AggressiveGeneric,
               "multi-texture aggressive fallback");
    ExpectTrue(DecideCompatPath(LegacyPassKind::UnknownCustom, prog, on) ==
                   CompatPath::SkipShaderless,
               "unknown skips by default");
    ExpectTrue(DecideCompatPath(LegacyPassKind::UnknownCustom, prog, aggro) ==
                   CompatPath::AggressiveGeneric,
               "unknown aggressive fallback when enabled");
    // Missing resources fail closed for every non-native pass.
    ExpectTrue(DecideCompatPath(LegacyPassKind::KnownLegacyFamily, prog, aggro,
                                false) == CompatPath::SkipShaderless,
               "no resources fails closed");
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction,
                                FixedFuncDesc(0), aggro,
                                false) == CompatPath::SkipShaderless,
               "fixedfunc without resources fails closed");
    ExpectTrue(DecideCompatPath(LegacyPassKind::NativeDx11, native, aggro,
                                false) == CompatPath::KeepNative,
               "native unaffected by missing resources");
}

void TestSourceSelection()
{
    std::printf("TestSourceSelection\n");
    ExpectTrue(SelectSourceTechniqueIndex({}, "high-pssm", 0) ==
                   kNoSourceTechnique,
               "empty has no source");
    const std::vector<TechniqueCandidate> candidates = {
        { "high-pssm", 0, 0, false },
        { "high-pssm", 1, 1, false },
        { "", 0, 2, false },
        { "default", 0, 3, false },
    };
    ExpectTrue(SelectSourceTechniqueIndex(candidates, "high-pssm", 0) == 0,
               "exact scheme+lod wins");
    ExpectTrue(SelectSourceTechniqueIndex(candidates, "high-pssm", 3) == 1,
               "exact scheme closest lod wins");
    ExpectTrue(SelectSourceTechniqueIndex(candidates, "medium", 0) == 2,
               "blank scheme fallback");
    const std::vector<TechniqueCandidate> onlyForeign = {
        { "weird-scheme", 5, 7, false },
    };
    ExpectTrue(SelectSourceTechniqueIndex(onlyForeign, "high-pssm", 0) == 7,
               "first technique as last resort");
}

void TestCacheKeys()
{
    std::printf("TestCacheKeys\n");
    const std::string a =
        BuildCompatCacheKey("xrain", "high-pssm", 0, 0, "fixedfunc-textured");
    const std::string b =
        BuildCompatCacheKey("xrain", "high-pssm", 0, 0, "fixedfunc-textured");
    ExpectTrue(a == b, "keys stable");
    ExpectTrue(a != BuildCompatCacheKey("xrain", "high-pssm", 0, 0,
                                        "fixedfunc-untextured"),
               "variant distinguishes keys");
    ExpectTrue(a != BuildCompatCacheKey("White_Clouds", "high-pssm", 0, 0,
                                        "fixedfunc-textured"),
               "material distinguishes keys");
    ExpectTrue(a.find("xrain") != std::string::npos, "material survives");
    const std::string weird =
        BuildCompatCacheKey("a/b c", "s", 0, 0, "v");
    ExpectTrue(weird.find('/') == std::string::npos &&
                   weird.find(' ') == std::string::npos,
               "keys sanitized");
}

void TestLogFormats()
{
    std::printf("TestLogFormats\n");
    ExpectContains(FormatCompatAppliedLog("xrain", "default/0",
                                          CompatPath::FixedFuncTextured, true),
                   "[DX11COMPAT]", "applied tag");
    ExpectContains(FormatCompatAppliedLog("xrain", "default/0",
                                          CompatPath::FixedFuncTextured, true),
                   "xrain", "applied names material");
    ExpectContains(FormatCompatAppliedLog("", "", CompatPath::SkipShaderless,
                                          false),
                   "<unknown>", "empty material placeholder");
    ExpectContains(
        FormatFamilyRemapLog("White_Clouds", "Effect", "Effect_vertexHLSL",
                             "Effect_fragmentHLSL"),
        "family-remap", "remap names path");
    ExpectContains(FormatUnsupportedLog("FancyWater", "ModWaterVS",
                                        "ModWaterPS", false),
                   "action=skip", "unsupported default skips");
    ExpectContains(FormatUnsupportedLog("FancyWater", "ModWaterVS",
                                        "ModWaterPS", true),
                   "aggressive-fallback", "aggressive action named");
    ExpectContains(
        FormatShaderlessSkippedLog("xrain", 0, 0, "", ""), "<none>",
        "missing programs render as <none>");
    ExpectContains(FormatRtssUnavailableLog("xrain"), "rtss=",
                   "rtss unavailable named");
    const CompatCounters counters{};
    ExpectContains(FormatCompatSummary(counters), "summary",
                   "summary tagged");
}

void TestStageMapping()
{
    std::printf("TestStageMapping\n");
    std::string out;

    // The heuristic form reads the stage out of the name; the stage-explicit
    // form ignores the name entirely. Both agree when the name is explicit.
    ExpectTrue(MapLegacyFamilyProgramForStage("Effect_vertexHLSL", true, out) &&
                   out == "OSE_Compat_Effect_vertex",
               "explicit vertex stage");
    ExpectTrue(MapLegacyFamilyProgramForStage("Effect_fragmentHLSL", false,
                                              out) &&
                   out == "OSE_Compat_Effect_fragment",
               "explicit fragment stage");

    // The point of the stage-explicit form: a name carrying one stage still
    // answers for the other. ResolveCompatPrograms relies on this to pair a
    // missing stage off the family the surviving stage names.
    ExpectTrue(MapLegacyFamilyProgramForStage("Effect_fragmentHLSL", true,
                                              out) &&
                   out == "OSE_Compat_Effect_vertex",
               "asked stage beats the spelled stage");
    ExpectTrue(MapLegacyFamilyProgramForStage("Sky_vertexHLSL", false, out) &&
                   out == "OSE_Compat_Sky_fragment",
               "vertex-spelled name answers for fragment");

    // A family name with no stage hint at all stays refused in both forms.
    // The table declines to guess rather than binding a coin-flip adapter.
    ExpectTrue(!MapLegacyFamilyProgram("simple_one_tex", out),
               "unhinted family name is refused by the heuristic form");
    ExpectTrue(!MapLegacyFamilyProgramForStage("simple_one_tex", true, out),
               "unhinted family name is refused stage-explicitly too");

    ExpectTrue(!MapLegacyFamilyProgramForStage("ModWaterVS", true, out) &&
                   out.empty(),
               "unknown family resolves no stage");
    ExpectTrue(!MapLegacyFamilyProgramForStage("", false, out),
               "empty name resolves no stage");
}

void TestResolveCompatPrograms()
{
    std::printf("TestResolveCompatPrograms\n");
    std::string vs;
    std::string ps;

    // Paths that synthesize nothing must refuse, so the runtime never
    // mutates a material it had no plan for.
    ExpectTrue(!ResolveCompatPrograms(CompatPath::KeepNative,
                                      ProgramDesc("A", "vs_4_0", "B", "ps_4_0"),
                                      vs, ps),
               "KeepNative resolves nothing");
    ExpectTrue(!ResolveCompatPrograms(CompatPath::SkipShaderless,
                                      FixedFuncDesc(1), vs, ps),
               "SkipShaderless resolves nothing");

    // Both stages remapped from the family table.
    LegacyPassDesc effect =
        ProgramDesc("Effect_vertexHLSL", "vs_3_0", "Effect_fragmentHLSL",
                    "ps_3_0");
    effect.textureUnits = 1;
    ExpectTrue(ResolveCompatPrograms(CompatPath::FamilyRemap, effect, vs, ps) &&
                   vs == "OSE_Compat_Effect_vertex" &&
                   ps == "OSE_Compat_Effect_fragment",
               "family remap fills both stages");

    // Half a remap is the failure this exists to prevent: a pass with only a
    // fragment reference still has to come back with a vertex program bound,
    // and it should be the one authored to pair with that fragment adapter.
    LegacyPassDesc psOnly = ProgramDesc(nullptr, nullptr, "Effect_fragmentHLSL",
                                        "ps_3_0");
    psOnly.textureUnits = 1;
    ExpectTrue(ResolveCompatPrograms(CompatPath::FamilyRemap, psOnly, vs, ps) &&
                   vs == "OSE_Compat_Effect_vertex" &&
                   ps == "OSE_Compat_Effect_fragment",
               "missing vertex stage pairs off the fragment's family");

    // An unknown name on one stage is the same hole, reached differently.
    LegacyPassDesc mixed =
        ProgramDesc("ModWaterVS", "vs_3_0", "Effect_fragmentHLSL", "ps_3_0");
    ExpectTrue(ResolveCompatPrograms(CompatPath::FamilyRemap, mixed, vs, ps) &&
                   vs == "OSE_Compat_Effect_vertex" &&
                   ps == "OSE_Compat_Effect_fragment",
               "unmappable vertex stage pairs off the fragment's family");

    // Only when neither stage names a family does the generic adapter stand
    // in, and then texturing picks which one.
    LegacyPassDesc unknownBoth =
        ProgramDesc("ModWaterVS", "vs_3_0", "ModWaterPS", "ps_3_0");
    unknownBoth.textureUnits = 1;
    ExpectTrue(ResolveCompatPrograms(CompatPath::FamilyRemap, unknownBoth, vs,
                                     ps) &&
                   vs == "OSE_FixedFunc_Textured_vertex" &&
                   ps == "OSE_FixedFunc_Textured_fragment",
               "no family on either stage falls back on texturing");

    ExpectTrue(ResolveCompatPrograms(CompatPath::FixedFuncTextured,
                                     FixedFuncDesc(1), vs, ps) &&
                   vs == "OSE_FixedFunc_Textured_vertex" &&
                   ps == "OSE_FixedFunc_Textured_fragment",
               "textured fixed function pair");
    ExpectTrue(ResolveCompatPrograms(CompatPath::FixedFuncUntextured,
                                     FixedFuncDesc(0), vs, ps) &&
                   vs == "OSE_FixedFunc_Untextured_vertex" &&
                   ps == "OSE_FixedFunc_Untextured_fragment",
               "untextured fixed function pair");

    ExpectTrue(ResolveCompatPrograms(CompatPath::AggressiveGeneric,
                                     FixedFuncDesc(2), vs, ps) &&
                   vs == "OSE_FixedFunc_Textured_vertex" &&
                   ps == "OSE_FixedFunc_Textured_fragment",
               "aggressive generic follows texturing");
}

void TestSynthesisExclusions()
{
    std::printf("TestSynthesisExclusions\n");

    // The exact shape that took the process down on 2026-09-19: a UI family
    // reached through the en-high-pssm scheme miss. Either the material name
    // or the program name must be enough to refuse it.
    LegacyPassDesc ui = ProgramDesc("UI_vertex", "vs_3_0", "UI_fragment",
                                    "ps_3_0");
    ExpectTrue(IsExcludedFromSynthesis("SomeMenuThing", ui),
               "UI program family is excluded on program name alone");
    ExpectTrue(IsExcludedFromSynthesis("UI_Background", FixedFuncDesc(1)),
               "UI material name is excluded on name alone");

    ExpectTrue(IsExcludedFromSynthesis("overlay_frame", FixedFuncDesc(1)),
               "overlays excluded");
    ExpectTrue(IsExcludedFromSynthesis("bzfont", FixedFuncDesc(1)),
               "font surfaces excluded");
    ExpectTrue(IsExcludedFromSynthesis("avtank_cockpit", FixedFuncDesc(1)),
               "cockpit excluded");
    ExpectTrue(IsExcludedFromSynthesis("Scope_overlay", FixedFuncDesc(1)),
               "scope excluded");
    ExpectTrue(IsExcludedFromSynthesis("Ogre/Compositor/StdQuad",
                                       FixedFuncDesc(0)),
               "compositor quad excluded");
    ExpectTrue(IsExcludedFromSynthesis("sprites", FixedFuncDesc(1)),
               "sprite sheets excluded");

    // Ordinary scene content must still be eligible, or the exclusion would
    // quietly disable the whole feature.
    LegacyPassDesc tank = ProgramDesc("BaseHighPSSM_vertex", "vs_3_0",
                                      "BaseHighPSSM_fragment", "ps_3_0");
    ExpectTrue(!IsExcludedFromSynthesis("avltnk00", tank),
               "a vehicle material is eligible");
    ExpectTrue(!IsExcludedFromSynthesis("abstor", tank),
               "a building material is eligible");
    LegacyPassDesc terrain = ProgramDesc("TerrainHighPSSM_vertex", "vs_3_0",
                                         "TerrainHighPSSM_fragment", "ps_3_0");
    ExpectTrue(!IsExcludedFromSynthesis("MN_DETAIL_ATLAS", terrain),
               "a terrain atlas is eligible");
    ExpectTrue(!IsExcludedFromSynthesis("", FixedFuncDesc(0)),
               "an empty name is not excluded here (the caller rejects it)");
}

std::string ReadTextFile(const char* path)
{
    std::string text;
    std::FILE* f = std::fopen(path, "rb");
    if (f == nullptr)
    {
        return text;
    }
    char buf[4096];
    size_t n = 0;
    while ((n = std::fread(buf, 1, sizeof(buf), f)) > 0)
    {
        text.append(buf, n);
    }
    std::fclose(f);
    return text;
}

// The block of a "vertex_program <name> hlsl" declaration, or "" if absent.
std::string ProgramBlock(const std::string& script, const std::string& name)
{
    const std::string header = "vertex_program " + name + " hlsl";
    size_t at = 0;
    while ((at = script.find(header, at)) != std::string::npos)
    {
        const size_t after = at + header.size();
        // Reject a longer name that merely starts with this one.
        if (after < script.size() && script[after] != '\r' &&
            script[after] != '\n' && script[after] != ' ')
        {
            at = after;
            continue;
        }
        const size_t close = script.find("\n}", after);
        return script.substr(at, close == std::string::npos
                                     ? std::string::npos
                                     : close - at);
    }
    return std::string();
}

void TestVertexInputFit()
{
    std::printf("TestVertexInputFit\n");
    std::string vs;

    // ISDF Chronicles prop.mesh: POSITION/NORMAL/TANGENT/TEXCOORD0, no
    // DIFFUSE. The full-input program made D3D11 throw per draw; this is
    // the exact case that quit isdfms10 under DX11.
    VertexInputs noColour;
    noColour.known = true;
    noColour.position = true;
    noColour.diffuse = false;
    noColour.texcoord0 = true;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex",
                                        noColour, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_novc",
               "textured fixed function on a mesh without DIFFUSE drops COLOR0");
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Untextured_vertex",
                                        noColour, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Untextured_vertex_novc",
               "untextured fixed function on a mesh without DIFFUSE drops COLOR0");
    // Family adapters share the entry points, so they take the same variant.
    ExpectTrue(FitVertexProgramToInputs("OSE_Compat_Effect_vertex", noColour,
                                        vs) == VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_novc",
               "a textured-entry family adapter adapts to the generic variant");
    ExpectTrue(FitVertexProgramToInputs("OSE_Compat_Untextured_vertex",
                                        noColour, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Untextured_vertex_novc",
               "the untextured family keeps the untextured entry");

    // Native BZR geometry (mire foliage: POSITION/NORMAL/DIFFUSE/TEXCOORD0)
    // keeps the program that was resolved, family name and all.
    VertexInputs full;
    full.known = true;
    full.diffuse = true;
    full.texcoord0 = true;
    ExpectTrue(FitVertexProgramToInputs("OSE_Compat_Effect_vertex", full, vs) ==
                       VertexInputFit::Unchanged &&
                   vs == "OSE_Compat_Effect_vertex",
               "a mesh with every input keeps the resolved program");
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Untextured_vertex",
                                        full, vs) == VertexInputFit::Unchanged &&
                   vs == "OSE_FixedFunc_Untextured_vertex",
               "untextured with DIFFUSE is unchanged");

    VertexInputs noUv = full;
    noUv.texcoord0 = false;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex", noUv,
                                        vs) == VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_nouv",
               "textured program on a mesh without TEXCOORD0 drops the UV input");
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Untextured_vertex",
                                        noUv, vs) == VertexInputFit::Unchanged,
               "the untextured entry never needed TEXCOORD0");
    VertexInputs bare;
    bare.known = true;
    bare.diffuse = false;
    bare.texcoord0 = false;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex", bare,
                                        vs) == VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_novc_nouv",
               "position-only mesh gets the position-only textured variant");

    VertexInputs noPosition = full;
    noPosition.position = false;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex",
                                        noPosition, vs) ==
                       VertexInputFit::Unsatisfiable && vs.empty(),
               "no POSITION is unsatisfiable and fails closed");

    // Unknown declaration: never require COLOR0 (fatal if absent), keep UVs.
    VertexInputs unknown;
    ExpectTrue(!unknown.known, "default VertexInputs is unknown");
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex",
                                        unknown, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_novc",
               "unknown inputs take the no-colour variant");
    unknown.diffuse = true; // ignored while known == false
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured_vertex",
                                        unknown, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured_vertex_novc",
               "an unverified diffuse flag is not trusted");

    // Programs this layer does not own are never touched.
    ExpectTrue(FitVertexProgramToInputs("BaseHighPSSM_vertexSM4", noColour,
                                        vs) == VertexInputFit::Unchanged &&
                   vs == "BaseHighPSSM_vertexSM4",
               "foreign programs are left alone");

    ExpectTrue(DescribeVertexInputs(VertexInputs{}) == "unknown",
               "unknown inputs describe as unknown");
    ExpectTrue(DescribeVertexInputs(noColour) == "position,texcoord0",
               "prop.mesh inputs describe as position,texcoord0");
    ExpectTrue(std::strcmp(VertexInputFitName(VertexInputFit::Adapted),
                           "adapted") == 0,
               "fit names");

    // Every variant the fitter can emit must be declared by the shipped
    // .program with the matching entry point and defines, or the runtime's
    // program-absent guard would silently decline every adaptation.
    const std::string script = ReadTextFile(BZR_FIXEDFUNC_PROGRAM);
    const std::string hlsl = ReadTextFile(BZR_FIXEDFUNC_HLSL);
    ExpectTrue(!script.empty() && !hlsl.empty(), "payload files readable");
    struct Expected
    {
        const char* name;
        const char* entry;
        bool noColour;
        bool noUv;
    };
    const Expected expected[] = {
        { "OSE_FixedFunc_Textured_vertex_novc", "fixedfunc_vertex", true, false },
        { "OSE_FixedFunc_Textured_vertex_nouv", "fixedfunc_vertex", false, true },
        { "OSE_FixedFunc_Textured_vertex_novc_nouv", "fixedfunc_vertex", true, true },
        { "OSE_FixedFunc_Untextured_vertex_novc", "fixedfunc_untextured_vertex", true, false },
    };
    for (const Expected& e : expected)
    {
        const std::string block = ProgramBlock(script, e.name);
        ExpectContains(block, "vs_4_0", e.name);
        // "entry_point fixedfunc_vertex" is not a substring of the
        // untextured entry's line, so this distinguishes the two.
        ExpectContains(block, (std::string("entry_point ") + e.entry).c_str(),
                       e.name);
        const bool hasNoColour =
            block.find("COMPAT_NO_VERTEX_COLOUR") != std::string::npos;
        const bool hasNoUv = block.find("COMPAT_NO_TEXCOORD") != std::string::npos;
        ExpectTrue(hasNoColour == e.noColour && hasNoUv == e.noUv, e.name);
        ExpectContains(block, "wvpMat worldviewproj_matrix", e.name);
    }
    ExpectContains(hlsl, "#ifndef COMPAT_NO_VERTEX_COLOUR",
                   "hlsl guards the COLOR0 input");
    ExpectContains(hlsl, "#ifndef COMPAT_NO_TEXCOORD",
                   "hlsl guards the TEXCOORD0 input");
}

TextureStageDesc Stage(int colourOp, int src1 = BlendSource::Texture,
                       int src2 = BlendSource::Current, unsigned uvSet = 0)
{
    TextureStageDesc s;
    s.known = true;
    s.colourOp = colourOp;
    s.colourSrc1 = src1;
    s.colourSrc2 = src2;
    s.alphaOp = BlendOpEx::Modulate;
    s.alphaSrc1 = BlendSource::Texture;
    s.alphaSrc2 = BlendSource::Current;
    s.texCoordSet = uvSet;
    return s;
}

LegacyPassDesc TwoStageDesc(const TextureStageDesc& s0, const TextureStageDesc& s1)
{
    LegacyPassDesc d;
    d.textureUnits = 2;
    d.stages = { s0, s1 };
    return d;
}

void TestTwoStageFixedFunction()
{
    std::printf("TestTwoStageFixedFunction\n");
    const CompatConfig config = DefaultCompatConfig();
    std::string vs;
    std::string ps;

    // colour_op shorthands as TextureUnitState::setColourOperation stores them.
    ExpectTrue(ClassifyStageColour(Stage(BlendOpEx::Modulate)) ==
                   StageCombine::Modulate, "modulate");
    ExpectTrue(ClassifyStageColour(Stage(BlendOpEx::Add)) == StageCombine::Add,
               "add");
    ExpectTrue(ClassifyStageColour(Stage(BlendOpEx::Source1)) ==
                   StageCombine::Replace, "replace");
    ExpectTrue(ClassifyStageColour(Stage(BlendOpEx::BlendTextureAlpha)) ==
                   StageCombine::AlphaBlendTexture, "alpha_blend");
    ExpectTrue(ClassifyStageColour(Stage(BlendOpEx::BlendTextureAlpha,
                                         BlendSource::Current,
                                         BlendSource::Texture)) ==
                   StageCombine::Unsupported,
               "reversed texture-alpha blend is not colour_op alpha_blend");
    ExpectTrue(ClassifyStageColour(Stage(9 /* blend_diffuse_alpha */)) ==
                   StageCombine::Unsupported, "exotic ops unsupported");
    ExpectTrue(ClassifyStageColour(TextureStageDesc{}) ==
                   StageCombine::Unsupported, "unread stage unsupported");

    // ISDF Chronicles xrain: unit 0 default, unit 1 colour_op alpha_blend.
    LegacyPassDesc xrain = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                        Stage(BlendOpEx::BlendTextureAlpha));
    ExpectTrue(ClassifyLegacyPass(xrain) == LegacyPassKind::TrueFixedFunction,
               "xrain is true fixed function");
    ExpectTrue(IsSupportedTwoStageCombo(xrain), "xrain combo supported");
    ExpectTrue(DecideCompatPath(ClassifyLegacyPass(xrain), xrain, config) ==
                   CompatPath::FixedFuncTextured2,
               "xrain takes the two-stage path");
    ExpectTrue(ResolveCompatPrograms(CompatPath::FixedFuncTextured2, xrain, vs,
                                     ps) &&
                   vs == "OSE_FixedFunc_Textured2_vertex" &&
                   ps == "OSE_FixedFunc_Textured2_fragment_alphablend",
               "xrain binds the alpha-blend two-stage pair");

    // Ported BZBase emissive overlay: unit 1 default modulate.
    LegacyPassDesc emissive = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                           Stage(BlendOpEx::Modulate));
    ExpectTrue(ResolveCompatPrograms(CompatPath::FixedFuncTextured2, emissive,
                                     vs, ps) &&
                   ps == "OSE_FixedFunc_Textured2_fragment_modulate",
               "emissive overlay binds the modulate two-stage pair");
    LegacyPassDesc added = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                        Stage(BlendOpEx::Add));
    ExpectTrue(ResolveCompatPrograms(CompatPath::FixedFuncTextured2, added, vs,
                                     ps) &&
                   ps == "OSE_FixedFunc_Textured2_fragment_add",
               "add on stage 1");

    // Outside the support set.
    LegacyPassDesc uv1 = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                      Stage(BlendOpEx::Modulate,
                                            BlendSource::Texture,
                                            BlendSource::Current, 1));
    ExpectTrue(!IsSupportedTwoStageCombo(uv1), "second UV set unsupported");
    LegacyPassDesc replace1 = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                           Stage(BlendOpEx::Source1));
    ExpectTrue(!IsSupportedTwoStageCombo(replace1), "stage-1 replace unsupported");
    LegacyPassDesc add0 = TwoStageDesc(Stage(BlendOpEx::Add),
                                       Stage(BlendOpEx::Modulate));
    ExpectTrue(!IsSupportedTwoStageCombo(add0), "stage-0 add unsupported");
    TextureStageDesc oddAlpha = Stage(BlendOpEx::Modulate);
    oddAlpha.alphaOp = BlendOpEx::Source1;
    ExpectTrue(!IsSupportedTwoStageCombo(
                   TwoStageDesc(Stage(BlendOpEx::Modulate), oddAlpha)),
               "non-default alpha op unsupported");
    LegacyPassDesc unread = TwoStageDesc(Stage(BlendOpEx::Modulate),
                                         TextureStageDesc{});
    ExpectTrue(!IsSupportedTwoStageCombo(unread), "unread stage unsupported");
    ExpectTrue(!ResolveCompatPrograms(CompatPath::FixedFuncTextured2, unread, vs,
                                      ps),
               "resolver refuses an unsupported two-stage pass");

    // Unsupported + shaderless fallback: suppress. Programmable fallback:
    // keep the historical decline. Aggressive still wins when enabled.
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, uv1, config) ==
                   CompatPath::SkipShaderless,
               "unsupported with a programmable fallback declines");
    uv1.fallbackShaderless = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, uv1, config) ==
                   CompatPath::SuppressPass,
               "unsupported with only shaderless fallbacks is suppressed");
    CompatConfig aggressive = config;
    aggressive.aggressiveEnabled = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, uv1,
                                aggressive) == CompatPath::AggressiveGeneric,
               "aggressive mode still takes precedence");
    CompatConfig off = config;
    off.compatEnabled = false;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, uv1, off) ==
                   CompatPath::SkipShaderless,
               "compat disabled never suppresses");
    ExpectTrue(ResolveCompatPrograms(CompatPath::SuppressPass, uv1, vs, ps) &&
                   vs == "OSE_FixedFunc_Suppress_vertex" &&
                   ps == "OSE_FixedFunc_Suppress_fragment",
               "suppress pair");

    LegacyPassDesc multi = FixedFuncDesc(1);
    multi.passCount = 2;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, multi,
                                config) == CompatPath::SkipShaderless,
               "multi-pass with a programmable fallback declines");
    multi.fallbackShaderless = true;
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, multi,
                                config) == CompatPath::SuppressPass,
               "multi-pass with only shaderless fallbacks is suppressed");

    // A pass this layer already converted in place is native on the next
    // miss, not "unsupported custom" (the runtime never reads targets).
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("OSE_FixedFunc_Textured2_vertex", "",
                                              "OSE_FixedFunc_Textured2_fragment_alphablend",
                                              "")) == LegacyPassKind::NativeDx11,
               "converted OSE pass classifies native");
    ExpectTrue(ClassifyLegacyPass(ProgramDesc("OSE_FixedFunc_Textured_vertex", "",
                                              "Effect_fragment", "")) !=
                   LegacyPassKind::NativeDx11,
               "a half-converted pass is still legacy");

    // Single-unit behaviour is unchanged by the stage data.
    LegacyPassDesc one = FixedFuncDesc(1);
    one.stages = { Stage(9) };
    ExpectTrue(DecideCompatPath(LegacyPassKind::TrueFixedFunction, one, config) ==
                   CompatPath::FixedFuncTextured,
               "one-unit path keeps its modulate assumption");

    // Vertex-input fitting for the new programs.
    VertexInputs noColour;
    noColour.known = true;
    noColour.diffuse = false;
    noColour.texcoord0 = true;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured2_vertex",
                                        noColour, vs) ==
                       VertexInputFit::Adapted &&
                   vs == "OSE_FixedFunc_Textured2_vertex_novc",
               "two-stage vertex drops COLOR0");
    VertexInputs full;
    full.known = true;
    full.diffuse = true;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured2_vertex", full,
                                        vs) == VertexInputFit::Unchanged,
               "two-stage vertex unchanged with every input");
    VertexInputs noUv = full;
    noUv.texcoord0 = false;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Textured2_vertex", noUv,
                                        vs) == VertexInputFit::Unsatisfiable,
               "two-stage vertex cannot bind without TEXCOORD0");
    VertexInputs bare;
    bare.known = true;
    bare.diffuse = false;
    bare.texcoord0 = false;
    ExpectTrue(FitVertexProgramToInputs("OSE_FixedFunc_Suppress_vertex", bare,
                                        vs) == VertexInputFit::Unchanged,
               "suppress binds on position only");

    const std::string line = FormatSuppressedLog("xrain_test",
                                                 "unsupported-texture-stages",
                                                 uv1);
    ExpectContains(line, "[DX11COMPAT] material=xrain_test path=suppress",
                   "suppress log prefix");
    ExpectContains(line, "stages=modulate,modulate@uv1", "suppress log stages");
    ExpectContains(line, "action=skip-draw", "suppress log action");
    ExpectTrue(std::strcmp(CompatPathName(CompatPath::FixedFuncTextured2),
                           "fixedfunc-textured2") == 0 &&
                   std::strcmp(CompatPathName(CompatPath::SuppressPass),
                               "suppress") == 0,
               "path names");

    // Every program the resolver or fitter can emit is declared.
    const std::string script = ReadTextFile(BZR_FIXEDFUNC_PROGRAM);
    const char* declared[] = {
        "vertex_program OSE_FixedFunc_Textured2_vertex hlsl",
        "vertex_program OSE_FixedFunc_Textured2_vertex_novc hlsl",
        "fragment_program OSE_FixedFunc_Textured2_fragment_modulate hlsl",
        "fragment_program OSE_FixedFunc_Textured2_fragment_add hlsl",
        "fragment_program OSE_FixedFunc_Textured2_fragment_alphablend hlsl",
        "vertex_program OSE_FixedFunc_Suppress_vertex hlsl",
        "fragment_program OSE_FixedFunc_Suppress_fragment hlsl",
    };
    for (const char* d : declared)
    {
        ExpectContains(script, d, "program declared");
    }
    ExpectContains(script, "param_named_auto texMatrix1 texture_matrix 1",
                   "stage 1 keeps its own texture matrix");
}

void TestNativeInputGuards()
{
    std::printf("TestNativeInputGuards\n");
    const NativeInputGuard* glow = FindNativeInputGuard("Glow/Null");
    ExpectTrue(glow != nullptr, "Glow/Null has a guard");
    if (glow != nullptr)
    {
        ExpectTrue(std::strcmp(glow->expectVertex, "Untextured_vertex") == 0 &&
                       std::strcmp(glow->expectFragment, "Untextured_fragment") == 0,
                   "guard pins the stock programs it replaces");
        // The replacement must keep the stock fragment's inputs (COLOR0,
        // TEXCOORD1) and read POSITION only: the untextured no-colour variant.
        ExpectTrue(std::strcmp(glow->replacementVertex,
                               "OSE_FixedFunc_Untextured_vertex_novc") == 0,
                   "Glow/Null takes the POSITION-only untextured variant");
        const std::string line = FormatNativeInputGuardLog(*glow, "applied");
        ExpectContains(line, "[DX11COMPAT] material=Glow/Null native-input-guard",
                       "guard log prefix");
        ExpectContains(line, "action=applied", "guard log action");
    }
    ExpectTrue(FindNativeInputGuard("glow/null") == nullptr,
               "guards match Ogre's case-sensitive material names exactly");
    ExpectTrue(FindNativeInputGuard("BaseWhite") == nullptr,
               "no guard for unrelated materials");
    ExpectTrue(NativeInputGuardCount() >= 1 && NativeInputGuardAt(0) != nullptr &&
                   NativeInputGuardAt(NativeInputGuardCount()) == nullptr,
               "guard table bounds");
    const std::string hlsl = ReadTextFile(BZR_FIXEDFUNC_HLSL);
    ExpectContains(hlsl, "out float vDepth : TEXCOORD1",
                   "untextured variant still outputs the depth the stock fragment reads");
}

int main()
{
    TestNativeInputGuards();
    TestTwoStageFixedFunction();
    TestVertexInputFit();
    TestSynthesisExclusions();
    TestSupportedTargets();
    TestParseCompatFlag();
    TestFamilyMapping();
    TestStageMapping();
    TestResolveCompatPrograms();
    TestClassification();
    TestFixedFuncSupport();
    TestDecidePaths();
    TestSourceSelection();
    TestCacheKeys();
    TestLogFormats();

    if (g_failures != 0)
    {
        std::printf("\ndx11_legacy_material_compat_tests FAILED (%d)\n",
                    g_failures);
        return 1;
    }
    std::printf("\ndx11_legacy_material_compat_tests passed\n");
    return 0;
}
