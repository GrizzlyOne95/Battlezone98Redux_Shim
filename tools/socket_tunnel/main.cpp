#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include "socket_tunnel.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <filesystem>

using namespace BZROpenShim::SocketTunnel;
static std::atomic<bool> stop{false};
static BOOL WINAPI Interrupt(DWORD) { stop = true; return TRUE; }
static void Log(const char* text) { std::printf("[%llu] %s\n", GetTickCount64(), text); std::fflush(stdout); }
int main(int argc, char** argv)
{
    Config cfg; unsigned seconds = 0; std::string stopFile;
    if (argc < 2 || (std::string(argv[1]) != "agent" && std::string(argv[1]) != "bridge"))
    {
        std::puts("socket_tunnel agent --remote IPv4:port [--seconds N]\n"
                  "socket_tunnel bridge [--listen IPv4:port] [--allow clientIPv4] [--server 127.0.0.2] [--seconds N]\n"
                  "M1 trusted LAN test transport. No encryption or Steam authentication. Never expose to WAN."); return 2;
    }
    cfg.bridge = std::string(argv[1]) == "bridge";
    for (int i = 2; i < argc; ++i)
    {
        std::string key = argv[i];
        if (++i == argc) return 2;
        std::string value = argv[i];
        if (key == "--remote" && !cfg.bridge) { if (!ParseEndpoint(value, cfg.remote, cfg.port)) return 2; }
        else if (key == "--listen" && cfg.bridge) { if (!ParseEndpoint(value, cfg.listen, cfg.port)) return 2; }
        else if (key == "--allow" && cfg.bridge) cfg.allow = value;
        else if (key == "--server" && cfg.bridge) cfg.server = value;
        else if (key == "--stop-file") stopFile = value;
        else if (key == "--seconds")
        {
            char* end = nullptr; auto n = std::strtoul(value.c_str(), &end, 10);
            if (!end || *end || n < 1 || n > 86400) return 2;
            seconds = unsigned(n);
        }
        else return 2;
    }
    SetConsoleCtrlHandler(Interrupt, TRUE);
    std::atomic<int> ready{0}; int result = 0;
    std::thread worker([&] { result = Run(cfg, stop, ready, Log); });
    const auto started = GetTickCount64();
    while (ready.load() >= 0 && !stop.load())
    {
        if (seconds && GetTickCount64() - started >= uint64_t(seconds) * 1000) stop = true;
        if (!stopFile.empty() && std::filesystem::exists(std::filesystem::u8path(stopFile))) stop = true;
        Sleep(10);
    }
    stop = true; worker.join(); return result;
}
