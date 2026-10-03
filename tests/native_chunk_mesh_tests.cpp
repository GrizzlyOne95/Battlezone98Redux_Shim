#include "native_chunk_mesh.h"
#include "native_chunk_cache.h"
#include "test_check.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

using Bytes = std::vector<uint8_t>;
using OpenShimTest::Require;
template <class T> void put(Bytes &b, T v)
{
    const auto *p = reinterpret_cast<const uint8_t *>(&v);
    b.insert(b.end(), p, p + sizeof(T));
}
void text(Bytes &b, const std::string &s)
{
    b.insert(b.end(), s.begin(), s.end());
    b.push_back('\n');
}
void chunk(Bytes &b, uint16_t id, const Bytes &data)
{
    put(b, id);
    put(b, static_cast<uint32_t>(data.size() + 6));
    b.insert(b.end(), data.begin(), data.end());
}
Bytes fixtureMesh(bool split = false)
{
    Bytes g;
    put(g, uint32_t{split ? 6u : 3u});
    Bytes decl, element;
    for (uint16_t v : {uint16_t{0}, uint16_t{2}, uint16_t{1}, uint16_t{0}, uint16_t{0}})
        put(element, v);
    chunk(decl, 0x5110, element);
    chunk(g, 0x5100, decl);
    Bytes vertices;
    for (float v : {11.f, 2.f, 3.f, 10.f, 3.f, 3.f, 10.f, 2.f, 4.f})
        put(vertices, v);
    if (split)
        for (float v : {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f})
            put(vertices, v);
    Bytes buf;
    put(buf, uint16_t{0});
    put(buf, uint16_t{12});
    chunk(buf, 0x5210, vertices);
    chunk(g, 0x5200, buf);
    Bytes sub;
    text(sub, "custom_material");
    put(sub, uint8_t{1});
    put(sub, uint32_t{split ? 6u : 3u});
    put(sub, uint8_t{0});
    for (uint16_t v : {uint16_t{0}, uint16_t{1}, uint16_t{2}})
        put(sub, v);
    if (split)
        for (uint16_t v : {uint16_t{3}, uint16_t{4}, uint16_t{5}})
            put(sub, v);
    Bytes body{1};
    chunk(body, 0x5000, g);
    chunk(body, 0x4000, sub);
    Bytes link;
    text(link, "test.skeleton");
    chunk(body, 0x6000, link);
    for (uint32_t v = 0; v < (split ? 6u : 3u); ++v)
    {
        Bytes a;
        put(a, v);
        put(a, static_cast<uint16_t>(v < 3 ? 1 : 0));
        put(a, 1.f);
        chunk(body, 0x7000, a);
    }
    Bytes out;
    put(out, uint16_t{0x1000});
    text(out, "[MeshSerializer_v1.8]");
    chunk(out, 0x3000, body);
    return out;
}
Bytes fixtureSkeleton(std::array<float, 4> rootRotation = {0, 0, 0, 1},
                      std::array<float, 3> rootPosition = {0, 0, 0},
                      std::array<float, 3> rootScale = {1, 1, 1},
                      std::array<float, 3> piecePosition = {10, 2, 3})
{
    Bytes out;
    put(out, uint16_t{0x1000});
    text(out, "[Serializer_v1.80]");
    for (uint16_t h : {uint16_t{0}, uint16_t{1}})
    {
        Bytes d;
        const std::string name = h ? "piece" : "root";
        text(d, name);
        put(d, h);
        for (float v : h ? piecePosition : rootPosition)
            put(d, v);
        // Ogre serializes quaternions x,y,z,w, not the in-memory w,x,y,z.
        for (float v : h ? std::array<float, 4>{0, 0, 0, 1} : rootRotation)
            put(d, v);
        if (!h && rootScale != std::array<float, 3>{1, 1, 1})
            for (float v : rootScale)
                put(d, v);
        // The source serializer excludes the name from a bone chunk's size.
        put(out, uint16_t{0x2000});
        put(out, static_cast<uint32_t>(d.size() + 6 - name.size() - 1));
        out.insert(out.end(), d.begin(), d.end());
    }
    Bytes parent;
    put(parent, uint16_t{1});
    put(parent, uint16_t{0});
    chunk(out, 0x3000, parent);
    return out;
}
Bytes load(const char *path)
{
    std::ifstream in(path, std::ios::binary);
    return Bytes(std::istreambuf_iterator<char>(in), {});
}
void extraAssignment(Bytes &mesh, uint32_t vertex, uint16_t bone, float weight)
{
    auto root = std::find(mesh.begin(), mesh.end(), uint8_t{'\n'}) - mesh.begin() + 1;
    Bytes a;
    put(a, vertex);
    put(a, bone);
    put(a, weight);
    chunk(mesh, 0x7000, a);
    const uint32_t size = static_cast<uint32_t>(mesh.size() - root);
    std::memcpy(mesh.data() + root + 2, &size, sizeof(size));
}
int main(int argc, char **argv)
{
    using namespace BZROpenShim::NativeChunks;
    std::vector<Piece> pieces;
    std::string error;
    if (argc >= 3)
    {
        auto mesh = load(argv[1]), skeleton = load(argv[2]);
        if (!Extract(mesh, skeleton, pieces, error))
        {
            std::cerr << error << '\n';
            return 1;
        }
        uint32_t triangles = 0;
        if (argc == 4)
            std::filesystem::create_directories(argv[3]);
        for (const auto &p : pieces)
        {
            triangles += p.triangles;
            if (argc == 4)
            {
                std::ofstream f(std::filesystem::path(argv[3]) / (p.name + ".mesh"), std::ios::binary);
                f.write(reinterpret_cast<const char *>(p.mesh.data()), static_cast<std::streamsize>(p.mesh.size()));
            }
        }
        std::cout << pieces.size() << " pieces, " << triangles << " triangles\n";
        return 0;
    }
    auto mesh = fixtureMesh(), skeleton = fixtureSkeleton();
    Require(StockFallbackKind("chunk1") == 1 && StockFallbackKind("CHUNK2") == 2,
            "stock chunklet names retain their shape");
    Require(StockFallbackKind("missing_piece") == StockFallbackKind("MISSING_PIECE") && StockFallbackKind("") >= 1 &&
                StockFallbackKind("") <= 2,
            "fallback choice is stable, bounded and independent of model assets");
    Require(StockFallbackMesh(0).mesh.empty() && StockFallbackMesh(3).mesh.empty(),
            "invalid fallback templates fail closed");
    Require(StockFallbackBatchKind("fallback/v1/stock_chunk1.mesh") == 1 &&
                StockFallbackBatchKind("fallback/v1/stock_chunk2.mesh") == 2 &&
                !StockFallbackBatchKind("native/abc/stock_chunk1.mesh") &&
                !StockFallbackBatchKind("fallback/v1/stock_chunk1.mesh.extra") &&
                !StockFallbackBatchKind("fallback/v2/stock_chunk1.mesh"),
            "batch classification cannot swallow model parts or similarly named assets");
    for (unsigned kind = 1; kind <= 2; ++kind)
    {
        const auto fallback = StockFallbackMesh(kind);
        const std::string data(fallback.mesh.begin(), fallback.mesh.end());
        Require(data.find("scarpmat2") != std::string::npos && SkeletonName(fallback.mesh).empty(),
                "fallback uses the stock scrap material and no skeleton");
        Require(fallback.mesh == StockFallbackMesh(kind).mesh && fallback.mesh.size() < 2048,
                "bounded deterministic fallback without external geometry");
        Require(Extract(fallback.mesh, skeleton, pieces, error) && pieces.size() == 1 &&
                    pieces[0].triangles == (kind == 1 ? 4u : 8u),
                "fallback mesh reloads with all stock faces preserved");
    }
    Require(SkeletonName(mesh) == "test.skeleton", "shared geometry skeleton link");
    Require(Extract(mesh, skeleton, pieces, error), "extract rigid bone group");
    Require(pieces.size() == 1 && pieces[0].name == "piece" && pieces[0].triangles == 1,
            "no empty root or fallback geometry");
    const auto cache = std::filesystem::temp_directory_path() /
                       ("openshim_native_chunks_" +
                        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::vector<CachedPiece> index;
    const auto originalPieces = pieces;
    Require(!ReadCache(cache, index) && index.empty(), "missing cache falls back to extraction");
    Require(WriteCache(cache, originalPieces, index) && ReadCache(cache, index) && index.size() == 1 &&
                index[0].name == "piece" && index[0].triangles == 1,
            "generated pieces reload from a complete content-validated cache");
    uintmax_t validatedBytes = 0;
    Require(!ReadCache(cache, index, 1, &validatedBytes) && index.empty() && !validatedBytes,
            "startup byte budget rejects oversized entries before payload IO");
    Require(ReadCache(cache, index, 2048, &validatedBytes) && validatedBytes == originalPieces[0].mesh.size(),
            "startup validation reports bounded payload IO");
    const auto payload = cache / "piece.mesh";
    const auto stamp = std::filesystem::file_time_type::clock::now() - std::chrono::hours(24);
    std::filesystem::last_write_time(payload, stamp);
    Require(WriteCache(cache, originalPieces, index) && std::filesystem::last_write_time(payload) == stamp,
            "unchanged payloads are not rewritten during cache repair");
    {
        std::fstream f(payload, std::ios::in | std::ios::out | std::ios::binary);
        f.put('!');
    }
    Require(!ReadCache(cache, index) && index.empty(), "same-size cache corruption is rejected");
    Require(WriteCache(cache, originalPieces, index) && ReadCache(cache, index), "corrupt cache regenerates");
    const auto manifest = cache / "pieces.cache";
    const auto malformedIndex = [&](const std::string &data) {
        { std::ofstream f(manifest, std::ios::binary | std::ios::trunc); f << data; }
        Require(!ReadCache(cache, index) && index.empty(), "untrusted or partial cache manifest rejected");
    };
    malformedIndex("old_version\n1\npiece 1 30 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V2\n1\npiece 1 30 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V3\n4097\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V3\n1\n../outside 1 30 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V3\n1\npiece 1 99999999999 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V3\n1\npiece 1\n");
    Require(WriteCache(cache, originalPieces, index), "restore fixture cache");
    { std::ofstream f(manifest, std::ios::app); f << "extra data\n"; }
    Require(!ReadCache(cache, index), "trailing cache records rejected");
    auto badPieces = originalPieces;
    badPieces[0].name = "../outside";
    Require(!WriteCache(cache, badPieces, index), "unsafe names rejected before any file writes");
    badPieces = originalPieces;
    auto duplicate = badPieces[0];
    duplicate.name = "PIECE";
    badPieces.push_back(duplicate);
    Require(!WriteCache(cache, badPieces, index), "case-colliding names cannot overwrite each other");
    Require(WriteCache(cache, originalPieces, index), "cache restored for missing-payload test");
    std::filesystem::remove(payload);
    Require(!ReadCache(cache, index), "incomplete cache rejected");
    std::filesystem::remove_all(cache);
    const std::string bytes(pieces[0].mesh.begin(), pieces[0].mesh.end());
    Require(bytes.find("custom_material") != std::string::npos, "preserve material identity");
    Require(bytes.find("test.skeleton") == std::string::npos, "static output has no skeleton dependency");
    // Pivot subtraction maps (11,2,3) to (1,0,0), with exact float bytes.
    Bytes vertex;
    for (float v : {1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f})
        put(vertex, v);
    Require(bytes.find(std::string(vertex.begin(), vertex.end())) != std::string::npos,
            "rebase vertices to bone pivot");
    // A wing's derived pivot is (10,2,3) even when the parent is translated,
    // rotated and scaled. Check the serialized output bounds independently
    // of the extractor's quaternion math: the same triangle stays at 0..1.
    const auto requireUnitBounds = [&]() {
        Require(pieces.size() == 1 && pieces[0].mesh.size() >= 28, "one detached piece with bounds");
        float bounds[6];
        std::memcpy(bounds, pieces[0].mesh.data() + pieces[0].mesh.size() - 28, sizeof(bounds));
        for (int axis = 0; axis < 3; ++axis)
            Require(std::abs(bounds[axis]) < 0.00002f && std::abs(bounds[axis + 3] - 1.f) < 0.00002f,
                    "detached wing bounds surround its derived pivot rather than the whole model origin");
    };
    constexpr float halfSqrt = 0.7071067811865475f;
    Require(Extract(mesh, fixtureSkeleton({0, 0, halfSqrt, halfSqrt}, {12, -8, 0}, {1, 1, 1}, {10, 2, 3}),
                    pieces, error),
            "Ogre xyzw parent rotation and translation");
    requireUnitBounds();
    Require(Extract(mesh, fixtureSkeleton({0, 0, halfSqrt, halfSqrt}, {4, 0, 1}, {2, 3, 4}, {1, -2, 0.5f}),
                    pieces, error),
            "scaled hierarchy derives the physical piece pivot in model space");
    requireUnitBounds();
    Require(Extract(mesh, skeleton, pieces, error), "restore identity fixture after hierarchy checks");
    auto weighted = mesh;
    for (uint32_t v = 0; v < 3; ++v)
        extraAssignment(weighted, v, 0, 0.25f);
    Require(Extract(weighted, skeleton, pieces, error), "extract soft-weighted face");
    Require(pieces.size() == 1 && pieces[0].name == "piece" && pieces[0].triangles == 1,
            "weighted face emitted once in strongest group");
    auto seam = mesh;
    extraAssignment(seam, 0, 0, 2.f);
    Require(Extract(seam, skeleton, pieces, error), "extract triangle crossing bone groups");
    Require(pieces.size() == 1 && pieces[0].name == "piece" && pieces[0].triangles == 1, "seam face preserved once");
    Require(Extract(fixtureMesh(true), skeleton, pieces, error) && pieces.size() == 2 &&
                pieces[0].name == "root" && pieces[1].name == "piece" && pieces[0].triangles == 1 &&
                pieces[1].triangles == 1,
            "face bucketing preserves distinct groups without duplication or dropped faces");
    for (size_t n = 0; n < mesh.size(); ++n)
    {
        auto cut = Bytes(mesh.begin(), mesh.begin() + n);
        Require(SkeletonName(cut).empty(), "truncated mesh cannot supply a cache-discovery skeleton link");
        Require(!Extract(cut, skeleton, pieces, error), "truncated mesh must fail closed");
    }
    auto corrupt = mesh;
    corrupt[0] = 1;
    Require(!Extract(corrupt, skeleton, pieces, error), "bad endian marker must fail closed");
    Require(!Extract(mesh, {}, pieces, error), "missing skeleton must fail closed");
    auto truncated = skeleton;
    truncated.pop_back();
    Require(!Extract(mesh, truncated, pieces, error), "truncated skeleton must fail closed");
    std::cout << "native chunk mesh tests passed\n";
}
