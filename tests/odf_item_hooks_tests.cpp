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

#include "map_folder_items.h"
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
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

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

    Check(first != nullptr && first != stock, "first use serves a processed copy, not the engine's bytes");
    Check(second == first && third == first, "every holder gets the same copy");
    Check(item.useCalls == 3, "the engine saw one UseItem per holder (cached hits used to skip it)");
    Check(item.locks == 3, "the engine holds one lock per holder");
    Check(OdfItemHookTest::CachedRefcount("magnet.odf") == 3, "the record counts three holders");
    Check(OdfGetItemSizeDetour("magnet.odf") == std::strlen(kLegacyMagnet) + 4,
          "size reports the processed length");
    Check(std::memcmp(first, "[GameObjectClass]", 17) == 0, "the copy is the processed text");

    OdfUnlockItemDetour("magnet.odf");
    Check(item.locks == 2 && OdfItemHookTest::CachedRefcount("magnet.odf") == 2,
          "one release drops both counts by one");
    Check(std::memcmp(first, "[GameObjectClass]", 17) == 0, "the copy survives while holders remain");
    OdfUnlockItemDetour("magnet.odf");
    OdfUnlockItemDetour("magnet.odf");
    Check(item.unlockCalls == 3, "the engine saw one UnlockItem per holder");
    Check(item.locks == 0, "the engine's lock count returns to zero");
    Check(item.minLocks == 0, "the engine's lock count never went negative (it used to end at -2)");
    Check(OdfItemHookTest::CachedItemCount() == 0, "the last release drops the record");
}

void TestPassthroughRecordCountsEveryHolder()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(false, true, false); // unknown-section logging only: nothing rewrites
    FakeItem& item = AddItem("wingman.odf", kPlain);

    void* a = OdfUseItemDetour("wingman.odf");
    void* b = OdfUseItemDetour("wingman.odf");
    Check(a == item.bytes.data() && b == a, "an unchanged item is served from the engine's own bytes");
    Check(item.useCalls == 2 && item.locks == 2, "the engine locked once per holder");
    Check(OdfItemHookTest::CachedRefcount("wingman.odf") == 2, "the passthrough record counts holders");
    Check(OdfGetItemSizeDetour("wingman.odf") == item.bytes.size(), "size is the stock length");

    OdfUnlockItemDetour("wingman.odf");
    OdfUnlockItemDetour("wingman.odf");
    Check(item.locks == 0 && item.minLocks == 0 && item.unlockCalls == 2, "passthrough releases balance");
    Check(OdfItemHookTest::CachedItemCount() == 0, "passthrough record released");
}

void TestUnarmedForwardsEverything()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(false, false, false);
    FakeItem& item = AddItem("magnet.odf", kLegacyMagnet);

    void* a = OdfUseItemDetour("magnet.odf");
    void* b = OdfUseItemDetour("magnet.odf");
    Check(a == item.bytes.data() && b == a, "no feature armed: stock bytes");
    Check(item.useCalls == 2, "unarmed: the engine is called per use");
    Check(OdfItemHookTest::CachedItemCount() == 0, "unarmed: no record");
    Check(OdfGetItemSizeDetour("magnet.odf") == item.bytes.size(), "unarmed: stock size");

    OdfUnlockItemDetour("magnet.odf");
    OdfUnlockItemDetour("magnet.odf");
    Check(item.locks == 0 && item.minLocks == 0, "unarmed releases balance");
}

void TestNonOdfNamesBypassTheCache()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, true, true);
    FakeItem& item = AddItem("spritea.st", "not an odf");

    void* a = OdfUseItemDetour("spritea.st");
    Check(a == item.bytes.data(), "a sprite table passes through");
    Check(OdfItemHookTest::CachedItemCount() == 0, "no record for a non-odf");
    Check(OdfGetItemSizeDetour("spritea.st") == item.bytes.size(), "non-odf: stock size");

    OdfUnlockItemDetour("spritea.st");
    Check(item.locks == 0 && item.useCalls == 1 && item.unlockCalls == 1, "non-odf: one lock, one unlock");
}

void TestUnknownAndNullNames()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);

    Check(OdfUseItemDetour("missing.odf") == nullptr, "an item the engine lacks is null");
    Check(OdfItemHookTest::CachedItemCount() == 0, "a null answer leaves no record");
    OdfUnlockItemDetour("missing.odf");
    Check(g_unknownUnlocks == 1, "an unlock for an unknown name still reaches the engine");

    Check(OdfUseItemDetour(nullptr) == nullptr, "a null name is null");
    Check(OdfGetItemSizeDetour(nullptr) == 0, "a null name has size zero");
    OdfUnlockItemDetour(nullptr);
    Check(g_unknownUnlocks == 1, "a null name is not forwarded to UnlockItem");
}

