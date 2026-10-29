#include "direct_lan_discovery.h"
#include <algorithm>
#include <cstring>
#include <set>
#include <utility>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
using DiscoverySocket = SOCKET;
constexpr DiscoverySocket kNoSocket = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/socket.h>
#include <unistd.h>
using DiscoverySocket = int;
constexpr DiscoverySocket kNoSocket = -1;
#endif

namespace BZROpenShim::DirectLan
{
    namespace
    {
        bool Local(uint32_t ip)
        { return (ip >> 24) == 10 || (ip >> 24) == 127 || (ip >> 20) == 0xAC1 || (ip >> 16) == 0xC0A8 || (ip >> 16) == 0xA9FE; }
        bool Label(const std::string& text, size_t maximum)
        { return !text.empty() && text.size() <= maximum && text.find_first_not_of(' ') != std::string::npos &&
            std::all_of(text.begin(), text.end(), [](unsigned char c) { return c >= 32 && c <= 126; }); }
        void CloseSocket(DiscoverySocket& socket)
        {
            if (socket == kNoSocket) return;
#ifdef _WIN32
            closesocket(socket);
#else
            close(socket);
#endif
            socket = kNoSocket;
        }
        struct SocketOwner
        {
            DiscoverySocket socket = kNoSocket;
            bool initialized = false;
            uint16_t port = 0;
            SocketOwner()
            {
#ifdef _WIN32
                WSADATA data{}; initialized = WSAStartup(MAKEWORD(2, 2), &data) == 0;
#else
                initialized = true;
#endif
            }
            ~SocketOwner()
            {
                CloseSocket(socket);
                port = 0;
#ifdef _WIN32
                if (initialized) WSACleanup();
#endif
            }
            bool Open(uint32_t ip, uint16_t requestedPort, bool broadcast)
            {
                CloseSocket(socket);
                port = 0;
                if (!initialized) return false;
                socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if (socket == kNoSocket) return false;
                auto fail = [&]() { CloseSocket(socket); return false; };
#ifdef _WIN32
                u_long nonblocking = 1; int exclusive = 1;
                if (ioctlsocket(socket, FIONBIO, &nonblocking) ||
                    setsockopt(socket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<const char*>(&exclusive), sizeof(exclusive)))
                    return fail();
#else
                const int flags = fcntl(socket, F_GETFL, 0);
                if (flags < 0 || fcntl(socket, F_SETFL, flags | O_NONBLOCK)) return fail();
#endif
                int yes = 1;
                if (broadcast && setsockopt(socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char*>(&yes), sizeof(yes))) return fail();
                sockaddr_in address{}; address.sin_family = AF_INET; address.sin_addr.s_addr = htonl(ip); address.sin_port = htons(requestedPort);
                if (bind(socket, reinterpret_cast<const sockaddr*>(&address), sizeof(address))) return fail();
#ifdef _WIN32
                int size = sizeof(address);
#else
                socklen_t size = sizeof(address);
#endif
                if (getsockname(socket, reinterpret_cast<sockaddr*>(&address), &size)) return fail();
                port = ntohs(address.sin_port); return true;
            }
            int Receive(uint8_t* buffer, size_t size, sockaddr_in& sender)
            {
#ifdef _WIN32
                int addressSize = sizeof(sender);
#else
                socklen_t addressSize = sizeof(sender);
#endif
                const int count = static_cast<int>(recvfrom(socket, reinterpret_cast<char*>(buffer), static_cast<int>(size), 0,
                    reinterpret_cast<sockaddr*>(&sender), &addressSize));
                return count >= 0 && (addressSize != sizeof(sender) || sender.sin_family != AF_INET) ? -1 : count;
            }
            void Send(const std::vector<uint8_t>& data, const sockaddr_in& address)
            { sendto(socket, reinterpret_cast<const char*>(data.data()), static_cast<int>(data.size()), 0,
                reinterpret_cast<const sockaddr*>(&address), sizeof(address)); }
        };
        struct Interface { uint32_t ip, mask; };
        std::vector<Interface> Interfaces(DiscoverySocket socket)
        {
            std::vector<Interface> result;
#ifdef _WIN32
            INTERFACE_INFO interfaces[64]{}; DWORD size = 0;
            if (!WSAIoctl(socket, SIO_GET_INTERFACE_LIST, nullptr, 0, interfaces, sizeof(interfaces), &size, nullptr, nullptr))
                for (size_t i = 0; i < size / sizeof(INTERFACE_INFO); ++i)
                {
                    const auto& item = interfaces[i];
                    const auto ip = ntohl(item.iiAddress.AddressIn.sin_addr.s_addr);
                    const auto mask = ntohl(item.iiNetmask.AddressIn.sin_addr.s_addr);
                    if ((item.iiFlags & IFF_UP) && (item.iiFlags & IFF_BROADCAST) && Local(ip) && mask)
                        result.push_back({ip, mask});
                }
#else
            (void)socket;
            ifaddrs* interfaces = nullptr;
            if (getifaddrs(&interfaces) == 0)
            {
                for (auto* item = interfaces; item; item = item->ifa_next)
                {
                    if (!item->ifa_addr || !item->ifa_netmask || item->ifa_addr->sa_family != AF_INET ||
                        !(item->ifa_flags & IFF_UP) || !(item->ifa_flags & IFF_BROADCAST)) continue;
                    const auto ip = ntohl(reinterpret_cast<sockaddr_in*>(item->ifa_addr)->sin_addr.s_addr);
                    const auto mask = ntohl(reinterpret_cast<sockaddr_in*>(item->ifa_netmask)->sin_addr.s_addr);
                    if (Local(ip) && mask) result.push_back({ip, mask});
                }
                freeifaddrs(interfaces);
            }
#endif
            return result;
        }
        std::vector<uint32_t> Targets(DiscoverySocket socket)
        {
            std::set<uint32_t> targets{0xFFFFFFFF, 0x7F000001};
            for (const auto& item : Interfaces(socket)) targets.insert(item.ip | ~item.mask);
            return {targets.begin(), targets.end()};
        }
    }
    std::vector<uint8_t> DiscoveryQuery(Id nonce)
    {
        std::vector<uint8_t> query(kDiscoveryQuerySize);
        std::memcpy(query.data(), "BZRLAN2?", 8); std::memcpy(query.data() + 8, nonce.bytes.data(), 16); return query;
    }
    bool DiscoveryReply(const std::vector<uint8_t>& query, const View& view, uint16_t controlPort, std::vector<uint8_t>& reply)
    {
        reply.clear();
        if (query.size() != kDiscoveryQuerySize || std::memcmp(query.data(), "BZRLAN2?", 8) ||
            std::any_of(query.begin() + 24, query.end(), [](uint8_t b) { return b != 0; }) ||
            view.phase != Phase::Lobby || view.session.Empty() || !controlPort ||
            !Label(view.config.name, 63) || !Label(view.config.compatibility.gameBuild, 32) ||
            std::all_of(view.config.compatibility.content.begin(), view.config.compatibility.content.end(), [](uint8_t b) { return b == 0; }) ||
            view.members.empty() || view.members.size() > view.config.capacity || view.config.capacity < 2 || view.config.capacity > kMaxMembers)
            return false;
        const std::string magic = "BZRLAN2!"; reply.assign(magic.begin(), magic.end());
        reply.insert(reply.end(), query.begin() + 8, query.begin() + 24);
        reply.insert(reply.end(), view.session.bytes.begin(), view.session.bytes.end());
        reply.push_back(uint8_t(controlPort >> 8)); reply.push_back(uint8_t(controlPort));
        reply.push_back(uint8_t(view.members.size())); reply.push_back(view.config.capacity);
        reply.insert(reply.end(), view.config.compatibility.content.begin(), view.config.compatibility.content.end());
        reply.push_back(uint8_t(view.config.compatibility.gameBuild.size()));
        reply.insert(reply.end(), view.config.compatibility.gameBuild.begin(), view.config.compatibility.gameBuild.end());
        reply.push_back(uint8_t(view.config.name.size())); reply.insert(reply.end(), view.config.name.begin(), view.config.name.end());
        return true;
    }
    bool ReadAdvertisement(const uint8_t* bytes, size_t size, Id nonce, uint32_t source, Advertisement& out)
    {
        out = {};
        if (size < 80 || size > 173 || !Local(source) || std::memcmp(bytes, "BZRLAN2!", 8) ||
            std::memcmp(bytes + 8, nonce.bytes.data(), 16)) return false;
        Advertisement candidate; std::memcpy(candidate.session.bytes.data(), bytes + 24, 16);
        candidate.control = {source, uint16_t((uint16_t(bytes[40]) << 8) | bytes[41])};
        candidate.members = bytes[42]; candidate.capacity = bytes[43];
        std::memcpy(candidate.compatibility.content.data(), bytes + 44, 32);
        size_t cursor = 76;
        auto text = [&](size_t maximum)
        {
            if (cursor >= size) return std::string();
            const size_t length = bytes[cursor++];
            if (length > maximum || length > size - cursor) return std::string();
            std::string value(reinterpret_cast<const char*>(bytes + cursor), length); cursor += length; return value;
        };
        candidate.compatibility.gameBuild = text(32); candidate.name = text(63);
        if (cursor != size || candidate.session.Empty() || !candidate.control.port ||
            candidate.capacity < 2 || candidate.capacity > kMaxMembers || !candidate.members || candidate.members > candidate.capacity ||
            !Label(candidate.compatibility.gameBuild, 32) || !Label(candidate.name, 63) ||
            std::all_of(candidate.compatibility.content.begin(), candidate.compatibility.content.end(), [](uint8_t b) { return b == 0; })) return false;
        out = std::move(candidate); return true;
    }
    struct DiscoveryHost::Impl
    {
        SocketOwner io;
        uint32_t address = 0, mask = 0;
        struct Source { uint32_t ip; double tokens; Time at; };
        std::vector<Source> sources;
        double tokens = 64;
        Time at = Now();
        bool Permit(uint32_t ip)
        {
            const auto now = Now(); tokens = (std::min)(64.0, tokens + double(now - at) * 0.032); at = now;
            auto source = std::find_if(sources.begin(), sources.end(), [&](const Source& s) { return s.ip == ip; });
            if (source == sources.end())
            {
                if (sources.size() == 128) sources.erase(sources.begin());
                sources.push_back({ip, 4, now}); source = sources.end() - 1;
            }
            source->tokens = (std::min)(4.0, source->tokens + double(now - source->at) * 0.002); source->at = now;
            if (tokens < 1 || source->tokens < 1) return false;
            --tokens; --source->tokens; return true;
        }
    };
    DiscoveryHost::DiscoveryHost() : impl_(new Impl) {}
    DiscoveryHost::~DiscoveryHost() = default;
    bool DiscoveryHost::Open(uint32_t address, uint16_t port)
    {
        auto& s = *impl_; s.address = address; s.mask = 0;
        CloseSocket(s.io.socket); s.io.port = 0;
        // A unicast bind misses subnet broadcasts on POSIX. Listen on ANY,
        // but advertise only to the selected control/game interface's subnet.
        if (!Local(address) || !s.io.Open(0, port, false)) return false;
        if ((address >> 24) == 127) s.mask = 0xFF000000;
        else for (const auto& item : Interfaces(s.io.socket))
            if (item.ip == address) { s.mask = item.mask; break; }
        if (!s.mask) { CloseSocket(s.io.socket); s.io.port = 0; return false; }
        return true;
    }
    uint16_t DiscoveryHost::Port() const { return impl_->io.port; }
    void DiscoveryHost::Poll(const View& view, uint16_t port)
    {
        if (impl_->io.socket == kNoSocket) return;
        for (int i = 0; i < 32; ++i)
        {
            uint8_t bytes[256]; sockaddr_in address{};
            const int count = impl_->io.Receive(bytes, sizeof(bytes), address);
            if (count < 0) break;
            const uint32_t source = ntohl(address.sin_addr.s_addr);
            if (!Local(source) || (source & impl_->mask) != (impl_->address & impl_->mask)) continue;
            const std::vector<uint8_t> query(bytes, bytes + count); std::vector<uint8_t> reply;
            if (DiscoveryReply(query, view, port, reply) && impl_->Permit(source)) impl_->io.Send(reply, address);
        }
    }
    struct Browser::Impl
    {
        SocketOwner io;
        Id nonce;
        uint16_t port = 0;
        Time since = 0, sent = 0;
        bool searching = false;
        std::vector<uint32_t> targets;
        std::vector<Advertisement> results;
        std::string error;
        void Send()
        {
            const auto query = DiscoveryQuery(nonce);
            for (auto ip : targets)
            {
                sockaddr_in address{}; address.sin_family = AF_INET; address.sin_addr.s_addr = htonl(ip); address.sin_port = htons(port);
                io.Send(query, address);
            }
            sent = Now();
        }
    };
    Browser::Browser() : impl_(new Impl) {}
    Browser::~Browser() = default;
    bool Browser::Start(uint16_t port, std::vector<uint32_t> targets)
    {
        auto& s = *impl_; s.results.clear(); s.searching = false; s.error.clear(); s.port = port;
        CloseSocket(s.io.socket); s.io.port = 0;
        if (!port || !RandomId(s.nonce) || !s.io.Open(0, 0, true)) { s.error = "Cannot open LAN discovery socket"; return false; }
        s.targets = targets.empty() ? Targets(s.io.socket) : std::move(targets);
        if (s.targets.size() > 128 || std::any_of(s.targets.begin(), s.targets.end(), [](uint32_t ip) { return ip != 0xFFFFFFFF && !Local(ip); }))
        { s.error = "Invalid LAN discovery targets"; CloseSocket(s.io.socket); return false; }
        s.since = Now(); s.searching = true; s.Send(); return true;
    }
    void Browser::Poll()
    {
        auto& s = *impl_; if (!s.searching) return;
        for (int i = 0; i < 64; ++i)
        {
            uint8_t bytes[256]; sockaddr_in source{};
            const int count = s.io.Receive(bytes, sizeof(bytes), source);
            if (count < 0) break;
            Advertisement result;
            if (ntohs(source.sin_port) != s.port || !ReadAdvertisement(bytes, size_t(count), s.nonce, ntohl(source.sin_addr.s_addr), result)) continue;
            auto found = std::find_if(s.results.begin(), s.results.end(), [&](const Advertisement& a)
                { return a.session == result.session && a.control.ipv4 == result.control.ipv4 && a.control.port == result.control.port; });
            if (found != s.results.end()) *found = std::move(result);
            else if (s.results.size() < 32) s.results.push_back(std::move(result));
        }
        const auto now = Now();
        if (now - s.since >= 3000) { s.searching = false; CloseSocket(s.io.socket); }
        else if (now - s.sent >= 750) s.Send();
    }
    bool Browser::Searching() const { return impl_->searching; }
    const std::vector<Advertisement>& Browser::Results() const { return impl_->results; }
    const std::string& Browser::Error() const { return impl_->error; }
}
