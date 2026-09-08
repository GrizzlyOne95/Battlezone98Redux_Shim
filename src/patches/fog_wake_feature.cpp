#include "fog_wake_feature.h"

#include "bzr_options_ui.h"
#include "fog_wake_runtime.h"
#include "shim_log.h"

#include <atomic>
#include <chrono>
#include <cmath>

namespace BZROpenShim
{
    namespace
    {
        using FogWake::Point;
        using FogWake::Runtime;
        using FogWake::RuntimeConfig;

        constexpr const char* kComponent = "fogwake";

        // One fixed bank, per the milestone plan: a wake must not move because
        // the camera did. The bank is latched to the first emitter observed in a
        // session, because a region centred on the world origin would sit
        // nowhere near where a Battlezone mission is actually played.
        constexpr double kBankCells = 256;
        constexpr double kBankCellSize = 2;   // 512 m square.

        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_ConfigLoaded{false};

        // Owned by the render thread: every entry point below is called from it.
        Runtime g_Runtime;
        bool g_BankPlaced = false;
        bool g_Running = false;

        bool ReadEnabledSetting()
        {
            bool enabled = false;
            if (TryGetUserConfigBool("Experimental", "InteractiveFogWakes", enabled) && enabled)
                return true;
            return EnvFlagEnabled("OPENSHIM_INTERACTIVE_FOG_WAKES");
        }

        void EnsureConfigLoaded()
        {
            if (g_ConfigLoaded.load(std::memory_order_acquire))
                return;
            g_Enabled.store(ReadEnabledSetting(), std::memory_order_relaxed);
            g_ConfigLoaded.store(true, std::memory_order_release);
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[FOGWAKE] simulation enabled; no rendering in this build");
            }
        }

        double NowSeconds()
        {
            using namespace std::chrono;
            const auto now = steady_clock::now().time_since_epoch();
            return duration<double>(now).count();
        }

        // Places the bank around the first emitter of the session and configures
        // the runtime. Failure latches the feature off rather than retrying every
        // frame with the same rejected numbers.
        bool PlaceBank(Point around)
        {
            RuntimeConfig config;
            config.field.width = static_cast<std::size_t>(kBankCells);
            config.field.height = static_cast<std::size_t>(kBankCells);
            config.field.cellSize = kBankCellSize;
            const double half = kBankCells * kBankCellSize * 0.5;
            config.field.origin = { around.x - half, around.z - half };

            if (!g_Runtime.Configure(config))
            {
                g_Enabled.store(false, std::memory_order_relaxed);
                LogShimA(LogLevel::Warn, kComponent,
                    "[FOGWAKE] configuration rejected; feature stood down");
                return false;
            }

            g_Runtime.BeginSession(NowSeconds());
            LogShimA(LogLevel::Info, kComponent,
                "[FOGWAKE] bank placed origin=(%.1f, %.1f) size=%.0fm cell=%.1fm",
                config.field.origin.x, config.field.origin.z,
                kBankCells * kBankCellSize, kBankCellSize);
            return true;
        }
    }

    bool FogWakeFeatureEnabled()
    {
        EnsureConfigLoaded();
        return g_Enabled.load(std::memory_order_relaxed);
    }

    void FogWakeNotifyMissionRunStateChanged(bool running)
    {
        if (!FogWakeFeatureEnabled())
            return;

        g_Running = running;
        if (running)
        {
            // The next emitter re-places the bank: a new mission is a new world.
            g_BankPlaced = false;
            return;
        }

        g_Runtime.Shutdown();
        g_BankPlaced = false;
    }

    void FogWakeObserveEmitter(const void* emitter, float worldX, float worldZ)
    {
        if (!FogWakeFeatureEnabled() || emitter == nullptr)
            return;
        if (!std::isfinite(worldX) || !std::isfinite(worldZ))
            return;

        const Point position{ static_cast<double>(worldX), static_cast<double>(worldZ) };
        if (!g_BankPlaced)
        {
            if (!PlaceBank(position))
                return;
            g_BankPlaced = true;
        }

        g_Runtime.Observe(emitter, position, NowSeconds());
    }

    void FogWakeRenderFrameTick()
    {
        if (!FogWakeFeatureEnabled() || !g_BankPlaced)
            return;

        // Called once per camera. The runtime steps a fixed cadence off this
        // clock, so the extra calls are no-ops rather than extra simulation.
        // No wind source is wired yet; transport is deliberately still.
        g_Runtime.AdvanceTo(NowSeconds(), Point{});
    }
}
