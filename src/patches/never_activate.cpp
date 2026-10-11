// never_activate.cpp
// BZR Open Shim - OPENSHIM_NEVER_ACTIVATE: keep a test client from taking the
// foreground or keyboard focus from whoever is at the desk.
#include "bzr_hooks.h"
#include "bzr_options_ui.h"
#include "iat_patch.h"
#include "never_activate_policy.h"
#include "patcher.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <intrin.h>
#include <winternl.h>

namespace BZROpenShim
{
    namespace
    {
        // OPENSHIM_NEVER_ACTIVATE=1 (environment, or [Environment] in
        // openshim.ini) stops the game window taking the foreground or
        // keyboard focus. NEVER_CAPTURE_MOUSE covers the cursor only.
        //
        // The first version patched only the executable's IAT. Ogre's window is
        // created and restyled inside RenderSystem_Direct3D11.dll / OgreMain.dll,
        // and DXGI shows and raises windows from inside the system, so none of
        // that went through the hooked imports. This version patches the user32
        // imports of EVERY loaded module (including the api-ms/ext-ms
        // forwarders user32 sits behind), and any module loaded later:
        //   * a loader DLL-notification callback patches new modules as they load;
        //   * every InstallNeverActivateHooks call re-sweeps, which also repairs
        //     a module the callback saw before the loader had snapped its imports.
        // The shim's own module and user32 itself are left alone, so the hooks'
        // calls to the real functions never recurse.
        //
        // Hooked: ShowWindow, ShowWindowAsync (activating commands ->
        // SHOWNOACTIVATE), SetForegroundWindow / BringWindowToTop /
        // SetActiveWindow / SwitchToThisWindow / AllowSetForegroundWindow
        // (no-ops), SetWindowPos (SWP_NOACTIVATE added), CreateWindowExA/W
        // (a visible top-level window is created hidden, then shown with
        // SW_SHOWNOACTIVATE), SetFocus (blocked unless the target's top-level
        // window already is the foreground window).
        //
        // Off by default; with the flag unset no import is touched.

        namespace Policy = NeverActivatePolicy;

        enum Slot
        {
            kShowWindow,
            kShowWindowAsync,
            kSetForegroundWindow,
            kBringWindowToTop,
            kSetActiveWindow,
            kSetWindowPos,
            kSwitchToThisWindow,
            kAllowSetForegroundWindow,
            kCreateWindowExA,
            kCreateWindowExW,
            kSetFocus,
            kSlotCount
        };

        const char* const kNames[kSlotCount] = {
            "ShowWindow", "ShowWindowAsync", "SetForegroundWindow", "BringWindowToTop",
            "SetActiveWindow", "SetWindowPos", "SwitchToThisWindow", "AllowSetForegroundWindow",
            "CreateWindowExA", "CreateWindowExW", "SetFocus"};

        using FnShowWindow = BOOL(WINAPI*)(HWND, int);
        using FnSetWindowPos = BOOL(WINAPI*)(HWND, HWND, int, int, int, int, UINT);
        using FnCreateWindowExA = HWND(WINAPI*)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
        using FnCreateWindowExW = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
        using FnSetFocus = HWND(WINAPI*)(HWND);

        void* s_hooks[kSlotCount] = {};
        void* s_real[kSlotCount] = {};
        HMODULE s_self = nullptr;
        bool s_requested = false;
        bool s_initialized = false;
        void* s_notificationCookie = nullptr;
        volatile long s_logged[kSlotCount] = {};
        volatile long s_sweepLogBudget = 6;

