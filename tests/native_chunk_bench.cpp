// Host benchmark for the native chunk / skinned gib generators. NOT a ctest
// test. Usage:
//   native_chunk_bench [--csv out.csv] [--tmp scratch_dir] [--runs N] [--gibs-only]
//                      [--hash out.txt] [--only substr] [--dump-obj outdir] [--plain-fan] dir [dir...]
// --only keeps just the meshes whose path contains the (case-insensitive) text.
// --dump-obj writes each selected model's gib pieces as OBJ+MTL (vertex colours as
// `v x y z r g b`) plus the generated flesh texture and material.
// ExtractGibs phase totals (summed over all runs, per call) are printed at the end.
// --gibs-only skips the chunk Extract/cache timings; --hash writes one line per
// gib piece ("model piece bytes fnv1a64"), sorted by model, so two builds can
// be diffed for byte-identical gib meshes.
// Recursively pairs every Ogre .mesh with the skeleton it names (same
// SkeletonName() the runtime uses; the runtime resolves it through the Ogre
// resource group by name, so a same-directory match is preferred and any
// scanned skeleton of that name is the fallback) and times, per model, the
// minimum of N runs of: Extract, SerializeCache (manifest + content hashes;
// the piece .mesh bytes are produced inside Extract), ExtractGibs, the gib
// SerializeCache, and ReadCache/ReadGibCache of a previously written cache.
// Inputs are only read; cache folders are written under --tmp.
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // fopen in the OBJ preview writer
#endif
#include "gib_flesh_texture.h"
#include "native_chunk_cache.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>

using namespace BZROpenShim::NativeChunks;
namespace BZROpenShim::NativeChunks
{
extern double g_gibPhaseMs[11];
extern double g_gibCapStats[9]; // native_chunk_mesh.cpp, OPENSHIM_NATIVE_CHUNK_PHASES
}
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

