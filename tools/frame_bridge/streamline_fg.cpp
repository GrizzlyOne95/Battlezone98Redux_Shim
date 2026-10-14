#include "streamline_fg.h"
#ifdef FRAME_BRIDGE_STREAMLINE
#include <sl.h>
#include <sl_dlss_g.h>
#include <sl_reflex.h>
#include <sl_pcl.h>
#include <sl_security.h>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <stdexcept>

namespace BZROpenShim::FrameBridge
{
    namespace
    {
        void Check(sl::Result result, const char* call)
        {
            if (result==sl::Result::eOk) return;
            char error[200]{}; std::snprintf(error,sizeof(error),"%s: Streamline result %u",call,static_cast<unsigned>(result));
            throw std::runtime_error(error);
        }
        void Log(sl::LogType type, const char* message)
        { if(type!=sl::LogType::eInfo) std::fprintf(stderr,"STREAMLINE %u: %s\n",static_cast<unsigned>(type),message); }
        sl::float4x4 Matrix(const MatrixD& matrix)
        {
            // Ogre uses column-vector math. Streamline's helpers use row
            // vectors, so transpose the semantic transform, not just storage.
            sl::float4x4 result{};
            for(unsigned r=0;r<4;++r) result[r]={static_cast<float>(matrix[r]),static_cast<float>(matrix[4+r]),
                static_cast<float>(matrix[8+r]),static_cast<float>(matrix[12+r])};
            return result;
        }
        template<class T> T* Export(HMODULE module,const char* name)
        {
            auto* function=reinterpret_cast<T*>(GetProcAddress(module,name));
            if(!function) throw std::runtime_error(std::string("missing Streamline export ")+name);
            return function;
        }
    }
    struct StreamlineFrameGeneration::Impl
    {
        HMODULE module=nullptr;
        bool initialized=false, enabled=false,development=false,configured=false;
        sl::DLSSGOptions initialOptions{};
        sl::ViewportHandle viewport{0}; sl::FrameToken* token=nullptr;
        unsigned width=0,height=0,realPresents=0,generatedPresents=0,multiPresentCalls=0,resetFrames=0,invalidFrames=0;
        unsigned status=0,maxGenerated=0,minDimension=0;
        std::wstring directory,logs;
        PFun_slInit* init=nullptr; PFun_slShutdown* shutdown=nullptr;
        PFun_slUpgradeInterface* upgrade=nullptr; PFun_slSetD3DDevice* setDevice=nullptr;
        PFun_slIsFeatureSupported* supported=nullptr; PFun_slGetFeatureFunction* getFunction=nullptr;
        PFun_slGetNewFrameToken* newFrame=nullptr; PFun_slSetConstants* constants=nullptr; PFun_slSetTagForFrame* tags=nullptr;
        PFun_slDLSSGSetOptions* options=nullptr; PFun_slDLSSGGetState* state=nullptr;
        PFun_slReflexSetOptions* reflexOptions=nullptr; PFun_slReflexSleep* sleep=nullptr; PFun_slPCLSetMarker* marker=nullptr;
        template<class T> T* Feature(sl::Feature feature,const char* name)
        { void* function=nullptr; Check(getFunction(feature,name,function),name); return reinterpret_cast<T*>(function); }
        void Mark(sl::PCLMarker value) { Check(marker(value,*token),"slPCLSetMarker"); }
    };
    StreamlineFrameGeneration::StreamlineFrameGeneration():impl_(std::make_unique<Impl>()) {}
    StreamlineFrameGeneration::~StreamlineFrameGeneration() { Shutdown(); }
    bool StreamlineFrameGeneration::Enabled() const { return impl_->enabled; }
    unsigned StreamlineFrameGeneration::AdditionalPresents() const { return impl_->generatedPresents; }
    void StreamlineFrameGeneration::Initialize(const std::wstring& directory,const std::wstring& logs,bool development)
    {
        auto& p=*impl_; p.development=development;
        p.directory=std::filesystem::absolute(directory).wstring(); p.logs=std::filesystem::absolute(logs).wstring();
        std::filesystem::create_directories(p.logs);
        if(development)
        {
            // SDK 2.14 reads per-plugin JSON next to the plugin DLL, despite
            // the older guide's working-directory example. Stage a private
            // diagnostic runtime so the downloaded SDK remains untouched.
            const auto staged=std::filesystem::path(p.logs).parent_path()/L"runtime-development";
            std::filesystem::create_directories(staged);
            for(const auto& file : std::filesystem::directory_iterator(p.directory))
                if(file.is_regular_file() && (file.path().extension()==L".dll" || file.path().extension()==L".txt"))
                    std::filesystem::copy_file(file.path(),staged/file.path().filename(),std::filesystem::copy_options::overwrite_existing);
            std::ofstream config(staged/L"sl.dlss_g.json");
            config<<"{\"runWhenNoFocus\":true,\"showDebugText\":true}\n"; config.close();
            if(!config) throw std::runtime_error("write private development DLSS-G config");
            p.directory=staged.wstring();
        }
        const auto dll=std::filesystem::path(p.directory)/L"sl.interposer.dll";
        if(!sl::security::verifyEmbeddedSignature(dll.c_str())) throw std::runtime_error("Streamline NVIDIA signature verification failed");
        p.module=LoadLibraryExW(dll.c_str(),nullptr,LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR|LOAD_LIBRARY_SEARCH_SYSTEM32);
        if(!p.module) throw std::runtime_error("load signed Streamline interposer");
#define IMPORT(member,name) p.member=Export<PFun_##name>(p.module,#name)
        IMPORT(init,slInit); IMPORT(shutdown,slShutdown); IMPORT(upgrade,slUpgradeInterface); IMPORT(setDevice,slSetD3DDevice);
        IMPORT(supported,slIsFeatureSupported); IMPORT(getFunction,slGetFeatureFunction); IMPORT(newFrame,slGetNewFrameToken);
        IMPORT(constants,slSetConstants); IMPORT(tags,slSetTagForFrame);
#undef IMPORT
        const sl::Feature features[]={sl::kFeatureDLSS_G,sl::kFeatureReflex,sl::kFeaturePCL};
        const wchar_t* paths[]={p.directory.c_str()};
        sl::Preferences pref{}; pref.featuresToLoad=features; pref.numFeaturesToLoad=3;
        pref.pathsToPlugins=paths; pref.numPathsToPlugins=1; pref.pathToLogsAndData=p.logs.c_str();
        pref.flags=sl::PreferenceFlags::eUseManualHooking|sl::PreferenceFlags::eDisableCLStateTracking|sl::PreferenceFlags::eUseFrameBasedResourceTagging;
        pref.logMessageCallback=Log; pref.logLevel=sl::LogLevel::eVerbose; pref.renderAPI=sl::RenderAPI::eD3D12;
        pref.engine=sl::EngineType::eCustom; pref.engineVersion="OpenShimFrameBridge-0.1";
        // Project identity for this experimental helper, not a registered
        // NVIDIA application ID and not the original game's identity.
        pref.projectId="1e8f1146-359e-4ce4-a2cf-719b86e3c74a";
        Check(p.init(pref,sl::kSDKVersion),"slInit"); p.initialized=true;
        std::printf("STREAMLINE runtime_mode=%s signed_interposer=yes\n",development ? "development-do-not-ship" : "production");
    }
    void StreamlineFrameGeneration::Upgrade(void** object) { Check(impl_->upgrade(object),"slUpgradeInterface"); }
    void StreamlineFrameGeneration::SetDevice(ID3D12Device* device,LUID adapter,unsigned width,unsigned height,DXGI_FORMAT format,DXGI_FORMAT hudlessFormat)
    {
        auto& p=*impl_; p.width=width; p.height=height;
        sl::AdapterInfo info{}; info.deviceLUID=reinterpret_cast<uint8_t*>(&adapter); info.deviceLUIDSizeInBytes=sizeof(adapter);
        Check(p.supported(sl::kFeatureDLSS_G,info),"DLSS Frame Generation support");
        Check(p.setDevice(device),"slSetD3DDevice");
        p.options=p.Feature<PFun_slDLSSGSetOptions>(sl::kFeatureDLSS_G,"slDLSSGSetOptions");
        p.state=p.Feature<PFun_slDLSSGGetState>(sl::kFeatureDLSS_G,"slDLSSGGetState");
        p.reflexOptions=p.Feature<PFun_slReflexSetOptions>(sl::kFeatureReflex,"slReflexSetOptions");
        p.sleep=p.Feature<PFun_slReflexSleep>(sl::kFeatureReflex,"slReflexSleep");
        p.marker=p.Feature<PFun_slPCLSetMarker>(sl::kFeaturePCL,"slPCLSetMarker");
        sl::ReflexOptions reflex{}; reflex.mode=sl::ReflexMode::eLowLatency; reflex.frameLimitUs=33333;
        Check(p.reflexOptions(reflex),"slReflexSetOptions");
        sl::DLSSGOptions options{}; options.mode=sl::DLSSGMode::eOff; options.numFramesToGenerate=1;
        options.numBackBuffers=2; options.mvecDepthWidth=options.colorWidth=width; options.mvecDepthHeight=options.colorHeight=height;
        options.colorBufferFormat=format; options.hudLessBufferFormat=hudlessFormat;
        options.depthBufferFormat=DXGI_FORMAT_R32_FLOAT; options.mvecBufferFormat=DXGI_FORMAT_R32G32_FLOAT;
        p.initialOptions=options;
        sl::DLSSGState state{}; Check(p.state(p.viewport,state,nullptr),"slDLSSGGetState");
        p.maxGenerated=state.numFramesToGenerateMax; p.minDimension=state.minWidthOrHeight;
        std::printf("DLSSG supported=yes max_generated=%u minimum_dimension=%u camera_motion_only=yes simulation_reflex_integrated=no\n",p.maxGenerated,p.minDimension);
        std::fflush(stdout);
        if(width<p.minDimension||height<p.minDimension) throw std::runtime_error("DLSS-G preview resolution below SDK minimum");
    }
    void StreamlineFrameGeneration::Begin(const CapturedCameraPair& pair,unsigned frameIndex,bool valid)
    {
        auto& p=*impl_; Check(p.newFrame(p.token,&frameIndex),"slGetNewFrameToken");
        Check(p.sleep(*p.token),"slReflexSleep");
        p.Mark(sl::PCLMarker::eSimulationStart); p.Mark(sl::PCLMarker::eSimulationEnd);
        const auto facts=InspectPerspective(pair.current);
        auto options=p.initialOptions; options.mode=valid && facts.recognized ? sl::DLSSGMode::eOn : sl::DLSSGMode::eOff;
        options.numFramesToGenerate=1;
        const bool enable=options.mode==sl::DLSSGMode::eOn;
        if(!p.configured||enable!=p.enabled) Check(p.options(p.viewport,options),"slDLSSGSetOptions frame");
        p.configured=true;
        p.enabled=enable;
        if(!p.enabled) ++p.invalidFrames;
        else
        {
            MatrixD projection{},view{},inverseProjection{},inverseView{},inverseVP{},previous{};
            for(unsigned i=0;i<16;++i) { projection[i]=pair.current.projection[i]; view[i]=pair.current.view[i]; }
            if(!Inverse(projection,inverseProjection)||!Inverse(view,inverseView)||!Inverse(ViewProjection(pair.current),inverseVP))
                throw std::runtime_error("noninvertible DLSS camera matrices");
            if(pair.comparable) previous=Multiply(ViewProjection(pair.previous),inverseVP);
            else { for(unsigned i=0;i<16;++i) previous[i]=i%5==0?1.0:0.0; ++p.resetFrames; }
            MatrixD reverse{}; if(!Inverse(previous,reverse)) throw std::runtime_error("noninvertible temporal transform");
            sl::Constants c{}; c.cameraViewToClip=Matrix(projection); c.clipToCameraView=Matrix(inverseProjection);
            c.clipToPrevClip=Matrix(previous); c.prevClipToClip=Matrix(reverse);
            c.jitterOffset={0,0}; c.mvecScale={1.0f/p.width,1.0f/p.height}; c.cameraPinholeOffset={0,0};
            c.cameraPos={static_cast<float>(inverseView[3]),static_cast<float>(inverseView[7]),static_cast<float>(inverseView[11])};
            c.cameraRight={static_cast<float>(inverseView[0]),static_cast<float>(inverseView[4]),static_cast<float>(inverseView[8])};
            c.cameraUp={static_cast<float>(inverseView[1]),static_cast<float>(inverseView[5]),static_cast<float>(inverseView[9])};
            c.cameraFwd={static_cast<float>(inverseView[2]*facts.forwardSign),static_cast<float>(inverseView[6]*facts.forwardSign),static_cast<float>(inverseView[10]*facts.forwardSign)};
            c.cameraNear=pair.current.nearClip; c.cameraFar=pair.current.farClip; c.cameraAspectRatio=static_cast<float>(facts.aspect);
            c.cameraFOV=static_cast<float>(facts.verticalFovDegrees*3.141592653589793/180);
            c.depthInverted=facts.reversed?sl::eTrue:sl::eFalse; c.cameraMotionIncluded=sl::eTrue;
            c.motionVectors3D=sl::eFalse; c.reset=pair.comparable?sl::eFalse:sl::eTrue;
            Check(p.constants(c,*p.token,p.viewport),"slSetConstants");
        }
        p.Mark(sl::PCLMarker::eRenderSubmitStart);
    }
    void StreamlineFrameGeneration::Tag(ID3D12GraphicsCommandList* commands,ID3D12Resource* depth,ID3D12Resource* motion,ID3D12Resource* scene)
    {
        auto& p=*impl_; const sl::Extent extent{0,0,p.width,p.height};
        sl::Resource d{sl::ResourceType::eTex2d,depth,D3D12_RESOURCE_STATE_COMMON};
        sl::Resource m{sl::ResourceType::eTex2d,motion,D3D12_RESOURCE_STATE_COMMON};
        sl::Resource s{sl::ResourceType::eTex2d,scene,D3D12_RESOURCE_STATE_COMMON};
        const auto life=sl::ResourceLifecycle::eValidUntilPresent;
        const sl::ResourceTag tags[]={ {p.enabled?&d:nullptr,sl::kBufferTypeDepth,life,&extent},
            {p.enabled?&m:nullptr,sl::kBufferTypeMotionVectors,life,&extent}, {p.enabled?&s:nullptr,sl::kBufferTypeHUDLessColor,life,&extent},
            {nullptr,sl::kBufferTypeBackbuffer,life,&extent} };
        Check(p.tags(*p.token,p.viewport,tags,4,commands),"slSetTagForFrame");
    }
    void StreamlineFrameGeneration::Submitted() { impl_->Mark(sl::PCLMarker::eRenderSubmitEnd); }
    void StreamlineFrameGeneration::BeforePresent() { impl_->Mark(sl::PCLMarker::ePresentStart); }
    void StreamlineFrameGeneration::AfterPresent()
    {
        auto& p=*impl_; p.Mark(sl::PCLMarker::ePresentEnd);
        sl::DLSSGState state{}; Check(p.state(p.viewport,state,nullptr),"slDLSSGGetState after Present");
        ++p.realPresents; p.status=static_cast<unsigned>(state.status);
        if(state.numFramesActuallyPresented>1) { p.generatedPresents+=state.numFramesActuallyPresented-1; ++p.multiPresentCalls; }
        if(p.realPresents%30==0) { std::printf("DLSSG real_present_calls=%u reported_additional_presents=%u multi_present_calls=%u status=0x%x resets=%u missing_inputs=%u\n",
            p.realPresents,p.generatedPresents,p.multiPresentCalls,p.status,p.resetFrames,p.invalidFrames); std::fflush(stdout); }
        if(p.enabled && p.status) throw std::runtime_error("DLSS-G reported runtime failure; inspect Streamline log");
    }
    void StreamlineFrameGeneration::SaveReport(const std::string& path) const
    {
        const auto& p=*impl_; std::ofstream out(path);
        out<<"{\n  \"previewOnly\": true,\n  \"cameraMotionOnly\": true,\n  \"gameSimulationReflexIntegrated\": false,\n  \"realPresentCalls\": "<<p.realPresents
            <<",\n  \"sdkReportedAdditionalPresents\": "<<p.generatedPresents<<",\n  \"multiPresentCalls\": "<<p.multiPresentCalls
            <<",\n  \"lastStatus\": "<<p.status<<",\n  \"historyResetFrames\": "<<p.resetFrames<<",\n  \"missingInputFrames\": "<<p.invalidFrames
            <<",\n  \"developmentRuntimeRequested\": "<<(p.development?"true":"false")<<",\n  \"maximumGeneratedFrames\": "<<p.maxGenerated<<"\n}\n";
        if(!out) throw std::runtime_error("save DLSS-G report");
        if(!p.multiPresentCalls) throw std::runtime_error("DLSS-G produced no reported additional presents");
    }
    void StreamlineFrameGeneration::Shutdown()
    {
        auto& p=*impl_;
        if(p.initialized) { const auto result=p.shutdown(); if(result!=sl::Result::eOk) std::fprintf(stderr,"STREAMLINE shutdown result %u\n",static_cast<unsigned>(result)); p.initialized=false; }
        // Leave the interposer loaded until process exit: upgraded COM objects
        // can still release through it after slShutdown.
    }
}
#else
#include <stdexcept>
namespace BZROpenShim::FrameBridge
{
    struct StreamlineFrameGeneration::Impl {};
    StreamlineFrameGeneration::StreamlineFrameGeneration():impl_(std::make_unique<Impl>()) {}
    StreamlineFrameGeneration::~StreamlineFrameGeneration()=default;
    void StreamlineFrameGeneration::Initialize(const std::wstring&,const std::wstring&,bool)
    { throw std::runtime_error("reconfigure helper with FRAME_BRIDGE_STREAMLINE_SDK to enable the DLSS-G preview"); }
    void StreamlineFrameGeneration::Upgrade(void**) {}
    void StreamlineFrameGeneration::SetDevice(ID3D12Device*,LUID,unsigned,unsigned,DXGI_FORMAT,DXGI_FORMAT) {}
    void StreamlineFrameGeneration::Begin(const CapturedCameraPair&,unsigned,bool) {}
    void StreamlineFrameGeneration::Tag(ID3D12GraphicsCommandList*,ID3D12Resource*,ID3D12Resource*,ID3D12Resource*) {}
    void StreamlineFrameGeneration::Submitted() {}
    void StreamlineFrameGeneration::BeforePresent() {}
    void StreamlineFrameGeneration::AfterPresent() {}
    void StreamlineFrameGeneration::SaveReport(const std::string&) const {}
    void StreamlineFrameGeneration::Shutdown() {}
    bool StreamlineFrameGeneration::Enabled() const { return false; }
    unsigned StreamlineFrameGeneration::AdditionalPresents() const { return 0; }
}
#endif
