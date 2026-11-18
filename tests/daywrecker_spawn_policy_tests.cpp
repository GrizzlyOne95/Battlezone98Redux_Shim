// Tests for the Daywrecker fall-on-spawn rules (include/daywrecker_spawn_policy.h).

#include "daywrecker_spawn_policy.h"

#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::DayWreckerSpawnPolicy;

    void TestKey()
    {
        Check(ParseKey("1") && ParseKey("true") && ParseKey(" yes "), "truthy values arm");
        Check(!ParseKey("0") && !ParseKey("false") && !ParseKey("off"), "falsy values do not");
        Check(!ParseKey(nullptr) && !ParseKey("") && !ParseKey("maybe"), "absent or junk is off");
        Check(std::string(kSection) == "DayWreckerClass" && std::string(kKey) == "fallOnSpawn", "key names");
    }

    void TestArm()
    {
        Check(ShouldArm(true, true, 0), "fresh Daywrecker with the key, single player: arm");
        Check(!ShouldArm(false, true, 0), "network game: never (replicas use the same constructor)");
        Check(!ShouldArm(true, false, 0), "no key: stock");
        Check(!ShouldArm(true, true, kFlagAirborne), "already airborne: leave it");
        Check(!ShouldArm(true, true, kFlagAirborne | kFlagOwnerSafe), "an Armory drop's flags: leave it");
        Check(!ShouldArm(true, true, kFlagDetonated), "already blown: leave it");
        Check(ShouldArm(true, true, kFlagLanded), "other bits do not block");
        Check(ArmedFlags(0) == kFlagAirborne, "arming sets only the airborne bit");
        Check(ArmedFlags(kFlagLanded) == (kFlagLanded | kFlagAirborne), "arming keeps the other bits");
        // The Armory lobber ORs 0xC after construction; arming first must
        // not change what it ends with.
        Check((ArmedFlags(0) | 0xCu) == 0xCu, "an armed Armory drop ends as stock (0xC)");
    }

    void TestCache()
    {
        ClassCache<2> cache;
        const int a = 0, b = 0, c = 0;
        const ClassKey ka{ &a, 0x61646177u, 0x6B637277u };
        const ClassKey kb{ &b, 1, 2 };
        const ClassKey kc{ &c, 3, 4 };
        bool v = false;
        Check(!cache.Find(ka, v), "empty cache misses");
        cache.Put(ka, true);
        Check(cache.Find(ka, v) && v, "hit after put");
        const ClassKey reused{ &a, 9, 9 };
        Check(!cache.Find(reused, v), "same address, another ODF: miss");
        cache.Put(kb, false);
        Check(cache.Find(kb, v) && !v, "second entry");
        cache.Put(kc, true);
        Check(cache.Find(kc, v) && v, "a third entry replaces one");
        Check(cache.count == 2, "capacity holds");
        cache.Put(kc, false);
        Check(cache.Find(kc, v) && !v && cache.count == 2, "put on an existing key updates in place");
        cache.Clear();
        Check(!cache.Find(kc, v), "clear empties it");
    }
}

int main()
{
    TestKey();
    TestArm();
    TestCache();
    return OpenShimTest::ExitCode();
}
