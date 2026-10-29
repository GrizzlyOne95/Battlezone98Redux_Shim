#include "embedded_lan_host.h"
#include <windows.h>
#include <cstdio>
#include <cstdlib>
int main(int argc,char** argv)
{
    if (argc<3) return 2;
    BZROpenShim::EmbeddedLan::Host host;
    if (!host.Start(argv[1],static_cast<unsigned short>(std::atoi(argv[2]))))
    { std::puts(host.Error().c_str()); return 1; }
    std::puts("IN_PROCESS_LAN_READY"); std::fflush(stdout);
    const auto start=GetTickCount64();
    while (host.Running() && GetTickCount64()-start<120000)
    {
        if (argc>3 && GetFileAttributesA(argv[3])!=INVALID_FILE_ATTRIBUTES) break;
        Sleep(10);
    }
    host.Stop();
    return 0;
}
