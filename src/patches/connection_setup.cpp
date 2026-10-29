#include "connection_setup.h"
#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "direct_lan_discovery.h"
#include "shell_screens.h"
#include <array>
#include <memory>
#include <string>

namespace BZROpenShim::ConnectionSetup
{
    namespace
    {
        namespace Shell = ShellScreens;
        bool g_Registered = false;
        std::unique_ptr<DirectLan::Browser> g_Browser;
        void* g_Status = nullptr;
        std::array<void*, 6> g_Rows{};
        std::array<std::string, 6> g_Shown{};
        std::string g_StatusShown;
        const char* kPreviewStatus = "Discovery preview. LAN gameplay is not available in this build.";
        void Status(const std::string& text)
        {
            if (text != g_StatusShown) { Shell::SetLabelText(g_Status, text.c_str()); g_StatusShown = text; }
        }
        void __cdecl BackChoice() { Shell::Back(Shell::LiveScreen(Shell::kConnectionSetupScreenId)); }
        void __cdecl BackLan() { Shell::Back(Shell::LiveScreen(Shell::kDirectLanScreenId)); }
        void __cdecl Server()
        { Shell::RequestScreen(Shell::LiveScreen(Shell::kConnectionSetupScreenId), Shell::kPreLobbyScreenId); }
        void __cdecl Lan()
        { Shell::RequestScreen(Shell::LiveScreen(Shell::kConnectionSetupScreenId), Shell::kDirectLanScreenId); }
        void __cdecl Refresh()
        {
            if (!g_Browser) g_Browser = std::make_unique<DirectLan::Browser>();
            if (g_Browser->Start()) Status("Searching nearby LAN games...");
            else Status(g_Browser->Error());
        }
        void __cdecl Host()
        {
            // Intentionally no native game creation, fake identity, readiness
            // bypass or helper launch here. Those require the qualified adapter.
            Status("Host Game is not available in this discovery preview.");
        }
        void __cdecl Join()
        { Status("Joining games is not available in this discovery preview."); }
        void __cdecl JoinIP()
        {
            PreLobbyEndServerEdit(); char text[192]{};
            uint32_t address = 0;
            if (!PreLobbyGetServerEntryText(text, sizeof(text)) || !DirectLan::ParseIPv4(text, address))
                Status("Enter the host's LAN IPv4 address.");
            else Join();
        }
        void* Panel(void* screen, const char* name)
        {
            void* panel = Shell::AddPanel(screen, nullptr, name, {0, 0, 1440, 1080}, nullptr);
            if (panel)
            {
                void* body = Shell::AddPanel(panel, panel, "ConnectionBody", {244, 270, 952, 660}, nullptr);
                Shell::SetPanelRectColor(body, {244, 270, 952, 660}, 0xE008180D);
            }
            return panel;
        }
        bool BuildChoice(void* screen)
        {
            void* panel = Panel(screen, "ConnectionSetup"); if (!panel) return false;
            Shell::AddLabel(panel, panel, "ConnectionTitle", {470, 132, 500, 56}, "MULTIPLAYER", Shell::kTitleLabelFlags);
            Shell::AddLabel(panel, panel, "ConnectionQuestion", {272, 300, 896, 46}, "Choose how to connect.");
            Shell::AddButton(panel, panel, "ConnectServer", {280, 400, 369, 68}, "Server Connect", Shell::kSkinToMainMenu, 1, 0, &Server);
            Shell::AddLabel(panel, panel, "ServerChoices", {280, 495, 390, 40}, "Official / Custom / Local");
            Shell::AddLabel(panel, panel, "ServerDescription", {280, 540, 390, 40}, "Browse through a lobby server.");
            Shell::AddButton(panel, panel, "ConnectLAN", {790, 400, 369, 68}, "LAN", Shell::kSkinToMainMenu, 1, 0, &Lan);
            Shell::AddLabel(panel, panel, "LANChoices", {790, 495, 380, 40}, "Host / Nearby Games / Join by IP");
            Shell::AddLabel(panel, panel, "LANDescription", {790, 540, 380, 40}, "Client to client. No account needed.");
            Shell::AddLabel(panel, panel, "ConnectionPreview", {272, 820, 896, 46}, "Layout preview: LAN gameplay is still in development.");
            return Shell::AddButton(panel, nullptr, "ConnectionBack", {0, 0, 342, 77}, "Back", Shell::kSkinTopCorner, 1, 28, &BackChoice) != nullptr;
        }
        void TickLan(void*)
        {
            if (!g_Browser) return;
            const bool searching = g_Browser->Searching(); g_Browser->Poll();
            if (searching && !g_Browser->Searching()) Status(kPreviewStatus);
            const auto& results = g_Browser->Results();
            for (size_t i = 0; i < g_Rows.size(); ++i)
            {
                std::string text = "-";
                if (i < results.size())
                {
                    const auto& a = results[i];
                    text = a.name + "  " + std::to_string(a.members) + "/" + std::to_string(a.capacity) +
                        "  " + DirectLan::FormatIPv4(a.control.ipv4);
                }
                if (g_Rows[i] && g_BzrFn_SetButtonLabel && text != g_Shown[i])
                { g_BzrFn_SetButtonLabel(g_Rows[i], text.c_str()); g_Shown[i] = text; }
            }
        }
        bool BuildLan(void* screen)
        {
            g_Shown.fill(""); g_StatusShown.clear();
            void* panel = Panel(screen, "DirectLANSetup"); if (!panel) return false;
            Shell::AddLabel(panel, panel, "DirectLANTitle", {470, 132, 500, 56}, "LAN", Shell::kTitleLabelFlags);
            Shell::AddLabel(panel, panel, "DirectLANHint", {272, 295, 896, 40}, "Host a game or choose one on your local network.");
            Shell::AddButton(panel, panel, "DirectLANHost", {280, 355, 369, 68}, "Host Game", Shell::kSkinToMainMenu, 1, 0, &Host);
            Shell::AddButton(panel, panel, "DirectLANRefresh", {790, 355, 369, 68}, "Refresh", Shell::kSkinToMainMenu, 1, 0, &Refresh);
            Shell::AddLabel(panel, panel, "DirectLANListTitle", {272, 450, 896, 40}, "NEARBY GAMES");
            for (size_t i = 0; i < g_Rows.size(); ++i)
            {
                const std::string name = "DirectLANRow" + std::to_string(i);
                g_Rows[i] = Shell::AddButton(panel, panel, name.c_str(), {272, 500 + float(i) * 43, 896, 40}, "-",
                    {nullptr, "optionhv.png", "optionck.png"}, 0.8f, 0, &Join);
            }
            Shell::AddPanel(panel, panel, "DirectLANAddressWell", {272, 780, 550, 48}, "optionhv.png");
            Shell::AddButton(panel, panel, "DirectLANJoinIP", {846, 780, 322, 48}, "Join by IP", Shell::kSkinToMainMenu, 0.85f, 0, &JoinIP);
            g_Status = Shell::AddLabel(panel, panel, "DirectLANStatus", {272, 855, 896, 40}, "");
            const bool back = Shell::AddButton(panel, nullptr, "DirectLANBack", {0, 0, 342, 77}, "Back", Shell::kSkinTopCorner, 1, 28, &BackLan) != nullptr;
            CreatePreLobbyServerEntry(panel, 280, 780, 534, 48, ""); PreLobbySetServerEntryVisible(true);
            Status(kPreviewStatus); Refresh(); return back;
        }
        void ClosedLan(void*)
        { g_Browser.reset(); ResetPreLobbyLobbyWidgets(); g_Status = nullptr; g_Rows.fill(nullptr); }
        bool CharLan(void*, uint8_t ch) { return PreLobbyForwardChar(ch); }
    }
    bool RegisterScreens()
    {
        static bool attempted = false;
        if (attempted) return g_Registered;
        attempted = true;
        const bool choice = Shell::RegisterScreen({Shell::kConnectionSetupScreenId, "ConnectionSetup", &BuildChoice, nullptr});
        const bool lan = Shell::RegisterScreen({Shell::kDirectLanScreenId, "DirectLANPreview", &BuildLan, &ClosedLan, &TickLan, &CharLan});
        g_Registered = choice && lan; return g_Registered;
    }
    bool PreviewEnabled()
    { bool enabled = false; TryGetUserConfigBool("Network", "ConnectionSetupPreview", enabled); return g_Registered && enabled; }
    uint32_t EntryScreen() { return PreviewEnabled() ? Shell::kConnectionSetupScreenId : Shell::kPreLobbyScreenId; }
}
