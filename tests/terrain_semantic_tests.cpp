// Characterization tests for src/patches/terrain_semantic.cpp: the terrain
// orientation table, atlas-UV reconstruction, the clipped vertex emission
// order and the packed-UV validation. Pure math; no engine, no Ogre.

#include "terrain_semantic.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::TerrainSemantic;

    bool Near(float a, float b, float epsilon = 1e-6f)
    {
        return std::fabs(a - b) <= epsilon;
    }

    bool Same(Float2 a, Float2 b)
    {
        return Near(a.x, b.x) && Near(a.y, b.y);
    }

    void TestOrientationZeroCorners()
    {
        // Orientation 0: local (0,0) is the bottom-left corner (0,1), +x runs
        // to the bottom-right (1,1), +y to the top-left (0,0).
        CHECK(Same(ApplyTerrainOrientation({0.0f, 0.0f}, 0), {0.0f, 1.0f}));
        CHECK(Same(ApplyTerrainOrientation({1.0f, 0.0f}, 0), {1.0f, 1.0f}));
        CHECK(Same(ApplyTerrainOrientation({0.0f, 1.0f}, 0), {0.0f, 0.0f}));
        CHECK(Same(ApplyTerrainOrientation({0.5f, 0.5f}, 0), {0.5f, 0.5f}));
    }

    void TestOrientationTableQuirks()
    {
        const Float2 points[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {0.2f, 0.8f} };
        for (const Float2& p : points)
        {
            // Only the low four bits select a record.
            CHECK(Same(ApplyTerrainOrientation(p, 16), ApplyTerrainOrientation(p, 0)));
            CHECK(Same(ApplyTerrainOrientation(p, 0x27), ApplyTerrainOrientation(p, 7)));
            // Records 8..11 repeat 0..3.
            for (std::uint8_t o = 0; o < 4; ++o)
                CHECK(Same(ApplyTerrainOrientation(p, static_cast<std::uint8_t>(o + 8)),
                           ApplyTerrainOrientation(p, o)));
            // The released table's last four records are 5,6,7,4, not 4..7.
            CHECK(Same(ApplyTerrainOrientation(p, 12), ApplyTerrainOrientation(p, 5)));
            CHECK(Same(ApplyTerrainOrientation(p, 13), ApplyTerrainOrientation(p, 6)));
            CHECK(Same(ApplyTerrainOrientation(p, 14), ApplyTerrainOrientation(p, 7)));
            CHECK(Same(ApplyTerrainOrientation(p, 15), ApplyTerrainOrientation(p, 4)));
        }
    }

    void TestReconstructMatchesOrientationMapping()
    {
        const AtlasRect rect = { 0.125f, 0.25f, 0.0625f, 0.0625f };
        for (std::uint8_t orientation = 0; orientation < 16; ++orientation)
        {
            for (int qz = 0; qz <= 5; ++qz)
            {
                for (int qx = 0; qx <= 5; ++qx)
                {
                    std::uint8_t packedU = 0;
                    std::uint8_t packedV = 0;
                    const Float2 uv = ReconstructAtlasUv(rect, orientation, qx, qz, &packedU, &packedV);
                    const Float2 local = ApplyTerrainOrientation(
                        { static_cast<float>(qx) / 5.0f, static_cast<float>(qz) / 5.0f }, orientation);
                    CHECK(Near(uv.x, rect.u + local.x * rect.w, 1e-5f));
                    CHECK(Near(uv.y, rect.v + local.y * rect.h, 1e-5f));
                    // Packing truncates value * 160, like the released code.
                    CHECK(packedU == static_cast<std::uint8_t>(static_cast<int>(uv.x * 160.0f)));
                    CHECK(packedV == static_cast<std::uint8_t>(static_cast<int>(uv.y * 160.0f)));
                }
            }
        }
        // The packed outputs are optional.
        const Float2 uv = ReconstructAtlasUv(rect, 3, 2, 4);
        CHECK(uv.x > 0.0f && uv.y > 0.0f);
    }

    bool UniformCells(void* context, int cellX, int cellZ, Cell& cell)
    {
        int* calls = static_cast<int*>(context);
        ++*calls;
        cell.cellX = cellX;
        cell.cellZ = cellZ;
        cell.tileIndex = static_cast<std::uint8_t>(cellZ * 17 + cellX);
        cell.orientation = static_cast<std::uint8_t>((cellX + cellZ) & 0xF);
        cell.typeA = 1;
        cell.typeB = 2;
        cell.mix = 3;
        cell.variant = 4;
        cell.rect = { 0.0625f * static_cast<float>(cellX % 8), 0.0625f * static_cast<float>(cellZ % 8),
                      0.0625f, 0.0625f };
        return true;
    }

    bool FailingCells(void*, int cellX, int cellZ, Cell&)
    {
        return !(cellX == 4 && cellZ == 9);
    }

    int CountCell(const std::vector<Vertex>& vertices, int cellX, int cellZ)
    {
        int count = 0;
        for (const Vertex& v : vertices)
        {
            if (v.cellX == cellX && v.cellZ == cellZ)
                ++count;
        }
        return count;
    }

    void TestBuildVertices()
    {
        int calls = 0;
        std::vector<Vertex> vertices;
        CHECK(BuildVertices(&UniformCells, &calls, vertices));
        CHECK(calls == 17 * 17);
        CHECK(vertices.size() == kVertexCount);

        // Emission order and clipping: the first tile is cell (0,0) from
        // (qx,qz) = (2,2); interior cells emit 6x6, edge and corner tiles are
        // clipped, and the last vertex is cell (16,16) at (2,2).
        CHECK(!vertices.empty() && vertices.front().cellX == 0 && vertices.front().cellZ == 0);
        CHECK(!vertices.empty() && vertices.front().qx == 2 && vertices.front().qz == 2);
        CHECK(!vertices.empty() && vertices.back().cellX == 16 && vertices.back().cellZ == 16);
        CHECK(!vertices.empty() && vertices.back().qx == 2 && vertices.back().qz == 2);
        CHECK(CountCell(vertices, 0, 0) == 16);
        CHECK(CountCell(vertices, 5, 0) == 24);
        CHECK(CountCell(vertices, 16, 0) == 12);
        CHECK(CountCell(vertices, 0, 5) == 24);
        CHECK(CountCell(vertices, 5, 5) == 36);
        CHECK(CountCell(vertices, 16, 16) == 9);

        // Per-vertex fields come from the cell.
        bool fieldsOk = true;
        for (const Vertex& v : vertices)
        {
            fieldsOk = fieldsOk &&
                v.gpu.tileIndex == static_cast<std::uint8_t>(v.cellZ * 17 + v.cellX) &&
                v.gpu.orientation == ((v.cellX + v.cellZ) & 0xF) &&
                v.gpu.typeA == 1 && v.gpu.typeB == 2 && v.mix == 3 && v.variant == 4 &&
                Near(v.gpu.localU, static_cast<float>(v.qx) / 5.0f) &&
                Near(v.gpu.localV, static_cast<float>(v.qz) / 5.0f);
        }
        CHECK(fieldsOk);
    }

    void TestBuildVerticesFailures()
    {
        std::vector<Vertex> vertices(3);
        CHECK(!BuildVertices(nullptr, nullptr, vertices));
        CHECK(vertices.empty());
        CHECK(!BuildVertices(&FailingCells, nullptr, vertices));
        CHECK(vertices.empty());
    }

    void TestValidatePackedUv()
    {
        int calls = 0;
        std::vector<Vertex> vertices;
        CHECK(BuildVertices(&UniformCells, &calls, vertices));

        // A stock stream carrying the same packed bytes, stride 4.
        std::vector<std::uint8_t> stock(vertices.size() * 4, 0);
        for (std::size_t i = 0; i < vertices.size(); ++i)
        {
            stock[i * 4] = vertices[i].packedU;
            stock[i * 4 + 1] = vertices[i].packedV;
        }
        ValidationResult result = ValidatePackedUv(vertices, stock.data(), 4, 8);
        CHECK(result.checked == kVertexCount);
        CHECK(result.exactMatches == kVertexCount);
        CHECK(result.mismatches == 0);
        CHECK(result.examples.empty());
        CHECK(result.maximumUvErrorBeforeQuantization < 1.0f / 160.0f + 1e-6f);

        stock[100 * 4] = static_cast<std::uint8_t>(stock[100 * 4] + 1);
        stock[200 * 4 + 1] = static_cast<std::uint8_t>(stock[200 * 4 + 1] + 1);
        result = ValidatePackedUv(vertices, stock.data(), 4, 1);
        CHECK(result.mismatches == 2);
        CHECK(result.exactMatches == kVertexCount - 2);
        CHECK(result.examples.size() == 1);
        CHECK(!result.examples.empty() && result.examples[0].vertex == 100);

        const ValidationResult none = ValidatePackedUv(vertices, nullptr, 4, 8);
        CHECK(none.checked == 0);
        const ValidationResult narrow = ValidatePackedUv(vertices, stock.data(), 1, 8);
        CHECK(narrow.checked == 0);
    }
}

int main()
{
    TestOrientationZeroCorners();
    TestOrientationTableQuirks();
    TestReconstructMatchesOrientationMapping();
    TestBuildVertices();
    TestBuildVerticesFailures();
    TestValidatePackedUv();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("terrain_semantic_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
