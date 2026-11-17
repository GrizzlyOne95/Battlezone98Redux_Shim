// rts_placement_policy.h
// BZR Open Shim - RTS placement aids (rts_placement.cpp, rts_markers.cpp):
// the engine-independent rules behind the build ghost, the power range rings
// and the waypoint lines. Header-only, portable C++14 and free of Windows and
// Ogre, so the unit tests check the same rules the shim runs. See
// Docs/RTS_MARKERS.md ("Build Ghost", "Power Range", "Waypoint Lines").
#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace RtsPlacement
    {
        // ---- Stock preview (ConstructionRig::GetCommand 0x0049D230) ---------
        // GetCommand's return values for a picked building (rows
        // RtsGhostPreviewResults): 8 = CMD_DROPOFF (the spot is valid), 9 = the
        // spot is refused (no power in range, or CanBuildHere failed).
        constexpr int kResultValid = 8;
        constexpr int kResultRefused = 9;

        // The four ghost tints. Valid/NoPower/Blocked mirror the stock ground
        // quad's sprite (ground.G / ground.Y / ground.R); Neutral is the nav
        // ghost, which never asks the engine.
        enum class Tint : uint8_t
        {
            None,
            Valid,
            NoPower,
            Blocked,
            Neutral,
        };

        // The tint the stock preview shows after one GetCommand call: the
        // sprite pointer it left in ConstructionDisplay +0x68 compared with the
        // three it loaded at +0x6C/+0x70/+0x74. The result must agree with
        // the sprite (8 with G, 9 with Y or R): GetCommand only sets the sprite
        // when the rig is the user's ally, so a stale sprite from an earlier
        // call never paints a different answer.
        inline Tint TintFor(int result, uintptr_t sprite, uintptr_t green, uintptr_t yellow, uintptr_t red)
        {
            if (sprite == 0)
                return Tint::None;
            if (result == kResultValid && sprite == green)
                return Tint::Valid;
            if (result == kResultRefused && sprite == yellow)
                return Tint::NoPower;
            if (result == kResultRefused && sprite == red)
                return Tint::Blocked;
            return Tint::None;
        }

        constexpr const char* kGhostMaterialValid = "openshim_rtsghost_g";
        constexpr const char* kGhostMaterialNoPower = "openshim_rtsghost_y";
        constexpr const char* kGhostMaterialBlocked = "openshim_rtsghost_r";
        constexpr const char* kGhostMaterialNeutral = "openshim_rtsghost_n";

        inline const char* MaterialFor(Tint tint)
        {
            switch (tint)
            {
            case Tint::Valid:
                return kGhostMaterialValid;
            case Tint::NoPower:
                return kGhostMaterialNoPower;
            case Tint::Blocked:
                return kGhostMaterialBlocked;
            case Tint::Neutral:
                return kGhostMaterialNeutral;
            case Tint::None:
            default:
                return nullptr;
            }
        }

        // The cursor ghost shows while the hook recorded a preview this tick
        // or the one before (`tickSerial - recordSerial` <= 1, wrap-safe).
        // `tickSerial` is the serial the hook stamps on records made since
        // the previous tick (rts_placement.cpp passes its counter minus one,
        // as it increments at the start of the tick). Also needed: the
        // option is on, the HUD is shown and the engine is not in its
        // alternate render pass (DAT_02cecf74, which also suppresses the stock
        // quad). Ticks with no GetCommand call age the record out.
        inline bool GhostVisible(bool optionOn, bool hudHidden, bool recorded, uint32_t recordSerial,
                                 uint32_t tickSerial, bool altPass, Tint tint)
        {
            if (!optionOn || hudHidden || !recorded || altPass || tint == Tint::None)
                return false;
            return static_cast<uint32_t>(tickSerial - recordSerial) <= 1u;
        }

        // ---- Class -------------------------------------------------------------
        // GameObjectClass +0x14 signatures GetCommand gives the power test
        // (row RtsGhostTowerSigCheck: `cmp dword [eax+14h], imm32`).
        constexpr uint32_t kSigComm = 0x434F4D4D; // 'COMM'
        constexpr uint32_t kSigTurr = 0x54555252; // 'TURR'
        constexpr uint32_t kSigShld = 0x53484C44; // 'SHLD'

        inline bool NeedsPower(uint32_t classSig)
        {
            return classSig == kSigComm || classSig == kSigTurr || classSig == kSigShld;
        }

        // The class's model: GameObjectClass +0x28 is an inline char[8] (the
        // ODF baseName), not NUL-terminated when all 8 are used. The engine
        // builds "%.*s.mesh" from it (FUN_0067f480; row RtsGhostMeshName).
        // Empty when the field is empty or holds a byte outside printable
        // ASCII (a garbage read).
        constexpr size_t kMeshBaseLength = 8;

        inline std::string MeshNameFor(const char* base)
        {
            if (!base)
                return std::string();
            size_t n = 0;
            while (n < kMeshBaseLength && base[n] != '\0')
            {
                const unsigned char c = static_cast<unsigned char>(base[n]);
                if (c < 0x21 || c > 0x7E)
                    return std::string();
                ++n;
            }
            if (n == 0)
                return std::string();
            char buffer[32] = {};
            std::snprintf(buffer, sizeof(buffer), "%.*s.mesh", static_cast<int>(n), base);
            return std::string(buffer);
        }

        // ---- Nav ghosts --------------------------------------------------------
        // The Go To Nav submenu lists the user team's beacon slots 0x23..0x2C
        // (row RtsNavSlotLoop), skipping empty ones.
        constexpr int kFirstNavSlot = 0x23;
        constexpr int kLastNavSlot = 0x2C;
        constexpr size_t kMaxNavGhosts = static_cast<size_t>(kLastNavSlot - kFirstNavSlot + 1);

        // Nav ghosts while the submenu is open (ControlPanel +0x117C equals the
        // nav menu id, row RtsNavSubmenuOpen), Build at Nav is active and a
        // selected rig has a building picked.
        inline bool NavGhostsWanted(bool optionOn, bool hudHidden, bool buildNavActive, int openMenu, int navMenu,
                                    uint32_t pickedClass)
        {
            return optionOn && !hudHidden && buildNavActive && openMenu == navMenu && pickedClass != 0;
        }

        // ---- Pending build ghosts ----------------------------------------------
        // A rig given BUILD runs a BuildGoto task (RigProcess::InitUState
        // 0x0049E940 stores it at process +0x38; ExitUState 0x0049E9F0 deletes
        // and clears it). Its stage at +0x14C (0x0049E416, jump table
        // 0x0049E924): 0 travelling (0x0049E433); 1 and 4 final approach
        // (0x0049E5B7, 0x0049E78D), which call the rig's Deploy (vtable +0x60,
        // 0x004AE2B0) and set stage 2 (0x0049E6F6, 0x0049E8EA); 2 deploying
        // (0x0049E72B), set to 3 at 0x0049E741 once vtable +0x68 (0x004AE300,
        // rig +0x228 == 2) reports deployed; 3 deployed/building (0x0049E753),
        // which waits on 0x00472400, calls Undeploy (+0x64) and sets +0x0C to
        // 13 (done). +0x08 at 13 also means finished (0x0049E3E9). The ghost
        // shows before construction starts.
        constexpr size_t kMaxPendingGhosts = 8;
        constexpr int32_t kTaskDone = 0xD;
        constexpr int32_t kStageBuilding = 3;
        constexpr int32_t kLastStage = 4;

        inline bool PendingBuildShows(int32_t state, int32_t result, int32_t stage)
        {
            return state != kTaskDone && result != kTaskDone && stage >= 0 && stage <= kLastStage &&
                   stage != kStageBuilding;
        }

        // ---- Orientation -------------------------------------------------------
        struct Axes
        {
            float x[3];
            float y[3];
            float z[3];
        };

        // Render-space node axes for a sim basis (MAT_3D right/up/front).
        // Sim -> render flips z; Ogre mesh local -> sim local mirrors z too
        // (native_chunk_mesh.cpp FragmentOriginShift), so mesh +Z is -front.
        // False when an axis is not finite or degenerate.
        inline bool RenderAxesFromSimBasis(const float right[3], const float up[3], const float front[3], Axes& out)
        {
            const float* basis[3] = {right, up, front};
            float unit[3][3] = {};
            for (int a = 0; a < 3; ++a)
            {
                const float* v = basis[a];
                if (!std::isfinite(v[0]) || !std::isfinite(v[1]) || !std::isfinite(v[2]))
                    return false;
                const float length = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
                if (!(length > 1e-4f))
                    return false;
                for (int i = 0; i < 3; ++i)
                    unit[a][i] = v[i] / length;
            }
            out.x[0] = unit[0][0];
            out.x[1] = unit[0][1];
            out.x[2] = -unit[0][2];
            out.y[0] = unit[1][0];
            out.y[1] = unit[1][1];
            out.y[2] = -unit[1][2];
            out.z[0] = -unit[2][0];
            out.z[1] = -unit[2][1];
            out.z[2] = unit[2][2];
            return true;
        }

        // A level sim basis facing the horizontal part of `front` (the
        // player's heading): right = (fz, 0, -fx), up = +Y. False when the
        // heading is (nearly) vertical or not finite.
        inline bool YawBasis(const float front[3], float right[3], float up[3], float flatFront[3])
        {
            if (!std::isfinite(front[0]) || !std::isfinite(front[2]))
                return false;
            const float length = std::sqrt(front[0] * front[0] + front[2] * front[2]);
            if (!(length > 1e-3f))
                return false;
            const float fx = front[0] / length, fz = front[2] / length;
            flatFront[0] = fx;
            flatFront[1] = 0.0f;
            flatFront[2] = fz;
            right[0] = fz;
            right[1] = 0.0f;
            right[2] = -fx;
            up[0] = 0.0f;
            up[1] = 1.0f;
            up[2] = 0.0f;
            return true;
        }

        // ---- Power range -------------------------------------------------------
        constexpr size_t kMaxPowerRings = 16;
        // The plant vector is sanity-checked before it is walked; more than
        // this many entries means a bad read.
        constexpr size_t kMaxPlantEntries = 1024;
        constexpr float kMaxPowerRadius = 2000.0f;

        // std::vector<PowerPlant*> (_Myfirst, _Mylast): both null (empty) or
        // ordered, 4-byte aligned and not absurdly long.
        inline bool PlantVectorSane(uintptr_t first, uintptr_t last, size_t& count)
        {
            count = 0;
            if (first == 0 && last == 0)
                return true;
            if (first < 0x10000 || last < first || ((last - first) % 4u) != 0)
                return false;
            const size_t n = static_cast<size_t>((last - first) / 4u);
            if (n > kMaxPlantEntries)
                return false;
            count = n;
            return true;
        }

        struct PlantCandidate
        {
            bool ally = false; // IsAlly(rig, plant)
            float pos[3] = {0.0f, 0.0f, 0.0f};
            float radius = 0.0f; // plant class +0x160 (powerRadius)
        };

        // Indices of the plants that get a ring: allied, finite position, a
        // sane radius; the `cap` nearest (2D) to the focus point.
        inline size_t SelectPowerRings(const PlantCandidate* plants, size_t count, float focusX, float focusZ,
                                       size_t cap, size_t* outIndices)
        {
            if (!plants || !outIndices || cap == 0)
                return 0;
            size_t chosen = 0;
            float chosenDistance[kMaxPowerRings] = {};
            if (cap > kMaxPowerRings)
                cap = kMaxPowerRings;
            for (size_t i = 0; i < count; ++i)
            {
                const PlantCandidate& p = plants[i];
                if (!p.ally || !std::isfinite(p.pos[0]) || !std::isfinite(p.pos[1]) || !std::isfinite(p.pos[2]) ||
                    !std::isfinite(p.radius) || !(p.radius > 0.0f) || p.radius > kMaxPowerRadius)
                    continue;
                const float dx = p.pos[0] - focusX, dz = p.pos[2] - focusZ;
                const float d = dx * dx + dz * dz;
                size_t at = chosen;
                if (chosen == cap)
                {
                    if (!(d < chosenDistance[cap - 1]))
                        continue;
                    at = cap - 1;
                }
                else
                {
                    ++chosen;
                }
                // Insertion into the sorted list.
                while (at > 0 && chosenDistance[at - 1] > d)
                {
                    chosenDistance[at] = chosenDistance[at - 1];
                    outIndices[at] = outIndices[at - 1];
                    --at;
                }
                chosenDistance[at] = d;
                outIndices[at] = i;
            }
            return chosen;
        }

        // ---- Waypoint lines ----------------------------------------------------
        constexpr size_t kMaxWaypointUnits = 16;
        // GameObject command records (row RtsCommandPromote): current at
        // +0xA8, pending at +0xC8, 0x20 bytes each; what at +0x04, the
        // AiPath* at +0x0C.
        constexpr size_t kCurrentRecordOffset = 0xA8;
        constexpr size_t kPendingRecordOffset = 0xC8;
        constexpr size_t kRecordWhatOffset = 0x04;
        constexpr size_t kRecordPathOffset = 0x0C;
        // AiPath (row RtsAiPathCtor): point count at +4, VECTOR_2D* at +8.
        constexpr size_t kPathCountOffset = 0x04;
        constexpr size_t kPathPointsOffset = 0x08;
        constexpr int32_t kMaxPathPoints = 4096;
        constexpr int kCmdStop = 2;
        constexpr int kCmdGo = 3;
        constexpr int kCmdAttack = 4;
        constexpr int kCmdLast = 26;
        // A line shorter than this is the unit standing on its destination.
        constexpr float kMinLineLength = 2.0f;

        // Reads the destination of the command record at `object + record`:
        // the last point of its AiPath. False for none/select/stop (idle),
        // unknown command ids, no path or a nonsense path. `read(address,
        // out, size)` copies engine memory and returns false on a fault.
        template <typename Reader>
        bool CommandDestination(Reader&& read, uintptr_t object, size_t record, int& what, float& x, float& z)
        {
            what = 0;
            int32_t value = 0;
            if (!object || !read(object + record + kRecordWhatOffset, &value, sizeof(value)))
                return false;
            what = value;
            if (what <= kCmdStop || what > kCmdLast)
                return false;
            uint32_t path = 0;
            if (!read(object + record + kRecordPathOffset, &path, sizeof(path)) || path < 0x10000u)
                return false;
            int32_t count = 0;
            uint32_t points = 0;
            if (!read(static_cast<uintptr_t>(path) + kPathCountOffset, &count, sizeof(count)) || count <= 0 ||
                count > kMaxPathPoints)
                return false;
            if (!read(static_cast<uintptr_t>(path) + kPathPointsOffset, &points, sizeof(points)) || points < 0x10000u)
                return false;
            float point[2] = {};
            if (!read(static_cast<uintptr_t>(points) + 8u * static_cast<uint32_t>(count - 1), point, sizeof(point)))
                return false;
            if (!std::isfinite(point[0]) || !std::isfinite(point[1]) || std::fabs(point[0]) > 1.0e6f ||
                std::fabs(point[1]) > 1.0e6f)
                return false;
            x = point[0];
            z = point[1];
            return true;
        }

        struct LineColour
        {
            float r = 1.0f;
            float g = 1.0f;
            float b = 1.0f;
            float a = 1.0f;
        };

        // Go green, Attack red, any other order yellow (the ping colours);
        // the pending order's line is dimmer.
        inline LineColour WaypointColour(int what, bool pending)
        {
            LineColour c;
            if (what == kCmdGo)
                c = {0.30f, 1.00f, 0.40f, 0.70f};
            else if (what == kCmdAttack)
                c = {1.00f, 0.22f, 0.16f, 0.70f};
            else
                c = {1.00f, 0.86f, 0.30f, 0.70f};
            if (pending)
                c.a *= 0.45f;
            return c;
        }

        // Draped line: a ribbon sampled every kLineSegmentLength metres, at
        // most kMaxLineSegments segments (the ring strip's vertex budget).
        constexpr float kLineSegmentLength = 4.0f;
        constexpr unsigned kMaxLineSegments = 96;
        constexpr float kLineWidth = 0.6f;

        inline unsigned LineSegmentsFor(float length)
        {
            if (!std::isfinite(length) || !(length > 0.0f))
                return 1;
            const float wanted = std::ceil(length / kLineSegmentLength);
            if (wanted <= 1.0f)
                return 1;
            if (wanted >= static_cast<float>(kMaxLineSegments))
                return kMaxLineSegments;
            return static_cast<unsigned>(wanted);
        }

        // ---- Planned-route ribbon ------------------------------------------
        // A route is a polyline of sim-space {x, z} points; the first is the
        // unit's position, the last the goal.
        constexpr unsigned kMaxRoutePoints = 64;
        constexpr float kMaxMiter = 2.0f; // longest corner offset, as a multiple of the half width

        // Keeps the first kMaxRoutePoints-1 points and the goal when the route
        // is longer. Returns the number of points written to `out`.
        inline unsigned TrimRoute(const float* xz, unsigned count, float (&out)[2 * kMaxRoutePoints])
        {
            if (!xz || count == 0)
                return 0;
            if (count <= kMaxRoutePoints)
            {
                std::memcpy(out, xz, sizeof(float) * 2 * count);
                return count;
            }
            std::memcpy(out, xz, sizeof(float) * 2 * (kMaxRoutePoints - 1));
            out[2 * (kMaxRoutePoints - 1)] = xz[2 * (count - 1)];
            out[2 * (kMaxRoutePoints - 1) + 1] = xz[2 * (count - 1) + 1];
            return kMaxRoutePoints;
        }

        // One ribbon sample: the centre line point relative to the route's
        // first point, and the half-width offset to add (subtract) for the
        // ribbon's two edges.
        struct RouteSample
        {
            float x, z;
            float px, pz;
        };
        constexpr unsigned kMaxRouteSamples = kMaxLineSegments + 1;

        // Resamples the route along its arc length every kLineSegmentLength
        // metres (a longer step when that would exceed kMaxLineSegments), with
        // an extra sample on every corner so bends stay sharp. Offsets use the
        // segment's perpendicular, mitred (clamped to kMaxMiter) at corners.
        // Duplicate and non-finite points are skipped. Returns the sample
        // count, 0 when there is no usable length (fewer than 2 distinct points).
        inline unsigned BuildRouteSamples(const float* xz, unsigned count, float width,
                                          RouteSample (&out)[kMaxRouteSamples])
        {
            if (!xz || count < 2)
                return 0;
            if (count > kMaxRoutePoints)
                count = kMaxRoutePoints;
            // Distinct points relative to the first.
            float px[kMaxRoutePoints], pz[kMaxRoutePoints];
            unsigned n = 0;
            for (unsigned i = 0; i < count; ++i)
            {
                if (!std::isfinite(xz[2 * i]) || !std::isfinite(xz[2 * i + 1]))
                    continue;
                if (n == 0)
                {
                    if (i != 0)
                        return 0; // the start must be valid
                    px[0] = 0.0f;
                    pz[0] = 0.0f;
                    n = 1;
                    continue;
                }
                const float x = xz[2 * i] - xz[0], z = xz[2 * i + 1] - xz[1];
                const float dx = x - px[n - 1], dz = z - pz[n - 1];
                if (dx * dx + dz * dz < 1.0e-6f)
                    continue;
                px[n] = x;
                pz[n] = z;
                ++n;
            }
            if (n < 2)
                return 0;
            // Cumulative length and unit direction per segment.
            float cum[kMaxRoutePoints], dirX[kMaxRoutePoints], dirZ[kMaxRoutePoints];
            cum[0] = 0.0f;
            for (unsigned j = 0; j + 1 < n; ++j)
            {
                const float dx = px[j + 1] - px[j], dz = pz[j + 1] - pz[j];
                const float len = std::sqrt(dx * dx + dz * dz);
                dirX[j] = dx / len;
                dirZ[j] = dz / len;
                cum[j + 1] = cum[j] + len;
            }
            const float total = cum[n - 1];
            if (!std::isfinite(total) || !(total > 0.0f))
                return 0;

            // Sample arc lengths: uniform steps plus every corner.
            const unsigned corners = n - 2;
            unsigned uniform = LineSegmentsFor(total);
            if (uniform + corners > kMaxLineSegments)
                uniform = kMaxLineSegments > corners ? kMaxLineSegments - corners : 1;
            float at[kMaxRouteSamples + kMaxRoutePoints];
            unsigned m = 0;
            for (unsigned i = 0; i <= uniform; ++i)
                at[m++] = total * static_cast<float>(i) / static_cast<float>(uniform);
            for (unsigned j = 1; j + 1 < n; ++j)
                at[m++] = cum[j];
            std::sort(at, at + m);
            // Drop samples closer than 1 mm to the previous one.
            unsigned k = 1;
            for (unsigned i = 1; i < m; ++i)
                if (at[i] - at[k - 1] > 1.0e-3f)
                    at[k++] = at[i];
            m = k;
            if (m > kMaxRouteSamples)
                m = kMaxRouteSamples;

            const float half = 0.5f * width;
            unsigned seg = 0;
            for (unsigned i = 0; i < m; ++i)
            {
                const float s = at[i];
                while (seg + 2 < n && s > cum[seg + 1] - 1.0e-3f)
                    ++seg;
                const float t = (s - cum[seg]) / (cum[seg + 1] - cum[seg]);
                float nx = -dirZ[seg], nz = dirX[seg];
                float scale = half;
                if (seg > 0 && std::fabs(s - cum[seg]) <= 1.0e-3f)
                {
                    // A corner: average the two segments' normals.
                    const float ax = -dirZ[seg - 1], az = dirX[seg - 1];
                    float mx = ax + nx, mz = az + nz;
                    const float ml = std::sqrt(mx * mx + mz * mz);
                    if (ml > 1.0e-4f)
                    {
                        mx /= ml;
                        mz /= ml;
                        const float d = mx * nx + mz * nz; // cos of half the turn
                        scale = half * (d > 1.0f / kMaxMiter ? 1.0f / d : kMaxMiter);
                        nx = mx;
                        nz = mz;
                    }
                }
                out[i] = {px[seg] + (px[seg + 1] - px[seg]) * t, pz[seg] + (pz[seg + 1] - pz[seg]) * t,
                          nx * scale, nz * scale};
            }
            return m;
        }

        // FNV-1a over the route's float bits; lets the renderer skip a rebuild
        // while the route is unchanged.
        inline uint32_t RouteHash(const float* xz, unsigned count)
        {
            uint32_t h = 2166136261u;
            for (unsigned i = 0; i < 2 * count; ++i)
            {
                uint32_t bits = 0;
                std::memcpy(&bits, &xz[i], sizeof(bits));
                for (int b = 0; b < 4; ++b)
                {
                    h ^= (bits >> (8 * b)) & 0xFFu;
                    h *= 16777619u;
                }
            }
            return h;
        }

        inline bool ShouldDrawLine(float fromX, float fromZ, float toX, float toZ)
        {
            const float dx = toX - fromX, dz = toZ - fromZ;
            const float length = std::sqrt(dx * dx + dz * dz);
            return std::isfinite(length) && length >= kMinLineLength;
        }
    }
}
