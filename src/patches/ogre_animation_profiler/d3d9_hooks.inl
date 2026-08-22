        void InstallD3D9DeviceHooks(IDirect3DDevice9* device);
        HRESULT STDMETHODCALLTYPE HookD3D9DrawIndexedPrimitive(
            IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);

        uint64_t D3D9PrimitiveVertexCount(
            D3DPRIMITIVETYPE primitiveType,
            UINT primitiveCount)
        {
            switch (primitiveType)
            {
            case D3DPT_POINTLIST:
                return primitiveCount;
            case D3DPT_LINELIST:
                return static_cast<uint64_t>(primitiveCount) * 2u;
            case D3DPT_LINESTRIP:
                return primitiveCount ? static_cast<uint64_t>(primitiveCount) + 1u : 0u;
            case D3DPT_TRIANGLELIST:
                return static_cast<uint64_t>(primitiveCount) * 3u;
            case D3DPT_TRIANGLESTRIP:
            case D3DPT_TRIANGLEFAN:
                return primitiveCount ? static_cast<uint64_t>(primitiveCount) + 2u : 0u;
            default:
                return 0;
            }
        }

        void __fastcall HookD3D9RenderSystemRender(
            void* self,
            void*,
            const void* renderOperation)
        {
            FnD3D9RenderSystemRender real = g_RealD3D9RenderSystemRender;
            if (!real)
                return;

            const uint64_t frame = g_FrameEpoch.load(std::memory_order_relaxed);
            if (t_LastRenderContextCheckFrame != frame && g_D3D9GetActiveDevice)
            {
                t_LastRenderContextCheckFrame = frame;
                IDirect3DDevice9* device = g_D3D9GetActiveDevice();
                if (device)
                {
                    void*** objectVtable = reinterpret_cast<void***>(device);
                    const bool drawObserverMissing = !objectVtable || !*objectVtable ||
                        (*objectVtable)[82] !=
                            reinterpret_cast<void*>(&HookD3D9DrawIndexedPrimitive);
                    const uintptr_t identity = reinterpret_cast<uintptr_t>(device);
                    const uintptr_t previous =
                        g_RenderContextIdentity.load(std::memory_order_relaxed);
                    if (identity != previous || drawObserverMissing)
                    {
                        InstallD3D9DeviceHooks(device);
                        g_RenderContextIdentity.store(identity, std::memory_order_release);
                        if (identity != previous)
                        {
                            LogShimA(
                                LogLevel::Info,
                                kComponent,
                                "[OgreProfile] captured active D3D9 device=0x%p previous=0x%p drawObserverWasMissing=%s",
                                device,
                                reinterpret_cast<void*>(previous),
                                drawObserverMissing ? "yes" : "no");
                        }
                    }
                }
            }

            const bool enabled = g_Enabled.load(std::memory_order_relaxed);
            const uint64_t start = enabled ? ReadQpc() : 0;
            real(self, renderOperation);
            if (enabled)
            {
                const uint64_t elapsed = ReadQpc() - start;
                g_RenderSystemSubmissions.fetch_add(1, std::memory_order_relaxed);
                g_RenderSystemSubmissionTicks.fetch_add(elapsed, std::memory_order_relaxed);
                AtomicMax(g_RenderSystemSubmissionMaxTicks, elapsed);
            }
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SwapChainPresent(
            IDirect3DSwapChain9* self,
            const RECT* sourceRect,
            const RECT* destinationRect,
            HWND destinationWindow,
            const RGNDATA* dirtyRegion,
            DWORD flags)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                const uint64_t now = ReadQpc();
                const uint64_t previous =
                    g_LastPresentQpc.exchange(now, std::memory_order_relaxed);
                if (previous && now > previous)
                    RecordFrameTime(now - previous);
                g_Presents.fetch_add(1, std::memory_order_relaxed);
                g_FrameEpoch.fetch_add(1, std::memory_order_relaxed);
            }
            if (!g_PresentObserved.exchange(true, std::memory_order_acq_rel))
                RefreshProfilerState("first D3D9 swap-chain Present observed");
            return g_RealD3D9SwapChainPresent(
                self, sourceRect, destinationRect, destinationWindow,
                dirtyRegion, flags);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9DrawPrimitive(
            IDirect3DDevice9* self,
            D3DPRIMITIVETYPE primitiveType,
            UINT startVertex,
            UINT primitiveCount)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawVertices.fetch_add(
                    D3D9PrimitiveVertexCount(primitiveType, primitiveCount),
                    std::memory_order_relaxed);
            }
            return g_RealD3D9DrawPrimitive(
                self, primitiveType, startVertex, primitiveCount);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9DrawIndexedPrimitive(
            IDirect3DDevice9* self,
            D3DPRIMITIVETYPE primitiveType,
            INT baseVertexIndex,
            UINT minVertexIndex,
            UINT vertexCount,
            UINT startIndex,
            UINT primitiveCount)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawIndexedCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawIndexedIndices.fetch_add(
                    D3D9PrimitiveVertexCount(primitiveType, primitiveCount),
                    std::memory_order_relaxed);
            }
            return g_RealD3D9DrawIndexedPrimitive(
                self, primitiveType, baseVertexIndex, minVertexIndex,
                vertexCount, startIndex, primitiveCount);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetRenderState(
            IDirect3DDevice9* self,
            D3DRENDERSTATETYPE state,
            DWORD value)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_D3D9RenderStateCalls.fetch_add(1, std::memory_order_relaxed);
                if (state == D3DRS_ALPHABLENDENABLE || state == D3DRS_SRCBLEND ||
                    state == D3DRS_DESTBLEND || state == D3DRS_BLENDOP ||
                    state == D3DRS_SEPARATEALPHABLENDENABLE ||
                    state == D3DRS_SRCBLENDALPHA ||
                    state == D3DRS_DESTBLENDALPHA || state == D3DRS_BLENDOPALPHA)
                {
                    g_D3D9BlendStateCalls.fetch_add(1, std::memory_order_relaxed);
                }
            }
            return g_RealD3D9SetRenderState(self, state, value);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetTexture(
            IDirect3DDevice9* self,
            DWORD stage,
            IDirect3DBaseTexture9* texture)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_D3D9TextureCalls.fetch_add(1, std::memory_order_relaxed);
            return g_RealD3D9SetTexture(self, stage, texture);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetTextureStageState(
            IDirect3DDevice9* self,
            DWORD stage,
            D3DTEXTURESTAGESTATETYPE state,
            DWORD value)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_D3D9TextureStageStateCalls.fetch_add(1, std::memory_order_relaxed);
            return g_RealD3D9SetTextureStageState(self, stage, state, value);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetSamplerState(
            IDirect3DDevice9* self,
            DWORD sampler,
            D3DSAMPLERSTATETYPE state,
            DWORD value)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_D3D9SamplerStateCalls.fetch_add(1, std::memory_order_relaxed);
            return g_RealD3D9SetSamplerState(self, sampler, state, value);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetVertexShader(
            IDirect3DDevice9* self,
            IDirect3DVertexShader9* shader)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_D3D9VertexShaderCalls.fetch_add(1, std::memory_order_relaxed);
            return g_RealD3D9SetVertexShader(self, shader);
        }

        HRESULT STDMETHODCALLTYPE HookD3D9SetPixelShader(
            IDirect3DDevice9* self,
            IDirect3DPixelShader9* shader)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_D3D9PixelShaderCalls.fetch_add(1, std::memory_order_relaxed);
            return g_RealD3D9SetPixelShader(self, shader);
        }

        void InstallD3D9DeviceHooks(IDirect3DDevice9* device)
        {
            if (!device)
                return;

            // Public IDirect3DDevice9 ABI ordinals from d3d9.h. These hooks
            // count diagnostic calls only and leave arguments/results intact.
            bool present = false;
            IDirect3DSwapChain9* swapChain = nullptr;
            if (SUCCEEDED(device->GetSwapChain(0, &swapChain)) && swapChain)
            {
                // Public IDirect3DSwapChain9 ABI ordinal.
                present = PatchComVtableEntry(
                    swapChain, 3, &HookD3D9SwapChainPresent,
                    g_RealD3D9SwapChainPresent,
                    "IDirect3DSwapChain9::Present");
                swapChain->Release();
            }
            const bool renderState = PatchComVtableEntry(
                device, 57, &HookD3D9SetRenderState, g_RealD3D9SetRenderState,
                "IDirect3DDevice9::SetRenderState");
            const bool texture = PatchComVtableEntry(
                device, 65, &HookD3D9SetTexture, g_RealD3D9SetTexture,
                "IDirect3DDevice9::SetTexture");
            const bool textureStage = PatchComVtableEntry(
                device, 67, &HookD3D9SetTextureStageState,
                g_RealD3D9SetTextureStageState,
                "IDirect3DDevice9::SetTextureStageState");
            const bool sampler = PatchComVtableEntry(
                device, 69, &HookD3D9SetSamplerState, g_RealD3D9SetSamplerState,
                "IDirect3DDevice9::SetSamplerState");
            const bool draw = PatchComVtableEntry(
                device, 81, &HookD3D9DrawPrimitive, g_RealD3D9DrawPrimitive,
                "IDirect3DDevice9::DrawPrimitive");
            const bool drawIndexed = PatchComVtableEntry(
                device, 82, &HookD3D9DrawIndexedPrimitive,
                g_RealD3D9DrawIndexedPrimitive,
                "IDirect3DDevice9::DrawIndexedPrimitive");
            const bool vertexShader = PatchComVtableEntry(
                device, 92, &HookD3D9SetVertexShader, g_RealD3D9SetVertexShader,
                "IDirect3DDevice9::SetVertexShader");
            const bool pixelShader = PatchComVtableEntry(
                device, 107, &HookD3D9SetPixelShader, g_RealD3D9SetPixelShader,
                "IDirect3DDevice9::SetPixelShader");

            if (present || renderState || texture || textureStage || sampler ||
                draw || drawIndexed || vertexShader || pixelShader)
            {
                g_D3D9DeviceObserved.store(true, std::memory_order_release);
                RefreshProfilerState("D3D9 device observers active");
            }
        }

        bool InstallD3D9RendererObservers(HMODULE renderer)
        {
            if (!renderer)
                return false;

            constexpr char kRenderExport[] =
                "?_render@D3D9RenderSystem@Ogre@@UAEXABVRenderOperation@2@@Z";
            constexpr char kGetActiveDeviceExport[] =
                "?getActiveD3D9DeviceIfExists@D3D9RenderSystem@Ogre@@SAPAUIDirect3DDevice9@@XZ";
            void* exportAddress = reinterpret_cast<void*>(
                GetProcAddress(renderer, kRenderExport));
            g_D3D9GetActiveDevice = reinterpret_cast<FnD3D9GetActiveDevice>(
                GetProcAddress(renderer, kGetActiveDeviceExport));
            if (!exportAddress || !g_D3D9GetActiveDevice)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] required D3D9 exports missing render=%s activeDevice=%s",
                    exportAddress ? "yes" : "no",
                    g_D3D9GetActiveDevice ? "yes" : "no");
                return false;
            }

            if (!g_D3D9RenderSystemRenderDetour.trampoline)
            {
                void* implementation = ResolveModuleExportImplementation(
                    renderer, exportAddress, "D3D9RenderSystem::_render");
                if (!implementation)
                    return false;

                // Retail GOG RenderSystem_Direct3D9.dll SHA-256
                // 822D26CA4B9CCE82DDD2FCA5E31E7D3A0CD8D05032130A987830143E3D0F95E1.
                // Complete instruction-aligned prefix: push ebp; mov ebp,esp; push -1.
                static const uint8_t kRenderPrologue[] =
                {
                    0x55,
                    0x8B, 0xEC,
                    0x6A, 0xFF
                };
                if (!InstallEntryDetour32(
                        g_D3D9RenderSystemRenderDetour,
                        renderer,
                        implementation,
                        reinterpret_cast<void*>(&HookD3D9RenderSystemRender),
                        kRenderPrologue,
                        sizeof(kRenderPrologue),
                        "D3D9RenderSystem::_render"))
                {
                    return false;
                }
                g_RealD3D9RenderSystemRender =
                    reinterpret_cast<FnD3D9RenderSystemRender>(
                        g_D3D9RenderSystemRenderDetour.trampoline);
                g_D3D9RenderSystemObserverInstalled.store(
                    true, std::memory_order_release);
                g_RenderSystemObserverInstalled.store(
                    true, std::memory_order_release);
            }

            // getActiveD3D9DeviceIfExists still dereferences the renderer
            // singleton before Ogre selects D3D9. Defer the query until the
            // first hooked D3D9RenderSystem::_render call, where the active
            // device contract is established.
            return true;
        }
