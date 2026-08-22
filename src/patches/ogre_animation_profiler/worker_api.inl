        unsigned __stdcall ProfilerThreadProc(void*)
        {
            QueryPerformanceFrequency(&g_QpcFrequency);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] enabled source=%s; observers are read-only and entry detours fail closed when retail Ogre thunks/prologues do not match",
                g_ProfilerRequestSource);

            unsigned ogreAttempts = 0;
            bool ogreInstallFinished = false;
            bool dx11Attempted = false;
            unsigned rendererObserverAttempts = 0;
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
                    const bool installed = InstallOgreObservers();
                    ogreInstallFinished = installed || !g_EntryInstallRetryRequested;
                    g_OgreInstallAttempted.store(true, std::memory_order_release);
                    RefreshProfilerState("Ogre observer installation completed");
                    nextOgreAttempt = loopNow + 100;
                }

                if (!dx11Attempted)
                {
                    HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
                    if (renderer)
                    {
                        if (!g_RenderSystemObserverInstalled.load(std::memory_order_acquire))
                        {
                            ++rendererObserverAttempts;
                            InstallRendererSubmissionObserver(renderer);
                            nextRendererObserverAttempt = loopNow + 100;
                        }
                        dx11Attempted = true;
                        g_Dx11ImportsPatched.store(
                            InstallDx11CreationObservers(renderer),
                            std::memory_order_release);
                        RefreshProfilerState("DX11 creation observer installation completed");
                    }
                }

                if (dx11Attempted &&
                    !g_RenderSystemObserverInstalled.load(std::memory_order_acquire) &&
                    loopNow >= nextRendererObserverAttempt &&
                    rendererObserverAttempts < 50)
                {
                    HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
                    if (renderer)
                    {
                        ++rendererObserverAttempts;
                        InstallRendererSubmissionObserver(renderer);
                        nextRendererObserverAttempt = loopNow + 100;
                    }
                }

                const ULONGLONG now = GetTickCount64();
                if (now >= nextReport)
                {
                    if (g_OgreHooksInstalled.load(std::memory_order_acquire) ||
                        g_RenderQueueHookInstalled.load(std::memory_order_acquire) ||
                        g_Dx11ContextObserved.load(std::memory_order_acquire) ||
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
        if (!ProfilerRequested())
        {
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] disabled source=%s",
                g_ProfilerRequestSource);
            return;
        }
        if (g_WorkerThread)
            return;

        g_ShutdownRequested.store(false, std::memory_order_release);
        g_OgreInstallAttempted.store(false, std::memory_order_release);
        g_Enabled.store(true, std::memory_order_release);
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
}
