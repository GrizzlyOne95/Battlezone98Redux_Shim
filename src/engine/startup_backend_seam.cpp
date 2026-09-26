// startup_backend_seam.cpp
// BZR Open Shim - the bootstrap startup renderer seam.
//
// This is deliberately NOT built like the file-I/O seam. There, a missing
// provider can mean "stock for now, the plugin catches up later". Here it
// cannot: the intercepted Ogre::ConfigFile::load is the game's own read of
// Ogre.cfg, and the very next thing the graphics bootstrap does is
// getSetting("Render System"). If the decision has not been made by the time
// this call returns, the decision point is gone for this boot. So the seam is
// self-sufficient -- it resolves the request and writes the transport with no
// plugin loaded at all -- and publishes a POD record that OpenShim reads
// afterwards to seed its runtime state.
//
// The decision core is backend_selection.cpp, which is pure and free of Win32
// and Ogre. Compiling that and render_profile.cpp into the bootstrap is fine:
// they are small and stateless. What the boundary must keep out is the patch
// engine, resolve tables, and mutable renderer runtime state.
//
// Everything below the public entry points was moved out of
// ogre_render_profile.cpp unchanged. The call-site proof in particular -- the
// return-address gate, the six-byte post-SteamStub validation, the Ogre.cfg
// argument check, the one-shot latch and the SEH fail-to-stock behaviour --
// is intact and should stay that way until there is a reason to touch it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "startup_backend_seam.h"

