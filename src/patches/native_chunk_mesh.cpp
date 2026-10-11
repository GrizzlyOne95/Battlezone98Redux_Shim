#include "native_chunk_mesh.h"
#include "native_chunk_prune.h"
#include <algorithm>
#include <array>
#ifdef OPENSHIM_NATIVE_CHUNK_PHASES
#include <chrono>
#endif
#include <cmath>
#include <cstring>
#include <map>
#include <optional>
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
    // Per-vertex (bone, summed weight) lists, bones ascending, in CSR form.
    // Equal-bone weights are summed in assignment order, exactly as the old
    // per-vertex std::map did, so the float totals are bit-identical.
    struct Influence
    {
        uint16_t bone;
        float weight;
    };
    std::vector<uint8_t> knownBone(bones.empty() ? 0 : static_cast<size_t>(bones.rbegin()->first) + 1, 0);
    for (const auto &entry : bones)
        knownBone[entry.first] = 1;
    std::vector<uint32_t> start(static_cast<size_t>(g.count) + 1, 0);
    for (const auto &a : assignments)
    {
        if (a.vertex >= g.count || !std::isfinite(a.weight) || a.weight < 0 || a.bone >= knownBone.size() ||
            !knownBone[a.bone])
            throw std::runtime_error("invalid bone assignment vertex=" + std::to_string(a.vertex) + "/" +
                                     std::to_string(g.count) + " bone=" + std::to_string(a.bone) +
                                     " weight=" + std::to_string(a.weight));
        if (a.weight > 0)
            ++start[a.vertex + 1];
    }
    for (size_t v = 0; v < g.count; ++v)
        start[v + 1] += start[v];
    std::vector<Influence> raw(start[g.count]);
    {
        std::vector<uint32_t> fill(start.begin(), start.end() - 1);
        for (const auto &a : assignments)
            if (a.weight > 0)
                raw[fill[a.vertex]++] = {a.bone, a.weight};
    }
    std::vector<Influence> merged;
    merged.reserve(raw.size());
    std::vector<uint32_t> first(static_cast<size_t>(g.count) + 1, 0);
    for (uint32_t v = 0; v < g.count; ++v)
    {
        const size_t begin = start[v], end = start[v + 1];
        // Stable insertion sort by bone: ties keep assignment order.
        for (size_t i = begin + 1; i < end; ++i)
        {
            const Influence x = raw[i];
            size_t j = i;
            for (; j > begin && raw[j - 1].bone > x.bone; --j)
                raw[j] = raw[j - 1];
            raw[j] = x;
        }
        for (size_t i = begin; i < end; ++i)
        {
            if (i > begin && raw[i].bone == raw[i - 1].bone)
                merged.back().weight += raw[i].weight;
            else
                merged.push_back({raw[i].bone, 0.0f + raw[i].weight});
        }
        first[v + 1] = static_cast<uint32_t>(merged.size());
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
    owners.reserve(sub.indices.size() / 3);
    std::vector<uint16_t> candidates;
    for (size_t i = 0; i < sub.indices.size(); i += 3)
    {
        const uint32_t vertex[3] = {sub.indices[i], sub.indices[i + 1], sub.indices[i + 2]};
        candidates.clear();
        for (size_t j = 0; j < 3; ++j)
        {
            if (vertex[j] >= g.count)
                throw std::runtime_error("invalid triangle index");
            for (uint32_t k = first[vertex[j]]; k < first[vertex[j] + 1]; ++k)
                candidates.push_back(merged[k].bone);
        }
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        int owner = unweightedToRoot ? root : -1;
        float best = 0;
        // A triangle is emitted exactly once. Aggregate weights preserve seam
        // faces between rigid groups and avoid duplicating soft-skinned faces.
        // Ascending handles give deterministic ties. Unweighted faces use the
        // unique skeleton root when present, never fabricated debris.
        for (const uint16_t id : candidates)
        {
            float score = 0;
            for (size_t j = 0; j < 3; ++j)
                for (uint32_t k = first[vertex[j]]; k < first[vertex[j] + 1]; ++k)
                    if (merged[k].bone == id)
                    {
                        score += merged[k].weight;
                        break;
                    }
            if (score > best)
            {
                owner = id;
                best = score;
            }
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
// position() with the element lookup done once: for loops over many vertices of
// one geometry. Construction throws exactly what position() would for a
// non-empty geometry; operator() checks the index like position().
struct PositionReader
{
    const uint8_t *data;
    size_t stride;
    size_t offset;
    uint32_t count;
    explicit PositionReader(const Geometry &g) : data(nullptr), stride(0), offset(0), count(g.count)
    {
        for (const auto &e : g.elements)
            if (e.semantic == 1)
            {
                const auto buffer = g.buffers.find(e.source);
                if (buffer == g.buffers.end() || e.type != 2 ||
                    static_cast<size_t>(e.offset) + 12 > buffer->second.stride)
                    throw std::runtime_error("unsupported position format");
                data = buffer->second.data.data();
                stride = buffer->second.stride;
                offset = e.offset;
                return;
            }
        throw std::runtime_error("missing position stream");
    }
    V operator()(uint32_t index) const
    {
        if (index >= count)
            throw std::runtime_error("index outside vertex data");
        V p;
        std::memcpy(p.data(), data + static_cast<size_t>(index) * stride + offset, 12);
        return p;
    }
};
// Chunks written in place: open, append the body, close to patch the size
// (same bytes as chunk(), without copying the body into every enclosing level).
size_t openChunk(Bytes &b, uint16_t id)
{
    const size_t start = b.size();
    put(b, id);
    put(b, uint32_t{0});
    return start;
}
void closeChunk(Bytes &b, size_t start)
{
    const auto size = static_cast<uint32_t>(b.size() - start);
    std::memcpy(b.data() + start + 2, &size, sizeof(size));
}
// Appends the geometry chunk body (vertex count, declaration, buffers).
void appendGeometry(Bytes &out, const Geometry &g, const std::vector<uint32_t> &vertices, const Frame &frame, V &lo,
                    V &hi, float &radius)
{
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
        const size_t bufferChunk = openChunk(out, 0x5200);
        put(out, source);
        put(out, buf.stride);
        const size_t dataChunk = openChunk(out, 0x5210);
        const size_t valuesAt = out.size();
        out.resize(valuesAt + vertices.size() * buf.stride);
        uint8_t *values = out.data() + valuesAt;
        size_t next = 0;
        // Bounds in locals for the loop (a throw discards the piece anyway).
        V loLocal = lo, hiLocal = hi;
        float radiusLocal = radius;
        for (auto index : vertices)
        {
            if (index >= g.count)
                throw std::runtime_error("index outside vertex data");
            const size_t begin = static_cast<size_t>(index) * buf.stride;
            std::memcpy(values + next, buf.data.data() + begin, buf.stride);
            for (auto offset : directions)
            {
                V d;
                std::memcpy(d.data(), values + next + offset, 12);
                d = rotate(frame.inverse, d);
                std::memcpy(values + next + offset, d.data(), 12);
            }
            if (pos)
            {
                V p;
                std::memcpy(p.data(), values + next + pos->offset, 12);
                p = toFrame(frame, p);
                float r2 = 0;
                for (int i = 0; i < 3; ++i)
                {
                    p[i] -= frame.center[i];
                    if (!std::isfinite(p[i]) || std::abs(p[i]) > 100000)
                        throw std::runtime_error("invalid vertex position");
                    loLocal[i] = std::min(loLocal[i], p[i]);
                    hiLocal[i] = std::max(hiLocal[i], p[i]);
                    r2 += p[i] * p[i];
                }
                radiusLocal = std::max(radiusLocal, std::sqrt(r2));
                std::memcpy(values + next + pos->offset, p.data(), 12);
            }
            next += buf.stride;
        }
        lo = loLocal;
        hi = hiLocal;
        radius = radiusLocal;
        closeChunk(out, dataChunk);
        closeChunk(out, bufferChunk);
    }
    if (!hasPosition)
        throw std::runtime_error("missing position stream");
}
Bytes emitGeometry(const Geometry &g, const std::vector<uint32_t> &vertices, const Frame &frame, V &lo, V &hi,
                   float &radius)
{
    Bytes out;
    appendGeometry(out, g, vertices, frame, lo, hi, radius);
    return out;
}
} // namespace
#ifdef OPENSHIM_NATIVE_CHUNK_PHASES
// Bench-only phase accumulators (milliseconds); compiled out of the DLL.
double g_gibPhaseMs[11] = {};
namespace
{
struct PhaseClock
{
    std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
    void mark(int phase)
    {
        const auto now = std::chrono::steady_clock::now();
        g_gibPhaseMs[phase] += std::chrono::duration<double, std::milli>(now - last).count();
        last = now;
    }
};
} // namespace
#define GIB_PHASE_BEGIN PhaseClock phaseClock
#define GIB_PHASE(n) phaseClock.mark(n)
// Cap outcomes: rings at full / 0.6 / 0.3 strength, fan (not eligible), fan (folded).
double g_gibCapStats[8] = {};
#define CAP_STAT(i) (g_gibCapStats[i] += 1.0)
#else
#define CAP_STAT(i) ((void)0)
#define GIB_PHASE_BEGIN ((void)0)
#define GIB_PHASE(n) ((void)0)
#endif
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
    if (resource == OPENSHIM_CHUNK_CACHE_FALLBACK_DIR "stock_chunk1.mesh")
        return 1;
    if (resource == OPENSHIM_CHUNK_CACHE_FALLBACK_DIR "stock_chunk2.mesh")
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
// points included. The edges must be distinct (the caller de-duplicates).
// `localOf` is caller scratch, at least (max welded id + 1) entries all -1; it
// is returned to that state.
std::vector<std::vector<int>> boundaryLoops(const std::vector<std::pair<int, int>> &edges,
                                            std::vector<int> &localOf)
{
    // Dense node ids and, per node, its outgoing edges in input order (CSR).
    std::vector<int> nodes;
    std::vector<int> tail(edges.size()), head(edges.size());
    const auto node = [&](int id) {
        int &slot = localOf[static_cast<size_t>(id)];
        if (slot < 0)
        {
            slot = static_cast<int>(nodes.size());
            nodes.push_back(id);
        }
        return slot;
    };
    for (size_t i = 0; i < edges.size(); ++i)
    {
        tail[i] = node(edges[i].first);
        head[i] = node(edges[i].second);
    }
    std::vector<uint32_t> first(nodes.size() + 1, 0);
    for (size_t i = 0; i < edges.size(); ++i)
        ++first[static_cast<size_t>(tail[i]) + 1];
    for (size_t n = 0; n < nodes.size(); ++n)
        first[n + 1] += first[n];
    std::vector<uint32_t> outgoing(edges.size()), fill(first.begin(), first.end() - 1);
    for (size_t i = 0; i < edges.size(); ++i)
        outgoing[fill[static_cast<size_t>(tail[i])]++] = static_cast<uint32_t>(i);
    std::vector<uint32_t> cursor(first.begin(), first.end() - 1);
    std::vector<char> used(edges.size(), 0);
    std::vector<std::vector<int>> loops;
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (used[i])
            continue;
        const int a = edges[i].first;
        std::vector<int> loop{a};
        used[i] = 1;
        int current = head[i];
        size_t guard = 0;
        while (nodes[static_cast<size_t>(current)] != a && guard < edges.size() + 1)
        {
            loop.push_back(nodes[static_cast<size_t>(current)]);
            // First not-yet-used outgoing edge; used edges only accumulate, so
            // the cursor never needs to back up.
            const size_t n = static_cast<size_t>(current);
            while (cursor[n] < first[n + 1] && used[outgoing[cursor[n]]])
                ++cursor[n];
            if (cursor[n] == first[n + 1])
                break;
            const uint32_t e = outgoing[cursor[n]];
            used[e] = 1;
            current = head[e];
            ++guard;
        }
        if (loop.size() >= 3)
            loops.push_back(std::move(loop));
    }
    for (int id : nodes)
        localOf[static_cast<size_t>(id)] = -1;
    return loops;
}
// Open-addressing tables for the weld and cut-edge passes (std::map here was
// the bulk of gib generation time on dense meshes).
size_t tableSize(size_t entries)
{
    size_t n = 16;
    while (n < entries)
        n <<= 1;
    return n;
}
uint64_t mix64(uint64_t x)
{
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return x;
}
// Position (quantised to 1e-4) -> welded id, ids chosen by the caller.
class WeldTable
{
  public:
    explicit WeldTable(size_t expected) : slots_(tableSize(expected * 2)), mask_(slots_.size() - 1)
    {
    }
    // Existing id for `key`, or `fresh` = true and `newId` recorded.
    int find(const std::array<long long, 3> &key, int newId, bool &fresh)
    {
        uint64_t h = mix64(static_cast<uint64_t>(key[0]));
        h = mix64(h ^ static_cast<uint64_t>(key[1]));
        h = mix64(h ^ static_cast<uint64_t>(key[2]));
        for (size_t i = h & mask_;; i = (i + 1) & mask_)
        {
            Slot &s = slots_[i];
            if (s.id < 0)
            {
                s.key = key;
                s.id = newId;
                fresh = true;
                return newId;
            }
            if (s.key == key)
            {
                fresh = false;
                return s.id;
            }
        }
    }

