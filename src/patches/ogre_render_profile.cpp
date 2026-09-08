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
#include <string>

namespace BZROpenShim::RenderProfiles
{
    // Command-line snapshot. Stock's parser (FUN_007D5120) strtok()s the
    // GetCommandLineA() buffer in place, so tokens after the first NUL it
    // inserts vanish for any later reader; DllMain captures the pristine
    // string before game main can run.
    char s_commandLineSnapshot[1200] = {};

    void CaptureCommandLineSnapshot()
    {
        if (const char* raw = GetCommandLineA())
        {
            strncpy_s(s_commandLineSnapshot, raw, _TRUNCATE);
        }
    }

    const char* GetCapturedCommandLine()
    {
        return s_commandLineSnapshot[0] != '\0' ? s_commandLineSnapshot : nullptr;
    }

    const char* RequestedBackendName(RendererBackend backend)
    {
        return backend == RendererBackend::DX11 ? "DX11"
               : backend == RendererBackend::DX9 ? "DX9"
                                                 : "Auto";
    }


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

        bool FileExistsNonEmpty(const std::filesystem::path& path)
        {
            std::error_code ec;
            return std::filesystem::is_regular_file(path, ec) &&
                   std::filesystem::file_size(path, ec) > 0 && !ec;
        }

        // Marker recording this boot's transport request. Its presence at the
        // NEXT launch proves the previous boot ended without an identified
        // renderer - the only observable signature of the device-init-failure
        // abort path (exit code -1 within seconds of Ogre initialisation).
        std::filesystem::path PendingMarkerPath()
        {
            const std::filesystem::path dir = GetMainModuleDirectory();
            return dir.empty() ? dir : dir / "logs" / "openshim_backend_pending.txt";
        }

        void WritePendingMarker(const char* subsystemName)
        {
            const auto markerDir = PendingMarkerPath().parent_path();
            if (markerDir.empty())
            {
                return;
            }
            std::error_code ec;
            std::filesystem::create_directories(markerDir, ec);
            FILE* file = nullptr;
            if (_wfopen_s(&file, PendingMarkerPath().c_str(), L"wb") != 0 ||
                file == nullptr)
            {
                return;
            }
            fwrite(subsystemName, 1, strlen(subsystemName), file);
            fputc('\n', file);
            fclose(file);
        }

        bool ReadPendingMarker(std::string& outSubsystem)
        {
            FILE* file = nullptr;
            if (_wfopen_s(&file, PendingMarkerPath().c_str(), L"rb") != 0 ||
                file == nullptr)
            {
                return false;
            }
            char buffer[64] = {};
            const size_t read = fread(buffer, 1, sizeof(buffer) - 1, file);
            fclose(file);
            outSubsystem.assign(buffer, read);
            while (!outSubsystem.empty() &&
                   (outSubsystem.back() == '\n' || outSubsystem.back() == '\r'))
            {
                outSubsystem.pop_back();
            }
            return !outSubsystem.empty();
        }

