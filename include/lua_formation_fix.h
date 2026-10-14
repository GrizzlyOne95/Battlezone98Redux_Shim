// lua_formation_fix.h -- engine-independent logic for the repaired Lua
// Formation binding (src/patches/lua_formation_fix.cpp,
// Docs/LUA_FORMATION_BINDING_20261014.md).
//
// Stock binding 0x005079B0 is a byte-for-byte copy of Recycle(unit, prio):
// it reads argument 1 as a handle and argument 2 with luaL_optinteger, then
// calls native Formation(me, him, priority) with (me, thatInteger, 1). A
// script passing the leader handle therefore raises "number expected, got
// userdata", and Formation(unit) forms on handle 1.
//
// Header-only and free of Windows and engine dependencies so that
// tests/lua_formation_fix_tests.cpp can drive it with fake engine calls.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace LuaFormation
{
    // Lua 5.1 type codes as returned by lua_type (the engine's 0x0082D490:
    // -1 for an absent argument, then LUA_TNIL = 0 ... LUA_TNUMBER = 3).
    constexpr int kLuaTypeNone = -1;
    constexpr int kLuaTypeNil = 0;
    constexpr int kLuaTypeNumber = 3;

    enum class Arg2Kind
    {
        // Absent, nil or a number: keep the stock reading,
        // `him = luaL_optinteger(L, 2, 1)`. This is what every script that
        // worked before still gets, so the fix cannot turn a script that ran
        // (however pointlessly, e.g. Formation(unit) on handle 1) into one
        // that raises.
        StockInteger,
        // Anything else (the BZHandle userdata, or a wrong type): read it
        // with the engine's own handle getter, which raises the engine's
        // normal "bad argument" error for a value that is not a handle.
        Handle,
    };

    inline Arg2Kind ClassifyArg2(int luaType)
    {
        return (luaType <= kLuaTypeNil || luaType == kLuaTypeNumber)
            ? Arg2Kind::StockInteger
            : Arg2Kind::Handle;
    }

    // The engine entry points the binding needs; the installer fills this
    // with the verified addresses, tests with fakes.
    struct Engine
    {
        int32_t (*getHandle)(void* L, int index);                     // 0x004FF750
        int (*luaType)(void* L, int index);                           // 0x0082D490
        int32_t (*optInteger)(void* L, int index, int32_t def);       // 0x0082C1FD
        void (*formation)(int32_t me, int32_t him, int32_t priority); // 0x005CE680
    };

    // Formation(me, him, priority?) as a lua_CFunction body. Returns the
    // number of Lua results (0, like the stock binding).
    inline int Run(void* L, const Engine& engine)
    {
        const int32_t me = engine.getHandle(L, 1);
        int32_t him = 0;
        if (ClassifyArg2(engine.luaType(L, 2)) == Arg2Kind::StockInteger)
            him = engine.optInteger(L, 2, 1);
        else
            him = engine.getHandle(L, 2);
        const int32_t priority = engine.optInteger(L, 3, 1);
        engine.formation(me, him, priority);
        return 0;
    }
}
}
