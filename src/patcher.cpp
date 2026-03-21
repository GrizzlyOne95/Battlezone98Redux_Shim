// patcher.cpp
// BZR Open Shim - runtime patcher implementation
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from prior reverse-engineering notes and validation against
// the game executable.
//
// The reference patch flow:
//  1. Open a patch log
//  2. Read BZR.exe file version via GetFileVersionInfoA; expect 0x12D (301)
//  3. Loop up to 1000 times polling ReadProcessMemory at 0x00868300
//     until the 256-byte signature block matches the expected value
//  4. Once matched, apply all JMP/DWORD/BYTE patches via WriteProcessMemory
//  5. Log each patch name and result

#include "patcher.h"
#include "patches.h"
#include "scroll_helper.h"
#include "trampolines.h"
#include "d3d_startup_hooks.h"
#include "file_io_hooks.h"
#include "bzr_hooks.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include <vector>

namespace BZROpenShim
{
    static const char kOpenShimVersionTag[] = "2.2.301 + OpenShim";
    static constexpr uint32_t kDefaultMaxSoundChannels = 150;
    static constexpr uint32_t kMaxSupportedSoundChannels = 256;
    static constexpr uint32_t kGASMasterMaxObjectsOffset = 0x10;
    static constexpr DWORD kSoundChannelRefreshDelayMs = 1000;

    struct SoundChannelOverrideConfig
    {
        bool enabled = true;
        bool envOverride = false;
        bool envInvalid = false;
        bool envClamped = false;
        const char* sourceEnv = nullptr;
        uint32_t requestedChannels = kDefaultMaxSoundChannels;
        uint32_t maxChannels = kDefaultMaxSoundChannels;
    };

    struct SoundChannelOverrideTargets
    {
        uint32_t gmStorageAddress = 0;
        uint32_t gasMasterAddress = 0;
        uint32_t initSiteAddress = 0;
    };

    struct SoundChannelOverrideThreadContext
    {
        uint32_t gmStorageAddress = 0;
        uint32_t gasMasterAddress = 0;
        uint32_t maxChannels = 0;
    };

    // -----------------------------------------------------------------------
    // Internal log helper.
    // CRT's per-FILE lock handles thread safety for individual fwprintf calls.
    // LogHit is budget-limited to prevent I/O saturation from trampolines
    // firing on hot paths.
    // -----------------------------------------------------------------------
    static FILE* g_Log = nullptr;