#include "backend_selection.h"
#include "render_profile.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <atomic>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <string_view>

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

    namespace
    {
        constexpr const char* kLogTag = "RENDER";

        // The seam's own state. The plugin half keeps its own copies of these
        // names; they are separate on purpose, and the plugin is seeded from
        // the published result rather than recomputing what happened.
        SRWLOCK s_stateLock = SRWLOCK_INIT;
        RendererBackend s_requestedBackend = RendererBackend::Auto;
        BackendSelection::BootRequest s_bootRequest {};
        bool s_backendTransportEnabled = true;
        bool s_transportWrittenThisBoot = false;

        StartupSeam::StartupRendererResult s_result = {
            StartupSeam::kStartupRendererResultVersion,
            sizeof(StartupSeam::StartupRendererResult),
        };

        // ---- minimal local services --------------------------------------
        // Deliberately not TryGetUserConfigString/TrimAsciiCopy/
        // GetMainModuleDirectory from bzr_options_ui.h: that header's
        // translation unit is what drags bzr_hooks and the patch engine into
        // the bootstrap. These read the same openshim.ini the same way.

        std::string TrimAsciiCopy(const std::string& value)
        {
            const size_t first = value.find_first_not_of(" \t\r\n");
            if (first == std::string::npos) return {};
            const size_t last = value.find_last_not_of(" \t\r\n");
            return value.substr(first, last - first + 1);
        }

        std::filesystem::path GetMainModuleDirectory()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH) return {};
            return std::filesystem::path(path).parent_path();
        }

        // Tri-state read with the same sentinel trick the runtime uses, so a
        // present-but-blank key is distinguishable from an absent one.
        bool TryGetUserConfigString(const char* section, const char* key,
                                    std::string& out)
        {
            const auto dir = GetMainModuleDirectory();
            if (dir.empty()) return false;
            const auto path = dir / "openshim.ini";

            constexpr char kUnsetSentinel[] = "\x01__openshim_unset__";
            char buf[128] = {};
            GetPrivateProfileStringA(section, key, kUnsetSentinel, buf,
                                     static_cast<DWORD>(sizeof(buf)),
                                     path.string().c_str());
            if (buf[0] == '\0' || std::strcmp(buf, kUnsetSentinel) == 0)
                return false;
            const std::string trimmed = TrimAsciiCopy(buf);
            if (trimmed.empty()) return false;
            out = trimmed;
            return true;
        }

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


        // Only the two keys the startup decision needs. The plugin parses the
        // rest of the renderer configuration for itself; duplicating the full
        // reader here would put renderer policy on both sides of the boundary.
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
            // Hard kill-switch for the startup transport seam. Default is ON:
            // the seam only acts when [Graphics] Renderer is explicitly not
            // Auto, so Auto users see byte-identical stock behavior either way.
            s_backendTransportEnabled = true;
            if (TryGetUserConfigString("Startup", "BackendTransport", value))
            {
                s_backendTransportEnabled =
                    BackendSelection::ParseTransportEnabled(TrimAsciiCopy(value));
            }
        }

        bool s_dx9Present = false;
        bool s_dx11Present = false;

        // Mirrors the seam's outcome into the POD record OpenShim reads. Called
        // once, after the transport has run, while the state lock is held.
        uint32_t BackendToWire(RendererBackend backend)
        {
            switch (backend)
            {
            case RendererBackend::DX9:  return StartupSeam::kBackendDx9;
            case RendererBackend::DX11: return StartupSeam::kBackendDx11;
            default:                    return StartupSeam::kBackendAuto;
            }
        }

        uint32_t SourceToWire(BackendSelection::RequestSource source)
        {
            switch (source)
            {
            case BackendSelection::RequestSource::Persistent:
                return StartupSeam::kSourcePersistent;
            case BackendSelection::RequestSource::CliOverride:
                return StartupSeam::kSourceCliOverride;
            default:
                return StartupSeam::kSourceNone;
            }
        }

        void PublishResultLocked()
        {
            s_result.requestedBackend = BackendToWire(s_bootRequest.backend);
            s_result.requestSource = SourceToWire(s_bootRequest.source);
            s_result.dx9Present = s_dx9Present ? 1u : 0u;
            s_result.dx11Present = s_dx11Present ? 1u : 0u;
            s_result.transportWritten = s_transportWrittenThisBoot ? 1u : 0u;
            s_result.selectionRan = 1u;
            s_result.startupSiteValidated = 1u;
        }

        bool FileExistsNonEmpty(const std::filesystem::path& path)
        {
            std::error_code ec;
            return std::filesystem::is_regular_file(path, ec) &&
                   std::filesystem::file_size(path, ec) > 0 && !ec;
        }

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

        void RunStartupBackendSelection()
        {
            s_dx9Present = false;
            s_dx11Present = false;
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
            s_dx9Present =
                !moduleDir.empty() &&
                FileExistsNonEmpty(moduleDir / "RenderSystem_Direct3D9.dll");
            s_dx11Present =
                !moduleDir.empty() &&
                FileExistsNonEmpty(moduleDir / "RenderSystem_Direct3D11.dll");
            const bool dx9Present = s_dx9Present;
            const bool dx11Present = s_dx11Present;
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

        // startup_seam_wire.cpp renders these by number, in both modules.
        // If this enum is reordered, that table must move with it.
        static_assert(static_cast<uint32_t>(BackendSeamArmStatus::NotAttempted) == 0u, "");
        static_assert(static_cast<uint32_t>(BackendSeamArmStatus::Armed) == 1u, "");
        static_assert(static_cast<uint32_t>(BackendSeamArmStatus::SlotWriteFaulted) == 12u, "");

        std::atomic<BackendSeamArmStatus> s_seamArmStatus {
            BackendSeamArmStatus::NotAttempted
        };

        bool FailStartupBackendSeamArm(BackendSeamArmStatus status)
        {
            s_seamArmStatus.store(status, std::memory_order_release);
            // Published as a number so the runtime can render the text on its
            // own side without a call back across the boundary. Every write
            // to s_result goes under the state lock, so a copy taken from
            // another thread is never torn.
            AcquireSRWLockExclusive(&s_stateLock);
            s_result.armStatus = static_cast<uint32_t>(status);
            ReleaseSRWLockExclusive(&s_stateLock);
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
            AcquireSRWLockExclusive(&s_stateLock);
            s_result.seamArmed = 1u;
            s_result.armStatus = StartupSeam::kArmArmed;
            ReleaseSRWLockExclusive(&s_stateLock);
            s_seamArmStatus.store(
                BackendSeamArmStatus::Armed, std::memory_order_release);
            return true;
        }

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
            PublishResultLocked();
            ReleaseSRWLockExclusive(&s_stateLock);
        }

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

    }

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

    // Small bridges so the plugin half can reach bootstrap-owned state
    // without reaching into the seam's internals.
    void CopySeamResultLocked(StartupSeam::StartupRendererResult& out)
    {
        // Shared against the exclusive publish in the ConfigFile::load
        // interception: the game thread writes the record field by field
        // there, and the runtime copies from its patch thread, which on a GOG
        // boot runs seconds earlier and on a warm Steam boot can run later.
        AcquireSRWLockShared(&s_stateLock);
        out = s_result;
        ReleaseSRWLockShared(&s_stateLock);
    }

    void ClearPendingMarkerFromRuntime()
    {
        ClearPendingMarker();
    }

    void RunStartupSelectionForTestImpl()
    {
        AcquireSRWLockExclusive(&s_stateLock);
        LoadConfigLocked();
        RunStartupBackendSelection();
        PublishResultLocked();
        ReleaseSRWLockExclusive(&s_stateLock);
    }
}

namespace BZROpenShim::StartupSeam
{
    void RunStartupSelectionForTest()
    {
        BZROpenShim::RenderProfiles::RunStartupSelectionForTestImpl();
    }

    bool CopyStartupRendererResult(void* out, uint32_t capacity)
    {
        if (out == nullptr || capacity < sizeof(StartupRendererResult))
            return false;
        StartupRendererResult snapshot = {};
        BZROpenShim::RenderProfiles::CopySeamResultLocked(snapshot);
        std::memcpy(out, &snapshot, sizeof(StartupRendererResult));
        return true;
    }

    void ClearPendingMarker()
    {
        BZROpenShim::RenderProfiles::ClearPendingMarkerFromRuntime();
    }

}
