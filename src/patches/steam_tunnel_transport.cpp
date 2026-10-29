#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include "steam_tunnel_transport.h"
#include "socket_tunnel_protocol.h"
#include <steam/isteamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#include <algorithm>
#include <cstdio>
#include <deque>
#include <map>
#include <stdexcept>
#include <utility>

namespace BZROpenShim::SocketTunnel
{
namespace
{
    constexpr int kVirtualPort = 1337;
    using VoidFn = void (__cdecl*)();
    using HandleFn = int (__cdecl*)();
    using PointerFn = void* (__cdecl*)();
    using GenericFn = void* (__cdecl*)(void*, int, int, const char*);
    template<class T> T Export(HMODULE dll, const char* name)
    {
        auto p = reinterpret_cast<T>(GetProcAddress(dll, name));
        if (!p) throw std::runtime_error(std::string("missing shipped Steam export: ") + name);
        return p;
    }
    SRWLOCK callbackLock = SRWLOCK_INIT;
    std::deque<SteamNetConnectionStatusChangedCallback_t>* callbackQueue = nullptr;
    bool callbackOverflow = false;
    void OnStatus(SteamNetConnectionStatusChangedCallback_t* change)
    {
        // SteamAPI_RunCallbacks may be called on the game's main thread. Do not
        // call Steam, log, touch tunnel sockets or retain callback-owned memory.
        AcquireSRWLockExclusive(&callbackLock);
        if (callbackQueue)
        {
            if (callbackQueue->size() < 1024)
            { try { callbackQueue->push_back(*change); } catch (...) { callbackOverflow = true; } }
            else callbackOverflow = true;
        }
        ReleaseSRWLockExclusive(&callbackLock);
    }
    bool NativeReliable(Kind kind) { return Reliable(kind) || kind == Kind::Hello || kind == Kind::Welcome; }
}
struct SteamTransport::Impl
{
    Config cfg;
    Logger logger = nullptr;
    HMODULE dll = nullptr;
    bool initialized = false, registered = false;
    ISteamNetworkingSockets* sockets = nullptr;
    ISteamNetworkingUtils* utils = nullptr;
    VoidFn run = nullptr, shutdown = nullptr;
    HSteamListenSocket listener = k_HSteamListenSocket_Invalid;
    struct Connection { uint64_t identity = 0; bool connected = false; };
    std::map<HSteamNetConnection, Connection> connections;
    std::deque<SteamNetConnectionStatusChangedCallback_t> callbacks;
    std::vector<SteamEvent> events;
    uint64_t nextConnect = 0, lastDiagnostics = 0;
    int lastRelay = -999, lastAuth = -999;
    uint64_t sentBytes = 0, receivedBytes = 0;

