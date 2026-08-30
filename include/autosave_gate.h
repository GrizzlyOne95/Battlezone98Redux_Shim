#pragma once

// Pure decision logic for "may OpenShim call the engine's SaveGame right now?".
//
// Kept free of Windows and of the game's memory layout so the rules can be
// exercised on the host by tests/autosave_gate_tests.cpp. autosave.cpp reads
// the live globals and feeds the result in here.
//
// Why this exists as its own unit: the 2026-08-29 Steam repro showed the old
// gate (isNetGame == 0 && userObject != nullptr) calling into the engine while
// an Instant Action map was still stuck on the loading screen behind a modal
// "no file exu.dll" dialog. The engine faulted every time:
//
//   0xC0000005 read=0x00000004 at battlezone98redux.exe+0x001D7593
//
// 0x005D7580 is a string-field serializer; it does movzx ecx,[eax+4] on its
// second argument straight away, and its caller at 0x00461EB9 hands it an
// element it pulled out of a container without a null check. A half-built
// mission leaves a null in that container, so SaveGame has nothing valid to
// walk. There is no way to make that call safe from outside - it must not be
// made at all until the mission is genuinely live.

#include "game_state.h"

#include <cstdint>

namespace BZROpenShim::AutoSaveGate
{
    // Everything autosave.cpp can observe about the process before deciding.
    // Each "readable" flag records whether the corresponding probe succeeded;
    // an unreadable probe is never treated as permission to save.
    struct ObservedState
    {
        // False when any of the mission or UI globals could not be read.
        bool stateReadable = false;

        // 0x00917F7B: non-zero in a network game.
        bool netGame = false;

        // 0x00917AFC: the local player's object pointer.
        bool userObjectPresent = false;

        // The same pointer passed a vtable sanity check: it is committed and
        // readable, its first word points at readable memory, and the word
        // there points at executable memory. A pointer that fails this is not
        // a constructed C++ object, whatever the global says.
        bool userObjectPlausible = false;

        // Stock Escape UI, single- or multiplayer.
        bool pauseMenuOpen = false;

        // 0x00918324 / 0x00918320 / 0x00918328.
        bool uiWrapperActive = false;
        bool uiScreenPresent = false;
        uint32_t uiScreenType = kScreenTypeNone;

        // Only used to qualify screen types we have not classified.
        bool cursorVisible = false;

        // A previous SaveGame call in this mission raised an SEH exception.
        bool missionSaveFaulted = false;

        // Faults have exhausted the per-process budget.
        bool saveDisabledForProcess = false;
    };

    enum class Decision
    {
        // The mission is live and nothing is in the way.
        Save,
        // No single-player mission is running, or its objects are not built.
        NoLiveMission,
        // A mission is live but the shell/pause/loading UI owns the screen.
        UiBusy,
        // A probe failed; nothing may be assumed.
        StateUnreadable,
        // SaveGame already faulted; do not call it again.
        FaultLatched,
    };

    struct GateResult
    {
        Decision decision = Decision::StateUnreadable;
        // Stable, allocation-free text for the log line. Never null.
        const char* reason = "unevaluated";

        constexpr bool MaySave() const noexcept { return decision == Decision::Save; }
    };

    // Order matters: the cheapest permanent reasons first, so a log line names
    // the condition a reader can actually act on rather than a symptom of it.
    constexpr GateResult Evaluate(const ObservedState& state) noexcept
    {
        if (state.saveDisabledForProcess)
            return {Decision::FaultLatched, "SaveGame fault budget exhausted for this process"};

        if (!state.stateReadable)
            return {Decision::StateUnreadable, "mission/UI state unreadable"};

        if (state.missionSaveFaulted)
            return {Decision::FaultLatched, "SaveGame already faulted in this mission"};

        if (state.netGame)
            return {Decision::NoLiveMission, "network game"};

        if (!state.userObjectPresent)
            return {Decision::NoLiveMission, "no player object"};

        // The EXU-abort repro's specific hole: the player object exists because
        // mission load got far enough to build it, then the load aborted.
        if (!state.userObjectPlausible)
            return {Decision::NoLiveMission, "player object is not a constructed object"};

        if (state.pauseMenuOpen)
            return {Decision::UiBusy, "pause menu"};

        if (state.uiWrapperActive && state.uiScreenPresent)
        {
            // Hard gate, deliberately independent of cursor visibility. The
            // loading screen hides the cursor, which is exactly how the old
            // cursor-qualified check let a load-screen save through.
            if (IsNonGameplayScreenType(state.uiScreenType))
                return {Decision::UiBusy, DescribeScreenType(state.uiScreenType)};

            // Screen types we have not classified are only treated as shell
            // screens when the cursor is up, because a stale non-zero type is
            // observed during ordinary gameplay (see the post-mission dump
            // note in autosave.cpp) and must not suppress saving forever.
            if (state.uiScreenType != kScreenTypeNone && state.cursorVisible)
                return {Decision::UiBusy, "unclassified shell screen"};
        }

        return {Decision::Save, "mission live"};
    }

    constexpr const char* DescribeDecision(Decision decision) noexcept
    {
        switch (decision)
        {
        case Decision::Save:
            return "save";
        case Decision::NoLiveMission:
            return "no-live-mission";
        case Decision::UiBusy:
            return "ui-busy";
        case Decision::StateUnreadable:
            return "state-unreadable";
        case Decision::FaultLatched:
            return "fault-latched";
        default:
            return "unknown";
        }
    }
}
