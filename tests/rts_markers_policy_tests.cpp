// RtsMarkers' engine-independent logic: ring geometry, ping classification
// and timing, the ping queue, the artillery range and reach test, the weapon
// filter and the generated assets. `--emit <dir>` writes the generated shader
// and material so the shader can be compiled with fxc by hand.
#include "rts_markers_assets.h"
#include "rts_markers_policy.h"
#include "test_check.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <string>

using namespace BZROpenShim::RtsMarkers;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-3f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void GeometryTests()
    {
        Check(SegmentsFor(1.0f) == kMinSegments, "a small ring uses the minimum segment count");
        Check(SegmentsFor(1000.0f) == kMaxSegments, "a huge ring is capped at the maximum");
        Check(SegmentsFor(0.0f) == kMinSegments && SegmentsFor(-5.0f) == kMinSegments &&
                  SegmentsFor(std::nanf("")) == kMinSegments,
              "nonsense radii fall back to the minimum");
        const unsigned mid = SegmentsFor(40.0f);
        Check(mid > kMinSegments && mid < kMaxSegments, "a medium ring lands between the bounds");
        for (float r = 0.5f; r < 2000.0f; r *= 1.7f)
        {
            const unsigned s = SegmentsFor(r);
            Check(s >= 48 && s <= 96, "segment count always within 48..96");
        }

        Check(Near(RingWidthFor(6.0f), 0.536f), "ping ring width");
        Check(Near(RingWidthFor(10000.0f), 2.5f), "width capped for huge rings");
        Check(Near(RingWidthFor(-1.0f), 0.5f), "nonsense radius gets the minimum width");

        const Band band = RingBand(10.0f, 2.0f);
        Check(Near(band.inner, 9.0f) && Near(band.outer, 11.0f), "band straddles the radius");
        const Band tiny = RingBand(0.2f, 2.0f);
        Check(Near(tiny.inner, 0.0f) && Near(tiny.outer, 1.2f), "inner radius never negative");
        const Band negative = RingBand(5.0f, -3.0f);
        Check(Near(negative.inner, 5.0f) && Near(negative.outer, 5.0f), "negative width collapses to the radius");

        Check(StripVertexCount(48) == 98 && StripVertexCount(96) == 194, "strip closes with a repeated pair");

        float x0 = 0, z0 = 0, xn = 0, zn = 0;
        RingDirection(0, 64, x0, z0);
        RingDirection(64, 64, xn, zn);
        Check(x0 == xn && z0 == zn, "the last point is exactly the first, so the strip has no seam");
        float xq = 0, zq = 0;
        RingDirection(16, 64, xq, zq);
        Check(Near(xq, 0.0f) && Near(zq, 1.0f), "a quarter turn points along +z");
        for (unsigned i = 0; i < 96; ++i)
        {
            float x = 0, z = 0;
            RingDirection(i, 96, x, z);
            Check(Near(x * x + z * z, 1.0f), "every direction is unit length");
        }
        float xz = 0, zz = 0;
        RingDirection(3, 0, xz, zz);
        Check(xz == 1.0f && zz == 0.0f, "zero segments does not divide by zero");

        Check(Near(LocalVertexY(105.0f, 100.0f), 5.0f + kLift), "vertex follows terrain relative to the node");
        Check(kLift >= 0.3f && kLift <= 0.5f, "lift is within the 0.3-0.5 m brief");
    }

    void PingClassificationTests()
    {
        Check(ClassifyPing(kCmdNone, false) == PingKind::None, "no command, no ping");
        Check(ClassifyPing(kCmdSelect, true) == PingKind::None, "select is not an order");
        Check(ClassifyPing(kCmdStop, false) == PingKind::None, "stop has no place to mark");
        Check(ClassifyPing(-1, false) == PingKind::None && ClassifyPing(27, true) == PingKind::None,
              "out-of-range values give no ping");
        Check(ClassifyPing(kCmdGo, false) == PingKind::Go, "go to a ground point is green");
        Check(ClassifyPing(kCmdGo, true) == PingKind::Go, "go to an object (nav) is green");
        Check(ClassifyPing(kCmdAttack, true) == PingKind::Attack, "attack on an object is red");
        Check(ClassifyPing(kCmdAttack, false) == PingKind::Neutral, "attack on ground is neutral");
        Check(ClassifyPing(5, true) == PingKind::Neutral, "follow is neutral");
        Check(ClassifyPing(15, true) == PingKind::Neutral, "defend is neutral");
        Check(ClassifyPing(22, false) == PingKind::Neutral, "patrol is neutral");
        Check(ClassifyPing(kCmdLast, false) == PingKind::Neutral, "the last command still pings");
    }

    void PingTimingTests()
    {
        const PingStyle go = StyleFor(PingKind::Go);
        Check(go.duration >= 0.8f && go.duration <= 1.0f, "go ping lasts 0.8-1.0 s");
        Check(go.endScale < go.startScale, "go ping shrinks");
        Check(go.colour.g > go.colour.r && go.colour.g > go.colour.b, "go ping is green");
        const PingStyle attack = StyleFor(PingKind::Attack);
        Check(Near(attack.duration, 1.0f), "attack ping lasts about 1 s");
        Check(attack.colour.r > attack.colour.g && attack.colour.r > attack.colour.b, "attack ping is red");
        const PingStyle neutral = StyleFor(PingKind::Neutral);
        Check(neutral.colour.r > 0.9f && neutral.colour.g > 0.7f && neutral.colour.b < 0.5f, "neutral is yellow");
        Check(!(StyleFor(PingKind::None).duration > 0.0f), "no style for no ping");

        const PingFrame start = EvaluatePing(go, 6.0f, 0.0f);
        Check(start.alive && Near(start.radius, 6.0f) && Near(start.alpha, go.colour.a), "full size and alpha at birth");
        const PingFrame half = EvaluatePing(go, 6.0f, go.duration * 0.5f);
        Check(half.alive && half.radius < start.radius && half.alpha < start.alpha, "shrinks and fades");
        const PingFrame late = EvaluatePing(go, 6.0f, go.duration * 0.99f);
        Check(late.alpha < 0.01f, "nearly invisible at the end");
        Check(!EvaluatePing(go, 6.0f, go.duration).alive, "dead at its duration");
        Check(!EvaluatePing(go, 6.0f, 50.0f).alive, "dead long after");
        Check(EvaluatePing(go, 6.0f, -1.0f).alive, "a negative age clamps to birth");
        Check(!EvaluatePing(go, 0.0f, 0.1f).alive, "zero radius never draws");
        Check(!EvaluatePing(go, 6.0f, std::nanf("")).alive, "NaN age never draws");

        float previousRadius = 1e9f, previousAlpha = 1e9f;
        for (int i = 0; i < 20; ++i)
        {
            const PingFrame f = EvaluatePing(go, 6.0f, go.duration * i / 20.0f);
            Check(f.radius <= previousRadius && f.alpha <= previousAlpha, "monotonic shrink and fade");
            previousRadius = f.radius;
            previousAlpha = f.alpha;
        }

        Check(Near(TargetRingRadius(10.0f), 11.0f), "target ring sits just outside the bounding radius");
        Check(Near(TargetRingRadius(0.5f), kMinTargetRadius + kTargetRingMargin), "tiny targets clamp up");
        Check(Near(TargetRingRadius(500.0f), kMaxTargetRadius + kTargetRingMargin), "huge targets clamp down");
        Check(Near(TargetRingRadius(std::nanf("")), kDefaultTargetRadius + kTargetRingMargin), "unreadable: default");
    }

    void PingQueueTests()
    {
        PingQueue<3> queue;
        Check(queue.ActiveCount() == 0, "starts empty");
        PingSlot ping;
        ping.kind = PingKind::Go;
        ping.baseRadius = 6.0f;
        Check(queue.Push(ping) == 0, "first ping takes slot 0");
        queue.Advance(0.1f);
        Check(queue.Push(ping) == 1, "second ping takes the next free slot");
        queue.Advance(0.1f);
        Check(queue.Push(ping) == 2, "third ping takes the last slot");
        Check(queue.ActiveCount() == 3, "three active");
        Check(queue.Push(ping) == 0, "a fourth replaces the oldest");
        Check(queue.slots[0].age == 0.0f && queue.slots[0].active, "the replacement starts fresh");
        queue.Advance(StyleFor(PingKind::Go).duration + 0.01f);
        Check(queue.ActiveCount() == 0, "all retire after their duration");
        queue.Advance(-1.0f);
        queue.Advance(std::nanf(""));
        Check(queue.ActiveCount() == 0, "bad dt is ignored");
        queue.Push(ping);
        queue.Clear();
        Check(queue.ActiveCount() == 0, "clear empties the queue");
    }

    void ArtilleryTests()
    {
        // No lifeSpan limit: v^2/g.
        Check(Near(FlatMaxRange(70.0f, 100.0f), 500.0f, 0.01f), "70 m/s, long life: 500 m");
        // Exactly the 45-degree flight time: still the full range.
        const float t45 = 70.0f * std::sqrt(2.0f) / kGravity;
        Check(Near(FlatMaxRange(70.0f, t45), 500.0f, 0.05f), "life equal to the 45-degree flight: full range");
        // Short life: shorter range, continuous at the boundary.
        const float shortRange = FlatMaxRange(70.0f, 5.0f);
        const double theta = std::asin(9.8 * 5.0 / (2.0 * 70.0));
        Check(Near(shortRange, static_cast<float>(4900.0 / 9.8 * std::sin(2.0 * theta)), 0.05f),
              "short life: the pitch whose flight time is the life");
        Check(shortRange < 500.0f, "short life shortens the ring");
        Check(Near(FlatMaxRange(70.0f, t45 * 0.9999f), 500.0f, 0.5f), "continuous at the 45-degree boundary");
        Check(FlatMaxRange(0.0f, 10.0f) == 0.0f && FlatMaxRange(-5.0f, 10.0f) == 0.0f, "no speed, no range");
        Check(FlatMaxRange(70.0f, 0.0f) == 0.0f, "no life, no range");
        Check(FlatMaxRange(std::nanf(""), 10.0f) == 0.0f && FlatMaxRange(70.0f, std::nanf("")) == 0.0f,
              "NaN inputs give no range");

        // Reach on flat ground matches the ring, both with and without the
        // lifeSpan limit.
        for (const float life : {100.0f, 5.0f, 2.0f})
        {
            const float r = FlatMaxRange(70.0f, life);
            Check(CanReach(70.0f, life, r * 0.99f, 0.0f), "just inside the flat ring is reachable");
            Check(!CanReach(70.0f, life, r * 1.01f, 0.0f), "just outside the flat ring is not");
        }
        Check(CanReach(70.0f, 100.0f, 0.0f, 0.0f), "the shooter's own spot is reachable");
        // Height: downhill reaches farther, uphill less far.
        Check(CanReach(70.0f, 100.0f, 520.0f, -50.0f), "downhill extends the reach");
        Check(!CanReach(70.0f, 100.0f, 480.0f, 60.0f), "uphill shortens the reach");
        Check(CanReach(70.0f, 100.0f, 400.0f, 60.0f), "uphill but close enough");
        // Straight up: max height v^2 / 2g = 250 m.
        Check(CanReach(70.0f, 100.0f, 0.0f, 249.0f) && !CanReach(70.0f, 100.0f, 0.0f, 251.0f),
              "vertical reach is v^2 / 2g");
        Check(!CanReach(0.0f, 100.0f, 10.0f, 0.0f), "no speed, no reach");
        Check(!CanReach(70.0f, 100.0f, std::nanf(""), 0.0f), "NaN distance is unreachable");
        Check(CanReach(70.0f, 0.0f, 400.0f, 0.0f), "no lifeSpan means no time limit in the reach test");
        Check(CanReach(70.0f, 100.0f, -400.0f, 0.0f), "distance sign does not matter");

        // The engine's own form: (v^2 - 9.8 dy)^2 - 4 * 24.01 * d^2 * (1 + dy^2/d^2).
        const float v = 55.0f, d = 250.0f, dy = 20.0f;
        const double a = v * v - 9.8 * dy;
        const double engine = a * a - 4.0 * 24.01 * (d * d) * (1.0 + (dy * dy) / (d * d));
        Check((engine >= 0.0) == CanReach(v, 100.0f, d, dy), "same verdict as the engine discriminant");
    }

    void WeaponFilterTests()
    {
        const uint32_t mort = 0x4D4F5254, cann = 0x43414E4E, gren = 0x4752454E, bull = 0x4C4C5542;
        Check(IsArtilleryWeapon(mort, gren), "mortar with grenade ordnance (howitzer)");
        Check(IsArtilleryWeapon(cann, gren), "cannon with grenade ordnance");
        Check(IsArtilleryWeapon(mort, 0x53424D42) && IsArtilleryWeapon(mort, 0x42424D42) &&
                  IsArtilleryWeapon(mort, 0x504F5052),
              "the other ballistic ordnance classes");
        Check(!IsArtilleryWeapon(cann, bull), "a cannon firing straight shells is not artillery");
        Check(!IsArtilleryWeapon(0x47554E4D, gren), "grenade ordnance from a non-pitch weapon is not artillery");
        Check(!IsArtilleryWeapon(0, 0), "nothing is not artillery");

        Check(ShouldDraw(true, false), "on and HUD shown: draw");
        Check(!ShouldDraw(true, true), "hidden HUD hides the markers");
        Check(!ShouldDraw(false, false), "option off: nothing");
    }

    void PoolTests()
    {
        Check(kMaxArtilleryRings == 16, "about 16 artillery rings");
        Check(kCursorSlot == kMaxArtilleryRings && kFirstPingSlot == kCursorSlot + 1, "slot layout");
        Check(kPoolSize == kMaxArtilleryRings + 1 + kMaxPings, "pool holds every ring at once");
    }

    void AssetTests()
    {
        const std::string material = MaterialScript();
        const std::string shader = ShaderSource();
        Check(IsGeneratedText(material) && IsGeneratedText(shader), "generated assets carry the marker");
        Check(!IsGeneratedText("material foo {}"), "user files are not ours");
        Check(material.find(std::string("material ") + kMaterialName) != std::string::npos, "material name");
        Check(material.find("scene_blend alpha_blend") != std::string::npos, "alpha blended");
        Check(material.find("depth_write off") != std::string::npos, "no depth write");
        Check(material.find("depth_check on") != std::string::npos, "depth tested");
        Check(material.find("lighting off") != std::string::npos, "unlit");
        Check(material.find("target vs_4_0") != std::string::npos && material.find("target ps_4_0") != std::string::npos,
              "SM4 technique for DX11");
        Check(material.find("fog_override true none") != std::string::npos, "DX9 fixed-function technique");
        Check(material.find(kShaderFile) != std::string::npos, "material points at the shader");
        Check(shader.find("rtsmarker_vertex") != std::string::npos && shader.find("rtsmarker_fragment") != std::string::npos,
              "both entry points");
        Check(shader.find("COLOR0") != std::string::npos, "vertex colour carried through");
    }

    void Emit(const std::filesystem::path& dir)
    {
        std::filesystem::create_directories(dir);
        std::ofstream(dir / kShaderFile, std::ios::binary) << ShaderSource();
        std::ofstream(dir / kMaterialFile, std::ios::binary) << MaterialScript();
    }
}

int main(int argc, char** argv)
{
    if (argc == 3 && std::string(argv[1]) == "--emit")
    {
        Emit(argv[2]);
        return 0;
    }
    GeometryTests();
    PingClassificationTests();
    PingTimingTests();
    PingQueueTests();
    ArtilleryTests();
    WeaponFilterTests();
    PoolTests();
    AssetTests();
    return OpenShimTest::ExitCode();
}