    void Log(const char* message) { if (logger) logger(message); }
    void Options(SteamNetworkingConfigValue_t (&options)[4])
    {
        options[0].SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, reinterpret_cast<void*>(&OnStatus));
        options[1].SetInt32(k_ESteamNetworkingConfig_SendBufferSize, int(kQueueMax));
        // Per-connection/listener scope only: avoid affecting stock networking.
        // Disable ICE so this preview actually qualifies SDR, not direct P2P.
        options[2].SetInt32(k_ESteamNetworkingConfig_P2P_Transport_ICE_Enable, 0);
        options[3].SetInt32(k_ESteamNetworkingConfig_TimeoutConnected, 15000);
    }
    void Connect(uint64_t now)
    {
        if (cfg.bridge || !connections.empty() || now < nextConnect) return;
        SteamNetworkingIdentity remote{}; remote.SetSteamID64(cfg.steamHost);
        SteamNetworkingConfigValue_t options[4]; Options(options);
        const auto connection = sockets->ConnectP2P(remote, kVirtualPort, 4, options);
        if (connection != k_HSteamNetConnection_Invalid)
        {
            connections.emplace(connection, Connection{cfg.steamHost, false});
            Log("Steam ConnectP2P requested; waiting for connection-status callback");
        }
        else Log("Steam ConnectP2P failed; retrying in five seconds");
        nextConnect = now + 5000;
    }
    void Close(uint32_t connection)
    {
        if (!connections.count(connection)) return;
        connections.erase(connection);
        sockets->CloseConnection(connection, 1000, "BZR tunnel closed", false);
    }
    ~Impl()
    {
        if (registered)
        {
            AcquireSRWLockExclusive(&callbackLock);
            callbackQueue = nullptr; callbackOverflow = false;
            ReleaseSRWLockExclusive(&callbackLock);
        }
        while (!connections.empty()) Close(connections.begin()->first);
        if (listener != k_HSteamListenSocket_Invalid)
        {
            sockets->CloseListenSocket(listener);
            // A request can be queued by the game's callback pump immediately
            // before shutdown and never reach our connection table.
            for (const auto& change : callbacks)
            {
                SteamNetConnectionInfo_t info{};
                if (sockets->GetConnectionInfo(change.m_hConn, &info) && info.m_hListenSocket == listener)
                    sockets->CloseConnection(change.m_hConn, 1000, "BZR bridge stopping", false);
            }
        }
        char text[160]; std::snprintf(text, sizeof(text), "Steam transport stopped: submitted=%llu received=%llu; Steam session %s",
            static_cast<unsigned long long>(sentBytes), static_cast<unsigned long long>(receivedBytes),
            initialized ? "owned and shutting down" : (cfg.ownSteam ? "not initialized" : "borrowed, left to game")); Log(text);
        // Client path never initializes, pumps or shuts down the game's Steam API.
        if (initialized && shutdown) shutdown();
        if (dll) FreeLibrary(dll);
    }
    void Start(const Config& config, std::atomic<bool>& stop, Logger log)
    {
        cfg = config; logger = log;
        if (!cfg.bridge && !IndividualSteamId(cfg.steamHost)) throw std::runtime_error("invalid Steam tunnel host");
        if (cfg.ownSteam)
        {
            wchar_t path[32768]{};
            const DWORD size = GetModuleFileNameW(nullptr, path, DWORD(std::size(path)));
            if (!size || size >= std::size(path)) throw std::runtime_error("standalone executable path unavailable");
            std::wstring name(path); name.resize(name.find_last_of(L"\\/") + 1); name += L"steam_api.dll";
            // Explicit sibling path. No working-directory/PATH DLL search.
            dll = LoadLibraryExW(name.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
            if (!dll) throw std::runtime_error("stage the shipped Win32 steam_api.dll beside the standalone exe");
            shutdown = Export<VoidFn>(dll, "SteamAPI_Shutdown");
            auto init = Export<bool (__cdecl*)()>(dll, "SteamAPI_Init");
            if (!init()) throw std::runtime_error("SteamAPI_Init failed (Steam login, owning account and appid 301650 required)");
            initialized = true;
            run = Export<VoidFn>(dll, "SteamAPI_RunCallbacks");
        }
        else
        {
            const auto deadline = GetTickCount64() + 30000;
            Log("waiting for the game's loaded Steam API and initialized handles (no client-side SteamAPI_Init)");
            while (!stop.load() && GetTickCount64() < deadline)
            {
                if (GetModuleHandleExW(0, L"steam_api.dll", &dll)) break;
                Sleep(20);
            }
            if (!dll) throw std::runtime_error("game Steam API unavailable; tunnel remains blocked");
        }
        auto user = Export<HandleFn>(dll, "SteamAPI_GetHSteamUser");
        auto pipe = Export<HandleFn>(dll, "SteamAPI_GetHSteamPipe");
        auto client = Export<PointerFn>(dll, "SteamClient");
        auto generic = Export<GenericFn>(dll, "SteamAPI_ISteamClient_GetISteamGenericInterface");
        auto legacyUtils = Export<PointerFn>(dll, "SteamUtils");
        auto appId = Export<unsigned (__cdecl*)(void*)>(dll, "SteamAPI_ISteamUtils_GetAppID");
        const auto deadline = GetTickCount64() + 30000;
        while (!stop.load() && (!user() || !pipe()) && GetTickCount64() < deadline) Sleep(20);
        if (stop.load() || !user() || !pipe()) throw std::runtime_error("game Steam API did not initialize in time");
        auto u = legacyUtils();
        if (!u || appId(u) != 301650) throw std::runtime_error("Steam tunnel requires appid 301650");
        auto c = client();
        if (!c) throw std::runtime_error("SteamClient017 accessor unavailable");
        sockets = static_cast<ISteamNetworkingSockets*>(generic(c, user(), pipe(), STEAMNETWORKINGSOCKETS_INTERFACE_VERSION));
        utils = static_cast<ISteamNetworkingUtils*>(generic(c, user(), pipe(), STEAMNETWORKINGUTILS_INTERFACE_VERSION));
        if (!sockets || !utils) throw std::runtime_error("exact SteamNetworkingSockets012/Utils004 interfaces unavailable; no legacy fallback");
        SteamNetworkingIdentity identity{};
        if (!sockets->GetIdentity(&identity) || !IndividualSteamId(identity.GetSteamID64()))
            throw std::runtime_error("Steam identity unavailable or not an individual public account");
        if (!cfg.bridge && identity.GetSteamID64() == cfg.steamHost) throw std::runtime_error("host and client must use distinct Steam accounts");
        char text[180]; std::snprintf(text, sizeof(text), "Steam appid=301650 local=%llu interfaces=%s/%s session=%s vport=%d ICE=disabled",
            static_cast<unsigned long long>(identity.GetSteamID64()), STEAMNETWORKINGSOCKETS_INTERFACE_VERSION,
            STEAMNETWORKINGUTILS_INTERFACE_VERSION, cfg.ownSteam ? "owned" : "borrowed", kVirtualPort); Log(text);
        // Pending SDK callbacks can outlive a connection. Keep their code mapped
        // until process exit and null the queue under the same lock on teardown.
        HMODULE owner = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                               reinterpret_cast<LPCWSTR>(&OnStatus), &owner))
            throw std::runtime_error("could not pin Steam callback code lifetime");
        AcquireSRWLockExclusive(&callbackLock);
        const bool busy = callbackQueue != nullptr;
        if (!busy) { callbackQueue = &callbacks; callbackOverflow = false; registered = true; }
        ReleaseSRWLockExclusive(&callbackLock);
        if (busy) throw std::runtime_error("only one Steam tunnel transport per process");
        utils->InitRelayNetworkAccess();
        if (cfg.bridge)
        {
            SteamNetworkingConfigValue_t options[4]; Options(options);
            listener = sockets->CreateListenSocketP2P(kVirtualPort, 4, options);
            if (listener == k_HSteamListenSocket_Invalid) throw std::runtime_error("Steam CreateListenSocketP2P failed");
            Log("Steam P2P bridge listening (authenticated Steam identities; max eight connections)");
        }
        else Connect(GetTickCount64());
    }
    void Status(const SteamNetConnectionStatusChangedCallback_t& change, uint64_t now)
    {
        const auto h = change.m_hConn;
        // Use current info: queued callback states can already be stale.
        SteamNetConnectionInfo_t info{};
        if (!sockets->GetConnectionInfo(h, &info)) return;
        auto it = connections.find(h);
        if (it == connections.end())
        {
            if (!cfg.bridge || info.m_hListenSocket != listener) return;
            const auto id = info.m_identityRemote.GetSteamID64();
            bool duplicate = false;
            for (const auto& entry : connections) if (entry.second.identity == id) duplicate = true;
            if (info.m_eState != k_ESteamNetworkingConnectionState_Connecting || !IndividualSteamId(id) || duplicate || connections.size() >= 8)
            { sockets->CloseConnection(h, 1001, "BZR tunnel capacity or identity rejected", false); return; }
            it = connections.emplace(h, Connection{id, false}).first;
            if (sockets->AcceptConnection(h) != k_EResultOK) { Close(h); return; }
        }
        char text[256]; std::snprintf(text, sizeof(text), "Steam status peer=%llu connection=%u state=%d reason=%d detail=%.100s",
            static_cast<unsigned long long>(it->second.identity), h, int(info.m_eState), info.m_eEndReason, info.m_szEndDebug); Log(text);
        if (info.m_eState == k_ESteamNetworkingConnectionState_Connected)
        {
            const bool valid = info.m_identityRemote.GetSteamID64() == it->second.identity &&
                !(info.m_nFlags & (k_nSteamNetworkConnectionInfoFlags_Unauthenticated | k_nSteamNetworkConnectionInfoFlags_Unencrypted));
            if (!valid) { events.push_back({h, it->second.identity, false}); Close(h); return; }
            if (!it->second.connected) { it->second.connected = true; events.push_back({h, it->second.identity, true}); }
        }
        else if (info.m_eState == k_ESteamNetworkingConnectionState_ClosedByPeer ||
                 info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally)
        {
            events.push_back({h, it->second.identity, false}); Close(h); nextConnect = now + 5000;
        }
    }
    void Diagnostics(uint64_t now)
    {
        SteamRelayNetworkStatus_t relay{}; utils->GetRelayNetworkStatus(&relay);
        SteamNetAuthenticationStatus_t auth{}; sockets->GetAuthenticationStatus(&auth);
        const bool periodic = now - lastDiagnostics >= 10000;
        char text[384];
        if (periodic || lastRelay != relay.m_eAvail || lastAuth != auth.m_eAvail)
        {
            std::snprintf(text, sizeof(text), "SDR overall=%d config=%d relay=%d measuring=%d auth=%d detail=%.150s",
                int(relay.m_eAvail), int(relay.m_eAvailNetworkConfig), int(relay.m_eAvailAnyRelay), relay.m_bPingMeasurementInProgress,
                int(auth.m_eAvail), relay.m_debugMsg); Log(text);
            lastRelay = relay.m_eAvail; lastAuth = auth.m_eAvail;
        }
        if (!periodic) return;
        lastDiagnostics = now;
        for (const auto& entry : connections)
        {
            SteamNetConnectionRealTimeStatus_t status{}; SteamNetConnectionInfo_t info{};
            if (sockets->GetConnectionRealTimeStatus(entry.first, &status, 0, nullptr) != k_EResultOK ||
                !sockets->GetConnectionInfo(entry.first, &info)) continue;
            std::snprintf(text, sizeof(text), "Steam quality peer=%llu state=%d relayed=%d ping_ms=%d local=%.3f remote=%.3f tx_Bps=%.1f rx_Bps=%.1f pending_rel=%d pending_unrel=%d unacked=%d",
                static_cast<unsigned long long>(entry.second.identity), int(status.m_eState),
                !!(info.m_nFlags & k_nSteamNetworkConnectionInfoFlags_Relayed), status.m_nPing,
                status.m_flConnectionQualityLocal, status.m_flConnectionQualityRemote, status.m_flOutBytesPerSec,
                status.m_flInBytesPerSec, status.m_cbPendingReliable, status.m_cbPendingUnreliable, status.m_cbSentUnackedReliable); Log(text);
        }
    }
};
SteamTransport::SteamTransport() : impl(new Impl) {}
SteamTransport::~SteamTransport() = default;
void SteamTransport::Start(const Config& cfg, std::atomic<bool>& stop, Logger log) { impl->Start(cfg, stop, log); }
std::vector<SteamEvent> SteamTransport::Poll(uint64_t now)
{
    if (impl->initialized) impl->run();
    std::deque<SteamNetConnectionStatusChangedCallback_t> changes;
    AcquireSRWLockExclusive(&callbackLock);
    changes.swap(impl->callbacks); const bool overflow = callbackOverflow;
    ReleaseSRWLockExclusive(&callbackLock);
    if (overflow) throw std::runtime_error("Steam callback queue overflow; transport stopped");
    for (const auto& change : changes) impl->Status(change, now);
    impl->Connect(now); impl->Diagnostics(now);
    return std::exchange(impl->events, {});
}
SteamSend SteamTransport::Send(uint32_t connection, const std::vector<uint8_t>& bytes, bool reliable)
{
    auto it = impl->connections.find(connection);
    if (it == impl->connections.end() || !it->second.connected) return SteamSend::Failed;
    SteamNetConnectionRealTimeStatus_t status{};
    if (impl->sockets->GetConnectionRealTimeStatus(connection, &status, 0, nullptr) != k_EResultOK) return SteamSend::Failed;
    const int pending = status.m_cbPendingReliable + status.m_cbSentUnackedReliable + status.m_cbPendingUnreliable;
    if (pending > int(kQueueMax - (reliable ? 2048 : 16384))) return SteamSend::Busy;
    const auto result = impl->sockets->SendMessageToConnection(connection, bytes.data(), uint32(bytes.size()),
        reliable ? k_nSteamNetworkingSend_ReliableNoNagle : k_nSteamNetworkingSend_UnreliableNoDelay, nullptr);
    if (result == k_EResultLimitExceeded || result == k_EResultIgnored) return SteamSend::Busy;
    if (result != k_EResultOK) return SteamSend::Failed;
    impl->sentBytes += bytes.size(); return SteamSend::Sent;
}
int SteamTransport::Receive(uint32_t connection, std::vector<uint8_t>& bytes, bool& reliable)
{
    SteamNetworkingMessage_t* message = nullptr;
    const int result = impl->sockets->ReceiveMessagesOnConnection(connection, &message, 1);
    if (result <= 0) return result;
    const bool valid = message->m_cbSize >= 28 && message->m_cbSize <= int(kPayloadMax + 28) && message->m_conn == connection;
    if (valid)
    {
        const auto data = static_cast<const uint8_t*>(message->m_pData);
        bytes.assign(data, data + message->m_cbSize);
        reliable = (message->m_nFlags & k_nSteamNetworkingSend_Reliable) != 0;
        impl->receivedBytes += size_t(message->m_cbSize);
    }
    message->Release(); return valid ? 1 : -1;
}
void SteamTransport::Close(uint32_t connection) { impl->Close(connection); }
int SteamTransport::SelfTest()
{
    HSteamNetConnection a = 0, b = 0;
    if (!impl->sockets->CreateSocketPair(&a, &b, true, nullptr, nullptr)) return 2;
    impl->connections.emplace(a, Impl::Connection{0, true});
    impl->connections.emplace(b, Impl::Connection{0, true});
    int result = 0;
    for (Kind kind : {Kind::Open, Kind::Data, Kind::Close, Kind::Reset, Kind::Datagram})
    {
        Frame frame{kind, 123, 1, 7};
        if (kind == Kind::Open) frame.port = 1337;
        if (kind == Kind::Data) frame.data.assign(1024, 0xa5);
        if (kind == Kind::Datagram) { frame.sequence = frame.stream = 0; frame.port = 1369; frame.source = 40000; frame.data.assign(4096, 0x81); }
        const auto encoded = Encode(frame);
        for (auto direction : {std::make_pair(a, b), std::make_pair(b, a)})
        {
            if (Send(direction.first, encoded, NativeReliable(kind)) != SteamSend::Sent) { result = 2; break; }
            bool received = false;
            const auto deadline = GetTickCount64() + 2000;
            while (GetTickCount64() < deadline)
            {
                if (impl->initialized) impl->run();
                std::vector<uint8_t> bytes; bool reliable = false;
                const int n = Receive(direction.second, bytes, reliable);
                if (n < 0) { result = 2; break; }
                if (n == 1) { received = bytes == encoded && reliable == NativeReliable(kind); break; }
                Sleep(1);
            }
            if (!received) result = 2;
        }
    }
    Close(a); Close(b);
    impl->Log(result ? "Steam local socket-pair self-test FAILED" : "Steam local socket-pair self-test PASS: both directions, reliable OPEN/DATA/CLOSE/RESET, unreliable UDP (not remote P2P/SDR acceptance)");
    return result;
}
}
