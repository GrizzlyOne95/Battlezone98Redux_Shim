#include "steam_launcher_argument.h"
#include "test_check.h"

#include <cstring>
#include <string>

using BZROpenShim::SteamLauncherArgument::BlankSteamLauncherArgument;
using OpenShimTest::Check;
using OpenShimTest::ExitCode;

namespace
{
    std::string Run(const char* input, int& count)
    {
        std::string buffer(input);
        count = BlankSteamLauncherArgument(&buffer[0]);
        Check(buffer.size() == std::strlen(input), "the buffer keeps its length");
        return buffer;
    }
}

int main()
{
    int n = 0;

    std::string out = Run(R"("C:\Games\BZR\battlezone98redux.exe" "C:\Games\BZR\Launcher\BZLauncher.exe")", n);
    Check(n == 1 && out.find("BZLauncher") == std::string::npos &&
              out.find(R"(battlezone98redux.exe")") != std::string::npos,
          "the quoted launcher path Steam adds is blanked and argv[0] survives");

    out = Run("bz.exe C:/x/launcher/bzlauncher.EXE /nointro", n);
    Check(n == 1 && out.find("/nointro") != std::string::npos && out.find("bzlauncher") == std::string::npos,
          "an unquoted, mixed-case launcher path is blanked and later switches survive");

    out = Run(R"("C:\Launcher\BZLauncher.exe" /nointro)", n);
    Check(n == 0 && out == R"("C:\Launcher\BZLauncher.exe" /nointro)", "argv[0] is never touched");

    out = Run("bz.exe /nointro sxshow.bzn", n);
    Check(n == 0 && out == "bz.exe /nointro sxshow.bzn", "a normal command line is unchanged");

    out = Run("bz.exe NotBZLauncher.exe myBZLauncher.exe.bzn", n);
    Check(n == 0, "names that only contain the launcher name are kept");

    out = Run("bz.exe BZLauncher.exe", n);
    Check(n == 1, "a bare launcher file name is blanked");

    out = Run(R"(bz.exe "C:\unterminated\BZLauncher.exe)", n);
    Check(n == 1, "an unterminated quote is handled");

    Check(BlankSteamLauncherArgument(nullptr) == 0, "null is ignored");
    return ExitCode();
}
