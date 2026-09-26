// bootstrap_file_io.cpp
// BZR Open Shim - the permanent bootstrap file-I/O seam. See the header for
// why the hook is permanent and the policy is not.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "bootstrap_file_io.h"
#include "game_log_path.h"

#include <atomic>
#include <cstring>
#include <cwctype>
#include <filesystem>
#include <string>

namespace BZROpenShim::BootstrapFileIo
{
    using PFN_CreateFileA = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    using PFN_CreateFileW = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

    namespace
    {
        PFN_CreateFileA g_RealCreateFileA = nullptr;
        PFN_CreateFileW g_RealCreateFileW = nullptr;

        // Release/acquire so a thread that sees the pointer also sees the
        // fully written table behind it. Read once per call into a local:
        // reading the atomic twice could route a path through one provider
        // and report the open to another.
        std::atomic<const Provider*> g_Provider{nullptr};

        // Rewritten into the executable's push operands, so the storage has
        // to outlive every caller and stay writable-by-address. Non-const and
        // file-scope for exactly that reason.
        char g_BzLoggerPath[] = "logs\\BZLogger.txt";
        char g_BzOgreLogPath[] = "logs\\BZOgreLogfile.log";
        char g_Crc32HostLogPath[] = "logs\\crc32host.log";
        char g_Crc32MissionLogPath[] = "logs\\crc32mission.log";

        template <typename CharT>
        CharT LowerAscii(CharT ch)
        {
            return (ch >= CharT('A') && ch <= CharT('Z'))
                       ? static_cast<CharT>(ch + (CharT('a') - CharT('A')))
                       : ch;
        }

        // The stock-log test, run on every CreateFile the game makes. It
        // allocates nothing and cannot throw: a bare name (no directory
        // separator, no drive) whose extension is ".log", or BZLogger.txt,
        // case-insensitively. This is what std::filesystem::path answered
        // before, minus the four to six allocations and the exceptions a
        // path conversion or an exhausted heap could raise inside the
        // game's own call.
        template <typename CharT>
        bool IsBareGameLogNameImpl(const CharT* name)
        {
            if (name == nullptr || *name == 0)
                return false;
            size_t length = 0;
            size_t lastDot = SIZE_MAX;
            for (; name[length] != 0; ++length)
            {
                const CharT ch = name[length];
                if (ch == CharT('\\') || ch == CharT('/') || ch == CharT(':'))
                    return false;
                if (ch == CharT('.'))
                    lastDot = length;
            }
            constexpr char kLogger[] = "bzlogger.txt";
            constexpr size_t kLoggerLength = sizeof(kLogger) - 1;
            if (length == kLoggerLength)
            {
                bool same = true;
                for (size_t i = 0; i < length && same; ++i)
                    same = LowerAscii(name[i]) == static_cast<CharT>(kLogger[i]);
                if (same)
                    return true;
            }
            // As std::filesystem::path::extension() has it: a leading dot is
            // not an extension, so ".log" on its own is not a log.
            if (lastDot == SIZE_MAX || lastDot == 0 || length - lastDot != 4)
                return false;
            return LowerAscii(name[lastDot + 1]) == CharT('l') &&
                   LowerAscii(name[lastDot + 2]) == CharT('o') &&
                   LowerAscii(name[lastDot + 3]) == CharT('g');
        }

        // Only a stock log pays for the conversion and the directory probe.
        // A failure there (a conversion error, an exhausted heap) leaves the
        // caller's own name in force instead of leaving the game's CreateFile
        // through a C++ exception. `out` is written only on success.
        bool RouteGameLogPath(LPCSTR fileName, std::string& out)
        {
            if (!IsBareGameLogNameImpl(fileName))
                return false;
            try
            {
                out = GetGameLogPath(fileName);
                return !out.empty();
            }
            catch (...)
            {
                return false;
            }
        }

