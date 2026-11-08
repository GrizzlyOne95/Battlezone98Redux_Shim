#include "socket_tunnel.h"
#include "shim_log.h"
#include <cstdio>
#include <thread>
#include <chrono>
#include <cstdarg>
#include <string>
#include <mutex>
static std::string lastLog, allLogs; // read only after Stop() joins workers
namespace BZROpenShim { void LogShimA(LogLevel, const char*, const char* format, ...)
{
    char text[1024]; va_list args; va_start(args, format);
    std::vsnprintf(text, sizeof(text), format, args); va_end(args);
    static std::mutex lock; std::lock_guard<std::mutex> guard(lock); // workers log too
    lastLog = text; allLogs += text; allLogs += '\n';
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
        else if (mode == "bridge_exclusive")
        {
            // Agent keys win; the host bridge is refused, never run alongside.
            Configure("76561198000000000", "", "127.0.0.1");
            Stop();
            if (allLogs.find("cannot run with SteamTunnelHost") == std::string::npos ||
                allLogs.find("[SteamBridge] hosting") != std::string::npos) return 1;
            std::puts("tunnel configuration guard passed"); return 0;
        }
        else if (mode == "bridge_invalid")
        {
            Configure("", "", "192.168.1.5");
            if (lastLog.find("the numeric loopback IPv4") == std::string::npos) return 1;
            Stop(); std::puts("tunnel configuration guard passed"); return 0;
        }
        else if (mode == "bridge_borrowed")
        {
            // No Steam API loaded: the host bridge fails promptly, agent untouched.
            const auto started = std::chrono::steady_clock::now();
            Configure("", "", "127.0.0.1");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            Stop();
            if (std::chrono::steady_clock::now() - started > std::chrono::seconds(2) ||
                allLogs.find("requires the Steam build") == std::string::npos || Requested()) return 1;
            std::puts("tunnel configuration guard passed"); return 0;
        }
        else if (mode == "bridge_auto_gog" || mode == "bridge_auto_guest")
        {
            // auto stays off without steam_api.dll or with an agent key; no thread, no agent.
            const bool guest = mode == "bridge_auto_guest";
            Configure(guest ? "76561198000000000" : "", "", "AUTO", [](std::string& h) { h = "127.0.0.2"; return true; });
            Stop();
            if (allLogs.find(guest ? "auto: this game joins through" : "auto: not the Steam build") == std::string::npos ||
                allLogs.find("hosting the Steam bridge") != std::string::npos || (!guest && Requested())) return 1;
            std::puts("tunnel configuration guard passed"); return 0;
        }
        else if (mode == "invalid") Configure("", "not-an-ip:27030");
        else return 2;
        if (!Requested() || WaitReady(1000)) return 1;
    }
    Stop(); Stop(); // explicit shutdown is idempotent, including failure paths
    std::puts("tunnel configuration guard passed");
}
