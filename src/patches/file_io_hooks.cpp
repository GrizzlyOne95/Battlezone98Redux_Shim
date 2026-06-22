// file_io_hooks.cpp
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "file_io_hooks.h"
#include "patcher.h"

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
            g_TrnWriteHandles[reinterpret_cast<uintptr_t>(handle)] = { path };
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

        static bool ConvertWideToAnsiBytes(const wchar_t* wide, int wideLenChars, std::vector<uint8_t>& outBytes)
        {
            const int bytesNeeded = WideCharToMultiByte(CP_ACP, 0, wide, wideLenChars, nullptr, 0, nullptr, nullptr);
            if (bytesNeeded < 0)
                return false;

            outBytes.resize(static_cast<size_t>(bytesNeeded));
            return WideCharToMultiByte(
                CP_ACP,
                0,
                wide,
                wideLenChars,
                reinterpret_cast<char*>(outBytes.data()),
                bytesNeeded,
                nullptr,
                nullptr) == bytesNeeded;
        }

        static bool ConvertUtfBomToAnsiBytes(const std::vector<uint8_t>& input, std::vector<uint8_t>& outBytes)
        {
            if (input.size() >= 3 &&
                input[0] == 0xEF &&
                input[1] == 0xBB &&
                input[2] == 0xBF)
            {
                const char* utf8 = reinterpret_cast<const char*>(input.data() + 3);
                const int utf8Len = static_cast<int>(input.size() - 3);
                const int wideChars = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8Len, nullptr, 0);
                if (wideChars <= 0)
                    return false;

                std::vector<wchar_t> wide(static_cast<size_t>(wideChars), L'\0');
                if (MultiByteToWideChar(CP_UTF8, 0, utf8, utf8Len, wide.data(), wideChars) != wideChars)
                    return false;

                return ConvertWideToAnsiBytes(wide.data(), wideChars, outBytes);
            }

            if (input.size() >= 2 &&
                input[0] == 0xFF &&
                input[1] == 0xFE)
            {
                const size_t rawBytes = input.size() - 2;
                const size_t wideChars = rawBytes / sizeof(wchar_t);
                if (wideChars == 0)
                {
                    outBytes.clear();
                    return true;
                }

                return ConvertWideToAnsiBytes(
                    reinterpret_cast<const wchar_t*>(input.data() + 2),
                    static_cast<int>(wideChars),
                    outBytes);
            }

            if (input.size() >= 2 &&
                input[0] == 0xFE &&
                input[1] == 0xFF)
            {
                const size_t rawBytes = input.size() - 2;
                const size_t codeUnits = rawBytes / 2;
                if (codeUnits == 0)
                {
                    outBytes.clear();
                    return true;
                }

                std::vector<wchar_t> wide(codeUnits, L'\0');
                for (size_t i = 0; i < codeUnits; ++i)
                {
                    const uint16_t value =
                        (static_cast<uint16_t>(input[2 + (i * 2)]) << 8) |
                        static_cast<uint16_t>(input[3 + (i * 2)]);
                    wide[i] = static_cast<wchar_t>(value);
                }

                return ConvertWideToAnsiBytes(wide.data(), static_cast<int>(wide.size()), outBytes);
            }

            return false;
        }

        static bool NormalizeLineEndingsToCrLf(const std::vector<uint8_t>& input, std::vector<uint8_t>& output)
        {
            output.clear();
            output.reserve(input.size() + 32);

            bool changed = false;
            for (size_t i = 0; i < input.size(); ++i)
            {
                const uint8_t ch = input[i];
                if (ch == '\r')
                {
                    output.push_back('\r');
                    if (i + 1 < input.size() && input[i + 1] == '\n')
                    {
                        output.push_back('\n');
                        ++i;
                    }
                    else
                    {
                        output.push_back('\n');
                        changed = true;
                    }
                }
                else if (ch == '\n')
                {
                    output.push_back('\r');
                    output.push_back('\n');
                    changed = true;
                }
                else
                {
                    output.push_back(ch);
                }
            }

            if (!changed &&
                (output.size() != input.size() ||
                 std::memcmp(output.data(), input.data(), input.size()) != 0))
            {
                changed = true;
            }

            return changed;
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

            std::vector<uint8_t> workingBytes;
            const bool convertedEncoding = ConvertUtfBomToAnsiBytes(originalBytes, workingBytes);
            if (!convertedEncoding)
                workingBytes = originalBytes;

            std::vector<uint8_t> normalizedBytes;
            const bool changedNewlines = NormalizeLineEndingsToCrLf(workingBytes, normalizedBytes);
            if (!changedNewlines && !convertedEncoding)
                return;

            if (!WriteBinaryFileAtomic(path, normalizedBytes))
            {
                Log(L"[TRN] Failed to rewrite normalized file path=%ls reason=%ls\n",
                    path.c_str(),
                    reason ? reason : L"<unknown>");
                return;
            }

            Log(L"[TRN] Normalized file path=%ls reason=%ls encodingFix=%hs bytes=%u->%u\n",
                path.c_str(),
                reason ? reason : L"<unknown>",
                convertedEncoding ? "yes" : "no",
                static_cast<unsigned>(originalBytes.size()),
                static_cast<unsigned>(normalizedBytes.size()));
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

            const HANDLE handle = g_RealCreateFileW(
                fileName,
                desiredAccess,
                shareMode,
                securityAttributes,
                creationDisposition,
                flagsAndAttributes,
                templateFile);

            if (!g_InTrnNormalization && handle != INVALID_HANDLE_VALUE)
                MaybeTrackOpenedTrnHandle(handle, fileName ? fileName : L"", desiredAccess, creationDisposition);

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

            const HANDLE handle = g_RealCreateFileA(
                fileName,
                desiredAccess,
                shareMode,
                securityAttributes,
                creationDisposition,
                flagsAndAttributes,
                templateFile);

            if (!g_InTrnNormalization && handle != INVALID_HANDLE_VALUE)
                MaybeTrackOpenedTrnHandle(handle, ResolveAbsolutePathFromAnsi(fileName), desiredAccess, creationDisposition);

            return handle;
        }

        static BOOL WINAPI Hooked_CloseHandle(HANDLE object)
        {
            if (!g_RealCloseHandle)
                return FALSE;

            TrnWriteRecord record = {};
            const bool tracked = !g_InTrnNormalization && PopTrackedTrnWriteHandle(object, record);
            const BOOL result = g_RealCloseHandle(object);

            if (tracked && result && !record.path.empty())
                NormalizeTrnFileIfNeeded(record.path, L"CloseHandle");

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
