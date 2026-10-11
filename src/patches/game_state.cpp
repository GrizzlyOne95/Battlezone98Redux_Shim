#include "game_state.h"
#include "hook_engine.h"

#include <Windows.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        // engine_addresses rows, bound together; every probe reads "not
        // open" / unreadable when they do not bind on this build.
        uint32_t g_MultiplayerPauseFlagAddr = 0;
        uint32_t g_MultiplayerPauseRootAddr = 0;
        uint32_t g_SingleplayerPauseRootAddr = 0;

        uint32_t g_UiCurrentScreenAddr = 0;
        uint32_t g_UiWrapperActiveAddr = 0;
        uint32_t g_UiCurrentScreenTypeAddr = 0;

        bool GameStateAddressesBound() noexcept
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "MultiplayerPauseFlag", &g_MultiplayerPauseFlagAddr },
                    { "MultiplayerPauseRoot", &g_MultiplayerPauseRootAddr },
                    { "SingleplayerPauseRoot", &g_SingleplayerPauseRootAddr },
                    { "UiPerfShellWrapperGlobal", &g_UiCurrentScreenAddr },
                    { "UiWrapperActive", &g_UiWrapperActiveAddr },
                    { "UiCurrentScreenType", &g_UiCurrentScreenTypeAddr },
                };
                return HookEngine::BindEngineRows("Game state probes", rows);
            }();
            return bound;
        }

        bool IsCursorVisible() noexcept
        {
            CURSORINFO info{};
            info.cbSize = sizeof(info);
            return GetCursorInfo(&info) && (info.flags & CURSOR_SHOWING) != 0;
        }
    }

    bool IsMultiplayerPauseMenuOpen() noexcept
    {
        if (!GameStateAddressesBound()) return false;
        __try
        {
            const auto* root = reinterpret_cast<void* const*>(g_MultiplayerPauseRootAddr);
            const auto* flag = reinterpret_cast<const uint8_t*>(g_MultiplayerPauseFlagAddr);
            return (*root != nullptr || *flag != 0) && IsCursorVisible();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool IsSingleplayerPauseMenuOpen() noexcept
    {
        if (!GameStateAddressesBound()) return false;
        __try
        {
            const auto* pauseRoot = reinterpret_cast<void* const*>(g_SingleplayerPauseRootAddr);
            const auto* uiWrapperActive = reinterpret_cast<const uint32_t*>(g_UiWrapperActiveAddr);
            const auto* uiCurrentScreen = reinterpret_cast<void* const*>(g_UiCurrentScreenAddr);
            const auto* uiCurrentScreenType = reinterpret_cast<const uint32_t*>(g_UiCurrentScreenTypeAddr);

            if (*pauseRoot == nullptr || *uiWrapperActive == 0)
            {
                return false;
            }

            if (*uiCurrentScreen == *pauseRoot)
            {
                return true;
            }

            return IsNonGameplayScreenType(*uiCurrentScreenType);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool IsPauseMenuOpen() noexcept
    {
        if (!GameStateAddressesBound()) return false;
        return IsMultiplayerPauseMenuOpen() || IsSingleplayerPauseMenuOpen();
    }

    ShellUiState ReadShellUiState() noexcept
    {
        if (!GameStateAddressesBound()) return {};
        ShellUiState state{};
        __try
        {
            const auto* uiWrapperActive = reinterpret_cast<const volatile uint32_t*>(g_UiWrapperActiveAddr);
            const auto* uiCurrentScreen = reinterpret_cast<void* const volatile*>(g_UiCurrentScreenAddr);
            const auto* uiCurrentScreenType =
                reinterpret_cast<const volatile uint32_t*>(g_UiCurrentScreenTypeAddr);

            state.wrapperActive = *uiWrapperActive != 0;
            state.screenPresent = *uiCurrentScreen != nullptr;
            state.screenType = *uiCurrentScreenType;
            state.readable = true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            state = {};
        }
        return state;
    }
}
