#include "test_check.h"
#include "gpu_motion.h"
#include <d3d12.h>
#include <cmath>
#include <limits>
#include <vector>
#include <cstdio>
using namespace BZROpenShim::FrameBridge;
using Microsoft::WRL::ComPtr;
using OpenShimTest::Require;
namespace
{
    void CheckHR(HRESULT hr) { Require(SUCCEEDED(hr),"D3D12 motion test operation"); }
    void Barrier(ID3D12GraphicsCommandList* list,ID3D12Resource* resource,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after)
    {
        D3D12_RESOURCE_BARRIER b{}; b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        b.Transition={resource,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after}; list->ResourceBarrier(1,&b);
    }
    ComPtr<ID3D12Resource> Buffer(ID3D12Device* device,UINT64 size,D3D12_HEAP_TYPE type,D3D12_RESOURCE_STATES state)
    {
        D3D12_RESOURCE_DESC desc{}; desc.Dimension=D3D12_RESOURCE_DIMENSION_BUFFER; desc.Width=size; desc.Height=1;
        desc.DepthOrArraySize=desc.MipLevels=1; desc.SampleDesc.Count=1; desc.Layout=D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        D3D12_HEAP_PROPERTIES heap{}; heap.Type=type; ComPtr<ID3D12Resource> output;
        CheckHR(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&desc,state,nullptr,IID_PPV_ARGS(&output))); return output;
    }
}
int main()
{
    constexpr unsigned width=67,height=33;
    ComPtr<ID3D12Device> device; CheckHR(D3D12CreateDevice(nullptr,D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device)));
    D3D12_RESOURCE_DESC desc{}; desc.Dimension=D3D12_RESOURCE_DIMENSION_TEXTURE2D; desc.Width=width; desc.Height=height;
    desc.DepthOrArraySize=desc.MipLevels=1; desc.SampleDesc.Count=1; desc.Format=DXGI_FORMAT_R32_FLOAT;
    D3D12_HEAP_PROPERTIES heap{}; heap.Type=D3D12_HEAP_TYPE_DEFAULT;
    ComPtr<ID3D12Resource> depth; CheckHR(device->CreateCommittedResource(&heap,D3D12_HEAP_FLAG_NONE,&desc,D3D12_RESOURCE_STATE_COPY_DEST,nullptr,IID_PPV_ARGS(&depth)));
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT inFoot{}; UINT64 inBytes=0;
    device->GetCopyableFootprints(&desc,0,1,0,&inFoot,nullptr,nullptr,&inBytes);
    auto upload=Buffer(device.Get(),inBytes,D3D12_HEAP_TYPE_UPLOAD,D3D12_RESOURCE_STATE_GENERIC_READ);
    unsigned char* mapped=nullptr; D3D12_RANGE none{0,0}; CheckHR(upload->Map(0,&none,reinterpret_cast<void**>(&mapped)));
    const float values[]={0.1f,0.5f,0.9f,1.0f,std::numeric_limits<float>::quiet_NaN()};
    for(unsigned y=0;y<height;++y) for(unsigned x=0;x<width;++x)
        reinterpret_cast<float*>(mapped+inFoot.Offset+y*inFoot.Footprint.RowPitch)[x]=values[x%5];
    upload->Unmap(0,nullptr);
    GpuCameraMotion motion; motion.Initialize(device.Get(),depth.Get());
    const auto outDesc=motion.Output()->GetDesc(); D3D12_PLACED_SUBRESOURCE_FOOTPRINT outFoot{}; UINT64 outBytes=0;
    device->GetCopyableFootprints(&outDesc,0,1,0,&outFoot,nullptr,nullptr,&outBytes);
    auto readback=Buffer(device.Get(),outBytes,D3D12_HEAP_TYPE_READBACK,D3D12_RESOURCE_STATE_COPY_DEST);
    D3D12_COMMAND_QUEUE_DESC q{}; ComPtr<ID3D12CommandQueue> queue; CheckHR(device->CreateCommandQueue(&q,IID_PPV_ARGS(&queue)));
    ComPtr<ID3D12CommandAllocator> allocator; CheckHR(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&allocator)));
    ComPtr<ID3D12GraphicsCommandList> list; CheckHR(device->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT,allocator.Get(),nullptr,IID_PPV_ARGS(&list)));
    D3D12_TEXTURE_COPY_LOCATION input{}; input.pResource=upload.Get(); input.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; input.PlacedFootprint=inFoot;
    D3D12_TEXTURE_COPY_LOCATION destination{}; destination.pResource=depth.Get(); destination.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    list->CopyTextureRegion(&destination,0,0,0,&input,nullptr);
    Barrier(list.Get(),depth.Get(),D3D12_RESOURCE_STATE_COPY_DEST,D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
    CapturedCameraPair pair{}; pair.comparable=true;
    auto& camera=pair.current; camera.status=1; camera.matrixSource=static_cast<unsigned>(CameraMatrixSource::Synthetic);
    camera.width=width; camera.height=height; camera.observationQpc=1; camera.cameraIdentity=1; camera.name[0]='T';
    camera.nearClip=.1f; camera.farClip=100;
    camera.view[0]=camera.view[5]=camera.view[10]=camera.view[15]=1;
    const float qz=camera.farClip/(camera.farClip-camera.nearClip);
    camera.projection[0]=1.2f; camera.projection[5]=1.4f; camera.projection[10]=-qz;
    camera.projection[11]=-qz*camera.nearClip; camera.projection[14]=-1;
    pair.previous=camera; camera.view[3]=.02f; camera.view[7]=-.03f;
    motion.Record(list.Get(),pair);
    Barrier(list.Get(),motion.Output(),D3D12_RESOURCE_STATE_COMMON,D3D12_RESOURCE_STATE_COPY_SOURCE);
    input.pResource=motion.Output(); input.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    destination.pResource=readback.Get(); destination.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT; destination.PlacedFootprint=outFoot;
    list->CopyTextureRegion(&destination,0,0,0,&input,nullptr); CheckHR(list->Close());
    ID3D12CommandList* lists[]={list.Get()}; queue->ExecuteCommandLists(1,lists);
    ComPtr<ID3D12Fence> fence; CheckHR(device->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence)));
    HANDLE event=CreateEventW(nullptr,FALSE,FALSE,nullptr); Require(event!=nullptr,"motion test completion event");
    CheckHR(queue->Signal(fence.Get(),1)); CheckHR(fence->SetEventOnCompletion(1,event)); Require(WaitForSingleObject(event,3000)==WAIT_OBJECT_0,"bounded motion GPU wait");
    D3D12_RANGE range{0,static_cast<SIZE_T>(outBytes)}; CheckHR(readback->Map(0,&range,reinterpret_cast<void**>(&mapped)));
    for(unsigned y=0;y<height;++y) for(unsigned x=0;x<width;++x)
    {
        const auto* pixel=reinterpret_cast<float*>(mapped+outFoot.Offset+y*outFoot.Footprint.RowPitch)+x*2;
        const float z=values[x%5];
        const float distance=std::isfinite(z)&&z<1?qz*camera.nearClip/(qz-z):1;
        const float dx=x%5<3 ? -.02f*1.2f*width*.5f/distance : 0;
        const float dy=x%5<3 ? -.03f*1.4f*height*.5f/distance : 0;
        Require(std::isfinite(pixel[0])&&std::isfinite(pixel[1])&&std::fabs(pixel[0]-dx)<.0001f&&std::fabs(pixel[1]-dy)<.0001f,
            "GPU motion matches analytic depth-dependent translation, sky ignores translation, invalid z is zero");
    }
    readback->Unmap(0,&none); CloseHandle(event);
    std::puts("PASS GPU motion: 2211 pixels, analytic translation, offscreen correspondences, sky, invalid depth");
}
