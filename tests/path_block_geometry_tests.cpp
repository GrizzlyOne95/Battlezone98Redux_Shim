// Host tests for include/path_block_geometry.h (PathBlockFaces).
//
//   path_block_geometry_tests                  unit tests (pure math)
//   path_block_geometry_tests --dry <dir> <odf> [--expect-tunnel]
//       offline dry check: loads <dir>/<odf>.odf, its SDF and GEOs with the
//       runtime parser and prints the stock box and face mask in grid cells
//       for several rotations and grid alignments. --expect-tunnel asserts a
//       16 m corridor along local Z stays open at every alignment while the
//       deck either side is blocked (the bbsubtun contract check).

#include "path_block_geometry.h"
#include "test_check.h"

#include <cmath>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace BZROpenShim::PathBlock;

namespace
{
    // Axis-aligned box as 12 triangles, outward normals by vertex order.
    void AddBox(Model& m, double x0, double y0, double z0, double x1, double y1, double z1, bool inward = false)
    {
        const Vec3 v[8] = {{x0, y0, z0}, {x1, y0, z0}, {x1, y1, z0}, {x0, y1, z0},
                           {x0, y0, z1}, {x1, y0, z1}, {x1, y1, z1}, {x0, y1, z1}};
        // Quads listed counter-clockwise seen from outside.
        const int q[6][4] = {
            {0, 3, 2, 1}, // -z
            {4, 5, 6, 7}, // +z
            {0, 4, 7, 3}, // -x
            {1, 2, 6, 5}, // +x
            {0, 1, 5, 4}, // -y
            {3, 7, 6, 2}, // +y
        };
        for (const auto& f : q)
        {
            if (inward)
            {
                m.AddTriangle(v[f[0]], v[f[2]], v[f[1]]);
                m.AddTriangle(v[f[0]], v[f[3]], v[f[2]]);
            }
            else
            {
                m.AddTriangle(v[f[0]], v[f[1]], v[f[2]]);
                m.AddTriangle(v[f[0]], v[f[2]], v[f[3]]);
            }
        }
    }

    int EvenOddCrossings(const Model& m, const Vec3& p)
    {
        int crossings = 0;
        for (const Tri& t : m.tris)
        {
            if (TriangleWinding2D(t, p.y, p.z) == 0)
                continue;
            const double e1y = t.b.y - t.a.y, e1z = t.b.z - t.a.z, e1x = t.b.x - t.a.x;
            const double e2y = t.c.y - t.a.y, e2z = t.c.z - t.a.z, e2x = t.c.x - t.a.x;
            const double nx = e1y * e2z - e1z * e2y, ny = e1z * e2x - e1x * e2z, nz = e1x * e2y - e1y * e2x;
            const double xHit = t.a.x - (ny * (p.y - t.a.y) + nz * (p.z - t.a.z)) / nx;
            if (xHit > p.x)
                ++crossings;
        }
        return crossings;
    }

    void TestWindingBox()
    {
        Model m;
        AddBox(m, -1, -1, -1, 1, 1, 1);
        CHECK(WindingAt(m, {0.1, 0.2, 0.3}) == -1);
        CHECK(WindingAt(m, {0, 0, 0}) == -1); // ray through the fan diagonal of +x face: counted once
        CHECK(WindingAt(m, {-5, 0.25, 0.25}) == 0);
        CHECK(WindingAt(m, {5, 0, 0}) == 0);
        CHECK(WindingAt(m, {0, 2, 0}) == 0);
        // A sample exactly on a horizontal face plane is either in or out,
        // never double counted.
        const int top = WindingAt(m, {0, 1, 0});
        CHECK(top == 0 || top == -1);
        // Points along the y = 0, z = 0 line on the cube edge-to-edge: stable.
        for (double y = -0.95; y < 1.0; y += 0.1)
            for (double z = -0.95; z < 1.0; z += 0.1)
                OpenShimTest::Check(WindingAt(m, {0, y, z}) == -1, "interior lattice point is inside");

        Model inward;
        AddBox(inward, -1, -1, -1, 1, 1, 1, true);
        CHECK(WindingAt(inward, {0.1, 0.2, 0.3}) == 1); // nonzero either way
    }

