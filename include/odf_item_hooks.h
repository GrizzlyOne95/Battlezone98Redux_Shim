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
// Live [RESOLVE] confirmation via a harness run is still pending; the sites
// are require_unique with no fallback and re-verify their prologues at
// install time, so a non-matching build simply keeps stock behavior.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

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

} // namespace BZROpenShim
