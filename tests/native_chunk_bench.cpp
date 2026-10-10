// Host benchmark for the native chunk / skinned gib generators. NOT a ctest
// test. Usage:
//   native_chunk_bench [--csv out.csv] [--tmp scratch_dir] [--runs N] dir [dir...]
// Recursively pairs every Ogre .mesh with the skeleton it names (same
// SkeletonName() the runtime uses; the runtime resolves it through the Ogre
// resource group by name, so a same-directory match is preferred and any
// scanned skeleton of that name is the fallback) and times, per model, the
// minimum of N runs of: Extract, SerializeCache (manifest + content hashes;
// the piece .mesh bytes are produced inside Extract), ExtractGibs, the gib
// SerializeCache, and ReadCache/ReadGibCache of a previously written cache.
// Inputs are only read; cache folders are written under --tmp.
#include "native_chunk_cache.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

using namespace BZROpenShim::NativeChunks;
namespace fs = std::filesystem;

namespace
{
using Clock = std::chrono::steady_clock;
double ms(Clock::time_point a, Clock::time_point b)
{
    return std::chrono::duration<double, std::milli>(b - a).count();
}
std::string lower(std::string s)
{
    for (auto &c : s)
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
    return s;
}
bool load(const fs::path &path, std::vector<uint8_t> &out)
{
    std::ifstream f(path, std::ios::binary);
    if (!f)
        return false;
    out.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    return !out.empty();
}
// Top-level SKELETON_BONE (0x2000) chunks of a binary .skeleton.
unsigned countBones(const std::vector<uint8_t> &s)
{
    size_t p = 2;
    while (p < s.size() && s[p++] != '\n')
    {
    }
    unsigned bones = 0;
    while (p + 6 <= s.size())
    {
        uint16_t id;
        uint32_t len;
        std::memcpy(&id, &s[p], 2);
        std::memcpy(&len, &s[p + 2], 4);
        if (id != 0x2000 && id != 0x3000 && id != 0x1010)
            break;
        if (len < 6 || len > s.size() - p)
            break;
        if (id == 0x2000)
        {
            // In 1.80 skeletons the bone's name string follows the 6-byte
            // header and is not counted in the chunk length.
            ++bones;
            size_t q = p + 6;
            while (q < s.size() && s[q] != '\n')
                ++q;
            p = q + 1 + (len - 6);
            continue;
        }
        p += len;
    }
    return bones;
}
struct Row
{
    std::string path;
    bool ok = false, hasGibs = false;
    std::string note;
    unsigned bones = 0, pieces = 0, gibPieces = 0;
    uint32_t tris = 0;
    uintmax_t bytes = 0, gibBytes = 0;
    double extract = 0, serialize = 0, gibs = 0, gibSerialize = 0, read = 0, gibRead = 0;
};
double percentile(const std::vector<double> &sorted, double p)
{
    if (sorted.empty())
        return 0;
    size_t rank = static_cast<size_t>(std::ceil(p * static_cast<double>(sorted.size())));
    rank = std::min(std::max<size_t>(rank, 1), sorted.size());
    return sorted[rank - 1];
}
bool validName(const Piece &p)
{
    return !p.name.empty() && p.name.size() < 80 &&
           p.name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-") ==
               std::string::npos;
}
// Minimum wall time of `runs` executions of fn; returns fn's last result.
template <class F> bool minTime(int runs, double &best, F fn)
{
    best = 1e300;
    bool ok = true;
    for (int r = 0; r < runs && ok; ++r)
    {
        const auto t0 = Clock::now();
        ok = fn();
        best = std::min(best, ms(t0, Clock::now()));
    }
    return ok;
}
} // namespace

