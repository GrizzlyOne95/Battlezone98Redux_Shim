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
// v4: pieces are in their bone's rotated frame and centred on their bounds.
// v3 output used model-axis offsets from the bone pivot and is ignored.
constexpr const char *kNativeFolder = "native/v4/";
struct Model
{
    std::map<std::string, std::string> pieces;
    bool extracted = false;
};
std::map<std::string, Model> models;
// Generated resource -> piece centre in its bone frame (Ogre axes). Used once
// per chunk, at creation, to move the physical origin onto the geometry.
std::map<std::string, std::array<float, 3>> pieceCenters;
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
    const std::string folder = std::string(kNativeFolder) + hex.str();
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
        const std::string resource = folder + "/" + piece.name + ".mesh";
        result.pieces[piece.name] = resource;
        pieceCenters[lower(resource)] = {piece.center[0], piece.center[1], piece.center[2]};
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
// The chunk's legacy matrix is engine memory: touch it only under SEH, with no
// C++ objects in this frame.
bool shiftOriginSafe(uint8_t *objectBytes, const float center[3], double shift[3])
{
    __try
    {
        auto *transform = reinterpret_cast<LegacyMat3 *>(objectBytes + 0x20);
        const float right[3] = {transform->right_x, transform->right_y, transform->right_z};
        const float up[3] = {transform->up_x, transform->up_y, transform->up_z};
        const float front[3] = {transform->front_x, transform->front_y, transform->front_z};
        if (!NativeChunks::FragmentOriginShift(right, up, front, center, shift))
            return false;
        const double x = transform->posit_x + shift[0], y = transform->posit_y + shift[1],
                     z = transform->posit_z + shift[2];
        if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
            return false;
        transform->posit_x = x;
        transform->posit_y = y;
        transform->posit_z = z;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
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
    pieceCenters.clear();
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
        const auto root = GetNativeChunkCacheDirectory() / kNativeFolder;
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
            readyCaches.emplace(std::string(kNativeFolder) + name, std::move(pieces));
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
bool RecenterNativeChunkObject(uint8_t *objectBytes, const char *payloadMeshName, const void *geomRef)
{
    if (!objectBytes || !payloadMeshName || !*payloadMeshName || !g_EnableChunkMeshProxy)
        return false;
    static const bool disabled = EnvFlagEnabled("OPENSHIM_DISABLE_NATIVE_CHUNK_RECENTER");
    if (disabled)
        return false;
    float center[3] = {};
    try
    {
        std::lock_guard<std::mutex> lock(modelsMutex);
        const auto found = pieceCenters.find(lower(payloadMeshName));
        if (found == pieceCenters.end())
            return false;
        std::copy(found->second.begin(), found->second.end(), center);
    }
    catch (...)
    {
        return false;
    }
    if (center[0] == 0 && center[1] == 0 && center[2] == 0)
        return false;
    // ChunkEffect::Simulate integrates, spins, terrain-tests, smokes and
    // finally explodes at this origin only, so moving it once at creation
    // makes the piece tumble and land about its own geometry. The rendered
    // mesh is centred to match; the visible pose at spawn is unchanged.
    double shift[3] = {};
    if (!shiftOriginSafe(objectBytes, center, shift))
        return false;
    if (AcquireChunkLogSlot())
    {
        // Frame check against the fragment's node-local legacy geometry.
        // Redux stores those arrays turned 180 degrees about Y relative to
        // the rendered mesh frame: geo = (-cx, cy, cz) for a piece centre c.
        // (The render side itself matches Redux's own object placement,
        // FUN_006802b0, which is what the origin shift above follows.)
        // Live GOG probe, 1.0.0.46: 86 of 86 pieces across ivsabr, ivrecy
        // (24 rotated bones), ibcmmd and fbcomm2 agree. A miss means this
        // model's piece frame disagrees; diagnostic only, nothing is undone.
        uint32_t count = 0;
        float lo[3] = {}, hi[3] = {};
        if (geomRef && TryComputeChunkGeomLocalBounds(geomRef, count, lo, hi))
        {
            const double expected[3] = {-static_cast<double>(center[0]), center[1], center[2]};
            double miss = 0, extent = 0;
            for (int axis = 0; axis < 3; ++axis)
            {
                const double d = (lo[axis] + hi[axis]) * 0.5 - expected[axis];
                miss += d * d;
                extent = std::max(extent, static_cast<double>(hi[axis] - lo[axis]));
            }
            miss = std::sqrt(miss);
            LogChunkDiagnostic("chunknative",
                               L"[CHUNKNATIVE] recentred obj=0x%08X mesh=%hs shift=(%.3f, %.3f, %.3f) "
                               L"frame=%hs geoCentre=(%.3f, %.3f, %.3f) expected=(%.3f, %.3f, %.3f) miss=%.3f "
                               L"extent=%.3f verts=%u\n",
                               static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)), payloadMeshName,
                               shift[0], shift[1], shift[2], miss <= std::max(0.05, extent * 0.02) ? "match" : "MISMATCH",
                               (lo[0] + hi[0]) * 0.5, (lo[1] + hi[1]) * 0.5, (lo[2] + hi[2]) * 0.5, expected[0],
                               expected[1], expected[2], miss, extent, count);
        }
        else
            LogChunkDiagnostic("chunknative",
                               L"[CHUNKNATIVE] recentred obj=0x%08X mesh=%hs shift=(%.3f, %.3f, %.3f) frame=unchecked\n",
                               static_cast<uint32_t>(reinterpret_cast<uintptr_t>(objectBytes)), payloadMeshName,
                               shift[0], shift[1], shift[2]);
    }
    return true;
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
