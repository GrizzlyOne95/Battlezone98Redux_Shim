#include "game_state.h"

#include <Windows.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        constexpr uintptr_t kMultiplayerPauseFlagAddr = 0x00945549;
        constexpr uintptr_t kMultiplayerPauseRootAddr = 0x0094557C;
        constexpr uintptr_t kSingleplayerPauseRootAddr = 0x009454EC;

        constexpr uintptr_t kUiCurrentScreenAddr = 0x00918320;
        constexpr uintptr_t kUiWrapperActiveAddr = 0x00918324;
        constexpr uintptr_t kUiCurrentScreenTypeAddr = 0x00918328;

        bool IsCursorVisible() noexcept
        {
            CURSORINFO info{};
            info.cbSize = sizeof(info);
            return GetCursorInfo(&info) && (info.flags & CURSOR_SHOWING) != 0;
        }
    }

    bool IsMultiplayerPauseMenuOpen() noexcept
    {
        __try
        {
            const auto* root = reinterpret_cast<void* const*>(kMultiplayerPauseRootAddr);
            const auto* flag = reinterpret_cast<const uint8_t*>(kMultiplayerPauseFlagAddr);
            return (*root != nullptr || *flag != 0) && IsCursorVisible();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool IsSingleplayerPauseMenuOpen() noexcept
    {
        __try
        {
            const auto* pauseRoot = reinterpret_cast<void* const*>(kSingleplayerPauseRootAddr);
            const auto* uiWrapperActive = reinterpret_cast<const uint32_t*>(kUiWrapperActiveAddr);
            const auto* uiCurrentScreen = reinterpret_cast<void* const*>(kUiCurrentScreenAddr);
            const auto* uiCurrentScreenType = reinterpret_cast<const uint32_t*>(kUiCurrentScreenTypeAddr);

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
        return IsMultiplayerPauseMenuOpen() || IsSingleplayerPauseMenuOpen();
    }

    ShellUiState ReadShellUiState() noexcept
    {
        ShellUiState state{};
        __try
        {
            const auto* uiWrapperActive = reinterpret_cast<const volatile uint32_t*>(kUiWrapperActiveAddr);
            const auto* uiCurrentScreen = reinterpret_cast<void* const volatile*>(kUiCurrentScreenAddr);
            const auto* uiCurrentScreenType =
                reinterpret_cast<const volatile uint32_t*>(kUiCurrentScreenTypeAddr);

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
