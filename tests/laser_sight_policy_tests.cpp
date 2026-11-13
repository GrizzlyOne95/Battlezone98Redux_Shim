// LaserSight's engine-independent logic: the enable gate, the export mode,
// the selected slot, the terrain march, the ray/box test, the beam transform
// and the generated assets. `--emit <dir>` writes the generated shader and
// material so scripts can compile the shader with fxc.
#include "laser_sight_assets.h"
#include "laser_sight_policy.h"
#include "test_check.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>

using namespace BZROpenShim::LaserSight;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-3f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void GateTests()
    {
        // option x netgame x mode -> on/off, all eight combinations.
        Check(!Enabled(false, false, 0), "option off, single player: off");
        Check(!Enabled(false, false, 1), "option off wins over the override");
        Check(!Enabled(false, true, 0), "option off, network game: off");
        Check(!Enabled(false, true, 1), "option off wins over the override in a network game");
        Check(Enabled(true, false, 0), "option on, single player: on");
        Check(Enabled(true, false, 1), "option on, single player, override: on");
        Check(!Enabled(true, true, 0), "network game closes the gate by default");
        Check(Enabled(true, true, 1), "override allows the beam in a network game");
        Check(!Enabled(true, true, 2) && !Enabled(true, true, -1), "unknown modes never open the gate");

        Check(IsValidMode(0) && IsValidMode(1), "both documented modes are accepted");
        Check(!IsValidMode(-1) && !IsValidMode(2) && !IsValidMode(1000), "other modes are rejected");
    }

    void SlotTests()
    {
        Check(FirstSelectedSlot(0) == -1, "no selection");
        Check(FirstSelectedSlot(1) == 0 && FirstSelectedSlot(4) == 2 && FirstSelectedSlot(16) == 4, "single slot");
        Check(FirstSelectedSlot(0x6) == 1, "linked weapons: lowest selected slot");
        Check(FirstSelectedSlot(0x20) == -1 && FirstSelectedSlot(0x80000000u) == -1, "only slots 0..4 exist");
    }

    void TerrainTests()
    {
        const TerrainMarch march;
        int samples = 0;
        // Flat ground at y = 0, muzzle 2 m up, pointing 1 in 10 down: the
        // ground is met where 2 - 0.1 * d * |dir| reaches 0.
        auto flat = [&](float, float, float& out) {
            ++samples;
            out = 0.0f;
            return true;
        };
        const float l = std::sqrt(1.0f + 0.01f);
        const Vec3 down = {1.0f / l, -0.1f / l, 0.0f};
        float t = 0.0f;
        Check(MarchTerrain(Vec3{0, 2, 0}, down, 500.0f, march, flat, t), "sloping ray meets flat ground");
        const float expected = 20.0f * l;
        Check(std::fabs(t - expected) <= march.coarseStep / 32.0f && t >= expected - 1e-3f,
              "refined crossing within 1/64 of a step, never short of the ground");
        Check(samples <= 1 + static_cast<int>(expected / march.coarseStep) + 1 + march.refineIterations,
              "coarse steps up to the crossing plus the refinement only");

        samples = 0;
        Check(!MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, flat, t), "level ray never meets the ground");
        Check(samples == 1 + static_cast<int>(500.0f / march.coarseStep) + 1,
              "a miss costs maxDistance / coarseStep samples");

        Check(MarchTerrain(Vec3{0, -1, 0}, Vec3{1, 0, 0}, 500.0f, march, flat, t) && t == 0.0f,
              "a buried muzzle hits at once");

        // A 4 m ridge at x = 100: met on its face.
        auto ridge = [](float x, float, float& out) {
            out = (x > 100.0f && x < 104.0f) ? 4.0f : 0.0f;
            return true;
        };
        Check(!MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, ridge, t),
              "a ridge narrower than the coarse step between samples is missed (documented limit)");
        auto wideRidge = [](float x, float, float& out) {
            out = x > 100.0f ? 4.0f : 0.0f;
            return true;
        };
        Check(MarchTerrain(Vec3{0, 2, 0}, Vec3{1, 0, 0}, 500.0f, march, wideRidge, t) && t > 100.0f &&
                  t < 100.0f + march.coarseStep / 32.0f,
              "a cliff face is located within the refinement");

        auto unsampled = [](float x, float, float& out) {
            out = 0.0f;
            return x < 10.0f; // the slope meets the ground at x = 20
        };
        Check(!MarchTerrain(Vec3{0, 2, 0}, down, 500.0f, march, unsampled, t), "no terrain sample before the crossing: no terrain hit");
        Check(!MarchTerrain(Vec3{0, 2, 0}, down, 0.0f, march, flat, t), "zero length never hits");
    }

    void RayObbTests()
    {
        Obb box;
        box.center = {50, 0, 0};
        box.half = {2, 2, 2};
        float t = 0.0f;
        Check(RayObb({0, 0, 0}, {1, 0, 0}, box, 500.0f, t) && Near(t, 48.0f), "axis-aligned entry distance");
        Check(!RayObb({0, 0, 0}, {1, 0, 0}, box, 40.0f, t), "box beyond the beam length is missed");
        Check(!RayObb({0, 3, 0}, {1, 0, 0}, box, 500.0f, t), "parallel ray outside the slab is missed");
        Check(!RayObb({0, 0, 0}, {-1, 0, 0}, box, 500.0f, t), "box behind the muzzle is missed");
        Check(RayObb({50, 0, 0}, {1, 0, 0}, box, 500.0f, t) && t == 0.0f, "origin inside reports 0");

        // Rotated 45 degrees about Y: the corner points at the muzzle.
        const float c = std::sqrt(0.5f);
        box.axis[0] = {c, 0, -c};
        box.axis[1] = {0, 1, 0};
        box.axis[2] = {c, 0, c};
        Check(RayObb({0, 0, 0}, {1, 0, 0}, box, 500.0f, t) && Near(t, 50.0f - 2.0f * std::sqrt(2.0f)),
              "oriented box entry at its corner");
    }

    void SegmentTests()
    {
        Check(SegmentCount(0.0f) == 0 && SegmentCount(-1.0f) == 0, "no beam, no segments");
        Check(SegmentCount(1.0f) == 1 && SegmentCount(50.0f) == 1 && SegmentCount(50.5f) == 2, "segment rounding");
        Check(SegmentCount(kMaxBeamLength) == 10, "a full beam is ten grid queries at most");
    }

    void TransformTests()
    {
        const BeamTransform t = MakeBeamTransform({1, 2, 3}, {0, 0, 1}, {0, 1, 0}, 120.0f, 0.05f);
        Check(t.position[0] == 1.0f && t.position[1] == 2.0f && t.position[2] == 3.0f, "beam starts at the muzzle");
        Check(Near(t.orientation[0], 1.0f) && Near(t.orientation[1], 0.0f) && Near(t.orientation[2], 0.0f) &&
                  Near(t.orientation[3], 0.0f),
              "local +Z along the beam: identity for a +Z beam");
        Check(t.scale[0] == 0.05f && t.scale[1] == 0.05f && t.scale[2] == 120.0f, "radius across, length along");

        const BeamTransform x = MakeBeamTransform({0, 0, 0}, {1, 0, 0}, {0, 1, 0}, 10.0f, 0.05f);
        const Quat q = {x.orientation[0], x.orientation[1], x.orientation[2], x.orientation[3]};
        const Vec3 axis = BZROpenShim::ShellCasings::Rotate(q, {0, 0, 1});
        Check(Near(axis.x, 1.0f) && Near(axis.y, 0.0f) && Near(axis.z, 0.0f), "mesh +Z maps onto the beam direction");
        Check(MakeBeamTransform({0, 0, 0}, {1, 0, 0}, {0, 1, 0}, 0.0f, 0.05f).scale[2] > 0.0f,
              "never a zero scale");
    }

    void BallisticSigTests()
    {
        // The engine stores the signature as a little-endian int: 'GREN'.
        Check(kOrdnanceSigGrenade == ((uint32_t('G') << 24) | (uint32_t('R') << 16) | (uint32_t('E') << 8) | 'N'),
              "grenade signature spells GREN");
        Check(IsBallisticOrdnance(kOrdnanceSigGrenade) && IsBallisticOrdnance(kOrdnanceSigSprayBomb) &&
                  IsBallisticOrdnance(kOrdnanceSigBounceBomb) && IsBallisticOrdnance(kOrdnanceSigPopper),
              "the four gravity ordnance classes take the arc");
        Check(!IsBallisticOrdnance(0) && !IsBallisticOrdnance(0x42554C4Cu /* 'BULL' */) &&
                  !IsBallisticOrdnance(kWeaponSigMortar),
              "anything else keeps the straight beam");
        Check(AppliesShotPitch(kWeaponSigMortar) && AppliesShotPitch(kWeaponSigCannon), "mortar and cannon pitch");
        Check(!AppliesShotPitch(0) && !AppliesShotPitch(kOrdnanceSigGrenade), "other weapon classes fire level");
    }

    // The engine's mean shot: Cannon::Simulate composes R(yaw 0, pitch
    // -shotPitch) from 0x0081ED60 onto the muzzle (row vectors, child left).
    // That matrix's front row is (sinA cosB, -sinB, cosA cosB).
    Vec3 EngineMeanShot(Vec3 right, Vec3 up, Vec3 front, float shotPitch)
    {
        const float a = 0.0f, b = -shotPitch;
        const Vec3 local = {std::sin(a) * std::cos(b), -std::sin(b), std::cos(a) * std::cos(b)};
        return {local.x * right.x + local.y * up.x + local.z * front.x,
                local.x * right.y + local.y * up.y + local.z * front.y,
                local.x * right.z + local.y * up.z + local.z * front.z};
    }

    void PitchTests()
    {
        const Vec3 f = {0, 0, 1}, u = {0, 1, 0};
        Vec3 d = PitchedFireDirection(f, u, 0.0f);
        Check(Near(d.x, 0) && Near(d.y, 0) && Near(d.z, 1), "no pitch: the muzzle front");
        d = PitchedFireDirection(f, u, 0.3f);
        Check(d.y > 0.0f && Near(d.y, std::sin(0.3f)) && Near(d.z, std::cos(0.3f)), "positive shotPitch aims up");
        d = PitchedFireDirection(f, u, -0.2f);
        Check(d.y < 0.0f, "negative shotPitch aims down");
        Check(Near(BZROpenShim::ShellCasings::Length(PitchedFireDirection(f, u, 1.1f)), 1.0f), "unit direction");

        // A rolled and yawed muzzle: same answer as the engine composition.
        const float c = std::cos(0.7f), s = std::sin(0.7f);
        const Vec3 right = {c, s, 0}, up = {-s, c, 0}, front = {0, 0, 1};
        const Vec3 yawRight = {right.x * c - front.x * s, right.y * c - front.y * s, right.z * c - front.z * s};
        const Vec3 yawFront = {right.x * s + front.x * c, right.y * s + front.y * c, right.z * s + front.z * c};
        const Vec3 engine = EngineMeanShot(yawRight, up, yawFront, 0.25f);
        d = PitchedFireDirection(yawFront, up, 0.25f);
        Check(Near(d.x, engine.x) && Near(d.y, engine.y) && Near(d.z, engine.z),
              "matches the engine's R(0, -shotPitch) composed onto the muzzle");
    }

    void ArcPointTests()
    {
        // Grenade::Simulate: vy -= 4.9 dt; move; vy -= 4.9 dt. Integrate it
        // and compare with the closed form.
        Arc arc;
        arc.origin = {10, 5, -3};
        arc.velocity = {20, 15, 4};
        arc.lifeSpan = 10.0f;
        Vec3 p = arc.origin, v = arc.velocity;
        const float dt = 1.0f / 30.0f;
        for (int i = 0; i < 90; ++i)
        {
            v.y -= 4.9f * dt;
            p = {p.x + v.x * dt, p.y + v.y * dt, p.z + v.z * dt};
            v.y -= 4.9f * dt;
        }
        const Vec3 q = ArcPoint(arc, 90 * dt);
        Check(Near(p.x, q.x, 1e-2f) && Near(p.y, q.y, 1e-2f) && Near(p.z, q.z, 1e-2f),
              "closed form equals the engine's integrator");
        const Vec3 w = ArcVelocity(arc, 90 * dt);
        Check(Near(w.y, v.y, 1e-3f) && w.x == arc.velocity.x, "velocity: only y changes");
    }

    // Flat ground at y = 0.
    bool Flat(float, float, float& out)
    {
        out = 0.0f;
        return true;
    }

    float LandingTime(float y0, float vy)
    {
        return (vy + std::sqrt(vy * vy + 4.0f * kHalfGravity * y0)) / (2.0f * kHalfGravity);
    }

    void MarchArcTests()
    {
        const ArcMarch march;
        const auto noObjects = [](const ArcSample*, int, float&) { return false; };
        const float k = std::sqrt(0.5f);

        Arc arc;
        arc.origin = {0, 2, 0};
        arc.velocity = {30 * k, 30 * k, 0};
        arc.lifeSpan = 1e30f; // stock grenade.odf
        int samples = 0;
        auto flat = [&](float x, float z, float& out) {
            ++samples;
            return Flat(x, z, out);
        };
        ArcResult r = MarchArc(arc, march, flat, noObjects);
        const float landing = LandingTime(2.0f, 30 * k);
        Check(r.end == ArcEnd::Terrain, "a mortar shot lands on flat ground");
        Check(r.endT >= landing - 1e-4f && r.endT - landing < march.maxStepTime / 32.0f,
              "landing refined within 1/64 of a step, never short of the ground");
        Check(std::fabs(ArcPoint(arc, r.endT).y) < 0.1f, "the arc ends at ground level");
        const float range = 30 * k * landing; // ~93 m; path a little longer
        Check(samples == r.samples && r.samples <= 2 + static_cast<int>(1.5f * range / march.terrainStep) +
                                                        march.refineIterations,
              "about one ground sample per 8 m of path plus the refinement");
        Check(r.spans >= 2 && r.spans <= 4, "one grid query per ~50 m of path");

        // A level shot from 2 m flies about 0.64 s.
        arc.velocity = {50, 0, 0};
        r = MarchArc(arc, march, Flat, noObjects);
        Check(r.end == ArcEnd::Terrain && Near(r.endT, LandingTime(2.0f, 0.0f), 0.01f), "level shot drops to the ground");

        // Expires in flight.
        arc.velocity = {30 * k, 30 * k, 0};
        arc.lifeSpan = 1.0f;
        r = MarchArc(arc, march, Flat, noObjects);
        Check(r.end == ArcEnd::LifeSpan && r.endT == 1.0f, "lifeSpan ends the arc in the air");

        // Straight up from a deep pit: the path limit, within the sample budget.
        arc.lifeSpan = 1e30f;
        arc.velocity = {0, 200, 0};
        auto pit = [](float, float, float& out) {
            out = -1.0e6f;
            return true;
        };
        r = MarchArc(arc, march, pit, noObjects);
        Check(r.end == ArcEnd::PathLimit && r.samples <= kMaxArcSamples, "path limit bounds the march");
        float path = 0.0f;
        for (int i = 0; i < 64; ++i)
            path += BZROpenShim::ShellCasings::Length(BZROpenShim::ShellCasings::Sub(
                ArcPoint(arc, r.endT * (i + 1) / 64.0f), ArcPoint(arc, r.endT * i / 64.0f)));
        Check(path >= march.maxPathLength - 1e-2f && path < march.maxPathLength + 2.0f * march.terrainStep,
              "the path limit is the straight beam's 500 m");

        // Slow shots are still bounded by the sample budget.
        arc.velocity = {0.5f, 0.0f, 0.0f};
        r = MarchArc(arc, march, pit, noObjects);
        Check(r.samples <= kMaxArcSamples && r.end == ArcEnd::PathLimit, "slow shot: sample budget");

        // Buried muzzle.
        arc.origin = {0, -1, 0};
        arc.velocity = {30, 0, 0};
        r = MarchArc(arc, march, Flat, noObjects);
        Check(r.end == ArcEnd::Terrain && r.endT == 0.0f, "a buried muzzle hits at once");

        // Off the map: the arc ends at the last sampled point.
        arc.origin = {0, 50, 0};
        auto edge = [](float x, float, float& out) {
            out = 0.0f;
            return x < 20.0f;
        };
        r = MarchArc(arc, march, edge, noObjects);
        Check(r.end == ArcEnd::Unsampled && ArcPoint(arc, r.endT).x < 20.0f && ArcPoint(arc, r.endT).x > 10.0f,
              "unsampled ground ends the arc at the last sampled point");

        Arc bad;
        Check(MarchArc(bad, march, Flat, noObjects).end == ArcEnd::Invalid, "no lifeSpan: nothing drawn");
    }

    void ArcObjectTests()
    {
        const ArcMarch march;
        const float k = std::sqrt(0.5f);
        Arc arc;
        arc.origin = {0, 2, 0};
        arc.velocity = {30 * k, 30 * k, 0};
        arc.lifeSpan = 1e30f;
        // A 30 m wall across the flight path at x = 60 (the shell passes
        // there about 23 m up, on its way down).
        Obb wall;
        wall.center = {61, 15, 0};
        wall.half = {1, 15, 10};
        float lastSpanEnd = 0.0f;
        bool contiguous = true;
        const auto wallHit = [&](const ArcSample* points, int count, float& outT) {
            contiguous = contiguous && points[0].t == lastSpanEnd && count >= 2 && count <= kMaxArcSpanPoints;
            lastSpanEnd = points[count - 1].t;
            return PolylineObbHit(points, count, wall, outT);
        };
        ArcResult r = MarchArc(arc, march, Flat, wallHit);
        const float tWall = 60.0f / (30 * k);
        Check(r.end == ArcEnd::Object && Near(r.endT, tWall, 0.02f), "the arc stops on the wall face");
        Check(ArcPoint(arc, r.endT).y < 30.0f && ArcPoint(arc, r.endT).y > 15.0f, "on the wall face, high up");
        Check(contiguous, "spans are contiguous and bounded");

        // The same wall beyond the landing point is never reached.
        wall.center = {200, 15, 0};
        lastSpanEnd = 0.0f;
        r = MarchArc(arc, march, Flat, wallHit);
        Check(r.end == ArcEnd::Terrain, "an object past the ground hit is ignored");

        // A low wall mid-flight is flown over.
        wall.center = {45, 1, 0};
        wall.half = {1, 1, 10};
        lastSpanEnd = 0.0f;
        r = MarchArc(arc, march, Flat, wallHit);
        Check(r.end == ArcEnd::Terrain, "the arc clears a low wall mid-flight");

        // PolylineObbHit on its own.
        Obb box;
        box.center = {15, 0, 0};
        box.half = {1, 1, 1};
        const ArcSample line[3] = {{0.0f, {0, 0, 0}}, {1.0f, {10, 0, 0}}, {2.0f, {20, 0, 0}}};
        float t = 0.0f;
        Check(PolylineObbHit(line, 3, box, t) && Near(t, 1.4f), "hit time interpolated inside the chord");
        Check(!PolylineObbHit(line, 2, box, t), "box beyond the polyline is missed");
        Check(!PolylineObbHit(line, 1, box, t), "a single point has no chord");
    }

    void ArcDrawTests()
    {
        Arc arc;
        arc.origin = {1, 2, 3};
        arc.velocity = {10, 20, -5};
        arc.lifeSpan = 9.0f;
        const float endT = 3.0f;
        Vec3 previousEnd = arc.origin;
        bool contiguous = true;
        const Vec3 side = ArcSideVector(arc, {0, 1, 0});
        bool perpendicular = true;
        for (unsigned k = 0; k < kArcSegments; ++k)
        {
            Vec3 a, b;
            ArcSegment(arc, endT, k, kArcSegments, a, b);
            contiguous = contiguous && Near(a.x, previousEnd.x) && Near(a.y, previousEnd.y) && Near(a.z, previousEnd.z);
            const Vec3 chord = BZROpenShim::ShellCasings::Sub(b, a);
            perpendicular = perpendicular && std::fabs(BZROpenShim::ShellCasings::Dot(chord, side)) < 1e-3f;
            previousEnd = b;
        }
        const Vec3 last = ArcPoint(arc, endT);
        Check(contiguous && Near(previousEnd.x, last.x) && Near(previousEnd.y, last.y) && Near(previousEnd.z, last.z),
              "pieces join end to end from the muzzle to the end point");
        Check(perpendicular && Near(BZROpenShim::ShellCasings::Length(side), 1.0f),
              "the roll reference is perpendicular to every piece");
        arc.velocity = {0, 30, 0};
        const Vec3 fallback = ArcSideVector(arc, {0, 0, 1});
        Check(fallback.z == 1.0f, "a vertical shot uses the fallback roll reference");
    }

    void AssetTests()
    {
        const auto rgb = BeamRgb();
        Check(rgb.size() == kTextureWidth * kTextureHeight * 3, "bounded RGB image");
        Check(rgb == BeamRgb(), "deterministic texture");
        const auto at = [](unsigned y, unsigned x) { return (static_cast<size_t>(y) * kTextureWidth + x) * 3; };
        unsigned long long nearSum = 0, farSum = 0;
        for (unsigned x = 0; x < kTextureWidth; ++x)
        {
            nearSum += rgb[at(0, x)];
            farSum += rgb[at(kTextureHeight - 1, x)];
            Check(rgb[at(0, x)] > rgb[at(0, x) + 1] * 4 && rgb[at(0, x)] > rgb[at(0, x) + 2] * 4, "red beam");
        }
        Check(nearSum > farSum * 2 && farSum > 0, "bright at the muzzle, fading but visible at the far end");
        bool seamless = true;
        for (unsigned y = 0; y < kTextureHeight; ++y)
        {
            const int a = rgb[at(y, 0)], b = rgb[at(y, kTextureWidth - 1)];
            seamless = seamless && std::abs(a - b) < 40;
        }
        Check(seamless, "the wrap seam around the tube is continuous");

        const auto tga = BeamTga();
        Check(IsGeneratedTga(tga) && tga.size() == 18 + tga[0] + rgb.size(), "marked, uncompressed 24-bit TGA");
        Check(!IsGeneratedTga(std::vector<uint8_t>(64, 0)), "an unmarked TGA is the user's");

        const std::string material = MaterialScript();
        const std::string shader = ShaderSource();
        Check(IsGeneratedText(material) && IsGeneratedText(shader), "generated text assets carry the marker");
        Check(!IsGeneratedText("material x {}\n"), "unmarked text is the user's");
        const auto count = [](const std::string& text, const std::string& needle) {
            size_t n = 0;
            for (size_t at = text.find(needle); at != std::string::npos; at = text.find(needle, at + 1))
                ++n;
            return n;
        };
        Check(count(material, "    technique\n") == 2, "two techniques");
        const size_t sm4 = material.find("vertex_program_ref openshim_lasersight_vs");
        const size_t ffp = material.find("fog_override true none");
        Check(sm4 != std::string::npos && ffp != std::string::npos && sm4 < ffp,
              "SM4 technique first (DX11), fixed function second (DX9)");
        Check(material.find("target vs_4_0") != std::string::npos &&
                  material.find("target ps_4_0") != std::string::npos,
              "DX11 programs are SM4");
        Check(count(material, "scene_blend add") == 2 && count(material, "depth_write off") == 2 &&
                  count(material, "lighting off") == 2 && count(material, "cull_hardware none") == 2,
              "both techniques: additive, no depth write, unlit, double sided");
        Check(material.find(std::string("material ") + kMaterialName + "\n") != std::string::npos &&
                  material.find(std::string("source ") + kShaderFile) != std::string::npos &&
                  count(material, std::string("texture ") + kTextureFile) == 2,
              "names tie the material, shader and texture together");
        Check(shader.find("void lasersight_vertex(") != std::string::npos &&
                  shader.find("void lasersight_fragment(") != std::string::npos &&
                  shader.find("SV_POSITION") != std::string::npos && shader.find("SV_TARGET") != std::string::npos,
              "both SM4 entry points");
        Check(material.find("entry_point lasersight_vertex") != std::string::npos &&
                  material.find("entry_point lasersight_fragment") != std::string::npos,
              "material entry points exist in the shader");
    }
}

int main(int argc, char** argv)
{
    if (argc == 3 && std::string(argv[1]) == "--emit")
    {
        const std::filesystem::path dir(argv[2]);
        std::filesystem::create_directories(dir);
        std::ofstream(dir / kShaderFile, std::ios::binary) << ShaderSource();
        std::ofstream(dir / kMaterialFile, std::ios::binary) << MaterialScript();
        const auto tga = BeamTga();
        std::ofstream(dir / kTextureFile, std::ios::binary)
            .write(reinterpret_cast<const char*>(tga.data()), static_cast<std::streamsize>(tga.size()));
        return 0;
    }
    GateTests();
    SlotTests();
    TerrainTests();
    RayObbTests();
    SegmentTests();
    TransformTests();
    BallisticSigTests();
    PitchTests();
    ArcPointTests();
    MarchArcTests();
    ArcObjectTests();
    ArcDrawTests();
    AssetTests();
    return OpenShimTest::ExitCode();
}
