#include "p2p_early_unreliable_policy.h"
#include <cstdio>
#include <initializer_list>

int main() {
    using BZROpenShim::P2PEarlyUnreliable::Packet;
    using BZROpenShim::P2PEarlyUnreliable::ShouldDeliver;
    using BZROpenShim::P2PEarlyUnreliable::kMaxAhead;
    int failures = 0;
    const auto check = [&failures](bool ok, const char* text) {
        if (!ok) { std::fprintf(stderr, "FAIL: %s\n", text); ++failures; }
    };
    // Unreliable data, single fragment, stamped one past a missing reliable.
    const Packet base = {0, false, true, 101, 100, true};
    check(ShouldDeliver(base), "update stamped past one missing reliable is delivered");

    Packet p = base;
    p.stamp = 100;
    check(!ShouldDeliver(p), "in-order stamp is stock's accept path, never ours");
    p.stamp = 99;
    check(!ShouldDeliver(p), "stale update sent before a held reliable stays rejected");
    p.stamp = 100 + kMaxAhead;
    check(ShouldDeliver(p), "window upper bound is inclusive");
    p.stamp = 100 + kMaxAhead + 1;
    check(!ShouldDeliver(p), "implausibly far stamp stays rejected");

    p = base; p.reliable = true;
    check(!ShouldDeliver(p), "reliable data stays strictly ordered");
    p = base; p.finalFragment = false;
    check(!ShouldDeliver(p), "a fragment that would start reassembly is left to stock");
    p = base; p.reassemblyEmpty = false;
    check(!ShouldDeliver(p), "a partial reliable message blocks delivery as stock does");
    for (int kind : {3, 4, 5, 6, 7}) {
        p = base; p.kind = static_cast<uint8_t>(kind);
        check(!ShouldDeliver(p), "only kind 0 data is considered");
    }

    p = base; p.expected = 0xFFFFFFFFu; p.stamp = 2;
    check(ShouldDeliver(p), "stamp ahead across u32 wrap is delivered");
    p = base; p.expected = 2; p.stamp = 0xFFFFFFFFu;
    check(!ShouldDeliver(p), "stamp behind across u32 wrap stays rejected");

    using BZROpenShim::P2PEarlyUnreliable::ShouldAcceptNak;
    check(ShouldAcceptNak(6, 101, 100), "NAK stamped past an unreceived reliable is accepted");
    check(ShouldAcceptNak(6, 100 + kMaxAhead, 100), "NAK window upper bound is inclusive");
    check(!ShouldAcceptNak(6, 100 + kMaxAhead + 1, 100), "implausibly far NAK stays dropped");
    check(!ShouldAcceptNak(6, 100, 100), "in-order NAK is stock's accept path");
    check(!ShouldAcceptNak(6, 99, 100), "stale NAK stays dropped");
    check(!ShouldAcceptNak(7, 101, 100), "keepalive is not a NAK");
    check(!ShouldAcceptNak(0, 101, 100), "data is not a NAK");
    check(ShouldAcceptNak(6, 1, 0xFFFFFFFFu), "NAK ahead across u32 wrap is accepted");

    using BZROpenShim::P2PEarlyUnreliable::NakGate;
    NakGate gate;
    check(gate.Admit(0x1000, 50, 1000, 300), "first NAK for a missing stamp is admitted");
    check(!gate.Admit(0x1000, 50, 1100, 300), "repeat NAK for the same stamp is held");
    check(!gate.Admit(0x1000, 50, 1299, 300), "holdoff is exclusive of its end");
    check(gate.Admit(0x1000, 50, 1300, 300), "same stamp is re-admitted after the holdoff");
    check(gate.Admit(0x1000, 51, 1310, 300), "NAK for a new missing stamp is admitted at once");
    check(gate.Admit(0x2000, 51, 1320, 300), "peers are gated independently");
    check(!gate.Admit(0x2000, 51, 1400, 300), "second peer holds its own repeat");
    NakGate wrap;
    check(wrap.Admit(0x1000, 7, 0xFFFFFF00u, 300), "first NAK before tick wrap");
    check(!wrap.Admit(0x1000, 7, 0x10u, 300), "holdoff spans GetTickCount wrap");
    NakGate full;
    for (uintptr_t peer = 1; peer <= NakGate::kSlots; ++peer)
        full.Admit(peer, 9, static_cast<uint32_t>(peer), 300);
    check(full.Admit(NakGate::kSlots + 1, 9, 100, 300), "a new peer evicts the oldest slot");
    check(full.Admit(1, 9, 101, 300), "the evicted peer is treated as new");
    check(!full.Admit(NakGate::kSlots, 9, 102, 300), "a recent peer keeps its slot");
    return failures ? 1 : 0;
}
