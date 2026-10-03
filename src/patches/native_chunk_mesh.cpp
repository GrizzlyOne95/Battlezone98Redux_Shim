#include "native_chunk_mesh.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <map>
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
Geometry geometry(Reader r)
{
    Geometry g;
    g.count = r.get<uint32_t>();
    if (g.count > 1000000)
        throw std::runtime_error("oversized vertex count");
    while (r.p < r.end)
    {
        uint16_t id;
        auto c = r.chunk(id);
        if (id == 0x5100)
            while (c.p < c.end)
            {
                uint16_t eid;
                auto e = c.chunk(eid);
                if (eid == 0x5110)
                    g.elements.push_back({e.get<uint16_t>(), e.get<uint16_t>(), e.get<uint16_t>(), e.get<uint16_t>(),
                                          e.get<uint16_t>()});
            }
        if (id == 0x5200)
        {
            auto source = c.get<uint16_t>();
            auto stride = c.get<uint16_t>();
            uint16_t did;
            auto d = c.chunk(did);
            if (did != 0x5210 || stride == 0 || stride > 4096)
                throw std::runtime_error("invalid vertex buffer");
            const size_t n = static_cast<size_t>(g.count) * stride;
            d.need(n);
            g.buffers[source] = {stride, Bytes(d.b.begin() + d.p, d.b.begin() + d.p + n)};
        }
    }
    return g;
}
Assignment assignment(Reader c)
{
    return {c.get<uint32_t>(), c.get<uint16_t>(), c.get<float>()};
}
Model model(const Bytes &b)
{
    auto r = header(b, true);
    uint16_t id;
    auto root = r.chunk(id);
    if (id != 0x3000)
        throw std::runtime_error("missing Ogre mesh");
    root.get<uint8_t>();
    Model m;
    while (root.p < root.end)
    {
        auto c = root.chunk(id);
        if (id == 0x5000)
            m.geometry = geometry(c);
        if (id == 0x6000)
            m.skeleton = c.line();
        if (id == 0x7000)
            m.assignments.push_back(assignment(c));
        if (id == 0x4000)
        {
            Sub s;
            s.material = c.line();
            s.shared = c.get<uint8_t>() != 0;
            auto count = c.get<uint32_t>();
            bool wide = c.get<uint8_t>() != 0;
            if (count > 3000000)
                throw std::runtime_error("oversized index count");
            c.need(static_cast<size_t>(count) * (wide ? 4 : 2));
            for (uint32_t i = 0; i < count; ++i)
                s.indices.push_back(wide ? c.get<uint32_t>() : c.get<uint16_t>());
            while (c.p < c.end)
            {
                uint16_t sid;
                auto d = c.chunk(sid);
                if (sid == 0x5000)
                    s.geometry = geometry(d);
                if (sid == 0x4100)
                    s.assignments.push_back(assignment(d));
                if (sid == 0x4010)
                    s.operation = d.get<uint16_t>();
            }
            m.subs.push_back(std::move(s));
            if (m.subs.size() > 1024)
                throw std::runtime_error("oversized submesh count");
        }
    }
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
std::vector<int> triangleOwners(const Sub &sub, const Model &model, const std::map<uint16_t, Bone> &bones)
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
            throw std::runtime_error("invalid bone assignment");
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
        int owner = root;
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
Bytes emitGeometry(const Geometry &g, const std::vector<uint32_t> &vertices, V pivot, V &lo, V &hi, float &radius)
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
            if (pos)
            {
                V p;
                std::memcpy(p.data(), values.data() + next + pos->offset, 12);
                float r2 = 0;
                for (int i = 0; i < 3; ++i)
                {
                    p[i] -= pivot[i];
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
    chunk(sub, 0x5000, emitGeometry(g, indices, V{}, lo, hi, radius));
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
std::string SkeletonName(const Bytes &b)
{
    try
    {
        // Resource discovery only needs the link. Skip serialized geometry
        // here so a cache hit does not copy and parse all vertex buffers.
        auto r = header(b, true);
        uint16_t id;
        auto root = r.chunk(id);
        if (id != 0x3000)
            return {};
        root.get<uint8_t>();
        std::string name;
        while (root.p < root.end)
        {
            auto c = root.chunk(id);
            if (id == 0x6000)
                name = c.line();
        }
        return name;
    }
    catch (...)
    {
        return {};
    }
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
                chunk(data, 0x5000, emitGeometry(g, vertices, b.pos, lo, hi, radius));
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
            pieces.push_back({b.name, std::move(out), triangles});
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
} // namespace BZROpenShim::NativeChunks
