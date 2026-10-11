#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::NativeChunks
{
// The default SkinnedGibs flesh: a procedural, tileable muscle texture and the
// materials for each zone of the cut caps (muscle, thin skin edge, fat band,
// bone, marrow). Pure and deterministic (no clock, no RNG state), shared by the
// runtime writer, the benchmark's preview dump and the tests.
//
// The materials inherit the stock BZBase (`material X : BZBase`, textures through
// `set_texture_alias DiffuseMap ...`), exactly like the stock pilots, so the
// stock vertex/fragment programs run on both renderers: DX9 SM3 HLSL and the DX11
// SM4 base programs (base-sm4.hlsl reads POSITION, TEXCOORD0 and NORMAL only;
// no program defines VERTEX_TANGENTS, so no tangent stream is needed). A plain
// fixed-function pass is not an option on DX11 without the compatibility layer,
// which the shipped config leaves off. Zone colours are tiny solid textures
// because the base programs are texture driven; vertex colours are not used
// (every DX11 path reads a packed colour as raw RGBA while the stock programs
// swizzle it).
//
// Bump kGibFleshVersion whenever a texture or material text changes: it is part
// of each generated file's first line / TGA id, which is how the runtime
// recognises (and replaces) a stale generated copy, while a file without the
// marker is the user's and is left alone.
inline constexpr const char *kGibFleshVersion = "v5";
inline constexpr const char *kGibFleshMaterialName = "openshim_gib_flesh";
inline constexpr const char *kGibFleshMaterialFile = "openshim_gib_flesh.material";
// Skin, fat, bone and marrow live in their own file so a mod can restyle the
// muscle (openshim_gib_flesh.material) without losing the other zones.
inline constexpr const char *kGibFleshZoneMaterialFile = "openshim_gib_flesh_zones.material";
inline constexpr const char *kGibFleshTextureFile = "openshim_gib_flesh.tga";
// Ownership prefixes of the generated files' first lines (any version).
inline constexpr const char *kGibFleshMaterialMarker = "// OpenShim SkinnedGibs default flesh material";
inline constexpr const char *kGibFleshZoneMaterialMarker = "// OpenShim SkinnedGibs default flesh zone materials";
inline constexpr unsigned kGibFleshTextureSize = 256;

// Every generated texture: the muscle image and one tiny solid image per zone
// (the base programs do not take a colour from the material).
struct GibFleshTexture
{
    const char *file;
    bool zone; // belongs to openshim_gib_flesh_zones.material, else to the muscle material
    std::vector<uint8_t> tga;
};
std::vector<GibFleshTexture> GibFleshTextures();

// Full first lines of the current generated files, without the newline.
std::string GibFleshMaterialHeader();
std::string GibFleshZoneMaterialHeader();
// The whole scripts (header line included).
std::string GibFleshMaterialScript();
std::string GibFleshZoneMaterialScript();
// kGibFleshTextureSize^2 RGB triples, top row first.
std::vector<uint8_t> GibFleshTextureRgb();
// The same image as an uncompressed 24-bit TGA; its ID field carries the
// version tag so a stale generated texture can be told from a mod's file.
std::vector<uint8_t> GibFleshTextureTga();
// Is `bytes` (the start of a file is enough) a TGA written by this module, of
// any version? Used to remove our own texture when a mod overrides the material.
bool IsGeneratedGibFleshTga(const std::vector<uint8_t> &bytes);
// Is it the current version's?
bool IsCurrentGibFleshTga(const std::vector<uint8_t> &bytes);
} // namespace BZROpenShim::NativeChunks
