#include "net_optimizer.h"
#include "netcode_hooks.h"
#include "shim_log.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
namespace
{
    constexpr DWORD kSioUdpConnReset = _WSAIOW(IOC_VENDOR, 12);
    constexpr uint32_t kDefaultPacketLogLimit = 16;
    constexpr uint32_t kDefaultPacketLogInterval = 128;
    constexpr uint32_t kDefaultReorderWindowMs = 100;
    constexpr uint32_t kDefaultReorderMinWindowMs = 5;
    constexpr uint32_t kMinReorderWindowMs = 5;
    constexpr uint32_t kMaxReorderWindowMs = 200;
    constexpr uint32_t kReorderGrowPadMs = 5;
    constexpr uint32_t kReorderDecayMs = 2000;
    constexpr uint32_t kReorderDecayStepMs = 5;
    constexpr uint32_t kDefaultReorderDepth = 8;
    constexpr uint32_t kMinReorderDepth = 1;
    constexpr uint32_t kDefaultReorderPeers = 32;
    constexpr uint32_t kMinReorderPeers = 1;
    constexpr uint32_t kDefaultReorderDrainCap = 32;
    constexpr uint32_t kMinReorderDrainCap = 1;
    constexpr uint32_t kMaxReorderDrainCap = 128;
    constexpr uint32_t kReorderSeqOffset = 13;
    constexpr uint32_t kReorderSeqMinPayloadBytes = 17;
    constexpr uint32_t kReorderSlotCount = 8;
    constexpr uint32_t kReorderMaxPeers = 32;
    constexpr uint32_t kReorderMaxPacketBytes = 1500;
    constexpr uint32_t kBufferLogMagic = 0x474C5A42u; // 'BZLG'
    constexpr uint32_t kBufferLogVersion = 2;
    constexpr uint32_t kDefaultBufferLogPayloadBytes = 32;
    constexpr uint32_t kMinBufferLogPayloadBytes = 8;
    constexpr uint32_t kMaxBufferLogPayloadBytes = 2048;
    constexpr uint32_t kRelayCapturePayloadBytes = 2048;
    constexpr uint32_t kRelayCaptureRingRecords = 32768;
    constexpr uint32_t kRelayCaptureMaxWebSocketBytes = 1024 * 1024;
    constexpr uint32_t kDefaultBufferLogRingRecords = 65536;
    constexpr uint32_t kMinBufferLogRingRecords = 1024;
    constexpr uint32_t kMaxBufferLogRingRecords = 1000000;
    constexpr const char* kBufferLogBinName = "bz_buffer_log.bin";
    constexpr const char* kBufferLogMetaName = "bz_buffer_log.meta.txt";
    constexpr const char* kRelayControlLogName = "bz_relay_control.jsonl";
    constexpr uint16_t kBzrNetWebSocketPort = 1337;
    constexpr uint16_t kBzrNetProbePort = 1338;
    constexpr uint16_t kBzrNetRelayPort = 1339;
    constexpr const char* kBzrNetMatchmakingHost = "battlezone98mp.webdev.rebellion.co.uk";
    constexpr uint32_t kDefaultDscp = 46;
    constexpr uint32_t kDupQueueSlots = 128;
    constexpr uint32_t kDupTickMs = 5;
    constexpr uint32_t kDefaultDupDelayMs = 25;
    constexpr uint32_t kDefaultDupMaxPps = 40;
    constexpr uint32_t kReorderWakeTickMs = 10;
    constexpr uint32_t kReorderWakeIdleMs = 10;
    constexpr uint32_t kReorderWakeBurstCap = 8;
    constexpr uint8_t kWakeMagic[8] = { 'B', 'Z', 'W', 'K', 'P', 'K', 'T', '1' };
    // A window carrying more than this many datagrams counts as a burst second.
    // The game's steady outbound rate is roughly 30 packets/sec, so 100 is well
    // clear of normal play and still catches the onset of a retransmit storm.
    constexpr uint32_t kBurstThresholdPps = 100;
    constexpr uint64_t kBurstReportMs = 30000;
    constexpr DWORD kGovPollMs = 100;
    constexpr DWORD kGovObservationLogMs = 10000;
    constexpr uint32_t kGovColdStart = 4000;
    constexpr uint32_t kGovStartMax = 200000;
    constexpr uint32_t kAutokickMsMax = 600000;
    constexpr uint32_t kAutokickPingMax = 60000;
    constexpr uint32_t kAutokickLossMax = 100000;
    static uint32_t* const kGovRateAddr = reinterpret_cast<uint32_t*>(0x008e8d14);
    constexpr uint8_t kGovSig[15] =
    {
        0x68, 0xA0, 0x0F, 0x00, 0x00,
        0x68, 0xE8, 0x03, 0x00, 0x00,
        0x68, 0x48, 0xF4, 0xFF, 0xFF,
    };

    // The 2026-08-12 xxMonke1.bzn match disproved the assumption the cold-start
    // watcher was built on. The comment justifying "a read of exactly 4000 is a
    // match start" claimed the ramp moves off 4000 immediately and never returns
    // to it exactly. It does return: four runaway repair-kit objects flooded the
    // reliable channel, ping went past MaxPing, and the governor took 54
    // consecutive DownCount steps over 107 seconds -- 25,900 -> 4,150 -> the
    // floor -- with no up-step in between. Thirteen minutes into the match the
    // governor walked DOWN onto the sentinel and the watcher read it as a match
    // start, jumping the rate 10x mid-fight with nobody asking.
    //
    // So classify the sentinel by how it was ARRIVED AT. A match start writes
    // 4000 over a value that has been sitting still (the lobby's, or the previous
    // match's parting rate, held for as long as the lobby lasted). A collapse
    // arrives from just above 4000, off a value that itself lasted one governor
    // step. A sentinel read reached from within kGovDescentBand bytes above it,
    // off a value held for less than kGovDescentMs, is a floor rescue: we still
    // write the target, because the alternative is a match that spends the rest
    // of its life at 4 kB/s, but it is named and counted apart from real match
    // starts so a sample set stays scoreable.
    //
    // Note it is the PREVIOUS value's lifetime that decides, not the age of the
    // change into the sentinel. That change is always "just now" whichever thing
    // happened, so its own age tells you nothing.
    //
    // The widest single step the governor can be seen to take between two 100 ms
    // polls: the collapse above stepped 400 B/s every 2 s at DownCount=200, so
    // 2000 is an order of magnitude of headroom and still less than half the
    // sentinel. A match start writes 4000 over a value nowhere near this close.
    constexpr uint32_t kGovDescentBand = 2000;
    // A collapse steps every couple of seconds; a lobby sits unchanged for
    // minutes. Doubles as the rescue cooldown so a governor parked on the floor
    // reports once rather than ten times a second.
    constexpr uint32_t kGovDescentMs = 30000;

    // ---- The game's [Net] tunables, written directly in .data ---------------
    //
    // Battlezone reads its whole [Net] block out of net.ini at match start into
    // a set of fixed .data globals. That path is not reliable: BZLogger reports
    // `MOD FOUND net.ini` while the values in the file are demonstrably not
    // applied, because only the session's active mod is parsed. Shipping tuning
    // through net.ini therefore does not work, and a copy in the game folder
    // root is ignored outright.
    //
    // So write the globals. This is the same DRM-safe mechanism the governor
    // cold-start fix uses and for the same reason: rewriting .text applies
    // cleanly and then trips SteamStub's code-integrity check about twelve
    // seconds later, while .data carries no integrity check. Aligned 32-bit
    // stores are atomic on x86. The session parser rewrites these at every match
    // start, so the poll loop re-asserts: within one tick of any match starting,
    // our value wins over both net.ini and the stock default.
    //
    // Addresses are only trusted after the unique 15-byte governor signature has
    // confirmed the build, and each entry is additionally sanity-gated on first
    // contact: if the value the game currently holds is outside a plausible
    // range, the address is not what we think it is for this build and the entry
    // is vetoed permanently rather than written blind.
    //
    // Ranges credit the PiercingXX/battlezone-netcode-patch field measurements;
    // the `stock` column there is phase-dependent (menu reads differ from
    // in-match reads for MinBandwidth, MaxBandwidth, MaxPing and the auto-kick
    // trio), so each range is wide enough to admit every value the entry has
    // legitimately been observed holding and narrow enough to reject a pointer,
    // a zero, or garbage.
    struct NetGlobalDef
    {
        uintptr_t address;
        const char* name;
        uint32_t plausibleMin;
        uint32_t plausibleMax;
    };

    constexpr NetGlobalDef kNetGlobals[] =
    {
        { 0x008e8cf4, "MinBandwidth",  500,  100000 },
        { 0x008e8d08, "MaxBandwidth", 1000, 4000000 },
        { 0x008e8cf0, "UpCount",         1,  100000 },
        { 0x008e8d10, "DownCount",       1,  100000 },
        { 0x008e8cec, "MaxPing",        50,   60000 },
        { 0x008e8cfc, "MaxPingsLost",    1,  100000 },
        { 0x008e8d0c, "AutoKickStart", 1000,  600000 },
        { 0x008e8cf8, "AutoKickPing",    50,   60000 },
        { 0x008e8bfc, "AutoKickLoss",     1,  100000 },
        { 0x008e8ce4, "AutoKickTime", 1000,  600000 },
    };

    enum NetGlobalIndex : size_t
    {
        kNgMinBandwidth = 0,
        kNgMaxBandwidth,
        kNgUpCount,
        kNgDownCount,
        kNgMaxPing,
        kNgMaxPingsLost,
        kNgAutoKickStart,
        kNgAutoKickPing,
        kNgAutoKickLoss,
        kNgAutoKickTime,
        kNgCount,
    };

    static_assert(std::size(kNetGlobals) == kNgCount, "net global table/index drift");

    enum BufferLogEventType : uint32_t
    {
        kBufferLogEventRecvFrom = 1,
        kBufferLogEventWSARecvFrom = 2,
        kBufferLogEventIoctlSocket = 3,
        kBufferLogEventWSAIoctl = 4,
        kBufferLogEventSendTo = 5,
        kBufferLogEventWSASendTo = 6,
        kBufferLogEventWSARecvCompletion = 7,
        kBufferLogEventWSARecvFromCompletion = 8,
    };

#pragma pack(push, 1)
    struct BufferLogRecordHeader
    {
        uint32_t magic = kBufferLogMagic;
        uint32_t version = kBufferLogVersion;
        uint32_t eventType = 0;
        uint32_t socketId = 0;
        uint64_t tickMs = 0;
        uint32_t sequence = 0;
        uint32_t requestedLength = 0;
        uint32_t transferredLength = 0;
        uint32_t wsaError = 0;
        uint32_t srcIpv4 = 0;
        uint16_t srcPort = 0;
        uint16_t flags = 0;
        uint16_t payloadLength = 0;
        uint16_t reserved = 0;
    };
#pragma pack(pop)

    struct NetConfig
    {
        bool enabled = true;
        bool logging = true;
        bool tcpNoDelay = true;
        bool keepAlive = true;
        bool disableUdpConnReset = true;
        bool logSocketErrors = true;
        bool logSocketLifecycle = true;
        bool logSocketPackets = true;
        bool logSockOptCalls = true;
        bool logPacketReorder = true;
        bool applySocketBuffers = true;
        bool enablePacketReorder = false;
        bool adaptivePacketReorder = true;
        bool enableReorderWake = true;
        bool enableBufferLog = false;
        bool enableRelayCapture = false;
        bool relayLogAllControl = false;
        bool relayLogDatagrams = false;
        bool sendDup = false;
        bool govScan = false;
        uint32_t sendBufferSize = DEFAULT_SEND_BUFFER;
        uint32_t recvBufferSize = DEFAULT_RECV_BUFFER;
        uint32_t dscp = kDefaultDscp;
        uint32_t dupDelayMs = kDefaultDupDelayMs;
        uint32_t dupMaxPps = kDefaultDupMaxPps;
        uint32_t govStart = 0;
        uint32_t autoKickStart = 60000;
        uint32_t autoKickPing = 2000;
        uint32_t autoKickLoss = 200;
        uint32_t autoKickTime = 60000;
        uint32_t netMinBandwidth = 16000;
        uint32_t netMaxBandwidth = 320000;
        uint32_t netUpCount = 100;
        uint32_t netDownCount = 50;
        uint32_t netMaxPing = 450;
        uint32_t netMaxPingsLost = 0;
        uint32_t packetLogLimit = kDefaultPacketLogLimit;
        uint32_t packetLogInterval = kDefaultPacketLogInterval;
        uint32_t reorderWindowMs = kDefaultReorderWindowMs;
        uint32_t reorderMinWindowMs = kDefaultReorderMinWindowMs;
        uint32_t reorderDepth = kDefaultReorderDepth;
        uint32_t reorderPeers = kDefaultReorderPeers;
        uint32_t reorderDrainCap = kDefaultReorderDrainCap;
        uint32_t bufferLogPayloadBytes = kDefaultBufferLogPayloadBytes;
        uint32_t bufferLogRingRecords = kDefaultBufferLogRingRecords;
        uint32_t bufferLogSocketId = 0;
        uint32_t bufferLogPeerIpv4 = 0;
        uint16_t bufferLogPeerPort = 0;
        bool bufferLogSocketFilterEnabled = false;
        bool bufferLogPeerFilterEnabled = false;
        std::string bufferLogPeerText;
        std::string matchmakingRedirectAddress;
    };

    struct SocketState
    {
        uint32_t socketId = 0;
        int af = AF_UNSPEC;
        int type = 0;
        int protocol = 0;
        bool optimized = false;
        std::string localAddress;
        std::string remoteAddress;
        uint64_t bytesSent = 0;
        uint64_t bytesRecv = 0;
        uint32_t packetsSent = 0;
        uint32_t packetsRecv = 0;
        int lastSendError = 0;
        int lastRecvError = 0;
        int lastSendToError = 0;
        int lastRecvFromError = 0;
        std::string lastRouteKey;
    };

