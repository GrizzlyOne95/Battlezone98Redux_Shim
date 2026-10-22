// screen_flash.cpp
// BZR Open Shim - explosion whiteout and player damage flash controls
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/screen_flash.h for the static trace. Explosions and damage to
// the player's craft both paint a fullscreen quad through the global
// ScreenFlash. This file rewrites those calls so each effect can be reduced
// (Soft) or dropped (Off) without touching the sun's call site, scripted
// colour fades, or anything else the explosion or hit draws.

#include "screen_flash.h"

#include "bzr_options_ui.h"
#include "patcher.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <string>

namespace
{
    // Stock by default, so an unconfigured install renders as it always has.
    constexpr BZROpenShim::ScreenFlash::Mode kDefaultMode =
        BZROpenShim::ScreenFlash::Mode::Stock;

    bool g_ConfigLoaded = false;
}

// Read from inline asm, so file scope with unmangled names. Only the
// simulation/render thread reaches the thunks.
extern "C" volatile unsigned char g_ExplosionFlashMode =
    static_cast<unsigned char>(kDefaultMode);
extern "C" volatile unsigned char g_DamageFlashMode =
    static_cast<unsigned char>(kDefaultMode);
extern "C" const float g_DamageFlashSoftScale = BZROpenShim::ScreenFlash::kSoftDamageScale;

// Set by VerifyCallSite. The thunks jump through these, so a failed verify
// leaves the payload unbuilt and the stock call in place.
extern "C" void* g_ScreenFlashStockAddFlash = nullptr;
extern "C" void* g_ScreenFlashStockAddColorFlash = nullptr;

