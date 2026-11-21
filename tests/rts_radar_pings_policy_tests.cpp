// RtsRadarPings' engine-independent logic: the radar projection with the
// native rim clamp, ping timing and alpha, the queue and the clock reset.
#include "rts_radar_pings_policy.h"
#include "test_check.h"

#include <cmath>

using namespace BZROpenShim::RtsRadarPings;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-4f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    // Looking along +z (front), +x to the right, +y up; range 500, centre
    // (275,170), radius 245: the stock layout.
    Radar StockRadar()
    {
        Radar radar;
        radar.userPos[0] = 100.0f;
        radar.userPos[1] = 10.0f;
        radar.userPos[2] = -50.0f;
        radar.range = 500.0f;
        radar.right[0] = 1.0f;
        radar.up[1] = 1.0f;
        radar.front[2] = 1.0f;
        radar.projRadius = 245;
        radar.centreX = 275;
        radar.centreY = 170;
        return radar;
    }

    void ProjectTests()
    {
        const Radar radar = StockRadar();
        const float here[3] = {100.0f, 10.0f, -50.0f};
        Projected p = Project(radar, here);
        Check(p.valid && !p.clamped && p.x == 275 && p.y == 170, "the user's own position is the radar centre");

        const float right[3] = {200.0f, 10.0f, -50.0f}; // d = (100,0,0)
        p = Project(radar, right);
        Check(p.valid && p.x > 275 && p.y == 170, "a point to the right lands right of centre");
        const float left[3] = {0.0f, 10.0f, -50.0f};
        p = Project(radar, left);
        Check(p.valid && p.x < 275 && p.y == 170, "a point to the left lands left of centre");
        const float up[3] = {100.0f, 110.0f, -50.0f};
        p = Project(radar, up);
        Check(p.valid && p.x == 275 && p.y < 170, "a point above lands higher on screen (smaller y)");
        const float down[3] = {100.0f, -90.0f, -50.0f};
        p = Project(radar, down);
        Check(p.valid && p.x == 275 && p.y > 170, "a point below lands lower on screen (larger y)");

        // s = 245*5 / (500*5 + 0) = 0.49; 100 * 0.49 = 49.
        p = Project(radar, right);
        Check(p.x == 275 + 49, "projector scale matches s = r*5/(range*5+z)");

        // Depth: a point ahead is pulled in, one behind pushed out.
        const float ahead[3] = {200.0f, 10.0f, 50.0f};  // z = +100
        const float behind[3] = {200.0f, 10.0f, -150.0f}; // z = -100
        Check(Project(radar, ahead).x < Project(radar, behind).x, "depth perspective follows the stock projector");
    }

    void ClampTests()
    {
        const Radar radar = StockRadar();
        const float far[3] = {100.0f + 3000.0f, 10.0f, -50.0f};
        const float edge[3] = {100.0f + 500.0f, 10.0f, -50.0f};
        const Projected clamped = Project(radar, far);
        const Projected rim = Project(radar, edge);
        Check(clamped.valid && clamped.clamped, "a far point is flagged as clamped");
        Check(rim.valid && !rim.clamped, "a point at exactly the range is not clamped");
        Check(clamped.x == rim.x && clamped.y == rim.y, "a clamped point lands on the same rim as one at exactly range");

        const float diag[3] = {100.0f + 2000.0f, 10.0f + 1500.0f, -50.0f + 900.0f};
        const float len = std::sqrt(2000.0f * 2000.0f + 1500.0f * 1500.0f + 900.0f * 900.0f);
        const float k = 500.0f / len;
        const float onRim[3] = {100.0f + 2000.0f * k, 10.0f + 1500.0f * k, -50.0f + 900.0f * k};
        const Projected a = Project(radar, diag);
        const Projected b = Project(radar, onRim);
        Check(a.valid && b.valid && std::abs(a.x - b.x) <= 1 && std::abs(a.y - b.y) <= 1,
              "a clamped diagonal point matches the rim point along the same ray");

        Radar bad = radar;
        bad.range = 0.0f;
        Check(!Project(bad, far).valid, "zero range is refused");
        const float nan[3] = {std::nanf(""), 0.0f, 0.0f};
        Check(!Project(radar, nan).valid, "a NaN position is refused");
    }

    void TimingTests()
    {
        Check(Evaluate(0.0f).alive && Near(Evaluate(0.0f).alpha, 1.0f) && Near(Evaluate(0.0f).radiusFrac, 0.04f),
              "a new ping starts opaque at the small radius");
        const Frame mid = Evaluate(kDuration * 0.5f);
        Check(mid.alive && Near(mid.alpha, 0.5f) && Near(mid.radiusFrac, 0.09f), "halfway: half alpha, middle radius");
        const Frame late = Evaluate(kDuration - 0.001f);
        Check(late.alive && late.alpha < 0.01f && Near(late.radiusFrac, 0.14f, 1e-3f), "just before the end: nearly clear, full radius");
        Check(!Evaluate(kDuration).alive && !Evaluate(5.0f).alive, "a finished ping is not alive");
        Check(!Evaluate(-0.1f).alive && !Evaluate(std::nanf("")).alive, "negative or NaN age is not alive");
        Check(RadiusPixels(0.04f, 245) > 9.0f && Near(RadiusPixels(0.04f, 245), 9.8f, 1e-3f), "radius scales with the projection radius");
        Check(Near(RadiusPixels(0.04f, 20), 3.0f), "radius never drops below 3 px");

        int x0 = 0, y0 = 0, x12 = 0, y12 = 0, x3 = 0, y3 = 0;
        RingPoint(100, 100, 10.0f, 0, x0, y0);
        RingPoint(100, 100, 10.0f, kRingSegments, x12, y12);
        RingPoint(100, 100, 10.0f, 3, x3, y3);
        Check(x0 == 110 && y0 == 100, "ring point 0 is at angle 0");
        Check(x12 == x0 && y12 == y0, "the last ring point closes the ring");
        Check(x3 == 100 && y3 == 110, "a quarter turn is 3 of 12 segments");
    }

    void QueueTests()
    {
        RadarPingQueue queue;
        for (int i = 0; i < 10; ++i)
        {
            Ping ping;
            ping.birth = 1.0f + 0.01f * static_cast<float>(i);
            ping.pos[0] = static_cast<float>(i);
            queue.Push(ping);
        }
        Check(queue.Prune(1.2f) == kMaxPings, "the queue holds at most 8 pings");
        bool hasOldest = false, hasNewest = false;
        for (size_t i = 0; i < kMaxPings; ++i)
        {
            Ping ping;
            if (!queue.Get(i, ping))
                continue;
            hasOldest |= ping.pos[0] == 0.0f || ping.pos[0] == 1.0f;
            hasNewest |= ping.pos[0] == 9.0f;
        }
        Check(!hasOldest && hasNewest, "overflow replaces the oldest pings");
        Check(queue.Prune(1.0f + kDuration + 0.05f) < kMaxPings, "old pings expire");
        Check(queue.Prune(10.0f) == 0, "everything expires");

        Ping ping;
        ping.birth = 500.0f;
        queue.Push(ping);
        Check(queue.Prune(501.0f) == 1, "a live ping is kept");
        Check(queue.Prune(3.0f) == 0, "a ping born after now (clock reset) is dropped");
        queue.Push(ping);
        queue.Clear();
        Check(queue.Prune(500.5f) == 0, "Clear empties the queue");
    }
}

int main()
{
    ProjectTests();
    ClampTests();
    TimingTests();
    QueueTests();
    return OpenShimTest::ExitCode();
}
