#pragma once
// Installer for the repaired Lua Formation binding. See lua_formation_fix.h.

namespace BZROpenShim
{
    namespace LuaFormation
    {
        // Points the Lua registration entry for "Formation" at the repaired
        // binding. Fail-closed: any identity, byte or table mismatch leaves
        // the engine untouched. Safe to call repeatedly.
        void InstallLuaFormationFixIfPossible();
    }
}
