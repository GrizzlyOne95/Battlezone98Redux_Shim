        bool InstallDx11CreationObservers(HMODULE renderer)
        {
            if (!renderer)
                return false;

            unsigned installed = 0;
            installed += PatchIatFunctionByName(
                renderer,
                "d3d11.dll",
                "D3D11CreateDevice",
                reinterpret_cast<void*>(&HookD3D11CreateDevice),
                reinterpret_cast<void**>(&g_RealD3D11CreateDevice)) ? 1u : 0u;
            installed += PatchIatFunctionByName(
                renderer,
                "d3d11.dll",
                "D3D11CreateDeviceAndSwapChain",
                reinterpret_cast<void*>(&HookD3D11CreateDeviceAndSwapChain),
                reinterpret_cast<void**>(&g_RealD3D11CreateDeviceAndSwapChain)) ? 1u : 0u;

            LogShimA(
                installed ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[OgreProfile] DX11 creation observers installed=%u renderer=0x%p",
                installed,
                renderer);
            return installed != 0;
        }

        bool InstallOgreObservers()
        {
            if (!OgreRuntime::IsLoaded())
                return false;

            void* updateAnimation = FindUniqueFunctionExport(
                "_updateAnimation@Entity@Ogre@@",
                "Entity::_updateAnimation");
            void* softwareVertexBlend = FindUniqueFunctionExport(
                "softwareVertexBlend@Mesh@Ogre@@",
                "Mesh::softwareVertexBlend");
            void* updateRenderQueue = FindUniqueFunctionExport(
                "_updateRenderQueue@Entity@Ogre@@",
                "Entity::_updateRenderQueue");

            if (!updateAnimation || !softwareVertexBlend)
                return false;

            g_RealEntityUpdateAnimation =
                reinterpret_cast<FnEntityUpdateAnimation>(updateAnimation);
            g_RealSoftwareVertexBlend =
                reinterpret_cast<FnSoftwareVertexBlend>(softwareVertexBlend);

            HMODULE ogre = GetModuleHandleA("OgreMain.dll");
            const size_t animationDirect = PatchDirectCallsInModule(
                ogre,
                updateAnimation,
                reinterpret_cast<void*>(&HookEntityUpdateAnimation),
                "Entity::_updateAnimation");
            const size_t animationIat = PatchIatEntriesByTarget(
                GetModuleHandleA(nullptr),
                updateAnimation,
                reinterpret_cast<void*>(&HookEntityUpdateAnimation),
                "Entity::_updateAnimation");
            const size_t blendDirect = PatchDirectCallsInModule(
                ogre,
                softwareVertexBlend,
                reinterpret_cast<void*>(&HookSoftwareVertexBlend),
                "Mesh::softwareVertexBlend");

            if (updateRenderQueue)
            {
                g_RealEntityUpdateRenderQueue =
                    reinterpret_cast<FnEntityUpdateRenderQueue>(updateRenderQueue);
                const size_t renderVtables = PatchEntityVtables(
                    updateRenderQueue,
                    reinterpret_cast<void*>(&HookEntityUpdateRenderQueue));
                g_RenderQueueHookInstalled.store(renderVtables != 0, std::memory_order_release);
                if (!renderVtables)
                {
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[OgreProfile] Entity::_updateRenderQueue export resolved but no matching Entity vtable slot was found; visibility-set comparison unavailable");
                }
            }

            const bool usable =
                (animationDirect + animationIat) != 0 && blendDirect != 0;
            if (!usable)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] required Ogre call sites were not found; leaving profiler fail-closed");
                return false;
            }

            g_OgreHooksInstalled.store(true, std::memory_order_release);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] Ogre observers active animationCalls=%u+%u softwareBlendCalls=%u renderQueue=%s",
                static_cast<unsigned>(animationDirect),
                static_cast<unsigned>(animationIat),
                static_cast<unsigned>(blendDirect),
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "yes" : "no");
            return true;
        }

