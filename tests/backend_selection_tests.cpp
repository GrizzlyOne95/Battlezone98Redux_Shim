// Backend-selection boot-request and transport decision tests. Pure logic:
// no engine, no game, no Win32. Build+run via
// scripts/run_backend_selection_tests.ps1.

#include "backend_selection.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>

using namespace BZROpenShim::BackendSelection;
using namespace std::string_literals;
using BZROpenShim::RenderProfiles::ActiveBackend;
using BZROpenShim::RenderProfiles::RendererBackend;

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }

    void ExpectToken(RendererToken actual, RendererToken expected, const char* what)
    {
        if (actual != expected)
        {
            std::printf("  FAIL: %s (actual=%u expected=%u)\n", what,
                        static_cast<unsigned>(actual), static_cast<unsigned>(expected));
            ++g_failures;
        }
    }

    void ExpectReason(SelectionReason actual, SelectionReason expected, const char* what)
    {
        if (actual != expected)
        {
            std::printf("  FAIL: %s (actual=%s expected=%s)\n", what,
                        ReasonName(actual), ReasonName(expected));
            ++g_failures;
        }
    }

    void ExpectStr(std::string_view actual, std::string_view expected, const char* what)
    {
        if (actual != expected)
        {
            std::printf("  FAIL: %s (actual='%.*s' expected='%.*s')\n", what,
                        static_cast<int>(actual.size()), actual.data(),
                        static_cast<int>(expected.size()), expected.data());
            ++g_failures;
        }
    }
}

void TestTokenClassification()
{
    std::printf("TestTokenClassification\n");
    ExpectToken(ClassifyRendererToken("dx9"), RendererToken::Dx9, "dx9");
    ExpectToken(ClassifyRendererToken("DX9"), RendererToken::Dx9, "DX9 case");
    ExpectToken(ClassifyRendererToken("d3d9"), RendererToken::Dx9, "d3d9 alias");
    ExpectToken(ClassifyRendererToken("DirectX9"), RendererToken::Dx9, "directx9 alias");
    ExpectToken(ClassifyRendererToken("dx11"), RendererToken::Dx11, "dx11");
    ExpectToken(ClassifyRendererToken("D3D11"), RendererToken::Dx11, "d3d11 alias");
    ExpectToken(ClassifyRendererToken("gl"), RendererToken::Gl, "gl");
    ExpectToken(ClassifyRendererToken("OpenGL"), RendererToken::Gl, "opengl alias");
    ExpectToken(ClassifyRendererToken(""), RendererToken::None, "empty token");
    ExpectToken(ClassifyRendererToken("garbage"), RendererToken::None, "garbage token");
    ExpectToken(ClassifyRendererToken("dx1"), RendererToken::None, "prefix trap dx1");
    ExpectToken(ClassifyRendererToken("dx11 "), RendererToken::None, "trailing space is not part of token");
}

void TestCommandLineScan()
{
    std::printf("TestCommandLineScan\n");
    ExpectToken(FindCommandLineRendererOverride(
                    "battlezone98redux.exe lcbench.bzn"), RendererToken::None,
                "no override");
    ExpectToken(FindCommandLineRendererOverride("/renderer:dx9"),
                RendererToken::Dx9, "/renderer:dx9");
    ExpectToken(FindCommandLineRendererOverride("-renderer=dx11"),
                RendererToken::Dx11, "-renderer=dx11");
    ExpectToken(FindCommandLineRendererOverride("+renderer:D3D9"),
                RendererToken::Dx9, "+renderer:D3D9 case-insensitive value");
    ExpectToken(FindCommandLineRendererOverride(
                    "game.exe /multi lcbench.bzn /RENDERER:DX11"),
                RendererToken::Dx11, "mixed args, uppercase key");
    ExpectToken(FindCommandLineRendererOverride(
                    "game.exe /renderer:dx9 /renderer:dx11"),
                RendererToken::Dx11, "last occurrence wins");
    ExpectToken(FindCommandLineRendererOverride(
                    "game.exe /renderer:dx11 /renderer:dx9"),
                RendererToken::Dx9, "last occurrence wins reversed");
    ExpectToken(FindCommandLineRendererOverride("renderer:dx9"),
                RendererToken::None, "missing introducer");
    ExpectToken(FindCommandLineRendererOverride("/rendered:dx9"),
                RendererToken::None, "wrong key");
    ExpectToken(FindCommandLineRendererOverride("/renderer:"),
                RendererToken::None, "missing value");
    ExpectToken(FindCommandLineRendererOverride("/renderer:gl"),
                RendererToken::Gl, "gl recognized on CLI");
    ExpectToken(FindCommandLineRendererOverride("/renderer:nonsense"),
                RendererToken::None, "unknown CLI value ignored");
    // A bare argument that merely CONTAINS the key text must not match.
    ExpectToken(FindCommandLineRendererOverride("/xrenderer:dx9"),
                RendererToken::None, "substring key rejected");
}

