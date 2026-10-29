#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <mswsock.h>
#include <windows.h>
#include <wincrypt.h>
#include "embedded_lan_host.h"
#include "embedded_lan_model.h"
#include "lan_discovery.h"
#include "lan_no_auth_policy.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <map>
#include <mutex>
#include <stdexcept>
#include <thread>
#pragma comment(lib,"advapi32.lib")

namespace BZROpenShim::EmbeddedLan
{
namespace
{
    struct Socket
    {
        Socket()=default;
        Socket(const Socket&)=delete;
        Socket& operator=(const Socket&)=delete;
        SOCKET value = INVALID_SOCKET;
        ~Socket() { Close(); }
        void Close() { if (value != INVALID_SOCKET) closesocket(value); value = INVALID_SOCKET; }
    };
    void Nonblocking(SOCKET s)
    {
        u_long on = 1;
        if (ioctlsocket(s,FIONBIO,&on)) throw std::runtime_error("LAN socket nonblocking setup failed");
    }
    void Bind(Socket& s, int type, const std::string& ip, uint16_t port)
    {
        s.value = socket(AF_INET,type,type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP);
        if (s.value == INVALID_SOCKET) throw std::runtime_error("LAN socket creation failed");
        BOOL exclusive = TRUE;
        sockaddr_in address{}; address.sin_family = AF_INET; address.sin_port = htons(port);
        if (inet_pton(AF_INET,ip.c_str(),&address.sin_addr) != 1 ||
            setsockopt(s.value,SOL_SOCKET,SO_EXCLUSIVEADDRUSE,reinterpret_cast<const char*>(&exclusive),sizeof(exclusive)) ||
            bind(s.value,reinterpret_cast<sockaddr*>(&address),sizeof(address)))
            throw std::runtime_error("LAN bind failed on " + ip + ":" + std::to_string(port) +
                " (Winsock " + std::to_string(WSAGetLastError()) + ")");
        Nonblocking(s.value);
        if (type == SOCK_DGRAM)
        {
            BOOL reset = FALSE; DWORD bytes = 0;
            WSAIoctl(s.value,SIO_UDP_CONNRESET,&reset,sizeof(reset),nullptr,0,&bytes,nullptr,nullptr);
        }
    }
    std::string Base64(const unsigned char* bytes, size_t size)
    {
        constexpr char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string out;
        for (size_t i = 0; i < size; i += 3)
        {
            const uint32_t v = (uint32_t(bytes[i]) << 16) | (i+1<size ? uint32_t(bytes[i+1]) << 8 : 0) |
                (i+2<size ? uint32_t(bytes[i+2]) : 0);
            out += table[(v >> 18) & 63]; out += table[(v >> 12) & 63];
            out += i+1<size ? table[(v >> 6) & 63] : '='; out += i+2<size ? table[v & 63] : '=';
        }
        return out;
    }
    std::string AcceptKey(const std::string& key)
    {
        HCRYPTPROV provider = 0; HCRYPTHASH hash = 0;
        std::array<unsigned char,20> digest{}; DWORD size = DWORD(digest.size());
        const auto text = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        const bool ok = CryptAcquireContextW(&provider,nullptr,nullptr,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT) &&
            CryptCreateHash(provider,CALG_SHA1,0,0,&hash) &&
            CryptHashData(hash,reinterpret_cast<const BYTE*>(text.data()),DWORD(text.size()),0) &&
            CryptGetHashParam(hash,HP_HASHVAL,digest.data(),&size,0);
        if (hash) CryptDestroyHash(hash);
        if (provider) CryptReleaseContext(provider,0);
        if (!ok) throw std::runtime_error("LAN WebSocket handshake SHA1 unavailable");
        return Base64(digest.data(),digest.size());
    }
    std::string Frame(const std::string& body, unsigned opcode = 1)
    {
        std::string out(1,char(0x80 | opcode));
        if (body.size() < 126) out += char(body.size());
        else if (body.size() <= 65535)
        { out += char(126); out += char(body.size() >> 8); out += char(body.size()); }
        else
        {
            out += char(127);
            const auto size = uint64_t(body.size());
            for (int i = 7; i >= 0; --i) out += char(size >> (8*i));
        }
        return out + body;
    }
    bool Pending() { const auto error = WSAGetLastError(); return error == WSAEWOULDBLOCK; }
    uint64_t EpochMs()
    {
        FILETIME file{}; GetSystemTimeAsFileTime(&file);
        const uint64_t ticks = (uint64_t(file.dwHighDateTime) << 32) | file.dwLowDateTime;
        return ticks / 10000 - 11644473600000ULL;
    }
}
struct Host::Impl
{
    struct Client
    {
        SOCKET socket = INVALID_SOCKET;
        std::string input, output, fragments;
        bool upgraded = false, closing = false, fragmented = false;
        uint64_t since = 0, rateSince = 0;
        uint64_t closingSince = 0;
        unsigned messages = 0;
    };
    std::atomic<bool> stop{false}, running{false};
    std::thread worker;
    mutable std::mutex errorLock;
    std::string error;
    Socket listener, probe, discovery;
    bool winsock = false;
    uint16_t port = 1337;
    uint64_t next = 1;
    std::map<uint64_t,Client> clients;
    Model model;
    uint64_t datagramSince=0;
    unsigned datagramCount=0;

