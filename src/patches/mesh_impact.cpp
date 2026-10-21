#include "mesh_impact.h"
#include "mesh_impact_geometry.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"
#include <Windows.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <vector>

// Layout qualified against GOG 2.2.301; see
// reverse_engineering/ordnance_hit_test_20261021.md for the call chain.
//
// Bullet::Collision (thiscall, ret 0xC) tests the segment
//   start = [this+0x14] obj position, dir = (endPos - start) / t, s in [0, t]
// against every grid candidate and returns the nearest root obj (or 0). On a
// hit it has shrunk *t and written endPos = start + t*dir and the normal.
// Bullet::Simulate then moves the shot to endPos and calls Hit, which builds
// the impact explosion at endPos + 0.01*normal.
namespace BZROpenShim::MeshImpact
{
    namespace
    {
        namespace G = MeshImpactGeometry;
        using CollisionFn = void*(__fastcall*)(void* self, void* edx, float* t, double* endPos, float* normal);

        constexpr unsigned kMaxNodes = 256;
        constexpr unsigned kMaxPartVertices = 65536;
        constexpr unsigned kMaxPartFaces = 65536;
        constexpr unsigned kMaxFaceIndices = 64;
        constexpr size_t kMaxCachedTriangles = 2000000;
        // Bullet::Hit offsets the explosion 0.01 along the normal; anything
        // farther than this from the recorded engine point is someone else's.
        constexpr double kPendingMatchDistance = 0.1;
        constexpr double kSurfaceOffset = 0.01;
        // The engine reports a hit where the shot's sweep crosses the craft's
        // sphere, often metres before the hull and beyond this frame's short
        // step. The visual tier looks this far further along the same line
        // for the surface the shot would strike.
        constexpr float kVisualReach = 12.0f;
        // Craft are hit-tested against one sphere (0.75 x radius plus the shot
        // radius), so most engine hits never touch the hull. The visual tier
        // moves those effects to the nearest hull point when it is this close.
        constexpr double kSnapReach = 10.0;

        // Bullet / obj field offsets used here.
        constexpr unsigned kBulletObj = 0x14;
        constexpr unsigned kBulletSkipObj = 0xD8;  // owner obj while +0xE0 is set
        constexpr unsigned kBulletSkipFlag = 0xE0;
        constexpr unsigned kObjMatrix = 0x20;      // 9 floats, pad, 3 doubles at +0x48
        constexpr unsigned kObjPosition = 0x48;
        constexpr unsigned kObjGeometry = 0x64;
        constexpr unsigned kObjSibling = 0x7C;
        constexpr unsigned kObjChild = 0x80;
        constexpr unsigned kObjKind = 0x84;
        constexpr unsigned kObjSphereCentre = 0xA0;
        constexpr unsigned kExplosionFrame = 0x98; // [ebp-0x98] in Explosion::Init
        constexpr unsigned kExplosionObj = 0x0C;

        struct MeshEntry
        {
            uint32_t vertices = 0;
            uint32_t checksum = 0;
            std::unique_ptr<G::TriangleBvh> bvh; // null: rejected, do not retry
        };

        struct PartPose
        {
            void* geometry;
            uint32_t vertices;
            uint32_t checksum;
            G::Frame world;
        };

        struct Ray
        {
            double start[3];
            G::Vec3 dir;
            float tmax;
        };

        struct CastResult
        {
            bool tested = false; // at least one part had a usable mesh
            bool hit = false;
            G::Hit nearest{};
        };

        struct Pending
        {
            bool valid = false;
            double engine[3]{};
            double corrected[3]{};
        };

        struct Stats
        {
            uint64_t engineHits = 0, tested = 0, meshHits = 0, meshMisses = 0;
            uint64_t passThroughs = 0, effectsMoved = 0, snaps = 0, builds = 0, rejects = 0;
            uint64_t castTicks = 0, maxCastTicks = 0, buildTicks = 0;
        };

