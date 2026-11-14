// soak_telemetry.cpp
// BZR Open Shim - opt-in soak telemetry (diagnostic only)
//
// Why: an RTX 5080 gets driver resets (TDR, nvlddmkm 153) in this game only.
// The GPU stops completing frames for seconds and the logs cannot say which
// work hung. An overnight soak runner turns this on and parses three line
// families from openshim.log:
//
//   [GPUWATCH]  A D3D11.4 fence is signalled on the render thread at stage
//               boundaries (frame start, each render-queue-group end, before
//               Present). ID3D11Fence::GetCompletedValue is safe from any
//               thread, so a worker reads it every 100 ms and logs one line
//               when the GPU has made no progress for SoakGpuStallMs, naming
//               the last completed and the first pending stage, then one
//               "resumed" line (none when the device dies instead).
//   [SOAK]      A heartbeat every 5 s and a main-loop stall detector, both on
//               that worker, so they keep logging while the main thread is
//               blocked.
//   [LIGHTING]  Once per frame on the render thread: ambient, fog, the sun
//               (the engine's TerrainMasterLight) and the main viewport's
//               material scheme; a sudden step logs a line and requests one
//               frame capture (Ogre RenderTarget::writeContentsToFile, the
//               same call OPENSHIM_FRAME_CAPTURE uses).
//
// Off ([Diagnostics] SoakTelemetry = 0, the default) installs nothing. Every
// piece fails closed: a missing Ogre export, a non-D3D11 renderer, a
// single-threaded device or a device without ID3D11Device5 /
// ID3D11DeviceContext4 (older Wine) logs once and leaves that piece off.
//
// Only exported Ogre/D3D11 API is used. The two engine reads are existing
// rows: RenderGlobals (SceneManager at +0x08 and main viewport at +0x1C, as
// dx11_enhanced_fxaa.cpp reads them) and TerrainMasterLight (the sun, as
// pilot_flashlight.cpp's sun watch reads it).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "soak_telemetry.h"

#include "bzr_hooks_internal.h"
#include "d3d11_device_loss_recovery.h"
#include "diagnostic_switch.h"
#include "engine_globals.h"
#include "game_log_path.h"
#include "hook_engine.h"
#include "render_profile_runtime.h"
#include "shim_log.h"
#include "soak_telemetry_policy.h"

