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
#include "odf_item_prologue.h"
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

// The prologue every site must still hold, and how much of it the trampoline
// has to relocate. The detour overwrites five bytes but the fifth lands inside
// `mov eax,[ebp+8]`, so the trampoline must replay six - see
// include/odf_item_prologue.h for why relocating five breaks the return jump.
constexpr size_t kMaxPrologueBytes = OdfPrologue::kExpectedPrologueSize;
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
    uint8_t prologue[kMaxPrologueBytes] = {};
    if (!SafeReadEngineBytes(reinterpret_cast<void*>(site), prologue, kMaxPrologueBytes))
    {
        LogShimA(LogLevel::Error, "odf", "%s: unreadable site 0x%08X; hook skipped", hookName, site);
        return nullptr;
    }

    // How many bytes end on an instruction boundary at or after the detour.
    // Relocating fewer would split `mov eax,[ebp+8]` and leave the trampoline
    // swallowing its own return jump.
    const size_t relocate = OdfPrologue::TrampolineCopyLength(prologue, kMaxPrologueBytes);
    if (relocate == 0)
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
    std::memcpy(tramp, prologue, relocate);
    tramp[relocate] = 0xE9; // jmp site+relocate
    const int32_t rel = static_cast<int32_t>(site + relocate) -
                        static_cast<int32_t>(reinterpret_cast<uintptr_t>(tramp) + relocate + 5);
    std::memcpy(tramp + relocate + 1, &rel, sizeof(rel));
    FlushInstructionCache(GetCurrentProcess(), tramp, relocate + 5);
    LogShimA(LogLevel::Info, "odf", "%s: trampoline relocated %zu prologue bytes, resumes at 0x%08X",
              hookName, relocate, static_cast<unsigned>(site + relocate));
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
    // Without a trampoline there is no such thing as failing closed here: the
    // engine's loader has already been redirected, so returning null does not
    // mean "stock behaviour", it means EVERY item in the game fails to load -
    // sprite tables and fonts included. The install is supposed to prevent the
    // detour ever being written in that state; if we are somehow reached
    // anyway, say so once rather than silently emptying the asset system.
    if (!g_OriginalUseItem)
    {
        static bool warned = false;
        if (!warned)
        {
            warned = true;
            LogShimA(LogLevel::Error, "odf",
                      "UseItem detour reached with no original-call trampoline; every item load "
                      "will fail. This is an install-order bug, not a content problem.");
        }
        return nullptr;
    }

    if (!name || !OdfCompat::IsOdfFileName(name) || !OdfFeaturesArmed())
    {
        bool faulted = false;
        void* stock = SafeCallUseItem(name, faulted);
        return faulted ? nullptr : stock;
    }

    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    const std::string key = LowerName(name);

    // Lock arithmetic. Every UseItem the engine would have seen still reaches
    // it, cached hit or not, so its own lock count rises once per holder and
    // the unconditional forward in OdfUnlockItemDetour stays one-for-one.
    // Serving a cached copy without this call left the engine holding one
    // lock for N holders: the first UnlockItem released the item under the
    // other N-1 (a dangling originalPtr for a passthrough record) and the
    // remaining forwards drove the engine's count below zero.
    bool faulted = false;
    void* originalPtr = SafeCallUseItem(name, faulted);
    if (faulted)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): engine call faulted; serving null", name);
        return nullptr;
    }
    if (!originalPtr)
        return nullptr; // the engine has no such item and took no lock; nothing to count

    auto it = g_OdfItems.find(key);
    if (it != g_OdfItems.end() && it->second.refcount > 0)
    {
        if (originalPtr != it->second.originalPtr)
        {
            // Not expected while the engine holds a lock on our behalf; say
            // so rather than keep serving a pointer the engine has dropped.
            LogShimA(LogLevel::Warn, "odf",
                      "UseItem(%s): engine moved a locked item %p -> %p; record refreshed", name,
                      it->second.originalPtr, originalPtr);
            it->second.originalPtr = originalPtr;
        }
        ++it->second.refcount;
        static bool s_firstHitLogged = false;
        if (!s_firstHitLogged)
        {
            // One line per process, so a live run shows the shared-record
            // path ran at all; the lock arithmetic itself is pinned by
            // tests/odf_item_hooks_tests.cpp.
            s_firstHitLogged = true;
            LogShimA(LogLevel::Info, "odf",
                      "UseItem(%s): first repeat use served from the record (holders=%d)", name,
                      it->second.refcount);
        }
        return it->second.changed ? it->second.patchedBuf : it->second.originalPtr;
    }

    // First holder. The record exists from here on whichever bytes end up
    // served, so every later UnlockItem for this name finds it and the
    // refcount counts every holder. A stock-served holder with no record
    // would otherwise decrement a record a later holder created and free
    // that holder's patched copy early.
    ItemRecord rec;
    rec.originalPtr = originalPtr;
    rec.refcount = 1;

    size_t originalSize = 0;
    if (g_OriginalGetItemSize)
        originalSize = SafeCallGetItemSize(name, faulted);
    if (faulted)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): size query faulted; serving stock", name);
        g_OdfItems[key] = rec;
        return originalPtr;
    }
    rec.originalSize = originalSize;
    if (originalSize == 0 || originalSize > kMaxPatchedBytes)
    {
        g_OdfItems[key] = rec;
        return originalPtr;
    }
    void* copy = SafeCopyEngineBytes(originalPtr, originalSize);
    if (!copy)
    {
        LogShimA(LogLevel::Error, "odf", "UseItem(%s): unreadable item bytes; serving stock", name);
        g_OdfItems[key] = rec;
        return originalPtr;
    }
    std::string bytes(static_cast<const char*>(copy), originalSize);
    std::free(copy);

    OdfCompat::ProcessResult result =
        OdfCompat::ProcessOdfText(name, bytes.data(), bytes.size(), g_OdfOptions);
    LogOdfEvents(result);
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
    // Same reasoning as UseItem: with no trampoline, 0 is not a safe default,
    // it is "every item is empty".
    if (!g_OriginalGetItemSize)
    {
        static bool warned = false;
        if (!warned)
        {
            warned = true;
            LogShimA(LogLevel::Error, "odf",
                      "GetItemSize detour reached with no original-call trampoline; every item "
                      "will report size 0. This is an install-order bug.");
        }
        return 0;
    }
    if (!name)
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

namespace OdfItemHookTest
{

void ResetCache()
{
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    for (auto& entry : g_OdfItems)
        std::free(entry.second.patchedBuf);
    g_OdfItems.clear();
    g_LoggedUnknowns.clear();
}

void SetEngine(UseItemFn useItem, GetItemSizeFn getItemSize, UnlockItemFn unlockItem)
{
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    ResetCache();
    g_OriginalUseItem = useItem;
    g_OriginalGetItemSize = getItemSize;
    g_OriginalUnlockItem = unlockItem;
}

void SetOptions(bool remapLegacySections, bool logUnknownSections, bool guardCrashValues)
{
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    g_OdfConfigRead = true; // the ini is not consulted after this
    g_OdfOptions.remapLegacySections = remapLegacySections;
    g_OdfOptions.logUnknownSections = logUnknownSections;
    g_OdfOptions.guardCrashValues = guardCrashValues;
}

size_t CachedItemCount()
{
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    return g_OdfItems.size();
}

int CachedRefcount(const char* name)
{
    std::lock_guard<std::recursive_mutex> lock(g_OdfMutex);
    auto it = g_OdfItems.find(LowerName(name));
    return it == g_OdfItems.end() ? -1 : it->second.refcount;
}

} // namespace OdfItemHookTest

} // namespace BZROpenShim
