// Pins the career kills-by-type mapping (include/career_kill_class.h).

#include "career_kill_class.h"

#include "test_check.h"

#include <cstring>

using OpenShimTest::Check;
using namespace BZROpenShim::CareerKillClass;

namespace
{
    void Wingman()
    {
        Check(Categorize("wingman", "Tank") == Category::Tank, "Tank");
        Check(Categorize("wingman", "Light Tank") == Category::Tank, "Light Tank");
        Check(Categorize("wingman", "Rocket Tank") == Category::Tank, "Rocket Tank");
        Check(Categorize("wingman", "Heavy Tank") == Category::Tank, "Heavy Tank");
        Check(Categorize("wingman", "Red Devil") == Category::Tank, "Red Devil");
        Check(Categorize("wingman", "Fury") == Category::Tank, "Fury");
        Check(Categorize("wingman", "") == Category::Tank, "unresolved name is a tank");
        Check(Categorize("wingman", "Scout") == Category::Scout, "Scout");
        Check(Categorize("wingman", "Fighter") == Category::Fighter, "Fighter");
        Check(Categorize("wingman", "Bomber") == Category::Bomber, "Bomber");
        Check(Categorize("WINGMAN", "heavy BOMBER") == Category::Bomber, "case-insensitive");
    }

    void Labels()
    {
        Check(Categorize("person", "") == Category::Pilot, "person");
        Check(Categorize("Person", "Scout") == Category::Pilot, "unit name ignored for person");
        Check(Categorize("walker", "") == Category::Tank, "walker");
        Check(Categorize("sav", "") == Category::Tank, "sav");
        Check(Categorize("turrettank", "") == Category::Turret, "turrettank");
        Check(Categorize("turret", "") == Category::Turret, "turret");
        Check(Categorize("howitzer", "") == Category::Artillery, "howitzer");
        for (const char* label : { "apc", "constructionrig", "scavenger", "tug", "minelayer",
                                   "recycler", "factory", "armory" })
            Check(Categorize(label, "") == Category::Support, label);
        for (const char* label : { "i76building", "barracks", "commtower", "powerplant",
                                   "repairdepot", "scrapsilo", "supplydepot", "portal" })
            Check(Categorize(label, "") == Category::Building, label);
        Check(Categorize("", "") == Category::Other, "empty is other");
        Check(Categorize("powerup", "") == Category::Other, "unknown is other");
        Check(Categorize("pond", "Fighter") == Category::Other, "name only matters for wingman");
    }

    void Keys()
    {
        Check(std::strcmp(KillClassKey(Category::Pilot), "pilot") == 0, "pilot key");
        Check(std::strcmp(KillClassKey(Category::Tank), "tank") == 0, "tank key");
        Check(std::strcmp(KillClassKey(Category::Fighter), "fighter") == 0, "fighter key");
        Check(std::strcmp(KillClassKey(Category::Scout), "scout") == 0, "scout key");
        Check(std::strcmp(KillClassKey(Category::Bomber), "bomber") == 0, "bomber key");
        Check(std::strcmp(KillClassKey(Category::Turret), "turret") == 0, "turret key");
        Check(std::strcmp(KillClassKey(Category::Artillery), "artillery") == 0, "artillery key");
        Check(std::strcmp(KillClassKey(Category::Support), "support") == 0, "support key");
        Check(std::strcmp(KillClassKey(Category::Building), "building") == 0, "building key");
        Check(std::strcmp(KillClassKey(Category::Other), "other") == 0, "other key");
    }
}

int main()
{
    Wingman();
    Labels();
    Keys();
    return OpenShimTest::ExitCode();
}
