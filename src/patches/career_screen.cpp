// career_screen.cpp
// BZR Open Shim - the Career shell screen: what career_stats.cfg has recorded,
// on a screen built like the stock ones (shell_screens.cpp). The title menu's
// CAREER button (bzr_options_ui.cpp) asks the shell for it; Back and Esc pop
// it like any stock screen.
//
// The panel art is resources/ui/custom_widgets/osh_career_center.png, painted
// by mkscreens.py. Its title plate and four boxes are the layout contract with
// the constants below; change both together.

#include "bzr_options_ui.h"
#include "patcher.h"
#include "shell_screens.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unordered_set>

namespace BZROpenShim
{
    namespace
    {
        namespace Shell = ShellScreens;

        constexpr const char* kCareerPanelTexture = "osh_career_center.png";

        // mkscreens.py CAREER_LAYOUT.
        constexpr Shell::Rect kTitleRect = { 470.0f, 132.0f, 500.0f, 56.0f };
        constexpr Shell::Rect kBoxRects[] = {
            { 244.0f, 238.0f, 464.0f, 300.0f },
            { 732.0f, 238.0f, 464.0f, 300.0f },
            { 244.0f, 566.0f, 464.0f, 300.0f },
            { 732.0f, 566.0f, 464.0f, 300.0f },
        };
        constexpr float kBoxHeaderH = 44.0f;   // painted header band
        constexpr float kBoxPadX = 28.0f;
        constexpr float kRowTop = 62.0f;       // first row, below the header band
        constexpr float kRowH = 46.0f;
        constexpr float kValueW = 150.0f;
        constexpr size_t kRowsPerBox = 5;

        // The stock top-corner Back button: Options builds its Back as
        // (0, 0, 342, 77) with the topcorner skin and a 28-unit caption inset.
        constexpr Shell::Rect kBackRect = { 0.0f, 0.0f, 342.0f, 77.0f };
        constexpr float kBackTextOffset = 28.0f;

        // ------------------------------------------------------------------
        // career_stats.cfg reader
        // ------------------------------------------------------------------
        //
        // The file is the flat "key=value" document bzr_hooks.cpp writes. Keys
        // are namespaced per profile (profile.<key>.career.totalKills and so
        // on). Values are summed across profiles: an install normally has one,
        // and summing is the honest answer when it has more rather than
        // silently picking whichever came first.
        struct CareerTotals
        {
            bool fileFound = false;
            int profiles = 0;
            long long totalKills = 0;
            long long totalDeaths = 0;
            long long spKills = 0;
            long long spDeaths = 0;
            long long mpKills = 0;
            long long mpDeaths = 0;
            long long missionsPlayed = 0;
            long long spMissions = 0;
            long long mpMatches = 0;
            int missionsRecorded = 0;
        };

        std::filesystem::path GetCareerStatsPath()
        {
            return GetUserConfigPath().parent_path() / "career_stats.cfg";
        }

        void ReadCareerTotals(CareerTotals& out)
        {
            out = CareerTotals{};

            std::ifstream input(GetCareerStatsPath());
            if (!input.is_open())
                return;
            out.fileFound = true;

            std::unordered_set<std::string> profileKeys;
            std::unordered_set<std::string> missionKeys;

            std::string line;
            while (std::getline(input, line))
            {
                const size_t split = line.find('=');
                if (split == std::string::npos || split == 0)
                    continue;
                std::string key = line.substr(0, split);
                const long long value = std::atoll(line.c_str() + split + 1);

                if (key.rfind("profile.", 0) != 0)
                    continue;

                const size_t profileEnd = key.find('.', sizeof("profile.") - 1);
                if (profileEnd == std::string::npos)
                    continue;
                profileKeys.insert(key.substr(0, profileEnd));

                const std::string tail = key.substr(profileEnd + 1);
                if (tail == "career.totalKills")            out.totalKills += value;
                else if (tail == "career.totalDeaths")      out.totalDeaths += value;
                else if (tail == "career.spKills")          out.spKills += value;
                else if (tail == "career.spDeaths")         out.spDeaths += value;
                else if (tail == "career.mpKills")          out.mpKills += value;
                else if (tail == "career.mpDeaths")         out.mpDeaths += value;
                else if (tail == "career.missionsPlayed")   out.missionsPlayed += value;
                else if (tail == "career.spMissionsPlayed") out.spMissions += value;
                else if (tail == "career.mpMatchesPlayed")  out.mpMatches += value;
                else if (tail.rfind("mission.", 0) == 0)
                {
                    const size_t nameEnd = tail.find('.', sizeof("mission.") - 1);
                    if (nameEnd != std::string::npos)
                        missionKeys.insert(tail.substr(0, nameEnd));
                }
            }

            out.profiles = static_cast<int>(profileKeys.size());
            out.missionsRecorded = static_cast<int>(missionKeys.size());
        }

        std::string FormatRatio(long long kills, long long deaths)
        {
            if (deaths <= 0)
                return kills > 0 ? "perfect" : "-";
            char buffer[32] = {};
            _snprintf_s(buffer, _TRUNCATE, "%.2f",
                        static_cast<double>(kills) / static_cast<double>(deaths));
            return buffer;
        }

