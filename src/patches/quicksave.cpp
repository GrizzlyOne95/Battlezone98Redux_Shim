// quicksave.cpp
// BZR Open Shim - QuickSave / QuickLoad (default Ctrl+Home / Ctrl+End, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// QuickSave writes Save\quick.sav (+ quick.label.txt) through the AutoSave
// service's SaveGame call and gate (autosave.h SaveMissionNow). QuickLoad
// mirrors the stock load-game key handler FUN_004fbd50 (reached from the
// command dispatch FUN_0061dc10 case 0xE in single player): it copies the
// save path into the queued-load path buffer DAT_00945708 (patches.json
// "QueuedLoadPathBuffer") and calls SetShellState(8) = FUN_00434170(8); state
// 8 then loads that path in FUN_006170a0. The stock handler also clears
// DAT_009467b4, a sim-startup flag that FUN_00617110 raises at its start and
// always clears before returning (decompile lines 13 and 23); it is already 0
// whenever a mission is running, so this file does not write it.
//
// Key input. The main WndProc FUN_00619340 hands WM_KEYDOWN/WM_KEYUP to
// FUN_00619be0, which feeds FUN_00434bf0(scancode, down) and then drains the
// rest of the queued keyboard messages itself with
// PeekMessageA(0x100..0x109, PM_REMOVE) (FUN_00619be0 decompile line 58),
// bypassing any window procedure. So the chord is filtered in two places that
// share one swallow state: a subclass of the game window (messages dispatched
// by any pump) and the exe's PeekMessageA import (messages that drain loop and
// the main pump FUN_006192b0 remove). The decision itself is the pure
// QuickSaveKeyPolicy (include/quicksave_key_policy.h).

#include "quicksave.h"
#include "quicksave_key_policy.h"
#include "autosave.h"
#include "autosave_notice.h"
#include "bzr_hooks_internal.h"
#include "iat_patch.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <atomic>
#include <cstring>
#include <filesystem>
#include <string>

namespace BZROpenShim::QuickSave
{
    namespace
    {
        constexpr int kLoadSaveState = 8;
        // A request older than this is from a frame that never ticked (the
        // mission ended under it) and is dropped rather than run later.
        constexpr ULONGLONG kRequestMaxAgeMs = 1000;
        // Keys are only taken while the world is updating; in the shell and on
        // the loading screen Ctrl+Home/End reach the game as stock.
        constexpr ULONGLONG kTickFreshMs = 500;

        enum Request : LONG
        {
            kNone = 0,
            kSave = 1,
            kLoad = 2,
        };

        std::atomic<bool> g_enabled{true};
        std::atomic<ULONGLONG> g_lastTickMs{0};
        std::atomic<LONG> g_request{kNone};
        std::atomic<ULONGLONG> g_requestTickMs{0};

        // Main (window) thread only: both filters run there, and so does the
        // key-binding editor that calls SetChordText.
        QuickSaveKeyPolicy::SwallowState g_swallow;
        QuickSaveKeyPolicy::Chords g_chords;
        std::string g_saveText = QuickSaveKeyPolicy::kDefaultSaveText;
        std::string g_loadText = QuickSaveKeyPolicy::kDefaultLoadText;

        HWND g_window = nullptr;
        WNDPROC g_prevWndProc = nullptr;
        bool g_subclassAttempted = false;
        bool g_peekAttempted = false;

        using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
        PFN_PeekMessageA g_realPeekMessageA = nullptr;

        bool KeyFilterActive()
        {
            return g_enabled.load(std::memory_order_relaxed) &&
                   GetTickCount64() - g_lastTickMs.load(std::memory_order_relaxed) <= kTickFreshMs;
        }

        // True when the message must be dropped.
        bool FilterKeyMessage(UINT msg, WPARAM wParam, LPARAM lParam)
        {
            using namespace QuickSaveKeyPolicy;
            if (msg != kWmKeyDown && msg != kWmKeyUp && msg != kWmSysKeyDown && msg != kWmSysKeyUp)
                return false;
            if (!IsChordKey(g_chords, static_cast<unsigned>(wParam)))
                return false;

            KeyMessage key;
            key.msg = msg;
            key.vk = static_cast<unsigned>(wParam);
            key.autorepeat = (static_cast<unsigned long>(lParam) & (1UL << 30)) != 0;
            key.extended = (static_cast<unsigned long>(lParam) & (1UL << 24)) != 0;
            key.ctrl = GetKeyState(VK_CONTROL) < 0;
            key.shift = GetKeyState(VK_SHIFT) < 0;
            key.alt = GetKeyState(VK_MENU) < 0;

            const Action action = Decide(key, g_chords, KeyFilterActive(), g_swallow);
            if (action == Action::Pass)
                return false;
            if (action == Action::SwallowRequestSave || action == Action::SwallowRequestLoad)
            {
                g_requestTickMs.store(GetTickCount64(), std::memory_order_relaxed);
                g_request.store(action == Action::SwallowRequestSave ? kSave : kLoad,
                                std::memory_order_release);
            }
            return true;
        }

