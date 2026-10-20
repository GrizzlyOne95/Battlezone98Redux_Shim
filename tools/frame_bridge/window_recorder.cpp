#include "window_recorder.h"
#include <stdexcept>
#include <cstdio>
#ifdef FRAME_BRIDGE_RECORD_WINDOW
#include <d3d11.h>
#include <dxgi.h>
#include <windows.graphics.capture.interop.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>
#include <fstream>
#include <vector>
#include <mutex>
#include <atomic>
#endif
namespace BZROpenShim::FrameBridge
{
#ifdef FRAME_BRIDGE_RECORD_WINDOW
    using namespace winrt::Windows::Graphics::Capture;
    struct OwnWindowRecorder::Impl
    {
        std::atomic<bool> active{false};
        std::mutex mutex;
        std::ofstream file;
        std::string error;
        unsigned width=0,height=0,frames=0;
        winrt::com_ptr<ID3D11Device> device;
        winrt::com_ptr<ID3D11DeviceContext> context;
        winrt::com_ptr<ID3D11Texture2D> staging;
        Direct3D11CaptureFramePool pool{nullptr};
        GraphicsCaptureSession session{nullptr};
        winrt::event_token arrived{};
        bool subscribed=false;
    };
    OwnWindowRecorder::OwnWindowRecorder():impl_(std::make_shared<Impl>()) {}
    OwnWindowRecorder::~OwnWindowRecorder()
    { try { Stop(); } catch(const std::exception& e) { std::fprintf(stderr,"RECORDING ERROR: %s\n",e.what()); } }
    void OwnWindowRecorder::Start(HWND window,const std::string& path)
    {
        DWORD owner=0; GetWindowThreadProcessId(window,&owner);
        if(owner!=GetCurrentProcessId()) throw std::runtime_error("recorder accepts only its own preview window");
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        if(!GraphicsCaptureSession::IsSupported()) throw std::runtime_error("Windows Graphics Capture is unavailable");
        auto p=impl_;
        winrt::check_hresult(D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            nullptr,0,D3D11_SDK_VERSION,p->device.put(),nullptr,p->context.put()));
        auto dxgi=p->device.as<IDXGIDevice>(); winrt::com_ptr<IInspectable> wrapped;
        winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgi.get(),wrapped.put()));
        auto captureDevice=wrapped.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
        auto factory=winrt::get_activation_factory<GraphicsCaptureItem,IGraphicsCaptureItemInterop>();
        GraphicsCaptureItem item{nullptr};
        winrt::check_hresult(factory->CreateForWindow(window,winrt::guid_of<GraphicsCaptureItem>(),winrt::put_abi(item)));
        p->width=static_cast<unsigned>(item.Size().Width); p->height=static_cast<unsigned>(item.Size().Height);
        if(!p->width||!p->height||p->width>8192||p->height>8192) throw std::runtime_error("recording extent outside bounded range");
        p->file.open(path,std::ios::binary|std::ios::trunc);
        p->file.write("BZRVID1\0",8); p->file.write(reinterpret_cast<const char*>(&p->width),4); p->file.write(reinterpret_cast<const char*>(&p->height),4);
        if(!p->file) throw std::runtime_error("open preview recording file");
        p->pool=Direct3D11CaptureFramePool::CreateFreeThreaded(captureDevice,
            winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized,2,item.Size());
        p->session=p->pool.CreateCaptureSession(item); p->session.IsCursorCaptureEnabled(false);
        p->active=true;
        p->arrived=p->pool.FrameArrived([p](const Direct3D11CaptureFramePool& sender,const winrt::Windows::Foundation::IInspectable&)
        {
            std::lock_guard<std::mutex> lock(p->mutex);
            if(!p->active) return;
            try
            {
                const auto frame=sender.TryGetNextFrame(); if(!frame) return;
                if(frame.ContentSize().Width!=static_cast<int>(p->width)||frame.ContentSize().Height!=static_cast<int>(p->height))
                    throw std::runtime_error("preview resized during recording");
                auto access=frame.Surface().as<Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess>();
                winrt::com_ptr<ID3D11Texture2D> source; winrt::check_hresult(access->GetInterface(__uuidof(ID3D11Texture2D),source.put_void()));
                if(!p->staging)
                {
                    D3D11_TEXTURE2D_DESC desc{}; source->GetDesc(&desc);
                    if(desc.Format!=DXGI_FORMAT_B8G8R8A8_UNORM||desc.SampleDesc.Count!=1) throw std::runtime_error("unexpected window capture format");
                    desc.Usage=D3D11_USAGE_STAGING; desc.BindFlags=desc.MiscFlags=0; desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
                    winrt::check_hresult(p->device->CreateTexture2D(&desc,nullptr,p->staging.put()));
                }
                p->context->CopyResource(p->staging.get(),source.get());
                D3D11_MAPPED_SUBRESOURCE mapped{}; winrt::check_hresult(p->context->Map(p->staging.get(),0,D3D11_MAP_READ,0,&mapped));
                const auto timestamp=frame.SystemRelativeTime().count();
                p->file.write(reinterpret_cast<const char*>(&timestamp),8);
                for(unsigned y=0;y<p->height;++y) p->file.write(static_cast<const char*>(mapped.pData)+y*mapped.RowPitch,p->width*4);
                p->context->Unmap(p->staging.get(),0);
                if(!p->file) throw std::runtime_error("write preview recording");
                ++p->frames;
            }
            catch(const winrt::hresult_error& e) { p->error=winrt::to_string(e.message()); p->active=false; }
            catch(const std::exception& e) { p->error=e.what(); p->active=false; }
        });
        p->subscribed=true; p->session.StartCapture();
        std::printf("RECORDING source=own-window-WindowsGraphicsCapture size=%ux%u path=%s\n",p->width,p->height,path.c_str());
        std::fflush(stdout);
    }
    void OwnWindowRecorder::Stop()
    {
        auto p=impl_; p->active=false;
        if(p->subscribed) { p->pool.FrameArrived(p->arrived); p->subscribed=false; }
        if(p->session) { p->session.Close(); p->session=nullptr; }
        if(p->pool) { p->pool.Close(); p->pool=nullptr; }
        std::lock_guard<std::mutex> lock(p->mutex);
        if(p->file.is_open())
        {
            p->file.close(); std::printf("RECORDING captured_frames=%u\n",p->frames);
            if(!p->frames) throw std::runtime_error("own-window recorder received no frames");
        }
        if(!p->error.empty()) { const auto error=std::move(p->error); p->error.clear(); throw std::runtime_error(error); }
    }
#else
    struct OwnWindowRecorder::Impl {};
    OwnWindowRecorder::OwnWindowRecorder():impl_(std::make_shared<Impl>()) {}
    OwnWindowRecorder::~OwnWindowRecorder()=default;
    void OwnWindowRecorder::Start(HWND,const std::string&)
    { throw std::runtime_error("configure FRAME_BRIDGE_RECORD_WINDOW=ON to record the preview"); }
    void OwnWindowRecorder::Stop() {}
#endif
}