        void ClearPendingMarker()
        {
            std::error_code ec;
            std::filesystem::remove(PendingMarkerPath(), ec);
        }

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
        bool WriteOgreConfigTransport(const char* subsystemName,
                                      std::string& outPreviousValue)
        {
            const std::filesystem::path dir = GetMainModuleDirectory();
            if (dir.empty())
            {
                return false;
            }
            const std::filesystem::path cfgPath = dir / "Ogre.cfg";

            std::error_code ec;
            const bool fileExists =
                std::filesystem::is_regular_file(cfgPath, ec) && !ec;

            std::string text;
            bool haveExistingImage = false;
            if (fileExists)
            {
                FILE* file = nullptr;
                if (_wfopen_s(&file, cfgPath.c_str(), L"rb") != 0 ||
                    file == nullptr)
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend transport: Ogre.cfg unreadable; stock "
                             "selection preserved");
                    return false;
                }
                char buffer[4096];
                size_t got = 0;
                while ((got = fread(buffer, 1, sizeof(buffer), file)) > 0)
                {
                    text.append(buffer, got);
                }
                fclose(file);
                haveExistingImage = !text.empty();
            }

            if (haveExistingImage)
            {
                outPreviousValue.assign(
                    BackendSelection::ExtractStockRenderSystemValue(text));
            }

            std::string updated;
            if (haveExistingImage)
            {
                updated = text;
                if (!BackendSelection::ApplyTransportToConfigImage(
                        updated, subsystemName))
                {
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend transport: Ogre.cfg refused (%zu bytes, "
                             "non-ASCII/empty); stock selection preserved",
                             text.size());
                    return false;
                }
            }
            else
            {
                updated.assign(BackendSelection::BuildMinimalConfigImage(
                    subsystemName));
                if (updated.empty())
                {
                    return false;
                }
            }
            if (haveExistingImage && updated == text)
            {
                return true; // already correct; nothing to write
            }

            // The helper returns ASCII by design (pure/testable); widen it
            // here for the Win32 calls below.
            const std::string tmpName = BackendSelection::MakeTransportTempFileName(
                GetCurrentProcessId());
            const std::filesystem::path tmpPath =
                dir / std::filesystem::path(tmpName.begin(), tmpName.end());
            bool wroteTemp = false;
            FILE* file = nullptr;
            if (_wfopen_s(&file, tmpPath.c_str(), L"wb") != 0 || file == nullptr)
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend transport: temp write failed err=%lu",
                         static_cast<unsigned long>(GetLastError()));
                return false;
            }
            const size_t written = fwrite(updated.data(), 1, updated.size(), file);
            fclose(file);
            wroteTemp = written == updated.size();
            if (!wroteTemp)
            {
                LogShimA(LogLevel::Warn, kLogTag, "backend transport: short write");
                std::filesystem::remove(tmpPath, ec);
                return false;
            }

            if (!MoveFileExW(tmpPath.c_str(), cfgPath.c_str(),
                             MOVEFILE_REPLACE_EXISTING))
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend transport: replace failed err=%lu",
                         static_cast<unsigned long>(GetLastError()));
                std::filesystem::remove(tmpPath, ec);
                return false;
            }

            if (!haveExistingImage)
            {
                LogShimA(LogLevel::Info, kLogTag,
                         "transport.bootstrap: Ogre.cfg absent; created minimal "
                         "%zu-byte config image",
                         updated.size());
            }
            return true;
        }

        // Resolves this boot's backend request and applies the Ogre.cfg
        // transport when an explicit, capability-validated request exists.
        //
        // Caller MUST hold s_stateLock exclusively: this runs inside
        // InitializeOgreRenderProfiles' startup critical section, before the
        // observation thread exists. SRW locks are not recursive, which is why
        // no locking happens in here despite all the s_* state mutation.
        void RunStartupBackendSelection()
        {
            // Previous-boot outcome evidence first: a surviving marker means
            // the last boot ended before any renderer was established (the
            // device-init abort exits the process before observation can
            // report anything).
            std::string pendingSubsystem;
            if (ReadPendingMarker(pendingSubsystem))
            {
                LogShimA(LogLevel::Warn, kLogTag,
                         "previous boot ended before renderer establishment "
                         "(requested=%.*s); possible device-init failure",
                         static_cast<int>(pendingSubsystem.size()),
                         pendingSubsystem.c_str());
            }

            // Launch-scoped CLI override (/renderer:...). Stock parses this
            // itself later; we read the DllMain-captured snapshot because the
            // stock parser strtok()s the PEB command-line buffer in place and
            // would otherwise already have destroyed these tokens for any
            // later reader. We only observe the token here to attribute source
            // and to keep it launch-scoped instead of letting saveConfig
            // absorb it into the persistent preference.
            const char* cmdline = GetCapturedCommandLine();
            if (cmdline == nullptr)
            {
                cmdline = GetCommandLineA(); // DllMain capture missed; best effort
            }
            LogShimA(LogLevel::Info, kLogTag, "cmdline snapshot: %s",
                     cmdline != nullptr ? cmdline : "");
            const auto cliToken =
                BackendSelection::FindCommandLineRendererOverride(cmdline);

            s_bootRequest = BackendSelection::ResolveBootRequest(
                s_requestedBackend, cliToken);

            if (cliToken == BackendSelection::RendererToken::Gl)
            {
                LogShimA(LogLevel::Info, kLogTag,
                         "CLI renderer override gl/opengl recognized but unsupported "
                         "by OpenShim; stock selection preserved");
            }

            const char* subsystemName =
                BackendSelection::SubsystemNameFor(s_bootRequest.backend);

            // Auto request (or explicit GL override): exact stock behavior.
            // Touch nothing; clear stale marker evidence.
            if (s_bootRequest.backend == RendererBackend::Auto)
            {
                s_transportWrittenThisBoot = false;
                LogShimA(LogLevel::Info, kLogTag,
                         "backend.boot: requested=Auto source=stock transport=untouched");
                ClearPendingMarker();
                return;
            }

            // Capability validation BEFORE touching the transport: requesting
            // a backend whose plugin is absent would otherwise let stock's
            // ladder fall back and PERSIST DX9 over our request on this very
            // boot (RE matrix case dx11-plugin-absent). Skipping the write
            // keeps openshim.ini as sole carrier of the user's intent.
            const auto moduleDir = GetMainModuleDirectory();
            const bool dx9Present =
                !moduleDir.empty() &&
                FileExistsNonEmpty(moduleDir / "RenderSystem_Direct3D9.dll");
            const bool dx11Present =
                !moduleDir.empty() &&
                FileExistsNonEmpty(moduleDir / "RenderSystem_Direct3D11.dll");
            LogShimA(LogLevel::Info, kLogTag,
                     "plugins: dx9=%s dx11=%s",
                     dx9Present ? "1" : "0", dx11Present ? "1" : "0");

            const bool pluginPresent =
                s_bootRequest.backend == RendererBackend::DX11 ? dx11Present : dx9Present;
            const char* sourceText =
                s_bootRequest.source == BackendSelection::RequestSource::CliOverride
                    ? "cli-override" : "persistent";

            if (!pluginPresent)
            {
                s_transportWrittenThisBoot = false;
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend.boot: requested=%s source=%s transport=plugin-missing "
                         "(stock fallback expected; persistent preference retained)",
                         RequestedBackendName(s_bootRequest.backend), sourceText);
                return;
            }

            if (!s_backendTransportEnabled)
            {
                s_transportWrittenThisBoot = false;
                LogShimA(LogLevel::Info, kLogTag,
                         "backend.boot: requested=%s source=%s transport=disabled "
                         "([Startup] BackendTransport=0)",
                         RequestedBackendName(s_bootRequest.backend), sourceText);
                ClearPendingMarker();
                return;
            }

            std::string previousValue;
            if (!WriteOgreConfigTransport(subsystemName, previousValue))
            {
                s_transportWrittenThisBoot = false;
                LogShimA(LogLevel::Info, kLogTag,
                         "backend.boot: requested=%s source=%s transport=failed "
                         "(stock selection preserved)",
                         RequestedBackendName(s_bootRequest.backend), sourceText);
                return;
            }

            s_transportWrittenThisBoot = true;
            LogShimA(LogLevel::Info, kLogTag,
                     "transport: Ogre.cfg 'Render System=' '%.*s' -> '%s'",
                     static_cast<int>(previousValue.size()), previousValue.c_str(),
                     subsystemName);
            LogShimA(LogLevel::Info, kLogTag,
                     "backend.boot: requested=%s source=%s transport=written",
                     RequestedBackendName(s_bootRequest.backend), sourceText);
            WritePendingMarker(subsystemName);
        }

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

        constexpr uintptr_t kImageBaseAssumption = 0x00400000u;
        constexpr uintptr_t kConfigFileLoadIatVa = 0x00869D08u;
        constexpr uintptr_t kStartupCfgLoadCallSiteVa = 0x006640E4u;
        constexpr uintptr_t kStartupCfgLoadRetVa =
            kStartupCfgLoadCallSiteVa + 6;
        constexpr uintptr_t kOgreCfgMarkerVa = 0x00892030u;
        constexpr size_t kExpectedMainImageSizeGog = 0x290F000u;
        constexpr size_t kExpectedMainImageSizeSteam = 0x292F000u;
        constexpr char kConfigFileLoadImportName[] =
            "?load@ConfigFile@Ogre@@QAEXABV?$basic_string@"
            "DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z";
        constexpr char kMainModuleName[] = "battlezone98redux.exe";

        using FnConfigFileLoad = void (__fastcall*)(
            void* self, void* edx, const std::string* arg0,
            const std::string* arg1, bool trimWhitespace);

        void __fastcall ConfigFileLoadHookForward(void* self, void* edx,
                                                  const std::string* arg0,
                                                  const std::string* arg1,
                                                  bool trimWhitespace);

        // The patched slot becomes `call [this cell]`; namespace scope so the
        // cell and the function it names outlive the process.
        void* s_hookTrampolineForConfigFileLoad =
            reinterpret_cast<void*>(&ConfigFileLoadHookForward);

        FnConfigFileLoad g_originalConfigFileLoad = nullptr;

        // One-shot latch for the transport attempt. Set immediately before
        // RunStartupBackendSelection executes so even a fault inside the heavy
        // work can never cause a second attempt; validation misses leave it
        // clear because the game reaches the validated call site exactly once.
        std::atomic<bool> s_transportAttempted { false };

        std::atomic<bool> s_seamInstalled { false };

        enum class BackendSeamArmStatus : uint8_t
        {
            NotAttempted,
            Armed,
            NoMainModule,
            UnsupportedExecutable,
            BadDosSignature,
            BadNtSignature,
            UnsupportedImageSize,
            MarkerMismatch,
            OgreMainAbsent,
            ExportAbsent,
            BindingMismatch,
            ProtectFailed,
            SlotWriteFaulted,
        };

        std::atomic<BackendSeamArmStatus> s_seamArmStatus {
            BackendSeamArmStatus::NotAttempted
        };

        bool FailStartupBackendSeamArm(BackendSeamArmStatus status)
        {
            s_seamArmStatus.store(status, std::memory_order_release);
            return false;
        }

        __declspec(noinline) static bool GuardedReadSlotValue(
            const void* slot, void** out)
        {
            __try
            {
                *out = *static_cast<void* const*>(slot);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

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

        __declspec(noinline) static bool GuardedMarkerEquals(
            const void* address, const char* expected, size_t len)
        {
            __try
            {
                return memcmp(address, expected, len) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool EndsWithNoCaseAscii(const wchar_t* text, size_t textLen,
                                 const char* suffix)
        {
            const size_t suffixLen = strlen(suffix);
            if (textLen < suffixLen)
            {
                return false;
            }
            const wchar_t* tail = text + (textLen - suffixLen);
            for (size_t i = 0; i < suffixLen; ++i)
            {
                wchar_t c = tail[i];
                if (c >= L'A' && c <= L'Z')
                {
                    c = static_cast<wchar_t>(c - L'A' + L'a');
                }
                const char lc = (suffix[i] >= 'A' && suffix[i] <= 'Z')
                    ? static_cast<char>(suffix[i] - 'A' + 'a')
                    : suffix[i];
                if (c != static_cast<wchar_t>(lc))
                {
                    return false;
                }
            }
            return true;
        }

        // Loader-lock-bounded install: header/name/export/slot checks plus one
        // protected pointer swap. No CRT containers, no filesystem, no waits,
        // no .text reads and no normal logger calls (Steam-safe at attach
        // time). Failures publish only a fixed enum; the patch thread reports
        // that result later, after DllMain has released the loader lock.
        bool InstallStartupBackendSeamImpl()
        {
            HMODULE mainModule = GetModuleHandleW(nullptr);
            if (mainModule == nullptr)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::NoMainModule);
            }

            wchar_t modulePath[MAX_PATH] = {};
            const DWORD pathLen = GetModuleFileNameW(
                mainModule, modulePath, MAX_PATH);
            if (pathLen == 0 || pathLen >= MAX_PATH ||
                !EndsWithNoCaseAscii(modulePath, pathLen, kMainModuleName))
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::UnsupportedExecutable);
            }

            const auto* dosHeader =
                reinterpret_cast<const IMAGE_DOS_HEADER*>(mainModule);
            if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::BadDosSignature);
            }
            const auto* ntHeaders =
                reinterpret_cast<const IMAGE_NT_HEADERS*>(
                    reinterpret_cast<const uint8_t*>(mainModule) +
                    dosHeader->e_lfanew);
            if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::BadNtSignature);
            }
            const size_t imageOfImage = ntHeaders->OptionalHeader.SizeOfImage;
            if (imageOfImage != kExpectedMainImageSizeGog &&
                imageOfImage != kExpectedMainImageSizeSteam)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::UnsupportedImageSize);
            }
            const uintptr_t imageBase =
                reinterpret_cast<uintptr_t>(mainModule);

            // Plaintext .rdata anchor: proves the data-section layout matches
            // the qualified build regardless of SteamStub state.
            if (!GuardedMarkerEquals(
                    reinterpret_cast<const void*>(imageBase +
                        (kOgreCfgMarkerVa - kImageBaseAssumption)),
                    "Ogre.cfg", sizeof("Ogre.cfg")))
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::MarkerMismatch);
            }

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (ogreMain == nullptr)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::OgreMainAbsent);
            }
            const FARPROC expectedTarget =
                GetProcAddress(ogreMain, kConfigFileLoadImportName);
            if (expectedTarget == nullptr)
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::ExportAbsent);
            }

            void* slotAddress = reinterpret_cast<void*>(
                imageBase + (kConfigFileLoadIatVa - kImageBaseAssumption));
            void* currentBinding = nullptr;
            if (!GuardedReadSlotValue(slotAddress, &currentBinding) ||
                currentBinding != reinterpret_cast<void*>(expectedTarget))
            {
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::BindingMismatch);
            }

            g_originalConfigFileLoad =
                reinterpret_cast<FnConfigFileLoad>(expectedTarget);

            DWORD oldProtect = 0;
            if (!VirtualProtect(slotAddress, sizeof(void*), PAGE_READWRITE,
                                &oldProtect))
            {
                g_originalConfigFileLoad = nullptr;
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::ProtectFailed);
            }
            const bool wrote = GuardedWriteSlotValue(
                slotAddress, s_hookTrampolineForConfigFileLoad);
            DWORD ignored = 0;
            VirtualProtect(slotAddress, sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slotAddress,
                                  sizeof(void*));
            if (!wrote)
            {
                g_originalConfigFileLoad = nullptr;
                return FailStartupBackendSeamArm(
                    BackendSeamArmStatus::SlotWriteFaulted);
            }

            s_seamInstalled.store(true, std::memory_order_release);
            s_seamArmStatus.store(
                BackendSeamArmStatus::Armed, std::memory_order_release);
            return true;
        }

        const char* BackendSeamArmStatusText(BackendSeamArmStatus status)
        {
            switch (status)
            {
            case BackendSeamArmStatus::NotAttempted: return "not-attempted";
            case BackendSeamArmStatus::Armed: return "armed";
            case BackendSeamArmStatus::NoMainModule: return "no-main-module";
            case BackendSeamArmStatus::UnsupportedExecutable: return "unsupported-executable";
            case BackendSeamArmStatus::BadDosSignature: return "bad-dos-signature";
            case BackendSeamArmStatus::BadNtSignature: return "bad-nt-signature";
            case BackendSeamArmStatus::UnsupportedImageSize: return "unsupported-image-size";
            case BackendSeamArmStatus::MarkerMismatch: return "marker-mismatch";
            case BackendSeamArmStatus::OgreMainAbsent: return "ogremain-absent";
            case BackendSeamArmStatus::ExportAbsent: return "config-load-export-absent";
            case BackendSeamArmStatus::BindingMismatch: return "iat-binding-mismatch";
            case BackendSeamArmStatus::ProtectFailed: return "iat-protect-failed";
            case BackendSeamArmStatus::SlotWriteFaulted: return "iat-write-faulted";
            }
            return "unknown";
        }

        // Post-settle call-site proof: the six bytes at the known startup call
        // instruction must still be `call dword ptr [0x00869D08]`. Runs on the
        // game thread, so SteamStub has long since decrypted .text.
        bool ValidateStartupCallSite()
        {
            uint8_t bytes[6] = {};
            SIZE_T read = 0;
            if (!ReadProcessMemory(GetCurrentProcess(),
                                   reinterpret_cast<const void*>(
                                       kStartupCfgLoadCallSiteVa),
                                   bytes, sizeof(bytes), &read) ||
                read != sizeof(bytes))
            {
                return false;
            }
            return bytes[0] == 0xFF && bytes[1] == 0x15 &&
                   bytes[2] == 0x08 && bytes[3] == 0x9D &&
                   bytes[4] == 0x86 && bytes[5] == 0x00;
        }

        void TransportGateImpl(uintptr_t returnAddress, const void* arg0)
        {
            if (returnAddress != kStartupCfgLoadRetVa)
            {
                return; // not the proven startup call site: pass through
            }
            static bool s_loggedSite = false;
            if (!ValidateStartupCallSite())
            {
                if (!s_loggedSite)
                {
                    s_loggedSite = true;
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend seam: startup call-site bytes mismatched "
                             "(unexpected build); stock selection preserved");
                }
                return;
            }
            // Secondary confirmation on the resolved argument: the bootstrap
            // loads Ogre.cfg through its path table, so accept the bare name
            // or any explicit path ending in it.
            const auto* filename = static_cast<const std::string*>(arg0);
            const bool looksLikeStartupCfg =
                filename != nullptr &&
                BackendSelection::IsStartupConfigFilename(*filename);
            if (!looksLikeStartupCfg)
            {
                if (!s_loggedSite)
                {
                    s_loggedSite = true;
                    LogShimA(LogLevel::Warn, kLogTag,
                             "backend seam: startup site reached without an "
                             "Ogre.cfg argument; stock selection preserved");
                }
                return;
            }

            // Consumes the one-shot before any heavy work runs.
            if (s_transportAttempted.exchange(true, std::memory_order_acq_rel))
            {
                return;
            }

            LogShimA(LogLevel::Info, kLogTag,
                     "backend seam triggered at ConfigFile::load('%.*s') ret=0x%08X",
                     static_cast<int>(filename->size()), filename->c_str(),
                     static_cast<uint32_t>(returnAddress));

            AcquireSRWLockExclusive(&s_stateLock);
            // Self-sufficient request resolution: on a fast boot (warm-cache
            // Steam start reaches this load in ~1 s) the hook can fire BEFORE
            // the patch thread reaches InitializeOgreRenderProfiles, so the
            // transport must not assume that initializer already parsed
            // openshim.ini. Loading here is idempotent and cheap.
            LoadConfigLocked();
            RunStartupBackendSelection();
            ReleaseSRWLockExclusive(&s_stateLock);
        }

        // SEH boundary: the forwarder itself holds no unwinding objects, so a
        // fault anywhere in the gate/transport degrades to stock behavior.
        __declspec(noinline) static void GuardedTransportGate(
            uintptr_t returnAddress, const void* arg0)
        {
            __try
            {
                TransportGateImpl(returnAddress, arg0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                s_transportAttempted.store(true, std::memory_order_release);
                LogShimA(LogLevel::Warn, kLogTag,
                         "backend seam: transport faulted; stock selection "
                         "preserved");
            }
        }

        void __fastcall ConfigFileLoadHookForward(void* self, void* edx,
                                                  const std::string* arg0,
                                                  const std::string* arg1,
                                                  bool trimWhitespace)
        {
            if (!s_transportAttempted.load(std::memory_order_acquire))
            {
                const void* retSlot = _AddressOfReturnAddress();
                const uintptr_t returnAddress =
                    *static_cast<const uintptr_t*>(retSlot);
                GuardedTransportGate(returnAddress, arg0);
            }
            const FnConfigFileLoad original = g_originalConfigFileLoad;
            if (original != nullptr)
            {
                original(self, edx, arg0, arg1, trimWhitespace);
            }
        }

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
                    ClearPendingMarker();
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
                ClearPendingMarker();
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

        void __fastcall ViewportSetMaterialSchemeHookImpl(void* viewport,
                                                          void* /*edx*/,
                                                          const std::string* scheme)
        {
            const FnViewportSetMaterialScheme original = OriginalSetMaterialSchemeFromIat();

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
    bool InstallStartupBackendSeam()
    {
        static bool s_attempted = false;
        if (s_attempted)
        {
            return s_seamInstalled.load(std::memory_order_acquire);
        }
        s_attempted = true;
        return InstallStartupBackendSeamImpl();
    }

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
        const BackendSeamArmStatus seamStatus =
            s_seamArmStatus.load(std::memory_order_acquire);
        LogShimA(
            seamStatus == BackendSeamArmStatus::Armed
                ? LogLevel::Info
                : LogLevel::Warn,
            kLogTag,
            "backend seam arm status=%s; %s",
            BackendSeamArmStatusText(seamStatus),
            seamStatus == BackendSeamArmStatus::Armed
                ? "startup ConfigFile::load interception active"
                : "stock renderer selection remains authoritative");

        AcquireSRWLockExclusive(&s_stateLock);
        LoadConfigLocked();
        s_resourcesValid = ValidateDeployedResourceSet();

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
