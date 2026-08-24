// file_io_hooks.cpp
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "file_io_hooks.h"
#include "patcher.h"
#include "shim_log.h"
#include "ogre_shader_cache.h"
#include "trn_codec.h"

#include <Windows.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    using PFN_CreateFileA = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    using PFN_CreateFileW = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    using PFN_CloseHandle = BOOL(WINAPI*)(HANDLE);
    using PFN_MoveFileExA = BOOL(WINAPI*)(LPCSTR, LPCSTR, DWORD);
    using PFN_MoveFileExW = BOOL(WINAPI*)(LPCWSTR, LPCWSTR, DWORD);

    static PFN_CreateFileA g_RealCreateFileA = nullptr;
    static PFN_CreateFileW g_RealCreateFileW = nullptr;
    static PFN_CloseHandle g_RealCloseHandle = nullptr;
    static PFN_MoveFileExA g_RealMoveFileExA = nullptr;
    static PFN_MoveFileExW g_RealMoveFileExW = nullptr;

    namespace
    {
        struct TrnWriteRecord
        {
            std::wstring path;
        };

        static std::mutex g_TrnWriteMutex;
        static std::unordered_map<uintptr_t, TrnWriteRecord> g_TrnWriteHandles;
        static thread_local bool g_InTrnNormalization = false;
        static std::wstring ToLowerWide(std::wstring value);

        // Cheap case-insensitive ".program" suffix test used to trigger the
        // Ogre microcode cache before the resource-group parser compiles the
        // mod's GPU programs. Kept tiny because it runs on every file open.
        static bool PathEndsWithProgramW(const wchar_t* path)
        {
            if (!path)
                return false;
            size_t len = 0;
            while (path[len])
                ++len;
            static const wchar_t kSuffix[] = L".program";
            constexpr size_t kSuffixLen = 8; // wcslen(".program")
            if (len < kSuffixLen)
                return false;
            const wchar_t* tail = path + (len - kSuffixLen);
            for (size_t i = 0; i < kSuffixLen; ++i)
            {
                if (::towlower(tail[i]) != kSuffix[i])
                    return false;
            }
            return true;
        }

        static bool PathEndsWithProgramA(const char* path)
        {
            if (!path)
                return false;
            size_t len = 0;
            while (path[len])
                ++len;
            static const char kSuffix[] = ".program";
            constexpr size_t kSuffixLen = 8;
            if (len < kSuffixLen)
                return false;
            const char* tail = path + (len - kSuffixLen);
            for (size_t i = 0; i < kSuffixLen; ++i)
            {
                if (static_cast<char>(::tolower(static_cast<unsigned char>(tail[i]))) != kSuffix[i])
                    return false;
            }
            return true;
        }

        static char g_BzLoggerPath[] = "logs\\BZLogger.txt";
        static char g_BzOgreLogPath[] = "logs\\BZOgreLogfile.log";
        static char g_Crc32HostLogPath[] = "logs\\crc32host.log";
        static char g_Crc32MissionLogPath[] = "logs\\crc32mission.log";

        static bool PatchPushStringOperand(uintptr_t instructionAddress,
                                           uintptr_t expectedStringAddress,
                                           const char* replacement)
        {
            if (!replacement)
                return false;

            __try
            {
                auto* instruction = reinterpret_cast<uint8_t*>(instructionAddress);
                auto* operand = reinterpret_cast<uint32_t*>(instruction + 1);
                if (*instruction != 0x68 || *operand != expectedStringAddress)
                    return false;

                DWORD oldProtect = 0;
                if (!VirtualProtect(operand, sizeof(*operand), PAGE_EXECUTE_READWRITE, &oldProtect))
                    return false;
                *operand = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(replacement));
                FlushInstructionCache(GetCurrentProcess(), operand, sizeof(*operand));
                DWORD ignored = 0;
                VirtualProtect(operand, sizeof(*operand), oldProtect, &ignored);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool ShouldRouteGameLog(const std::filesystem::path& path)
        {
            if (path.empty() || path.has_parent_path())
                return false;

            const std::wstring fileName = ToLowerWide(path.filename().wstring());
            const std::wstring extension = ToLowerWide(path.extension().wstring());
            return extension == L".log" || fileName == L"bzlogger.txt";
        }

        static std::string RouteGameLogPath(LPCSTR fileName)
        {
            if (!fileName || !*fileName || !ShouldRouteGameLog(std::filesystem::path(fileName)))
                return fileName ? fileName : "";
            return GetGameLogPath(fileName);
        }

        static std::wstring RouteGameLogPath(LPCWSTR fileName)
        {
            if (!fileName || !*fileName || !ShouldRouteGameLog(std::filesystem::path(fileName)))
                return fileName ? fileName : L"";

            const std::wstring leaf = std::filesystem::path(fileName).filename().wstring();
            const int byteCount = WideCharToMultiByte(
                CP_UTF8, 0, leaf.c_str(), -1, nullptr, 0, nullptr, nullptr);
            if (byteCount <= 1)
                return fileName;

            std::string utf8(static_cast<size_t>(byteCount), '\0');
            WideCharToMultiByte(
                CP_UTF8, 0, leaf.c_str(), -1, utf8.data(), byteCount, nullptr, nullptr);
            utf8.pop_back();
            const std::string routed = GetGameLogPath(utf8.c_str());

            const int wideCount = MultiByteToWideChar(
                CP_UTF8, 0, routed.c_str(), -1, nullptr, 0);
            if (wideCount <= 1)
                return fileName;

            std::wstring wide(static_cast<size_t>(wideCount), L'\0');
            MultiByteToWideChar(CP_UTF8, 0, routed.c_str(), -1, wide.data(), wideCount);
            wide.pop_back();
            return wide;
        }

        class ScopedNormalizationGuard
        {
        public:
            ScopedNormalizationGuard()
                : m_Previous(g_InTrnNormalization)
            {
                g_InTrnNormalization = true;
            }

            ~ScopedNormalizationGuard()
            {
                g_InTrnNormalization = m_Previous;
            }

        private:
            bool m_Previous;
        };

        static bool PatchIATByFuncName(HMODULE targetModule, const char* funcName, void* newFunc, void** oldFunc)
        {
            if (!targetModule || !funcName || !*funcName || !newFunc)
                return false;

            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(targetModule);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;

            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
                reinterpret_cast<uint8_t*>(targetModule) + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            const DWORD importRva =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
            if (!importRva)
                return false;

            auto* importDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
                reinterpret_cast<uint8_t*>(targetModule) + importRva);
            while (importDesc->Name)
            {
                auto* origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                    reinterpret_cast<uint8_t*>(targetModule) +
                    (importDesc->OriginalFirstThunk ? importDesc->OriginalFirstThunk : importDesc->FirstThunk));
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                    reinterpret_cast<uint8_t*>(targetModule) + importDesc->FirstThunk);

                while (origThunk->u1.AddressOfData)
                {
                    if (!IMAGE_SNAP_BY_ORDINAL(origThunk->u1.Ordinal))
                    {
                        auto* importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                            reinterpret_cast<uint8_t*>(targetModule) + origThunk->u1.AddressOfData);
                        if (std::strcmp(reinterpret_cast<const char*>(importByName->Name), funcName) == 0)
                        {
                            auto** iatEntry = reinterpret_cast<void**>(&thunk->u1.Function);
                            DWORD oldProtect = 0;
                            if (!VirtualProtect(iatEntry, sizeof(void*), PAGE_READWRITE, &oldProtect))
                                return false;

                            if (oldFunc && *oldFunc == nullptr)
                                *oldFunc = *iatEntry;
                            *iatEntry = newFunc;
                            VirtualProtect(iatEntry, sizeof(void*), oldProtect, &oldProtect);
                            return true;
                        }
                    }

                    ++origThunk;
                    ++thunk;
                }

                ++importDesc;
            }

            return false;
        }

        static std::wstring ToLowerWide(std::wstring value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](wchar_t ch)
            {
                return static_cast<wchar_t>(::towlower(ch));
            });
            return value;
        }

        static std::wstring ResolveAbsolutePath(const wchar_t* path)
        {
            if (!path || !*path)
                return {};

            std::vector<wchar_t> buffer(MAX_PATH, L'\0');
            DWORD written = GetFullPathNameW(path, static_cast<DWORD>(buffer.size()), buffer.data(), nullptr);
            if (written == 0)
                return path;

            if (written >= buffer.size())
            {
                buffer.resize(static_cast<size_t>(written) + 1, L'\0');
                written = GetFullPathNameW(path, static_cast<DWORD>(buffer.size()), buffer.data(), nullptr);
                if (written == 0 || written >= buffer.size())
                    return path;
            }

            return std::wstring(buffer.data(), buffer.data() + written);
        }

        static std::wstring ResolveAbsolutePathFromAnsi(const char* path)
        {
            if (!path || !*path)
                return {};

            const int wideChars = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
            if (wideChars <= 1)
                return {};

            std::vector<wchar_t> wide(static_cast<size_t>(wideChars), L'\0');
            MultiByteToWideChar(CP_ACP, 0, path, -1, wide.data(), wideChars);
            return ResolveAbsolutePath(wide.data());
        }

        static bool IsTrnPath(const std::wstring& path)
        {
            if (path.empty())
                return false;

            const std::wstring extension =
                ToLowerWide(std::filesystem::path(path).extension().wstring());
            return extension == L".trn";
        }

        static bool ShouldTrackTrnWrite(DWORD desiredAccess, DWORD creationDisposition)
        {
            constexpr DWORD kWriteMask =
                GENERIC_WRITE | GENERIC_ALL | FILE_WRITE_DATA | FILE_APPEND_DATA | DELETE;

            if ((desiredAccess & kWriteMask) != 0)
                return true;

            switch (creationDisposition)
            {
            case CREATE_ALWAYS:
            case CREATE_NEW:
            case OPEN_ALWAYS:
            case TRUNCATE_EXISTING:
                return true;
            default:
                return false;
            }
        }

        static void TrackTrnWriteHandle(HANDLE handle, const std::wstring& path)
        {
            if (!handle || handle == INVALID_HANDLE_VALUE || path.empty())
                return;

            std::lock_guard<std::mutex> lock(g_TrnWriteMutex);
            // Growth cap. Entries are removed only by a hooked CloseHandle in
            // a patched module; a close from any other module (or NtClose)
            // leaks the entry. Windows reuses HANDLE values aggressively, so
            // an unbounded leak eventually turns into a stale record for an
            // unrelated file. Eviction is arbitrary because every entry over
            // the cap is, by construction, already orphaned.
            constexpr size_t kMaxTrackedTrnHandles = 4096;
            if (g_TrnWriteHandles.size() >= kMaxTrackedTrnHandles &&
                g_TrnWriteHandles.find(reinterpret_cast<uintptr_t>(handle)) ==
                    g_TrnWriteHandles.end())
            {
                g_TrnWriteHandles.erase(g_TrnWriteHandles.begin());
            }
            g_TrnWriteHandles[reinterpret_cast<uintptr_t>(handle)] = { path };
        }

        // A tracked record must only drive normalization while the closing
        // HANDLE still refers to the file that was recorded. Handles leaked
        // past the hooked modules stay in the map and Windows hands their
        // numeric values back out, so identity has to be re-verified against
        // the still-open handle at close time.
        static bool TrackedHandleMatchesRecord(HANDLE handle, const TrnWriteRecord& record)
        {
            if (record.path.empty())
                return false;

            wchar_t buffer[1024] = {};
            const DWORD written = GetFinalPathNameByHandleW(
                handle, buffer, static_cast<DWORD>(std::size(buffer)),
                FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
            if (written == 0 || written >= std::size(buffer))
                return false;

            // GetFinalPathNameByHandleW returns \\?\C:\... for DOS paths; the
            // recorded path came from GetFullPathNameW without the prefix.
            std::wstring actual = buffer;
            const wchar_t kNtDosPrefix[] = L"\\\\?\\";
            if (_wcsnicmp(actual.c_str(), kNtDosPrefix, 4) == 0)
                actual.erase(0, 4);

            return _wcsicmp(actual.c_str(), record.path.c_str()) == 0;
        }

        static bool PopTrackedTrnWriteHandle(HANDLE handle, TrnWriteRecord& outRecord)
        {
            if (!handle || handle == INVALID_HANDLE_VALUE)
                return false;

            std::lock_guard<std::mutex> lock(g_TrnWriteMutex);
            const auto it = g_TrnWriteHandles.find(reinterpret_cast<uintptr_t>(handle));
            if (it == g_TrnWriteHandles.end())
                return false;

            outRecord = it->second;
            g_TrnWriteHandles.erase(it);
            return true;
        }

        static bool ReadBinaryFile(const std::wstring& path, std::vector<uint8_t>& outBytes)
        {
            std::ifstream input(std::filesystem::path(path), std::ios::binary);
            if (!input.is_open())
                return false;

            input.seekg(0, std::ios::end);
            const std::streamoff size = input.tellg();
            input.seekg(0, std::ios::beg);
            if (size < 0)
                return false;

            outBytes.resize(static_cast<size_t>(size));
            if (!outBytes.empty())
                input.read(reinterpret_cast<char*>(outBytes.data()), size);

            return input.good() || input.eof();
        }

        static bool WriteBinaryFileAtomic(const std::wstring& path, const std::vector<uint8_t>& bytes)
        {
            const std::filesystem::path targetPath(path);
            const std::filesystem::path tempPath = targetPath.wstring() + L".openshim_tmp";

            {
                std::ofstream output(tempPath, std::ios::binary | std::ios::trunc);
                if (!output.is_open())
                    return false;

                if (!bytes.empty())
                    output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));

                if (!output.good())
                    return false;
            }

            SetFileAttributesW(path.c_str(), FILE_ATTRIBUTE_NORMAL);
            if (!MoveFileExW(tempPath.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED))
            {
                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                return false;
            }

            return true;
        }

        static void NormalizeTrnFileIfNeeded(const std::wstring& path, const wchar_t* reason)
        {
            if (path.empty() || g_InTrnNormalization)
                return;

            ScopedNormalizationGuard guard;

            std::vector<uint8_t> originalBytes;
            if (!ReadBinaryFile(path, originalBytes))
            {
                Log(L"[TRN] Failed to read tracked file path=%ls reason=%ls\n",
                    path.c_str(),
                    reason ? reason : L"<unknown>");
                return;
            }

            const TrnCanonicalResult result = CanonicalizeTrnBytes(originalBytes);
            if (result.status != TrnCodecStatus::Ok)
            {
                Log(L"[TRN] Safety normalizer left file unchanged path=%ls reason=%ls status=%hs\n",
                    path.c_str(), reason ? reason : L"<unknown>",
                    TrnCodecStatusName(result.status));
                return;
            }
            if (!result.changed)
                return;

            if (!WriteBinaryFileAtomic(path, result.serializedCrLf))
            {
                Log(L"[TRN] Failed to rewrite normalized file path=%ls reason=%ls\n",
                    path.c_str(),
                    reason ? reason : L"<unknown>");
                return;
            }

            Log(L"[TRN] Safety-normalized file path=%ls reason=%ls encoding=%hs bytes=%u->%u\n",
                path.c_str(),
                reason ? reason : L"<unknown>",
                TrnSourceEncodingName(result.sourceEncoding),
                static_cast<unsigned>(originalBytes.size()),
                static_cast<unsigned>(result.serializedCrLf.size()));
        }

        static void MaybeTrackOpenedTrnHandle(HANDLE handle, const std::wstring& path, DWORD desiredAccess, DWORD creationDisposition)
        {
            if (g_InTrnNormalization)
                return;

            if (!ShouldTrackTrnWrite(desiredAccess, creationDisposition))
                return;

            const std::wstring absolutePath = ResolveAbsolutePath(path.c_str());
            if (!IsTrnPath(absolutePath))
                return;

            TrackTrnWriteHandle(handle, absolutePath);
            Log(L"[TRN] Tracking write handle=0x%p path=%ls disposition=%u access=0x%08X\n",
                handle,
                absolutePath.c_str(),
                static_cast<unsigned>(creationDisposition),
                static_cast<unsigned>(desiredAccess));
        }

        static HANDLE WINAPI Hooked_CreateFileW(
            LPCWSTR fileName,
            DWORD desiredAccess,
            DWORD shareMode,
            LPSECURITY_ATTRIBUTES securityAttributes,
            DWORD creationDisposition,
            DWORD flagsAndAttributes,
            HANDLE templateFile)
        {
            if (!g_RealCreateFileW)
                return INVALID_HANDLE_VALUE;

            const std::wstring routedPath = RouteGameLogPath(fileName);
            const HANDLE handle = g_RealCreateFileW(
                routedPath.c_str(),
                desiredAccess,
                shareMode,
                securityAttributes,
                creationDisposition,
                flagsAndAttributes,
                templateFile);

            if (!g_InTrnNormalization && handle != INVALID_HANDLE_VALUE)
                MaybeTrackOpenedTrnHandle(handle, fileName ? fileName : L"", desiredAccess, creationDisposition);

            // Ogre parses the mod's *.program scripts (and then compiles the
            // enhanced-lighting shaders) right after this open succeeds. Prime
            // the microcode cache on this exact thread so a prior session's
            // compiled shaders are available before compilation begins.
            if (handle != INVALID_HANDLE_VALUE && PathEndsWithProgramW(fileName))
                OgreShaderCacheOnProgramScriptOpen();

            return handle;
        }

        static HANDLE WINAPI Hooked_CreateFileA(
            LPCSTR fileName,
            DWORD desiredAccess,
            DWORD shareMode,
            LPSECURITY_ATTRIBUTES securityAttributes,
            DWORD creationDisposition,
            DWORD flagsAndAttributes,
            HANDLE templateFile)
        {
            if (!g_RealCreateFileA)
                return INVALID_HANDLE_VALUE;

            const std::string routedPath = RouteGameLogPath(fileName);
            const HANDLE handle = g_RealCreateFileA(
                routedPath.c_str(),
                desiredAccess,
                shareMode,
                securityAttributes,
                creationDisposition,
                flagsAndAttributes,
                templateFile);

            if (!g_InTrnNormalization && handle != INVALID_HANDLE_VALUE)
                MaybeTrackOpenedTrnHandle(handle, ResolveAbsolutePathFromAnsi(fileName), desiredAccess, creationDisposition);

            if (handle != INVALID_HANDLE_VALUE && PathEndsWithProgramA(fileName))
                OgreShaderCacheOnProgramScriptOpen();

            return handle;
        }

        static BOOL WINAPI Hooked_CloseHandle(HANDLE object)
        {
            if (!g_RealCloseHandle)
                return FALSE;

            TrnWriteRecord record = {};
            const bool tracked = !g_InTrnNormalization && PopTrackedTrnWriteHandle(object, record);
            // Identity check must run before the real close, while the handle
            // still resolves. A mismatch means the map held a stale numeric
            // handle value (leaked past a hooked closer and reused by
            // Windows); rewriting the recorded path then would corrupt an
            // unrelated file.
            const bool matches = tracked && TrackedHandleMatchesRecord(object, record);
            const BOOL result = g_RealCloseHandle(object);

            if (tracked && result && matches)
                NormalizeTrnFileIfNeeded(record.path, L"CloseHandle");
            else if (tracked)
            {
                Log(L"[TRN] Dropping stale tracked write handle=0x%p path=%ls closeOk=%d identity=%d\n",
                    object,
                    record.path.c_str(),
                    static_cast<int>(result),
                    static_cast<int>(matches));
            }

            return result;
        }

        static void MaybeNormalizeMovedDestination(const std::wstring& destination, const wchar_t* reason)
        {
            if (g_InTrnNormalization)
                return;

            const std::wstring absoluteDestination = ResolveAbsolutePath(destination.c_str());
            if (IsTrnPath(absoluteDestination))
                NormalizeTrnFileIfNeeded(absoluteDestination, reason);
        }

        static BOOL WINAPI Hooked_MoveFileExW(LPCWSTR existingFileName, LPCWSTR newFileName, DWORD flags)
        {
            if (!g_RealMoveFileExW)
                return FALSE;

            const BOOL result = g_RealMoveFileExW(existingFileName, newFileName, flags);
            if (result && newFileName && *newFileName)
                MaybeNormalizeMovedDestination(newFileName, L"MoveFileExW");
            return result;
        }

        static BOOL WINAPI Hooked_MoveFileExA(LPCSTR existingFileName, LPCSTR newFileName, DWORD flags)
        {
            if (!g_RealMoveFileExA)
                return FALSE;

            const BOOL result = g_RealMoveFileExA(existingFileName, newFileName, flags);
            if (result && newFileName && *newFileName)
                MaybeNormalizeMovedDestination(ResolveAbsolutePathFromAnsi(newFileName), L"MoveFileExA");
            return result;
        }

        static int PatchTrackedFunctionsForModule(HMODULE module, const wchar_t* label)
        {
            if (!module)
                return 0;

            int patched = 0;
            patched += PatchIATByFuncName(module, "CreateFileW", reinterpret_cast<void*>(Hooked_CreateFileW), reinterpret_cast<void**>(&g_RealCreateFileW)) ? 1 : 0;
            patched += PatchIATByFuncName(module, "CreateFileA", reinterpret_cast<void*>(Hooked_CreateFileA), reinterpret_cast<void**>(&g_RealCreateFileA)) ? 1 : 0;
            patched += PatchIATByFuncName(module, "CloseHandle", reinterpret_cast<void*>(Hooked_CloseHandle), reinterpret_cast<void**>(&g_RealCloseHandle)) ? 1 : 0;
            patched += PatchIATByFuncName(module, "MoveFileExW", reinterpret_cast<void*>(Hooked_MoveFileExW), reinterpret_cast<void**>(&g_RealMoveFileExW)) ? 1 : 0;
            patched += PatchIATByFuncName(module, "MoveFileExA", reinterpret_cast<void*>(Hooked_MoveFileExA), reinterpret_cast<void**>(&g_RealMoveFileExA)) ? 1 : 0;

            Log(L"[TRN] Module %ls file hook results: patched=%d base=0x%p\n",
                label ? label : L"<unknown>",
                patched,
                module);
            return patched;
        }
    }

    void ApplyEarlyGameLogHooks()
    {
        HMODULE mainModule = GetModuleHandleW(nullptr);
        if (!mainModule)
            return;

        PatchIATByFuncName(
            mainModule,
            "CreateFileW",
            reinterpret_cast<void*>(Hooked_CreateFileW),
            reinterpret_cast<void**>(&g_RealCreateFileW));
        PatchIATByFuncName(
            mainModule,
            "CreateFileA",
            reinterpret_cast<void*>(Hooked_CreateFileA),
            reinterpret_cast<void**>(&g_RealCreateFileA));

        // These logger paths are passed as immediate string pointers inside
        // the executable and bypass the Win32 imports above through the
        // statically linked runtime. Redirect the operands before the entry
        // point runs. GOG and Steam currently share these settled bytes.
        PatchPushStringOperand(0x00663FF6u, 0x00892050u, g_BzOgreLogPath);
        PatchPushStringOperand(0x0081E864u, 0x008A1EE0u, g_BzLoggerPath);
        PatchPushStringOperand(0x00743E55u, 0x0089A794u, g_Crc32HostLogPath);
        PatchPushStringOperand(0x0079631Fu, 0x0089A794u, g_Crc32HostLogPath);
        PatchPushStringOperand(0x00743109u, 0x0089A760u, g_Crc32MissionLogPath);
    }

    void ApplyTrnSaveNormalizeHooks()
    {
        Log(L"=========== TRN SAVE NORMALIZATION HOOKS ===========\n");

        HMODULE mainModule = GetModuleHandleW(nullptr);
        if (!mainModule)
        {
            Log(L"[TRN] GetModuleHandleW(nullptr) failed; file hooks not installed\n");
            return;
        }

        int patched = PatchTrackedFunctionsForModule(mainModule, L"battlezone98redux.exe");

        const wchar_t* modulesToWatch[] =
        {
            L"msvcr120.dll",
            L"ucrtbase.dll"
        };

        for (const wchar_t* moduleName : modulesToWatch)
        {
            HMODULE module = nullptr;
            for (int attempt = 0; attempt < 200; ++attempt)
            {
                module = GetModuleHandleW(moduleName);
                if (module)
                    break;
                Sleep(25);
            }

            if (module)
            {
                patched += PatchTrackedFunctionsForModule(module, moduleName);
            }
            else
            {
                Log(L"[TRN] Module %ls was not loaded during hook watch window\n", moduleName);
            }
        }

        Log(L"[TRN] Automatic save normalization %hs\n", patched > 0 ? "enabled" : "not installed");
    }
}
