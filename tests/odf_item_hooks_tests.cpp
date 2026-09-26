// Lock arithmetic of the ODF item detours, driven against a fake engine.
//
// The engine resolves item bodies through UseItem / GetItemSize / UnlockItem
// and keeps a per-item lock count. The detours cache a processed copy per
// name and count holders themselves. Audit item P1-7
// (Docs/CODE_AUDIT_20260925.md): a cached UseItem hit returned the copy
// without calling the engine while every UnlockItem forwarded, so N holders
// left the engine at one lock and its count ended at 1-N as they released;
// the first release also freed the engine's bytes under every passthrough
// holder. These tests pin the invariant that the engine sees exactly one
// UseItem and one UnlockItem per holder, whichever bytes the holder was
// served, and that a record exists for every holder served while armed.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "odf_item_hooks.h"
#include "shim_log.h"
#include "shim_log_sink.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace BZROpenShim
{
// The detours read their switches through this (bzr_hooks.cpp). The seam
// fixes the switches directly, so the ini is never consulted here.
bool TryGetUserConfigBool(const char*, const char*, bool&)
{
    return false;
}
// The log sink asks for the game's logs directory; keep the test out of it.
std::string GetGameLogPath(const char* fileName)
{
    return fileName;
}
} // namespace BZROpenShim

namespace
{
using namespace BZROpenShim;

int g_failures = 0;

void Require(bool condition, const char* message)
{
    if (!condition)
    {
        std::fprintf(stderr, "odf_item_hooks_tests: FAIL %s\n", message);
        ++g_failures;
    }
}

std::string Lower(const char* name)
{
    std::string out(name ? name : "");
    for (char& c : out)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return out;
}

struct FakeItem
{
    std::string bytes;        // what the engine serves
    void* servePtr = nullptr; // overrides bytes.data() when set (unreadable-memory case)
    size_t serveSize = 0;     // overrides bytes.size() when servePtr is set
    int locks = 0;
    int minLocks = 0; // the lowest the count ever went
    int useCalls = 0;
    int unlockCalls = 0;
    bool vanished = false; // the engine answers null and takes no lock
};

// The engine's item table is case-insensitive, as the detours' key is.
std::map<std::string, FakeItem> g_engine;
int g_unknownUnlocks = 0;
std::vector<std::string> g_logLines;

void __cdecl CaptureLog(uint32_t, const char* component, const char* message)
{
    g_logLines.push_back(std::string(component ? component : "") + ": " +
                         (message ? message : ""));
}

void* __cdecl FakeUseItem(const char* name)
{
    if (!name)
        return nullptr;
    auto it = g_engine.find(Lower(name));
    if (it == g_engine.end() || it->second.vanished)
        return nullptr;
    ++it->second.useCalls;
    ++it->second.locks;
    return it->second.servePtr ? it->second.servePtr
                               : static_cast<void*>(it->second.bytes.data());
}

size_t __cdecl FakeGetItemSize(const char* name)
{
    if (!name)
        return 0;
    auto it = g_engine.find(Lower(name));
    if (it == g_engine.end())
        return 0;
    return it->second.servePtr ? it->second.serveSize : it->second.bytes.size();
}

void __cdecl FakeUnlockItem(const char* name)
{
    if (!name)
        return;
    auto it = g_engine.find(Lower(name));
    if (it == g_engine.end())
    {
        ++g_unknownUnlocks;
        return;
    }
    ++it->second.unlockCalls;
    --it->second.locks;
    it->second.minLocks = (std::min)(it->second.minLocks, it->second.locks);
}

void ResetEngine()
{
    g_engine.clear();
    g_unknownUnlocks = 0;
    g_logLines.clear();
    OdfItemHookTest::SetEngine(&FakeUseItem, &FakeGetItemSize, &FakeUnlockItem);
}

FakeItem& AddItem(const char* name, const char* bytes)
{
    FakeItem& item = g_engine[Lower(name)];
    item.bytes = bytes;
    return item;
}

bool LogContains(const char* needle)
{
    for (const auto& line : g_logLines)
        if (line.find(needle) != std::string::npos)
            return true;
    return false;
}

// A legacy section header the remap rewrites (MagnetClass -> MagnetMineClass,
// four bytes longer), so the served copy differs from the engine's bytes.
// odf_compat_tests covers the rewrite itself.
const char* const kLegacyMagnet =
    "[GameObjectClass]\r\nclassLabel = \"magnet\"\r\n\r\n[MagnetClass]\r\ntriggerDelay = 2.0\r\n";
const char* const kPlain = "[GameObjectClass]\r\nclassLabel = \"wingman\"\r\n";

void TestCachedHitStillLocksTheEngine()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    FakeItem& item = AddItem("magnet.odf", kLegacyMagnet);
    const void* stock = item.bytes.data();