    void TestWindingOverlap()
    {
        // Two overlapping closed solids: the overlap has winding -2, which
        // even-odd parity would call outside.
        Model m;
        AddBox(m, -2, 0, -1, 1, 2, 1);
        AddBox(m, -1, 0, -1, 2, 2, 1);
        const Vec3 p{0, 1, 0};
        CHECK(WindingAt(m, p) == -2);
        CHECK(EvenOddCrossings(m, p) % 2 == 0);
        CHECK(IsSolidAt(m, 0, 0, 1.0f, 1.5f));
        CHECK(!IsSolidAt(m, 3, 0, 1.0f, 1.5f));
    }

    void TestTunnelSolid()
    {
        // 32 x 32 deck with a 16 m corridor along Z: two side blocks and a
        // roof slab above the sample heights.
        Model m;
        AddBox(m, -16, 0, -16, -8, 10, 16);
        AddBox(m, 8, 0, -16, 16, 10, 16);
        AddBox(m, -16, 6, -16, 16, 10, 16); // overlaps both sides
        CHECK(!IsSolidAt(m, 0, 0, 1.5f, 3.0f));
        CHECK(!IsSolidAt(m, 7.9, 5, 1.5f, 3.0f));
        CHECK(IsSolidAt(m, 8.1, 5, 1.5f, 3.0f));
        CHECK(IsSolidAt(m, -12, -15, 1.5f, 3.0f));
        CHECK(IsSolidAt(m, 0, 0, 1.5f, 7.0f)); // the roof is solid at 7 m
        CHECK(WindingAt(m, {12, 8, 0}) == -2);   // side + roof overlap
    }

    void TestOdfSpec()
    {
        Spec s;
        CHECK(!ParseOdfSpec("[GameObjectClass]\nbaseName = \"bbsubtun\"\n", s));
        CHECK(s.mode == Mode::Box && s.baseName == "bbsubtun");
        CHECK(ParseOdfSpec("[GameObjectClass]\r\nPATHBLOCK = \"Faces\" // tunnels\r\npathBlockHeight=2\r\n"
                           "pathblockheight2 = 4.5f\r\n",
                           s));
        CHECK(s.mode == Mode::Faces);
        CHECK(std::fabs(s.height1 - 2.0f) < 1e-6f && std::fabs(s.height2 - 4.5f) < 1e-6f);
        CHECK(ParseOdfSpec("[gameobjectclass]\npathBlock = none ; nothing\n", s) && s.mode == Mode::None);
        CHECK(ParseOdfSpec("[GameObjectClass]\npathBlock = \"tunnel\"\n", s) && s.mode == Mode::Box);
        // Keys outside [GameObjectClass] are ignored.
        CHECK(!ParseOdfSpec("[BuildingClass]\npathBlock = \"faces\"\n", s) && s.mode == Mode::Box);
        CHECK(ParseOdfSpec("[GameObjectClass]\npathBlock = \"faces\"\npathBlockHeight = junk\n", s));
        CHECK(std::fabs(s.height1 - 1.5f) < 1e-6f && std::fabs(s.height2 - 3.0f) < 1e-6f);
    }

