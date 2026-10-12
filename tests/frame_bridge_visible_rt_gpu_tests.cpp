#include "test_check.h"
#include "visible_rt.h"
#include <d3d12.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
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
    std::vector<unsigned char> Render(const Input& input)
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
        VisibleRayTracing rt; rt.Initialize(device.Get(),textures[0].Get(),textures[1].Get(),textures[2].Get()); rt.Record(list.Get(),input.camera);
        const auto desc=rt.FinalOutput()->GetDesc(); D3D12_PLACED_SUBRESOURCE_FOOTPRINT foot{}; UINT64 bytes=0;
        device->GetCopyableFootprints(&desc,0,1,0,&foot,nullptr,nullptr,&bytes);
        auto readback=Buffer(device.Get(),bytes,D3D12_HEAP_TYPE_READBACK,D3D12_RESOURCE_STATE_COPY_DEST);
        Barrier(list.Get(),rt.FinalOutput(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COPY_SOURCE);
        D3D12_TEXTURE_COPY_LOCATION from{}; from.pResource=rt.FinalOutput(); from.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        D3D12_TEXTURE_COPY_LOCATION to{}; to.pResource=readback.Get(); to.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; to.PlacedFootprint=foot;
        list->CopyTextureRegion(&to,0,0,0,&from,nullptr); Check(list->Close());
        ID3D12CommandList* lists[]={list.Get()}; queue->ExecuteCommandLists(1,lists);
        ComPtr<ID3D12Fence> fence; Check(device->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence)));
        HANDLE event=CreateEventW(nullptr,FALSE,FALSE,nullptr); Require(event!=nullptr,"DXR test event");
        Check(queue->Signal(fence.Get(),1)); Check(fence->SetEventOnCompletion(1,event)); Require(WaitForSingleObject(event,5000)==WAIT_OBJECT_0,"bounded DXR completion");
        unsigned char* mapped=nullptr; D3D12_RANGE range{0,static_cast<SIZE_T>(bytes)}; Check(readback->Map(0,&range,reinterpret_cast<void**>(&mapped)));
        std::vector<unsigned char> pixels(input.width*input.height*4);
        for(unsigned y=0;y<input.height;++y) std::memcpy(pixels.data()+y*input.width*4,mapped+foot.Offset+y*foot.Footprint.RowPitch,input.width*4);
        const D3D12_RANGE none{0,0}; readback->Unmap(0,&none); CloseHandle(event);
        std::printf("DXR_CAPTURE triangles_capacity=%u pixels=%u\n",rt.TriangleCapacity(),input.width*input.height); return pixels;
    }
}
int main(int argc,char** argv)
{
    if(argc==3)
    {
        const auto input=ReadCapture(argv[1]); const auto pixels=Render(input);
        std::ofstream file(argv[2],std::ios::binary); file.write(reinterpret_cast<const char*>(pixels.data()),static_cast<std::streamsize>(pixels.size()));
        Require(file.good(),"save captured DXR RGBA output"); return 0;
    }
    Require(argc==1,"usage: frame_bridge_visible_rt_gpu_tests [capture.bin output.rgba]");
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
}
