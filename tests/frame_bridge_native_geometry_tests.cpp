#include "frame_bridge_native_geometry.h"
#include "test_check.h"
#include <sstream>
#include <limits>
using namespace BZROpenShim::FrameBridge;
using OpenShimTest::Require;
int main()
{
    NativeGeometry mesh; mesh.header.producerPid=12; mesh.header.missionGeneration=1; mesh.header.clusters=1;
    mesh.vertices={{0,0,0},{1,0,0},{0,1,0}};
    std::stringstream stream(std::ios::in|std::ios::out|std::ios::binary); WriteNativeGeometry(stream,mesh);
    auto loaded=ReadNativeGeometry(stream); Require(ValidGeometry(loaded),"valid native geometry roundtrip");
    Require(loaded.vertices[1].x==1,"native world position preserved");
    loaded.header.missionGeneration=0; Require(ValidGeometry(loaded),"initial native mission generation zero is valid");
    loaded.vertices[0].y=1; Require(!ValidGeometry(loaded),"payload mutation detected");
    const auto bytes=stream.str();
    for(int kind=0;kind<6;++kind)
    {
        auto bad=bytes;
        if(kind==0) bad.resize(47);
        if(kind==1) bad.pop_back();
        if(kind==2) bad.push_back('x');
        if(kind==3) bad[0]='x';
        if(kind==4) { uint32_t size=4000000; memcpy(bad.data()+28,&size,4); }
        if(kind==5) { float value=std::numeric_limits<float>::quiet_NaN(); memcpy(bad.data()+48,&value,4); }
        std::stringstream input(bad,std::ios::in|std::ios::binary); bool rejected=false;
        try { ReadNativeGeometry(input); } catch(const std::exception&) { rejected=true; }
        Require(rejected,"malformed native geometry declined");
    }
    return OpenShimTest::ExitCode();
}
