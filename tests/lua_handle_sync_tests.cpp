#include "lua_handle_sync.h"

#include <cstdio>
#include <string>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::LuaHandleSync;
    using Status = LabelIndex::Status;

    // Finds two distinct labels with the same 31-bit hash by brute force, so
    // the collision path is exercised against the real hash rather than a
    // stand-in. The birthday bound makes ~100k attempts plenty.
    bool FindCollidingLabels(std::string& a, std::string& b)
    {
        std::unordered_map<uint32_t, std::string> seen;
        for (uint32_t i = 0; i < 400000; ++i)
        {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "lbl%u", i);
            const uint32_t h = LabelHash31(buf);
            const auto it = seen.find(h);
            if (it != seen.end())
            {
                a = it->second;
                b = buf;
                return true;
            }
            seen.emplace(h, buf);
        }
        return false;
    }

    void TestHashIsFnv1aAndPinned()
    {
        // Published FNV-1a/32 vectors: "" and "a" and "foobar".
        CHECK(Fnv1a32("") == 0x811C9DC5u);
        CHECK(Fnv1a32("a") == 0xE40C292Cu);
        CHECK(Fnv1a32("foobar") == 0xBF9CF968u);
        // The wire value is a contract between peers: pin real labels.
        CHECK(MakeReservedId("a") == (0x80000000u | (0xE40C292Cu & 0x7FFFFFFFu)));
        CHECK(MakeReservedId("eggeizr139_geyser") ==
              (0x80000000u | (Fnv1a32("eggeizr139_geyser") & 0x7FFFFFFFu)));
    }

    void TestReservedIdsNeverLookLikeRealOnes()
    {
        CHECK(IsReservedId(MakeReservedId("x")));
        CHECK(IsReservedId(0x80000000u));
        CHECK(IsReservedId(0xFFFFFFFFu));
        CHECK(!IsReservedId(0));
        // Real ids are owner << 16 | counter; the high bit needs owner >= 0x8000.
        const uint32_t realMax = (0x7FFFu << 16) | 0xFFFFu;
        CHECK(!IsReservedId(realMax));
        CHECK(!IsReservedId((1u << 16) | 1u));
        // Every label hashes into the reserved half, whatever its bytes.
        for (const char* label : { "a", "geyser1", "apdrop196_camerapod", "player-1_hover", "\x80\xFF" })
            CHECK(IsReservedId(MakeReservedId(label)));
    }

    void TestCarriableLabels()
    {
        CHECK(!IsCarriableLabel(nullptr));
        CHECK(!IsCarriableLabel(""));
        CHECK(IsCarriableLabel("x"));
        CHECK(IsCarriableLabel(std::string(kMaxLabelLength, 'a').c_str()));
        CHECK(!IsCarriableLabel(std::string(kMaxLabelLength + 1, 'a').c_str()));
    }

    void TestUniqueLabelRoundTrips()
    {
        LabelIndex index;
        index.Add("geyser_a", 0x1000);
        index.Add("geyser_b", 0x2000);
        index.Add("", 0x3000);          // unlabelled objects are ignored
        index.Add(nullptr, 0x4000);
        CHECK(index.Size() == 2);

        // Sender computes the id from the label; receiver looks the id up.
        const uint32_t id = MakeReservedId("geyser_b");
        const LabelIndex::Result r = index.Lookup(id);
        CHECK(r.status == Status::Unique);
        CHECK(r.tag == 0x2000);
        CHECK(r.label == "geyser_b");

        const LabelIndex::Result byLabel = index.LookupLabel("geyser_a");
        CHECK(byLabel.status == Status::Unique);
        CHECK(byLabel.tag == 0x1000);

        // An id nothing hashes to resolves to nothing: nil, as today.
        CHECK(index.Lookup(MakeReservedId("not_here")).status == Status::Unknown);
        CHECK(index.LookupLabel("not_here").status == Status::Unknown);
    }

    void TestLookupIgnoresTheReservedBit()
    {
        LabelIndex index;
        index.Add("beacon", 0x10);
        const uint32_t hash = LabelHash31("beacon");
        CHECK(index.Lookup(hash).status == Status::Unique);
        CHECK(index.Lookup(hash | kReservedBit).status == Status::Unique);
    }

    void TestSameLabelOnTwoObjectsIsAmbiguous()
    {
        LabelIndex index;
        index.Add("dup", 0x10);
        index.Add("dup", 0x20);
        CHECK(index.Lookup(MakeReservedId("dup")).status == Status::Ambiguous);
        CHECK(index.LookupLabel("dup").status == Status::Ambiguous);

        // Seeing the same object twice is not a duplicate.
        LabelIndex again;
        again.Add("one", 0x10);
        again.Add("one", 0x10);
        CHECK(again.Lookup(MakeReservedId("one")).status == Status::Unique);
    }

    void TestHashCollisionDisablesBothLabels()
    {
        std::string a, b;
        CHECK(FindCollidingLabels(a, b));
        CHECK(a != b);
        CHECK(LabelHash31(a.c_str()) == LabelHash31(b.c_str()));

        LabelIndex index;
        index.Add(a.c_str(), 0x10);
        index.Add(b.c_str(), 0x20);
        index.Add("bystander", 0x30);
        CHECK(index.CollisionCount() == 1);

        // Neither colliding label is sent, and the receiver refuses the id.
        CHECK(index.LookupLabel(a.c_str()).status == Status::Collision);
        CHECK(index.LookupLabel(b.c_str()).status == Status::Collision);
        CHECK(index.Lookup(MakeReservedId(a.c_str())).status == Status::Collision);

        // A third label that merely collides with an existing entry is
        // reported as the collision, not as the stored label's object.
        CHECK(index.LookupLabel("bystander").status == Status::Unique);

        // Insertion order does not matter.
        LabelIndex reversed;
        reversed.Add(b.c_str(), 0x20);
        reversed.Add(a.c_str(), 0x10);
        CHECK(reversed.LookupLabel(a.c_str()).status == Status::Collision);
        CHECK(reversed.LookupLabel(b.c_str()).status == Status::Collision);
    }

    void TestLookupLabelDetectsAForeignLabelOnTheSameHash()
    {
        // The index holds only `a`; asking for `b` (same hash, never added)
        // must not answer with a's object.
        std::string a, b;
        CHECK(FindCollidingLabels(a, b));
        LabelIndex index;
        index.Add(a.c_str(), 0x10);
        CHECK(index.LookupLabel(a.c_str()).status == Status::Unique);
        CHECK(index.LookupLabel(b.c_str()).status == Status::Collision);
    }

    void TestOverlongLabelsAreIgnored()
    {
        LabelIndex index;
        index.Add(std::string(kMaxLabelLength + 1, 'z').c_str(), 0x10);
        CHECK(index.Size() == 0);
    }

    void TestClearForgetsEverything()
    {
        LabelIndex index;
        index.Add("x", 0x10);
        index.Clear();
        CHECK(index.Size() == 0);
        CHECK(index.CollisionCount() == 0);
        CHECK(index.Lookup(MakeReservedId("x")).status == Status::Unknown);
    }
}

int main()
{
    TestHashIsFnv1aAndPinned();
    TestReservedIdsNeverLookLikeRealOnes();
    TestCarriableLabels();
    TestUniqueLabelRoundTrips();
    TestLookupIgnoresTheReservedBit();
    TestSameLabelOnTwoObjectsIsAmbiguous();
    TestHashCollisionDisablesBothLabels();
    TestLookupLabelDetectsAForeignLabelOnTheSameHash();
    TestOverlongLabelsAreIgnored();
    TestClearForgetsEverything();
    return OpenShimTest::ExitCode();
}
