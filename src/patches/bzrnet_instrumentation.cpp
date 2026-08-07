#include "bzrnet_instrumentation.h"
#include "bzrnet_protocol.h"
#include "bzrnet_trace.h"
#include "shim_log.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace BZROpenShim
{
namespace
{
    constexpr uint16_t kWsPort = 1337;
    constexpr uint16_t kProbePort = 1338;
    constexpr uint16_t kRelayPort = 1339;
    constexpr size_t kMaxWsBytes = 1024 * 1024;
    constexpr size_t kWirePrefixBytes = 96;

    struct Config
    {
        bool enabled = false;
        bool privateForensic = false;
        bool allUdp = false;
        uint32_t queueRecords = 4096;
    };

    struct WsDirection
    {
        bool handshakeComplete = false;
        uint8_t fragmentedOpcode = 0;
        std::vector<uint8_t> pending;
        std::vector<uint8_t> fragmented;
    };

    struct WsState
    {
        WsDirection outbound;
        WsDirection inbound;
    };

    enum class PendingKind : uint8_t { Stream, Datagram };
    struct PendingIo
    {
        PendingKind kind = PendingKind::Stream;
        SOCKET socket = INVALID_SOCKET;
        std::vector<WSABUF> buffers;
        sockaddr* from = nullptr;
        LPINT fromLen = nullptr;
        LPWSAOVERLAPPED_COMPLETION_ROUTINE originalCompletion = nullptr;
        bool capturedImmediate = false;
    };

    struct SocketIdentity
    {
        uint32_t id = 0;
        uint32_t generation = 0;
    };

    using SendFn = int (WSAAPI*)(SOCKET, const char*, int, int);
    using RecvFn = int (WSAAPI*)(SOCKET, char*, int, int);
    using SendToFn = int (WSAAPI*)(SOCKET, const char*, int, int, const sockaddr*, int);
    using RecvFromFn = int (WSAAPI*)(SOCKET, char*, int, int, sockaddr*, int*);
    using WSASendFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSASendToFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const sockaddr*, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFromFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, sockaddr*, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using CloseSocketFn = int (WSAAPI*)(SOCKET);
    using GqcsFn = BOOL (WINAPI*)(HANDLE, LPDWORD, PULONG_PTR, LPOVERLAPPED*, DWORD);

    Config g_Config;
    INIT_ONCE g_InitOnce = INIT_ONCE_STATIC_INIT;
    volatile LONG g_Shutdown = 0;

    SendFn g_Send = nullptr;
    RecvFn g_Recv = nullptr;
    SendToFn g_SendTo = nullptr;
    RecvFromFn g_RecvFrom = nullptr;
    WSASendFn g_WSASend = nullptr;
    WSARecvFn g_WSARecv = nullptr;
    WSASendToFn g_WSASendTo = nullptr;
    WSARecvFromFn g_WSARecvFrom = nullptr;
    CloseSocketFn g_CloseSocket = nullptr;
    GqcsFn g_Gqcs = nullptr;

    SRWLOCK g_WsLock = SRWLOCK_INIT;
    std::unordered_map<SOCKET, WsState> g_Ws;
    SRWLOCK g_PendingLock = SRWLOCK_INIT;
    std::unordered_map<LPWSAOVERLAPPED, PendingIo> g_Pending;
    SRWLOCK g_SocketLock = SRWLOCK_INIT;
    std::unordered_map<SOCKET, SocketIdentity> g_Sockets;
    volatile LONG g_NextSocketId = 0;

    std::string GameDir()
    {
        char path[MAX_PATH] = {};
        const DWORD n = GetModuleFileNameA(nullptr, path, static_cast<DWORD>(sizeof(path)));
        if (!n || n >= sizeof(path)) return ".";
        std::string value(path, n);
        const size_t slash = value.find_last_of("\\/");
        return slash == std::string::npos ? "." : value.substr(0, slash);
    }

    bool EnvBool(const char* name)
    {
        char value[32] = {};
        const DWORD n = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        if (!n || n >= sizeof(value)) return false;
        return _stricmp(value, "1") == 0 || _stricmp(value, "true") == 0 ||
            _stricmp(value, "yes") == 0 || _stricmp(value, "on") == 0;
    }

    uint32_t EnvUint(const char* name, uint32_t fallback)
    {
        char value[64] = {};
        const DWORD n = GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value)));
        if (!n || n >= sizeof(value)) return fallback;
        char* end = nullptr;
        const unsigned long parsed = std::strtoul(value, &end, 10);
        return end && *end == '\0' ? static_cast<uint32_t>(parsed) : fallback;
    }

    Config LoadConfig()
    {
        Config cfg;
        const std::string ini = GameDir() + "\\net.ini";
        cfg.enabled = GetPrivateProfileIntA("OpenShimSocket", "EnableBZRNetTrace", 0, ini.c_str()) != 0;
        cfg.privateForensic = GetPrivateProfileIntA("OpenShimSocket", "BZRNetTracePrivate", 0, ini.c_str()) != 0;
        cfg.allUdp = GetPrivateProfileIntA("OpenShimSocket", "BZRNetTraceAllUdp", 0, ini.c_str()) != 0;
        cfg.queueRecords = static_cast<uint32_t>(GetPrivateProfileIntA("OpenShimSocket", "BZRNetTraceQueueRecords", 4096, ini.c_str()));
        cfg.enabled = cfg.enabled || EnvBool("BZ_BZRNET_TRACE") || EnvBool("OPENSHIM_BZRNET_TRACE");
        cfg.enabled = cfg.enabled || EnvBool("BZ_RELAY_CAPTURE") || EnvBool("OPENSHIM_RELAY_CAPTURE");
        cfg.privateForensic = cfg.privateForensic || EnvBool("BZ_BZRNET_TRACE_PRIVATE") || EnvBool("OPENSHIM_BZRNET_TRACE_PRIVATE");
        cfg.allUdp = cfg.allUdp || EnvBool("BZ_BZRNET_TRACE_ALL_UDP") || EnvBool("OPENSHIM_BZRNET_TRACE_ALL_UDP");
        cfg.queueRecords = EnvUint("BZ_BZRNET_TRACE_QUEUE", cfg.queueRecords);
        cfg.queueRecords = EnvUint("OPENSHIM_BZRNET_TRACE_QUEUE", cfg.queueRecords);
        cfg.queueRecords = (std::max)(256u, (std::min)(cfg.queueRecords, 65536u));
        return cfg;
    }

    SocketIdentity RememberSocket(SOCKET s)
    {
        if (s == INVALID_SOCKET) return {};
        AcquireSRWLockExclusive(&g_SocketLock);
        SocketIdentity& state = g_Sockets[s];
        if (!state.id)
        {
            state.id = static_cast<uint32_t>(InterlockedIncrement(&g_NextSocketId));
            state.generation = BzrNetTraceRememberSocket(static_cast<uintptr_t>(s));
        }
        const SocketIdentity copy = state;
        ReleaseSRWLockExclusive(&g_SocketLock);
        return copy;
    }

    SocketIdentity SocketFor(SOCKET s)
    {
        AcquireSRWLockShared(&g_SocketLock);
        const auto it = g_Sockets.find(s);
        const SocketIdentity copy = it == g_Sockets.end() ? SocketIdentity{} : it->second;
        ReleaseSRWLockShared(&g_SocketLock);
        return copy.id ? copy : RememberSocket(s);
    }

    void ForgetSocket(SOCKET s)
    {
        BzrNetTraceForgetSocket(static_cast<uintptr_t>(s));
        AcquireSRWLockExclusive(&g_SocketLock);
        g_Sockets.erase(s);
        ReleaseSRWLockExclusive(&g_SocketLock);
        AcquireSRWLockExclusive(&g_WsLock);
        g_Ws.erase(s);
        ReleaseSRWLockExclusive(&g_WsLock);
    }

    uint16_t PortOf(const sockaddr* address, int length)
    {
        if (!address || length <= 0) return 0;
        if (address->sa_family == AF_INET && length >= static_cast<int>(sizeof(sockaddr_in)))
            return ntohs(reinterpret_cast<const sockaddr_in*>(address)->sin_port);
        if (address->sa_family == AF_INET6 && length >= static_cast<int>(sizeof(sockaddr_in6)))
            return ntohs(reinterpret_cast<const sockaddr_in6*>(address)->sin6_port);
        return 0;
    }

    std::string EndpointOf(const sockaddr* address, int length)
    {
        if (!address || length <= 0) return {};
        char host[INET6_ADDRSTRLEN] = {};
        uint16_t port = PortOf(address, length);
        if (address->sa_family == AF_INET && length >= static_cast<int>(sizeof(sockaddr_in)))
        {
            const auto* a = reinterpret_cast<const sockaddr_in*>(address);
            InetNtopA(AF_INET, &a->sin_addr, host, static_cast<DWORD>(sizeof(host)));
        }
        else if (address->sa_family == AF_INET6 && length >= static_cast<int>(sizeof(sockaddr_in6)))
        {
            const auto* a = reinterpret_cast<const sockaddr_in6*>(address);
            InetNtopA(AF_INET6, &a->sin6_addr, host, static_cast<DWORD>(sizeof(host)));
        }
        else return {};
        char out[128] = {};
        _snprintf_s(out, _TRUNCATE, "%s:%u", host, static_cast<unsigned>(port));
        return out;
    }

    bool IsWsSocket(SOCKET s)
    {
        sockaddr_storage peer = {};
        int length = static_cast<int>(sizeof(peer));
        if (getpeername(s, reinterpret_cast<sockaddr*>(&peer), &length) != 0) return false;
        return PortOf(reinterpret_cast<const sockaddr*>(&peer), length) == kWsPort;
    }

    std::string JsonEscape(const std::string& input)
    {
        std::string out;
        out.reserve(input.size() + 8);
        for (const unsigned char c : input)
        {
            switch (c)
            {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default: out.push_back(c < 0x20 ? '?' : static_cast<char>(c)); break;
            }
        }
        return out;
    }

    uint64_t Fnv1a64(const uint8_t* data, size_t length)
    {
        uint64_t hash = 1469598103934665603ull;
        for (size_t i = 0; i < length; ++i) { hash ^= data[i]; hash *= 1099511628211ull; }
        return hash;
    }

    std::string HexPrefix(const uint8_t* data, size_t length)
    {
        static const char hex[] = "0123456789abcdef";
        const size_t count = (std::min)(length, kWirePrefixBytes);
        std::string out(count * 2, '0');
        for (size_t i = 0; i < count; ++i)
        {
            out[i * 2] = hex[data[i] >> 4];
            out[i * 2 + 1] = hex[data[i] & 0x0f];
        }
        return out;
    }

    uint32_t Gather(LPWSABUF buffers, DWORD count, uint8_t* output, uint32_t capacity)
    {
        if (!buffers || !output || !capacity) return 0;
        uint32_t copied = 0;
        for (DWORD i = 0; i < count && copied < capacity; ++i)
        {
            if (!buffers[i].buf || !buffers[i].len) continue;
            const uint32_t chunk = (std::min)(static_cast<uint32_t>(buffers[i].len), capacity - copied);
            std::memcpy(output + copied, buffers[i].buf, chunk);
            copied += chunk;
        }
        return copied;
    }

    uint32_t Requested(LPWSABUF buffers, DWORD count)
    {
        uint32_t total = 0;
        if (!buffers) return 0;
        for (DWORD i = 0; i < count; ++i) total += static_cast<uint32_t>(buffers[i].len);
        return total;
    }

    void TraceWire(SOCKET s, bool outbound, const sockaddr* endpoint, int endpointLen, const uint8_t* data, size_t length, bool pending)
    {
        if (!data || !length) return;
        const uint16_t port = PortOf(endpoint, endpointLen);
        if (!g_Config.allUdp && port != kProbePort && port != kRelayPort) return;
        const SocketIdentity socket = SocketFor(s);
        const std::string endpointText = SanitizeBzrNetEndpoint(EndpointOf(endpoint, endpointLen), g_Config.privateForensic);
        char hash[32] = {};
        _snprintf_s(hash, _TRUNCATE, "%016llx", static_cast<unsigned long long>(Fnv1a64(data, length)));
        BzrUdpControlInfo control = DecodeBzrUdpControl(data, length);
        if (!control.recognized && length >= 20) control = DecodeBzrUdpControl(data + 18, length - 18);
        std::string details = "{\"transport\":\"udp\",\"port\":" + std::to_string(port) +
            ",\"endpoint\":\"" + JsonEscape(endpointText) + "\",\"payloadLength\":" + std::to_string(length) +
            ",\"fnv1a64\":\"" + hash + "\",\"payloadPrefixHex\":\"" + HexPrefix(data, length) + "\",\"pending\":" +
            (pending ? "true" : "false");
        if (length >= 18) details += ",\"commonKind\":" + std::to_string(data[1] & 0x0f);
        if (control.recognized)
        {
            details += ",\"controlMarker\":\"" + JsonEscape(control.marker) + "\",\"controlMeaning\":\"" +
                JsonEscape(control.likelyMeaning) + "\",\"controlEvidence\":\"" + BzrNetEvidenceName(control.evidence) + "\"";
            if (control.fieldCount)
            {
                const uint32_t fields[5] = {control.field0, control.field1, control.field2, control.field3, control.field4};
                details += ",\"controlFields\":[";
                for (uint32_t i = 0; i < control.fieldCount; ++i) { if (i) details += ','; details += std::to_string(fields[i]); }
                details += ']';
            }
        }
        details += '}';
        EmitBzrNetTrace("wire", outbound ? "UDP_WIRE_TX" : "UDP_WIRE_RX", outbound ? "outbound" : "inbound",
            socket.id, socket.generation, "", details);
    }

    void ProcessWsMessage(SOCKET s, bool outbound, uint8_t opcode, const std::vector<uint8_t>& payload)
    {
        if (opcode != 0x1 || payload.empty()) return;
        const std::string json(payload.begin(), payload.end());
        std::string type;
        const bool hasType = ExtractBzrNetMessageType(json, type);
        const BzrNetMessageInfo* info = hasType ? LookupBzrNetMessage(type) : nullptr;
        const BzrNetSanitizedMessage safe = SanitizeBzrNetJson(json, g_Config.privateForensic);
        int64_t reasonCode = 0;
        bool success = false;
        const bool hasReason = TryExtractBzrNetJsonInt(json, "reasonCode", reasonCode);
        const bool hasSuccess = TryExtractBzrNetJsonBool(json, "success", success);
        std::string details = "{\"knownMessage\":" + std::string(info ? "true" : "false") +
            ",\"protocolEvidence\":\"" + BzrNetEvidenceName(info ? info->evidence : BzrNetEvidence::Unknown) + "\"";
        if (info && info->envelope) details += ",\"envelope\":\"" + std::string(info->envelope) + "\"";
        if (safe.authTicketRedacted) details += ",\"authTicket\":{\"redacted\":true,\"length\":" + std::to_string(safe.authTicketLength) + '}';
        if (safe.passwordRedacted) details += ",\"password\":{\"redacted\":true,\"length\":" + std::to_string(safe.passwordLength) + '}';
        if (hasReason) details += ",\"reasonCode\":" + std::to_string(reasonCode);
        if (hasSuccess) details += ",\"success\":" + std::string(success ? "true" : "false");
        details += ",\"messageJson\":\"" + JsonEscape(safe.json) + "\"}";
        const SocketIdentity socket = SocketFor(s);
        EmitBzrNetTrace("websocket", outbound ? "BZR_WS_TX" : "BZR_WS_RX", outbound ? "outbound" : "inbound",
            socket.id, socket.generation, hasType ? type.c_str() : "<unknown>", details);
    }

    size_t HeaderEnd(const std::vector<uint8_t>& data)
    {
        static const uint8_t delimiter[] = {'\r','\n','\r','\n'};
        const auto it = std::search(data.begin(), data.end(), std::begin(delimiter), std::end(delimiter));
        return it == data.end() ? std::string::npos : static_cast<size_t>(it - data.begin()) + sizeof(delimiter);
    }

    void ProcessWsDirection(SOCKET s, bool outbound, WsDirection& state, const uint8_t* bytes, size_t length)
    {
        if (!bytes || !length) return;
        if (state.pending.size() + length > kMaxWsBytes)
        {
            state.pending.clear(); state.fragmented.clear(); state.fragmentedOpcode = 0; return;
        }
        state.pending.insert(state.pending.end(), bytes, bytes + length);
        if (!state.handshakeComplete)
        {
            const size_t end = HeaderEnd(state.pending);
            if (end == std::string::npos) { if (state.pending.size() > 64 * 1024) state.pending.clear(); return; }
            state.pending.erase(state.pending.begin(), state.pending.begin() + end);
            state.handshakeComplete = true;
        }
        while (state.pending.size() >= 2)
        {
            const uint8_t first = state.pending[0], second = state.pending[1];
            const bool fin = (first & 0x80u) != 0, masked = (second & 0x80u) != 0;
            const uint8_t opcode = first & 0x0fu;
            uint64_t payloadLength = second & 0x7fu;
            size_t headerLength = 2;
            if (payloadLength == 126)
            {
                if (state.pending.size() < 4) return;
                payloadLength = (static_cast<uint64_t>(state.pending[2]) << 8) | state.pending[3]; headerLength = 4;
            }
            else if (payloadLength == 127)
            {
                if (state.pending.size() < 10) return;
                payloadLength = 0; for (size_t i = 2; i < 10; ++i) payloadLength = (payloadLength << 8) | state.pending[i]; headerLength = 10;
            }
            if (payloadLength > kMaxWsBytes) { state.pending.clear(); state.fragmented.clear(); state.fragmentedOpcode = 0; return; }
            uint8_t mask[4] = {};
            if (masked)
            {
                if (state.pending.size() < headerLength + 4) return;
                std::memcpy(mask, state.pending.data() + headerLength, 4); headerLength += 4;
            }
            if (state.pending.size() < headerLength + static_cast<size_t>(payloadLength)) return;
            std::vector<uint8_t> payload(static_cast<size_t>(payloadLength));
            for (size_t i = 0; i < payload.size(); ++i)
            {
                payload[i] = state.pending[headerLength + i]; if (masked) payload[i] ^= mask[i % 4];
            }
            state.pending.erase(state.pending.begin(), state.pending.begin() + headerLength + static_cast<size_t>(payloadLength));
            if (opcode == 0x0)
            {
                if (!state.fragmentedOpcode || state.fragmented.size() + payload.size() > kMaxWsBytes)
                { state.fragmented.clear(); state.fragmentedOpcode = 0; continue; }
                state.fragmented.insert(state.fragmented.end(), payload.begin(), payload.end());
                if (fin) { ProcessWsMessage(s, outbound, state.fragmentedOpcode, state.fragmented); state.fragmented.clear(); state.fragmentedOpcode = 0; }
            }
            else if (opcode == 0x1 || opcode == 0x2)
            {
                if (fin) ProcessWsMessage(s, outbound, opcode, payload);
                else { state.fragmentedOpcode = opcode; state.fragmented = std::move(payload); }
            }
        }
    }

    void FeedWs(SOCKET s, bool outbound, const uint8_t* data, size_t length)
    {
        if (!IsBzrNetTraceEnabled() || !data || !length || !IsWsSocket(s)) return;
        RememberSocket(s);
        AcquireSRWLockExclusive(&g_WsLock);
        WsState& state = g_Ws[s];
        ProcessWsDirection(s, outbound, outbound ? state.outbound : state.inbound, data, length);
        ReleaseSRWLockExclusive(&g_WsLock);
    }

    bool RegisterPending(LPWSAOVERLAPPED overlapped, PendingKind kind, SOCKET s, LPWSABUF buffers, DWORD count,
        sockaddr* from, LPINT fromLen, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
    {
        if (!overlapped || !buffers || !count || !IsBzrNetTraceEnabled()) return false;
        if (kind == PendingKind::Stream && !IsWsSocket(s)) return false;
        PendingIo io;
        io.kind = kind; io.socket = s; io.buffers.assign(buffers, buffers + count); io.from = from; io.fromLen = fromLen; io.originalCompletion = completion;
        AcquireSRWLockExclusive(&g_PendingLock);
        g_Pending[overlapped] = std::move(io);
        ReleaseSRWLockExclusive(&g_PendingLock);
        return true;
    }

    bool TakePending(LPWSAOVERLAPPED overlapped, PendingIo& out, bool remove)
    {
        if (!overlapped) return false;
        AcquireSRWLockExclusive(&g_PendingLock);
        const auto it = g_Pending.find(overlapped);
        if (it == g_Pending.end()) { ReleaseSRWLockExclusive(&g_PendingLock); return false; }
        out = it->second; if (remove) g_Pending.erase(it);
        ReleaseSRWLockExclusive(&g_PendingLock);
        return true;
    }

    void MarkImmediate(LPWSAOVERLAPPED overlapped)
    {
        AcquireSRWLockExclusive(&g_PendingLock);
        const auto it = g_Pending.find(overlapped);
        if (it != g_Pending.end()) it->second.capturedImmediate = true;
        ReleaseSRWLockExclusive(&g_PendingLock);
    }

    void CapturePending(const PendingIo& io, DWORD transferred)
    {
        if (!transferred || io.buffers.empty()) return;
        const uint32_t limit = io.kind == PendingKind::Stream ? static_cast<uint32_t>(kMaxWsBytes) : 2048u;
        const uint32_t capacity = (std::min)(transferred, limit);
        std::vector<uint8_t> data(capacity);
        const uint32_t copied = Gather(const_cast<WSABUF*>(io.buffers.data()), static_cast<DWORD>(io.buffers.size()), data.data(), capacity);
        if (!copied) return;
        if (io.kind == PendingKind::Stream) FeedWs(io.socket, false, data.data(), copied);
        else TraceWire(io.socket, false, io.from, io.fromLen ? *io.fromLen : 0, data.data(), copied, false);
    }

    void CALLBACK CompletionThunk(DWORD error, DWORD transferred, LPWSAOVERLAPPED overlapped, DWORD flags)
    {
        PendingIo io;
        if (!TakePending(overlapped, io, true)) return;
        if (!error && !io.capturedImmediate) CapturePending(io, transferred);
        if (io.originalCompletion) io.originalCompletion(error, transferred, overlapped, flags);
    }

    int WSAAPI HookSend(SOCKET s, const char* buffer, int length, int flags)
    {
        const int rc = g_Send ? g_Send(s, buffer, length, flags) : SOCKET_ERROR;
        if (rc > 0 && buffer) FeedWs(s, true, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc));
        return rc;
    }

    int WSAAPI HookRecv(SOCKET s, char* buffer, int length, int flags)
    {
        const int rc = g_Recv ? g_Recv(s, buffer, length, flags) : SOCKET_ERROR;
        if (rc > 0 && buffer) FeedWs(s, false, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc));
        return rc;
    }

    int WSAAPI HookSendTo(SOCKET s, const char* buffer, int length, int flags, const sockaddr* to, int toLen)
    {
        const int rc = g_SendTo ? g_SendTo(s, buffer, length, flags, to, toLen) : SOCKET_ERROR;
        if (rc > 0 && buffer) TraceWire(s, true, to, toLen, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc), false);
        return rc;
    }

    int WSAAPI HookRecvFrom(SOCKET s, char* buffer, int length, int flags, sockaddr* from, int* fromLen)
    {
        const int rc = g_RecvFrom ? g_RecvFrom(s, buffer, length, flags, from, fromLen) : SOCKET_ERROR;
        if (rc > 0 && buffer) TraceWire(s, false, from, fromLen ? *fromLen : 0, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc), false);
        return rc;
    }

    int WSAAPI HookWSASend(SOCKET s, LPWSABUF buffers, DWORD count, LPDWORD bytesSent, DWORD flags,
        LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
    {
        const int rc = g_WSASend ? g_WSASend(s, buffers, count, bytesSent, flags, overlapped, completion) : SOCKET_ERROR;
        const int err = rc == SOCKET_ERROR ? WSAGetLastError() : 0;
        if (rc == 0 || err == WSA_IO_PENDING)
        {
            const uint32_t bytes = rc == 0 && bytesSent ? *bytesSent : Requested(buffers, count);
            const uint32_t capacity = (std::min)(bytes, static_cast<uint32_t>(kMaxWsBytes));
            std::vector<uint8_t> data(capacity);
            const uint32_t copied = capacity ? Gather(buffers, count, data.data(), capacity) : 0;
            if (copied) FeedWs(s, true, data.data(), copied);
        }
        if (rc == SOCKET_ERROR) WSASetLastError(err);
        return rc;
    }

    int WSAAPI HookWSARecv(SOCKET s, LPWSABUF buffers, DWORD count, LPDWORD bytesRecv, LPDWORD flags,
        LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
    {
        const bool registered = RegisterPending(overlapped, PendingKind::Stream, s, buffers, count, nullptr, nullptr, completion);
        const auto effective = registered && completion ? CompletionThunk : completion;
        const int rc = g_WSARecv ? g_WSARecv(s, buffers, count, bytesRecv, flags, overlapped, effective) : SOCKET_ERROR;
        const int err = rc == SOCKET_ERROR ? WSAGetLastError() : 0;
        if (rc == 0 && bytesRecv && *bytesRecv)
        {
            const uint32_t capacity = (std::min)(*bytesRecv, static_cast<DWORD>(kMaxWsBytes));
            std::vector<uint8_t> data(capacity);
            const uint32_t copied = Gather(buffers, count, data.data(), capacity);
            if (copied) FeedWs(s, false, data.data(), copied);
            if (registered) MarkImmediate(overlapped);
        }
        else if (registered && err != WSA_IO_PENDING) { PendingIo ignored; TakePending(overlapped, ignored, true); }
        if (rc == SOCKET_ERROR) WSASetLastError(err);
        return rc;
    }

    int WSAAPI HookWSASendTo(SOCKET s, LPWSABUF buffers, DWORD count, LPDWORD bytesSent, DWORD flags,
        const sockaddr* to, int toLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
    {
        const int rc = g_WSASendTo ? g_WSASendTo(s, buffers, count, bytesSent, flags, to, toLen, overlapped, completion) : SOCKET_ERROR;
        const int err = rc == SOCKET_ERROR ? WSAGetLastError() : 0;
        if (rc == 0 || err == WSA_IO_PENDING)
        {
            const uint32_t bytes = rc == 0 && bytesSent ? *bytesSent : Requested(buffers, count);
            const uint32_t capacity = (std::min)(bytes, 2048u);
            std::vector<uint8_t> data(capacity);
            const uint32_t copied = capacity ? Gather(buffers, count, data.data(), capacity) : 0;
            if (copied) TraceWire(s, true, to, toLen, data.data(), copied, err == WSA_IO_PENDING);
        }
        if (rc == SOCKET_ERROR) WSASetLastError(err);
        return rc;
    }

    int WSAAPI HookWSARecvFrom(SOCKET s, LPWSABUF buffers, DWORD count, LPDWORD bytesRecv, LPDWORD flags,
        sockaddr* from, LPINT fromLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
    {
        const bool registered = RegisterPending(overlapped, PendingKind::Datagram, s, buffers, count, from, fromLen, completion);
        const auto effective = registered && completion ? CompletionThunk : completion;
        const int rc = g_WSARecvFrom ? g_WSARecvFrom(s, buffers, count, bytesRecv, flags, from, fromLen, overlapped, effective) : SOCKET_ERROR;
        const int err = rc == SOCKET_ERROR ? WSAGetLastError() : 0;
        if (rc == 0 && bytesRecv && *bytesRecv)
        {
            const uint32_t capacity = (std::min)(*bytesRecv, 2048u);
            std::vector<uint8_t> data(capacity);
            const uint32_t copied = Gather(buffers, count, data.data(), capacity);
            if (copied) TraceWire(s, false, from, fromLen ? *fromLen : 0, data.data(), copied, false);
            if (registered) MarkImmediate(overlapped);
        }
        else if (registered && err != WSA_IO_PENDING) { PendingIo ignored; TakePending(overlapped, ignored, true); }
        if (rc == SOCKET_ERROR) WSASetLastError(err);
        return rc;
    }

    int WSAAPI HookCloseSocket(SOCKET s)
    {
        const SocketIdentity socket = SocketFor(s);
        const int rc = g_CloseSocket ? g_CloseSocket(s) : SOCKET_ERROR;
        if (rc == 0)
        {
            EmitBzrNetTrace("socket", "SOCKET_CLOSED", "internal", socket.id, socket.generation, "", "{}");
            ForgetSocket(s);
        }
        return rc;
    }

    BOOL WINAPI HookGqcs(HANDLE port, LPDWORD bytes, PULONG_PTR key, LPOVERLAPPED* overlapped, DWORD timeout)
    {
        const BOOL ok = g_Gqcs ? g_Gqcs(port, bytes, key, overlapped, timeout) : FALSE;
        if (overlapped && *overlapped)
        {
            PendingIo io;
            if (TakePending(*overlapped, io, true) && ok && bytes && !io.capturedImmediate) CapturePending(io, *bytes);
        }
        return ok;
    }

    struct HookSpec { const char* name; WORD ordinal; FARPROC replacement; FARPROC* previous; };

    int PatchImports(HMODULE module, const char* moduleLabel, const char* dllName, HookSpec* specs, size_t count)
    {
        if (!module) return 0;
        auto* base = reinterpret_cast<uint8_t*>(module);
        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE) return 0;
        const auto& dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
        if (!dir.VirtualAddress) return 0;
        auto* desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + dir.VirtualAddress);
        for (; desc->Name; ++desc)
        {
            const char* importedDll = reinterpret_cast<const char*>(base + desc->Name);
            if (_stricmp(importedDll, dllName) != 0) continue;
            if (!desc->OriginalFirstThunk)
            {
                LogShimA(LogLevel::Warn, "bzrnet", "[BZRNetTrace] %s %s lacks OriginalFirstThunk; observational hook skipped", moduleLabel, dllName);
                return 0;
            }
            auto* original = reinterpret_cast<IMAGE_THUNK_DATA*>(base + desc->OriginalFirstThunk);
            auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + desc->FirstThunk);
            int patched = 0;
            for (size_t specIndex = 0; specIndex < count; ++specIndex)
            {
                auto* o = original;
                auto* t = thunk;
                for (; t->u1.Function; ++t, ++o)
                {
                    bool match = false;
                    if (IMAGE_SNAP_BY_ORDINAL(o->u1.Ordinal))
                        match = specs[specIndex].ordinal && IMAGE_ORDINAL(o->u1.Ordinal) == specs[specIndex].ordinal;
                    else
                    {
                        auto* import = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + o->u1.AddressOfData);
                        match = import && _stricmp(reinterpret_cast<const char*>(import->Name), specs[specIndex].name) == 0;
                    }
                    if (!match) continue;
                    const FARPROC prior = reinterpret_cast<FARPROC>(t->u1.Function);
                    if (prior == specs[specIndex].replacement) break;
                    DWORD oldProtect = 0;
                    if (!VirtualProtect(&t->u1.Function, sizeof(t->u1.Function), PAGE_READWRITE, &oldProtect)) break;
                    t->u1.Function = reinterpret_cast<ULONG_PTR>(specs[specIndex].replacement);
                    DWORD ignored = 0;
                    VirtualProtect(&t->u1.Function, sizeof(t->u1.Function), oldProtect, &ignored);
                    FlushInstructionCache(GetCurrentProcess(), &t->u1.Function, sizeof(t->u1.Function));
                    if (specs[specIndex].previous && !*specs[specIndex].previous) *specs[specIndex].previous = prior;
                    ++patched;
                    break;
                }
            }
            if (patched) LogShimA(LogLevel::Info, "bzrnet", "[BZRNetTrace] %s %s observational hooks installed=%d", moduleLabel, dllName, patched);
            return patched;
        }
        return 0;
    }

    void InstallFor(HMODULE module, const char* label)
    {
        HookSpec winsock[] = {
            {"closesocket", 3, reinterpret_cast<FARPROC>(HookCloseSocket), reinterpret_cast<FARPROC*>(&g_CloseSocket)},
            {"send", 19, reinterpret_cast<FARPROC>(HookSend), reinterpret_cast<FARPROC*>(&g_Send)},
            {"recv", 16, reinterpret_cast<FARPROC>(HookRecv), reinterpret_cast<FARPROC*>(&g_Recv)},
            {"sendto", 20, reinterpret_cast<FARPROC>(HookSendTo), reinterpret_cast<FARPROC*>(&g_SendTo)},
            {"recvfrom", 17, reinterpret_cast<FARPROC>(HookRecvFrom), reinterpret_cast<FARPROC*>(&g_RecvFrom)},
            {"WSASend", 0, reinterpret_cast<FARPROC>(HookWSASend), reinterpret_cast<FARPROC*>(&g_WSASend)},
            {"WSARecv", 0, reinterpret_cast<FARPROC>(HookWSARecv), reinterpret_cast<FARPROC*>(&g_WSARecv)},
            {"WSASendTo", 0, reinterpret_cast<FARPROC>(HookWSASendTo), reinterpret_cast<FARPROC*>(&g_WSASendTo)},
            {"WSARecvFrom", 0, reinterpret_cast<FARPROC>(HookWSARecvFrom), reinterpret_cast<FARPROC*>(&g_WSARecvFrom)},
        };
        PatchImports(module, label, "ws2_32.dll", winsock, std::size(winsock));
        HookSpec kernel[] = {{"GetQueuedCompletionStatus", 0, reinterpret_cast<FARPROC>(HookGqcs), reinterpret_cast<FARPROC*>(&g_Gqcs)}};
        PatchImports(module, label, "kernel32.dll", kernel, std::size(kernel));
    }

    BOOL CALLBACK InitializeOnce(PINIT_ONCE, PVOID, PVOID*)
    {
        g_Config = LoadConfig();
        if (!g_Config.enabled) return TRUE;
        BzrNetTraceConfig trace;
        trace.enabled = true;
        trace.privateForensic = g_Config.privateForensic;
        trace.queueCapacity = g_Config.queueRecords;
        if (!InitializeBzrNetTrace(trace)) return TRUE;

        // net_optimizer runs first. Capturing the current IAT target here means
        // every hook chains through the optimizer (or the original Winsock
        // export) exactly once; this layer only observes the buffers/results.
        InstallFor(GetModuleHandleA(nullptr), "battlezone98redux.exe");
        InstallFor(GetModuleHandleA("Galaxy.dll"), "Galaxy.dll");
        InstallFor(GetModuleHandleA("GalaxyPeer.dll"), "GalaxyPeer.dll");
        InstallFor(GetModuleHandleA("steam_api.dll"), "steam_api.dll");
        InterlockedExchange(&g_Shutdown, 0);
        EmitBzrNetTrace("config", "BZR_TRACE_READY", "internal", 0, 0, "",
            std::string("{\"privateForensic\":") + (g_Config.privateForensic ? "true" : "false") +
            ",\"allUdp\":" + (g_Config.allUdp ? "true" : "false") + ",\"queueRecords\":" + std::to_string(g_Config.queueRecords) + '}');
        return TRUE;
    }
}

void InitializeBzrNetInstrumentation()
{
    InitOnceExecuteOnce(&g_InitOnce, InitializeOnce, nullptr, nullptr);
}

void ShutdownBzrNetInstrumentation()
{
    if (InterlockedExchange(&g_Shutdown, 1) != 0) return;
    AcquireSRWLockExclusive(&g_PendingLock); g_Pending.clear(); ReleaseSRWLockExclusive(&g_PendingLock);
    AcquireSRWLockExclusive(&g_WsLock); g_Ws.clear(); ReleaseSRWLockExclusive(&g_WsLock);
    AcquireSRWLockExclusive(&g_SocketLock); g_Sockets.clear(); ReleaseSRWLockExclusive(&g_SocketLock);
    ShutdownBzrNetTrace();
}
}
