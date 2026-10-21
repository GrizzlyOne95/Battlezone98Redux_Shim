#include "frame_bridge_native_mesh.h"
#include "test_check.h"
#include <limits>
using namespace BZROpenShim::FrameBridge;
using OpenShimTest::Require;
int main()
{
    NativeIndexedMesh draw; draw.stride=24; draw.positionOffset=4; draw.positionFloats=3;
    draw.vertexStart=1; draw.vertexCount=3; draw.indexStart=2; draw.indexCount=3; draw.indexBytes=2;
    draw.world[0]=0; draw.world[2]=-1; draw.world[5]=2; draw.world[8]=1; draw.world[15]=1;
    draw.world[3]=37; draw.world[7]=-12; draw.world[11]=19;
    std::vector<unsigned char> vertices(4*24,0x7f),indices(5*2,0xff);
    const float points[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    const std::uint16_t order[]={2,0,1};
    for(unsigned i=0;i<3;++i) std::memcpy(vertices.data()+(1+i)*24+4,points[i],12);
    std::memcpy(indices.data()+4,order,6);
    const auto decoded=DecodeNativeIndexedMesh(draw,vertices,indices);
    Require(decoded.size()==3&&decoded[0].x==28&&decoded[0].y==4&&decoded[0].z==26,"stride/offset/base vertex/index start and affine transform decoded");
    Require(decoded[1].x==34&&decoded[1].y==-8&&decoded[1].z==20,"actual index order preserved");
    draw.positionFloats=4;
    for(unsigned i=0;i<3;++i) { float w=1; std::memcpy(vertices.data()+(1+i)*24+16,&w,4); }
    Require(DecodeNativeIndexedMesh(draw,vertices,indices)[0].z==26,"FLOAT4 unit W matches FLOAT3");
    auto wide=draw; wide.indexBytes=4; std::vector<unsigned char> wideIndices(5*4,0xff);
    const std::uint32_t wideOrder[]={2,0,1}; std::memcpy(wideIndices.data()+8,wideOrder,12);
    Require(DecodeNativeIndexedMesh(wide,vertices,wideIndices)[0].x==28,"32-bit indices supported");
    for(unsigned fault=0;fault<12;++fault) {
        auto bad=draw; auto v=vertices; auto ix=indices;
        if(fault==0)bad.positionOffset=22;
        if(fault==1)bad.vertexStart=UINT32_MAX;
        if(fault==2)bad.indexStart=UINT32_MAX;
        if(fault==3)bad.indexCount=2;
        if(fault==4)bad.indexBytes=1;
        if(fault==5)v.pop_back();
        if(fault==6)ix.pop_back();
        if(fault==7) { std::uint16_t index=3; std::memcpy(ix.data()+4,&index,2); }
        if(fault==8)bad.world[15]=0;
        if(fault==9)bad.world[0]=std::numeric_limits<float>::quiet_NaN();
        if(fault==10) { float w=2; std::memcpy(v.data()+3*24+16,&w,4); }
        if(fault==11) { float x=std::numeric_limits<float>::infinity(); std::memcpy(v.data()+3*24+4,&x,4); }
        bool rejected=false; try { DecodeNativeIndexedMesh(bad,v,ix); } catch(const std::exception&) { rejected=true; }
        Require(rejected,"malformed native indexed draw rejected");
    }
    NativeGeometry terrain,objects; terrain.header.producerPid=12; terrain.header.clusters=1; terrain.vertices=decoded;
    terrain.header.vertices=3; terrain.header.payloadHash=GeometryHash(terrain.vertices); objects=terrain;
    Require(ValidNativeOccluderPair(terrain,objects),"owned receiver/caster pair accepted");
    objects.header.producerPid=13; Require(!ValidNativeOccluderPair(terrain,objects),"foreign caster PID rejected");
    objects=terrain; objects.header.missionGeneration=1; Require(!ValidNativeOccluderPair(terrain,objects),"foreign caster mission rejected");
    return OpenShimTest::ExitCode();
}