  private:
    struct Slot
    {
        std::array<long long, 3> key{};
        int id = -1;
    };
    std::vector<Slot> slots_;
    size_t mask_;
};
inline uint64_t pairKey(int a, int b)
{
    return (static_cast<uint64_t>(static_cast<uint32_t>(a)) << 32) | static_cast<uint32_t>(b);
}
// Undirected welded edge -> (first piece seen, touched by another piece too).
class EdgeTable
{
  public:
    explicit EdgeTable(size_t edges) : slots_(tableSize(edges + edges / 2 + 1)), mask_(slots_.size() - 1)
    {
    }
    void touch(int u, int v, int piece)
    {
        Slot &s = slot(pairKey(std::min(u, v), std::max(u, v)));
        if (s.key == kEmpty)
        {
            s.key = pairKey(std::min(u, v), std::max(u, v));
            s.first = piece;
        }
        else if (s.first != piece)
            s.multi = true;
    }
    bool shared(int u, int v)
    {
        const Slot &s = slot(pairKey(std::min(u, v), std::max(u, v)));
        if (s.key == kEmpty)
            throw std::out_of_range("edge missing from piece topology");
        return s.multi;
    }

  private:
    static constexpr uint64_t kEmpty = ~0ULL;
    struct Slot
    {
        uint64_t key = kEmpty;
        int first = 0;
        bool multi = false;
    };
    Slot &slot(uint64_t key)
    {
        for (size_t i = mix64(key) & mask_;; i = (i + 1) & mask_)
            if (slots_[i].key == key || slots_[i].key == kEmpty)
                return slots_[i];
    }
    std::vector<Slot> slots_;
    size_t mask_;
};
// Insert-only set of ordered welded pairs.
class PairSet
{
  public:
    explicit PairSet(size_t entries) : slots_(tableSize(entries * 2), kEmpty), mask_(slots_.size() - 1)
    {
    }
    bool insert(int a, int b)
    {
        const uint64_t key = pairKey(a, b);
        for (size_t i = mix64(key) & mask_;; i = (i + 1) & mask_)
        {
            if (slots_[i] == key)
                return false;
            if (slots_[i] == kEmpty)
            {
                slots_[i] = key;
                return true;
            }
        }
    }

