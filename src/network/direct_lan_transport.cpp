#define _CRT_RAND_S
#include "direct_lan_transport.h"
#include "direct_lan_discovery.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <random>
#include <utility>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using Socket = SOCKET;
constexpr Socket kInvalid = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
using Socket = int;
constexpr Socket kInvalid = -1;
#endif

namespace BZROpenShim::DirectLan
{
    namespace
    {
        bool Local(uint32_t ip)
        { return (ip >> 24) == 10 || (ip >> 24) == 127 || (ip >> 20) == 0xAC1 || (ip >> 16) == 0xC0A8 || (ip >> 16) == 0xA9FE; }
        void Shut(Socket& socket)
        {
            if (socket == kInvalid) return;
#ifdef _WIN32
            closesocket(socket);
#else
            close(socket);
#endif
            socket = kInvalid;
        }
        int ErrorCode()
        {
#ifdef _WIN32
            return WSAGetLastError();
#else
            return errno;
#endif
        }
        bool Pending(int error)
        {
#ifdef _WIN32
            return error == WSAEWOULDBLOCK || error == WSAEINPROGRESS;
#else
            return error == EWOULDBLOCK || error == EAGAIN || error == EINPROGRESS;
#endif
        }
        bool Nonblocking(Socket socket)
        {
#ifdef _WIN32
            u_long value = 1; return ioctlsocket(socket, FIONBIO, &value) == 0;
#else
            const int flags = fcntl(socket, F_GETFL, 0);
            return flags >= 0 && fcntl(socket, F_SETFL, flags | O_NONBLOCK) == 0;
#endif
        }
        sockaddr_in SockAddress(Address address)
        {
            sockaddr_in result{}; result.sin_family = AF_INET;
            result.sin_addr.s_addr = htonl(address.ipv4); result.sin_port = htons(address.port); return result;
        }
        using SockLength =
#ifdef _WIN32
            int;
#else
            socklen_t;
#endif
        int SendBytes(Socket socket, const uint8_t* data, size_t size)
        {
#ifdef _WIN32
            return send(socket, reinterpret_cast<const char*>(data), static_cast<int>(size), 0);
#else
            return static_cast<int>(send(socket, data, size, MSG_NOSIGNAL));
#endif
        }
    }

