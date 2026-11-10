// Graphics options screen: the stock "Full Screen" row gains a third value,
// Borderless, on DX11.
//
// The options ctor (0x007AF4A0) fills the Full Screen cUI_Checklist
// (screen+0x150) with the Ogre "Full Screen" possible values ("Yes", "No"),
// item value = possibleValues index, selects the current one, then installs
// the change callback with `call 0x007C3CF0` at 0x007B07CF. That call is
// redirected here: after the original runs, a "Borderless" item is appended
// (value kBorderlessValue, not an Ogre index), and selected when "Yes" is
// current and [Graphics] BorderlessFullscreen is on.
//
// Apply (0x007AEBC0, reached only through `call` at 0x007AE819) writes the
// selected item's TEXT to Ogre's "Full Screen" option. That call is
// redirected too: while Borderless is selected the "Yes" item is selected
// around the original, so Ogre only ever sees "Yes"/"No". When the Full Screen
// row changed (dirty byte +0x19E) and the borderless choice differs from the
// ini, the ini is written and the stock restart-required path (+0x19F) is
// raised: dxgi_flip_model.cpp reads the key once at startup.
//
// DX9 (Ogre's active render system is not Direct3D11) gets no third item, so the row
// stays two-state. OPENSHIM_DISABLE_FULLSCREEN_MODE_CHOICE=1 turns it off.
// RE note: reverse_engineering/fullscreen_mode_choice_20261110.md.
#include "fullscreen_mode_choice.h"

#include "bool_token.h"
#include "diagnostic_switch.h"
#include "hook_engine.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <string>

