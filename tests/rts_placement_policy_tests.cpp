// RTS placement aids' engine-independent logic: build ghost tint and
// visibility, the power signature check, mesh names, ghost orientation, the
// power ring filter, waypoint destination extraction from a fake command
// record, line sampling, the pool layout and the generated ghost assets.
// `--emit <dir>` writes the ghost shader and material so the shader can be
// compiled with fxc by hand.
#include "rts_markers_assets.h"
#include "rts_markers_policy.h"
#include "rts_placement_policy.h"
#include "test_check.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using namespace BZROpenShim::RtsPlacement;
using OpenShimTest::Check;

namespace
{
    bool Near(float a, float b, float epsilon = 1e-4f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    void TintTests()
    {
        const uintptr_t g = 0x1000, y = 0x2000, r = 0x3000;
        Check(TintFor(kResultValid, g, g, y, r) == Tint::Valid, "8 with ground.G: valid");
        Check(TintFor(kResultRefused, y, g, y, r) == Tint::NoPower, "9 with ground.Y: no power");
        Check(TintFor(kResultRefused, r, g, y, r) == Tint::Blocked, "9 with ground.R: blocked");
        Check(TintFor(kResultValid, 0, g, y, r) == Tint::None, "no sprite: the quad is not shown");
        Check(TintFor(kResultValid, r, g, y, r) == Tint::None, "8 with a red sprite disagrees: nothing");
        Check(TintFor(kResultRefused, g, g, y, r) == Tint::None, "9 with a green sprite disagrees: nothing");
        Check(TintFor(0, g, g, y, r) == Tint::None && TintFor(3, g, g, y, r) == Tint::None,
              "not a building result: nothing");
        Check(TintFor(kResultValid, 0x4000, g, y, r) == Tint::None, "an unknown sprite: nothing");

        Check(std::string(MaterialFor(Tint::Valid)) == "openshim_rtsghost_g", "valid material");
        Check(std::string(MaterialFor(Tint::NoPower)) == "openshim_rtsghost_y", "no-power material");
        Check(std::string(MaterialFor(Tint::Blocked)) == "openshim_rtsghost_r", "blocked material");
        Check(std::string(MaterialFor(Tint::Neutral)) == "openshim_rtsghost_n", "nav material");
        Check(MaterialFor(Tint::None) == nullptr, "no material for no tint");
    }

    void VisibilityTests()
    {
        // tickSerial = the serial stamped on records made since the previous
        // tick (the call site passes its incremented counter minus one).
        Check(GhostVisible(true, false, true, 10, 10, false, Tint::Valid), "recorded this tick: shown");
        Check(GhostVisible(true, false, true, 10, 11, false, Tint::Blocked), "recorded last tick: shown");
        Check(!GhostVisible(true, false, true, 10, 12, false, Tint::Valid), "two ticks old: hidden");
        Check(GhostVisible(true, false, true, 0xFFFFFFFFu, 0u, false, Tint::Valid), "serial wrap");
        Check(!GhostVisible(false, false, true, 10, 10, false, Tint::Valid), "option off: hidden");
        Check(!GhostVisible(true, true, true, 10, 10, false, Tint::Valid), "HUD hidden: hidden");
        Check(!GhostVisible(true, false, false, 10, 10, false, Tint::Valid), "nothing recorded: hidden");
        Check(!GhostVisible(true, false, true, 10, 10, true, Tint::Valid), "alternate render pass: hidden");
        Check(!GhostVisible(true, false, true, 10, 10, false, Tint::None), "no tint: hidden");

        Check(NavGhostsWanted(true, false, true, 3, 3, 0x1234), "submenu open with a picked rig: nav ghosts");
        Check(!NavGhostsWanted(true, false, true, -1, 3, 0x1234), "submenu closed: none");
        Check(!NavGhostsWanted(true, false, false, 3, 3, 0x1234), "Build at Nav inactive: none");
        Check(!NavGhostsWanted(true, false, true, 3, 3, 0), "no picked rig: none");
        Check(!NavGhostsWanted(false, false, true, 3, 3, 0x1234), "option off: none");
        Check(!NavGhostsWanted(true, true, true, 3, 3, 0x1234), "HUD hidden: none");
        Check(kMaxNavGhosts == 10 && kFirstNavSlot == 0x23 && kLastNavSlot == 0x2C, "beacon slots 35..44");

        Check(PendingBuildShows(0, 0, 0), "travelling: pending ghost");
        Check(PendingBuildShows(0, 0, 1) && PendingBuildShows(0, 0, 4), "final approach: pending ghost");
        Check(PendingBuildShows(0, 0, 2), "deploying: pending ghost");
        Check(!PendingBuildShows(0, 0, 3), "construction started: hidden");
        Check(!PendingBuildShows(kTaskDone, 0, 0) && !PendingBuildShows(0, kTaskDone, 1), "task finished: hidden");
        Check(!PendingBuildShows(0, 0, -1) && !PendingBuildShows(0, 0, 5), "unknown stage: hidden");
        Check(kMaxPendingGhosts == 8, "eight pending ghosts at most");
    }

    void SignatureTests()
    {
        const auto sig = [](const char* text) {
            uint32_t v = 0;
            std::memcpy(&v, text, 4);
            return v;
        };
        // The engine compares the dword as an imm32; the bytes in memory are
        // the ODF class letters reversed ("MMOC" for COMM).
        Check(NeedsPower(kSigComm) && sig("MMOC") == kSigComm, "COMM needs power");
        Check(NeedsPower(kSigTurr) && sig("RRUT") == kSigTurr, "TURR needs power");
        Check(NeedsPower(kSigShld) && sig("DLHS") == kSigShld, "SHLD needs power");
        Check(!NeedsPower(0x504F5752) && !NeedsPower(0) && !NeedsPower(sig("COMM")), "anything else does not");
    }

    void MeshNameTests()
    {
        const char full[8] = {'a', 'b', 's', 'p', 'o', 'w', 'e', 'r'};
        Check(MeshNameFor(full) == "abspower.mesh", "8 chars, no terminator: precision 8");
        const char shortName[8] = {'a', 'b', 'c', 'o', 'm', 'm', 0, 'x'};
        Check(MeshNameFor(shortName) == "abcomm.mesh", "stops at the terminator");
        const char empty[8] = {};
        Check(MeshNameFor(empty).empty(), "empty field: no mesh");
        const char garbage[8] = {'a', 'b', '\x01', 'c', 0, 0, 0, 0};
        Check(MeshNameFor(garbage).empty(), "a control byte: a bad read, no mesh");
        Check(MeshNameFor(nullptr).empty(), "null: no mesh");
    }

    void OrientationTests()
    {
        const float right[3] = {1, 0, 0}, up[3] = {0, 1, 0}, front[3] = {0, 0, 1};
        Axes axes{};
        Check(RenderAxesFromSimBasis(right, up, front, axes), "identity basis");
        Check(Near(axes.x[0], 1) && Near(axes.y[1], 1) && Near(axes.z[2], 1) && Near(axes.x[2], 0) &&
                  Near(axes.z[0], 0),
              "identity sim basis is the identity in render space");
        // Facing sim +X: front (1,0,0), right (0,0,-1).
        const float r2[3] = {0, 0, -1}, f2[3] = {1, 0, 0};
        Check(RenderAxesFromSimBasis(r2, up, f2, axes), "turned basis");
        Check(Near(axes.x[2], 1) && Near(axes.z[0], -1), "z flip on both the axis and the mesh");
        // Right-handed: x cross y == z.
        const float cx = axes.x[1] * axes.y[2] - axes.x[2] * axes.y[1];
        const float cy = axes.x[2] * axes.y[0] - axes.x[0] * axes.y[2];
        const float cz = axes.x[0] * axes.y[1] - axes.x[1] * axes.y[0];
        Check(Near(cx, axes.z[0]) && Near(cy, axes.z[1]) && Near(cz, axes.z[2]), "render axes are right-handed");
        const float zero[3] = {0, 0, 0}, nan3[3] = {std::nanf(""), 0, 0};
        Check(!RenderAxesFromSimBasis(zero, up, front, axes), "degenerate axis refused");
        Check(!RenderAxesFromSimBasis(right, nan3, front, axes), "NaN axis refused");
        // A scaled basis is normalised.
        const float big[3] = {3, 0, 0};
        Check(RenderAxesFromSimBasis(big, up, front, axes) && Near(axes.x[0], 1), "scaled axis normalised");

        float rr[3], uu[3], ff[3];
        const float heading[3] = {3.0f, 5.0f, 4.0f};
        Check(YawBasis(heading, rr, uu, ff), "a pitched heading still has a yaw");
        Check(Near(ff[0], 0.6f) && Near(ff[1], 0) && Near(ff[2], 0.8f), "flattened front");
        Check(Near(rr[0], 0.8f) && Near(rr[2], -0.6f) && Near(uu[1], 1), "right is front turned a quarter");
        const float identityFront[3] = {0, 0, 1};
        Check(YawBasis(identityFront, rr, uu, ff) && Near(rr[0], 1), "facing +Z: right is +X");
        const float vertical[3] = {0, 1, 0};
        Check(!YawBasis(vertical, rr, uu, ff), "straight up has no yaw");
    }

    void PowerTests()
    {
        size_t count = 99;
        Check(PlantVectorSane(0, 0, count) && count == 0, "empty vector");
        Check(PlantVectorSane(0x100000, 0x100010, count) && count == 4, "four plants");
        Check(!PlantVectorSane(0x100010, 0x100000, count), "last before first: bad read");
        Check(!PlantVectorSane(0x100000, 0x100006, count), "misaligned: bad read");
        Check(!PlantVectorSane(0x100000, 0x100000 + 4 * (kMaxPlantEntries + 1), count), "too long: bad read");
        Check(!PlantVectorSane(0x10, 0x20, count), "a null-page pointer: bad read");

        std::vector<PlantCandidate> plants(40);
        for (size_t i = 0; i < plants.size(); ++i)
        {
            plants[i].ally = (i % 2) == 0;
            plants[i].pos[0] = static_cast<float>(i) * 10.0f;
            plants[i].pos[2] = 0.0f;
            plants[i].radius = 100.0f;
        }
        plants[4].radius = 0.0f;               // no radius
        plants[6].radius = std::nanf("");      // bad read
        plants[8].pos[1] = std::nanf("");      // bad position
        plants[10].radius = kMaxPowerRadius * 2; // nonsense radius
        size_t chosen[kMaxPowerRings] = {};
        const size_t n = SelectPowerRings(plants.data(), plants.size(), 0.0f, 0.0f, kMaxPowerRings, chosen);
        Check(n == kMaxPowerRings, "capped at 16");
        bool allAllied = true, sorted = true, noBad = true;
        for (size_t i = 0; i < n; ++i)
        {
            allAllied = allAllied && plants[chosen[i]].ally;
            noBad = noBad && chosen[i] != 4 && chosen[i] != 6 && chosen[i] != 8 && chosen[i] != 10;
            if (i > 0)
                sorted = sorted && chosen[i] > chosen[i - 1];
        }
        Check(allAllied, "only allied plants");
        Check(noBad, "bad radius or position skipped");
        Check(sorted && chosen[0] == 0 && chosen[1] == 2 && chosen[2] == 12, "nearest first");

        // Focus at the far end: the nearest 16 from there.
        const size_t m = SelectPowerRings(plants.data(), plants.size(), 390.0f, 0.0f, kMaxPowerRings, chosen);
        Check(m == kMaxPowerRings && chosen[0] == 38 && chosen[1] == 36, "nearest to the focus");
        Check(SelectPowerRings(plants.data(), plants.size(), 0, 0, 0, chosen) == 0, "cap 0: nothing");
        Check(SelectPowerRings(plants.data(), 3, 0, 0, kMaxPowerRings, chosen) == 2, "fewer than the cap");
        Check(SelectPowerRings(nullptr, 3, 0, 0, kMaxPowerRings, chosen) == 0, "no list");
    }

    // A fake engine heap: addresses map into one byte buffer.
    struct FakeMemory
    {
        static constexpr uintptr_t kBase = 0x20000000;
        std::vector<uint8_t> bytes = std::vector<uint8_t>(0x1000, 0);

        template <typename T>
        void Put(uintptr_t address, T value)
        {
            std::memcpy(bytes.data() + (address - kBase), &value, sizeof(T));
        }

        bool Read(uintptr_t address, void* out, size_t size) const
        {
            if (address < kBase || address + size > kBase + bytes.size())
                return false;
            std::memcpy(out, bytes.data() + (address - kBase), size);
            return true;
        }
    };

    void WaypointTests()
    {
        FakeMemory mem;
        const uintptr_t obj = FakeMemory::kBase;
        const uintptr_t path = FakeMemory::kBase + 0x400;
        const uintptr_t points = FakeMemory::kBase + 0x500;
        const auto read = [&mem](uintptr_t a, void* out, size_t n) { return mem.Read(a, out, n); };
        // Current: GO along a 3-point path ending at (120, -40).
        mem.Put<int32_t>(obj + kCurrentRecordOffset + kRecordWhatOffset, kCmdGo);
        mem.Put<uint32_t>(obj + kCurrentRecordOffset + kRecordPathOffset, static_cast<uint32_t>(path));
        mem.Put<int32_t>(path + kPathCountOffset, 3);
        mem.Put<uint32_t>(path + kPathPointsOffset, static_cast<uint32_t>(points));
        const float pts[6] = {0, 0, 50, 10, 120, -40};
        std::memcpy(mem.bytes.data() + (points - FakeMemory::kBase), pts, sizeof(pts));

        int what = 0;
        float x = 0, z = 0;
        Check(CommandDestination(read, obj, kCurrentRecordOffset, what, x, z) && what == kCmdGo && Near(x, 120) &&
                  Near(z, -40),
              "current record: the path's last point");
        Check(kCurrentRecordOffset == 0xA8 && kPendingRecordOffset == 0xC8 && kRecordWhatOffset == 4 &&
                  kRecordPathOffset == 0x0C,
              "record layout as the promote routine copies it");

        // Pending: nothing yet.
        Check(!CommandDestination(read, obj, kPendingRecordOffset, what, x, z), "empty pending record");
        // Pending: ATTACK sharing the same path.
        mem.Put<int32_t>(obj + kPendingRecordOffset + kRecordWhatOffset, kCmdAttack);
        mem.Put<uint32_t>(obj + kPendingRecordOffset + kRecordPathOffset, static_cast<uint32_t>(path));
        Check(CommandDestination(read, obj, kPendingRecordOffset, what, x, z) && what == kCmdAttack,
              "pending record read the same way");

        // Idle commands.
        for (const int idle : {0, 1, 2})
        {
            mem.Put<int32_t>(obj + kCurrentRecordOffset + kRecordWhatOffset, idle);
            Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "none/select/stop: no line");
        }
        mem.Put<int32_t>(obj + kCurrentRecordOffset + kRecordWhatOffset, kCmdLast + 1);
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "unknown command id: no line");
        mem.Put<int32_t>(obj + kCurrentRecordOffset + kRecordWhatOffset, kCmdGo);

