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
    check(gate.Admit(0x1000, 50, 1000, 0, 300), "first NAK for a missing stamp is admitted");
    check(!gate.Admit(0x1000, 50, 1100, 0, 300), "repeat NAK for the same stamp is held");
    check(!gate.Admit(0x1000, 50, 1299, 0, 300), "holdoff is exclusive of its end");
    check(gate.Admit(0x1000, 50, 1300, 0, 300), "same stamp is re-admitted after the holdoff");
    check(gate.Admit(0x1000, 51, 1310, 0, 300), "NAK for a new missing stamp is admitted at once");
    check(gate.Admit(0x2000, 51, 1320, 0, 300), "peers are gated independently");
    check(!gate.Admit(0x2000, 51, 1400, 0, 300), "second peer holds its own repeat");
    NakGate wrap;
    check(wrap.Admit(0x1000, 7, 0xFFFFFF00u, 0, 300), "first NAK before tick wrap");
    check(!wrap.Admit(0x1000, 7, 0x10u, 0, 300), "holdoff spans GetTickCount wrap");
    NakGate full;
    for (uintptr_t peer = 1; peer <= NakGate::kSlots; ++peer)
        full.Admit(peer, 9, static_cast<uint32_t>(peer), 0, 300);
    check(full.Admit(NakGate::kSlots + 1, 9, 100, 0, 300), "a new peer evicts the oldest slot");
    check(full.Admit(1, 9, 101, 0, 300), "the evicted peer is treated as new");
    check(!full.Admit(NakGate::kSlots, 9, 102, 0, 300), "a recent peer keeps its slot");

    // Reorder hold: a stamp must still be named reorderMs after its first NAK.
    NakGate hold;
    check(!hold.Admit(0x1000, 50, 1000, 40, 300), "first NAK for a stamp waits out the reorder window");
    check(!hold.Admit(0x1000, 50, 1039, 40, 300), "reorder window is exclusive of its end");
    check(hold.Admit(0x1000, 50, 1040, 40, 300), "stamp still missing after the window is admitted");
    check(!hold.Admit(0x1000, 50, 1100, 40, 300), "admitted stamp then holds for the holdoff");
    check(hold.Admit(0x1000, 50, 1340, 40, 300), "admitted stamp is re-admitted after the holdoff");
    check(!hold.Admit(0x1000, 52, 1350, 40, 300), "a new stamp restarts the reorder window");
    check(!hold.Admit(0x1000, 51, 1400, 40, 300), "a stamp behind the current one is held");
    check(hold.Admit(0x1000, 52, 1400, 40, 300), "an older NAK does not reset the window");
    NakGate late;
    check(!late.Admit(0x1000, 60, 1000, 40, 300), "reordered datagram: first NAK held");
    check(!late.Admit(0x1000, 61, 1020, 40, 300), "it arrived and NAKs moved on: no pass for 60");
    check(!late.Admit(0x1000, 61, 1050, 40, 300), "61 itself still inside its own window");
    check(late.Admit(0x1000, 61, 1060, 40, 300), "61 still missing after its window is admitted");
    NakGate reset;
    check(reset.Admit(0x1000, 0x80000000u, 1000, 0, 300), "stamp far ahead admitted");
    check(reset.Admit(0x1000, 5, 1010, 0, 300), "a stamp far behind (reconnect) is treated as new");
    NakGate wrapHold;
    check(!wrapHold.Admit(0x1000, 0xFFFFFFFFu, 1000, 40, 300), "window before stamp wrap");
    check(!wrapHold.Admit(0x1000, 0xFFFFFFFEu, 1050, 40, 300), "behind across stamp wrap is held");
    check(!wrapHold.Admit(0x1000, 1, 1060, 40, 300), "ahead across stamp wrap restarts the window");

    using BZROpenShim::P2PEarlyUnreliable::ParseNakReorderMs;
    uint32_t ms = 7;
    check(ParseNakReorderMs(" 0 ", ms) && ms == 0, "zero disables the reorder hold");
    check(ParseNakReorderMs("1000", ms) && ms == 1000, "upper bound is accepted");
    ms = 7;
    check(!ParseNakReorderMs("1001", ms) && ms == 7, "above the bound is rejected unchanged");
    check(!ParseNakReorderMs("", ms) && !ParseNakReorderMs("-1", ms) && !ParseNakReorderMs("40ms", ms),
        "empty, signed and suffixed values are rejected");
    check(!ParseNakReorderMs("99999999999", ms), "overflow is rejected");
    return failures ? 1 : 0;
}
