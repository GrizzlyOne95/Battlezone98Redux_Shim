// p2p_early_unreliable_receive.cpp
// BZR Open Shim - lets a BZRNet P2P receiver use an unreliable update that
// arrives while an earlier reliable fragment is still being retransmitted,
// instead of discarding every update on the link until the retransmit lands.
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "p2p_early_unreliable_policy.h"
#include "p2p_reliable_send_fix.h"
#include "p2p_reliable_send_policy.h"
#include "patcher.h"
#include <Windows.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        // -----------------------------------------------------------------
        // P2P early unreliable receive
        // -----------------------------------------------------------------
        //
        // Recovered from the GOG 2.2.301 image; see
        // reverse_engineering/p2p_early_unreliable_receive_20261010.md.
        //
        // The receive routine 0x0075D800 accepts a data packet only when its
        // stamp equals peer+0x84, the next reliable stamp it expects. Senders
        // stamp unreliable updates with their next reliable stamp, so after a
        // single lost reliable fragment every following update is dropped until
        // the retransmit arrives: at least a round trip after the receiver's
        // NAK, up to the 1000/2500 ms retry timers when that NAK is lost too.
        // The reliable-send backlog fix removed the sender-side cause of
        // permanent stalls; this is the receiver half of the same symptom and
        // the remaining source of rejected updates under real packet loss.
        //
        // The drop path for a connected peer, entered with EBP on the host
        // frame (stamp [ebp-0x15C], peer [ebp-0x134], reliable flag
        // [ebp-0x13A], kind [ebp-0x139], final-fragment flag [ebp-0x151]):
        //
        //   0x0075DA1A  pop acknowledged fragments (cumulative ack, always)
        //   0x0075DA70  kinds 6/7 return silently
        //   0x0075DA8D  cmp [log level], 0 / je 0x0075DB32   <- site A
        //   0x0075DA9A  "Dropping Packet Type ..." log
        //   0x0075DB32  send kind 6 (expected stamp) back: the NAK that makes
        //               the sender retransmit at once
        //   0x0075DB96  jmp 0x0075EE69 (return)                <- site B
        //
        // Site A skips only the drop log for a packet this patch will deliver.
        // Site B, after the NAK has been sent exactly as stock sends it, jumps
        // to the accepted-packet tail 0x0075DEEF (the same cumulative-ack loop,
        // then the kind switch) instead of returning. Case 0 there delivers an
        // unreliable packet only while the reassembly vector is empty, the
        // same guard stock applies to in-order updates. peer+0x84 is never
        // written for unreliable packets, so reliable ordering, ACKs, NAKs and
        // retransmission are untouched and the wire format is unchanged.

        namespace
        {
            constexpr long kStampFrame = -0x15C;
            constexpr long kAckFrame = -0x174;  // header +0x0E; a NAK carries the missing stamp
            constexpr long kPeerFrame = -0x134;
            constexpr long kReliableFrame = -0x13A;
            constexpr long kKindFrame = -0x139;
            constexpr long kFinalFrame = -0x151;
            constexpr size_t kPeerExpected = 0x84;
            constexpr size_t kPeerReassembly = 0x98;
            constexpr size_t kSiteALen = 13;
            constexpr size_t kSiteBLen = 5;
            constexpr size_t kSiteBAcceptJmp = 0x39;
            constexpr size_t kSiteBMarkReceived = 0x2F;  // 0x0075DBC5: peer+0x19 = 1, jmp 0x0075DEEF
            constexpr size_t kSiteCLen = 5;
            constexpr DWORD kLogIntervalMs = 5000;

            bool g_Enabled = false;
            bool g_NakEnabled = false;
            uint32_t g_SiteCReturn = 0;
            uint32_t g_SiteCAccept = 0;
            uint32_t g_LogLevelAddr = 0;
            uint32_t g_SiteALogResume = 0;
            uint32_t g_SiteASkipLog = 0;
            uint32_t g_SiteBReturn = 0;
            uint32_t g_SiteBDeliver = 0;
            struct Counter
            {
                const wchar_t* what;
                volatile LONG total;
                volatile LONG logged;
                volatile LONG lastTick;
            };
            Counter g_Delivered = { L"Delivered early unreliable updates", 0, 0, 0 };
            Counter g_NaksAccepted = { L"Accepted early NAKs", 0, 0, 0 };
            Counter g_NaksHeld = { L"Held NAKs (reorder window or repeat)", 0, 0, 0 };
            uint32_t g_NakHoldoffMs = P2PEarlyUnreliable::kDefaultNakHoldoffMs;
            uint32_t g_NakReorderMs = P2PEarlyUnreliable::kDefaultNakReorderMs;
            P2PEarlyUnreliable::NakGate g_NakGate;
            SRWLOCK g_NakGateLock = SRWLOCK_INIT;

            uint32_t Rel32Target(uint32_t instr, size_t relOffset, size_t len)
            {
                const int32_t rel = *reinterpret_cast<const int32_t*>(instr + relOffset);
                return instr + static_cast<uint32_t>(len) + static_cast<uint32_t>(rel);
            }

            void Note(Counter& c)
            {
                const LONG total = InterlockedIncrement(&c.total);
                const LONG now = static_cast<LONG>(GetTickCount());
                const LONG last = c.lastTick;
                if (total != 1 && static_cast<DWORD>(now - last) < kLogIntervalMs) return;
                if (InterlockedCompareExchange(&c.lastTick, now, last) != last) return;
                const LONG previous = InterlockedExchange(&c.logged, total);
                Log(L"[P2PRECV] %s: total=%ld (+%ld)\n", c.what, total, total - previous);
            }
        }

        // Called from both thunks with the host frame. Reads only values the
        // native routine has already decoded and validated (peer is non-null
        // on this path), so no guard beyond the policy is needed.
        extern "C" int __stdcall P2PEarlyUnreliableDecide(const uint8_t* frame, int count)
        {
            if (!g_Enabled) return 0;
            const uint8_t* peer = *reinterpret_cast<uint8_t* const*>(frame + kPeerFrame);
            if (!peer) return 0;
            const uintptr_t* reassembly = reinterpret_cast<const uintptr_t*>(peer + kPeerReassembly);

            P2PEarlyUnreliable::Packet packet = {};
            packet.kind = frame[kKindFrame];
            packet.reliable = frame[kReliableFrame] != 0;
            packet.finalFragment = frame[kFinalFrame] != 0;
            packet.stamp = *reinterpret_cast<const uint32_t*>(frame + kStampFrame);
            packet.expected = *reinterpret_cast<const uint32_t*>(peer + kPeerExpected);
            packet.reassemblyEmpty = reassembly[0] == reassembly[1];
            if (!P2PEarlyUnreliable::ShouldDeliver(packet)) return 0;
            if (count) Note(g_Delivered);
            return 1;
        }

        // Site C: the silent kind 6/7 return. Same host frame as above.
        extern "C" int __stdcall P2PEarlyNakDecide(const uint8_t* frame)
        {
            if (!g_NakEnabled) return 0;
            const uint8_t* peer = *reinterpret_cast<uint8_t* const*>(frame + kPeerFrame);
            if (!peer) return 0;
            if (!P2PEarlyUnreliable::ShouldAcceptNak(frame[kKindFrame],
                    *reinterpret_cast<const uint32_t*>(frame + kStampFrame),
                    *reinterpret_cast<const uint32_t*>(peer + kPeerExpected)))
                return 0;
            AcquireSRWLockExclusive(&g_NakGateLock);
            const bool admit = g_NakGate.Admit(reinterpret_cast<uintptr_t>(peer),
                *reinterpret_cast<const uint32_t*>(frame + kAckFrame), GetTickCount(), g_NakReorderMs, g_NakHoldoffMs);
            ReleaseSRWLockExclusive(&g_NakGateLock);
            Note(admit ? g_NaksAccepted : g_NaksHeld);
            return admit ? 1 : 0;
        }

        // Both sites are entered by a JMP written over whole instructions, so
        // EBP is the host frame. POPAD leaves EFLAGS alone, carrying the
        // decision's TEST across it. The host's next instructions at every
        // resume target reload EAX/ECX/EDX before use and set their own flags;
        // the nearest earlier instruction that could leave XMM state is a CALL.
        static __declspec(naked) void P2PEarlyUnreliableSiteAThunk()
        {
            __asm
            {
                pushad
                push 0
                push ebp
                call P2PEarlyUnreliableDecide
                test eax, eax
                popad
                jnz  skip_log
                push eax
                mov  eax, dword ptr [g_LogLevelAddr]
                cmp  dword ptr [eax], 0
                pop  eax
                je   skip_log
                jmp  dword ptr [g_SiteALogResume]
            skip_log:
                jmp  dword ptr [g_SiteASkipLog]
            }
        }

        static __declspec(naked) void P2PEarlyUnreliableSiteBThunk()
        {
            __asm
            {
                pushad
                push 1
                push ebp
                call P2PEarlyUnreliableDecide
                test eax, eax
                popad
                jnz  deliver
                jmp  dword ptr [g_SiteBReturn]
            deliver:
                jmp  dword ptr [g_SiteBDeliver]
            }
        }

        // Accepting continues at 0x0075DBC5, the tail of the stock accept
        // path: peer+0x19 = 1 (the retry pump resends only for a peer heard
        // from since its last pass), then the cumulative-ack loop and case 6.
        static __declspec(naked) void P2PEarlyNakSiteCThunk()
        {
            __asm
            {
                pushad
                push ebp
                call P2PEarlyNakDecide
                test eax, eax
                popad
                jnz  accept
                jmp  dword ptr [g_SiteCReturn]
            accept:
                jmp  dword ptr [g_SiteCAccept]
            }
        }

        void ConfigureP2PEarlyUnreliablePatches(std::vector<HookEngine::PatchDef>& patches)
        {
            bool enabled = true;  // default on since the 2026-10-10 live matrices
            TryGetUserConfigBool("Network", "EarlyUnreliableAccept", enabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_EARLY_UNRELIABLE_ACCEPT") ||
                EnvFlagEnabled("BZR_DISABLE_EARLY_UNRELIABLE_ACCEPT"))
                enabled = false;
            bool nakEnabled = false;
            TryGetUserConfigBool("Network", "EarlyNakAccept", nakEnabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_EARLY_NAK_ACCEPT") ||
                EnvFlagEnabled("BZR_DISABLE_EARLY_NAK_ACCEPT"))
                nakEnabled = false;
            std::string holdoff;
            if (nakEnabled && TryGetUserConfigString("Network", "EarlyNakHoldoffMs", holdoff) &&
                !P2PReliable::ParseRetryMs(holdoff, g_NakHoldoffMs))
            {
                g_NakHoldoffMs = P2PEarlyUnreliable::kDefaultNakHoldoffMs;
                Log(L"[P2PRECV] Invalid EarlyNakHoldoffMs; decimal %u-%u ms required; %u ms kept\n",
                    P2PReliable::kRetryMinMs, P2PReliable::kRetryMaxMs, g_NakHoldoffMs);
            }
            std::string reorder;
            if (nakEnabled && TryGetUserConfigString("Network", "EarlyNakReorderMs", reorder) &&
                !P2PEarlyUnreliable::ParseNakReorderMs(reorder, g_NakReorderMs))
            {
                g_NakReorderMs = P2PEarlyUnreliable::kDefaultNakReorderMs;
                Log(L"[P2PRECV] Invalid EarlyNakReorderMs; decimal 0-%u ms required; %u ms kept\n",
                    P2PEarlyUnreliable::kNakReorderMaxMs, g_NakReorderMs);
            }
            if (!enabled && !nakEnabled) return;

            HookEngine::PatchDef* siteA = nullptr;
            HookEngine::PatchDef* siteB = nullptr;
            HookEngine::PatchDef* siteC = nullptr;
            for (auto& patch : patches)
            {
                if (patch.name == "P2P Early Unreliable Drop Log") siteA = &patch;
                else if (patch.name == "P2P Early Unreliable Deliver") siteB = &patch;
                else if (patch.name == "P2P Early NAK Accept") siteC = &patch;
            }
            // The NAK site resumes at an address inside site B's verified
            // pattern, so it needs site B's signature but not its JMP.
            if (nakEnabled)
            {
                if (!siteB || !siteC || !siteB->verified || !siteB->address ||
                    !siteC->verified || !siteC->address)
                {
                    Log(L"[P2PRECV] NAK signatures unavailable; stock NAK receive kept\n");
                }
                else
                {
                    g_SiteCReturn = Rel32Target(siteC->address, 1, kSiteCLen);
                    g_SiteCAccept = siteB->address + static_cast<uint32_t>(kSiteBMarkReceived);
                    g_NakEnabled = true;
                    siteC->payload = HookEngine::MakeJmp5Payload(siteC->address,
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&P2PEarlyNakSiteCThunk)), kSiteCLen);
                    Log(L"[P2PRECV] Early NAK receive armed: return=0x%08X accept=0x%08X window=%u reorder=%ums holdoff=%ums\n",
                        g_SiteCReturn, g_SiteCAccept, P2PEarlyUnreliable::kMaxAhead, g_NakReorderMs, g_NakHoldoffMs);
                }
            }
            if (!enabled) return;
            // Both sites or neither: site B alone would deliver while still
            // logging a drop, site A alone would hide drops it never delivers.
            if (!siteA || !siteB || !siteA->verified || !siteA->address ||
                !siteB->verified || !siteB->address)
            {
                Log(L"[P2PRECV] Receive signatures unavailable; stock strict receive kept\n");
                return;
            }

            const uint32_t a = siteA->address;
            const uint32_t b = siteB->address;
            g_LogLevelAddr = *reinterpret_cast<const uint32_t*>(a + 2);
            g_SiteALogResume = a + static_cast<uint32_t>(kSiteALen);
            g_SiteASkipLog = Rel32Target(a + 7, 2, 6);
            g_SiteBReturn = Rel32Target(b, 1, kSiteBLen);
            g_SiteBDeliver = Rel32Target(b + static_cast<uint32_t>(kSiteBAcceptJmp), 1, 5);
            g_Enabled = true;

            siteA->payload = HookEngine::MakeJmp5Payload(a,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&P2PEarlyUnreliableSiteAThunk)), kSiteALen);
            siteB->payload = HookEngine::MakeJmp5Payload(b,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&P2PEarlyUnreliableSiteBThunk)), kSiteBLen);
            Log(L"[P2PRECV] Early unreliable receive armed: log=0x%08X skip=0x%08X return=0x%08X deliver=0x%08X window=%u\n",
                g_LogLevelAddr, g_SiteASkipLog, g_SiteBReturn, g_SiteBDeliver, P2PEarlyUnreliable::kMaxAhead);
        }
    }
}
