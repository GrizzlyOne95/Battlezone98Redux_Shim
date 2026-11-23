// fog_wake_render.cpp
// BZR Open Shim - InteractiveFogWakes render spike. Draws the CPU clearance
// field (fog_wake_feature.cpp) as stacked translucent ground-fog layers so
// the look and the frame cost can be judged. Hard-coded colour, density and
// heights; no Lua API, no wind, no new config. Behind the existing
// [Experimental] InteractiveFogWakes toggle, DX11 only, failing closed.
//
// Layers: one ManualObject on a child of the root scene node, one section
// per layer. Each layer is a terrain-following grid over the whole bank
// (kGridVerts per side at kGridStep m, from Terrain::HeightAt) lifted
// kLayerHeights[i] above the ground. The node sits at the bank centre in
// render space and follows the render origin; vertices are node-local.
// Built once per bank (FogWakeRenderView::bankGeneration), never per frame.
// Sections are emitted lowest, second, top, third: transparent sort sees one
// depth for all of them (one node), so emission order is the draw order, and
// this order is back to front for a camera between layers 2 and 3 looking
// down or up.
//
// Clearance: an Ogre manual 2D texture (PF_L8, static usage) created once per
// process in the chunk payload group and kept (one deliberate SharedPtr ref).
// After each simulation tick its D3D11 texture is refreshed with
// UpdateSubresource (64 KB). The material samples it by name.
//
// Driver: TickFogWakeRender from ChunkEffect::Simulate on the game thread
// (bzr_hooks.cpp), after TickRtsMarkers; never inside render-queue traversal.
// Teardown: lifecycle_seams.cpp (destroyAllEntities destroys; clearScene and
// destroyAllMovableObjects forget).
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "fog_wake_feature.h"
#include "fog_wake_render_assets.h"
#include "hook_engine.h"
#include "render_profile_runtime.h"
#include "scene_mutation_drain.h"
#include "shim_log.h"

