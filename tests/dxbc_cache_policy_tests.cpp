// Unit tests for the DXBC cache key and entry header.
#include "dxbc_cache_policy.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace BZROpenShim::DxbcCachePolicy;

static int g_Failures = 0;

static void Check(bool condition, const char* what)
{
    if (!condition)
    {
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }
}

static uint64_t Key(const std::string& src, const char* entry, const char* target,
                    uint32_t f1, uint32_t f2)
{
    return ComputeKey(src.data(), src.size(), entry, target, f1, f2);
}

int main()
{
    const uint64_t base = Key("float4 main() { return 0; }", "main", "ps_3_0", 1, 2);
    Check(base == Key("float4 main() { return 0; }", "main", "ps_3_0", 1, 2), "same inputs same key");
    Check(base != Key("float4 main() { return 1; }", "main", "ps_3_0", 1, 2), "source differs");
    Check(base != Key("float4 main() { return 0; }", "main2", "ps_3_0", 1, 2), "entry differs");
    Check(base != Key("float4 main() { return 0; }", "main", "ps_4_0", 1, 2), "target differs");
    Check(base != Key("float4 main() { return 0; }", "main", "ps_3_0", 3, 2), "flags1 differs");
    Check(base != Key("float4 main() { return 0; }", "main", "ps_3_0", 1, 4), "flags2 differs");
    Check(Key("ab", "c", "d", 0, 0) != Key("a", "bc", "d", 0, 0), "field boundaries matter");
    Check(Key("x", nullptr, "t", 0, 0) != Key("x", "", "t", 0, 0), "null entry differs from empty");

    char hex[17];
    HexName(0x0123456789abcdefull, hex);
    Check(std::strcmp(hex, "0123456789abcdef") == 0, "hex name");

    std::string blob(64, 'x');
    std::memcpy(&blob[0], "DXBC", 4);
    const uint32_t total = static_cast<uint32_t>(blob.size());
    std::memcpy(&blob[24], &total, sizeof(total));
    const size_t pre = 27;
    std::vector<unsigned char> file(sizeof(EntryHeader) + blob.size());
    const EntryHeader h = MakeHeader(base, pre, blob.data(), blob.size());
    std::memcpy(file.data(), &h, sizeof(h));
    std::memcpy(file.data() + sizeof(h), blob.data(), blob.size());

    size_t off = 0, size = 0;
    Check(ValidateEntry(file.data(), file.size(), base, pre, &off, &size), "round trip valid");
    Check(off == sizeof(EntryHeader) && size == blob.size(), "round trip offsets");
    Check(!ValidateEntry(file.data(), file.size(), base + 1, pre, &off, &size), "wrong key rejected");
    Check(!ValidateEntry(file.data(), file.size(), base, pre + 1, &off, &size), "wrong preprocessed length rejected");
    Check(!ValidateEntry(file.data(), file.size() - 1, base, pre, &off, &size), "truncated blob rejected");
    Check(!ValidateEntry(file.data(), sizeof(EntryHeader) - 1, base, pre, &off, &size), "truncated header rejected");
    Check(!ValidateEntry(file.data(), 0, base, pre, &off, &size), "empty rejected");
    Check(!ValidateEntry(nullptr, 100, base, pre, &off, &size), "null rejected");

    auto corrupt = file;
    corrupt[0] ^= 0xFF;
    Check(!ValidateEntry(corrupt.data(), corrupt.size(), base, pre, &off, &size), "bad magic rejected");
    corrupt = file;
    corrupt[4] ^= 0xFF;
    Check(!ValidateEntry(corrupt.data(), corrupt.size(), base, pre, &off, &size), "bad version rejected");
    auto grown = file;
    grown.push_back(0);
    Check(!ValidateEntry(grown.data(), grown.size(), base, pre, &off, &size), "trailing bytes rejected");

    corrupt = file;
    corrupt[sizeof(EntryHeader) + 40] ^= 0x01;
    Check(!ValidateEntry(corrupt.data(), corrupt.size(), base, pre, &off, &size), "corrupt payload rejected");

    // Bad fourcc / bad size field, each with a hash that matches the payload.
    for (int variant = 0; variant < 2; ++variant)
    {
        std::string bad = blob;
        if (variant == 0)
            bad[0] = 'X';
        else
            bad[24] ^= 0x01;
        std::vector<unsigned char> f(sizeof(EntryHeader) + bad.size());
        const EntryHeader bh = MakeHeader(base, pre, bad.data(), bad.size());
        std::memcpy(f.data(), &bh, sizeof(bh));
        std::memcpy(f.data() + sizeof(bh), bad.data(), bad.size());
        Check(!ValidateEntry(f.data(), f.size(), base, pre, &off, &size),
              variant == 0 ? "bad fourcc rejected" : "bad dxbc size field rejected");
    }

    if (g_Failures == 0)
        std::puts("dxbc_cache_policy_tests: all passed");
    return g_Failures ? 1 : 0;
}
