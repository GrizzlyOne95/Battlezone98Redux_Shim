// fog_wake_shader.cpp
// BZR Open Shim - interactive fog wakes, in-shader ground fog (spike).
//
// Off unless [Experimental] InteractiveFogWakes is on. DX11 Enhanced only:
// the two Enhanced SM4 fragment shaders (terrain and base) declare
//   Texture2D oseFogWakeParams : register(t32)   5x1 RGBA32F, per frame
//   Texture2D oseFogWakeBank   : register(t33)   R16G16 UNORM, R = clearance,
//                                                G = terrain height (normalised)
// and integrate a thin ground mist along the camera-to-pixel ray. Ogre binds
// pixel shader resources only from slot 0 up to the pass's texture count, so
// slots 32/33 are never touched by it: binding them here once per camera,
// during the render-queue fill and before that camera's draws, reaches every
// Enhanced terrain and object material without any material or .program change.
// An unbound slot reads zero, and texel 0 carries a magic value the shader
// checks, so the effect is off unless this file bound valid data.
//
// Fails closed: any other render system, a missing export, or a failed
// resource creation stands the effect down for the session.
//
// See Docs/INTERACTIVE_FOG_WAKES.md, "In-shader spike".

#include "fog_wake_feature.h"

#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>
#include <d3d11.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "fogwake";

        // Must match OSE_FOG_WAKE_MAGIC in the Enhanced SM4 shaders.
        constexpr float kParamsMagic = 4096.25f;
        constexpr UINT kParamsSlot = 32;    // t32, t33 follows.
        constexpr float kMistTopMetres = 6.0f;

        using FnRootSingleton = void*(__cdecl*)();
        using FnRootRenderSystem = void*(__thiscall*)(void* root);
        using FnRenderSystemGetDevice = void*(__thiscall*)(void* renderSystem);
        using FnDeviceGetImmediateContext = ID3D11DeviceContext*(__thiscall*)(void* device);
        using FnHeightAt = double(__cdecl*)(double x, double z);
        using FnCurrentViewport = void*(__thiscall*)(const void* sceneManager);
        using FnViewportCamera = void*(__thiscall*)(const void* viewport);

        struct Tuning
        {
            float density = 0.045f;     // Extinction per metre at the ground.
            float scaleHeight = 1.4f;   // Metres for density to fall to 1/e.
            float edgeFade = 64.0f;     // Metres inside the bank edge.
            float nearFade = 4.0f;      // Metres from the camera.
            float farDistance = 220.0f; // Metres; mist fades out towards here.
            float litMix = 0.7f;        // Lit grey over the atmosphere colour (dark-sky maps).
            bool debug = false;         // Paint the mist magenta (binding check).
        };

        struct Gpu
        {
            ID3D11DeviceContext* context = nullptr; // AddRef'd while held, so the
                                                    // address cannot be reused.
            ID3D11Texture2D* paramsTex = nullptr;
            ID3D11ShaderResourceView* paramsSrv = nullptr;
            ID3D11Texture2D* bankTex = nullptr;
            ID3D11ShaderResourceView* bankSrv = nullptr;
            unsigned bankWidth = 0;
            unsigned bankHeight = 0;
            unsigned bakedGeneration = 0;
            unsigned long long uploadedSteps = ~0ull;
            bool bound = false;
        };

        Gpu g_Gpu;
        bool g_Failed = false;
        bool g_LoggedActive = false;
        bool g_TuningLoaded = false;
        Tuning g_Tuning;
        std::vector<uint32_t> g_Staging; // R16G16 texels.
        float g_HeightMin = 0;
        float g_HeightRange = 1;

        FnRootSingleton g_GetRoot = nullptr;
        FnRootRenderSystem g_GetRenderSystem = nullptr;
        FnRenderSystemGetDevice g_GetDevice = nullptr;
        FnDeviceGetImmediateContext g_GetContext = nullptr;
        FnHeightAt g_HeightAt = nullptr;
        FnCurrentViewport g_CurrentViewport = nullptr;
        FnViewportCamera g_ViewportCamera = nullptr;

        float EnvFloat(const char* name, float fallback, float lo, float hi)
        {
            char buffer[64] = {};
            const DWORD length = GetEnvironmentVariableA(name, buffer, sizeof(buffer));
            if (length == 0 || length >= sizeof(buffer))
                return fallback;
            char* end = nullptr;
            const double value = std::strtod(buffer, &end);
            if (end == buffer || !std::isfinite(value) || value < lo || value > hi)
                return fallback;
            return static_cast<float>(value);
        }

        void LoadTuning()
        {
            if (g_TuningLoaded)
                return;
            g_TuningLoaded = true;
            g_Tuning.density = EnvFloat("OPENSHIM_FOGWAKE_DENSITY", g_Tuning.density, 0.0f, 1.0f);
            g_Tuning.scaleHeight = EnvFloat("OPENSHIM_FOGWAKE_SCALE_HEIGHT", g_Tuning.scaleHeight, 0.2f, 20.0f);
            g_Tuning.farDistance = EnvFloat("OPENSHIM_FOGWAKE_FAR", g_Tuning.farDistance, 20.0f, 2000.0f);
            g_Tuning.litMix = EnvFloat("OPENSHIM_FOGWAKE_LIT_MIX", g_Tuning.litMix, 0.0f, 1.0f);
            g_Tuning.debug = EnvFloat("OPENSHIM_FOGWAKE_DEBUG", 0.0f, 0.0f, 1.0f) > 0.5f;
            LogShimA(LogLevel::Info, kComponent,
                     "[FOGWAKE] shader tuning density=%.4f/m scaleHeight=%.2fm top=%.1fm far=%.0fm litMix=%.2f debug=%d",
                     g_Tuning.density, g_Tuning.scaleHeight, kMistTopMetres, g_Tuning.farDistance,
                     g_Tuning.litMix, g_Tuning.debug ? 1 : 0);
        }

        void Unbind();

        void StandDown(const char* why)
        {
            Unbind();
            g_Failed = true;
            LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] in-shader fog stands down: %s", why);
        }

        template <typename T> void SafeRelease(T*& p)
        {
            if (p)
            {
                p->Release();
                p = nullptr;
            }
        }

        // unbind=false when the context may already be released (device reset).
        void ReleaseGpu(bool unbind)
        {
            if (unbind && g_Gpu.bound && g_Gpu.context)
            {
                ID3D11ShaderResourceView* nulls[2] = {};
                g_Gpu.context->PSSetShaderResources(kParamsSlot, 2, nulls);
            }
            SafeRelease(g_Gpu.bankSrv);
            SafeRelease(g_Gpu.bankTex);
            SafeRelease(g_Gpu.paramsSrv);
            SafeRelease(g_Gpu.paramsTex);
            SafeRelease(g_Gpu.context);
            g_Gpu = Gpu{};
        }

        bool ResolveExports()
        {
            if (g_GetRoot && g_GetRenderSystem && g_GetDevice && g_GetContext && g_HeightAt &&
                g_CurrentViewport && g_ViewportCamera)
                return true;
            HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
            HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
            if (!ogre || !renderer)
                return false;
            g_GetRoot = reinterpret_cast<FnRootSingleton>(
                GetProcAddress(ogre, "?getSingletonPtr@Root@Ogre@@SAPAV12@XZ"));
            g_GetRenderSystem = reinterpret_cast<FnRootRenderSystem>(
                GetProcAddress(ogre, "?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ"));
            g_GetDevice = reinterpret_cast<FnRenderSystemGetDevice>(
                GetProcAddress(renderer, "?_getDevice@D3D11RenderSystem@Ogre@@QAEAAVD3D11Device@2@XZ"));
            g_GetContext = reinterpret_cast<FnDeviceGetImmediateContext>(
                GetProcAddress(renderer, "?GetImmediateContext@D3D11Device@Ogre@@QAEPAUID3D11DeviceContext@@XZ"));
            g_CurrentViewport = reinterpret_cast<FnCurrentViewport>(
                GetProcAddress(ogre, "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ"));
            g_ViewportCamera = reinterpret_cast<FnViewportCamera>(
                GetProcAddress(ogre, "?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ"));
            g_HeightAt = reinterpret_cast<FnHeightAt>(
                static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("Terrain::HeightAt")));
            return g_GetRoot && g_GetRenderSystem && g_GetDevice && g_GetContext && g_HeightAt &&
                   g_CurrentViewport && g_ViewportCamera;
        }

        // The params carry the main view camera's position, so only the main
        // camera may draw with them bound: another camera (render-to-texture,
        // a second viewport) gets the slots cleared for its draws.
        bool FillingMainCameraSeh()
        {
            __try
            {
                void* sceneManager = Hooks::GetOgreSceneManagerRuntime();
                void* viewport = sceneManager ? g_CurrentViewport(sceneManager) : nullptr;
                void* camera = viewport ? g_ViewportCamera(viewport) : nullptr;
                return camera && camera == Hooks::GetMainViewCameraObject();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        ID3D11DeviceContext* QueryContextSeh()
        {
            __try
            {
                void* root = g_GetRoot();
                void* renderSystem = root ? g_GetRenderSystem(root) : nullptr;
                void* device = renderSystem ? g_GetDevice(renderSystem) : nullptr;
                return device ? g_GetContext(device) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool CreateGpu(ID3D11DeviceContext* context, unsigned width, unsigned height)
        {
            ID3D11Device* device = nullptr;
            context->GetDevice(&device);
            if (!device)
                return false;

            bool ok = true;
            D3D11_TEXTURE2D_DESC params = {};
            params.Width = 5;
            params.Height = 1;
            params.MipLevels = 1;
            params.ArraySize = 1;
            params.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            params.SampleDesc.Count = 1;
            params.Usage = D3D11_USAGE_DYNAMIC;
            params.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            params.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            ok = ok && SUCCEEDED(device->CreateTexture2D(&params, nullptr, &g_Gpu.paramsTex));
            ok = ok && SUCCEEDED(device->CreateShaderResourceView(g_Gpu.paramsTex, nullptr, &g_Gpu.paramsSrv));

            D3D11_TEXTURE2D_DESC bank = {};
            bank.Width = width;
            bank.Height = height;
            bank.MipLevels = 1;
            bank.ArraySize = 1;
            bank.Format = DXGI_FORMAT_R16G16_UNORM;
            bank.SampleDesc.Count = 1;
            bank.Usage = D3D11_USAGE_DEFAULT;
            bank.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            ok = ok && SUCCEEDED(device->CreateTexture2D(&bank, nullptr, &g_Gpu.bankTex));
            ok = ok && SUCCEEDED(device->CreateShaderResourceView(g_Gpu.bankTex, nullptr, &g_Gpu.bankSrv));
            device->Release();

            context->AddRef();
            g_Gpu.context = context;
            g_Gpu.bankWidth = width;
            g_Gpu.bankHeight = height;
            if (!ok)
                ReleaseGpu(false);
            return ok;
        }

        // Samples Terrain::HeightAt once per cell centre of a new bank. The
        // heights only feed the G channel; clearance is merged at upload.
        bool BakeHeightsSeh(const FogWakeRenderView& view, std::vector<float>& heights)
        {
            __try
            {
                for (unsigned z = 0; z < view.height; ++z)
                {
                    const double wz = view.originZ + (z + 0.5) * view.cellSize;
                    for (unsigned x = 0; x < view.width; ++x)
                    {
                        const double wx = view.originX + (x + 0.5) * view.cellSize;
                        heights[static_cast<size_t>(z) * view.width + x] = static_cast<float>(g_HeightAt(wx, wz));
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return true;
        }

        bool BakeBank(const FogWakeRenderView& view)
        {
            const size_t count = static_cast<size_t>(view.width) * view.height;
            std::vector<float> heights(count, 0.0f);
            if (!BakeHeightsSeh(view, heights))
                return false;
            // Off-map cells (the bank is centred on the player, so it can
            // overhang the terrain) take the lowest valid height instead of
            // failing the whole bank.
            float lo = 1.0e9f;
            float hi = -1.0e9f;
            size_t bad = 0;
            for (float h : heights)
            {
                if (!std::isfinite(h) || std::fabs(h) > 1.0e5f)
                {
                    ++bad;
                    continue;
                }
                lo = (std::min)(lo, h);
                hi = (std::max)(hi, h);
            }
            if (bad == count)
                return false;
            for (float& h : heights)
            {
                if (!std::isfinite(h) || std::fabs(h) > 1.0e5f)
                    h = lo;
            }
            g_HeightMin = lo;
            g_HeightRange = (std::max)(hi - lo, 1.0f);
            g_Staging.assign(count, 0u);
            for (size_t i = 0; i < count; ++i)
            {
                const float g = (heights[i] - g_HeightMin) / g_HeightRange;
                const uint32_t g16 = static_cast<uint32_t>(std::lround(std::fmin(std::fmax(g, 0.0f), 1.0f) * 65535.0f));
                g_Staging[i] = g16 << 16;
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[FOGWAKE] shader bank baked gen=%u cells=%ux%u heightMin=%.1f range=%.1f badCells=%u",
                     view.bankGeneration, view.width, view.height, g_HeightMin, g_HeightRange,
                     static_cast<unsigned>(bad));
            return true;
        }

        void UploadClearance(const FogWakeRenderView& view)
        {
            const size_t count = static_cast<size_t>(view.width) * view.height;
            for (size_t i = 0; i < count; ++i)
            {
                const float c = std::fmin(std::fmax(view.clearance[i], 0.0f), 1.0f);
                const uint32_t r16 = static_cast<uint32_t>(c * 65535.0f + 0.5f);
                g_Staging[i] = (g_Staging[i] & 0xFFFF0000u) | r16;
            }
            g_Gpu.context->UpdateSubresource(g_Gpu.bankTex, 0, nullptr, g_Staging.data(),
                                             view.width * sizeof(uint32_t), 0);
            g_Gpu.uploadedSteps = view.steps;
        }

        bool ReadRenderOrigin(float (&out)[3])
        {
            const uintptr_t addr = Hooks::WorldRenderOriginAddr();
            if (!addr)
                return false;
            __try
            {
                const float* origin = reinterpret_cast<const float*>(addr);
                out[0] = origin[0];
                out[1] = origin[1];
                out[2] = origin[2];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return std::isfinite(out[0]) && std::isfinite(out[1]) && std::isfinite(out[2]);
        }

        // Render space is (simX - ox, simY - oy, -simZ - oz); see the old
        // render spike notes in Docs/INTERACTIVE_FOG_WAKES.md.
        bool CameraSimPosition(float (&sim)[3])
        {
            float render[3] = {};
            float fovY = 0;
            float origin[3] = {};
            if (!Hooks::TryGetMainViewCamera(render, &fovY) || !ReadRenderOrigin(origin))
                return false;
            sim[0] = render[0] + origin[0];
            sim[1] = render[1] + origin[1];
            sim[2] = -(render[2] + origin[2]);
            return std::isfinite(sim[0]) && std::isfinite(sim[1]) && std::isfinite(sim[2]);
        }

        bool UploadParams(const FogWakeRenderView& view, const float (&camSim)[3])
        {
            const float sizeX = static_cast<float>(view.width * view.cellSize);
            const float sizeZ = static_cast<float>(view.height * view.cellSize);
            const double now = std::chrono::duration<double>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            const float time = static_cast<float>(std::fmod(now, 4096.0));
            const float texels[20] = {
                kParamsMagic, g_Tuning.density, time, kMistTopMetres,
                static_cast<float>(camSim[0] - view.originX), camSim[1] - g_HeightMin,
                static_cast<float>(camSim[2] - view.originZ), g_Tuning.scaleHeight,
                sizeX, sizeZ, g_HeightRange, g_Tuning.edgeFade,
                static_cast<float>(view.width), static_cast<float>(view.height),
                g_Tuning.nearFade, g_Tuning.farDistance,
                g_Tuning.debug ? 1.0f : 0.0f, g_Tuning.litMix, 0.0f, 0.0f,
            };
            D3D11_MAPPED_SUBRESOURCE mapped = {};
            if (FAILED(g_Gpu.context->Map(g_Gpu.paramsTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)) || !mapped.pData)
                return false;
            std::memcpy(mapped.pData, texels, sizeof(texels));
            g_Gpu.context->Unmap(g_Gpu.paramsTex, 0);
            return true;
        }

        // The bank latches to the first engine-flame emitter. A scene with no
        // thrusting craft would never get one, so fall back to the player.
        void* ReadUserObject(uintptr_t slot)
        {
            __try
            {
                return *reinterpret_cast<void* const*>(slot);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // Change-only decision log for the player fallback.
        void NotePlayerFallback(const char* outcome)
        {
            static const char* s_last = nullptr;
            if (s_last == outcome)
                return;
            s_last = outcome;
            LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] player-fallback placement: %s", outcome);
        }

        void PlaceBankAroundPlayer()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            if (!slot)
                return NotePlayerFallback("no user slot");
            void* user = ReadUserObject(slot);
            if (!user)
                return NotePlayerFallback("no user object");
            float position[3] = {};
            if (!Hooks::TryGetGameObjectWorldPosition(user, position))
                return NotePlayerFallback("user position unreadable");
            // A player not yet positioned reads (0, 0); the bank never moves
            // once placed, so wait for a real position.
            if (std::fabs(position[0]) <= 1.0f && std::fabs(position[2]) <= 1.0f)
                return NotePlayerFallback("user at origin; waiting");
            NotePlayerFallback(FogWakePlaceBankIfAbsent(position[0], position[2])
                                   ? "placed around player"
                                   : "declined (stopped since start, or place failed)");
        }

        void Unbind()
        {
            if (!g_Gpu.bound || !g_Gpu.context)
                return;
            ID3D11ShaderResourceView* nulls[2] = {};
            g_Gpu.context->PSSetShaderResources(kParamsSlot, 2, nulls);
            g_Gpu.bound = false;
        }
    }

    void FogWakeShaderFrameTick(bool active)
    {
        if (g_Failed)
            return;
        if (!active)
        {
            Unbind();
            PlaceBankAroundPlayer();
            return;
        }

        FogWakeRenderView view;
        if (!FogWakeGetRenderView(view))
        {
            Unbind();
            return;
        }

        if (RenderProfiles::IdentifyActiveRenderSystem() != 1)
        {
            StandDown("active render system is not Direct3D11");
            return;
        }
        if (!ResolveExports())
        {
            StandDown("renderer exports or Terrain::HeightAt unresolved");
            return;
        }
        LoadTuning();
        if (!FillingMainCameraSeh())
        {
            static bool s_Logged = false;
            if (!s_Logged)
            {
                s_Logged = true;
                LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] in-shader fog skipped for a non-main camera");
            }
            Unbind();
            return;
        }

        // Re-query every frame: a device reset hands back a new context.
        ID3D11DeviceContext* context = QueryContextSeh();
        if (!context)
        {
            Unbind();
            return;
        }
        if (g_Gpu.context != context || g_Gpu.bankWidth != view.width || g_Gpu.bankHeight != view.height)
        {
            if (g_Gpu.context)
                LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] shader resources recreated (context or bank changed)");
            // Clear t32/t33 on the context we are about to use, so no view of
            // the released textures stays bound there.
            ID3D11ShaderResourceView* nulls[2] = {};
            context->PSSetShaderResources(kParamsSlot, 2, nulls);
            ReleaseGpu(g_Gpu.context == context);
            if (!CreateGpu(context, view.width, view.height))
            {
                StandDown("texture creation failed");
                return;
            }
        }
        if (g_Gpu.bakedGeneration != view.bankGeneration)
        {
            if (!BakeBank(view))
            {
                StandDown("terrain height bake failed");
                return;
            }
            g_Gpu.bakedGeneration = view.bankGeneration;
            g_Gpu.uploadedSteps = ~0ull;
        }
        if (g_Gpu.uploadedSteps != view.steps)
            UploadClearance(view);

        float camSim[3] = {};
        if (!CameraSimPosition(camSim) || !UploadParams(view, camSim))
        {
            Unbind();
            return;
        }

        ID3D11ShaderResourceView* views[2] = { g_Gpu.paramsSrv, g_Gpu.bankSrv };
        g_Gpu.context->PSSetShaderResources(kParamsSlot, 2, views);
        g_Gpu.bound = true;
        if (!g_LoggedActive)
        {
            g_LoggedActive = true;
            LogShimA(LogLevel::Info, kComponent,
                     "[FOGWAKE] in-shader fog bound t32/t33 camSim=(%.1f, %.1f, %.1f) bankOrigin=(%.1f, %.1f)",
                     camSim[0], camSim[1], camSim[2], view.originX, view.originZ);
        }
    }
}