void TestBootRequestResolution()
{
    std::printf("TestBootRequestResolution\n");
    const BootRequest stock =
        ResolveBootRequest(RendererBackend::Auto, RendererToken::None);
    ExpectTrue(stock.backend == RendererBackend::Auto &&
                   stock.source == RequestSource::None,
               "auto+no-cli -> stock");

    const BootRequest persistent =
        ResolveBootRequest(RendererBackend::DX11, RendererToken::None);
    ExpectTrue(persistent.backend == RendererBackend::DX11 &&
                   persistent.source == RequestSource::Persistent,
               "persistent wins over no cli");

    const BootRequest cli =
        ResolveBootRequest(RendererBackend::DX11, RendererToken::Dx9);
    ExpectTrue(cli.backend == RendererBackend::DX9 &&
                   cli.source == RequestSource::CliOverride,
               "cli beats persistent for this boot");

    // GL is explicit but unsupported by the resolver space -> stock.
    const BootRequest gl =
        ResolveBootRequest(RendererBackend::Auto, RendererToken::Gl);
    ExpectTrue(gl.backend == RendererBackend::Auto && gl.source == RequestSource::None,
               "gl cli collapses to stock");

    const BootRequest glOverPersistent =
        ResolveBootRequest(RendererBackend::DX9, RendererToken::Gl);
    ExpectTrue(glOverPersistent.backend == RendererBackend::Auto,
                "gl cli over persistent still yields stock this boot");

    // Case B contract: a /renderer:gl boot must not consume or alter the
    // persistent preference — this boot collapses to stock selection and the
    // next normal boot re-asserts the stored request.
    const BootRequest glOverDx11 =
        ResolveBootRequest(RendererBackend::DX11, RendererToken::Gl);
    ExpectTrue(glOverDx11.backend == RendererBackend::Auto &&
                   glOverDx11.source == RequestSource::None,
               "gl cli over persistent dx11: stock this boot");
    const BootRequest bootAfterGl =
        ResolveBootRequest(RendererBackend::DX11, RendererToken::None);
    ExpectTrue(bootAfterGl.backend == RendererBackend::DX11 &&
                   bootAfterGl.source == RequestSource::Persistent,
               "persistent dx11 reasserted on the boot after gl");
}

void TestSubsystemNames()
{
    std::printf("TestSubsystemNames\n");
    ExpectStr(SubsystemNameFor(RendererBackend::DX9),
              "Direct3D9 Rendering Subsystem", "dx9 subsystem name");
    ExpectStr(SubsystemNameFor(RendererBackend::DX11),
              "Direct3D11 Rendering Subsystem", "dx11 subsystem name");
    ExpectTrue(SubsystemNameFor(RendererBackend::Auto) == nullptr,
               "auto has no subsystem name");

    RendererBackend parsed = RendererBackend::Auto;
    ExpectTrue(BackendFromSubsystemName("Direct3D11 Rendering Subsystem", parsed) &&
                   parsed == RendererBackend::DX11,
               "inverse map dx11");
    ExpectTrue(BackendFromSubsystemName("OpenGL Rendering Subsystem", parsed) == false,
               "gl not transportable");
}

