#include "openshim_auto_update.h"
#include "test_check.h"

using namespace BZROpenShim;
using OpenShimTest::Check;

int main()
{
    AutoStageInputs in;
    in.steamBuild = true;
    Check(ShouldAutoStageUpdate(in), "default config on a Steam build stages");

    AutoStageInputs off = in;
    off.configEnabled = false;
    Check(!ShouldAutoStageUpdate(off), "AutoStage = 0 disables the check");

    AutoStageInputs nonSteam = in;
    nonSteam.steamBuild = false;
    Check(!ShouldAutoStageUpdate(nonSteam), "non-Steam builds never auto-check");

    AutoStageInputs net = in;
    net.inNetworkSession = true;
    Check(!ShouldAutoStageUpdate(net), "no auto-check in a network session");

    AutoStageInputs again = in;
    again.alreadyRanThisProcess = true;
    Check(!ShouldAutoStageUpdate(again), "only once per process");

    Check(FormatAutoStageNotice("1.2.3.4") ==
              "OpenShim 1.2.3.4 is ready and will install when you quit the game.",
          "notice text");

    std::wstring script;
    Check(BuildUpdateRestartWatcherScript(
              L"C:\\Games\\Battlezone 98 Redux\\openshim_update.status", L"301650", 180, script),
          "valid watcher script builds");
    Check(script.find(L"$p='C:\\Games\\Battlezone 98 Redux\\openshim_update.status';") == 0,
          "path is a single-quoted literal");
    Check(script.find(L"AddSeconds(180)") != std::wstring::npos, "timeout embedded");
    Check(script.find(L"steam://rungameid/301650") != std::wstring::npos, "launch uri");
    Check(script.find(L'"') == std::wstring::npos, "no double quotes to break the command line");

    // Injection attempts: quotes are doubled, control characters refused.
    Check(BuildUpdateRestartWatcherScript(L"C:\\a'; calc; '\\x", L"301650", 180, script) &&
              script.find(L"$p='C:\\a''; calc; ''\\x';") == 0,
          "ASCII quote is doubled");
    Check(BuildUpdateRestartWatcherScript(L"C:\\a\u2019; calc\\x", L"301650", 180, script) &&
              script.find(L"$p='C:\\a\u2019\u2019; calc\\x';") == 0,
          "typographic quote is doubled");
    Check(!BuildUpdateRestartWatcherScript(L"C:\\a\nb", L"301650", 180, script) && script.empty(),
          "newline refused");
    Check(!BuildUpdateRestartWatcherScript(L"relative\\status", L"301650", 180, script),
          "relative path refused");
    Check(!BuildUpdateRestartWatcherScript(L"C:\\a", L"301650;calc", 180, script),
          "non-numeric app id refused");
    Check(!BuildUpdateRestartWatcherScript(L"C:\\a", L"301650", 0, script),
          "zero timeout refused");
    return OpenShimTest::ExitCode();
}
