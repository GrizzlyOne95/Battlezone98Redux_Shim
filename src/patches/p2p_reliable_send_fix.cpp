// p2p_reliable_send_fix.cpp
// BZR Open Shim - lets a BZRNet P2P peer that is retransmitting still send
// new reliable messages immediately, so a reliable backlog drains instead of
// starving the link of every unreliable update.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"
#include <Windows.h>
#include <cstdint>

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

        constexpr uintptr_t kP2PReliableSendSiteAddr = 0x0075C71B;
        constexpr uintptr_t kP2PReliableSendGateAddr = 0x0075C730;

        bool g_P2PReliableSendFixEnabled = true;

        void InstallP2PReliableSendFixIfEnabled()
        {
            bool configured = true;
            if (TryGetUserConfigBool("Network", "ReliableSendBacklogFix", configured))
                g_P2PReliableSendFixEnabled = configured;
            if (EnvFlagEnabled("OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX") ||
                EnvFlagEnabled("BZR_DISABLE_RELIABLE_SEND_BACKLOG_FIX"))
            {
                g_P2PReliableSendFixEnabled = false;
            }
            if (!g_P2PReliableSendFixEnabled)
            {
                Log(L"[P2PSEND] Reliable send backlog fix disabled; stock retry gating kept\n");
                return;
            }

            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
            {
                Log(L"[P2PSEND] Executable relocated; reliable send backlog fix not applied\n");
                return;
            }

            // mov eax,[ebp-78h] / cmp dword [eax],8 / jne +24Bh /
            // mov ecx,[ebp-78h] / movzx edx,byte [ecx+1Ah] / test edx,edx /
            // jne +23Ch. The state test is kept; only the last jne goes.
            static const uint8_t kExpected[] =
            {
                0x8B, 0x45, 0x88, 0x83, 0x38, 0x08, 0x0F, 0x85, 0x4B, 0x02, 0x00, 0x00,
                0x8B, 0x4D, 0x88, 0x0F, 0xB6, 0x51, 0x1A, 0x85, 0xD2,
                0x0F, 0x85, 0x3C, 0x02, 0x00, 0x00,
            };
            static const uint8_t kPatched[] =
            {
                0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00,
            };
            static_assert(sizeof(kExpected) ==
                          kP2PReliableSendGateAddr - kP2PReliableSendSiteAddr + sizeof(kPatched),
                          "gate must be the last instruction of the signature");

            if (ExpectedBytesMatchAt(kP2PReliableSendGateAddr, kPatched, sizeof(kPatched)))
            {
                Log(L"[P2PSEND] Reliable send backlog fix already applied\n");
                return;
            }
            if (!ExpectedBytesMatchAt(kP2PReliableSendSiteAddr, kExpected, sizeof(kExpected)))
            {
                Log(L"[P2PSEND] Signature mismatch at 0x%08X; stock retry gating kept\n",
                    static_cast<uint32_t>(kP2PReliableSendSiteAddr));
                return;
            }
            if (!HookEngine::WriteMemory(static_cast<uint32_t>(kP2PReliableSendGateAddr),
                                         kPatched, sizeof(kPatched)))
            {
                Log(L"[P2PSEND] Could not write 0x%08X; stock retry gating kept\n",
                    static_cast<uint32_t>(kP2PReliableSendGateAddr));
                return;
            }
            Log(L"[P2PSEND] Reliable send backlog fix applied at 0x%08X\n",
                static_cast<uint32_t>(kP2PReliableSendGateAddr));
        }
    }
}
