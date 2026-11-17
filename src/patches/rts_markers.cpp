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
// kFirstPendingSlot..).
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "game_state.h"
#include "hook_engine.h"
#include "hud_visibility.h"
#include "rts_markers.h"
#include "rts_markers_assets.h"
#include "rts_markers_policy.h"
#include "rts_placement.h"
#include "rts_placement_policy.h"
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

            void OnGroundCommand(void* panel, int what, const float* where);

            void LoadConfig()
            {
                bool value = true;
                g_PingsOn = TryGetUserConfigBool("Gameplay", "RtsCommandPings", value) ? value : true;
                value = true;
                g_RangeOn = TryGetUserConfigBool("Gameplay", "RtsArtilleryRange", value) ? value : true;
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

                g_Api.usable = true;
                LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] engine rows bound (cursor=%d artillery=%d)",
                         g_Api.cursor ? 1 : 0, g_Api.artillery ? 1 : 0);
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
            volatile long g_PingLogBudget = 16;

            // The order came from the local ControlPanel with units selected.
            bool IsLocalPanelOrder(void* panel)
            {
                if (!g_ConfigLoaded)
                    LoadConfig();
                if (!g_PingsOn || !BindApi() || reinterpret_cast<uintptr_t>(panel) != g_Api.panel)
                    return false;
                int count = 0;
                return ReadInt(g_Api.panel + kSelectCountOffset, count) && count > 0;
            }

            void QueuePing(RM::PingKind kind, const float pos[3], uint32_t targetHandle, float baseRadius, int what)
            {
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

            // Per selected-unit index: 0 none, 1 straight line, 2 planned route
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
                for (size_t i = 0; i < unitCount; ++i)
                {
                    float pos[3] = {};
                    if (!TryGetGameObjectWorldPosition(units[i], pos))
                        continue;
                    // The pending line starts where the current one ends.
                    float from[3] = {pos[0], pos[1], pos[2]};
                    int what = 0;
                    float x = 0.0f, z = 0.0f;
                    if (ReadRtsCommandDestination(units[i], false, what, x, z))
                    {
                        RingRequest& current = requests[RM::kFirstWaypointSlot + i];
                        LineRequest(current, pos, x, z, what, false);
                        if (current.wanted)
                        {
                            unsigned routeIndex = 0;
                            int routeCount = 0;
                            if (!ReadUnitRoute(units[i], pos, current, routeIndex, routeCount))
                                current.routeCount = 0;
                            const int source = current.routeCount >= 2 ? 2 : 1;
                            if (g_LineSource[i] != source)
                            {
                                g_LineSource[i] = source;
                                if (source == 2)
                                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] unit line source=route idx=%u count=%d",
                                             routeIndex, routeCount);
                                else
                                    LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] unit line source=straight");
                            }
                        }
                        double ground = pos[1];
                        from[0] = x;
                        from[1] = TerrainHeightSeh(x, z, ground) ? static_cast<float>(ground) : pos[1];
                        from[2] = z;
                    }
                    if (!requests[RM::kFirstWaypointSlot + i].wanted)
                        g_LineSource[i] = 0;
                    if (ReadRtsCommandDestination(units[i], true, what, x, z))
                        LineRequest(requests[RM::kFirstPendingSlot + i], from, x, z, what, true);
                }
                for (size_t i = unitCount; i < RM::kMaxWaypointLineSlots; ++i)
                    g_LineSource[i] = 0;
            }

            void BuildRequests(RingRequest (&requests)[RM::kSlotCount])
            {
                BuildPlacementRequests(requests);
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
                if (!target || !g_PingsOn || !BindApi())
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
            LogShimA(LogLevel::Info, kComponent, "[RTSMARKERS] %s installed", kHookName);
        }

        void TickRtsMarkers(float dt)
        {
            if (!g_ConfigLoaded)
                LoadConfig();
            if (!g_PingsOn && !g_RangeOn && !RtsPlacementAnyEnabled())
            {
                if (g_AnyVisible)
                    HideAll();
                HideRtsPlacement();
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
            g_Pings.Clear();
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
