// OpenShim-owned renderer-profile runtime.
//
// Ownership model (see Docs/OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md):
//   OpenShim  - renderer capability/policy state, scheme policy application,
//               user settings persistence, capability reporting.
//   EXU       - content intent; forwards requests over the optional winmm
//               bridge and mirrors the ABI in its own OpenShimBridge.h.
//   CR        - art direction; requests profiles where its content wants them.
//
// The viewport-scheme takeover intentionally replicates the mechanism proven
// by ExtraUtilities' Environment module (IAT slot 0x00869810 =
// Ogre::Viewport::setMaterialScheme; call sites 0x00681585 = the exe's ~1 Hz
// graphics-settings reassert loop, 0x00682AA0/0x00682EA7 = secondary/tertiary
// viewport creation with the literal "low-noshadow" scheme). Identity evidence
// for every address is verified at install time: each site must begin with
// FF 15 <exactly the IAT displacement> or the takeover is skipped whole and
// Enhanced/Retro report themselves unavailable rather than half-working.

#include "render_profile_runtime.h"
#include "BZROpenShim.h"
#include "bzr_options_ui.h"
#include "render_profile.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <process.h>

#include <atomic>
#include <cstring>
#include <filesystem>
#include <string>

namespace BZROpenShim::RenderProfiles
{
    namespace
    {
        constexpr const char* kLogTag = "RENDER";

        // Compiled expectation for the deployed renderer-resource set. Bump
        // whenever resources/renderer/** changes in a way that must not pair
        // with an older DLL. Deploy-OpenShim.ps1 writes the matching file;
        // a mismatch degrades Enhanced cleanly to Redux instead of letting a
        // new DLL run against stale shaders (the winmm.dll+patches.json rule,
        // extended to renderer resources).
        constexpr char kEnhancedResourcesVersion[] = "1";
        constexpr const char* kEnhancedResourceDirRel = "openshim\\renderer\\enhanced";
        constexpr const char* kEnhancedResourceVersionFile = "resources.version";

        void __fastcall ViewportSetMaterialSchemeHookForward(void* viewport,
                                                             void* edx,
                                                             const std::string* scheme);

        // ---- process state (guarded by s_stateLock) -----------------------
        SRWLOCK s_stateLock = SRWLOCK_INIT;

        RendererBackend s_requestedBackend = RendererBackend::Auto;
        ActiveBackend s_detectedBackend = ActiveBackend::DX9;
        bool s_backendDetected = false;
        Profile s_userProfile = Profile::Redux;
        ContentRequest s_contentRequest = ContentRequest::Inherit;
        bool s_contentOverridePresent = false;
        ResolverResult s_effective {};
        uint32_t s_capabilityMask = 0;
        bool s_resourcesValid = false;

        // Lock-free read path for the render-thread scheme hook.
        std::atomic<uint8_t> s_effectiveProfileAtomic {
            static_cast<uint8_t>(Profile::Redux) };
        std::atomic<bool> s_schemeTakeoverInstalled { false };

        const char* BackendName(ActiveBackend backend)
        {
            return backend == ActiveBackend::DX11 ? "DX11" : "DX9";
        }

        const char* ProfileName(Profile profile)
        {
            switch (profile)
            {
            case Profile::Enhanced: return "Enhanced";
            case Profile::Retro: return "Retro";
            default: return "Redux";
            }
        }

        // ---- openshim.ini persistence --------------------------------------

        bool EqualsNoCase(const char* a, const char* b)
        {
            return _stricmp(a, b) == 0;
        }

        bool ParseBackendText(const char* text, RendererBackend& out)
        {
            if (EqualsNoCase(text, "auto") || EqualsNoCase(text, "default"))
            {
                out = RendererBackend::Auto;
                return true;
            }
            if (EqualsNoCase(text, "dx9") || EqualsNoCase(text, "d3d9") ||
                EqualsNoCase(text, "directx9"))
            {
                out = RendererBackend::DX9;
                return true;
            }
            if (EqualsNoCase(text, "dx11") || EqualsNoCase(text, "d3d11") ||
                EqualsNoCase(text, "directx11"))
            {
                out = RendererBackend::DX11;
                return true;
            }
            return false;
        }

