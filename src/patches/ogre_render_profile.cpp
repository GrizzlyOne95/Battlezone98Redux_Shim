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
#include "backend_selection.h"
#include "startup_backend_seam.h"
#include "dx11_legacy_material_compat.h"
#include "enhanced_resource_bootstrap.h"
#include "openshim_assets.h"
#include "render_profile_resources.h"
#include "render_profile_request_tracker.h"
#include "BZROpenShim.h"
#include "bzr_options_ui.h"
#include "render_profile.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <intrin.h>
#include <process.h>

#include <atomic>
#include <cstring>
#include <filesystem>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_set>

namespace BZROpenShim::RenderProfiles
{




    namespace
    {
        constexpr const char* kLogTag = "RENDER";

        void __fastcall ViewportSetMaterialSchemeHookForward(void* viewport,
                                                             void* edx,
                                                             const std::string* scheme);

        // ---- process state (guarded by s_stateLock) -----------------------
        SRWLOCK s_stateLock = SRWLOCK_INIT;

        RendererBackend s_requestedBackend = RendererBackend::Auto;
        ActiveBackend s_detectedBackend = ActiveBackend::DX9;
        bool s_backendDetected = false;

        // ---- backend-selection boot state (Seam A) --------------------------
        //
        // Persistent requested renderer lives in openshim.ini ([Graphics]
        // Renderer) and is NEVER derived from Ogre.cfg: stock saveConfig()
        // rewrites that file on clean exit, after in-game renderer changes,
        // and even on failed boots, so it is effective-transport only. See
        // reverse_engineering/renderer_startup_backend_selection_20260825.md.
        BackendSelection::BootRequest s_bootRequest {};
        bool s_backendTransportEnabled = true;
        // Read on the render thread by the scheme hook, written under
        // s_stateLock by LoadConfigLocked; atomic so the two never tear.
        std::atomic<bool> s_enhancedSchemeFallbackEnabled { true };
        // DX11 legacy material compatibility ladder (Docs/
        // DX11_LEGACY_MATERIAL_COMPATIBILITY.md). Compat defaults ON once
        // qualified (no mod-side setting can fix abandoned content); the
        // shaderless guard defaults ON (bounded diagnostics instead of
        // exception floods); aggressive generic fallback defaults OFF (it
        // intentionally flattens unknown custom semantics).
        std::atomic<bool> s_dx11CompatEnabled { true };
        std::atomic<bool> s_dx11GuardEnabled { true };
        std::atomic<bool> s_dx11AggressiveEnabled { false };
        // Lock-free DX11 read for the render-thread compat probe. Mirrors
        // s_detectedBackend (written under s_stateLock by the observation
        // worker); DX9 sessions must never enter the compat ladder.
        std::atomic<bool> s_detectedDx11Atomic { false };
        // Lock-free mirror of s_resourcesValid for the render-thread probe.
        // Compat techniques fail closed when the deployed set is broken.
        std::atomic<bool> s_resourcesValidAtomic { false };
        bool s_transportWrittenThisBoot = false;
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

        // Set by non-game-thread requesters that need viewport state applied;
        // drained ONLY by the scheme hook running on the game/render thread
        // (Ogre state mutation must stay on the engine's thread). The epoch
        // tracker is what makes OpenShimRequestRenderProfile's result
        // truthful: a request reports AppliedLive only after a drain whose
        // snapshot covered that publish actually reached viewports.
        std::atomic<bool> s_reapplyPending { false };
        RequestApplyTracker s_applyTracker;

        const char* BackendName(ActiveBackend backend)
        {
            return backend == ActiveBackend::DX11 ? "DX11" : "DX9";
        }

        // Every deferred-apply publisher goes through here so each request
        // gets a distinct epoch (see RequestApplyTracker for the contract).
        void PublishReapplyPending()
        {
            s_applyTracker.Publish();
            s_reapplyPending.store(true, std::memory_order_release);
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
            // Hard kill-switch for the startup transport seam. Default is ON:
            // the seam only acts when [Graphics] Renderer is explicitly not
            // Auto, so Auto users see byte-identical stock behavior either way.
            s_backendTransportEnabled = true;
            if (TryGetUserConfigString("Startup", "BackendTransport", value))
            {
                s_backendTransportEnabled =
                    BackendSelection::ParseTransportEnabled(
                        TrimAsciiCopy(value));
            }
            // Defaults ON: without it, content that lacks enhanced
            // techniques renders black under Enhanced on DX11.
            if (TryGetUserConfigString("Fixes", "EnhancedSchemeFallback",
                                       value))
            {
                s_enhancedSchemeFallbackEnabled.store(
                    BackendSelection::ParseTransportEnabled(
                        TrimAsciiCopy(value)),
                    std::memory_order_release);
            }
            // DX11 legacy material compatibility ladder. Compat + guard
            // default ON (abandoned mods have no mod-side fix; the guard
            // only bounds diagnostics), aggressive defaults OFF (it
            // intentionally approximates unknown custom semantics).
            if (TryGetUserConfigString("Fixes", "DX11LegacyMaterialCompat",
                                       value))
            {
                s_dx11CompatEnabled.store(
                    Dx11Compat::ParseCompatFlag(TrimAsciiCopy(value), true),
                    std::memory_order_release);
            }
            if (TryGetUserConfigString("Fixes", "DX11ShaderlessDrawGuard",
                                       value))
            {
                s_dx11GuardEnabled.store(
                    Dx11Compat::ParseCompatFlag(TrimAsciiCopy(value), true),
                    std::memory_order_release);
            }
            if (TryGetUserConfigString("Fixes", "DX11LegacyMaterialAggressive",
                                       value))
            {
                s_dx11AggressiveEnabled.store(
                    Dx11Compat::ParseCompatFlag(TrimAsciiCopy(value), false),
                    std::memory_order_release);
            }
        }

        // ---- backend-selection startup seam ---------------------------------
        //
        // Evidence base: reverse_engineering/
        // renderer_startup_backend_selection_20260825.md (hardening addendum).
        // Redux resolves its backend from a global desired-name string seeded
        // from /renderer:... or Ogre.cfg's "Render System=" line; OpenShim
        // never intercepts anything downstream of that ladder.
        //
        // Execution model: the heavy transport does NOT run from DllMain
        // (loader lock) and does NOT run from a racing patch thread either.
        // DllMain only installs a narrow IAT interception of the exact Ogre
        // import through which the game's graphics bootstrap reads Ogre.cfg;
        // the transport then executes synchronously on the game thread inside
        // that load call, strictly before stock parses "Render System=", and
        // exactly once per process. Steam's ~1 s startup cannot outrun this:
        // the trigger IS the game's own configuration read.


        // Marker recording this boot's transport request. Its presence at the
        // NEXT launch proves the previous boot ended without an identified
        // renderer - the only observable signature of the device-init-failure
        // abort path (exit code -1 within seconds of Ogre initialisation).




        // Applies the transport request to the "Render System=" line of
        // <game root>\Ogre.cfg via process-unique temp file + MoveFileEx
        // replace; every other byte of the stock file is preserved.
        //
        // Missing-file bootstrap: when Ogre.cfg does not exist at all, the
        // transport previously failed open and the explicit request was lost
        // for one boot (stock recreated the file with DX9). Instead, write a
        // minimal single-line config image ("Render System=<name>"): stock's
        // own restore/default-seeding path completes every remaining section
        // on this same boot (RE matrix case cfg-missing proved the game fully
        // recreates the file even from nothing).
        //
        // Any failure leaves the stock file untouched (fail open to stock
        // selection) and cleans up this process's temp file; the temp name is
        // PID-unique so two concurrent game processes can never collide or
        // delete each other's files.

        // Resolves this boot's backend request and applies the Ogre.cfg
        // transport when an explicit, capability-validated request exists.
        //
        // Caller MUST hold s_stateLock exclusively: this runs inside
        // InitializeOgreRenderProfiles' startup critical section, before the
        // observation thread exists. SRW locks are not recursive, which is why
        // no locking happens in here despite all the s_* state mutation.

        // ---- startup configuration-load interception (the Seam A trigger) --
        //
        // Binary facts (GOG 2.2.301, image base 0x00400000; verified against
        // the import table and a full .text scan of FF 15 <IAT disp>; Steam
        // shares every .rdata/.idata fact and settles to identical .text):
        //
        //   Ogre::ConfigFile::load(const String&, const String&, bool)
        //     mangled: ?load@ConfigFile@Ogre@@QAEXABV?$basic_string@DU?$char_
        //              traits@D@std@@V?$allocator@D@2@@std@@0_N@Z
        //     IAT slot VA 0x00869D08 (RVA 0x00469D08), OgreMain.dll import.
        //
        //   Startup call chain: FUN_00663ED0 (graphics bootstrap) loads
        //   <game root>\Ogre.cfg through this import with its only call at
        //   0x006640E4 = `FF 15 08 9D 86 00` (return address 0x006640EA),
        //   then tail-continues into FUN_00664110 which reads getSetting(
        //   "Render System") — the exact seam ordering we need: our transport
        //   runs inside load(), before that read.
        //
        //   A second unrelated caller exists at 0x0066471E inside
        //   FUN_00664110; it is excluded by the return-address gate below.
        //
        // Install-time validation (DllMain, loader-lock-bounded, no .text
        // access so SteamStub-at-rest bytes are never consulted):
        //   1. main module name is battlezone98redux.exe;
        //   2. SizeOfImage matches a known qualified build
        //      (GOG 0x290F000 / Steam 0x292F000 incl. .bind);
        //   3. plaintext .rdata identity marker "Ogre.cfg\0" sits at the
        //      qualified VA 0x00892030 (identical both storefronts);
        //   4. OgreMain.dll is loaded and exports exactly the mangled import;
        //   5. IAT slot 0x469D08 is bound to that export right now.
        // Any miss fails closed: no hook, feature inert, pure stock behavior.
        //
        // Call-time validation (game thread, .text settled by definition since
        // the CPU is executing it): return address == 0x006640EA AND the six
        // call-site bytes still equal FF 15 08 9D 86 00 AND the first string
        // argument names Ogre.cfg. Only then does the one-shot transport run.




