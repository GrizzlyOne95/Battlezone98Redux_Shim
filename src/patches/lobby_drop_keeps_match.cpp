// lobby_drop_keeps_match.cpp
// BZR Open Shim - keeps a running multiplayer match alive when only the BZRNet
// lobby websocket drops while the P2P game traffic is still flowing.
#include "lobby_drop_keeps_match.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"
#include <Windows.h>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // -----------------------------------------------------------------
        // Lobby drop keeps match
        // -----------------------------------------------------------------
        //
        // Recovered from the GOG 2.2.301 image (2026-10-26). Gameplay is P2P
        // UDP; the websocket only carries the lobby. Stock still ends the match
        // on any websocket loss:
        //
        //   0x006BF0D0  BZRNetInterface websocket close handler. "reset
        //               active_con due to websocket connection close", then,
        //               when a lobby is current (+0xC38), call 0x0074D250
        //               <- site "Local" at 0x006BF11B
        //   0x0074D250  leave-lobby cleanup: P2P session teardown (0x0075CEA0)
        //               and player-left (0x00578640) for the local id
        //   0x00578640  player-left, cdecl(const NetId*, bool kicked); for the
        //               local player it sets Net state ([0x00917F48]+8) = 5
        //   0x005715D0  Net Execute returns false in states 0/5/6, so
        //               DoNextFrame 0x00618130 logs "Quiting Game Due to Net
        //               Execute failure" and prints "Lost connection to game"
        //
        // The websocket reconnects on its own (46 ms in the 2026-10-26 log),
        // but by then the match is gone. The other players take the server's
        // member-left update for the same session through
        // CNetGameLobby::OnLobbyChatUpdate 0x0073EEB0, which calls player-left
        // for that member <- site "Remote" at 0x0073F13F, and drop a player
        // whose P2P is still live.
        //
        // Local: while a match is running and some remote peer was heard over
        // P2P within kFreshMs, skip the leave-lobby cleanup so the P2P session
        // and the Net state survive; the websocket reconnect proceeds as stock.
        // Remote: while a match is running, skip the lobby-driven drop of a
        // remote player heard over P2P within kFreshMs. Kicks and bans still
        // drop. A peer whose P2P really died is still flagged lagging and then
        // auto-kicked by the host's ping check (0x00576B70: 10 s + 10 s), and
        // a client whose P2P is silent too quits exactly as stock.

        namespace
        {
            constexpr uint32_t kFreshMs = 5000;   // stock flags "lagging" at 10000
            constexpr uint32_t kNetStateOffset = 0x08;
            constexpr uint32_t kNetStateInSession = 4;
            constexpr uint32_t kGameStatePlaying = 5;
            constexpr uint32_t kPlayerShortIdOffset = 0x28;
            constexpr uint32_t kPlayerLastHeardOffset = 0x40;
            constexpr uint32_t kPlayerIsLocalOffset = 0x8E;

            using LeaveLobbyFn = void(__thiscall*)(void* lobby);
            using PlayerLeftFn = void(__cdecl*)(const void* id, int kicked);
            using FindPlayerFn = uintptr_t(__cdecl*)(const void* id);
            using NextPlayerFn = uintptr_t(__cdecl*)(uintptr_t player);
            using GetU32Fn = uint32_t(__cdecl*)();
            using GetBoolFn = int(__cdecl*)();

            bool g_Enabled = false;
            LeaveLobbyFn g_LeaveLobby = nullptr;
            PlayerLeftFn g_PlayerLeft = nullptr;
            FindPlayerFn g_FindPlayer = nullptr;
            NextPlayerFn g_NextPlayer = nullptr;
            GetU32Fn g_Clock = nullptr;
            GetU32Fn g_GameState = nullptr;
            GetBoolFn g_GameEnded = nullptr;
            uintptr_t g_NetManagerSlot = 0;
            LONG g_LocalKept = 0;
            LONG g_RemoteKept = 0;

            bool ReadU32(uintptr_t address, uint32_t& out)
            {
                __try { out = *reinterpret_cast<const uint32_t*>(address); return true; }
                __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
            }

            bool ReadU8(uintptr_t address, uint8_t& out)
            {
                __try { out = *reinterpret_cast<const uint8_t*>(address); return true; }
                __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
            }

            bool ReadU16(uintptr_t address, uint16_t& out)
            {
                __try { out = *reinterpret_cast<const uint16_t*>(address); return true; }
                __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
            }

            // A running match: Net in session, game loop playing, no game-end
            // countdown. The lobby screens before launch keep stock behavior.
            bool MatchRunning(uint32_t& netState, uint32_t& gameState)
            {
                netState = gameState = 0;
                uint32_t net = 0;
                if (!ReadU32(g_NetManagerSlot, net) || !net ||
                    !ReadU32(net + kNetStateOffset, netState))
                    return false;
                gameState = g_GameState();
                return netState == kNetStateInSession && gameState == kGameStatePlaying && !(g_GameEnded() & 0xFF);
            }

            // Milliseconds since the player was last heard over P2P, or ~0u.
            uint32_t SinceHeard(uintptr_t player, uint32_t now)
            {
                uint32_t heard = 0;
                if (!ReadU32(player + kPlayerLastHeardOffset, heard) || !heard) return ~0u;
                return now - heard;
            }

            void __fastcall LocalLeaveLobbyHook(void* lobby)
            {
                uint32_t netState = 0, gameState = 0;
                if (g_Enabled && MatchRunning(netState, gameState))
                {
                    const uint32_t now = g_Clock();
                    uint32_t freshest = ~0u;
                    uint16_t freshestId = 0;
                    int peers = 0;
                    for (uintptr_t p = g_NextPlayer(0); p && peers < 64; p = g_NextPlayer(p), ++peers)
                    {
                        uint8_t local = 1;
                        if (!ReadU8(p + kPlayerIsLocalOffset, local) || local) continue;
                        const uint32_t since = SinceHeard(p, now);
                        if (since < freshest) { freshest = since; ReadU16(p + kPlayerShortIdOffset, freshestId); }
                    }
                    if (freshest <= kFreshMs)
                    {
                        const LONG n = InterlockedIncrement(&g_LocalKept);
                        Log(L"[LOBBYDROP] websocket closed mid-match; P2P peer %u heard %u ms ago, keeping the match (lobby leave skipped, #%ld)\n",
                            static_cast<unsigned>(freshestId), freshest, n);
                        return;
                    }
                    Log(L"[LOBBYDROP] websocket closed mid-match with no P2P peer heard within %u ms (freshest %u ms); stock leave\n",
                        kFreshMs, freshest);
                }
                g_LeaveLobby(lobby);
            }

            void __cdecl RemotePlayerLeftHook(const void* id, int kicked)
            {
                uint32_t netState = 0, gameState = 0;
                if (g_Enabled && !(kicked & 0xFF) && id && MatchRunning(netState, gameState))
                {
                    const uintptr_t player = g_FindPlayer(id);
                    uint8_t local = 1;
                    if (player && ReadU8(player + kPlayerIsLocalOffset, local) && !local)
                    {
                        const uint32_t since = SinceHeard(player, g_Clock());
                        uint16_t shortId = 0;
                        ReadU16(player + kPlayerShortIdOffset, shortId);
                        if (since <= kFreshMs)
                        {
                            const LONG n = InterlockedIncrement(&g_RemoteKept);
                            Log(L"[LOBBYDROP] player %u left the lobby mid-match but was heard over P2P %u ms ago; kept in the match (#%ld)\n",
                                static_cast<unsigned>(shortId), since, n);
                            return;
                        }
                        Log(L"[LOBBYDROP] player %u left the lobby mid-match, P2P silent for %u ms; stock drop\n",
                            static_cast<unsigned>(shortId), since);
                    }
                }
                g_PlayerLeft(id, kicked);
            }

            bool ResolveHelpers()
            {
                if (g_Clock) return true;
                const uint32_t slot = HookEngine::ResolveNamedAddress("Net::ManagerSlot");
                const uint32_t find = HookEngine::ResolveNamedAddress("Net::FindPlayer");
                const uint32_t next = HookEngine::ResolveNamedAddress("Net::NextPlayer");
                const uint32_t clock = HookEngine::ResolveNamedAddress("Net::Clock");
                const uint32_t state = HookEngine::ResolveNamedAddress("GameState::Get");
                const uint32_t ended = HookEngine::ResolveNamedAddress("Net::GameEnded");
                if (!slot || !find || !next || !clock || !state || !ended)
                {
                    Log(L"[LOBBYDROP] helper unresolved (slot=0x%08X find=0x%08X next=0x%08X clock=0x%08X state=0x%08X ended=0x%08X); stock kept\n",
                        slot, find, next, clock, state, ended);
                    return false;
                }
                g_NetManagerSlot = slot;
                g_FindPlayer = reinterpret_cast<FindPlayerFn>(static_cast<uintptr_t>(find));
                g_NextPlayer = reinterpret_cast<NextPlayerFn>(static_cast<uintptr_t>(next));
                g_GameState = reinterpret_cast<GetU32Fn>(static_cast<uintptr_t>(state));
                g_GameEnded = reinterpret_cast<GetBoolFn>(static_cast<uintptr_t>(ended));
                g_Clock = reinterpret_cast<GetU32Fn>(static_cast<uintptr_t>(clock));
                return true;
            }
        }

        bool IsLobbyDropKeepsMatchPatchName(const char* name)
        {
            return name && strncmp(name, "Lobby Drop Keeps Match ", 23) == 0;
        }

        uint32_t PrepareLobbyDropKeepsMatchHook(const char* name, uint32_t site, void* original)
        {
            bool enabled = true;  // default on: the drop it prevents is a stock defect
            TryGetUserConfigBool("Network", "LobbyDropKeepsMatch", enabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_LOBBY_DROP_KEEPS_MATCH") ||
                EnvFlagEnabled("BZR_DISABLE_LOBBY_DROP_KEEPS_MATCH"))
                enabled = false;
            if (!enabled || !ResolveHelpers()) return 0;

            const bool local = strcmp(name, "Lobby Drop Keeps Match Local") == 0;
            const uint32_t expected = local
                ? HookEngine::ResolveNamedAddress("Net::LeaveLobbyOnClose")
                : HookEngine::ResolveNamedAddress("Net::PlayerLeft");
            if (!original || !expected || reinterpret_cast<uintptr_t>(original) != expected)
            {
                Log(L"[LOBBYDROP] %hs identity failed site=0x%08X original=%p expected=0x%08X; stock call kept\n",
                    name, site, original, expected);
                return 0;
            }
            g_Enabled = true;
            Log(L"[LOBBYDROP] %hs redirected site=0x%08X original=%p fresh=%u ms\n", name, site, original, kFreshMs);
            if (local)
            {
                g_LeaveLobby = reinterpret_cast<LeaveLobbyFn>(original);
                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&LocalLeaveLobbyHook));
            }
            g_PlayerLeft = reinterpret_cast<PlayerLeftFn>(original);
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&RemotePlayerLeftHook));
        }
    }
}
