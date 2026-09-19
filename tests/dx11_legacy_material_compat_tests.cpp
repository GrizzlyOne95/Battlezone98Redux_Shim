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

int main()
{
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
