// autosave.cpp
// BZR Open Shim - engine-level single-player autosave support
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// This is an independent OpenShim implementation of BZR's native save call.
// The calling convention and stable byte signature were established by prior
// reverse-engineering/testing in Extra Utilities; OpenShim does not load or
// link EXU and does not require mission Lua to participate.

#include "autosave.h"

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
#include <filesystem>
#include <fstream>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        using NativeSaveGameFn = bool(__cdecl*)(char*, int);
        using WorldUpdateRenderQueueFn = void(__thiscall*)(void*, void*);

        // BZR 2.2.301 runtime state already used elsewhere in OpenShim/EXU.
        constexpr uintptr_t kIsNetGameAddr = 0x00917F7B;
        constexpr uintptr_t kUserObjectAddr = 0x00917AFC;
        constexpr uintptr_t kEditModeAddr = 0x009454B8;
        constexpr uintptr_t kUiCurrentScreenAddr = 0x00918320;
        constexpr uintptr_t kUiWrapperActiveAddr = 0x00918324;
        constexpr uintptr_t kUiCurrentScreenTypeAddr = 0x00918328;

        // Existing OpenShim patch catalog entry "Legacy World Update RenderQueue
        // VTable Hook". We stack the autosave hook after RunPatcher(), so the
        // previous target is either stock BZR or OpenShim's existing wrapper.
        constexpr uintptr_t kWorldUpdateRenderQueueVtableSlot = 0x00892728;

        constexpr DWORD kDefaultIntervalSeconds = 120;
        constexpr DWORD kDefaultInitialDelaySeconds = 10;
        constexpr DWORD kDefaultRetrySeconds = 15;

        // Proven BZR 2.2.301 native SaveGame(char*, int) signature. -1 denotes
        // bytes that vary because they contain call targets/data addresses.
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

        bool SafeReadDword(uintptr_t address, uint32_t& value) noexcept
        {
            __try
            {
                value = *reinterpret_cast<const volatile uint32_t*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                value = 0;
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

        bool IsExecutableProtect(DWORD protect) noexcept
        {
            if ((protect & PAGE_GUARD) != 0 || (protect & PAGE_NOACCESS) != 0)
                return false;

            const DWORD baseProtect = protect & 0xFF;
            return baseProtect == PAGE_EXECUTE ||
                   baseProtect == PAGE_EXECUTE_READ ||
                   baseProtect == PAGE_EXECUTE_READWRITE ||
                   baseProtect == PAGE_EXECUTE_WRITECOPY;
        }

        bool IsExecutableAddress(const void* address) noexcept
        {
            if (!address)
                return false;

            MEMORY_BASIC_INFORMATION mbi{};
            if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;

            return mbi.State == MEM_COMMIT && IsExecutableProtect(mbi.Protect);
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
                "AutoSave",
                key,
                static_cast<INT>(defaultValue),
                iniPath.string().c_str());
            return (std::clamp)(static_cast<DWORD>(raw), minimum, maximum);
        }

        void LoadConfig()
        {
            g_config = {};
            const std::filesystem::path iniPath = g_gameDirectory / "openshim.ini";

            g_config.enabled = GetPrivateProfileIntA(
                "AutoSave", "Enabled", 1, iniPath.string().c_str()) != 0;
            g_config.backupExisting = GetPrivateProfileIntA(
                "AutoSave", "BackupExisting", 1, iniPath.string().c_str()) != 0;
            g_config.respectExternalAutoSave = GetPrivateProfileIntA(
                "AutoSave", "RespectExternalAutoSave", 1, iniPath.string().c_str()) != 0;

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

        const uint8_t* FindPattern(
            const uint8_t* start,
            size_t size,
            const std::array<int, 54>& pattern) noexcept
        {
            if (!start || size < pattern.size())
                return nullptr;

            const size_t last = size - pattern.size();
            for (size_t offset = 0; offset <= last; ++offset)
            {
                bool matched = true;
                for (size_t index = 0; index < pattern.size(); ++index)
                {
                    const int expected = pattern[index];
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

            for (WORD index = 0; index < nt->FileHeader.NumberOfSections; ++index, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;

                const size_t sectionSize = section->Misc.VirtualSize != 0
                    ? static_cast<size_t>(section->Misc.VirtualSize)
                    : static_cast<size_t>(section->SizeOfRawData);
                const uint8_t* sectionBase = base + section->VirtualAddress;

                const uint8_t* cursor = sectionBase;
                size_t remaining = sectionSize;
                while (remaining >= kNativeSaveGameSignature.size())
                {
                    const uint8_t* match = FindPattern(cursor, remaining, kNativeSaveGameSignature);
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

        bool IsSinglePlayerMissionActive() noexcept
        {
            uint8_t isNetGame = 0;
            void* userObject = nullptr;
            if (!SafeReadByte(kIsNetGameAddr, isNetGame) ||
                !SafeReadPointer(kUserObjectAddr, userObject))
            {
                return false;
            }

            return isNetGame == 0 && userObject != nullptr;
        }

        bool IsUnsafeUiState() noexcept
        {
            if (IsPauseMenuOpen())
                return true;

            uint8_t editMode = 0;
            if (SafeReadByte(kEditModeAddr, editMode) && editMode != 0)
                return true;

            uint32_t wrapperActive = 0;
            uint32_t screenType = 0;
            void* currentScreen = nullptr;
            if (!SafeReadDword(kUiWrapperActiveAddr, wrapperActive) ||
                !SafeReadDword(kUiCurrentScreenTypeAddr, screenType) ||
                !SafeReadPointer(kUiCurrentScreenAddr, currentScreen))
            {
                return true;
            }

            if (wrapperActive != 0 && currentScreen != nullptr && screenType != 0)
            {
                CURSORINFO cursorInfo{};
                cursorInfo.cbSize = sizeof(cursorInfo);
                if (GetCursorInfo(&cursorInfo) && (cursorInfo.flags & CURSOR_SHOWING) != 0)
                    return true;
            }

            return false;
        }

        void ResetMissionState()
        {
            g_missionActive = false;
            g_nextSaveTick = 0;
            g_haveObservedAutoSaveWriteTime = false;
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

            error.clear();
            std::filesystem::create_directories(g_autoSaveBackupPath.parent_path(), error);
            if (error)
                return false;

            error.clear();
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
            std::ofstream label(g_autoSaveLabelPath, std::ios::binary | std::ios::trunc);
            if (!label.is_open())
            {
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "Could not write AutoSave label %s",
                    g_autoSaveLabelPath.string().c_str());
                return;
            }

            label << "AutoSave";
        }

        bool PerformAutoSave()
        {
            if (!g_nativeSaveGame)
                return false;

            if (InterlockedCompareExchange(&g_saveInProgress, 1, 0) != 0)
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
                    const bool saved = InvokeNativeSaveGame(
                        g_nativeSaveGame,
                        filename.data(),
                        0,
                        exceptionCode);

                    if (exceptionCode != 0)
                    {
                        LogShimA(
                            LogLevel::Error,
                            "autosave",
                            "Native SaveGame raised exception 0x%08lX for %s",
                            exceptionCode,
                            filename.c_str());
                    }
                    else if (!saved)
                    {
                        LogShimA(
                            LogLevel::Warn,
                            "autosave",
                            "Native SaveGame returned false for %s",
                            filename.c_str());
                    }
                    else
                    {
                        WriteAutoSaveLabel();
                        success = true;
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

        void __fastcall AutoSaveWorldUpdateRenderQueueHook(
            void* thisPtr,
            void*,
            void* renderQueue)
        {
            WorldUpdateRenderQueueFn previous = g_previousWorldUpdateRenderQueue;
            if (previous)
                previous(thisPtr, renderQueue);

            AutoSaveTick();
        }

        bool InstallMainThreadHook()
        {
            auto* const slot = reinterpret_cast<void* volatile*>(kWorldUpdateRenderQueueVtableSlot);
            void* current = nullptr;
            __try
            {
                current = *slot;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            void* hook = reinterpret_cast<void*>(&AutoSaveWorldUpdateRenderQueueHook);
            if (current == hook)
            {
                g_hookInstalled = true;
                return true;
            }

            if (!current || !IsExecutableAddress(current))
            {
                LogShimA(
                    LogLevel::Error,
                    "autosave",
                    "World-update vtable target is invalid (%p); autosave hook not installed",
                    current);
                return false;
            }

            DWORD oldProtect = 0;
            if (!VirtualProtect(
                    reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                    sizeof(void*),
                    PAGE_READWRITE,
                    &oldProtect))
            {
                LogShimA(
                    LogLevel::Error,
                    "autosave",
                    "VirtualProtect failed for world-update vtable slot (err=%lu)",
                    GetLastError());
                return false;
            }

            g_previousWorldUpdateRenderQueue = reinterpret_cast<WorldUpdateRenderQueueFn>(current);
            void* observed = InterlockedCompareExchangePointer(
                reinterpret_cast<PVOID volatile*>(const_cast<void**>(reinterpret_cast<void* const*>(slot))),
                hook,
                current);

            DWORD ignored = 0;
            VirtualProtect(
                reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                sizeof(void*),
                oldProtect,
                &ignored);
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot), sizeof(void*));

            if (observed != current)
            {
                g_previousWorldUpdateRenderQueue = nullptr;
                LogShimA(
                    LogLevel::Warn,
                    "autosave",
                    "World-update vtable changed during install (%p -> %p); autosave hook skipped",
                    current,
                    observed);
                return false;
            }

            g_hookInstalled = true;
            LogShimA(
                LogLevel::Info,
                "autosave",
                "Installed main-thread autosave hook; chained previous target %p",
                current);
            return true;
        }

        void RestoreMainThreadHook()
        {
            if (!g_hookInstalled || !g_previousWorldUpdateRenderQueue)
                return;

            auto* const slot = reinterpret_cast<void* volatile*>(kWorldUpdateRenderQueueVtableSlot);
            void* hook = reinterpret_cast<void*>(&AutoSaveWorldUpdateRenderQueueHook);
            DWORD oldProtect = 0;
            if (!VirtualProtect(
                    reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                    sizeof(void*),
                    PAGE_READWRITE,
                    &oldProtect))
            {
                return;
            }

            InterlockedCompareExchangePointer(
                reinterpret_cast<PVOID volatile*>(const_cast<void**>(reinterpret_cast<void* const*>(slot))),
                reinterpret_cast<void*>(g_previousWorldUpdateRenderQueue),
                hook);

            DWORD ignored = 0;
            VirtualProtect(
                reinterpret_cast<void*>(kWorldUpdateRenderQueueVtableSlot),
                sizeof(void*),
                oldProtect,
                &ignored);

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

        // Keep the existing Campaign Reimagined/OpenShim load-button contract.
        g_autoSavePath = g_gameDirectory / "Save" / "auto.sav";
        g_autoSaveLabelPath = g_gameDirectory / "Save" / "auto.label.txt";
        g_autoSaveBackupPath = g_gameDirectory / "Save" / "AutoSaveBackups" / "auto.pre_autosave.sav";

        LoadConfig();
        if (!g_config.enabled)
        {
            LogShimA(LogLevel::Info, "autosave", "Engine-level autosave disabled by openshim.ini");
            return true;
        }

        g_nativeSaveGame = ResolveNativeSaveGame();
        if (!g_nativeSaveGame)
            return false;

        if (!InstallMainThreadHook())
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
                "EXU detected; OpenShim remains self-contained and will defer when another component updates Save\\auto.sav");
        }

        LogShimA(
            LogLevel::Info,
            "autosave",
            "Enabled: path=%s interval=%llu ms initialDelay=%llu ms backup=%d externalCoexistence=%d",
            g_autoSavePath.string().c_str(),
            g_config.intervalMs,
            g_config.initialDelayMs,
            g_config.backupExisting ? 1 : 0,
            g_config.respectExternalAutoSave ? 1 : 0);
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
        if (!g_config.enabled || !g_nativeSaveGame)
            return;

        if (!IsSinglePlayerMissionActive())
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
            return;
        }

        if (ObserveExternalAutoSave(now))
            return;

        if (now < g_nextSaveTick)
            return;

        // Leave the deadline expired while unsafe. The first normal gameplay
        // update after a pause/menu/loading transition will perform the save.
        if (IsUnsafeUiState())
            return;

        if (PerformAutoSave())
            g_nextSaveTick = GetTickCount64() + g_config.intervalMs;
        else
            g_nextSaveTick = GetTickCount64() + g_config.retryMs;
    }

    bool TriggerAutoSaveNow()
    {
        if (!g_config.enabled || !g_nativeSaveGame ||
            !IsSinglePlayerMissionActive() || IsUnsafeUiState())
        {
            return false;
        }

        const bool saved = PerformAutoSave();
        const ULONGLONG now = GetTickCount64();
        g_nextSaveTick = now + (saved ? g_config.intervalMs : g_config.retryMs);
        return saved;
    }
}
