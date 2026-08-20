        unsigned __stdcall ProfilerThreadProc(void*)
        {
            QueryPerformanceFrequency(&g_QpcFrequency);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] enabled source=%s; observers are read-only and fail closed when retail Ogre exports/call sites do not match",
                g_ProfilerRequestSource);

            bool ogreAttempted = false;
            bool dx11Attempted = false;
            ULONGLONG lastReport = GetTickCount64();
            ULONGLONG nextReport = lastReport + kReportIntervalMs;

            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                if (!ogreAttempted && OgreRuntime::IsLoaded())
                {
                    ogreAttempted = true;
                    InstallOgreObservers();
                }

                if (!dx11Attempted)
                {
                    HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
                    if (renderer)
                    {
                        dx11Attempted = true;
                        g_Dx11ImportsPatched.store(
                            InstallDx11CreationObservers(renderer),
                            std::memory_order_release);
                    }
                }

                const ULONGLONG now = GetTickCount64();
                if (now >= nextReport)
                {
                    if (g_OgreHooksInstalled.load(std::memory_order_acquire))
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
        g_Enabled.store(true, std::memory_order_release);
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

        if (g_WorkerThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_WorkerThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_WorkerThread));
            g_WorkerThread = 0;
        }
    }
}
