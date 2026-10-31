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
        std::array<void*, 8> g_Rows{};
        std::array<std::string, 8> g_RowText{};
        std::string g_StatusText, g_SearchText;
        size_t g_Page = 0;
        bool g_JoinHostedWhenReady = false;
        std::string g_Note;
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
            g_JoinHostedWhenReady = LanSession::StartHost(GameRoot(),LanNoAuth::Enabled());
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
        }
        void __cdecl ManualJoin()
        {
            PreLobbyEndServerEdit();
            char text[192]{};
            if (PreLobbyGetServerEntryText(text, sizeof(text))) Join(text);
        }
        template<size_t Row> void __cdecl Select()
        {
            const auto status = LanSession::Status();
            const auto index = g_Page * g_Rows.size() + Row;
            if (index >= status.hosts.size()) return;
            const auto& host = status.hosts[index];
            // A loopback discovery answer from our managed host must use its
            // actual LAN endpoint when we join, as other PCs will do.
            const auto address = host.address == "127.0.0.1" && status.state == LanSession::HostState::Running
                ? status.hostAddress : host.address;
            Join(LanDiscovery::Endpoint(address, host.port));
        }
        void __cdecl Next()
        {
            const size_t count = LanSession::Status().hosts.size();
            g_Page = count ? (g_Page + 1) % ((count + 7) / 8) : 0;
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
            const auto search = status.scanMessage + " (" + std::to_string(status.hosts.size()) + " found)";
            if (search != g_SearchText)
            { Shell::SetLabelText(g_Search, search.c_str()); g_SearchText = search; }
            for (size_t row = 0; row < g_Rows.size(); ++row)
            {
                const auto index = g_Page * g_Rows.size() + row;
                std::string text = "-";
                if (index < status.hosts.size())
                {
                    const auto& host = status.hosts[index];
                    text = host.name + "  [" + LanDiscovery::Endpoint(host.address, host.port) + "]";
                }
                if (g_Rows[row] && g_BzrFn_SetButtonLabel && text != g_RowText[row])
                { g_BzrFn_SetButtonLabel(g_Rows[row], text.c_str()); g_RowText[row] = text; }
            }
        }
        bool Build(void* screen)
        {
            g_Note.clear(); g_Page = 0; g_JoinHostedWhenReady = false;
            g_StatusText.clear(); g_SearchText.clear(); g_RowText.fill("");
            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimLAN", {0, 0, 1440, 1080}, nullptr);
            if (!panel) return false;
            void* body = Shell::AddPanel(panel, panel, "OpenShimLAN_Body", {230, 225, 980, 735}, nullptr);
            Shell::SetPanelRectColor(body, {230, 225, 980, 735}, 0xD8101820);
            Shell::AddLabel(panel, panel, "OpenShimLAN_Title", {420, 132, 600, 56}, LanNoAuth::Enabled() ? "LAN (NO SIGN-IN)" : "LOCAL HOST TOOLS", Shell::kTitleLabelFlags);
            Shell::AddLabel(panel, panel, "OpenShimLAN_Hint", {260, 230, 920, 40}, "Hosting opens LAN listeners; Windows may ask for firewall access.");
            const auto& skin = Shell::kSkinToMainMenu;
            Shell::AddButton(panel, panel, "OpenShimLAN_Host", {260, 285, 280, 60}, "Start local host", skin, 0.85f, 0, &Start);
            Shell::AddButton(panel, panel, "OpenShimLAN_Stop", {565, 285, 280, 60}, "Stop Host", skin, 0.85f, 0, &Stop);
            Shell::AddButton(panel, panel, "OpenShimLAN_Refresh", {870, 285, 280, 60}, "Refresh", skin, 0.85f, 0, &Refresh);
            g_Status = Shell::AddLabel(panel, panel, "OpenShimLAN_Status", {260, 350, 920, 40}, "");
            g_Search = Shell::AddLabel(panel, panel, "OpenShimLAN_Search", {260, 395, 920, 40}, "");
            const std::array<void(__cdecl*)(), 8> callbacks = {&Select<0>, &Select<1>, &Select<2>, &Select<3>, &Select<4>, &Select<5>, &Select<6>, &Select<7>};
            Shell::ButtonSkin rowSkin{nullptr, "optionhv.png", "optionck.png"};
            for (size_t row = 0; row < g_Rows.size(); ++row)
            {
                const std::string name = "OpenShimLAN_Host" + std::to_string(row);
                g_Rows[row] = Shell::AddButton(panel, panel, name.c_str(),
                    {260, 440 + 43.0f * row, 920, 40}, "-", rowSkin, 0.8f, 0, callbacks[row]);
            }
            Shell::AddButton(panel, panel, "OpenShimLAN_Next", {870, 787, 280, 50}, "Next page", skin, 0.75f, 0, &Next);
            Shell::AddLabel(panel, panel, "OpenShimLAN_ManualLabel", {260, 795, 590, 35}, "Join by IP (optional :port):");
            Shell::AddPanel(panel, panel, "OpenShimLAN_EntryWell", {260, 845, 590, 48}, "optionhv.png");
            Shell::AddButton(panel, panel, "OpenShimLAN_Manual", {870, 840, 280, 60}, "Use address", skin, 0.8f, 0, &ManualJoin);
            Shell::AddLabel(panel, panel, "OpenShimLAN_SignIn", {260, 905, 920, 40}, LanNoAuth::Enabled() ? "Hosted by this game. No accounts or helper. Stop Host disconnects players." : "Steam/Galaxy sign-in is still required. Stop Host disconnects its players.");
            const bool back = Shell::AddButton(panel, nullptr, "OpenShimLAN_Back", {0, 0, 342, 77}, "Back", Shell::kSkinTopCorner, 1, 28, &Back) != nullptr;
            // Borrowed entry uses the same ownership/char routing as setup.
            CreatePreLobbyServerEntry(panel, 268, 845, 574, 48, "");
            PreLobbySetServerEntryVisible(true);
            Refresh(); Tick(screen);
            return back;
        }
        void Closed(void*)
        {
            LanSession::StopScan(); // Hosting intentionally survives menu and mission transitions.
            ResetPreLobbyLobbyWidgets();
            g_Status = g_Search = nullptr; g_Rows.fill(nullptr);
            g_JoinHostedWhenReady = false;
        }
        bool OnChar(void*, uint8_t ch) { return PreLobbyForwardChar(ch); }
    }
    bool RegisterLanScreen()
    {
        return Shell::RegisterScreen({Shell::kLanScreenId, "LanMultiplayer", &Build, &Closed, &Tick, &OnChar});
    }
}
