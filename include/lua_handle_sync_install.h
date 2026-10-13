#pragma once
// Installer for the Lua handle label remap. See lua_handle_sync.h.

namespace BZROpenShim
{
    namespace LuaHandleSync
    {
        // Rewrites the two call sites in the Lua handle pack/unpack routines.
        // Fail-closed: any signature, call-target or byte mismatch leaves the
        // engine untouched. Safe to call repeatedly.
        void InstallLuaHandleSyncIfPossible();
    }
}
