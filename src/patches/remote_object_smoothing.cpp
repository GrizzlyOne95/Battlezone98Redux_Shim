// remote_object_smoothing.cpp
// BZR Open Shim - frame-rate-independent smoothing of remote objects (opt-in)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// GameObject::Simulate (GOG 0x004DEEC0, void __cdecl(obj76*), plain `ret`),
// for a remote object in a network game:
//   1. saves the displayed transform obj76+0x20 as D0;
//   2. unless true_transform.posit_y (GO+0x58) is the -1.0 sentinel, copies
//      true_transform (GO+0x28) into obj76+0x20;
//   3. dead-reckons up to 5 physics sub-steps, stopping if obj76+0x14 & 0x200
//      (deleted), in which case it returns without the steps below;
//   4. stores the result P in true_transform;
//   5. displays D0 + 0.3 (P - D0) and slerp(D0, P, 0.5) - fixed per frame;
//   6. calls GameObject::UpdatePosition (0x004DB100).
// With [Network] RemoteSmoothingMs = tau > 0 this entry detour keeps steps
// 1-4 and recomputes step 5 with alpha = 1 - exp(-dt / tau), then repeats 6.
// Step 2 discards the display at the start of every frame, so the blend never
// feeds back into physics. A sentinel frame keeps the stock result.
// See reverse_engineering/notes/remote_object_smoothing_20261107.md.

#include "remote_object_smoothing.h"

