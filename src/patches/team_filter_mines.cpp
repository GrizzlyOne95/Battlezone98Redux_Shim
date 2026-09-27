// team_filter_mines.cpp
// BZR Open Shim - ODF team filters for the shield tower, magnet mine and
// proximity mine (with the magnet zero-range guard and the stock-style
// proximity detonation), split out of bzr_hooks.cpp.
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
        constexpr size_t kOrdnanceSpeedOffset = 0x20;

        constexpr size_t kOrdnanceInvSpeedOffset = 0x24;

        constexpr size_t kOrdnanceVelocityOffset = 0x30;

        // Verified byte-for-byte against the shipped GOG v2.2.301 exe
        // (ImageBase 0x00400000). Ordnance is the class in
        // fun3d\OrdnanceClass.cpp: vtable 0x00884E60, with that source-path
        // literal sitting immediately after it at 0x00884E84; an instance is
        // 0xE0 bytes (its factory does `push 0xE0` at 0x00586F88), and the
        // derived "bullet" ordnance (vtable 0x00876720, name string at
        // 0x00876744) is 0xE8. Ordnance::Init is vtable slot 1 = 0x00584FE0,
        // and stores its second argument -- the creator handle -- straight
        // into this field:
        //     0x00585289  mov edx, [ebp-0xA8]    ; edx = this
        //     0x0058528F  mov eax, [ebp+0x0C]    ; eax = creator arg
        //     0x00585292  mov [edx+0xD8], eax
        // That argument is an obj76, not a GameObject: the same Init masks its
        // +0x14 flags into the ordnance's OWN obj76 +0x14 (0x00585001 ..
        // 0x00585016 -- same field at the same offset), and passes it to
        // 0x0062CF50, which walks +0x7C/+0x80 sibling/child links, i.e. the
        // obj76 node links TryReadChunkObjectLinks already reads. So
        // kObj76GameObjectOffset is the correct second hop; the GameObject ctor
        // writes that back-pointer at 0x004DA183 (`mov [obj76+0x8C], this`)
        // right after storing the obj76 at GameObject+0xF4 (0x004DA14B).
        // This constant was 0xCC, which is an unrelated scalar: the same Init
        // zeroes it at 0x005854DC, wedged between an `fstp [this+0xC8]` and a
        // zero store to [this+0xD0], and no ordnance code anywhere reads it.
        // The bad read therefore always yielded 0, TryGetGameObjectFromObj76
        // rejected the null, and TeamFilterShouldAffectOrdnance failed closed --
        // a shield tower or magnet mine with a one-sided team filter silently
        // skipped every ordnance in the list. It stayed invisible because
        // TeamFilterConfig defaults affectAllies/affectEnemies both true, which
        // short-circuits to true before the read is ever reached.
        constexpr uintptr_t kOrdnanceListAddr = 0x0072665C;

        constexpr size_t kShieldTowerClassShieldMinXOffset = 0x160;

        constexpr size_t kShieldTowerClassShieldMaxXOffset = 0x16C;

        constexpr size_t kShieldTowerClassObjPushOffset = 0x178;

        constexpr size_t kShieldTowerClassObjDragOffset = 0x17C;

        constexpr size_t kShieldTowerClassOrdPushOffset = 0x180;

        constexpr size_t kShieldTowerClassOrdDragOffset = 0x184;

        constexpr size_t kShieldTowerPowerSourceOffset = 0x238;

        constexpr size_t kMagnetMineArmingTimerOffset = 0x238;

        constexpr size_t kProximityMineArmingTimerOffset = 0x240;

        constexpr size_t kMagnetMineClassTotalLifeOffset = 0x160;

        constexpr size_t kMagnetMineClassArmingDelayOffset = 0x168;

        constexpr size_t kMagnetMineClassRangeOffset = 0x16C;

        constexpr size_t kMagnetMineClassObjPull1Offset = 0x170;

        constexpr size_t kMagnetMineClassObjPull2Offset = 0x174;

        constexpr size_t kMagnetMineClassObjRotPullOffset = 0x178;

        constexpr size_t kMagnetMineClassOrdPull1Offset = 0x17C;

        constexpr size_t kMagnetMineClassOrdPull2Offset = 0x180;

        constexpr size_t kMagnetMineClassOrdRotPullOffset = 0x184;

        constexpr size_t kProximityMineClassRangeOffset = 0x168;

        constexpr size_t kProximityMineClassScanPeriodOffset = 0x16C;

        constexpr size_t kProximityMineClassExplosionOffset = 0x170;

        constexpr size_t kProximityMinePositionOffset = 0x108;

        // Calls in stock ProximityMine::Simulate's detonation block
        // (FUN_005b0e40, 0x005B1067-0x005B1247), read from the GOG image.
        // Debris: thiscall on the global at 0x00950190 (const double pos[3],
        // const float vel[3], int 0), ret 0xC, run 20 times.
        constexpr uintptr_t kGogProximityMineDebrisAddr = 0x004927D0;

        constexpr uintptr_t kGogProximityMineDebrisOwnerAddr = 0x00950190;

        // cdecl (float x, float z, float 3.0).
        constexpr uintptr_t kGogProximityMineGroundFxAddr = 0x007809D0;

        // double cdecl (double x, double z): terrain height; stock stores it
        // into obj+0x50 before building the explosion.
        constexpr uintptr_t kGogTerrainHeightAtAddr = 0x007855E0;

        // thiscall (mine): the damage owner, or null.
        constexpr uintptr_t kGogGameObjectDamageOwnerAddr = 0x004B0400;

        // ExplosionClass::Build, thiscall (explosionClass, obj+0x20, owner obj), ret 8.
        constexpr uintptr_t kGogExplosionClassBuildAddr = 0x004CB7B0;

        // Returns a global flag; when set, stock calls the next one on mine+0x18.
        constexpr uintptr_t kGogProximityMineNetFlagAddr = 0x00571C40;

        constexpr uintptr_t kGogProximityMineNetNotifyAddr = 0x004B8460;

        constexpr uintptr_t kCollisionRangeSearchAddr = 0x006A3E10;

        constexpr uintptr_t kGogShieldTowerSimulateAddr = 0x005D0D80;

        constexpr uintptr_t kGogMagnetMineSimulateAddr = 0x0050C650;

        constexpr uintptr_t kGogProximityMineSimulateAddr = 0x005B0E40;

        constexpr uintptr_t kGogMineSimulateAddr = 0x00511460;

        constexpr uintptr_t kGogShieldTowerPowerUpdateAddr = 0x005D0CC0;

        // GameObject::FriendP/EnemyP(GameObject*) — bool __thiscall(this, other).
        // Verified on live GOG exe by disassembly (int3-padded prologue; null-checks
        // other, calls other vtable[1]=GetTeamNum, then the int-overload FriendP/EnemyP
        // at 0x4DB560/0x4DB600 → Team::FriendP/EnemyP at 0x5E1310/0x5E1350). Matches the
        // 1.5 decomp bodies exactly. Previous values (0x0046BF40/0x0046BFD0) were WRONG —
        // they land mid-instruction, same failure class as the fixed GetObjByHandle.
        constexpr uintptr_t kGogGameObjectFriendPAddr = 0x004DB510;

        constexpr uintptr_t kGogGameObjectEnemyPAddr = 0x004DB5B0;

        constexpr uintptr_t kGogGameObjectAddVelocityAddr = 0x004A75B0;

        constexpr uintptr_t kGogMatrixInverseAddr = 0x008203F0;

        constexpr uintptr_t kGogVectorTransformAddr = 0x00820180;

        constexpr uintptr_t kGogRangeSearchAddr = 0x005B2950;

        constexpr uintptr_t kGogRangeResultsGetNextAddr = 0x00462710;

        constexpr uintptr_t kShieldTowerSimulateVtableSlotAddr = 0x00887724;

        constexpr uintptr_t kMagnetMineSimulateVtableSlotAddr = 0x0087D574;

        constexpr uintptr_t kProximityMineSimulateVtableSlotAddr = 0x008862B4;

        struct ShieldTowerRangeSearchResults
        {
            uint8_t storage[48] = {};
        };

        struct ListPtrValue
        {
            ListNodePtrValue* head = nullptr;
            size_t size = 0;
        };

        struct ShieldTowerRuntimeParams
        {
            float minX = 0.0f;
            float maxX = 0.0f;
            float minY = 0.0f;
            float maxY = 0.0f;
            float minZ = 0.0f;
            float maxZ = 0.0f;
            float objPush = 0.0f;
            float objDrag = 0.0f;
            float ordPush = 0.0f;
            float ordDrag = 0.0f;
        };

        void __fastcall ShieldTowerSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunShieldTowerFilteredSimulate(thisPtr, dt);
        }

        static bool TryGetUnsafeMagnetRange(void* magnetMinePtr, float& outRange)
        {
            outRange = 0.0f;
            if (!magnetMinePtr)
                return false;

            __try
            {
                auto* mineBytes = reinterpret_cast<const uint8_t*>(magnetMinePtr);
                const void* mineClass = *reinterpret_cast<void* const*>(
                    mineBytes + kGameObjectClassOffset);
                if (!mineClass)
                    return false;

                outRange = *reinterpret_cast<const float*>(
                    reinterpret_cast<const uint8_t*>(mineClass) +
                    kMagnetMineClassRangeOffset);
                return !std::isfinite(outRange) || outRange <= 0.0f;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void __fastcall MagnetMineSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            float range = 0.0f;
            if (g_MagnetZeroRangeGuardEnabled && TryGetUnsafeMagnetRange(thisPtr, range))
            {
                const long remaining = InterlockedDecrement(&g_MagnetZeroRangeLogBudget);
                if (remaining >= 0)
                {
                    Log(L"[MAGNET] Skipped attraction for invalid range=%.6g mine=0x%08X; base Mine::Simulate preserved (remaining=%ld)\n",
                        static_cast<double>(range),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)),
                        remaining);
                }

                // MagnetMine::Simulate eventually delegates to Mine::Simulate.
                // Preserve that lifetime/removal behavior while bypassing the
                // invalid attraction bounds that trigger the zero-range fault.
                if (g_BzrFn_MineSimulate)
                    g_BzrFn_MineSimulate(thisPtr, dt);
                else if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(thisPtr, dt);
                return;
            }

            RunMagnetMineFilteredSimulate(thisPtr, dt);
        }

        void __fastcall ProximityMineSimulateTeamFilterHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunProximityMineFilteredSimulate(thisPtr, dt);
        }

        void InstallShieldTowerTeamFilterHookIfPossible()
        {
            if (g_ShieldTowerSimulateHookInstalled)
                return;

            if (!g_BzrFn_ShieldTowerSimulateOriginal)
                g_BzrFn_ShieldTowerSimulateOriginal =
                    reinterpret_cast<FnShieldTowerSimulate>(kGogShieldTowerSimulateAddr);
            if (!g_BzrFn_BuildingSimulate)
                g_BzrFn_BuildingSimulate =
                    reinterpret_cast<FnShieldTowerSimulate>(kGogBuildingSimulateAddr);
            if (!g_BzrFn_ShieldTowerPowerUpdate)
                g_BzrFn_ShieldTowerPowerUpdate =
                    reinterpret_cast<FnShieldTowerPowerUpdate>(kGogShieldTowerPowerUpdateAddr);
            if (!g_BzrFn_GameObjectFriendP)
                g_BzrFn_GameObjectFriendP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectFriendPAddr);
            if (!g_BzrFn_GameObjectEnemyP)
                g_BzrFn_GameObjectEnemyP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectEnemyPAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
                g_BzrFn_GameObjectGetObjByHandle =
                    &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
            if (!g_BzrFn_MatrixInverse)
                g_BzrFn_MatrixInverse =
                    reinterpret_cast<FnMatrixInverse>(kGogMatrixInverseAddr);
            if (!g_BzrFn_VectorTransform)
                g_BzrFn_VectorTransform =
                    reinterpret_cast<FnVectorTransform>(kGogVectorTransformAddr);
            if (!g_BzrFn_CollisionRangeSearch)
                g_BzrFn_CollisionRangeSearch =
                    reinterpret_cast<FnRangeSearch>(kGogRangeSearchAddr);
            if (!g_BzrFn_RangeResultsGetNext)
                g_BzrFn_RangeResultsGetNext =
                    reinterpret_cast<FnRangeResultsGetNext>(kGogRangeResultsGetNextAddr);

            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(kShieldTowerSimulateVtableSlotAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            if (current != reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook) &&
                current != reinterpret_cast<void*>(kGogShieldTowerSimulateAddr))
            {
                Log(L"[SHIELDODF] ShieldTower::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                    static_cast<uint32_t>(kShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                    static_cast<uint32_t>(kGogShieldTowerSimulateAddr));
                return;
            }

            const bool patched =
                (current == reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook)) ||
                WritePointerValue(kShieldTowerSimulateVtableSlotAddr,
                                  reinterpret_cast<void*>(ShieldTowerSimulateTeamFilterHook));
            g_ShieldTowerSimulateHookInstalled =
                patched &&
                g_BzrFn_ShieldTowerSimulateOriginal &&
                g_BzrFn_BuildingSimulate &&
                g_BzrFn_ShieldTowerPowerUpdate &&
                g_BzrFn_GameObjectFriendP &&
                g_BzrFn_GameObjectEnemyP &&
                g_BzrFn_GameObjectGetObjByHandle &&
                g_BzrFn_MatrixInverse &&
                g_BzrFn_VectorTransform &&
                g_BzrFn_CollisionRangeSearch &&
                g_BzrFn_RangeResultsGetNext;

            if (g_ShieldTowerSimulateHookInstalled)
            {
                Log(L"[SHIELDODF] Installed ShieldTower team filter hook slot=0x%08X original=0x%08X\n",
                    static_cast<uint32_t>(kShieldTowerSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ShieldTowerSimulateOriginal)));
            }
        }
        void InstallMineTeamFilterHooksIfPossible()
        {
            if (g_MagnetMineSimulateHookInstalled && g_ProximityMineSimulateHookInstalled)
                return;

            if (!g_BzrFn_MagnetMineSimulateOriginal)
                g_BzrFn_MagnetMineSimulateOriginal =
                    reinterpret_cast<FnMagnetMineSimulate>(kGogMagnetMineSimulateAddr);
            if (!g_BzrFn_ProximityMineSimulateOriginal)
                g_BzrFn_ProximityMineSimulateOriginal =
                    reinterpret_cast<FnProximityMineSimulate>(kGogProximityMineSimulateAddr);
            if (!g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate =
                    reinterpret_cast<FnProximityMineSimulate>(kGogMineSimulateAddr);

            if (!g_BzrFn_GameObjectFriendP)
                g_BzrFn_GameObjectFriendP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectFriendPAddr);
            if (!g_BzrFn_GameObjectEnemyP)
                g_BzrFn_GameObjectEnemyP =
                    reinterpret_cast<FnGameObjectRelation>(kGogGameObjectEnemyPAddr);
            if (!g_BzrFn_GameObjectGetObjByHandle)
                g_BzrFn_GameObjectGetObjByHandle =
                    &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
            if (!g_BzrFn_CollisionRangeSearch)
                g_BzrFn_CollisionRangeSearch =
                    reinterpret_cast<FnRangeSearch>(kGogRangeSearchAddr);
            if (!g_BzrFn_RangeResultsGetNext)
                g_BzrFn_RangeResultsGetNext =
                    reinterpret_cast<FnRangeResultsGetNext>(kGogRangeResultsGetNextAddr);

            if (!g_MagnetMineSimulateHookInstalled)
            {
                void* current = nullptr;
                __try { current = *reinterpret_cast<void**>(kMagnetMineSimulateVtableSlotAddr); }
                __except (EXCEPTION_EXECUTE_HANDLER) { current = nullptr; }

                if (current != reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook) &&
                    current != reinterpret_cast<void*>(kGogMagnetMineSimulateAddr))
                {
                    Log(L"[MAGNETODF] MagnetMine::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        static_cast<uint32_t>(kMagnetMineSimulateVtableSlotAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        static_cast<uint32_t>(kGogMagnetMineSimulateAddr));
                }
                else
                {
                    const bool patched =
                        (current == reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook)) ||
                        WritePointerValue(kMagnetMineSimulateVtableSlotAddr,
                                          reinterpret_cast<void*>(MagnetMineSimulateTeamFilterHook));
                    g_MagnetMineSimulateHookInstalled =
                        patched &&
                        g_BzrFn_MagnetMineSimulateOriginal &&
                        g_BzrFn_MineSimulate &&
                        g_BzrFn_GameObjectFriendP &&
                        g_BzrFn_GameObjectEnemyP &&
                        g_BzrFn_GameObjectGetObjByHandle &&
                        g_BzrFn_CollisionRangeSearch &&
                        g_BzrFn_RangeResultsGetNext;

                    if (g_MagnetMineSimulateHookInstalled)
                    {
                        Log(L"[MAGNETODF] Installed MagnetMine team filter hook slot=0x%08X original=0x%08X\n",
                            static_cast<uint32_t>(kMagnetMineSimulateVtableSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_MagnetMineSimulateOriginal)));
                    }
                }
            }

            if (!g_ProximityMineSimulateHookInstalled)
            {
                void* current = nullptr;
                __try { current = *reinterpret_cast<void**>(kProximityMineSimulateVtableSlotAddr); }
                __except (EXCEPTION_EXECUTE_HANDLER) { current = nullptr; }

                if (current != reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook) &&
                    current != reinterpret_cast<void*>(kGogProximityMineSimulateAddr))
                {
                    Log(L"[PROXODF] ProximityMine::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                        static_cast<uint32_t>(kProximityMineSimulateVtableSlotAddr),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        static_cast<uint32_t>(kGogProximityMineSimulateAddr));
                }
                else
                {
                    const bool patched =
                        (current == reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook)) ||
                        WritePointerValue(kProximityMineSimulateVtableSlotAddr,
                                          reinterpret_cast<void*>(ProximityMineSimulateTeamFilterHook));
                    g_ProximityMineSimulateHookInstalled =
                        patched &&
                        g_BzrFn_ProximityMineSimulateOriginal &&
                        g_BzrFn_MineSimulate &&
                        g_BzrFn_GameObjectFriendP &&
                        g_BzrFn_GameObjectEnemyP &&
                        g_BzrFn_GameObjectGetObjByHandle &&
                        g_BzrFn_CollisionRangeSearch &&
                        g_BzrFn_RangeResultsGetNext;

                    if (g_ProximityMineSimulateHookInstalled)
                    {
                        Log(L"[PROXODF] Installed ProximityMine team filter hook slot=0x%08X original=0x%08X\n",
                            static_cast<uint32_t>(kProximityMineSimulateVtableSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_ProximityMineSimulateOriginal)));
                    }
                }
            }
        }

        static bool TryParseTeamFilterValue(const char* value,
                                                       bool& outAffectAllies,
                                                       bool& outAffectEnemies)
        {
            char normalized[64] = {};
            if (!TryNormalizeQuotedStringValue(value, normalized, sizeof(normalized)))
                return false;

            if (strcmp(normalized, "all") == 0 ||
                strcmp(normalized, "both") == 0 ||
                strcmp(normalized, "default") == 0)
            {
                outAffectAllies = true;
                outAffectEnemies = true;
                return true;
            }

            if (strcmp(normalized, "allies") == 0 ||
                strcmp(normalized, "ally") == 0 ||
                strcmp(normalized, "friendly") == 0 ||
                strcmp(normalized, "friendlies") == 0)
            {
                outAffectAllies = true;
                outAffectEnemies = false;
                return true;
            }

            if (strcmp(normalized, "enemies") == 0 ||
                strcmp(normalized, "enemy") == 0 ||
                strcmp(normalized, "hostile") == 0 ||
                strcmp(normalized, "hostiles") == 0)
            {
                outAffectAllies = false;
                outAffectEnemies = true;
                return true;
            }

            if (strcmp(normalized, "none") == 0 ||
                strcmp(normalized, "off") == 0 ||
                strcmp(normalized, "disabled") == 0)
            {
                outAffectAllies = false;
                outAffectEnemies = false;
                return true;
            }

            return false;
        }

        static bool TryReadTeamFilterFromOdfFile(const char* odfToken,
                                                 TeamFilterConfig& outConfig,
                                                 const char* logTag)
        {
            outConfig = {};

            std::filesystem::path resolvedPath;
            if (!TryResolveOdfFilePath(odfToken, resolvedPath))
                return false;

            const ProducerBuildMenuEntry odfKey = NormalizeQuotedOdfToken(odfToken);
            if (!odfKey.hasValue)
                return false;

            FILE* file = nullptr;
            if (fopen_s(&file, resolvedPath.string().c_str(), "r") != 0 || !file)
                return false;

            bool foundAny = false;
            bool affectAllies = true;
            bool affectEnemies = true;
            char line[256] = {};
            while (std::fgets(line, static_cast<int>(sizeof(line)), file))
            {
                char* trimmed = TrimAsciiInPlace(line);
                if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#')
                    continue;

                if (*trimmed == '[')
                    continue;

                char* equals = std::strchr(trimmed, '=');
                if (!equals)
                    continue;

                *equals = '\0';
                char* key = TrimAsciiInPlace(trimmed);
                char* value = TrimAsciiInPlace(equals + 1);
                if (!key || !*key || !value || !*value)
                    continue;

                bool parsedBool = false;
                bool parsedAllies = false;
                bool parsedEnemies = false;
                if (_stricmp(key, "teamFilter") == 0 &&
                    TryParseTeamFilterValue(value, parsedAllies, parsedEnemies))
                {
                    affectAllies = parsedAllies;
                    affectEnemies = parsedEnemies;
                    foundAny = true;
                }
                else if (_stricmp(key, "affectAllies") == 0 && TryParseBoolValue(value, parsedBool))
                {
                    affectAllies = parsedBool;
                    foundAny = true;
                }
                else if (_stricmp(key, "affectEnemies") == 0 && TryParseBoolValue(value, parsedBool))
                {
                    affectEnemies = parsedBool;
                    foundAny = true;
                }
            }

            std::fclose(file);

            if (!foundAny)
                return false;

            outConfig.parsed = true;
            outConfig.affectAllies = affectAllies;
            outConfig.affectEnemies = affectEnemies;
            Log(L"[%hs] Loaded team filter odf=%hs allies=%hs enemies=%hs file=%hs\n",
                logTag ? logTag : "TEAMODF",
                odfKey.token,
                affectAllies ? "true" : "false",
                affectEnemies ? "true" : "false",
                resolvedPath.string().c_str());
            return true;
        }

        bool TryGetTeamFilterForObject(void* objectPtr, TeamFilterConfig& outConfig, TeamFilterCache& cache, const char* logTag)
        {
            outConfig = {};

            char odfToken[kProducerBuildMenuTokenLen + 1] = {};
            if (!TryGetObjectOdfToken(objectPtr, odfToken))
                return false;

            const auto cached = cache.odfEntries.find(odfToken);
            if (cached != cache.odfEntries.end())
            {
                outConfig = cached->second;
                return outConfig.parsed;
            }

            TeamFilterConfig loaded = {};
            TryReadTeamFilterFromOdfFile(odfToken, loaded, logTag);
            cache.odfEntries[odfToken] = loaded;
            outConfig = loaded;
            return outConfig.parsed;
        }

        static bool TeamFilterNeedsCustomPath(const TeamFilterConfig& config)
        {
            return config.parsed && !(config.affectAllies && config.affectEnemies);
        }

        static bool TryGetOrdnanceWorldPosition(void* ordnance, float (&outPosition)[3])
        {
            outPosition[0] = 0.0f;
            outPosition[1] = 0.0f;
            outPosition[2] = 0.0f;
            if (!ordnance)
                return false;

            __try
            {
                void* obj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(ordnance) + kOrdnanceObjOffset);
                return TryGetObjectWorldPositionFromObj76(obj76, outPosition);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryGetOrdnanceOwnerGameObject(void* ordnance, void*& outOwner)
        {
            outOwner = nullptr;
            if (!ordnance)
                return false;

            __try
            {
                void* ownerObj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(ordnance) + kOrdnanceOwnerObjOffset);
                return TryGetGameObjectFromObj76(ownerObj76, outOwner);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outOwner = nullptr;
                return false;
            }
        }

        static bool TryReadShieldTowerRuntimeParams(void* shieldTowerPtr,
                                                    ShieldTowerRuntimeParams& outParams,
                                                    void*& outTowerObj76,
                                                    LegacyMat3*& outTowerMatrix,
                                                    LegacyMat3& outInverseMatrix)
        {
            outParams = {};
            outTowerObj76 = nullptr;
            outTowerMatrix = nullptr;
            std::memset(&outInverseMatrix, 0, sizeof(outInverseMatrix));
            if (!shieldTowerPtr)
                return false;

            __try
            {
                const auto* shieldBytes = reinterpret_cast<const uint8_t*>(shieldTowerPtr);
                outTowerObj76 = *reinterpret_cast<void* const*>(shieldBytes + kGameObjectObjOffset);
                auto* shieldClass = *reinterpret_cast<void* const*>(shieldBytes + kGameObjectClassOffset);
                if (!outTowerObj76 || !shieldClass)
                    return false;

                outTowerMatrix = reinterpret_cast<LegacyMat3*>(
                    reinterpret_cast<uint8_t*>(outTowerObj76) + kObj76TransformOffset);
                if (!outTowerMatrix)
                    return false;

                outParams.minX = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x00);
                outParams.minY = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x04);
                outParams.minZ = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMinXOffset + 0x08);
                outParams.maxX = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x00);
                outParams.maxY = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x04);
                outParams.maxZ = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassShieldMaxXOffset + 0x08);
                outParams.objPush = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassObjPushOffset);
                outParams.objDrag = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassObjDragOffset);
                outParams.ordPush = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassOrdPushOffset);
                outParams.ordDrag = *reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(shieldClass) + kShieldTowerClassOrdDragOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outTowerObj76 = nullptr;
                outTowerMatrix = nullptr;
                return false;
            }

            if (!g_BzrFn_MatrixInverse)
                return false;

            g_BzrFn_MatrixInverse(&outInverseMatrix, outTowerMatrix);
            return true;
        }

        static bool ShieldTowerContainsLocalPosition(const float (&localPosition)[3],
                                                     const ShieldTowerRuntimeParams& params)
        {
            return (params.minX < localPosition[0] && localPosition[0] < params.maxX) &&
                   (params.minY < localPosition[1] && localPosition[1] < params.maxY) &&
                   (params.minZ < localPosition[2] && localPosition[2] < params.maxZ);
        }

        static bool TeamFilterShouldAffectObject(void* shieldTowerPtr,
                                                  void* targetObject,
                                                  const TeamFilterConfig& config)
        {
            if (!shieldTowerPtr || !targetObject)
                return false;

            if (config.affectAllies && config.affectEnemies)
                return true;

            bool allow = false;
            if (config.affectAllies && g_BzrFn_GameObjectFriendP)
                allow = g_BzrFn_GameObjectFriendP(shieldTowerPtr, targetObject);
            if (!allow && config.affectEnemies && g_BzrFn_GameObjectEnemyP)
                allow = g_BzrFn_GameObjectEnemyP(shieldTowerPtr, targetObject);
            return allow;
        }

        static bool TeamFilterShouldAffectOrdnance(void* shieldTowerPtr,
                                                    void* ordnance,
                                                    const TeamFilterConfig& config)
        {
            if (config.affectAllies && config.affectEnemies)
                return true;

            void* ownerObject = nullptr;
            if (!TryGetOrdnanceOwnerGameObject(ordnance, ownerObject))
                return false;

            return TeamFilterShouldAffectObject(shieldTowerPtr, ownerObject, config);
        }

        static void ShieldTowerApplyObjectForce(void* shieldTowerPtr,
                                                void* targetObject,
                                                const LegacyMat3& towerMatrix,
                                                const ShieldTowerRuntimeParams& params,
                                                float dt)
        {
            if (!shieldTowerPtr || !targetObject)
                return;

            __try
            {
                float delta[3] =
                {
                    towerMatrix.front_x * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x12C) * (params.objDrag * dt),
                    towerMatrix.front_y * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x130) * (params.objDrag * dt),
                    towerMatrix.front_z * (params.objPush * dt) -
                        *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(targetObject) + 0x134) * (params.objDrag * dt)
                };
                reinterpret_cast<void(__thiscall*)(void*, const float*)>(kGogGameObjectAddVelocityAddr)(targetObject, delta);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void ShieldTowerApplyOrdnanceForce(void* ordnance,
                                                  const LegacyMat3& towerMatrix,
                                                  const ShieldTowerRuntimeParams& params,
                                                  float dt)
        {
            if (!ordnance)
                return;

            __try
            {
                auto* ordBytes = reinterpret_cast<uint8_t*>(ordnance);
                auto* velocity = reinterpret_cast<float*>(ordBytes + kOrdnanceVelocityOffset);
                velocity[0] += towerMatrix.front_x * (params.ordPush * dt) - velocity[0] * (params.ordDrag * dt);
                velocity[1] += towerMatrix.front_y * (params.ordPush * dt) - velocity[1] * (params.ordDrag * dt);
                velocity[2] += towerMatrix.front_z * (params.ordPush * dt) - velocity[2] * (params.ordDrag * dt);

                const float speed = std::sqrt(
                    velocity[0] * velocity[0] +
                    velocity[1] * velocity[1] +
                    velocity[2] * velocity[2]);
                *reinterpret_cast<float*>(ordBytes + kOrdnanceSpeedOffset) = speed;
                *reinterpret_cast<float*>(ordBytes + kOrdnanceInvSpeedOffset) =
                    (speed == 0.0f) ? 1.0e30f : (1.0f / speed);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void RunShieldTowerFilteredSimulate(void* shieldTowerPtr, float dt)
        {
            if (!shieldTowerPtr || !g_BzrFn_ShieldTowerPowerUpdate || !g_BzrFn_BuildingSimulate ||
                !g_BzrFn_VectorTransform || !g_BzrFn_CollisionRangeSearch || !g_BzrFn_RangeResultsGetNext ||
                !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            ShieldTowerRuntimeParams params = {};
            void* towerObj76 = nullptr;
            LegacyMat3* towerMatrix = nullptr;
            LegacyMat3 inverseMatrix = {};

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(shieldTowerPtr, filter, g_ShieldTowerTeamFilterCache, "SHIELDODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            g_BzrFn_ShieldTowerPowerUpdate(shieldTowerPtr);

            if (!TryReadShieldTowerRuntimeParams(shieldTowerPtr, params, towerObj76, towerMatrix, inverseMatrix))
            {
                if (g_BzrFn_ShieldTowerSimulateOriginal)
                    g_BzrFn_ShieldTowerSimulateOriginal(shieldTowerPtr, dt);
                return;
            }

            if (*reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(shieldTowerPtr) + kShieldTowerPowerSourceOffset) != 0)
            {
                float worldCorners[24] =
                {
                    params.minX, params.minY, params.minZ,
                    params.maxX, params.minY, params.minZ,
                    params.minX, params.minY, params.maxZ,
                    params.maxX, params.minY, params.maxZ,
                    params.minX, params.maxY, params.minZ,
                    params.maxX, params.maxY, params.minZ,
                    params.minX, params.maxY, params.maxZ,
                    params.maxX, params.maxY, params.maxZ
                };

                g_BzrFn_VectorTransform(worldCorners, worldCorners, 8, towerMatrix);

                float minWorldX = 1.0e30f;
                float minWorldZ = 1.0e30f;
                float maxWorldX = -1.0e30f;
                float maxWorldZ = -1.0e30f;
                for (size_t i = 0; i < 8; ++i)
                {
                    const float worldX = worldCorners[i * 3 + 0];
                    const float worldZ = worldCorners[i * 3 + 2];
                    minWorldX = (std::min)(minWorldX, worldX);
                    minWorldZ = (std::min)(minWorldZ, worldZ);
                    maxWorldX = (std::max)(maxWorldX, worldX);
                    maxWorldZ = (std::max)(maxWorldZ, worldZ);
                }

                void* collisionRangeSearch = nullptr;
                __try
                {
                    collisionRangeSearch = *reinterpret_cast<void**>(kCollisionRangeSearchAddr);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    collisionRangeSearch = nullptr;
                }

                if (collisionRangeSearch)
                {
                    ShieldTowerRangeSearchResults results = {};
                    g_BzrFn_CollisionRangeSearch(
                        collisionRangeSearch,
                        static_cast<double>(minWorldX),
                        static_cast<double>(minWorldZ),
                        static_cast<double>(maxWorldX),
                        static_cast<double>(maxWorldZ),
                        &results);

                    uint32_t* handlePtr = nullptr;
                    while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                    {
                        if (!handlePtr)
                            continue;

                        void* targetObject = g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr));
                        if (!targetObject || !TeamFilterShouldAffectObject(shieldTowerPtr, targetObject, filter))
                            continue;

                        float targetWorld[3] = {};
                        if (!TryGetGameObjectWorldPosition(targetObject, targetWorld))
                            continue;

                        float targetLocal[3] = { targetWorld[0], targetWorld[1], targetWorld[2] };
                        g_BzrFn_VectorTransform(targetLocal, targetLocal, 1, &inverseMatrix);
                        if (!ShieldTowerContainsLocalPosition(targetLocal, params))
                            continue;

                        ShieldTowerApplyObjectForce(shieldTowerPtr, targetObject, *towerMatrix, params, dt);
                    }
                }

                const auto* list = reinterpret_cast<const ListPtrValue*>(kOrdnanceListAddr);
                __try
                {
                    if (list && list->head)
                    {
                        for (ListNodePtrValue* node = list->head->next;
                             node && node != list->head;
                             node = node->next)
                        {
                            void* ordnance = node->value;
                            if (!ordnance || !TeamFilterShouldAffectOrdnance(shieldTowerPtr, ordnance, filter))
                                continue;

                            float ordWorld[3] = {};
                            if (!TryGetOrdnanceWorldPosition(ordnance, ordWorld))
                                continue;

                            float ordLocal[3] = { ordWorld[0], ordWorld[1], ordWorld[2] };
                            g_BzrFn_VectorTransform(ordLocal, ordLocal, 1, &inverseMatrix);
                            if (!ShieldTowerContainsLocalPosition(ordLocal, params))
                                continue;

                            ShieldTowerApplyOrdnanceForce(ordnance, *towerMatrix, params, dt);
                        }
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            g_BzrFn_BuildingSimulate(shieldTowerPtr, dt);
        }
        void RunMagnetMineFilteredSimulate(void* magnetMinePtr, float dt)
        {
            if (!magnetMinePtr || !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(magnetMinePtr, dt);
                return;
            }

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(magnetMinePtr, filter, g_MagnetMineTeamFilterCache, "MAGNETODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_MagnetMineSimulateOriginal)
                    g_BzrFn_MagnetMineSimulateOriginal(magnetMinePtr, dt);
                return;
            }

            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(magnetMinePtr);
                void* mineClass = *reinterpret_cast<void**>(mineBytes + kGameObjectClassOffset);
                // No class, no attraction, but the base Mine::Simulate below
                // still has to run: it is what expires and removes the mine.
                if (!mineClass) __leave;

                float armingTimer = *reinterpret_cast<float*>(mineBytes + kMagnetMineArmingTimerOffset);
                float totalLife = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassTotalLifeOffset);
                float armingDelay = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassArmingDelayOffset);

                float elapsed = totalLife - armingTimer;
                if (elapsed >= armingDelay)
                {
                    float range = *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassRangeOffset);
                    float minePos[3] = {
                        *reinterpret_cast<float*>(mineBytes + 0x108),
                        *reinterpret_cast<float*>(mineBytes + 0x10C),
                        *reinterpret_cast<float*>(mineBytes + 0x110)
                    };

                    // Proximity scan for objects
                    void* collisionRangeSearch = *reinterpret_cast<void**>(kCollisionRangeSearchAddr);
                    if (collisionRangeSearch && g_BzrFn_CollisionRangeSearch && g_BzrFn_RangeResultsGetNext)
                    {
                        ShieldTowerRangeSearchResults results = {};
                        g_BzrFn_CollisionRangeSearch(
                            collisionRangeSearch,
                            static_cast<double>(minePos[0] - range),
                            static_cast<double>(minePos[2] - range),
                            static_cast<double>(minePos[0] + range),
                            static_cast<double>(minePos[2] + range),
                            &results);

                        uint32_t* handlePtr = nullptr;
                        while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                        {
                            if (!handlePtr) continue;
                            void* target = g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr));
                            if (!target || target == magnetMinePtr) continue;

                            // ORIGINAL check: vtable[+0x2c] targets? and distance.
                            // We add TeamFilter check.
                            if (!TeamFilterShouldAffectObject(magnetMinePtr, target, filter))
                                continue;

                            float targetPos[3] = {};
                            if (TryGetGameObjectWorldPosition(target, targetPos))
                            {
                                float dx = targetPos[0] - minePos[0];
                                float dy = targetPos[1] - minePos[1];
                                float dz = targetPos[2] - minePos[2];
                                float distSq = dx * dx + dy * dy + dz * dz;

                                if (distSq < range * range)
                                {
                                    float dist = std::sqrt(distSq + 0.0001f);
                                    float pull = (dist * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjPull1Offset) +
                                                  *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjPull2Offset)) * dt;
                                    float rotPull = dt * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassObjRotPullOffset);

                                    float velDelta[3] = {
                                        dx * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x12C) * rotPull),
                                        dy * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x130) * rotPull),
                                        dz * pull - (*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(target) + 0x134) * rotPull)
                                    };
                                    reinterpret_cast<void(__thiscall*)(void*, const float*)>(kGogGameObjectAddVelocityAddr)(target, velDelta);
                                }
                            }
                        }
                    }

                    // Proximity scan for ordnance
                    const auto* ordList = reinterpret_cast<const ListPtrValue*>(kOrdnanceListAddr);
                    if (ordList && ordList->head)
                    {
                        for (ListNodePtrValue* node = ordList->head->next; node && node != ordList->head; node = node->next)
                        {
                            void* ordnance = node->value;
                            if (!ordnance || !TeamFilterShouldAffectOrdnance(magnetMinePtr, ordnance, filter))
                                continue;

                            float ordPos[3] = {};
                            if (TryGetOrdnanceWorldPosition(ordnance, ordPos))
                            {
                                float dx = ordPos[0] - minePos[0];
                                float dy = ordPos[1] - minePos[1];
                                float dz = ordPos[2] - minePos[2];
                                float distSq = dx * dx + dy * dy + dz * dz;

                                if (distSq < range * range)
                                {
                                    float dist = std::sqrt(distSq + 0.0001f);
                                    float pull = (dist * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdPull1Offset) +
                                                  *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdPull2Offset)) * dt;
                                    float rotPull = dt * *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(mineClass) + kMagnetMineClassOrdRotPullOffset);

                                    auto* ordBytes = reinterpret_cast<uint8_t*>(ordnance);
                                    auto* velocity = reinterpret_cast<float*>(ordBytes + kOrdnanceVelocityOffset);
                                    velocity[0] += dx * pull - velocity[0] * rotPull;
                                    velocity[1] += dy * pull - velocity[1] * rotPull;
                                    velocity[2] += dz * pull - velocity[2] * rotPull;

                                    const float speed = std::sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
                                    *reinterpret_cast<float*>(ordBytes + kOrdnanceSpeedOffset) = speed;
                                    *reinterpret_cast<float*>(ordBytes + kOrdnanceInvSpeedOffset) = (speed == 0.0f) ? 1.0e30f : (1.0f / speed);
                                }
                            }
                        }
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            if (g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate(magnetMinePtr, dt);
        }

        // Resolved once: the filtered path reproduces stock's detonation block
        // and must not run it on an image where those calls have moved.
        static bool ProximityMineDetonationSitesVerified()
        {
            static int s_verified = -1;
            if (s_verified >= 0)
                return s_verified != 0;

            struct Site { uintptr_t address; uint8_t bytes[8]; };
            static const Site kSites[] = {
                { kGogProximityMineDebrisAddr,    { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xB8, 0x00, 0x00 } },
                { kGogProximityMineGroundFxAddr,  { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x30, 0x83, 0x3D } },
                { kGogTerrainHeightAtAddr,        { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x2C, 0xF3, 0x0F } },
                { kGogGameObjectDamageOwnerAddr,  { 0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC, 0x8B } },
                { kGogExplosionClassBuildAddr,    { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10, 0x89, 0x4D } },
                { kGogProximityMineNetFlagAddr,   { 0x55, 0x8B, 0xEC, 0xA0, 0x7B, 0x7F, 0x91, 0x00 } },
                { kGogProximityMineNetNotifyAddr, { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x14, 0x89, 0x4D } },
            };
            s_verified = 1;
            for (const Site& site : kSites)
            {
                if (!ExpectedBytesMatchAt(site.address, site.bytes, sizeof(site.bytes)))
                {
                    Log(L"[PROXODF] teamFilter disabled: detonation call 0x%08X does not match; "
                        L"filtered proximity mines use stock targeting\n",
                        static_cast<uint32_t>(site.address));
                    s_verified = 0;
                    break;
                }
            }
            return s_verified != 0;
        }

        // Stock ProximityMine::Simulate's detonation block, call for call.
        static void DetonateProximityMineLikeStock(void* proximityMinePtr)
        {
            using FnDebris = void(__thiscall*)(void* owner, const void* position, const float* velocity, int flags);
            using FnGroundFx = void(__cdecl*)(float x, float z, float radius);
            using FnTerrainHeightAt = double(__cdecl*)(double x, double z);
            using FnDamageOwner = void*(__thiscall*)(void* gameObject);
            using FnOwnerObj = void*(__thiscall*)(void* entity);
            using FnExplosionBuild = void(__thiscall*)(void* explosionClass, void* matrix, void* ownerObj);
            using FnNetFlag = bool(__cdecl*)();
            using FnNetNotify = void(__thiscall*)(void* entity);

            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(proximityMinePtr);
                auto* obj = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectObjOffset);
                auto* mineClass = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectClassOffset);
                if (!obj || !mineClass)
                    return;

                double position[3] = {};
                std::memcpy(position, obj + 0x48, sizeof(position));
                const float debrisVelocity[3] = { 0.0f, 15.0f, 0.0f };
                auto debris = reinterpret_cast<FnDebris>(kGogProximityMineDebrisAddr);
                for (int i = 0; i < 20; ++i)
                    debris(reinterpret_cast<void*>(kGogProximityMineDebrisOwnerAddr), position, debrisVelocity, 0);

                const double x = *reinterpret_cast<double*>(obj + 0x48);
                const double z = *reinterpret_cast<double*>(obj + 0x58);
                reinterpret_cast<FnGroundFx>(kGogProximityMineGroundFxAddr)(
                    static_cast<float>(x), static_cast<float>(z), 3.0f);
                *reinterpret_cast<double*>(obj + 0x50) =
                    reinterpret_cast<FnTerrainHeightAt>(kGogTerrainHeightAtAddr)(x, z);

                void* ownerObj = obj;
                auto* damageOwner = static_cast<uint8_t*>(
                    reinterpret_cast<FnDamageOwner>(kGogGameObjectDamageOwnerAddr)(proximityMinePtr));
                if (damageOwner)
                {
                    void* entity = damageOwner + 0x18;
                    void** vtable = *reinterpret_cast<void***>(entity);
                    ownerObj = reinterpret_cast<FnOwnerObj>(vtable[0x30 / sizeof(void*)])(entity);
                }

                void* explosionClass = *reinterpret_cast<void**>(mineClass + kProximityMineClassExplosionOffset);
                if (explosionClass)
                    reinterpret_cast<FnExplosionBuild>(kGogExplosionClassBuildAddr)(explosionClass, obj + 0x20, ownerObj);

                *reinterpret_cast<uint32_t*>(obj + 0x14) |= 0x280;
                if (reinterpret_cast<FnNetFlag>(kGogProximityMineNetFlagAddr)())
                    reinterpret_cast<FnNetNotify>(kGogProximityMineNetNotifyAddr)(mineBytes + 0x18);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void RunProximityMineFilteredSimulate(void* proximityMinePtr, float dt)
        {
            if (!proximityMinePtr || !g_BzrFn_GameObjectGetObjByHandle || !g_BzrFn_GameObjectFriendP || !g_BzrFn_GameObjectEnemyP)
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            TeamFilterConfig filter = {};
            const bool hasFilter = TryGetTeamFilterForObject(proximityMinePtr, filter, g_ProximityMineTeamFilterCache, "PROXODF");
            if (!hasFilter || !TeamFilterNeedsCustomPath(filter))
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            if (!ProximityMineDetonationSitesVerified())
            {
                if (g_BzrFn_ProximityMineSimulateOriginal)
                    g_BzrFn_ProximityMineSimulateOriginal(proximityMinePtr, dt);
                return;
            }

            // Stock ProximityMine::Simulate with the team filter in place of
            // its friend test. Stock: every scan period, a friend in range
            // holds fire, and any other object in range that is moving away
            // from the mine (offset . velocity > 0) sets it off. Here, an
            // object the filter affects can set it off, and an object it
            // spares holds fire only where stock would (a friend).
            bool detonate = false;
            __try
            {
                auto* mineBytes = reinterpret_cast<uint8_t*>(proximityMinePtr);
                float* scanTimer = reinterpret_cast<float*>(mineBytes + kProximityMineArmingTimerOffset);
                *scanTimer -= dt;
                auto* mineObj = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectObjOffset);
                auto* mineClass = *reinterpret_cast<uint8_t**>(mineBytes + kGameObjectClassOffset);
                if (*scanTimer <= 0.0f && *scanTimer != 0.0f && mineObj && mineClass &&
                    (*reinterpret_cast<uint32_t*>(mineObj + 0x14) & 0x200) == 0)
                {
                    *scanTimer += *reinterpret_cast<float*>(mineClass + kProximityMineClassScanPeriodOffset);
                    const float range = *reinterpret_cast<float*>(mineClass + kProximityMineClassRangeOffset);
                    const float rangeSq = range * range;
                    const float* minePos = reinterpret_cast<float*>(mineBytes + kProximityMinePositionOffset);

                    void* collisionRangeSearch = *reinterpret_cast<void**>(kCollisionRangeSearchAddr);
                    if (collisionRangeSearch && g_BzrFn_CollisionRangeSearch && g_BzrFn_RangeResultsGetNext)
                    {
                        ShieldTowerRangeSearchResults results = {};
                        g_BzrFn_CollisionRangeSearch(
                            collisionRangeSearch,
                            static_cast<double>(minePos[0] - range),
                            static_cast<double>(minePos[2] - range),
                            static_cast<double>(minePos[0] + range),
                            static_cast<double>(minePos[2] + range),
                            &results);

                        uint32_t* handlePtr = nullptr;
                        while (g_BzrFn_RangeResultsGetNext(&results, &handlePtr) != 0)
                        {
                            if (!handlePtr)
                                continue;
                            auto* target = static_cast<uint8_t*>(
                                g_BzrFn_GameObjectGetObjByHandle(static_cast<int>(*handlePtr)));
                            if (!target || target == mineBytes)
                                continue;
                            auto* targetObj = *reinterpret_cast<uint8_t**>(target + kGameObjectObjOffset);
                            if (!targetObj || (*reinterpret_cast<uint32_t*>(targetObj + 0x14) & 0x200) != 0)
                                continue;
                            const float* targetPos = TryCallEntityGetPosition(target);
                            if (!targetPos)
                                continue;
                            const float offset[3] = {
                                targetPos[0] - minePos[0],
                                targetPos[1] - minePos[1],
                                targetPos[2] - minePos[2]
                            };
                            if (offset[0] * offset[0] + offset[1] * offset[1] + offset[2] * offset[2] > rangeSq)
                                continue;

                            if (TeamFilterShouldAffectObject(proximityMinePtr, target, filter))
                            {
                                const float* velocity = reinterpret_cast<float*>(target + kGameObjectVelocityOffset);
                                if (offset[0] * velocity[0] + offset[1] * velocity[1] + offset[2] * velocity[2] > 0.0f)
                                    detonate = true;
                            }
                            else if (g_BzrFn_GameObjectFriendP(proximityMinePtr, target))
                            {
                                detonate = false;
                                break;
                            }
                        }
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                detonate = false;
            }

            if (detonate)
                DetonateProximityMineLikeStock(proximityMinePtr);

            if (g_BzrFn_MineSimulate)
                g_BzrFn_MineSimulate(proximityMinePtr, dt);
        }
    }

}
