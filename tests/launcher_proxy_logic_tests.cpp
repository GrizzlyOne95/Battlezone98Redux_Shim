#include "launcher_proxy_logic.h"
#include "test_check.h"

#include <cwchar>

using namespace BZROpenShim::LauncherProxy;
using OpenShimTest::Check;

int main()
{
    Check(ShouldSkipLauncher(false, true, true, false), "all gates pass: skip");
    Check(!ShouldSkipLauncher(true, true, true, false), "Shift shows the launcher");
    Check(!ShouldSkipLauncher(false, false, true, false), "toggle off shows the launcher");
    Check(!ShouldSkipLauncher(false, true, false, false), "first run (no Ogre.cfg) shows the launcher");
    Check(!ShouldSkipLauncher(false, true, true, true), "Wine/Proton shows the launcher");

    Check(ParseToggle(L"1"), "1 is on");
    Check(ParseToggle(L"true"), "true is on");
    Check(!ParseToggle(L"0"), "0 is off");
    Check(!ParseToggle(L""), "blank is off");
    Check(!ParseToggle(nullptr), "null is off");
    Check(!ParseToggle(L"maybe"), "unknown word is off");
    Check(!ParseToggle(L"11111111111111111111"), "over-long value is off");
    Check(!ParseToggle(L"\x00e9"), "non-ASCII is off");

    Check(std::wcscmp(CommandLineTail(nullptr), L"") == 0, "null command line");
    Check(std::wcscmp(CommandLineTail(L"\"C:\\S team\\BZLauncher.exe\"  -a b"), L"-a b") == 0,
          "quoted argv0 dropped");
    Check(std::wcscmp(CommandLineTail(L"BZLauncher.exe -a"), L"-a") == 0, "bare argv0 dropped");
    Check(std::wcscmp(CommandLineTail(L"\"C:\\x\\BZLauncher.exe\""), L"") == 0, "no arguments");
    Check(std::wcscmp(CommandLineTail(L"\"unterminated"), L"") == 0, "unterminated quote");
    return OpenShimTest::ExitCode();
}