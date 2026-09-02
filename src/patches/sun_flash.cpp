// sun_flash.cpp
// BZR Open Shim - sun "flashbang" whiteout opt-out
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/sun_flash.h for the full static trace of where the whiteout
// comes from. In short: LensFlare::Render computes
//
//     flash = visiblePixels * dot(cameraForward, sunDirection)^32 * scale
//
// and hands it to the global ScreenFlash, which paints one fullscreen white
// quad at up to 224/255 alpha. This file rewrites that single call so the
// contribution can be dropped without touching the sun disc, the six flare
// sprites, the sky, the directional light, PSSM, or the Glow compositor -- and
// without touching the two explosion callers of the same ScreenFlash method.

#include "sun_flash.h"

#include "bzr_options_ui.h"
#include "patcher.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstring>

namespace
{
    // Suppress the sun's fullscreen flash contribution. Default OFF, i.e.
    // stock behaviour, so an unconfigured install renders exactly as it always
    // has.
    constexpr bool kSuppressDefault = false;

    // Enough records to cover a slow full sweep across the sun at 60 fps
    // without an unbounded log.
    constexpr long kTraceBudget = 1200;

    bool g_ConfigLoaded = false;
    bool g_PatchInstalled = false;
    long g_TraceRecords = 0;
}

// The thunk reads these from inline asm, so they live at file scope with
// external linkage and unmangled names. Only the render thread reaches the
// thunk, which is why plain volatile bytes are enough.
extern "C" volatile unsigned char g_SunFlashSuppress = kSuppressDefault ? 1u : 0u;
extern "C" volatile unsigned char g_SunFlashTrace = 0u;

// Counts what the arm actually did, so a run where suppression never engaged is
// distinguishable from a run where it engaged and changed nothing.
extern "C" volatile long g_SunFlashSuppressedCalls = 0;
extern "C" volatile long g_SunFlashPassedThroughCalls = 0;

// Filled in by VerifyCallSite with the stock callee the operand used to select.
// The thunk jumps through this, so a failed verify fails closed: the REL32
// payload is never built and the stock call stays in place.
extern "C" void* g_SunFlashStockAddFlash = nullptr;

// Called from the thunk while EBP still addresses LensFlare::Render's frame.
// Reconstructs the three inputs the call site multiplied together and checks
// them against the value we were actually handed: if the product does not
// reproduce `flash`, the frame layout is not what sun_flash.h documents, and
// the reconstructed columns are reported as unverified rather than believed.
extern "C" void __cdecl SunFlashTraceRecord(std::uintptr_t callerFrame, float flash)
{
    using namespace BZROpenShim;

    if (g_TraceRecords >= kTraceBudget)
        return;

    float dot = 0.0f;
    float dotPow32 = 0.0f;
    float scale = 0.0f;
    int visiblePixels = 0;
    bool frameVerified = false;

    __try
    {
        std::memcpy(&dot,
                    reinterpret_cast<const void*>(callerFrame + SunFlash::kFrameOffsetDot),
                    sizeof(dot));
        std::memcpy(&dotPow32,
                    reinterpret_cast<const void*>(callerFrame + SunFlash::kFrameOffsetDotPow32),
                    sizeof(dotPow32));

        std::uintptr_t lensFlare = 0;
        std::memcpy(&lensFlare,
                    reinterpret_cast<const void*>(callerFrame + SunFlash::kFrameOffsetLensFlareThis),
                    sizeof(lensFlare));
        if (lensFlare)
        {
            std::memcpy(&visiblePixels,
                        reinterpret_cast<const void*>(lensFlare + SunFlash::kLensFlareVisiblePixels),
                        sizeof(visiblePixels));
            std::memcpy(&scale,
                        reinterpret_cast<const void*>(lensFlare + SunFlash::kLensFlareScale),
                        sizeof(scale));
        }

        const float rebuilt = static_cast<float>(visiblePixels) * dotPow32 * scale;
        const float magnitude = std::fabs(flash) > 1.0f ? std::fabs(flash) : 1.0f;
        frameVerified = std::isfinite(rebuilt) && std::fabs(rebuilt - flash) <= 1e-3f * magnitude;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        frameVerified = false;
    }

    ++g_TraceRecords;

    const int alpha = SunFlash::WhiteoutAlpha(flash);
    const char* const saturated = flash > 1.0f ? " SATURATED" : "";
    const char* arm = g_SunFlashSuppress ? "SUPPRESSED" : "STOCK";

    if (frameVerified)
    {
        const float clamped = dot > 1.0f ? 1.0f : (dot < -1.0f ? -1.0f : dot);
        const double degrees =
            std::acos(static_cast<double>(clamped)) * 180.0 / 3.14159265358979323846;
        Log(L"[SUNFLASH] dot=%.5f angle=%.2fdeg dot^32=%.6f px=%d scale=%.6f "
            L"flash=%.4f alpha=%d/255%hs %hs\n",
            static_cast<double>(dot), degrees, static_cast<double>(dotPow32),
            visiblePixels, static_cast<double>(scale),
            static_cast<double>(flash), alpha, saturated, arm);
    }
    else
    {
        // The value itself came straight off the call site, so it stands on its
        // own; only the reconstructed inputs do not.
        Log(L"[SUNFLASH] flash=%.4f alpha=%d/255%hs %hs (frame unverified)\n",
            static_cast<double>(flash), alpha, saturated, arm);
    }
}