    void* first = OdfUseItemDetour("magnet.odf");
    void* second = OdfUseItemDetour("magnet.odf");
    void* third = OdfUseItemDetour("MAGNET.ODF"); // the record key is case-folded

    Require(first != nullptr && first != stock, "first use serves a processed copy, not the engine's bytes");
    Require(second == first && third == first, "every holder gets the same copy");
    Require(item.useCalls == 3, "the engine saw one UseItem per holder (cached hits used to skip it)");
    Require(item.locks == 3, "the engine holds one lock per holder");
    Require(OdfItemHookTest::CachedRefcount("magnet.odf") == 3, "the record counts three holders");
    Require(OdfGetItemSizeDetour("magnet.odf") == std::strlen(kLegacyMagnet) + 4,
            "size reports the processed length");
    Require(std::memcmp(first, "[GameObjectClass]", 17) == 0, "the copy is the processed text");

    OdfUnlockItemDetour("magnet.odf");
    Require(item.locks == 2 && OdfItemHookTest::CachedRefcount("magnet.odf") == 2,
            "one release drops both counts by one");
    Require(std::memcmp(first, "[GameObjectClass]", 17) == 0, "the copy survives while holders remain");
    OdfUnlockItemDetour("magnet.odf");
    OdfUnlockItemDetour("magnet.odf");
    Require(item.unlockCalls == 3, "the engine saw one UnlockItem per holder");
    Require(item.locks == 0, "the engine's lock count returns to zero");
    Require(item.minLocks == 0, "the engine's lock count never went negative (it used to end at -2)");
    Require(OdfItemHookTest::CachedItemCount() == 0, "the last release drops the record");
}

void TestPassthroughRecordCountsEveryHolder()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(false, true, false); // unknown-section logging only: nothing rewrites
    FakeItem& item = AddItem("wingman.odf", kPlain);

    void* a = OdfUseItemDetour("wingman.odf");
    void* b = OdfUseItemDetour("wingman.odf");
    Require(a == item.bytes.data() && b == a, "an unchanged item is served from the engine's own bytes");
    Require(item.useCalls == 2 && item.locks == 2, "the engine locked once per holder");
    Require(OdfItemHookTest::CachedRefcount("wingman.odf") == 2, "the passthrough record counts holders");
    Require(OdfGetItemSizeDetour("wingman.odf") == item.bytes.size(), "size is the stock length");

    OdfUnlockItemDetour("wingman.odf");
    OdfUnlockItemDetour("wingman.odf");
    Require(item.locks == 0 && item.minLocks == 0 && item.unlockCalls == 2, "passthrough releases balance");
    Require(OdfItemHookTest::CachedItemCount() == 0, "passthrough record released");
}

void TestUnarmedForwardsEverything()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(false, false, false);
    FakeItem& item = AddItem("magnet.odf", kLegacyMagnet);

    void* a = OdfUseItemDetour("magnet.odf");
    void* b = OdfUseItemDetour("magnet.odf");
    Require(a == item.bytes.data() && b == a, "no feature armed: stock bytes");
    Require(item.useCalls == 2, "unarmed: the engine is called per use");
    Require(OdfItemHookTest::CachedItemCount() == 0, "unarmed: no record");
    Require(OdfGetItemSizeDetour("magnet.odf") == item.bytes.size(), "unarmed: stock size");

    OdfUnlockItemDetour("magnet.odf");
    OdfUnlockItemDetour("magnet.odf");
    Require(item.locks == 0 && item.minLocks == 0, "unarmed releases balance");
}

