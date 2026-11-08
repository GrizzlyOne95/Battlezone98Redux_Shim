#pragma once
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
} // namespace P2PReliable
} // namespace BZROpenShim
