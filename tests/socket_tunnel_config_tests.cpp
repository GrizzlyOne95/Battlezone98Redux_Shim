#include "socket_tunnel.h"
#include "shim_log.h"
#include <cstdio>
namespace BZROpenShim { void LogShimA(LogLevel, const char*, const char*, ...) {} }
using namespace BZROpenShim::SocketTunnel;
int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    const std::string mode = argv[1];
    if (mode == "disabled")
    {
        Configure("", "");
        if (Requested() || WaitReady(1)) return 1;
    }
    else if (mode == "startup")
    {
        Configure("", "127.0.0.1:27030");
        // Resolve immediately after Configure: worker may not have bound yet.
        if (!Requested() || !WaitReady(1000)) { Stop(); return 1; }
    }
    else
    {
        // A Steam request must never downgrade to a supplied plain-UDP route.
        if (mode == "steam") Configure("76561198000000000", "127.0.0.1:27030");
        else if (mode == "invalid") Configure("", "not-an-ip:27030");
        else return 2;
        if (!Requested() || WaitReady(1000)) return 1;
    }
    Stop(); Stop(); // explicit shutdown is idempotent, including failure paths
    std::puts("tunnel configuration guard passed");
}