    void TestQuadAndMapping()
    {
        GridDesc g;
        g.size = 5.0f;
        g.minX = -100;
        g.maxX = 100;
        g.minZ = -100;
        g.maxZ = 100;
        Placement p; // identity at origin
        const Quad q = ComputeQuad(p, -10, -10, 10, 10);
        // Interior and half-cell-overlap cells are covered; the corner disc
        // rounds off cells that only touch the corner diagonally.
        CHECK(QuadCoversCell(q, 0, 0, 5.0f));
        CHECK(QuadCoversCell(q, -2, -2, 5.0f));
        CHECK(QuadCoversCell(q, 1, 1, 5.0f));
        CHECK(QuadCoversCell(q, 2, 0, 5.0f));    // centre 12.5: 2.5 outside = half a cell, kept
        CHECK(!QuadCoversCell(q, 3, 0, 5.0f));   // centre 17.5
        CHECK(!QuadCoversCell(q, 2, 2, 5.0f));   // corner cell outside the rounding disc
        int ix0, iz0, ix1, iz1;
        CellRange(g, -10, -10, 10, 10, ix0, iz0, ix1, iz1);
        CHECK(ix0 == 98 && ix1 == 102 && iz0 == 98 && iz1 == 102);

        // Rotated placement round-trips world -> local.
        Placement r;
        const float a = 0.6f;
        r.rightX = std::cos(a);
        r.rightZ = -std::sin(a);
        r.frontX = std::sin(a);
        r.frontZ = std::cos(a);
        r.positX = 1234.5;
        r.positZ = -77.25;
        const double lx = 3.0, lz = -7.0;
        const double wx = r.rightX * lx + r.frontX * lz + r.positX, wz = r.rightZ * lx + r.frontZ * lz + r.positZ;
        double bx = 0, bz = 0;
        CHECK(LocalFromWorld(r, wx, wz, bx, bz));
        CHECK(std::fabs(bx - lx) < 1e-4 && std::fabs(bz - lz) < 1e-4);
    }

    void PutF(std::vector<uint8_t>& b, float f)
    {
        uint8_t t[4];
        std::memcpy(t, &f, 4);
        b.insert(b.end(), t, t + 4);
    }
    void PutI(std::vector<uint8_t>& b, int32_t v)
    {
        uint8_t t[4];
        std::memcpy(t, &v, 4);
        b.insert(b.end(), t, t + 4);
    }
    void PutName(std::vector<uint8_t>& b, const char* s, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
            b.push_back(i < std::strlen(s) ? static_cast<uint8_t>(s[i]) : 0);
    }

