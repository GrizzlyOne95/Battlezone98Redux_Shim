// database_screen.cpp
// BZR Open Shim - the single-player Database screen (Docs/DATABASE_SCREEN.md):
// a DATABASE button on the stock Single Player screen opens an OpenShim shell
// screen with faction tabs on the left, a paged entry list under them, and the
// selected entry on the right. Back and Esc return to Single Player.
//
// Content: resources/database/oshdb.cfg, embedded in the DLL; an oshdb.cfg
// the game's file system finds (the enabled mod, e.g. Campaign Reimagined)
// merges over it (DatabasePolicy::MergeContent). Units show their .inf header
// and live ODF stats; the Briefings tab shows each mission's .des pages
// through the lobby Briefing overlay's reader (des_reader.cpp).
//
// Engine sites: no new addresses. The button rides the stock-screen observer
// (ShellScreens::ObserveStockScreen) for shell screen 2; files are read with
// the PathBlock::ReadFile row; the text block uses the ScrollingTextBlock rows
// the lobby overlay already binds.
//
// Widgets can only be created inside the build call (bans_screen.cpp), so the
// tab buttons, list rows and page buttons are built once and re-texted.

#include <Windows.h>
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "database_policy.h"
#include "database_content_resources.h"
#include "des_reader.h"
#include "hook_engine.h"
#include "lobby_briefing_policy.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "shell_screens.h"
#include "ui_decor.h"

#include <array>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <vector>

