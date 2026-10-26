// lua_getindependence_guard.h -- engine-independent logic for the guarded Lua
// GetIndependence binding (src/patches/lua_getindependence_guard.cpp).
//
// Stock binding 0x005041F0 calls native GetIndependence 0x005CB660, which
// resolves the handle, takes the AI process pointer at GameObject+0xFC and
// returns [process+0x18] after testing only that the pointer is non-null.
// While a save loads, GameObject::Load leaves a placeholder in that field
// (the saved pointer id, or 1 in missionSave mode) and PostLoadAll replaces
// it with the real process later. A Lua mission Load() callback that runs in
// between and calls GetIndependence reads [placeholder+0x18] and faults; the
// access violation is native, so pcall cannot catch it.
//
// Header-only and free of Windows and engine dependencies so that
// tests/lua_getindependence_guard_tests.cpp can drive it with fakes.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace LuaGetIndependence
{
    // Below this, a "pointer" is the low 64 KB that Windows never maps: the
    // save placeholders (1, small pointer ids) all land here.
    constexpr uintptr_t kMinPointer = 0x10000;

    enum class Verdict
    {
        NoObject,       // handle does not resolve: stock returns 0 here too
        NoProcess,      // process pointer is null: stock returns 0 here too
        Placeholder,    // below kMinPointer: a load-time placeholder
        Unreadable,     // the first word (vtable) could not be read
        ForeignVtable,  // vtable outside the game image, or no RTTI behind it
        Accept,         // a real polymorphic object: forward to stock
    };

    inline const char* VerdictName(Verdict v)
    {
        switch (v)
        {
        case Verdict::NoObject: return "no-object";
        case Verdict::NoProcess: return "no-process";
        case Verdict::Placeholder: return "placeholder";
        case Verdict::Unreadable: return "unreadable";
        case Verdict::ForeignVtable: return "foreign-vtable";
        case Verdict::Accept: return "accept";
        }
        return "?";
    }

    // What the binding needs from the engine; the installer fills this with
    // verified addresses and SEH-guarded readers, tests with fakes.
    struct Engine
    {
        int32_t (*getHandle)(void* L, int index);              // 0x004FF750
        void (*pushInteger)(void* L, int32_t value);           // 0x0082CCCA
        int32_t (*getIndependence)(int32_t handle);            // 0x005CB660
        void* (*getObject)(int32_t handle);                    // 0x00462630
        // Reads the AI process pointer at object+0xFC. False when unreadable.
        bool (*readProcess)(const void* object, uintptr_t& process);
        // Reads the first word of the process. False when unreadable.
        bool (*readVtable)(uintptr_t process, uintptr_t& vtable);
        // True when vtable lies in the game image and carries MSVC RTTI.
        bool (*vtableIsGameClass)(uintptr_t vtable);
        // Called once per rejected (non-stock-zero) lookup, for logging.
        void (*onReject)(int32_t handle, uintptr_t process, uintptr_t vtable, Verdict verdict);
    };

    inline Verdict Classify(const Engine& engine, int32_t handle, uintptr_t& process, uintptr_t& vtable)
    {
        process = 0;
        vtable = 0;
        const void* object = engine.getObject(handle);
        if (!object)
            return Verdict::NoObject;
        if (!engine.readProcess(object, process))
            return Verdict::Unreadable;
        if (process == 0)
            return Verdict::NoProcess;
        if (process < kMinPointer)
            return Verdict::Placeholder;
        if (!engine.readVtable(process, vtable))
            return Verdict::Unreadable;
        if (!engine.vtableIsGameClass(vtable))
            return Verdict::ForeignVtable;
        return Verdict::Accept;
    }

    // GetIndependence(h) as a lua_CFunction body: one integer result, like
    // the stock binding. A process that is not a real object reads as 0
    // (what stock already returns for a handle with no process), and the
    // native function is never entered for it.
    inline int Run(void* L, const Engine& engine)
    {
        const int32_t handle = engine.getHandle(L, 1);
        uintptr_t process = 0, vtable = 0;
        const Verdict verdict = Classify(engine, handle, process, vtable);
        int32_t value = 0;
        if (verdict == Verdict::Accept)
            value = engine.getIndependence(handle);
        else if (verdict != Verdict::NoObject && verdict != Verdict::NoProcess)
            engine.onReject(handle, process, vtable, verdict);
        engine.pushInteger(L, value);
        return 1;
    }
}
}
