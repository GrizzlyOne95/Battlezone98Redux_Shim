// mouse_every_frame.cpp
// BZR Open Shim - per-frame mouse look (experimental, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// The mouse reader 0x00623B20 (GOG Redux 2.2.301) runs once per frame from
// NextInputs and does:
//   call TimeStep (0x00822D60)            <- MouseReadChannels::TimeStepCall
//   accum += step
//   movss xmm0,[0x008A24F4]  ; 0.016666f  <- MouseReadChannels::BucketThreshold
//   comiss xmm0,[accum] ; jbe apply
// and only on "apply" scales the gathered deltas, writes position
// (accumulated, clamped to +-0x10000) and rate (delta / accum) into the
// device's analog channels, recentres the cursor and clears accum. Between
// buckets the channels keep their last values. Stock input.map binds steer
// to the rate (HorizVel) and pitch to the position (VertPos), so both keep
// their per-second scale when the bucket is one frame long.
//
// The operand is repointed at g_Threshold, which the TimeStep wrapper sets
// just before the compare: a tiny positive value in single player, the
// original constant in network games and while the step is zero (paused).
// Zero would divide by a zero accumulator when paused.
// See reverse_engineering/mouse_every_frame_20261020.md.

#include "mouse_every_frame.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "mouse";
        constexpr float kStockThreshold = 0.016666f;
        // Below any real step (the engine's is whole milliseconds), above zero.
        constexpr float kPerFrameThreshold = 0.0001f;

        using FnTimeStep = float(__cdecl*)();
        FnTimeStep g_RealTimeStep = nullptr;
        uint32_t g_IsNetGame = 0;
        uint32_t g_Accumulator = 0;   // diagnostics only; 0 when unresolved
        // Read by the patched movss; written on the main thread right before.
        float g_Threshold = kStockThreshold;

        // Main thread only. A bucket that closed on the previous read leaves
        // the accumulator at zero, so "zero on entry" counts per-frame applies.
        constexpr uint32_t kStatsWindow = 3000;
        uint32_t g_Calls = 0;
        uint32_t g_PerFrameCalls = 0;
        uint32_t g_ClosedOnEntry = 0;
        uint32_t g_StatsLogged = 0;

        void CountCall(bool perFrame)
        {
            ++g_Calls;
            if (perFrame)
                ++g_PerFrameCalls;
            if (g_Accumulator != 0 &&
                *reinterpret_cast<const volatile float*>(static_cast<uintptr_t>(g_Accumulator)) == 0.0f)
                ++g_ClosedOnEntry;
            if (g_Calls < kStatsWindow)
                return;
            if (g_StatsLogged < 20)
            {
                ++g_StatsLogged;
                LogShimA(LogLevel::Info, kComponent,
                         "[MouseEveryFrame] last %u reads: %u per-frame threshold, %u with the bucket already closed",
                         g_Calls, g_PerFrameCalls, g_ClosedOnEntry);
            }
            g_Calls = g_PerFrameCalls = g_ClosedOnEntry = 0;
        }

        float __cdecl TimeStepHook()
        {
            const float step = g_RealTimeStep();
            const bool netGame = *reinterpret_cast<const volatile uint8_t*>(
                                     static_cast<uintptr_t>(g_IsNetGame)) != 0;
            const bool perFrame = !netGame && step > 0.0f;
            g_Threshold = perFrame ? kPerFrameThreshold : kStockThreshold;
            CountCall(perFrame);
            return step;
        }

        bool IsReadable(uint32_t address, size_t size)
        {
            MEMORY_BASIC_INFORMATION info{};
            if (VirtualQuery(reinterpret_cast<const void*>(static_cast<uintptr_t>(address)), &info, sizeof(info)) == 0)
                return false;
            const DWORD readable = PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE;
            const uintptr_t end = reinterpret_cast<uintptr_t>(info.BaseAddress) + info.RegionSize;
            return info.State == MEM_COMMIT && (info.Protect & readable) != 0 &&
                   (info.Protect & PAGE_GUARD) == 0 && address + size <= end;
        }

        bool ReadEnabledSetting()
        {
            bool enabled = false;
            if (TryGetUserConfigBool("Experimental", "MouseEveryFrame", enabled) && enabled)
                return true;
            return EnvFlagEnabled("OPENSHIM_MOUSE_EVERY_FRAME");
        }
    }

    void InitializeMouseEveryFrame()
    {
        if (!ReadEnabledSetting())
            return;

        const uint32_t callSite = HookEngine::ResolveNamedAddress("MouseReadChannels::TimeStepCall");
        const uint32_t operand = HookEngine::ResolveNamedAddress("MouseReadChannels::BucketThreshold");
        const uint32_t timeStep = HookEngine::ResolveNamedAddress("TimeStep");
        g_IsNetGame = HookEngine::EngineAddress("IsNetGameFlag");
        g_Accumulator = HookEngine::ResolveNamedAddress("MouseReadChannels::Accumulator");
        if (callSite == 0 || operand == 0 || timeStep == 0 || g_IsNetGame == 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MouseEveryFrame] stands down: call 0x%08X operand 0x%08X TimeStep 0x%08X net 0x%08X",
                     callSite, operand, timeStep, g_IsNetGame);
            return;
        }

        // The operand must belong to `movss xmm0,[m32]` and name the stock
        // 1/60 s constant; anything else is a different build or a prior patch.
        uint8_t opcode[4] = {};
        uint32_t constantAddress = 0;
        std::memcpy(opcode, reinterpret_cast<const void*>(static_cast<uintptr_t>(operand - 4)), sizeof(opcode));
        std::memcpy(&constantAddress, reinterpret_cast<const void*>(static_cast<uintptr_t>(operand)),
                    sizeof(constantAddress));
        static const uint8_t kMovssXmm0Abs[4] = {0xF3, 0x0F, 0x10, 0x05};
        float constant = 0.0f;
        if (std::memcmp(opcode, kMovssXmm0Abs, sizeof(opcode)) != 0 ||
            !IsReadable(constantAddress, sizeof(float)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MouseEveryFrame] stands down: 0x%08X is not movss xmm0,[m32]", operand - 4);
            return;
        }
        std::memcpy(&constant, reinterpret_cast<const void*>(static_cast<uintptr_t>(constantAddress)),
                    sizeof(constant));
        if (constant != kStockThreshold)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MouseEveryFrame] stands down: threshold at 0x%08X is %.6f, not 1/60",
                     constantAddress, static_cast<double>(constant));
            return;
        }

        g_RealTimeStep = reinterpret_cast<FnTimeStep>(static_cast<uintptr_t>(timeStep));
        g_Threshold = kStockThreshold;
        // Wrapper first: until the operand moves, g_Threshold is unread.
        if (!Hooks::RedirectCallTarget(callSite, timeStep, reinterpret_cast<uintptr_t>(&TimeStepHook)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MouseEveryFrame] stands down: call at 0x%08X does not target TimeStep 0x%08X",
                     callSite, timeStep);
            return;
        }
        const uint32_t thresholdAddress = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_Threshold));
        if (!Hooks::WritePatchBytes(operand, reinterpret_cast<const uint8_t*>(&thresholdAddress),
                                    sizeof(thresholdAddress)))
        {
            // The wrapper alone changes nothing: the compare still reads the constant.
            LogShimA(LogLevel::Warn, kComponent,
                     "[MouseEveryFrame] stands down: could not write operand 0x%08X", operand);
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
                 "[MouseEveryFrame] enabled: bucket compare 0x%08X -> shim threshold (single player only)",
                 operand - 4);
    }
}
