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
// The CONNECTION box also picks the matchmaking server (Rebellion or a custom
// host; include/matchmaking_server.h). Continue persists a changed choice,
// sets the live override the resolver hook applies (net_optimizer.cpp) and
// recycles the BZRNet websocket -- once, together with any nickname change --
// so the stock reconnect resolves the new host.
//
// The panel art is resources/ui/custom_widgets/osh_prelobby_center.png,
// painted by mkscreens.py. Its title plate, two boxes, the two server toggle
// slots and the custom-host well are the layout contract with the constants
// below; change both together.

#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "matchmaking_server.h"
#include "net_optimizer.h"
#include "patcher.h"
#include "shell_screens.h"

#include <windows.h>

#include <cstdio>
#include <cstring>
#include <string>

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
        constexpr Shell::Rect kConnectionBox = { 244.0f, 596.0f, 952.0f, 220.0f };
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

        // The Server row: caption, the two toggle slots (the 196x42 option-slot
        // size the settings pages use), then the custom-host well to the box's
        // right padding. The security note sits one gap below.
        constexpr float kServerRowY = kConnectionBox.y + kRowTop + kRowH;
        constexpr float kServerRowH = 42.0f;
        constexpr float kServerCaptionW = 110.0f;
        constexpr float kServerSlotW = 196.0f;
        constexpr float kServerSlotGap = 10.0f;
        constexpr float kServerCaptionX = kConnectionBox.x + kBoxPadX;
        constexpr float kServerSlotX = kServerCaptionX + kServerCaptionW + kServerSlotGap;
        constexpr float kServerWellX = kServerSlotX + 2.0f * (kServerSlotW + kServerSlotGap);
        constexpr float kServerWellW = kConnectionBox.x + kConnectionBox.w - kBoxPadX - kServerWellX;
        constexpr float kServerNoteY = kServerRowY + kServerRowH + 8.0f;

        constexpr Shell::Rect kHintRect = { 244.0f, 828.0f, 952.0f, 46.0f };

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
        char g_NetworkShown[128] = {};

        // The Server selector. g_ServerSelector is false while a test redirect
        // owns the endpoint: the row is then a read-only label.
        enum class ServerChoice { Rebellion, Custom };
        bool g_ServerSelector = false;
        ServerChoice g_Choice = ServerChoice::Rebellion;
        void* g_RebellionButton = nullptr;
        void* g_CustomButton = nullptr;
        void* g_ServerNoteLabel = nullptr;

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

        namespace MS = MatchmakingServer;

        constexpr const char* kCustomServerNote = "Custom servers never receive your sign-in ticket.";

        // The host the client connects to right now: the live override, else
        // the /bzrserver= launch host, else the official one.
        std::string CurrentServerHost()
        {
            char host[256] = {};
            if (!GetMatchmakingServerOverride(host, sizeof(host)))
                GetLaunchServerHost(host, sizeof(host));
            return host;
        }

        // Where the selector starts: the host in effect decides Rebellion or
        // Custom, and the entry is prefilled with it (or, for Rebellion, with
        // the saved CustomServer so toggling back finds it).
        void ReadServerState(ServerChoice& choice, std::string& customText)
        {
            const std::string current = CurrentServerHost();
            std::string saved;
            TryGetUserConfigString("Network", "CustomServer", saved);
            if (current.empty() || MS::EqualsNoCase(current, MS::kRebellionHost))
            {
                choice = ServerChoice::Rebellion;
                customText = TrimAsciiCopy(saved);
            }
            else
            {
                choice = ServerChoice::Custom;
                customText = current;
            }
        }

        const char* ServerCaption(ServerChoice which)
        {
            const bool selected = g_Choice == which;
            if (which == ServerChoice::Rebellion)
                return selected ? "> Rebellion <" : "Rebellion";
            return selected ? "> Custom <" : "Custom";
        }

        // Captions mark the selected button; the host entry and the security
        // note exist only while Custom is selected.
        void RefreshServerSelector()
        {
            if (!g_ServerSelector)
                return;
            const bool custom = g_Choice == ServerChoice::Custom;
            if (g_BzrFn_SetButtonLabel)
            {
                if (g_RebellionButton)
                    g_BzrFn_SetButtonLabel(g_RebellionButton, ServerCaption(ServerChoice::Rebellion));
                if (g_CustomButton)
                    g_BzrFn_SetButtonLabel(g_CustomButton, ServerCaption(ServerChoice::Custom));
            }
            PreLobbySetServerEntryVisible(custom);
            Shell::SetLabelText(g_ServerNoteLabel, custom ? kCustomServerNote : "");
        }

        void __cdecl OnRebellionClicked()
        {
            g_Choice = ServerChoice::Rebellion;
            RefreshServerSelector();
        }

        void __cdecl OnCustomClicked()
        {
            g_Choice = ServerChoice::Custom;
            RefreshServerSelector();
        }

        // Resolves the selector to the host that should be in effect. False,
        // with a note set, when a Custom address is unusable.
        bool ResolveDesiredServerHost(std::string& desired)
        {
            if (g_Choice == ServerChoice::Rebellion)
            {
                desired = MS::kRebellionHost;
                return true;
            }
            char typed[192] = {};
            PreLobbyGetServerEntryText(typed, sizeof(typed));
            switch (MS::ValidateCustomHost(typed, desired))
            {
            case MS::HostStatus::Ok:
                return true;
            case MS::HostStatus::UnsupportedPort:
                SetNote("Only port 1337 is supported");
                break;
            case MS::HostStatus::Invalid:
                SetNote("Enter a host name or IP address only");
                break;
            default:
                SetNote("Enter a server address");
                break;
            }
            return false;
        }

        // Persists and applies a changed server. `changed` reports whether the
        // host in effect differs, i.e. whether the websocket must reconnect.
        // False, with a note set, when the choice is unusable or not saved.
        bool ApplyServerSelection(bool& changed)
        {
            changed = false;
            if (!g_ServerSelector)
                return true;

            std::string desired;
            if (!ResolveDesiredServerHost(desired))
                return false;
            if (MS::EqualsNoCase(desired, CurrentServerHost()))
                return true;

            const bool custom = g_Choice == ServerChoice::Custom;
            if (!WriteShimUserConfigValue("Network", "Server", custom ? "Custom" : "Rebellion") ||
                (custom && !WriteShimUserConfigValue("Network", "CustomServer", desired.c_str())))
            {
                SetNote("Server not saved");
                Log(L"[PRELOBBY] server selection could not be persisted\n");
                return false;
            }
            SetMatchmakingServerOverride(desired.c_str());
            Log(L"[PRELOBBY] server selection applied: %hs (%hs)\n", desired.c_str(),
                custom ? "custom" : "rebellion");
            changed = true;
            return true;
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
            g_ServerSelector = false;
            g_Choice = ServerChoice::Rebellion;
            g_RebellionButton = nullptr;
            g_CustomButton = nullptr;
            g_ServerNoteLabel = nullptr;
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
            PreLobbyEndServerEdit();

            // The server goes first: the override must be in place before any
            // recycle, since the reconnect's lookup is what picks the host up.
            bool serverChanged = false;
            if (!ApplyServerSelection(serverChanged))
            {
                RefreshStatus(true);
                return;
            }

            bool recycled = false;
            char pending[192] = {};
            if (PreLobbyGetPendingNickname(pending, sizeof(pending)))
            {
                BzrNetNicknameResult result = BzrNetNicknameResult::StoredForNextConnection;
                if (!PreLobbyApplyNickname(pending, result))
                {
                    // The server change still has to take effect.
                    if (serverChanged)
                        RecycleBzrNetWebSocket();
                    SetNote("Nickname not saved");
                    Log(L"[PRELOBBY] nickname apply failed (result=%u)\n",
                        static_cast<uint32_t>(result));
                    RefreshStatus(true);
                    return;
                }
                recycled = (result == BzrNetNicknameResult::ReauthQueued);
            }

            // One recycle covers both: the nickname apply recycles an
            // authorised connection itself; otherwise a server change does.
            if (serverChanged && !recycled)
            {
                recycled = RecycleBzrNetWebSocket();
                Log(L"[PRELOBBY] server change recycle %hs\n", recycled ? "done" : "found no socket");
                if (!recycled && QueryStockIsNetworkInit() > 0)
                {
                    SetNote("Server saved; restart to connect to it");
                    RefreshStatus(true);
                    return;
                }
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

        // The custom-host entry and the selector state that depends on it. A
        // separate function from its guard: __try cannot share a function with
        // std::string.
        void CreateServerEntry(void* panel)
        {
            if (!g_ServerSelector)
                return;
            ServerChoice choice = ServerChoice::Rebellion;
            std::string customText;
            ReadServerState(choice, customText);
            CreatePreLobbyServerEntry(panel, kServerWellX + 8.0f, kServerRowY,
                                      kServerWellW - 16.0f, kServerRowH, customText.c_str());
            RefreshServerSelector();
        }

        void CreateServerEntryGuarded(void* panel)
        {
            __try
            {
                CreateServerEntry(panel);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] server entry faulted (0x%08X)\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
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
            char redirect[80] = {};
            if (GetMatchmakingRedirectTarget(redirect, sizeof(redirect)) && redirect[0])
            {
                // The test redirect owns the endpoint: show it, build no toggle.
                char text[128] = {};
                _snprintf_s(text, _TRUNCATE, "Server: %s (test redirect)", redirect);
                Shell::AddLabel(panel, panel, "OpenShimPreLobby_Server",
                                { kServerCaptionX, kServerRowY, rowW, kRowH }, text);
            }
            else
            {
                Shell::AddLabel(panel, panel, "OpenShimPreLobby_Server",
                                { kServerCaptionX, kServerRowY, kServerCaptionW, kServerRowH },
                                "Server:");

                // As the settings pages' value buttons: the slot is painted
                // into the panel and the button only supplies hover/press.
                Shell::ButtonSkin slotSkin = { "optionhv.png", "optionhv.png", "optionck.png" };
                if (Shell::IsTextureDeployed("osh_value_hv.png") &&
                    Shell::IsTextureDeployed("osh_value_ck.png"))
                {
                    slotSkin = { nullptr, "osh_value_hv.png", "osh_value_ck.png" };
                }

                ServerChoice choice = ServerChoice::Rebellion;
                std::string customText;
                ReadServerState(choice, customText);
                g_Choice = choice;
                g_ServerSelector = true;
                g_RebellionButton = Shell::AddButton(
                    panel, panel, "OpenShimPreLobby_ServerRebellion",
                    { kServerSlotX, kServerRowY, kServerSlotW, kServerRowH },
                    ServerCaption(ServerChoice::Rebellion), slotSkin, 1.0f, 0.0f, &OnRebellionClicked);
                g_CustomButton = Shell::AddButton(
                    panel, panel, "OpenShimPreLobby_ServerCustom",
                    { kServerSlotX + kServerSlotW + kServerSlotGap, kServerRowY, kServerSlotW,
                      kServerRowH },
                    ServerCaption(ServerChoice::Custom), slotSkin, 1.0f, 0.0f, &OnCustomClicked);
                g_ServerNoteLabel = Shell::AddLabel(
                    panel, panel, "OpenShimPreLobby_ServerNote",
                    { kServerCaptionX, kServerNoteY, rowW, 34.0f }, "");
            }
            Shell::AddLabel(panel, panel, "OpenShimPreLobby_Hint", kHintRect,
                            "A new name or server is applied when you press Continue.");
            RefreshStatus(true);

            const bool back = Shell::AddButton(panel, nullptr, "OpenShimPreLobby_Back", kBackRect,
                                               "Back", Shell::kSkinTopCorner, 1.0f, kBackTextOffset,
                                               &OnBackClicked) != nullptr;
            // Laid out against the panel so it centres with the content; the
            // top-corner Back keeps a null layout parent because it sits on
            // the window corner.
            const bool cont = Shell::AddButton(panel, panel, "OpenShimPreLobby_Continue",
                                               kContinueRect, "Continue", Shell::kSkinToMainMenu,
                                               1.0f, 0.0f, &OnContinueClicked) != nullptr;

            // Created last so they draw above the panel art.
            CreatePickersGuarded(panel);
            CreateServerEntryGuarded(panel);
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
