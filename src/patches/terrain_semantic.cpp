#include "terrain_semantic.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <xmmintrin.h>

namespace BZROpenShim::TerrainSemantic
{
    namespace
    {
        struct OrientationCorners
        {
            Float2 bottomLeft;
            Float2 topLeft;
            Float2 bottomRight;
        };

        constexpr std::array<OrientationCorners, 16> kOrientationCorners = {{
            {{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}},
            {{1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}},
            {{1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}},
            {{0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}},
            {{1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}},
            // The released table's final four records are not a byte-for-byte
            // copy of records 4..7. Their order is 5,6,7,4.
            {{1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}},
            {{0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}},
        }};

        float Mul(float left, float right)
        {
            return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(left), _mm_set_ss(right)));
        }

        float Add(float left, float right)
        {
            return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(left), _mm_set_ss(right)));
        }

        float Sub(float left, float right)
        {
            return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(left), _mm_set_ss(right)));
        }

        float Div(float left, float right)
        {
            return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(left), _mm_set_ss(right)));
        }

        std::uint8_t PackUv(float value)
        {
            // Released FUN_00779C20 uses mulss followed by cvttss2si, then
            // stores AL. Keep every operation in scalar single precision.
            return static_cast<std::uint8_t>(
                _mm_cvtt_ss2si(_mm_mul_ss(_mm_set_ss(value), _mm_set_ss(160.0f))));
        }
    }

    Float2 ApplyTerrainOrientation(Float2 localUv, std::uint8_t orientation)
    {
        const OrientationCorners& corners =
            kOrientationCorners[orientation & 0xFu];
        return {
            corners.bottomLeft.x +
                localUv.y * (corners.topLeft.x - corners.bottomLeft.x) +
                localUv.x * (corners.bottomRight.x - corners.bottomLeft.x),
            corners.bottomLeft.y +
                localUv.y * (corners.topLeft.y - corners.bottomLeft.y) +
                localUv.x * (corners.bottomRight.y - corners.bottomLeft.y),
        };
    }

    Float2 ReconstructAtlasUv(
        const AtlasRect& rect,
        std::uint8_t orientation,
        int qx,
        int qz,
        std::uint8_t* packedU,
        std::uint8_t* packedV)
    {
        const OrientationCorners& corners =
            kOrientationCorners[orientation & 0xFu];

        const float originU = Add(Mul(corners.bottomLeft.x, rect.w), rect.u);
        const float originV = Add(Mul(corners.bottomLeft.y, rect.h), rect.v);
        const float topU = Add(Mul(corners.topLeft.x, rect.w), rect.u);
        const float topV = Add(Mul(corners.topLeft.y, rect.h), rect.v);
        const float rightU = Add(Mul(corners.bottomRight.x, rect.w), rect.u);
        const float rightV = Add(Mul(corners.bottomRight.y, rect.h), rect.v);
        const float stepZU = Div(Sub(topU, originU), 5.0f);
        const float stepZV = Div(Sub(topV, originV), 5.0f);
        const float stepXU = Div(Sub(rightU, originU), 5.0f);
        const float stepXV = Div(Sub(rightV, originV), 5.0f);

        // Preserve 0077A128..0077A176 exactly: qz * step, add origin,
        // qx * step, then add that second term.
        const float u = Add(Add(Mul(static_cast<float>(qz), stepZU), originU),
            Mul(static_cast<float>(qx), stepXU));
        const float v = Add(Add(Mul(static_cast<float>(qz), stepZV), originV),
            Mul(static_cast<float>(qx), stepXV));
        if (packedU)
            *packedU = PackUv(u);
        if (packedV)
            *packedV = PackUv(v);
        return {u, v};
    }

    bool BuildVertices(
        CellProvider provider,
        void* context,
        std::vector<Vertex>& vertices)
    {
        vertices.clear();
        if (!provider)
            return false;

        std::array<Cell, 17 * 17> cells = {};
        for (int z = 0; z <= 16; ++z)
        {
            for (int x = 0; x <= 16; ++x)
            {
                Cell& cell = cells[static_cast<std::size_t>(z * 17 + x)];
                if (!provider(context, x, z, cell))
                    return false;
            }
        }

        vertices.reserve(kVertexCount);
        const auto emitTile = [&](int cellX, int cellZ,
                                  int qxBegin, int qxEnd,
                                  int qzBegin, int qzEnd)
        {
            const Cell& cell =
                cells[static_cast<std::size_t>(cellZ * 17 + cellX)];
            for (int qz = qzBegin; qz < qzEnd; ++qz)
            {
                for (int qx = qxBegin; qx < qxEnd; ++qx)
                {
                    Vertex vertex;
                    vertex.gpu.localU = static_cast<float>(qx) / 5.0f;
                    vertex.gpu.localV = static_cast<float>(qz) / 5.0f;
                    vertex.gpu.tileIndex = cell.tileIndex;
                    vertex.gpu.orientation = cell.orientation & 0xFu;
                    vertex.gpu.typeA = cell.typeA;
                    vertex.gpu.typeB = cell.typeB;
                    vertex.gpu.atlasU = cell.rect.u;
                    vertex.gpu.atlasV = cell.rect.v;
                    vertex.gpu.atlasW = cell.rect.w;
                    vertex.gpu.atlasH = cell.rect.h;
                    vertex.mix = cell.mix;
                    vertex.variant = cell.variant;
                    vertex.qx = static_cast<std::uint8_t>(qx);
                    vertex.qz = static_cast<std::uint8_t>(qz);
                    vertex.cellX = static_cast<std::int8_t>(cellX);
                    vertex.cellZ = static_cast<std::int8_t>(cellZ);
                    vertex.rect = cell.rect;
                    vertex.atlasUv = ReconstructAtlasUv(
                        cell.rect, cell.orientation, qx, qz,
                        &vertex.packedU, &vertex.packedV);
                    vertices.push_back(vertex);
                }
            }
        };

        // Exact call order and clipped ranges from released FUN_007789A0 /
        // FUN_007794F0. Tile boundaries intentionally remain duplicated.
        emitTile(0, 0, 2, 6, 2, 6);
        for (int x = 1; x < 16; ++x)
            emitTile(x, 0, 0, 6, 2, 6);
        emitTile(16, 0, 0, 3, 2, 6);

        for (int z = 1; z < 16; ++z)
            emitTile(0, z, 2, 6, 0, 6);
        for (int x = 1; x < 16; ++x)
            for (int z = 1; z < 16; ++z)
                emitTile(x, z, 0, 6, 0, 6);
        emitTile(0, 16, 2, 6, 0, 3);

        for (int z = 1; z < 16; ++z)
            emitTile(16, z, 0, 3, 0, 6);
        for (int x = 1; x < 16; ++x)
            emitTile(x, 16, 0, 6, 0, 3);
        emitTile(16, 16, 0, 3, 0, 3);

        return vertices.size() == kVertexCount;
    }

    ValidationResult ValidatePackedUv(
        const std::vector<Vertex>& vertices,
        const std::uint8_t* stockStream,
        std::size_t stockStride,
        std::size_t mismatchExampleLimit)
    {
        ValidationResult result;
        if (!stockStream || stockStride < 2)
            return result;

        result.checked = vertices.size();
        result.examples.reserve(std::min(mismatchExampleLimit, vertices.size()));
        for (std::size_t i = 0; i < vertices.size(); ++i)
        {
            const Vertex& semantic = vertices[i];
            const std::uint8_t* stock = stockStream + i * stockStride;
            const bool match = semantic.packedU == stock[0] &&
                semantic.packedV == stock[1];
            if (match)
            {
                ++result.exactMatches;
            }
            else
            {
                ++result.mismatches;
                if (result.examples.size() < mismatchExampleLimit)
                {
                    result.examples.push_back({i, semantic, stock[0], stock[1]});
                }
            }

            const float stockQuantizedU = static_cast<float>(stock[0]) / 160.0f;
            const float stockQuantizedV = static_cast<float>(stock[1]) / 160.0f;
            result.maximumUvErrorBeforeQuantization = std::max(
                result.maximumUvErrorBeforeQuantization,
                std::max(std::fabs(semantic.atlasUv.x - stockQuantizedU),
                         std::fabs(semantic.atlasUv.y - stockQuantizedV)));
        }
        return result;
    }
}
