// Regression tests for the Enhanced sun lighting baseline policy.
//
// Pins the per-world table (the Campaign Reimagined day calibration the
// Enhanced profile was tuned against), the multiply/floor/clamp grading, the
// [SunBaseline] overrides, and the parser's handling of bad numbers. The
// runtime in pilot_flashlight.cpp only converts to and from these types.

#include "sun_baseline.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace openshim::sunbaseline;

    bool Near(float a, float b)
    {
        return std::fabs(a - b) <= 1e-5f;
    }

    bool NearRgb(const float actual[3], float r, float g, float b)
    {
        return Near(actual[0], r) && Near(actual[1], g) && Near(actual[2], b);
    }

    SunLightStateLike MakeStock()
    {
        SunLightStateLike stock = {};
        stock.diffuse[0] = 0.80f;
        stock.diffuse[1] = 0.70f;
        stock.diffuse[2] = 0.60f;
        stock.specular[0] = 0.50f;
        stock.specular[1] = 0.50f;
        stock.specular[2] = 0.50f;
        stock.ambient[0] = 0.20f;
        stock.ambient[1] = 0.20f;
        stock.ambient[2] = 0.20f;
        stock.powerScale = 1.0f;
        stock.shadowFar = 128.0f;
        return stock;
    }

    void TestTableLookup()
    {
        Check(&BaselineForWorldCode("ti") == &kTitanBaseline, "ti must map to the Titan entry");
        Check(&BaselineForWorldCode("mn") == &kMoonClassBaseline, "mn must map to the moon-class entry");
        Check(&BaselineForWorldCode("eu") == &kMoonClassBaseline, "eu must map to the moon-class entry");
        Check(&BaselineForWorldCode("io") == &kMoonClassBaseline, "io must map to the moon-class entry");
        Check(&BaselineForWorldCode("") == &kDefaultBaseline, "an empty code must map to the default");
        Check(&BaselineForWorldCode("ma") == &kDefaultBaseline, "Mars must map to the default");
        Check(&BaselineForWorldCode("zz") == &kDefaultBaseline, "an unknown code must map to the default");
        Check(&BaselineForWorldCode("TI") == &kDefaultBaseline,
              "codes are lowercase by contract; uppercase is not a known code");

        Check(Near(kDefaultBaseline.powerScale, 1.15f), "default power scale must be 1.15");
        Check(Near(kTitanBaseline.powerScale, 0.95f), "Titan power scale must be 0.95");
        Check(Near(kMoonClassBaseline.powerScale, 1.32f), "moon-class power scale must be 1.32");

        Check(NearRgb(kTitanBaseline.specularMul, 1.00f * 0.80f, 0.76f * 0.80f, 0.46f * 0.80f),
              "Titan specular multiplier must be (1.00,0.76,0.46)*0.80");
        Check(NearRgb(kMoonClassBaseline.ambientMul, 0.64f * 0.70f, 0.68f * 0.70f, 0.82f * 0.70f),
              "moon-class ambient multiplier must be (0.64,0.68,0.82)*0.70");
        Check(NearRgb(kMoonClassBaseline.specularMul, 1.30f * 1.08f, 1.26f * 1.08f, 1.18f * 1.08f),
              "moon-class specular multiplier must be (1.30,1.26,1.18)*1.08");
    }

    void TestDefaultTouchesOnlyPower()
    {
        const SunLightStateLike stock = MakeStock();
        SunLightStateLike out = {};
        unsigned mask = 0;
        ComputeBaseline(SunBaselineConfig{}, BaselineForWorldCode(""), stock, out, mask);
        Check(mask == kFieldPowerScale, "the default world must change only the power scale");
        Check(Near(out.powerScale, 1.15f), "the default world must set power 1.15");
        Check(NearRgb(out.diffuse, 0.80f, 0.70f, 0.60f), "the default world must keep diffuse");
        Check(NearRgb(out.ambient, 0.20f, 0.20f, 0.20f), "the default world must keep ambient");
        Check(Near(out.shadowFar, 128.0f), "shadow far must be untouched without an override");
    }

    void TestMulFloorAndClamp()
    {
        // Titan: diffuse floor (0.86,0.60,0.30) beats stock*mul for dim input.
        SunLightStateLike stock = MakeStock();
        SunLightStateLike out = {};
        unsigned mask = 0;
        ComputeBaseline(SunBaselineConfig{}, kTitanBaseline, stock, out, mask);
        Check(NearRgb(out.diffuse, 0.92f, 0.60f, 0.30f),
              "Titan diffuse must be max(stock*mul, floor) per channel");
        Check(NearRgb(out.ambient, 0.34f, 0.23f, 0.11f),
              "Titan ambient must rise to its floor when stock*mul is below it");
        Check(NearRgb(out.specular, 0.42f, 0.304f, 0.184f),
              "Titan specular must mix floor (r) and stock*mul (g,b)");
        Check(Near(out.powerScale, 0.95f), "Titan must set power 0.95");
        Check(mask == (kFieldDiffuse | kFieldSpecular | kFieldAmbient | kFieldPowerScale),
              "Titan must report the four changed fields");

        // Moon class on a bright sun: clamp at 4, and NaN/negative go to 0.
        stock.diffuse[0] = 10.0f;
        stock.diffuse[1] = -1.0f;
        stock.diffuse[2] = std::nanf("");
        ComputeBaseline(SunBaselineConfig{}, kMoonClassBaseline, stock, out, mask);
        Check(Near(out.diffuse[0], kColourMax), "graded channels must clamp to 4");
        Check(Near(out.diffuse[1], 0.0f), "negative channels must clamp to 0");
        Check(Near(out.diffuse[2], 0.0f), "NaN channels must clamp to 0");
        Check(NearRgb(out.ambient, 0.20f * 0.448f, 0.20f * 0.476f, 0.20f * 0.574f),
              "moon-class ambient must be stock*mul with no floor");
    }

    void TestConfigOverrides()
    {
        const SunLightStateLike stock = MakeStock();
        SunLightStateLike out = {};
        unsigned mask = 0;

        SunBaselineConfig config;
        config.hasPowerScale = true;
        config.powerScale = 2.0f;
        ComputeBaseline(config, kTitanBaseline, stock, out, mask);
        Check(Near(out.powerScale, 2.0f), "a configured PowerScale must beat the table");

        config = SunBaselineConfig{};
        config.worldColorGrading = false;
        ComputeBaseline(config, kTitanBaseline, stock, out, mask);
        Check(mask == kFieldPowerScale, "WorldColorGrading=0 must change only the power scale");
        Check(NearRgb(out.diffuse, 0.80f, 0.70f, 0.60f), "WorldColorGrading=0 must keep diffuse");
        Check(NearRgb(out.specular, 0.50f, 0.50f, 0.50f), "WorldColorGrading=0 must keep specular");
        Check(NearRgb(out.ambient, 0.20f, 0.20f, 0.20f), "WorldColorGrading=0 must keep ambient");

        config = SunBaselineConfig{};
        config.hasShadowFar = true;
        config.shadowFar = 256.0f;
        ComputeBaseline(config, kDefaultBaseline, stock, out, mask);
        Check(Near(out.shadowFar, 256.0f), "a configured ShadowFarDistance must be written");
        Check((mask & kFieldShadowFar) != 0, "a changed shadow far must be in the mask");

        // A power scale already at the target is not reported as changed.
        SunLightStateLike already = stock;
        already.powerScale = 1.15f;
        ComputeBaseline(SunBaselineConfig{}, kDefaultBaseline, already, out, mask);
        Check(mask == 0, "an unchanged field must not be in the mask");
    }

    struct FakeIni
    {
        std::map<std::string, std::string> values;
        std::vector<std::string> invalid;

        SunBaselineConfig Parse()
        {
            invalid.clear();
            return ParseSunBaselineConfig(
                [this](const char* key, std::string& out) {
                    const auto it = values.find(key);
                    if (it == values.end())
                        return false;
                    out = it->second;
                    return true;
                },
                [this](const char* key, bool& out) {
                    const auto it = values.find(key);
                    if (it == values.end())
                        return false;
                    out = it->second == "1";
                    return true;
                },
                [this](const char* key) { invalid.push_back(key); });
        }
    };

    void TestParser()
    {
        FakeIni ini;
        SunBaselineConfig config = ini.Parse();
        Check(config.enabled && config.worldColorGrading, "absent keys must default on");
        Check(!config.hasPowerScale && !config.hasShadowFar, "absent numbers must be absent");
        Check(ini.invalid.empty(), "absent keys must not be reported");

        ini.values = { { "Enabled", "0" }, { "WorldColorGrading", "0" },
                       { "PowerScale", "" }, { "ShadowFarDistance", "  " } };
        config = ini.Parse();
        Check(!config.enabled && !config.worldColorGrading, "explicit 0 must turn both off");
        Check(!config.hasPowerScale && !config.hasShadowFar, "blank numbers must be absent");
        Check(ini.invalid.empty(), "blank numbers must not be reported as invalid");

        ini.values = { { "PowerScale", " 1.5 " }, { "ShadowFarDistance", "384" } };
        config = ini.Parse();
        Check(config.hasPowerScale && Near(config.powerScale, 1.5f), "PowerScale 1.5 must parse");
        Check(config.hasShadowFar && Near(config.shadowFar, 384.0f),
              "ShadowFarDistance 384 must parse");

        ini.values = { { "PowerScale", "1,5" }, { "ShadowFarDistance", "far" } };
        config = ini.Parse();
        Check(!config.hasPowerScale && !config.hasShadowFar, "unparsable numbers must be absent");
        Check(ini.invalid.size() == 2 && ini.invalid[0] == "PowerScale" &&
                  ini.invalid[1] == "ShadowFarDistance",
              "each unparsable number must be reported once by key");

        ini.values = { { "PowerScale", "9" }, { "ShadowFarDistance", "8" } };
        config = ini.Parse();
        Check(!config.hasPowerScale && !config.hasShadowFar, "out-of-range numbers must be absent");
        Check(ini.invalid.size() == 2, "out-of-range numbers must be reported");
    }
}

int main()
{
    TestTableLookup();
    std::printf("TestTableLookup\n");
    TestDefaultTouchesOnlyPower();
    std::printf("TestDefaultTouchesOnlyPower\n");
    TestMulFloorAndClamp();
    std::printf("TestMulFloorAndClamp\n");
    TestConfigOverrides();
    std::printf("TestConfigOverrides\n");
    TestParser();
    std::printf("TestParser\n");

    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "sun_baseline_tests: %d failure(s)\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("\nsun_baseline_tests passed\n");
    return 0;
}
