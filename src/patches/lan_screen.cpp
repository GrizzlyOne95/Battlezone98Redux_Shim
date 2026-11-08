// Uses the registered shell-screen API; no new executable patch sites.
#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "lan_session.h"
#include "lan_no_auth.h"
#include "lan_no_auth_policy.h"
#include "lan_discovery.h"
#include "matchmaking_server.h"
#include "net_optimizer.h"
#include "shell_screens.h"
#include "steam_public_listing.h"
#include "steam_tunnel_join.h"
#include "patcher.h"
#include <windows.h>
#include <array>
#include <filesystem>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        namespace Shell = ShellScreens;
        void* g_Status = nullptr;
        void* g_Search = nullptr;
        void* g_Hint = nullptr;
        void* g_SteamButton = nullptr;
        // mkscreens.py LAN_LAYOUT paints the panel these rects sit on.
        constexpr const char* kLanPanelTexture = "osh_lan_center.png";
        constexpr float kPadX = 28.0f;          // box text inset, as the pre-lobby
        constexpr float kCaptionDrop = 10.0f;   // label top -> centred slot text
        constexpr Shell::Rect kHostBox = {244, 238, 952, 196};
        constexpr Shell::Rect kGamesBox = {244, 450, 952, 272};
        constexpr Shell::Rect kJoinBox = {244, 738, 952, 110};
        constexpr float kTextX = kHostBox.x + kPadX;
        constexpr float kTextW = kHostBox.w - 2 * kPadX;
        constexpr float kRowY = 556, kRowPitch = 40, kRowH = 36;

        std::array<void*, 4> g_Rows{};
        std::array<std::string, 4> g_RowText{};
        // What each row joins, fixed when its label is set, so a list that
        // changes between drawing and clicking never joins another game.
        struct RowTarget { bool steam = false; uint64_t bridge = 0; std::string endpoint, name; };
        std::array<RowTarget, 4> g_RowTarget{};
        std::string g_StatusText, g_SearchText, g_HintText, g_SteamButtonText;
        size_t g_Page = 0;
        bool g_JoinHostedWhenReady = false;
        std::string g_Note;
        constexpr const char* kFirewallHint = "Hosting opens LAN listeners; Windows may ask for firewall access.";
        // Matches the bridge docs: kept apart from the agent's 127.0.0.1 ports.
        constexpr const char* kSteamHostAddress = "127.0.0.2";
        std::string SwitchNote() { return "Stop and start the host to switch between LAN and Steam hosting."; }
        // LAN hosts first, then public Steam listings.
        size_t GameCount(const LanSession::Snapshot& status)
        {
            return status.hosts.size() + SteamPublicListing::Games().size();
        }
        std::wstring GameRoot()
        {
            wchar_t path[32768]{};
            const DWORD size = GetModuleFileNameW(nullptr, path, DWORD(std::size(path)));
            return size && size < std::size(path) ? std::filesystem::path(path).parent_path().wstring() : L"";
        }
        void Join(const std::string& endpoint)
        {
            g_JoinHostedWhenReady = false;
            char redirect[256]{};
            if (GetMatchmakingRedirectTarget(redirect, sizeof(redirect)))
            { g_Note = "A test redirect owns the server address."; return; }
            // Persist the explicit LAN selection. Its readiness policy still
            // requires a real admission; discovery alone never enables it.
            std::string canonical;
            if (LanNoAuth::Enabled() && !LanNoAuth::PrivateEndpoint(endpoint,canonical))
            { g_Note = "Enter a private numeric LAN IPv4 address (optional :port)."; return; }
            if (MatchmakingServer::ValidateCustomHost(endpoint, canonical) != MatchmakingServer::HostStatus::Ok)
            { g_Note = "Enter an IPv4 address or host name, optionally with :port."; return; }
            if (!WriteShimUserConfigValue("Network", "CustomServer", canonical.c_str()) ||
                !WriteShimUserConfigValue("Network", "Server", "LAN"))
            { g_Note = "Could not save the LAN host address."; return; }
            SetMatchmakingServerOverride(canonical.c_str(), false);
            RecycleBzrNetWebSocket();
            Shell::Back(Shell::LiveScreen(Shell::kLanScreenId));
        }
        void __cdecl Back()
        {
            g_JoinHostedWhenReady = false;
            Shell::Back(Shell::LiveScreen(Shell::kLanScreenId));
        }
        void __cdecl Start()
        {
            g_Note.clear();
            // With the Steam list on, host on loopback so the in-game Steam
            // bridge (SteamTunnelBridge=auto) serves it and the listing follows.
            // The bridge gives each Steam peer its own loopback source address.
            const bool forSteam = SteamPublicListing::Available() && SteamPublicListing::HostListingOn();
            const auto before = LanSession::Status();
            if ((before.state == LanSession::HostState::Starting || before.state == LanSession::HostState::Running) &&
                (before.hostAddress == kSteamHostAddress) != forSteam)
            { g_Note = SwitchNote(); return; } // never join a host in the other mode
            // A Steam join moved the tunnel; the bridge never runs while it is moved.
            std::string note;
            if (forSteam && !SteamTunnelJoin::RestoreStartup(note))
            { g_Note = "Cannot host for Steam: " + note + "."; return; }
            g_JoinHostedWhenReady = LanSession::StartHost(GameRoot(), LanNoAuth::Enabled(),
                forSteam ? std::string(kSteamHostAddress) : std::string());
            const auto status = LanSession::Status();
            Log(L"[LAN-HOST] start %hs: %hs\n", g_JoinHostedWhenReady ? "ok" : "failed", status.hostMessage.c_str());
        }
        void __cdecl Stop()
        {
            g_JoinHostedWhenReady = false;
            g_Note.clear();
            LanSession::StopHost();
        }
        void __cdecl Refresh()
        {
            g_Note.clear(); g_Page = 0;
            LanSession::StartScan();
            SteamPublicListing::StartBrowse();
        }
        void __cdecl ToggleSteamListing()
        {
            g_Note.clear();
            SteamPublicListing::SetHostListing(!SteamPublicListing::HostListingOn());
            const auto status = LanSession::Status();
            const bool forSteam = SteamPublicListing::HostListingOn();
            if ((status.state == LanSession::HostState::Starting || status.state == LanSession::HostState::Running) &&
                (status.hostAddress == kSteamHostAddress) != forSteam)
                g_Note = SwitchNote(); // toggling back to the running mode clears it
        }
        void __cdecl ManualJoin()
        {
            PreLobbyEndServerEdit();
            char text[192]{};
            if (PreLobbyGetServerEntryText(text, sizeof(text))) Join(text);
        }
        template<size_t Row> void __cdecl Select()
        {
            const auto target = g_RowTarget[Row]; // copy: joining redraws the rows
            if (target.steam)
            {
                std::string note;
                g_JoinHostedWhenReady = false;
                if (SteamTunnelJoin::JoinBridge(target.bridge, note))
                    Shell::Back(Shell::LiveScreen(Shell::kLanScreenId));
                else
                    g_Note = "Cannot join " + target.name + ": " + note + ".";
                return;
            }
            if (target.endpoint.empty()) return;
            // A Steam join moved the tunnel; a LAN row must not go through it.
            std::string note;
            if (!SteamTunnelJoin::RestoreStartup(note))
            { g_Note = "Cannot join " + target.endpoint + ": " + note + "."; return; }
            Join(target.endpoint);
        }
        void __cdecl Next()
        {
            const size_t count = GameCount(LanSession::Status());
            const size_t rows = g_Rows.size();
            g_Page = count ? (g_Page + 1) % ((count + rows - 1) / rows) : 0;
        }
        void Tick(void*)
        {
            LanNoAuth::PumpMainThread();
            LanSession::Tick();
            const auto status = LanSession::Status();
            if (g_JoinHostedWhenReady)
            {
                if (status.state == LanSession::HostState::Running)
                { g_JoinHostedWhenReady = false; Join(status.hostAddress); return; }
                if (status.state == LanSession::HostState::Failed || status.state == LanSession::HostState::Stopped)
                    g_JoinHostedWhenReady = false;
            }
            const auto statusText = g_Note.empty() ? status.hostMessage : g_Note;
            if (statusText != g_StatusText)
            { Shell::SetLabelText(g_Status, statusText.c_str()); g_StatusText = statusText; }
            // The count only matters with hosts; the label must end before Refresh.
            auto search = status.hosts.empty() ? status.scanMessage
                : status.scanMessage + " (" + std::to_string(status.hosts.size()) + " found)";
            const bool steam = SteamPublicListing::Available();
            if (steam && !SteamPublicListing::BrowseText().empty())
                search += "; " + SteamPublicListing::BrowseText();
            const auto hint = steam ? SteamPublicListing::HostListingText() : std::string(kFirewallHint);
            if (hint != g_HintText)
            { Shell::SetLabelText(g_Hint, hint.c_str()); g_HintText = hint; }
            const std::string steamButton = SteamPublicListing::HostListingOn() ? "Steam list: On" : "Steam list: Off";
            if (g_SteamButton && g_BzrFn_SetButtonLabel && steamButton != g_SteamButtonText)
            { g_BzrFn_SetButtonLabel(g_SteamButton, steamButton.c_str()); g_SteamButtonText = steamButton; }
            if (search != g_SearchText)
            { Shell::SetLabelText(g_Search, search.c_str()); g_SearchText = search; }
            // Hosts expire; keep the page on the list instead of showing blanks.
            const auto& games = SteamPublicListing::Games();
            if (g_Page && g_Page * g_Rows.size() >= GameCount(status)) g_Page = 0;
            for (size_t row = 0; row < g_Rows.size(); ++row)
            {
                const auto index = g_Page * g_Rows.size() + row;
                std::string text;
                RowTarget target;
                if (index < status.hosts.size())
                {
                    const auto& host = status.hosts[index];
                    text = host.name + "  [" + LanDiscovery::Endpoint(host.address, host.port) + "]";
                    // A loopback discovery answer from our managed host must use its
                    // actual LAN endpoint when we join, as other PCs will do.
                    const auto address = host.address == "127.0.0.1" && status.state == LanSession::HostState::Running
                        ? status.hostAddress : host.address;
                    target.endpoint = LanDiscovery::Endpoint(address, host.port);
                }
                else if (index < GameCount(status))
                {
                    const auto& game = games[index - status.hosts.size()];
                    text = game.name + "  [Steam]";
                    target.steam = true; target.bridge = game.bridge; target.name = game.name;
                }
                g_RowTarget[row] = target;
                if (g_Rows[row] && g_BzrFn_SetButtonLabel && text != g_RowText[row])
                { g_BzrFn_SetButtonLabel(g_Rows[row], text.c_str()); g_RowText[row] = text; }
            }
        }
        bool Build(void* screen)
        {
            g_Note.clear(); g_Page = 0; g_JoinHostedWhenReady = false;
            g_StatusText.clear(); g_SearchText.clear(); g_HintText.clear(); g_SteamButtonText.clear(); g_RowText.fill(""); g_RowTarget.fill({});
            const bool steam = SteamPublicListing::Available();
            const char* texture = Shell::IsTextureDeployed(kLanPanelTexture) ? kLanPanelTexture : nullptr;
            if (!texture) Log(L"[LAN] %hs is not deployed; the screen shows the bare stock background\n", kLanPanelTexture);
            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimLAN", {0, 0, 1440, 1080}, texture);
            if (!panel) return false;
            const bool noAuth = LanNoAuth::Enabled();
            Shell::AddLabel(panel, panel, "OpenShimLAN_Title", {470, 132, 500, 56}, noAuth ? "LAN (NO SIGN-IN)" : "LOCAL HOST TOOLS", Shell::kTitleLabelFlags);
            const struct { const char* name; const Shell::Rect& box; const char* title; } headers[] = {
                {"OpenShimLAN_HostHdr", kHostBox, "HOST"},
                {"OpenShimLAN_GamesHdr", kGamesBox, steam ? "GAMES ON THIS NETWORK AND STEAM" : "GAMES ON THIS NETWORK"},
                {"OpenShimLAN_JoinHdr", kJoinBox, "JOIN BY ADDRESS"},
            };
            for (const auto& h : headers)
                Shell::AddLabel(panel, panel, h.name, {h.box.x + kPadX, h.box.y + 4, h.box.w - 2 * kPadX, 38}, h.title);

            // Slot buttons: the slot is painted into the panel, the button
            // only supplies hover/press, as on the pre-lobby Server row.
            Shell::ButtonSkin slot{"optionhv.png", "optionhv.png", "optionck.png"};
            if (texture && Shell::IsTextureDeployed("osh_value_hv.png") && Shell::IsTextureDeployed("osh_value_ck.png"))
                slot = {nullptr, "osh_value_hv.png", "osh_value_ck.png"};
            Shell::AddButton(panel, panel, "OpenShimLAN_Host", {272, 294, 220, 42}, "Start host", slot, 1.0f, 0, &Start);
            Shell::AddButton(panel, panel, "OpenShimLAN_Stop", {508, 294, 220, 42}, "Stop host", slot, 1.0f, 0, &Stop);
            g_SteamButton = steam ? Shell::AddButton(panel, panel, "OpenShimLAN_SteamList", {744, 294, 220, 42},
                SteamPublicListing::HostListingOn() ? "Steam list: On" : "Steam list: Off", slot, 1.0f, 0, &ToggleSteamListing) : nullptr;
            g_Status = Shell::AddLabel(panel, panel, "OpenShimLAN_Status", {kTextX, 346, kTextW, 28}, "");
            g_Hint = Shell::AddLabel(panel, panel, "OpenShimLAN_Hint", {kTextX, 374, kTextW, 28}, kFirewallHint);
            Shell::AddLabel(panel, panel, "OpenShimLAN_SignIn", {kTextX, 402, kTextW, 28}, noAuth ? "Hosted by this game. No accounts or helper. Stop host disconnects players." : "Steam/Galaxy sign-in is still required. Stop host disconnects its players.");

            g_Search = Shell::AddLabel(panel, panel, "OpenShimLAN_Search", {kTextX, 504 + kCaptionDrop - 2, 540, 32}, "");
            Shell::AddButton(panel, panel, "OpenShimLAN_Refresh", {832, 504, 160, 40}, "Refresh", slot, 1.0f, 0, &Refresh);
            Shell::AddButton(panel, panel, "OpenShimLAN_Next", {1008, 504, 160, 40}, "Next page", slot, 1.0f, 0, &Next);
            const std::array<void(__cdecl*)(), 4> callbacks = {&Select<0>, &Select<1>, &Select<2>, &Select<3>};
            Shell::ButtonSkin rowSkin{nullptr, "optionhv.png", "optionck.png"};
            for (size_t row = 0; row < g_Rows.size(); ++row)
            {
                const std::string name = "OpenShimLAN_Host" + std::to_string(row);
                g_Rows[row] = Shell::AddButton(panel, panel, name.c_str(),
                    {kTextX, kRowY + kRowPitch * row, kTextW, kRowH}, "", rowSkin, 0.9f, 0, callbacks[row]);
            }

            Shell::AddLabel(panel, panel, "OpenShimLAN_ManualLabel", {kTextX, 792 + kCaptionDrop, 130, 42}, "Address:");
            Shell::AddButton(panel, panel, "OpenShimLAN_Manual", {1008, 792, 160, 42}, "Use address", slot, 1.0f, 0, &ManualJoin);
            const bool back = Shell::AddButton(panel, nullptr, "OpenShimLAN_Back", {0, 0, 342, 77}, "Back", Shell::kSkinTopCorner, 1, 28, &Back) != nullptr;
            // Borrowed entry uses the same ownership/char routing as setup.
            CreatePreLobbyServerEntry(panel, 420, 792, 564, 42, "");
            PreLobbySetServerEntryVisible(true);
            Refresh(); Tick(screen);
            return back;
        }
        void Closed(void*)
        {
            LanSession::StopScan(); // Hosting intentionally survives menu and mission transitions.
            ResetPreLobbyLobbyWidgets();
            g_Status = g_Search = g_Hint = g_SteamButton = nullptr; g_Rows.fill(nullptr);
            g_JoinHostedWhenReady = false;
        }
        bool OnChar(void*, uint8_t ch) { return PreLobbyForwardChar(ch); }
    }
    bool RegisterLanScreen()
    {
        return Shell::RegisterScreen({Shell::kLanScreenId, "LanMultiplayer", &Build, &Closed, &Tick, &OnChar});
    }
}
