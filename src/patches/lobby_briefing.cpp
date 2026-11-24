// lobby_briefing.cpp
// BZR Open Shim - Briefing button and page overlay on the multiplayer lobby
// (cUI_Multiplayer_Create, shell screen 0xF). See Docs/LOBBY_BRIEFING.md.
//
// The overlay lives on the lobby screen itself, not on a shell screen of its
// own: the lobby screen's refresh starts the game when the host launches and
// handles a kick, and a shell transition would destroy it (and rebuild it on
// return, re-running the host's settings write). So:
//   build   a stock-screen observer (ShellScreens::ObserveStockScreen) adds,
//           inside the factory call, a Briefing button to Middle_Overlay and a
//           hidden overlay view as the screen's FIRST child, so the click walk
//           (containers in child order, 0x007D2570) reaches it before
//           Middle_Overlay and, while it is shown, its rect swallows clicks.
//   draw    UiViewSetZOrder puts the overlay above the stock widgets.
//   keys    lobby vtable slots 2 (char), 4 (KeyPressed) and 5 (KeyReleased)
//           are wrapped; they pass through unless the overlay is open.
//           Slot 13 (per-frame update) stays with the map preview fix.
//   tick    the overlay view gets its own copy of the cUI_View vtable whose
//           slot 13 runs a tick after the stock update (the lobby update calls
//           slot 13 on each child) and whose slot 0 forgets the overlay as the
//           screen frees it. The tick re-checks the selected map and greys the
//           button when it has no <stem>.des.
#include <Windows.h>
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "bzr_string.h"
#include "des_reader.h"
#include "hook_engine.h"
#include "lobby_briefing_policy.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "shell_screens.h"
#include "ui_decor.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using BZROpenShim::L10n::ShimText;
using BZROpenShim::L10n::ShimFormat;

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace Policy = LobbyBriefingPolicy;
            namespace Pages = BriefingPagesPolicy;
            namespace Shell = ShellScreens;

            constexpr uint32_t kCreateScreenId = 0xF;
            constexpr char kCreateRtti[] = ".?AVcUI_Multiplayer_Create@@";
            constexpr char kViewRtti[] = ".?AVcUI_View@@";

            // cUI_Multiplayer_Create (FUN_00796880).
            constexpr size_t kScreenMiddleOverlay = 0x150;
            constexpr size_t kScreenNetLobby = 0x1BC;
            constexpr size_t kScreenMapComponent = 0x1C8;
            // Lobby record (FUN_0056F900): the map file std::string.
            constexpr size_t kRecordMapFile = 0xDC;
            // Map component entry (MapComponentSelectedEntry): file name first.
            constexpr size_t kMapEntryFileName = 0x00;
            // cUI_View.
            constexpr size_t kUiChildBegin = 0x12C;
            constexpr size_t kUiChildEnd = 0x130;
            constexpr size_t kUiViewVtableSlots = 15;
            constexpr size_t kSlotDeletingDtor = 0;
            constexpr size_t kSlotChar = 2;
            constexpr size_t kSlotKeyPressed = 4;
            constexpr size_t kSlotKeyReleased = 5;
            constexpr size_t kSlotSetActive = 9;
            constexpr size_t kSlotUpdate = 13;
            // cUI_ScrollingTextBlock (ctor 0x007CD8D0).
            constexpr size_t kScrollingTextBlockSize = 0x295C;
            constexpr size_t kScrollDownArrow = 0x2954;
            constexpr size_t kScrollPosition = 0x2958;

            constexpr size_t kMapNameMax = 260;
            constexpr int kTextColour = 3;             // green, the stock briefing text colour
            constexpr uint32_t kVkEscape = 0x1B;
            // Render queue 0x3C + z: stock Middle_Overlay children sit at 1..6,
            // please_wait at 0xE and overlay messages at 0x10 stay on top.
            constexpr uint8_t kOverlayZ = 8;
            constexpr uint8_t kContentZ = 1;

            // 1440x1080 design space, as the stock lobby ctor uses. The overlay
            // reaches kPadX past both sides of the design area so it also
            // covers the corner buttons a wide window anchors to its edges;
            // its children are placed relative to it, hence the + kPadX.
            constexpr float kPadX = 1200.0f;
            const Shell::Rect kOverlayRect{ -kPadX, 0.0f, 1440.0f + 2.0f * kPadX, 1080.0f };
            const Shell::Rect kFrameRect{ kPadX + 80.0f, 100.0f, 1280.0f, 880.0f };
            const Shell::Rect kTitleRect{ kPadX + 100.0f, 112.0f, 1240.0f, 44.0f };
            const Shell::Rect kTextRect{ kPadX + 110.0f, 170.0f, 700.0f, 720.0f };
            const Shell::Rect kImageRect{ kPadX + 880.0f, 170.0f, 450.0f, 338.0f };
            const Shell::Rect kPrevRect{ kPadX + 110.0f, 910.0f, 180.0f, 50.0f };
            const Shell::Rect kPageRect{ kPadX + 300.0f, 915.0f, 300.0f, 40.0f };
            const Shell::Rect kNextRect{ kPadX + 610.0f, 910.0f, 180.0f, 50.0f };
            const Shell::Rect kCloseRect{ kPadX + 1150.0f, 910.0f, 180.0f, 50.0f };
            // Left-column slot below Sync Join: ctor FUN_00796880 builds the
            // stock TeamButton here (:221) and hides it at once (:228); no other
            // lobby code touches that widget, so the slot is empty on screen and
            // does not claim clicks. The right-hand column (x 760/1060) is not
            // usable: its third row is the Any Nation control, whose value text
            // runs past its own box into the neighbouring slot, and that widget
            // sits earlier in the child order, so it also took the clicks.
            const Shell::Rect kButtonRect{ 50.0f, 575.0f, 300.0f, 60.0f };
            // The lobby button wears the stock settings buttons' label cell
            // (cUI_Multiplayer_SettingButton 0x007C3E30 loads sync_join_off /
            // _over / _on for each label), so it matches Sync Join and its
            // neighbours instead of the brighter mode-button art the overlay uses.
            const Shell::ButtonSkin kLobbySkin{ "sync_join_off.png", "sync_join_over.png", "sync_join_on.png" };
            const Shell::ButtonSkin kSkin{ "MultiplayerModeButton_off.png", "MultiplayerModeButton_over.png",
                                           "MultiplayerModeButton_on.png" };

            using FnScrollingTextBlockCtor = void*(__thiscall*)(void* self, char flag, const char* name,
                                                               float x, float y, float w, float h,
                                                               void(__cdecl* onPageUp)(), void(__cdecl* onPageDown)(),
                                                               uint32_t flags, void* parent);
            using FnSetText = void(__thiscall*)(void* block, const char* text, int colourIndex);
            using FnScroll = void(__thiscall*)(void* block);
            using FnSetTextScale = void(__thiscall*)(void* block, float scale);
            using FnSetByte = void(__thiscall*)(void* widget, uint8_t value);
            using FnLobbyRecord = uint8_t*(__thiscall*)(void* netLobby);
            using FnSelectedEntry = const uint8_t*(__thiscall*)(void* component);
            using FnGameNew = void*(__cdecl*)(size_t size);
            using FnDeletingDtor = void*(__thiscall*)(void* self, unsigned flags);
            using FnUpdate = void(__thiscall*)(void* self);
            using FnKeyPressed = uint8_t(__thiscall*)(void* self, uint32_t key, uint32_t mods, uint32_t repeat);
            using FnKeyReleased = uint8_t(__thiscall*)(void* self, uint32_t key, uint32_t mods);
            using FnChar = uint8_t(__thiscall*)(void* self, uint32_t ch);

            uint32_t g_CreateVtable = 0, g_ScreenSlot = 0, g_UiViewVtable = 0;
            uint32_t g_KeyPressedAddr = 0, g_CharAddr = 0, g_KeyReleasedAddr = 0;
            uint32_t g_TextCtorAddr = 0, g_SetTextAddr = 0, g_SetTextScaleAddr = 0, g_ScrollUpAddr = 0, g_ScrollDownAddr = 0;
            uint32_t g_SetZAddr = 0, g_SetEnabledAddr = 0, g_RecordAddr = 0, g_SelectedEntryAddr = 0;
            FnGameNew g_GameNew = nullptr;

            FnDeletingDtor g_ViewDtor = nullptr;
            FnUpdate g_ViewUpdate = nullptr;
            // [0] is the RTTI locator copied from the stock table.
            uintptr_t g_OverlayVtable[1 + kUiViewVtableSlots] = {};

            bool g_Active = false;     // every hook and row in place
            bool g_GaveUp = false;
            bool g_TickFaultLogged = false;

            struct State
            {
                uint8_t* screen = nullptr;
                void* overlay = nullptr;
                void* button = nullptr;
                void* text = nullptr;
                void* image = nullptr;
                void* title = nullptr;
                void* pageLabel = nullptr;
                void* prev = nullptr;
                void* next = nullptr;
                void* close = nullptr;
                std::vector<void*> decor;
                bool open = false;
                bool swallowEscRelease = false;
                bool hiddenOnce = false;
                // Selected map, and whether it has a briefing.
                bool mapKnown = false;
                std::string mapFile;
                std::string stem;
                bool hasBriefing = false;
                // Loaded pages while open.
                std::string shownStem;
                std::vector<std::string> pages;
                std::vector<std::string> images;
                int page = 1;
                std::string loadedImage;
            };
            State g_State;

            // ---- SEH helpers (POD only) ----

            bool ScreenIsLive()
            {
                if (!g_State.screen || !g_ScreenSlot)
                    return false;
                __try
                {
                    return *reinterpret_cast<uint8_t* volatile*>(static_cast<uintptr_t>(g_ScreenSlot)) == g_State.screen;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
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

            void CopyBzrString(const uint8_t* source, char* out, size_t outSize)
            {
                const BzrString* s = reinterpret_cast<const BzrString*>(source);
                const char* data = BzrStringData(s);
                size_t length = s->size;
                if (length >= outSize)
                    length = outSize - 1;
                std::memcpy(out, data, length);
                out[length] = '\0';
            }

            // The map the lobby shows: the map list's selected entry (the
            // host's pick, or the record's map the refresh selected on a
            // client), else the lobby record's map file (record+0xDC).
            bool ReadMapFileSeh(uint8_t* screen, char* out, size_t outSize)
            {
                out[0] = '\0';
                __try
                {
                    void* component = *reinterpret_cast<void**>(screen + kScreenMapComponent);
                    if (component)
                    {
                        const uint8_t* entry =
                            reinterpret_cast<FnSelectedEntry>(static_cast<uintptr_t>(g_SelectedEntryAddr))(component);
                        if (entry)
                            CopyBzrString(entry + kMapEntryFileName, out, outSize);
                    }
                    if (!out[0])
                    {
                        void* lobby = *reinterpret_cast<void**>(screen + kScreenNetLobby);
                        uint8_t* record = lobby
                            ? reinterpret_cast<FnLobbyRecord>(static_cast<uintptr_t>(g_RecordAddr))(lobby)
                            : nullptr;
                        if (record)
                            CopyBzrString(record + kRecordMapFile, out, outSize);
                    }
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out[0] = '\0';
                    return false;
                }
            }

            // cUI_Button overrides SetActive (slot 9, 0x007C27F0) to hide its
            // caption as well; the cUI_View one (0x007D3310) does not.
            void VirtualSetActive(void* widget, bool shown)
            {
                if (!widget)
                    return;
                __try
                {
                    const uintptr_t* vtable = *reinterpret_cast<uintptr_t* const*>(widget);
                    reinterpret_cast<FnSetByte>(vtable[kSlotSetActive])(widget, shown ? 1 : 0);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            void ViewSetActive(void* widget, bool shown)
            {
                if (widget && g_BzrFn_UiSetActive)
                    g_BzrFn_UiSetActive(widget, shown ? 1 : 0);
            }

            bool ViewInputActive(void* widget)
            {
                if (!widget)
                    return false;
                __try
                {
                    return static_cast<const uint8_t*>(widget)[kUiViewInputActiveOffset] != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void SetZ(void* widget, uint8_t z)
            {
                if (widget)
                    reinterpret_cast<FnSetByte>(static_cast<uintptr_t>(g_SetZAddr))(widget, z);
            }

            // ---- resources ----

            // Page reads go through the shared reader (des_reader.cpp).
            bool ResourceExists(const std::string& name)
            {
                return DesReader::ResourceExists(name);
            }

            bool ImageExists(const std::string& name)
            {
                return DesReader::ImageExists(name);
            }

            std::string LoadDes(const std::string& file)
            {
                return DesReader::LoadPage(file);
            }

            // ---- overlay state ----

            void SetText(const std::string& text)
            {
                if (g_State.text)
                    reinterpret_cast<FnSetText>(static_cast<uintptr_t>(g_SetTextAddr))(
                        g_State.text, text.c_str(), kTextColour);
            }

            void SetLabel(void* label, const char* text)
            {
                if (label)
                    Shell::SetLabelText(label, text);
            }

            void HideOverlay()
            {
                State& s = g_State;
                SetText("");
                SetLabel(s.title, "");
                SetLabel(s.pageLabel, "");
                VirtualSetActive(s.prev, false);
                VirtualSetActive(s.next, false);
                VirtualSetActive(s.close, false);
                ViewSetActive(s.image, false);
                ViewSetActive(s.title, false);
                ViewSetActive(s.pageLabel, false);
                ViewSetActive(s.text, false);
                for (void* piece : s.decor)
                    ViewSetActive(piece, false);
                ViewSetActive(s.overlay, false);
            }

            void ShowPage(int requested)
            {
                State& s = g_State;
                const int count = static_cast<int>(s.pages.size());
                const int page = Pages::ClampPage(requested, count);
                s.page = page;
                SetText(s.pages[static_cast<size_t>(page - 1)]);
                const std::string& image = s.images[static_cast<size_t>(page - 1)];
                if (!image.empty() && s.image && g_BzrFn_SetTextureOff)
                {
                    if (s.loadedImage != image)
                    {
                        g_BzrFn_SetTextureOff(s.image, image.c_str());
                        s.loadedImage = image;
                    }
                    ViewSetActive(s.image, true);
                }
                else
                {
                    ViewSetActive(s.image, false);
                }
                VirtualSetActive(s.prev, page > 1);
                VirtualSetActive(s.next, page < count);
                const std::string pageText = ShimFormat("openshim_ui:lobbybrief_page", "Page %s",
                    std::to_string(page) + "/" + std::to_string(count));
                SetLabel(s.pageLabel, count > 1 ? pageText.c_str() : "");
            }

            bool LoadPages(const std::string& stem)
            {
                State& s = g_State;
                const int count = Policy::CountPages(stem, ResourceExists);
                s.pages.clear();
                s.images.clear();
                if (count < 1)
                    return false;
                for (int page = 1; page <= count; ++page)
                {
                    s.pages.push_back(LoadDes(Policy::PageTextFileName(stem, page)));
                    const std::string image = Policy::PageImageFileName(stem, page);
                    s.images.push_back(ImageExists(image) ? image : std::string());
                }
                s.shownStem = stem;
                return true;
            }

            void CloseOverlay(const wchar_t* why)
            {
                State& s = g_State;
                if (!s.open)
                    return;
                s.open = false;
                HideOverlay();
                Log(L"[LOBBYBRIEF] closed (%ls)\n", why);
            }

            void OpenOverlay()
            {
                State& s = g_State;
                if (!g_Active || !ScreenIsLive() || s.open || !s.overlay || !s.hasBriefing)
                    return;
                if (!LoadPages(s.stem))
                {
                    Log(L"[LOBBYBRIEF] %hs: no pages to show\n", s.stem.c_str());
                    return;
                }
                s.open = true;
                s.swallowEscRelease = false;
                ViewSetActive(s.overlay, true);
                for (void* piece : s.decor)
                    ViewSetActive(piece, true);
                ViewSetActive(s.text, true);
                ViewSetActive(s.title, true);
                ViewSetActive(s.pageLabel, true);
                SetLabel(s.title, s.stem.c_str());
                VirtualSetActive(s.close, true);
                ShowPage(1);
                Log(L"[LOBBYBRIEF] opened %hs (%d pages)\n", s.stem.c_str(), static_cast<int>(s.pages.size()));
            }

            void StepPage(int step)
            {
                if (g_State.open && ScreenIsLive())
                    ShowPage(g_State.page + step);
            }

            void ScrollUp()
            {
                State& s = g_State;
                if (!s.open || !s.text || !ScreenIsLive())
                    return;
                __try
                {
                    // The stock scroll does not clamp; the up arrow only shows above 0.
                    if (*reinterpret_cast<int*>(static_cast<uint8_t*>(s.text) + kScrollPosition) > 0)
                        reinterpret_cast<FnScroll>(static_cast<uintptr_t>(g_ScrollUpAddr))(s.text);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            void ScrollDown()
            {
                State& s = g_State;
                if (!s.open || !s.text || !ScreenIsLive())
                    return;
                void* arrow = nullptr;
                // The down arrow is shown only while there is more text below.
                if (ReadPointerSeh(s.text, kScrollDownArrow, arrow) && ViewInputActive(arrow))
                    reinterpret_cast<FnScroll>(static_cast<uintptr_t>(g_ScrollDownAddr))(s.text);
            }

            void __cdecl OnBriefingClicked() { OpenOverlay(); }
            void __cdecl OnCloseClicked()
            {
                if (ScreenIsLive())
                    CloseOverlay(L"Close button");
            }
            void __cdecl OnPrevClicked() { StepPage(-1); }
            void __cdecl OnNextClicked() { StepPage(1); }
            void __cdecl OnScrollUpClicked() { ScrollUp(); }
            void __cdecl OnScrollDownClicked() { ScrollDown(); }

            void SetButtonEnabled(bool enabled)
            {
                State& s = g_State;
                if (!s.button)
                    return;
                reinterpret_cast<FnSetByte>(static_cast<uintptr_t>(g_SetEnabledAddr))(s.button, enabled ? 1 : 0);
                if (g_BzrFn_SetButtonLabel)
                    g_BzrFn_SetButtonLabel(s.button, enabled
                        ? ShimText("openshim_ui:lobbybrief_button", "Briefing")
                        : ShimText("openshim_ui:lobbybrief_none", "No Briefing"));
            }

            // ---- per-frame tick (overlay view slot 13) ----

            void Tick()
            {
                State& s = g_State;
                if (!g_Active || !ScreenIsLive())
                    return;

                // The overlay was hidden at build; if anything shows it again
                // while closed, hide it once more so it cannot swallow clicks.
                if (!s.open && ViewInputActive(s.overlay))
                {
                    HideOverlay();
                    if (!s.hiddenOnce)
                    {
                        s.hiddenOnce = true;
                        Log(L"[LOBBYBRIEF] overlay was re-shown while closed; hidden again\n");
                    }
                }

                char map[kMapNameMax] = {};
                ReadMapFileSeh(s.screen, map, sizeof(map));
                if (s.mapKnown && s.mapFile == map)
                    return;
                s.mapKnown = true;
                s.mapFile = map;
                s.stem = Policy::MissionStemFromMapFile(s.mapFile);
                s.hasBriefing = Policy::HasBriefing(s.stem, ResourceExists);
                SetButtonEnabled(s.hasBriefing);
                Log(L"[LOBBYBRIEF] map '%hs': %ls\n", map,
                    s.hasBriefing ? L"briefing available" : (map[0] ? L"no .des, button greyed" : L"no map yet, button greyed"));

                if (s.open && (s.stem != s.shownStem || !s.hasBriefing))
                {
                    if (!s.hasBriefing || !LoadPages(s.stem))
                    {
                        CloseOverlay(L"map changed to one without a briefing");
                    }
                    else
                    {
                        SetLabel(s.title, s.stem.c_str());
                        s.loadedImage.clear();
                        ShowPage(1);
                        Log(L"[LOBBYBRIEF] map changed while open; showing %hs\n", s.stem.c_str());
                    }
                }
            }

            bool TickGuarded(DWORD& code)
            {
                code = 0;
                __try
                {
                    Tick();
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    code = GetExceptionCode();
                    return false;
                }
            }

            void __fastcall OverlayUpdate(void* self, void* /*edx*/)
            {
                g_ViewUpdate(self);
                if (self != g_State.overlay)
                    return;
                DWORD code = 0;
                if (!TickGuarded(code) && !g_TickFaultLogged)
                {
                    g_TickFaultLogged = true;
                    Log(L"[LOBBYBRIEF] tick faulted (0x%08X)\n", code);
                }
            }

            void* __fastcall OverlayDeletingDtor(void* self, void* /*edx*/, unsigned flags)
            {
                // The screen frees its children as it closes; every widget
                // pointer kept here goes with it.
                if (self == g_State.overlay)
                    g_State = State();
                return g_ViewDtor(self, flags);
            }

            // ---- lobby vtable slots 2, 4, 5 ----

            FnChar g_OrigChar = nullptr;
            FnKeyPressed g_OrigKeyPressed = nullptr;
            FnKeyReleased g_OrigKeyReleased = nullptr;

            bool OpenOn(void* screen)
            {
                return g_State.open && screen == g_State.screen && ScreenIsLive();
            }

            uint8_t __fastcall CharHook(void* self, void* /*edx*/, uint32_t ch)
            {
                // While the overlay is open, typing must not reach the chat entry.
                if (OpenOn(self))
                    return 1;
                return g_OrigChar(self, ch);
            }

            uint8_t __fastcall KeyPressedHook(void* self, void* /*edx*/, uint32_t key, uint32_t mods, uint32_t repeat)
            {
                if (!OpenOn(self))
                {
                    if (key == kVkEscape && self == g_State.screen)
                    {
                        // A held Esc that closed the overlay keeps repeating;
                        // those repeats are ours too. A fresh press means the
                        // release was lost, so the next release is the lobby's.
                        if (repeat && g_State.swallowEscRelease)
                            return 1;
                        g_State.swallowEscRelease = false;
                    }
                    return g_OrigKeyPressed(self, key, mods, repeat);
                }
                switch (Policy::ActionForKey(key))
                {
                case Policy::KeyAction::Close:
                    CloseOverlay(L"Esc");
                    g_State.swallowEscRelease = true;
                    break;
                case Policy::KeyAction::Prev:
                    StepPage(-1);
                    break;
                case Policy::KeyAction::Next:
                    StepPage(1);
                    break;
                case Policy::KeyAction::ScrollUp:
                    ScrollUp();
                    break;
                case Policy::KeyAction::ScrollDown:
                    ScrollDown();
                    break;
                default:
                    break;
                }
                // Every key stops here while open (chat, map list, Enter).
                return 1;
            }

            uint8_t __fastcall KeyReleasedHook(void* self, void* /*edx*/, uint32_t key, uint32_t mods)
            {
                if (OpenOn(self))
                {
                    if (key == kVkEscape)
                        CloseOverlay(L"Esc");
                    return 1;
                }
                // The release of the Esc that closed the overlay is ours too.
                if (key == kVkEscape && g_State.swallowEscRelease && self == g_State.screen)
                {
                    g_State.swallowEscRelease = false;
                    return 1;
                }
                return g_OrigKeyReleased(self, key, mods);
            }

            // ---- build (stock screen observer, inside the factory call) ----

            void* AddDecor(void* overlay, const char* name, const Shell::Rect& r, const char* texture)
            {
                void* piece = Shell::AddPanel(overlay, overlay, name, r, texture, Shell::kControlFlags);
                if (piece)
                    g_State.decor.push_back(piece);
                return piece;
            }

            void BuildFrame(void* overlay)
            {
                if (!Shell::IsTextureDeployed("uiplate.png"))
                    return;
                AddDecor(overlay, "OpenShimLobbyBrief_Plate", kFrameRect, "uiplate.png");
                if (!Shell::IsTextureDeployed("uiline.png"))
                    return;
                UiDecorPanelDesc desc;
                desc.rect = { kFrameRect.x, kFrameRect.y, kFrameRect.w, kFrameRect.h };
                UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
                const size_t count = BuildUiDecorPanel(desc, pieces, kUiDecorMaxPanelPieces);
                char name[48] = {};
                for (size_t i = 0; i < count; ++i)
                {
                    std::snprintf(name, sizeof(name), "OpenShimLobbyBrief_Border%u", static_cast<unsigned>(i));
                    AddDecor(overlay, name, { pieces[i].rect.x, pieces[i].rect.y, pieces[i].rect.width,
                                              pieces[i].rect.height }, pieces[i].texture);
                }
            }

            void* MakeTextBlock(void* overlay)
            {
                void* memory = g_GameNew(kScrollingTextBlockSize);
                if (!memory)
                    return nullptr;
                std::memset(memory, 0, kScrollingTextBlockSize);
                void* block = reinterpret_cast<FnScrollingTextBlockCtor>(static_cast<uintptr_t>(g_TextCtorAddr))(
                    memory, 0, "OpenShimLobbyBrief_Text", kTextRect.x, kTextRect.y, kTextRect.w, kTextRect.h,
                    &OnScrollUpClicked, &OnScrollDownClicked, Shell::kControlFlags, overlay);
                if (block)
                {
                    // The block starts at text scale 0.75; the reflow and the stride probe
                    // both apply it, so pages skip lines (Docs/DATABASE_SCREEN.md, "Briefing
                    // scrolling"). 1.0 makes them agree.
                    reinterpret_cast<FnSetTextScale>(static_cast<uintptr_t>(g_SetTextScaleAddr))(block, 1.0f);
                    g_BzrFn_AddChild(overlay, block, 0);
                }
                return block;
            }

            // Overlay view first in the screen's child list (AddChild's third
            // argument inserts before that child, FUN_007D2110).
            void* MakeOverlay(uint8_t* screen, void* middle)
            {
                void* first = nullptr;
                void* begin = nullptr;
                void* end = nullptr;
                if (ReadPointerSeh(screen, kUiChildBegin, begin) && ReadPointerSeh(screen, kUiChildEnd, end) &&
                    begin && begin != end)
                    ReadPointerSeh(begin, 0, first);

                void* memory = g_GameNew(kUiViewSize);
                if (!memory)
                    return nullptr;
                std::memset(memory, 0, kUiViewSize);
                void* overlay = g_BzrFn_OverlayCtor(memory, "OpenShimLobbyBrief", kOverlayRect.x, kOverlayRect.y,
                                                    kOverlayRect.w, kOverlayRect.h, Shell::kControlFlags, middle, 0);
                if (!overlay)
                    return nullptr;
                if (*reinterpret_cast<uintptr_t*>(overlay) != g_UiViewVtable)
                {
                    Log(L"[LOBBYBRIEF] overlay view has an unexpected class; not built\n");
                    // Unknown class means an unknown dtor layout: leak this
                    // one view on a should-never-happen path rather than run
                    // the cUI_View dtor on an object that may not be one.
                    return nullptr;
                }
                g_BzrFn_SetTextureOff(overlay, "blackui.png");
                g_BzrFn_AddChild(screen, overlay, static_cast<int>(reinterpret_cast<intptr_t>(first)));
                *reinterpret_cast<uintptr_t*>(overlay) = reinterpret_cast<uintptr_t>(&g_OverlayVtable[1]);
                return overlay;
            }

            void BuildOnScreen(uint8_t* screen)
            {
                void* middle = nullptr;
                if (!ReadPointerSeh(screen, kScreenMiddleOverlay, middle) || !middle)
                {
                    Log(L"[LOBBYBRIEF] lobby screen has no Middle_Overlay; not built\n");
                    return;
                }

                State s;
                s.screen = screen;
                g_State = s;
                g_State.button = Shell::AddButton(middle, middle, "OpenShimLobbyBrief_Button", kButtonRect,
                    ShimText("openshim_ui:lobbybrief_button", "Briefing"), kLobbySkin, 1.0f, 0.0f, &OnBriefingClicked);
                if (!g_State.button)
                {
                    g_State = State();
                    Log(L"[LOBBYBRIEF] Briefing button not built\n");
                    return;
                }
                void* overlay = MakeOverlay(screen, middle);
                if (!overlay)
                {
                    VirtualSetActive(g_State.button, false);
                    g_State = State();
                    Log(L"[LOBBYBRIEF] overlay not built; Briefing button hidden\n");
                    return;
                }
                g_State.overlay = overlay;
                BuildFrame(overlay);
                g_State.title = Shell::AddLabel(overlay, overlay, "OpenShimLobbyBrief_Title", kTitleRect, "",
                                                Shell::kTitleLabelFlags);
                g_State.text = MakeTextBlock(overlay);
                g_State.image = Shell::AddPanel(overlay, overlay, "OpenShimLobbyBrief_Image", kImageRect, nullptr,
                                                Shell::kControlFlags);
                g_State.pageLabel = Shell::AddLabel(overlay, overlay, "OpenShimLobbyBrief_Page", kPageRect, "");
                g_State.prev = Shell::AddButton(overlay, overlay, "OpenShimLobbyBrief_Prev", kPrevRect,
                    ShimText("openshim_ui:lobbybrief_prev", "Prev"), kSkin, 1.0f, 0.0f, &OnPrevClicked);
                g_State.next = Shell::AddButton(overlay, overlay, "OpenShimLobbyBrief_Next", kNextRect,
                    ShimText("openshim_ui:lobbybrief_next", "Next"), kSkin, 1.0f, 0.0f, &OnNextClicked);
                g_State.close = Shell::AddButton(overlay, overlay, "OpenShimLobbyBrief_Close", kCloseRect,
                    ShimText("openshim_ui:lobbybrief_close", "Close"), kSkin, 1.0f, 0.0f, &OnCloseClicked);

                if (!g_State.text || !g_State.close)
                {
                    // What was built belongs to the screen; keep it hidden and inert.
                    HideOverlay();
                    VirtualSetActive(g_State.button, false);
                    void* keepOverlay = g_State.overlay;
                    g_State = State();
                    g_State.overlay = keepOverlay; // the dtor hook still matches it
                    Log(L"[LOBBYBRIEF] overlay widgets not built; Briefing button hidden\n");
                    return;
                }

                const void* content[] = { g_State.title, g_State.text, g_State.image, g_State.pageLabel,
                                          g_State.prev, g_State.next, g_State.close };
                for (void* piece : g_State.decor)
                    SetZ(piece, kContentZ);
                for (const void* widget : content)
                    SetZ(const_cast<void*>(widget), kContentZ);
                SetZ(overlay, kOverlayZ); // re-applies every child's z on top

                HideOverlay();
                SetButtonEnabled(false);
                Tick();
                Log(L"[LOBBYBRIEF] Briefing button and overlay built\n");
            }

            bool ShouldEnable();

            void OnCreateScreenBuilt(void* screen)
            {
                if (!g_Active || !screen || !ShouldEnable())
                    return;
                if (*static_cast<uintptr_t*>(screen) != g_CreateVtable)
                {
                    Log(L"[LOBBYBRIEF] stock screen 0xF is not cUI_Multiplayer_Create; not built\n");
                    return;
                }
                BuildOnScreen(static_cast<uint8_t*>(screen));
            }

            bool ShouldEnable()
            {
                // The env kill switch wins; otherwise [Features] LobbyBriefing
                // (default on), read each time a lobby is built.
                if (EnvFlagEnabled("OPENSHIM_DISABLE_LOBBY_BRIEFING"))
                    return false;
                bool enabled = true;
                return !TryGetUserConfigBool("Features", "LobbyBriefing", enabled) || enabled;
            }

            bool SlotHolds(uintptr_t slot, uint32_t expected)
            {
                __try
                {
                    return *reinterpret_cast<const uint32_t*>(slot) == expected;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }
        }

        void InstallLobbyBriefingIfPossible()
        {
            if (g_Active || g_GaveUp)
                return;
            if (EnvFlagEnabled("OPENSHIM_DISABLE_LOBBY_BRIEFING"))
            {
                g_GaveUp = true;
                Log(L"[LOBBYBRIEF] disabled by OPENSHIM_DISABLE_LOBBY_BRIEFING\n");
                return;
            }
            // Shared UI bindings resolve later on some launches; ask again next
            // time rather than letting the shell-screen binder give up for good.
            if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_OverlayCtor || !g_BzrFn_AddChild ||
                !g_BzrFn_UiSetActive || !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover || !g_BzrFn_SetTextureOff ||
                !g_BzrFn_SetTextureOver || !g_BzrFn_SetTextureOn || !g_BzrFn_SetButtonLabel)
                return;

            g_GaveUp = true; // every early return below is final
            const HookEngine::EngineRow rows[] = {
                { "MultiplayerCreateVtable", &g_CreateVtable },
                { "MultiCreateScreenSlot", &g_ScreenSlot },
                { "UiViewVtable", &g_UiViewVtable },
                { "MultiCreateKeyPressed", &g_KeyPressedAddr },
                { "MultiCreateChar", &g_CharAddr },
                { "UiViewKeyReleased", &g_KeyReleasedAddr },
                { "ScrollingTextBlockCtor", &g_TextCtorAddr },
                { "ScrollingTextBlockSetText", &g_SetTextAddr },
                { "ScrollingTextBlockSetTextScale", &g_SetTextScaleAddr },
                { "ScrollingTextBlockScrollUp", &g_ScrollUpAddr },
                { "ScrollingTextBlockScrollDown", &g_ScrollDownAddr },
                { "UiViewSetZOrder", &g_SetZAddr },
                { "UiButtonSetEnabled", &g_SetEnabledAddr },
                { "AnyNationLobbyRecord", &g_RecordAddr },
                { "MapComponentSelectedEntry", &g_SelectedEntryAddr },
            };
            if (!HookEngine::BindEngineRows("Lobby briefing", rows))
                return;
            if (!VtableTypeNameMatches(g_CreateVtable, kCreateRtti) || !VtableTypeNameMatches(g_UiViewVtable, kViewRtti))
            {
                Log(L"[LOBBYBRIEF] vtable RTTI mismatch; lobby briefing off\n");
                return;
            }
            HMODULE crt = GetModuleHandleW(L"MSVCR120.dll");
            g_GameNew = crt ? reinterpret_cast<FnGameNew>(GetProcAddress(crt, "??2@YAPAXI@Z")) : nullptr;
            // The page reader binds DescriptionFileLoad, Music::ResourceSize
            // and the Ogre image lookup (des_reader.cpp).
            if (!DesReader::Bind() || !g_GameNew)
            {
                Log(L"[LOBBYBRIEF] page reader or game allocator unresolved; lobby briefing off\n");
                return;
            }

            // The overlay view's own vtable: cUI_View's with the dtor and the
            // per-frame update replaced.
            const uintptr_t* stock = reinterpret_cast<const uintptr_t*>(static_cast<uintptr_t>(g_UiViewVtable));
            g_OverlayVtable[0] = stock[-1];
            std::memcpy(&g_OverlayVtable[1], stock, sizeof(uintptr_t) * kUiViewVtableSlots);
            g_ViewDtor = reinterpret_cast<FnDeletingDtor>(stock[kSlotDeletingDtor]);
            g_ViewUpdate = reinterpret_cast<FnUpdate>(stock[kSlotUpdate]);
            g_OverlayVtable[1 + kSlotDeletingDtor] = reinterpret_cast<uintptr_t>(&OverlayDeletingDtor);
            g_OverlayVtable[1 + kSlotUpdate] = reinterpret_cast<uintptr_t>(&OverlayUpdate);

            // All three lobby slots must still hold the stock handlers before
            // any is written.
            const uintptr_t charSlot = g_CreateVtable + kSlotChar * sizeof(void*);
            const uintptr_t pressedSlot = g_CreateVtable + kSlotKeyPressed * sizeof(void*);
            const uintptr_t releasedSlot = g_CreateVtable + kSlotKeyReleased * sizeof(void*);
            if (!SlotHolds(charSlot, g_CharAddr) || !SlotHolds(pressedSlot, g_KeyPressedAddr) ||
                !SlotHolds(releasedSlot, g_KeyReleasedAddr))
            {
                Log(L"[LOBBYBRIEF] lobby vtable slots 2/4/5 are not stock; lobby briefing off\n");
                return;
            }
            if (!Shell::ObserveStockScreen(kCreateScreenId, &OnCreateScreenBuilt))
            {
                Log(L"[LOBBYBRIEF] shell screen factory unavailable; lobby briefing off\n");
                return;
            }
            g_OrigChar = reinterpret_cast<FnChar>(static_cast<uintptr_t>(g_CharAddr));
            g_OrigKeyPressed = reinterpret_cast<FnKeyPressed>(static_cast<uintptr_t>(g_KeyPressedAddr));
            g_OrigKeyReleased = reinterpret_cast<FnKeyReleased>(static_cast<uintptr_t>(g_KeyReleasedAddr));
            if (!WritePointerValue(charSlot, reinterpret_cast<void*>(&CharHook)) ||
                !WritePointerValue(pressedSlot, reinterpret_cast<void*>(&KeyPressedHook)) ||
                !WritePointerValue(releasedSlot, reinterpret_cast<void*>(&KeyReleasedHook)))
            {
                // The hooks pass through while the overlay is closed, and it
                // never opens without g_Active, so a partial write is inert.
                Log(L"[LOBBYBRIEF] could not write the lobby vtable slots; lobby briefing off\n");
                return;
            }
            g_Active = true;
            g_GaveUp = false;
            Log(L"[LOBBYBRIEF] installed (lobby vtable slots 2/4/5, stock screen 0xF observer)\n");
        }
    }
}
