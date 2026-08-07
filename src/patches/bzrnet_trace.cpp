#include "bzrnet_trace.h"
#include "bzrnet_protocol.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <cstdio>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace BZROpenShim
{
namespace
{
    struct TraceRecord
    {
        uint64_t seq = 0;
        uint64_t tickMs = 0;
        int64_t qpc = 0;
        uint32_t threadId = 0;
        uint32_t socketId = 0;
        uint32_t socketGeneration = 0;
        std::string layer;
        std::string event;
        std::string direction;
        std::string messageType;
        std::string detailsJson;
    };

    BzrNetTraceConfig g_Config;
    volatile LONG g_Initialized = 0;
    volatile LONG g_Stop = 0;
    __declspec(align(8)) volatile LONG64 g_NextSeq = 0;
    __declspec(align(8)) volatile LONG64 g_DroppedTotal = 0;
    __declspec(align(8)) volatile LONG64 g_DroppedReported = 0;
    volatile LONG g_HighWater = 0;
    volatile LONG g_WriterShutdownClean = 0;

    SRWLOCK g_QueueLock = SRWLOCK_INIT;
    std::deque<TraceRecord> g_Queue;
    HANDLE g_WakeEvent = nullptr;
    HANDLE g_WriterThread = nullptr;
    FILE* g_TraceFile = nullptr;
    std::string g_TracePath;
    std::string g_SessionPath;
    std::string g_CaptureId;

    SRWLOCK g_SocketGenerationLock = SRWLOCK_INIT;
    std::unordered_map<uintptr_t, uint32_t> g_SocketGenerations;
    volatile LONG g_NextSocketGeneration = 0;

    LARGE_INTEGER g_QpcFrequency = {};
    LARGE_INTEGER g_StartQpc = {};
    uint64_t g_StartTickMs = 0;
    uint64_t g_StartFileTime = 0;
    uint64_t g_StopFileTime = 0;

    std::string JsonEscape(const std::string& input)
    {
        std::string out;
        out.reserve(input.size() + 8);
        for (const unsigned char c : input)
        {
            switch (c)
            {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\b': out += "\\b"; break;
                case '\f': out += "\\f"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default:
                    if (c < 0x20)
                    {
                        char escaped[7] = {};
                        _snprintf_s(escaped, _TRUNCATE, "\\u%04x", static_cast<unsigned>(c));
                        out += escaped;
                    }
                    else
                    {
                        out.push_back(static_cast<char>(c));
                    }
                    break;
            }
        }
        return out;
    }

    uint64_t FileTimeNow()
    {
        FILETIME ft = {};
        using PreciseFn = VOID (WINAPI*)(LPFILETIME);
        static PreciseFn precise = []() -> PreciseFn
        {
            HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
            return kernel32 ? reinterpret_cast<PreciseFn>(GetProcAddress(kernel32, "GetSystemTimePreciseAsFileTime")) : nullptr;
        }();
        if (precise)
            precise(&ft);
        else
            GetSystemTimeAsFileTime(&ft);
        ULARGE_INTEGER value = {};
        value.LowPart = ft.dwLowDateTime;
        value.HighPart = ft.dwHighDateTime;
        return value.QuadPart;
    }

    std::string GameDirectory()
    {
        char path[MAX_PATH] = {};
        const DWORD len = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
        if (len == 0 || len >= sizeof(path))
            return ".";
        std::string value(path, len);
        const size_t slash = value.find_last_of("\\/");
        return slash == std::string::npos ? "." : value.substr(0, slash);
    }

    std::string JoinPath(const std::string& a, const char* b)
    {
        if (a.empty()) return b ? std::string(b) : std::string();
        if (!b || !*b) return a;
        if (a.back() == '\\' || a.back() == '/') return a + b;
        return a + "\\" + b;
    }

    void WriteTraceRecord(const TraceRecord& record)
    {
        if (!g_TraceFile)
            return;
        const std::string layer = JsonEscape(record.layer);
        const std::string event = JsonEscape(record.event);
        const std::string direction = JsonEscape(record.direction);
        const std::string type = JsonEscape(record.messageType);
        const std::string& details = record.detailsJson.empty() ? std::string("{}") : record.detailsJson;
        std::fprintf(
            g_TraceFile,
            "{\"captureId\":\"%s\",\"processId\":%lu,\"seq\":%llu,\"tickMs\":%llu,\"qpc\":%lld,\"qpcFrequency\":%lld,\"threadId\":%u,\"layer\":\"%s\",\"event\":\"%s\",\"direction\":\"%s\",\"socketId\":%u,\"socketGeneration\":%u,\"messageType\":\"%s\",\"details\":%s}\n",
            g_CaptureId.c_str(),
            static_cast<unsigned long>(GetCurrentProcessId()),
            static_cast<unsigned long long>(record.seq),
            static_cast<unsigned long long>(record.tickMs),
            static_cast<long long>(record.qpc),
            static_cast<long long>(g_QpcFrequency.QuadPart),
            record.threadId,
            layer.c_str(),
            event.c_str(),
            direction.c_str(),
            record.socketId,
            record.socketGeneration,
            type.c_str(),
            details.c_str());
    }

    void WriteDroppedRecord(uint64_t total, uint64_t delta)
    {
        if (!g_TraceFile || delta == 0)
            return;
        LARGE_INTEGER qpc = {};
        QueryPerformanceCounter(&qpc);
        const uint64_t seq = static_cast<uint64_t>(InterlockedIncrement64(&g_NextSeq));
        std::fprintf(
            g_TraceFile,
            "{\"captureId\":\"%s\",\"processId\":%lu,\"seq\":%llu,\"tickMs\":%llu,\"qpc\":%lld,\"qpcFrequency\":%lld,\"threadId\":%lu,\"layer\":\"trace\",\"event\":\"TRACE_DROPPED_EVENTS\",\"direction\":\"internal\",\"socketId\":0,\"socketGeneration\":0,\"messageType\":\"\",\"details\":{\"droppedSinceLastReport\":%llu,\"droppedTotal\":%llu}}\n",
            g_CaptureId.c_str(),
            static_cast<unsigned long>(GetCurrentProcessId()),
            static_cast<unsigned long long>(seq),
            static_cast<unsigned long long>(GetTickCount64()),
            static_cast<long long>(qpc.QuadPart),
            static_cast<long long>(g_QpcFrequency.QuadPart),
            static_cast<unsigned long>(GetCurrentThreadId()),
            static_cast<unsigned long long>(delta),
            static_cast<unsigned long long>(total));
    }

    DWORD WINAPI WriterThreadProc(LPVOID)
    {
        std::vector<TraceRecord> batch;
        batch.reserve(128);
        for (;;)
        {
            if (g_WakeEvent)
                WaitForSingleObject(g_WakeEvent, g_Config.flushIntervalMs);

            batch.clear();
            AcquireSRWLockExclusive(&g_QueueLock);
            const size_t take = (std::min)(static_cast<size_t>(128), g_Queue.size());
            for (size_t i = 0; i < take; ++i)
            {
                batch.emplace_back(std::move(g_Queue.front()));
                g_Queue.pop_front();
            }
            const bool empty = g_Queue.empty();
            ReleaseSRWLockExclusive(&g_QueueLock);

            for (const auto& record : batch)
                WriteTraceRecord(record);

            const uint64_t dropped = static_cast<uint64_t>(InterlockedCompareExchange64(&g_DroppedTotal, 0, 0));
            const uint64_t reported = static_cast<uint64_t>(InterlockedCompareExchange64(&g_DroppedReported, 0, 0));
            if (dropped > reported)
            {
                WriteDroppedRecord(dropped, dropped - reported);
                InterlockedExchange64(&g_DroppedReported, static_cast<LONG64>(dropped));
            }

            if (g_TraceFile && (!batch.empty() || dropped > reported))
                std::fflush(g_TraceFile);

            const bool stopping = InterlockedCompareExchange(&g_Stop, 0, 0) != 0;
            if (stopping && empty)
                break;

            if (!empty && g_WakeEvent)
                SetEvent(g_WakeEvent);
        }
        if (g_TraceFile)
            std::fflush(g_TraceFile);
        InterlockedExchange(&g_WriterShutdownClean, 1);
        return 0;
    }

    void WriteSessionFile(bool finalState)
    {
        if (g_SessionPath.empty())
            return;
        FILE* file = nullptr;
        fopen_s(&file, g_SessionPath.c_str(), "wb");
        if (!file)
            return;
        const uint64_t endTime = finalState ? g_StopFileTime : 0;
        std::fprintf(file,
            "{\n"
            "  \"captureFormatVersion\": 1,\n"
            "  \"captureId\": \"%s\",\n"
            "  \"processId\": %lu,\n"
            "  \"privateForensic\": %s,\n"
            "  \"captureStartFileTimeUtc\": %llu,\n"
            "  \"captureEndFileTimeUtc\": %s,\n"
            "  \"clockCalibration\": {\"qpc\": %lld, \"qpcFrequency\": %lld, \"tickMs\": %llu, \"fileTimeUtc\": %llu},\n"
            "  \"traceQueueCapacity\": %u,\n"
            "  \"traceQueueHighWater\": %ld,\n"
            "  \"droppedEvents\": %lld,\n"
            "  \"writerShutdownClean\": %s,\n"
            "  \"exeSha256\": null,\n"
            "  \"hookSummary\": []\n"
            "}\n",
            g_CaptureId.c_str(),
            static_cast<unsigned long>(GetCurrentProcessId()),
            g_Config.privateForensic ? "true" : "false",
            static_cast<unsigned long long>(g_StartFileTime),
            finalState ? std::to_string(endTime).c_str() : "null",
            static_cast<long long>(g_StartQpc.QuadPart),
            static_cast<long long>(g_QpcFrequency.QuadPart),
            static_cast<unsigned long long>(g_StartTickMs),
            static_cast<unsigned long long>(g_StartFileTime),
            g_Config.queueCapacity,
            static_cast<long>(InterlockedCompareExchange(&g_HighWater, 0, 0)),
            static_cast<long long>(InterlockedCompareExchange64(&g_DroppedTotal, 0, 0)),
            InterlockedCompareExchange(&g_WriterShutdownClean, 0, 0) ? "true" : "false");
        std::fclose(file);
    }
}

bool InitializeBzrNetTrace(const BzrNetTraceConfig& config)
{
    if (!config.enabled)
        return false;
    if (InterlockedCompareExchange(&g_Initialized, 1, 0) != 0)
        return true;

    g_Config = config;
    InterlockedExchange64(&g_NextSeq, 0);
    InterlockedExchange64(&g_DroppedTotal, 0);
    InterlockedExchange64(&g_DroppedReported, 0);
    InterlockedExchange(&g_HighWater, 0);
    g_StopFileTime = 0;
    AcquireSRWLockExclusive(&g_QueueLock);
    g_Queue.clear();
    ReleaseSRWLockExclusive(&g_QueueLock);
    AcquireSRWLockExclusive(&g_SocketGenerationLock);
    g_SocketGenerations.clear();
    ReleaseSRWLockExclusive(&g_SocketGenerationLock);
    InterlockedExchange(&g_NextSocketGeneration, 0);
    g_Config.queueCapacity = (std::max)(256u, (std::min)(g_Config.queueCapacity, 65536u));
    g_Config.flushIntervalMs = (std::max)(50u, (std::min)(g_Config.flushIntervalMs, 5000u));
    QueryPerformanceFrequency(&g_QpcFrequency);
    QueryPerformanceCounter(&g_StartQpc);
    g_StartTickMs = GetTickCount64();
    g_StartFileTime = FileTimeNow();
    ResetBzrNetSanitizationAliases();

    char capture[128] = {};
    _snprintf_s(capture, _TRUNCATE, "bzr-%lu-%016llx-%016llx",
        static_cast<unsigned long>(GetCurrentProcessId()),
        static_cast<unsigned long long>(g_StartFileTime),
        static_cast<unsigned long long>(g_StartQpc.QuadPart));
    g_CaptureId = capture;

    const std::string logs = JoinPath(GameDirectory(), "logs");
    CreateDirectoryA(logs.c_str(), nullptr);
    g_TracePath = JoinPath(logs, "bzrnet_trace.jsonl");
    g_SessionPath = JoinPath(logs, "bzrnet_session.json");
    fopen_s(&g_TraceFile, g_TracePath.c_str(), "wb");
    if (!g_TraceFile)
    {
        InterlockedExchange(&g_Initialized, 0);
        LogShimA(LogLevel::Error, "bzrnet", "[BZRNetTrace] failed to open %s", g_TracePath.c_str());
        return false;
    }

    g_WakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_WakeEvent)
    {
        std::fclose(g_TraceFile);
        g_TraceFile = nullptr;
        InterlockedExchange(&g_Initialized, 0);
        LogShimA(LogLevel::Error, "bzrnet", "[BZRNetTrace] failed to create writer event err=%lu", GetLastError());
        return false;
    }

    InterlockedExchange(&g_Stop, 0);
    InterlockedExchange(&g_WriterShutdownClean, 0);
    g_WriterThread = CreateThread(nullptr, 0, WriterThreadProc, nullptr, 0, nullptr);
    if (!g_WriterThread)
    {
        CloseHandle(g_WakeEvent);
        g_WakeEvent = nullptr;
        std::fclose(g_TraceFile);
        g_TraceFile = nullptr;
        InterlockedExchange(&g_Initialized, 0);
        LogShimA(LogLevel::Error, "bzrnet", "[BZRNetTrace] failed to start writer thread err=%lu", GetLastError());
        return false;
    }

    WriteSessionFile(false);
    LogShimA(LogLevel::Info, "bzrnet", "[BZRNetTrace] enabled captureId=%s private=%d queue=%u trace=%s",
        g_CaptureId.c_str(), g_Config.privateForensic ? 1 : 0, g_Config.queueCapacity, g_TracePath.c_str());
    return true;
}

