// perf_telemetry.cpp
// BZR Open Shim - frame-hitch and address-space telemetry (diagnostic only)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// What this answers
// -----------------
// The CPU sampler answers "where does the average frame go". It cannot say
// what happens in the one frame in two hundred that takes 40 ms, because those
// samples are a rounding error in a whole-capture profile. This module records
// the frame boundaries themselves -- one QPC stamp per call of
// Ogre::Root::renderOneFrame, on the same clock the sampler uses -- so the
// offline analysis (reverse_engineering/analyze_frame_hitches.py) can select
// exactly the samples that fell inside slow frames and compare them with the
// samples from normal ones.
//
// It also reports the 32-bit address space: free, reserved and committed
// totals, the largest free block and how fragmented the rest is, at startup,
// at every mission enter and leave, and periodically. That is the number that
// decides whether long sessions are at risk of running out of usable address
// space, which nothing measured before this.
//
// Frame boundary
// --------------
// The executable imports renderOneFrame from OgreMain.dll and calls it once
// per main-loop iteration, on both render systems. Redirecting that one import
// slot gives a frame boundary without a code detour. The interval between two
// successive calls is the whole loop (simulation, Lua, rendering, present), so
// it is the frame time the player sees, not only Ogre's share of it.
//
// Cost on the main thread is two QPC reads, a histogram increment and a
// 24-byte append per frame, plus one summary every five seconds. The
// address-space walk (a VirtualQuery per region, a few milliseconds) runs on
// its own thread so it never lands inside a measured frame.

