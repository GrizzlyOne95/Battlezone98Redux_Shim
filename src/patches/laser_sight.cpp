// laser_sight.cpp
// BZR Open Shim - LaserSight: an optional laser-sight beam from the player
// vehicle's selected weapon to the first terrain or object hit within 500 m,
// modelled on BZCC. Purely cosmetic and fully shim-owned: no engine object is
// created and no engine state is written. See Docs/LASER_SIGHT.md.
//
// Driver: the world render-queue hook (bzr_hooks.cpp), which runs while a
// world is rendered, several times per frame (one call per camera/scheme
// traversal). The work is keyed on the muzzle pose, so repeated calls inside
// one frame, and frames without a simulation step, cost a few reads.
//
// Cost contract (the user's "framerate must not suffer"):
//  - Option off: one branch per call. Gate closed by a network game: one
//    byte read more. No ray, no Ogre call (the beam is hidden once, on the
//    transition).
//  - One Ogre entity and scene node, created on first use and only moved,
//    scaled and shown/hidden afterwards. No per-frame allocation.
//  - Ray: coarse terrain steps refined only in the crossing segment; objects
//    only from collision-grid cells the beam reaches, segment by segment,
//    stopping at the first hit; no VirtualQuery or any OS call per object.
//  - [Diagnostics] TraceLaserSight / OPENSHIM_TRACE_LASER_SIGHT=1 logs the
//    measured per-call and per-recompute cost (QueryPerformanceCounter) every
//    five seconds; without it no clock is read.
//
// Pose (VERIFIED, Docs/LASER_SIGHT.md): the selected weapon is
// Carrier::GetWeapon(lowest set bit of Carrier::GetSelected()) on
// GameObject::GetCarrier(GetPlayer()); its world muzzle matrix is
// Matrix_Multiply(weapon->obj->matrix, weapon->mountWorld), as
// SniperInterface::Simulate builds it.
//
// Ballistic arc (VERIFIED facts, Docs/LASER_SIGHT.md "Ballistic arc"): when
// the selected weapon fires gravity ordnance (Grenade, SprayBomb, BounceBomb,
// Popper), the beam is drawn as kArcSegments pieces along the predicted mean
// trajectory to its first ground or object hit. Same keying, gate and cost
// bounds as the straight beam; any failure falls back to the straight beam.
//
// [General] LaserSight = 0 (default) leaves everything below inert.

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "game_state.h"
#include "hook_engine.h"
#include "laser_sight_assets.h"
#include "laser_sight_policy.h"
#include "native_chunk_mesh.h"
#include "native_chunk_prune.h"
#include "shell_casing_physics.h"
#include "shim_log.h"
#include "weapon_convergence.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error LaserSight reads the GOG x86 engine layout
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace LS = LaserSight;
            namespace SC = ShellCasings;
            namespace WC = WeaponConvergence;
            using Vec3 = SC::Vec3;

            constexpr const char* kComponent = "lasersight";
            constexpr const char* kMeshResource = OPENSHIM_CHUNK_CACHE_LASERSIGHT_DIR "openshim_lasersight.mesh";
            constexpr unsigned kBeamSides = 8;
            // The arc spans 40% of the straight beam's fade, so its ground contact stays
            // bright and thick (the straight beam fades to 30% brightness, half radius).
            constexpr float kArcFadeSpan = 0.4f;
            constexpr float kBeamRadius = 0.05f;  // metres at the muzzle; half that at the far end
            // Objects move without the player's muzzle moving: refresh at
            // least this often even when the pose is unchanged.
            constexpr DWORD kRefreshMs = 50;
            constexpr size_t kMaxGridHandles = 32;   // per segment query
            constexpr size_t kMaxTestedObjects = 64; // per recompute
            constexpr LS::TerrainMarch kTerrainMarch = {};
            // Ballistic arc pieces: <prefix>NN.mesh, NN = 00..kArcSegments-1.
            constexpr const char* kArcMeshPrefix = OPENSHIM_CHUNK_CACHE_LASERSIGHT_DIR "openshim_lasersight_arc";
            constexpr LS::ArcMarch kArcMarch = {};

            // Released-layout contracts (GOG Redux 2.2.301), cited in
            // Docs/LASER_SIGHT.md. Weapon +0x10 = the hardpoint object whose
            // +0x20 is its local MAT_3D; weapon +0x28 = the mount's world
            // MAT_3D, refreshed by Weapon::Control 0x00611610 every tick.
            constexpr size_t kWeaponObject = 0x10;
            constexpr size_t kWeaponMountWorld = 0x28;
            constexpr size_t kObjectMatrix = 0x20;
            // As shell_casings.cpp: GameObject +0x0F0 render bridge, bridge
            // +0x094 Ogre entity; obj76 +0x14 flags, 0x200 = dead.
            constexpr size_t kGameObjectRenderBridgeOffset = 0x0F0;
            constexpr size_t kRenderBridgeWorldEntityOffset = 0x094;
            constexpr size_t kObj76FlagsOffset = 0x14;
            constexpr uint32_t kObj76DeadFlag = 0x200;
            // Ballistic arc (Docs/LASER_SIGHT.md, "Ballistic arc"); each is
            // guarded at bind time by a LaserArc* row in scripts/patches.json.
            // Weapon +0x08 = WeaponClass, +0x0C = OrdnanceClass; both classes
            // keep their signature at +0x0C; WeaponClass(Cannon) +0x90 =
            // shotPitch; OrdnanceClass +0x50 = lifeSpan, +0x54 = shotSpeed.
            constexpr size_t kWeaponClassOffset = 0x08;
            constexpr size_t kWeaponOrdnanceClassOffset = 0x0C;
            constexpr size_t kClassSigOffset = 0x0C;
            constexpr size_t kCannonShotPitchOffset = 0x90;
            constexpr size_t kOrdnanceLifeSpanOffset = 0x50;
            constexpr size_t kOrdnanceShotSpeedOffset = 0x54;

            // ---- Config ------------------------------------------------------
            enum class ConfigState : uint8_t
            {
                Unloaded,
                Off,
                On,
            };
            ConfigState g_State = ConfigState::Unloaded;
            bool g_Trace = false;
            volatile LONG g_Mode = static_cast<LONG>(LS::Mode::Default);

            void LoadConfig()
            {
                bool option = false;
                TryGetUserConfigBool("General", "LaserSight", option);
                bool trace = false;
                TryGetUserConfigBool("Diagnostics", "TraceLaserSight", trace);
                g_Trace = trace || EnvFlagEnabled("OPENSHIM_TRACE_LASER_SIGHT");
                g_State = option ? ConfigState::On : ConfigState::Off;
                LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] config option=%d mode=%ld trace=%d",
                         option ? 1 : 0, static_cast<long>(g_Mode), g_Trace ? 1 : 0);
            }

            // ---- Engine API --------------------------------------------------
            using FnGetPlayer = void*(__cdecl*)();
            using FnThisPointer = void*(__thiscall*)(void*);
            using FnThisValue = uint32_t(__thiscall*)(void*);
            using FnGetWeapon = void*(__thiscall*)(void*, int);

            struct EngineApi
            {
                FnGetPlayer getPlayer = nullptr;
                FnThisPointer getCarrier = nullptr;
                FnThisValue getSelected = nullptr;
                FnGetWeapon getWeapon = nullptr;
                const volatile uint8_t* isNetGame = nullptr;
                bool attempted = false;
                bool usable = false;
            };
            EngineApi g_Api;

            bool BindApi()
            {
                if (g_Api.attempted)
                    return g_Api.usable;
                g_Api.attempted = true;
                uint32_t player = 0, carrier = 0, selected = 0, netGame = 0;
                const HookEngine::EngineRow rows[] = {
                    {"HudFadeGetPlayer", &player},
                    {"HudFadeGetCarrier", &carrier},
                    {"HudFadeGetSelected", &selected},
                    {"IsNetGameFlag", &netGame},
                };
                const uint32_t weapon = HookEngine::ResolveNamedAddress("Carrier::GetWeapon");
                if (!HookEngine::BindEngineRows("Laser sight", rows) || !weapon)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "[LASERSIGHT] stands down: engine rows unresolved (Carrier::GetWeapon=0x%08X)", weapon);
                    return false;
                }
                g_Api.getPlayer = reinterpret_cast<FnGetPlayer>(static_cast<uintptr_t>(player));
                g_Api.getCarrier = reinterpret_cast<FnThisPointer>(static_cast<uintptr_t>(carrier));
                g_Api.getSelected = reinterpret_cast<FnThisValue>(static_cast<uintptr_t>(selected));
                g_Api.getWeapon = reinterpret_cast<FnGetWeapon>(static_cast<uintptr_t>(weapon));
                g_Api.isNetGame = reinterpret_cast<const volatile uint8_t*>(static_cast<uintptr_t>(netGame));
                g_Api.usable = true;
                LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] engine rows bound");
                return true;
            }

            // The arc's layout guards. Unbound, every weapon gets the
            // straight beam, as before the arc existed.
            bool BindArcRows()
            {
                static bool attempted = false;
                static bool usable = false;
                if (attempted)
                    return usable;
                attempted = true;
                uint32_t weaponClass = 0, weaponOrdnance = 0, lifeSpan = 0, shotSpeed = 0, shotPitch = 0, gravity = 0;
                uint32_t grenade = 0, sprayBomb = 0, bounceBomb = 0, popper = 0, mortar = 0, cannon = 0;
                const HookEngine::EngineRow rows[] = {
                    {"LaserArcWeaponClassField", &weaponClass},
                    {"LaserArcWeaponOrdnanceField", &weaponOrdnance},
                    {"LaserArcOrdnanceLifeSpan", &lifeSpan},
                    {"LaserArcOrdnanceShotSpeed", &shotSpeed},
                    {"LaserArcCannonShotPitch", &shotPitch},
                    {"LaserArcGrenadeGravity", &gravity},
                    {"LaserArcGrenadeSig", &grenade},
                    {"LaserArcSprayBombSig", &sprayBomb},
                    {"LaserArcBounceBombSig", &bounceBomb},
                    {"LaserArcPopperSig", &popper},
                    {"LaserArcMortarSig", &mortar},
                    {"LaserArcCannonSig", &cannon},
                };
                usable = HookEngine::BindEngineRows("Laser sight arc", rows);
                LogShimA(usable ? LogLevel::Info : LogLevel::Warn, kComponent,
                         usable ? "[LASERSIGHT] arc rows bound"
                                : "[LASERSIGHT] arc rows unbound; ballistic weapons get the straight beam");
                return usable;
            }

            // ---- Ogre access -------------------------------------------------
            struct OgreApi
            {
                const void*(__thiscall* entityBounds)(void*) = nullptr;
                void*(__thiscall* parentSceneNode)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedPosition)(void*) = nullptr;
                const OgreQuaternion*(__thiscall* derivedOrientation)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedScale)(void*) = nullptr;
                void(__thiscall* setCastShadows)(void*, bool) = nullptr;
                bool objects = false;
            };

            const OgreApi& GetOgreApi()
            {
                static OgreApi api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.entityBounds = ResolveOgreProc<decltype(api.entityBounds)>(
                    "?getBoundingBox@Entity@Ogre@@UBEABVAxisAlignedBox@2@XZ");
                api.parentSceneNode = ResolveOgreProc<decltype(api.parentSceneNode)>(
                    "?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ");
                api.derivedPosition = ResolveOgreProc<decltype(api.derivedPosition)>(
                    "?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ");
                api.derivedOrientation = ResolveOgreProc<decltype(api.derivedOrientation)>(
                    "?_getDerivedOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ");
                api.derivedScale = ResolveOgreProc<decltype(api.derivedScale)>(
                    "?_getDerivedScale@Node@Ogre@@UBEABVVector3@2@XZ");
                api.setCastShadows = ResolveOgreProc<decltype(api.setCastShadows)>(
                    "?setCastShadows@MovableObject@Ogre@@UAEX_N@Z");
                api.objects = api.entityBounds && api.parentSceneNode && api.derivedPosition &&
                              api.derivedOrientation && api.derivedScale;
                return api;
            }

            // Ogre 1.x AxisAlignedBox: mMinimum, mMaximum, then the extent enum
            // (0 null, 1 finite, 2 infinite).
            struct OgreAabbView
            {
                OgreVector3 minimum;
                OgreVector3 maximum;
                int32_t extent;
            };

            bool ReadEntityObbSeh(const OgreApi& api, void* entity, SC::Obb& out)
            {
                __try
                {
                    const auto* box = static_cast<const OgreAabbView*>(api.entityBounds(entity));
                    if (!box || box->extent != 1)
                        return false;
                    void* node = api.parentSceneNode(entity);
                    if (!node)
                        return false;
                    const OgreVector3* p = api.derivedPosition(node);
                    const OgreQuaternion* q = api.derivedOrientation(node);
                    const OgreVector3* s = api.derivedScale(node);
                    if (!p || !q || !s)
                        return false;
                    out = SC::ObbFromNode({box->minimum.x, box->minimum.y, box->minimum.z},
                                          {box->maximum.x, box->maximum.y, box->maximum.z}, {p->x, p->y, p->z},
                                          SC::QNormalize({q->w, q->x, q->y, q->z}), {s->x, s->y, s->z});
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return SC::Finite(out.center) && SC::Finite(out.half) && out.half.x < 500.0f &&
                       out.half.y < 500.0f && out.half.z < 500.0f;
            }

            void SetCastShadowsSeh(const OgreApi& api, void* entity)
            {
                if (!api.setCastShadows || !entity)
                    return;
                __try
                {
                    api.setCastShadows(entity, false);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            // A vtable inside OgreMain, without VirtualQuery (the module range
            // is cached); the guarded read covers unmapped pages.
            bool LooksLikeOgreObjectInPlace(const void* candidate)
            {
                const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
                if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                    return false;
                uintptr_t ogreBase = 0, ogreEnd = 0;
                if (!TryGetOgreModuleRange(ogreBase, ogreEnd))
                    return false;
                uintptr_t vtable = 0;
                __try
                {
                    vtable = *reinterpret_cast<const uintptr_t*>(candidate);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return vtable >= ogreBase && vtable < ogreEnd;
            }

            bool ReadObjectEntitySeh(void* gameObject, void*& entity)
            {
                entity = nullptr;
                __try
                {
                    void* bridge = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(gameObject) +
                                                                   kGameObjectRenderBridgeOffset);
                    if (bridge)
                        entity = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(bridge) +
                                                                 kRenderBridgeWorldEntityOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    entity = nullptr;
                }
                if (!entity)
                    return false;
                void* obj76 = nullptr;
                if (TryGetGameObjectObj76(gameObject, obj76) && obj76)
                {
                    uint32_t flags = kObj76DeadFlag;
                    __try
                    {
                        flags = *reinterpret_cast<const uint32_t*>(static_cast<const uint8_t*>(obj76) +
                                                                   kObj76FlagsOffset);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                    if (flags & kObj76DeadFlag)
                        return false;
                }
                return true;
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

            // ---- Terrain -----------------------------------------------------
            using FnTerrainHeightAt = double(__cdecl*)(double x, double z);
            FnTerrainHeightAt ResolveTerrainHeight()
            {
                static FnTerrainHeightAt fn = nullptr;
                static bool attempted = false;
                if (!attempted)
                {
                    attempted = true;
                    fn = reinterpret_cast<FnTerrainHeightAt>(
                        static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("Terrain::HeightAt")));
                    if (!fn)
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[LASERSIGHT] Terrain::HeightAt unresolved; the beam ignores terrain");
                }
                return fn;
            }

            bool TerrainHeightSimSeh(FnTerrainHeightAt fn, double x, double z, double& out)
            {
                __try
                {
                    out = fn(x, z);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out) && std::abs(out) < 1.0e6;
            }

            // ---- Collision grid ----------------------------------------------
            using FnGridQuery = void(__thiscall*)(void* grid, double minX, double minZ, double maxX, double maxZ,
                                                  void* results);
            using FnGridNext = uint8_t(__thiscall*)(void* results, uint32_t** outHandle);
            struct GridApi
            {
                void** gridGlobal = nullptr;
                FnGridQuery query = nullptr;
                FnGridNext next = nullptr;
                bool usable = false;
            };

            const GridApi& GetGridApi()
            {
                static GridApi api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.gridGlobal = reinterpret_cast<void**>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("CollisionGrid::Objects")));
                api.query = reinterpret_cast<FnGridQuery>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("CollisionGrid::RangeQuery")));
                api.next = reinterpret_cast<FnGridNext>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("CollisionGrid::RangeNext")));
                api.usable = api.gridGlobal && api.query && api.next;
                if (!api.usable)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[LASERSIGHT] object grid unresolved; the beam ignores objects");
                return api;
            }

            // The grid's own results record: 44 bytes on the stack in every
            // stock caller, plain data with no destructor (as ShellCasings).
            struct GridResults
            {
                uint8_t storage[64];
            };

            size_t QueryGridSeh(const GridApi& api, double minX, double minZ, double maxX, double maxZ, int* handles,
                                size_t capacity)
            {
                size_t count = 0;
                __try
                {
                    void* grid = *api.gridGlobal;
                    if (!grid)
                        return 0;
                    GridResults results = {};
                    api.query(grid, minX, minZ, maxX, maxZ, &results);
                    uint32_t* handle = nullptr;
                    for (int guard = 0; guard < 512 && api.next(&results, &handle); ++guard)
                    {
                        if (handle && count < capacity)
                            handles[count++] = static_cast<int>(*handle);
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return count;
                }
                return count;
            }

            // ---- Player and selected weapon ----------------------------------
            struct Snapshot
            {
                void* player = nullptr;
                const void* playerVtable = nullptr;
                void* weapon = nullptr;
                WC::Matrix local = {};
                WC::Matrix mount = {};
            };

            bool ReadPlayerSeh(void*& player, const void*& vtable)
            {
                player = nullptr;
                vtable = nullptr;
                __try
                {
                    player = g_Api.getPlayer();
                    if (player)
                        vtable = *reinterpret_cast<const void* const*>(player);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return player && vtable;
            }

            bool ReadWeaponPoseSeh(void* player, void*& weapon, WC::Matrix& local, WC::Matrix& mount)
            {
                weapon = nullptr;
                __try
                {
                    void* carrier = g_Api.getCarrier(player);
                    if (!carrier)
                        return false;
                    const int slot = LS::FirstSelectedSlot(g_Api.getSelected(carrier));
                    if (slot < 0)
                        return false;
                    weapon = g_Api.getWeapon(carrier, slot);
                    if (!weapon)
                        return false;
                    const uint8_t* bytes = static_cast<const uint8_t*>(weapon);
                    const void* object = *reinterpret_cast<const void* const*>(bytes + kWeaponObject);
                    if (!object)
                        return false;
                    std::memcpy(&local, static_cast<const uint8_t*>(object) + kObjectMatrix, sizeof(local));
                    std::memcpy(&mount, bytes + kWeaponMountWorld, sizeof(mount));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    weapon = nullptr;
                    return false;
                }
                return true;
            }

            // The selected weapon's ballistics, when it fires gravity
            // ordnance. False for every other weapon (straight beam).
            struct Ballistics
            {
                float shotSpeed = 0.0f;
                float lifeSpan = 0.0f;
                float shotPitch = 0.0f; // radians, 0 unless Cannon::Simulate fires it
            };

            bool ReadBallisticsSeh(void* weapon, Ballistics& out)
            {
                __try
                {
                    const uint8_t* bytes = static_cast<const uint8_t*>(weapon);
                    const uint8_t* ordnanceClass =
                        *reinterpret_cast<const uint8_t* const*>(bytes + kWeaponOrdnanceClassOffset);
                    const uint8_t* weaponClass = *reinterpret_cast<const uint8_t* const*>(bytes + kWeaponClassOffset);
                    if (!ordnanceClass || !weaponClass ||
                        !LS::IsBallisticOrdnance(*reinterpret_cast<const uint32_t*>(ordnanceClass + kClassSigOffset)))
                        return false;
                    out.shotSpeed = *reinterpret_cast<const float*>(ordnanceClass + kOrdnanceShotSpeedOffset);
                    out.lifeSpan = *reinterpret_cast<const float*>(ordnanceClass + kOrdnanceLifeSpanOffset);
                    out.shotPitch =
                        LS::AppliesShotPitch(*reinterpret_cast<const uint32_t*>(weaponClass + kClassSigOffset))
                            ? *reinterpret_cast<const float*>(weaponClass + kCannonShotPitchOffset)
                            : 0.0f;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out.shotSpeed) && out.shotSpeed > 0.0f && out.lifeSpan > 0.0f &&
                       std::isfinite(out.shotPitch) && std::fabs(out.shotPitch) < 3.2f;
            }

            // On foot the player object is a Person: no beam. RTTI is read only
            // when the player object or its vtable changes.
            struct PersonCache
            {
                const void* player = nullptr;
                const void* vtable = nullptr;
                bool person = false;
            };
            PersonCache g_PersonCache;

            bool IsPerson(void* player, const void* vtable)
            {
                if (g_PersonCache.player != player || g_PersonCache.vtable != vtable)
                {
                    char className[128] = {};
                    const char* name = TryGetRttiClassName(player, className, sizeof(className));
                    g_PersonCache = {player, vtable, !name || std::strstr(name, "Person") != nullptr};
                }
                return g_PersonCache.person;
            }

            // ---- Beam object -------------------------------------------------
            struct Beam
            {
                void* sceneManager = nullptr;
                void* node = nullptr;
                void* entity = nullptr;
                bool visible = false;
                bool failed = false; // creation failed in this scene; not retried until it changes
                // Ballistic arc: kArcSegments pieces, created on first use
                // in the same scene as the straight beam.
                void* arcNodes[LS::kArcSegments] = {};
                void* arcEntities[LS::kArcSegments] = {};
                bool arcCreated = false;
                bool arcVisible = false;
                bool arcFailed = false; // as `failed`, for the arc pieces
            };
            Beam g_Beam;

            bool BeamShown()
            {
                return g_Beam.visible || g_Beam.arcVisible;
            }

            // Last recompute's inputs; equal inputs inside kRefreshMs skip it.
            struct ComputeKey
            {
                void* weapon = nullptr;
                WC::Matrix local = {};
                WC::Matrix mount = {};
                Vec3 origin = {0, 0, 0};
                DWORD tick = 0;
                bool valid = false;
            };
            ComputeKey g_Key;

            // ---- Trace -------------------------------------------------------
            struct TraceStats
            {
                LARGE_INTEGER frequency = {};
                DWORD lastLog = 0;
                uint32_t calls = 0;
                uint32_t recomputes = 0;
                uint32_t objectsTested = 0;
                uint32_t arcSamples = 0; // last arc recompute: ground samples
                uint32_t arcSpans = 0;   // last arc recompute: grid queries
                int64_t callTicks = 0;
                int64_t callMax = 0;
                int64_t recomputeTicks = 0;
                int64_t recomputeMax = 0;
            };
            TraceStats g_Stats;

            // keepKey: Recompute hid it for this pose (muzzle against a hull);
            // keep the cache so the same pose is not traced again every call.
            void HideStraight()
            {
                if (g_Beam.visible && g_Beam.node && g_Beam.entity)
                    HideShimOwnedObject(g_Beam.node, g_Beam.entity);
                g_Beam.visible = false;
            }

            void HideArc()
            {
                if (g_Beam.arcVisible)
                    for (unsigned k = 0; k < LS::kArcSegments; ++k)
                        if (g_Beam.arcNodes[k] && g_Beam.arcEntities[k])
                            HideShimOwnedObject(g_Beam.arcNodes[k], g_Beam.arcEntities[k]);
                g_Beam.arcVisible = false;
            }

            void HideBeam(bool keepKey = false)
            {
                HideStraight();
                HideArc();
                if (!keepKey)
                    g_Key.valid = false;
            }

            void ForgetBeam(const wchar_t* reason)
            {
                const bool had = g_Beam.node || g_Beam.entity || g_Beam.arcCreated;
                g_Beam = Beam{};
                g_Key.valid = false;
                g_PersonCache = PersonCache{};
                if (had)
                    LogShimW(LogLevel::Info, kComponent, L"[LASERSIGHT] forgot beam object (%ls)",
                             reason ? reason : L"unspecified");
            }

            bool EnsureBeam(void* sceneManager)
            {
                if (g_Beam.sceneManager && g_Beam.sceneManager != sceneManager)
                    ForgetBeam(L"scene manager changed"); // its objects went with the old scene
                if (g_Beam.entity)
                    return true;
                if (g_Beam.failed)
                    return false;
                void* created = nullptr;
                void* node = nullptr;
                void* entity = nullptr;
                if (!CreateShimOwnedMeshObject(kMeshResource, created, node, entity))
                {
                    g_Beam.failed = true;
                    g_Beam.sceneManager = sceneManager;
                    LogShimA(LogLevel::Warn, kComponent,
                             "[LASERSIGHT] beam entity creation failed mesh=%s (not retried in this scene)",
                             kMeshResource);
                    return false;
                }
                g_Beam.sceneManager = created;
                g_Beam.node = node;
                g_Beam.entity = entity;
                g_Beam.visible = false;
                SetCastShadowsSeh(GetOgreApi(), entity);
                LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] beam entity created node=0x%08X entity=0x%08X",
                         static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)),
                         static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entity)));
                return true;
            }

            // Drops the arc handles without destroying anything: this runs
            // inside a render traversal, so, as for the straight beam, Ogre
            // keeps the hidden objects until the scene is torn down.
            void ForgetArcObjects()
            {
                for (unsigned k = 0; k < LS::kArcSegments; ++k)
                {
                    g_Beam.arcNodes[k] = nullptr;
                    g_Beam.arcEntities[k] = nullptr;
                }
                g_Beam.arcCreated = false;
                g_Beam.arcVisible = false;
            }

            // The arc pieces, in the straight beam's scene (EnsureBeam ran).
            bool EnsureArc()
            {
                if (g_Beam.arcCreated)
                    return true;
                if (g_Beam.arcFailed || !g_Beam.sceneManager)
                    return false;
                for (unsigned k = 0; k < LS::kArcSegments; ++k)
                {
                    char mesh[160] = {};
                    std::snprintf(mesh, sizeof(mesh), "%s%02u.mesh", kArcMeshPrefix, k);
                    void* created = nullptr;
                    if (!CreateShimOwnedMeshObject(mesh, created, g_Beam.arcNodes[k], g_Beam.arcEntities[k]) ||
                        created != g_Beam.sceneManager)
                    {
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[LASERSIGHT] arc piece creation failed mesh=%s (straight beam instead; not "
                                 "retried in this scene)",
                                 mesh);
                        ForgetArcObjects();
                        g_Beam.arcFailed = true;
                        return false;
                    }
                    SetCastShadowsSeh(GetOgreApi(), g_Beam.arcEntities[k]);
                }
                g_Beam.arcCreated = true;
                g_Beam.arcVisible = false;
                LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] arc pieces created count=%u", LS::kArcSegments);
                return true;
            }

            // One object's box for the hit tests, or false to skip it: the
            // player, dead or entity-less objects, and boxes that contain the
            // muzzle. Entity bounds are loose: a box the muzzle sits in (a
            // hull we are pressed against, a building we hover over) would
            // swallow the whole beam.
            bool ReadObjectBox(const OgreApi& ogre, int handle, void* player, Vec3 muzzle, SC::Obb& box)
            {
                void* object = GameObjectFromHandleGog(handle);
                if (!object || object == player)
                    return false;
                void* entity = nullptr;
                if (!ReadObjectEntitySeh(object, entity) || !LooksLikeOgreObjectInPlace(entity) ||
                    !ReadEntityObbSeh(ogre, entity, box))
                    return false;
                return !SC::PointInsideObb(muzzle, box);
            }

            // Nearest object hit along the beam, up to `length`. Objects come
            // only from the grid cells of the segments walked so far; the walk
            // stops once a hit lies inside the segment just searched.
            bool NearestObjectHit(Vec3 muzzle, Vec3 dir, float length, void* player, const Vec3& origin,
                                  float& outT)
            {
                const GridApi& grid = GetGridApi();
                const OgreApi& ogre = GetOgreApi();
                if (!grid.usable || !ogre.objects)
                    return false;
                int tested[kMaxTestedObjects] = {};
                size_t testedCount = 0;
                float best = length;
                bool hit = false;
                const int segments = LS::SegmentCount(length);
                for (int s = 0; s < segments; ++s)
                {
                    const float t0 = static_cast<float>(s) * LS::kObjectSegment;
                    const float t1 = std::min(length, t0 + LS::kObjectSegment);
                    const Vec3 a = SC::RenderToSimPoint(SC::Add(muzzle, SC::Scale(dir, t0)), origin);
                    const Vec3 b = SC::RenderToSimPoint(SC::Add(muzzle, SC::Scale(dir, t1)), origin);
                    int handles[kMaxGridHandles] = {};
                    const size_t found = QueryGridSeh(grid, std::min(a.x, b.x), std::min(a.z, b.z),
                                                      std::max(a.x, b.x), std::max(a.z, b.z), handles,
                                                      kMaxGridHandles);
                    for (size_t i = 0; i < found; ++i)
                    {
                        const int handle = handles[i];
                        if (std::find(tested, tested + testedCount, handle) != tested + testedCount)
                            continue;
                        if (testedCount == kMaxTestedObjects)
                            break;
                        tested[testedCount++] = handle;
                        SC::Obb box;
                        if (!ReadObjectBox(ogre, handle, player, muzzle, box))
                            continue;
                        float t = 0.0f;
                        if (LS::RayObb(muzzle, dir, box, best, t) && t < best)
                        {
                            best = t;
                            hit = true;
                        }
                    }
                    if (g_Trace)
                        g_Stats.objectsTested = static_cast<uint32_t>(testedCount);
                    if ((hit && best <= t1) || testedCount == kMaxTestedObjects)
                        break;
                }
                if (hit)
                    outT = best;
                return hit;
            }

            // Objects met by the arc. Each object's box is read once per
            // recompute (at most kMaxTestedObjects, as the straight beam) and
            // kept, because consecutive spans query overlapping grid cells.
            struct ArcObjects
            {
                int handles[kMaxTestedObjects] = {};
                SC::Obb boxes[kMaxTestedObjects];
                bool usable[kMaxTestedObjects] = {};
                size_t count = 0;
            };

            bool ArcSpanObjectHit(const LS::ArcSample* points, int count, void* player, Vec3 muzzle,
                                  const Vec3& origin, ArcObjects& cache, float& outT)
            {
                const GridApi& grid = GetGridApi();
                const OgreApi& ogre = GetOgreApi();
                if (!grid.usable || !ogre.objects || count < 2)
                    return false;
                Vec3 lo = SC::RenderToSimPoint(points[0].p, origin), hi = lo;
                for (int i = 1; i < count; ++i)
                {
                    const Vec3 p = SC::RenderToSimPoint(points[i].p, origin);
                    lo = {std::min(lo.x, p.x), 0.0f, std::min(lo.z, p.z)};
                    hi = {std::max(hi.x, p.x), 0.0f, std::max(hi.z, p.z)};
                }
                int handles[kMaxGridHandles] = {};
                const size_t found = QueryGridSeh(grid, lo.x, lo.z, hi.x, hi.z, handles, kMaxGridHandles);
                bool hit = false;
                float best = 0.0f;
                for (size_t i = 0; i < found; ++i)
                {
                    size_t slot = std::find(cache.handles, cache.handles + cache.count, handles[i]) - cache.handles;
                    if (slot == cache.count)
                    {
                        if (cache.count == kMaxTestedObjects)
                            continue;
                        cache.handles[slot] = handles[i];
                        cache.usable[slot] = ReadObjectBox(ogre, handles[i], player, muzzle, cache.boxes[slot]);
                        ++cache.count;
                    }
                    float t = 0.0f;
                    if (cache.usable[slot] && LS::PolylineObbHit(points, count, cache.boxes[slot], t) &&
                        (!hit || t < best))
                    {
                        best = t;
                        hit = true;
                    }
                }
                if (g_Trace)
                    g_Stats.objectsTested = static_cast<uint32_t>(cache.count);
                if (hit)
                    outT = best;
                return hit;
            }

            // The ballistic arc for gravity ordnance. False when the arc
            // cannot be drawn (pieces unavailable or a transform failed): the
            // caller then draws the straight beam.
            bool RecomputeArc(const Snapshot& snap, const Vec3& origin, Vec3 muzzle, Vec3 front, Vec3 up,
                              const Ballistics& ballistics)
            {
                if (!EnsureArc())
                    return false;
                LS::Arc arc;
                arc.origin = muzzle;
                arc.velocity = SC::Scale(LS::PitchedFireDirection(front, up, ballistics.shotPitch), ballistics.shotSpeed);
                arc.lifeSpan = ballistics.lifeSpan;

                const FnTerrainHeightAt terrain = ResolveTerrainHeight();
                const auto heightAt = [&](float x, float z, float& out) {
                    if (!terrain)
                    {
                        out = -1.0e9f; // no terrain row: the arc ignores the ground, as the straight beam does
                        return true;
                    }
                    const Vec3 sim = SC::RenderToSimPoint({x, 0.0f, z}, origin);
                    double height = 0.0;
                    if (!TerrainHeightSimSeh(terrain, sim.x, sim.z, height))
                        return false;
                    out = static_cast<float>(height) - origin.y;
                    return true;
                };
                ArcObjects objects;
                const auto spanHit = [&](const LS::ArcSample* points, int count, float& outT) {
                    return ArcSpanObjectHit(points, count, snap.player, muzzle, origin, objects, outT);
                };
                const LS::ArcResult result = LS::MarchArc(arc, kArcMarch, heightAt, spanHit);
                if (g_Trace)
                {
                    g_Stats.arcSamples = static_cast<uint32_t>(result.samples);
                    g_Stats.arcSpans = static_cast<uint32_t>(result.spans);
                }
                // Approximate path length (launch speed x flight time), not the chord: a steep lob
                // that lands next to the muzzle still draws.
                if (result.endT * ballistics.shotSpeed < LS::kMinBeamLength)
                {
                    HideBeam(true);
                    return true;
                }
                const Vec3 side = LS::ArcSideVector(arc, up);
                for (unsigned k = 0; k < LS::kArcSegments; ++k)
                {
                    Vec3 a, b;
                    LS::ArcSegment(arc, result.endT, k, LS::kArcSegments, a, b);
                    const Vec3 chord = SC::Sub(b, a);
                    const float length = SC::Length(chord);
                    const Vec3 dir = SC::Normalize(chord, front);
                    const LS::BeamTransform transform = LS::MakeBeamTransform(a, dir, side, length, kBeamRadius);
                    if (!SetShimOwnedObjectTransform(g_Beam.arcNodes[k], g_Beam.arcEntities[k], transform.position,
                                                     transform.orientation, transform.scale))
                    {
                        LogShimA(LogLevel::Warn, kComponent,
                                 "[LASERSIGHT] arc transform failed; straight beam from now on in this scene");
                        g_Beam.arcVisible = true; // some pieces may be shown: hide them all
                        HideArc();
                        ForgetArcObjects();
                        g_Beam.arcFailed = true;
                        return false;
                    }
                }
                HideStraight();
                g_Beam.arcVisible = true;
                return true;
            }

            void Recompute(const Snapshot& snap, const Vec3& origin)
            {
                const WC::Matrix pose = WC::Multiply(snap.local, snap.mount);
                if (!WC::IsFinite(pose))
                {
                    HideBeam(true);
                    return;
                }
                const Vec3 muzzle = SC::SimToRenderPoint(
                    {static_cast<float>(pose.positionX), static_cast<float>(pose.positionY),
                     static_cast<float>(pose.positionZ)},
                    origin);
                const Vec3 dir = SC::Normalize(SC::SimToRenderDir({pose.frontX, pose.frontY, pose.frontZ}),
                                               {0, 0, 0});
                const Vec3 up = SC::SimToRenderDir({pose.upX, pose.upY, pose.upZ});
                if (!SC::Finite(muzzle) || SC::Length(dir) < 0.5f)
                {
                    HideBeam(true);
                    return;
                }

                // Gravity ordnance: the predicted arc instead of the line.
                Ballistics ballistics;
                if (BindArcRows() && ReadBallisticsSeh(snap.weapon, ballistics) &&
                    RecomputeArc(snap, origin, muzzle, dir, SC::Normalize(up, {0, 1, 0}), ballistics))
                    return;

                float length = LS::kMaxBeamLength;
                if (const FnTerrainHeightAt terrain = ResolveTerrainHeight())
                {
                    const auto heightAt = [&](float x, float z, float& out) {
                        const Vec3 sim = SC::RenderToSimPoint({x, 0.0f, z}, origin);
                        double height = 0.0;
                        if (!TerrainHeightSimSeh(terrain, sim.x, sim.z, height))
                            return false;
                        out = static_cast<float>(height) - origin.y;
                        return true;
                    };
                    float t = 0.0f;
                    if (LS::MarchTerrain(muzzle, dir, length, kTerrainMarch, heightAt, t))
                        length = t;
                }
                float objectT = 0.0f;
                if (length > LS::kMinBeamLength &&
                    NearestObjectHit(muzzle, dir, length, snap.player, origin, objectT))
                    length = std::min(length, objectT);

                if (length < LS::kMinBeamLength)
                {
                    HideBeam(true);
                    return;
                }
                const LS::BeamTransform transform = LS::MakeBeamTransform(muzzle, dir, up, length, kBeamRadius);
                if (!SetShimOwnedObjectTransform(g_Beam.node, g_Beam.entity, transform.position,
                                                 transform.orientation, transform.scale))
                {
                    LogShimA(LogLevel::Warn, kComponent, "[LASERSIGHT] beam transform failed; dropping the object");
                    HideBeam(); // ForgetBeam drops the handles; do not leave it drawn
                    ForgetBeam(L"transform failed");
                    g_Beam.failed = true;
                    return;
                }
                HideArc();
                g_Beam.visible = true;
            }

            void TickEnabled()
            {
                if (!BindApi())
                    return;
                if (!LS::Enabled(true, *g_Api.isNetGame != 0, static_cast<int>(g_Mode)))
                {
                    if (BeamShown())
                        HideBeam();
                    return;
                }
                if (IsPauseMenuOpen())
                    return; // keep the last beam; nothing moves
                Snapshot snap;
                if (!ReadPlayerSeh(snap.player, snap.playerVtable) || IsPerson(snap.player, snap.playerVtable) ||
                    !ReadWeaponPoseSeh(snap.player, snap.weapon, snap.local, snap.mount))
                {
                    if (BeamShown())
                        HideBeam();
                    return;
                }
                void* const sceneManager = GetOgreSceneManagerRuntime();
                Vec3 origin = {0, 0, 0};
                if (!sceneManager || !ReadRenderOrigin(origin) || !EnsureBeam(sceneManager))
                    return;

                const DWORD now = GetTickCount();
                if (g_Key.valid && g_Key.weapon == snap.weapon &&
                    std::memcmp(&g_Key.local, &snap.local, sizeof(snap.local)) == 0 &&
                    std::memcmp(&g_Key.mount, &snap.mount, sizeof(snap.mount)) == 0 &&
                    g_Key.origin.x == origin.x && g_Key.origin.y == origin.y && g_Key.origin.z == origin.z &&
                    now - g_Key.tick < kRefreshMs)
                    return;
                g_Key.weapon = snap.weapon;
                g_Key.local = snap.local;
                g_Key.mount = snap.mount;
                g_Key.origin = origin;
                g_Key.tick = now;
                g_Key.valid = true;

                LARGE_INTEGER start = {};
                if (g_Trace)
                    QueryPerformanceCounter(&start);
                Recompute(snap, origin);
                if (g_Trace)
                {
                    LARGE_INTEGER end = {};
                    QueryPerformanceCounter(&end);
                    const int64_t ticks = end.QuadPart - start.QuadPart;
                    ++g_Stats.recomputes;
                    g_Stats.recomputeTicks += ticks;
                    g_Stats.recomputeMax = std::max(g_Stats.recomputeMax, ticks);
                }
            }

            void MaybeLogStats()
            {
                const DWORD now = GetTickCount();
                if (now - g_Stats.lastLog < 5000)
                    return;
                if (g_Stats.calls && g_Stats.frequency.QuadPart > 0)
                {
                    const double us = 1.0e6 / static_cast<double>(g_Stats.frequency.QuadPart);
                    LogShimA(LogLevel::Info, kComponent,
                             "[LASERSIGHT] calls=%u avg=%.2fus max=%.2fus recomputes=%u avg=%.2fus max=%.2fus "
                             "lastObjectsTested=%u visible=%d arc=%d lastArcSamples=%u lastArcSpans=%u",
                             g_Stats.calls, static_cast<double>(g_Stats.callTicks) * us / g_Stats.calls,
                             static_cast<double>(g_Stats.callMax) * us, g_Stats.recomputes,
                             g_Stats.recomputes ? static_cast<double>(g_Stats.recomputeTicks) * us / g_Stats.recomputes
                                                : 0.0,
                             static_cast<double>(g_Stats.recomputeMax) * us, g_Stats.objectsTested,
                             g_Beam.visible ? 1 : 0, g_Beam.arcVisible ? 1 : 0, g_Stats.arcSamples,
                             g_Stats.arcSpans);
                }
                const LARGE_INTEGER frequency = g_Stats.frequency;
                g_Stats = TraceStats{};
                g_Stats.frequency = frequency;
                g_Stats.lastLog = now;
            }
        }

        void TickLaserSight()
        {
            if (g_State != ConfigState::On)
            {
                if (g_State == ConfigState::Unloaded)
                    LoadConfig();
                else if (BeamShown())
                    HideBeam();
                return;
            }
            if (!g_Trace)
            {
                TickEnabled();
                return;
            }
            if (!g_Stats.frequency.QuadPart)
                QueryPerformanceFrequency(&g_Stats.frequency);
            LARGE_INTEGER start = {}, end = {};
            QueryPerformanceCounter(&start);
            TickEnabled();
            QueryPerformanceCounter(&end);
            const int64_t ticks = end.QuadPart - start.QuadPart;
            ++g_Stats.calls;
            g_Stats.callTicks += ticks;
            g_Stats.callMax = std::max(g_Stats.callMax, ticks);
            MaybeLogStats();
        }

        void ReloadLaserSightConfig()
        {
            // Applied on the next tick: hiding here could run off the render
            // thread. TickLaserSight hides a visible beam when the option is off.
            LoadConfig();
        }

        void ForgetLaserSightSceneResources(const wchar_t* reason)
        {
            ForgetBeam(reason);
        }

        void DestroyLaserSightSceneObjects(void* sceneManager, const wchar_t* reason)
        {
            // destroyAllEntities would free the beam's entity under us.
            if (!g_Beam.sceneManager || g_Beam.sceneManager != sceneManager)
                return;
            if (g_Beam.node || g_Beam.entity)
                DestroyShimOwnedMeshObject(g_Beam.sceneManager, g_Beam.node, g_Beam.entity);
            for (unsigned k = 0; k < LS::kArcSegments; ++k)
                if (g_Beam.arcNodes[k] || g_Beam.arcEntities[k])
                    DestroyShimOwnedMeshObject(g_Beam.sceneManager, g_Beam.arcNodes[k], g_Beam.arcEntities[k]);
            ForgetBeam(reason);
        }

        void DeactivateLaserSight(const wchar_t* reason)
        {
            if (BeamShown())
            {
                HideBeam();
                LogShimW(LogLevel::Info, kComponent, L"[LASERSIGHT] hid beam (%ls)", reason ? reason : L"unspecified");
            }
            g_Key.valid = false;
            g_Beam.failed = false;
            g_Beam.arcFailed = false;
            // The network allow mode belongs to the mission that set it; a stock
            // network game joined later must not inherit it.
            const LONG previous = InterlockedExchange(&g_Mode, static_cast<LONG>(LS::Mode::Default));
            if (previous != static_cast<LONG>(LS::Mode::Default))
                LogShimW(LogLevel::Info, kComponent, L"[LASERSIGHT] external mode %ld -> 0 (%ls)",
                         static_cast<long>(previous), reason ? reason : L"unspecified");
        }

        int GetLaserSightMode()
        {
            return static_cast<int>(InterlockedCompareExchange(&g_Mode, 0, 0));
        }

        int SetLaserSightMode(int mode)
        {
            if (LS::IsValidMode(mode))
            {
                const LONG previous = InterlockedExchange(&g_Mode, static_cast<LONG>(mode));
                if (previous != mode)
                    LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] external mode %ld -> %d",
                             static_cast<long>(previous), mode);
            }
            return GetLaserSightMode();
        }

        void EnsureLaserSightAssets(const std::filesystem::path& cacheRoot,
                                    const std::vector<std::filesystem::path>& payloadDirectories)
        {
            // Written whatever the option says, so turning it on later needs no
            // restart; each file is rewritten only when its bytes differ.
            if (cacheRoot.empty())
                return;
            try
            {
                std::error_code ec;
                const auto readAll = [](const std::filesystem::path& path) {
                    std::ifstream input(path, std::ios::binary);
                    return std::vector<uint8_t>((std::istreambuf_iterator<char>(input)),
                                                std::istreambuf_iterator<char>());
                };
                const auto writeIfChanged = [&](const std::filesystem::path& path, const std::vector<uint8_t>& data) {
                    if (data.empty() || readAll(path) == data)
                        return true;
                    std::filesystem::create_directories(path.parent_path(), ec);
                    std::ofstream output(path, std::ios::binary | std::ios::trunc);
                    output.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
                    output.close();
                    LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] wrote %s ok=%d", path.string().c_str(),
                             output ? 1 : 0);
                    return static_cast<bool>(output);
                };

                const NativeChunks::Piece mesh = NativeChunks::LaserBeamMesh(kBeamSides);
                writeIfChanged(cacheRoot / std::filesystem::path(kMeshResource), mesh.mesh);
                for (unsigned k = 0; k < LS::kArcSegments; ++k)
                {
                    char name[160] = {};
                    std::snprintf(name, sizeof(name), "%s%02u.mesh", kArcMeshPrefix, k);
                    writeIfChanged(cacheRoot / std::filesystem::path(name),
                                   NativeChunks::LaserBeamSectionMesh(kBeamSides, k, LS::kArcSegments, kArcFadeSpan).mesh);
                }

                // Text and texture assets: an asset pack overrides any of them
                // by shipping the same file at the top of a chunk payload
                // directory; our marked copy then steps aside. Unmarked files
                // in the cache belong to the user and are never touched.
                const auto toBytes = [](const std::string& text) {
                    return std::vector<uint8_t>(text.begin(), text.end());
                };
                struct Asset
                {
                    const char* file;
                    std::vector<uint8_t> data;
                    bool texture;
                };
                const Asset assets[] = {
                    {LS::kTextureFile, LS::BeamTga(), true},
                    {LS::kShaderFile, toBytes(LS::ShaderSource()), false},
                    {LS::kMaterialFile, toBytes(LS::MaterialScript()), false},
                };
                for (const Asset& asset : assets)
                {
                    const auto ours = cacheRoot / asset.file;
                    const std::vector<uint8_t> existing = readAll(ours);
                    const bool marked =
                        asset.texture ? LS::IsGeneratedTga(existing)
                                      : LS::IsGeneratedText(std::string(existing.begin(), existing.end()));
                    if (!existing.empty() && !marked)
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
                        LogShimA(LogLevel::Info, kComponent, "[LASERSIGHT] %s overridden by an asset pack",
                                 asset.file);
                        continue;
                    }
                    writeIfChanged(ours, asset.data);
                }
            }
            catch (...)
            {
                // Optional: without its assets the beam entity fails to create
                // and the feature stands down for the scene.
            }
        }
    }
}

// ---- External ownership (EXU, mods) --------------------------------------------
// Mode 0 (default): the beam follows [General] LaserSight and is forced off in a
// network game. Mode 1: also allowed in a network game. The user's option off
// always wins. Unknown modes are rejected; both functions return the mode in
// effect. See Docs/LASER_SIGHT.md.
extern "C" __declspec(dllexport) int __cdecl OpenShimSetLaserSightMode(int mode)
{
    try
    {
        return BZROpenShim::Hooks::SetLaserSightMode(mode);
    }
    catch (...)
    {
        return BZROpenShim::Hooks::GetLaserSightMode();
    }
}

extern "C" __declspec(dllexport) int __cdecl OpenShimGetLaserSightMode()
{
    return BZROpenShim::Hooks::GetLaserSightMode();
}

#if defined(_M_IX86)
#pragma comment(linker, "/EXPORT:OpenShimSetLaserSightMode=_OpenShimSetLaserSightMode")
#pragma comment(linker, "/EXPORT:OpenShimGetLaserSightMode=_OpenShimGetLaserSightMode")
#endif
