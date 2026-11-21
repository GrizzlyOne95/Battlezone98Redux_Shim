// handle_sequence_check.h -- engine-independent logic for the object handle
// sequence check (src/patches/handle_sequence_check.cpp).
//
// GOG Redux 2.2.301 object handles are (slot << 20) | (sequence & 0xFFFFF):
// 12 index bits for the 4096-slot pool and 20 sequence bits.
//   GameObject::GetHandle 0x00462380 builds [obj+0x160] << 0x14 | [obj+0x15C] & 0xFFFFF.
//   The handle lookup 0x004DA060 takes slot = (h >> 20) & 0xFFF and rejects
//   the object unless [obj+0x15C] == h & 0xFFFFF.
//   The GameObject constructor 0x004DA0B0 stores the global counter at
//   0x008E8660 (initial value 1) unmasked into [obj+0x15C] and increments it;
//   nothing else writes it except the save loader restoring "seq_count".
// So the counter never saturates or wraps into the index bits: once it reaches
// 0x100000, every new object stores a sequence the lookup's 20-bit compare can
// never equal. The object spawns, but its handle resolves to nothing (Lua sees
// nil, multiplayer peers reject it). About 1,048,575 creations per session.
//
// The check only reads the counter. Header-only and free of Windows and engine
// dependencies so tests/handle_sequence_check_tests.cpp can drive it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace HandleSequence
{
    constexpr uint32_t kSequenceBits = 20;
    // First counter value whose object can no longer be looked up.
    constexpr uint32_t kExhaustedAt = 1u << kSequenceBits;  // 0x100000
    // 90% of the sequence space.
    constexpr uint32_t kWarnAt = static_cast<uint32_t>((static_cast<uint64_t>(kExhaustedAt) * 9u) / 10u);

    // Offsets of the three abs32 counter operands inside the patches.json row
    // GameObjectCtorSequenceAssign (mov ecx,[ctr] / mov [eax+0x15C],ecx /
    // mov edx,[ctr] / add edx,1 / mov [ctr],edx). Pinned against that row's
    // expected bytes by tests/handle_sequence_check_tests.cpp.
    constexpr uint32_t kCtorOperandOffsets[3] = { 0x08, 0x14, 0x1D };

    enum class Level
    {
        Normal,
        Warn,       // >= 90% of the sequence space used
        Exhausted,  // the next object (and every one after it) is unreferenceable
    };

    inline Level Classify(uint32_t counter)
    {
        if (counter >= kExhaustedAt)
            return Level::Exhausted;
        if (counter >= kWarnAt)
            return Level::Warn;
        return Level::Normal;
    }

    // Percent of the sequence space used, rounded; 100 only once exhausted.
    inline uint32_t PercentUsed(uint32_t counter)
    {
        if (counter >= kExhaustedAt)
            return 100;
        const uint32_t p = static_cast<uint32_t>(
            (static_cast<uint64_t>(counter) * 100u + kExhaustedAt / 2u) / kExhaustedAt);
        return p > 99u ? 99u : p;
    }

    // Sequence numbers left before the counter reaches kExhaustedAt.
    inline uint32_t Remaining(uint32_t counter)
    {
        return counter >= kExhaustedAt ? 0u : kExhaustedAt - counter;
    }

    enum class Event
    {
        None,
        Warn,       // crossed into Warn (from Normal)
        Exhausted,  // crossed into Exhausted (from Normal or Warn)
        // The level dropped (save load / new mission restored a lower
        // counter). Intended: a drop from Exhausted to Warn reports only this,
        // not a fresh Warn; the Info line carries the new percentage.
        Rearmed,
    };

    struct Tracker
    {
        bool started = false;
        Level level = Level::Normal;
    };

    // Feeds one counter reading. Reports a crossing only when the level rises,
    // so a steady value logs nothing; a lower level re-arms both lines. The
    // first reading counts as a rise from Normal, so a save loaded already past
    // a threshold is reported once.
    inline Event Observe(Tracker& t, uint32_t counter)
    {
        const Level next = Classify(counter);
        const Level prev = t.started ? t.level : Level::Normal;
        t.started = true;
        t.level = next;
        if (next == prev)
            return Event::None;
        if (next < prev)
            return Event::Rearmed;
        return next == Level::Exhausted ? Event::Exhausted : Event::Warn;
    }
}
}