#include "perf_telemetry.h"
#include "bool_token.h"
#include "bzr_hooks_internal.h"
#include "diagnostic_output_cap.h"
#include "game_log_path.h"
#include "iat_patch.h"
#include "native_cpu_sampler.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <Psapi.h>
#include <process.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "perf-telemetry";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_PERF_TELEMETRY";
        // Seconds between periodic address-space reports; 0 = only at startup,
        // mission transitions and shutdown. Default kDefaultVaIntervalSeconds.
        constexpr char kEnvironmentVaSeconds[] = "OPENSHIM_PERF_TELEMETRY_VA_SECONDS";
        // Frame file size cap in whole MiB; 0 = no cap.
        constexpr char kEnvironmentMaxMiB[] = "OPENSHIM_PERF_TELEMETRY_MAX_MB";
        // Shared with the CPU sampler so the two files of one run pair by name.
        constexpr char kEnvironmentLabel[] = "OPENSHIM_PROFILE_NATIVE_CPU_LABEL";

        constexpr char kRenderOneFrameExport[] = "?renderOneFrame@Root@Ogre@@QAE_NXZ";

        constexpr uint32_t kDefaultVaIntervalSeconds = 30;
        // 24 bytes per frame: an hour at 200 fps is ~17 MiB.
        constexpr uint32_t kDefaultMaxMiB = 64;
        constexpr uint32_t kWindowMs = 5000;
        constexpr size_t kFlushThresholdBytes = 64u * 1024u;
        // Harnesses end a run with a hard kill, so buffered frames are written
        // at least this often; one second of records is ~1.5 KB.
        constexpr uint32_t kFlushIntervalMs = 1000;

        // A frame is a hitch when it takes at least twice the previous
        // window's median AND at least 4 ms longer than it. The second term
        // keeps a 3 ms -> 6 ms wobble in a 300 fps menu from counting.
        constexpr double kHitchRatio = 2.0;
        constexpr double kHitchMinExcessMs = 4.0;
        constexpr uint64_t kMinReferenceFrames = 30;
        constexpr uint32_t kHitchLinesPerWindow = 8;
        constexpr size_t kWorstFramesKept = 5;

        // 0.1 ms buckets to 200 ms; the last bucket is overflow.
        constexpr uint32_t kBucketUs = 100;
        constexpr uint32_t kBuckets = 2000;

        struct Histogram
        {
            uint32_t counts[kBuckets + 1];
            uint64_t frames;
            double sumMs;
            double maxMs;

            void Reset() noexcept
            {
                std::memset(this, 0, sizeof(*this));
            }

            void Add(double ms) noexcept
            {
                const double scaled = (ms * 1000.0) / static_cast<double>(kBucketUs);
                const uint32_t bucket = scaled >= kBuckets ? kBuckets
                                                           : static_cast<uint32_t>(scaled < 0.0 ? 0.0 : scaled);
                ++counts[bucket];
                ++frames;
                sumMs += ms;
                maxMs = std::max(maxMs, ms);
            }

            // Upper edge of the bucket holding the requested rank; the
            // overflow bucket reports the true maximum.
            double Percentile(double fraction) const noexcept
            {
                if (frames == 0)
                {
                    return 0.0;
                }
                const uint64_t rank = static_cast<uint64_t>(
                    std::max(1.0, fraction * static_cast<double>(frames) + 0.5));
                uint64_t seen = 0;
                for (uint32_t bucket = 0; bucket <= kBuckets; ++bucket)
                {
                    seen += counts[bucket];
                    if (seen >= rank)
                    {
                        return bucket == kBuckets
                                   ? maxMs
                                   : static_cast<double>((bucket + 1) * kBucketUs) / 1000.0;
                    }
                }
                return maxMs;
            }

            double MeanMs() const noexcept
            {
                return frames ? sumMs / static_cast<double>(frames) : 0.0;
            }
        };

        struct WorstFrame
        {
            double intervalMs;
            uint64_t frameIndex;
            double secondsIntoMission;
        };

        // On-disk record. Frame i is [beginQpc_i, beginQpc_{i+1}); renderEndQpc
        // is when renderOneFrame returned inside it.
        struct FrameRecord
        {
            uint64_t beginQpc;
            uint64_t renderEndQpc;
            int32_t runState;
            uint32_t flags;
        };
        static_assert(sizeof(FrameRecord) == 24, "frame record layout is part of the file format");
        constexpr uint32_t kFrameFlagHitch = 1u << 0;

        enum class VaReason : int
        {
            None = 0,
            Startup,
            Periodic,
            MissionEnter,
            MissionLeave,
            Shutdown,
        };

        const char* VaReasonName(VaReason reason) noexcept
        {
            switch (reason)
            {
            case VaReason::Startup: return "startup";
            case VaReason::Periodic: return "periodic";
            case VaReason::MissionEnter: return "mission-enter";
            case VaReason::MissionLeave: return "mission-leave";
            case VaReason::Shutdown: return "shutdown";
            default: return "none";
            }
        }

        using FnRenderOneFrame = bool(__thiscall*)(void*);

        std::atomic<bool> g_Active{ false };
        void* g_RealRenderOneFrame = nullptr;
        void** g_RenderOneFrameSlot = nullptr;
        uint64_t g_MaxFrameBytes = 0;
        std::string g_Label;

        // Main-thread frame state. The frame file buffer is also flushed at
        // shutdown from whichever thread runs it, so the buffer and handle sit
        // behind g_FrameLock; it is uncontended on every frame.
        SRWLOCK g_FrameLock = SRWLOCK_INIT;
        HANDLE g_FrameFile = INVALID_HANDLE_VALUE;
        std::vector<uint8_t> g_FrameBuffer;
        uint64_t g_FrameBytesWritten = 0;
        bool g_FrameFileCapped = false;
        bool g_FrameFileOpenFailed = false;

        DWORD g_MainThreadId = 0;
        uint64_t g_FrameIndex = 0;
        bool g_HavePending = false;
        FrameRecord g_Pending{};
        uint64_t g_LastRenderEndQpc = 0;

        Histogram g_Window;
        Histogram g_Mission;
        uint64_t g_WindowStartQpc = 0;
        uint64_t g_LastFlushQpc = 0;
        uint32_t g_WindowHitches = 0;
        uint32_t g_WindowHitchLines = 0;
        double g_ReferenceP50Ms = 0.0;
        bool g_HaveReference = false;

        bool g_InMission = false;
        uint64_t g_MissionStartQpc = 0;
        uint32_t g_MissionHitches = 0;
        uint32_t g_MissionOrdinal = 0;
        WorstFrame g_Worst[kWorstFramesKept] = {};

        // Mission transitions arrive from the SetRunning seam. They are applied
        // at the next frame boundary so all histogram state stays on the frame
        // thread.
        std::atomic<int> g_PendingTransition{ 0 }; // +1 enter, -1 leave

        // Address-space reporter.
        HANDLE g_VaThread = nullptr;
        HANDLE g_VaWakeEvent = nullptr;
        std::atomic<bool> g_VaShutdown{ false };
        std::atomic<int> g_VaRequestedReason{ 0 };
        DWORD g_VaIntervalMs = 0;
        std::string g_VaCsvPath;

        uint64_t ReadQpc() noexcept
        {
            LARGE_INTEGER value;
            QueryPerformanceCounter(&value);
            return static_cast<uint64_t>(value.QuadPart);
        }

        uint64_t QpcFrequency() noexcept
        {
            static const uint64_t frequency = []() -> uint64_t {
                LARGE_INTEGER value;
                QueryPerformanceFrequency(&value);
                return static_cast<uint64_t>(value.QuadPart);
            }();
            return frequency;
        }

        double QpcToMs(uint64_t ticks) noexcept
        {
            return static_cast<double>(ticks) * 1000.0 / static_cast<double>(QpcFrequency());
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
            return end == text.c_str() ? fallback : static_cast<uint32_t>(parsed);
        }

        std::string SanitizedLabel()
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
            return label;
        }

        void CurrentMissionName(char (&out)[Hooks::kQueuedLoadNameBufferLen + 1]) noexcept
        {
            // Written by the career-stats load hook on the main thread; a torn
            // read only garbles a diagnostic label, so copy it bounded.
            for (int index = 0; index < Hooks::kQueuedLoadNameBufferLen; ++index)
            {
                const char character = Hooks::g_LastKnownQueuedMissionName[index];
                out[index] = (character >= 0x20 && character < 0x7F) ? character : '\0';
                if (character == '\0')
                {
                    break;
                }
            }
            out[Hooks::kQueuedLoadNameBufferLen] = '\0';
            if (out[0] == '\0')
            {
                std::strcpy(out, "?");
            }
        }

        int ReadRunState() noexcept
        {
            int state = Hooks::kBzrRunStateUnknown;
            return Hooks::TryReadBzrRunState(state) ? state : Hooks::kBzrRunStateUnknown;
        }

        // ---------------------------------------------------------------
        // Frame file
        // ---------------------------------------------------------------
        void OpenFrameFileLocked()
        {
            char fileName[192] = {};
            _snprintf_s(fileName, sizeof(fileName), _TRUNCATE,
                        "openshim_frames_%s_%lu.bin", g_Label.c_str(), GetCurrentProcessId());
            const std::string path = GetGameLogPath(fileName);
            g_FrameFile = CreateFileA(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (g_FrameFile == INVALID_HANDLE_VALUE)
            {
                g_FrameFileOpenFailed = true;
                LogShimA(LogLevel::Error, kComponent,
                         "Cannot create frame file '%s' (error %lu); frame records will not be written",
                         path.c_str(), GetLastError());
                return;
            }

            // 64-byte header: magic, header size, record size, QPC frequency,
            // QPC at open, local FILETIME at open, main thread id, process id.
            uint8_t header[64] = {};
            std::memcpy(header, "OSFRAME1", 8);
            const uint32_t headerSize = sizeof(header);
            const uint32_t recordSize = sizeof(FrameRecord);
            const uint64_t frequency = QpcFrequency();
            const uint64_t openQpc = ReadQpc();
            SYSTEMTIME localNow{};
            GetLocalTime(&localNow);
            FILETIME localFileTime{};
            SystemTimeToFileTime(&localNow, &localFileTime);
            const uint64_t localStamp =
                (static_cast<uint64_t>(localFileTime.dwHighDateTime) << 32) | localFileTime.dwLowDateTime;
            const uint32_t mainThread = g_MainThreadId;
            const uint32_t processId = GetCurrentProcessId();
            size_t offset = 8;
            const auto put = [&](const void* data, size_t bytes) {
                std::memcpy(header + offset, data, bytes);
                offset += bytes;
            };
            put(&headerSize, 4);
            put(&recordSize, 4);
            put(&frequency, 8);
            put(&openQpc, 8);
            put(&localStamp, 8);
            put(&mainThread, 4);
            put(&processId, 4);
            DWORD written = 0;
            WriteFile(g_FrameFile, header, sizeof(header), &written, nullptr);
            g_FrameBytesWritten = written;
            LogShimA(LogLevel::Info, kComponent, "Frame records -> '%s'", path.c_str());
        }

        void FlushFramesLocked(bool force)
        {
            if (g_FrameBuffer.empty() || (!force && g_FrameBuffer.size() < kFlushThresholdBytes))
            {
                return;
            }
            if (g_FrameFile == INVALID_HANDLE_VALUE || g_FrameFileCapped)
            {
                g_FrameBuffer.clear();
                return;
            }
            DWORD written = 0;
            if (WriteFile(g_FrameFile, g_FrameBuffer.data(),
                          static_cast<DWORD>(g_FrameBuffer.size()), &written, nullptr))
            {
                g_FrameBytesWritten += written;
            }
            g_FrameBuffer.clear();
            if (DiagnosticOutputCap::ReachedCap(g_FrameBytesWritten, g_MaxFrameBytes))
            {
                g_FrameFileCapped = true;
                LogShimA(LogLevel::Warn, kComponent,
                         "Frame file reached its size cap (%llu bytes; %s, 0 = no cap); "
                         "summaries continue, records stop",
                         static_cast<unsigned long long>(g_FrameBytesWritten), kEnvironmentMaxMiB);
            }
        }

        void AppendFrameRecord(const FrameRecord& record)
        {
            AcquireSRWLockExclusive(&g_FrameLock);
            if (g_FrameFile == INVALID_HANDLE_VALUE && !g_FrameFileOpenFailed)
            {
                OpenFrameFileLocked();
            }
            if (g_FrameFile != INVALID_HANDLE_VALUE && !g_FrameFileCapped)
            {
                const auto* bytes = reinterpret_cast<const uint8_t*>(&record);
                g_FrameBuffer.insert(g_FrameBuffer.end(), bytes, bytes + sizeof(record));
            }
            ReleaseSRWLockExclusive(&g_FrameLock);
        }

        // ---------------------------------------------------------------
        // Address-space report
        // ---------------------------------------------------------------
        void RequestVaReport(VaReason reason) noexcept
        {
            g_VaRequestedReason.store(static_cast<int>(reason), std::memory_order_release);
            if (g_VaWakeEvent)
            {
                SetEvent(g_VaWakeEvent);
            }
        }

        void WriteVaReport(VaReason reason)
        {
            constexpr double kMiB = 1024.0 * 1024.0;
            const uint64_t walkStart = ReadQpc();

            SYSTEM_INFO systemInfo{};
            GetSystemInfo(&systemInfo);
            const uintptr_t low = reinterpret_cast<uintptr_t>(systemInfo.lpMinimumApplicationAddress);
            const uintptr_t high = reinterpret_cast<uintptr_t>(systemInfo.lpMaximumApplicationAddress);

            uint64_t freeBytes = 0, reservedBytes = 0, committedBytes = 0;
            uint64_t imageBytes = 0, mappedBytes = 0, privateBytes = 0;
            uint64_t largestFree = 0;
            uint32_t regions = 0, freeRegions = 0, free1MiB = 0, free16MiB = 0, free64MiB = 0;

            uintptr_t address = low;
            MEMORY_BASIC_INFORMATION info{};
            while (address < high && VirtualQuery(reinterpret_cast<const void*>(address), &info, sizeof(info)) != 0)
            {
                const uintptr_t base = reinterpret_cast<uintptr_t>(info.BaseAddress);
                const uint64_t size = info.RegionSize;
                ++regions;
                if (info.State == MEM_FREE)
                {
                    freeBytes += size;
                    ++freeRegions;
                    largestFree = std::max(largestFree, size);
                    free1MiB += size >= (1ull << 20) ? 1u : 0u;
                    free16MiB += size >= (16ull << 20) ? 1u : 0u;
                    free64MiB += size >= (64ull << 20) ? 1u : 0u;
                }
                else
                {
                    if (info.State == MEM_RESERVE)
                    {
                        reservedBytes += size;
                    }
                    else
                    {
                        committedBytes += size;
                        if (info.Type == MEM_IMAGE)
                        {
                            imageBytes += size;
                        }
                        else if (info.Type == MEM_MAPPED)
                        {
                            mappedBytes += size;
                        }
                        else
                        {
                            privateBytes += size;
                        }
                    }
                }
                const uintptr_t next = base + static_cast<uintptr_t>(size);
                if (next <= address)
                {
                    break;
                }
                address = next;
            }
            const double walkMs = QpcToMs(ReadQpc() - walkStart);

            PROCESS_MEMORY_COUNTERS_EX counters{};
            counters.cb = sizeof(counters);
            K32GetProcessMemoryInfo(GetCurrentProcess(),
                                    reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&counters),
                                    sizeof(counters));
            const DWORD heaps = GetProcessHeaps(0, nullptr);

            char mission[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            CurrentMissionName(mission);
            const int runState = ReadRunState();
            const double userSpaceMiB = static_cast<double>(high - low + 1) / kMiB;

            LogShimA(LogLevel::Info, kComponent,
                     "[VA] reason=%s mission=%s runState=%d userSpaceMiB=%.0f freeMiB=%.1f "
                     "largestFreeMiB=%.1f freeRegions=%u free>=1MiB=%u free>=16MiB=%u free>=64MiB=%u "
                     "reservedMiB=%.1f committedMiB=%.1f imageMiB=%.1f mappedMiB=%.1f privateMiB=%.1f "
                     "privateUsageMiB=%.1f workingSetMiB=%.1f heaps=%lu regions=%u walkMs=%.2f",
                     VaReasonName(reason), mission, runState, userSpaceMiB,
                     freeBytes / kMiB, largestFree / kMiB, freeRegions, free1MiB, free16MiB, free64MiB,
                     reservedBytes / kMiB, committedBytes / kMiB, imageBytes / kMiB, mappedBytes / kMiB,
                     privateBytes / kMiB, counters.PrivateUsage / kMiB, counters.WorkingSetSize / kMiB,
                     heaps, regions, walkMs);

            const bool newFile = GetFileAttributesA(g_VaCsvPath.c_str()) == INVALID_FILE_ATTRIBUTES;
            FILE* csv = nullptr;
            if (fopen_s(&csv, g_VaCsvPath.c_str(), "ab") != 0 || !csv)
            {
                return;
            }
            if (newFile)
            {
                std::fputs("local_time,qpc,reason,mission,run_state,user_space_mib,free_mib,"
                           "largest_free_mib,free_regions,free_ge_1mib,free_ge_16mib,free_ge_64mib,"
                           "reserved_mib,committed_mib,image_mib,mapped_mib,private_mib,"
                           "private_usage_mib,working_set_mib,heaps,regions,walk_ms\n",
                           csv);
            }
            SYSTEMTIME now{};
            GetLocalTime(&now);
            std::fprintf(csv,
                         "%04u-%02u-%02uT%02u:%02u:%02u.%03u,%llu,%s,%s,%d,%.0f,%.2f,%.2f,%u,%u,%u,%u,"
                         "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%lu,%u,%.2f\n",
                         now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond,
                         now.wMilliseconds, static_cast<unsigned long long>(walkStart),
                         VaReasonName(reason), mission, runState, userSpaceMiB,
                         freeBytes / kMiB, largestFree / kMiB, freeRegions, free1MiB, free16MiB,
                         free64MiB, reservedBytes / kMiB, committedBytes / kMiB, imageBytes / kMiB,
                         mappedBytes / kMiB, privateBytes / kMiB, counters.PrivateUsage / kMiB,
                         counters.WorkingSetSize / kMiB, heaps, regions, walkMs);
            std::fclose(csv);
        }

        unsigned __stdcall VaThreadProc(void*)
        {
            WriteVaReport(VaReason::Startup);
            while (!g_VaShutdown.load(std::memory_order_acquire))
            {
                const DWORD wait = WaitForSingleObject(
                    g_VaWakeEvent, g_VaIntervalMs != 0 ? g_VaIntervalMs : INFINITE);
                if (g_VaShutdown.load(std::memory_order_acquire))
                {
                    break;
                }
                VaReason reason = VaReason::Periodic;
                if (wait == WAIT_OBJECT_0)
                {
                    reason = static_cast<VaReason>(
                        g_VaRequestedReason.exchange(0, std::memory_order_acq_rel));
                    if (reason == VaReason::None)
                    {
                        continue;
                    }
                }
                WriteVaReport(reason);
            }
            WriteVaReport(VaReason::Shutdown);
            return 0;
        }

        // ---------------------------------------------------------------
        // Frame bookkeeping (frame thread only)
        // ---------------------------------------------------------------
        void ResetMissionStats(uint64_t nowQpc)
        {
            g_Mission.Reset();
            g_MissionStartQpc = nowQpc;
            g_MissionHitches = 0;
            for (WorstFrame& worst : g_Worst)
            {
                worst = WorstFrame{};
            }
        }

        void NoteWorstFrame(double intervalMs, uint64_t frameIndex, uint64_t frameQpc)
        {
            WorstFrame* smallest = &g_Worst[0];
            for (WorstFrame& worst : g_Worst)
            {
                if (worst.intervalMs < smallest->intervalMs)
                {
                    smallest = &worst;
                }
            }
            if (intervalMs <= smallest->intervalMs)
            {
                return;
            }
            smallest->intervalMs = intervalMs;
            smallest->frameIndex = frameIndex;
            smallest->secondsIntoMission = QpcToMs(frameQpc - g_MissionStartQpc) / 1000.0;
        }

        void LogMissionSummary(uint64_t nowQpc)
        {
            char mission[Hooks::kQueuedLoadNameBufferLen + 1] = {};
            CurrentMissionName(mission);
            const double seconds = QpcToMs(nowQpc - g_MissionStartQpc) / 1000.0;
            WorstFrame sorted[kWorstFramesKept];
            std::copy(std::begin(g_Worst), std::end(g_Worst), sorted);
            std::sort(std::begin(sorted), std::end(sorted),
                      [](const WorstFrame& a, const WorstFrame& b) { return a.intervalMs > b.intervalMs; });
            char worst[256] = {};
            size_t used = 0;
            for (const WorstFrame& entry : sorted)
            {
                if (entry.intervalMs <= 0.0)
                {
                    break;
                }
                const int wrote = _snprintf_s(worst + used, sizeof(worst) - used, _TRUNCATE,
                                              "%s%.1fms@%.1fs", used ? "," : "",
                                              entry.intervalMs, entry.secondsIntoMission);
                if (wrote < 0)
                {
                    break;
                }
                used += static_cast<size_t>(wrote);
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[Frames][Mission] ordinal=%u mission=%s seconds=%.1f frames=%llu fps=%.1f "
                     "meanMs=%.2f p50Ms=%.1f p90Ms=%.1f p99Ms=%.1f p999Ms=%.1f maxMs=%.1f "
                     "hitches=%u hitchesPerMin=%.2f worst=%s",
                     g_MissionOrdinal, mission, seconds,
                     static_cast<unsigned long long>(g_Mission.frames),
                     seconds > 0.0 ? static_cast<double>(g_Mission.frames) / seconds : 0.0,
                     g_Mission.MeanMs(), g_Mission.Percentile(0.50), g_Mission.Percentile(0.90),
                     g_Mission.Percentile(0.99), g_Mission.Percentile(0.999), g_Mission.maxMs,
                     g_MissionHitches, seconds > 0.0 ? g_MissionHitches * 60.0 / seconds : 0.0,
                     worst[0] ? worst : "-");
        }

        void ApplyPendingTransition(uint64_t nowQpc)
        {
            const int transition = g_PendingTransition.exchange(0, std::memory_order_acq_rel);
            if (transition > 0 && !g_InMission)
            {
                g_InMission = true;
                ++g_MissionOrdinal;
                ResetMissionStats(nowQpc);
                // The first frames after a load are the loading tail; let the
                // reference median re-establish itself before judging hitches.
                g_HaveReference = false;
            }
            else if (transition < 0 && g_InMission)
            {
                g_InMission = false;
                LogMissionSummary(nowQpc);
                AcquireSRWLockExclusive(&g_FrameLock);
                FlushFramesLocked(true);
                ReleaseSRWLockExclusive(&g_FrameLock);
            }
        }

        void CloseWindow(uint64_t nowQpc, int runState)
        {
            const double seconds = QpcToMs(nowQpc - g_WindowStartQpc) / 1000.0;
            if (g_Window.frames != 0)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[Frames] seconds=%.1f frames=%llu fps=%.1f meanMs=%.2f p50Ms=%.1f "
                         "p95Ms=%.1f p99Ms=%.1f maxMs=%.1f hitches=%u runState=%d",
                         seconds, static_cast<unsigned long long>(g_Window.frames),
                         seconds > 0.0 ? static_cast<double>(g_Window.frames) / seconds : 0.0,
                         g_Window.MeanMs(), g_Window.Percentile(0.50), g_Window.Percentile(0.95),
                         g_Window.Percentile(0.99), g_Window.maxMs, g_WindowHitches, runState);
            }
            if (g_Window.frames >= kMinReferenceFrames)
            {
                g_ReferenceP50Ms = g_Window.Percentile(0.50);
                g_HaveReference = true;
            }
            g_Window.Reset();
            g_WindowStartQpc = nowQpc;
            g_WindowHitches = 0;
            g_WindowHitchLines = 0;

            // Forced: a process killed or exited without shutdown keeps every
            // frame up to the last window.
            AcquireSRWLockExclusive(&g_FrameLock);
            FlushFramesLocked(true);
            ReleaseSRWLockExclusive(&g_FrameLock);
        }

        void OnFrameBegin(uint64_t nowQpc)
        {
            if (g_MainThreadId == 0)
            {
                g_MainThreadId = GetCurrentThreadId();
                g_WindowStartQpc = nowQpc;
                LogShimA(LogLevel::Info, kComponent,
                         "First frame on thread %lu; frame boundary = renderOneFrame",
                         g_MainThreadId);
            }

            const int runState = ReadRunState();
            if (g_HavePending)
            {
                // Close the previous frame now that its end is known.
                const double intervalMs = QpcToMs(nowQpc - g_Pending.beginQpc);
                g_Pending.renderEndQpc = g_LastRenderEndQpc;
                const bool hitch = g_HaveReference &&
                                   intervalMs >= g_ReferenceP50Ms * kHitchRatio &&
                                   intervalMs - g_ReferenceP50Ms >= kHitchMinExcessMs;
                if (hitch)
                {
                    g_Pending.flags |= kFrameFlagHitch;
                    ++g_WindowHitches;
                    if (g_InMission)
                    {
                        ++g_MissionHitches;
                    }
                    if (g_WindowHitchLines < kHitchLinesPerWindow)
                    {
                        ++g_WindowHitchLines;
                        LogShimA(LogLevel::Info, kComponent,
                                 "[Hitch] frame=%llu intervalMs=%.1f renderMs=%.1f referenceP50Ms=%.1f "
                                 "runState=%d missionSeconds=%.1f qpc=%llu",
                                 static_cast<unsigned long long>(g_FrameIndex - 1), intervalMs,
                                 QpcToMs(g_Pending.renderEndQpc - g_Pending.beginQpc),
                                 g_ReferenceP50Ms, g_Pending.runState,
                                 g_InMission ? QpcToMs(g_Pending.beginQpc - g_MissionStartQpc) / 1000.0 : 0.0,
                                 static_cast<unsigned long long>(g_Pending.beginQpc));
                    }
                }
                g_Window.Add(intervalMs);
                if (g_InMission)
                {
                    g_Mission.Add(intervalMs);
                    NoteWorstFrame(intervalMs, g_FrameIndex - 1, g_Pending.beginQpc);
                }
                AppendFrameRecord(g_Pending);
            }

            ApplyPendingTransition(nowQpc);
            if (QpcToMs(nowQpc - g_WindowStartQpc) >= kWindowMs)
            {
                CloseWindow(nowQpc, runState);
            }
            else if (QpcToMs(nowQpc - g_LastFlushQpc) >= kFlushIntervalMs)
            {
                g_LastFlushQpc = nowQpc;
                AcquireSRWLockExclusive(&g_FrameLock);
                FlushFramesLocked(true);
                ReleaseSRWLockExclusive(&g_FrameLock);
            }

            g_Pending = FrameRecord{ nowQpc, 0, runState, 0 };
            g_HavePending = true;
            ++g_FrameIndex;
        }

        bool __fastcall RenderOneFrameHook(void* self, void* /*edx*/)
        {
            const auto real = reinterpret_cast<FnRenderOneFrame>(g_RealRenderOneFrame);
            if (g_Active.load(std::memory_order_acquire) &&
                (GetCurrentThreadId() == g_MainThreadId || g_MainThreadId == 0))
            {
                OnFrameBegin(ReadQpc());
                const bool result = real(self);
                g_LastRenderEndQpc = ReadQpc();
                return result;
            }
            return real(self);
        }
    }

    bool IsPerfTelemetryRequested()
    {
        std::string value;
        if (ReadEnvironmentValue(kEnvironmentSwitch, value))
        {
            return BoolToken::IsTruthy(value);
        }
        return IsNativeCpuSamplerRequested();
    }

    void InitializePerfTelemetry()
    {
        if (g_Active.load(std::memory_order_acquire) || !IsPerfTelemetryRequested())
        {
            return;
        }
        g_Label = SanitizedLabel();
        {
            std::string maxText;
            const bool haveMax = ReadEnvironmentValue(kEnvironmentMaxMiB, maxText);
            g_MaxFrameBytes = DiagnosticOutputCap::ResolveCapBytes(
                haveMax ? maxText.c_str() : nullptr, nullptr, kDefaultMaxMiB);
        }
        g_FrameBuffer.reserve(kFlushThresholdBytes + sizeof(FrameRecord) * 64);

        // Address-space reporter first: it is useful even when the frame
        // boundary cannot be found on this build.
        g_VaIntervalMs = ReadEnvironmentUnsigned(kEnvironmentVaSeconds, kDefaultVaIntervalSeconds) * 1000u;
        {
            char fileName[192] = {};
            _snprintf_s(fileName, sizeof(fileName), _TRUNCATE,
                        "openshim_va_%s_%lu.csv", g_Label.c_str(), GetCurrentProcessId());
            g_VaCsvPath = GetGameLogPath(fileName);
        }
        g_VaWakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        if (g_VaWakeEvent)
        {
            g_VaShutdown.store(false, std::memory_order_release);
            g_VaThread = reinterpret_cast<HANDLE>(
                _beginthreadex(nullptr, 0, &VaThreadProc, nullptr, 0, nullptr));
        }
        if (!g_VaThread)
        {
            LogShimA(LogLevel::Warn, kComponent, "Address-space reporter thread did not start");
        }

        const IatPatch::Result result = IatPatch::PatchImport(
            GetModuleHandleW(nullptr), "OgreMain.dll", kRenderOneFrameExport,
            reinterpret_cast<void*>(&RenderOneFrameHook), &g_RealRenderOneFrame,
            &g_RenderOneFrameSlot);
        if (result != IatPatch::Result::Patched || !g_RealRenderOneFrame)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "Executable import %s from OgreMain.dll not redirected (result=%d); "
                     "frame-hitch telemetry unavailable, address-space reports continue",
                     kRenderOneFrameExport, static_cast<int>(result));
        }
        g_Active.store(true, std::memory_order_release);
        LogShimA(LogLevel::Warn, kComponent,
                 "ACTIVE frames=%d vaIntervalSeconds=%lu maxFrameBytes=%llu label=%s va='%s'. "
                 "Hitch = interval >= %.1fx previous 5 s median and >= %.1f ms over it.",
                 g_RealRenderOneFrame ? 1 : 0, g_VaIntervalMs / 1000u,
                 static_cast<unsigned long long>(g_MaxFrameBytes), g_Label.c_str(),
                 g_VaCsvPath.c_str(), kHitchRatio, kHitchMinExcessMs);
    }

    void PerfTelemetryMissionRunStateChanged(int previous, int current)
    {
        if (!g_Active.load(std::memory_order_acquire))
        {
            return;
        }
        const bool entered = previous != Hooks::kBzrRunStateStarted && current == Hooks::kBzrRunStateStarted;
        const bool left = previous == Hooks::kBzrRunStateStarted && current != Hooks::kBzrRunStateStarted;
        if (entered)
        {
            g_PendingTransition.store(1, std::memory_order_release);
            RequestVaReport(VaReason::MissionEnter);
        }
        else if (left)
        {
            g_PendingTransition.store(-1, std::memory_order_release);
            RequestVaReport(VaReason::MissionLeave);
        }
    }

    void ShutdownPerfTelemetry()
    {
        if (!g_Active.exchange(false, std::memory_order_acq_rel))
        {
            return;
        }
        if (g_VaThread)
        {
            g_VaShutdown.store(true, std::memory_order_release);
            SetEvent(g_VaWakeEvent);
            if (WaitForSingleObject(g_VaThread, 3000) == WAIT_OBJECT_0)
            {
                CloseHandle(g_VaThread);
                CloseHandle(g_VaWakeEvent);
                g_VaWakeEvent = nullptr;
            }
            g_VaThread = nullptr;
        }
        // The import slot keeps pointing at the hook: Ogre may still render a
        // frame during teardown, and with g_Active cleared the hook only
        // forwards. Flush whatever is buffered.
        AcquireSRWLockExclusive(&g_FrameLock);
        FlushFramesLocked(true);
        if (g_FrameFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(g_FrameFile);
            g_FrameFile = INVALID_HANDLE_VALUE;
            g_FrameFileOpenFailed = true; // do not reopen during teardown frames
        }
        ReleaseSRWLockExclusive(&g_FrameLock);
    }
}
