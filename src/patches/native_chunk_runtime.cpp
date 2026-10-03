#include "bzr_hooks_internal.h"
#include "native_chunk_mesh.h"
#include "native_chunk_cache.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <map>
#include <mutex>
#include <sstream>

namespace BZROpenShim::Hooks
{
namespace
{
struct Ptr
{
    void *rep = nullptr;
    void *info = nullptr;
};
static_assert(sizeof(Ptr) == 8);
using GetMesh = const Ptr *(__thiscall *)(void *);
using GetString = const std::string *(__thiscall *)(void *);
using Singleton = void *(__cdecl *)();
using Open = Ptr *(__thiscall *)(void *, Ptr *, const std::string &, const std::string &, bool, void *);
using Read = size_t(__thiscall *)(void *, void *, size_t);
using Free = void(__cdecl *)(void *);
using Dtor = void(__thiscall *)(void *, unsigned);
struct Model
{
    std::map<std::string, std::string> pieces;
    bool extracted = false;
};
std::map<std::string, Model> models;
std::mutex modelsMutex;
// Cache verification belongs to startup, before simulation. Keep only bounded
// names/counts, never source geometry or Ogre pointers, across mission hops.
std::map<std::string, std::vector<NativeChunks::CachedPiece>> readyCaches;
bool cachesWarmed = false;
size_t readyPieceCount = 0;
constexpr size_t maxReadyModels = 128;
constexpr size_t maxReadyPieces = 8192;
// Failed cache creation backs off for the rest of the mission. Do not retry
// filesystem writes every render update on a read-only installation.
int stockFallbackState = 0;
std::string lower(std::string s)
{
    for (auto &c : s)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}
std::string base(std::string s)
{
    auto p = s.find_last_of("/\\");
    if (p != std::string::npos)
        s.erase(0, p + 1);
    p = s.find_last_of('.');
    if (p != std::string::npos)
        s.resize(p);
    return lower(s);
}
// Redux's two-word SharedPtr ABI and StdAllocPolicy are already used by the
// terrain proxy. Release a stream with the owning DLL's virtual destructor
// and allocator, including the final reference; never free Ogre memory in CRT.
void release(Ptr &p, Free deallocate)
{
    if (!p.rep || !p.info)
        return;
    auto *count = reinterpret_cast<volatile LONG *>(static_cast<uint8_t *>(p.info) + 4);
    if (InterlockedDecrement(count) == 0)
    {
        auto destructor = reinterpret_cast<Dtor>((*static_cast<void ***>(p.info))[0]);
        destructor(p.info, 0);
        deallocate(p.info);
    }
    p = {};
}
bool readResource(void *manager, const std::string &name, const std::string &group, std::vector<uint8_t> &bytes)
{
    static auto open = ResolveOgreProc<Open>("?openResource@ResourceGroupManager@Ogre@@QAE?AV?$SharedPtr@VDataStream@"
                                             "Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@"
                                             "@0_NPAVResource@2@@Z");
    static auto free = ResolveOgreProc<Free>("?deallocateBytes@StdAllocPolicy@Ogre@@SAXPAX@Z");
    if (!open || !free)
        return false;
    Ptr stream;
    try
    {
        open(manager, &stream, name, group, false, nullptr);
        if (!stream.rep)
            return false;
        // Redux's DataStream ABI: isReadable, isWriteable, deleting destructor,
        // read. Read into shim-owned storage. getAsString returns an Ogre-owned
        // STL allocation whose large-buffer alignment differs from our CRT.
        auto read = reinterpret_cast<Read>((*static_cast<void ***>(stream.rep))[3]);
        std::array<uint8_t, 16384> block{};
        bytes.clear();
        while (true)
        {
            const size_t n = read(stream.rep, block.data(), block.size());
            if (n > block.size() || bytes.size() + n > 64 * 1024 * 1024)
            {
                release(stream, free);
                bytes.clear();
                return false;
            }
            if (!n)
                break;
            bytes.insert(bytes.end(), block.begin(), block.begin() + n);
        }
        release(stream, free);
        return !bytes.empty();
    }
    catch (...)
    {
        if (stream.rep)
            release(stream, free);
        return false;
    }
}
bool prepare(void *entity, char *sourceName, size_t capacity)
{
    static auto getMesh = ResolveOgreProc<GetMesh>("?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ");
    static auto getName =
        ResolveOgreProc<GetString>("?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$"
                                   "allocator@D@2@@std@@XZ");
    static auto getGroup =
        ResolveOgreProc<GetString>("?getGroup@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$"
                                   "allocator@D@2@@std@@XZ");
    static auto singleton = ResolveOgreProc<Singleton>("?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
    if (!entity || !getMesh || !getName || !getGroup || !singleton)
        return false;
    const Ptr *mesh = getMesh(entity);
    if (!mesh || !mesh->rep)
        return false;
    const std::string name = *getName(mesh->rep), group = *getGroup(mesh->rep), key = base(name);
    if (sourceName && capacity)
        strncpy_s(sourceName, capacity, name.c_str(), _TRUNCATE);
    if (models.count(key))
        return models[key].extracted;
    auto &result = models[key];
    const auto started = std::chrono::steady_clock::now();
    void *manager = singleton();
    if (!manager)
        return false;
    std::vector<uint8_t> bytes, skeleton;
    std::string error;
    if (!readResource(manager, name, group, bytes))
        return false;
    auto skeletonName = NativeChunks::SkeletonName(bytes);
    if (skeletonName.empty() || !readResource(manager, skeletonName, group, skeleton))
        return false;
    uint64_t hash = 14695981039346656037ull;
    for (const auto *source : {&bytes, &skeleton})
        for (uint8_t c : *source)
        {
            hash ^= c;
            hash *= 1099511628211ull;
        }
    // Resource names include the content fingerprint: two mods reusing a
    // basename cannot inherit each other's generated meshes, even after hops.
    std::ostringstream hex;
    hex << std::hex << hash;
    const std::string folder = "native/v3/" + hex.str();
    const auto root = GetNativeChunkCacheDirectory();
    std::vector<NativeChunks::CachedPiece> cached;
    const auto ready = readyCaches.find(folder);
    const bool reused = ready != readyCaches.end() ? (cached = ready->second, true)
                                                  : NativeChunks::ReadCache(root / folder, cached);
    if (!reused)
    {
        std::vector<NativeChunks::Piece> pieces;
        if (!NativeChunks::Extract(bytes, skeleton, pieces, error))
        {
            LogChunkDiagnostic("chunknative", L"[CHUNKNATIVE] unsupported mesh=%hs reason=%hs\n", name.c_str(),
                               error.c_str());
            return false;
        }
        // Preserve the previous per-group filename policy: an exporter's
        // unusable bone name must not suppress all of its other valid pieces.
        pieces.erase(std::remove_if(pieces.begin(), pieces.end(), [](const NativeChunks::Piece &piece) {
                         return piece.name.empty() || piece.name.size() >= 80 ||
                                piece.name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                             "0123456789_-") != std::string::npos;
                     }),
                     pieces.end());
        if (!NativeChunks::WriteCache(root / folder, pieces, cached))
            return false;
    }
    if (ready == readyCaches.end() && readyCaches.size() < maxReadyModels &&
        cached.size() <= maxReadyPieces - readyPieceCount)
    {
        readyCaches.emplace(folder, cached);
        readyPieceCount += cached.size();
    }
    uint32_t triangles = 0;
    for (const auto &piece : cached)
    {
        result.pieces[piece.name] = folder + "/" + piece.name + ".mesh";
        triangles += piece.triangles;
    }
    result.extracted = !result.pieces.empty();
    LogChunkDiagnostic("chunknative",
                       L"[CHUNKNATIVE] %hs mesh=%hs group=%hs pieces=%zu "
                       L"triangles=%u cache=%hs prepareMs=%.3f\n",
                       reused ? "reused" : "generated", name.c_str(), group.c_str(), result.pieces.size(), triangles,
                       (root / folder).string().c_str(),
                       std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count());
    return result.extracted;
}
bool prepareCppSafe(void *entity, char *sourceName, size_t capacity)
{
    try
    {
        return prepare(entity, sourceName, capacity);
    }
    catch (...)
    {
        return false;
    }
}
bool prepareSafe(void *entity, char *sourceName, size_t capacity)
{
    __try
    {
        return prepareCppSafe(entity, sourceName, capacity);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}
} // namespace
std::filesystem::path GetNativeChunkCacheDirectory()
{
    return GetMainModuleDirectory() / "openshim" / "cache" / "chunks";
}
bool PrepareNativeChunkPayloads(void *entity, char *sourceName, size_t capacity)
{
    if (!g_EnableChunkMeshProxy)
        return false;
    // Keep lock ownership outside the SEH leaf: a bad engine pointer must
    // not bypass a C++ lock_guard destructor and strand the render thread.
    std::lock_guard<std::mutex> lock(modelsMutex);
    return prepareSafe(entity, sourceName, capacity);
}
void ResetNativeChunkPayloads()
{
    std::lock_guard<std::mutex> lock(modelsMutex);
    models.clear();
    stockFallbackState = 0;
}
void WarmNativeChunkCaches()
{
    if (!g_EnableChunkMeshProxy)
        return;
    try
    {
        std::lock_guard<std::mutex> lock(modelsMutex);
        if (cachesWarmed)
            return;
        cachesWarmed = true;
        const auto start = std::chrono::steady_clock::now();
        const auto root = GetNativeChunkCacheDirectory() / "native/v3";
        std::error_code ec;
        std::filesystem::directory_iterator directories(root, ec);
        if (ec)
            return;
        uintmax_t remainingBytes = 64 * 1024 * 1024;
        size_t inspected = 0;
        for (auto end = std::filesystem::directory_iterator(); directories != end; directories.increment(ec))
        {
            if (ec || ++inspected > 512 || readyCaches.size() >= maxReadyModels ||
                readyPieceCount >= maxReadyPieces || !remainingBytes)
                break;
            const auto name = directories->path().filename().string();
            if (name.empty() || name.size() > 16 || name.find_first_not_of("0123456789abcdef") != std::string::npos)
                continue;
            std::vector<NativeChunks::CachedPiece> pieces;
            uintmax_t bytes = 0;
            const bool valid = NativeChunks::ReadCache(directories->path(), pieces, remainingBytes, &bytes);
            remainingBytes -= std::min(remainingBytes, bytes);
            if (!valid || pieces.size() > maxReadyPieces - readyPieceCount)
                continue;
            readyPieceCount += pieces.size();
            readyCaches.emplace("native/v3/" + name, std::move(pieces));
        }
        LogChunkDiagnostic("chunknative", L"[CHUNKNATIVE] startup cache validation models=%zu pieces=%zu ms=%.3f\n",
                           readyCaches.size(), readyPieceCount,
                           std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count());
    }
    catch (...)
    {
        // Cache warming is optional; the guarded first-use path still works.
    }
}
bool TryResolveGeneratedStockChunkFallback(const char *seed, char *out, size_t capacity)
{
    if (!out || !capacity)
        return false;
    out[0] = 0;
    if (!g_EnableChunkMeshProxy)
        return false;
    try
    {
        std::lock_guard<std::mutex> lock(modelsMutex);
        if (stockFallbackState < 0)
            return false;
        constexpr const char *folder = "fallback/v1/";
        if (!stockFallbackState)
        {
            stockFallbackState = -1;
            const auto root = GetNativeChunkCacheDirectory();
            std::error_code ec;
            std::filesystem::create_directories(root / folder, ec);
            if (ec)
                return false;
            for (unsigned kind = 1; kind <= 2; ++kind)
            {
                const auto piece = NativeChunks::StockFallbackMesh(kind);
                if (piece.mesh.empty())
                    return false;
                std::ofstream file(root / folder / (piece.name + ".mesh"), std::ios::binary | std::ios::trunc);
                if (!file)
                    return false;
                file.write(reinterpret_cast<const char *>(piece.mesh.data()),
                           static_cast<std::streamsize>(piece.mesh.size()));
                file.close();
                if (!file)
                    return false;
            }
            stockFallbackState = 1;
            LogChunkDiagnostic("chunknative",
                               L"[CHUNKNATIVE] generated stock debris fallback (2 templates, no asset pack)\n");
        }
        const auto kind = NativeChunks::StockFallbackKind(seed ? seed : "");
        const std::string resource = std::string(folder) + "stock_chunk" + std::to_string(kind) + ".mesh";
        if (resource.size() + 1 > capacity)
            return false;
        strncpy_s(out, capacity, resource.c_str(), _TRUNCATE);
        return true;
    }
    catch (...)
    {
        return false;
    }
}
bool TryResolveNativeChunkPayload(const char *mesh, const char *geom, char *out, size_t capacity, bool &handled)
{
    handled = false;
    if (!mesh || !geom || !out || !capacity)
        return false;
    std::lock_guard<std::mutex> lock(modelsMutex);
    auto m = models.find(base(mesh));
    if (m == models.end() || !m->second.extracted)
        return false;
    handled = true;
    const std::string key = base(geom);
    if (key.empty())
        return false;
    auto p = m->second.pieces.find(key);
    // Duplicate-suffixed geometry bones are used by several Redux exporters.
    // Only accept one candidate, and only when the original group is empty.
    if (p == m->second.pieces.end())
    {
        auto match = m->second.pieces.end();
        for (auto i = m->second.pieces.begin(); i != m->second.pieces.end(); ++i)
        {
            if (i->first.size() > key.size() && i->first.compare(0, key.size(), key) == 0 &&
                i->first.find_first_not_of("0123456789", key.size()) == std::string::npos)
            {
                if (match != m->second.pieces.end())
                    return false;
                match = i;
            }
        }
        p = match;
    }
    if (p == m->second.pieces.end())
        return false;
    strncpy_s(out, capacity, p->second.c_str(), _TRUNCATE);
    return out[0] != 0;
}
} // namespace BZROpenShim::Hooks
