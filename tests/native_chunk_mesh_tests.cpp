#include "native_chunk_mesh.h"
#include "gib_flesh_texture.h"
#include "native_chunk_cache.h"
#include "test_check.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

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
// ---- Skinned gib fixtures ---------------------------------------------------
struct GibTestSub
{
    std::string material;
    std::vector<std::array<float, 3>> positions;
    std::vector<uint16_t> indices;
    uint16_t bone;
};
// Every submesh owns its geometry (position + normal) and its assignments,
// so a cut between two submeshes is only visible through position welding.
Bytes gibFixtureMesh(const std::vector<GibTestSub> &subs)
{
    Bytes body{1};
    for (const auto &s : subs)
    {
        Bytes sub;
        text(sub, s.material);
        put(sub, uint8_t{0});
        put(sub, static_cast<uint32_t>(s.indices.size()));
        put(sub, uint8_t{0});
        for (uint16_t i : s.indices)
            put(sub, i);
        Bytes g;
        put(g, static_cast<uint32_t>(s.positions.size()));
        Bytes decl;
        for (const auto &e : {std::array<uint16_t, 5>{0, 2, 1, 0, 0}, std::array<uint16_t, 5>{0, 2, 4, 12, 0}})
        {
            Bytes element;
            for (uint16_t v : e)
                put(element, v);
            chunk(decl, 0x5110, element);
        }
        chunk(g, 0x5100, decl);
        Bytes vertices;
        for (const auto &p : s.positions)
            for (float v : {p[0], p[1], p[2], 0.f, 1.f, 0.f})
                put(vertices, v);
        Bytes buf;
        put(buf, uint16_t{0});
        put(buf, uint16_t{24});
        chunk(buf, 0x5210, vertices);
        chunk(g, 0x5200, buf);
        chunk(sub, 0x5000, g);
        for (uint32_t v = 0; v < s.positions.size(); ++v)
        {
            Bytes a;
            put(a, v);
            put(a, s.bone);
            put(a, 1.f);
            chunk(sub, 0x4100, a);
        }
        chunk(body, 0x4000, sub);
    }
    Bytes link;
    text(link, "gib.skeleton");
    chunk(body, 0x6000, link);
    Bytes bounds;
    for (float v : {-1.f, 0.f, -1.f, 1.f, 3.f, 1.f, 3.f})
        put(bounds, v);
    chunk(body, 0x9000, bounds);
    Bytes out;
    put(out, uint16_t{0x1000});
    text(out, "[MeshSerializer_v1.8]");
    chunk(out, 0x3000, body);
    return out;
}
// root (0) at the origin; head (1) one unit up, turned 90 degrees about Y;
// finger (2) half a unit above the head.
Bytes gibFixtureSkeleton(const char *rootName = "root", const char *headName = "head")
{
    constexpr float h = 0.7071067811865475f;
    struct B
    {
        const char *name;
        std::array<float, 3> position;
        std::array<float, 4> xyzw;
    };
    const B bones[] = {{rootName, {0, 0, 0}, {0, 0, 0, 1}}, {headName, {0, 1, 0}, {0, h, 0, h}},
                       {"finger", {0, 0.5f, 0}, {0, 0, 0, 1}}};
    Bytes out;
    put(out, uint16_t{0x1000});
    text(out, "[Serializer_v1.80]");
    for (uint16_t handle = 0; handle < 3; ++handle)
    {
        Bytes d;
        text(d, bones[handle].name);
        put(d, handle);
        for (float v : bones[handle].position)
            put(d, v);
        for (float v : bones[handle].xyzw)
            put(d, v);
        // The source serializer excludes the name from a bone chunk's size.
        put(out, uint16_t{0x2000});
        put(out, static_cast<uint32_t>(d.size() + 6 - std::strlen(bones[handle].name) - 1));
        out.insert(out.end(), d.begin(), d.end());
    }
    for (uint16_t child : {uint16_t{1}, uint16_t{2}})
    {
        Bytes parent;
        put(parent, child);
        put(parent, static_cast<uint16_t>(child - 1));
        chunk(out, 0x3000, parent);
    }
    return out;
}
std::vector<std::array<float, 3>> gibRing(float y)
{
    return {{-0.5f, y, -0.5f}, {0.5f, y, -0.5f}, {0.5f, y, 0.5f}, {-0.5f, y, 0.5f}};
}
GibTestSub gibBand(float y0, float y1, bool bottom, uint16_t bone)
{
    GibTestSub s{"body_mat", gibRing(y0), {}, bone};
    const auto upper = gibRing(y1);
    s.positions.insert(s.positions.end(), upper.begin(), upper.end());
    for (uint16_t i = 0; i < 4; ++i)
    {
        const uint16_t a = i, b = static_cast<uint16_t>((i + 1) % 4);
        for (uint16_t v : {a, b, static_cast<uint16_t>(b + 4), a, static_cast<uint16_t>(b + 4),
                           static_cast<uint16_t>(a + 4)})
            s.indices.push_back(v);
    }
    const std::array<uint16_t, 6> cap = bottom ? std::array<uint16_t, 6>{0, 2, 1, 0, 3, 2}
                                               : std::array<uint16_t, 6>{4, 5, 6, 4, 6, 7};
    s.indices.insert(s.indices.end(), cap.begin(), cap.end());
    return s;
}
// A square column: rings y=0 and y=1 skinned to root, a duplicated y=1 ring
// and y=2 to head, closed top and bottom; a finger triangle and a rifle.
std::vector<GibTestSub> gibFixtureSubs()
{
    GibTestSub finger{"body_mat", {{0, 2, 0}, {0.1f, 2.2f, 0}, {0, 2.2f, 0.1f}}, {0, 1, 2}, 2};
    GibTestSub rifle{"ISDF_Rifle_Mat", {{0.6f, 1.5f, 0}, {0.6f, 1.5f, 0.8f}, {0.7f, 1.6f, 0}}, {0, 1, 2}, 2};
    return {gibBand(0, 1, true, 0), gibBand(1, 2, false, 1), finger, rifle};
}
// The flesh-zone cap submeshes of a gib piece (materials openshim_gib_flesh*),
// read back from the bytes. Vertices of all zones are welded by exact position
// into one list so the cap's topology can be checked as a whole.
struct CapData
{
    bool found = false;
    std::map<std::string, uint32_t> trianglesByMaterial;
    uint32_t stride = 0;
    bool hasColourElement = false;
    std::vector<std::array<uint16_t, 4>> elements; // type, semantic, offset, index
    std::vector<std::array<float, 3>> positions, normals; // welded
    std::vector<uint32_t> indices;                         // into the welded list
    bool has(const char *material) const
    {
        const auto it = trianglesByMaterial.find(material);
        return it != trianglesByMaterial.end() && it->second > 0;
    }
};
CapData parseCap(const Bytes &mesh)
{
    CapData cap;
    std::map<std::array<float, 3>, uint32_t> weld;
    size_t p = 2;
    while (p < mesh.size() && mesh[p++] != '\n')
    {
    }
    const auto u16 = [&](size_t at) {
        uint16_t v;
        std::memcpy(&v, mesh.data() + at, 2);
        return v;
    };
    const auto u32 = [&](size_t at) {
        uint32_t v;
        std::memcpy(&v, mesh.data() + at, 4);
        return v;
    };
    p += 6 + 1; // 0x3000 header and its leading byte
    while (p + 6 <= mesh.size())
    {
        const uint16_t id = u16(p);
        const uint32_t size = u32(p + 2);
        if (id != 0x4000)
        {
            p += size;
            continue;
        }
        size_t q = p + 6;
        size_t nameEnd = q;
        while (nameEnd < mesh.size() && mesh[nameEnd] != '\n')
            ++nameEnd;
        const std::string material(mesh.begin() + static_cast<std::ptrdiff_t>(q),
                                   mesh.begin() + static_cast<std::ptrdiff_t>(nameEnd));
        q = nameEnd + 1 + 1;
        const uint32_t count = u32(q);
        const bool wide = mesh[q + 4] != 0;
        q += 5;
        std::vector<uint32_t> indices;
        for (uint32_t i = 0; i < count; ++i, q += wide ? 4 : 2)
            indices.push_back(wide ? u32(q) : u16(q));
        if (material.rfind("openshim_gib_flesh", 0) == 0)
        {
            cap.found = true;
            cap.trianglesByMaterial[material] += count / 3;
            q += 6; // 0x5000 header
            const uint32_t vertices = u32(q);
            q += 4;
            const uint32_t declSize = u32(q + 2);
            for (uint32_t used = 6, e = static_cast<uint32_t>(q) + 6; used < declSize; used += 16, e += 16)
            {
                if (u16(e + 10) == 5)
                    cap.hasColourElement = true;
                if (cap.trianglesByMaterial.size() == 1) // the first flesh submesh declares them all alike
                    cap.elements.push_back({u16(e + 8), u16(e + 10), u16(e + 12), u16(e + 14)});
            }
            q += declSize;
            cap.stride = u16(q + 8);
            const size_t data = q + 6 + 4 + 6;
            std::vector<uint32_t> global(vertices);
            for (uint32_t v = 0; v < vertices; ++v)
            {
                const size_t row = data + static_cast<size_t>(v) * cap.stride;
                std::array<float, 3> position, normal;
                std::memcpy(position.data(), mesh.data() + row, 12);
                std::memcpy(normal.data(), mesh.data() + row + 12, 12);
                const auto inserted = weld.emplace(position, static_cast<uint32_t>(cap.positions.size()));
                if (inserted.second)
                {
                    cap.positions.push_back(position);
                    cap.normals.push_back(normal);
                }
                global[v] = inserted.first->second;
            }
            for (const uint32_t index : indices)
                cap.indices.push_back(global[index]);
        }
        p += size;
    }
    return cap;
}
float dot(const std::array<float, 3> &a, const std::array<float, 3> &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
std::array<float, 3> cross(const std::array<float, 3> &a, const std::array<float, 3> &b)
{
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}
std::array<float, 3> minus(const std::array<float, 3> &a, const std::array<float, 3> &b)
{
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}
bool allFinite(const CapData &cap)
{
    for (size_t v = 0; v < cap.positions.size(); ++v)
        for (int i = 0; i < 3; ++i)
            if (!std::isfinite(cap.positions[v][i]) || !std::isfinite(cap.normals[v][i]))
                return false;
    return true;
}
// Every directed edge once; interior edges shared by exactly two triangles in
// opposite directions; the remaining boundary has exactly `rim` edges (the cut
// loop), so the cap is a closed, consistently wound disc glued to the cut.
bool closedWinding(const CapData &cap, size_t rim)
{
    std::map<std::pair<uint32_t, uint32_t>, int> directed;
    for (size_t t = 0; t + 2 < cap.indices.size(); t += 3)
        for (size_t e = 0; e < 3; ++e)
            ++directed[{cap.indices[t + e], cap.indices[t + (e + 1) % 3]}];
    size_t boundary = 0;
    for (const auto &[edge, count] : directed)
    {
        if (count != 1)
            return false;
        if (!directed.count({edge.second, edge.first}))
            ++boundary;
    }
    return boundary == rim;
}
// Every face winds with its vertex normals, and none is degenerate or folded
// against them (a folded flap would flip its geometric normal).
bool windingMatchesNormals(const CapData &cap)
{
    for (size_t t = 0; t + 2 < cap.indices.size(); t += 3)
    {
        const auto &a = cap.positions[cap.indices[t]], &b = cap.positions[cap.indices[t + 1]],
                   &c = cap.positions[cap.indices[t + 2]];
        const auto face = cross(minus(b, a), minus(c, a));
        std::array<float, 3> n{0, 0, 0};
        for (size_t k = 0; k < 3; ++k)
            for (int i = 0; i < 3; ++i)
                n[i] += cap.normals[cap.indices[t + k]][i];
        if (!(dot(face, n) > 0))
            return false;
    }
    return true;
}
void gibTests()
{
    using namespace BZROpenShim::NativeChunks;
    const auto mesh = gibFixtureMesh(gibFixtureSubs());
    const auto skeleton = gibFixtureSkeleton();
    std::vector<GibPiece> gibs;
    std::string error;
    Require(ExtractGibs(mesh, skeleton, GibOptions{}, gibs, error), ("extract gibs: " + error).c_str());
    Require(gibs.size() == 3 && gibs[0].piece.name == "gib_head" && gibs[1].piece.name == "gib_root" &&
                gibs[2].piece.name == "gib_weapon",
            "finger rolls into the kept head; root and weapon stay separate, in sorted order");
    const auto &head = gibs[0], &root = gibs[1], &weapon = gibs[2];
    Require(head.bone == 1 && head.boneName == "head" && root.bone == 0 && root.boneName == "root",
            "body gibs record their driving bone handle and name");
    Require(weapon.weapon && weapon.bone == 2 && weapon.capTriangles == 0 && weapon.piece.triangles == 1,
            "weapon submesh is one uncapped piece driven by its own dominant bone, not rolled up");
    // A square loop on a non-limb cut: rim plus four inner rings of 4 and a
    // centre -- 4 bands of 8 triangles (skin, fat, clot, muscle) plus a 4-triangle fan.
    Require(head.capTriangles == 36 && root.capTriangles == 36,
            "the welded cut between the two submeshes closes one torn-flesh cap per side");
    Require(head.piece.triangles == 10 + 1 + 36 && root.piece.triangles == 10 + 36,
            "every skinned face lands in exactly one gib, plus its caps");
    {
        const std::string bytes(head.piece.mesh.begin(), head.piece.mesh.end());
        Require(bytes.find("openshim_gib_flesh") != std::string::npos && bytes.find("body_mat") != std::string::npos,
                "caps use the flesh material in their own submesh");
        const std::string weaponBytes(weapon.piece.mesh.begin(), weapon.piece.mesh.end());
        Require(weaponBytes.find("ISDF_Rifle_Mat") != std::string::npos &&
                    weaponBytes.find("openshim_gib_flesh") == std::string::npos,
                "weapon keeps its own material and gets no cap");
    }
    // Caps face away from their own piece: up out of the root, down out of
    // the head. The head's bind yaw about Y leaves the vertical axis alone.
    const auto rootCap = parseCap(root.piece.mesh), headCap = parseCap(head.piece.mesh);
    Require(rootCap.found && headCap.found && rootCap.positions.size() == 21 && headCap.positions.size() == 21,
            "cap vertices are shared: rim 4, four inner rings of 4, centre 1");
    // Smoothed normals tilt with the bulge but still face away from the piece.
    Require(std::all_of(rootCap.normals.begin(), rootCap.normals.end(),
                        [](const std::array<float, 3> &n) { return n[1] > 0.7f; }) &&
                std::all_of(headCap.normals.begin(), headCap.normals.end(),
                            [](const std::array<float, 3> &n) { return n[1] < -0.7f; }),
            "cap normals point away from the piece");
    // Head bone sits at (0,1,0); its geometry spans y 1..2.2, so the
    // bone-frame centre is y = 0.6. The root spans 0..1.
    Require(std::abs(head.piece.center[1] - 0.6f) < 1e-4f && std::abs(root.piece.center[1] - 0.5f) < 1e-4f,
            "piece centres are reported in the driving bone frame");
    Require(head.radius > 0.5f && root.radius > 0.5f, "bound radius recorded");
    std::vector<GibPiece> again;
    Require(ExtractGibs(mesh, skeleton, GibOptions{}, again, error) && again.size() == gibs.size(),
            "repeat extraction");
    for (size_t i = 0; i < gibs.size(); ++i)
        Require(again[i].piece.mesh == gibs[i].piece.mesh && again[i].piece.name == gibs[i].piece.name,
                "gib output is byte-for-byte deterministic");

    // ---- Torn-flesh cap structure ------------------------------------------
    {
        // A square loop on a non-limb cut: rim + three inner rings of 4 and a
        // centre (17 vertices); skin, fat and two muscle bands of 8 triangles
        // each plus a 4-triangle muscle fan.
        Require(rootCap.stride == 32 && !rootCap.hasColourElement && !headCap.hasColourElement,
                "caps carry no vertex colour: position, normal, uv0 (stride 32); hue is in the zone textures");
        // Exactly the inputs the stock BZBase programs read (base-sm4.hlsl base_vertex:
        // POSITION float3, TEXCOORD0 float2, NORMAL float3; no VERTEX_TANGENTS anywhere),
        // so there is no D3D11 input-layout mismatch.
        using Element = std::array<uint16_t, 4>;
        Require(rootCap.elements == std::vector<Element>{{2, 1, 0, 0}, {2, 4, 12, 0}, {1, 7, 24, 0}} &&
                    headCap.elements == rootCap.elements,
                "cap vertex elements: POSITION float3 @0, NORMAL float3 @12, TEXCOORD0 float2 @24");
        Require(rootCap.trianglesByMaterial.size() == 4 && rootCap.has("openshim_gib_flesh_skin") &&
                    rootCap.has("openshim_gib_flesh_fat") && rootCap.has("openshim_gib_flesh_clot") &&
                    rootCap.has("openshim_gib_flesh") &&
                    !rootCap.has("openshim_gib_flesh_bone") && !rootCap.has("openshim_gib_flesh_marrow"),
                "a non-limb cut has skin, fat, clot and muscle zones and no bone ring");
        Require(rootCap.trianglesByMaterial.at("openshim_gib_flesh_skin") == 8 &&
                    rootCap.trianglesByMaterial.at("openshim_gib_flesh_fat") == 8 &&
                    rootCap.trianglesByMaterial.at("openshim_gib_flesh") == 12,
                "zone triangle counts follow the ring layers");
        Require(allFinite(rootCap) && allFinite(headCap), "no NaN or infinite cap positions or normals");
        Require(closedWinding(rootCap, 4) && closedWinding(headCap, 4),
                "cap rings form a closed, consistently wound disc whose only boundary is the cut loop");
        Require(windingMatchesNormals(rootCap) && windingMatchesNormals(headCap),
                "cap faces wind with their outward normals and none is folded");
        // The rim is the cut itself: its four corners are present exactly.
        const std::array<float, 3> corner = {-0.5f, 0.5f, -0.5f}; // root bone frame, ring at y=1 about centre y=0.5
        Require(std::any_of(rootCap.positions.begin(), rootCap.positions.end(),
                            [&](const std::array<float, 3> &q) { return near(q, corner); }),
                "the rim sits exactly on the cut");
        // Every inner ring stays inside the rim (no flap pokes outside it).
        Require(std::all_of(rootCap.positions.begin(), rootCap.positions.end(),
                            [](const std::array<float, 3> &q) { return std::abs(q[0]) <= 0.5f + 1e-4f &&
                                                                        std::abs(q[2]) <= 0.5f + 1e-4f; }),
                "no cap vertex lies outside the cut loop");
        std::vector<GibPiece> repeat;
        Require(ExtractGibs(mesh, skeleton, GibOptions{}, repeat, error) &&
                    parseCap(repeat[1].piece.mesh).positions == rootCap.positions,
                "ragged offsets are deterministic");

        // A limb cut adds muscle -> bone -> marrow: 6 rings + centre; skin 8,
        // fat 8, muscle 16, bone 8, marrow 4.
        const auto limbSkeleton = gibFixtureSkeleton("bip01_l_thigh", "bip01_neck");
        std::vector<GibPiece> limb;
        Require(ExtractGibs(mesh, limbSkeleton, GibOptions{}, limb, error) && limb.size() == 3,
                ("limb extraction: " + error).c_str());
        // Sorted by bone name: bip01_l_thigh (the root), then bip01_neck (the head).
        const auto thighCap = parseCap(limb[0].piece.mesh), neckCap = parseCap(limb[1].piece.mesh);
        Require(limb[0].boneName == "bip01_l_thigh" && limb[0].capTriangles == 52 && thighCap.positions.size() == 29 &&
                    limb[1].boneName == "bip01_neck" && limb[1].capTriangles == 52 && neckCap.positions.size() == 29,
                "limb and neck cuts add muscle, bone and marrow rings");
        Require(thighCap.has("openshim_gib_flesh_bone") && thighCap.has("openshim_gib_flesh_marrow") &&
                    neckCap.has("openshim_gib_flesh_bone") && neckCap.has("openshim_gib_flesh_marrow") &&
                    thighCap.trianglesByMaterial.at("openshim_gib_flesh") == 16,
                "limb caps have bone and marrow zones");
        Require(closedWinding(thighCap, 4) && closedWinding(neckCap, 4) && windingMatchesNormals(thighCap) &&
                    allFinite(thighCap),
                "limb caps are closed and consistently wound");
        GibOptions noLimb;
        noLimb.limbPattern.clear();
        std::vector<GibPiece> plain;
        Require(ExtractGibs(mesh, limbSkeleton, noLimb, plain, error) && plain[0].capTriangles == 36 &&
                    !parseCap(plain[0].piece.mesh).has("openshim_gib_flesh_bone"),
                "the limb pattern is an option; empty disables the bone ring");

        // Rings off: the loop is ear-clipped as the polygon it is, n-2
        // triangles over the rim vertices only (no centre vertex, no fan).
        GibOptions ear;
        ear.capRings = false;
        ear.capBands = false;
        std::vector<GibPiece> flat;
        Require(ExtractGibs(mesh, skeleton, ear, flat, error) && flat[1].capTriangles == 2 &&
                    flat[0].capTriangles == 2 && flat[1].capEarLoops == 1 && flat[1].capFanLoops == 0 &&
                    flat[1].capRingLoops == 0,
                "an ear-clipped simple loop has n-2 triangles and is counted as ear-clipped");
        const auto earCap = parseCap(flat[1].piece.mesh);
        Require(earCap.positions.size() == 4 && closedWinding(earCap, 4) && allFinite(earCap) &&
                    windingMatchesNormals(earCap) && earCap.trianglesByMaterial.size() == 1 &&
                    earCap.has("openshim_gib_flesh"),
                "the ear-clipped cap is closed, wound with its normal, in the muscle material");
        // With bands on (the default) the same loop gets skin and fat insets
        // where it does not self-intersect; a 4-point loop is too small to inset.
        GibOptions bandedOptions;
        bandedOptions.capRings = false;
        std::vector<GibPiece> banded;
        Require(ExtractGibs(mesh, skeleton, bandedOptions, banded, error) && banded[1].capEarLoops == 1,
                "bands are optional on ear-clipped loops");
        Require(flat[1].capRingLoops == 0 && ExtractGibs(mesh, skeleton, GibOptions{}, flat, error) &&
                    flat[1].capRingLoops == 1 && flat[1].capFanLoops == 0,
                "the default close of a square loop is ringed");
        auto tiny = gibFixtureSubs();
        for (auto &sub : tiny)
            for (auto &p : sub.positions)
                for (float &c : p)
                    c *= 1.5e-3f;
        std::vector<GibPiece> small;
        Require(ExtractGibs(gibFixtureMesh(tiny), skeleton, GibOptions{}, small, error) && small.size() == 3 &&
                    small[1].capTriangles == 2 && small[1].capEarLoops == 1 && small[1].capFanLoops == 0,
                "a tiny loop is ear-clipped, not fanned");
        // A very non-planar loop (opposite corners lifted: a saddle): rings
        // do not apply, but its projection is a simple square, so it is
        // ear-clipped over the exact rim vertices.
        auto warped = gibFixtureSubs();
        for (auto &sub : warped)
            for (auto &p : sub.positions)
                if (std::abs(p[1] - 1.0f) < 1e-6f && p[0] * p[2] > 0.2f)
                    p[1] = 2.2f;
        std::vector<GibPiece> bent;
        Require(ExtractGibs(gibFixtureMesh(warped), skeleton, GibOptions{}, bent, error) && bent.size() == 3 &&
                    bent[1].capTriangles == 2 && bent[0].capTriangles == 2 && bent[1].capFanLoops == 0,
                "a very non-planar loop is ear-clipped, not fanned");
    }

    GibOptions merge;
    merge.keepPattern.clear();
    merge.minFaceFraction = 0.6f;
    Require(ExtractGibs(mesh, skeleton, merge, gibs, error) && gibs.size() == 2 && gibs[0].piece.name == "gib_root" &&
                gibs[0].capTriangles == 0 && gibs[0].piece.triangles == 21 && gibs[1].piece.name == "gib_weapon",
            "small bones roll up deepest first and a whole-body gib has no cut to cap");
    GibOptions noCaps;
    noCaps.caps = false;
    Require(ExtractGibs(mesh, skeleton, noCaps, gibs, error) && gibs.size() == 3 && gibs[0].capTriangles == 0 &&
                gibs[0].piece.triangles == 11,
            "caps can be disabled");
    GibOptions badPattern;
    badPattern.dropPattern = "(";
    Require(!ExtractGibs(mesh, skeleton, badPattern, gibs, error) && gibs.empty(), "bad pattern fails closed");
    Require(!ExtractGibs(mesh, {}, GibOptions{}, gibs, error) && gibs.empty(), "missing skeleton fails closed");

    // Cache round trip, including the bone sidecar.
    Require(ExtractGibs(mesh, skeleton, GibOptions{}, gibs, error), "restore gibs");
    const auto cache = std::filesystem::temp_directory_path() /
                       ("openshim_gib_cache_" +
                        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::vector<CachedGib> cached, read;
    Require(!ReadGibCache(cache, read), "missing gib cache");
    Require(WriteGibCache(cache, gibs, cached) && cached.size() == 3 && ReadGibCache(cache, read) && read.size() == 3,
            "gib cache round trip");
    for (size_t i = 0; i < 3; ++i)
        Require(read[i].piece.name == gibs[i].piece.name && read[i].bone == gibs[i].bone &&
                    read[i].boneName == gibs[i].boneName && read[i].radius == gibs[i].radius &&
                    read[i].weapon == gibs[i].weapon && read[i].capTriangles == gibs[i].capTriangles &&
                    std::memcmp(read[i].piece.center, gibs[i].piece.center, sizeof(read[i].piece.center)) == 0,
                "gib cache keeps bones, radius and centre bit-exactly");
    {
        std::ofstream f(cache / "gibs.cache", std::ios::binary | std::ios::trunc);
        f << "OPENSHIM_SKINNED_GIBS_V1\n3\n";
    }
    Require(!ReadGibCache(cache, read) && read.empty(), "truncated gib sidecar fails closed");
    std::filesystem::remove(cache / "gibs.cache");
    Require(!ReadGibCache(cache, read), "missing gib sidecar fails closed");
    std::filesystem::remove_all(cache);
}
// The procedural flesh texture and its material script.
void fleshTextureTests()
{
    using namespace BZROpenShim::NativeChunks;
    const auto rgb = GibFleshTextureRgb();
    constexpr unsigned N = kGibFleshTextureSize;
    Require(rgb.size() == static_cast<size_t>(N) * N * 3 && rgb == GibFleshTextureRgb(),
            "flesh texture is the right size and deterministic");
    double sum = 0;
    for (size_t i = 0; i < rgb.size(); i += 3)
        sum += (0.299 * rgb[i] + 0.587 * rgb[i + 1] + 0.114 * rgb[i + 2]) / 255.0;
    const double mean = sum / (static_cast<double>(N) * N);
    double red = 0, green = 0, blue = 0;
    for (size_t i = 0; i < rgb.size(); i += 3)
    {
        red += rgb[i];
        green += rgb[i + 1];
        blue += rgb[i + 2];
    }
    // Deep red-brown muscle overall (the texture carries the hue), neither black nor pale.
    Require(red > green * 2.0 && red > blue * 2.0 && mean > 0.12 && mean < 0.55,
            "flesh texture is desaturated deep red-brown muscle");
    // Tileable: the wrap-around step is no bigger than an ordinary neighbouring step.
    double wrapStep = 0, step = 0;
    for (unsigned y = 0; y < N; ++y)
        for (unsigned c = 0; c < 3; ++c)
        {
            wrapStep += std::abs(static_cast<int>(rgb[(y * N + N - 1) * 3 + c]) - static_cast<int>(rgb[(y * N) * 3 + c]));
            for (unsigned x = 0; x + 1 < N; ++x)
                step += std::abs(static_cast<int>(rgb[(y * N + x) * 3 + c]) - static_cast<int>(rgb[(y * N + x + 1) * 3 + c])) /
                        static_cast<double>(N - 1);
        }
    double wrapRows = 0, rows = 0;
    for (unsigned x = 0; x < N; ++x)
        for (unsigned c = 0; c < 3; ++c)
        {
            wrapRows += std::abs(static_cast<int>(rgb[((N - 1) * N + x) * 3 + c]) - static_cast<int>(rgb[x * 3 + c]));
            for (unsigned y = 0; y + 1 < N; ++y)
                rows += std::abs(static_cast<int>(rgb[(y * N + x) * 3 + c]) - static_cast<int>(rgb[((y + 1) * N + x) * 3 + c])) /
                        static_cast<double>(N - 1);
        }
    Require(wrapStep <= 2.5 * step && wrapRows <= 2.5 * rows, "flesh texture tiles without a seam");
    const auto tga = GibFleshTextureTga();
    Require(tga.size() == 18 + tga[0] + static_cast<size_t>(N) * N * 3 && tga[2] == 2 && tga[16] == 24 &&
                IsGeneratedGibFleshTga(tga) && IsCurrentGibFleshTga(tga) && !IsGeneratedGibFleshTga({}) &&
                !IsCurrentGibFleshTga(Bytes(64, 0)),
            "flesh TGA is an uncompressed 24-bit image tagged with its version");
    const std::string script = GibFleshMaterialScript();
    Require(script.rfind(GibFleshMaterialHeader(), 0) == 0 &&
                script.find("import * from \"BZBase.material\"") != std::string::npos &&
                script.find("material openshim_gib_flesh : BZBase") != std::string::npos &&
                script.find(std::string("set_texture_alias DiffuseMap ") + kGibFleshTextureFile) != std::string::npos &&
                script.find("vertexcolour") == std::string::npos && script.find("vertex_program") == std::string::npos,
            "muscle material inherits the stock BZBase with the muscle texture as its diffuse map");
    {
        // One solid-colour texture per zone, each referenced by its material.
        const std::string zones = GibFleshZoneMaterialScript();
        const auto images = GibFleshTextures();
        size_t zoneImages = 0;
        bool referenced = true, allCurrent = true;
        for (const auto &image : images)
        {
            allCurrent = allCurrent && IsCurrentGibFleshTga(image.tga);
            if (image.zone)
            {
                ++zoneImages;
                referenced = referenced && zones.find(std::string("DiffuseMap ") + image.file) != std::string::npos;
            }
        }
        Require(images.size() == 6 && zoneImages == 5 && referenced && allCurrent &&
                    zones.find(" : BZBase") != std::string::npos,
                "each cap zone has its own generated texture and a BZBase-derived material");
    }
    Require(std::string(kGibFleshMaterialName) == GibOptions{}.capMaterial &&
                GibFleshZoneMaterialScript().find(GibOptions{}.capSkinMaterial) != std::string::npos &&
                GibFleshZoneMaterialScript().find(GibOptions{}.capFatMaterial) != std::string::npos &&
                GibFleshZoneMaterialScript().find(GibOptions{}.capBoneMaterial) != std::string::npos &&
                GibFleshZoneMaterialScript().find(GibOptions{}.capMarrowMaterial) != std::string::npos &&
                GibFleshZoneMaterialScript().rfind(GibFleshZoneMaterialHeader(), 0) == 0,
            "the default cap materials are the ones the writer generates");
}
// Offline check against a real model: prints the split, like
// scripts/export_gib_payloads.py does.
int printGibs(const char *meshPath, const char *skeletonPath)
{
    using namespace BZROpenShim::NativeChunks;
    const auto mesh = load(meshPath), skeleton = load(skeletonPath);
    std::vector<GibPiece> gibs;
    std::string error;
    if (!ExtractGibs(mesh, skeleton, GibOptions{}, gibs, error))
    {
        std::cerr << "ExtractGibs failed: " << error << '\n';
        return 1;
    }
    uint32_t triangles = 0;
    for (const auto &gib : gibs)
    {
        triangles += gib.piece.triangles;
        std::printf("  %-24s bone %-24s handle %3u tris %5u caps %4u r %.3f centre (%.3f, %.3f, %.3f)\n",
                    gib.piece.name.c_str(), gib.boneName.c_str(), static_cast<unsigned>(gib.bone),
                    static_cast<unsigned>(gib.piece.triangles), static_cast<unsigned>(gib.capTriangles),
                    static_cast<double>(gib.radius), static_cast<double>(gib.piece.center[0]),
                    static_cast<double>(gib.piece.center[1]), static_cast<double>(gib.piece.center[2]));
    }
    std::printf("%zu gibs, %u triangles\n", gibs.size(), static_cast<unsigned>(triangles));
    uint32_t rings = 0, ears = 0, fans = 0;
    for (const auto &gib : gibs)
    {
        rings += gib.capRingLoops;
        ears += gib.capEarLoops;
        fans += gib.capFanLoops;
    }
    std::printf("cut loops: %u ringed, %u ear-clipped, %u fan\n", rings, ears, fans);
    // Centroid fans are the very last resort: a real pilot has almost none.
    if (fans * 10 > rings + ears + fans)
        return 1;
    // A humanoid must come apart into limbs, not one lump or a hundred bits.
    return gibs.size() >= 6 && gibs.size() <= 32 ? 0 : 1;
}
int main(int argc, char **argv)
{
    if (argc == 4 && std::string(argv[1]) == "--gibs")
        return printGibs(argv[2], argv[3]);
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
    fleshTextureTests();
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
    {
        // ShellCasings' generated cartridge case.
        Require(CasingMesh(5).mesh.empty() && CasingMesh(33).mesh.empty(), "invalid casing side counts fail closed");
        const auto casing = CasingMesh(10);
        const std::string data(casing.mesh.begin(), casing.mesh.end());
        Require(casing.mesh == CasingMesh(10).mesh && casing.mesh.size() < 32768, "casing mesh is deterministic and small");
        Require(data.find("openshim_casing_brass") != std::string::npos &&
                    data.find("openshim_casing_rim") != std::string::npos && SkeletonName(casing.mesh).empty(),
                "casing uses the brass and rim materials and no skeleton");
        // Body 3 bands + rim band = 4 * 2 * sides; rim top annulus 2 * sides;
        // base and mouth discs one fan triangle per side each.
        Require(casing.triangles == 10u * (8u + 2u + 2u), "casing triangle count");
        Require(Extract(casing.mesh, skeleton, pieces, error) && pieces.size() == 1 &&
                    pieces[0].triangles == casing.triangles,
                "casing mesh reloads through the Ogre mesh parser with every face");
        // Bounds: unit length along Z, rim radius 0.225 across X/Y.
        // The bounds chunk (id 0x9000, 6-byte header, min, max, radius) is
        // the last thing in the file.
        float bounds[7] = {};
        Require(casing.mesh.size() > sizeof(bounds) + 6 &&
                    casing.mesh[casing.mesh.size() - sizeof(bounds) - 6] == 0x00 &&
                    casing.mesh[casing.mesh.size() - sizeof(bounds) - 5] == 0x90,
                "casing ends with its bounds chunk");
        std::memcpy(bounds, casing.mesh.data() + casing.mesh.size() - sizeof(bounds), sizeof(bounds));
        Require(std::fabs(bounds[2] + 0.5f) < 1e-5f && std::fabs(bounds[5] - 0.5f) < 1e-5f &&
                    std::fabs(bounds[3] - 0.225f) < 1e-4f && std::fabs(bounds[0] + 0.225f) < 1e-3f,
                "casing bounds span z -0.5..0.5 and the rim radius");
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
    gibTests();
    std::cout << "native chunk mesh tests passed\n";
}