void TestUnreadableBytesStillTakeARecord()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    void* guarded = VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
    Check(guarded != nullptr, "guard page allocated");
    FakeItem& item = AddItem("broken.odf", "");
    item.servePtr = guarded;
    item.serveSize = 64;

    void* a = OdfUseItemDetour("broken.odf");
    Check(a == guarded, "unreadable bytes are served as the engine gave them");
    Check(LogContains("unreadable item bytes"), "the unreadable copy is logged");
    Check(OdfItemHookTest::CachedRefcount("broken.odf") == 1, "a stock-served holder still has a record");

    void* b = OdfUseItemDetour("broken.odf");
    Check(b == guarded, "the second holder is served the same way");
    Check(OdfItemHookTest::CachedRefcount("broken.odf") == 2 && item.useCalls == 2,
          "the second holder is counted and locked");

    OdfUnlockItemDetour("broken.odf");
    OdfUnlockItemDetour("broken.odf");
    Check(item.locks == 0 && item.minLocks == 0, "stock-served releases balance");
    Check(OdfItemHookTest::CachedItemCount() == 0, "stock-served record released");
    VirtualFree(guarded, 0, MEM_RELEASE);
}

void TestEngineNullOnAHitIsMirrored()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    FakeItem& item = AddItem("magnet.odf", kLegacyMagnet);

    void* a = OdfUseItemDetour("magnet.odf");
    Check(a != nullptr, "first use succeeds");
    item.vanished = true;
    Check(OdfUseItemDetour("magnet.odf") == nullptr, "when the engine answers null so does the detour");
    Check(OdfItemHookTest::CachedRefcount("magnet.odf") == 1 && item.locks == 1,
          "a null answer takes no lock and adds no holder");
    item.vanished = false;

    OdfUnlockItemDetour("magnet.odf");
    Check(item.locks == 0 && OdfItemHookTest::CachedItemCount() == 0, "the one real holder releases");
}

void TestOwnedOdfRead()
{
    ResetEngine();
    OdfItemHookTest::SetOptions(false, false, false);
    FakeItem& item = AddItem("avtank.odf", "[HoverCraft]\nflameColor=green\n");
    std::string text;
    Check(OdfReadItemText("avtank.odf", text) && text == item.bytes,
          "ODF read uses the engine-selected item even with compatibility options disabled");
    Check(item.locks == 0 && item.useCalls == 1 && item.unlockCalls == 1,
          "owned read releases its engine lock before returning");
    item.bytes = "replaced";
    Check(text == "[HoverCraft]\nflameColor=green\n", "result owns its bytes after engine release");
    Check(!OdfReadItemText("missing.odf", text) && text.empty() && g_unknownUnlocks == 0,
          "missing items return empty without an unmatched unlock");
    Check(!OdfReadItemText(nullptr, text) && !OdfReadItemText("bad.mesh", text),
          "only ODF names accepted");

    void* guarded = VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
    Check(guarded != nullptr, "guard page allocated for owned reader");
    item.servePtr = guarded;
    item.serveSize = 64;
    Check(!OdfReadItemText("avtank.odf", text) && text.empty() && item.locks == 0,
          "unreadable bytes fail closed and release the lock");
    item.serveSize = 9u * 1024u * 1024u;
    Check(!OdfReadItemText("avtank.odf", text) && item.locks == 0,
          "oversized reads fail closed and release the lock");
    VirtualFree(guarded, 0, MEM_RELEASE);

    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    FakeItem& shared = AddItem("magnet.odf", kLegacyMagnet);
    void* holder = OdfUseItemDetour("magnet.odf");
    Check(OdfReadItemText("magnet.odf", text) && text == kLegacyMagnet,
          "owned reader sees original text alongside compatibility rewrite holders");
    Check(shared.locks == 1 && OdfItemHookTest::CachedRefcount("magnet.odf") == 1 && holder,
          "owned reader does not disturb another holder's record or engine lock");
    OdfUnlockItemDetour("magnet.odf");
    Check(shared.locks == 0, "remaining holder releases normally");
    OdfItemHookTest::SetEngine(nullptr, nullptr, nullptr);
    Check(!OdfReadItemText("magnet.odf", text) && text.empty(), "unavailable loader fails closed");
}