int main(int argc, char **argv)
{
    fs::path csvPath, tmp = fs::temp_directory_path() / "openshim_chunk_bench";
    int runs = 3;
    std::vector<fs::path> roots;
    for (int i = 1; i < argc; ++i)
    {
        const std::string a = argv[i];
        if (a == "--csv" && i + 1 < argc)
            csvPath = argv[++i];
        else if (a == "--tmp" && i + 1 < argc)
            tmp = argv[++i];
        else if (a == "--runs" && i + 1 < argc)
            runs = std::max(1, std::atoi(argv[++i]));
        else
            roots.emplace_back(a);
    }
    if (roots.empty())
    {
        std::cerr << "usage: native_chunk_bench [--csv f] [--tmp dir] [--runs N] dir...\n";
        return 2;
    }
    std::vector<fs::path> meshes;
    std::multimap<std::string, fs::path> skeletons;
    for (const auto &root : roots)
    {
        std::error_code ec;
        for (fs::recursive_directory_iterator it(root, fs::directory_options::skip_permission_denied, ec), end;
             it != end; it.increment(ec))
        {
            if (ec)
            {
                ec.clear();
                continue;
            }
            std::error_code e2;
            if (!it->is_regular_file(e2))
                continue;
            const auto ext = lower(it->path().extension().string());
            if (ext == ".mesh")
                meshes.push_back(it->path());
            else if (ext == ".skeleton")
                skeletons.emplace(lower(it->path().filename().string()), it->path());
        }
    }
    std::sort(meshes.begin(), meshes.end());
    std::cerr << "found " << meshes.size() << " .mesh, " << skeletons.size() << " .skeleton\n";

    fs::remove_all(tmp);
    std::vector<Row> rows;
    std::map<uint64_t, bool> seen;
    size_t noSkeleton = 0, duplicates = 0, unreadable = 0;
    for (const auto &meshPath : meshes)
    {
        std::vector<uint8_t> meshBytes, skeletonBytes;
        if (!load(meshPath, meshBytes))
        {
            ++unreadable;
            continue;
        }
        const auto skelName = lower(SkeletonName(meshBytes));
        if (skelName.empty())
            continue; // static mesh, nothing to split
        auto range = skeletons.equal_range(skelName);
        const fs::path *pick = nullptr;
        for (auto it = range.first; it != range.second; ++it)
        {
            if (!pick)
                pick = &it->second;
            if (it->second.parent_path() == meshPath.parent_path())
            {
                pick = &it->second;
                break;
            }
        }
        if (!pick || !load(*pick, skeletonBytes))
        {
            ++noSkeleton;
            continue;
        }
        std::vector<uint8_t> both = meshBytes;
        both.insert(both.end(), skeletonBytes.begin(), skeletonBytes.end());
        if (!seen.emplace(Fingerprint(both), true).second)
        {
            ++duplicates; // the runtime cache is content-keyed: identical pairs are one model
            continue;
        }
        Row row;
        row.path = meshPath.string();
        row.bones = countBones(skeletonBytes);
        const std::string id = std::to_string(rows.size());
        std::vector<Piece> pieces;
        std::string error;
        double t = 0;
        if (minTime(runs, t, [&] { return Extract(meshBytes, skeletonBytes, pieces, error); }))
        {
            row.extract = t;
            // Mirror the runtime's piece-name filter before caching.
            pieces.erase(std::remove_if(pieces.begin(), pieces.end(), [](const Piece &p) { return !validName(p); }),
                         pieces.end());
            CacheImage image;
            if (minTime(runs, t, [&] { return SerializeCache(pieces, image); }))
            {
                row.ok = true;
                row.serialize = t;
                row.pieces = static_cast<unsigned>(pieces.size());
                for (const auto &p : pieces)
                {
                    row.tris += p.triangles;
                    row.bytes += p.mesh.size();
                }
                std::vector<CachedPiece> cached, back;
                if (WriteCache(tmp / "native" / id, pieces, cached))
                    row.read = minTime(runs, t, [&] { return ReadCache(tmp / "native" / id, back); }) ? t : -1;
            }
            else
                row.note = "serialize rejected";
        }
        else
            row.note = "extract: " + error;
        std::vector<GibPiece> gibs;
        std::string gibError;
        if (minTime(runs, t, [&] { return ExtractGibs(meshBytes, skeletonBytes, GibOptions{}, gibs, gibError); }))
        {
            row.hasGibs = true;
            row.gibs = t;
            row.gibPieces = static_cast<unsigned>(gibs.size());
            std::vector<Piece> gp;
            for (const auto &g : gibs)
            {
                gp.push_back(g.piece);
                row.gibBytes += g.piece.mesh.size();
            }
            CacheImage image;
            row.gibSerialize = minTime(runs, t, [&] { return SerializeCache(gp, image); }) ? t : 0;
            std::vector<CachedGib> cached, back;
            if (WriteGibCache(tmp / "gibs" / id, gibs, cached))
                row.gibRead = minTime(runs, t, [&] { return ReadGibCache(tmp / "gibs" / id, back); }) ? t : -1;
        }
        else
            row.note += (row.note.empty() ? "" : "; ") + std::string("gibs: ") + gibError;
        rows.push_back(std::move(row));
    }

    std::ostream *csv = &std::cout;
    std::ofstream csvFile;
    if (!csvPath.empty())
    {
        csvFile.open(csvPath);
        csv = &csvFile;
    }
    *csv << "model,status,bones,tris,pieces,extractMs,serializeMs,gibPieces,gibsMs,gibSerializeMs,readCacheMs,"
            "gibReadCacheMs,bytes,gibBytes,note\n";
    char buf[64];
    auto num = [&](double v) {
        std::snprintf(buf, sizeof(buf), "%.4f", v);
        return std::string(buf);
    };
    for (const auto &r : rows)
        *csv << '"' << r.path << "\"," << (r.ok ? "ok" : (r.hasGibs ? "gibs-only" : "fail")) << ',' << r.bones << ','
             << r.tris << ',' << r.pieces << ',' << num(r.extract) << ',' << num(r.serialize) << ',' << r.gibPieces
             << ',' << num(r.gibs) << ',' << num(r.gibSerialize) << ',' << num(r.read) << ',' << num(r.gibRead) << ','
             << r.bytes << ',' << r.gibBytes << ",\"" << r.note << "\"\n";

    size_t okCount = 0, gibCount = 0;
    for (const auto &r : rows)
    {
        okCount += r.ok;
        gibCount += r.hasGibs;
    }
    std::printf("models=%zu extractOk=%zu gibsOk=%zu skippedNoSkeleton=%zu duplicates=%zu unreadable=%zu runs=%d\n",
                rows.size(), okCount, gibCount, noSkeleton, duplicates, unreadable, runs);
    struct Col
    {
        const char *name;
        std::vector<double> v;
    };
    std::vector<Col> cols = {{"extractMs", {}},      {"serializeMs", {}},   {"gibsMs", {}}, {"gibSerializeMs", {}},
                             {"readCacheMs", {}},    {"gibReadCacheMs", {}}, {"bytes", {}},  {"gibBytes", {}}};
    for (const auto &r : rows)
    {
        if (r.ok)
        {
            cols[0].v.push_back(r.extract);
            cols[1].v.push_back(r.serialize);
            if (r.read > 0)
                cols[4].v.push_back(r.read);
            cols[6].v.push_back(static_cast<double>(r.bytes));
        }
        if (r.hasGibs)
        {
            cols[2].v.push_back(r.gibs);
            cols[3].v.push_back(r.gibSerialize);
            if (r.gibRead > 0)
                cols[5].v.push_back(r.gibRead);
            cols[7].v.push_back(static_cast<double>(r.gibBytes));
        }
    }
    std::printf("%-15s %6s %10s %10s %10s %10s %12s\n", "column", "n", "median", "p90", "p99", "max", "total");
    for (auto &c : cols)
    {
        std::sort(c.v.begin(), c.v.end());
        double total = 0;
        for (double x : c.v)
            total += x;
        std::printf("%-15s %6zu %10.4f %10.4f %10.4f %10.4f %12.2f\n", c.name, c.v.size(), percentile(c.v, 0.5),
                    percentile(c.v, 0.9), percentile(c.v, 0.99), c.v.empty() ? 0.0 : c.v.back(), total);
    }
    auto slowest = [&](const char *label, auto key, auto has) {
        std::vector<const Row *> v;
        for (const auto &r : rows)
            if (has(r))
                v.push_back(&r);
        std::sort(v.begin(), v.end(), [&](const Row *a, const Row *b) { return key(*a) > key(*b); });
        std::printf("\n10 slowest by %s\n", label);
        for (size_t i = 0; i < v.size() && i < 10; ++i)
            std::printf("  %9.3f ms  bones %3u tris %6u pieces %3u gibPieces %3u  %s\n", key(*v[i]), v[i]->bones,
                        static_cast<unsigned>(v[i]->tris), v[i]->pieces, v[i]->gibPieces, v[i]->path.c_str());
    };
    slowest("extract+serialize", [](const Row &r) { return r.extract + r.serialize; },
            [](const Row &r) { return r.ok; });
    slowest("gibs+serialize", [](const Row &r) { return r.gibs + r.gibSerialize; },
            [](const Row &r) { return r.hasGibs; });
    std::error_code ec;
    fs::remove_all(tmp, ec);
    return 0;
}