        // Path problems.
        mem.Put<uint32_t>(obj + kCurrentRecordOffset + kRecordPathOffset, 0u);
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "no path: no line");
        mem.Put<uint32_t>(obj + kCurrentRecordOffset + kRecordPathOffset, static_cast<uint32_t>(path));
        mem.Put<int32_t>(path + kPathCountOffset, 0);
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "empty path");
        mem.Put<int32_t>(path + kPathCountOffset, kMaxPathPoints + 1);
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "absurd point count");
        mem.Put<int32_t>(path + kPathCountOffset, 1000);
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "points past readable memory");
        mem.Put<int32_t>(path + kPathCountOffset, 1);
        Check(CommandDestination(read, obj, kCurrentRecordOffset, what, x, z) && Near(x, 0) && Near(z, 0),
              "a one-point path");
        mem.Put<float>(points, std::nanf(""));
        Check(!CommandDestination(read, obj, kCurrentRecordOffset, what, x, z), "NaN point");
        Check(!CommandDestination(read, 0, kCurrentRecordOffset, what, x, z), "no object");

        Check(ShouldDrawLine(0, 0, 10, 0) && !ShouldDrawLine(0, 0, 1, 1), "arrived units draw nothing");
        Check(LineSegmentsFor(0.0f) == 1 && LineSegmentsFor(3.0f) == 1 && LineSegmentsFor(10.0f) == 3,
              "a segment every 4 m");
        Check(LineSegmentsFor(10000.0f) == kMaxLineSegments && LineSegmentsFor(std::nanf("")) == 1, "capped");

        const LineColour go = WaypointColour(kCmdGo, false), goPending = WaypointColour(kCmdGo, true);
        Check(go.g > go.r && goPending.a < go.a && Near(goPending.g, go.g), "pending is the same colour, dimmer");
        Check(WaypointColour(kCmdAttack, false).r > WaypointColour(kCmdAttack, false).g, "attack is red");
    }

    void RouteTests()
    {
        RouteSample out[kMaxRouteSamples];

        // A straight 2-point route matches the old straight line.
        const float straight[] = {10.0f, 20.0f, 10.0f, 30.0f}; // 10 m along +z
        const unsigned segments = LineSegmentsFor(10.0f);
        unsigned n = BuildRouteSamples(straight, 2, kLineWidth, out);
        Check(n == segments + 1, "straight route: same sample count as the line");
        bool same = n == segments + 1;
        for (unsigned i = 0; i < n && same; ++i)
        {
            const float t = static_cast<float>(i) / static_cast<float>(segments);
            // Old line: perpendicular (-dz, dx)/len * half.
            same = Near(out[i].x, 0.0f) && Near(out[i].z, 10.0f * t) && Near(out[i].px, -0.5f * kLineWidth) &&
                   Near(out[i].pz, 0.0f);
        }
        Check(same, "straight route: samples and offsets match the old line");

        // An L-shaped route keeps its corner (a sample sits on it, mitred).
        const float ell[] = {0.0f, 0.0f, 10.0f, 0.0f, 10.0f, 10.0f};
        n = BuildRouteSamples(ell, 3, kLineWidth, out);
        bool corner = false;
        for (unsigned i = 0; i < n; ++i)
            if (Near(out[i].x, 10.0f) && Near(out[i].z, 0.0f))
            {
                corner = true;
                // Normals (0,1) and (-1,0) average to (-0.707, 0.707), scaled by 1/cos(45).
                Check(Near(out[i].px, -0.5f * kLineWidth) && Near(out[i].pz, 0.5f * kLineWidth), "corner is mitred");
            }
        Check(corner && n >= 3, "L route keeps its corner");
        Check(Near(out[n - 1].x, 10.0f) && Near(out[n - 1].z, 10.0f), "L route ends on the goal");

        // A sharp reversal clamps the miter.
        const float back[] = {0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.001f};
        n = BuildRouteSamples(back, 3, kLineWidth, out);
        bool clamped = n > 0;
        for (unsigned i = 0; i < n; ++i)
            clamped = clamped && std::sqrt(out[i].px * out[i].px + out[i].pz * out[i].pz) <=
                                     kMaxMiter * 0.5f * kLineWidth + 1e-4f;
        Check(clamped, "miter is clamped");

        // A long, winding route stays within the vertex budget.
        float longRoute[2 * kMaxRoutePoints];
        for (unsigned i = 0; i < kMaxRoutePoints; ++i)
        {
            longRoute[2 * i] = 500.0f * static_cast<float>(i);
            longRoute[2 * i + 1] = (i & 1u) ? 300.0f : 0.0f;
        }
        n = BuildRouteSamples(longRoute, kMaxRoutePoints, kLineWidth, out);
        Check(n >= 2 && n <= kMaxRouteSamples, "long route stays within the budget");
        Check(Near(out[n - 1].x, longRoute[2 * (kMaxRoutePoints - 1)] - longRoute[0], 0.01f), "long route reaches the goal");

        // Degenerate input.
        const float dup[] = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
        Check(BuildRouteSamples(dup, 3, kLineWidth, out) == 0, "all-duplicate points: nothing");
        Check(BuildRouteSamples(dup, 1, kLineWidth, out) == 0, "one point: nothing");
        Check(BuildRouteSamples(nullptr, 2, kLineWidth, out) == 0, "no points: nothing");
        const float nanRoute[] = {0.0f, 0.0f, std::nanf(""), 1.0f, 8.0f, 0.0f};
        n = BuildRouteSamples(nanRoute, 3, kLineWidth, out);
        Check(n >= 2 && Near(out[n - 1].x, 8.0f), "a NaN point is skipped");
        const float dupMid[] = {0.0f, 0.0f, 4.0f, 0.0f, 4.0f, 0.0f, 8.0f, 0.0f};
        n = BuildRouteSamples(dupMid, 4, kLineWidth, out);
        Check(n >= 2 && Near(out[n - 1].x, 8.0f), "a duplicate mid point is merged");

        // Trim keeps the first 63 points and the goal.
        float big[2 * 100], trimmed[2 * kMaxRoutePoints];
        for (unsigned i = 0; i < 100; ++i)
        {
            big[2 * i] = static_cast<float>(i);
            big[2 * i + 1] = 0.0f;
        }
        Check(TrimRoute(big, 100, trimmed) == kMaxRoutePoints && Near(trimmed[2 * 62], 62.0f) &&
                  Near(trimmed[2 * 63], 99.0f),
              "long route trimmed to 63 points and the goal");
        Check(TrimRoute(big, 5, trimmed) == 5 && TrimRoute(big, 0, trimmed) == 0, "short route kept whole");

        // The hash follows the points.
        float a[] = {0.0f, 0.0f, 1.0f, 1.0f}, b[] = {0.0f, 0.0f, 1.0f, 1.0f};
        Check(RouteHash(a, 2) == RouteHash(b, 2), "equal routes hash equal");
        b[3] = 1.5f;
        Check(RouteHash(a, 2) != RouteHash(b, 2), "a changed point changes the hash");
    }

    void PoolTests()
    {
        using namespace BZROpenShim::RtsMarkers;
        Check(kFirstPowerSlot == kPoolSize, "power rings follow the rings");
        Check(kMaxPowerRingSlots == kMaxPowerRings && kMaxWaypointLineSlots == kMaxWaypointUnits,
              "one slot per ring and per line");
        Check(kSlotCount == kPoolSize + kMaxPowerRings + 2 * kMaxWaypointUnits, "pool holds everything at once");
        Check(2u * (kMaxLineSegments + 1u) <= 2u * (kMaxSegments + 1u), "a line fits the ring strip budget");
    }

    void AssetTests()
    {
        using namespace BZROpenShim::RtsMarkers;
        const std::string material = GhostMaterialScript();
        const std::string shader = GhostShaderSource();
        Check(IsGeneratedText(material) && IsGeneratedText(shader), "generated assets carry the marker");
        for (const char* name : {kGhostMaterialValid, kGhostMaterialNoPower, kGhostMaterialBlocked, kGhostMaterialNeutral})
            Check(material.find(std::string("material ") + name + "\n") != std::string::npos, "every ghost material");
        size_t blends = 0, noDepthWrite = 0, depthCheck = 0, fogOff = 0, tints = 0;
        for (size_t at = 0; (at = material.find("scene_blend alpha_blend", at)) != std::string::npos; ++at)
            ++blends;
        for (size_t at = 0; (at = material.find("depth_write off", at)) != std::string::npos; ++at)
            ++noDepthWrite;
        for (size_t at = 0; (at = material.find("depth_check on", at)) != std::string::npos; ++at)
            ++depthCheck;
        for (size_t at = 0; (at = material.find("fog_override true none", at)) != std::string::npos; ++at)
            ++fogOff;
        for (size_t at = 0; (at = material.find("param_named tint float4", at)) != std::string::npos; ++at)
            ++tints;
        Check(blends == 8 && noDepthWrite == 8 && depthCheck == 8, "both techniques of all four: blended, depth read only");
        Check(fogOff == 4, "DX9 technique has no fog");
        Check(tints == 4, "DX11 technique carries the tint");
        Check(material.find("emissive 0.395 1.000 0.510 1") != std::string::npos, "valid glow on DX9");
        Check(material.find("cull_hardware none") == std::string::npos, "back faces culled");
        Check(material.find("target vs_4_0") != std::string::npos && material.find("target ps_4_0") != std::string::npos,
              "SM4 technique for DX11");
        Check(material.find(kGhostShaderFile) != std::string::npos, "material points at the shader");
        Check(shader.find("rtsghost_vertex") != std::string::npos && shader.find("rtsghost_fragment") != std::string::npos,
              "both entry points");
        Check(shader.find("uniform float4 tint") != std::string::npos, "constant tint");
        Check(std::string(kGhostMaterialFile) != kMaterialFile && std::string(kGhostShaderFile) != kShaderFile,
              "separate files from the ring assets");
        Check(Near(GhostGlow(1.0f), 1.0f) && Near(GhostGlow(0.0f), kGhostGlowLift), "glow saturates");
    }

    void Emit(const std::filesystem::path& dir)
    {
        using namespace BZROpenShim::RtsMarkers;
        std::filesystem::create_directories(dir);
        std::ofstream(dir / kGhostShaderFile, std::ios::binary) << GhostShaderSource();
        std::ofstream(dir / kGhostMaterialFile, std::ios::binary) << GhostMaterialScript();
    }
}

int main(int argc, char** argv)
{
    if (argc == 3 && std::string(argv[1]) == "--emit")
    {
        Emit(argv[2]);
        return 0;
    }
    TintTests();
    VisibilityTests();
    SignatureTests();
    MeshNameTests();
    OrientationTests();
    PowerTests();
    WaypointTests();
    RouteTests();
    PoolTests();
    AssetTests();
    return OpenShimTest::ExitCode();
}
