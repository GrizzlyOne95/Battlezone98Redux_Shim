#pragma once
#include <array>
#include <cstdint>

namespace BZROpenShim
{
// Copied SDK record v1; no endpoint, identity, payload or borrowed pointers.
// Tx counts Winsock-accepted submissions (pending included), Rx completed reads.
// These are UDP payload bytes, including the BZR header, excluding IP/UDP overhead.
struct NetworkTrafficSnapshot
{
    uint32_t version = 1, structSize = sizeof(NetworkTrafficSnapshot);
    uint32_t available = 0, windowMs = 2000;
    uint64_t sampledAtMs = 0, txBytes = 0, rxBytes = 0, txPackets = 0, rxPackets = 0;
    uint32_t txBytesPerSecond = 0, rxBytesPerSecond = 0;
    uint32_t txPacketsPerSecond = 0, rxPacketsPerSecond = 0;
    uint32_t route = 0; // 0 idle/unknown, 1 relay observed, 2 direct observed, 3 mixed, 4 unclassified UDP
    uint32_t routeAgeMs = UINT32_MAX, receiveAgeMs = UINT32_MAX;
    uint32_t coverageLimited = 0; // pending completion registration overflow/unsupported path
};
static_assert(sizeof(NetworkTrafficSnapshot) == 88, "SDK traffic record layout");

// Host-testable bounded rolling counter. Caller serializes access.
class NetworkTrafficWindow
{
    struct Bucket { uint64_t epoch = UINT64_MAX, txBytes = 0, rxBytes = 0, txPackets = 0, rxPackets = 0; uint32_t routes = 0; };
    std::array<Bucket, 8> buckets_{};
    uint64_t lastTraffic_ = UINT64_MAX, lastRx_ = UINT64_MAX;
    uint64_t txBytes_ = 0, rxBytes_ = 0, txPackets_ = 0, rxPackets_ = 0;
public:
    void Reset(uint64_t) { *this = NetworkTrafficWindow{}; }
    void Observe(uint64_t now, bool tx, uint32_t bytes, uint32_t route)
    {
        auto& b = buckets_[(now / 250) % buckets_.size()];
        if (b.epoch != now / 250) { b = {}; b.epoch = now / 250; }
        if (tx) { b.txBytes += bytes; ++b.txPackets; txBytes_ += bytes; ++txPackets_; }
        else { b.rxBytes += bytes; ++b.rxPackets; rxBytes_ += bytes; ++rxPackets_; lastRx_ = now; }
        b.routes |= route; lastTraffic_ = now;
    }
    NetworkTrafficSnapshot Snapshot(uint64_t now) const
    {
        NetworkTrafficSnapshot out;
        out.sampledAtMs = now;
        out.txBytes = txBytes_; out.rxBytes = rxBytes_; out.txPackets = txPackets_; out.rxPackets = rxPackets_;
        uint64_t tx = 0, rx = 0, tp = 0, rp = 0;
        uint32_t routes = 0;
        for (const auto& b : buckets_) if (b.epoch != UINT64_MAX && now / 250 >= b.epoch && now / 250 - b.epoch < 8)
        { tx += b.txBytes; rx += b.rxBytes; tp += b.txPackets; rp += b.rxPackets; routes |= b.routes; }
        // Fixed denominator: rates decay to zero without a reader or new traffic.
        out.txBytesPerSecond = static_cast<uint32_t>(tx / 2); out.rxBytesPerSecond = static_cast<uint32_t>(rx / 2);
        out.txPacketsPerSecond = static_cast<uint32_t>(tp / 2); out.rxPacketsPerSecond = static_cast<uint32_t>(rp / 2);
        out.route = (routes & 3) == 3 ? 3 : (routes & 1) ? ((routes & 4) ? 3 : 1) :
            (routes & 2) ? ((routes & 4) ? 3 : 2) : (routes & 4) ? 4 : 0;
        auto age = [now](uint64_t at) { return at == UINT64_MAX || now < at ? UINT32_MAX :
            static_cast<uint32_t>((now - at) > UINT32_MAX ? UINT32_MAX : now - at); };
        out.routeAgeMs = age(lastTraffic_); out.receiveAgeMs = age(lastRx_);
        return out;
    }
};
}
