// The bootstrap file-I/O seam, driven through the real mechanism.
//
// This patches the test executable's own import table with the real wrappers
// and then calls CreateFileW/A normally, so the calls arrive the same way the
// game's do. What it is checking is the lifecycle the split introduced:
//
//     no provider -> early open -> install provider -> runtime open
//
// The pre-provider half is the part that did not exist before. Until OpenShim
// loads, the wrappers must still route the stock logs, open the file, and
// preserve GetLastError -- and must not need anything else to be alive.

#include "bootstrap_file_io.h"
#include "game_log_path.h"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>

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

    // --- provider observations -----------------------------------------
    struct Observation
    {
        bool routeCalledW = false;
        bool routeCalledA = false;
        bool openedCalledW = false;
        bool openedCalledA = false;
        std::wstring lastRequestedW;
        std::wstring lastRoutedW;
        std::string lastRequestedA;
        std::string lastRoutedA;
        std::wstring redirectFromW;
        std::wstring redirectToW;
        DWORD lastAccess = 0;
        DWORD lastDisposition = 0;
    };

    Observation g_Seen;
    thread_local std::wstring g_RouteBufferW;

    const wchar_t* __cdecl RoutePathW(const wchar_t* path, DWORD, DWORD)
    {
        g_Seen.routeCalledW = true;
        if (!path || g_Seen.redirectFromW.empty()) return nullptr;
        if (g_Seen.redirectFromW != path) return nullptr;
        g_RouteBufferW = g_Seen.redirectToW;
        return g_RouteBufferW.c_str();
    }

    const char* __cdecl RoutePathA(const char*, DWORD, DWORD)
    {
        g_Seen.routeCalledA = true;
        return nullptr;
    }

    void __cdecl OnOpenedW(HANDLE handle, const wchar_t* requested,
                           const wchar_t* routed, DWORD access, DWORD disposition)
    {
        g_Seen.openedCalledW = true;
        g_Seen.lastRequestedW = requested ? requested : L"";
        g_Seen.lastRoutedW = routed ? routed : L"";
        g_Seen.lastAccess = access;
        g_Seen.lastDisposition = disposition;
        CHECK(handle != INVALID_HANDLE_VALUE);
    }

    void __cdecl OnOpenedA(HANDLE, const char* requested, const char* routed,
                           DWORD, DWORD)
    {
        g_Seen.openedCalledA = true;
        g_Seen.lastRequestedA = requested ? requested : "";
        g_Seen.lastRoutedA = routed ? routed : "";
    }

    std::filesystem::path ExeDirectory()
    {
        wchar_t buffer[MAX_PATH] = {};
        GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }

    bool WriteThrough(const std::wstring& path)
    {
        const HANDLE h = ::CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr,
                                       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (h == INVALID_HANDLE_VALUE) return false;
        DWORD written = 0;
        WriteFile(h, "x", 1, &written, nullptr);
        CloseHandle(h);
        return true;
    }
}

