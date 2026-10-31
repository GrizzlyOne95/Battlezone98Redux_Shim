#define _CRT_RAND_S
#include "lan_session.h"
#include "lan_discovery.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <ws2ipdef.h>
#include <mstcpip.h>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <set>
#include <vector>

namespace BZROpenShim::LanSession
{
    namespace
    {
        struct State
        {
            Snapshot snapshot;
            SOCKET discovery = INVALID_SOCKET;
            LanDiscovery::Nonce nonce{};
            ULONGLONG scanSince = 0, lastQuery = 0, hostSince = 0;
            bool winsock = false;
            HANDLE process = nullptr, job = nullptr, input = nullptr, output = nullptr;
            std::string pendingOutput;
            std::filesystem::path hostLog;
        };
        // Intentionally retained until process teardown. The kernel closes the
        // job then; its kill-on-close policy prevents an orphaned helper. A DLL
        // detach handler must not wait on a process or enter Winsock.
        State& Data() { static State* state = new State; return *state; }
        void Close(HANDLE& handle)
        {
            if (handle && handle != INVALID_HANDLE_VALUE) CloseHandle(handle);
            handle = nullptr;
        }
        bool Winsock()
        {
            auto& s = Data();
            if (!s.winsock)
            {
                WSADATA data{};
                s.winsock = WSAStartup(MAKEWORD(2, 2), &data) == 0;
            }
            return s.winsock;
        }
        std::vector<INTERFACE_INFO> Interfaces(SOCKET socket)
        {
            std::vector<INTERFACE_INFO> list(64);
            DWORD size = 0;
            if (WSAIoctl(socket, SIO_GET_INTERFACE_LIST, nullptr, 0, list.data(),
                    static_cast<DWORD>(list.size() * sizeof(INTERFACE_INFO)), &size,
                    nullptr, nullptr) == SOCKET_ERROR)
                return {};
            list.resize(size / sizeof(INTERFACE_INFO));
            return list;
        }
        std::string HostAddress()
        {
            if (!Winsock()) return {};
            SOCKET socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (socket == INVALID_SOCKET) return {};
            // UDP connect chooses the routed local interface without sending a
            // packet. Prefer it over WSL/Hyper-V enumeration order. A private
            // fallback still permits isolated LANs with no default route.
            sockaddr_in route{}; route.sin_family = AF_INET;
            route.sin_addr.s_addr = htonl(0x08080808); route.sin_port = htons(9);
            sockaddr_in local{}; int localSize = sizeof(local);
            uint32_t preferred = 0;
            if (connect(socket, reinterpret_cast<sockaddr*>(&route), sizeof(route)) == 0 &&
                getsockname(socket, reinterpret_cast<sockaddr*>(&local), &localSize) == 0)
                preferred = local.sin_addr.s_addr;
            auto list = Interfaces(socket);
            closesocket(socket);
            std::stable_sort(list.begin(), list.end(), [preferred](const auto& a, const auto& b) {
                return a.iiAddress.AddressIn.sin_addr.s_addr == preferred &&
                       b.iiAddress.AddressIn.sin_addr.s_addr != preferred;
            });
            for (const auto& item : list)
            {
                const auto ip = ntohl(item.iiAddress.AddressIn.sin_addr.s_addr);
                if (!(item.iiFlags & IFF_UP) || (item.iiFlags & IFF_LOOPBACK) ||
                    !LanDiscovery::IsLocalIPv4(ip)) continue;
                char text[INET_ADDRSTRLEN]{};
                if (InetNtopA(AF_INET, &item.iiAddress.AddressIn.sin_addr, text, sizeof(text)))
                    return text;
            }
            return {};
        }
        std::wstring Quote(const std::wstring& value)
        {
            std::wstring result = L"\"";
            size_t slashes = 0;
            for (wchar_t ch : value)
            {
                if (ch == L'\\') { ++slashes; continue; }
                result.append(slashes * (ch == L'\"' ? 2 : 1), L'\\');
                slashes = 0;
                if (ch == L'\"') result += L'\\';
                result += ch;
            }
            result.append(slashes * 2, L'\\');
            return result + L'\"';
        }
        void ReleaseHost()
        {
            auto& s = Data();
            Close(s.input); Close(s.output); Close(s.process); Close(s.job);
            s.pendingOutput.clear();
        }
        void SendQuery()
        {
            auto& s = Data();
            const auto query = LanDiscovery::MakeQuery(s.nonce);
            std::set<uint32_t> targets{INADDR_BROADCAST, 0x7F000001};
            for (const auto& item : Interfaces(s.discovery))
            {
                const auto ip = ntohl(item.iiAddress.AddressIn.sin_addr.s_addr);
                const auto mask = ntohl(item.iiNetmask.AddressIn.sin_addr.s_addr);
                if ((item.iiFlags & IFF_UP) && (item.iiFlags & IFF_BROADCAST) &&
                    LanDiscovery::IsLocalIPv4(ip) && mask != 0)
                    targets.insert(ip | ~mask);
            }
            for (const auto ip : targets)
            {
                sockaddr_in address{};
                address.sin_family = AF_INET;
                address.sin_port = htons(LanDiscovery::kPort);
                address.sin_addr.s_addr = htonl(ip);
                sendto(s.discovery, reinterpret_cast<const char*>(query.data()),
                    static_cast<int>(query.size()), 0,
                    reinterpret_cast<sockaddr*>(&address), sizeof(address));
            }
            s.lastQuery = GetTickCount64();
        }
        std::string HostFailure()
        {
            // Read only this launch's bounded log tail after process exit.
            HANDLE file = CreateFileW(Data().hostLog.c_str(), GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
            if (file == INVALID_HANDLE_VALUE) return {};
            LARGE_INTEGER size{};
            std::string tail;
            if (GetFileSizeEx(file, &size))
            {
                LARGE_INTEGER start{}; start.QuadPart = (std::max)(0LL, size.QuadPart - 4096);
                if (SetFilePointerEx(file, start, nullptr, FILE_BEGIN))
                {
                    char bytes[4096]; DWORD count = 0;
                    if (ReadFile(file, bytes, sizeof(bytes), &count, nullptr)) tail.assign(bytes, count);
                }
            }
            CloseHandle(file);
            while (!tail.empty() && (tail.back() == '\r' || tail.back() == '\n')) tail.pop_back();
            const auto last = tail.find_last_of('\n');
            if (last != std::string::npos) tail.erase(0, last + 1);
            for (auto& ch : tail) if (static_cast<unsigned char>(ch) < 32 || static_cast<unsigned char>(ch) > 126) ch = ' ';
            return tail.substr(0, 240);
        }
        void PumpOutput()
        {
            auto& s = Data();
            // Bounded work on the UI thread, even if a helper writes garbage.
            DWORD available = 0;
            for (int i = 0; i < 8 && s.output &&
                 PeekNamedPipe(s.output, nullptr, 0, nullptr, &available, nullptr) && available; ++i)
            {
                char buffer[512]; DWORD read = 0;
                if (!ReadFile(s.output, buffer, (std::min)(available, DWORD(sizeof(buffer))), &read, nullptr)) break;
                s.pendingOutput.append(buffer, read);
                size_t newline;
                while ((newline = s.pendingOutput.find('\n')) != std::string::npos)
                {
                    auto line = s.pendingOutput.substr(0, newline);
                    s.pendingOutput.erase(0, newline + 1);
                    if (!line.empty() && line.back() == '\r') line.pop_back();
                    if (line == "BZRLAN_READY 1337" && s.snapshot.state == HostState::Starting)
                    {
                        s.snapshot.state = HostState::Running;
                        s.snapshot.hostMessage = "Hosting on " + s.snapshot.hostAddress;
                    }
                }
                if (s.pendingOutput.size() > 4096) s.pendingOutput.clear();
            }
        }
    }

