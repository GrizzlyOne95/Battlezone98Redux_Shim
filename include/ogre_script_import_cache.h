// ogre_script_import_cache.h
// BZR Open Shim - cache of imported Ogre script parses within one parse wave
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Installs the import cache detours on OgreMain.dll's
    // ScriptCompiler::loadImportPath and ScriptParser::parse. Idempotent and
    // safe to call before OgreMain.dll is loaded (it then does nothing and a
    // later retry installs it). Fails closed: a missing export, an unexpected
    // prologue or a SharedPtr layout that does not match leaves Ogre untouched.
    // OPENSHIM_DISABLE_SCRIPT_IMPORT_CACHE=1 keeps it off.
    void InstallOgreScriptImportCacheIfPossible();
}
