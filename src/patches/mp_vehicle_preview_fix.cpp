#include "mp_vehicle_preview_fix.h"

#include "bzr_options_ui.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#include <windows.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "mppreview";

        // The render-globals structure the game keeps at a fixed address; the
        // same global supplies the SceneManager at +0x08 (bzr_hooks.cpp,
        // walker_cockpit_trace.cpp). The vehicle preview viewport is +0x24 --
        // established by reading it back live (a 512x512 target with visibility
        // mask 0x08, matching exactly what FUN_007A9590 configures) rather than
        // by offset arithmetic alone. +0x20 is the in-game sniper viewport and
        // is null on this screen.
        constexpr uintptr_t kPreferredImageBase = 0x00400000;
        constexpr uintptr_t kRenderGlobalsAddr = 0x00920EA0;
        constexpr uintptr_t kVehiclePreviewViewportOffset = 0x24;

        using FnViewportGetScheme = const std::string*(__thiscall*)(const void*);
        using FnViewportSetScheme = void(__thiscall*)(void*, const std::string&);

        FnViewportGetScheme g_GetMaterialScheme = nullptr;
        FnViewportSetScheme g_SetMaterialScheme = nullptr;

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ConfigLoaded{ false };
        std::atomic<bool> g_Resolved{ false };
        std::atomic<bool> g_ResolveFailed{ false };
        bool g_Logged = false;

        bool ResolveViewportApi()
        {
            if (g_Resolved.load(std::memory_order_acquire))
                return true;
            if (g_ResolveFailed.load(std::memory_order_acquire))
                return false;
            if (!OgreRuntime::IsLoaded())
                return false;

            g_GetMaterialScheme = reinterpret_cast<FnViewportGetScheme>(
                OgreRuntime::ResolveExport(
                    "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@"
                    "V?$allocator@D@2@@std@@XZ"));
            g_SetMaterialScheme = reinterpret_cast<FnViewportSetScheme>(
                OgreRuntime::ResolveExport(
                    "?setMaterialScheme@Viewport@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@"
                    "V?$allocator@D@2@@std@@@Z"));

            if (!g_GetMaterialScheme || !g_SetMaterialScheme)
            {
                g_ResolveFailed.store(true, std::memory_order_release);
                LogShimA(LogLevel::Warn, kComponent,
                         "[MPPREVIEW] Viewport material-scheme API unavailable "
                         "(get=%d set=%d); preview left stock",
                         g_GetMaterialScheme ? 1 : 0, g_SetMaterialScheme ? 1 : 0);
                return false;
            }
            g_Resolved.store(true, std::memory_order_release);
            return true;
        }

        // Keeps the player's quality family and only drops the shadow half, so
        // the preview still matches their settings.
        const char* NoShadowSchemeFor(const char* current)
        {
            // The measured case: no scheme was ever set on this viewport, so it
            // holds Ogre's default and the material falls back to its first
            // technique -- BZBase.material's "high-pssm".
            if (!current || !*current ||
                std::strcmp(current, "Default") == 0 ||
                std::strcmp(current, "ShaderGeneratorDefaultScheme") == 0)
            {
                return "high-noshadow";
            }
            if (std::strncmp(current, "lowest", 6) == 0)
                return "lowest-noshadow";
            if (std::strncmp(current, "low", 3) == 0)
                return "low-noshadow";
            if (std::strncmp(current, "medium", 6) == 0)
                return "medium-noshadow";
            if (std::strncmp(current, "high", 4) == 0)
                return "high-noshadow";
            // A Workshop or Enhanced scheme we do not recognise: leave it be
            // rather than forcing it onto a stock technique.
            return nullptr;
        }

        // Engine-owned memory can be torn down between frames, and /EHsc means
        // a C++ catch would not cover an access violation -- hence __try. The
        // std::string lives outside these frames because MSVC refuses __try in
        // a function that requires object unwinding.
        bool ReadCurrentScheme(const void* viewport, char* out, size_t capacity)
        {
            __try
            {
                const std::string* const current = g_GetMaterialScheme(viewport);
                if (!current)
                    return false;
                _snprintf_s(out, capacity, _TRUNCATE, "%s", current->c_str());
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool WriteScheme(const void* viewport, const std::string& scheme)
        {
            __try
            {
                g_SetMaterialScheme(const_cast<void*>(viewport), scheme);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        const void* ReadPreviewViewport()
        {
            const uintptr_t mainBase =
                reinterpret_cast<uintptr_t>(::GetModuleHandleW(nullptr));
            if (!mainBase)
                return nullptr;
            const uintptr_t globalsSlot =
                mainBase + (kRenderGlobalsAddr - kPreferredImageBase);

            __try
            {
                const uintptr_t globals =
                    *reinterpret_cast<const uintptr_t*>(globalsSlot);
                if (!globals)
                    return nullptr;
                return *reinterpret_cast<void* const*>(
                    globals + kVehiclePreviewViewportOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }
    }

    void MpVehiclePreviewFixTick()
    {
        if (!g_ConfigLoaded.exchange(true, std::memory_order_acq_rel))
        {
            bool enabled = true;
            TryGetUserConfigBool("Fixes", "MpVehiclePreviewShadowScheme", enabled);
            g_Enabled.store(enabled, std::memory_order_release);
        }
        if (!g_Enabled.load(std::memory_order_acquire))
            return;
        if (!ResolveViewportApi())
            return;

        // Every frame the preview exists: the screen re-creates the viewport
        // when it opens, and the stock settings loop can reassert a scheme.
        const void* const viewport = ReadPreviewViewport();
        if (!viewport)
            return;

        char current[64] = {};
        if (!ReadCurrentScheme(viewport, current, sizeof(current)))
            return;
        if (std::strstr(current, "noshadow") != nullptr)
            return;

        const char* const wanted = NoShadowSchemeFor(current);
        if (!wanted)
            return;

        const std::string scheme(wanted);
        if (!WriteScheme(viewport, scheme))
            return;

        if (!g_Logged)
        {
            g_Logged = true;
            LogShimA(LogLevel::Info, kComponent,
                     "[MPPREVIEW] vehicle preview scheme '%hs' -> '%hs' "
                     "(a PSSM technique on a viewport with shadows disabled "
                     "reads NaN shadow matrices and blanks the panel)",
                     current, wanted);
        }
    }
}