        // One box of the page: a title in the painted header band and up to
        // kRowsPerBox caption/value rows. Captions and values are separate
        // labels on fixed columns so the numbers line up; the font is
        // proportional, so padding one string with spaces aligns nothing.
        struct CareerRow
        {
            std::string caption;
            std::string value;
        };
        struct CareerBox
        {
            std::string title;
            CareerRow rows[kRowsPerBox];
        };

        void BuildCareerBoxes(CareerBox (&boxes)[4])
        {
            CareerTotals t;
            ReadCareerTotals(t);
            const auto num = [](long long v) { return std::to_string(v); };

            boxes[0].title = "OVERALL";
            boxes[0].rows[0] = { "Kills", num(t.totalKills) };
            boxes[0].rows[1] = { "Deaths", num(t.totalDeaths) };
            boxes[0].rows[2] = { "Kill / death", FormatRatio(t.totalKills, t.totalDeaths) };

            boxes[1].title = "SINGLE PLAYER";
            boxes[1].rows[0] = { "Kills", num(t.spKills) };
            boxes[1].rows[1] = { "Deaths", num(t.spDeaths) };
            // career.spMissionsPlayed is written only by the OpenShim career
            // layer; career.missionsPlayed predates it and is what every record
            // written before this feature shipped actually carries. Preferring
            // the specific key and falling back to the general one is why an
            // existing install reads its real total instead of a flat zero.
            boxes[1].rows[2] = { "Missions played", num(t.spMissions > 0 ? t.spMissions : t.missionsPlayed) };

            boxes[2].title = "MULTIPLAYER";
            boxes[2].rows[0] = { "Kills", num(t.mpKills) };
            boxes[2].rows[1] = { "Deaths", num(t.mpDeaths) };
            boxes[2].rows[2] = { "Matches played", num(t.mpMatches) };

            boxes[3].title = "RECORD";
            if (!t.fileFound)
            {
                boxes[3].rows[0] = { "No record yet.", "" };
                boxes[3].rows[1] = { "Kills, deaths and missions", "" };
                boxes[3].rows[2] = { "are recorded as you play.", "" };
                boxes[3].rows[4] = { "Off switch: OpenShim Settings.", "" };
                return;
            }
            boxes[3].rows[0] = { "Distinct missions", num(t.missionsRecorded) };
            if (t.profiles > 1)
                boxes[3].rows[1] = { "Profiles combined", num(t.profiles) };
        }

        void __cdecl OnCareerBackClicked()
        {
            Shell::Back(Shell::LiveScreen(Shell::kCareerScreenId));
        }

        bool BuildCareerScreen(void* screen)
        {
            const char* texture =
                Shell::IsTextureDeployed(kCareerPanelTexture) ? kCareerPanelTexture : nullptr;
            if (!texture)
                Log(L"[CAREERUI] %hs is not deployed; Career shows the bare stock background\n",
                    kCareerPanelTexture);

            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimCareer_Overlay",
                                          { 0.0f, 0.0f, 1440.0f, 1080.0f }, texture);
            if (!panel)
                return false;

            Shell::AddLabel(panel, panel, "OpenShimCareer_Title", kTitleRect, "CAREER",
                            Shell::kTitleLabelFlags);

            CareerBox boxes[4];
            BuildCareerBoxes(boxes);
            char name[64] = {};
            for (size_t b = 0; b < 4; ++b)
            {
                const Shell::Rect& box = kBoxRects[b];
                _snprintf_s(name, _TRUNCATE, "OpenShimCareer_Box%zu", b);
                Shell::AddLabel(panel, panel, name,
                                { box.x + kBoxPadX, box.y + 4.0f, box.w - 2.0f * kBoxPadX, kBoxHeaderH - 6.0f },
                                boxes[b].title.c_str());

                for (size_t r = 0; r < kRowsPerBox; ++r)
                {
                    const CareerRow& row = boxes[b].rows[r];
                    if (row.caption.empty())
                        continue;
                    const float y = box.y + kRowTop + kRowH * static_cast<float>(r);
                    _snprintf_s(name, _TRUNCATE, "OpenShimCareer_Cap%zu_%zu", b, r);
                    Shell::AddLabel(panel, panel, name,
                                    { box.x + kBoxPadX, y, box.w - 2.0f * kBoxPadX - kValueW, kRowH },
                                    row.caption.c_str());
                    if (row.value.empty())
                        continue;
                    _snprintf_s(name, _TRUNCATE, "OpenShimCareer_Val%zu_%zu", b, r);
                    Shell::AddLabel(panel, panel, name,
                                    { box.x + box.w - kBoxPadX - kValueW, y, kValueW, kRowH },
                                    row.value.c_str());
                }
            }

            return Shell::AddButton(panel, nullptr, "OpenShimCareer_Back", kBackRect, "Back",
                                    Shell::kSkinTopCorner, 1.0f, kBackTextOffset,
                                    &OnCareerBackClicked) != nullptr;
        }
    }

    bool RegisterCareerScreen()
    {
        static const bool registered = Shell::RegisterScreen({
            Shell::kCareerScreenId, "Career", &BuildCareerScreen, nullptr });
        return registered;
    }
}
