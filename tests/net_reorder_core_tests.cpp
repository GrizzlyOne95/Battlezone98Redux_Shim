// net_reorder_core_tests.cpp
// Host tests for the experimental UDP reorder path's pure core
// (include/net_reorder_core.h). Pins audit P2-10: a datagram larger than a
// reorder slot is never cut down, and a datagram larger than the caller's
// buffers is reported as truncated (WSAEMSGSIZE) instead of as a success.

#include "net_reorder_core.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace
{
int g_failures = 0;

void Check(bool cond, const char* what, int line)
{
    if (!cond)
    {
        ++g_failures;
        std::printf("FAIL %d: %s\n", line, what);
    }
}
#define CHECK(c) Check((c), #c, __LINE__)

using namespace BZROpenShim::NetReorder;

// Same member names and types as WSABUF (ULONG len; CHAR* buf).
struct FakeWsabuf
{
    unsigned long len;
    char* buf;
};

struct FakeSlot
{
    uint64_t timestampMs = 0;
    uint32_t sequence = 0;
    uint32_t used = 0;
};

std::vector<uint8_t> Pattern(uint32_t length)
{
    std::vector<uint8_t> data(length);
    for (uint32_t i = 0; i < length; ++i)
        data[i] = static_cast<uint8_t>((i * 31u + 7u) & 0xFFu);
    return data;
}

void TestBufferSizes()
{
    // The hook's own receive buffer must hold any IPv4 UDP datagram, or the
    // kernel truncates on the hook's behalf before the game ever sees it.
    CHECK(kReceiveBufferBytes >= kMaxUdpPayloadBytes);
    CHECK(kMaxUdpPayloadBytes == 65535u - 20u - 8u);
    CHECK(kSlotBytes == 1500u);
}

void TestClassify()
{
    const uint32_t minSeq = 17;
    CHECK(ClassifyDatagram(false, 100, minSeq) == Admission::BypassNotIpv4);
    CHECK(ClassifyDatagram(true, 0, minSeq) == Admission::BypassShort);
    CHECK(ClassifyDatagram(true, 16, minSeq) == Admission::BypassShort);
    CHECK(ClassifyDatagram(true, 17, minSeq) == Admission::Reorder);
    CHECK(ClassifyDatagram(true, kSlotBytes, minSeq) == Admission::Reorder);
    // The P2-10 case: one byte past a slot used to be cut to 1500 bytes.
    CHECK(ClassifyDatagram(true, kSlotBytes + 1, minSeq) == Admission::BypassOversize);
    CHECK(ClassifyDatagram(true, kMaxUdpPayloadBytes, minSeq) == Admission::BypassOversize);
    // Custom slot size is honoured.
    CHECK(ClassifyDatagram(true, 64, minSeq, 32) == Admission::BypassOversize);

    CHECK(std::strcmp(AdmissionReason(Admission::BypassOversize), "oversize") == 0);
    CHECK(std::strcmp(AdmissionReason(Admission::BypassShort), "short") == 0);
    CHECK(std::strcmp(AdmissionReason(Admission::BypassNotIpv4), "not_ipv4") == 0);
    CHECK(std::strcmp(AdmissionReason(Admission::Reorder), "reorder") == 0);
}

void TestScatterFits()
{
    const std::vector<uint8_t> datagram = Pattern(3000);
    std::vector<char> a(1000, 0), c(2500, 0);
    FakeWsabuf buffers[4] = {
        { static_cast<unsigned long>(a.size()), a.data() },
        { 0, nullptr },                     // skipped: null
        { 64, nullptr },                    // skipped: null with length
        { static_cast<unsigned long>(c.size()), c.data() },
    };
    const ScatterResult r = ScatterDatagram(buffers, 4, datagram.data(), 3000);
    CHECK(r.copied == 3000);
    CHECK(r.capacity == 3500);
    CHECK(!r.truncated);
    CHECK(std::memcmp(a.data(), datagram.data(), 1000) == 0);
    CHECK(std::memcmp(c.data(), datagram.data() + 1000, 2000) == 0);
    CHECK(c[2000] == 0);
}

void TestScatterTruncates()
{
    // A datagram larger than the caller's buffers: the leading bytes land,
    // and truncation is reported so the hook can return WSAEMSGSIZE.
    const std::vector<uint8_t> datagram = Pattern(4000);
    std::vector<char> a(1024, 0), b(1024, 0);
    FakeWsabuf buffers[2] = {
        { static_cast<unsigned long>(a.size()), a.data() },
        { static_cast<unsigned long>(b.size()), b.data() },
    };
    const ScatterResult r = ScatterDatagram(buffers, 2, datagram.data(), 4000);
    CHECK(r.copied == 2048);
    CHECK(r.capacity == 2048);
    CHECK(r.truncated);
    CHECK(std::memcmp(a.data(), datagram.data(), 1024) == 0);
    CHECK(std::memcmp(b.data(), datagram.data() + 1024, 1024) == 0);
}

void TestScatterEdges()
{
    const std::vector<uint8_t> datagram = Pattern(10);
    const ScatterResult none = ScatterDatagram<FakeWsabuf>(nullptr, 0, datagram.data(), 10);
    CHECK(none.copied == 0);
    CHECK(none.truncated);

    const ScatterResult empty = ScatterDatagram<FakeWsabuf>(nullptr, 0, datagram.data(), 0);
    CHECK(!empty.truncated);

    std::vector<char> a(10, 0);
    FakeWsabuf exact[1] = { { 10, a.data() } };
    const ScatterResult r = ScatterDatagram(exact, 1, datagram.data(), 10);
    CHECK(r.copied == 10);
    CHECK(!r.truncated);

    // A zero-length datagram into real buffers is not a truncation.
    const ScatterResult zero = ScatterDatagram(exact, 1, datagram.data(), 0);
    CHECK(zero.copied == 0);
    CHECK(!zero.truncated);
    CHECK(zero.capacity == 10);

    // A jumbo datagram into a big buffer arrives whole.
    const std::vector<uint8_t> jumbo = Pattern(kMaxUdpPayloadBytes);
    std::vector<char> big(kReceiveBufferBytes, 0);
    FakeWsabuf bigBuf[1] = { { static_cast<unsigned long>(big.size()), big.data() } };
    const ScatterResult j = ScatterDatagram(bigBuf, 1, jumbo.data(), kMaxUdpPayloadBytes);
    CHECK(j.copied == kMaxUdpPayloadBytes);
    CHECK(!j.truncated);
    CHECK(std::memcmp(big.data(), jumbo.data(), kMaxUdpPayloadBytes) == 0);
}

void Fill(FakeSlot& slot, uint32_t sequence, uint64_t timestampMs)
{
    slot.used = 1;
    slot.sequence = sequence;
    slot.timestampMs = timestampMs;
}

void TestPlanInsert()
{
    FakeSlot slots[4] = {};
    CHECK(PlanInsert<FakeSlot>(nullptr, 4, 1).kind == InsertKind::Rejected);
    CHECK(PlanInsert(slots, 0, 1).kind == InsertKind::Rejected);

    InsertPlan p = PlanInsert(slots, 4, 10);
    CHECK(p.kind == InsertKind::Free && p.index == 0);
    Fill(slots[0], 10, 100);

    p = PlanInsert(slots, 4, 10);
    CHECK(p.kind == InsertKind::Duplicate && p.index == 0);

    p = PlanInsert(slots, 4, 11);
    CHECK(p.kind == InsertKind::Free && p.index == 1);
    Fill(slots[1], 11, 90);
    Fill(slots[2], 12, 120);
    Fill(slots[3], 13, 110);

    // Full: evict the oldest arrival (slot 1, t=90), not the lowest sequence.
    p = PlanInsert(slots, 4, 14);
    CHECK(p.kind == InsertKind::EvictOldest && p.index == 1);

    // Only the configured depth is considered.
    p = PlanInsert(slots, 2, 99);
    CHECK(p.kind == InsertKind::EvictOldest && p.index == 1);
}

void TestPickReadySlot()
{
    FakeSlot slots[4] = {};
    CHECK(PickReadySlot(slots, 4, false, 0, 50, 1000) == -1);
    CHECK(PickReadySlot<FakeSlot>(nullptr, 4, false, 0, 50, 1000) == -1);

    Fill(slots[0], 7, 1000);
    Fill(slots[2], 5, 1000);

    // Before the first delivery the lowest sequence goes at once.
    CHECK(PickReadySlot(slots, 4, false, 0, 50, 1000) == 2);

    // The next expected sequence goes at once.
    CHECK(PickReadySlot(slots, 4, true, 6, 50, 1000) == 0);

    // A gap: the lowest waits for the window ...
    CHECK(PickReadySlot(slots, 4, true, 3, 50, 1010) == -1);
    // ... and goes once it has waited windowMs.
    CHECK(PickReadySlot(slots, 4, true, 3, 50, 1050) == 2);

    // A clock that went backwards never releases early.
    CHECK(PickReadySlot(slots, 4, true, 3, 50, 900) == -1);
}
} // namespace

int main()
{
    TestBufferSizes();
    TestClassify();
    TestScatterFits();
    TestScatterTruncates();
    TestScatterEdges();
    TestPlanInsert();
    TestPickReadySlot();

    if (g_failures == 0)
        std::printf("net_reorder_core_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