        bool ParseProfileText(const char* text, Profile& out)
        {
            if (EqualsNoCase(text, "redux") || EqualsNoCase(text, "default") ||
                EqualsNoCase(text, "modern"))
            {
                out = Profile::Redux;
                return true;
            }
            if (EqualsNoCase(text, "enhanced") || EqualsNoCase(text, "en"))
            {
                out = Profile::Enhanced;
                return true;
            }
            if (EqualsNoCase(text, "retro") || EqualsNoCase(text, "og") ||
                EqualsNoCase(text, "classic"))
            {
                out = Profile::Retro;
                return true;
            }
            return false;
        }

        void LoadConfigLocked()
        {
            std::string value;
            if (TryGetUserConfigString("Graphics", "Renderer", value))
            {
                RendererBackend parsed;
                if (ParseBackendText(TrimAsciiCopy(value).c_str(), parsed))
                {
                    s_requestedBackend = parsed;
                }
            }
            if (TryGetUserConfigString("Graphics", "RenderProfile", value))
            {
                Profile parsed;
                if (ParseProfileText(TrimAsciiCopy(value).c_str(), parsed))
                {
                    s_userProfile = parsed;
                }
            }
        }

        // ---- deployed Enhanced renderer-resource validation -----------------

        bool ValidateDeployedResourceSet()
        {
            const std::filesystem::path gameDir = GetMainModuleDirectory();
            if (gameDir.empty())
            {
                return false;
            }

            const std::filesystem::path dir = gameDir / kEnhancedResourceDirRel;
            if (!std::filesystem::is_directory(dir))
            {
                LogShimA(LogLevel::Info, kLogTag,
                         "Enhanced resource set absent (%s); standalone retrofit path disabled",
                         kEnhancedResourceDirRel);
                return false;
            }

            FILE* file = nullptr;
            const std::filesystem::path versionFile = dir / kEnhancedResourceVersionFile;
            if (_wfopen_s(&file, versionFile.c_str(), L"rb") != 0 || file == nullptr)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "Enhanced resource set missing %s marker", kEnhancedResourceVersionFile);
                return false;
            }

            char actual[32] = {};
            const size_t read = fread(actual, 1, sizeof(actual) - 1, file);
            fclose(file);

