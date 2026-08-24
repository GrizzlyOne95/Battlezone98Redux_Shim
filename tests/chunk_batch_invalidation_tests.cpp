// Regression tests for the generic chunk batch's state-version reuse.
//
// The hazard this guards is asymmetric. A spurious rebuild costs CPU; a missed
// rebuild draws last frame's debris positions, or keeps an expired chunk on
// screen. So the tests below spend most of their effort proving that every
// render-affecting change produces a different version, and that every
// uncertain input resolves toward rebuilding.

#include "chunk_batch_invalidation.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace
{
    using namespace BZROpenShim::ChunkBatchInvalidation;

    [[noreturn]] void Fail(const char* message)
    {
        std::fprintf(stderr, "chunk_batch_invalidation_tests: %s\n", message);
        std::exit(1);
    }

    void Require(bool condition, const char* message)
    {
        if (!condition)
            Fail(message);
    }

    SlotState MakeSlot(std::uint8_t kind = 1)
    {
        SlotState slot = {};
        slot.kind = kind;
        slot.x = 123.5f;
        slot.y = 4.25f;
        slot.z = -67.75f;
        slot.qw = 0.7071f;
        slot.qx = 0.0f;
        slot.qy = 0.7071f;
        slot.qz = 0.0f;
        slot.sx = 1.0f;
        slot.sy = 1.0f;
        slot.sz = 1.0f;
        return slot;
    }

    std::uint64_t VersionOf(const std::vector<SlotState>& slots)
    {
        SourceVersion version;
        std::uint32_t ordinal = 0;
        for (const SlotState& slot : slots)
            MixSlot(version, ordinal++, slot);
        MixCount(version, static_cast<std::uint32_t>(slots.size()));
        return version.Value();
    }

    void TestIdenticalStateProducesIdenticalVersion()
    {
        const std::vector<SlotState> slots = { MakeSlot(1), MakeSlot(2), MakeSlot(1) };
        Require(VersionOf(slots) == VersionOf(slots),
            "the same source state produced two different versions");
        Require(VersionOf(slots) != kUnbuiltVersion,
            "a populated batch hashed to the unbuilt sentinel");
    }

    // The heart of it: every field the geometry emitter reads must move the
    // version, or a real change would be silently reused.
    void TestEveryRenderAffectingFieldMovesTheVersion()
    {
        const std::vector<SlotState> baseline = { MakeSlot() };
        const std::uint64_t reference = VersionOf(baseline);

        struct Mutation
        {
            const char* name;
            void (*apply)(SlotState&);
        };

        const Mutation mutations[] = {
            { "kind", [](SlotState& s) { s.kind = 2; } },
            { "x", [](SlotState& s) { s.x += 0.001f; } },
            { "y", [](SlotState& s) { s.y += 0.001f; } },
            { "z", [](SlotState& s) { s.z += 0.001f; } },
            { "qw", [](SlotState& s) { s.qw += 0.001f; } },
            { "qx", [](SlotState& s) { s.qx += 0.001f; } },
            { "qy", [](SlotState& s) { s.qy += 0.001f; } },
            { "qz", [](SlotState& s) { s.qz += 0.001f; } },
            { "sx", [](SlotState& s) { s.sx += 0.001f; } },
            { "sy", [](SlotState& s) { s.sy += 0.001f; } },
            { "sz", [](SlotState& s) { s.sz += 0.001f; } },
        };

        for (const Mutation& mutation : mutations)
        {
            std::vector<SlotState> mutated = baseline;
            mutation.apply(mutated[0]);
            if (VersionOf(mutated) == reference)
            {
                std::fprintf(stderr,
                    "chunk_batch_invalidation_tests: field '%s' did not change the version\n",
                    mutation.name);
                std::exit(1);
            }
        }
    }

    void TestSmallestRepresentableMoveIsDetected()
    {
        // A chunk drifting by one float ulp still emits different vertices.
        std::vector<SlotState> slots = { MakeSlot() };
        const std::uint64_t before = VersionOf(slots);
        slots[0].x = std::nextafterf(slots[0].x, 1e30f);
        Require(VersionOf(slots) != before,
            "a one-ulp position change was treated as no change");
    }

    void TestMembershipChangesMoveTheVersion()
    {
        const std::vector<SlotState> one = { MakeSlot() };
        std::vector<SlotState> two = one;
        two.push_back(MakeSlot(2));

        Require(VersionOf(one) != VersionOf(two),
            "adding a chunk did not change the version");

        // Removal is the dangerous direction: a chunk that expires must not
        // stay on screen because the remaining set happened to hash the same.
        std::vector<SlotState> removed = two;
        removed.pop_back();
        Require(VersionOf(removed) == VersionOf(one),
            "removing the added chunk did not return to the earlier version");
        Require(VersionOf(removed) != VersionOf(two),
            "removing a chunk did not change the version");
    }

    void TestReorderingMovesTheVersion()
    {
        // Emission order determines index order, so a reordered set is a
        // different batch even though the members are equal.
        std::vector<SlotState> forward = { MakeSlot(1), MakeSlot(2) };
        std::vector<SlotState> reversed = { MakeSlot(2), MakeSlot(1) };
        Require(VersionOf(forward) != VersionOf(reversed),
            "swapping two slots did not change the version");
    }

    void TestNegativeZeroDoesNotForceARebuild()
    {
        std::vector<SlotState> positive = { MakeSlot() };
        positive[0].x = 0.0f;
        std::vector<SlotState> negative = positive;
        negative[0].x = -0.0f;
        Require(VersionOf(positive) == VersionOf(negative),
            "-0.0 and +0.0 produced different versions");
    }

    void TestDecisionReusesOnlyWhenEverythingIsIntact()
    {
        BuiltState built = {};
        built.version = 0x1234ull;
        built.objectAlive = true;
        built.sectionCreated = true;
        built.objectIdentityStable = true;
        built.materialStable = true;

        Require(DecideRebuild(built, 0x1234ull, false) == Reason::None,
            "an unchanged, intact batch was rebuilt");
        Require(!ShouldRebuild(DecideRebuild(built, 0x1234ull, false)),
            "ShouldRebuild disagreed with Reason::None");

        Require(DecideRebuild(built, 0x9999ull, false) == Reason::SourceChanged,
            "a changed source version did not force a rebuild");
        Require(DecideRebuild(built, 0x1234ull, true) == Reason::ForcedByCaller,
            "the opt-out did not force a rebuild");
    }

    void TestEveryUncertainInputFailsTowardRebuilding()
    {
        const std::uint64_t version = 0x1234ull;
        BuiltState intact = {};
        intact.version = version;
        intact.objectAlive = true;
        intact.sectionCreated = true;
        intact.objectIdentityStable = true;
        intact.materialStable = true;

        struct Case
        {
            const char* name;
            void (*apply)(BuiltState&);
            Reason expected;
        };

        const Case cases[] = {
            { "object destroyed",
              [](BuiltState& b) { b.objectAlive = false; }, Reason::ObjectRecreated },
            { "identity changed",
              [](BuiltState& b) { b.objectIdentityStable = false; }, Reason::ObjectRecreated },
            { "material changed",
              [](BuiltState& b) { b.materialStable = false; }, Reason::MaterialChanged },
            { "no section",
              [](BuiltState& b) { b.sectionCreated = false; }, Reason::SectionMissing },
            { "never built",
              [](BuiltState& b) { b.version = kUnbuiltVersion; }, Reason::NeverBuilt },
        };

        for (const Case& testCase : cases)
        {
            BuiltState state = intact;
            testCase.apply(state);
            const Reason reason = DecideRebuild(state, version, false);
            if (reason != testCase.expected || !ShouldRebuild(reason))
            {
                std::fprintf(stderr,
                    "chunk_batch_invalidation_tests: '%s' gave reason %s, expected %s\n",
                    testCase.name, ReasonName(reason), ReasonName(testCase.expected));
                std::exit(1);
            }
        }

        // A default-constructed BuiltState is the state at process start, and
        // must never be mistaken for something reusable.
        BuiltState fresh = {};
        Require(ShouldRebuild(DecideRebuild(fresh, version, false)),
            "a default-constructed built state was treated as reusable");
    }

    void TestTelemetryIsBoundedAndReconciles()
    {
        Telemetry telemetry = {};
        for (int i = 0; i < 100; ++i)
        {
            char name[32] = {};
            std::snprintf(name, sizeof(name), "scheme-%d", i);
            telemetry.NoteScheme(name, i % 2 == 0);
            ++telemetry.requests;
        }
        Require(telemetry.schemeCount <= kMaxTrackedSchemes,
            "the scheme table grew past its bound");

        std::uint64_t counted = 0;
        for (std::size_t i = 0; i < telemetry.schemeCount; ++i)
            counted += telemetry.schemes[i].requests;
        Require(counted == telemetry.requests,
            "scheme attribution dropped requests instead of folding them into the last slot");

        // Repeats of a known scheme must accumulate rather than allocate.
        Telemetry repeated = {};
        for (int i = 0; i < 10; ++i)
            repeated.NoteScheme("high-pssm", i < 3);
        Require(repeated.schemeCount == 1, "a repeated scheme name was tracked twice");
        Require(repeated.schemes[0].requests == 10, "repeated scheme requests did not accumulate");
        Require(repeated.schemes[0].rebuilds == 3, "repeated scheme rebuilds did not accumulate");

        Telemetry unnamed = {};
        unnamed.NoteScheme(nullptr, false);
        unnamed.NoteScheme("", false);
        Require(unnamed.schemeCount == 1, "null and empty scheme names were not folded together");
    }

    void TestReasonCountsStayInBounds()
    {
        Telemetry telemetry = {};
        for (int i = 0; i <= static_cast<int>(Reason::ForcedByCaller); ++i)
            telemetry.NoteReason(static_cast<Reason>(i));
        for (int i = 0; i <= static_cast<int>(Reason::ForcedByCaller); ++i)
            Require(telemetry.reasonCounts[i] == 1, "a reason count did not record");

        // An out-of-range reason must be dropped, never written past the array.
        telemetry.NoteReason(static_cast<Reason>(200));
        Require(telemetry.reasonCounts[0] == 1, "an out-of-range reason corrupted the table");
    }
}

int main()
{
    TestIdenticalStateProducesIdenticalVersion();
    TestEveryRenderAffectingFieldMovesTheVersion();
    TestSmallestRepresentableMoveIsDetected();
    TestMembershipChangesMoveTheVersion();
    TestReorderingMovesTheVersion();
    TestNegativeZeroDoesNotForceARebuild();
    TestDecisionReusesOnlyWhenEverythingIsIntact();
    TestEveryUncertainInputFailsTowardRebuilding();
    TestTelemetryIsBoundedAndReconciles();
    TestReasonCountsStayInBounds();
    std::printf("chunk_batch_invalidation_tests: all checks passed\n");
    return 0;
}