// ---- OBJ preview (--dump-obj) ---------------------------------------------
// Reads a generated piece back (Ogre v1.8 binary, our own writer's layout) and
// writes it as OBJ with `v x y z r g b` vertex colours, for looking at in
// Blender. Pieces sit in their own bone frames, laid out in a row.
struct DumpSub
{
    std::string material;
    std::vector<uint32_t> indices;
    std::vector<std::array<float, 3>> position, normal;
    std::vector<std::array<float, 2>> uv;
    std::vector<std::array<float, 3>> colour;
};
struct Cursor
{
    const std::vector<uint8_t> &b;
    size_t p;
    template <class T> T get()
    {
        T v;
        if (p + sizeof(T) > b.size())
            throw std::runtime_error("truncated piece");
        std::memcpy(&v, &b[p], sizeof(T));
        p += sizeof(T);
        return v;
    }
};
std::vector<DumpSub> parsePiece(const std::vector<uint8_t> &mesh)
{
    Cursor c{mesh, 2};
    while (c.p < mesh.size() && mesh[c.p++] != '\n')
    {
    }
    c.get<uint16_t>(); // 0x3000
    c.get<uint32_t>();
    c.get<uint8_t>();
    std::vector<DumpSub> subs;
    while (c.p + 6 <= mesh.size())
    {
        const size_t start = c.p;
        const auto id = c.get<uint16_t>();
        const auto size = c.get<uint32_t>();
        if (id != 0x4000)
        {
            c.p = start + size;
            continue;
        }
        DumpSub sub;
        while (c.p < mesh.size() && mesh[c.p] != '\n')
            sub.material.push_back(static_cast<char>(mesh[c.p++]));
        ++c.p;
        c.get<uint8_t>();
        const auto count = c.get<uint32_t>();
        const bool wide = c.get<uint8_t>() != 0;
        for (uint32_t i = 0; i < count; ++i)
            sub.indices.push_back(wide ? c.get<uint32_t>() : c.get<uint16_t>());
        c.get<uint16_t>(); // 0x5000
        c.get<uint32_t>();
        const auto vertices = c.get<uint32_t>();
        struct El
        {
            uint16_t source, type, semantic, offset, index;
        };
        std::vector<El> elements;
        c.get<uint16_t>(); // 0x5100
        const auto declSize = c.get<uint32_t>();
        for (uint32_t used = 6; used < declSize; used += 16)
        {
            c.get<uint16_t>();
            c.get<uint32_t>();
            elements.push_back({c.get<uint16_t>(), c.get<uint16_t>(), c.get<uint16_t>(), c.get<uint16_t>(),
                                c.get<uint16_t>()});
        }
        c.get<uint16_t>(); // 0x5200
        c.get<uint32_t>();
        c.get<uint16_t>(); // source
        const auto stride = c.get<uint16_t>();
        c.get<uint16_t>(); // 0x5210
        c.get<uint32_t>();
        const size_t data = c.p;
        c.p += static_cast<size_t>(vertices) * stride;
        auto f3 = [&](size_t at) {
            std::array<float, 3> v;
            std::memcpy(v.data(), &mesh[at], 12);
            return v;
        };
        for (uint32_t v = 0; v < vertices; ++v)
        {
            const size_t row = data + static_cast<size_t>(v) * stride;
            std::array<float, 3> colour{0.7f, 0.7f, 0.7f};
            std::array<float, 3> position{}, normal{0, 1, 0};
            std::array<float, 2> uv{};
            for (const auto &e : elements)
            {
                if (e.semantic == 1)
                    position = f3(row + e.offset);
                else if (e.semantic == 4)
                    normal = f3(row + e.offset);
                else if (e.semantic == 7)
                    std::memcpy(uv.data(), &mesh[row + e.offset], 8);
                else if (e.semantic == 5 && sub.material == kGibFleshMaterialName)
                {
                    uint32_t packed;
                    std::memcpy(&packed, &mesh[row + e.offset], 4);
                    // VET_COLOUR_ABGR (11) is 0xAABBGGRR; ARGB (10) and the
                    // generic colour (4) are 0xAARRGGBB.
                    const unsigned r = e.type == 11 ? packed & 255 : (packed >> 16) & 255;
                    const unsigned b = e.type == 11 ? (packed >> 16) & 255 : packed & 255;
                    colour = {static_cast<float>(r) / 255.0f, static_cast<float>((packed >> 8) & 255) / 255.0f,
                              static_cast<float>(b) / 255.0f};
                }
            }
            sub.position.push_back(position);
            sub.normal.push_back(normal);
            sub.uv.push_back(uv);
            sub.colour.push_back(colour);
        }
        subs.push_back(std::move(sub));
    }
    return subs;
}
// "r g b" of a generated zone material: the colour of its solid diffuse texture
// (the muscle returns empty: it uses the muscle texture itself).
std::string materialDiffuse(const std::string &name)
{
    const std::string scripts = GibFleshMaterialScript() + GibFleshZoneMaterialScript();
    const size_t at = scripts.find("material " + name + " : BZBase");
    if (at == std::string::npos)
        return {};
    const size_t alias = scripts.find("DiffuseMap ", at);
    const std::string file = scripts.substr(alias + 11, scripts.find('\n', alias) - alias - 11);
    for (const auto &image : GibFleshTextures())
        if (file == image.file && image.zone)
        {
            const size_t pixel = 18 + image.tga[0];
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%.3f %.3f %.3f", image.tga[pixel + 2] / 255.0, image.tga[pixel + 1] / 255.0,
                          image.tga[pixel] / 255.0);
            return buf;
        }
    return {};
}
void dumpObj(const fs::path &dir, const std::string &model, const std::vector<GibPiece> &gibs)
{
    fs::create_directories(dir);
    std::FILE *obj = std::fopen((dir / (model + ".obj")).string().c_str(), "wb");
    std::FILE *mtl = std::fopen((dir / (model + ".mtl")).string().c_str(), "wb");
    if (!obj || !mtl)
    {
        if (obj)
            std::fclose(obj);
        if (mtl)
            std::fclose(mtl);
        return;
    }
    std::fprintf(obj, "# %s gib pieces, laid out in a row (each in its own bone frame)\nmtllib %s.mtl\n",
                 model.c_str(), model.c_str());
    std::map<std::string, bool> written;
    size_t base = 1;
    float cursor = 0;
    for (const auto &gib : gibs)
    {
        std::vector<DumpSub> subs;
        try
        {
            subs = parsePiece(gib.piece.mesh);
        }
        catch (const std::exception &e)
        {
            std::fprintf(stderr, "dump %s: %s\n", gib.piece.name.c_str(), e.what());
            continue;
        }
        cursor += gib.radius;
        std::fprintf(obj, "o %s\n", gib.piece.name.c_str());
        for (const auto &sub : subs)
        {
            if (!written[sub.material])
            {
                written[sub.material] = true;
                const bool flesh = sub.material == kGibFleshMaterialName;
                const std::string kd = materialDiffuse(sub.material);
                std::fprintf(mtl, "newmtl %s\nKd %s\nKs 0.35 0.25 0.25\nNs 48\n%s\n", sub.material.c_str(),
                             kd.empty() ? "0.55 0.5 0.45" : kd.c_str(), flesh ? "map_Kd openshim_gib_flesh.tga" : "");
            }
            for (size_t v = 0; v < sub.position.size(); ++v)
                std::fprintf(obj, "v %.6f %.6f %.6f %.4f %.4f %.4f\n",
                             static_cast<double>(sub.position[v][0] + cursor), static_cast<double>(sub.position[v][1]),
                             static_cast<double>(sub.position[v][2]), static_cast<double>(sub.colour[v][0]),
                             static_cast<double>(sub.colour[v][1]), static_cast<double>(sub.colour[v][2]));
            for (const auto &n : sub.normal)
                std::fprintf(obj, "vn %.5f %.5f %.5f\n", static_cast<double>(n[0]), static_cast<double>(n[1]),
                             static_cast<double>(n[2]));
            for (const auto &t : sub.uv)
                std::fprintf(obj, "vt %.5f %.5f\n", static_cast<double>(t[0]), static_cast<double>(1.0f - t[1]));
            std::fprintf(obj, "usemtl %s\n", sub.material.c_str());
            for (size_t i = 0; i + 2 < sub.indices.size(); i += 3)
            {
                const size_t a = base + sub.indices[i], b = base + sub.indices[i + 1], c = base + sub.indices[i + 2];
                std::fprintf(obj, "f %zu/%zu/%zu %zu/%zu/%zu %zu/%zu/%zu\n", a, a, a, b, b, b, c, c, c);
            }
            base += sub.position.size();
        }
        cursor += gib.radius * 0.25f;
    }
    std::fclose(obj);
    std::fclose(mtl);
    // The generated texture and material script, next to the OBJ.
    for (const auto &image : GibFleshTextures())
        std::ofstream(dir / image.file, std::ios::binary)
            .write(reinterpret_cast<const char *>(image.tga.data()), static_cast<std::streamsize>(image.tga.size()));
    std::ofstream(dir / kGibFleshMaterialFile, std::ios::binary) << GibFleshMaterialScript();
    std::ofstream(dir / kGibFleshZoneMaterialFile, std::ios::binary) << GibFleshZoneMaterialScript();
}
} // namespace

