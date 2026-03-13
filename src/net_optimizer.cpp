#include "net_optimizer.h"
#include "shim_log.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <Windows.h>

#include <algorithm>
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
namespace
{
    constexpr DWORD kSioUdpConnReset = _WSAIOW(IOC_VENDOR, 12);

    struct NetConfig
    {
        bool enabled = true;
        bool logging = true;
        bool tcpNoDelay = true;
        bool keepAlive = true;
        bool disableUdpConnReset = true;
        bool logSocketErrors = true;
        bool applySocketBuffers = true;
        uint32_t sendBufferSize = 524288;
        uint32_t recvBufferSize = 2097152;
    };

    struct SocketState
    {
        int af = AF_UNSPEC;
        int type = 0;
        int protocol = 0;
        bool optimized = false;
        int lastSendError = 0;
        int lastRecvError = 0;
        int lastSendToError = 0;
        int lastRecvFromError = 0;
    };

    using WSASocketWFn = SOCKET (WSAAPI*)(int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);
    using WSASendFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSASendToFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const sockaddr*, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFromFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, sockaddr*, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSAIoctlFn = int (WSAAPI*)(SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using SetSockOptFn = int (WSAAPI*)(SOCKET, int, int, const char*, int);
    using GetSockOptFn = int (WSAAPI*)(SOCKET, int, int, char*, int*);
    using WSAGetLastErrorFn = int (WSAAPI*)();
    using WSASetLastErrorFn = void (WSAAPI*)(int);

    NetConfig g_Config;
    std::string g_NetIniPath;

    SRWLOCK g_SocketLock = SRWLOCK_INIT;
    std::unordered_map<SOCKET, SocketState> g_Sockets;

    HMODULE g_Ws2Module = nullptr;
    WSASocketWFn g_RealWSASocketW = nullptr;
    WSASendFn g_RealWSASend = nullptr;
    WSARecvFn g_RealWSARecv = nullptr;
    WSASendToFn g_RealWSASendTo = nullptr;
    WSARecvFromFn g_RealWSARecvFrom = nullptr;
    WSAIoctlFn g_RealWSAIoctl = nullptr;
    SetSockOptFn g_RealSetSockOpt = nullptr;
    GetSockOptFn g_RealGetSockOpt = nullptr;
    WSAGetLastErrorFn g_RealWSAGetLastError = nullptr;
    WSASetLastErrorFn g_RealWSASetLastError = nullptr;

    void Logf(const char* fmt, ...)
    {
        if (!g_Config.logging)
            return;

        va_list args;
        va_start(args, fmt);
        LogShimVA(LogLevel::Info, "net", fmt, args);
        va_end(args);
    }

    std::string GetGameDir()
    {
        char path[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        char* lastSlash = std::strrchr(path, '\\');
        if (!lastSlash)
            return {};

        *lastSlash = '\0';
        return path;
    }

    std::string JoinPath(const std::string& dir, const char* leaf)
    {
        if (dir.empty())
            return leaf ? leaf : "";

        std::string path = dir;
        path.push_back('\\');
        path += leaf;
        return path;
    }

    bool FileExists(const std::string& path)
    {
        const DWORD attrs = GetFileAttributesA(path.c_str());
        return (attrs != INVALID_FILE_ATTRIBUTES) && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool ReadIniBool(const char* section, const char* key, bool fallback)
    {
        if (g_NetIniPath.empty())
            return fallback;

        char buf[32] = {};
        GetPrivateProfileStringA(section, key, "", buf, static_cast<DWORD>(sizeof(buf)), g_NetIniPath.c_str());
        if (buf[0] == '\0')
            return fallback;

        const int value = std::atoi(buf);
        return value != 0;
    }

    uint32_t ReadIniUint(const char* section, const char* key, uint32_t fallback)
    {
        if (g_NetIniPath.empty())
            return fallback;

        char buf[64] = {};
        GetPrivateProfileStringA(section, key, "", buf, static_cast<DWORD>(sizeof(buf)), g_NetIniPath.c_str());
        if (buf[0] == '\0')
            return fallback;

        const unsigned long value = std::strtoul(buf, nullptr, 10);
        return static_cast<uint32_t>(value);
    }

    int ReadIniInt(const char* section, const char* key, int fallback)
    {
        if (g_NetIniPath.empty())
            return fallback;

        char buf[64] = {};
        GetPrivateProfileStringA(section, key, "", buf, static_cast<DWORD>(sizeof(buf)), g_NetIniPath.c_str());
        if (buf[0] == '\0')
            return fallback;

        return std::atoi(buf);
    }

    void LoadConfig()
    {
        const std::string netIni = JoinPath(GetGameDir(), "net.ini");
        if (FileExists(netIni))
            g_NetIniPath = netIni;

        g_Config.enabled = ReadIniBool("OpenShimSocket", "EnableSocketOptimizer", true);
        g_Config.logging = ReadIniBool("OpenShimSocket", "EnableLogging", true);
        g_Config.tcpNoDelay = ReadIniBool("OpenShimSocket", "EnableTcpNoDelay", true);
        g_Config.keepAlive = ReadIniBool("OpenShimSocket", "EnableKeepAlive", true);
        g_Config.disableUdpConnReset = ReadIniBool("OpenShimSocket", "DisableUdpConnReset", true);
        g_Config.logSocketErrors = ReadIniBool("OpenShimSocket", "LogSocketErrors", true);
        const uint32_t legacySocketBufferSize = ReadIniUint("OpenShimSocket", "SocketBufferSize", 0);
        g_Config.sendBufferSize = ReadIniUint(
            "OpenShimSocket",
            "SendBufferSize",
            legacySocketBufferSize ? legacySocketBufferSize : 524288);
        g_Config.recvBufferSize = ReadIniUint(
            "OpenShimSocket",
            "ReceiveBufferSize",
            legacySocketBufferSize ? legacySocketBufferSize : 2097152);
        g_Config.sendBufferSize = std::max<uint32_t>(g_Config.sendBufferSize, 32 * 1024);
        g_Config.recvBufferSize = std::max<uint32_t>(g_Config.recvBufferSize, 32 * 1024);

        const std::string manifestPath = JoinPath(GetGameDir(), "netcode_manifest.json");
        if (FileExists(manifestPath))
        {
            g_Config.applySocketBuffers = false;
            g_Config.sendBufferSize = 524288;
            g_Config.recvBufferSize = 2097152;
        }
    }

    void LogNetIniValues()
    {
        if (g_NetIniPath.empty())
        {
            Logf("[OpenShimNet] net.ini not found next to the game executable");
            return;
        }

        Logf("[OpenShimNet] net.ini path: %s", g_NetIniPath.c_str());
        Logf("[OpenShimNet] [Net] MaxPing=%d UpCount=%d DownCount=%d MinBandwidth=%d MaxBandwidth=%d MaxPingsLost=%d AutoKickStart=%d AutoKickPing=%d AutoKickLoss=%d AutoKickTime=%d UseCompression=%d",
            ReadIniInt("Net", "MaxPing", -1),
            ReadIniInt("Net", "UpCount", -1),
            ReadIniInt("Net", "DownCount", -1),
            ReadIniInt("Net", "MinBandwidth", -1),
            ReadIniInt("Net", "MaxBandwidth", -1),
            ReadIniInt("Net", "MaxPingsLost", -1),
            ReadIniInt("Net", "AutoKickStart", -1),
            ReadIniInt("Net", "AutoKickPing", -1),
            ReadIniInt("Net", "AutoKickLoss", -1),
            ReadIniInt("Net", "AutoKickTime", -1),
            ReadIniInt("Net", "UseCompression", -1));
    }

    bool LoadWinsockExports()
    {
        g_Ws2Module = GetModuleHandleA("ws2_32.dll");
        if (!g_Ws2Module)
            g_Ws2Module = LoadLibraryA("ws2_32.dll");
        if (!g_Ws2Module)
        {
            LogShimA(LogLevel::Error, "net", "[OpenShimNet] Failed to load ws2_32.dll");
            return false;
        }

        g_RealWSASocketW = reinterpret_cast<WSASocketWFn>(GetProcAddress(g_Ws2Module, "WSASocketW"));
        g_RealWSASend = reinterpret_cast<WSASendFn>(GetProcAddress(g_Ws2Module, "WSASend"));
        g_RealWSARecv = reinterpret_cast<WSARecvFn>(GetProcAddress(g_Ws2Module, "WSARecv"));
        g_RealWSASendTo = reinterpret_cast<WSASendToFn>(GetProcAddress(g_Ws2Module, "WSASendTo"));
        g_RealWSARecvFrom = reinterpret_cast<WSARecvFromFn>(GetProcAddress(g_Ws2Module, "WSARecvFrom"));
        g_RealWSAIoctl = reinterpret_cast<WSAIoctlFn>(GetProcAddress(g_Ws2Module, "WSAIoctl"));
        g_RealSetSockOpt = reinterpret_cast<SetSockOptFn>(GetProcAddress(g_Ws2Module, "setsockopt"));
        g_RealGetSockOpt = reinterpret_cast<GetSockOptFn>(GetProcAddress(g_Ws2Module, "getsockopt"));
        g_RealWSAGetLastError = reinterpret_cast<WSAGetLastErrorFn>(GetProcAddress(g_Ws2Module, "WSAGetLastError"));
        g_RealWSASetLastError = reinterpret_cast<WSASetLastErrorFn>(GetProcAddress(g_Ws2Module, "WSASetLastError"));

        const bool ok =
            g_RealWSASocketW &&
            g_RealWSASend &&
            g_RealWSARecv &&
            g_RealWSASendTo &&
            g_RealWSARecvFrom &&
            g_RealWSAIoctl &&
            g_RealSetSockOpt &&
            g_RealGetSockOpt &&
            g_RealWSAGetLastError &&
            g_RealWSASetLastError;

        if (!ok)
            LogShimA(LogLevel::Error, "net", "[OpenShimNet] Missing one or more required Winsock exports");

        return ok;
    }

    void RememberSocket(SOCKET s, int af, int type, int protocol)
    {
        AcquireSRWLockExclusive(&g_SocketLock);
        SocketState& state = g_Sockets[s];
        state.af = af;
        state.type = type;
        state.protocol = protocol;
        ReleaseSRWLockExclusive(&g_SocketLock);
    }

    bool LookupSocket(SOCKET s, SocketState& outState)
    {
        AcquireSRWLockShared(&g_SocketLock);
        const auto it = g_Sockets.find(s);
        if (it == g_Sockets.end())
        {
            ReleaseSRWLockShared(&g_SocketLock);
            return false;
        }

        outState = it->second;
        ReleaseSRWLockShared(&g_SocketLock);
        return true;
    }

    void MarkSocketOptimized(SOCKET s)
    {
        AcquireSRWLockExclusive(&g_SocketLock);
        g_Sockets[s].optimized = true;
        ReleaseSRWLockExclusive(&g_SocketLock);
    }

    int QuerySocketInt(SOCKET s, int level, int optName)
    {
        int value = 0;
        int len = sizeof(value);
        if (!g_RealGetSockOpt || g_RealGetSockOpt(s, level, optName, reinterpret_cast<char*>(&value), &len) != 0 || len != sizeof(value))
            return -1;
        return value;
    }

    void SetSocketIntOption(SOCKET s, int level, int optName, int value, const char* optLabel)
    {
        const int current = QuerySocketInt(s, level, optName);
        if (current >= value)
            return;

        const int rc = g_RealSetSockOpt(s, level, optName, reinterpret_cast<const char*>(&value), sizeof(value));
        if (rc == 0)
        {
            const int readback = QuerySocketInt(s, level, optName);
            Logf("[OpenShimNet] Socket 0x%08X %s %d -> %d", static_cast<unsigned>(s), optLabel, current, readback);
            return;
        }

        const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : 0;
        Logf("[OpenShimNet] Failed to set %s on socket 0x%08X (err=%d)", optLabel, static_cast<unsigned>(s), err);
        if (g_RealWSASetLastError)
            g_RealWSASetLastError(err);
    }

    void MaybeDisableUdpConnReset(SOCKET s, const SocketState& state)
    {
        if (!g_Config.disableUdpConnReset)
            return;

        const bool isUdp = (state.type == SOCK_DGRAM) || (state.protocol == IPPROTO_UDP);
        if (!isUdp || state.af != AF_INET)
            return;

        BOOL newBehavior = FALSE;
        DWORD bytesReturned = 0;
        const int rc = g_RealWSAIoctl(
            s,
            kSioUdpConnReset,
            &newBehavior,
            sizeof(newBehavior),
            nullptr,
            0,
            &bytesReturned,
            nullptr,
            nullptr);

        if (rc == 0)
            Logf("[OpenShimNet] Disabled SIO_UDP_CONNRESET on socket 0x%08X", static_cast<unsigned>(s));
    }

    void EnsureSocketOptions(SOCKET s)
    {
        if (!g_Config.enabled)
            return;

        SocketState state = {};
        if (LookupSocket(s, state) && state.optimized)
            return;

        if (!LookupSocket(s, state))
        {
            state.type = QuerySocketInt(s, SOL_SOCKET, SO_TYPE);
            RememberSocket(s, AF_UNSPEC, state.type, 0);
        }

        if (g_Config.applySocketBuffers)
        {
            SetSocketIntOption(s, SOL_SOCKET, SO_SNDBUF, static_cast<int>(g_Config.sendBufferSize), "SO_SNDBUF");
            SetSocketIntOption(s, SOL_SOCKET, SO_RCVBUF, static_cast<int>(g_Config.recvBufferSize), "SO_RCVBUF");
        }

        if ((state.type == SOCK_STREAM || state.protocol == IPPROTO_TCP) && g_Config.tcpNoDelay)
            SetSocketIntOption(s, IPPROTO_TCP, TCP_NODELAY, 1, "TCP_NODELAY");

        if ((state.type == SOCK_STREAM || state.protocol == IPPROTO_TCP) && g_Config.keepAlive)
            SetSocketIntOption(s, SOL_SOCKET, SO_KEEPALIVE, 1, "SO_KEEPALIVE");

        MaybeDisableUdpConnReset(s, state);
        MarkSocketOptimized(s);
    }

    void LogSocketError(const char* api, SOCKET s, int rc, int SocketState::*lastErrorField)
    {
        if (rc != SOCKET_ERROR || !g_Config.logSocketErrors || !g_RealWSAGetLastError)
            return;

        const int err = g_RealWSAGetLastError();
        if (err == WSAEWOULDBLOCK)
            return;

        bool shouldLog = true;

        AcquireSRWLockExclusive(&g_SocketLock);
        SocketState& state = g_Sockets[s];
        if (state.*lastErrorField == err)
            shouldLog = false;
        else
            state.*lastErrorField = err;
        ReleaseSRWLockExclusive(&g_SocketLock);

        if (shouldLog)
            Logf("[OpenShimNet] %s failed on socket 0x%08X (err=%d)", api, static_cast<unsigned>(s), err);

        if (g_RealWSASetLastError)
            g_RealWSASetLastError(err);
    }

    SOCKET WSAAPI Hook_WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW protocolInfo, GROUP group, DWORD flags)
    {
        const SOCKET s = g_RealWSASocketW(af, type, protocol, protocolInfo, group, flags);
        if (s == INVALID_SOCKET)
        {
            const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : 0;
            Logf("[OpenShimNet] WSASocketW failed (af=%d type=%d proto=%d err=%d)", af, type, protocol, err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
            return s;
        }

        RememberSocket(s, af, type, protocol);
        Logf("[OpenShimNet] WSASocketW created socket 0x%08X (af=%d type=%d proto=%d)", static_cast<unsigned>(s), af, type, protocol);
        EnsureSocketOptions(s);
        return s;
    }

    int WSAAPI Hook_WSASend(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesSent, DWORD flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSASend(s, buffers, bufferCount, bytesSent, flags, overlapped, completionRoutine);
        LogSocketError("WSASend", s, rc, &SocketState::lastSendError);
        return rc;
    }

    int WSAAPI Hook_WSARecv(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesRecv, LPDWORD flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSARecv(s, buffers, bufferCount, bytesRecv, flags, overlapped, completionRoutine);
        LogSocketError("WSARecv", s, rc, &SocketState::lastRecvError);
        return rc;
    }

    int WSAAPI Hook_WSASendTo(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesSent, DWORD flags, const sockaddr* to, int toLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSASendTo(s, buffers, bufferCount, bytesSent, flags, to, toLen, overlapped, completionRoutine);
        LogSocketError("WSASendTo", s, rc, &SocketState::lastSendToError);
        return rc;
    }

    int WSAAPI Hook_WSARecvFrom(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesRecv, LPDWORD flags, sockaddr* from, LPINT fromLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSARecvFrom(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, overlapped, completionRoutine);
        LogSocketError("WSARecvFrom", s, rc, &SocketState::lastRecvFromError);
        return rc;
    }

    struct HookTarget
    {
        const char* name;
        FARPROC hook;
    };

    bool PatchImportSlot(HMODULE module, const char* moduleLabel, IMAGE_THUNK_DATA32* origThunk, IMAGE_THUNK_DATA32* thunk, const HookTarget& target)
    {
        if (!origThunk)
            return false;

        while (origThunk->u1.AddressOfData && thunk->u1.Function)
        {
            if (!(origThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32))
            {
                auto* importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                    reinterpret_cast<uint8_t*>(module) + origThunk->u1.AddressOfData);

                if (std::strcmp(reinterpret_cast<const char*>(importByName->Name), target.name) == 0)
                {
                    DWORD oldProtect = 0;
                    if (!VirtualProtect(&thunk->u1.Function, sizeof(thunk->u1.Function), PAGE_READWRITE, &oldProtect))
                        return false;

                    thunk->u1.Function = static_cast<DWORD>(reinterpret_cast<uintptr_t>(target.hook));
                    VirtualProtect(&thunk->u1.Function, sizeof(thunk->u1.Function), oldProtect, &oldProtect);

                    Logf("[OpenShimNet] Patched %s import in %s", target.name, moduleLabel);
                    return true;
                }
            }

            ++origThunk;
            ++thunk;
        }

        return false;
    }

    void PatchWinsockImportsForModule(HMODULE module, const char* moduleLabel)
    {
        if (!module)
        {
            LogShimA(LogLevel::Debug, "net", "[OpenShimNet] Module %s not loaded; skipping Winsock IAT patching", moduleLabel);
            return;
        }

        auto* base = reinterpret_cast<uint8_t*>(module);
        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        {
            LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Module %s has invalid DOS signature; skipping", moduleLabel);
            return;
        }

        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
        {
            LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Module %s has invalid NT signature; skipping", moduleLabel);
            return;
        }

        const auto& importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
        if (importDir.VirtualAddress == 0)
        {
            LogShimA(LogLevel::Debug, "net", "[OpenShimNet] Module %s has no import table; skipping", moduleLabel);
            return;
        }

        auto* importDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + importDir.VirtualAddress);
        for (; importDesc->Name; ++importDesc)
        {
            const char* dllName = reinterpret_cast<const char*>(base + importDesc->Name);
            if (_stricmp(dllName, "ws2_32.dll") != 0)
                continue;

            auto* origThunk = importDesc->OriginalFirstThunk
                ? reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->OriginalFirstThunk)
                : reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->FirstThunk);

            auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->FirstThunk);