    bool ParseIPv4(const std::string& text, uint32_t& ip)
    {
        // Strict dotted decimal: no hostname/DNS/account service lookup.
        ip = 0; size_t begin = 0;
        for (int part = 0; part < 4; ++part)
        {
            const auto end = text.find('.', begin);
            if ((part < 3 && end == std::string::npos) || (part == 3 && end != std::string::npos)) return false;
            const auto length = (end == std::string::npos ? text.size() : end) - begin;
            if (!length || length > 3) return false;
            unsigned byte = 0;
            for (size_t i = begin; i < begin + length; ++i)
            { if (text[i] < '0' || text[i] > '9') return false; byte = byte * 10 + unsigned(text[i] - '0'); }
            if (byte > 255) return false;
            ip = (ip << 8) | byte; begin += length + 1;
        }
        return true;
    }
    std::string FormatIPv4(uint32_t ip)
    {
        return std::to_string(ip >> 24) + "." + std::to_string((ip >> 16) & 255) + "." +
            std::to_string((ip >> 8) & 255) + "." + std::to_string(ip & 255);
    }
    bool RandomId(Id& id)
    {
        id = {};
        try
        {
#ifdef _WIN32
            for (size_t i = 0; i < id.bytes.size(); i += sizeof(unsigned))
            {
                unsigned value;
                if (rand_s(&value)) { id = {}; return false; }
                std::memcpy(id.bytes.data() + i, &value, sizeof(value));
            }
#else
            std::random_device random;
            for (auto& byte : id.bytes) byte = uint8_t(random());
#endif
        }
        catch (...) { id = {}; return false; }
        return !id.Empty();
    }
    Time Now()
    { return uint64_t(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }

    struct Node::Impl
    {
        struct Channel
        {
            Socket socket = kInvalid;
            Connection id = 0;
            uint32_t address = 0;
            Time since = 0;
            Time rateAt = 0;
            Time closingSince = 0;
            double receiveTokens = 32;
            bool connecting = false, closeAfter = false, broken = false, sendShutdown = false;
            Decoder decoder;
            std::deque<std::vector<uint8_t>> output;
            size_t offset = 0, queued = 0;
        };
        Session session;
        Socket listener = kInvalid;
        std::vector<Channel> channels;
        std::unique_ptr<DiscoveryHost> discovery;
        uint32_t localAddress = 0;
        Connection next = 1;
        uint16_t port = 0;
        std::string error;
        bool initialized = false;
        Impl(Id id, std::string name, Compatibility compatibility, uint16_t gameplayPort)
            : session(id, std::move(name), std::move(compatibility), gameplayPort)
        {
#ifdef _WIN32
            WSADATA data{}; initialized = WSAStartup(MAKEWORD(2, 2), &data) == 0;
#else
            initialized = true;
#endif
        }
        ~Impl()
        {
            Stop();
#ifdef _WIN32
            if (initialized) WSACleanup();
#endif
        }
        void Stop()
        { discovery.reset(); Shut(listener); for (auto& c : channels) Shut(c.socket); channels.clear(); port = 0; }
        bool Fail(const std::string& message)
        { error = message; Stop(); return false; }
        void Drop(size_t index, const char* reason)
        {
            const auto id = channels[index].id; Shut(channels[index].socket);
            channels.erase(channels.begin() + index); session.Disconnected(id, reason);
        }
        void Queue()
        {
            for (auto& item : session.TakeOutbound())
            {
                auto c = std::find_if(channels.begin(), channels.end(), [&](const Channel& channel) { return channel.id == item.connection; });
                if (c == channels.end()) continue;
                if (c->broken) continue;
                std::vector<uint8_t> frame;
                if (!Encode(item.packet, frame) || c->queued + frame.size() > 65536)
                { c->broken = true; continue; }
                c->queued += frame.size(); c->output.push_back(std::move(frame));
                c->closeAfter = c->closeAfter || item.closeAfter;
            }
        }
        void Accept(Time now)
        {
            if (listener == kInvalid) return;
            for (int accepted = 0; accepted < 8; ++accepted)
            {
                sockaddr_in address{}; SockLength size = sizeof(address);
                Socket socket = accept(listener, reinterpret_cast<sockaddr*>(&address), &size);
                if (socket == kInvalid) break;
                if (channels.size() >= 32 || size != sizeof(address) || !Local(ntohl(address.sin_addr.s_addr)) || !Nonblocking(socket))
                { Shut(socket); continue; }
                int noDelay = 1;
                setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&noDelay), sizeof(noDelay));
                Channel channel; channel.socket = socket; channel.id = next++;
                channel.address = ntohl(address.sin_addr.s_addr); channel.since = channel.rateAt = now;
                channels.push_back(std::move(channel));
            }
        }
        void Poll()
        {
            if (session.State().phase == Phase::Closed) Shut(listener);
            const Time now = Now(); Accept(now);
            for (size_t index = 0; index < channels.size();)
            {
                auto& c = channels[index]; bool failed = false;
                if (c.connecting)
                {
                    fd_set writable; FD_ZERO(&writable); FD_SET(c.socket, &writable);
                    fd_set exceptions; FD_ZERO(&exceptions); FD_SET(c.socket, &exceptions);
                    timeval timeout{};
                    const int ready = select(static_cast<int>(c.socket + 1), nullptr, &writable, &exceptions, &timeout);
                    if (ready > 0)
                    {
                        int status = 0; SockLength length = sizeof(status);
                        if (getsockopt(c.socket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&status), &length) || status) failed = true;
                        else c.connecting = false;
                    }
                    else if (ready < 0 || now - c.since >= 5000) failed = true;
                }
                if (!c.connecting && !failed)
                {
                    for (int read = 0; read < 4; ++read)
                    {
                        uint8_t buffer[4096];
                        const int count = static_cast<int>(recv(c.socket, reinterpret_cast<char*>(buffer), sizeof(buffer), 0));
                        if (count < 0) { if (!Pending(ErrorCode())) failed = true; break; }
                        if (!count) { failed = true; break; }
                        if (c.closeAfter || session.State().phase == Phase::Closed) continue;
                        std::vector<Packet> packets;
                        if (!c.decoder.Feed(buffer, size_t(count), packets)) { failed = true; break; }
                        c.receiveTokens = (std::min)(32.0, c.receiveTokens + double(now - c.rateAt) * 0.032); c.rateAt = now;
                        for (const auto& packet : packets)
                        {
                            if (c.receiveTokens < 1) { failed = true; break; }
                            --c.receiveTokens;
                            session.Receive(c.id, c.address, packet, now);
                            Queue(); // bound the session output between received control messages
                            if (c.closeAfter || c.broken) break;
                        }
                        if (failed || c.closeAfter || c.broken) break;
                    }
                }
                if (failed) { error = c.connecting ? "LAN connection failed" : "LAN connection closed"; Drop(index, error.c_str()); }
                else ++index;
            }
            session.Tick(now); Queue();
            for (size_t index = 0; index < channels.size();)
            {
                auto& c = channels[index]; bool failed = c.broken;
                if (!c.connecting && !failed)
                    for (int sent = 0; sent < 16 && !c.output.empty(); ++sent)
                    {
                        const auto& frame = c.output.front();
                        const int count = SendBytes(c.socket, frame.data() + c.offset, frame.size() - c.offset);
                        if (count < 0) { if (!Pending(ErrorCode())) failed = true; break; }
                        if (!count) { failed = true; break; }
                        c.offset += size_t(count); c.queued -= size_t(count);
                        if (c.offset == frame.size()) { c.output.pop_front(); c.offset = 0; }
                    }
                const bool expiredGreeting = session.IsHost() && now - c.since >= 5000 &&
                    !session.HasConnection(c.id);
                const bool closing = c.closeAfter || session.State().phase == Phase::Closed;
                if (closing && !c.closingSince) c.closingSince = now;
                // A close with unread incoming data can reset TCP and discard
                // the final session message. Half-close, then drain until EOF
                // (or the bounded deadline) before releasing the socket.
                if (closing && c.output.empty() && !c.sendShutdown && !c.connecting)
                {
#ifdef _WIN32
                    shutdown(c.socket, SD_SEND);
#else
                    shutdown(c.socket, SHUT_WR);
#endif
                    c.sendShutdown = true;
                }
                if (failed || expiredGreeting || (closing && now - c.closingSince >= 1000))
                    Drop(index, "LAN channel ended");
                else ++index;
            }
            if (session.State().phase == Phase::Closed && channels.empty()) Shut(listener);
            if (session.State().phase == Phase::Closed) discovery.reset();
            else if (discovery) discovery->Poll(session.State(), port);
        }
    };
    Node::Node(Id id, std::string name, Compatibility compatibility, uint16_t gameplayPort)
        : impl_(new Impl(id, std::move(name), std::move(compatibility), gameplayPort)) {}
    Node::~Node() = default;
    bool Node::Host(Config config, Id session, uint32_t address, uint16_t port)
    {
        auto& s = *impl_;
        if (!s.initialized || s.listener != kInvalid || !s.channels.empty() || s.session.State().phase != Phase::Idle)
            return false;
        s.listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s.listener == kInvalid || !Nonblocking(s.listener)) return s.Fail("Cannot create LAN listen socket");