void TestTransportImage()
{
    std::printf("TestTransportImage\n");

    // CRLF file, line present.
    std::string crlf =
        "Render System=Direct3D9 Rendering Subsystem\r\n"
        "\r\n"
        "[Direct3D9 Rendering Subsystem]\r\n"
        "Full Screen=Yes\r\n";
    ExpectTrue(ApplyTransportToConfigImage(crlf, "Direct3D11 Rendering Subsystem"),
               "crlf replace succeeds");
    ExpectTrue(crlf ==
               "Render System=Direct3D11 Rendering Subsystem\r\n"
               "\r\n"
               "[Direct3D9 Rendering Subsystem]\r\n"
               "Full Screen=Yes\r\n",
               "only the Render System line changed (CRLF preserved)");

    // LF-only file.
    std::string lf = "Render System=A\nOther=1\n";
    ExpectTrue(ApplyTransportToConfigImage(lf, "B"), "lf replace succeeds");
    ExpectStr(lf, "Render System=B\nOther=1\n", "lf preserved");

    // No trailing newline on the target line.
    std::string nonl = "[Section]\nRender System=Old";
    ExpectTrue(ApplyTransportToConfigImage(nonl, "New"), "final-line replace");
    ExpectStr(nonl, "[Section]\nRender System=New", "final-line content");

    // Absent key: prepend minimal keyed line.
    std::string absent = "[Sections only]\nKey=V";
    ExpectTrue(ApplyTransportToConfigImage(absent, "Direct3D9 Rendering Subsystem"),
               "absent key prepend");
    ExpectStr(absent,
              "Render System=Direct3D9 Rendering Subsystem\r\n[Sections only]\nKey=V",
              "prepended keyed line keeps document");

    // Refuse-to-touch cases.
    std::string empty;
    ExpectTrue(!ApplyTransportToConfigImage(empty, "X"), "empty refused");
    std::string binary = "Render System=X\x00\xFF"s + "tail";
    ExpectTrue(!ApplyTransportToConfigImage(binary, "Y"), "non-ASCII refused");
    ExpectStr(binary, "Render System=X\x00\xFF"s + "tail", "refused input untouched");

    // Extraction round-trip.
    ExpectStr(ExtractStockRenderSystemValue(crlf), "Direct3D11 Rendering Subsystem",
              "extract after rewrite");
    ExpectStr(ExtractStockRenderSystemValue("[a]\nb=c\n"), "", "absent extracts empty");
}

void TestOutcomeClassification()
{
    std::printf("TestOutcomeClassification\n");

    OutcomeInput in;

    in = {};
    ExpectReason(ClassifyOutcome(in), SelectionReason::Stock, "no request -> stock");

    in = {};
    in.haveRequest = true;
    in.requested = RendererBackend::DX11;
    in.backendIdentified = true;
    in.effective = ActiveBackend::DX11;
    in.stockLineAfterBoot = "Direct3D11 Rendering Subsystem";
    ExpectReason(ClassifyOutcome(in), SelectionReason::None,
                 "requested==effective persistent -> none");

    in.source = RequestSource::CliOverride;
    ExpectReason(ClassifyOutcome(in), SelectionReason::CliOverride,
                 "requested==effective via cli -> cli-override");

    // Ladder fallback burned the transport: effective DX9 while requested
    // DX11 and the stock line was rewritten underneath us.
    in.effective = ActiveBackend::DX9;
    in.stockLineAfterBoot = "Direct3D9 Rendering Subsystem";
    ExpectReason(ClassifyOutcome(in), SelectionReason::BackendUnavailable,
                 "fallback with burned line -> backend-unavailable");

    // Mismatch without a burned line should NOT be reported as unavailable.
    in.stockLineAfterBoot = "Direct3D11 Rendering Subsystem";
    ExpectReason(ClassifyOutcome(in), SelectionReason::UnresolvedMismatch,
                 "mismatch with intact line -> unresolved-mismatch");

    // Device-init failure signature: process died before identification.
    in = {};
    in.haveRequest = true;
    in.requested = RendererBackend::DX11;
    in.backendIdentified = false;
    ExpectReason(ClassifyOutcome(in), SelectionReason::NoEstablishment,
                 "no establishment -> no-establishment");
}

void TestReasonNames()
{
    std::printf("TestReasonNames\n");
    ExpectStr(ReasonName(SelectionReason::None), "none", "none name");
    ExpectStr(ReasonName(SelectionReason::CliOverride), "cli-override", "cli name");
    ExpectStr(ReasonName(SelectionReason::BackendUnavailable), "backend-unavailable",
              "unavailable name");
    ExpectStr(ReasonName(SelectionReason::UnresolvedMismatch), "unresolved-mismatch",
              "mismatch name");
    ExpectStr(ReasonName(SelectionReason::NoEstablishment), "no-establishment",
              "no-establishment name");
    ExpectStr(ReasonName(SelectionReason::Stock), "stock", "stock name");
}

