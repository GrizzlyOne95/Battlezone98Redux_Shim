// odf_item_hooks.cpp
// BZR Open Shim - UseItem/GetItemSize/UnlockItem detours for ODF text
// normalization (legacy section remap + crash-value guards + unknown-section
// logging). See include/odf_item_hooks.h for hook-site evidence.
//
// Design: the engine resolves ODF bodies through UseItem(name) /
// GetItemSize(name) / UnlockItem(name). When any [ODF] feature is enabled and
// the item is an .odf file, UseItem serves a patched copy (same lifetime
// rules as the original: valid until the matching UnlockItem), GetItemSize
// reports the patched length, and UnlockItem releases the copy. Everything
// else passes through untouched. Any failure serves stock bytes.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "odf_item_hooks.h"

#include "bzr_options_ui.h"
#include "odf_compat.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cctype>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace BZROpenShim
{
namespace
{

using OdfUseItemFn = void*(__cdecl*)(const char* name);
using OdfGetItemSizeFn = size_t(__cdecl*)(const char* name);
using OdfUnlockItemFn = void(__cdecl*)(const char* name);

OdfUseItemFn g_OriginalUseItem = nullptr;
OdfGetItemSizeFn g_OriginalGetItemSize = nullptr;
OdfUnlockItemFn g_OriginalUnlockItem = nullptr;

// First five bytes every site must still hold (55 8B EC 8B 45:
// push ebp / mov ebp,esp / mov eax,[ebp+8]). Anything else aborts the install.
constexpr uint8_t kPrologue[5] = {0x55, 0x8B, 0xEC, 0x8B, 0x45};
constexpr size_t kDetourSize = 5;
constexpr size_t kMaxPatchedBytes = 8u * 1024u * 1024u; // ODFs are kilobytes

struct ItemRecord
{
    void* originalPtr = nullptr;
    size_t originalSize = 0;
    void* patchedBuf = nullptr; // malloc-owned; null when passthrough
    size_t patchedSize = 0;
    int refcount = 0;
    bool changed = false;
};

std::recursive_mutex g_OdfMutex;
std::unordered_map<std::string, ItemRecord> g_OdfItems; // key: lowercase name
std::unordered_set<std::string> g_LoggedUnknowns; // (file + section), to avoid log spam
bool g_OdfConfigRead = false;
OdfCompat::Options g_OdfOptions;

void ReadOdfConfig()
{
    if (g_OdfConfigRead)
        return;
    g_OdfConfigRead = true;
    bool v = false;
    if (TryGetUserConfigBool("ODF", "LegacySectionRemap", v))
        g_OdfOptions.remapLegacySections = v;
    if (TryGetUserConfigBool("ODF", "LogUnknownOdfSections", v))
        g_OdfOptions.logUnknownSections = v;
    if (TryGetUserConfigBool("ODF", "CrashValueGuards", v))
        g_OdfOptions.guardCrashValues = v;
}

bool OdfFeaturesArmed()
{
    ReadOdfConfig();
    return g_OdfOptions.remapLegacySections || g_OdfOptions.logUnknownSections ||
           g_OdfOptions.guardCrashValues;
}

std::string LowerName(const char* name)
{
    std::string out(name ? name : "");
    for (char& c : out)
    {
        if (c >= 'A' && c <= 'Z')
            c = static_cast<char>(c + ('a' - 'A'));
    }
    return out;
}

// SEH-guarded primitives. Each is POD-only so /EHsc stays happy; callers own
// all C++ objects and stay outside __try (C2712).
bool SafeReadEngineBytes(const void* src, void* dst, size_t n)
{
    bool ok = false;
    __try
    {
        std::memcpy(dst, src, n);
        ok = true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        ok = false;
    }
    return ok;
}

void* SafeCallUseItem(const char* name, bool& faulted)
{
    void* result = nullptr;
    faulted = false;
    __try
    {
        result = g_OriginalUseItem(name);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        faulted = true;
    }
    return result;
}

size_t SafeCallGetItemSize(const char* name, bool& faulted)
{
    size_t result = 0;
    faulted = false;
    __try
    {
        result = g_OriginalGetItemSize(name);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        faulted = true;
    }
    return result;
}

void SafeCallUnlockItem(const char* name, bool& faulted)
{
    faulted = false;
    __try
    {
        g_OriginalUnlockItem(name);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        faulted = true;
    }
}

void* SafeCopyEngineBytes(const void* src, size_t n)
{
    void* buf = std::malloc(n ? n : 1);
    if (!buf)
        return nullptr;
    if (!SafeReadEngineBytes(src, buf, n))
    {
        std::free(buf);
        return nullptr;
    }
    return buf;
}

void* BuildTrampoline(uint32_t site, const char* hookName)
{
    uint8_t prologue[kDetourSize] = {};
    if (!SafeReadEngineBytes(reinterpret_cast<void*>(site), prologue, kDetourSize))
    {
        LogShimA(LogLevel::Error, "odf", "%s: unreadable site 0x%08X; hook skipped", hookName, site);
        return nullptr;
    }
    if (std::memcmp(prologue, kPrologue, kDetourSize) != 0)
    {
        LogShimA(LogLevel::Error, "odf", "%s: prologue mismatch at 0x%08X; hook skipped", hookName,
                  site);
        return nullptr;
    }
    uint8_t* tramp = static_cast<uint8_t*>(
        VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    if (!tramp)
    {
        LogShimA(LogLevel::Error, "odf", "%s: trampoline alloc failed; hook skipped", hookName);
        return nullptr;
    }
    std::memcpy(tramp, prologue, kDetourSize);
    tramp[kDetourSize] = 0xE9; // jmp site+5
    const int32_t rel = static_cast<int32_t>(site + kDetourSize) -
                        static_cast<int32_t>(reinterpret_cast<uintptr_t>(tramp) + kDetourSize + 5);
    std::memcpy(tramp + kDetourSize + 1, &rel, sizeof(rel));
    FlushInstructionCache(GetCurrentProcess(), tramp, kDetourSize + 5);
    return tramp;
}

bool g_UseItemHooked = false;
bool g_GetItemSizeHooked = false;
bool g_UnlockItemHooked = false;

bool InstallOne(uint32_t site, const char* hookName, void** originalSlot)
{
    if (site == 0)
    {
        LogShimA(LogLevel::Error, "odf", "%s: unresolved site; hook skipped", hookName);
        return false;
    }
    void* tramp = BuildTrampoline(site, hookName);
    if (!tramp)
        return false;
    *originalSlot = tramp;
    LogShimA(LogLevel::Info, "odf", "%s: trampoline ready for site 0x%08X", hookName, site);
    return true;
}

void LogOdfEvents(const OdfCompat::ProcessResult& result)
{
    for (const auto& e : result.remaps)
        LogShimA(LogLevel::Warn, "odf", "remap %s:%d [%s] -> [%s]", e.file.c_str(), e.line,
                  e.name.c_str(), e.mappedTo.c_str());
    for (const auto& e : result.unknowns)
    {
        const std::string key = e.file + '\x01' + e.name;
        if (g_LoggedUnknowns.insert(key).second)
            LogShimA(LogLevel::Warn, "odf", "unknown section %s:%d [%s]", e.file.c_str(), e.line,
                      e.name.c_str());
    }
    for (const auto& e : result.guards)
        LogShimA(LogLevel::Error, "odf", "guard %s:%d [%s] %s = %s (%s)", e.file.c_str(), e.line,
                  e.section.c_str(), e.key.c_str(), e.value.c_str(), e.action.c_str());
}

} // namespace

bool OdfInstallUseItemHook(uint32_t siteAddress)
{
    if (g_UseItemHooked)
        return true;
    if (!InstallOne(siteAddress, "ODF UseItem Hook", reinterpret_cast<void**>(&g_OriginalUseItem)))
        return false;
    g_UseItemHooked = true;
    return true;
}

bool OdfInstallGetItemSizeHook(uint32_t siteAddress)
{
    if (g_GetItemSizeHooked)
        return true;
    if (!InstallOne(siteAddress, "ODF GetItemSize Hook",
                     reinterpret_cast<void**>(&g_OriginalGetItemSize)))
        return false;
    g_GetItemSizeHooked = true;
    return true;
}

bool OdfInstallUnlockItemHook(uint32_t siteAddress)
{
    if (g_UnlockItemHooked)
        return true;
    if (!InstallOne(siteAddress, "ODF UnlockItem Hook",
                     reinterpret_cast<void**>(&g_OriginalUnlockItem)))
        return false;
    g_UnlockItemHooked = true;
    return true;
}

void* __cdecl OdfUseItemDetour(const char* name)
{
    if (!name || !OdfCompat::IsOdfFileName(name) || !OdfFeaturesArmed() || !g_OriginalUseItem)
        return g_OriginalUseItem ? g_OriginalUseItem(name) : nullptr;

    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    const std::string key = LowerName(name);
    auto it = g_OdfItems.find(key);
    if (it != g_OdfItems.end() && it->second.refcount > 0)
    {
        ++it->second.refcount;
        return it->second.changed ? it->second.patchedBuf : it->second.originalPtr;
    }

    void* originalPtr = nullptr;
    size_t originalSize = 0;
    bool faulted = false;
    originalPtr = SafeCallUseItem(name, faulted);
    if (faulted)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): engine call faulted; serving null", name);
        return nullptr;
    }
    if (originalPtr && g_OriginalGetItemSize)
        originalSize = SafeCallGetItemSize(name, faulted);
    if (faulted)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): size query faulted; serving stock", name);
        return originalPtr;
    }
    if (!originalPtr || originalSize == 0 || originalSize > kMaxPatchedBytes)
        return originalPtr;

    void* copy = SafeCopyEngineBytes(originalPtr, originalSize);
    if (!copy)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): unreadable item bytes; serving stock", name);
        return originalPtr;
    }
    std::string bytes(static_cast<const char*>(copy), originalSize);
    std::free(copy);

    OdfCompat::ProcessResult result =
        OdfCompat::ProcessOdfText(name, bytes.data(), bytes.size(), g_OdfOptions);
    LogOdfEvents(result);
    ItemRecord rec;
    rec.originalPtr = originalPtr;
    rec.originalSize = originalSize;
    rec.refcount = 1;
    if (!result.changed)
    {
        g_OdfItems[key] = rec;
        return originalPtr;
    }
    void* patched = std::malloc(result.text.size());
    if (!patched)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): out of memory; serving stock", name);
        g_OdfItems[key] = rec;
        return originalPtr;
    }
    std::memcpy(patched, result.text.data(), result.text.size());
    rec.patchedBuf = patched;
    rec.patchedSize = result.text.size();
    rec.changed = true;
    g_OdfItems[key] = rec;
    return patched;
}

size_t __cdecl OdfGetItemSizeDetour(const char* name)
{
    if (!name || !g_OriginalGetItemSize)
        return 0;
    bool faulted = false;
    const size_t stock = SafeCallGetItemSize(name, faulted);
    if (faulted)
        return 0;
    if (!OdfCompat::IsOdfFileName(name) || !OdfFeaturesArmed())
        return stock;
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    auto it = g_OdfItems.find(LowerName(name));
    if (it != g_OdfItems.end() && it->second.refcount > 0 && it->second.changed)
        return it->second.patchedSize;
    return stock;
}

void __cdecl OdfUnlockItemDetour(const char* name)
{
    if (g_OriginalUnlockItem && name)
    {
        bool faulted = false;
        SafeCallUnlockItem(name, faulted);
        if (faulted)
            LogShimA(LogLevel::Error, "odf", "UnlockItem(%s): engine call faulted", name);
    }
    if (!name)
        return;
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    auto it = g_OdfItems.find(LowerName(name));
    if (it == g_OdfItems.end() || it->second.refcount <= 0)
        return;
    if (--it->second.refcount == 0)
    {
        std::free(it->second.patchedBuf);
        g_OdfItems.erase(it);
    }
}

} // namespace BZROpenShim