    bool StartHost(const std::wstring& gameRoot)
    {
        auto& s = Data();
        Tick();
        if (s.process) return s.snapshot.state == HostState::Running || s.snapshot.state == HostState::Starting;
        s.snapshot.state = HostState::Failed;
        s.snapshot.hostAddress = HostAddress();
        if (s.snapshot.hostAddress.empty())
        { s.snapshot.hostMessage = "No active LAN IPv4 address found."; return false; }
        const auto root = std::filesystem::path(gameRoot);
        const auto executable = root / L"tools" / L"lan" / L"BZRServer.exe";
        const DWORD attributes = GetFileAttributesW(executable.c_str());
        if (attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY))
        { s.snapshot.hostMessage = "LAN helper missing: install tools/lan/BZRServer.exe."; return false; }
        const auto runtime = root / L"openshim" / L"lan";
        std::error_code error;
        std::filesystem::create_directories(runtime, error);
        if (error)
        { s.snapshot.hostMessage = "Cannot create openshim/lan for host state."; return false; }

        SECURITY_ATTRIBUTES security{sizeof(security), nullptr, TRUE};
        HANDLE childInput = nullptr, childOutput = nullptr;
        s.hostLog = runtime / L"host.log";
        HANDLE childLog = CreateFileW(s.hostLog.c_str(), FILE_APPEND_DATA,
            FILE_SHARE_READ | FILE_SHARE_WRITE, &security, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (childLog == INVALID_HANDLE_VALUE)
        { s.snapshot.hostMessage = "Cannot open openshim/lan/host.log."; return false; }
        if (!CreatePipe(&childInput, &s.input, &security, 0) ||
            !CreatePipe(&s.output, &childOutput, &security, 0))
        {
            Close(childInput); Close(childOutput); Close(childLog); ReleaseHost();
            s.snapshot.hostMessage = "Cannot create LAN helper pipes."; return false;
        }
        SetHandleInformation(s.input, HANDLE_FLAG_INHERIT, 0);
        SetHandleInformation(s.output, HANDLE_FLAG_INHERIT, 0);
        STARTUPINFOEXW startup{};
        startup.StartupInfo.cb = sizeof(startup);
        startup.StartupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
        startup.StartupInfo.wShowWindow = SW_HIDE;
        startup.StartupInfo.hStdInput = childInput;
        startup.StartupInfo.hStdOutput = childOutput;
        // Logging must never fill a pipe while a mission is running and the
        // menu pump is idle. Only the one-line READY protocol uses stdout.
        startup.StartupInfo.hStdError = childLog;
        SIZE_T bytes = 0;
        InitializeProcThreadAttributeList(nullptr, 1, 0, &bytes);
        std::vector<uint8_t> storage(bytes);
        startup.lpAttributeList = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(storage.data());
        HANDLE inherit[] = { childInput, childOutput, childLog };
        bool initialized = InitializeProcThreadAttributeList(startup.lpAttributeList, 1, 0, &bytes) != FALSE;
        bool attributesOk = initialized && UpdateProcThreadAttribute(startup.lpAttributeList, 0,
            PROC_THREAD_ATTRIBUTE_HANDLE_LIST, inherit, sizeof(inherit), nullptr, nullptr);
        s.job = CreateJobObjectW(nullptr, nullptr);
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
        limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        const bool jobOk = s.job && SetInformationJobObject(s.job,
            JobObjectExtendedLimitInformation, &limits, sizeof(limits));
        std::wstring command = Quote(executable.wstring()) +
            L" --lan-discovery --lan-managed --stdin-control --health-port 0 --access-mode open"
            L" --ws-host " + std::wstring(s.snapshot.hostAddress.begin(), s.snapshot.hostAddress.end()) +
            L" --ws-port 1337 --udp-host " + std::wstring(s.snapshot.hostAddress.begin(), s.snapshot.hostAddress.end()) +
            L" --udp-port 1338 --relay-host " + std::wstring(s.snapshot.hostAddress.begin(), s.snapshot.hostAddress.end()) +
            L" --relay-port 1339 --relay-pair-ports"
            L" --relay-pair-port-start 1340 --relay-pair-port-end 1369 --state-file " +
            Quote((runtime / L"state.json").wstring()) + L" --audit-log " +
            Quote((runtime / L"audit.log").wstring());
        PROCESS_INFORMATION process{};
        const bool created = attributesOk && jobOk && CreateProcessW(executable.c_str(),
            command.data(), nullptr, nullptr, TRUE,
            CREATE_NO_WINDOW | CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT,
            nullptr, executable.parent_path().c_str(), &startup.StartupInfo, &process);
        if (initialized) DeleteProcThreadAttributeList(startup.lpAttributeList);
        Close(childInput); Close(childOutput); Close(childLog);
        if (!created)
        { ReleaseHost(); s.snapshot.hostMessage = "Cannot start LAN helper."; return false; }
        s.process = process.hProcess;
        if (!AssignProcessToJobObject(s.job, s.process))
        {
            TerminateProcess(s.process, 1); // only our still-suspended child
            Close(process.hThread); ReleaseHost();
            s.snapshot.hostMessage = "Cannot supervise LAN helper; hosting cancelled."; return false;
        }
        if (ResumeThread(process.hThread) == DWORD(-1))
        {
            Close(process.hThread); ReleaseHost();
            s.snapshot.hostMessage = "Cannot resume LAN helper."; return false;
        }
        Close(process.hThread);
        s.hostSince = GetTickCount64();
        s.snapshot.state = HostState::Starting;
        s.snapshot.hostMessage = "Starting LAN host...";
        return true;
    }

