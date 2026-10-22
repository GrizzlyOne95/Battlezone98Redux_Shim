// map_folder_items.h
// BZR Open Shim - serve a lobby map's own .vxt/.des/.odf from its folder when
// the engine file index lacks them.
//
// The multiplayer waiting room's file index does not include a Workshop map
// pack's folder (buildMPResources 0x0076A240 mounts only some mods), so the
// vehicle loader 0x00766900 finds no <map>.vxt and falls back to netveh.odf.
// The mission mount indexes that folder later, so in-game spawns resolve.
//
// This store fills only that gap: while a folder is set, an item whose name
// has one of the three extensions, is absent from the engine index and exists
// in the folder is served from disk through the UseItem / GetItemSize /
// UnlockItem detours. A name the index has is never shadowed.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

namespace BZROpenShim::MapFolderItems
{

// True when the engine file index holds the name. Null disables serving.
using IndexHasFn = bool (*)(const char* name);
void SetIndexCheck(IndexHasFn fn);

// The folder gap items are served from; empty stops serving. Items a holder
// still has locked stay valid until their last Release.
void SetFolder(const std::filesystem::path& folder);
std::filesystem::path CurrentFolder();

// The first root holding both <base>.vxt and <base>.bzn, else empty. Roots
// are checked in order, each itself only (the map pack layout is flat).
std::filesystem::path FindMapFolder(const std::vector<std::filesystem::path>& roots,
                                    const std::string& base);

// True when the name would be served now.
bool CanServe(const char* name);

// Detour hooks. Each returns false when the name is not ours, and the detour
// then runs its stock path. Acquire hands out a buffer valid until the
// matching Release; Size works without a prior Acquire, as the engine asks.
bool Acquire(const char* name, void*& data);
bool Size(const char* name, std::size_t& size);
bool Release(const char* name);

// Test seams.
std::size_t CachedItemCount();
int Refcount(const char* name); // -1 when the name has no record
void ResetForTesting();

} // namespace BZROpenShim::MapFolderItems
