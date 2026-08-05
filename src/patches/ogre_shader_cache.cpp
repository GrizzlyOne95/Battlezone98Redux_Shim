// ogre_shader_cache.cpp
// BZR Open Shim - Ogre GpuProgram microcode cache bridge
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Root cause this fixes: the game unloads/clears/reinitialises the "Modable"
// resource group on every mission load AND when leaving a game back to the
// shell. Parsing the mod's *.program scripts recompiles every HLSL program
// whose unified wrapper carries default_params, and the enhanced-lighting
// ps_3_0 fragment variants (MAX_LIGHTS=24 with a mandatory [unroll] loop —
// ps_3_0 cannot index constants dynamically — plus 4x4 PCF shadow unrolls)
// cost seconds of D3DXCompileShader each. That is the ~30 s "Leave Game"
// freeze observed in BZOgreLogfile.log as 4-6 s gaps bracketing the
// CR_*EN* shader lines.
//
// Ogre 1.10's GpuProgramManager already ships a microcode cache and the
// bundled RenderSystem_Direct3D9.dll imports the full cache API
// (isMicrocodeAvailableInCache / getMicrocodeFromCache / addMicrocodeToCache
// gated on getSaveMicrocodesToCache). The engine just never turns it on.
// This module enables the save flag, loads a cache file at startup, and
// saves it whenever new microcode was added, keyed by a fingerprint of the
// mod shader sources so stale microcode is never used after shader edits.
//
// ABI notes (verified against the shipped OgreMain.dll):
//  - SharedPtr<DataStream> is 8 bytes: loadMicrocodeCache's callee-cleanup
//    is `ret 8` (Ogre 1.10 {pRep, pInfo} layout).
//  - Streams are obtained from Root::openFileStream/createFileStream so the
//    engine constructs every SharedPtr itself; we pass the returned 8-byte
//    blob by value exactly once (MSVC callee-destroys by-value args, which
//    releases the engine-owned reference) and never touch it again.
//  - setSaveMicrocodesToCache is not exported; the exported getter
//    disassembles to `mov al, [ecx+0xEC]; ret`, so the flag byte offset is
//    parsed from the getter body at runtime (fallback 0xEC) and the write is
//    verified through the exported getter afterwards.

