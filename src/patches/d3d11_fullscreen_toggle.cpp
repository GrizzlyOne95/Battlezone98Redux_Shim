// DX11: make Alt-Enter from a window reach fullscreen.
//
// Why: stock Alt-Enter toggles Ogre's "Full Screen" option and calls
// RenderWindow::setFullscreen(true, w, h). In Redux's RenderSystem_Direct3D11
// (GOG 2.2.301, Ghidra decompile of the shipped DLL):
//   - D3D11RenderWindowHwnd::setFullscreen (0x100022c5) stores mIsFullScreen
//     and only then calls SetWindowPos(HWND_TOPMOST, 0, 0, w, h) and strips
//     the caption;
//   - each size change is delivered as WM_SIZE inside that call, and
//     windowMovedOrResized (0x10006460) -> _resizeSwapChainBuffers
//     (0x100048f9) ends with mIsFullScreen = (swap chain desc.Windowed == 0).
//     The swap chain is still windowed, so the flag is cleared again;
//   - on the next frame _finishSwitchingFullscreen (0x10005218) sees a
//     windowed render window, never calls SetFullscreenState, and re-centres
//     the window at the originally requested windowed size, now without its
//     caption.
// Result: a small borderless window in the middle of the screen (measured
// 2026-11-10 on a 3840x2160 desktop from a 1600x900 window: 1622x956 at
// 1109,566, style 0x16000000), with or without flip model. It only works when
// the window already has the fullscreen size, because then no WM_SIZE is sent.
// The same clobber exists on the way back (the flag is set again while the
// swap chain is still fullscreen). DX9 has its own render window and is fine.
//
// What: the setFullscreen entry of the D3D11RenderWindowHwnd vtable is wrapped
// and the original is called twice. The first call resizes the window (and
// may lose the flag); the second finds the window already at the right size,
// so nothing resizes and the flag it stores survives. When the first call was
// enough, the second is the function's own "nothing changed" early return.
//
// Fail closed: the slot is found by comparing the DLL's exported vtable with
// its exported setFullscreen; no match means nothing is patched.
//
// Kill switch: OPENSHIM_DISABLE_D3D11_FULLSCREEN_FIX=1 (stock behaviour).
#include "bool_token.h"
#include "com_vtable_patch.h"
#include "d3d11_fullscreen_toggle.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>
#include <process.h>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "D3D11FullscreenToggle";
        constexpr unsigned kDiscoveryAttempts = 3000;  // 3000 x 20 ms
        constexpr DWORD kDiscoverySleepMs = 20;
        // RenderWindow has about 90 virtuals; setFullscreen is entry 67.
        constexpr size_t kVtableSearchEntries = 128;

        constexpr const char* kVtableExport = "??_7D3D11RenderWindowHwnd@Ogre@@6BRenderWindow@1@@";
        constexpr const char* kSetFullscreenExport = "?setFullscreen@D3D11RenderWindowHwnd@Ogre@@UAEX_NII@Z";

        // __thiscall as __fastcall: ecx = this, edx unused, callee pops the rest.
        using FnSetFullscreen = void(__fastcall*)(void* self, void* edx, bool fullScreen, unsigned width,
                                                  unsigned height);
        FnSetFullscreen g_RealSetFullscreen = nullptr;
        uintptr_t g_DiscoveryThread = 0;

        void __fastcall HookSetFullscreen(void* self, void* edx, bool fullScreen, unsigned width, unsigned height)
        {
            g_RealSetFullscreen(self, edx, fullScreen, width, height);
            g_RealSetFullscreen(self, edx, fullScreen, width, height);
            LogShimA(LogLevel::Info, kComponent, "[DX11 Fullscreen] setFullscreen(%s, %ux%u) applied twice",
                     fullScreen ? "fullscreen" : "windowed", width, height);
        }

        void Install(HMODULE renderer)
        {
            void** vtable = reinterpret_cast<void**>(GetProcAddress(renderer, kVtableExport));
            void* target = reinterpret_cast<void*>(GetProcAddress(renderer, kSetFullscreenExport));
            if (!vtable || !target)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Fullscreen] renderer does not export the render window vtable and setFullscreen; not installed");
                return;
            }
            size_t slot = kVtableSearchEntries;
            for (size_t i = 0; i < kVtableSearchEntries; ++i)
            {
                if (vtable[i] == target)
                {
                    slot = i;
                    break;
                }
            }
            if (slot == kVtableSearchEntries)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Fullscreen] setFullscreen is not in the render window vtable; not installed");
                return;
            }
            // Set before the entry is written, so the hook can never run without it.
            g_RealSetFullscreen = reinterpret_cast<FnSetFullscreen>(target);
            // PatchEntry takes an object, i.e. a pointer to a vtable pointer.
            const auto result = ComVtablePatch::PatchEntry(&vtable, slot, &HookSetFullscreen, g_RealSetFullscreen,
                                                           ComVtablePatch::OnForeignWrapper::Refuse);
            if (ComVtablePatch::Succeeded(result))
                LogShimA(LogLevel::Info, kComponent,
                         "[DX11 Fullscreen] installed (vtable entry %u): Alt-Enter keeps the fullscreen state through the resize",
                         static_cast<unsigned>(slot));
            else
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Fullscreen] could not write the vtable entry (result=%d); not installed",
                         static_cast<int>(result));
        }

        unsigned __stdcall DiscoveryThreadProc(void*)
        {
            for (unsigned attempt = 0; attempt < kDiscoveryAttempts; ++attempt)
            {
                HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
                if (renderer)
                {
                    IatPatch::WaitForModuleLoadToFinish(renderer, nullptr);
                    Install(renderer);
                    return 0;
                }
                Sleep(kDiscoverySleepMs);
            }
            return 0;  // DX9, or the renderer never loaded: nothing to do.
        }
    }

    void InitializeD3D11FullscreenToggle()
    {
        if (g_DiscoveryThread)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_D3D11_FULLSCREEN_FIX", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;
        g_DiscoveryThread = _beginthreadex(nullptr, 0, DiscoveryThreadProc, nullptr, 0, nullptr);
    }
}