#ifdef _WIN32
        int exclusive = 1;
        if (setsockopt(s.listener, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<const char*>(&exclusive), sizeof(exclusive)))
            return s.Fail("Cannot reserve LAN listen socket");
#endif
        const auto bindAddress = SockAddress({address, port});
        if (bind(s.listener, reinterpret_cast<const sockaddr*>(&bindAddress), sizeof(bindAddress)) || listen(s.listener, 16))
            return s.Fail("Cannot bind LAN listen socket");
        sockaddr_in bound{}; SockLength size = sizeof(bound);
        if (getsockname(s.listener, reinterpret_cast<sockaddr*>(&bound), &size)) return s.Fail("Cannot read LAN listen port");
        s.port = ntohs(bound.sin_port);
        s.localAddress = address;
        if (!s.session.Host(std::move(config), session, address, Now())) return s.Fail("Invalid LAN host configuration");
        return true;
    }
    bool Node::Join(Address target, Id expected)
    {
        auto& s = *impl_;
        if (!s.initialized || !Local(target.ipv4) || !target.port || s.listener != kInvalid ||
            !s.channels.empty() || s.session.State().phase != Phase::Idle) return false;
        Socket socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket == kInvalid || !Nonblocking(socket)) { Shut(socket); return s.Fail("Cannot create LAN peer socket"); }
        const auto address = SockAddress(target);
        const int connected = connect(socket, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
        if (connected && !Pending(ErrorCode())) { Shut(socket); return s.Fail("LAN host is unreachable"); }
        int noDelay = 1;
        setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&noDelay), sizeof(noDelay));
        Impl::Channel channel; channel.socket = socket; channel.id = s.next++;
        channel.address = target.ipv4; channel.since = channel.rateAt = Now(); channel.connecting = connected != 0;
        if (!s.session.Join(channel.id, expected, Now())) { Shut(socket); return false; }
        s.channels.push_back(std::move(channel)); return true;
    }
    void Node::Poll() { impl_->Poll(); }
    bool Node::EnableDiscovery(uint16_t port)
    {
        auto& s = *impl_;
        if (!s.session.IsHost() || s.session.State().phase != Phase::Lobby || s.discovery) return false;
        auto discovery = std::make_unique<DiscoveryHost>();
        if (!discovery->Open(s.localAddress, port)) { s.error = "Cannot bind LAN discovery; direct IP remains available"; return false; }
        s.discovery = std::move(discovery); return true;
    }
    uint16_t Node::DiscoveryPort() const { return impl_->discovery ? impl_->discovery->Port() : 0; }
    void Node::Close() { impl_->session.Leave(); impl_->Stop(); }
    Session& Node::Control() { return impl_->session; }
    const Session& Node::Control() const { return impl_->session; }
    uint16_t Node::ControlPort() const { return impl_->port; }
    size_t Node::Connections() const { return impl_->channels.size(); }
    const std::string& Node::Error() const { return impl_->error; }
}
