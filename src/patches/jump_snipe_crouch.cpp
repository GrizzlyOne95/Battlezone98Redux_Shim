// jump_snipe_crouch.cpp
// BZR Open Shim - jump-snipe crouch-on-landing fix (SinglePlayer tier) and
// its bridge setter, split out of bzr_hooks.cpp. The Person::Simulate
// research probe stays there; shared helpers come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Item 23: restore legacy 1.5 crouch-on-landing while sniper-selected.
        // Person::Simulate (GOG 0x0059D340) case-0 grounded branch tests the
        // held-jump flag BEFORE the sniper-selected flag, so holding jump while
        // touching ground never re-enters the crouch pose. The two adjacent
        // frame bools are jumpHeld ([ebp-0x352]) and sniperSelected
        // ([ebp-0x351]). Rewriting the predicate to "goto sniper-check iff
        // jumpHeld <= sniper" makes the (jumpHeld && sniper) case crouch like
        // 1.5 while leaving every other path byte-identical. See
        // reverse_engineering/jump_sniping_crouch_fix_20260713.md.
        constexpr uintptr_t kGogPersonCrouchBranchAddr = 0x0059DEA5;
        constexpr size_t kPersonCrouchBranchPatchLen = 11;
        // movzbl [ebp-0x352],eax ; test al,al ; je 0x59DED6
        constexpr uint8_t kPersonCrouchBranchExpected[kPersonCrouchBranchPatchLen] =
        {
            0x0F, 0xB6, 0x85, 0xAE, 0xFC, 0xFF, 0xFF, 0x85, 0xC0, 0x74, 0x26
        };
        // mov ax,[ebp-0x352] ; cmp al,ah ; jbe 0x59DED6
        constexpr uint8_t kPersonCrouchBranchPatched[kPersonCrouchBranchPatchLen] =
        {
            0x66, 0x8B, 0x85, 0xAE, 0xFC, 0xFF, 0xFF, 0x38, 0xE0, 0x76, 0x26
        };

        // Desired state starts from the INI baseline and may be overridden by
        // the EXU bridge for scripted content. The refresh gate keeps it out
        // of multiplayer.
        bool g_JumpSnipeCrouchEnabled = true;
        bool g_JumpSnipeCrouchBaselineEnabled = true;
        // Whether the byte patch is currently live in the exe image.
        static bool g_JumpSnipeCrouchPatchActive = false;

        static bool WritePersonCrouchBranchBytes(const uint8_t* bytes)
        {
            auto* target = reinterpret_cast<uint8_t*>(kGogPersonCrouchBranchAddr);
            DWORD oldProtect = 0;
            if (!VirtualProtect(target,
                                kPersonCrouchBranchPatchLen,
                                PAGE_EXECUTE_READWRITE,
                                &oldProtect))
            {
                Log(L"[JUMPSNIPE] Crouch fix VirtualProtect failed at 0x%08X\n",
                    static_cast<uint32_t>(kGogPersonCrouchBranchAddr));
                return false;
            }

            memcpy(target, bytes, kPersonCrouchBranchPatchLen);
            FlushInstructionCache(GetCurrentProcess(), target, kPersonCrouchBranchPatchLen);

            DWORD restoreProtect = 0;
            VirtualProtect(target, kPersonCrouchBranchPatchLen, oldProtect, &restoreProtect);
            return true;
        }

        // Reconciles the live byte patch with the desired state. The fix is
        // applied only when a script has enabled it AND we are not in a network
        // game (net id 0). Guarded by the exact expected/patched bytes so it
        // no-ops on any build (e.g. Steam, which relocates Person::Simulate).
        void RefreshJumpSnipeCrouchPatchState()
        {
            const bool wantActive =
                g_JumpSnipeCrouchEnabled && (ReadLocalPlayerNetIdValue() == 0);
            if (wantActive == g_JumpSnipeCrouchPatchActive)
                return;

            if (wantActive)
            {
                if (!ExpectedBytesMatchAt(kGogPersonCrouchBranchAddr,
                                          kPersonCrouchBranchExpected,
                                          sizeof(kPersonCrouchBranchExpected)))
                {
                    return;
                }
                if (WritePersonCrouchBranchBytes(kPersonCrouchBranchPatched))
                {
                    g_JumpSnipeCrouchPatchActive = true;
                    Log(L"[JUMPSNIPE] Applied legacy crouch-on-landing fix at 0x%08X (SP-only)\n",
                        static_cast<uint32_t>(kGogPersonCrouchBranchAddr));
                }
            }
            else
            {
                if (ExpectedBytesMatchAt(kGogPersonCrouchBranchAddr,
                                         kPersonCrouchBranchPatched,
                                         sizeof(kPersonCrouchBranchPatched)))
                {
                    if (WritePersonCrouchBranchBytes(kPersonCrouchBranchExpected))
                    {
                        g_JumpSnipeCrouchPatchActive = false;
                        Log(L"[JUMPSNIPE] Reverted crouch-on-landing fix at 0x%08X\n",
                            static_cast<uint32_t>(kGogPersonCrouchBranchAddr));
                    }
                }
                else
                {
                    // Bytes are not ours (unpatched or a different build);
                    // treat as inactive without touching memory.
                    g_JumpSnipeCrouchPatchActive = false;
                }
            }
        }

        // Mission-end resting state for the crouch fix: drop the scripted enable
        // back to the build default, then reconcile the live patch (which also
        // re-applies the multiplayer gate). Named to match the registry's
        // revert-to-baseline contract below.
        void RevertJumpSnipeCrouchToBaseline()
        {
            g_JumpSnipeCrouchEnabled = g_JumpSnipeCrouchBaselineEnabled;
            RefreshJumpSnipeCrouchPatchState();
        }
    }

    using namespace Hooks;

    bool SetJumpSnipeCrouchEnabledFromBridge(bool enabled)
    {
        // Scripted content can temporarily override the INI baseline. Never
        // applies in a network game; see RefreshJumpSnipeCrouchPatchState().
        g_JumpSnipeCrouchEnabled = enabled;
        RefreshJumpSnipeCrouchPatchState();
        const bool active = g_JumpSnipeCrouchPatchActive;
        Log(L"[MISSIONHOOK] jump-snipe crouch fix %hs (patch %hs)\n",
            enabled ? "enabled" : "disabled",
            active ? "active" : "inactive");
        // Report the effective state so a script can tell it was suppressed
        // (e.g. requested in multiplayer, or bytes did not match this build).
        return active == enabled;
    }
}
