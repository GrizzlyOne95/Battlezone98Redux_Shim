#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace BZROpenShim::TerrainSemantic
{
    constexpr std::size_t kVertexCount = 9409;

    struct Float2
    {
        float x;
        float y;
    };

    struct AtlasRect
    {
        float u;
        float v;
        float w;
        float h;
    };

    struct Cell
    {
        int cellX = 0;
        int cellZ = 0;
        int terrainX = 0;
        int terrainZ = 0;
        std::uint16_t word = 0;
        std::uint8_t tileIndex = 0;
        std::uint8_t orientation = 0;
        std::uint8_t typeA = 0;
        std::uint8_t typeB = 0;
        std::uint8_t mix = 0;
        std::uint8_t variant = 0;
        AtlasRect rect = {};
    };

#pragma pack(push, 1)
    // Phase 3A stream: TEXCOORD2=float2, TEXCOORD3=ubyte4, and
    // TEXCOORD4=float4. The per-vertex AtlasRect is an intentionally simple
    // proof transport; tileIndex remains explicit and can become the lookup
    // key when Phase 3B replaces this with an indexed table/texture array.
    // Stock packed atlas bytes remain in the cloned mesh solely as an
    // independent validation oracle and for untouched auxiliary techniques.
    struct GpuVertex
    {
        float localU;
        float localV;
        std::uint8_t tileIndex;
        std::uint8_t orientation;
        std::uint8_t typeA;
        std::uint8_t typeB;
        float atlasU;
        float atlasV;
        float atlasW;
        float atlasH;
    };
#pragma pack(pop)
    static_assert(sizeof(GpuVertex) == 28, "Phase 3A semantic vertex ABI changed");

    struct Vertex
    {
        GpuVertex gpu = {};
        std::uint8_t mix = 0;
        std::uint8_t variant = 0;
        std::uint8_t qx = 0;
        std::uint8_t qz = 0;
        std::int8_t cellX = 0;
        std::int8_t cellZ = 0;
        AtlasRect rect = {};
        Float2 atlasUv = {};
        std::uint8_t packedU = 0;
        std::uint8_t packedV = 0;
    };

    using CellProvider = bool(*)(void* context, int cellX, int cellZ, Cell& cell);

    struct Mismatch
    {
        std::size_t vertex = 0;
        Vertex semantic = {};
        std::uint8_t stockU = 0;
        std::uint8_t stockV = 0;
    };

    struct ValidationResult
    {
        std::size_t checked = 0;
        std::size_t exactMatches = 0;
        std::size_t mismatches = 0;
        float maximumUvErrorBeforeQuantization = 0.0f;
        std::vector<Mismatch> examples;
    };

    Float2 ApplyTerrainOrientation(Float2 localUv, std::uint8_t orientation);

    Float2 ReconstructAtlasUv(
        const AtlasRect& rect,
        std::uint8_t orientation,
        int qx,
        int qz,
        std::uint8_t* packedU = nullptr,
        std::uint8_t* packedV = nullptr);

    bool BuildVertices(
        CellProvider provider,
        void* context,
        std::vector<Vertex>& vertices);

    ValidationResult ValidatePackedUv(
        const std::vector<Vertex>& vertices,
        const std::uint8_t* stockStream,
        std::size_t stockStride,
        std::size_t mismatchExampleLimit);
}