extern "C" void __cdecl ExplosionFlashSoftAdd(std::uintptr_t screenFlash, float amount)
{
    using namespace BZROpenShim::ScreenFlash;
    __try
    {
        auto* pending = reinterpret_cast<float*>(screenFlash + kPendingOffset);
        *pending = SoftPendingAfter(*pending, amount);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// __thiscall stand-in for ScreenFlash::AddFlash at the explosion sites.
//
// On entry:   ECX     = ScreenFlash*  (the call site loads 0x0097838C)
//             [ESP+0] = return address
//             [ESP+4] = float amount  (callee-cleaned, hence the ret 4)
//
// The callers treat EAX/ECX/EDX as clobbered across this __thiscall, so the
// Soft path may call into C without saving them.
extern "C" void __declspec(naked) ExplosionFlashAddThunk()
{
    __asm
    {
        cmp     byte ptr [g_ExplosionFlashMode], 0
        jne     not_stock
        jmp     dword ptr [g_ScreenFlashStockAddFlash]   // tail call: ECX and stack intact
    not_stock:
        cmp     byte ptr [g_ExplosionFlashMode], 2
        je      drop
        push    dword ptr [esp + 4]                      // amount
        push    ecx                                      // ScreenFlash*
        call    ExplosionFlashSoftAdd
        add     esp, 8
    drop:
        ret     4                                        // consume the callee-cleaned argument
    }
}

// __thiscall stand-in for ScreenFlash::AddColorFlash at the player damage
// sites. [ESP+4] = float amount, then decay, r, g, b; callee cleans 0x14.
// Soft scales the amount in place and continues to the stock routine, so the
// colour and decay the engine chose are kept. XMM0 is caller-saved.
extern "C" void __declspec(naked) DamageFlashAddThunk()
{
    __asm
    {
        cmp     byte ptr [g_DamageFlashMode], 0
        je      stock
        cmp     byte ptr [g_DamageFlashMode], 2
        je      drop
        movss   xmm0, dword ptr [esp + 4]
        mulss   xmm0, dword ptr [g_DamageFlashSoftScale]
        movss   dword ptr [esp + 4], xmm0
    stock:
        jmp     dword ptr [g_ScreenFlashStockAddColorFlash]
    drop:
        ret     0x14
    }
}

namespace
{
    bool CallSiteMatchesStock(const BZROpenShim::ScreenFlash::CallSite& site)
    {
        using namespace BZROpenShim::ScreenFlash;
        __try
        {
            const unsigned long opcodeAddr = site.opcodeAddr;
            if (*reinterpret_cast<const std::uint8_t*>(opcodeAddr) != 0xE8)
                return false;
            // The instruction in front loads the global ScreenFlash into ECX.
            const auto* mov = reinterpret_cast<const std::uint8_t*>(opcodeAddr - 5);
            std::uint32_t instance = 0;
            std::memcpy(&instance, mov + 1, sizeof(instance));
            if (mov[0] != 0xB9 || instance != kInstanceAddr)
                return false;
            const auto rel = *reinterpret_cast<const std::int32_t*>(opcodeAddr + 1);
            const auto target = static_cast<std::uintptr_t>(opcodeAddr) + 5u + rel;
            return target == site.callee;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    const char* ModeName(unsigned char mode)
    {
        switch (static_cast<BZROpenShim::ScreenFlash::Mode>(mode))
        {
        case BZROpenShim::ScreenFlash::Mode::Soft: return "Soft";
        case BZROpenShim::ScreenFlash::Mode::Off: return "Off";
        default: return "Stock";
        }
    }

    bool ParseMode(const std::string& text, BZROpenShim::ScreenFlash::Mode& out)
    {
        using BZROpenShim::ScreenFlash::Mode;
        if (_stricmp(text.c_str(), "Stock") == 0 || text == "1")
            out = Mode::Stock;
        else if (_stricmp(text.c_str(), "Soft") == 0)
            out = Mode::Soft;
        else if (_stricmp(text.c_str(), "Off") == 0 || text == "0")
            out = Mode::Off;
        else
            return false;
        return true;
    }

    unsigned char ReadMode(const char* key)
    {
        BZROpenShim::ScreenFlash::Mode mode = kDefaultMode;
        std::string text;
        if (BZROpenShim::TryGetUserConfigString("Display", key, text) && !ParseMode(text, mode))
        {
            BZROpenShim::Log(L"[SCREENFLASH] unrecognised %hs=%hs; using Stock\n", key, text.c_str());
            mode = kDefaultMode;
        }
        return static_cast<unsigned char>(mode);
    }
}

namespace BZROpenShim::ScreenFlash
{
    void LoadConfig()
    {
        if (g_ConfigLoaded)
            return;
        g_ConfigLoaded = true;
        g_ExplosionFlashMode = ReadMode("ExplosionFlash");
        g_DamageFlashMode = ReadMode("DamageFlash");
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
            if (CallSiteMatchesStock(kCallSites[site]))
            {
                if (kCallSites[site].callee == kAddFlashAddr)
                    g_ScreenFlashStockAddFlash = reinterpret_cast<void*>(kAddFlashAddr);
                else
                    g_ScreenFlashStockAddColorFlash = reinterpret_cast<void*>(kAddColorFlashAddr);
                return true;
            }
        }
        return false;
    }

    void* ThunkAddress(unsigned long site)
    {
        if (site >= kCallSiteCount)
            return nullptr;
        return kCallSites[site].effect == Effect::Explosion
            ? reinterpret_cast<void*>(&ExplosionFlashAddThunk)
            : reinterpret_cast<void*>(&DamageFlashAddThunk);
    }

    void SetPatchInstalled(unsigned long site)
    {
        if (site >= kCallSiteCount)
            return;
        const bool explosion = kCallSites[site].effect == Effect::Explosion;
        Log(L"[SCREENFLASH] installed %hs site=0x%08lX mode=%hs\n",
            explosion ? "explosion" : "damage",
            kCallSites[site].opcodeAddr,
            ModeName(explosion ? g_ExplosionFlashMode : g_DamageFlashMode));
    }
}
