#include "lua_send_length.h"

#include <cstdint>
#include <cstring>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::LuaSendLength;

    // GOG Redux 2.2.301 sites (scripts/patches.json fallbacks).
    constexpr uint32_t kStringSite = 0x00505944;
    constexpr uint32_t kTableSite = 0x00505A7A;
    constexpr uint32_t kStubBase = 0x10000000;

    uint32_t Rel32At(const std::vector<uint8_t>& code, size_t at)
    {
        return static_cast<uint32_t>(code[at]) | (static_cast<uint32_t>(code[at + 1]) << 8) |
               (static_cast<uint32_t>(code[at + 2]) << 16) | (static_cast<uint32_t>(code[at + 3]) << 24);
    }

    // Absolute target of a rel32 branch whose operand starts at `at`.
    uint32_t TargetAt(const std::vector<uint8_t>& code, uint32_t base, size_t at)
    {
        return base + static_cast<uint32_t>(at) + 4 + Rel32At(code, at);
    }

    void TestDecoderSiteClassification()
    {
        const uint8_t stock[3] = { 0x0F, 0xBE, 0x11 };
        const uint8_t patched[3] = { 0x0F, 0xB6, 0x11 };
        const uint8_t other[3] = { 0x0F, 0xBE, 0x10 }; // movsx edx,[eax]: not our load
        CHECK(DecoderSiteIsStock(stock));
        CHECK(!DecoderSiteIsPatched(stock));
        CHECK(DecoderSiteIsPatched(patched));
        CHECK(!DecoderSiteIsStock(patched));
        CHECK(!DecoderSiteIsStock(other));
        CHECK(!DecoderSiteIsPatched(other));

        // The single-byte write turns the stock load into the patched one.
        uint8_t bytes[3] = { 0x0F, 0xBE, 0x11 };
        CHECK(bytes[kDecoderFlipOffset] == kDecoderOriginal[kDecoderFlipOffset]);
        bytes[kDecoderFlipOffset] = kDecoderMovzxOpcode;
        CHECK(DecoderSiteIsPatched(bytes));
    }

    void TestSiteDescriptions()
    {
        // The fail exit must land on the stock `xor al,al`.
        CHECK(kStringEncoder.failOffset + 1 < kStringEncoder.expectedLen);
        CHECK(kStringEncoderExpected[kStringEncoder.failOffset] == 0x32 &&
              kStringEncoderExpected[kStringEncoder.failOffset + 1] == 0xC0);
        CHECK(kTableEncoder.failOffset + 1 < kTableEncoder.expectedLen);
        CHECK(kTableEncoderExpected[kTableEncoder.failOffset] == 0x32 &&
              kTableEncoderExpected[kTableEncoder.failOffset + 1] == 0xC0);

        // The replayed range is whole instructions with no relative operand and
        // stops before the fail exit, and is long enough for a 5-byte JMP.
        // String: 8B 55 08 | 8B 02 | 8B 4D FC | 8D 54 08 01  (3+2+3+4)
        CHECK(kStringEncoder.replayLen == 12);
        CHECK(kStringEncoderExpected[5] == 0x8B && kStringEncoderExpected[6] == 0x4D &&
              static_cast<int8_t>(kStringEncoderExpected[7]) == kStringEncoder.countFrameOffset);
        // Table: 8B 45 08 | 8B 08 | 83 C1 01  (3+2+3)
        CHECK(kTableEncoder.replayLen == 8);
        CHECK(kStringEncoder.replayLen >= 5 && kStringEncoder.replayLen < kStringEncoder.failOffset);
        CHECK(kTableEncoder.replayLen >= 5 && kTableEncoder.replayLen < kTableEncoder.failOffset);
        CHECK(kStringEncoder.countFrameOffset == -4 && kTableEncoder.countFrameOffset == -4);
        CHECK(kMaxWireLength == 255);
    }

    void CheckStub(const EncoderSite& site, uint32_t siteAddr, uint32_t stubAddr,
                   uint32_t expectFail, uint32_t expectResume)
    {
        const std::vector<uint8_t> stub = BuildGuardStub(site, siteAddr, stubAddr);
        CHECK(stub.size() == 18 + site.replayLen);
        if (stub.size() != 18 + site.replayLen)
            return;

        // cmp dword [ebp-4], 0x000000FF
        const uint8_t cmp[] = { 0x81, 0x7D, 0xFC, 0xFF, 0x00, 0x00, 0x00 };
        CHECK(std::memcmp(stub.data(), cmp, sizeof(cmp)) == 0);
        // ja (unsigned): 255 passes, 256 and up -- and any negative -- fail.
        CHECK(stub[7] == 0x0F && stub[8] == 0x87);
        CHECK(TargetAt(stub, stubAddr, 9) == expectFail);
        CHECK(expectFail == siteAddr + site.failOffset);
        // Replay is a byte-exact copy of the overwritten prefix.
        CHECK(std::memcmp(stub.data() + 13, site.expected, site.replayLen) == 0);
        const size_t jmp = 13 + site.replayLen;
        CHECK(stub[jmp] == 0xE9);
        CHECK(TargetAt(stub, stubAddr, jmp + 1) == expectResume);
        CHECK(expectResume == siteAddr + site.replayLen);
    }

    void TestStringStub()
    {
        CheckStub(kStringEncoder, kStringSite, kStubBase, 0x00505955, 0x00505950);
        const std::vector<uint8_t> stub = BuildGuardStub(kStringEncoder, kStringSite, kStubBase);
        // Hand-computed rel32s, so the helper cannot agree with itself by accident.
        CHECK(Rel32At(stub, 9) == 0xF0505948u);
        CHECK(Rel32At(stub, 26) == 0xF0505932u);
    }

    void TestTableStub()
    {
        CheckStub(kTableEncoder, kTableSite, kStubBase + 0x40, 0x00505A87, 0x00505A82);
        const std::vector<uint8_t> stub = BuildGuardStub(kTableEncoder, kTableSite, kStubBase + 0x40);
        CHECK(Rel32At(stub, 9) == 0xF0505A3Au);
        CHECK(Rel32At(stub, 22) == 0xF0505A28u);
    }

    void CheckDetour(const EncoderSite& site, uint32_t siteAddr, uint32_t stubAddr, uint32_t expectRel)
    {
        const std::vector<uint8_t> detour = BuildDetour(site, siteAddr, stubAddr);
        CHECK(detour.size() == site.replayLen);
        if (detour.size() != site.replayLen)
            return;
        CHECK(detour[0] == 0xE9);
        CHECK(Rel32At(detour, 1) == expectRel);
        CHECK(TargetAt(detour, siteAddr, 1) == stubAddr);
        for (size_t i = 5; i < detour.size(); ++i)
            CHECK(detour[i] == 0x90);
    }

    void TestDetours()
    {
        CheckDetour(kStringEncoder, kStringSite, kStubBase, 0x0FAFA6B7u);
        CheckDetour(kTableEncoder, kTableSite, kStubBase + 0x40, 0x0FAFA5C1u);
        // A stub below the site (negative displacement) still round-trips.
        CheckDetour(kStringEncoder, kStringSite, 0x00400000, 0x00400000u - (kStringSite + 5));
    }

    void TestStubFitsSlot()
    {
        // lua_send_length.cpp places each stub in a 64-byte slot.
        CHECK(BuildGuardStub(kStringEncoder, kStringSite, kStubBase).size() <= 64);
        CHECK(BuildGuardStub(kTableEncoder, kTableSite, kStubBase).size() <= 64);
    }
}

int main()
{
    TestDecoderSiteClassification();
    TestSiteDescriptions();
    TestStringStub();
    TestTableStub();
    TestDetours();
    TestStubFitsSlot();
    return OpenShimTest::ExitCode();
}