        bool g_visualRequested = false;
        bool g_gameplayRequested = false;
        bool g_gameplayActive = false;
        uint32_t g_collisionAddr = 0;
        uint32_t g_effectAddr = 0;
        InlineDetour32 g_collisionDetour;
        InlineDetour32 g_effectDetour;
        CollisionFn g_original = nullptr;
        void* g_effectResume = nullptr;
        std::unordered_map<const void*, MeshEntry> g_meshes;
        size_t g_cachedTriangles = 0;
        Pending g_pending;
        Stats g_stats;
        PartPose g_parts[kMaxNodes];
        unsigned g_partCount = 0; // parts collected by the last CastRoot
        LARGE_INTEGER g_qpcFrequency{};
        LONGLONG g_lastLogTicks = 0;

        template<class T> T& Field(void* object, unsigned offset)
        {
            return *reinterpret_cast<T*>(static_cast<unsigned char*>(object) + offset);
        }

        LONGLONG Now()
        {
            LARGE_INTEGER value;
            QueryPerformanceCounter(&value);
            return value.QuadPart;
        }

        double TicksToMicroseconds(uint64_t ticks)
        {
            return g_qpcFrequency.QuadPart ? ticks * 1e6 / static_cast<double>(g_qpcFrequency.QuadPart) : 0.0;
        }

        // Craft kinds; buildings, scrap and other props keep the engine answer.
        bool IsCraftKind(int kind) { return kind == 1 || (kind >= 3 && kind <= 7); }

        // Same exterior-surface filter as GeometryContactTest: LOD group "11",
        // mesh-bearing kinds, not hidden. Helpers, cockpit and hardpoints skip.
        bool Physical(void* object)
        {
            const int kind = Field<int>(object, kObjKind);
            const char* name = static_cast<const char*>(object) + 8;
            return name[3] == '1' && name[4] == '1' &&
                (kind == 60 || kind == 65 || kind == 66 || kind == 67 || kind == 68) &&
                !(Field<DWORD>(object, 0x14) & 1);
        }

        G::Frame ReadFrame(void* object)
        {
            G::Frame frame;
            const float* m = &Field<float>(object, kObjMatrix);
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j) frame.r[i][j] = m[i * 3 + j];
            const double* p = &Field<double>(object, kObjPosition);
            frame.p[0] = p[0];
            frame.p[1] = p[1];
            frame.p[2] = p[2];
            return frame;
        }

