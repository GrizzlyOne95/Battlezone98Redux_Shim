// Tests for the classLabel=tracked multiplayer helpers (include/tracked_vehicle_net.h).

#include "tracked_vehicle_net.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::TrackedNet;
    namespace TU = BZROpenShim::TrackedTurret;

    void CheckNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            OpenShimTest::Fail("%s (actual=%.6f expected=%.6f)", message, actual, expected);
        }
    }

    void TestPackRoundTrip()
    {
        TurretRecord in[2];
        in[0].id = 0x00030017u;
        in[0].delta = -1.25f;
        in[0].rate = 0.75f;
        in[1].id = 0x00010002u;
        in[1].delta = 2.0f;
        in[1].rate = -0.5f;
        uint8_t buf[kMaxPacketLen];
        const unsigned len = Pack(in, 2, buf);
        Check(len == kHeaderLen + 2 * kRecordLen, "two records: 28 bytes");
        Check(buf[0] == 'T' && buf[1] == 'Y', "tag bytes are T,Y");
        uint16_t tag = 0;
        std::memcpy(&tag, buf, sizeof(tag));
        Check(tag == kTagTurret, "tag reads as kTagTurret little-endian");
        Check(buf[2] == kVersion && buf[3] == 2, "version and count");

        TurretBatch out;
        Check(Unpack(buf, len, out) == UnpackResult::Ok, "round trip unpacks");
        Check(out.count == 2 && out.rejected == 0, "both records come back");
        for (unsigned i = 0; i < 2; ++i)
        {
            Check(out.records[i].id == in[i].id, "id round trips");
            CheckNear(out.records[i].delta, in[i].delta, 0.0, "delta round trips");
            CheckNear(out.records[i].rate, in[i].rate, 0.0, "rate round trips");
        }

        Check(Pack(in, 0, buf) == 0, "no records, no packet");
        TurretRecord many[kMaxRecords + 3];
        for (unsigned i = 0; i < kMaxRecords + 3; ++i)
            many[i].id = i + 1;
        Check(Pack(many, kMaxRecords + 3, buf) == kMaxPacketLen, "pack caps at kMaxRecords");
        Check(buf[3] == kMaxRecords, "capped count");
        Check(kMaxPacketLen <= 244, "a full batch stays under the smallest send-size estimate");
    }

    void TestUnpackRejects()
    {
        TurretRecord good;
        good.id = 7;
        good.delta = 0.5f;
        good.rate = 1.0f;
        uint8_t buf[kMaxPacketLen];
        TurretBatch out;

        unsigned len = Pack(&good, 1, buf);
        Check(Unpack(buf, kHeaderLen - 1, out) == UnpackResult::NotOurs, "shorter than a header is not ours");
        Check(Unpack(nullptr, len, out) == UnpackResult::NotOurs, "null buffer is not ours");
        Check(Unpack(buf, len - 1, out) == UnpackResult::Invalid, "truncated record is invalid");
        buf[3] = 0;
        Check(Unpack(buf, len, out) == UnpackResult::Invalid, "count 0 is invalid");
        buf[3] = kMaxRecords + 1;
        Check(Unpack(buf, kMaxPacketLen, out) == UnpackResult::Invalid, "count over the cap is invalid");
        buf[3] = 1;
        buf[2] = 2;
        Check(Unpack(buf, len, out) == UnpackResult::NotOurs, "another version is not ours");
        buf[2] = kVersion;
        buf[1] = 'X';
        Check(Unpack(buf, len, out) == UnpackResult::NotOurs, "another tag is not ours");

        // Bad records are skipped; the good ones in the same batch survive.
        TurretRecord recs[7];
        for (TurretRecord& r : recs)
            r = good;
        recs[0].id = 0;
        recs[1].delta = NAN;
        recs[2].delta = 3.5f;
        recs[3].rate = INFINITY;
        recs[4].rate = -50.0f;
        recs[5].delta = TU::kPi;
        recs[5].rate = -TU::kMaxYawRate;
        recs[6].id = 99;
        len = Pack(recs, 7, buf);
        Check(Unpack(buf, len, out) == UnpackResult::Ok, "mixed batch unpacks");
        Check(out.count == 2 && out.rejected == 5, "five bad records skipped, two kept");
        Check(out.records[0].id == 7 && out.records[1].id == 99, "pi, the largest rate and a normal record kept");
    }

    void TestSendBatch()
    {
        SendBatch b;
        int a = 0, c = 0;
        Check(!b.NoteVisit(&a), "first visit: same frame");
        Check(!b.NoteVisit(&c), "another object: same frame");
        Check(b.NoteVisit(&a), "a second visit is a new frame");
        b.Reset();
        Check(!b.NoteVisit(&a), "after the reset the frame starts again");

        TurretRecord r;
        r.id = 1;
        for (unsigned i = 0; i < kMaxRecords; ++i)
            Check(b.Add(r), "fits under the cap");
        Check(!b.Add(r), "full batch refuses");
        b.ClearRecords();
        Check(b.count == 0 && b.visitedCount == 1, "clearing records keeps the visits");
        Check(b.Add(r), "adds after a flush");

        SendBatch full;
        static int objs[SendBatch::kMaxVisited];
        for (unsigned i = 0; i < SendBatch::kMaxVisited; ++i)
            Check(!full.NoteVisit(&objs[i]), "distinct objects fill the visit list");
        int extra = 0;
        Check(full.NoteVisit(&extra), "a full visit list forces a flush");
    }

    void TestReceivedTable()
    {
        static ReceivedTable t;
        ReceivedTurret out;
        Check(!t.Lookup(5, 0, kStaleMs, out), "empty table finds nothing");
        t.Store(5, 0.5f, 1.0f, 1000);
        Check(t.Lookup(5, 1000 + kStaleMs, kStaleMs, out), "found within the age");
        CheckNear(out.delta, 0.5, 0.0, "stored delta");
        Check(!t.Lookup(5, 1001 + kStaleMs, kStaleMs, out), "too old is not found");
        Check(!t.Lookup(5, 999, kStaleMs, out), "a future entry is not found");
        Check(!t.Lookup(5, 1000 + kRateMaxAgeMs + 1, kRateMaxAgeMs, out), "rate age gate is shorter");
        t.Store(5, -0.5f, 0.0f, 2000);
        Check(t.Lookup(5, 2000, kStaleMs, out) && out.delta == -0.5f, "update in place");
        t.Store(0, 1.0f, 1.0f, 2000);
        Check(!t.Lookup(0, 2000, kStaleMs, out), "id 0 is never stored");

        // Full: the oldest entry is replaced.
        t.Clear();
        for (uint32_t i = 1; i <= ReceivedTable::kSlots; ++i)
            t.Store(i, 0.0f, 0.0f, 100 + i);
        t.Store(9999, 0.25f, 0.0f, 5000);
        Check(!t.Lookup(1, 5000, kStaleMs, out), "oldest entry evicted");
        Check(t.Lookup(2, 5000, kStaleMs, out), "next oldest kept");
        Check(t.Lookup(9999, 5000, kStaleMs, out), "new entry stored");
        t.Clear();
        Check(!t.Lookup(9999, 5000, kStaleMs, out), "clear empties the table");
    }

    void TestSendPolicy()
    {
        SendState s;
        Check(ShouldSend(s, 0.0f, 0.0f, 1000), "first send goes out");
        MarkSent(s, 0.0f, 0.0f, 1000);

        Check(!ShouldSend(s, 1.0f, 2.0f, 1000 + kMinSendIntervalMs - 1), "a change waits for the interval");
        Check(ShouldSend(s, 1.0f, 0.0f, 1000 + kMinSendIntervalMs), "a delta change goes after the interval");
        Check(ShouldSend(s, 0.0f, 0.2f, 1000 + kMinSendIntervalMs), "a rate change goes after the interval");
        Check(!ShouldSend(s, 0.005f, 0.01f, 1000 + kMinSendIntervalMs), "a small change is held");
        Check(!ShouldSend(s, 0.0f, 0.0f, 1000 + kRefreshMs - 1), "no change, no send before the refresh");
        Check(ShouldSend(s, 0.0f, 0.0f, 1000 + kRefreshMs), "refresh after a second");

        // Across the +-pi seam the change is the short way round.
        SendState seam;
        MarkSent(seam, TU::kPi - 0.002f, 0.0f, 0);
        Check(!ShouldSend(seam, -TU::kPi + 0.002f, 0.0f, kMinSendIntervalMs), "seam crossing is a small change");

        // At most one send per interval while the turret keeps slewing.
        SendState slew;
        int sends = 0;
        for (uint64_t t = 0; t <= 2000; t += 16)
        {
            const float delta = 0.001f * static_cast<float>(t);
            if (ShouldSend(slew, delta, 1.0f, t))
            {
                MarkSent(slew, delta, 1.0f, t);
                ++sends;
            }
        }
        Check(sends <= static_cast<int>(2000 / kMinSendIntervalMs) + 1, "slewing is rate limited");
        Check(sends >= 8, "slewing still sends about five a second");
    }

    void TestReplicaTarget()
    {
        const TU::Config free = TU::Sanitize(TU::Config{});
        CheckNear(ReplicaTarget(free, 0.5f, 1.0f, 0.1f), 0.6, 1e-6, "extrapolates by the rate");
        CheckNear(ReplicaTarget(free, 0.5f, 1.0f, 10.0f), 0.5 + kMaxExtrapolateSeconds, 1e-6,
                  "extrapolation is capped");
        CheckNear(ReplicaTarget(free, 0.5f, 1.0f, -1.0f), 0.5, 1e-6, "negative age is no extrapolation");
        CheckNear(ReplicaTarget(free, TU::kPi - 0.05f, 1.0f, 0.1f), -TU::kPi + 0.05, 1e-5, "wraps at pi");

        TU::Config raw;
        raw.yawMin = -1.0f;
        raw.yawMax = 1.0f;
        const TU::Config limited = TU::Sanitize(raw);
        CheckNear(ReplicaTarget(limited, 0.95f, 2.0f, 0.2f), 1.0, 1e-6, "limited target is clamped");
    }

    void TestSlewToward()
    {
        TU::Config raw;
        raw.yawRate = 1.0f;
        const TU::Config free = TU::Sanitize(raw);
        const float dt = 0.1f;
        const float maxStep = kCatchUpFactor * 1.0f * dt;
        CheckNear(SlewToward(free, 0.0f, 1.0f, dt), maxStep, 1e-6, "slews at the catch-up rate");
        CheckNear(SlewToward(free, 0.0f, 0.05f, dt), 0.05, 1e-6, "reaches a close target");
        CheckNear(SlewToward(free, 0.0f, -1.0f, dt), -maxStep, 1e-6, "slews the other way");
        // Short way round the seam: from 3.0 to -3.0 is +0.28 rad, not -6.
        const float across = SlewToward(free, 3.0f, -3.0f, dt);
        CheckNear(TU::WrapAngle(across - 3.0f), maxStep, 1e-5, "takes the short way across pi");
        CheckNear(SlewToward(free, 0.4f, 1.0f, 0.0f), 0.4, 1e-6, "no time, no move");
        CheckNear(SlewToward(free, 0.4f, NAN, dt), 0.4, 1e-6, "NaN target holds");

        // Converges, and per-frame stepping does not depend on how the frame
        // was split: the same total time reaches the same place.
        float a = 0.0f;
        for (int i = 0; i < 100; ++i)
            a = SlewToward(free, a, 1.5f, 0.016f);
        CheckNear(a, 1.5, 1e-5, "converges on the target");

        TU::Config lraw;
        lraw.yawRate = 1.0f;
        lraw.yawMin = -1.0f;
        lraw.yawMax = 1.0f;
        const TU::Config limited = TU::Sanitize(lraw);
        // A limited turret never crosses the back: 0.9 -> -0.9 goes through 0.
        const float l = SlewToward(limited, 0.9f, -0.9f, dt);
        CheckNear(l, 0.9 - maxStep, 1e-6, "limited turret goes the long way inside its limits");
        CheckNear(SlewToward(limited, 0.0f, 5.0f, 10.0f), 1.0, 1e-6, "limited result stays inside");
    }

    void TestReplicaTreadSpeeds()
    {
        const Vec3 right{ 1.0f, 0.0f, 0.0f };
        const Vec3 front{ 0.0f, 0.0f, 1.0f };
        // Straight ahead at 5 m/s, no turn.
        TreadSpeeds t = ReplicaTreadSpeeds({ 0.0f, 0.0f, 5.0f }, right, front, 0.0f, 0.0f, 0.0f, 1.5f);
        CheckNear(t.left, 5.0, 1e-6, "straight: left");
        CheckNear(t.right, 5.0, 1e-6, "straight: right");
        // Pivot left at 1 rad/s: left back, right forward.
        t = ReplicaTreadSpeeds({ 0.0f, 0.0f, 0.0f }, right, front, 1.0f, 0.0f, 0.0f, 1.5f);
        CheckNear(t.left, -1.5, 1e-6, "pivot left: left tread backward");
        CheckNear(t.right, 1.5, 1e-6, "pivot left: right tread forward");
        // Turret slewing at the root's yaw rate: the hull is not turning.
        t = ReplicaTreadSpeeds({ 0.0f, 0.0f, 0.0f }, right, front, 0.8f, 0.0f, 0.8f, 1.5f);
        CheckNear(t.left, 0.0, 1e-6, "turret slew alone: left still");
        CheckNear(t.right, 0.0, 1e-6, "turret slew alone: right still");
        // Turret turned 90 degrees left: the root front is the hull's left,
        // so motion along the root's right is the hull driving forward.
        const float half = 0.5f * TU::kPi;
        t = ReplicaTreadSpeeds({ 4.0f, 0.0f, 0.0f }, right, front, 0.0f, half, 0.0f, 1.5f);
        CheckNear(t.left, 4.0, 1e-5, "turret 90 left: forward along the hull");
        CheckNear(t.right, 4.0, 1e-5, "turret 90 left: forward along the hull (right)");
        // Non-finite motion is still.
        t = ReplicaTreadSpeeds({ NAN, 0.0f, 0.0f }, right, front, 0.0f, half, 0.0f, 1.5f);
        CheckNear(t.left, 0.0, 0.0, "NaN veloc: left 0");
        CheckNear(t.right, 0.0, 0.0, "NaN veloc: right 0");
    }
}

int main()
{
    TestPackRoundTrip();
    TestUnpackRejects();
    TestSendPolicy();
    TestSendBatch();
    TestReceivedTable();
    TestReplicaTarget();
    TestSlewToward();
    TestReplicaTreadSpeeds();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("tracked_vehicle_net_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
