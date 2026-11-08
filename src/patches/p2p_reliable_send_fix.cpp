// p2p_reliable_send_fix.cpp
// BZR Open Shim - lets a BZRNet P2P peer that is retransmitting still send
// new reliable messages immediately, so a reliable backlog drains instead of
// starving the link of every unreliable update.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "p2p_reliable_send_fix.h"
#include "p2p_reliable_send_policy.h"
#include "patcher.h"
#include <Windows.h>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace BZROpenShim
{
    namespace Hooks
    {
        // -----------------------------------------------------------------
        // P2P reliable send backlog
        // -----------------------------------------------------------------
        //
        // Recovered from the GOG 2.2.301 image. A connected peer (state 8)
        // keeps its outbound reliable queue at peer+0xA4, its next send
        // sequence at peer+0x88 and the sequence it expects back at
        // peer+0x84.
        //
        //   0x0075BEB0  P2P send. A reliable message is split into <=0x5AA
        //               byte fragments; each is stamped with peer+0x88 and
        //               appended to the queue, then sent at once unless the
        //               gate below skips it. peer+0x88 advances either way.
        //   0x0075C72A  the gate: movzx edx, byte [peer+0x1A] / test /
        //               jne 0x0075C972 skips the immediate send.
        //   0x0075AAF0  retry pump. When the queue is non-empty it sets
        //               peer+0x1A, resends the queue within a budget of
        //               5000 / peerCount bytes, and re-arms a 2.5 s timer;
        //               peer+0x1A clears only on a pump that finds the queue
        //               empty.
        //   0x0075D800  receive. Any packet, reliable or not, is accepted only
        //               when its stamp equals peer+0x84, so an unreliable
        //               update stamped past a reliable fragment the receiver
        //               has not yet seen is dropped.
        //
        // Together these lock a busy link: once a retry pass runs, every new
        // reliable fragment waits for the next pump, every unreliable update
        // carries a stamp the receiver cannot accept, and if the game queues
        // reliable traffic faster than the pump's budget the queue is never
        // empty when the pump looks, so the link never leaves that mode. Players
        // see it as 100% loss and climbing ping, most often with three or more
        // players (more reliable traffic per link, a smaller per-peer budget).
        // A four-player run on 2026-10-07 dropped 600-750 updates per guest
        // link while the relay forwarded every datagram.
        //
        // The fix removes only the jne, so a new fragment is always sent once
        // immediately. It stays in the queue exactly as before and the pump
        // still retransmits it until it is acknowledged; the wire format and
        // the receiver are untouched, so stock peers see an ordinary sender
        // that is merely on time.

        void ConfigureP2PReliablePatches(std::vector<HookEngine::PatchDef>& patches)
        {
            bool enabled = true;
            TryGetUserConfigBool("Network", "ReliableSendBacklogFix", enabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX") ||
                EnvFlagEnabled("BZR_DISABLE_RELIABLE_SEND_BACKLOG_FIX"))
                enabled = false;
            if (!enabled)
                Log(L"[P2PSEND] Reliable send backlog fix disabled; stock retry gating kept\n");

            for (auto& patch : patches)
            {
                if (patch.name == "P2P Reliable Send Backlog")
                {
                    if (!enabled) continue;
                    if (!patch.verified || !patch.address)
                    {
                        Log(L"[P2PSEND] Reliable send signature unavailable; stock retry gating kept\n");
                        continue;
                    }
                    patch.payload = { 0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00 };
                    continue;
                }

                const char* key = nullptr;
                uint32_t stockMs = 0;
                uint32_t defaultMs = 0;
                if (patch.name == "P2P Reliable First Retry")
                {
                    key = "ReliableFirstRetryMs";
                    stockMs = P2PReliable::kFirstRetryStockMs;
                    defaultMs = P2PReliable::kFirstRetryDefaultMs;
                }
                else if (patch.name == "P2P Reliable Retry Interval")
                {
                    key = "ReliableRetryIntervalMs";
                    stockMs = P2PReliable::kRetryIntervalStockMs;
                    defaultMs = P2PReliable::kRetryIntervalDefaultMs;
                }
                else continue;

                uint32_t ms = defaultMs;
                std::string text;
                if (TryGetUserConfigString("Network", key, text) &&
                    !P2PReliable::ParseRetryMs(text, ms))
                {
                    Log(L"[P2PSEND] Invalid %hs; decimal %u-%u ms required; stock %u ms kept\n",
                        key, P2PReliable::kRetryMinMs, P2PReliable::kRetryMaxMs, stockMs);
                    continue;
                }
                if (ms == stockMs) continue;
                if (!patch.verified || !patch.address)
                {
                    Log(L"[P2PSEND] Signature unavailable; %hs stays %u ms\n", key, stockMs);
                    continue;
                }
                const auto* bytes = reinterpret_cast<const uint8_t*>(&ms);
                patch.payload.assign(bytes, bytes + sizeof(ms));
                Log(L"[P2PSEND] %hs requested %u ms (stock %u); guarded write follows\n", key, ms, stockMs);
            }
        }

        // -----------------------------------------------------------------
        // Ping-adaptive reliable retry wait
        // -----------------------------------------------------------------
        //
        // Both retry timers are armed through the deadline helper 0x0075FE50
        // (__thiscall, ecx = deadline object, uint32 lo_ms, uint32 hi_ms,
        // `ret 8`). At 350 ms round trip the 300 ms first retry fires before
        // the ACK can arrive and nearly every reliable packet is resent. The
        // two call sites are redirected to naked stubs that hand the transport
        // peer record to a wrapper in edx (pump: eax from the iterator deref;
        // send: [ebp-0x78]). The wrapper raises the low word to 1.5x THAT
        // peer's round trip (P2PReliable::AdaptiveRetryMs) and calls the
        // original helper, so the configured imm32 patches keep working
        // untouched. A peer is matched to a Player by the remote address
        // (peer+0x08 vs Player+0x30, dwords 0, 2, 3 like the engine's own
        // comparator); no match falls back to the worst peer round trip.
        // Pings come from the game's own player list: 0x00577B50 (__cdecl,
        // next Player*) and 0x00575F80 (__thiscall, average RTT over the
        // player's pong ring). Everything runs on the game thread, the same
        // thread as the retry pump.
        namespace
        {
            using DeadlineFn = void*(__fastcall*)(void* self, void* peer, uint32_t lo, uint32_t hi);
            using NextPlayerFn = int(__cdecl*)(int prev);
            using PlayerPingFn = uint32_t(__fastcall*)(void* player, void* edx);

            DeadlineFn g_firstRetryOriginal = nullptr;
            DeadlineFn g_intervalOriginal = nullptr;
            NextPlayerFn g_nextPlayer = nullptr;
            PlayerPingFn g_playerPing = nullptr;

            constexpr ULONGLONG kRttRefreshMs = 500;
            constexpr ULONGLONG kRttFaultBackoffMs = 10000;
            constexpr ULONGLONG kLogMinGapMs = 10000;
            constexpr int kMaxPlayers = 64;
            constexpr uintptr_t kPlayerAddrOffset = 0x30;
            constexpr uintptr_t kPeerAddrOffset = 0x08;

            ULONGLONG g_nextRttRefresh = 0;
            P2PReliable::PeerRttEntry g_peerTable[kMaxPlayers] = {};
            size_t g_peerCount = 0;
            uint32_t g_maxRttMs = 0;
            uint32_t g_lastFirstMs = 0;
            uint32_t g_lastIntervalMs = 0;
            uint32_t g_loggedFirstMs = 0;
            uint32_t g_matchedCount = 0;
            uint32_t g_fallbackCount = 0;
            ULONGLONG g_lastLogTick = 0;

            // No C++ objects with destructors: __try cannot share a frame with them.
            bool ReadPeerTable()
            {
                size_t count = 0;
                uint32_t maxRtt = 0;
                __try
                {
                    int player = g_nextPlayer(0);
                    for (int i = 0; player != 0 && i < kMaxPlayers; ++i)
                    {
                        const uint32_t rtt = g_playerPing(
                            reinterpret_cast<void*>(static_cast<uintptr_t>(player)), nullptr);
                        if (rtt > maxRtt) maxRtt = rtt;
                        const uint32_t* addr = reinterpret_cast<const uint32_t*>(
                            static_cast<uintptr_t>(player) + kPlayerAddrOffset);
                        P2PReliable::PeerRttEntry& e = g_peerTable[count++];
                        e.addr0 = addr[0];
                        e.addr2 = addr[2];
                        e.addr3 = addr[3];
                        e.rttMs = rtt;
                        player = g_nextPlayer(player);
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    g_peerCount = 0;
                    g_maxRttMs = 0;
                    return false;
                }
                g_peerCount = count;
                g_maxRttMs = maxRtt;
                return true;
            }

            void RefreshPeerTable()
            {
                const ULONGLONG now = GetTickCount64();
                if (now < g_nextRttRefresh) return;
                if (!ReadPeerTable())
                {
                    g_nextRttRefresh = now + kRttFaultBackoffMs;
                    Log(L"[P2PSEND] adaptive retry: peer ping read faulted; configured waits kept for 10 s\n");
                    return;
                }
                g_nextRttRefresh = now + kRttRefreshMs;
            }

            bool ReadPeerKey(const void* peer, uint32_t (&key)[3])
            {
                if (!peer) return false;
                __try
                {
                    const uint32_t* addr = reinterpret_cast<const uint32_t*>(
                        reinterpret_cast<uintptr_t>(peer) + kPeerAddrOffset);
                    key[0] = addr[0];
                    key[1] = addr[2];
                    key[2] = addr[3];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return true;
            }

            // This peer's round trip, else the worst one; 0 when nothing is known.
            uint32_t PeerRttMs(const void* peer)
            {
                RefreshPeerTable();
                uint32_t key[3] = {};
                bool matched = false;
                uint32_t rtt = g_maxRttMs;
                if (ReadPeerKey(peer, key))
                    rtt = P2PReliable::PeerRttOrMax(g_peerTable, g_peerCount,
                                                    key[0], key[1], key[2], g_maxRttMs, &matched);
                if (g_maxRttMs != 0)
                {
                    if (matched) ++g_matchedCount;
                    else ++g_fallbackCount;
                }
                return rtt;
            }

            void MaybeLogAdaptive(uint32_t rttMs)
            {
                const ULONGLONG now = GetTickCount64();
                if (g_lastLogTick != 0 && now - g_lastLogTick < kLogMinGapMs) return;
                const uint32_t prev = g_loggedFirstMs;
                const uint32_t cur = g_lastFirstMs;
                // Log only a >= 25% change from the last logged value.
                if (prev != 0)
                {
                    const uint32_t delta = cur > prev ? cur - prev : prev - cur;
                    if (static_cast<uint64_t>(delta) * 4 < prev) return;
                }
                else if (rttMs == 0)
                {
                    return; // nothing adaptive to report yet
                }
                g_loggedFirstMs = cur;
                g_lastLogTick = now;
                Log(L"[P2PSEND] adaptive retry: peer rtt %u ms (max %u, matched %u, fallback %u) -> first retry %u ms, interval %u ms\n",
                    rttMs, g_maxRttMs, g_matchedCount, g_fallbackCount, cur, g_lastIntervalMs);
            }

            void* __fastcall FirstRetryDeadline(void* self, void* peer, uint32_t lo, uint32_t hi)
            {
                if (hi == 0)
                {
                    const uint32_t rtt = PeerRttMs(peer);
                    lo = P2PReliable::AdaptiveRetryMs(lo, rtt);
                    g_lastFirstMs = lo;
                    MaybeLogAdaptive(rtt);
                }
                return g_firstRetryOriginal(self, nullptr, lo, hi);
            }

            void* __fastcall IntervalDeadline(void* self, void* peer, uint32_t lo, uint32_t hi)
            {
                if (hi == 0)
                {
                    lo = P2PReliable::AdaptiveRetryMs(lo, PeerRttMs(peer));
                    g_lastIntervalMs = lo;
                }
                return g_intervalOriginal(self, nullptr, lo, hi);
            }

            // Call targets. ecx/stack are already the helper's arguments; only
            // edx (the peer) is added. Pump: eax holds the peer at the call.
            // Send: the peer is [ebp-0x78] in the send function's frame.
            __declspec(naked) void IntervalStub()
            {
                __asm
                {
                    mov edx, eax
                    jmp IntervalDeadline
                }
            }

            __declspec(naked) void FirstRetryStub()
            {
                __asm
                {
                    mov edx, dword ptr [ebp - 0x78]
                    jmp FirstRetryDeadline
                }
            }
        }

        void InitializeP2PAdaptiveRetry()
        {
            bool enabled = true;
            TryGetUserConfigBool("Network", "ReliableRetryAdaptToPing", enabled);
            if (!enabled)
            {
                Log(L"[P2PSEND] Adaptive retry disabled; configured retry waits kept\n");
                return;
            }
            const uint32_t nextPlayer = HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::NextPlayer");
            const uint32_t playerPing = HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::PlayerPing");
            if (nextPlayer == 0 || playerPing == 0)
            {
                Log(L"[SKIP] P2P adaptive retry: ping source unresolved (next 0x%08X ping 0x%08X)\n",
                    nextPlayer, playerPing);
                return;
            }
            g_nextPlayer = reinterpret_cast<NextPlayerFn>(nextPlayer);
            g_playerPing = reinterpret_cast<PlayerPingFn>(playerPing);

            struct Site
            {
                uint32_t call;
                uint32_t helper;
                const wchar_t* label;
                void (*wrapper)();
                DeadlineFn* original;
            };
            const Site sites[] = {
                { HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::FirstRetryCall"),
                  HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::FirstRetryHelper"),
                  L"first retry", &FirstRetryStub, &g_firstRetryOriginal },
                { HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::IntervalCall"),
                  HookEngine::ResolveNamedAddress("P2PAdaptiveRetry::IntervalHelper"),
                  L"retry interval", &IntervalStub, &g_intervalOriginal },
            };
            int installed = 0;
            for (const Site& site : sites)
            {
                const uint32_t call = site.call;
                const uint32_t helper = site.helper;
                if (call == 0 || helper == 0)
                {
                    Log(L"[SKIP] P2P adaptive %ls: call 0x%08X helper 0x%08X unresolved\n",
                        site.label, call, helper);
                    continue;
                }
                *site.original = reinterpret_cast<DeadlineFn>(helper);
                if (!RedirectCallTarget(call, helper, reinterpret_cast<uintptr_t>(site.wrapper)))
                {
                    *site.original = nullptr;
                    Log(L"[SKIP] P2P adaptive %ls: call at 0x%08X does not target 0x%08X\n",
                        site.label, call, helper);
                    continue;
                }
                ++installed;
            }
            Log(L"[P2PSEND] adaptive retry installed on %d of 2 deadline sites (wait = max(configured, 1.5 x this peer's rtt))\n",
                installed);
        }

        // -----------------------------------------------------------------
        // Sync Join default on
        // -----------------------------------------------------------------
        //
        // Sync Join locks a lobby once the game starts, so nobody joins
        // mid-game. A late joiner loads the mission's BZN and pushes its own
        // starting units to the host, which duplicates them and desyncs the
        // game. Stock reads the setting from multi.ini for every hosted lobby
        // (0x00742090, default "1"), but the in-lobby toggle saves its last
        // value there, so a host who turned it off once hosts every later game
        // unlocked. The patch writes 1 over the loader's "off" immediate
        // (0x0074216E): each new lobby starts with Sync Join on and the host
        // can still turn it off for that game.
        void ConfigureSyncJoinDefaultPatch(std::vector<HookEngine::PatchDef>& patches)
        {
            bool enabled = true;
            TryGetUserConfigBool("Fixes", "SyncJoinDefaultOn", enabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON"))
                enabled = false;
            for (auto& patch : patches)
            {
                if (patch.name != "Sync Join Default On") continue;
                if (!enabled)
                {
                    Log(L"[SYNCJOIN] Default-on disabled; lobbies keep the saved multi.ini value\n");
                    continue;
                }
                if (!patch.verified || !patch.address)
                {
                    Log(L"[SYNCJOIN] Lobby loader signature unavailable; saved multi.ini value kept\n");
                    continue;
                }
                patch.payload = { 0x01 };
            }
        }
    }
}