#include "ogre_shader_cache.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwctype>
#include <filesystem>
#include <mutex>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        struct OgreDataStreamPtrPod
        {
            void* a = nullptr;
            void* b = nullptr;
        };
        static_assert(sizeof(OgreDataStreamPtrPod) == 8,
            "Ogre 1.10 SharedPtr<DataStream> passes as 8 bytes (loadMicrocodeCache rets 8)");

        using FnOgreSingletonPtr = void* (__cdecl*)();
        using FnOgreBoolThis = uint8_t(__thiscall*)(const void*);
        using FnOgreLoadMicrocodeCache = void(__thiscall*)(void*, OgreDataStreamPtrPod);
        using FnOgreSaveMicrocodeCache = void(__thiscall*)(const void*, OgreDataStreamPtrPod);
        using FnRootOpenFileStream = OgreDataStreamPtrPod* (__thiscall*)(
            void*, OgreDataStreamPtrPod*,
            const std::string&, const std::string&, const std::string&);
        using FnRootCreateFileStream = OgreDataStreamPtrPod* (__thiscall*)(
            void*, OgreDataStreamPtrPod*,
            const std::string&, const std::string&, bool, const std::string&);

        constexpr uint32_t kSaveFlagFallbackOffset = 0xEC;
        constexpr uint32_t kSaveFlagMaxReasonableOffset = 0x400;
        constexpr ULONGLONG kSaveThrottleMs = 10000;
        constexpr uintmax_t kMaxReasonableCacheBytes = 256ull * 1024 * 1024;
        constexpr const char* kFingerprintVersion = "v1";

        std::mutex g_Mutex;
        std::atomic<bool> g_InitDone{ false };
        bool g_Disabled = false;
        bool g_DisabledLogged = false;
        bool g_SaveFlagEnabled = false;
        ULONGLONG g_LastSaveAttemptTick = 0;
        uint64_t g_ShaderFingerprint = 0;

        void* g_Gpm = nullptr;
        void* g_Root = nullptr;
        FnOgreBoolThis g_FnGetSaveMicrocodesToCache = nullptr;
        FnOgreBoolThis g_FnIsCacheDirty = nullptr;
        FnOgreLoadMicrocodeCache g_FnLoadMicrocodeCache = nullptr;
        FnOgreSaveMicrocodeCache g_FnSaveMicrocodeCache = nullptr;
        FnRootOpenFileStream g_FnOpenFileStream = nullptr;
        FnRootCreateFileStream g_FnCreateFileStream = nullptr;

        static bool EnvFlagSet(const char* name)
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return len >= sizeof(value);
            return !(value[0] == '0' && value[1] == '\0');
        }

        static std::filesystem::path GetGameRootDirectory()
        {
            wchar_t buffer[MAX_PATH] = {};
            const DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
            if (len == 0 || len >= MAX_PATH)
                return {};
            return std::filesystem::path(buffer).parent_path();
        }

        static std::filesystem::path GetCacheFilePath()
        {
            return GetGameRootDirectory() / L"shader_cache" / L"ogre_microcode.cache";
        }

        static std::filesystem::path GetFingerprintFilePath()
        {
            return GetGameRootDirectory() / L"shader_cache" / L"ogre_microcode.fp";
        }

        static bool IsShaderSourceExtension(const std::wstring& extLower)
        {
            return extLower == L".program" || extLower == L".hlsl" ||
                   extLower == L".cg" || extLower == L".glsl" ||
                   extLower == L".glsles" || extLower == L".frag" ||
                   extLower == L".vert";
        }

        // FNV-1a over (relative path, size, mtime) of every shader source file
        // under the mod content roots. Stock shader sources live inside the
        // game's archives and never change between sessions; mod shaders are
        // the ones users edit, and stale microcode after an edit would be
        // silently wrong, so their fingerprint keys the cache file.
        static uint64_t ComputeShaderSourceFingerprint()
        {
            uint64_t hash = 1469598103934665603ull;
            const auto mix = [&hash](const void* data, size_t size)
            {
                const auto* bytes = static_cast<const uint8_t*>(data);
                for (size_t i = 0; i < size; ++i)
                {
                    hash ^= bytes[i];
                    hash *= 1099511628211ull;
                }
            };

            const std::filesystem::path root = GetGameRootDirectory();
            const std::filesystem::path scanRoots[] =
            {
                root / L"mods",
                root / L"packaged_mods",
                // Steam install: workshop content sits outside the game root.
                root / L".." / L".." / L"workshop" / L"content" / L"301650",
            };

            size_t filesSeen = 0;
            for (const auto& scanRoot : scanRoots)
            {
                std::error_code ec;
                if (!std::filesystem::is_directory(scanRoot, ec))
                    continue;
                std::filesystem::recursive_directory_iterator it(
                    scanRoot,
                    std::filesystem::directory_options::skip_permission_denied,
                    ec);
                const std::filesystem::recursive_directory_iterator end;
                for (; !ec && it != end && filesSeen < 50000; it.increment(ec))
                {
                    if (!it->is_regular_file(ec))
                        continue;
                    std::wstring ext = it->path().extension().wstring();
                    for (auto& ch : ext)
                        ch = static_cast<wchar_t>(::towlower(ch));
                    if (!IsShaderSourceExtension(ext))
                        continue;

                    std::wstring name = it->path().filename().wstring();
                    for (auto& ch : name)
                        ch = static_cast<wchar_t>(::towlower(ch));
                    mix(name.data(), name.size() * sizeof(wchar_t));
                    const uintmax_t size = it->file_size(ec);
                    mix(&size, sizeof(size));
                    const auto mtime = it->last_write_time(ec).time_since_epoch().count();
                    mix(&mtime, sizeof(mtime));
                    ++filesSeen;
                }
            }
            mix(&filesSeen, sizeof(filesSeen));
            return hash ? hash : 1ull;
        }

        static bool ReadStoredFingerprint(uint64_t& outFingerprint)
        {
            outFingerprint = 0;
            FILE* file = nullptr;
            if (_wfopen_s(&file, GetFingerprintFilePath().c_str(), L"r") != 0 || !file)
                return false;
            char version[16] = {};
            unsigned long long stored = 0;
            const bool ok = std::fscanf(file, "%15s %llx", version, &stored) == 2 &&
                std::strcmp(version, kFingerprintVersion) == 0;
            std::fclose(file);
            if (ok)
                outFingerprint = stored;
            return ok;
        }

        static bool WriteStoredFingerprint(uint64_t fingerprint)
        {
            FILE* file = nullptr;
            if (_wfopen_s(&file, GetFingerprintFilePath().c_str(), L"w") != 0 || !file)
                return false;
            std::fprintf(file, "%s %016llx\n",
                kFingerprintVersion,
                static_cast<unsigned long long>(fingerprint));
            std::fclose(file);
            return true;
        }

        template <typename T>
        static T ResolveOgreMainProc(const char* name)
        {
            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return nullptr;
            return reinterpret_cast<T>(GetProcAddress(ogreMain, name));
        }

        // --- POD-frame SEH boundaries -----------------------------------
        // Ogre throws C++ exceptions (FileNotFound and friends) and a bad
        // cache file could fault outright; C++ throws surface as SEH
        // 0xE06D7363, so one __except handler covers both. Frames below hold
        // no unwindable objects.

        static bool SehParseSaveFlagOffset(const uint8_t* code, uint32_t* outOffset)
        {
            __try
            {
                for (int hop = 0; hop < 4 && code[0] == 0xE9; ++hop)
                    code += 5 + *reinterpret_cast<const int32_t*>(code + 1);
                if (code[0] == 0x8A && code[1] == 0x81 && code[6] == 0xC3)
                {
                    *outOffset = *reinterpret_cast<const uint32_t*>(code + 2);
                    return true;
                }
                if (code[0] == 0x8A && code[1] == 0x41 && code[3] == 0xC3)
                {
                    *outOffset = code[2];
                    return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        static bool SehWriteByte(void* address, uint8_t value)
        {
            __try
            {
                *static_cast<uint8_t*>(address) = value;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehCallBoolGetter(FnOgreBoolThis fn, const void* self, uint8_t* outValue)
        {
            __try
            {
                *outValue = fn(self);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehOpenFileStream(
            FnRootOpenFileStream fn,
            void* root,
            OgreDataStreamPtrPod* out,
            const std::string* file,
            const std::string* group,
            const std::string* pattern)
        {
            __try
            {
                fn(root, out, *file, *group, *pattern);
                return out->a != nullptr || out->b != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehCreateFileStream(
            FnRootCreateFileStream fn,
            void* root,
            OgreDataStreamPtrPod* out,
            const std::string* file,
            const std::string* group,
            const std::string* pattern)
        {
            __try
            {
                fn(root, out, *file, *group, true, *pattern);
                return out->a != nullptr || out->b != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehLoadMicrocodeCache(
            FnOgreLoadMicrocodeCache fn, void* gpm, const OgreDataStreamPtrPod* stream)
        {
            __try
            {
                // By-value pass transfers the single engine-owned reference;
                // the callee destroys its copy (normal return or unwind).
                fn(gpm, *stream);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehSaveMicrocodeCache(
            FnOgreSaveMicrocodeCache fn, const void* gpm, const OgreDataStreamPtrPod* stream)
        {
            __try
            {
                fn(gpm, *stream);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // ----------------------------------------------------------------

        static bool EnableSaveFlag()
        {
            uint32_t offset = kSaveFlagFallbackOffset;
            const auto* getterBytes =
                reinterpret_cast<const uint8_t*>(g_FnGetSaveMicrocodesToCache);
            uint32_t parsed = 0;
            if (SehParseSaveFlagOffset(getterBytes, &parsed) &&
                parsed < kSaveFlagMaxReasonableOffset)
            {
                offset = parsed;
            }
            else
            {
                LogShimA(LogLevel::Warn, "shadercache",
                    "save-flag getter pattern parse failed; using fallback offset 0x%X",
                    kSaveFlagFallbackOffset);
            }

            if (!SehWriteByte(static_cast<uint8_t*>(g_Gpm) + offset, 1))
                return false;

            uint8_t verify = 0;
            if (!SehCallBoolGetter(g_FnGetSaveMicrocodesToCache, g_Gpm, &verify) || !verify)
            {
                // Undo a write that the getter does not observe: wrong offset.
                SehWriteByte(static_cast<uint8_t*>(g_Gpm) + offset, 0);
                LogShimA(LogLevel::Warn, "shadercache",
                    "save-flag verification failed at gpm+0x%X; cache disabled", offset);
                return false;
            }

            LogShimA(LogLevel::Info, "shadercache",
                "microcode save-to-cache enabled (gpm=0x%p flag=+0x%X)", g_Gpm, offset);
            return true;
        }

        static void TryLoadCacheFile()
        {
            const std::filesystem::path cachePath = GetCacheFilePath();
            std::error_code ec;

            g_ShaderFingerprint = ComputeShaderSourceFingerprint();
            uint64_t stored = 0;
            const bool haveStored = ReadStoredFingerprint(stored);
            if (!std::filesystem::is_regular_file(cachePath, ec))
            {
                LogShimA(LogLevel::Info, "shadercache",
                    "no cache file yet (fingerprint=%016llx); first compiles will seed it",
                    static_cast<unsigned long long>(g_ShaderFingerprint));
                return;
            }
            if (!haveStored || stored != g_ShaderFingerprint)
            {
                std::filesystem::remove(cachePath, ec);
                std::filesystem::remove(GetFingerprintFilePath(), ec);
                LogShimA(LogLevel::Info, "shadercache",
                    "shader sources changed (stored=%016llx current=%016llx); dropped stale cache",
                    static_cast<unsigned long long>(stored),
                    static_cast<unsigned long long>(g_ShaderFingerprint));
                return;
            }
            const uintmax_t cacheSize = std::filesystem::file_size(cachePath, ec);
            if (ec || cacheSize == 0 || cacheSize > kMaxReasonableCacheBytes)
            {
                std::filesystem::remove(cachePath, ec);
                LogShimA(LogLevel::Warn, "shadercache",
                    "cache file size unreasonable (%llu bytes); dropped",
                    static_cast<unsigned long long>(cacheSize));
                return;
            }

            const std::string fileName = cachePath.string();
            const std::string group = "General";
            const std::string pattern;
            OgreDataStreamPtrPod stream = {};
            if (!SehOpenFileStream(g_FnOpenFileStream, g_Root, &stream,
                    &fileName, &group, &pattern))
            {
                LogShimA(LogLevel::Warn, "shadercache",
                    "failed opening cache stream path=%s", fileName.c_str());
                return;
            }
            if (!SehLoadMicrocodeCache(g_FnLoadMicrocodeCache, g_Gpm, &stream))
            {
                std::filesystem::remove(cachePath, ec);
                std::filesystem::remove(GetFingerprintFilePath(), ec);
                LogShimA(LogLevel::Warn, "shadercache",
                    "loadMicrocodeCache failed; dropped cache file path=%s", fileName.c_str());
                return;
            }
            LogShimA(LogLevel::Info, "shadercache",
                "loaded microcode cache bytes=%llu fingerprint=%016llx path=%s",
                static_cast<unsigned long long>(cacheSize),
                static_cast<unsigned long long>(g_ShaderFingerprint),
                fileName.c_str());
        }

        // Caller holds g_Mutex.
        static void TryInitLocked()
        {
            if (g_InitDone.load(std::memory_order_relaxed) || g_Disabled)
                return;

            if (EnvFlagSet("OPENSHIM_DISABLE_SHADER_CACHE") ||
                EnvFlagSet("BZR_DISABLE_SHADER_CACHE"))
            {
                g_Disabled = true;
                if (!g_DisabledLogged)
                {
                    g_DisabledLogged = true;
                    LogShimA(LogLevel::Info, "shadercache",
                        "disabled by environment kill switch");
                }
                return;
            }

            const auto gpmSingleton = ResolveOgreMainProc<FnOgreSingletonPtr>(
                "?getSingletonPtr@GpuProgramManager@Ogre@@SAPAV12@XZ");
            const auto rootSingleton = ResolveOgreMainProc<FnOgreSingletonPtr>(
                "?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            g_FnGetSaveMicrocodesToCache = ResolveOgreMainProc<FnOgreBoolThis>(
                "?getSaveMicrocodesToCache@GpuProgramManager@Ogre@@QAE_NXZ");
            g_FnIsCacheDirty = ResolveOgreMainProc<FnOgreBoolThis>(
                "?isCacheDirty@GpuProgramManager@Ogre@@QBE_NXZ");
            g_FnLoadMicrocodeCache = ResolveOgreMainProc<FnOgreLoadMicrocodeCache>(
                "?loadMicrocodeCache@GpuProgramManager@Ogre@@UAEXV?$SharedPtr@VDataStream@Ogre@@@2@@Z");
            g_FnSaveMicrocodeCache = ResolveOgreMainProc<FnOgreSaveMicrocodeCache>(
                "?saveMicrocodeCache@GpuProgramManager@Ogre@@UBEXV?$SharedPtr@VDataStream@Ogre@@@2@@Z");
            g_FnOpenFileStream = ResolveOgreMainProc<FnRootOpenFileStream>(
                "?openFileStream@Root@Ogre@@QAE?AV?$SharedPtr@VDataStream@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");
            g_FnCreateFileStream = ResolveOgreMainProc<FnRootCreateFileStream>(
                "?createFileStream@Root@Ogre@@QAE?AV?$SharedPtr@VDataStream@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N0@Z");

            if (!gpmSingleton || !rootSingleton || !g_FnGetSaveMicrocodesToCache ||
                !g_FnIsCacheDirty || !g_FnLoadMicrocodeCache || !g_FnSaveMicrocodeCache ||
                !g_FnOpenFileStream || !g_FnCreateFileStream)
            {
                g_Disabled = true;
                LogShimA(LogLevel::Warn, "shadercache",
                    "OgreMain cache exports unavailable; cache disabled");
                return;
            }

            g_Gpm = gpmSingleton();
            g_Root = rootSingleton();
            if (!g_Gpm || !g_Root)
                return; // singletons not constructed yet; retry on next trigger

            std::error_code ec;
            std::filesystem::create_directories(GetCacheFilePath().parent_path(), ec);

            g_SaveFlagEnabled = EnableSaveFlag();
            if (!g_SaveFlagEnabled)
            {
                g_Disabled = true;
                return;
            }

            TryLoadCacheFile();
            g_InitDone.store(true, std::memory_order_release);
        }

        // Caller holds g_Mutex.
        static void TrySaveLocked()
        {
            if (!g_InitDone.load(std::memory_order_relaxed) || !g_SaveFlagEnabled)
                return;

            const ULONGLONG now = GetTickCount64();
            if (g_LastSaveAttemptTick != 0 &&
                now - g_LastSaveAttemptTick < kSaveThrottleMs)
            {
                return;
            }

            uint8_t dirty = 0;
            if (!SehCallBoolGetter(g_FnIsCacheDirty, g_Gpm, &dirty) || !dirty)
                return;
            g_LastSaveAttemptTick = now;

            const std::filesystem::path cachePath = GetCacheFilePath();
            const std::string fileName = cachePath.string();
            const std::string group = "General";
            const std::string pattern;
            OgreDataStreamPtrPod stream = {};
            if (!SehCreateFileStream(g_FnCreateFileStream, g_Root, &stream,
                    &fileName, &group, &pattern))
            {
                LogShimA(LogLevel::Warn, "shadercache",
                    "failed creating cache stream path=%s", fileName.c_str());
                return;
            }
            if (!SehSaveMicrocodeCache(g_FnSaveMicrocodeCache, g_Gpm, &stream))
            {
                LogShimA(LogLevel::Warn, "shadercache",
                    "saveMicrocodeCache failed path=%s", fileName.c_str());
                return;
            }
            WriteStoredFingerprint(g_ShaderFingerprint);

            std::error_code ec;
            const uintmax_t cacheSize = std::filesystem::file_size(cachePath, ec);
            LogShimA(LogLevel::Info, "shadercache",
                "saved microcode cache bytes=%llu path=%s",
                static_cast<unsigned long long>(cacheSize),
                fileName.c_str());
        }
    }

    void OgreShaderCacheOnProgramScriptOpen()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (g_Disabled)
            return;
        if (!g_InitDone.load(std::memory_order_relaxed))
        {
            TryInitLocked();
            return;
        }
        // Covers shell-only sessions where the sim tick never runs: the
        // leave-game group reinit reopens *.program files, which lands here
        // and flushes any microcode compiled since the last save.
        TrySaveLocked();
    }

    void OgreShaderCacheTick()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (g_Disabled)
            return;
        if (!g_InitDone.load(std::memory_order_relaxed))
        {
            TryInitLocked();
            return;
        }
        TrySaveLocked();
    }
}
