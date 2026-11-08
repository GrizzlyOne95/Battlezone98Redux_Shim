// Main-menu banner follows the single-player 98/TRO toggle, and the mode
// survives a restart.
//
// Stock cUI_MainScreen builds its banner widget (+0x15C) with the literal
// "bzone.ogv" (push at 0x0078DEBC in the GOG 2.2.301 build). "TRO Banner
// Movie Name" points that push at g_BannerMovie instead, and the wrapper
// below runs after the SP view's mode refresh (the only writer of the TRO
// flag) to pick the name, re-point an already-built banner and save the mode
// to openshim.ini ([General] LastSinglePlayerMode).
//
// Stock keeps the mode for the session only. The refresh (FUN_007befd0) is a
// toggle: it flips the four campaign flags' visibility and sets the TRO flag
// from the Black Dog flag's (decomp lines 16-32). When the SP view is built,
// FUN_007bf440 (line 348) calls it once if the flag is already set, which
// puts the fresh view into TRO. So restoring a saved TRO mode only needs the
// flag (and the shell music track the refresh would have set) seeded before
// the first menu build; the engine does the rest.
#include "tro_menu_movie.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"
#include <Windows.h>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        using Refresh = void(__fastcall*)(void*);
        using SetMovie = void(__thiscall*)(void*, const char*, int);
        using Play = void(__thiscall*)(void*, bool);

        constexpr const char kStockMovie[] = "bzone.ogv";
        constexpr const char kTroMovie[] = "odyssey.ogv";
        // cUI_MainScreen banner widget ("movie"), created by 0x0078DDE0.
        constexpr uintptr_t kBannerWidgetOffset = 0x15C;
        // Shell music tracks FUN_007befd0 stores (decomp lines 33-39).
        constexpr int32_t k98ShellTrack = 0xC;
        constexpr int32_t kTroShellTrack = 0x1B;
        constexpr const char kIniSection[] = "General";
        constexpr const char kIniKey[] = "LastSinglePlayerMode";
        constexpr unsigned kAllSitesHooked = 0x3;

        char g_BannerMovie[16] = "bzone.ogv";
        Refresh g_Refresh = nullptr;
        SetMovie g_SetMovie = nullptr;
        Play g_Play = nullptr;
        volatile uint8_t* g_TroFlag = nullptr;
        void* const volatile* g_MainScreen = nullptr;
        bool g_Resolved = false;
        bool g_ResolveOk = false;
        unsigned g_HookedSites = 0;
        // Saving is only safe when both refresh calls run through the
        // wrapper; otherwise a saved TRO could be restored but never cleared.
        bool g_PersistEnabled = false;
        int g_SavedMode = -1;  // -1 unknown, 0 = 98, 1 = TRO
        uint32_t g_DlcManagerFn = 0;
        uint32_t g_DlcOwnedFn = 0;
        volatile int32_t* g_ShellTrack = nullptr;

        bool ResolveOnce()
        {
            if (g_Resolved) return g_ResolveOk;
            g_Resolved = true;
            const uint32_t refresh = HookEngine::ResolveNamedAddress("TroMenuMovie::SpModeRefresh");
            const uint32_t setMovie = HookEngine::ResolveNamedAddress("TroMenuMovie::SetMovie");
            const uint32_t play = HookEngine::ResolveNamedAddress("PlanetVideo::ViewPlay");
            const uint32_t flag = HookEngine::ResolveNamedAddress("TroMenuMovie::TroFlag");
            const uint32_t screen = HookEngine::ResolveNamedAddress("TroMenuMovie::MainScreen");
            if (!refresh || !setMovie || !play || !flag || !screen) {
                LogShimA(LogLevel::Warn, "TroMenuMovie",
                    "resolve failed refresh=0x%08X setMovie=0x%08X play=0x%08X flag=0x%08X screen=0x%08X; banner stays stock",
                    refresh, setMovie, play, flag, screen);
                return false;
            }
            g_Refresh = reinterpret_cast<Refresh>(static_cast<uintptr_t>(refresh));
            g_SetMovie = reinterpret_cast<SetMovie>(static_cast<uintptr_t>(setMovie));
            g_Play = reinterpret_cast<Play>(static_cast<uintptr_t>(play));
            g_TroFlag = reinterpret_cast<volatile uint8_t*>(static_cast<uintptr_t>(flag));
            g_MainScreen = reinterpret_cast<void* const volatile*>(static_cast<uintptr_t>(screen));
            g_ResolveOk = true;
            return true;
        }

        // Kept free of C++ objects so __try can guard the engine calls.
        void ApplyToBuiltBanner()
        {
            __try {
                void* screen = *g_MainScreen;
                if (!screen) return;
                void* widget = *reinterpret_cast<void**>(
                    static_cast<char*>(screen) + kBannerWidgetOffset);
                if (!widget) return;
                g_SetMovie(widget, g_BannerMovie, 0);
                g_Play(widget, true);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                LogShimA(LogLevel::Warn, "TroMenuMovie",
                    "re-pointing the built banner faulted; it keeps its movie until rebuilt");
            }
        }

        bool SetMode(uint8_t tro)
        {
            __try {
                *g_TroFlag = tro;
                if (g_ShellTrack) *g_ShellTrack = tro ? kTroShellTrack : k98ShellTrack;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                return false;
            }
        }

        using DlcManagerFn = void*(__cdecl*)();
        using DlcOwnedFn = bool(__thiscall*)(void*, int);
        constexpr int kTroDlcId = 1;

        // Same ownership test FUN_007bf440 uses before it creates the 98/TRO
        // toggle (decomp lines 173-175). -1 = could not ask: the manager is
        // created later in startup (FUN_00764f50, from FUN_00618c10) than
        // patching runs, so at restore time this is usually -1.
        int TroDlcOwned()
        {
            if (!g_DlcManagerFn || !g_DlcOwnedFn) return -1;
            __try {
                void* manager = reinterpret_cast<DlcManagerFn>(static_cast<uintptr_t>(g_DlcManagerFn))();
                if (!manager) return -1;
                return reinterpret_cast<DlcOwnedFn>(static_cast<uintptr_t>(g_DlcOwnedFn))(manager, kTroDlcId) ? 1 : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
        }

        bool MenuAlreadyBuilt()
        {
            __try { return *g_MainScreen != nullptr; }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        void SaveMode(int mode)
        {
            if (!g_PersistEnabled || mode == g_SavedMode) return;
            if (WriteShimUserConfigValue(kIniSection, kIniKey, mode ? "TRO" : "98"))
                g_SavedMode = mode;
        }

        void __fastcall TroModeRefreshHook(void* view)
        {
            // A restored TRO on an install without the DLC: the SP view built
            // no toggle (FUN_007bf440 lines 173-175) but still calls the
            // refresh because the flag is set (0x007C11F7), and the refresh
            // reads that toggle. Drop back to 98 instead; "unknown" counts as
            // not owned. With the DLC the engine's own test has just passed,
            // so this costs one lookup. The saved preference is kept, so a
            // transient failure does not reset it. Unresolved check functions
            // also block the restore, so then the flag can only have come from
            // the toggle, which exists only with the DLC: no check needed.
            bool fellBack = false;
            if (*g_TroFlag != 0 && g_DlcManagerFn && g_DlcOwnedFn && TroDlcOwned() != 1) {
                LogShimA(LogLevel::Warn, "TroMenuMovie", "TRO DLC not owned or not readable; returning to 98 mode");
                SetMode(0);
                fellBack = true;
            } else {
                g_Refresh(view);
            }
            const int mode = (*g_TroFlag != 0) ? 1 : 0;
            if (!fellBack) SaveMode(mode);
            const char* want = mode ? kTroMovie : kStockMovie;
            if (std::strcmp(g_BannerMovie, want) == 0) return;
            strcpy_s(g_BannerMovie, want);
            ApplyToBuiltBanner();
        }
    }

    const char* GetTroBannerMovieName()
    {
        return g_BannerMovie;
    }

    void* PrepareTroModeRefreshHook(uint32_t callAddress)
    {
        if (!ResolveOnce()) return nullptr;
        void* original = HookEngine::ResolveRelCallTarget(callAddress);
        if (reinterpret_cast<uintptr_t>(original) != reinterpret_cast<uintptr_t>(g_Refresh)) {
            LogShimA(LogLevel::Warn, "TroMenuMovie",
                "call 0x%08X reaches %p, not SP mode refresh %p; leaving stock call",
                callAddress, original, reinterpret_cast<void*>(g_Refresh));
            return nullptr;
        }
        return reinterpret_cast<void*>(&TroModeRefreshHook);
    }

    void NoteTroModeRefreshHookInstalled(unsigned siteIndex)
    {
        if (siteIndex < 2) g_HookedSites |= (1u << siteIndex);
    }

    void RestoreSavedTroMode()
    {
        if (g_HookedSites != kAllSitesHooked || !g_ResolveOk) {
            if (g_HookedSites != 0)
                LogShimA(LogLevel::Warn, "TroMenuMovie",
                    "only refresh sites 0x%X of 0x3 hooked; single-player mode is not saved or restored",
                    g_HookedSites);
            return;
        }
        g_PersistEnabled = true;
        // Resolved whatever the saved mode is: the refresh wrapper only
        // checks ownership when these are set.
        g_DlcManagerFn = HookEngine::ResolveNamedAddress("TroMenuMovie::DlcManager");
        g_DlcOwnedFn = HookEngine::ResolveNamedAddress("TroMenuMovie::DlcOwned");

        std::string saved;
        if (!TryGetUserConfigString(kIniSection, kIniKey, saved)) {
            g_SavedMode = -1;
            return;
        }
        saved = TrimAsciiCopy(saved);
        if (_stricmp(saved.c_str(), "TRO") != 0) {
            g_SavedMode = (_stricmp(saved.c_str(), "98") == 0) ? 0 : -1;
            return;
        }

        // Without these the SP view cannot be checked for the DLC (see
        // TroModeRefreshHook), so a TRO restore could fault there.
        if (!g_DlcManagerFn || !g_DlcOwnedFn) {
            LogShimA(LogLevel::Warn, "TroMenuMovie", "saved TRO mode not restored: TRO DLC check unresolved; starting in 98 mode");
            return;
        }
        const int owned = TroDlcOwned();
        if (owned == 0) {
            LogShimA(LogLevel::Warn, "TroMenuMovie", "saved TRO mode not restored: TRO DLC not owned; starting in 98 mode");
            return;
        }

        // The music track is cosmetic; a miss leaves the 98 shell music
        // until the single-player screen runs the refresh.
        const uint32_t track = HookEngine::ResolveNamedAddress("TroMenuMovie::ShellMusicTrack");
        g_ShellTrack = reinterpret_cast<volatile int32_t*>(static_cast<uintptr_t>(track));
        if (!SetMode(1)) {
            LogShimA(LogLevel::Warn, "TroMenuMovie", "seeding the saved TRO mode faulted; starting in 98 mode");
            return;
        }
        strcpy_s(g_BannerMovie, kTroMovie);
        g_SavedMode = 1;
        // Patching runs beside the game thread, so the menu may already be
        // up with bzone.ogv. It is not re-pointed from this thread; it
        // switches on the next menu build or SP toggle. (Ordering UNVERIFIED.)
        if (MenuAlreadyBuilt())
            LogShimA(LogLevel::Warn, "TroMenuMovie", "main menu was built before the TRO restore; banner stays 98 until it is rebuilt");
        LogShimA(LogLevel::Info, "TroMenuMovie", "restored saved TRO single-player mode (shell track %s, DLC %s)",
            track ? "set" : "unresolved", owned == 1 ? "owned" : "not known yet; checked when the SP view opens");
    }
}
