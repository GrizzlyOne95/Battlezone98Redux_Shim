#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include "socket_tunnel.h"
#include "steam_tunnel_transport.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <filesystem>
#include <vector>

using namespace BZROpenShim::SocketTunnel;
static std::atomic<bool> stop{false};
static BOOL WINAPI Interrupt(DWORD) { stop = true; return TRUE; }
static void Log(const char* text) { std::printf("[%llu] %s\n", GetTickCount64(), text); std::fflush(stdout); }
int wmain(int argc, wchar_t** wideArgs)
{
    std::vector<std::string> args;
    std::vector<const char*> argv;
    for (int i = 0; i < argc; ++i)
    {
        const int n = WideCharToMultiByte(CP_UTF8, 0, wideArgs[i], -1, nullptr, 0, nullptr, nullptr);
        if (!n) return 2;
        std::string text(size_t(n), 0);
        WideCharToMultiByte(CP_UTF8, 0, wideArgs[i], -1, text.data(), n, nullptr, nullptr);
        text.resize(size_t(n - 1)); args.push_back(std::move(text));
    }
    for (const auto& arg : args) argv.push_back(arg.c_str());
    Config cfg; unsigned seconds = 0; std::string stopFile;
    if (argc == 2 && std::string(argv[1]) == "steam-self-test")
    {
        try
        {
            cfg.steam = cfg.bridge = cfg.ownSteam = true;
            SteamTransport transport; transport.Start(cfg, stop, Log);
            return transport.SelfTest();
        }
        catch (const std::exception& error) { Log(error.what()); return 2; }
    }
    if (argc < 2 || (std::string(argv[1]) != "agent" && std::string(argv[1]) != "bridge"))
    {
        std::puts("socket_tunnel agent --remote IPv4:port [--seconds N]\n"
                  "socket_tunnel bridge [--listen IPv4:port] [--allow clientIPv4] [--server 127.0.0.2] [--seconds N]\n"
                  "socket_tunnel agent --steam-host SteamID64 [--seconds N]\n"
                  "socket_tunnel bridge --steam [--server loopbackIPv4] [--identity-map PATH]\n"
                  "socket_tunnel steam-self-test (real SDK local socket pair; not a remote P2P test)\n"
                  "Plain UDP is a trusted LAN test transport. Never expose it to WAN. Steam needs appid 301650."); return 2;
    }
    cfg.bridge = std::string(argv[1]) == "bridge";
    for (int i = 2; i < argc; ++i)
    {
        std::string key = argv[i];
        if (key == "--steam" && cfg.bridge) { cfg.steam = cfg.ownSteam = true; continue; }
        if (++i == argc) return 2;
        std::string value = argv[i];
        if (key == "--remote" && !cfg.bridge) { if (!ParseEndpoint(value, cfg.remote, cfg.port)) return 2; }
        else if (key == "--steam-host" && !cfg.bridge)
        {
            if (!ParseSteamId(value, cfg.steamHost)) return 2;
            cfg.steam = cfg.ownSteam = true;
        }
        else if (key == "--identity-map" && cfg.bridge) cfg.identityMap = value;
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
    // Reject ambiguous CLI selections just as the INI path does.
    for (int i = 2; i < argc; ++i)
        if (cfg.steam && (std::string(argv[i]) == "--remote" || std::string(argv[i]) == "--listen" || std::string(argv[i]) == "--allow")) return 2;
    if (cfg.steam && cfg.bridge && cfg.identityMap.empty())
    {
        wchar_t path[32768]{};
        const auto n = GetModuleFileNameW(nullptr, path, DWORD(std::size(path)));
        if (!n || n >= std::size(path)) return 2;
        cfg.identityMap = (std::filesystem::path(path).parent_path() / "steam_tunnel_peers.txt").u8string();
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
