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
} // namespace P2PEarlyUnreliable
} // namespace BZROpenShim
