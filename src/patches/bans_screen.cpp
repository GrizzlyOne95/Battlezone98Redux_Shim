// bans_screen.cpp
// BZR Open Shim - the Banned Players shell screen: every entry of bans.cfg
// with an Unban button, so a host need not hand-edit the file. Reached from the
// "Banned Players" row on the Network options page (bzr_options_ui.cpp).
//
// The panel art is resources/ui/custom_widgets/osh_bans_center.png, painted by
// mkscreens.py. Its list box, row wells, Unban slots and the status box are the
// layout contract with the constants below; change both together.
//
// Widgets can only be created inside the build call (a widget made from a
// click draws its caption but not its frame), so the ten row widgets are built
// once and re-texted or hidden as the list and page change.

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shell_screens.h"

#include <array>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        namespace Shell = ShellScreens;

        constexpr const char* kBansPanelTexture = "osh_bans_center.png";

        // mkscreens.py BANS_LAYOUT.
        constexpr Shell::Rect kTitleRect = { 470.0f, 132.0f, 500.0f, 56.0f };
        constexpr size_t kRowsPerPage = 10;
        constexpr float kRowTop = 292.0f;
        constexpr float kRowPitch = 42.0f;
        constexpr float kRowH = 40.0f;
        constexpr float kNameX = 284.0f, kNameW = 400.0f;
        constexpr float kIdX = 696.0f, kIdW = 300.0f;
        constexpr Shell::Rect kUnbanRect = { 1018.0f, 0.0f, 150.0f, kRowH };  // y per row
        constexpr Shell::Rect kPrevRect = { 272.0f, 796.0f, 150.0f, 40.0f };
        constexpr Shell::Rect kNextRect = { 1018.0f, 796.0f, 150.0f, 40.0f };
        constexpr Shell::Rect kPageRect = { 440.0f, 800.0f, 560.0f, 32.0f };
        constexpr Shell::Rect kStatusRect = { 272.0f, 764.0f, 896.0f, 28.0f };
        // The painted slot is the resting state; the button only adds hover and
        // press, as on the LAN screen. Without the art, stock slot textures.
        constexpr size_t kMaxNameChars = 26;
        constexpr size_t kMaxIdChars = 26;

        // The stock top-corner Back button, as Career builds it.
        constexpr Shell::Rect kBackRect = { 0.0f, 0.0f, 342.0f, 77.0f };
        constexpr float kBackTextOffset = 28.0f;

        std::array<void*, kRowsPerPage> g_NameLabels{};
        std::array<void*, kRowsPerPage> g_IdLabels{};
        std::array<void*, kRowsPerPage> g_UnbanButtons{};
        void* g_EmptyLabel = nullptr;
        void* g_StatusLabel = nullptr;
        void* g_PageLabel = nullptr;
        void* g_PrevButton = nullptr;
        void* g_NextButton = nullptr;

        std::vector<Hooks::BanRecord> g_Bans;
        size_t g_Page = 0;
        // The id whose Unban button shows "Confirm"; empty when none is armed.
        // Keyed by id, not row, so a re-listed page never confirms another ban.
        std::string g_ArmedId;

        std::string CutText(const std::string& text, size_t maxChars)
        {
            if (text.size() <= maxChars)
                return text;
            // Byte cut; step back off UTF-8 continuation bytes so a non-ASCII
            // name never ends in half a character.
            size_t cut = maxChars - 3;
            while (cut > 0 && (static_cast<unsigned char>(text[cut]) & 0xC0) == 0x80)
                --cut;
            return text.substr(0, cut) + "...";
        }

        size_t PageCount()
        {
            return g_Bans.empty() ? 1 : (g_Bans.size() + kRowsPerPage - 1) / kRowsPerPage;
        }

        void SetShown(void* view, bool shown)
        {
            if (view && g_BzrFn_UiSetActive)
                g_BzrFn_UiSetActive(view, shown ? 1 : 0);
        }

        // Live run: UiSetActive(0) on a freshly built screen left the captions
        // drawn (likely the screen re-shows its children on activation). The painted
        // slot is the button's resting frame, so a blank caption reads as an
        // empty slot; clicks on unused rows are already ignored by index.
        void SetCaption(void* button, const char* text)
        {
            if (button && g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(button, text);
        }

        void SetStatus(const std::string& text)
        {
            Shell::SetLabelText(g_StatusLabel, text.c_str());
        }

        // Re-reads bans.cfg's in-memory list and redraws the current page.
        void RefreshRows()
        {
            g_Bans = Hooks::GetBanRecordsSnapshot();
            if (g_Page >= PageCount())
                g_Page = PageCount() - 1;

            for (size_t row = 0; row < kRowsPerPage; ++row)
            {
                const size_t index = g_Page * kRowsPerPage + row;
                const bool used = index < g_Bans.size();
                const Hooks::BanRecord* ban = used ? &g_Bans[index] : nullptr;

                Shell::SetLabelText(g_NameLabels[row],
                    ban ? CutText(ban->name.empty() ? "(unnamed)" : ban->name, kMaxNameChars).c_str() : "");
                Shell::SetLabelText(g_IdLabels[row],
                    ban ? CutText(ban->id, kMaxIdChars).c_str() : "");
                SetShown(g_UnbanButtons[row], used);
                SetCaption(g_UnbanButtons[row], !used ? "" : ban->id == g_ArmedId ? "Confirm" : "Unban");
            }

            Shell::SetLabelText(g_EmptyLabel, g_Bans.empty()
                ? "No banned players. Use the lobby Ban button or /ban while hosting." : "");

            const bool paged = PageCount() > 1;
            SetShown(g_PrevButton, paged);
            SetShown(g_NextButton, paged);
            SetCaption(g_PrevButton, paged ? "Prev" : "");
            SetCaption(g_NextButton, paged ? "Next" : "");
            char page[32] = {};
            if (paged)
                _snprintf_s(page, _TRUNCATE, "Page %zu/%zu", g_Page + 1, PageCount());
            Shell::SetLabelText(g_PageLabel, page);
        }

        template <size_t Row>
        void __cdecl OnUnbanClicked()
        {
            const size_t index = g_Page * kRowsPerPage + Row;
            if (index >= g_Bans.size())
                return;

            // Copy: the refresh below replaces the vector the entry lives in.
            const Hooks::BanRecord ban = g_Bans[index];
            const std::string label = ban.name.empty() ? ban.id : ban.name;
            if (ban.id != g_ArmedId)
            {
                g_ArmedId = ban.id;
                SetStatus("Click Confirm to unban " + CutText(label, kMaxNameChars) + ".");
                RefreshRows();
                return;
            }

            g_ArmedId.clear();
            if (Hooks::RemoveBanConfigEntry(ban.id.c_str(), "ban screen"))
                SetStatus("Unbanned " + CutText(label, kMaxNameChars) + ". They can join your next game.");
            else
                SetStatus("Could not unban " + CutText(label, kMaxNameChars) + "; see openshim.log ([BAN]).");
            RefreshRows();
        }

        void __cdecl OnPrevClicked()
        {
            g_ArmedId.clear();
            SetStatus("");
            g_Page = g_Page ? g_Page - 1 : PageCount() - 1;
            RefreshRows();
        }

        void __cdecl OnNextClicked()
        {
            g_ArmedId.clear();
            SetStatus("");
            g_Page = (g_Page + 1) % PageCount();
            RefreshRows();
        }

        void __cdecl OnBansBackClicked()
        {
            Shell::Back(Shell::LiveScreen(Shell::kBansScreenId));
        }

        template <size_t... Rows>
        void BuildUnbanButtons(void* panel, const Shell::ButtonSkin& skin, std::index_sequence<Rows...>)
        {
            constexpr void(__cdecl* callbacks[])() = { &OnUnbanClicked<Rows>... };
            char name[48] = {};
            for (size_t row = 0; row < kRowsPerPage; ++row)
            {
                const float y = kRowTop + kRowPitch * static_cast<float>(row);
                _snprintf_s(name, _TRUNCATE, "OpenShimBans_Name%zu", row);
                g_NameLabels[row] = Shell::AddLabel(panel, panel, name,
                    { kNameX, y, kNameW, kRowH }, "");
                _snprintf_s(name, _TRUNCATE, "OpenShimBans_Id%zu", row);
                g_IdLabels[row] = Shell::AddLabel(panel, panel, name,
                    { kIdX, y, kIdW, kRowH }, "");
                _snprintf_s(name, _TRUNCATE, "OpenShimBans_Unban%zu", row);
                g_UnbanButtons[row] = Shell::AddButton(panel, panel, name,
                    { kUnbanRect.x, y, kUnbanRect.w, kUnbanRect.h }, "Unban", skin, 1.0f, 0.0f, callbacks[row]);
            }
        }

        bool BuildBansScreen(void* screen)
        {
            g_Bans.clear();
            g_Page = 0;
            g_ArmedId.clear();

            const bool hasArt = Shell::IsTextureDeployed(kBansPanelTexture);
            if (!hasArt)
                Log(L"[BANSUI] %hs is not deployed; Banned Players shows the bare stock background\n",
                    kBansPanelTexture);

            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimBans_Overlay",
                                          { 0.0f, 0.0f, 1440.0f, 1080.0f },
                                          hasArt ? kBansPanelTexture : nullptr);
            if (!panel)
                return false;

            Shell::AddLabel(panel, panel, "OpenShimBans_Title", kTitleRect, "BANNED PLAYERS",
                            Shell::kTitleLabelFlags);

            Shell::ButtonSkin slot{ "optionhv.png", "optionhv.png", "optionck.png" };
            if (hasArt && Shell::IsTextureDeployed("osh_tool_hv.png") && Shell::IsTextureDeployed("osh_tool_ck.png"))
                slot = { nullptr, "osh_tool_hv.png", "osh_tool_ck.png" };

            g_EmptyLabel = Shell::AddLabel(panel, panel, "OpenShimBans_Empty",
                { kNameX, kRowTop, 880.0f, kRowH }, "");
            BuildUnbanButtons(panel, slot, std::make_index_sequence<kRowsPerPage>{});

            g_StatusLabel = Shell::AddLabel(panel, panel, "OpenShimBans_Status", kStatusRect, "");
            g_PageLabel = Shell::AddLabel(panel, panel, "OpenShimBans_Page", kPageRect, "");
            g_PrevButton = Shell::AddButton(panel, panel, "OpenShimBans_Prev", kPrevRect,
                                            "Prev", slot, 1.0f, 0.0f, &OnPrevClicked);
            g_NextButton = Shell::AddButton(panel, panel, "OpenShimBans_Next", kNextRect,
                                            "Next", slot, 1.0f, 0.0f, &OnNextClicked);
            RefreshRows();

            return Shell::AddButton(panel, nullptr, "OpenShimBans_Back", kBackRect, "Back",
                                    Shell::kSkinTopCorner, 1.0f, kBackTextOffset,
                                    &OnBansBackClicked) != nullptr;
        }

        // The widgets die with the screen; drop the pointers so a stale click
        // path can never touch them.
        void OnBansClosed(void*)
        {
            g_NameLabels.fill(nullptr);
            g_IdLabels.fill(nullptr);
            g_UnbanButtons.fill(nullptr);
            g_EmptyLabel = g_StatusLabel = g_PageLabel = g_PrevButton = g_NextButton = nullptr;
            g_Bans.clear();
            g_ArmedId.clear();
        }
    }

    bool RegisterBansScreen()
    {
        static const bool registered = Shell::RegisterScreen({
            Shell::kBansScreenId, "Banned Players", &BuildBansScreen, &OnBansClosed });
        return registered;
    }
}
