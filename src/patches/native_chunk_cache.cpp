#include "native_chunk_cache.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <set>
#include <sstream>

namespace BZROpenShim::NativeChunks
{
namespace
{
constexpr uintmax_t maxPieceBytes = 64 * 1024 * 1024;
constexpr uintmax_t maxCacheBytes = 128 * 1024 * 1024;
constexpr size_t maxPieces = 4096;
constexpr const char *manifestName = "pieces.cache";
constexpr const char *manifestVersion = "OPENSHIM_NATIVE_CHUNKS_V3";
std::string normalized(std::string name)
{
    for (auto &c : name)
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
    return name;
}
bool safeName(const std::string &name)
{
    return !name.empty() && name.size() < 80 &&
           name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_-") == std::string::npos;
}
bool matches(const std::filesystem::path &file, uintmax_t bytes, uint64_t expectedHash)
{
    std::error_code ec;
    if (!bytes || bytes > maxPieceBytes || !std::filesystem::is_regular_file(file, ec) || ec ||
        std::filesystem::file_size(file, ec) != bytes || ec)
        return false;
    std::ifstream input(file, std::ios::binary);
    if (!input)
        return false;
    std::array<char, 16384> block{};
    uint64_t hash = 14695981039346656037ull;
    uintmax_t read = 0;
    while (input)
    {
        input.read(block.data(), block.size());
        const auto n = input.gcount();
        read += static_cast<uintmax_t>(n);
        if (read > bytes)
            return false;
        for (std::streamsize i = 0; i < n; ++i)
        {
            hash ^= static_cast<uint8_t>(block[static_cast<size_t>(i)]);
            hash *= 1099511628211ull;
        }
    }
    return input.eof() && read == bytes && hash == expectedHash;
}
} // namespace
uint64_t Fingerprint(const std::vector<uint8_t> &bytes)
{
    uint64_t hash = 14695981039346656037ull;
    for (auto c : bytes)
    {
        hash ^= c;
        hash *= 1099511628211ull;
    }
    return hash;
}
bool ReadCache(const std::filesystem::path &directory, std::vector<CachedPiece> &pieces, uintmax_t byteBudget,
               uintmax_t *validatedBytes)
{
    pieces.clear();
    if (validatedBytes)
        *validatedBytes = 0;
    byteBudget = std::min(byteBudget, maxCacheBytes);
    try
    {
        std::error_code ec;
        const auto path = directory / manifestName;
        if (std::filesystem::file_size(path, ec) > 512 * 1024 || ec)
            return false;
        std::ifstream input(path);
        std::string version;
        size_t count = 0;
        if (!std::getline(input, version) || version != manifestVersion || !(input >> count) || !count ||
            count > maxPieces)
            return false;
        std::vector<CachedPiece> result;
        std::set<std::string> names;
        uintmax_t total = 0;
        for (size_t i = 0; i < count; ++i)
        {
            CachedPiece piece;
            uintmax_t bytes = 0;
            uint64_t hash = 0;
            if (!(input >> piece.name >> piece.triangles >> bytes >> hash) || !safeName(piece.name) ||
                !piece.triangles || !names.insert(piece.name).second || !bytes || bytes > maxPieceBytes ||
                bytes > byteBudget - total)
                return false;
            total += bytes;
            if (validatedBytes)
                *validatedBytes = total;
            if (!matches(directory / (piece.name + ".mesh"), bytes, hash))
                return false;
            result.push_back(std::move(piece));
        }
        input >> std::ws;
        if (!input.eof())
            return false;
        pieces = std::move(result);
        if (validatedBytes)
            *validatedBytes = total;
        return true;
    }
    catch (...)
    {
        return false;
    }
}
bool WriteCache(const std::filesystem::path &directory, const std::vector<Piece> &pieces,
                std::vector<CachedPiece> &cached)
{
    cached.clear();
    try
    {
        if (pieces.empty() || pieces.size() > maxPieces)
            return false;
        std::set<std::string> names;
        uintmax_t total = 0;
        std::vector<CachedPiece> result;
        std::ostringstream manifest;
        manifest << manifestVersion << '\n' << pieces.size() << '\n';
        // Validate every name and bound before touching any cache files.
        for (const auto &piece : pieces)
        {
            const auto name = normalized(piece.name);
            if (!safeName(name) || !names.insert(name).second || !piece.triangles || piece.mesh.empty() ||
                piece.mesh.size() > maxPieceBytes || piece.mesh.size() > maxCacheBytes - total)
                return false;
            total += piece.mesh.size();
            manifest << name << ' ' << piece.triangles << ' ' << piece.mesh.size() << ' '
                     << Fingerprint(piece.mesh) << '\n';
            result.push_back({name, piece.triangles});
        }
        std::error_code ec;
        std::filesystem::create_directories(directory, ec);
        if (ec)
            return false;
        for (size_t i = 0; i < pieces.size(); ++i)
        {
            const auto &piece = pieces[i];
            const auto file = directory / (result[i].name + ".mesh");
            if (matches(file, piece.mesh.size(), Fingerprint(piece.mesh)))
                continue;
            std::ofstream output(file, std::ios::binary | std::ios::trunc);
            output.write(reinterpret_cast<const char *>(piece.mesh.data()),
                         static_cast<std::streamsize>(piece.mesh.size()));
            output.close();
            if (!output)
                return false;
        }
        // Publish the index last. Interrupted writes never make a partial
        // cache usable: readers also validate each file's size and content.
        std::ofstream output(directory / manifestName, std::ios::binary | std::ios::trunc);
        output << manifest.str();
        output.close();
        if (!output)
            return false;
        cached = std::move(result);
        return true;
    }
    catch (...)
    {
        return false;
    }
}
} // namespace BZROpenShim::NativeChunks