        __declspec(noinline) static bool GuardedWriteSlotValue(
            void* slot, void* value)
        {
            __try
            {
                *static_cast<void**>(slot) = value;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }


        // Loader-lock-bounded install: header/name/export/slot checks plus one
        // protected pointer swap. No CRT containers, no filesystem, no waits,
        // no .text reads and no normal logger calls (Steam-safe at attach
        // time). Failures publish only a fixed enum; the patch thread reports
        // that result later, after DllMain has released the loader lock.


        // Post-settle call-site proof: the six bytes at the known startup call
        // instruction must still be `call dword ptr [0x00869D08]`. Runs on the
        // game thread, so SteamStub has long since decrypted .text.


        // SEH boundary: the forwarder itself holds no unwinding objects, so a
        // fault anywhere in the gate/transport degrades to stock behavior.


        // Post-establishment classification. Runs on the observation worker
        // after the active render system was identified (or after the window
        // closed without identification). Pure reporting: never mutates Ogre.
        // Takes the state lock only briefly to snapshot boot request state;
        // all file reads happen outside it.
        void ReportSelectionOutcome(bool identified, bool effectiveIsDx11)
        {
            AcquireSRWLockExclusive(&s_stateLock);
            const BackendSelection::BootRequest boot = s_bootRequest;
            const bool transportWritten = s_transportWrittenThisBoot;
            ReleaseSRWLockExclusive(&s_stateLock);

            if (boot.backend == RendererBackend::Auto)
            {
                if (identified)
                {
                    LogShimA(LogLevel::Info, kLogTag,
                             "backend.selection=stock requested=Auto effective=%s "
                             "reason=stock",
                             effectiveIsDx11 ? "DX11" : "DX9");
                    StartupSeam::ClearPendingMarker();
                }
                return;
            }

            BackendSelection::OutcomeInput input;
            input.haveRequest = true;
            input.requested = boot.backend;
            input.source = boot.source;
            input.backendIdentified = identified;
            input.effective =
                effectiveIsDx11 ? ActiveBackend::DX11 : ActiveBackend::DX9;

            if (identified)
            {
                // Post-boot stock line is the signal distinguishing a ladder
                // fallback that rewrote the transport (backend-unavailable)
                // from other mismatches. Read OUTSIDE any lock.
                const auto dir = GetMainModuleDirectory();
                std::string cfgText;
                if (!dir.empty())
                {
                    FILE* file = nullptr;
                    const auto cfgPath = dir / "Ogre.cfg";
                    if (_wfopen_s(&file, cfgPath.c_str(), L"rb") == 0 && file != nullptr)
                    {
                        char buffer[2048] = {};
                        const size_t got = fread(buffer, 1, sizeof(buffer) - 1, file);
                        fclose(file);
                        cfgText.assign(buffer, got);
                    }
                }
                input.stockLineAfterBoot =
                    BackendSelection::ExtractStockRenderSystemValue(cfgText);
            }

            const auto reason = BackendSelection::ClassifyOutcome(input);
            const char* requestedText = RequestedBackendName(boot.backend);
            const char* effectiveText =
                identified ? (effectiveIsDx11 ? "DX11" : "DX9") : "none";

            LogShimA(reason == BackendSelection::SelectionReason::None ||
                             reason == BackendSelection::SelectionReason::CliOverride ||
                             reason == BackendSelection::SelectionReason::Stock
                         ? LogLevel::Info
                         : LogLevel::Warn,
                     kLogTag,
                     "backend.selection=%s requested=%s effective=%s reason=%s%s",
                     boot.source == BackendSelection::RequestSource::None ? "stock"
                                                                          : "override",
                     requestedText, effectiveText, BackendSelection::ReasonName(reason),
                     transportWritten ? " transport=written" : "");
            if (reason == BackendSelection::SelectionReason::BackendUnavailable)
            {
                LogShimA(LogLevel::Info, kLogTag,
                         "preserving requested backend=%s (openshim.ini unchanged; "
                         "stock rewrote Ogre.cfg only)",
                         requestedText);
            }

            // Establishment happened: this boot consumed its marker. On
            // non-identification the marker survives so an abnormal exit is
            // still attributed on the next launch.
            if (identified)
            {
                StartupSeam::ClearPendingMarker();
            }
        }

        // ---- deployed Enhanced renderer-resource validation -----------------

        // Thin runtime wrapper: the actual file-set contract lives in
        // src/engine/render_profile_resources.cpp (unit-tested against real
        // directory trees); this layer adds the game-directory join and the
        // log formatting.
        bool ValidateDeployedResourceSet()
        {
            const std::filesystem::path gameDir = GetMainModuleDirectory();
            if (gameDir.empty())
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "Enhanced resource set unverifiable: main module directory unknown");
                return false;
            }

