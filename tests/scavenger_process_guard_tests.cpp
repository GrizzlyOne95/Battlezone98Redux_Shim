// Decision-logic tests for the AI_Team_Compute_Other scavenger process guard.
#include "scavenger_process_guard.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::ScavengerProcessGuard;

namespace
{
    // The GOG Redux 2.2.301 vtables (RTTI hierarchy walk, 2026-10-14).
    constexpr uintptr_t kScavengerProcess = 0x008871D8;
    constexpr uintptr_t kScavengerFriend = 0x00887190;
    constexpr uintptr_t kScavengerEnemy = 0x008871B4;
    constexpr uintptr_t kNetProcess = 0x00884BB4;
    constexpr uintptr_t kAiProcess = 0x00884A00;  // base class vtable of a destroying object (any non-family value)

    Config Gog()
    {
        Config config;
        config.vtables[0] = kScavengerProcess;
        config.vtables[1] = kScavengerFriend;
        config.vtables[2] = kScavengerEnemy;
        config.count = 3;
        return config;
    }

    const void* Obj()
    {
        static int dummy = 0;
        return &dummy;
    }

    void TestFamilyIsAccepted()
    {
        const Config config = Gog();
        Check(Classify(config, Obj(), true, kScavengerProcess) == Verdict::Accept, "base ScavengerProcess accepted");
        Check(Classify(config, Obj(), true, kScavengerFriend) == Verdict::Accept, "ScavengerFriend accepted");
        Check(Classify(config, Obj(), true, kScavengerEnemy) == Verdict::Accept, "ScavengerEnemy accepted");
    }

    void TestNetProcessAndForeignRejected()
    {
        const Config config = Gog();
        Check(Classify(config, Obj(), true, kNetProcess) == Verdict::ForeignVtable, "NetProcess rejected");
        Check(Classify(config, Obj(), true, kAiProcess) == Verdict::ForeignVtable,
              "a base/destroying object (non-family vtable) rejected");
        Check(Classify(config, Obj(), true, 0) == Verdict::ForeignVtable, "zeroed vtable rejected");
        Check(Classify(config, Obj(), true, kScavengerProcess + 4) == Verdict::ForeignVtable,
              "an interior pointer into a family vtable is not a vtable");
    }

    void TestNullAndUnreadableRejected()
    {
        const Config config = Gog();
        Check(Classify(config, nullptr, false, 0) == Verdict::NullProcess, "null process rejected");
        Check(Classify(config, nullptr, true, kScavengerProcess) == Verdict::NullProcess,
              "null wins even if a stale vtable word was supplied");
        Check(Classify(config, Obj(), false, kScavengerProcess) == Verdict::UnreadableProcess,
              "unreadable object rejected even with a stale family value");
    }

    void TestUnusableConfigFailsClosed()
    {
        Config empty;
        Check(!ConfigIsUsable(empty), "empty set is unusable");
        Check(Classify(empty, Obj(), true, kScavengerProcess) == Verdict::BadConfig, "empty set accepts nothing");

        Config withZero = Gog();
        withZero.vtables[1] = 0;
        Check(!ConfigIsUsable(withZero), "a null vtable entry is unusable");
        Check(Classify(withZero, Obj(), true, 0) != Verdict::Accept, "a null entry must not make null vtables acceptable");

        Config dup = Gog();
        dup.vtables[2] = dup.vtables[0];
        Check(!ConfigIsUsable(dup), "duplicate entries are unusable");

        Config tooMany = Gog();
        tooMany.count = kMaxVtables + 1;
        Check(!ConfigIsUsable(tooMany), "oversized count is unusable");
    }

    // Models the stock callee's hazard: a fake "process" whose allocation is the
    // size of NetProcess (0x18) sits in front of a guard word standing for the next
    // heap header. The stock function would store -1.0f at +0x3C; the guarded path
    // must never touch the object and must return a y = -1 vector.
    struct FakeNetAllocation
    {
        std::uint32_t process[6];     // 0x18 bytes: NetProcess
        std::uint32_t neighbour[16];  // stand-in for the next heap entry
    };

    const float* GuardedCall(const Config& config, FakeNetAllocation& alloc)
    {
        const bool readable = true;
        const std::uintptr_t vtable = alloc.process[0];
        if (Classify(config, &alloc, readable, vtable) == Verdict::Accept)
        {
            // Stock path (would be the engine call); the test never takes it for NetProcess.
            alloc.neighbour[(0x3C - 0x18) / 4] = 0xBF800000u;
            return nullptr;
        }
        return NoScrapPosition();
    }

    void TestRejectedProcessIsNeverWritten()
    {
        FakeNetAllocation alloc;
        std::memset(&alloc, 0xAB, sizeof(alloc));
        alloc.process[0] = static_cast<std::uint32_t>(kNetProcess);
        FakeNetAllocation before = alloc;
        const float* result = GuardedCall(Gog(), alloc);
        Check(std::memcmp(&before, &alloc, sizeof(alloc)) == 0, "guarded call leaves the allocation and its neighbour untouched");
        Check(result != nullptr, "a vector is returned");
        if (result)
        {
            Check(result[1] == -1.0f, "returned y is -1 (the caller's no-scrap value)");
            Check(!(result[1] > 0.0f), "caller promotion test (y > 0) fails for the returned vector");
            Check(result != reinterpret_cast<const float*>(&alloc), "returned vector is independent of the process");
            Check(result == NoScrapPosition(), "the same read-only vector is reused");
        }
        Check(kPositionYOffset == 4, "y component sits at +4 of the position vector");
    }
}

int main()
{
    TestFamilyIsAccepted();
    TestNetProcessAndForeignRejected();
    TestNullAndUnreadableRejected();
    TestUnusableConfigFailsClosed();
    TestRejectedProcessIsNeverWritten();

    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "scavenger_process_guard_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("scavenger_process_guard_tests: all checks passed\n");
    return 0;
}
