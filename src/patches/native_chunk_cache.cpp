#include "native_chunk_cache.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
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
constexpr const char *manifestVersion = "OPENSHIM_NATIVE_CHUNKS_V4";
// Centres round-trip as their exact IEEE bit patterns, not decimal text.
uint32_t bits(float value)
{
    uint32_t out;
    std::memcpy(&out, &value, sizeof(out));
    return out;
}
float fromBits(uint32_t value)
{
    float out;
    std::memcpy(&out, &value, sizeof(out));
    return out;
}
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
            uint32_t center[3] = {};
            if (!(input >> piece.name >> piece.triangles >> bytes >> hash >> center[0] >> center[1] >> center[2]) ||
                !safeName(piece.name) || !piece.triangles || !names.insert(piece.name).second || !bytes ||
                bytes > maxPieceBytes || bytes > byteBudget - total)
                return false;
            for (int axis = 0; axis < 3; ++axis)
            {
                piece.center[axis] = fromBits(center[axis]);
                if (!std::isfinite(piece.center[axis]) || std::abs(piece.center[axis]) > 100000)
                    return false;
            }
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
            for (float axis : piece.center)
                if (!std::isfinite(axis) || std::abs(axis) > 100000)
                    return false;
            total += piece.mesh.size();
            manifest << name << ' ' << piece.triangles << ' ' << piece.mesh.size() << ' '
                     << Fingerprint(piece.mesh) << ' ' << bits(piece.center[0]) << ' ' << bits(piece.center[1])
                     << ' ' << bits(piece.center[2]) << '\n';
            result.push_back({name, piece.triangles, {piece.center[0], piece.center[1], piece.center[2]}});
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
namespace
{
constexpr const char *gibManifestName = "gibs.cache";
constexpr const char *gibManifestVersion = "OPENSHIM_SKINNED_GIBS_V1";
std::string hexName(const std::string &name)
{
    static const char digits[] = "0123456789abcdef";
    std::string out;
    for (unsigned char c : name)
    {
        out.push_back(digits[c >> 4]);
        out.push_back(digits[c & 15]);
    }
    return out.empty() ? std::string("-") : out;
}
bool unhexName(const std::string &hex, std::string &out)
{
    out.clear();
    if (hex == "-")
        return true;
    if (hex.size() % 2 || hex.size() > 256)
        return false;
    for (size_t i = 0; i < hex.size(); i += 2)
    {
        int value = 0;
        for (size_t k = 0; k < 2; ++k)
        {
            const char c = hex[i + k];
            value <<= 4;
            if (c >= '0' && c <= '9')
                value |= c - '0';
            else if (c >= 'a' && c <= 'f')
                value |= c - 'a' + 10;
            else
                return false;
        }
        if (value < 0x20 || value > 0x7E)
            return false;
        out.push_back(static_cast<char>(value));
    }
    return true;
}
} // namespace
bool ReadGibCache(const std::filesystem::path &directory, std::vector<CachedGib> &gibs)
{
    gibs.clear();
    try
    {
        std::vector<CachedPiece> pieces;
        if (!ReadCache(directory, pieces))
            return false;
        std::error_code ec;
        const auto path = directory / gibManifestName;
        if (std::filesystem::file_size(path, ec) > 256 * 1024 || ec)
            return false;
        std::ifstream input(path);
        std::string version;
        size_t count = 0;
        if (!std::getline(input, version) || version != gibManifestVersion || !(input >> count) ||
            count != pieces.size())
            return false;
        std::vector<CachedGib> result;
        for (size_t i = 0; i < count; ++i)
        {
            CachedGib gib;
            std::string name, boneHex;
            uint32_t bone = 0, radius = 0, weapon = 0;
            if (!(input >> name >> bone >> boneHex >> radius >> gib.capTriangles >> weapon) || bone > 0xFFFF ||
                weapon > 1 || name != pieces[i].name || !unhexName(boneHex, gib.boneName))
                return false;
            gib.piece = pieces[i];
            gib.bone = static_cast<uint16_t>(bone);
            gib.radius = fromBits(radius);
            gib.weapon = weapon != 0;
            if (!std::isfinite(gib.radius) || gib.radius < 0 || gib.radius > 100000 ||
                gib.capTriangles > gib.piece.triangles)
                return false;
            result.push_back(std::move(gib));
        }
        input >> std::ws;
        if (!input.eof())
            return false;
        gibs = std::move(result);
        return true;
    }
    catch (...)
    {
        gibs.clear();
        return false;
    }
}
bool WriteGibCache(const std::filesystem::path &directory, const std::vector<GibPiece> &gibs,
                   std::vector<CachedGib> &cached)
{
    cached.clear();
    try
    {
        std::vector<Piece> pieces;
        for (const auto &gib : gibs)
        {
            if (!std::isfinite(gib.radius) || gib.radius < 0 || gib.radius > 100000)
                return false;
            pieces.push_back(gib.piece);
        }
        std::vector<CachedPiece> written;
        // Drop a stale sidecar first: a crash between the two writes must
        // never pair new pieces with old bones.
        std::error_code ec;
        std::filesystem::remove(directory / gibManifestName, ec);
        if (!WriteCache(directory, pieces, written) || written.size() != gibs.size())
            return false;
        std::ostringstream manifest;
        manifest << gibManifestVersion << '\n' << gibs.size() << '\n';
        std::vector<CachedGib> result;
        for (size_t i = 0; i < gibs.size(); ++i)
        {
            const auto &gib = gibs[i];
            manifest << written[i].name << ' ' << gib.bone << ' ' << hexName(gib.boneName) << ' ' << bits(gib.radius)
                     << ' ' << gib.capTriangles << ' ' << (gib.weapon ? 1 : 0) << '\n';
            CachedGib entry;
            entry.piece = written[i];
            entry.bone = gib.bone;
            entry.boneName = gib.boneName;
            entry.radius = gib.radius;
            entry.capTriangles = gib.capTriangles;
            entry.weapon = gib.weapon;
            result.push_back(std::move(entry));
        }
        std::ofstream output(directory / gibManifestName, std::ios::binary | std::ios::trunc);
        output << manifest.str();
        output.close();
        if (!output)
            return false;
        cached = std::move(result);
        return true;
    }
    catch (...)
    {
        cached.clear();
        return false;
    }
}
} // namespace BZROpenShim::NativeChunks
