#pragma once
// ui_performance.h
// BZR Open Shim - UI Responsiveness / Stall Profiling & Optimization
//
// Hierarchical, opt-in [UIPERF] instrumentation for Battlezone 98 Redux menu
// transitions.  Default OFF (zero overhead path).  When enabled via
//   [Diagnostics] UiPerformanceLogging=true
//   [Diagnostics] UiPerformanceVerbose=false
// it records:
//   - wall-clock durations for every major shell/UI transition
//   - nested sub-phase timings (ModDiscovery, OgreResourceGroups, Shader, etc.)
//   - file/mod scan counters, Ogre ResourceGroup call counts/times,
//     shader cache hit/miss, and per-root elapsed
//   - long main-thread stall detection (heartbeat watchdog)
//
// Design constraints:
//   - Must not materially affect runtime when OFF: hot-path is a single
//     relaxed atomic bool check.
//   - QPC-based, microsecond resolution, QueryPerformanceCounter.
//
// SPDX-License-Identifier: MIT

#include <cstdint>
#include <string>

namespace BZROpenShim::UiPerf
{
    // Called once at startup to read openshim.ini [Diagnostics].
    void Initialize();
    bool IsEnabled() noexcept;
    bool IsVerbose() noexcept;

    // High-resolution monotonic timestamp (QPC ticks) and helpers.
    uint64_t NowTicks() noexcept;
    double TicksToMs(uint64_t ticks) noexcept;
    double TicksToUs(uint64_t ticks) noexcept;

    // ------------------------------------------------------------------
    // Hierarchical scoped timers.  Use RAII: BEGIN on construction, END on
    // destruction with elapsed.  Nesting is tracked per-thread via a simple
    // stack so BEGIN/END lines are indented and parent inclusive time is
    // computable offline.  If UiPerformanceLogging==false the ctor/dtor are
    // near-zero-cost (early-out).
    // ------------------------------------------------------------------
    class ScopedPhase
    {
    public:
        explicit ScopedPhase(const char* name);
        explicit ScopedPhase(const std::string& name);
        ~ScopedPhase();

        ScopedPhase(const ScopedPhase&) = delete;
        ScopedPhase& operator=(const ScopedPhase&) = delete;

        // Annotate current phase with a key=value string (verbose only buffered).
        void Annotate(const char* key, const char* value);
        void Annotate(const char* key, int64_t value);
        void Annotate(const char* key, uint64_t value);
        void Annotate(const char* key, double valueMs);

        // Mark this phase as not logging its END line (for long-lived probes).
        void Dismiss() noexcept { m_dismissed = true; }

    private:
        const char* m_name = nullptr;
        std::string m_owned;
        uint64_t m_start = 0;
        int m_depth = 0;
        bool m_active = false;
        bool m_dismissed = false;
    };

    // ------------------------------------------------------------------
    // Transition-level API: bracket a full UI transition (e.g. "MainMenu ->
    // Multiplayer") so a [UIPERF][SUMMARY] line is always emitted.
    // ------------------------------------------------------------------
    class ScopedTransition
    {
    public:
        explicit ScopedTransition(const char* label);
        explicit ScopedTransition(const std::string& label);
        ~ScopedTransition();

        ScopedTransition(const ScopedTransition&) = delete;
        ScopedTransition& operator=(const ScopedTransition&) = delete;

        // Allow sub-phases to contribute their elapsed to a coarse category
        // bucket.  Category names are free-form but the summary groups them.
        void AddCategoryTime(const char* category, double ms) noexcept;
        void AddCategoryTime(const char* category, uint64_t ticks) noexcept;

        // Attach a free-form note to the summary.
        void Note(const char* fmt, ...);

    private:
        std::string m_label;
        uint64_t m_start = 0;
        bool m_active = false;
    };

    // Immediate counters that can be emitted even without a surrounding phase.
    // All are no-ops when logging is OFF.

    // File/mod discovery counters.  Call once per scan root on completion.
    struct ScanCounters
    {
        const char* root = nullptr;          // e.g. "addon", "workshop/content/301650"
        uint32_t directories = 0;
        uint32_t files = 0;
        uint32_t filesOpened = 0;
        uint32_t odf = 0;
        uint32_t bzn = 0;
        uint32_t trn = 0;
        uint32_t des = 0;
        uint32_t ini = 0;
        uint32_t duplicatePaths = 0;
        uint32_t workshopItems = 0;
        double elapsedMs = 0.0;
    };
    void RecordScan(const ScanCounters& c) noexcept;

    // Ogre ResourceGroup stats.  Call after each resource-group operation.
    void RecordOgreResourceOp(const char* op,            // e.g. "initialiseResourceGroup"
                              const char* group,         // e.g. "Modable"
                              double elapsedMs,
                              bool fromCache = false) noexcept;

    // Ogre material/script discovery summary.
    struct OgreScriptStats
    {
        uint32_t filesParsed = 0;
        uint32_t materialsParsed = 0;
        uint32_t programsParsed = 0;
        double elapsedMs = 0.0;
    };
    void RecordOgreScriptStats(const OgreScriptStats& s) noexcept;

    // Shader cache summary.
    void RecordShaderCache(uint32_t hits, uint32_t misses, double elapsedMs) noexcept;

    // Generic stall/heartbeat.  Call once per frame on main thread with the
    // name of the last completed marker.  If the gap since the previous call
    // exceeds the stall threshold a [UIPERF][STALL] line is emitted.
    void Heartbeat(const char* marker) noexcept;
    void SetStallThresholdMs(double ms) noexcept;

    // Emit a summary line for the most recent (or active) transition.  Used
    // when a transition is driven by native code without an explicit
    // ScopedTransition wrapper.
    void EmitSummary(const char* transitionLabel, uint64_t startTicks, uint64_t endTicks) noexcept;

    // Low-level log helpers (component="uiperf").  These respect the global
    // enable flag; LogVerbose* additionally requires UiPerformanceVerbose.
    void Log(const char* fmt, ...) noexcept;
    void LogVerbose(const char* fmt, ...) noexcept;

    // Flush any buffered verbose lines.  Called automatically at transition End.
    void Flush() noexcept;

    // Shell/menu gate helpers: these wrap the native shell request/history
    // seam so transitions are auto-timed even without per-screen instrumentation.
    void NotifyShellRequest(int screenId) noexcept;
    void NotifyShellTransitionComplete() noexcept;
    const char* ShellScreenName(int id) noexcept;
} // namespace BZROpenShim::UiPerf
