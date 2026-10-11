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
// Hue lives in materials and the texture, never in vertex colours: every DX11
// path reads a packed vertex colour as raw RGBA while the stock/compat programs
// swizzle it (.bgra), so a coloured vertex draws with red and blue swapped on
// whichever path does not swizzle. Plain material colours behave identically on
// DX9 fixed function, the DX11 compatibility layer and a generated DX11 shader.
//
// Bump kGibFleshVersion whenever the texture or a material text changes: it is
// part of each generated file's first line, which is how the runtime
// recognises (and replaces) a stale generated copy, while a file without the
// marker is the user's and is left alone.
inline constexpr const char *kGibFleshVersion = "v3";
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
