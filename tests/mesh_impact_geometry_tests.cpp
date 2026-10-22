// Tests for include/mesh_impact_geometry.h: segment/triangle and slab tests,
// the triangle BVH against brute force, part-frame composition, and the
// world-space cast through a rotated, scaled, offset part.
#include "mesh_impact_geometry.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    namespace G = BZROpenShim::MeshImpactGeometry;

    bool Near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) <= eps; }

    // Cube [-1,1]^3 as six quads, fanned like Cgeom polygons.
    void MakeCube(std::vector<G::Vec3>& verts, std::vector<uint32_t>& tris)
    {
        verts.clear();
        tris.clear();
        for (int i = 0; i < 8; ++i)
            verts.push_back({(i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f, (i & 4) ? 1.0f : -1.0f});
        const uint16_t faces[6][4] = {{0, 1, 3, 2}, {4, 6, 7, 5}, {0, 4, 5, 1}, {2, 3, 7, 6}, {0, 2, 6, 4}, {1, 5, 7, 3}};
        for (const auto& f : faces) G::AppendFan(f, 4, verts.size(), tris);
    }

    void TestTriangle()
    {
        float t = 0;
        const G::Vec3 a{0, 0, 0}, b{1, 0, 0}, c{0, 1, 0};
        Check(G::SegmentHitsTriangle({0.2f, 0.2f, -1}, {0, 0, 1}, a, b, c, 10, t) && Near(t, 1), "front hit");
        Check(G::SegmentHitsTriangle({0.2f, 0.2f, 1}, {0, 0, -1}, a, b, c, 10, t) && Near(t, 1), "back face hits too");
        Check(!G::SegmentHitsTriangle({0.2f, 0.2f, -1}, {0, 0, 1}, a, b, c, 0.5f, t), "beyond tmax misses");
        Check(!G::SegmentHitsTriangle({0.8f, 0.8f, -1}, {0, 0, 1}, a, b, c, 10, t), "outside the triangle misses");
        Check(!G::SegmentHitsTriangle({0.2f, 0.2f, -1}, {1, 0, 0}, a, b, c, 10, t), "parallel misses");
    }

    void TestFan()
    {
        std::vector<uint32_t> tris;
        const uint16_t quad[4] = {0, 1, 2, 3};
        Check(G::AppendFan(quad, 4, 4, tris) && tris.size() == 6, "quad fans to two triangles");
        const uint16_t bad[3] = {0, 1, 9};
        Check(!G::AppendFan(bad, 3, 4, tris), "out-of-range index rejects");
        tris.clear();
        Check(G::AppendFan(quad, 2, 4, tris) && tris.empty(), "degenerate polygon is skipped");
    }

    void TestCube()
    {
        std::vector<G::Vec3> v;
        std::vector<uint32_t> t;
        MakeCube(v, t);
        G::TriangleBvh bvh;
        Check(bvh.Build(v, t), "cube builds");
        G::Hit hit;
        Check(bvh.Cast({-5, 0.1f, 0.2f}, {1, 0, 0}, 100, hit) && Near(hit.t, 4) && Near(hit.normal.x, -1),
              "hits the near face with an opposing normal");
        Check(!bvh.Cast({-5, 3, 0}, {1, 0, 0}, 100, hit), "passes beside the cube");
        Check(!bvh.Cast({-5, 0, 0}, {1, 0, 0}, 3.5f, hit), "segment ends short");
        // Engine-style direction: a velocity scaled by t, so t is not metres.
        Check(bvh.Cast({-5, 0, 0}, {10, 0, 0}, 1, hit) && Near(hit.t, 0.4f), "t is in direction units");
        Check(!G::TriangleBvh().Build(v, {0, 1, 99}), "bad triangle index rejects the build");
    }

    // Two boxes with a gap between them: the "between the cannon and the body"
    // case. A segment through the gap must miss.
    void TestGapAndBruteForce()
    {
        std::vector<G::Vec3> v;
        std::vector<uint32_t> t;
        std::vector<G::Vec3> cv;
        std::vector<uint32_t> ct;
        MakeCube(cv, ct);
        for (int box = 0; box < 2; ++box)
        {
            const uint32_t base = static_cast<uint32_t>(v.size());
            for (const auto& p : cv) v.push_back({p.x, p.y + (box ? 3.0f : 0.0f), p.z});
            for (uint32_t i : ct) t.push_back(base + i);
        }
        G::TriangleBvh bvh;
        bvh.Build(v, t);
        G::Hit hit;
        Check(!bvh.Cast({-5, 1.5f, 0}, {1, 0, 0}, 100, hit), "segment through the gap misses");
        Check(bvh.Cast({-5, 3.2f, 0}, {1, 0, 0}, 100, hit) && Near(hit.t, 4), "upper box hit");

        // Random triangle soup: the BVH must agree with brute force.
        std::vector<G::Vec3> sv;
        std::vector<uint32_t> st;
        uint32_t seed = 12345;
        auto rnd = [&]() {
            seed = seed * 1664525u + 1013904223u;
            return static_cast<float>(seed >> 8) / 16777216.0f * 2.0f - 1.0f;
        };
        for (uint32_t i = 0; i < 600; ++i)
        {
            const G::Vec3 c{rnd() * 5, rnd() * 5, rnd() * 5};
            for (int k = 0; k < 3; ++k) sv.push_back({c.x + rnd() * 0.6f, c.y + rnd() * 0.6f, c.z + rnd() * 0.6f});
            st.push_back(i * 3);
            st.push_back(i * 3 + 1);
            st.push_back(i * 3 + 2);
        }
        G::TriangleBvh soup;
        Check(soup.Build(sv, st), "soup builds");
        Check(soup.NodeCount() < st.size(), "node count is bounded");
        int mismatches = 0, hits = 0;
        for (int r = 0; r < 400; ++r)
        {
            const G::Vec3 o{rnd() * 8, rnd() * 8, -9};
            const G::Vec3 d{rnd() * 0.3f, rnd() * 0.3f, 1};
            float best = 20;
            bool any = false;
            for (size_t i = 0; i < st.size(); i += 3)
            {
                float tt = 0;
                if (G::SegmentHitsTriangle(o, d, sv[st[i]], sv[st[i + 1]], sv[st[i + 2]], best, tt))
                {
                    best = tt;
                    any = true;
                }
            }
            G::Hit h;
            const bool got = soup.Cast(o, d, 20, h);
            if (got != any || (got && !Near(h.t, best, 1e-3f))) ++mismatches;
            hits += any ? 1 : 0;
        }
        Check(mismatches == 0, "BVH matches brute force");
        Check(hits > 20, "the brute-force sample actually hits");
    }

    void TestFrames()
    {
        // Parent: 90 degrees about Y (right -> -Z), at (10,0,0). Child: offset
        // (0,2,1) in the parent, uniform scale 2.
        G::Frame parent;
        parent.r[0][0] = 0; parent.r[0][1] = 0; parent.r[0][2] = -1;
        parent.r[1][0] = 0; parent.r[1][1] = 1; parent.r[1][2] = 0;
        parent.r[2][0] = 1; parent.r[2][1] = 0; parent.r[2][2] = 0;
        parent.p[0] = 10;
        G::Frame child;
        for (int i = 0; i < 3; ++i) child.r[i][i] = 2;
        child.p[1] = 2;
        child.p[2] = 1;
        const G::Frame world = G::Compose(child, parent);
        // Child origin: (0,2,1)*R_p + (10,0,0) = (0,2,0)+(1,0,0)+(10,0,0).
        Check(std::fabs(world.p[0] - 11) < 1e-9 && std::fabs(world.p[1] - 2) < 1e-9 && std::fabs(world.p[2]) < 1e-9,
              "child origin composes through the parent");
        Check(Near(world.r[0][2], -2), "child right axis is scaled and rotated");

        std::vector<G::Vec3> v;
        std::vector<uint32_t> t;
        MakeCube(v, t);
        G::TriangleBvh bvh;
        bvh.Build(v, t);
        // World cube spans x in [9,13], y in [0,4], z in [-2,2].
        G::Hit hit;
        const double o[3] = {11, 2, -10};
        Check(G::CastPart(bvh, world, o, {0, 0, 1}, 100, hit) && Near(hit.t, 8, 1e-3f), "world cast hits the scaled part");
        Check(Near(hit.normal.z, -1, 1e-3f), "world normal faces the shooter");
        const double miss[3] = {14, 2, -10};
        Check(!G::CastPart(bvh, world, miss, {0, 0, 1}, 100, hit), "world cast beside the part misses");

        float inv[3][3];
        G::Frame singular;
        singular.r[2][0] = singular.r[2][1] = singular.r[2][2] = 0;
        Check(!G::Invert(singular.r, inv), "a singular frame is rejected");

        // Nearest hull point to a point 3 above the world cube's top face.
        double near[3] = {}, distSq = 0;
        const double above[3] = {11, 7, 0};
        Check(G::ClosestOnPart(bvh, world, above, near, distSq) && std::fabs(near[1] - 4) < 1e-3 &&
                  std::fabs(near[0] - 11) < 1e-3 && std::fabs(distSq - 9) < 1e-2,
              "nearest point on the scaled part is straight below");
    }

    void TestClosest()
    {
        const G::Vec3 a{0, 0, 0}, b{1, 0, 0}, c{0, 1, 0};
        const G::Vec3 face = G::ClosestPointOnTriangle({0.2f, 0.2f, 5}, a, b, c);
        Check(Near(face.x, 0.2f) && Near(face.y, 0.2f) && Near(face.z, 0), "face region projects");
        const G::Vec3 vertex = G::ClosestPointOnTriangle({-1, -1, 0}, a, b, c);
        Check(Near(vertex.x, 0) && Near(vertex.y, 0), "vertex region clamps to a");
        const G::Vec3 edge = G::ClosestPointOnTriangle({1, 1, 0}, a, b, c);
        Check(Near(edge.x, 0.5f) && Near(edge.y, 0.5f), "hypotenuse region clamps to bc");

        std::vector<G::Vec3> v;
        std::vector<uint32_t> t;
        MakeCube(v, t);
        G::TriangleBvh bvh;
        bvh.Build(v, t);
        G::Vec3 q;
        float distSq = 0;
        Check(bvh.Closest({0.3f, 4, -0.2f}, 1e30f, q, distSq) && Near(q.y, 1) && Near(distSq, 9), "cube top is nearest");
        Check(bvh.Closest({3, 3, 0}, 1e30f, q, distSq) && Near(q.x, 1) && Near(q.y, 1) && Near(distSq, 8),
              "cube edge is nearest off the corner");
        Check(!bvh.Closest({0, 5, 0}, 1.0f, q, distSq), "nothing within the bound");

        // Brute force over a random soup.
        std::vector<G::Vec3> sv;
        std::vector<uint32_t> st;
        uint32_t seed = 7;
        auto rnd = [&]() {
            seed = seed * 1664525u + 1013904223u;
            return static_cast<float>(seed >> 8) / 16777216.0f * 2.0f - 1.0f;
        };
        for (uint32_t i = 0; i < 300; ++i)
        {
            const G::Vec3 centre{rnd() * 5, rnd() * 5, rnd() * 5};
            for (int k = 0; k < 3; ++k) sv.push_back({centre.x + rnd(), centre.y + rnd(), centre.z + rnd()});
            st.push_back(i * 3);
            st.push_back(i * 3 + 1);
            st.push_back(i * 3 + 2);
        }
        G::TriangleBvh soup;
        soup.Build(sv, st);
        int mismatches = 0;
        for (int r = 0; r < 200; ++r)
        {
            const G::Vec3 p{rnd() * 9, rnd() * 9, rnd() * 9};
            float best = 1e30f;
            for (size_t i = 0; i < st.size(); i += 3)
            {
                const G::Vec3 d = G::Sub(G::ClosestPointOnTriangle(p, sv[st[i]], sv[st[i + 1]], sv[st[i + 2]]), p);
                best = (std::min)(best, G::Dot(d, d));
            }
            if (!soup.Closest(p, 1e30f, q, distSq) || !Near(distSq, best, 1e-3f)) ++mismatches;
        }
        Check(mismatches == 0, "closest-point BVH matches brute force");
    }
}

int main()
{
    TestTriangle();
    TestFan();
    TestCube();
    TestGapAndBruteForce();
    TestFrames();
    TestClosest();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("mesh_impact_geometry_tests passed\n");
    return OpenShimTest::ExitCode();
}
