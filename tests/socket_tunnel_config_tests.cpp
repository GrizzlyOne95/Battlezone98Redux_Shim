#include "socket_tunnel.h"
#include "shim_log.h"
#include <cstdio>
#include <thread>
#include <chrono>
#include <cstdarg>
#include <string>
static std::string lastLog;
namespace BZROpenShim { void LogShimA(LogLevel, const char*, const char* format, ...)
{
    char text[1024]; va_list args; va_start(args, format);
    std::vsnprintf(text, sizeof(text), format, args); va_end(args);
    lastLog = text;
} }
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
        else if (mode == "steam_invalid") Configure("not-a-SteamID", "");
        else if (mode == "borrowed")
        {
            // No Steam API is loaded: fail promptly with an actionable diagnostic.
            const auto started = std::chrono::steady_clock::now();
            Configure("76561198000000000", "");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            Stop(); // synchronizes worker log access
            if (std::chrono::steady_clock::now() - started > std::chrono::seconds(2) ||
                lastLog.find("requires the Steam build") == std::string::npos) return 1;
        }
        else if (mode == "invalid") Configure("", "not-an-ip:27030");
        else return 2;
        if (!Requested() || WaitReady(1000)) return 1;
    }
    Stop(); Stop(); // explicit shutdown is idempotent, including failure paths
    std::puts("tunnel configuration guard passed");
}
