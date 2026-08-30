// autosave.cpp
// BZR Open Shim - engine-level single-player autosave support
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Independent OpenShim implementation of BZR's native save call. The calling
// convention and stable byte signature were established by prior BZR 2.2.301
// reverse-engineering/testing. OpenShim does not link or require EXU/Lua.

#include "autosave.h"
#include "autosave_gate.h"
#include "BZROpenShim.h"
#include "game_state.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        using NativeSaveGameFn = bool(__cdecl*)(char*, int);
        using WorldUpdateRenderQueueFn = void(__thiscall*)(void*, void*);

        constexpr uintptr_t kIsNetGameAddr = 0x00917F7B;
        constexpr uintptr_t kUserObjectAddr = 0x00917AFC;
        constexpr uintptr_t kEditModeAddr = 0x009454B8;
        constexpr uintptr_t kQueuedLoadNameBufferAddr = 0x00915540;
        constexpr size_t kQueuedLoadNameBufferLen = 16;

        // Existing patch-catalog slot for LegacyWorld::updateRenderQueue.
        // Installed after RunPatcher() so this chains either stock BZR or the
        // OpenShim wrapper already present in the slot.
        constexpr uintptr_t kWorldUpdateRenderQueueVtableSlot = 0x00892728;

        constexpr DWORD kDefaultIntervalSeconds = 120;
        constexpr DWORD kDefaultInitialDelaySeconds = 10;
        constexpr DWORD kDefaultRetrySeconds = 15;

        // A SaveGame fault means the engine walked a half-built mission, so the
        // gate that let the call through was wrong for that state. One fault
        // stands the feature down for the rest of the mission; this many across
        // the process stands it down until restart. Without the second cap a
        // wrong gate writes a fault - and, with WER LocalDumps configured, a
        // full-process dump - on every interval for as long as the game runs.
        constexpr LONG kMaxSaveFaultsPerProcess = 3;

        // Native bool __cdecl SaveGame(char* filename, int saveType).
        // -1 represents a wildcard byte.
        constexpr std::array<int, 54> kNativeSaveGameSignature = {
            0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x94, 0x00, 0x00, 0x00, 0xC6, 0x45, 0xFF, 0x01, 0xE8, -1, -1,
            -1, -1, 0x89, 0x85, 0x78, 0xFF, 0xFF, 0xFF, 0x68, -1, -1, -1, -1, 0xE8, -1, -1, -1, -1,
            0x83, 0xC4, 0x04, 0x0F, 0xB6, 0x05, -1, -1, -1, -1, 0x85, 0xC0, 0x0F, 0x84, -1, -1, -1, -1,
            0x6A, 0x2E
        };

        struct AutoSaveConfig
        {
            bool enabled = true;
            bool backupExisting = true;
            bool respectExternalAutoSave = true;
            ULONGLONG intervalMs = static_cast<ULONGLONG>(kDefaultIntervalSeconds) * 1000ULL;
            ULONGLONG initialDelayMs = static_cast<ULONGLONG>(kDefaultInitialDelaySeconds) * 1000ULL;
            ULONGLONG retryMs = static_cast<ULONGLONG>(kDefaultRetrySeconds) * 1000ULL;
        };

        AutoSaveConfig g_config;
        NativeSaveGameFn g_nativeSaveGame = nullptr;
        WorldUpdateRenderQueueFn g_previousWorldUpdateRenderQueue = nullptr;
        bool g_hookInstalled = false;
        bool g_missionActive = false;
        bool g_missionSaveFaulted = false;
        bool g_saveDisabledForProcess = false;
        LONG g_saveFaultCount = 0;
        ULONGLONG g_nextSaveTick = 0;
        volatile LONG g_saveInProgress = 0;

        std::filesystem::path g_gameDirectory;
        std::filesystem::path g_autoSavePath;
        std::filesystem::path g_autoSaveLabelPath;
        std::filesystem::path g_autoSaveBackupPath;
        std::filesystem::file_time_type g_observedAutoSaveWriteTime{};
        bool g_haveObservedAutoSaveWriteTime = false;

        bool SafeReadByte(uintptr_t address, uint8_t& value) noexcept
        {
            __try
            {
                value = *reinterpret_cast<const volatile uint8_t*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                value = 0;
                return false;
            }
        }

        // The engine keeps the current mission's short name here; it is the same
        // buffer the shell fills when a mission is queued for load.
        bool SafeReadMissionName(char (&value)[kQueuedLoadNameBufferLen + 1]) noexcept
        {
            value[0] = '\0';
            __try
            {
                const auto* text =
                    reinterpret_cast<const volatile char*>(kQueuedLoadNameBufferAddr);
                for (size_t index = 0; index < kQueuedLoadNameBufferLen; ++index)
                {
                    const char ch = text[index];
                    if (ch == '\0')
                        break;
                    // Mission names are identifiers; anything else means the
                    // buffer holds something that is not a name right now.
                    if (ch < 0x20 || ch > 0x7E)
                    {
                        value[0] = '\0';
                        return false;
                    }
                    value[index] = ch;
                    value[index + 1] = '\0';
                }
                return value[0] != '\0';
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                value[0] = '\0';
                return false;
            }
        }

        bool SafeReadPointer(uintptr_t address, void*& value) noexcept
        {
            __try
            {
                value = *reinterpret_cast<void* const volatile*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                value = nullptr;
                return false;
            }
        }

        bool InvokeNativeSaveGame(
            NativeSaveGameFn saveGame,
            char* filename,
            int saveType,
            DWORD& exceptionCode) noexcept
        {
            exceptionCode = 0;
            __try
            {
                return saveGame(filename, saveType);
            }
            __except (exceptionCode = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsExecutableAddress(const void* address) noexcept
        {
            if (!address)
                return false;

            MEMORY_BASIC_INFORMATION mbi{};
            if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi) || mbi.State != MEM_COMMIT)
                return false;

            if ((mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) != 0)
                return false;

            const DWORD protect = mbi.Protect & 0xFF;
            return protect == PAGE_EXECUTE ||
                   protect == PAGE_EXECUTE_READ ||
                   protect == PAGE_EXECUTE_READWRITE ||
                   protect == PAGE_EXECUTE_WRITECOPY;
        }

        bool IsReadableAddress(const void* address, size_t length) noexcept
        {
            if (!address || length == 0)
                return false;

            MEMORY_BASIC_INFORMATION mbi{};
            if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi) || mbi.State != MEM_COMMIT)
                return false;

            if ((mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) != 0)
                return false;

            const DWORD protect = mbi.Protect & 0xFF;
            const bool readable =
                protect == PAGE_READONLY ||
                protect == PAGE_READWRITE ||
                protect == PAGE_WRITECOPY ||
                protect == PAGE_EXECUTE_READ ||
                protect == PAGE_EXECUTE_READWRITE ||
                protect == PAGE_EXECUTE_WRITECOPY;
            if (!readable)
                return false;

            const auto regionEnd =
                reinterpret_cast<uintptr_t>(mbi.BaseAddress) + static_cast<uintptr_t>(mbi.RegionSize);
            return reinterpret_cast<uintptr_t>(address) + length <= regionEnd;
        }

        // A non-null global is not proof that the object behind it was ever
        // constructed. SaveGame walks the mission through virtual calls, so the
        // cheapest honest check is that the pointer looks like a live C++
        // object: readable storage, a readable vtable, and code at slot 0.
        bool IsPlausiblePolymorphicObject(void* object) noexcept
        {
            if (!IsReadableAddress(object, sizeof(void*)))
                return false;

            void* vtable = nullptr;
            if (!SafeReadPointer(reinterpret_cast<uintptr_t>(object), vtable) ||
                !IsReadableAddress(vtable, sizeof(void*)))
            {
                return false;
            }

            void* firstVirtual = nullptr;
            if (!SafeReadPointer(reinterpret_cast<uintptr_t>(vtable), firstVirtual))
                return false;

            return IsExecutableAddress(firstVirtual);
        }

        std::filesystem::path GetGameDirectory()
        {
            char modulePath[MAX_PATH]{};
            const DWORD length = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};

            return std::filesystem::path(std::string(modulePath, length)).parent_path();
        }

        DWORD ReadIniDword(
            const std::filesystem::path& iniPath,
            const char* key,
            DWORD defaultValue,
            DWORD minimum,
            DWORD maximum)
        {
            const UINT raw = GetPrivateProfileIntA(
                "AutoSave", key, static_cast<INT>(defaultValue), iniPath.string().c_str());
            return (std::clamp)(static_cast<DWORD>(raw), minimum, maximum);
        }

        void LoadConfig()
        {
            g_config = {};
            const std::filesystem::path iniPath = g_gameDirectory / "openshim.ini";
            const std::string ini = iniPath.string();

            g_config.enabled = GetPrivateProfileIntA("AutoSave", "Enabled", 1, ini.c_str()) != 0;
            g_config.backupExisting = GetPrivateProfileIntA("AutoSave", "BackupExisting", 1, ini.c_str()) != 0;
            g_config.respectExternalAutoSave =
                GetPrivateProfileIntA("AutoSave", "RespectExternalAutoSave", 1, ini.c_str()) != 0;

            const DWORD intervalSeconds = ReadIniDword(
                iniPath, "IntervalSeconds", kDefaultIntervalSeconds, 10, 3600);
            const DWORD initialDelaySeconds = ReadIniDword(
                iniPath, "InitialDelaySeconds", kDefaultInitialDelaySeconds, 0, 600);
            const DWORD retrySeconds = ReadIniDword(
                iniPath, "RetrySeconds", kDefaultRetrySeconds, 5, 120);

            g_config.intervalMs = static_cast<ULONGLONG>(intervalSeconds) * 1000ULL;
            g_config.initialDelayMs = static_cast<ULONGLONG>(initialDelaySeconds) * 1000ULL;
            g_config.retryMs = static_cast<ULONGLONG>(retrySeconds) * 1000ULL;
        }

        const uint8_t* FindPattern(const uint8_t* start, size_t size) noexcept
        {
            if (!start || size < kNativeSaveGameSignature.size())
                return nullptr;

            const size_t last = size - kNativeSaveGameSignature.size();
            for (size_t offset = 0; offset <= last; ++offset)
            {
                bool matched = true;
                for (size_t index = 0; index < kNativeSaveGameSignature.size(); ++index)
                {
                    const int expected = kNativeSaveGameSignature[index];
                    if (expected >= 0 && start[offset + index] != static_cast<uint8_t>(expected))
                    {
                        matched = false;
                        break;
                    }
                }

                if (matched)
                    return start + offset;
            }
            return nullptr;
        }

        NativeSaveGameFn ResolveNativeSaveGame()
        {
            HMODULE module = GetModuleHandleA(nullptr);
            if (!module)
                return nullptr;

            const auto* base = reinterpret_cast<const uint8_t*>(module);
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return nullptr;

            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return nullptr;

            const IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(nt);
            const uint8_t* resolved = nullptr;
            size_t matchCount = 0;

            for (WORD sectionIndex = 0;
                 sectionIndex < nt->FileHeader.NumberOfSections;
                 ++sectionIndex, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;

                const size_t sectionSize = section->Misc.VirtualSize != 0
                    ? static_cast<size_t>(section->Misc.VirtualSize)
                    : static_cast<size_t>(section->SizeOfRawData);
                const uint8_t* cursor = base + section->VirtualAddress;
                size_t remaining = sectionSize;

                while (remaining >= kNativeSaveGameSignature.size())
                {
                    const uint8_t* match = FindPattern(cursor, remaining);
                    if (!match)
                        break;

                    ++matchCount;
                    if (!resolved)
                        resolved = match;

                    const size_t consumed = static_cast<size_t>(match - cursor) + 1;
                    cursor += consumed;
                    remaining -= consumed;
                }
            }

            if (matchCount != 1 || !resolved)
            {
                LogShimA(
                    LogLevel::Error,
                    "autosave",
                    "Native SaveGame signature resolution failed/ambiguous (matches=%zu)",
                    matchCount);
                return nullptr;
            }

            LogShimA(LogLevel::Info, "autosave", "Resolved native SaveGame at %p", resolved);
            return reinterpret_cast<NativeSaveGameFn>(const_cast<uint8_t*>(resolved));
        }

        bool IsTerrainEditActive() noexcept
        {
            uint8_t editMode = 0;
            if (SafeReadByte(kEditModeAddr, editMode) && editMode != 0)
                return true;
            return false;
        }

        // Reads everything the gate needs in one pass so a log line describes a
        // single consistent moment rather than a mix of re-probed values.
        //
        // TerrainEdit (0x009454B8) is deliberately absent: unscripted
        // single-player / Instant Action missions carry that flag while a manual
        // SaveGame still succeeds, so it stays diagnostic only. Dump
        // battlezone98redux.exe.38660.dmp was taken with editMode=1,
        // wrapperActive=1, screenType=1, userObject=0 (post-mission) and showed
        // that treating it as a gate would have permanently suppressed the timer
        // armed at 09:38:20.698 with initialDelay=10000ms.
        AutoSaveGate::ObservedState ObserveState() noexcept
        {
            AutoSaveGate::ObservedState state;
            state.missionSaveFaulted = g_missionSaveFaulted;
            state.saveDisabledForProcess = g_saveDisabledForProcess;

            uint8_t isNetGame = 0;
            void* userObject = nullptr;
            const ShellUiState ui = ReadShellUiState();
            if (!SafeReadByte(kIsNetGameAddr, isNetGame) ||
                !SafeReadPointer(kUserObjectAddr, userObject) ||
                !ui.readable)
            {
                return state;
            }

            state.stateReadable = true;
            state.netGame = isNetGame != 0;
            state.userObjectPresent = userObject != nullptr;
            state.userObjectPlausible = IsPlausiblePolymorphicObject(userObject);
            state.pauseMenuOpen = IsPauseMenuOpen();
            state.uiWrapperActive = ui.wrapperActive;
            state.uiScreenPresent = ui.screenPresent;
            state.uiScreenType = ui.screenType;

            CURSORINFO info{};
            info.cbSize = sizeof(info);
            state.cursorVisible = GetCursorInfo(&info) && (info.flags & CURSOR_SHOWING) != 0;
            return state;
        }

        // A mission is "live" when the gate's non-UI preconditions hold: this is
        // what arms and disarms the timer, independently of whether a shell
        // screen is transiently in the way.
        bool IsSinglePlayerMissionActive(const AutoSaveGate::ObservedState& state) noexcept
        {
            return state.stateReadable && !state.netGame &&
                   state.userObjectPresent && state.userObjectPlausible;
        }

        void LogGateSnapshot(LogLevel level, const char* prefix, const AutoSaveGate::ObservedState& state)
        {
            LogShimA(
                level,
                "autosave",
                "%s readable=%u netGame=%u userObject=%u/%u pause=%u wrapper=%u screen=%u "
                "type=0x%02X(%s) cursor=%u terrainEdit=%u",
                prefix,
                state.stateReadable ? 1u : 0u,
                state.netGame ? 1u : 0u,
                state.userObjectPresent ? 1u : 0u,
                state.userObjectPlausible ? 1u : 0u,
                state.pauseMenuOpen ? 1u : 0u,
                state.uiWrapperActive ? 1u : 0u,
                state.uiScreenPresent ? 1u : 0u,
                static_cast<unsigned>(state.uiScreenType),
                DescribeScreenType(state.uiScreenType),
                state.cursorVisible ? 1u : 0u,
                IsTerrainEditActive() ? 1u : 0u);
        }

        void ResetMissionState()
        {
            g_missionActive = false;
            g_nextSaveTick = 0;
            g_haveObservedAutoSaveWriteTime = false;
            // A new mission gets a fresh attempt; the per-process budget in
            // g_saveFaultCount is what stops an endlessly wrong gate.
            g_missionSaveFaulted = false;
        }

        void CaptureAutoSaveWriteTime()
        {
            std::error_code error;
            if (!std::filesystem::exists(g_autoSavePath, error) || error)
            {
                g_haveObservedAutoSaveWriteTime = false;
                return;
            }

            const auto writeTime = std::filesystem::last_write_time(g_autoSavePath, error);
            if (error)
            {
                g_haveObservedAutoSaveWriteTime = false;
                return;
            }

            g_observedAutoSaveWriteTime = writeTime;
            g_haveObservedAutoSaveWriteTime = true;
        }

        bool ObserveExternalAutoSave(ULONGLONG now)
        {
            if (!g_config.respectExternalAutoSave ||
                InterlockedCompareExchange(&g_saveInProgress, 0, 0) != 0)
            {
                return false;
            }

            std::error_code error;
            if (!std::filesystem::exists(g_autoSavePath, error) || error)
                return false;

            const auto writeTime = std::filesystem::last_write_time(g_autoSavePath, error);
            if (error)
                return false;

            if (!g_haveObservedAutoSaveWriteTime)
            {
                g_observedAutoSaveWriteTime = writeTime;
                g_haveObservedAutoSaveWriteTime = true;
                return false;
            }
            if (writeTime == g_observedAutoSaveWriteTime)
                return false;

            g_observedAutoSaveWriteTime = writeTime;
            g_nextSaveTick = now + g_config.intervalMs;
            LogShimA(
                LogLevel::Info,
                "autosave",
                "Observed external Save\\auto.sav update; deferring OpenShim autosave for %llu ms",
                g_config.intervalMs);
            return true;
        }

        bool PreserveExistingAutoSave()
        {
            if (!g_config.backupExisting)
                return true;

            std::error_code error;
            if (!std::filesystem::exists(g_autoSavePath, error) || error)
                return !error;

            error.clear();
            if (std::filesystem::exists(g_autoSaveBackupPath, error))
                return !error;
            if (error)
                return false;

            std::filesystem::create_directories(g_autoSaveBackupPath.parent_path(), error);
            if (error)
                return false;

            const bool copied = std::filesystem::copy_file(
                g_autoSavePath,
                g_autoSaveBackupPath,
                std::filesystem::copy_options::none,
                error);
            if (!copied || error)
            {
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "Could not preserve existing autosave to %s (error=%d)",
                    g_autoSaveBackupPath.string().c_str(),
                    error.value());
                return false;
            }

            LogShimA(
                LogLevel::Info,
                "autosave",
                "Preserved pre-autosave file at %s",
                g_autoSaveBackupPath.string().c_str());
            return true;
        }

        void WriteAutoSaveLabel()
        {
            // This file is the text drawn on the injected AutoSave load button,
            // so it is for the player, not for parsing. Naming the mission is
            // the difference between "AutoSave" and knowing which one it is --
            // parity with the label EXU writes, without depending on EXU.
            char missionName[kQueuedLoadNameBufferLen + 1] = {};
            const bool haveMission = SafeReadMissionName(missionName);

            std::ofstream label(g_autoSaveLabelPath, std::ios::binary | std::ios::trunc);
            if (label.is_open())
            {
                if (haveMission)
                    label << missionName << " - AutoSave";
                else
                    label << "AutoSave";
            }
            else
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "Could not write AutoSave label %s",
                    g_autoSaveLabelPath.string().c_str());
        }

        bool PerformAutoSave(const AutoSaveGate::ObservedState& gateState)
        {
            if (!g_nativeSaveGame || InterlockedCompareExchange(&g_saveInProgress, 1, 0) != 0)
                return false;

            bool success = false;
            try
            {
                std::error_code error;
                std::filesystem::create_directories(g_autoSavePath.parent_path(), error);
                if (error)
                {
                    LogShimA(
                        LogLevel::Error,
                        "autosave",
                        "Could not create Save directory for %s (error=%d)",
                        g_autoSavePath.string().c_str(),
                        error.value());
                }
                else if (!PreserveExistingAutoSave())
                {
                    LogShimA(LogLevel::Warn, "autosave", "Autosave aborted because backup preservation failed");
                }
                else
                {
                    std::string filename = g_autoSavePath.string();
                    DWORD exceptionCode = 0;
                    const bool saved = InvokeNativeSaveGame(g_nativeSaveGame, filename.data(), 0, exceptionCode);

                    if (exceptionCode != 0)
                    {
                        // The call already touched the file, so its timestamp
                        // moved; re-observe it here or ObserveExternalAutoSave
                        // reports our own half-written file as somebody else's
                        // autosave and silently pushes the deadline out.
                        CaptureAutoSaveWriteTime();

                        g_missionSaveFaulted = true;
                        ++g_saveFaultCount;
                        LogShimA(
                            LogLevel::Error,
                            "autosave",
                            "Native SaveGame raised exception 0x%08lX for %s "
                            "(fault %ld of %ld); %s may be truncated",
                            exceptionCode,
                            filename.c_str(),
                            g_saveFaultCount,
                            kMaxSaveFaultsPerProcess,
                            g_autoSavePath.filename().string().c_str());
                        // The gate said this state was safe and it was not, so
                        // record what it saw: that snapshot is the only way to
                        // learn which global actually discriminates.
                        LogGateSnapshot(LogLevel::Error, "Gate state at fault:", gateState);

                        if (g_saveFaultCount >= kMaxSaveFaultsPerProcess)
                        {
                            g_saveDisabledForProcess = true;
                            LogShimA(
                                LogLevel::Error,
                                "autosave",
                                "Disabling autosave for this process after %ld SaveGame faults",
                                g_saveFaultCount);
                        }
                        else
                        {
                            LogShimA(
                                LogLevel::Warn,
                                "autosave",
                                "Standing down autosave until the next mission starts");
                        }
                    }
                    else if (!saved)
                    {
                        LogShimA(LogLevel::Warn, "autosave", "Native SaveGame returned false for %s", filename.c_str());
                    }
                    else
                    {
                        WriteAutoSaveLabel();
                        success = true;
                        g_saveFaultCount = 0;
                        LogShimA(LogLevel::Info, "autosave", "Saved %s", filename.c_str());
                    }
                }
            }
            catch (...)
            {
                LogShimA(LogLevel::Error, "autosave", "Unhandled C++ exception while preparing autosave");
            }

            InterlockedExchange(&g_saveInProgress, 0);
            if (success)
                CaptureAutoSaveWriteTime();
            return success;
        }

        void __fastcall AutoSaveWorldUpdateRenderQueueHook(void* thisPtr, void*, void* renderQueue)
        {
            const WorldUpdateRenderQueueFn previous = g_previousWorldUpdateRenderQueue;
            if (previous)
                previous(thisPtr, renderQueue);
            AutoSaveTick();
        }

        bool InstallMainThreadHook()
        {
            auto* const slot = reinterpret_cast<PVOID volatile*>(kWorldUpdateRenderQueueVtableSlot);
            void* current = nullptr;
            __try
            {
                current = *slot;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            void* const hook = reinterpret_cast<void*>(&AutoSaveWorldUpdateRenderQueueHook);
            if (current == hook)
            {
                g_hookInstalled = true;
                return true;
            }
            if (!current || !IsExecutableAddress(current))
            {
                LogShimA(LogLevel::Error, "autosave", "World-update vtable target is invalid (%p)", current);
                return false;
            }

            DWORD oldProtect = 0;
            if (!VirtualProtect(
                    reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                    sizeof(void*), PAGE_READWRITE, &oldProtect))
            {
                LogShimA(LogLevel::Error, "autosave", "VirtualProtect failed for update hook (err=%lu)", GetLastError());
                return false;
            }

            g_previousWorldUpdateRenderQueue = reinterpret_cast<WorldUpdateRenderQueueFn>(current);
            void* const observed = InterlockedCompareExchangePointer(slot, hook, current);

            DWORD ignored = 0;
            VirtualProtect(
                reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(
                GetCurrentProcess(),
                reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                sizeof(void*));

            if (observed != current)
            {
                g_previousWorldUpdateRenderQueue = nullptr;
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "World-update vtable changed during install (%p -> %p); hook skipped",
                    current,
                    observed);
                return false;
            }

            g_hookInstalled = true;
            LogShimA(LogLevel::Info, "autosave", "Installed main-thread hook; chained target %p", current);
            return true;
        }

        void RestoreMainThreadHook()
        {
            if (!g_hookInstalled || !g_previousWorldUpdateRenderQueue)
                return;

            auto* const slot = reinterpret_cast<PVOID volatile*>(kWorldUpdateRenderQueueVtableSlot);
            void* const hook = reinterpret_cast<void*>(&AutoSaveWorldUpdateRenderQueueHook);

            DWORD oldProtect = 0;
            if (!VirtualProtect(
                    reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                    sizeof(void*), PAGE_READWRITE, &oldProtect))
            {
                return;
            }

            InterlockedCompareExchangePointer(
                slot,
                reinterpret_cast<void*>(g_previousWorldUpdateRenderQueue),
                hook);

            DWORD ignored = 0;
            VirtualProtect(
                reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                sizeof(void*), oldProtect, &ignored);

            g_hookInstalled = false;
            g_previousWorldUpdateRenderQueue = nullptr;
        }
    }

    bool InitializeAutoSave()
    {
        if (g_hookInstalled)
            return true;

        g_gameDirectory = GetGameDirectory();
        if (g_gameDirectory.empty())
        {
            LogShimA(LogLevel::Error, "autosave", "Could not resolve game directory");
            return false;
        }

        // Existing Campaign Reimagined/OpenShim load-button contract.
        g_autoSavePath = g_gameDirectory / "Save" / "auto.sav";
        g_autoSaveLabelPath = g_gameDirectory / "Save" / "auto.label.txt";
        g_autoSaveBackupPath =
            g_gameDirectory / "Save" / "AutoSaveBackups" / "auto.pre_autosave.sav";

        LoadConfig();
        if (!g_config.enabled)
        {
            LogShimA(LogLevel::Info, "autosave", "Engine-level autosave disabled by openshim.ini");
            return true;
        }

        g_nativeSaveGame = ResolveNativeSaveGame();
        if (!g_nativeSaveGame || !InstallMainThreadHook())
        {
            g_nativeSaveGame = nullptr;
            return false;
        }

        ResetMissionState();
        if (GetModuleHandleA("exu.dll") != nullptr)
        {
            LogShimA(
                LogLevel::Info,
                "autosave",
                "EXU detected; OpenShim stays self-contained and defers when another component updates Save\\auto.sav");
        }

        LogShimA(
            LogLevel::Info,
            "autosave",
            "Enabled path=%s interval=%llu ms initialDelay=%llu ms backup=%d externalCoexistence=%d",
            g_autoSavePath.string().c_str(),
            g_config.intervalMs,
            g_config.initialDelayMs,
            g_config.backupExisting ? 1 : 0,
            g_config.respectExternalAutoSave ? 1 : 0);
        return true;
    }

    bool ReloadAutoSaveConfig()
    {
        if (g_gameDirectory.empty())
        {
            // Nothing has initialized yet. That is either a first enable on a
            // build where startup skipped setup, or a build the patcher refused.
            // Re-check the gate rather than inheriting the caller's: the settings
            // page is reachable independently of it, and InitializeAutoSave
            // resolves version-specific addresses.
            if (!IsCompatibleGameVersion())
            {
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "Cannot enable AutoSave: this build did not pass the version check");
                return false;
            }
            return InitializeAutoSave();
        }

        const bool wasEnabled = g_config.enabled;
        const ULONGLONG previousIntervalMs = g_config.intervalMs;
        LoadConfig();

        if (!g_config.enabled)
        {
            ResetMissionState();
            LogShimA(LogLevel::Info, "autosave", "Disabled live from OpenShim settings");
            return true;
        }

        // A game launched with AutoSave disabled never resolved SaveGame or
        // installed the recurring hook, so enabling it must finish setup live.
        if (!g_nativeSaveGame)
        {
            g_nativeSaveGame = ResolveNativeSaveGame();
            if (!g_nativeSaveGame)
                return false;
        }
        if (!g_hookInstalled && !InstallMainThreadHook())
        {
            g_nativeSaveGame = nullptr;
            return false;
        }

        if (!wasEnabled)
        {
            // Turning the feature back on by hand is an explicit request to try
            // again, so it clears a fault stand-down as well as re-entering
            // normal mission detection - the initial grace period still applies
            // when AutoSave is enabled mid-mission.
            if (g_saveDisabledForProcess || g_saveFaultCount != 0)
            {
                LogShimA(
                    LogLevel::Info,
                    "autosave",
                    "Clearing SaveGame fault stand-down (%ld prior faults) on explicit re-enable",
                    g_saveFaultCount);
            }
            g_saveDisabledForProcess = false;
            g_saveFaultCount = 0;
            ResetMissionState();
        }
        else if (g_missionActive && previousIntervalMs != g_config.intervalMs)
        {
            // A changed interval starts fresh from the moment it is selected.
            g_nextSaveTick = GetTickCount64() + g_config.intervalMs;
        }

        LogShimA(
            LogLevel::Info,
            "autosave",
            "Reloaded live config enabled=1 interval=%llu ms initialDelay=%llu ms",
            g_config.intervalMs,
            g_config.initialDelayMs);
        return true;
    }

    void ShutdownAutoSave()
    {
        RestoreMainThreadHook();
        g_nativeSaveGame = nullptr;
        ResetMissionState();
        InterlockedExchange(&g_saveInProgress, 0);
    }

    void AutoSaveTick()
    {
        if (!g_config.enabled || !g_nativeSaveGame || g_saveDisabledForProcess)
            return;

        const AutoSaveGate::ObservedState gateState = ObserveState();
        if (!IsSinglePlayerMissionActive(gateState))
        {
            if (g_missionActive)
                LogShimA(LogLevel::Debug, "autosave", "Single-player mission ended; timer reset");
            ResetMissionState();
            return;
        }

        const ULONGLONG now = GetTickCount64();
        if (!g_missionActive)
        {
            g_missionActive = true;
            g_nextSaveTick = now + g_config.initialDelayMs;
            CaptureAutoSaveWriteTime();
            LogShimA(
                LogLevel::Info,
                "autosave",
                "Single-player mission detected; first autosave eligible in %llu ms",
                g_config.initialDelayMs);
            // Pair every "mission detected" with what convinced it, so a log
            // from a repro says which globals the gate believed.
            LogGateSnapshot(LogLevel::Debug, "Gate state at mission detect:", gateState);
            return;
        }

        if (ObserveExternalAutoSave(now) || now < g_nextSaveTick)
            return;

        // Keep the deadline expired while paused/in shell UI or after a fault.
        // The first normal gameplay update once the gate clears saves.
        const AutoSaveGate::GateResult gate = AutoSaveGate::Evaluate(gateState);
        if (!gate.MaySave())
        {
            static ULONGLONG s_lastDeferLogTick = 0;
            static const char* s_lastDeferReason = nullptr;
            const bool reasonChanged = s_lastDeferReason != gate.reason;
            const bool intervalElapsed = now - s_lastDeferLogTick >= 5000ULL;
            if (reasonChanged || intervalElapsed)
            {
                LogShimA(
                    LogLevel::Debug,
                    "autosave",
                    "Deferring autosave (%s): %s (terrainEdit=%u)",
                    AutoSaveGate::DescribeDecision(gate.decision),
                    gate.reason,
                    IsTerrainEditActive() ? 1u : 0u);
                s_lastDeferLogTick = now;
                s_lastDeferReason = gate.reason;
            }
            return;
        }

        const ULONGLONG base = GetTickCount64();
        g_nextSaveTick = base + (PerformAutoSave(gateState) ? g_config.intervalMs : g_config.retryMs);
    }

    bool TriggerAutoSaveNow()
    {
        if (!g_config.enabled || !g_nativeSaveGame)
            return false;

        const AutoSaveGate::ObservedState gateState = ObserveState();
        const AutoSaveGate::GateResult gate = AutoSaveGate::Evaluate(gateState);
        if (!gate.MaySave())
        {
            LogShimA(
                LogLevel::Info,
                "autosave",
                "Manual autosave request refused (%s): %s",
                AutoSaveGate::DescribeDecision(gate.decision),
                gate.reason);
            return false;
        }

        const bool saved = PerformAutoSave(gateState);
        const ULONGLONG now = GetTickCount64();
        g_nextSaveTick = now + (saved ? g_config.intervalMs : g_config.retryMs);
        return saved;
    }
}
