#include "fog_wake_feature.h"
#include "fog_wake_api.h"
#include "fog_wake_renderer.h"
#include "fog_wake_runtime.h"
#include "bzr_options_ui.h"
#include "shim_log.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>

namespace BZROpenShim {
namespace {
    FogWake::Runtime runtime;
    FogWakeApi::Config config;
    std::atomic<bool> enabled{false};
    bool configLoaded=false, bankPlaced=false, scriptOwned=false;
    bool renderReady=false, resetRenderer=false, haveClock=false;
    double scriptClock=0;
    // Lua Update and the world render hook run on the game's main thread.
    double Now() {
        return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    bool Range(float v,float lo,float hi) { return std::isfinite(v)&&v>=lo&&v<=hi; }
    bool Valid(const FogWakeApi::Config& c) {
        return c.size==sizeof(c)&&c.version==FogWakeApi::Version
            &&Range(c.centerX,-1e6f,1e6f)&&Range(c.centerZ,-1e6f,1e6f)&&Range(c.baseY,-1e5f,1e5f)
            &&Range(c.width,32,1024)&&Range(c.cellSize,1,16)&&c.width/c.cellSize<=256
            &&Range(c.height,1,64)&&Range(c.wakeRadius,1,64)&&Range(c.recoverySeconds,.1f,300)
            &&Range(c.density,0,1)&&Range(c.windX,-100,100)&&Range(c.windZ,-100,100)
            &&Range(c.colorR,0,1)&&Range(c.colorG,0,1)&&Range(c.colorB,0,1);
    }
    bool Configure(const FogWakeApi::Config& c,bool scripted) {
        if (!Valid(c)) return false;
        FogWake::RuntimeConfig rc;
        rc.field.width=rc.field.height=static_cast<std::size_t>(std::ceil(c.width/c.cellSize));
        rc.field.cellSize=c.cellSize;
        const double half=rc.field.width*rc.field.cellSize*.5;
        rc.field.origin={c.centerX-half,c.centerZ-half};
        rc.field.recoverySeconds=c.recoverySeconds;
        rc.field.maxSegmentLength=64;
        rc.radius=c.wakeRadius;
        rc.simulationHz=20;
        rc.maxSpeed=160;
        rc.forgetAfterSeconds=.5;
        if (!runtime.Configure(rc)) return false;
        config=c; scriptOwned=scripted; haveClock=false;
        if (!scripted) runtime.BeginSession(Now());
        resetRenderer=true; renderReady=false; bankPlaced=true; enabled.store(true);
        LogShimA(LogLevel::Info,"fogwake",
            "[FOGWAKE] bank configured owner=%s center=(%.1f,%.1f,%.1f) width=%.1f height=%.1f",
            scripted?"mission":"ini",c.centerX,c.baseY,c.centerZ,c.width,c.height);
        return true;
    }
    void Disable() {
        runtime.Shutdown(); bankPlaced=false; scriptOwned=false; haveClock=false;
        renderReady=false; resetRenderer=true; enabled.store(false);
    }
}
bool FogWakeFeatureEnabled() {
    if (!configLoaded) {
        bool v=false;
        const bool found=TryGetUserConfigBool("Experimental","InteractiveFogWakes",v);
        enabled.store(found?v:EnvFlagEnabled("OPENSHIM_INTERACTIVE_FOG_WAKES"));
        configLoaded=true;
    }
    return enabled.load(std::memory_order_relaxed);
}
void FogWakeNotifyMissionRunStateChanged(bool running,void* sceneManager) {
    if (!running) { Disable(); ResetFogWakeRenderer(sceneManager); resetRenderer=false; }
    // Lua Init/Start/Load owns reconfiguration; do not re-enable across missions.
}
void FogWakeObserveEmitter(const void* emitter,float x,float z) {
    if (!FogWakeFeatureEnabled()||scriptOwned||!emitter||!std::isfinite(x)||!std::isfinite(z)) return;
    try {
        if (!bankPlaced) {
            FogWakeApi::Config c; c.centerX=x; c.centerZ=z;
            if (!Configure(c,false)) return;
        }
        runtime.Observe(emitter,{x,z},Now());
    } catch (...) { Disable(); }
}
void FogWakeRenderFrameTick(void* sceneManager) {
    if (resetRenderer) { ResetFogWakeRenderer(sceneManager); resetRenderer=false; }
    if (!enabled.load(std::memory_order_relaxed)||!bankPlaced) return;
    try {
        if (!scriptOwned) {
            runtime.AdvanceTo(Now(),{config.windX,config.windZ});
            return; // INI has no ground plane; only mission-configured banks render.
        }
        const auto& field=runtime.GetField();
        const auto& s=field.Settings();
        FogWake::RendererSnapshot snapshot;
        snapshot.clearance=field.Clearance().data();
        snapshot.width=static_cast<unsigned>(s.width);
        snapshot.height=static_cast<unsigned>(s.height);
        snapshot.cellSize=static_cast<float>(s.cellSize);
        snapshot.originX=static_cast<float>(s.origin.x);
        snapshot.originZ=static_cast<float>(s.origin.z);
        FogWake::RendererConfig draw;
        draw.groundY=config.baseY; draw.height=config.height; draw.density=config.density;
        draw.red=config.colorR; draw.green=config.colorG; draw.blue=config.colorB;
        renderReady=UpdateFogWakeRenderer(sceneManager,snapshot,draw);
    } catch (...) {
        Disable();
        LogShimA(LogLevel::Warn,"fogwake","[FOGWAKE] runtime exception; disabled");
    }
}
std::int32_t ConfigureFogWakeApi(const FogWakeApi::Config* c) {
    configLoaded=true; // Mission intent must not be replaced by lazy INI init.
    return c&&Configure(*c,true)?1:0;
}
std::int32_t UpdateFogWakeApi(double now) {
    if (!scriptOwned||!bankPlaced||!std::isfinite(now)) return 0;
    if (!haveClock) { runtime.BeginSession(now); haveClock=true; }
    scriptClock=now;
    runtime.AdvanceTo(now,{config.windX,config.windZ});
    return 1;
}
std::int32_t ObserveFogWakeApi(std::uint32_t id,float x,float y,float z) {
    if (!scriptOwned||!haveClock||!id||!Range(x,-1e6f,1e6f)||!Range(z,-1e6f,1e6f)||!Range(y,-1e5f,1e5f)) return 0;
    const auto key=reinterpret_cast<const void*>(static_cast<std::uintptr_t>(id));
    if (y<config.baseY-4||y>config.baseY+config.height+4) { runtime.Forget(key); return 1; }
    return runtime.Observe(key,{x,z},scriptClock)?1:0;
}
std::int32_t RemoveFogWakeApi(std::uint32_t id) {
    if (!scriptOwned||!id) return 0;
    runtime.Forget(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(id)));
    return 1;
}
std::int32_t ResetFogWakeApi() { configLoaded=true; Disable(); return 1; }
std::int32_t GetFogWakeStatusApi(FogWakeApi::Status* s) {
    if (!s||s->size!=sizeof(*s)||s->version!=FogWakeApi::Version) return 0;
    *s=FogWakeApi::Status{};
    s->supported=1; s->configured=scriptOwned&&bankPlaced?1:0; s->renderReady=renderReady?1:0;
    s->emitterCount=static_cast<std::uint32_t>(runtime.TrackedEmitters());
    for (float v:runtime.GetField().Clearance()) {
        if (v>.01f) ++s->activeCells;
        s->maxClearance=std::max(s->maxClearance,v);
    }
    return 1;
}
}
// Optional value-only C ABI. Never throw across the companion DLL boundary.
extern "C" {
__declspec(dllexport) std::int32_t __cdecl OpenShimConfigureFogWake(const FogWakeApi::Config* c)
{ try { return BZROpenShim::ConfigureFogWakeApi(c); } catch (...) { BZROpenShim::ResetFogWakeApi(); return 0; } }
__declspec(dllexport) std::int32_t __cdecl OpenShimUpdateFogWake(double now)
{ try { return BZROpenShim::UpdateFogWakeApi(now); } catch (...) { BZROpenShim::ResetFogWakeApi(); return 0; } }
__declspec(dllexport) std::int32_t __cdecl OpenShimObserveFogWake(std::uint32_t id,float x,float y,float z)
{ try { return BZROpenShim::ObserveFogWakeApi(id,x,y,z); } catch (...) { BZROpenShim::ResetFogWakeApi(); return 0; } }
__declspec(dllexport) std::int32_t __cdecl OpenShimRemoveFogWakeEmitter(std::uint32_t id)
{ return BZROpenShim::RemoveFogWakeApi(id); }
__declspec(dllexport) std::int32_t __cdecl OpenShimResetFogWake()
{ return BZROpenShim::ResetFogWakeApi(); }
__declspec(dllexport) std::int32_t __cdecl OpenShimGetFogWakeStatus(FogWakeApi::Status* s)
{ return BZROpenShim::GetFogWakeStatusApi(s); }
}