namespace BZROpenShim::Hooks
{
    bool RedirectCallTarget(uintptr_t, uintptr_t, uintptr_t);
    bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
}

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "FullscreenModeChoice";

        // Ogre D3D11 "Full Screen" possible value that means fullscreen; the
        // checklist item text is the raw possible value (ctor 0x007B077A).
        constexpr const char* kFullscreenText = "Yes";
        constexpr const char* kBorderlessText = "Borderless";
        // Not an Ogre possibleValues index, so it never collides with one.
        constexpr int kBorderlessValue = 0x100;

        // cUI_OptionsGraphics.
        constexpr uint32_t kScreenFullScreenList = 0x150;
        constexpr uint32_t kScreenAlert = 0x178;        // open restart alert
        constexpr uint32_t kScreenFullScreenDirty = 0x19E;
        constexpr uint32_t kScreenRestartDirty = 0x19F; // saveConfig + restart alert
        // cUI_Checklist.
        constexpr uint32_t kListSelected = 0x1DC;
        constexpr uint32_t kListItemsBegin = 0x1E4;     // vector<Item*>
        constexpr uint32_t kListItemsEnd = 0x1E8;

        struct ChecklistItem
        {
            char text[0x40];
            int value;
        };

        using FnSetCallback = void(__thiscall*)(void* list, void* callback);
        using FnAdd = void(__thiscall*)(void* list, const char* text, int value);
        using FnSelectValue = void(__thiscall*)(void* list, int value);
        using FnApply = void(__fastcall*)(void* screen);

        FnSetCallback g_SetCallback = nullptr;
        FnAdd g_Add = nullptr;
        FnSelectValue g_SelectValue = nullptr;
        FnApply g_Apply = nullptr;
        bool g_Installed = false;

        // The Full Screen list of the last screen built (UI thread only). Only
        // compared with screen+0x150, never dereferenced on its own.
        void* g_List = nullptr;
        int g_FullscreenValue = -1;

        // POD only: contains __try. Value of the item whose text matches, or -1.
        int FindItemValue(void* list, const char* text)
        {
            __try
            {
                const auto base = reinterpret_cast<uintptr_t>(list);
                auto it = *reinterpret_cast<ChecklistItem* const* const*>(base + kListItemsBegin);
                auto end = *reinterpret_cast<ChecklistItem* const* const*>(base + kListItemsEnd);
                if (!it || end < it || end - it > 64)
                    return -1;
                for (; it != end; ++it)
                    if (*it && std::strncmp((*it)->text, text, sizeof((*it)->text)) == 0)
                        return (*it)->value;
                return -1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // POD only: contains __try. False when there is no valid selection.
        bool SelectedValue(void* list, int& value)
        {
            __try
            {
                const auto base = reinterpret_cast<uintptr_t>(list);
                auto begin = *reinterpret_cast<ChecklistItem* const* const*>(base + kListItemsBegin);
                auto end = *reinterpret_cast<ChecklistItem* const* const*>(base + kListItemsEnd);
                const int index = *reinterpret_cast<const int*>(base + kListSelected);
                if (!begin || end < begin || index < 0 || index >= end - begin || !begin[index])
                    return false;
                value = begin[index]->value;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // POD only: contains __try.
        bool ReadScreen(void* screen, void*& list, uint32_t& alert)
        {
            __try
            {
                const auto base = reinterpret_cast<uintptr_t>(screen);
                list = *reinterpret_cast<void* const*>(base + kScreenFullScreenList);
                alert = *reinterpret_cast<const uint32_t*>(base + kScreenAlert);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // POD only: contains __try. Adds the item; selects it when wanted.
        bool AddBorderlessGuarded(void* list, bool selectIt)
        {
            __try
            {
                g_Add(list, kBorderlessText, kBorderlessValue);
                if (selectIt)
                    g_SelectValue(list, kBorderlessValue);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // POD only: contains __try.
        bool SelectGuarded(void* list, int value)
        {
            __try
            {
                g_SelectValue(list, value);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool Dx11Renderer()
        {
            // Ogre's ACTIVE render system, not module presence: every
            // configured RenderSystem DLL is loaded, DX9 sessions included
            // (seen live: D3D9, D3D11 and GL all mapped in one process).
            return RenderProfiles::IdentifyActiveRenderSystem() == 1;
        }

        bool IniBorderless()
        {
            const std::string ini = DiagnosticSwitch::OpenShimIniPath();
            return GetPrivateProfileIntA("Graphics", "BorderlessFullscreen", 0, ini.c_str()) != 0;
        }

        void ExtendList(void* list)
        {
            g_List = nullptr;
            if (!Dx11Renderer())
                return;  // DX9: the stock two values.
            if (!Hooks::VtableTypeNameMatches(*reinterpret_cast<uintptr_t*>(list), ".?AVcUI_Checklist@@"))
            {
                LogShimA(LogLevel::Warn, kComponent, "[FsMode] Full Screen row is not a cUI_Checklist; left stock");
                return;
            }
            // dxgi_flip_model.cpp lets the environment win over the ini; the
            // row could not change the mode then, so it stays stock.
            char env[16] = {};
            if (GetEnvironmentVariableA("OPENSHIM_BORDERLESS_FULLSCREEN", env, static_cast<DWORD>(sizeof(env))) > 0)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[FsMode] OPENSHIM_BORDERLESS_FULLSCREEN is set; Full Screen row left stock");
                return;
            }
            const int fullscreen = FindItemValue(list, kFullscreenText);
            if (fullscreen < 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FsMode] Full Screen row has no \"%s\" item; left stock",
                         kFullscreenText);
                return;
            }
            if (FindItemValue(list, kBorderlessText) >= 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[FsMode] Full Screen row already has \"%s\"; left as is",
                         kBorderlessText);
                return;
            }
            int selected = -1;
            const bool fullscreenNow = SelectedValue(list, selected) && selected == fullscreen;
            const bool borderless = fullscreenNow && IniBorderless();
            if (!AddBorderlessGuarded(list, borderless))
            {
                LogShimA(LogLevel::Warn, kComponent, "[FsMode] adding the Borderless item faulted");
                return;
            }
            g_List = list;
            g_FullscreenValue = fullscreen;
            LogShimA(LogLevel::Info, kComponent, "[FsMode] Full Screen row: Borderless added (shown=%s)",
                     borderless ? "Borderless" : (fullscreenNow ? "Yes" : "No"));
        }

        // Replaces `call 0x007C3CF0` (thiscall(list, callback), ret 4).
        void __fastcall SetCallbackHook(void* list, void* /*edx*/, void* callback)
        {
            g_SetCallback(list, callback);
            if (list)
                ExtendList(list);
        }

        // Replaces `call 0x007AEBC0` (fastcall(screen)).
        void __fastcall ApplyHook(void* screen)
        {
            void* list = nullptr;
            uint32_t alert = 1;
            int selected = -1;
            // The original does nothing while a restart alert is open (+0x178).
            if (!g_List || !screen || !ReadScreen(screen, list, alert) || list != g_List || alert != 0 ||
                !SelectedValue(list, selected))
            {
                g_Apply(screen);
                return;
            }

            const bool borderless = selected == kBorderlessValue;
            auto* bytes = reinterpret_cast<volatile uint8_t*>(screen);
            if (bytes[kScreenFullScreenDirty] != 0 && borderless != IniBorderless())
            {
                const std::string ini = DiagnosticSwitch::OpenShimIniPath();
                if (WritePrivateProfileStringA("Graphics", "BorderlessFullscreen", borderless ? "1" : "0",
                                               ini.c_str()))
                {
                    // Stock restart path: saveConfig and the restart_required alert.
                    bytes[kScreenRestartDirty] = 1;
                    LogShimA(LogLevel::Info, kComponent, "[FsMode] BorderlessFullscreen = %d (restart required)",
                             borderless ? 1 : 0);
                }
                else
                {
                    LogShimA(LogLevel::Warn, kComponent, "[FsMode] could not write BorderlessFullscreen (error %lu)",
                             GetLastError());
                }
            }

            if (!borderless)
            {
                g_Apply(screen);
                return;
            }
            // Ogre must only see a value it offered.
            g_SelectValue(list, g_FullscreenValue);
            g_Apply(screen);
            // Apply switches the mode live; only touch the list if the screen
            // still holds it.
            void* after = nullptr;
            uint32_t ignored = 0;
            if (ReadScreen(screen, after, ignored) && after == list && !SelectGuarded(list, kBorderlessValue))
                LogShimA(LogLevel::Warn, kComponent, "[FsMode] reselecting Borderless faulted");
        }
    }

    void InitializeFullscreenModeChoice()
    {
        if (g_Installed)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_FULLSCREEN_MODE_CHOICE", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;

        uint32_t callbackGuard = 0, callbackCall = 0, callbackTarget = 0;
        uint32_t applyGuard = 0, applyCall = 0, applyTarget = 0;
        uint32_t add = 0, selectValue = 0;
        const HookEngine::EngineRow rows[] = {
            {"FsModeCallbackGuard", &callbackGuard},
            {"FsModeSetCallbackCall", &callbackCall},
            {"FsModeSetCallbackTarget", &callbackTarget},
            {"FsModeApplyGuard", &applyGuard},
            {"FsModeApplyCall", &applyCall},
            {"FsModeApplyTarget", &applyTarget},
            {"ResListAddTarget", &add},
            {"ResDropChecklistSelectValue", &selectValue},
        };
        if (!HookEngine::BindEngineRows("FullscreenModeChoice", rows, sizeof(rows) / sizeof(rows[0])))
            return;  // BindEngineRows logged the reason once.

        g_SetCallback = reinterpret_cast<FnSetCallback>(static_cast<uintptr_t>(callbackTarget));
        g_Add = reinterpret_cast<FnAdd>(static_cast<uintptr_t>(add));
        g_SelectValue = reinterpret_cast<FnSelectValue>(static_cast<uintptr_t>(selectValue));
        g_Apply = reinterpret_cast<FnApply>(static_cast<uintptr_t>(applyTarget));

        // Apply first: a list item the apply hook does not know about must
        // never reach Ogre's "Full Screen" option.
        if (!Hooks::RedirectCallTarget(applyCall, applyTarget, reinterpret_cast<uintptr_t>(&ApplyHook)))
        {
            LogShimA(LogLevel::Warn, kComponent, "[FsMode] stands down: apply call site did not match");
            return;
        }
        if (!Hooks::RedirectCallTarget(callbackCall, callbackTarget, reinterpret_cast<uintptr_t>(&SetCallbackHook)))
        {
            // The apply hook passes everything through while g_List is null.
            LogShimA(LogLevel::Warn, kComponent, "[FsMode] stands down: Full Screen callback call site did not match");
            return;
        }
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent, "[FsMode] installed: Full Screen row offers Borderless on DX11");
    }
}
