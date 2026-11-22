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
// be recovered from a single user repro. Each crash also copies the log to
// openshim_crash_<time>.log beside its .dmp, since the next launch
// truncates openshim_crash.log.
//
// Paths that reach a report:
//   unhandled exception      UnhandledFilter (SetUnhandledExceptionFilter)
//   stack overflow           StackOverflowCatcher (first VEH) hands the
//                            record to a watcher thread made at install,
//                            which writes the report and dump on its own stack
//   CRT purecall, invalid parameter, std::terminate, abort (SIGABRT)
//                            handlers in both the game's msvcr120.dll and
//                            OpenShim's own UCRT; each reports once
// __fastfail (including the CRT's own fail-fast paths after these handlers)
// ends the process in the kernel and cannot be caught in-process; only WER
// LocalDumps or procdump capture it.
//
// Minidumps: MiniDumpNormal + thread info, on by default ([Diagnostics]
// CrashMinidumps = 0 or OPENSHIM_DISABLE_CRASH_DUMP turns them off); the
// newest kKeptDumps openshim_crash_*.dmp are kept. They stay on this PC.

#include "crash_logger.h"
#include "crash_av_classify.h"
#include "crash_dump_retention.h"
#include "memory_access.h"
#include "shim_log.h"
#include "shim_log_sink.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <DbgHelp.h>
#include <algorithm>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <intrin.h>
#include <string>
#include <vector>

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
        volatile LONG g_EarlyFatalReported = 0;
        volatile uintptr_t g_EarlyFatalEip = 0;
        volatile DWORD g_EarlyFatalThreadId = 0;
        HMODULE g_SelfModule = nullptr;
        HMODULE g_ProxyModule = nullptr;
        // Read at install: the unhandled filter must not call
        // GetEnvironmentVariableA, which takes the PEB lock a faulting thread
        // may already hold.
        bool g_CrashDumpDisabled = false;
        // Thread the report is about when it is written from another thread
        // (the stack-overflow watcher); 0 = the current thread.
        DWORD g_ReportThreadId = 0;
        // One dump per process for the CRT handlers: purecall is followed by
        // the CRT's own abort, which would report again.
        volatile LONG g_SyntheticReported = 0;

        // Stack overflow hand-off (see StackOverflowCatcher).
        HANDLE g_SoRequest = nullptr;
        HANDLE g_SoDone = nullptr;
        volatile LONG g_SoClaimed = 0;
        EXCEPTION_RECORD g_SoRecord = {};
        CONTEXT g_SoContext = {};
        DWORD g_SoThreadId = 0;

        // Watcher thread made at install. It writes the stack-overflow
        // report on its own stack and forwards the dump line to openshim.log
        // (whose lock a crashing thread may hold; the wait is bounded).
        HANDLE g_WatcherThread = nullptr;
        DWORD g_WatcherThreadId = 0;
        HANDLE g_LogRequest = nullptr;
        HANDLE g_LogDone = nullptr;
        char g_LogLine[MAX_PATH + 192] = {};

        constexpr DWORD kCodeCrtAbort = 0x40000015;            // STATUS_FATAL_APP_EXIT
        constexpr DWORD kCodeCrtInvalidParameter = 0xC0000417; // STATUS_INVALID_CRUNTIME_PARAMETER

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
            // A vectored handler sees exceptions before the program's SEH
            // handlers do. OpenShim deliberately uses SEH around a few
            // best-effort engine/Ogre probes, so calling every first-chance AV
            // a crash makes healthy sessions look fatal in support bundles.
            AppendString(buffer, capacity, offset,
                         kind && kind[0] == 'f' ? "[FIRST-CHANCE] " : "[CRASH] ");
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
            AppendDecimal(buffer, capacity, offset, g_ReportThreadId ? g_ReportThreadId : GetCurrentThreadId());
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

        // <logdir>\openshim_crash_YYYYMMDD_HHMMSS, shared by the .dmp and the .log copy.
        size_t BuildCrashStem(char* path, size_t capacity)
        {
            size_t offset = 0;
            AppendString(path, capacity, offset, g_DumpDirectory);
            AppendString(path, capacity, offset, "\\openshim_crash_");
            SYSTEMTIME st = {};
            GetLocalTime(&st);
            AppendDecimal(path, capacity, offset, st.wYear);
            if (st.wMonth < 10) AppendChar(path, capacity, offset, '0');
            AppendDecimal(path, capacity, offset, st.wMonth);
            if (st.wDay < 10) AppendChar(path, capacity, offset, '0');
            AppendDecimal(path, capacity, offset, st.wDay);
            AppendChar(path, capacity, offset, '_');
            if (st.wHour < 10) AppendChar(path, capacity, offset, '0');
            AppendDecimal(path, capacity, offset, st.wHour);
            if (st.wMinute < 10) AppendChar(path, capacity, offset, '0');
            AppendDecimal(path, capacity, offset, st.wMinute);
            if (st.wSecond < 10) AppendChar(path, capacity, offset, '0');
            AppendDecimal(path, capacity, offset, st.wSecond);
            return offset;
        }

        void SetExtension(char* path, size_t capacity, size_t stemLength, const char* extension)
        {
            size_t offset = stemLength;
            AppendString(path, capacity, offset, extension);
            path[offset < capacity ? offset : capacity - 1] = '\0';
        }

        // CopyFileA allocates on the process heap; copy through a static buffer instead.
        void CopyCrashLog(const char* destination)
        {
            HANDLE source = CreateFileA(g_CrashLogPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (source == INVALID_HANDLE_VALUE) return;
            HANDLE target = CreateFileA(destination, GENERIC_WRITE, 0, nullptr,
                                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (target != INVALID_HANDLE_VALUE)
            {
                static char chunk[16384];
                DWORD read = 0;
                DWORD written = 0;
                while (ReadFile(source, chunk, sizeof(chunk), &read, nullptr) && read)
                    if (!WriteFile(target, chunk, read, &written, nullptr)) break;
                CloseHandle(target);
            }
            CloseHandle(source);
        }

        // Returns 0 on success, else a Win32 error (ERROR_PROC_NOT_FOUND when
        // dbghelp did not load).
        DWORD WriteMinidump(EXCEPTION_POINTERS* pointers, char* path, size_t capacity, size_t stemLength)
        {
            if (!g_MiniDumpWriteDump) return ERROR_PROC_NOT_FOUND;
            SetExtension(path, capacity, stemLength, ".dmp");
            HANDLE file = CreateFileA(path, GENERIC_WRITE, 0, nullptr,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE) return GetLastError();
            MINIDUMP_EXCEPTION_INFORMATION exceptionInfo = {};
            exceptionInfo.ThreadId = g_ReportThreadId ? g_ReportThreadId : GetCurrentThreadId();
            exceptionInfo.ExceptionPointers = pointers;
            exceptionInfo.ClientPointers = FALSE;
            // Stacks, registers, module list and thread info. Data segments
            // are left out: the game image alone has tens of MB of .data/.bss.
            const MINIDUMP_TYPE dumpType = static_cast<MINIDUMP_TYPE>(MiniDumpNormal | MiniDumpWithThreadInfo);
            const BOOL ok = g_MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file,
                                                dumpType, &exceptionInfo, nullptr, nullptr);
            // MiniDumpWriteDump returns an HRESULT in GetLastError on failure.
            const DWORD error = ok ? 0 : (GetLastError() ? GetLastError() : ERROR_GEN_FAILURE);
            CloseHandle(file);
            if (!ok) DeleteFileA(path);
            return error;
        }

        // Keeps the newest kKeptDumps openshim_crash_YYYYMMDD_HHMMSS.dmp in the
        // dump folder and deletes only other names of that exact layout, never
        // `keepPath` (the dump just written). Fixed buffers: it also runs
        // after a crash dump is written, as the last step of the report
        // (FindFirstFile may still allocate, so nothing important follows it).
        void PruneOldCrashDumps(const char* keepPath)
        {
            if (!g_DumpDirectory[0]) return;
            static char path[MAX_PATH];
            static CrashDumpRetention::NewestKeeper keeper;
            keeper = CrashDumpRetention::NewestKeeper{};
            if (keepPath)
            {
                const char* keepName = keepPath;
                for (const char* p = keepPath; *p; ++p)
                    if (*p == '\\' || *p == '/') keepName = p + 1;
                keeper.Protect(keepName);
            }
            size_t offset = 0;
            AppendString(path, sizeof(path), offset, g_DumpDirectory);
            const size_t directoryLength = offset;
            AppendString(path, sizeof(path), offset, "\\openshim_crash_*.dmp");
            if (offset + 1 >= sizeof(path)) return;
            path[offset] = '\0';

            static WIN32_FIND_DATAA found;
            HANDLE search = FindFirstFileA(path, &found);
            if (search == INVALID_HANDLE_VALUE) return;
            do
            {
                if (!(found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    keeper.Offer(found.cFileName);
            } while (FindNextFileA(search, &found));
            FindClose(search);

            search = FindFirstFileA(path, &found);
            if (search == INVALID_HANDLE_VALUE) return;
            do
            {
                if ((found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || !keeper.ShouldDelete(found.cFileName))
                    continue;
                size_t fileOffset = directoryLength;
                static char victim[MAX_PATH];
                std::memcpy(victim, g_DumpDirectory, directoryLength);
                AppendChar(victim, sizeof(victim), fileOffset, '\\');
                AppendString(victim, sizeof(victim), fileOffset, found.cFileName);
                if (fileOffset + 1 >= sizeof(victim)) continue;
                victim[fileOffset] = '\0';
                DeleteFileA(victim);
            } while (FindNextFileA(search, &found));
            FindClose(search);
        }

        // False once ExitProcess has ended the watcher (a crash in a DLL
        // detach must not wait on it).
        bool WatcherAlive()
        {
            return g_WatcherThread && WaitForSingleObject(g_WatcherThread, 0) == WAIT_TIMEOUT;
        }

        // Sends one line to openshim.log through the watcher thread, waiting
        // at most 2 s: the crashing thread may hold the log lock. Skipped when
        // there is no watcher. On the watcher itself (stack-overflow report)
        // it writes directly; that is the report's last step, so a held lock
        // there loses only this line.
        void MirrorToShimLog(const char* line)
        {
            const ShimLogSinkFn sink = GetShimLogSink();
            if (!sink) return;
            if (GetCurrentThreadId() == g_WatcherThreadId)
            {
                sink(static_cast<uint32_t>(LogLevel::Error), "crash", line);
                return;
            }
            if (!g_LogRequest || !g_LogDone || !WatcherAlive()) return;
            lstrcpynA(g_LogLine, line, sizeof(g_LogLine));
            ResetEvent(g_LogDone);
            SetEvent(g_LogRequest);
            WaitForSingleObject(g_LogDone, 2000);
        }

        // "[CRASH] minidump saved: <path> (send this file with your report)",
        // or why none was written, to openshim_crash.log. Returns the line
        // (no CRLF) for openshim.log, which the caller writes last.
        const char* ReportDumpOutcome(const char* path, DWORD error)
        {
            static char line[MAX_PATH + 160];
            size_t offset = 0;
            if (error == 0)
            {
                AppendString(line, sizeof(line), offset, "[CRASH] minidump saved: ");
                AppendString(line, sizeof(line), offset, path);
                AppendString(line, sizeof(line), offset, " (send this file with your report)");
            }
            else if (g_CrashDumpDisabled)
            {
                AppendString(line, sizeof(line), offset,
                             "[CRASH] minidump not written: turned off ([Diagnostics] CrashMinidumps = 0 "
                             "or OPENSHIM_DISABLE_CRASH_DUMP)");
            }
            else
            {
                AppendString(line, sizeof(line), offset, "[CRASH] minidump failed: ");
                AppendString(line, sizeof(line), offset,
                             error == ERROR_PROC_NOT_FOUND ? "dbghelp.dll MiniDumpWriteDump unavailable"
                                                           : "could not write ");
                if (error != ERROR_PROC_NOT_FOUND)
                    AppendString(line, sizeof(line), offset, path);
                AppendString(line, sizeof(line), offset, " (error 0x");
                AppendHex(line, sizeof(line), offset, error);
                AppendString(line, sizeof(line), offset, ")");
            }
            const size_t messageLength = offset;
            AppendString(line, sizeof(line), offset, "\r\n");
            WriteToCrashLog(line, offset);
            line[messageLength < sizeof(line) ? messageLength : sizeof(line) - 1] = '\0';
            return line;
        }

        void WriteCrashReport(EXCEPTION_POINTERS* pointers, const char* kind, bool withDump)
        {
            static char buffer[16384];
            size_t offset = 0;
            AppendExceptionHeader(buffer, sizeof(buffer), offset, pointers->ExceptionRecord, kind);
            AppendRegisters(buffer, sizeof(buffer), offset, pointers->ContextRecord);
            AppendStackScan(buffer, sizeof(buffer), offset, pointers->ContextRecord);
            WriteToCrashLog(buffer, offset);
            if (!withDump || !g_DumpDirectory[0]) return;
            static char path[MAX_PATH];
            const size_t stemLength = BuildCrashStem(path, sizeof(path));
            if (stemLength + sizeof(".dmp") > sizeof(path)) return; // no room for an extension
            DWORD dumpError = ERROR_CANCELLED;
            if (!g_CrashDumpDisabled)
                dumpError = WriteMinidump(pointers, path, sizeof(path), stemLength);
            const char* dumpLine = ReportDumpOutcome(path, dumpError);
            if (dumpError == 0)
                PruneOldCrashDumps(path);
            // The next launch truncates openshim_crash.log, so keep this crash's
            // copy (now including the dump line) beside its dump.
            SetExtension(path, sizeof(path), stemLength, ".log");
            CopyCrashLog(path);
            // Last: this may wait up to 2 s, or lose the line, if the log lock is held.
            MirrorToShimLog(dumpLine);
        }

        // Report for a CRT handler: no exception record exists, so one is
        // made up with the handler's caller as the address. One dump per
        // process; later handlers (the CRT's abort after purecall) log only.
        void ReportCrtFailure(const char* kind, DWORD code, void* caller)
        {
            if (InterlockedCompareExchange(&g_InHandler, 1, 0) != 0)
                return;
            static CONTEXT context;
            static EXCEPTION_RECORD record;
            RtlCaptureContext(&context);
            record = {};
            record.ExceptionCode = code;
            record.ExceptionFlags = EXCEPTION_NONCONTINUABLE;
            record.ExceptionAddress = caller;
            EXCEPTION_POINTERS pointers = { &record, &context };
            const bool first = InterlockedExchange(&g_SyntheticReported, 1) == 0;
            WriteCrashReport(&pointers, kind, first);
            InterlockedExchange(&g_InHandler, 0);
        }

        // First VEH. On a stack overflow the faulting thread has a few KB
        // left: copy the record and context, wake the watcher, and wait while
        // it writes the report and dump on its own stack. Once per process.
        LONG WINAPI StackOverflowCatcher(EXCEPTION_POINTERS* pointers)
        {
            if (pointers->ExceptionRecord->ExceptionCode != EXCEPTION_STACK_OVERFLOW)
                return EXCEPTION_CONTINUE_SEARCH;
            // The watcher cannot serve its own overflow; the unhandled filter
            // reports that one (on the overflowed stack, as before this change).
            if (GetCurrentThreadId() == g_WatcherThreadId || !g_SoRequest || !g_SoDone || !WatcherAlive())
                return EXCEPTION_CONTINUE_SEARCH;
            if (InterlockedCompareExchange(&g_SoClaimed, 1, 0) != 0)
                return EXCEPTION_CONTINUE_SEARCH;
            g_SoRecord = *pointers->ExceptionRecord;
            g_SoRecord.ExceptionRecord = nullptr;
            g_SoContext = *pointers->ContextRecord;
            g_SoThreadId = GetCurrentThreadId();
            SetEvent(g_SoRequest);
            WaitForSingleObject(g_SoDone, 15000);
            return EXCEPTION_CONTINUE_SEARCH;
        }

        void WriteStackOverflowReport()
        {
            // Another report may be mid-write; wait for it briefly.
            for (int tries = 0; InterlockedCompareExchange(&g_InHandler, 1, 0) != 0; ++tries)
            {
                if (tries >= 200) return;
                Sleep(10);
            }
            EXCEPTION_POINTERS pointers = { &g_SoRecord, &g_SoContext };
            g_ReportThreadId = g_SoThreadId;
            WriteCrashReport(&pointers, "stack-overflow", true);
            g_ReportThreadId = 0;
            InterlockedExchange(&g_InHandler, 0);
        }

        DWORD WINAPI WatcherThread(LPVOID)
        {
            HANDLE waits[2] = { g_SoRequest, g_LogRequest };
            for (;;)
            {
                const DWORD which = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
                if (which == WAIT_OBJECT_0)
                {
                    WriteStackOverflowReport();
                    SetEvent(g_SoDone);
                }
                else if (which == WAIT_OBJECT_0 + 1)
                {
                    const ShimLogSinkFn sink = GetShimLogSink();
                    if (sink) sink(static_cast<uint32_t>(LogLevel::Error), "crash", g_LogLine);
                    SetEvent(g_LogDone);
                }
                else
                {
                    return 0;
                }
            }
        }

        // ---- CRT handlers -------------------------------------------------
        // Each is set in the game's msvcr120.dll (resolved by name, so a
        // missing export just skips it) and in OpenShim's own UCRT.

        using FnPurecall = void(__cdecl*)();
        using FnInvalidParameter = void(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned, uintptr_t);
        using FnTerminate = void(__cdecl*)();
        using FnSignal = void(__cdecl*)(int);
        using FnSetPurecall = FnPurecall(__cdecl*)(FnPurecall);
        using FnSetInvalidParameter = FnInvalidParameter(__cdecl*)(FnInvalidParameter);
        using FnSetTerminate = FnTerminate(__cdecl*)(FnTerminate);
        using FnSetSignal = FnSignal(__cdecl*)(int, FnSignal);
        using FnAbort = void(__cdecl*)();

        struct CrtHandlers
        {
            FnPurecall purecall = nullptr;
            FnInvalidParameter invalidParameter = nullptr;
            FnTerminate terminate = nullptr;
            FnSignal abortSignal = nullptr;
            FnAbort abort = nullptr;
        };
        CrtHandlers g_GameCrt;  // previous handlers in msvcr120.dll
        CrtHandlers g_ShimCrt;  // previous handlers in OpenShim's UCRT

        bool IsRealSignalHandler(FnSignal handler)
        {
            return handler != SIG_DFL && handler != SIG_IGN && handler != SIG_ERR && handler != nullptr;
        }

        void OnPurecall(const CrtHandlers& previous, void* caller)
        {
            ReportCrtFailure("purecall", kCodeCrtAbort, caller);
            if (previous.purecall) previous.purecall();
            // Returning lets the CRT end the process as it would without us.
        }

        void OnInvalidParameter(const CrtHandlers& previous, void* caller,
                                const wchar_t* expression, const wchar_t* function,
                                const wchar_t* file, unsigned line, uintptr_t reserved)
        {
            ReportCrtFailure("invalid-parameter", kCodeCrtInvalidParameter, caller);
            // Keep what would have happened without us: an earlier handler
            // decides (it may return, and the CRT call fails with EINVAL);
            // with none, the CRT's default ends the process, so never return
            // into the CRT here.
            if (previous.invalidParameter)
            {
                previous.invalidParameter(expression, function, file, line, reserved);
                return;
            }
            __fastfail(5); // FAST_FAIL_INVALID_ARG, as the CRT's default does
        }

        [[noreturn]] void OnTerminate(const CrtHandlers& previous, void* caller)
        {
            ReportCrtFailure("terminate", kCodeCrtAbort, caller);
            if (previous.terminate) previous.terminate();
            if (previous.abort) previous.abort();
            std::abort();
        }

        void OnAbortSignal(const CrtHandlers& previous, int signalNumber, void* caller)
        {
            ReportCrtFailure("abort", kCodeCrtAbort, caller);
            if (IsRealSignalHandler(previous.abortSignal)) previous.abortSignal(signalNumber);
        }

        void __cdecl GamePurecall() { OnPurecall(g_GameCrt, _ReturnAddress()); }
        void __cdecl GameInvalidParameter(const wchar_t* e, const wchar_t* f, const wchar_t* file, unsigned line, uintptr_t r)
        {
            OnInvalidParameter(g_GameCrt, _ReturnAddress(), e, f, file, line, r);
        }
        void __cdecl GameTerminate() { OnTerminate(g_GameCrt, _ReturnAddress()); }
        void __cdecl GameAbortSignal(int signalNumber) { OnAbortSignal(g_GameCrt, signalNumber, _ReturnAddress()); }

        void __cdecl ShimPurecall() { OnPurecall(g_ShimCrt, _ReturnAddress()); }
        void __cdecl ShimInvalidParameter(const wchar_t* e, const wchar_t* f, const wchar_t* file, unsigned line, uintptr_t r)
        {
            OnInvalidParameter(g_ShimCrt, _ReturnAddress(), e, f, file, line, r);
        }
        void __cdecl ShimTerminate() { OnTerminate(g_ShimCrt, _ReturnAddress()); }
        void __cdecl ShimAbortSignal(int signalNumber) { OnAbortSignal(g_ShimCrt, signalNumber, _ReturnAddress()); }

        // terminate handlers are per thread in both CRTs: this covers the
        // thread that installs the logger (the plugin load thread).
        void InstallGameCrtHandlers(char* summary, size_t capacity)
        {
            HMODULE crt = GetModuleHandleA("msvcr120.dll");
            if (!crt)
            {
                lstrcpynA(summary, "msvcr120.dll not loaded", static_cast<int>(capacity));
                return;
            }
            size_t offset = 0;
            const auto setPurecall = reinterpret_cast<FnSetPurecall>(GetProcAddress(crt, "_set_purecall_handler"));
            const auto setInvalid = reinterpret_cast<FnSetInvalidParameter>(
                GetProcAddress(crt, "_set_invalid_parameter_handler"));
            const auto setTerminate = reinterpret_cast<FnSetTerminate>(
                GetProcAddress(crt, "?set_terminate@@YAP6AXXZP6AXXZ@Z"));
            const auto setSignal = reinterpret_cast<FnSetSignal>(GetProcAddress(crt, "signal"));
            g_GameCrt.abort = reinterpret_cast<FnAbort>(GetProcAddress(crt, "abort"));
            if (setPurecall)
            {
                g_GameCrt.purecall = setPurecall(&GamePurecall);
                AppendString(summary, capacity, offset, "purecall ");
            }
            if (setInvalid)
            {
                g_GameCrt.invalidParameter = setInvalid(&GameInvalidParameter);
                AppendString(summary, capacity, offset, "invalid-parameter ");
            }
            if (setTerminate)
            {
                g_GameCrt.terminate = setTerminate(&GameTerminate);
                AppendString(summary, capacity, offset, "terminate ");
            }
            if (setSignal)
            {
                const FnSignal previous = setSignal(SIGABRT, &GameAbortSignal);
                if (previous != SIG_ERR)
                {
                    g_GameCrt.abortSignal = previous;
                    AppendString(summary, capacity, offset, "abort");
                }
            }
            if (offset == 0) AppendString(summary, capacity, offset, "none");
            summary[offset < capacity ? offset : capacity - 1] = '\0';
        }

        void InstallShimCrtHandlers()
        {
            g_ShimCrt.purecall = _set_purecall_handler(&ShimPurecall);
            g_ShimCrt.invalidParameter = _set_invalid_parameter_handler(&ShimInvalidParameter);
            g_ShimCrt.terminate = std::set_terminate(&ShimTerminate);
            const FnSignal previous = std::signal(SIGABRT, &ShimAbortSignal);
            g_ShimCrt.abortSignal = previous == SIG_ERR ? nullptr : previous;
        }

        LONG WINAPI UnhandledFilter(EXCEPTION_POINTERS* pointers)
        {
            // Already reported from the watcher; writing again here would run
            // on the overflowed stack.
            // Only the overflow the watcher reported: same thread and address.
            const bool overflowReported = pointers->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW &&
                                          g_SoClaimed != 0 && g_SoThreadId == GetCurrentThreadId() &&
                                          g_SoRecord.ExceptionAddress == pointers->ExceptionRecord->ExceptionAddress;
            // The first-chance path already dumped this fault; log the record
            // again but keep one dump per crash.
            const bool earlyDumped = g_EarlyFatalReported != 0 && g_EarlyFatalThreadId == GetCurrentThreadId() &&
                                     g_EarlyFatalEip == reinterpret_cast<uintptr_t>(pointers->ExceptionRecord->ExceptionAddress);
            if (!overflowReported && InterlockedCompareExchange(&g_InHandler, 1, 0) == 0)
            {
                WriteCrashReport(pointers, "unhandled", !earlyDumped);
                InterlockedExchange(&g_InHandler, 0);
            }
            if (g_PreviousFilter) return g_PreviousFilter(pointers);
            return EXCEPTION_CONTINUE_SEARCH;
        }

        HMODULE ModuleOf(uintptr_t address)
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    reinterpret_cast<LPCSTR>(address), &module))
                return nullptr;
            return module;
        }

        bool IsShimModule(HMODULE module)
        {
            return module != nullptr && (module == g_SelfModule || module == g_ProxyModule);
        }

        // True when a shim __try guard is around a shim call through a bad
        // pointer, so the fault may recover: the dword at esp (the return
        // address the call pushed) and the handler of the nearest SEH record
        // are both in an OpenShim module (this plugin or the winmm.dll proxy).
        // A shim call with no guard of its own still dumps.
        bool ShimGuardedCall(const CONTEXT* context)
        {
#if defined(_M_IX86)
            const uintptr_t* top = reinterpret_cast<const uintptr_t*>(context->Esp);
            if (!top || !MemoryAccess::IsReadable(top, sizeof(*top)) || !IsShimModule(ModuleOf(*top)))
                return false;
            const NT_TIB* tib = reinterpret_cast<const NT_TIB*>(NtCurrentTeb());
            const EXCEPTION_REGISTRATION_RECORD* frame = tib->ExceptionList;
            const uintptr_t at = reinterpret_cast<uintptr_t>(frame);
            if (at == 0xFFFFFFFFu || at < reinterpret_cast<uintptr_t>(tib->StackLimit) ||
                at + sizeof(*frame) > reinterpret_cast<uintptr_t>(tib->StackBase) || (at & 3) != 0)
                return false;
            return IsShimModule(ModuleOf(reinterpret_cast<uintptr_t>(frame->Handler)));
#else
            (void)context;
            return false;
#endif
        }

        bool IsCertainlyFatal(const EXCEPTION_POINTERS* pointers)
        {
            const EXCEPTION_RECORD* record = pointers->ExceptionRecord;
            if (record->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) return false;
            CrashAvClassify::FaultFacts facts = {};
            facts.code = record->ExceptionCode;
            facts.numberParameters = record->NumberParameters;
            facts.accessKind = record->NumberParameters >= 1 ? record->ExceptionInformation[0] : 0;
            facts.faultAddress = record->NumberParameters >= 2 ? record->ExceptionInformation[1] : 0;
            facts.eip = reinterpret_cast<uintptr_t>(record->ExceptionAddress);
            facts.eipExecutable = MemoryAccess::IsExecutable(record->ExceptionAddress);
            // Cheap facts first: handled probes never reach the module
            // lookups, which may take the loader lock.
            if (!CrashAvClassify::IsCertainlyFatalAv(facts)) return false;
            facts.shimGuardedCall = ShimGuardedCall(pointers->ContextRecord);
            return CrashAvClassify::IsCertainlyFatalAv(facts);
        }

        LONG WINAPI FirstChanceLogger(EXCEPTION_POINTERS* pointers)
        {
            const EXCEPTION_RECORD* record = pointers->ExceptionRecord;
            if (!IsFatalExceptionCode(record->ExceptionCode))
                return EXCEPTION_CONTINUE_SEARCH;
            // A first-chance report runs on the overflowed stack: the file
            // write and region scan double-fault and lose the unhandled report
            // and minidump that would otherwise follow.
            if (record->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
                return EXCEPTION_CONTINUE_SEARCH;
            // Running code that is not there cannot be recovered. Write the
            // full [CRASH] record and minidump now (once per process): some
            // runtimes end the process before the unhandled filter runs.
            if (g_EarlyFatalReported == 0 && IsCertainlyFatal(pointers) &&
                InterlockedCompareExchange(&g_InHandler, 1, 0) == 0)
            {
                if (InterlockedCompareExchange(&g_EarlyFatalReported, 1, 0) == 0)
                {
                    g_EarlyFatalEip = reinterpret_cast<uintptr_t>(record->ExceptionAddress);
                    g_EarlyFatalThreadId = GetCurrentThreadId();
                    WriteCrashReport(pointers, "non-code-eip", true);
                }
                InterlockedExchange(&g_InHandler, 0);
                return EXCEPTION_CONTINUE_SEARCH;
            }
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

        // Keeps the newest kKeptCrashFiles files matching the pattern in the
        // dump directory. The names carry YYYYMMDD_HHMMSS, so name order is
        // age order.
        void PruneOldCrashFiles(const char* pattern)
        {
            constexpr size_t kKeptCrashFiles = 5;
            const std::string directory = g_DumpDirectory;
            if (directory.empty()) return;

            std::vector<std::string> names;
            WIN32_FIND_DATAA found = {};
            HANDLE search = FindFirstFileA((directory + pattern).c_str(), &found);
            if (search == INVALID_HANDLE_VALUE) return;
            do
            {
                if (!(found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    names.emplace_back(found.cFileName);
            } while (FindNextFileA(search, &found));
            FindClose(search);

            if (names.size() <= kKeptCrashFiles) return;
            std::sort(names.begin(), names.end());
            for (size_t index = 0; index + kKeptCrashFiles < names.size(); ++index)
                DeleteFileA((directory + "\\" + names[index]).c_str());
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

        // Nothing else removes old reports: a crash that repeats on every
        // launch would otherwise pile them up. Dumps are also pruned right
        // after each one is written.
        PruneOldCrashDumps(nullptr);
        PruneOldCrashFiles("\\openshim_crash_*.log");

        // Keep the report scoped to this process. The ordinary shim log and
        // support wrapper already preserve the previous launch; carrying this
        // file forward made old handled exceptions appear to belong to a new
        // Linux/Proton report.
        HANDLE freshLog = CreateFileA(g_CrashLogPath, GENERIC_WRITE,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (freshLog != INVALID_HANDLE_VALUE)
            CloseHandle(freshLog);

        g_CrashDumpDisabled = EnvDisabled("OPENSHIM_DISABLE_CRASH_DUMP");

        // From the system directory, not by bare name: the proxy's search-path
        // setup puts the game directory ahead of System32, where a stray
        // dbghelp.dll would load into the crash path.
        HMODULE dbghelp = nullptr;
        char dbghelpPath[MAX_PATH] = {};
        const UINT systemDirLength = GetSystemDirectoryA(dbghelpPath, MAX_PATH);
        if (systemDirLength > 0 && systemDirLength < MAX_PATH - 14)
        {
            lstrcatA(dbghelpPath, "\\dbghelp.dll");
            dbghelp = LoadLibraryA(dbghelpPath);
        }
        if (dbghelp)
            g_MiniDumpWriteDump = reinterpret_cast<FnMiniDumpWriteDump>(
                GetProcAddress(dbghelp, "MiniDumpWriteDump"));

        // Made before any handler that uses it, so a crash never has to
        // create a thread or an event.
        g_SoRequest = CreateEventA(nullptr, FALSE, FALSE, nullptr);
        g_SoDone = CreateEventA(nullptr, FALSE, FALSE, nullptr);
        g_LogRequest = CreateEventA(nullptr, FALSE, FALSE, nullptr);
        g_LogDone = CreateEventA(nullptr, TRUE, FALSE, nullptr);
        if (g_SoRequest && g_SoDone && g_LogRequest && g_LogDone)
            g_WatcherThread = CreateThread(nullptr, 0, WatcherThread, nullptr, 0, &g_WatcherThreadId);
        PVOID overflowHandle = nullptr;
        if (g_WatcherThread)
            overflowHandle = AddVectoredExceptionHandler(1, StackOverflowCatcher);

        g_PreviousFilter = SetUnhandledExceptionFilter(UnhandledFilter);
        // Resolved here so the first-chance handler takes no loader lock.
        g_SelfModule = ModuleOf(reinterpret_cast<uintptr_t>(&ModuleOf));
        g_ProxyModule = GetModuleHandleA("winmm.dll");
        if (!EnvDisabled("OPENSHIM_DISABLE_CRASH_VEH"))
            g_VectoredHandle = AddVectoredExceptionHandler(0, FirstChanceLogger);

        char gameCrt[96] = "off";
        const bool crtHandlers = !EnvDisabled("OPENSHIM_DISABLE_CRASH_CRT_HANDLERS");
        if (crtHandlers)
        {
            InstallGameCrtHandlers(gameCrt, sizeof(gameCrt));
            InstallShimCrtHandlers();
        }

        LogShimA(LogLevel::Info, "crash",
                 "Crash logger installed log=%s dump=%s minidumps=%s veh=%s stack-overflow=%s "
                 "crt(game)=%s crt(shim)=%s previousFilter=0x%p",
                 g_CrashLogPath,
                 g_MiniDumpWriteDump ? "available" : "unavailable",
                 g_CrashDumpDisabled ? "off" : "on (normal+threads, keep 3)",
                 g_VectoredHandle ? "on" : "off",
                 overflowHandle ? "on" : "off",
                 gameCrt,
                 crtHandlers ? "on" : "off",
                 reinterpret_cast<void*>(g_PreviousFilter));
    }

    void WriteCrashLogFailClosed(const char* component, const char* reason)
    {
        if (!g_CrashLogPath[0])
            return;
        if (InterlockedCompareExchange(&g_InHandler, 1, 0) != 0)
            return;
        static char buffer[1024];
        size_t offset = 0;
        AppendTimestamp(buffer, sizeof(buffer), offset);
        AppendString(buffer, sizeof(buffer), offset, " FAIL-CLOSED [");
        AppendString(buffer, sizeof(buffer), offset, component ? component : "?");
        AppendString(buffer, sizeof(buffer), offset, "]: ");
        AppendString(buffer, sizeof(buffer), offset, reason ? reason : "(no reason given)");
        AppendString(buffer, sizeof(buffer), offset, "\r\n");
        WriteToCrashLog(buffer, offset);
        if (g_DumpDirectory[0])
        {
            static char path[MAX_PATH];
            const size_t stemLength = BuildCrashStem(path, sizeof(path));
            if (stemLength + sizeof(".log") <= sizeof(path))
            {
                SetExtension(path, sizeof(path), stemLength, ".log");
                CopyCrashLog(path);
            }
        }
        InterlockedExchange(&g_InHandler, 0);
    }
}
