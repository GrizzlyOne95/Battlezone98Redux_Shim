// crash_logger.cpp
// BZR Open Shim - crash reporting (unhandled filter + first-chance VEH)
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Written to be usable at crash time: no CRT heap allocation, static
// buffers only, one WriteFile per report chunk, and an interlocked
// reentrancy guard. The text report goes to logs\openshim_crash.log and a
// minidump is written beside it so faulting addresses for engine bugs
// (weaponMask follow crash, renderCount allocation, ODF parse order) can
// be recovered from a single user repro.

#include "crash_logger.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <DbgHelp.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        using FnMiniDumpWriteDump = BOOL(WINAPI*)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
                                                  PMINIDUMP_EXCEPTION_INFORMATION,
                                                  PMINIDUMP_USER_STREAM_INFORMATION,
                                                  PMINIDUMP_CALLBACK_INFORMATION);

        LPTOP_LEVEL_EXCEPTION_FILTER g_PreviousFilter = nullptr;
        PVOID g_VectoredHandle = nullptr;
        FnMiniDumpWriteDump g_MiniDumpWriteDump = nullptr;
        volatile LONG g_InHandler = 0;
        volatile LONG g_FirstChanceBudget = 64;
        char g_CrashLogPath[MAX_PATH] = {};
        char g_DumpDirectory[MAX_PATH] = {};
        uintptr_t g_SeenFirstChanceEips[64] = {};
        volatile LONG g_SeenFirstChanceCount = 0;

        bool EnvDisabled(const char* name)
        {
            char value[16] = {};
            DWORD len = GetEnvironmentVariableA(name, value, sizeof(value));
            if (len == 0 || len >= sizeof(value)) return false;
            return !(value[0] == '0' && value[1] == '\0');
        }

        void AppendChar(char* buffer, size_t capacity, size_t& offset, char c)
        {
            if (offset + 1 < capacity) buffer[offset++] = c;
        }

        void AppendString(char* buffer, size_t capacity, size_t& offset, const char* text)
        {
            while (*text) AppendChar(buffer, capacity, offset, *text++);
        }

        void AppendHex(char* buffer, size_t capacity, size_t& offset, uint32_t value)
        {
            static const char kDigits[] = "0123456789ABCDEF";
            for (int shift = 28; shift >= 0; shift -= 4)
                AppendChar(buffer, capacity, offset, kDigits[(value >> shift) & 0xF]);
        }

        void AppendDecimal(char* buffer, size_t capacity, size_t& offset, uint32_t value)
        {
            char digits[12];
            int count = 0;
            do { digits[count++] = static_cast<char>('0' + value % 10); value /= 10; } while (value);
            while (count > 0) AppendChar(buffer, capacity, offset, digits[--count]);
        }

        // Appends "module.dll+0xRVA" when the address is inside a loaded
        // module, or nothing (returns false) when it is not.
        bool AppendModuleOffset(char* buffer, size_t capacity, size_t& offset, uintptr_t address)
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    reinterpret_cast<LPCSTR>(address), &module) || !module)
                return false;
            char path[MAX_PATH] = {};
            if (GetModuleFileNameA(module, path, MAX_PATH) == 0) return false;
            const char* base = path;
            for (const char* p = path; *p; ++p)
                if (*p == '\\' || *p == '/') base = p + 1;
            AppendString(buffer, capacity, offset, base);
            AppendString(buffer, capacity, offset, "+0x");
            AppendHex(buffer, capacity, offset, static_cast<uint32_t>(address - reinterpret_cast<uintptr_t>(module)));
            return true;
        }

        void WriteToCrashLog(const char* data, size_t length)
        {
            if (!g_CrashLogPath[0]) return;
            HANDLE file = CreateFileA(g_CrashLogPath, FILE_APPEND_DATA,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                      OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE) return;
            DWORD written = 0;
            WriteFile(file, data, static_cast<DWORD>(length), &written, nullptr);
            CloseHandle(file);
        }

        void AppendTimestamp(char* buffer, size_t capacity, size_t& offset)
        {
            SYSTEMTIME st = {};
            GetLocalTime(&st);
            AppendDecimal(buffer, capacity, offset, st.wYear);
            AppendChar(buffer, capacity, offset, '-');
            if (st.wMonth < 10) AppendChar(buffer, capacity, offset, '0');
            AppendDecimal(buffer, capacity, offset, st.wMonth);
            AppendChar(buffer, capacity, offset, '-');
            if (st.wDay < 10) AppendChar(buffer, capacity, offset, '0');
            AppendDecimal(buffer, capacity, offset, st.wDay);
            AppendChar(buffer, capacity, offset, ' ');
            if (st.wHour < 10) AppendChar(buffer, capacity, offset, '0');
            AppendDecimal(buffer, capacity, offset, st.wHour);
            AppendChar(buffer, capacity, offset, ':');
            if (st.wMinute < 10) AppendChar(buffer, capacity, offset, '0');
            AppendDecimal(buffer, capacity, offset, st.wMinute);
            AppendChar(buffer, capacity, offset, ':');
            if (st.wSecond < 10) AppendChar(buffer, capacity, offset, '0');
            AppendDecimal(buffer, capacity, offset, st.wSecond);
        }

        bool IsFatalExceptionCode(DWORD code)
        {
            switch (code)
            {
            case EXCEPTION_ACCESS_VIOLATION:
            case EXCEPTION_ILLEGAL_INSTRUCTION:
            case EXCEPTION_PRIV_INSTRUCTION:
            case EXCEPTION_STACK_OVERFLOW:
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            case EXCEPTION_DATATYPE_MISALIGNMENT:
                return true;
            default:
                return false;
            }
        }

        void AppendExceptionHeader(char* buffer, size_t capacity, size_t& offset,
                                   const EXCEPTION_RECORD* record, const char* kind)
        {
            AppendString(buffer, capacity, offset, "[CRASH] ");
            AppendTimestamp(buffer, capacity, offset);
            AppendString(buffer, capacity, offset, " ");
            AppendString(buffer, capacity, offset, kind);
            AppendString(buffer, capacity, offset, " code=0x");
            AppendHex(buffer, capacity, offset, record->ExceptionCode);
            AppendString(buffer, capacity, offset, " eip=0x");
            AppendHex(buffer, capacity, offset, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(record->ExceptionAddress)));
            AppendString(buffer, capacity, offset, " (");
            if (!AppendModuleOffset(buffer, capacity, offset, reinterpret_cast<uintptr_t>(record->ExceptionAddress)))
                AppendString(buffer, capacity, offset, "unmapped");
            AppendString(buffer, capacity, offset, ")");
            if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2)
            {
                AppendString(buffer, capacity, offset,
                             record->ExceptionInformation[0] == 1 ? " write=0x" :
                             record->ExceptionInformation[0] == 8 ? " exec=0x" : " read=0x");
                AppendHex(buffer, capacity, offset, static_cast<uint32_t>(record->ExceptionInformation[1]));
            }
            AppendString(buffer, capacity, offset, " tid=");
            AppendDecimal(buffer, capacity, offset, GetCurrentThreadId());
            AppendString(buffer, capacity, offset, "\r\n");
        }

        void AppendRegisters(char* buffer, size_t capacity, size_t& offset, const CONTEXT* context)
        {
#if defined(_M_IX86)
            struct { const char* name; DWORD value; } regs[] = {
                { "eax", context->Eax }, { "ebx", context->Ebx },
                { "ecx", context->Ecx }, { "edx", context->Edx },
                { "esi", context->Esi }, { "edi", context->Edi },
                { "ebp", context->Ebp }, { "esp", context->Esp },
                { "eip", context->Eip }, { "efl", context->EFlags },
            };
            AppendString(buffer, capacity, offset, "  regs:");
            for (const auto& reg : regs)
            {
                AppendString(buffer, capacity, offset, " ");
                AppendString(buffer, capacity, offset, reg.name);
                AppendString(buffer, capacity, offset, "=0x");
                AppendHex(buffer, capacity, offset, reg.value);
            }
            AppendString(buffer, capacity, offset, "\r\n");
#else
            (void)buffer; (void)capacity; (void)offset; (void)context;
#endif
        }

        // Scans stack dwords and reports the ones that land inside a loaded
        // module - a poor man's backtrace that survives frame-pointer
        // omission and works without symbol lookup at crash time.
        void AppendStackScan(char* buffer, size_t capacity, size_t& offset, const CONTEXT* context)
        {
#if defined(_M_IX86)
            const uint32_t* stack = reinterpret_cast<const uint32_t*>(context->Esp & ~3u);
            AppendString(buffer, capacity, offset, "  stack-scan (esp=0x");
            AppendHex(buffer, capacity, offset, context->Esp);
            AppendString(buffer, capacity, offset, "):\r\n");
            int reported = 0;
            for (int index = 0; index < 512 && reported < 24; ++index)
            {
                uint32_t value = 0;
                if (IsBadReadPtr(stack + index, sizeof(uint32_t))) break;
                value = stack[index];
                if (value < 0x10000) continue;
                MEMORY_BASIC_INFORMATION info = {};
                if (!VirtualQuery(reinterpret_cast<LPCVOID>(static_cast<uintptr_t>(value)), &info, sizeof(info)))
                    continue;
                if (!(info.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
                    continue;
                size_t lineStart = offset;
                AppendString(buffer, capacity, offset, "    esp+0x");
                AppendHex(buffer, capacity, offset, index * 4);
                AppendString(buffer, capacity, offset, " 0x");
                AppendHex(buffer, capacity, offset, value);
                AppendString(buffer, capacity, offset, " ");
                if (!AppendModuleOffset(buffer, capacity, offset, value))
                {
                    offset = lineStart;
                    continue;
                }
                AppendString(buffer, capacity, offset, "\r\n");
                ++reported;
            }
#else
            (void)buffer; (void)capacity; (void)offset; (void)context;
#endif
        }

        void WriteMinidump(EXCEPTION_POINTERS* pointers)
        {
            if (!g_MiniDumpWriteDump || !g_DumpDirectory[0]) return;
            char path[MAX_PATH] = {};
            size_t offset = 0;
            AppendString(path, sizeof(path), offset, g_DumpDirectory);
            AppendString(path, sizeof(path), offset, "\\openshim_crash_");
            SYSTEMTIME st = {};
            GetLocalTime(&st);
            AppendDecimal(path, sizeof(path), offset, st.wYear);
            if (st.wMonth < 10) AppendChar(path, sizeof(path), offset, '0');
            AppendDecimal(path, sizeof(path), offset, st.wMonth);
            if (st.wDay < 10) AppendChar(path, sizeof(path), offset, '0');
            AppendDecimal(path, sizeof(path), offset, st.wDay);
            AppendChar(path, sizeof(path), offset, '_');
            if (st.wHour < 10) AppendChar(path, sizeof(path), offset, '0');
            AppendDecimal(path, sizeof(path), offset, st.wHour);
            if (st.wMinute < 10) AppendChar(path, sizeof(path), offset, '0');
            AppendDecimal(path, sizeof(path), offset, st.wMinute);
            if (st.wSecond < 10) AppendChar(path, sizeof(path), offset, '0');
            AppendDecimal(path, sizeof(path), offset, st.wSecond);
            AppendString(path, sizeof(path), offset, ".dmp");
            path[offset < sizeof(path) ? offset : sizeof(path) - 1] = '\0';

            HANDLE file = CreateFileA(path, GENERIC_WRITE, 0, nullptr,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE) return;
            MINIDUMP_EXCEPTION_INFORMATION exceptionInfo = {};
            exceptionInfo.ThreadId = GetCurrentThreadId();
            exceptionInfo.ExceptionPointers = pointers;
            exceptionInfo.ClientPointers = FALSE;
            const MINIDUMP_TYPE dumpType = static_cast<MINIDUMP_TYPE>(
                MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithIndirectlyReferencedMemory);
            g_MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file,
                                dumpType, &exceptionInfo, nullptr, nullptr);
            CloseHandle(file);
        }

        void WriteCrashReport(EXCEPTION_POINTERS* pointers, const char* kind, bool withDump)
        {
            static char buffer[16384];
            size_t offset = 0;
            AppendExceptionHeader(buffer, sizeof(buffer), offset, pointers->ExceptionRecord, kind);
            AppendRegisters(buffer, sizeof(buffer), offset, pointers->ContextRecord);
            AppendStackScan(buffer, sizeof(buffer), offset, pointers->ContextRecord);
            WriteToCrashLog(buffer, offset);
            if (withDump && !EnvDisabled("OPENSHIM_DISABLE_CRASH_DUMP"))
                WriteMinidump(pointers);
        }

        LONG WINAPI UnhandledFilter(EXCEPTION_POINTERS* pointers)
        {
            if (InterlockedCompareExchange(&g_InHandler, 1, 0) == 0)
            {
                WriteCrashReport(pointers, "unhandled", true);
                InterlockedExchange(&g_InHandler, 0);
            }
            if (g_PreviousFilter) return g_PreviousFilter(pointers);
            return EXCEPTION_CONTINUE_SEARCH;
        }

        LONG WINAPI FirstChanceLogger(EXCEPTION_POINTERS* pointers)
        {
            const EXCEPTION_RECORD* record = pointers->ExceptionRecord;
            if (!IsFatalExceptionCode(record->ExceptionCode))
                return EXCEPTION_CONTINUE_SEARCH;
            if (g_FirstChanceBudget <= 0)
                return EXCEPTION_CONTINUE_SEARCH;

            // Log each faulting eip once so a handled-and-retried exception
            // cannot flood the report file.
            const uintptr_t eip = reinterpret_cast<uintptr_t>(record->ExceptionAddress);
            LONG seen = g_SeenFirstChanceCount;
            for (LONG index = 0; index < seen && index < 64; ++index)
                if (g_SeenFirstChanceEips[index] == eip)
                    return EXCEPTION_CONTINUE_SEARCH;
            LONG slot = InterlockedIncrement(&g_SeenFirstChanceCount) - 1;
            if (slot < 64) g_SeenFirstChanceEips[slot] = eip;

            if (InterlockedDecrement(&g_FirstChanceBudget) >= 0 &&
                InterlockedCompareExchange(&g_InHandler, 1, 0) == 0)
            {
                WriteCrashReport(pointers, "first-chance", false);
                InterlockedExchange(&g_InHandler, 0);
            }
            return EXCEPTION_CONTINUE_SEARCH;
        }
    }

    void InstallCrashLogger()
    {
        static bool s_Installed = false;
        if (s_Installed) return;
        if (EnvDisabled("OPENSHIM_DISABLE_CRASH_LOGGER"))
        {
            LogShimA(LogLevel::Info, "crash", "Crash logger disabled by environment");
            return;
        }
        s_Installed = true;

        const std::string logPath = GetGameLogPath("openshim_crash.log");
        lstrcpynA(g_CrashLogPath, logPath.c_str(), MAX_PATH);
        lstrcpynA(g_DumpDirectory, logPath.c_str(), MAX_PATH);
        for (int index = lstrlenA(g_DumpDirectory) - 1; index >= 0; --index)
        {
            if (g_DumpDirectory[index] == '\\' || g_DumpDirectory[index] == '/')
            {
                g_DumpDirectory[index] = '\0';
                break;
            }
        }

        HMODULE dbghelp = LoadLibraryA("dbghelp.dll");
        if (dbghelp)
            g_MiniDumpWriteDump = reinterpret_cast<FnMiniDumpWriteDump>(
                GetProcAddress(dbghelp, "MiniDumpWriteDump"));

        g_PreviousFilter = SetUnhandledExceptionFilter(UnhandledFilter);
        if (!EnvDisabled("OPENSHIM_DISABLE_CRASH_VEH"))
            g_VectoredHandle = AddVectoredExceptionHandler(0, FirstChanceLogger);

        LogShimA(LogLevel::Info, "crash",
                 "Crash logger installed log=%s dump=%s veh=%s previousFilter=0x%p",
                 g_CrashLogPath,
                 g_MiniDumpWriteDump ? "available" : "unavailable",
                 g_VectoredHandle ? "on" : "off",
                 reinterpret_cast<void*>(g_PreviousFilter));
    }
}
