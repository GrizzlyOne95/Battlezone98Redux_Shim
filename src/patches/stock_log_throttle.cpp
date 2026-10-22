#include "BZROpenShim.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "openshim_env_config.h"
#include "patcher.h"
#include "shim_log.h"
#include <Windows.h>
#include <cstdint>

// The stock BZLogger.txt stream is unitbuf and every line also calls
// ostream::flush, so each line is one synchronous WriteFile on the game
// thread. LinkCopy (GAS, the sound layer) takes one of 100 playing-sound
// copies; in a big fight the pool runs dry and every sound that cannot start
// logs "LinkCopy out of copies": 36k lines in a 60 s 80-craft firing run,
// and 46-69 ms frames blocked in WriteFile. The sound is dropped either way;
// gas_copy_pool.cpp enlarges the pool, and this rate-limits the two LinkCopy
// log calls for whatever still runs it dry: the first line is logged as
// before, later ones as one count every 10 s.
// OPENSHIM_STOCK_LOG_UNTHROTTLED=1 leaves the stock behaviour alone.
namespace BZROpenShim::Hooks
{
    namespace
    {
        using FnLogger = void(__cdecl*)(const char* fmt, ...);

        constexpr ULONGLONG kRateLimitReportMs = 10000;

        uint32_t g_LoggerAddr = 0;
        uint32_t g_OutOfCopiesCallAddr = 0;
        uint32_t g_NullGoCallAddr = 0;

        bool g_Installed = false;

        struct RateLimitedLine
        {
            const char* label;
            volatile LONG pending;
            volatile LONG64 lastReportMs;
        };
        RateLimitedLine g_OutOfCopiesLine = { "LinkCopy out of copies", 0, 0 };
        RateLimitedLine g_NullGoLine = { "LinkCopy with NULL go", 0, 0 };

        void ReportRateLimited(RateLimitedLine& line, const char* fmt)
        {
            InterlockedIncrement(&line.pending);
            const ULONGLONG now = GetTickCount64();
            const LONG64 last = line.lastReportMs;
            if (last != 0 && now - static_cast<ULONGLONG>(last) < kRateLimitReportMs)
                return;
            if (InterlockedCompareExchange64(&line.lastReportMs, static_cast<LONG64>(now), last) != last)
                return;
            const LONG count = InterlockedExchange(&line.pending, 0);
            const FnLogger logger = reinterpret_cast<FnLogger>(g_LoggerAddr);
            if (last == 0)
                logger(fmt);
            else
                logger("%s x%ld in the last %llus (OpenShim rate-limits this line)\n",
                       line.label, count, (now - static_cast<ULONGLONG>(last)) / 1000);
        }

        void __cdecl LinkCopyOutOfCopiesLogHook(const char* fmt)
        {
            ReportRateLimited(g_OutOfCopiesLine, fmt);
        }

        void __cdecl LinkCopyNullGoLogHook(const char* fmt)
        {
            ReportRateLimited(g_NullGoLine, fmt);
        }
    }

    void InstallStockLogThrottleIfPossible()
    {
        if (g_Installed)
            return;
        if (EnvFlagEnabled("OPENSHIM_STOCK_LOG_UNTHROTTLED"))
        {
            g_Installed = true;
            Log(L"[STOCKLOG] Stock log throttle disabled by OPENSHIM_STOCK_LOG_UNTHROTTLED\n");
            return;
        }
        static const bool s_bound = [] {
            const HookEngine::EngineRow rows[] = {
                { "BzrNetLogger", &g_LoggerAddr },
                { "LinkCopyOutOfCopiesLogCall", &g_OutOfCopiesCallAddr },
                { "LinkCopyNullGoLogCall", &g_NullGoCallAddr },
            };
            return HookEngine::BindEngineRows("Stock log throttle", rows);
        }();
        g_Installed = true;
        if (!s_bound)
            return;

        const bool outOfCopies = RedirectCallTarget(
            g_OutOfCopiesCallAddr, g_LoggerAddr,
            reinterpret_cast<uintptr_t>(&LinkCopyOutOfCopiesLogHook));
        const bool nullGo = RedirectCallTarget(
            g_NullGoCallAddr, g_LoggerAddr,
            reinterpret_cast<uintptr_t>(&LinkCopyNullGoLogHook));
        Log(L"[STOCKLOG] Stock log throttle: linkcopy=%hs/%hs\n",
            outOfCopies ? "ok" : "mismatch", nullGo ? "ok" : "mismatch");
    }
}