#include "BZROpenShim.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "remote_smoothing_policy.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "remotesmooth";

        constexpr uint32_t kObjFlagsOffset = 0x14;
        constexpr uint32_t kObjFlagDeleted = 0x200;
        constexpr uint32_t kObjTransformOffset = 0x20;
        constexpr uint32_t kGoTrueTransformOffset = 0x28;
        constexpr uint32_t kGoTruePositYOffset = 0x58;
        // DistributedObject at GO+0x18; its object_type byte at +0x68 is 2 for
        // a remote object (pinned by the DistributedObjectIsRemote row).
        constexpr uint32_t kGoObjectTypeOffset = 0x18 + 0x68;
        constexpr uint8_t kObjectTypeRemote = 2;
        constexpr double kInvalidPositY = -1.0;

        // push ebp; mov ebp,esp; sub esp,0x1A8 - no relative operands.
        constexpr uint8_t kPrologue[] = {0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xA8, 0x01, 0x00, 0x00};

        using SimulateFn = void(__cdecl*)(void* obj);
        using FromObj76Fn = void*(__cdecl*)(void* obj);
        using UpdatePositionFn = void(__thiscall*)(void* go);
        using TimeStepFn = float(__cdecl*)();

        InlineDetour32 g_Detour;
        FromObj76Fn g_FromObj76 = nullptr;
        UpdatePositionFn g_UpdatePosition = nullptr;
        TimeStepFn g_TimeStep = nullptr;
        uint32_t g_IsNetGameAddr = 0;
        double g_TauSeconds = 0.0;
        volatile LONG g_Faulted = 0;

        // Main thread only.
        uint32_t g_Blended = 0;
        uint32_t g_Snapped = 0;
        uint32_t g_Skipped = 0;
        ULONGLONG g_LastReport = 0;

        template <typename T>
        T& At(uintptr_t address)
        {
            return *reinterpret_cast<T*>(address);
        }

        struct Pre
        {
            void* go = nullptr;
            RemoteSmoothing::Transform previous{};
        };

        // True when the stock remote path is about to run with a valid
        // true_transform, so its step 5 will execute unless the object dies.
        bool CapturePrevious(void* obj, Pre& pre)
        {
            __try
            {
                if (!At<uint8_t>(g_IsNetGameAddr)) return false;
                const auto o = reinterpret_cast<uintptr_t>(obj);
                if (At<uint32_t>(o + kObjFlagsOffset) & kObjFlagDeleted) return false;
                void* go = g_FromObj76(obj);
                if (!go) return false;
                const auto g = reinterpret_cast<uintptr_t>(go);
                if (At<uint8_t>(g + kGoObjectTypeOffset) != kObjectTypeRemote) return false;
                if (At<double>(g + kGoTruePositYOffset) == kInvalidPositY) return false;
                std::memcpy(&pre.previous, reinterpret_cast<const void*>(o + kObjTransformOffset),
                            sizeof(pre.previous));
                pre.go = go;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                InterlockedExchange(&g_Faulted, 1);
                return false;
            }
        }

        void ApplyBlend(void* obj, const Pre& pre)
        {
            __try
            {
                const auto o = reinterpret_cast<uintptr_t>(obj);
                if (At<uint32_t>(o + kObjFlagsOffset) & kObjFlagDeleted) return;
                const auto g = reinterpret_cast<uintptr_t>(pre.go);
                if (At<uint8_t>(g + kGoObjectTypeOffset) != kObjectTypeRemote) return;

                RemoteSmoothing::Transform target;
                std::memcpy(&target, reinterpret_cast<const void*>(g + kGoTrueTransformOffset), sizeof(target));
                RemoteSmoothing::Transform out;
                const RemoteSmoothing::Outcome outcome =
                    RemoteSmoothing::Blend(pre.previous, target, g_TimeStep(), g_TauSeconds, out);
                if (outcome == RemoteSmoothing::Outcome::Skipped)
                {
                    ++g_Skipped;
                    return;
                }
                std::memcpy(reinterpret_cast<void*>(o + kObjTransformOffset), &out, sizeof(out));
                g_UpdatePosition(pre.go);
                if (outcome == RemoteSmoothing::Outcome::Blended) ++g_Blended; else ++g_Snapped;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                InterlockedExchange(&g_Faulted, 1);
            }
        }

        void ReportCounters()
        {
            const ULONGLONG now = GetTickCount64();
            if (now - g_LastReport < 30000) return;
            g_LastReport = now;
            if (!g_Blended && !g_Snapped && !g_Skipped) return;
            LogShimA(LogLevel::Info, kComponent,
                     "[RemoteSmoothing] last 30 s: blended=%u snapped=%u skipped=%u",
                     g_Blended, g_Snapped, g_Skipped);
            g_Blended = g_Snapped = g_Skipped = 0;
        }

        void __cdecl SimulateHook(void* obj)
        {
            const auto original = reinterpret_cast<SimulateFn>(g_Detour.trampoline);
            if (g_Faulted)
            {
                original(obj);
                return;
            }
            Pre pre;
            const bool armed = CapturePrevious(obj, pre);
            original(obj);
            if (armed) ApplyBlend(obj, pre);
            if (g_Faulted)
                LogShimA(LogLevel::Warn, kComponent, "[RemoteSmoothing] fault reading an object; stock blend from now on");
            else
                ReportCounters();
        }

        // [Network] RemoteSmoothingMs: 0 (default) = stock, else the position
        // time constant in milliseconds, clamped to 0..300.
        int ReadTauMs()
        {
            std::string text;
            if (!TryGetUserConfigString("Network", "RemoteSmoothingMs", text) || text.empty()) return 0;
            char* end = nullptr;
            const long value = std::strtol(text.c_str(), &end, 10);
            if (end == text.c_str()) return 0;
            return RemoteSmoothing::ClampTauMs(static_cast<int>(value));
        }
    }

    void InitializeRemoteObjectSmoothing()
    {
        const int tauMs = ReadTauMs();
        if (tauMs <= 0) return;  // stock; nothing logged for the default
        if (!IsCompatibleGameVersion())
        {
            LogShimA(LogLevel::Warn, kComponent, "[RemoteSmoothing] stands down: unsupported game build");
            return;
        }

        uint32_t simulate = 0;
        // remoteCopy and isRemote are layout guards only: binding them proves
        // the offsets this file hard-codes still match the build. Keep them.
        uint32_t remoteCopy = 0;
        uint32_t isRemote = 0;
        uint32_t updatePosition = 0;
        uint32_t isNetGame = 0;
        const HookEngine::EngineRow rows[] = {
            { "GameObjectSimulate", &simulate },
            { "GameObjectSimulateRemoteCopy", &remoteCopy },
            { "DistributedObjectIsRemote", &isRemote },
            { "GameObjectUpdatePosition", &updatePosition },
            { "IsNetGameFlag", &isNetGame },
        };
        const uint32_t fromObj76 = HookEngine::ResolveNamedAddress("GameObject::FromObj76");
        const uint32_t timeStep = HookEngine::ResolveNamedAddress("TimeStep");
        if (!fromObj76 || !timeStep || !HookEngine::BindEngineRows("RemoteSmoothing", rows))
        {
            LogShimA(LogLevel::Warn, kComponent, "[RemoteSmoothing] stands down: an address did not resolve");
            return;
        }

        g_FromObj76 = reinterpret_cast<FromObj76Fn>(static_cast<uintptr_t>(fromObj76));
        g_TimeStep = reinterpret_cast<TimeStepFn>(static_cast<uintptr_t>(timeStep));
        g_UpdatePosition = reinterpret_cast<UpdatePositionFn>(static_cast<uintptr_t>(updatePosition));
        g_IsNetGameAddr = isNetGame;
        g_TauSeconds = tauMs / 1000.0;

        if (!InstallInlineDetour32(g_Detour, simulate, reinterpret_cast<void*>(&SimulateHook),
                                   sizeof(kPrologue), kPrologue, sizeof(kPrologue)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[RemoteSmoothing] stands down: entry detour at 0x%08X failed", simulate);
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
                 "[RemoteSmoothing] enabled: tau=%d ms (rotation %.0f ms), snap %.0f m, detour 0x%08X",
                 tauMs, tauMs / RemoteSmoothing::kRotationTauDivisor, RemoteSmoothing::kSnapDistance, simulate);
    }
}