  private:
    static constexpr uint64_t kEmpty = ~0ULL;
    std::vector<uint64_t> slots_;
    size_t mask_;
};
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
// One cap vertex: position, normal and planar UVs. Hue deliberately does not
// ride on vertex colours: every DX11 path reads a packed colour as raw RGBA
// (RenderSystem_Direct3D11's D3D11Mappings::get maps VET_COLOUR, _ARGB and
// _ABGR all to R8G8B8A8_UNORM), and the stock/compat programs swizzle with
// .bgra while a generated fixed-function shader would not, so red would draw
// blue on one of them. Zones are separate submeshes with their own material
// colours instead, which every path (DX9 fixed function, DX11 compat, DX11
// generated) handles identically.
struct CapVertex
{
    V p, n;
    float u, v;
};
enum CapZone : size_t
{
    kZoneSkin,   // thin dark dermis edge
    kZoneFat,    // pale subcutaneous fat band
    kZoneMuscle, // textured muscle, the main body of the cap
    kZoneBone,   // limb cuts: ivory ring
    kZoneMarrow, // limb cuts: dark centre
    kZoneCount
};
struct CapMesh
{
    std::vector<CapVertex> vertices;
    std::vector<uint32_t> indices[kZoneCount];
    size_t triangles() const
    {
        size_t n = 0;
        for (const auto &list : indices)
            n += list.size() / 3;
        return n;
    }
};
// Stable per-position noise in [0,1): the hash of the welded (1e-4 quantised)
// position and a salt, so a cut gets the same ragged edge on every run and on
// both sides of a shared boundary point.
float positionNoise(const V &p, uint32_t salt)
{
    uint32_t h = 0x9e3779b9U * (salt + 1);
    for (int i = 0; i < 3; ++i)
    {
        h ^= static_cast<uint32_t>(static_cast<int32_t>(std::llround(static_cast<double>(p[i]) / 1e-4)));
        h ^= h >> 16;
        h *= 0x7feb352dU;
        h ^= h >> 15;
        h *= 0x846ca68bU;
        h ^= h >> 16;
    }
    return static_cast<float>(h >> 8) * (1.0f / 16777216.0f);
}
constexpr uint16_t kCapStride = 32; // position, normal, uv0
constexpr size_t kMinRingLoop = 4, kMaxRingLoop = 96, kMaxRingTriangles = 60000;
// Loops smaller than this (about 2 mm) are not worth rings.
constexpr float kMinRingRadius = 2e-3f;
// A ring layer: radius as a fraction of the loop's (smoothed) radius, normal
// lift (fraction of the radius) and which zone the band OUTSIDE it belongs to.
struct CapLayer
{
    float scale, lift;
    float smoothing;  // how much of one Laplacian pass this ring takes: the skin edge hugs the rim
    CapZone bandZone; // the band between the previous layer and this one
};
// Skin band ~5% of the radius, fat ~8%, then muscle in to the centre; limb
// cuts end the muscle at 0.30 with a bone annulus down to a marrow core.
constexpr CapLayer kPlainLayers[] = {{0.95f, -0.01f, 0.3f, kZoneSkin},
                                     {0.87f, -0.02f, 0.6f, kZoneFat},
                                     {0.50f, -0.03f, 1.0f, kZoneMuscle}};
