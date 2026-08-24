// native_cpu_sampler.cpp
// BZR Open Shim - process-wide sampling CPU profiler (diagnostic only)
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Why sampling rather than instrumentation
// ----------------------------------------
// Phase 1 established that roughly 86% of a large-battle frame is neither Ogre
// submission nor GPU execution, and it did so with instrumented hooks. Two of
// those hooks failed silently during that phase -- an isolation arm whose
// detours were never installed, and a DX11 draw observer that was reverted
// mid-frame -- and in both cases the failure produced a plausible-looking
// number rather than an error. Placing timers on native functions whose call
// hierarchy is not yet known would repeat that pattern at a much larger scale:
// a category that reads 0.00 ms because its hook never fired is
// indistinguishable from a category that is genuinely cheap.
//
// A sampler inverts the failure mode. It has no per-function hooks to lose, it
// attributes 100% of the observed CPU time by construction (there is no
// "unattributed" bucket that instrumentation forgot to cover), and its own
// health is a single number -- samples actually taken versus samples the clock
// asked for -- that is reported alongside every capture.
//
// Safety rules for the suspend window
// -----------------------------------
// Between SuspendThread and ResumeThread this code must not take any lock the
// suspended thread could already hold, or the process deadlocks. Inside that
// window it therefore performs no allocation, no CRT call, no logging, and no
// VirtualQuery: it reads the thread context, walks the frame-pointer chain out
// of a preallocated buffer, and resumes. Module ranges and stack bounds used by
// the walk are computed outside the window and cached.
//
// The frame walk only reads at addresses at or above ESP. The pages below ESP
// hold the stack guard page, and touching a guard page from another thread
// would clear the guard bit without growing the stack properly, so "at or above
// ESP" is a correctness requirement here rather than a plausibility check.