    void StopHost()
    {
        auto& s = Data();
        if (!s.process || s.snapshot.state == HostState::Stopping) return;
        DWORD written = 0;
        if (s.input) WriteFile(s.input, "stop\n", 5, &written, nullptr);
        Close(s.input);
        s.hostSince = GetTickCount64();
        s.snapshot.state = HostState::Stopping;
        s.snapshot.hostMessage = "Stopping host (connected players will disconnect)...";
    }

    void StopScan()
    {
        auto& s = Data();
        if (s.discovery != INVALID_SOCKET) closesocket(s.discovery);
        s.discovery = INVALID_SOCKET;
        s.snapshot.scanning = false;
    }

    bool StartScan()
    {
        auto& s = Data();
        StopScan();
        s.snapshot.hosts.clear();
        s.snapshot.scanMessage = "Cannot start LAN search.";
        if (!Winsock()) return false;
        unsigned random[2]{};
        if (rand_s(&random[0]) || rand_s(&random[1])) return false;
        std::memcpy(s.nonce.data(), random, sizeof(random));
        s.discovery = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (s.discovery == INVALID_SOCKET) return false;
        BOOL broadcast = TRUE;
        u_long nonblocking = 1;
        sockaddr_in local{}; local.sin_family = AF_INET;
        if (setsockopt(s.discovery, SOL_SOCKET, SO_BROADCAST,
                reinterpret_cast<const char*>(&broadcast), sizeof(broadcast)) == SOCKET_ERROR ||
            bind(s.discovery, reinterpret_cast<sockaddr*>(&local), sizeof(local)) == SOCKET_ERROR ||
            ioctlsocket(s.discovery, FIONBIO, &nonblocking) == SOCKET_ERROR)
        { StopScan(); return false; }
        s.snapshot.scanning = true;
        s.snapshot.scanMessage = "Searching the LAN...";
        s.scanSince = GetTickCount64();
        SendQuery();
        return true;
    }

