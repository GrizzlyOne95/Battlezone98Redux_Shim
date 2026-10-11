// Direct3D 11 device-loss recovery: recreate the device only once the GPU has
// settled, and never fall back to the software rasterizer while the hardware
// adapter is merely resetting.
//
// Why: when the display driver resets the GPU (a TDR; on 2026-10-07 a four-
// client co-op load on an RTX 5080 logged sixteen nvlddmkm 153 events over
// eight seconds), Ogre's RenderSystem_Direct3D11 sees the device as lost and
// recreates it at once. It did so inside the reset window, so:
//   * the new device was removed again moments later and every buffer it was
//     asked for failed with DXGI_ERROR_DEVICE_REMOVED, which escaped into the
//     game as an unhandled C++ exception; and
//   * a second recreation enumerated only "Microsoft Basic Render Driver"
//     because the hardware adapter was briefly absent, created a WARP device,
//     ran out of memory creating textures and crashed in the renderer.
// Two clients crashed and two shut down. Nothing was wrong with the game's own
// restore path; it was simply handed a device that could not survive.
//
// What: RenderSystem_Direct3D11.dll's import of D3D11CreateDevice is wrapped.
// The first successful creation records the hardware adapter (by LUID). Every
// later creation is a recovery: before forwarding it, the hook creates small
// probe devices on that adapter until several in a row survive a submit and a
// short wait, bounded by a time limit; and if Ogre picked a software adapter
// while the recorded hardware adapter is present again, the hardware adapter
// is substituted. The game thread blocks for that settle time, which it would
// otherwise spend crashing. Initial device creation is never delayed.
//
// The restored device then gets its vertex and index buffers back in place
// instead of through Ogre's mesh reload; see d3d11_buffer_restore.cpp.
//
// Config: [Graphics] D3D11DeviceLossRecovery (default 1);
// OPENSHIM_DISABLE_D3D11_DEVICE_LOSS_RECOVERY=1 turns it off.
//
// Test only (environment, never ini): OPENSHIM_TEST_D3D11_DEVICE_LOSS_AFTER_MS
// makes the first device report DXGI_ERROR_DEVICE_REMOVED that many ms after it
// is created, OPENSHIM_TEST_D3D11_DEVICE_LOSS_FILE makes the current device do
// so whenever that file exists (a loss at a chosen moment, e.g. mid-mission;
// the file is deleted as the loss fires, so each write is one loss), and
// OPENSHIM_TEST_D3D11_UNSTABLE_MS (default 4000) makes probes fail for that
// long afterwards, so the settle loop has a reset to wait out.
#include "bool_token.h"
#include "com_vtable_patch.h"
#include "d3d11_buffer_restore.h"
#include "d3d11_device_loss_recovery.h"
#include "diagnostic_switch.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <process.h>

