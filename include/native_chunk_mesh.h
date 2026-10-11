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
// Skinned gibs (OpenShim SkinnedGibs): the runtime twin of
// scripts/export_gib_payloads.py. Every face goes to its dominant bone
// (summed weights over its three corners; unweighted faces are skipped);
// bones owning fewer than minFaceFraction of all faces, or matching
// dropPattern, roll up into their parent deepest first unless they match
// keepPattern or are a root; submeshes whose material matches
// weaponMaterialPattern become one uncapped "weapon" piece driven by their
// dominant bone; and each cut (an edge shared by two body pieces in the
// position-welded topology) is closed by a torn-flesh cap: concentric rings
// that follow the rim's shape (a thin skin edge, a pale fat band, muscle to a
// slightly bulged centre; limb cuts end the muscle in a bone ring around a
// marrow core), with smooth normals and planar UVs, one extra submesh per
// zone. Everything is deterministic: the small ragged offsets hash the welded
// positions. No vertex colours (see CapVertex in native_chunk_mesh.cpp). Patterns are ECMAScript, case-insensitive, searched; empty
// matches nothing. Pieces are written like Extract's: in the driving bone's
// bind frame, centred on their bounds, with `piece.center` that centre in the
// bone frame, so world = entityNode * boneDerived * translate(center).
struct GibOptions
{
    float minFaceFraction = 0.025f;
    std::string keepPattern = "head$";
    std::string dropPattern = "nub|footsteps|finger|toe|clavicle";
    std::string weaponMaterialPattern = "gun|laser|weapon|rifle";
    // Cap zones are separate submeshes so each carries its own material
    // colour: capMaterial is the muscle (and the plain fan); the others are
    // the thin skin edge, the fat band, and the bone and marrow of limb cuts.
    std::string capMaterial = "openshim_gib_flesh";
    std::string capSkinMaterial = "openshim_gib_flesh_skin";
    std::string capFatMaterial = "openshim_gib_flesh_fat";
    std::string capBoneMaterial = "openshim_gib_flesh_bone";
    std::string capMarrowMaterial = "openshim_gib_flesh_marrow";
    // Cuts of a driving bone matching this pattern (limbs, neck) also get a
    // bone/marrow ring in the middle of the cap.
    std::string limbPattern = "arm|forearm|leg|thigh|calf|shin|knee|elbow|neck";
    float capUvScale = 4.0f;
    bool caps = true;
    // Torn-flesh rings (rim, inset ragged ring, bulged centre) instead of the
    // plain fan; loops that are degenerate, huge or far from planar fall back.
    bool capRings = true;
};
struct GibPiece
{
    Piece piece;           // name gib_<bone> (lower case) or gib_weapon
    uint16_t bone = 0;     // driving bone handle (== Ogre bone index)
    std::string boneName;  // driving bone name
    float radius = 0;      // bound radius about the piece centre
    uint32_t capTriangles = 0;
    bool weapon = false;
};
bool ExtractGibs(const std::vector<uint8_t> &mesh, const std::vector<uint8_t> &skeleton, const GibOptions &options,
                 std::vector<GibPiece> &pieces, std::string &error);
// The stock chunklet shapes already embedded for batching, emitted on demand
// with the game's scrap material. No skeleton, texture or payload pack needed.
Piece StockFallbackMesh(unsigned kind);
unsigned StockFallbackKind(std::string_view seed);
// Exact generated resource names only; vehicle pieces and similarly named
// custom assets must never become generic debris.
unsigned StockFallbackBatchKind(std::string_view resource);
// ShellCasings: a unit-length cartridge case along local +Z (centred, rim and
// base at -Z, open mouth at +Z) with `sides` facets (6..32), position/normal/
// uv0, in two submeshes using openshim_casing_brass and openshim_casing_rim.
// Deterministic; an out-of-range side count returns an empty piece.
Piece CasingMesh(unsigned sides);
} // namespace BZROpenShim::NativeChunks
