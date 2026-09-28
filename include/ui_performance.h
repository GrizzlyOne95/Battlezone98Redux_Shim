#pragma once
// ui_performance.h
// BZR Open Shim - UI Responsiveness / Stall Profiling & Optimization
//
// Hierarchical, opt-in [UIPERF] instrumentation for Battlezone 98 Redux menu
// transitions.  Default OFF (zero overhead path).  When enabled via
//   [Diagnostics] UiPerformanceLogging=true
//   [Diagnostics] UiPerformanceVerbose=false
// (UiPerformanceVerbose is still read and echoed on the init line, but no
// output depends on it since the unused verbose-buffer API was removed.)
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

    // High-resolution monotonic timestamp (QPC ticks) and helpers.
    uint64_t NowTicks() noexcept;
    double TicksToMs(uint64_t ticks) noexcept;

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
        explicit ScopedPhase(const char* name, const char* category = nullptr);
        explicit ScopedPhase(const std::string& name, const char* category = nullptr);
        ~ScopedPhase();

        ScopedPhase(const ScopedPhase&) = delete;
        ScopedPhase& operator=(const ScopedPhase&) = delete;

    private:
        const char* m_name = nullptr;
        std::string m_owned;
        std::string m_category;
        uint64_t m_start = 0;
        int m_depth = 0;
        bool m_active = false;
        bool m_hasCategory = false;
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
        double elapsedMs = 0.0;       // inclusive enumeration lifetime
        double exclusiveMs = 0.0;     // time inside hooked filesystem APIs
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

    // Low-level log helper (component="uiperf").  Respects the global enable
    // flag.
    void Log(const char* fmt, ...) noexcept;

    // Shell/menu gate helpers: these wrap the native shell request/history
    // seam so transitions are auto-timed even without per-screen instrumentation.
    void NotifyShellRequest(int screenId) noexcept;
    void NotifyShellTransitionComplete() noexcept;
    const char* ShellScreenName(int id) noexcept;
} // namespace BZROpenShim::UiPerf