    void TestFileParsers()
    {
        // One square face (fanned into two triangles).
        std::vector<uint8_t> geo;
        PutName(geo, "OEG.", 4);
        PutI(geo, 69);
        PutName(geo, "tst11a", 16);
        PutI(geo, 4);
        PutI(geo, 1);
        PutI(geo, 0);
        const float vx[4][3] = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}};
        for (auto& v : vx)
            for (float f : v)
                PutF(geo, f);
        for (int i = 0; i < 12; ++i)
            PutF(geo, 0.0f);
        PutI(geo, 0);
        PutI(geo, 4);
        geo.insert(geo.end(), {1, 2, 3});
        for (int i = 0; i < 5; ++i)
            PutF(geo, 0.0f);
        geo.insert(geo.end(), {4, 1, 0});
        PutName(geo, "tex", 13);
        PutI(geo, 0);
        PutI(geo, 0);
        for (int k = 0; k < 4; ++k)
        {
            PutI(geo, k);
            PutI(geo, k);
            PutF(geo, 0);
            PutF(geo, 0);
        }
        std::vector<Vec3> tv;
        CHECK(ParseGeoTriangles(geo.data(), geo.size(), tv));
        CHECK(tv.size() == 6);
        CHECK(!ParseGeoTriangles(geo.data(), geo.size() - 4, tv));

        std::vector<uint8_t> sdf;
        PutName(sdf, "BWD2", 4);
        PutI(sdf, 8);
        PutName(sdf, "REV", 4);
        PutI(sdf, 12);
        PutI(sdf, 8);
        PutName(sdf, "SGEO", 4);
        PutI(sdf, 12 + 2 * 120);
        PutI(sdf, 2);
        auto rec = [&](const char* name, const char* parent, float px) {
            PutName(sdf, name, 8);
            const float mtx[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, px, 0, 0};
            for (float f : mtx)
                PutF(sdf, f);
            PutName(sdf, parent, 8);
            for (int i = 0; i < 7; ++i)
                PutF(sdf, 0);
            for (int i = 0; i < 3; ++i)
                PutI(sdf, 0);
            for (int i = 0; i < 4; ++i)
                PutF(sdf, 0);
        };
        rec("TST11A", "WORLD", 10.0f);
        rec("tst11b", "tst11a", 5.0f);
        std::vector<SdfGeo> geos;
        CHECK(ParseSdfGeos(sdf.data(), sdf.size(), geos));
        CHECK(geos.size() == 2 && geos[0].name == "tst11a" && geos[1].parent == "tst11a");
        Model m;
        std::string err;
        const bool built = BuildModel(
            geos, [&](const std::string&, std::vector<uint8_t>& out) {
                out = geo;
                return true;
            },
            m, &err);
        CHECK(built);
        CHECK(m.geoCount == 2 && m.tris.size() == 4);
        CHECK(std::fabs(m.maxX - 16.0) < 1e-6); // child placed at 10 + 5, plus the 1 m face
    }

    // ------------------------------------------------------------------
    // Offline dry check against real files
    // ------------------------------------------------------------------

    bool ReadFile(const std::string& path, std::vector<uint8_t>& out)
    {
        std::ifstream f(path, std::ios::binary);
        if (!f)
            return false;
        out.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
        return !out.empty();
    }

    int DryCheck(const std::string& dir, const std::string& odf, bool expectTunnel)
    {
        std::vector<uint8_t> bytes;
        if (!ReadFile(dir + "/" + odf + ".odf", bytes))
        {
            std::printf("cannot read %s/%s.odf\n", dir.c_str(), odf.c_str());
            return 1;
        }
        Spec spec;
        const bool flagged = ParseOdfSpec(std::string(bytes.begin(), bytes.end()), spec);
        std::printf("odf %s: pathBlock %s (%s), heights %.2f / %.2f, baseName '%s'\n", odf.c_str(),
                    ModeName(spec.mode), flagged ? "set" : "absent; dry check forces faces", spec.height1,
                    spec.height2, spec.baseName.c_str());
        const std::string base = spec.baseName.empty() ? odf : spec.baseName;
        std::vector<SdfGeo> geos;
        if (!ReadFile(dir + "/" + base + ".sdf", bytes) || !ParseSdfGeos(bytes.data(), bytes.size(), geos))
        {
            std::printf("cannot parse %s.sdf\n", base.c_str());
            return 1;
        }
        Model model;
        std::string err;
        if (!BuildModel(
                geos, [&](const std::string& name, std::vector<uint8_t>& out) { return ReadFile(dir + "/" + name, out); },
                model, &err))
        {
            std::printf("model build failed: %s\n", err.c_str());
            return 1;
        }
        std::printf("model: %d geos (%s), %zu triangles, bbox x[%.2f %.2f] y[%.2f %.2f] z[%.2f %.2f]\n",
                    model.geoCount, model.lodNote.c_str(), model.tris.size(), model.minX, model.maxX, model.minY,
                    model.maxY, model.minZ, model.maxZ);

        // Local cross-section at the sample heights, 1 m resolution.
        std::printf("\nlocal cross-section (1 m, x right, z up; '#' solid at either height):\n");
        for (int z = static_cast<int>(std::ceil(model.maxZ)) - 1; z >= static_cast<int>(std::floor(model.minZ)); --z)
        {
            std::string row;
            for (int x = static_cast<int>(std::floor(model.minX)); x < static_cast<int>(std::ceil(model.maxX)); ++x)
                row.push_back(IsSolidAt(model, x + 0.5, z + 0.5, spec.height1, spec.height2) ? '#' : '.');
            std::printf("  %4d %s\n", z, row.c_str());
        }

        GridDesc g;
        g.size = 5.0f; // Terrain grid size in GOG Redux (0x0077E990 stores 5.0 to 0x02CC50E0)
        g.minX = -200;
        g.maxX = 200;
        g.minZ = -200;
        g.maxZ = 200;
        const SolidSampler solid = [&](double lx, double lz) {
            return IsSolidAt(model, lx, lz, spec.height1, spec.height2);
        };
        const double offsets[] = {0.0, 1.25, 2.5, 3.75};
        const double angles[] = {0.0, 30.0, 45.0, 90.0};
        int failures = 0;
        for (double ang : angles)
        {
            for (double off : offsets)
            {
                const double rad = ang * 3.14159265358979323846 / 180.0;
                Placement p;
                p.rightX = static_cast<float>(std::cos(rad));
                p.rightZ = static_cast<float>(-std::sin(rad));
                p.frontX = static_cast<float>(std::sin(rad));
                p.frontZ = static_cast<float>(std::cos(rad));
                p.positX = 500.0 + off;
                p.positZ = 500.0 + off * 0.6;
                const Quad q = ComputeQuad(p, static_cast<float>(model.minX), static_cast<float>(model.minZ),
                                           static_cast<float>(model.maxX), static_cast<float>(model.maxZ));
                const auto cells = ComputeFootprint(g, p, q, solid);
                int blocked = 0;
                int gx0 = 1 << 30, gx1 = -(1 << 30), gz0 = 1 << 30, gz1 = -(1 << 30);
                for (const auto& c : cells)
                {
                    blocked += c.solid ? 1 : 0;
                    gx0 = std::min(gx0, c.gx);
                    gx1 = std::max(gx1, c.gx);
                    gz0 = std::min(gz0, c.gz);
                    gz1 = std::max(gz1, c.gz);
                }
                std::printf("\nrot %.0f deg, origin (%.2f, %.2f): box %zu cells, faces block %d "
                            "('#' blocked, 'o' box cell left open, '.' outside box)\n",
                            ang, p.positX, p.positZ, cells.size(), blocked);
                for (int gz = gz1; gz >= gz0; --gz)
                {
                    std::string row;
                    for (int gx = gx0; gx <= gx1; ++gx)
                    {
                        char ch = '.';
                        for (const auto& c : cells)
                            if (c.gx == gx && c.gz == gz)
                                ch = c.solid ? '#' : 'o';
                        row.push_back(ch);
                    }
                    std::printf("    %s\n", row.c_str());
                }

                if (expectTunnel)
                {
                    // Corridor: cells whose centre lies at |local x| < 8 with
                    // |local z| < 14 (inside the deck). Require at least one
                    // open cell per 5 m of corridor length along local Z and
                    // a blocked cell on each side at mid-length.
                    int openInCorridor = 0, solidInCorridor = 0, blockedLeft = 0, blockedRight = 0;
                    for (const auto& c : cells)
                    {
                        double lx = 0, lz = 0;
                        LocalFromWorld(p, (c.gx + 0.5) * g.size, (c.gz + 0.5) * g.size, lx, lz);
                        if (std::fabs(lx) < 7.5 && std::fabs(lz) < 14.0)
                        {
                            if (c.solid)
                                ++solidInCorridor;
                            else
                                ++openInCorridor;
                        }
                        if (c.solid && lx < -9.0)
                            ++blockedLeft;
                        if (c.solid && lx > 9.0)
                            ++blockedRight;
                    }
                    std::printf("    corridor cells open %d, solid %d; deck blocked left %d right %d\n",
                                openInCorridor, solidInCorridor, blockedLeft, blockedRight);
                    if (solidInCorridor != 0 || openInCorridor < 4 || blockedLeft == 0 || blockedRight == 0)
                    {
                        ++failures;
                        std::printf("    FAIL: corridor not open or deck not blocked\n");
                    }
                }
            }
        }
        return failures == 0 ? 0 : 1;
    }
}

int main(int argc, char** argv)
{
    if (argc >= 4 && std::string(argv[1]) == "--dry")
        return DryCheck(argv[2], argv[3], argc >= 5 && std::string(argv[4]) == "--expect-tunnel");

    TestWindingBox();
    TestWindingOverlap();
    TestTunnelSolid();
    TestOdfSpec();
    TestQuadAndMapping();
    TestFileParsers();
    return OpenShimTest::ExitCode();
}
