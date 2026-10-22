#pragma once
// Pure geometry for mesh-accurate ordnance impacts: a per-part triangle BVH
// built once from the engine's own collision polygons, and a segment cast
// against it. No engine or Windows dependencies, so it is unit tested on the
// host. See reverse_engineering/ordnance_hit_test_20261021.md.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace BZROpenShim::MeshImpactGeometry
{
    struct Vec3
    {
        float x = 0, y = 0, z = 0;
    };

    inline Vec3 Sub(const Vec3& a, const Vec3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
    inline Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    inline float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    inline float Axis(const Vec3& v, int a) { return a == 0 ? v.x : (a == 1 ? v.y : v.z); }
    inline Vec3 AddScaled(const Vec3& a, const Vec3& b, float s) { return {a.x + b.x * s, a.y + b.y * s, a.z + b.z * s}; }

    struct Box
    {
        Vec3 lo{1e30f, 1e30f, 1e30f};
        Vec3 hi{-1e30f, -1e30f, -1e30f};
        void Add(const Vec3& p)
        {
            lo = {(std::min)(lo.x, p.x), (std::min)(lo.y, p.y), (std::min)(lo.z, p.z)};
            hi = {(std::max)(hi.x, p.x), (std::max)(hi.y, p.y), (std::max)(hi.z, p.z)};
        }
        void Add(const Box& b) { Add(b.lo); Add(b.hi); }
    };

    struct Hit
    {
        float t = 0;     // in units of the segment direction, like the engine's t
        Vec3 normal{};   // unit length, facing against the direction
    };

    // A large finite stand-in for 1/0 keeps the slab test free of inf * 0.
    inline float SafeReciprocal(float v)
    {
        const float clamped = v < 0.0f ? (std::min)(v, -1e-30f) : (std::max)(v, 1e-30f);
        return 1.0f / clamped;
    }

    // Slab test of origin + t*dir, t in [0, tmax]. inv holds 1/dir per axis.
    inline bool SegmentHitsBox(const Box& b, const Vec3& o, const Vec3& inv, float tmax)
    {
        float t0 = 0.0f, t1 = tmax;
        for (int a = 0; a < 3; ++a)
        {
            const float ia = Axis(inv, a), oa = Axis(o, a);
            float n = (Axis(b.lo, a) - oa) * ia;
            float f = (Axis(b.hi, a) - oa) * ia;
            if (n > f) std::swap(n, f);
            // NaN from 0 * inf (origin on a slab plane, dir 0) keeps the bound.
            if (n > t0) t0 = n;
            if (f < t1) t1 = f;
            if (t0 > t1) return false;
        }
        return true;
    }

    // Two-sided Moller-Trumbore. Returns t in (epsilon, tmax].
    inline bool SegmentHitsTriangle(const Vec3& o, const Vec3& d, const Vec3& a, const Vec3& b,
                                    const Vec3& c, float tmax, float& outT)
    {
        const Vec3 e1 = Sub(b, a), e2 = Sub(c, a);
        const Vec3 p = Cross(d, e2);
        const float det = Dot(e1, p);
        if (std::fabs(det) < 1e-12f) return false;
        const float inv = 1.0f / det;
        const Vec3 s = Sub(o, a);
        const float u = Dot(s, p) * inv;
        if (u < 0.0f || u > 1.0f) return false;
        const Vec3 q = Cross(s, e1);
        const float v = Dot(d, q) * inv;
        if (v < 0.0f || u + v > 1.0f) return false;
        const float t = Dot(e2, q) * inv;
        if (!(t >= 0.0f) || t > tmax) return false;
        outT = t;
        return true;
    }

    // Closest point on triangle abc to p (Ericson, Real-Time Collision
    // Detection, 5.1.5): classify p against the vertex, edge and face regions.
    inline Vec3 ClosestPointOnTriangle(const Vec3& p, const Vec3& a, const Vec3& b, const Vec3& c)
    {
        const Vec3 ab = Sub(b, a), ac = Sub(c, a), ap = Sub(p, a);
        const float d1 = Dot(ab, ap), d2 = Dot(ac, ap);
        if (d1 <= 0.0f && d2 <= 0.0f) return a;
        const Vec3 bp = Sub(p, b);
        const float d3 = Dot(ab, bp), d4 = Dot(ac, bp);
        if (d3 >= 0.0f && d4 <= d3) return b;
        const float vc = d1 * d4 - d3 * d2;
        if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) return AddScaled(a, ab, d1 / (d1 - d3));
        const Vec3 cp = Sub(p, c);
        const float d5 = Dot(ab, cp), d6 = Dot(ac, cp);
        if (d6 >= 0.0f && d5 <= d6) return c;
        const float vb = d5 * d2 - d1 * d6;
        if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) return AddScaled(a, ac, d2 / (d2 - d6));
        const float va = d3 * d6 - d5 * d4;
        if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
            return AddScaled(b, Sub(c, b), (d4 - d3) / ((d4 - d3) + (d5 - d6)));
        const float denom = va + vb + vc;
        if (!(std::fabs(denom) > 1e-30f)) return a; // degenerate triangle
        const float v = vb / denom, w = vc / denom;
        return AddScaled(AddScaled(a, ab, v), ac, w);
    }

    inline float BoxDistanceSq(const Box& b, const Vec3& p)
    {
        float sum = 0.0f;
        for (int a = 0; a < 3; ++a)
        {
            const float v = Axis(p, a);
            const float d = v < Axis(b.lo, a) ? Axis(b.lo, a) - v : (v > Axis(b.hi, a) ? v - Axis(b.hi, a) : 0.0f);
            sum += d * d;
        }
        return sum;
    }

    // Fans a convex polygon (the engine's Cgeom polygons are planar faces of
    // the authored collision mesh) into triangles. Returns false on an index
    // outside the vertex range, so a corrupt record rejects the whole mesh.
    template <typename Index>
    bool AppendFan(const Index* indices, uint32_t count, size_t vertexCount, std::vector<uint32_t>& tris)
    {
        if (!indices || count < 3) return true;
        for (uint32_t i = 0; i < count; ++i)
            if (static_cast<long long>(indices[i]) < 0 || static_cast<size_t>(indices[i]) >= vertexCount) return false;
        for (uint32_t i = 1; i + 1 < count; ++i)
        {
            tris.push_back(static_cast<uint32_t>(indices[0]));
            tris.push_back(static_cast<uint32_t>(indices[i]));
            tris.push_back(static_cast<uint32_t>(indices[i + 1]));
        }
        return true;
    }

    class TriangleBvh
    {
    public:
        // vertices: xyz triples. triangles: index triples into vertices.
        bool Build(std::vector<Vec3> vertices, std::vector<uint32_t> triangles)
        {
            m_vertices = std::move(vertices);
            m_triangles = std::move(triangles);
            m_nodes.clear();
            m_order.clear();
            const size_t count = m_triangles.size() / 3;
            if (count == 0 || m_triangles.size() % 3 != 0) return false;
            for (uint32_t index : m_triangles)
                if (index >= m_vertices.size()) return false;
            std::vector<Box> boxes(count);
            std::vector<Vec3> centres(count);
            for (size_t i = 0; i < count; ++i)
            {
                for (int k = 0; k < 3; ++k) boxes[i].Add(m_vertices[m_triangles[i * 3 + k]]);
                centres[i] = {(boxes[i].lo.x + boxes[i].hi.x) * 0.5f, (boxes[i].lo.y + boxes[i].hi.y) * 0.5f,
                              (boxes[i].lo.z + boxes[i].hi.z) * 0.5f};
            }
            m_order.resize(count);
            for (size_t i = 0; i < count; ++i) m_order[i] = static_cast<uint32_t>(i);
            m_nodes.reserve(count * 2);
            m_nodes.push_back({});
            BuildNode(0, 0, static_cast<uint32_t>(count), boxes, centres, 0);
            return true;
        }

        bool Empty() const { return m_nodes.empty(); }
        size_t TriangleCount() const { return m_triangles.size() / 3; }
        size_t NodeCount() const { return m_nodes.size(); }
        const Box& Bounds() const { return m_nodes.front().box; }

        // Nearest hit of origin + t*dir for t in [0, tmax].
        bool Cast(const Vec3& o, const Vec3& d, float tmax, Hit& out) const
        {
            if (m_nodes.empty() || !(tmax > 0.0f)) return false;
            const Vec3 inv{SafeReciprocal(d.x), SafeReciprocal(d.y), SafeReciprocal(d.z)};
            float best = tmax;
            uint32_t bestTri = UINT32_MAX;
            uint32_t stack[64];
            int top = 0;
            stack[top++] = 0;
            while (top > 0)
            {
                const Node& node = m_nodes[stack[--top]];
                if (!SegmentHitsBox(node.box, o, inv, best)) continue;
                if (node.count)
                {
                    for (uint32_t i = node.first; i < node.first + node.count; ++i)
                    {
                        const uint32_t tri = m_order[i];
                        float t = 0;
                        if (SegmentHitsTriangle(o, d, m_vertices[m_triangles[tri * 3]],
                                                m_vertices[m_triangles[tri * 3 + 1]],
                                                m_vertices[m_triangles[tri * 3 + 2]], best, t))
                        {
                            best = t;
                            bestTri = tri;
                        }
                    }
                }
                else if (top + 2 <= 64)
                {
                    stack[top++] = node.first;
                    stack[top++] = node.first + 1;
                }
            }
            if (bestTri == UINT32_MAX) return false;
            const Vec3& a = m_vertices[m_triangles[bestTri * 3]];
            Vec3 n = Cross(Sub(m_vertices[m_triangles[bestTri * 3 + 1]], a),
                           Sub(m_vertices[m_triangles[bestTri * 3 + 2]], a));
            const float len = std::sqrt(Dot(n, n));
            if (!(len > 0.0f)) return false;
            n = {n.x / len, n.y / len, n.z / len};
            if (Dot(n, d) > 0.0f) n = {-n.x, -n.y, -n.z};
            out.t = best;
            out.normal = n;
            return true;
        }

        // Closest surface point to p within sqrt(maxDistSq). Nodes farther
        // than the best so far are pruned by their box distance.
        bool Closest(const Vec3& p, float maxDistSq, Vec3& outPoint, float& outDistSq) const
        {
            if (m_nodes.empty()) return false;
            float best = maxDistSq;
            bool found = false;
            uint32_t stack[64];
            int top = 0;
            stack[top++] = 0;
            while (top > 0)
            {
                const Node& node = m_nodes[stack[--top]];
                if (BoxDistanceSq(node.box, p) > best) continue;
                if (node.count)
                {
                    for (uint32_t i = node.first; i < node.first + node.count; ++i)
                    {
                        const uint32_t tri = m_order[i];
                        const Vec3 q = ClosestPointOnTriangle(p, m_vertices[m_triangles[tri * 3]],
                                                              m_vertices[m_triangles[tri * 3 + 1]],
                                                              m_vertices[m_triangles[tri * 3 + 2]]);
                        const Vec3 d = Sub(q, p);
                        const float distSq = Dot(d, d);
                        if (distSq <= best)
                        {
                            best = distSq;
                            outPoint = q;
                            found = true;
                        }
                    }
                }
                else if (top + 2 <= 64)
                {
                    // Pop the nearer child first so the bound tightens early.
                    const uint32_t l = node.first, r = node.first + 1;
                    const bool leftNearer = BoxDistanceSq(m_nodes[l].box, p) <= BoxDistanceSq(m_nodes[r].box, p);
                    stack[top++] = leftNearer ? r : l;
                    stack[top++] = leftNearer ? l : r;
                }
            }
            if (found) outDistSq = best;
            return found;
        }

    private:
        struct Node
        {
            Box box;
            uint32_t first = 0; // leaf: first index into m_order; inner: left child
            uint32_t count = 0; // 0 for inner nodes
        };

        static constexpr uint32_t kLeafSize = 4;
        static constexpr int kMaxDepth = 30; // keeps the cast stack (64) bounded

        void BuildNode(uint32_t slot, uint32_t first, uint32_t count, const std::vector<Box>& boxes,
                       const std::vector<Vec3>& centres, int depth)
        {
            Box box, centreBox;
            for (uint32_t i = first; i < first + count; ++i)
            {
                box.Add(boxes[m_order[i]]);
                centreBox.Add(centres[m_order[i]]);
            }
            m_nodes[slot].box = box;
            const Vec3 extent = Sub(centreBox.hi, centreBox.lo);
            int axis = 0;
            if (extent.y > Axis(extent, axis)) axis = 1;
            if (extent.z > Axis(extent, axis)) axis = 2;
            if (count <= kLeafSize || depth >= kMaxDepth || !(Axis(extent, axis) > 0.0f))
            {
                m_nodes[slot].first = first;
                m_nodes[slot].count = count;
                return;
            }
            // Median split on the widest centroid axis. Children are allocated
            // adjacently so an inner node stores only the left index.
            const uint32_t mid = first + count / 2;
            std::nth_element(m_order.begin() + first, m_order.begin() + mid, m_order.begin() + first + count,
                             [&](uint32_t l, uint32_t r) { return Axis(centres[l], axis) < Axis(centres[r], axis); });
            const uint32_t left = static_cast<uint32_t>(m_nodes.size());
            m_nodes.push_back({});
            m_nodes.push_back({});
            m_nodes[slot].first = left;
            m_nodes[slot].count = 0;
            BuildNode(left, first, mid - first, boxes, centres, depth + 1);
            BuildNode(left + 1, mid, first + count - mid, boxes, centres, depth + 1);
        }

        std::vector<Vec3> m_vertices;
        std::vector<uint32_t> m_triangles;
        std::vector<uint32_t> m_order;
        std::vector<Node> m_nodes;
    };

    // Engine part frame: rows right/up/front plus position. A point maps to
    // world as x*right + y*up + z*front + position (BZ row-vector convention).
    struct Frame
    {
        float r[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        double p[3] = {0, 0, 0};
    };

    // world(child) = child relative to parent, then parent to world.
    inline Frame Compose(const Frame& child, const Frame& parent)
    {
        Frame out;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                out.r[i][j] = child.r[i][0] * parent.r[0][j] + child.r[i][1] * parent.r[1][j] +
                              child.r[i][2] * parent.r[2][j];
        for (int j = 0; j < 3; ++j)
            out.p[j] = child.p[0] * parent.r[0][j] + child.p[1] * parent.r[1][j] +
                       child.p[2] * parent.r[2][j] + parent.p[j];
        return out;
    }

    // General 3x3 inverse, so a scaled part is still handled. Returns false if
    // singular. inv satisfies v_local = v_world_rel * inv.
    inline bool Invert(const float m[3][3], float inv[3][3])
    {
        const float a = m[0][0], b = m[0][1], c = m[0][2];
        const float d = m[1][0], e = m[1][1], f = m[1][2];
        const float g = m[2][0], h = m[2][1], i = m[2][2];
        const float A = e * i - f * h, B = -(d * i - f * g), C = d * h - e * g;
        const float det = a * A + b * B + c * C;
        if (!(std::fabs(det) > 1e-12f) || !std::isfinite(det)) return false;
        const float s = 1.0f / det;
        inv[0][0] = A * s; inv[0][1] = -(b * i - c * h) * s; inv[0][2] = (b * f - c * e) * s;
        inv[1][0] = B * s; inv[1][1] = (a * i - c * g) * s;  inv[1][2] = -(a * f - c * d) * s;
        inv[2][0] = C * s; inv[2][1] = -(a * h - b * g) * s; inv[2][2] = (a * e - b * d) * s;
        return true;
    }

    inline Vec3 RowTimes(const float v[3], const float m[3][3])
    {
        return {v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0],
                v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1],
                v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2]};
    }

    // Casts a world segment (origin + t*dir, t in [0, tmax]) against a part
    // mesh posed by `world`. t is invariant under the affine map, so the hit t
    // is directly comparable with the engine's own t. Normal returned in world.
    inline bool CastPart(const TriangleBvh& bvh, const Frame& world, const double origin[3], const Vec3& dir,
                         float tmax, Hit& out)
    {
        float inv[3][3];
        if (!Invert(world.r, inv)) return false;
        const float rel[3] = {static_cast<float>(origin[0] - world.p[0]), static_cast<float>(origin[1] - world.p[1]),
                              static_cast<float>(origin[2] - world.p[2])};
        const float d[3] = {dir.x, dir.y, dir.z};
        const Vec3 lo = RowTimes(rel, inv);
        const Vec3 ld = RowTimes(d, inv);
        Hit local;
        if (!bvh.Cast(lo, ld, tmax, local)) return false;
        // A normal maps by the inverse transpose; for the row-vector form that
        // is n_world = inv * n (column), i.e. dot each inv row with n.
        Vec3 n{inv[0][0] * local.normal.x + inv[0][1] * local.normal.y + inv[0][2] * local.normal.z,
               inv[1][0] * local.normal.x + inv[1][1] * local.normal.y + inv[1][2] * local.normal.z,
               inv[2][0] * local.normal.x + inv[2][1] * local.normal.y + inv[2][2] * local.normal.z};
        const float len = std::sqrt(Dot(n, n));
        if (!(len > 0.0f)) return false;
        n = {n.x / len, n.y / len, n.z / len};
        if (Dot(n, dir) > 0.0f) n = {-n.x, -n.y, -n.z};
        out.t = local.t;
        out.normal = n;
        return true;
    }

    // Closest point on a posed part mesh to a world point. The search runs
    // in part space, so with a scaled frame "closest" is measured there; the
    // returned distance is the true world distance of the point found.
    inline bool ClosestOnPart(const TriangleBvh& bvh, const Frame& world, const double point[3], double outWorld[3],
                              double& outDistSq)
    {
        float inv[3][3];
        if (!Invert(world.r, inv)) return false;
        const float rel[3] = {static_cast<float>(point[0] - world.p[0]), static_cast<float>(point[1] - world.p[1]),
                              static_cast<float>(point[2] - world.p[2])};
        Vec3 local;
        float localDistSq = 0;
        if (!bvh.Closest(RowTimes(rel, inv), 1e30f, local, localDistSq)) return false;
        const float l[3] = {local.x, local.y, local.z};
        const Vec3 w = RowTimes(l, world.r);
        outWorld[0] = w.x + world.p[0];
        outWorld[1] = w.y + world.p[1];
        outWorld[2] = w.z + world.p[2];
        outDistSq = 0;
        for (int a = 0; a < 3; ++a) outDistSq += (outWorld[a] - point[a]) * (outWorld[a] - point[a]);
        return true;
    }
}
