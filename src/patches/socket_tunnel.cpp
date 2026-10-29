#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define FD_SETSIZE 1024
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "socket_tunnel.h"
#include "socket_tunnel_protocol.h"
#include "steam_tunnel_transport.h"
#include <algorithm>
#include <cstdio>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <utility>

namespace BZROpenShim::SocketTunnel
{
namespace
{
    struct Socket
    {
        SOCKET s = INVALID_SOCKET;
        Socket() = default;
        explicit Socket(SOCKET value) : s(value) {}
        ~Socket() { if (s != INVALID_SOCKET) closesocket(s); }
        Socket(Socket&& other) noexcept : s(std::exchange(other.s, INVALID_SOCKET)) {}
        Socket& operator=(Socket&& other) noexcept
        { if (s != INVALID_SOCKET) closesocket(s); s = std::exchange(other.s, INVALID_SOCKET); return *this; }
        Socket(const Socket&) = delete;
    };
    sockaddr_in Address(const std::string& ip, uint16_t port)
    {
        sockaddr_in a{}; a.sin_family = AF_INET; a.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &a.sin_addr) != 1) throw std::runtime_error("numeric IPv4 required");
        return a;
    }
    bool Same(const sockaddr_in& a, const sockaddr_in& b)
    { return a.sin_addr.s_addr == b.sin_addr.s_addr && a.sin_port == b.sin_port; }
    bool WouldBlock() { return WSAGetLastError() == WSAEWOULDBLOCK; }
    void Nonblock(SOCKET s)
    { u_long yes = 1; if (ioctlsocket(s, FIONBIO, &yes)) throw std::runtime_error("FIONBIO failed"); }
    Socket Bound(int type, const std::string& ip, uint16_t port)
    {
        Socket s(socket(AF_INET, type, 0));
        if (s.s == INVALID_SOCKET) throw std::runtime_error("socket failed");
        BOOL exclusive = TRUE;
        if (setsockopt(s.s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char*>(&exclusive), sizeof(exclusive)))
            throw std::runtime_error("exclusive bind option failed");
        const auto a = Address(ip, port);
        if (bind(s.s, reinterpret_cast<const sockaddr*>(&a), sizeof(a))) throw std::runtime_error("bind failed (port occupied?)");
        Nonblock(s.s);
        if (type == SOCK_STREAM)
        {
            BOOL yes = TRUE; setsockopt(s.s, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes));
        }
        else
        {
            // A closed pair-relay port must not poison this shared UDP socket.
            BOOL no = FALSE; DWORD returned = 0;
            WSAIoctl(s.s, _WSAIOW(IOC_VENDOR, 12), &no, sizeof(no), nullptr, 0, &returned, nullptr, nullptr);
            int size = 1024 * 1024;
            setsockopt(s.s, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char*>(&size), sizeof(size));
        }
        return s;
    }
    struct Stream
    {
        Socket socket;
        bool connecting = false, readEof = false, remoteEof = false, writeClosed = false;
        uint64_t opened = 0;
        std::vector<uint8_t> output;
        size_t offset = 0;
    };
    struct UdpSource { Socket socket; };
    struct Peer
    {
        uint64_t session = 0, seen = 0, ping = 0;
        sockaddr_in address{};
        std::string sourceIp;
        bool connected = false, failed = false;
        uint32_t connection = 0;
        bool pendingNative = false;
        Frame nativeFrame;
        ReliableQueue reliable;
        std::map<uint32_t, Stream> streams;
        std::map<uint16_t, UdpSource> udp;
    };
    struct Runtime
    {
        const Config& cfg;
        Logger logger;
        Socket wire, listener;
        std::map<uint16_t, Socket> ports;
        std::map<uint64_t, Peer> peers;
        std::set<uint16_t> localSources;
        std::vector<uint32_t> allowed;
        std::unique_ptr<SteamTransport> steam;
        SteamIdentityMap identityMap;
        HANDLE identityLock = INVALID_HANDLE_VALUE;
        uint32_t nextStream = 1;
        uint64_t tx = 0, rx = 0, retries = 0, drops = 0;
        explicit Runtime(const Config& c, Logger l) : cfg(c), logger(l) {}
        void Log(const char* message) { if (logger) logger(message); }
        static uint64_t NewSession()
        {
            std::random_device random;
            uint64_t n = (uint64_t(random()) << 32) ^ random(); return n ? n : 1;
        }
        void NewClient(uint64_t now)
        {
            peers.clear(); localSources.clear();
            Peer p; p.session = NewSession(); p.address = Address(cfg.remote, cfg.port); p.seen = now;
            peers.emplace(p.session, std::move(p));
        }
        static std::wstring Wide(const std::string& text)
        {
            const int n = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.c_str(), -1, nullptr, 0);
            if (!n) throw std::runtime_error("identity-map path is not UTF-8");
            std::wstring result(size_t(n), 0);
            MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.c_str(), -1, result.data(), n);
            result.resize(size_t(n - 1)); return result;
        }
        void LoadIdentities()
        {
            if (cfg.identityMap.empty()) throw std::runtime_error("Steam bridge requires an identity-map path");
            const auto path = Wide(cfg.identityMap);
            identityLock = CreateFileW((path + L".lock").c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (identityLock == INVALID_HANDLE_VALUE) throw std::runtime_error("identity-map lock unavailable (directory missing or another bridge running)");
            HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
            {
                if (GetLastError() == ERROR_FILE_NOT_FOUND) return;
                throw std::runtime_error("cannot read Steam identity map");
            }
            LARGE_INTEGER size{}; DWORD read = 0;
            const bool sized = GetFileSizeEx(file, &size) && size.QuadPart <= 16384;
            std::string text(sized ? size_t(size.QuadPart) : 0, 0);
            const bool ok = sized && ReadFile(file, text.data(), DWORD(text.size()), &read, nullptr) && read == text.size();
            CloseHandle(file);
            if (!ok || !identityMap.Load(text)) throw std::runtime_error("invalid Steam identity map; preserve/repair it before retrying");
            for (const auto& entry : identityMap.slots)
                if (SteamIdentityMap::Ip(entry.second) == cfg.server) throw std::runtime_error("identity-map address conflicts with server address");
        }
        std::string SteamSource(uint64_t id)
        {
            if (auto slot = identityMap.Find(id)) return SteamIdentityMap::Ip(slot);
            auto updated = identityMap;
            const auto slot = updated.Assign(id, cfg.server);
            if (!slot) throw std::runtime_error("Steam identity map exhausted; new peer refused");
            const auto text = updated.Save(), pathText = cfg.identityMap;
            const auto path = Wide(pathText), temporary = path + L".tmp";
            HANDLE file = CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE) throw std::runtime_error("cannot write Steam identity map");
            DWORD written = 0;
            const bool ok = WriteFile(file, text.data(), DWORD(text.size()), &written, nullptr) && written == text.size() && FlushFileBuffers(file);
            CloseHandle(file);
            if (!ok || !MoveFileExW(temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
                throw std::runtime_error("cannot persist Steam peer identity; peer refused");
            identityMap = std::move(updated);
            return SteamIdentityMap::Ip(slot);
        }
        void Start(uint64_t now, std::atomic<bool>& stop)
        {
            if (!cfg.bridge && cfg.listen != "127.0.0.1") throw std::runtime_error("agent must bind 127.0.0.1");
            if (cfg.bridge && !IsLoopback(cfg.server)) throw std::runtime_error("bridge server must be loopback");
            if (cfg.steam)
            {
                if (cfg.bridge) LoadIdentities();
                steam.reset(new SteamTransport);
                steam->Start(cfg, stop, logger);
            }
            else
            {
                size_t start = 0;
                do
                {
                    const auto comma = cfg.allow.find(',', start);
                    allowed.push_back(Address(cfg.allow.substr(start, comma - start), 0).sin_addr.s_addr);
                    if (comma == std::string::npos) break;
                    start = comma + 1;
                } while (allowed.size() <= 8);
                if (allowed.size() > 8) throw std::runtime_error("at most eight allowed client addresses");
                Address(cfg.remote, 0);
                wire = Bound(SOCK_DGRAM, cfg.listen, cfg.bridge ? cfg.port : 0);
            }
            if (!cfg.bridge)
            {
                listener = Bound(SOCK_STREAM, cfg.listen, 1337);
                if (listen(listener.s, 8)) throw std::runtime_error("listen failed");
                for (uint16_t port = 1338; port <= 1369; ++port) ports.emplace(port, Bound(SOCK_DGRAM, cfg.listen, port));
                if (!cfg.steam) NewClient(now);
            }
            Log(cfg.bridge ? "bridge ready (TCP 1337 / UDP 1338-1369 only)" : "agent ready on 127.0.0.1 (TCP 1337 / UDP 1338-1369)");
        }
        void Send(Peer& p, Frame f)
        {
            f.session = p.session;
            auto b = Encode(f);
            if (steam)
            {
                const bool reliable = Reliable(f.kind) || f.kind == Kind::Hello || f.kind == Kind::Welcome;
                const auto sent = steam->Send(p.connection, b, reliable);
                if (sent == SteamSend::Sent) tx += b.size();
                else { ++drops; if (reliable || sent == SteamSend::Failed) p.failed = true; }
                return;
            }
            const int n = sendto(wire.s, reinterpret_cast<const char*>(b.data()), int(b.size()), 0,
                                 reinterpret_cast<const sockaddr*>(&p.address), sizeof(p.address));
            if (n >= 0) tx += uint64_t(n); else ++drops;
        }
        void Queue(Peer& p, Frame f)
        {
            f.session = p.session;
            if (!p.reliable.Push(std::move(f))) p.failed = true;
        }
        Peer* FindPeer(const Frame& f, const sockaddr_in& address, uint64_t now)
        {
            auto it = peers.find(f.session);
            if (it != peers.end()) return Same(it->second.address, address) ? &it->second : nullptr;
            if (!cfg.bridge || f.kind != Kind::Hello || peers.size() >= 8 ||
                std::find(allowed.begin(), allowed.end(), address.sin_addr.s_addr) == allowed.end()) return nullptr;
            // A slot remains reserved until the old session expires. Replayed
            // HELLOs cannot steal an active peer's loopback identity.
            unsigned slot = 10;
            for (; slot < 26; ++slot)
            {
                bool used = cfg.server == "127.0.0." + std::to_string(slot);
                for (const auto& entry : peers) if (entry.second.sourceIp == "127.0.0." + std::to_string(slot)) used = true;
                if (!used) break;
            }
            Peer p; p.session = f.session; p.address = address; p.sourceIp = "127.0.0." + std::to_string(slot);
            p.connected = true; p.seen = now;
            char message[160]; std::snprintf(message, sizeof(message), "plain-UDP peer admitted as %s (trusted test transport)", p.sourceIp.c_str()); Log(message);
            return &peers.emplace(f.session, std::move(p)).first->second;
        }
        bool Deliver(Peer& p, const Frame& f, uint64_t now)
        {
            if (f.kind == Kind::Open)
            {
                if (!cfg.bridge || p.streams.count(f.stream)) return false;
                if (p.streams.size() >= 16) { Queue(p, Frame{Kind::Reset, 0, 0, f.stream}); return true; }
                Stream stream; stream.socket = Bound(SOCK_STREAM, p.sourceIp, 0); stream.opened = now;
                const auto target = Address(cfg.server, 1337);
                const int rc = connect(stream.socket.s, reinterpret_cast<const sockaddr*>(&target), sizeof(target));
                if (rc && !WouldBlock()) { Queue(p, Frame{Kind::Reset, 0, 0, f.stream}); return true; }
                stream.connecting = rc != 0;
                p.streams.emplace(f.stream, std::move(stream)); return true;
            }
            auto it = p.streams.find(f.stream);
            // A reset can cross queued DATA/FIN. ACK and discard frames for a
            // retired stream; stream IDs never repeat within one session.
            if (it == p.streams.end()) return true;
            auto& stream = it->second;
            if (f.kind == Kind::Reset) { p.streams.erase(it); return true; }
            if (f.kind == Kind::Close) { stream.remoteEof = true; return true; }
            if (stream.remoteEof) return false;
            if (stream.output.size() - stream.offset + f.data.size() > kQueueMax) return false;
            if (stream.offset) { stream.output.erase(stream.output.begin(), stream.output.begin() + stream.offset); stream.offset = 0; }
            stream.output.insert(stream.output.end(), f.data.begin(), f.data.end()); return true;
        }
        void Datagram(Peer& p, const Frame& f)
        {
            if (cfg.bridge)
            {
                auto it = p.udp.find(f.source);
                if (it == p.udp.end())
                {
                    if (p.udp.size() >= 64) { ++drops; return; }
                    UdpSource u; u.socket = Bound(SOCK_DGRAM, p.sourceIp, 0);
                    it = p.udp.emplace(f.source, std::move(u)).first;
                }
                const auto target = Address(cfg.server, f.port);
                sendto(it->second.socket.s, reinterpret_cast<const char*>(f.data.data()), int(f.data.size()), 0,
                       reinterpret_cast<const sockaddr*>(&target), sizeof(target));
            }
            else
            {
                if (!localSources.count(f.source)) { ++drops; return; }
                auto target = Address("127.0.0.1", f.source);
                sendto(ports.at(f.port).s, reinterpret_cast<const char*>(f.data.data()), int(f.data.size()), 0,
                       reinterpret_cast<const sockaddr*>(&target), sizeof(target));
            }
        }
        void Receive(uint64_t now)
        {
            if (steam) { ReceiveSteam(now); return; }
            uint8_t bytes[65536];
            for (unsigned count = 0; count < 256; ++count)
            {
                sockaddr_in address{}; int size = sizeof(address);
                const int n = recvfrom(wire.s, reinterpret_cast<char*>(bytes), sizeof(bytes), 0, reinterpret_cast<sockaddr*>(&address), &size);
                if (n < 0) break;
                rx += uint64_t(n);
                Frame f;
                if (!Decode(bytes, size_t(n), f)) { ++drops; continue; }
                auto p = FindPeer(f, address, now);
                if (!p) { ++drops; continue; }
                p->seen = now;
                if (cfg.bridge && f.kind == Kind::Hello) Send(*p, Frame{Kind::Welcome});
                else if (!cfg.bridge && f.kind == Kind::Welcome) { if (!p->connected) Log("plain-UDP bridge connected"); p->connected = true; }
                else if (!p->connected) continue;
                else if (f.kind == Kind::Ack) p->reliable.Ack(f.sequence);
                else if (f.kind == Kind::Datagram)
                {
                    try { Datagram(*p, f); }
                    catch (const std::exception&) { p->failed = true; }
                }
                else if (Reliable(f.kind))
                {
                    auto& q = p->reliable;
                    try
                    { if (f.sequence == q.received + 1 && Deliver(*p, f, now)) q.received = f.sequence; }
                    catch (const std::exception&) { p->failed = true; }
                    if (f.sequence <= q.received) Send(*p, Frame{Kind::Ack, 0, f.sequence});
                }
            }
        }
        void ReceiveSteam(uint64_t now)
        {
            for (const auto& event : steam->Poll(now))
            {
                const auto key = uint64_t(event.connection);
                if (!event.connected) { peers.erase(key); if (!cfg.bridge) localSources.clear(); continue; }
                Peer p; p.connection = event.connection; p.seen = now;
                if (!cfg.bridge)
                {
                    peers.clear(); localSources.clear();
                    p.session = NewSession();
                }
                else
                {
                    try { p.sourceIp = SteamSource(event.identity); }
                    catch (const std::exception& error) { Log(error.what()); steam->Close(event.connection); continue; }
                    char message[160]; std::snprintf(message, sizeof(message), "Steam peer=%llu source=%s (persistent)",
                        static_cast<unsigned long long>(event.identity), p.sourceIp.c_str()); Log(message);
                }
                peers.emplace(key, std::move(p));
                if (!cfg.bridge) Send(peers.at(key), Frame{Kind::Hello});
            }
            for (auto& entry : peers)
            {
                auto& p = entry.second;
                for (unsigned count = 0; count < 32 && !p.failed; ++count)
                {
                    Frame frame;
                    if (p.pendingNative) { frame = std::move(p.nativeFrame); p.pendingNative = false; }
                    else
                    {
                        std::vector<uint8_t> bytes; bool reliable = false;
                        const int n = steam->Receive(p.connection, bytes, reliable);
                        if (!n) break;
                        if (n < 0 || !Decode(bytes.data(), bytes.size(), frame) ||
                            reliable != (Reliable(frame.kind) || frame.kind == Kind::Hello || frame.kind == Kind::Welcome))
                        { p.failed = true; break; }
                        rx += bytes.size();
                        p.seen = now;
                    }
                    if (cfg.bridge && !p.session && frame.kind == Kind::Hello) p.session = frame.session;
                    if (!p.session || frame.session != p.session) { ++drops; continue; }
                    if (cfg.bridge && frame.kind == Kind::Hello)
                    { p.connected = true; Send(p, Frame{Kind::Welcome}); }
                    else if (!cfg.bridge && frame.kind == Kind::Welcome)
                    { if (!p.connected) Log("Steam tunnel handshake complete"); p.connected = true; }
                    else if (frame.kind == Kind::Datagram && p.connected)
                    {
                        try { Datagram(p, frame); } catch (const std::exception&) { p.failed = true; }
                    }
                    else if (Reliable(frame.kind) && p.connected)
                    {
                        if (frame.sequence != p.reliable.received + 1) { p.failed = true; break; }
                        try
                        {
                            if (!Deliver(p, frame, now))
                            { p.nativeFrame = std::move(frame); p.pendingNative = true; break; }
                            p.reliable.received = frame.sequence;
                        }
                        catch (const std::exception&) { p.failed = true; }
                    }
                    else if (frame.kind != Kind::Ping) { p.failed = true; break; }
                }
            }
        }
        void Accept(Peer& p, uint64_t now)
        {
            sockaddr_in source{}; int size = sizeof(source);
            Socket accepted(accept(listener.s, reinterpret_cast<sockaddr*>(&source), &size));
            if (accepted.s == INVALID_SOCKET) return;
            if (!p.connected || p.streams.size() >= 16 || !nextStream ||
                source.sin_addr.s_addr != Address("127.0.0.1", 0).sin_addr.s_addr) return;
            Nonblock(accepted.s);
            BOOL yes = TRUE; setsockopt(accepted.s, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes));
            Stream stream; stream.socket = std::move(accepted); stream.opened = now;
            const auto id = nextStream++;
            p.streams.emplace(id, std::move(stream));
            Queue(p, Frame{Kind::Open, 0, 0, id, 1337});
        }
        void PumpStreams(Peer& p, uint64_t now)
        {
            for (auto it = p.streams.begin(); it != p.streams.end();)
            {
                const uint32_t id = it->first; auto& s = it->second;
                bool failed = false;
                if (s.connecting)
                {
                    fd_set write, error; FD_ZERO(&write); FD_ZERO(&error); FD_SET(s.socket.s, &write); FD_SET(s.socket.s, &error);
                    timeval wait{};
                    if (select(0, nullptr, &write, &error, &wait) > 0)
                    {
                        int code = 0, length = sizeof(code);
                        failed = getsockopt(s.socket.s, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&code), &length) != 0 || code != 0;
                        s.connecting = false;
                    }
                    else failed = now - s.opened > 5000;
                }
                if (!s.connecting && !failed)
                {
                    if (s.offset < s.output.size())
                    {
                        const int n = send(s.socket.s, reinterpret_cast<const char*>(s.output.data() + s.offset), int(s.output.size() - s.offset), 0);
                        if (n > 0) s.offset += size_t(n); else if (n < 0 && !WouldBlock()) failed = true;
                    }
                    if (s.offset == s.output.size())
                    {
                        s.output.clear(); s.offset = 0;
                        if (s.remoteEof && !s.writeClosed) { shutdown(s.socket.s, SD_SEND); s.writeClosed = true; }
                    }
                    if (!s.readEof && p.reliable.bytes < kQueueMax - 4096 && p.reliable.pending.size() < 500)
                    {
                        uint8_t bytes[1024]; const int n = recv(s.socket.s, reinterpret_cast<char*>(bytes), sizeof(bytes), 0);
                        if (n > 0) { Frame f{Kind::Data, 0, 0, id}; f.data.assign(bytes, bytes + n); Queue(p, std::move(f)); }
                        else if (n == 0) { s.readEof = true; Queue(p, Frame{Kind::Close, 0, 0, id}); }
                        else if (!WouldBlock()) failed = true;
                    }
                }
                if (failed) Queue(p, Frame{Kind::Reset, 0, 0, id});
                if (failed || (s.readEof && s.writeClosed)) it = p.streams.erase(it); else ++it;
            }
        }
        void PumpUdp(Peer& p)
        {
            uint8_t bytes[kPayloadMax];
            auto read = [&](SOCKET socket, uint16_t tag, bool bridge)
            {
                for (unsigned count = 0; count < 32; ++count)
                {
                    sockaddr_in source{}; int size = sizeof(source);
                    const int n = recvfrom(socket, reinterpret_cast<char*>(bytes), sizeof(bytes), 0, reinterpret_cast<sockaddr*>(&source), &size);
                    if (n < 0) break;
                    const uint16_t port = ntohs(source.sin_port);
                    if (!p.connected) { ++drops; continue; }
                    const auto expected = Address(bridge ? cfg.server : "127.0.0.1", 0);
                    if (source.sin_addr.s_addr != expected.sin_addr.s_addr || (bridge && !GameUdp(port))) { ++drops; continue; }
                    if (!bridge)
                    {
                        if (!localSources.count(port) && localSources.size() >= 64) { ++drops; continue; }
                        localSources.insert(port);
                    }
                    Frame f{Kind::Datagram, 0, 0, 0, bridge ? port : tag, bridge ? tag : port};
                    f.data.assign(bytes, bytes + n); Send(p, std::move(f));
                }
            };
            if (cfg.bridge)
            {
                // Preserve the probe-advertised endpoint across a long lobby
                // idle. The bounded mappings live until this peer disconnects.
                for (auto& source : p.udp) read(source.second.socket.s, source.first, true);
            }
            else
            {
                for (auto& port : ports) read(port.second.s, port.first, false);
            }
        }
        void Tick(uint64_t now)
        {
            Receive(now);
            for (auto it = peers.begin(); it != peers.end();)
            {
                auto& p = it->second;
                if (p.failed || now - p.seen > kIdleMs || p.reliable.Expired(now))
                {
                    Log("peer timeout: closing TCP streams and releasing UDP sockets");
                    if (steam) steam->Close(p.connection);
                    it = peers.erase(it); continue;
                }
                if (now - p.ping >= 1000 && (!steam || p.session))
                {
                    Send(p, Frame{p.connected ? Kind::Ping : Kind::Hello}); p.ping = now;
                }
                if (!cfg.bridge) Accept(p, now);
                if (!cfg.bridge && !p.connected) PumpUdp(p);
                if (p.connected)
                {
                    PumpStreams(p, now); PumpUdp(p);
                    auto& q = p.reliable;
                    if (steam)
                    {
                        // Steam owns reliability and ordering: consume a frame
                        // on successful SDK submission, never on our UDP ACKs.
                        for (unsigned count = 0; count < 32 && !q.pending.empty(); ++count)
                        {
                            const auto bytes = Encode(q.pending.front());
                            const auto sent = steam->Send(p.connection, bytes, true);
                            if (sent == SteamSend::Busy) { if (!q.startedAt) q.startedAt = now; break; }
                            if (sent == SteamSend::Failed) { p.failed = true; break; }
                            tx += bytes.size(); q.Ack(q.pending.front().sequence);
                        }
                    }
                    else if (q.Due(now)) { if (q.sentAt) ++retries; Send(p, q.pending.front()); q.Sent(now); }
                }
                ++it;
            }
            if (!cfg.bridge && peers.empty() && !steam) NewClient(now);
            if (!cfg.bridge && peers.empty() && steam)
            {
                // Refuse game streams while Steam reconnects; drain stale UDP.
                Peer offline; Accept(offline, now); PumpUdp(offline);
            }
        }
        void Wait()
        {
            // Socket readiness wakes immediately. Sleep(1) rounds up to a
            // Windows timer tick and adds tens of ms across four tunnel hops.
            fd_set read, write, error; FD_ZERO(&read); FD_ZERO(&write); FD_ZERO(&error);
            if (wire.s != INVALID_SOCKET) FD_SET(wire.s, &read);
            if (!cfg.bridge) FD_SET(listener.s, &read);
            for (auto& port : ports) FD_SET(port.second.s, &read);
            for (auto& entry : peers)
            {
                auto& p = entry.second;
                for (auto& udp : p.udp) FD_SET(udp.second.socket.s, &read);
                for (auto& stream : p.streams)
                {
                    auto& s = stream.second;
                    if (!s.connecting && !s.readEof && p.reliable.bytes < kQueueMax - 4096 && p.reliable.pending.size() < 500)
                        FD_SET(s.socket.s, &read);
                    if (s.connecting || s.offset < s.output.size()) FD_SET(s.socket.s, &write);
                    FD_SET(s.socket.s, &error);
                }
            }
            timeval timeout{0, 5000};
            if (read.fd_count || write.fd_count || error.fd_count) select(0, &read, &write, &error, &timeout);
            else Sleep(5);
        }
        ~Runtime()
        {
            steam.reset(); // stop callbacks/connections before peer state and WSA cleanup
            if (identityLock != INVALID_HANDLE_VALUE) CloseHandle(identityLock);
            char message[200]; std::snprintf(message, sizeof(message), "tunnel stopped: wire tx=%llu rx=%llu retransmits=%llu drops=%llu",
                static_cast<unsigned long long>(tx), static_cast<unsigned long long>(rx),
                static_cast<unsigned long long>(retries), static_cast<unsigned long long>(drops)); Log(message);
        }
    };
}
    bool IsLoopback(const std::string& ip)
    {
        IN_ADDR a{};
        return inet_pton(AF_INET, ip.c_str(), &a) == 1 && (ntohl(a.s_addr) >> 24) == 127;
    }
    bool ParseEndpoint(const std::string& text, std::string& ip, uint16_t& port)
    {
        const auto colon = text.find(':');
        if (colon == std::string::npos) return false;
        const auto host = text.substr(0, colon), service = text.substr(colon + 1);
        IN_ADDR a{};
        if (inet_pton(AF_INET, host.c_str(), &a) != 1 || service.empty() || service.size() > 5) return false;
        unsigned n = 0;
        for (char c : service) { if (c < '0' || c > '9') return false; n = n * 10 + unsigned(c - '0'); }
        if (!n || n > 65535) return false;
        ip = host; port = uint16_t(n); return true;
    }
    int Run(const Config& cfg, std::atomic<bool>& stop, std::atomic<int>& ready, Logger logger)
    {
        WSADATA data{};
        if (WSAStartup(MAKEWORD(2, 2), &data)) { ready = -1; return 2; }
        int result = 0;
        try
        {
            Runtime runtime(cfg, logger); runtime.Start(GetTickCount64(), stop); ready = 1;
            while (!stop.load()) { runtime.Tick(GetTickCount64()); runtime.Wait(); }
        }
        catch (const std::exception& error) { if (logger) logger(error.what()); ready = -1; result = 2; }
        WSACleanup(); return result;
    }
}
