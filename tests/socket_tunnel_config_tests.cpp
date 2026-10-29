#include "socket_tunnel.h"
#include "shim_log.h"
#include <cstdio>
#include <thread>
#include <chrono>
namespace BZROpenShim { void LogShimA(LogLevel, const char*, const char*, ...) {} }
using namespace BZROpenShim::SocketTunnel;
int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    const std::string mode = argv[1];
    if (mode == "disabled")
    {
        Configure("", "");
        if (Requested() || Ready()) return 1;
    }
    else
    {
        // A Steam request must never downgrade to a supplied plain-UDP route.
        if (mode == "steam") Configure("76561198000000000", "127.0.0.1:27030");
        else if (mode == "steam_invalid") Configure("not-a-SteamID", "");
        else if (mode == "borrowed")
        {
            // The test process has no Steam API loaded. It must never load/init
            // another one; shutdown cancels its wait rather than blocking 30 s.
            Configure("76561198000000000", "");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        else if (mode == "invalid") Configure("", "not-an-ip:27030");
        else return 2;
        if (!Requested() || Ready()) return 1;
    }
    Stop(); Stop(); // explicit shutdown is idempotent, including failure paths
    std::puts("tunnel configuration guard passed");
}
