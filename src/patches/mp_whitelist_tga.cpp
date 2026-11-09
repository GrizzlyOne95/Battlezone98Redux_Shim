// mp_whitelist_tga.cpp
// BZR Open Shim - opt-in: let .tga files pass the multiplayer mod asset
// whitelist, so a sky/visual-only Workshop mod that ships .tga textures
// still counts as "MP safe".
//
// Stock: cWorkshop's constructor (0x00767A30) builds the whitelist
//   *.wav *.ogg *.ini *.inf *.jpg *.txt *.stb *.des *.dds *.png *.sta *mod.material
// and the per-mod check (0x0076E020) tests every non-directory file against
// it with the glob matcher at 0x0076DDF0, cdecl (const std::string* name,
// const std::string* pattern) -> bool in AL. One miss logs "UNSAFE" and
// clears mod+0x90, after which a network game will not mount the mod.
//
// This detours the matcher (its only caller is that loop): when the original
// says no, a name ending in ".tga" is accepted. On by default; off with
// [Network] AllowTgaInMultiplayerMods = 0.
//
// Multiplayer consistency: the whitelist is evaluated by each client for its
// own installed copy. Peers that do not enable this still treat a mod that
// holds a .tga as UNSAFE and do not mount it, so they see stock visuals while
// the enabling peer sees the mod's. The engine never names ".tga" (no such
// string anywhere in the Redux decompile) and terrain is .trn/.hg2/.mat/.lgt,
// so the simulation does not read these files; the cost is mismatched visuals
// between peers, not desync.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            using FnWhitelistMatch = unsigned char(__cdecl*)(const void* name, const void* pattern);

            // push ebp / mov ebp,esp / push -1 / push <SEH handler>: 10 bytes,
            // whole instructions only.
            constexpr size_t kMatcherPatchLen = 10;
            constexpr uint8_t kMatcherStock[kMatcherPatchLen] =
                { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x18, 0x52, 0x84, 0x00 };

            InlineDetour32 g_MatcherDetour = {};
            FnWhitelistMatch g_OrigMatcher = nullptr;
            volatile bool g_AllowTga = false;
            bool g_ConfigInitialized = false;

            // MSVC120 std::string: 16-byte SSO buffer or pointer, size at +0x10,
            // capacity at +0x14 (24 bytes, matching the decompile's locals).
            bool ReadStdString(const void* s, const char*& data, uint32_t& len)
            {
                if (!s)
                    return false;
                const auto* b = static_cast<const uint8_t*>(s);
                uint32_t size = 0, cap = 0;
                std::memcpy(&size, b + 0x10, 4);
                std::memcpy(&cap, b + 0x14, 4);
                if (size > 4096 || cap < size)
                    return false;
                if (cap >= 16)
                {
                    const char* p = nullptr;
                    std::memcpy(&p, b, sizeof(p));
                    if (!p)
                        return false;
                    data = p;
                }
                else
                {
                    data = reinterpret_cast<const char*>(b);
                }
                len = size;
                return true;
            }

            bool EndsWithTga(const char* d, uint32_t n)
            {
                if (n < 5)
                    return false;
                const char* e = d + n - 4;
                return e[0] == '.' && (e[1] | 0x20) == 't' && (e[2] | 0x20) == 'g' && (e[3] | 0x20) == 'a';
            }

            unsigned char __cdecl MatcherHook(const void* name, const void* pattern)
            {
                if (g_OrigMatcher(name, pattern))
                    return 1;
                if (g_AllowTga)
                {
                    const char* d = nullptr;
                    uint32_t n = 0;
                    if (ReadStdString(name, d, n) && EndsWithTga(d, n))
                        return 1;
                }
                return 0;
            }

            void InstallMatcherDetour()
            {
                if (g_OrigMatcher)
                    return;
                const uintptr_t addr = HookEngine::EngineAddress("MpWhitelistMatch");
                if (addr == 0)
                {
                    Log(L"[MPTGA] MpWhitelistMatch did not resolve; leaving the stock whitelist\n");
                    return;
                }
                if (!ExpectedBytesMatchAt(addr, kMatcherStock, sizeof(kMatcherStock)))
                {
                    Log(L"[MPTGA] Matcher bytes at 0x%08X are not stock; standing down\n",
                        static_cast<uint32_t>(addr));
                    return;
                }
                if (!InstallInlineDetour32(g_MatcherDetour, addr, reinterpret_cast<void*>(MatcherHook),
                                           kMatcherPatchLen, kMatcherStock, sizeof(kMatcherStock)))
                {
                    Log(L"[MPTGA] Detour install failed at 0x%08X\n", static_cast<uint32_t>(addr));
                    return;
                }
                g_OrigMatcher = reinterpret_cast<FnWhitelistMatch>(g_MatcherDetour.trampoline);
                Log(L"[MPTGA] Whitelist matcher hooked at 0x%08X\n", static_cast<uint32_t>(addr));
            }
        }

        void InitializeMpWhitelistTgaConfig()
        {
            if (g_ConfigInitialized)
                return;
            g_ConfigInitialized = true;
            bool cfg = true;
            TryGetUserConfigBool(kUserConfigNetworkSection, "AllowTgaInMultiplayerMods", cfg);
            const bool on = cfg;
            g_AllowTga = on;
            Log(L"[MPTGA] AllowTgaInMultiplayerMods=%hs\n", on ? "on" : "off");
            if (on)
                InstallMatcherDetour();
        }

        void ReloadMpWhitelistTgaConfig()
        {
            g_ConfigInitialized = false;
            InitializeMpWhitelistTgaConfig();
        }
    }
}
