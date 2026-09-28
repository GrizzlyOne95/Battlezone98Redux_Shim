#pragma once

// Engine- and Winsock-independent core of the experimental UDP reorder path
// (net_optimizer.cpp, [OpenShimSocket] EnablePacketReorder, off by default).
//
// Kept free of Windows so tests/net_reorder_core_tests.cpp can run it on the
// host. net_optimizer.cpp owns the locking, logging and Winsock calls; this
// header owns the decisions that decide whether a datagram survives:
//
//   * ClassifyDatagram - which datagrams may enter a reorder slot. A slot holds
//     kSlotBytes; anything larger is delivered straight through, in arrival
//     order, instead of being cut down to the slot size.
//   * ScatterDatagram  - copying a datagram into the caller's WSABUF array and
//     reporting truncation, so the hook can return WSAEMSGSIZE exactly as
//     Winsock does when the caller's buffers are smaller than the datagram.
//   * PlanInsert / PickReadySlot - the per-peer slot ring.
//
// The hook receives into a kReceiveBufferBytes scratch buffer, which holds any
// IPv4 UDP payload, so the kernel never truncates a datagram on the hook's
// behalf either.
//
// C++14-compatible on purpose: no nested namespace definitions, and every
// static_assert carries a message.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
namespace NetReorder
{
    // Bytes one reorder slot can hold. BZR game traffic sits far below an
    // Ethernet MTU; the slots stay this size so the peer table stays small
    // (kSlotBytes * depth * peers is allocated statically).
    constexpr uint32_t kSlotBytes = 1500;

    // Largest payload a single IPv4 UDP datagram can carry
    // (65535 - 20-byte IP header - 8-byte UDP header).
    constexpr uint32_t kMaxUdpPayloadBytes = 65507;

    // The hook's private receive buffer. Large enough for any IPv4 UDP
    // datagram, so a receive into it can never end in WSAEMSGSIZE.
    constexpr uint32_t kReceiveBufferBytes = 65536;
    static_assert(kReceiveBufferBytes >= kMaxUdpPayloadBytes,
        "the reorder receive buffer must hold any IPv4 UDP payload");
    static_assert(kSlotBytes <= kReceiveBufferBytes,
        "a reorder slot cannot be larger than the receive buffer");

    enum class Admission
    {
        Reorder,         // sequenced and fits a slot: buffer and reorder it
        BypassNotIpv4,   // no IPv4 source: deliver immediately
        BypassShort,     // too short to carry the sequence: deliver immediately
        BypassOversize,  // larger than a slot: deliver immediately, never cut
    };

    inline Admission ClassifyDatagram(
        bool ipv4Source,
        uint32_t length,
        uint32_t minSequencedBytes,
        uint32_t slotBytes = kSlotBytes)
    {
        if (!ipv4Source)
            return Admission::BypassNotIpv4;
        if (length < minSequencedBytes)
            return Admission::BypassShort;
        if (length > slotBytes)
            return Admission::BypassOversize;
        return Admission::Reorder;
    }

    inline const char* AdmissionReason(Admission admission)
    {
        switch (admission)
        {
        case Admission::Reorder: return "reorder";
        case Admission::BypassNotIpv4: return "not_ipv4";
        case Admission::BypassShort: return "short";
        case Admission::BypassOversize: return "oversize";
        }
        return "unknown";
    }

    struct ScatterResult
    {
        uint32_t copied = 0;     // bytes written into the caller's buffers
        uint32_t capacity = 0;   // total bytes the caller's buffers can hold
        bool truncated = false;  // the datagram did not fit: WSAEMSGSIZE
    };

    // Scatter one datagram across a WSABUF-shaped array (any type with `buf`
    // and `len` members). Fills buffers in order, skipping null or empty ones,
    // and reports whether the datagram was cut short.
    template <typename Buffer>
    ScatterResult ScatterDatagram(
        Buffer* buffers,
        uint32_t bufferCount,
        const uint8_t* source,
        uint32_t sourceLength)
    {
        ScatterResult result;
        if (!buffers)
        {
            result.truncated = sourceLength > 0;
            return result;
        }

        for (uint32_t i = 0; i < bufferCount; ++i)
        {
            if (!buffers[i].buf || buffers[i].len == 0)
                continue;

            const uint32_t length = static_cast<uint32_t>(buffers[i].len);
            result.capacity = (result.capacity > UINT32_MAX - length)
                ? UINT32_MAX
                : result.capacity + length;

            if (result.copied >= sourceLength)
                continue;

            uint32_t chunk = sourceLength - result.copied;
            if (chunk > length)
                chunk = length;
            std::memcpy(buffers[i].buf, source + result.copied, chunk);
            result.copied += chunk;
        }

        result.truncated = result.copied < sourceLength;
        return result;
    }

    enum class InsertKind
    {
        Rejected,     // no slots configured (depth 0)
        Duplicate,    // this sequence is already buffered: drop the new copy
        Free,         // store in the free slot at `index`
        EvictOldest,  // every slot is used: overwrite the oldest at `index`
    };

    struct InsertPlan
    {
        InsertKind kind = InsertKind::Rejected;
        uint32_t index = 0;
    };

    // Slot is any type with `used`, `sequence` and `timestampMs` members.
    template <typename Slot>
    InsertPlan PlanInsert(const Slot* slots, uint32_t depth, uint32_t sequence)
    {
        InsertPlan plan;
        if (!slots || depth == 0)
            return plan;

        for (uint32_t i = 0; i < depth; ++i)
        {
            if (slots[i].used && slots[i].sequence == sequence)
            {
                plan.kind = InsertKind::Duplicate;
                plan.index = i;
                return plan;
            }
        }

        for (uint32_t i = 0; i < depth; ++i)
        {
            if (!slots[i].used)
            {
                plan.kind = InsertKind::Free;
                plan.index = i;
                return plan;
            }
        }

        uint32_t oldest = 0;
        for (uint32_t i = 1; i < depth; ++i)
        {
            if (slots[i].timestampMs < slots[oldest].timestampMs)
                oldest = i;
        }
        plan.kind = InsertKind::EvictOldest;
        plan.index = oldest;
        return plan;
    }

    // Which buffered slot, if any, may be delivered now. Returns -1 for none.
    //   * the next expected sequence goes out at once;
    //   * before the first delivery the lowest sequence goes out at once;
    //   * otherwise the lowest sequence goes out once it has waited windowMs.
    template <typename Slot>
    int PickReadySlot(
        const Slot* slots,
        uint32_t depth,
        bool sequenceInitialized,
        uint32_t lastSequence,
        uint32_t windowMs,
        uint64_t nowMs)
    {
        if (!slots)
            return -1;

        if (sequenceInitialized)
        {
            const uint32_t expected = lastSequence + 1;
            for (uint32_t i = 0; i < depth; ++i)
            {
                if (slots[i].used && slots[i].sequence == expected)
                    return static_cast<int>(i);
            }
        }

        int lowest = -1;
        for (uint32_t i = 0; i < depth; ++i)
        {
            if (!slots[i].used)
                continue;
            if (lowest < 0 || slots[i].sequence < slots[lowest].sequence)
                lowest = static_cast<int>(i);
        }

        if (lowest < 0)
            return -1;
        if (!sequenceInitialized)
            return lowest;

        const uint64_t stamp = slots[lowest].timestampMs;
        if (nowMs >= stamp && (nowMs - stamp) >= windowMs)
            return lowest;
        return -1;
    }
} // namespace NetReorder
} // namespace BZROpenShim
