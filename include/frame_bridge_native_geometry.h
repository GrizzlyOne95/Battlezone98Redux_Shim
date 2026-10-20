#pragma once
#include <cmath>
#include <cstdint>
#include <cstring>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <vector>

namespace BZROpenShim::FrameBridge
{
    // Development snapshot, not a live IPC contract. No pointers or engine
    // ownership cross the file boundary. Vertices are expanded world triangles.
    struct NativeGeometryHeader
    {
        char magic[8]={'B','Z','R','G','E','O','1',0};
        // Initial mission may be generation zero when the adapter starts after
        // RUN_STARTED. A snapshot is identified by its producer PID and hash.
        std::uint32_t version=1, byteSize=48, producerPid=0, missionGeneration=0;
        std::uint32_t clusters=0, vertices=0, flags=0, reserved=0;
        std::uint64_t payloadHash=0;
    };
    static_assert(sizeof(NativeGeometryHeader)==48);
    struct NativePoint { float x,y,z; };
    static_assert(sizeof(NativePoint)==12);
    struct NativeGeometry { NativeGeometryHeader header; std::vector<NativePoint> vertices; };
    inline std::uint64_t GeometryHash(const std::vector<NativePoint>& points)
    {
        std::uint64_t hash=14695981039346656037ull;
        const auto* bytes=reinterpret_cast<const unsigned char*>(points.data());
        for(size_t i=0;i<points.size()*12;++i) { hash^=bytes[i]; hash*=1099511628211ull; }
        return hash;
    }
    inline bool ValidGeometry(const NativeGeometry& mesh)
    {
        const auto& h=mesh.header;
        if(std::memcmp(h.magic,"BZRGEO1\0",8)||h.version!=1||h.byteSize!=48||!h.producerPid||
            !h.clusters||h.clusters>256||h.flags||h.reserved||!h.vertices||h.vertices%3||h.vertices>3000000||h.vertices!=mesh.vertices.size()) return false;
        for(const auto& p:mesh.vertices)
            if(!std::isfinite(p.x)||!std::isfinite(p.y)||!std::isfinite(p.z)||std::abs(p.x)>100000||std::abs(p.y)>100000||std::abs(p.z)>100000) return false;
        return h.payloadHash==GeometryHash(mesh.vertices);
    }
    inline void WriteNativeGeometry(std::ostream& stream,NativeGeometry mesh)
    {
        mesh.header.vertices=static_cast<std::uint32_t>(mesh.vertices.size()); mesh.header.payloadHash=GeometryHash(mesh.vertices);
        if(!ValidGeometry(mesh)) throw std::runtime_error("invalid native geometry snapshot");
        stream.write(reinterpret_cast<const char*>(&mesh.header),48);
        stream.write(reinterpret_cast<const char*>(mesh.vertices.data()),static_cast<std::streamsize>(mesh.vertices.size()*12));
        if(!stream) throw std::runtime_error("write native geometry snapshot");
    }
    inline NativeGeometry ReadNativeGeometry(std::istream& stream)
    {
        NativeGeometry mesh; stream.read(reinterpret_cast<char*>(&mesh.header),48);
        const auto& h=mesh.header;
        if(!stream||std::memcmp(h.magic,"BZRGEO1\0",8)||h.version!=1||h.byteSize!=48||!h.producerPid||
            !h.clusters||h.clusters>256||h.flags||h.reserved||!h.vertices||h.vertices%3||h.vertices>3000000)
            throw std::runtime_error("invalid native geometry header");
        mesh.vertices.resize(mesh.header.vertices);
        stream.read(reinterpret_cast<char*>(mesh.vertices.data()),static_cast<std::streamsize>(mesh.vertices.size()*12));
        if(!stream||stream.peek()!=std::char_traits<char>::eof()||!ValidGeometry(mesh)) throw std::runtime_error("invalid native geometry payload");
        return mesh;
    }
}