int wmain()
{
    const std::filesystem::path exeDir = ExeDirectory();
    std::filesystem::current_path(exeDir);

    // ---- the seam installs into a real import table --------------------
    const int patched =
        BootstrapFileIo::PatchCreateFileHooksForModule(GetModuleHandleW(nullptr));
    CHECK(patched == 2);
    CHECK(BootstrapFileIo::GetProvider() == nullptr);

    // ---- no provider: opens still work ---------------------------------
    const std::wstring plain = (exeDir / L"bootstrap_seam_plain.tmp").wstring();
    CHECK(WriteThrough(plain));
    CHECK(std::filesystem::exists(plain));

    // ...and GetLastError survives the wrapper's own bookkeeping.
    SetLastError(ERROR_SUCCESS);
    const HANDLE missing = ::CreateFileW(
        (exeDir / L"definitely_not_here_bootstrap.tmp").wstring().c_str(),
        GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    const DWORD failureError = GetLastError();
    CHECK(missing == INVALID_HANDLE_VALUE);
    CHECK(failureError == ERROR_FILE_NOT_FOUND);

    // ---- no provider: the stock logs are still routed ------------------
    // This is the behaviour the bootstrap has to keep on its own. A bare
    // "*.log" name lands under logs\, not next to the executable.
    // Clear both candidate locations first. A previous failed run that wrote
    // the log next to the executable would otherwise make the "not here"
    // assertion below fail on a perfectly good build.
    const std::filesystem::path logsDir = exeDir / "logs";
    for (const auto& dir : {logsDir, exeDir})
    {
        std::error_code ec;
        std::filesystem::remove(dir / "bootstrap_seam.log", ec);
        std::filesystem::remove(dir / "bootstrap_seam2.log", ec);
        std::filesystem::remove(dir / "BZLogger.txt", ec);
    }
    CHECK(WriteThrough(L"bootstrap_seam.log"));
    CHECK(std::filesystem::exists(logsDir / "bootstrap_seam.log"));
    CHECK(!std::filesystem::exists(exeDir / "bootstrap_seam.log"));

    // BZLogger.txt is routed by name rather than by extension.
    std::filesystem::remove(logsDir / "BZLogger.txt");
    CHECK(WriteThrough(L"BZLogger.txt"));
    CHECK(std::filesystem::exists(logsDir / "BZLogger.txt"));

    // A path that already has a directory is left alone.
    CHECK(WriteThrough((exeDir / L"bootstrap_seam_kept.log").wstring()));
    CHECK(std::filesystem::exists(exeDir / "bootstrap_seam_kept.log"));

    // Nothing above should have needed a provider.
    CHECK(!g_Seen.openedCalledW);
    CHECK(!g_Seen.routeCalledW);

    // ---- install the runtime policy ------------------------------------
    const BootstrapFileIo::Provider provider = {
        sizeof(BootstrapFileIo::Provider), RoutePathW, RoutePathA, OnOpenedW, OnOpenedA,
    };
    CHECK(BootstrapFileIo::InstallProvider(&provider));
    CHECK(BootstrapFileIo::GetProvider() == &provider);

    // A plain open now reaches the provider, and reports both names.
    g_Seen = Observation{};
    CHECK(WriteThrough(plain));
    CHECK(g_Seen.routeCalledW);
    CHECK(g_Seen.openedCalledW);
    CHECK(g_Seen.lastRequestedW == plain);
    CHECK(g_Seen.lastRoutedW == plain);
    CHECK(g_Seen.lastDisposition == CREATE_ALWAYS);

    // The requested and routed names must stay distinguishable: the shader
    // cache and TRN tracking key off what the caller asked for, while load
    // tracing follows what was really opened.
    g_Seen = Observation{};
    const std::wstring from = (exeDir / L"bootstrap_seam_from.tmp").wstring();
    const std::wstring to = (exeDir / L"bootstrap_seam_to.tmp").wstring();
    std::filesystem::remove(to);
    g_Seen.redirectFromW = from;
    g_Seen.redirectToW = to;
    CHECK(WriteThrough(from));
    CHECK(g_Seen.lastRequestedW == from);
    CHECK(g_Seen.lastRoutedW == to);
    CHECK(std::filesystem::exists(to));
    CHECK(!std::filesystem::exists(from));

    // Log routing happens before the provider sees the path, so a provider
    // observes the routed log name rather than the bare one.
    g_Seen = Observation{};
    g_Seen.redirectFromW.clear();
    CHECK(WriteThrough(L"bootstrap_seam2.log"));
    CHECK(g_Seen.lastRequestedW == L"bootstrap_seam2.log");
    CHECK(g_Seen.lastRoutedW.find(L"logs") != std::wstring::npos);

    // ANSI path goes through its own wrapper.
    g_Seen = Observation{};
    const std::string ansi = (exeDir / "bootstrap_seam_ansi.tmp").string();
    const HANDLE ah = ::CreateFileA(ansi.c_str(), GENERIC_WRITE, 0, nullptr,
                                    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    CHECK(ah != INVALID_HANDLE_VALUE);
    if (ah != INVALID_HANDLE_VALUE) CloseHandle(ah);
    CHECK(g_Seen.routeCalledA);
    CHECK(g_Seen.openedCalledA);
    CHECK(g_Seen.lastRequestedA == ansi);

    // A failed open must not be reported as an open.
    g_Seen = Observation{};
    const HANDLE bad = ::CreateFileW(
        (exeDir / L"still_not_here_bootstrap.tmp").wstring().c_str(),
        GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    CHECK(bad == INVALID_HANDLE_VALUE);
    CHECK(!g_Seen.openedCalledW);

    // ---- append-only truncation ----------------------------------------
    // A provider built before a callback existed reports a shorter table, and
    // the seam must not call through the fields it does not have.
    const BootstrapFileIo::Provider truncated = {
        (uint32_t)offsetof(BootstrapFileIo::Provider, onOpenedW),
        RoutePathW, RoutePathA, OnOpenedW, OnOpenedA,
    };
    CHECK(BootstrapFileIo::InstallProvider(&truncated));
    g_Seen = Observation{};
    g_Seen.redirectFromW.clear();
    CHECK(WriteThrough(plain));
    CHECK(g_Seen.routeCalledW);     // inside the reported size
    CHECK(!g_Seen.openedCalledW);   // past it

    // A table too small to carry structSize is refused.
    BootstrapFileIo::Provider degenerate = provider;
    degenerate.structSize = 0;
    CHECK(!BootstrapFileIo::InstallProvider(&degenerate));
    CHECK(!BootstrapFileIo::InstallProvider(nullptr));

    // ---- cleanup --------------------------------------------------------
    for (const wchar_t* leaf : {L"bootstrap_seam_plain.tmp", L"bootstrap_seam_to.tmp",
                                L"bootstrap_seam_from.tmp", L"bootstrap_seam_ansi.tmp",
                                L"bootstrap_seam_kept.log"})
    {
        std::error_code ec;
        std::filesystem::remove(exeDir / leaf, ec);
    }
    for (const wchar_t* leaf : {L"bootstrap_seam.log", L"bootstrap_seam2.log",
                                L"BZLogger.txt"})
    {
        std::error_code ec;
        std::filesystem::remove(logsDir / leaf, ec);
    }

    if (g_Failures != 0)
    {
        std::printf("bootstrap file io tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("bootstrap file io tests passed\n");
    return 0;
}