#include "native_cpu_sampler.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <TlHelp32.h>
#include <process.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "cpu-sampler";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_PROFILE_NATIVE_CPU";
        constexpr char kEnvironmentHz[] = "OPENSHIM_PROFILE_NATIVE_CPU_HZ";
        constexpr char kEnvironmentDepth[] = "OPENSHIM_PROFILE_NATIVE_CPU_DEPTH";
        constexpr char kEnvironmentDelay[] = "OPENSHIM_PROFILE_NATIVE_CPU_DELAY";
        constexpr char kEnvironmentDuration[] = "OPENSHIM_PROFILE_NATIVE_CPU_DURATION";
        constexpr char kEnvironmentLabel[] = "OPENSHIM_PROFILE_NATIVE_CPU_LABEL";

        constexpr uint32_t kDefaultHz = 1000;
        constexpr uint32_t kMinHz = 50;
        constexpr uint32_t kMaxHz = 4000;
        // A truncated walk loses the root, not the leaf, so a depth that is too
        // small destroys exactly the frame hierarchy this phase is trying to
        // reconstruct. The first calibration run capped 44% of stacks at 24.
        constexpr uint32_t kDefaultDepth = 48;
        constexpr uint32_t kMaxDepth = 64;
        // Threads below this share of one core over an enumeration pass are
        // tracked for CPU time but not stack-sampled. Suspending a thread that
        // is parked in a wait costs the same as suspending a busy one, and a
        // large battle keeps a dozen mostly-idle threads alive.
        constexpr uint64_t kSampleThresholdPercent = 2;
        constexpr DWORD kEnumerateIntervalMs = 1000;
        constexpr DWORD kReportIntervalMs = 5000;
        constexpr size_t kFlushThresholdBytes = 512u * 1024u;
        constexpr size_t kBufferReserveBytes = 1024u * 1024u;
        constexpr uint32_t kMaxModules = 128;
        // Redux keeps well over a hundred threads alive in a battle mission.
        // The first calibration run pinned a 128 cap, which would have silently
        // excluded any thread that became busy after the cap was reached.
        constexpr uint32_t kMaxThreads = 512;
        // The frame walk never reads further above ESP than this. A Redux
        // thread stack is 1 MB by default; the cap only has to be generous
        // enough that a legitimate chain is never truncated by it.
        constexpr uint32_t kStackWindowBytes = 4u * 1024u * 1024u;

        constexpr uint32_t kTagModule = 0x4C444F4Du;   // 'MODL'
        constexpr uint32_t kTagThread = 0x44524854u;   // 'THRD'
        constexpr uint32_t kTagSampleBlock = 0x4B4C4253u; // 'SBLK'
        constexpr uint32_t kTagStats = 0x54415453u;    // 'STAT'
        constexpr uint32_t kTagEnd = 0x53444E45u;      // 'ENDS'

        constexpr uint8_t kFlagDepthCapped = 1u << 0;
        constexpr uint8_t kFlagLeafOutsideModules = 1u << 1;
        constexpr uint8_t kFlagWalkRejected = 1u << 2;

        struct ModuleRange
        {
            uintptr_t base;
            uintptr_t end;
        };

        struct ThreadEntry
        {
            DWORD tid;
            HANDLE handle;
            uint64_t creationFileTime;
            uint64_t lastCpu100ns;
            uint64_t totalCpu100ns;
            uint64_t deltaCpu100ns;
            uint64_t samples;
            uint32_t suspendFailures;
            uint32_t contextFailures;
            bool sampled;
            bool announced;
        };

        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_Running{ false };
        HANDLE g_WorkerThread = nullptr;
        HANDLE g_WakeEvent = nullptr;

        uint32_t g_RequestedHz = kDefaultHz;
        uint32_t g_RequestedDepth = kDefaultDepth;
        uint32_t g_DelaySeconds = 0;
        uint32_t g_DurationSeconds = 0;

        // Read by the sampler thread only; published before sampling starts.
        ModuleRange g_Modules[kMaxModules];
        std::atomic<uint32_t> g_ModuleCount{ 0 };

        // Health counters. Every one of these is reported so that a capture
        // which failed to observe anything cannot be mistaken for a capture
        // which observed that nothing was happening.
        uint64_t g_TicksRequested = 0;
        uint64_t g_TicksServiced = 0;
        uint64_t g_SamplesTaken = 0;
        uint64_t g_SuspendFailures = 0;
        uint64_t g_ContextFailures = 0;
        uint64_t g_FramesRecorded = 0;
        uint64_t g_LeafOutsideModules = 0;
        uint64_t g_DepthCapped = 0;
        uint64_t g_BytesWritten = 0;
        uint64_t g_SuspendQpcTotal = 0;

        HANDLE g_OutputFile = INVALID_HANDLE_VALUE;
        std::vector<uint8_t> g_Buffer;
        std::string g_OutputPath;

        uint64_t ReadQpc() noexcept
        {
            LARGE_INTEGER value;
            QueryPerformanceCounter(&value);
            return static_cast<uint64_t>(value.QuadPart);
        }

        uint64_t QpcFrequency() noexcept
        {
            static uint64_t frequency = []() -> uint64_t {
                LARGE_INTEGER value;
                QueryPerformanceFrequency(&value);
                return static_cast<uint64_t>(value.QuadPart);
            }();
            return frequency;
        }

        bool ReadEnvironmentValue(const char* name, std::string& out)
        {
            char buffer[256] = {};
            const DWORD length = GetEnvironmentVariableA(name, buffer, sizeof(buffer));
            if (length == 0 || length >= sizeof(buffer))
            {
                return false;
            }
            out.assign(buffer, length);
            return true;
        }

        uint32_t ReadEnvironmentUnsigned(const char* name, uint32_t fallback)
        {
            std::string text;
            if (!ReadEnvironmentValue(name, text))
            {
                return fallback;
            }
            char* end = nullptr;
            const unsigned long parsed = std::strtoul(text.c_str(), &end, 10);
            if (end == text.c_str())
            {
                return fallback;
            }
            return static_cast<uint32_t>(parsed);
        }

        bool IsTruthy(const std::string& text)
        {
            if (text.empty())
            {
                return false;
            }
            if (text == "0" || text == "false" || text == "FALSE" || text == "off")
            {
                return false;
            }
            return true;
        }

        // ---------------------------------------------------------------
        // Output buffer. All writes happen on the sampler thread outside any
        // suspend window.
        // ---------------------------------------------------------------
        void BufferAppend(const void* data, size_t bytes)
        {
            const uint8_t* const start = static_cast<const uint8_t*>(data);
            g_Buffer.insert(g_Buffer.end(), start, start + bytes);
        }

        template <typename T>
        void BufferAppendValue(const T& value)
        {
            BufferAppend(&value, sizeof(T));
        }

        void FlushBuffer(bool force)
        {
            if (g_OutputFile == INVALID_HANDLE_VALUE)
            {
                g_Buffer.clear();
                return;
            }
            if (!force && g_Buffer.size() < kFlushThresholdBytes)
            {
                return;
            }
            if (g_Buffer.empty())
            {
                return;
            }
            DWORD written = 0;
            if (WriteFile(g_OutputFile,
                          g_Buffer.data(),
                          static_cast<DWORD>(g_Buffer.size()),
                          &written,
                          nullptr))
            {
                g_BytesWritten += written;
            }
            g_Buffer.clear();
        }

        void BeginChunk(uint32_t tag, uint32_t payloadBytes)
        {
            BufferAppendValue(tag);
            BufferAppendValue(payloadBytes);
        }

        // ---------------------------------------------------------------
        // Module ranges
        // ---------------------------------------------------------------
        void RefreshModules()
        {
            const HANDLE snapshot = CreateToolhelp32Snapshot(
                TH32CS_SNAPMODULE, GetCurrentProcessId());
            if (snapshot == INVALID_HANDLE_VALUE)
            {
                return;
            }
            MODULEENTRY32 entry{};
            entry.dwSize = sizeof(entry);
            uint32_t count = 0;
            if (Module32First(snapshot, &entry))
            {
                do
                {
                    if (count >= kMaxModules)
                    {
                        break;
                    }
                    const uintptr_t base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                    g_Modules[count].base = base;
                    g_Modules[count].end = base + entry.modBaseSize;

                    // Module identity is recorded once per capture. Offline
                    // attribution needs the base to turn a sampled address into
                    // a module-relative RVA, and the full path so it can read
                    // the module's export table for near-symbol naming. Two
                    // loaded modules share the name "WINMM.dll" here -- the
                    // shim and the system library -- so the name alone is not
                    // an identity.
                    std::string name(entry.szExePath);
                    if (name.empty())
                    {
                        name.assign(entry.szModule);
                    }
                    const uint16_t nameBytes = static_cast<uint16_t>(
                        std::min<size_t>(name.size(), 511));
                    BeginChunk(kTagModule,
                               static_cast<uint32_t>(8 + 8 + 2 + nameBytes));
                    BufferAppendValue(static_cast<uint64_t>(base));
                    BufferAppendValue(static_cast<uint64_t>(entry.modBaseSize));
                    BufferAppendValue(nameBytes);
                    BufferAppend(name.data(), nameBytes);
                    ++count;
                } while (Module32Next(snapshot, &entry));
            }
            CloseHandle(snapshot);
            if (count != 0)
            {
                g_ModuleCount.store(count, std::memory_order_release);
            }
        }

        // Suspend-window safe: reads only the cached range table.
        bool IsInKnownModule(uintptr_t address) noexcept
        {
            const uint32_t count = g_ModuleCount.load(std::memory_order_relaxed);
            for (uint32_t index = 0; index < count; ++index)
            {
                if (address >= g_Modules[index].base && address < g_Modules[index].end)
                {
                    return true;
                }
            }
            return false;
        }

        // ---------------------------------------------------------------
        // Frame-pointer walk
        //
        // Isolated in its own function because SEH cannot coexist with objects
        // that require unwinding, and because everything it touches has to be
        // safe to touch while another thread of this process is suspended.
        // ---------------------------------------------------------------
