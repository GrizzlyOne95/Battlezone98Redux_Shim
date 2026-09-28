// The OPENSHIM_* / BZR_* environment redirect (src/patches/openshim_env_mapping.cpp):
// which openshim.ini key a legacy name reads, how the value is normalised, and
// the order the INI and the process environment are consulted in. Fake INI and
// environment readers stand in for GetPrivateProfileStringA and the process
// environment, so no plugin directory is involved.

#include "openshim_env_mapping.h"

#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::EnvConfig;

    struct FakeIni
    {
        std::map<std::tuple<IniFile, std::string, std::string>, std::string> values;
        mutable std::vector<std::string> reads;

        void Set(const char* section, const char* key, const char* value, IniFile file = IniFile::Main)
        {
            values[std::make_tuple(file, std::string(section), std::string(key))] = value;
        }

        // GetPrivateProfileStringA as TryReadIniValue wraps it: a missing key
        // and an empty value both read as absent.
        IniReader Reader() const
        {
            return [this](IniFile file, const char* section, const char* key, std::string& out)
            {
                reads.push_back(std::string(IniFileName(file)) + ":" + section + "/" + key);
                const auto it = values.find(std::make_tuple(file, std::string(section), std::string(key)));
                if (it == values.end() || it->second.empty())
                    return false;
                out = it->second;
                return true;
            };
        }
    };

    struct FakeEnv
    {
        std::map<std::string, std::string> values;
        mutable int calls = 0;

        // GetEnvironmentVariableA with a buffer: 0 when unset or empty,
        // otherwise the copy contract.
        EnvironmentReader Reader() const
        {
            return [this](const char* name, char* buffer, uint32_t size) -> uint32_t
            {
                ++calls;
                const auto it = values.find(name ? name : "");
                if (it == values.end() || it->second.empty())
                    return 0;
                return CopyEnvironmentValue(it->second, buffer, size);
            };
        }
    };

    // The INI answer for `name`, or "<none>".
    std::string Mapped(const FakeIni& ini, const char* name)
    {
        std::string out;
        if (!TryReadFromIni(name, ini.Reader(), out))
            return "<none>";
        return out;
    }

    // The whole lookup through a 256-byte buffer, or "<unset>".
    std::string Lookup(const char* name, const FakeIni* ini, const FakeEnv& env)
    {
        char buffer[256] = {};
        const IniReader reader = ini ? ini->Reader() : IniReader();
        const uint32_t length = GetEnvironmentValue(name, buffer, sizeof(buffer), ini ? &reader : nullptr, env.Reader());
        if (length == 0)
            return "<unset>";
        if (length >= sizeof(buffer))
            return "<too long>";
        return std::string(buffer, length);
    }

    void TestBooleanKeysNormalise()
    {
        FakeIni ini;
        for (const char* word : {"1", "true", "On", " yes ", "ENABLED"})
        {
            ini.Set("Diagnostics", "TraceHookHits", word);
            Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "1", std::string("true word '") + word + "' maps to 1");
        }
        for (const char* word : {"0", "false", "off", "No", "disabled"})
        {
            ini.Set("Diagnostics", "TraceHookHits", word);
            Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "0", std::string("false word '") + word + "' maps to 0");
        }
    }

    void TestDisableNamesInvertPositiveKeys()
    {
        FakeIni ini;
        ini.Set("Fixes", "ApcAlliedTargetDeploy", "0");
        Check(Mapped(ini, "OPENSHIM_DISABLE_APC_DEPLOY_FIX") == "1", "fix turned off in the INI reads as DISABLE=1");
        Check(Mapped(ini, "BZR_DISABLE_APC_DEPLOY_FIX") == "1", "the BZR_ alias reads the same key");
        ini.Set("Fixes", "ApcAlliedTargetDeploy", "on");
        Check(Mapped(ini, "OPENSHIM_DISABLE_APC_DEPLOY_FIX") == "0", "fix left on reads as DISABLE=0");

        // ENABLE_ and DISABLE_ spellings of one key always disagree.
        ini.Set("Network", "LobbyBanButton", "yes");
        Check(Mapped(ini, "OPENSHIM_ENABLE_LOBBY_BAN_BUTTON") == "1", "ENABLE_ name reads the key as written");
        Check(Mapped(ini, "OPENSHIM_DISABLE_LOBBY_BAN_BUTTON") == "0", "DISABLE_ name reads it inverted");

        // Three legacy chunk switches share the one ChunkMeshes key.
        ini.Set("General", "ChunkMeshes", "false");
        for (const char* name : {"OPENSHIM_DISABLE_CHUNK_EXPERIMENTS", "BZR_DISABLE_CHUNK_MESH_PROXY",
                                 "OPENSHIM_DISABLE_GENERIC_CHUNK_BATCH"})
        {
            Check(Mapped(ini, name) == "1", std::string(name) + " follows [General] ChunkMeshes");
        }

        // DisableControlSmoothing is the one General DISABLE_ key that is
        // itself negative, so it is read as written.
        ini.Set("General", "DisableControlSmoothing", "1");
        Check(Mapped(ini, "OPENSHIM_DISABLE_CONTROL_SMOOTHING") == "1", "negative key is not inverted again");
    }

    void TestNamesMatchWithoutCase()
    {
        FakeIni ini;
        ini.Set("Diagnostics", "TraceSunFlash", "1");
        Check(Mapped(ini, "openshim_trace_sun_flash") == "1", "lower-case name still maps");
        Check(Mapped(ini, "OpenShim_Trace_Sun_Flash") == "1", "mixed-case name still maps");
        Check(Mapped(ini, "OPENSHIM_TRACE_SUN_FLASHX") == "<none>", "a longer name is not a prefix match");
        Check(Mapped(ini, "OPENSHIM_TRACE_SUN_FLAS") == "<none>", "a shorter name is not a prefix match");
    }

    void TestAbsentAndUnparseableKeys()
    {
        FakeIni ini;
        Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "<none>", "absent key gives no INI answer");

        ini.Set("Diagnostics", "TraceHookHits", "");
        Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "<none>", "empty value is treated as absent");

        ini.Set("Diagnostics", "TraceHookHits", "maybe");
        Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "<none>", "unrecognised bool word gives no INI answer");

        // An unparseable friendly key falls through to the verbatim
        // [Environment] entry for the same name.
        ini.Set("Environment", "OPENSHIM_TRACE_HITS", "raw");
        Check(Mapped(ini, "OPENSHIM_TRACE_HITS") == "raw", "unparseable friendly key falls back to [Environment]");
    }

    void TestFriendlyKeyBeatsEnvironmentSection()
    {
        FakeIni ini;
        ini.Set("Diagnostics", "TraceBznLoad", "0");
        ini.Set("Environment", "OPENSHIM_TRACE_BZN_LOAD", "1");
        Check(Mapped(ini, "OPENSHIM_TRACE_BZN_LOAD") == "0", "the documented key wins over [Environment]");
    }

    void TestEnvironmentSectionPassesAnyName()
    {
        FakeIni ini;
        ini.Set("Environment", "OPENSHIM_SOMETHING_NEW", "  verbatim value ");
        Check(Mapped(ini, "OPENSHIM_SOMETHING_NEW") == "  verbatim value ", "[Environment] value is passed verbatim");
        Check(Mapped(ini, "OPENSHIM_SOMETHING_ELSE") == "<none>", "an unlisted name with no entry has no answer");
        Check(ini.reads.back() == "openshim.ini:Environment/OPENSHIM_SOMETHING_ELSE",
              "an unknown name goes straight to [Environment]");
    }

    void TestStringKeysAreVerbatim()
    {
        FakeIni ini;
        ini.Set("General", "SoundChannels", "64");
        Check(Mapped(ini, "OPENSHIM_MAX_SOUND_CHANNELS") == "64", "numeric setting is not bool-normalised");
        Check(Mapped(ini, "BZR_MAX_SOUND_CHANNELS") == "64", "numeric setting alias");

        ini.Set("SinglePlayer", "TurretAimPitchMultiplier", "1.5");
        Check(Mapped(ini, "OPENSHIM_TURRET_PITCH_MULTIPLIER") == "1.5", "float setting passes verbatim");

        ini.Set("Network", "StockFactionSet", "nsdf,cca");
        Check(Mapped(ini, "OPENSHIM_STOCK_FACTION_SET") == "nsdf,cca", "list setting passes verbatim");
    }

    void TestGovernorTuningWords()
    {
        FakeIni ini;
        const struct { const char* word; const char* expected; } cases[] = {
            {"openshim", "1"}, {"  Tuned ", "1"}, {"STOCK", "0"}, {"default", "0"},
            {"on", "1"}, {"0", "0"}, {"bogus", "<none>"},
        };
        for (const auto& c : cases)
        {
            ini.Set("Network", "GovernorTuning", c.word);
            Check(Mapped(ini, "OPENSHIM_GOVERNOR_TUNING") == c.expected,
                  std::string("GovernorTuning '") + c.word + "' -> " + c.expected);
            Check(Mapped(ini, "BZ_GOVERNOR_TUNING") == c.expected,
                  std::string("BZ_GOVERNOR_TUNING '") + c.word + "' -> " + c.expected);
        }
    }

    void TestProducerMenusDefaultOnFromTheirOwnFile()
    {
        FakeIni ini;
        Check(Mapped(ini, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") == "1", "producer menus are on with no key");
        Check(!ini.reads.empty() &&
                  ini.reads.back() == "openshim_producer_build_menus.ini:ProducerBuildMenus/Enabled",
              "producer menus read their own INI");

        // The main INI does not reach it.
        ini.Set("ProducerBuildMenus", "Enabled", "0", IniFile::Main);
        Check(Mapped(ini, "BZR_ENABLE_PRODUCER_BUILD_MENU") == "1", "a main-INI key is not the producer switch");

        ini.Set("ProducerBuildMenus", "Enabled", "off", IniFile::ProducerBuildMenus);
        Check(Mapped(ini, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT") == "0", "producer INI turns menus off");

        ini.Set("ProducerBuildMenus", "Enabled", "garbage", IniFile::ProducerBuildMenus);
        Check(Mapped(ini, "OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") == "1", "unrecognised word keeps menus on");
    }

    void TestIniBeatsLaunchEnvironment()
    {
        FakeIni ini;
        FakeEnv env;
        env.values["OPENSHIM_TRACE_HITS"] = "0";
        ini.Set("Diagnostics", "TraceHookHits", "on");
        Check(Lookup("OPENSHIM_TRACE_HITS", &ini, env) == "1", "INI value beats the launch environment");

        // Absent from the INI: the launch environment still answers.
        env.values["OPENSHIM_TERRAIN_HD"] = "1";
        Check(Lookup("OPENSHIM_TERRAIN_HD", &ini, env) == "1", "launch environment answers when the INI is silent");
        Check(Lookup("OPENSHIM_NOT_SET_ANYWHERE", &ini, env) == "<unset>", "unset everywhere reads as unset");

        // No plugin directory: straight to the environment, and the
        // producer-menu default does not apply.
        Check(Lookup("OPENSHIM_TRACE_HITS", nullptr, env) == "0", "no plugin directory reads the environment");
        Check(Lookup("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU", nullptr, env) == "<unset>",
              "producer default needs the plugin directory");
        Check(Lookup("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU", &ini, env) == "1",
              "producer default applies with the plugin directory");
    }

    void TestCaptureNamesLetTheEnvironmentWin()
    {
        FakeIni ini;
        FakeEnv env;
        ini.Set("Diagnostics", "RelayLogging", "0");
        Check(Lookup("OPENSHIM_RELAY_CAPTURE", &ini, env) == "0", "capture reads the INI when the environment is unset");

        env.values["OPENSHIM_RELAY_CAPTURE"] = "1";
        Check(Lookup("OPENSHIM_RELAY_CAPTURE", &ini, env) == "1", "a set capture variable beats the INI");

        env.values["OPENSHIM_RELAY_CAPTURE"] = "";
        Check(Lookup("OPENSHIM_RELAY_CAPTURE", &ini, env) == "0", "an empty capture variable does not");

        // An ordinary name set in both places still takes the INI.
        env.values["OPENSHIM_TRACE_SUN_FLASH"] = "1";
        ini.Set("Diagnostics", "TraceSunFlash", "0");
        Check(Lookup("OPENSHIM_TRACE_SUN_FLASH", &ini, env) == "0", "non-capture name is INI first");

        Check(IsCaptureOverrideName("bz_bzrnet_trace_queue"), "capture names match without case");
        Check(!IsCaptureOverrideName("OPENSHIM_TRACE_HITS"), "trace flags are not capture names");
        Check(!IsCaptureOverrideName(nullptr), "null is not a capture name");
    }

    void TestEmptyNamesPassThrough()
    {
        FakeIni ini;
        FakeEnv env;
        ini.Set("Environment", "", "x");
        Check(Lookup("", &ini, env) == "<unset>", "empty name goes to the environment");
        Check(env.calls == 1, "empty name makes exactly one environment call");
        std::string out;
        Check(!TryReadFromIni(nullptr, ini.Reader(), out), "null name has no INI answer");
        Check(!TryReadFromIni("", ini.Reader(), out), "empty name has no INI answer");
    }

    void TestCopyContract()
    {
        char buffer[8];
        std::memset(buffer, 'x', sizeof(buffer));
        Check(CopyEnvironmentValue("abc", nullptr, 0) == 4, "size 0 reports the size with terminator");
        Check(CopyEnvironmentValue("abc", nullptr, 4) == 0, "no buffer with a size copies nothing");
        Check(CopyEnvironmentValue("abc", buffer, 3) == 4 && buffer[0] == '\0',
              "too small reports the size and clears the buffer");
        Check(CopyEnvironmentValue("abc", buffer, 4) == 3 && std::strcmp(buffer, "abc") == 0,
              "an exact fit copies and reports the length");
        Check(CopyEnvironmentValue("", buffer, 4) == 0 && buffer[0] == '\0', "empty value copies the terminator");

        // A mapped value comes back through the same contract.
        FakeIni ini;
        FakeEnv env;
        ini.Set("General", "SoundChannels", "128");
        const IniReader reader = ini.Reader();
        char small[3] = {'x', 'x', 'x'};
        Check(GetEnvironmentValue("OPENSHIM_MAX_SOUND_CHANNELS", small, sizeof(small), &reader, env.Reader()) == 4,
              "mapped value too big for the buffer reports its size");
        Check(env.calls == 0, "a mapped value never consults the environment");
    }
}

int main()
{
    TestBooleanKeysNormalise();
    TestDisableNamesInvertPositiveKeys();
    TestNamesMatchWithoutCase();
    TestAbsentAndUnparseableKeys();
    TestFriendlyKeyBeatsEnvironmentSection();
    TestEnvironmentSectionPassesAnyName();
    TestStringKeysAreVerbatim();
    TestGovernorTuningWords();
    TestProducerMenusDefaultOnFromTheirOwnFile();
    TestIniBeatsLaunchEnvironment();
    TestCaptureNamesLetTheEnvironmentWin();
    TestEmptyNamesPassThrough();
    TestCopyContract();

    if (OpenShimTest::FailureCount() == 0)
        std::printf("openshim_env_mapping_tests: %d checks passed\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