        LRESULT CALLBACK QuickSaveWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
        {
            if (FilterKeyMessage(msg, w, l))
                return 0;
            return g_prevWndProc ? CallWindowProcA(g_prevWndProc, h, msg, w, l) : DefWindowProcA(h, msg, w, l);
        }

        BOOL WINAPI QuickSavePeekMessageA(LPMSG msg, HWND hwnd, UINT minFilter, UINT maxFilter, UINT remove)
        {
            for (;;)
            {
                const BOOL got = g_realPeekMessageA
                    ? g_realPeekMessageA(msg, hwnd, minFilter, maxFilter, remove)
                    : FALSE;
                // Only a removed message can be dropped; a peek without
                // PM_REMOVE leaves it for the removing call to filter.
                if (!got || !msg || (remove & PM_REMOVE) == 0 ||
                    !FilterKeyMessage(msg->message, msg->wParam, msg->lParam))
                {
                    return got;
                }
            }
        }

        struct FindCtx
        {
            HWND found = nullptr;
        };

        BOOL CALLBACK FindGameWindowCb(HWND h, LPARAM context)
        {
            char title[256] = {};
            GetWindowTextA(h, title, sizeof(title));
            if (std::strstr(title, "Battlezone 98 Redux"))
            {
                reinterpret_cast<FindCtx*>(context)->found = h;
                return FALSE;
            }
            return TRUE;
        }

