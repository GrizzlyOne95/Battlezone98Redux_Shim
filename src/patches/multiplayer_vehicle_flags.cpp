// multiplayer_vehicle_flags.cpp
// BZR Open Shim - multiplayer vehicle flags: flag payload staging as TGA
// resources, the Ogre billboard set per team, the FlagDisplay::Submit hook
// with its sim-tick fallback, and the FLAGDIAG dumps, split out of
// bzr_hooks.cpp.
#include "bzr_hooks.h"
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
    namespace Hooks
    {
        // Master switch for the whole multiplayer vehicle-flag feature: the
        // flag-selection UI, the payload upload and the Ogre renderer hook.
        // [Display] MultiplayerFlags in openshim.ini, defaulting OFF so a
        // missing key does not grow widgets onto BZP/BZP-T's faction-only
        // waiting room. The legacy disable variables remain an override.
        // Latched, because the renderer hook is a vtable write that is only
        // attempted while the feature is on.
        bool ShouldEnableMultiplayerFlagUi()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                bool enabled = false;
                bool iniValue = false;
                if (EnvFlagEnabled("OPENSHIM_DISABLE_MP_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_DISABLE_MULTIPLAYER_FLAG_UI") ||
                    EnvFlagEnabled("OPENSHIM_DISABLE_MP_FLAGS") ||
                    EnvFlagEnabled("BZR_DISABLE_MP_FLAG_UI"))
                {
                    enabled = false;
                }
                else if (TryGetUserConfigBool("Display", "MultiplayerFlags", iniValue))
                {
                    enabled = iniValue;
                }
                s_cached = enabled ? 1 : 0;
                Log(L"[FLAG] multiplayer vehicle flags: %hs\n",
                    enabled ? "enabled" : "disabled");
            }
            return s_cached != 0;
        }

        constexpr uintptr_t kFlagDisplaySubmitVtableSlotAddr = 0x008799A4;

        constexpr uintptr_t kFlagDisplaySubmitAddr = 0x004D1C80;

        constexpr uintptr_t kNetPlayerGetDataAddr = 0x00575510;

        constexpr uintptr_t kGameObjectGetSphereAddr = 0x00462400;

        constexpr size_t kNetPlayerFlagBufferOffset = 0x1C;

        constexpr uint32_t kFlagObjectExcludedStateMask = 0x600;

        constexpr float kMultiplayerFlagRange = 100.0f;

        constexpr float kMultiplayerFlagWidth = 2.0f;

        constexpr float kMultiplayerFlagHeight = 1.0f;

        constexpr float kMultiplayerFlagMinimumLift = 1.5f;

        constexpr float kMultiplayerFlagHiddenY = -100000.0f;

        bool g_FlagPayloadReady = false;

        bool g_FlagApplyPending = false;

        using FnNetPlayerGetData = void*(__thiscall*)(void*, uint32_t);

        using FnGameObjectGetSphere = void*(__thiscall*)(void*);

        // Live-dispatch diagnostics: whether Redux ever calls the hooked
        // FlagDisplay::Submit vtable slot, and one-time renderer gate logs so
        // a session log shows exactly which stage the flag pipeline reached.
        static volatile ULONGLONG g_MultiplayerFlagSubmitLastTick = 0;

        static bool g_MultiplayerFlagSubmitObservedLogged = false;

        static bool g_MultiplayerFlagTickFallbackLogged = false;

        static bool g_MultiplayerFlagPayloadSeenLogged = false;

        static bool g_MultiplayerFlagContextMissingLogged = false;

        static bool g_MultiplayerFlagDiagLogged = false;

        static bool g_MultiplayerFlagObjScanLogged = false;

        static bool g_MultiplayerFlagInMatchApplyLogged = false;

        static bool g_MultiplayerFlagCopyFailLogged = false;

        static ULONGLONG g_MultiplayerFlagLastApplyAttemptTick = 0;

        constexpr ULONGLONG kMultiplayerFlagSubmitStaleMs = 2000;

        constexpr ULONGLONG kMultiplayerFlagApplyRetryMs = 500;

        static uint64_t HashMultiplayerFlagPayload(const uint8_t* data, size_t size)
        {
            uint64_t hash = 1469598103934665603ull;
            for (size_t i = 0; i < size; ++i)
            {
                hash ^= data[i];
                hash *= 1099511628211ull;
            }
            return hash ? hash : 1ull;
        }

        static bool TryCopyMultiplayerFlagPayload(
            void* netPlayer,
            std::array<uint8_t, kLegacyFlagPayloadBytes>& outPayload)
        {
            outPayload.fill(0);
            if (!netPlayer)
                return false;

            auto getData = reinterpret_cast<FnNetPlayerGetData>(kNetPlayerGetDataAddr);
            __try
            {
                if (getData)
                {
                    auto* vectorBytes = reinterpret_cast<uint8_t*>(
                        getData(netPlayer, kLegacyFlagDataSlot));
                    if (vectorBytes)
                    {
                        const auto* begin = *reinterpret_cast<uint8_t* const*>(vectorBytes + 0x0);
                        const auto* end = *reinterpret_cast<uint8_t* const*>(vectorBytes + 0x4);
                        if (begin && end && end >= begin &&
                            static_cast<size_t>(end - begin) == outPayload.size())
                        {
                            std::memcpy(outPayload.data(), begin, outPayload.size());
                            return true;
                        }
                    }
                }

                const auto* flagBuffer = *reinterpret_cast<uint8_t* const*>(
                    reinterpret_cast<const uint8_t*>(netPlayer) + kNetPlayerFlagBufferOffset);
                if (flagBuffer)
                {
                    std::memcpy(outPayload.data(), flagBuffer, outPayload.size());
                    return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return false;
        }

        static bool WriteMultiplayerFlagTga(
            const std::filesystem::path& path,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload)
        {
            FILE* file = nullptr;
            if (fopen_s(&file, path.string().c_str(), "wb") != 0 || !file)
                return false;

            uint8_t header[18] = {};
            header[2] = 2; // uncompressed true-colour
            header[12] = static_cast<uint8_t>(kLegacyFlagWidth & 0xFF);
            header[13] = static_cast<uint8_t>((kLegacyFlagWidth >> 8) & 0xFF);
            header[14] = static_cast<uint8_t>(kLegacyFlagHeight & 0xFF);
            header[15] = static_cast<uint8_t>((kLegacyFlagHeight >> 8) & 0xFF);
            header[16] = 32;
            header[17] = 8; // eight alpha bits, bottom-left origin like the BMP payload

            bool ok = std::fwrite(header, 1, sizeof(header), file) == sizeof(header);
            for (int y = 0; ok && y < kLegacyFlagHeight; ++y)
            {
                for (int x = 0; x < kLegacyFlagWidth; ++x)
                {
                    const uint8_t packed = payload[
                        static_cast<size_t>(y) * kLegacyFlagRowBytes + static_cast<size_t>(x / 8)];
                    const bool enabled = (packed & static_cast<uint8_t>(0x80u >> (x & 7))) != 0;
                    const uint8_t pixel[4] = { 0xFF, 0xFF, 0xFF, enabled ? 0xFFu : 0x00u };
                    ok = std::fwrite(pixel, 1, sizeof(pixel), file) == sizeof(pixel);
                    if (!ok)
                        break;
                }
            }
            std::fclose(file);
            return ok;
        }

        // POD-only SEH boundary for Ogre calls. Keep this separate from the
        // filesystem/string-owning caller so MSVC can unwind that caller.
        static bool InitialiseMultiplayerFlagResourceGroupSafe(
            FnOgreGetResourceGroupManager getResourceGroupManager,
            FnOgreResourceGroupExists resourceGroupExists,
            FnOgreCreateResourceGroup createResourceGroup,
            FnOgreAddResourceLocation addResourceLocation,
            FnOgreInitialiseResourceGroup initialiseResourceGroup,
            const std::string* directory,
            const std::string* group)
        {
            if (!getResourceGroupManager || !resourceGroupExists || !createResourceGroup ||
                !addResourceLocation || !initialiseResourceGroup || !directory || !group)
            {
                return false;
            }
            void* manager = getResourceGroupManager();
            if (!manager)
                return false;
            if (!resourceGroupExists(manager, *group))
            {
                createResourceGroup(manager, *group, false);
                addResourceLocation(manager, *directory, "FileSystem", *group, false, false);
                initialiseResourceGroup(manager, *group);
            }
            return true;
        }

        static bool EnsureMultiplayerFlagResourceFiles(
            MultiplayerFlagRenderSet& renderSet,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload)
        {
            if (renderSet.resourcesReady)
                return true;

            char suffix[32] = {};
            std::snprintf(suffix, sizeof(suffix), "%016llx",
                static_cast<unsigned long long>(renderSet.payloadHash));
            renderSet.materialName = std::string("OpenShimFlag_") + suffix;
            renderSet.resourceGroup = std::string("OpenShimFlagGroup_") + suffix;
            renderSet.resourceDirectory =
                GetGeneratedFlagsDirectoryPath() / "runtime" / suffix;

            std::error_code ec;
            std::filesystem::create_directories(renderSet.resourceDirectory, ec);
            if (ec)
                return false;

            const auto texturePath = renderSet.resourceDirectory / "flag.tga";
            const auto materialPath = renderSet.resourceDirectory / "flag.material";
            if (!std::filesystem::exists(texturePath, ec) &&
                !WriteMultiplayerFlagTga(texturePath, payload))
            {
                return false;
            }

            if (!std::filesystem::exists(materialPath, ec))
            {
                FILE* material = nullptr;
                if (fopen_s(&material, materialPath.string().c_str(), "w") != 0 || !material)
                    return false;
                std::fprintf(material,
                    "material %s\n"
                    "{\n"
                    "  technique\n"
                    "  {\n"
                    "    pass\n"
                    "    {\n"
                    "      lighting off\n"
                    "      scene_blend alpha_blend\n"
                    "      depth_check on\n"
                    "      depth_write off\n"
                    "      cull_hardware none\n"
                    "      cull_software none\n"
                    "      texture_unit\n"
                    "      {\n"
                    "        texture flag.tga\n"
                    "        filtering none\n"
                    "      }\n"
                    "    }\n"
                    "  }\n"
                    "}\n",
                    renderSet.materialName.c_str());
                std::fclose(material);
            }

            auto getResourceGroupManager = ResolveOgreProc<FnOgreGetResourceGroupManager>(
                "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
            auto resourceGroupExists = ResolveOgreProc<FnOgreResourceGroupExists>(
                "?resourceGroupExists@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            auto createResourceGroup = ResolveOgreProc<FnOgreCreateResourceGroup>(
                "?createResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            auto addResourceLocation = ResolveOgreProc<FnOgreAddResourceLocation>(
                "?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
            auto initialiseResourceGroup = ResolveOgreProc<FnOgreInitialiseResourceGroup>(
                "?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            if (!getResourceGroupManager || !resourceGroupExists || !createResourceGroup ||
                !addResourceLocation || !initialiseResourceGroup)
            {
                return false;
            }

            const std::string resourceDirectory = renderSet.resourceDirectory.string();
            try
            {
                if (!InitialiseMultiplayerFlagResourceGroupSafe(
                        getResourceGroupManager,
                        resourceGroupExists,
                        createResourceGroup,
                        addResourceLocation,
                        initialiseResourceGroup,
                        &resourceDirectory,
                        &renderSet.resourceGroup))
                {
                    return false;
                }
            }
            catch (const std::exception& ex)
            {
                Log(L"[FLAG] Ogre resource initialization failed material=%hs error=%hs\n",
                    renderSet.materialName.c_str(), ex.what());
                return false;
            }
            catch (...)
            {
                Log(L"[FLAG] Ogre resource initialization failed material=%hs (unknown exception)\n",
                    renderSet.materialName.c_str());
                return false;
            }
            renderSet.resourcesReady = true;

            Log(L"[FLAG] Ogre resources ready hash=%hs material=%hs group=%hs path=%hs\n",
                suffix,
                renderSet.materialName.c_str(),
                renderSet.resourceGroup.c_str(),
                renderSet.resourceDirectory.string().c_str());
            return true;
        }

        void ForgetMultiplayerFlagSceneResources(const wchar_t* reason)
        {
            // Re-arm the one-shot per-match diagnostics/logs for the next match.
            g_MultiplayerFlagDiagLogged = false;
            g_MultiplayerFlagObjScanLogged = false;
            g_MultiplayerFlagPayloadSeenLogged = false;
            g_MultiplayerFlagContextMissingLogged = false;
            g_MultiplayerFlagInMatchApplyLogged = false;
            g_MultiplayerFlagCopyFailLogged = false;
            g_MultiplayerFlagLastApplyAttemptTick = 0;
            size_t forgotten = 0;
            for (auto& pair : g_MultiplayerFlagRenderSets)
            {
                MultiplayerFlagRenderSet& renderSet = pair.second;
                if (renderSet.billboardSet || !renderSet.billboards.empty())
                    ++forgotten;
                renderSet.sceneManager = nullptr;
                renderSet.billboardSet = nullptr;
                renderSet.billboards.clear();
                renderSet.usedBillboards = 0;
            }
            if (forgotten > 0)
            {
                Log(L"[FLAG] Scene teardown (%ls): forgot %zu flag billboard set(s)\n",
                    reason ? reason : L"<none>", forgotten);
            }
        }

        static bool EnsureMultiplayerFlagBillboardSet(MultiplayerFlagRenderSet& renderSet)
        {
            void* sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return false;
            if (renderSet.billboardSet && renderSet.sceneManager == sceneManager)
                return true;

            renderSet.sceneManager = nullptr;
            renderSet.billboardSet = nullptr;
            renderSet.billboards.clear();
            renderSet.usedBillboards = 0;

            auto getRootSceneNode = ResolveOgreProc<FnOgreGetRootSceneNode>(
                "?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
            auto createBillboardSet = ResolveOgreProc<FnOgreCreateBillboardSet>(
                "?createBillboardSet@SceneManager@Ogre@@UAEPAVBillboardSet@2@I@Z");
            auto attachObject = ResolveOgreProc<FnOgreAttachObject>(
                "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            auto setWorldSpace = ResolveOgreProc<FnOgreSetBillboardsInWorldSpace>(
                "?setBillboardsInWorldSpace@BillboardSet@Ogre@@UAEX_N@Z");
            auto setDimensions = ResolveOgreProc<FnOgreSetDefaultDimensions>(
                "?setDefaultDimensions@BillboardSet@Ogre@@UAEXMM@Z");
            auto setMaterialName = ResolveOgreProc<FnOgreSetBillboardMaterialName>(
                "?setMaterialName@BillboardSet@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            if (!getRootSceneNode || !createBillboardSet || !attachObject ||
                !setWorldSpace || !setDimensions || !setMaterialName)
            {
                return false;
            }

            __try
            {
                void* rootNode = getRootSceneNode(sceneManager);
                void* billboardSet = createBillboardSet(sceneManager, 16);
                if (!rootNode || !billboardSet)
                    return false;
                setWorldSpace(billboardSet, true);
                setDimensions(billboardSet, kMultiplayerFlagWidth, kMultiplayerFlagHeight);
                setMaterialName(billboardSet, renderSet.materialName, renderSet.resourceGroup);
                attachObject(rootNode, billboardSet);
                renderSet.sceneManager = sceneManager;
                renderSet.billboardSet = billboardSet;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                renderSet.sceneManager = nullptr;
                renderSet.billboardSet = nullptr;
                return false;
            }
        }

        static bool IsMultiplayerFlagEligibleObject(void* gameObject)
        {
            if (!gameObject)
                return false;
            __try
            {
                const auto* bytes = reinterpret_cast<const uint8_t*>(gameObject);
                const auto* objectClass = *reinterpret_cast<uint8_t* const*>(
                    bytes + kGameObjectClassOffset);
                const auto* obj = *reinterpret_cast<uint8_t* const*>(
                    bytes + kGameObjectObjOffset);
                if (!objectClass || !obj)
                    return false;
                const int classType = *reinterpret_cast<const int*>(
                    objectClass + kObjectClassTypeOffset);
                if (classType != 1 && classType != 2 && classType != 4 && classType != 6)
                    return false;
                const uint32_t stateFlags = *reinterpret_cast<const uint32_t*>(
                    obj + kObjStateFlagsOffset);
                return (stateFlags & kFlagObjectExcludedStateMask) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static float GetMultiplayerFlagObjectLift(void* gameObject)
        {
            auto getSphere = reinterpret_cast<FnGameObjectGetSphere>(kGameObjectGetSphereAddr);
            if (!gameObject || !getSphere)
                return kMultiplayerFlagMinimumLift;
            __try
            {
                const auto* sphere = reinterpret_cast<const uint8_t*>(getSphere(gameObject));
                if (!sphere)
                    return kMultiplayerFlagMinimumLift;
                const float radius = *reinterpret_cast<const float*>(sphere + 0x0C);
                if (!std::isfinite(radius) || radius <= 0.0f || radius > 100.0f)
                    return kMultiplayerFlagMinimumLift;
                return (std::max)(radius, kMultiplayerFlagMinimumLift);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kMultiplayerFlagMinimumLift;
            }
        }

        static bool ConvertMultiplayerFlagPointToRenderSpace(float (&position)[3])
        {
            __try
            {
                const float* origin = reinterpret_cast<const float*>(kGogWorldRenderOriginAddr);
                position[0] -= origin[0];
                position[1] -= origin[1];
                position[2] = -position[2] - origin[2];
                return std::isfinite(position[0]) &&
                       std::isfinite(position[1]) &&
                       std::isfinite(position[2]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void HideUnusedMultiplayerFlagBillboards()
        {
            auto setPosition = ResolveOgreProc<FnOgreSetBillboardPosition>(
                "?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            if (!setPosition)
                return;
            for (auto& pair : g_MultiplayerFlagRenderSets)
            {
                MultiplayerFlagRenderSet& renderSet = pair.second;
                for (size_t i = renderSet.usedBillboards; i < renderSet.billboards.size(); ++i)
                {
                    __try
                    {
                        setPosition(renderSet.billboards[i], 0.0f, kMultiplayerFlagHiddenY, 0.0f);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                }
            }
        }

        static bool TryReadMultiplayerFlagRuntimeContext(
            void*& outUserObject,
            int& outLocalTeam)
        {
            outUserObject = nullptr;
            outLocalTeam = 0;
            // GameObject::userObject global 0x00917AFC — the exact value the
            // accessor 0x417C70 returns, which FlagDisplay::Submit itself
            // uses for its skip-own-craft compare. The previous userObject /
            // userTeamNumber globals (removed) were advisory-PDB drift into
            // string data ("Chat"), so every scan read garbage. Local team
            // comes from the object itself instead of a second unverified
            // global.
            void* userObject = TryGetHeadlightPlayerObject();
            if (!userObject || !IsLiveHeadlightObjectSlot(userObject))
                return false;
            const int team = GetGameObjectTeamForLog(userObject);
            if (team == INT_MIN)
                return false;
            outUserObject = userObject;
            outLocalTeam = team;
            return true;
        }

        static void* TryCreateMultiplayerFlagBillboardSafe(
            FnOgreCreateBillboard createBillboard,
            void* billboardSet,
            const OgreColourValue& colour)
        {
            if (!createBillboard || !billboardSet)
                return nullptr;
            __try
            {
                return createBillboard(
                    billboardSet, 0.0f, kMultiplayerFlagHiddenY, 0.0f, colour);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static bool TryUpdateMultiplayerFlagBillboardSafe(
            FnOgreSetBillboardColour setColour,
            FnOgreSetBillboardPosition setPosition,
            void* billboard,
            const OgreColourValue& colour,
            const float (&position)[3])
        {
            if (!setColour || !setPosition || !billboard)
                return false;
            __try
            {
                setColour(billboard, colour);
                setPosition(billboard, position[0], position[1], position[2]);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // One-shot per match: dump the by-team NetPlayer array and the local
        // (BanLookup) player so a single reload proves where the uploaded flag
        // mask actually lands and whether the two player views are the same
        // objects. Every field offset here is from the disassembly of
        // FlagDisplay::Submit (player+0x50 sprite index), NetPlayer::RecordDeath
        // (playerId +0x28), the by-team populate (team byte +0x68), and
        // SetFlagBuffer (mask ptr +0x1C).
        static void DumpMultiplayerFlagDiagnosticsOnce()
        {
            if (g_MultiplayerFlagDiagLogged)
                return;
            g_MultiplayerFlagDiagLogged = true;

            auto** playersByTeam = reinterpret_cast<void**>(kNetPlayerByTeamAddr);
            auto getData = reinterpret_cast<FnNetPlayerGetData>(kNetPlayerGetDataAddr);
            for (int team = 0; team < 16; ++team)
            {
                __try
                {
                    void* player = playersByTeam[team];
                    if (!player)
                        continue;
                    const auto* p = reinterpret_cast<const uint8_t*>(player);
                    const unsigned id = *reinterpret_cast<const uint16_t*>(p + 0x28);
                    const unsigned teamByte = *reinterpret_cast<const uint8_t*>(p + 0x68);
                    const int spriteIdx = *reinterpret_cast<const int*>(p + 0x50);
                    const void* flagBuf = *reinterpret_cast<void* const*>(p + 0x1C);
                    long slotSize = -1;
                    if (getData)
                    {
                        auto* v = reinterpret_cast<const uint8_t*>(getData(player, kLegacyFlagDataSlot));
                        if (v)
                        {
                            const auto* b = *reinterpret_cast<const uint8_t* const*>(v + 0x0);
                            const auto* e = *reinterpret_cast<const uint8_t* const*>(v + 0x4);
                            if (b && e && e >= b)
                                slotSize = static_cast<long>(e - b);
                        }
                    }
                    Log(L"[FLAGDIAG] byteam[%d]=0x%p id=%u teamByte=%u sprite=%d flagBuf=0x%p slot0x0D=%ld\n",
                        team, player, id, teamByte, spriteIdx, flagBuf, slotSize);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[FLAGDIAG] byteam[%d] read faulted\n", team);
                }
            }

            void* localPlayer = nullptr;
            if (TryGetLocalPlayerForFlags(localPlayer) && localPlayer)
            {
                __try
                {
                    const auto* p = reinterpret_cast<const uint8_t*>(localPlayer);
                    const unsigned id = *reinterpret_cast<const uint16_t*>(p + 0x28);
                    const unsigned teamByte = *reinterpret_cast<const uint8_t*>(p + 0x68);
                    const void* flagBuf = *reinterpret_cast<void* const*>(p + 0x1C);
                    void* arrayForTeam =
                        (teamByte < 16) ? playersByTeam[teamByte] : nullptr;
                    Log(L"[FLAGDIAG] localPlayer=0x%p id=%u teamByte=%u flagBuf=0x%p byteam[team]=0x%p same=%hs\n",
                        localPlayer, id, teamByte, flagBuf, arrayForTeam,
                        (arrayForTeam == localPlayer) ? "YES" : "NO");
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[FLAGDIAG] localPlayer read faulted\n");
                }
            }
            else
            {
                Log(L"[FLAGDIAG] no local player resolved (BanLookup)\n");
            }
        }

        // Object-list reachability, latched separately so it waits until the
        // local craft has actually spawned (the one-shot above fires on the
        // first render frame, often before objects exist). Isolates why the
        // render loop produces no flag: does the world scan work, is the user
        // object inside it, and what eligible craft/teams are present?
        static void DumpMultiplayerFlagObjectScanOnce()
        {
            if (g_MultiplayerFlagObjScanLogged)
                return;

            void* userObject = nullptr;
            int localTeam = 0;
            const bool ctxOk = TryReadMultiplayerFlagRuntimeContext(userObject, localTeam);
            if (!ctxOk || !userObject)
                return; // craft not spawned yet; try again next frame

            g_MultiplayerFlagObjScanLogged = true;

            static void* s_scanObjects[kHeadlightObjectSlotCount];
            const long totalObjects = static_cast<long>(
                CollectLiveGameObjectsFromArena(s_scanObjects, kHeadlightObjectSlotCount));
            Log(L"[FLAGDIAG] arena scan liveObjects=%ld userObject=0x%p localTeam=%d\n",
                totalObjects, userObject, localTeam);

            if (totalObjects <= 0)
                return;

            const long limit = totalObjects;
            long userFoundIndex = -1;
            long eligibleCount = 0;
            char teams[96] = {};
            size_t used = 0;
            for (long i = 0; i < limit; ++i)
            {
                void* obj = s_scanObjects[i];
                if (!obj)
                    continue;
                if (obj == userObject)
                    userFoundIndex = i;
                if (IsMultiplayerFlagEligibleObject(obj))
                {
                    ++eligibleCount;
                    const int t = GetGameObjectTeamForLog(obj);
                    if (used < sizeof(teams) - 10)
                        used += static_cast<size_t>(std::snprintf(
                            teams + used, sizeof(teams) - used, "%s%d%s",
                            used ? "," : "", t, (obj == userObject) ? "(self)" : ""));
                }
            }
            Log(L"[FLAGDIAG] userFoundIndex=%ld eligibleCount=%ld eligibleTeams=[%hs]\n",
                userFoundIndex, eligibleCount, teams);
        }

        // Opt-in (default off): also draw the local player's own flag over
        // their own craft. Legacy Submit and our renderer skip userObject, so
        // solo hosts see nothing; this lets a single player verify rendering
        // without a second human. [Display] MultiplayerFlagShowOwnCraft in
        // openshim.ini, or the OPENSHIM_MP_FLAG_SHOW_OWN env override.
        static bool ShouldShowOwnMultiplayerFlag()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                bool enabled = false;
                if (EnvFlagEnabled("OPENSHIM_MP_FLAG_SHOW_OWN") ||
                    EnvFlagEnabled("BZR_MP_FLAG_SHOW_OWN"))
                {
                    enabled = true;
                }
                else
                {
                    bool iniValue = false;
                    if (TryGetUserConfigBool(kUserConfigDisplaySection, "MultiplayerFlagShowOwnCraft", iniValue))
                        enabled = iniValue;
                }
                s_cached = enabled ? 1 : 0;
                Log(L"[FLAG] show-own-craft flag: %hs\n", enabled ? "enabled" : "disabled");
            }
            return s_cached != 0;
        }

        // The pending flag upload was historically driven only from the flag-
        // selection UI callback (UpdateFlagSelectionUiLabel), so once the local
        // player left that screen for the match, the deferred apply only fired
        // if they happened back onto the flag UI. Observed live 2026-07-18: the
        // match started ~9s before the apply landed, leaving it applied for
        // only ~3s before the world tore down, so the renderer never saw a
        // payload. Drive the apply from the in-match render tick (this runs
        // every frame via Submit or the sim-tick fallback) so the flag lands
        // the instant the local NetPlayer exists in the match, throttled so a
        // persistent failure does not hammer the engine every frame.
        static void MaybeDrivePendingFlagApplyInMatch()
        {
            if (!g_FlagApplyPending || !g_FlagPayloadReady)
                return;

            const ULONGLONG now = GetTickCount64();
            if (g_MultiplayerFlagLastApplyAttemptTick != 0 &&
                now - g_MultiplayerFlagLastApplyAttemptTick < kMultiplayerFlagApplyRetryMs)
                return;
            g_MultiplayerFlagLastApplyAttemptTick = now;

            void* localPlayer = nullptr;
            if (!TryGetLocalPlayerForFlags(localPlayer) || !localPlayer)
                return; // match player not spawned yet; retry next tick

            const bool applied = TryApplyCachedFlagPayload("match_tick");
            if (!applied)
                TryApplySelectedFlagThroughEngine("match_tick");

            if (!g_FlagApplyPending && !g_MultiplayerFlagInMatchApplyLogged)
            {
                g_MultiplayerFlagInMatchApplyLogged = true;
                // Re-arm the payload diagnostic so the next frame's one-shot
                // dump reflects the post-apply NetPlayer state (flagBuf / slot
                // 0x0D populated) instead of the stale pre-apply snapshot.
                g_MultiplayerFlagDiagLogged = false;
                Log(L"[FLAG] in-match tick applied pending flag payload player=0x%p\n",
                    localPlayer);
            }
        }

        // Raw diagnostic reads are isolated from the renderer because the
        // renderer owns Debug STL iterators/range-for state. Mixing those with
        // SEH in one function triggers MSVC C2712.
        static void DumpMultiplayerFlagCopyFailureDiagnostics(void** playersByTeam)
        {
            __try
            {
                void* p1 = playersByTeam ? playersByTeam[1] : nullptr;
                auto getData = reinterpret_cast<FnNetPlayerGetData>(kNetPlayerGetDataAddr);
                void* slotVec = (getData && p1) ? getData(p1, kLegacyFlagDataSlot) : nullptr;
                long slotSize = -1;
                if (slotVec)
                {
                    const auto* b = *reinterpret_cast<uint8_t* const*>(
                        reinterpret_cast<uint8_t*>(slotVec) + 0x0);
                    const auto* e = *reinterpret_cast<uint8_t* const*>(
                        reinterpret_cast<uint8_t*>(slotVec) + 0x4);
                    if (b && e && e >= b)
                        slotSize = static_cast<long>(e - b);
                }
                const void* flagBuf = p1
                    ? *reinterpret_cast<void* const*>(
                          reinterpret_cast<uint8_t*>(p1) + kNetPlayerFlagBufferOffset)
                    : nullptr;
                Log(L"[FLAGDIAG] applied but copy empty: byteam[1]=0x%p getData=0x%p slot0x0D=%ld flagBuf=0x%p\n",
                    p1, slotVec, slotSize, flagBuf);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[FLAGDIAG] applied but copy empty: raw read faulted\n");
            }
        }

        void RenderMultiplayerFlags(void* /*camera*/)
        {
            if (!ShouldEnableMultiplayerFlagUi())
                return;

            MaybeDrivePendingFlagApplyInMatch();
            DumpMultiplayerFlagDiagnosticsOnce();
            DumpMultiplayerFlagObjectScanOnce();

            for (auto& pair : g_MultiplayerFlagRenderSets)
                pair.second.usedBillboards = 0;

            std::array<uint64_t, 16> teamHashes = {};
            std::array<std::array<uint8_t, kLegacyFlagPayloadBytes>, 16> teamPayloads = {};
            auto** playersByTeam = reinterpret_cast<void**>(kNetPlayerByTeamAddr);
            bool anyTeamPayload = false;
            for (int team = 1; team < 16; ++team)
            {
                void* player = playersByTeam[team];
                if (!player || !TryCopyMultiplayerFlagPayload(player, teamPayloads[team]))
                    continue;
                teamHashes[team] = HashMultiplayerFlagPayload(
                    teamPayloads[team].data(), teamPayloads[team].size());
                anyTeamPayload = true;
            }
            if (anyTeamPayload && !g_MultiplayerFlagPayloadSeenLogged)
            {
                g_MultiplayerFlagPayloadSeenLogged = true;
                char teams[64] = {};
                size_t used = 0;
                for (int team = 1; team < 16; ++team)
                {
                    if (teamHashes[team] == 0)
                        continue;
                    used += static_cast<size_t>(std::snprintf(
                        teams + used, sizeof(teams) - used, "%s%d",
                        used ? "," : "", team));
                    if (used >= sizeof(teams) - 1)
                        break;
                }
                Log(L"[FLAG] renderer sees replicated flag payload(s) team(s)=%hs\n", teams);
            }

            // If a flag was applied (pending cleared) but the copy loop still
            // found nothing, the payload storage the renderer reads does not
            // match where the apply wrote. Dump the raw NetPlayer state once so
            // the failing path is unambiguous on the next test.
            if (!anyTeamPayload && g_FlagPayloadReady && !g_FlagApplyPending &&
                !g_MultiplayerFlagCopyFailLogged)
            {
                g_MultiplayerFlagCopyFailLogged = true;
                DumpMultiplayerFlagCopyFailureDiagnostics(playersByTeam);
            }

            void* userObject = nullptr;
            int localTeam = 0;
            float userPosition[3] = {};
            if (!TryReadMultiplayerFlagRuntimeContext(userObject, localTeam) ||
                !TryGetGameObjectWorldPosition(userObject, userPosition))
            {
                if (anyTeamPayload && !g_MultiplayerFlagContextMissingLogged)
                {
                    g_MultiplayerFlagContextMissingLogged = true;
                    Log(L"[FLAG] renderer has payload(s) but no local user object/position yet\n");
                }
                HideUnusedMultiplayerFlagBillboards();
                return;
            }

            // Skip the arena walk entirely on frames with nothing to draw.
            if (!anyTeamPayload)
            {
                HideUnusedMultiplayerFlagBillboards();
                return;
            }

            static void* s_renderObjects[kHeadlightObjectSlotCount];
            const size_t liveObjectCount =
                CollectLiveGameObjectsFromArena(s_renderObjects, kHeadlightObjectSlotCount);
            if (liveObjectCount == 0)
            {
                HideUnusedMultiplayerFlagBillboards();
                return;
            }

            auto createBillboard = ResolveOgreProc<FnOgreCreateBillboard>(
                "?createBillboard@BillboardSet@Ogre@@QAEPAVBillboard@2@MMMABVColourValue@2@@Z");
            auto setPosition = ResolveOgreProc<FnOgreSetBillboardPosition>(
                "?setPosition@Billboard@Ogre@@QAEXMMM@Z");
            auto setColour = ResolveOgreProc<FnOgreSetBillboardColour>(
                "?setColour@Billboard@Ogre@@QAEXABVColourValue@2@@Z");
            if (!createBillboard || !setPosition || !setColour)
            {
                HideUnusedMultiplayerFlagBillboards();
                return;
            }

            for (size_t i = 0; i < liveObjectCount; ++i)
            {
                void* gameObject = s_renderObjects[i];
                const bool isOwnCraft = (gameObject == userObject);
                if (!gameObject ||
                    (isOwnCraft && !ShouldShowOwnMultiplayerFlag()) ||
                    !IsMultiplayerFlagEligibleObject(gameObject))
                    continue;
                const int team = GetGameObjectTeamForLog(gameObject);
                if (team <= 0 || team >= 16 || teamHashes[team] == 0)
                    continue;

                float position[3] = {};
                if (!TryGetGameObjectWorldPosition(gameObject, position))
                    continue;
                const float dx = position[0] - userPosition[0];
                const float dy = position[1] - userPosition[1];
                const float dz = position[2] - userPosition[2];
                if ((dx * dx + dy * dy + dz * dz) >
                    (kMultiplayerFlagRange * kMultiplayerFlagRange))
                {
                    continue;
                }
                if (!HasTerrainLineOfSight(
                        userPosition[0], userPosition[1], userPosition[2],
                        position[0], position[1], position[2]))
                {
                    continue;
                }

                position[1] += GetMultiplayerFlagObjectLift(gameObject);
                if (!ConvertMultiplayerFlagPointToRenderSpace(position))
                    continue;

                const uint64_t hash = teamHashes[team];
                auto [it, inserted] = g_MultiplayerFlagRenderSets.try_emplace(hash);
                MultiplayerFlagRenderSet& renderSet = it->second;
                if (inserted)
                    renderSet.payloadHash = hash;
                if (!EnsureMultiplayerFlagResourceFiles(renderSet, teamPayloads[team]) ||
                    !EnsureMultiplayerFlagBillboardSet(renderSet))
                {
                    continue;
                }

                // Legacy used green for the local team and red for enemies.
                // The alpha-mask texture preserves each team's distinct pattern.
                const OgreColourValue colour =
                    (team == localTeam)
                        ? OgreColourValue{ 0.20f, 1.00f, 0.20f, 1.00f }
                        : OgreColourValue{ 1.00f, 0.20f, 0.20f, 1.00f };

                void* billboard = nullptr;
                if (renderSet.usedBillboards < renderSet.billboards.size())
                {
                    billboard = renderSet.billboards[renderSet.usedBillboards];
                }
                else
                {
                    billboard = TryCreateMultiplayerFlagBillboardSafe(
                        createBillboard, renderSet.billboardSet, colour);
                    if (billboard)
                        renderSet.billboards.push_back(billboard);
                }
                if (!billboard)
                    continue;

                if (TryUpdateMultiplayerFlagBillboardSafe(
                        setColour, setPosition, billboard, colour, position))
                    ++renderSet.usedBillboards;
            }

            HideUnusedMultiplayerFlagBillboards();
            if (!g_MultiplayerFlagRendererLoggedReady && !g_MultiplayerFlagRenderSets.empty())
            {
                g_MultiplayerFlagRendererLoggedReady = true;
                Log(L"[FLAG] Ogre multiplayer vehicle flag renderer active sets=%u range=%.1f\n",
                    static_cast<unsigned>(g_MultiplayerFlagRenderSets.size()),
                    static_cast<double>(kMultiplayerFlagRange));
            }
        }

        static void __fastcall MultiplayerFlagSubmitHook(
            void* flagDisplay,
            void* /*unusedEdx*/,
            void* camera)
        {
            g_MultiplayerFlagSubmitLastTick = GetTickCount64();
            if (!g_MultiplayerFlagSubmitObservedLogged)
            {
                g_MultiplayerFlagSubmitObservedLogged = true;
                Log(L"[FLAG] FlagDisplay::Submit dispatch observed; renderer driven by engine submit\n");
            }
            if (g_BzrFn_FlagDisplaySubmitOriginal)
                g_BzrFn_FlagDisplaySubmitOriginal(flagDisplay, camera);
            RenderMultiplayerFlags(camera);
        }

        // Redux keeps the FlagDisplay vtable, but whether the surviving
        // GameFeature loop still dispatches Submit in live multiplayer has
        // never been observed in a session log. When Submit stays silent,
        // drive the same renderer from the per-sim-tick hook instead so the
        // feature does not depend on the unproven dispatch path.
        void MaybeDriveMultiplayerFlagRenderFallback()
        {
            if (!ShouldEnableMultiplayerFlagUi())
                return;
            const ULONGLONG now = GetTickCount64();
            const ULONGLONG lastSubmit = g_MultiplayerFlagSubmitLastTick;
            if (lastSubmit != 0 && now - lastSubmit < kMultiplayerFlagSubmitStaleMs)
                return;
            if (!g_MultiplayerFlagTickFallbackLogged)
            {
                g_MultiplayerFlagTickFallbackLogged = true;
                Log(L"[FLAG] FlagDisplay::Submit not dispatching; driving Ogre flag renderer from sim tick\n");
            }
            RenderMultiplayerFlags(nullptr);
        }

        void InstallMultiplayerFlagRenderHookIfPossible()
        {
            if (!ShouldEnableMultiplayerFlagUi() || g_MultiplayerFlagRenderHookInstalled)
                return;

            __try
            {
                void* current = *reinterpret_cast<void**>(kFlagDisplaySubmitVtableSlotAddr);
                if (current == reinterpret_cast<void*>(MultiplayerFlagSubmitHook))
                {
                    g_MultiplayerFlagRenderHookInstalled = true;
                    return;
                }
                if (current != reinterpret_cast<void*>(kFlagDisplaySubmitAddr))
                {
                    if (!g_MultiplayerFlagRenderHookFailureLogged)
                    {
                        Log(L"[FLAG] Submit hook skipped: vtable slot=0x%08X current=0x%08X expected=0x%08X\n",
                            static_cast<uint32_t>(kFlagDisplaySubmitVtableSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                            static_cast<uint32_t>(kFlagDisplaySubmitAddr));
                        g_MultiplayerFlagRenderHookFailureLogged = true;
                    }
                    return;
                }

                g_BzrFn_FlagDisplaySubmitOriginal =
                    reinterpret_cast<FnFlagDisplaySubmit>(current);
                if (!WritePointerValue(
                        kFlagDisplaySubmitVtableSlotAddr,
                        reinterpret_cast<void*>(MultiplayerFlagSubmitHook)))
                {
                    return;
                }
                g_MultiplayerFlagRenderHookInstalled = true;
                Log(L"[FLAG] Installed Redux FlagDisplay::Submit Ogre renderer hook slot=0x%08X original=0x%08X\n",
                    static_cast<uint32_t>(kFlagDisplaySubmitVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_MultiplayerFlagRenderHookFailureLogged)
                {
                    Log(L"[FLAG] Submit hook install fault code=0x%08X\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                    g_MultiplayerFlagRenderHookFailureLogged = true;
                }
            }
        }
    }

}
