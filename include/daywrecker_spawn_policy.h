#pragma once
// daywrecker_spawn_policy.h
// Pure rules for the Daywrecker ODF keys [DayWreckerClass] fallOnSpawn and
// dropRate. No Windows or engine calls, so
// tests/daywrecker_spawn_policy_tests.cpp runs them directly. The engine side
// is src/patches/daywrecker_spawn_fall.cpp; evidence and limits:
// Docs/DAYWRECKER_FALL_ON_SPAWN.md and Docs/DAYWRECKER_DROP_RATE.md.
//
// Stock behaviour (GOG 2.2.301): DayWrecker::Simulate (0x004B0460) detonates
// on its first tick unless the PowerUp state flags ([obj+0x228]+0x114) have
// bit 0x4 (airborne) set. Only the Armory's ObjectLobber (0x00582190) sets it
// (|= 0xC) before the first tick, so a Daywrecker made any other way (Lua
// BuildObject, a map object) explodes where it was made. With 0x4 set,
// PowerUp::Simulate (0x005A7D70) runs the airborne step (gravity) and clears
// 0x4 when the object reaches the terrain; the next DayWrecker tick then
// detonates, as an Armory drop does.

#include "bool_token.h"

#include <cmath>
#include <cstdint>

namespace BZROpenShim
{
    namespace DayWreckerSpawnPolicy
    {
        // PowerUp state flags ([obj+0x228]+0x114).
        constexpr uint32_t kFlagLanded = 0x1;
        constexpr uint32_t kFlagAirborne = 0x4;   // falling; Simulate does not detonate
        constexpr uint32_t kFlagOwnerSafe = 0x8;  // ignore collision with the launcher
        constexpr uint32_t kFlagDetonated = 0x20; // set by Simulate/Explode when it blows

        // The ODF key. Absent or unparsable: off.
        constexpr const char* kSection = "DayWreckerClass";
        constexpr const char* kKey = "fallOnSpawn";

        inline bool ParseKey(const char* raw)
        {
            bool value = false;
            return raw && BoolToken::TryParse(raw, value) && value;
        }

        // Whether a freshly constructed Daywrecker gets the airborne bit.
        // Single player only: a network replica is built by the same
        // constructor (the create path, flags 0) and must keep its owner's
        // state. A Daywrecker already airborne or already blown is left alone.
        inline bool ShouldArm(bool singlePlayer, bool keyOn, uint32_t flags)
        {
            return singlePlayer && keyOn && (flags & (kFlagAirborne | kFlagDetonated)) == 0;
        }

        inline uint32_t ArmedFlags(uint32_t flags)
        {
            return flags | kFlagAirborne;
        }

        // ---- [DayWreckerClass] dropRate ----------------------------------
        // Time scale for an airborne Daywrecker: its Simulate runs with
        // dt * dropRate while the airborne bit is set. That fast-forwards the
        // flight (gravity, the descent drag, the drift terms all advance by
        // the larger step), so the arc and the landing point stay where the
        // Armory aimed them, up to step-size error; only the flight time
        // changes (time / dropRate).
        constexpr const char* kDropRateKey = "dropRate";
        constexpr float kDropRateStock = 1.0f;
        constexpr float kDropRateMin = 0.25f;
        // A larger step moves the bomb further per tick, so unit hits
        // (Collide) get coarser; the cap keeps that bounded. Terrain landing
        // is a height test, so it cannot be stepped over.
        constexpr float kDropRateMax = 3.0f;

        // Locale-independent: "2", "0.5", " 1.5 ", "2 ; comment". Absent,
        // junk, non-positive or not finite: stock (1). Out of range: clamped.
        inline float ParseDropRate(const char* raw)
        {
            if (!raw)
                return kDropRateStock;
            const char* p = raw;
            while (*p == ' ' || *p == '\t')
                ++p;
            if (*p == '+')
                ++p;
            bool sawDigit = false;
            double value = 0.0;
            while (*p >= '0' && *p <= '9')
            {
                value = value * 10.0 + static_cast<double>(*p - '0');
                sawDigit = true;
                ++p;
            }
            if (*p == '.')
            {
                ++p;
                double scale = 0.1;
                while (*p >= '0' && *p <= '9')
                {
                    value += static_cast<double>(*p - '0') * scale;
                    scale *= 0.1;
                    sawDigit = true;
                    ++p;
                }
            }
            while (*p == ' ' || *p == '\t')
                ++p;
            if (!sawDigit || (*p != '\0' && *p != ';' && *p != '/'))
                return kDropRateStock;
            const float rate = static_cast<float>(value);
            if (!std::isfinite(rate) || rate <= 0.0f)
                return kDropRateStock;
            if (rate < kDropRateMin)
                return kDropRateMin;
            if (rate > kDropRateMax)
                return kDropRateMax;
            return rate;
        }

        // The dt to hand the stock Simulate. Only an airborne, not yet
        // detonated Daywrecker in single player is scaled: a grounded one's
        // Simulate is the detonation itself, and a network game would
        // desynchronise the flight.
        inline float ScaledStep(bool singlePlayer, float rate, uint32_t flags, float dt)
        {
            if (!singlePlayer || rate == kDropRateStock)
                return dt;
            if ((flags & kFlagAirborne) == 0 || (flags & kFlagDetonated) != 0)
                return dt;
            return dt * rate;
        }

        // What a class's ODF asks for; read once per class.
        struct ClassSettings
        {
            bool fallOnSpawn = false;
            float dropRate = kDropRateStock;
        };

        // Per-class cache entry: the class pointer and its packed 8-character
        // ODF name (GameObjectClass +0x30), so a class freed and another
        // allocated at the same address is not mistaken for it.
        struct ClassKey
        {
            const void* cls = nullptr;
            uint32_t nameLo = 0;
            uint32_t nameHi = 0;
            bool operator==(const ClassKey& o) const
            {
                return cls == o.cls && nameLo == o.nameLo && nameHi == o.nameHi;
            }
        };

        // A small fixed cache; the ODF is read once per class.
        template <int N, typename V = bool>
        struct ClassCache
        {
            ClassKey keys[N] = {};
            V values[N] = {};
            int count = 0;
            int next = 0; // replacement cursor once full

            bool Find(const ClassKey& key, V& value) const
            {
                for (int i = 0; i < count; ++i)
                {
                    if (keys[i] == key)
                    {
                        value = values[i];
                        return true;
                    }
                }
                return false;
            }

            void Put(const ClassKey& key, const V& value)
            {
                for (int i = 0; i < count; ++i)
                {
                    if (keys[i] == key)
                    {
                        values[i] = value;
                        return;
                    }
                }
                int slot = count;
                if (count < N)
                    ++count;
                else
                {
                    slot = next;
                    next = (next + 1) % N;
                }
                keys[slot] = key;
                values[slot] = value;
            }

            void Clear()
            {
                count = 0;
                next = 0;
            }
        };
    }
}
