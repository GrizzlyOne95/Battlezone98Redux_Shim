// objective_cap_guard.h -- engine-independent logic for the objective list
// capacity guard (src/patches/objective_cap_guard.cpp).
//
// The objective panel (GOG Redux 2.2.301, global at 0x009B7998) keeps a fixed
// array of 10 entries: count at +0x08, entries of 0x18 bytes from +0x0C
// (char name[16], char* text, uint32 color), then the "display until" float
// at +0xFC. Add (0x004F39B0, __thiscall) writes entry[count] and increments
// count with no bounds check, so the 11th objective overwrites +0xFC and the
// object behind it. Lua AddObjective, mission DLLs (both through 0x004F6AB0)
// and the save loader (0x004F4370, N read from the save unchecked) reach it.
//
// Header-only and free of Windows and engine dependencies so that
// tests/objective_cap_guard_tests.cpp can drive it with fakes.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace ObjectiveCap
{
    constexpr int32_t kCapacity = 10;
    constexpr uint32_t kCountOffset = 0x08;
    constexpr uint32_t kEntriesOffset = 0x0C;
    constexpr uint32_t kEntryStride = 0x18;
    constexpr uint32_t kNameLength = 16;

    enum class Action
    {
        Add,                // room left: stock Add
        DropOldestThenAdd,  // full: remove entry 0 through the engine, then Add
        Reject,             // count already outside 0..10: the list is corrupt
    };

    inline const char* ActionName(Action a)
    {
        switch (a)
        {
        case Action::Add: return "add";
        case Action::DropOldestThenAdd: return "drop-oldest-then-add";
        case Action::Reject: return "reject";
        }
        return "?";
    }

    inline Action Decide(int32_t count)
    {
        if (count < 0 || count > kCapacity)
            return Action::Reject;
        if (count == kCapacity)
            return Action::DropOldestThenAdd;
        return Action::Add;
    }

    // What the guarded Add needs from the engine; the installer fills this
    // with SEH-guarded readers and the verified engine functions, tests with
    // fakes. `self` is the objective list object.
    struct Engine
    {
        // Reads the count at self+0x08. False when unreadable.
        bool (*readCount)(void* self, int32_t& count);
        // Copies entry 0's name (16 raw bytes) into out; Run terminates its
        // own 17-byte copy. False when unreadable.
        bool (*readOldestName)(void* self, char (&out)[kNameLength]);
        // Engine Remove (0x004F3E70): frees the text with the engine's CRT.
        void (*remove)(void* self, const char* name);
        // Stock Add through the trampoline.
        void (*add)(void* self, const char* name, uint32_t color, float duration, const char* text);
        // Logging hooks; may be null.
        void (*onDrop)(const char* dropped, const char* added);
        void (*onReject)(int32_t count, const char* added, const char* why);
    };

    // The guarded Add. Returns the action taken (Reject also covers a drop
    // that did not make room, so stock Add is never entered at count >= 10).
    inline Action Run(const Engine& engine, void* self, const char* name, uint32_t color, float duration,
                      const char* text)
    {
        int32_t count = 0;
        if (!engine.readCount(self, count))
        {
            if (engine.onReject) engine.onReject(-1, name, "count unreadable");
            return Action::Reject;
        }
        const Action action = Decide(count);
        if (action == Action::Reject)
        {
            if (engine.onReject) engine.onReject(count, name, "count outside 0..10");
            return Action::Reject;
        }
        if (action == Action::DropOldestThenAdd)
        {
            char raw[kNameLength] = {};
            if (!engine.readOldestName(self, raw))
            {
                if (engine.onReject) engine.onReject(count, name, "oldest entry unreadable");
                return Action::Reject;
            }
            // All 16 bytes plus a NUL: Remove compares 16 chars, so even an
            // entry with no terminator inside its 16 bytes still matches.
            char oldest[kNameLength + 1] = {};
            for (uint32_t i = 0; i < kNameLength; ++i)
                oldest[i] = raw[i];
            oldest[kNameLength] = '\0';
            // Remove matches by name and takes the first hit, which is entry
            // 0 itself (or an earlier duplicate of it: there is none before 0).
            engine.remove(self, oldest);
            int32_t after = 0;
            if (!engine.readCount(self, after) || after >= kCapacity || after < 0)
            {
                if (engine.onReject) engine.onReject(after, name, "dropping the oldest entry made no room");
                return Action::Reject;
            }
            if (engine.onDrop) engine.onDrop(oldest, name);
        }
        engine.add(self, name, color, duration, text);
        return action;
    }
}
}
