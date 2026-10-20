#pragma once
#include "frame_bridge_native_geometry.h"
#include <cstddef>
#include <limits>

namespace BZROpenShim::FrameBridge
{
    // Owned position bytes from a bounded indexed native draw operation.
    // Software-skinned poses can change; this decoder establishes no lifetime.
    // D3D11 DrawIndexed uses indexStart and vertexStart as its base vertex.
    struct NativeIndexedMesh
    {
        std::uint32_t stride=0, positionOffset=0, positionFloats=0;
        std::uint32_t vertexStart=0, vertexCount=0, indexStart=0, indexCount=0, indexBytes=0;
        float world[16]{};
    };
    inline std::vector<NativePoint> DecodeNativeIndexedMesh(const NativeIndexedMesh& draw,
        const std::vector<unsigned char>& vertexBytes,const std::vector<unsigned char>& indexBytes)
    {
        if((draw.positionFloats!=3&&draw.positionFloats!=4)||draw.stride<draw.positionFloats*4||draw.stride>256||
            draw.positionOffset>draw.stride-draw.positionFloats*4||!draw.vertexCount||draw.vertexCount>1000000||
            !draw.indexCount||draw.indexCount%3||draw.indexCount>3000000||(draw.indexBytes!=2&&draw.indexBytes!=4)||
            (std::uint64_t(draw.vertexStart)+draw.vertexCount)*draw.stride>vertexBytes.size()||
            (std::uint64_t(draw.indexStart)+draw.indexCount)*draw.indexBytes>indexBytes.size())
            throw std::runtime_error("native indexed mesh layout/range unsupported");
        if(draw.world[12]!=0||draw.world[13]!=0||draw.world[14]!=0||draw.world[15]!=1)
            throw std::runtime_error("native indexed mesh needs affine world transform");
        for(float element:draw.world) if(!std::isfinite(element)) throw std::runtime_error("native indexed mesh nonfinite world transform");
        std::vector<NativePoint> points; points.reserve(draw.indexCount);
        for(std::uint32_t i=0;i<draw.indexCount;++i) {
            const auto at=(std::size_t(draw.indexStart)+i)*draw.indexBytes;
            std::uint32_t index=0;
            if(draw.indexBytes==2) { std::uint16_t compactIndex=0; std::memcpy(&compactIndex,indexBytes.data()+at,2); index=compactIndex; }
            else std::memcpy(&index,indexBytes.data()+at,4);
            if(index>=draw.vertexCount) throw std::runtime_error("native index outside draw vertex range");
            float p[4]={0,0,0,1};
            std::memcpy(p,vertexBytes.data()+(std::size_t(draw.vertexStart)+index)*draw.stride+draw.positionOffset,draw.positionFloats*4);
            if(p[3]!=1) throw std::runtime_error("native indexed mesh position W unsupported");
            for(float element:p) if(!std::isfinite(element)) throw std::runtime_error("native indexed mesh nonfinite position");
            const auto* m=draw.world;
            NativePoint world{m[0]*p[0]+m[1]*p[1]+m[2]*p[2]+m[3],
                              m[4]*p[0]+m[5]*p[1]+m[6]*p[2]+m[7],
                              m[8]*p[0]+m[9]*p[1]+m[10]*p[2]+m[11]};
            if(!std::isfinite(world.x)||!std::isfinite(world.y)||!std::isfinite(world.z)||
                std::abs(world.x)>100000||std::abs(world.y)>100000||std::abs(world.z)>100000)
                throw std::runtime_error("native indexed mesh world bounds unsupported");
            points.push_back(world);
        }
        return points;
    }
    inline bool ValidNativeOccluderPair(const NativeGeometry& receivers,const NativeGeometry& casters)
    {
        return ValidGeometry(receivers)&&ValidGeometry(casters)&&
            receivers.header.producerPid==casters.header.producerPid&&receivers.header.missionGeneration==casters.header.missionGeneration&&
            receivers.vertices.size()+casters.vertices.size()<=3000000;
    }
}
