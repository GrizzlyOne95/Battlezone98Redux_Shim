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
Bytes fixtureMesh(bool split = false, bool normals = false)
{
    Bytes g;
    put(g, uint32_t{split ? 6u : 3u});
    Bytes decl, element;
    for (uint16_t v : {uint16_t{0}, uint16_t{2}, uint16_t{1}, uint16_t{0}, uint16_t{0}})
        put(element, v);
    chunk(decl, 0x5110, element);
    if (normals)
    {
        Bytes normal;
        for (uint16_t v : {uint16_t{0}, uint16_t{2}, uint16_t{4}, uint16_t{12}, uint16_t{0}})
            put(normal, v);
        chunk(decl, 0x5110, normal);
    }
    chunk(g, 0x5100, decl);
    Bytes vertices;
    const float positions[] = {11.f, 2.f, 3.f, 10.f, 3.f, 3.f, 10.f, 2.f, 4.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f};
    for (size_t v = 0; v < (split ? 6u : 3u); ++v)
    {
        for (size_t axis = 0; axis < 3; ++axis)
            put(vertices, positions[v * 3 + axis]);
        if (normals)
            for (float n : {1.f, 0.f, 0.f})
                put(vertices, n);
    }
    Bytes buf;
    put(buf, uint16_t{0});
    put(buf, static_cast<uint16_t>(normals ? 24 : 12));
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
    // Ogre always closes the mesh with bounds (min, max, radius).
    Bytes bounds;
    for (float v : {0.f, 0.f, 0.f, 11.f, 3.f, 4.f, 12.f})
        put(bounds, v);
    chunk(body, 0x9000, bounds);
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
// Reads back float triples from a generated piece's single vertex stream,
// independently of the extractor: positions at +0, normals at +12 if stride 24.
std::vector<std::array<float, 3>> outputVectors(const Bytes &mesh, size_t offset)
{
    std::vector<std::array<float, 3>> out;
    for (size_t p = 0; p + 6 <= mesh.size(); ++p)
    {
        uint16_t id;
        uint32_t size;
        std::memcpy(&id, mesh.data() + p, 2);
        std::memcpy(&size, mesh.data() + p + 2, 4);
        if (id != 0x5210 || p + size > mesh.size() || size < 6)
            continue;
        uint16_t stride;
        std::memcpy(&stride, mesh.data() + p - 2, 2);
        if (stride != 12 && stride != 24)
            continue;
        if ((size - 6) % stride || offset + 12 > stride)
            continue;
        for (size_t v = p + 6; v < p + size; v += stride)
        {
            std::array<float, 3> value;
            std::memcpy(value.data(), mesh.data() + v + offset, 12);
            out.push_back(value);
        }
        return out;
    }
    return out;
}
bool near(const std::array<float, 3> &a, std::array<float, 3> b)
{
    for (int i = 0; i < 3; ++i)
        if (std::abs(a[i] - b[i]) > 0.0001f)
            return false;
    return true;
}
void extraAssignment(Bytes &mesh, uint32_t vertex, uint16_t bone, float weight)
{
    auto root = std::find(mesh.begin(), mesh.end(), uint8_t{'\n'}) - mesh.begin() + 1;
    Bytes a;
    put(a, vertex);
    put(a, bone);
    put(a, weight);
    // Mesh-level assignments precede the trailing bounds chunk (6 + 28).
    Bytes assignmentChunk;
    chunk(assignmentChunk, 0x7000, a);
    mesh.insert(mesh.end() - 34, assignmentChunk.begin(), assignmentChunk.end());
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
    Require(std::memcmp(index[0].center, originalPieces[0].center, sizeof(index[0].center)) == 0,
            "piece centres round-trip bit-exactly through the cache");
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
    // V3 pieces were offset in model axes from the bone pivot: never reuse.
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V3\n1\npiece 1 30 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V4\n4097\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V4\n1\n../outside 1 30 0 0 0 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V4\n1\npiece 1 99999999999 0 0 0 0\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V4\n1\npiece 1\n");
    malformedIndex("OPENSHIM_NATIVE_CHUNKS_V4\n1\npiece 1 30 0\n");
    Require(WriteCache(cache, originalPieces, index), "restore fixture cache");
    {
        // Otherwise-valid entry with a NaN centre (0x7FC00000): it must not
        // be able to move a fragment origin.
        std::ifstream in(manifest, std::ios::binary);
        std::string valid((std::istreambuf_iterator<char>(in)), {});
        in.close();
        const auto lineStart = valid.rfind('\n', valid.size() - 2) + 1;
        std::string fields = valid.substr(lineStart);
        for (int field = 0; field < 3; ++field)
            fields.erase(fields.find_last_of(' ', fields.size() - 2));
        malformedIndex(valid.substr(0, lineStart) + fields + " 2143289344 0 0\n");
    }
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
    // Pivot (10,2,3) maps the triangle to the unit axes; centring on its
    // bounds then moves it by (0.5,0.5,0.5). Exact float bytes.
    Bytes vertex;
    for (float v : {0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f})
        put(vertex, v);
    Require(bytes.find(std::string(vertex.begin(), vertex.end())) != std::string::npos,
            "rebase vertices to bone pivot, then centre on the piece");
    Require(pieces[0].center[0] == 0.5f && pieces[0].center[1] == 0.5f && pieces[0].center[2] == 0.5f,
            "piece centre is reported in the bone frame");
    // Fragments spin about their origin, so every piece must surround it,
    // even one whose bone pivot sits away from the geometry.
    const auto requireCentred = [&](std::array<float, 3> center) {
        Require(pieces.size() == 1 && pieces[0].mesh.size() >= 28, "one detached piece with bounds");
        float bounds[6];
        std::memcpy(bounds, pieces[0].mesh.data() + pieces[0].mesh.size() - 28, sizeof(bounds));
        for (int axis = 0; axis < 3; ++axis)
            Require(std::abs(bounds[axis] + 0.5f) < 0.00002f && std::abs(bounds[axis + 3] - 0.5f) < 0.00002f,
                    "piece bounds are centred on the fragment origin");
        Require(near({pieces[0].center[0], pieces[0].center[1], pieces[0].center[2]}, center),
                "piece centre in the rotated bone frame");
    };
    // The engine's fragment carries the node's full world matrix, so a
    // rotated bone's piece must be stored in that bone's rotated frame:
    // derived pose here is (10,2,3) rotated 90 degrees about Z. Rotating
    // the model-space offsets back by -90 gives (0,-1,0), (1,0,0), (0,0,1).
    constexpr float halfSqrt = 0.7071067811865475f;
    Require(Extract(mesh, fixtureSkeleton({0, 0, halfSqrt, halfSqrt}, {12, -8, 0}, {1, 1, 1}, {10, 2, 3}),
                    pieces, error),
            "Ogre xyzw parent rotation and translation");
    requireCentred({0.5f, -0.5f, 0.5f});
    {
        const auto positions = outputVectors(pieces[0].mesh, 0);
        Require(positions.size() == 3 && near(positions[0], {-0.5f, -0.5f, -0.5f}) &&
                    near(positions[1], {0.5f, 0.5f, -0.5f}) && near(positions[2], {-0.5f, 0.5f, 0.5f}),
                "bind rotation removed: rotating by the bone pose restores the source vertices");
    }
    Require(Extract(mesh, fixtureSkeleton({0, 0, halfSqrt, halfSqrt}, {4, 0, 1}, {2, 3, 4}, {1, -2, 0.5f}),
                    pieces, error),
            "scaled hierarchy derives the physical piece pivot in model space");
    requireCentred({0.5f, -0.5f, 0.5f});
    // Normals are directions in the same frame: rotate, never translate.
    Require(Extract(fixtureMesh(false, true),
                    fixtureSkeleton({0, 0, halfSqrt, halfSqrt}, {12, -8, 0}, {1, 1, 1}, {10, 2, 3}), pieces,
                    error),
            "extract rotated piece with normals");
    {
        const auto normals = outputVectors(pieces[0].mesh, 12);
        Require(normals.size() == 3 &&
                    std::all_of(normals.begin(), normals.end(),
                                [](const auto &n) { return near(n, {0.f, -1.f, 0.f}); }),
                "normals rotated into the bone frame");
    }
    Require(Extract(fixtureMesh(false, true), skeleton, pieces, error), "extract identity piece with normals");
    {
        const auto normals = outputVectors(pieces[0].mesh, 12);
        Require(normals.size() == 3 && std::all_of(normals.begin(), normals.end(),
                                                   [](const auto &n) { return n == std::array<float, 3>{1.f, 0.f, 0.f}; }),
                "identity binds keep exact normal bytes");
    }
    // Origin shift: sim axes mirror Ogre's Z, then follow the fragment basis.
    {
        const float right[3] = {1, 0, 0}, up[3] = {0, 1, 0}, front[3] = {0, 0, 1};
        const float center[3] = {1, 2, 3};
        double shift[3];
        Require(FragmentOriginShift(right, up, front, center, shift) && shift[0] == 1 && shift[1] == 2 &&
                    shift[2] == -3,
                "identity fragment shifts by the Z-mirrored centre");
        // Yaw 90 degrees: local +X (right) points along world -Z, local +Z
        // (front) along world +X. Non-unit legacy basis lengths are ignored.
        const float yawRight[3] = {0, 0, -2}, yawUp[3] = {0, 3, 0}, yawFront[3] = {4, 0, 0};
        Require(FragmentOriginShift(yawRight, yawUp, yawFront, center, shift) && std::abs(shift[0] + 3) < 1e-9 &&
                    std::abs(shift[1] - 2) < 1e-9 && std::abs(shift[2] + 1) < 1e-9,
                "rotated fragment shifts along its own basis");
        const float degenerate[3] = {0, 0, 0};
        Require(!FragmentOriginShift(degenerate, up, front, center, shift), "degenerate basis fails closed");
    }
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
    {
        // Exporters behind several Resurgence craft write submesh and root
        // lengths a byte short. Ogre reads chunks by content and loads them;
        // so must we, without letting a short file through.
        auto undersized = mesh;
        const std::string data(undersized.begin(), undersized.end());
        const size_t submesh = data.find("custom_material") - 6;
        const size_t root = data.find('\n') + 1;
        for (size_t at : {submesh, root})
        {
            uint32_t size;
            std::memcpy(&size, undersized.data() + at + 2, 4);
            --size;
            std::memcpy(undersized.data() + at + 2, &size, 4);
        }
        Require(undersized[submesh] == 0x00 && undersized[submesh + 1] == 0x40 && undersized[root + 1] == 0x30,
                "fixture chunk offsets located");
        Require(Extract(undersized, skeleton, pieces, error) && pieces.size() == 1 && pieces[0].triangles == 1 &&
                    SkeletonName(undersized) == "test.skeleton",
                "under-declared chunk lengths parse by content, as Ogre does");
        // sbsilo/rbsilo claim 17 bytes past the end of the file.
        uint32_t size;
        std::memcpy(&size, undersized.data() + root + 2, 4);
        size += 18;
        std::memcpy(undersized.data() + root + 2, &size, 4);
        Require(Extract(undersized, skeleton, pieces, error) && pieces.size() == 1,
                "over-declared root length is ignored when the content is complete");
        auto noBounds = mesh;
        noBounds.resize(noBounds.size() - 34);
        Require(!Extract(noBounds, skeleton, pieces, error) && SkeletonName(noBounds).empty(),
                "content cut at a chunk boundary is still truncation");
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
