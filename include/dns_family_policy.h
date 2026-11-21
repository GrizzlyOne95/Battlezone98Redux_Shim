#pragma once

// IPv4-only matchmaking lookup: the pure decisions behind
// openshim.ini [Network] ForceIPv4Matchmaking. Header-only and free of
// Windows calls so the tests can include it.
//
// The game resolves its matchmaking host through asio (WS2_32!getaddrinfo,
// import 0x86A05C, call 0x006AFF25 on GOG 2.2.301) with AI_ADDRCONFIG,
// AF_UNSPEC and SOCK_STREAM, under a hard 5000 ms resolve timer (0x006D057F).
// With IPv6 enabled Windows also sends the AAAA query; when that stalls past
// 5 s every attempt fails and the MP tab stays "Not Ready". The host has only
// an A record, so asking for AF_INET loses nothing.

#include <cstdint>

namespace BZROpenShim
{
namespace DnsFamilyPolicy
{
    // Winsock values, mirrored so the header needs no Windows includes; the
    // hook static_asserts that they match.
    inline constexpr int kAfUnspec = 0;
    inline constexpr int kAfInet = 2;
    inline constexpr int kEaiNoName = 11001;  // EAI_NONAME == WSAHOST_NOT_FOUND
    inline constexpr int kEaiNoData = 11004;  // EAI_NODATA == WSANO_DATA (e.g. AAAA-only host)
    inline constexpr uint32_t kMaxTestStallMs = 15000;

    // An IPv6 literal (e.g. a redirect to "::1") must keep AF_UNSPEC.
    inline bool IsIPv6Literal(const char* node)
    {
        if (!node)
            return false;
        for (; *node; ++node)
        {
            if (*node == ':')
                return true;
        }
        return false;
    }

    // hintsUnspec: hints are null or ask for AF_UNSPEC.
    inline bool ShouldForceIPv4(bool enabled, bool isBzrNet, bool hintsUnspec, bool nodeIsIPv6Literal)
    {
        return enabled && isBzrNet && hintsUnspec && !nodeIsIPv6Literal;
    }

    // The forced lookup found nothing: try once more with the caller's hints.
    inline bool ShouldRetryWithOriginal(int rc, unsigned resultCount)
    {
        return rc == kEaiNoName || rc == kEaiNoData || (rc == 0 && resultCount == 0);
    }

    // OPENSHIM_TEST_DNS_STALL_MS imitates the AAAA stall: it only delays a
    // BZRNet lookup whose effective hints still ask for AF_UNSPEC.
    inline bool TestStallApplies(uint32_t stallMs, bool isBzrNet, int effectiveFamily)
    {
        return stallMs > 0 && isBzrNet && effectiveFamily == kAfUnspec;
    }

    inline uint32_t ClampTestStallMs(uint32_t ms)
    {
        return ms > kMaxTestStallMs ? kMaxTestStallMs : ms;
    }

    // Log the first few lookups, then only when the outcome changes, so the
    // game's unlimited retries do not spam the log.
    struct LookupLogBudget
    {
        static constexpr unsigned kFirst = 4;
        unsigned logged = 0;
        int lastRc = 0;
        unsigned lastV4 = 0;
        unsigned lastV6 = 0;

        bool ShouldLog(int rc, unsigned v4, unsigned v6)
        {
            const bool changed = logged == 0 || rc != lastRc || v4 != lastV4 || v6 != lastV6;
            lastRc = rc;
            lastV4 = v4;
            lastV6 = v6;
            if (logged < kFirst || changed)
            {
                if (logged < kFirst)
                    ++logged;
                return true;
            }
            return false;
        }
    };
} // namespace DnsFamilyPolicy
} // namespace BZROpenShim