// The waiting room's file index lacks a map pack's folder, so the store
// serves that folder's own .vxt/.des/.odf through the detours, and only names
// the index does not have.
bool __cdecl FakeIndexHas(const char* name)
{
    return name && g_engine.count(Lower(name)) != 0;
}

void WriteFile(const std::filesystem::path& p, const char* text)
{
    std::ofstream out(p, std::ios::binary);
    out << text;
}

void TestMapFolderItemsServeOnlyIndexGaps()
{
    namespace fs = std::filesystem;
    const fs::path root = fs::temp_directory_path() / "openshim_map_folder_items_test";
    std::error_code ec;
    fs::remove_all(root, ec);
    const fs::path pack = root / "3686673790";
    const fs::path other = root / "other";
    fs::create_directories(pack);
    fs::create_directories(other);
    const char* kVxt = "avobserv avobserv.des\tx\tNSDF\r\n";
    WriteFile(pack / "uarracda.vxt", kVxt);
    WriteFile(pack / "uarracda.bzn", "bzn");
    WriteFile(pack / "avobserv.des", "NSDF Observer");
    WriteFile(pack / "avtank.odf", "[GameObjectClass]\r\n");
    WriteFile(pack / "uarracda.lua", "-- not served");
    WriteFile(other / "uarracda.vxt", "no bzn beside it");

    Check(MapFolderItems::FindMapFolder({ other, pack }, "uarracda") == pack,
          "the map folder needs both <map>.vxt and <map>.bzn");
    Check(MapFolderItems::FindMapFolder({ other }, "uarracda").empty(), "a lone .vxt is no map folder");
    Check(MapFolderItems::FindMapFolder({ pack }, "..\\uarracda").empty(), "a path is never a map name");

    ResetEngine();
    OdfItemHookTest::SetOptions(true, false, false);
    MapFolderItems::ResetForTesting();
    FakeItem& stockTank = AddItem("avtank.odf", "[GameObjectClass]\r\nstock\r\n");

    MapFolderItems::SetFolder(pack);
    Check(!MapFolderItems::CanServe("uarracda.vxt"), "no index probe means nothing is served");
    MapFolderItems::SetIndexCheck(&FakeIndexHas);

    Check(MapFolderItems::CanServe("uarracda.vxt"), "an index gap in the map folder is servable");
    Check(!MapFolderItems::CanServe("avtank.odf"), "a name the index has is never shadowed");
    Check(!MapFolderItems::CanServe("uarracda.lua"), "only .vxt/.des/.odf are served");
    Check(!MapFolderItems::CanServe("missing.des"), "a file the folder lacks is not servable");

    // The loader asks the size before UseItem for each .des.
    Check(OdfGetItemSizeDetour("avobserv.des") == std::strlen("NSDF Observer"),
          "GetItemSize reports the folder file's size");
    void* vxt = OdfUseItemDetour("UARRACDA.VXT");
    Check(vxt && std::strcmp(static_cast<const char*>(vxt), kVxt) == 0,
          "UseItem serves the folder bytes, NUL-terminated, case-insensitively");
    void* again = OdfUseItemDetour("uarracda.vxt");
    Check(again == vxt && MapFolderItems::Refcount("uarracda.vxt") == 2, "a second holder shares the copy");

    void* tank = OdfUseItemDetour("avtank.odf");
    Check(tank && stockTank.useCalls == 1, "an indexed name still reaches the engine");
    OdfUnlockItemDetour("avtank.odf");
    Check(stockTank.locks == 0, "the engine releases its own item");

    // Switching maps keeps a held copy valid until its last Release.
    MapFolderItems::SetFolder({});
    Check(!MapFolderItems::CanServe("avobserv.des"), "a cleared folder serves nothing new");
    Check(static_cast<const char*>(vxt)[0] == 'a', "a held copy outlives the folder switch");
    OdfUnlockItemDetour("uarracda.vxt");
    OdfUnlockItemDetour("uarracda.vxt");
    Check(MapFolderItems::Refcount("uarracda.vxt") == -1, "the last Release frees a retired copy");
    Check(g_unknownUnlocks == 0, "no served name's unlock reaches the engine");
    Check(OdfUseItemDetour("uarracda.vxt") == nullptr, "with no folder the stock miss returns");

    MapFolderItems::ResetForTesting();
    fs::remove_all(root, ec);
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
    TestOwnedOdfRead();
    TestMapFolderItemsServeOnlyIndexGaps();

    OdfItemHookTest::ResetCache();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("odf_item_hooks_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
