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

        bool InstallRendererSubmissionObserver(HMODULE renderer)
        {
            if (!renderer)
                return false;
            if (g_D3D11RenderSystemRenderDetour.trampoline)
                return true;

            constexpr char kRenderExport[] =
                "?_render@D3D11RenderSystem@Ogre@@UAEXABVRenderOperation@2@@Z";
            constexpr char kGetDeviceExport[] =
                "?_getDevice@D3D11RenderSystem@Ogre@@QAEAAVD3D11Device@2@XZ";
            constexpr char kGetImmediateContextExport[] =
                "?GetImmediateContext@D3D11Device@Ogre@@QAEPAUID3D11DeviceContext@@XZ";
            void* exportAddress = reinterpret_cast<void*>(
                GetProcAddress(renderer, kRenderExport));
            g_D3D11RenderSystemGetDevice =
                reinterpret_cast<FnD3D11RenderSystemGetDevice>(
                    GetProcAddress(renderer, kGetDeviceExport));
            g_OgreD3D11DeviceGetImmediateContext =
                reinterpret_cast<FnOgreD3D11DeviceGetImmediateContext>(
                    GetProcAddress(renderer, kGetImmediateContextExport));
            if (!exportAddress || !g_D3D11RenderSystemGetDevice ||
                !g_OgreD3D11DeviceGetImmediateContext)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] required renderer exports missing render=%s getDevice=%s getImmediateContext=%s; renderer submission cross-check unavailable",
                    exportAddress ? "yes" : "no",
                    g_D3D11RenderSystemGetDevice ? "yes" : "no",
                    g_OgreD3D11DeviceGetImmediateContext ? "yes" : "no");
                return false;
            }

            void* implementation = ResolveModuleExportImplementation(
                renderer,
                exportAddress,
                "D3D11RenderSystem::_render");
            if (!implementation)
                return false;

            // Retail GOG RenderSystem_Direct3D11.dll SHA-256
            // 78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0.
            // Complete instruction-aligned prefix: push ebp; mov ebp,esp; push -1.
            static const uint8_t kRenderPrologue[] =
            {
                0x55,
                0x8B, 0xEC,
                0x6A, 0xFF
            };
            const bool installed = InstallEntryDetour32(
                g_D3D11RenderSystemRenderDetour,
                renderer,
                implementation,
                reinterpret_cast<void*>(&HookD3D11RenderSystemRender),
                kRenderPrologue,
                sizeof(kRenderPrologue),
                "D3D11RenderSystem::_render");
            if (installed)
            {
                g_RealD3D11RenderSystemRender =
                    reinterpret_cast<FnD3D11RenderSystemRender>(
                        g_D3D11RenderSystemRenderDetour.trampoline);
                g_RenderSystemObserverInstalled.store(true, std::memory_order_release);
            }
            return installed;
        }

        bool InstallOgreObservers()
        {
            g_EntryInstallRetryRequested = false;
            if (!OgreRuntime::IsLoaded())
                return false;

            void* updateAnimation = FindUniqueFunctionExport(
                "_updateAnimation@Entity@Ogre@@",
                "Entity::_updateAnimation");
            void* softwareVertexBlend = FindUniqueFunctionExport(
                "softwareVertexBlend@Mesh@Ogre@@",
                "Mesh::softwareVertexBlend");
            void* updateAnimationCore = FindUniqueFunctionExport(
                "?updateAnimation@Entity@Ogre@@",
                "Entity::updateAnimation core");
            void* updateRenderQueue = FindUniqueFunctionExport(
                "_updateRenderQueue@Entity@Ogre@@",
                "Entity::_updateRenderQueue");

            if (!updateAnimation || !updateAnimationCore || !softwareVertexBlend)
                return false;

            void* updateAnimationImplementation = g_EntityUpdateAnimationDetour.trampoline
                ? g_EntityUpdateAnimationDetour.target
                : ResolveOgreExportImplementation(
                    updateAnimation,
                    "Entity::_updateAnimation");
            void* softwareVertexBlendImplementation = g_SoftwareVertexBlendDetour.trampoline
                ? g_SoftwareVertexBlendDetour.target
                : ResolveOgreExportImplementation(
                    softwareVertexBlend,
                    "Mesh::softwareVertexBlend");
            void* updateAnimationCoreImplementation = g_EntityUpdateAnimationCoreDetour.trampoline
                ? g_EntityUpdateAnimationCoreDetour.target
                : ResolveOgreExportImplementation(
                    updateAnimationCore,
                    "Entity::updateAnimation core");
            if (!updateAnimationImplementation || !updateAnimationCoreImplementation ||
                !softwareVertexBlendImplementation)
                return false;

            // GOG OgreMain.dll SHA-256
            // E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45.
            // These are complete instruction-aligned entry sequences. Unknown
            // prologues fail closed instead of guessing an overwrite length.
            static const uint8_t kUpdateAnimationPrologue[] =
            {
                0x56,                         // push esi
                0x8B, 0xF1,                   // mov esi, ecx
                0x83, 0xBE, 0xBC, 0x01, 0x00, 0x00, 0x00 // cmp [esi+1BCh], 0
            };
            static const uint8_t kSoftwareVertexBlendPrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x6A, 0xFF                    // push -1
            };
            static const uint8_t kUpdateAnimationCorePrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x81, 0xEC, 0x24, 0x04, 0x00, 0x00 // sub esp, 424h
            };

            const HMODULE ogreModule = GetModuleHandleA("OgreMain.dll");
            const bool animationEntry = g_EntityUpdateAnimationDetour.trampoline ||
                InstallEntryDetour32(
                    g_EntityUpdateAnimationDetour,
                    ogreModule,
                    updateAnimationImplementation,
                    reinterpret_cast<void*>(&HookEntityUpdateAnimation),
                    kUpdateAnimationPrologue,
                    sizeof(kUpdateAnimationPrologue),
                    "Entity::_updateAnimation");
            if (animationEntry)
            {
                g_RealEntityUpdateAnimation = reinterpret_cast<FnEntityUpdateAnimation>(
                    g_EntityUpdateAnimationDetour.trampoline);
            }

            const bool animationCoreEntry = g_EntityUpdateAnimationCoreDetour.trampoline ||
                InstallEntryDetour32(
                    g_EntityUpdateAnimationCoreDetour,
                    ogreModule,
                    updateAnimationCoreImplementation,
                    reinterpret_cast<void*>(&HookEntityUpdateAnimationCore),
                    kUpdateAnimationCorePrologue,
                    sizeof(kUpdateAnimationCorePrologue),
                    "Entity::updateAnimation core");
            if (animationCoreEntry)
            {
                g_RealEntityUpdateAnimationCore = reinterpret_cast<FnEntityUpdateAnimation>(
                    g_EntityUpdateAnimationCoreDetour.trampoline);
            }

            const bool blendEntry = g_SoftwareVertexBlendDetour.trampoline ||
                InstallEntryDetour32(
                    g_SoftwareVertexBlendDetour,
                    ogreModule,
                    softwareVertexBlendImplementation,
                    reinterpret_cast<void*>(&HookSoftwareVertexBlend),
                    kSoftwareVertexBlendPrologue,
                    sizeof(kSoftwareVertexBlendPrologue),
                    "Mesh::softwareVertexBlend");
            if (blendEntry)
            {
                g_RealSoftwareVertexBlend = reinterpret_cast<FnSoftwareVertexBlend>(
                    g_SoftwareVertexBlendDetour.trampoline);
            }

            if (updateRenderQueue &&
                !g_RenderQueueHookInstalled.load(std::memory_order_acquire))
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

            const bool usable = animationEntry && animationCoreEntry && blendEntry;
            if (!usable)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] required Ogre entry observers were not installed animationWrapper=%s animationCore=%s softwareBlend=%s; partial observers remain explicitly classified",
                    animationEntry ? "active" : "unavailable",
                    animationCoreEntry ? "active" : "unavailable",
                    blendEntry ? "active" : "unavailable");
                return false;
            }

            g_OgreHooksInstalled.store(true, std::memory_order_release);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] Ogre observers active animationWrapperEntry=%s animationCoreEntry=%s softwareBlendEntry=%s renderQueue=%s",
                animationEntry ? "yes" : "no",
                animationCoreEntry ? "yes" : "no",
                blendEntry ? "yes" : "no",
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "yes" : "no");
            return true;
        }

