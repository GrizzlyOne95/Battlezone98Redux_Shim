#include "frame_bridge_camera_observer.h"
#include <Windows.h>
#include <string>
#include "bzr_options_ui.h"
#include "openshim_preset_migration.h"
#include "shim_log.h"
#include <cstring>
#include <atomic>

namespace BZROpenShim::FrameBridge
{
    namespace
    {
        struct Api
        {
            void* (__cdecl* root)() = nullptr;
            void* (__thiscall* renderer)(void*) = nullptr;
            void* (__thiscall* rendererByName)(void*, const std::string&) = nullptr;
            void* (__thiscall* viewport)(void*) = nullptr;
            void* (__thiscall* camera)(void*) = nullptr;
            int (__thiscall* width)(void*) = nullptr;
            int (__thiscall* height)(void*) = nullptr;
            const float* (__thiscall* view)(void*, bool) = nullptr;
            const float* (__thiscall* projection)(void*) = nullptr;
            float (__thiscall* nearClip)(void*) = nullptr;
            float (__thiscall* farClip)(void*) = nullptr;
            const std::string& (__thiscall* name)(void*) = nullptr;
        };
        template<class T> bool Bind(HMODULE module, T& target, const char* name)
        {
            target = reinterpret_cast<T>(GetProcAddress(module, name));
            return target != nullptr;
        }
        bool Resolve(Api& api)
        {
            const HMODULE module = GetModuleHandleW(L"OgreMain.dll");
            if (!module) return false;
            return Bind(module, api.root, "?getSingletonPtr@Root@Ogre@@SAPAV12@XZ") &&
                Bind(module, api.renderer, "?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ") &&
                Bind(module, api.rendererByName, "?getRenderSystemByName@Root@Ogre@@QAEPAVRenderSystem@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z") &&
                Bind(module, api.viewport, "?_getViewport@RenderSystem@Ogre@@UAEPAVViewport@2@XZ") &&
                Bind(module, api.camera, "?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ") &&
                Bind(module, api.width, "?getActualWidth@Viewport@Ogre@@QBEHXZ") &&
                Bind(module, api.height, "?getActualHeight@Viewport@Ogre@@QBEHXZ") &&
                Bind(module, api.view, "?getViewMatrix@Camera@Ogre@@QBEABVMatrix4@2@_N@Z") &&
                Bind(module, api.projection, "?getProjectionMatrixWithRSDepth@Frustum@Ogre@@UBEABVMatrix4@2@XZ") &&
                Bind(module, api.nearClip, "?getNearClipDistance@Camera@Ogre@@UBEMXZ") &&
                Bind(module, api.farClip, "?getFarClipDistance@Camera@Ogre@@UBEMXZ") &&
                Bind(module, api.name, "?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        }
        bool GuardedRead(const Api& api, const std::string& dx11Name, CameraSnapshot& snapshot)
        {
            // Plain locals only; no C++ unwind objects in the SEH scope.
            __try
            {
                void* root = api.root();
                if (!root) return false;
                void* renderer = api.renderer(root);
                if (!renderer || renderer != api.rendererByName(root, dx11Name)) return false;
                void* viewport = api.viewport(renderer);
                if (!viewport) return false;
                void* camera = api.camera(viewport);
                const int width = api.width(viewport), height = api.height(viewport);
                if (!camera || width <= 0 || height <= 0 || width > 8192 || height > 8192) return false;
                snapshot.width = static_cast<std::uint32_t>(width);
                snapshot.height = static_cast<std::uint32_t>(height);
                snapshot.cameraIdentity = reinterpret_cast<std::uintptr_t>(camera);
                // Match the camera baseline used by AutoParamDataSource. Its
                // renderable overrides, camera-relative transforms and target
                // flipping still require separate draw-level qualification.
                const float* view = api.view(camera, true);
                const float* projection = api.projection(camera);
                if (!view || !projection) return false;
                for (unsigned i = 0; i < 16; ++i) { snapshot.view[i] = view[i]; snapshot.projection[i] = projection[i]; }
                snapshot.nearClip = api.nearClip(camera);
                snapshot.farClip = api.farClip(camera);
                const std::string& name = api.name(camera);
                const auto length = name.size() < 63 ? name.size() : 63;
                for (std::size_t i = 0; i < length; ++i)
                {
                    // Keep wire names printable and JSON-safe, including on
                    // builds with unusual camera names. No string crosses ABI.
                    const char value = name.data()[i];
                    snapshot.name[i] = value >= 32 && value <= 126 && value != '"' && value != '\\' ? value : '_';
                }
                LARGE_INTEGER qpc{};
                QueryPerformanceCounter(&qpc);
                snapshot.observationQpc = qpc.QuadPart;
                snapshot.status = static_cast<std::uint32_t>(CameraStatus::Observed);
                snapshot.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::CameraForShaders);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }
    }
    bool ObserveViewportCamera(CameraSnapshot& snapshot)
    {
        snapshot = {};
        // Only called under the frame producer's render-thread mutex. Retry
        // missing exports, but never inspect native object field offsets.
        static Api api;
        static bool ready = false;
        if (!ready) ready = Resolve(api);
        static const std::string dx11Name("Direct3D11 Rendering Subsystem");
        if (!ready || !GuardedRead(api, dx11Name, snapshot)) { snapshot = {}; return false; }
        if (!ValidCameraSnapshot(snapshot))
        {
            snapshot = {};
            snapshot.status = static_cast<std::uint32_t>(CameraStatus::Invalid);
            return false;
        }
        return true;
    }

    namespace
    {
        using ParameterMatrix = const float*(__thiscall*)(void*);
        InlineDetour32 overlayViewDetour{}, overlayProjectionDetour{};
        void* volatile parameterView = nullptr;
        void* volatile parameterProjection = nullptr;
        ParameterMatrix ParameterFunction(void* volatile& slot)
        { return reinterpret_cast<ParameterMatrix>(InterlockedCompareExchangePointer(&slot, nullptr, nullptr)); }
        std::atomic<void(*)(bool)> overlayNotify{nullptr};
        thread_local bool checkingOverlay = false;
        bool GuardedOverlayMatch(void* source)
        {
            __try { return IdentityOverlayMatrices(ParameterFunction(parameterView)(source), ParameterFunction(parameterProjection)(source)); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }
        void MaybeOverlay(void* source)
        {
            const auto notify = overlayNotify.load(std::memory_order_acquire);
            if (!notify || checkingOverlay) return;
            checkingOverlay = true;
            notify(GuardedOverlayMatch(source));
            checkingOverlay = false;
        }
        const float* __fastcall OverlayView(void* source, void*)
        {
            const float* result = ParameterFunction(parameterView)(source);
            MaybeOverlay(source); return result;
        }
        const float* __fastcall OverlayProjection(void* source, void*)
        {
            const float* result = ParameterFunction(parameterProjection)(source);
            MaybeOverlay(source); return result;
        }
        std::uint8_t* OverlayExportBody(HMODULE module, const char* name)
        {
            auto* body = reinterpret_cast<std::uint8_t*>(GetProcAddress(module, name));
            const auto base = reinterpret_cast<std::uintptr_t>(module);
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(module);
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
            const std::size_t size = nt->OptionalHeader.SizeOfImage;
            const auto inModule = [base, size](const std::uint8_t* address) {
                const auto va = reinterpret_cast<std::uintptr_t>(address);
                return va >= base && va - base <= size && size - (va - base) >= 16;
            };
            for (unsigned i = 0; inModule(body) && body[0] == 0xE9 && i < 4; ++i)
            {
                std::int32_t relative{}; std::memcpy(&relative, body + 1, sizeof(relative)); body += 5 + relative;
            }
            return inModule(body) && body[0] != 0xE9 ? body : nullptr;
        }
    }
    bool InstallIdentityOverlayObserver(void(*notify)(bool))
    {
        static bool attempted = false;
        if (attempted) return overlayNotify.load() != nullptr;
        HMODULE module = GetModuleHandleW(L"OgreMain.dll");
        if (!module || !notify) return false;
        attempted = true;
        wchar_t path[MAX_PATH]{};
        const DWORD length = GetModuleFileNameW(module, path, MAX_PATH);
        std::string hash;
        if (!length || length >= MAX_PATH || !TryComputeFileSha256Hex(std::filesystem::path(path), hash) ||
            hash != "e5e693960b95ad0d60733a3b688464a6c6cba234e86950698f9c2bea4acfeb45") return false;
        auto* view = OverlayExportBody(module, "?getViewMatrix@AutoParamDataSource@Ogre@@UBEABVMatrix4@2@XZ");
        auto* projection = OverlayExportBody(module, "?getProjectionMatrix@AutoParamDataSource@Ogre@@UBEABVMatrix4@2@XZ");
        const std::uint8_t viewBytes[] = {0x56,0x8B,0xF1,0x80,0xBE,0x51,0x4B,0,0,0};
        const std::uint8_t projectionBytes[] = {0x56,0x8B,0xF1,0x80,0xBE,0x52,0x4B,0,0,0};
        if (!view || !projection || !ExpectedBytesMatchAt(reinterpret_cast<std::uintptr_t>(view), viewBytes, sizeof(viewBytes)) ||
            !ExpectedBytesMatchAt(reinterpret_cast<std::uintptr_t>(projection), projectionBytes, sizeof(projectionBytes))) return false;
        if (!InstallInlineDetour32(overlayViewDetour, reinterpret_cast<std::uintptr_t>(view), reinterpret_cast<void*>(&OverlayView),
            sizeof(viewBytes), viewBytes, sizeof(viewBytes), &parameterView)) return false;
        if (!InstallInlineDetour32(overlayProjectionDetour, reinterpret_cast<std::uintptr_t>(projection), reinterpret_cast<void*>(&OverlayProjection),
            sizeof(projectionBytes), projectionBytes, sizeof(projectionBytes), &parameterProjection)) return false;
        overlayNotify.store(notify, std::memory_order_release);
        LogShimA(LogLevel::Info, "frame-bridge", "[FrameBridge] qualified identity overlay parameter observers installed; HUD coverage unqualified");
        return true;
    }
}