#include <Windows.h>
#include <d3d11_4.h>
#include <process.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace SoakTelemetryDetail
    {
        bool g_TrackPasses = false;
        const void* g_LastPass = nullptr;
    }

    namespace
    {
        using namespace SoakTelemetry;

        constexpr char kComponent[] = "soak";
        constexpr DWORD kWatchIntervalMs = 100;
        constexpr uint64_t kHeartbeatMs = 5000;
        constexpr uint64_t kMainLoopStallMs = 2000;
        constexpr uint64_t kTestStallDelayMs = 30000;
        constexpr uint32_t kDefaultGpuStallMs = 1000;
        // Power of two. Live: ~73 stages per frame at ~215 fps, so 1024
        // wrapped in a frame or two and a stall line printed lastDone=? once
        // the flushed-but-unfinished backlog outgrew it. 16384 entries
        // (~1.7 MB of BSS, untouched while the diagnostic is off) hold one
        // full second at that rate.
        constexpr size_t kRingSize = 16384;
        constexpr uint32_t kDeviceRecheckFrames = 120;
        constexpr uint32_t kAcquireRetryFrames = 60;
        constexpr unsigned kAcquireAttempts = 20;

        // --- Ogre exports ---------------------------------------------------
        using FnRootGet = void*(__cdecl*)();
        using FnRootAddFrameListener = void(__thiscall*)(void*, void*);
        using FnRootGetWindow = void*(__thiscall*)(void*);
        using FnRootGetRenderSystem = void*(__thiscall*)(void*);
        using FnRenderSystemViewport = void*(__thiscall*)(void*);
        using FnAddRenderQueueListener = void(__thiscall*)(void*, void*);
        using FnRemoveRenderQueueListener = void(__thiscall*)(void*, void*);
        using FnWindowAttribute = void(__thiscall*)(void*, const std::string&, void*);
        using FnWriteContents = void(__thiscall*)(void*, const std::string&);
        using FnPassParent = const void*(__thiscall*)(const void*);
        using FnStringGetter = const std::string*(__thiscall*)(const void*);
        using FnColourGetter = const float*(__thiscall*)(const void*);
        using FnFloatGetter = float(__thiscall*)(const void*);
        using FnIntGetter = int(__thiscall*)(const void*);
        using FnPtrGetter = void*(__thiscall*)(const void*);

        struct OgreApi
        {
            FnRootGet root = nullptr;
            FnRootAddFrameListener addFrameListener = nullptr;
            FnRootGetWindow autoWindow = nullptr;
            FnRootGetRenderSystem renderSystem = nullptr;
            FnRenderSystemViewport currentViewport = nullptr;
            FnAddRenderQueueListener addRenderQueueListener = nullptr;
            FnRemoveRenderQueueListener removeRenderQueueListener = nullptr;
            FnWriteContents writeContents = nullptr;
            FnPassParent passParent = nullptr;
            FnPassParent techniqueParent = nullptr;
            FnStringGetter resourceName = nullptr;
            FnColourGetter ambient = nullptr;
            FnColourGetter fogColour = nullptr;
            FnFloatGetter fogStart = nullptr;
            FnFloatGetter fogEnd = nullptr;
            FnIntGetter fogMode = nullptr;
            FnPtrGetter viewportCamera = nullptr;
            FnColourGetter cameraPosition = nullptr;
            FnStringGetter viewportScheme = nullptr;
            FnColourGetter lightDirection = nullptr;
            FnColourGetter lightDiffuse = nullptr;
        };
        OgreApi g_Ogre;

        // --- Configuration and lifetime ---------------------------------------
        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_Shutdown{false};
        uint32_t g_GpuStallMs = kDefaultGpuStallMs;
        uint32_t g_TestStallMs = 0;
        HANDLE g_StopEvent = nullptr;
        HANDLE g_Thread = nullptr;
        bool g_ListenerInstalled = false;
        bool g_ListenerWarned = false;

        // --- Render-thread state the watchdog reads ----------------------------
        std::atomic<uint32_t> g_Frame{0};
        std::atomic<uint64_t> g_FirstMissionFrameMs{0};
        std::atomic<bool> g_CaptureBusy{false};
        std::atomic<bool> g_HaveCamera{false};
        // Ogre's render window HWND, set once on the render thread. The
        // watchdog reads it only for IsIconic: a minimized window stops
        // frames and skips Present, which is neither a hang nor a GPU stall.
        std::atomic<HWND> g_RenderHwnd{nullptr};
        std::atomic<float> g_Camera[3] = {};

        // --- GPU fence ---------------------------------------------------------
        // g_Fence is replaced only by the render thread, under the exclusive
        // lock; the watchdog reads its completed value under the shared lock.
        SRWLOCK g_FenceLock = SRWLOCK_INIT;
        ID3D11Fence* g_Fence = nullptr;
        ID3D11DeviceContext4* g_Context4 = nullptr;  // render thread only
        ID3D11Device* g_FenceDevice = nullptr;       // identity, not owned
        std::atomic<uint32_t> g_FenceGeneration{0};
        std::atomic<uint64_t> g_LastSignalled{0};
        // Newest value the GPU has been handed. D3D11 queues a Signal until the
        // command buffer is flushed, and only Present (which follows the
        // "present" stage in Root's frame) is a guaranteed flush. Judging
        // stalls on g_LastSignalled would report a CPU stall mid-frame (a
        // mission load, a debugger) as a GPU stall.
        std::atomic<uint64_t> g_LastSubmitted{0};
        std::atomic<bool> g_FenceDead{false};
        uint64_t g_NextValue = 0;
        bool g_GpuDisabled = false;
        unsigned g_AcquireFailures = 0;
        unsigned g_SeenRecoveries = 0;
        void* g_RegisteredSceneManager = nullptr;

        struct StageInfo
        {
            uint64_t value;
            int64_t qpc;
            uint32_t frame;
            int16_t group;  // -1 outside a render queue group
            char label[8];
            char material[64];
        };
        // No member initializers: static storage is zero-filled, and a
        // non-trivial constructor could make the compiler emit a load-time
        // loop over the whole ring even with the diagnostic off.
        struct RingEntry
        {
            std::atomic<uint32_t> seq;
            StageInfo info;
        };
        RingEntry g_Ring[kRingSize];

        // Watchdog thread only. The test stall freezes fence reads while the
        // GPU keeps completing work, so at high fps the ring overwrites the two
        // stages the stall line names before the threshold passes; these
        // copies are taken while they are still fresh. Real stalls never
        // need them (Present caps the backlog at a few frames).
        struct StagePin
        {
            uint64_t value;
            bool valid;
            StageInfo info;
        };
        StagePin g_TestPins[2];

        // --- Lighting ----------------------------------------------------------
        struct LightingSample
        {
            float ambient[3];
            float fogColour[3];
            float fogStart;
            float fogEnd;
            int fogMode;
            bool haveSun;
            float sunDirection[3];
            float sunDiffuse[3];
            bool haveCamera;
            float camera[3];
            char scheme[48];
        };
        enum LightingField
        {
            kFieldAmbient,
            kFieldFogMode,
            kFieldFogColour,
            kFieldFogStart,
            kFieldFogEnd,
            kFieldSunDirection,
            kFieldSunDiffuse,
            kFieldSun,
            kFieldScheme,
            kFieldCount
        };
        constexpr const char* kFieldNames[kFieldCount] = {
            "ambient", "fogMode", "fogColour", "fogStart", "fogEnd",
            "sunDirection", "sunDiffuse", "sun", "scheme"};
        bool g_LightingApiReady = false;
        bool g_LightingApiFailed = false;
        bool g_HaveLightingBaseline = false;
        LightingSample g_LastLighting = {};
        FieldRateLimit g_FieldLimits[kFieldCount];
        CaptureBudget g_CaptureBudget;
        bool g_CaptureUnavailable = false;
        bool g_CapturePending = false;
        char g_CapturePath[MAX_PATH] = {};

        uint64_t NowMs() { return GetTickCount64(); }

        DWORD ReadUnsigned(const char* environmentName, const char* iniKey, DWORD fallback)
        {
            char value[32] = {};
            const DWORD n = GetEnvironmentVariableA(environmentName, value, static_cast<DWORD>(sizeof(value)));
            if (n > 0 && n < sizeof(value))
            {
                char* end = nullptr;
                const unsigned long parsed = std::strtoul(value, &end, 10);
                if (end && *end == '\0')
                    return static_cast<DWORD>(parsed);
            }
            if (!iniKey)
                return fallback;
            const std::string ini = DiagnosticSwitch::OpenShimIniPath();
            return static_cast<DWORD>(GetPrivateProfileIntA(
                "Diagnostics", iniKey, static_cast<INT>(fallback), ini.c_str()));
        }

        // Bounded copy for log fields: printable ASCII only, and no spaces so
        // the soak runner can split the line on whitespace.
        void CopyLogToken(const char* source, size_t length, char* out, size_t capacity)
        {
            size_t used = 0;
            for (size_t i = 0; i < length && used + 1 < capacity; ++i)
            {
                const char c = source[i];
                if (c == '\0')
                    break;
                out[used++] = (c > 0x20 && c < 0x7F) ? c : '_';
            }
            out[used] = '\0';
        }

        void CurrentMission(char (&out)[Hooks::kQueuedLoadNameBufferLen + 1])
        {
            // Written by the career-stats load hook on the main thread; a torn
            // read only garbles a diagnostic label (perf_telemetry.cpp does the
            // same).
            char raw[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            for (int i = 0; i < Hooks::kQueuedLoadNameBufferLen; ++i)
            {
                raw[i] = Hooks::g_LastKnownQueuedMissionName[i];
                if (raw[i] == '\0')
                    break;
            }
            CopyLogToken(raw, sizeof(raw), out, sizeof(out));
            if (out[0] == '\0')
                std::strcpy(out, "?");
        }

        int CurrentRunState()
        {
            int state = Hooks::kBzrRunStateUnknown;
            return Hooks::TryReadBzrRunState(state) ? state : Hooks::kBzrRunStateUnknown;
        }

        // --- SEH leaves (no C++ objects with destructors) ---------------------
        void* ReadRenderGlobalsField(uintptr_t offset)
        {
            const uintptr_t slot = EngineGlobals::RenderGlobals();
            if (!slot)
                return nullptr;
            __try
            {
                const uintptr_t record = *reinterpret_cast<const uintptr_t*>(slot);
                return record ? *reinterpret_cast<void* const*>(record + offset) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool IsMainViewportCurrent()
        {
            void* const main = ReadRenderGlobalsField(0x1C);
            if (!main || !g_Ogre.root || !g_Ogre.renderSystem || !g_Ogre.currentViewport)
                return false;
            __try
            {
                void* const root = g_Ogre.root();
                void* const renderSystem = root ? g_Ogre.renderSystem(root) : nullptr;
                return renderSystem && g_Ogre.currentViewport(renderSystem) == main;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadPassMaterial(const void* pass, char* out, size_t capacity)
        {
            if (!pass || !g_Ogre.passParent || !g_Ogre.techniqueParent || !g_Ogre.resourceName)
                return false;
            __try
            {
                const void* const technique = g_Ogre.passParent(pass);
                const void* const material = technique ? g_Ogre.techniqueParent(technique) : nullptr;
                if (!material)
                    return false;
                const std::string* const name = g_Ogre.resourceName(material);
                if (!name)
                    return false;
                CopyLogToken(name->c_str(), name->size(), out, capacity);
                return out[0] != '\0';
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Ogre erases the listener if present and does nothing otherwise, so
        // remove-then-add re-arms without ever registering it twice.
        bool RemoveRenderQueueListenerGuarded(void* sceneManager, void* listener)
        {
            if (!g_Ogre.removeRenderQueueListener)
                return true;
            __try
            {
                g_Ogre.removeRenderQueueListener(sceneManager, listener);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool AddRenderQueueListenerGuarded(void* sceneManager, void* listener)
        {
            __try
            {
                g_Ogre.addRenderQueueListener(sceneManager, listener);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool VtableInModule(const void* object, HMODULE module)
        {
            if (!object || !module)
                return false;
            const void* vtable = nullptr;
            __try
            {
                vtable = *static_cast<const void* const*>(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            HMODULE owner = nullptr;
            return GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                      static_cast<LPCWSTR>(vtable), &owner) &&
                   owner == module;
        }

        bool ReadLightingGuarded(void* sceneManager, void* viewport, void* sun, LightingSample& s)
        {
            __try
            {
                const float* const ambient = g_Ogre.ambient(sceneManager);
                const float* const fog = g_Ogre.fogColour(sceneManager);
                if (!ambient || !fog)
                    return false;
                for (int i = 0; i < 3; ++i)
                {
                    s.ambient[i] = ambient[i];
                    s.fogColour[i] = fog[i];
                }
                s.fogStart = g_Ogre.fogStart(sceneManager);
                s.fogEnd = g_Ogre.fogEnd(sceneManager);
                s.fogMode = g_Ogre.fogMode(sceneManager);
                s.haveSun = false;
                if (sun)
                {
                    const float* const direction = g_Ogre.lightDirection(sun);
                    const float* const diffuse = g_Ogre.lightDiffuse(sun);
                    if (direction && diffuse)
                    {
                        for (int i = 0; i < 3; ++i)
                        {
                            s.sunDirection[i] = direction[i];
                            s.sunDiffuse[i] = diffuse[i];
                        }
                        s.haveSun = true;
                    }
                }
                s.scheme[0] = '\0';
                s.haveCamera = false;
                if (viewport)
                {
                    const std::string* const scheme = g_Ogre.viewportScheme(viewport);
                    if (scheme)
                        CopyLogToken(scheme->c_str(), scheme->size(), s.scheme, sizeof(s.scheme));
                    void* const camera = g_Ogre.viewportCamera(viewport);
                    const float* const position = camera ? g_Ogre.cameraPosition(camera) : nullptr;
                    if (position)
                    {
                        for (int i = 0; i < 3; ++i)
                            s.camera[i] = position[i];
                        s.haveCamera = true;
                    }
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* ReadSunGuarded(uintptr_t global)
        {
            __try
            {
                return *reinterpret_cast<void* const*>(global);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // --- Fence ring --------------------------------------------------------
        void WriteStage(const StageInfo& info)
        {
            RingEntry& entry = g_Ring[info.value & (kRingSize - 1)];
            entry.seq.fetch_add(1, std::memory_order_relaxed);  // odd: writing
            std::atomic_thread_fence(std::memory_order_release);
            entry.info = info;
            entry.seq.fetch_add(1, std::memory_order_release);  // even: stable
        }

        bool ReadStage(uint64_t value, StageInfo& out)
        {
            const RingEntry& entry = g_Ring[value & (kRingSize - 1)];
            for (int attempt = 0; attempt < 3; ++attempt)
            {
                const uint32_t before = entry.seq.load(std::memory_order_acquire);
                if (before & 1u)
                    continue;
                out = entry.info;
                std::atomic_thread_fence(std::memory_order_acquire);
                if (entry.seq.load(std::memory_order_relaxed) == before)
                    return out.value == value;
            }
            return false;
        }

        bool LookupStage(uint64_t value, StageInfo& out)
        {
            for (const StagePin& pin : g_TestPins)
            {
                if (pin.valid && pin.value == value)
                {
                    out = pin.info;
                    return true;
                }
            }
            return ReadStage(value, out);
        }

        void FormatStage(uint64_t value, char* out, size_t capacity)
        {
            StageInfo info = {};
            if (value == 0 || !LookupStage(value, info))
            {
                std::snprintf(out, capacity, "%s", value == 0 ? "none" : "?");
                return;
            }
            char group[8] = "-";
            if (info.group >= 0)
                std::snprintf(group, sizeof(group), "%d", info.group);
            std::snprintf(out, capacity, "%s/%s/%s", info.label, group,
                          info.material[0] ? info.material : "-");
        }

        // Render thread. Records the stage, then queues the signal for it.
        void SignalStage(const char* label, int group)
        {
            if (!g_Context4 || !g_Fence)
                return;
            StageInfo info = {};
            info.value = ++g_NextValue;
            LARGE_INTEGER qpc = {};
            QueryPerformanceCounter(&qpc);
            info.qpc = qpc.QuadPart;
            info.frame = g_Frame.load(std::memory_order_relaxed);
            info.group = static_cast<int16_t>(group);
            std::snprintf(info.label, sizeof(info.label), "%s", label);
            if (!ReadPassMaterial(SoakTelemetryDetail::g_LastPass, info.material, sizeof(info.material)))
                info.material[0] = '\0';
            SoakTelemetryDetail::g_LastPass = nullptr;
            WriteStage(info);
            if (SUCCEEDED(g_Context4->Signal(g_Fence, info.value)))
                g_LastSignalled.store(info.value, std::memory_order_release);
        }

        void DisableGpuWatch(const char* why, HRESULT hr = S_OK)
        {
            g_GpuDisabled = true;
            SoakTelemetryDetail::g_TrackPasses = false;
            if (hr != S_OK)
                LogShimA(LogLevel::Warn, kComponent, "[GPUWATCH] off: %s (hr=0x%08X)", why,
                         static_cast<unsigned>(hr));
            else
                LogShimA(LogLevel::Warn, kComponent, "[GPUWATCH] off: %s", why);
        }

        void ReleaseFence(const char* reason)
        {
            AcquireSRWLockExclusive(&g_FenceLock);
            ID3D11Fence* const fence = g_Fence;
            g_Fence = nullptr;
            g_FenceGeneration.fetch_add(1, std::memory_order_release);
            ReleaseSRWLockExclusive(&g_FenceLock);
            if (fence)
                fence->Release();
            if (g_Context4)
                g_Context4->Release();
            g_Context4 = nullptr;
            g_FenceDevice = nullptr;
            g_LastSignalled.store(0, std::memory_order_release);
            g_LastSubmitted.store(0, std::memory_order_release);
            g_NextValue = 0;
            g_FenceDead.store(false, std::memory_order_release);
            LogShimA(LogLevel::Info, kComponent, "[GPUWATCH] fence released (%s)", reason);
        }

        FnWindowAttribute s_attribute = nullptr;

        // Asks Ogre's render window for a custom attribute; false when the
        // export or the window is missing or Ogre throws.
        bool QueryWindowAttribute(const char* name, void* out)
        {
            if (!s_attribute)
            {
                const HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                s_attribute = renderer ? reinterpret_cast<FnWindowAttribute>(GetProcAddress(renderer,
                    "?getCustomAttribute@D3D11RenderWindowHwnd@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAX@Z"))
                    : nullptr;
                if (!s_attribute)
                    return false;
            }
            try
            {
                void* const root = g_Ogre.root();
                void* const window = root ? g_Ogre.autoWindow(root) : nullptr;
                if (!window)
                    return false;
                s_attribute(window, std::string(name), out);
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        // The device behind Ogre's render window. Not AddRef'd.
        ID3D11Device* QueryRendererDevice()
        {
            ID3D11Device* device = nullptr;
            if (!QueryWindowAttribute("D3DDEVICE", &device))
                return nullptr;
            // The attribute must hand back a real D3D11 device, whose vtable
            // lives in d3d11.dll (native or DXVK's); anything else stands down.
            return VtableInModule(device, GetModuleHandleW(L"d3d11.dll")) ? device : nullptr;
        }

        void TryAcquireFence()
        {
            const int backend = RenderProfiles::IdentifyActiveRenderSystem();
            if (backend == 0 || backend == -1)
                return;  // not identified yet
            if (backend != 1)
            {
                DisableGpuWatch("the renderer is not Direct3D 11");
                return;
            }
            ID3D11Device* const device = QueryRendererDevice();
            if (!device)
            {
                if (++g_AcquireFailures >= kAcquireAttempts)
                    DisableGpuWatch("Ogre's render window did not yield a D3D11 device");
                return;
            }
            if (device->GetCreationFlags() & D3D11_CREATE_DEVICE_SINGLETHREADED)
            {
                DisableGpuWatch("the device is single-threaded, so its fence cannot be read off the render thread");
                return;
            }
            ID3D11Device5* device5 = nullptr;
            HRESULT hr = device->QueryInterface(__uuidof(ID3D11Device5), reinterpret_cast<void**>(&device5));
            if (FAILED(hr) || !device5)
            {
                DisableGpuWatch("ID3D11Device5 unavailable", hr);
                return;
            }
            ID3D11DeviceContext* context = nullptr;
            device->GetImmediateContext(&context);
            ID3D11DeviceContext4* context4 = nullptr;
            hr = context ? context->QueryInterface(__uuidof(ID3D11DeviceContext4), reinterpret_cast<void**>(&context4))
                         : E_NOINTERFACE;
            if (context)
                context->Release();
            if (FAILED(hr) || !context4)
            {
                device5->Release();
                DisableGpuWatch("ID3D11DeviceContext4 unavailable", hr);
                return;
            }
            ID3D11Fence* fence = nullptr;
            hr = device5->CreateFence(0, D3D11_FENCE_FLAG_NONE, __uuidof(ID3D11Fence), reinterpret_cast<void**>(&fence));
            device5->Release();
            if (FAILED(hr) || !fence)
            {
                context4->Release();
                DisableGpuWatch("CreateFence failed", hr);
                return;
            }
            g_Context4 = context4;
            g_FenceDevice = device;
            g_NextValue = 0;
            g_LastSignalled.store(0, std::memory_order_release);
            g_LastSubmitted.store(0, std::memory_order_release);
            g_FenceDead.store(false, std::memory_order_release);
            AcquireSRWLockExclusive(&g_FenceLock);
            g_Fence = fence;
            const uint32_t generation = g_FenceGeneration.fetch_add(1, std::memory_order_release) + 1;
            ReleaseSRWLockExclusive(&g_FenceLock);
            g_AcquireFailures = 0;
            g_SeenRecoveries = D3D11DeviceRecoveryCount();
            LogShimA(LogLevel::Info, kComponent,
                     "[GPUWATCH] armed: fence on device=0x%p generation=%u stallMs=%u",
                     static_cast<void*>(device), generation, g_GpuStallMs);
        }

        // frameStarted, render thread, outside any rendering. A recovered
        // or replaced device makes the fence an orphan of the old one. A
        // removed device (the watchdog reads UINT64_MAX) keeps its fence and
        // context references until a new device appears, so the new one
        // cannot reuse the old address and look unchanged.
        void MaintainFence(uint32_t frame)
        {
            if (g_GpuDisabled)
                return;
            if (g_Fence)
            {
                if (D3D11DeviceRecoveryCount() != g_SeenRecoveries)
                {
                    ReleaseFence("device recovered");
                }
                else
                {
                    const bool dead = g_FenceDead.load(std::memory_order_acquire);
                    const uint32_t interval = dead ? kAcquireRetryFrames : kDeviceRecheckFrames;
                    if (frame % interval != 0)
                        return;
                    ID3D11Device* const current = QueryRendererDevice();
                    if (!current || current == g_FenceDevice)
                        return;
                    ReleaseFence("device replaced");
                }
            }
            if (!g_Fence && (g_AcquireFailures == 0 || frame % kAcquireRetryFrames == 0))
                TryAcquireFence();
        }

        // --- Ogre listeners ----------------------------------------------------
        // Ogre::RenderQueueListener as OgreMain 1.x lays it out: deleting dtor,
        // preRenderQueues, postRenderQueues, renderQueueStarted,
        // renderQueueEnded (same shape as dx11_enhanced_fxaa.cpp's listener).
        class StageQueueListener
        {
        public:
            virtual ~StageQueueListener() = default;
            virtual void preRenderQueues() {}
            virtual void postRenderQueues() {}
            virtual void renderQueueStarted(unsigned char, const void*, bool&) {}
            virtual void renderQueueEnded(unsigned char queueGroup, const void*, bool&)
            {
                if (g_Shutdown.load(std::memory_order_relaxed) || !g_Context4)
                    return;
                SignalStage(IsMainViewportCurrent() ? "rq" : "rq-aux", queueGroup);
            }
        };
        StageQueueListener g_QueueListener;

        void EnsureQueueListener()
        {
            if (g_GpuDisabled || !g_Fence || !g_Ogre.addRenderQueueListener)
                return;
            void* const sceneManager = ReadRenderGlobalsField(0x08);
            if (!sceneManager)
                return;
            // Re-arm on every mission start as well as on a new pointer: a
            // SceneManager rebuilt at the same address has an empty listener
            // list, and the stall lines would silently lose their rq stages.
            static int s_lastRunState = Hooks::kBzrRunStateUnknown;
            const int runState = CurrentRunState();
            const bool missionStarted = runState == Hooks::kBzrRunStateStarted &&
                                        s_lastRunState != Hooks::kBzrRunStateStarted;
            s_lastRunState = runState;
            if (sceneManager == g_RegisteredSceneManager &&
                (!missionStarted || !g_Ogre.removeRenderQueueListener))
                return;  // without remove, a re-add would register it twice
            if (sceneManager == g_RegisteredSceneManager &&
                !RemoveRenderQueueListenerGuarded(sceneManager, &g_QueueListener))
            {
                ReleaseFence("removeRenderQueueListener faulted");
                DisableGpuWatch("removeRenderQueueListener faulted");
                return;
            }
            if (!AddRenderQueueListenerGuarded(sceneManager, &g_QueueListener))
            {
                // Drop the fence and context too: MaintainFence stops for good
                // once disabled, and would otherwise keep a removed device alive.
                ReleaseFence("addRenderQueueListener faulted");
                DisableGpuWatch("addRenderQueueListener faulted");
                return;
            }
            g_RegisteredSceneManager = sceneManager;
            LogShimA(LogLevel::Info, kComponent,
                     "[GPUWATCH] render queue stages armed on SceneManager=0x%p", sceneManager);
        }

        // --- Lighting monitor --------------------------------------------------
        bool BindLightingApi()
        {
            if (g_LightingApiReady || g_LightingApiFailed)
                return g_LightingApiReady;
            using Hooks::ResolveOgreProc;
            g_Ogre.ambient = ResolveOgreProc<FnColourGetter>("?getAmbientLight@SceneManager@Ogre@@QBEABVColourValue@2@XZ");
            g_Ogre.fogColour = ResolveOgreProc<FnColourGetter>("?getFogColour@SceneManager@Ogre@@UBEABVColourValue@2@XZ");
            g_Ogre.fogStart = ResolveOgreProc<FnFloatGetter>("?getFogStart@SceneManager@Ogre@@UBEMXZ");
            g_Ogre.fogEnd = ResolveOgreProc<FnFloatGetter>("?getFogEnd@SceneManager@Ogre@@UBEMXZ");
            g_Ogre.fogMode = ResolveOgreProc<FnIntGetter>("?getFogMode@SceneManager@Ogre@@UBE?AW4FogMode@2@XZ");
            g_Ogre.viewportCamera = ResolveOgreProc<FnPtrGetter>("?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ");
            g_Ogre.cameraPosition = ResolveOgreProc<FnColourGetter>("?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ");
            g_Ogre.viewportScheme = ResolveOgreProc<FnStringGetter>(
                "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_Ogre.lightDirection = ResolveOgreProc<FnColourGetter>("?getDerivedDirection@Light@Ogre@@QBEABVVector3@2@XZ");
            g_Ogre.lightDiffuse = ResolveOgreProc<FnColourGetter>("?getDiffuseColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            g_LightingApiReady = g_Ogre.ambient && g_Ogre.fogColour && g_Ogre.fogStart && g_Ogre.fogEnd &&
                                 g_Ogre.fogMode && g_Ogre.viewportCamera && g_Ogre.cameraPosition &&
                                 g_Ogre.viewportScheme && g_Ogre.lightDirection && g_Ogre.lightDiffuse;
            g_LightingApiFailed = !g_LightingApiReady;
            if (g_LightingApiFailed)
                LogShimA(LogLevel::Warn, kComponent, "[LIGHTING] monitor off: Ogre scene/light exports unresolved");
            return g_LightingApiReady;
        }

        void FormatTriple(const float v[3], char* out, size_t capacity)
        {
            std::snprintf(out, capacity, "%.3f,%.3f,%.3f", v[0], v[1], v[2]);
        }

        // Asks for this frame's capture once and returns what the line reports.
        const char* RequestCapture(uint64_t now)
        {
            if (g_CaptureUnavailable || !g_Ogre.writeContents || !g_Ogre.autoWindow)
                return "unavailable";
            if (g_CapturePending)
                return g_CapturePath;
            if (!g_CaptureBudget.Allow(now))
                return "none";
            char name[96] = {};
            std::snprintf(name, sizeof(name), "openshim_soak_lighting_%lu_%02u.png",
                          GetCurrentProcessId(), g_CaptureBudget.taken);
            // Kept verbatim (the game folder can contain spaces): capture= is
            // the last field of the line and runs to its end.
            const std::string path = GetGameLogPath(name);
            if (path.empty() || path.size() >= sizeof(g_CapturePath))
                return "unavailable";
            std::memcpy(g_CapturePath, path.c_str(), path.size() + 1);
            g_CapturePending = true;
            return g_CapturePath;
        }

        void LogLightingChange(LightingField field, const char* before, const char* after,
                               uint32_t frame, uint64_t now)
        {
            if (!g_FieldLimits[field].Allow(now))
                return;
            const char* const capture = RequestCapture(now);
            char mission[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            CurrentMission(mission);
            LogShimA(LogLevel::Info, kComponent,
                     "[LIGHTING] change field=%s old=%s new=%s frame=%u mission=%s capture=%s",
                     kFieldNames[field], before, after, frame, mission, capture);
        }

        void CompareLighting(const LightingSample& a, const LightingSample& b, uint32_t frame, uint64_t now)
        {
            char before[64] = {};
            char after[64] = {};
            const auto triple = [&](LightingField field, const float* x, const float* y) {
                FormatTriple(x, before, sizeof(before));
                FormatTriple(y, after, sizeof(after));
                LogLightingChange(field, before, after, frame, now);
            };
            if (ColourJumped(a.ambient, b.ambient))
                triple(kFieldAmbient, a.ambient, b.ambient);
            if (a.fogMode != b.fogMode)
            {
                std::snprintf(before, sizeof(before), "%d", a.fogMode);
                std::snprintf(after, sizeof(after), "%d", b.fogMode);
                LogLightingChange(kFieldFogMode, before, after, frame, now);
            }
            if (ColourJumped(a.fogColour, b.fogColour))
                triple(kFieldFogColour, a.fogColour, b.fogColour);
            if (FogDistanceJumped(a.fogStart, b.fogStart))
            {
                std::snprintf(before, sizeof(before), "%.1f", a.fogStart);
                std::snprintf(after, sizeof(after), "%.1f", b.fogStart);
                LogLightingChange(kFieldFogStart, before, after, frame, now);
            }
            if (FogDistanceJumped(a.fogEnd, b.fogEnd))
            {
                std::snprintf(before, sizeof(before), "%.1f", a.fogEnd);
                std::snprintf(after, sizeof(after), "%.1f", b.fogEnd);
                LogLightingChange(kFieldFogEnd, before, after, frame, now);
            }
            if (a.haveSun && b.haveSun)
            {
                if (DirectionJumped(a.sunDirection, b.sunDirection))
                    triple(kFieldSunDirection, a.sunDirection, b.sunDirection);
                if (ColourJumped(a.sunDiffuse, b.sunDiffuse))
                    triple(kFieldSunDiffuse, a.sunDiffuse, b.sunDiffuse);
            }
            else if (a.haveSun != b.haveSun)
            {
                LogLightingChange(kFieldSun, a.haveSun ? "present" : "absent",
                                  b.haveSun ? "present" : "absent", frame, now);
            }
            if (std::strcmp(a.scheme, b.scheme) != 0)
                LogLightingChange(kFieldScheme, a.scheme[0] ? a.scheme : "-", b.scheme[0] ? b.scheme : "-",
                                  frame, now);
        }

        // Frames rendered in a started mission before lighting is compared.
        // The run state flips to "started" a few frames before the world's
        // ambient, fog and sun are set up (live: every field stepped from zero
        // at frame 3, then the load hitch), so the first frames are setup.
        constexpr uint32_t kLightingSettleFrames = 60;
        uint32_t g_StartedFrames = 0;

        void SampleLighting(uint32_t frame)
        {
            // Only a running mission has lighting worth watching; any other
            // state drops the baseline so a mission start is not a "change".
            if (CurrentRunState() != Hooks::kBzrRunStateStarted)
            {
                g_HaveLightingBaseline = false;
                g_StartedFrames = 0;
                g_HaveCamera.store(false, std::memory_order_relaxed);
                return;
            }
            if (!BindLightingApi())
                return;
            void* const sceneManager = Hooks::GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;
            // The row lookup caches successes; keep the hit here too so the
            // per-frame cost is one load.
            static uint32_t s_sunGlobal = 0;
            if (!s_sunGlobal)
                s_sunGlobal = HookEngine::EngineAddress("TerrainMasterLight");
            void* sun = nullptr;
            if (const uint32_t global = s_sunGlobal)
            {
                sun = ReadSunGuarded(global);
                if (sun && !Hooks::IsLiveOgreLight(sun))
                    sun = nullptr;
            }
            LightingSample sample = {};
            if (!ReadLightingGuarded(sceneManager, ReadRenderGlobalsField(0x1C), sun, sample))
                return;
            if (sample.haveCamera)
            {
                for (int i = 0; i < 3; ++i)
                    g_Camera[i].store(sample.camera[i], std::memory_order_relaxed);
            }
            g_HaveCamera.store(sample.haveCamera, std::memory_order_release);
            if (g_StartedFrames < kLightingSettleFrames)
                ++g_StartedFrames;
            else if (g_HaveLightingBaseline)
                CompareLighting(g_LastLighting, sample, frame, NowMs());
            g_LastLighting = sample;
            g_HaveLightingBaseline = true;
        }

        // frameRenderingQueued: every target has rendered, buffers not swapped.
        void WritePendingCapture()
        {
            if (!g_CapturePending)
                return;
            g_CapturePending = false;
            g_CaptureBusy.store(true, std::memory_order_release);
            try
            {
                void* const root = g_Ogre.root();
                void* const window = root ? g_Ogre.autoWindow(root) : nullptr;
                if (window)
                    g_Ogre.writeContents(window, std::string(g_CapturePath));
                else
                    LogShimA(LogLevel::Warn, kComponent, "[LIGHTING] capture skipped: no render window");
            }
            catch (...)
            {
                g_CaptureUnavailable = true;
                LogShimA(LogLevel::Warn, kComponent, "[LIGHTING] capture write failed; captures off");
            }
            g_CaptureBusy.store(false, std::memory_order_release);
        }

        // Ogre::FrameListener, laid out to its 1.10 vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor (the shape
        // gpu_skinning.cpp and terrain_proxy.cpp register).
        class SoakFrameListener
        {
        public:
            virtual bool frameStarted(const void*)
            {
                if (g_Shutdown.load(std::memory_order_relaxed))
                    return true;
                const uint32_t frame = g_Frame.fetch_add(1, std::memory_order_release) + 1;
                if (g_TestStallMs && g_FirstMissionFrameMs.load(std::memory_order_relaxed) == 0 &&
                    CurrentRunState() == Hooks::kBzrRunStateStarted)
                    g_FirstMissionFrameMs.store(NowMs(), std::memory_order_release);
                MaintainFence(frame);
                EnsureQueueListener();
                SignalStage("frame", -1);
                SampleLighting(frame);
                if (!g_RenderHwnd.load(std::memory_order_relaxed))
                {
                    HWND hwnd = nullptr;
                    if (QueryWindowAttribute("WINDOW", &hwnd) && hwnd && IsWindow(hwnd))
                        g_RenderHwnd.store(hwnd, std::memory_order_release);
                }
                return true;
            }
            virtual bool frameRenderingQueued(const void*)
            {
                if (g_Shutdown.load(std::memory_order_relaxed))
                    return true;
                WritePendingCapture();
                SignalStage("present", -1);
                // Root swaps buffers right after this callback; that Present
                // flushes every signal up to here.
                // Flush explicitly: Root skips Present for an inactive or
                // hidden target, and another listener may block before the
                // swap. Present flushes anyway, but with ~73 Signals per frame this
                // can split command buffers on some drivers, so telemetry ON can
                // shift GPU timing a little: compare TDR rates ON vs OFF before
                // reading "no repro" as a fix.
                if (g_Context4)
                    g_Context4->Flush();
                g_LastSubmitted.store(g_LastSignalled.load(std::memory_order_relaxed),
                                      std::memory_order_release);
                return true;
            }
            virtual bool frameEnded(const void*)
            {
                // A Pass noted after the last signal (overlays, loading
                // screens) may be freed by a mission load before the next one.
                SoakTelemetryDetail::g_LastPass = nullptr;
                return true;
            }
            virtual ~SoakFrameListener() = default;
        };
        SoakFrameListener g_FrameListener;

        // --- Watchdog thread ---------------------------------------------------
        struct WatchState
        {
            StallTracker gpu;
            StallTracker mainLoop;
            uint32_t seenGeneration = 0;
            bool fenceDead = false;
            bool testDone = false;
            uint64_t testUntilMs = 0;
            uint64_t testFrozen = 0;
            uint64_t lastHeartbeatMs = 0;
            uint64_t fpsSampleMs = 0;
            uint32_t fpsSampleFrame = 0;
            double fps = 0.0;
        };

        void LogGpuStall(uint64_t stalledMs, uint64_t completed, uint64_t newest)
        {
            char lastDone[96] = {};
            char firstPending[96] = {};
            FormatStage(completed, lastDone, sizeof(lastDone));
            FormatStage(completed + 1, firstPending, sizeof(firstPending));
            StageInfo pendingInfo = {};
            const uint32_t frame = LookupStage(completed + 1, pendingInfo)
                ? pendingInfo.frame : g_Frame.load(std::memory_order_acquire);
            char mission[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            CurrentMission(mission);
            char camera[64] = "?";
            if (g_HaveCamera.load(std::memory_order_acquire))
                std::snprintf(camera, sizeof(camera), "(%.1f,%.1f,%.1f)",
                              g_Camera[0].load(std::memory_order_relaxed),
                              g_Camera[1].load(std::memory_order_relaxed),
                              g_Camera[2].load(std::memory_order_relaxed));
            LogShimA(LogLevel::Warn, kComponent,
                     "[GPUWATCH] stall ms=%llu frame=%u lastDone=%s firstPending=%s pending=%llu mission=%s cam=%s",
                     static_cast<unsigned long long>(stalledMs), frame, lastDone, firstPending,
                     static_cast<unsigned long long>(newest - completed), mission, camera);
        }

        void WatchGpu(WatchState& w, uint64_t now)
        {
            AcquireSRWLockShared(&g_FenceLock);
            ID3D11Fence* const fence = g_Fence;
            const uint32_t generation = g_FenceGeneration.load(std::memory_order_acquire);
            const uint64_t completedReal = fence ? fence->GetCompletedValue() : 0;
            ReleaseSRWLockShared(&g_FenceLock);
            if (generation != w.seenGeneration)
            {
                w.seenGeneration = generation;
                w.fenceDead = false;
                w.gpu.Reset(now);
            }
            if (!fence || w.fenceDead)
                return;
            if (completedReal == UINT64_MAX)
            {
                // A removed device completes everything. The episode ends
                // without a "resumed" line; the render thread re-arms.
                w.fenceDead = true;
                w.gpu.Reset(now);
                g_FenceDead.store(true, std::memory_order_release);
                LogShimA(LogLevel::Warn, kComponent,
                         "[GPUWATCH] device removed (fence completed value is UINT64_MAX); waiting for a new device");
                return;
            }
            // Only flushed signals can be pending on the GPU (see g_LastSubmitted).
            const uint64_t newest = g_LastSubmitted.load(std::memory_order_acquire);
            uint64_t completed = completedReal;
            if (g_TestStallMs && !w.testDone)
            {
                const uint64_t first = g_FirstMissionFrameMs.load(std::memory_order_acquire);
                if (first && now >= first + kTestStallDelayMs)
                {
                    w.testDone = true;
                    w.testFrozen = completedReal;
                    w.testUntilMs = now + g_TestStallMs;
                    LogShimA(LogLevel::Info, kComponent,
                             "[SOAK] test GPU stall injected for ms=%u (fence reads frozen; the GPU is not stalled)",
                             g_TestStallMs);
                }
            }
            if (w.testUntilMs && now < w.testUntilMs)
            {
                completed = w.testFrozen < completedReal ? w.testFrozen : completedReal;
                for (unsigned i = 0; i < 2; ++i)
                {
                    StagePin& pin = g_TestPins[i];
                    const uint64_t want = completed + i;
                    if (!pin.valid || pin.value != want)
                    {
                        pin.value = want;
                        pin.valid = want != 0 && ReadStage(want, pin.info);
                    }
                }
            }
            else
            {
                w.testUntilMs = 0;
                g_TestPins[0].valid = g_TestPins[1].valid = false;
            }

            uint64_t stalledMs = 0;
            switch (w.gpu.Tick(now, completed, newest > completed, g_GpuStallMs, stalledMs))
            {
            case StallEvent::Began:
                LogGpuStall(stalledMs, completed, newest);
                break;
            case StallEvent::Ended:
                LogShimA(LogLevel::Info, kComponent, "[GPUWATCH] resumed after ms=%llu",
                         static_cast<unsigned long long>(stalledMs));
                break;
            default:
                break;
            }
        }

        // Minimized: the engine stops frames and Root skips Present. Neither
        // is a stall, and the soak runner restores the window itself.
        bool RenderWindowIconic()
        {
            const HWND hwnd = g_RenderHwnd.load(std::memory_order_acquire);
            return hwnd && IsIconic(hwnd);
        }

        void WatchMainLoop(WatchState& w, uint64_t now)
        {
            const uint32_t frame = g_Frame.load(std::memory_order_acquire);
            if (frame == 0)
                return;  // listener not installed yet
            if (RenderWindowIconic())
            {
                if (!w.mainLoop.inEpisode)
                    w.mainLoop.Reset(now);
                return;
            }
            if (g_CaptureBusy.load(std::memory_order_acquire))
            {
                // A PNG write blocks the frame by design; not a stall.
                if (!w.mainLoop.inEpisode)
                    w.mainLoop.Reset(now);
                return;
            }
            uint64_t stalledMs = 0;
            switch (w.mainLoop.Tick(now, frame, true, kMainLoopStallMs, stalledMs))
            {
            case StallEvent::Began:
                LogShimA(LogLevel::Warn, kComponent, "[SOAK] main-loop stalled ms=%llu lastFrame=%u",
                         static_cast<unsigned long long>(stalledMs), frame);
                break;
            case StallEvent::Ended:
                LogShimA(LogLevel::Info, kComponent, "[SOAK] main-loop resumed after ms=%llu",
                         static_cast<unsigned long long>(stalledMs));
                break;
            default:
                break;
            }
        }

        void Heartbeat(WatchState& w, uint64_t now)
        {
            const uint32_t frame = g_Frame.load(std::memory_order_acquire);
            if (w.fpsSampleMs == 0)
            {
                w.fpsSampleMs = now;
                w.fpsSampleFrame = frame;
            }
            else if (now - w.fpsSampleMs >= 1000)
            {
                w.fps = static_cast<double>(frame - w.fpsSampleFrame) * 1000.0 /
                        static_cast<double>(now - w.fpsSampleMs);
                w.fpsSampleMs = now;
                w.fpsSampleFrame = frame;
            }
            if (w.lastHeartbeatMs != 0 && now - w.lastHeartbeatMs < kHeartbeatMs)
                return;
            w.lastHeartbeatMs = now;
            char mission[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            CurrentMission(mission);
            LogShimA(LogLevel::Info, kComponent, "[SOAK] heartbeat frame=%u fps=%.1f run=%d mission=%s",
                     frame, w.fps, CurrentRunState(), mission);
        }

        unsigned __stdcall WatchdogThread(void*)
        {
            WatchState w;
            const uint64_t start = NowMs();
            w.gpu.Reset(start);
            w.mainLoop.Reset(start);
            while (WaitForSingleObject(g_StopEvent, kWatchIntervalMs) == WAIT_TIMEOUT)
            {
                const uint64_t now = NowMs();
                WatchGpu(w, now);
                WatchMainLoop(w, now);
                Heartbeat(w, now);
            }
            return 0;
        }

        bool BindCoreApi()
        {
            using Hooks::ResolveOgreProc;
            g_Ogre.root = ResolveOgreProc<FnRootGet>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            g_Ogre.addFrameListener = ResolveOgreProc<FnRootAddFrameListener>(
                "?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
            g_Ogre.autoWindow = ResolveOgreProc<FnRootGetWindow>(
                "?getAutoCreatedWindow@Root@Ogre@@QAEPAVRenderWindow@2@XZ");
            g_Ogre.renderSystem = ResolveOgreProc<FnRootGetRenderSystem>(
                "?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ");
            g_Ogre.currentViewport = ResolveOgreProc<FnRenderSystemViewport>(
                "?_getViewport@RenderSystem@Ogre@@UAEPAVViewport@2@XZ");
            g_Ogre.addRenderQueueListener = ResolveOgreProc<FnAddRenderQueueListener>(
                "?addRenderQueueListener@SceneManager@Ogre@@UAEXPAVRenderQueueListener@2@@Z");
            g_Ogre.removeRenderQueueListener = ResolveOgreProc<FnRemoveRenderQueueListener>(
                "?removeRenderQueueListener@SceneManager@Ogre@@UAEXPAVRenderQueueListener@2@@Z");
            g_Ogre.writeContents = ResolveOgreProc<FnWriteContents>(
                "?writeContentsToFile@RenderTarget@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_Ogre.passParent = ResolveOgreProc<FnPassParent>("?getParent@Pass@Ogre@@QBEPAVTechnique@2@XZ");
            g_Ogre.techniqueParent = ResolveOgreProc<FnPassParent>("?getParent@Technique@Ogre@@QBEPAVMaterial@2@XZ");
            g_Ogre.resourceName = ResolveOgreProc<FnStringGetter>(
                "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            return g_Ogre.root && g_Ogre.addFrameListener;
        }
    }

    void InitializeSoakTelemetry()
    {
        if (!DiagnosticSwitch::Requested("OPENSHIM_SOAK_TELEMETRY", "Diagnostics", "SoakTelemetry"))
            return;
        DWORD stallMs = ReadUnsigned("OPENSHIM_SOAK_GPU_STALL_MS", "SoakGpuStallMs", kDefaultGpuStallMs);
        if (stallMs < 200)
            stallMs = 200;
        if (stallMs > 60000)
            stallMs = 60000;
        g_GpuStallMs = stallMs;
        const DWORD testMs = ReadUnsigned("OPENSHIM_SOAK_TEST_STALL_MS", nullptr, 0);
        g_TestStallMs = testMs > 600000 ? 600000 : testMs;

        g_StopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (!g_StopEvent)
        {
            LogShimA(LogLevel::Warn, kComponent, "[SOAK] telemetry off: CreateEvent failed (%lu)", GetLastError());
            return;
        }
        g_Thread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, &WatchdogThread, nullptr, 0, nullptr));
        if (!g_Thread)
        {
            CloseHandle(g_StopEvent);
            g_StopEvent = nullptr;
            LogShimA(LogLevel::Warn, kComponent, "[SOAK] telemetry off: watchdog thread did not start");
            return;
        }
        SoakTelemetryDetail::g_TrackPasses = true;
        g_Enabled.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent,
                 "[SOAK] telemetry on: gpuStallMs=%u mainLoopStallMs=%u heartbeatMs=%u testStallMs=%u",
                 g_GpuStallMs, static_cast<unsigned>(kMainLoopStallMs), static_cast<unsigned>(kHeartbeatMs),
                 g_TestStallMs);
    }

    void SoakTelemetryRenderTick()
    {
        if (g_ListenerInstalled || !g_Enabled.load(std::memory_order_acquire) ||
            g_Shutdown.load(std::memory_order_acquire))
            return;
        void* root = nullptr;
        if (BindCoreApi())
        {
            try
            {
                root = g_Ogre.root();
            }
            catch (...)
            {
                root = nullptr;
            }
        }
        if (!root)
        {
            // Retried at the next seam call; Root may not exist yet.
            if (!g_ListenerWarned)
                LogShimA(LogLevel::Info, kComponent, "[SOAK] Ogre Root not ready; frame listener will retry");
            g_ListenerWarned = true;
            return;
        }
        g_ListenerInstalled = true;
        g_Ogre.addFrameListener(root, &g_FrameListener);
        LogShimA(LogLevel::Info, kComponent, "[SOAK] frame listener installed");
    }

    void ShutdownSoakTelemetry()
    {
        if (g_Shutdown.exchange(true, std::memory_order_acq_rel))
            return;
        SoakTelemetryDetail::g_TrackPasses = false;
        if (g_StopEvent)
            SetEvent(g_StopEvent);
        if (g_Thread)
        {
            if (WaitForSingleObject(g_Thread, 2000) == WAIT_TIMEOUT)
                LogShimA(LogLevel::Warn, kComponent, "[SOAK] watchdog did not stop within 2 s");
            CloseHandle(g_Thread);
            g_Thread = nullptr;
        }
        if (g_Enabled.load(std::memory_order_acquire))
            LogShimA(LogLevel::Info, kComponent, "[SOAK] telemetry stopped");
    }
}