void ShutdownBzrNetTrace()
{
    if (InterlockedCompareExchange(&g_Initialized, 0, 0) == 0)
        return;

    InterlockedExchange(&g_Stop, 1);
    if (g_WakeEvent)
        SetEvent(g_WakeEvent);
    if (g_WriterThread)
    {
        const DWORD wait = WaitForSingleObject(g_WriterThread, 5000);
        if (wait == WAIT_OBJECT_0)
        {
            CloseHandle(g_WriterThread);
            g_WriterThread = nullptr;
        }
        else
        {
            LogShimA(LogLevel::Warn, "bzrnet", "[BZRNetTrace] writer did not stop cleanly wait=%lu", wait);
        }
    }

    g_StopFileTime = FileTimeNow();
    WriteSessionFile(true);
    if (g_TraceFile && InterlockedCompareExchange(&g_WriterShutdownClean, 0, 0))
    {
        std::fclose(g_TraceFile);
        g_TraceFile = nullptr;
    }
    if (g_WakeEvent)
    {
        CloseHandle(g_WakeEvent);
        g_WakeEvent = nullptr;
    }
    AcquireSRWLockExclusive(&g_SocketGenerationLock);
    g_SocketGenerations.clear();
    ReleaseSRWLockExclusive(&g_SocketGenerationLock);
    ResetBzrNetSanitizationAliases();
    InterlockedExchange(&g_Initialized, 0);
}

