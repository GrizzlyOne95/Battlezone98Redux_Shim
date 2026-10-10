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
    return failures ? 1 : 0;
}