void TestNonOdfNamesBypassTheCache()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, true, true);
    FakeItem& item = AddItem("spritea.st", "not an odf");

    void* a = OdfUseItemDetour("spritea.st");
    Require(a == item.bytes.data(), "a sprite table passes through");
    Require(OdfItemHookTest::CachedItemCount() == 0, "no record for a non-odf");
    Require(OdfGetItemSizeDetour("spritea.st") == item.bytes.size(), "non-odf: stock size");

    OdfUnlockItemDetour("spritea.st");
    Require(item.locks == 0 && item.useCalls == 1 && item.unlockCalls == 1, "non-odf: one lock, one unlock");
}

void TestUnknownAndNullNames()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);

    Require(OdfUseItemDetour("missing.odf") == nullptr, "an item the engine lacks is null");
    Require(OdfItemHookTest::CachedItemCount() == 0, "a null answer leaves no record");
    OdfUnlockItemDetour("missing.odf");
    Require(g_unknownUnlocks == 1, "an unlock for an unknown name still reaches the engine");

    Require(OdfUseItemDetour(nullptr) == nullptr, "a null name is null");
    Require(OdfGetItemSizeDetour(nullptr) == 0, "a null name has size zero");
    OdfUnlockItemDetour(nullptr);
    Require(g_unknownUnlocks == 1, "a null name is not forwarded to UnlockItem");
}

void TestUnreadableBytesStillTakeARecord()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    void* guarded = VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
    Require(guarded != nullptr, "guard page allocated");
    FakeItem& item = AddItem("broken.odf", "");
    item.servePtr = guarded;
    item.serveSize = 64;

    void* a = OdfUseItemDetour("broken.odf");
    Require(a == guarded, "unreadable bytes are served as the engine gave them");
    Require(LogContains("unreadable item bytes"), "the unreadable copy is logged");
    Require(OdfItemHookTest::CachedRefcount("broken.odf") == 1, "a stock-served holder still has a record");

    void* b = OdfUseItemDetour("broken.odf");
    Require(b == guarded, "the second holder is served the same way");
    Require(OdfItemHookTest::CachedRefcount("broken.odf") == 2 && item.useCalls == 2,
            "the second holder is counted and locked");

    OdfUnlockItemDetour("broken.odf");
    OdfUnlockItemDetour("broken.odf");
    Require(item.locks == 0 && item.minLocks == 0, "stock-served releases balance");
    Require(OdfItemHookTest::CachedItemCount() == 0, "stock-served record released");
    VirtualFree(guarded, 0, MEM_RELEASE);
}

void TestEngineNullOnAHitIsMirrored()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    FakeItem& item = AddItem("magnet.odf", kLegacyMagnet);

    void* a = OdfUseItemDetour("magnet.odf");
    Require(a != nullptr, "first use succeeds");
    item.vanished = true;
    Require(OdfUseItemDetour("magnet.odf") == nullptr, "when the engine answers null so does the detour");
    Require(OdfItemHookTest::CachedRefcount("magnet.odf") == 1 && item.locks == 1,
            "a null answer takes no lock and adds no holder");
    item.vanished = false;

    OdfUnlockItemDetour("magnet.odf");
    Require(item.locks == 0 && OdfItemHookTest::CachedItemCount() == 0, "the one real holder releases");
}

} // namespace

int main()
{
    SetShimLogSink(&CaptureLog);

    TestCachedHitStillLocksTheEngine();
    TestPassthroughRecordCountsEveryHolder();
    TestUnarmedForwardsEverything();
    TestNonOdfNamesBypassTheCache();
    TestUnknownAndNullNames();
    TestUnreadableBytesStillTakeARecord();
    TestEngineNullOnAHitIsMirrored();

    OdfItemHookTest::ResetCache();
    if (g_failures == 0)
        std::printf("odf_item_hooks_tests: all checks passed\n");
    return g_failures == 0 ? 0 : 1;
}