#include <atomic>
#include <cstdlib>
#include <mutex>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "dx11-recovery";

        constexpr DWORD kSettleLimitMs = 15000;
        constexpr DWORD kProbeIntervalMs = 250;
        constexpr DWORD kProbeSurviveMs = 300;
        constexpr unsigned kStableProbesRequired = 3;
        constexpr unsigned kDiscoveryAttempts = 600;  // 600 x 100 ms
        constexpr DWORD kDiscoverySleepMs = 100;
        // ID3D11Device: IUnknown(3), then CreateBuffer .. GetCreationFlags
        // (35 methods), so GetFeatureLevel is 37 and GetDeviceRemovedReason
        // 39. Both are checked against a live device before the test hook is
        // installed.
        constexpr size_t kSlotGetFeatureLevel = 37;
        constexpr size_t kSlotGetDeviceRemovedReason = 39;

        using FnD3D11CreateDevice = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnCreateDXGIFactory1 = HRESULT(WINAPI*)(REFIID, void**);
        using FnGetDeviceRemovedReason = HRESULT(STDMETHODCALLTYPE*)(ID3D11Device*);
        using FnGetFeatureLevel = D3D_FEATURE_LEVEL(STDMETHODCALLTYPE*)(ID3D11Device*);

        FnD3D11CreateDevice g_RealCreateDevice = nullptr;   // through the renderer's IAT
        FnD3D11CreateDevice g_ExportCreateDevice = nullptr; // d3d11.dll export, for probes
        FnCreateDXGIFactory1 g_CreateFactory = nullptr;

        std::mutex g_Mutex;
        bool g_HaveBaseline = false;
        LUID g_BaselineLuid = {};
        UINT g_BaselineVendor = 0;
        UINT g_BaselineDeviceId = 0;
        unsigned g_Creations = 0;
        ID3D11Device* g_LastDevice = nullptr;  // AddRef'd; released at the next creation

        // Test injector state.
        DWORD g_TestLossAfterMs = 0;
        char g_TestLossFile[MAX_PATH] = {};
        DWORD g_TestUnstableMs = 4000;
        std::atomic<ID3D11Device*> g_TestDevice{nullptr};
        std::atomic<ID3D11Device*> g_TestLostDevice{nullptr};
        std::atomic<DWORD> g_TestDeviceCreatedAt{0};
        std::atomic<DWORD> g_TestLossFiredAt{0};
        FnGetDeviceRemovedReason g_RealGetDeviceRemovedReason = nullptr;

        uintptr_t g_DiscoveryThread = 0;

        DWORD ReadEnvMs(const char* name, DWORD fallback)
        {
            char value[32] = {};
            const DWORD n = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
            if (n == 0 || n >= sizeof(value))
                return fallback;
            char* end = nullptr;
            const unsigned long ms = std::strtoul(value, &end, 10);
            return (end && *end == '\0' && ms <= 600000) ? static_cast<DWORD>(ms) : fallback;
        }

        bool IsSoftwareAdapter(const DXGI_ADAPTER_DESC1& desc)
        {
            // The Basic Render Driver (WARP) is vendor 0x1414, device 0x8C.
            return (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) != 0 ||
                   (desc.VendorId == 0x1414 && desc.DeviceId == 0x8C);
        }

        bool DescribeAdapter(IDXGIAdapter* adapter, DXGI_ADAPTER_DESC1& desc)
        {
            if (!adapter)
                return false;
            IDXGIAdapter1* adapter1 = nullptr;
            if (FAILED(adapter->QueryInterface(__uuidof(IDXGIAdapter1), reinterpret_cast<void**>(&adapter1))))
                return false;
            const bool ok = SUCCEEDED(adapter1->GetDesc1(&desc));
            adapter1->Release();
            return ok;
        }

        bool DescribeDeviceAdapter(ID3D11Device* device, DXGI_ADAPTER_DESC1& desc)
        {
            IDXGIDevice* dxgiDevice = nullptr;
            if (FAILED(device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
                return false;
            IDXGIAdapter* adapter = nullptr;
            const bool ok = SUCCEEDED(dxgiDevice->GetAdapter(&adapter)) && DescribeAdapter(adapter, desc);
            if (adapter)
                adapter->Release();
            dxgiDevice->Release();
            return ok;
        }

        // The recorded hardware adapter from a fresh factory (LUID first, then
        // the same vendor/device in case the reset renumbered it), AddRef'd.
        IDXGIAdapter1* FindBaselineAdapter()
        {
            if (!g_CreateFactory)
                return nullptr;
            IDXGIFactory1* factory = nullptr;
            if (FAILED(g_CreateFactory(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&factory))))
                return nullptr;
            IDXGIAdapter1* byLuid = nullptr;
            IDXGIAdapter1* byId = nullptr;
            for (UINT i = 0;; ++i)
            {
                IDXGIAdapter1* adapter = nullptr;
                if (factory->EnumAdapters1(i, &adapter) == DXGI_ERROR_NOT_FOUND)
                    break;
                DXGI_ADAPTER_DESC1 desc = {};
                if (SUCCEEDED(adapter->GetDesc1(&desc)) && !IsSoftwareAdapter(desc))
                {
                    if (!byLuid && desc.AdapterLuid.LowPart == g_BaselineLuid.LowPart &&
                        desc.AdapterLuid.HighPart == g_BaselineLuid.HighPart)
                    {
                        byLuid = adapter;
                        continue;
                    }
                    if (!byId && desc.VendorId == g_BaselineVendor && desc.DeviceId == g_BaselineDeviceId)
                    {
                        byId = adapter;
                        continue;
                    }
                }
                adapter->Release();
            }
            factory->Release();
            if (byLuid)
            {
                if (byId)
                    byId->Release();
                return byLuid;
            }
            return byId;
        }

        bool InTestUnstableWindow()
        {
            const DWORD fired = g_TestLossFiredAt.load(std::memory_order_acquire);
            return fired && GetTickCount() - fired < g_TestUnstableMs;
        }

        // One probe: a device on the adapter, a submitted buffer, a short wait,
        // and the device must still be alive.
        bool ProbeSurvives(IDXGIAdapter* adapter)
        {
            if (InTestUnstableWindow())
                return false;
            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* context = nullptr;
            const HRESULT hr = g_ExportCreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0,
                                                    D3D11_SDK_VERSION, &device, nullptr, &context);
            if (FAILED(hr) || !device)
                return false;
            bool alive = false;
            D3D11_BUFFER_DESC bd = {};
            bd.ByteWidth = 256;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            ID3D11Buffer* buffer = nullptr;
            if (SUCCEEDED(device->CreateBuffer(&bd, nullptr, &buffer)))
            {
                context->Flush();
                Sleep(kProbeSurviveMs);
                alive = device->GetDeviceRemovedReason() == S_OK;
                buffer->Release();
            }
            context->Release();
            device->Release();
            return alive;
        }

        // Blocks until the recorded hardware adapter has produced
        // kStableProbesRequired surviving probes in a row, or the limit runs
        // out. Returns that adapter (AddRef'd) when it settled.
        IDXGIAdapter1* SettleHardwareAdapter(DWORD& waitedMs, unsigned& probes)
        {
            const DWORD start = GetTickCount();
            unsigned stable = 0;
            probes = 0;
            IDXGIAdapter1* settled = nullptr;
            while (GetTickCount() - start < kSettleLimitMs)
            {
                IDXGIAdapter1* adapter = FindBaselineAdapter();
                if (adapter)
                {
                    ++probes;
                    if (ProbeSurvives(adapter))
                    {
                        if (++stable >= kStableProbesRequired)
                        {
                            settled = adapter;
                            break;
                        }
                    }
                    else
                    {
                        stable = 0;
                    }
                    adapter->Release();
                }
                else
                {
                    stable = 0;
                }
                Sleep(kProbeIntervalMs);
            }
            waitedMs = GetTickCount() - start;
            return settled;
        }

        HRESULT STDMETHODCALLTYPE TestGetDeviceRemovedReason(ID3D11Device* self)
        {
            if (self == g_TestDevice.load(std::memory_order_acquire))
            {
                const DWORD created = g_TestDeviceCreatedAt.load(std::memory_order_acquire);
                const bool due = g_TestLostDevice.load(std::memory_order_acquire) == self ||
                                 (g_TestLossAfterMs && !g_TestLossFiredAt.load(std::memory_order_acquire) &&
                                  GetTickCount() - created >= g_TestLossAfterMs) ||
                                 (g_TestLossFile[0] && GetFileAttributesA(g_TestLossFile) != INVALID_FILE_ATTRIBUTES);
                if (due)
                {
                    if (g_TestLostDevice.exchange(self) != self)
                    {
                        g_TestLossFiredAt.store(GetTickCount(), std::memory_order_release);
                        // The file is consumed, so writing it again later
                        // removes the device that replaced this one.
                        if (g_TestLossFile[0])
                            DeleteFileA(g_TestLossFile);
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[DX11 Recovery] TEST: device 0x%p now reports DXGI_ERROR_DEVICE_REMOVED; probes fail for %lu ms",
                                 self, g_TestUnstableMs);
                    }
                    return DXGI_ERROR_DEVICE_REMOVED;
                }
            }
            return g_RealGetDeviceRemovedReason(self);
        }

        void ArmTestInjector(ID3D11Device* device, D3D_FEATURE_LEVEL createdLevel)
        {
            void** vtable = *reinterpret_cast<void***>(device);
            const auto getLevel = reinterpret_cast<FnGetFeatureLevel>(vtable[kSlotGetFeatureLevel]);
            const auto getReason = reinterpret_cast<FnGetDeviceRemovedReason>(vtable[kSlotGetDeviceRemovedReason]);
            if (getLevel(device) != createdLevel || getReason(device) != S_OK)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Recovery] TEST: ID3D11Device slot check failed; injector not armed");
                return;
            }
            // Devices share one vtable: patch it once, so the saved original
            // can never become the hook itself.
            const auto result = g_RealGetDeviceRemovedReason
                ? ComVtablePatch::Result::AlreadyHooked
                : ComVtablePatch::PatchEntry(device, kSlotGetDeviceRemovedReason, &TestGetDeviceRemovedReason,
                                             g_RealGetDeviceRemovedReason, ComVtablePatch::OnForeignWrapper::Refuse);
            if (!ComVtablePatch::Succeeded(result))
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 Recovery] TEST: could not hook GetDeviceRemovedReason");
                return;
            }
            // The clock starts at the first device; later start-up devices
            // (the one Ogre keeps is the last) inherit it.
            DWORD unset = 0;
            g_TestDeviceCreatedAt.compare_exchange_strong(unset, GetTickCount());
            g_TestDevice.store(device, std::memory_order_release);
            LogShimA(LogLevel::Warn, kComponent,
                     "[DX11 Recovery] TEST: device 0x%p will report removal after %lu ms%s%s", device, g_TestLossAfterMs,
                     g_TestLossFile[0] ? " or once this file exists: " : "", g_TestLossFile);
        }

        HRESULT WINAPI HookD3D11CreateDevice(
            IDXGIAdapter* adapter, D3D_DRIVER_TYPE driverType, HMODULE software, UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels, UINT featureLevelCount, UINT sdkVersion,
            ID3D11Device** device, D3D_FEATURE_LEVEL* featureLevel, ID3D11DeviceContext** immediateContext)
        {
            // Ogre creates several devices during a normal start, so a later
            // creation is a recovery only when the device it replaces reports
            // itself removed. The hook holds a reference to the last device it
            // returned for exactly this check.
            ID3D11Device* previous = nullptr;
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                ++g_Creations;
                previous = g_LastDevice;
                g_LastDevice = nullptr;
            }
            bool recovery = false;
            if (previous)
            {
                recovery = g_HaveBaseline && previous->GetDeviceRemovedReason() != S_OK;
                previous->Release();
            }

            IDXGIAdapter1* substitute = nullptr;
            if (recovery)
            {
                // The device being replaced is gone; stop the test reporting
                // removal for an address the allocator may hand out again.
                g_TestDevice.store(nullptr, std::memory_order_release);
                g_TestLostDevice.store(nullptr, std::memory_order_release);

                DXGI_ADAPTER_DESC1 requested = {};
                const bool requestedKnown = DescribeAdapter(adapter, requested);
                const bool requestedSoftware = (requestedKnown && IsSoftwareAdapter(requested)) ||
                                               driverType == D3D_DRIVER_TYPE_WARP ||
                                               driverType == D3D_DRIVER_TYPE_REFERENCE;
                DWORD waited = 0;
                unsigned probes = 0;
                IDXGIAdapter1* settled = SettleHardwareAdapter(waited, probes);
                if (settled)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "[DX11 Recovery] device recreation #%u: hardware adapter settled after %lu ms (%u probes)%s",
                             g_Creations, waited, probes,
                             requestedSoftware ? "; replacing the software adapter Ogre selected" : "");
                    if (requestedSoftware)
                        substitute = settled;
                    else
                        settled->Release();
                }
                else
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Recovery] device recreation #%u: hardware adapter did not settle within %lu ms (%u probes); forwarding Ogre's request unchanged",
                             g_Creations, waited, probes);
                }
            }

            const HRESULT hr = substitute
                ? g_RealCreateDevice(substitute, D3D_DRIVER_TYPE_UNKNOWN, nullptr, flags, featureLevels,
                                     featureLevelCount, sdkVersion, device, featureLevel, immediateContext)
                : g_RealCreateDevice(adapter, driverType, software, flags, featureLevels, featureLevelCount,
                                     sdkVersion, device, featureLevel, immediateContext);
            if (substitute)
                substitute->Release();

            if (SUCCEEDED(hr) && device && *device)
            {
                DXGI_ADAPTER_DESC1 desc = {};
                if (DescribeDeviceAdapter(*device, desc))
                {
                    std::lock_guard<std::mutex> lock(g_Mutex);
                    if (!g_HaveBaseline && !IsSoftwareAdapter(desc))
                    {
                        g_HaveBaseline = true;
                        g_BaselineLuid = desc.AdapterLuid;
                        g_BaselineVendor = desc.VendorId;
                        g_BaselineDeviceId = desc.DeviceId;
                        LogShimA(LogLevel::Info, kComponent,
                                 "[DX11 Recovery] recorded hardware adapter %04X:%04X for device-loss recovery",
                                 desc.VendorId, desc.DeviceId);
                    }
                }
                (*device)->AddRef();
                {
                    std::lock_guard<std::mutex> lock(g_Mutex);
                    g_LastDevice = *device;
                }
                // The timer removes the first device once; the file can remove
                // each device in turn, recovered ones included.
                if ((!recovery && g_TestLossAfterMs) || g_TestLossFile[0])
                    ArmTestInjector(*device, (*device)->GetFeatureLevel());
            }
            else if (recovery)
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 Recovery] device recreation #%u failed hr=0x%08lX",
                         g_Creations, static_cast<unsigned long>(hr));
            }
            return hr;
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            for (unsigned attempt = 0; attempt < kDiscoveryAttempts; ++attempt)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (renderer)
                {
                    IatPatch::WaitForModuleLoadToFinish(renderer, nullptr);
                    HMODULE d3d11 = GetModuleHandleW(L"d3d11.dll");
                    HMODULE dxgi = LoadLibraryW(L"dxgi.dll");
                    g_ExportCreateDevice = d3d11
                        ? reinterpret_cast<FnD3D11CreateDevice>(GetProcAddress(d3d11, "D3D11CreateDevice"))
                        : nullptr;
                    g_CreateFactory = dxgi
                        ? reinterpret_cast<FnCreateDXGIFactory1>(GetProcAddress(dxgi, "CreateDXGIFactory1"))
                        : nullptr;
                    if (!g_ExportCreateDevice || !g_CreateFactory)
                    {
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[DX11 Recovery] d3d11/dxgi entry points unavailable; recovery not installed");
                        return 0;
                    }
                    // Before the first device, so every buffer is seen from its
                    // constructor on (d3d11_buffer_restore.cpp).
                    InstallD3D11BufferRestore(renderer);
                    for (unsigned retry = 0; retry < 20; ++retry)
                    {
                        const auto result = IatPatch::PatchImport(
                            renderer, "d3d11.dll", "D3D11CreateDevice",
                            reinterpret_cast<void*>(&HookD3D11CreateDevice),
                            reinterpret_cast<void**>(&g_RealCreateDevice));
                        if (result == IatPatch::Result::Patched)
                        {
                            LogShimA(LogLevel::Info, kComponent,
                                     "[DX11 Recovery] installed: device recreation waits for the hardware adapter to settle (limit %lu ms)%s",
                                     kSettleLimitMs, (g_TestLossAfterMs || g_TestLossFile[0]) ? "; TEST injector enabled" : "");
                            return 0;
                        }
                        if (result == IatPatch::Result::NotFound)
                            break;
                        Sleep(50);
                    }
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Recovery] could not patch the renderer's D3D11CreateDevice import; recovery not installed");
                    return 0;
                }
                Sleep(kDiscoverySleepMs);
            }
            return 0;  // DX9, or the renderer never loaded: nothing to do.
        }
    }

    void InitializeD3D11DeviceLossRecovery()
    {
        if (g_DiscoveryThread)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_D3D11_DEVICE_LOSS_RECOVERY", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;
        const std::string ini = DiagnosticSwitch::OpenShimIniPath();
        if (GetPrivateProfileIntA("Graphics", "D3D11DeviceLossRecovery", 1, ini.c_str()) == 0)
            return;

        g_TestLossAfterMs = ReadEnvMs("OPENSHIM_TEST_D3D11_DEVICE_LOSS_AFTER_MS", 0);
        const DWORD fileLen = GetEnvironmentVariableA("OPENSHIM_TEST_D3D11_DEVICE_LOSS_FILE", g_TestLossFile,
                                                      static_cast<DWORD>(sizeof(g_TestLossFile)));
        if (fileLen == 0 || fileLen >= sizeof(g_TestLossFile))
            g_TestLossFile[0] = '\0';
        g_TestUnstableMs = ReadEnvMs("OPENSHIM_TEST_D3D11_UNSTABLE_MS", 4000);
        g_DiscoveryThread = _beginthreadex(nullptr, 0, DiscoveryThreadProc, nullptr, 0, nullptr);
    }
}