        // One-shot per API: names the module and offset of the first caller so a
        // later run identifies the culprit.
        void Note(Slot slot, const char* what, void* returnAddress)
        {
            if (InterlockedExchange(&s_logged[slot], 1) != 0)
                return;
            wchar_t path[MAX_PATH] = L"?";
            DWORD offset = 0;
            HMODULE module = nullptr;
            if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                       GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                   reinterpret_cast<LPCWSTR>(returnAddress), &module) &&
                module)
            {
                wchar_t full[MAX_PATH] = {};
                if (GetModuleFileNameW(module, full, MAX_PATH))
                {
                    const wchar_t* base = wcsrchr(full, L'\\');
                    wcsncpy_s(path, base ? base + 1 : full, _TRUNCATE);
                }
                offset = static_cast<DWORD>(reinterpret_cast<const char*>(returnAddress) -
                                            reinterpret_cast<const char*>(module));
            }
            Log(L"[NOACTIVATE] Never-activate mode; suppressed %hs (caller %ls+0x%X)\n", what, path, offset);
        }

        BOOL WINAPI ShowWindowHook(HWND hwnd, int cmd)
        {
            const int mapped = Policy::NoActivateShowCommand(cmd);
            if (mapped != cmd)
                Note(kShowWindow, "ShowWindow activation", _ReturnAddress());
            return reinterpret_cast<FnShowWindow>(s_real[kShowWindow])(hwnd, mapped);
        }

        BOOL WINAPI ShowWindowAsyncHook(HWND hwnd, int cmd)
        {
            const int mapped = Policy::NoActivateShowCommand(cmd);
            if (mapped != cmd)
                Note(kShowWindowAsync, "ShowWindowAsync activation", _ReturnAddress());
            return reinterpret_cast<FnShowWindow>(s_real[kShowWindowAsync])(hwnd, mapped);
        }

        BOOL WINAPI SetForegroundWindowHook(HWND)
        {
            Note(kSetForegroundWindow, "SetForegroundWindow", _ReturnAddress());
            return TRUE;
        }

        BOOL WINAPI BringWindowToTopHook(HWND)
        {
            Note(kBringWindowToTop, "BringWindowToTop", _ReturnAddress());
            return TRUE;
        }

        HWND WINAPI SetActiveWindowHook(HWND)
        {
            Note(kSetActiveWindow, "SetActiveWindow", _ReturnAddress());
            return GetActiveWindow(); // SetActiveWindow returns the previous active window
        }

        void WINAPI SwitchToThisWindowHook(HWND, BOOL)
        {
            Note(kSwitchToThisWindow, "SwitchToThisWindow", _ReturnAddress());
        }

        BOOL WINAPI AllowSetForegroundWindowHook(DWORD)
        {
            Note(kAllowSetForegroundWindow, "AllowSetForegroundWindow", _ReturnAddress());
            return TRUE;
        }

        BOOL WINAPI SetWindowPosHook(HWND hwnd, HWND after, int x, int y, int cx, int cy, UINT flags)
        {
            if (!(flags & Policy::kSwpNoActivate))
                Note(kSetWindowPos, "SetWindowPos activation", _ReturnAddress());
            flags = Policy::NoActivateWindowPosFlags(flags);
            return reinterpret_cast<FnSetWindowPos>(s_real[kSetWindowPos])(hwnd, after, x, y, cx, cy, flags);
        }

        HWND WINAPI CreateWindowExAHook(DWORD ex, LPCSTR cls, LPCSTR name, DWORD style, int x, int y, int w, int h,
                                        HWND parent, HMENU menu, HINSTANCE inst, LPVOID param)
        {
            const bool defer = Policy::ShouldDeferVisibleCreate(style);
            if (defer)
            {
                Note(kCreateWindowExA, "CreateWindowExA WS_VISIBLE activation", _ReturnAddress());
                style = Policy::StyleWithoutVisible(style);
            }
            HWND hwnd = reinterpret_cast<FnCreateWindowExA>(s_real[kCreateWindowExA])(
                ex, cls, name, style, x, y, w, h, parent, menu, inst, param);
            if (hwnd && defer)
                reinterpret_cast<FnShowWindow>(s_real[kShowWindow])(hwnd, Policy::DeferredShowCommand(style));
            return hwnd;
        }

        HWND WINAPI CreateWindowExWHook(DWORD ex, LPCWSTR cls, LPCWSTR name, DWORD style, int x, int y, int w, int h,
                                        HWND parent, HMENU menu, HINSTANCE inst, LPVOID param)
        {
            const bool defer = Policy::ShouldDeferVisibleCreate(style);
            if (defer)
            {
                Note(kCreateWindowExW, "CreateWindowExW WS_VISIBLE activation", _ReturnAddress());
                style = Policy::StyleWithoutVisible(style);
            }
            HWND hwnd = reinterpret_cast<FnCreateWindowExW>(s_real[kCreateWindowExW])(
                ex, cls, name, style, x, y, w, h, parent, menu, inst, param);
            if (hwnd && defer)
                reinterpret_cast<FnShowWindow>(s_real[kShowWindow])(hwnd, Policy::DeferredShowCommand(style));
            return hwnd;
        }

        HWND WINAPI SetFocusHook(HWND hwnd)
        {
            if (hwnd)
            {
                const HWND root = GetAncestor(hwnd, GA_ROOT);
                const HWND foreground = GetForegroundWindow();
                if (Policy::ShouldBlockSetFocus(true, reinterpret_cast<std::uintptr_t>(root ? root : hwnd),
                                                reinterpret_cast<std::uintptr_t>(foreground)))
                {
                    Note(kSetFocus, "SetFocus on a background window", _ReturnAddress());
                    return GetFocus();
                }
            }
            return reinterpret_cast<FnSetFocus>(s_real[kSetFocus])(hwnd);
        }

        // Patches one module; returns the number of imports it covers.
        int PatchModule(HMODULE module)
        {
            if (!module || module == s_self)
                return 0;
            int count = 0;
            for (int i = 0; i < kSlotCount; ++i)
            {
                IatPatch::Result r = IatPatch::PatchImport(module, "user32.dll", kNames[i], s_hooks[i], nullptr);
                if (r == IatPatch::Result::NotFound)
                    r = IatPatch::PatchImportFromAnyDll(module, kNames[i], s_hooks[i], nullptr);
                if (r == IatPatch::Result::Patched)
                    ++count;
            }
            return count;
        }

        // Re-patching an already patched slot returns Patched without a write, so
        // the sweep reports slots covered, not slots newly written.
        int SweepAllModules(int* modulesSeen)
        {
            HANDLE snap = INVALID_HANDLE_VALUE;
            for (int attempt = 0; attempt < 5; ++attempt)
            {
                snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId());
                if (snap != INVALID_HANDLE_VALUE || GetLastError() != ERROR_BAD_LENGTH)
                    break;
            }
            if (snap == INVALID_HANDLE_VALUE)
                return 0;
            const HMODULE user32 = GetModuleHandleW(L"user32.dll");
            int total = 0;
            int seen = 0;
            MODULEENTRY32W entry = {};
            entry.dwSize = sizeof(entry);
            for (BOOL ok = Module32FirstW(snap, &entry); ok; ok = Module32NextW(snap, &entry))
            {
                const HMODULE module = reinterpret_cast<HMODULE>(entry.modBaseAddr);
                if (module == user32)
                    continue;
                ++seen;
                total += PatchModule(module);
            }
            CloseHandle(snap);
            if (modulesSeen)
                *modulesSeen = seen;
            return total;
        }

        struct DllNotificationData
        {
            ULONG Flags;
            const UNICODE_STRING* FullDllName;
            const UNICODE_STRING* BaseDllName;
            PVOID DllBase;
            ULONG SizeOfImage;
        };
        using FnDllNotification = void(CALLBACK*)(ULONG, const DllNotificationData*, PVOID);
        using FnLdrRegisterDllNotification = LONG(NTAPI*)(ULONG, FnDllNotification, PVOID, PVOID*);

        // Runs under the loader lock: patch only, no logging, no allocation.
        void CALLBACK OnDllNotification(ULONG reason, const DllNotificationData* data, PVOID)
        {
            if (reason == 1 /* LDR_DLL_NOTIFICATION_REASON_LOADED */ && data && data->DllBase)
            {
                const HMODULE module = reinterpret_cast<HMODULE>(data->DllBase);
                if (module != GetModuleHandleW(L"user32.dll"))
                    PatchModule(module);
            }
        }
    }

    void InstallNeverActivateHooks()
    {
        if (!s_initialized)
        {
            s_initialized = true;
            s_requested = EnvFlagEnabled("OPENSHIM_NEVER_ACTIVATE");
            if (!s_requested)
                return; // flag unset: no hooks, no retry
            Log(L"[NOACTIVATE] OPENSHIM_NEVER_ACTIVATE: window never takes foreground or focus (test clients only)\n");

            GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               reinterpret_cast<LPCWSTR>(&InstallNeverActivateHooks), &s_self);

            const HMODULE user32 = LoadLibraryW(L"user32.dll");
            void* const hooks[kSlotCount] = {
                reinterpret_cast<void*>(&ShowWindowHook), reinterpret_cast<void*>(&ShowWindowAsyncHook),
                reinterpret_cast<void*>(&SetForegroundWindowHook), reinterpret_cast<void*>(&BringWindowToTopHook),
                reinterpret_cast<void*>(&SetActiveWindowHook), reinterpret_cast<void*>(&SetWindowPosHook),
                reinterpret_cast<void*>(&SwitchToThisWindowHook), reinterpret_cast<void*>(&AllowSetForegroundWindowHook),
                reinterpret_cast<void*>(&CreateWindowExAHook), reinterpret_cast<void*>(&CreateWindowExWHook),
                reinterpret_cast<void*>(&SetFocusHook)};
            bool resolved = user32 != nullptr;
            for (int i = 0; i < kSlotCount; ++i)
            {
                s_hooks[i] = hooks[i];
                s_real[i] = user32 ? reinterpret_cast<void*>(GetProcAddress(user32, kNames[i])) : nullptr;
                // The hooks that forward to the real function need a target.
                if (!s_real[i] && (i == kShowWindow || i == kShowWindowAsync || i == kSetWindowPos ||
                                   i == kCreateWindowExA || i == kCreateWindowExW || i == kSetFocus))
                    resolved = false;
            }
            if (!resolved)
            {
                Log(L"[NOACTIVATE] could not resolve user32 exports; hooks NOT installed\n");
                s_requested = false;
                return;
            }

            if (HMODULE ntdll = GetModuleHandleW(L"ntdll.dll"))
            {
                const auto reg = reinterpret_cast<FnLdrRegisterDllNotification>(
                    reinterpret_cast<void*>(GetProcAddress(ntdll, "LdrRegisterDllNotification")));
                if (reg && reg(0, &OnDllNotification, nullptr, &s_notificationCookie) == 0)
                    Log(L"[NOACTIVATE] DLL-notification hook registered for later-loaded modules\n");
                else
                    Log(L"[NOACTIVATE] DLL-notification hook unavailable; relying on periodic sweeps\n");
            }
        }
        if (!s_requested)
            return;

        int modules = 0;
        const int covered = SweepAllModules(&modules);
        if (InterlockedDecrement(&s_sweepLogBudget) >= 0)
            Log(L"[NOACTIVATE] sweep: %d user32 imports covered across %d modules\n", covered, modules);
    }
}
