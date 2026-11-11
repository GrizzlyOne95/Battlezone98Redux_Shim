#include "ordnance_entity_leak_policy.h"

#include <cstdio>

namespace
{
    using namespace BZROpenShim::OrdnanceEntityLeak;

    int g_failures = 0;
    void check(bool ok, const char* text)
    {
        if (!ok)
        {
            std::fprintf(stderr, "FAIL: %s\n", text);
            ++g_failures;
        }
    }

    int g_entity = 0;
    int g_other = 0;

    // The stock case: same pointer, live scene, registered, detached.
    TeardownObservation Orphaned()
    {
        TeardownObservation o;
        o.entityBefore = &g_entity;
        o.entityAfter = &g_entity;
        o.hasRuntimeScene = true;
        o.queryOk = true;
        o.registeredInRuntimeScene = true;
        o.stillAttached = false;
        return o;
    }
}

int main()
{
    check(Decide(Orphaned()) == Decision::Destroy, "stock orphan is destroyed");

    TeardownObservation o = Orphaned();
    o.entityBefore = nullptr;
    o.entityAfter = nullptr;
    check(Decide(o) == Decision::NothingToDo, "no entity, nothing to do");

    o = Orphaned();
    o.entityAfter = nullptr;
    check(Decide(o) == Decision::SkipChanged, "engine cleared the slot: hands off");
    o.entityAfter = &g_other;
    check(Decide(o) == Decision::SkipChanged, "engine replaced the entity: hands off");

    o = Orphaned();
    o.hasRuntimeScene = false;
    check(Decide(o) == Decision::SkipNoScene, "no live scene: skip");

    o = Orphaned();
    o.queryOk = false;
    check(Decide(o) == Decision::SkipQueryFailed, "faulting query: skip");

    // Double-free guard: an Entity the engine already destroyed has left the
    // SceneManager map, so it reads as unregistered and is never destroyed.
    o = Orphaned();
    o.registeredInRuntimeScene = false;
    check(Decide(o) == Decision::SkipNotRegistered, "already destroyed: never destroyed twice");

    o = Orphaned();
    o.stillAttached = true;
    check(Decide(o) == Decision::SkipAttached, "still attached elsewhere: skip");

    // A fault reported together with stale flags must still skip.
    o = Orphaned();
    o.queryOk = false;
    o.registeredInRuntimeScene = true;
    check(Decide(o) != Decision::Destroy, "query failure wins over stale flags");

    if (g_failures)
    {
        std::fprintf(stderr, "%d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("ordnance_entity_leak_policy_tests: all passed\n");
    return 0;
}
