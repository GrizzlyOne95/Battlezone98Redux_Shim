#pragma once
// daywrecker_spawn_policy.h
// Pure rules for the Daywrecker fall-on-spawn ODF key
// ([DayWreckerClass] fallOnSpawn). No Windows or engine calls, so
// tests/daywrecker_spawn_policy_tests.cpp runs them directly. The engine side
// is src/patches/daywrecker_spawn_fall.cpp; evidence and limits:
// Docs/DAYWRECKER_FALL_ON_SPAWN.md.
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
        template <int N>
        struct ClassCache
        {
            ClassKey keys[N] = {};
            bool values[N] = {};
            int count = 0;
            int next = 0; // replacement cursor once full

            bool Find(const ClassKey& key, bool& value) const
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

            void Put(const ClassKey& key, bool value)
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
