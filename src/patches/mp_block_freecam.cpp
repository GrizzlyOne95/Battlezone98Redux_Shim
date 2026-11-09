// mp_block_freecam.cpp
// BZR Open Shim - Block Free Camera in Multiplayer (Network section).
//
// GK 9 (FREE_EYE_VIEW, Shift/Ctrl+F11) detaches the camera from the player's
// craft so it can scout the map. The game-key handler 0x0061DC10 sends GK
// 6/7/8/9/0x2A through one call, `SetViewMode(player, gk)` at 0x0061DDF8. In a
// network game that call is only reached while the player controls an object.
// This wraps that single call site and drops mode 9 in a network game.
//
// Other SetViewMode callers (vehicle-enter default view, the GK 1-5 path) are
// untouched, so cockpit/chase switching and any dead-player or spectator
// camera that goes through them keep working. A player already in free eye
// is left alone, so a stuck camera can still be left with the view keys.
//
// This is client-local enforcement: a modified client skips it.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "shim_log.h"

#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            constexpr const char* kComponent = "freecam";
            constexpr int kFreeEyeMode = 9;
            // Call at row + 8: push gk; push player; call SetViewMode.
            constexpr uint32_t kCallOffset = 8;

            using FnSetViewMode = void(__cdecl*)(void* player, int mode);
            FnSetViewMode g_SetViewMode = nullptr;
            uint32_t g_IsNetGameAddr = 0;
            uint32_t g_CurrentViewModeAddr = 0;
            bool g_LoggedBlock = false;

            bool BlockEnabled()
            {
                bool value = true; // default on; the ini is only a kill switch
                TryGetUserConfigBool(kUserConfigNetworkSection, "BlockFreeCamInMultiplayer", value);
                return value;
            }

            void __cdecl SetViewModeHook(void* player, int mode)
            {
                if (mode == kFreeEyeMode &&
                    *reinterpret_cast<const volatile uint8_t*>(static_cast<uintptr_t>(g_IsNetGameAddr)) != 0 &&
                    *reinterpret_cast<const volatile int*>(static_cast<uintptr_t>(g_CurrentViewModeAddr)) != kFreeEyeMode &&
                    BlockEnabled())
                {
                    if (!g_LoggedBlock)
                    {
                        g_LoggedBlock = true;
                        LogShimA(LogLevel::Info, kComponent,
                                 "[MPFREECAM] Free camera blocked in multiplayer "
                                 "(Network BlockFreeCamInMultiplayer=0 to allow)");
                    }
                    return;
                }
                g_SetViewMode(player, mode);
            }
        }

        void InitializeMpBlockFreeCam()
        {
            static bool initialized = false;
            if (initialized)
                return;
            initialized = true;

            uint32_t setViewMode = 0, site = 0;
            const HookEngine::EngineRow rows[] = {
                { "SetViewMode", &setViewMode },
                { "GameKeyViewSetCall", &site },
                { "CurrentViewMode", &g_CurrentViewModeAddr },
                { "IsNetGameFlag", &g_IsNetGameAddr },
            };
            if (!HookEngine::BindEngineRows("MP free camera block", rows))
                return;

            g_SetViewMode = reinterpret_cast<FnSetViewMode>(static_cast<uintptr_t>(setViewMode));
            if (!RedirectCallTarget(site + kCallOffset, setViewMode,
                                    reinterpret_cast<uintptr_t>(&SetViewModeHook)))
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[MPFREECAM] stands down: call at 0x%08X does not target SetViewMode 0x%08X",
                         site + kCallOffset, setViewMode);
                g_SetViewMode = nullptr;
                return;
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[MPFREECAM] installed (default on; Network BlockFreeCamInMultiplayer=%d)",
                     BlockEnabled() ? 1 : 0);
        }
    }
}
