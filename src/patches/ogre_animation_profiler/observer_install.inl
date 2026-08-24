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

        bool InstallD3D11RendererSubmissionObserver(HMODULE renderer)
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
                g_D3D11RenderSystemObserverInstalled.store(
                    true, std::memory_order_release);
                g_RenderSystemObserverInstalled.store(true, std::memory_order_release);
            }
            return installed;
        }

        bool InstallOgreObservers(bool installProfilerObservers)
        {
            g_EntryInstallRetryRequested = false;
            if (!OgreRuntime::IsLoaded())
                return false;

            const HMODULE ogreModule = GetModuleHandleA("OgreMain.dll");
            g_OgreGetEntityName = reinterpret_cast<FnOgreStringQuery>(GetProcAddress(
                ogreModule,
                "?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
            g_OgreEntityGetMesh = reinterpret_cast<FnEntityGetMesh>(GetProcAddress(
                ogreModule,
                 "?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ"));
            g_OgreSubEntityGetParent = reinterpret_cast<FnSubEntityGetParent>(
                GetProcAddress(
                    ogreModule,
                    "?getParent@SubEntity@Ogre@@QBEPAVEntity@2@XZ"));
            g_OgrePassGetParent = reinterpret_cast<FnPassGetParent>(GetProcAddress(
                ogreModule,
                "?getParent@Pass@Ogre@@QBEPAVTechnique@2@XZ"));
            g_OgreTechniqueGetParent = reinterpret_cast<FnTechniqueGetParent>(
                GetProcAddress(
                    ogreModule,
                    "?getParent@Technique@Ogre@@QBEPAVMaterial@2@XZ"));
            g_OgrePassGetIndex = reinterpret_cast<FnPassGetIndex>(GetProcAddress(
                ogreModule,
                "?getIndex@Pass@Ogre@@QBEGXZ"));
            g_OgreTechniqueGetName = reinterpret_cast<FnOgreStringQuery>(
                GetProcAddress(
                    ogreModule,
                    "?getName@Technique@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
            g_OgreTechniqueGetSchemeName = reinterpret_cast<FnOgreStringQuery>(
                GetProcAddress(
                    ogreModule,
                    "?getSchemeName@Technique@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
            g_OgreTechniqueGetLodIndex =
                reinterpret_cast<FnTechniqueGetLodIndex>(GetProcAddress(
                    ogreModule,
                    "?getLodIndex@Technique@Ogre@@QBEGXZ"));
            g_OgrePassGetName = reinterpret_cast<FnOgreStringQuery>(GetProcAddress(
                ogreModule,
                "?getName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
            const auto subEntityVtables = FindExportsContaining(
                "??_7SubEntity@Ogre@@");
            g_OgreSubEntityVtable = subEntityVtables.size() == 1
                ? subEntityVtables[0].address
                : nullptr;
            g_OgreGetResourceName = reinterpret_cast<FnOgreStringQuery>(GetProcAddress(
                ogreModule,
                "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
            g_OgreGetCastShadows = reinterpret_cast<FnMovableGetCastShadows>(GetProcAddress(
                ogreModule,
                "?getCastShadows@MovableObject@Ogre@@UBE_NXZ"));
            g_OgreSetCastShadows = reinterpret_cast<FnMovableSetCastShadows>(GetProcAddress(
                ogreModule,
                "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z"));
            g_OgreVertexElementGetSource =
                reinterpret_cast<FnVertexElementGetSource>(GetProcAddress(
                    ogreModule,
                    "?getSource@VertexElement@Ogre@@QBEGXZ"));
            g_OgreVertexElementGetType =
                reinterpret_cast<FnVertexElementGetType>(GetProcAddress(
                    ogreModule,
                    "?getType@VertexElement@Ogre@@QBE?AW4VertexElementType@2@XZ"));
            g_OgreVertexElementGetTypeCount =
                reinterpret_cast<FnVertexElementGetTypeCount>(GetProcAddress(
                    ogreModule,
                    "?getTypeCount@VertexElement@Ogre@@SAGW4VertexElementType@2@@Z"));
            g_OgreVertexBufferGetVertexSize =
                reinterpret_cast<FnHardwareVertexBufferGetVertexSize>(GetProcAddress(
                    ogreModule,
                    "?getVertexSize@HardwareVertexBuffer@Ogre@@QBEIXZ"));
            g_OgreHardwareBufferGetSizeInBytes =
                reinterpret_cast<FnHardwareBufferGetSizeInBytes>(GetProcAddress(
                    ogreModule,
                    "?getSizeInBytes@HardwareBuffer@Ogre@@QBEIXZ"));
            g_OgreHardwareBufferGetUsage =
                reinterpret_cast<FnHardwareBufferGetUsage>(GetProcAddress(
                    ogreModule,
                    "?getUsage@HardwareBuffer@Ogre@@QBE?AW4Usage@12@XZ"));
            g_OgreHardwareBufferHasShadow =
                reinterpret_cast<FnHardwareBufferBoolQuery>(GetProcAddress(
                    ogreModule,
                    "?hasShadowBuffer@HardwareBuffer@Ogre@@QBE_NXZ"));
            g_OgreHardwareBufferIsSystemMemory =
                reinterpret_cast<FnHardwareBufferBoolQuery>(GetProcAddress(
                    ogreModule,
                    "?isSystemMemory@HardwareBuffer@Ogre@@QBE_NXZ"));
            g_OgreHardwareBufferManagerGetSingletonPtr =
                reinterpret_cast<FnHardwareBufferManagerGetSingletonPtr>(
                    GetProcAddress(
                        ogreModule,
                        "?getSingletonPtr@HardwareBufferManager@Ogre@@SAPAV12@XZ"));
            g_OgreHardwareBufferManagerCreateVertexBuffer =
                reinterpret_cast<FnHardwareBufferManagerCreateVertexBuffer>(
                    GetProcAddress(
                        ogreModule,
                        "?createVertexBuffer@HardwareBufferManager@Ogre@@UAE?AVHardwareVertexBufferSharedPtr@2@IIW4Usage@HardwareBuffer@2@_N@Z"));
            g_OgreHardwareBufferLock = reinterpret_cast<FnHardwareBufferLock>(
                GetProcAddress(
                    ogreModule,
                    "?lock@HardwareBuffer@Ogre@@QAEPAXW4LockOptions@12@W4UploadOptions@12@@Z"));
            g_OgreHardwareBufferUnlock =
                reinterpret_cast<FnHardwareBufferUnlock>(GetProcAddress(
                    ogreModule,
                    "?unlock@HardwareBuffer@Ogre@@UAEXXZ"));
            g_OgreVertexBufferBindingSetBinding =
                reinterpret_cast<FnVertexBufferBindingSetBinding>(GetProcAddress(
                    ogreModule,
                    "?setBinding@VertexBufferBinding@Ogre@@UAEXGABVHardwareVertexBufferSharedPtr@2@@Z"));
            g_OgreHardwareVertexBufferSharedPtrDestructor =
                reinterpret_cast<FnHardwareVertexBufferSharedPtrDestructor>(
                    GetProcAddress(
                        ogreModule,
                        "??1HardwareVertexBufferSharedPtr@Ogre@@QAE@XZ"));
            LogShimA(
                (g_OgreGetEntityName && g_OgreEntityGetMesh &&
                 g_OgreGetResourceName && g_OgreGetCastShadows &&
                 g_OgreSetCastShadows)
                    ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[OgreProfile] Entity metadata observers name=%s mesh=%s resourceName=%s getCastShadows=%s setCastShadows=%s",
                g_OgreGetEntityName ? "yes" : "no",
                g_OgreEntityGetMesh ? "yes" : "no",
                g_OgreGetResourceName ? "yes" : "no",
                g_OgreGetCastShadows ? "yes" : "no",
                g_OgreSetCastShadows ? "yes" : "no");

            const bool validatedChunkShadowRuntime =
                IsValidatedGogChunkShadowRuntime(ogreModule);
            if (g_ChunkShadowPolicyEnabled.load(std::memory_order_acquire) &&
                !validatedChunkShadowRuntime)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][ChunkShadowPolicy] unavailable: executable/Ogre PE identity is not the validated GOG 2.2.301 runtime");
            }

            if (g_ChunkShadowPolicyEnabled.load(std::memory_order_acquire) &&
                validatedChunkShadowRuntime &&
                g_OgreGetCastShadows && g_OgreEntityGetMesh &&
                g_OgreGetResourceName && g_OgreSetCastShadows &&
                !g_ChunkShadowHookInstalled.load(std::memory_order_acquire))
            {
                const size_t shadowVtables = PatchEntityVtables(
                    reinterpret_cast<void*>(g_OgreGetCastShadows),
                    reinterpret_cast<void*>(&HookEntityGetCastShadows),
                    "native-chunk shadow policy");
                g_ChunkShadowHookInstalled.store(
                    shadowVtables != 0,
                    std::memory_order_release);
                LogShimA(
                    shadowVtables ? LogLevel::Info : LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][ChunkShadowPolicy] %s exactMeshes=chunk1/chunk1.mesh,chunk2/chunk2.mesh patchedVtables=%u",
                    shadowVtables ? "active" : "unavailable",
                    static_cast<unsigned>(shadowVtables));
            }

            const bool skinSourcePolicyRequested =
                g_Dx11SkinSourceShadowPolicyEnabled.load(
                    std::memory_order_acquire);
            const bool skinSourcePolicyAvailable =
                skinSourcePolicyRequested && validatedChunkShadowRuntime &&
                g_OgreVertexElementGetSource &&
                g_OgreVertexBufferGetVertexSize &&
                g_OgreHardwareBufferGetSizeInBytes &&
                g_OgreHardwareBufferGetUsage &&
                g_OgreHardwareBufferHasShadow &&
                g_OgreHardwareBufferManagerGetSingletonPtr &&
                g_OgreHardwareBufferManagerCreateVertexBuffer &&
                g_OgreHardwareBufferLock && g_OgreHardwareBufferUnlock &&
                g_OgreVertexBufferBindingSetBinding &&
                g_OgreHardwareVertexBufferSharedPtrDestructor;
            if (skinSourcePolicyRequested && !skinSourcePolicyAvailable)
            {
                g_Dx11SkinSourceShadowPolicyEnabled.store(
                    false, std::memory_order_release);
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][DX11SkinSourceShadow] unavailable: validated GOG 2.2.301 runtime or required Ogre buffer exports missing");
            }

            void* softwareVertexBlend =
                (installProfilerObservers || skinSourcePolicyAvailable)
                    ? FindUniqueFunctionExport(
                          "softwareVertexBlend@Mesh@Ogre@@",
                          "Mesh::softwareVertexBlend")
                    : nullptr;
            void* softwareVertexBlendImplementation = softwareVertexBlend
                ? (g_SoftwareVertexBlendDetour.trampoline
                       ? g_SoftwareVertexBlendDetour.target
                       : ResolveOgreExportImplementation(
                             softwareVertexBlend,
                             "Mesh::softwareVertexBlend"))
                : nullptr;
            static const uint8_t kSoftwareVertexBlendPrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x6A, 0xFF                    // push -1
            };
            const bool blendEntry = softwareVertexBlendImplementation &&
                (g_SoftwareVertexBlendDetour.trampoline ||
                 InstallEntryDetour32(
                     g_SoftwareVertexBlendDetour,
                     ogreModule,
                     softwareVertexBlendImplementation,
                     reinterpret_cast<void*>(&HookSoftwareVertexBlend),
                     kSoftwareVertexBlendPrologue,
                     sizeof(kSoftwareVertexBlendPrologue),
                     "Mesh::softwareVertexBlend"));
            if (blendEntry)
            {
                g_RealSoftwareVertexBlend = reinterpret_cast<FnSoftwareVertexBlend>(
                    g_SoftwareVertexBlendDetour.trampoline);
            }
            if (skinSourcePolicyAvailable)
            {
                g_Dx11SkinSourceShadowHookInstalled.store(
                    blendEntry, std::memory_order_release);
                LogShimA(
                    (blendEntry || g_EntryInstallRetryRequested)
                        ? LogLevel::Info : LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][DX11SkinSourceShadow] %s exactRuntime=GOG-2.2.301 scope=software-skinned-position-normal-sources",
                    blendEntry ? "active" :
                        (g_EntryInstallRetryRequested ? "deferred" : "unavailable"));
            }

            if (!installProfilerObservers)
            {
                if (skinSourcePolicyAvailable && !blendEntry)
                    return false;
                return g_ChunkShadowHookInstalled.load(std::memory_order_acquire) ||
                    g_Dx11SkinSourceShadowHookInstalled.load(
                        std::memory_order_acquire);
            }

            void* updateAnimation = FindUniqueFunctionExport(
                "_updateAnimation@Entity@Ogre@@",
                "Entity::_updateAnimation");
            void* updateAnimationCore = FindUniqueFunctionExport(
                "?updateAnimation@Entity@Ogre@@",
                "Entity::updateAnimation core");
            void* updateRenderQueue = FindUniqueFunctionExport(
                "_updateRenderQueue@Entity@Ogre@@",
                "Entity::_updateRenderQueue");
            void* renderScene = FindUniqueFunctionExport(
                "_renderScene@SceneManager@Ogre@@",
                "SceneManager::_renderScene");
            void* renderSingleObject = FindUniqueFunctionExport(
                "?renderSingleObject@SceneManager@Ogre@@",
                "SceneManager::renderSingleObject");

            if (!updateAnimation || !updateAnimationCore || !blendEntry)
                return false;

            void* updateAnimationImplementation = g_EntityUpdateAnimationDetour.trampoline
                ? g_EntityUpdateAnimationDetour.target
                : ResolveOgreExportImplementation(
                    updateAnimation,
                    "Entity::_updateAnimation");
            void* updateAnimationCoreImplementation = g_EntityUpdateAnimationCoreDetour.trampoline
                ? g_EntityUpdateAnimationCoreDetour.target
                : ResolveOgreExportImplementation(
                    updateAnimationCore,
                    "Entity::updateAnimation core");
            void* renderSceneImplementation = g_SceneManagerRenderSceneDetour.trampoline
                ? g_SceneManagerRenderSceneDetour.target
                : ResolveOgreExportImplementation(
                    renderScene,
                    "SceneManager::_renderScene");
            void* renderSingleObjectImplementation =
                g_SceneManagerRenderSingleObjectDetour.trampoline
                    ? g_SceneManagerRenderSingleObjectDetour.target
                    : ResolveOgreExportImplementation(
                        renderSingleObject,
                        "SceneManager::renderSingleObject");
            if (!updateAnimationImplementation || !updateAnimationCoreImplementation)
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
            static const uint8_t kUpdateAnimationCorePrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x81, 0xEC, 0x24, 0x04, 0x00, 0x00 // sub esp, 424h
            };
            static const uint8_t kRenderScenePrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x6A, 0xFF                    // push -1
            };
            static const uint8_t kRenderSingleObjectPrologue[] =
            {
                0x55,                         // push ebp
                0x8B, 0xEC,                   // mov ebp, esp
                0x6A, 0xFF                    // push -1
            };

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

            const bool renderSceneEntry = renderSceneImplementation &&
                (g_SceneManagerRenderSceneDetour.trampoline ||
                 InstallEntryDetour32(
                    g_SceneManagerRenderSceneDetour,
                    ogreModule,
                    renderSceneImplementation,
                    reinterpret_cast<void*>(&HookSceneManagerRenderScene),
                    kRenderScenePrologue,
                    sizeof(kRenderScenePrologue),
                    "SceneManager::_renderScene"));
            if (renderSceneEntry)
            {
                g_RealSceneManagerRenderScene =
                    reinterpret_cast<FnSceneManagerRenderScene>(
                        g_SceneManagerRenderSceneDetour.trampoline);
            }

            const bool renderSingleObjectEntry = renderSingleObjectImplementation &&
                (g_SceneManagerRenderSingleObjectDetour.trampoline ||
                 InstallEntryDetour32(
                    g_SceneManagerRenderSingleObjectDetour,
                    ogreModule,
                    renderSingleObjectImplementation,
                    reinterpret_cast<void*>(&HookSceneManagerRenderSingleObject),
                    kRenderSingleObjectPrologue,
                    sizeof(kRenderSingleObjectPrologue),
                    "SceneManager::renderSingleObject"));
            if (renderSingleObjectEntry)
            {
                g_RealSceneManagerRenderSingleObject =
                    reinterpret_cast<FnSceneManagerRenderSingleObject>(
                        g_SceneManagerRenderSingleObjectDetour.trampoline);
            }
            g_RenderSingleObjectHookInstalled.store(
                renderSingleObjectEntry, std::memory_order_release);

            if (updateRenderQueue &&
                !g_RenderQueueHookInstalled.load(std::memory_order_acquire))
            {
                g_RealEntityUpdateRenderQueue =
                    reinterpret_cast<FnEntityUpdateRenderQueue>(updateRenderQueue);
                const size_t renderVtables = PatchEntityVtables(
                    updateRenderQueue,
                    reinterpret_cast<void*>(&HookEntityUpdateRenderQueue),
                    "render-queue observer");
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
                "[OgreProfile] Ogre observers active animationWrapperEntry=%s animationCoreEntry=%s softwareBlendEntry=%s renderQueue=%s sceneRender=%s renderSingleObject=%s",
                animationEntry ? "yes" : "no",
                animationCoreEntry ? "yes" : "no",
                blendEntry ? "yes" : "no",
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "yes" : "no",
                renderSceneEntry ? "yes" : "no",
                renderSingleObjectEntry ? "yes" : "no");
            return true;
        }

