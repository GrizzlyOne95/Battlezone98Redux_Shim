// odf_compat_tests.cpp
// Unit tests for the portable ODF compatibility core (no engine linkage).

#include "odf_compat.h"

#include <cassert>
#include <cstdio>
#include <string>

namespace
{
int g_failures = 0;

void Check(bool cond, const char* what, int line)
{
    if (!cond)
    {
        ++g_failures;
        std::printf("FAIL %d: %s\n", line, what);
    }
}
#define CHECK(c) Check((c), #c, __LINE__)

using BZROpenShim::OdfCompat::Options;
using BZROpenShim::OdfCompat::ProcessResult;
using BZROpenShim::OdfCompat::ProcessOdfText;

ProcessResult Run(const char* file, const std::string& text, bool remap, bool unknowns, bool guards)
{
    Options opt;
    opt.remapLegacySections = remap;
    opt.logUnknownSections = unknowns;
    opt.guardCrashValues = guards;
    return ProcessOdfText(file, text.data(), text.size(), opt);
}
} // namespace

int main()
{
    using namespace BZROpenShim::OdfCompat;

    // File-name matching.
    CHECK(IsOdfFileName("flare.odf"));
    CHECK(IsOdfFileName("FLARE.ODF"));
    CHECK(IsOdfFileName("a/b\\c.ODf"));
    CHECK(!IsOdfFileName(nullptr));
    CHECK(!IsOdfFileName("flare.od"));
    CHECK(!IsOdfFileName("odf"));
    CHECK(!IsOdfFileName("flare.geo"));

    // Known sections (loader set + retail census), case-insensitive.
    CHECK(IsKnownSection("FlareMineClass"));
    CHECK(IsKnownSection("flaremineclass"));
    CHECK(IsKnownSection("GameObjectClass"));
    CHECK(IsKnownSection("Explosion"));
    CHECK(IsKnownSection("Render"));
    CHECK(IsKnownSection("Sphere"));
    CHECK(IsKnownSection("smokecenter"));
    CHECK(IsKnownSection("MineLayerClass")); // spelling variant, same hash
    CHECK(!IsKnownSection("FlareBuildingClass"));
    CHECK(!IsKnownSection("NoSuchSection"));
    CHECK(!IsKnownSection(""));

    // Legacy map.
    CHECK(CanonicalSectionFor("FlareBuildingClass") != nullptr);
    CHECK(std::string(CanonicalSectionFor("magnetclass")) == "MagnetMineClass");
    CHECK(std::string(CanonicalSectionFor("SPRAYBUILDNGCLASS")) == "SprayBuildingClass");
    CHECK(std::string(CanonicalSectionFor("gameobject")) == "GameObjectClass");
    CHECK(std::string(CanonicalSectionFor("SprayBomb")) == "SprayBombClass");
    CHECK(CanonicalSectionFor("Explosion") == nullptr); // live dispatch root: never remap
    CHECK(CanonicalSectionFor("FlareMineClass") == nullptr);

    // Remap rewrites the header name only, preserves CRLF and the rest.
    {
        const std::string in = "[GameObjectClass]\r\nclassLabel = \"magnet\"\r\n\r\n[MagnetClass]\r\ntriggerDelay = 2.0\r\n";
        ProcessResult r = Run("magpull.odf", in, true, false, false);
        CHECK(r.changed);
        CHECK(r.text == "[GameObjectClass]\r\nclassLabel = \"magnet\"\r\n\r\n[MagnetMineClass]\r\ntriggerDelay = 2.0\r\n");
        CHECK(r.remaps.size() == 1);
        CHECK(r.remaps[0].line == 4);
        CHECK(r.remaps[0].name == "MagnetClass");
        CHECK(r.remaps[0].mappedTo == "MagnetMineClass");
        CHECK(r.unknowns.empty());
    }

    // Remap off: byte-identical, no events (Redux-strict default).
    {
        const std::string in = "[MagnetClass]\ntriggerDelay = 2.0\n";
        ProcessResult r = Run("magpull.odf", in, false, false, false);
        CHECK(!r.changed);
        CHECK(r.text == in);
        CHECK(r.remaps.empty() && r.unknowns.empty() && r.guards.empty());
    }

    // Missing ']' is preserved, name still remapped.
    {
        const std::string in = "[GameObjectClass\nclassLabel = \"sav\"\n";
        ProcessResult r = Run("savs8.odf", in, true, true, false);
        CHECK(!r.changed); // GameObjectClass is canonical: nothing to do
        CHECK(r.text == in);
        CHECK(r.unknowns.empty()); // tolerated header, known section
    }
    {
        const std::string in = "[MagnetClass\ntriggerDelay = 2.0\n";
        ProcessResult r = Run("m.odf", in, true, false, false);
        CHECK(r.changed);
        CHECK(r.text == "[MagnetMineClass\ntriggerDelay = 2.0\n");
    }

    // Unknown headers: logged once per file, gated by toggle.
    {
        const std::string in = "[GameObjectClass]\n[WeirdSection]\na = 1\n[WeirdSection]\nb = 2\n";
        ProcessResult r = Run("x.odf", in, false, true, false);
        CHECK(!r.changed);
        CHECK(r.unknowns.size() == 1);
        CHECK(r.unknowns[0].line == 2);
        CHECK(r.unknowns[0].name == "WeirdSection");
        ProcessResult r2 = Run("x.odf", in, false, false, false);
        CHECK(r2.unknowns.empty());
    }

    // Key lines and comments are never treated as headers.
    {
        const std::string in = "; [NotAHeader]\n// [AlsoNot]\nkey = \"[brackets]\"\n";
        ProcessResult r = Run("x.odf", in, true, true, false);
        CHECK(!r.changed);
        CHECK(r.text == in);
        CHECK(r.remaps.empty() && r.unknowns.empty());
    }

    // Crash-value guards: fieldRadius zero forms clamp to 20.0.
    for (const char* zero : {"0", "0.0", "0e0", ".0", "-0.0"})
    {
        std::string in = std::string("[MagnetMineClass]\nfieldRadius = ") + zero + "\nobjDrag = 2.0\n";
        ProcessResult r = Run("m.odf", in, false, false, true);
        CHECK(r.changed);
        CHECK(r.text == "[MagnetMineClass]\nfieldRadius = 20.0\nobjDrag = 2.0\n");
        CHECK(r.guards.size() == 1);
        CHECK(r.guards[0].line == 2);
    }
    // Sane values untouched. "400.0f" keeps its float suffix: the strict
    // token parse rejects the trailing 'f', so it is left alone.
    for (const char* v : {"20.0", "-30.0", "1e30", "400.0f", "0.5"})
    {
        std::string in = std::string("[MagnetMineClass]\nfieldRadius = ") + v + "\n";
        ProcessResult r = Run("m.odf", in, false, false, true);
        CHECK(!r.changed);
        CHECK(r.guards.empty());
    }
    // Guards are section-scoped: fieldRadius elsewhere is ignored.
    {
        const std::string in = "[FlamePuffClass]\nflameRadius = 0\n";
        ProcessResult r = Run("f.odf", in, false, false, true);
        CHECK(!r.changed);
        CHECK(r.guards.empty());
    }

    // Negative counts clamp to 0.
    {
        const std::string in = "[ChargeGunClass]\nordnanceCount = -3\n";
        ProcessResult r = Run("g.odf", in, false, false, true);
        CHECK(r.changed);
        CHECK(r.text == "[ChargeGunClass]\nordnanceCount = 0\n");
        const std::string in2 = "[LauncherClass]\ntargetCount = -1\n";
        ProcessResult r2 = Run("l.odf", in2, false, false, true);
        CHECK(r2.changed);
        CHECK(r2.text == "[LauncherClass]\ntargetCount = 0\n");
        const std::string in3 = "[LauncherClass]\ntargetCount = 4\n";
        CHECK(!Run("l.odf", in3, false, false, true).changed);
    }

    // Missing payloadName is reported (error-grade), present is silent.
    {
        const std::string in = "[FlareMineClass]\nfireSound = \"x.wav\"\n";
        ProcessResult r = Run("flare.odf", in, false, false, true);
        CHECK(!r.changed);
        CHECK(r.guards.size() == 1);
        CHECK(r.guards[0].key == "payloadName");
        const std::string in2 = "[FlareMineClass]\npayloadName = \"flame\"\n";
        CHECK(Run("flare.odf", in2, false, false, true).guards.empty());
        // Gated by the toggle.
        CHECK(Run("flare.odf", in, false, false, false).guards.empty());
    }

    // Empty input.
    {
        ProcessResult r = Run("e.odf", "", true, true, true);
        CHECK(r.text.empty() && !r.changed);
    }

    if (g_failures == 0)
        std::printf("odf_compat_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
