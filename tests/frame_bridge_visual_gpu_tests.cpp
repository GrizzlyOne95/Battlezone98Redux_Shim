#include "test_check.h"
#include "visual_enhancements.h"
#include <d3d12.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <fstream>
#include <stdexcept>
using namespace BZROpenShim::FrameBridge;
using Microsoft::WRL::ComPtr;
using OpenShimTest::Require;
namespace
{
    void Check(HRESULT hr) { Require(SUCCEEDED(hr),"visual GPU operation"); }
    void Barrier(ID3D12GraphicsCommandList* list,ID3D12Resource* resource,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after)
    {
        D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; list->ResourceBarrier(1,&b);
    }
    struct Input
    {
        unsigned width=67,height=33;
        CameraSnapshot camera{};
        std::vector<float> depth;
        std::vector<unsigned char> scene,final;
    };
    Input Fixture()
    {
        Input in; auto& c=in.camera; c.status=1; c.matrixSource=static_cast<unsigned>(CameraMatrixSource::Synthetic);
        c.width=in.width; c.height=in.height; c.observationQpc=1; c.cameraIdentity=1; c.name[0]='V';
        c.nearClip=.1f; c.farClip=1000; c.view[0]=c.view[5]=c.view[10]=c.view[15]=1;
        const float q=c.farClip/(c.farClip-c.nearClip); c.projection[0]=1.2f; c.projection[5]=1.4f;
        c.projection[10]=-q; c.projection[11]=-q*c.nearClip; c.projection[14]=-1;
        in.depth.resize(in.width*in.height); in.scene.resize(in.depth.size()*4); in.final.resize(in.scene.size());
        for(unsigned y=0;y<in.height;++y) for(unsigned x=0;x<in.width;++x)
        {
            const auto i=y*in.width+x; const float distance=x<in.width/2?2.0f:50.0f;
            in.depth[i]=q-q*c.nearClip/distance;
            for(unsigned ch=0;ch<4;++ch) in.scene[i*4+ch]=in.final[i*4+ch]=ch==3?177:40;
            if(x<5&&y<5) { in.final[i*4]=255; in.final[i*4+1]=in.final[i*4+2]=0; }
        }
        in.depth[4*in.width+10]=std::numeric_limits<float>::quiet_NaN();
        for(unsigned ch=0;ch<3;++ch) in.final[(20*in.width+55)*4+ch]=44; // Small raster/postprocess difference.
        in.depth[4*in.width+11]=1; return in;
    }
    Input ReadCapture(const char* path)
    {
        Input in; std::ifstream file(path,std::ios::binary); char magic[8]{}; file.read(magic,8);
        Require(std::memcmp(magic,"BZRCAP1\0",8)==0,"visual capture magic");
        file.read(reinterpret_cast<char*>(&in.width),4); file.read(reinterpret_cast<char*>(&in.height),4);
        Require(in.width>=3&&in.height>=3&&in.width<=4096&&in.height<=4096,"bounded visual capture extent");
        auto& c=in.camera; c.status=1; c.matrixSource=static_cast<unsigned>(CameraMatrixSource::CameraForShaders);
        c.width=in.width; c.height=in.height; c.observationQpc=1; c.cameraIdentity=1; c.name[0]='C';
        file.read(reinterpret_cast<char*>(c.projection),sizeof(c.projection)); file.read(reinterpret_cast<char*>(c.view),sizeof(c.view));
        file.read(reinterpret_cast<char*>(&c.nearClip),4); file.read(reinterpret_cast<char*>(&c.farClip),4);
        in.depth.resize(in.width*in.height); in.scene.resize(in.depth.size()*4); in.final.resize(in.scene.size());
        file.read(reinterpret_cast<char*>(in.depth.data()),static_cast<std::streamsize>(in.depth.size()*4));
        file.read(reinterpret_cast<char*>(in.scene.data()),static_cast<std::streamsize>(in.scene.size()));
        file.read(reinterpret_cast<char*>(in.final.data()),static_cast<std::streamsize>(in.final.size()));
        Require(file.good()&&file.peek()==std::char_traits<char>::eof(),"complete visual capture input"); return in;
    }
    ComPtr<ID3D12Resource> Buffer(ID3D12Device* device,UINT64 bytes,D3D12_HEAP_TYPE type,D3D12_RESOURCE_STATES state)
    {
        D3D12_RESOURCE_DESC d{}; d.Dimension=D3D12_RESOURCE_DIMENSION_BUFFER; d.Width=bytes; d.Height=1;
        d.DepthOrArraySize=d.MipLevels=1; d.SampleDesc.Count=1; d.Layout=D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        D3D12_HEAP_PROPERTIES h{}; h.Type=type; ComPtr<ID3D12Resource> r;
        Check(device->CreateCommittedResource(&h,D3D12_HEAP_FLAG_NONE,&d,state,nullptr,IID_PPV_ARGS(&r))); return r;
    }
    std::vector<unsigned char> Render(const Input& input,const VisualSettings& settings,bool bgra=false)
    {
        ComPtr<ID3D12Device> device; Check(D3D12CreateDevice(nullptr,D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device)));
        D3D12_COMMAND_QUEUE_DESC q{}; ComPtr<ID3D12CommandQueue> queue; Check(device->CreateCommandQueue(&q,IID_PPV_ARGS(&queue)));
        ComPtr<ID3D12CommandAllocator> allocator; Check(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&allocator)));
        ComPtr<ID3D12GraphicsCommandList> list; Check(device->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,allocator.Get(),nullptr,IID_PPV_ARGS(&list)));
        ComPtr<ID3D12Resource> textures[3],uploads[3];
        for(unsigned t=0;t<3;++t)
        {
            D3D12_RESOURCE_DESC d{}; d.Dimension=D3D12_RESOURCE_DIMENSION_TEXTURE2D; d.Width=input.width; d.Height=input.height;
            d.DepthOrArraySize=d.MipLevels=1; d.SampleDesc.Count=1;
            d.Format=t==0?DXGI_FORMAT_R32_FLOAT:bgra?DXGI_FORMAT_B8G8R8A8_UNORM:DXGI_FORMAT_R8G8B8A8_UNORM;
            D3D12_HEAP_PROPERTIES h{}; h.Type=D3D12_HEAP_TYPE_DEFAULT;
            Check(device->CreateCommittedResource(&h,D3D12_HEAP_FLAG_NONE,&d,D3D12_RESOURCE_STATE_COPY_DEST,nullptr,IID_PPV_ARGS(&textures[t])));
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot{}; UINT64 bytes=0; device->GetCopyableFootprints(&d,0,1,0,&foot,nullptr,nullptr,&bytes);
            uploads[t]=Buffer(device.Get(),bytes,D3D12_HEAP_TYPE_UPLOAD,D3D12_RESOURCE_STATE_GENERIC_READ);
            unsigned char* mapped=nullptr; D3D12_RANGE none{0,0}; Check(uploads[t]->Map(0,&none,reinterpret_cast<void**>(&mapped)));
            const auto* source=t==0?reinterpret_cast<const unsigned char*>(input.depth.data()):t==1?input.scene.data():input.final.data();
            for(unsigned y=0;y<input.height;++y)
            {
                auto* row=mapped+foot.Offset+y*foot.Footprint.RowPitch; std::memcpy(row,source+y*input.width*4,input.width*4);
                if(t&&bgra) for(unsigned x=0;x<input.width;++x) std::swap(row[x*4],row[x*4+2]);
            }
            uploads[t]->Unmap(0,nullptr);
            D3D12_TEXTURE_COPY_LOCATION from{}; from.pResource=uploads[t].Get(); from.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; from.PlacedFootprint=foot;
            D3D12_TEXTURE_COPY_LOCATION to{}; to.pResource=textures[t].Get(); to.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            list->CopyTextureRegion(&to,0,0,0,&from,nullptr); Barrier(list.Get(),textures[t].Get(),D3D12_RESOURCE_STATE_COPY_DEST,D3D12_RESOURCE_STATE_COMMON);
        }
        VisualEnhancements visuals; visuals.Initialize(device.Get(),textures[0].Get(),textures[1].Get(),textures[1].Get(),textures[2].Get());
        visuals.Record(list.Get(),input.camera); // Exercise reuse and clear previous bloom.
        visuals.Record(list.Get(),input.camera,settings);
        auto invalid=settings; invalid.contrast=std::numeric_limits<float>::infinity(); bool rejected=false;
        try { visuals.Record(list.Get(),input.camera,invalid); } catch(const std::runtime_error&) { rejected=true; }
        Require(rejected,"nonfinite visual settings rejected before GPU commands");
        const auto d=visuals.FinalOutput()->GetDesc(); D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot{}; UINT64 bytes=0;
        device->GetCopyableFootprints(&d,0,1,0,&foot,nullptr,nullptr,&bytes);
        auto readback=Buffer(device.Get(),bytes,D3D12_HEAP_TYPE_READBACK,D3D12_RESOURCE_STATE_COPY_DEST);
        Barrier(list.Get(),visuals.FinalOutput(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COPY_SOURCE);
        D3D12_TEXTURE_COPY_LOCATION from{}; from.pResource=visuals.FinalOutput(); from.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        D3D12_TEXTURE_COPY_LOCATION to{}; to.pResource=readback.Get(); to.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; to.PlacedFootprint=foot;
        list->CopyTextureRegion(&to,0,0,0,&from,nullptr); Check(list->Close());
        ID3D12CommandList* lists[]={list.Get()}; queue->ExecuteCommandLists(1,lists);
        ComPtr<ID3D12Fence> fence; Check(device->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence)));
        HANDLE event=CreateEventW(nullptr,FALSE,FALSE,nullptr); Require(event!=nullptr,"visual test event");
        Check(queue->Signal(fence.Get(),1)); Check(fence->SetEventOnCompletion(1,event)); Require(WaitForSingleObject(event,5000)==WAIT_OBJECT_0,"bounded visual GPU completion");
        unsigned char* mapped=nullptr; D3D12_RANGE range{0,static_cast<SIZE_T>(bytes)}; Check(readback->Map(0,&range,reinterpret_cast<void**>(&mapped)));
        std::vector<unsigned char> pixels(input.width*input.height*4);
        for(unsigned y=0;y<input.height;++y) std::memcpy(pixels.data()+y*input.width*4,mapped+foot.Offset+y*foot.Footprint.RowPitch,input.width*4);
        const D3D12_RANGE none{0,0}; readback->Unmap(0,&none); CloseHandle(event); return pixels;
    }
    void PreservedHUD(const Input& input,const std::vector<unsigned char>& pixels)
    {
        for(unsigned y=0;y<input.height;++y) for(unsigned x=0;x<input.width;++x)
        {
            const auto i=(y*input.width+x)*4;
            Require(pixels[i+3]==input.final[i+3],"final alpha preserved");
            if(x<5&&y<5) Require(std::memcmp(pixels.data()+i,input.final.data()+i,4)==0,"distinct HUD pixels exactly preserved");
        }
    }
}
int main(int argc,char** argv)
{
    try
    {
    if(argc==3)
    {
        const auto input=ReadCapture(argv[1]); const auto pixels=Render(input,{});
        std::ofstream file(argv[2],std::ios::binary); file.write(reinterpret_cast<const char*>(pixels.data()),static_cast<std::streamsize>(pixels.size()));
        Require(file.good(),"save captured cinematic output"); return OpenShimTest::ExitCode();
    }
    Require(argc==1,"usage: frame_bridge_visual_gpu_tests [capture.bin output.rgba]");
    VisualSettings neutral{}; neutral.exposure=neutral.contrast=neutral.saturation=1; neutral.bloomStrength=neutral.hazeDensity=0;
    auto input=Fixture();
    for(bool bgra:{false,true})
    {
        const auto pixels=Render(input,neutral,bgra); PreservedHUD(input,pixels);
        for(unsigned i=0;i<pixels.size();++i) Require(std::abs(int(pixels[i])-int(input.final[i]))<=1,"neutral preset preserves every odd-extent RGBA/BGRA pixel");
    }
    auto haze=neutral; haze.hazeDensity=.02f; haze.hazeStart=0; haze.hazeColor={.7f,.75f,.8f};
    auto pixels=Render(input,haze); PreservedHUD(input,pixels);
    const auto blue=[&](unsigned x,unsigned y){return pixels[(y*input.width+x)*4+2];};
    Require(blue(50,16)>blue(10,16)+60,"distant depth receives stronger haze than nearby depth");
    Require(blue(10,4)==40&&blue(11,4)==40,"NaN depth and clear sky receive no haze");
    auto bloom=neutral; bloom.bloomThreshold=.1f; bloom.bloomStrength=1;
    for(unsigned y=15;y<18;++y) for(unsigned x=34;x<37;++x)
        for(unsigned ch=0;ch<3;++ch) input.scene[(y*input.width+x)*4+ch]=input.final[(y*input.width+x)*4+ch]=255;
    pixels=Render(input,bloom); PreservedHUD(input,pixels); unsigned halo=0;
    for(unsigned y=10;y<24;++y) for(unsigned x=28;x<44;++x)
        if((x<34||x>=37||y<15||y>=18)&&pixels[(y*input.width+x)*4]>42) ++halo;
    Require(halo>20,"scene highlight blooms into surrounding pixels");
    Require(pixels[(4*input.width+8)*4]==40,"bright HUD does not enter scene bloom");
    bloom.bloomThreshold=1; pixels=Render(input,bloom);
    for(unsigned i=0;i<pixels.size();++i) Require(std::abs(int(pixels[i])-int(input.final[i]))<=1,"bloom history cleared at threshold one");
    auto grade=neutral; grade.exposure=1.3f; grade.saturation=1.2f;
    pixels=Render(input,grade); PreservedHUD(input,pixels);
    Require(pixels[(20*input.width+20)*4]>input.final[(20*input.width+20)*4]+3,"exposure changes scene independently of haze/bloom");
    Require(pixels[(20*input.width+55)*4]>input.final[(20*input.width+55)*4]+3,"small raster differences retain enhancement without binary speckles");
    std::puts("PASS DX12 visuals: RGBA/BGRA identity, alpha/HUD, depth haze, invalid/sky depth, bloom halo/reset and color grade");
    return OpenShimTest::ExitCode();
    }
    catch(const std::exception& error) { std::fprintf(stderr,"VISUAL_GPU ERROR: %s\n",error.what()); return 1; }
}
