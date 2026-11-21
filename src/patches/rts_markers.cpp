// rts_markers.cpp
// BZR Open Shim - RTS markers: terrain-conforming ground rings, drawn locally
// for the local player only. Two features share one ring renderer:
//
//  * [Gameplay] RtsCommandPings (default on): one short ping per order the
//    local ControlPanel issues. Go: a green ring shrinking onto the point;
//    Attack on an object: a red ring around the target that follows it; any
//    other targeted order: a yellow ring.
//  * [Gameplay] RtsArtilleryRange (default on): a max-range ring around every
//    selected own-team howitzer (HowitzerVtable / HowitzerSecondaryVtable),
//    plus a cursor ring at the reticle point, green when one of them can
//    reach it and red when none can. Never on the piloted vehicle: the laser
//    sight's mortar arc already covers that.
//
// Nothing here is sent, saved or written to the engine: the rings are
// shim-owned Ogre ManualObjects. No network gate (local visuals only).
//
// Ring renderer: a fixed pool (RtsMarkers::kPoolSize) of ManualObjects, each
// on its own child of the root scene node, created on first use and then only
// rebuilt (beginUpdate), moved and shown/hidden; never created or destroyed
// per frame. A ring's node sits at its centre in render space and its
// vertices are local offsets, so the node absorbs the render origin and the
// vertices stay small. Each vertex samples Terrain::HeightAt and is lifted
// RtsMarkers::kLift above it. Material: rts_markers_assets.h.
//
// Order sources (Docs/RTS_MARKERS.md, "Order paths"):
//  * ControlPanel::BroadcastCommand(what, VECTOR_3D*) 0x004A70C0: ground
//    orders. Its detour belongs to producer_rally_points.cpp; this file only
//    registers a listener on it (SetBroadcastCommandListener).
//  * ControlPanel::BroadcastCommand(what, GameObject*) 0x004A7050: orders on
//    an object. Its own entry detour, "RTS Markers Object Command Hook" in
//    scripts/patches.json, a pass-through.
//
// Driver: TickRtsMarkers, from ChunkEffect::Simulate on the game thread
// (bzr_hooks.cpp), the same point as the rally beacons; never inside
// render-queue traversal. Teardown: lifecycle_seams.cpp.
//
// The same tick drives the RTS placement aids (rts_placement.cpp): the build
// ghosts first, then this pool draws their power rings ([Gameplay]
// RtsPowerRange, slots RtsMarkers::kFirstPowerSlot..) and the waypoint lines
// ([Gameplay] RtsWaypointLines: a thin draped ribbon from each selected
// own-team unit to its current order's destination, slots
// kFirstWaypointSlot.., and a dimmer one on to its pending order's,
// kFirstPendingSlot..). An order on an object (attack, follow, defend...)
// ends its line at the object's live position, and the object gets a ring
// in the line's colour (slots kFirstTargetRingSlot.., one per object).
//
// [Gameplay] RtsAttackMarks (default off): a pulsing red ring around every
// own-team object (units and buildings) an enemy hit in the last 2 s, the
// window the stock radar flashes its blip for (slots kFirstAttackRingSlot..).
// Detection reads the engine's own GameObject::enemyShot stamp; no hook.
//
// [Gameplay] RtsOrderQueue (rts_order_queue.cpp): an amber chain of lines and
// target rings for the queued orders of the selected units (slots
// kFirstQueueLineSlot.. and kFirstQueueRingSlot..), drawn whenever it is on.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "contextual_hud.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "hud_visibility.h"
#include "rts_markers.h"
#include "rts_markers_assets.h"
#include "rts_markers_policy.h"
#include "rts_placement.h"
#include "rts_placement_policy.h"
#include "rts_range_labels.h"
#include "rts_range_rings_policy.h"
#include "rts_radar_pings_policy.h"
#include "scene_mutation_drain.h"
#include "shell_casing_physics.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <unordered_map>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error RtsMarkers reads the GOG x86 engine layout
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace RM = RtsMarkers;
            namespace SC = ShellCasings;
            namespace RRP = RtsRadarPings;
            namespace RR = RtsRangeRings;
            using Vec3 = SC::Vec3;

            constexpr const char* kComponent = "rtsmarkers";
            constexpr const char* kHookName = "RTS Markers Object Command Hook";

            // ControlPanel selection: handles at +0x1C, count at +0x188; both
            // pinned by the hook pattern (`3B 91 88 01 00 00`, `8B 54 81 1C`).
            constexpr size_t kSelectHandlesOffset = 0x1C;
            constexpr size_t kSelectCountOffset = 0x188;
            constexpr int kSelectMax = static_cast<int>((kSelectCountOffset - kSelectHandlesOffset) / 4);
            // Planned route (the data the stock Shift+F9 AI debug view draws):
            // GameObject +0xFC AiProcess*, process +0x38 current task*; a
            // UnitTask holds an int state at +0x08 (2 = GOTO), the AiPath* plan
            // at +0x40 and the uint32 current point index at +0x44. AiPath +0x04
            // is the int point count, +0x08 a float* of {x, z} pairs.
            // GOG:0x006004A0 / GOG:0x00601070
            constexpr size_t kGameObjectAiProcessOffset = 0xFC;
            constexpr size_t kAiProcessTaskOffset = 0x38;
            constexpr size_t kTaskStateOffset = 0x08;
            constexpr size_t kTaskPathOffset = 0x40;
            constexpr size_t kTaskPathIndexOffset = 0x44;
            constexpr size_t kPathCountOffset = 0x04;
            constexpr size_t kPathPointsOffset = 0x08;
            constexpr int kTaskStateGoto = 2;
            constexpr int kMaxEngineRoutePoints = 512;
            // ControlPanel +0x1124: VECTOR_3D* of the reticle/satellite cursor
            // point (row RtsMarkersCursorPointField).
            constexpr size_t kCursorPointOffset = 0x1124;
            // Weapon/ordnance layout, as LaserSight (rows LaserArc*).
            constexpr size_t kWeaponClassOffset = 0x08;
            constexpr size_t kWeaponOrdnanceClassOffset = 0x0C;
            constexpr size_t kClassSigOffset = 0x0C;
            constexpr size_t kOrdnanceLifeSpanOffset = 0x50;
            constexpr size_t kOrdnanceShotSpeedOffset = 0x54;
            constexpr int kWeaponSlots = 5; // Carrier slots +0x18..+0x28, mask at +0x2C
            // As laser_sight.cpp: GameObject +0x0F0 render bridge, bridge
            // +0x094 Ogre entity.
            constexpr size_t kGameObjectRenderBridgeOffset = 0x0F0;
            constexpr size_t kRenderBridgeWorldEntityOffset = 0x094;
            constexpr float kCursorRadius = 3.0f;
            constexpr int kOgreTriangleStrip = 5; // RenderOperation::OT_TRIANGLE_STRIP

            // ---- Config ------------------------------------------------------
            bool g_ConfigLoaded = false;
            bool g_PingsOn = true;
            bool g_RangeOn = true;
            bool g_AttackOn = false;
            bool g_WeaponOn = true;       // [Gameplay] RtsWeaponRange
            bool g_RadarRangeOn = false;  // [Gameplay] RtsRadarRange
            bool g_MineRangeOn = false;   // [Gameplay] RtsMineRange
            bool g_RangeLabelsOn = true;  // [Gameplay] RtsRangeLabels
            int g_RangeLoggedState = -1;  // change-only "range rings" line
            int g_AttackLoggedState = -1; // change-only "enabled" line
            bool g_RadarPingsOn = false;
            bool g_RadarPostDrawRegistered = false; // the registration succeeded
            int g_RadarLoggedState = -1;            // change-only "enabled/installed" line

            void OnGroundCommand(void* panel, int what, const float* where);
            void RadarPingsPostDraw(void* radar, float opacity);

            void LoadConfig()
            {
                bool value = true;
                g_PingsOn = TryGetUserConfigBool("Gameplay", "RtsCommandPings", value) ? value : true;
                value = true;
                g_RangeOn = TryGetUserConfigBool("Gameplay", "RtsArtilleryRange", value) ? value : true;
                value = false;
                g_AttackOn = TryGetUserConfigBool("Gameplay", "RtsAttackMarks", value) ? value : false;
                if (g_AttackLoggedState != (g_AttackOn ? 1 : 0))
                {
                    g_AttackLoggedState = g_AttackOn ? 1 : 0;
                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] attack marks enabled=%d", g_AttackLoggedState);
                }
                value = false;
                g_RadarPingsOn = TryGetUserConfigBool("Gameplay", "RtsRadarPings", value) ? value : false;
                if (g_RadarPingsOn && !g_RadarPostDrawRegistered)
                    g_RadarPostDrawRegistered = ContextualHud::RegisterRadarPostDraw(&RadarPingsPostDraw);
                {
                    const int state = (g_RadarPingsOn ? 1 : 0) | (g_RadarPostDrawRegistered ? 2 : 0);
                    if (g_RadarLoggedState != state)
                    {
                        g_RadarLoggedState = state;
                        LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] radar pings enabled=%d installed=%d",
                                 g_RadarPingsOn ? 1 : 0, g_RadarPostDrawRegistered ? 1 : 0);
                    }
                }
                value = true;
                g_WeaponOn = TryGetUserConfigBool("Gameplay", "RtsWeaponRange", value) ? value : true;
                value = false;
                g_RadarRangeOn = TryGetUserConfigBool("Gameplay", "RtsRadarRange", value) ? value : false;
                value = false;
                g_MineRangeOn = TryGetUserConfigBool("Gameplay", "RtsMineRange", value) ? value : false;
                value = true;
                g_RangeLabelsOn = TryGetUserConfigBool("Gameplay", "RtsRangeLabels", value) ? value : true;
                {
                    const int state = (g_WeaponOn ? 1 : 0) | (g_RadarRangeOn ? 2 : 0) | (g_MineRangeOn ? 4 : 0) |
                                      (g_RangeLabelsOn ? 8 : 0);
                    if (g_RangeLoggedState != state)
                    {
                        g_RangeLoggedState = state;
                        LogShimA(LogLevel::Info, kComponent,
                                 "[RTSRANGE] config weapon=%d radar=%d mine=%d labels=%d", g_WeaponOn ? 1 : 0,
                                 g_RadarRangeOn ? 1 : 0, g_MineRangeOn ? 1 : 0, g_RangeLabelsOn ? 1 : 0);
                    }
                }
                g_ConfigLoaded = true;
                // The ground-order listener on the rally detour; registered
                // whatever the option says (the listener checks it), so turning
                // the option on later needs nothing else.
                SetBroadcastCommandListener(&OnGroundCommand);
                LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] config pings=%d artilleryRange=%d",
                         g_PingsOn ? 1 : 0, g_RangeOn ? 1 : 0);
            }

            // ---- Engine API --------------------------------------------------
            using FnGetPlayer = void*(__cdecl*)();
            using FnThisPointer = void*(__thiscall*)(void*);
            using FnGetWeapon = void*(__thiscall*)(void*, int);
            using FnGetObj = void*(__cdecl*)(uint32_t handle);
            using FnGetHandle = uint32_t(__thiscall*)(void*);
            using FnTerrainHeightAt = double(__cdecl*)(double x, double z);
            using FnObjectBroadcast = void(__thiscall*)(void* panel, int what, void* target);
            using FnGetTime = float(__cdecl*)(); // game-local clock (row HudFadeRadarTime), as contextual_hud.cpp

            struct EngineApi
            {
                uintptr_t panel = 0;
                FnGetObj getObj = nullptr;
                FnGetPlayer getPlayer = nullptr;
                FnThisPointer getCarrier = nullptr;
                FnGetWeapon getWeapon = nullptr;
                FnTerrainHeightAt heightAt = nullptr;
                bool cursor = false;    // RtsMarkersCursorPointField bound
                bool artillery = false; // LaserArc* layout rows bound
                FnGetTime getTime = nullptr; // null: no attack marks
                uintptr_t objectList = 0;    // GameObject::objectList; 0: no attack marks
                bool attempted = false;
                bool usable = false;
            };
            EngineApi g_Api;

            bool BindApi()
            {
                if (g_Api.attempted)
                    return g_Api.usable;
                g_Api.attempted = true;
                uint32_t panel = 0, getObj = 0, player = 0, carrier = 0;
                const HookEngine::EngineRow rows[] = {
                    {"ControlPanelGlobal", &panel},
                    {"GameObjectHandleGetObj", &getObj},
                    {"HudFadeGetPlayer", &player},
                    {"HudFadeGetCarrier", &carrier},
                };
                const uint32_t heightAt = HookEngine::ResolveNamedAddress("Terrain::HeightAt");
                if (!HookEngine::BindEngineRows("RTS markers", rows) || !heightAt)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "[RTSMARKERS] stands down: engine rows unresolved (Terrain::HeightAt=0x%08X)", heightAt);
                    return false;
                }
                g_Api.panel = panel;
                g_Api.getObj = reinterpret_cast<FnGetObj>(static_cast<uintptr_t>(getObj));
                g_Api.getPlayer = reinterpret_cast<FnGetPlayer>(static_cast<uintptr_t>(player));
                g_Api.getCarrier = reinterpret_cast<FnThisPointer>(static_cast<uintptr_t>(carrier));
                g_Api.heightAt = reinterpret_cast<FnTerrainHeightAt>(static_cast<uintptr_t>(heightAt));

                uint32_t cursorField = 0;
                const HookEngine::EngineRow cursorRows[] = {
                    {"RtsMarkersCursorPointField", &cursorField},
                };
                g_Api.cursor = HookEngine::BindEngineRows("RTS markers cursor", cursorRows);

                // Artillery reads the weapon/ordnance layout LaserSight pins.
                uint32_t weaponClass = 0, weaponOrdnance = 0, lifeSpan = 0, shotSpeed = 0, gravity = 0;
                uint32_t grenade = 0, mortar = 0, cannon = 0;
                const HookEngine::EngineRow artilleryRows[] = {
                    {"LaserArcWeaponClassField", &weaponClass},
                    {"LaserArcWeaponOrdnanceField", &weaponOrdnance},
                    {"LaserArcOrdnanceLifeSpan", &lifeSpan},
                    {"LaserArcOrdnanceShotSpeed", &shotSpeed},
                    {"LaserArcGrenadeGravity", &gravity},
                    {"LaserArcGrenadeSig", &grenade},
                    {"LaserArcMortarSig", &mortar},
                    {"LaserArcCannonSig", &cannon},
                };
                const uint32_t weapon = HookEngine::ResolveNamedAddress("Carrier::GetWeapon");
                g_Api.artillery = HookEngine::BindEngineRows("RTS markers artillery", artilleryRows) && weapon;
                g_Api.getWeapon = reinterpret_cast<FnGetWeapon>(static_cast<uintptr_t>(weapon));

                // The attack marks walk the object vector and read the
                // game-local clock (Get_TimeLocal): the one SetDamageFlags
                // stamps enemyShot with and the radar compares against. The
                // sim clock (GetGameTime) follows the network offset in MP.
                uint32_t getTime = 0;
                const HookEngine::EngineRow timeRows[] = {
                    {"HudFadeRadarTime", &getTime},
                };
                const uint32_t objectList = HookEngine::ResolveNamedAddress("GameObject::objectList");
                if (HookEngine::BindEngineRows("RTS markers attack marks", timeRows) && objectList)
                {
                    g_Api.getTime = reinterpret_cast<FnGetTime>(static_cast<uintptr_t>(getTime));
                    g_Api.objectList = objectList;
                }

                g_Api.usable = true;
                LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] engine rows bound (cursor=%d artillery=%d attack=%d)",
                         g_Api.cursor ? 1 : 0, g_Api.artillery ? 1 : 0, g_Api.getTime ? 1 : 0);
                return true;
            }

            // ---- Fault-safe engine access (no C++ objects in these frames) ---
            bool ReadInt(uintptr_t address, int& out)
            {
                if (address < 0x10000)
                    return false;
                __try
                {
                    out = *reinterpret_cast<const int*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadVector(uintptr_t address, float out[3])
            {
                if (address < 0x10000)
                    return false;
                __try
                {
                    const float* v = reinterpret_cast<const float*>(address);
                    out[0] = v[0];
                    out[1] = v[1];
                    out[2] = v[2];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out[0]) && std::isfinite(out[1]) && std::isfinite(out[2]);
            }

            void* SafeGetObj(uint32_t handle)
            {
                if (!g_Api.getObj || handle == 0)
                    return nullptr;
                __try
                {
                    return g_Api.getObj(handle);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            uint32_t SafeGetHandle(void* obj)
            {
                const auto fn = reinterpret_cast<FnGetHandle>(g_GameObjectGetHandleAddr);
                if (!fn || !obj)
                    return 0;
                __try
                {
                    return fn(obj);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
            }

            void* SafeGetPlayer()
            {
                if (!g_Api.getPlayer)
                    return nullptr;
                __try
                {
                    return g_Api.getPlayer();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool SameTeam(void* obj, void* player)
            {
                int team = -1, playerTeam = -2;
                return obj && player &&
                       ReadInt(reinterpret_cast<uintptr_t>(obj) + kGameObjectActualTeamOffset, team) &&
                       ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) &&
                       team == playerTeam;
            }

            // Copies `pairs` {x, z} floats; all must be finite.
            bool CopyRoutePointsSeh(uintptr_t address, float* out, unsigned pairs)
            {
                if (address < 0x10000)
                    return false;
                __try
                {
                    const float* in = reinterpret_cast<const float*>(address);
                    for (unsigned i = 0; i < 2 * pairs; ++i)
                    {
                        out[i] = in[i];
                        if (!std::isfinite(out[i]))
                            return false;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return true;
            }

            bool TerrainHeightSeh(double x, double z, double& out)
            {
                if (!g_Api.heightAt)
                    return false;
                __try
                {
                    out = g_Api.heightAt(x, z);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out) && std::fabs(out) < 1.0e6;
            }

            bool ReadRenderOrigin(Vec3& out)
            {
                const uintptr_t originAddr = WorldRenderOriginAddr();
                if (!originAddr)
                    return false;
                __try
                {
                    const float* origin = reinterpret_cast<const float*>(originAddr);
                    out = {origin[0], origin[1], origin[2]};
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return SC::Finite(out);
            }

            // Longest flat-ground range over the unit's gravity-ordnance
            // cannon/howitzer slots; false when it carries none.
            struct Artillery
            {
                float speed = 0.0f;
                float lifeSpan = 0.0f;
                float range = 0.0f;
            };

            bool ReadArtillerySeh(void* obj, Artillery& out)
            {
                out = Artillery{};
                __try
                {
                    void* carrier = g_Api.getCarrier(obj);
                    if (!carrier)
                        return false;
                    for (int slot = 0; slot < kWeaponSlots; ++slot)
                    {
                        const uint8_t* weapon = static_cast<const uint8_t*>(g_Api.getWeapon(carrier, slot));
                        if (!weapon)
                            continue;
                        const uint8_t* weaponClass = *reinterpret_cast<const uint8_t* const*>(weapon + kWeaponClassOffset);
                        const uint8_t* ordnance =
                            *reinterpret_cast<const uint8_t* const*>(weapon + kWeaponOrdnanceClassOffset);
                        if (!weaponClass || !ordnance)
                            continue;
                        if (!RM::IsArtilleryWeapon(*reinterpret_cast<const uint32_t*>(weaponClass + kClassSigOffset),
                                                   *reinterpret_cast<const uint32_t*>(ordnance + kClassSigOffset)))
                            continue;
                        const float speed = *reinterpret_cast<const float*>(ordnance + kOrdnanceShotSpeedOffset);
                        const float life = *reinterpret_cast<const float*>(ordnance + kOrdnanceLifeSpanOffset);
                        const float range = RM::FlatMaxRange(speed, life);
                        if (range > out.range)
                        {
                            out.speed = speed;
                            out.lifeSpan = life;
                            out.range = range;
                        }
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out = Artillery{};
                    return false;
                }
                return out.range > 0.0f;
            }

            // Longest straight-flying reach over the unit's Cannon-class
            // weapons whose ordnance is not a gravity shell (those are the
            // artillery ring's): shotSpeed * lifeSpan - 1, as ai_odf_tuning.cpp.
            // Only the Cannon class (signature 'CANN', LaserSight) qualifies in
            // v1: homing and guided weapons are other classes and are skipped.
            bool ReadDirectFireSeh(void* obj, float& range)
            {
                range = 0.0f;
                __try
                {
                    void* carrier = g_Api.getCarrier(obj);
                    if (!carrier)
                        return false;
                    for (int slot = 0; slot < kWeaponSlots; ++slot)
                    {
                        const uint8_t* weapon = static_cast<const uint8_t*>(g_Api.getWeapon(carrier, slot));
                        if (!weapon)
                            continue;
                        const uint8_t* weaponClass = *reinterpret_cast<const uint8_t* const*>(weapon + kWeaponClassOffset);
                        const uint8_t* ordnance =
                            *reinterpret_cast<const uint8_t* const*>(weapon + kWeaponOrdnanceClassOffset);
                        if (!weaponClass || !ordnance)
                            continue;
                        const uint32_t weaponSig = *reinterpret_cast<const uint32_t*>(weaponClass + kClassSigOffset);
                        const uint32_t ordnanceSig = *reinterpret_cast<const uint32_t*>(ordnance + kClassSigOffset);
                        if (weaponSig != LaserSight::kWeaponSigCannon || ordnanceSig == 0 ||
                            LaserSight::IsBallisticOrdnance(ordnanceSig))
                            continue;
                        const float reach = RR::DirectFireRange(
                            *reinterpret_cast<const float*>(ordnance + kOrdnanceShotSpeedOffset),
                            *reinterpret_cast<const float*>(ordnance + kOrdnanceLifeSpanOffset));
                        if (reach > range)
                            range = reach;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    range = 0.0f;
                    return false;
                }
                return range > 0.0f;
            }

            // ---- Radar range ---------------------------------------------------
            // [CraftClass] rangeScan, read from the unit's ODF through the shared
            // ODF path (TryGetObjectOdfToken + TryResolveOdfFilePath), cached per
            // ODF. When the file cannot be resolved, CraftClass +0x150 (rangeScan
            // in reverse_engineering/bsim/out/object_model/core_object_model.md)
            // is read behind a sanity check. UNVERIFIED on GOG 2.2.301.
            constexpr size_t kCraftClassRangeScanOffset = 0x150;
            std::unordered_map<std::string, float> g_RadarByOdf; // <= 0: no radar
            volatile long g_RangeLogBudget = 64;

            bool ReadRadarRangeFromOdf(const char* token, float& out)
            {
                out = 0.0f;
                std::filesystem::path path;
                if (!TryResolveOdfFilePath(token, path))
                    return false;
                FILE* file = nullptr;
                if (fopen_s(&file, path.string().c_str(), "r") != 0 || !file)
                    return false;
                char line[256] = {};
                while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                {
                    char* trimmed = TrimAsciiInPlace(line);
                    if (*trimmed == '\0' || *trimmed == ';' || *trimmed == '#' || *trimmed == '[')
                        continue;
                    char* equals = std::strchr(trimmed, '=');
                    if (!equals)
                        continue;
                    *equals = '\0';
                    char* key = TrimAsciiInPlace(trimmed);
                    if (_stricmp(key, "rangeScan") != 0)
                        continue;
                    char* value = TrimAsciiInPlace(equals + 1);
                    float parsed = 0.0f;
                    if (TryParseFloatValue(value, parsed) && std::isfinite(parsed))
                        out = parsed;
                    break; // a key without a usable value counts as no radar
                }
                std::fclose(file);
                return true; // the file was read; out is 0 when it has no rangeScan
            }

            bool ReadRuntimeRadarRangeSeh(void* obj, float& out)
            {
                out = 0.0f;
                __try
                {
                    const uint8_t* cls = *reinterpret_cast<const uint8_t* const*>(static_cast<const uint8_t*>(obj) +
                                                                                    kGameObjectClassOffset);
                    if (!cls)
                        return false;
                    out = *reinterpret_cast<const float*>(cls + kCraftClassRangeScanOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out = 0.0f;
                    return false;
                }
                return RR::SaneRadarRange(out);
            }

            // The scan range of one unit, 0 when it has no radar.
            float ReadRadarRange(void* obj)
            {
                char token[kProducerBuildMenuTokenLen + 1] = {};
                const bool haveToken = TryGetObjectOdfToken(obj, token) && token[0];
                if (haveToken)
                {
                    const auto cached = g_RadarByOdf.find(token);
                    if (cached != g_RadarByOdf.end())
                        return cached->second;
                }
                float range = 0.0f;
                const char* source = "odf";
                if (!haveToken || !ReadRadarRangeFromOdf(token, range))
                {
                    source = "runtime(+0x150, UNVERIFIED)";
                    if (!ReadRuntimeRadarRangeSeh(obj, range))
                    {
                        range = 0.0f;
                        source = "none";
                    }
                }
                if (haveToken)
                {
                    g_RadarByOdf[token] = range;
                    if (InterlockedDecrement(&g_RangeLogBudget) >= 0)
                        LogShimA(LogLevel::Info, kComponent, "[RTSRANGE] radar odf=%s range=%.1f source=%s", token, range,
                                 source);
                }
                return range;
            }

            // Bounding radius of the object's Ogre entity, or NaN.
            using FnEntityBoundingRadius = float(__thiscall*)(void*);
            FnEntityBoundingRadius EntityBoundingRadiusFn()
            {
                static const FnEntityBoundingRadius radiusOf =
                    ResolveOgreProc<FnEntityBoundingRadius>("?getBoundingRadius@Entity@Ogre@@UBEMXZ");
                return radiusOf;
            }

            float ReadBoundingRadiusSeh(void* gameObject)
            {
                const FnEntityBoundingRadius radiusOf = EntityBoundingRadiusFn();
                uintptr_t ogreBase = 0, ogreEnd = 0;
                if (!radiusOf || !gameObject || !TryGetOgreModuleRange(ogreBase, ogreEnd))
                    return std::nanf("");
                __try
                {
                    const uint8_t* bridge = *reinterpret_cast<const uint8_t* const*>(
                        static_cast<const uint8_t*>(gameObject) + kGameObjectRenderBridgeOffset);
                    if (!bridge)
                        return std::nanf("");
                    void* entity = *reinterpret_cast<void* const*>(bridge + kRenderBridgeWorldEntityOffset);
                    if (!entity)
                        return std::nanf("");
                    const uintptr_t vtable = *reinterpret_cast<const uintptr_t*>(entity);
                    if (vtable < ogreBase || vtable >= ogreEnd)
                        return std::nanf("");
                    return radiusOf(entity);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return std::nanf("");
                }
            }

            // ---- Command pings -----------------------------------------------
            RM::PingQueue<RM::kMaxPings> g_Pings;
            FnObjectBroadcast g_OrigObjectBroadcast = nullptr;
            std::atomic<bool> g_ObjectCommandHookInstalled{ false };
            volatile long g_PingLogBudget = 16;

            // The order came from the local ControlPanel with units selected.
            bool IsLocalPanelOrder(void* panel)
            {
                if (!g_ConfigLoaded)
                    LoadConfig();
                if ((!g_PingsOn && !g_RadarPingsOn) || !BindApi() || reinterpret_cast<uintptr_t>(panel) != g_Api.panel)
                    return false;
                int count = 0;
                return ReadInt(g_Api.panel + kSelectCountOffset, count) && count > 0;
            }

            // ---- Radar pings -------------------------------------------------
            // A short ring on the cockpit radar at the order's position, drawn
            // from the radar post-draw seam (contextual_hud.cpp). Local only.
            using FnHudLine = void(__cdecl*)(void* buf, int x1, int y1, int x2, int y2, uint32_t argb, uint32_t mode);

            struct RadarPingApi
            {
                FnHudLine line = nullptr;
                FnGetTime getTime = nullptr;
                uintptr_t paneBuffer = 0;
                uintptr_t spriteZ = 0;
                uintptr_t projRadius = 0, centreX = 0, centreY = 0;
                bool attempted = false;
                bool usable = false;
            };
            RadarPingApi g_RadarApi;
            RRP::RadarPingQueue g_RadarPings;
            volatile long g_RadarPingLogBudget = 8;
            constexpr size_t kRadarScannerOffset = 0x08;
            constexpr size_t kRadarUserOffset = 0x0C;
            constexpr size_t kRadarRangeOffset = 0x10;
            constexpr size_t kRadarUserPosOffset = 0x20;
            constexpr size_t kRadarBasisOffset = 0x30; // right, up, front: three float[3] rows
            constexpr float kRadarRingZStep = 0.0005f; // as the native radar's overlay bump

            bool BindRadarPingApi()
            {
                if (g_RadarApi.attempted)
                    return g_RadarApi.usable;
                g_RadarApi.attempted = true;
                uint32_t line = 0, time = 0, pane = 0, z = 0, radius = 0, cx = 0, cy = 0;
                const HookEngine::EngineRow rows[] = {
                    {"HudLine", &line},
                    {"HudFadeRadarTime", &time},
                    {"HudPaneBuffer", &pane},
                    {"HudSpriteZ", &z},
                    {"RadarProjRadius", &radius},
                    {"RadarProjCentreX", &cx},
                    {"RadarProjCentreY", &cy},
                };
                if (!HookEngine::BindEngineRows("RTS radar pings", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "[RTSMARKERS] radar pings stand down: engine rows unresolved");
                    return false;
                }
                g_RadarApi.line = reinterpret_cast<FnHudLine>(static_cast<uintptr_t>(line));
                g_RadarApi.getTime = reinterpret_cast<FnGetTime>(static_cast<uintptr_t>(time));
                g_RadarApi.paneBuffer = pane;
                g_RadarApi.spriteZ = z;
                g_RadarApi.projRadius = radius;
                g_RadarApi.centreX = cx;
                g_RadarApi.centreY = cy;
                g_RadarApi.usable = true;
                return true;
            }

            // Game-local clock; NaN when it faults.
            float ReadRadarClock() noexcept
            {
                __try
                {
                    return g_RadarApi.getTime();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return std::nanf("");
                }
            }

            // CockpitRadar: +0x08 scanner and +0x0C user object (non-null when
            // the radar works), +0x10 range, +0x20 user position, +0x30 basis.
            // The projection globals are read live (radar_layout.cpp rescales).
            bool ReadRadarSeh(void* radar, RRP::Radar& out, void*& paneBuffer) noexcept
            {
                __try
                {
                    const auto* bytes = static_cast<const uint8_t*>(radar);
                    if (!bytes || !*reinterpret_cast<void* const*>(bytes + kRadarScannerOffset) ||
                        !*reinterpret_cast<void* const*>(bytes + kRadarUserOffset))
                        return false;
                    out.range = *reinterpret_cast<const float*>(bytes + kRadarRangeOffset);
                    const auto* user = reinterpret_cast<const float*>(bytes + kRadarUserPosOffset);
                    const auto* basis = reinterpret_cast<const float*>(bytes + kRadarBasisOffset);
                    for (int i = 0; i < 3; ++i)
                    {
                        out.userPos[i] = user[i];
                        out.right[i] = basis[i];
                        out.up[i] = basis[3 + i];
                        out.front[i] = basis[6 + i];
                    }
                    out.projRadius = *reinterpret_cast<const int*>(g_RadarApi.projRadius);
                    out.centreX = *reinterpret_cast<const int*>(g_RadarApi.centreX);
                    out.centreY = *reinterpret_cast<const int*>(g_RadarApi.centreY);
                    paneBuffer = *reinterpret_cast<void* const*>(g_RadarApi.paneBuffer);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // One ring: the native overlay z bump around the line segments.
            void DrawRadarRingSeh(void* paneBuffer, int cx, int cy, float radius, uint32_t argb) noexcept
            {
                __try
                {
                    float* z = reinterpret_cast<float*>(g_RadarApi.spriteZ);
                    const float previous = *z;
                    *z = previous + kRadarRingZStep;
                    __try
                    {
                        int px = 0, py = 0;
                        RRP::RingPoint(cx, cy, radius, 0, px, py);
                        for (int i = 1; i <= RRP::kRingSegments; ++i)
                        {
                            int nx = 0, ny = 0;
                            RRP::RingPoint(cx, cy, radius, i, nx, ny);
                            g_RadarApi.line(paneBuffer, px, py, nx, ny, argb, 0);
                            px = nx;
                            py = ny;
                        }
                    }
                    __finally
                    {
                        *z = previous;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            uint32_t ToArgb(const RM::Colour& colour)
            {
                const auto channel = [](float v) {
                    return static_cast<uint32_t>(std::lround(std::fmin(std::fmax(v, 0.0f), 1.0f) * 255.0f));
                };
                return 0xFF000000u | (channel(colour.r) << 16) | (channel(colour.g) << 8) | channel(colour.b);
            }

            void QueueRadarPing(RM::PingKind kind, const float pos[3])
            {
                if (!BindRadarPingApi())
                    return;
                const float now = ReadRadarClock();
                if (!std::isfinite(now))
                    return;
                RRP::Ping ping;
                ping.pos[0] = pos[0];
                ping.pos[1] = pos[1];
                ping.pos[2] = pos[2];
                ping.argb = ToArgb(RM::StyleFor(kind).colour);
                ping.birth = now;
                g_RadarPings.Push(ping);
            }

            // Radar post-draw (frame thread, inside SEH): the live rings.
            void RadarPingsPostDraw(void* radar, float opacity)
            {
                if (!g_RadarPingsOn || !radar || !BindRadarPingApi())
                    return;
                const float now = ReadRadarClock();
                if (!std::isfinite(now) || g_RadarPings.Prune(now) == 0)
                    return;
                RRP::Radar view;
                void* paneBuffer = nullptr;
                if (!ReadRadarSeh(radar, view, paneBuffer) || !paneBuffer || !std::isfinite(view.range) ||
                    !(view.range > 0.0f) || view.projRadius <= 0)
                    return;
                const float* fields[] = {view.userPos, view.right, view.up, view.front};
                for (const float* row : fields)
                    for (int i = 0; i < 3; ++i)
                        if (!std::isfinite(row[i]))
                            return;
                if (!std::isfinite(opacity))
                    opacity = 1.0f;
                opacity = std::fmin(std::fmax(opacity, 0.0f), 1.0f);
                for (size_t i = 0; i < RRP::kMaxPings; ++i)
                {
                    RRP::Ping ping;
                    if (!g_RadarPings.Get(i, ping))
                        continue;
                    const RRP::Frame frame = RRP::Evaluate(now - ping.birth);
                    const RRP::Projected at = RRP::Project(view, ping.pos);
                    if (!frame.alive || !at.valid)
                        continue;
                    const uint32_t alpha = static_cast<uint32_t>(std::lround(frame.alpha * opacity * 255.0f));
                    if (alpha == 0)
                        continue;
                    DrawRadarRingSeh(paneBuffer, at.x, at.y, RRP::RadiusPixels(frame.radiusFrac, view.projRadius),
                                     (ping.argb & 0x00FFFFFFu) | (alpha << 24));
                    if (g_RadarPings.TakeLogToken(i) && InterlockedDecrement(&g_RadarPingLogBudget) >= 0)
                        LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] radar ping drawn at %d,%d%s", at.x, at.y,
                                 at.clamped ? " (clamped to the rim)" : "");
                }
            }

            void QueuePing(RM::PingKind kind, const float pos[3], uint32_t targetHandle, float baseRadius, int what)
            {
                if (g_RadarPingsOn)
                    QueueRadarPing(kind, pos);
                if (!g_PingsOn)
                    return;
                RM::PingSlot ping;
                ping.kind = kind;
                ping.baseRadius = baseRadius;
                ping.pos[0] = pos[0];
                ping.pos[1] = pos[1];
                ping.pos[2] = pos[2];
                ping.targetHandle = targetHandle;
                g_Pings.Push(ping);
                if (InterlockedDecrement(&g_PingLogBudget) >= 0)
                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] ping what=%d kind=%d at %.1f,%.1f%s", what,
                             static_cast<int>(kind), pos[0], pos[2], targetHandle ? " (follows target)" : "");
            }

            // Listener on the rally detour of 0x004A70C0 (ground point).
            void OnGroundCommand(void* panel, int what, const float* where)
            {
                try
                {
                    // Any player order that reaches the broadcast ends the
                    // selected units' queued orders (RtsOrderQueue).
                    NoteRtsOrderQueuePlainBroadcast(panel);
                    if (!where || !IsLocalPanelOrder(panel))
                        return;
                    const RM::PingKind kind = RM::ClassifyPing(what, false);
                    float pos[3] = {};
                    if (kind == RM::PingKind::None || !ReadVector(reinterpret_cast<uintptr_t>(where), pos))
                        return;
                    QueuePing(kind, pos, 0, RM::kGroundPingRadius, what);
                }
                catch (...)
                {
                }
            }

            void OnObjectCommand(void* panel, int what, void* target)
            {
                try
                {
                    if (!target || !IsLocalPanelOrder(panel))
                        return;
                    const RM::PingKind kind = RM::ClassifyPing(what, true);
                    float pos[3] = {};
                    if (kind == RM::PingKind::None || !TryGetGameObjectWorldPosition(target, pos))
                        return;
                    // Attack follows its target; the other object orders mark
                    // where the target was when the order was given.
                    const uint32_t handle = kind == RM::PingKind::Attack ? SafeGetHandle(target) : 0;
                    QueuePing(kind, pos, handle, RM::TargetRingRadius(ReadBoundingRadiusSeh(target)), what);
                }
                catch (...)
                {
                }
            }

            // ControlPanel::BroadcastCommand(what, GameObject* target)
            // 0x004A7050: thiscall, two stack arguments, ret 8.
            void __fastcall ObjectBroadcastDetour(void* panel, void* /*edx*/, int what, void* target)
            {
                NoteRtsOrderQueuePlainBroadcast(panel);
                OnObjectCommand(panel, what, target);
                g_OrigObjectBroadcast(panel, what, target);
            }

            // ---- Ring pool ---------------------------------------------------
            using FnSetCastShadows = void(__thiscall*)(void*, bool);
            using FnManualColour = void(__thiscall*)(void*, float, float, float, float);

            struct OgreApi
            {
                FnOgreCreateManualObject createManualObject = nullptr;
                FnOgreGetRootSceneNode getRootSceneNode = nullptr;
                FnOgreCreateChildSceneNode createChildSceneNode = nullptr;
                FnOgreAttachObject attachObject = nullptr;
                FnOgreManualObjectSetDynamic setDynamic = nullptr;
                FnOgreManualObjectEstimateCount estimateVertices = nullptr;
                FnOgreManualObjectBegin begin = nullptr;
                FnOgreManualObjectBeginUpdate beginUpdate = nullptr;
                FnOgreManualObjectVertex3 position = nullptr;
                FnManualColour colour = nullptr;
                FnOgreManualObjectEnd end = nullptr;
                FnOgreSetVisible setVisible = nullptr;
                FnOgreSetNodePosition setNodePosition = nullptr;
                FnSetCastShadows setCastShadows = nullptr;
                bool usable = false;
            };

            const OgreApi& GetOgreApi()
            {
                static OgreApi api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.createManualObject = ResolveOgreProc<FnOgreCreateManualObject>(
                    "?createManualObject@SceneManager@Ogre@@UAEPAVManualObject@2@XZ");
                api.getRootSceneNode =
                    ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
                api.createChildSceneNode = ResolveOgreProc<FnOgreCreateChildSceneNode>(
                    "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
                api.attachObject =
                    ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
                api.setDynamic = ResolveOgreProc<FnOgreManualObjectSetDynamic>("?setDynamic@ManualObject@Ogre@@UAEX_N@Z");
                api.estimateVertices =
                    ResolveOgreProc<FnOgreManualObjectEstimateCount>("?estimateVertexCount@ManualObject@Ogre@@UAEXI@Z");
                api.begin = ResolveOgreProc<FnOgreManualObjectBegin>(
                    "?begin@ManualObject@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@"
                    "W4OperationType@RenderOperation@2@0@Z");
                api.beginUpdate = ResolveOgreProc<FnOgreManualObjectBeginUpdate>("?beginUpdate@ManualObject@Ogre@@UAEXI@Z");
                api.position = ResolveOgreProc<FnOgreManualObjectVertex3>("?position@ManualObject@Ogre@@UAEXMMM@Z");
                api.colour = ResolveOgreProc<FnManualColour>("?colour@ManualObject@Ogre@@UAEXMMMM@Z");
                api.end = ResolveOgreProc<FnOgreManualObjectEnd>("?end@ManualObject@Ogre@@UAEPAVManualObjectSection@12@XZ");
                api.setVisible = ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
                api.setNodePosition = ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
                api.setCastShadows = ResolveOgreProc<FnSetCastShadows>("?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
                api.usable = api.createManualObject && api.getRootSceneNode && api.createChildSceneNode &&
                             api.attachObject && api.setDynamic && api.estimateVertices && api.begin &&
                             api.beginUpdate && api.position && api.colour && api.end && api.setVisible &&
                             api.setNodePosition && api.setCastShadows;
                if (!api.usable)
                    LogShimA(LogLevel::Warn, kComponent, "[RTSMARKERS] Ogre exports unresolved; rings unavailable");
                return api;
            }

            // Ogre takes these by const reference; kept alive for the process
            // so the SEH frames below hold no C++ objects.
            const std::string& MaterialName()
            {
                static const std::string name = RM::kMaterialName;
                return name;
            }
            const std::string& MaterialGroup()
            {
                static const std::string group = kChunkPayloadResourceRootName;
                return group;
            }

            struct RingSlot
            {
                void* sceneManager = nullptr;
                void* node = nullptr;
                void* manual = nullptr;
                bool sectionCreated = false;
                bool visible = false;
                // Last built geometry; equal requests skip the rebuild.
                float key[10] = {};
                bool keyValid = false;
                uint32_t routeHash = 0;
            };
            RingSlot g_Slots[RM::kSlotCount];
            bool g_AnyVisible = false;
            bool g_PoolFailed = false; // creation failed in this scene; not retried until it changes
            void* g_PoolSceneManager = nullptr;

            struct RingRequest
            {
                bool wanted = false;
                float centre[3] = {}; // sim space; a line's start
                float radius = 0.0f;
                RM::Colour colour;
                bool line = false;   // a draped line from centre to end
                float end[2] = {};   // sim x, z of a line's end
                // A line that follows a planned route: sim {x, z} points from
                // the unit's position (the first) to the goal.
                unsigned routeCount = 0;
                float route[2 * RtsPlacement::kMaxRoutePoints] = {};
            };

            // One ring's strip, built before begin() so nothing between
            // begin() and end() can fail half-way except Ogre itself.
            struct StripVertex
            {
                float x, y, z;
            };
            constexpr unsigned kMaxStripVertices = 2u * (RM::kMaxSegments + 1u);

            unsigned BuildStrip(const RingRequest& request, StripVertex (&out)[kMaxStripVertices])
            {
                const unsigned segments = RM::SegmentsFor(request.radius);
                const RM::Band band = RM::RingBand(request.radius, RM::RingWidthFor(request.radius));
                unsigned n = 0;
                const double cx = request.centre[0], cz = request.centre[2];
                double lastInner = request.centre[1], lastOuter = request.centre[1];
                for (unsigned i = 0; i <= segments; ++i)
                {
                    float dx = 0.0f, dz = 0.0f;
                    RM::RingDirection(i, segments, dx, dz);
                    const float ix = dx * band.inner, iz = dz * band.inner;
                    const float ox = dx * band.outer, oz = dz * band.outer;
                    double hi = lastInner, ho = lastOuter;
                    if (!TerrainHeightSeh(cx + ix, cz + iz, hi))
                        hi = lastInner; // off the map: keep the neighbour's height
                    if (!TerrainHeightSeh(cx + ox, cz + oz, ho))
                        ho = lastOuter;
                    lastInner = hi;
                    lastOuter = ho;
                    // Sim -> render: x and y keep their sign, z flips.
                    out[n++] = {ix, RM::LocalVertexY(static_cast<float>(hi), request.centre[1]), -iz};
                    out[n++] = {ox, RM::LocalVertexY(static_cast<float>(ho), request.centre[1]), -oz};
                }
                return n;
            }

            static_assert(RtsPlacement::kMaxLineSegments <= RM::kMaxSegments, "a line fits the ring strip budget");

            // A planned-route line: the same ribbon, bent through each route
            // point (RtsPlacement::BuildRouteSamples), draped like a line.
            unsigned BuildRouteStrip(const RingRequest& request, StripVertex (&out)[kMaxStripVertices])
            {
                RtsPlacement::RouteSample samples[RtsPlacement::kMaxRouteSamples];
                const unsigned count =
                    RtsPlacement::BuildRouteSamples(request.route, request.routeCount, RtsPlacement::kLineWidth, samples);
                unsigned n = 0;
                double last = request.centre[1];
                for (unsigned i = 0; i < count; ++i)
                {
                    const RtsPlacement::RouteSample& s = samples[i];
                    double h = last;
                    if (!TerrainHeightSeh(request.centre[0] + s.x, request.centre[2] + s.z, h))
                        h = last;
                    last = h;
                    const float y = RM::LocalVertexY(static_cast<float>(h), request.centre[1]);
                    out[n++] = {s.x + s.px, y, -(s.z + s.pz)};
                    out[n++] = {s.x - s.px, y, -(s.z - s.pz)};
                }
                return n;
            }

            // A waypoint line: a ribbon kLineWidth wide from centre to end,
            // sampled every kLineSegmentLength metres along the ground, in the
            // same node-local frame as a ring.
            unsigned BuildLineStrip(const RingRequest& request, StripVertex (&out)[kMaxStripVertices])
            {
                if (request.routeCount >= 2)
                {
                    const unsigned n = BuildRouteStrip(request, out);
                    if (n >= 4)
                        return n;
                    // A degenerate route (every point under the unit): draw
                    // the straight line instead.
                }
                const float dx = request.end[0] - request.centre[0];
                const float dz = request.end[1] - request.centre[2];
                const float length = std::sqrt(dx * dx + dz * dz);
                if (!std::isfinite(length) || !(length > 0.0f))
                    return 0;
                const float half = 0.5f * RtsPlacement::kLineWidth;
                const float px = -dz / length * half, pz = dx / length * half;
                const unsigned segments = RtsPlacement::LineSegmentsFor(length);
                unsigned n = 0;
                double last = request.centre[1];
                for (unsigned i = 0; i <= segments; ++i)
                {
                    const float t = static_cast<float>(i) / static_cast<float>(segments);
                    const float x = dx * t, z = dz * t;
                    double h = last;
                    if (!TerrainHeightSeh(request.centre[0] + x, request.centre[2] + z, h))
                        h = last;
                    last = h;
                    const float y = RM::LocalVertexY(static_cast<float>(h), request.centre[1]);
                    out[n++] = {x + px, y, -(z + pz)};
                    out[n++] = {x - px, y, -(z - pz)};
                }
                return n;
            }

            // C++ exceptions from Ogre are caught here; access violations by
            // the SEH frame around it.
            bool EmitStripCpp(const OgreApi& api, RingSlot& slot, const StripVertex* vertices, unsigned count,
                              const RM::Colour& colour)
            {
                bool started = false;
                try
                {
                    if (slot.sectionCreated)
                        api.beginUpdate(slot.manual, 0);
                    else
                        api.begin(slot.manual, MaterialName(), kOgreTriangleStrip, MaterialGroup());
                    started = true;
                    for (unsigned i = 0; i < count; ++i)
                    {
                        api.position(slot.manual, vertices[i].x, vertices[i].y, vertices[i].z);
                        api.colour(slot.manual, colour.r, colour.g, colour.b, colour.a);
                    }
                    api.end(slot.manual);
                    slot.sectionCreated = true;
                    return true;
                }
                catch (...)
                {
                    if (started)
                    {
                        try
                        {
                            api.end(slot.manual);
                        }
                        catch (...)
                        {
                        }
                    }
                    return false;
                }
            }

            bool EmitStripSeh(const OgreApi& api, RingSlot& slot, const StripVertex* vertices, unsigned count,
                              const RM::Colour& colour)
            {
                __try
                {
                    return EmitStripCpp(api, slot, vertices, count, colour);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool CreateSlotCpp(const OgreApi& api, void* sceneManager, RingSlot& slot)
            {
                try
                {
                    void* root = api.getRootSceneNode(sceneManager);
                    if (!root)
                        return false;
                    const OgreVector3 origin = {0.0f, 0.0f, 0.0f};
                    const OgreQuaternion identity = {1.0f, 0.0f, 0.0f, 0.0f};
                    void* node = api.createChildSceneNode(root, origin, identity);
                    void* manual = node ? api.createManualObject(sceneManager) : nullptr;
                    if (!manual)
                        return false; // a lone node stays empty; Ogre frees it with the scene
                    api.attachObject(node, manual);
                    api.setDynamic(manual, true);
                    api.estimateVertices(manual, kMaxStripVertices);
                    api.setCastShadows(manual, false);
                    api.setVisible(manual, false);
                    slot.sceneManager = sceneManager;
                    slot.node = node;
                    slot.manual = manual;
                    return true;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool CreateSlotSeh(const OgreApi& api, void* sceneManager, RingSlot& slot)
            {
                __try
                {
                    return CreateSlotCpp(api, sceneManager, slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SetVisibleSeh(const OgreApi& api, void* manual, bool visible)
            {
                __try
                {
                    api.setVisible(manual, visible);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SetNodePositionSeh(const OgreApi& api, void* node, const Vec3& p)
            {
                __try
                {
                    api.setNodePosition(node, p.x, p.y, p.z);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void HideSlot(RingSlot& slot)
            {
                if (slot.visible && slot.manual)
                    SetVisibleSeh(GetOgreApi(), slot.manual, false);
                slot.visible = false;
            }

            void HideAll()
            {
                for (RingSlot& slot : g_Slots)
                    HideSlot(slot);
                g_AnyVisible = false;
            }

            // Drops the pointers without an Ogre call: the scene that made
            // them is gone or is being torn down (Ogre frees the objects).
            void ForgetSlots(const wchar_t* reason)
            {
                size_t held = 0;
                for (RingSlot& slot : g_Slots)
                {
                    if (slot.manual || slot.node)
                        ++held;
                    slot = RingSlot{};
                }
                g_AnyVisible = false;
                g_PoolFailed = false;
                g_PoolSceneManager = nullptr;
                if (held)
                    LogShimW(LogLevel::Info, kComponent, L"[RTSMARKERS] forgot %zu ring(s) (%ls)", held,
                             reason ? reason : L"unspecified");
            }

            bool DrawRing(const OgreApi& api, void* sceneManager, RingSlot& slot, const RingRequest& request,
                          const Vec3& origin)
            {
                if (g_PoolFailed)
                    return false;
                if (!slot.manual)
                {
                    // The material lives in the chunk payload group.
                    if (!EnsureSkinnedGibResourceLocations() || !CreateSlotSeh(api, sceneManager, slot))
                    {
                        g_PoolFailed = true;
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[RTSMARKERS] ring creation failed; rings off for this scene");
                        return false;
                    }
                }
                const float key[10] = {request.centre[0], request.centre[1], request.centre[2],
                                       request.line ? -1.0f : request.radius,
                                       request.colour.r,  request.colour.g,  request.colour.b,  request.colour.a,
                                       request.line ? request.end[0] : 0.0f, request.line ? request.end[1] : 0.0f};
                const uint32_t routeHash =
                    request.line && request.routeCount >= 2 ? RtsPlacement::RouteHash(request.route, request.routeCount) : 0u;
                if (!slot.keyValid || std::memcmp(key, slot.key, sizeof(key)) != 0 || routeHash != slot.routeHash)
                {
                    static StripVertex vertices[kMaxStripVertices];
                    const unsigned count = request.line ? BuildLineStrip(request, vertices) : BuildStrip(request, vertices);
                    if (count < 4)
                    {
                        HideSlot(slot);
                        return false;
                    }
                    if (!EmitStripSeh(api, slot, vertices, count, request.colour))
                    {
                        // The ManualObject may be left mid-section (an AV skips
                        // end()), and a missing material would fail every frame:
                        // hide everything and stop for this scene. ForgetSlots on
                        // the next scene change starts a fresh pool.
                        slot.keyValid = false;
                        g_PoolFailed = true;
                        HideAll();
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[RTSMARKERS] ring update failed; rings off for this scene");
                        return false;
                    }
                    std::memcpy(slot.key, key, sizeof(key));
                    slot.routeHash = routeHash;
                    slot.keyValid = true;
                }
                // The node follows the render origin every tick; the vertices
                // are relative to it and do not change with the origin.
                const Vec3 centre = SC::SimToRenderPoint({request.centre[0], request.centre[1], request.centre[2]}, origin);
                if (!SetNodePositionSeh(api, slot.node, centre))
                {
                    HideSlot(slot);
                    return false;
                }
                if (!slot.visible)
                {
                    if (!SetVisibleSeh(api, slot.manual, true))
                        return false;
                    slot.visible = true;
                }
                return true;
            }

            // ---- Requests ----------------------------------------------------
            struct ArtilleryUnit
            {
                float pos[3] = {};
                Artillery gun;
            };

            // True for a howitzer craft (complete object, vtable at +0).
            bool IsHowitzer(void* obj)
            {
                static const uint32_t primary = HookEngine::EngineAddress("HowitzerVtable");
                static const uint32_t secondary = HookEngine::EngineAddress("HowitzerSecondaryVtable");
                int vtable = 0;
                if (!primary || !secondary || !ReadInt(reinterpret_cast<uintptr_t>(obj), vtable))
                    return false;
                const uint32_t v = static_cast<uint32_t>(vtable);
                return v == primary || v == secondary;
            }

            // Every selected own-team howitzer carrying a gravity cannon, at
            // most kMaxArtilleryRings of them. The piloted vehicle is skipped.
            size_t GatherArtillery(ArtilleryUnit (&units)[RM::kMaxArtilleryRings])
            {
                if (!g_Api.artillery)
                    return 0;
                void* const player = SafeGetPlayer();
                if (!player)
                    return 0;
                void* candidates[kSelectMax] = {};
                size_t candidateCount = 0;
                int count = 0;
                if (ReadInt(g_Api.panel + kSelectCountOffset, count) && count > 0)
                {
                    if (count > kSelectMax)
                        count = kSelectMax;
                    for (int i = 0; i < count; ++i)
                    {
                        int handle = 0;
                        if (!ReadInt(g_Api.panel + kSelectHandlesOffset + 4 * static_cast<size_t>(i), handle) || !handle)
                            continue;
                        void* obj = SafeGetObj(static_cast<uint32_t>(handle));
                        if (!obj || obj == player || !SameTeam(obj, player) || !IsHowitzer(obj))
                            continue;
                        candidates[candidateCount++] = obj;
                    }
                }
                size_t found = 0;
                for (size_t i = 0; i < candidateCount && found < RM::kMaxArtilleryRings; ++i)
                {
                    ArtilleryUnit unit;
                    if (!ReadArtillerySeh(candidates[i], unit.gun) || !TryGetGameObjectWorldPosition(candidates[i], unit.pos))
                        continue;
                    units[found++] = unit;
                }
                return found;
            }

            // The reticle (cockpit) or satellite cursor point; false when the
            // engine holds none (aiming at the sky).
            bool ReadCursorPoint(float out[3])
            {
                if (!g_Api.cursor)
                    return false;
                int pointer = 0;
                return ReadInt(g_Api.panel + kCursorPointOffset, pointer) && pointer &&
                       ReadVector(static_cast<uintptr_t>(static_cast<uint32_t>(pointer)), out);
            }

            // Every selected own-team unit (never the piloted vehicle), at
            // most kMaxWaypointLineSlots of them.
            size_t GatherSelectedOwnUnits(void* (&units)[RM::kMaxWaypointLineSlots])
            {
                void* const player = SafeGetPlayer();
                int count = 0;
                if (!player || !ReadInt(g_Api.panel + kSelectCountOffset, count) || count <= 0)
                    return 0;
                if (count > kSelectMax)
                    count = kSelectMax;
                size_t found = 0;
                for (int i = 0; i < count && found < RM::kMaxWaypointLineSlots; ++i)
                {
                    int handle = 0;
                    if (!ReadInt(g_Api.panel + kSelectHandlesOffset + 4 * static_cast<size_t>(i), handle) || !handle)
                        continue;
                    void* obj = SafeGetObj(static_cast<uint32_t>(handle));
                    if (!obj || obj == player || !SameTeam(obj, player))
                        continue;
                    units[found++] = obj;
                }
                return found;
            }

            // The unit's remaining planned route as {x, z} pairs, the unit's
            // own position first and the goal last. False (use the straight
            // line) unless the current task is a UnitTask in GOTO state with a
            // plan and a valid point index.
            bool ReadUnitRoute(void* obj, const float pos[3], RingRequest& request, unsigned& indexOut, int& countOut)
            {
                int process = 0, task = 0, vtable = 0, state = 0, path = 0, index = 0, count = 0, points = 0;
                const uintptr_t o = reinterpret_cast<uintptr_t>(obj);
                if (!ReadInt(o + kGameObjectAiProcessOffset, process) || !process ||
                    !ReadInt(static_cast<uintptr_t>(static_cast<uint32_t>(process)) + kAiProcessTaskOffset, task) || !task ||
                    !ReadInt(static_cast<uintptr_t>(static_cast<uint32_t>(task)), vtable) || !vtable ||
                    !VtableDerivesFrom(static_cast<uintptr_t>(static_cast<uint32_t>(vtable)), ".?AVUnitTask@@"))
                    return false;
                const uintptr_t t = static_cast<uintptr_t>(static_cast<uint32_t>(task));
                if (!ReadInt(t + kTaskStateOffset, state) || state != kTaskStateGoto ||
                    !ReadInt(t + kTaskPathOffset, path) || !path || !ReadInt(t + kTaskPathIndexOffset, index))
                    return false;
                const uintptr_t p = static_cast<uintptr_t>(static_cast<uint32_t>(path));
                if (!ReadInt(p + kPathCountOffset, count) || count < 1 || count > kMaxEngineRoutePoints || index < 0 ||
                    index >= count || !ReadInt(p + kPathPointsOffset, points) || !points)
                    return false;
                const unsigned remaining = static_cast<unsigned>(count - index);
                static float buffer[2 * (kMaxEngineRoutePoints + 1)];
                buffer[0] = pos[0];
                buffer[1] = pos[2];
                if (!CopyRoutePointsSeh(static_cast<uintptr_t>(static_cast<uint32_t>(points)) + 8u * static_cast<unsigned>(index),
                                        buffer + 2, remaining))
                    return false;
                request.routeCount = RtsPlacement::TrimRoute(buffer, remaining + 1, request.route);
                indexOut = static_cast<unsigned>(index);
                countOut = count;
                return request.routeCount >= 2;
            }

            void LineRequest(RingRequest& line, const float from[3], float toX, float toZ, int what, bool pending)
            {
                if (!RtsPlacement::ShouldDrawLine(from[0], from[2], toX, toZ))
                    return;
                const RtsPlacement::LineColour c = RtsPlacement::WaypointColour(what, pending);
                line.wanted = true;
                line.line = true;
                std::memcpy(line.centre, from, sizeof(line.centre));
                line.end[0] = toX;
                line.end[1] = toZ;
                line.colour.r = c.r;
                line.colour.g = c.g;
                line.colour.b = c.b;
                line.colour.a = c.a;
            }

            // The live position of the object the unit's order targets. False
            // without one, when it is gone, when it is the unit itself or the
            // piloted vehicle (no ring under the camera), and for another
            // team's object the local team does not detect right now (the
            // line must not track an enemy the player cannot see).
            bool ReadLiveObjectPosition(void* unit, uint32_t who, float (&out)[3])
            {
                void* target = SafeGetObj(who);
                void* const player = SafeGetPlayer();
                if (!target || target == unit || target == player)
                    return false;
                if (!SameTeam(target, player))
                {
                    int playerTeam = -1, detected = 0;
                    if (!ReadInt(reinterpret_cast<uintptr_t>(player) + kGameObjectActualTeamOffset, playerTeam) ||
                        playerTeam < kGameTeamMin || playerTeam > kGameTeamMax ||
                        !ReadInt(reinterpret_cast<uintptr_t>(target) + kGameObjectIsVisibleOffset, detected) ||
                        ((static_cast<uint32_t>(detected) >> static_cast<uint32_t>(playerTeam)) & 1u) == 0)
                        return false;
                }
                return TryGetGameObjectWorldPosition(target, out);
            }

            bool ReadLiveTarget(void* unit, bool pending, int& what, uint32_t& who, float (&out)[3])
            {
                int targetWhat = 0;
                if (!ReadRtsCommandTarget(unit, pending, targetWhat, who) || !ReadLiveObjectPosition(unit, who, out))
                    return false;
                what = targetWhat;
                return true;
            }

            // A live order ping already rings this object.
            bool PingRingsTarget(uint32_t who)
            {
                for (size_t i = 0; i < RM::kMaxPings; ++i)
                    if (g_Pings.slots[i].active && g_Pings.slots[i].targetHandle == who)
                        return true;
                return false;
            }

            // One ring per distinct target, in the line's colour, sized to the
            // target like the attack ping.
            void AddTargetRing(RingRequest (&requests)[RM::kSlotCount], uint32_t (&handles)[RM::kMaxTargetRingSlots],
                               size_t& count, uint32_t who, const float pos[3], int what)
            {
                for (size_t i = 0; i < count; ++i)
                    if (handles[i] == who)
                        return;
                if (count >= RM::kMaxTargetRingSlots || (g_PingsOn && PingRingsTarget(who)))
                    return;
                void* target = SafeGetObj(who);
                if (!target)
                    return;
                RingRequest& ring = requests[RM::kFirstTargetRingSlot + count];
                handles[count++] = who;
                const RtsPlacement::LineColour c = RtsPlacement::WaypointColour(what, false);
                ring.wanted = true;
                std::memcpy(ring.centre, pos, sizeof(ring.centre));
                ring.radius = RM::TargetRingRadius(ReadBoundingRadiusSeh(target));
                ring.colour.r = c.r;
                ring.colour.g = c.g;
                ring.colour.b = c.b;
                ring.colour.a = c.a;
            }

            // Per selected-unit index: 0 none, 1 straight line, 2 planned route, +2
            // when the line ends on a live target
            // (change-only log).
            int g_LineSource[RM::kMaxWaypointLineSlots] = {};

            void BuildPlacementRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                RtsPowerRing rings[RM::kMaxPowerRingSlots];
                const size_t ringCount = RtsPowerRingsThisTick(rings, RM::kMaxPowerRingSlots);
                for (size_t i = 0; i < ringCount; ++i)
                {
                    RingRequest& ring = requests[RM::kFirstPowerSlot + i];
                    ring.wanted = true;
                    std::memcpy(ring.centre, rings[i].centre, sizeof(ring.centre));
                    ring.radius = rings[i].radius;
                    ring.colour = RM::kPowerColour;
                }
                if (!RtsWaypointLinesEnabled())
                    return;
                void* units[RM::kMaxWaypointLineSlots] = {};
                const size_t unitCount = GatherSelectedOwnUnits(units);
                uint32_t targetHandles[RM::kMaxTargetRingSlots] = {};
                size_t targetCount = 0;
                for (size_t i = 0; i < unitCount; ++i)
                {
                    float pos[3] = {};
                    if (!TryGetGameObjectWorldPosition(units[i], pos))
                        continue;
                    // The pending line starts where the current one ends.
                    float from[3] = {pos[0], pos[1], pos[2]};
                    int what = 0;
                    float x = 0.0f, z = 0.0f;
                    bool haveDestination = ReadRtsCommandDestination(units[i], false, what, x, z);
                    // An order on an object ends at where the object is now,
                    // not where its path was planned to.
                    float targetPos[3] = {};
                    uint32_t who = 0;
                    const bool haveTarget = ReadLiveTarget(units[i], false, what, who, targetPos);
                    if (haveTarget)
                    {
                        x = targetPos[0];
                        z = targetPos[2];
                        haveDestination = true;
                        AddTargetRing(requests, targetHandles, targetCount, who, targetPos, what);
                    }
                    if (haveDestination)
                    {
                        RingRequest& current = requests[RM::kFirstWaypointSlot + i];
                        LineRequest(current, pos, x, z, what, false);
                        if (current.wanted)
                        {
                            unsigned routeIndex = 0;
                            int routeCount = 0;
                            if (!ReadUnitRoute(units[i], pos, current, routeIndex, routeCount))
                                current.routeCount = 0;
                            else if (haveTarget)
                            {
                                // The route's goal is stale once the target moves.
                                current.route[2 * (current.routeCount - 1)] = x;
                                current.route[2 * (current.routeCount - 1) + 1] = z;
                            }
                            const int source = (current.routeCount >= 2 ? 2 : 1) + (haveTarget ? 2 : 0);
                            if (g_LineSource[i] != source)
                            {
                                g_LineSource[i] = source;
                                const char* const target = haveTarget ? " target=live" : "";
                                if (current.routeCount >= 2)
                                    LogShimA(LogLevel::Info, kComponent,
                                             "[RTSMARKERS] unit line source=route idx=%u count=%d what=%d%s", routeIndex,
                                             routeCount, what, target);
                                else
                                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] unit line source=straight what=%d%s",
                                             what, target);
                            }
                        }
                        double ground = pos[1];
                        from[0] = x;
                        from[1] = TerrainHeightSeh(x, z, ground) ? static_cast<float>(ground) : pos[1];
                        from[2] = z;
                    }
                    if (!requests[RM::kFirstWaypointSlot + i].wanted)
                        g_LineSource[i] = 0;
                    float pendingTarget[3] = {};
                    uint32_t pendingWho = 0;
                    if (ReadLiveTarget(units[i], true, what, pendingWho, pendingTarget))
                        LineRequest(requests[RM::kFirstPendingSlot + i], from, pendingTarget[0], pendingTarget[2], what, true);
                    else if (ReadRtsCommandDestination(units[i], true, what, x, z))
                        LineRequest(requests[RM::kFirstPendingSlot + i], from, x, z, what, true);
                }
                for (size_t i = unitCount; i < RM::kMaxWaypointLineSlots; ++i)
                    g_LineSource[i] = 0;
            }

            // ---- Queued orders (RtsOrderQueue) --------------------------------
            // For each selected own unit that holds a queue: an amber line
            // from where its current order ends (else the unit) through every
            // queued point, one line slot per leg (kFirstQueueLineSlot..), and
            // a ring on each distinct queued object target. Drawn whenever
            // the option is active, whatever RtsWaypointLines says. An object
            // that is gone, or an enemy the player cannot detect, drops its
            // leg (the chain carries on from the previous point).
            void QueueLine(RingRequest& line, const float from[3], float toX, float toZ)
            {
                if (!RtsPlacement::ShouldDrawLine(from[0], from[2], toX, toZ))
                    return;
                const RtsOrderQueuePolicy::LineColour c = RtsOrderQueuePolicy::kQueueColour;
                line.wanted = true;
                line.line = true;
                std::memcpy(line.centre, from, sizeof(line.centre));
                line.end[0] = toX;
                line.end[1] = toZ;
                line.colour.r = c.r;
                line.colour.g = c.g;
                line.colour.b = c.b;
                line.colour.a = c.a;
            }

            void SetGroundHeight(float (&p)[3])
            {
                double ground = p[1];
                if (TerrainHeightSeh(p[0], p[2], ground))
                    p[1] = static_cast<float>(ground);
            }

            void BuildQueueRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                if (!RtsOrderQueueDrawActive())
                    return;
                void* units[RM::kMaxWaypointLineSlots] = {};
                const size_t unitCount = GatherSelectedOwnUnits(units);
                uint32_t ringTargets[RM::kMaxQueueRingSlots] = {};
                size_t lines = 0, rings = 0;
                for (size_t i = 0; i < unitCount && lines < RM::kMaxQueueLineSlots; ++i)
                {
                    RtsOrderQueuePolicy::Entry legs[RtsOrderQueuePolicy::kMaxEntries];
                    const int legCount = RtsOrderQueueSnapshot(SafeGetHandle(units[i]), legs, RtsOrderQueuePolicy::kMaxEntries);
                    float pos[3] = {};
                    if (legCount <= 0 || !TryGetGameObjectWorldPosition(units[i], pos))
                        continue;
                    // The chain starts where the current order ends.
                    float from[3] = {pos[0], pos[1], pos[2]};
                    int what = 0;
                    float x = 0.0f, z = 0.0f;
                    float targetPos[3] = {};
                    uint32_t who = 0;
                    if (ReadLiveTarget(units[i], false, what, who, targetPos))
                    {
                        from[0] = targetPos[0];
                        from[1] = targetPos[1];
                        from[2] = targetPos[2];
                    }
                    else if (ReadRtsCommandDestination(units[i], false, what, x, z))
                    {
                        from[0] = x;
                        from[2] = z;
                        SetGroundHeight(from);
                    }
                    for (int j = 0; j < legCount && lines < RM::kMaxQueueLineSlots; ++j)
                    {
                        float to[3] = {};
                        if (legs[j].kind == RtsOrderQueuePolicy::Kind::Object)
                        {
                            if (!ReadLiveObjectPosition(units[i], legs[j].target, to))
                                continue;
                            bool ringed = false;
                            for (size_t r = 0; r < rings && !ringed; ++r)
                                ringed = ringTargets[r] == legs[j].target;
                            if (!ringed && rings < RM::kMaxQueueRingSlots)
                            {
                                void* const target = SafeGetObj(legs[j].target);
                                RingRequest& ring = requests[RM::kFirstQueueRingSlot + rings];
                                ringTargets[rings++] = legs[j].target;
                                ring.wanted = true;
                                std::memcpy(ring.centre, to, sizeof(ring.centre));
                                ring.radius = RM::TargetRingRadius(ReadBoundingRadiusSeh(target));
                                ring.colour.r = RtsOrderQueuePolicy::kQueueColour.r;
                                ring.colour.g = RtsOrderQueuePolicy::kQueueColour.g;
                                ring.colour.b = RtsOrderQueuePolicy::kQueueColour.b;
                                ring.colour.a = RtsOrderQueuePolicy::kQueueColour.a;
                            }
                        }
                        else
                        {
                            to[0] = legs[j].where[0];
                            to[1] = legs[j].where[1];
                            to[2] = legs[j].where[2];
                            SetGroundHeight(to);
                        }
                        QueueLine(requests[RM::kFirstQueueLineSlot + lines], from, to[0], to[2]);
                        if (requests[RM::kFirstQueueLineSlot + lines].wanted)
                            ++lines;
                        from[0] = to[0];
                        from[1] = to[1];
                        from[2] = to[2];
                    }
                }
            }

            // ---- Under-attack marks ----------------------------------------
            // GameObject::enemyShot: the sim time of the last damage from an
            // enemy team (also read by satellite_visibility.cpp).
            constexpr size_t kGameObjectEnemyShotOffset = 0x1E8;
            constexpr size_t kObj76FlagsOffset = 0x14; // as rts_placement.cpp: 0x200 = dead
            constexpr uint32_t kObj76DeadFlag = 0x200;
            constexpr size_t kMaxObjects = 4096;       // as rts_commands.cpp
            constexpr ULONGLONG kAttackScanMs = 100;

            // One object-vector buffer for the attack-mark and mine-ring scans.
            // Each scan takes a fresh snapshot and uses it at once: a snapshot
            // kept across frames would hold pointers to destroyed objects.
            void* g_SharedObjects[kMaxObjects];

            uint32_t g_AttackMarks[RM::kMaxAttackRingSlots] = {};
            size_t g_AttackMarkCount = 0;
            ULONGLONG g_AttackLastScan = 0;
            volatile long g_AttackLogBudget = 64;

            float SafeNow()
            {
                if (!g_Api.getTime)
                    return std::nanf("");
                __try
                {
                    return g_Api.getTime();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return std::nanf("");
                }
            }

            // The engine's object vector (GameObject::objectList: _Myfirst at
            // +0, _Mylast at +4; lua_handle_sync.cpp SnapshotObjects).
            size_t SnapshotObjects(void** out, size_t capacity)
            {
                if (!g_Api.objectList)
                    return 0;
                size_t count = 0;
                __try
                {
                    const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_Api.objectList);
                    if (!vec)
                        return 0;
                    void* const* first = *reinterpret_cast<void* const* const*>(vec);
                    void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                    if (!first || last < first || static_cast<size_t>(last - first) > kMaxObjects)
                        return 0;
                    const size_t available = static_cast<size_t>(last - first);
                    for (size_t i = 0; i < available && count < capacity; ++i)
                        if (reinterpret_cast<uintptr_t>(first[i]) >= 0x10000)
                            out[count++] = first[i];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
                return count;
            }

            // The object's enemyShot stamp; false for a dead or unreadable one.
            bool ReadEnemyShotSeh(void* obj, float& stamp)
            {
                __try
                {
                    const uint8_t* const o = static_cast<const uint8_t*>(obj);
                    const uint8_t* const obj76 = *reinterpret_cast<const uint8_t* const*>(o + kGameObjectObjOffset);
                    if (obj76 && (*reinterpret_cast<const uint32_t*>(obj76 + kObj76FlagsOffset) & kObj76DeadFlag))
                        return false;
                    stamp = *reinterpret_cast<const float*>(o + kGameObjectEnemyShotOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void LogAttackMark(uint32_t handle, bool on, float age)
            {
                if (InterlockedDecrement(&g_AttackLogBudget) < 0)
                    return;
                if (on)
                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] attack mark handle=0x%08X on age=%.2f", handle, age);
                else
                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] attack mark handle=0x%08X off", handle);
            }

            size_t SharedSnapshot()
            {
                return SnapshotObjects(g_SharedObjects, kMaxObjects);
            }

            // Walks every object: own team, not the piloted one, hit by an
            // enemy inside the window. Keeps the 16 most recently hit.
            void ScanAttackMarks(float now, void* player)
            {
                static RM::AttackMarkCandidate hits[kMaxObjects];
                void** const objects = g_SharedObjects;
                const size_t total = SharedSnapshot();
                size_t hitCount = 0;
                for (size_t i = 0; i < total; ++i)
                {
                    float stamp = 0.0f, age = 0.0f;
                    if (objects[i] == player || !ReadEnemyShotSeh(objects[i], stamp) ||
                        !RM::AttackMarkAge(now, stamp, age) || !SameTeam(objects[i], player))
                        continue;
                    hits[hitCount].age = age;
                    hits[hitCount++].id = i;
                }
                const size_t kept = RM::KeepMostRecent(hits, hitCount, RM::kMaxAttackRingSlots);
                uint32_t next[RM::kMaxAttackRingSlots] = {};
                size_t nextCount = 0;
                for (size_t i = 0; i < kept; ++i)
                {
                    const uint32_t handle = SafeGetHandle(objects[hits[i].id]);
                    if (!handle)
                        continue;
                    bool known = false;
                    for (size_t j = 0; j < g_AttackMarkCount && !known; ++j)
                        known = g_AttackMarks[j] == handle;
                    if (!known)
                        LogAttackMark(handle, true, hits[i].age);
                    next[nextCount++] = handle;
                }
                for (size_t j = 0; j < g_AttackMarkCount; ++j)
                {
                    bool stillMarked = false;
                    for (size_t i = 0; i < nextCount && !stillMarked; ++i)
                        stillMarked = next[i] == g_AttackMarks[j];
                    if (!stillMarked)
                        LogAttackMark(g_AttackMarks[j], false, 0.0f);
                }
                std::memcpy(g_AttackMarks, next, sizeof(next));
                g_AttackMarkCount = nextCount;
            }

            void ClearAttackMarks()
            {
                g_AttackMarkCount = 0;
                g_AttackLastScan = 0;
            }

            void BuildAttackRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                const float now = SafeNow();
                void* const player = SafeGetPlayer();
                if (!std::isfinite(now) || !player)
                    return;
                const ULONGLONG tick = GetTickCount64();
                if (tick - g_AttackLastScan >= kAttackScanMs)
                {
                    g_AttackLastScan = tick;
                    ScanAttackMarks(now, player);
                }
                // Every frame: re-read each marked object's stamp so a fresh
                // hit restarts the pulse and an expired one ends it at once.
                size_t kept = 0;
                for (size_t i = 0; i < g_AttackMarkCount; ++i)
                {
                    const uint32_t handle = g_AttackMarks[i];
                    void* const obj = SafeGetObj(handle);
                    float stamp = 0.0f, age = 0.0f;
                    float pos[3] = {};
                    if (!obj || obj == player || !ReadEnemyShotSeh(obj, stamp) || !RM::AttackMarkAge(now, stamp, age) ||
                        !TryGetGameObjectWorldPosition(obj, pos))
                    {
                        LogAttackMark(handle, false, 0.0f);
                        continue;
                    }
                    g_AttackMarks[kept] = handle;
                    RingRequest& ring = requests[RM::kFirstAttackRingSlot + kept++];
                    const RM::AttackMarkFrame frame = RM::AttackMarkStyle(age);
                    ring.wanted = frame.alpha > 0.0f;
                    std::memcpy(ring.centre, pos, sizeof(ring.centre));
                    ring.radius = std::min(RM::kMaxTargetRadius + RM::kTargetRingMargin,
                                           RM::TargetRingRadius(ReadBoundingRadiusSeh(obj)) * frame.radiusScale);
                    ring.colour = RM::kAttackColour;
                    ring.colour.a = RM::kAttackColour.a * frame.alpha;
                }
                g_AttackMarkCount = kept;
            }

            // ---- Range rings (RtsRangeRings, Docs/RTS_RANGE_RINGS.md) -----------
            // Direct-fire weapon, radar and own-team mine-trigger rings for the
            // selected own units (never the piloted vehicle), plus the labels
            // for them and for the artillery rings. Local draw only.
            constexpr size_t kProximityMineClassRangeOffset = 0x168;  // team_filter_mines.cpp:177
            constexpr size_t kProximityMinePositionOffset = 0x108;    // team_filter_mines.cpp:183

            struct MineRing
            {
                float pos[3] = {};
                float radius = 0.0f;
            };
            MineRing g_MineRings[RM::kMaxMineRingSlots];
            size_t g_MineRingCount = 0;
            ULONGLONG g_MineLastScan = 0;
            int g_MineLoggedCount = -1; // change-only "mines shown" line

            // A live ProximityMine of this vtable: its position (obj +0x108)
            // and trigger radius (class +0x168). False for anything else.
            bool ReadMineSeh(void* obj, uint32_t vtable, float pos[3], float& radius)
            {
                __try
                {
                    const uint8_t* const o = static_cast<const uint8_t*>(obj);
                    if (*reinterpret_cast<const uint32_t*>(o) != vtable)
                        return false;
                    const uint8_t* const obj76 = *reinterpret_cast<const uint8_t* const*>(o + kGameObjectObjOffset);
                    if (!obj76 || (*reinterpret_cast<const uint32_t*>(obj76 + kObj76FlagsOffset) & kObj76DeadFlag))
                        return false;
                    const uint8_t* const cls = *reinterpret_cast<const uint8_t* const*>(o + kGameObjectClassOffset);
                    if (!cls)
                        return false;
                    radius = *reinterpret_cast<const float*>(cls + kProximityMineClassRangeOffset);
                    const float* const p = reinterpret_cast<const float*>(o + kProximityMinePositionOffset);
                    pos[0] = p[0];
                    pos[1] = p[1];
                    pos[2] = p[2];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return RR::SaneMineRadius(radius) && std::isfinite(pos[0]) && std::isfinite(pos[1]) &&
                       std::isfinite(pos[2]);
            }

            // Own-team proximity mines within searchRadius + 20 m of a selected
            // unit, nearest 24, from the shared 100 ms object snapshot.
            void ScanMineRings(void* player)
            {
                g_MineRingCount = 0;
                void* units[RM::kMaxWaypointLineSlots] = {};
                float unitPos[RM::kMaxWaypointLineSlots][3] = {};
                const size_t selected = GatherSelectedOwnUnits(units);
                size_t unitCount = 0;
                for (size_t i = 0; i < selected; ++i)
                    if (TryGetGameObjectWorldPosition(units[i], unitPos[unitCount]))
                        ++unitCount;
                static const uint32_t vtable = HookEngine::EngineAddress("ProximityMineVtable");
                if (unitCount && vtable)
                {
                    static MineRing candidates[kMaxObjects];
                    static RR::NearItem nearest[kMaxObjects];
                    size_t found = 0;
                    const size_t total = SharedSnapshot();
                    for (size_t i = 0; i < total; ++i)
                    {
                        MineRing mine;
                        if (!ReadMineSeh(g_SharedObjects[i], vtable, mine.pos, mine.radius) ||
                            !SameTeam(g_SharedObjects[i], player))
                            continue;
                        float best = -1.0f;
                        for (size_t u = 0; u < unitCount; ++u)
                        {
                            const float dx = mine.pos[0] - unitPos[u][0];
                            const float dz = mine.pos[2] - unitPos[u][2];
                            if (!RR::MineNearUnit(dx, dz, mine.radius))
                                continue;
                            const float d = std::sqrt(dx * dx + dz * dz);
                            if (best < 0.0f || d < best)
                                best = d;
                        }
                        if (best < 0.0f)
                            continue;
                        candidates[found] = mine;
                        nearest[found].distance = best;
                        nearest[found].id = found;
                        ++found;
                    }
                    const size_t kept = RR::KeepNearest(nearest, found, RM::kMaxMineRingSlots);
                    for (size_t i = 0; i < kept; ++i)
                        g_MineRings[g_MineRingCount++] = candidates[nearest[i].id];
                }
                if (g_MineLoggedCount != static_cast<int>(g_MineRingCount))
                {
                    g_MineLoggedCount = static_cast<int>(g_MineRingCount);
                    if (InterlockedDecrement(&g_RangeLogBudget) >= 0)
                        LogShimA(LogLevel::Info, kComponent, "[RTSRANGE] mine rings shown=%d (selected units=%d)",
                                 g_MineLoggedCount, static_cast<int>(unitCount));
                }
            }

            void SetRangeRing(RingRequest& ring, const float pos[3], float radius, const RM::Colour& colour)
            {
                ring.wanted = true;
                std::memcpy(ring.centre, pos, sizeof(ring.centre));
                ring.radius = radius;
                ring.colour = colour;
            }

            void BuildRangeRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                if (!g_MineRangeOn)
                {
                    g_MineRingCount = 0;
                    g_MineLoggedCount = -1;
                }
                if (!g_WeaponOn && !g_RadarRangeOn && !g_MineRangeOn)
                    return;
                void* const player = SafeGetPlayer();
                if (!player)
                    return;
                if (g_WeaponOn || g_RadarRangeOn)
                {
                    void* units[RM::kMaxWaypointLineSlots] = {};
                    const size_t count = GatherSelectedOwnUnits(units);
                    size_t weapons = 0, radars = 0;
                    for (size_t i = 0; i < count; ++i)
                    {
                        float pos[3] = {};
                        if (!TryGetGameObjectWorldPosition(units[i], pos))
                            continue;
                        float range = 0.0f;
                        if (g_WeaponOn && g_Api.artillery && weapons < RM::kMaxWeaponRingSlots &&
                            ReadDirectFireSeh(units[i], range) && RR::ValidRadius(range))
                            SetRangeRing(requests[RM::kFirstWeaponRingSlot + weapons++], pos, range, RM::kDirectFireColour);
                        if (g_RadarRangeOn && radars < RM::kMaxRadarRingSlots)
                        {
                            range = ReadRadarRange(units[i]);
                            if (RR::ValidRadius(range))
                                SetRangeRing(requests[RM::kFirstRadarRingSlot + radars++], pos, range, RM::kRadarColour);
                        }
                    }
                }
                if (g_MineRangeOn)
                {
                    const ULONGLONG tick = GetTickCount64();
                    if (tick - g_MineLastScan >= kAttackScanMs)
                    {
                        g_MineLastScan = tick;
                        ScanMineRings(player);
                    }
                    for (size_t i = 0; i < g_MineRingCount; ++i)
                        SetRangeRing(requests[RM::kFirstMineRingSlot + i], g_MineRings[i].pos, g_MineRings[i].radius,
                                     RM::kMineColour);
                }
            }

            // ---- Range ring labels -------------------------------------------
            struct ArcCache
            {
                bool valid = false;
                float centre[3] = {};
                float radius = 0.0f;
                float arc[RR::kLabelArcPoints][3] = {};
            };
            ArcCache g_ArcCache[RR::kMaxLabelRings];

            void FillArc(ArcCache& cache, const float centre[3], float radius)
            {
                std::memcpy(cache.centre, centre, sizeof(cache.centre));
                cache.radius = radius;
                double last = centre[1];
                for (size_t i = 0; i < RR::kLabelArcPoints; ++i)
                {
                    float dx = 0.0f, dz = 0.0f;
                    RM::RingDirection(static_cast<unsigned>(i), static_cast<unsigned>(RR::kLabelArcPoints), dx, dz);
                    const double x = static_cast<double>(centre[0]) + dx * radius;
                    const double z = static_cast<double>(centre[2]) + dz * radius;
                    double h = last;
                    if (!TerrainHeightSeh(x, z, h))
                        h = last; // off the map: keep the neighbour's height
                    last = h;
                    cache.arc[i][0] = static_cast<float>(x);
                    cache.arc[i][1] = static_cast<float>(h) + RM::kLift;
                    cache.arc[i][2] = static_cast<float>(z);
                }
                cache.valid = true;
            }

            uint32_t LabelArgb(const RM::Colour& c)
            {
                const auto byte = [](float v) { return static_cast<uint32_t>(std::min(255.0f, std::max(0.0f, v * 255.0f))); };
                return (0xF0u << 24) | (byte(c.r) << 16) | (byte(c.g) << 8) | byte(c.b);
            }

            void ClearRangeLabels()
            {
                PublishRangeLabels(nullptr, 0);
            }

            // Publishes a label for every wanted artillery, weapon, radar and
            // mine ring (the painter keeps the 24 nearest on screen).
            void PublishRangeRingLabels(const RingRequest (&requests)[RM::kSlotCount])
            {
                if (!g_RangeLabelsOn)
                {
                    ClearRangeLabels();
                    return;
                }
                struct Group
                {
                    size_t first;
                    size_t count;
                    RR::Kind kind;
                    bool optionOn;
                    size_t cacheBase;
                };
                const Group groups[] = {
                    {0, RM::kMaxArtilleryRings, RR::Kind::Artillery, g_RangeOn, 0},
                    {RM::kFirstWeaponRingSlot, RM::kMaxWeaponRingSlots, RR::Kind::Weapon, g_WeaponOn, 16},
                    {RM::kFirstRadarRingSlot, RM::kMaxRadarRingSlots, RR::Kind::Radar, g_RadarRangeOn, 32},
                    {RM::kFirstMineRingSlot, RM::kMaxMineRingSlots, RR::Kind::Mine, g_MineRangeOn, 48},
                };
                static RangeLabelRing out[RR::kMaxLabelRings];
                size_t published = 0;
                for (const Group& group : groups)
                {
                    if (!RR::LabelsShown(group.optionOn, g_RangeLabelsOn, false))
                        continue;
                    for (size_t i = 0; i < group.count; ++i)
                    {
                        const RingRequest& request = requests[group.first + i];
                        ArcCache& cache = g_ArcCache[group.cacheBase + i];
                        if (!request.wanted || !RR::ValidRadius(request.radius))
                        {
                            cache.valid = false;
                            continue;
                        }
                        // Re-sample the terrain only when the ring changes size or
                        // its unit has moved over half a metre: hovering units
                        // drift every frame, and each refill is 64 height reads.
                        const float mdx = cache.centre[0] - request.centre[0];
                        const float mdz = cache.centre[2] - request.centre[2];
                        if (!cache.valid || cache.radius != request.radius || mdx * mdx + mdz * mdz > 0.25f)
                            FillArc(cache, request.centre, request.radius);
                        RangeLabelRing& label = out[published++];
                        label.kind = group.kind;
                        label.argb = LabelArgb(request.colour);
                        std::memcpy(label.centre, request.centre, sizeof(label.centre));
                        std::memcpy(label.arc, cache.arc, sizeof(label.arc));
                    }
                }
                PublishRangeLabels(out, published);
            }

            void BuildRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                BuildPlacementRequests(requests);
                BuildQueueRequests(requests);
                if (g_AttackOn)
                    BuildAttackRequests(requests);
                if (g_RangeOn)
                {
                    ArtilleryUnit units[RM::kMaxArtilleryRings];
                    const size_t count = GatherArtillery(units);
                    for (size_t i = 0; i < count; ++i)
                    {
                        RingRequest& ring = requests[i];
                        ring.wanted = true;
                        std::memcpy(ring.centre, units[i].pos, sizeof(ring.centre));
                        ring.radius = units[i].gun.range;
                        ring.colour = RM::kRangeColour;
                    }
                    float cursor[3] = {};
                    if (count && ReadCursorPoint(cursor))
                    {
                        bool reachable = false;
                        for (size_t i = 0; i < count && !reachable; ++i)
                        {
                            const float dx = cursor[0] - units[i].pos[0];
                            const float dz = cursor[2] - units[i].pos[2];
                            reachable = RM::CanReach(units[i].gun.speed, units[i].gun.lifeSpan,
                                                     std::sqrt(dx * dx + dz * dz), cursor[1] - units[i].pos[1]);
                        }
                        RingRequest& ring = requests[RM::kCursorSlot];
                        ring.wanted = true;
                        std::memcpy(ring.centre, cursor, sizeof(ring.centre));
                        ring.radius = kCursorRadius;
                        ring.colour = reachable ? RM::kReachableColour : RM::kUnreachableColour;
                    }
                }
                if (g_PingsOn)
                {
                    for (size_t i = 0; i < RM::kMaxPings; ++i)
                    {
                        RM::PingSlot& ping = g_Pings.slots[i];
                        if (!ping.active)
                            continue;
                        if (ping.targetHandle)
                        {
                            // Follows a live target; a dead one keeps its last spot.
                            float pos[3] = {};
                            if (void* target = SafeGetObj(ping.targetHandle))
                                if (TryGetGameObjectWorldPosition(target, pos))
                                    std::memcpy(ping.pos, pos, sizeof(pos));
                        }
                        const RM::PingStyle style = RM::StyleFor(ping.kind);
                        const RM::PingFrame frame = RM::EvaluatePing(style, ping.baseRadius, ping.age);
                        if (!frame.alive)
                            continue;
                        RingRequest& ring = requests[RM::kFirstPingSlot + i];
                        ring.wanted = true;
                        std::memcpy(ring.centre, ping.pos, sizeof(ring.centre));
                        ring.radius = frame.radius;
                        ring.colour = style.colour;
                        ring.colour.a = frame.alpha;
                    }
                }
            }

            void TickEnabled(float dt)
            {
                g_Pings.Advance(dt);
                if (HudVisibility::IsHidden() || !BindApi())
                {
                    if (g_AnyVisible)
                        HideAll();
                    HideRtsPlacement();
                    ClearRangeLabels();
                    return;
                }
                // Never mutate the scene inside render-queue traversal.
                if (InsideRenderQueueHookWithDeferral())
                    return;
                const OgreApi& api = GetOgreApi();
                void* const sceneManager = GetOgreSceneManagerRuntime();
                Vec3 origin = {0, 0, 0};
                if (!api.usable || !sceneManager || !ReadRenderOrigin(origin))
                {
                    if (g_AnyVisible)
                        HideAll();
                    HideRtsPlacement();
                    ClearRangeLabels();
                    return;
                }
                if (g_PoolSceneManager != sceneManager)
                {
                    if (g_PoolSceneManager)
                        ForgetSlots(L"scene manager changed");
                    g_PoolSceneManager = sceneManager;
                }

                // The ghosts first: they gather the power rings drawn below.
                const float renderOrigin[3] = {origin.x, origin.y, origin.z};
                TickRtsPlacement(sceneManager, renderOrigin);

                RingRequest requests[RM::kSlotCount];
                BuildRequests(requests);
                BuildRangeRequests(requests);
                PublishRangeRingLabels(requests);
                bool anyVisible = false;
                for (size_t i = 0; i < RM::kSlotCount; ++i)
                {
                    if (requests[i].wanted && DrawRing(api, sceneManager, g_Slots[i], requests[i], origin))
                        anyVisible = true;
                    else
                        HideSlot(g_Slots[i]);
                }
                g_AnyVisible = anyVisible;
            }

            // Kept for the patcher (prepare) and its log.
            constexpr size_t kPrologueLength = 6;
            // push ebp; mov ebp,esp; sub esp,0Ch (no relative operands).
            constexpr uint8_t kPrologue[kPrologueLength] = {0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C};
        }

        bool IsRtsMarkersObjectCommandHook(const char* patchName)
        {
            return patchName && std::strcmp(patchName, kHookName) == 0;
        }

        // Patcher thread, before the JMP5 is written. Relocates the 6-byte
        // prologue into a trampoline that jumps back to site + 6 and returns
        // the detour. Null leaves the site stock (no object-order pings).
        void* PrepareRtsMarkersObjectCommandHook(uint32_t site)
        {
            if (g_OrigObjectBroadcast)
                return reinterpret_cast<void*>(&ObjectBroadcastDetour);
            uint8_t prologue[kPrologueLength] = {};
            if (!site || !HookEngine::ReadMemory(site, prologue, kPrologueLength) ||
                std::memcmp(prologue, kPrologue, kPrologueLength) != 0)
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[RTSMARKERS] %s: prologue mismatch at 0x%08X; no pings for object orders", kHookName, site);
                return nullptr;
            }
            // Verify the ControlPanelBroadcastCommandObj engine row while the
            // bytes are still stock. ResolveEngineAddress remembers a verified
            // row for the process, so the RTS commands parts that call this
            // function (Defend target, Build at Nav) still bind after the
            // JMP5; otherwise their guard reads the JMP and they stand down.
            uint32_t rowAddress = 0;
            if (HookEngine::ResolveEngineAddress("ControlPanelBroadcastCommandObj", rowAddress) !=
                    HookEngine::EngineAddressStatus::Bound ||
                rowAddress != site)
                LogShimA(LogLevel::Warn, kComponent,
                         "[RTSMARKERS] %s: ControlPanelBroadcastCommandObj row did not verify at 0x%08X (row 0x%08X); "
                         "RTS commands that call it will stand down",
                         kHookName, site, rowAddress);
            auto* tramp = static_cast<uint8_t*>(VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
            if (!tramp)
            {
                LogShimA(LogLevel::Warn, kComponent, "[RTSMARKERS] %s: trampoline allocation failed", kHookName);
                return nullptr;
            }
            std::memcpy(tramp, prologue, kPrologueLength);
            tramp[kPrologueLength] = 0xE9;
            const int32_t rel = static_cast<int32_t>(site + kPrologueLength) -
                                static_cast<int32_t>(reinterpret_cast<uintptr_t>(tramp) + kPrologueLength + 5);
            std::memcpy(tramp + kPrologueLength + 1, &rel, sizeof(rel));
            FlushInstructionCache(GetCurrentProcess(), tramp, kPrologueLength + 5);
            g_OrigObjectBroadcast = reinterpret_cast<FnObjectBroadcast>(tramp);
            return reinterpret_cast<void*>(&ObjectBroadcastDetour);
        }

        void NotifyRtsMarkersCommand(int what, void* target)
        {
            try
            {
                if (!g_ConfigLoaded)
                    LoadConfig();
                if (!target || (!g_PingsOn && !g_RadarPingsOn) || !BindApi())
                    return;
                // Same gate as the broadcast detour: the local ControlPanel
                // with units selected (the caller runs before the stock
                // SelectNone that follows an accepted pick).
                OnObjectCommand(reinterpret_cast<void*>(g_Api.panel), what, target);
            }
            catch (...)
            {
            }
        }

        void NoteRtsMarkersObjectCommandHookInstalled()
        {
            g_ObjectCommandHookInstalled.store(true, std::memory_order_release);
            LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] %s installed", kHookName);
        }

        bool RtsMarkersObjectCommandHookInstalled()
        {
            return g_ObjectCommandHookInstalled.load(std::memory_order_acquire);
        }

        void TickRtsMarkers(float dt)
        {
            if (!g_ConfigLoaded)
                LoadConfig();
            if (!g_AttackOn)
                ClearAttackMarks();
            if (!g_PingsOn && !g_RangeOn && !g_AttackOn && !g_WeaponOn && !g_RadarRangeOn && !g_MineRangeOn &&
                !RtsPlacementAnyEnabled() && !RtsOrderQueueDrawActive())
            {
                if (g_AnyVisible)
                    HideAll();
                HideRtsPlacement();
                ClearRangeLabels();
                g_Pings.Clear();
                return;
            }
            if (!g_PingsOn)
                g_Pings.Clear();
            TickEnabled(dt);
        }

        void ReloadRtsMarkersConfig()
        {
            // Applied on the next tick (game thread), which hides what is off.
            LoadConfig();
            ReloadRtsPlacementConfig();
        }

        void ForgetRtsMarkersSceneResources(const wchar_t* reason)
        {
            ForgetSlots(reason);
            ForgetRtsPlacementSceneResources(reason);
        }

        void DeactivateRtsMarkers(const wchar_t* reason)
        {
            if (g_AnyVisible)
            {
                HideAll();
                LogShimW(LogLevel::Info, kComponent, L"[RTSMARKERS] hid rings (%ls)", reason ? reason : L"unspecified");
            }
            ClearRangeLabels();
            g_MineRingCount = 0;
            g_MineLoggedCount = -1;
            g_RadarByOdf.clear();
            g_RangeLogBudget = 64;
            g_Pings.Clear();
            g_RadarPings.Clear();
            g_RadarPingLogBudget = 8;
            ClearAttackMarks();
            g_AttackLogBudget = 64;
            g_PoolFailed = false;
            g_PingLogBudget = 16;
            DeactivateRtsPlacement(reason);
        }

        void EnsureRtsMarkerAssets(const std::filesystem::path& cacheRoot,
                                   const std::vector<std::filesystem::path>& payloadDirectories)
        {
            // Written whatever the options say, so turning them on later needs
            // no restart; each file is rewritten only when its bytes differ.
            // An asset pack overrides a file by shipping the same name at the
            // top of a chunk payload directory; our marked copy then steps
            // aside. Unmarked files in the cache belong to the user.
            if (cacheRoot.empty())
                return;
            try
            {
                std::error_code ec;
                const auto readAll = [](const std::filesystem::path& path) {
                    std::ifstream input(path, std::ios::binary);
                    return std::string((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
                };
                struct Asset
                {
                    const char* file;
                    std::string data;
                };
                const Asset assets[] = {
                    {RM::kShaderFile, RM::ShaderSource()},
                    {RM::kMaterialFile, RM::MaterialScript()},
                    {RM::kGhostShaderFile, RM::GhostShaderSource()},
                    {RM::kGhostMaterialFile, RM::GhostMaterialScript()},
                };
                for (const Asset& asset : assets)
                {
                    const auto ours = cacheRoot / asset.file;
                    const std::string existing = readAll(ours);
                    if (!existing.empty() && !RM::IsGeneratedText(existing))
                        continue; // the user's own file
                    bool overridden = false;
                    for (const auto& directory : payloadDirectories)
                    {
                        if (std::filesystem::equivalent(directory, cacheRoot, ec) && !ec)
                            continue;
                        ec.clear();
                        if (std::filesystem::is_regular_file(directory / asset.file, ec) && !ec)
                        {
                            overridden = true;
                            break;
                        }
                        ec.clear();
                    }
                    if (overridden)
                    {
                        if (!existing.empty())
                            std::filesystem::remove(ours, ec);
                        LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] %s overridden by an asset pack", asset.file);
                        continue;
                    }
                    if (existing == asset.data)
                        continue;
                    std::filesystem::create_directories(ours.parent_path(), ec);
                    std::ofstream output(ours, std::ios::binary | std::ios::trunc);
                    output.write(asset.data.data(), static_cast<std::streamsize>(asset.data.size()));
                    output.close();
                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] wrote %s ok=%d", ours.string().c_str(),
                             output ? 1 : 0);
                }
            }
            catch (...)
            {
                // Optional: without its material a ring draws with Ogre's
                // fallback material; the feature does not depend on it.
            }
        }
    }
}
