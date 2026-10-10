// prelobby_screen.cpp
// BZR Open Shim - the multiplayer pre-lobby shell screen ([Network] PreLobby):
// nickname, flag and server status before the lobby, on a screen built like
// the stock ones (shell_screens.cpp). With the setting on, Click_MultiPlayer
// asks the shell for this screen instead of the lobby; Continue applies a
// changed nickname, waits for the BZRNet connection to authorise, and then
// runs the original Click_MultiPlayer, so the stock prechecks and the push of
// the lobby (screen 0x0E) are unchanged. The lobby pushes on top of this
// screen, and Back from the lobby returns here.
//
// The panel art is resources/ui/custom_widgets/osh_prelobby_center.png,
// painted by mkscreens.py. Its title plate and two boxes are the layout
// contract with the constants below; change both together.

#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "net_optimizer.h"
#include "patcher.h"
#include "shell_screens.h"

#include <windows.h>

#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool RedirectCallTarget(uintptr_t callAddress,
                                uintptr_t originalTarget,
                                uintptr_t desiredTarget);
    }

    void __fastcall PreLobbyClickMultiPlayerHook(void* thisPtr, void* /*edx*/);
    void __fastcall PreLobbyMpStatusRefreshHook(void* thisPtr, void* /*edx*/);

    namespace
    {
        namespace Shell = ShellScreens;

        constexpr const char* kPreLobbyPanelTexture = "osh_prelobby_center.png";

        // mkscreens.py PRELOBBY_LAYOUT.
        constexpr Shell::Rect kTitleRect = { 470.0f, 132.0f, 500.0f, 56.0f };
        constexpr Shell::Rect kPlayerBox = { 244.0f, 238.0f, 952.0f, 330.0f };
        constexpr Shell::Rect kConnectionBox = { 244.0f, 596.0f, 952.0f, 200.0f };
        constexpr float kBoxHeaderH = 44.0f;   // painted header band
        constexpr float kBoxPadX = 28.0f;
        constexpr float kRowTop = 62.0f;       // first row, below the header band
        constexpr float kRowH = 46.0f;

        // Inside the PLAYER box the nickname panel (240x144) and the flag
        // picker (224x170 preview, 8 gap, 48x51 arrows: 229 tall) each sit
        // centred in a half of the box, starting kRowTop below its top.
        constexpr float kNicknameW = 240.0f;
        constexpr float kNicknameH = 144.0f;
        constexpr float kFlagW = 224.0f;
        constexpr float kFlagColumnH = 229.0f;
        constexpr float kFlagPreviewToArrows = 178.0f;  // 170 high plus the 8 gap
        constexpr float kColumnTop = kPlayerBox.y + kRowTop - 4.0f;
        constexpr float kNicknameX = kPlayerBox.x + (kPlayerBox.w * 0.5f - kNicknameW) * 0.5f;
        constexpr float kNicknameY = kColumnTop + (kFlagColumnH - kNicknameH) * 0.5f;
        constexpr float kFlagX = kPlayerBox.x + kPlayerBox.w * 0.5f + (kPlayerBox.w * 0.5f - kFlagW) * 0.5f;
        constexpr float kFlagArrowsY = kColumnTop + kFlagPreviewToArrows;

        constexpr Shell::Rect kHintRect = { 244.0f, 816.0f, 952.0f, 46.0f };

        // The stock top-corner Back button, as Career builds it.
        constexpr Shell::Rect kBackRect = { 0.0f, 0.0f, 342.0f, 77.0f };
        constexpr float kBackTextOffset = 28.0f;

        // Continue: the stock 369x68 "to main menu" skin, bottom-centre.
        constexpr Shell::Rect kContinueRect = { (1440.0f - 369.0f) * 0.5f, 900.0f, 369.0f, 68.0f };

        constexpr ULONGLONG kConnectTimeoutMs = 20000;
        // After a recycle the old authorisation is still readable until the
        // socket's close handler runs; wait for it to drop (or this long)
        // before trusting a non-zero isNetworkInit.
        constexpr ULONGLONG kDropGraceMs = 2000;

        constexpr uintptr_t kMainScreenMpStatusRefreshAddr = 0x0078EB50;
        constexpr size_t kMainScreenMpButtonOffset = 0x170;
        constexpr size_t kUiButtonEnabledOffset = 0x148;

        // Page state. Cleared when the screen closes.
        void* g_NetworkLabel = nullptr;
        bool g_Pending = false;
        bool g_AwaitDrop = false;
        bool g_InContinue = false;
        ULONGLONG g_PendingSince = 0;
        char g_Note[64] = {};
        char g_Server[96] = {};
        char g_NetworkShown[128] = {};

        using FnClickMultiPlayer = void(__thiscall*)(void* screen);
        InlineDetour32 g_ClickDetour = {};
        FnClickMultiPlayer g_ClickOriginal = nullptr;
        bool g_ClickHookInstalled = false;
        bool g_MpStatusHookInstalled = false;
        bool g_Registered = false;

        void SetNote(const char* note)
        {
            _snprintf_s(g_Note, _TRUNCATE, "%s", note ? note : "");
        }

        void ReadServerName()
        {
            char redirect[80] = {};
            if (GetMatchmakingRedirectTarget(redirect, sizeof(redirect)) && redirect[0])
                _snprintf_s(g_Server, _TRUNCATE, "Server: %s (custom server)", redirect);
            else
                _snprintf_s(g_Server, _TRUNCATE, "Server: Official");
        }

        // The Network line. Rewritten only when the text changes: this runs
        // from the per-frame tick.
        void RefreshStatus(bool force)
        {
            if (!g_NetworkLabel)
                return;

            const char* network = g_Note;
            if (!network[0])
            {
                const int ready = QueryStockIsNetworkInit();
                network = ready > 0 ? "Ready"
                        : ready == 0 ? "Connecting..."
                        : "Status unknown";
            }

            char text[sizeof(g_NetworkShown)] = {};
            _snprintf_s(text, _TRUNCATE, "Network: %s", network);
            if (!force && std::strcmp(text, g_NetworkShown) == 0)
                return;
            std::memcpy(g_NetworkShown, text, sizeof(text));
            Shell::SetLabelText(g_NetworkLabel, text);
        }

        void ClearPageState()
        {
            g_NetworkLabel = nullptr;
            g_Pending = false;
            g_AwaitDrop = false;
            g_InContinue = false;
            g_Note[0] = '\0';
            g_NetworkShown[0] = '\0';
        }

        // The original runs with this = the live pre-lobby screen: it only
        // reads the shell manager at +0x138, which every OpenShim screen
        // stores. Its push of the lobby is a request, so calling it from the
        // per-frame tick is safe.
        void CompleteContinue(void* screen)
        {
            g_InContinue = true;
            Log(L"[PRELOBBY] continue: calling stock Click_MultiPlayer this=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)));
            __try
            {
                if (g_ClickOriginal && screen)
                    g_ClickOriginal(screen);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] stock Click_MultiPlayer faulted (0x%08X)\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
            g_InContinue = false;
        }

        void ContinueImpl(void* screen)
        {
            if (!screen || g_InContinue)
                return;

            g_Pending = false;
            g_AwaitDrop = false;
            SetNote("");
            PreLobbyEndNicknameEdit();

            bool recycled = false;
            char pending[192] = {};
            if (PreLobbyGetPendingNickname(pending, sizeof(pending)))
            {
                BzrNetNicknameResult result = BzrNetNicknameResult::StoredForNextConnection;
                if (!PreLobbyApplyNickname(pending, result))
                {
                    SetNote("Nickname not saved");
                    Log(L"[PRELOBBY] nickname apply failed (result=%u)\n",
                        static_cast<uint32_t>(result));
                    RefreshStatus(true);
                    return;
                }
                recycled = (result == BzrNetNicknameResult::ReauthQueued);
            }

            if (!recycled && QueryStockIsNetworkInit() != 0)
            {
                CompleteContinue(screen);
                return;
            }

            // Either the connection was just recycled for the new name, or it
            // has not authorised yet: wait for isNetworkInit.
            g_Pending = true;
            g_AwaitDrop = recycled;
            g_PendingSince = GetTickCount64();
            SetNote("Connecting...");
            Log(L"[PRELOBBY] continue pending (recycled=%d)\n", recycled ? 1 : 0);
            RefreshStatus(true);
        }

        void __cdecl OnContinueClicked()
        {
            void* const screen = Shell::LiveScreen(Shell::kPreLobbyScreenId);
            __try
            {
                ContinueImpl(screen);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] Continue faulted (0x%08X)\n",
                    static_cast<uint32_t>(GetExceptionCode()));
                g_InContinue = false;
            }
        }

        // A nickname that was typed but never applied is dropped: the entry
        // always starts on the persisted nickname.
        void __cdecl OnBackClicked()
        {
            Shell::Back(Shell::LiveScreen(Shell::kPreLobbyScreenId));
        }

        void TickPreLobby(void* screen)
        {
            if (g_InContinue)
                return;

            if (g_Pending)
            {
                const int ready = QueryStockIsNetworkInit();
                const ULONGLONG elapsed = GetTickCount64() - g_PendingSince;
                if (g_AwaitDrop && (ready == 0 || elapsed >= kDropGraceMs))
                    g_AwaitDrop = false;

                if (!g_AwaitDrop && ready != 0)
                {
                    g_Pending = false;
                    SetNote("");
                    CompleteContinue(screen);
                }
                else if (elapsed >= kConnectTimeoutMs)
                {
                    g_Pending = false;
                    g_AwaitDrop = false;
                    SetNote("Still not ready (check sign-in or network)");
                    Log(L"[PRELOBBY] continue timed out after %llu ms\n", elapsed);
                }
            }
            RefreshStatus(false);
        }

        bool OnCharPreLobby(void* /*screen*/, uint8_t ch)
        {
            return PreLobbyForwardChar(ch);
        }

        void ClosedPreLobby(void* /*screen*/)
        {
            ResetPreLobbyLobbyWidgets();
            ClearPageState();
            Log(L"[PRELOBBY] closed\n");
        }

        // Kept out of BuildPreLobbyScreen so a fault in the borrowed lobby
        // widgets cannot cost the screen its Back and Continue buttons.
        bool CreatePickersGuarded(void* panel)
        {
            __try
            {
                const bool created = CreatePreLobbyNicknameAndFlagWidgets(
                    panel, kNicknameX, kNicknameY, kFlagX, kFlagArrowsY);
                RefreshPreLobbyLobbyWidgets(true);
                return created;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] nickname/flag widgets faulted (0x%08X)\n",
                    static_cast<uint32_t>(GetExceptionCode()));
                return false;
            }
        }

        bool BuildPreLobbyScreen(void* screen)
        {
            ClearPageState();
            ReadServerName();

            const char* texture =
                Shell::IsTextureDeployed(kPreLobbyPanelTexture) ? kPreLobbyPanelTexture : nullptr;
            if (!texture)
                Log(L"[PRELOBBY] %hs is not deployed; the screen shows the bare stock background\n",
                    kPreLobbyPanelTexture);

            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimPreLobby_Overlay",
                                          { 0.0f, 0.0f, 1440.0f, 1080.0f }, texture);
            if (!panel)
                return false;

            Shell::AddLabel(panel, panel, "OpenShimPreLobby_Title", kTitleRect, "MULTIPLAYER",
                            Shell::kTitleLabelFlags);

            const struct
            {
                const char* name;
                const Shell::Rect& box;
                const char* title;
            } headers[] = {
                { "OpenShimPreLobby_PlayerHdr", kPlayerBox, "PLAYER" },
                { "OpenShimPreLobby_ConnectionHdr", kConnectionBox, "CONNECTION" },
            };
            for (const auto& header : headers)
            {
                Shell::AddLabel(panel, panel, header.name,
                                { header.box.x + kBoxPadX, header.box.y + 4.0f,
                                  header.box.w - 2.0f * kBoxPadX, kBoxHeaderH - 6.0f },
                                header.title);
            }

            const float rowW = kConnectionBox.w - 2.0f * kBoxPadX;
            g_NetworkLabel = Shell::AddLabel(
                panel, panel, "OpenShimPreLobby_Network",
                { kConnectionBox.x + kBoxPadX, kConnectionBox.y + kRowTop, rowW, kRowH }, "");
            Shell::AddLabel(
                panel, panel, "OpenShimPreLobby_Server",
                { kConnectionBox.x + kBoxPadX, kConnectionBox.y + kRowTop + kRowH, rowW, kRowH },
                g_Server);
            Shell::AddLabel(panel, panel, "OpenShimPreLobby_Hint", kHintRect,
                            "A new name is applied when you press Continue.");
            RefreshStatus(true);

            const bool back = Shell::AddButton(panel, nullptr, "OpenShimPreLobby_Back", kBackRect,
                                               "Back", Shell::kSkinTopCorner, 1.0f, kBackTextOffset,
                                               &OnBackClicked) != nullptr;
            const bool cont = Shell::AddButton(panel, nullptr, "OpenShimPreLobby_Continue",
                                               kContinueRect, "Continue", Shell::kSkinToMainMenu,
                                               1.0f, 0.0f, &OnContinueClicked) != nullptr;

            // Created last so they draw above the panel art.
            CreatePickersGuarded(panel);
            return back && cont;
        }

        // ------------------------------------------------------------------
        // Entry hooks
        // ------------------------------------------------------------------

        // Click_MultiPlayer (0x0078C6C0, __thiscall on the title screen; it
        // only uses the shell manager at this+0x138). With [Network] PreLobby
        // on, the click opens this screen instead; every other case, including
        // a failed request, is the stock call.
        void InstallEntryHooks()
        {
            static constexpr uint8_t kExpectedClickBytes[] = {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xF3, 0xEA, 0x85, 0x00
            };

            if (!g_ClickHookInstalled)
            {
                uint32_t address = 0;
                const HookEngine::EngineAddressStatus status =
                    HookEngine::ResolveEngineAddress("ClickMultiPlayer", address);
                if (status != HookEngine::EngineAddressStatus::Bound)
                {
                    Log(L"[PRELOBBY] Click_MultiPlayer is not bound (status=%d); the pre-lobby "
                        L"stays off\n", static_cast<int>(status));
                }
                else if (InstallInlineDetour32(g_ClickDetour, address,
                                               reinterpret_cast<void*>(PreLobbyClickMultiPlayerHook),
                                               sizeof(kExpectedClickBytes), kExpectedClickBytes,
                                               sizeof(kExpectedClickBytes)))
                {
                    g_ClickOriginal = reinterpret_cast<FnClickMultiPlayer>(g_ClickDetour.trampoline);
                    g_ClickHookInstalled = g_ClickOriginal != nullptr;
                    Log(L"[PRELOBBY] Click_MultiPlayer hook installed entry=0x%08X\n", address);
                }
                else
                {
                    Log(L"[PRELOBBY] Click_MultiPlayer bytes mismatch at 0x%08X; the pre-lobby "
                        L"stays off\n", address);
                }
            }

            // The title screen disables the Multiplayer button every frame
            // until BZRNet authorises (0x0078EB50 -> SetEnabled(0) on +0x170),
            // so the click never reaches Click_MultiPlayer while it reads "Not
            // Ready". The pre-lobby has to open in exactly that state, so the
            // refresh's one call site is redirected to re-enable the button
            // after the stock refresh has run.
            if (!g_MpStatusHookInstalled)
            {
                uint32_t callSite = 0;
                if (HookEngine::ResolveEngineAddress("MainScreenMpStatusRefreshCall", callSite) !=
                    HookEngine::EngineAddressStatus::Bound)
                {
                    Log(L"[PRELOBBY] MP status refresh call is not bound; the screen opens only "
                        L"once the network is ready\n");
                }
                else if (Hooks::RedirectCallTarget(
                             callSite, kMainScreenMpStatusRefreshAddr,
                             reinterpret_cast<uintptr_t>(&PreLobbyMpStatusRefreshHook)))
                {
                    g_MpStatusHookInstalled = true;
                    Log(L"[PRELOBBY] MP status refresh call redirected at 0x%08X\n", callSite);
                }
                else
                {
                    Log(L"[PRELOBBY] MP status refresh call at 0x%08X has an unexpected target; "
                        L"the screen opens only once the network is ready\n", callSite);
                }
            }
        }

        // Read at click time, so the Options row (ReadOnNextUse) takes effect
        // without a restart.
        bool PreLobbyIniEnabled()
        {
            bool enabled = false;
            return TryGetUserConfigBool("Network", "PreLobby", enabled) && enabled;
        }

        // The MP-status refresh runs every title-screen frame, and the ini read
        // is a file read; re-read at most once a second there.
        bool PreLobbyIniEnabledThrottled()
        {
            static bool s_enabled = false;
            static ULONGLONG s_readAt = 0;
            const ULONGLONG now = GetTickCount64();
            if (s_readAt == 0 || now - s_readAt >= 1000)
            {
                s_enabled = PreLobbyIniEnabled();
                s_readAt = now;
            }
            return s_enabled;
        }
    }

    bool IsPreLobbyEnabled()
    {
        return PreLobbyIniEnabled();
    }

    void __fastcall PreLobbyClickMultiPlayerHook(void* thisPtr, void* /*edx*/)
    {
        bool requested = false;
        if (!g_InContinue && thisPtr && PreLobbyIniEnabled())
        {
            __try
            {
                requested = Shell::RequestScreen(thisPtr, Shell::kPreLobbyScreenId);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] requesting the screen faulted (0x%08X); using the stock click\n",
                    static_cast<uint32_t>(GetExceptionCode()));
                requested = false;
            }
        }
        if (!requested && g_ClickOriginal)
            g_ClickOriginal(thisPtr);
    }

    // Stock MP-status refresh first (label, status text, enabled byte), then
    // the button is made clickable again while the pre-lobby is on.
    void __fastcall PreLobbyMpStatusRefreshHook(void* thisPtr, void* /*edx*/)
    {
        using FnRefresh = void(__thiscall*)(void*);
        reinterpret_cast<FnRefresh>(kMainScreenMpStatusRefreshAddr)(thisPtr);

        if (!thisPtr || !PreLobbyIniEnabledThrottled())
            return;
        __try
        {
            auto* const button = *reinterpret_cast<uint8_t**>(
                static_cast<uint8_t*>(thisPtr) + kMainScreenMpButtonOffset);
            if (button)
                button[kUiButtonEnabledOffset] = 1;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    bool RegisterPreLobbyScreen()
    {
        static bool attempted = false;
        if (attempted)
            return g_Registered;
        attempted = true;

        Shell::ScreenDef def = { Shell::kPreLobbyScreenId, "MultiplayerPreLobby", &BuildPreLobbyScreen,
                                 &ClosedPreLobby, &TickPreLobby, &OnCharPreLobby };
        g_Registered = Shell::RegisterScreen(def);
        if (g_Registered)
            InstallEntryHooks();
        else
            Log(L"[PRELOBBY] shell screens unavailable on this build; the pre-lobby stays off\n");
        return g_Registered;
    }
}
