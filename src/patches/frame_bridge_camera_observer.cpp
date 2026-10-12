#include "frame_bridge_camera_observer.h"
#include <Windows.h>
#include <string>

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
            const float* (__thiscall* view)(void*) = nullptr;
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
                Bind(module, api.view, "?getViewMatrix@Camera@Ogre@@UBEABVMatrix4@2@XZ") &&
                Bind(module, api.projection, "?getProjectionMatrixRS@Frustum@Ogre@@UBEABVMatrix4@2@XZ") &&
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
                const float* view = api.view(camera);
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
}
