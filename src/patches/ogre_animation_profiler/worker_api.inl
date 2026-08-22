        unsigned __stdcall ProfilerThreadProc(void*)
        {
            QueryPerformanceFrequency(&g_QpcFrequency);
            const bool collectProfilerData =
                g_Enabled.load(std::memory_order_acquire);
            LogShimA(
                LogLevel::Info,
                kComponent,
                collectProfilerData
                    ? "[OgreProfile] enabled source=%s; observers are read-only and entry detours fail closed when retail Ogre thunks/prologues do not match"
                    : "[OgreProfile] diagnostics disabled source=%s; installing native chunk shadow policy only",
                g_ProfilerRequestSource);

            const ConfiguredRenderer configuredRenderer =
                ReadConfiguredRenderer();
            const bool observeD3D11 =
                configuredRenderer == ConfiguredRenderer::Direct3D11;
            const bool observeD3D9 =
                configuredRenderer == ConfiguredRenderer::Direct3D9;
            if (collectProfilerData)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile] configured renderer=%s; renderer-specific observers are restricted to the selected backend",
                    ConfiguredRendererName(configuredRenderer));
            }

            unsigned ogreAttempts = 0;
            bool ogreInstallFinished = false;
            bool dx11CreationAttempted = false;
            unsigned dx11ObserverAttempts = 0;
            unsigned d3d9ObserverAttempts = 0;
            ULONGLONG nextOgreAttempt = 0;
            ULONGLONG nextRendererObserverAttempt = 0;
            ULONGLONG lastReport = GetTickCount64();
            ULONGLONG nextReport = lastReport + kReportIntervalMs;

            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                const ULONGLONG loopNow = GetTickCount64();
                if (!ogreInstallFinished &&
                    !g_OgreHooksInstalled.load(std::memory_order_acquire) &&
                    OgreRuntime::IsLoaded() && loopNow >= nextOgreAttempt &&
                    ogreAttempts < 50)
                {
                    ++ogreAttempts;
                    const bool installed = InstallOgreObservers(collectProfilerData);
                    ogreInstallFinished = installed || !g_EntryInstallRetryRequested;
                    g_OgreInstallAttempted.store(true, std::memory_order_release);
                    if (collectProfilerData)
                        RefreshProfilerState("Ogre observer installation completed");
                    nextOgreAttempt = loopNow + 100;
                }

                if (collectProfilerData && observeD3D11 && !dx11CreationAttempted)
                {
                    HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
                    if (renderer)
                    {
                        dx11CreationAttempted = true;
                        g_Dx11ImportsPatched.store(
                            InstallDx11CreationObservers(renderer),
                            std::memory_order_release);
                        RefreshProfilerState("DX11 creation observer installation completed");
                    }
                }

                if (collectProfilerData && loopNow >= nextRendererObserverAttempt)
                {
                    bool retryNeeded = false;
                    if (observeD3D11 &&
                        !g_D3D11RenderSystemObserverInstalled.load(
                            std::memory_order_acquire) &&
                        dx11ObserverAttempts < 50)
                    {
                        HMODULE renderer =
                            GetModuleHandleA("RenderSystem_Direct3D11.dll");
                        if (renderer)
                        {
                            ++dx11ObserverAttempts;
                            InstallD3D11RendererSubmissionObserver(renderer);
                        }
                        retryNeeded = true;
                    }
                    if (observeD3D9 &&
                        !g_D3D9RenderSystemObserverInstalled.load(
                            std::memory_order_acquire) &&
                        d3d9ObserverAttempts < 50)
                    {
                        HMODULE renderer =
                            GetModuleHandleA("RenderSystem_Direct3D9.dll");
                        if (renderer)
                        {
                            ++d3d9ObserverAttempts;
                            InstallD3D9RendererObservers(renderer);
                        }
                        retryNeeded = true;
                    }
                    if (retryNeeded)
                        nextRendererObserverAttempt = loopNow + 100;
                }

                const ULONGLONG now = GetTickCount64();
                if (collectProfilerData && now >= nextReport)
                {
                    if (g_OgreHooksInstalled.load(std::memory_order_acquire) ||
                        g_RenderQueueHookInstalled.load(std::memory_order_acquire) ||
                        g_Dx11ContextObserved.load(std::memory_order_acquire) ||
                        g_D3D9DeviceObserved.load(std::memory_order_acquire) ||
                        g_PresentObserved.load(std::memory_order_acquire))
                        ReportAndResetInterval(now - lastReport);
                    lastReport = now;
                    nextReport = now + kReportIntervalMs;
                }
                Sleep(kPollSleepMs);
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] reporter stopped (hooks now pass-through until process exit)");
            return 0;
        }
    }

    bool IsOgreAnimationProfilerRequested()
    {
        return ProfilerRequested();
    }

    void InitializeOgreAnimationProfiler()
    {
        const bool profilerRequested = ProfilerRequested();
        const bool chunkShadowPolicyEnabled =
            !EnvironmentFlagEnabled(kDisableChunkShadowFixSwitch) &&
            !EnvironmentFlagEnabled(kLegacyDisableChunkShadowFixSwitch);
        g_ChunkShadowPolicyEnabled.store(
            chunkShadowPolicyEnabled,
            std::memory_order_release);

        if (!profilerRequested && !chunkShadowPolicyEnabled)
        {
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] disabled source=%s; native chunk shadow policy disabled by environment",
                g_ProfilerRequestSource);
            return;
        }
        if (g_WorkerThread)
            return;

        g_ShutdownRequested.store(false, std::memory_order_release);
        g_OgreInstallAttempted.store(false, std::memory_order_release);
        g_Enabled.store(profilerRequested, std::memory_order_release);
        if (profilerRequested)
            SetProfilerState(ProfilerState::WaitingForOgre, "profiler worker starting");
        g_WorkerThread = _beginthreadex(
            nullptr,
            0,
            ProfilerThreadProc,
            nullptr,
            0,
            nullptr);

        if (!g_WorkerThread)
        {
            g_Enabled.store(false, std::memory_order_release);
            LogShimA(
                LogLevel::Warn,
                kComponent,
                "[OgreProfile] failed to start profiler worker (err=%lu)",
                GetLastError());
        }
    }

    void ShutdownOgreAnimationProfiler()
    {
        g_ChunkShadowPolicyEnabled.store(false, std::memory_order_release);
        g_Enabled.store(false, std::memory_order_release);
        g_ShutdownRequested.store(true, std::memory_order_release);
        SetProfilerState(ProfilerState::Disabled, "shutdown requested");

        if (g_WorkerThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_WorkerThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_WorkerThread));
            g_WorkerThread = 0;
        }
    }

    bool IsOgreAnimationProfilerCollecting() noexcept
    {
        return g_Enabled.load(std::memory_order_relaxed);
    }

    void RecordNativeChunkSimulationSample(
        uint32_t activeChunks,
        uint64_t elapsedQpcTicks) noexcept
    {
        if (!g_Enabled.load(std::memory_order_relaxed))
            return;
        g_NativeChunkSimCalls.fetch_add(1, std::memory_order_relaxed);
        g_NativeChunkSimTicks.fetch_add(elapsedQpcTicks, std::memory_order_relaxed);
        g_NativeChunkActiveTotal.fetch_add(activeChunks, std::memory_order_relaxed);
        AtomicMax(g_NativeChunkActiveMax, activeChunks);
    }

    void RecordNativeDynamicGeometryPrepareSample(
        const void* objectIdentity,
        bool rebuilt,
        uint64_t elapsedQpcTicks) noexcept
    {
        if (!g_Enabled.load(std::memory_order_relaxed))
            return;
        g_DynamicGeometryPrepareCalls.fetch_add(1, std::memory_order_relaxed);
        g_DynamicGeometryPrepareTicks.fetch_add(elapsedQpcTicks, std::memory_order_relaxed);
        AtomicMax(g_DynamicGeometryPrepareMaxTicks, elapsedQpcTicks);
        DynamicGeometryProfileSlot* slot =
            FindOrClaimDynamicGeometrySlot(objectIdentity);
        if (slot)
        {
            slot->prepareCalls.fetch_add(1, std::memory_order_relaxed);
            slot->prepareTicks.fetch_add(elapsedQpcTicks, std::memory_order_relaxed);
        }
        if (rebuilt)
        {
            g_DynamicGeometryRebuilds.fetch_add(1, std::memory_order_relaxed);
            if (slot)
                slot->rebuilds.fetch_add(1, std::memory_order_relaxed);
        }
    }

    void RecordNativeDynamicGeometryQueueSample(
        const void* objectIdentity,
        uint32_t batchCount,
        uint32_t mergeableBatchCount,
        uint32_t blendedBatchCount,
        uint32_t distinctMaterialCount,
        uint64_t vertexCount,
        uint64_t indexCount) noexcept
    {
        if (!g_Enabled.load(std::memory_order_relaxed))
            return;
        g_DynamicGeometryQueueCalls.fetch_add(1, std::memory_order_relaxed);
        g_DynamicGeometryBatchTotal.fetch_add(batchCount, std::memory_order_relaxed);
        AtomicMax(g_DynamicGeometryBatchMax, batchCount);
        g_DynamicGeometryMergeableBatchTotal.fetch_add(
            mergeableBatchCount, std::memory_order_relaxed);
        g_DynamicGeometryBlendedBatchTotal.fetch_add(
            blendedBatchCount, std::memory_order_relaxed);
        g_DynamicGeometryDistinctMaterialTotal.fetch_add(
            distinctMaterialCount, std::memory_order_relaxed);
        g_DynamicGeometryVertexTotal.fetch_add(
            vertexCount, std::memory_order_relaxed);
        g_DynamicGeometryIndexTotal.fetch_add(
            indexCount, std::memory_order_relaxed);
        DynamicGeometryProfileSlot* slot =
            FindOrClaimDynamicGeometrySlot(objectIdentity);
        if (slot)
        {
            slot->queueCalls.fetch_add(1, std::memory_order_relaxed);
            slot->batches.fetch_add(batchCount, std::memory_order_relaxed);
            AtomicMax(slot->batchMax, batchCount);
        }
    }

    void RecordNativeDynamicGeometryMaterialSample(
        const void* materialIdentity,
        uint32_t batchCount,
        uint32_t blendedBatchCount) noexcept
    {
        if (!g_Enabled.load(std::memory_order_relaxed))
            return;
        DynamicMaterialProfileSlot* slot =
            FindOrClaimDynamicMaterialSlot(materialIdentity);
        if (!slot)
            return;
        CaptureDynamicMaterialMetadata(slot, materialIdentity);
        slot->batches.fetch_add(batchCount, std::memory_order_relaxed);
        slot->blendedBatches.fetch_add(
            blendedBatchCount, std::memory_order_relaxed);
    }
}