void TestMinimalConfigImage()
{
    std::printf("TestMinimalConfigImage\n");
    const std::string dx11 = BuildMinimalConfigImage(
        "Direct3D11 Rendering Subsystem");
    ExpectStr(dx11, "Render System=Direct3D11 Rendering Subsystem\r\n",
              "minimal dx11 image");

    // Stock's own parser accepts this image: the key extracts cleanly.
    ExpectStr(ExtractStockRenderSystemValue(dx11),
              "Direct3D11 Rendering Subsystem", "minimal image round-trips");

    // And a second transport pass on the image is idempotent.
    std::string again = dx11;
    ExpectTrue(ApplyTransportToConfigImage(again,
                                           "Direct3D9 Rendering Subsystem"),
               "minimal image is rewritable");
    ExpectStr(again, "Render System=Direct3D9 Rendering Subsystem\r\n",
              "rewritten minimal image");

    ExpectStr(BuildMinimalConfigImage(""), "", "empty subsystem refused");
}

void TestTransportTempFileName()
{
    std::printf("TestTransportTempFileName\n");
    const std::string a = MakeTransportTempFileName(1234u);
    ExpectStr(a, "Ogre.cfg.openshim-1234.tmp", "pid 1234 format");
    ExpectTrue(MakeTransportTempFileName(0u) == "Ogre.cfg.openshim-0.tmp",
               "pid 0 format");
    ExpectTrue(MakeTransportTempFileName(4294967295u) ==
                   "Ogre.cfg.openshim-4294967295.tmp",
               "max pid format");
    // Distinct processes must never share a temp file.
    ExpectTrue(MakeTransportTempFileName(1u) != MakeTransportTempFileName(2u),
               "distinct pids disjoint");
    ExpectTrue(a.find("Ogre.cfg") == 0, "name anchored to Ogre.cfg prefix");
    ExpectTrue(a.ends_with(".tmp"), "tmp suffix present");
}

void TestParseTransportEnabled()
{
    std::printf("TestParseTransportEnabled\n");
    ExpectTrue(ParseTransportEnabled(""), "empty enables");
    ExpectTrue(ParseTransportEnabled("1"), "1 enables");
    ExpectTrue(ParseTransportEnabled("yes"), "yes enables");
    ExpectTrue(ParseTransportEnabled("true"), "true enables");
    ExpectTrue(ParseTransportEnabled("on"), "on enables");
    ExpectTrue(ParseTransportEnabled("garbage"), "garbage enables (fail-open)");
    ExpectTrue(ParseTransportEnabled(" ENABLED "), "whitespace + unknown word enables");
    ExpectTrue(!ParseTransportEnabled(" FALSE "), "whitespace + case-insensitive false disables");
    ExpectTrue(!ParseTransportEnabled("0"), "0 disables");
    ExpectTrue(!ParseTransportEnabled("false"), "false disables");
    ExpectTrue(!ParseTransportEnabled("No"), "No disables");
    ExpectTrue(!ParseTransportEnabled("OFF"), "OFF disables");
    ExpectTrue(!ParseTransportEnabled("\toff\t"), "surrounding tabs tolerated");
}

void TestStartupFilenameRecognition()
{
    std::printf("TestStartupFilenameRecognition\n");
    ExpectTrue(IsStartupConfigFilename("Ogre.cfg"), "bare name");
    ExpectTrue(IsStartupConfigFilename("ogre.cfg"), "case-insensitive bare");
    ExpectTrue(IsStartupConfigFilename(R"(C:\Games\BZR\Ogre.cfg)"),
               "windows absolute path");
    ExpectTrue(IsStartupConfigFilename("/game/root/ogre.CFG"),
               "slash path, mixed case");
    ExpectTrue(!IsStartupConfigFilename("bz_resources.cfg"),
               "other config rejected");
    ExpectTrue(!IsStartupConfigFilename(""), "empty rejected");
    ExpectTrue(!IsStartupConfigFilename("Ogre.cfg.bak"), "suffix trap");
    ExpectTrue(!IsStartupConfigFilename("myOgre.cfg"), "prefix trap");
    ExpectTrue(!IsStartupConfigFilename("Ogre.cf"), "truncated rejected");
}

int main()
{
    std::printf("backend_selection_tests\n");
    TestTokenClassification();
    TestCommandLineScan();
    TestBootRequestResolution();
    TestSubsystemNames();
    TestTransportImage();
    TestOutcomeClassification();
    TestReasonNames();
    TestMinimalConfigImage();
    TestTransportTempFileName();
    TestParseTransportEnabled();
    TestStartupFilenameRecognition();
    if (g_failures != 0)
    {
        std::printf("FAILED: %d assertion(s)\n", g_failures);
        return 1;
    }
    std::printf("all backend selection tests passed\n");
    return 0;
}
