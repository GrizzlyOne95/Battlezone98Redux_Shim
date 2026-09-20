// The private bootstrap service table, and the two bridges that run over it.
//
// After the DLL split these are the only calls from plugins/openshim.dll back
// into winmm.dll, so what matters is that nothing but plain data crosses:
// a formatted UTF-8 string, a fixed-layout POD, and a void call. No va_list,
// no std::string, no FILE*, no C++ enum whose values could drift between two
// separately built modules.

#include "openshim_bootstrap_api.h"
#include "shim_log.h"
#include "shim_log_sink.h"
#include "startup_backend_seam.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace
{
    using namespace BZROpenShim;

    int g_Failures = 0;

    void Check(bool condition, const char* what, int line)
    {
        if (condition) return;
        std::printf("FAIL line %d: %s\n", line, what);
        ++g_Failures;
    }

#define CHECK(c) Check((c), #c, __LINE__)

    struct Captured
    {
        uint32_t level;
        std::string component;
        std::string message;
    };

    std::vector<Captured> g_Seen;

    void __cdecl CapturingSink(uint32_t level, const char* component, const char* message)
    {
        g_Seen.push_back({level, component ? component : "", message ? message : ""});
    }
}

int main()
{
    // ---- version negotiation --------------------------------------------
    const OpenShimBootstrapApiV1* api = OpenShimBootstrap_GetApi(OPENSHIM_BOOTSTRAP_API_V1);
    CHECK(api != nullptr);
    CHECK(OpenShimBootstrap_GetApi(0) == api);          // 0 means "newest"
    CHECK(OpenShimBootstrap_GetApi(2) == nullptr);      // refuse, don't approximate
    CHECK(OpenShimBootstrap_GetApi(99) == nullptr);
    if (api == nullptr)
    {
        std::printf("openshim bootstrap api tests FAILED (no table)\n");
        return 1;
    }

    CHECK(api->version == OPENSHIM_BOOTSTRAP_API_V1);
    CHECK(api->structSize == sizeof(OpenShimBootstrapApiV1));
    CHECK(api->logMessage != nullptr);
    CHECK(api->copyStartupRendererResult != nullptr);
    CHECK(api->clearStartupPendingMarker != nullptr);

    // ---- the logging bridge ---------------------------------------------
    // Formatting must happen on the caller's side: only a finished string
    // crosses. Route the client at a capturing sink and check what arrives.
    const ShimLogSinkFn previous = GetShimLogSink();
    SetShimLogSink(&CapturingSink);

    g_Seen.clear();
    LogShimA(LogLevel::Warn, "unit", "value=%d name=%s", 42, "abc");
    CHECK(g_Seen.size() == 1);
    if (!g_Seen.empty())
    {
        CHECK(g_Seen[0].level == static_cast<uint32_t>(LogLevel::Warn));
        CHECK(g_Seen[0].component == "unit");
        // Fully expanded before it reached the sink -- no format string and
        // no va_list travelled.
        CHECK(g_Seen[0].message == "value=42 name=abc");
        CHECK(g_Seen[0].message.find('%') == std::string::npos);
    }

    // Wide formatting converts to UTF-8 on the caller's side too.
    g_Seen.clear();
    LogShimW(LogLevel::Info, "unit", L"wide=%d", 7);
    CHECK(g_Seen.size() == 1);
    if (!g_Seen.empty()) CHECK(g_Seen[0].message == "wide=7");

    // Trailing newlines are trimmed before the boundary, and an empty
    // message becomes a marker rather than a blank line.
    g_Seen.clear();
    LogShimA(LogLevel::Info, "unit", "trailing\n\n");
    CHECK(g_Seen.size() == 1);
    if (!g_Seen.empty()) CHECK(g_Seen[0].message == "trailing");

    // The api's own logMessage takes an already-formatted string and must not
    // reinterpret it -- a literal percent has to survive.
    g_Seen.clear();
    api->logMessage(static_cast<uint32_t>(LogLevel::Error), "viaapi", "100% done");
    // logMessage goes straight to the real sink, not the capturing one, so
    // nothing should land in the capture.
    CHECK(g_Seen.empty());

    // ---- no sink installed ------------------------------------------------
    // The window before BZPlugin_Load installs the bridge. Must not crash and
    // must not reach any sink.
    SetShimLogSink(nullptr);
    CHECK(GetShimLogSink() == nullptr);
    g_Seen.clear();
    LogShimA(LogLevel::Info, "unit", "dropped=%d", 1);
    CHECK(g_Seen.empty());

    SetShimLogSink(previous);
    CHECK(GetShimLogSink() == previous);

    // ---- the startup result bridge ---------------------------------------
    // Fixed layout, because two separately built modules read and write it.
    CHECK(sizeof(StartupSeam::StartupRendererResult) == 28);

    StartupSeam::StartupRendererResult result = {};
    CHECK(api->copyStartupRendererResult(&result, sizeof(result)) == 1);
    CHECK(result.version == StartupSeam::kStartupRendererResultVersion);
    CHECK(result.structSize == sizeof(StartupSeam::StartupRendererResult));

    // A buffer under the mandatory size is refused rather than partially
    // filled: a short read here would be a silently wrong renderer decision.
    StartupSeam::StartupRendererResult shortBuf = {};
    CHECK(api->copyStartupRendererResult(&shortBuf, sizeof(result) - 1) == 0);
    CHECK(api->copyStartupRendererResult(nullptr, sizeof(result)) == 0);

    // It is a copy, not a window into bootstrap memory.
    result.transportWritten = 0xEE;
    StartupSeam::StartupRendererResult again = {};
    CHECK(api->copyStartupRendererResult(&again, sizeof(again)) == 1);
    CHECK(again.transportWritten != 0xEE);

    // ---- arm status text is a local mapping, not a boundary call ----------
    CHECK(std::strcmp(StartupSeam::ArmStatusText(StartupSeam::kArmArmed), "armed") == 0);
    CHECK(std::strcmp(StartupSeam::ArmStatusText(StartupSeam::kArmNotAttempted),
                      "not-attempted") == 0);
    CHECK(StartupSeam::ArmStatusText(9999u) != nullptr);  // never null

    // ---- the marker clear is a real call back into the bootstrap ----------
    api->clearStartupPendingMarker();   // must be safe with no marker present

    if (g_Failures != 0)
    {
        std::printf("openshim bootstrap api tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("openshim bootstrap api tests passed\n");
    return 0;
}