// __thiscall stand-in for ScreenFlash::AddFlash, installed at the sun call site
// only.
//
// On entry:   ECX     = ScreenFlash*     (the call site loads 0x0097838C)
//             [ESP+0] = return address
//             [ESP+4] = float flash      (callee-cleaned, hence the ret 4)
//             EBP     = LensFlare::Render's frame, untouched by the call
//                       sequence (push ecx / movss [esp],xmm0 / mov ecx,imm32)
//
// The pass-through path restores every register and jumps to the stock routine
// through memory, so with suppression off the behaviour is that of the
// unpatched game.
extern "C" void __declspec(naked) SunFlashAddThunk()
{
    __asm
    {
        cmp     byte ptr [g_SunFlashTrace], 0
        je      no_trace
        pushad                                      // 32 bytes: ret at +32, flash at +36
        push    dword ptr [esp + 36]                // flash
        push    ebp                                 // caller frame
        call    SunFlashTraceRecord
        add     esp, 8
        popad
    no_trace:
        cmp     byte ptr [g_SunFlashSuppress], 0
        jne     do_suppress
        inc     dword ptr [g_SunFlashPassedThroughCalls]
        jmp     dword ptr [g_SunFlashStockAddFlash] // tail call: ECX and stack intact
    do_suppress:
        inc     dword ptr [g_SunFlashSuppressedCalls]
        ret     4                                   // consume the callee-cleaned argument
    }
}

namespace
{
    // Kept separate from the retry loop so the __try body holds no C++ objects.
    bool CallSiteMatchesStock()
    {
        using namespace BZROpenShim::SunFlash;
        __try
        {
            if (*reinterpret_cast<const std::uint8_t*>(kAddFlashCallOpcodeAddr) != 0xE8)
                return false;
            const auto rel = *reinterpret_cast<const std::int32_t*>(kAddFlashCallOperandAddr);
            const auto target =
                static_cast<std::uintptr_t>(kAddFlashCallOperandAddr) + 4u + rel;
            return target == kScreenFlashAddFlashAddr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }
}

namespace BZROpenShim::SunFlash
{
    void LoadConfig()
    {
        if (g_ConfigLoaded)
            return;
        g_ConfigLoaded = true;

        bool suppress = kSuppressDefault;
        bool configured = false;

        // Canonical positive key: SunFlashbang = 1 keeps stock behaviour.
        if (TryGetUserConfigBool("Display", "SunFlashbang", configured))
            suppress = !configured;
        // The inverted spelling is accepted too, and wins when both are
        // present because it states the intent more directly.
        if (TryGetUserConfigBool("Display", "DisableSunFlashbang", configured))
            suppress = configured;

        if (EnvFlagEnabled("OPENSHIM_DISABLE_SUN_FLASHBANG"))
            suppress = true;

        g_SunFlashSuppress = suppress ? 1u : 0u;

        bool trace = false;
        if (TryGetUserConfigBool("Diagnostics", "TraceSunFlash", trace))
            g_SunFlashTrace = trace ? 1u : 0u;
        if (EnvFlagEnabled("OPENSHIM_TRACE_SUN_FLASH"))
            g_SunFlashTrace = 1u;
    }

    void ReloadConfig()
    {
        g_ConfigLoaded = false;
        LoadConfig();
    }

    bool IsSuppressionEnabled()
    {
        return g_SunFlashSuppress != 0u;
    }

    bool IsTraceEnabled()
    {
        return g_SunFlashTrace != 0u;
    }

    // Instruction-anchored identity check, run before the REL32 payload is
    // built. Guarding the operand alone would only say "these four bytes still
    // read E8 14 FA FF"; this also insists the byte in front is a CALL rel32
    // and that it resolves to ScreenFlash::AddFlash, so a build whose layout
    // moved fails closed.
    bool VerifyCallSite(int maxAttempts, unsigned delayMs)
    {
        if (maxAttempts < 1)
            maxAttempts = 1;

        for (int attempt = 0; attempt < maxAttempts; ++attempt)
        {
            if (attempt != 0)
                ::Sleep(delayMs);
            if (CallSiteMatchesStock())
            {
                g_SunFlashStockAddFlash = reinterpret_cast<void*>(kScreenFlashAddFlashAddr);
                return true;
            }
        }
        return false;
    }

    void* ThunkAddress()
    {
        return reinterpret_cast<void*>(&SunFlashAddThunk);
    }

    void SetPatchInstalled(bool installed)
    {
        g_PatchInstalled = installed;
        Log(L"[SUNFLASH] installed=%d suppress=%d trace=%d\n",
            installed ? 1 : 0,
            static_cast<int>(g_SunFlashSuppress),
            static_cast<int>(g_SunFlashTrace));
    }

    bool IsPatchInstalled()
    {
        return g_PatchInstalled;
    }

    long SuppressedCallCount()
    {
        return g_SunFlashSuppressedCalls;
    }

    long PassedThroughCallCount()
    {
        return g_SunFlashPassedThroughCalls;
    }
}