#include <Windows.h>
#include <d3d11.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error FogWake render reads the GOG x86 engine layout
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace FR = FogWakeRender;

            constexpr const char* kComponent = "fogwake";

            // Layer heights above the terrain, emitted in this order (see top).
            constexpr float kLayerHeights[] = {0.5f, 1.5f, 4.5f, 3.0f};
            constexpr float kLayerFractions[] = {0.0f, 1.0f / 3.0f, 1.0f, 2.0f / 3.0f};
            constexpr unsigned kLayerCount = 4;
            // 4 m vertex spacing: the offline estimate on lcbench put the p99
            // interpolation error at ~0 m (8 m: 4.5 m, clipping the hills).
            constexpr float kGridStep = 4.0f;
            constexpr unsigned kMaxGridVerts = 129; // 512 m / 4 m + 1
            constexpr int kOgreTriangleList = 4;    // RenderOperation::OT_TRIANGLE_LIST
            constexpr int kOgreTextureType2D = 2;
            constexpr int kOgrePixelFormatL8 = 1;
            constexpr int kOgreTextureUsageStaticWriteOnly = 5;

            struct OgreSharedPtr
            {
                void* rep = nullptr;
                void* info = nullptr;
            };
            static_assert(sizeof(OgreSharedPtr) == 8, "Redux Ogre SharedPtr ABI changed");

            using FnHeightAt = double(__cdecl*)(double, double);
            using FnManualColour = void(__thiscall*)(void*, float, float, float, float);
            using FnSetCastShadows = void(__thiscall*)(void*, bool);
            using FnDestroyManualObject = void(__thiscall*)(void*, void*);
            using FnDestroySceneNode = void(__thiscall*)(void*, void*);
            using FnGetTextureManager = void*(__cdecl*)();
            using FnCreateManualTexture = OgreSharedPtr*(__thiscall*)(
                void*, OgreSharedPtr*, const std::string&, const std::string&, int, uint32_t, uint32_t, uint32_t,
                int, int, int, void*, bool, uint32_t, const std::string&);
            using FnGetD3D11Texture2D = ID3D11Texture2D*(__thiscall*)(void*);

            struct OgreApi
            {
                bool attempted = false;
                bool usable = false;
                FnOgreCreateManualObject createManualObject = nullptr;
                FnOgreGetRootSceneNode getRootSceneNode = nullptr;
                FnOgreCreateChildSceneNode createChildSceneNode = nullptr;
                FnOgreAttachObject attachObject = nullptr;
                FnOgreManualObjectEstimateCount estimateVertices = nullptr;
                FnOgreManualObjectEstimateCount estimateIndices = nullptr;
                FnOgreManualObjectBegin begin = nullptr;
                FnOgreManualObjectVertex3 position = nullptr;
                FnOgreManualObjectTexture2 textureCoord = nullptr;
                FnManualColour colour = nullptr;
                FnOgreManualObjectIndex index = nullptr;
                FnOgreManualObjectEnd end = nullptr;
                FnOgreSetVisible setVisible = nullptr;
                FnOgreSetNodePosition setNodePosition = nullptr;
                FnSetCastShadows setCastShadows = nullptr;
                FnDestroyManualObject destroyManualObject = nullptr;
                FnDestroySceneNode destroySceneNode = nullptr;
                FnGetTextureManager getTextureManager = nullptr;
                FnCreateManualTexture createManualTexture = nullptr;
                FnHeightAt heightAt = nullptr;
            };
            OgreApi g_Api;

            const OgreApi& GetApi()
            {
                OgreApi& api = g_Api;
                if (api.attempted)
                    return api;
                api.attempted = true;
                api.createManualObject = ResolveOgreProc<FnOgreCreateManualObject>(
                    "?createManualObject@SceneManager@Ogre@@UAEPAVManualObject@2@XZ");
                api.getRootSceneNode =
                    ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
                api.createChildSceneNode = ResolveOgreProc<FnOgreCreateChildSceneNode>(
                    "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
                api.attachObject =
                    ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
                api.estimateVertices =
                    ResolveOgreProc<FnOgreManualObjectEstimateCount>("?estimateVertexCount@ManualObject@Ogre@@UAEXI@Z");
                api.estimateIndices =
                    ResolveOgreProc<FnOgreManualObjectEstimateCount>("?estimateIndexCount@ManualObject@Ogre@@UAEXI@Z");
                api.begin = ResolveOgreProc<FnOgreManualObjectBegin>(
                    "?begin@ManualObject@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@"
                    "W4OperationType@RenderOperation@2@0@Z");
                api.position = ResolveOgreProc<FnOgreManualObjectVertex3>("?position@ManualObject@Ogre@@UAEXMMM@Z");
                api.textureCoord =
                    ResolveOgreProc<FnOgreManualObjectTexture2>("?textureCoord@ManualObject@Ogre@@UAEXMM@Z");
                api.colour = ResolveOgreProc<FnManualColour>("?colour@ManualObject@Ogre@@UAEXMMMM@Z");
                api.index = ResolveOgreProc<FnOgreManualObjectIndex>("?index@ManualObject@Ogre@@UAEXI@Z");
                api.end = ResolveOgreProc<FnOgreManualObjectEnd>("?end@ManualObject@Ogre@@UAEPAVManualObjectSection@12@XZ");
                api.setVisible = ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
                api.setNodePosition = ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
                api.setCastShadows = ResolveOgreProc<FnSetCastShadows>("?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
                api.destroyManualObject = ResolveOgreProc<FnDestroyManualObject>(
                    "?destroyManualObject@SceneManager@Ogre@@UAEXPAVManualObject@2@@Z");
                api.destroySceneNode =
                    ResolveOgreProc<FnDestroySceneNode>("?destroySceneNode@SceneManager@Ogre@@UAEXPAVSceneNode@2@@Z");
                api.getTextureManager =
                    ResolveOgreProc<FnGetTextureManager>("?getSingletonPtr@TextureManager@Ogre@@SAPAV12@XZ");
                api.createManualTexture = ResolveOgreProc<FnCreateManualTexture>(
                    "?createManual@TextureManager@Ogre@@UAE?AV?$SharedPtr@VTexture@Ogre@@@2@ABV?$basic_string@DU?$"
                    "char_traits@D@std@@V?$allocator@D@2@@std@@0W4TextureType@2@IIIHW4PixelFormat@2@HPAVManualResour"
                    "ceLoader@2@_NI0@Z");
                const uint32_t heightAt = HookEngine::ResolveNamedAddress("Terrain::HeightAt");
                api.heightAt = reinterpret_cast<FnHeightAt>(static_cast<uintptr_t>(heightAt));
                api.usable = api.createManualObject && api.getRootSceneNode && api.createChildSceneNode &&
                             api.attachObject && api.estimateVertices && api.begin &&
                             api.position && api.textureCoord && api.colour && api.index && api.end &&
                             api.setVisible && api.setNodePosition && api.setCastShadows && api.destroyManualObject &&
                             api.destroySceneNode && api.getTextureManager && api.createManualTexture && api.heightAt;
                LogShimA(api.usable ? LogLevel::Info : LogLevel::Warn, kComponent,
                         "[FOGWAKE] render exports %s", api.usable ? "resolved" : "unresolved; layers unavailable");
                return api;
            }

            const std::string& MaterialName()
            {
                static const std::string name = FR::kMaterialName;
                return name;
            }
            const std::string& PayloadGroup()
            {
                static const std::string group = kChunkPayloadResourceRootName;
                return group;
            }
            const std::string& TextureName()
            {
                static const std::string name = FR::kTextureName;
                return name;
            }
            const std::string& EmptyString()
            {
                static const std::string empty;
                return empty;
            }

            // ---- Clearance texture (process lifetime) -----------------------
            struct TextureState
            {
                bool failed = false;
                OgreSharedPtr texture;          // one ref kept for the process
                FnGetD3D11Texture2D getTex2D = nullptr;
                // Last native texture seen. Not owned and never trusted across
                // ticks: device-loss recovery replaces it, so each upload asks
                // Ogre again (UploadClearance).
                ID3D11Texture2D* native = nullptr;
                bool dynamicUsage = false;      // D3D11_USAGE_DYNAMIC: Map instead of UpdateSubresource
                uint32_t width = 0, height = 0;
                std::vector<uint8_t> bytes;
                uint64_t uploadedSteps = ~0ull;
                uint32_t uploadedGeneration = 0;
            };
            TextureState g_Texture;

            bool CreateTextureCpp(const OgreApi& api, uint32_t width, uint32_t height, OgreSharedPtr& out)
            {
                try
                {
                    void* manager = api.getTextureManager();
                    if (!manager)
                        return false;
                    api.createManualTexture(manager, &out, TextureName(), PayloadGroup(), kOgreTextureType2D, width,
                                            height, 1, 0, kOgrePixelFormatL8, kOgreTextureUsageStaticWriteOnly,
                                            nullptr, false, 0, EmptyString());
                    return out.rep != nullptr;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool CreateTextureSeh(const OgreApi& api, uint32_t width, uint32_t height, OgreSharedPtr& out)
            {
                __try
                {
                    return CreateTextureCpp(api, width, height, out);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            ID3D11Texture2D* NativeTextureSeh(FnGetD3D11Texture2D getTex2D, void* texture, D3D11_TEXTURE2D_DESC& desc)
            {
                __try
                {
                    ID3D11Texture2D* native = getTex2D(texture);
                    if (native)
                        native->GetDesc(&desc);
                    return native;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool UploadSeh(ID3D11Texture2D* native, bool dynamicUsage, const uint8_t* bytes, uint32_t width,
                           uint32_t height)
            {
                ID3D11Device* device = nullptr;
                ID3D11DeviceContext* context = nullptr;
                bool ok = false;
                __try
                {
                    native->GetDevice(&device);
                    if (device)
                        device->GetImmediateContext(&context);
                    if (context)
                    {
                        if (!dynamicUsage)
                        {
                            context->UpdateSubresource(native, 0, nullptr, bytes, width, 0);
                            ok = true;
                        }
                        else
                        {
                            D3D11_MAPPED_SUBRESOURCE mapping = {};
                            if (SUCCEEDED(context->Map(native, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping)) &&
                                mapping.pData)
                            {
                                for (uint32_t row = 0; row < height; ++row)
                                    std::memcpy(static_cast<uint8_t*>(mapping.pData) + row * mapping.RowPitch,
                                                bytes + row * width, width);
                                context->Unmap(native, 0);
                                ok = true;
                            }
                        }
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    ok = false;
                }
                __try
                {
                    if (context)
                        context->Release();
                    if (device)
                        device->Release();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                return ok;
            }

            bool MeetsContract(const D3D11_TEXTURE2D_DESC& desc, uint32_t width, uint32_t height, bool& dynamicUsage)
            {
                dynamicUsage = desc.Usage == D3D11_USAGE_DYNAMIC && (desc.CPUAccessFlags & D3D11_CPU_ACCESS_WRITE);
                return desc.Width == width && desc.Height == height && desc.Format == DXGI_FORMAT_R8_UNORM &&
                       (desc.Usage == D3D11_USAGE_DEFAULT || dynamicUsage);
            }

            // Creates the texture on first use. DX11 only: the upload is a
            // D3D11 call, and RenderSystem_Direct3D11.dll is loaded under DX9
            // too, so the active render system is checked first.
            bool EnsureTexture(const OgreApi& api, uint32_t width, uint32_t height)
            {
                if (g_Texture.native)
                    return g_Texture.width == width && g_Texture.height == height;
                if (g_Texture.failed)
                    return false;
                g_Texture.failed = true; // cleared below on success
                const int renderSystem = RenderProfiles::IdentifyActiveRenderSystem();
                if (renderSystem != 1)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "[FOGWAKE] render stands down: active render system %d is not Direct3D11", renderSystem);
                    return false;
                }
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                const auto getTex2D = renderer ? reinterpret_cast<FnGetD3D11Texture2D>(GetProcAddress(
                                                     renderer, "?GetTex2D@D3D11Texture@Ogre@@QAEPAUID3D11Texture2D@@XZ"))
                                               : nullptr;
                if (!getTex2D || !EnsureSkinnedGibResourceLocations() ||
                    !CreateTextureSeh(api, width, height, g_Texture.texture))
                {
                    LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] render stands down: clearance texture not created");
                    return false;
                }
                D3D11_TEXTURE2D_DESC desc = {};
                ID3D11Texture2D* native = NativeTextureSeh(getTex2D, g_Texture.texture.rep, desc);
                bool dynamicUsage = false;
                if (!native || !MeetsContract(desc, width, height, dynamicUsage))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "[FOGWAKE] render stands down: clearance texture contract native=%d %ux%u format=%d usage=%d",
                             native ? 1 : 0, desc.Width, desc.Height, static_cast<int>(desc.Format),
                             static_cast<int>(desc.Usage));
                    return false;
                }
                g_Texture.getTex2D = getTex2D;
                g_Texture.native = native;
                g_Texture.dynamicUsage = dynamicUsage;
                g_Texture.width = width;
                g_Texture.height = height;
                g_Texture.bytes.assign(static_cast<size_t>(width) * height, 0);
                g_Texture.failed = false;
                LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] render clearance texture %ux%u R8 usage=%s", width,
                         height, dynamicUsage ? "dynamic" : "default");
                return true;
            }

            void UploadClearance(const FogWakeRenderView& view)
            {
                // Ask Ogre for the native texture every upload: device-loss
                // recovery frees it and creates a new one. Null means the
                // device is lost right now; try again next tick.
                D3D11_TEXTURE2D_DESC desc = {};
                ID3D11Texture2D* const native = NativeTextureSeh(g_Texture.getTex2D, g_Texture.texture.rep, desc);
                if (!native)
                    return;
                if (native != g_Texture.native)
                {
                    bool dynamicUsage = false;
                    if (!MeetsContract(desc, g_Texture.width, g_Texture.height, dynamicUsage))
                    {
                        g_Texture.native = nullptr;
                        g_Texture.failed = true;
                        LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] render restored texture breaks contract; layers off");
                        return;
                    }
                    g_Texture.native = native;
                    g_Texture.dynamicUsage = dynamicUsage;
                    g_Texture.uploadedSteps = ~0ull; // restored contents are undefined
                }
                if (g_Texture.uploadedSteps == view.steps && g_Texture.uploadedGeneration == view.bankGeneration)
                    return;
                const size_t count = static_cast<size_t>(g_Texture.width) * g_Texture.height;
                for (size_t i = 0; i < count; ++i)
                {
                    const float c = std::clamp(view.clearance[i], 0.0f, 1.0f);
                    g_Texture.bytes[i] = static_cast<uint8_t>(c * 255.0f + 0.5f);
                }
                if (!UploadSeh(g_Texture.native, g_Texture.dynamicUsage, g_Texture.bytes.data(), g_Texture.width,
                               g_Texture.height))
                {
                    g_Texture.native = nullptr;
                    g_Texture.failed = true;
                    LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] render clearance upload failed; layers off");
                    return;
                }
                g_Texture.uploadedSteps = view.steps;
                g_Texture.uploadedGeneration = view.bankGeneration;
            }

            // ---- Layer mesh (scene lifetime) ---------------------------------
            struct LayerState
            {
                void* sceneManager = nullptr;
                void* node = nullptr;
                void* manual = nullptr;
                uint32_t generation = 0; // bank the mesh was built for
                bool visible = false;
                bool failed = false;     // creation failed in this scene; not retried until it changes
                double centreX = 0, centreZ = 0;
            };
            LayerState g_Layers;

            struct GridVertex
            {
                float x, y, z, u, v;
            };

            bool CreateLayersCpp(const OgreApi& api, void* sceneManager, LayerState& state)
            {
                try
                {
                    void* root = api.getRootSceneNode(sceneManager);
                    if (!root)
                        return false;
                    const OgreVector3 origin = {0.0f, 0.0f, 0.0f};
                    const OgreQuaternion identity = {1.0f, 0.0f, 0.0f, 0.0f};
                    void* node = api.createChildSceneNode(root, origin, identity);
                    void* manual = node ? api.createManualObject(sceneManager) : nullptr;
                    if (!manual)
                        return false;
                    api.attachObject(node, manual);
                    api.setCastShadows(manual, false);
                    api.setVisible(manual, false);
                    state.sceneManager = sceneManager;
                    state.node = node;
                    state.manual = manual;
                    return true;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool CreateLayersSeh(const OgreApi& api, void* sceneManager, LayerState& state)
            {
                __try
                {
                    return CreateLayersCpp(api, sceneManager, state);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool EmitLayersCpp(const OgreApi& api, void* manual, const GridVertex* grid, unsigned side)
            {
                bool started = false;
                try
                {
                    const unsigned vertices = side * side;
                    const unsigned indices = (side - 1) * (side - 1) * 6;
                    api.estimateVertices(manual, vertices);
                    if (api.estimateIndices)
                        api.estimateIndices(manual, indices);
                    for (unsigned layer = 0; layer < kLayerCount; ++layer)
                    {
                        api.begin(manual, MaterialName(), kOgreTriangleList, PayloadGroup());
                        started = true;
                        const float lift = kLayerHeights[layer];
                        const float fraction = kLayerFractions[layer];
                        for (unsigned i = 0; i < vertices; ++i)
                        {
                            api.position(manual, grid[i].x, grid[i].y + lift, grid[i].z);
                            api.colour(manual, 1.0f, 1.0f, 1.0f, fraction);
                            api.textureCoord(manual, grid[i].u, grid[i].v);
                        }
                        for (unsigned row = 0; row + 1 < side; ++row)
                            for (unsigned col = 0; col + 1 < side; ++col)
                            {
                                const uint32_t a = row * side + col, b = a + 1, c = a + side, d = c + 1;
                                api.index(manual, a);
                                api.index(manual, c);
                                api.index(manual, b);
                                api.index(manual, b);
                                api.index(manual, c);
                                api.index(manual, d);
                            }
                        api.end(manual);
                        started = false;
                    }
                    return true;
                }
                catch (...)
                {
                    if (started)
                    {
                        try
                        {
                            api.end(manual);
                        }
                        catch (...)
                        {
                        }
                    }
                    return false;
                }
            }

            bool EmitLayersSeh(const OgreApi& api, void* manual, const GridVertex* grid, unsigned side)
            {
                __try
                {
                    return EmitLayersCpp(api, manual, grid, side);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool HeightSeh(FnHeightAt heightAt, double x, double z, double& out)
            {
                __try
                {
                    out = heightAt(x, z);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out) && std::fabs(out) < 1.0e6;
            }

            bool SetVisibleSeh(const OgreApi& api, void* manual, bool visible)
            {
                __try
                {
                    api.setVisible(manual, visible);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SetNodePositionSeh(const OgreApi& api, void* node, float x, float y, float z)
            {
                __try
                {
                    api.setNodePosition(node, x, y, z);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadRenderOrigin(float (&out)[3])
            {
                const uintptr_t originAddr = WorldRenderOriginAddr();
                if (!originAddr)
                    return false;
                __try
                {
                    const float* origin = reinterpret_cast<const float*>(originAddr);
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

            void HideLayers()
            {
                if (g_Layers.visible && g_Layers.manual)
                    SetVisibleSeh(GetApi(), g_Layers.manual, false);
                g_Layers.visible = false;
            }

            void ForgetLayers(const wchar_t* reason)
            {
                const bool held = g_Layers.manual || g_Layers.node;
                g_Layers = LayerState{};
                if (held)
                    LogShimW(LogLevel::Info, kComponent, L"[FOGWAKE] render forgot layers (%ls)",
                             reason ? reason : L"unspecified");
            }

            // Builds the terrain-following grid for the bank and emits the
            // layers. The grid samples Terrain::HeightAt once per vertex.
            bool BuildLayers(const OgreApi& api, const FogWakeRenderView& view)
            {
                const double bankX = static_cast<double>(view.width) * view.cellSize;
                const double bankZ = static_cast<double>(view.height) * view.cellSize;
                const unsigned side = static_cast<unsigned>(std::lround(std::min(bankX, bankZ) / kGridStep)) + 1u;
                if (side < 2 || side > kMaxGridVerts)
                    return false;
                const double centreX = view.originX + bankX * 0.5;
                const double centreZ = view.originZ + bankZ * 0.5;
                static std::vector<GridVertex> grid;
                grid.resize(static_cast<size_t>(side) * side);
                double last = 0.0;
                unsigned missed = 0;
                for (unsigned row = 0; row < side; ++row)
                    for (unsigned col = 0; col < side; ++col)
                    {
                        const double simX = view.originX + col * kGridStep;
                        const double simZ = view.originZ + row * kGridStep;
                        double h = last;
                        if (!HeightSeh(api.heightAt, simX, simZ, h))
                        {
                            h = last; // off the map: keep the neighbour's height
                            ++missed;
                        }
                        last = h;
                        GridVertex& v = grid[static_cast<size_t>(row) * side + col];
                        // Node-local render space: x keeps its sign, z flips.
                        v.x = static_cast<float>(simX - centreX);
                        v.y = static_cast<float>(h);
                        v.z = static_cast<float>(-(simZ - centreZ));
                        v.u = static_cast<float>((simX - view.originX) / bankX);
                        v.v = static_cast<float>((simZ - view.originZ) / bankZ);
                    }
                if (!EmitLayersSeh(api, g_Layers.manual, grid.data(), side))
                    return false;
                g_Layers.centreX = centreX;
                g_Layers.centreZ = centreZ;
                LogShimA(LogLevel::Info, kComponent,
                         "[FOGWAKE] render layers built gen=%u grid=%ux%u step=%.0fm layers=%u heightMisses=%u",
                         view.bankGeneration, side, side, kGridStep, kLayerCount, missed);
                return true;
            }

            // The bank latches to the first engine-flame emitter. A scene with
            // no thrusting craft would never get one, so fall back to the
            // local player's position: fog should be there before anything
            // moves through it. Placing does not observe, so nothing is carved.
            void PlaceBankAroundPlayerIfAbsent()
            {
                const uintptr_t slot = EngineGlobals::UserObjectSlot();
                if (!slot)
                    return;
                void* user = nullptr;
                __try
                {
                    user = *reinterpret_cast<void* const*>(slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return;
                }
                float position[3] = {};
                if (user && TryGetGameObjectWorldPosition(user, position))
                    FogWakePlaceBankIfAbsent(position[0], position[2]);
            }

            void TickEnabled()
            {
                FogWakeRenderView view;
                if (!FogWakeGetRenderView(view))
                    PlaceBankAroundPlayerIfAbsent();
                if (!FogWakeGetRenderView(view))
                {
                    HideLayers();
                    return;
                }
                // Never mutate the scene inside render-queue traversal.
                if (InsideRenderQueueHookWithDeferral())
                    return;
                const OgreApi& api = GetApi();
                void* const sceneManager = GetOgreSceneManagerRuntime();
                float origin[3] = {};
                if (!api.usable || !sceneManager || !ReadRenderOrigin(origin))
                {
                    HideLayers();
                    return;
                }
                if (g_Layers.sceneManager && g_Layers.sceneManager != sceneManager)
                    ForgetLayers(L"scene manager changed");
                if (!EnsureTexture(api, static_cast<uint32_t>(view.width), static_cast<uint32_t>(view.height)))
                {
                    HideLayers();
                    return;
                }
                UploadClearance(view);
                if (!g_Texture.native)
                {
                    HideLayers();
                    return;
                }
                if (g_Layers.failed)
                    return;
                // A bank re-placed in the same scene: the old mesh belongs to
                // the old bank. Rebuilt on a fresh ManualObject (game thread,
                // outside traversal, so destroying here is safe).
                if (g_Layers.manual && g_Layers.generation != view.bankGeneration)
                    DestroyFogWakeSceneObjects(sceneManager, L"bank re-placed");
                if (!g_Layers.manual)
                {
                    if (!EnsureSkinnedGibResourceLocations() || !CreateLayersSeh(api, sceneManager, g_Layers))
                    {
                        g_Layers.failed = true;
                        LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] render layer creation failed; off for this scene");
                        return;
                    }
                }
                if (g_Layers.generation != view.bankGeneration)
                {
                    if (!BuildLayers(api, view))
                    {
                        HideLayers();
                        g_Layers.failed = true;
                        LogShimA(LogLevel::Warn, kComponent, "[FOGWAKE] render layer build failed; off for this scene");
                        return;
                    }
                    g_Layers.generation = view.bankGeneration;
                }
                // The node follows the render origin every tick.
                const float x = static_cast<float>(g_Layers.centreX) - origin[0];
                const float y = -origin[1];
                const float z = static_cast<float>(-g_Layers.centreZ) - origin[2];
                if (!SetNodePositionSeh(api, g_Layers.node, x, y, z))
                {
                    HideLayers();
                    return;
                }
                if (!g_Layers.visible)
                {
                    if (!SetVisibleSeh(api, g_Layers.manual, true))
                        return;
                    g_Layers.visible = true;
                    LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] render layers shown");
                }
            }
        }

        void TickFogWakeRender()
        {
            if (!FogWakeFeatureEnabled())
                return;
            TickEnabled();
        }

        void DestroyFogWakeSceneObjects(void* sceneManager, const wchar_t* reason)
        {
            if (!g_Layers.sceneManager || g_Layers.sceneManager != sceneManager)
                return;
            const OgreApi& api = GetApi();
            if (api.usable && sceneManager == GetOgreSceneManagerRuntime())
            {
                if (g_Layers.manual)
                {
                    __try
                    {
                        api.destroyManualObject(sceneManager, g_Layers.manual);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                }
                if (g_Layers.node)
                {
                    __try
                    {
                        api.destroySceneNode(sceneManager, g_Layers.node);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                }
            }
            ForgetLayers(reason);
        }

        void ForgetFogWakeSceneResources(const wchar_t* reason)
        {
            ForgetLayers(reason);
        }

        void EnsureFogWakeRenderAssets(const std::filesystem::path& cacheRoot,
                                       const std::vector<std::filesystem::path>& payloadDirectories)
        {
            // Same policy as EnsureRtsMarkerAssets: written whatever the
            // toggle says; only marked files are rewritten; an asset pack
            // shipping the same name wins.
            if (cacheRoot.empty())
                return;
            try
            {
                std::error_code ec;
                const auto readAll = [](const std::filesystem::path& path) {
                    std::ifstream input(path, std::ios::binary);
                    return std::string((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
                };
                struct Asset
                {
                    const char* file;
                    std::string data;
                };
                const Asset assets[] = {
                    {FR::kShaderFile, FR::ShaderSource()},
                    {FR::kMaterialFile, FR::MaterialScript()},
                };
                for (const Asset& asset : assets)
                {
                    const auto ours = cacheRoot / asset.file;
                    const std::string existing = readAll(ours);
                    if (!existing.empty() && !FR::IsGeneratedText(existing))
                        continue;
                    bool overridden = false;
                    for (const auto& directory : payloadDirectories)
                    {
                        if (std::filesystem::equivalent(directory, cacheRoot, ec) && !ec)
                            continue;
                        ec.clear();
                        if (std::filesystem::is_regular_file(directory / asset.file, ec) && !ec)
                        {
                            overridden = true;
                            break;
                        }
                        ec.clear();
                    }
                    if (overridden)
                    {
                        if (!existing.empty())
                            std::filesystem::remove(ours, ec);
                        continue;
                    }
                    if (existing == asset.data)
                        continue;
                    std::filesystem::create_directories(ours.parent_path(), ec);
                    std::ofstream output(ours, std::ios::binary | std::ios::trunc);
                    output.write(asset.data.data(), static_cast<std::streamsize>(asset.data.size()));
                    output.close();
                    LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] wrote %s ok=%d", ours.string().c_str(),
                             output ? 1 : 0);
                }
            }
            catch (...)
            {
            }
        }
    }
}
