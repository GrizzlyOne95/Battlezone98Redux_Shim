// precise_timestep.cpp
// BZR Open Shim - QPC-precise simulation step (experimental, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// SetLoopTimes (GOG 0x00822AE0, void(void)) spins Sleep(1) until the
// millisecond system clock changes, then stores:
//   integer ms dt (clamped to 200)   -> TimestepClampedMs
//   the same before the clamp        -> TimestepRawMs
//   clamped dt * 0.001 (float)       -> TimestepSeconds, read by the getter
//                                       0x00822D60 that physics, input and AI use
//   unclamped dt * 0.001 (float)     -> TimestepUnclampedSeconds
//   1 / step (float)                 -> TimestepInverse (no readers found)
// The integer game clocks are accumulated from the integer dt inside the same
// function, so replacing only the floats afterwards cannot move game time.
//
// Test-only OPENSHIM_FRAME_CAPTURE_STEP_MS=N (1..200, single player) makes each
// frame advance game time by exactly N ms, however long the frame took: before
// SetLoopTimes runs, its previous-clock global is set to (clock now - N), so its
// own dt comes out as N (N+1 if the millisecond ticks in between). Frame
// captures that take seconds to write then still play back smoothly.
// See reverse_engineering/frame_hitch_va_measurement_20261020.md.

