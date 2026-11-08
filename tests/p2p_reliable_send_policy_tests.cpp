#include "p2p_reliable_send_policy.h"
#include <cstdio>

int main() {
    int failures = 0;
    const auto check = [&failures](bool ok, const char* text) {
        if (!ok) { std::fprintf(stderr, "FAIL: %s\n", text); ++failures; }
    };
    const struct { const char* text; uint32_t expected; } valid[] = {
        {"50", 50}, {"1000", 1000}, {"2500", 2500}, {"10000", 10000},
        {" \t250\r\n", 250}, {"00050", 50}
    };
    for (const auto& input : valid) {
        uint32_t ms = 0;
        check(BZROpenShim::P2PReliable::ParseRetryMs(input.text, ms), input.text);
        check(ms == input.expected, "accepted retry has the requested value");
    }
    for (const auto& text : {"", " \t", "0", "49", "10001", "250ms", "250junk",
                            "250 500", "-250", "+250", "0x100", "4294967546",
                            "999999999999999999999999999"}) {
        uint32_t ms = 1234;
        check(!BZROpenShim::P2PReliable::ParseRetryMs(text, ms), text);
        check(ms == 1234, "invalid input preserves stock value");
    }
    using BZROpenShim::P2PReliable::AdaptiveRetryMs;
    check(AdaptiveRetryMs(300, 0) == 300, "no ping sample keeps the configured wait");
    check(AdaptiveRetryMs(300, 40) == 300, "low ping keeps the configured wait");
    check(AdaptiveRetryMs(300, 200) == 300, "rtt*1.5 equal to the base keeps it");
    check(AdaptiveRetryMs(300, 350) == 525, "350 ms rtt waits 525 ms");
    check(AdaptiveRetryMs(800, 350) == 800, "interval base above 1.5x rtt wins");
    check(AdaptiveRetryMs(800, 1000) == 1500, "high rtt raises the interval");
    check(AdaptiveRetryMs(300, 100000) == 10000, "huge rtt is capped");
    check(AdaptiveRetryMs(300, 0xFFFFFFFFu) == 10000, "rtt near UINT32_MAX does not overflow");
    check(AdaptiveRetryMs(300, 0xFFFFFFFEu) == 10000, "rtt UINT32_MAX-1 does not overflow");
    return failures ? 1 : 0;
}