            const HookTarget targets[] =
            {
                { "WSASocketW", reinterpret_cast<FARPROC>(Hook_WSASocketW) },
                { "WSASend", reinterpret_cast<FARPROC>(Hook_WSASend) },
                { "WSARecv", reinterpret_cast<FARPROC>(Hook_WSARecv) },
                { "WSASendTo", reinterpret_cast<FARPROC>(Hook_WSASendTo) },
                { "WSARecvFrom", reinterpret_cast<FARPROC>(Hook_WSARecvFrom) },
            };

            int patched = 0;
            for (const auto& target : targets)
                patched += PatchImportSlot(module, moduleLabel, origThunk, thunk, target) ? 1 : 0;

            Logf("[OpenShimNet] %s Winsock IAT hooks installed: %d", moduleLabel, patched);
            return;
        }

        LogShimA(LogLevel::Debug, "net", "[OpenShimNet] Module %s does not import ws2_32.dll; no hooks installed", moduleLabel);
    }
} // namespace

    void InitializeNetworkOptimizer()
    {
        LoadConfig();

        LogShimA(LogLevel::Info, "net", "[OpenShimNet] Initializing");
        LogNetIniValues();
        Logf("[OpenShimNet] Config enabled=%d logging=%d sendBufferSize=%u recvBufferSize=%u applySocketBuffers=%d tcpNoDelay=%d keepAlive=%d disableUdpConnReset=%d logSocketErrors=%d",
            g_Config.enabled ? 1 : 0,
            g_Config.logging ? 1 : 0,
            g_Config.sendBufferSize,
            g_Config.recvBufferSize,
            g_Config.applySocketBuffers ? 1 : 0,
            g_Config.tcpNoDelay ? 1 : 0,
            g_Config.keepAlive ? 1 : 0,
            g_Config.disableUdpConnReset ? 1 : 0,
            g_Config.logSocketErrors ? 1 : 0);
        if (!g_Config.applySocketBuffers)
            LogShimA(LogLevel::Info, "net", "[OpenShimNet] netcode_manifest.json detected; skipping socket buffer overrides");

        if (!g_Config.enabled)
        {
            LogShimA(LogLevel::Info, "net", "[OpenShimNet] Socket optimizer disabled by configuration");
            return;
        }

        if (!LoadWinsockExports())
            return;

        PatchWinsockImportsForModule(GetModuleHandleA(nullptr), "battlezone98redux.exe");
        PatchWinsockImportsForModule(GetModuleHandleA("Galaxy.dll"), "Galaxy.dll");
        PatchWinsockImportsForModule(GetModuleHandleA("GalaxyPeer.dll"), "GalaxyPeer.dll");
        PatchWinsockImportsForModule(GetModuleHandleA("steam_api.dll"), "steam_api.dll");

        LogShimA(LogLevel::Info, "net", "[OpenShimNet] Initialization complete");
    }
}