        uint32_t GeometryChecksum(void* geometry, uint32_t vertices)
        {
            const uint32_t* bits = Field<const uint32_t*>(geometry, 0x0C);
            uint32_t sum = vertices * 2654435761u ^ static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Field<void*>(geometry, 0x14)));
            const uint32_t words = vertices * 3;
            for (uint32_t i = 0; i < words; i += (words / 16) + 1) sum = (sum ^ bits[i]) * 16777619u;
            return sum ^ bits[words - 1];
        }

        // Walks the root's part tree composing world frames (a child's matrix
        // is relative to its parent; the root's is world). The root's own
        // sibling link is the world list and is not followed. Engine memory
        // only; fixed arrays, so it can live under __try.
        unsigned CollectParts(void* root)
        {
            struct Item { void* object; G::Frame parent; bool hasParent; };
            static Item stack[kMaxNodes];
            unsigned top = 0, visited = 0, parts = 0;
            stack[top++] = {root, {}, false};
            while (top)
            {
                const Item item = stack[--top];
                if (++visited > kMaxNodes) return 0;
                const G::Frame local = ReadFrame(item.object);
                const G::Frame world = item.hasParent ? G::Compose(local, item.parent) : local;
                if (Physical(item.object))
                {
                    void* geometry = Field<void*>(item.object, kObjGeometry);
                    const uint32_t vertices = geometry ? Field<uint32_t>(geometry, 4) : 0;
                    if (vertices >= 3 && vertices <= kMaxPartVertices && Field<void*>(geometry, 0x0C))
                        g_parts[parts++] = {geometry, vertices, GeometryChecksum(geometry, vertices), world};
                }
                void* sibling = item.hasParent ? Field<void*>(item.object, kObjSibling) : nullptr;
                void* child = Field<void*>(item.object, kObjChild);
                if (sibling)
                {
                    if (top == kMaxNodes) return 0;
                    stack[top++] = {sibling, item.parent, true};
                }
                if (child)
                {
                    if (top == kMaxNodes) return 0;
                    stack[top++] = {child, world, true};
                }
            }
            return parts;
        }

        unsigned SafeCollectParts(void* root)
        {
            __try { return CollectParts(root); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
        }

        // Legacy geometry: +4 vertex count, +0x0C float3 positions (part
        // local), +0x14 face list (+0x30 next, +4 corner count, corner records
        // of 0x10 bytes from +0x40 whose first int is the vertex index). This is
        // what Cgeom_Create (0x00444220) reads; reading it directly avoids the
        // engine allocator during combat.
        bool ReadGeometry(void* geometry, std::vector<G::Vec3>& vertices, std::vector<uint32_t>& triangles)
        {
            const uint32_t count = Field<uint32_t>(geometry, 4);
            const float* positions = Field<const float*>(geometry, 0x0C);
            vertices.resize(count);
            for (uint32_t i = 0; i < count; ++i)
            {
                vertices[i] = {positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]};
                if (!std::isfinite(vertices[i].x) || !std::isfinite(vertices[i].y) || !std::isfinite(vertices[i].z))
                    return false;
            }
            int32_t corners[kMaxFaceIndices];
            unsigned faces = 0;
            for (void* face = Field<void*>(geometry, 0x14); face; face = Field<void*>(face, 0x30))
            {
                if (++faces > kMaxPartFaces) return false;
                const uint32_t n = Field<uint32_t>(face, 4);
                if (n < 3) continue;
                if (n > kMaxFaceIndices) return false;
                for (uint32_t i = 0; i < n; ++i) corners[i] = Field<int32_t>(face, 0x40 + i * 0x10);
                if (!G::AppendFan(corners, n, count, triangles)) return false;
            }
            return !triangles.empty();
        }

        bool SafeReadGeometry(void* geometry, std::vector<G::Vec3>& vertices, std::vector<uint32_t>& triangles)
        {
            __try { return ReadGeometry(geometry, vertices, triangles); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        // Cached per geometry pointer. A freed-and-reused pointer is caught by
        // the vertex count and checksum; the mission seams drop everything.
        const G::TriangleBvh* MeshFor(const PartPose& part)
        {
            auto it = g_meshes.find(part.geometry);
            if (it != g_meshes.end() && it->second.vertices == part.vertices && it->second.checksum == part.checksum)
                return it->second.bvh.get();
            if (it != g_meshes.end())
            {
                if (it->second.bvh) g_cachedTriangles -= it->second.bvh->TriangleCount();
                g_meshes.erase(it);
            }
            MeshEntry entry;
            entry.vertices = part.vertices;
            entry.checksum = part.checksum;
            const LONGLONG begin = Now();
            std::vector<G::Vec3> vertices;
            std::vector<uint32_t> triangles;
            if (g_cachedTriangles < kMaxCachedTriangles && SafeReadGeometry(part.geometry, vertices, triangles))
            {
                auto bvh = std::make_unique<G::TriangleBvh>();
                if (bvh->Build(std::move(vertices), std::move(triangles)))
                {
                    g_cachedTriangles += bvh->TriangleCount();
                    entry.bvh = std::move(bvh);
                }
            }
            g_stats.buildTicks += static_cast<uint64_t>(Now() - begin);
            ++(entry.bvh ? g_stats.builds : g_stats.rejects);
            const G::TriangleBvh* result = entry.bvh.get();
            g_meshes.emplace(part.geometry, std::move(entry));
            return result;
        }

        bool CastRoot(void* root, const Ray& ray, CastResult& out)
        {
            const unsigned parts = SafeCollectParts(root);
            g_partCount = parts;
            for (unsigned i = 0; i < parts; ++i)
            {
                const G::TriangleBvh* bvh = MeshFor(g_parts[i]);
                if (!bvh) continue;
                out.tested = true;
                const float limit = out.hit ? out.nearest.t : ray.tmax;
                G::Hit hit;
                if (G::CastPart(*bvh, g_parts[i].world, ray.start, ray.dir, limit, hit) && (!out.hit || hit.t < out.nearest.t))
                {
                    out.hit = true;
                    out.nearest = hit;
                }
            }
            return out.tested;
        }

        // Nearest hull point to `point` over the parts the last CastRoot
        // collected, with an outward offset along the point's own direction.
        bool NearestHull(const double point[3], const G::Vec3& dir, double out[3])
        {
            double best = kSnapReach * kSnapReach;
            bool found = false;
            for (unsigned i = 0; i < g_partCount; ++i)
            {
                const G::TriangleBvh* bvh = MeshFor(g_parts[i]);
                double candidate[3], distSq = 0;
                if (bvh && G::ClosestOnPart(*bvh, g_parts[i].world, point, candidate, distSq) && distSq < best)
                {
                    best = distSq;
                    std::memcpy(out, candidate, sizeof(candidate));
                    found = true;
                }
            }
            if (!found) return false;
            double n[3] = {point[0] - out[0], point[1] - out[1], point[2] - out[2]};
            double len = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
            if (!(len > 1e-6))
            {
                // On the surface already: back off toward the shooter instead.
                n[0] = -dir.x; n[1] = -dir.y; n[2] = -dir.z;
                len = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
                if (!(len > 0.0)) return true;
            }
            for (int a = 0; a < 3; ++a) out[a] += kSurfaceOffset * n[a] / len;
            return true;
        }

        bool ReadRay(void* bullet, float t, const double end[3], Ray& ray)
        {
            __try
            {
                void* object = Field<void*>(bullet, kBulletObj);
                if (!object || !(t > 0.0f)) return false;
                const double* p = &Field<double>(object, kObjPosition);
                for (int a = 0; a < 3; ++a) ray.start[a] = p[a];
                ray.dir = {static_cast<float>((end[0] - p[0]) / t), static_cast<float>((end[1] - p[1]) / t),
                           static_cast<float>((end[2] - p[2]) / t)};
                ray.tmax = t;
                return std::isfinite(ray.dir.x) && std::isfinite(ray.dir.y) && std::isfinite(ray.dir.z);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        int SafeKind(void* object)
        {
            __try { return Field<int>(object, kObjKind); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
        }

        void MaybeLog(bool force)
        {
            const LONGLONG now = Now();
            if (!force && (now - g_lastLogTicks) < g_qpcFrequency.QuadPart * 30) return;
            g_lastLogTicks = now;
            if (!g_stats.engineHits) return;
            LogShimA(LogLevel::Info, "meshimpact",
                "engineHits=%llu tested=%llu meshHits=%llu meshMisses=%llu passThroughs=%llu effectsMoved=%llu snaps=%llu "
                "avgCastUs=%.2f maxCastUs=%.2f builds=%llu rejects=%llu buildMs=%.2f cachedTris=%zu",
                g_stats.engineHits, g_stats.tested, g_stats.meshHits, g_stats.meshMisses, g_stats.passThroughs,
                g_stats.effectsMoved, g_stats.snaps, g_stats.tested ? TicksToMicroseconds(g_stats.castTicks) / g_stats.tested : 0.0,
                TicksToMicroseconds(g_stats.maxCastTicks), g_stats.builds, g_stats.rejects,
                TicksToMicroseconds(g_stats.buildTicks) / 1000.0, g_cachedTriangles);
        }

        // Timed cast of one engine hit. False when the root is not a craft or
        // has no usable part mesh: the caller then keeps the engine answer.
        bool Evaluate(void* root, const Ray& ray, CastResult& result)
        {
            if (!IsCraftKind(SafeKind(root))) return false;
            const LONGLONG begin = Now();
            const bool tested = CastRoot(root, ray, result);
            const uint64_t ticks = static_cast<uint64_t>(Now() - begin);
            if (!tested) return false;
            ++g_stats.tested;
            g_stats.castTicks += ticks;
            if (ticks > g_stats.maxCastTicks) g_stats.maxCastTicks = ticks;
            ++(result.hit ? g_stats.meshHits : g_stats.meshMisses);
            return true;
        }

        void WriteHit(const Ray& ray, const G::Hit& hit, float* t, double* endPos, float* normal)
        {
            *t = hit.t;
            endPos[0] = ray.start[0] + static_cast<double>(hit.t) * ray.dir.x;
            endPos[1] = ray.start[1] + static_cast<double>(hit.t) * ray.dir.y;
            endPos[2] = ray.start[2] + static_cast<double>(hit.t) * ray.dir.z;
            normal[0] = hit.normal.x;
            normal[1] = hit.normal.y;
            normal[2] = hit.normal.z;
        }

        void* __fastcall CollisionHook(void* self, void* edx, float* t, double* endPos, float* normal)
        {
            g_pending.valid = false;
            const float t0 = *t;
            double end0[3];
            float normal0[3];
            std::memcpy(end0, endPos, sizeof(end0));
            std::memcpy(normal0, normal, sizeof(normal0));

            void* root = g_original(self, edx, t, endPos, normal);
            if (!root) return root;
            ++g_stats.engineHits;
            MaybeLog(false);

            Ray ray;
            CastResult result;
            if (!ReadRay(self, t0, end0, ray)) return root;
            if (!g_gameplayActive)
            {
                const float speed = std::sqrt(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z);
                if (speed > 0.0f) ray.tmax += kVisualReach / speed;
            }
            if (!Evaluate(root, ray, result)) return root;

            if (!g_gameplayActive)
            {
                // Visual tier: hand Explosion::Init the surface point the shot
                // strikes, or for a sphere hit that never touches the hull, the
                // nearest hull point. Too far from any hull keeps the engine's.
                if (!g_visualRequested || !g_effectResume) return root;
                if (result.hit)
                {
                    for (int a = 0; a < 3; ++a)
                    {
                        const float d = a == 0 ? ray.dir.x : (a == 1 ? ray.dir.y : ray.dir.z);
                        const float n = a == 0 ? result.nearest.normal.x : (a == 1 ? result.nearest.normal.y : result.nearest.normal.z);
                        g_pending.corrected[a] = ray.start[a] + static_cast<double>(result.nearest.t) * d + kSurfaceOffset * n;
                    }
                }
                else if (NearestHull(endPos, ray.dir, g_pending.corrected))
                    ++g_stats.snaps;
                else
                    return root;
                g_pending.valid = true;
                std::memcpy(g_pending.engine, endPos, sizeof(g_pending.engine));
                return root;
            }

            // Gameplay trial: the mesh decides.
            if (result.hit)
            {
                WriteHit(ray, result.nearest, t, endPos, normal);
                return root;
            }
            // The shot went between parts, or (hovering craft, box margin) has
            // not reached the hull within this frame's step; in the latter case
            // it meets the hull on a later frame. Look again with this craft skipped,
            // using the engine's own owner-skip slot. If that slot is busy (the
            // shot is still leaving its owner) keep the engine hit.
            uint8_t& skip = Field<uint8_t>(self, kBulletSkipFlag);
            void*& skipObj = Field<void*>(self, kBulletSkipObj);
            if (skip) return root;
            void* const savedObj = skipObj;
            *t = t0;
            std::memcpy(endPos, end0, sizeof(end0));
            std::memcpy(normal, normal0, sizeof(normal0));
            skipObj = root;
            skip = 1;
            void* next = g_original(self, edx, t, endPos, normal);
            skipObj = savedObj;
            skip = 0;
            ++g_stats.passThroughs;
            CastResult second;
            if (next && !Evaluate(next, ray, second)) return next;
            if (next && second.hit)
            {
                WriteHit(ray, second.nearest, t, endPos, normal);
                return next;
            }
            // Nothing solid on the segment: the shot flies on to its end.
            *t = t0;
            std::memcpy(endPos, end0, sizeof(end0));
            std::memcpy(normal, normal0, sizeof(normal0));
            return nullptr;
        }

        // Runs at 0x004CA0C1 in Explosion::Init, after splash damage and before
        // the render effect and particles read the explosion matrix. Moves the
        // explosion onto the hull and shifts its local sphere centre the other
        // way, so Explosion::Simulate's physics kick keeps the engine centre.
        void __cdecl ApplyEffectPosition(uint8_t* frame)
        {
            if (!g_pending.valid) return;
            g_pending.valid = false;
            __try
            {
                void* explosion = *reinterpret_cast<void**>(frame - kExplosionFrame);
                void* object = explosion ? Field<void*>(explosion, kExplosionObj) : nullptr;
                if (!object) return;
                double* p = &Field<double>(object, kObjPosition);
                double d2 = 0;
                for (int a = 0; a < 3; ++a) d2 += (p[a] - g_pending.engine[a]) * (p[a] - g_pending.engine[a]);
                if (d2 > kPendingMatchDistance * kPendingMatchDistance) return;
                const G::Frame frameNow = ReadFrame(object);
                float inv[3][3];
                if (!G::Invert(frameNow.r, inv)) return;
                const float offset[3] = {static_cast<float>(p[0] - g_pending.corrected[0]),
                                         static_cast<float>(p[1] - g_pending.corrected[1]),
                                         static_cast<float>(p[2] - g_pending.corrected[2])};
                const G::Vec3 local = G::RowTimes(offset, inv);
                float* centre = &Field<float>(object, kObjSphereCentre);
                centre[0] += local.x;
                centre[1] += local.y;
                centre[2] += local.z;
                for (int a = 0; a < 3; ++a) p[a] = g_pending.corrected[a];
                ++g_stats.effectsMoved;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        // Entered by a 5-byte JMP over two whole integer moves, so EBP is still
        // Explosion::Init's frame. XMM state is not live here: the next
        // instructions are integer moves and a call (caller-saved ABI).
        __declspec(naked) void EffectThunk()
        {
            __asm
            {
                pushad
                pushfd
                push ebp
                call ApplyEffectPosition
                add  esp, 4
                popfd
                popad
                jmp  dword ptr [g_effectResume]
            }
        }

        bool Install()
        {
            HookEngine::FrameThreadSitesScope frameSites;
            const HookEngine::EngineRow rows[] = {
                {"BulletCollisionEntry", &g_collisionAddr},
                {"ExplosionInitEffectSite", &g_effectAddr},
            };
            if (!HookEngine::BindEngineRows("Mesh-accurate impacts", rows)) return false;
            // Whole instructions; the /GS cookie load is position independent.
            static const uint8_t kCollisionExpected[] = {0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xAC, 0x00, 0x00, 0x00};
            static const uint8_t kEffectExpected[] = {0x8B, 0x85, 0x68, 0xFF, 0xFF, 0xFF, 0x8B, 0x48, 0x08};
            if (!g_original)
            {
                if (!InstallInlineDetour32(g_collisionDetour, g_collisionAddr, reinterpret_cast<void*>(&CollisionHook),
                                           sizeof(kCollisionExpected), kCollisionExpected, sizeof(kCollisionExpected)))
                    return false;
                g_original = reinterpret_cast<CollisionFn>(g_collisionDetour.trampoline);
            }
            if (g_visualRequested && !g_effectResume &&
                InstallInlineDetour32(g_effectDetour, g_effectAddr, reinterpret_cast<void*>(&EffectThunk),
                                      sizeof(kEffectExpected), kEffectExpected, sizeof(kEffectExpected)))
                g_effectResume = g_effectDetour.trampoline;
            return true;
        }
    }

    void InitializeGlobal()
    {
        HookEngine::CodePatchLock lock;
        QueryPerformanceFrequency(&g_qpcFrequency);
        bool visual = false, gameplay = false;
        TryGetUserConfigBool(Hooks::kUserConfigDisplaySection, "MeshAccurateImpacts", visual);
        TryGetUserConfigBool(Hooks::kUserConfigSinglePlayerSection, "MeshAccurateHits", gameplay);
        g_visualRequested = visual || EnvFlagEnabled("OPENSHIM_MESH_IMPACTS");
        g_gameplayRequested = gameplay || EnvFlagEnabled("OPENSHIM_MESH_HITS");
        if (!g_visualRequested && !g_gameplayRequested) return;
        // GOG layout only; the mission seams own cache retirement.
        const bool installed = !g_IsSteamExe && Hooks::g_MissionSeamInstalled && Install();
        LogShimA(LogLevel::Info, "meshimpact", "visual=%s gameplay=%s (single player only) hooks=%s effectSite=%s",
            g_visualRequested ? "requested" : "off", g_gameplayRequested ? "requested" : "off",
            installed ? "installed" : "unavailable", g_effectResume ? "installed" : "off");
        if (!installed) g_visualRequested = g_gameplayRequested = false;
        RefreshGate();
    }

    void RefreshGate()
    {
        g_gameplayActive = g_gameplayRequested && g_original && Hooks::IsSinglePlayerSession();
    }

    void Clear()
    {
        if (!g_original) return;
        HookEngine::CodePatchLock lock;
        MaybeLog(true);
        g_meshes.clear();
        g_cachedTriangles = 0;
        g_pending = {};
        g_stats = {};
    }
}
