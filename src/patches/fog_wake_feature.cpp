#include "fog_wake_feature.h"

#include "bzr_options_ui.h"
#include "fog_wake_runtime.h"
#include "shim_log.h"

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>

#include <Windows.h>

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
        // Wake look: a trail wider than a hover tank (half-width 7 m), and a
        // refill slow enough that it lingers for several seconds.
        constexpr double kWakeRadius = 7;
        constexpr double kRecoverySeconds = 6;

        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_ConfigLoaded{false};

        // Owned by the render thread: every entry point below is called from it.
        Runtime g_Runtime;
        bool g_BankPlaced = false;
        bool g_Running = false;
        bool g_StoppedSinceStart = false;
        unsigned g_BankGeneration = 0;

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
                    "[FOGWAKE] simulation enabled; in-shader ground fog on DX11 Enhanced only");
            }
        }

        double EnvDouble(const char* name, double fallback, double lo, double hi)
        {
            char buffer[64] = {};
            const DWORD length = GetEnvironmentVariableA(name, buffer, sizeof(buffer));
            if (length == 0 || length >= sizeof(buffer))
                return fallback;
            char* end = nullptr;
            const double value = std::strtod(buffer, &end);
            if (end == buffer || !std::isfinite(value) || value < lo || value > hi)
                return fallback;
            return value;
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
            config.radius = EnvDouble("OPENSHIM_FOGWAKE_RADIUS", kWakeRadius, 1.0, 40.0);
            config.field.recoverySeconds = EnvDouble("OPENSHIM_FOGWAKE_RECOVERY", kRecoverySeconds, 0.5, 120.0);

            if (!g_Runtime.Configure(config))
            {
                g_Enabled.store(false, std::memory_order_relaxed);
                LogShimA(LogLevel::Warn, kComponent,
                    "[FOGWAKE] configuration rejected; feature stood down");
                return false;
            }

            g_Runtime.BeginSession(NowSeconds());
            ++g_BankGeneration;
            LogShimA(LogLevel::Info, kComponent,
                "[FOGWAKE] bank placed origin=(%.1f, %.1f) size=%.0fm cell=%.1fm wakeRadius=%.1fm recovery=%.1fs",
                config.field.origin.x, config.field.origin.z,
                kBankCells * kBankCellSize, kBankCellSize, config.radius, config.field.recoverySeconds);
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
        g_StoppedSinceStart = !running;
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

    bool FogWakePlaceBankIfAbsent(float worldX, float worldZ)
    {
        // Not gated on g_Running: a command-line mission launch (lcbench)
        // never sees the RUN_STARTED edge, so that gate kept quiet scenes
        // fog-free. Only a seen stop blocks it, until the next start, so a
        // transition never latches the bank to the old world's player.
        if (!FogWakeFeatureEnabled() || g_BankPlaced || g_StoppedSinceStart)
            return false;
        if (!std::isfinite(worldX) || !std::isfinite(worldZ))
            return false;
        if (PlaceBank(Point{ static_cast<double>(worldX), static_cast<double>(worldZ) }))
            g_BankPlaced = true;
        return g_BankPlaced;
    }

    bool FogWakeGetRenderView(FogWakeRenderView& out)
    {
        if (!FogWakeFeatureEnabled() || !g_BankPlaced || !g_Runtime.Enabled())
            return false;
        const auto& field = g_Runtime.GetField();
        const auto& settings = field.Settings();
        const auto& cells = field.Clearance();
        if (cells.size() != settings.width * settings.height || cells.empty())
            return false;
        out.clearance = cells.data();
        out.width = static_cast<unsigned>(settings.width);
        out.height = static_cast<unsigned>(settings.height);
        out.originX = settings.origin.x;
        out.originZ = settings.origin.z;
        out.cellSize = settings.cellSize;
        out.steps = g_Runtime.GetStats().steps;
        out.bankGeneration = g_BankGeneration;
        return true;
    }

    void FogWakeRenderFrameTick()
    {
        if (!FogWakeFeatureEnabled())
            return;
        if (!g_BankPlaced)
        {
            FogWakeShaderFrameTick(false);
            return;
        }

        // Called once per camera. The runtime steps a fixed cadence off this
        // clock, so the extra calls are no-ops rather than extra simulation.
        // No wind source is wired yet; transport is deliberately still.
        g_Runtime.AdvanceTo(NowSeconds(), Point{});
        FogWakeShaderFrameTick(true);
    }
}
