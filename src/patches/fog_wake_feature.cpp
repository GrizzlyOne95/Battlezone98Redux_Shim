#include "fog_wake_feature.h"

#include "bzr_options_ui.h"
#include "fog_wake_runtime.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

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

        // Trail probe (OPENSHIM_FOGWAKE_TRAIL_PROBE=1): records each emitter's
        // observed path and, once a second, samples the clearance field along
        // the centreline of the freshest stretch of the busiest path. The
        // adjacent-sample variation is the trail-uniformity figure: a chain of
        // patches shows up as large jumps, an even trail as a few percent.
        struct ProbeSample { Point p; double t; };
        struct ProbePath { const void* key = nullptr; std::vector<ProbeSample> samples; };
        constexpr std::size_t kProbeMaxPaths = 8;
        constexpr std::size_t kProbeMaxSamples = 4096;
        constexpr double kProbeMinAge = 0.75;  // Seconds behind the craft.
        constexpr double kProbeMaxAge = 3.0;
        int g_ProbeEnabled = -1;
        std::vector<ProbePath> g_ProbePaths;
        double g_ProbeNextLog = 0;

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

        using FnGameTime = float(__cdecl*)();

        // The field runs on game time, so it follows the simulation: a pause
        // freezes it, and a capture that steps game time per frame
        // (OPENSHIM_FRAME_CAPTURE_STEP_MS) sees the same wake as play. On the
        // wall clock such a capture runs the game many times faster than the
        // field between captured frames, so the 120 m/s check rejects ordinary
        // moves and the trail breaks into patches. Without the engine clock it
        // falls back to the wall clock.
        FnGameTime ResolveGameTime()
        {
            const uint32_t address = HookEngine::EngineAddress("GetGameTime");
            LogShimA(LogLevel::Info, kComponent, "[FOGWAKE] clock=%s",
                     address ? "game time" : "wall clock (GetGameTime unresolved)");
            return reinterpret_cast<FnGameTime>(static_cast<uintptr_t>(address));
        }

        double NowSeconds()
        {
            static const FnGameTime gameTime = ResolveGameTime();
            if (gameTime)
                return static_cast<double>(gameTime());
            using namespace std::chrono;
            const auto now = steady_clock::now().time_since_epoch();
            return duration<double>(now).count();
        }

        bool ProbeEnabled()
        {
            if (g_ProbeEnabled < 0)
                g_ProbeEnabled = EnvFlagEnabled("OPENSHIM_FOGWAKE_TRAIL_PROBE") ? 1 : 0;
            return g_ProbeEnabled == 1;
        }

        void ProbeRecord(const void* key, Point p, double now)
        {
            auto it = std::find_if(g_ProbePaths.begin(), g_ProbePaths.end(),
                                   [key](const ProbePath& path) { return path.key == key; });
            if (it == g_ProbePaths.end())
            {
                if (g_ProbePaths.size() >= kProbeMaxPaths)
                    return;
                g_ProbePaths.push_back({ key, {} });
                it = g_ProbePaths.end() - 1;
            }
            auto& s = it->samples;
            if (!s.empty() && std::hypot(p.x - s.back().p.x, p.z - s.back().p.z) < 0.5)
                return;
            if (s.size() >= kProbeMaxSamples)
                s.erase(s.begin(), s.begin() + kProbeMaxSamples / 2);
            s.push_back({ p, now });
        }

        void ProbeLog(double now)
        {
            if (now < g_ProbeNextLog)
                return;
            g_ProbeNextLog = now + 1.0;
            const auto& field = g_Runtime.GetField();
            const double step = field.Settings().cellSize;

            // The stretch of each path aged kProbeMinAge..kProbeMaxAge, resampled
            // every cell along its arc length; keep the longest one.
            std::vector<float> best;
            for (const auto& path : g_ProbePaths)
            {
                std::vector<float> values;
                double carry = 0;
                for (std::size_t i = 1; i < path.samples.size(); ++i)
                {
                    const auto& a = path.samples[i - 1];
                    const auto& b = path.samples[i];
                    const double ageA = now - a.t;
                    const double ageB = now - b.t;
                    if (ageA > kProbeMaxAge || ageB < kProbeMinAge)
                        continue;
                    const double length = std::hypot(b.p.x - a.p.x, b.p.z - a.p.z);
                    for (double d = carry; d < length; d += step)
                    {
                        const double f = d / length;
                        values.push_back(field.Sample({ a.p.x + (b.p.x - a.p.x) * f, a.p.z + (b.p.z - a.p.z) * f }));
                    }
                    carry = std::fmod(carry - length, step);
                    if (carry < 0)
                        carry += step;
                }
                if (values.size() > best.size())
                    best.swap(values);
            }
            const auto& stats = g_Runtime.GetStats();
            if (best.size() < 5)
                return;
            double sum = 0, lo = 1, hi = 0, adjMax = 0, adjSum = 0;
            unsigned adjCount = 0;
            for (std::size_t i = 0; i < best.size(); ++i)
            {
                sum += best[i];
                lo = (std::min)(lo, static_cast<double>(best[i]));
                hi = (std::max)(hi, static_cast<double>(best[i]));
                if (i == 0)
                    continue;
                const double m = (std::max)(best[i], best[i - 1]);
                const double v = m > 0.05 ? std::abs(best[i] - best[i - 1]) / m : 0.0;
                adjMax = (std::max)(adjMax, v);
                adjSum += v;
                ++adjCount;
            }
            LogShimA(LogLevel::Info, kComponent,
                "[FOGWAKE] trail probe samples=%u clearance mean=%.3f min=%.3f max=%.3f adjVar max=%.1f%% mean=%.1f%% stamps=%llu teleports=%llu",
                static_cast<unsigned>(best.size()), sum / best.size(), lo, hi,
                adjMax * 100.0, adjCount ? adjSum / adjCount * 100.0 : 0.0,
                static_cast<unsigned long long>(stats.stamps),
                static_cast<unsigned long long>(stats.teleports));

            // The trail body: the longest run at or above half the peak. Its ends
            // are where the craft started and stopped, which ramp by design, so
            // the uniformity figure leaves them out.
            if (hi <= 0)
                return;
            std::size_t runStart = 0, bestStart = 0, bestLen = 0;
            for (std::size_t i = 0; i <= best.size(); ++i)
            {
                if (i < best.size() && best[i] >= 0.5 * hi)
                    continue;
                if (i - runStart > bestLen)
                {
                    bestStart = runStart;
                    bestLen = i - runStart;
                }
                runStart = i + 1;
            }
            double coreMax = 0, coreSum = 0;
            for (std::size_t i = bestStart + 1; i < bestStart + bestLen; ++i)
            {
                const double v = std::abs(best[i] - best[i - 1]) / (std::max)(best[i], best[i - 1]);
                coreMax = (std::max)(coreMax, v);
                coreSum += v;
            }
            char values[512];
            int used = 0;
            for (std::size_t i = 0; i < best.size() && used < static_cast<int>(sizeof(values)) - 8; ++i)
                used += std::snprintf(values + used, sizeof(values) - used, "%s%.2f", i ? " " : "", best[i]);
            LogShimA(LogLevel::Info, kComponent,
                "[FOGWAKE] trail probe body cells=%u adjVar max=%.1f%% mean=%.1f%% values=%s",
                static_cast<unsigned>(bestLen), coreMax * 100.0,
                bestLen > 1 ? coreSum / (bestLen - 1) * 100.0 : 0.0, values);
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
        g_ProbePaths.clear();
        g_ProbeNextLog = 0;
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

        const double now = NowSeconds();
        g_Runtime.Observe(emitter, position, now);
        if (ProbeEnabled())
            ProbeRecord(emitter, position, now);
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
        const double now = NowSeconds();
        g_Runtime.AdvanceTo(now, Point{});
        if (ProbeEnabled())
            ProbeLog(now);
        FogWakeShaderFrameTick(true);
    }
}
