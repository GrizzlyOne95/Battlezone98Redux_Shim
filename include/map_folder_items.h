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
// UnlockItem detours. A name the index has is never shadowed, with the one
// waiting-room exception described under "<stem>.mpdes" below.
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

// ---------------------------------------------------------------------
// MP-only map description: <stem>.mpdes
//
// Stock reads "<stem>.des" for the single-player briefing (FUN_004889C0) and,
// through FUN_0076EB90, for the description pane of the multiplayer waiting
// room (FUN_007A3F80), instant action (FUN_00789910) and mod select
// (FUN_00788080). A pack whose one .bzn serves both a campaign and a co-op
// map can put the multiplayer text in <stem>.mpdes beside its <stem>.bzn.
//
// Only between BeginMpDescription and EndMpDescription, which wrap the
// waiting room's one FUN_0076EB90 call, is "<stem>.des" served from
// <folder>/<stem>.mpdes, and only when the resolver names a folder holding
// it. That check comes before the gap rule above and before the engine, so
// it applies whether or not the index has the stock .des. Every other .des
// read, and every miss, stays stock.
using MpDescriptionFolderFn = std::filesystem::path (*)(const std::string& base);
void SetMpDescriptionResolver(MpDescriptionFolderFn fn);

// The first root holding both <base>.mpdes and <base>.bzn, else empty.
std::filesystem::path FindMpDescriptionFolder(const std::vector<std::filesystem::path>& roots,
                                              const std::string& base);

// Brackets one waiting-room description load. Nesting counts; records
// nobody holds are dropped when the outermost one ends.
void BeginMpDescription();
void EndMpDescription();

// Test seams.
std::size_t CachedItemCount();
std::size_t MpDescriptionItemCount();
int Refcount(const char* name); // -1 when the name has no record
void ResetForTesting();

} // namespace BZROpenShim::MapFolderItems
