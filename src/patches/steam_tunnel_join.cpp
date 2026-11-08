// steam_tunnel_join.cpp -- Steam invite / Join Game onto a host's own server
// through the Steam tunnel.
//
// HOST: socket_tunnel.exe bridge --steam announces its SteamID through a
// named mapping (kBridgeAnnounceMapping). While it exists, Tick() publishes
// rich presence "openshim_tunnel" = that SteamID, and, when the game itself
// advertises no lobby ("connect" empty), connect = kLoungeToken so the
// friends list offers Join Game even before the host makes a lobby.
//
// FRIEND: Steam delivers Join Game and accepted invites to the game's
// GameRichPresenceJoinRequested_t handler, 0x00757E00 (__thiscall(this,
// callback*), ret 4; the callback holds the inviter's SteamID at +0 and
// m_rgchConnect[256] at +8, decomp FUN_00757e00 lines 33-50). The detour
// reads the inviter's "openshim_tunnel" presence and, in the menus, points
// the tunnel at that bridge (or back at the net.ini host when the inviter
// has none), then reconnects BZRNet. A lobby connect string then runs the
// stock handler, which parks the lobby id for the next lobby list
// (FUN_007408c0). The lounge token stops there: the friend lands in the
// host server's lounge.
//
// In a mission nothing is switched and stock runs unchanged (UNVERIFIED
// what stock then does with a lobby on another server). The friend's game
// must already be running: UNVERIFIED how a launch with kLoungeToken on the
// command line behaves.

#include "steam_tunnel_join.h"

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "net_optimizer.h"
#include "shim_log.h"
#include "socket_tunnel.h"