    using SocketFn = SOCKET (WSAAPI*)(int, int, int);
    using WSASocketWFn = SOCKET (WSAAPI*)(int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);
    using WSASendFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSASendToFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const sockaddr*, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSARecvFromFn = int (WSAAPI*)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, sockaddr*, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using WSAIoctlFn = int (WSAAPI*)(SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
    using SendFn = int (WSAAPI*)(SOCKET, const char*, int, int);
    using RecvFn = int (WSAAPI*)(SOCKET, char*, int, int);
    using SendToFn = int (WSAAPI*)(SOCKET, const char*, int, int, const sockaddr*, int);
    using RecvFromFn = int (WSAAPI*)(SOCKET, char*, int, int, sockaddr*, int*);
    using IoctlSocketFn = int (WSAAPI*)(SOCKET, long, u_long*);
    using BindFn = int (WSAAPI*)(SOCKET, const sockaddr*, int);
    using ConnectFn = int (WSAAPI*)(SOCKET, const sockaddr*, int);
    using WSAConnectFn = int (WSAAPI*)(SOCKET, const sockaddr*, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS);
    using CloseSocketFn = int (WSAAPI*)(SOCKET);
    using SetSockOptFn = int (WSAAPI*)(SOCKET, int, int, const char*, int);
    using GetSockOptFn = int (WSAAPI*)(SOCKET, int, int, char*, int*);
    using GetSockNameFn = int (WSAAPI*)(SOCKET, sockaddr*, int*);
    using GetPeerNameFn = int (WSAAPI*)(SOCKET, sockaddr*, int*);
    using WSAGetLastErrorFn = int (WSAAPI*)();
    using WSASetLastErrorFn = void (WSAAPI*)(int);
    using GetAddrInfoAFn = INT (WSAAPI*)(PCSTR, PCSTR, const ADDRINFOA*, PADDRINFOA*);
    using GetQueuedCompletionStatusFn = BOOL (WINAPI*)(HANDLE, LPDWORD, PULONG_PTR, LPOVERLAPPED*, DWORD);

    NetConfig g_Config;
    std::string g_NetIniPath;
    INIT_ONCE g_NetworkInitOnce = INIT_ONCE_STATIC_INIT;

    SRWLOCK g_SocketLock = SRWLOCK_INIT;
    std::unordered_map<SOCKET, SocketState> g_Sockets;
    volatile LONG g_NextSocketId = 0;

    HMODULE g_Ws2Module = nullptr;
    SocketFn g_RealSocket = nullptr;
    SocketFn g_DispatchSocket = nullptr;
    WSASocketWFn g_RealWSASocketW = nullptr;
    WSASocketWFn g_DispatchWSASocketW = nullptr;
    WSASendFn g_RealWSASend = nullptr;
    WSARecvFn g_RealWSARecv = nullptr;
    WSASendToFn g_RealWSASendTo = nullptr;
    WSARecvFromFn g_RealWSARecvFrom = nullptr;
    WSAIoctlFn g_RealWSAIoctl = nullptr;
    SendFn g_RealSend = nullptr;
    RecvFn g_RealRecv = nullptr;
    SendToFn g_RealSendTo = nullptr;
    RecvFromFn g_RealRecvFrom = nullptr;
    IoctlSocketFn g_RealIoctlSocket = nullptr;
    BindFn g_RealBind = nullptr;
    ConnectFn g_RealConnect = nullptr;
    WSAConnectFn g_RealWSAConnect = nullptr;
    CloseSocketFn g_RealCloseSocket = nullptr;
    SetSockOptFn g_RealSetSockOpt = nullptr;
    GetSockOptFn g_RealGetSockOpt = nullptr;
    GetSockNameFn g_RealGetSockName = nullptr;
    GetPeerNameFn g_RealGetPeerName = nullptr;
    WSAGetLastErrorFn g_RealWSAGetLastError = nullptr;
    WSASetLastErrorFn g_RealWSASetLastError = nullptr;
    GetAddrInfoAFn g_RealGetAddrInfoA = nullptr;
    GetQueuedCompletionStatusFn g_RealGetQueuedCompletionStatus = nullptr;

    enum class PendingIoKind : uint8_t
    {
        WSARecv,
        WSARecvFrom,
    };

    struct PendingCaptureIo
    {
        PendingIoKind kind = PendingIoKind::WSARecv;
        SOCKET socket = INVALID_SOCKET;
        std::vector<WSABUF> buffers;
        sockaddr* from = nullptr;
        LPINT fromLen = nullptr;
        LPWSAOVERLAPPED_COMPLETION_ROUTINE originalCompletionRoutine = nullptr;
        uint32_t requestedLength = 0;
        bool capturedImmediate = false;
    };

    struct WebSocketDirectionState
    {
        bool handshakeComplete = false;
        uint8_t fragmentedOpcode = 0;
        std::vector<uint8_t> pending;
        std::vector<uint8_t> fragmented;
    };

    struct WebSocketCaptureState
    {
        WebSocketDirectionState outbound;
        WebSocketDirectionState inbound;
    };

    struct ReorderSlot
    {
        uint64_t timestampMs = 0;
        uint32_t sequence = 0;
        uint32_t length = 0;
        uint32_t used = 0;
        uint32_t reserved = 0;
        sockaddr_in from = {};
        uint8_t data[kReorderMaxPacketBytes] = {};
    };

    struct PeerBuf
    {
        SOCKET socket = INVALID_SOCKET;
        uint64_t peerKey = 0;
        uint32_t seqInitialized = 0;
        uint32_t lastSequence = 0;
        uint32_t filled = 0;
        uint32_t windowMs = kDefaultReorderMinWindowMs;
        uint64_t lastAdjustMs = 0;
        ReorderSlot slots[kReorderSlotCount] = {};
    };

    struct DupEntry
    {
        SOCKET socket = INVALID_SOCKET;
        uint64_t dueMs = 0;
        int toLen = 0;
        uint32_t length = 0;
        sockaddr_storage to = {};
        uint8_t data[kReorderMaxPacketBytes] = {};
    };

    SRWLOCK g_ReorderLock = SRWLOCK_INIT;
    PeerBuf g_ReorderPeers[kReorderMaxPeers] = {};
    volatile LONG g_WakeStop = 0;
    HANDLE g_WakeThread = nullptr;
    SOCKET g_WakeSender = INVALID_SOCKET;
    SOCKET g_ReorderSocket = INVALID_SOCKET;
    uint64_t g_LastRecvCallMs = 0;
    bool g_WakeLogged = false;

    SRWLOCK g_DupLock = SRWLOCK_INIT;
    DupEntry g_DupQueue[kDupQueueSlots] = {};
    uint32_t g_DupHead = 0;
    uint32_t g_DupCount = 0;
    volatile LONG g_DupStop = 0;
    HANDLE g_DupThread = nullptr;
    uint64_t g_DupBucketStartMs = 0;
    uint32_t g_DupBucketSent = 0;

    volatile LONG g_GovStop = 0;
    HANDLE g_GovScanThread = nullptr;
    HANDLE g_GovPatchThread = nullptr;
    volatile LONG g_GovLastObserved = 0;
    volatile LONG g_GovObservationValid = 0;
    volatile LONG g_GovBumps = 0;
    volatile LONG g_AutoKickStop = 0;
    HANDLE g_AutoKickThread = nullptr;

    // Outbound burst measurement. The failure that actually ends matches is not
    // receive-side reordering: it is a peer's reliable-send queue backing up and
    // then burst-retransmitting. One measured case pushed 1,179 datagrams
    // carrying a single reliable message in 13.4 seconds and drowned the ping
    // exchange badly enough that the host's auto-kick fired ten seconds after
    // the flood ended. Receive-side buffering cannot help with that, and until
    // the local machine measures its own outbound behaviour there is no evidence
    // about whether it produces these floods at all. So this measures and does
    // not act: a one-second window, its peaks, and how many windows ran above
    // the burst threshold. Session peaks separate a healthy evening (175-442
    // packets/sec, 3-10 burst seconds) from a storm (1,646-4,186 packets/sec,
    // 283-1,914 burst seconds) at a glance.
    SRWLOCK g_BurstLock = SRWLOCK_INIT;
    uint64_t g_BurstWindowStartMs = 0;
    uint32_t g_BurstWindowPackets = 0;
    uint32_t g_BurstWindowBytes = 0;
    uint32_t g_BurstPeakPps = 0;
    uint32_t g_BurstPeakBps = 0;
    uint64_t g_BurstSeconds = 0;
    uint64_t g_BurstTotalPackets = 0;
    uint64_t g_BurstTotalBytes = 0;
    uint64_t g_BurstLastReportMs = 0;

    SRWLOCK g_BufferLogLock = SRWLOCK_INIT;
    uint8_t* g_BufferLogRing = nullptr;
    uint32_t g_BufferLogStride = 0;
    uint32_t g_BufferLogHead = 0;
    uint32_t g_BufferLogCount = 0;
    uint32_t g_BufferLogSequence = 0;
    uint64_t g_BufferLogTotalEvents = 0;
    bool g_BufferLogInitialized = false;
    bool g_BufferLogEnabled = false;
    std::string g_BufferLogBinPath;
    std::string g_BufferLogMetaPath;
    SRWLOCK g_PendingCaptureLock = SRWLOCK_INIT;
    std::unordered_map<LPWSAOVERLAPPED, PendingCaptureIo> g_PendingCaptureIo;
    SRWLOCK g_WebSocketCaptureLock = SRWLOCK_INIT;
    std::unordered_map<SOCKET, WebSocketCaptureState> g_WebSocketCapture;
    SRWLOCK g_RelayControlLogLock = SRWLOCK_INIT;
    FILE* g_RelayControlLog = nullptr;
    std::string g_RelayControlLogPath;

    uint32_t GetSocketId(SOCKET s);
    bool TryGetSockaddrPort(const sockaddr* addr, int addrLen, uint16_t* outPort);
    bool TryGetSockaddrIpv4HostOrder(const sockaddr* addr, int addrLen, uint32_t* outIpv4);
    void HandleCompletedCaptureIo(LPWSAOVERLAPPED overlapped, DWORD transferredLength, DWORD completionError);
    uint32_t GetRequestedWsabufBytes(LPWSABUF buffers, DWORD bufferCount);
    void CaptureRecvPathEvent(
        BufferLogEventType eventType,
        SOCKET s,
        const sockaddr* from,
        uint16_t flags,
        uint32_t requestedLength,
        uint32_t transferredLength,
        uint32_t wsaError,
        const uint8_t* payload);

    void Logf(const char* fmt, ...)
    {
        if (!g_Config.logging)
            return;

        va_list args;
        va_start(args, fmt);
        LogShimVA(LogLevel::Info, "net", fmt, args);
        va_end(args);
    }

    void LogReorderf(const char* fmt, ...)
    {
        if (!g_Config.logging || !g_Config.logPacketReorder)
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

    bool TryReadEnvValue(const char* name, char* buffer, DWORD bufferSize)
    {
        if (!name || !*name || !buffer || bufferSize == 0)
            return false;

        const DWORD len = GetEnvironmentVariableA(name, buffer, bufferSize);
        return len > 0 && len < bufferSize;
    }

    bool EnvValueEnabled(const char* value)
    {
        if (!value || value[0] == '\0')
            return false;

        char lower[16] = {};
        size_t len = std::strlen(value);
        len = (std::min)(len, sizeof(lower) - 1);
        for (size_t i = 0; i < len; ++i)
            lower[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(value[i])));

        return std::strcmp(lower, "0") != 0 &&
            std::strcmp(lower, "false") != 0 &&
            std::strcmp(lower, "no") != 0 &&
            std::strcmp(lower, "off") != 0;
    }

    std::string TrimString(const std::string& value)
    {
        const char* whitespace = " \t\r\n";
        const size_t first = value.find_first_not_of(whitespace);
        if (first == std::string::npos)
            return {};

        const size_t last = value.find_last_not_of(whitespace);
        return value.substr(first, last - first + 1);
    }

    uint32_t ClampUint(uint32_t value, uint32_t minValue, uint32_t maxValue)
    {
        return (std::max)(minValue, (std::min)(value, maxValue));
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

    std::string ReadIniString(const char* section, const char* key)
    {
        if (g_NetIniPath.empty())
            return {};

        char buf[256] = {};
        GetPrivateProfileStringA(section, key, "", buf, static_cast<DWORD>(sizeof(buf)), g_NetIniPath.c_str());
        return TrimString(buf);
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

    uint32_t ClampReorderWindow(uint32_t value)
    {
        return (std::max)(kMinReorderWindowMs, (std::min)(value, kMaxReorderWindowMs));
    }

    uint32_t ClampReorderMinWindow(uint32_t value, uint32_t maxWindow)
    {
        return ClampUint(value, 0, maxWindow);
    }

    uint32_t ClampReorderDepth(uint32_t value)
    {
        return ClampUint(value, kMinReorderDepth, kReorderSlotCount);
    }

    uint32_t ClampReorderPeerCount(uint32_t value)
    {
        return ClampUint(value, kMinReorderPeers, kReorderMaxPeers);
    }

    uint32_t ClampReorderDrainCap(uint32_t value)
    {
        return ClampUint(value, kMinReorderDrainCap, kMaxReorderDrainCap);
    }

    uint32_t ClampBufferLogPayloadBytes(uint32_t value)
    {
        return ClampUint(value, kMinBufferLogPayloadBytes, kMaxBufferLogPayloadBytes);
    }

    uint32_t ClampBufferLogRingRecords(uint32_t value)
    {
        return ClampUint(value, kMinBufferLogRingRecords, kMaxBufferLogRingRecords);
    }

    bool ParseBufferLogPeerFilter(const std::string& text, uint32_t* outIpv4, uint16_t* outPort, std::string* outNormalized)
    {
        if (!outIpv4 || !outPort)
            return false;

        const std::string trimmed = TrimString(text);
        if (trimmed.empty())
            return false;

        std::string ipPart = trimmed;
        std::string portPart;
        const size_t colon = trimmed.rfind(':');
        if (colon != std::string::npos)
        {
            ipPart = TrimString(trimmed.substr(0, colon));
            portPart = TrimString(trimmed.substr(colon + 1));
        }

        if (ipPart.empty())
            return false;

        IN_ADDR addr4 = {};
        if (InetPtonA(AF_INET, ipPart.c_str(), &addr4) != 1)
            return false;

        uint16_t port = 0;
        if (!portPart.empty())
        {
            char* end = nullptr;
            const unsigned long parsedPort = std::strtoul(portPart.c_str(), &end, 10);
            if (!end || *end != '\0' || parsedPort > 65535ul)
                return false;
            port = static_cast<uint16_t>(parsedPort);
        }

        char normalized[64] = {};
        if (port != 0)
            _snprintf_s(normalized, _TRUNCATE, "%s:%u", ipPart.c_str(), static_cast<unsigned>(port));
        else
            _snprintf_s(normalized, _TRUNCATE, "%s", ipPart.c_str());

        *outIpv4 = ntohl(addr4.S_un.S_addr);
        *outPort = port;
        if (outNormalized)
            *outNormalized = normalized;
        return true;
    }

    bool LoadManifestProfile(const std::string& manifestPath, uint32_t& outSend, uint32_t& outRecv)
    {
        FILE* file = nullptr;
        fopen_s(&file, manifestPath.c_str(), "rb");
        if (!file)
            return false;

        if (fseek(file, 0, SEEK_END) != 0)
        {
            fclose(file);
            return false;
        }

        const long size = ftell(file);
        if (size <= 0 || size > 64 * 1024 || fseek(file, 0, SEEK_SET) != 0)
        {
            fclose(file);
            return false;
        }

        std::string buffer(static_cast<size_t>(size), '\0');
        const size_t bytesRead = fread(buffer.data(), 1, buffer.size(), file);
        fclose(file);
        buffer.resize(bytesRead);

        const char* profileStart = std::strstr(buffer.c_str(), "\"profile\"");
        if (!profileStart)
            return false;

        auto extractUint = [](const char* start, const char* key) -> uint32_t
        {
            const char* pos = std::strstr(start, key);
            if (!pos)
                return 0;

            pos += std::strlen(key);
            while (*pos && (*pos == ':' || *pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r' || *pos == '"'))
                ++pos;

            return static_cast<uint32_t>(std::strtoul(pos, nullptr, 10));
        };

        bool found = false;
        const uint32_t send = extractUint(profileStart, "\"send_buffer_bytes\"");
        const uint32_t recv = extractUint(profileStart, "\"receive_buffer_bytes\"");
        if (send > 0)
        {
            outSend = send;
            found = true;
        }
        if (recv > 0)
        {
            outRecv = recv;
            found = true;
        }
        return found;
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
        g_Config.logSocketLifecycle = ReadIniBool("OpenShimSocket", "LogSocketLifecycle", true);
        g_Config.logSocketPackets = ReadIniBool("OpenShimSocket", "LogSocketPackets", true);
        g_Config.logSockOptCalls = ReadIniBool("OpenShimSocket", "LogSockOptCalls", true);
        g_Config.logPacketReorder = ReadIniBool("OpenShimSocket", "LogPacketReorder", true);
        g_Config.applySocketBuffers = ReadIniBool("OpenShimSocket", "ApplySocketBuffers", true);
        g_Config.dscp = ClampUint(ReadIniUint("OpenShimSocket", "Dscp", kDefaultDscp), 0, 63);
        const uint32_t legacySocketBufferSize = ReadIniUint("OpenShimSocket", "SocketBufferSize", 0);
        g_Config.sendBufferSize = ReadIniUint(
            "OpenShimSocket",
            "SendBufferSize",
            legacySocketBufferSize ? legacySocketBufferSize : DEFAULT_SEND_BUFFER);
        g_Config.recvBufferSize = ReadIniUint(
            "OpenShimSocket",
            "ReceiveBufferSize",
            legacySocketBufferSize ? legacySocketBufferSize : DEFAULT_RECV_BUFFER);
        g_Config.sendBufferSize = std::max<uint32_t>(g_Config.sendBufferSize, 32 * 1024);
        g_Config.recvBufferSize = std::max<uint32_t>(g_Config.recvBufferSize, 32 * 1024);
        g_Config.packetLogLimit = std::max<uint32_t>(ReadIniUint("OpenShimSocket", "PacketLogLimit", kDefaultPacketLogLimit), 1);
        g_Config.packetLogInterval = ReadIniUint("OpenShimSocket", "PacketLogInterval", kDefaultPacketLogInterval);
        g_Config.enablePacketReorder = ReadIniBool("OpenShimSocket", "EnablePacketReorder", false);
        g_Config.reorderWindowMs = ClampReorderWindow(ReadIniUint("OpenShimSocket", "PacketReorderWindowMs", kDefaultReorderWindowMs));
        g_Config.reorderMinWindowMs = ClampReorderMinWindow(ReadIniUint("OpenShimSocket", "PacketReorderMinWindowMs", kDefaultReorderMinWindowMs), g_Config.reorderWindowMs);
        g_Config.adaptivePacketReorder = ReadIniBool("OpenShimSocket", "EnableAdaptivePacketReorder", true);
        g_Config.enableReorderWake = ReadIniBool("OpenShimSocket", "EnablePacketReorderWake", true);
        g_Config.reorderDepth = ClampReorderDepth(ReadIniUint("OpenShimSocket", "PacketReorderDepth", kDefaultReorderDepth));
        g_Config.reorderPeers = ClampReorderPeerCount(ReadIniUint("OpenShimSocket", "PacketReorderPeers", kDefaultReorderPeers));
        g_Config.reorderDrainCap = ClampReorderDrainCap(ReadIniUint("OpenShimSocket", "PacketReorderDrainCap", kDefaultReorderDrainCap));
        g_Config.sendDup = ReadIniBool("OpenShimSocket", "SendDup", false);
        g_Config.dupDelayMs = ClampUint(ReadIniUint("OpenShimSocket", "DupDelayMs", kDefaultDupDelayMs), 0, 500);
        g_Config.dupMaxPps = ClampUint(ReadIniUint("OpenShimSocket", "DupMaxPps", kDefaultDupMaxPps), 0, 2000);
        g_Config.govStart = ClampUint(ReadIniUint("OpenShimSocket", "GovernorStart", 0), 0, kGovStartMax);
        g_Config.govScan = ReadIniBool("OpenShimSocket", "GovernorScan", false);
        const bool autoKickRelax = ReadIniBool("OpenShimSocket", "AutoKickRelax", true);
        g_Config.autoKickStart = ClampUint(ReadIniUint("OpenShimSocket", "AutoKickStart", autoKickRelax ? 60000 : 0), 0, kAutokickMsMax);
        g_Config.autoKickPing = ClampUint(ReadIniUint("OpenShimSocket", "AutoKickPing", autoKickRelax ? 2000 : 0), 0, kAutokickPingMax);
        g_Config.autoKickLoss = ClampUint(ReadIniUint("OpenShimSocket", "AutoKickLoss", autoKickRelax ? 200 : 0), 0, kAutokickLossMax);
        g_Config.autoKickTime = ClampUint(ReadIniUint("OpenShimSocket", "AutoKickTime", autoKickRelax ? 60000 : 0), 0, kAutokickMsMax);

        // The governor/bandwidth half of the [Net] block, on the same "0 leaves
        // the game's own value alone" convention as the auto-kick keys above.
        //
        // MinBandwidth is the collapse floor. The 2026-08-12 session took 54
        // consecutive DownCount steps and bottomed out at 4,150 -> 4,000 B/s --
        // the stock floor, not net.ini's documented 16000, which is how we know
        // the file was not being applied. 16000 makes that collapse survivable
        // and, as a bonus, lifts the floor out of the cold-start sentinel's
        // reach, which is the structural fix for the misfire rather than the
        // defensive one.
        //
        // MaxBandwidth at 320000 effectively removes the cap. A lower "safe"
        // ceiling is a regression: sessions have been measured ramping to 79,600
        // B/s, and the 2026-08-15/16 storms sustained peaks of 86k-224k B/s. A
        // 64000 ceiling tried in the upstream V5.0 sat BELOW real traffic, so
        // the governor spent whole matches throttling against it. The governor
        // is closed-loop -- it only climbs while ping < MaxPing -- so a high
        // ceiling is not itself a risk.
        //
        // UpCount/DownCount at 100/50 restores stock's 2:1 up-bias while keeping
        // the 10x scale-up that is the point of tuning them. Measured at the old
        // 50/200 the governor fell -203 B/s per second and climbed +40.5: five
        // to one, so a two-minute collapse needed nine minutes to undo and in a
        // real fight it never recovered before the next spike.
        //
        // MaxPing 450 gives a jittery link headroom before the governor bites;
        // stock 300 turns a jitter spike into a rate cut into fewer state
        // updates into more warping, and the cut itself keeps ping high.
        //
        // MaxPingsLost is left alone by default: no evidence a change helps.
        const bool netTune = ReadIniBool("OpenShimSocket", "NetTune", true);
        g_Config.netMinBandwidth = ReadIniUint("OpenShimSocket", "NetMinBandwidth", netTune ? 16000 : 0);
        g_Config.netMaxBandwidth = ReadIniUint("OpenShimSocket", "NetMaxBandwidth", netTune ? 320000 : 0);
        g_Config.netUpCount = ReadIniUint("OpenShimSocket", "NetUpCount", netTune ? 100 : 0);
        g_Config.netDownCount = ReadIniUint("OpenShimSocket", "NetDownCount", netTune ? 50 : 0);
        g_Config.netMaxPing = ReadIniUint("OpenShimSocket", "NetMaxPing", netTune ? 450 : 0);
        g_Config.netMaxPingsLost = ReadIniUint("OpenShimSocket", "NetMaxPingsLost", 0);

        g_Config.enableBufferLog = ReadIniBool("OpenShimSocket", "EnableBufferLog", false);
        g_Config.enableRelayCapture = ReadIniBool("OpenShimSocket", "EnableRelayCapture", false);
        g_Config.relayLogAllControl = ReadIniBool("OpenShimSocket", "RelayLogAllControl", false);
        g_Config.relayLogDatagrams = ReadIniBool("OpenShimSocket", "RelayLogDatagrams", false);
        g_Config.bufferLogPayloadBytes = ClampBufferLogPayloadBytes(ReadIniUint("OpenShimSocket", "BufferLogPayloadBytes", kDefaultBufferLogPayloadBytes));
        g_Config.bufferLogRingRecords = ClampBufferLogRingRecords(ReadIniUint("OpenShimSocket", "BufferLogRingRecords", kDefaultBufferLogRingRecords));
        g_Config.bufferLogSocketId = ReadIniUint("OpenShimSocket", "BufferLogSocketId", 0);
        g_Config.bufferLogSocketFilterEnabled = g_Config.bufferLogSocketId != 0;
        g_Config.bufferLogPeerText = ReadIniString("OpenShimSocket", "BufferLogPeer");
        g_Config.matchmakingRedirectAddress = ReadIniString("OpenShimSocket", "MatchmakingRedirectAddress");
        if (!g_Config.bufferLogPeerText.empty())
        {
            std::string normalizedPeer;
            if (ParseBufferLogPeerFilter(g_Config.bufferLogPeerText, &g_Config.bufferLogPeerIpv4, &g_Config.bufferLogPeerPort, &normalizedPeer))
            {
                g_Config.bufferLogPeerFilterEnabled = true;
                g_Config.bufferLogPeerText = normalizedPeer;
            }
            else
            {
                g_Config.bufferLogPeerText.clear();
            }
        }

        char envValue[256] = {};
        if (TryReadEnvValue("BZ_MATCHMAKING_ADDRESS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_MATCHMAKING_ADDRESS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.matchmakingRedirectAddress = envValue;
        }

        if (g_Config.matchmakingRedirectAddress.find('/') != std::string::npos)
        {
            Logf("[OpenShimNet] Ignoring MatchmakingRedirectAddress containing a URL/path; use a hostname or IP only");
            g_Config.matchmakingRedirectAddress.clear();
        }

        if (!g_Config.matchmakingRedirectAddress.empty())
        {
            Logf("[OpenShimNet] BZRNet matchmaking DNS redirect enabled: %s -> %s",
                kBzrNetMatchmakingHost,
                g_Config.matchmakingRedirectAddress.c_str());
        }

        if (TryReadEnvValue("BZ_REORDER", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.enablePacketReorder = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_REORDER_WINDOW_MS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_WINDOW_MS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.reorderWindowMs = ClampReorderWindow(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
            g_Config.reorderMinWindowMs = ClampReorderMinWindow(g_Config.reorderMinWindowMs, g_Config.reorderWindowMs);
        }

        if (TryReadEnvValue("BZ_REORDER_MIN_MS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_MIN_MS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.reorderMinWindowMs = ClampReorderMinWindow(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), g_Config.reorderWindowMs);
        }

        if (TryReadEnvValue("BZ_REORDER_ADAPT", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_ADAPT", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.adaptivePacketReorder = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_REORDER_WAKE", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_WAKE", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.enableReorderWake = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_REORDER_DEPTH", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_DEPTH", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.reorderDepth = ClampReorderDepth(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
        }

        if (TryReadEnvValue("BZ_REORDER_PEERS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_PEERS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.reorderPeers = ClampReorderPeerCount(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
        }

        if (TryReadEnvValue("BZ_REORDER_DRAIN", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_REORDER_DRAIN", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.reorderDrainCap = ClampReorderDrainCap(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
        }

        if (TryReadEnvValue("BZ_BUFFER_LOG", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_BUFFER_LOG", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.enableBufferLog = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_DSCP", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_DSCP", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.dscp = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, 63);
        }

        if (TryReadEnvValue("BZ_SEND_DUP", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_SEND_DUP", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.sendDup = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_DUP_DELAY_MS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_DUP_DELAY_MS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.dupDelayMs = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, 500);
        }

        if (TryReadEnvValue("BZ_DUP_MAX_PPS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_DUP_MAX_PPS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.dupMaxPps = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, 2000);
        }

        if (TryReadEnvValue("BZ_GOV_SCAN", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_GOV_SCAN", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.govScan = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("BZ_GOV_START", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_GOV_START", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.govStart = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, kGovStartMax);
        }

        if (TryReadEnvValue("BZ_AUTOKICK_RELAX", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_AUTOKICK_RELAX", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            if (!EnvValueEnabled(envValue))
            {
                g_Config.autoKickStart = 0;
                g_Config.autoKickPing = 0;
                g_Config.autoKickLoss = 0;
                g_Config.autoKickTime = 0;
            }
        }

        if (TryReadEnvValue("BZ_AUTOKICK_START", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_AUTOKICK_START", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.autoKickStart = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, kAutokickMsMax);
        }

        if (TryReadEnvValue("BZ_AUTOKICK_PING", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_AUTOKICK_PING", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.autoKickPing = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, kAutokickPingMax);
        }

        if (TryReadEnvValue("BZ_AUTOKICK_LOSS", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_AUTOKICK_LOSS", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.autoKickLoss = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, kAutokickLossMax);
        }

        if (TryReadEnvValue("BZ_AUTOKICK_TIME", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_AUTOKICK_TIME", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.autoKickTime = ClampUint(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)), 0, kAutokickMsMax);
        }

        if (TryReadEnvValue("BZ_BUFFER_LOG_BYTES", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_BUFFER_LOG_BYTES", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.bufferLogPayloadBytes = ClampBufferLogPayloadBytes(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
        }

        if (TryReadEnvValue("BZ_BUFFER_LOG_RING", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_BUFFER_LOG_RING", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.bufferLogRingRecords = ClampBufferLogRingRecords(static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10)));
        }

        if (TryReadEnvValue("BZ_BUFFER_LOG_SOCKET", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_BUFFER_LOG_SOCKET", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.bufferLogSocketId = static_cast<uint32_t>(std::strtoul(envValue, nullptr, 10));
            g_Config.bufferLogSocketFilterEnabled = g_Config.bufferLogSocketId != 0;
        }

        if (TryReadEnvValue("BZ_BUFFER_LOG_PEER", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_BUFFER_LOG_PEER", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.bufferLogPeerFilterEnabled = false;
            g_Config.bufferLogPeerText.clear();
            g_Config.bufferLogPeerIpv4 = 0;
            g_Config.bufferLogPeerPort = 0;

            std::string normalizedPeer;
            if (ParseBufferLogPeerFilter(envValue, &g_Config.bufferLogPeerIpv4, &g_Config.bufferLogPeerPort, &normalizedPeer))
            {
                g_Config.bufferLogPeerFilterEnabled = true;
                g_Config.bufferLogPeerText = normalizedPeer;
            }
        }

        // openshim.ini [Diagnostics] RelayLogging maps onto OPENSHIM_RELAY_CAPTURE
        // through the friendly-key redirect in openshim_env_config.cpp, so the
        // one toggle a tester is told about reaches every part of this: the
        // relay-control JSONL, the WebSocket control-plane capture, and the raw
        // buffer ring the two are carried on.
        if (TryReadEnvValue("BZ_RELAY_CAPTURE", envValue, static_cast<DWORD>(sizeof(envValue))) ||
            TryReadEnvValue("OPENSHIM_RELAY_CAPTURE", envValue, static_cast<DWORD>(sizeof(envValue))))
        {
            g_Config.enableRelayCapture = EnvValueEnabled(envValue);
        }

        if (TryReadEnvValue("OPENSHIM_RELAY_LOG_ALL_CONTROL", envValue, static_cast<DWORD>(sizeof(envValue))))
            g_Config.relayLogAllControl = EnvValueEnabled(envValue);
        if (TryReadEnvValue("OPENSHIM_RELAY_LOG_DATAGRAMS", envValue, static_cast<DWORD>(sizeof(envValue))))
            g_Config.relayLogDatagrams = EnvValueEnabled(envValue);

        // Both detail switches imply the capture they add detail to: a tester who
        // sets one and not the master toggle would otherwise get silence.
        if (g_Config.relayLogAllControl || g_Config.relayLogDatagrams)
            g_Config.enableRelayCapture = true;

        if (g_Config.enableRelayCapture)
        {
            g_Config.enableBufferLog = true;
            g_Config.bufferLogPayloadBytes = kRelayCapturePayloadBytes;
            if (g_Config.bufferLogRingRecords == kDefaultBufferLogRingRecords)
                g_Config.bufferLogRingRecords = kRelayCaptureRingRecords;
            g_Config.bufferLogSocketFilterEnabled = false;
            g_Config.bufferLogPeerFilterEnabled = false;
            g_Config.bufferLogSocketId = 0;
            g_Config.bufferLogPeerText.clear();
        }

        const std::string manifestPath = JoinPath(GetGameDir(), "netcode_manifest.json");
        if (FileExists(manifestPath))
        {
            uint32_t manifestSend = DEFAULT_SEND_BUFFER;
            uint32_t manifestRecv = DEFAULT_RECV_BUFFER;
            if (LoadManifestProfile(manifestPath, manifestSend, manifestRecv))
            {
                // Keep manifest targets as runtime minimums so the optimizer and
                // startup hook stay aligned on the authoritative buffer values.
                g_Config.sendBufferSize = (std::max)(g_Config.sendBufferSize, manifestSend);
                g_Config.recvBufferSize = (std::max)(g_Config.recvBufferSize, manifestRecv);
            }
        }

        if (ReadIniString("OpenShimSocket", "BufferLogPeer").size() > 0 &&
            !g_Config.bufferLogPeerFilterEnabled &&
            g_Config.bufferLogPeerText.empty())
        {
            Logf("[OpenShimNet] buffer_log peer filter ignored: invalid BufferLogPeer value");
        }

        // State what relay logging is actually doing, always. "Relay logging was
        // on but produced nothing" and "relay logging was never on" look the same
        // in a bug report otherwise, and both have happened.
        Logf("[OpenShimNet] relay_logging: capture=%s allControl=%s datagrams=%s "
            "matchmakingRedirect=%s controlPorts=ws:%u,probe:%u,relay:%u",
            g_Config.enableRelayCapture ? "on" : "off",
            g_Config.relayLogAllControl ? "on" : "off",
            g_Config.relayLogDatagrams ? "on" : "off",
            g_Config.matchmakingRedirectAddress.empty() ? "<stock>" : g_Config.matchmakingRedirectAddress.c_str(),
            static_cast<unsigned>(kBzrNetWebSocketPort),
            static_cast<unsigned>(kBzrNetProbePort),
            static_cast<unsigned>(kBzrNetRelayPort));
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

        g_RealSocket = reinterpret_cast<SocketFn>(GetProcAddress(g_Ws2Module, "socket"));
        g_RealWSASocketW = reinterpret_cast<WSASocketWFn>(GetProcAddress(g_Ws2Module, "WSASocketW"));
        g_RealWSASend = reinterpret_cast<WSASendFn>(GetProcAddress(g_Ws2Module, "WSASend"));
        g_RealWSARecv = reinterpret_cast<WSARecvFn>(GetProcAddress(g_Ws2Module, "WSARecv"));
        g_RealWSASendTo = reinterpret_cast<WSASendToFn>(GetProcAddress(g_Ws2Module, "WSASendTo"));
        g_RealWSARecvFrom = reinterpret_cast<WSARecvFromFn>(GetProcAddress(g_Ws2Module, "WSARecvFrom"));
        g_RealWSAIoctl = reinterpret_cast<WSAIoctlFn>(GetProcAddress(g_Ws2Module, "WSAIoctl"));
        g_RealSend = reinterpret_cast<SendFn>(GetProcAddress(g_Ws2Module, "send"));
        g_RealRecv = reinterpret_cast<RecvFn>(GetProcAddress(g_Ws2Module, "recv"));
        g_RealSendTo = reinterpret_cast<SendToFn>(GetProcAddress(g_Ws2Module, "sendto"));
        g_RealRecvFrom = reinterpret_cast<RecvFromFn>(GetProcAddress(g_Ws2Module, "recvfrom"));
        g_RealIoctlSocket = reinterpret_cast<IoctlSocketFn>(GetProcAddress(g_Ws2Module, "ioctlsocket"));
        g_RealBind = reinterpret_cast<BindFn>(GetProcAddress(g_Ws2Module, "bind"));
        g_RealConnect = reinterpret_cast<ConnectFn>(GetProcAddress(g_Ws2Module, "connect"));
        g_RealWSAConnect = reinterpret_cast<WSAConnectFn>(GetProcAddress(g_Ws2Module, "WSAConnect"));
        g_RealCloseSocket = reinterpret_cast<CloseSocketFn>(GetProcAddress(g_Ws2Module, "closesocket"));
        g_RealSetSockOpt = reinterpret_cast<SetSockOptFn>(GetProcAddress(g_Ws2Module, "setsockopt"));
        g_RealGetSockOpt = reinterpret_cast<GetSockOptFn>(GetProcAddress(g_Ws2Module, "getsockopt"));
        g_RealGetSockName = reinterpret_cast<GetSockNameFn>(GetProcAddress(g_Ws2Module, "getsockname"));
        g_RealGetPeerName = reinterpret_cast<GetPeerNameFn>(GetProcAddress(g_Ws2Module, "getpeername"));
        g_RealWSAGetLastError = reinterpret_cast<WSAGetLastErrorFn>(GetProcAddress(g_Ws2Module, "WSAGetLastError"));
        g_RealWSASetLastError = reinterpret_cast<WSASetLastErrorFn>(GetProcAddress(g_Ws2Module, "WSASetLastError"));
        g_RealGetAddrInfoA = reinterpret_cast<GetAddrInfoAFn>(GetProcAddress(g_Ws2Module, "getaddrinfo"));
        HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
        if (kernel32)
        {
            g_RealGetQueuedCompletionStatus = reinterpret_cast<GetQueuedCompletionStatusFn>(
                GetProcAddress(kernel32, "GetQueuedCompletionStatus"));
        }

        const bool ok =
            g_RealSocket &&
            g_RealWSASocketW &&
            g_RealWSASend &&
            g_RealWSARecv &&
            g_RealWSASendTo &&
            g_RealWSARecvFrom &&
            g_RealWSAIoctl &&
            g_RealSend &&
            g_RealRecv &&
            g_RealSendTo &&
            g_RealRecvFrom &&
            g_RealIoctlSocket &&
            g_RealBind &&
            g_RealConnect &&
            g_RealWSAConnect &&
            g_RealCloseSocket &&
            g_RealSetSockOpt &&
            g_RealGetSockOpt &&
            g_RealGetSockName &&
            g_RealGetPeerName &&
            g_RealWSAGetLastError &&
            g_RealWSASetLastError &&
            g_RealGetAddrInfoA;

        if (!ok)
            LogShimA(LogLevel::Error, "net", "[OpenShimNet] Missing one or more required Winsock exports");
        if (g_Config.enableRelayCapture && !g_RealGetQueuedCompletionStatus)
            LogShimA(LogLevel::Error, "net", "[OpenShimNet] relay_capture cannot hook IOCP completions: GetQueuedCompletionStatus missing");

        g_DispatchSocket = g_RealSocket;
        g_DispatchWSASocketW = g_RealWSASocketW;

        return ok;
    }

    void InitializeRelayControlLog()
    {
        if (!g_Config.enableRelayCapture || g_RelayControlLog)
            return;

        g_RelayControlLogPath = GetGameLogPath(kRelayControlLogName);
        fopen_s(&g_RelayControlLog, g_RelayControlLogPath.c_str(), "wb");
        if (!g_RelayControlLog)
        {
            Logf("[OpenShimNet] relay_capture failed to open control log %s", g_RelayControlLogPath.c_str());
            return;
        }

        Logf("[OpenShimNet] relay_capture control log enabled path=%s", g_RelayControlLogPath.c_str());
    }

    void InitializeBufferLog()
    {
        if (g_BufferLogInitialized)
            return;

        g_BufferLogInitialized = true;
        if (!g_Config.enableBufferLog)
        {
            Logf("[OpenShimNet] buffer_log disabled");
            return;
        }

        g_BufferLogBinPath = GetGameLogPath(kBufferLogBinName);
        g_BufferLogMetaPath = GetGameLogPath(kBufferLogMetaName);
        g_BufferLogStride = static_cast<uint32_t>(sizeof(BufferLogRecordHeader) + g_Config.bufferLogPayloadBytes);

        const size_t totalBytes =
            static_cast<size_t>(g_BufferLogStride) * static_cast<size_t>(g_Config.bufferLogRingRecords);
        g_BufferLogRing = static_cast<uint8_t*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalBytes));
        if (!g_BufferLogRing)
        {
            Logf("[OpenShimNet] buffer_log allocation failed bytes=%llu",
                static_cast<unsigned long long>(totalBytes));
            return;
        }

        g_BufferLogEnabled = true;
        Logf("[OpenShimNet] buffer_log enabled payload=%u ring=%u stride=%u socketFilter=%u peerFilter=%s bin=%s",
            g_Config.bufferLogPayloadBytes,
            g_Config.bufferLogRingRecords,
            g_BufferLogStride,
            g_Config.bufferLogSocketFilterEnabled ? g_Config.bufferLogSocketId : 0,
            g_Config.bufferLogPeerFilterEnabled ? g_Config.bufferLogPeerText.c_str() : "<off>",
            g_BufferLogBinPath.c_str());
    }

    bool BufferLogPeerMatches(const sockaddr* source)
    {
        if (!g_Config.bufferLogPeerFilterEnabled)
            return true;

        uint32_t ipv4 = 0;
        uint16_t port = 0;
        if (!source ||
            !TryGetSockaddrIpv4HostOrder(source, static_cast<int>(sizeof(sockaddr_in)), &ipv4) ||
            !TryGetSockaddrPort(source, static_cast<int>(sizeof(sockaddr_in)), &port))
        {
            return false;
        }

        if (ipv4 != g_Config.bufferLogPeerIpv4)
            return false;

        return g_Config.bufferLogPeerPort == 0 || port == g_Config.bufferLogPeerPort;
    }

    bool ShouldCaptureBufferLogEvent(SOCKET s, const sockaddr* source)
    {
        if (g_Config.bufferLogSocketFilterEnabled && GetSocketId(s) != g_Config.bufferLogSocketId)
            return false;

        if (!BufferLogPeerMatches(source))
            return false;

        return true;
    }

    void BufferLogEvent(
        BufferLogEventType eventType,
        SOCKET s,
        const sockaddr* source,
        uint16_t flags,
        uint32_t requestedLength,
        uint32_t transferredLength,
        uint32_t wsaError,
        const uint8_t* payload,
        uint16_t payloadLength)
    {
        if (!g_BufferLogEnabled || !g_BufferLogRing)
            return;
        if (!ShouldCaptureBufferLogEvent(s, source))
            return;

        if (payloadLength > g_Config.bufferLogPayloadBytes)
            payloadLength = static_cast<uint16_t>(g_Config.bufferLogPayloadBytes);

        BufferLogRecordHeader record = {};
        record.eventType = static_cast<uint32_t>(eventType);
        record.socketId = GetSocketId(s);
        record.tickMs = GetTickCount64();

        AcquireSRWLockExclusive(&g_BufferLogLock);
        record.sequence = g_BufferLogSequence++;

        if (source && source->sa_family == AF_INET)
        {
            const auto* addr4 = reinterpret_cast<const sockaddr_in*>(source);
            record.srcIpv4 = static_cast<uint32_t>(addr4->sin_addr.S_un.S_addr);
            record.srcPort = ntohs(addr4->sin_port);
        }

        record.requestedLength = requestedLength;
        record.transferredLength = transferredLength;
        record.wsaError = wsaError;
        record.flags = flags;
        record.payloadLength = payloadLength;

        uint8_t* slot = g_BufferLogRing +
            (static_cast<size_t>(g_BufferLogHead) * static_cast<size_t>(g_BufferLogStride));
        std::memcpy(slot, &record, sizeof(record));

        uint8_t* payloadDst = slot + sizeof(record);
        if (payloadLength > 0 && payload)
            std::memcpy(payloadDst, payload, payloadLength);
        if (payloadLength < g_Config.bufferLogPayloadBytes)
            std::memset(payloadDst + payloadLength, 0, g_Config.bufferLogPayloadBytes - payloadLength);

        g_BufferLogHead = (g_BufferLogHead + 1) % g_Config.bufferLogRingRecords;
        if (g_BufferLogCount < g_Config.bufferLogRingRecords)
            ++g_BufferLogCount;
        ++g_BufferLogTotalEvents;

        ReleaseSRWLockExclusive(&g_BufferLogLock);
    }

    void FlushBufferLog()
    {
        if (!g_BufferLogEnabled || !g_BufferLogRing)
            return;

        FILE* binFile = nullptr;
        fopen_s(&binFile, g_BufferLogBinPath.c_str(), "wb");
        if (binFile)
        {
            AcquireSRWLockShared(&g_BufferLogLock);
            const uint32_t start =
                (g_BufferLogHead + g_Config.bufferLogRingRecords - g_BufferLogCount) % g_Config.bufferLogRingRecords;
            for (uint32_t i = 0; i < g_BufferLogCount; ++i)
            {
                const uint32_t index = (start + i) % g_Config.bufferLogRingRecords;
                const uint8_t* slot = g_BufferLogRing +
                    (static_cast<size_t>(index) * static_cast<size_t>(g_BufferLogStride));
                fwrite(slot, 1, g_BufferLogStride, binFile);
            }
            ReleaseSRWLockShared(&g_BufferLogLock);
            fclose(binFile);
        }
        else
        {
            Logf("[OpenShimNet] buffer_log failed to open %s for write", g_BufferLogBinPath.c_str());
        }

        FILE* metaFile = nullptr;
        fopen_s(&metaFile, g_BufferLogMetaPath.c_str(), "wb");
        if (metaFile)
        {
            std::fprintf(metaFile,
                "format=buffer_log_v2\r\nrecord_header_size=%u\r\npayload_bytes=%u\r\nrecord_stride=%u\r\nring_records=%u\r\nrecords_written=%u\r\ntotal_events_seen=%llu\r\nsocket_filter=%u\r\npeer_filter=%s\r\nrelay_capture=%u\r\nrelay_control_log=%s\r\nevent_types=1:recvfrom,2:WSARecvFrom,3:ioctlsocket,4:WSAIoctl,5:sendto,6:WSASendTo,7:WSARecv_completion,8:WSARecvFrom_completion\r\n",
                static_cast<unsigned>(sizeof(BufferLogRecordHeader)),
                static_cast<unsigned>(g_Config.bufferLogPayloadBytes),
                static_cast<unsigned>(g_BufferLogStride),
                static_cast<unsigned>(g_Config.bufferLogRingRecords),
                static_cast<unsigned>(g_BufferLogCount),
                static_cast<unsigned long long>(g_BufferLogTotalEvents),
                g_Config.bufferLogSocketFilterEnabled ? g_Config.bufferLogSocketId : 0,
                g_Config.bufferLogPeerFilterEnabled ? g_Config.bufferLogPeerText.c_str() : "<off>",
                g_Config.enableRelayCapture ? 1u : 0u,
                g_Config.enableRelayCapture ? g_RelayControlLogPath.c_str() : "<off>");
            fclose(metaFile);
        }
        else
        {
            Logf("[OpenShimNet] buffer_log failed to open %s for write", g_BufferLogMetaPath.c_str());
        }

        Logf("[OpenShimNet] buffer_log flushed records=%u totalEvents=%llu",
            g_BufferLogCount,
            static_cast<unsigned long long>(g_BufferLogTotalEvents));
    }

    template <typename T>
    void AdoptChainedImportTarget(const char* name, T candidate, T realProc, T& dispatchProc)
    {
        if (!candidate || candidate == realProc || candidate == dispatchProc)
            return;

        if (!dispatchProc || dispatchProc == realProc)
        {
            dispatchProc = candidate;
            Logf("[OpenShimNet] Preserving pre-existing %s import chain", name);
            return;
        }

        Logf("[OpenShimNet] Multiple pre-existing %s import targets detected; keeping first chained target", name);
    }

    void RememberPatchedImport(const char* name, FARPROC previousTarget)
    {
        if (!name || !previousTarget)
            return;

        if (std::strcmp(name, "socket") == 0)
        {
            AdoptChainedImportTarget("socket", reinterpret_cast<SocketFn>(previousTarget), g_RealSocket, g_DispatchSocket);
        }
        else if (std::strcmp(name, "WSASocketW") == 0)
        {
            AdoptChainedImportTarget("WSASocketW", reinterpret_cast<WSASocketWFn>(previousTarget), g_RealWSASocketW, g_DispatchWSASocketW);
        }
    }

    const char* SocketTypeLabel(int type, int protocol)
    {
        if (type == SOCK_DGRAM || protocol == IPPROTO_UDP)
            return "udp";
        if (type == SOCK_STREAM || protocol == IPPROTO_TCP)
            return "tcp";
        return "other";
    }

    std::string FormatSockaddr(const sockaddr* addr, int addrLen)
    {
        if (!addr || addrLen <= 0)
            return "";

        char host[INET6_ADDRSTRLEN] = {};
        uint16_t port = 0;
        if (addr->sa_family == AF_INET && addrLen >= static_cast<int>(sizeof(sockaddr_in)))
        {
            const auto* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
            InetNtopA(AF_INET, &addr4->sin_addr, host, static_cast<DWORD>(sizeof(host)));
            port = ntohs(addr4->sin_port);
        }
        else if (addr->sa_family == AF_INET6 && addrLen >= static_cast<int>(sizeof(sockaddr_in6)))
        {
            const auto* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
            InetNtopA(AF_INET6, &addr6->sin6_addr, host, static_cast<DWORD>(sizeof(host)));
            port = ntohs(addr6->sin6_port);
        }
        else
        {
            char buffer[64] = {};
            _snprintf_s(buffer, _TRUNCATE, "af=%d len=%d", static_cast<int>(addr->sa_family), addrLen);
            return buffer;
        }

        char buffer[128] = {};
        if (port != 0)
            _snprintf_s(buffer, _TRUNCATE, "%s:%u", host, static_cast<unsigned>(port));
        else
            _snprintf_s(buffer, _TRUNCATE, "%s", host);
        return buffer;
    }

    std::string QuerySocketAddress(SOCKET s, bool peer)
    {
        sockaddr_storage addr = {};
        int len = sizeof(addr);
        const int rc = peer
            ? g_RealGetPeerName(s, reinterpret_cast<sockaddr*>(&addr), &len)
            : g_RealGetSockName(s, reinterpret_cast<sockaddr*>(&addr), &len);
        if (rc != 0)
            return {};
        return FormatSockaddr(reinterpret_cast<const sockaddr*>(&addr), len);
    }

    void RefreshSocketAddresses(SOCKET s)
    {
        const std::string local = QuerySocketAddress(s, false);
        const std::string remote = QuerySocketAddress(s, true);

        AcquireSRWLockExclusive(&g_SocketLock);
        const auto it = g_Sockets.find(s);
        if (it != g_Sockets.end())
        {
            if (!local.empty())
                it->second.localAddress = local;
            if (!remote.empty())
                it->second.remoteAddress = remote;
        }
        ReleaseSRWLockExclusive(&g_SocketLock);
    }

    uint32_t RememberSocket(SOCKET s, int af, int type, int protocol)
    {
        AcquireSRWLockExclusive(&g_SocketLock);
        SocketState& state = g_Sockets[s];
        if (state.socketId == 0)
            state.socketId = static_cast<uint32_t>(InterlockedIncrement(&g_NextSocketId));
        if (af != AF_UNSPEC)
            state.af = af;
        if (type != 0)
            state.type = type;
        if (protocol != 0)
            state.protocol = protocol;
        const uint32_t socketId = state.socketId;
        ReleaseSRWLockExclusive(&g_SocketLock);
        return socketId;
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

    bool IsUdpSocket(SOCKET s)
    {
        SocketState state = {};
        if (LookupSocket(s, state))
            return state.type == SOCK_DGRAM || state.protocol == IPPROTO_UDP;

        return QuerySocketInt(s, SOL_SOCKET, SO_TYPE) == SOCK_DGRAM;
    }

    bool TryGetSockaddrPort(const sockaddr* addr, int addrLen, uint16_t* outPort)
    {
        if (!addr || !outPort || addrLen <= 0)
            return false;

        if (addr->sa_family == AF_INET && addrLen >= static_cast<int>(sizeof(sockaddr_in)))
        {
            const auto* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
            *outPort = ntohs(addr4->sin_port);
            return true;
        }

        if (addr->sa_family == AF_INET6 && addrLen >= static_cast<int>(sizeof(sockaddr_in6)))
        {
            const auto* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
            *outPort = ntohs(addr6->sin6_port);
            return true;
        }

        return false;
    }

    bool TryGetSockaddrIpv4HostOrder(const sockaddr* addr, int addrLen, uint32_t* outIpv4)
    {
        if (!addr || !outIpv4 || addrLen < static_cast<int>(sizeof(sockaddr_in)) || addr->sa_family != AF_INET)
            return false;

        const auto* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
        *outIpv4 = ntohl(addr4->sin_addr.S_un.S_addr);
        return true;
    }

    bool IsPrivateOrLocalIpv4(uint32_t ipv4)
    {
        const uint8_t a = static_cast<uint8_t>((ipv4 >> 24) & 0xFF);
        const uint8_t b = static_cast<uint8_t>((ipv4 >> 16) & 0xFF);

        if (a == 10 || a == 127)
            return true;
        if (a == 192 && b == 168)
            return true;
        if (a == 172 && b >= 16 && b <= 31)
            return true;
        if (a == 169 && b == 254)
            return true;

        return false;
    }

    bool IsPendingConnectError(int err)
    {
        return err == WSAEWOULDBLOCK || err == WSAEINPROGRESS || err == WSAEALREADY;
    }

    const char* ClassifyEndpoint(const sockaddr* addr, int addrLen, int type, int protocol)
    {
        if (!addr || addrLen <= 0)
            return "connected_peer";

        uint16_t port = 0;
        if (TryGetSockaddrPort(addr, addrLen, &port))
        {
            if (port == kBzrNetWebSocketPort)
                return "bzrnet_ws";
            if (port == kBzrNetProbePort)
                return "bzrnet_probe";
            if (port == kBzrNetRelayPort)
                return "bzrnet_relay";
        }

        const bool isUdp = type == SOCK_DGRAM || protocol == IPPROTO_UDP;
        const bool isTcp = type == SOCK_STREAM || protocol == IPPROTO_TCP;

        if (isUdp)
        {
            uint32_t ipv4 = 0;
            if (TryGetSockaddrIpv4HostOrder(addr, addrLen, &ipv4))
                return IsPrivateOrLocalIpv4(ipv4) ? "p2p_lan" : "p2p_candidate";
            return "udp_peer";
        }

        if (isTcp)
            return "tcp_peer";

        return "endpoint";
    }

    bool IsWebSocketControlSocket(SOCKET s)
    {
        if (!g_Config.enableRelayCapture || !g_RealGetPeerName)
            return false;

        sockaddr_storage peer = {};
        int peerLen = static_cast<int>(sizeof(peer));
        if (g_RealGetPeerName(s, reinterpret_cast<sockaddr*>(&peer), &peerLen) != 0)
            return false;

        uint16_t port = 0;
        return TryGetSockaddrPort(reinterpret_cast<const sockaddr*>(&peer), peerLen, &port) &&
            port == kBzrNetWebSocketPort;
    }

    // The eight message types that decide the gameplay route: endpoint exchange
    // and the two connect/route handoffs. These are what an /iprelay vs /ipdirect
    // investigation needs and nothing else, so they are what the default capture
    // records.
    //
    // RelayLogAllControl widens this to every control-plane message the service
    // exchanges -- Authorization, DoEnterLounge, DoJoinLobby, SetPlayerData,
    // game creation, chat, member joins and leaves. That is the traffic a
    // replacement/dedicated matchmaking service has to reproduce, so growing one
    // needs the whole conversation rather than the routing slice of it. It is
    // off by default because the wider capture carries account identity and
    // lobby metadata; see the privacy note in openshim.ini.
    bool IsRelayControlMessageType(const std::string& type)
    {
        if (g_Config.relayLogAllControl)
            return !type.empty();

        return type == "DoUpdateLAN" ||
            type == "DoUpdateWAN" ||
            type == "OnLANUpdated" ||
            type == "OnWANUpdated" ||
            type == "DoP2PConnect" ||
            type == "OnLobbyMemberP2PConnect" ||
            type == "DoP2PRoute" ||
            type == "OnP2PRoute";
    }

    bool ExtractJsonMessageType(const std::string& json, std::string& outType)
    {
        const size_t key = json.find("\"type\"");
        if (key == std::string::npos)
            return false;

        const size_t colon = json.find(':', key + 6);
        if (colon == std::string::npos)
            return false;

        size_t quote = json.find('"', colon + 1);
        if (quote == std::string::npos)
            return false;
        const size_t end = json.find('"', quote + 1);
        if (end == std::string::npos || end == quote + 1 || end - quote > 128)
            return false;

        outType.assign(json, quote + 1, end - quote - 1);
        return true;
    }

    void WriteRelayControlMessage(SOCKET s, bool outbound, const std::string& type, const std::string& message)
    {
        if (!g_RelayControlLog || !IsRelayControlMessageType(type))
            return;

        std::string compact = message;
        std::replace(compact.begin(), compact.end(), '\r', ' ');
        std::replace(compact.begin(), compact.end(), '\n', ' ');

        AcquireSRWLockExclusive(&g_RelayControlLogLock);
        std::fprintf(
            g_RelayControlLog,
            "{\"tickMs\":%llu,\"direction\":\"%s\",\"socketId\":%u,\"type\":\"%s\",\"message\":%s}\n",
            static_cast<unsigned long long>(GetTickCount64()),
            outbound ? "outbound" : "inbound",
            GetSocketId(s),
            type.c_str(),
            compact.c_str());
        std::fflush(g_RelayControlLog);
        ReleaseSRWLockExclusive(&g_RelayControlLogLock);

        Logf("[OpenShimNet] relay_capture ws direction=%s sid=%u type=%s bytes=%u",
            outbound ? "outbound" : "inbound",
            GetSocketId(s),
            type.c_str(),
            static_cast<unsigned>(message.size()));
    }

    void ProcessWebSocketMessage(SOCKET s, bool outbound, uint8_t opcode, const std::vector<uint8_t>& payload)
    {
        if (opcode != 0x1 || payload.empty())
            return;

        const std::string json(payload.begin(), payload.end());
        std::string type;
        if (ExtractJsonMessageType(json, type))
            WriteRelayControlMessage(s, outbound, type, json);
    }

    size_t FindHttpHeaderEnd(const std::vector<uint8_t>& data)
    {
        static const uint8_t delimiter[] = { '\r', '\n', '\r', '\n' };
        const auto it = std::search(data.begin(), data.end(), std::begin(delimiter), std::end(delimiter));
        return it == data.end() ? std::string::npos : static_cast<size_t>(it - data.begin()) + sizeof(delimiter);
    }

    void ProcessWebSocketDirection(
        SOCKET s,
        bool outbound,
        WebSocketDirectionState& state,
        const uint8_t* bytes,
        size_t length)
    {
        if (!bytes || length == 0)
            return;
        if (state.pending.size() + length > kRelayCaptureMaxWebSocketBytes)
        {
            state.pending.clear();
            state.fragmented.clear();
            state.fragmentedOpcode = 0;
            return;
        }

        state.pending.insert(state.pending.end(), bytes, bytes + length);
        if (!state.handshakeComplete)
        {
            const size_t headerEnd = FindHttpHeaderEnd(state.pending);
            if (headerEnd == std::string::npos)
            {
                if (state.pending.size() > 64 * 1024)
                    state.pending.clear();
                return;
            }
            state.pending.erase(state.pending.begin(), state.pending.begin() + headerEnd);
            state.handshakeComplete = true;
        }

        while (state.pending.size() >= 2)
        {
            const uint8_t first = state.pending[0];
            const uint8_t second = state.pending[1];
            const bool fin = (first & 0x80u) != 0;
            const uint8_t opcode = first & 0x0Fu;
            const bool masked = (second & 0x80u) != 0;
            uint64_t payloadLength = second & 0x7Fu;
            size_t headerLength = 2;

            if (payloadLength == 126)
            {
                if (state.pending.size() < 4)
                    return;
                payloadLength = (static_cast<uint64_t>(state.pending[2]) << 8) |
                    static_cast<uint64_t>(state.pending[3]);
                headerLength = 4;
            }
            else if (payloadLength == 127)
            {
                if (state.pending.size() < 10)
                    return;
                payloadLength = 0;
                for (size_t i = 2; i < 10; ++i)
                    payloadLength = (payloadLength << 8) | state.pending[i];
                headerLength = 10;
            }

            if (payloadLength > kRelayCaptureMaxWebSocketBytes)
            {
                state.pending.clear();
                state.fragmented.clear();
                state.fragmentedOpcode = 0;
                return;
            }

            uint8_t mask[4] = {};
            if (masked)
            {
                if (state.pending.size() < headerLength + sizeof(mask))
                    return;
                std::memcpy(mask, state.pending.data() + headerLength, sizeof(mask));
                headerLength += sizeof(mask);
            }

            if (state.pending.size() < headerLength + static_cast<size_t>(payloadLength))
                return;

            std::vector<uint8_t> payload(static_cast<size_t>(payloadLength));
            for (size_t i = 0; i < payload.size(); ++i)
            {
                payload[i] = state.pending[headerLength + i];
                if (masked)
                    payload[i] ^= mask[i % 4];
            }
            state.pending.erase(
                state.pending.begin(),
                state.pending.begin() + headerLength + static_cast<size_t>(payloadLength));

            if (opcode == 0x0)
            {
                if (state.fragmentedOpcode == 0 ||
                    state.fragmented.size() + payload.size() > kRelayCaptureMaxWebSocketBytes)
                {
                    state.fragmented.clear();
                    state.fragmentedOpcode = 0;
                    continue;
                }
                state.fragmented.insert(state.fragmented.end(), payload.begin(), payload.end());
                if (fin)
                {
                    ProcessWebSocketMessage(s, outbound, state.fragmentedOpcode, state.fragmented);
                    state.fragmented.clear();
                    state.fragmentedOpcode = 0;
                }
            }
            else if (opcode == 0x1 || opcode == 0x2)
            {
                if (fin)
                {
                    ProcessWebSocketMessage(s, outbound, opcode, payload);
                }
                else
                {
                    state.fragmentedOpcode = opcode;
                    state.fragmented = std::move(payload);
                }
            }
        }
    }

    void FeedWebSocketCapture(SOCKET s, bool outbound, const uint8_t* bytes, size_t length)
    {
        if (!g_Config.enableRelayCapture || !IsWebSocketControlSocket(s) || !bytes || length == 0)
            return;

        AcquireSRWLockExclusive(&g_WebSocketCaptureLock);
        WebSocketCaptureState& state = g_WebSocketCapture[s];
        ProcessWebSocketDirection(s, outbound, outbound ? state.outbound : state.inbound, bytes, length);
        ReleaseSRWLockExclusive(&g_WebSocketCaptureLock);
    }

    uint32_t GetSocketId(SOCKET s)
    {
        AcquireSRWLockShared(&g_SocketLock);
        const auto it = g_Sockets.find(s);
        const uint32_t socketId = (it != g_Sockets.end()) ? it->second.socketId : 0;
        ReleaseSRWLockShared(&g_SocketLock);
        return socketId;
    }

    const char* SockOptName(int level, int optName)
    {
        if (level == SOL_SOCKET)
        {
            switch (optName)
            {
            case SO_SNDBUF: return "SO_SNDBUF";
            case SO_RCVBUF: return "SO_RCVBUF";
            case SO_KEEPALIVE: return "SO_KEEPALIVE";
            case SO_REUSEADDR: return "SO_REUSEADDR";
            case SO_BROADCAST: return "SO_BROADCAST";
            case SO_LINGER: return "SO_LINGER";
            case SO_TYPE: return "SO_TYPE";
            default: break;
            }
        }
        else if (level == IPPROTO_TCP && optName == TCP_NODELAY)
        {
            return "TCP_NODELAY";
        }
        else if (level == IPPROTO_IP && optName == IP_TOS)
        {
            return "IP_TOS";
        }
        return "opt";
    }

    bool ShouldLogPacket(uint32_t packetCount)
    {
        if (!g_Config.logSocketPackets)
            return false;
        return packetCount <= g_Config.packetLogLimit ||
            (g_Config.packetLogInterval > 0 && (packetCount % g_Config.packetLogInterval) == 0);
    }

    // Every datagram on the BZRNet endpoint-probe (1338) and UDP relay (1339)
    // ports, unsampled. LogPacketActivity below samples by packet count, which
    // is right for gameplay traffic and wrong here: relay and probe exchanges
    // are sparse and each one is a decision point, so a sampled view can miss
    // the entire negotiation. Off by default because it is per-packet.
    void LogRelayDatagram(const char* api, SOCKET s, bool outbound, int bytes, const sockaddr* addr, int addrLen)
    {
        if (!g_Config.relayLogDatagrams || !addr || addrLen <= 0)
            return;

        uint16_t port = 0;
        if (!TryGetSockaddrPort(addr, addrLen, &port))
            return;
        if (port != kBzrNetProbePort && port != kBzrNetRelayPort)
            return;

        Logf("[OpenShimNet] relay_datagram sid=%u api=%s direction=%s bytes=%d port=%u peer=%s",
            GetSocketId(s),
            api,
            outbound ? "outbound" : "inbound",
            bytes,
            static_cast<unsigned>(port),
            FormatSockaddr(addr, addrLen).c_str());
    }

    void LogPacketActivity(const char* api, SOCKET s, bool outbound, int bytes, const sockaddr* addr, int addrLen)
    {
        // Ahead of the sampling and the socket-table lookup below, both of which
        // can return early.
        LogRelayDatagram(api, s, outbound, bytes, addr, addrLen);

        SocketState snapshot = {};
        bool found = false;

        AcquireSRWLockExclusive(&g_SocketLock);
        auto it = g_Sockets.find(s);
        if (it != g_Sockets.end())
        {
            SocketState& state = it->second;
            if (addr)
            {
                std::string formatted = FormatSockaddr(addr, addrLen);
                if (!formatted.empty())
                    state.remoteAddress = formatted;
            }
            if (outbound)
            {
                state.bytesSent += static_cast<uint64_t>(bytes);
                ++state.packetsSent;
            }
            else
            {
                state.bytesRecv += static_cast<uint64_t>(bytes);
                ++state.packetsRecv;
            }
            snapshot = state;
            found = true;
        }
        ReleaseSRWLockExclusive(&g_SocketLock);

        if (!found)
            return;

        RefreshSocketAddresses(s);
        if (!LookupSocket(s, snapshot))
            return;

        const uint32_t packetCount = outbound ? snapshot.packetsSent : snapshot.packetsRecv;
        const uint64_t byteCount = outbound ? snapshot.bytesSent : snapshot.bytesRecv;
        if (!ShouldLogPacket(packetCount))
            return;

        const std::string endpoint = addr ? FormatSockaddr(addr, addrLen) : snapshot.remoteAddress;
        const char* routeClass = ClassifyEndpoint(addr, addrLen, snapshot.type, snapshot.protocol);
        Logf("[OpenShimNet] sid=%u sock=0x%08X %s %s bytes=%d packet=%u totalBytes=%llu route=%s local=%s remote=%s",
            snapshot.socketId,
            static_cast<unsigned>(s),
            SocketTypeLabel(snapshot.type, snapshot.protocol),
            api,
            bytes,
            packetCount,
            static_cast<unsigned long long>(byteCount),
            routeClass,
            snapshot.localAddress.empty() ? "<unbound>" : snapshot.localAddress.c_str(),
            endpoint.empty() ? (snapshot.remoteAddress.empty() ? "<unknown>" : snapshot.remoteAddress.c_str()) : endpoint.c_str());
    }

    void LogSocketLifecycleEvent(const char* action, SOCKET s, const sockaddr* addr, int addrLen)
    {
        if (!g_Config.logSocketLifecycle)
            return;

        RefreshSocketAddresses(s);
        SocketState snapshot = {};
        if (!LookupSocket(s, snapshot))
            return;

        const std::string endpoint = addr ? FormatSockaddr(addr, addrLen) : snapshot.remoteAddress;
        const char* routeClass = ClassifyEndpoint(addr, addrLen, snapshot.type, snapshot.protocol);
        Logf("[OpenShimNet] sid=%u sock=0x%08X %s %s af=%d type=%d proto=%d route=%s local=%s remote=%s",
            snapshot.socketId,
            static_cast<unsigned>(s),
            SocketTypeLabel(snapshot.type, snapshot.protocol),
            action,
            snapshot.af,
            snapshot.type,
            snapshot.protocol,
            routeClass,
            snapshot.localAddress.empty() ? "<unbound>" : snapshot.localAddress.c_str(),
            endpoint.empty() ? (snapshot.remoteAddress.empty() ? "<unknown>" : snapshot.remoteAddress.c_str()) : endpoint.c_str());
    }

    bool RememberRouteKey(SOCKET s, const std::string& routeKey, SocketState* outSnapshot)
    {
        bool changed = false;

        AcquireSRWLockExclusive(&g_SocketLock);
        SocketState& state = g_Sockets[s];
        if (state.socketId == 0)
            state.socketId = static_cast<uint32_t>(InterlockedIncrement(&g_NextSocketId));
        if (state.lastRouteKey != routeKey)
        {
            state.lastRouteKey = routeKey;
            changed = true;
        }
        if (outSnapshot)
            *outSnapshot = state;
        ReleaseSRWLockExclusive(&g_SocketLock);

        return changed;
    }

    void LogRouteEvent(const char* api, SOCKET s, const sockaddr* addr, int addrLen, bool success, int err, bool onlyOnChange)
    {
        if (!g_Config.logging)
            return;

        RefreshSocketAddresses(s);

        SocketState snapshot = {};
        if (!LookupSocket(s, snapshot))
            RememberSocket(s, AF_UNSPEC, 0, 0);
        if (!LookupSocket(s, snapshot))
            return;

        const std::string endpoint = addr ? FormatSockaddr(addr, addrLen) : snapshot.remoteAddress;
        const char* routeClass = ClassifyEndpoint(addr, addrLen, snapshot.type, snapshot.protocol);

        std::string routeKey = api;
        routeKey.push_back('|');
        routeKey += routeClass;
        routeKey.push_back('|');
        routeKey += endpoint;

        const bool changed = RememberRouteKey(s, routeKey, &snapshot);
        if (onlyOnChange && !changed)
            return;

        RefreshSocketAddresses(s);
        if (!LookupSocket(s, snapshot))
            return;

        const char* status = success ? "ok" : (IsPendingConnectError(err) ? "pending" : "failed");
        Logf("[OpenShimNet] sid=%u route api=%s status=%s sock=0x%08X %s class=%s endpoint=%s local=%s remote=%s err=%d",
            snapshot.socketId,
            api,
            status,
            static_cast<unsigned>(s),
            SocketTypeLabel(snapshot.type, snapshot.protocol),
            routeClass,
            endpoint.empty() ? "<unknown>" : endpoint.c_str(),
            snapshot.localAddress.empty() ? "<unbound>" : snapshot.localAddress.c_str(),
            snapshot.remoteAddress.empty() ? "<unknown>" : snapshot.remoteAddress.c_str(),
            err);
    }

    void LogSocketSummaryAndForget(SOCKET s)
    {
        SocketState snapshot = {};
        bool found = false;
        AcquireSRWLockExclusive(&g_SocketLock);
        const auto it = g_Sockets.find(s);
        if (it != g_Sockets.end())
        {
            snapshot = it->second;
            g_Sockets.erase(it);
            found = true;
        }
        ReleaseSRWLockExclusive(&g_SocketLock);

        if (!found || !g_Config.logSocketLifecycle)
            return;

        Logf("[OpenShimNet] sid=%u sock=0x%08X %s close sentPackets=%u sentBytes=%llu recvPackets=%u recvBytes=%llu local=%s remote=%s",
            snapshot.socketId,
            static_cast<unsigned>(s),
            SocketTypeLabel(snapshot.type, snapshot.protocol),
            snapshot.packetsSent,
            static_cast<unsigned long long>(snapshot.bytesSent),
            snapshot.packetsRecv,
            static_cast<unsigned long long>(snapshot.bytesRecv),
            snapshot.localAddress.empty() ? "<unbound>" : snapshot.localAddress.c_str(),
            snapshot.remoteAddress.empty() ? "<unknown>" : snapshot.remoteAddress.c_str());
    }

    void ResetPeerBuf(PeerBuf& peer)
    {
        std::memset(&peer, 0, sizeof(peer));
        peer.socket = INVALID_SOCKET;
        peer.windowMs = g_Config.adaptivePacketReorder ? g_Config.reorderMinWindowMs : g_Config.reorderWindowMs;
    }

    uint64_t MakePeerKey(const sockaddr_in& addr)
    {
        return (static_cast<uint64_t>(static_cast<uint32_t>(addr.sin_addr.S_un.S_addr)) << 16) |
            static_cast<uint64_t>(ntohs(addr.sin_port));
    }

    std::string FormatIpv4Peer(const sockaddr_in& addr)
    {
        return FormatSockaddr(reinterpret_cast<const sockaddr*>(&addr), static_cast<int>(sizeof(addr)));
    }

    uint32_t ScatterCopy(LPWSABUF buffers, DWORD bufferCount, const uint8_t* source, uint32_t sourceLength)
    {
        uint32_t copied = 0;
        for (DWORD i = 0; i < bufferCount && copied < sourceLength; ++i)
        {
            if (!buffers[i].buf || buffers[i].len == 0)
                continue;

            uint32_t chunk = sourceLength - copied;
            chunk = (std::min)(chunk, static_cast<uint32_t>(buffers[i].len));
            std::memcpy(buffers[i].buf, source + copied, chunk);
            copied += chunk;
        }
        return copied;
    }

    uint32_t CopyPacketToCaller(
        LPWSABUF buffers,
        DWORD bufferCount,
        LPDWORD bytesRecv,
        LPDWORD flags,
        sockaddr* from,
        LPINT fromLen,
        const uint8_t* data,
        uint32_t dataLength,
        const sockaddr_in* source)
    {
        const uint32_t copied = ScatterCopy(buffers, bufferCount, data, dataLength);
        if (bytesRecv)
            *bytesRecv = copied;
        if (flags)
            *flags = 0;
        if (source && from && fromLen)
        {
            const int copyBytes = (std::min)(*fromLen, static_cast<int>(sizeof(*source)));
            if (copyBytes > 0)
                std::memcpy(from, source, static_cast<size_t>(copyBytes));
            *fromLen = static_cast<int>(sizeof(*source));
        }
        return copied;
    }

    PeerBuf* FindOrCreatePeerBufLocked(SOCKET s, const sockaddr_in& from)
    {
        const uint64_t peerKey = MakePeerKey(from);
        for (uint32_t i = 0; i < g_Config.reorderPeers; ++i)
        {
            PeerBuf& peer = g_ReorderPeers[i];
            if (peer.peerKey == peerKey && peer.socket == s)
                return &peer;
        }

        for (uint32_t i = 0; i < g_Config.reorderPeers; ++i)
        {
            PeerBuf& peer = g_ReorderPeers[i];
            if (peer.peerKey == 0)
            {
                ResetPeerBuf(peer);
                peer.socket = s;
                peer.peerKey = peerKey;
                LogReorderf("[OpenShimNet] sid=%u reorder peer created sock=0x%08X peer=%s key=0x%llX",
                    GetSocketId(s),
                    static_cast<unsigned>(s),
                    FormatIpv4Peer(from).c_str(),
                    static_cast<unsigned long long>(peerKey));
                return &peer;
            }
        }

        LogReorderf("[OpenShimNet] sid=%u reorder peer table full sock=0x%08X peer=%s key=0x%llX",
            GetSocketId(s),
            static_cast<unsigned>(s),
            FormatIpv4Peer(from).c_str(),
            static_cast<unsigned long long>(peerKey));
        return nullptr;
    }

    void AdaptReorderWindowOnArrival(PeerBuf& peer, uint32_t sequence, uint64_t nowMs)
    {
        if (!g_Config.adaptivePacketReorder || !peer.seqInitialized)
            return;

        const uint32_t expected = peer.lastSequence + 1;
        if (sequence <= peer.lastSequence)
            return;

        if (sequence > expected)
        {
            const uint32_t grown = peer.windowMs * 2 + kReorderGrowPadMs;
            peer.windowMs = (std::min)(grown, g_Config.reorderWindowMs);
            peer.lastAdjustMs = nowMs;
            LogReorderf("[OpenShimNet] sid=%u reorder adapt grow sock=0x%08X seq=%u expected=%u windowMs=%u",
                GetSocketId(peer.socket),
                static_cast<unsigned>(peer.socket),
                sequence,
                expected,
                peer.windowMs);
        }
    }

    void DecayReorderWindow(PeerBuf& peer, uint64_t nowMs)
    {
        if (!g_Config.adaptivePacketReorder || peer.windowMs <= g_Config.reorderMinWindowMs)
            return;
        if (nowMs - peer.lastAdjustMs < kReorderDecayMs)
            return;

        peer.windowMs = (peer.windowMs > g_Config.reorderMinWindowMs + kReorderDecayStepMs)
            ? peer.windowMs - kReorderDecayStepMs
            : g_Config.reorderMinWindowMs;
        peer.lastAdjustMs = nowMs;
    }

    void InsertPacketLocked(PeerBuf& peer, uint32_t sequence, uint64_t timestampMs, const sockaddr_in& from, const uint8_t* data, uint32_t dataLength)
    {
        for (uint32_t i = 0; i < g_Config.reorderDepth; ++i)
        {
            ReorderSlot& slot = peer.slots[i];
            if (slot.used && slot.sequence == sequence)
            {
                LogReorderf("[OpenShimNet] sid=%u reorder duplicate dropped sock=0x%08X peer=%s seq=%u filled=%u",
                    GetSocketId(peer.socket),
                    static_cast<unsigned>(peer.socket),
                    FormatIpv4Peer(from).c_str(),
                    sequence,
                    peer.filled);
                return;
            }
        }

        for (uint32_t i = 0; i < g_Config.reorderDepth; ++i)
        {
            ReorderSlot& slot = peer.slots[i];
            if (slot.used)
                continue;

            slot.used = 1;
            slot.sequence = sequence;
            slot.timestampMs = timestampMs;
            slot.from = from;
            slot.length = (std::min)(dataLength, kReorderMaxPacketBytes);
            std::memcpy(slot.data, data, slot.length);
            ++peer.filled;
            LogReorderf("[OpenShimNet] sid=%u reorder buffered sock=0x%08X peer=%s seq=%u bytes=%u filled=%u",
                GetSocketId(peer.socket),
                static_cast<unsigned>(peer.socket),
                FormatIpv4Peer(from).c_str(),
                sequence,
                slot.length,
                peer.filled);
            return;
        }

        ReorderSlot* oldest = &peer.slots[0];
        for (uint32_t i = 1; i < g_Config.reorderDepth; ++i)
        {
            if (peer.slots[i].used && peer.slots[i].timestampMs < oldest->timestampMs)
                oldest = &peer.slots[i];
        }

        oldest->used = 1;
        oldest->sequence = sequence;
        oldest->timestampMs = timestampMs;
        oldest->from = from;
        oldest->length = (std::min)(dataLength, kReorderMaxPacketBytes);
        std::memcpy(oldest->data, data, oldest->length);
        LogReorderf("[OpenShimNet] sid=%u reorder evicted oldest sock=0x%08X peer=%s newSeq=%u bytes=%u filled=%u",
            GetSocketId(peer.socket),
            static_cast<unsigned>(peer.socket),
            FormatIpv4Peer(from).c_str(),
            sequence,
            oldest->length,
            peer.filled);
    }

    int PickReadySlotLocked(PeerBuf& peer, uint64_t nowMs)
    {
        if (peer.filled == 0)
            return -1;

        DecayReorderWindow(peer, nowMs);

        if (peer.seqInitialized)
        {
            const uint32_t expected = peer.lastSequence + 1;
            for (uint32_t i = 0; i < g_Config.reorderDepth; ++i)
            {
                if (peer.slots[i].used && peer.slots[i].sequence == expected)
                    return static_cast<int>(i);
            }
        }

        int lowestIndex = -1;
        for (uint32_t i = 0; i < g_Config.reorderDepth; ++i)
        {
            if (!peer.slots[i].used)
                continue;

            if (lowestIndex < 0 || peer.slots[i].sequence < peer.slots[lowestIndex].sequence)
                lowestIndex = static_cast<int>(i);
        }

        if (lowestIndex < 0)
            return -1;

        if (!peer.seqInitialized)
            return lowestIndex;

        const ReorderSlot& slot = peer.slots[lowestIndex];
        if (nowMs >= slot.timestampMs && (nowMs - slot.timestampMs) >= peer.windowMs)
            return lowestIndex;

        return -1;
    }

    bool TryDeliverBufferedPacket(
        SOCKET s,
        LPWSABUF buffers,
        DWORD bufferCount,
        LPDWORD bytesRecv,
        LPDWORD flags,
        sockaddr* from,
        LPINT fromLen,
        uint32_t& outDelivered,
        sockaddr_in& outSource)
    {
        outDelivered = 0;
        std::memset(&outSource, 0, sizeof(outSource));

        AcquireSRWLockExclusive(&g_ReorderLock);

        const uint64_t nowMs = GetTickCount64();
        PeerBuf* selectedPeer = nullptr;
        ReorderSlot* selectedSlot = nullptr;
        for (uint32_t i = 0; i < g_Config.reorderPeers; ++i)
        {
            PeerBuf& peer = g_ReorderPeers[i];
            if (peer.peerKey == 0 || peer.socket != s)
                continue;

            const int slotIndex = PickReadySlotLocked(peer, nowMs);
            if (slotIndex >= 0)
            {
                selectedPeer = &peer;
                selectedSlot = &peer.slots[slotIndex];
                break;
            }
        }

        if (!selectedPeer || !selectedSlot)
        {
            ReleaseSRWLockExclusive(&g_ReorderLock);
            return false;
        }

        outSource = selectedSlot->from;
        outDelivered = CopyPacketToCaller(buffers, bufferCount, bytesRecv, flags, from, fromLen, selectedSlot->data, selectedSlot->length, &selectedSlot->from);
        selectedPeer->lastSequence = selectedSlot->sequence;
        selectedPeer->seqInitialized = 1;
        selectedSlot->used = 0;
        if (selectedPeer->filled > 0)
            --selectedPeer->filled;

        LogReorderf("[OpenShimNet] sid=%u reorder delivered sock=0x%08X peer=%s seq=%u bytes=%u remaining=%u windowMs=%u",
            GetSocketId(s),
            static_cast<unsigned>(s),
            FormatIpv4Peer(outSource).c_str(),
            selectedPeer->lastSequence,
            outDelivered,
            selectedPeer->filled,
            selectedPeer->windowMs);

        ReleaseSRWLockExclusive(&g_ReorderLock);
        return true;
    }

    void ClearReorderStateForSocket(SOCKET s)
    {
        AcquireSRWLockExclusive(&g_ReorderLock);
        uint32_t clearedPeers = 0;
        for (uint32_t i = 0; i < g_Config.reorderPeers; ++i)
        {
            PeerBuf& peer = g_ReorderPeers[i];
            if (peer.peerKey != 0 && peer.socket == s)
            {
                ResetPeerBuf(peer);
                ++clearedPeers;
            }
        }
        ReleaseSRWLockExclusive(&g_ReorderLock);

        if (clearedPeers > 0)
        {
            LogReorderf("[OpenShimNet] sid=%u reorder cleared sock=0x%08X peers=%u",
                GetSocketId(s),
                static_cast<unsigned>(s),
                clearedPeers);
        }
    }

    bool SocketHasQueuedReceiveData(SOCKET s)
    {
        if (!g_RealIoctlSocket)
            return false;

        u_long queuedBytes = 0;
        const int rc = g_RealIoctlSocket(s, FIONREAD, &queuedBytes);
        if (rc != 0)
        {
            const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : WSAGetLastError();
            LogReorderf("[OpenShimNet] sid=%u reorder FIONREAD failed sock=0x%08X err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
            return false;
        }

        LogReorderf("[OpenShimNet] sid=%u reorder FIONREAD sock=0x%08X queuedBytes=%lu",
            GetSocketId(s),
            static_cast<unsigned>(s),
            static_cast<unsigned long>(queuedBytes));
        return queuedBytes > 0;
    }

    bool HasBufferedReorderPackets(SOCKET s)
    {
        bool hasPackets = false;
        AcquireSRWLockShared(&g_ReorderLock);
        for (uint32_t i = 0; i < g_Config.reorderPeers; ++i)
        {
            const PeerBuf& peer = g_ReorderPeers[i];
            if (peer.peerKey != 0 && peer.socket == s && peer.filled > 0)
            {
                hasPackets = true;
                break;
            }
        }
        ReleaseSRWLockShared(&g_ReorderLock);
        return hasPackets;
    }

    bool IsWakePacket(const uint8_t* data, uint32_t length, const sockaddr_in& source)
    {
        return length == sizeof(kWakeMagic) &&
            source.sin_family == AF_INET &&
            ntohl(source.sin_addr.S_un.S_addr) == 0x7f000001u &&
            std::memcmp(data, kWakeMagic, sizeof(kWakeMagic)) == 0;
    }

    DWORD WINAPI ReorderWakeThread(LPVOID)
    {
        uint32_t burst = 0;
        while (InterlockedCompareExchange(&g_WakeStop, 0, 0) == 0)
        {
            Sleep(kReorderWakeTickMs);
            const SOCKET target = g_ReorderSocket;
            if (target == INVALID_SOCKET || !HasBufferedReorderPackets(target) || !g_RealGetSockName || !g_RealSendTo)
            {
                burst = 0;
                continue;
            }

            const uint64_t now = GetTickCount64();
            if (now - g_LastRecvCallMs < kReorderWakeIdleMs)
            {
                burst = 0;
                continue;
            }
            if (burst >= kReorderWakeBurstCap)
                continue;

            sockaddr_in local = {};
            int localLen = sizeof(local);
            if (g_RealGetSockName(target, reinterpret_cast<sockaddr*>(&local), &localLen) != 0 ||
                local.sin_family != AF_INET || local.sin_port == 0)
            {
                continue;
            }

            if (g_WakeSender == INVALID_SOCKET)
            {
                g_WakeSender = g_RealSocket ? g_RealSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) : INVALID_SOCKET;
                if (g_WakeSender == INVALID_SOCKET)
                    continue;
            }

            sockaddr_in wakeTo = {};
            wakeTo.sin_family = AF_INET;
            wakeTo.sin_addr.S_un.S_addr = htonl(0x7f000001u);
            wakeTo.sin_port = local.sin_port;
            g_RealSendTo(g_WakeSender, reinterpret_cast<const char*>(kWakeMagic),
                static_cast<int>(sizeof(kWakeMagic)), 0,
                reinterpret_cast<const sockaddr*>(&wakeTo), sizeof(wakeTo));
            ++burst;
            if (!g_WakeLogged)
            {
                g_WakeLogged = true;
                Logf("[OpenShimNet] reorder wake thread nudging socket 0x%08X on loopback port %u",
                    static_cast<unsigned>(target),
                    ntohs(local.sin_port));
            }
        }
        return 0;
    }

    bool IsLoopbackDestination(const sockaddr* to)
    {
        if (!to || to->sa_family != AF_INET)
            return false;

        const auto* addr4 = reinterpret_cast<const sockaddr_in*>(to);
        return (ntohl(addr4->sin_addr.S_un.S_addr) >> 24) == 127;
    }

    uint32_t GatherWsabufPayload(LPWSABUF buffers, DWORD bufferCount, uint8_t* outData, uint32_t outCapacity)
    {
        if (!buffers || !outData || outCapacity == 0)
            return 0;

        uint32_t copied = 0;
        for (DWORD i = 0; i < bufferCount && copied < outCapacity; ++i)
        {
            if (!buffers[i].buf || buffers[i].len == 0)
                continue;

            const uint32_t chunk = (std::min)(static_cast<uint32_t>(buffers[i].len), outCapacity - copied);
            std::memcpy(outData + copied, buffers[i].buf, chunk);
            copied += chunk;
        }
        return copied;
    }

    bool RegisterPendingCaptureIo(
        LPWSAOVERLAPPED overlapped,
        PendingIoKind kind,
        SOCKET s,
        LPWSABUF buffers,
        DWORD bufferCount,
        sockaddr* from,
        LPINT fromLen,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE originalCompletionRoutine)
    {
        if (!g_Config.enableRelayCapture || !overlapped || !buffers || bufferCount == 0)
            return false;

        PendingCaptureIo pending = {};
        pending.kind = kind;
        pending.socket = s;
        pending.buffers.assign(buffers, buffers + bufferCount);
        pending.from = from;
        pending.fromLen = fromLen;
        pending.originalCompletionRoutine = originalCompletionRoutine;
        pending.requestedLength = GetRequestedWsabufBytes(buffers, bufferCount);

        AcquireSRWLockExclusive(&g_PendingCaptureLock);
        g_PendingCaptureIo[overlapped] = std::move(pending);
        ReleaseSRWLockExclusive(&g_PendingCaptureLock);
        return true;
    }

    bool TakePendingCaptureIo(LPWSAOVERLAPPED overlapped, PendingCaptureIo& outPending)
    {
        if (!overlapped)
            return false;

        AcquireSRWLockExclusive(&g_PendingCaptureLock);
        const auto it = g_PendingCaptureIo.find(overlapped);
        if (it == g_PendingCaptureIo.end())
        {
            ReleaseSRWLockExclusive(&g_PendingCaptureLock);
            return false;
        }
        outPending = std::move(it->second);
        g_PendingCaptureIo.erase(it);
        ReleaseSRWLockExclusive(&g_PendingCaptureLock);
        return true;
    }

    void MarkPendingCaptureImmediate(LPWSAOVERLAPPED overlapped)
    {
        if (!overlapped)
            return;
        AcquireSRWLockExclusive(&g_PendingCaptureLock);
        const auto it = g_PendingCaptureIo.find(overlapped);
        if (it != g_PendingCaptureIo.end())
            it->second.capturedImmediate = true;
        ReleaseSRWLockExclusive(&g_PendingCaptureLock);
    }

    void CancelPendingCaptureIo(LPWSAOVERLAPPED overlapped)
    {
        if (!overlapped)
            return;
        AcquireSRWLockExclusive(&g_PendingCaptureLock);
        g_PendingCaptureIo.erase(overlapped);
        ReleaseSRWLockExclusive(&g_PendingCaptureLock);
    }

    void PurgeWebSocketCaptureForSocket(SOCKET s)
    {
        AcquireSRWLockExclusive(&g_WebSocketCaptureLock);
        g_WebSocketCapture.erase(s);
        ReleaseSRWLockExclusive(&g_WebSocketCaptureLock);
    }

    void CaptureCompletedIo(const PendingCaptureIo& pending, DWORD transferredLength, DWORD completionError)
    {
        if (pending.capturedImmediate)
            return;

        const uint32_t captureLength = (std::min)(
            static_cast<uint32_t>(transferredLength),
            kRelayCaptureMaxWebSocketBytes);
        std::vector<uint8_t> payload(captureLength);
        const uint32_t copied = captureLength > 0
            ? GatherWsabufPayload(
                const_cast<LPWSABUF>(pending.buffers.data()),
                static_cast<DWORD>(pending.buffers.size()),
                payload.data(),
                captureLength)
            : 0;
        payload.resize(copied);

        sockaddr_storage peer = {};
        int peerLen = 0;
        const sockaddr* endpoint = nullptr;
        if (pending.kind == PendingIoKind::WSARecvFrom && pending.from)
        {
            endpoint = pending.from;
            peerLen = pending.fromLen ? *pending.fromLen : static_cast<int>(sizeof(sockaddr_in));
        }
        else if (g_RealGetPeerName)
        {
            peerLen = static_cast<int>(sizeof(peer));
            if (g_RealGetPeerName(pending.socket, reinterpret_cast<sockaddr*>(&peer), &peerLen) == 0)
                endpoint = reinterpret_cast<const sockaddr*>(&peer);
            else
                peerLen = 0;
        }

        if (pending.kind == PendingIoKind::WSARecvFrom && IsUdpSocket(pending.socket))
        {
            CaptureRecvPathEvent(
                kBufferLogEventWSARecvFromCompletion,
                pending.socket,
                endpoint,
                0,
                pending.requestedLength,
                transferredLength,
                completionError,
                payload.empty() ? nullptr : payload.data());
        }

        if (!payload.empty())
            FeedWebSocketCapture(pending.socket, false, payload.data(), payload.size());
        if (completionError == 0)
            LogPacketActivity(
                pending.kind == PendingIoKind::WSARecvFrom ? "WSARecvFrom/IOCP" : "WSARecv/IOCP",
                pending.socket,
                false,
                static_cast<int>(transferredLength),
                endpoint,
                peerLen);
    }

    void HandleCompletedCaptureIo(LPWSAOVERLAPPED overlapped, DWORD transferredLength, DWORD completionError)
    {
        PendingCaptureIo pending = {};
        if (TakePendingCaptureIo(overlapped, pending))
            CaptureCompletedIo(pending, transferredLength, completionError);
    }

    // Count one outbound datagram, closing the one-second window when it expires.
    // Called from every UDP send path, including failed sends: sendto promises
    // handoff rather than delivery, and a send that errors still consumed the
    // queue slot and the CPU that produced it.
    void MeasureOutboundBurst(uint32_t bytes)
    {
        uint32_t closedPackets = 0;
        uint32_t closedBytes = 0;
        bool report = false;
        uint32_t peakPps = 0;
        uint32_t peakBps = 0;
        uint64_t burstSeconds = 0;
        uint64_t totalPackets = 0;
        uint64_t totalBytes = 0;

        const uint64_t nowMs = GetTickCount64();
        AcquireSRWLockExclusive(&g_BurstLock);
        if (g_BurstWindowStartMs == 0)
        {
            g_BurstWindowStartMs = nowMs;
            g_BurstLastReportMs = nowMs;
        }
        if (nowMs - g_BurstWindowStartMs >= 1000)
        {
            closedPackets = g_BurstWindowPackets;
            closedBytes = g_BurstWindowBytes;
            if (closedPackets > g_BurstPeakPps)
                g_BurstPeakPps = closedPackets;
            if (closedBytes > g_BurstPeakBps)
                g_BurstPeakBps = closedBytes;
            if (closedPackets > kBurstThresholdPps)
                ++g_BurstSeconds;
            g_BurstWindowStartMs = nowMs;
            g_BurstWindowPackets = 0;
            g_BurstWindowBytes = 0;
        }
        ++g_BurstWindowPackets;
        g_BurstWindowBytes += bytes;
        ++g_BurstTotalPackets;
        g_BurstTotalBytes += bytes;

        if (nowMs - g_BurstLastReportMs >= kBurstReportMs)
        {
            g_BurstLastReportMs = nowMs;
            report = true;
            peakPps = g_BurstPeakPps;
            peakBps = g_BurstPeakBps;
            burstSeconds = g_BurstSeconds;
            totalPackets = g_BurstTotalPackets;
            totalBytes = g_BurstTotalBytes;
        }
        ReleaseSRWLockExclusive(&g_BurstLock);

        if (report)
        {
            Logf("[OpenShimNet] send_burst: packets=%llu bytes=%llu peakPps=%u peakBps=%u burstSeconds=%llu threshold=%u",
                static_cast<unsigned long long>(totalPackets),
                static_cast<unsigned long long>(totalBytes),
                peakPps,
                peakBps,
                static_cast<unsigned long long>(burstSeconds),
                kBurstThresholdPps);
        }
    }

    // Close the trailing window and emit the session totals. A burst that ends
    // the traffic -- exactly the case worth catching -- would otherwise never
    // have its window accounted, and the peak would read low or zero.
    void LogOutboundBurstSummary()
    {
        AcquireSRWLockExclusive(&g_BurstLock);
        if (g_BurstWindowPackets > g_BurstPeakPps)
            g_BurstPeakPps = g_BurstWindowPackets;
        if (g_BurstWindowBytes > g_BurstPeakBps)
            g_BurstPeakBps = g_BurstWindowBytes;
        if (g_BurstWindowPackets > kBurstThresholdPps)
            ++g_BurstSeconds;
        g_BurstWindowPackets = 0;
        g_BurstWindowBytes = 0;
        const uint32_t peakPps = g_BurstPeakPps;
        const uint32_t peakBps = g_BurstPeakBps;
        const uint64_t burstSeconds = g_BurstSeconds;
        const uint64_t totalPackets = g_BurstTotalPackets;
        const uint64_t totalBytes = g_BurstTotalBytes;
        ReleaseSRWLockExclusive(&g_BurstLock);

        if (totalPackets == 0)
            return;

        Logf("[OpenShimNet] send_burst session: packets=%llu bytes=%llu peakPps=%u peakBps=%u burstSeconds=%llu",
            static_cast<unsigned long long>(totalPackets),
            static_cast<unsigned long long>(totalBytes),
            peakPps,
            peakBps,
            static_cast<unsigned long long>(burstSeconds));
    }

    void CALLBACK RelayCaptureCompletionRoutine(
        DWORD error,
        DWORD transferredLength,
        LPWSAOVERLAPPED overlapped,
        DWORD flags)
    {
        PendingCaptureIo pending = {};
        LPWSAOVERLAPPED_COMPLETION_ROUTINE original = nullptr;
        if (TakePendingCaptureIo(overlapped, pending))
        {
            original = pending.originalCompletionRoutine;
            CaptureCompletedIo(pending, transferredLength, error);
        }
        if (original)
            original(error, transferredLength, overlapped, flags);
    }

    BOOL WINAPI Hook_GetQueuedCompletionStatus(
        HANDLE completionPort,
        LPDWORD transferredLength,
        PULONG_PTR completionKey,
        LPOVERLAPPED* overlapped,
        DWORD milliseconds)
    {
        const BOOL rc = g_RealGetQueuedCompletionStatus(
            completionPort,
            transferredLength,
            completionKey,
            overlapped,
            milliseconds);
        const DWORD error = rc ? ERROR_SUCCESS : GetLastError();
        if (overlapped && *overlapped)
        {
            HandleCompletedCaptureIo(
                *overlapped,
                transferredLength ? *transferredLength : 0,
                error);
        }
        if (!rc)
            SetLastError(error);
        return rc;
    }

    void DupPurgeSocket(SOCKET s)
    {
        AcquireSRWLockExclusive(&g_DupLock);
        uint32_t kept = 0;
        for (uint32_t i = 0; i < g_DupCount; ++i)
        {
            const uint32_t idx = (g_DupHead + i) % kDupQueueSlots;
            if (g_DupQueue[idx].socket == s)
                continue;
            if (kept != i)
                g_DupQueue[(g_DupHead + kept) % kDupQueueSlots] = g_DupQueue[idx];
            ++kept;
        }
        g_DupCount = kept;
        ReleaseSRWLockExclusive(&g_DupLock);
    }

    void DupEnqueue(SOCKET s, const uint8_t* data, uint32_t length, const sockaddr* to, int toLen)
    {
        if (!g_Config.sendDup || !data || length == 0 || length > kReorderMaxPacketBytes ||
            !to || toLen <= 0 || static_cast<size_t>(toLen) > sizeof(sockaddr_storage) ||
            IsLoopbackDestination(to))
        {
            return;
        }

        if (g_Config.dupDelayMs == 0)
        {
            if (g_RealSendTo)
                g_RealSendTo(s, reinterpret_cast<const char*>(data), static_cast<int>(length), 0, to, toLen);
            return;
        }

        const uint64_t now = GetTickCount64();
        AcquireSRWLockExclusive(&g_DupLock);
        if (now - g_DupBucketStartMs >= 1000)
        {
            g_DupBucketStartMs = now;
            g_DupBucketSent = 0;
        }

        if ((g_Config.dupMaxPps != 0 && g_DupBucketSent >= g_Config.dupMaxPps) ||
            g_DupCount >= kDupQueueSlots)
        {
            ReleaseSRWLockExclusive(&g_DupLock);
            return;
        }

        DupEntry& entry = g_DupQueue[(g_DupHead + g_DupCount) % kDupQueueSlots];
        entry.socket = s;
        entry.dueMs = now + g_Config.dupDelayMs;
        entry.toLen = toLen;
        entry.length = length;
        std::memcpy(&entry.to, to, static_cast<size_t>(toLen));
        std::memcpy(entry.data, data, length);
        ++g_DupCount;
        ++g_DupBucketSent;
        ReleaseSRWLockExclusive(&g_DupLock);
    }

    DWORD WINAPI DupPacerThread(LPVOID)
    {
        while (InterlockedCompareExchange(&g_DupStop, 0, 0) == 0)
        {
            Sleep(kDupTickMs);
            if (!g_RealSendTo)
                continue;

            for (;;)
            {
                DupEntry local = {};
                AcquireSRWLockExclusive(&g_DupLock);
                if (g_DupCount == 0 || g_DupQueue[g_DupHead].dueMs > GetTickCount64())
                {
                    ReleaseSRWLockExclusive(&g_DupLock);
                    break;
                }

                local = g_DupQueue[g_DupHead];
                g_DupHead = (g_DupHead + 1) % kDupQueueSlots;
                --g_DupCount;
                ReleaseSRWLockExclusive(&g_DupLock);

                g_RealSendTo(local.socket, reinterpret_cast<const char*>(local.data),
                    static_cast<int>(local.length), 0,
                    reinterpret_cast<const sockaddr*>(&local.to), local.toLen);
            }
        }
        return 0;
    }

    bool FindExeSection(const char* sectionName, uint8_t** outBase, size_t* outSize)
    {
        if (!sectionName || !outBase || !outSize)
            return false;

        HMODULE exe = GetModuleHandleA(nullptr);
        auto* base = reinterpret_cast<uint8_t*>(exe);
        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
        if (!base || dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;

        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;

        auto* section = IMAGE_FIRST_SECTION(nt);
        for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
        {
            char name[9] = {};
            std::memcpy(name, section->Name, 8);
            if (std::strcmp(name, sectionName) == 0)
            {
                *outBase = base + section->VirtualAddress;
                *outSize = section->Misc.VirtualSize ? section->Misc.VirtualSize : section->SizeOfRawData;
                return true;
            }
        }
        return false;
    }

    int CountGovernorSignatureMatches()
    {
        uint8_t* text = nullptr;
        size_t textSize = 0;
        if (!FindExeSection(".text", &text, &textSize))
            return -1;

        int matches = 0;
        for (size_t i = 0; i + sizeof(kGovSig) <= textSize; ++i)
        {
            if (std::memcmp(text + i, kGovSig, sizeof(kGovSig)) == 0)
            {
                ++matches;
                if (matches > 1)
                    break;
            }
        }
        return matches;
    }

    DWORD WINAPI GovernorScanThread(LPVOID)
    {
        Sleep(15000);

        uint8_t* text = nullptr;
        size_t textSize = 0;
        if (!FindExeSection(".text", &text, &textSize))
        {
            Logf("[OpenShimNet] governor_scan: .text section not found");
            return 0;
        }

        Logf("[OpenShimNet] governor_scan: scanning .text base=%p size=%u for 0x00000FA0",
            text,
            static_cast<unsigned>(textSize));

        const uint8_t pat[4] = { 0xA0, 0x0F, 0x00, 0x00 };
        int hits = 0;
        constexpr int kMaxHits = 48;
        for (size_t i = 0; i + sizeof(pat) <= textSize && hits < kMaxHits; ++i)
        {
            if (std::memcmp(text + i, pat, sizeof(pat)) != 0)
                continue;

            char ctx[64] = {};
            int written = 0;
            const size_t start = (i >= 3) ? i - 3 : 0;
            const size_t end = (std::min)(i + 8, textSize);
            for (size_t k = start; k < end && written < static_cast<int>(sizeof(ctx)) - 4; ++k)
                written += _snprintf_s(ctx + written, sizeof(ctx) - static_cast<size_t>(written), _TRUNCATE, "%02x ", text[k]);

            Logf("[OpenShimNet] governor_scan: hit #%d va=0x%08lX bytes[%s]",
                hits + 1,
                static_cast<unsigned long>(reinterpret_cast<uintptr_t>(text + i)),
                ctx);
            ++hits;
        }
        Logf("[OpenShimNet] governor_scan: done hits=%d%s", hits, hits >= kMaxHits ? " capped" : "");
        return 0;
    }

    DWORD WINAPI GovernorPatchThread(LPVOID)
    {
        if (g_Config.govStart == 0)
            return 0;

        Sleep(15000);
        if (InterlockedCompareExchange(&g_GovStop, 0, 0) != 0)
            return 0;

        const int matches = CountGovernorSignatureMatches();
        if (matches != 1)
        {
            Logf("[OpenShimNet] governor_patch: %d signature matches; disabled", matches);
            return 0;
        }

        Logf("[OpenShimNet] governor_patch: version confirmed; watching 0x%08lX coldStart=%u target=%u",
            static_cast<unsigned long>(reinterpret_cast<uintptr_t>(kGovRateAddr)),
            kGovColdStart,
            g_Config.govStart);

        uint32_t bumps = 0;
        uint32_t rescues = 0;
        uint32_t peak = 0;
        uint32_t windowMin = 0xFFFFFFFFu;
        uint32_t windowMax = 0;
        uint32_t windowSamples = 0;
        uint32_t lastObserved = *kGovRateAddr;
        // The value held before the most recent change, and how long it was held
        // for. The poll runs ~20x faster than the governor adjusts, so comparing
        // against the previous poll alone would see "unchanged" almost every time
        // and lose the arrival that classifies a sentinel read.
        uint32_t previousDistinct = lastObserved;
        uint64_t lastChangeMs = GetTickCount64();
        uint64_t previousHoldMs = 0;
        uint64_t lastRescueMs = 0;
        uint64_t lastObservationLogMs = GetTickCount64();
        InterlockedExchange(&g_GovLastObserved, static_cast<LONG>(lastObserved));
        InterlockedExchange(&g_GovObservationValid, 1);
        InterlockedExchange(&g_GovBumps, 0);
        Logf("[OpenShimNet] governor_patch: initial observed=%u target=%u descentBand=%u descentMs=%u",
            lastObserved,
            g_Config.govStart,
            kGovDescentBand,
            kGovDescentMs);

        while (InterlockedCompareExchange(&g_GovStop, 0, 0) == 0)
        {
            const uint64_t nowMs = GetTickCount64();
            const uint32_t observed = *kGovRateAddr;
            const uint32_t previousPoll = lastObserved;

            if (observed != previousPoll)
            {
                previousDistinct = previousPoll;
                previousHoldMs = nowMs - lastChangeMs;
                lastChangeMs = nowMs;
            }
            if (observed > peak)
                peak = observed;
            if (observed < windowMin)
                windowMin = observed;
            if (observed > windowMax)
                windowMax = observed;
            ++windowSamples;

            // Was the sentinel WRITTEN here (a match start) or WALKED onto (the
            // governor collapsing to its floor mid-match)? `arrivedFrom` is the
            // value immediately before this one: the previous poll if it
            // differed, otherwise the value held before the most recent change,
            // which is what a run of identical polls sitting on the floor sees.
            bool descentArrival = false;
            if (observed == kGovColdStart)
            {
                const uint32_t arrivedFrom = (observed != previousPoll) ? previousPoll : previousDistinct;
                descentArrival = arrivedFrom > kGovColdStart &&
                    (arrivedFrom - kGovColdStart) <= kGovDescentBand &&
                    previousHoldMs <= kGovDescentMs;
            }

            if (observed != previousPoll)
            {
                const char* reason = observed == kGovColdStart
                    ? (descentArrival ? "governor collapsed onto its floor" : "cold-start trigger")
                    : (observed == g_Config.govStart ? "target restored" : "game overwrite or clamp");
                Logf("[OpenShimNet] governor_patch: observed transition %u -> %u reason=%s heldMs=%llu",
                    previousPoll,
                    observed,
                    reason,
                    static_cast<unsigned long long>(previousHoldMs));
                lastObserved = observed;
                InterlockedExchange(&g_GovLastObserved, static_cast<LONG>(observed));
            }

            // A floor rescue still writes the target -- with the game's own floor
            // at 4000 the alternative is a match that spends the rest of its life
            // at 4 kB/s -- but it is rate-limited and counted apart from real
            // match starts, because counting them together is what put 32
            // "matches" into an evening that had three.
            const bool rescueDue = descentArrival &&
                (rescues == 0 || (nowMs - lastRescueMs) >= kGovDescentMs);

            if (observed == kGovColdStart && (!descentArrival || rescueDue))
            {
                *kGovRateAddr = g_Config.govStart;
                const uint32_t readback = *kGovRateAddr;
                if (descentArrival)
                {
                    ++rescues;
                    lastRescueMs = nowMs;
                }
                else
                {
                    ++bumps;
                    InterlockedExchange(&g_GovBumps, static_cast<LONG>(bumps));
                }
                lastObserved = readback;
                previousDistinct = kGovColdStart;
                previousHoldMs = 0;
                lastChangeMs = nowMs;
                lastObservationLogMs = nowMs;
                InterlockedExchange(&g_GovLastObserved, static_cast<LONG>(readback));
                Logf("[OpenShimNet] governor_patch: applied %s previous=%u requested=%u readback=%u bumps=%u rescues=%u",
                    descentArrival ? "floor-rescue" : "cold-start",
                    observed,
                    g_Config.govStart,
                    readback,
                    bumps,
                    rescues);
            }
            else if (nowMs - lastObservationLogMs >= kGovObservationLogMs)
            {
                Logf("[OpenShimNet] governor_trace: observed=%u target=%u windowMin=%u windowMax=%u samples=%u peak=%u bumps=%u rescues=%u",
                    observed,
                    g_Config.govStart,
                    windowSamples ? windowMin : 0u,
                    windowMax,
                    windowSamples,
                    peak,
                    bumps,
                    rescues);
                lastObservationLogMs = nowMs;
                windowMin = 0xFFFFFFFFu;
                windowMax = 0;
                windowSamples = 0;
            }

            Sleep(kGovPollMs);
        }

        const LONG finalObserved = InterlockedCompareExchange(&g_GovLastObserved, 0, 0);
        Logf("[OpenShimNet] governor_patch: thread exit bumps=%u rescues=%u peak=%u finalObserved=%ld target=%u",
            bumps,
            rescues,
            peak,
            static_cast<long>(finalObserved),
            g_Config.govStart);
        return 0;
    }

    // Re-asserts the [Net] tunables the game parses out of net.ini at every match
    // start. Named for what it now covers: it began as the auto-kick-only patch
    // and the four auto-kick INI keys are unchanged.
    DWORD WINAPI NetGlobalsPatchThread(LPVOID)
    {
        struct Slot
        {
            const NetGlobalDef* def;
            uint32_t want;
            uint32_t seen;
            bool gated;
            bool vetoed;
        };

        Slot slots[kNgCount] =
        {
            { &kNetGlobals[kNgMinBandwidth], g_Config.netMinBandwidth, 0, false, false },
            { &kNetGlobals[kNgMaxBandwidth], g_Config.netMaxBandwidth, 0, false, false },
            { &kNetGlobals[kNgUpCount],      g_Config.netUpCount,      0, false, false },
            { &kNetGlobals[kNgDownCount],    g_Config.netDownCount,    0, false, false },
            { &kNetGlobals[kNgMaxPing],      g_Config.netMaxPing,      0, false, false },
            { &kNetGlobals[kNgMaxPingsLost], g_Config.netMaxPingsLost, 0, false, false },
            { &kNetGlobals[kNgAutoKickStart], g_Config.autoKickStart,  0, false, false },
            { &kNetGlobals[kNgAutoKickPing],  g_Config.autoKickPing,   0, false, false },
            { &kNetGlobals[kNgAutoKickLoss],  g_Config.autoKickLoss,   0, false, false },
            { &kNetGlobals[kNgAutoKickTime],  g_Config.autoKickTime,   0, false, false },
        };

        // Never write something the sanity gate would reject on read-back anyway:
        // a configured value outside the plausible range would veto the entry on
        // the very next poll and produce a confusing pair of log lines.
        bool anyWanted = false;
        for (Slot& slot : slots)
        {
            if (slot.want == 0)
                continue;
            if (slot.want < slot.def->plausibleMin || slot.want > slot.def->plausibleMax)
            {
                Logf("[OpenShimNet] net_globals: %s=%u outside the plausible range %u..%u; ignoring",
                    slot.def->name,
                    slot.want,
                    slot.def->plausibleMin,
                    slot.def->plausibleMax);
                slot.want = 0;
                continue;
            }
            anyWanted = true;
        }
        if (!anyWanted)
            return 0;

        Sleep(15000);
        const int matches = CountGovernorSignatureMatches();
        if (matches != 1)
        {
            Logf("[OpenShimNet] net_globals: %d signature matches; disabled", matches);
            return 0;
        }

        Logf("[OpenShimNet] net_globals: version confirmed; asserting "
            "MinBandwidth=%u MaxBandwidth=%u UpCount=%u DownCount=%u MaxPing=%u MaxPingsLost=%u "
            "AutoKickStart=%u AutoKickPing=%u AutoKickLoss=%u AutoKickTime=%u (0 = leave alone)",
            slots[kNgMinBandwidth].want,
            slots[kNgMaxBandwidth].want,
            slots[kNgUpCount].want,
            slots[kNgDownCount].want,
            slots[kNgMaxPing].want,
            slots[kNgMaxPingsLost].want,
            slots[kNgAutoKickStart].want,
            slots[kNgAutoKickPing].want,
            slots[kNgAutoKickLoss].want,
            slots[kNgAutoKickTime].want);

        while (InterlockedCompareExchange(&g_AutoKickStop, 0, 0) == 0)
        {
            for (Slot& slot : slots)
            {
                if (slot.want == 0 || slot.vetoed)
                    continue;

                uint32_t* const address = reinterpret_cast<uint32_t*>(slot.def->address);
                const uint32_t live = *address;

                if (!slot.gated)
                {
                    // First contact. If the game is not holding a plausible value
                    // for this tunable, the address is not what we think it is on
                    // this build -- refuse to write rather than corrupt whatever
                    // it really is.
                    slot.gated = true;
                    slot.seen = live;
                    if (live < slot.def->plausibleMin || live > slot.def->plausibleMax)
                    {
                        slot.vetoed = true;
                        Logf("[OpenShimNet] net_globals: %s vetoed; 0x%08lX holds %u, outside %u..%u",
                            slot.def->name,
                            static_cast<unsigned long>(slot.def->address),
                            live,
                            slot.def->plausibleMin,
                            slot.def->plausibleMax);
                        continue;
                    }
                    Logf("[OpenShimNet] net_globals: %s %u -> %u (as found at 0x%08lX)",
                        slot.def->name,
                        live,
                        slot.want,
                        static_cast<unsigned long>(slot.def->address));
                }

                if (live != slot.want)
                    *address = slot.want;
            }
            Sleep(kGovPollMs);
        }

        Logf("[OpenShimNet] net_globals: stopping");
        return 0;
    }

    bool ProcessReceivedDatagram(
        SOCKET s,
        LPWSABUF buffers,
        DWORD bufferCount,
        LPDWORD bytesRecv,
        LPDWORD flags,
        sockaddr* from,
        LPINT fromLen,
        const sockaddr_in& packetSource,
        const uint8_t* packetData,
        uint32_t packetLength,
        uint32_t& outDelivered,
        sockaddr_in& outDeliveredSource)
    {
        outDelivered = 0;
        std::memset(&outDeliveredSource, 0, sizeof(outDeliveredSource));

        if (packetSource.sin_family != AF_INET || packetLength < kReorderSeqMinPayloadBytes)
        {
            outDeliveredSource = packetSource;
            outDelivered = CopyPacketToCaller(buffers, bufferCount, bytesRecv, flags, from, fromLen, packetData, packetLength, &packetSource);
            LogReorderf("[OpenShimNet] sid=%u reorder bypass immediate sock=0x%08X peer=%s family=%d bytes=%u",
                GetSocketId(s),
                static_cast<unsigned>(s),
                FormatIpv4Peer(packetSource).c_str(),
                static_cast<int>(packetSource.sin_family),
                packetLength);
            return true;
        }

        uint32_t sequence = 0;
        std::memcpy(&sequence, packetData + kReorderSeqOffset, sizeof(sequence));

        AcquireSRWLockExclusive(&g_ReorderLock);
        PeerBuf* peer = FindOrCreatePeerBufLocked(s, packetSource);
        if (!peer)
        {
            ReleaseSRWLockExclusive(&g_ReorderLock);
            outDeliveredSource = packetSource;
            outDelivered = CopyPacketToCaller(buffers, bufferCount, bytesRecv, flags, from, fromLen, packetData, packetLength, &packetSource);
            LogReorderf("[OpenShimNet] sid=%u reorder fallback immediate sock=0x%08X peer=%s seq=%u bytes=%u reason=peer_table_full",
                GetSocketId(s),
                static_cast<unsigned>(s),
                FormatIpv4Peer(packetSource).c_str(),
                sequence,
                packetLength);
            return true;
        }

        const uint64_t arrivalMs = GetTickCount64();
        AdaptReorderWindowOnArrival(*peer, sequence, arrivalMs);
        InsertPacketLocked(*peer, sequence, arrivalMs, packetSource, packetData, packetLength);
        ReleaseSRWLockExclusive(&g_ReorderLock);

        return false;
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

    int ConfiguredSocketBufferFloor(int level, int optName)
    {
        if (!g_Config.applySocketBuffers || level != SOL_SOCKET)
            return 0;

        if (optName == SO_SNDBUF)
            return static_cast<int>(g_Config.sendBufferSize);
        if (optName == SO_RCVBUF)
            return static_cast<int>(g_Config.recvBufferSize);
        return 0;
    }

    int ReassertSocketBufferFloor(SOCKET s, int level, int optName, int requested, int readback)
    {
        const int floor = ConfiguredSocketBufferFloor(level, optName);
        if (floor <= 0)
            return readback;

        const bool belowFloor = (readback >= 0 && readback < floor) ||
            (requested > 0 && requested < floor);
        if (!belowFloor)
            return readback;

        const int savedErr = g_RealWSAGetLastError ? g_RealWSAGetLastError() : 0;
        SetSocketIntOption(s, level, optName, floor, SockOptName(level, optName));
        const int finalReadback = QuerySocketInt(s, level, optName);
        Logf("[OpenShimNet] sid=%u reasserted %s floor on sock=0x%08X requested=%d initialReadback=%d floor=%d finalReadback=%d",
            GetSocketId(s),
            SockOptName(level, optName),
            static_cast<unsigned>(s),
            requested,
            readback,
            floor,
            finalReadback);
        if (g_RealWSASetLastError)
            g_RealWSASetLastError(savedErr);
        return finalReadback;
    }

    int ApplyDscpToSocket(SOCKET s)
    {
        if (g_Config.dscp == 0 || !g_RealSetSockOpt || !IsUdpSocket(s))
            return 0;

        const int tos = static_cast<int>((g_Config.dscp & 0x3Fu) << 2);
        const int rc = g_RealSetSockOpt(s, IPPROTO_IP, IP_TOS, reinterpret_cast<const char*>(&tos), sizeof(tos));
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        Logf("[OpenShimNet] sid=%u DSCP=%u IP_TOS=%d sock=0x%08X rc=%d err=%d",
            GetSocketId(s),
            g_Config.dscp,
            tos,
            static_cast<unsigned>(s),
            rc,
            err);
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
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

        if ((state.type == SOCK_DGRAM || state.protocol == IPPROTO_UDP) && state.af == AF_INET)
            ApplyDscpToSocket(s);

        if ((state.type == SOCK_STREAM || state.protocol == IPPROTO_TCP) && g_Config.tcpNoDelay)
            SetSocketIntOption(s, IPPROTO_TCP, TCP_NODELAY, 1, "TCP_NODELAY");

        if ((state.type == SOCK_STREAM || state.protocol == IPPROTO_TCP) && g_Config.keepAlive)
            SetSocketIntOption(s, SOL_SOCKET, SO_KEEPALIVE, 1, "SO_KEEPALIVE");

        MaybeDisableUdpConnReset(s, state);
        RefreshSocketAddresses(s);
        MarkSocketOptimized(s);
    }

    void LogSocketError(const char* api, SOCKET s, int rc, int SocketState::*lastErrorField)
    {
        if (rc != SOCKET_ERROR || !g_Config.logSocketErrors || !g_RealWSAGetLastError)
            return;

        const int err = g_RealWSAGetLastError();
        if (err == WSAEWOULDBLOCK || err == WSA_IO_PENDING || err == ERROR_IO_PENDING)
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
            Logf("[OpenShimNet] sid=%u %s failed on socket 0x%08X (err=%d)",
                GetSocketId(s),
                api,
                static_cast<unsigned>(s),
                err);

        if (g_RealWSASetLastError)
            g_RealWSASetLastError(err);
    }

    INT WSAAPI Hook_getaddrinfo(
        PCSTR nodeName,
        PCSTR serviceName,
        const ADDRINFOA* hints,
        PADDRINFOA* result)
    {
        PCSTR resolvedNode = nodeName;
        if (nodeName &&
            !g_Config.matchmakingRedirectAddress.empty() &&
            _stricmp(nodeName, kBzrNetMatchmakingHost) == 0)
        {
            resolvedNode = g_Config.matchmakingRedirectAddress.c_str();
            Logf("[OpenShimNet] Redirecting BZRNet lookup %s -> %s",
                nodeName,
                resolvedNode);
        }

        return g_RealGetAddrInfoA(resolvedNode, serviceName, hints, result);
    }

    SOCKET WSAAPI Hook_socket(int af, int type, int protocol)
    {
        const SocketFn dispatch = g_DispatchSocket ? g_DispatchSocket : g_RealSocket;
        const SOCKET s = dispatch(af, type, protocol);
        if (s == INVALID_SOCKET)
        {
            const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : 0;
            Logf("[OpenShimNet] socket failed (af=%d type=%d proto=%d err=%d)", af, type, protocol, err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
            return s;
        }

        const uint32_t socketId = RememberSocket(s, af, type, protocol);
        Logf("[OpenShimNet] sid=%u socket created socket=0x%08X af=%d type=%d proto=%d", socketId, static_cast<unsigned>(s), af, type, protocol);
        EnsureSocketOptions(s);
        return s;
    }

    SOCKET WSAAPI Hook_WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW protocolInfo, GROUP group, DWORD flags)
    {
        const WSASocketWFn dispatch = g_DispatchWSASocketW ? g_DispatchWSASocketW : g_RealWSASocketW;
        const SOCKET s = dispatch(af, type, protocol, protocolInfo, group, flags);
        if (s == INVALID_SOCKET)
        {
            const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : 0;
            Logf("[OpenShimNet] WSASocketW failed (af=%d type=%d proto=%d err=%d)", af, type, protocol, err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
            return s;
        }

        const uint32_t socketId = RememberSocket(s, af, type, protocol);
        Logf("[OpenShimNet] sid=%u WSASocketW created socket 0x%08X (af=%d type=%d proto=%d flags=0x%08X)",
            socketId, static_cast<unsigned>(s), af, type, protocol, static_cast<unsigned>(flags));
        EnsureSocketOptions(s);
        return s;
    }

    int WSAAPI Hook_bind(SOCKET s, const sockaddr* name, int namelen)
    {
        const int rc = g_RealBind(s, name, namelen);
        if (rc == 0)
        {
            LogSocketLifecycleEvent("bind", s, name, namelen);
        }
        else if (g_Config.logSocketErrors && g_RealWSAGetLastError)
        {
            const int err = g_RealWSAGetLastError();
            Logf("[OpenShimNet] sid=%u bind failed sock=0x%08X addr=%s err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                FormatSockaddr(name, namelen).c_str(),
                err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
        }
        return rc;
    }

    int WSAAPI Hook_connect(SOCKET s, const sockaddr* name, int namelen)
    {
        const int rc = g_RealConnect(s, name, namelen);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (rc == 0)
        {
            LogSocketLifecycleEvent("connect", s, name, namelen);
            LogRouteEvent("connect", s, name, namelen, true, 0, false);
        }
        else if (g_Config.logSocketErrors && g_RealWSAGetLastError)
        {
            LogRouteEvent("connect", s, name, namelen, false, err, false);
            Logf("[OpenShimNet] sid=%u connect %s sock=0x%08X addr=%s err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                IsPendingConnectError(err) ? "pending" : "failed",
                FormatSockaddr(name, namelen).c_str(),
                err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
        }
        return rc;
    }

    int WSAAPI Hook_WSAConnect(SOCKET s, const sockaddr* name, int namelen, LPWSABUF callerData, LPWSABUF calleeData, LPQOS sqos, LPQOS gqos)
    {
        const int rc = g_RealWSAConnect(s, name, namelen, callerData, calleeData, sqos, gqos);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (rc == 0)
        {
            LogSocketLifecycleEvent("WSAConnect", s, name, namelen);
            LogRouteEvent("WSAConnect", s, name, namelen, true, 0, false);
        }
        else if (g_Config.logSocketErrors && g_RealWSAGetLastError)
        {
            LogRouteEvent("WSAConnect", s, name, namelen, false, err, false);
            Logf("[OpenShimNet] sid=%u WSAConnect %s sock=0x%08X addr=%s err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                IsPendingConnectError(err) ? "pending" : "failed",
                FormatSockaddr(name, namelen).c_str(),
                err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
        }
        return rc;
    }

    int WSAAPI Hook_closesocket(SOCKET s)
    {
        const int rc = g_RealCloseSocket(s);
        if (rc == 0)
        {
            PurgeWebSocketCaptureForSocket(s);
            ClearReorderStateForSocket(s);
            DupPurgeSocket(s);
            LogSocketSummaryAndForget(s);
        }
        else if (g_Config.logSocketErrors && g_RealWSAGetLastError)
        {
            const int err = g_RealWSAGetLastError();
            Logf("[OpenShimNet] sid=%u closesocket failed sock=0x%08X err=%d", GetSocketId(s), static_cast<unsigned>(s), err);
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
        }
        return rc;
    }

    int WSAAPI Hook_WSASend(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesSent, DWORD flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSASend(s, buffers, bufferCount, bytesSent, flags, overlapped, completionRoutine);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (g_Config.enableRelayCapture &&
            (rc == 0 || err == WSA_IO_PENDING) &&
            IsWebSocketControlSocket(s))
        {
            const uint32_t requested = GetRequestedWsabufBytes(buffers, bufferCount);
            const uint32_t accepted = (rc == 0 && bytesSent && *bytesSent > 0) ? *bytesSent : requested;
            std::vector<uint8_t> payload((std::min)(accepted, kRelayCaptureMaxWebSocketBytes));
            const uint32_t copied = payload.empty()
                ? 0
                : GatherWsabufPayload(buffers, bufferCount, payload.data(), static_cast<uint32_t>(payload.size()));
            if (copied > 0)
                FeedWebSocketCapture(s, true, payload.data(), copied);
        }
        if (rc == 0 && bytesSent)
            LogPacketActivity("WSASend", s, true, static_cast<int>(*bytesSent), nullptr, 0);
        LogSocketError("WSASend", s, rc, &SocketState::lastSendError);
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_WSARecv(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesRecv, LPDWORD flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const bool pendingRegistered = RegisterPendingCaptureIo(
            overlapped,
            PendingIoKind::WSARecv,
            s,
            buffers,
            bufferCount,
            nullptr,
            nullptr,
            completionRoutine);
        const auto effectiveCompletion = pendingRegistered && completionRoutine
            ? RelayCaptureCompletionRoutine
            : completionRoutine;
        const int rc = g_RealWSARecv(s, buffers, bufferCount, bytesRecv, flags, overlapped, effectiveCompletion);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (rc == 0 && bytesRecv && *bytesRecv > 0)
        {
            std::vector<uint8_t> payload((std::min)(static_cast<uint32_t>(*bytesRecv), kRelayCaptureMaxWebSocketBytes));
            const uint32_t copied = GatherWsabufPayload(
                buffers,
                bufferCount,
                payload.data(),
                static_cast<uint32_t>(payload.size()));
            if (copied > 0)
                FeedWebSocketCapture(s, false, payload.data(), copied);
            if (pendingRegistered)
                MarkPendingCaptureImmediate(overlapped);
        }
        else if (pendingRegistered && err != WSA_IO_PENDING)
        {
            CancelPendingCaptureIo(overlapped);
        }
        if (rc == 0 && bytesRecv)
            LogPacketActivity("WSARecv", s, false, static_cast<int>(*bytesRecv), nullptr, 0);
        LogSocketError("WSARecv", s, rc, &SocketState::lastRecvError);
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_WSASendTo(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesSent, DWORD flags, const sockaddr* to, int toLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealWSASendTo(s, buffers, bufferCount, bytesSent, flags, to, toLen, overlapped, completionRoutine);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (IsUdpSocket(s) && !IsLoopbackDestination(to))
            MeasureOutboundBurst(GetRequestedWsabufBytes(buffers, bufferCount));
        if (g_BufferLogEnabled && IsUdpSocket(s) && (rc == 0 || err == WSA_IO_PENDING))
        {
            uint8_t capture[kRelayCapturePayloadBytes] = {};
            const uint32_t requested = GetRequestedWsabufBytes(buffers, bufferCount);
            const uint32_t copied = GatherWsabufPayload(buffers, bufferCount, capture, g_Config.bufferLogPayloadBytes);
            BufferLogEvent(
                kBufferLogEventWSASendTo,
                s,
                to,
                static_cast<uint16_t>(flags & 0xFFFFu),
                requested,
                rc == 0 && bytesSent ? *bytesSent : requested,
                static_cast<uint32_t>(err),
                copied > 0 ? capture : nullptr,
                static_cast<uint16_t>(copied));
        }
        if (rc == 0 && bytesSent)
        {
            LogPacketActivity("WSASendTo", s, true, static_cast<int>(*bytesSent), to, toLen);
            LogRouteEvent("WSASendTo", s, to, toLen, true, 0, true);
            uint8_t dupData[kReorderMaxPacketBytes] = {};
            const uint32_t dupLength = GatherWsabufPayload(buffers, bufferCount, dupData, kReorderMaxPacketBytes);
            if (dupLength > 0)
                DupEnqueue(s, dupData, dupLength, to, toLen);
        }
        else if (rc == SOCKET_ERROR)
        {
            LogRouteEvent("WSASendTo", s, to, toLen, false, err, true);
        }
        LogSocketError("WSASendTo", s, rc, &SocketState::lastSendToError);
        return rc;
    }

    int WSAAPI Hook_send(SOCKET s, const char* buffer, int length, int flags)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealSend(s, buffer, length, flags);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (rc > 0 && buffer)
            FeedWebSocketCapture(s, true, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc));
        if (rc >= 0)
            LogPacketActivity("send", s, true, rc, nullptr, 0);
        LogSocketError("send", s, rc == SOCKET_ERROR ? SOCKET_ERROR : 0, &SocketState::lastSendError);
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_recv(SOCKET s, char* buffer, int length, int flags)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealRecv(s, buffer, length, flags);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (rc > 0 && buffer)
            FeedWebSocketCapture(s, false, reinterpret_cast<const uint8_t*>(buffer), static_cast<size_t>(rc));
        if (rc >= 0)
            LogPacketActivity("recv", s, false, rc, nullptr, 0);
        LogSocketError("recv", s, rc == SOCKET_ERROR ? SOCKET_ERROR : 0, &SocketState::lastRecvError);
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_sendto(SOCKET s, const char* buffer, int length, int flags, const sockaddr* to, int toLen)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealSendTo(s, buffer, length, flags, to, toLen);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (IsUdpSocket(s) && !IsLoopbackDestination(to))
            MeasureOutboundBurst(length > 0 ? static_cast<uint32_t>(length) : 0);
        if (g_BufferLogEnabled && IsUdpSocket(s) && buffer && rc > 0)
        {
            const uint16_t captured = static_cast<uint16_t>((std::min)(
                static_cast<uint32_t>(rc),
                g_Config.bufferLogPayloadBytes));
            BufferLogEvent(
                kBufferLogEventSendTo,
                s,
                to,
                static_cast<uint16_t>(flags & 0xFFFFu),
                length > 0 ? static_cast<uint32_t>(length) : 0,
                static_cast<uint32_t>(rc),
                0,
                reinterpret_cast<const uint8_t*>(buffer),
                captured);
        }
        if (rc != SOCKET_ERROR)
        {
            LogPacketActivity("sendto", s, true, rc, to, toLen);
            LogRouteEvent("sendto", s, to, toLen, true, 0, true);
            if (buffer && rc > 0)
                DupEnqueue(s, reinterpret_cast<const uint8_t*>(buffer), static_cast<uint32_t>((std::min)(rc, static_cast<int>(kReorderMaxPacketBytes))), to, toLen);
        }
        else
        {
            LogRouteEvent("sendto", s, to, toLen, false, err, true);
        }
        LogSocketError("sendto", s, rc, &SocketState::lastSendToError);
        return rc;
    }

    uint32_t GetRequestedWsabufBytes(LPWSABUF buffers, DWORD bufferCount)
    {
        uint32_t total = 0;
        if (!buffers)
            return 0;

        for (DWORD i = 0; i < bufferCount; ++i)
            total += buffers[i].len;
        return total;
    }

    void CaptureRecvPathEvent(
        BufferLogEventType eventType,
        SOCKET s,
        const sockaddr* from,
        uint16_t flags,
        uint32_t requestedLength,
        uint32_t transferredLength,
        uint32_t wsaError,
        const uint8_t* payload)
    {
        if (!g_BufferLogEnabled)
            return;

        const uint16_t payloadLength = static_cast<uint16_t>((std::min)(
            transferredLength,
            g_Config.bufferLogPayloadBytes));
        BufferLogEvent(
            eventType,
            s,
            from,
            flags,
            requestedLength,
            transferredLength,
            wsaError,
            payloadLength > 0 ? payload : nullptr,
            payloadLength);
    }

    int WSAAPI Hook_WSARecvFrom(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD bytesRecv, LPDWORD flags, sockaddr* from, LPINT fromLen, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        EnsureSocketOptions(s);
        const bool canReorder =
            g_Config.enablePacketReorder &&
            IsUdpSocket(s) &&
            overlapped == nullptr &&
            completionRoutine == nullptr &&
            buffers != nullptr &&
            bufferCount > 0;

        if (!canReorder)
        {
            if (g_Config.logPacketReorder)
            {
                const char* reason = "unknown";
                if (!g_Config.enablePacketReorder)
                    reason = "disabled";
                else if (!IsUdpSocket(s))
                    reason = "not_udp";
                else if (overlapped != nullptr || completionRoutine != nullptr)
                    reason = "async";
                else if (buffers == nullptr || bufferCount == 0)
                    reason = "bad_args";

                LogReorderf("[OpenShimNet] sid=%u reorder bypass sock=0x%08X reason=%s",
                    GetSocketId(s),
                    static_cast<unsigned>(s),
                    reason);
            }

            const bool pendingRegistered = RegisterPendingCaptureIo(
                overlapped,
                PendingIoKind::WSARecvFrom,
                s,
                buffers,
                bufferCount,
                from,
                fromLen,
                completionRoutine);
            const auto effectiveCompletion = pendingRegistered && completionRoutine
                ? RelayCaptureCompletionRoutine
                : completionRoutine;
            const int rc = g_RealWSARecvFrom(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, overlapped, effectiveCompletion);
            const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
            std::vector<uint8_t> capture;
            if (rc == 0 && bytesRecv && *bytesRecv > 0)
            {
                capture.resize((std::min)(static_cast<uint32_t>(*bytesRecv), g_Config.bufferLogPayloadBytes));
                const uint32_t copied = GatherWsabufPayload(
                    buffers,
                    bufferCount,
                    capture.data(),
                    static_cast<uint32_t>(capture.size()));
                capture.resize(copied);
                if (pendingRegistered)
                    MarkPendingCaptureImmediate(overlapped);
            }
            else if (pendingRegistered && err != WSA_IO_PENDING)
            {
                CancelPendingCaptureIo(overlapped);
            }
            CaptureRecvPathEvent(
                kBufferLogEventWSARecvFrom,
                s,
                from,
                flags ? static_cast<uint16_t>(*flags & 0xFFFFu) : 0,
                GetRequestedWsabufBytes(buffers, bufferCount),
                (rc == 0 && bytesRecv) ? *bytesRecv : 0,
                static_cast<uint32_t>(err),
                capture.empty() ? nullptr : capture.data());
            if (rc == 0 && bytesRecv)
                LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(*bytesRecv), from, fromLen ? *fromLen : 0);
            LogSocketError("WSARecvFrom", s, rc, &SocketState::lastRecvFromError);
            return rc;
        }

        g_ReorderSocket = s;
        g_LastRecvCallMs = GetTickCount64();
        uint32_t delivered = 0;
        sockaddr_in deliveredSource = {};
        if (TryDeliverBufferedPacket(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, delivered, deliveredSource))
        {
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(0);
            LogReorderf("[OpenShimNet] sid=%u reorder satisfied from buffer before recv sock=0x%08X bytes=%u peer=%s",
                GetSocketId(s),
                static_cast<unsigned>(s),
                delivered,
                FormatIpv4Peer(deliveredSource).c_str());
            CaptureRecvPathEvent(
                kBufferLogEventWSARecvFrom,
                s,
                reinterpret_cast<const sockaddr*>(&deliveredSource),
                0,
                GetRequestedWsabufBytes(buffers, bufferCount),
                delivered,
                0,
                buffers && bufferCount > 0 && buffers[0].buf
                    ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                    : nullptr);
            LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
            return 0;
        }

        uint8_t packetBuffer[kReorderMaxPacketBytes] = {};
        WSABUF packetWsabuf = {};
        packetWsabuf.buf = reinterpret_cast<char*>(packetBuffer);
        packetWsabuf.len = kReorderMaxPacketBytes;

        DWORD firstBytes = 0;
        DWORD firstFlags = 0;
        sockaddr_in firstSource = {};
        int firstSourceLen = sizeof(firstSource);
        int rc = g_RealWSARecvFrom(
            s,
            &packetWsabuf,
            1,
            &firstBytes,
            &firstFlags,
            reinterpret_cast<sockaddr*>(&firstSource),
            &firstSourceLen,
            nullptr,
            nullptr);
        if (rc != 0)
        {
            const int err = g_RealWSAGetLastError ? g_RealWSAGetLastError() : WSAGetLastError();
            LogReorderf("[OpenShimNet] sid=%u reorder initial recv failed sock=0x%08X rc=%d err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                rc,
                err);
            if (err == WSAEWOULDBLOCK &&
                TryDeliverBufferedPacket(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, delivered, deliveredSource))
            {
                if (g_RealWSASetLastError)
                    g_RealWSASetLastError(0);
                LogReorderf("[OpenShimNet] sid=%u reorder late buffer deliver after wouldblock sock=0x%08X bytes=%u peer=%s",
                    GetSocketId(s),
                    static_cast<unsigned>(s),
                    delivered,
                    FormatIpv4Peer(deliveredSource).c_str());
                CaptureRecvPathEvent(
                    kBufferLogEventWSARecvFrom,
                    s,
                    reinterpret_cast<const sockaddr*>(&deliveredSource),
                    0,
                    GetRequestedWsabufBytes(buffers, bufferCount),
                    delivered,
                    0,
                    buffers && bufferCount > 0 && buffers[0].buf
                        ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                        : nullptr);
                LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
                return 0;
            }

            if (g_RealWSASetLastError)
                g_RealWSASetLastError(err);
            LogSocketError("WSARecvFrom", s, rc, &SocketState::lastRecvFromError);
            return rc;
        }

        if (IsWakePacket(packetBuffer, firstBytes, firstSource))
        {
            LogReorderf("[OpenShimNet] sid=%u reorder wake packet consumed sock=0x%08X",
                GetSocketId(s),
                static_cast<unsigned>(s));
            if (TryDeliverBufferedPacket(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, delivered, deliveredSource))
            {
                if (g_RealWSASetLastError)
                    g_RealWSASetLastError(0);
                CaptureRecvPathEvent(
                    kBufferLogEventWSARecvFrom,
                    s,
                    reinterpret_cast<const sockaddr*>(&deliveredSource),
                    0,
                    GetRequestedWsabufBytes(buffers, bufferCount),
                    delivered,
                    0,
                    buffers && bufferCount > 0 && buffers[0].buf
                        ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                        : nullptr);
                LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
                return 0;
            }

            if (g_RealWSASetLastError)
                g_RealWSASetLastError(WSAEWOULDBLOCK);
            return SOCKET_ERROR;
        }

        LogReorderf("[OpenShimNet] sid=%u reorder initial recv sock=0x%08X peer=%s bytes=%lu flags=0x%08lX",
            GetSocketId(s),
            static_cast<unsigned>(s),
            FormatIpv4Peer(firstSource).c_str(),
            static_cast<unsigned long>(firstBytes),
            static_cast<unsigned long>(firstFlags));

        if (ProcessReceivedDatagram(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, firstSource, packetBuffer, firstBytes, delivered, deliveredSource))
        {
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(0);
            LogReorderf("[OpenShimNet] sid=%u reorder delivered immediate after first recv sock=0x%08X bytes=%u peer=%s",
                GetSocketId(s),
                static_cast<unsigned>(s),
                delivered,
                FormatIpv4Peer(deliveredSource).c_str());
            CaptureRecvPathEvent(
                kBufferLogEventWSARecvFrom,
                s,
                reinterpret_cast<const sockaddr*>(&deliveredSource),
                0,
                GetRequestedWsabufBytes(buffers, bufferCount),
                delivered,
                0,
                buffers && bufferCount > 0 && buffers[0].buf
                    ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                    : nullptr);
            LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
            return 0;
        }

        uint32_t drainedPackets = 1;
        for (uint32_t drainCount = 1; drainCount < g_Config.reorderDrainCap && SocketHasQueuedReceiveData(s); ++drainCount)
        {
            DWORD drainBytes = 0;
            DWORD drainFlags = 0;
            sockaddr_in drainSource = {};
            int drainSourceLen = sizeof(drainSource);
            rc = g_RealWSARecvFrom(
                s,
                &packetWsabuf,
                1,
                &drainBytes,
                &drainFlags,
                reinterpret_cast<sockaddr*>(&drainSource),
                &drainSourceLen,
                nullptr,
                nullptr);
            if (rc != 0 || drainBytes == 0)
            {
                const int err = (rc != 0 && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
                LogReorderf("[OpenShimNet] sid=%u reorder drain stopped sock=0x%08X iteration=%u rc=%d err=%d bytes=%lu",
                    GetSocketId(s),
                    static_cast<unsigned>(s),
                    drainCount,
                    rc,
                    err,
                    static_cast<unsigned long>(drainBytes));
                break;
            }

            ++drainedPackets;
            if (IsWakePacket(packetBuffer, drainBytes, drainSource))
            {
                LogReorderf("[OpenShimNet] sid=%u reorder wake packet consumed during drain sock=0x%08X",
                    GetSocketId(s),
                    static_cast<unsigned>(s));
                continue;
            }
            LogReorderf("[OpenShimNet] sid=%u reorder drain recv sock=0x%08X iteration=%u peer=%s bytes=%lu flags=0x%08lX",
                GetSocketId(s),
                static_cast<unsigned>(s),
                drainCount,
                FormatIpv4Peer(drainSource).c_str(),
                static_cast<unsigned long>(drainBytes),
                static_cast<unsigned long>(drainFlags));

            if (ProcessReceivedDatagram(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, drainSource, packetBuffer, drainBytes, delivered, deliveredSource))
            {
                if (g_RealWSASetLastError)
                    g_RealWSASetLastError(0);
                LogReorderf("[OpenShimNet] sid=%u reorder delivered during drain sock=0x%08X drained=%u bytes=%u peer=%s",
                    GetSocketId(s),
                    static_cast<unsigned>(s),
                    drainedPackets,
                    delivered,
                    FormatIpv4Peer(deliveredSource).c_str());
                CaptureRecvPathEvent(
                    kBufferLogEventWSARecvFrom,
                    s,
                    reinterpret_cast<const sockaddr*>(&deliveredSource),
                    0,
                    GetRequestedWsabufBytes(buffers, bufferCount),
                    delivered,
                    0,
                    buffers && bufferCount > 0 && buffers[0].buf
                        ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                        : nullptr);
                LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
                return 0;
            }
        }

        if (TryDeliverBufferedPacket(s, buffers, bufferCount, bytesRecv, flags, from, fromLen, delivered, deliveredSource))
        {
            if (g_RealWSASetLastError)
                g_RealWSASetLastError(0);
            LogReorderf("[OpenShimNet] sid=%u reorder delivered after drain sock=0x%08X drained=%u bytes=%u peer=%s",
                GetSocketId(s),
                static_cast<unsigned>(s),
                drainedPackets,
                delivered,
                FormatIpv4Peer(deliveredSource).c_str());
            CaptureRecvPathEvent(
                kBufferLogEventWSARecvFrom,
                s,
                reinterpret_cast<const sockaddr*>(&deliveredSource),
                0,
                GetRequestedWsabufBytes(buffers, bufferCount),
                delivered,
                0,
                buffers && bufferCount > 0 && buffers[0].buf
                    ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                    : nullptr);
            LogPacketActivity("WSARecvFrom", s, false, static_cast<int>(delivered), reinterpret_cast<const sockaddr*>(&deliveredSource), static_cast<int>(sizeof(deliveredSource)));
            return 0;
        }

        if (g_RealWSASetLastError)
            g_RealWSASetLastError(WSAEWOULDBLOCK);
        LogReorderf("[OpenShimNet] sid=%u reorder defer sock=0x%08X drained=%u result=WSAEWOULDBLOCK",
            GetSocketId(s),
            static_cast<unsigned>(s),
            drainedPackets);
        LogSocketError("WSARecvFrom", s, SOCKET_ERROR, &SocketState::lastRecvFromError);
        return SOCKET_ERROR;
    }

    int WSAAPI Hook_recvfrom(SOCKET s, char* buffer, int len, int flags, sockaddr* from, int* fromLen)
    {
        EnsureSocketOptions(s);
        const int rc = g_RealRecvFrom(s, buffer, len, flags, from, fromLen);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        CaptureRecvPathEvent(
            kBufferLogEventRecvFrom,
            s,
            from,
            static_cast<uint16_t>(flags & 0xFFFFu),
            len > 0 ? static_cast<uint32_t>(len) : 0,
            rc >= 0 ? static_cast<uint32_t>(rc) : 0,
            static_cast<uint32_t>(err),
            (rc > 0 && buffer) ? reinterpret_cast<const uint8_t*>(buffer) : nullptr);
        if (rc >= 0)
            LogPacketActivity("recvfrom", s, false, rc, from, fromLen ? *fromLen : 0);
        LogSocketError("recvfrom", s, rc == SOCKET_ERROR ? SOCKET_ERROR : 0, &SocketState::lastRecvFromError);
        return rc;
    }

    int WSAAPI Hook_ioctlsocket(SOCKET s, long cmd, u_long* argp)
    {
        const int rc = g_RealIoctlSocket(s, cmd, argp);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (cmd == FIONBIO)
        {
            BufferLogEvent(
                kBufferLogEventIoctlSocket,
                s,
                nullptr,
                static_cast<uint16_t>((argp && (*argp & 1u)) ? 1u : 0u),
                static_cast<uint32_t>(cmd),
                argp ? static_cast<uint32_t>(*argp) : 0,
                static_cast<uint32_t>(err),
                nullptr,
                0);
        }
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_WSAIoctl(
        SOCKET s,
        DWORD controlCode,
        LPVOID inBuffer,
        DWORD inBufferLen,
        LPVOID outBuffer,
        DWORD outBufferLen,
        LPDWORD bytesReturned,
        LPWSAOVERLAPPED overlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine)
    {
        const int rc = g_RealWSAIoctl(
            s,
            controlCode,
            inBuffer,
            inBufferLen,
            outBuffer,
            outBufferLen,
            bytesReturned,
            overlapped,
            completionRoutine);
        const int err = (rc == SOCKET_ERROR && g_RealWSAGetLastError) ? g_RealWSAGetLastError() : 0;
        if (controlCode == FIONBIO)
        {
            uint32_t mode = 0;
            if (inBuffer && inBufferLen >= sizeof(u_long))
                mode = static_cast<uint32_t>(*reinterpret_cast<u_long*>(inBuffer));
            BufferLogEvent(
                kBufferLogEventWSAIoctl,
                s,
                nullptr,
                static_cast<uint16_t>((mode & 1u) ? 1u : 0u),
                controlCode,
                mode,
                static_cast<uint32_t>(err),
                nullptr,
                0);
        }
        if (rc == SOCKET_ERROR && g_RealWSASetLastError)
            g_RealWSASetLastError(err);
        return rc;
    }

    int WSAAPI Hook_setsockopt(SOCKET s, int level, int optName, const char* optVal, int optLen)
    {
        const int rc = g_RealSetSockOpt(s, level, optName, optVal, optLen);
        int requested = 0;
        if (optVal && optLen >= static_cast<int>(sizeof(int)))
            std::memcpy(&requested, optVal, sizeof(int));

        int readback = -1;
        if (rc == 0 && optLen >= static_cast<int>(sizeof(int)))
        {
            readback = QuerySocketInt(s, level, optName);
            readback = ReassertSocketBufferFloor(s, level, optName, requested, readback);
            if (IsUdpSocket(s) && (level != IPPROTO_IP || optName != IP_TOS || requested != static_cast<int>((g_Config.dscp & 0x3Fu) << 2)))
                ApplyDscpToSocket(s);
        }

        if (g_Config.logSockOptCalls)
        {
            const int err = (rc == 0 || !g_RealWSAGetLastError) ? 0 : g_RealWSAGetLastError();
            Logf("[OpenShimNet] sid=%u setsockopt sock=0x%08X level=%d opt=%s(%d) requested=%d readback=%d rc=%d err=%d",
                GetSocketId(s),
                static_cast<unsigned>(s),
                level,
                SockOptName(level, optName),
                optName,
                requested,
                readback,
                rc,
                err);
            if (rc != 0 && g_RealWSASetLastError)
                g_RealWSASetLastError(err);
        }
        return rc;
    }

    struct HookTarget
    {
        const char* name;
        WORD ordinal;
        FARPROC hook;
    };

    bool PatchImportSlot(HMODULE module, const char* moduleLabel, IMAGE_THUNK_DATA32* origThunk, IMAGE_THUNK_DATA32* thunk, const HookTarget& target, FARPROC* previousTarget)
    {
        if (!origThunk)
            return false;

        while (origThunk->u1.AddressOfData && thunk->u1.Function)
        {
            bool matched = false;
            if (origThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
            {
                matched = target.ordinal != 0 && IMAGE_ORDINAL(origThunk->u1.Ordinal) == target.ordinal;
            }
            else
            {
                auto* importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                    reinterpret_cast<uint8_t*>(module) + origThunk->u1.AddressOfData);

                matched = std::strcmp(reinterpret_cast<const char*>(importByName->Name), target.name) == 0;
            }

            if (matched)
            {
                DWORD oldProtect = 0;
                if (!VirtualProtect(&thunk->u1.Function, sizeof(thunk->u1.Function), PAGE_READWRITE, &oldProtect))
                    return false;

                if (previousTarget)
                    *previousTarget = reinterpret_cast<FARPROC>(static_cast<uintptr_t>(thunk->u1.Function));
                thunk->u1.Function = static_cast<DWORD>(reinterpret_cast<uintptr_t>(target.hook));
                VirtualProtect(&thunk->u1.Function, sizeof(thunk->u1.Function), oldProtect, &oldProtect);

                Logf("[OpenShimNet] Patched %s import in %s", target.name, moduleLabel);
                return true;
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
                { "getaddrinfo", 0, reinterpret_cast<FARPROC>(Hook_getaddrinfo) },
                { "socket", 23, reinterpret_cast<FARPROC>(Hook_socket) },
                { "WSASocketW", 0, reinterpret_cast<FARPROC>(Hook_WSASocketW) },
                { "bind", 2, reinterpret_cast<FARPROC>(Hook_bind) },
                { "connect", 4, reinterpret_cast<FARPROC>(Hook_connect) },
                { "WSAConnect", 0, reinterpret_cast<FARPROC>(Hook_WSAConnect) },
                { "closesocket", 3, reinterpret_cast<FARPROC>(Hook_closesocket) },
                { "send", 19, reinterpret_cast<FARPROC>(Hook_send) },
                { "recv", 16, reinterpret_cast<FARPROC>(Hook_recv) },
                { "sendto", 20, reinterpret_cast<FARPROC>(Hook_sendto) },
                { "recvfrom", 17, reinterpret_cast<FARPROC>(Hook_recvfrom) },
                { "setsockopt", 21, reinterpret_cast<FARPROC>(Hook_setsockopt) },
                { "WSASend", 0, reinterpret_cast<FARPROC>(Hook_WSASend) },
                { "WSARecv", 0, reinterpret_cast<FARPROC>(Hook_WSARecv) },
                { "WSASendTo", 0, reinterpret_cast<FARPROC>(Hook_WSASendTo) },
                { "WSARecvFrom", 0, reinterpret_cast<FARPROC>(Hook_WSARecvFrom) },
                // WS2_32 ordinal 12 is inet_ntoa; ioctlsocket is ordinal 10.
                { "ioctlsocket", 10, reinterpret_cast<FARPROC>(Hook_ioctlsocket) },
                { "WSAIoctl", 0, reinterpret_cast<FARPROC>(Hook_WSAIoctl) },
            };

            int patched = 0;
            for (const auto& target : targets)
            {
                FARPROC previousTarget = nullptr;
                if (PatchImportSlot(module, moduleLabel, origThunk, thunk, target, &previousTarget))
                {
                    RememberPatchedImport(target.name, previousTarget);
                    ++patched;
                }
            }

            Logf("[OpenShimNet] %s Winsock IAT hooks installed: %d", moduleLabel, patched);
            return;
        }

        LogShimA(LogLevel::Debug, "net", "[OpenShimNet] Module %s does not import ws2_32.dll; no hooks installed", moduleLabel);
    }

    void PatchCompletionImportsForModule(HMODULE module, const char* moduleLabel)
    {
        if (!g_Config.enableRelayCapture || !module || !g_RealGetQueuedCompletionStatus)
            return;

        auto* base = reinterpret_cast<uint8_t*>(module);
        auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return;
        auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return;

        const auto& importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
        if (importDir.VirtualAddress == 0)
            return;

        auto* importDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + importDir.VirtualAddress);
        for (; importDesc->Name; ++importDesc)
        {
            const char* dllName = reinterpret_cast<const char*>(base + importDesc->Name);
            if (_stricmp(dllName, "kernel32.dll") != 0)
                continue;

            auto* origThunk = importDesc->OriginalFirstThunk
                ? reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->OriginalFirstThunk)
                : reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->FirstThunk);
            auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA32*>(base + importDesc->FirstThunk);
            const HookTarget target = {
                "GetQueuedCompletionStatus",
                0,
                reinterpret_cast<FARPROC>(Hook_GetQueuedCompletionStatus),
            };
            FARPROC previousTarget = nullptr;
            if (PatchImportSlot(module, moduleLabel, origThunk, thunk, target, &previousTarget))
            {
                if (previousTarget && previousTarget != reinterpret_cast<FARPROC>(Hook_GetQueuedCompletionStatus))
                    g_RealGetQueuedCompletionStatus = reinterpret_cast<GetQueuedCompletionStatusFn>(previousTarget);
                Logf("[OpenShimNet] relay_capture IOCP completion hook installed in %s", moduleLabel);
            }
            return;
        }

        LogShimA(LogLevel::Warn, "net", "[OpenShimNet] relay_capture GetQueuedCompletionStatus import not found in %s", moduleLabel);
    }
} // namespace

    BOOL CALLBACK InitializeNetworkOptimizerOnce(PINIT_ONCE, PVOID, PVOID*)
    {
        LoadConfig();

        LogShimA(LogLevel::Info, "net", "[OpenShimNet] Initializing");
        LogNetIniValues();
        Logf("[OpenShimNet] Config enabled=%d logging=%d sendBufferSize=%u recvBufferSize=%u applySocketBuffers=%d dscp=%u tcpNoDelay=%d keepAlive=%d disableUdpConnReset=%d logSocketErrors=%d logSocketLifecycle=%d logSocketPackets=%d logSockOptCalls=%d logPacketReorder=%d packetLogLimit=%u packetLogInterval=%u enablePacketReorder=%d reorderWindowMs=%u reorderMinWindowMs=%u reorderAdapt=%d reorderWake=%d reorderDepth=%u reorderPeers=%u reorderDrainCap=%u sendDup=%d dupDelayMs=%u dupMaxPps=%u govStart=%u govScan=%d autokickStart=%u autokickPing=%u autokickLoss=%u autokickTime=%u enableBufferLog=%d enableRelayCapture=%d bufferLogPayloadBytes=%u bufferLogRingRecords=%u bufferLogSocketId=%u bufferLogPeer=%s",
            g_Config.enabled ? 1 : 0,
            g_Config.logging ? 1 : 0,
            g_Config.sendBufferSize,
            g_Config.recvBufferSize,
            g_Config.applySocketBuffers ? 1 : 0,
            g_Config.dscp,
            g_Config.tcpNoDelay ? 1 : 0,
            g_Config.keepAlive ? 1 : 0,
            g_Config.disableUdpConnReset ? 1 : 0,
            g_Config.logSocketErrors ? 1 : 0,
            g_Config.logSocketLifecycle ? 1 : 0,
            g_Config.logSocketPackets ? 1 : 0,
            g_Config.logSockOptCalls ? 1 : 0,
            g_Config.logPacketReorder ? 1 : 0,
            g_Config.packetLogLimit,
            g_Config.packetLogInterval,
            g_Config.enablePacketReorder ? 1 : 0,
            g_Config.reorderWindowMs,
            g_Config.reorderMinWindowMs,
            g_Config.adaptivePacketReorder ? 1 : 0,
            g_Config.enableReorderWake ? 1 : 0,
            g_Config.reorderDepth,
            g_Config.reorderPeers,
            g_Config.reorderDrainCap,
            g_Config.sendDup ? 1 : 0,
            g_Config.dupDelayMs,
            g_Config.dupMaxPps,
            g_Config.govStart,
            g_Config.govScan ? 1 : 0,
            g_Config.autoKickStart,
            g_Config.autoKickPing,
            g_Config.autoKickLoss,
            g_Config.autoKickTime,
            g_Config.enableBufferLog ? 1 : 0,
            g_Config.enableRelayCapture ? 1 : 0,
            g_Config.bufferLogPayloadBytes,
            g_Config.bufferLogRingRecords,
            g_Config.bufferLogSocketFilterEnabled ? g_Config.bufferLogSocketId : 0,
            g_Config.bufferLogPeerFilterEnabled ? g_Config.bufferLogPeerText.c_str() : "<off>");
        if (FileExists(JoinPath(GetGameDir(), "netcode_manifest.json")))
            LogShimA(LogLevel::Info, "net", "[OpenShimNet] netcode_manifest.json detected; runtime buffer minimums aligned to manifest profile");

        if (!g_Config.enabled)
        {
            LogShimA(LogLevel::Info, "net", "[OpenShimNet] Socket optimizer disabled by configuration");
            return TRUE;
        }

        if (g_Config.enablePacketReorder)
        {
            LogShimA(LogLevel::Warn, "net",
                "[OpenShimNet] EXPERIMENTAL packet reordering is enabled. The wire sequence field is unresolved and overlapped WSARecvFrom traffic bypasses this path; use only for controlled diagnostics.");
        }
        if (g_Config.sendDup)
        {
            LogShimA(LogLevel::Warn, "net",
                "[OpenShimNet] DEPRECATED packet duplication is enabled. Testing indicates duplication may worsen constrained uplinks; use only for controlled diagnostics.");
        }

        if (!LoadWinsockExports())
            return TRUE;

        InitializeRelayControlLog();
        InitializeBufferLog();
        PatchWinsockImportsForModule(GetModuleHandleA(nullptr), "battlezone98redux.exe");
        PatchWinsockImportsForModule(GetModuleHandleA("Galaxy.dll"), "Galaxy.dll");
        PatchWinsockImportsForModule(GetModuleHandleA("GalaxyPeer.dll"), "GalaxyPeer.dll");
        PatchWinsockImportsForModule(GetModuleHandleA("steam_api.dll"), "steam_api.dll");
        PatchCompletionImportsForModule(GetModuleHandleA(nullptr), "battlezone98redux.exe");

        if (g_Config.enablePacketReorder && g_Config.enableReorderWake && !g_WakeThread)
        {
            InterlockedExchange(&g_WakeStop, 0);
            g_WakeThread = CreateThread(nullptr, 0, ReorderWakeThread, nullptr, 0, nullptr);
            if (!g_WakeThread)
                LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Failed to start reorder wake thread err=%lu", GetLastError());
        }

        if (g_Config.sendDup && g_Config.dupDelayMs > 0 && !g_DupThread)
        {
            InterlockedExchange(&g_DupStop, 0);
            g_DupThread = CreateThread(nullptr, 0, DupPacerThread, nullptr, 0, nullptr);
            if (!g_DupThread)
            {
                LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Failed to start dup pacer thread err=%lu; falling back to immediate duplicates", GetLastError());
                g_Config.dupDelayMs = 0;
            }
        }

        if (g_Config.govScan && !g_GovScanThread)
        {
            g_GovScanThread = CreateThread(nullptr, 0, GovernorScanThread, nullptr, 0, nullptr);
            if (!g_GovScanThread)
                LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Failed to start governor scan thread err=%lu", GetLastError());
        }

        if (g_Config.govStart != 0 && !g_GovPatchThread)
        {
            InterlockedExchange(&g_GovStop, 0);
            InterlockedExchange(&g_GovLastObserved, 0);
            InterlockedExchange(&g_GovObservationValid, 0);
            InterlockedExchange(&g_GovBumps, 0);
            g_GovPatchThread = CreateThread(nullptr, 0, GovernorPatchThread, nullptr, 0, nullptr);
            if (!g_GovPatchThread)
                LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Failed to start governor patch thread err=%lu", GetLastError());
        }

        const bool wantNetGlobals =
            g_Config.autoKickStart || g_Config.autoKickPing || g_Config.autoKickLoss || g_Config.autoKickTime ||
            g_Config.netMinBandwidth || g_Config.netMaxBandwidth || g_Config.netUpCount ||
            g_Config.netDownCount || g_Config.netMaxPing || g_Config.netMaxPingsLost;
        if (wantNetGlobals && !g_AutoKickThread)
        {
            InterlockedExchange(&g_AutoKickStop, 0);
            g_AutoKickThread = CreateThread(nullptr, 0, NetGlobalsPatchThread, nullptr, 0, nullptr);
            if (!g_AutoKickThread)
                LogShimA(LogLevel::Warn, "net", "[OpenShimNet] Failed to start net globals patch thread err=%lu", GetLastError());
        }

        LogShimA(LogLevel::Info, "net", "[OpenShimNet] Initialization complete");
        return TRUE;
    }

    void InitializeNetworkOptimizer()
    {
        InitOnceExecuteOnce(&g_NetworkInitOnce, InitializeNetworkOptimizerOnce, nullptr, nullptr);
    }

    void ShutdownNetworkOptimizer()
    {
        InterlockedExchange(&g_WakeStop, 1);
        InterlockedExchange(&g_DupStop, 1);
        InterlockedExchange(&g_GovStop, 1);
        InterlockedExchange(&g_AutoKickStop, 1);
        if (g_Config.govStart != 0 &&
            InterlockedCompareExchange(&g_GovObservationValid, 0, 0) != 0)
        {
            const LONG finalObserved = InterlockedCompareExchange(&g_GovLastObserved, 0, 0);
            const LONG finalBumps = InterlockedCompareExchange(&g_GovBumps, 0, 0);
            Logf("[OpenShimNet] governor_patch: shutdown snapshot bumps=%ld finalObserved=%ld target=%u",
                static_cast<long>(finalBumps),
                static_cast<long>(finalObserved),
                g_Config.govStart);
        }
        // Join before freeing anything the workers touch. Closing a thread
        // handle without waiting leaves its final iteration free to run
        // against state torn down below (the ring buffer, capture maps and
        // relay log). Mirrors the ShutdownBzrNetTrace contract: bounded wait,
        // then refuse to free what a still-running worker could reach.
        auto stopWorkerThread = [](void** slot) -> bool
        {
            if (!*slot)
                return true;
            const DWORD wait =
                WaitForSingleObject(static_cast<HANDLE>(*slot), 1500);
            if (wait != WAIT_OBJECT_0)
                return false;
            CloseHandle(static_cast<HANDLE>(*slot));
            *slot = nullptr;
            return true;
        };
        const bool wakeStopped = stopWorkerThread(reinterpret_cast<void**>(&g_WakeThread));
        const bool dupStopped = stopWorkerThread(reinterpret_cast<void**>(&g_DupThread));
        const bool govScanStopped = stopWorkerThread(reinterpret_cast<void**>(&g_GovScanThread));
        const bool govPatchStopped = stopWorkerThread(reinterpret_cast<void**>(&g_GovPatchThread));
        const bool autoKickStopped = stopWorkerThread(reinterpret_cast<void**>(&g_AutoKickThread));
        const bool allStopped = wakeStopped && dupStopped && govScanStopped &&
                                govPatchStopped && autoKickStopped;
        // The wake sender is owned by ReorderWakeThread, which reads and
        // recreates g_WakeSender without a lock. Closing it before that worker
        // is joined let its final iteration send through a closed (and
        // potentially recycled) SOCKET value, or leak a sender it had just
        // created. Close it only after the owning thread has been joined.
        if (wakeStopped && g_WakeSender != INVALID_SOCKET && g_RealCloseSocket)
        {
            g_RealCloseSocket(g_WakeSender);
            g_WakeSender = INVALID_SOCKET;
        }
        if (!allStopped)
        {
            Logf("[OpenShimNet] shutdown: workers exceeded join window "
                 "wake=%d dup=%d govScan=%d govPatch=%d autoKick=%d; leaking "
                 "shared buffers rather than freeing under live threads",
                 static_cast<int>(wakeStopped), static_cast<int>(dupStopped),
                 static_cast<int>(govScanStopped),
                 static_cast<int>(govPatchStopped),
                 static_cast<int>(autoKickStopped));
        }
        LogOutboundBurstSummary();
        if (allStopped)
        {
            FlushBufferLog();
            if (g_BufferLogRing)
            {
                HeapFree(GetProcessHeap(), 0, g_BufferLogRing);
                g_BufferLogRing = nullptr;
            }
            g_BufferLogEnabled = false;
            AcquireSRWLockExclusive(&g_PendingCaptureLock);
            g_PendingCaptureIo.clear();
            ReleaseSRWLockExclusive(&g_PendingCaptureLock);
            AcquireSRWLockExclusive(&g_WebSocketCaptureLock);
            g_WebSocketCapture.clear();
            ReleaseSRWLockExclusive(&g_WebSocketCaptureLock);
            AcquireSRWLockExclusive(&g_RelayControlLogLock);
            if (g_RelayControlLog)
            {
                std::fclose(g_RelayControlLog);
                g_RelayControlLog = nullptr;
            }
            ReleaseSRWLockExclusive(&g_RelayControlLogLock);
        }
    }
}