            if (read == 0 || strncmp(actual, kEnhancedResourcesVersion, read) != 0)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "Enhanced unavailable: resource version mismatch "
                         "(expected=%s got=%.31s); redeploy winmm.dll + openshim\\renderer together",
                         kEnhancedResourcesVersion, actual);
                return false;
            }

            LogShimA(LogLevel::Info, kLogTag,
                     "resource-version=%s resources compatible=yes",
                     kEnhancedResourcesVersion);
            return true;
        }

        // ---- resolution + diagnostics ----------------------------------------

        uint32_t ComposeCapabilityMaskLocked()
        {
            uint32_t mask = CapabilitiesForBackend(s_detectedBackend);
            if (!s_schemeTakeoverInstalled.load(std::memory_order_acquire))
            {
                mask &= ~static_cast<uint32_t>(CapSchemeRewrite);
            }
            if (s_resourcesValid)
            {
                mask |= static_cast<uint32_t>(CapIblResources);
            }
            else
            {
                mask &= ~static_cast<uint32_t>(CapIblResources);
            }
            return mask;
        }

        const char* ContentRequestName(ContentRequest request)
        {
            switch (request)
            {
            case ContentRequest::Retro: return "Retro";
            case ContentRequest::Redux: return "Redux";
            case ContentRequest::Enhanced: return "Enhanced";
            default: return "Inherit";
            }
        }

        void EmitDiagnosticsLocked()
        {
            static ResolverResult s_lastReported {};
            static uint32_t s_lastMask = 0;
            static bool s_haveLast = false;

            if (s_haveLast &&
                s_lastReported.effectiveProfile == s_effective.effectiveProfile &&
                s_lastReported.fellBack == s_effective.fellBack &&
                s_lastMask == s_capabilityMask &&
                strcmp(s_lastReported.reason, s_effective.reason) == 0)
            {
                return;
            }

            s_lastReported = s_effective;
            s_lastMask = s_capabilityMask;
            s_haveLast = true;

            const char* requestedName =
                s_requestedBackend == RendererBackend::DX11 ? "DX11"
                : s_requestedBackend == RendererBackend::DX9 ? "DX9"
                                                             : "Auto";

            LogShimA(LogLevel::Info, kLogTag,
                     "backend.requested=%s backend.effective=%s",
                     requestedName, BackendName(s_effective.effectiveBackend));
            LogShimA(LogLevel::Info, kLogTag,
                     "profile.user=%s profile.content=%s profile.effective=%s profile.source=%s",
                     ProfileName(s_userProfile),
                     s_contentOverridePresent ? ContentRequestName(s_contentRequest) : "Inherit",
                     ProfileName(s_effective.effectiveProfile),
                     (s_contentOverridePresent && s_contentRequest != ContentRequest::Inherit)
                         ? "EXU" : "user");
            LogShimA(LogLevel::Info, kLogTag,
                     "enhanced.supported=%s resources.compatible=%s capabilities=0x%08X",
                     HasCapability(s_capabilityMask, CapSchemeRewrite) ? "yes" : "no",
                     s_resourcesValid ? "yes" : "no",
                     s_capabilityMask);
            LogShimA(LogLevel::Info, kLogTag,
                     "enhanced.sharpening=%s enhanced.linearLighting=%s enhanced.pssm=%s "
                     "enhanced.lightSelection=%s",
                     HasCapability(s_capabilityMask, CapNormalSharpening) ? "yes" : "no",
                     HasCapability(s_capabilityMask, CapLinearLighting) ? "yes" : "no",
                     HasCapability(s_capabilityMask, CapModernPssm) ? "yes" : "no",
                     HasCapability(s_capabilityMask, CapLightSelection) ? "yes" : "no");

            if (s_effective.fellBack && s_effective.reason[0] != '\0')
            {
                LogShimA(LogLevel::Warn, kLogTag, "fallback=%s", s_effective.reason);
            }
        }

        void ResolveAndPublishLocked(const char* context)
        {
            s_capabilityMask = ComposeCapabilityMaskLocked();

            ResolverInput input;
            input.requestedBackend = s_requestedBackend;
            input.detectedBackend = s_detectedBackend;
            input.userProfile = s_userProfile;
            input.contentOverridePresent = s_contentOverridePresent;
            input.contentOverride = s_contentRequest;
            input.capabilityMask = s_capabilityMask;

            const Profile previous = s_effective.effectiveProfile;
            const bool previousFallBack = s_effective.fellBack;

            s_effective = ResolveRenderProfile(input);
            s_effectiveProfileAtomic.store(
                static_cast<uint8_t>(s_effective.effectiveProfile),
                std::memory_order_release);

            if (previous != s_effective.effectiveProfile ||
                previousFallBack != s_effective.fellBack)
            {
                LogShimA(LogLevel::Info, kLogTag,
                         "resolved (%s): effective=%s",
                         context != nullptr ? context : "?",
                         ProfileName(s_effective.effectiveProfile));
            }
            EmitDiagnosticsLocked();
        }

        // ---- backend observation --------------------------------------------

        unsigned __stdcall BackendObservationThread(void*)
        {
            // Watch which render system the engine actually loads.
            constexpr DWORD pollMs = 250;
            constexpr DWORD timeoutMs = 60000;
            DWORD waited = 0;
            bool decided = false;
            bool dx11 = false;

            while (waited < timeoutMs)
            {
                if (GetModuleHandleA("RenderSystem_Direct3D11.dll") != nullptr)
                {
                    dx11 = true;
                    decided = true;
                    break;
                }
                if (GetModuleHandleA("RenderSystem_Direct3D9.dll") != nullptr)
                {
                    dx11 = false;
                    decided = true;
                    break;
                }
                Sleep(pollMs);
                waited += pollMs;
            }

            if (!decided)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend detection timed out after %lu ms; conservative DX9 assumptions stay active",
                         static_cast<unsigned long>(timeoutMs));
                return 0;
            }

            AcquireSRWLockExclusive(&s_stateLock);
            s_detectedBackend = dx11 ? ActiveBackend::DX11 : ActiveBackend::DX9;
            s_backendDetected = true;
            ResolveAndPublishLocked("backend observed");
            ReleaseSRWLockExclusive(&s_stateLock);
            return 0;
        }

        // ---- viewport scheme takeover ----------------------------------------

        using FnViewportSetMaterialScheme = void (__thiscall*)(void*, const std::string&);

        // Identity: IAT thunk of Ogre::Viewport::setMaterialScheme(const String&)
        // in battlezone98redux.exe 2.2.301, cross-checked against ExtraUtilities
        // Environment.cpp kViewportSetMaterialSchemeIat (independently shipped,
        // field-tested there, and byte-verified here before any write).
        constexpr uintptr_t kViewportSetMaterialSchemeIat = 0x00869810;

        struct SchemeCallSite
        {
            uintptr_t address;
            const char* identity;
        };

        constexpr SchemeCallSite kSchemeCallSites[] = {
            { 0x00681585, "settings reassert loop over all viewports" },
            { 0x00682AA0, "secondary viewport creation ('low-noshadow')" },
            { 0x00682EA7, "tertiary viewport creation ('low-noshadow')" },
        };

        // The patched instruction becomes `call [s_hookTrampolinePtr]`; the
        // cell and the function it names must outlive the process (namespace
        // scope both).
        void* s_hookTrampolinePtr =
            reinterpret_cast<void*>(&ViewportSetMaterialSchemeHookForward);

        FnViewportSetMaterialScheme OriginalSetMaterialSchemeFromIat()
        {
            return *reinterpret_cast<FnViewportSetMaterialScheme*>(
                kViewportSetMaterialSchemeIat);
        }

        // Tracks the engine's modern base so prefixed schemes keep resolving to
        // a sane quality level across switches. Written on the render thread by
        // the hook; read best-effort elsewhere (matches EXU's proven behavior).
        char (&LastModernBaseStorage())[32]
        {
            static char storage[32] = "high-pssm";
            return storage;
        }

        std::string_view LastModernBase()
        {
            return std::string_view(LastModernBaseStorage());
        }

        void RememberModernBase(std::string_view modern)
        {
            char (&storage)[32] = LastModernBaseStorage();
            if (modern.size() < sizeof(storage))
            {
                std::memcpy(storage, modern.data(), modern.size());
                storage[modern.size()] = '\0';
            }
        }

        void __fastcall ViewportSetMaterialSchemeHookImpl(void* viewport,
                                                          void* /*edx*/,
                                                          const std::string* scheme)
        {
            const FnViewportSetMaterialScheme original = OriginalSetMaterialSchemeFromIat();

            const std::string_view incoming =
                (scheme != nullptr) ? std::string_view(*scheme) : std::string_view();

            if (IsModernMaterialScheme(incoming))
            {
                RememberModernBase(incoming);
            }

            const Profile effective = static_cast<Profile>(
                s_effectiveProfileAtomic.load(std::memory_order_acquire));

            bool rewritten = false;
            std::string finalScheme;

            if ((effective == Profile::Enhanced || effective == Profile::Retro) &&
                !incoming.empty())
            {
                // Fail open: foreign/custom schemes pass through untouched so
                // Workshop material scripts keep their own technique selection.
                // Only engine-native modern bases and our own prefixes carry
                // the policy prefix.
                const bool oursOrNative =
                    IsModernMaterialScheme(incoming) ||
                    incoming.starts_with("en-") ||
                    incoming.starts_with("og-");
                if (oursOrNative)
                {
                    const std::string_view modernBase =
                        NormalizeModernMaterialScheme(incoming, LastModernBase());
                    char buffer[48] = {};
                    if (BuildMaterialSchemeForProfile(effective, modernBase,
                                                      buffer, sizeof(buffer)))
                    {
                        finalScheme.assign(buffer);
                        rewritten = (finalScheme != incoming);
                    }
                }
            }

            if (original != nullptr)
            {
                if (rewritten)
                {
                    original(viewport, finalScheme);
                }
                else if (scheme != nullptr)
                {
                    original(viewport, *scheme);
                }
                else
                {
                    original(viewport, std::string());
                }
            }
        }

        void __fastcall ViewportSetMaterialSchemeHookForward(void* viewport,
                                                             void* edx,
                                                             const std::string* scheme)
        {
            ViewportSetMaterialSchemeHookImpl(viewport, edx, scheme);
        }

        bool InstallSchemeTakeover()
        {
            if (s_schemeTakeoverInstalled.load(std::memory_order_acquire))
            {
                return true;
            }

            // Verify every site before writing anything: a partially applied
            // takeover would be worse than none.
            for (const SchemeCallSite& site : kSchemeCallSites)
            {
                uint8_t bytes[6] = {};
                SIZE_T read = 0;
                if (!ReadProcessMemory(GetCurrentProcess(),
                                       reinterpret_cast<const void*>(site.address),
                                       bytes, sizeof(bytes), &read) ||
                    read != sizeof(bytes))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "scheme takeover skipped: unreadable call site 0x%08X (%s)",
                             static_cast<uint32_t>(site.address), site.identity);
                    return false;
                }
                const uint32_t disp = *reinterpret_cast<const uint32_t*>(bytes + 2);
                const uint32_t expectedDisp =
                    static_cast<uint32_t>(kViewportSetMaterialSchemeIat);
                if (bytes[0] != 0xFF || bytes[1] != 0x15 || disp != expectedDisp)
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "scheme takeover skipped: identity mismatch at 0x%08X "
                             "(%02X %02X disp=0x%08X expected=0x%08X) %s",
                             static_cast<uint32_t>(site.address),
                             bytes[0], bytes[1], disp, expectedDisp, site.identity);
                    return false;
                }
            }

            const void* operandValue =
                reinterpret_cast<const void*>(&s_hookTrampolinePtr);

            for (const SchemeCallSite& site : kSchemeCallSites)
            {
                DWORD oldProtect = 0;
                uint8_t* target = reinterpret_cast<uint8_t*>(site.address);
                if (!VirtualProtect(target, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "scheme takeover skipped: VirtualProtect failed at 0x%08X err=%lu",
                             static_cast<uint32_t>(site.address),
                             static_cast<unsigned long>(GetLastError()));
                    return false;
                }
                // Keep FF 15; replace only the displacement so the instruction
                // calls through our pointer cell instead of the import table.
                // The IAT entry stays pristine and remains how we invoke the
                // real function from inside the hook.
                std::memcpy(target + 2, &operandValue, sizeof(operandValue));
                DWORD ignored = 0;
                VirtualProtect(target, 6, oldProtect, &ignored);
                LogShimA(LogLevel::Info, kLogTag,
                         "scheme takeover installed at 0x%08X (%s)",
                         static_cast<uint32_t>(site.address), site.identity);
            }

            s_schemeTakeoverInstalled.store(true, std::memory_order_release);
            return true;
        }

        // ---- guarded direct-Ogre helpers for active-viewport application -----
        //
        // MSVC forbids __try in functions that require object unwinding, so
        // every SEH body lives in a noinline core whose scope holds only POD;
        // all std::string construction and export resolution happens in the
        // wrappers outside the guarded region.

        template <typename T>
        T ResolveOgreExport(const char* mangled)
        {
            const HMODULE ogre = GetModuleHandleA("OgreMain.dll");
            if (ogre == nullptr)
            {
                return nullptr;
            }
            return reinterpret_cast<T>(GetProcAddress(ogre, mangled));
        }

        using FnRootGetSingletonPtr = void* (*)();
        using FnRootGetRenderSystem = void* (__thiscall*)(void*);
        using FnRsGetViewport = void* (__thiscall*)(void*);
        using FnVpGetScheme = const std::string& (__thiscall*)(void*);
        using FnVpSetScheme = void (__thiscall*)(void*, const std::string&);
        using FnCompositorGetSingletonPtr = void* (*)();
        using FnCompositorSetEnabled =
            void (__thiscall*)(void*, void*, const std::string&, bool);

        struct OgreViewportApi
        {
            FnVpGetScheme getScheme = nullptr;
            FnVpSetScheme setScheme = nullptr;
            FnRootGetSingletonPtr rootSingleton = nullptr;
            FnRootGetRenderSystem getRenderSystem = nullptr;
            FnRsGetViewport rsGetViewport = nullptr;
            FnCompositorGetSingletonPtr compositorSingleton = nullptr;
            FnCompositorSetEnabled compositorSetEnabled = nullptr;
            bool attempted = false;
        };

        OgreViewportApi g_ogreViewportApi;

        void EnsureOgreViewportApi()
        {
            if (g_ogreViewportApi.attempted)
            {
                return;
            }
            g_ogreViewportApi.attempted = true;

            g_ogreViewportApi.getScheme = ResolveOgreExport<FnVpGetScheme>(
                "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@"
                "V?$allocator@D@2@@std@@XZ");
            g_ogreViewportApi.setScheme = ResolveOgreExport<FnVpSetScheme>(
                "?setMaterialScheme@Viewport@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@"
                "V?$allocator@D@2@@std@@@Z");
            g_ogreViewportApi.rootSingleton =
                ResolveOgreExport<FnRootGetSingletonPtr>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            g_ogreViewportApi.getRenderSystem =
                ResolveOgreExport<FnRootGetRenderSystem>("?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ");
            g_ogreViewportApi.rsGetViewport =
                ResolveOgreExport<FnRsGetViewport>("?_getViewport@RenderSystem@Ogre@@UAEPAVViewport@2@XZ");
            g_ogreViewportApi.compositorSingleton =
                ResolveOgreExport<FnCompositorGetSingletonPtr>("?getSingletonPtr@CompositorManager@Ogre@@SAPAV12@XZ");
            g_ogreViewportApi.compositorSetEnabled =
                ResolveOgreExport<FnCompositorSetEnabled>(
                    "?setCompositorEnabled@CompositorManager@Ogre@@QAEXPAVViewport@2@"
                    "ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");

            LogShimA(LogLevel::Info, kLogTag,
                     "ogre viewport api resolved: scheme=%d set=%d root=%d compositor=%d",
                     g_ogreViewportApi.getScheme ? 1 : 0,
                     g_ogreViewportApi.setScheme ? 1 : 0,
                     (g_ogreViewportApi.rootSingleton && g_ogreViewportApi.getRenderSystem &&
                      g_ogreViewportApi.rsGetViewport) ? 1 : 0,
                     (g_ogreViewportApi.compositorSingleton &&
                      g_ogreViewportApi.compositorSetEnabled) ? 1 : 0);
        }

        __declspec(noinline) static bool GuardedReadViewportScheme(
            FnVpGetScheme fn, void* viewport, std::string* out)
        {
            __try
            {
                *out = fn(viewport);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadViewportScheme(void* viewport, std::string& out)
        {
            EnsureOgreViewportApi();
            if (viewport == nullptr || g_ogreViewportApi.getScheme == nullptr)
            {
                return false;
            }
            return GuardedReadViewportScheme(
                g_ogreViewportApi.getScheme, viewport, &out);
        }

        __declspec(noinline) static bool GuardedWriteViewportScheme(
            FnVpSetScheme fn, void* viewport, const std::string* scheme)
        {
            __try
            {
                fn(viewport, *scheme);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "setMaterialScheme crashed viewport=%p", viewport);
                return false;
            }
        }

        bool WriteViewportScheme(void* viewport, const std::string& scheme)
        {
            EnsureOgreViewportApi();
            if (viewport == nullptr || g_ogreViewportApi.setScheme == nullptr)
            {
                return false;
            }
            return GuardedWriteViewportScheme(
                g_ogreViewportApi.setScheme, viewport, &scheme);
        }

        __declspec(noinline) static bool GuardedSetCompositorEnabled(
            FnCompositorSetEnabled fn, void* manager, void* viewport,
            const std::string* name, int enabled)
        {
            __try
            {
                fn(manager, viewport, *name, enabled != 0);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SetGlowCompositorEnabled(void* viewport, bool enabled)
        {
            EnsureOgreViewportApi();
            if (viewport == nullptr || g_ogreViewportApi.compositorSingleton == nullptr ||
                g_ogreViewportApi.compositorSetEnabled == nullptr)
            {
                return false;
            }
            void* manager = g_ogreViewportApi.compositorSingleton();
            if (manager == nullptr)
            {
                return false;
            }
            static const std::string glowName("Glow");
            return GuardedSetCompositorEnabled(
                g_ogreViewportApi.compositorSetEnabled, manager, viewport,
                &glowName, enabled ? 1 : 0);
        }

        __declspec(noinline) static void* GuardedGetCurrentViewport(
            FnRootGetSingletonPtr rootSingleton,
            FnRootGetRenderSystem getRenderSystem,
            FnRsGetViewport rsGetViewport)
        {
            __try
            {
                void* root = (rootSingleton != nullptr) ? rootSingleton() : nullptr;
                if (root == nullptr || getRenderSystem == nullptr || rsGetViewport == nullptr)
                {
                    return nullptr;
                }
                void* renderSystem = getRenderSystem(root);
                return (renderSystem != nullptr) ? rsGetViewport(renderSystem) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        size_t CollectActiveViewports(void** outViewports, size_t capacity)
        {
            EnsureOgreViewportApi();
            size_t count = 0;
            auto addUnique = [&](void* viewport)
            {
                if (viewport == nullptr)
                {
                    return;
                }
                for (size_t i = 0; i < count; ++i)
                {
                    if (outViewports[i] == viewport)
                    {
                        return;
                    }
                }
                if (count < capacity)
                {
                    outViewports[count++] = viewport;
                }
            };

            addUnique(GuardedGetCurrentViewport(
                g_ogreViewportApi.rootSingleton,
                g_ogreViewportApi.getRenderSystem,
                g_ogreViewportApi.rsGetViewport));
            return count;
        }
    } // anonymous namespace

    void ReapplyEffectiveProfileToViewports(const char* context)
    {
        void* viewports[4] = {};
        const size_t count = CollectActiveViewports(viewports, 4);
        if (count == 0)
        {
            return;
        }

        const Profile effective = static_cast<Profile>(
            s_effectiveProfileAtomic.load(std::memory_order_acquire));
        const bool glowTarget = (effective != Profile::Retro);
        bool changedAny = false;

        for (size_t i = 0; i < count; ++i)
        {
            std::string current;
            if (!ReadViewportScheme(viewports[i], current))
            {
                continue;
            }
            const std::string_view modernBase =
                NormalizeModernMaterialScheme(current, {});

            char buffer[48] = {};
            if (BuildMaterialSchemeForProfile(effective, modernBase, buffer, sizeof(buffer)))
            {
                const std::string target(buffer);
                if (target != current)
                {
                    WriteViewportScheme(viewports[i], target);
                    changedAny = true;
                }
            }
            // Retro suppresses the Glow compositor (legacy CR/EXU behavior);
            // the engine re-enables Glow when it rebuilds a viewport, so the
            // desired state is asserted on every explicit reapply.
            SetGlowCompositorEnabled(viewports[i], glowTarget);
        }

        LogShimA(LogLevel::Info, kLogTag,
                 "reapply (%s): viewports=%zu effective=%s changed=%d glow=%s",
                 context != nullptr ? context : "?",
                 count,
                 ProfileName(effective),
                 changedAny ? 1 : 0,
                 glowTarget ? "on" : "off");
    }

    void RequestContentRenderProfile(ContentRequest request, const char* context)
    {
        {
            AcquireSRWLockExclusive(&s_stateLock);
            s_contentRequest = request;
            s_contentOverridePresent = (request != ContentRequest::Inherit);
            ResolveAndPublishLocked(context);
            ReleaseSRWLockExclusive(&s_stateLock);
        }
        ReapplyEffectiveProfileToViewports(context);
    }

    void ClearContentRenderProfileOverride(const char* context)
    {
        bool hadOverride = false;
        {
            AcquireSRWLockExclusive(&s_stateLock);
            hadOverride = s_contentOverridePresent;
            s_contentRequest = ContentRequest::Inherit;
            s_contentOverridePresent = false;
            ResolveAndPublishLocked(context);
            ReleaseSRWLockExclusive(&s_stateLock);
        }
        if (hadOverride)
        {
            ReapplyEffectiveProfileToViewports(
                context != nullptr ? context : "override cleared");
        }
    }

    void ReloadRenderProfileConfig()
    {
        {
            AcquireSRWLockExclusive(&s_stateLock);
            LoadConfigLocked();
            ResolveAndPublishLocked("ini reload");
            ReleaseSRWLockExclusive(&s_stateLock);
        }
        ReapplyEffectiveProfileToViewports("ini reload");
    }

    void InitializeOgreRenderProfiles()
    {
        static bool s_initialized = false;
        if (s_initialized)
        {
            return;
        }
        s_initialized = true;

        AcquireSRWLockExclusive(&s_stateLock);
        LoadConfigLocked();
        s_resourcesValid = ValidateDeployedResourceSet();

        // Address-dependent work is gated on the supported build; anywhere else
        // the takeover stays off and Enhanced reports itself unavailable
        // instead of half-working.
        if (IsCompatibleGameVersion())
        {
            InstallSchemeTakeover();
        }
        else
        {
            LogShimA(LogLevel::Info, kLogTag,
                     "unsupported build; renderer-profile scheme layer inactive");
        }

        ResolveAndPublishLocked("startup");
        ReleaseSRWLockExclusive(&s_stateLock);

        HANDLE thread = reinterpret_cast<HANDLE>(
            _beginthreadex(nullptr, 0, BackendObservationThread, nullptr, 0, nullptr));
        if (thread != nullptr)
        {
            CloseHandle(thread); // detached worker; self-terminating
        }
        else
        {
            LogShimA(LogLevel::Warn, kLogTag,
                     "backend observation thread failed to start err=%lu",
                     static_cast<unsigned long>(GetLastError()));
        }
    }

    namespace Exports
    {
        uint32_t GetRenderApiVersion()
        {
            return Abi::kRenderApiVersion;
        }

        uint32_t RequestRenderProfile(uint32_t abiRequest)
        {
            ContentRequest request;
            if (!Abi::RequestFromAbi(abiRequest, request))
            {
                return Abi::kRequestStatusRejectedValue;
            }

            RequestContentRenderProfile(request, "EXU request");

            void* probe[1] = {};
            const size_t seen = CollectActiveViewports(probe, 1);
            return seen > 0 ? Abi::kRequestStatusAppliedLive
                            : Abi::kRequestStatusStoredDeferred;
        }

        uint32_t GetUserRenderProfile()
        {
            AcquireSRWLockShared(&s_stateLock);
            uint32_t abi = Abi::kProfileUnknown;
            Abi::ProfileToAbi(s_userProfile, abi);
            ReleaseSRWLockShared(&s_stateLock);
            return abi;
        }

        uint32_t GetRequestedContentRenderProfile()
        {
            AcquireSRWLockShared(&s_stateLock);
            const uint32_t abi = s_contentOverridePresent
                ? static_cast<uint32_t>(static_cast<uint8_t>(s_contentRequest))
                : static_cast<uint32_t>(Abi::kRequestInherit);
            ReleaseSRWLockShared(&s_stateLock);
            return abi;
        }

        uint32_t GetEffectiveRenderProfile()
        {
            AcquireSRWLockShared(&s_stateLock);
            uint32_t abi = Abi::kProfileUnknown;
            Abi::ProfileToAbi(s_effective.effectiveProfile, abi);
            ReleaseSRWLockShared(&s_stateLock);
            return abi;
        }

        uint32_t GetActiveBackend()
        {
            AcquireSRWLockShared(&s_stateLock);
            const uint32_t backend = static_cast<uint32_t>(s_detectedBackend);
            ReleaseSRWLockShared(&s_stateLock);
            return backend;
        }

        uint32_t GetRenderCapabilities()
        {
            AcquireSRWLockShared(&s_stateLock);
            const uint32_t mask = s_capabilityMask;
            ReleaseSRWLockShared(&s_stateLock);
            return mask;
        }

        int SupportsRenderProfile(uint32_t abiProfile)
        {
            Profile profile;
            if (!Abi::ProfileFromAbi(abiProfile, profile))
            {
                return FALSE;
            }
            AcquireSRWLockShared(&s_stateLock);
            const uint32_t mask = s_capabilityMask;
            ReleaseSRWLockShared(&s_stateLock);

            switch (profile)
            {
            case Profile::Enhanced:
            case Profile::Retro:
                return HasCapability(mask, CapSchemeRewrite) ? TRUE : FALSE;
            case Profile::Redux:
            default:
                return TRUE; // Redux is the always-available baseline
            }
        }
    }
} // namespace BZROpenShim::RenderProfiles

// ---- stable winmm bridge exports --------------------------------------------

extern "C" UINT WINAPI OpenShimGetRenderApiVersion()
{
    return BZROpenShim::RenderProfiles::Exports::GetRenderApiVersion();
}

extern "C" DWORD WINAPI OpenShimRequestRenderProfile(DWORD profileRequest)
{
    return BZROpenShim::RenderProfiles::Exports::RequestRenderProfile(profileRequest);
}

extern "C" DWORD WINAPI OpenShimGetUserRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetUserRenderProfile();
}

extern "C" DWORD WINAPI OpenShimGetRequestedContentRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetRequestedContentRenderProfile();
}

extern "C" DWORD WINAPI OpenShimGetEffectiveRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetEffectiveRenderProfile();
}

extern "C" DWORD WINAPI OpenShimGetActiveRendererBackend()
{
    return BZROpenShim::RenderProfiles::Exports::GetActiveBackend();
}

extern "C" DWORD WINAPI OpenShimGetRenderCapabilities()
{
    return BZROpenShim::RenderProfiles::Exports::GetRenderCapabilities();
}

extern "C" BOOL WINAPI OpenShimSupportsRenderProfile(DWORD profile)
{
    return BZROpenShim::RenderProfiles::Exports::SupportsRenderProfile(profile)
        ? TRUE : FALSE;
}
