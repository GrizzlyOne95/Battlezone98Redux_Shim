#include "env_switch_table.h"

#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <vector>

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

    using BZROpenShim::EnvSwitches::Apply;
    using BZROpenShim::EnvSwitches::EnvSwitch;
    using BZROpenShim::EnvSwitches::Kind;

    struct FakeEnv
    {
        std::set<std::string> set;
        std::vector<std::string> queried;

        bool operator()(const char* name)
        {
            queried.emplace_back(name);
            return set.count(name) != 0;
        }
    };

    void TestKillSwitchDefaultsOnAndEitherNameTurnsItOff()
    {
        bool neither = false;
        bool primary = true;
        bool alias = true;
        const EnvSwitch rows[] = {
            {&neither, Kind::KillSwitch, "OPENSHIM_DISABLE_A", "BZR_DISABLE_A"},
            {&primary, Kind::KillSwitch, "OPENSHIM_DISABLE_B", "BZR_DISABLE_B"},
            {&alias, Kind::KillSwitch, "OPENSHIM_DISABLE_C", "BZR_DISABLE_C"},
        };
        FakeEnv env;
        env.set = {"OPENSHIM_DISABLE_B", "BZR_DISABLE_C"};
        Apply(rows, env);
        CHECK(neither);
        CHECK(!primary);
        CHECK(!alias);
    }

    void TestOptInDefaultsOffAndEitherNameTurnsItOn()
    {
        bool neither = true;
        bool primary = false;
        bool alias = false;
        const EnvSwitch rows[] = {
            {&neither, Kind::OptIn, "OPENSHIM_A", "BZR_A"},
            {&primary, Kind::OptIn, "OPENSHIM_B", "BZR_B"},
            {&alias, Kind::OptIn, "OPENSHIM_C", "BZR_C"},
        };
        FakeEnv env;
        env.set = {"OPENSHIM_B", "BZR_C"};
        Apply(rows, env);
        CHECK(!neither);
        CHECK(primary);
        CHECK(alias);
    }

    void TestAliasIsNotQueriedWhenPrimaryIsSet()
    {
        bool flag = true;
        const EnvSwitch rows[] = {
            {&flag, Kind::KillSwitch, "OPENSHIM_DISABLE_X", "BZR_DISABLE_X"},
        };
        FakeEnv env;
        env.set = {"OPENSHIM_DISABLE_X"};
        Apply(rows, env);
        CHECK(env.queried.size() == 1);
        CHECK(env.queried[0] == "OPENSHIM_DISABLE_X");
    }

    void TestRowsAreEvaluatedInOrder()
    {
        bool a = false;
        bool b = false;
        const EnvSwitch rows[] = {
            {&a, Kind::OptIn, "FIRST", "FIRST_ALIAS"},
            {&b, Kind::OptIn, "SECOND", "SECOND_ALIAS"},
        };
        FakeEnv env;
        Apply(rows, env);
        const std::vector<std::string> expected = {"FIRST", "FIRST_ALIAS", "SECOND", "SECOND_ALIAS"};
        CHECK(env.queried == expected);
    }
}

int main()
{
    TestKillSwitchDefaultsOnAndEitherNameTurnsItOff();
    TestOptInDefaultsOffAndEitherNameTurnsItOn();
    TestAliasIsNotQueriedWhenPrimaryIsSet();
    TestRowsAreEvaluatedInOrder();
    if (g_failures == 0)
        std::printf("env_switch_table_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
