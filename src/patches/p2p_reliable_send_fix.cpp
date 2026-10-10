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
                if (patch.name == "P2P Reliable First Retry")
                {
                    key = "ReliableFirstRetryMs";
                    stockMs = P2PReliable::kFirstRetryStockMs;
                }
                else if (patch.name == "P2P Reliable Retry Interval")
                {
                    key = "ReliableRetryIntervalMs";
                    stockMs = P2PReliable::kRetryIntervalStockMs;
                }
                else continue;

                std::string text;
                if (!TryGetUserConfigString("Network", key, text)) continue;
                uint32_t ms = stockMs;
                if (!P2PReliable::ParseRetryMs(text, ms))
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
    }
}
