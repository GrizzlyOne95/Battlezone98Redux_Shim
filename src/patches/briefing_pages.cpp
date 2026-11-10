// briefing_pages.cpp
// BZR Open Shim - multi-page mission briefings on the pre-launch briefing
// screen (cUI_Mission). Page 1 is the stock screen; pages 2..9 come from
// <mission>_N.des and optional sidebar/media/wav files next to it. See
// Docs/BRIEFING_PAGES.md and reverse_engineering/briefing_pages_20261110.md.
//
// Four entry detours, all pass-through until every one of them is in:
//   cUI_Mission ctor        -- brackets the build so page 1 can be captured
//   description loader      -- during the ctor: page-1 mission and planet text
//   cUI_Mission play-wav    -- during the ctor: page-1 wav name
//   cUI_Mission OnKey       -- arrow / PgUp / PgDn page keys
// After the ctor returns, the extra pages are loaded and two arrow buttons
// plus two media views are added to the screen's Middle_Overlay. Widgets are
// allocated with the game's operator new and owned by the overlay, like the
// stock ones; the shim keeps only text copies and raw pointers that are used
// while the briefing singleton still names this screen.
#include <Windows.h>
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "briefing_pages_policy.h"
#include "hook_engine.h"
#include "patcher.h"
#include <cstring>
#include <set>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool g_BriefingPagesEnabled = true;
        bool g_BriefingPagesInstalled = false;

        namespace
        {
            namespace Policy = BriefingPagesPolicy;

            // std::string passed by value to the ctor (MSVC 2013, 24 bytes).
            // The original destroys it; the shim only forwards the bytes.
            struct StdStringBytes
            {
                uint8_t bytes[24];
            };

            using FnCtor = void*(__thiscall*)(void* self, int manager, StdStringBytes name);
            using FnDesLoad = uintptr_t(__cdecl*)(const char* name, char* buffer);
            using FnPlayWav = void(__thiscall*)(void* self, const char* wav);
            using FnStopWav = void(__thiscall*)(void* self);
            using FnOnKey = bool(__thiscall*)(void* self, uint32_t key, uint32_t mods);
            using FnSetText = void(__thiscall*)(void* block, const char* text, int colourIndex);
            using FnSetColour = void(__thiscall*)(void* block, uint32_t rgb);
            using FnLoadMovie = void(__thiscall*)(void* view, const char* ogv, const char* audio);
            using FnPlayMovie = void(__thiscall*)(void* view, bool play);
            using FnResourceSize = size_t(__cdecl*)(const char* name);
            using FnGameNew = void*(__cdecl*)(size_t size);

            // Layout read from this build's code (see the RE note).
            constexpr size_t kDesBufferSize = 0x1F401;      // loader caps at 0x1F400 + NUL
            constexpr size_t kDesNameBufferSize = 256;      // loader reads up to 0xF6 bytes
            constexpr size_t kScreenMissionBlockOffset = 0x15C;
            constexpr size_t kTextBlockRgbOffset = 0x100;
            constexpr size_t kTextBlockStoredTextOffset = 0x144;
            constexpr size_t kSetTextVtableOffset = 0x3C;
            constexpr size_t kUiChildBeginOffset = 0x12C;
            constexpr size_t kUiChildEndOffset = 0x130;
            constexpr size_t kUiNameOffset = 0x20;
            constexpr size_t kUiNameMax = 0xC8;
            // Stock movie panel rect (cUI_Mission ctor) and arrow size
            // (cUI_ScrollingTextBlock pageUp/pageDn).
            constexpr float kMovieX = 100.0f, kMovieY = 95.0f, kMovieW = 700.0f, kMovieH = 515.0f;
            constexpr float kArrowW = 30.0f, kArrowH = 35.0f;
            constexpr float kArrowX = kMovieX + kMovieW + 5.0f;
            constexpr float kPrevY = kMovieY + kMovieH - 70.0f;
            constexpr float kNextY = kMovieY + kMovieH - 35.0f;
            constexpr uint32_t kWidgetFlags = 0x20;

            uint32_t g_CtorAddr = 0, g_OnKeyAddr = 0, g_PlayWavAddr = 0, g_StopWavAddr = 0;
            uint32_t g_DesLoadAddr = 0, g_SetColourAddr = 0, g_LoadMovieAddr = 0;
            uint32_t g_PlayMovieAddr = 0, g_SingletonAddr = 0;
            uint32_t g_MissionSetTextAddr = 0, g_PlanetSetTextAddr = 0;

            InlineDetour32 g_CtorDetour, g_DesLoadDetour, g_PlayWavDetour, g_OnKeyDetour;
            FnResourceSize g_ResourceSize = nullptr;
            FnGameNew g_GameNew = nullptr;
            void*(__cdecl* g_OgreGroupManager)() = nullptr;
            bool(__thiscall* g_OgreResourceExists)(void*, const std::string&) = nullptr;

            // Set only once every detour is in; until then they all pass through.
            bool g_Active = false;

            // ---- capture while the stock ctor runs ----
            void* g_Capturing = nullptr;
            int g_DesCalls = 0;
            std::string g_CapBase, g_CapMissionText, g_CapPlanetText, g_CapWav;

            struct Page
            {
                std::string text;
                std::string sidebar; // empty: page 1's
                std::string media;
                Policy::MediaKind kind = Policy::MediaKind::Inherit;
                std::string wav;
            };

            struct State
            {
                void* screen = nullptr;
                void* overlay = nullptr;
                void* missionBlock = nullptr;
                void* planetBlock = nullptr;
                void* stockMovie = nullptr;
                void* imageView = nullptr;
                void* videoView = nullptr;
                void* prev = nullptr;
                void* next = nullptr;
                int missionColour = 0, planetColour = 0;
                uint32_t missionRgb = 0, planetRgb = 0;
                bool missionRgbValid = false, planetRgbValid = false;
                std::string page1Text, page1Sidebar, page1Wav;
                std::vector<Page> pages; // pages[0] is page 2
                int count = 1;
                int current = 1;
                int shownSidebarPage = 1; // whose sidebar text is on screen
                std::string loadedImage, loadedVideo;
            };
            State g_State;

            std::set<std::string> g_LoggedBases;
            bool g_OgreMissingLogged = false;

            void LogOncePerBase(const std::string& base, const wchar_t* why)
            {
                if (g_LoggedBases.size() > 256 || !g_LoggedBases.insert(base).second)
                    return;
                Log(L"[BRIEFPAGES] %hs: %ls\n", base.c_str(), why);
            }

            bool ScreenIsLive()
            {
                if (!g_State.screen || !g_SingletonAddr)
                    return false;
                __try
                {
                    return *reinterpret_cast<void* volatile*>(static_cast<uintptr_t>(g_SingletonAddr)) == g_State.screen;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool NameEquals(void* widget, const char* name)
            {
                __try
                {
                    const char* stored = reinterpret_cast<const char*>(widget) + kUiNameOffset;
                    return strncmp(stored, name, kUiNameMax) == 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void* ReadPointer(void* object, size_t offset)
            {
                __try
                {
                    return *reinterpret_cast<void**>(static_cast<uint8_t*>(object) + offset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool ReadChildren(void* parent, void**& begin, void**& end)
            {
                __try
                {
                    auto* bytes = static_cast<uint8_t*>(parent);
                    begin = *reinterpret_cast<void***>(bytes + kUiChildBeginOffset);
                    end = *reinterpret_cast<void***>(bytes + kUiChildEndOffset);
                    return begin && end && begin <= end && (end - begin) <= 1024;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void* FindChild(void* parent, const char* name)
            {
                void** begin = nullptr;
                void** end = nullptr;
                if (!parent || !ReadChildren(parent, begin, end))
                    return nullptr;
                for (void** it = begin; it != end; ++it)
                {
                    void* child = nullptr;
                    __try
                    {
                        child = *it;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        return nullptr;
                    }
                    if (child && NameEquals(child, name))
                        return child;
                }
                return nullptr;
            }

            // True when the object's SetText slot is the function the row bound,
            // which confirms both the object's class and the call target.
            bool SetTextSlotIs(void* block, uint32_t expected)
            {
                __try
                {
                    const uintptr_t vtable = *reinterpret_cast<uintptr_t*>(block);
                    return *reinterpret_cast<uint32_t*>(vtable + kSetTextVtableOffset) == expected;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // The colour index the stock ctor passed (kept as "%<n>" ahead of
            // the text) and the RGB it may have overridden afterwards.
            void ReadBlockColour(void* block, int& colour, uint32_t& rgb, bool& rgbValid)
            {
                colour = 0;
                rgbValid = false;
                __try
                {
                    auto* bytes = static_cast<uint8_t*>(block);
                    char prefix[3] = {};
                    std::memcpy(prefix, bytes + kTextBlockStoredTextOffset, 2);
                    Policy::ParseColourPrefix(prefix, colour);
                    rgb = *reinterpret_cast<uint32_t*>(bytes + kTextBlockRgbOffset) & 0x00FFFFFFu;
                    rgbValid = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            bool ResourceExists(const std::string& name)
            {
                return name.size() <= Policy::kMaxNameLength && g_ResourceSize(name.c_str()) > 0;
            }

            bool OgreExistsSeh(void* manager, const std::string& name, bool& exists)
            {
                __try
                {
                    exists = g_OgreResourceExists(manager, name);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return true;
            }

            void* OgreManagerSeh()
            {
                __try
                {
                    return g_OgreGroupManager();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            // Media is loaded through Ogre's resource groups, so look it up there.
            bool MediaExists(const std::string& name)
            {
                if (!g_OgreGroupManager || !g_OgreResourceExists)
                {
                    if (!g_OgreMissingLogged)
                    {
                        g_OgreMissingLogged = true;
                        Log(L"[BRIEFPAGES] Ogre resource lookup unavailable; page media ignored\n");
                    }
                    return false;
                }
                void* manager = OgreManagerSeh();
                bool exists = false;
                return manager && OgreExistsSeh(manager, name, exists) && exists;
            }

            bool LoadDes(const std::string& file, std::string& out)
            {
                char name[kDesNameBufferSize] = {};
                if (file.size() >= sizeof(name))
                    return false;
                std::memcpy(name, file.c_str(), file.size());
                std::vector<char> buffer(kDesBufferSize, '\0');
                reinterpret_cast<FnDesLoad>(g_DesLoadDetour.trampoline)(name, buffer.data());
                buffer.back() = '\0';
                out.assign(buffer.data());
                return true;
            }

            void SetBlockText(void* block, uint32_t setText, const std::string& text,
                              int colour, uint32_t rgb, bool rgbValid)
            {
                reinterpret_cast<FnSetText>(static_cast<uintptr_t>(setText))(block, text.c_str(), colour);
                if (rgbValid)
                    reinterpret_cast<FnSetColour>(static_cast<uintptr_t>(g_SetColourAddr))(block, rgb);
            }

            void SetVisible(void* widget, bool visible)
            {
                if (widget)
                    g_BzrFn_UiSetActive(widget, visible ? 1 : 0);
            }

            void ShowPage(int requested)
            {
                State& s = g_State;
                const int page = Policy::ClampPage(requested, s.count);
                if (page == s.current)
                    return;
                const Page* extra = page > 1 ? &s.pages[static_cast<size_t>(page - 2)] : nullptr;

                SetBlockText(s.missionBlock, g_MissionSetTextAddr, extra ? extra->text : s.page1Text,
                             s.missionColour, s.missionRgb, s.missionRgbValid);

                if (s.planetBlock)
                {
                    const int sidebarPage = extra && !extra->sidebar.empty() ? page : 1;
                    if (sidebarPage != s.shownSidebarPage)
                    {
                        SetBlockText(s.planetBlock, g_PlanetSetTextAddr,
                                     sidebarPage == 1 ? s.page1Sidebar : extra->sidebar,
                                     s.planetColour, s.planetRgb, s.planetRgbValid);
                        s.shownSidebarPage = sidebarPage;
                    }
                }

                const Policy::MediaKind kind = extra ? extra->kind : Policy::MediaKind::Inherit;
                if (kind == Policy::MediaKind::Video && s.videoView)
                {
                    if (s.loadedVideo != extra->media)
                    {
                        reinterpret_cast<FnLoadMovie>(static_cast<uintptr_t>(g_LoadMovieAddr))(
                            s.videoView, extra->media.c_str(), nullptr);
                        reinterpret_cast<FnPlayMovie>(static_cast<uintptr_t>(g_PlayMovieAddr))(s.videoView, true);
                        s.loadedVideo = extra->media;
                    }
                    SetVisible(s.stockMovie, false);
                    SetVisible(s.imageView, false);
                    SetVisible(s.videoView, true);
                }
                else if (kind == Policy::MediaKind::Image && s.imageView)
                {
                    if (s.loadedImage != extra->media)
                    {
                        g_BzrFn_SetTextureOff(s.imageView, extra->media.c_str());
                        s.loadedImage = extra->media;
                    }
                    SetVisible(s.stockMovie, false);
                    SetVisible(s.videoView, false);
                    SetVisible(s.imageView, true);
                }
                else
                {
                    SetVisible(s.imageView, false);
                    SetVisible(s.videoView, false);
                    SetVisible(s.stockMovie, true);
                }

                // The play-wav routine stops the current sound before starting
                // the new one; a page without a wav is silent.
                const std::string& wav = extra ? extra->wav : s.page1Wav;
                if (!wav.empty())
                    reinterpret_cast<FnPlayWav>(g_PlayWavDetour.trampoline)(s.screen, wav.c_str());
                else
                    reinterpret_cast<FnStopWav>(static_cast<uintptr_t>(g_StopWavAddr))(s.screen);

                SetVisible(s.prev, page > 1);
                SetVisible(s.next, page < s.count);
                s.current = page;
            }

            void StepPage(int step)
            {
                if (!g_Active || !ScreenIsLive() || g_State.count < 2)
                    return;
                ShowPage(g_State.current + step);
            }

            void __cdecl PrevClicked() { StepPage(-1); }
            void __cdecl NextClicked() { StepPage(1); }
            void __cdecl ArrowHoverNoop(void*) {}

            void* MakeView(void* overlay, const char* name)
            {
                void* memory = g_GameNew(kUiViewSize);
                if (!memory)
                    return nullptr;
                std::memset(memory, 0, kUiViewSize);
                void* view = g_BzrFn_OverlayCtor(memory, name, kMovieX, kMovieY, kMovieW, kMovieH,
                                                 kWidgetFlags, overlay, 0);
                if (!view)
                    return nullptr;
                g_BzrFn_AddChild(overlay, view, 0);
                g_BzrFn_UiSetActive(view, 0);
                return view;
            }

            void* MakeArrow(void* overlay, const char* name, float y, const char* stem, void (__cdecl* onClick)())
            {
                void* memory = g_GameNew(kUiButtonSize);
                if (!memory)
                    return nullptr;
                std::memset(memory, 0, kUiButtonSize);
                void* button = g_BzrFn_ButtonCtor(memory, name, kArrowX, y, kArrowW, kArrowH,
                                                  kWidgetFlags, overlay, 0, 0);
                if (!button)
                    return nullptr;
                const std::string base(stem);
                g_BzrFn_SetTextureOff(button, (base + "off.png").c_str());
                g_BzrFn_SetTextureOver(button, (base + "clk.png").c_str());
                g_BzrFn_SetTextureOn(button, (base + "on.png").c_str());
                // Stock arrows clear the default label (cUI_ScrollingTextBlock ctor).
                if (g_BzrFn_SetButtonLabel)
                    g_BzrFn_SetButtonLabel(button, "");
                g_BzrFn_SetOnClick(button, reinterpret_cast<void*>(onClick));
                g_BzrFn_SetOnHover(button, reinterpret_cast<void*>(&ArrowHoverNoop));
                g_BzrFn_AddChild(overlay, button, 0);
                return button;
            }

            void BuildPages(void* screen)
            {
                const std::string base = g_CapBase;
                if (base.empty() || g_DesCalls < 1)
                    return;
                if (!Policy::NamesFit(base))
                {
                    // Only worth a line when the mission actually tried for pages.
                    const std::string probe = Policy::PageFileName(base, 2, ".des");
                    if (g_ResourceSize(probe.c_str()) > 0)
                        LogOncePerBase(base, L"name too long for page files (15-char limit); single page");
                    return;
                }
                const int count = Policy::CountPages(base, ResourceExists);
                if (count < 2)
                    return;

                void* overlay = FindChild(screen, "Middle_Overlay");
                void* missionBlock = ReadPointer(screen, kScreenMissionBlockOffset);
                if (!overlay || !missionBlock || !SetTextSlotIs(missionBlock, g_MissionSetTextAddr))
                {
                    LogOncePerBase(base, L"briefing screen layout not recognised; single page");
                    return;
                }

                State s;
                s.screen = screen;
                s.overlay = overlay;
                s.missionBlock = missionBlock;
                s.count = count;
                s.page1Text = g_CapMissionText;
                s.page1Wav = g_CapWav;
                ReadBlockColour(missionBlock, s.missionColour, s.missionRgb, s.missionRgbValid);

                // Sidebars need the planet block and a captured page-1 sidebar to go back to.
                void* planet = FindChild(overlay, "Planet");
                if (planet && g_DesCalls >= 2 && SetTextSlotIs(planet, g_PlanetSetTextAddr))
                {
                    s.planetBlock = planet;
                    s.page1Sidebar = g_CapPlanetText;
                    ReadBlockColour(planet, s.planetColour, s.planetRgb, s.planetRgbValid);
                }
                s.stockMovie = FindChild(overlay, "movie");

                bool anyImage = false, anyVideo = false;
                s.pages.reserve(static_cast<size_t>(count - 1));
                for (int page = 2; page <= count; ++page)
                {
                    const Policy::PageFiles files = Policy::ResolvePage(base, page, [](const std::string& name) {
                        const size_t dot = name.rfind('.');
                        const std::string ext = dot == std::string::npos ? std::string() : name.substr(dot);
                        return ext == ".ogv" || ext == ".png" ? MediaExists(name) : ResourceExists(name);
                    });
                    Page p;
                    if (!LoadDes(files.des, p.text))
                        return;
                    if (s.planetBlock && !files.sidebar.empty() && !LoadDes(files.sidebar, p.sidebar))
                        return;
                    p.media = files.media;
                    p.kind = files.mediaKind;
                    p.wav = files.wav;
                    anyImage = anyImage || p.kind == Policy::MediaKind::Image;
                    anyVideo = anyVideo || p.kind == Policy::MediaKind::Video;
                    s.pages.push_back(std::move(p));
                }

                if (anyImage)
                    s.imageView = MakeView(overlay, "BriefPgImage");
                if (anyVideo)
                    s.videoView = MakeView(overlay, "BriefPgMovie");
                s.prev = MakeArrow(overlay, "BriefPgPrev", kPrevY, "uparr", &PrevClicked);
                s.next = MakeArrow(overlay, "BriefPgNext", kNextY, "dnarr", &NextClicked);
                if (!s.prev || !s.next)
                {
                    // Whatever was built belongs to the overlay; keep it hidden.
                    SetVisible(s.prev, false);
                    SetVisible(s.next, false);
                    LogOncePerBase(base, L"page buttons could not be created; single page");
                    return;
                }
                SetVisible(s.prev, false);
                g_State = std::move(s);
                Log(L"[BRIEFPAGES] %hs: %d pages\n", base.c_str(), count);
            }

            // A fault while adding page widgets must not take the briefing down:
            // the stock screen is already built, so it just stays single-page.
            bool BuildPagesGuarded(void* screen)
            {
                __try
                {
                    BuildPages(screen);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void* __fastcall CtorHook(void* self, void* /*edx*/, int manager, StdStringBytes name)
            {
                const auto original = reinterpret_cast<FnCtor>(g_CtorDetour.trampoline);
                if (!g_Active || !g_BriefingPagesEnabled)
                    return original(self, manager, name);

                g_State = State();
                g_Capturing = self;
                g_DesCalls = 0;
                g_CapBase.clear();
                g_CapMissionText.clear();
                g_CapPlanetText.clear();
                g_CapWav.clear();
                void* result = original(self, manager, name);
                g_Capturing = nullptr;
                if (!BuildPagesGuarded(self))
                {
                    g_State = State();
                    Log(L"[BRIEFPAGES] fault while building pages; single page\n");
                }
                return result;
            }

            uintptr_t __cdecl DesLoadHook(const char* name, char* buffer)
            {
                const uintptr_t result = reinterpret_cast<FnDesLoad>(g_DesLoadDetour.trampoline)(name, buffer);
                if (g_Capturing && buffer)
                {
                    // Call 0 is the mission text, call 1 the planet sidebar.
                    if (g_DesCalls == 0)
                    {
                        g_CapBase = Policy::MissionBaseFromDesArg(name);
                        g_CapMissionText.assign(buffer, strnlen(buffer, kDesBufferSize - 1));
                    }
                    else if (g_DesCalls == 1)
                    {
                        g_CapPlanetText.assign(buffer, strnlen(buffer, kDesBufferSize - 1));
                    }
                    ++g_DesCalls;
                }
                return result;
            }

            void __fastcall PlayWavHook(void* self, void* /*edx*/, const char* wav)
            {
                // The last sound the ctor starts is page 1's.
                if (g_Capturing && self == g_Capturing)
                    g_CapWav = wav ? wav : "";
                reinterpret_cast<FnPlayWav>(g_PlayWavDetour.trampoline)(self, wav);
            }

            bool __fastcall OnKeyHook(void* self, void* /*edx*/, uint32_t key, uint32_t mods)
            {
                if (g_Active && self == g_State.screen && g_State.count > 1 && ScreenIsLive())
                {
                    const int step = Policy::StepForKey(key);
                    if (step != 0)
                    {
                        ShowPage(g_State.current + step);
                        return true;
                    }
                }
                return reinterpret_cast<FnOnKey>(g_OnKeyDetour.trampoline)(self, key, mods);
            }

            bool InstallOne(InlineDetour32& detour, uint32_t target, void* hook, size_t patchLen,
                            const uint8_t* expected, size_t expectedLen, const wchar_t* what)
            {
                if (detour.trampoline)
                    return true;
                if (InstallInlineDetour32(detour, target, hook, patchLen, expected, expectedLen))
                    return true;
                Log(L"[BRIEFPAGES] %ls detour failed at 0x%08X; briefing pages off\n", what, target);
                return false;
            }
        }

        void InstallBriefingPagesIfPossible()
        {
            if (!g_BriefingPagesEnabled || g_Active)
                return;
            static int s_bound = 0;
            if (s_bound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "BriefingScreenCtor", &g_CtorAddr },
                    { "BriefingScreenOnKey", &g_OnKeyAddr },
                    { "BriefingScreenPlayWav", &g_PlayWavAddr },
                    { "BriefingScreenStopWav", &g_StopWavAddr },
                    { "BriefingScreenSingleton", &g_SingletonAddr },
                    { "DescriptionFileLoad", &g_DesLoadAddr },
                    { "ScrollingTextBlockSetText", &g_MissionSetTextAddr },
                    { "TextBlockSetText", &g_PlanetSetTextAddr },
                    { "UiTextBlockSetColour", &g_SetColourAddr },
                    { "UiViewLoadMovie", &g_LoadMovieAddr },
                    { "UiViewPlayMovie", &g_PlayMovieAddr },
                };
                s_bound = HookEngine::BindEngineRows("Briefing pages", rows) ? 1 : -1;
            }
            if (s_bound < 0)
                return;
            // Shared UI bindings resolve later on some launches; ask again next time.
            if (!g_BzrFn_ButtonCtor || !g_BzrFn_OverlayCtor || !g_BzrFn_AddChild || !g_BzrFn_UiSetActive ||
                !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover || !g_BzrFn_SetTextureOff ||
                !g_BzrFn_SetTextureOver || !g_BzrFn_SetTextureOn)
                return;

            static bool s_failed = false;
            if (s_failed)
                return;
            g_ResourceSize = reinterpret_cast<FnResourceSize>(
                static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("Music::ResourceSize")));
            HMODULE crt = GetModuleHandleW(L"MSVCR120.dll");
            g_GameNew = crt ? reinterpret_cast<FnGameNew>(GetProcAddress(crt, "??2@YAPAXI@Z")) : nullptr;
            if (!g_ResourceSize || !g_GameNew)
            {
                s_failed = true;
                Log(L"[BRIEFPAGES] resource-size or game allocator unresolved; briefing pages off\n");
                return;
            }
            g_OgreGroupManager = ResolveOgreProc<decltype(g_OgreGroupManager)>(
                "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
            g_OgreResourceExists = ResolveOgreProc<decltype(g_OgreResourceExists)>(
                "?resourceExistsInAnyGroup@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

            // The planet-video feature finds this routine by its stock prologue;
            // let it resolve (the result is cached) before the detour rewrites it.
            HookEngine::ResolveNamedAddress("PlanetVideo::MissionIntroSound");

            static const uint8_t kDesLoadBytes[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x51, 0x90, 0x84, 0x00 };
            static const uint8_t kPlayWavBytes[] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x34, 0xA1 };
            static const uint8_t kOnKeyBytes[] = { 0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0x08, 0x1B };
            static const uint8_t kCtorBytes[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x53, 0xED, 0x85, 0x00 };
            // The ctor goes last: capture starts only once the others are in.
            const bool ok =
                InstallOne(g_DesLoadDetour, g_DesLoadAddr, reinterpret_cast<void*>(&DesLoadHook), 5,
                           kDesLoadBytes, sizeof(kDesLoadBytes), L"description loader") &&
                InstallOne(g_PlayWavDetour, g_PlayWavAddr, reinterpret_cast<void*>(&PlayWavHook), 6,
                           kPlayWavBytes, sizeof(kPlayWavBytes), L"play-wav") &&
                InstallOne(g_OnKeyDetour, g_OnKeyAddr, reinterpret_cast<void*>(&OnKeyHook), 7,
                           kOnKeyBytes, sizeof(kOnKeyBytes), L"OnKey") &&
                InstallOne(g_CtorDetour, g_CtorAddr, reinterpret_cast<void*>(&CtorHook), 5,
                           kCtorBytes, sizeof(kCtorBytes), L"briefing ctor");
            if (!ok)
            {
                s_failed = true;
                return;
            }
            g_Active = true;
            g_BriefingPagesInstalled = true;
            Log(L"[BRIEFPAGES] briefing pages hooks installed\n");
        }
    }
}