        bool RouteGameLogPath(LPCWSTR fileName, std::wstring& out)
        {
            if (!IsBareGameLogNameImpl(fileName))
                return false;
            try
            {
                const int byteCount = WideCharToMultiByte(
                    CP_UTF8, 0, fileName, -1, nullptr, 0, nullptr, nullptr);
                if (byteCount <= 1)
                    return false;

                std::string utf8(static_cast<size_t>(byteCount), '\0');
                WideCharToMultiByte(
                    CP_UTF8, 0, fileName, -1, utf8.data(), byteCount, nullptr, nullptr);
                utf8.pop_back();
                const std::string routed = GetGameLogPath(utf8.c_str());

                const int wideCount = MultiByteToWideChar(
                    CP_UTF8, 0, routed.c_str(), -1, nullptr, 0);
                if (wideCount <= 1)
                    return false;

                out.assign(static_cast<size_t>(wideCount), L'\0');
                MultiByteToWideChar(CP_UTF8, 0, routed.c_str(), -1, out.data(), wideCount);
                out.pop_back();
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        template <typename Fn>
        bool ProviderHas(const Provider* provider, Fn Provider::*member, size_t fieldEnd)
        {
            return provider && provider->structSize >= fieldEnd &&
                   (provider->*member) != nullptr;
        }

        // A provider promises not to throw. One that does anyway is treated
        // as having declined, the count is kept for the tests and for a
        // later diagnostic, and the game's CreateFile never sees the throw.
        std::atomic<uint32_t> g_ProviderExceptions{0};

        void NoteProviderException()
        {
            g_ProviderExceptions.fetch_add(1, std::memory_order_relaxed);
        }

        bool PatchPushStringOperand(uintptr_t instructionAddress,
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

        HANDLE WINAPI CreateFileWWrapper(
            LPCWSTR fileName,
            DWORD desiredAccess,
            DWORD shareMode,
            LPSECURITY_ATTRIBUTES securityAttributes,
            DWORD creationDisposition,
            DWORD flagsAndAttributes,
            HANDLE templateFile)
        {
            const PFN_CreateFileW real = g_RealCreateFileW;
            if (!real)
                return INVALID_HANDLE_VALUE;

            // Bootstrap-owned and unconditional: the stock logs have to reach
            // logs\ whether or not OpenShim ever loads. Nothing is allocated
            // unless the name is a stock log; every other open passes the
            // caller's own pointer straight through.
            const wchar_t* path = fileName ? fileName : L"";
            std::wstring logRouted;
            if (RouteGameLogPath(fileName, logRouted))
                path = logRouted.c_str();

            // One load. Everything below uses this same provider instance.
            const Provider* provider = g_Provider.load(std::memory_order_acquire);

            if (ProviderHas(provider, &Provider::routePathW,
                            offsetof(Provider, routePathW) + sizeof(provider->routePathW)))
            {
                try
                {
                    if (const wchar_t* routed =
                            provider->routePathW(path, desiredAccess, creationDisposition))
                        path = routed;
                }
                catch (...)
                {
                    NoteProviderException();
                }
            }

            const HANDLE handle = real(
                path, desiredAccess, shareMode, securityAttributes,
                creationDisposition, flagsAndAttributes, templateFile);
            const DWORD openError = GetLastError();

            if (handle != INVALID_HANDLE_VALUE &&
                ProviderHas(provider, &Provider::onOpenedW,
                            offsetof(Provider, onOpenedW) + sizeof(provider->onOpenedW)))
            {
                try
                {
                    provider->onOpenedW(handle, fileName ? fileName : L"", path,
                                        desiredAccess, creationDisposition);
                }
                catch (...)
                {
                    NoteProviderException();
                }
            }

            SetLastError(openError);
            return handle;
        }

        HANDLE WINAPI CreateFileAWrapper(
            LPCSTR fileName,
            DWORD desiredAccess,
            DWORD shareMode,
            LPSECURITY_ATTRIBUTES securityAttributes,
            DWORD creationDisposition,
            DWORD flagsAndAttributes,
            HANDLE templateFile)
        {
            const PFN_CreateFileA real = g_RealCreateFileA;
            if (!real)
                return INVALID_HANDLE_VALUE;

            const char* path = fileName ? fileName : "";
            std::string logRouted;
            if (RouteGameLogPath(fileName, logRouted))
                path = logRouted.c_str();

            const Provider* provider = g_Provider.load(std::memory_order_acquire);

            if (ProviderHas(provider, &Provider::routePathA,
                            offsetof(Provider, routePathA) + sizeof(provider->routePathA)))
            {
                try
                {
                    if (const char* routed =
                            provider->routePathA(path, desiredAccess, creationDisposition))
                        path = routed;
                }
                catch (...)
                {
                    NoteProviderException();
                }
            }

            const HANDLE handle = real(
                path, desiredAccess, shareMode, securityAttributes,
                creationDisposition, flagsAndAttributes, templateFile);
            const DWORD openError = GetLastError();

            if (handle != INVALID_HANDLE_VALUE &&
                ProviderHas(provider, &Provider::onOpenedA,
                            offsetof(Provider, onOpenedA) + sizeof(provider->onOpenedA)))
            {
                try
                {
                    provider->onOpenedA(handle, fileName ? fileName : "", path,
                                        desiredAccess, creationDisposition);
                }
                catch (...)
                {
                    NoteProviderException();
                }
            }

            SetLastError(openError);
            return handle;
        }
    }

    bool IsBareGameLogNameW(const wchar_t* fileName)
    {
        return IsBareGameLogNameImpl(fileName);
    }

    bool IsBareGameLogNameA(const char* fileName)
    {
        return IsBareGameLogNameImpl(fileName);
    }

    uint32_t ProviderExceptionCount()
    {
        return g_ProviderExceptions.load(std::memory_order_relaxed);
    }

    bool PatchIATByFuncName(HMODULE targetModule, const char* funcName, void* newFunc, void** oldFunc)
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

    bool InstallProvider(const Provider* provider)
    {
        if (!provider || provider->structSize < sizeof(uint32_t))
            return false;
        g_Provider.store(provider, std::memory_order_release);
        return true;
    }

    const Provider* GetProvider()
    {
        return g_Provider.load(std::memory_order_acquire);
    }

    int PatchCreateFileHooksForModule(HMODULE module)
    {
        if (!module)
            return 0;

        int patched = 0;
        patched += PatchIATByFuncName(
            module, "CreateFileW", reinterpret_cast<void*>(CreateFileWWrapper),
            reinterpret_cast<void**>(&g_RealCreateFileW)) ? 1 : 0;
        patched += PatchIATByFuncName(
            module, "CreateFileA", reinterpret_cast<void*>(CreateFileAWrapper),
            reinterpret_cast<void**>(&g_RealCreateFileA)) ? 1 : 0;
        return patched;
    }

    void ApplyEarlyGameLogHooks()
    {
        HMODULE mainModule = GetModuleHandleW(nullptr);
        if (!mainModule)
            return;

        PatchCreateFileHooksForModule(mainModule);

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
}
