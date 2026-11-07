// Options screen: shorten the in-game resolution cycle list.
//
// The options screen ctor (0x007AF4A0) walks the Ogre "Video Mode" possible
// values, skips 16-bit and anything under 1024x720, and adds each remaining
// mode with `call 0x007C3AC0` (checklist add, thiscall(str, ogreIndex),
// ret 8) at 0x007B01A8. That call is redirected here; the original is called
// only for modes the policy keeps (include/resolution_list_policy.h).
//
// Current value: right after the add, the ctor compares the item with the
// config's currentValue (`mov ecx,[ebp-0x318]; call 0x41F8C0`, a BzrString*
// stored at 0x7B000A). The thunk records the caller's ebp, so the hook reads
// that BzrString under SEH and always keeps the matching mode. Selection is
// then unaffected, and write-back is by item text.
//
// Config: [Graphics] ResolutionListFilter (default 1);
// OPENSHIM_DISABLE_RESOLUTION_LIST_FILTER=1 turns it off.
#include "resolution_list_filter.h"

#include "bool_token.h"
#include "bzr_string.h"
#include "diagnostic_switch.h"
#include "hook_engine.h"
#include "resolution_list_policy.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <string>

namespace BZROpenShim::Hooks
{
    bool RedirectCallTarget(uintptr_t, uintptr_t, uintptr_t);
}

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "ResolutionListFilter";
        // [ebp-0x318] in the options ctor frame holds the BzrString* of the
        // config's currentValue (store 0x7B000A, load 0x7B01C0; the guard rows start a byte or three earlier; both byte
        // guarded by the ResList* rows in patches.json).
        constexpr uintptr_t kCurrentValueEbpOffset = 0x318;

        using FnChecklistAdd = void(__thiscall*)(void* self, const char* text, int index);

        FnChecklistAdd g_Original = nullptr;
        uintptr_t g_CallerEbp = 0;  // written by the thunk, UI thread only
        bool g_Installed = false;

        // State of the list being built.
        void* g_ListSelf = nullptr;
        int g_LastIndex = -1;
        int g_Kept = 0;
        int g_Total = 0;
        int g_DesktopW = 0;
        int g_DesktopH = 0;
        ResolutionList::SeenSizes g_Seen;

        // POD only: contains __try. False when the frame slot or string looks
        // wrong, in which case there is no "current" mode.
        bool TryReadCurrentValue(uintptr_t ebp, char* out, size_t outSize)
        {
            out[0] = '\0';
            __try
            {
                const BzrString* value = *reinterpret_cast<const BzrString* const*>(ebp - kCurrentValueEbpOffset);
                if (!value || value->capacity < 0xF || value->capacity > 0x1000 || value->size > value->capacity)
                    return false;
                const char* data = (value->capacity > 0xF) ? value->heap : value->small;
                if (!data)
                    return false;
                size_t n = value->size;
                if (n >= outSize)
                    n = outSize - 1;
                std::memcpy(out, data, n);
                out[n] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void FlushListLog()
        {
            if (g_Total > 0)
                LogShimA(LogLevel::Info, kComponent, "[ResList] kept %d of %d modes", g_Kept, g_Total);
            g_Total = g_Kept = 0;
        }

        void __fastcall AddHook(void* self, void* /*edx*/, const char* text, int index)
        {
            if (self != g_ListSelf || index <= g_LastIndex)
            {
                // A new list started; the previous one is complete.
                FlushListLog();
                g_ListSelf = self;
                g_Seen.Clear();
                DEVMODEA mode = {};
                mode.dmSize = sizeof(mode);
                g_DesktopW = g_DesktopH = 0;
                // The registry mode is the desktop's own; the current mode is the
                // game's when it already runs fullscreen at another aspect.
                if (EnumDisplaySettingsA(nullptr, ENUM_REGISTRY_SETTINGS, &mode) ||
                    EnumDisplaySettingsA(nullptr, ENUM_CURRENT_SETTINGS, &mode))
                {
                    g_DesktopW = static_cast<int>(mode.dmPelsWidth);
                    g_DesktopH = static_cast<int>(mode.dmPelsHeight);
                }
            }
            g_LastIndex = index;
            ++g_Total;

            int w = 0, h = 0;
            bool keep = true;  // fail open
            if (ResolutionList::ParseModeSize(text, w, h))
            {
                char current[128];
                const bool haveCurrent = TryReadCurrentValue(g_CallerEbp, current, sizeof(current));
                const bool isCurrent = haveCurrent && std::strcmp(text, current) == 0;
                keep = ResolutionList::ShouldKeep(w, h, g_DesktopW, g_DesktopH, isCurrent, g_Seen);
            }
            if (!keep)
                return;
            ++g_Kept;
            g_Original(self, text, index);
        }

        // Keeps the call site's thiscall shape (ecx, 2 stack args, ret 8) and
        // records the caller's frame for AddHook, which is __fastcall with the
        // same stack layout.
        __declspec(naked) void AddThunk()
        {
            __asm
            {
                mov dword ptr [g_CallerEbp], ebp
                jmp AddHook
            }
        }
    }

    void InitializeResolutionListFilter()
    {
        if (g_Installed)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_RESOLUTION_LIST_FILTER", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;
        const std::string ini = DiagnosticSwitch::OpenShimIniPath();
        if (GetPrivateProfileIntA("Graphics", "ResolutionListFilter", 1, ini.c_str()) == 0)
            return;

        uint32_t call = 0, target = 0, load = 0, store = 0;
        const HookEngine::EngineRow rows[] = {
            {"ResListAddCall", &call},
            {"ResListAddTarget", &target},
            {"ResListCurrentValueLoad", &load},
            {"ResListCurrentValueStore", &store},
        };
        if (!HookEngine::BindEngineRows("ResolutionListFilter", rows, sizeof(rows) / sizeof(rows[0])))
            return;  // BindEngineRows logged the reason once.

        g_Original = reinterpret_cast<FnChecklistAdd>(static_cast<uintptr_t>(target));
        if (!Hooks::RedirectCallTarget(call, target, reinterpret_cast<uintptr_t>(&AddThunk)))
        {
            LogShimA(LogLevel::Warn, kComponent, "[ResList] stands down: add call site did not match");
            return;
        }
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent, "[ResList] installed: resolution list filtered");
    }
}
