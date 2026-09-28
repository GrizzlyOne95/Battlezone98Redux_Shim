// ui_performance.cpp
// BZR Open Shim - UI Responsiveness / Stall Profiling implementation
//
// See include/ui_performance.h for design.  Key properties:
//  - Hot path when OFF: single relaxed atomic load + early return.
//  - Hierarchical depth tracked thread-local; indentation derived from depth.
//  - Summary buckets accumulated per transition and emitted at transition End.
//  - QPC-based monotonic timer.
//  - All public entry points are noexcept and never throw.
//
// SPDX-License-Identifier: MIT

#include "ui_performance.h"
#include "bool_token.h"
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
        constexpr double kStallThresholdMs = 250.0;

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_Initialized{ false };

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
        };
        thread_local ThreadState t_state;

        // Category stack for exclusive vs inclusive accounting.
        // Ogre parseScripts synchronously performs filesystem work, so inclusive
        // Ogre and inclusive filesystem overlap. We keep exclusive buckets for
        // percentages and inclusive diagnostics separate.
        struct CatStackEntry
        {
            std::string category;
            uint64_t startTicks = 0;
            double childMs = 0.0;
        };
        thread_local std::vector<CatStackEntry> t_catStack;

        // Transition-level aggregation (protected by mutex because shell
        // notifications and the scan/Ogre recorders can run on other threads).
        struct CategoryBucket
        {
            double totalMs = 0.0; // exclusive for percentages
            double inclusiveMs = 0.0; // diagnostic inclusive
            uint32_t calls = 0;
        };
        std::mutex g_Mutex;
        std::unordered_map<std::string, CategoryBucket> g_CategoryBuckets;
        std::string g_ActiveTransitionLabel;
        uint64_t g_ActiveTransitionStart = 0;
        bool g_TransitionActive = false;

        static void AddLeafCategoryTimeLocked(const char* category, double ms) noexcept
        {
            if (!category || ms <= 0.0) return;
            // If we are inside a parent category, record overlap so parent's
            // exclusive is reduced.
            if (!t_catStack.empty())
            {
                t_catStack.back().childMs += ms;
            }
            // Caller holds g_Mutex.
            auto& b = g_CategoryBuckets[category];
            b.totalMs += ms;
            b.inclusiveMs += ms;
            b.calls += 1;
        }

        static void PopCategoryLocked(const std::string& cat, uint64_t end) noexcept
        {
            if (t_catStack.empty()) return;
            CatStackEntry entry = t_catStack.back();
            t_catStack.pop_back();
            // Defensive: allow mismatched pop due to early outs, just use entry's category.
            const double inclusive = TicksToMs(end - entry.startTicks);
            const double exclusive = inclusive > entry.childMs ? inclusive - entry.childMs : 0.0;
            auto& b = g_CategoryBuckets[entry.category];
            b.totalMs += exclusive;
            b.inclusiveMs += inclusive;
            b.calls += 1;
            if (!t_catStack.empty())
                t_catStack.back().childMs += inclusive;
            // If caller supplied different cat than stack top, also ensure that cat gets inclusive? No, trust stack.
            (void)cat;
        }

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

        void ResetCategoryBucketsLocked() noexcept
        {
            g_CategoryBuckets.clear();
            t_catStack.clear();
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
                double exclusiveSum = 0.0;
                for (const auto& kv : sorted)
                    exclusiveSum += kv.second.totalMs;
                const double unattributed = totalMs > exclusiveSum ? totalMs - exclusiveSum : 0.0;
                for (const auto& kv : sorted)
                {
                    char line[320] = {};
                    // Report exclusive for percentages; include inclusive in parentheses when it differs.
                    if (kv.second.inclusiveMs > kv.second.totalMs + 0.01)
                    {
                        _snprintf_s(line, _countof(line), _TRUNCATE,
                            "  %s=%.2fms (inclusive %.2fms) calls=%u",
                            kv.first.c_str(), kv.second.totalMs, kv.second.inclusiveMs, kv.second.calls);
                    }
                    else
                    {
                        _snprintf_s(line, _countof(line), _TRUNCATE,
                            "  %s=%.2fms calls=%u",
                            kv.first.c_str(), kv.second.totalMs, kv.second.calls);
                    }
                    out += "\n";
                    out += line;
                }
                // Always report unattributed exclusive remainder.
                {
                    char line[128] = {};
                    _snprintf_s(line, _countof(line), _TRUNCATE,
                        "  unattributed=%.2fms", unattributed);
                    out += "\n";
                    out += line;
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
            return BZROpenShim::BoolToken::TryParse(buf, len, out);
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
                BZROpenShim::BoolToken::TryParse(val, enabled);
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
                BZROpenShim::BoolToken::TryParse(val, verbose);
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

        LogShimA(LogLevel::Info, kComponent,
            "UiPerformance init enabled=%d verbose=%d ini=%s",
            enabled ? 1 : 0, verbose ? 1 : 0, iniPath.c_str());
    }

    bool IsEnabled() noexcept { return g_Enabled.load(std::memory_order_relaxed); }

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

    // ------------------------------------------------------------------
    // ScopedPhase
    // ------------------------------------------------------------------
    ScopedPhase::ScopedPhase(const char* name, const char* category)
        : m_name(name)
        , m_category(category ? category : "")
        , m_start(NowTicks())
        , m_depth(t_state.depth)
        , m_active(IsEnabled())
        , m_hasCategory(category && category[0])
    {
        if (!m_active) return;
        if (m_hasCategory)
        {
            // Push category stack for exclusive accounting.
            t_catStack.push_back(CatStackEntry{m_category, m_start, 0.0});
        }
        // Emit BEGIN line.
        const std::string indent = IndentForDepth(m_depth);
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sBEGIN %s", indent.c_str(), m_name ? m_name : "<unnamed>");
        EmitLocked(line);
        ++t_state.depth;
    }

    ScopedPhase::ScopedPhase(const std::string& name, const char* category)
        : m_owned(name)
        , m_category(category ? category : "")
        , m_start(NowTicks())
        , m_depth(t_state.depth)
        , m_active(IsEnabled())
        , m_hasCategory(category && category[0])
    {
        m_name = m_owned.c_str();
        if (!m_active) return;
        if (m_hasCategory)
        {
            t_catStack.push_back(CatStackEntry{m_category, m_start, 0.0});
        }
        const std::string indent = IndentForDepth(m_depth);
        char line[512] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sBEGIN %s", indent.c_str(), m_name);
        EmitLocked(line);
        ++t_state.depth;
    }

    ScopedPhase::~ScopedPhase()
    {
        if (!m_active) return;
        const uint64_t end = NowTicks();
        const double ms = TicksToMs(end - m_start);
        if (m_hasCategory)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            PopCategoryLocked(m_category, end);
        }
        // Depth was incremented in ctor; END is at the original depth.
        if (t_state.depth > 0) --t_state.depth;
        const std::string indent = IndentForDepth(m_depth);
        char line[640] = {};
        _snprintf_s(line, _countof(line), _TRUNCATE,
            "[UIPERF] %sEND %s %.2fms", indent.c_str(), m_name ? m_name : "<unnamed>", ms);
        EmitLocked(line);
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
            "[UIPERF][SCAN] %sroot=%s directories=%u files=%u opened=%u odf=%u bzn=%u trn=%u des=%u ini=%u dup=%u workshopItems=%u elapsed=%.2fms exclusive=%.2fms",
            indent.c_str(),
            c.root ? c.root : "<unknown>",
            c.directories, c.files, c.filesOpened,
            c.odf, c.bzn, c.trn, c.des, c.ini,
            c.duplicatePaths, c.workshopItems,
            c.elapsedMs, c.exclusiveMs);
        EmitLocked(line);
        if (g_TransitionActive)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            AddLeafCategoryTimeLocked("filesystem", c.exclusiveMs);
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
            // Ogre ops may nest inside each other (e.g. initialise contains parse),
            // but we treat each as leaf for now; the category stack will handle
            // parent subtraction if caller used ScopedPhase with category "ogre".
            AddLeafCategoryTimeLocked("ogre", elapsedMs);
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
            AddLeafCategoryTimeLocked("shader", elapsedMs);
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
        if (gapMs >= kStallThresholdMs)
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

    void Log(const char* fmt, ...) noexcept
    {
        if (!IsEnabled()) return;
        va_list args;
        va_start(args, fmt);
        LogLocked(LogLevel::Info, fmt, args);
        va_end(args);
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
