// steam_public_listing.cpp -- see include/steam_public_listing.h.
//
// Uses the flat API of the game's own steam_api.dll (SDK era of
// SteamClient017 / SteamUser019 / SteamUtils008) on the game's Steam
// session. Call results are polled with ISteamUtils::GetAPICallResult on the
// game thread, so nothing is registered with the game's callback manager.
//
// Creating a lobby also enters it, and Steam posts LobbyEnter_t to every
// registered handler. The game's CNetGameLobby::OnLobbyEntered (0x0073E240,
// reached from its LobbyEnter_t callback 0x00750F90) adopts any lobby it did
// not create itself: it leaves its current lobby and treats the entered one
// as its game room. So the advert is only created once a guard on 0x00750F90
// is in place that keeps the advert's LobbyEnter_t away from the game.

#include "steam_public_listing.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "socket_tunnel.h"
#include "steam_tunnel_join.h"

#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace BZROpenShim
{
    extern bool g_IsSteamExe; // bzr_hooks.cpp
    namespace SteamPublicListing
    {
        namespace
        {
            constexpr const char* kComponent = "STEAMLIST";
            // Filter key and value: only OpenShim adverts carry it.
            constexpr const char* kTagKey = "openshim";
            constexpr const char* kTagValue = "tunnel1";
            constexpr const char* kBridgeKey = "bridge";
            constexpr const char* kNameKey = "name";
            constexpr int kLobbyPublic = 2;            // k_ELobbyTypePublic
            constexpr int kMaxMembers = 250;           // never full: search hides full lobbies
            constexpr int kDistanceWorldwide = 3;      // k_ELobbyDistanceFilterWorldwide
            constexpr int kCompareEqual = 0;           // k_ELobbyComparisonEqual
            constexpr int kLobbyCreatedCallback = 513; // LobbyCreated_t
            constexpr int kLobbyMatchListCallback = 510; // LobbyMatchList_t
            constexpr int kResultOk = 1;
            constexpr size_t kMaxName = 40;

#pragma pack(push, 8) // Valve callback packing on Windows
            struct LobbyCreated { int result; uint64_t lobby; };
            struct LobbyMatchList { uint32_t count; };
            struct LobbyEnter { uint64_t lobby; uint32_t permissions; bool locked; uint32_t response; };
#pragma pack(pop)
            static_assert(sizeof(LobbyEnter) == 24, "LobbyEnter_t layout");

            using Call = uint64_t;
            using FnHandle = int(__cdecl*)();
            using FnPointer = void*(__cdecl*)();
            using FnGetInterface = void*(__cdecl*)(void* client, int user, int pipe, const char* version);
            using FnGetUtils = void*(__cdecl*)(void* client, int pipe, const char* version);
            using FnGetSteamId = uint64_t(__cdecl*)(void* user);
            using FnCreateLobby = Call(__cdecl*)(void* mm, int type, int maxMembers);
            using FnSetLobbyData = bool(__cdecl*)(void* mm, uint64_t lobby, const char* key, const char* value);
            using FnGetLobbyData = const char*(__cdecl*)(void* mm, uint64_t lobby, const char* key);
            using FnLeaveLobby = void(__cdecl*)(void* mm, uint64_t lobby);
            using FnStringFilter = void(__cdecl*)(void* mm, const char* key, const char* value, int comparison);
            using FnIntFilter = void(__cdecl*)(void* mm, int value);
            using FnRequestList = Call(__cdecl*)(void* mm);
            using FnLobbyByIndex = uint64_t(__cdecl*)(void* mm, int index);
            using FnLobbyOwner = uint64_t(__cdecl*)(void* mm, uint64_t lobby);
            using FnCallFailed = bool(__cdecl*)(void* utils, Call call, bool* failed);
            using FnCallResult = bool(__cdecl*)(void* utils, Call call, void* out, int size, int expected, bool* failed);
            using FnPersonaName = const char*(__cdecl*)(void* friends);

            struct Api
            {
                void* mm = nullptr;
                void* utils = nullptr;
                void* friends = nullptr;
                uint64_t self = 0;
                FnCreateLobby createLobby = nullptr;
                FnSetLobbyData setData = nullptr;
                FnGetLobbyData getData = nullptr;
                FnLeaveLobby leave = nullptr;
                FnStringFilter stringFilter = nullptr;
                FnIntFilter distanceFilter = nullptr;
                FnIntFilter countFilter = nullptr;
                FnRequestList requestList = nullptr;
                FnLobbyByIndex byIndex = nullptr;
                FnLobbyOwner owner = nullptr;
                FnCallFailed completed = nullptr;
                FnCallResult result = nullptr;
                FnPersonaName persona = nullptr;
            };

            // Game thread only below.
            Api g_Api;
            bool g_Resolved = false, g_ExportsMissing = false;
            int g_Listing = -1; // -1 unread, 0 off, 1 on
            enum class Host { Idle, Creating, Listed } g_Host = Host::Idle;
            Call g_CreateCall = 0;
            uint64_t g_Lobby = 0, g_ListedBridge = 0;
            uint64_t g_HostRetryAfter = 0, g_NextHostCheck = 0;
            // Steam can sit on a call while it reconnects; give up after this.
            constexpr uint64_t kCallTimeoutMs = 15000;
            uint64_t g_CreateDeadline = 0, g_BrowseDeadline = 0;
            // A create we gave up on: its lobby is left as soon as it lands.
            Call g_OrphanCall = 0;
            std::string g_HostText;
            Call g_BrowseCall = 0;
            bool g_BrowseWanted = false;
            std::vector<Game> g_Games;
            std::string g_BrowseText;

            // Guard on the game's LobbyEnter_t handler (see the file comment).
            using FnEnterRun = void(__fastcall*)(void* self, void* edx, LobbyEnter* data);
            constexpr size_t kEnterPatchLen = 6; // push ebp; mov ebp,esp; sub esp,28h
            InlineDetour32 g_EnterDetour;
            FnEnterRun g_EnterOriginal = nullptr;
            int g_Guard = 0; // 0 not yet, 1 installed, -1 cannot install on this build
            // Lobbies we made and left, whose LobbyEnter_t may still be queued.
            uint64_t g_Strays[4] = {};
            size_t g_NextStray = 0;
            // An enter seen while our create is in flight, owned by us, before
            // the create result names the lobby. Replayed if it was not ours.
            struct Held { LobbyEnter data; void* self; };
            Held g_Held[2] = {};

            bool KillSwitched()
            {
                static int cached = -1;
                if (cached < 0)
                {
                    bool enabled = true;
                    static const EnvSwitches::EnvSwitch rows[] = {
                        { &enabled, EnvSwitches::Kind::KillSwitch,
                          "OPENSHIM_DISABLE_STEAM_PUBLIC_LISTING", "BZR_DISABLE_STEAM_PUBLIC_LISTING" },
                    };
                    EnvSwitches::Apply(rows, EnvFlagEnabled);
                    cached = enabled ? 0 : 1;
                }
                return cached == 1;
            }

            template <typename T> bool Get(HMODULE dll, const char* name, T& out)
            {
                out = reinterpret_cast<T>(GetProcAddress(dll, name));
                return out != nullptr;
            }

            bool Resolve()
            {
                if (g_Resolved)
                    return true;
                if (g_ExportsMissing || KillSwitched())
                    return false;
                HMODULE dll = GetModuleHandleW(L"steam_api.dll");
                if (!dll)
                    return false;
                FnHandle user = nullptr, pipe = nullptr;
                FnPointer client = nullptr;
                FnGetInterface getMm = nullptr, getFriends = nullptr, getUser = nullptr;
                FnGetUtils getUtils = nullptr;
                FnGetSteamId getId = nullptr;
                Api a;
                const bool ok =
                    Get(dll, "SteamAPI_GetHSteamUser", user) && Get(dll, "SteamAPI_GetHSteamPipe", pipe) &&
                    Get(dll, "SteamClient", client) &&
                    Get(dll, "SteamAPI_ISteamClient_GetISteamMatchmaking", getMm) &&
                    Get(dll, "SteamAPI_ISteamClient_GetISteamFriends", getFriends) &&
                    Get(dll, "SteamAPI_ISteamClient_GetISteamUser", getUser) &&
                    Get(dll, "SteamAPI_ISteamClient_GetISteamUtils", getUtils) &&
                    Get(dll, "SteamAPI_ISteamUser_GetSteamID", getId) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_CreateLobby", a.createLobby) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_SetLobbyData", a.setData) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_GetLobbyData", a.getData) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_LeaveLobby", a.leave) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter", a.stringFilter) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter", a.distanceFilter) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter", a.countFilter) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_RequestLobbyList", a.requestList) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_GetLobbyByIndex", a.byIndex) &&
                    Get(dll, "SteamAPI_ISteamMatchmaking_GetLobbyOwner", a.owner) &&
                    Get(dll, "SteamAPI_ISteamUtils_IsAPICallCompleted", a.completed) &&
                    Get(dll, "SteamAPI_ISteamUtils_GetAPICallResult", a.result) &&
                    Get(dll, "SteamAPI_ISteamFriends_GetPersonaName", a.persona);
                if (!ok)
                {
                    g_ExportsMissing = true;
                    LogShimA(LogLevel::Warn, kComponent, "steam_api.dll lacks a needed export; public listing off");
                    return false;
                }
                const int u = user(), p = pipe();
                void* c = (u && p) ? client() : nullptr;
                if (!c)
                    return false; // Steam not up yet; retry later
                a.mm = getMm(c, u, p, "SteamMatchMaking009");
                a.friends = getFriends(c, u, p, "SteamFriends015");
                a.utils = getUtils(c, p, "SteamUtils008");
                void* steamUser = getUser(c, u, p, "SteamUser019");
                a.self = steamUser ? getId(steamUser) : 0;
                if (!a.mm || !a.friends || !a.utils || !SocketTunnel::IndividualSteamId(a.self))
                    return false;
                g_Api = a;
                g_Resolved = true;
                return true;
            }

            // Steam keeps a finished result until it is fetched once.
            // Returns false while pending; ok=false on failure.
            template <typename T> bool Poll(Call& call, int callback, T& out, bool& ok)
            {
                bool failed = false;
                if (!g_Api.completed(g_Api.utils, call, &failed))
                {
                    if (!failed)
                        return false; // still pending
                    ok = false;       // bad handle
                }
                else
                    ok = g_Api.result(g_Api.utils, call, &out, int(sizeof(T)), callback, &failed) && !failed;
                call = 0;
                return true;
            }

            std::string Clean(const char* text)
            {
                std::string out;
                for (const char* p = text ? text : ""; *p && out.size() < kMaxName; ++p)
                    out += (static_cast<unsigned char>(*p) >= 32 && static_cast<unsigned char>(*p) < 127) ? *p : '?';
                return out;
            }

            void SetHostText(const std::string& text)
            {
                if (text == g_HostText)
                    return;
                g_HostText = text;
                LogShimA(LogLevel::Info, kComponent, "host: %s", text.c_str());
            }

            bool IsStray(uint64_t lobby)
            {
                for (const uint64_t id : g_Strays)
                    if (id && id == lobby)
                        return true;
                return false;
            }

            void AddStray(uint64_t lobby)
            {
                if (!lobby || IsStray(lobby))
                    return;
                g_Strays[g_NextStray] = lobby;
                g_NextStray = (g_NextStray + 1) % (sizeof(g_Strays) / sizeof(g_Strays[0]));
            }

            void LeaveOurs(uint64_t lobby)
            {
                if (!lobby)
                    return;
                g_Api.leave(g_Api.mm, lobby);
                AddStray(lobby);
            }

            // Steam dispatches callbacks on the game thread, as Tick runs.
            void __fastcall EnterHook(void* self, void* edx, LobbyEnter* data)
            {
                if (data && data->lobby)
                {
                    if (data->lobby == g_Lobby || IsStray(data->lobby))
                    {
                        LogShimA(LogLevel::Info, kComponent, "kept the advert lobby away from the game");
                        return;
                    }
                    if (g_Host == Host::Creating && g_Resolved && g_Api.owner(g_Api.mm, data->lobby) == g_Api.self)
                        for (Held& slot : g_Held)
                            if (!slot.data.lobby)
                            {
                                slot = {*data, self}; // decided when the create result arrives
                                return;
                            }
                }
                g_EnterOriginal(self, edx, data);
            }

            // Held enters that are not the advert go back to the game. advert 0
            // (the create failed or timed out) gives every held enter back:
            // a failed create entered no lobby, so a held one is the game's.
            void ReleaseHeld(uint64_t advert)
            {
                for (Held& slot : g_Held)
                {
                    Held held = slot;
                    slot = {};
                    if (!held.data.lobby || held.data.lobby == advert)
                        continue;
                    LogShimA(LogLevel::Warn, kComponent, "replaying a lobby enter that was not the advert");
                    g_EnterOriginal(held.self, nullptr, &held.data);
                }
            }

            bool EnsureGuard()
            {
                if (g_Guard)
                    return g_Guard > 0;
                const uint32_t target = HookEngine::EngineAddress("SteamLobbyEnterRun");
                if (!target)
                    return false; // unbound, or SteamStub not finished: asked again later
                const uint8_t* live = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(target));
                if (!InstallInlineDetour32(g_EnterDetour, target, reinterpret_cast<void*>(&EnterHook), kEnterPatchLen,
                                           live, kEnterPatchLen))
                {
                    g_Guard = -1;
                    LogShimA(LogLevel::Warn, kComponent,
                             "could not guard the game's lobby-enter handler; hosting a listing is off");
                    return false;
                }
                g_EnterOriginal = reinterpret_cast<FnEnterRun>(g_EnterDetour.trampoline);
                g_Guard = g_EnterOriginal ? 1 : -1;
                LogShimA(LogLevel::Info, kComponent, "lobby-enter guard at 0x%08X", target);
                return g_Guard > 0;
            }

            void Unlist(const char* why)
            {
                LeaveOurs(g_Lobby);
                // A create still in flight is dropped: its lobby, if made,
                // is left as soon as its result arrives (see TickHost).
                g_Lobby = g_ListedBridge = 0;
                if (g_Host == Host::Listed)
                    g_Host = Host::Idle;
                SetHostText(why);
            }

            void TickHost(uint64_t now)
            {
                if (g_OrphanCall)
                {
                    LobbyCreated late{};
                    bool lateOk = false;
                    if (Poll(g_OrphanCall, kLobbyCreatedCallback, late, lateOk) && lateOk &&
                        late.result == kResultOk)
                        LeaveOurs(late.lobby);
                }
                if (g_Host == Host::Creating)
                {
                    LobbyCreated created{};
                    bool ok = false;
                    if (!Poll(g_CreateCall, kLobbyCreatedCallback, created, ok))
                    {
                        if (now < g_CreateDeadline)
                            return;
                        // Stop holding the game's enters; leave the advert if it lands late.
                        g_OrphanCall = g_CreateCall;
                        g_CreateCall = 0;
                        g_Host = Host::Idle;
                        g_ListedBridge = 0;
                        ReleaseHeld(0);
                        g_HostRetryAfter = now + 60000;
                        SetHostText("Steam listing timed out; retrying in 60 s");
                        LogShimA(LogLevel::Warn, kComponent, "CreateLobby timed out");
                        return;
                    }
                    g_Host = Host::Idle;
                    const uint64_t bridge = SteamTunnelJoin::AnnouncedBridge();
                    if (!ok || created.result != kResultOk || !created.lobby)
                    {
                        ReleaseHeld(0);
                        g_HostRetryAfter = now + 60000;
                        SetHostText("Steam listing failed; retrying in 60 s");
                        LogShimA(LogLevel::Warn, kComponent, "CreateLobby failed (call ok %d, result %d)", ok ? 1 : 0,
                                 created.result);
                        return;
                    }
                    ReleaseHeld(created.lobby);
                    if (!HostListingOn() || !bridge || bridge != g_ListedBridge)
                    {
                        LeaveOurs(created.lobby); // changed while creating
                        g_ListedBridge = 0;
                        return;
                    }
                    const std::string id = std::to_string(bridge);
                    const std::string name = Clean(g_Api.persona(g_Api.friends));
                    // The tag goes last, so a search never sees a half-made advert.
                    if (!g_Api.setData(g_Api.mm, created.lobby, kBridgeKey, id.c_str()) ||
                        !g_Api.setData(g_Api.mm, created.lobby, kNameKey, name.c_str()) ||
                        !g_Api.setData(g_Api.mm, created.lobby, kTagKey, kTagValue))
                    {
                        LeaveOurs(created.lobby);
                        g_ListedBridge = 0;
                        g_HostRetryAfter = now + 60000;
                        SetHostText("Steam listing failed; retrying in 60 s");
                        return;
                    }
                    g_Lobby = created.lobby;
                    g_Host = Host::Listed;
                    SetHostText("Listed on Steam: players worldwide can find this server");
                    return;
                }
                if (now < g_NextHostCheck)
                    return;
                g_NextHostCheck = now + 2000;
                const uint64_t bridge = SteamTunnelJoin::AnnouncedBridge();
                if (!HostListingOn())
                {
                    if (g_Host == Host::Listed)
                        Unlist("Not listed on Steam");
                    else
                        SetHostText("Not listed on Steam");
                    return;
                }
                if (!bridge)
                {
                    if (g_Host == Host::Listed)
                        Unlist("Steam listing waits for the Steam bridge (start a server on this PC)");
                    else
                        SetHostText("Steam listing waits for the Steam bridge (start a server on this PC)");
                    return;
                }
                if (g_Host == Host::Listed && bridge != g_ListedBridge)
                    Unlist("Steam bridge changed; relisting");
                if (g_Host == Host::Listed)
                {
                    // Steam can drop us from the lobby (connection loss); the
                    // tag then reads empty and a fresh advert is made.
                    const char* tag = g_Api.getData(g_Api.mm, g_Lobby, kTagKey);
                    if (!tag || std::strcmp(tag, kTagValue) != 0)
                        Unlist("Steam listing lost; relisting");
                }
                if (g_Host == Host::Idle && !g_OrphanCall && now >= g_HostRetryAfter)
                {
                    if (!EnsureGuard())
                    {
                        SetHostText(g_Guard < 0 ? "Steam listing is not supported on this game build"
                                                : "Steam listing waits for the game to finish loading");
                        return;
                    }
                    g_CreateCall = g_Api.createLobby(g_Api.mm, kLobbyPublic, kMaxMembers);
                    if (!g_CreateCall)
                    {
                        g_HostRetryAfter = now + 60000;
                        SetHostText("Steam listing failed; retrying in 60 s");
                        return;
                    }
                    g_ListedBridge = bridge;
                    g_CreateDeadline = now + kCallTimeoutMs;
                    g_Host = Host::Creating;
                    SetHostText("Listing on Steam...");
                }
            }

            void TickBrowse(uint64_t now)
            {
                if (g_BrowseWanted && !g_BrowseCall)
                {
                    g_BrowseWanted = false;
                    g_Api.stringFilter(g_Api.mm, kTagKey, kTagValue, kCompareEqual);
                    g_Api.distanceFilter(g_Api.mm, kDistanceWorldwide);
                    g_Api.countFilter(g_Api.mm, 50);
                    g_BrowseCall = g_Api.requestList(g_Api.mm);
                    g_BrowseText = g_BrowseCall ? "Steam: searching" : "Steam: search failed";
                    g_BrowseDeadline = now + kCallTimeoutMs;
                    return;
                }
                if (!g_BrowseCall)
                    return;
                LobbyMatchList list{};
                bool ok = false;
                if (!Poll(g_BrowseCall, kLobbyMatchListCallback, list, ok))
                {
                    if (now >= g_BrowseDeadline)
                    {
                        g_BrowseCall = 0; // a late result is never fetched
                        g_BrowseText = "Steam: search timed out";
                    }
                    return;
                }
                g_Games.clear();
                if (!ok)
                {
                    g_BrowseText = "Steam: search failed";
                    return;
                }
                for (uint32_t i = 0; i < list.count && i < 50; ++i)
                {
                    const uint64_t lobby = g_Api.byIndex(g_Api.mm, int(i));
                    if (!lobby)
                        continue;
                    uint64_t bridge = 0;
                    const char* id = g_Api.getData(g_Api.mm, lobby, kBridgeKey);
                    // The in-game bridge is the host's own account, so only the
                    // lobby owner may advertise it: nobody can list another
                    // player's bridge. Steam documents the owner only for
                    // lobbies we are in; if it reads 0 here the check is skipped
                    // (UNVERIFIED). One row per bridge.
                    const uint64_t owner = g_Api.owner(g_Api.mm, lobby);
                    if (!SocketTunnel::ParseSteamId(id ? id : "", bridge) || bridge == g_Api.self ||
                        (owner && owner != bridge))
                        continue; // our own advert, malformed, or spoofed
                    bool seen = false;
                    for (const Game& known : g_Games)
                        seen = seen || known.bridge == bridge;
                    if (seen)
                        continue;
                    Game game;
                    game.bridge = bridge;
                    game.name = Clean(g_Api.getData(g_Api.mm, lobby, kNameKey));
                    if (game.name.empty())
                        game.name = "OpenShim server";
                    g_Games.push_back(game);
                }
                g_BrowseText = g_Games.empty() ? "Steam: none listed" : "Steam: " + std::to_string(g_Games.size());
                LogShimA(LogLevel::Info, kComponent, "search: %u adverts, %u listed", list.count,
                         static_cast<unsigned>(g_Games.size()));
            }
        }

        bool Available()
        {
            // GOG also ships a steam_api.dll, so the module alone does not mean Steam.
            return g_IsSteamExe && !KillSwitched() && !g_ExportsMissing && GetModuleHandleW(L"steam_api.dll") != nullptr;
        }

        uint64_t LocalSteamId()
        {
            return Available() && Resolve() ? g_Api.self : 0;
        }

        bool HostListingOn()
        {
            if (g_Listing < 0)
            {
                std::string value;
                g_Listing = TryGetUserConfigString("Network", "SteamPublicListing", value) && value == "1" ? 1 : 0;
            }
            return g_Listing == 1;
        }

        void SetHostListing(bool on)
        {
            g_Listing = on ? 1 : 0;
            g_NextHostCheck = 0; // act on the next tick
            g_HostRetryAfter = 0;
            if (!WriteShimUserConfigValue("Network", "SteamPublicListing", on ? "1" : "0"))
                LogShimA(LogLevel::Warn, kComponent, "could not save SteamPublicListing");
        }

        std::string HostListingText()
        {
            if (!Available())
                return "Steam listing needs the Steam build";
            return g_HostText.empty() ? (HostListingOn() ? "Listing on Steam..." : "Not listed on Steam") : g_HostText;
        }

        void StartBrowse()
        {
            if (!Available())
                return;
            g_BrowseWanted = true; // a search in flight finishes first, then this one runs
            if (!g_BrowseCall)
                g_BrowseText = "Steam: searching";
        }

        const std::vector<Game>& Games()
        {
            return g_Games;
        }

        std::string BrowseText()
        {
            return g_BrowseText;
        }

        void Tick()
        {
            if (!g_IsSteamExe || !Resolve())
                return;
            TickHost(GetTickCount64());
            TickBrowse(GetTickCount64());
        }
    }
}
