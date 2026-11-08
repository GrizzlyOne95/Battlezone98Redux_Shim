#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim {
namespace P2PReliable {
constexpr uint32_t kFirstRetryStockMs = 1000;
constexpr uint32_t kRetryIntervalStockMs = 2500;
// Shipped defaults, used when the INI key is absent.
constexpr uint32_t kFirstRetryDefaultMs = 300;
constexpr uint32_t kRetryIntervalDefaultMs = 800;
constexpr uint32_t kRetryMinMs = 50;
constexpr uint32_t kRetryMaxMs = 10000;

// Accept decimal milliseconds with surrounding INI whitespace only. Reject
// signs, suffixes and overflow rather than applying a partial conversion.
inline bool ParseRetryMs(const std::string& text, uint32_t& out) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return false;
    const auto last = text.find_last_not_of(" \t\r\n");
    uint32_t value = 0;
    for (size_t i = first; i <= last; ++i) {
        if (text[i] < '0' || text[i] > '9') return false;
        const uint32_t digit = static_cast<uint32_t>(text[i] - '0');
        if (value > (kRetryMaxMs - digit) / 10) return false;
        value = value * 10 + digit;
    }
    if (value < kRetryMinMs) return false;
    out = value;
    return true;
}

// Effective wait before a reliable resend: the configured value, raised to
// 1.5x the worst peer round trip so a slow link only resends real losses.
// rttMs == 0 means "no sample"; the configured value is kept. Capped at
// kRetryMaxMs, and the 1.5x term cannot overflow.
inline uint32_t AdaptiveRetryMs(uint32_t configuredMs, uint32_t rttMs) {
    if (rttMs == 0) return configuredMs;
    const uint64_t scaled = static_cast<uint64_t>(rttMs) + rttMs / 2;
    uint64_t ms = configuredMs > scaled ? configuredMs : scaled;
    if (ms > kRetryMaxMs) ms = kRetryMaxMs;
    return static_cast<uint32_t>(ms);
}
// Per-peer round trips. The engine's address comparator looks at dwords 0, 2
// and 3 of the 16-byte remote address only (dword 1 is skipped), so the key
// does the same.
struct PeerRttEntry {
    uint32_t addr0;
    uint32_t addr2;
    uint32_t addr3;
    uint32_t rttMs;
};

// Round trip for the peer with this key: the matching entry's rtt when it is
// non-zero, otherwise maxRttMs (unknown peer or no sample yet). An empty table
// with no max yields 0, i.e. "no sample".
inline uint32_t PeerRttOrMax(const PeerRttEntry* table, size_t count,
                             uint32_t addr0, uint32_t addr2, uint32_t addr3,
                             uint32_t maxRttMs, bool* matched = nullptr) {
    if (matched) *matched = false;
    for (size_t i = 0; i < count; ++i) {
        const PeerRttEntry& e = table[i];
        if (e.addr0 == addr0 && e.addr2 == addr2 && e.addr3 == addr3 && e.rttMs != 0) {
            if (matched) *matched = true;
            return e.rttMs;
        }
    }
    return maxRttMs;
}
// Same lookup from a full 16-byte address as four dwords (dword 1 ignored).
inline uint32_t PeerRttOrMax(const PeerRttEntry* table, size_t count,
                             const uint32_t (&addr)[4], uint32_t maxRttMs,
                             bool* matched = nullptr) {
    return PeerRttOrMax(table, count, addr[0], addr[2], addr[3], maxRttMs, matched);
}
} // namespace P2PReliable
} // namespace BZROpenShim
