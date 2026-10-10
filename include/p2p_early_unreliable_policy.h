#pragma once
#include <cstdint>

namespace BZROpenShim {
namespace P2PEarlyUnreliable {
// An unreliable update carries the sender's next reliable stamp, so it can be
// at most as far ahead of the receiver as the sender has reliable fragments in
// flight. Anything further is not a plausible update for this link.
constexpr uint32_t kMaxAhead = 4096;

// The frame values the native receive (GOG 0x0075D800) has already decoded
// when it decides to drop a packet from a connected peer.
struct Packet {
    uint8_t kind;          // header byte 1 low nibble; 0 = data
    bool reliable;         // header flag 0x80
    bool finalFragment;    // header flag 0x40
    uint32_t stamp;        // header +0x0A
    uint32_t expected;     // peer+0x84
    bool reassemblyEmpty;  // peer+0x98 vector begin == end
};

// True when stock would drop the packet only because it was stamped past a
// reliable fragment the receiver has not yet seen. Such an update was sent
// after every reliable message this receiver already holds, so delivering it
// can never apply older state over newer. Stale stamps (behind expected) stay
// rejected, reliable data stays strictly ordered, and a packet that would join
// or start a multi-fragment reassembly is left to stock.
inline bool ShouldDeliver(const Packet& p) {
    if (p.kind != 0 || p.reliable || !p.finalFragment || !p.reassemblyEmpty) return false;
    const uint32_t ahead = p.stamp - p.expected;  // modular: wraps like the native u32 stamp
    return ahead != 0 && ahead <= kMaxAhead;
}

// A kind-6 NAK carries the requester's next reliable stamp, so stock accepts it
// only when every reliable fragment the requester has sent us has arrived;
// with reliable traffic in flight in both directions that is rarely true, and
// the native receive drops kinds 6/7 silently. Accepting a NAK stamped ahead
// runs its only effect, case 6 setting peer+0x20 (retry deadline) to now.
inline bool ShouldAcceptNak(uint8_t kind, uint32_t stamp, uint32_t expected) {
    if (kind != 6) return false;
    const uint32_t ahead = stamp - expected;
    return ahead != 0 && ahead <= kMaxAhead;
}

// One lost reliable fragment makes the requester drop, and NAK, every later
// fragment until the retransmission lands; each of those NAKs names the same
// missing stamp (header ack, the requester's peer+0x84). Every accepted NAK
// runs a go-back-N resend pass, so admitting them all multiplies duplicates
// on exactly the links that are short of bandwidth. NakGate admits the first
// NAK for a missing stamp, then that stamp again only after holdoffMs (the
// retransmission itself was lost); a NAK naming a new stamp is always admitted.
constexpr uint32_t kDefaultNakHoldoffMs = 300;

class NakGate {
public:
    static constexpr int kSlots = 32;
    bool Admit(uintptr_t peer, uint32_t missing, uint32_t nowMs, uint32_t holdoffMs) {
        Slot* slot = nullptr;
        Slot* oldest = &slots_[0];
        for (Slot& s : slots_) {
            if (s.peer == peer) { slot = &s; break; }
            if (!s.peer || static_cast<int32_t>(s.lastMs - oldest->lastMs) < 0) oldest = &s;
            if (!s.peer) break;
        }
        if (!slot) {
            slot = oldest;
            *slot = Slot{ peer, missing, nowMs };
            return true;
        }
        if (slot->missing == missing && nowMs - slot->lastMs < holdoffMs) return false;
        slot->missing = missing;
        slot->lastMs = nowMs;
        return true;
    }
private:
    struct Slot { uintptr_t peer; uint32_t missing; uint32_t lastMs; };
    Slot slots_[kSlots] = {};
};
} // namespace P2PEarlyUnreliable
} // namespace BZROpenShim
