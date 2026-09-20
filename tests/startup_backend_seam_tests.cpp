// The bootstrap startup renderer seam, with nothing else alive.
//
// This is the case that made the renderer seam different from the file-I/O
// seam: the intercepted Ogre::ConfigFile::load is the game's own read of
// Ogre.cfg, and getSetting("Render System") happens immediately after it. If
// the decision has not been made by the time that call returns, it is gone
// for this boot. On a warm-cache Steam start the load is reached in about a
// second, long before a plugin could be hosted -- so "the plugin will catch
// up" is not an available answer and the seam has to be self-sufficient.
//
// So that is what this exercises: no plugin, no OpenShim runtime, no patch
// thread, nothing initialised. Just openshim.ini on disk, and the question of
// whether Ogre.cfg is correct before the original load would run.
//
// The seam derives every path from GetModuleFileNameA(nullptr), so the
// fixture is written next to this test executable.

#include "startup_backend_seam.h"
#include "backend_selection.h"
#include "render_profile.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
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

    std::filesystem::path ExeDir()
    {
        char buffer[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }

    void WriteText(const std::filesystem::path& p, const std::string& text)
    {
        std::ofstream out(p, std::ios::binary | std::ios::trunc);
        out.write(text.data(), static_cast<std::streamsize>(text.size()));
    }

    std::string ReadText(const std::filesystem::path& p)
    {
        std::ifstream in(p, std::ios::binary);
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

    std::string RenderSystemLine(const std::string& cfg)
    {
        return std::string(
            BackendSelection::ExtractStockRenderSystemValue(cfg));
    }

    // The seam refuses to transport a backend whose plugin DLL is absent, so
    // the fixture has to provide a non-empty stand-in.
    void MakePlugin(const std::filesystem::path& p)
    {
        WriteText(p, "not a real dll, only presence and non-emptiness matter");
    }
}

int main()
{
    const std::filesystem::path dir = ExeDir();
    const auto ini = dir / "openshim.ini";
    const auto cfg = dir / "Ogre.cfg";
    const auto dx11 = dir / "RenderSystem_Direct3D11.dll";
    const auto dx9 = dir / "RenderSystem_Direct3D9.dll";

    std::error_code ec;
    for (const auto& p : {ini, cfg, dx11, dx9}) std::filesystem::remove(p, ec);

    const std::string stockCfg =
        "Render System=Direct3D9 Rendering Subsystem\r\n"
        "\r\n"
        "[Direct3D9 Rendering Subsystem]\r\n"
        "Full Screen=No\r\n";

    // ---- the dangerous case --------------------------------------------
    // Explicit DX11 request, plugin present, nothing else alive. Ogre.cfg
    // must already say DX11 by the time the seam returns.
    WriteText(ini, "[Graphics]\r\nRenderer=dx11\r\n");
    WriteText(cfg, stockCfg);
    MakePlugin(dx11);
    MakePlugin(dx9);

    StartupSeam::RunStartupSelectionForTest();

    const StartupSeam::StartupRendererResult* r =
        StartupSeam::GetStartupRendererResult();
    CHECK(r != nullptr);
    CHECK(r->version == StartupSeam::kStartupRendererResultVersion);
    CHECK(r->selectionRan != 0);
    CHECK(r->requested == RenderProfiles::RendererBackend::DX11);
    CHECK(r->source == BackendSelection::RequestSource::Persistent);
    CHECK(r->transportWritten != 0);
    CHECK(r->dx11Present != 0);
    CHECK(RenderSystemLine(ReadText(cfg)) == "Direct3D11 Rendering Subsystem");

    // Every other byte of the file has to survive the rewrite.
    const std::string after = ReadText(cfg);
    CHECK(after.find("[Direct3D9 Rendering Subsystem]\r\n") != std::string::npos);
    CHECK(after.find("Full Screen=No\r\n") != std::string::npos);

    // ---- the transport must not fire without a plugin DLL ---------------
    // Otherwise stock's ladder falls back and PERSISTS DX9 over the request.
    WriteText(cfg, stockCfg);
    std::filesystem::remove(dx11, ec);
    StartupSeam::RunStartupSelectionForTest();
    CHECK(StartupSeam::GetStartupRendererResult()->dx11Present == 0);
    CHECK(StartupSeam::GetStartupRendererResult()->transportWritten == 0);
    CHECK(RenderSystemLine(ReadText(cfg)) == "Direct3D9 Rendering Subsystem");
    MakePlugin(dx11);

    // ---- the kill switch -------------------------------------------------
    WriteText(ini, "[Graphics]\r\nRenderer=dx11\r\n[Startup]\r\nBackendTransport=0\r\n");
    WriteText(cfg, stockCfg);
    StartupSeam::RunStartupSelectionForTest();
    CHECK(StartupSeam::GetStartupRendererResult()->transportWritten == 0);
    CHECK(RenderSystemLine(ReadText(cfg)) == "Direct3D9 Rendering Subsystem");

    // ---- Auto is byte-identical stock behaviour --------------------------
    WriteText(ini, "[Graphics]\r\nRenderer=auto\r\n");
    WriteText(cfg, stockCfg);
    StartupSeam::RunStartupSelectionForTest();
    CHECK(StartupSeam::GetStartupRendererResult()->requested ==
          RenderProfiles::RendererBackend::Auto);
    CHECK(StartupSeam::GetStartupRendererResult()->transportWritten == 0);
    CHECK(ReadText(cfg) == stockCfg);

    // ---- an absent openshim.ini is Auto, and touches nothing -------------
    std::filesystem::remove(ini, ec);
    WriteText(cfg, stockCfg);
    StartupSeam::RunStartupSelectionForTest();
    CHECK(StartupSeam::GetStartupRendererResult()->transportWritten == 0);
    CHECK(ReadText(cfg) == stockCfg);

    // ---- DX9 request rewrites too ----------------------------------------
    WriteText(ini, "[Graphics]\r\nRenderer=dx9\r\n");
    WriteText(cfg,
              "Render System=Direct3D11 Rendering Subsystem\r\n"
              "\r\n[Direct3D11 Rendering Subsystem]\r\nFull Screen=No\r\n");
    StartupSeam::RunStartupSelectionForTest();
    CHECK(StartupSeam::GetStartupRendererResult()->requested ==
          RenderProfiles::RendererBackend::DX9);
    CHECK(StartupSeam::GetStartupRendererResult()->transportWritten != 0);
    CHECK(RenderSystemLine(ReadText(cfg)) == "Direct3D9 Rendering Subsystem");

    // ---- a missing Ogre.cfg is created, not skipped ----------------------
    WriteText(ini, "[Graphics]\r\nRenderer=dx11\r\n");
    std::filesystem::remove(cfg, ec);
    StartupSeam::RunStartupSelectionForTest();
    CHECK(std::filesystem::exists(cfg));
    CHECK(RenderSystemLine(ReadText(cfg)) == "Direct3D11 Rendering Subsystem");

    // ---- no temp file is left behind -------------------------------------
    const std::string tmpName =
        BackendSelection::MakeTransportTempFileName(GetCurrentProcessId());
    CHECK(!std::filesystem::exists(dir / tmpName));

    for (const auto& p : {ini, cfg, dx11, dx9}) std::filesystem::remove(p, ec);
    std::filesystem::remove(dir / "openshim_backend_pending.marker", ec);

    if (g_Failures != 0)
    {
        std::printf("startup backend seam tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("startup backend seam tests passed\n");
    return 0;
}
