// ui_performance.cpp
// BZR Open Shim - UI Responsiveness / Stall Profiling implementation
//
// See include/ui_performance.h for design.  Key properties:
//  - Hot path when OFF: single relaxed atomic load + early return.
//  - Hierarchical depth tracked thread-local; indentation derived from depth.
//  - Summary buckets accumulated per transition and emitted at transition End.
//  - QPC-based monotonic timer.
//  - Verbose lines are buffered and flushed as a block to avoid log interleaving.
//  - All public entry points are noexcept and never throw.
//
// SPDX-License-Identifier: MIT

#include "ui_performance.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim::UiPerf
{
    namespace
    {
        constexpr const char* kComponent = "uiperf";
        constexpr double kDefaultStallThresholdMs = 250.0;
        constexpr size_t kMaxBufferedLines = 4096;

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_Verbose{ false };
        std::atomic<bool> g_Initialized{ false };
        std::atomic<double> g_StallThresholdMs{ kDefaultStallThresholdMs };

        // QPC frequency cached at first use.
        uint64_t QpcFrequency() noexcept
        {
            static uint64_t s_freq = []() -> uint64_t {
                LARGE_INTEGER f{};
                QueryPerformanceFrequency(&f);
                return static_cast<uint64_t>(f.QuadPart);
            }();
            return s_freq;
        }

        // Thread-local nesting stack.
        struct ThreadState
        {
            int depth = 0;
            uint64_t lastHeartbeatTicks = 0;
            const char* lastMarker = nullptr;
            std::vector<std::string> verboseBuffer;
            bool bufferActive = false;
        };
        thread_local ThreadState t_state;

        // Transition-level aggregation (protected by mutex because shell
        // notifications may come from a different path than ScopedTransition).
        struct CategoryBucket
        {
            double totalMs = 0.0;
            uint32_t calls = 0;
        };
        std::mutex g_Mutex;
        std::unordered_map<std::string, CategoryBucket> g_CategoryBuckets;
        std::string g_ActiveTransitionLabel;
        uint64_t g_ActiveTransitionStart = 0;
        std::vector<std::string> g_ActiveNotes;
        bool g_TransitionActive = false;

        void LogLocked(LogLevel level, const char* fmt, va_list args) noexcept
        {
            char buf[1024] = {};
            _vsnprintf_s(buf, _countof(buf), _TRUNCATE, fmt, args);
            // Trim trailing newlines; shim_log adds its own.
            std::string s(buf);
            while (!s.empty() && (s.back() == '\r' || s.back() == '\n'))
                s.pop_back();
            if (s.empty()) s = "<empty>";
            // Use LogShimVA to avoid re-entering UI perf.
            // We forward via the narrow helper with a truncated format string.
            // Simpler: reformat once and call LogShimA.
            LogShimA(level, kComponent, "%s", s.c_str());
        }

        void EmitLocked(const char* line) noexcept
        {
            LogShimA(LogLevel::Info, kComponent, "%s", line);
        }

        std::string IndentForDepth(int depth) noexcept
        {
            // Two spaces per level, matching the spec example.
            if (depth <= 0) return {};
            return std::string(static_cast<size_t>(depth * 2), ' ');
        }

        void BufferOrEmitVerbose(const std::string& line) noexcept
        {
            if (t_state.bufferActive)
            {
                if (t_state.verboseBuffer.size() < kMaxBufferedLines)
                    t_state.verboseBuffer.push_back(line);
            }
            else
            {
                EmitLocked(line.c_str());
            }
        }

        void ResetCategoryBucketsLocked() noexcept
        {
            g_CategoryBuckets.clear();
            g_ActiveNotes.clear();
        }

        std::string FormatSummaryLocked(const char* label, double totalMs) noexcept
        {
            // Summary print order is deterministic for log grepping.
            char header[512] = {};
            _snprintf_s(header, _countof(header), _TRUNCATE,
                "[UIPERF][SUMMARY] transition=%s total=%.2fms",
                label ? label : "<unknown>", totalMs);
            std::string out(header);

            // Emit category breakdown on subsequent lines, sorted alphabetically
            // to keep output stable across runs.
            if (!g_CategoryBuckets.empty())
            {
                std::vector<std::pair<std::string, CategoryBucket>> sorted(
                    g_CategoryBuckets.begin(), g_CategoryBuckets.end());
                std::sort(sorted.begin(), sorted.end(),
                    [](const auto& a, const auto& b){ return a.first < b.first; });
                for (const auto& kv : sorted)
                {
                    char line[256] = {};
                    _snprintf_s(line, _countof(line), _TRUNCATE,
                        "  %s=%.2fms calls=%u",
                        kv.first.c_str(), kv.second.totalMs, kv.second.calls);
                    out += "\n";
                    out += line;
                }
            }
            if (!g_ActiveNotes.empty())
            {
                for (const auto& n : g_ActiveNotes)
                {
                    out += "\n  note: ";
                    out += n;
                }
            }
            return out;
        }

        // Map known Redux shell screen IDs to human names (from
        // reverse_engineering/REDUX_SHELL_UI_RE_MAP.md). Unknown IDs still
        // produce "Screen0xNN".
        const char* ScreenNameTable(int id) noexcept
        {
            switch (id)
            {
            case 0x01: return "MainMenu";
            case 0x02: return "SinglePlayer";
            case 0x03: return "OptionsAudio/OptionsParent";
            case 0x04: return "OptionsPlay";
            case 0x05: return "OptionsGraphics";
            case 0x06: return "OptionsAudio";
            case 0x07: return "Mission";
            case 0x08: return "Mission2";
            case 0x09: return "Mission3";
            case 0x0B: return "Esc/Multiplayer_Status";
            case 0x0E: return "Multiplayer_Lobby";
            case 0x0F: return "Multiplayer_Create";
            case 0x11: return "Save";
            case 0x12: return "Load";
            case 0x13: return "MissionFailed";
            case 0x14: return "MissionSuccess";
            case 0x15: return "OptionsInput";
            case 0x16: return "OptionsJoystick";
            case 0x17: return "Loading";
            case 0x18: return "MissionArchives";
            case 0x1B: return "InstantAction";
            case 0x1C: return "Mods";
            case 0x1D: return "AlertDlgBox";
            case 0x1E: return "Multiplayer_Refresh";
            case 0x1F: return "Invite";
            case 0x20: return "Campaign";
            default:   return nullptr;
            }
        }
    } // namespace

    void Initialize()
    {
        if (g_Initialized.exchange(true))
            return;

        bool enabled = false;
        bool verbose = false;
        // Openshim's universal alias: any OPENSHIM_*/BZR_* can be set under
        // [Environment] in openshim.ini; the forced-include header redirects
        // GetEnvironmentVariableA automatically, so probing the env var covers
        // both the real environment and the ini.
        char buf[32] = {};

        auto readBoolEnv = [&](const char* name, bool& out) -> bool {
            const DWORD len = GetEnvironmentVariableA(name, buf, sizeof(buf));
            if (len == 0 || len >= sizeof(buf)) return false;
            std::string v(buf, len);
            for (char& c : v) c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
            if (v == "1" || v == "true" || v == "on" || v == "yes" || v == "enabled") { out = true; return true; }
            if (v == "0" || v == "false" || v == "off" || v == "no" || v == "disabled") { out = false; return true; }
            return false;
        };

        // Friendly INI keys live in [Diagnostics] directly; check them first.
        char gameDir[MAX_PATH] = {};
        const DWORD exeLen = GetModuleFileNameA(nullptr, gameDir, MAX_PATH);
        std::string iniPath;
        if (exeLen > 0 && exeLen < MAX_PATH)
        {
            char* slash = strrchr(gameDir, '\\');
            if (slash) { *(slash+1) = '\0'; iniPath = std::string(gameDir) + "openshim.ini"; }
        }
        if (!iniPath.empty())
        {
            char val[64] = {};
            GetPrivateProfileStringA("Diagnostics", "UiPerformanceLogging", "__unset__", val, sizeof(val), iniPath.c_str());
            if (strcmp(val, "__unset__") != 0)
            {
                std::string v(val);
                for (char& c : v) c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
                if (v == "1" || v == "true" || v == "on" || v == "yes" || v == "enabled") enabled = true;
                else if (v == "0" || v == "false" || v == "off" || v == "no" || v == "disabled") enabled = false;
                // Also allow direct env probing to win if ini absent.
            }
            else
            {
                // Fall back to env aliases when ini key absent.
                readBoolEnv("OPENSHIM_UI_PERFORMANCE_LOGGING", enabled);
            }
            GetPrivateProfileStringA("Diagnostics", "UiPerformanceVerbose", "__unset__", val, sizeof(val), iniPath.c_str());
            if (strcmp(val, "__unset__") != 0)
            {
                std::string v(val);
                for (char& c : v) c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
                if (v == "1" || v == "true" || v == "on" || v == "yes" || v == "enabled") verbose = true;
                else if (v == "0" || v == "false" || v == "off" || v == "no" || v == "disabled") verbose = false;
            }
            else
            {
                readBoolEnv("OPENSHIM_UI_PERFORMANCE_VERBOSE", verbose);
            }
        }
        else
        {
            readBoolEnv("OPENSHIM_UI_PERFORMANCE_LOGGING", enabled);
            readBoolEnv("OPENSHIM_UI_PERFORMANCE_VERBOSE", verbose);
        }

        // Always honour env var as final override when it is set, regardless of ini.
        bool envEnabled = false;
        if (readBoolEnv("OPENSHIM_UI_PERFORMANCE_LOGGING", envEnabled)) enabled = envEnabled;
        if (readBoolEnv("OPENSHIM_UI_PERFORMANCE_VERBOSE", envEnabled)) verbose = envEnabled;

        g_Enabled.store(enabled, std::memory_order_relaxed);
        g_Verbose.store(verbose, std::memory_order_relaxed);

        LogShimA(LogLevel::Info, kComponent,
            "UiPerformance init enabled=%d verbose=%d ini=%s",
            enabled ? 1 : 0, verbose ? 1 : 0, iniPath.c_str());
    }

    bool IsEnabled() noexcept { return g_Enabled.load(std::memory_order_relaxed); }
    bool IsVerbose() noexcept { return g_Verbose.load(std::memory_order_relaxed); }

    uint64_t NowTicks() noexcept
    {
        LARGE_INTEGER v{};
        QueryPerformanceCounter(&v);
        return static_cast<uint64_t>(v.QuadPart);
    }

    double TicksToMs(uint64_t ticks) noexcept
    {
        const uint64_t freq = QpcFrequency();
        if (freq == 0) return 0.0;
        return (static_cast<double>(ticks) * 1000.0) / static_cast<double>(freq);
    }

    double TicksToUs(uint64_t ticks) noexcept
    {
        const uint64_t freq = QpcFrequency();
        if (freq == 0) return 0.0;
        return (static_cast<double>(ticks) * 1'000'000.0) / static_cast<double>(freq);
    }

    // ------------------------------------------------------------------
    // ScopedPhase
    // ------------------------------------------------------------------
    ScopedPhase::ScopedPhase(const char* name)
        : m_name(name)
        , m_start(NowTicks())
        , m_depth(t_state.depth)
        , m_active(IsEnabled())
    {
        if (!m_active) return;
        // Emit BEGIN line.
        const std::string indent = IndentForDepth(m_depth);
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sBEGIN %s", indent.c_str(), m_name ? m_name : "<unnamed>");
        EmitLocked(line);
        ++t_state.depth;
        // Enable verbose buffering if requested.
        if (IsVerbose() && !t_state.bufferActive)
        {
            t_state.bufferActive = true;
            t_state.verboseBuffer.clear();
        }
    }

    ScopedPhase::ScopedPhase(const std::string& name)
        : m_owned(name)
        , m_start(NowTicks())
        , m_depth(t_state.depth)
        , m_active(IsEnabled())
    {
        m_name = m_owned.c_str();
        if (!m_active) return;
        const std::string indent = IndentForDepth(m_depth);
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sBEGIN %s", indent.c_str(), m_name);
        EmitLocked(line);
        ++t_state.depth;
        if (IsVerbose() && !t_state.bufferActive)
        {
            t_state.bufferActive = true;
            t_state.verboseBuffer.clear();
        }
    }

    ScopedPhase::~ScopedPhase()
    {
        if (!m_active || m_dismissed) return;
        const uint64_t end = NowTicks();
        const double ms = TicksToMs(end - m_start);
        // Depth was incremented in ctor; END is at the original depth.
        if (t_state.depth > 0) --t_state.depth;
        const std::string indent = IndentForDepth(m_depth);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sEND %s %.2fms", indent.c_str(), m_name ? m_name : "<unnamed>", ms);
        EmitLocked(line);

        // If this was the outermost phase, flush verbose buffer.
        if (t_state.depth == 0 && t_state.bufferActive)
        {
            for (const auto& v : t_state.verboseBuffer)
                EmitLocked(v.c_str());
            t_state.verboseBuffer.clear();
            t_state.bufferActive = false;
        }
    }

    void ScopedPhase::Annotate(const char* key, const char* value)
    {
        if (!m_active || !IsVerbose()) return;
        const std::string indent = IndentForDepth(m_depth + 1);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %s%s=%s", indent.c_str(), key ? key : "?", value ? value : "");
        BufferOrEmitVerbose(line);
    }

    void ScopedPhase::Annotate(const char* key, int64_t value)
    {
        if (!m_active || !IsVerbose()) return;
        const std::string indent = IndentForDepth(m_depth + 1);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %s%s=%lld", indent.c_str(), key ? key : "?", static_cast<long long>(value));
        BufferOrEmitVerbose(line);
    }

    void ScopedPhase::Annotate(const char* key, uint64_t value)
    {
        if (!m_active || !IsVerbose()) return;
        const std::string indent = IndentForDepth(m_depth + 1);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %s%s=%llu", indent.c_str(), key ? key : "?", static_cast<unsigned long long>(value));
        BufferOrEmitVerbose(line);
    }

    void ScopedPhase::Annotate(const char* key, double valueMs)
    {
        if (!m_active || !IsVerbose()) return;
        const std::string indent = IndentForDepth(m_depth + 1);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %s%s=%.2fms", indent.c_str(), key ? key : "?", valueMs);
        BufferOrEmitVerbose(line);
    }

    // ------------------------------------------------------------------
    // ScopedTransition
    // ------------------------------------------------------------------
    ScopedTransition::ScopedTransition(const char* label)
        : m_label(label ? label : "<unknown>")
        , m_start(NowTicks())
        , m_active(IsEnabled())
    {
        if (!m_active) return;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            g_ActiveTransitionLabel = m_label;
            g_ActiveTransitionStart = m_start;
            g_TransitionActive = true;
            ResetCategoryBucketsLocked();
        }
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition begin %s", m_label.c_str());
        EmitLocked(line);
        // Start stall heartbeat baseline.
        t_state.lastHeartbeatTicks = m_start;
        t_state.lastMarker = "transition_begin";
    }

    ScopedTransition::ScopedTransition(const std::string& label)
        : m_label(label)
        , m_start(NowTicks())
        , m_active(IsEnabled())
    {
        if (!m_active) return;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            g_ActiveTransitionLabel = m_label;
            g_ActiveTransitionStart = m_start;
            g_TransitionActive = true;
            ResetCategoryBucketsLocked();
        }
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition begin %s", m_label.c_str());
        EmitLocked(line);
        t_state.lastHeartbeatTicks = m_start;
        t_state.lastMarker = "transition_begin";
    }

    ScopedTransition::~ScopedTransition()
    {
        if (!m_active) return;
        const uint64_t end = NowTicks();
        const double totalMs = TicksToMs(end - m_start);
        char line[256] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition end   %s elapsed=%.2fms",
            m_label.c_str(), totalMs);
        EmitLocked(line);

        std::string summary;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            summary = FormatSummaryLocked(m_label.c_str(), totalMs);
            g_TransitionActive = false;
        }
        EmitLocked(summary.c_str());

        // Flush verbose buffer if any.
        if (t_state.bufferActive)
        {
            for (const auto& v : t_state.verboseBuffer)
                EmitLocked(v.c_str());
            t_state.verboseBuffer.clear();
            t_state.bufferActive = false;
        }
        t_state.depth = 0;
    }

    void ScopedTransition::AddCategoryTime(const char* category, double ms) noexcept
    {
        if (!m_active || !category) return;
        std::lock_guard<std::mutex> lock(g_Mutex);
        auto& b = g_CategoryBuckets[category];
        b.totalMs += ms;
        b.calls += 1;
    }

    void ScopedTransition::AddCategoryTime(const char* category, uint64_t ticks) noexcept
    {
        AddCategoryTime(category, TicksToMs(ticks));
    }

    void ScopedTransition::Note(const char* fmt, ...)
    {
        if (!m_active || !fmt) return;
        char buf[512] = {};
        va_list args;
        va_start(args, fmt);
        _vsnprintf_s(buf, _countof(buf), _TRUNCATE, fmt, args);
        va_end(args);
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_ActiveNotes.emplace_back(buf);
    }

    // ------------------------------------------------------------------
    // Counters & helpers
    // ------------------------------------------------------------------
    void RecordScan(const ScanCounters& c) noexcept
    {
        if (!IsEnabled()) return;
        const int depth = t_state.depth;
        const std::string indent = IndentForDepth(depth);
        char line[768] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF][SCAN] %sroot=%s directories=%u files=%u opened=%u odf=%u bzn=%u trn=%u des=%u ini=%u dup=%u workshopItems=%u elapsed=%.2fms",
            indent.c_str(),
            c.root ? c.root : "<unknown>",
            c.directories, c.files, c.filesOpened,
            c.odf, c.bzn, c.trn, c.des, c.ini,
            c.duplicatePaths, c.workshopItems,
            c.elapsedMs);
        EmitLocked(line);
        if (IsEnabled())
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            if (g_TransitionActive)
            {
                auto& b = g_CategoryBuckets["filesystem"];
                b.totalMs += c.elapsedMs;
                b.calls += 1;
            }
        }
    }

    void RecordOgreResourceOp(const char* op, const char* group, double elapsedMs, bool fromCache) noexcept
    {
        if (!IsEnabled()) return;
        const int depth = t_state.depth;
        const std::string indent = IndentForDepth(depth);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF][OGRE] %s%s group=%s elapsed=%.2fms%s",
            indent.c_str(),
            op ? op : "unknown",
            group ? group : "<none>",
            elapsedMs,
            fromCache ? " (cached)" : "");
        EmitLocked(line);
        if (g_TransitionActive)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            auto& b = g_CategoryBuckets["ogre"];
            b.totalMs += elapsedMs;
            b.calls += 1;
        }
    }

    void RecordOgreScriptStats(const OgreScriptStats& s) noexcept
    {
        if (!IsEnabled()) return;
        const int depth = t_state.depth;
        const std::string indent = IndentForDepth(depth);
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF][OGRE] %sScriptParse files=%u materials=%u programs=%u elapsed=%.2fms",
            indent.c_str(),
            s.filesParsed, s.materialsParsed, s.programsParsed, s.elapsedMs);
        EmitLocked(line);
    }

    void RecordShaderCache(uint32_t hits, uint32_t misses, double elapsedMs) noexcept
    {
        if (!IsEnabled()) return;
        const int depth = t_state.depth;
        const std::string indent = IndentForDepth(depth);
        char line[384] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF][SHADER] %scache_hits=%u cache_misses=%u elapsed=%.2fms",
            indent.c_str(), hits, misses, elapsedMs);
        EmitLocked(line);
        if (g_TransitionActive)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            auto& b = g_CategoryBuckets["shader"];
            b.totalMs += elapsedMs;
            b.calls += 1;
        }
    }

    void Heartbeat(const char* marker) noexcept
    {
        if (!IsEnabled()) return;
        const uint64_t now = NowTicks();
        if (t_state.lastHeartbeatTicks == 0)
        {
            t_state.lastHeartbeatTicks = now;
            t_state.lastMarker = marker;
            return;
        }
        const double gapMs = TicksToMs(now - t_state.lastHeartbeatTicks);
        const double threshold = g_StallThresholdMs.load(std::memory_order_relaxed);
        if (gapMs >= threshold)
        {
            char line[512] = {};
            _snprintf_s(line, _countof(line), _TRUNCATE,
                "[UIPERF][STALL] %.2fms previous_marker=%s next_marker=%s",
                gapMs,
                t_state.lastMarker ? t_state.lastMarker : "<none>",
                marker ? marker : "<none>");
            EmitLocked(line);
        }
        t_state.lastHeartbeatTicks = now;
        t_state.lastMarker = marker;
    }

    void SetStallThresholdMs(double ms) noexcept
    {
        if (ms < 1.0) ms = 1.0;
        g_StallThresholdMs.store(ms, std::memory_order_relaxed);
    }

    void EmitSummary(const char* label, uint64_t startTicks, uint64_t endTicks) noexcept
    {
        if (!IsEnabled()) return;
        const double totalMs = TicksToMs(endTicks - startTicks);
        char line[256] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition end   %s elapsed=%.2fms (emit)",
            label ? label : "<unknown>", totalMs);
        EmitLocked(line);
        std::string summary;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            summary = FormatSummaryLocked(label, totalMs);
        }
        EmitLocked(summary.c_str());
    }

    void Log(const char* fmt, ...) noexcept
    {
        if (!IsEnabled()) return;
        va_list args;
        va_start(args, fmt);
        LogLocked(LogLevel::Info, fmt, args);
        va_end(args);
    }

    void LogVerbose(const char* fmt, ...) noexcept
    {
        if (!IsEnabled() || !IsVerbose()) return;
        char buf[768] = {};
        va_list args;
        va_start(args, fmt);
        _vsnprintf_s(buf, _countof(buf), _TRUNCATE, fmt, args);
        va_end(args);
        const int depth = t_state.depth;
        const std::string indent = IndentForDepth(depth);
        std::string line = "[UIPERF] ";
        line += indent;
        line += buf;
        BufferOrEmitVerbose(line);
    }

    void Flush() noexcept
    {
        if (t_state.bufferActive)
        {
            for (const auto& v : t_state.verboseBuffer)
                EmitLocked(v.c_str());
            t_state.verboseBuffer.clear();
            t_state.bufferActive = false;
        }
    }

    void NotifyShellRequest(int screenId) noexcept
    {
        if (!IsEnabled()) return;
        const char* name = ShellScreenName(screenId);
        char label[128] = {};
        if (name)
            _snprintf_s(label, _countof(label), _TRUNCATE, "ShellRequest->%s(0x%02X)", name, screenId);
        else
            _snprintf_s(label, _countof(label), _TRUNCATE, "ShellRequest->Screen0x%02X", screenId);

        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            // If a transition is already active, close it first (back-to-back requests).
            if (g_TransitionActive)
            {
                const uint64_t now = NowTicks();
                const double totalMs = TicksToMs(now - g_ActiveTransitionStart);
                std::string summary = FormatSummaryLocked(g_ActiveTransitionLabel.c_str(), totalMs);
                EmitLocked(summary.c_str());
            }
            g_ActiveTransitionLabel = label;
            g_ActiveTransitionStart = NowTicks();
            g_TransitionActive = true;
            ResetCategoryBucketsLocked();
            // Need to re-set label after reset.
            g_ActiveTransitionLabel = label;
        }
        char line[256] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition begin %s", label);
        EmitLocked(line);
        t_state.lastHeartbeatTicks = NowTicks();
        t_state.lastMarker = "ShellRequest";
    }

    void NotifyShellTransitionComplete() noexcept
    {
        if (!IsEnabled()) return;
        std::string label;
        uint64_t start = 0;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            if (!g_TransitionActive) return;
            label = g_ActiveTransitionLabel;
            start = g_ActiveTransitionStart;
        }
        const uint64_t now = NowTicks();
        const double totalMs = TicksToMs(now - start);
        char line[256] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] transition end   %s elapsed=%.2fms",
            label.c_str(), totalMs);
        EmitLocked(line);
        std::string summary;
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            summary = FormatSummaryLocked(label.c_str(), totalMs);
            g_TransitionActive = false;
        }
        EmitLocked(summary.c_str());
    }

    const char* ShellScreenName(int id) noexcept
    {
        return ScreenNameTable(id);
    }

} // namespace BZROpenShim::UiPerf