using BZROpenShim::L10n::ShimText;
using BZROpenShim::L10n::ShimFormat;

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace Db = DatabasePolicy;
            namespace Brief = LobbyBriefingPolicy;
            namespace Shell = ShellScreens;

            // ---- stock Single Player screen (cUI_SinglePlayer) ----
            // Shell factory case 2 (FUN_007c7ad0 lines 88-107): operator_new(0x180)
            // then the ctor FUN_007bf440. Its vtable (0x008A0350, stored at
            // 0x007BF489) carries the RTTI name below; it is checked on the live
            // object, so no address row is needed.
            constexpr uint32_t kSinglePlayerScreenId = 2;
            constexpr char kSinglePlayerRtti[] = ".?AVcUI_SinglePlayer@@";
            // Middle_Overlay (0,0,1440,1080, flags 0x60): FUN_007bf440 stores it
            // at +0x14C (decompile `param_1[0x53] = local_4bc`; GOG exe
            // 0x007BF5A8 `mov [eax+0x14c], ecx`).
            constexpr size_t kSpMiddleOverlay = 0x14C;
            // Training prompt: FUN_007bf440 lines 63-66 store FUN_004894f0()'s
            // result at +0x17C (GOG exe 0x007BF4D5 `mov [ecx+0x17c], al`), and
            // line 132 builds the normal screen only when it is zero; otherwise
            // the screen offers the training missions instead. No button then.
            constexpr size_t kSpTrainingPrompt = 0x17C;

            // ---- DATABASE button position: MOVE IT HERE ----
            // Design space 1440x1080 of the Single Player Middle_Overlay. Top
            // centre: the stock Red Odyssey button is 369x68 with the same
            // tomnoff skin at bottom centre (y 1012); this mirrors it at the top,
            // between the top-corner Back (x 0..342) and Campaign buttons and
            // above the posters video (y 85). x = (1440 - 369) / 2.
            const Shell::Rect kDatabaseButtonRect{ 535.5f, 4.0f, 369.0f, 68.0f };

            // ---- Database screen layout (1440x1080 design space) ----
            const Shell::Rect kTitleRect{ 470.0f, 88.0f, 500.0f, 56.0f };
            const Shell::Rect kLeftFrame{ 50.0f, 160.0f, 570.0f, 830.0f };
            const Shell::Rect kRightFrame{ 640.0f, 160.0f, 750.0f, 830.0f };
            constexpr size_t kMaxTabs = 6;
            constexpr float kTabX = 66.0f, kTabY = 178.0f, kTabW = 210.0f, kTabH = 56.0f, kTabPitch = 66.0f;
            constexpr size_t kRowsPerPage = 16;
            constexpr float kRowX = 290.0f, kRowY = 178.0f, kRowW = 316.0f, kRowH = 40.0f, kRowPitch = 44.0f;
            constexpr size_t kMaxRowChars = 26;
            constexpr size_t kMaxTabChars = 17;  // kMaxRowChars scaled by kTabW / kRowW
            const Shell::Rect kListPrevRect{ 290.0f, 918.0f, 150.0f, 50.0f };
            const Shell::Rect kListNextRect{ 456.0f, 918.0f, 150.0f, 50.0f };
            const Shell::Rect kListPageRect{ 66.0f, 926.0f, 210.0f, 36.0f };
            const Shell::Rect kDetailTitleRect{ 660.0f, 172.0f, 710.0f, 44.0f };
            const Shell::Rect kImageRect{ 660.0f, 224.0f, 710.0f, 400.0f };
            const Shell::Rect kTextRect{ 660.0f, 636.0f, 710.0f, 270.0f };
            const Shell::Rect kPagePrevRect{ 660.0f, 918.0f, 150.0f, 50.0f };
            const Shell::Rect kPageNextRect{ 1220.0f, 918.0f, 150.0f, 50.0f };
            const Shell::Rect kPageLabelRect{ 830.0f, 926.0f, 370.0f, 36.0f };
            const Shell::Rect kBackRect{ 0.0f, 0.0f, 342.0f, 77.0f };
            constexpr float kBackTextOffset = 28.0f;
            const Shell::ButtonSkin kTabSkin{ "MultiplayerModeButton_off.png", "MultiplayerModeButton_over.png",
                                              "MultiplayerModeButton_on.png" };
            // List rows show nothing at rest, a highlight on hover (stock option slots).
            const Shell::ButtonSkin kRowSkin{ nullptr, "optionhv.png", "optionck.png" };

            // cUI_ScrollingTextBlock (ctor 0x007CD8D0), as lobby_briefing.cpp.
            constexpr size_t kScrollingTextBlockSize = 0x295C;
            constexpr size_t kScrollDownArrow = 0x2954;
            constexpr size_t kScrollPosition = 0x2958;
            constexpr int kTextColour = 3;  // green, the stock briefing text colour

            constexpr int kFileReadMax = 1024 * 1024;

            using FnScrollingTextBlockCtor = void*(__thiscall*)(void* self, char flag, const char* name,
                                                               float x, float y, float w, float h,
                                                               void(__cdecl* onPageUp)(), void(__cdecl* onPageDown)(),
                                                               uint32_t flags, void* parent);
            using FnSetText = void(__thiscall*)(void* block, const char* text, int colourIndex);
            using FnScroll = void(__thiscall*)(void* block);
            using FnGameNew = void*(__cdecl*)(size_t size);
            using FnReadFile = int(__cdecl*)(const char* name, int* size, void* buffer, int capacity);

            bool g_Active = false;
            bool g_GaveUp = false;
            uint32_t g_TextCtorAddr = 0, g_SetTextAddr = 0, g_ScrollUpAddr = 0, g_ScrollDownAddr = 0;
            FnGameNew g_GameNew = nullptr;
            FnReadFile g_ReadFile = nullptr;

            // The Single Player screen the button was last built on. The button
            // is its child, so a click always comes while it is live.
            void* g_SpScreen = nullptr;

            // ---- list model ----

            enum class EntryKind
            {
                Unit,
                Mission,
                Other,
            };

            struct Entry
            {
                EntryKind kind = EntryKind::Other;
                const Db::Section* section = nullptr;
                std::string caption;
                std::string mission;  // Mission: the .des stem
            };

            struct Ui
            {
                std::array<void*, kMaxTabs> tabs{};
                std::array<void*, kRowsPerPage> rows{};
                void* listPrev = nullptr;
                void* listNext = nullptr;
                void* listPage = nullptr;
                void* detailTitle = nullptr;
                void* image = nullptr;
                void* text = nullptr;
                void* pagePrev = nullptr;
                void* pageNext = nullptr;
                void* pageLabel = nullptr;
            };

            struct State
            {
                Db::Content content;
                std::vector<const Db::Section*> tabs;
                size_t tab = 0;
                std::vector<Entry> entries;
                size_t listPage = 0;
                int selected = -1;
                // Briefing pages of the selected mission.
                std::vector<std::string> pages;
                std::vector<std::string> pageImages;
                int page = 1;
                std::string loadedImage;
                std::map<std::string, Db::InfHeader> infCache;
                std::map<std::string, std::string> weaponNames;
                std::map<std::string, std::string> unitNames;
                Ui ui;
            };
            State g_State;

            // ---- file reads ----

            bool SafeReadFile(const char* name, int& size, void* buffer, int capacity)
            {
                __try
                {
                    return g_ReadFile(name, &size, buffer, capacity) != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // The game's own file read, so mod and packed files resolve as the
            // game loads them. Same two-attempt contract as kill_ticker.cpp: a
            // loose file reports its size before failing on a short buffer.
            bool ReadGameText(const std::string& file, std::string& out)
            {
                out.clear();
                if (!g_ReadFile || file.empty())
                    return false;
                // Absent files never reach the engine read (it logs a miss).
                const size_t known = DesReader::ResourceSize(file);
                if (known == 0)
                    return false;
                const size_t capacity = known <= static_cast<size_t>(kFileReadMax) ? known + 1
                                                                                  : static_cast<size_t>(kFileReadMax);
                std::vector<char> buffer(capacity);
                for (int attempt = 0; attempt < 2; ++attempt)
                {
                    int size = 0;
                    if (SafeReadFile(file.c_str(), size, buffer.data(), static_cast<int>(buffer.size())) &&
                        size > 0 && static_cast<size_t>(size) <= buffer.size())
                    {
                        out.assign(buffer.data(), static_cast<size_t>(size));
                        return true;
                    }
                    const int retry = size > static_cast<int>(buffer.size()) ? size : 0;
                    if (attempt > 0 || retry <= 0 || retry > kFileReadMax)
                        break;
                    buffer.resize(static_cast<size_t>(retry));
                }
                Log(L"[DATABASE] could not read %hs (%zu bytes; cap %d)\n", file.c_str(), known, kFileReadMax);
                return false;
            }

            bool ReadEmbeddedContent(std::string& out)
            {
                HMODULE module = nullptr;
                if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                        reinterpret_cast<LPCSTR>(&g_State), &module))
                    return false;
                HRSRC resource = FindResourceA(module, MAKEINTRESOURCEA(IDR_OPENSHIM_DATABASE_CONTENT), RT_RCDATA);
                HGLOBAL loaded = resource ? LoadResource(module, resource) : nullptr;
                const void* data = loaded ? LockResource(loaded) : nullptr;
                const DWORD size = resource ? SizeofResource(module, resource) : 0;
                if (!data || size == 0)
                    return false;
                out.assign(static_cast<const char*>(data), size);
                return true;
            }

            void LogErrors(const char* source, const std::vector<std::string>& errors)
            {
                for (const std::string& e : errors)
                    Log(L"[DATABASE] %hs %hs\n", source, e.c_str());
            }

            // Stock content, with a mod's oshdb.cfg merged over it.
            Db::Content LoadContent()
            {
                std::string text;
                std::vector<std::string> errors;
                Db::Content stock;
                if (ReadEmbeddedContent(text))
                    stock = Db::ParseContent(text, &errors);
                else
                    Log(L"[DATABASE] embedded content missing; only a mod's %hs can fill the screen\n",
                        Db::kContentFileName);
                LogErrors("embedded content", errors);

                if (!ReadGameText(Db::kContentFileName, text))
                    return stock;
                errors.clear();
                const Db::Content override = Db::ParseContent(text, &errors);
                LogErrors("override", errors);
                Log(L"[DATABASE] %hs from the game file system merged (%zu sections)\n", Db::kContentFileName,
                    override.sections.size());
                std::vector<std::string> warnings;
                const Db::Content merged = Db::MergeContent(stock, override, &warnings);
                LogErrors("override", warnings);
                return merged;
            }

            const Db::InfHeader& InfFor(const std::string& odf)
            {
                auto found = g_State.infCache.find(odf);
                if (found != g_State.infCache.end())
                    return found->second;
                std::string text;
                Db::InfHeader header;
                if (ReadGameText(odf + ".inf", text))
                    header = Db::ParseInfHeader(text);
                return g_State.infCache.emplace(odf, header).first->second;
            }

            // [GameObjectClass] unitName of an ODF, for units with no .inf header.
            std::string OdfUnitName(const std::string& odf)
            {
                auto found = g_State.unitNames.find(odf);
                if (found != g_State.unitNames.end())
                    return found->second;
                std::string text;
                std::string name;
                if (ReadGameText(odf + ".odf", text))
                    name = Db::ParseOdf(text).Get("GameObjectClass", "unitName");
                g_State.unitNames.emplace(odf, name);
                return name;
            }

            std::string WeaponName(const std::string& weaponOdf)
            {
                auto found = g_State.weaponNames.find(weaponOdf);
                if (found != g_State.weaponNames.end())
                    return found->second;
                std::string text;
                std::string name;
                if (ReadGameText(weaponOdf + ".odf", text))
                    name = Db::ParseOdf(text).Get("WeaponClass", "wpnName");
                g_State.weaponNames.emplace(weaponOdf, name);
                return name;
            }

            // ---- widgets ----

            // Cuts to `maxChars` bytes with "...", never inside a UTF-8 sequence.
            std::string CutText(const std::string& text, size_t maxChars)
            {
                if (text.size() <= maxChars)
                    return text;
                size_t cut = maxChars - 3;
                while (cut > 0 && (static_cast<unsigned char>(text[cut]) & 0xC0) == 0x80)
                    --cut;  // text[cut] is a continuation byte: back up to its lead byte
                return text.substr(0, cut) + "...";
            }

            void SetShown(void* view, bool shown)
            {
                if (view && g_BzrFn_UiSetActive)
                    g_BzrFn_UiSetActive(view, shown ? 1 : 0);
            }

            void SetCaption(void* button, const std::string& text)
            {
                if (button && g_BzrFn_SetButtonLabel)
                    g_BzrFn_SetButtonLabel(button, text.c_str());
            }

            void SetLabel(void* label, const std::string& text)
            {
                if (label)
                    Shell::SetLabelText(label, text.c_str());
            }

            void SetDetailText(const std::string& text)
            {
                if (g_State.ui.text)
                    reinterpret_cast<FnSetText>(static_cast<uintptr_t>(g_SetTextAddr))(
                        g_State.ui.text, Brief::ClipPageText(text).c_str(), kTextColour);
            }

            void ShowImage(const std::string& image)
            {
                State& s = g_State;
                if (image.empty() || !s.ui.image || !g_BzrFn_SetTextureOff || !DesReader::ImageExists(image))
                {
                    SetShown(s.ui.image, false);
                    return;
                }
                if (s.loadedImage != image)
                {
                    g_BzrFn_SetTextureOff(s.ui.image, image.c_str());
                    s.loadedImage = image;
                }
                SetShown(s.ui.image, true);
            }

            bool ReadPointerSeh(const void* object, size_t offset, void*& out)
            {
                out = nullptr;
                __try
                {
                    out = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(object) + offset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadByteSeh(const void* object, size_t offset, uint8_t& out)
            {
                out = 0;
                __try
                {
                    out = static_cast<const uint8_t*>(object)[offset];
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ViewInputActive(void* widget)
            {
                uint8_t active = 0;
                return widget && ReadByteSeh(widget, kUiViewInputActiveOffset, active) && active != 0;
            }

            void __cdecl OnScrollUp()
            {
                void* block = g_State.ui.text;
                if (!block)
                    return;
                __try
                {
                    // The stock scroll does not clamp; the up arrow only shows above 0.
                    if (*reinterpret_cast<int*>(static_cast<uint8_t*>(block) + kScrollPosition) > 0)
                        reinterpret_cast<FnScroll>(static_cast<uintptr_t>(g_ScrollUpAddr))(block);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            void __cdecl OnScrollDown()
            {
                void* block = g_State.ui.text;
                void* arrow = nullptr;
                // The down arrow is shown only while there is more text below.
                if (block && ReadPointerSeh(block, kScrollDownArrow, arrow) && ViewInputActive(arrow))
                    reinterpret_cast<FnScroll>(static_cast<uintptr_t>(g_ScrollDownAddr))(block);
            }

            // ---- detail pane ----

            void ShowBriefingPage(int requested)
            {
                State& s = g_State;
                const int count = static_cast<int>(s.pages.size());
                const bool paged = count > 1;
                if (count < 1)
                {
                    SetShown(s.ui.pagePrev, false);
                    SetShown(s.ui.pageNext, false);
                    SetCaption(s.ui.pagePrev, "");
                    SetCaption(s.ui.pageNext, "");
                    SetLabel(s.ui.pageLabel, "");
                    return;
                }
                const int page = BriefingPagesPolicy::ClampPage(requested, count);
                s.page = page;
                SetDetailText(s.pages[static_cast<size_t>(page - 1)]);
                ShowImage(s.pageImages[static_cast<size_t>(page - 1)]);
                SetShown(s.ui.pagePrev, paged);
                SetShown(s.ui.pageNext, paged);
                SetCaption(s.ui.pagePrev, paged ? ShimText("openshim_ui:database_prev", "Prev") : "");
                SetCaption(s.ui.pageNext, paged ? ShimText("openshim_ui:database_next", "Next") : "");
                SetLabel(s.ui.pageLabel, paged ? ShimFormat("openshim_ui:database_page", "Page %s",
                    std::to_string(page) + "/" + std::to_string(count)) : std::string());
            }

            Db::Labels LocalizedLabels()
            {
                Db::Labels l;
                l.role = ShimText("openshim_ui:database_role", "Role");
                l.model = ShimText("openshim_ui:database_model", "Model");
                l.designations = ShimText("openshim_ui:database_designations", "Model numbers");
                l.scrapCost = ShimText("openshim_ui:database_scrap", "Scrap cost");
                l.armor = ShimText("openshim_ui:database_armor", "Armor");
                l.ammo = ShimText("openshim_ui:database_ammo", "Ammo");
                l.speed = ShimText("openshim_ui:database_speed", "Speed");
                l.speedUnit = ShimText("openshim_ui:database_speed_unit", "m/s");
                l.weapons = ShimText("openshim_ui:database_weapons", "Weapons");
                l.slot = ShimText("openshim_ui:database_slot", "Slot");
                l.noWeapons = ShimText("openshim_ui:database_no_weapons", "none");
                l.odf = ShimText("openshim_ui:database_odf", "ODF");
                l.noOdf = ShimText("openshim_ui:database_no_odf", "ODF not found");
                l.lore = ShimText("openshim_ui:database_notes", "Notes");
                return l;
            }

            void ShowUnit(const Entry& entry)
            {
                const Db::Section& unit = *entry.section;
                const std::string& odfName = unit.id;
                const Db::InfHeader& inf = InfFor(odfName);
                Db::UnitDetail detail;
                detail.odf = odfName;
                detail.role = unit.Has("name") ? unit.Get("name") : inf.role;
                detail.model = unit.Has("model") ? unit.Get("model") : inf.model;
                for (const std::string& d : unit.GetAll("designation"))
                    detail.designations.push_back(Db::ParseDesignation(d));
                detail.lore = unit.Get("lore");
                std::string odfText;
                detail.odfFound = ReadGameText(odfName + ".odf", odfText);
                if (detail.odfFound)
                    detail.stats = Db::ReadStats(Db::ParseOdf(odfText), &WeaponName);
                SetLabel(g_State.ui.detailTitle, entry.caption);
                SetDetailText(Db::FormatUnitDetail(detail, LocalizedLabels()));
                ShowImage(unit.Get("icon"));
            }

            void ShowMission(const Entry& entry)
            {
                State& s = g_State;
                const std::string& stem = entry.mission;
                const std::string label = entry.section->Get("label", entry.section->id);
                const std::string source = entry.section->Get("source");
                SetLabel(s.ui.detailTitle, label + ": " + stem + (source.empty() ? std::string() : " (" + source + ")"));
                const int count = Brief::CountPages(stem, DesReader::ResourceExists);
                for (int page = 1; page <= count; ++page)
                {
                    s.pages.push_back(DesReader::LoadPage(Brief::PageTextFileName(stem, page)));
                    const std::string image = Brief::PageImageFileName(stem, page);
                    s.pageImages.push_back(DesReader::ImageExists(image) ? image : std::string());
                }
                if (count < 1)
                {
                    SetDetailText(ShimFormat("openshim_ui:database_no_briefing", "No briefing found (%s).",
                                             Brief::PageOneFileName(stem)));
                    ShowImage("");
                }
                ShowBriefingPage(1);
            }

            void ShowOther(const Entry& entry)
            {
                std::string text;
                for (const std::string& line : entry.section->GetAll("text"))
                    text += line + "\n";
                SetLabel(g_State.ui.detailTitle, entry.caption);
                SetDetailText(text);
                ShowImage(entry.section->Get("icon"));
            }

            void ShowSelected()
            {
                State& s = g_State;
                s.pages.clear();
                s.pageImages.clear();
                s.page = 1;
                ShowBriefingPage(1);  // no pages: hides the page controls
                if (s.selected < 0 || static_cast<size_t>(s.selected) >= s.entries.size())
                {
                    SetLabel(s.ui.detailTitle, "");
                    SetDetailText("");
                    ShowImage("");
                    return;
                }
                const Entry& entry = s.entries[static_cast<size_t>(s.selected)];
                switch (entry.kind)
                {
                case EntryKind::Unit:
                    ShowUnit(entry);
                    break;
                case EntryKind::Mission:
                    ShowMission(entry);
                    break;
                default:
                    ShowOther(entry);
                    break;
                }
            }

            // ---- list ----

            void RefreshList()
            {
                State& s = g_State;
                const size_t pages = Db::PageCount(s.entries.size(), kRowsPerPage);
                if (s.listPage >= pages)
                    s.listPage = pages - 1;
                for (size_t row = 0; row < kRowsPerPage; ++row)
                {
                    const size_t index = s.listPage * kRowsPerPage + row;
                    std::string caption;
                    if (index < s.entries.size())
                        caption = (static_cast<int>(index) == s.selected ? "> " : "") +
                                  CutText(s.entries[index].caption, kMaxRowChars);
                    SetCaption(s.ui.rows[row], caption);
                }
                const bool paged = pages > 1;
                SetShown(s.ui.listPrev, paged);
                SetShown(s.ui.listNext, paged);
                SetCaption(s.ui.listPrev, paged ? ShimText("openshim_ui:database_prev", "Prev") : "");
                SetCaption(s.ui.listNext, paged ? ShimText("openshim_ui:database_next", "Next") : "");
                SetLabel(s.ui.listPage, paged ? ShimFormat("openshim_ui:database_page", "Page %s",
                    std::to_string(s.listPage + 1) + "/" + std::to_string(pages)) : std::string());
                for (size_t t = 0; t < kMaxTabs; ++t)
                {
                    std::string caption;
                    if (t < s.tabs.size())
                    {
                        caption = s.tabs[t]->Get("label", s.tabs[t]->id);
                        if (t == s.tab)
                            caption = "> " + caption;
                        caption = CutText(caption, kMaxTabChars);
                    }
                    SetCaption(s.ui.tabs[t], caption);
                }
            }

            void BuildEntries()
            {
                State& s = g_State;
                s.entries.clear();
                if (s.tab >= s.tabs.size())
                    return;
                for (const Db::Section* section : s.content.InTab(s.tabs[s.tab]->id))
                {
                    if (section->kind == Db::kKindUnit)
                    {
                        const Db::InfHeader& inf = InfFor(section->id);
                        Entry e;
                        e.kind = EntryKind::Unit;
                        e.section = section;
                        const std::string model = section->Has("model") ? section->Get("model") : inf.model;
                        const std::string role = section->Has("name") ? section->Get("name") : inf.role;
                        e.caption = Db::UnitCaption(model, role,
                                                    model.empty() && role.empty() ? OdfUnitName(section->id) : std::string(),
                                                    section->id);
                        s.entries.push_back(e);
                    }
                    else if (section->kind == Db::kKindCampaign)
                    {
                        const std::string label = section->Get("label", section->id);
                        for (const std::string& value : section->GetAll("missions"))
                            for (const std::string& mission : Db::SplitList(value))
                            {
                                Entry e;
                                e.kind = EntryKind::Mission;
                                e.section = section;
                                e.mission = mission;
                                e.caption = label + " - " + mission;
                                s.entries.push_back(e);
                            }
                    }
                    else
                    {
                        Entry e;
                        e.section = section;
                        e.caption = section->Get("label", section->id);
                        s.entries.push_back(e);
                    }
                }
            }

            void SelectTab(size_t tab)
            {
                State& s = g_State;
                if (tab >= s.tabs.size())
                    return;
                s.tab = tab;
                s.listPage = 0;
                BuildEntries();
                s.selected = s.entries.empty() ? -1 : 0;
                RefreshList();
                ShowSelected();
            }

            template <size_t Tab>
            void __cdecl OnTabClicked()
            {
                if (g_State.ui.tabs[Tab])
                    SelectTab(Tab);
            }

            template <size_t Row>
            void __cdecl OnRowClicked()
            {
                State& s = g_State;
                const size_t index = s.listPage * kRowsPerPage + Row;
                if (!s.ui.rows[Row] || index >= s.entries.size())
                    return;
                s.selected = static_cast<int>(index);
                RefreshList();
                ShowSelected();
            }

            void __cdecl OnListPrev()
            {
                State& s = g_State;
                const size_t pages = Db::PageCount(s.entries.size(), kRowsPerPage);
                s.listPage = s.listPage ? s.listPage - 1 : pages - 1;
                RefreshList();
            }

            void __cdecl OnListNext()
            {
                State& s = g_State;
                s.listPage = (s.listPage + 1) % Db::PageCount(s.entries.size(), kRowsPerPage);
                RefreshList();
            }

            void __cdecl OnPagePrev()
            {
                if (!g_State.pages.empty())
                    ShowBriefingPage(g_State.page - 1);
            }

            void __cdecl OnPageNext()
            {
                if (!g_State.pages.empty())
                    ShowBriefingPage(g_State.page + 1);
            }

            void __cdecl OnBackClicked()
            {
                Shell::Back(Shell::LiveScreen(Shell::kDatabaseScreenId));
            }

            // ---- build ----

            template <size_t... I>
            void BuildTabs(void* panel, std::index_sequence<I...>)
            {
                constexpr void(__cdecl* callbacks[])() = { &OnTabClicked<I>... };
                char name[48] = {};
                for (size_t t = 0; t < kMaxTabs; ++t)
                {
                    _snprintf_s(name, _TRUNCATE, "OpenShimDatabase_Tab%zu", t);
                    g_State.ui.tabs[t] = Shell::AddButton(panel, panel, name,
                        { kTabX, kTabY + kTabPitch * static_cast<float>(t), kTabW, kTabH }, "", kTabSkin, 1.0f, 0.0f,
                        callbacks[t]);
                }
            }

            template <size_t... I>
            void BuildRows(void* panel, std::index_sequence<I...>)
            {
                constexpr void(__cdecl* callbacks[])() = { &OnRowClicked<I>... };
                char name[48] = {};
                for (size_t r = 0; r < kRowsPerPage; ++r)
                {
                    _snprintf_s(name, _TRUNCATE, "OpenShimDatabase_Row%zu", r);
                    g_State.ui.rows[r] = Shell::AddButton(panel, panel, name,
                        { kRowX, kRowY + kRowPitch * static_cast<float>(r), kRowW, kRowH }, "", kRowSkin, 1.0f, 0.0f,
                        callbacks[r]);
                }
            }

            void BuildFrame(void* panel, const Shell::Rect& frame, const char* tag)
            {
                if (!Shell::IsTextureDeployed("uiplate.png"))
                    return;
                char name[64] = {};
                _snprintf_s(name, _TRUNCATE, "OpenShimDatabase_%sPlate", tag);
                Shell::AddPanel(panel, panel, name, frame, "uiplate.png", Shell::kControlFlags);
                if (!Shell::IsTextureDeployed("uiline.png"))
                    return;
                UiDecorPanelDesc desc;
                desc.rect = { frame.x, frame.y, frame.w, frame.h };
                UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
                const size_t count = BuildUiDecorPanel(desc, pieces, kUiDecorMaxPanelPieces);
                for (size_t i = 0; i < count; ++i)
                {
                    _snprintf_s(name, _TRUNCATE, "OpenShimDatabase_%sBorder%zu", tag, i);
                    Shell::AddPanel(panel, panel, name, { pieces[i].rect.x, pieces[i].rect.y, pieces[i].rect.width,
                                                          pieces[i].rect.height }, pieces[i].texture,
                                    Shell::kControlFlags);
                }
            }

            void* MakeTextBlock(void* panel)
            {
                void* memory = g_GameNew(kScrollingTextBlockSize);
                if (!memory)
                    return nullptr;
                std::memset(memory, 0, kScrollingTextBlockSize);
                void* block = reinterpret_cast<FnScrollingTextBlockCtor>(static_cast<uintptr_t>(g_TextCtorAddr))(
                    memory, 0, "OpenShimDatabase_Text", kTextRect.x, kTextRect.y, kTextRect.w, kTextRect.h,
                    &OnScrollUp, &OnScrollDown, Shell::kControlFlags, panel);
                if (block)
                    g_BzrFn_AddChild(panel, block, 0);
                return block;
            }

            bool BuildDatabaseScreen(void* screen)
            {
                g_State = State();
                State& s = g_State;
                s.content = LoadContent();
                s.tabs = s.content.OfKind(Db::kKindTab);
                if (s.tabs.size() > kMaxTabs)
                {
                    Log(L"[DATABASE] %zu tabs in the content; showing the first %zu\n", s.tabs.size(), kMaxTabs);
                    s.tabs.resize(kMaxTabs);
                }

                void* panel = Shell::AddPanel(screen, nullptr, "OpenShimDatabase_Overlay",
                                              { 0.0f, 0.0f, 1440.0f, 1080.0f }, nullptr);
                if (!panel)
                    return false;
                BuildFrame(panel, kLeftFrame, "Left");
                BuildFrame(panel, kRightFrame, "Right");
                Shell::AddLabel(panel, panel, "OpenShimDatabase_Title", kTitleRect,
                                ShimText("openshim_ui:database_title", "DATABASE"), Shell::kTitleLabelFlags);

                BuildTabs(panel, std::make_index_sequence<kMaxTabs>{});
                BuildRows(panel, std::make_index_sequence<kRowsPerPage>{});
                s.ui.listPage = Shell::AddLabel(panel, panel, "OpenShimDatabase_ListPage", kListPageRect, "");
                s.ui.listPrev = Shell::AddButton(panel, panel, "OpenShimDatabase_ListPrev", kListPrevRect,
                    ShimText("openshim_ui:database_prev", "Prev"), kTabSkin, 1.0f, 0.0f, &OnListPrev);
                s.ui.listNext = Shell::AddButton(panel, panel, "OpenShimDatabase_ListNext", kListNextRect,
                    ShimText("openshim_ui:database_next", "Next"), kTabSkin, 1.0f, 0.0f, &OnListNext);

                s.ui.detailTitle = Shell::AddLabel(panel, panel, "OpenShimDatabase_DetailTitle", kDetailTitleRect, "");
                s.ui.image = Shell::AddPanel(panel, panel, "OpenShimDatabase_Image", kImageRect, nullptr,
                                             Shell::kControlFlags);
                s.ui.text = MakeTextBlock(panel);
                s.ui.pageLabel = Shell::AddLabel(panel, panel, "OpenShimDatabase_PageLabel", kPageLabelRect, "");
                s.ui.pagePrev = Shell::AddButton(panel, panel, "OpenShimDatabase_PagePrev", kPagePrevRect,
                    ShimText("openshim_ui:database_prev", "Prev"), kTabSkin, 1.0f, 0.0f, &OnPagePrev);
                s.ui.pageNext = Shell::AddButton(panel, panel, "OpenShimDatabase_PageNext", kPageNextRect,
                    ShimText("openshim_ui:database_next", "Next"), kTabSkin, 1.0f, 0.0f, &OnPageNext);

                const bool back = Shell::AddButton(panel, nullptr, "OpenShimDatabase_Back", kBackRect,
                                                   ShimText("openshim_ui:back", "Back"), Shell::kSkinTopCorner, 1.0f,
                                                   kBackTextOffset, &OnBackClicked) != nullptr;
                if (s.tabs.empty())
                {
                    Log(L"[DATABASE] the content defines no tabs; the screen is empty\n");
                    RefreshList();
                    ShowSelected();
                }
                else
                {
                    SelectTab(0);
                }
                Log(L"[DATABASE] screen built: %zu tabs, %zu sections\n", s.tabs.size(), s.content.sections.size());
                return back;
            }

            // The widgets die with the screen; drop every pointer to them.
            void OnDatabaseClosed(void*)
            {
                g_State = State();
            }

            // ---- Single Player button ----

            void __cdecl OnDatabaseButtonClicked()
            {
                if (!g_SpScreen || !Shell::RequestScreen(g_SpScreen, Shell::kDatabaseScreenId))
                    Log(L"[DATABASE] could not request the Database screen\n");
            }

            bool ShouldEnable();

            void OnSinglePlayerBuilt(void* screen)
            {
                if (!g_Active || !screen || !ShouldEnable())
                    return;
                uintptr_t vtable = 0;
                void* vtablePointer = nullptr;
                if (!ReadPointerSeh(screen, 0, vtablePointer))
                    return;
                vtable = reinterpret_cast<uintptr_t>(vtablePointer);
                if (!VtableTypeNameMatches(vtable, kSinglePlayerRtti))
                {
                    Log(L"[DATABASE] stock screen 2 is not cUI_SinglePlayer; no button\n");
                    return;
                }
                uint8_t trainingPrompt = 0;
                if (!ReadByteSeh(screen, kSpTrainingPrompt, trainingPrompt) || trainingPrompt != 0)
                {
                    Log(L"[DATABASE] Single Player shows the training prompt; no button this time\n");
                    return;
                }
                void* middle = nullptr;
                if (!ReadPointerSeh(screen, kSpMiddleOverlay, middle) || !middle)
                {
                    Log(L"[DATABASE] Single Player screen has no Middle_Overlay; no button\n");
                    return;
                }
                g_SpScreen = screen;
                if (!Shell::AddButton(middle, middle, "OpenShimDatabase_Button", kDatabaseButtonRect,
                                      ShimText("openshim_ui:database_button", "DATABASE"), Shell::kSkinToMainMenu,
                                      1.0f, 0.0f, &OnDatabaseButtonClicked))
                {
                    Log(L"[DATABASE] DATABASE button not built\n");
                    return;
                }
                Log(L"[DATABASE] DATABASE button added to Single Player\n");
            }

            bool ShouldEnable()
            {
                return !EnvFlagEnabled("OPENSHIM_DISABLE_DATABASE");
            }
        }

        void InstallDatabaseScreenIfPossible()
        {
            if (g_Active || g_GaveUp)
                return;
            // The setting is read per Single Player build (OnSinglePlayerBuilt),
            // so the Options row applies without a restart.
            // Shared UI bindings resolve later on some launches; ask again next
            // time rather than giving up for good.
            if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_OverlayCtor || !g_BzrFn_AddChild ||
                !g_BzrFn_UiSetActive || !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover || !g_BzrFn_SetTextureOff ||
                !g_BzrFn_SetTextureOver || !g_BzrFn_SetTextureOn || !g_BzrFn_SetButtonLabel)
                return;

            g_GaveUp = true;  // every early return below is final
            const HookEngine::EngineRow rows[] = {
                { "ScrollingTextBlockCtor", &g_TextCtorAddr },
                { "ScrollingTextBlockSetText", &g_SetTextAddr },
                { "ScrollingTextBlockScrollUp", &g_ScrollUpAddr },
                { "ScrollingTextBlockScrollDown", &g_ScrollDownAddr },
            };
            if (!HookEngine::BindEngineRows("Database screen", rows))
                return;
            g_ReadFile = reinterpret_cast<FnReadFile>(
                static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("PathBlock::ReadFile")));
            HMODULE crt = GetModuleHandleW(L"MSVCR120.dll");
            g_GameNew = crt ? reinterpret_cast<FnGameNew>(GetProcAddress(crt, "??2@YAPAXI@Z")) : nullptr;
            if (!g_ReadFile || !g_GameNew || !DesReader::Bind())
            {
                Log(L"[DATABASE] file read, game allocator or page reader unresolved; Database off\n");
                return;
            }
            if (!Shell::RegisterScreen({ Shell::kDatabaseScreenId, "Database", &BuildDatabaseScreen,
                                         &OnDatabaseClosed }))
            {
                Log(L"[DATABASE] shell screens unavailable; Database off\n");
                return;
            }
            g_Active = true;
            if (!Shell::ObserveStockScreen(kSinglePlayerScreenId, &OnSinglePlayerBuilt))
            {
                // Registered but unreachable: harmless, nothing requests it.
                g_Active = false;
                Log(L"[DATABASE] shell screen factory unavailable; Database off\n");
                return;
            }
            g_GaveUp = false;
            Log(L"[DATABASE] installed (Single Player button, shell screen 0x%X)\n", Shell::kDatabaseScreenId);
        }
    }
}
