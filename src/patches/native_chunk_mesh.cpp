#include "native_chunk_mesh.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <map>
#include <regex>
#include <set>
#include <stdexcept>

namespace BZROpenShim::NativeChunks
{
namespace
{
using Bytes = std::vector<uint8_t>;
// Keep the canonical stock geometry shared with the renderer without bringing
// its live Ogre ABI into this engine-independent serializer.
struct OgreVector3
{
    float x, y, z;
};
#include "chunk_proxy_generic_meshes.inl"
static_assert(kChunk1MeshBytes && kChunk2MeshBytes && kChunk1MeshFnv1a && kChunk2MeshFnv1a);
struct Reader
{
    const Bytes &b;
    size_t p, end;
    void need(size_t n) const
    {
        if (p > end || n > end - p)
            throw std::runtime_error("truncated Ogre chunk");
    }
    template <class T> T get()
    {
        need(sizeof(T));
        T v;
        std::memcpy(&v, b.data() + p, sizeof(T));
        p += sizeof(T);
        return v;
    }
    std::string line()
    {
        std::string s;
        while (true)
        {
            char c = get<char>();
            if (c == '\n')
                return s;
            if (s.size() >= 1024)
                throw std::runtime_error("oversized Ogre string");
            s += c;
        }
    }
    Reader chunk(uint16_t &id)
    {
        const size_t start = p;
        id = get<uint16_t>();
        uint32_t n = get<uint32_t>();
        if (n < 6)
            throw std::runtime_error("invalid Ogre chunk length");
        need(n - 6);
        p = start + n;
        return {b, start + 6, p};
    }
};
template <class T> void put(Bytes &b, T v)
{
    const auto *p = reinterpret_cast<const uint8_t *>(&v);
    b.insert(b.end(), p, p + sizeof(T));
}
void line(Bytes &b, const std::string &s)
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
Reader header(const Bytes &b, bool mesh)
{
    Reader r{b, 0, b.size()};
    if (r.get<uint16_t>() != 0x1000)
        throw std::runtime_error("unsupported Ogre endianness");
    auto v = r.line();
    if (mesh && v != "[MeshSerializer_v1.8]" && v != "[MeshSerializer_v1.100]" && v != "[MeshSerializer_v1.41]")
        throw std::runtime_error("unsupported Ogre mesh version");
    if (!mesh && v != "[Serializer_v1.80]" && v != "[Serializer_v1.10]")
        throw std::runtime_error("unsupported Ogre skeleton version");
    return r;
}
struct Element
{
    uint16_t source, type, semantic, offset, index;
};
struct Buffer
{
    uint16_t stride;
    Bytes data;
};
struct Geometry
{
    uint32_t count = 0;
    std::vector<Element> elements;
    std::map<uint16_t, Buffer> buffers;
};
struct Assignment
{
    uint32_t vertex;
    uint16_t bone;
    float weight;
};
struct Sub
{
    std::string material;
    bool shared = false;
    uint16_t operation = 4;
    Geometry geometry;
    std::vector<uint32_t> indices;
    std::vector<Assignment> assignments;
};
struct Model
{
    Geometry geometry;
    std::vector<Assignment> assignments;
    std::vector<Sub> subs;
    std::string skeleton;
};
// Ogre's MeshSerializer reads chunks sequentially by content and uses the
// declared lengths only to skip chunks it does not know. Some exporters'
// v1.100/v1.8 lengths are a few bytes off, which Ogre tolerates, so parse
// the same way: known chunks by their contents, children while their IDs fit.
struct Head
{
    uint16_t id;
    uint32_t size;
    size_t start;
};
bool nextHead(Reader &r, Head &h)
{
    if (r.p > r.end || r.end - r.p < 6)
        return false;
    h.start = r.p;
    h.id = r.get<uint16_t>();
    h.size = r.get<uint32_t>();
    return true;
}
void rewind(Reader &r, const Head &h)
{
    r.p = h.start;
}
Geometry geometry(Reader &r, bool copy)
{
    Geometry g;
    g.count = r.get<uint32_t>();
    if (g.count > 1000000)
        throw std::runtime_error("oversized vertex count");
    Head h;
    while (nextHead(r, h))
    {
        if (h.id == 0x5100)
        {
            Head e;
            while (nextHead(r, e))
            {
                if (e.id != 0x5110)
                {
                    rewind(r, e);
                    break;
                }
                g.elements.push_back({r.get<uint16_t>(), r.get<uint16_t>(), r.get<uint16_t>(), r.get<uint16_t>(),
                                      r.get<uint16_t>()});
                if (g.elements.size() > 64)
                    throw std::runtime_error("oversized vertex declaration");
            }
        }
        else if (h.id == 0x5200)
        {
            auto source = r.get<uint16_t>();
            auto stride = r.get<uint16_t>();
            Head d;
            if (!nextHead(r, d) || d.id != 0x5210 || stride == 0 || stride > 4096)
                throw std::runtime_error("invalid vertex buffer");
            const size_t n = static_cast<size_t>(g.count) * stride;
            r.need(n);
            Buffer buffer{stride, {}};
            if (copy)
                buffer.data.assign(r.b.begin() + r.p, r.b.begin() + r.p + n);
            if (!g.buffers.emplace(source, std::move(buffer)).second)
                throw std::runtime_error("duplicate vertex buffer source");
            r.p += n;
        }
        else
        {
            rewind(r, h);
            break;
        }
    }
    return g;
}
Assignment assignment(Reader &r)
{
    return {r.get<uint32_t>(), r.get<uint16_t>(), r.get<float>()};
}
Sub submesh(Reader &r, bool copy)
{
    Sub s;
    s.material = r.line();
    s.shared = r.get<uint8_t>() != 0;
    auto count = r.get<uint32_t>();
    bool wide = r.get<uint8_t>() != 0;
    if (count > 3000000)
        throw std::runtime_error("oversized index count");
    r.need(static_cast<size_t>(count) * (wide ? 4 : 2));
    s.indices.reserve(count);
    for (uint32_t i = 0; i < count; ++i)
        s.indices.push_back(wide ? r.get<uint32_t>() : r.get<uint16_t>());
    Head h;
    if (!s.shared)
    {
        if (!nextHead(r, h) || h.id != 0x5000)
            throw std::runtime_error("missing submesh geometry");
        s.geometry = geometry(r, copy);
    }
    while (nextHead(r, h))
    {
        if (h.id == 0x4010)
            s.operation = r.get<uint16_t>();
        else if (h.id == 0x4100)
            s.assignments.push_back(assignment(r));
        else if (h.id == 0x4200)
        {
            r.line();
            r.line();
        }
        else
        {
            rewind(r, h);
            break;
        }
    }
    return s;
}
// `copy` false walks the same structure without copying vertex data, for a
// cache hit that only needs the skeleton link.
Model model(const Bytes &b, bool copy = true)
{
    auto r = header(b, true);
    Head h;
    if (!nextHead(r, h) || h.id != 0x3000)
        throw std::runtime_error("missing Ogre mesh");
    // Lengths are not trusted: shipped Resurgence/stock exports over- and
    // under-declare the root by up to 17 bytes, and Ogre ignores them.
    r.get<uint8_t>();
    Model m;
    // Ogre writes shared geometry, submeshes, the skeleton link and mesh
    // bone assignments, then always at least the bounds chunk. Stopping at
    // a known trailing chunk proves everything consumed here is complete,
    // without trusting a possibly mis-sized length to skip it.
    bool complete = false;
    while (nextHead(r, h))
    {
        if (h.id == 0x5000)
            m.geometry = geometry(r, copy);
        else if (h.id == 0x4000)
        {
            m.subs.push_back(submesh(r, copy));
            if (m.subs.size() > 1024)
                throw std::runtime_error("oversized submesh count");
        }
        else if (h.id == 0x6000)
            m.skeleton = r.line();
        else if (h.id == 0x7000)
            m.assignments.push_back(assignment(r));
        else if (h.id >= 0x8000 && h.id <= 0xE000 && (h.id & 0x0FFF) == 0)
        {
            // LOD, bounds, submesh names, edge lists, poses, animations or
            // extremes. Bounds is fixed-size, so check its body as well.
            if (h.id == 0x9000)
                r.need(28);
            complete = true;
            break;
        }
        else
            throw std::runtime_error("unexpected Ogre mesh chunk");
    }
    if (m.subs.empty())
        throw std::runtime_error("mesh has no submeshes");
    if (!complete)
        throw std::runtime_error("truncated Ogre mesh (no trailing chunks)");
    return m;
}
using V = std::array<float, 3>;
using Q = std::array<float, 4>;
V add(V a, V b)
{
    for (int i = 0; i < 3; ++i)
        a[i] += b[i];
    return a;
}
V mul(V a, V b)
{
    for (int i = 0; i < 3; ++i)
        a[i] *= b[i];
    return a;
}
Q product(Q a, Q b)
{
    return {
        a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3], a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2],
        a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1], a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0]};
}
V rotate(Q q, V v)
{
    auto x = product(product(q, {0, v[0], v[1], v[2]}), {q[0], -q[1], -q[2], -q[3]});
    return {x[1], x[2], x[3]};
}
struct Bone
{
    std::string name;
    int parent = -1;
    V pos{}, scale{1, 1, 1};
    Q ori{1, 0, 0, 0};
    int state = 0;
};
std::map<uint16_t, Bone> bones(const Bytes &b)
{
    auto r = header(b, false);
    std::map<uint16_t, Bone> out;
    while (r.p < r.end)
    {
        const size_t start = r.p;
        uint16_t id = r.get<uint16_t>();
        auto size = r.get<uint32_t>();
        if (size < 6)
            throw std::runtime_error("invalid skeleton chunk");
        if (id == 0x2000)
        {
            Bone x;
            const size_t nameStart = r.p;
            x.name = r.line();
            const size_t nameBytes = r.p - nameStart;
            auto handle = r.get<uint16_t>();
            x.pos = {r.get<float>(), r.get<float>(), r.get<float>()};
            // Ogre Serializer::writeObject(Quaternion) writes x,y,z,w,
            // while our quaternion arithmetic uses w,x,y,z. Treating the
            // serialized identity as w-first rotates child pivots by 180
            // degrees and makes detached geometry orbit the wrong origin.
            const float qx = r.get<float>(), qy = r.get<float>(), qz = r.get<float>(), qw = r.get<float>();
            x.ori = {qw, qx, qy, qz};
            // Ogre skeleton bone lengths historically omit the variable name.
            const size_t end = start + size + nameBytes;
            if (end > b.size() || r.p > end)
                throw std::runtime_error("invalid skeleton bone");
            if (end - r.p == 12)
                x.scale = {r.get<float>(), r.get<float>(), r.get<float>()};
            else if (end != r.p)
                throw std::runtime_error("unsupported bone layout");
            if (!out.emplace(handle, std::move(x)).second)
                throw std::runtime_error("duplicate bone handle");
        }
        else
        {
            r.need(size - 6);
            auto end = r.p + size - 6;
            if (id == 0x3000)
            {
                auto h = r.get<uint16_t>();
                auto parent = r.get<uint16_t>();
                out[h].parent = parent;
            }
            r.p = end;
        }
        if (out.size() > 4096)
            throw std::runtime_error("oversized skeleton");
    }
    return out;
}
void derive(uint16_t id, std::map<uint16_t, Bone> &bs, int depth = 0)
{
    auto &b = bs.at(id);
    if (b.state == 2)
        return;
    if (b.state == 1 || depth > 128)
        throw std::runtime_error("cyclic skeleton");
    b.state = 1;
    if (b.parent >= 0)
    {
        auto p = bs.find(static_cast<uint16_t>(b.parent));
        if (p == bs.end())
            throw std::runtime_error("missing parent bone");
        derive(p->first, bs, depth + 1);
        b.pos = add(p->second.pos, rotate(p->second.ori, mul(p->second.scale, b.pos)));
        b.ori = product(p->second.ori, b.ori);
        b.scale = mul(p->second.scale, b.scale);
    }
    b.state = 2;
}
// unweightedToRoot: chunk extraction gives an unweighted face to the unique
// skeleton root; the gib split skips it, as scripts/export_gib_payloads.py does.
std::vector<int> triangleOwners(const Sub &sub, const Model &model, const std::map<uint16_t, Bone> &bones,
                                bool unweightedToRoot = true)
{
    if (sub.operation != 4)
        throw std::runtime_error("unsupported primitive operation");
    if (sub.indices.size() % 3)
        throw std::runtime_error("incomplete triangle list");
    const auto &g = sub.shared ? model.geometry : sub.geometry;
    const auto &assignments = sub.shared ? model.assignments : sub.assignments;
    std::vector<std::map<uint16_t, float>> weights(g.count);
    for (auto a : assignments)
    {
        if (a.vertex >= g.count || !std::isfinite(a.weight) || a.weight < 0 || !bones.count(a.bone))
            throw std::runtime_error("invalid bone assignment vertex=" + std::to_string(a.vertex) + "/" +
                                     std::to_string(g.count) + " bone=" + std::to_string(a.bone) +
                                     " weight=" + std::to_string(a.weight));
        if (a.weight > 0)
            weights[a.vertex][a.bone] += a.weight;
    }
    int root = -1;
    for (const auto &[id, b] : bones)
        if (b.parent < 0)
        {
            if (root >= 0)
            {
                root = -1;
                break;
            }
            root = id;
        }
    std::vector<int> owners;
    for (size_t i = 0; i < sub.indices.size(); i += 3)
    {
        std::map<uint16_t, float> scores;
        for (size_t j = 0; j < 3; ++j)
        {
            auto vertex = sub.indices[i + j];
            if (vertex >= g.count)
                throw std::runtime_error("invalid triangle index");
            for (const auto &[id, weight] : weights[vertex])
                scores[id] += weight;
        }
        int owner = unweightedToRoot ? root : -1;
        float best = 0;
        // A triangle is emitted exactly once. Aggregate weights preserve seam
        // faces between rigid groups and avoid duplicating soft-skinned faces.
        // Ordered handles give deterministic ties. Unweighted faces use the
        // unique skeleton root when present, never fabricated debris.
        for (const auto &[id, score] : scores)
            if (score > best)
            {
                owner = id;
                best = score;
            }
        owners.push_back(owner);
    }
    return owners;
}
// Maps source model space into a piece's own frame: remove the bone's bind
// translation and rotation, then the piece-bounds centre.
struct Frame
{
    V pivot{};
    Q inverse{1, 0, 0, 0};
    V center{};
    bool rotate = false;
};
Frame boneFrame(const Bone &b)
{
    Frame f;
    f.pivot = b.pos;
    const float n = std::sqrt(b.ori[0] * b.ori[0] + b.ori[1] * b.ori[1] + b.ori[2] * b.ori[2] + b.ori[3] * b.ori[3]);
    if (!std::isfinite(n) || n < 1e-6f)
        throw std::runtime_error("degenerate bone orientation");
    f.inverse = {b.ori[0] / n, -b.ori[1] / n, -b.ori[2] / n, -b.ori[3] / n};
    // Identity binds keep exact source bytes for directions; anything else is
    // a real rotation the fragment's world matrix will apply again.
    f.rotate = std::abs(std::abs(f.inverse[0]) - 1.0f) > 1e-7f;
    return f;
}
V toFrame(const Frame &f, V p)
{
    for (int i = 0; i < 3; ++i)
        p[i] -= f.pivot[i];
    return f.rotate ? rotate(f.inverse, p) : p;
}
bool isDirection(uint16_t semantic)
{
    // VES_NORMAL, VES_BINORMAL, VES_TANGENT.
    return semantic == 4 || semantic == 8 || semantic == 9;
}
V position(const Geometry &g, uint32_t index)
{
    for (const auto &e : g.elements)
        if (e.semantic == 1)
        {
            const auto buffer = g.buffers.find(e.source);
            if (buffer == g.buffers.end() || e.type != 2 || static_cast<size_t>(e.offset) + 12 > buffer->second.stride)
                throw std::runtime_error("unsupported position format");
            if (index >= g.count)
                throw std::runtime_error("index outside vertex data");
            V p;
            std::memcpy(p.data(), buffer->second.data.data() + static_cast<size_t>(index) * buffer->second.stride + e.offset,
                        12);
            return p;
        }
    throw std::runtime_error("missing position stream");
}
Bytes emitGeometry(const Geometry &g, const std::vector<uint32_t> &vertices, const Frame &frame, V &lo, V &hi,
                   float &radius)
{
    Bytes out;
    put(out, static_cast<uint32_t>(vertices.size()));
    Bytes decl;
    bool hasPosition = false;
    for (auto e : g.elements)
    {
        if (e.semantic == 2 || e.semantic == 3)
            continue;
        Bytes d;
        put(d, e.source);
        put(d, e.type);
        put(d, e.semantic);
        put(d, e.offset);
        put(d, e.index);
        chunk(decl, 0x5110, d);
    }
    chunk(out, 0x5100, decl);
    for (const auto &[source, buf] : g.buffers)
    {
        Bytes values;
        const Element *pos = nullptr;
        std::vector<uint16_t> directions;
        bool used = false;
        for (const auto &e : g.elements)
            if (e.source == source && e.semantic != 2 && e.semantic != 3)
            {
                used = true;
                if (e.semantic == 1)
                {
                    if (e.type != 2 || static_cast<size_t>(e.offset) + 12 > buf.stride)
                        throw std::runtime_error("unsupported position format");
                    pos = &e;
                    hasPosition = true;
                }
                else if (frame.rotate && isDirection(e.semantic))
                {
                    // FLOAT3, or FLOAT4 tangents whose w (handedness) is kept.
                    if ((e.type != 2 && e.type != 3) || static_cast<size_t>(e.offset) + 12 > buf.stride)
                        throw std::runtime_error("unsupported direction format on rotated bone");
                    directions.push_back(e.offset);
                }
            }
        if (!used)
            continue;
        for (auto index : vertices)
        {
            if (index >= g.count)
                throw std::runtime_error("index outside vertex data");
            const size_t begin = static_cast<size_t>(index) * buf.stride;
            const size_t next = values.size();
            values.insert(values.end(), buf.data.begin() + begin, buf.data.begin() + begin + buf.stride);
            for (auto offset : directions)
            {
                V d;
                std::memcpy(d.data(), values.data() + next + offset, 12);
                d = rotate(frame.inverse, d);
                std::memcpy(values.data() + next + offset, d.data(), 12);
            }
            if (pos)
            {
                V p;
                std::memcpy(p.data(), values.data() + next + pos->offset, 12);
                p = toFrame(frame, p);
                float r2 = 0;
                for (int i = 0; i < 3; ++i)
                {
                    p[i] -= frame.center[i];
                    if (!std::isfinite(p[i]) || std::abs(p[i]) > 100000)
                        throw std::runtime_error("invalid vertex position");
                    lo[i] = std::min(lo[i], p[i]);
                    hi[i] = std::max(hi[i], p[i]);
                    r2 += p[i] * p[i];
                }
                radius = std::max(radius, std::sqrt(r2));
                std::memcpy(values.data() + next + pos->offset, p.data(), 12);
            }
        }
        Bytes d;
        put(d, source);
        put(d, buf.stride);
        chunk(d, 0x5210, values);
        chunk(out, 0x5200, d);
    }
    if (!hasPosition)
        throw std::runtime_error("missing position stream");
    return out;
}
} // namespace
unsigned StockFallbackKind(std::string_view seed)
{
    uint32_t hash = 2166136261u;
    std::string folded;
    for (unsigned char c : seed)
    {
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
        folded.push_back(static_cast<char>(c));
        hash = (hash ^ c) * 16777619u;
    }
    if (folded == "chunk1")
        return 1;
    if (folded == "chunk2")
        return 2;
    return 1 + hash % 2;
}
unsigned StockFallbackBatchKind(std::string_view resource)
{
    if (resource == "fallback/v1/stock_chunk1.mesh")
        return 1;
    if (resource == "fallback/v1/stock_chunk2.mesh")
        return 2;
    return 0;
}
Piece StockFallbackMesh(unsigned kind)
{
    if (kind != 1 && kind != 2)
        return {};
    const auto *vertices = kind == 1 ? kChunk1Vertices : kChunk2Vertices;
    const auto count = kind == 1 ? std::size(kChunk1Vertices) : std::size(kChunk2Vertices);
    Geometry g;
    g.count = static_cast<uint32_t>(count);
    g.elements = {{0, 2, 1, 0, 0}, {0, 2, 4, 12, 0}, {0, 2, 9, 24, 0}, {0, 1, 7, 36, 0}};
    Buffer buffer{44, {}};
    std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < count; ++i)
    {
        const auto &v = vertices[i];
        for (float value : {v.position.x, v.position.y, v.position.z, v.normal.x, v.normal.y, v.normal.z, v.tangent.x,
                            v.tangent.y, v.tangent.z, v.u, v.v})
            put(buffer.data, value);
        indices.push_back(i);
    }
    g.buffers.emplace(uint16_t{0}, std::move(buffer));
    V lo{1e30f, 1e30f, 1e30f}, hi{-1e30f, -1e30f, -1e30f};
    float radius = 0;
    Bytes sub;
    line(sub, "scarpmat2");
    put(sub, uint8_t{0});
    put(sub, g.count);
    put(sub, uint8_t{0});
    for (uint16_t i = 0; i < count; ++i)
        put(sub, i);
    chunk(sub, 0x5000, emitGeometry(g, indices, Frame{}, lo, hi, radius));
    Bytes body{0};
    chunk(body, 0x4000, sub);
    Bytes bounds;
    for (float v : lo)
        put(bounds, v);
    for (float v : hi)
        put(bounds, v);
    put(bounds, radius);
    chunk(body, 0x9000, bounds);
    Bytes out;
    put(out, uint16_t{0x1000});
    line(out, "[MeshSerializer_v1.8]");
    chunk(out, 0x3000, body);
    return {"stock_chunk" + std::to_string(kind), std::move(out), g.count / 3};
}
Piece CasingMesh(unsigned sides)
{
    if (sides < 6 || sides > 32)
        return {};
    // Unit-length shell along local +Z, centred on the origin: a rim and base
    // at z = -0.5, a straight body, a short shoulder and a neck to the mouth
    // at z = +0.5. Two submeshes so the brass and the darker rim, base and
    // open mouth take separate materials.
    constexpr float kRim = 0.225f, kBody = 0.2f, kNeck = 0.165f;
    constexpr float kBase = -0.5f, kRimTop = -0.44f, kShoulder = 0.36f, kNeckStart = 0.42f, kMouth = 0.5f;
    constexpr float kPi = 3.14159265358979f;
    struct Vertex
    {
        V p, n;
        float u, v;
    };
    auto ring = [&](unsigned i, float radius) {
        const float a = 2.0f * kPi * static_cast<float>(i % sides) / static_cast<float>(sides);
        return V{std::cos(a) * radius, std::sin(a) * radius, 0.0f};
    };
    auto at = [](V p, float z) { return V{p[0], p[1], z}; };
    auto norm = [](V a) {
        const float l = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        return l > 1e-9f ? V{a[0] / l, a[1] / l, a[2] / l} : V{0, 0, 1};
    };
    std::vector<Vertex> brass, rim;
    auto tri = [](std::vector<Vertex> &out, Vertex a, Vertex b, Vertex c) {
        out.push_back(a);
        out.push_back(b);
        out.push_back(c);
    };
    // A band between two rings, outward facing. Normals tilt with the slope
    // so the shoulder shades as a cone.
    auto band = [&](std::vector<Vertex> &out, float z0, float r0, float z1, float r1) {
        for (unsigned i = 0; i < sides; ++i)
        {
            const float u0 = static_cast<float>(i) / static_cast<float>(sides);
            const float u1 = static_cast<float>(i + 1) / static_cast<float>(sides);
            const V d0 = ring(i, 1.0f), d1 = ring(i + 1, 1.0f);
            const V n0 = norm({d0[0] * (z1 - z0), d0[1] * (z1 - z0), r0 - r1});
            const V n1 = norm({d1[0] * (z1 - z0), d1[1] * (z1 - z0), r0 - r1});
            const Vertex a0{at(ring(i, r0), z0), n0, u0, z0 + 0.5f}, a1{at(ring(i + 1, r0), z0), n1, u1, z0 + 0.5f};
            const Vertex b0{at(ring(i, r1), z1), n0, u0, z1 + 0.5f}, b1{at(ring(i + 1, r1), z1), n1, u1, z1 + 0.5f};
            tri(out, a0, a1, b1);
            tri(out, a0, b1, b0);
        }
    };
    // A flat ring between two radii at one z, facing +Z or -Z.
    auto annulus = [&](std::vector<Vertex> &out, float z, float inner, float outer, bool up) {
        const V n{0, 0, up ? 1.0f : -1.0f};
        for (unsigned i = 0; i < sides; ++i)
        {
            const V in0 = at(ring(i, inner), z), in1 = at(ring(i + 1, inner), z);
            const V out0 = at(ring(i, outer), z), out1 = at(ring(i + 1, outer), z);
            const Vertex vi0{in0, n, in0[0] + 0.5f, in0[1] + 0.5f}, vi1{in1, n, in1[0] + 0.5f, in1[1] + 0.5f};
            const Vertex vo0{out0, n, out0[0] + 0.5f, out0[1] + 0.5f}, vo1{out1, n, out1[0] + 0.5f, out1[1] + 0.5f};
            // A disc (inner radius 0) is a fan: its second triangle would
            // be degenerate.
            if (up)
            {
                tri(out, vi0, vo0, vo1);
                if (inner > 0.0f)
                    tri(out, vi0, vo1, vi1);
            }
            else
            {
                tri(out, vi0, vo1, vo0);
                if (inner > 0.0f)
                    tri(out, vi0, vi1, vo1);
            }
        }
    };
    band(brass, kRimTop, kBody, kShoulder, kBody);
    band(brass, kShoulder, kBody, kNeckStart, kNeck);
    band(brass, kNeckStart, kNeck, kMouth, kNeck);
    band(rim, kBase, kRim, kRimTop, kRim);
    annulus(rim, kRimTop, kBody, kRim, true);
    annulus(rim, kBase, 0.0f, kRim, false);
    annulus(rim, kMouth, 0.0f, kNeck, true);

    V lo{1e30f, 1e30f, 1e30f}, hi{-1e30f, -1e30f, -1e30f};
    float radius = 0;
    Bytes body{0};
    uint32_t triangles = 0;
    for (const auto &[material, vertices] :
         {std::pair<const char *, const std::vector<Vertex> *>{"openshim_casing_brass", &brass},
          std::pair<const char *, const std::vector<Vertex> *>{"openshim_casing_rim", &rim}})
    {
        Geometry g;
        g.count = static_cast<uint32_t>(vertices->size());
        // Position, normal, uv0: the gib cap declaration.
        g.elements = {{0, 2, 1, 0, 0}, {0, 2, 4, 12, 0}, {0, 1, 7, 24, 0}};
        Buffer buffer{32, {}};
        std::vector<uint32_t> indices;
        for (const auto &v : *vertices)
        {
            for (float value : {v.p[0], v.p[1], v.p[2], v.n[0], v.n[1], v.n[2], v.u, v.v})
                put(buffer.data, value);
            indices.push_back(static_cast<uint32_t>(indices.size()));
        }
        g.buffers.emplace(uint16_t{0}, std::move(buffer));
        Bytes sub;
        line(sub, material);
        put(sub, uint8_t{0});
        put(sub, g.count);
        put(sub, uint8_t{0});
        for (auto index : indices)
            put(sub, static_cast<uint16_t>(index));
        chunk(sub, 0x5000, emitGeometry(g, indices, Frame{}, lo, hi, radius));
        chunk(body, 0x4000, sub);
        triangles += g.count / 3;
    }
    Bytes bounds;
    for (float v : lo)
        put(bounds, v);
    for (float v : hi)
        put(bounds, v);
    put(bounds, radius);
    chunk(body, 0x9000, bounds);
    Bytes out;
    put(out, uint16_t{0x1000});
    line(out, "[MeshSerializer_v1.8]");
    chunk(out, 0x3000, body);
    return {"openshim_casing", std::move(out), triangles};
}
std::string SkeletonName(const Bytes &b)
{
    try
    {
        // Resource discovery only needs the link. Walk the structure without
        // copying vertex buffers so a cache hit stays cheap.
        return model(b, false).skeleton;
    }
    catch (...)
    {
        return {};
    }
}
bool FragmentOriginShift(const float right[3], const float up[3], const float front[3], const float center[3],
                         double out[3])
{
    out[0] = out[1] = out[2] = 0;
    // Ogre local -> sim local mirrors Z (see the proxy's render conversion).
    const double local[3] = {center[0], center[1], -static_cast<double>(center[2])};
    const float *basis[3] = {right, up, front};
    for (int column = 0; column < 3; ++column)
    {
        const double length = std::sqrt(static_cast<double>(basis[column][0]) * basis[column][0] +
                                        static_cast<double>(basis[column][1]) * basis[column][1] +
                                        static_cast<double>(basis[column][2]) * basis[column][2]);
        if (!std::isfinite(length) || length < 1e-6 || !std::isfinite(local[column]))
            return false;
        for (int axis = 0; axis < 3; ++axis)
            out[axis] += basis[column][axis] / length * local[column];
    }
    return std::isfinite(out[0]) && std::isfinite(out[1]) && std::isfinite(out[2]);
}
bool Extract(const Bytes &bytes, const Bytes &skeleton, std::vector<Piece> &pieces, std::string &error)
{
    pieces.clear();
    error.clear();
    try
    {
        if (bytes.size() > 64 * 1024 * 1024 || skeleton.size() > 16 * 1024 * 1024)
            throw std::runtime_error("oversized Ogre resource");
        auto m = model(bytes);
        auto bs = bones(skeleton);
        for (auto &[id, b] : bs)
            derive(id, bs);
        // Bucket each face once instead of rescanning every face for every
        // skeleton bone. Authored models can have hundreds of empty bones.
        std::vector<std::map<int, std::vector<uint32_t>>> faces;
        for (const auto &sub : m.subs)
        {
            const auto owners = triangleOwners(sub, m, bs);
            std::map<int, std::vector<uint32_t>> groups;
            for (size_t i = 0; i < owners.size(); ++i)
                if (owners[i] >= 0)
                {
                    auto &indices = groups[owners[i]];
                    indices.insert(indices.end(), sub.indices.begin() + i * 3, sub.indices.begin() + i * 3 + 3);
                }
            faces.push_back(std::move(groups));
        }
        for (const auto &[id, b] : bs)
        {
            Bytes body{0};
            uint32_t triangles = 0;
            V lo{1e30f, 1e30f, 1e30f}, hi{-1e30f, -1e30f, -1e30f};
            float radius = 0;
            Frame frame = boneFrame(b);
            // Centre the piece on its own bounds in the bone frame. A bone
            // pivot can sit far from its geometry (many exporters leave every
            // vertex-group bone at the model origin), and the engine spins a
            // fragment about its origin: without this it orbits empty space.
            bool any = false;
            for (size_t s = 0; s < m.subs.size(); ++s)
            {
                const auto group = faces[s].find(id);
                if (group == faces[s].end())
                    continue;
                const auto &g = m.subs[s].shared ? m.geometry : m.subs[s].geometry;
                for (auto index : group->second)
                {
                    const V p = toFrame(frame, position(g, index));
                    for (int i = 0; i < 3; ++i)
                    {
                        lo[i] = std::min(lo[i], p[i]);
                        hi[i] = std::max(hi[i], p[i]);
                    }
                    any = true;
                }
            }
            if (!any)
                continue;
            for (int i = 0; i < 3; ++i)
            {
                frame.center[i] = (lo[i] + hi[i]) * 0.5f;
                if (!std::isfinite(frame.center[i]) || std::abs(frame.center[i]) > 100000)
                    throw std::runtime_error("invalid piece centre");
            }
            lo = {1e30f, 1e30f, 1e30f};
            hi = {-1e30f, -1e30f, -1e30f};
            for (size_t s = 0; s < m.subs.size(); ++s)
            {
                const auto &sub = m.subs[s];
                const auto &g = sub.shared ? m.geometry : sub.geometry;
                const auto group = faces[s].find(id);
                if (group == faces[s].end())
                    continue;
                const auto &selected = group->second;
                const std::set<uint32_t> used(selected.begin(), selected.end());
                std::vector<uint32_t> vertices(used.begin(), used.end());
                std::map<uint32_t, uint32_t> remap;
                for (uint32_t i = 0; i < vertices.size(); ++i)
                    remap[vertices[i]] = i;
                Bytes data;
                line(data, sub.material);
                put(data, uint8_t{0});
                put(data, static_cast<uint32_t>(selected.size()));
                put(data, uint8_t{1});
                for (auto index : selected)
                    put(data, remap.at(index));
                chunk(data, 0x5000, emitGeometry(g, vertices, frame, lo, hi, radius));
                chunk(body, 0x4000, data);
                triangles += static_cast<uint32_t>(selected.size() / 3);
            }
            if (!triangles)
                continue;
            Bytes bounds;
            for (float v : lo)
                put(bounds, v);
            for (float v : hi)
                put(bounds, v);
            put(bounds, radius);
            chunk(body, 0x9000, bounds);
            Bytes out;
            put(out, uint16_t{0x1000});
            line(out, "[MeshSerializer_v1.8]");
            chunk(out, 0x3000, body);
            pieces.push_back({b.name, std::move(out), triangles, {frame.center[0], frame.center[1], frame.center[2]}});
        }
        if (pieces.empty())
            throw std::runtime_error("no complete bone-group faces");
        return true;
    }
    catch (const std::exception &e)
    {
        pieces.clear();
        error = e.what();
        return false;
    }
}
// ---------------------------------------------------------------------------
// Skinned gibs: the runtime twin of scripts/export_gib_payloads.py. Follow
// that script when changing the split; the two must agree on which faces
// form which gib.
namespace
{
V sub3(V a, V b)
{
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}
V scale3(V a, float s)
{
    return {a[0] * s, a[1] * s, a[2] * s};
}
V cross3(V a, V b)
{
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}
float dot3(V a, V b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
V normalize3(V a)
{
    const float length = std::sqrt(dot3(a, a));
    if (!(length >= 1e-12f))
        return {0, 1, 0};
    return scale3(a, 1.0f / length);
}
// Directed boundary edges (welded ids) chained into loops, tolerant of junk:
// the same walk as the script's _boundary_loops, open chains of three or more
// points included.
std::vector<std::vector<int>> boundaryLoops(const std::vector<std::pair<int, int>> &edges)
{
    std::map<int, std::vector<int>> outgoing;
    for (const auto &[a, b] : edges)
        outgoing[a].push_back(b);
    std::set<std::pair<int, int>> used;
    std::vector<std::vector<int>> loops;
    for (const auto &[a, b] : edges)
    {
        if (used.count({a, b}))
            continue;
        std::vector<int> loop{a};
        used.insert({a, b});
        int current = b;
        size_t guard = 0;
        while (current != a && guard < edges.size() + 1)
        {
            loop.push_back(current);
            int next = -1;
            bool found = false;
            const auto out = outgoing.find(current);
            if (out != outgoing.end())
                for (int candidate : out->second)
                    if (!used.count({current, candidate}))
                    {
                        next = candidate;
                        found = true;
                        break;
                    }
            if (!found)
                break;
            used.insert({current, next});
            current = next;
            ++guard;
        }
        if (loop.size() >= 3)
            loops.push_back(std::move(loop));
    }
    return loops;
}
// re.sub(r"[^A-Za-z0-9_]+", "_", key).lower(), bounded for the cache.
std::string gibPieceName(const std::string &key)
{
    std::string out = "gib_";
    bool underscoreRun = false;
    for (unsigned char c : key.substr(0, 60))
    {
        const bool keep = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        if (keep)
        {
            out.push_back(static_cast<char>(c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c));
            underscoreRun = false;
        }
        else if (!underscoreRun)
        {
            out.push_back('_');
            underscoreRun = true;
        }
    }
    return out;
}
struct GibFace
{
    size_t sub;
    size_t face;
};
struct CapTri
{
    V a, b, c, normal;
};
} // namespace
bool ExtractGibs(const Bytes &bytes, const Bytes &skeleton, const GibOptions &options, std::vector<GibPiece> &gibs,
                 std::string &error)
{
    gibs.clear();
    error.clear();
    try
    {
        if (bytes.size() > 64 * 1024 * 1024 || skeleton.size() > 16 * 1024 * 1024)
            throw std::runtime_error("oversized Ogre resource");
        if (!std::isfinite(options.minFaceFraction) || options.minFaceFraction < 0 || options.minFaceFraction > 1)
            throw std::runtime_error("invalid gib face fraction");
        const auto flags = std::regex::ECMAScript | std::regex::icase;
        // An empty pattern matches nothing.
        const auto pattern = [&](const std::string &text) { return std::regex(text.empty() ? "$^" : text, flags); };
        const std::regex keep = pattern(options.keepPattern);
        const std::regex drop = pattern(options.dropPattern);
        const std::regex weapon = pattern(options.weaponMaterialPattern);
        const auto m = model(bytes);
        auto bs = bones(skeleton);
        for (auto &[id, b] : bs)
            derive(id, bs);
        // derive() already rejected cycles and missing parents.
        const auto depth = [&](uint16_t id) {
            int d = 0;
            for (int p = bs.at(id).parent; p >= 0; p = bs.at(static_cast<uint16_t>(p)).parent)
                ++d;
            return d;
        };

        // 1. Dominant bone per face; weapon submeshes are counted apart.
        std::vector<std::vector<int>> owners;
        std::vector<bool> weaponSub;
        std::map<uint16_t, uint32_t> counts;
        std::vector<std::pair<uint16_t, uint32_t>> weaponCounts; // first-seen order breaks ties
        uint32_t totalFaces = 0;
        for (const auto &sub : m.subs)
        {
            owners.push_back(triangleOwners(sub, m, bs, false));
            weaponSub.push_back(std::regex_search(sub.material, weapon));
            for (int owner : owners.back())
            {
                if (owner < 0)
                    continue;
                ++totalFaces;
                const auto bone = static_cast<uint16_t>(owner);
                if (!weaponSub.back())
                {
                    ++counts[bone];
                    continue;
                }
                auto found = std::find_if(weaponCounts.begin(), weaponCounts.end(),
                                          [bone](const std::pair<uint16_t, uint32_t> &entry) {
                                              return entry.first == bone;
                                          });
                if (found == weaponCounts.end())
                    weaponCounts.push_back({bone, 1});
                else
                    ++found->second;
            }
        }
        if (!totalFaces)
            throw std::runtime_error("no skinned faces");

        // 2. Roll small bones into their parent, deepest first, so fingers
        //    fold into the hand before the (now heavier) hand is judged. A
        //    root never merges; the keep pattern always stays its own gib.
        const auto minFaces =
            std::max<uint32_t>(1, static_cast<uint32_t>(static_cast<double>(totalFaces) * options.minFaceFraction));
        std::map<uint16_t, uint16_t> target;
        std::vector<uint16_t> order;
        for (const auto &[id, b] : bs)
        {
            target[id] = id;
            order.push_back(id);
        }
        std::stable_sort(order.begin(), order.end(), [&](uint16_t a, uint16_t b) { return depth(a) > depth(b); });
        for (uint16_t id : order)
        {
            const auto &bone = bs.at(id);
            if (!counts[id] || bone.parent < 0 || std::regex_search(bone.name, keep))
                continue;
            if (!std::regex_search(bone.name, drop) && counts[id] >= minFaces)
                continue;
            const auto parent = static_cast<uint16_t>(bone.parent);
            counts[parent] += counts[id];
            counts[id] = 0;
            for (auto &[source, mapped] : target)
                if (mapped == id)
                    mapped = parent;
        }
        uint16_t weaponBone = 0;
        uint32_t weaponBest = 0;
        for (const auto &[bone, count] : weaponCounts)
            if (count > weaponBest)
            {
                weaponBone = bone;
                weaponBest = count;
            }

        // 3. Group faces into pieces keyed like the script (gib bone name, or
        //    "weapon"); std::map gives the script's sorted output order.
        static const std::string kWeaponKey = "weapon";
        std::map<std::string, std::vector<GibFace>> pieceFaces;
        std::map<std::string, uint16_t> pieceBone;
        for (size_t s = 0; s < m.subs.size(); ++s)
            for (size_t f = 0; f < owners[s].size(); ++f)
            {
                if (owners[s][f] < 0)
                    continue;
                const uint16_t bone = weaponSub[s] ? weaponBone : target.at(static_cast<uint16_t>(owners[s][f]));
                const std::string &key = weaponSub[s] ? kWeaponKey : bs.at(bone).name;
                pieceFaces[key].push_back({s, f});
                pieceBone[key] = bone;
            }
        std::map<std::string, int> pieceIds;
        for (const auto &entry : pieceFaces)
            pieceIds.emplace(entry.first, static_cast<int>(pieceIds.size()));
        std::vector<std::vector<int>> facePiece(m.subs.size());
        for (size_t s = 0; s < m.subs.size(); ++s)
            facePiece[s].assign(owners[s].size(), -1);
        for (const auto &[key, faces] : pieceFaces)
            for (const auto &face : faces)
                facePiece[face.sub][face.face] = pieceIds.at(key);

        // 4. Position-welded topology: a cut is an edge shared by faces of
        //    more than one body piece, wherever the exporter split vertices.
        std::map<std::array<long long, 3>, int> weldLookup;
        std::vector<V> weldPosition;
        std::map<const Geometry *, std::vector<int>> weldCache;
        for (const auto &sub : m.subs)
        {
            const Geometry &g = sub.shared ? m.geometry : sub.geometry;
            if (weldCache.count(&g))
                continue;
            std::vector<int> ids(g.count);
            for (uint32_t v = 0; v < g.count; ++v)
            {
                const V p = position(g, v);
                const std::array<long long, 3> key{std::llround(static_cast<double>(p[0]) / 1e-4),
                                                   std::llround(static_cast<double>(p[1]) / 1e-4),
                                                   std::llround(static_cast<double>(p[2]) / 1e-4)};
                const auto inserted = weldLookup.emplace(key, static_cast<int>(weldLookup.size()));
                if (inserted.second)
                    weldPosition.push_back(p);
                ids[v] = inserted.first->second;
            }
            weldCache.emplace(&g, std::move(ids));
        }
        const auto faceWelds = [&](size_t s, size_t f) {
            const Sub &sub = m.subs[s];
            const auto &ids = weldCache.at(sub.shared ? &m.geometry : &sub.geometry);
            return std::array<int, 3>{ids.at(sub.indices[f * 3]), ids.at(sub.indices[f * 3 + 1]),
                                      ids.at(sub.indices[f * 3 + 2])};
        };
        std::map<std::pair<int, int>, std::vector<int>> edgePieces;
        for (size_t s = 0; s < m.subs.size(); ++s)
        {
            if (weaponSub[s])
                continue;
            for (size_t f = 0; f < owners[s].size(); ++f)
            {
                if (facePiece[s][f] < 0)
                    continue;
                const auto w = faceWelds(s, f);
                for (int e = 0; e < 3; ++e)
                {
                    const int u = w[e], v = w[(e + 1) % 3];
                    auto &list = edgePieces[{std::min(u, v), std::max(u, v)}];
                    if (std::find(list.begin(), list.end(), facePiece[s][f]) == list.end())
                        list.push_back(facePiece[s][f]);
                }
            }
        }

        std::set<std::string> usedNames;
        for (const auto &[key, faces] : pieceFaces)
        {
            const bool isWeapon = key == kWeaponKey;
            const uint16_t boneId = pieceBone.at(key);
            const Bone &bone = bs.at(boneId);
            Frame frame = boneFrame(bone);

            // Model-space centroid of every face corner (duplicates counted,
            // as the script does): caps face away from it.
            V centroid{};
            size_t corners = 0;
            V lo{1e30f, 1e30f, 1e30f}, hi{-1e30f, -1e30f, -1e30f};
            std::map<size_t, std::vector<uint32_t>> bySub;
            for (const auto &face : faces)
            {
                const Sub &sub = m.subs[face.sub];
                const Geometry &g = sub.shared ? m.geometry : sub.geometry;
                auto &indices = bySub[face.sub];
                for (size_t k = 0; k < 3; ++k)
                {
                    const uint32_t index = sub.indices[face.face * 3 + k];
                    indices.push_back(index);
                    const V p = position(g, index);
                    centroid = add(centroid, p);
                    ++corners;
                    const V local = toFrame(frame, p);
                    for (int i = 0; i < 3; ++i)
                    {
                        lo[i] = std::min(lo[i], local[i]);
                        hi[i] = std::max(hi[i], local[i]);
                    }
                }
            }
            centroid = scale3(centroid, 1.0f / static_cast<float>(corners));
            for (int i = 0; i < 3; ++i)
            {
                frame.center[i] = (lo[i] + hi[i]) * 0.5f;
                if (!std::isfinite(frame.center[i]) || std::abs(frame.center[i]) > 100000)
                    throw std::runtime_error("invalid gib centre");
            }

            // 5. Fan caps over every cut loop, built in model space.
            std::vector<CapTri> caps;
            if (!isWeapon && options.caps)
            {
                std::vector<std::pair<int, int>> cutEdges;
                std::set<std::pair<int, int>> seen;
                for (const auto &face : faces)
                {
                    const auto w = faceWelds(face.sub, face.face);
                    for (int e = 0; e < 3; ++e)
                    {
                        const int u = w[e], v = w[(e + 1) % 3];
                        // Reversed, so the cap winds opposite to the skin it closes.
                        if (edgePieces.at({std::min(u, v), std::max(u, v)}).size() > 1 && seen.insert({v, u}).second)
                            cutEdges.push_back({v, u});
                    }
                }
                for (const auto &loop : boundaryLoops(cutEdges))
                {
                    std::vector<V> points;
                    for (int w : loop)
                        points.push_back(weldPosition.at(static_cast<size_t>(w)));
                    V center{};
                    for (const auto &p : points)
                        center = add(center, p);
                    center = scale3(center, 1.0f / static_cast<float>(points.size()));
                    V newell{};
                    for (size_t i = 0; i < points.size(); ++i)
                    {
                        const V p = points[i], q = points[(i + 1) % points.size()];
                        newell = add(newell, V{(p[1] - q[1]) * (p[2] + q[2]), (p[2] - q[2]) * (p[0] + q[0]),
                                               (p[0] - q[0]) * (p[1] + q[1])});
                    }
                    V normal = normalize3(newell);
                    if (dot3(normal, sub3(center, centroid)) < 0)
                    {
                        normal = scale3(normal, -1.0f);
                        std::reverse(points.begin(), points.end());
                    }
                    for (size_t i = 0; i < points.size(); ++i)
                    {
                        V p0 = points[i], p1 = points[(i + 1) % points.size()];
                        if (dot3(cross3(sub3(p0, center), sub3(p1, center)), normal) < 0)
                            std::swap(p0, p1);
                        caps.push_back({center, p0, p1, normal});
                    }
                }
                if (caps.size() > 1000000)
                    throw std::runtime_error("oversized gib cap");
            }

            // 6. Serialize in the bone frame, centred on the piece bounds,
            //    exactly as Extract writes a chunk piece.
            Bytes body{0};
            uint32_t triangles = 0;
            float radius = 0;
            lo = {1e30f, 1e30f, 1e30f};
            hi = {-1e30f, -1e30f, -1e30f};
            for (const auto &[s, selected] : bySub)
            {
                const Sub &sub = m.subs[s];
                const Geometry &g = sub.shared ? m.geometry : sub.geometry;
                const std::set<uint32_t> used(selected.begin(), selected.end());
                std::vector<uint32_t> vertices(used.begin(), used.end());
                std::map<uint32_t, uint32_t> remap;
                for (uint32_t i = 0; i < vertices.size(); ++i)
                    remap[vertices[i]] = i;
                Bytes data;
                line(data, sub.material);
                put(data, uint8_t{0});
                put(data, static_cast<uint32_t>(selected.size()));
                put(data, uint8_t{1});
                for (auto index : selected)
                    put(data, remap.at(index));
                chunk(data, 0x5000, emitGeometry(g, vertices, frame, lo, hi, radius));
                chunk(body, 0x4000, data);
                triangles += static_cast<uint32_t>(selected.size() / 3);
            }
            if (!caps.empty())
            {
                // Its own submesh and declaration (position, normal, uv0).
                // Planar UVs in each cap's plane so a flesh texture tiles
                // evenly; positions and normals go through the piece frame.
                Geometry g;
                g.count = static_cast<uint32_t>(caps.size() * 3);
                g.elements = {{0, 2, 1, 0, 0}, {0, 2, 4, 12, 0}, {0, 1, 7, 24, 0}};
                Buffer buffer{32, {}};
                std::vector<uint32_t> indices;
                for (const auto &tri : caps)
                {
                    const V tangent =
                        normalize3(cross3(tri.normal, std::abs(tri.normal[1]) < 0.9f ? V{0, 1, 0} : V{1, 0, 0}));
                    const V bitangent = cross3(tri.normal, tangent);
                    for (const V &p : {tri.a, tri.b, tri.c})
                    {
                        for (float value : {p[0], p[1], p[2], tri.normal[0], tri.normal[1], tri.normal[2],
                                            dot3(p, tangent) * options.capUvScale,
                                            dot3(p, bitangent) * options.capUvScale})
                            put(buffer.data, value);
                        indices.push_back(static_cast<uint32_t>(indices.size()));
                    }
                }
                g.buffers.emplace(uint16_t{0}, std::move(buffer));
                Bytes data;
                line(data, options.capMaterial);
                put(data, uint8_t{0});
                put(data, static_cast<uint32_t>(indices.size()));
                put(data, uint8_t{1});
                for (auto index : indices)
                    put(data, index);
                chunk(data, 0x5000, emitGeometry(g, indices, frame, lo, hi, radius));
                chunk(body, 0x4000, data);
                triangles += static_cast<uint32_t>(caps.size());
            }
            Bytes bounds;
            for (float v : lo)
                put(bounds, v);
            for (float v : hi)
                put(bounds, v);
            put(bounds, radius);
            chunk(body, 0x9000, bounds);
            Bytes out;
            put(out, uint16_t{0x1000});
            line(out, "[MeshSerializer_v1.8]");
            chunk(out, 0x3000, body);

            std::string name = gibPieceName(key);
            for (int suffix = 2; !usedNames.insert(name).second; ++suffix)
                name = gibPieceName(key) + "_" + std::to_string(suffix);
            GibPiece gib;
            gib.piece.name = name;
            gib.piece.mesh = std::move(out);
            gib.piece.triangles = triangles;
            for (int i = 0; i < 3; ++i)
                gib.piece.center[i] = frame.center[i];
            gib.bone = boneId;
            gib.boneName = bone.name;
            gib.radius = radius;
            gib.capTriangles = static_cast<uint32_t>(caps.size());
            gib.weapon = isWeapon;
            gibs.push_back(std::move(gib));
        }
        if (gibs.empty())
            throw std::runtime_error("no gib pieces");
        return true;
    }
    catch (const std::exception &e)
    {
        gibs.clear();
        error = e.what();
        return false;
    }
}
} // namespace BZROpenShim::NativeChunks