#pragma warning(push)
#pragma warning(disable : 4509) // SEH used in a function with no unwind objects.
        bool ReadStackSlot(uintptr_t address, uint32_t& outValue) noexcept
        {
            __try
            {
                outValue = *reinterpret_cast<const volatile uint32_t*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
#pragma warning(pop)

        uint32_t WalkFrames(const CONTEXT& context,
                            uint32_t* addresses,
                            uint32_t maxDepth,
                            uint8_t& outFlags) noexcept
        {
            outFlags = 0;
            uint32_t depth = 0;
            addresses[depth++] = context.Eip;
            if (!IsInKnownModule(context.Eip))
            {
                outFlags |= kFlagLeafOutsideModules;
            }

            const uintptr_t stackLow = context.Esp;
            const uintptr_t stackHigh = stackLow + kStackWindowBytes;
            uintptr_t frame = context.Ebp;
            uintptr_t previousFrame = 0;

            while (depth < maxDepth)
            {
                if (frame < stackLow || frame + 8 > stackHigh ||
                    (frame & 3u) != 0 || frame <= previousFrame)
                {
                    outFlags |= kFlagWalkRejected;
                    break;
                }
                uint32_t nextFrame = 0;
                uint32_t returnAddress = 0;
                if (!ReadStackSlot(frame, nextFrame) ||
                    !ReadStackSlot(frame + 4, returnAddress))
                {
                    outFlags |= kFlagWalkRejected;
                    break;
                }
                if (!IsInKnownModule(returnAddress))
                {
                    outFlags |= kFlagWalkRejected;
                    break;
                }
                addresses[depth++] = returnAddress;
                previousFrame = frame;
                frame = nextFrame;
            }
            if (depth >= maxDepth)
            {
                outFlags |= kFlagDepthCapped;
            }
            return depth;
        }

        // ---------------------------------------------------------------
        // Thread tracking
        // ---------------------------------------------------------------
        uint64_t FileTimeToU64(const FILETIME& value) noexcept
        {
            ULARGE_INTEGER converted;
            converted.LowPart = value.dwLowDateTime;
            converted.HighPart = value.dwHighDateTime;
            return converted.QuadPart;
        }

        void CloseThreads(std::vector<ThreadEntry>& threads)
        {
            for (ThreadEntry& entry : threads)
            {
                if (entry.handle)
                {
                    CloseHandle(entry.handle);
                    entry.handle = nullptr;
                }
            }
            threads.clear();
        }

        void RefreshThreads(std::vector<ThreadEntry>& threads,
                            DWORD selfThreadId,
                            uint64_t passIntervalNs100)
        {
            const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
            if (snapshot == INVALID_HANDLE_VALUE)
            {
                return;
            }
            const DWORD processId = GetCurrentProcessId();
            std::vector<DWORD> live;
            THREADENTRY32 entry{};
            entry.dwSize = sizeof(entry);
            if (Thread32First(snapshot, &entry))
            {
                do
                {
                    if (entry.th32OwnerProcessID != processId ||
                        entry.th32ThreadID == selfThreadId)
                    {
                        continue;
                    }
                    live.push_back(entry.th32ThreadID);
                    const bool known = std::any_of(
                        threads.begin(), threads.end(),
                        [&](const ThreadEntry& tracked) {
                            return tracked.tid == entry.th32ThreadID;
                        });
                    if (known || threads.size() >= kMaxThreads)
                    {
                        continue;
                    }
                    const HANDLE handle = OpenThread(
                        THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT |
                            THREAD_QUERY_INFORMATION,
                        FALSE,
                        entry.th32ThreadID);
                    if (!handle)
                    {
                        continue;
                    }
                    ThreadEntry tracked{};
                    tracked.tid = entry.th32ThreadID;
                    tracked.handle = handle;
                    FILETIME creation{}, exitTime{}, kernel{}, user{};
                    if (GetThreadTimes(handle, &creation, &exitTime, &kernel, &user))
                    {
                        tracked.creationFileTime = FileTimeToU64(creation);
                        tracked.lastCpu100ns =
                            FileTimeToU64(kernel) + FileTimeToU64(user);
                    }
                    threads.push_back(tracked);
                } while (Thread32Next(snapshot, &entry));
            }
            CloseHandle(snapshot);

            // Drop threads that have exited so their handles do not accumulate
            // over a long capture.
            for (size_t index = threads.size(); index-- > 0;)
            {
                const bool stillLive = std::find(live.begin(), live.end(),
                                                 threads[index].tid) != live.end();
                if (stillLive)
                {
                    continue;
                }
                if (threads[index].handle)
                {
                    CloseHandle(threads[index].handle);
                }
                threads.erase(threads.begin() + static_cast<ptrdiff_t>(index));
            }

            const uint64_t nowQpc = ReadQpc();
            for (ThreadEntry& tracked : threads)
            {
                FILETIME creation{}, exitTime{}, kernel{}, user{};
                if (!GetThreadTimes(tracked.handle, &creation, &exitTime, &kernel, &user))
                {
                    continue;
                }
                const uint64_t total = FileTimeToU64(kernel) + FileTimeToU64(user);
                tracked.deltaCpu100ns =
                    total > tracked.lastCpu100ns ? total - tracked.lastCpu100ns : 0;
                tracked.lastCpu100ns = total;
                tracked.totalCpu100ns = total;
                // A thread earns stack sampling by having consumed CPU in the
                // previous pass. Every thread keeps its CPU total recorded
                // either way, so "the work is on another thread" remains
                // answerable without sampling every parked worker.
                tracked.sampled = passIntervalNs100 != 0 &&
                    (tracked.deltaCpu100ns * 100u) >=
                        (passIntervalNs100 * kSampleThresholdPercent);

                const uint32_t payload =
                    4 + 8 + 8 + 8 + 8 + 1 + 3;
                BeginChunk(kTagThread, payload);
                BufferAppendValue(static_cast<uint32_t>(tracked.tid));
                BufferAppendValue(tracked.creationFileTime);
                BufferAppendValue(tracked.totalCpu100ns);
                BufferAppendValue(tracked.deltaCpu100ns);
                BufferAppendValue(nowQpc);
                BufferAppendValue(static_cast<uint8_t>(tracked.sampled ? 1 : 0));
                const uint8_t padding[3] = { 0, 0, 0 };
                BufferAppend(padding, sizeof(padding));
                tracked.announced = true;
            }
        }

        // ---------------------------------------------------------------
        // One sampling tick
        // ---------------------------------------------------------------
        void SampleThread(ThreadEntry& tracked,
                          uint32_t depthLimit,
                          std::vector<uint8_t>& sampleScratch)
        {
            if (SuspendThread(tracked.handle) == static_cast<DWORD>(-1))
            {
                ++tracked.suspendFailures;
                ++g_SuspendFailures;
                return;
            }

            CONTEXT context{};
            context.ContextFlags = CONTEXT_CONTROL;
            uint32_t addresses[kMaxDepth] = {};
            uint32_t depth = 0;
            uint8_t flags = 0;
            const uint64_t suspendStart = ReadQpc();
            if (GetThreadContext(tracked.handle, &context))
            {
                depth = WalkFrames(context, addresses, depthLimit, flags);
            }
            else
            {
                ++tracked.contextFailures;
                ++g_ContextFailures;
            }
            const uint64_t suspendEnd = ReadQpc();
            ResumeThread(tracked.handle);

            if (depth == 0)
            {
                return;
            }
            g_SuspendQpcTotal += suspendEnd - suspendStart;
            ++tracked.samples;
            ++g_SamplesTaken;
            g_FramesRecorded += depth;
            if ((flags & kFlagLeafOutsideModules) != 0)
            {
                ++g_LeafOutsideModules;
            }
            if ((flags & kFlagDepthCapped) != 0)
            {
                ++g_DepthCapped;
            }

            const uint32_t tid = tracked.tid;
            const uint64_t qpc = suspendStart;
            const uint8_t depthByte = static_cast<uint8_t>(depth);
            const uint16_t reserved = 0;
            const size_t offset = sampleScratch.size();
            sampleScratch.resize(offset + 16 + depth * 4u);
            uint8_t* cursor = sampleScratch.data() + offset;
            std::memcpy(cursor, &tid, 4); cursor += 4;
            std::memcpy(cursor, &qpc, 8); cursor += 8;
            std::memcpy(cursor, &depthByte, 1); cursor += 1;
            std::memcpy(cursor, &flags, 1); cursor += 1;
            std::memcpy(cursor, &reserved, 2); cursor += 2;
            std::memcpy(cursor, addresses, depth * 4u);
        }

        void WriteStats(uint64_t elapsedQpc)
        {
            const uint32_t payload = 8 * 10;
            BeginChunk(kTagStats, payload);
            BufferAppendValue(elapsedQpc);
            BufferAppendValue(g_TicksRequested);
            BufferAppendValue(g_TicksServiced);
            BufferAppendValue(g_SamplesTaken);
            BufferAppendValue(g_FramesRecorded);
            BufferAppendValue(g_SuspendFailures);
            BufferAppendValue(g_ContextFailures);
            BufferAppendValue(g_LeafOutsideModules);
            BufferAppendValue(g_DepthCapped);
            BufferAppendValue(g_SuspendQpcTotal);
        }

        void ReportHealth(uint64_t elapsedQpc, const std::vector<ThreadEntry>& threads)
        {
            const uint64_t frequency = QpcFrequency();
            const double elapsedSeconds =
                frequency != 0 ? static_cast<double>(elapsedQpc) / static_cast<double>(frequency)
                               : 0.0;
            const double achievedHz =
                elapsedSeconds > 0.0 ? static_cast<double>(g_TicksServiced) / elapsedSeconds : 0.0;
            const double suspendMs =
                frequency != 0
                    ? (static_cast<double>(g_SuspendQpcTotal) * 1000.0) / static_cast<double>(frequency)
                    : 0.0;
            const double overheadPercent =
                elapsedSeconds > 0.0 ? (suspendMs / (elapsedSeconds * 1000.0)) * 100.0 : 0.0;

            size_t sampledThreads = 0;
            for (const ThreadEntry& tracked : threads)
            {
                if (tracked.sampled)
                {
                    ++sampledThreads;
                }
            }

            LogShimA(LogLevel::Info,
                     kComponent,
                     "[Health] elapsed=%.1fs ticksRequested=%llu ticksServiced=%llu "
                     "achievedHz=%.1f requestedHz=%u samples=%llu frames=%llu "
                     "threadsTracked=%zu threadsSampled=%zu suspendFailures=%llu "
                     "contextFailures=%llu leafOutsideModules=%llu depthCapped=%llu "
                     "suspendWindowMs=%.1f suspendOverheadPercent=%.2f bytesWritten=%llu",
                     elapsedSeconds,
                     static_cast<unsigned long long>(g_TicksRequested),
                     static_cast<unsigned long long>(g_TicksServiced),
                     achievedHz,
                     g_RequestedHz,
                     static_cast<unsigned long long>(g_SamplesTaken),
                     static_cast<unsigned long long>(g_FramesRecorded),
                     threads.size(),
                     sampledThreads,
                     static_cast<unsigned long long>(g_SuspendFailures),
                     static_cast<unsigned long long>(g_ContextFailures),
                     static_cast<unsigned long long>(g_LeafOutsideModules),
                     static_cast<unsigned long long>(g_DepthCapped),
                     suspendMs,
                     overheadPercent,
                     static_cast<unsigned long long>(g_BytesWritten));

            for (const ThreadEntry& tracked : threads)
            {
                if (tracked.samples == 0 && tracked.deltaCpu100ns == 0)
                {
                    continue;
                }
                LogShimA(LogLevel::Info,
                         kComponent,
                         "[Thread] tid=%lu sampled=%d samples=%llu cpuTotalMs=%.1f "
                         "cpuLastPassMs=%.2f suspendFailures=%u contextFailures=%u",
                         tracked.tid,
                         tracked.sampled ? 1 : 0,
                         static_cast<unsigned long long>(tracked.samples),
                         static_cast<double>(tracked.totalCpu100ns) / 10000.0,
                         static_cast<double>(tracked.deltaCpu100ns) / 10000.0,
                         tracked.suspendFailures,
                         tracked.contextFailures);
            }
        }

        bool OpenOutputFile()
        {
            std::string label;
            if (!ReadEnvironmentValue(kEnvironmentLabel, label) || label.empty())
            {
                label = "run";
            }
            for (char& character : label)
            {
                if (!((character >= '0' && character <= '9') ||
                      (character >= 'a' && character <= 'z') ||
                      (character >= 'A' && character <= 'Z') ||
                      character == '-' || character == '_'))
                {
                    character = '_';
                }
            }
            char fileName[192] = {};
            _snprintf_s(fileName, sizeof(fileName), _TRUNCATE,
                        "openshim_cpu_samples_%s_%lu.bin",
                        label.c_str(),
                        GetCurrentProcessId());
            g_OutputPath = GetGameLogPath(fileName);
            g_OutputFile = CreateFileA(g_OutputPath.c_str(),
                                       GENERIC_WRITE,
                                       FILE_SHARE_READ,
                                       nullptr,
                                       CREATE_ALWAYS,
                                       FILE_ATTRIBUTE_NORMAL,
                                       nullptr);
            if (g_OutputFile == INVALID_HANDLE_VALUE)
            {
                LogShimA(LogLevel::Error, kComponent,
                         "Cannot create sample file '%s' (error %lu); sampler will not start",
                         g_OutputPath.c_str(), GetLastError());
                return false;
            }

            uint8_t header[64] = {};
            std::memcpy(header, "OSCPUSM1", 8);
            const uint32_t headerSize = 64;
            const uint32_t pointerBits = 32;
            const uint64_t frequency = QpcFrequency();
            const uint64_t startQpc = ReadQpc();
            FILETIME now{};
            GetSystemTimeAsFileTime(&now);
            const uint64_t startFileTime = FileTimeToU64(now);
            // BZLogger stamps its benchmark markers in local time, and the
            // measurement window is selected offline by matching those markers.
            // Recording the local-time start here removes any need for the
            // analysis to guess this machine's UTC offset.
            SYSTEMTIME localNow{};
            GetLocalTime(&localNow);
            FILETIME localFileTime{};
            SystemTimeToFileTime(&localNow, &localFileTime);
            const uint64_t startLocalFileTime = FileTimeToU64(localFileTime);
            const uint32_t processId = GetCurrentProcessId();
            const uint32_t reserved = 0;
            size_t offset = 8;
            auto put = [&](const void* data, size_t bytes) {
                std::memcpy(header + offset, data, bytes);
                offset += bytes;
            };
            put(&headerSize, 4);
            put(&pointerBits, 4);
            put(&frequency, 8);
            put(&startQpc, 8);
            put(&startFileTime, 8);
            put(&g_RequestedHz, 4);
            put(&g_RequestedDepth, 4);
            put(&processId, 4);
            put(&reserved, 4);
            put(&startLocalFileTime, 8);

            DWORD written = 0;
            WriteFile(g_OutputFile, header, sizeof(header), &written, nullptr);
            g_BytesWritten += written;
            return true;
        }

        unsigned __stdcall SamplerThreadProc(void*)
        {
            const DWORD selfThreadId = GetCurrentThreadId();
            SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
            g_Buffer.reserve(kBufferReserveBytes);

            if (!OpenOutputFile())
            {
                g_Running.store(false, std::memory_order_release);
                return 1;
            }

            const uint64_t frequency = QpcFrequency();
            const uint32_t depthLimit = std::min(g_RequestedDepth, kMaxDepth);

            HANDLE timer = CreateWaitableTimerExW(
                nullptr, nullptr,
                CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                TIMER_ALL_ACCESS);
            bool highResolutionTimer = timer != nullptr;
            if (!timer)
            {
                timer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
            }
            if (!timer)
            {
                LogShimA(LogLevel::Error, kComponent,
                         "Cannot create sampling timer (error %lu); sampler will not start",
                         GetLastError());
                CloseHandle(g_OutputFile);
                g_OutputFile = INVALID_HANDLE_VALUE;
                g_Running.store(false, std::memory_order_release);
                return 1;
            }

            // The interval is jittered rather than periodic. A fixed 1 ms
            // period lands at the system timer granularity of about 1.5 ms,
            // and a 9.2 ms battle frame is almost exactly six of those: a
            // periodic sampler would keep landing at the same phase of every
            // frame and would report whichever subsystem happens to run there.
            // Uniform jitter over +/-50% of the nominal period removes the
            // aliasing, at the cost of an interval that is only correct on
            // average -- which is all a statistical profile needs.
            const uint64_t nominal100ns = 10000000ull / g_RequestedHz;
            uint64_t randomState =
                (static_cast<uint64_t>(GetCurrentThreadId()) << 32) ^ ReadQpc();
            const auto nextInterval = [&]() -> LONGLONG {
                randomState ^= randomState << 13;
                randomState ^= randomState >> 7;
                randomState ^= randomState << 17;
                const uint64_t span = nominal100ns; // half below, half above.
                const uint64_t jittered =
                    (nominal100ns / 2) + (randomState % (span == 0 ? 1 : span));
                return -static_cast<LONGLONG>(jittered == 0 ? 1 : jittered);
            };
            const auto armTimer = [&]() {
                LARGE_INTEGER due;
                due.QuadPart = nextInterval();
                SetWaitableTimer(timer, &due, 0, nullptr, nullptr, FALSE);
            };
            armTimer();

            LogShimA(LogLevel::Warn,
                     kComponent,
                     "ACTIVE requestedHz=%u depth=%u delaySeconds=%u durationSeconds=%u "
                     "highResolutionTimer=%d output='%s'. This capture suspends and "
                     "resumes process threads; frame times from a sampled run are not "
                     "evidence.",
                     g_RequestedHz, depthLimit, g_DelaySeconds, g_DurationSeconds,
                     highResolutionTimer ? 1 : 0, g_OutputPath.c_str());

            std::vector<ThreadEntry> threads;
            std::vector<uint8_t> sampleScratch;
            sampleScratch.reserve(64 * 1024);

            const uint64_t startQpc = ReadQpc();
            const uint64_t delayQpc =
                static_cast<uint64_t>(g_DelaySeconds) * frequency;
            const uint64_t durationQpc =
                g_DurationSeconds != 0
                    ? static_cast<uint64_t>(g_DurationSeconds) * frequency
                    : 0;

            RefreshModules();

            uint64_t lastEnumerateQpc = 0;
            uint64_t lastReportQpc = startQpc;
            bool sampling = delayQpc == 0;

            const HANDLE waitHandles[2] = { g_WakeEvent, timer };

            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                const DWORD wait = WaitForMultipleObjects(2, waitHandles, FALSE, 2000);
                if (wait == WAIT_OBJECT_0)
                {
                    break;
                }
                armTimer();
                const uint64_t nowQpc = ReadQpc();
                const uint64_t elapsedQpc = nowQpc - startQpc;
                ++g_TicksRequested;

                if (!sampling)
                {
                    if (elapsedQpc < delayQpc)
                    {
                        continue;
                    }
                    sampling = true;
                    LogShimA(LogLevel::Info, kComponent,
                             "Sampling window opened after %u s delay", g_DelaySeconds);
                }
                if (durationQpc != 0 && elapsedQpc > delayQpc + durationQpc)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "Sampling window closed after %u s", g_DurationSeconds);
                    break;
                }

                if (lastEnumerateQpc == 0 ||
                    (nowQpc - lastEnumerateQpc) >
                        (frequency * kEnumerateIntervalMs) / 1000u)
                {
                    const uint64_t passInterval100ns =
                        lastEnumerateQpc == 0
                            ? static_cast<uint64_t>(kEnumerateIntervalMs) * 10000ull
                            : ((nowQpc - lastEnumerateQpc) * 10000000ull) / frequency;
                    RefreshThreads(threads, selfThreadId, passInterval100ns);
                    RefreshModules();
                    lastEnumerateQpc = nowQpc;
                }

                sampleScratch.clear();
                for (ThreadEntry& tracked : threads)
                {
                    if (!tracked.sampled)
                    {
                        continue;
                    }
                    SampleThread(tracked, depthLimit, sampleScratch);
                }
                ++g_TicksServiced;

                if (!sampleScratch.empty())
                {
                    BeginChunk(kTagSampleBlock,
                               static_cast<uint32_t>(sampleScratch.size()));
                    BufferAppend(sampleScratch.data(), sampleScratch.size());
                }
                FlushBuffer(false);

                if ((nowQpc - lastReportQpc) >
                    (frequency * kReportIntervalMs) / 1000u)
                {
                    WriteStats(elapsedQpc);
                    ReportHealth(elapsedQpc, threads);
                    lastReportQpc = nowQpc;
                }
            }

            const uint64_t finalElapsed = ReadQpc() - startQpc;
            WriteStats(finalElapsed);
            BeginChunk(kTagEnd, 0);
            FlushBuffer(true);
            ReportHealth(finalElapsed, threads);

            CancelWaitableTimer(timer);
            CloseHandle(timer);
            CloseThreads(threads);
            if (g_OutputFile != INVALID_HANDLE_VALUE)
            {
                FlushFileBuffers(g_OutputFile);
                CloseHandle(g_OutputFile);
                g_OutputFile = INVALID_HANDLE_VALUE;
            }
            LogShimA(LogLevel::Info, kComponent,
                     "Sampler stopped; wrote %llu bytes to '%s'",
                     static_cast<unsigned long long>(g_BytesWritten),
                     g_OutputPath.c_str());
            g_Running.store(false, std::memory_order_release);
            return 0;
        }
    }

    bool IsNativeCpuSamplerRequested()
    {
        std::string value;
        if (!ReadEnvironmentValue(kEnvironmentSwitch, value))
        {
            return false;
        }
        return IsTruthy(value);
    }

    void InitializeNativeCpuSampler()
    {
        if (!IsNativeCpuSamplerRequested())
        {
            return;
        }
        if (g_Running.load(std::memory_order_acquire))
        {
            return;
        }

        g_RequestedHz = std::clamp(
            ReadEnvironmentUnsigned(kEnvironmentHz, kDefaultHz), kMinHz, kMaxHz);
        g_RequestedDepth = std::clamp(
            ReadEnvironmentUnsigned(kEnvironmentDepth, kDefaultDepth), 1u, kMaxDepth);
        g_DelaySeconds = ReadEnvironmentUnsigned(kEnvironmentDelay, 0);
        g_DurationSeconds = ReadEnvironmentUnsigned(kEnvironmentDuration, 0);

        g_WakeEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (!g_WakeEvent)
        {
            LogShimA(LogLevel::Error, kComponent,
                     "Cannot create sampler wake event (error %lu)", GetLastError());
            return;
        }
        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Running.store(true, std::memory_order_release);
        g_WorkerThread = reinterpret_cast<HANDLE>(
            _beginthreadex(nullptr, 0, &SamplerThreadProc, nullptr, 0, nullptr));
        if (!g_WorkerThread)
        {
            g_Running.store(false, std::memory_order_release);
            CloseHandle(g_WakeEvent);
            g_WakeEvent = nullptr;
            LogShimA(LogLevel::Error, kComponent, "Cannot start sampler thread");
        }
    }

    void ShutdownNativeCpuSampler()
    {
        if (!g_WorkerThread)
        {
            return;
        }
        g_ShutdownRequested.store(true, std::memory_order_release);
        if (g_WakeEvent)
        {
            SetEvent(g_WakeEvent);
        }
        // Bounded join. If the sampler misses the window, leave the thread
        // handle and its wake event alone: closing them under a still-running
        // worker hands it an invalid event and frees state it can still touch.
        const DWORD wait = WaitForSingleObject(g_WorkerThread, 5000);
        if (wait != WAIT_OBJECT_0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "CPU sampler thread exceeded its shutdown join window; "
                     "leaking thread and wake event rather than freeing under it");
            return;
        }
        CloseHandle(g_WorkerThread);
        g_WorkerThread = nullptr;
        if (g_WakeEvent)
        {
            CloseHandle(g_WakeEvent);
            g_WakeEvent = nullptr;
        }
    }
}
