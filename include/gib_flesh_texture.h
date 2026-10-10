#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::NativeChunks
{
// The default SkinnedGibs flesh: a procedural, tileable, mid-tone texture and
// the material that multiplies it by the cap meshes' vertex colours. Pure and
// deterministic (no clock, no RNG state), shared by the runtime writer, the
// benchmark's preview dump and the tests.
//
// Bump kGibFleshVersion whenever the texture or the material text changes: it
// is part of the generated material's first line, which is how the runtime
// recognises (and replaces) a stale generated copy, while a file without the
// marker is the user's and is left alone.
inline constexpr const char *kGibFleshVersion = "v2";
inline constexpr const char *kGibFleshMaterialName = "openshim_gib_flesh";
inline constexpr const char *kGibFleshMaterialFile = "openshim_gib_flesh.material";
inline constexpr const char *kGibFleshTextureFile = "openshim_gib_flesh.tga";
// Ownership prefix of the material's first line (any version).
inline constexpr const char *kGibFleshMaterialMarker = "// OpenShim SkinnedGibs default flesh material";
inline constexpr unsigned kGibFleshTextureSize = 256;

// Full first line of the current generated material, without the newline.
std::string GibFleshMaterialHeader();
// The whole material script (header line included).
std::string GibFleshMaterialScript();
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