constexpr CapLayer kLimbLayers[] = {{0.95f, -0.01f, 0.3f, kZoneSkin},   {0.87f, -0.02f, 0.6f, kZoneFat},
                                    {0.55f, -0.03f, 1.0f, kZoneMuscle}, {0.32f, -0.02f, 1.0f, kZoneMuscle},
                                    {0.20f, 0.02f, 1.0f, kZoneBone}};
// Torn-tissue cap over one cut loop. `points` are the welded boundary points,
// `normal` faces away from the piece. The rim is the boundary itself (it must
// seal the skin); every inner ring is an in-plane Laplacian-smoothed copy of
// the one outside it, scaled toward the centre, with a few percent of
// deterministic jitter, so the surface follows the rim's shape instead of
// fanning out in flaps. Every triangle is validated (positive area in the cap
// plane, facing the cap normal); a loop that folds is retried with weaker
// inset and smoothing and finally keeps the plain fan.
enum class RingResult
{
    Built,
    NotStarShaped, // a band triangle has negative area: weaker inset cannot help, try another pivot
    Folded         // degenerate or too steep: retry weaker
};
RingResult addRingCap(CapMesh &cap, const std::vector<V> &points, V normal, V centre, bool limb, float uvScale,
                      float radius, float strength)
{
    const size_t n = points.size();
    const CapLayer *layers = limb ? kLimbLayers : kPlainLayers;
    const size_t layerCount = limb ? sizeof(kLimbLayers) / sizeof(CapLayer) : sizeof(kPlainLayers) / sizeof(CapLayer);
    const V tangent = normalize3(cross3(normal, std::abs(normal[1]) < 0.9f ? V{0, 1, 0} : V{1, 0, 0}));
    const V bitangent = cross3(normal, tangent);
    // Cap-plane coordinates relative to the centre: x along tangent, y along
    // bitangent, z along the normal. Ring 0 is the boundary, wound CCW about N.
    std::vector<std::array<float, 3>> ring(n);
    for (size_t i = 0; i < n; ++i)
    {
        const V d = sub3(points[i], centre);
        ring[i] = {dot3(d, tangent), dot3(d, bitangent), dot3(d, normal)};
    }
    double area2 = 0;
    for (size_t i = 0; i < n; ++i)
    {
        const auto &a = ring[i], &b = ring[(i + 1) % n];
        area2 += static_cast<double>(a[0]) * b[1] - static_cast<double>(b[0]) * a[1];
    }
    if (area2 < 0)
        std::reverse(ring.begin(), ring.end());
    std::vector<V> boundary = points;
    if (area2 < 0)
        std::reverse(boundary.begin(), boundary.end());

    // Rings keep each boundary point's polar angle and move only along its
    // ray (radius) and the normal: the radius is Laplacian-smoothed, scaled
    // toward the centre and always kept inside the ring outside it, so every
    // band triangle stays positively oriented in the cap plane (no folds).
    std::vector<float> angle(n);
    for (size_t i = 0; i < n; ++i)
        angle[i] = std::atan2(ring[i][1], ring[i][0]);
    std::vector<std::vector<std::array<float, 3>>> rings{ring};
    std::vector<float> rho(n), height(n);
    for (size_t i = 0; i < n; ++i)
    {
        rho[i] = std::sqrt(ring[i][0] * ring[i][0] + ring[i][1] * ring[i][1]);
        height[i] = ring[i][2];
    }
    float previousScale = 1.0f;
    for (size_t j = 0; j < layerCount; ++j)
    {
        const CapLayer &layer = layers[j];
        const float s = 1.0f - (1.0f - layer.scale) * strength;
        const float ratio = s / previousScale;
        std::vector<float> nextRho(n), nextHeight(n);
        for (size_t i = 0; i < n; ++i)
        {
            const size_t before = (i + n - 1) % n, after = (i + 1) % n;
            const float smoothRho = (rho[before] + 2.0f * rho[i] + rho[after]) * 0.25f;
            const float smoothHeight = (height[before] + 2.0f * height[i] + height[after]) * 0.25f;
            const float blendRho = rho[i] + (smoothRho - rho[i]) * strength * layer.smoothing;
            const float blendHeight = height[i] + (smoothHeight - height[i]) * strength * layer.smoothing;
            // Jitter: a few percent of the local edge length, deterministic.
            const float edge = std::sqrt((rho[after] * std::cos(angle[after]) - rho[i] * std::cos(angle[i])) *
                                             (rho[after] * std::cos(angle[after]) - rho[i] * std::cos(angle[i])) +
                                         (rho[after] * std::sin(angle[after]) - rho[i] * std::sin(angle[i])) *
                                             (rho[after] * std::sin(angle[after]) - rho[i] * std::sin(angle[i])));
            const float jr = (2.0f * positionNoise(boundary[i], 10 + static_cast<uint32_t>(j)) - 1.0f) * 0.04f * edge;
            const float jz = (2.0f * positionNoise(boundary[i], 30 + static_cast<uint32_t>(j)) - 1.0f) * 0.05f * edge;
            // Never reach the ring outside along the same ray.
            nextRho[i] = std::min(blendRho * ratio + jr, rho[i] * 0.97f);
            nextHeight[i] = blendHeight * ratio * 0.5f + layer.lift * radius * strength + jz;
        }
        previousScale = s;
        rho = std::move(nextRho);
        height = std::move(nextHeight);
        std::vector<std::array<float, 3>> next(n);
        for (size_t i = 0; i < n; ++i)
            next[i] = {rho[i] * std::cos(angle[i]), rho[i] * std::sin(angle[i]), height[i]};
        rings.push_back(std::move(next));
    }
    const float centreLift = (limb ? 0.01f + 0.01f * positionNoise(centre, 40) : 0.06f + 0.03f * positionNoise(centre, 40)) * radius * strength;

    // Positions (centre is ring-local origin).
    const auto world = [&](const std::array<float, 3> &q) {
        return add(add(centre, add(scale3(tangent, q[0]), scale3(bitangent, q[1]))), scale3(normal, q[2]));
    };
    const size_t base = cap.vertices.size();
    for (const V &p : boundary)
        cap.vertices.push_back({p, normal, 0, 0}); // the rim is the cut itself, bit for bit
    for (size_t j = 1; j < rings.size(); ++j)
        for (const auto &q : rings[j])
            cap.vertices.push_back({world(q), normal, 0, 0});
    cap.vertices.push_back({add(centre, scale3(normal, centreLift)), normal, 0, 0});
    const uint32_t centreIndex = static_cast<uint32_t>(base + rings.size() * n);
    const auto index = [&](size_t layer, size_t i) { return static_cast<uint32_t>(base + layer * n + i % n); };

    // Triangles: ring bands, then the fan into the centre.
    std::vector<std::array<uint32_t, 3>> tris;
    std::vector<size_t> triZone;
    const auto planarArea = [&](uint32_t a, uint32_t b, uint32_t c) {
        const V &pa = cap.vertices[a].p, &pb = cap.vertices[b].p, &pc = cap.vertices[c].p;
        return 0.5f * dot3(cross3(sub3(pb, pa), sub3(pc, pa)), normal);
    };
    bool valid = true, negative = false;
    const float minArea = 1e-4f * radius * radius;
    const auto add_tri = [&](uint32_t a, uint32_t b, uint32_t c, size_t zone) {
        const V &pa = cap.vertices[a].p, &pb = cap.vertices[b].p, &pc = cap.vertices[c].p;
        const V face = cross3(sub3(pb, pa), sub3(pc, pa));
        const float length = std::sqrt(dot3(face, face));
        // Positive in the cap plane, and not steeply folded against the normal.
        if (planarArea(a, b, c) < minArea || !(dot3(face, normal) >= 0.05f * length))
        {
            if (valid && strength == 1.0f)
                CAP_STAT(planarArea(a, b, c) < 0 ? 5 : (planarArea(a, b, c) < minArea ? 6 : 7));
            if (planarArea(a, b, c) < 0)
                negative = true;
            valid = false;
        }
        tris.push_back({a, b, c});
        triZone.push_back(zone);
    };
    for (size_t j = 0; j + 1 < rings.size(); ++j)
    {
        const size_t zone = layers[j].bandZone;
        for (size_t i = 0; i < n; ++i)
        {
            add_tri(index(j, i), index(j, i + 1), index(j + 1, i + 1), zone);
            add_tri(index(j, i), index(j + 1, i + 1), index(j + 1, i), zone);
        }
    }
    // The innermost band (last layer) has no band entry of its own: it is the
    // fan, zone = bone annulus' inside = marrow for limbs, muscle otherwise.
    for (size_t i = 0; i < n; ++i)
        add_tri(index(rings.size() - 1, i), index(rings.size() - 1, i + 1), centreIndex,
                limb ? static_cast<size_t>(kZoneMarrow) : static_cast<size_t>(kZoneMuscle));
    if (!valid)
    {
        cap.vertices.resize(base);
        return negative ? RingResult::NotStarShaped : RingResult::Folded;
    }
    // Smooth normals from the real surface.
    std::vector<V> accumulated(cap.vertices.size() - base, V{0, 0, 0});
    for (const auto &t : tris)
    {
        const V &a = cap.vertices[t[0]].p, &b = cap.vertices[t[1]].p, &c = cap.vertices[t[2]].p;
        const V face = cross3(sub3(b, a), sub3(c, a));
        for (const uint32_t v : t)
            accumulated[v - base] = add(accumulated[v - base], face);
    }
    for (size_t k = 0; k < accumulated.size(); ++k)
    {
        const V smoothed = normalize3(accumulated[k]);
        cap.vertices[base + k].n = dot3(smoothed, normal) > 0.1f ? smoothed : normal;
    }
    for (size_t k = base; k < cap.vertices.size(); ++k)
    {
        const V &p = cap.vertices[k].p;
        cap.vertices[k].u = dot3(p, tangent) * uvScale;
        cap.vertices[k].v = dot3(p, bitangent) * uvScale;
    }
    for (size_t t = 0; t < tris.size(); ++t)
        for (const uint32_t v : tris[t])
            cap.indices[triZone[t]].push_back(v);
    return RingResult::Built;
}
// The plain fan from the loop centroid: the fallback for loops that are
// degenerate, huge, far from planar, or that fold when ringed. Same winding
// logic as the original cap.
void addFanCap(CapMesh &cap, const std::vector<V> &points, V normal, V centre, float uvScale)
{
    const size_t n = points.size();
    const V tangent = normalize3(cross3(normal, std::abs(normal[1]) < 0.9f ? V{0, 1, 0} : V{1, 0, 0}));
    const V bitangent = cross3(normal, tangent);
    const size_t base = cap.vertices.size();
    for (const V &p : points)
        cap.vertices.push_back({p, normal, dot3(p, tangent) * uvScale, dot3(p, bitangent) * uvScale});
    cap.vertices.push_back({centre, normal, dot3(centre, tangent) * uvScale, dot3(centre, bitangent) * uvScale});
    const uint32_t centreIndex = static_cast<uint32_t>(base + n);
    for (size_t i = 0; i < n; ++i)
    {
        uint32_t p0 = static_cast<uint32_t>(base + i), p1 = static_cast<uint32_t>(base + (i + 1 == n ? 0 : i + 1));
        if (dot3(cross3(sub3(cap.vertices[p0].p, centre), sub3(cap.vertices[p1].p, centre)), normal) < 0)
            std::swap(p0, p1);
        cap.indices[kZoneMuscle].push_back(centreIndex);
        cap.indices[kZoneMuscle].push_back(p0);
        cap.indices[kZoneMuscle].push_back(p1);
    }
}
void addCap(CapMesh &cap, const std::vector<V> &points, V normal, V centre, float newellLength, bool limb,
            bool rings, float uvScale)
{
    const size_t n = points.size();
    float radius = 0, planarity = 0;
    for (const V &p : points)
    {
        const V d = sub3(p, centre);
        const float along = dot3(d, normal);
        radius += std::sqrt(std::max(0.0f, dot3(d, d) - along * along));
        planarity = std::max(planarity, std::abs(along));
    }
    radius /= static_cast<float>(n);
    const bool ringed = rings && n >= kMinRingLoop && n <= kMaxRingLoop && radius > kMinRingRadius &&
                        planarity <= 0.4f * radius && newellLength >= 0.5f * radius * radius &&
                        cap.triangles() < kMaxRingTriangles;
    if (ringed)
    {
        // Full inset and smoothing first; on a fold, weaker, then the fan.
        // Rings need a pivot every boundary point can be seen from in order
        // (star-shaped). Try the vertex mean, then the polygon's area centroid
        // and bounding-box centre in the cap plane.
        const V tangent = normalize3(cross3(normal, std::abs(normal[1]) < 0.9f ? V{0, 1, 0} : V{1, 0, 0}));
        const V bitangent = cross3(normal, tangent);
        std::vector<V> pivots{centre};
        {
            double a2 = 0, cx = 0, cy = 0;
            float lox = 1e30f, hix = -1e30f, loy = 1e30f, hiy = -1e30f;
            for (size_t i = 0; i < n; ++i)
            {
                const V d0 = sub3(points[i], centre), d1 = sub3(points[(i + 1) % n], centre);
                const double x0 = dot3(d0, tangent), y0 = dot3(d0, bitangent), x1 = dot3(d1, tangent), y1 = dot3(d1, bitangent);
                const double w = x0 * y1 - x1 * y0;
                a2 += w;
                cx += (x0 + x1) * w;
                cy += (y0 + y1) * w;
                lox = std::min(lox, static_cast<float>(x0));
                hix = std::max(hix, static_cast<float>(x0));
                loy = std::min(loy, static_cast<float>(y0));
                hiy = std::max(hiy, static_cast<float>(y0));
            }
            if (std::abs(a2) > 1e-12)
                pivots.push_back(add(add(centre, scale3(tangent, static_cast<float>(cx / (3.0 * a2)))),
                                     scale3(bitangent, static_cast<float>(cy / (3.0 * a2)))));
            pivots.push_back(add(add(centre, scale3(tangent, 0.5f * (lox + hix))), scale3(bitangent, 0.5f * (loy + hiy))));
        }
        size_t attempt = 0;
        for (const V &pivot : pivots)
            for (const float strength : {1.0f, 0.6f, 0.3f})
            {
                const RingResult result = addRingCap(cap, points, normal, pivot, limb, uvScale, radius, strength);
                if (result == RingResult::Built)
                {
                    CAP_STAT(attempt < 3 ? attempt : 2);
                    return;
                }
                ++attempt;
                if (result == RingResult::NotStarShaped)
                    break; // a weaker inset cannot fix the loop's shape; try the next pivot
            }
    }
    CAP_STAT(ringed ? 4 : 3);
    addFanCap(cap, points, normal, centre, uvScale);
}
} // namespace
bool ExtractGibs(const Bytes &bytes, const Bytes &skeleton, const GibOptions &options, std::vector<GibPiece> &gibs,
                 std::string &error)
{
    gibs.clear();
    error.clear();
    try
    {
        GIB_PHASE_BEGIN;
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
        const std::regex limbRegex = pattern(options.limbPattern);
        GIB_PHASE(0); // regex setup
        const auto m = model(bytes);
        auto bs = bones(skeleton);
        for (auto &[id, b] : bs)
            derive(id, bs);
        GIB_PHASE(1); // parse mesh + skeleton
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
        // Dense by bone handle (a uint16_t): the hot loops below bump it per face.
        std::vector<uint32_t> counts(65536, 0);
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
        GIB_PHASE(2); // dominant bone per face

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
        struct PieceEntry
        {
            std::vector<GibFace> faces;
            uint16_t bone = 0; // the last face's driving bone, like the script's dict overwrite
        };
        std::map<std::string, PieceEntry> pieceFaces;
        // Bone -> entry, so the per-face work is two array reads, not a string-keyed map lookup.
        std::vector<PieceEntry *> entryOfBone(65536, nullptr);
        PieceEntry *weaponEntry = nullptr;
        for (size_t s = 0; s < m.subs.size(); ++s)
            for (size_t f = 0; f < owners[s].size(); ++f)
            {
                if (owners[s][f] < 0)
                    continue;
                const uint16_t bone = weaponSub[s] ? weaponBone : target.at(static_cast<uint16_t>(owners[s][f]));
                PieceEntry *&slot = weaponSub[s] ? weaponEntry : entryOfBone[bone];
                if (!slot)
                    slot = &pieceFaces[weaponSub[s] ? kWeaponKey : bs.at(bone).name];
                slot->faces.push_back({s, f});
                slot->bone = bone;
            }
        std::map<std::string, int> pieceIds;
        for (const auto &entry : pieceFaces)
            pieceIds.emplace(entry.first, static_cast<int>(pieceIds.size()));
        std::vector<std::vector<int>> facePiece(m.subs.size());
        for (size_t s = 0; s < m.subs.size(); ++s)
            facePiece[s].assign(owners[s].size(), -1);
        for (const auto &[key, entry] : pieceFaces)
        {
            const int id = pieceIds.at(key);
            for (const auto &face : entry.faces)
                facePiece[face.sub][face.face] = id;
        }

        GIB_PHASE(3); // roll-up + piece grouping
        // 4. Position-welded topology: a cut is an edge shared by faces of
        //    more than one body piece, wherever the exporter split vertices.
        //    Weld ids are handed out in first-seen order (the output depends
        //    on them only through that order).
        std::vector<V> weldPosition;
        std::map<const Geometry *, std::vector<int>> weldCache;
        {
            size_t vertexTotal = 0;
            for (const auto &sub : m.subs)
                vertexTotal += (sub.shared ? m.geometry : sub.geometry).count;
            WeldTable table(vertexTotal);
            for (const auto &sub : m.subs)
            {
                const Geometry &g = sub.shared ? m.geometry : sub.geometry;
                if (weldCache.count(&g))
                    continue;
                std::vector<int> ids(g.count);
                if (g.count)
                {
                    const PositionReader position(g);
                    for (uint32_t v = 0; v < g.count; ++v)
                    {
                        const V p = position(v);
                        const std::array<long long, 3> key{std::llround(static_cast<double>(p[0]) / 1e-4),
                                                           std::llround(static_cast<double>(p[1]) / 1e-4),
                                                           std::llround(static_cast<double>(p[2]) / 1e-4)};
                        bool fresh = false;
                        ids[v] = table.find(key, static_cast<int>(weldPosition.size()), fresh);
                        if (fresh)
                            weldPosition.push_back(p);
                    }
                }
                weldCache.emplace(&g, std::move(ids));
            }
        }
        std::vector<const std::vector<int> *> subWelds(m.subs.size());
        for (size_t s = 0; s < m.subs.size(); ++s)
        {
            const Sub &sub = m.subs[s];
            subWelds[s] = &weldCache.at(sub.shared ? &m.geometry : &sub.geometry);
        }
        // Triangle indices were range-checked against the vertex count by
        // triangleOwners, which sized the weld id arrays.
        const auto faceWelds = [&](size_t s, size_t f) {
            const Sub &sub = m.subs[s];
            const auto &ids = *subWelds[s];
            return std::array<int, 3>{ids[sub.indices[f * 3]], ids[sub.indices[f * 3 + 1]],
                                      ids[sub.indices[f * 3 + 2]]};
        };
        // Per welded edge: the first body piece to touch it and whether any
        // other piece does too (all the cut test needs).
        // A shared edge needs both ends on more than one piece, so find those
        // vertices first and keep only edges between them in the table.
        std::vector<int> vertexPiece(weldPosition.size(), -1);
        std::vector<char> vertexMulti(weldPosition.size(), 0);
        const auto forBodyFaces = [&](auto &&fn) {
            for (size_t s = 0; s < m.subs.size(); ++s)
            {
                if (weaponSub[s])
                    continue;
                for (size_t f = 0; f < owners[s].size(); ++f)
                    if (facePiece[s][f] >= 0)
                        fn(faceWelds(s, f), facePiece[s][f]);
            }
        };
        forBodyFaces([&](const std::array<int, 3> &w, int piece) {
            for (const int id : w)
            {
                int &first = vertexPiece[static_cast<size_t>(id)];
                if (first < 0)
                    first = piece;
                else if (first != piece)
                    vertexMulti[static_cast<size_t>(id)] = 1;
            }
        });
        const auto multiEdge = [&](int u, int v) {
            return vertexMulti[static_cast<size_t>(u)] && vertexMulti[static_cast<size_t>(v)];
        };
        size_t candidateEdges = 0;
        forBodyFaces([&](const std::array<int, 3> &w, int) {
            for (int e = 0; e < 3; ++e)
                candidateEdges += multiEdge(w[e], w[(e + 1) % 3]);
        });
        EdgeTable edgePieces(candidateEdges);
        forBodyFaces([&](const std::array<int, 3> &w, int piece) {
            for (int e = 0; e < 3; ++e)
                if (multiEdge(w[e], w[(e + 1) % 3]))
                    edgePieces.touch(w[e], w[(e + 1) % 3], piece);
        });

        GIB_PHASE(4); // weld + edge->piece topology
        std::set<std::string> usedNames;
        std::vector<std::optional<PositionReader>> positionReaders(m.subs.size());
        const auto positionOf = [&](size_t s) -> const PositionReader & {
            if (!positionReaders[s])
            {
                const Sub &sub = m.subs[s];
                positionReaders[s].emplace(sub.shared ? m.geometry : sub.geometry);
            }
            return *positionReaders[s];
        };
        std::vector<int> loopScratch(weldPosition.size(), -1);
        std::vector<uint32_t> remapScratch;
        for (const auto &[key, entry] : pieceFaces)
        {
            const auto &faces = entry.faces;
            const bool isWeapon = key == kWeaponKey;
            const uint16_t boneId = entry.bone;
            const Bone &bone = bs.at(boneId);
            Frame frame = boneFrame(bone);

            // Model-space centroid of every face corner (duplicates counted,
            // as the script does): caps face away from it.
            V centroid{};
            size_t corners = 0;
            V lo{1e30f, 1e30f, 1e30f}, hi{-1e30f, -1e30f, -1e30f};
            std::vector<std::vector<uint32_t>> bySub(m.subs.size());
            for (const auto &face : faces)
            {
                const Sub &sub = m.subs[face.sub];
                const PositionReader &position = positionOf(face.sub);
                auto &indices = bySub[face.sub];
                for (size_t k = 0; k < 3; ++k)
                {
                    const uint32_t index = sub.indices[face.face * 3 + k];
                    indices.push_back(index);
                    const V p = position(index);
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

            GIB_PHASE(5); // per-piece centroid + bounds
            // 5. Torn-flesh caps over every cut loop, built in model space.
            CapMesh caps;
            if (!isWeapon && options.caps)
            {
                std::vector<std::pair<int, int>> cutEdges;
                PairSet seen(faces.size() * 3);
                for (const auto &face : faces)
                {
                    const auto w = faceWelds(face.sub, face.face);
                    for (int e = 0; e < 3; ++e)
                    {
                        const int u = w[e], v = w[(e + 1) % 3];
                        // Reversed, so the cap winds opposite to the skin it closes.
                        if (multiEdge(u, v) && edgePieces.shared(u, v) && seen.insert(v, u))
                            cutEdges.push_back({v, u});
                    }
                }
                GIB_PHASE(8); // cut edges
                const auto cutLoops = boundaryLoops(cutEdges, loopScratch);
                GIB_PHASE(9); // boundary loops
                const bool limb = std::regex_search(bone.name, limbRegex);
                std::vector<V> points;
                for (const auto &loop : cutLoops)
                {
                    points.clear();
                    for (int w : loop)
                        points.push_back(weldPosition.at(static_cast<size_t>(w)));
                    V center{};
                    for (const auto &p : points)
                        center = add(center, p);
                    center = scale3(center, 1.0f / static_cast<float>(points.size()));
                    V newell{};
                    for (size_t i = 0; i < points.size(); ++i)
                    {
                        const V p = points[i], q = points[i + 1 == points.size() ? 0 : i + 1];
                        newell = add(newell, V{(p[1] - q[1]) * (p[2] + q[2]), (p[2] - q[2]) * (p[0] + q[0]),
                                               (p[0] - q[0]) * (p[1] + q[1])});
                    }
                    V normal = normalize3(newell);
                    if (dot3(normal, sub3(center, centroid)) < 0)
                    {
                        normal = scale3(normal, -1.0f);
                        std::reverse(points.begin(), points.end());
                    }
                    addCap(caps, points, normal, center, std::sqrt(dot3(newell, newell)), limb, options.capRings,
                           options.capUvScale);
                }
                GIB_PHASE(10); // cap triangles
                if (caps.triangles() > 1000000)
                    throw std::runtime_error("oversized gib cap");
            }

            GIB_PHASE(6); // caps
            // 6. Serialize in the bone frame, centred on the piece bounds,
            //    exactly as Extract writes a chunk piece.
            Bytes body;
            put(body, uint16_t{0x1000});
            line(body, "[MeshSerializer_v1.8]");
            const size_t meshChunk = openChunk(body, 0x3000);
            put(body, uint8_t{0});
            uint32_t triangles = 0;
            float radius = 0;
            lo = {1e30f, 1e30f, 1e30f};
            hi = {-1e30f, -1e30f, -1e30f};
            for (size_t s = 0; s < bySub.size(); ++s)
            {
                const auto &selected = bySub[s];
                if (selected.empty())
                    continue;
                const Sub &sub = m.subs[s];
                const Geometry &g = sub.shared ? m.geometry : sub.geometry;
                // Distinct vertices ascending; every selected index was
                // range-checked against g.count by the bounds pass above.
                constexpr uint32_t kUnused = 0xFFFFFFFFu, kMarked = 0xFFFFFFFEu;
                if (remapScratch.size() < g.count)
                    remapScratch.resize(g.count);
                std::fill(remapScratch.begin(), remapScratch.begin() + g.count, kUnused);
                for (const uint32_t index : selected)
                    remapScratch[index] = kMarked;
                std::vector<uint32_t> vertices;
                for (uint32_t v = 0; v < g.count; ++v)
                    if (remapScratch[v] == kMarked)
                    {
                        remapScratch[v] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(v);
                    }
                const size_t subChunk = openChunk(body, 0x4000);
                line(body, sub.material);
                put(body, uint8_t{0});
                put(body, static_cast<uint32_t>(selected.size()));
                put(body, uint8_t{1});
                {
                    const size_t base = body.size();
                    body.resize(base + selected.size() * sizeof(uint32_t));
                    for (size_t i = 0; i < selected.size(); ++i)
                        std::memcpy(body.data() + base + i * sizeof(uint32_t), &remapScratch[selected[i]],
                                    sizeof(uint32_t));
                }
                const size_t geometryChunk = openChunk(body, 0x5000);
                appendGeometry(body, g, vertices, frame, lo, hi, radius);
                closeChunk(body, geometryChunk);
                closeChunk(body, subChunk);
                triangles += static_cast<uint32_t>(selected.size() / 3);
            }
            const std::string *zoneMaterial[kZoneCount] = {&options.capSkinMaterial, &options.capFatMaterial,
                                                           &options.capMaterial, &options.capBoneMaterial,
                                                           &options.capMarrowMaterial};
            for (size_t zone = 0; zone < kZoneCount; ++zone)
            {
                const auto &zoneIndices = caps.indices[zone];
                if (zoneIndices.empty())
                    continue;
                // One submesh per zone (its own material colour), with only
                // the vertices that zone uses: position, normal, uv0. Planar
                // UVs in each cap's plane so the flesh texture tiles evenly;
                // positions and normals go through the piece frame.
                std::vector<uint32_t> used;
                std::vector<uint32_t> local(caps.vertices.size(), 0xFFFFFFFFu);
                std::vector<uint32_t> indices;
                indices.reserve(zoneIndices.size());
                for (const uint32_t index : zoneIndices)
                {
                    if (local[index] == 0xFFFFFFFFu)
                    {
                        local[index] = static_cast<uint32_t>(used.size());
                        used.push_back(index);
                    }
                    indices.push_back(local[index]);
                }
                Geometry g;
                g.count = static_cast<uint32_t>(used.size());
                g.elements = {{0, 2, 1, 0, 0}, {0, 2, 4, 12, 0}, {0, 1, 7, 24, 0}};
                Buffer buffer{kCapStride, {}};
                buffer.data.resize(used.size() * kCapStride);
                uint8_t *dst = buffer.data.data();
                for (const uint32_t index : used)
                {
                    const CapVertex &vertex = caps.vertices[index];
                    std::memcpy(dst, vertex.p.data(), 12);
                    std::memcpy(dst + 12, vertex.n.data(), 12);
                    std::memcpy(dst + 24, &vertex.u, 4);
                    std::memcpy(dst + 28, &vertex.v, 4);
                    dst += kCapStride;
                }
                std::vector<uint32_t> vertices(used.size());
                for (size_t i = 0; i < vertices.size(); ++i)
                    vertices[i] = static_cast<uint32_t>(i);
                g.buffers.emplace(uint16_t{0}, std::move(buffer));
                const size_t subChunk = openChunk(body, 0x4000);
                line(body, *zoneMaterial[zone]);
                put(body, uint8_t{0});
                put(body, static_cast<uint32_t>(indices.size()));
                put(body, uint8_t{1});
                body.insert(body.end(), reinterpret_cast<const uint8_t *>(indices.data()),
                            reinterpret_cast<const uint8_t *>(indices.data() + indices.size()));
                const size_t geometryChunk = openChunk(body, 0x5000);
                appendGeometry(body, g, vertices, frame, lo, hi, radius);
                closeChunk(body, geometryChunk);
                closeChunk(body, subChunk);
                triangles += static_cast<uint32_t>(indices.size() / 3);
            }
            Bytes bounds;
            for (float v : lo)
                put(bounds, v);
            for (float v : hi)
                put(bounds, v);
            put(bounds, radius);
            chunk(body, 0x9000, bounds);
            closeChunk(body, meshChunk);
            Bytes &out = body;

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
            gib.capTriangles = static_cast<uint32_t>(caps.triangles());
            gib.weapon = isWeapon;
            gibs.push_back(std::move(gib));
            GIB_PHASE(7); // serialize
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
