#pragma once

// Engine-independent multiplayer pieces of `classLabel = "tracked"`
// (src/patches/tracked_vehicle_class.cpp, Docs/TRACKED_VEHICLES.md
// "Multiplayer").
//
// The owner simulates a tracked unit; every other peer holds a replica that
// the stock GameObject::Simulate dead-reckons from the last received pose.
// The turret angle is not part of the stock replication, so the owner
// broadcasts it in a small OpenShim net message and each replica slews its
// displayed angle toward the received one once per frame.
//
// 'T','Y' turret batch v1 (little-endian, 4 + 12 * count bytes):
//   +0  tag 'T','Y'      +2 version 1     +3 u8 count (1..kMaxRecords)
//   then count records of 12 bytes:
//   +0  u32 DistributedObject id (the stock dwLocalID; 0 is never sent)
//   +4  f32 delta: turret yaw relative to the hull, radians, + left
//   +8  f32 rate: its slew rate, rad/s
// A peer sends at most one batch per frame (more only when it owns more than
// kMaxRecords turrets due in the same frame); the per-object send policy
// decides which records go in.

#include "tracked_vehicle_turret.h"

#include <cmath>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::TrackedNet
{
    namespace TU = TrackedTurret;
    using Vec3 = TrackedPhysics::Vec3;

    constexpr uint16_t kTagTurret = 0x5954;  // 'T','Y' read little-endian
    constexpr uint8_t kVersion = 1;
    constexpr unsigned kHeaderLen = 4;
    constexpr unsigned kRecordLen = 12;
    // 16 records = 196 bytes: far under the 1152-byte packing buffer of the
    // stock Lua Send (Docs/MP_LUA_REPLICATION_QUALIFICATION.md) and under the
    // older ~244-byte estimate too.
    constexpr unsigned kMaxRecords = 16;
    constexpr unsigned kMaxPacketLen = kHeaderLen + kRecordLen * kMaxRecords;

    // Owner send policy: on a change, at most every kMinSendIntervalMs, and
    // a refresh every kRefreshMs while the turret exists.
    constexpr uint64_t kMinSendIntervalMs = 200;
    constexpr uint64_t kRefreshMs = 1000;
    constexpr float kDeltaThreshold = 0.01f;  // rad, about 0.6 degrees
    constexpr float kRateThreshold = 0.05f;   // rad/s

    // Replica: a received angle older than this is ignored (the displayed
    // angle holds); it is extrapolated by its rate for at most
    // kMaxExtrapolateSeconds; the displayed angle catches up at up to
    // kCatchUpFactor times the class's yawRate.
    constexpr uint64_t kStaleMs = 5000;
    constexpr float kMaxExtrapolateSeconds = 0.25f;
    constexpr float kCatchUpFactor = 2.0f;
    // The replica's tread speeds use the owner's last received slew rate
    // while it is at most this old (two refreshes), else 0.
    constexpr uint64_t kRateMaxAgeMs = 2 * kRefreshMs;

    // Payload bounds: a rate slightly above the largest sanitized yawRate
    // is still accepted.
    constexpr float kMaxDelta = TU::kPi + 1.0e-3f;
    constexpr float kMaxRate = TU::kMaxYawRate * 1.01f;

    struct TurretRecord
    {
        uint32_t id = 0;
        float delta = 0.0f;
        float rate = 0.0f;
    };

    // Packs the first min(count, kMaxRecords) records; returns the byte
    // length, 0 for no records.
    inline unsigned Pack(const TurretRecord* records, unsigned count, uint8_t (&out)[kMaxPacketLen])
    {
        std::memset(out, 0, sizeof(out));
        if (!records || count == 0)
            return 0;
        if (count > kMaxRecords)
            count = kMaxRecords;
        out[0] = 'T';
        out[1] = 'Y';
        out[2] = kVersion;
        out[3] = static_cast<uint8_t>(count);
        for (unsigned i = 0; i < count; ++i)
        {
            uint8_t* rec = out + kHeaderLen + kRecordLen * i;
            std::memcpy(rec, &records[i].id, sizeof(records[i].id));
            std::memcpy(rec + 4, &records[i].delta, sizeof(records[i].delta));
            std::memcpy(rec + 8, &records[i].rate, sizeof(records[i].rate));
        }
        return kHeaderLen + kRecordLen * count;
    }

    enum class UnpackResult
    {
        NotOurs,  // too short for a header, or another tag/version: hand it on
        Invalid,  // our message with a bad header: consume and ignore it
        Ok,       // header fine; bad records are skipped and counted
    };

    struct TurretBatch
    {
        TurretRecord records[kMaxRecords];
        unsigned count = 0;     // valid records
        unsigned rejected = 0;  // records skipped for a bad value
    };

    inline bool RecordValid(const TurretRecord& r)
    {
        return r.id != 0 && std::isfinite(r.delta) && std::fabs(r.delta) <= kMaxDelta &&
               std::isfinite(r.rate) && std::fabs(r.rate) <= kMaxRate;
    }

    inline UnpackResult Unpack(const unsigned char* buf, unsigned len, TurretBatch& out)
    {
        out.count = 0;
        out.rejected = 0;
        if (!buf || len < kHeaderLen || buf[0] != 'T' || buf[1] != 'Y' || buf[2] != kVersion)
            return UnpackResult::NotOurs;
        const unsigned count = buf[3];
        if (count == 0 || count > kMaxRecords || len < kHeaderLen + kRecordLen * count)
            return UnpackResult::Invalid;
        for (unsigned i = 0; i < count; ++i)
        {
            const unsigned char* rec = buf + kHeaderLen + kRecordLen * i;
            TurretRecord r;
            std::memcpy(&r.id, rec, sizeof(r.id));
            std::memcpy(&r.delta, rec + 4, sizeof(r.delta));
            std::memcpy(&r.rate, rec + 8, sizeof(r.rate));
            if (RecordValid(r))
                out.records[out.count++] = r;
            else
                ++out.rejected;
        }
        return UnpackResult::Ok;
    }

    // The owner's outgoing batch. The simulation has no frame counter OpenShim
    // can read without a new resolve, so a frame boundary is detected when an
    // owner turret object is visited a second time since the last flush:
    // every live owner turret runs PostSimulate once per frame, so the batch
    // goes out one frame late at most. Main (simulation) thread only.
    struct SendBatch
    {
        static constexpr unsigned kMaxVisited = 256;
        const void* visited[kMaxVisited] = {};
        unsigned visitedCount = 0;
        TurretRecord records[kMaxRecords];
        unsigned count = 0;

        // True when obj was already visited (or the visit list is full): a
        // new frame has started, so the caller flushes and calls again.
        bool NoteVisit(const void* obj)
        {
            for (unsigned i = 0; i < visitedCount; ++i)
            {
                if (visited[i] == obj)
                    return true;
            }
            if (visitedCount >= kMaxVisited)
                return true;
            visited[visitedCount++] = obj;
            return false;
        }

        // False when the batch is full: the caller flushes the records and
        // adds again.
        bool Add(const TurretRecord& r)
        {
            if (count >= kMaxRecords)
                return false;
            records[count++] = r;
            return true;
        }

        void ClearRecords() { count = 0; }

        void Reset()
        {
            visitedCount = 0;
            count = 0;
        }
    };

    // Received angles by object id, a fixed table so storing never
    // allocates. The caller locks. A full table replaces the oldest entry;
    // entries older than kStaleMs never match.
    struct ReceivedTurret
    {
        uint32_t id = 0;  // 0: empty slot
        float delta = 0.0f;
        float rate = 0.0f;
        uint64_t tickMs = 0;
    };

    struct ReceivedTable
    {
        static constexpr unsigned kSlots = 256;
        ReceivedTurret slots[kSlots];

        void Store(uint32_t id, float delta, float rate, uint64_t now)
        {
            if (id == 0)
                return;
            ReceivedTurret* target = nullptr;
            ReceivedTurret* oldest = &slots[0];
            for (ReceivedTurret& s : slots)
            {
                if (s.id == id)
                {
                    target = &s;
                    break;
                }
                if (!target && s.id == 0)
                    target = &s;
                if (s.tickMs < oldest->tickMs)
                    oldest = &s;
            }
            if (!target)
                target = oldest;
            target->id = id;
            target->delta = delta;
            target->rate = rate;
            target->tickMs = now;
        }

        // The entry for id if it is at most maxAgeMs old.
        bool Lookup(uint32_t id, uint64_t now, uint64_t maxAgeMs, ReceivedTurret& out) const
        {
            if (id == 0)
                return false;
            for (const ReceivedTurret& s : slots)
            {
                if (s.id == id)
                {
                    if (now < s.tickMs || now - s.tickMs > maxAgeMs)
                        return false;
                    out = s;
                    return true;
                }
            }
            return false;
        }

        void Clear()
        {
            for (ReceivedTurret& s : slots)
                s = ReceivedTurret{};
        }
    };

    struct SendState
    {
        bool sent = false;
        float delta = 0.0f;
        float rate = 0.0f;
        uint64_t tickMs = 0;
    };

    inline bool ShouldSend(const SendState& state, float delta, float rate, uint64_t nowMs)
    {
        if (!state.sent)
            return true;
        const uint64_t elapsed = nowMs >= state.tickMs ? nowMs - state.tickMs : 0;
        if (elapsed < kMinSendIntervalMs)
            return false;
        if (elapsed >= kRefreshMs)
            return true;
        return std::fabs(TU::WrapAngle(delta - state.delta)) > kDeltaThreshold ||
               std::fabs(rate - state.rate) > kRateThreshold;
    }

    inline void MarkSent(SendState& state, float delta, float rate, uint64_t nowMs)
    {
        state.sent = true;
        state.delta = delta;
        state.rate = rate;
        state.tickMs = nowMs;
    }

    // The received angle carried forward by its rate for ageSeconds (capped).
    inline float ReplicaTarget(const TU::Config& c, float delta, float rate, float ageSeconds)
    {
        if (!std::isfinite(ageSeconds) || ageSeconds < 0.0f)
            ageSeconds = 0.0f;
        if (ageSeconds > kMaxExtrapolateSeconds)
            ageSeconds = kMaxExtrapolateSeconds;
        if (!std::isfinite(rate))
            rate = 0.0f;
        const float target = delta + rate * ageSeconds;
        if (!std::isfinite(target))
            return 0.0f;
        return c.limited ? TrackedPhysics::Clamp(target, c.yawMin, c.yawMax) : TU::WrapAngle(target);
    }

    // The displayed angle one frame on: toward target, the short way round
    // (inside the limits for a limited turret), at no more than
    // kCatchUpFactor * yawRate.
    inline float SlewToward(const TU::Config& c, float current, float target, float dt)
    {
        if (!std::isfinite(current))
            current = 0.0f;
        if (!std::isfinite(target) || !std::isfinite(dt) || !(dt > 0.0f))
            return current;
        const float maxStep = kCatchUpFactor * c.yawRate * dt;
        const float diff = c.limited ? target - current : TU::WrapAngle(target - current);
        const float next = current + TrackedPhysics::Clamp(diff, -maxStep, maxStep);
        return c.limited ? TrackedPhysics::Clamp(next, c.yawMin, c.yawMax) : TU::WrapAngle(next);
    }

    struct TreadSpeeds
    {
        float left = 0.0f;
        float right = 0.0f;
    };

    // A replica's tread speeds from its replicated motion, in the contact
    // model's convention (TrackedPhysics::Step: left = v - w * halfWidth,
    // right = v + w * halfWidth, +w turns left). v is the velocity along the
    // hull's front; w is the hull's yaw rate, the root-local omega.y less the
    // turret's slew (the owner's last received rate, so the replica's own
    // catch-up slew does not show as hull turn). rootRight/rootFront are the
    // root (turret) axes.
    inline TreadSpeeds ReplicaTreadSpeeds(Vec3 veloc, Vec3 rootRight, Vec3 rootFront, float omegaY,
                                          float delta, float turretRate, float halfWidth)
    {
        TreadSpeeds out;
        Vec3 hullRight{ 0.0f, 0.0f, 0.0f };
        Vec3 hullFront{ 0.0f, 0.0f, 0.0f };
        TU::HullAxes(rootRight, rootFront, delta, hullRight, hullFront);
        const float v = TrackedPhysics::Dot(veloc, hullFront);
        const float w = omegaY - turretRate;
        if (!std::isfinite(v) || !std::isfinite(w) || !std::isfinite(halfWidth))
            return out;
        out.left = v - w * halfWidth;
        out.right = v + w * halfWidth;
        return out;
    }
}