#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace SteamTunnelJoin
    {
        namespace
        {
            constexpr const char* kComponent = "TUNNELJOIN";
            constexpr const char* kPresenceKey = "openshim_tunnel";
            constexpr const char* kLoungeToken = "-openshim-steam-tunnel";
            constexpr uintptr_t kCallbackConnectOffset = 8;
            constexpr size_t kConnectBytes = 256;

            // push ebp / mov ebp,esp / push -1 / push imm32 (absolute SEH handler).
            constexpr uint8_t kJoinRequestedStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x83, 0xC6, 0x85, 0x00 };
            using FnJoinRequested = void(__fastcall*)(void* self, void* edx, const void* callback);

            using FnHandle = int(__cdecl*)();
            using FnPointer = void*(__cdecl*)();
            using FnGetInterface = void*(__cdecl*)(void* client, int user, int pipe, const char* version);
            using FnGetSteamId = uint64_t(__cdecl*)(void* user);
            using FnSetPresence = bool(__cdecl*)(void* friends, const char* key, const char* value);
            using FnGetPresence = const char*(__cdecl*)(void* friends, uint64_t id, const char* key);

            bool g_Done = false;
            bool g_Enabled = false;
            InlineDetour32 g_Detour = {};
            void* volatile g_Original = nullptr;

            // Game thread only below.
            void* g_Friends = nullptr;
            uint64_t g_Self = 0;
            FnSetPresence g_SetPresence = nullptr;
            FnGetPresence g_GetPresence = nullptr;
            bool g_SteamTried = false;
            bool g_LoggedNoInterface = false;
            DWORD g_GameThread = 0;  // set by Tick()
            uint64_t g_NextTick = 0;
            uint64_t g_Advertised = 0;
            bool g_LoungeSet = false;
            bool g_SelfReadsWork = false;
            bool g_LoggedSelfReads = false;
            bool g_StartupCaptured = false;
            uint64_t g_StartupHost = 0;
            bool g_StartupUdp = false;

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_STEAM_TUNNEL_JOIN", "BZR_DISABLE_STEAM_TUNNEL_JOIN" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool SafeCopy(void* dst, uintptr_t src, size_t len)
            {
                __try
                {
                    std::memcpy(dst, reinterpret_cast<const void*>(src), len);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // The Steam build loads steam_api.dll before the shim; GOG has none.
            bool ResolveSteam()
            {
                if (g_Friends)
                    return true;
                HMODULE dll = GetModuleHandleW(L"steam_api.dll");
                if (!dll)
                    return false;
                const auto user = reinterpret_cast<FnHandle>(GetProcAddress(dll, "SteamAPI_GetHSteamUser"));
                const auto pipe = reinterpret_cast<FnHandle>(GetProcAddress(dll, "SteamAPI_GetHSteamPipe"));
                const auto client = reinterpret_cast<FnPointer>(GetProcAddress(dll, "SteamClient"));
                const auto getFriends =
                    reinterpret_cast<FnGetInterface>(GetProcAddress(dll, "SteamAPI_ISteamClient_GetISteamFriends"));
                const auto getUser =
                    reinterpret_cast<FnGetInterface>(GetProcAddress(dll, "SteamAPI_ISteamClient_GetISteamUser"));
                const auto getId = reinterpret_cast<FnGetSteamId>(GetProcAddress(dll, "SteamAPI_ISteamUser_GetSteamID"));
                const auto set = reinterpret_cast<FnSetPresence>(GetProcAddress(dll, "SteamAPI_ISteamFriends_SetRichPresence"));
                const auto get =
                    reinterpret_cast<FnGetPresence>(GetProcAddress(dll, "SteamAPI_ISteamFriends_GetFriendRichPresence"));
                if (!user || !pipe || !client || !getFriends || !getUser || !getId || !set || !get)
                {
                    if (!g_SteamTried)
                        LogShimA(LogLevel::Warn, kComponent, "steam_api.dll lacks a needed export; Join Game support off");
                    g_SteamTried = true;
                    return false;
                }
                const int u = user(), p = pipe();
                void* c = (u && p) ? client() : nullptr;
                if (!c)
                    return false;  // Steam not up yet; retry next tick
                void* friends = getFriends(c, u, p, "SteamFriends015");
                void* steamUser = getUser(c, u, p, "SteamUser019");
                const uint64_t self = steamUser ? getId(steamUser) : 0;
                if (!friends || !SocketTunnel::IndividualSteamId(self))
                {
                    if (!g_LoggedNoInterface)
                        LogShimA(LogLevel::Warn, kComponent,
                                 "SteamFriends015/SteamUser019 not available yet (friends %p, self %llu); retrying",
                                 friends, static_cast<unsigned long long>(self));
                    g_LoggedNoInterface = true;
                    return false;
                }
                g_SetPresence = set;
                g_GetPresence = get;
                g_Self = self;
                g_Friends = friends;
                return true;
            }

            std::string Presence(uint64_t id, const char* key)
            {
                const char* value = g_GetPresence(g_Friends, id, key);
                return value ? std::string(value) : std::string();
            }

            uint64_t ReadAnnouncedBridge()
            {
                HANDLE mapping = OpenFileMappingW(FILE_MAP_READ, FALSE, SocketTunnel::kBridgeAnnounceMapping);
                if (!mapping)
                    return 0;
                uint64_t id = 0;
                if (const void* view = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, sizeof(id)))
                {
                    SafeCopy(&id, reinterpret_cast<uintptr_t>(view), sizeof(id));
                    UnmapViewOfFile(view);
                }
                CloseHandle(mapping);
                return SocketTunnel::IndividualSteamId(id) ? id : 0;
            }

            void CaptureStartup()
            {
                if (g_StartupCaptured)
                    return;
                // First join request precedes any switch of ours.
                g_StartupCaptured = true;
                g_StartupHost = SocketTunnel::SteamHost();
                g_StartupUdp = SocketTunnel::UdpBridgeConfigured();
            }

            // Game thread, Steam resolved. note gets a short player-facing reason.
            bool ApplySwitch(uint64_t target, std::string& note)
            {
                if (target == SocketTunnel::SteamHost())
                {
                    // Same host: nothing to do unless its worker died (e.g. a
                    // local server held 1337); then this join restarts it.
                    if (!target || !SocketTunnel::Failed())
                    {
                        note = "already connected through that server";
                        return true;
                    }
                    LogShimA(LogLevel::Info, kComponent, "tunnel to this host had stopped; restarting it");
                }
                if (g_StartupUdp)
                {
                    note = "TunnelUdpBridge is set in net.ini; Steam joins are off";
                    LogShimA(LogLevel::Warn, kComponent, "TunnelUdpBridge is configured; not switching to Steam");
                    return false;
                }
                if (target == g_Self)
                {
                    note = "that server is this account's own";
                    LogShimA(LogLevel::Info, kComponent, "the bridge is this account's own; not switching");
                    return false;
                }
                if (IsMissionSimulationActiveFromBridge())
                {
                    note = "leave the mission first";
                    LogShimA(LogLevel::Warn, kComponent, "in a mission: tunnel not switched; join from the menus");
                    return false;
                }
                if (!BzrNetLookupHookInstalled())
                {
                    note = "[OpenShimSocket] is off; Steam joins need it";
                    LogShimA(LogLevel::Warn, kComponent,
                             "BZRNet lookup hook not installed ([OpenShimSocket] off); cannot switch the tunnel live");
                    return false;
                }
                if (!SocketTunnel::SwitchSteamHost(target))
                {
                    note = "the Steam tunnel refused the switch";
                    LogShimA(LogLevel::Warn, kComponent, "tunnel switch refused");
                    return false;
                }
                if (!target)
                    Hooks::InitializeBzrNetConfig();  // put the route flag back to the user's preference
                const bool recycled = RecycleBzrNetWebSocket();
                LogShimA(LogLevel::Info, kComponent, "tunnel now %llu; BZRNet reconnect %s",
                         static_cast<unsigned long long>(target), recycled ? "started" : "not needed (no socket open)");
                note = "connecting through Steam";
                return true;
            }

            void SwitchTunnel(uint64_t inviter, const char* connect, bool lounge)
            {
                CaptureStartup();
                uint64_t bridge = 0;
                const std::string announced = Presence(inviter, kPresenceKey);
                if (!SocketTunnel::ParseSteamId(announced, bridge) && lounge)
                    bridge = SocketTunnel::IndividualSteamId(inviter) ? inviter : 0;
                const uint64_t target = bridge ? bridge : g_StartupHost;
                LogShimA(LogLevel::Info, kComponent, "join request from %llu (%s): tunnel presence %s, target %llu",
                         static_cast<unsigned long long>(inviter), lounge ? "lounge" : (connect[0] ? "lobby" : "empty"),
                         announced.empty() ? "none" : announced.c_str(), static_cast<unsigned long long>(target));
                std::string note;
                ApplySwitch(target, note);
            }

            void __fastcall JoinRequestedHook(void* self, void* edx, const void* callback)
            {
                const auto original = reinterpret_cast<FnJoinRequested>(g_Original);
                uint64_t inviter = 0;
                char connect[kConnectBytes + 1] = {};
                const uintptr_t cb = reinterpret_cast<uintptr_t>(callback);
                const bool read = cb && SafeCopy(&inviter, cb, sizeof(inviter)) &&
                                  SafeCopy(connect, cb + kCallbackConnectOffset, kConnectBytes);
                const bool lounge = read && std::strcmp(connect, kLoungeToken) == 0;
                // The switch joins the tunnel worker and recycles BZRNet: game
                // thread only. (Borrowed Steam never pumps callbacks on the worker.)
                if (read && GetCurrentThreadId() != g_GameThread)
                    LogShimA(LogLevel::Warn, kComponent, "join request off the game thread; tunnel not switched");
                else if (read && ResolveSteam())
                    SwitchTunnel(inviter, connect, lounge);
                if (!lounge && original)
                    original(self, edx, callback);
            }

            bool DoInstall()
            {
                uint32_t address = 0;
                // Literal name so patch_registration_tests can check it
                // against scripts/patches.json.
                const HookEngine::EngineRow rows[] = {
                    { "LobbyOnRichPresenceJoinRequested", &address },
                };
                if (!HookEngine::BindEngineRows("SteamTunnelJoin", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "address did not resolve; Steam tunnel join not installed");
                    return false;
                }
                if (!InstallInlineDetour32(g_Detour, address, reinterpret_cast<void*>(JoinRequestedHook),
                                           sizeof(kJoinRequestedStolen), kJoinRequestedStolen,
                                           sizeof(kJoinRequestedStolen), &g_Original))
                {
                    LogShimA(LogLevel::Warn, kComponent, "join handler failed its byte guard; not installed");
                    g_Detour = {};
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: rich-presence join handler 0x%08X", address);
                return true;
            }
        }

        void InstallSteamTunnelJoinIfPossible()
        {
            if (g_Done)
                return;
            g_Done = true;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled (OPENSHIM_DISABLE_STEAM_TUNNEL_JOIN)");
                return;
            }
            // The host half needs no hook; it runs from Tick().
            g_Enabled = true;
            DoInstall();
        }

        uint64_t AnnouncedBridge()
        {
            return ReadAnnouncedBridge();
        }

        bool JoinBridge(uint64_t bridge, std::string& note)
        {
            if (!g_Enabled)
            {
                note = "Steam tunnel join is disabled";
                return false;
            }
            if (!SocketTunnel::IndividualSteamId(bridge))
            {
                note = "not a valid Steam server";
                return false;
            }
            if (!ResolveSteam())
            {
                note = "Steam is not ready";
                return false;
            }
            g_GameThread = GetCurrentThreadId();
            CaptureStartup();
            LogShimA(LogLevel::Info, kComponent, "public listing join: target %llu",
                     static_cast<unsigned long long>(bridge));
            return ApplySwitch(bridge, note);
        }

        bool RestoreStartup(std::string& note)
        {
            if (!g_StartupCaptured || SocketTunnel::SteamHost() == g_StartupHost)
                return true; // never moved
            LogShimA(LogLevel::Info, kComponent, "LAN join: tunnel back to %llu",
                     static_cast<unsigned long long>(g_StartupHost));
            return ApplySwitch(g_StartupHost, note);
        }

        void Tick()
        {
            if (!g_Enabled)
                return;
            g_GameThread = GetCurrentThreadId();
            const uint64_t now = GetTickCount64();
            if (now < g_NextTick)
                return;
            g_NextTick = now + 2000;
            if (!ResolveSteam())
                return;

            const uint64_t bridge = ReadAnnouncedBridge();
            const std::string value = bridge ? std::to_string(bridge) : std::string();
            // Re-set when the game cleared it too (only checkable once self-reads work).
            const bool lost = bridge && bridge == g_Advertised && g_SelfReadsWork &&
                              Presence(g_Self, kPresenceKey) != value;
            if (bridge != g_Advertised || lost)
            {
                if (g_SetPresence(g_Friends, kPresenceKey, value.c_str()))
                {
                    LogShimA(LogLevel::Info, kComponent, !bridge ? "bridge gone; tunnel presence cleared"
                                                         : (lost ? "tunnel presence was cleared; re-advertising %llu"
                                                                 : "advertising tunnel bridge %llu in Steam presence"),
                             static_cast<unsigned long long>(bridge));
                    g_Advertised = bridge;
                }
                else if (bridge != g_Advertised)
                    LogShimA(LogLevel::Warn, kComponent, "SetRichPresence failed; retrying");
            }

            // Lounge Join Game: only where reading our own presence back works,
            // so the token never overwrites a lobby the game advertises.
            if (bridge && !g_SelfReadsWork)
            {
                g_SelfReadsWork = Presence(g_Self, kPresenceKey) == std::to_string(bridge);
                if (!g_SelfReadsWork && !g_LoggedSelfReads)
                {
                    g_LoggedSelfReads = true;
                    LogShimA(LogLevel::Info, kComponent, "own presence not readable yet; lounge Join Game waits");
                }
            }
            if (!g_SelfReadsWork)
                return;
            const std::string connect = Presence(g_Self, "connect");
            if (bridge && connect.empty())
            {
                g_SetPresence(g_Friends, "connect", kLoungeToken);
                if (!g_LoungeSet)
                    LogShimA(LogLevel::Info, kComponent, "no lobby advertised: Join Game opens this server's lounge");
                g_LoungeSet = true;
            }
            else if (!bridge && g_LoungeSet)
            {
                if (connect == kLoungeToken)
                    g_SetPresence(g_Friends, "connect", "");
                g_LoungeSet = false;
            }
        }
    }
}
