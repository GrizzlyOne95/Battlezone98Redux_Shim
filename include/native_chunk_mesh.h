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
//
// The engine's physical fragment carries the source node's full world matrix
// (ChunkEffect::CreateChunk copies obj_rel_parent_matrix), so vertices are
// stored in the bone's own frame: translation AND bind rotation removed.
// They are then centred on the piece's bounds; `center` is that centre in
// the bone frame (Ogre render axes), which the fragment origin must move to
// so the piece spins about its own geometry rather than the bone pivot.
struct Piece
{
    std::string name;
    std::vector<uint8_t> mesh;
    uint32_t triangles = 0;
    float center[3] = {0, 0, 0};
};
bool Extract(const std::vector<uint8_t> &mesh, const std::vector<uint8_t> &skeleton, std::vector<Piece> &pieces,
             std::string &error);
std::string SkeletonName(const std::vector<uint8_t> &mesh);
// World-space (sim axes) displacement that moves a fragment's origin from its
// bone pivot onto the piece centre. right/up/front are the fragment's legacy
// basis columns; sim space is Ogre's with Z mirrored. Fails on a degenerate
// basis or non-finite input.
bool FragmentOriginShift(const float right[3], const float up[3], const float front[3], const float center[3],
                         double out[3]);
// The stock chunklet shapes already embedded for batching, emitted on demand
// with the game's scrap material. No skeleton, texture or payload pack needed.
Piece StockFallbackMesh(unsigned kind);
unsigned StockFallbackKind(std::string_view seed);
// Exact generated resource names only; vehicle pieces and similarly named
// custom assets must never become generic debris.
unsigned StockFallbackBatchKind(std::string_view resource);
} // namespace BZROpenShim::NativeChunks
