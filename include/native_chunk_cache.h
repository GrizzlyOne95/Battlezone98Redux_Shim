#pragma once
#include "native_chunk_mesh.h"
#include <filesystem>

namespace BZROpenShim::NativeChunks
{
struct CachedPiece
{
    std::string name;
    uint32_t triangles = 0;
    float center[3] = {0, 0, 0};
};
uint64_t Fingerprint(const std::vector<uint8_t> &bytes);
// Only complete, bounded manifests with matching payload hashes are usable.
// The caller supplies a directory keyed by both source resources and emitter
// version. Corrupt, partial or stale caches fail closed and can be regenerated.
bool ReadCache(const std::filesystem::path &directory, std::vector<CachedPiece> &pieces,
               uintmax_t byteBudget = 128 * 1024 * 1024, uintmax_t *validatedBytes = nullptr);
bool WriteCache(const std::filesystem::path &directory, const std::vector<Piece> &pieces,
                std::vector<CachedPiece> &cached);
// Skinned gib caches: the same content-validated piece cache plus a
// gibs.cache sidecar carrying each piece's driving bone and bound radius.
// A missing, stale or mismatched sidecar fails the whole cache closed.
struct CachedGib
{
    CachedPiece piece;
    uint16_t bone = 0;
    std::string boneName;
    float radius = 0;
    uint32_t capTriangles = 0;
    bool weapon = false;
};
bool ReadGibCache(const std::filesystem::path &directory, std::vector<CachedGib> &gibs);
bool WriteGibCache(const std::filesystem::path &directory, const std::vector<GibPiece> &gibs,
                   std::vector<CachedGib> &cached);
} // namespace BZROpenShim::NativeChunks
