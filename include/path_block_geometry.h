// path_block_geometry.h
// BZR Open Shim - pure geometry for PathBlockFaces (src/patches/path_block.cpp).
//
// Stock AI planning blocks the whole oriented SDF bounding box of a building in
// the 2-D path grid. For an ODF that opts in with
//
//     [GameObjectClass]
//     pathBlock = "faces"      ; "box" (default) | "faces" | "none"
//     pathBlockHeight = 1.5    ; local sample height above the origin
//     pathBlockHeight2 = 3.0   ; second sample height
//
// a cell of the stock box is blocked only when its centre is inside the
// object's LOD collision solids at either sample height. "Inside" is the
// nonzero winding number of a ray cast from the sample point along local +X
// through the collision triangles: +1 for a face whose normal points against
// the ray (entering), -1 for one pointing along it (exiting). Parts are closed
// solids that may overlap, so even-odd parity would be wrong.
//
// Everything here is engine-independent so the host tests can pin it and the
// offline dry-check harness (tests/path_block_dry_check.cpp) runs the same code
// against real SDF/GEO files. The engine contract (cell size, world-to-cell
// mapping, the BuildingBlock quad rule) is ported from GOG Redux 2.2.301; see
// path_block.cpp for the addresses.
//
// The shared contract with EXU is PATHBLOCK_CONTRACT.md (Bane building kit).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace BZROpenShim
{
namespace PathBlock
{
    enum class Mode : uint8_t
    {
        Box,   // stock behaviour
        Faces, // block only cells whose centre is inside solid geometry
        None,  // block nothing
    };

    inline const char* ModeName(Mode m)
    {
        switch (m)
        {
        case Mode::Faces: return "faces";
        case Mode::None: return "none";
        default: return "box";
        }
    }

    struct Spec
    {
        Mode mode = Mode::Box;
        float height1 = 1.5f;
        float height2 = 3.0f;
        std::string baseName; // [GameObjectClass] baseName/geometryName, lowercase, may be empty
    };

    namespace Detail
    {
        inline char Lower(char c) { return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + 32) : c; }

        inline bool IEquals(std::string_view a, std::string_view b)
        {
            if (a.size() != b.size())
                return false;
            for (size_t i = 0; i < a.size(); ++i)
                if (Lower(a[i]) != Lower(b[i]))
                    return false;
            return true;
        }

        inline std::string_view Trim(std::string_view s)
        {
            while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r' || s.front() == '\n'))
                s.remove_prefix(1);
            while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '\n'))
                s.remove_suffix(1);
            return s;
        }

        inline std::string_view StripComment(std::string_view s)
        {
            // ODF comments: "//" anywhere, ";" anywhere (outside a quoted value).
            bool quoted = false;
            for (size_t i = 0; i < s.size(); ++i)
            {
                const char c = s[i];
                if (c == '"')
                    quoted = !quoted;
                if (quoted)
                    continue;
                if (c == ';' || (c == '/' && i + 1 < s.size() && s[i + 1] == '/'))
                    return s.substr(0, i);
            }
            return s;
        }

        inline std::string Unquote(std::string_view v)
        {
            v = Trim(v);
            if (v.size() >= 2 && (v.front() == '"' || v.front() == '\'') && v.back() == v.front())
                v = v.substr(1, v.size() - 2);
            v = Trim(v);
            std::string out(v);
            for (char& c : out)
                c = Lower(c);
            return out;
        }

        inline bool ParseFloat(std::string_view v, float& out)
        {
            const std::string s = Unquote(v);
            if (s.empty())
                return false;
            char* end = nullptr;
            const float f = std::strtof(s.c_str(), &end);
            if (end == s.c_str())
                return false;
            while (*end == ' ' || *end == '\t' || *end == 'f')
                ++end;
            if (*end != '\0' || !std::isfinite(f))
                return false;
            out = f;
            return true;
        }
    }

    // Reads the three contract keys (and the geometry base name) from the
    // [GameObjectClass] section. Section and key names ignore case; unknown
    // pathBlock values fall back to "box". Returns true when pathBlock was
    // present at all (whatever its value).
    inline bool ParseOdfSpec(std::string_view text, Spec& out)
    {
        out = Spec{};
        bool inClass = false;
        bool sawPathBlock = false;
        size_t pos = 0;
        while (pos <= text.size())
        {
            size_t eol = text.find('\n', pos);
            if (eol == std::string_view::npos)
                eol = text.size();
            std::string_view line = Detail::Trim(Detail::StripComment(text.substr(pos, eol - pos)));
            pos = eol + 1;
            if (line.empty())
                continue;
            if (line.front() == '[')
            {
                const size_t close = line.find(']');
                const std::string_view name =
                    Detail::Trim(line.substr(1, close == std::string_view::npos ? line.size() - 1 : close - 1));
                inClass = Detail::IEquals(name, "GameObjectClass");
                continue;
            }
            if (!inClass)
                continue;
            const size_t eq = line.find('=');
            if (eq == std::string_view::npos)
                continue;
            const std::string_view key = Detail::Trim(line.substr(0, eq));
            const std::string_view value = line.substr(eq + 1);
            if (Detail::IEquals(key, "pathBlock"))
            {
                sawPathBlock = true;
                const std::string v = Detail::Unquote(value);
                out.mode = v == "faces" ? Mode::Faces : (v == "none" ? Mode::None : Mode::Box);
            }
            else if (Detail::IEquals(key, "pathBlockHeight"))
            {
                float f = 0.0f;
                if (Detail::ParseFloat(value, f))
                    out.height1 = f;
            }
            else if (Detail::IEquals(key, "pathBlockHeight2"))
            {
                float f = 0.0f;
                if (Detail::ParseFloat(value, f))
                    out.height2 = f;
            }
            else if (Detail::IEquals(key, "baseName") || (out.baseName.empty() && Detail::IEquals(key, "geometryName")))
            {
                out.baseName = Detail::Unquote(value);
            }
        }
        return sawPathBlock;
    }

    // ---------------------------------------------------------------------
    // SDF / GEO parsing
    // ---------------------------------------------------------------------

    struct Vec3
    {
        double x = 0.0, y = 0.0, z = 0.0;
    };

    // 3x4 affine in the SDF layout: right, up, front, posit.
    struct Affine
    {
        double m[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};

        Vec3 Apply(const Vec3& v) const
        {
            return {v.x * m[0] + v.y * m[3] + v.z * m[6] + m[9],
                    v.x * m[1] + v.y * m[4] + v.z * m[7] + m[10],
                    v.x * m[2] + v.y * m[5] + v.z * m[8] + m[11]};
        }

        // this(child(v)): the child frame expressed in this frame.
        Affine Compose(const Affine& child) const
        {
            Affine r;
            for (int axis = 0; axis < 3; ++axis)
            {
                const double* c = &child.m[axis * 3];
                r.m[axis * 3 + 0] = c[0] * m[0] + c[1] * m[3] + c[2] * m[6];
                r.m[axis * 3 + 1] = c[0] * m[1] + c[1] * m[4] + c[2] * m[7];
                r.m[axis * 3 + 2] = c[0] * m[2] + c[1] * m[5] + c[2] * m[8];
            }
            const Vec3 p = Apply({child.m[9], child.m[10], child.m[11]});
            r.m[9] = p.x;
            r.m[10] = p.y;
            r.m[11] = p.z;
            return r;
        }

        double Determinant() const
        {
            return m[0] * (m[4] * m[8] - m[5] * m[7]) - m[3] * (m[1] * m[8] - m[2] * m[7]) +
                   m[6] * (m[1] * m[5] - m[2] * m[4]);
        }
    };

    struct SdfGeo
    {
        std::string name;   // lowercase, no extension
        std::string parent; // lowercase; "world" for the root
        Affine local;
    };

    namespace Detail
    {
        inline std::string FixedName(const uint8_t* p, size_t n)
        {
            std::string s;
            for (size_t i = 0; i < n && p[i]; ++i)
                s.push_back(Lower(static_cast<char>(p[i])));
            return s;
        }

        inline float ReadF32(const uint8_t* p)
        {
            float f;
            std::memcpy(&f, p, 4);
            return f;
        }

        inline int32_t ReadI32(const uint8_t* p)
        {
            int32_t v;
            std::memcpy(&v, p, 4);
            return v;
        }
    }

    // SDF: "BWD2" header, then tagged sections; SGEO = tag, length, count,
    // then count x 120-byte records (name[8], 12 floats right/up/front/posit,
    // parent[8], centre, radius, half extents, type, flags, ddr, 4 floats).
    inline bool ParseSdfGeos(const uint8_t* data, size_t size, std::vector<SdfGeo>& out)
    {
        out.clear();
        if (!data || size < 32 || std::memcmp(data, "BWD2", 4) != 0)
            return false;
        // Find the SGEO tag. Sections are walked by length where possible;
        // a tag search is the fallback (lengths in the wild are not reliable).
        size_t at = 0;
        for (size_t i = 0; i + 12 <= size; ++i)
        {
            if (std::memcmp(data + i, "SGEO", 4) == 0)
            {
                at = i;
                break;
            }
        }
        if (at == 0)
            return false;
        const int32_t count = Detail::ReadI32(data + at + 8);
        constexpr size_t kRecord = 120;
        if (count <= 0 || count > 4096 || at + 12 + static_cast<size_t>(count) * kRecord > size)
            return false;
        const uint8_t* rec = data + at + 12;
        for (int32_t i = 0; i < count; ++i, rec += kRecord)
        {
            SdfGeo g;
            g.name = Detail::FixedName(rec, 8);
            for (int k = 0; k < 12; ++k)
                g.local.m[k] = Detail::ReadF32(rec + 8 + 4 * k);
            g.parent = Detail::FixedName(rec + 56, 8);
            out.push_back(std::move(g));
        }
        return true;
    }

    // GEO: ".GEO"(LE "OEG."), checksum, name[16], vertCount, faceCount, flags,
    // positions, normals, then per face: index, vcount, rgb[3], 4 floats
    // (plane - not reliable in exporter output, so unused), area, 3 bytes,
    // texture[13], parent, branch, vcount x {vert, normal, u, v}.
    // Polygons are fanned into triangles in stored order.
    inline bool ParseGeoTriangles(const uint8_t* data, size_t size, std::vector<Vec3>& triVerts)
    {
        triVerts.clear();
        if (!data || size < 36)
            return false;
        const int32_t nv = Detail::ReadI32(data + 24);
        const int32_t nf = Detail::ReadI32(data + 28);
        if (nv < 0 || nf < 0 || nv > 1000000 || nf > 1000000)
            return false;
        size_t off = 36;
        if (off + static_cast<size_t>(nv) * 24 > size)
            return false;
        std::vector<Vec3> verts(static_cast<size_t>(nv));
        for (int32_t i = 0; i < nv; ++i)
            verts[i] = {Detail::ReadF32(data + off + 12 * i), Detail::ReadF32(data + off + 12 * i + 4),
                        Detail::ReadF32(data + off + 12 * i + 8)};
        off += static_cast<size_t>(nv) * 24;
        for (int32_t f = 0; f < nf; ++f)
        {
            constexpr size_t kFaceHeader = 8 + 3 + 20 + 3 + 13 + 8;
            if (off + kFaceHeader > size)
                return false;
            const int32_t vc = Detail::ReadI32(data + off + 4);
            off += kFaceHeader;
            if (vc < 0 || vc > 4096 || off + static_cast<size_t>(vc) * 16 > size)
                return false;
            std::vector<int32_t> idx(static_cast<size_t>(vc));
            for (int32_t k = 0; k < vc; ++k)
                idx[k] = Detail::ReadI32(data + off + 16 * k);
            off += static_cast<size_t>(vc) * 16;
            for (int32_t k = 1; k + 1 < vc; ++k)
            {
                const int32_t a = idx[0], b = idx[k], c = idx[k + 1];
                if (a < 0 || b < 0 || c < 0 || a >= nv || b >= nv || c >= nv)
                    return false;
                triVerts.push_back(verts[a]);
                triVerts.push_back(verts[b]);
                triVerts.push_back(verts[c]);
            }
        }
        return true;
    }

    // ---------------------------------------------------------------------
    // Solid model and winding
    // ---------------------------------------------------------------------

    struct Tri
    {
        Vec3 a, b, c;
        double minY, maxY, minZ, maxZ, maxX;
    };

    struct Model
    {
        std::vector<Tri> tris;
        double minX = 0, maxX = 0, minY = 0, maxY = 0, minZ = 0, maxZ = 0;
        int geoCount = 0;
        std::string lodNote;

        void AddTriangle(const Vec3& a, const Vec3& b, const Vec3& c)
        {
            Tri t{a, b, c, 0, 0, 0, 0, 0};
            t.minY = std::min({a.y, b.y, c.y});
            t.maxY = std::max({a.y, b.y, c.y});
            t.minZ = std::min({a.z, b.z, c.z});
            t.maxZ = std::max({a.z, b.z, c.z});
            t.maxX = std::max({a.x, b.x, c.x});
            if (tris.empty())
            {
                minX = std::min({a.x, b.x, c.x});
                maxX = t.maxX;
                minY = t.minY;
                maxY = t.maxY;
                minZ = t.minZ;
                maxZ = t.maxZ;
            }
            else
            {
                minX = std::min({minX, a.x, b.x, c.x});
                maxX = std::max(maxX, t.maxX);
                minY = std::min(minY, t.minY);
                maxY = std::max(maxY, t.maxY);
                minZ = std::min(minZ, t.minZ);
                maxZ = std::max(maxZ, t.maxZ);
            }
            tris.push_back(t);
        }
    };

    // Sunday's winding rule for one triangle projected on the (y, z) plane,
    // with u = y and v = z. Half-open in v and strict in the edge test, so a
    // point on an edge shared by two triangles counts in exactly one of them.
    // Returns +1 / -1 (the projected orientation) when inside, else 0.
    inline int TriangleWinding2D(const Tri& t, double pu, double pv)
    {
        const double u[3] = {t.a.y, t.b.y, t.c.y};
        const double v[3] = {t.a.z, t.b.z, t.c.z};
        int wn = 0;
        for (int i = 0; i < 3; ++i)
        {
            const int j = (i + 1) % 3;
            const double isLeft = (u[j] - u[i]) * (pv - v[i]) - (pu - u[i]) * (v[j] - v[i]);
            if (v[i] <= pv)
            {
                if (v[j] > pv && isLeft > 0.0)
                    ++wn;
            }
            else if (v[j] <= pv && isLeft < 0.0)
            {
                --wn;
            }
        }
        return wn;
    }

    // Winding number of point p for a ray along +X. A face whose normal has
    // x > 0 (points along the ray) contributes -1, x < 0 contributes +1.
    // The projected (y,z) orientation of a triangle has the sign of its normal
    // x, so the contribution is minus the 2-D winding. Normals follow the
    // stored vertex order: n = (b - a) x (c - a), outward for BZ GEO solids.
    inline int WindingAt(const Model& model, const Vec3& p)
    {
        int total = 0;
        for (const Tri& t : model.tris)
        {
            if (p.y < t.minY || p.y > t.maxY || p.z < t.minZ || p.z > t.maxZ || t.maxX <= p.x)
                continue;
            const int wn = TriangleWinding2D(t, p.y, p.z);
            if (wn == 0)
                continue;
            const double e1x = t.b.x - t.a.x, e1y = t.b.y - t.a.y, e1z = t.b.z - t.a.z;
            const double e2x = t.c.x - t.a.x, e2y = t.c.y - t.a.y, e2z = t.c.z - t.a.z;
            const double nx = e1y * e2z - e1z * e2y;
            const double ny = e1z * e2x - e1x * e2z;
            const double nz = e1x * e2y - e1y * e2x;
            if (nx == 0.0)
                continue;
            const double xHit = t.a.x - (ny * (p.y - t.a.y) + nz * (p.z - t.a.z)) / nx;
            if (xHit > p.x)
                total -= wn;
        }
        return total;
    }

    inline bool IsSolidAt(const Model& model, double lx, double lz, float height1, float height2)
    {
        return WindingAt(model, {lx, height1, lz}) != 0 || WindingAt(model, {lx, height2, lz}) != 0;
    }

    // Builds the object-space collision model from the SDF hierarchy. Only the
    // primary LOD is used: a GEO whose 4th name character is '1' (BZ naming,
    // e.g. "bku11bda"); when no GEO carries that marker, all GEOs are used.
    // "null"/empty records are skipped. Each GEO is placed by composing its
    // local matrix up the parent chain; a mirroring chain keeps outward normals
    // by swapping the triangle winding.
    using GeoLoader = std::function<bool(const std::string& fileName, std::vector<uint8_t>& bytes)>;

    inline bool IsPrimaryLodGeo(const std::string& name)
    {
        return name.size() >= 4 && name[3] == '1';
    }

    inline bool BuildModel(const std::vector<SdfGeo>& geos, const GeoLoader& load, Model& out, std::string* error)
    {
        out = Model{};
        auto usable = [](const SdfGeo& g) { return !g.name.empty() && g.name != "null"; };
        bool anyPrimary = false;
        for (const auto& g : geos)
            if (usable(g) && IsPrimaryLodGeo(g.name))
                anyPrimary = true;
        out.lodNote = anyPrimary ? "lod1" : "all";

        auto findGeo = [&](const std::string& name) -> const SdfGeo* {
            for (const auto& g : geos)
                if (g.name == name)
                    return &g;
            return nullptr;
        };

        std::vector<uint8_t> bytes;
        std::vector<Vec3> tv;
        for (const auto& g : geos)
        {
            if (!usable(g) || (anyPrimary && !IsPrimaryLodGeo(g.name)))
                continue;
            Affine world = g.local;
            const SdfGeo* parent = findGeo(g.parent);
            for (int depth = 0; parent && depth < 64; ++depth)
            {
                world = parent->local.Compose(world);
                parent = findGeo(parent->parent);
            }
            if (!load(g.name + ".geo", bytes) || !ParseGeoTriangles(bytes.data(), bytes.size(), tv))
            {
                if (error)
                    *error = "geo " + g.name + ".geo unreadable";
                return false;
            }
            const bool mirror = world.Determinant() < 0.0;
            for (size_t i = 0; i + 2 < tv.size(); i += 3)
            {
                const Vec3 a = world.Apply(tv[i]), b = world.Apply(tv[i + 1]), c = world.Apply(tv[i + 2]);
                if (mirror)
                    out.AddTriangle(a, c, b);
                else
                    out.AddTriangle(a, b, c);
            }
            ++out.geoCount;
        }
        if (out.tris.empty())
        {
            if (error)
                *error = "no collision triangles";
            return false;
        }
        return true;
    }

    // ---------------------------------------------------------------------
    // Engine grid contract (GOG Redux 2.2.301)
    // ---------------------------------------------------------------------

    // Path grid: one byte per cell. Cell (gx, gz) covers world
    // [gx*size, (gx+1)*size) x [gz*size, (gz+1)*size); gx = floor(x / size).
    // Index = (gx - minX) + (maxX - minX) * (gz - minZ).
    struct GridDesc
    {
        float size = 5.0f;
        int minX = 0, maxX = 0, minZ = 0, maxZ = 0;

        int Width() const { return maxX - minX; }
        int Depth() const { return maxZ - minZ; }
        float Scale() const { return 1.0f / size; }
    };

    // BlockCells' placement: the yaw part of the object's world matrix.
    struct Placement
    {
        float rightX = 1, rightZ = 0, frontX = 0, frontZ = 1;
        double positX = 0, positZ = 0;
    };

    struct Quad
    {
        float x[4] = {};
        float z[4] = {};
    };

    // BlockCells' quad (0x00468B0F..): corners (min.x,min.z), (max.x,min.z),
    // (max.x,max.z), (min.x,max.z) of the local bbox; float products, double
    // position add, stored as float.
    inline Quad ComputeQuad(const Placement& p, float minX, float minZ, float maxX, float maxZ)
    {
        const float lx[4] = {minX, maxX, maxX, minX};
        const float lz[4] = {minZ, minZ, maxZ, maxZ};
        Quad q;
        for (int i = 0; i < 4; ++i)
        {
            q.x[i] = static_cast<float>(static_cast<double>(p.rightX * lx[i] + p.frontX * lz[i]) + p.positX);
            q.z[i] = static_cast<float>(static_cast<double>(p.rightZ * lx[i] + p.frontZ * lz[i]) + p.positZ);
        }
        return q;
    }

    inline void QuadBounds(const Quad& q, float& x0, float& z0, float& x1, float& z1)
    {
        x0 = std::min(std::min(q.x[0], q.x[1]), std::min(q.x[2], q.x[3]));
        z0 = std::min(std::min(q.z[0], q.z[1]), std::min(q.z[2], q.z[3]));
        x1 = std::max(std::max(q.x[0], q.x[1]), std::max(q.x[2], q.x[3]));
        z1 = std::max(std::max(q.z[0], q.z[1]), std::max(q.z[2], q.z[3]));
    }

    // UpdateCells (0x004690F0) index range: clamp(floor(v * scale) - min, 0, n-1),
    // inclusive on both ends, relative to the grid minimum.
    inline void CellRange(const GridDesc& g, float x0, float z0, float x1, float z1, int& ix0, int& iz0, int& ix1,
                          int& iz1)
    {
        if (x1 < x0)
            std::swap(x0, x1);
        if (z1 < z0)
            std::swap(z0, z1);
        const float s = g.Scale();
        auto clampi = [](int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); };
        ix0 = clampi(static_cast<int>(std::floor(x0 * s)) - g.minX, 0, g.Width() - 1);
        ix1 = clampi(static_cast<int>(std::floor(x1 * s)) - g.minX, 0, g.Width() - 1);
        iz0 = clampi(static_cast<int>(std::floor(z0 * s)) - g.minZ, 0, g.Depth() - 1);
        iz1 = clampi(static_cast<int>(std::floor(z1 * s)) - g.minZ, 0, g.Depth() - 1);
    }

    // Port of BuildingBlock (0x004693C0): does the stock box block cell
    // (gx, gz)? The cell is kept unless its centre is more than half a cell
    // outside an edge, with a rounded corner test.
    inline bool QuadCoversCell(const Quad& q, int gx, int gz, float size)
    {
        constexpr int n = 4;
        const float px = (static_cast<float>(gx) + 0.5f) * size;
        const float pz = (static_cast<float>(gz) + 0.5f) * size;
        const float h = size * 0.5f;
        int best = -1;
        float bestD = -3.4028235e+38f;
        float prevX = q.x[n - 1], prevZ = q.z[n - 1];
        for (int i = 0; i < n; ++i)
        {
            float ex = q.x[i] - prevX, ez = q.z[i] - prevZ;
            const double len2 = static_cast<double>(ex * ex + ez * ez);
            if (len2 <= 0.0)
            {
                ex = 0.0f;
                ez = 0.0f;
            }
            else
            {
                const float inv = static_cast<float>(1.0 / std::sqrt(len2));
                ex *= inv;
                ez *= inv;
            }
            const float ux = px - prevX, uz = pz - prevZ;
            const float d = (ux * ez + uz * -ex) - h;
            if (0.0f < d)
                return false;
            if (bestD < d)
            {
                best = i;
                bestD = d;
            }
            prevX = q.x[i];
            prevZ = q.z[i];
        }
        if (-h < bestD)
        {
            const int k = (best > 0 ? best : n) - 1;
            const float ax = q.x[k], az = q.z[k], bx = q.x[best], bz = q.z[best];
            if (0.0f < (px - ax) * (bx - ax) + (pz - az) * (bz - az))
            {
                if ((px - bx) * (ax - bx) + (pz - bz) * (az - bz) <= 0.0f)
                {
                    const float dx = px - bx, dz = pz - bz;
                    if (h * h < dx * dx + dz * dz)
                        return false;
                }
            }
            else
            {
                const float dx = px - ax, dz = pz - az;
                if (h * h < dx * dx + dz * dz)
                    return false;
            }
        }
        return true;
    }

    // World (x, z) to object local (x, z) through the inverse of BlockCells'
    // 2x2 yaw block. Returns false for a singular placement.
    inline bool LocalFromWorld(const Placement& p, double wx, double wz, double& lx, double& lz)
    {
        const double det = static_cast<double>(p.rightX) * p.frontZ - static_cast<double>(p.frontX) * p.rightZ;
        if (std::fabs(det) < 1e-9)
            return false;
        const double dx = wx - p.positX, dz = wz - p.positZ;
        lx = (p.frontZ * dx - p.frontX * dz) / det;
        lz = (-p.rightZ * dx + p.rightX * dz) / det;
        return true;
    }

    struct FootprintCell
    {
        int gx = 0, gz = 0; // absolute grid coordinates
        int index = 0;      // byte index into the grid
        bool solid = false;
    };

    // The cells the stock box blocks for this placement, each marked with the
    // face-mode verdict. A null model means "none" (nothing solid).
    // `solidAt` lets the runtime memoise per ODF; when empty, the model is
    // sampled directly.
    using SolidSampler = std::function<bool(double lx, double lz)>;

    inline std::vector<FootprintCell> ComputeFootprint(const GridDesc& g, const Placement& p, const Quad& q,
                                                       const SolidSampler& solidAt)
    {
        std::vector<FootprintCell> cells;
        if (g.Width() <= 0 || g.Depth() <= 0 || !(g.size > 0.0f))
            return cells;
        float x0, z0, x1, z1;
        QuadBounds(q, x0, z0, x1, z1);
        int ix0, iz0, ix1, iz1;
        CellRange(g, x0, z0, x1, z1, ix0, iz0, ix1, iz1);
        for (int iz = iz0; iz <= iz1; ++iz)
        {
            for (int ix = ix0; ix <= ix1; ++ix)
            {
                const int gx = ix + g.minX, gz = iz + g.minZ;
                if (!QuadCoversCell(q, gx, gz, g.size))
                    continue;
                FootprintCell c;
                c.gx = gx;
                c.gz = gz;
                c.index = ix + g.Width() * iz;
                if (solidAt)
                {
                    const double cx = (static_cast<float>(gx) + 0.5f) * g.size;
                    const double cz = (static_cast<float>(gz) + 0.5f) * g.size;
                    double lx = 0, lz = 0;
                    c.solid = LocalFromWorld(p, cx, cz, lx, lz) && solidAt(lx, lz);
                }
                cells.push_back(c);
            }
        }
        return cells;
    }
}
}
