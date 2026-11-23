// DX11: make Alt-Enter from a window reach fullscreen, and keep the swap-chain
// buffers at the window size after setFullscreen.
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
// What: the setFullscreen entry of the D3D11RenderWindowHwnd vtable is wrapped.
// The first call resizes the window (and may lose the flag). On the known
// renderer build the original is called again only when the flag (+0xa8) no
// longer matches the request (on other builds, always): the second call finds
// the window already at the right size, so nothing resizes and the flag it
// stores survives.
//
// Buffer resync: setFullscreen stamps mWidth/mHeight (+0x20/+0x24) with the
// requested size before it moves the window, so a resize it triggers can leave
// the swap-chain buffers at an older size while windowMovedOrResized sees
// "client == mWidth/mHeight" and never resizes them again. Seen with Options >
// Apply, which calls setFullscreen(false, w-1, h-1) then (true, w, h): at
// 3840x2160 the buffers stayed about 3863x2216 and the shell drew ~1.006 x
// 1.026 too big, clipped at the right and bottom. So after the calls the
// client rect of the window (+0x148) is compared with the buffer size the
// swap chain (+0xd8) reports (GetDesc); if they differ, the exported
// _resizeSwapChainBuffers (0x100048f9) is called with the client size. That
// function re-reads the desc and resets the flag from desc.Windowed, so the
// flag and the stored desc.Windowed (+0x10c) are put back to what
// setFullscreen left; the fullscreen state switch itself still happens in
// _finishSwitchingFullscreen on the next frame (which reads only the stored
// width/height of the desc copy, now the client size, and its own GetDesc).
// The extra ResizeBuffers carries the same failure modes as the one stock runs
// from WM_SIZE: device loss goes to handleDeviceLost, other failures throw an
// Ogre exception through this hook to setFullscreen's caller.
//
// Fail closed: the slot is found by comparing the DLL's exported vtable with
// its exported setFullscreen; no match means nothing is patched. Reading the
// flag and the resync need the renderer build the offsets were read from
// (TimeDateStamp 0x586F03D3, SizeOfImage 0xF3000, GOG and Steam), and the
// resync also needs the _resizeSwapChainBuffers export; without them the
// wrapper always calls setFullscreen twice and does not resync.
//
// Kill switch: OPENSHIM_DISABLE_D3D11_FULLSCREEN_FIX=1 (stock behaviour).
#include "bool_token.h"
#include "com_vtable_patch.h"
#include "d3d11_fullscreen_toggle.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>
#include <cstdint>
#include <dxgi.h>
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
        constexpr const char* kResizeBuffersExport =
            "?_resizeSwapChainBuffers@D3D11RenderWindowSwapChainBased@Ogre@@IAEXII@Z";

        // Layout of the renderer build these offsets were read from.
        constexpr DWORD kRendererTimeDateStamp = 0x586F03D3;
        constexpr DWORD kRendererSizeOfImage = 0xF3000;
        constexpr size_t kOffsetIsFullScreen = 0xa8;   // bool mIsFullScreen
        constexpr size_t kOffsetSwapChain = 0xd8;      // IDXGISwapChain*
        constexpr size_t kOffsetDescWindowed = 0x10c;  // stored DXGI_SWAP_CHAIN_DESC.Windowed
        constexpr size_t kOffsetHwnd = 0x148;          // HWND

        // __thiscall as __fastcall: ecx = this, edx unused, callee pops the rest.
        using FnSetFullscreen = void(__fastcall*)(void* self, void* edx, bool fullScreen, unsigned width,
                                                  unsigned height);
        using FnResizeBuffers = void(__fastcall*)(void* self, void* edx, unsigned width, unsigned height);
        FnSetFullscreen g_RealSetFullscreen = nullptr;
        FnResizeBuffers g_ResizeBuffers = nullptr;  // null: resync not available
        bool g_LayoutKnown = false;                 // offsets above match this renderer build
        uintptr_t g_DiscoveryThread = 0;
        int g_LastResyncDecision = -1;  // 0 in sync, 1 resynced, 2 skipped; render thread only

        template <typename T> T& Field(void* self, size_t offset)
        {
            return *reinterpret_cast<T*>(static_cast<uint8_t*>(self) + offset);
        }

        bool IsKnownRenderer(HMODULE renderer)
        {
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(renderer);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            const auto* nt =
                reinterpret_cast<const IMAGE_NT_HEADERS32*>(reinterpret_cast<const uint8_t*>(renderer) + dos->e_lfanew);
            return nt->Signature == IMAGE_NT_SIGNATURE && nt->FileHeader.TimeDateStamp == kRendererTimeDateStamp &&
                   nt->OptionalHeader.SizeOfImage == kRendererSizeOfImage;
        }

        // "In sync" and "skipped" log on change only; a resync always logs (it
        // only happens on a real mismatch, after a user action).
        void LogResyncDecision(int decision, const char* fmt, unsigned a, unsigned b, unsigned c, unsigned d)
        {
            if (decision == g_LastResyncDecision && decision != 1)
                return;
            g_LastResyncDecision = decision;
            LogShimA(LogLevel::Info, kComponent, fmt, a, b, c, d);
        }

        // Resize the swap-chain buffers to the window's client size when a
        // setFullscreen call left them at an older size.
        void ResyncBuffers(void* self)
        {
            if (!g_ResizeBuffers)
                return;
            HWND hwnd = Field<HWND>(self, kOffsetHwnd);
            auto* chain = Field<IDXGISwapChain*>(self, kOffsetSwapChain);
            RECT client = {};
            if (!chain || !hwnd || !IsWindow(hwnd) || IsIconic(hwnd) || !GetClientRect(hwnd, &client))
                return;
            DXGI_SWAP_CHAIN_DESC desc = {};
            if (FAILED(chain->GetDesc(&desc)))
                return;
            const unsigned clientW = static_cast<unsigned>(client.right - client.left);
            const unsigned clientH = static_cast<unsigned>(client.bottom - client.top);
            if (clientW == desc.BufferDesc.Width && clientH == desc.BufferDesc.Height)
            {
                LogResyncDecision(0, "[DX11 Fullscreen] buffers match the client area (%ux%u = %ux%u)", clientW,
                                  clientH, desc.BufferDesc.Width, desc.BufferDesc.Height);
                return;
            }
            if (clientW == 0 || clientH == 0)
            {
                LogResyncDecision(2, "[DX11 Fullscreen] buffer resync skipped: client %ux%u, buffers %ux%u", clientW,
                                  clientH, desc.BufferDesc.Width, desc.BufferDesc.Height);
                return;
            }
            // _resizeSwapChainBuffers resets these from GetDesc; keep what
            // setFullscreen stored so the pending state switch still runs.
            const bool isFullScreen = Field<bool>(self, kOffsetIsFullScreen);
            const BOOL descWindowed = Field<BOOL>(self, kOffsetDescWindowed);
            g_ResizeBuffers(self, nullptr, clientW, clientH);
            Field<bool>(self, kOffsetIsFullScreen) = isFullScreen;
            Field<BOOL>(self, kOffsetDescWindowed) = descWindowed;
            LogResyncDecision(1, "[DX11 Fullscreen] buffers %ux%u resized to the client area %ux%u",
                              desc.BufferDesc.Width, desc.BufferDesc.Height, clientW, clientH);
        }

        void __fastcall HookSetFullscreen(void* self, void* edx, bool fullScreen, unsigned width, unsigned height)
        {
            g_RealSetFullscreen(self, edx, fullScreen, width, height);
            const bool repeated = !g_LayoutKnown || Field<bool>(self, kOffsetIsFullScreen) != fullScreen;
            if (repeated)
                g_RealSetFullscreen(self, edx, fullScreen, width, height);
            LogShimA(LogLevel::Info, kComponent, "[DX11 Fullscreen] setFullscreen(%s, %ux%u) applied %s",
                     fullScreen ? "fullscreen" : "windowed", width, height, repeated ? "twice" : "once");
            ResyncBuffers(self);
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
            g_LayoutKnown = IsKnownRenderer(renderer);
            void* resize = reinterpret_cast<void*>(GetProcAddress(renderer, kResizeBuffersExport));
            if (resize && g_LayoutKnown)
                g_ResizeBuffers = reinterpret_cast<FnResizeBuffers>(resize);
            else
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Fullscreen] %s; setFullscreen always applied twice, swap-chain buffer resync not installed",
                         g_LayoutKnown ? "renderer does not export _resizeSwapChainBuffers" : "unknown renderer build");
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
