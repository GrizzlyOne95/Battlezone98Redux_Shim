        void InstallContextHooks(ID3D11DeviceContext* context);
        bool RefreshContextHooks(ID3D11DeviceContext* context);
        void STDMETHODCALLTYPE HookDrawIndexed(
            ID3D11DeviceContext* self,
            UINT indexCount,
            UINT startIndexLocation,
            INT baseVertexLocation);

        void __fastcall HookD3D11RenderSystemRender(
            void* self,
            void*,
            const void* renderOperation)
        {
            FnD3D11RenderSystemRender real = g_RealD3D11RenderSystemRender;
            if (!real)
                return;

            const uint64_t frame = g_FrameEpoch.load(std::memory_order_relaxed);
            if (t_LastRenderContextCheckFrame != frame &&
                g_D3D11RenderSystemGetDevice &&
                g_OgreD3D11DeviceGetImmediateContext)
            {
                t_LastRenderContextCheckFrame = frame;
                void* deviceWrapper = g_D3D11RenderSystemGetDevice(self);
                ID3D11DeviceContext* context = deviceWrapper
                    ? g_OgreD3D11DeviceGetImmediateContext(deviceWrapper)
                    : nullptr;
                if (context)
                {
                    void*** objectVtable = reinterpret_cast<void***>(context);
                    const bool drawObserverMissing = !objectVtable || !*objectVtable ||
                        (*objectVtable)[12] != reinterpret_cast<void*>(&HookDrawIndexed);
                    const uintptr_t identity = reinterpret_cast<uintptr_t>(context);
                    const uintptr_t previous =
                        g_RenderContextIdentity.load(std::memory_order_relaxed);
                    if (identity != previous)
                    {
                        InstallContextHooks(context);
                        g_RenderContextIdentity.store(identity, std::memory_order_release);
                        LogShimA(
                            LogLevel::Info,
                            kComponent,
                            "[OgreProfile] captured renderer-owned immediate context=0x%p previous=0x%p drawObserverWasMissing=%s",
                            context,
                            reinterpret_cast<void*>(previous),
                            drawObserverMissing ? "yes" : "no");
                    }
                    else if (drawObserverMissing && RefreshContextHooks(context))
                    {
                        g_ContextVtableRefreshes.fetch_add(1, std::memory_order_relaxed);
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

        void __fastcall HookEntityUpdateRenderQueue(void* self, void*, void* renderQueue)
        {
            if (!g_RealEntityUpdateRenderQueue)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealEntityUpdateRenderQueue(self, renderQueue);
                return;
            }

            g_RenderQueueCalls.fetch_add(1, std::memory_order_relaxed);
            BloomAdd(g_RenderEntityBloom, self);
            RenderQueueScope scope(self);
            g_RealEntityUpdateRenderQueue(self, renderQueue);
        }

        void STDMETHODCALLTYPE HookDrawIndexed(
            ID3D11DeviceContext* self,
            UINT indexCount,
            UINT startIndexLocation,
            INT baseVertexLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawIndexedCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawIndexedIndices.fetch_add(indexCount, std::memory_order_relaxed);
            }
            g_RealDrawIndexed(self, indexCount, startIndexLocation, baseVertexLocation);
        }

        void STDMETHODCALLTYPE HookDraw(
            ID3D11DeviceContext* self,
            UINT vertexCount,
            UINT startVertexLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawVertices.fetch_add(vertexCount, std::memory_order_relaxed);
            }
            g_RealDraw(self, vertexCount, startVertexLocation);
        }

        HRESULT STDMETHODCALLTYPE HookMap(
            ID3D11DeviceContext* self, ID3D11Resource* resource, UINT subresource,
            D3D11_MAP mapType, UINT mapFlags, D3D11_MAPPED_SUBRESOURCE* mapped)
        {
            const uint64_t start = g_Enabled.load(std::memory_order_relaxed) ? ReadQpc() : 0;
            const HRESULT hr = g_RealMap(self, resource, subresource, mapType, mapFlags, mapped);
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                const uint64_t elapsed = ReadQpc() - start;
                g_MapCalls.fetch_add(1, std::memory_order_relaxed);
                g_MapTicks.fetch_add(elapsed, std::memory_order_relaxed);
                AtomicMax(g_MapMaxTicks, elapsed);
                if (t_CurrentAnimationEntity)
                    g_MapDuringAnimationCalls.fetch_add(1, std::memory_order_relaxed);
                if (t_SoftwareBlendDepth)
                    g_MapDuringBlendCalls.fetch_add(1, std::memory_order_relaxed);
                switch (mapType)
                {
                case D3D11_MAP_WRITE:
                    g_MapWriteCalls.fetch_add(1, std::memory_order_relaxed);
                    break;
                case D3D11_MAP_WRITE_DISCARD:
                    g_MapWriteDiscardCalls.fetch_add(1, std::memory_order_relaxed);
                    break;
                case D3D11_MAP_WRITE_NO_OVERWRITE:
                    g_MapWriteNoOverwriteCalls.fetch_add(1, std::memory_order_relaxed);
                    break;
                default:
                    g_MapOtherCalls.fetch_add(1, std::memory_order_relaxed);
                    break;
                }
            }
            return hr;
        }

        void STDMETHODCALLTYPE HookUnmap(
            ID3D11DeviceContext* self, ID3D11Resource* resource, UINT subresource)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_UnmapCalls.fetch_add(1, std::memory_order_relaxed);
                if (t_CurrentAnimationEntity)
                    g_UnmapDuringAnimationCalls.fetch_add(1, std::memory_order_relaxed);
            }
            g_RealUnmap(self, resource, subresource);
        }

        void STDMETHODCALLTYPE HookUpdateSubresource(
            ID3D11DeviceContext* self, ID3D11Resource* resource, UINT subresource,
            const D3D11_BOX* box, const void* sourceData, UINT sourceRowPitch,
            UINT sourceDepthPitch)
        {
            const uint64_t start = g_Enabled.load(std::memory_order_relaxed) ? ReadQpc() : 0;
            g_RealUpdateSubresource(
                self, resource, subresource, box, sourceData,
                sourceRowPitch, sourceDepthPitch);
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                const uint64_t elapsed = ReadQpc() - start;
                g_UpdateSubresourceCalls.fetch_add(1, std::memory_order_relaxed);
                g_UpdateSubresourceTicks.fetch_add(elapsed, std::memory_order_relaxed);
                AtomicMax(g_UpdateSubresourceMaxTicks, elapsed);
                if (t_CurrentAnimationEntity)
                    g_UpdateSubresourceDuringAnimationCalls.fetch_add(1, std::memory_order_relaxed);
                if (t_SoftwareBlendDepth)
                    g_UpdateSubresourceDuringBlendCalls.fetch_add(1, std::memory_order_relaxed);
            }
        }

        void STDMETHODCALLTYPE HookDrawIndexedInstanced(
            ID3D11DeviceContext* self, UINT indexCountPerInstance, UINT instanceCount,
            UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawIndexedInstancedCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawIndexedInstancedIndices.fetch_add(
                    static_cast<uint64_t>(indexCountPerInstance) * instanceCount,
                    std::memory_order_relaxed);
            }
            g_RealDrawIndexedInstanced(
                self, indexCountPerInstance, instanceCount, startIndexLocation,
                baseVertexLocation, startInstanceLocation);
        }

        void STDMETHODCALLTYPE HookDrawInstanced(
            ID3D11DeviceContext* self, UINT vertexCountPerInstance, UINT instanceCount,
            UINT startVertexLocation, UINT startInstanceLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawInstancedCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawInstancedVertices.fetch_add(
                    static_cast<uint64_t>(vertexCountPerInstance) * instanceCount,
                    std::memory_order_relaxed);
            }
            g_RealDrawInstanced(
                self, vertexCountPerInstance, instanceCount,
                startVertexLocation, startInstanceLocation);
        }

        void STDMETHODCALLTYPE HookDrawIndexedInstancedIndirect(
            ID3D11DeviceContext* self, ID3D11Buffer* args, UINT offset)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_DrawIndexedInstancedIndirectCalls.fetch_add(1, std::memory_order_relaxed);
            g_RealDrawIndexedInstancedIndirect(self, args, offset);
        }

        void STDMETHODCALLTYPE HookDrawInstancedIndirect(
            ID3D11DeviceContext* self, ID3D11Buffer* args, UINT offset)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_DrawInstancedIndirectCalls.fetch_add(1, std::memory_order_relaxed);
            g_RealDrawInstancedIndirect(self, args, offset);
        }

        HRESULT STDMETHODCALLTYPE HookPresent(IDXGISwapChain* self, UINT syncInterval, UINT flags)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                const uint64_t now = ReadQpc();
                const uint64_t previous = g_LastPresentQpc.exchange(now, std::memory_order_relaxed);
                if (previous && now > previous)
                    RecordFrameTime(now - previous);
                g_Presents.fetch_add(1, std::memory_order_relaxed);
                g_FrameEpoch.fetch_add(1, std::memory_order_relaxed);
            }
            if (!g_PresentObserved.exchange(true, std::memory_order_acq_rel))
                RefreshProfilerState("first DX11 Present observed");
            return g_RealPresent(self, syncInterval, flags);
        }

        void InstallContextHooks(ID3D11DeviceContext* context)
        {
            if (!context)
                return;

            // Public ID3D11DeviceContext ABI ordinals from d3d11.h.
            const bool indexed = PatchComVtableEntry(
                context, 12, &HookDrawIndexed, g_RealDrawIndexed,
                "ID3D11DeviceContext::DrawIndexed");
            const bool draw = PatchComVtableEntry(
                context, 13, &HookDraw, g_RealDraw,
                "ID3D11DeviceContext::Draw");
            const bool map = PatchComVtableEntry(
                context, 14, &HookMap, g_RealMap,
                "ID3D11DeviceContext::Map");
            const bool unmap = PatchComVtableEntry(
                context, 15, &HookUnmap, g_RealUnmap,
                "ID3D11DeviceContext::Unmap");
            const bool indexedInstanced = PatchComVtableEntry(
                context, 20, &HookDrawIndexedInstanced, g_RealDrawIndexedInstanced,
                "ID3D11DeviceContext::DrawIndexedInstanced");
            const bool instanced = PatchComVtableEntry(
                context, 21, &HookDrawInstanced, g_RealDrawInstanced,
                "ID3D11DeviceContext::DrawInstanced");
            const bool indexedIndirect = PatchComVtableEntry(
                context, 39, &HookDrawIndexedInstancedIndirect,
                g_RealDrawIndexedInstancedIndirect,
                "ID3D11DeviceContext::DrawIndexedInstancedIndirect");
            const bool indirect = PatchComVtableEntry(
                context, 40, &HookDrawInstancedIndirect, g_RealDrawInstancedIndirect,
                "ID3D11DeviceContext::DrawInstancedIndirect");
            const bool updateSubresource = PatchComVtableEntry(
                context, 48, &HookUpdateSubresource, g_RealUpdateSubresource,
                "ID3D11DeviceContext::UpdateSubresource");
            if (indexed || draw || map || unmap || indexedInstanced || instanced ||
                indexedIndirect || indirect || updateSubresource)
            {
                g_Dx11ContextObserved.store(true, std::memory_order_release);
                RefreshProfilerState("DX11 context observers active");
            }
        }

        bool RefreshContextHooks(ID3D11DeviceContext* context)
        {
            if (!context || !g_RealDrawIndexed || !g_RealDraw || !g_RealMap ||
                !g_RealUnmap || !g_RealDrawIndexedInstanced || !g_RealDrawInstanced ||
                !g_RealDrawIndexedInstancedIndirect || !g_RealDrawInstancedIndirect ||
                !g_RealUpdateSubresource)
            {
                return false;
            }

            struct RefreshEntry
            {
                size_t index;
                void* hook;
                void* original;
            };
            const RefreshEntry entries[] =
            {
                { 12, reinterpret_cast<void*>(&HookDrawIndexed), reinterpret_cast<void*>(g_RealDrawIndexed) },
                { 13, reinterpret_cast<void*>(&HookDraw), reinterpret_cast<void*>(g_RealDraw) },
                { 14, reinterpret_cast<void*>(&HookMap), reinterpret_cast<void*>(g_RealMap) },
                { 15, reinterpret_cast<void*>(&HookUnmap), reinterpret_cast<void*>(g_RealUnmap) },
                { 20, reinterpret_cast<void*>(&HookDrawIndexedInstanced), reinterpret_cast<void*>(g_RealDrawIndexedInstanced) },
                { 21, reinterpret_cast<void*>(&HookDrawInstanced), reinterpret_cast<void*>(g_RealDrawInstanced) },
                { 39, reinterpret_cast<void*>(&HookDrawIndexedInstancedIndirect), reinterpret_cast<void*>(g_RealDrawIndexedInstancedIndirect) },
                { 40, reinterpret_cast<void*>(&HookDrawInstancedIndirect), reinterpret_cast<void*>(g_RealDrawInstancedIndirect) },
                { 48, reinterpret_cast<void*>(&HookUpdateSubresource), reinterpret_cast<void*>(g_RealUpdateSubresource) }
            };

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            void*** objectVtable = reinterpret_cast<void***>(context);
            if (!objectVtable || !*objectVtable)
                return false;
            void** vtable = *objectVtable;
            bool needsWrite = false;
            for (const RefreshEntry& entry : entries)
            {
                void* current = vtable[entry.index];
                if (current == entry.hook)
                    continue;
                if (current != entry.original)
                    return false;
                needsWrite = true;
            }
            if (!needsWrite)
                return true;

            DWORD oldProtection = 0;
            void** begin = &vtable[entries[0].index];
            const size_t byteLength =
                (entries[(sizeof(entries) / sizeof(entries[0])) - 1].index -
                 entries[0].index + 1) * sizeof(void*);
            if (!VirtualProtect(begin, byteLength, PAGE_READWRITE, &oldProtection))
                return false;
            for (const RefreshEntry& entry : entries)
            {
                if (vtable[entry.index] == entry.original)
                    vtable[entry.index] = entry.hook;
            }
            DWORD ignored = 0;
            VirtualProtect(begin, byteLength, oldProtection, &ignored);
            return true;
        }

        HRESULT STDMETHODCALLTYPE HookCreateDeferredContext(
            ID3D11Device* self,
            UINT contextFlags,
            ID3D11DeviceContext** deferredContext)
        {
            const HRESULT hr = g_RealCreateDeferredContext(
                self,
                contextFlags,
                deferredContext);
            if (SUCCEEDED(hr) && deferredContext && *deferredContext)
                InstallContextHooks(*deferredContext);
            return hr;
        }

        void CaptureSwapChain(IDXGISwapChain* swapChain)
        {
            if (!swapChain)
                return;
            // Public IDXGISwapChain ABI ordinal.
            PatchComVtableEntry(
                swapChain, 8, &HookPresent, g_RealPresent,
                "IDXGISwapChain::Present");
        }

        HRESULT STDMETHODCALLTYPE HookFactoryCreateSwapChain(
            IDXGIFactory* self,
            IUnknown* device,
            DXGI_SWAP_CHAIN_DESC* desc,
            IDXGISwapChain** swapChain)
        {
            const HRESULT hr = g_RealFactoryCreateSwapChain(self, device, desc, swapChain);
            if (SUCCEEDED(hr) && swapChain && *swapChain)
                CaptureSwapChain(*swapChain);
            return hr;
        }

        void InstallFactoryFromDevice(ID3D11Device* device)
        {
            if (!device)
                return;

            IDXGIDevice* dxgiDevice = nullptr;
            if (FAILED(device->QueryInterface(
                    __uuidof(IDXGIDevice),
                    reinterpret_cast<void**>(&dxgiDevice))) || !dxgiDevice)
            {
                return;
            }

            IDXGIAdapter* adapter = nullptr;
            if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter)) && adapter)
            {
                IDXGIFactory* factory = nullptr;
                if (SUCCEEDED(adapter->GetParent(
                        __uuidof(IDXGIFactory),
                        reinterpret_cast<void**>(&factory))) && factory)
                {
                    // Public IDXGIFactory ABI ordinal.
                    PatchComVtableEntry(
                        factory, 10, &HookFactoryCreateSwapChain,
                        g_RealFactoryCreateSwapChain,
                        "IDXGIFactory::CreateSwapChain");
                    factory->Release();
                }
                adapter->Release();
            }
            dxgiDevice->Release();
        }

        void InstallDeviceHooks(ID3D11Device* device, ID3D11DeviceContext* suppliedContext)
        {
            if (!device)
                return;

            InstallFactoryFromDevice(device);
            // Public ID3D11Device ABI ordinal. Ogre can record all work on
            // deferred contexts and execute command lists on the immediate
            // context, so observing only the supplied immediate context misses
            // every Draw/Map in that renderer configuration.
            PatchComVtableEntry(
                device, 27, &HookCreateDeferredContext,
                g_RealCreateDeferredContext,
                "ID3D11Device::CreateDeferredContext");
            if (suppliedContext)
            {
                InstallContextHooks(suppliedContext);
                return;
            }

            ID3D11DeviceContext* context = nullptr;
            device->GetImmediateContext(&context);
            if (context)
            {
                InstallContextHooks(context);
                context->Release();
            }
        }

        HRESULT WINAPI HookD3D11CreateDevice(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDevice(
                adapter, driverType, software, flags,
                featureLevels, featureLevelCount, sdkVersion,
                device, featureLevel, immediateContext);
            if (SUCCEEDED(hr) && device && *device)
            {
                InstallDeviceHooks(
                    *device,
                    immediateContext ? *immediateContext : nullptr);
            }
            return hr;
        }

        HRESULT WINAPI HookD3D11CreateDeviceAndSwapChain(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            const DXGI_SWAP_CHAIN_DESC* swapChainDesc,
            IDXGISwapChain** swapChain,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDeviceAndSwapChain(
                adapter, driverType, software, flags,
                featureLevels, featureLevelCount, sdkVersion,
                swapChainDesc, swapChain, device, featureLevel, immediateContext);
            if (SUCCEEDED(hr))
            {
                if (device && *device)
                {
                    InstallDeviceHooks(
                        *device,
                        immediateContext ? *immediateContext : nullptr);
                }
                if (swapChain && *swapChain)
                    CaptureSwapChain(*swapChain);
            }
            return hr;
        }

