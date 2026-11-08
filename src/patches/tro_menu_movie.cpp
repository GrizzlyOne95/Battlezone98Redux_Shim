// Main-menu banner follows the single-player 98/TRO toggle.
//
// Stock cUI_MainScreen builds its banner widget (+0x15C) with the literal
// "bzone.ogv" (push at 0x0078DEBC in the GOG 2.2.301 build). "TRO Banner
// Movie Name" points that push at g_BannerMovie instead, and the wrapper
// below runs after the SP view's mode refresh (the only writer of the TRO
// flag) to pick the name and re-point an already-built banner.
//
// The flag is process state only: a fresh launch shows the 98 banner until
// the single-player screen has been opened once.
#include "tro_menu_movie.h"
#include "hook_engine.h"
#include "shim_log.h"
#include <Windows.h>
#include <cstring>

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

        char g_BannerMovie[16] = "bzone.ogv";
        Refresh g_Refresh = nullptr;
        SetMovie g_SetMovie = nullptr;
        Play g_Play = nullptr;
        const volatile uint8_t* g_TroFlag = nullptr;
        void* const volatile* g_MainScreen = nullptr;
        bool g_Resolved = false;
        bool g_ResolveOk = false;

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
            g_TroFlag = reinterpret_cast<const volatile uint8_t*>(static_cast<uintptr_t>(flag));
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

        void __fastcall TroModeRefreshHook(void* view)
        {
            g_Refresh(view);
            const char* want = (*g_TroFlag != 0) ? kTroMovie : kStockMovie;
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
}