    static bool ShouldLogHookHits()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            char value[8] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_HITS", value, static_cast<DWORD>(sizeof(value)));
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableD3DStartupHooks()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            char value[8] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_ENABLE_D3D_STARTUP_HOOKS", value, static_cast<DWORD>(sizeof(value)));
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldSuppressStartupAutoLoad()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            char value[8] = {};
            const DWORD allowLen = GetEnvironmentVariableA("OPENSHIM_ALLOW_STARTUP_AUTOLOAD", value, static_cast<DWORD>(sizeof(value)));
            if (allowLen > 0 && allowLen < sizeof(value) && value[0] != '0')
            {
                s_cached = 0;
            }
            else
            {
                s_cached = 1;
            }
        }
        return s_cached != 0;
    }

    static bool ShouldEnableArtilleryMaskTracePatch()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            char value[8] = {};
            DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_ARTILLERY_MASK", value, static_cast<DWORD>(sizeof(value)));
            if (!(len > 0 && len < sizeof(value) && value[0] != '0'))
            {
                ZeroMemory(value, sizeof(value));
                len = GetEnvironmentVariableA("OPENSHIM_TRACE_WEAPON_MASK", value, static_cast<DWORD>(sizeof(value)));
            }
            s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool EnvFlagEnabledByName(const char* name);

    static bool ShouldEnableChunkExperiments()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            s_cached =
                EnvFlagEnabledByName("OPENSHIM_ENABLE_CHUNK_EXPERIMENTS") ||
                EnvFlagEnabledByName("BZR_ENABLE_CHUNK_EXPERIMENTS") ||
                EnvFlagEnabledByName("BZR_CHUNK_FORCE_FIRST_GEO") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_FORCE_FIRST_GEO") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_PROXY_DEBUG") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_PLACEHOLDER_PROXY") ||
                EnvFlagEnabledByName("BZR_CHUNK_TRACE") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_TRACE") ||
                EnvFlagEnabledByName("BZR_CHUNK_TRACE_VERBOSE") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_TRACE_VERBOSE") ||
                EnvFlagEnabledByName("BZR_TRACE_CHUNK_EFFECT") ||
                EnvFlagEnabledByName("OPENSHIM_TRACE_CHUNK_EFFECT") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_EFFECT_TRACE") ||
                EnvFlagEnabledByName("BZR_CHUNK_LOG_BUDGET") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_LOG_BUDGET") ||
                EnvFlagEnabledByName("BZR_CHUNK_TRACE_ENTRY_LIMIT") ||
                EnvFlagEnabledByName("OPENSHIM_CHUNK_TRACE_ENTRY_LIMIT") ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableProducerBuildMenuExperiment()
    {
        static int s_cached = -1;
        if (s_cached < 0)
        {
            s_cached =
                EnvFlagEnabledByName("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU") ||
                EnvFlagEnabledByName("OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT") ||
                EnvFlagEnabledByName("BZR_ENABLE_PRODUCER_BUILD_MENU") ? 1 : 0;
        }
        return s_cached != 0;
    }

    static bool ShouldEnableLobbyBzrnetIntegration(bool isSteam)
    {
        static int s_cachedSteam = -1;
        static int s_cachedGog = -1;
        int& cache = isSteam ? s_cachedSteam : s_cachedGog;
        if (cache >= 0)
            return cache != 0;

        if (EnvFlagEnabledByName("OPENSHIM_DISABLE_LOBBY_BZRNET_INTEGRATION") ||
            EnvFlagEnabledByName("BZR_DISABLE_LOBBY_BZRNET_INTEGRATION"))
        {
            cache = 0;
            return false;
        }

        if (EnvFlagEnabledByName("OPENSHIM_ENABLE_LOBBY_BZRNET_INTEGRATION") ||
            EnvFlagEnabledByName("OPENSHIM_ENABLE_LOBBY_UI_BZRNET") ||
            EnvFlagEnabledByName("BZR_ENABLE_LOBBY_BZRNET_INTEGRATION"))
        {
            cache = 1;
            return true;
        }

        cache = isSteam ? 0 : 1;
        return cache != 0;
    }

    static bool EnvFlagEnabledByName(const char* name)
    {
        if (!name || !*name)
            return false;

        char value[8] = {};
        const DWORD len = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        return (len > 0 && len < sizeof(value) && value[0] != '0');
    }

    static bool ShouldEnableMapRefreshFixes(bool isSteam)
    {
        static int s_cachedSteam = -1;
        static int s_cachedGog = -1;
        int& cache = isSteam ? s_cachedSteam : s_cachedGog;
        if (cache >= 0)
            return cache != 0;

        if (EnvFlagEnabledByName("OPENSHIM_DISABLE_MAP_REFRESH_FIXES") ||
            EnvFlagEnabledByName("BZR_DISABLE_MAP_REFRESH_FIXES"))
        {
            cache = 0;
            return false;
        }

        if (!isSteam)
        {
            cache = 1;
            return true;
        }

        cache = 1;
        return true;
    }

    static bool IsMapRefreshPatchName(const char* name)
    {
        if (!name)
            return false;

        return strcmp(name, "Map Sorting") == 0 ||
               strcmp(name, "Map List Rewrite for Hop-Fix 1/3") == 0 ||
               strcmp(name, "Map List Rewrite for Hop-Fix 2/3") == 0 ||
               strcmp(name, "Map List Rewrite for Hop-Fix 3/3") == 0 ||
               strcmp(name, "Map List Fix Support 1/3") == 0 ||
               strcmp(name, "Map Jump Fix Branch Override") == 0;
    }

    static bool IsChunkExperimentPatchName(const char* name)
    {
        if (!name)
            return false;

        return strcmp(name, "Chunk Render Resolve Hook") == 0 ||
               strcmp(name, "Chunk Effect Simulate VTable Hook") == 0;
    }

    static bool IsProducerBuildMenuExperimentPatchName(const char* name)
    {
        return name && strcmp(name, "Producer Build Menu Root Hook") == 0;
    }

    static bool IsLobbyBzrnetIntegrationPatchName(const char* name)
    {
        if (!name)
            return false;

        return strcmp(name, "Lobby BZRNET Integration HOST") == 0 ||
               strcmp(name, "Lobby BZRNET Integration CLIENT") == 0;
    }

    static void FilterPatchesForRuntime(std::vector<PatchDef>& patches, bool isSteam)
    {
        if (ShouldEnableMapRefreshFixes(isSteam))
        {
            // keep existing set
        }
        else
        {
            const size_t before = patches.size();
            patches.erase(
                std::remove_if(
                    patches.begin(),
                    patches.end(),
                    [](const PatchDef& patch)
                    {
                        return IsMapRefreshPatchName(patch.name);
                    }),
                patches.end());

            const size_t removed = before - patches.size();
            if (removed > 0)
            {
                if (isSteam)
                {
                    Log(L"[INFO] Steam map refresh fixes disabled via env override (%zu patch(es) skipped)\n",
                        removed);
                }
                else
                {
                    Log(L"[INFO] Map refresh fixes disabled via env override (%zu patch(es) skipped)\n",
                        removed);
                }
            }
        }

        if (!ShouldEnableChunkExperiments())
        {
            const size_t before = patches.size();
            patches.erase(
                std::remove_if(
                    patches.begin(),
                    patches.end(),
                    [](const PatchDef& patch)
                    {
                        return IsChunkExperimentPatchName(patch.name);
                    }),
                patches.end());

            const size_t removed = before - patches.size();
            if (removed > 0)
            {
                Log(L"[INFO] Chunk experiments disabled by default (%zu patch(es) skipped). Set OPENSHIM_ENABLE_CHUNK_EXPERIMENTS=1 or a chunk trace/fallback env var to opt in.\n",
                    removed);
            }
        }

        if (!ShouldEnableProducerBuildMenuExperiment())
        {
            const size_t before = patches.size();
            patches.erase(
                std::remove_if(
                    patches.begin(),
                    patches.end(),
                    [](const PatchDef& patch)
                    {
                        return IsProducerBuildMenuExperimentPatchName(patch.name);
                    }),
                patches.end());

            const size_t removed = before - patches.size();
            if (removed > 0)
            {
                Log(L"[INFO] Producer build-menu experiment disabled by default (%zu patch(es) skipped). Set OPENSHIM_ENABLE_PRODUCER_BUILD_MENU=1 to opt in.\n",
                    removed);
            }
        }

        if (!ShouldEnableLobbyBzrnetIntegration(isSteam))
        {
            const size_t before = patches.size();
            patches.erase(
                std::remove_if(
                    patches.begin(),
                    patches.end(),
                    [](const PatchDef& patch)
                    {
                        return IsLobbyBzrnetIntegrationPatchName(patch.name);
                    }),
                patches.end());

            const size_t removed = before - patches.size();
            if (removed > 0)
            {
                if (isSteam)
                {
                    Log(L"[INFO] Steam lobby BZRNET integration hooks disabled by default (%zu patch(es) skipped). Set OPENSHIM_ENABLE_LOBBY_BZRNET_INTEGRATION=1 to opt in.\n",
                        removed);
                }
                else
                {
                    Log(L"[INFO] Lobby BZRNET integration hooks disabled via env override (%zu patch(es) skipped).\n",
                        removed);
                }
            }
        }
    }

    static SoundChannelOverrideConfig GetSoundChannelOverrideConfig()
    {
        static bool s_initialized = false;
        static SoundChannelOverrideConfig s_config = {};
        if (s_initialized)
            return s_config;

        s_initialized = true;
        s_config.enabled = true;
        s_config.requestedChannels = kDefaultMaxSoundChannels;
        s_config.maxChannels = kDefaultMaxSoundChannels;

        const char* envNames[] = {
            "OPENSHIM_MAX_SOUND_CHANNELS",
            "BZR_MAX_SOUND_CHANNELS"
        };

        for (const char* envName : envNames)
        {
            char value[32] = {};
            const DWORD len = GetEnvironmentVariableA(envName, value, static_cast<DWORD>(sizeof(value)));
            if (!(len > 0 && len < sizeof(value)))
                continue;

            s_config.envOverride = true;
            s_config.sourceEnv = envName;

            char* end = nullptr;
            const unsigned long parsed = strtoul(value, &end, 10);
            if (end == value || *end != '\0')
            {
                s_config.envInvalid = true;
                return s_config;
            }

            s_config.requestedChannels = static_cast<uint32_t>(parsed);
            if (s_config.requestedChannels == 0)
            {
                s_config.enabled = false;
                s_config.maxChannels = 0;
                return s_config;
            }

            s_config.maxChannels = s_config.requestedChannels;
            if (s_config.maxChannels > kMaxSupportedSoundChannels)
            {
                s_config.maxChannels = kMaxSupportedSoundChannels;
                s_config.envClamped = true;
            }

            return s_config;
        }

        return s_config;
    }

    static void SuppressStartupShellAutoLoad()
    {
        constexpr uintptr_t kStartupShellAutoLoadFlagAddr = 0x008EAAA8;

        if (!ShouldSuppressStartupAutoLoad())
        {
            Log(L"[INFO] Startup shell autoload gate preserved via OPENSHIM_ALLOW_STARTUP_AUTOLOAD\n");
            return;
        }

        __try
        {
            auto* flag = reinterpret_cast<volatile uint32_t*>(kStartupShellAutoLoadFlagAddr);
            const uint32_t previous = *flag;
            *flag = 0;
            Log(L"[INFO] Startup shell autoload gate cleared (prev=%u)\n", previous);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[WARN] Failed to clear startup shell autoload gate\n");
        }
    }

    static bool ScanForSoundChannelOverrideTargets(SoundChannelOverrideTargets& outTargets)
    {
        outTargets = {};

        static const uint8_t kPattern[] = {
            0xA3, 0x00, 0x00, 0x00, 0x00,
            0xA3, 0x00, 0x00, 0x00, 0x00,
            0xA3, 0x00, 0x00, 0x00, 0x00,
            0xA3, 0x00, 0x00, 0x00, 0x00,
            0xA3, 0x00, 0x00, 0x00, 0x00,
            0x68, 0x00, 0x00, 0x00, 0x00,
            0xE8, 0x00, 0x00, 0x00, 0x00,
            0x83, 0xC4, 0x04, 0x85, 0xC0, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x00,
            0xC7, 0x05, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x68, 0x00, 0x00, 0x00, 0x00,
            0xE8, 0x00, 0x00, 0x00, 0x00
        };
        static const uint8_t kMask[] = {
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
            0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x00, 0x00, 0x00
        };

        HMODULE hMain = GetModuleHandleA(nullptr);
        uint8_t* mainBase = reinterpret_cast<uint8_t*>(hMain);
        size_t mainSize = 0;
        if (hMain)
        {
            auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(hMain);
            if (dos->e_magic == IMAGE_DOS_SIGNATURE)
            {
                auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
                    reinterpret_cast<uint8_t*>(hMain) + dos->e_lfanew);
                if (nt->Signature == IMAGE_NT_SIGNATURE)
                    mainSize = nt->OptionalHeader.SizeOfImage;
            }
        }

        if (!mainBase || !mainSize)
        {
            Log(L"[AUDIO] Failed to resolve main module bounds for GAS scan\n");
            return false;
        }

        const uint32_t mainBaseValue = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainBase));
        const uint32_t mainEndValue = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainBase + mainSize));

        HANDLE hProc = GetCurrentProcess();
        MEMORY_BASIC_INFORMATION mbi = {};
        uint8_t* addr = mainBase;

        while (addr < (mainBase + mainSize) &&
               VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi))
        {
            uint8_t* regionBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
            uint8_t* regionEnd = regionBase + mbi.RegionSize;
            if (regionEnd <= mainBase || regionBase >= (mainBase + mainSize))
            {
                addr = regionEnd;
                continue;
            }

            if (mbi.State != MEM_COMMIT ||
                !(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ |
                                 PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            {
                addr = regionEnd;
                continue;
            }

            uint8_t* clipStart = (regionBase < mainBase) ? mainBase : regionBase;
            uint8_t* clipEnd = (regionEnd > (mainBase + mainSize)) ? (mainBase + mainSize) : regionEnd;
            const size_t clipSize = static_cast<size_t>(clipEnd - clipStart);
            if (clipSize < sizeof(kPattern))
            {
                addr = regionEnd;
                continue;
            }

            std::vector<uint8_t> buffer(clipSize);
            SIZE_T read = 0;
            if (!ReadProcessMemory(hProc, clipStart, buffer.data(), clipSize, &read) ||
                read < sizeof(kPattern))
            {
                addr = regionEnd;
                continue;
            }

            for (size_t i = 0; i <= read - sizeof(kPattern); ++i)
            {
                bool match = true;
                for (size_t j = 0; j < sizeof(kPattern); ++j)
                {
                    if ((buffer[i + j] & kMask[j]) != (kPattern[j] & kMask[j]))
                    {
                        match = false;
                        break;
                    }
                }

                if (!match)
                    continue;

                uint32_t gasMasterA = 0;
                uint32_t gasMasterB = 0;
                uint32_t gasMasterC = 0;
                uint32_t gmStorage = 0;
                memcpy(&gasMasterA, &buffer[i + 26], sizeof(gasMasterA));
                memcpy(&gmStorage, &buffer[i + 48], sizeof(gmStorage));
                memcpy(&gasMasterB, &buffer[i + 52], sizeof(gasMasterB));
                memcpy(&gasMasterC, &buffer[i + 57], sizeof(gasMasterC));

                if (gasMasterA == 0 || gmStorage == 0 ||
                    gasMasterA != gasMasterB || gasMasterA != gasMasterC)
                {
                    continue;
                }

                if (gmStorage < mainBaseValue || (gmStorage + sizeof(uint32_t)) > mainEndValue ||
                    gasMasterA < mainBaseValue || (gasMasterA + kGASMasterMaxObjectsOffset + sizeof(uint32_t)) > mainEndValue)
                {
                    continue;
                }

                outTargets.gmStorageAddress = gmStorage;
                outTargets.gasMasterAddress = gasMasterA;
                outTargets.initSiteAddress = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(clipStart + i));

                Log(L"[AUDIO] GAS init anchor found at 0x%08X (GM storage=0x%08X, GAS_Master=0x%08X)\n",
                    outTargets.initSiteAddress, outTargets.gmStorageAddress, outTargets.gasMasterAddress);
                return true;
            }

            addr = regionEnd;
        }

        Log(L"[AUDIO] GAS init anchor not found in executable regions\n");
        return false;
    }

    static bool IsAddressInMainImage(uint32_t address, size_t size)
    {
        HMODULE hMain = GetModuleHandleA(nullptr);
        if (!hMain)
            return false;

        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(hMain);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;

        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
            reinterpret_cast<uint8_t*>(hMain) + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;

        const uint32_t base = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(hMain));
        const uint32_t end = base + nt->OptionalHeader.SizeOfImage;
        return address >= base && (address + size) <= end;
    }

    static bool ValidateSoundChannelOverrideTargets(const SoundChannelOverrideTargets& targets,
                                                    const wchar_t* sourceTag)
    {
        if (targets.gmStorageAddress == 0 || targets.gasMasterAddress == 0)
            return false;

        if (!IsAddressInMainImage(targets.gmStorageAddress, sizeof(uint32_t)) ||
            !IsAddressInMainImage(targets.gasMasterAddress + kGASMasterMaxObjectsOffset, sizeof(uint32_t)))
        {
            Log(L"[AUDIO] %ls GAS globals rejected (outside main image: GM storage=0x%08X, GAS_Master=0x%08X)\n",
                sourceTag ? sourceTag : L"candidate",
                targets.gmStorageAddress,
                targets.gasMasterAddress);
            return false;
        }

        HANDLE hProc = GetCurrentProcess();
        uint32_t staticMaxObjects = 0;
        SIZE_T bytesRead = 0;
        if (!ReadProcessMemory(hProc,
                               reinterpret_cast<LPCVOID>(targets.gasMasterAddress + kGASMasterMaxObjectsOffset),
                               &staticMaxObjects,
                               sizeof(staticMaxObjects),
                               &bytesRead) ||
            bytesRead != sizeof(staticMaxObjects))
        {
            Log(L"[AUDIO] %ls GAS globals rejected (failed reading GAS_Master maxObjects at 0x%08X)\n",
                sourceTag ? sourceTag : L"candidate",
                targets.gasMasterAddress + kGASMasterMaxObjectsOffset);
            return false;
        }

        if (staticMaxObjects == 0 || staticMaxObjects > kMaxSupportedSoundChannels)
        {
            Log(L"[AUDIO] %ls GAS globals rejected (unexpected GAS_Master maxObjects=%u at 0x%08X)\n",
                sourceTag ? sourceTag : L"candidate",
                staticMaxObjects,
                targets.gasMasterAddress + kGASMasterMaxObjectsOffset);
            return false;
        }

        Log(L"[AUDIO] %ls GAS globals validated (GM storage=0x%08X, GAS_Master=0x%08X, maxObjects=%u)\n",
            sourceTag ? sourceTag : L"candidate",
            targets.gmStorageAddress,
            targets.gasMasterAddress,
            staticMaxObjects);
        return true;
    }

    static bool ResolveSoundChannelOverrideTargets(bool isSteam, SoundChannelOverrideTargets& outTargets)
    {
        if (ScanForSoundChannelOverrideTargets(outTargets))
            return true;

        if (!isSteam)
        {
            outTargets.gmStorageAddress = 0x00915594;
            outTargets.gasMasterAddress = 0x0091559C;
            Log(L"[AUDIO] Falling back to revalidated GOG GAS globals (GM storage=0x%08X, GAS_Master=0x%08X)\n",
                outTargets.gmStorageAddress, outTargets.gasMasterAddress);
            return true;
        }

        SoundChannelOverrideTargets gogFallback = {};
        gogFallback.gmStorageAddress = 0x00915594;
        gogFallback.gasMasterAddress = 0x0091559C;
        if (ValidateSoundChannelOverrideTargets(gogFallback, L"Steam fallback"))
        {
            outTargets = gogFallback;
            return true;
        }

        return false;
    }

    static DWORD WINAPI SoundChannelOverrideThreadProc(LPVOID param)
    {
        SoundChannelOverrideThreadContext context = {};
        SoundChannelOverrideThreadContext* heapContext =
            reinterpret_cast<SoundChannelOverrideThreadContext*>(param);
        if (heapContext)
        {
            context = *heapContext;
            delete heapContext;
        }

        HANDLE hProc = GetCurrentProcess();
        uint32_t lastGmPointer = 0;
        uint32_t lastPatchedBase = 0;
        bool loggedStorageReadFailure = false;

        while (true)
        {
            uint32_t gmPointer = 0;
            SIZE_T bytesRead = 0;
            if (!ReadProcessMemory(hProc,
                                   reinterpret_cast<LPCVOID>(context.gmStorageAddress),
                                   &gmPointer, sizeof(gmPointer), &bytesRead) ||
                bytesRead != sizeof(gmPointer))
            {
                if (!loggedStorageReadFailure)
                {
                    Log(L"[AUDIO] Failed reading GM storage at 0x%08X\n",
                        context.gmStorageAddress);
                    loggedStorageReadFailure = true;
                }
                Sleep(kSoundChannelRefreshDelayMs);
                continue;
            }

            loggedStorageReadFailure = false;

            const uint32_t targetBase = (gmPointer != 0) ? gmPointer : context.gasMasterAddress;
            if (gmPointer != lastGmPointer)
            {
                Log(L"[AUDIO] GM pointer %s: 0x%08X\n",
                    (gmPointer != 0) ? L"updated" : L"not yet published",
                    gmPointer);
                lastGmPointer = gmPointer;
            }

            if (targetBase != 0)
            {
                const uint32_t maxObjectsAddress = targetBase + kGASMasterMaxObjectsOffset;
                uint32_t currentValue = 0;
                SIZE_T fieldRead = 0;
                if (ReadProcessMemory(hProc,
                                      reinterpret_cast<LPCVOID>(maxObjectsAddress),
                                      &currentValue, sizeof(currentValue), &fieldRead) &&
                    fieldRead == sizeof(currentValue) &&
                    currentValue != context.maxChannels)
                {
                    const uint32_t desiredValue = context.maxChannels;
                    SIZE_T written = 0;
                    if (WriteProcessMemory(hProc,
                                           reinterpret_cast<LPVOID>(maxObjectsAddress),
                                           &desiredValue, sizeof(desiredValue), &written) &&
                        written == sizeof(desiredValue))
                    {
                        Log(L"[AUDIO] maxObjects %s at 0x%08X: %u -> %u\n",
                            (gmPointer != 0) ? L"patched" : L"primed",
                            maxObjectsAddress, currentValue, desiredValue);
                        lastPatchedBase = targetBase;
                    }
                    else if (targetBase != lastPatchedBase)
                    {
                        Log(L"[AUDIO] Failed writing maxObjects at 0x%08X (err=%lu)\n",
                            maxObjectsAddress, GetLastError());
                        lastPatchedBase = targetBase;
                    }
                }
            }

            Sleep(kSoundChannelRefreshDelayMs);
        }
    }

    static void StartSoundChannelOverride(bool isSteam)
    {
        const SoundChannelOverrideConfig config = GetSoundChannelOverrideConfig();
        if (config.envInvalid)
        {
            Log(L"[AUDIO] Invalid %hs value; using default %u channels\n",
                config.sourceEnv ? config.sourceEnv : "OPENSHIM_MAX_SOUND_CHANNELS",
                kDefaultMaxSoundChannels);
        }

        if (!config.enabled)
        {
            Log(L"[AUDIO] Sound channel override disabled via %hs\n",
                config.sourceEnv ? config.sourceEnv : "OPENSHIM_MAX_SOUND_CHANNELS");
            return;
        }

        if (config.envOverride && !config.envInvalid)
        {
            Log(L"[AUDIO] Sound channel override requested via %hs: %u channel(s)\n",
                config.sourceEnv, config.requestedChannels);
            if (config.envClamped)
            {
                Log(L"[AUDIO] Requested sound channel count clamped to %u\n",
                    config.maxChannels);
            }
        }
        else
        {
            Log(L"[AUDIO] Sound channel override enabled by default: %u channel(s)\n",
                config.maxChannels);
        }

        SoundChannelOverrideTargets targets = {};
        if (!ResolveSoundChannelOverrideTargets(isSteam, targets))
        {
            Log(L"[AUDIO] Sound channel override unavailable; GAS globals not located\n");
            return;
        }

        auto* context = new (std::nothrow) SoundChannelOverrideThreadContext();
        if (!context)
        {
            Log(L"[AUDIO] Failed allocating sound channel override context\n");
            return;
        }

        context->gmStorageAddress = targets.gmStorageAddress;
        context->gasMasterAddress = targets.gasMasterAddress;
        context->maxChannels = config.maxChannels;

        HANDLE threadHandle = CreateThread(nullptr, 0, SoundChannelOverrideThreadProc,
                                           context, 0, nullptr);
        if (!threadHandle)
        {
            Log(L"[AUDIO] Failed starting sound channel override thread (err=%lu)\n",
                GetLastError());
            delete context;
            return;
        }

        CloseHandle(threadHandle);
        Log(L"[AUDIO] Sound channel override worker started\n");
    }

    void Log(const wchar_t* fmt, ...)
    {
        if (!g_Log) return;
        va_list args;
        va_start(args, fmt);
        vfwprintf(g_Log, fmt, args);
        va_end(args);
        fflush(g_Log);
    }

    extern "C" void LogHit(const char* name)
    {
        static volatile long s_budget = 100;
        if (ShouldLogHookHits() && InterlockedDecrement(&s_budget) >= 0)
            Log(L"[HIT]  %hs\n", name);
    }

    // -----------------------------------------------------------------------
    // Detect Steam executable by filename.
    // -----------------------------------------------------------------------
    static bool IsSteamExe()
    {
        char path[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        const char* base = strrchr(path, '\\');
        base = base ? (base + 1) : path;
        return _stricmp(base, "battlezone98redux.exe") == 0;
    }

    // -----------------------------------------------------------------------
    // Read BZR.exe file version (minor build number)
    // Mirrors the reference patch logic: reads VS_FIXEDFILEINFO fields.
    // Expected value: 0x12D == 301 decimal
    // -----------------------------------------------------------------------
    static uint32_t GetBZRVersion()
    {
        char path[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, path, MAX_PATH);

        DWORD dummy = 0;
        DWORD size = GetFileVersionInfoSizeA(path, &dummy);
        if (size == 0) return 0xFFFFFFFF;

        std::vector<uint8_t> buf(size);
        if (!GetFileVersionInfoA(path, 0, size, buf.data())) return 0xFFFFFFFF;

        VS_FIXEDFILEINFO* ffi = nullptr;
        UINT ffiLen = 0;
        if (!VerQueryValueA(buf.data(), "\\",
            reinterpret_cast<LPVOID*>(&ffi), &ffiLen))
            return 0xFFFFFFFF;
        if (!ffi || ffi->dwSignature != 0xFEEF04BD) return 0xFFFFFFFF;

        Log(L"[INFO] FileVersion MS: 0x%08X, LS: 0x%08X\n", ffi->dwFileVersionMS, ffi->dwFileVersionLS);
        Log(L"[INFO] ProductVersion MS: 0x%08X, LS: 0x%08X\n", ffi->dwProductVersionMS, ffi->dwProductVersionLS);

        // The reference patch reads *(ushort*)((int)local_160 + 0xe)
        // local_160 is likely the start of VS_FIXEDFILEINFO.
        // +0xE is the HIWORD of dwFileVersionLS? 
        // No, in memory it's: 0x8 (MS), 0xC (LS). 
        // 0xC is LOWORD of LS, 0xE is HIWORD of LS.
        // So it's probably return static_cast<uint32_t>(HIWORD(ffi->dwFileVersionLS));
        
        uint32_t ver = static_cast<uint32_t>(LOWORD(ffi->dwFileVersionLS));
        if (ver == 0) ver = static_cast<uint32_t>(HIWORD(ffi->dwFileVersionLS));

        return ver;
    }

    // -----------------------------------------------------------------------
    // Apply a single patch via WriteProcessMemory.
    // Mirrors the reference patch's patch-write helpers.
    // Returns: 1 = applied, 0 = skipped (not a failure), -1 = failed
    // -----------------------------------------------------------------------
    static int ApplyPatch(uint32_t address, const void* data, size_t len, const char* name,
                          const std::vector<uint8_t>& expected_original)
    {
        if (address == 0)
        {
            Log(L"[SKIP] %hs (address not yet verified)\n", name);
            return 0; // skip
        }

        HANDLE hProc = GetCurrentProcess();
        DWORD oldProtect = 0;
        void* ptr = reinterpret_cast<void*>(address);
        const bool isSteam = IsSteamExe();

        // Verify original bytes match (detects Steam vs GOG mismatch)
        if (!expected_original.empty())
        {
            std::vector<uint8_t> current(expected_original.size());
            SIZE_T read = 0;
            if (!ReadProcessMemory(hProc, ptr, current.data(), current.size(), &read) ||
                read != current.size())
            {
                Log(L"[SKIP] %hs - could not read original bytes\n", name);
                return 0; // skip
            }

            bool match = true;
            for (size_t i = 0; i < expected_original.size(); ++i)
            {
                if (current[i] != expected_original[i])
                {
                    match = false;
                    break;
                }
            }

            if (!match && isSteam)
            {
                constexpr DWORD kRetryAttempts = 300;
                constexpr DWORD kRetryDelayMs = 10;
                for (DWORD attempt = 0; attempt < kRetryAttempts && !match; ++attempt)
                {
                    Sleep(kRetryDelayMs);

                    read = 0;
                    if (!ReadProcessMemory(hProc, ptr, current.data(), current.size(), &read) ||
                        read != current.size())
                    {
                        break;
                    }

                    match = true;
                    for (size_t i = 0; i < expected_original.size(); ++i)
                    {
                        if (current[i] != expected_original[i])
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        Log(L"[INFO] %hs original bytes settled after %u retry attempts\n",
                            name,
                            static_cast<unsigned>(attempt + 1));
                    }
                }
            }

            if (!match)
            {
                Log(L"[SKIP] %hs - original bytes mismatch (likely Steam vs GOG)\n", name);
                Log(L"       Expected: ");
                for (auto b : expected_original) Log(L"%02X ", b);
                Log(L"\n       Found:    ");
                for (auto b : current) Log(L"%02X ", b);
                Log(L"\n");
                return 0; // skip, not a failure
            }
        }

        // Make writable
        if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            Log(L"[FAIL] %hs - VirtualProtect failed (err %u)\n", name, GetLastError());
            return false;
        }

        SIZE_T written = 0;
        BOOL ok = WriteProcessMemory(hProc, ptr, data, len, &written);

        // Restore protection
        VirtualProtect(ptr, len, oldProtect, &oldProtect);

        if (!ok || written != len)
        {
            Log(L"[FAIL] %hs - WriteProcessMemory failed (err %u)\n", name, GetLastError());
            return -1; // failure
        }

        Log(L"[OK]   %hs wrote %zu bytes to 0x%08X\n", name, len, address);
        return 1; // applied
    }

    static bool BytesMatchAt(uint32_t address, const uint8_t* expected, size_t len)
    {
        if (!expected || len == 0)
            return false;

        std::vector<uint8_t> buf(len);
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<LPCVOID>(address),
                               buf.data(), len, &read) ||
            read != len)
            return false;

        return memcmp(buf.data(), expected, len) == 0;
    }

    static bool ReadFileAt(HANDLE hFile, uint32_t offset, void* dst, uint32_t len)
    {
        if (SetFilePointer(hFile, offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER &&
            GetLastError() != NO_ERROR)
            return false;

        DWORD read = 0;
        return ReadFile(hFile, dst, len, &read, nullptr) && read == len;
    }

    // -----------------------------------------------------------------------
    // Read the 256-byte signature block from the on-disk BZR.exe.
    // This is used to wait until SteamStub has decrypted .text in memory.
    // -----------------------------------------------------------------------
    static bool ReadExeSignature(std::vector<uint8_t>& outSig)
    {
        outSig.clear();

        char path[MAX_PATH] = {};
        if (!GetModuleFileNameA(nullptr, path, MAX_PATH))
        {
            Log(L"[WARN] GetModuleFileNameA failed for exe (err=%lu)\n", GetLastError());
            return false;
        }

        HANDLE hFile = CreateFileA(path, GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                   nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            Log(L"[WARN] Failed to open exe for signature read (err=%lu)\n", GetLastError());
            return false;
        }

        IMAGE_DOS_HEADER dos = {};
        if (!ReadFileAt(hFile, 0, &dos, sizeof(dos)) || dos.e_magic != IMAGE_DOS_SIGNATURE)
        {
            Log(L"[WARN] Invalid DOS header when reading signature\n");
            CloseHandle(hFile);
            return false;
        }

        IMAGE_NT_HEADERS32 nt = {};
        if (!ReadFileAt(hFile, static_cast<uint32_t>(dos.e_lfanew), &nt, sizeof(nt)) ||
            nt.Signature != IMAGE_NT_SIGNATURE)
        {
            Log(L"[WARN] Invalid NT headers when reading signature\n");
            CloseHandle(hFile);
            return false;
        }

        if (nt.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
        {
            Log(L"[WARN] Unexpected optional header magic (0x%04X)\n", nt.OptionalHeader.Magic);
            CloseHandle(hFile);
            return false;
        }

        const uint32_t imageBase = static_cast<uint32_t>(nt.OptionalHeader.ImageBase);
        if (BZR_SIGNATURE_ADDR < imageBase)
        {
            Log(L"[WARN] Signature VA 0x%08X is below image base 0x%08X\n",
                BZR_SIGNATURE_ADDR, imageBase);
            CloseHandle(hFile);
            return false;
        }

        const uint32_t sigRva = BZR_SIGNATURE_ADDR - imageBase;
        const uint32_t sigLen = 256;

        const uint32_t sectionTableOffset =
            static_cast<uint32_t>(dos.e_lfanew) + sizeof(uint32_t) +
            sizeof(IMAGE_FILE_HEADER) + nt.FileHeader.SizeOfOptionalHeader;

        std::vector<IMAGE_SECTION_HEADER> sections(nt.FileHeader.NumberOfSections);
        if (!ReadFileAt(hFile, sectionTableOffset,
                        sections.data(),
                        static_cast<uint32_t>(sections.size() * sizeof(IMAGE_SECTION_HEADER))))
        {
            Log(L"[WARN] Failed to read section headers for signature\n");
            CloseHandle(hFile);
            return false;
        }

        uint32_t sigRaw = 0;
        bool found = false;
        for (const auto& s : sections)
        {
            const uint32_t va = s.VirtualAddress;
            const uint32_t vsz = (std::max)(s.Misc.VirtualSize, s.SizeOfRawData);
            if (sigRva >= va && (sigRva + sigLen) <= (va + vsz))
            {
                sigRaw = s.PointerToRawData + (sigRva - va);
                found = true;
                break;
            }
        }

        if (!found)
        {
            Log(L"[WARN] Signature RVA 0x%08X not found in any section\n", sigRva);
            CloseHandle(hFile);
            return false;
        }

        outSig.resize(sigLen);
        if (!ReadFileAt(hFile, sigRaw, outSig.data(), sigLen))
        {
            Log(L"[WARN] Failed to read signature bytes from exe\n");
            outSig.clear();
            CloseHandle(hFile);
            return false;
        }

        CloseHandle(hFile);
        Log(L"[INFO] Loaded signature bytes from disk (VA=0x%08X)\n", BZR_SIGNATURE_ADDR);
        return true;
    }

    static bool WaitForSignature(const std::vector<uint8_t>& sig)
    {
        if (sig.empty())
            return true; // best-effort: skip gating if we couldn't load signature

        Log(L"[INFO] Waiting for signature at 0x%08X...\n", BZR_SIGNATURE_ADDR);
        for (int attempt = 0; attempt < PATCH_MAX_RETRIES; ++attempt)
        {
            if (BytesMatchAt(BZR_SIGNATURE_ADDR, sig.data(), sig.size()))
            {
                Log(L"[OK]   Signature matched after %d attempts\n", attempt + 1);
                return true;
            }
            Sleep(PATCH_RETRY_DELAY_MS);
        }

        Log(L"[FAIL] Signature never matched after %d attempts\n", PATCH_MAX_RETRIES);
        return false;
    }

    // -----------------------------------------------------------------------
    // Resolve a relative CALL target (E8 rel32) at a given instruction address.
    // Returns nullptr if the opcode is not a CALL or the read fails.
    // -----------------------------------------------------------------------
    static void* ResolveRelCallTarget(uint32_t instrAddr)
    {
        uint8_t buf[5] = {};
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<LPCVOID>(instrAddr),
                               buf, sizeof(buf), &read) ||
            read != sizeof(buf))
            return nullptr;

        if (buf[0] != 0xE8)
            return nullptr;

        int32_t rel = 0;
        memcpy(&rel, &buf[1], sizeof(rel));
        uint32_t target = instrAddr + 5 + static_cast<uint32_t>(rel);
        return reinterpret_cast<void*>(target);
    }

    static void* ResolveRelCallTargetWithRetry(uint32_t instrAddr, int maxAttempts, DWORD delayMs)
    {
        for (int attempt = 0; attempt < maxAttempts; ++attempt)
        {
            if (void* target = ResolveRelCallTarget(instrAddr))
            {
                if (attempt > 0)
                {
                    Log(L"[PTR] REL32 call at 0x%08X settled after %d attempts\n",
                        instrAddr,
                        attempt + 1);
                }
                return target;
            }

            if (attempt + 1 < maxAttempts)
                Sleep(delayMs);
        }

        uint8_t buf[5] = {};
        SIZE_T read = 0;
        if (ReadProcessMemory(GetCurrentProcess(),
                              reinterpret_cast<LPCVOID>(instrAddr),
                              buf, sizeof(buf), &read) &&
            read == sizeof(buf))
        {
            Log(L"[PTR] REL32 call unresolved at 0x%08X bytes=%02X %02X %02X %02X %02X\n",
                instrAddr, buf[0], buf[1], buf[2], buf[3], buf[4]);
        }

        return nullptr;
    }

    // -----------------------------------------------------------------------
    // Build final patch payloads for JMP5 patches.
    // For each JMP5 patch, the payload is a 5-byte E9 sequence jumping to
    // the corresponding Trampoline_xxx function in this DLL.
    // -----------------------------------------------------------------------
    // -----------------------------------------------------------------------
    // Resolve internal BZR.exe pointers for trampolines/helpers.
    // Now uses dynamic addresses found by pattern scanning.
    // -----------------------------------------------------------------------
    static void ResolvePointers(uint32_t mapSortingAddr, uint32_t hopFix1Addr, uint32_t hopFix2Addr, uint32_t hopFix3Addr, uint32_t probeMapFilter1Addr, uint32_t probeMapListFix1Addr, uint32_t probeMapListFix2Addr, uint32_t artilleryHowitzerVolleyAddr, uint32_t turretCraftAimPitchAddr, uint32_t turretTankAimPitchAddr, uint32_t underAttackAlertHook1Addr, uint32_t underAttackAlertHook2Addr, uint32_t offensiveAttackRevealAddr, uint32_t turretTankAttackRevealAddr)
    {
        Log(L"=========== RESOLVING POINTERS ===========\n");

        // Hop-Fix 1 - reference patch jumps back to patch site + 0xE
        // (covers overwritten + inlined original call block).
        if (hopFix1Addr) {
            g_RetAddr_HopFix1 = reinterpret_cast<void*>(hopFix1Addr + 0x0E);
            if (void* callTarget = ResolveRelCallTarget(hopFix1Addr + 0x09))
            {
                g_BZRFnPtr_HopFix1 = reinterpret_cast<void (*)()>(callTarget);
                Log(L"[PTR] Hop-Fix 1 call target (decoded): 0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(callTarget)));
            }
            else
            {
                g_BZRFnPtr_HopFix1 = reinterpret_cast<void (*)()>(0x005D4260);
                Log(L"[PTR] Hop-Fix 1 call target fallback: 0x%08X\n", 0x005D4260);
            }
            Log(L"[PTR] Hop-Fix 1 return: 0x%08X\n", hopFix1Addr + 0x0E);
        }

        // Hop-Fix 2 - reference patch jumps back to patch site + 0x13.
        if (hopFix2Addr) {
            g_RetAddr_HopFix2 = reinterpret_cast<void*>(hopFix2Addr + 0x13);
            g_MapListObject = reinterpret_cast<void**>(0x0094555C);
            // Stability mode: replay original call site target from 0x00799279 context.
            if (void* callTarget = ResolveRelCallTarget(hopFix2Addr + 0x0E))
            {
                g_BZRFnPtr_HopFix2 = reinterpret_cast<void (*)()>(callTarget);
                Log(L"[PTR] Hop-Fix 2 call target (decoded): 0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(callTarget)));
            }
            else
            {
                g_BZRFnPtr_HopFix2 = reinterpret_cast<void (*)()>(0x007CAFA0);
                Log(L"[PTR] Hop-Fix 2 call target fallback: 0x%08X\n", 0x007CAFA0);
            }
            Log(L"[PTR] Hop-Fix 2 return: 0x%08X\n", hopFix2Addr + 0x13);
        }

        // Hop-Fix 3 - reference patch jumps back to patch site + 7
        // (CALL EDX + PUSH 0x930).
        if (hopFix3Addr) {
            g_RetAddr_HopFix3 = reinterpret_cast<void*>(hopFix3Addr + 0x07);
            Log(L"[PTR] Hop-Fix 3 return: 0x%08X\n", hopFix3Addr + 0x07);
        }
        if (!g_BZRFnPtr_HopFix3Step)
        {
            g_BZRFnPtr_HopFix3Step = reinterpret_cast<void (*)()>(0x007A3130);
            Log(L"[PTR] Hop-Fix 3 step function fallback: 0x%08X\n", 0x007A3130);
        }

        if (mapSortingAddr) {
            g_RetAddr_Probe_MapSorting = reinterpret_cast<void*>(mapSortingAddr + 0x07);
            Log(L"[PTR] Map Sorting return: 0x%08X\n", mapSortingAddr + 0x07);
        }
        if (probeMapFilter1Addr) {
            g_RetAddr_Probe_MapFilter1 = reinterpret_cast<void*>(probeMapFilter1Addr + 0x05);
            Log(L"[PTR] Probe MapFilter1 return: 0x%08X\n", probeMapFilter1Addr + 0x05);
        }

        if (probeMapListFix1Addr) {
            g_RetAddr_MapListFixSupport1 = reinterpret_cast<void*>(probeMapListFix1Addr + 0x15);
            g_BZRFn_MapListFixSupport1 = reinterpret_cast<void (*)()>(0x007A3BD0);
            Log(L"[PTR] Map List Fix Support 1 return: 0x%08X\n", probeMapListFix1Addr + 0x15);
            Log(L"[PTR] Map List Fix Support 1 fallback: 0x%08X\n", 0x007A3BD0);
        }
        if (probeMapListFix2Addr) {
            g_RetAddr_Probe_MapListFix2 = reinterpret_cast<void*>(probeMapListFix2Addr + 0x05);
            Log(L"[PTR] Probe MapListFix2 return: 0x%08X\n", probeMapListFix2Addr + 0x05);
        }
        if (artilleryHowitzerVolleyAddr) {
            g_BZRFnPtr_ArtilleryHowitzerVolleyContinue =
                reinterpret_cast<void*>(artilleryHowitzerVolleyAddr + 0x06);
            Log(L"[PTR] Artillery howitzer volley continue: 0x%08X\n",
                artilleryHowitzerVolleyAddr + 0x06);
        }
        if (turretCraftAimPitchAddr) {
            g_RetAddr_TurretCraftAimPitchMultiplier =
                reinterpret_cast<void*>(turretCraftAimPitchAddr + 0x08);
            Log(L"[PTR] TurretCraft aim pitch return: 0x%08X\n",
                turretCraftAimPitchAddr + 0x08);
        }
        if (turretTankAimPitchAddr) {
            g_RetAddr_TurretTankAimPitchMultiplier =
                reinterpret_cast<void*>(turretTankAimPitchAddr + 0x08);
            Log(L"[PTR] TurretTank aim pitch return: 0x%08X\n",
                turretTankAimPitchAddr + 0x08);
        }
        if (underAttackAlertHook1Addr) {
            g_RetAddr_UnderAttackAlertHook1 =
                reinterpret_cast<void*>(underAttackAlertHook1Addr + 0x34);
            Log(L"[PTR] Under-attack alert hook 1 return: 0x%08X\n",
                underAttackAlertHook1Addr + 0x34);
        }
        if (underAttackAlertHook2Addr) {
            g_RetAddr_UnderAttackAlertHook2 =
                reinterpret_cast<void*>(underAttackAlertHook2Addr + 0x34);
            Log(L"[PTR] Under-attack alert hook 2 return: 0x%08X\n",
                underAttackAlertHook2Addr + 0x34);
        }
        if (offensiveAttackRevealAddr) {
            g_RetAddr_OffensiveAttackRevealHook =
                reinterpret_cast<void*>(offensiveAttackRevealAddr + 0x0C);
            Log(L"[PTR] Offensive attack reveal return: 0x%08X\n",
                offensiveAttackRevealAddr + 0x0C);
        }
        if (turretTankAttackRevealAddr) {
            g_RetAddr_TurretTankAttackRevealHook =
                reinterpret_cast<void*>(turretTankAttackRevealAddr + 0x0C);
            Log(L"[PTR] TurretTank attack reveal return: 0x%08X\n",
                turretTankAttackRevealAddr + 0x0C);
        }

        if (EnableExperimentalMapFilters())
        {
            g_RetAddr_MapFilters1 = reinterpret_cast<void*>(0x007A35C0);
            g_RetAddr_MapFilters2 = reinterpret_cast<void*>(0x00752D00);
            g_RetAddr_MapFilters3 = reinterpret_cast<void*>(0x0079D6B9);
            g_RetAddr_MapFilters4 = reinterpret_cast<void*>(0x0079D699);
            g_RetAddr_MapFilters5 = reinterpret_cast<void*>(0x0079916B);
            g_RetAddr_MapFilters7 = reinterpret_cast<void*>(0x007998B4);
            g_RetAddr_MapFilters8_A = reinterpret_cast<void*>(0x007997B2);
            g_RetAddr_MapFilters8_B = reinterpret_cast<void*>(0x007997B7);
            g_RetAddr_MapFilters8_C = reinterpret_cast<void*>(0x0079987C);
            Log(L"[PTR] MapFilters1 return: 0x%08X\n", 0x007A35C0);
            Log(L"[PTR] MapFilters2 return: 0x%08X\n", 0x00752D00);
            Log(L"[PTR] MapFilters3 return: 0x%08X\n", 0x0079D6B9);
            Log(L"[PTR] MapFilters4 return: 0x%08X\n", 0x0079D699);
            Log(L"[PTR] MapFilters5 return: 0x%08X\n", 0x0079916B);
            Log(L"[PTR] MapFilters7 return: 0x%08X\n", 0x007998B4);
            Log(L"[PTR] MapFilters8 return A: 0x%08X\n", 0x007997B2);
            Log(L"[PTR] MapFilters8 return B: 0x%08X\n", 0x007997B7);
            Log(L"[PTR] MapFilters8 return C: 0x%08X\n", 0x0079987C);
        }
        else
        {
            Log(L"[INFO] Experimental map-filter hooks disabled; using stock map filter UI\n");
        }

        // Vehicle list mod fix returns.
        g_RetAddr_VehicleListModFix1 = reinterpret_cast<void*>(0x00766C52);
        g_RetAddr_VehicleListModFix4 = reinterpret_cast<void*>(0x00798BE6);
        Log(L"[PTR] Vehicle ModFix1 return: 0x%08X\n", 0x00766C52);
        Log(L"[PTR] Vehicle ModFix4 return: 0x%08X\n", 0x00798BE6);

        // Lobby/BZRNET + ban button returns.
        g_RetAddr_BzrnetHost   = reinterpret_cast<void*>(0x00743C30);
        g_RetAddr_BzrnetClient = reinterpret_cast<void*>(0x0073E748);
        g_RetAddr_CommandHelpHandled = reinterpret_cast<void*>(0x00625052);
        g_RetAddr_CommandHelpFallback = reinterpret_cast<void*>(0x0062491F);
        g_RetAddr_JoinerEventHook = reinterpret_cast<void*>(0x0073F435);
        g_RetAddr_BanHook1     = reinterpret_cast<void*>(0x007D0A35);
        g_RetAddr_BanHook2     = reinterpret_cast<void*>(0x007A691A);
        g_RetAddr_AutoSaveLoadHook = reinterpret_cast<void*>(0x0078B45F);
        g_BZRFnPtr_JoinerEventOriginal = reinterpret_cast<void (*)()>(0x00742560);
        Log(L"[PTR] BZRNET Host return: 0x%08X\n", 0x00743C30);
        Log(L"[PTR] BZRNET Client return: 0x%08X\n", 0x0073E748);
        Log(L"[PTR] Command Help handled return: 0x%08X\n", 0x00625052);
        Log(L"[PTR] Command Help fallback return: 0x%08X\n", 0x0062491F);
        Log(L"[PTR] Joiner Event return: 0x%08X\n", 0x0073F435);
        Log(L"[PTR] Ban Hook1 return: 0x%08X\n", 0x007D0A35);
        Log(L"[PTR] Ban Hook2 return: 0x%08X\n", 0x007A691A);
        Log(L"[PTR] Joiner Event original: 0x%08X\n", 0x00742560);

        g_BZRFn_GetScrollState = reinterpret_cast<uint32_t (*)()>(0x007D3360);
        g_BZRFn_ScrollUp = reinterpret_cast<void (*)()>(0x007CB500);
        g_BZRFn_ScrollDown = reinterpret_cast<void (*)()>(0x007CB540);
        Log(L"[PTR] Scroll state helper: 0x%08X\n", 0x007D3360);
        Log(L"[PTR] Scroll up helper: 0x%08X\n", 0x007CB500);
        Log(L"[PTR] Scroll down helper: 0x%08X\n", 0x007CB540);

        Log(L"[OK]   Pointers resolved\n");
    }

    // -----------------------------------------------------------------------
    // Runtime pattern scanner - finds patch addresses by scanning memory
    // This works for both Steam and GOG versions since we search for actual
    // instruction patterns rather than hardcoded addresses.
    // -----------------------------------------------------------------------
    static void ScanForPatchAddresses(std::vector<PatchDef>& patches, bool isSteam)
    {
        Log(L"=========== SCANNING FOR PATTERNS ===========\n");

        // Define patterns to search for
        struct ScanTarget {
            const char* patchName;
            std::vector<uint8_t> pattern;
            std::vector<uint8_t> mask;  // 0xFF = must match, 0x00 = wildcard
            uint32_t patchOffset;
            uint32_t expectedSize;
        };

        std::vector<ScanTarget> targets = {
            // Hop-Fix 1 at 0x0079B85F (confirmed identical on Steam and GOG).
            // Unique 14-byte pattern verified against full process dump (1 hit only):
            //   8B 45 FC  = MOV EAX,[EBP-4]
            //   8B 88 38 01 00 00 = MOV ECX,[EAX+0x138]
            //   E8 F3 89 E3 FF = CALL (relative, follows directly - makes this unique)
            { "Map List Rewrite for Hop-Fix 1/3",
              { 0x8B, 0x45, 0xFC, 0x8B, 0x88, 0x38, 0x01, 0x00, 0x00, 0xE8, 0xF3, 0x89, 0xE3, 0xFF },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
              0,
              5 },

            // Hop-Fix 2 at 0x00799279 (confirmed identical on Steam and GOG).
            // Unique 15-byte pattern verified against full process dump (1 hit only):
            //   6A 00  = PUSH 0
            //   8B 85 5C FF FF FF = MOV EAX,[EBP-0xA4]
            //   8B 88 7C 01 00 00 = MOV ECX,[EAX+0x17C]  (7C 01 makes this unique vs other hits)
            //   E8 = CALL follows
            { "Map List Rewrite for Hop-Fix 2/3",
              { 0x6A, 0x00, 0x8B, 0x85, 0x5C, 0xFF, 0xFF, 0xFF, 0x8B, 0x88, 0x7C, 0x01, 0x00, 0x00, 0xE8 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
              0,
              5 },

            // Hop-Fix 3 at 0x00799377 (confirmed identical on Steam and GOG).
            // Unique 7-byte pattern verified against full process dump (1 hit only):
            //   FF D2 = CALL EDX
            //   68 30 09 00 00 = PUSH 0x930
            { "Map List Rewrite for Hop-Fix 3/3",
              { 0xFF, 0xD2, 0x68, 0x30, 0x09, 0x00, 0x00 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
              0,
              5 },
            { "HoverCraft Engine Flame Emit Hook 1/2",
              { 0x0F, 0x11, 0x04, 0x24, 0x8D, 0x85, 0x00, 0x00, 0x00, 0x00,
                0x50, 0xB9, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
                0x00, 0x83, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x84 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
                0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
                0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF },
              17,
              4 },
            { "HoverCraft Engine Flame Emit Hook 2/2",
              { 0x8D, 0x95, 0x00, 0x00, 0x00, 0x00, 0x52, 0xB9, 0x00, 0x00,
                0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00,
                0x00, 0x00, 0x83, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
                0x8E },
              { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
                0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
                0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                0xFF },
              13,
              4 },
            // Native artillery helper entry at 0x0042F840 on GOG.
            // The six-byte prologue is followed by a unique local setup block.
            { "Artillery Howitzer Volley Hook",
              { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x56, 0x89, 0x4D, 0xF8, 0x8B, 0x4D, 0xF8, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xE8, 0x01 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF },
              0,
              6 },
        };

        // Restrict scan to executable pages inside the main BZR.exe image.
        HMODULE hMain = GetModuleHandleA(nullptr);
        uint8_t* mainBase = reinterpret_cast<uint8_t*>(hMain);
        size_t mainSize = 0;
        if (hMain)
        {
            auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(hMain);
            if (dos->e_magic == IMAGE_DOS_SIGNATURE)
            {
                auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
                    reinterpret_cast<uint8_t*>(hMain) + dos->e_lfanew);
                if (nt->Signature == IMAGE_NT_SIGNATURE)
                    mainSize = nt->OptionalHeader.SizeOfImage;
            }
        }

        if (!mainBase || !mainSize)
        {
            Log(L"[SCAN] Failed to resolve main module bounds; skipping scan.\n");
            return;
        }

        uint8_t* mainEnd = mainBase + mainSize;
        Log(L"[SCAN] Main image: 0x%08X - 0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainBase)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainEnd)));

        // Scan BZR-only memory for each pattern
        HANDLE hProc = GetCurrentProcess();
        MEMORY_BASIC_INFORMATION mbi = {};
        uint8_t* addr = mainBase;

        // Collect all executable memory regions
        std::vector<std::pair<uint8_t*, size_t>> regions;
        while (addr < mainEnd && VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi))
        {
            uint8_t* rBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
            uint8_t* rEnd = rBase + mbi.RegionSize;
            if (rEnd <= mainBase || rBase >= mainEnd)
            {
                addr = rEnd;
                continue;
            }
            uint8_t* clipStart = (rBase < mainBase) ? mainBase : rBase;
            uint8_t* clipEnd = (rEnd > mainEnd) ? mainEnd : rEnd;
            size_t clipSize = static_cast<size_t>(clipEnd - clipStart);

            if (clipSize > 0 && mbi.State == MEM_COMMIT &&
                (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            {
                regions.push_back({ clipStart, clipSize });
            }
            addr = rEnd;
        }

        Log(L"[SCAN] Found %zu executable regions\n", regions.size());

        // Search for each pattern
        for (const auto& target : targets)
        {
            bool found = false;
            for (const auto& region : regions)
            {
                std::vector<uint8_t> buf(region.second);
                SIZE_T read = 0;
                if (!ReadProcessMemory(hProc, region.first, buf.data(), region.second, &read) || read == 0)
                    continue;
                if (read < target.pattern.size())
                    continue;

                for (size_t i = 0; i <= read - target.pattern.size(); i++)
                {
                    bool match = true;
                    for (size_t j = 0; j < target.pattern.size(); j++)
                    {
                        if ((buf[i + j] & target.mask[j]) != (target.pattern[j] & target.mask[j]))
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        uint32_t foundAddr = static_cast<uint32_t>(
                            reinterpret_cast<uintptr_t>(region.first + i));
                        const size_t patchIndex = i + target.patchOffset;
                        const uint32_t patchAddr = foundAddr + target.patchOffset;
                        
                        Log(L"[SCAN] Found '%hs' at 0x%08X\n", target.patchName, patchAddr);
                        
                        // Update the patch address
                        for (auto& p : patches)
                        {
                            if (strcmp(p.name, target.patchName) == 0)
                            {
                                p.bzr_address = patchAddr;
                                p.verified = true;
                                
                                p.expected_original.clear();
                                for (size_t j = 0; j < target.expectedSize && (patchIndex + j) < read; ++j)
                                    p.expected_original.push_back(buf[patchIndex + j]);
                                
                                found = true;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (found) break;
            }

            if (!found)
            {
                Log(L"[SCAN] Pattern '%hs' NOT FOUND\n", target.patchName);
            }
        }

        // Fallback for v2.2.301 when pattern scan misses due environment noise.
        // These Steam fixed sites are stable enough to use as a fallback once
        // the helper logic matches the intended map-sorting behavior.
        for (auto& p : patches)
        {
            if (p.verified) continue;

            if (strcmp(p.name, "Map Sorting") == 0)
            {
                p.bzr_address = 0x007680D6;
                p.verified = true;
                p.expected_original = { 0x89, 0x4D, 0xF8, 0x0F, 0xB6 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map List Rewrite for Hop-Fix 1/3") == 0)
            {
                p.bzr_address = 0x0079B85F;
                p.verified = true;
                p.expected_original = { 0x8B, 0x45, 0xFC, 0x8B, 0x88 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map List Rewrite for Hop-Fix 2/3") == 0)
            {
                p.bzr_address = 0x00799279;
                p.verified = true;
                p.expected_original = { 0x6A, 0x00, 0x8B, 0x85, 0x5C };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map List Rewrite for Hop-Fix 3/3") == 0)
            {
                p.bzr_address = 0x00799377;
                p.verified = true;
                p.expected_original = { 0xFF, 0xD2, 0x68, 0x30, 0x09 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map List Fix Support 1/3") == 0)
            {
                p.bzr_address = 0x00799774;
                p.verified = true;
                p.expected_original = { 0x89, 0x4D, 0xFC, 0x8B, 0x45 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Jump Fix Branch Override") == 0)
            {
                p.bzr_address = 0x007AA5A1;
                p.verified = true;
                p.expected_original = { 0x75 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Version Notice 1/2 OpenShim") == 0)
            {
                p.bzr_address = isSteam ? 0x004B022B : 0x0078DD4E;
                p.verified = true;
                p.expected_original = { 0xE4, 0x84, 0x87, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Version Notice 2/2 OpenShim") == 0)
            {
                p.bzr_address = isSteam ? 0x004B0247 : 0x00618C2F;
                p.verified = true;
                p.expected_original = { 0xE4, 0x84, 0x87, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Version Notice 3/3 OpenShim") == 0)
            {
                if (!isSteam)
                {
                    Log(L"[SCAN] SKIPPED %hs (Steam-only site)\n", p.name);
                    continue;
                }

                p.bzr_address = 0x005091F4;
                p.verified = true;
                p.expected_original = { 0xE4, 0x84, 0x87, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Main Menu GameVersion OpenShim") == 0)
            {
                if (!isSteam)
                {
                    Log(L"[SCAN] SKIPPED %hs (Steam-only site)\n", p.name);
                    continue;
                }

                p.bzr_address = 0x008EDA3C;
                p.verified = true;
                p.expected_original = { 0xE4, 0x84, 0x87, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Main Menu Version Text OpenShim") == 0)
            {
                p.bzr_address = 0x0078DD4E;
                p.verified = true;
                p.expected_original = { 0xE4, 0x84, 0x87, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3)") == 0)
            {
                p.bzr_address = 0x00766C4A;
                p.verified = true;
                p.expected_original = { 0xE8, 0xA1, 0xAE, 0xD1, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Vehicle List Mod Fix 2/4 (Force Mod-Scoped Assets 2/3)") == 0)
            {
                // rel32 operand for CALL at 0x0079A4F3
                p.bzr_address = 0x0079A4F4;
                p.verified = true;
                p.expected_original = { 0x68, 0x99, 0x00, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3)") == 0)
            {
                p.bzr_address = 0x00798BD9;
                p.verified = true;
                p.expected_original = { 0x51, 0xE8, 0xA1, 0xBB, 0xFC };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 3/8") == 0)
            {
                p.bzr_address = 0x0079D6B1;
                p.verified = true;
                p.expected_original = { 0x8B, 0xEC, 0x8B, 0x0D, 0x64 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 1/8") == 0)
            {
                p.bzr_address = 0x007A31D9;
                p.verified = true;
                p.expected_original = { 0x68, 0xE0, 0xB3, 0x89, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 2/8") == 0)
            {
                p.bzr_address = 0x00752A82;
                p.verified = true;
                p.expected_original = { 0xE8, 0x49, 0x04, 0x00, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 4/8") == 0)
            {
                p.bzr_address = 0x0079D691;
                p.verified = true;
                p.expected_original = { 0x8B, 0xEC, 0x8B, 0x0D, 0x64 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 5/8") == 0)
            {
                p.bzr_address = 0x00799116;
                p.verified = true;
                p.expected_original = { 0x52, 0x6A, 0x20, 0x6A, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 6/8") == 0)
            {
                p.bzr_address = 0x0079920A;
                p.verified = true;
                p.expected_original = { 0x92, 0x23, 0x03, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 7/8") == 0)
            {
                p.bzr_address = 0x007998AB;
                p.verified = true;
                p.expected_original = { 0x8B, 0x45, 0xBC, 0x8B, 0x88 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Filters 8/8") == 0)
            {
                p.bzr_address = 0x007997A9;
                p.verified = true;
                p.expected_original = { 0x8B, 0x45, 0xF8, 0x8B, 0x88 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Chunk Render Resolve Hook") == 0)
            {
                // rel32 operand for CALL 0x004E3620 at 0x00443B34
                p.bzr_address = 0x00443B35;
                p.verified = true;
                p.expected_original = { 0xE7, 0xFA, 0x09, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Producer Build Menu Root Hook") == 0)
            {
                // rel32 operand for CALL 0x0082BA59 at 0x004FFA9E
                p.bzr_address = 0x004FFA9F;
                p.verified = true;
                p.expected_original = { 0xB6, 0xBF, 0x32, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Target Reticle Popup Recent-Hit Getter Hook") == 0)
            {
                // rel32 operand for CALL 0x00497890 at 0x00497C26
                p.bzr_address = 0x00497C27;
                p.verified = true;
                p.expected_original = { 0x65, 0xFC, 0xFF, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "HoverCraft Engine Flame Emit Hook 1/2") == 0)
            {
                p.bzr_address = 0x004EAD78;
                p.verified = true;
                p.expected_original = { 0x84, 0xDA, 0xFD, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "HoverCraft Engine Flame Emit Hook 2/2") == 0)
            {
                p.bzr_address = 0x004EAFDF;
                p.verified = true;
                p.expected_original = { 0x1D, 0xD8, 0xFD, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Engine Flame Control VTable Hook") == 0)
            {
                p.bzr_address = 0x008791A4;
                p.verified = true;
                p.expected_original = { 0xA0, 0x88, 0x4C, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Engine Flame Submit VTable Hook") == 0)
            {
                p.bzr_address = 0x008791AC;
                p.verified = true;
                p.expected_original = { 0xC0, 0x88, 0x4C, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Chunk Effect Simulate VTable Hook") == 0)
            {
                p.bzr_address = 0x0087708C;
                p.verified = true;
                p.expected_original = { 0xF0, 0x17, 0x49, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Artillery Howitzer Volley Hook") == 0)
            {
                p.bzr_address = 0x0042F840;
                p.verified = true;
                p.expected_original = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Decoded Weapon Mask Carrier Bias Hook") == 0)
            {
                p.bzr_address = 0x00417C80;
                p.verified = true;
                p.expected_original = { 0x55, 0x8B, 0xEC, 0x51, 0x89 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Raw Weapon Mask Carrier Bias Hook") == 0)
            {
                p.bzr_address = 0x0046DD70;
                p.verified = true;
                p.expected_original = { 0x55, 0x8B, 0xEC, 0x51, 0x89 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Lobby BZRNET Integration HOST") == 0)
            {
                p.bzr_address = 0x00743C05;
                p.verified = true;
                p.expected_original = { 0x8D, 0x85, 0x00, 0xFF, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Lobby BZRNET Integration CLIENT") == 0)
            {
                p.bzr_address = 0x0073E71C;
                p.verified = true;
                p.expected_original = { 0xC6, 0x45, 0xFC, 0x07, 0x8D };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Custom Command /help Handler") == 0)
            {
                p.bzr_address = 0x0062480B;
                p.verified = true;
                p.expected_original = { 0x68, 0x3C, 0xD5, 0x88, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Joiner Event Hook") == 0)
            {
                p.bzr_address = 0x0073F430;
                p.verified = true;
                p.expected_original = { 0xE8, 0x2B, 0x31, 0x00, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Ban Button Hook 1/2") == 0)
            {
                p.bzr_address = 0x007D0A2F;
                p.verified = true;
                p.expected_original = { 0x0F, 0xB6, 0x45, 0x20, 0x85 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Ban Button Hook 2/2") == 0)
            {
                p.bzr_address = 0x007A6913;
                p.verified = true;
                p.expected_original = { 0xC7, 0x45, 0xFC, 0xFF, 0xFF };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "AutoSave Load Button Hook") == 0)
            {
                p.bzr_address = 0x0078B45A;
                p.verified = true;
                p.expected_original = { 0xA1, 0x0C, 0x83, 0x91, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Restart Mission Hook Pause") == 0)
            {
                p.bzr_address = 0x00788F40;
                p.verified = true;
                p.expected_original = { 0x55, 0x8B, 0xEC, 0x51, 0x89 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Restart Mission Hook Failure") == 0)
            {
                p.bzr_address = 0x00791F50;
                p.verified = true;
                p.expected_original = { 0x55, 0x8B, 0xEC, 0x51, 0x89 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "TurretCraft Aim Pitch Multiplier") == 0)
            {
                p.bzr_address = 0x005F1838;
                p.verified = true;
                p.expected_original = { 0xF3, 0x0F, 0x10, 0x05, 0x84, 0x25, 0x8A, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "TurretTank Aim Pitch Multiplier") == 0)
            {
                p.bzr_address = 0x005F561A;
                p.verified = true;
                p.expected_original = { 0xF3, 0x0F, 0x10, 0x05, 0x84, 0x25, 0x8A, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Under Attack Alert Hook 1/2") == 0)
            {
                p.bzr_address = 0x00494D35;
                p.verified = true;
                p.expected_original = { 0x0F, 0x2F, 0x05, 0xD0, 0x73 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Under Attack Alert Hook 2/2") == 0)
            {
                p.bzr_address = 0x0050E6DD;
                p.verified = true;
                p.expected_original = { 0x0F, 0x2F, 0x05, 0xD0, 0x73 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Offensive Attack Reveal Hook") == 0)
            {
                p.bzr_address = 0x005839E0;
                p.verified = true;
                p.expected_original = { 0x8B, 0x4D, 0xF8, 0x8B, 0x55, 0xF8, 0x8B, 0x42, 0x1C, 0x89, 0x41, 0x24 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "TurretTank Attack Reveal Hook") == 0)
            {
                p.bzr_address = 0x005F73F3;
                p.verified = true;
                p.expected_original = { 0x8B, 0x55, 0xF8, 0x8B, 0x45, 0xF8, 0x8B, 0x48, 0x1C, 0x89, 0x4A, 0x24 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else
            {
                Log(L"[SCAN] SKIPPED %hs (pattern not found, no safe fallback)\n", p.name);
            }
        }
    }

    static void FillJmp5Payloads(std::vector<PatchDef>& patches)
    {
        // Map patch names to their trampoline addresses
        struct { const char* name; void* fn; } map[] =
        {
            { "Map Sorting",                                     (void*)Trampoline_Probe_MapSorting },
            { "Map List Rewrite for Hop-Fix 1/3",              (void*)Trampoline_HopFix1 },
            { "Map List Rewrite for Hop-Fix 2/3",              (void*)Trampoline_HopFix2 },
            { "Map List Rewrite for Hop-Fix 3/3",              (void*)Trampoline_HopFix3 },
            { "Map List Fix Support 1/3",                       (void*)Trampoline_MapListFixSupport1 },
            { "Probe Refresh Path MapFilter1",                 (void*)Trampoline_Probe_MapFilter1 },
            { "Probe MapListFix1",                              (void*)Trampoline_Probe_MapListFix1 },
            { "Probe MapListFix2",                              (void*)Trampoline_Probe_MapListFix2 },
            { "Map Filters 1/8",                                (void*)Trampoline_MapFilters1 },
            { "Map Filters 2/8",                                (void*)Trampoline_MapFilters2 },
            { "Map Filters 3/8",                                (void*)Trampoline_MapFilters3 },
            { "Map Filters 4/8",                                (void*)Trampoline_MapFilters4 },
            { "Map Filters 5/8",                                (void*)Trampoline_MapFilters5 },
            { "Map Filters 7/8",                                (void*)Trampoline_MapFilters7 },
            { "Map Filters 8/8",                                (void*)Trampoline_MapFilters8 },
            { "Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3)", (void*)Trampoline_VehicleListModFix1 },
            { "Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3)", (void*)Trampoline_VehicleListModFix4 },
            { "Lobby BZRNET Integration HOST",                  (void*)Trampoline_BzrnetHost },
            { "Lobby BZRNET Integration CLIENT",                (void*)Trampoline_BzrnetClient },
            { "Custom Command /help Handler",                   (void*)Trampoline_CommandHelp },
            { "Joiner Event Hook",                              (void*)Trampoline_JoinerEventHook },
            { "Ban Button Hook 1/2",                            (void*)Trampoline_BanButtonHook1 },
            { "Ban Button Hook 2/2",                            (void*)Trampoline_BanButtonHook2 },
            { "AutoSave Load Button Hook",                      (void*)Trampoline_AutoSaveLoadButtonHook },
            { "Restart Mission Hook Pause",                     (void*)Trampoline_RestartMissionPauseHook },
            { "Restart Mission Hook Failure",                   (void*)Trampoline_RestartMissionFailureHook },
            { "TurretCraft Aim Pitch Multiplier",               (void*)Trampoline_TurretCraftAimPitchMultiplier },
            { "TurretTank Aim Pitch Multiplier",                (void*)Trampoline_TurretTankAimPitchMultiplier },
            { "Under Attack Alert Hook 1/2",                    (void*)Trampoline_UnderAttackAlertHook1 },
            { "Under Attack Alert Hook 2/2",                    (void*)Trampoline_UnderAttackAlertHook2 },
            { "Offensive Attack Reveal Hook",                   (void*)Trampoline_OffensiveAttackRevealHook },
            { "TurretTank Attack Reveal Hook",                  (void*)Trampoline_TurretTankAttackRevealHook },
            { "Artillery Howitzer Volley Hook",                 (void*)Trampoline_ArtilleryHowitzerVolley },
            { "Decoded Weapon Mask Carrier Bias Hook",          (void*)Trampoline_DecodedWeaponMaskBias },
            { "Raw Weapon Mask Carrier Bias Hook",              (void*)Trampoline_RawWeaponMaskBias },
        };

        for (auto& p : patches)
        {
            if (p.type != PatchType::JMP5) continue;
            if (!p.verified) continue;   // skip unverified entries

            for (auto& m : map)
            {
                if (strcmp(p.name, m.name) == 0 && m.fn)
                {
                    uint32_t targetVal = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m.fn));
                    const size_t patchLen =
                        (strcmp(p.name, "TurretCraft Aim Pitch Multiplier") == 0 ||
                         strcmp(p.name, "TurretTank Aim Pitch Multiplier") == 0) ? 8 :
                        ((strcmp(p.name, "Offensive Attack Reveal Hook") == 0 ||
                          strcmp(p.name, "TurretTank Attack Reveal Hook") == 0) ? 12 :
                        (strcmp(p.name, "Artillery Howitzer Volley Hook") == 0 ? 6 :
                        ((strcmp(p.name, "Under Attack Alert Hook 1/2") == 0 ||
                          strcmp(p.name, "Under Attack Alert Hook 2/2") == 0) ? 52 : 5)));
                    p.payload = MakeJmpPatch(p.bzr_address, targetVal, patchLen);
                    break;
                }
            }
        }
    }

    static void FillRel32Payloads(std::vector<PatchDef>& patches, bool isSteam)
    {
        for (auto& p : patches)
        {
            if (p.type != PatchType::REL32) continue;
            if (!p.verified) continue;
            if (strcmp(p.name, "Vehicle List Mod Fix 2/4 (Force Mod-Scoped Assets 2/3)") == 0)
            {
                // Patch address points at the rel32 operand (CALL +1).
                uint32_t instrAddr = p.bzr_address - 1;
                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(VehicleListModFix2));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
            else if (strcmp(p.name, "Map Filters 6/8") == 0)
            {
                uint32_t instrAddr = p.bzr_address - 1;
                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(MapFilters6Rel32));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
            else if (strcmp(p.name, "Chunk Render Resolve Hook") == 0)
            {
                uint32_t instrAddr = p.bzr_address - 1;
                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(ChunkRenderResolveHook));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
            else if (strcmp(p.name, "Producer Build Menu Root Hook") == 0)
            {
                uint32_t instrAddr = p.bzr_address - 1;
                void* originalTarget = nullptr;
                if (isSteam)
                {
                    originalTarget = ResolveRelCallTargetWithRetry(instrAddr, 300, 10);
                }
                else
                {
                    originalTarget = ResolveRelCallTarget(instrAddr);
                }
                if (!originalTarget)
                {
                    Log(L"[SKIP] %hs (failed to resolve original call target)\n", p.name);
                    continue;
                }

                SetProducerBuildMenuOriginal(originalTarget);

                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(ProducerBuildMenuCallHook));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
            else if (strcmp(p.name, "Target Reticle Popup Recent-Hit Getter Hook") == 0)
            {
                uint32_t instrAddr = p.bzr_address - 1;
                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(TargetReticlePopupRecentHitGetterHook));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
            else if (strcmp(p.name, "HoverCraft Engine Flame Emit Hook 1/2") == 0 ||
                     strcmp(p.name, "HoverCraft Engine Flame Emit Hook 2/2") == 0)
            {
                uint32_t instrAddr = p.bzr_address - 1;
                uint32_t target = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(Trampoline_EngineFlameHoverCraftEmit));
                int32_t rel = static_cast<int32_t>(target) - static_cast<int32_t>(instrAddr + 5);
                p.payload.resize(4);
                memcpy(p.payload.data(), &rel, sizeof(rel));
            }
        }
    }

    static void FillVersionNoticePayloads(std::vector<PatchDef>& patches)
    {
        const uint32_t tagPtr = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(kOpenShimVersionTag));
        uint8_t tagBytes[4] = {};
        memcpy(tagBytes, &tagPtr, sizeof(tagBytes));
        const uint32_t engineFlameControlHook = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(EngineFlameControlHook));
        const uint32_t engineFlameSubmitHook = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(EngineFlameSubmitHook));
        const uint32_t chunkEffectSimulateHook = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(ChunkEffectSimulateHook));
        uint8_t engineFlameControlBytes[4] = {};
        uint8_t engineFlameSubmitBytes[4] = {};
        uint8_t chunkEffectSimulateBytes[4] = {};
        memcpy(engineFlameControlBytes, &engineFlameControlHook, sizeof(engineFlameControlBytes));
        memcpy(engineFlameSubmitBytes, &engineFlameSubmitHook, sizeof(engineFlameSubmitBytes));
        memcpy(chunkEffectSimulateBytes, &chunkEffectSimulateHook, sizeof(chunkEffectSimulateBytes));

        for (auto& p : patches)
        {
            if (p.type != PatchType::DWORD) continue;
            if (strcmp(p.name, "Version Notice 1/2 OpenShim") == 0 ||
                strcmp(p.name, "Version Notice 2/2 OpenShim") == 0 ||
                strcmp(p.name, "Version Notice 3/3 OpenShim") == 0 ||
                strcmp(p.name, "Main Menu GameVersion OpenShim") == 0 ||
                strcmp(p.name, "Main Menu Version Text OpenShim") == 0)
            {
                p.payload.assign(tagBytes, tagBytes + sizeof(tagBytes));
            }
            else if (strcmp(p.name, "Engine Flame Control VTable Hook") == 0)
            {
                p.payload.assign(engineFlameControlBytes, engineFlameControlBytes + sizeof(engineFlameControlBytes));
            }
            else if (strcmp(p.name, "Engine Flame Submit VTable Hook") == 0)
            {
                p.payload.assign(engineFlameSubmitBytes, engineFlameSubmitBytes + sizeof(engineFlameSubmitBytes));
            }
            else if (strcmp(p.name, "Chunk Effect Simulate VTable Hook") == 0)
            {
                p.payload.assign(chunkEffectSimulateBytes, chunkEffectSimulateBytes + sizeof(chunkEffectSimulateBytes));
            }
        }
    }

    static void WaitForExpectedBytes(std::vector<PatchDef>& patches, bool isSteam)
    {
        if (!isSteam)
            return;

        const char* const steamTrackedNames[] =
        {
            "Version Notice 1/2 OpenShim",
            "Version Notice 2/2 OpenShim",
            "Version Notice 3/3 OpenShim",
            "Main Menu Version Text OpenShim",
            "Offensive Attack Reveal Hook",
            "TurretTank Attack Reveal Hook",
        };

        auto isTrackedPatch = [&steamTrackedNames](const PatchDef& patch) -> bool
        {
            for (const char* name : steamTrackedNames)
            {
                if (strcmp(patch.name, name) == 0)
                    return true;
            }
            return false;
        };

        Log(L"[INFO] Waiting for Steam tracked patch sites to settle...\n");
        constexpr int kMaxAttempts = 2500;
        constexpr DWORD kDelayMs = 10;

        for (int attempt = 0; attempt < kMaxAttempts; ++attempt)
        {
            bool allReady = true;

            for (const auto& patch : patches)
            {
                if (!isTrackedPatch(patch) || patch.expected_original.empty() || patch.bzr_address == 0)
                    continue;

                std::vector<uint8_t> current(patch.expected_original.size());
                SIZE_T read = 0;
                if (!ReadProcessMemory(
                        GetCurrentProcess(),
                        reinterpret_cast<const void*>(patch.bzr_address),
                        current.data(),
                        current.size(),
                        &read) ||
                    read != current.size() ||
                    current != patch.expected_original)
                {
                    allReady = false;
                    break;
                }
            }

            if (allReady)
            {
                Log(L"[OK]   Steam version notice sites settled after %d attempts\n", attempt + 1);
                return;
            }

            Sleep(kDelayMs);
        }

        Log(L"[WARN] Steam version notice sites never settled; version tag patches may be skipped\n");
    }

    // -----------------------------------------------------------------------
    // RunPatcher - main patch thread
    // -----------------------------------------------------------------------
    void RunPatcher(uint32_t shimVersion)
    {
        // 1. Open log
        _wfopen_s(&g_Log, L"winmm_shim.log", L"w");
        if (g_Log)
        {
            Log(L"=========== BZR Open Shim ===========\n");
            Log(L"Open source DLL patcher\n");
            Log(L"Shim Version: %u\n", shimVersion);
        }

        const bool isSteam = IsSteamExe();
        Log(L"[INFO] Executable: %hs\n", isSteam ? "battlezone98redux.exe (Steam)" : "BZR.exe (GOG)");
        g_EnableScrollRestore = true;
        Log(L"[INFO] HopFix helpers %hs for %hs\n",
            ShouldEnableMapRefreshFixes(isSteam) ? "enabled" : "disabled",
            isSteam ? "Steam" : "GOG");
        Log(L"[INFO] Lobby BZRNET integration hooks %hs for %hs\n",
            ShouldEnableLobbyBzrnetIntegration(isSteam) ? "enabled" : "disabled",
            isSteam ? "Steam" : "GOG");

        if (ShouldEnableD3DStartupHooks())
        {
            Log(L"[INFO] D3D startup hooks enabled via OPENSHIM_ENABLE_D3D_STARTUP_HOOKS\n");
            ApplyD3DStartupHooks();
        }
        else
        {
            Log(L"[INFO] D3D startup hooks disabled by default\n");
        }

        ApplyTrnSaveNormalizeHooks();

        // 2. Check BZR.exe version
        uint32_t gameVer = GetBZRVersion();
        Log(L"[INFO] Detected BZR version: %u (expected %u)\n", gameVer, BZR_EXPECTED_VERSION);
        if (gameVer != BZR_EXPECTED_VERSION)
        {
            Log(L"[FAIL] Version mismatch; aborting patcher\n");
            return;
        }

        // 3. Wait for signature (SteamStub decrypt gate)
        std::vector<uint8_t> signature;
        if (!ReadExeSignature(signature))
            Log(L"[WARN] Signature read failed; proceeding without gate\n");
        else if (!WaitForSignature(signature))
            return;

        StartSoundChannelOverride(isSteam);

        // 4. Build patch list and resolve dynamic addresses
        auto patches = BuildPatchList();
        FilterPatchesForRuntime(patches, isSteam);
        if (ShouldEnableArtilleryMaskTracePatch())
        {
            Log(L"[INFO] Artillery weapon-mask trace enabled via OPENSHIM_TRACE_ARTILLERY_MASK\n");
        }
        ScanForPatchAddresses(patches, isSteam);

        auto findAddr = [&patches](const char* name) -> uint32_t
        {
            for (const auto& p : patches)
            {
                if (strcmp(p.name, name) == 0)
                    return p.bzr_address;
            }
            return 0;
        };

        ResolvePointers(
            findAddr("Map Sorting"),
            findAddr("Map List Rewrite for Hop-Fix 1/3"),
            findAddr("Map List Rewrite for Hop-Fix 2/3"),
            findAddr("Map List Rewrite for Hop-Fix 3/3"),
            findAddr("Probe Refresh Path MapFilter1"),
            findAddr("Map List Fix Support 1/3"),
            findAddr("Probe MapListFix2"),
            findAddr("Artillery Howitzer Volley Hook"),
            findAddr("TurretCraft Aim Pitch Multiplier"),
            findAddr("TurretTank Aim Pitch Multiplier"),
            findAddr("Under Attack Alert Hook 1/2"),
            findAddr("Under Attack Alert Hook 2/2"),
            findAddr("Offensive Attack Reveal Hook"),
            findAddr("TurretTank Attack Reveal Hook"));

        ResolveBzrHooks(isSteam);
        InitBzrHookStrings();
        SuppressStartupShellAutoLoad();

        FillJmp5Payloads(patches);
        FillVersionNoticePayloads(patches);
        FillRel32Payloads(patches, isSteam);
        WaitForExpectedBytes(patches, isSteam);
        RetryDeferredRuntimeHooks();

        // 5. Apply patches
        int applied = 0;
        int skipped = 0;
        int failed  = 0;

        for (const auto& p : patches)
        {
            int result = 0;
            switch (p.type)
            {
            case PatchType::JMP5:
                if (p.payload.size() < 5)
                {
                    Log(L"[SKIP] %hs (jmp payload missing)\n", p.name);
                    result = 0;
                }
                else
                {
                    result = ApplyPatch(p.bzr_address, p.payload.data(), p.payload.size(),
                                        p.name, p.expected_original);
                }
                break;
            case PatchType::DWORD:
                if (p.payload.size() < 4)
                {
                    Log(L"[SKIP] %hs (DWORD payload missing)\n", p.name);
                    result = 0;
                }
                else
                {
                    result = ApplyPatch(p.bzr_address, p.payload.data(), 4,
                                        p.name, p.expected_original);
                }
                break;
            case PatchType::REL32:
                if (p.payload.size() < 4)
                {
                    Log(L"[SKIP] %hs (REL32 payload missing)\n", p.name);
                    result = 0;
                }
                else
                {
                    result = ApplyPatch(p.bzr_address, p.payload.data(), 4,
                                        p.name, p.expected_original);
                }
                break;
            case PatchType::BYTE1:
                if (p.payload.empty())
                {
                    Log(L"[SKIP] %hs (BYTE payload missing)\n", p.name);
                    result = 0;
                }
                else
                {
                    result = ApplyPatch(p.bzr_address, p.payload.data(), 1,
                                        p.name, p.expected_original);
                }
                break;
            case PatchType::BYTES:
                if (p.payload.empty())
                {
                    Log(L"[SKIP] %hs (BYTES payload missing)\n", p.name);
                    result = 0;
                }
                else
                {
                    result = ApplyPatch(p.bzr_address, p.payload.data(), p.payload.size(),
                                        p.name, p.expected_original);
                }
                break;
            default:
                Log(L"[SKIP] %hs (unknown patch type)\n", p.name);
                result = 0;
                break;
            }

            if (result > 0) ++applied;
            else if (result < 0) ++failed;
            else ++skipped;
        }

        Log(L"[DONE] Applied=%d Skipped=%d Failed=%d\n", applied, skipped, failed);

        // Keep the log file open for runtime hook telemetry (LogHit in trampolines).
        // Closing here leaves g_Log dangling while hooks are still active.
    }

} // namespace BZROpenShim
