// explosion_flash.cpp
// BZR Open Shim - explosion fullscreen white strobe control
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/explosion_flash.h for the static trace. Two explosion routines
// hand 3 * size / depth to the global ScreenFlash, which paints one
// fullscreen white quad for exactly one frame. This file rewrites both calls
// so that contribution can be capped (Soft) or dropped (Off) without touching
// the sun's call site or anything else the explosion draws.

#include "explosion_flash.h"

#include "bzr_options_ui.h"
#include "patcher.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <string>

namespace
{
    // Stock by default, so an unconfigured install renders as it always has.
    constexpr BZROpenShim::ExplosionFlash::Mode kDefaultMode =
        BZROpenShim::ExplosionFlash::Mode::Stock;

    bool g_ConfigLoaded = false;
}

// Read from inline asm, so file scope with unmangled names. Only the render
// thread reaches the thunk.
extern "C" volatile unsigned char g_ExplosionFlashMode =
    static_cast<unsigned char>(kDefaultMode);

// Set by VerifyCallSite. The thunk jumps through it, so a failed verify leaves
// the payload unbuilt and the stock call in place.
extern "C" void* g_ExplosionFlashStockAddFlash = nullptr;

extern "C" void __cdecl ExplosionFlashSoftAdd(std::uintptr_t screenFlash, float amount)
{
    using namespace BZROpenShim::ExplosionFlash;
    __try
    {
        auto* pending = reinterpret_cast<float*>(screenFlash + kScreenFlashPendingOffset);
        *pending = SoftPendingAfter(*pending, amount);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// __thiscall stand-in for ScreenFlash::AddFlash at the two explosion sites.
//
// On entry:   ECX     = ScreenFlash*  (the call site loads 0x0097838C)
//             [ESP+0] = return address
//             [ESP+4] = float flash   (callee-cleaned, hence the ret 4)
//
// The callers treat EAX/ECX/EDX as clobbered across this __thiscall, so the
// Soft path may call into C without saving them.
extern "C" void __declspec(naked) ExplosionFlashAddThunk()
{
    __asm
    {
        cmp     byte ptr [g_ExplosionFlashMode], 0
        jne     not_stock
        jmp     dword ptr [g_ExplosionFlashStockAddFlash] // tail call: ECX and stack intact
    not_stock:
        cmp     byte ptr [g_ExplosionFlashMode], 2
        je      drop
        push    dword ptr [esp + 4]                      // flash
        push    ecx                                      // ScreenFlash*
        call    ExplosionFlashSoftAdd
        add     esp, 8
    drop:
        ret     4                                        // consume the callee-cleaned argument
    }
}

namespace
{
    bool CallSiteMatchesStock(unsigned long opcodeAddr)
    {
        using namespace BZROpenShim::ExplosionFlash;
        __try
        {
            if (*reinterpret_cast<const std::uint8_t*>(opcodeAddr) != 0xE8)
                return false;
            // The instruction in front loads the global ScreenFlash into ECX.
            const auto* mov = reinterpret_cast<const std::uint8_t*>(opcodeAddr - 5);
            std::uint32_t instance = 0;
            std::memcpy(&instance, mov + 1, sizeof(instance));
            if (mov[0] != 0xB9 || instance != kScreenFlashInstanceAddr)
                return false;
            const auto rel = *reinterpret_cast<const std::int32_t*>(opcodeAddr + 1);
            const auto target = static_cast<std::uintptr_t>(opcodeAddr) + 5u + rel;
            return target == kScreenFlashAddFlashAddr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    const char* ModeName(unsigned char mode)
    {
        switch (static_cast<BZROpenShim::ExplosionFlash::Mode>(mode))
        {
        case BZROpenShim::ExplosionFlash::Mode::Soft: return "Soft";
        case BZROpenShim::ExplosionFlash::Mode::Off: return "Off";
        default: return "Stock";
        }
    }
}

namespace BZROpenShim::ExplosionFlash
{
    bool ParseMode(const char* text, Mode& out)
    {
        if (!text)
            return false;
        if (_stricmp(text, "Stock") == 0 || std::strcmp(text, "1") == 0)
            out = Mode::Stock;
        else if (_stricmp(text, "Soft") == 0)
            out = Mode::Soft;
        else if (_stricmp(text, "Off") == 0 || std::strcmp(text, "0") == 0)
            out = Mode::Off;
        else
            return false;
        return true;
    }

    void LoadConfig()
    {
        if (g_ConfigLoaded)
            return;
        g_ConfigLoaded = true;

        Mode mode = kDefaultMode;
        std::string text;
        if (TryGetUserConfigString("Display", "ExplosionFlash", text) &&
            !ParseMode(text.c_str(), mode))
        {
            Log(L"[EXPLFLASH] unrecognised ExplosionFlash=%hs; using Stock\n", text.c_str());
            mode = kDefaultMode;
        }
        g_ExplosionFlashMode = static_cast<unsigned char>(mode);
    }

    void ReloadConfig()
    {
        g_ConfigLoaded = false;
        LoadConfig();
    }

    bool VerifyCallSite(unsigned long site, int maxAttempts, unsigned delayMs)
    {
        if (site >= kCallSiteCount)
            return false;
        if (maxAttempts < 1)
            maxAttempts = 1;

        for (int attempt = 0; attempt < maxAttempts; ++attempt)
        {
            if (attempt != 0)
                ::Sleep(delayMs);
            if (CallSiteMatchesStock(kCallOpcodeAddrs[site]))
            {
                g_ExplosionFlashStockAddFlash = reinterpret_cast<void*>(kScreenFlashAddFlashAddr);
                return true;
            }
        }
        return false;
    }

    void* ThunkAddress()
    {
        return reinterpret_cast<void*>(&ExplosionFlashAddThunk);
    }

    void SetPatchInstalled(unsigned long site)
    {
        Log(L"[EXPLFLASH] installed site=0x%08lX mode=%hs\n",
            site < kCallSiteCount ? kCallOpcodeAddrs[site] : 0ul,
            ModeName(g_ExplosionFlashMode));
    }
}