bool IsBzrNetTraceEnabled()
{
    return InterlockedCompareExchange(&g_Initialized, 0, 0) != 0 && g_Config.enabled;
}

bool IsBzrNetPrivateForensicTrace()
{
    return g_Config.privateForensic;
}

const std::string& GetBzrNetCaptureId()
{
    return g_CaptureId;
}

uint32_t BzrNetTraceRememberSocket(uintptr_t socketHandle)
{
    if (!IsBzrNetTraceEnabled() || socketHandle == static_cast<uintptr_t>(-1))
        return 0;
    AcquireSRWLockExclusive(&g_SocketGenerationLock);
    const auto it = g_SocketGenerations.find(socketHandle);
    if (it != g_SocketGenerations.end())
    {
        const uint32_t existing = it->second;
        ReleaseSRWLockExclusive(&g_SocketGenerationLock);
        return existing;
    }
    const uint32_t generation = static_cast<uint32_t>(InterlockedIncrement(&g_NextSocketGeneration));
    g_SocketGenerations.emplace(socketHandle, generation);
    ReleaseSRWLockExclusive(&g_SocketGenerationLock);
    return generation;
}

uint32_t BzrNetTraceSocketGeneration(uintptr_t socketHandle)
{
    if (!IsBzrNetTraceEnabled())
        return 0;
    AcquireSRWLockShared(&g_SocketGenerationLock);
    const auto it = g_SocketGenerations.find(socketHandle);
    const uint32_t generation = it == g_SocketGenerations.end() ? 0 : it->second;
    ReleaseSRWLockShared(&g_SocketGenerationLock);
    return generation;
}