int main(int argc, char **argv)
{
    fs::path csvPath, tmp = fs::temp_directory_path() / "openshim_chunk_bench";
    int runs = 3;
    bool gibsOnly = false;
    fs::path hashPath;
    std::string only;
    fs::path dumpDir;
    GibOptions gibOptions;
    std::vector<std::string> hashLines;
    std::vector<fs::path> roots;
    for (int i = 1; i < argc; ++i)
    {
        const std::string a = argv[i];
        if (a == "--csv" && i + 1 < argc)
            csvPath = argv[++i];
        else if (a == "--tmp" && i + 1 < argc)
            tmp = argv[++i];
        else if (a == "--gibs-only")
            gibsOnly = true;
        else if (a == "--plain-fan")
            gibOptions.capRings = false;
        else if (a == "--dump-obj" && i + 1 < argc)
            dumpDir = argv[++i];
        else if (a == "--only" && i + 1 < argc)
            only = lower(argv[++i]);
        else if (a == "--hash" && i + 1 < argc)
            hashPath = argv[++i];
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
            {
                if (only.empty() || lower(it->path().string()).find(only) != std::string::npos)
                    meshes.push_back(it->path());
            }
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
        if (gibsOnly)
            row.note = "gibs-only";
        else if (minTime(runs, t, [&] { return Extract(meshBytes, skeletonBytes, pieces, error); }))
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
        if (minTime(runs, t, [&] { return ExtractGibs(meshBytes, skeletonBytes, gibOptions, gibs, gibError); }))
        {
            row.hasGibs = true;
            row.gibs = t;
            row.gibPieces = static_cast<unsigned>(gibs.size());
            if (!dumpDir.empty())
                dumpObj(dumpDir, meshPath.stem().string(), gibs);
            std::vector<Piece> gp;
            for (const auto &g : gibs)
            {
                if (!hashPath.empty())
                    hashLines.push_back(meshPath.string() + " " + g.piece.name + " " +
                                        std::to_string(g.piece.mesh.size()) + " " + std::to_string(g.piece.triangles) +
                                        " " + std::to_string(Fingerprint(g.piece.mesh)));
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
        {
            row.note += (row.note.empty() ? "" : "; ") + std::string("gibs: ") + gibError;
            if (!hashPath.empty())
                hashLines.push_back(meshPath.string() + " FAIL " + gibError);
        }
        rows.push_back(std::move(row));
    }

    if (!hashPath.empty())
    {
        std::sort(hashLines.begin(), hashLines.end());
        std::ofstream h(hashPath);
        for (const auto &l : hashLines)
            h << l << '\n';
    }
    {
        static const char *names[11] = {"regex setup", "parse",      "owners",    "roll-up/group", "weld/edges",
                                        "piece bounds", "caps other", "serialize", "cut edges",     "cut loops",
                                        "cap triangles"};
        double total = 0;
        for (double v : g_gibPhaseMs)
            total += v;
        const double calls = static_cast<double>(std::max<size_t>(1, rows.size())) * runs;
        std::printf("ExtractGibs phases (ms per call, mean over %zu models x %d runs):\n", rows.size(), runs);
        for (int i = 0; i < 11; ++i)
            std::printf("  %-14s %9.4f  (%4.1f%%)\n", names[i], g_gibPhaseMs[i] / calls,
                        total > 0 ? 100.0 * g_gibPhaseMs[i] / total : 0.0);
    }
    std::printf("cap loops: rings %.0f (full %.0f, 0.6 %.0f, 0.3 %.0f), ear-clipped %.0f (with skin/fat bands %.0f), "
                "fan %.0f\n",
                g_gibCapStats[0] + g_gibCapStats[1] + g_gibCapStats[2], g_gibCapStats[0], g_gibCapStats[1],
                g_gibCapStats[2], g_gibCapStats[3] + g_gibCapStats[4], g_gibCapStats[4], g_gibCapStats[8]);
    std::printf("first fold at full strength: negative area %.0f, tiny area %.0f, steep %.0f\n", g_gibCapStats[5],
                g_gibCapStats[6], g_gibCapStats[7]);
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