            std::string problem;
            std::filesystem::path resourceDir;
            if (!Assets::ProbeEnhancedResourcesAt(
                    gameDir, problem, &resourceDir))
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "Enhanced unavailable: %s",
                         problem.c_str());
                return false;
            }

            LogShimA(LogLevel::Info, kLogTag,
                     "resource-version=%s resources compatible=yes (%zu files verified root=%s)",
                     kEnhancedResourcesVersion,
                     RequiredEnhancedResourceCount(),
                     resourceDir.string().c_str());
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
            // Resource findings only ever REMOVE base bits, then add the two
            // resource-derived bits. CapEnhancedResources is the MANDATORY
            // set (gates Enhanced itself in the resolver); CapIblResources is
            // the OPTIONAL IBL extras (never gates the profile).
            if (s_resourcesValid)
            {
                mask |= static_cast<uint32_t>(CapIblResources) |
                        static_cast<uint32_t>(CapEnhancedResources);
            }
            else
            {
                mask &= ~(static_cast<uint32_t>(CapIblResources) |
                          static_cast<uint32_t>(CapEnhancedResources));
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
            static BackendSelection::BootRequest s_lastBootReported {};
            static bool s_haveLast = false;

            if (s_haveLast &&
                s_lastReported.effectiveProfile == s_effective.effectiveProfile &&
                s_lastReported.fellBack == s_effective.fellBack &&
                s_lastMask == s_capabilityMask &&
                s_lastBootReported.backend == s_bootRequest.backend &&
                s_lastBootReported.source == s_bootRequest.source &&
                strcmp(s_lastReported.reason, s_effective.reason) == 0)
            {
                return;
            }

            s_lastReported = s_effective;
            s_lastMask = s_capabilityMask;
            s_lastBootReported = s_bootRequest;
            s_haveLast = true;

            // Report THIS BOOT's effective request (CLI override included),
            // not just the persistent preference: requested/effective must
            // stay attributable to what was actually asked of stock selection
            // this launch.
            const char* requestedName =
                s_bootRequest.backend == RendererBackend::DX11 ? "DX11"
                : s_bootRequest.backend == RendererBackend::DX9 ? "DX9"
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
                     ProfileRequirementsMet(Profile::Enhanced, s_capabilityMask) ? "yes" : "no",
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

        // ---- guarded direct-Ogre helpers -------------------------------------
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

        // ---- backend observation --------------------------------------------

        using FnRsGetNameByName =
            void* (__thiscall*)(void*, const std::string&);

        // Built once on first use; lives here so the SEH core below holds no
        // destructor-bearing objects.
        const std::string& KnownRenderSystemName(int index)
        {
            static const std::string kNames[3] = {
                "Direct3D11 Rendering Subsystem",
                "Direct3D9 Rendering Subsystem",
                "OpenGL Rendering Subsystem",
            };
            return kNames[index];
        }

        // Returns 0 = not ready, 1 = DX11, 2 = DX9, 3 = other/unknown,
        // -1 = transient fault (retry).
        __declspec(noinline) static int GuardedIdentifyActiveBackend(
            FnRootGetSingletonPtr rootSingleton,
            FnRootGetRenderSystem getRenderSystem,
            FnRsGetNameByName getRenderSystemByName)
        {
            // No dynamic locals allowed in an SEH scope: KnownRenderSystemName
            // hands back references to storage built elsewhere.
            __try
            {
                void* root = (rootSingleton != nullptr) ? rootSingleton() : nullptr;
                if (root == nullptr || getRenderSystem == nullptr ||
                    getRenderSystemByName == nullptr)
                {
                    return 0;
                }
                void* active = getRenderSystem(root);
                if (active == nullptr)
                {
                    return 0;
                }
                // Identity comparison against the known render systems avoids
                // RenderSystem::getName entirely: it is virtual and this build
                // does not export it.
                if (getRenderSystemByName(root, KnownRenderSystemName(0)) == active)
                {
                    return 1;
                }
                if (getRenderSystemByName(root, KnownRenderSystemName(1)) == active)
                {
                    return 2;
                }
                if (getRenderSystemByName(root, KnownRenderSystemName(2)) == active)
                {
                    return 3;
                }
                return 4;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        int DetectActiveBackend()
        {
            // Deliberately NOT cached in function-local statics: this polls
            // from a worker that starts before OgreMain.dll loads, and a
            // first-call nullptr would otherwise be cached for the process
            // lifetime (the exact failure the matrix caught).
            const FnRootGetSingletonPtr rootSingleton =
                ResolveOgreExport<FnRootGetSingletonPtr>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            if (rootSingleton == nullptr)
            {
                static bool s_loggedRootWait = false;
                if (!s_loggedRootWait)
                {
                    s_loggedRootWait = true;
                    LogShimA(LogLevel::Info, kLogTag,
                             "observation: waiting for OgreMain Root export");
                }
                return 0;
            }
            static bool s_loggedRootReady = false;
            if (!s_loggedRootReady)
            {
                s_loggedRootReady = true;
                LogShimA(LogLevel::Info, kLogTag,
                         "observation: Root export resolved");
            }
            static FnRootGetRenderSystem getRenderSystem = nullptr;
            static FnRsGetNameByName getRenderSystemByName = nullptr;
            if (getRenderSystem == nullptr)
            {
                getRenderSystem =
                    ResolveOgreExport<FnRootGetRenderSystem>("?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ");
                getRenderSystemByName =
                    ResolveOgreExport<FnRsGetNameByName>(
                        "?getRenderSystemByName@Root@Ogre@@QAEPAVRenderSystem@2@"
                        "ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            }
            if (getRenderSystem == nullptr || getRenderSystemByName == nullptr)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "observation: Root render-system exports unresolved");
                return 0;
            }
            return GuardedIdentifyActiveBackend(
                rootSingleton, getRenderSystem, getRenderSystemByName);
        }

        unsigned __stdcall BackendObservationThread(void*)
        {
            LogShimA(LogLevel::Info, kLogTag, "backend observation thread started");
            constexpr DWORD pollMs = 250;
            constexpr DWORD timeoutMs = 90000;
            DWORD waited = 0;
            bool decided = false;
            bool dx11 = false;

            while (waited < timeoutMs)
            {
                // Authoritative signal only: pointer-identity comparison of the
                // engine's ACTIVE render system against the known subsystems
                // via exported Root APIs. Module presence is NOT used: Ogre
                // loads every configured render-system plugin, so module
                // enumeration races plugin order and misreports the backend.
                const int identified = DetectActiveBackend();
                if (identified == 1)
                {
                    dx11 = true;
                    decided = true;
                    LogShimA(LogLevel::Info, kLogTag,
                             "backend identified: active render system is Direct3D11");
                    break;
                }
                if (identified == 2)
                {
                    dx11 = false;
                    decided = true;
                    LogShimA(LogLevel::Info, kLogTag,
                             "backend identified: active render system is Direct3D9");
                    break;
                }
                if (identified == 3)
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend observation: active render system is OpenGL; "
                             "conservative DX9 assumptions stay active");
                    ReportSelectionOutcome(false, false);
                    return 0;
                }
                if (identified == 4)
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend observation: active render system unrecognized; "
                             "conservative DX9 assumptions stay active");
                    ReportSelectionOutcome(false, false);
                    return 0;
                }
                Sleep(pollMs);
                waited += pollMs;
            }

            if (!decided)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend detection timed out after %lu ms; conservative DX9 assumptions stay active",
                         static_cast<unsigned long>(timeoutMs));
                // No establishment observed; the pending marker deliberately
                // survives so an abnormal exit after this point is still
                // attributed on the next launch.
                ReportSelectionOutcome(false, false);
                return 0;
            }

            AcquireSRWLockExclusive(&s_stateLock);
            s_detectedBackend = dx11 ? ActiveBackend::DX11 : ActiveBackend::DX9;
            s_backendDetected = true;
            s_detectedDx11Atomic.store(dx11, std::memory_order_release);
            ResolveAndPublishLocked("backend observed");
            ReleaseSRWLockExclusive(&s_stateLock);
            // Seam A outcome reporting: pure logging + marker bookkeeping.
            ReportSelectionOutcome(true, dx11);
            // This is a worker thread: never touch Ogre viewports from here.
            // Publish the pending flag; the scheme hook drains it on the
            // engine's own thread at the next setMaterialScheme call (~1 Hz).
            PublishReapplyPending();
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


        // ---- enhanced-scheme fallback ---------------------------------------
        //
        // The takeover above is viewport-global: it rewrites the engine's
        // scheme ("high-noshadow") to "en-high-noshadow" for everything drawn
        // through that viewport. Only materials that declare the enhanced
        // technique family can satisfy it -- in practice CR_BZTerrainBase,
        // CR_BZBase, and the materials that inherit them.
        //
        // A Workshop or converted legacy map whose terrain material inherits
        // stock BZTerrainBase has no "en-" technique at all. Ogre's default
        // answer to "no technique for the active scheme" is to fall back to the
        // material's FIRST technique, and BZTerrainBase opens with
        // `scheme high-pssm`. That pass consumes texWorldViewProj1..3; on a
        // viewport whose shadow setup never ran those arrive NaN, the sm4 pixel
        // shader writes NaN, and a UNORM target stores NaN as 0. The terrain
        // renders black -- on DX11 only, because only the sm4 path produces the
        // NaN. Same defect shape as [Fixes] MpVehiclePreviewShadowScheme,
        // reached through a different door.
        //
        // handleSchemeNotFound is Ogre's designed hook for exactly this case.
        // Strip our own prefix and hand back the material's own technique for
        // the base scheme, so unenhanced content renders the way it does under
        // the stock profile instead of falling through to PSSM.

        using FnMaterialManagerGetSingletonPtr = void* (*)();
        using FnMaterialManagerAddListener =
            void(__thiscall*)(void*, void*, const std::string&);
        using FnMaterialGetNumTechniques = unsigned short(__thiscall*)(const void*);
        using FnMaterialGetTechnique = void* (__thiscall*)(void*, unsigned short);
        using FnTechniqueGetSchemeName =
            const std::string& (__thiscall*)(const void*);
        using FnTechniqueGetLodIndex = unsigned short(__thiscall*)(const void*);
        using FnTechniqueIsSupported = bool(__thiscall*)(const void*);

        struct OgreTechniqueApi
        {
            FnMaterialGetNumTechniques getNumTechniques = nullptr;
            FnMaterialGetTechnique getTechnique = nullptr;
            FnTechniqueGetSchemeName getSchemeName = nullptr;
            FnTechniqueGetLodIndex getLodIndex = nullptr;
            FnTechniqueIsSupported isSupported = nullptr;

            bool Valid() const
            {
                return getNumTechniques != nullptr && getTechnique != nullptr &&
                       getSchemeName != nullptr && getLodIndex != nullptr &&
                       isSupported != nullptr;
            }
        };

        const OgreTechniqueApi& TechniqueApi()
        {
            static const OgreTechniqueApi api = [] {
                OgreTechniqueApi resolved;
                resolved.getNumTechniques =
                    ResolveOgreExport<FnMaterialGetNumTechniques>(
                        "?getNumTechniques@Material@Ogre@@QBEGXZ");
                resolved.getTechnique =
                    ResolveOgreExport<FnMaterialGetTechnique>(
                        "?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
                resolved.getSchemeName =
                    ResolveOgreExport<FnTechniqueGetSchemeName>(
                        "?getSchemeName@Technique@Ogre@@QBEABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                resolved.getLodIndex =
                    ResolveOgreExport<FnTechniqueGetLodIndex>(
                        "?getLodIndex@Technique@Ogre@@QBEGXZ");
                resolved.isSupported =
                    ResolveOgreExport<FnTechniqueIsSupported>(
                        "?isSupported@Technique@Ogre@@QBE_NXZ");
                return resolved;
            }();
            return api;
        }

        void* ResolveBaseSchemeTechnique(const std::string& schemeName,
                                         void* material,
                                         unsigned short lodIndex)
        {
            if (material == nullptr)
            {
                return nullptr;
            }

            const std::string_view name(schemeName);
            if (!name.starts_with("en-") && !name.starts_with("og-"))
            {
                // Not a scheme this layer invents. Anything else is the
                // engine's or a mod's business, so leave Ogre's answer alone.
                return nullptr;
            }
            const std::string_view base = name.substr(3);
            if (base.empty())
            {
                return nullptr;
            }

            const OgreTechniqueApi& api = TechniqueApi();
            if (!api.Valid())
            {
                return nullptr;
            }

            void* schemeMatch = nullptr;
            const unsigned short count = api.getNumTechniques(material);
            for (unsigned short i = 0; i < count; ++i)
            {
                void* technique = api.getTechnique(material, i);
                if (technique == nullptr)
                {
                    continue;
                }
                // Ogre requires a technique that is supported on this hardware;
                // returning an unsupported one fails later and less visibly.
                if (!api.isSupported(technique))
                {
                    continue;
                }
                if (std::string_view(api.getSchemeName(technique)) != base)
                {
                    continue;
                }
                if (api.getLodIndex(technique) == lodIndex)
                {
                    return technique;
                }
                if (schemeMatch == nullptr)
                {
                    schemeMatch = technique;
                }
            }
            // Prefer the exact LOD; otherwise any supported technique in the
            // base scheme still beats technique 0 from a foreign scheme.
            return schemeMatch;
        }

        // ---- DX11 legacy material compatibility probe ----------------------
        //
        // Design anchor for Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md.
        // handleSchemeNotFound is Ogre's designed hook for a missing scheme;
        // the ISDF Chronicles repro shows a second DX11-only failure shape on
        // top of that: materials whose techniques exist but are unsupported
        // on D3D11 (true fixed-function passes with no VS/PS at all, plus
        // programmable passes referencing SM2/SM3-only families such as
        // Effect_*/Textured_*/Untextured_*/Sky_*/simple_one_tex). D3D11 has
        // no fixed pipeline, so Ogre reaches the render path with no shaders
        // bound and throws per draw (1,300 observed) plus "Invalid target
        // for D3D11 shader" spam (264 observed).
        //
        // Policy lives in the pure engine module
        // (include/dx11_legacy_material_compat.h); this layer only resolves
        // the narrow Ogre ABI needed to inspect techniques/passes, builds a
        // LegacyPassDesc, classifies it, logs once per unique miss, bumps
        // counters, and fails closed to nullptr (Ogre's stock answer) when
        // no compat path can be proven. The first instantiation slice now
        // deep-clones one-pass source techniques, swaps in
        // OSE_Compat_*/OSE_FixedFunc_* SM4 programs, reloads the parent
        // material so Ogre recompiles its supported-technique table, and
        // returns the generated technique directly. Multi-pass and aggressive
        // conversion remain diagnostic-only until each pass can be classified.
        //
        // Constraints honored here: DX9 untouched (DX11-gated), native DX11
        // techniques untouched (only reached when no supported technique
        // exists), no disk rewriting, no per-draw generation (once-only log
        // + cache-key set), aggressive mode OFF by default.

        using FnTechniqueGetNumPasses = unsigned short(__thiscall*)(const void*);
        using FnTechniqueGetPass = void* (__thiscall*)(void*, unsigned short);
        using FnPassHasVertexProgram = bool(__thiscall*)(const void*);
        using FnPassHasFragmentProgram = bool(__thiscall*)(const void*);
        using FnPassGetVertexProgramName =
            const std::string& (__thiscall*)(const void*);
        using FnPassGetFragmentProgramName =
            const std::string& (__thiscall*)(const void*);
        using FnPassGetNumTexUnits = unsigned short(__thiscall*)(const void*);
        using FnResourceGetName =
            const std::string& (__thiscall*)(const void*);
        using FnMaterialCreateTechnique = void* (__thiscall*)(void*);
        using FnMaterialRemoveTechnique = void(__thiscall*)(void*, unsigned short);
        using FnMaterialNotifyNeedsRecompile = void(__thiscall*)(void*);
        using FnTechniqueAssign = void* (__thiscall*)(void*, const void*);
        using FnTechniqueSetSchemeName =
            void(__thiscall*)(void*, const std::string&);
        using FnTechniqueSetLodIndex = void(__thiscall*)(void*, unsigned short);
        using FnPassSetProgram =
            void(__thiscall*)(void*, const std::string&, bool);
        using FnResourceLoad = void(__thiscall*)(void*, bool);

        struct OgreCompatPassApi
        {
            FnTechniqueGetNumPasses getNumPasses = nullptr;
            FnTechniqueGetPass getPass = nullptr;
            FnPassHasVertexProgram hasVertexProgram = nullptr;
            FnPassHasFragmentProgram hasFragmentProgram = nullptr;
            FnPassGetVertexProgramName getVertexProgramName = nullptr;
            FnPassGetFragmentProgramName getFragmentProgramName = nullptr;
            FnPassGetNumTexUnits getNumTexUnits = nullptr;
            FnResourceGetName getResourceName = nullptr;

            bool CanInspect() const
            {
                return getNumPasses != nullptr && getPass != nullptr &&
                       hasVertexProgram != nullptr &&
                       hasFragmentProgram != nullptr &&
                       getVertexProgramName != nullptr &&
                       getFragmentProgramName != nullptr;
            }
        };

        const OgreCompatPassApi& CompatPassApi()
        {
            static const OgreCompatPassApi api = [] {
                OgreCompatPassApi resolved;
                resolved.getNumPasses =
                    ResolveOgreExport<FnTechniqueGetNumPasses>(
                        "?getNumPasses@Technique@Ogre@@QBEGXZ");
                resolved.getPass =
                    ResolveOgreExport<FnTechniqueGetPass>(
                        "?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
                resolved.hasVertexProgram =
                    ResolveOgreExport<FnPassHasVertexProgram>(
                        "?hasVertexProgram@Pass@Ogre@@QBE_NXZ");
                resolved.hasFragmentProgram =
                    ResolveOgreExport<FnPassHasFragmentProgram>(
                        "?hasFragmentProgram@Pass@Ogre@@QBE_NXZ");
                resolved.getVertexProgramName =
                    ResolveOgreExport<FnPassGetVertexProgramName>(
                        "?getVertexProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                resolved.getFragmentProgramName =
                    ResolveOgreExport<FnPassGetFragmentProgramName>(
                        "?getFragmentProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                resolved.getNumTexUnits =
                    ResolveOgreExport<FnPassGetNumTexUnits>(
                        "?getNumTextureUnitStates@Pass@Ogre@@QBEGXZ");
                resolved.getResourceName =
                    ResolveOgreExport<FnResourceGetName>(
                        // "UBE", not "QBE": Resource::getName is VIRTUAL and
                        // decorates differently. The non-virtual spelling
                        // resolves to nothing, GetProcAddress returns null,
                        // and every material silently reports "<unknown>" --
                        // which is exactly what a live DX11 run showed for
                        // every material in the log. Calling the exported
                        // address directly stays correct because Material
                        // does not override getName.
                        "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                return resolved;
            }();
            return api;
        }

        struct OgreCompatMutationApi
        {
            FnMaterialCreateTechnique createTechnique = nullptr;
            FnMaterialRemoveTechnique removeTechnique = nullptr;
            FnMaterialNotifyNeedsRecompile notifyNeedsRecompile = nullptr;
            FnTechniqueAssign assignTechnique = nullptr;
            FnTechniqueSetSchemeName setSchemeName = nullptr;
            FnTechniqueSetLodIndex setLodIndex = nullptr;
            FnPassSetProgram setVertexProgram = nullptr;
            FnPassSetProgram setFragmentProgram = nullptr;
            FnResourceLoad loadResource = nullptr;

            bool CanInstantiate() const
            {
                return createTechnique != nullptr &&
                       assignTechnique != nullptr &&
                       setSchemeName != nullptr &&
                       setLodIndex != nullptr &&
                       setVertexProgram != nullptr &&
                       setFragmentProgram != nullptr &&
                       loadResource != nullptr;
            }
        };

        const OgreCompatMutationApi& CompatMutationApi()
        {
            static const OgreCompatMutationApi api = [] {
                OgreCompatMutationApi resolved;
                resolved.createTechnique =
                    ResolveOgreExport<FnMaterialCreateTechnique>(
                        "?createTechnique@Material@Ogre@@QAEPAVTechnique@2@XZ");
                resolved.removeTechnique =
                    ResolveOgreExport<FnMaterialRemoveTechnique>(
                        "?removeTechnique@Material@Ogre@@QAEXG@Z");
                resolved.notifyNeedsRecompile =
                    ResolveOgreExport<FnMaterialNotifyNeedsRecompile>(
                        "?_notifyNeedsRecompile@Material@Ogre@@QAEXXZ");
                resolved.assignTechnique =
                    ResolveOgreExport<FnTechniqueAssign>(
                        "??4Technique@Ogre@@QAEAAV01@ABV01@@Z");
                resolved.setSchemeName =
                    ResolveOgreExport<FnTechniqueSetSchemeName>(
                        "?setSchemeName@Technique@Ogre@@QAEXABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                resolved.setLodIndex =
                    ResolveOgreExport<FnTechniqueSetLodIndex>(
                        "?setLodIndex@Technique@Ogre@@QAEXG@Z");
                resolved.setVertexProgram =
                    ResolveOgreExport<FnPassSetProgram>(
                        "?setVertexProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
                resolved.setFragmentProgram =
                    ResolveOgreExport<FnPassSetProgram>(
                        "?setFragmentProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?"
                        "$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
                resolved.loadResource =
                    ResolveOgreExport<FnResourceLoad>(
                        "?load@Resource@Ogre@@UAEX_N@Z");
                return resolved;
            }();
            return api;
        }

        __declspec(noinline) static unsigned short GuardedGetNumPasses(
            FnTechniqueGetNumPasses fn, const void* technique)
        {
            __try
            {
                return (fn != nullptr && technique != nullptr) ? fn(technique) : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        __declspec(noinline) static void* GuardedGetPass(
            FnTechniqueGetPass fn, void* technique, unsigned short index)
        {
            __try
            {
                return (fn != nullptr && technique != nullptr)
                    ? fn(technique, index)
                    : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        __declspec(noinline) static unsigned short GuardedGetNumTexUnits(
            FnPassGetNumTexUnits fn, const void* pass)
        {
            __try
            {
                return (fn != nullptr && pass != nullptr) ? fn(pass) : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        __declspec(noinline) static bool GuardedHasProgram(
            bool isVertex, const void* pass, bool fallback)
        {
            __try
            {
                const OgreCompatPassApi& api = CompatPassApi();
                if (pass == nullptr)
                {
                    return false;
                }
                if (isVertex)
                {
                    return (api.hasVertexProgram != nullptr)
                        ? api.hasVertexProgram(pass)
                        : fallback;
                }
                return (api.hasFragmentProgram != nullptr)
                    ? api.hasFragmentProgram(pass)
                    : fallback;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return fallback;
            }
        }

        __declspec(noinline) static bool GuardedCopyProgramName(
            bool isVertex, const void* pass, std::string* out)
        {
            __try
            {
                const OgreCompatPassApi& api = CompatPassApi();
                if (pass == nullptr || out == nullptr)
                {
                    return false;
                }
                if (isVertex && api.getVertexProgramName != nullptr)
                {
                    *out = api.getVertexProgramName(pass);
                    return true;
                }
                if (!isVertex && api.getFragmentProgramName != nullptr)
                {
                    *out = api.getFragmentProgramName(pass);
                    return true;
                }
                return false;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        __declspec(noinline) static bool GuardedCopyResourceName(
            const void* material, std::string* out)
        {
            __try
            {
                const OgreCompatPassApi& api = CompatPassApi();
                if (material == nullptr || out == nullptr ||
                    api.getResourceName == nullptr)
                {
                    return false;
                }
                *out = api.getResourceName(material);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct CompatProbeState
        {
            std::mutex lock;
            std::unordered_set<std::string> loggedLines;
            std::unordered_set<std::string> cacheKeys;
            std::atomic<uint64_t> nativeSupported { 0 };
            std::atomic<uint64_t> familyRemaps { 0 };
            std::atomic<uint64_t> fixedFunc { 0 };
            std::atomic<uint64_t> aggressive { 0 };
            std::atomic<uint64_t> unsupported { 0 };
            std::atomic<uint64_t> skipped { 0 };
            std::atomic<bool> apiWarned { false };
            std::atomic<bool> resourcesWarned { false };
        };

        CompatProbeState& ProbeState()
        {
            static CompatProbeState state;
            return state;
        }

        void LogCompatOnce(const std::string& line, LogLevel level)
        {
            CompatProbeState& state = ProbeState();
            {
                std::lock_guard<std::mutex> guard(state.lock);
                if (!state.loggedLines.insert(line).second)
                {
                    return;
                }
            }
            LogShimA(level, kLogTag, "%s", line.c_str());
        }

        bool NoteCompatCacheKey(const std::string& key)
        {
            CompatProbeState& state = ProbeState();
            std::lock_guard<std::mutex> guard(state.lock);
            if (state.cacheKeys.find(key) != state.cacheKeys.end())
            {
                return true;
            }
            state.cacheKeys.insert(key);
            return false;
        }

        Dx11Compat::CompatConfig CurrentCompatConfig()
        {
            Dx11Compat::CompatConfig config;
            config.compatEnabled =
                s_dx11CompatEnabled.load(std::memory_order_acquire);
            config.guardEnabled =
                s_dx11GuardEnabled.load(std::memory_order_acquire);
            config.aggressiveEnabled =
                s_dx11AggressiveEnabled.load(std::memory_order_acquire);
            return config;
        }

        // Best-effort legacy description for the FIRST pass of the source
        // technique. Texture color-op is not resolved through the narrow ABI
        // (TextureUnitState combine reads need a wider, proven surface), so
        // single-texture passes assume the overwhelmingly common modulate
        // combine; multi-texture passes are reported as-is and the pure
        // policy marks 2+ units unsupported pending corpus telemetry.
        Dx11Compat::LegacyPassDesc DescribeFirstPass(void* technique)
        {
            Dx11Compat::LegacyPassDesc desc;
            if (technique == nullptr || !CompatPassApi().CanInspect())
            {
                return desc;
            }
            void* pass = GuardedGetPass(CompatPassApi().getPass, technique, 0);
            if (pass == nullptr)
            {
                return desc;
            }
            desc.hasVertexRef = GuardedHasProgram(true, pass, false);
            desc.hasFragmentRef = GuardedHasProgram(false, pass, false);
            if (desc.hasVertexRef)
            {
                std::string vs;
                if (GuardedCopyProgramName(true, pass, &vs))
                {
                    desc.vertexProgram = vs;
                }
            }
            if (desc.hasFragmentRef)
            {
                std::string ps;
                if (GuardedCopyProgramName(false, pass, &ps))
                {
                    desc.fragmentProgram = ps;
                }
            }
            // Targets are not resolved through this narrow surface (that
            // needs GpuProgram dereference); names alone drive the family
            // table, and any technique that reaches this probe is already
            // known-unsupported on DX11. Leave targets empty so
            // ClassifyLegacyPass treats referenced programs as legacy.
            desc.textureUnits = static_cast<int>(
                GuardedGetNumTexUnits(CompatPassApi().getNumTexUnits, pass));
            if (desc.textureUnits == 1)
            {
                desc.colorOp0 = "modulate";
            }
            return desc;
        }

        void RestoreMaterialAfterCompatFailure(void* material,
                                               unsigned short createdIndex)
        {
            const OgreCompatMutationApi& mutate = CompatMutationApi();
            try
            {
                if (mutate.removeTechnique != nullptr)
                {
                    mutate.removeTechnique(material, createdIndex);
                }
                if (mutate.notifyNeedsRecompile != nullptr)
                {
                    mutate.notifyNeedsRecompile(material);
                }
                if (mutate.loadResource != nullptr)
                {
                    mutate.loadResource(material, false);
                }
            }
            catch (...)
            {
                // The compatibility path is best-effort. Never allow cleanup
                // of a failed generated technique to escape into Ogre's render
                // loop; the caller will fail closed to the stock fallback.
            }
        }

        // ---- OpenShim-owned Enhanced resource bootstrap ---------------------
        //
        // OpenShim ships the Enhanced payload but nothing ever registered it
        // with Ogre: bz_resources.cfg names only ./BZ_ASSETS and
        // ./BZ_ASSETS_CORE, so on an install without Campaign Reimagined the
        // OSE_* .program declarations sit on disk unparsed and every OSE_*
        // name is absent at runtime. A live DX11 run proved it -- all 81
        // synthesis attempts declined with reason=program-absent while all 26
        // payload files were present on disk. CR's own resource config is
        // what pulled the directory in, which is precisely the dependency
        // Docs/ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md forbids.
        //
        // The directory is never hardcoded. Assets::ProbeEnhancedResourcesAt
        // already searches the game-root developer deployment, addon/, mods/,
        // packaged_mods/ and Steam Workshop content and returns whichever one
        // validated; this registers exactly that.
        //
        // The group is private on purpose. The game clears and re-initialises
        // "Modable" on every mod staging cycle (see
        // reverse_engineering/standalone_enhanced_resource_bootstrap_20260825.md
        // section 2.2), which would drop OpenShim's payload mid-session.

        namespace Boot = EnhancedBootstrap;

        // Defined with the synthesis refusal policy below; the
        // bootstrap needs it to verify the payload really parsed.
        bool GuardedProgramExists(const std::string* name);

        using FnRgmGetSingletonPtr = void* (*)();
        using FnRgmGroupExists = bool(__thiscall*)(void*, const std::string&);
        using FnRgmCreateGroup =
            void(__thiscall*)(void*, const std::string&, bool);
        using FnRgmAddLocation = void(__thiscall*)(void*, const std::string&,
                                                   const std::string&,
                                                   const std::string&, bool,
                                                   bool);
        using FnRgmInitialiseGroup =
            void(__thiscall*)(void*, const std::string&);

        struct OgreResourceGroupApi
        {
            FnRgmGetSingletonPtr getSingleton = nullptr;
            FnRgmGroupExists groupExists = nullptr;
            FnRgmCreateGroup createGroup = nullptr;
            FnRgmAddLocation addLocation = nullptr;
            FnRgmInitialiseGroup initialiseGroup = nullptr;

            bool Valid() const
            {
                return getSingleton != nullptr && groupExists != nullptr &&
                       createGroup != nullptr && addLocation != nullptr &&
                       initialiseGroup != nullptr;
            }
        };

        // Same export names bzr_hooks.cpp already uses for the chunk payload
        // roots; this deliberately reuses that proven surface rather than
        // introducing a second ABI wrapper for the same manager.
        const OgreResourceGroupApi& ResourceGroupApi()
        {
            static const OgreResourceGroupApi api = [] {
                OgreResourceGroupApi resolved;
                resolved.getSingleton =
                    ResolveOgreExport<FnRgmGetSingletonPtr>(
                        "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
                resolved.groupExists = ResolveOgreExport<FnRgmGroupExists>(
                    "?resourceGroupExists@ResourceGroupManager@Ogre@@QAE_NABV?$"
                    "basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                resolved.createGroup = ResolveOgreExport<FnRgmCreateGroup>(
                    "?createResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$"
                    "basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
                resolved.addLocation = ResolveOgreExport<FnRgmAddLocation>(
                    "?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$"
                    "basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
                resolved.initialiseGroup =
                    ResolveOgreExport<FnRgmInitialiseGroup>(
                        "?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$"
                        "basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                return resolved;
            }();
            return api;
        }

        std::atomic<int> s_enhancedBootstrapState {
            static_cast<int>(Boot::BootstrapState::NotAttempted) };

        bool RegisterEnhancedResourceGroup(const std::string& resourceDir,
                                           std::string& outDetail)
        {
            const OgreResourceGroupApi& api = ResourceGroupApi();
            void* manager = api.getSingleton();
            if (manager == nullptr)
            {
                outDetail = "ResourceGroupManager singleton not up yet";
                return false;
            }
            const std::string group = Boot::ResourceGroupName();
            const std::string type = Boot::ResourceLocationType();
            try
            {
                if (!api.groupExists(manager, group))
                {
                    api.createGroup(manager, group, false);
                }
                // recursive=true so the payload's subdirectories are indexed;
                // readOnly=true because OpenShim never writes into it.
                api.addLocation(manager, resourceDir, type, group, true, true);
                api.initialiseGroup(manager, group);
                return true;
            }
            catch (...)
            {
                outDetail = "exception while registering the resource location";
                return false;
            }
        }

        // Idempotent. Runs at most once per process: a failure is as final as
        // a success, so nothing here can repeat per draw or per material.
        Boot::BootstrapState EnsureEnhancedResourceGroup()
        {
            int expected = static_cast<int>(Boot::BootstrapState::NotAttempted);
            if (!s_enhancedBootstrapState.compare_exchange_strong(
                    expected,
                    static_cast<int>(Boot::BootstrapState::Attempting),
                    std::memory_order_acq_rel,
                    std::memory_order_acquire))
            {
                return static_cast<Boot::BootstrapState>(expected);
            }

            Boot::BootstrapObservations obs;
            std::string detail;
            std::string resolvedDir;

            const std::filesystem::path gameDir = GetMainModuleDirectory();
            if (gameDir.empty())
            {
                detail = "main module directory unknown";
            }
            else
            {
                std::string problem;
                std::filesystem::path resourceDir;
                if (Assets::ProbeEnhancedResourcesAt(gameDir, problem,
                                                     &resourceDir) &&
                    !resourceDir.empty())
                {
                    obs.probeResolvedDirectory = true;
                    resolvedDir = resourceDir.string();
                }
                else
                {
                    detail = problem.empty() ? "no OpenShim asset package found"
                                             : problem;
                }
            }

            if (obs.probeResolvedDirectory)
            {
                obs.ogreApiResolved = ResourceGroupApi().Valid();
                if (!obs.ogreApiResolved)
                {
                    detail = "ResourceGroupManager exports unavailable";
                }
                else
                {
                    obs.groupRegistered =
                        RegisterEnhancedResourceGroup(resolvedDir, detail);
                }
            }

            if (obs.groupRegistered)
            {
                // Creating and initialising a group succeeds just as happily
                // for an empty or wrong directory, so prove one real program
                // is actually there before claiming the capability.
                const std::string canonical = Boot::CanonicalProbeProgram();
                obs.canonicalProgramResolved = GuardedProgramExists(&canonical);
                if (!obs.canonicalProgramResolved)
                {
                    detail = "payload parsed no OSE programs";
                }
            }

            const Boot::BootstrapState decided = Boot::DecideBootstrapState(obs);
            s_enhancedBootstrapState.store(static_cast<int>(decided),
                                           std::memory_order_release);
            if (decided == Boot::BootstrapState::Ready)
            {
                LogShimA(LogLevel::Info, kLogTag, "%s",
                         Boot::FormatBootstrapReadyLog(resolvedDir).c_str());
            }
            else
            {
                // One concise diagnostic; the dependent path stays disabled and
                // the game continues normally.
                LogShimA(LogLevel::Warn, kLogTag, "%s",
                         Boot::FormatBootstrapFailedLog(obs, detail).c_str());
            }
            return decided;
        }

        bool EnhancedResourcesAvailable()
        {
            return Boot::IsEnhancedCapabilityAvailable(
                static_cast<Boot::BootstrapState>(
                    s_enhancedBootstrapState.load(std::memory_order_acquire)));
        }

        // ---- synthesis refusal policy and diagnostics ----------------------

        // Sentinel for a material whose Resource::getName could not be read.
        // Not cosmetic: on the live DX11 run the one material that took the
        // process down logged exactly this, and a pointer whose name cannot be
        // read is a pointer that must not be mutated.
        constexpr const char* kUnknownMaterial = "<unknown>";

        // How far a synthesis attempt got. A single opaque "failed" line hid
        // the real cause for several live runs; naming the last completed
        // mutation step is what identified it.
        enum SynthStage : int
        {
            kStageEntry = 0,
            kStageCreated,
            kStageAssigned,
            kStageSchemed,
            kStageLodSet,
            kStagePassFetched,
            kStagePrograms,
            kStageReloaded,
            kStageDone,
        };

        const char* SynthStageName(int stage)
        {
            switch (stage)
            {
            case kStageEntry: return "entry";
            case kStageCreated: return "createTechnique";
            case kStageAssigned: return "technique-assign";
            case kStageSchemed: return "setSchemeName";
            case kStageLodSet: return "setLodIndex";
            case kStagePassFetched: return "getPass";
            case kStagePrograms: return "setProgram";
            case kStageReloaded: return "material-reload";
            case kStageDone: return "done";
            default: return "unknown";
            }
        }

        // Refuse a material this layer cannot identify or must not touch.
        bool IsSynthesisTarget(const std::string& materialName,
                               const Dx11Compat::LegacyPassDesc& desc,
                               const char* pathLabel)
        {
            if (materialName.empty() || materialName == kUnknownMaterial)
            {
                LogCompatOnce(std::string("[DX11COMPAT] ") + pathLabel +
                                  " declined: material name unreadable; "
                                  "refusing to mutate an unidentified material",
                              LogLevel::Warn);
                return false;
            }
            if (Dx11Compat::IsExcludedFromSynthesis(materialName, desc))
            {
                LogCompatOnce(std::string("[DX11COMPAT] ") + pathLabel +
                                  " declined material=" + materialName +
                                  " reason=excluded-class",
                              LogLevel::Info);
                return false;
            }
            return true;
        }

        // Does a GPU program of this name actually exist?
        //
        // Pass::setVertexProgram resolves the name through GpuProgramManager,
        // which checks HighLevelGpuProgramManager first for the hlsl/glsl/
        // unified declarations loaded from .program scripts, and throws
        // ItemIdentityException on a miss. Catching that after the fact is not
        // good enough -- Ogre has already allocated a GpuProgramUsage on the
        // pass, leaving the material half-mutated.
        using FnHighLevelGpuProgramManagerGetSingletonPtr = void* (*)();
        using FnResourceManagerResourceExists =
            bool(__thiscall*)(void*, const std::string&);

        struct OgreProgramLookupApi
        {
            FnHighLevelGpuProgramManagerGetSingletonPtr getManager = nullptr;
            FnResourceManagerResourceExists resourceExists = nullptr;

            bool Valid() const
            {
                return getManager != nullptr && resourceExists != nullptr;
            }
        };

        // Resolved outside any guarded core: a function-local static carries a
        // thread-safe initialization guard, which counts as object unwinding
        // and __try forbids it (C2712).
        const OgreProgramLookupApi& ProgramLookupApi()
        {
            static const OgreProgramLookupApi api = [] {
                OgreProgramLookupApi resolved;
                // .program declarations create HighLevelGpuProgram resources
                // (hlsl/glsl/unified). GpuProgramManager::getByName delegates
                // to this manager, but ResourceManager::resourceExists called
                // on GpuProgramManager only inspects its low-level map. Using
                // the low-level singleton here therefore reported every parsed
                // OSE program absent even though Pass::setProgramName could
                // resolve it through the high-level manager.
                resolved.getManager =
                    ResolveOgreExport<FnHighLevelGpuProgramManagerGetSingletonPtr>(
                        "?getSingletonPtr@HighLevelGpuProgramManager@Ogre@@SAPAV12@XZ");
                // "UAE": resourceExists is virtual and non-const in 1.10.
                resolved.resourceExists =
                    ResolveOgreExport<FnResourceManagerResourceExists>(
                        "?resourceExists@ResourceManager@Ogre@@UAE_NABV?$basic_"
                        "string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                return resolved;
            }();
            return api;
        }

        bool GuardedProgramExists(const std::string* name)
        {
            const OgreProgramLookupApi& api = ProgramLookupApi();
            if (name == nullptr || name->empty() || !api.Valid())
            {
                return false;
            }
            try
            {
                void* manager = api.getManager();
                if (manager == nullptr)
                {
                    return false;
                }
                return api.resourceExists(manager, *name);
            }
            catch (...)
            {
                return false;
            }
        }

        void* InstantiateDx11CompatTechnique(
            void* material,
            void* sourceTechnique,
            const std::string& schemeName,
            unsigned short lodIndex,
            Dx11Compat::CompatPath path,
            const Dx11Compat::LegacyPassDesc& desc,
            const std::string& materialName)
        {
            if (material == nullptr || sourceTechnique == nullptr)
            {
                return nullptr;
            }

            const OgreCompatPassApi& inspect = CompatPassApi();
            const OgreCompatMutationApi& mutate = CompatMutationApi();
            const OgreTechniqueApi& techApi = TechniqueApi();
            if (!inspect.CanInspect() || !mutate.CanInstantiate() ||
                !techApi.Valid())
            {
                return nullptr;
            }

            // First implementation slice: one-pass techniques only. The clone
            // is deep, so all render state and texture units survive unchanged;
            // multi-pass conversion needs per-pass classification before it is
            // safe to retarget and is deliberately left for the next slice.
            if (GuardedGetNumPasses(inspect.getNumPasses, sourceTechnique) != 1)
            {
                return nullptr;
            }

            std::string targetVs;
            std::string targetPs;
            // ResolveCompatPrograms is stage-explicit. The older
            // MapLegacyFamilyProgram infers vertex-vs-fragment from the
            // spelling, which is right for "Effect_vertexHLSL" and wrong
            // for a stage-agnostic family name -- there it falls through to
            // the fragment adapter, and binding a fragment adapter as a
            // vertex program is silently fatal on D3D11. It also guarantees
            // both stages are filled, since a pass with one stage bound and
            // the other empty is the shaderless draw this ladder exists to
            // remove.
            if (!Dx11Compat::ResolveCompatPrograms(path, desc, targetVs,
                                                   targetPs))
            {
                return nullptr;
            }

            // Everything below this point mutates a live material, so every
            // refusal belongs above it.
            if (!IsSynthesisTarget(materialName, desc, "instantiate"))
            {
                return nullptr;
            }
            if (!GuardedProgramExists(&targetVs) ||
                !GuardedProgramExists(&targetPs))
            {
                // Ask HighLevelGpuProgramManager rather than letting
                // Pass::setVertexProgram throw: by the time it throws, Ogre
                // has already allocated a GpuProgramUsage on the pass, so
                // the material is left half-mutated. On an install without
                // the OpenShim asset package NONE of the OSE_* programs
                // resolve, so this is the common case, not the edge case.
                LogCompatOnce("[DX11COMPAT] instantiate declined material=" +
                                  materialName + " reason=program-absent vs=" +
                                  targetVs + " ps=" + targetPs,
                              LogLevel::Warn);
                return nullptr;
            }

            const unsigned short createdIndex = techApi.getNumTechniques(material);
            void* generated = nullptr;
            int stage = kStageEntry;
            try
            {
                generated = mutate.createTechnique(material);
                if (generated == nullptr)
                {
                    return nullptr;
                }
                stage = kStageCreated;

                // Ogre 1.10's own RTSS uses this exact construction pattern:
                // createTechnique(); *dst = *src; then retarget the clone.
                // Technique::operator= deep-copies every Pass and each Pass
                // deep-copies its TextureUnitStates and render state.
                mutate.assignTechnique(generated, sourceTechnique);
                stage = kStageAssigned;
                mutate.setSchemeName(generated, schemeName);
                stage = kStageSchemed;
                mutate.setLodIndex(generated, lodIndex);
                stage = kStageLodSet;

                void* pass = GuardedGetPass(inspect.getPass, generated, 0);
                if (pass == nullptr)
                {
                    RestoreMaterialAfterCompatFailure(material, createdIndex);
                    return nullptr;
                }

                stage = kStagePassFetched;
                mutate.setVertexProgram(pass, targetVs, true);
                mutate.setFragmentProgram(pass, targetPs, true);
                stage = kStagePrograms;

                // setSchemeName/setProgram call _notifyNeedsRecompile(), which
                // unloads a loaded Material. Resource::load(false) is therefore
                // not optional bookkeeping: prepareImpl recompiles the Material,
                // rebuilds mSupportedTechniques / scheme+LOD lookup, and loadImpl
                // loads the newly referenced SM4 programs before we hand Ogre the
                // generated Technique from handleSchemeNotFound.
                mutate.loadResource(material, false);
                stage = kStageReloaded;

                if (!techApi.isSupported(generated))
                {
                    RestoreMaterialAfterCompatFailure(material, createdIndex);
                    LogCompatOnce("[DX11COMPAT] instantiate failed material=" +
                                      materialName + " scheme=" + schemeName +
                                      " lastStage=" + SynthStageName(stage) +
                                      " reason=unsupported-after-reload",
                                  LogLevel::Warn);
                    return nullptr;
                }
                stage = kStageDone;
                return generated;
            }
            catch (...)
            {
                if (generated != nullptr)
                {
                    RestoreMaterialAfterCompatFailure(material, createdIndex);
                }
                // One opaque "failed" line is what hid the real cause for
                // several live runs; naming the stage is what pinned it.
                LogCompatOnce("[DX11COMPAT] instantiate failed material=" +
                                  materialName + " scheme=" + schemeName +
                                  " lastStage=" + SynthStageName(stage),
                              LogLevel::Warn);
                return nullptr;
            }
        }

        void* ProbeDx11LegacyCompat(const std::string& schemeName,
                                    void* material,
                                    unsigned short lodIndex)
        {
            // DX9 untouched by construction.
            if (!s_detectedDx11Atomic.load(std::memory_order_acquire))
            {
                return nullptr;
            }
            const Dx11Compat::CompatConfig config = CurrentCompatConfig();
            if (!config.compatEnabled && !config.guardEnabled)
            {
                return nullptr;
            }
            const bool filesValid =
                s_resourcesValidAtomic.load(std::memory_order_acquire);
            const bool bootstrapReady = EnhancedResourcesAvailable();
            if (!filesValid || !bootstrapReady)
            {
                CompatProbeState& state = ProbeState();
                if (!state.resourcesWarned.exchange(true,
                                                    std::memory_order_acq_rel))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "[DX11COMPAT] probe disabled: renderer files=%s "
                             "OSE-bootstrap=%s; failing closed to stock fallback",
                             filesValid ? "valid" : "invalid",
                             Boot::BootstrapStateName(
                                 static_cast<Boot::BootstrapState>(
                                     s_enhancedBootstrapState.load(
                                         std::memory_order_acquire))));
                }
                return nullptr;
            }

            const OgreTechniqueApi& techApi = TechniqueApi();
            if (!techApi.Valid())
            {
                return nullptr;
            }
            if (!CompatPassApi().CanInspect())
            {
                CompatProbeState& state = ProbeState();
                if (!state.apiWarned.exchange(true, std::memory_order_acq_rel))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "[DX11COMPAT] pass-inspection ABI unavailable; "
                             "compat probe fails closed to stock fallback");
                }
                return nullptr;
            }

            std::string materialName(kUnknownMaterial);
            {
                std::string probed;
                if (GuardedCopyResourceName(material, &probed) && !probed.empty())
                {
                    materialName = probed;
                }
            }

            // Collect every technique as a semantic-source candidate, even
            // unsupported ones: the generator still needs the best template.
            std::vector<Dx11Compat::TechniqueCandidate> candidates;
            const unsigned short count =
                techApi.getNumTechniques(material);
            for (unsigned short i = 0; i < count; ++i)
            {
                void* technique = techApi.getTechnique(material, i);
                if (technique == nullptr)
                {
                    continue;
                }
                Dx11Compat::TechniqueCandidate c;
                c.scheme = std::string(techApi.getSchemeName(technique));
                c.lod = techApi.getLodIndex(technique);
                c.index = static_cast<size_t>(i);
                c.supported = techApi.isSupported(technique);
                candidates.push_back(std::move(c));
            }
            if (candidates.empty())
            {
                return nullptr;
            }

            const size_t sourceIndex =
                Dx11Compat::SelectSourceTechniqueIndex(candidates, schemeName,
                                                       lodIndex);
            if (sourceIndex == Dx11Compat::kNoSourceTechnique)
            {
                return nullptr;
            }
            void* sourceTechnique = nullptr;
            std::string sourceScheme("default");
            for (const auto& c : candidates)
            {
                if (c.index == sourceIndex)
                {
                    sourceTechnique = techApi.getTechnique(
                        material, static_cast<unsigned short>(c.index));
                    sourceScheme = c.scheme.empty() ? "default" : c.scheme;
                    break;
                }
            }

            Dx11Compat::LegacyPassDesc desc = DescribeFirstPass(sourceTechnique);
            const Dx11Compat::LegacyPassKind kind =
                Dx11Compat::ClassifyLegacyPass(desc);
            const Dx11Compat::CompatPath path =
                Dx11Compat::DecideCompatPath(kind, desc, config, true);

            char sourceLabel[192] = {};
            snprintf(sourceLabel, sizeof(sourceLabel), "%s/%zu",
                     sourceScheme.c_str(), sourceIndex);
            const std::string cacheKey = Dx11Compat::BuildCompatCacheKey(
                materialName, schemeName, lodIndex, sourceIndex,
                Dx11Compat::CompatPathName(path));
            const bool cached = NoteCompatCacheKey(cacheKey);

            // A miss may be evaluated many times in one frame. Reserve the
            // cache key before mutation so a failed conversion also cannot
            // synthesize one Technique per draw.
            if (cached && path != Dx11Compat::CompatPath::KeepNative)
            {
                return nullptr;
            }

            CompatProbeState& state = ProbeState();
            switch (path)
            {
            case Dx11Compat::CompatPath::KeepNative:
                state.nativeSupported.fetch_add(1, std::memory_order_relaxed);
                break;
            case Dx11Compat::CompatPath::FamilyRemap:
            {
                state.familyRemaps.fetch_add(1, std::memory_order_relaxed);
                std::string mappedVs;
                std::string mappedPs;
                std::string family("legacy");
                if (!desc.vertexProgram.empty() &&
                    Dx11Compat::MapLegacyFamilyProgram(desc.vertexProgram,
                                                       mappedVs))
                {
                    family = desc.vertexProgram;
                }
                else if (!desc.fragmentProgram.empty() &&
                         Dx11Compat::MapLegacyFamilyProgram(desc.fragmentProgram,
                                                            mappedPs))
                {
                    family = desc.fragmentProgram;
                }
                LogCompatOnce(Dx11Compat::FormatFamilyRemapLog(
                                  materialName, family, desc.vertexProgram,
                                  desc.fragmentProgram),
                              LogLevel::Info);
                void* generated = InstantiateDx11CompatTechnique(
                    material, sourceTechnique, schemeName, lodIndex, path, desc,
                    materialName);
                if (generated != nullptr)
                {
                    LogCompatOnce(Dx11Compat::FormatCompatAppliedLog(
                                      materialName, sourceLabel, path, false),
                                  LogLevel::Info);
                    return generated;
                }
                LogCompatOnce(
                    "[DX11COMPAT] instantiation failed material=" + materialName +
                        " path=family-remap action=stock-fallback",
                    LogLevel::Warn);
                break;
            }
            case Dx11Compat::CompatPath::FixedFuncTextured:
            case Dx11Compat::CompatPath::FixedFuncUntextured:
            {
                state.fixedFunc.fetch_add(1, std::memory_order_relaxed);
                void* generated = InstantiateDx11CompatTechnique(
                    material, sourceTechnique, schemeName, lodIndex, path, desc,
                    materialName);
                if (generated != nullptr)
                {
                    LogCompatOnce(Dx11Compat::FormatCompatAppliedLog(
                                      materialName, sourceLabel, path, false),
                                  LogLevel::Info);
                    return generated;
                }
                LogCompatOnce(
                    "[DX11COMPAT] instantiation failed material=" + materialName +
                        " path=" + Dx11Compat::CompatPathName(path) +
                        " action=stock-fallback",
                    LogLevel::Warn);
                break;
            }
            case Dx11Compat::CompatPath::AggressiveGeneric:
                state.aggressive.fetch_add(1, std::memory_order_relaxed);
                LogCompatOnce(Dx11Compat::FormatUnsupportedLog(
                                  materialName, desc.vertexProgram,
                                  desc.fragmentProgram, true),
                              LogLevel::Warn);
                break;
            case Dx11Compat::CompatPath::SkipShaderless:
            default:
                if (kind == Dx11Compat::LegacyPassKind::UnknownCustom)
                {
                    state.unsupported.fetch_add(1, std::memory_order_relaxed);
                    if (config.guardEnabled)
                    {
                        LogCompatOnce(Dx11Compat::FormatUnsupportedLog(
                                          materialName, desc.vertexProgram,
                                          desc.fragmentProgram, false),
                                      LogLevel::Warn);
                    }
                }
                else
                {
                    state.unsupported.fetch_add(1, std::memory_order_relaxed);
                    if (config.guardEnabled)
                    {
                        LogCompatOnce(Dx11Compat::FormatShaderlessSkippedLog(
                                          materialName,
                                          static_cast<unsigned>(sourceIndex),
                                          0u, desc.vertexProgram,
                                          desc.fragmentProgram),
                                      LogLevel::Warn);
                    }
                }
                if (config.guardEnabled)
                {
                    state.skipped.fetch_add(1, std::memory_order_relaxed);
                }
                break;
            }
            return nullptr;
        }

        class EnhancedSchemeFallbackListener
        {
        public:
            // Ogre::MaterialManager::Listener vtable order in 1.10: virtual
            // destructor, handleSchemeNotFound, afterIlluminationPassesCreated,
            // beforeIlluminationPassesCleared. Both illumination hooks return
            // bool ("notification handled") in 1.10, not void; declaring them
            // keeps this object's vtable the right shape even though Ogre only
            // calls them for runtime-generated techniques.
            virtual ~EnhancedSchemeFallbackListener() {}

            virtual void* handleSchemeNotFound(unsigned short /*schemeIndex*/,
                                               const std::string& schemeName,
                                               void* originalMaterial,
                                               unsigned short lodIndex,
                                               const void* /*renderable*/)
            {
                void* base = ResolveBaseSchemeTechnique(schemeName,
                                                        originalMaterial,
                                                        lodIndex);
                if (base != nullptr)
                {
                    ProbeState().nativeSupported.fetch_add(
                        1, std::memory_order_relaxed);
                    return base;
                }
                // No supported technique exists: DX11 legacy compatibility
                // ladder (fixed function + known SM2/SM3 families). The probe
                // may synthesize one cached SM4 Technique and return it
                // directly, matching Ogre RTSS's handleSchemeNotFound pattern.
                return ProbeDx11LegacyCompat(schemeName, originalMaterial,
                                             lodIndex);
            }

            virtual bool afterIlluminationPassesCreated(void* /*technique*/)
            {
                return false;
            }

            virtual bool beforeIlluminationPassesCleared(void* /*technique*/)
            {
                return false;
            }
        };

        bool InstallEnhancedSchemeFallbackListener()
        {
            const FnMaterialManagerGetSingletonPtr getMaterialManager =
                ResolveOgreExport<FnMaterialManagerGetSingletonPtr>(
                    "?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            const FnMaterialManagerAddListener addListener =
                ResolveOgreExport<FnMaterialManagerAddListener>(
                    "?addListener@MaterialManager@Ogre@@UAEXPAVListener@12@ABV?"
                    "$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            if (getMaterialManager == nullptr || addListener == nullptr ||
                !TechniqueApi().Valid())
            {
                return false;
            }

            void* const materialManager = getMaterialManager();
            if (materialManager == nullptr)
            {
                return false;
            }

            static EnhancedSchemeFallbackListener s_listener;
            // A blank scheme name registers a GENERIC listener. Ogre consults
            // scheme-specific listeners first, then the generic list, taking the
            // first non-null technique -- so this adds to the chain rather than
            // displacing anything the game or a mod installed.
            const std::string anyScheme;
            addListener(materialManager, &s_listener, anyScheme);

            // Ogre's Root and ResourceGroupManager are definitely up by
            // the time MaterialManager hands out a singleton, so this is
            // the earliest safe point to register OpenShim's own payload.
            // Idempotent: it runs at most once per process.
            EnsureEnhancedResourceGroup();
            return true;
        }

        void EnsureEnhancedSchemeFallbackInstalled()
        {
            static bool s_settled = false;
            if (s_settled)
            {
                return;
            }

            if (!s_enhancedSchemeFallbackEnabled.load(std::memory_order_acquire))
            {
                s_settled = true;
                LogShimA(LogLevel::Info, kLogTag,
                         "enhanced scheme fallback disabled by configuration");
                return;
            }

            // Bounded retry, then settle for good. This runs from the engine's
            // ~1 Hz settings-reassert loop; a resolve-if-null retry with no
            // latch would re-probe a bad export name for the life of the
            // process. The budget only covers the window where Ogre's
            // MaterialManager singleton might not exist yet.
            static int s_attemptsLeft = 16;
            if (InstallEnhancedSchemeFallbackListener())
            {
                s_settled = true;
                LogShimA(LogLevel::Info, kLogTag,
                         "enhanced scheme fallback installed "
                         "(en-/og- scheme miss resolves to the base technique)");
                return;
            }

            if (--s_attemptsLeft <= 0)
            {
                s_settled = true;
                LogShimA(LogLevel::Warn, kLogTag,
                         "enhanced scheme fallback unavailable; materials without "
                         "enhanced techniques keep Ogre's first-technique fallback");
            }
        }

        void __fastcall ViewportSetMaterialSchemeHookImpl(void* viewport,
                                                          void* /*edx*/,
                                                          const std::string* scheme)
        {
            const FnViewportSetMaterialScheme original = OriginalSetMaterialSchemeFromIat();

            // The engine calls this from its own render thread, both on
            // viewport creation and on the ~1 Hz reassert loop, which is
            // exactly where Ogre state may be touched safely.
            EnsureEnhancedSchemeFallbackInstalled();

            const char* incomingRaw = (scheme != nullptr) ? scheme->c_str() : "";
            const std::string_view incoming(incomingRaw);

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
                    // Rate-limited visibility: one line per distinct final
                    // scheme, not per call (~1 Hz reassert loop otherwise).
                    // Held as std::string so the comparison can never read
                    // past the logical end of either side.
                    static std::string s_lastLogged;
                    if (s_lastLogged != finalScheme)
                    {
                        s_lastLogged = finalScheme;
                        LogShimA(LogLevel::Info, kLogTag,
                                 "scheme rewrite incoming=%hs final=%hs",
                                 incomingRaw,
                                 finalScheme.c_str());
                    }
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

            // Deferred-profile drain. Ogre state must only be mutated from the
            // game/render thread, so off-thread requesters (backend observation,
            // companion bridge) publish s_reapplyPending and THIS hook — which
            // the engine invokes on its own thread via the ~1 Hz settings-
            // reassert loop and viewport creation — performs the actual
            // viewport/compositor application here. The reapply path calls
            // Ogre exports directly (not this IAT site), so no recursion.
            //
            // Snapshot BEFORE consuming: everything published up to now is
            // covered by this pass. A publish racing in after the snapshot is
            // simply drained by the next call instead (under-report, never
            // over-report).
            if (s_reapplyPending.exchange(false, std::memory_order_acq_rel))
            {
                const uint64_t coveredEpoch = s_applyTracker.SnapshotPublished();
                if (ReapplyEffectiveProfileToViewports("deferred apply"))
                {
                    s_applyTracker.MarkApplied(coveredEpoch);
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

            constexpr size_t kSchemeCallSiteCount =
                sizeof(kSchemeCallSites) / sizeof(kSchemeCallSites[0]);

            // Phase 1: make EVERY site writable before touching ANY bytes. A
            // protection failure past the first site must not leave earlier
            // sites redirected while later ones still call the import table
            // (the partial-ownership state this function exists to prevent).
            DWORD oldProtect[kSchemeCallSiteCount] = {};
            size_t protectedCount = 0;
            for (; protectedCount < kSchemeCallSiteCount; ++protectedCount)
            {
                const SchemeCallSite& site = kSchemeCallSites[protectedCount];
                uint8_t* target = reinterpret_cast<uint8_t*>(site.address);
                if (!VirtualProtect(target, 6, PAGE_EXECUTE_READWRITE,
                                    &oldProtect[protectedCount]))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "scheme takeover skipped: VirtualProtect failed at 0x%08X err=%lu",
                             static_cast<uint32_t>(site.address),
                             static_cast<unsigned long>(GetLastError()));
                    break;
                }
            }
            if (protectedCount < kSchemeCallSiteCount)
            {
                // Nothing was written yet; undo the protections already taken.
                for (size_t i = 0; i < protectedCount; ++i)
                {
                    DWORD ignored = 0;
                    VirtualProtect(reinterpret_cast<uint8_t*>(
                                       kSchemeCallSites[i].address),
                                   6, oldProtect[i], &ignored);
                }
                return false;
            }

            // Phase 2: every target page is writable, so these writes cannot
            // fail on protection; no partial-write rollback is possible.
            // Keep FF 15; replace only the displacement so the instruction
            // calls through our pointer cell instead of the import table.
            // The IAT entry stays pristine and remains how we invoke the
            // real function from inside the hook.
            for (const SchemeCallSite& site : kSchemeCallSites)
            {
                uint8_t* target = reinterpret_cast<uint8_t*>(site.address);
                std::memcpy(target + 2, &operandValue, sizeof(operandValue));
                FlushInstructionCache(GetCurrentProcess(), target + 2,
                                      sizeof(operandValue));
                LogShimA(LogLevel::Info, kLogTag,
                         "scheme takeover installed at 0x%08X (%s)",
                         static_cast<uint32_t>(site.address), site.identity);
            }

            // Phase 3: restore the original page protections.
            for (size_t i = 0; i < kSchemeCallSiteCount; ++i)
            {
                DWORD ignored = 0;
                VirtualProtect(reinterpret_cast<uint8_t*>(
                                   kSchemeCallSites[i].address),
                               6, oldProtect[i], &ignored);
            }

            s_schemeTakeoverInstalled.store(true, std::memory_order_release);
            return true;
        }

        // ---- active-viewport application API --------------------------------
        //
        // Export resolution and SEH-free wrappers; the guarded cores live in
        // small noinline POD-only functions below.

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

    // Returns true when at least one active viewport was found and processed;
    // false means "nothing to apply to" (the request stays deferred from the
    // ABI's point of view).
    bool ReapplyEffectiveProfileToViewports(const char* context)
    {
        void* viewports[4] = {};
        const size_t count = CollectActiveViewports(viewports, 4);
        if (count == 0)
        {
            return false;
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
        return true;
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
        // The companion bridge can be called from any thread; defer the Ogre
        // mutation to the game/render-thread scheme hook.
        PublishReapplyPending();
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
            PublishReapplyPending();
        }
    }

    void ReloadRenderProfileConfig()
    {
        AcquireSRWLockExclusive(&s_stateLock);
        LoadConfigLocked();
        ResolveAndPublishLocked("ini reload");
        ReleaseSRWLockExclusive(&s_stateLock);
        PublishReapplyPending();
    }

    // Public Seam A entry point (see header). Called ONCE from DllMain
    // (DLL_PROCESS_ATTACH); performs only loader-lock-bounded work: identity
    // checks plus a single protected IAT pointer swap. The backend transport
    // itself runs later, on the game thread, from inside the intercepted
    // startup Ogre::ConfigFile::load. Idempotent.

    void InitializeOgreRenderProfiles()
    {
        static bool s_initialized = false;
        if (s_initialized)
        {
            return;
        }
        s_initialized = true;

        // The arm attempt ran under the loader lock and deliberately emitted
        // no normal logger traffic there. Report its fixed status now from the
        // patch thread, where logger locks/CRT work are safe.
        // The arm and the whole startup transport belong to the bootstrap
        // seam now (src/engine/startup_backend_seam.cpp); it has already run
        // by the time this executes. Read its published result rather than
        // recomputing what happened.
        const StartupSeam::StartupRendererResult* startup =
            StartupSeam::GetStartupRendererResult();
        const char* armText = StartupSeam::ArmStatusText();
        const bool armed = startup != nullptr && startup->seamArmed != 0;
        LogShimA(
            armed ? LogLevel::Info : LogLevel::Warn,
            kLogTag,
            "backend seam arm status=%s; %s",
            armText != nullptr ? armText : "unknown",
            armed ? "startup ConfigFile::load interception active"
                  : "stock renderer selection remains authoritative");

        AcquireSRWLockExclusive(&s_stateLock);
        LoadConfigLocked();
        // s_bootRequest and s_transportWrittenThisBoot describe what the
        // bootstrap already decided and did. Seeding them from the record is
        // the whole point of the split: the runtime must not independently
        // re-derive a decision that was made before it existed.
        if (startup != nullptr && startup->selectionRan != 0)
        {
            s_bootRequest.backend = startup->requested;
            s_bootRequest.source = startup->source;
            s_transportWrittenThisBoot = startup->transportWritten != 0;
        }
        s_resourcesValid = ValidateDeployedResourceSet();
        s_resourcesValidAtomic.store(s_resourcesValid, std::memory_order_release);
        if (!s_resourcesValid)
        {
            LogShimA(LogLevel::Warn, kLogTag,
                     "[DX11COMPAT] compat feature unavailable: renderer resource "
                     "set invalid (see Enhanced resource warning above)");
        }

        // The backend transport does NOT run here: it is triggered
        // synchronously by the intercepted startup ConfigFile::load (armed in
        // DllMain via InstallStartupBackendSeam), which is deterministic even
        // when Steam reaches graphics init in ~1 s. This initializer only
        // prepares profile state and starts the observation worker.

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

            // Truthful unsupported-build reporting: without the scheme-policy
            // layer an Enhanced/Retro request can never drive rendering (the
            // resolver clamps it to Redux). The request is still stored so
            // GetRequestedContentRenderProfile stays coherent; the status
            // tells the companion why it will not apply. Redux/Inherit have
            // no such dependency and always proceed.
            bool schemeLayerActive = false;
            {
                AcquireSRWLockShared(&s_stateLock);
                schemeLayerActive =
                    s_schemeTakeoverInstalled.load(std::memory_order_acquire);
                ReleaseSRWLockShared(&s_stateLock);
            }
            const Profile requestedAsProfile =
                (request == ContentRequest::Enhanced) ? Profile::Enhanced
                : (request == ContentRequest::Retro) ? Profile::Retro
                                                     : Profile::Redux;
            if (!schemeLayerActive && requestedAsProfile != Profile::Redux)
            {
                RequestContentRenderProfile(request, "EXU request");
                return Abi::kRequestStatusUnsupportedBuild;
            }

            // The actual Ogre mutation happens later on the engine thread, so
            // the honest answer right now is StoredDeferred unless a drain
            // covering this publish already completed. Viewport existence is
            // deliberately NOT consulted: it says nothing about whether the
            // deferred apply ran.
            RequestContentRenderProfile(request, "EXU request");
            const uint64_t publishedEpoch =
                s_applyTracker.SnapshotPublished();
            return s_applyTracker.AppliedSince(publishedEpoch)
                ? Abi::kRequestStatusAppliedLive
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

            // Same gate the resolver enforces: Enhanced additionally requires
            // the mandatory resource set, so a deployment with verified
            // scheme hooks but broken/missing renderer files no longer
            // claims Enhanced is usable. Redux stays always-available.
            return ProfileRequirementsMet(profile, mask) ? TRUE : FALSE;
        }
    }
} // namespace BZROpenShim::RenderProfiles

// ---- stable winmm bridge exports --------------------------------------------

extern "C" UINT WINAPI OpenShimImpl_GetRenderApiVersion()
{
    return BZROpenShim::RenderProfiles::Exports::GetRenderApiVersion();
}

extern "C" DWORD WINAPI OpenShimImpl_RequestRenderProfile(DWORD profileRequest)
{
    return BZROpenShim::RenderProfiles::Exports::RequestRenderProfile(profileRequest);
}

extern "C" DWORD WINAPI OpenShimImpl_GetUserRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetUserRenderProfile();
}

extern "C" DWORD WINAPI OpenShimImpl_GetRequestedContentRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetRequestedContentRenderProfile();
}

extern "C" DWORD WINAPI OpenShimImpl_GetEffectiveRenderProfile()
{
    return BZROpenShim::RenderProfiles::Exports::GetEffectiveRenderProfile();
}

extern "C" DWORD WINAPI OpenShimImpl_GetActiveRendererBackend()
{
    return BZROpenShim::RenderProfiles::Exports::GetActiveBackend();
}

extern "C" DWORD WINAPI OpenShimImpl_GetRenderCapabilities()
{
    return BZROpenShim::RenderProfiles::Exports::GetRenderCapabilities();
}

extern "C" BOOL WINAPI OpenShimImpl_SupportsRenderProfile(DWORD profile)
{
    return BZROpenShim::RenderProfiles::Exports::SupportsRenderProfile(profile)
        ? TRUE : FALSE;
}
