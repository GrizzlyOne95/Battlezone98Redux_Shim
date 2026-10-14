#include "test_check.h"
#include "visible_rt.h"
#include "frame_bridge_native_lease.h"
#include <d3d12.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace BZROpenShim::FrameBridge;
using Microsoft::WRL::ComPtr;
using OpenShimTest::Require;
namespace
{
    void Check(HRESULT hr) { Require(SUCCEEDED(hr),"DXR capture test operation"); }
    void Barrier(ID3D12GraphicsCommandList* list,ID3D12Resource* resource,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after)
    {
        D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; list->ResourceBarrier(1,&b);
    }
    struct Input
    {
        unsigned width=257,height=193;
        CameraSnapshot camera{};
        std::vector<float> depth;
        std::vector<unsigned char> scene,final;
    };
    Input Fixture(bool corner)
    {
        Input in; auto& c=in.camera; c.status=1; c.matrixSource=static_cast<unsigned>(CameraMatrixSource::Synthetic);
        c.width=in.width; c.height=in.height; c.observationQpc=1; c.cameraIdentity=1; c.name[0]='T';
        c.nearClip=.1f; c.farClip=100; c.view[0]=c.view[5]=c.view[10]=c.view[15]=1;
        const float q=c.farClip/(c.farClip-c.nearClip); c.projection[0]=1.2f; c.projection[5]=1.4f;
        c.projection[10]=-q; c.projection[11]=-q*c.nearClip; c.projection[14]=-1;
        in.depth.resize(in.width*in.height); in.scene.resize(in.depth.size()*4); in.final.resize(in.scene.size());
        for(unsigned y=0;y<in.height;++y) for(unsigned x=0;x<in.width;++x)
        {
            const auto i=y*in.width+x;
            const float viewY=(1-2*(y+.5f)/in.height)/c.projection[5];
            float distance=3;
            if(corner && viewY<0) distance=std::min(distance,-.8f/viewY);
            in.depth[i]=q-q*c.nearClip/distance;
            for(unsigned channel=0;channel<4;++channel) in.final[i*4+channel]=in.scene[i*4+channel]=channel==3?255:200;
            if(x<9&&y<9) { in.final[i*4]=255; in.final[i*4+1]=in.final[i*4+2]=0; }
        }
        return in;
    }
    Input ReadCapture(const char* path)
    {
        Input in; std::ifstream file(path,std::ios::binary); char magic[8]{}; file.read(magic,8);
        Require(std::memcmp(magic,"BZRCAP1\0",8)==0,"capture input magic");
        file.read(reinterpret_cast<char*>(&in.width),4); file.read(reinterpret_cast<char*>(&in.height),4);
        Require(in.width>=3&&in.height>=3&&in.width<=4096&&in.height<=4096,"bounded capture input extent");
        auto& c=in.camera; c.status=1; c.matrixSource=static_cast<unsigned>(CameraMatrixSource::CameraForShaders);
        c.width=in.width; c.height=in.height; c.observationQpc=1; c.cameraIdentity=1; c.name[0]='C';
        file.read(reinterpret_cast<char*>(c.projection),sizeof(c.projection)); file.read(reinterpret_cast<char*>(c.view),sizeof(c.view));
        file.read(reinterpret_cast<char*>(&c.nearClip),4); file.read(reinterpret_cast<char*>(&c.farClip),4);
        in.depth.resize(in.width*in.height); in.scene.resize(in.depth.size()*4); in.final.resize(in.scene.size());
        file.read(reinterpret_cast<char*>(in.depth.data()),static_cast<std::streamsize>(in.depth.size()*4));
        file.read(reinterpret_cast<char*>(in.scene.data()),static_cast<std::streamsize>(in.scene.size()));
        file.read(reinterpret_cast<char*>(in.final.data()),static_cast<std::streamsize>(in.final.size()));
        Require(file.good()&&file.peek()==std::char_traits<char>::eof(),"complete capture input");
        return in;
    }
    ComPtr<ID3D12Resource> Buffer(ID3D12Device* device,UINT64 bytes,D3D12_HEAP_TYPE type,D3D12_RESOURCE_STATES state)
    {
        D3D12_RESOURCE_DESC desc{}; desc.Dimension=D3D12_RESOURCE_DIMENSION_BUFFER; desc.Width=bytes; desc.Height=1;
        desc.DepthOrArraySize=desc.MipLevels=1; desc.SampleDesc.Count=1; desc.Layout=D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        D3D12_HEAP_PROPERTIES heap{}; heap.Type=type; ComPtr<ID3D12Resource> resource;
        Check(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&desc,state,nullptr,IID_PPV_ARGS(&resource))); return resource;
    }
    std::vector<unsigned char> Render(const Input& input,const NativeGeometry* native=nullptr,
        const NativeGeometry* replacement=nullptr,bool retire=false,const float* sun=nullptr,unsigned shadowMode=0,const NativeGeometry* casters=nullptr)
    {
        ComPtr<ID3D12Device> device; Check(D3D12CreateDevice(nullptr,D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device)));
        D3D12_COMMAND_QUEUE_DESC q{}; ComPtr<ID3D12CommandQueue> queue; Check(device->CreateCommandQueue(&q,IID_PPV_ARGS(&queue)));
        ComPtr<ID3D12CommandAllocator> allocator; Check(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&allocator)));
        ComPtr<ID3D12GraphicsCommandList> list; Check(device->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,allocator.Get(),nullptr,IID_PPV_ARGS(&list)));
        ComPtr<ID3D12Resource> textures[3],uploads[3];
        for(unsigned t=0;t<3;++t)
        {
            D3D12_RESOURCE_DESC desc{}; desc.Dimension=D3D12_RESOURCE_DIMENSION_TEXTURE2D; desc.Width=input.width; desc.Height=input.height;
            desc.DepthOrArraySize=desc.MipLevels=1; desc.SampleDesc.Count=1; desc.Format=t==0?DXGI_FORMAT_R32_FLOAT:DXGI_FORMAT_R8G8B8A8_UNORM;
            D3D12_HEAP_PROPERTIES heap{}; heap.Type=D3D12_HEAP_TYPE_DEFAULT;
            Check(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COPY_DEST,nullptr,IID_PPV_ARGS(&textures[t])));
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot{}; UINT64 bytes=0; device->GetCopyableFootprints(&desc,0,1,0,&foot,nullptr,nullptr,&bytes);
            uploads[t]=Buffer(device.Get(),bytes,D3D12_HEAP_TYPE_UPLOAD,D3D12_RESOURCE_STATE_GENERIC_READ);
            unsigned char* mapped=nullptr; D3D12_RANGE none{0,0}; Check(uploads[t]->Map(0,&none,reinterpret_cast<void**>(&mapped)));
            const auto* source=t==0?reinterpret_cast<const unsigned char*>(input.depth.data()):t==1?input.scene.data():input.final.data();
            for(unsigned y=0;y<input.height;++y) std::memcpy(mapped+foot.Offset+y*foot.Footprint.RowPitch,source+y*input.width*4,input.width*4);
            uploads[t]->Unmap(0,nullptr);
            D3D12_TEXTURE_COPY_LOCATION from{}; from.pResource=uploads[t].Get(); from.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; from.PlacedFootprint=foot;
            D3D12_TEXTURE_COPY_LOCATION to{}; to.pResource=textures[t].Get(); to.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            list->CopyTextureRegion(&to,0,0,0,&from,nullptr); Barrier(list.Get(),textures[t].Get(),D3D12_RESOURCE_STATE_COPY_DEST,D3D12_RESOURCE_STATE_COMMON);
        }
        VisibleRayTracing rt; rt.Initialize(device.Get(),textures[0].Get(),textures[1].Get(),textures[2].Get());
        if(native) rt.SetNativeGeometry(device.Get(),*native,casters);
        rt.SetTerrainSun(sun,shadowMode);
        rt.Record(list.Get(),input.camera);
        const auto desc=rt.FinalOutput()->GetDesc(); D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot{}; UINT64 bytes=0;
        device->GetCopyableFootprints(&desc,0,1,0,&foot,nullptr,nullptr,&bytes);
        auto readback=Buffer(device.Get(),bytes,D3D12_HEAP_TYPE_READBACK,D3D12_RESOURCE_STATE_COPY_DEST);
        Barrier(list.Get(),rt.FinalOutput(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COPY_SOURCE);
        D3D12_TEXTURE_COPY_LOCATION from{}; from.pResource=rt.FinalOutput(); from.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        D3D12_TEXTURE_COPY_LOCATION to{}; to.pResource=readback.Get(); to.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; to.PlacedFootprint=foot;
        list->CopyTextureRegion(&to,0,0,0,&from,nullptr);
        Barrier(list.Get(),rt.FinalOutput(),D3D12_RESOURCE_STATE_COPY_SOURCE,D3D12_RESOURCE_STATE_COMMON); Check(list->Close());
        ID3D12CommandList* lists[]={list.Get()}; queue->ExecuteCommandLists(1,lists);
        ComPtr<ID3D12Fence> fence; Check(device->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence)));
        HANDLE event=CreateEventW(nullptr,FALSE,FALSE,nullptr); Require(event!=nullptr,"DXR test event");
        Check(queue->Signal(fence.Get(),1)); Check(fence->SetEventOnCompletion(1,event)); Require(WaitForSingleObject(event,5000)==WAIT_OBJECT_0,"bounded DXR completion");
        if(replacement||retire) {
            // Exercise actual in-place live-resource replacement/retirement
            // only after the first submission has completed on the GPU.
            if(replacement) rt.SetNativeGeometry(device.Get(),*replacement); else rt.ClearNativeGeometry();
            Check(allocator->Reset()); Check(list->Reset(allocator.Get(),nullptr));
            rt.Record(list.Get(),input.camera);
            Barrier(list.Get(),rt.FinalOutput(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COPY_SOURCE);
            list->CopyTextureRegion(&to,0,0,0,&from,nullptr);
            Barrier(list.Get(),rt.FinalOutput(),D3D12_RESOURCE_STATE_COPY_SOURCE,D3D12_RESOURCE_STATE_COMMON);
            Check(list->Close()); queue->ExecuteCommandLists(1,lists);
            Check(queue->Signal(fence.Get(),2)); Check(fence->SetEventOnCompletion(2,event));
            Require(WaitForSingleObject(event,5000)==WAIT_OBJECT_0,"bounded replacement DXR completion");
        }
        unsigned char* mapped=nullptr; D3D12_RANGE range{0,static_cast<SIZE_T>(bytes)}; Check(readback->Map(0,&range,reinterpret_cast<void**>(&mapped)));
        std::vector<unsigned char> pixels(input.width*input.height*4);
        for(unsigned y=0;y<input.height;++y) std::memcpy(pixels.data()+y*input.width*4,mapped+foot.Offset+y*foot.Footprint.RowPitch,input.width*4);
        const D3D12_RANGE none{0,0}; readback->Unmap(0,&none); CloseHandle(event);
        std::printf("DXR_CAPTURE triangles_capacity=%u native_triangles=%u caster_triangles=%u pixels=%u\n",rt.TriangleCapacity(),rt.NativeTriangleCount(),rt.NativeCasterTriangleCount(),input.width*input.height); return pixels;
    }
}
int main(int argc,char** argv)
{
    if(argc==3||argc==4||argc==8||argc==9)
    {
        NativeGeometry mesh;
        if(argc>=4) { std::ifstream geometry(argv[3],std::ios::binary); mesh=ReadNativeGeometry(geometry); }
        float sun[3]{}; unsigned mode=0;
        if(argc>=8) {
            for(unsigned i=0;i<3;++i) { char* end=nullptr; sun[i]=std::strtof(argv[4+i],&end); Require(end&&*end==0,"numeric sun direction"); }
            Require(ValidTerrainSun(sun),"unit captured sun direction");
            const std::string name(argv[7]); mode=name=="preview"?1:name=="mask"?2:0;
            Require(mode!=0,"terrain shadow preview or mask mode");
        }
        NativeGeometry casters;
        if(argc==9) { std::ifstream geometry(argv[8],std::ios::binary); casters=ReadNativeGeometry(geometry); }
        const auto input=ReadCapture(argv[1]); const auto pixels=Render(input,argc>=4?&mesh:nullptr,nullptr,false,sun,mode,argc==9?&casters:nullptr);
        std::ofstream file(argv[2],std::ios::binary); file.write(reinterpret_cast<const char*>(pixels.data()),static_cast<std::streamsize>(pixels.size()));
        Require(file.good(),"save captured DXR RGBA output"); return 0;
    }
    Require(argc==1,"usage: frame_bridge_visible_rt_gpu_tests [capture.bin output.rgba [native.bin [sunX sunY sunZ preview|mask [casters.bin]]]]");
    for(bool corner : {false,true})
    {
        const auto input=Fixture(corner); const auto pixels=Render(input); unsigned darker=0;
        for(unsigned y=0;y<input.height;++y) for(unsigned x=0;x<input.width;++x)
        {
            const auto i=(y*input.width+x)*4;
            Require(pixels[i]<=input.final[i]&&pixels[i+1]<=input.final[i+1]&&pixels[i+2]<=input.final[i+2]&&pixels[i+3]==input.final[i+3],"AO darkens RGB only and preserves alpha");
            if(x<9&&y<9) Require(std::memcmp(pixels.data()+i,input.final.data()+i,4)==0,"distinct UI pixels unchanged");
            if(pixels[i]+2<input.final[i]) ++darker;
        }
        if(corner) Require(darker>100,"perpendicular wall/floor produce hardware ray occlusion");
        else Require(darker==0,"single plane has no self-occlusion");
        std::printf("PASS DXR analytic %s darker_pixels=%u\n",corner?"corner":"plane",darker);
    }
    // A distant sloping plane quantized to D24 has no geometric occluder.
    // Its coarse two-pixel mesh is not fine enough for a four-unit AO radius:
    // decline that geometry rather than turn quantization into black flecks.
    auto distant=Fixture(false); distant.camera.farClip=1000;
    const float q=1000.0f/(1000.0f-distant.camera.nearClip);
    distant.camera.projection[10]=-q; distant.camera.projection[11]=-q*distant.camera.nearClip;
    for(unsigned y=0;y<distant.height;++y) for(unsigned x=0;x<distant.width;++x)
    {
        const float nx=(2*(x+.5f)/distant.width-1)/distant.camera.projection[0];
        const float ny=(1-2*(y+.5f)/distant.height)/distant.camera.projection[5];
        const float distance=110.0f/(1+.12f*nx+.06f*ny);
        const float z=q-q*distant.camera.nearClip/distance;
        distant.depth[y*distant.width+x]=std::round(z*16777215.0f)/16777215.0f;
    }
    const auto pixels=Render(distant);
    Require(pixels==distant.final,"under-resolved distant D24 plane has no false self-occlusion");
    std::puts("PASS DXR coarse distant D24 plane preserved without self-shadow speckles");
    // This wall is not in the depth image: native world triangles alone must
    // cause AO, and translating the camera/world together must preserve it.
    auto plane=Fixture(false); NativeGeometry native;
    native.header.producerPid=1; native.header.missionGeneration=1; native.header.clusters=1;
    native.vertices={{-20,-.35f,-10},{20,-.35f,-10},{-20,-.35f,2},
                     {20,-.35f,-10},{20,-.35f,2},{-20,-.35f,2}};
    native.header.vertices=6; native.header.payloadHash=GeometryHash(native.vertices);
    auto coplanar=native;
    coplanar.vertices={{-20,-20,-3},{20,-20,-3},{-20,20,-3},
                       {20,-20,-3},{20,20,-3},{-20,20,-3}};
    coplanar.header.payloadHash=GeometryHash(coplanar.vertices);
    Require(Render(plane,&coplanar)==plane.final,"duplicate coplanar native terrain adds no false self-occlusion");
    auto worldOcclusion=Render(plane,&native); unsigned nativeDarker=0;
    Require(Render(plane,&native,&coplanar)==plane.final,"replacement native BLAS removes old occluder after GPU completion");
    Require(Render(plane,&native,nullptr,true)==plane.final,"retiring native BLAS restores depth-only rays after GPU completion");
    for(size_t i=0;i<worldOcclusion.size();i+=4) if(worldOcclusion[i]+2<plane.final[i]) ++nativeDarker;
    Require(nativeDarker>100,"native occluder absent from depth affects real hardware rays");
    auto translated=plane; translated.camera.view[3]=-37; translated.camera.view[7]=12; translated.camera.view[11]=-19;
    auto moved=native; for(auto& p:moved.vertices) { p.x+=37; p.y-=12; p.z+=19; }
    moved.header.payloadHash=GeometryHash(moved.vertices);
    const auto movedPixels=Render(translated,&moved);
    unsigned translationMax=0,translationOverOne=0;
    for(size_t i=0;i<movedPixels.size();++i) {
        unsigned delta=static_cast<unsigned>(std::abs(int(movedPixels[i])-int(worldOcclusion[i])));
        translationMax=std::max(translationMax,delta); if(delta>1)++translationOverOne;
    }
    std::printf("DXR native translation max_channel_delta=%u channels_over_one=%u\n",translationMax,translationOverOne);
    Require(translationMax<=1,"native and visible world-space rays agree within one SDR quantization step under camera translation");
    // A rotated world/camera must also retain the same view-space result.
    auto rotated=plane; rotated.camera.view[0]=0; rotated.camera.view[2]=1; rotated.camera.view[8]=-1; rotated.camera.view[10]=0;
    auto turn=native; for(auto& p:turn.vertices) { const float x=p.x; p.x=-p.z; p.z=x; }
    turn.header.payloadHash=GeometryHash(turn.vertices);
    Require(Render(rotated,&turn)==worldOcclusion,"native world rays agree under camera rotation");
    std::printf("PASS DXR native occluder absent from depth darker_pixels=%u; translation and rotation preserved\n",nativeDarker);
    // Sun rays must see an offscreen native occluder eight meters beyond the
    // receiver, outside the four-meter AO radius. Half the plane is blocked.
    auto sunlight=coplanar;
    const NativePoint wall[]={{-20,-20,5},{0,-20,5},{-20,20,5},
                             {0,-20,5},{0,20,5},{-20,20,5}};
    sunlight.vertices.insert(sunlight.vertices.end(),std::begin(wall),std::end(wall));
    sunlight.header.vertices=static_cast<unsigned>(sunlight.vertices.size());
    sunlight.header.payloadHash=GeometryHash(sunlight.vertices);
    const float sun[3]={0,0,1},away[3]={0,0,-1},invalid[3]={0,0,2};
    Require(Render(plane,&sunlight)==plane.final,"distant sun occluder adds no short-range AO");
    Require(Render(plane,&sunlight,nullptr,false,invalid,1)==plane.final,"invalid sun fails closed");
    Require(Render(plane,&sunlight,nullptr,false,away,1)==plane.final,"backlit receiver adds no shadow multiplication");
    Require(Render(plane,nullptr,nullptr,false,sun,1)==plane.final,"missing native geometry disables sun shadows");
    for(float value : {1.0f,NAN}) {
        auto unavailable=plane; std::fill(unavailable.depth.begin(),unavailable.depth.end(),value);
        Require(Render(unavailable,&sunlight,nullptr,false,sun,2)==unavailable.final,"clear/nonfinite depth never launches terrain sun receiver rays");
    }
    const auto shadow=Render(plane,&sunlight,nullptr,false,sun,1);
    const auto mask=Render(plane,&sunlight,nullptr,false,sun,2);
    auto separateCaster=coplanar; separateCaster.vertices.assign(std::begin(wall),std::end(wall));
    separateCaster.header.payloadHash=GeometryHash(separateCaster.vertices);
    Require(Render(plane,&coplanar,nullptr,false,sun,1,&separateCaster)==shadow,"separate owned caster casts same offscreen sun shadow on terrain");
    Require(Render(plane,&coplanar,nullptr,false,sun,2,&separateCaster)==mask,"separate caster preserves terrain-only diagnostic receivers");
    auto terrainBehind=coplanar; for(auto& v:terrainBehind.vertices) v.z-=2;
    terrainBehind.header.payloadHash=GeometryHash(terrainBehind.vertices);
    Require(Render(plane,&terrainBehind,nullptr,false,sun,2,&coplanar)==plane.final,"caster geometry never becomes a terrain receiver");
    unsigned shadowed=0,marked=0;
    for(unsigned y=0;y<plane.height;++y) for(unsigned x=0;x<plane.width;++x) {
        const auto i=(y*plane.width+x)*4;
        Require(shadow[i+3]==plane.final[i+3]&&mask[i+3]==plane.final[i+3],"sun preview preserves alpha");
        if(x<9&&y<9) { Require(std::memcmp(shadow.data()+i,plane.final.data()+i,4)==0&&std::memcmp(mask.data()+i,plane.final.data()+i,4)==0,"sun preview preserves distinct HUD"); continue; }
        if(shadow[i]+2<plane.final[i]) ++shadowed;
        if(mask[i]>220&&mask[i+1]<50&&mask[i+2]>220) ++marked;
        if(x>plane.width/2+1) Require(std::memcmp(shadow.data()+i,plane.final.data()+i,4)==0,"sunlit half unchanged");
    }
    Require(shadowed>20000&&marked==shadowed,"offscreen native wall shadows only blocked half of terrain receiver");
    Require(Render(plane,&coplanar,nullptr,false,sun,1)==plane.final,"native plane has no sun self-shadow");
    auto behind=coplanar; for(auto& v:behind.vertices) v.z-=2;
    behind.header.payloadHash=GeometryHash(behind.vertices);
    Require(Render(plane,&behind,nullptr,false,sun,2)==plane.final,"depth mismatching native receiver is not marked");
    auto movedSunlight=sunlight;
    for(auto& v:movedSunlight.vertices) { v.x+=37; v.y-=12; v.z+=19; }
    movedSunlight.header.payloadHash=GeometryHash(movedSunlight.vertices);
    const auto translatedShadow=Render(translated,&movedSunlight,nullptr,false,sun,1);
    unsigned shadowTranslationChanged=0;
    for(unsigned y=0;y<plane.height;++y) for(unsigned x=0;x<plane.width;++x) {
        const auto i=(y*plane.width+x)*4;
        if(std::memcmp(translatedShadow.data()+i,shadow.data()+i,4)!=0) {
            ++shadowTranslationChanged;
            // The center sample lies exactly on the zero-width hard shadow
            // boundary. Floating world translation may choose either side.
            Require(x==plane.width/2,"translated sun shadows differ only on exact hard-shadow boundary");
        }
    }
    std::printf("DXR sun translation changed_boundary_pixels=%u\n",shadowTranslationChanged);
    auto turnedSunlight=sunlight;
    for(auto& v:turnedSunlight.vertices) { float x=v.x; v.x=-v.z; v.z=x; }
    turnedSunlight.header.payloadHash=GeometryHash(turnedSunlight.vertices);
    const float turnedSun[3]={-1,0,0};
    Require(Render(rotated,&turnedSunlight,nullptr,false,turnedSun,1)==shadow,"sun shadows preserve world camera rotation");
    std::printf("PASS DXR terrain sunlight offscreen wall blocked_pixels=%u marked_pixels=%u\n",shadowed,marked);
    // MSAA minimum depth is not necessarily the depth at the pixel center.
    // A flat floor sampled below the center must still match its native plane.
    auto sampleFloor=Fixture(false); auto nativeFloor=coplanar;
    nativeFloor.vertices={{-1000,-.8f,-1000},{-1000,-.8f,-.1f},{1000,-.8f,-1000},
                          {1000,-.8f,-1000},{-1000,-.8f,-.1f},{1000,-.8f,-.1f}};
    nativeFloor.header.payloadHash=GeometryHash(nativeFloor.vertices);
    const float floorQ=sampleFloor.camera.farClip/(sampleFloor.camera.farClip-sampleFloor.camera.nearClip);
    for(unsigned y=0;y<sampleFloor.height;++y) for(unsigned x=0;x<sampleFloor.width;++x) {
        const float sampleY=(1-2*(y+.5f+.4375f)/sampleFloor.height)/sampleFloor.camera.projection[5];
        const float distance=sampleY<0?-.8f/sampleY:10000;
        sampleFloor.depth[y*sampleFloor.width+x]=distance<sampleFloor.camera.farClip?floorQ-floorQ*sampleFloor.camera.nearClip/distance:1;
    }
    const float upwardSun[3]={0,1,0};
    const auto sampleMask=Render(sampleFloor,&nativeFloor,nullptr,false,upwardSun,2);
    unsigned sampleReceivers=0;
    for(unsigned y=110;y<125;++y) for(unsigned x=30;x<220;++x) {
        const auto i=(y*sampleFloor.width+x)*4;
        if(sampleMask[i]<60&&sampleMask[i+1]>210&&sampleMask[i+2]<100) ++sampleReceivers;
    }
    Require(sampleReceivers==15*190,"native floor receiver survives a real within-pixel MSAA depth offset");
    std::printf("PASS DXR native MSAA plane receiver pixels=%u\n",sampleReceivers);
    return OpenShimTest::ExitCode();
}