        void EnsureKeyFilters()
        {
            if (!g_peekAttempted)
            {
                g_peekAttempted = true;
                const IatPatch::Result result = IatPatch::PatchImportFromAnyDll(
                    GetModuleHandleW(nullptr), "PeekMessageA",
                    reinterpret_cast<void*>(&QuickSavePeekMessageA),
                    reinterpret_cast<void**>(&g_realPeekMessageA));
                if (result != IatPatch::Result::Patched)
                    LogShimA(LogLevel::Warn, "quicksave",
                             "PeekMessageA import not patched; a chord queued behind another key can reach the game");
            }

            if (g_window || g_subclassAttempted)
                return;
            FindCtx ctx;
            EnumThreadWindows(GetCurrentThreadId(), FindGameWindowCb, reinterpret_cast<LPARAM>(&ctx));
            if (!ctx.found)
                return; // try again next tick
            g_subclassAttempted = true;
            SetLastError(ERROR_SUCCESS);
            const auto prev = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(
                ctx.found, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&QuickSaveWndProc)));
            if (!prev && GetLastError() != ERROR_SUCCESS)
            {
                LogShimA(LogLevel::Warn, "quicksave", "Could not subclass the game window (error=%lu)",
                         GetLastError());
                return;
            }
            g_prevWndProc = prev;
            g_window = ctx.found;
            LogShimA(LogLevel::Info, "quicksave",
                     "QuickSave (%s) / QuickLoad (%s) active (hwnd=%p previous=%p)", g_saveText.c_str(),
                     g_loadText.c_str(), ctx.found, prev);
        }

        void RunQuickSave()
        {
            const char* reason = nullptr;
            // Outside a live mission, or with the pause/shell UI up, a refusal
            // is only logged: a HUD notice would wait for the next HUD frame.
            if (!IsMissionLiveForLoad(reason))
            {
                LogShimA(LogLevel::Info, "quicksave", "QuickSave refused: %s", reason);
                return;
            }
            switch (SaveMissionNow(kSlotStem, "QuickSave", "Game quicksaved.", reason))
            {
            case MissionSaveResult::Saved:
                LogShimA(LogLevel::Info, "quicksave", "QuickSave written");
                break;
            case MissionSaveResult::Refused:
                LogShimA(LogLevel::Info, "quicksave", "QuickSave refused: %s", reason);
                AutoSaveNotice::Show("QuickSave not available yet.");
                break;
            case MissionSaveResult::Failed:
                LogShimA(LogLevel::Warn, "quicksave", "QuickSave failed: %s", reason);
                AutoSaveNotice::Show("QuickSave failed.");
                break;
            }
        }

        std::filesystem::path QuickSavePath()
        {
            char modulePath[MAX_PATH]{};
            const DWORD length = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};
            return std::filesystem::path(std::string(modulePath, length)).parent_path() / "Save" /
                   (std::string(kSlotStem) + ".sav");
        }

        // POD-only so __try is allowed. FUN_004fbd50: the path into
        // DAT_00945708, then SetShellState(8).
        bool QueueLoadAndSetState(char* queuedPath, const char* path) noexcept
        {
            __try
            {
                strncpy_s(queuedPath, MAX_PATH, path, _TRUNCATE);
                g_BzrFn_SetShellState(kLoadSaveState);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void RunQuickLoad()
        {
            const char* reason = nullptr;
            if (!IsMissionLiveForLoad(reason))
            {
                LogShimA(LogLevel::Info, "quicksave", "QuickLoad refused: %s", reason);
                return;
            }

            const std::filesystem::path path = QuickSavePath();
            std::error_code error;
            if (path.empty() || !std::filesystem::exists(path, error))
            {
                LogShimA(LogLevel::Info, "quicksave", "QuickLoad: no %s", path.string().c_str());
                AutoSaveNotice::Show("No quicksave.");
                return;
            }

            auto* queuedPath = reinterpret_cast<char*>(Hooks::QueuedLoadPathBufferAddr());
            if (!queuedPath || !g_BzrFn_SetShellState)
            {
                LogShimA(LogLevel::Warn, "quicksave",
                         "QuickLoad unavailable: queued-load buffer or SetShellState did not bind");
                return;
            }

            const std::string pathText = path.string();
            if (pathText.size() >= MAX_PATH)
            {
                LogShimA(LogLevel::Warn, "quicksave", "QuickLoad path too long: %s", pathText.c_str());
                return;
            }

            if (!QueueLoadAndSetState(queuedPath, pathText.c_str()))
            {
                LogShimA(LogLevel::Error, "quicksave", "QuickLoad raised an exception");
                return;
            }
            LogShimA(LogLevel::Info, "quicksave", "QuickLoad queued for stock save-load state path=%s",
                     pathText.c_str());
        }
    }

    void LoadConfig(const char* iniPath)
    {
        const bool enabled = GetPrivateProfileIntA("QuickSave", "QuickSaveEnabled", 1, iniPath) != 0;
        g_enabled.store(enabled, std::memory_order_relaxed);

        char saveText[64] = {};
        char loadText[64] = {};
        GetPrivateProfileStringA("QuickSave", "SaveKey", QuickSaveKeyPolicy::kDefaultSaveText, saveText,
                                 sizeof(saveText), iniPath);
        GetPrivateProfileStringA("QuickSave", "LoadKey", QuickSaveKeyPolicy::kDefaultLoadText, loadText,
                                 sizeof(loadText), iniPath);
        const QuickSaveKeyPolicy::ResolvedChords resolved = QuickSaveKeyPolicy::ResolveChords(saveText, loadText);
        if (resolved.saveProblem)
            LogShimA(LogLevel::Warn, "quicksave", "[QuickSave] SaveKey=\"%s\" ignored (%s); using %s", saveText,
                     resolved.saveProblem, QuickSaveKeyPolicy::kDefaultSaveText);
        if (resolved.loadProblem)
            LogShimA(LogLevel::Warn, "quicksave", "[QuickSave] LoadKey=\"%s\" ignored (%s); using %s", loadText,
                     resolved.loadProblem, QuickSaveKeyPolicy::kDefaultLoadText);
        g_chords = resolved.chords;
        // Same as SetChordText: a mark left by an old chord could never clear.
        g_swallow = QuickSaveKeyPolicy::SwallowState{};
        g_saveText = resolved.saveProblem ? QuickSaveKeyPolicy::kDefaultSaveText : saveText;
        g_loadText = resolved.loadProblem ? QuickSaveKeyPolicy::kDefaultLoadText : loadText;
        // A collision reverts both to defaults, whatever the strings said.
        if (resolved.saveProblem && resolved.loadProblem)
        {
            g_saveText = QuickSaveKeyPolicy::kDefaultSaveText;
            g_loadText = QuickSaveKeyPolicy::kDefaultLoadText;
        }
        // The rally key was first checked against the default chords (its
        // config is read earlier at startup); check it again against these.
        Hooks::ResolveRallyKeyFromConfig();
    }

    const char* ChordText(bool save)
    {
        return (save ? g_saveText : g_loadText).c_str();
    }

    const char* SetChordText(bool save, const char* text)
    {
        using namespace QuickSaveKeyPolicy;
        Chord chord;
        if (const char* reason = CheckChordText(text, save ? g_chords.load : g_chords.save, chord))
            return reason;
        if (Hooks::RallyKeyClashesWithChord(chord))
            return "Shift plus the rally key clears the rally point";
        (save ? g_chords.save : g_chords.load) = chord;
        (save ? g_saveText : g_loadText) = text;
        // Decide matches by the new keys only, so a mark left by the old chord
        // could never be cleared by a key-up: drop it.
        g_swallow = SwallowState{};
        LogShimA(LogLevel::Info, "quicksave", "%s rebound to %s", save ? "QuickSave" : "QuickLoad", text);
        return nullptr;
    }

    bool IsEnabled()
    {
        return g_enabled.load(std::memory_order_relaxed);
    }

    void Tick()
    {
        const ULONGLONG now = GetTickCount64();
        if (!IsEnabled())
        {
            g_request.store(kNone, std::memory_order_relaxed);
            return;
        }
        g_lastTickMs.store(now, std::memory_order_relaxed);
        EnsureKeyFilters();

        const LONG request = g_request.exchange(kNone, std::memory_order_acquire);
        if (request == kNone)
            return;
        if (now - g_requestTickMs.load(std::memory_order_relaxed) > kRequestMaxAgeMs)
        {
            LogShimA(LogLevel::Info, "quicksave", "Dropped a stale %s request",
                     request == kSave ? "QuickSave" : "QuickLoad");
            return;
        }
        if (request == kSave)
            RunQuickSave();
        else
            RunQuickLoad();
    }
}
