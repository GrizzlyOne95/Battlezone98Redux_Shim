#include "direct_lan_mesh.h"
#include <algorithm>
#include <deque>
#include <utility>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using MeshSocket = SOCKET;
constexpr MeshSocket kBadMeshSocket = INVALID_SOCKET;
using MeshLength = int;
#else
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
using MeshSocket = int;
constexpr MeshSocket kBadMeshSocket = -1;
using MeshLength = socklen_t;
#endif

namespace BZROpenShim::DirectLan
{
    namespace
    {
        constexpr size_t kPayload = 1152, kQueue = 256 * 1024;
        bool Local(uint32_t ip)
        { return (ip >> 24) == 10 || (ip >> 24) == 127 || (ip >> 20) == 0xAC1 || (ip >> 16) == 0xC0A8 || (ip >> 16) == 0xA9FE; }
        bool Before(const Id& a, const Id& b) { return a.bytes < b.bytes; }
        void Shut(MeshSocket& s)
        {
            if (s == kBadMeshSocket) return;
#ifdef _WIN32
            closesocket(s);
#else
            close(s);
#endif
            s = kBadMeshSocket;
        }
        bool Pending()
        {
#ifdef _WIN32
            const auto e = WSAGetLastError(); return e == WSAEWOULDBLOCK || e == WSAEINPROGRESS;
#else
            return errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS;
#endif
        }
        bool Nonblocking(MeshSocket s)
        {
#ifdef _WIN32
            u_long yes = 1; return ioctlsocket(s, FIONBIO, &yes) == 0;
#else
            const int flags = fcntl(s, F_GETFL, 0); return flags >= 0 && fcntl(s, F_SETFL, flags | O_NONBLOCK) == 0;
#endif
        }
        bool Reserve(MeshSocket s)
        {
#ifdef _WIN32
            int yes = 1; return setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<const char*>(&yes), sizeof(yes)) == 0;
#else
            (void)s; return true;
#endif
        }
        sockaddr_in SocketAddress(uint32_t ip, uint16_t port)
        { sockaddr_in a{}; a.sin_family = AF_INET; a.sin_addr.s_addr = htonl(ip); a.sin_port = htons(port); return a; }
        int Write(MeshSocket s, const uint8_t* data, size_t count)
        {
#ifdef _WIN32
            return send(s, reinterpret_cast<const char*>(data), int(count), 0);
#else
            return int(send(s, data, count, MSG_NOSIGNAL));
#endif
        }
    }
    struct Mesh::Impl
    {
        struct Link
        {
            MeshSocket socket = kBadMeshSocket;
            uint32_t source = 0;
            Id peer;
            bool outgoing = false, connecting = false, greeted = false;
            Decoder decoder{kPeerFrameMagic};
            std::deque<std::vector<uint8_t>> output;
            size_t offset = 0, queued = 0;
            Time began = 0, heard = 0, ping = 0;
            uint64_t serial = 0;
        };
        struct Peer { Id id; Endpoint endpoint; uint64_t udpSerial = 0; Time retry = 0; bool lost = false; };
        Id local, session;
        uint32_t address = 0;
        uint16_t port = 0;
        MeshSocket tcp = kBadMeshSocket, udp = kBadMeshSocket;
        bool initialized = false, active = false;
        std::vector<Peer> peers;
        std::vector<Link> links;
        std::vector<PeerPacket> received;
        std::string error;
        uint64_t sequence = 0;
        size_t bytesReceived = 0;
        explicit Impl(Id id) : local(id)
        {
#ifdef _WIN32
            WSADATA data{}; initialized = WSAStartup(MAKEWORD(2, 2), &data) == 0;
#else
            initialized = true;
#endif
        }
        ~Impl()
        {
            Close();
#ifdef _WIN32
            if (initialized) WSACleanup();
#endif
        }
        void ClearLinks()
        { for (auto& link : links) Shut(link.socket); links.clear(); received.clear(); bytesReceived = 0; }
        void Close()
        { ClearLinks(); Shut(tcp); Shut(udp); port = 0; active = false; peers.clear(); }
        bool Fail(const char* why) { error = why; Close(); return false; }
        bool Open(uint32_t ip, uint16_t requested)
        {
            if (!initialized || local.Empty() || port || !Local(ip) || !session.Empty()) return false;
            for (int attempt = 0; attempt < (requested ? 1 : 8); ++attempt)
            {
                udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                const auto a = SocketAddress(ip, requested);
                if (udp == kBadMeshSocket || tcp == kBadMeshSocket || !Nonblocking(udp) || !Nonblocking(tcp) || !Reserve(udp) || !Reserve(tcp))
                    return Fail("Cannot create direct gameplay sockets");
                sockaddr_in bound{}; MeshLength length = sizeof(bound);
                // Let TCP pick the ephemeral port first: its allocator avoids
                // TIME_WAIT reservations from previous sessions. UDP-first
                // selection can repeatedly choose ports TCP cannot reuse.
                if (!bind(tcp, reinterpret_cast<const sockaddr*>(&a), sizeof(a)) &&
                    !getsockname(tcp, reinterpret_cast<sockaddr*>(&bound), &length) &&
                    !bind(udp, reinterpret_cast<const sockaddr*>(&bound), sizeof(bound)) && !listen(tcp, 16))
                { address = ip; port = ntohs(bound.sin_port); error.clear(); return true; }
                Shut(udp); Shut(tcp);
            }
            return Fail("Cannot reserve direct gameplay TCP/UDP port");
        }
        bool Apply(const View& view)
        {
            if (view.phase == Phase::Closed) { Close(); return true; }
            if (!port || view.session.Empty() || (!session.Empty() && session != view.session) ||
                (view.phase != Phase::Lobby && view.phase != Phase::Preparing && view.phase != Phase::Running) ||
                view.members.empty() || view.members.size() > kMaxMembers) return Fail("Invalid direct gameplay roster");
            std::vector<Peer> next; bool foundLocal = false;
            for (const auto& m : view.members)
            {
                if (m.id.Empty() || !Local(m.endpoint.ipv4) || !m.endpoint.gamePort ||
                    std::any_of(next.begin(), next.end(), [&](const Peer& p) { return p.id == m.id ||
                        (p.endpoint.ipv4 == m.endpoint.ipv4 && p.endpoint.gamePort == m.endpoint.gamePort); }))
                    return Fail("Duplicate or invalid gameplay endpoint");
                if (m.id == local)
                {
                    if (foundLocal || m.endpoint.ipv4 != address || m.endpoint.gamePort != port) return Fail("Local gameplay endpoint differs");
                    foundLocal = true; continue;
                }
                if (m.endpoint.ipv4 == address && m.endpoint.gamePort == port) return Fail("Peer uses local gameplay endpoint");
                Peer peer{m.id, m.endpoint};
                const auto old = std::find_if(peers.begin(), peers.end(), [&](const Peer& p) { return p.id == m.id; });
                if (old != peers.end())
                {
                    if (old->endpoint.ipv4 != peer.endpoint.ipv4 || old->endpoint.gamePort != peer.endpoint.gamePort)
                        return Fail("Gameplay endpoint changed during session");
                    peer.udpSerial = old->udpSerial; peer.retry = old->retry; peer.lost = old->lost;
                }
                next.push_back(peer);
            }
            if (!foundLocal) return Fail("Local player missing from gameplay roster");
            for (auto& link : links)
                if (!link.peer.Empty() && std::none_of(next.begin(), next.end(), [&](const Peer& p) { return p.id == link.peer; })) Shut(link.socket);
            links.erase(std::remove_if(links.begin(), links.end(), [](const Link& l) { return l.socket == kBadMeshSocket; }), links.end());
            received.erase(std::remove_if(received.begin(), received.end(), [&](const PeerPacket& p)
                { return std::none_of(next.begin(), next.end(), [&](const Peer& peer) { return peer.id == p.sender; }); }), received.end());
            bytesReceived = 0; for (const auto& p : received) bytesReceived += p.bytes.size();
            peers = std::move(next); session = view.session; active = true; return true;
        }
        bool Frame(Type type, const uint8_t* data, size_t size, std::vector<uint8_t>& bytes)
        {
            if (++sequence == 0) { error = "Gameplay sequence exhausted"; return false; }
            Packet p{type, session, local, sequence, {}};
            if (size) p.payload.assign(data, data + size);
            return Encode(p, bytes, kPeerFrameMagic);
        }
        bool Queue(Link& link, Type type, const uint8_t* data = nullptr, size_t size = 0)
        {
            std::vector<uint8_t> bytes;
            if (!Frame(type, data, size, bytes) || link.queued + bytes.size() > kQueue) return false;
            link.queued += bytes.size(); link.output.push_back(std::move(bytes)); return true;
        }
        bool Push(Id sender, const std::vector<uint8_t>& bytes, bool reliable)
        {
            if (received.size() >= 1024 || bytesReceived + bytes.size() > 1024 * 1024) return false;
            received.push_back({sender, bytes, reliable}); bytesReceived += bytes.size(); return true;
        }
        void Connect(Time now)
        {
            for (auto& peer : peers)
            {
                if (peer.lost || !Before(local, peer.id) || now < peer.retry || std::any_of(links.begin(), links.end(), [&](const Link& l) { return l.peer == peer.id; })) continue;
                peer.retry = now + 1000;
                MeshSocket socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                const auto a = SocketAddress(peer.endpoint.ipv4, peer.endpoint.gamePort);
                // Bind source to the selected LAN interface, even on a
                // multi-adapter host. The source TCP port need not match UDP.
                const auto source = SocketAddress(address, 0);
                if (socket == kBadMeshSocket || !Nonblocking(socket) || bind(socket, reinterpret_cast<const sockaddr*>(&source), sizeof(source)))
                { Shut(socket); continue; }
                const int connected = connect(socket, reinterpret_cast<const sockaddr*>(&a), sizeof(a));
                if (connected && !Pending()) { Shut(socket); continue; }
                Link link; link.socket = socket; link.source = peer.endpoint.ipv4; link.peer = peer.id;
                link.outgoing = true; link.connecting = connected != 0; link.began = link.heard = link.ping = now;
                int yes = 1; setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&yes), sizeof(yes));
                Queue(link, Type::Hello); links.push_back(std::move(link));
            }
        }
        void Accept(Time now)
        {
            for (int i = 0; i < 8; ++i)
            {
                sockaddr_in a{}; MeshLength length = sizeof(a);
                auto socket = accept(tcp, reinterpret_cast<sockaddr*>(&a), &length);
                if (socket == kBadMeshSocket) break;
                const auto ip = ntohl(a.sin_addr.s_addr);
                if (!active || length != sizeof(a) || a.sin_family != AF_INET || links.size() >= 30 || !Nonblocking(socket) ||
                    std::none_of(peers.begin(), peers.end(), [&](const Peer& p) { return p.endpoint.ipv4 == ip && Before(p.id, local); }))
                { Shut(socket); continue; }
                Link link; link.socket = socket; link.source = ip; link.began = link.heard = link.ping = now;
                int yes = 1; setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&yes), sizeof(yes));
                Queue(link, Type::Hello); links.push_back(std::move(link));
            }
        }
        bool Receive(Link& link, const Packet& packet, Time now)
        {
            if (packet.session != session || packet.serial <= link.serial || packet.payload.size() > kPayload) return false;
            if (!link.greeted)
            {
                const auto peer = std::find_if(peers.begin(), peers.end(), [&](const Peer& p) { return p.id == packet.sender; });
                if (packet.type != Type::Hello || !packet.payload.empty() || peer == peers.end() || peer->lost || peer->endpoint.ipv4 != link.source ||
                    (link.outgoing ? link.peer != peer->id : !Before(peer->id, local)) ||
                    std::any_of(links.begin(), links.end(), [&](const Link& l) { return &l != &link && l.greeted && l.peer == peer->id; })) return false;
                link.peer = peer->id; link.greeted = true;
            }
            else
            {
                if (packet.sender != link.peer) return false;
                if (packet.type == Type::Snapshot && !packet.payload.empty())
                { if (!Push(link.peer, packet.payload, true)) return false; }
                else if (packet.type != Type::Ping || !packet.payload.empty()) return false;
            }
            link.serial = packet.serial; link.heard = now; return true;
        }
        void Poll()
        {
            if (!port) return;
            const auto now = Now();
            if (active) Connect(now);
            Accept(now);
            for (size_t index = 0; index < links.size();)
            {
                auto& l = links[index]; bool failed = l.socket == kBadMeshSocket;
                if (!failed && l.connecting)
                {
                    fd_set write, except; FD_ZERO(&write); FD_ZERO(&except); FD_SET(l.socket, &write); FD_SET(l.socket, &except);
                    timeval timeout{}; const auto ready = select(int(l.socket + 1), nullptr, &write, &except, &timeout);
                    if (ready > 0)
                    {
                        int status = 0; MeshLength length = sizeof(status);
                        failed = getsockopt(l.socket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&status), &length) != 0 || status != 0;
                        l.connecting = false;
                    }
                    else if (ready < 0) failed = true;
                }
                if (!failed && !l.connecting)
                {
                    for (int i = 0; i < 4 && !failed; ++i)
                    {
                        uint8_t bytes[4096]; const int count = int(recv(l.socket, reinterpret_cast<char*>(bytes), sizeof(bytes), 0));
                        if (count < 0) { failed = !Pending(); break; }
                        if (!count) { failed = true; break; }
                        std::vector<Packet> packets;
                        if (!l.decoder.Feed(bytes, size_t(count), packets)) { failed = true; break; }
                        for (const auto& p : packets) if (!Receive(l, p, now)) { failed = true; break; }
                    }
                    if (l.greeted && now - l.ping >= 1000) { failed = failed || !Queue(l, Type::Ping); l.ping = now; }
                    for (int i = 0; i < 32 && !l.output.empty() && !failed; ++i)
                    {
                        const auto& bytes = l.output.front();
                        const int count = Write(l.socket, bytes.data() + l.offset, bytes.size() - l.offset);
                        if (count < 0) { failed = !Pending(); break; }
                        if (!count) { failed = true; break; }
                        l.offset += size_t(count); l.queued -= size_t(count);
                        if (l.offset == bytes.size()) { l.output.pop_front(); l.offset = 0; }
                    }
                }
                failed = failed || (!l.greeted && now - l.began >= 5000) || now - l.heard >= 10000;
                if (failed)
                {
                    // Never reconnect an established reliable stream and
                    // pretend queued/lost payloads were delivered. Control
                    // membership must remove this peer or end the session.
                    if (l.greeted) for (auto& p : peers) if (p.id == l.peer) p.lost = true;
                    Shut(l.socket); links.erase(links.begin() + index); error = "Direct gameplay peer disconnected";
                }
                else ++index;
            }
            for (int i = 0; i < 128; ++i)
            {
                uint8_t bytes[1280]; sockaddr_in a{}; MeshLength length = sizeof(a);
                const int count = int(recvfrom(udp, reinterpret_cast<char*>(bytes), sizeof(bytes), 0, reinterpret_cast<sockaddr*>(&a), &length));
                if (count < 0) break;
                if (!active || count < 56 || count > int(56 + kPayload) || length != sizeof(a) || a.sin_family != AF_INET) continue;
                Decoder decoder{kPeerFrameMagic}; std::vector<Packet> packets;
                if (!decoder.Feed(bytes, size_t(count), packets) || packets.size() != 1) continue;
                const auto& p = packets[0];
                // Re-encode size must match: a datagram is exactly one frame,
                // never a valid frame plus a partial next one.
                if (count != int(56 + p.payload.size()) || p.session != session || p.type != Type::Ready || p.payload.empty()) continue;
                const auto peer = std::find_if(peers.begin(), peers.end(), [&](const Peer& old) { return old.id == p.sender &&
                    old.endpoint.ipv4 == ntohl(a.sin_addr.s_addr) && old.endpoint.gamePort == ntohs(a.sin_port); });
                if (peer == peers.end() || p.serial <= peer->udpSerial || !std::any_of(links.begin(), links.end(),
                    [&](const Link& l) { return l.greeted && l.peer == p.sender; })) continue;
                peer->udpSerial = p.serial; Push(p.sender, p.payload, false);
            }
        }
        bool Ready() const
        { return active && port && std::all_of(peers.begin(), peers.end(), [&](const Peer& p) { return std::any_of(links.begin(), links.end(),
            [&](const Link& l) { return l.greeted && l.peer == p.id && l.socket != kBadMeshSocket; }); }); }
        bool Send(Id target, const uint8_t* data, size_t size, bool reliable)
        {
            if (!active || !data || !size || size > kPayload) return false;
            const auto p = std::find_if(peers.begin(), peers.end(), [&](const Peer& peer) { return peer.id == target; });
            const auto l = std::find_if(links.begin(), links.end(), [&](const Link& link) { return link.greeted && link.socket != kBadMeshSocket && link.peer == target; });
            if (p == peers.end() || l == links.end()) return false;
            if (reliable) return Queue(*l, Type::Snapshot, data, size);
            std::vector<uint8_t> bytes; if (!Frame(Type::Ready, data, size, bytes)) return false;
            const auto a = SocketAddress(p->endpoint.ipv4, p->endpoint.gamePort);
            return sendto(udp, reinterpret_cast<const char*>(bytes.data()), int(bytes.size()), 0, reinterpret_cast<const sockaddr*>(&a), sizeof(a)) == int(bytes.size());
        }
    };
    Mesh::Mesh(Id id) : impl_(new Impl(id)) {}
    Mesh::~Mesh() = default;
    bool Mesh::Open(uint32_t ip, uint16_t port) { return impl_->Open(ip, port); }
    bool Mesh::Apply(const View& view) { return impl_->Apply(view); }
    void Mesh::Poll() { impl_->Poll(); }
    bool Mesh::Ready() const { return impl_->Ready(); }
    bool Mesh::Send(Id target, const uint8_t* data, size_t size, bool reliable) { return impl_->Send(target, data, size, reliable); }
    std::vector<PeerPacket> Mesh::TakeReceived()
    { auto out = std::move(impl_->received); impl_->received.clear(); impl_->bytesReceived = 0; return out; }
    void Mesh::Close() { impl_->Close(); }
    uint16_t Mesh::Port() const { return impl_->port; }
    const std::string& Mesh::Error() const { return impl_->error; }
}
