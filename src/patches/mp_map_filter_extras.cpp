// mp_map_filter_extras.cpp
// BZR Open Shim - extra filters and a search box on the multiplayer Create
// Game map list.
//
// Stock offers All Maps, Strategy, Death Match, King of the Hill, 2/3/4
// Players and (when any exist) Workshop. This adds "5+ Players", "Stock
// Maps" and a free-text search without re-implementing the list: every
// container operation is the engine's own, so nothing the MSVC120 game
// allocates is ever freed by the v143 shim, or the other way round.
//
//   1. Filter list. The map component's constructor (0x007A3160) fills a
//      keys vector (+0x00) and a labels vector (+0x0C) with push_back
//      (0x006CF320). A detour at 0x007A35C0, the first instruction after the
//      last label, appends our key/label pairs the same way. Like stock's
//      Workshop entry, an extra filter is offered only when at least one map
//      matches it.
//   2. Predicate. cMapManager::BuildFilteredMapList (0x00752A50, thiscall on
//      the filtered deque, key std::string by value, ret 0x18) clears the
//      deque and appends nothing for a key it does not know. For one of our
//      keys the entry detour runs it as "All Maps" instead and remembers
//      which extra filter is active.
//   3. Append. The predicate's only push_back call (0x00752CD0 ->
//      0x00752DD0, the deque<MapEntry> copy-append) is redirected here, so a
//      map is appended only when it matches the active extra filter and the
//      search text.
//   4. Screen. The only call to the cUI_Multiplayer_Create constructor
//      (0x007C8591 -> 0x00796880) is redirected so that, once every stock
//      child exists, the filter dropdown gets back any label its fixed row
//      count dropped (it keeps as many rows as fit its height and silently
//      ignores the rest), and the search box is built.
//   5. Search. A cUI_TextEntry with a transparent button over it, the same
//      construction as the lobby nickname field. The screen's OnChar sends
//      every character to its chat entry through cUI_TextEntry::AppendChar
//      (0x007CFA70), which lobby_screen_hooks.cpp already detours; while the
//      search box is being edited that detour hands each character here.
//      Each edit re-runs the current filter through the screen's own
//      re-filter (0x007A4460) and keeps the selected map when it survives.
//
// An empty filtered list must never be reachable: when hosting, the list's
// reselect path selects row 0 and dereferences it without a bounds check.
// Extra filters are offered only when non-empty, and a search that matches
// nothing is dropped for that pass, so the list shows everything instead.
//
// Off by default: [General] MapFilterExtras = 1, or
// OPENSHIM_MAP_FILTER_EXTRAS=1. Every address comes from engine_addresses
// with its guard bytes; a mismatch leaves the stock list untouched.

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "bzr_string.h"
#include "hook_engine.h"
#include "map_filter_extras.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            using MapFilterExtras::Extra;
            using MapFilterExtras::ExtraFilterInfo;
            using MapFilterExtras::kExtraFilters;

            // __thiscall with the key by value; declared __fastcall so the
            // dummy edx lines the key up on the stack. Callee pops 0x18.
            using FnMapFilterPredicate = void(__fastcall*)(void* filteredDeque, void* edx, BzrString key);
            using FnMapDequePushBack = void(__thiscall*)(void* deque, const void* entry);
            using FnVectorStringPushBack = void(__thiscall*)(void* vector, const BzrString* value);
            // cUI_Multiplayer_Create ctor: one stack argument, ret 4, returns this.
            using FnCreateScreenCtor = void*(__thiscall*)(void* self, void* arg);
            // Re-filter by dropdown label, then reselect by map file name
            // (not found selects row 0). ret 8.
            using FnMapFilterRefresh = void(__thiscall*)(void* component, const BzrString* label,
                                                         const BzrString* reselect);
            // cUI_Selectlist: the selected row's text, or null with no selection.
            using FnSelectlistSelectedText = const char*(__thiscall*)(void* list);
            // Map component: the selected MapEntry, or null (bounds-checked).
            using FnComponentSelectedEntry = const uint8_t*(__thiscall*)(void* component);

            // MapEntry (0xB4 bytes, confirmed from its copy constructor 0x00753550).
            constexpr uint32_t kMapEntryFileName = 0x00;
            constexpr uint32_t kMapEntryMinPlayers = 0x18;
            constexpr uint32_t kMapEntryMaxPlayers = 0x1C;
            constexpr uint32_t kMapEntryTitle = 0x20;
            constexpr uint32_t kMapEntryWorkshopId = 0x3C;
            // The map manager's full list is a deque<MapEntry> at +0x18 with
            // one element per block: +4 block map, +8 map size (a power of
            // two), +0xC first offset, +0x10 count. The filtered list is the
            // same deque type.
            constexpr uint32_t kMapManagerDeque = 0x18;
            constexpr uint32_t kDequeCount = 0x10;
            // Map component (constructed by 0x007A3160; `this` at [ebp-0x1C4]).
            constexpr uint32_t kComponentKeys = 0x00;
            constexpr uint32_t kComponentLabels = 0x0C;
            constexpr uint32_t kEngineStringSize = 0x18;
            // cUI_Multiplayer_Create (0x1D8 bytes, rebuilt on every visit).
            constexpr uint32_t kScreenWidgetParent = 0x150; // Middle_Overlay
            constexpr uint32_t kScreenFilterList = 0x17C;
            constexpr uint32_t kScreenMapComponent = 0x1C8;
            // cUI_Selectlist: the row widgets the ctor pre-built (a pointer
            // vector) and the items vector of {std::string, int}.
            constexpr uint32_t kSelectlistRowsBegin = 0x15C;
            constexpr uint32_t kSelectlistRowsEnd = 0x160;
            constexpr uint32_t kSelectlistItemsBegin = 0x168;
            constexpr uint32_t kSelectlistItemsEnd = 0x16C;
            constexpr uint32_t kSelectlistItemSize = 0x1C;

            // Search box, in the 1440x1080 design space: right of the Back
            // corner (x <= 342), under the error line (y <= 63) and above the
            // column headers (y >= 96).
            constexpr float kSearchX = 350.0f;
            constexpr float kSearchY = 66.0f;
            constexpr float kSearchWidth = 280.0f;
            constexpr float kSearchHeight = 28.0f;
            // The display length is a width budget (~14.4 design units per
            // glyph, see the nickname field in lobby_ui.cpp), not an input limit.
            constexpr int kSearchVisibleCharacters = 19;
            constexpr int kSearchInputLimit = 31;
            constexpr char kSearchPlaceholder[] = "Search: click here";

            constexpr uint8_t kPredicatePrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            constexpr uint8_t kKeysBuiltBytes[] = { 0x8B, 0x85, 0x3C, 0xFE, 0xFF, 0xFF };

            InlineDetour32 g_PredicateDetour = {};
            InlineDetour32 g_KeysBuiltDetour = {};
            void* g_KeysBuiltTrampoline = nullptr;
            FnMapDequePushBack g_MapDequePushBack = nullptr;
            FnVectorStringPushBack g_VectorStringPushBack = nullptr;
            FnCreateScreenCtor g_CreateScreenCtor = nullptr;
            FnMapFilterRefresh g_MapFilterRefresh = nullptr;
            FnSelectlistSelectedText g_SelectlistSelectedText = nullptr;
            FnComponentSelectedEntry g_ComponentSelectedEntry = nullptr;
            uint32_t g_MapManagerSlot = 0;
            uint32_t g_CreateScreenSlot = 0;
            bool g_MapFilterExtrasInstalled = false;
            bool g_MapFilterExtrasInstallLogged = false;

            // Set only while the predicate runs. Everything here lives on the
            // game's UI thread.
            Extra g_ActiveExtra = Extra::None;
            bool g_ApplySearch = false;

            // The search box of the Create Game screen currently open. The
            // screen frees its children when it closes, so every use is gated
            // on the screen global still naming this screen.
            uint8_t* g_SearchScreen = nullptr;
            void* g_SearchParent = nullptr;
            void* g_SearchEntry = nullptr;
            bool g_SearchEditing = false;
            char g_SearchText[kSearchInputLimit + 1] = {};

            constexpr const char* kComponent = "mapfilter";

            bool ShouldEnableMapFilterExtras()
            {
                if (EnvFlagEnabled("OPENSHIM_MAP_FILTER_EXTRAS"))
                    return true;
                bool enabled = false;
                return TryGetUserConfigBool("General", "MapFilterExtras", enabled) && enabled;
            }

            // Truncating copy. POD-only: called from inside __try.
            void CopyText(char* out, size_t outSize, const char* text)
            {
                size_t i = 0;
                for (; text && text[i] && i + 1 < outSize; ++i)
                    out[i] = text[i];
                out[i] = '\0';
            }

            void CopyEngineString(const void* engineString, char* out, size_t outSize)
            {
                CopyText(out, outSize, BzrStringData(static_cast<const BzrString*>(engineString)));
            }

            // Reads the fields the extra filters use. POD-only: called from
            // inside __try.
            bool TryReadEntry(const uint8_t* entry, int& minPlayers, int& maxPlayers,
                              char* workshopId, size_t workshopIdSize)
            {
                __try
                {
                    minPlayers = *reinterpret_cast<const int*>(entry + kMapEntryMinPlayers);
                    maxPlayers = *reinterpret_cast<const int*>(entry + kMapEntryMaxPlayers);
                    CopyEngineString(entry + kMapEntryWorkshopId, workshopId, workshopIdSize);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool TryReadEntryNames(const uint8_t* entry, char* title, size_t titleSize,
                                   char* fileName, size_t fileNameSize)
            {
                __try
                {
                    CopyEngineString(entry + kMapEntryTitle, title, titleSize);
                    CopyEngineString(entry + kMapEntryFileName, fileName, fileNameSize);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool EntryMatches(const void* entry, Extra extra)
            {
                if (extra == Extra::None)
                    return true;
                int minPlayers = 0;
                int maxPlayers = 0;
                char workshopId[64] = {};
                // An unreadable entry is shown rather than hidden: the extra
                // filter narrows "All Maps", so failing open is what stock does.
                if (!entry || !TryReadEntry(static_cast<const uint8_t*>(entry), minPlayers,
                                            maxPlayers, workshopId, sizeof(workshopId)))
                {
                    return true;
                }
                return MapFilterExtras::MatchesExtra(extra, minPlayers, maxPlayers, workshopId);
            }

            bool EntryMatchesSearch(const void* entry)
            {
                char title[128] = {};
                char fileName[128] = {};
                if (!entry || !TryReadEntryNames(static_cast<const uint8_t*>(entry), title,
                                                 sizeof(title), fileName, sizeof(fileName)))
                {
                    return true;
                }
                return MapFilterExtras::MatchesSearch(title, fileName, g_SearchText);
            }

            // Collects up to `capacity` entry pointers from the full map list.
            // POD-only: called from inside __try.
            bool TryCollectMapEntries(const void** out, unsigned capacity, unsigned& outCount)
            {
                outCount = 0;
                __try
                {
                    const uint8_t* manager = *reinterpret_cast<const uint8_t* const*>(g_MapManagerSlot);
                    if (!manager)
                        return false;
                    const uint8_t* deque = manager + kMapManagerDeque;
                    const void* const* blocks = *reinterpret_cast<const void* const* const*>(deque + 0x4);
                    const uint32_t mapSize = *reinterpret_cast<const uint32_t*>(deque + 0x8);
                    const uint32_t first = *reinterpret_cast<const uint32_t*>(deque + 0xC);
                    const uint32_t count = *reinterpret_cast<const uint32_t*>(deque + kDequeCount);
                    if (!blocks || mapSize == 0 || (mapSize & (mapSize - 1)) != 0)
                        return false;
                    for (uint32_t i = 0; i < count && outCount < capacity; ++i)
                    {
                        const void* entry = blocks[(first + i) & (mapSize - 1)];
                        if (entry)
                            out[outCount++] = entry;
                    }
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    outCount = 0;
                    return false;
                }
            }

            unsigned CountMatchingMaps(Extra extra)
            {
                static const void* entries[4096];
                unsigned count = 0;
                if (!TryCollectMapEntries(entries, 4096, count))
                    return 0;
                unsigned matches = 0;
                for (unsigned i = 0; i < count; ++i)
                {
                    if (EntryMatches(entries[i], extra))
                        ++matches;
                }
                return matches;
            }

            // A fault reads as non-empty, which skips the no-match retry and
            // leaves whatever the predicate built.
            uint32_t FilteredCount(const void* filteredDeque)
            {
                __try
                {
                    return *reinterpret_cast<const uint32_t*>(
                        static_cast<const uint8_t*>(filteredDeque) + kDequeCount);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 1;
                }
            }

            // Appends one key/label pair through the engine's own string and
            // vector code. POD-only: called from inside __try.
            bool TryPushKeyAndLabel(uint8_t* component, const char* key, const char* label)
            {
                __try
                {
                    BzrString text;
                    g_BzrFn_BzrStringCtorFromCStr(&text, key);
                    g_VectorStringPushBack(component + kComponentKeys, &text);
                    g_BzrFn_BzrStringDtor(&text);

                    g_BzrFn_BzrStringCtorFromCStr(&text, label);
                    g_VectorStringPushBack(component + kComponentLabels, &text);
                    g_BzrFn_BzrStringDtor(&text);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void __cdecl AppendExtraFilterKeys(uint8_t* component)
            {
                if (!component || !g_VectorStringPushBack ||
                    !g_BzrFn_BzrStringCtorFromCStr || !g_BzrFn_BzrStringDtor)
                {
                    return;
                }
                for (const ExtraFilterInfo& info : kExtraFilters)
                {
                    const unsigned matches = CountMatchingMaps(info.extra);
                    if (matches == 0)
                    {
                        LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] '%s' not offered: no map matches", info.label);
                        continue;
                    }
                    const bool pushed = TryPushKeyAndLabel(component, info.key, info.label);
                    LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] '%s' %s (%u maps)",
                        info.label, pushed ? "offered" : "push failed", matches);
                }
            }

            __declspec(naked) void MapFilterKeysBuiltStub()
            {
                __asm
                {
                    pushad
                    pushfd
                    mov  eax, dword ptr [ebp - 0x1C4]
                    push eax
                    call AppendExtraFilterKeys
                    add  esp, 4
                    popfd
                    popad
                    jmp  dword ptr [g_KeysBuiltTrampoline]
                }
            }

            uint8_t* CurrentCreateScreen()
            {
                __try
                {
                    return *reinterpret_cast<uint8_t**>(g_CreateScreenSlot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool SearchScreenLive()
            {
                return g_SearchScreen && g_CreateScreenSlot && CurrentCreateScreen() == g_SearchScreen;
            }

            bool SearchEntryLive()
            {
                return SearchScreenLive() && g_SearchParent && g_SearchEntry &&
                       IsWidgetLiveChildOfParent(g_SearchParent, g_SearchEntry);
            }

            void ForgetSearchBox()
            {
                g_SearchScreen = nullptr;
                g_SearchParent = nullptr;
                g_SearchEntry = nullptr;
                g_SearchEditing = false;
                g_SearchText[0] = '\0';
            }

            void __fastcall MapFilterPredicateHook(void* filteredDeque, void* edx, BzrString key)
            {
                const auto original = reinterpret_cast<FnMapFilterPredicate>(g_PredicateDetour.trampoline);
                const Extra extra = MapFilterExtras::ExtraFromKey(BzrStringData(&key));
                const bool search = g_SearchText[0] != '\0' && SearchScreenLive();
                if (extra == Extra::None && !search)
                {
                    g_ActiveExtra = Extra::None;
                    g_ApplySearch = false;
                    original(filteredDeque, edx, key); // takes ownership of the key
                    return;
                }

                // The stock predicate destroys the key it is given, and a
                // search that matches nothing needs a second run, so it gets
                // engine-built copies and this frame destroys the original.
                // An extra filter runs as "All Maps" and is narrowed in the
                // append hook.
                char runKey[256] = {};
                CopyText(runKey, sizeof(runKey), extra == Extra::None ? BzrStringData(&key) : "All Maps");

                BzrString first = {};
                BzrString retry = {};
                g_BzrFn_BzrStringCtorFromCStr(&first, runKey);
                if (search)
                    g_BzrFn_BzrStringCtorFromCStr(&retry, runKey);
                g_BzrFn_BzrStringDtor(&key);

                g_ActiveExtra = extra;
                g_ApplySearch = search;
                original(filteredDeque, edx, first);
                if (search)
                {
                    if (FilteredCount(filteredDeque) == 0)
                    {
                        // The predicate clears the deque first, so this simply
                        // rebuilds the list without the search.
                        g_ApplySearch = false;
                        original(filteredDeque, edx, retry);
                        LogShimA(LogLevel::Info, kComponent,
                                 "[MAPFILTER] search '%s' matches nothing here; showing the unsearched list",
                                 g_SearchText);
                    }
                    else
                    {
                        g_BzrFn_BzrStringDtor(&retry);
                    }
                }
                g_ActiveExtra = Extra::None;
                g_ApplySearch = false;
            }

            void __fastcall MapFilterAppendHook(void* filteredDeque, void* /*edx*/, const void* entry)
            {
                if (g_ActiveExtra != Extra::None && !EntryMatches(entry, g_ActiveExtra))
                    return;
                if (g_ApplySearch && !EntryMatchesSearch(entry))
                    return;
                g_MapDequePushBack(filteredDeque, entry);
            }

            // ---- Filter dropdown top-up ----

            // The dropdown's constructor pre-builds as many rows as fit its
            // height and stock fills only those, dropping any label past the
            // last row. Its item setter appends past the rows (and shows the
            // page arrows), so give back what was dropped.
            void TopUpFilterList(uint8_t* screen)
            {
                if (!g_BzrFn_SelectlistSetItem)
                    return;
                unsigned rows = 0;
                unsigned items = 0;
                unsigned labels = 0;
                unsigned added = 0;
                __try
                {
                    uint8_t* list = *reinterpret_cast<uint8_t**>(screen + kScreenFilterList);
                    const uint8_t* component = *reinterpret_cast<uint8_t**>(screen + kScreenMapComponent);
                    if (!list || !component)
                        return;
                    rows = (*reinterpret_cast<uint32_t*>(list + kSelectlistRowsEnd) -
                            *reinterpret_cast<uint32_t*>(list + kSelectlistRowsBegin)) / 4;
                    const uint8_t* labelsBegin = *reinterpret_cast<const uint8_t* const*>(component + kComponentLabels);
                    const uint8_t* labelsEnd = *reinterpret_cast<const uint8_t* const*>(component + kComponentLabels + 4);
                    labels = static_cast<unsigned>(labelsEnd - labelsBegin) / kEngineStringSize;
                    for (;;)
                    {
                        items = (*reinterpret_cast<uint32_t*>(list + kSelectlistItemsEnd) -
                                 *reinterpret_cast<uint32_t*>(list + kSelectlistItemsBegin)) / kSelectlistItemSize;
                        if (items >= labels || added >= 16)
                            break;
                        const char* label = BzrStringData(
                            reinterpret_cast<const BzrString*>(labelsBegin + items * kEngineStringSize));
                        // Appends only when index == size(); stock passes 0 as the value.
                        g_BzrFn_SelectlistSetItem(list, label, static_cast<int>(items), 0);
                        ++added;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] filter list top-up faulted code=0x%08X",
                             static_cast<uint32_t>(GetExceptionCode()));
                    return;
                }
                LogShimA(LogLevel::Info, kComponent,
                         "[MAPFILTER] filter list rows=%u labels=%u items=%u restored=%u",
                         rows, labels, items, added);
            }

            // ---- Search box ----

            bool TryReadSearchEntryText(char* out, size_t outSize)
            {
                __try
                {
                    CopyEngineString(static_cast<uint8_t*>(g_SearchEntry) + kUiTextEntryTextOffset, out, outSize);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out[0] = '\0';
                    return false;
                }
            }

            // cUI_Text::SetText only changes what is drawn; the next
            // AppendChar redraws from the backing string. Editing shows a
            // trailing cursor, idle shows the text or the placeholder.
            void ShowSearchText()
            {
                if (!g_BzrFn_SetTooltip || !SearchEntryLive())
                    return;
                char shown[kSearchInputLimit + 8] = {};
                if (g_SearchEditing)
                    std::snprintf(shown, sizeof(shown), "%s_", g_SearchText);
                else
                    CopyText(shown, sizeof(shown), g_SearchText[0] ? g_SearchText : kSearchPlaceholder);
                __try
                {
                    g_BzrFn_SetTooltip(g_SearchEntry, shown);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            // Gathers what the screen's re-filter needs: the selected
            // dropdown label (checked against the labels vector, since an
            // unknown label reads past the keys vector) and the selected
            // map's file name (copied now: the predicate frees every entry).
            bool TryPrepareRefresh(uint8_t*& component, char* label, size_t labelSize,
                                   char* reselect, size_t reselectSize)
            {
                __try
                {
                    component = *reinterpret_cast<uint8_t**>(g_SearchScreen + kScreenMapComponent);
                    uint8_t* list = *reinterpret_cast<uint8_t**>(g_SearchScreen + kScreenFilterList);
                    if (!component || !list)
                        return false;
                    const char* selected = g_SelectlistSelectedText(list);
                    if (!selected || !*selected)
                        return false;
                    CopyText(label, labelSize, selected);

                    const uint8_t* begin = *reinterpret_cast<const uint8_t* const*>(component + kComponentLabels);
                    const uint8_t* end = *reinterpret_cast<const uint8_t* const*>(component + kComponentLabels + 4);
                    bool known = false;
                    for (const uint8_t* p = begin; p && p < end; p += kEngineStringSize)
                    {
                        if (std::strcmp(BzrStringData(reinterpret_cast<const BzrString*>(p)), label) == 0)
                        {
                            known = true;
                            break;
                        }
                    }
                    if (!known)
                        return false;

                    reselect[0] = '\0';
                    const uint8_t* entry = g_ComponentSelectedEntry(component);
                    if (entry)
                        CopyEngineString(entry + kMapEntryFileName, reselect, reselectSize);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool TryRunRefresh(uint8_t* component, const char* label, const char* reselect)
            {
                __try
                {
                    BzrString labelText;
                    BzrString reselectText;
                    g_BzrFn_BzrStringCtorFromCStr(&labelText, label);
                    g_BzrFn_BzrStringCtorFromCStr(&reselectText, reselect);
                    g_MapFilterRefresh(component, &labelText, &reselectText);
                    g_BzrFn_BzrStringDtor(&reselectText);
                    g_BzrFn_BzrStringDtor(&labelText);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void RefreshMapListForSearch()
            {
                if (!SearchScreenLive())
                    return;
                uint8_t* component = nullptr;
                char label[256] = {};
                char reselect[260] = {};
                if (!TryPrepareRefresh(component, label, sizeof(label), reselect, sizeof(reselect)))
                {
                    LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] search refresh skipped: no current filter");
                    return;
                }
                if (!TryRunRefresh(component, label, reselect))
                {
                    LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] search refresh faulted; search cleared");
                    g_SearchText[0] = '\0';
                }
            }

            void EndSearchEdit()
            {
                g_SearchEditing = false;
                ShowSearchText();
            }

            void __cdecl MapSearchOnClick()
            {
                if (!SearchEntryLive())
                    return;
                g_SearchEditing = true;
                ShowSearchText();
            }

            bool CreateSearchBox(uint8_t* screen)
            {
                if (!g_BzrFn_TextEntryCtor || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
                    !g_BzrFn_SetOnClick || !g_BzrFn_SetTooltip || !g_BzrFn_TextEntryAppendChar)
                {
                    return false;
                }
                void* parent = nullptr;
                __try
                {
                    parent = *reinterpret_cast<void**>(screen + kScreenWidgetParent);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                if (!parent)
                    return false;

                void* entryMem = ::operator new(kUiTextEntrySize, std::nothrow);
                void* buttonMem = ::operator new(kUiButtonSize, std::nothrow);
                if (!entryMem || !buttonMem)
                {
                    ::operator delete(entryMem, std::nothrow);
                    ::operator delete(buttonMem, std::nothrow);
                    return false;
                }
                std::memset(entryMem, 0, kUiTextEntrySize);
                std::memset(buttonMem, 0, kUiButtonSize);

                void* entry = nullptr;
                void* button = nullptr;
                __try
                {
                    entry = g_BzrFn_TextEntryCtor(entryMem, 0, 1, kSearchVisibleCharacters,
                                                  "OpenShimMapSearch", kSearchX, kSearchY,
                                                  kSearchWidth, kSearchHeight, 0x8020, parent);
                    if (!entry)
                        return false;
                    if (g_BzrFn_TextEntrySetInputLimit)
                        g_BzrFn_TextEntrySetInputLimit(entry, kSearchInputLimit);
                    g_BzrFn_SetTooltip(entry, kSearchPlaceholder);
                    g_BzrFn_AddChild(parent, entry, 0);

                    // The entry has no click path of its own that reaches
                    // the shim. A textureless button over it, added after it
                    // so it is ahead in the hit walk, starts editing; it
                    // draws nothing, leaving the entry visible.
                    button = g_BzrFn_ButtonCtor(buttonMem, "OpenShimMapSearchEdit", kSearchX, kSearchY,
                                                kSearchWidth, kSearchHeight, 0x20, parent, 0, 0);
                    if (button)
                    {
                        g_BzrFn_SetOnClick(button, reinterpret_cast<void*>(&MapSearchOnClick));
                        g_BzrFn_AddChild(parent, button, 0);
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] search box construction faulted code=0x%08X",
                             static_cast<uint32_t>(GetExceptionCode()));
                    return false;
                }
                if (!button)
                    return false;

                g_SearchScreen = screen;
                g_SearchParent = parent;
                g_SearchEntry = entry;
                return true;
            }

            void* __fastcall CreateScreenBuiltHook(void* self, void* /*edx*/, void* arg)
            {
                // Forget the previous visit first: the ctor itself runs the
                // first filter pass, and a new screen can reuse the old one's
                // address.
                ForgetSearchBox();
                void* const screen = g_CreateScreenCtor(self, arg);
                if (screen)
                {
                    TopUpFilterList(static_cast<uint8_t*>(screen));
                    const bool built = CreateSearchBox(static_cast<uint8_t*>(screen));
                    LogShimA(built ? LogLevel::Info : LogLevel::Warn, kComponent,
                             "[MAPFILTER] search box %s", built ? "built" : "not built");
                }
                return screen;
            }

            bool ResolveCode(const char* name, uint32_t& address)
            {
                return HookEngine::ResolveEngineAddress(name, address) == HookEngine::EngineAddressStatus::Bound;
            }

            bool ResolveData(const char* name, uint32_t& address)
            {
                return HookEngine::ResolveEngineAddress(name, address) == HookEngine::EngineAddressStatus::BoundData;
            }
        }

        bool TryRouteMapSearchChar(uint8_t character, FnUiTextEntryAppendChar original, uint8_t& result)
        {
            if (!g_SearchEditing)
                return false;
            if (!original || !SearchEntryLive())
            {
                // The screen closed while editing; its children are gone.
                ForgetSearchBox();
                return false;
            }

            result = 1;
            if (character == '\r' || character == '\n' || character == 0x1B)
            {
                // Enter or Escape stops editing. Neither reaches the entry:
                // it has no Enter callback, and Escape would be appended.
                EndSearchEdit();
                return true;
            }
            if (character == '\t')
                return true;

            char before[kSearchInputLimit + 1] = {};
            CopyText(before, sizeof(before), g_SearchText);
            result = original(g_SearchEntry, character);
            char text[kSearchInputLimit + 1] = {};
            TryReadSearchEntryText(text, sizeof(text));
            if (std::strcmp(text, before) != 0)
            {
                CopyText(g_SearchText, sizeof(g_SearchText), text);
                RefreshMapListForSearch();
            }
            ShowSearchText();
            return true;
        }

        void InstallMapFilterExtrasIfEnabled()
        {
            if (g_MapFilterExtrasInstalled || !ShouldEnableMapFilterExtras())
                return;

            uint32_t predicate = 0;
            uint32_t appendCall = 0;
            uint32_t pushBack = 0;
            uint32_t keysBuilt = 0;
            uint32_t vectorPush = 0;
            const bool resolved =
                ResolveCode("MapFilterPredicate", predicate) &&
                ResolveCode("MapFilterAppendCall", appendCall) &&
                ResolveCode("MapDequePushBack", pushBack) &&
                ResolveCode("MapFilterKeysBuilt", keysBuilt) &&
                ResolveCode("VectorStringPushBack", vectorPush) &&
                ResolveData("MapManagerSlot", g_MapManagerSlot);
            if (!resolved || !g_BzrFn_BzrStringCtorFromCStr || !g_BzrFn_BzrStringDtor)
            {
                if (!g_MapFilterExtrasInstallLogged)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: an engine address did not verify");
                    g_MapFilterExtrasInstallLogged = true;
                }
                return;
            }
            g_MapDequePushBack = reinterpret_cast<FnMapDequePushBack>(pushBack);
            g_VectorStringPushBack = reinterpret_cast<FnVectorStringPushBack>(vectorPush);

            // Filtering first, then the list entries: an entry is only
            // offered once selecting it can actually narrow the list.
            if (!InstallInlineDetour32(g_PredicateDetour, predicate,
                                       reinterpret_cast<void*>(&MapFilterPredicateHook),
                                       sizeof(kPredicatePrologue), kPredicatePrologue,
                                       sizeof(kPredicatePrologue)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: predicate detour refused");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            if (!RedirectCallTarget(appendCall, pushBack, reinterpret_cast<uintptr_t>(&MapFilterAppendHook)))
            {
                // The predicate detour stays, but with no append hook an extra
                // key would show every map; since no extra key is offered
                // below and no search box is built, the detour only ever sees
                // stock keys and forwards them.
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: append call site did not match");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            if (!InstallInlineDetour32(g_KeysBuiltDetour, keysBuilt,
                                       reinterpret_cast<void*>(&MapFilterKeysBuiltStub),
                                       sizeof(kKeysBuiltBytes), kKeysBuiltBytes,
                                       sizeof(kKeysBuiltBytes)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: filter-list detour refused");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            // The detour publishes its trampoline only after the jump is
            // written. That is safe here because this runs in late init, long
            // before the Create Game screen can exist to reach the stub.
            g_KeysBuiltTrampoline = g_KeysBuiltDetour.trampoline;
            g_MapFilterExtrasInstalled = true;
            LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] extra filters installed (5+ Players, Stock Maps)");

            // The screen hook (dropdown top-up and search box) is separate:
            // the filters above work without it.
            uint32_t factoryCall = 0;
            uint32_t screenCtor = 0;
            uint32_t refresh = 0;
            uint32_t selectedText = 0;
            uint32_t selectedEntry = 0;
            const bool screenResolved =
                ResolveCode("MultiCreateFactoryCall", factoryCall) &&
                ResolveCode("MultiCreateScreenCtor", screenCtor) &&
                ResolveCode("MapFilterRefresh", refresh) &&
                ResolveCode("SelectlistSelectedText", selectedText) &&
                ResolveCode("MapComponentSelectedEntry", selectedEntry) &&
                ResolveData("MultiCreateScreenSlot", g_CreateScreenSlot);
            if (!screenResolved)
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] search box stands down: an engine address did not verify");
                return;
            }
            g_CreateScreenCtor = reinterpret_cast<FnCreateScreenCtor>(screenCtor);
            g_MapFilterRefresh = reinterpret_cast<FnMapFilterRefresh>(refresh);
            g_SelectlistSelectedText = reinterpret_cast<FnSelectlistSelectedText>(selectedText);
            g_ComponentSelectedEntry = reinterpret_cast<FnComponentSelectedEntry>(selectedEntry);
            if (!RedirectCallTarget(factoryCall, screenCtor, reinterpret_cast<uintptr_t>(&CreateScreenBuiltHook)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] search box stands down: screen factory call did not match");
                return;
            }
            LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] search box and filter-list top-up installed");
        }
    }
}