#include "precise_timestep.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdlib>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "timestep";

        // The engine's own interval is whole milliseconds of wall-clock time,
        // so a genuine frame differs from the QPC interval by under 1 ms. A
        // larger gap means the two clocks are not measuring the same frame
        // (first frame, pause, the menu loop's own SetLoopTimes call, a clock
        // adjustment): keep the engine value.
        constexpr double kAgreementToleranceMs = 1.5;
        constexpr uint32_t kEngineClampMs = 200;
        // Bytes from the SetLoopTimes entry in which its clock spin-wait must sit.
        constexpr uint32_t kOwnSpinWindow = 0x30;
        // Fraction of the accumulated difference between the integer and the
        // precise step totals fed back per frame, and its per-frame cap. Keeps
        // simulated time within about a millisecond of the engine's clock.
        constexpr double kDriftGain = 0.1;
        constexpr double kDriftCapMs = 0.25;

        struct Globals
        {
            uint32_t clampedMs = 0;
            uint32_t rawMs = 0;
            uint32_t seconds = 0;
            uint32_t unclampedSeconds = 0;
            uint32_t inverse = 0;
            uint32_t isNetGame = 0;
        };

        Globals g_Globals;
        std::atomic<int> g_GlobalsState{0};   // 0 unresolved, 1 bound, -1 failed

        using FnSetLoopTimes = void(__cdecl*)();
        FnSetLoopTimes g_RealSetLoopTimes = nullptr;

        // Main thread only.
        uint64_t g_LastQpc = 0;
        double g_QpcToMs = 0.0;
        double g_DebtMs = 0.0;   // sum(engine ms) - sum(precise ms)
        bool g_LastPrecise = false;

        // OPENSHIM_FRAME_CAPTURE_STEP_MS; 0 when off.
        using FnClockMs = uint32_t(__cdecl*)();
        FnClockMs g_ClockMs = nullptr;
        uint32_t g_LastClockMs = 0;
        uint32_t g_CaptureStepMs = 0;

        // The openshim.ini answer, and that answer AND'd with the single-player
        // predicate by the multiplayer gate (RefreshPreciseTimestepState).
        bool g_Enabled = false;
        std::atomic<bool> g_Active{false};

        uint64_t ReadQpc()
        {
            LARGE_INTEGER value{};
            QueryPerformanceCounter(&value);
            return static_cast<uint64_t>(value.QuadPart);
        }

        bool BindGlobals()
        {
            const int state = g_GlobalsState.load(std::memory_order_acquire);
            if (state != 0)
                return state > 0;

            Globals bound;
            bound.clampedMs = HookEngine::ResolveNamedAddress("Timestep::ClampedMs");
            bound.rawMs = HookEngine::ResolveNamedAddress("Timestep::RawMs");
            bound.seconds = HookEngine::ResolveNamedAddress("Timestep::Seconds");
            bound.unclampedSeconds = HookEngine::ResolveNamedAddress("Timestep::UnclampedSeconds");
            bound.inverse = HookEngine::ResolveNamedAddress("Timestep::Inverse");
            bound.isNetGame = HookEngine::EngineAddress("IsNetGameFlag");
            const bool ok = bound.clampedMs && bound.rawMs && bound.seconds &&
                            bound.unclampedSeconds && bound.inverse && bound.isNetGame;
            if (ok)
            {
                g_Globals = bound;
            }
            else
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "Timestep globals unresolved (clamped=0x%08X raw=0x%08X step=0x%08X "
                         "unclamped=0x%08X inverse=0x%08X net=0x%08X)",
                         bound.clampedMs, bound.rawMs, bound.seconds,
                         bound.unclampedSeconds, bound.inverse, bound.isNetGame);
            }
            g_GlobalsState.store(ok ? 1 : -1, std::memory_order_release);
            return ok;
        }

        template <typename T>
        T& At(uint32_t address)
        {
            return *reinterpret_cast<T*>(static_cast<uintptr_t>(address));
        }

        void __cdecl SetLoopTimesHook()
        {
            if (g_CaptureStepMs != 0)
            {
                if (Hooks::IsSinglePlayerSession() && At<uint8_t>(g_Globals.isNetGame) == 0)
                    At<uint32_t>(g_LastClockMs) = g_ClockMs() - g_CaptureStepMs;
                g_RealSetLoopTimes();
                g_LastPrecise = false;
                return;
            }

            g_RealSetLoopTimes();

            const uint64_t now = ReadQpc();
            const uint64_t last = g_LastQpc;
            g_LastQpc = now;
            g_LastPrecise = false;

            const uint32_t engineMs = At<uint32_t>(g_Globals.clampedMs);
            const uint32_t rawMs = At<uint32_t>(g_Globals.rawMs);
            // The registry gate can lag a session change by one reconcile, so
            // the engine's own net-game byte is checked here as well.
            const bool netGame = !g_Active.load(std::memory_order_relaxed) ||
                                 At<uint8_t>(g_Globals.isNetGame) != 0;
            if (last == 0 || netGame || engineMs == 0 || rawMs >= kEngineClampMs)
            {
                g_DebtMs = 0.0;
                return;
            }

            const double measuredMs = static_cast<double>(now - last) * g_QpcToMs;
            if (std::fabs(measuredMs - static_cast<double>(engineMs)) > kAgreementToleranceMs)
            {
                g_DebtMs = 0.0;
                return;
            }

            double correction = g_DebtMs * kDriftGain;
            if (correction > kDriftCapMs)
                correction = kDriftCapMs;
            else if (correction < -kDriftCapMs)
                correction = -kDriftCapMs;
            const double stepMs = measuredMs + correction;
            g_DebtMs += static_cast<double>(engineMs) - stepMs;

            const float stepSeconds = static_cast<float>(stepMs * 0.001);
            At<float>(g_Globals.seconds) = stepSeconds;
            At<float>(g_Globals.unclampedSeconds) = stepSeconds;
            At<float>(g_Globals.inverse) = 1.0f / stepSeconds;
            g_LastPrecise = true;
        }

        // [Fixes] PreciseTimestep, default ON. The kill-switch name maps to
        // the inverted ini key in openshim_env_mapping.cpp.
        bool ReadEnabledSetting()
        {
            return !EnvFlagEnabled("OPENSHIM_DISABLE_PRECISE_TIMESTEP");
        }

        // 0 when unset; out-of-range values are rejected with a warning.
        uint32_t ReadCaptureStepMs()
        {
            char text[16] = {};
            const DWORD length = GetEnvironmentVariableA("OPENSHIM_FRAME_CAPTURE_STEP_MS",
                                                         text, static_cast<DWORD>(sizeof(text)));
            if (length == 0)
                return 0;
            char* end = nullptr;
            const unsigned long value = length < sizeof(text) ? std::strtoul(text, &end, 10) : 0;
            if (end == text || end == nullptr || *end != '\0' || value == 0 || value > kEngineClampMs)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[CaptureStep] OPENSHIM_FRAME_CAPTURE_STEP_MS must be 1..%u ms; ignored",
                         kEngineClampMs);
                return 0;
            }
            return static_cast<uint32_t>(value);
        }

        bool BindCaptureClock()
        {
            g_ClockMs = reinterpret_cast<FnClockMs>(static_cast<uintptr_t>(
                HookEngine::ResolveNamedAddress("SetLoopTimes::Clock")));
            g_LastClockMs = HookEngine::ResolveNamedAddress("SetLoopTimes::LastClockMs");
            if (g_ClockMs == nullptr || g_LastClockMs == 0)
                return false;
            // Fail closed unless the matched spin-wait is SetLoopTimes' own:
            // its first bytes must hold `cmp [LastClockMs],eax` (39 05 imm32).
            const uint32_t target = HookEngine::ResolveNamedAddress("SetLoopTimes");
            if (target == 0)
                return false;
            const auto* code = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(target));
            for (uint32_t i = 0; i + 6 <= kOwnSpinWindow; ++i)
            {
                if (code[i] == 0x39 && code[i + 1] == 0x05 &&
                    *reinterpret_cast<const uint32_t*>(code + i + 2) == g_LastClockMs)
                    return true;
            }
            return false;
        }
    }

    namespace Hooks
    {
        void RefreshPreciseTimestepState()
        {
            g_Active.store(g_Enabled && IsSinglePlayerSession(), std::memory_order_relaxed);
        }
    }

    void InitializePreciseTimestep()
    {
        const bool precise = ReadEnabledSetting();
        uint32_t captureStepMs = ReadCaptureStepMs();
        if (!precise)
            LogShimA(LogLevel::Info, kComponent, "[PreciseTimestep] disabled by [Fixes] PreciseTimestep = 0");
        if (!precise && captureStepMs == 0)
            return;
        if (!BindGlobals())
        {
            LogShimA(LogLevel::Warn, kComponent, "[PreciseTimestep] stands down: globals unresolved");
            return;
        }
        if (captureStepMs != 0 && !BindCaptureClock())
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[CaptureStep] stands down: clock 0x%08X or last-clock global 0x%08X unresolved",
                     static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_ClockMs)), g_LastClockMs);
            captureStepMs = 0;
            if (!precise)
                return;
        }

        const uint32_t callSite = HookEngine::ResolveNamedAddress("SetLoopTimes::FrameCall");
        const uint32_t target = HookEngine::ResolveNamedAddress("SetLoopTimes");
        if (callSite == 0 || target == 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[PreciseTimestep] stands down: call site 0x%08X target 0x%08X", callSite, target);
            return;
        }

        LARGE_INTEGER frequency{};
        QueryPerformanceFrequency(&frequency);
        g_QpcToMs = 1000.0 / static_cast<double>(frequency.QuadPart);
        g_RealSetLoopTimes = reinterpret_cast<FnSetLoopTimes>(static_cast<uintptr_t>(target));
        g_CaptureStepMs = captureStepMs;
        g_Enabled = precise;
        Hooks::RefreshPreciseTimestepState();
        if (!Hooks::RedirectCallTarget(callSite, target, reinterpret_cast<uintptr_t>(&SetLoopTimesHook)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[PreciseTimestep] stands down: call at 0x%08X does not target 0x%08X",
                     callSite, target);
            g_Enabled = false;
            g_CaptureStepMs = 0;
            Hooks::RefreshPreciseTimestepState();
            return;
        }
        if (g_CaptureStepMs != 0)
            LogShimA(LogLevel::Info, kComponent,
                     "[CaptureStep] enabled: every frame advances game time by %u ms (single player; "
                     "PreciseTimestep off while it runs)", g_CaptureStepMs);
        if (precise)
            LogShimA(LogLevel::Info, kComponent,
                     "[PreciseTimestep] enabled: frame call 0x%08X -> wrapper (single player only)", callSite);
    }

    bool ReadTimestepSample(TimestepSample& out)
    {
        if (!BindGlobals())
            return false;
        out.rawMs = At<uint32_t>(g_Globals.rawMs);
        out.stepSeconds = At<float>(g_Globals.seconds);
        out.precise = g_LastPrecise;
        return true;
    }
}