void BzrNetTraceForgetSocket(uintptr_t socketHandle)
{
    if (!IsBzrNetTraceEnabled())
        return;
    AcquireSRWLockExclusive(&g_SocketGenerationLock);
    g_SocketGenerations.erase(socketHandle);
    ReleaseSRWLockExclusive(&g_SocketGenerationLock);
}

void EmitBzrNetTrace(
    const char* layer,
    const char* event,
    const char* direction,
    uint32_t socketId,
    uint32_t socketGeneration,
    const char* messageType,
    const std::string& detailsJson)
{
    if (!IsBzrNetTraceEnabled())
        return;

    TraceRecord record;
    record.seq = static_cast<uint64_t>(InterlockedIncrement64(&g_NextSeq));
    record.tickMs = GetTickCount64();
    LARGE_INTEGER qpc = {};
    QueryPerformanceCounter(&qpc);
    record.qpc = qpc.QuadPart;
    record.threadId = GetCurrentThreadId();
    record.socketId = socketId;
    record.socketGeneration = socketGeneration;
    record.layer = layer ? layer : "unknown";
    record.event = event ? event : "unknown";
    record.direction = direction ? direction : "unknown";
    record.messageType = messageType ? messageType : "";
    record.detailsJson = detailsJson.empty() ? "{}" : detailsJson;

    bool queued = false;
    AcquireSRWLockExclusive(&g_QueueLock);
    if (g_Queue.size() < g_Config.queueCapacity)
    {
        g_Queue.emplace_back(std::move(record));
        const LONG depth = static_cast<LONG>(g_Queue.size());
        LONG high = InterlockedCompareExchange(&g_HighWater, 0, 0);
        while (depth > high)
        {
            const LONG prior = InterlockedCompareExchange(&g_HighWater, depth, high);
            if (prior == high) break;
            high = prior;
        }
        queued = true;
    }
    ReleaseSRWLockExclusive(&g_QueueLock);

    if (!queued)
        InterlockedIncrement64(&g_DroppedTotal);
    else if (g_WakeEvent)
        SetEvent(g_WakeEvent);
}
}
