#pragma once
// Installer for the guarded Lua GetIndependence binding. See
// lua_getindependence_guard.h.

namespace BZROpenShim
{
    namespace LuaGetIndependence
    {
        // Points the Lua registration entry for "GetIndependence" at the
        // guarded binding. Fail-closed: any identity, byte or table mismatch
        // leaves the engine untouched. Safe to call repeatedly.
        void InstallLuaGetIndependenceGuardIfPossible();
    }
}
