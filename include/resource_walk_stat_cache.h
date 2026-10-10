// resource_walk_stat_cache.h
// BZR Open Shim - answer the resource-location walk's stat calls from the
// directory enumeration it just did
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Detours buildSingleIAResource (engine address "BuildSingleIAResource")
    // to open a per-thread scope, and patches the game executable's imports of
    // FindFirstFileW / FindNextFileW / FindClose / GetFileAttributesW /
    // GetFileAttributesExW. Inside the scope, attributes returned by directory
    // enumeration are remembered and later stat calls for exactly those paths
    // are answered from them; the record is discarded when the scope ends.
    // Outside the scope every call passes straight through.
    // Idempotent; fails closed if the engine address does not verify.
    // OPENSHIM_DISABLE_RESOURCE_WALK_STAT_CACHE=1 keeps it off.
    void InstallResourceWalkStatCacheIfPossible();
}
