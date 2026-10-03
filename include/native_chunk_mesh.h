#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace BZROpenShim::NativeChunks
{
// Ogre's serialized assets, not live Mesh/SubMesh layouts. Invalid, unsupported
// or incomplete geometry fails closed. Output retains original vertex streams
// (normals, tangents, UV sets and colours) and material names, without
// skinning.
struct Piece
{
    std::string name;
    std::vector<uint8_t> mesh;
    uint32_t triangles = 0;
};
bool Extract(const std::vector<uint8_t> &mesh, const std::vector<uint8_t> &skeleton, std::vector<Piece> &pieces,
             std::string &error);
std::string SkeletonName(const std::vector<uint8_t> &mesh);
// The stock chunklet shapes already embedded for batching, emitted on demand
// with the game's scrap material. No skeleton, texture or payload pack needed.
Piece StockFallbackMesh(unsigned kind);
unsigned StockFallbackKind(std::string_view seed);
// Exact generated resource names only; vehicle pieces and similarly named
// custom assets must never become generic debris.
unsigned StockFallbackBatchKind(std::string_view resource);
} // namespace BZROpenShim::NativeChunks
