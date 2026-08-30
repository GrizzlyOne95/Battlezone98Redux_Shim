#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // Validated UI-state globals for Battlezone 98 Redux v2.2.301, from
    // reverse_engineering/pause_menu_notes.md:
    //   0x00918320  current UI screen pointer
    //   0x00918324  UI wrapper active flag
    //   0x00918328  current UI screen type
    // The screen-type values below are the ones that note pins down. They live
    // here rather than in game_state.cpp because autosave_gate.h classifies the
    // same values and the two must not drift apart.
    inline constexpr uint32_t kScreenTypeNone = 0x00;
    inline constexpr uint32_t kScreenTypeOptions = 0x03;
    inline constexpr uint32_t kScreenTypePause = 0x0B;
    inline constexpr uint32_t kScreenTypeSaveGame = 0x11;
    inline constexpr uint32_t kScreenTypeLoadGame = 0x12;
    // pause_menu_notes.md labels 0x17 "restart"; the 2026-08-29 EXU-abort repro
    // reports the same value for the Loading screen. Whichever label is right,
    // it is not gameplay, and no save may be attempted while it is up.
    inline constexpr uint32_t kScreenTypeLoading = 0x17;

    // True for the shell screens above: the ones known to be up while the
    // simulation is not the thing the player is looking at.
    constexpr bool IsNonGameplayScreenType(uint32_t screenType) noexcept
    {
        switch (screenType)
        {
        case kScreenTypeOptions:
        case kScreenTypePause:
        case kScreenTypeSaveGame:
        case kScreenTypeLoadGame:
        case kScreenTypeLoading:
            return true;
        default:
            return false;
        }
    }

    constexpr const char* DescribeScreenType(uint32_t screenType) noexcept
    {
        switch (screenType)
        {
        case kScreenTypeNone:
            return "none";
        case kScreenTypeOptions:
            return "options";
        case kScreenTypePause:
            return "pause";
        case kScreenTypeSaveGame:
            return "save game";
        case kScreenTypeLoadGame:
            return "load game";
        case kScreenTypeLoading:
            return "loading/restart";
        default:
            return "other";
        }
    }

    bool IsPauseMenuOpen() noexcept;
    bool IsSingleplayerPauseMenuOpen() noexcept;
    bool IsMultiplayerPauseMenuOpen() noexcept;

    // Snapshot of the shell UI globals. Every field is only meaningful when
    // readable is true; a failed probe means the caller must assume the worst.
    struct ShellUiState
    {
        bool readable = false;
        bool wrapperActive = false;
        bool screenPresent = false;
        uint32_t screenType = kScreenTypeNone;
    };

    ShellUiState ReadShellUiState() noexcept;
}
