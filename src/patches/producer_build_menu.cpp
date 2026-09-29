// producer_build_menu.cpp
// BZR Open Shim - producer nested build menus (PRODMENU): Recycler, Factory
// and ConstructionRig pages driven by a [Builder] ODF tree, through vtable
// replacements for UpdateModeList / SetActiveMode / Deselect.
#include "bzr_hooks.h"
#include "bool_token.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <malloc.h>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    // Redux's BuildItem, as InitBuildItem (0x0049F5C0) lays it out: 0x20 bytes,
    // ten children per [Builder] from calloc(10, 0x20). A child whose ODF has no
    // [Builder] section is a leaf naming a GameObjectClass. A leaf copies its
    // parent's team, so a root needs a parent even though it is never shown.
    struct BuildItem
    {
        BuildItem* parent;
        char name[16];      // buildName for a [Builder], unitName for a leaf
        int32_t team;
        BuildItem* menu;    // children, or null for a leaf
        void* item;         // GameObjectClass* for a leaf
    };
    static_assert(sizeof(BuildItem) == 0x20, "BuildItem must match the engine's 0x20-byte layout");

    FnModeListUpdate g_BzrFn_ProducerUpdateModeList = nullptr;
    FnSetActiveMode g_BzrFn_ProducerSetActiveMode = nullptr;
    FnObjectDeselect g_BzrFn_GameObjectDeselect = nullptr;
    FnModeListUpdate g_BzrFn_ConstructionRigUpdateModeList = nullptr;
    FnSetActiveMode g_BzrFn_ConstructionRigSetActiveMode = nullptr;
    FnObjectDeselect g_BzrFn_ConstructionRigDeselect = nullptr;
    FnControlPanelLifecycle g_BzrFn_ControlPanelPostLoad = nullptr;
    FnControlPanelLifecycle g_BzrFn_ControlPanelCleanup = nullptr;
    FnModeListSetMode g_BzrFn_ModeListSetMode = nullptr;
    void* g_BzrVtbl_Producer = nullptr;
    void* g_BzrVtbl_Recycler = nullptr;
    void* g_BzrVtbl_Factory = nullptr;
    void* g_BzrVtbl_ConstructionRig = nullptr;
    uint8_t* g_BzrPtr_ClassLoadAssetsFlag = nullptr;

    namespace Hooks
    {
        ProducerBuildMenuConfig g_ProducerBuildMenuConfig = {};

        constexpr char kProducerBuildMenuIniName[] = "openshim_producer_build_menus.ini";

        constexpr char kProducerBuildMenuSection[] = "ProducerBuildMenus";

        // How the stock mode-list code reads a producer (Producer::
        // UpdateModeList 0x005AE660, ConstructionRig::UpdateModeList
        // 0x0049D550; reverse_engineering/producer_build_menu_notes.md).
        // +0x228 is the Craft deploy state: 0 mobile, 1 deploying, 2
        // deployed, 3 packing up.
        constexpr uintptr_t kCraftDeployStateOffset = 0x228;
        constexpr uintptr_t kObjectClassOffset = 0xF8;
        constexpr uintptr_t kProducerClassBuildListOffset = 0x608;
        constexpr size_t kProducerClassBuildListCount = 9;
        constexpr uintptr_t kObjectModeListOffset = 0x1A4;

        // Mode values up to 0x1A are the engine's named modes; anything larger
        // is drawn and dispatched as a GameObjectClass*. 0x16 is "Back".
        constexpr int kModeBack = 0x16;
        constexpr uint32_t kModeLastNamed = 0x1A;

        constexpr size_t kVtableDeselectIndex = 9;
        constexpr size_t kVtableSetActiveModeIndex = 11;
        constexpr size_t kVtableUpdateModeListIndex = 23;
        constexpr size_t kControlPanelCleanupIndex = 7;

        constexpr size_t kBuildItemChildCount = 10;

        // A submenu button is a GameObjectClass-shaped block. The mode panel
        // reads only the label at +0x64 (through the "names" lookup) and the
        // scrap and pilot costs at +0x48 and +0x50, which stay zero.
        constexpr size_t kMenuStubSize = 0x200;
        constexpr uintptr_t kMenuStubLabelOffset = 0x64;
        constexpr size_t kMenuStubLabelMax = 31;

        enum class ProducerBuildMenuKind
        {
            Producer,
            Recycler,
            Factory,
            ConstructionRig,
        };

        // Where each family puts its build page. The producer family shows its
        // list in slots 1..9 once it starts deploying and builds when deployed;
        // the rig shows slots 3..9 in every state and builds while mobile. Slot
        // 10 (Pack Up / Cancel / Recycle) is never touched, and a page below the
        // root gives its last position to Back.
        struct ProducerMenuLayout
        {
            int firstSlot;
            size_t capacity;
            int buildState;
            bool listShownWhenMobile;
        };
        constexpr ProducerMenuLayout kProducerFamilyLayout = {1, 9, 2, false};
        constexpr ProducerMenuLayout kConstructionRigLayout = {3, 7, 0, true};

        static bool IsIniBoolTrue(const char* value, bool fallback)
        {
            bool parsed = fallback;
            return BZROpenShim::BoolToken::TryParse(value, parsed) ? parsed : fallback;
        }

        static int64_t PackProducerBuildMenuToken(const char* token)
        {
            if (!token)
                return 0;

            uint8_t bytes[kProducerBuildMenuTokenLen] = {};
            for (size_t i = 0; i < kProducerBuildMenuTokenLen && token[i]; ++i)
                bytes[i] = static_cast<uint8_t>(token[i]);

            int64_t packed = 0;
            memcpy(&packed, bytes, sizeof(bytes));
            return packed;
        }

        ProducerBuildMenuEntry NormalizeProducerBuildMenuToken(const char* value)
        {
            ProducerBuildMenuEntry entry = {};
            if (!value)
                return entry;

            const char* start = value;
            while (*start && std::isspace(static_cast<unsigned char>(*start)))
                ++start;

            const char* end = start + strlen(start);
            while (end > start && std::isspace(static_cast<unsigned char>(end[-1])))
                --end;

            size_t length = static_cast<size_t>(end - start);
            if (length == 0)
                return entry;

            char normalized[64] = {};
            size_t out = 0;
            for (size_t i = 0; i < length && out + 1 < sizeof(normalized); ++i)
            {
                normalized[out++] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(start[i])));
            }
            normalized[out] = '\0';

            if (out > 7 && strcmp(normalized + out - 7, "_mp.odf") == 0)
            {
                out -= 7;
                normalized[out] = '\0';
            }
            else if (out > 4 && strcmp(normalized + out - 4, ".odf") == 0)
            {
                out -= 4;
                normalized[out] = '\0';
            }

            if (out == 0)
                return entry;

            if (out > kProducerBuildMenuTokenLen)
                out = kProducerBuildMenuTokenLen;

            memcpy(entry.token, normalized, out);
            entry.token[out] = '\0';
            entry.hasValue = entry.token[0] != '\0';
            entry.packedToken = entry.hasValue ? PackProducerBuildMenuToken(entry.token) : 0;
            return entry;
        }

        static ProducerBuildMenuEntry ReadProducerBuildMenuEntry(const char* key)
        {
            ProducerBuildMenuEntry entry = {};
            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return entry;

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            char buffer[64] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                key,
                "",
                buffer,
                static_cast<DWORD>(sizeof(buffer)),
                configPath.string().c_str());
            return NormalizeProducerBuildMenuToken(buffer);
        }

        static bool IsProducerBuildMenuReservedKey(const char* key)
        {
            if (!key || !*key)
                return true;

            return _stricmp(key, "Enabled") == 0 ||
                _stricmp(key, "Recycler") == 0 ||
                _stricmp(key, "Factory") == 0 ||
                _stricmp(key, "Armory") == 0 ||
                _stricmp(key, "ConstructionRig") == 0 ||
                _stricmp(key, "Constructor") == 0 ||
                _stricmp(key, "Default") == 0 ||
                _stricmp(key, "Fallback") == 0;
        }

        static void LoadProducerBuildMenuOdfOverrides(const std::filesystem::path& configPath)
        {
            g_ProducerBuildMenuConfig.odfOverrides.clear();

            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") != 0 || !file)
                return;

            char line[256] = {};
            bool inTargetSection = false;
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                    continue;

                if (*trimmed == '[')
                {
                    char* closing = std::strchr(trimmed, ']');
                    if (!closing)
                        continue;

                    *closing = '\0';
                    inTargetSection = (_stricmp(trimmed + 1, kProducerBuildMenuSection) == 0);
                    continue;
                }

                if (!inTargetSection)
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (!key || !*key || !value || !*value)
                    continue;
                if (IsProducerBuildMenuReservedKey(key))
                    continue;

                const ProducerBuildMenuEntry keyEntry = NormalizeProducerBuildMenuToken(key);
                const ProducerBuildMenuEntry valueEntry = NormalizeProducerBuildMenuToken(value);
                if (!keyEntry.hasValue || !valueEntry.hasValue)
                    continue;

                g_ProducerBuildMenuConfig.odfOverrides[keyEntry.token] = valueEntry;
            }

            std::fclose(file);
        }

        static ProducerBuildMenuEntry TryGetProducerBuildMenuEntryForOdf(const char* producerOdf)
        {
            ProducerBuildMenuEntry entry = {};
            const ProducerBuildMenuEntry key = NormalizeProducerBuildMenuToken(producerOdf);
            if (!key.hasValue)
                return entry;

            const auto it = g_ProducerBuildMenuConfig.odfOverrides.find(key.token);
            if (it != g_ProducerBuildMenuConfig.odfOverrides.end())
                return it->second;

            return entry;
        }

        static ProducerBuildMenuEntry TryReadProducerBuildMenuEntryFromOdfFile(const char* producerOdf)
        {
            ProducerBuildMenuEntry result = {};
            const ProducerBuildMenuEntry producerKey = NormalizeProducerBuildMenuToken(producerOdf);
            if (!producerKey.hasValue)
                return result;

            const auto cached = g_ProducerBuildMenuConfig.odfFileEntries.find(producerKey.token);
            if (cached != g_ProducerBuildMenuConfig.odfFileEntries.end())
                return cached->second;

            const auto directories = GetProducerOdfDirectoryCandidates();
            std::filesystem::path resolvedPath;
            for (const auto& directory : directories)
            {
                std::error_code error;
                const auto mpPath = directory / (std::string(producerKey.token) + "_mp.odf");
                if (std::filesystem::exists(mpPath, error) && !error)
                {
                    resolvedPath = mpPath;
                    break;
                }

                error.clear();
                const auto normalPath = directory / (std::string(producerKey.token) + ".odf");
                if (std::filesystem::exists(normalPath, error) && !error)
                {
                    resolvedPath = normalPath;
                    break;
                }
            }

            if (!resolvedPath.empty())
            {
                FILE* file = nullptr;
                if (fopen_s(&file, resolvedPath.string().c_str(), "r") == 0 && file)
                {
                    char line[256] = {};
                    bool inProducerSection = false;
                    while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                    {
                        char* trimmed = TrimAsciiInPlace(line);
                        if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                            continue;

                        if (*trimmed == '[')
                        {
                            char* closing = std::strchr(trimmed, ']');
                            if (!closing)
                                continue;

                            *closing = '\0';
                            inProducerSection = (_stricmp(trimmed + 1, "ProducerClass") == 0);
                            continue;
                        }

                        if (!inProducerSection)
                            continue;

                        char* equals = std::strchr(trimmed, '=');
                        if (!equals)
                            continue;

                        *equals = '\0';
                        char* key = TrimAsciiInPlace(trimmed);
                        char* value = TrimAsciiInPlace(equals + 1);
                        if (!key || !*key || !value || !*value)
                            continue;

                        if (_stricmp(key, "buildMenuRoot") == 0 ||
                            _stricmp(key, "buildMenu") == 0)
                        {
                            result = NormalizeProducerBuildMenuToken(value);
                            break;
                        }
                    }

                    std::fclose(file);

                    if (result.hasValue)
                    {
                        Log(L"[PRODMENU] ODF root producer=%hs root=%hs path=%hs\n",
                            producerKey.token,
                            result.token,
                            resolvedPath.string().c_str());
                    }
                }
            }

            g_ProducerBuildMenuConfig.odfFileEntries[producerKey.token] = result;
            return result;
        }

        static void LoadProducerBuildMenuConfig()
        {
            if (g_ProducerBuildMenuConfig.initialized)
                return;

            g_ProducerBuildMenuConfig.initialized = true;

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
            {
                Log(L"[PRODMENU] Game directory unavailable; feature disabled\n");
                return;
            }

            const auto configPath = moduleDir / kProducerBuildMenuIniName;
            const auto configPathString = configPath.string();
            DWORD attrs = GetFileAttributesA(configPathString.c_str());
            if (attrs == INVALID_FILE_ATTRIBUTES || (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
                Log(L"[PRODMENU] Config not found at %hs; feature disabled\n", configPathString.c_str());
                return;
            }

            char enabledBuffer[32] = {};
            GetPrivateProfileStringA(
                kProducerBuildMenuSection,
                "Enabled",
                "1",
                enabledBuffer,
                static_cast<DWORD>(sizeof(enabledBuffer)),
                configPathString.c_str());

            g_ProducerBuildMenuConfig.recycler = ReadProducerBuildMenuEntry("Recycler");
            g_ProducerBuildMenuConfig.factory = ReadProducerBuildMenuEntry("Factory");
            g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("ConstructionRig");
            if (!g_ProducerBuildMenuConfig.constructionRig.hasValue)
                g_ProducerBuildMenuConfig.constructionRig = ReadProducerBuildMenuEntry("Constructor");
            LoadProducerBuildMenuOdfOverrides(configPath);

            // The Armory keeps its own category pages, and a stock Builder
            // root is no longer applied to producers nobody configured.
            for (const char* ignored : {"Armory", "Fallback", "Default"})
            {
                if (ReadProducerBuildMenuEntry(ignored).hasValue)
                    Log(L"[PRODMENU] %hs= is ignored: only Recycler, Factory, ConstructionRig and per-ODF keys select a menu root\n", ignored);
            }

            // ODF-local buildMenuRoot keys need no mapping here, so the file's
            // Enabled switch alone turns the feature on.
            g_ProducerBuildMenuConfig.enabled = IsIniBoolTrue(enabledBuffer, true);

            Log(L"[PRODMENU] Config %hs loaded enabled=%hs recycler=%hs factory=%hs constrig=%hs odfOverrides=%u\n",
                configPathString.c_str(),
                g_ProducerBuildMenuConfig.enabled ? "true" : "false",
                g_ProducerBuildMenuConfig.recycler.hasValue ? g_ProducerBuildMenuConfig.recycler.token : "-",
                g_ProducerBuildMenuConfig.factory.hasValue ? g_ProducerBuildMenuConfig.factory.token : "-",
                g_ProducerBuildMenuConfig.constructionRig.hasValue ? g_ProducerBuildMenuConfig.constructionRig.token : "-",
                static_cast<unsigned>(g_ProducerBuildMenuConfig.odfOverrides.size()));
        }

        // Root precedence: the producer ODF's own [ProducerClass]
        // buildMenuRoot, then a per-ODF INI override, then the type mapping.
        // A producer that none of them names keeps its stock flat list.
        static ProducerBuildMenuEntry SelectProducerBuildMenuEntry(const char* producerOdf, ProducerBuildMenuKind kind)
        {
            ProducerBuildMenuEntry odfFileEntry = TryReadProducerBuildMenuEntryFromOdfFile(producerOdf);
            if (odfFileEntry.hasValue)
                return odfFileEntry;

            ProducerBuildMenuEntry odfEntry = TryGetProducerBuildMenuEntryForOdf(producerOdf);
            if (odfEntry.hasValue)
                return odfEntry;

            switch (kind)
            {
            case ProducerBuildMenuKind::Recycler:
                return g_ProducerBuildMenuConfig.recycler;
            case ProducerBuildMenuKind::Factory:
                return g_ProducerBuildMenuConfig.factory;
            case ProducerBuildMenuKind::ConstructionRig:
                return g_ProducerBuildMenuConfig.constructionRig;
            default:
                return {};
            }
        }

        // --- Menu trees ---------------------------------------------------------
        //
        // One tree per root token, built with the engine's own InitBuildItem so
        // [Builder] files resolve exactly as the arcade build panel resolves
        // them (including *_mp.odf in a net game). Leaves hold GameObjectClass
        // pointers, which the engine frees between missions, so the trees live
        // only between ControlPanel::PostLoad and ControlPanel::Cleanup -- the
        // same span the engine gives its own buildMenu tree.

        struct ProducerMenuTree
        {
            BuildItem anchor;   // the root's parent; never shown
            BuildItem root;
            char token[kProducerBuildMenuTokenLen + 1];
        };

        // A null value records a root that failed to build, so it is not
        // retried every frame.
        static std::unordered_map<std::string, ProducerMenuTree*> g_ProducerMenuTrees;
        // Objects below their root page; an object at the root has no entry.
        static std::unordered_map<void*, const BuildItem*> g_ProducerMenuCursors;
        static bool g_ProducerMenuSessionActive = false;

        // Submenu stubs. A stub is never freed: a stale mode value may still
        // name one after its tree is gone, and SetActiveMode must recognise it
        // then too, so it can never reach the stock build command.
        static std::unordered_map<const BuildItem*, uint8_t*> g_ProducerMenuNodeStubs;
        static std::unordered_map<uintptr_t, const BuildItem*> g_ProducerMenuStubNodes;
        static std::unordered_set<uintptr_t> g_ProducerMenuAllStubs;
        static std::vector<uint8_t*> g_ProducerMenuFreeStubs;
        static std::unordered_set<const BuildItem*> g_ProducerMenuOverflowLogged;

        static bool InitBuildItemGuarded(BuildItem* item, int64_t token)
        {
            __try
            {
                g_BzrFn_InitBuildItem(*item, token);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // A [Builder] that lists itself recurses until the stack runs
                // out; the guard page has to be restored before continuing.
                if (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW)
                    _resetstkoflw();
                return false;
            }
        }

        static bool CleanupBuildItemGuarded(BuildItem* item)
        {
            __try
            {
                g_BzrFn_CleanupBuildItem(*item);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void CountProducerMenuTree(const BuildItem* node, unsigned depth,
                                          unsigned& leaves, unsigned& menus, unsigned& maxDepth)
        {
            if (!node || !node->menu)
                return;
            maxDepth = (std::max)(maxDepth, depth);
            for (size_t i = 0; i < kBuildItemChildCount; ++i)
            {
                const BuildItem& child = node->menu[i];
                if (child.menu)
                {
                    ++menus;
                    CountProducerMenuTree(&child, depth + 1, leaves, menus, maxDepth);
                }
                else if (child.item)
                {
                    ++leaves;
                }
            }
        }

        static ProducerMenuTree* BuildProducerMenuTree(const ProducerBuildMenuEntry& rootEntry)
        {
            auto* tree = new (std::nothrow) ProducerMenuTree{};
            if (!tree)
                return nullptr;
            strncpy_s(tree->token, rootEntry.token, _TRUNCATE);
            tree->root.parent = &tree->anchor;

            // Build as ControlPanel::PostLoad does: with the class loader's
            // asset preload off, so a mid-mission build does not load meshes.
            const uint8_t savedPreload = *g_BzrPtr_ClassLoadAssetsFlag;
            *g_BzrPtr_ClassLoadAssetsFlag = 0;
            const bool built = InitBuildItemGuarded(&tree->root, rootEntry.packedToken);
            *g_BzrPtr_ClassLoadAssetsFlag = savedPreload;

            if (!built)
            {
                // The engine's allocations may be half made; leak them rather
                // than free a tree of unknown shape.
                Log(L"[PRODMENU] Menu root %hs faulted while loading (a [Builder] that contains itself?); producers using it keep their stock list\n",
                    tree->token);
                return nullptr;
            }
            if (!tree->root.menu)
            {
                Log(L"[PRODMENU] Menu root %hs is not a [Builder] ODF; producers using it keep their stock list\n",
                    tree->token);
                delete tree;
                return nullptr;
            }

            unsigned leaves = 0;
            unsigned menus = 0;
            unsigned depth = 0;
            CountProducerMenuTree(&tree->root, 1, leaves, menus, depth);
            Log(L"[PRODMENU] Menu root %hs loaded: %u buildable, %u submenus, depth %u\n",
                tree->token, leaves, menus, depth);
            return tree;
        }

        static void ReleaseProducerMenuTrees()
        {
            for (auto& entry : g_ProducerMenuTrees)
            {
                ProducerMenuTree* tree = entry.second;
                if (!tree)
                    continue;
                CleanupBuildItemGuarded(&tree->root);
                delete tree;
            }
            g_ProducerMenuTrees.clear();
            g_ProducerMenuCursors.clear();
            g_ProducerMenuOverflowLogged.clear();

            for (auto& entry : g_ProducerMenuNodeStubs)
            {
                memset(entry.second, 0, kMenuStubSize);
                g_ProducerMenuFreeStubs.push_back(entry.second);
            }
            g_ProducerMenuNodeStubs.clear();
            g_ProducerMenuStubNodes.clear();
        }

        static uint8_t* GetProducerMenuStub(const BuildItem* node)
        {
            const auto found = g_ProducerMenuNodeStubs.find(node);
            if (found != g_ProducerMenuNodeStubs.end())
                return found->second;

            uint8_t* stub = nullptr;
            if (!g_ProducerMenuFreeStubs.empty())
            {
                stub = g_ProducerMenuFreeStubs.back();
                g_ProducerMenuFreeStubs.pop_back();
            }
            else
            {
                stub = static_cast<uint8_t*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, kMenuStubSize));
                if (!stub)
                    return nullptr;
                g_ProducerMenuAllStubs.insert(reinterpret_cast<uintptr_t>(stub));
            }

            char* label = reinterpret_cast<char*>(stub + kMenuStubLabelOffset);
            const size_t nameLength = strnlen(node->name, sizeof(node->name));
            if (nameLength == 0)
                memcpy(label, "Menu", 5);
            else
                memcpy(label, node->name, (std::min)(nameLength, kMenuStubLabelMax));

            g_ProducerMenuNodeStubs[node] = stub;
            g_ProducerMenuStubNodes[reinterpret_cast<uintptr_t>(stub)] = node;
            return stub;
        }

        static bool IsProducerMenuStub(int mode)
        {
            const uint32_t value = static_cast<uint32_t>(mode);
            return value > kModeLastNamed &&
                g_ProducerMenuAllStubs.count(static_cast<uintptr_t>(value)) != 0;
        }

        // --- Objects ------------------------------------------------------------

        static void* const* ObjectVtable(void* self)
        {
            return *static_cast<void* const* const*>(self);
        }

        static bool VtableSlotIs(void* self, size_t index, const void* expected)
        {
            return ObjectVtable(self)[index] == expected;
        }

        static ProducerBuildMenuKind ClassifyProducerBuildMenuKind(void* self)
        {
            const void* vtable = ObjectVtable(self);
            if (vtable == g_BzrVtbl_Recycler)
                return ProducerBuildMenuKind::Recycler;
            if (vtable == g_BzrVtbl_Factory)
                return ProducerBuildMenuKind::Factory;
            if (vtable == g_BzrVtbl_ConstructionRig)
                return ProducerBuildMenuKind::ConstructionRig;
            return ProducerBuildMenuKind::Producer;
        }

        static void** ProducerBuildList(void* self)
        {
            uint8_t* const producerClass =
                *reinterpret_cast<uint8_t**>(static_cast<uint8_t*>(self) + kObjectClassOffset);
            if (!producerClass)
                return nullptr;
            return reinterpret_cast<void**>(producerClass + kProducerClassBuildListOffset);
        }

        static int ProducerDeployState(void* self)
        {
            return *reinterpret_cast<const int*>(static_cast<uint8_t*>(self) + kCraftDeployStateOffset);
        }

        static ProducerMenuTree* ProducerMenuTreeFor(void* self)
        {
            LoadProducerBuildMenuConfig();
            if (!g_ProducerBuildMenuConfig.enabled)
                return nullptr;

            char producerOdf[kProducerBuildMenuTokenLen + 1] = {};
            if (!TryGetObjectOdfToken(self, producerOdf))
                return nullptr;

            const ProducerBuildMenuEntry rootEntry =
                SelectProducerBuildMenuEntry(producerOdf, ClassifyProducerBuildMenuKind(self));
            if (!rootEntry.hasValue)
                return nullptr;

            const auto found = g_ProducerMenuTrees.find(rootEntry.token);
            if (found != g_ProducerMenuTrees.end())
                return found->second;

            ProducerMenuTree* tree = BuildProducerMenuTree(rootEntry);
            g_ProducerMenuTrees[rootEntry.token] = tree;
            if (tree)
                Log(L"[PRODMENU] %hs uses menu root %hs\n", producerOdf, tree->token);
            return tree;
        }

        static bool ProducerMenuTreeContains(const ProducerMenuTree* tree, const BuildItem* node)
        {
            for (const BuildItem* at = node; at; at = at->parent)
            {
                if (at == &tree->root)
                    return true;
            }
            return false;
        }

        // The page an object is on; a stale cursor (another tree, or an object
        // at a reused address) falls back to the root.
        static const BuildItem* ProducerMenuNodeFor(void* self, const ProducerMenuTree* tree)
        {
            const auto found = g_ProducerMenuCursors.find(self);
            if (found == g_ProducerMenuCursors.end())
                return &tree->root;
            if (ProducerMenuTreeContains(tree, found->second))
                return found->second;
            g_ProducerMenuCursors.erase(found);
            return &tree->root;
        }

        static void SetProducerMenuNode(void* self, const ProducerMenuTree* tree, const BuildItem* node)
        {
            if (node == &tree->root)
                g_ProducerMenuCursors.erase(self);
            else
                g_ProducerMenuCursors[self] = node;
        }

        // --- Pages --------------------------------------------------------------

        struct ProducerMenuPage
        {
            bool atRoot = true;
            bool browsable = false;
            void* classes[kProducerClassBuildListCount] = {};
            uint8_t* stubs[kProducerClassBuildListCount] = {};
        };

        // Lays out one page: children in file order with empty entries
        // skipped, leaves as their class and submenus as their stub. Returns
        // false when the object keeps its stock list.
        static bool TryComposeProducerMenuPage(void* self, const ProducerMenuLayout& layout,
                                               const void* setActiveModeHook, ProducerMenuPage& page)
        {
            if (!g_ProducerMenuSessionActive)
                return false;
            // Only emit stubs where this class's SetActiveMode is ours: the
            // stock one would turn a stub into a build order.
            if (!VtableSlotIs(self, kVtableSetActiveModeIndex, setActiveModeHook))
                return false;

            const int state = ProducerDeployState(self);
            if (state == 0 && !layout.listShownWhenMobile)
                return false;

            ProducerMenuTree* tree = ProducerMenuTreeFor(self);
            if (!tree)
                return false;

            const BuildItem* node = ProducerMenuNodeFor(self, tree);
            page.atRoot = (node == &tree->root);
            page.browsable = (state == layout.buildState);

            const size_t positions = page.atRoot ? layout.capacity : layout.capacity - 1;
            size_t used = 0;
            size_t dropped = 0;
            for (size_t i = 0; i < kBuildItemChildCount; ++i)
            {
                const BuildItem& child = node->menu[i];
                const bool isMenu = child.menu != nullptr;
                if (!isMenu && !child.item)
                    continue;
                if (used == positions)
                {
                    ++dropped;
                    continue;
                }
                if (isMenu)
                {
                    uint8_t* stub = GetProducerMenuStub(&child);
                    if (!stub)
                        continue;
                    page.stubs[used] = stub;
                }
                else
                {
                    page.classes[used] = child.item;
                }
                ++used;
            }

            if (dropped && g_ProducerMenuOverflowLogged.insert(node).second)
            {
                Log(L"[PRODMENU] Menu %hs page \"%.16hs\" has %u more entries than the %u buttons it gets; the extra ones are not shown\n",
                    tree->token, node->name, static_cast<unsigned>(dropped), static_cast<unsigned>(positions));
            }
            return true;
        }

        // Runs the stock UpdateModeList with the page's classes standing in for
        // the class's flat build list, so the stock code prices and enables
        // every leaf. The list belongs to the class, shared by every producer of
        // that ODF, and is put back before anything else can read it.
        static void RunUpdateModeListWithPage(FnModeListUpdate original, void* self, void** buildList,
                                              void* const* pageClasses)
        {
            void* saved[kProducerClassBuildListCount];
            memcpy(saved, buildList, sizeof(saved));
            memcpy(buildList, pageClasses, sizeof(saved));
            __try
            {
                original(self);
            }
            __finally
            {
                memcpy(buildList, saved, sizeof(saved));
            }
        }

        static void OverlayProducerMenuPage(void* self, const ProducerMenuLayout& layout, const ProducerMenuPage& page)
        {
            void* const modeList = static_cast<uint8_t*>(self) + kObjectModeListOffset;
            const int enabled = page.browsable ? 1 : 0;
            for (size_t i = 0; i < layout.capacity; ++i)
            {
                if (page.stubs[i])
                {
                    g_BzrFn_ModeListSetMode(modeList, layout.firstSlot + static_cast<int>(i),
                        static_cast<int>(reinterpret_cast<uintptr_t>(page.stubs[i])), enabled);
                }
            }
            if (!page.atRoot)
            {
                g_BzrFn_ModeListSetMode(modeList, layout.firstSlot + static_cast<int>(layout.capacity) - 1,
                    kModeBack, enabled);
            }
        }

        static void RunProducerMenuUpdateModeList(void* self, const ProducerMenuLayout& layout,
                                                  FnModeListUpdate original, const void* setActiveModeHook)
        {
            if (!original)
                return;
            ProducerMenuPage page;
            void** const buildList = ProducerBuildList(self);
            if (!buildList || !TryComposeProducerMenuPage(self, layout, setActiveModeHook, page))
            {
                original(self);
                return;
            }
            RunUpdateModeListWithPage(original, self, buildList, page.classes);
            OverlayProducerMenuPage(self, layout, page);
        }

        static void RefreshProducerModeList(void* self)
        {
            const auto update = reinterpret_cast<FnModeListUpdate>(ObjectVtable(self)[kVtableUpdateModeListIndex]);
            update(self);
        }

        // Handles the menu's own buttons. Returns true when the mode was a
        // menu action, which SetActiveMode then reports as false so the panel
        // stays open, as the Armory's category pages do.
        static bool TryHandleProducerMenuMode(void* self, int mode)
        {
            if (IsProducerMenuStub(mode))
            {
                const auto found = g_ProducerMenuStubNodes.find(static_cast<uintptr_t>(static_cast<uint32_t>(mode)));
                if (found == g_ProducerMenuStubNodes.end() || !g_ProducerMenuSessionActive)
                    return true;
                ProducerMenuTree* tree = ProducerMenuTreeFor(self);
                if (!tree || !ProducerMenuTreeContains(tree, found->second))
                    return true;
                SetProducerMenuNode(self, tree, found->second);
                RefreshProducerModeList(self);
                Log(L"[PRODMENU] Opened \"%.16hs\" in menu %hs\n", found->second->name, tree->token);
                return true;
            }

            if (mode == kModeBack && g_ProducerMenuSessionActive)
            {
                ProducerMenuTree* tree = ProducerMenuTreeFor(self);
                if (!tree)
                    return false;
                const BuildItem* node = ProducerMenuNodeFor(self, tree);
                if (node == &tree->root)
                    return false;
                SetProducerMenuNode(self, tree, node->parent);
                RefreshProducerModeList(self);
                return true;
            }
            return false;
        }

        void ResetProducerBuildMenuRuntime()
        {
            g_ProducerMenuSessionActive = false;
            ReleaseProducerMenuTrees();
        }
    }

    using namespace Hooks;

    void __fastcall ProducerUpdateModeListHook(void* self, void* /*edx*/)
    {
        RunProducerMenuUpdateModeList(self, kProducerFamilyLayout, g_BzrFn_ProducerUpdateModeList,
            reinterpret_cast<const void*>(&ProducerSetActiveModeHook));
    }

    bool __fastcall ProducerSetActiveModeHook(void* self, void* /*edx*/, int mode)
    {
        if (TryHandleProducerMenuMode(self, mode))
            return false;
        return g_BzrFn_ProducerSetActiveMode ? g_BzrFn_ProducerSetActiveMode(self, mode) : true;
    }

    void __fastcall ProducerDeselectHook(void* self, void* /*edx*/)
    {
        g_ProducerMenuCursors.erase(self);
        if (g_BzrFn_GameObjectDeselect)
            g_BzrFn_GameObjectDeselect(self);
    }

    void __fastcall ConstructionRigUpdateModeListHook(void* self, void* /*edx*/)
    {
        RunProducerMenuUpdateModeList(self, kConstructionRigLayout, g_BzrFn_ConstructionRigUpdateModeList,
            reinterpret_cast<const void*>(&ConstructionRigSetActiveModeHook));
    }

    bool __fastcall ConstructionRigSetActiveModeHook(void* self, void* /*edx*/, int mode)
    {
        if (TryHandleProducerMenuMode(self, mode))
            return false;
        return g_BzrFn_ConstructionRigSetActiveMode ? g_BzrFn_ConstructionRigSetActiveMode(self, mode) : true;
    }

    void __fastcall ConstructionRigDeselectHook(void* self, void* /*edx*/)
    {
        g_ProducerMenuCursors.erase(self);
        if (g_BzrFn_ConstructionRigDeselect)
            g_BzrFn_ConstructionRigDeselect(self);
    }

    void __fastcall ControlPanelPostLoadHook(void* self, void* /*edx*/)
    {
        if (g_BzrFn_ControlPanelPostLoad)
            g_BzrFn_ControlPanelPostLoad(self);
        // Trees from a mission whose Cleanup never ran would name freed classes.
        ReleaseProducerMenuTrees();
        // Without the Cleanup hook nothing would drop the trees before the
        // engine frees their classes, so the menus stay off.
        g_ProducerMenuSessionActive =
            VtableSlotIs(self, kControlPanelCleanupIndex, reinterpret_cast<const void*>(&ControlPanelCleanupHook));
        Log(L"[PRODMENU] Mission menus %hs\n",
            g_ProducerMenuSessionActive ? "open" : "stay closed: the ControlPanel cleanup slot is not hooked");
    }

    void __fastcall ControlPanelCleanupHook(void* self, void* /*edx*/)
    {
        if (g_ProducerMenuSessionActive)
            Log(L"[PRODMENU] Mission menus closed; %u tree(s) released\n",
                static_cast<unsigned>(g_ProducerMenuTrees.size()));
        g_ProducerMenuSessionActive = false;
        ReleaseProducerMenuTrees();
        if (g_BzrFn_ControlPanelCleanup)
            g_BzrFn_ControlPanelCleanup(self);
    }

    namespace
    {
        struct ProducerMenuPatchRow
        {
            const char* name;
            const void* hook;
        };

        const ProducerMenuPatchRow* ProducerMenuPatchRows(size_t& count)
        {
            static const ProducerMenuPatchRow kRows[] = {
                {"Producer UpdateModeList VTable Hook", reinterpret_cast<const void*>(&ProducerUpdateModeListHook)},
                {"Recycler UpdateModeList VTable Hook", reinterpret_cast<const void*>(&ProducerUpdateModeListHook)},
                {"Factory UpdateModeList VTable Hook", reinterpret_cast<const void*>(&ProducerUpdateModeListHook)},
                {"Producer SetActiveMode VTable Hook", reinterpret_cast<const void*>(&ProducerSetActiveModeHook)},
                {"Recycler SetActiveMode VTable Hook", reinterpret_cast<const void*>(&ProducerSetActiveModeHook)},
                {"Factory SetActiveMode VTable Hook", reinterpret_cast<const void*>(&ProducerSetActiveModeHook)},
                {"Producer Deselect VTable Hook", reinterpret_cast<const void*>(&ProducerDeselectHook)},
                {"Recycler Deselect VTable Hook", reinterpret_cast<const void*>(&ProducerDeselectHook)},
                {"Factory Deselect VTable Hook", reinterpret_cast<const void*>(&ProducerDeselectHook)},
                {"ConstructionRig UpdateModeList VTable Hook", reinterpret_cast<const void*>(&ConstructionRigUpdateModeListHook)},
                {"ConstructionRig SetActiveMode VTable Hook", reinterpret_cast<const void*>(&ConstructionRigSetActiveModeHook)},
                {"ConstructionRig Deselect VTable Hook", reinterpret_cast<const void*>(&ConstructionRigDeselectHook)},
                {"ControlPanel PostLoad VTable Hook", reinterpret_cast<const void*>(&ControlPanelPostLoadHook)},
                {"ControlPanel Cleanup VTable Hook", reinterpret_cast<const void*>(&ControlPanelCleanupHook)},
            };
            count = sizeof(kRows) / sizeof(kRows[0]);
            return kRows;
        }
    }

    bool IsProducerBuildMenuPatchName(const char* name)
    {
        return ProducerBuildMenuPatchTarget(name) != 0;
    }

    uint32_t ProducerBuildMenuPatchTarget(const char* name)
    {
        if (!name)
            return 0;
        size_t count = 0;
        const ProducerMenuPatchRow* rows = ProducerMenuPatchRows(count);
        for (size_t i = 0; i < count; ++i)
        {
            if (strcmp(rows[i].name, name) == 0)
                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rows[i].hook));
        }
        return 0;
    }
}