    void Tick()
    {
        auto& s = Data();
        if (s.process)
        {
            PumpOutput();
            if (WaitForSingleObject(s.process, 0) == WAIT_OBJECT_0)
            {
                const bool stopped = s.snapshot.state == HostState::Stopping;
                const auto detail = stopped ? std::string{} : HostFailure();
                ReleaseHost();
                s.snapshot.state = stopped ? HostState::Stopped : HostState::Failed;
                s.snapshot.hostMessage = stopped ? "LAN host stopped." :
                    detail.empty() ? "LAN helper exited. See openshim/lan/host.log (ports 1337-1369, UDP 21337)." :
                    "LAN helper exited: " + detail;
            }
            else if (s.snapshot.state == HostState::Starting && GetTickCount64() - s.hostSince > 30000)
            {
                StopHost();
                s.snapshot.hostMessage = "LAN helper startup timed out; stopping.";
            }
            else if (s.snapshot.state == HostState::Stopping && GetTickCount64() - s.hostSince > 5000)
            {
                ReleaseHost(); // kill-on-close applies only to our child tree
                s.snapshot.state = HostState::Failed;
                s.snapshot.hostMessage = "LAN helper did not stop; its owned process was closed.";
            }
        }
        if (!s.snapshot.scanning) return;
        for (int i = 0; i < 64; ++i)
        {
            char buffer[256]; sockaddr_in sender{}; int size = sizeof(sender);
            const int count = recvfrom(s.discovery, buffer, sizeof(buffer), 0,
                reinterpret_cast<sockaddr*>(&sender), &size);
            if (count == SOCKET_ERROR) break;
            LanDiscovery::Reply reply;
            if (size != sizeof(sender) || sender.sin_family != AF_INET ||
                ntohs(sender.sin_port) != LanDiscovery::kPort ||
                !LanDiscovery::IsLocalIPv4(ntohl(sender.sin_addr.s_addr)) ||
                !LanDiscovery::ParseReply({buffer, static_cast<size_t>(count)}, s.nonce, reply)) continue;
            char address[INET_ADDRSTRLEN]{};
            if (!InetNtopA(AF_INET, &sender.sin_addr, address, sizeof(address))) continue;
            const auto found = std::find_if(s.snapshot.hosts.begin(), s.snapshot.hosts.end(),
                [&](const Host& host) { return host.address == address && host.port == reply.port; });
            if (found != s.snapshot.hosts.end()) found->name = reply.name;
            else if (s.snapshot.hosts.size() < LanDiscovery::kMaxHosts)
                s.snapshot.hosts.push_back({address, reply.name, reply.port});
        }
        const auto now = GetTickCount64();
        if (now - s.scanSince >= 3000)
        {
            StopScan();
            s.snapshot.scanMessage = s.snapshot.hosts.empty() ?
                "No hosts found. Try Refresh or enter the host IP below." : "Select a host below.";
        }
        else if (now - s.lastQuery >= 750) SendQuery();
    }

    Snapshot Status() { return Data().snapshot; }
}
