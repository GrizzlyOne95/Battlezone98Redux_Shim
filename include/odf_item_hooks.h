#pragma once

// odf_item_hooks.h
// BZR Open Shim - engine item-loader interposition for ODF compatibility.
//
// Installs JMP5 detours on the engine UseItem / GetItemSize / UnlockItem trio
// so ODF text can be normalized (legacy section remap, crash-value guards)
// before the ParameterDB parser sees it. All detours fail closed: any
// verification, allocation, or engine-call failure serves stock bytes.
//
// Evidence for the hook sites (GOG battlezone98redux.exe SHA256
// 8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413):
// FileData ctor 0x588E00 calls GetItemSize at 0x588E60 (result feeds malloc),
// UseItem at 0x588E72 (result is the parse source), UnlockItem at 0x5893B4.
// All three sites clean one pushed argument (add esp,4): __cdecl(const char*).
// Live bytes confirmed via Frida read on GOG 8D71F56C (ImageBase 0x400000,
// no ASLR) during a harness-gated windowed run on 2026-09-15: entry bytes
// match exactly, and the FileData filename hook installed cleanly (zero hits
// at menu idle, as expected - class loads happen on mission start). The sites
// stay require_unique with no fallback, so a non-matching build simply keeps
// stock behavior.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{

// Patcher-branch entry points. Each verifies the site prologue, builds the
// original-call trampoline from pristine bytes, and returns true when the
// generic JMP5 writer may redirect the site to the matching detour.
// Returns false (leaving stock behavior) on any failure.
bool OdfInstallUseItemHook(uint32_t siteAddress);
bool OdfInstallGetItemSizeHook(uint32_t siteAddress);
bool OdfInstallUnlockItemHook(uint32_t siteAddress);

// Detour targets (wired via FillJmp5Payloads by name).
void* __cdecl OdfUseItemDetour(const char* name);
size_t __cdecl OdfGetItemSizeDetour(const char* name);
void __cdecl OdfUnlockItemDetour(const char* name);

// Test seams. The engine trio, the [ODF] switches and the item cache are
// globals of the detour translation unit; a host test stands in for the
// engine here and reads the cache back. Nothing in the shim calls these.
namespace OdfItemHookTest
{
using UseItemFn = void*(__cdecl*)(const char* name);
using GetItemSizeFn = size_t(__cdecl*)(const char* name);
using UnlockItemFn = void(__cdecl*)(const char* name);

// Replaces the original-call trampolines and empties the cache.
void SetEngine(UseItemFn useItem, GetItemSizeFn getItemSize, UnlockItemFn unlockItem);
// Fixes the [ODF] switches without reading openshim.ini.
void SetOptions(bool remapLegacySections, bool logUnknownSections, bool guardCrashValues);
size_t CachedItemCount();
int CachedRefcount(const char* name); // -1 when the name has no record
void ResetCache();
} // namespace OdfItemHookTest

} // namespace BZROpenShim
