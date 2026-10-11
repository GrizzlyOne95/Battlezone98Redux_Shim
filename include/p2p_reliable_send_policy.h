#pragma once
#include <cstdint>
#include <string>

namespace BZROpenShim {
namespace P2PReliable {
constexpr uint32_t kFirstRetryStockMs = 1000;
constexpr uint32_t kRetryIntervalStockMs = 2500;
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
} // namespace P2PReliable
} // namespace BZROpenShim