    void Queue(uint64_t id, const std::string& bytes)
    {
        auto it = clients.find(id); if (it == clients.end()) return;
        if (it->second.output.size() + bytes.size() > 512*1024)
        { it->second.closing = true; it->second.output.clear(); }
        else it->second.output += bytes;
    }
    void Deliver(const std::vector<Delivery>& messages)
    {
        for (const auto& message : messages) Queue(message.connection,Frame(message.message.dump()));
    }
    bool Handshake(Client& c)
    {
        const auto end = c.input.find("\r\n\r\n");
        if (end == std::string::npos) return c.input.size() <= 8192;
        if (end > 8192 || c.input.compare(0,4,"GET ")) return false;
        std::string header = c.input.substr(0,end+2);
        std::transform(header.begin(),header.end(),header.begin(),[](unsigned char ch){return char(std::tolower(ch));});
        if (header.find("upgrade: websocket\r\n") == std::string::npos ||
            header.find("sec-websocket-version: 13\r\n") == std::string::npos) return false;
        const auto at = header.find("sec-websocket-key:");
        if (at == std::string::npos) return false;
        auto start = at + 18; while (start < end && c.input[start] == ' ') ++start;
        const auto finish = c.input.find("\r\n",start);
        const auto key = c.input.substr(start,finish-start);
        if (key.size() != 24 || key.substr(22) != "==" ||
            key.substr(0,22).find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") != std::string::npos) return false;
        c.output += "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: " + AcceptKey(key) + "\r\n\r\n";
        c.upgraded = true; c.input.erase(0,end+4); return true;
    }
    bool ReadFrames(uint64_t id, Client& c, uint64_t now)
    {
        for (unsigned count = 0; count < 32 && c.input.size() >= 2; ++count)
        {
            const auto* bytes = reinterpret_cast<const unsigned char*>(c.input.data());
            const unsigned opcode = bytes[0] & 15;
            const bool fin = (bytes[0] & 128) != 0;
            if ((bytes[0] & 0x70) || !(bytes[1] & 128)) return false;
            uint64_t size = bytes[1] & 127; size_t head = 2;
            if (size == 126)
            { if (c.input.size() < 4) return true; size = (uint64_t(bytes[2]) << 8) | bytes[3]; head = 4; if (size<126) return false; }
            else if (size == 127)
            {
                if (c.input.size() < 10) return true;
                size = 0; for (unsigned i = 2; i < 10; ++i) size = (size << 8) | bytes[i]; head = 10;
                if (size<=65535) return false;
            }
            if (size > 65536 || (opcode >= 8 && (!fin || size > 125))) return false;
            if (c.input.size() < head+4+size) return true;
            std::string body(size_t(size),'\0');
            for (size_t i = 0; i < body.size(); ++i) body[i] = char(bytes[head+4+i] ^ bytes[head+(i%4)]);
            c.input.erase(0,head+4+size_t(size));
            if (now - c.rateSince >= 1000) { c.messages = 0; c.rateSince = now; }
            if (++c.messages > 200) return false;
            if (opcode == 8) { Queue(id,Frame(body,8)); c.closing = true; return true; }
            if (opcode == 9) { Queue(id,Frame(body,10)); continue; }
            if (opcode == 10) continue;
            if ((opcode != 1 && opcode != 0) || (opcode == 0) != c.fragmented) return false;
            if (c.fragments.size() + body.size() > 65536) return false;
            c.fragments += body; c.fragmented = !fin;
            if (fin)
            {
                const auto message = Json::parse(c.fragments,nullptr,false);
                c.fragments.clear();
                if (message.is_discarded()) return false;
                Deliver(model.Receive(id,message));
            }
        }
        return true;
    }
    void Datagrams(SOCKET socket, bool browse)
    {
        for (unsigned i = 0; i < 64; ++i)
        {
            char bytes[256]; sockaddr_in sender{}; int length = sizeof(sender);
            const int size = recvfrom(socket,bytes,sizeof(bytes),0,reinterpret_cast<sockaddr*>(&sender),&length);
            if (size < 0) break;
            if (sender.sin_family != AF_INET || !LanDiscovery::IsLocalIPv4(ntohl(sender.sin_addr.s_addr))) continue;
            const auto tick=GetTickCount64();
            if (tick-datagramSince>=1000) {datagramSince=tick;datagramCount=0;}
            if (++datagramCount>256) continue;
            std::string response;
            if (browse)
            {
                if (size != 96 || std::memcmp(bytes,"BZRLAN1?",8) ||
                    !std::all_of(bytes+16,bytes+96,[](char ch){return ch==0;})) continue;
                response.assign("BZRLAN1!",8); response.append(bytes+8,8);
                response += char(port >> 8); response += char(port); response += "OpenShim LAN (no sign-in)";
            }
            else
            {
                if (size != 18 || (bytes[0] & 0xc0) != 0x40 || (bytes[1] & 15) != 2) continue;
                uint64_t sent = 0; for (unsigned j=2;j<10;++j) sent=(sent<<8)|static_cast<unsigned char>(bytes[j]);
                const auto now = EpochMs(); if (sent > now+60000 || now > sent+60000) continue;
                response.assign(bytes,18); response += char(4);
                response.append(reinterpret_cast<const char*>(&sender.sin_addr),4);
                response.append(reinterpret_cast<const char*>(&sender.sin_port),2);
            }
            sendto(socket,response.data(),int(response.size()),0,reinterpret_cast<sockaddr*>(&sender),length);
        }
    }
    void Run()
    {
        try
        {
            while (!stop.load())
            {
                const auto now = GetTickCount64();
                for (unsigned i = 0; i < 8; ++i)
                {
                    sockaddr_in sender{}; int length = sizeof(sender);
                    const auto socket = accept(listener.value,reinterpret_cast<sockaddr*>(&sender),&length);
                    if (socket == INVALID_SOCKET) break;
                    if (clients.size() >= 16 || !LanDiscovery::IsLocalIPv4(ntohl(sender.sin_addr.s_addr)))
                    { closesocket(socket); continue; }
                    Socket accepted; accepted.value=socket;
                    Nonblocking(socket);
                    char address[INET_ADDRSTRLEN]{}; inet_ntop(AF_INET,&sender.sin_addr,address,sizeof(address));
                    const auto id = next++;
                    clients[id].socket = socket; clients[id].since = now;
                    accepted.value=INVALID_SOCKET;
                    model.Connect(id,address);
                }
                Datagrams(probe.value,false); Datagrams(discovery.value,true);
                std::vector<uint64_t> removed;
                for (auto& entry : clients)
                {
                    const auto id = entry.first; auto& c = entry.second;
                    bool alive = true;
                    for (unsigned i=0;i<8 && !c.closing;++i)
                    {
                        char bytes[4096]; const int size = recv(c.socket,bytes,sizeof(bytes),0);
                        if (size == 0 || (size < 0 && !Pending())) { alive=false; break; }
                        if (size < 0) break;
                        c.input.append(bytes,size);
                        if (c.input.size() > 128*1024) { alive=false; break; }
                    }
                    if (!c.upgraded && (now-c.since > 10000 || !Handshake(c))) alive=false;
                    if (now-c.since>10000 && !model.Admitted(id)) alive=false;
                    if (alive && c.upgraded && !c.closing && !ReadFrames(id,c,now)) alive=false;
                    if (!c.output.empty())
                    {
                        const int size=send(c.socket,c.output.data(),int((std::min)(c.output.size(),size_t(32768))),0);
                        if (size>0) c.output.erase(0,size_t(size)); else if (!Pending()) alive=false;
                    }
                    if (!alive || (c.closing && c.output.empty())) removed.push_back(id);
                    else if (c.closing)
                    {
                        if (!c.closingSince) c.closingSince=now;
                        if (now-c.closingSince>2000) removed.push_back(id);
                    }
                }
                for (const auto id : removed)
                { closesocket(clients.at(id).socket); clients.erase(id); Deliver(model.Disconnect(id)); }
                // Bounded worker wait; no game-thread polling or loader work.
                fd_set reads; FD_ZERO(&reads); FD_SET(listener.value,&reads);
                FD_SET(probe.value,&reads); FD_SET(discovery.value,&reads);
                for (const auto& entry : clients) FD_SET(entry.second.socket,&reads);
                timeval timeout{0,10000}; select(0,&reads,nullptr,nullptr,&timeout);
            }
        }
        catch (const std::exception& e) { std::lock_guard<std::mutex> lock(errorLock); error=e.what(); }
        running=false;
    }
    void Stop()
    {
        stop=true; if (worker.joinable()) worker.join();
        for (const auto& entry : clients) closesocket(entry.second.socket);
        clients.clear(); listener.Close(); probe.Close(); discovery.Close();
        if (winsock) WSACleanup(); winsock=false; running=false;
    }
};
Host::Host() : impl(new Impl) {}
Host::~Host() { Stop(); }
bool Host::Start(const std::string& ip, unsigned short port)
{
    if (impl->running) return true;
    impl->Stop(); impl->stop=false; impl->model=Model{};
    { std::lock_guard<std::mutex> lock(impl->errorLock); impl->error.clear(); }
    try
    {
        std::string address;
        if (port==65535 || !LanNoAuth::PrivateEndpoint(ip+":"+std::to_string(port),address))
            throw std::runtime_error("Choose a private LAN IPv4 address and port 1..65534");
        WSADATA data{}; if (WSAStartup(MAKEWORD(2,2),&data)) throw std::runtime_error("LAN Winsock initialization failed");
        impl->winsock=true; impl->port=port;
        Bind(impl->listener,SOCK_STREAM,ip,port);
        if (listen(impl->listener.value,16)) throw std::runtime_error("LAN listen failed");
        Bind(impl->probe,SOCK_DGRAM,ip,uint16_t(port+1));
        Bind(impl->discovery,SOCK_DGRAM,"0.0.0.0",LanDiscovery::kPort);
        impl->running=true; impl->worker=std::thread([this]{impl->Run();}); return true;
    }
    catch (const std::exception& e)
    {
        { std::lock_guard<std::mutex> lock(impl->errorLock); impl->error=e.what(); }
        impl->Stop(); return false;
    }
}
void Host::Stop() { impl->Stop(); }
bool Host::Running() const { return impl->running.load(); }
std::string Host::Error() const { std::lock_guard<std::mutex> lock(impl->errorLock); return impl->error; }
}
