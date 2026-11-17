// local_damage.cpp
// BZR Open Shim - localized damage scorch (Docs/LOCAL_DAMAGE.md).
//
// Sim side: the craft DamageAlloc adapter (hud_feedback.cpp DamageHook<1>)
// hands every call here. Only the two callers whose third argument and
// DAMAGE fields locate the hit are kept (Ordnance::Hit and explosion
// splash, scripts/patches.json LocalDamageBulletHitCall/SplashCall); the
// hit point, direction and health ratio lost are copied into a fixed ring.
//
// Render side: an Ogre frame listener drains the ring at frameStarted, turns
// each hit into a point in the craft's root Entity space (the space the
// Enhanced shader reconstructs with surfaceViewToLocal), keeps up to eight
// marks per unit with cooling ember heat, and writes them as Renderable
// custom parameters 1400..1410 on every SubEntity. Only marked units and the
// objects of the frame's hits are resolved. A Renderable that never set the
// parameters inherits the pass constants of the last draw, whose camera key
// (1410) fails the shader's test, so nothing else is zeroed.
// Render only: no gameplay, sim or network state is written.
#include "local_damage.h"
#include "local_damage_policy.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "ogre_entity_liveness.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
    namespace
    {
        using Hooks::ResolveOgreProc;
        namespace Policy = LocalDamage;

        constexpr const char* kComponent = "local-damage";
        constexpr const char* kSection = "LocalDamage";

        // Return address = the call instruction row + 8 (mov, mov, call reg).
        constexpr uint32_t kCallReturnOffset = 8;
        constexpr size_t kQueueCapacity = 128;
        // A frame gap longer than this (load, pause, alt-tab) cools by this much.
        constexpr float kMaxFrameSeconds = 0.25f;
        constexpr uint32_t kProveIntervalFrames = 15;
        constexpr uint32_t kAwaitTeardownFrameLimit = 300;

        using GetHandle = int(__thiscall*)(void*);
        using FnSingleton = void* (__cdecl*)();
        using FnAddListener = void(__thiscall*)(void*, void*);
        using FnCount = unsigned(__thiscall*)(void*);
        using FnSubAt = void* (__thiscall*)(void*, unsigned);
        using FnSetCustom = void(__thiscall*)(void*, size_t, const float*);
        using FnPointer = void* (__thiscall*)(void*);
        using FnVector = const float* (__thiscall*)(void*);
        using FnRadius = float(__thiscall*)(void*);

        struct OgreApi
        {
            FnSingleton rootSingleton = nullptr;
            FnAddListener addFrameListener = nullptr;
            FnCount subEntityCount = nullptr;
            FnSubAt subEntityAt = nullptr;
            FnSetCustom setCustomParameter = nullptr;
            FnPointer parentSceneNode = nullptr;
            FnVector derivedPosition = nullptr;
            FnVector derivedOrientation = nullptr;  // w, x, y, z
            FnVector derivedScale = nullptr;
            FnRadius boundingRadius = nullptr;
        };
        OgreApi g_ogre;
        bool g_apiResolved = false;
        bool g_apiAvailable = false;

        // ---- Settings (frame thread) ---------------------------------------
        bool g_configRead = false;
        std::atomic<bool> g_enabled{false};
        int g_maxMarks = Policy::kDefaultMaxMarks;
        float g_emberSeconds = Policy::kDefaultEmberSeconds;
        uint32_t g_bulletReturn = 0;
        uint32_t g_splashReturn = 0;
        bool g_rowsTried = false;

        // ---- Capture ring (sim -> render) ----------------------------------
        struct HitEvent
        {
            void* object;
            int handle;
            double point[3];
            float direction[3];
            float radius;
            float after;
        };
        SRWLOCK g_queueLock = SRWLOCK_INIT;
        HitEvent g_queue[kQueueCapacity];
        size_t g_queueCount = 0;
        uint32_t g_queueDropped = 0;

        // ---- Render state (render thread) ----------------------------------
        std::atomic<bool> g_failed{false};
        std::atomic<bool> g_active{false};
        // Set by the options menu; consumed by the render-queue tick.
        std::atomic<bool> g_reloadRequested{false};
        // The Root the listener went into. A different Root singleton (a
        // recreated one) gets the listener again.
        void* g_listenerRoot = nullptr;
        bool g_missionEvaluated = false;
        bool g_teardownSeam = false;
        bool g_awaitTeardown = false;
        uint32_t g_awaitStartedFrames = 0;
        uint32_t g_frame = 0;
        LARGE_INTEGER g_lastCounter{};
        // Only the units that carry marks and the objects of this frame's
        // hits are resolved; nothing walks the arena.
        OgreEntityLiveness::RootEntityCache g_rootProbes;

        struct Unit
        {
            bool used = false;
            void* object = nullptr;
            int handle = 0;
            void* entity = nullptr;
            // g_frame the entity was last resolved (and checked) in; keys
            // are written only for an entity resolved this frame.
            uint32_t entityFrame = 0;
            unsigned subCount = 0;
            void* firstSub = nullptr;
            float lastHealth = 1.0f;
            float localPerMetre = 1.0f;
            bool dirty = false;
            Policy::UnitMarks marks;
        };
        Unit g_units[Policy::kMaxUnits];
        int g_unitCount = 0;
        std::unordered_map<void*, int> g_unitByObject;

        struct Stats
        {
            uint32_t hits = 0;
            uint32_t merged = 0;
            uint32_t dropped = 0;
            uint32_t zeroed = 0;
        };
        Stats g_stats;

        const char* g_stage = "idle";
        char g_faultDetail[160] = {};

        // ---- Config ----------------------------------------------------------
        bool ReadInt(const char* key, int& out)
        {
            std::string text;
            if (!TryGetUserConfigString(kSection, key, text) || text.empty())
                return false;
            char* end = nullptr;
            const long value = std::strtol(text.c_str(), &end, 10);
            if (end == text.c_str())
                return false;
            out = static_cast<int>(value);
            return true;
        }

        bool ReadFloat(const char* key, float& out)
        {
            std::string text;
            if (!TryGetUserConfigString(kSection, key, text) || text.empty())
                return false;
            char* end = nullptr;
            const float value = std::strtof(text.c_str(), &end);
            if (end == text.c_str())
                return false;
            out = value;
            return true;
        }

        void ReloadConfig()
        {
            g_configRead = true;
            bool enabled = false;
            if (!TryGetUserConfigBool(kSection, "HullScorch", enabled))
                TryGetUserConfigBool(kSection, "Enabled", enabled);
            int maxMarks = Policy::kDefaultMaxMarks;
            ReadInt("MaxMarksPerUnit", maxMarks);
            float ember = Policy::kDefaultEmberSeconds;
            ReadFloat("EmberSeconds", ember);
            g_maxMarks = Policy::ClampMaxMarks(maxMarks);
            g_emberSeconds = Policy::ClampEmberSeconds(ember);
            if (enabled && !g_rowsTried)
            {
                g_rowsTried = true;
                uint32_t bullet = 0;
                uint32_t splash = 0;
                const HookEngine::EngineRow rows[] = {
                    {"LocalDamageBulletHitCall", &bullet},
                    {"LocalDamageSplashCall", &splash},
                };
                if (HookEngine::BindEngineRows("Localized damage scorch", rows))
                {
                    g_bulletReturn = bullet + kCallReturnOffset;
                    g_splashReturn = splash + kCallReturnOffset;
                }
            }
            enabled = enabled && g_bulletReturn && g_splashReturn && !g_failed.load(std::memory_order_acquire);
            g_enabled.store(enabled, std::memory_order_release);
        }

        // ---- Sim capture -----------------------------------------------------
        float ReadHealthRatio(const void* object)
        {
            __try
            {
                return *reinterpret_cast<const float*>(static_cast<const uint8_t*>(object) + 0x200);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return NAN;
            }
        }

        // Layouts (Docs/LOCAL_DAMAGE.md): DAMAGE +4 = source OBJ76; OBJ76
        // +0x38 front (float3), +0x48 world position (double3).
        bool ReadHit(uint8_t kind, const void* damage, uint32_t argument, double point[3], float direction[3])
        {
            __try
            {
                const auto* const source = *reinterpret_cast<const uint8_t* const*>(static_cast<const uint8_t*>(damage) + 4);
                if (!source || !argument)
                    return false;
                const auto* const vector = reinterpret_cast<const float*>(static_cast<uintptr_t>(argument));
                if (kind == 1)
                {
                    // Ordnance::Hit passes &source->front; the ordnance's
                    // position follows it at +0x10.
                    if (reinterpret_cast<uintptr_t>(source) + 0x38 != argument)
                        return false;
                    const auto* const position = reinterpret_cast<const double*>(static_cast<uintptr_t>(argument) + 0x10);
                    for (int i = 0; i < 3; ++i) point[i] = position[i];
                }
                else
                {
                    const auto* const position = reinterpret_cast<const double*>(source + 0x48);
                    for (int i = 0; i < 3; ++i) point[i] = position[i];
                }
                for (int i = 0; i < 3; ++i) direction[i] = vector[i];
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            for (int i = 0; i < 3; ++i)
                if (!std::isfinite(point[i]) || !std::isfinite(direction[i]))
                    return false;
            return true;
        }

        void Push(const HitEvent& event)
        {
            AcquireSRWLockExclusive(&g_queueLock);
            if (g_queueCount < kQueueCapacity)
                g_queue[g_queueCount++] = event;
            else
                ++g_queueDropped;
            ReleaseSRWLockExclusive(&g_queueLock);
        }

        void ClearQueue()
        {
            AcquireSRWLockExclusive(&g_queueLock);
            g_queueCount = 0;
            g_queueDropped = 0;
            ReleaseSRWLockExclusive(&g_queueLock);
        }

        // ---- Ogre ------------------------------------------------------------
        bool ResolveApi()
        {
            if (g_apiResolved)
                return g_apiAvailable;
            g_apiResolved = true;
            OgreApi& o = g_ogre;
            o.rootSingleton = ResolveOgreProc<FnSingleton>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            o.addFrameListener = ResolveOgreProc<FnAddListener>("?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
            o.subEntityCount = ResolveOgreProc<FnCount>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            o.subEntityAt = ResolveOgreProc<FnSubAt>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            o.setCustomParameter = ResolveOgreProc<FnSetCustom>("?setCustomParameter@Renderable@Ogre@@QAEXIABVVector4@2@@Z");
            o.parentSceneNode = ResolveOgreProc<FnPointer>("?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ");
            o.derivedPosition = ResolveOgreProc<FnVector>("?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ");
            o.derivedOrientation = ResolveOgreProc<FnVector>("?_getDerivedOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ");
            o.derivedScale = ResolveOgreProc<FnVector>("?_getDerivedScale@Node@Ogre@@UBEABVVector3@2@XZ");
            o.boundingRadius = ResolveOgreProc<FnRadius>("?getBoundingRadius@Entity@Ogre@@UBEMXZ");
            g_apiAvailable = o.rootSingleton && o.addFrameListener && o.subEntityCount && o.subEntityAt &&
                             o.setCustomParameter && o.parentSceneNode && o.derivedPosition &&
                             o.derivedOrientation && o.derivedScale && o.boundingRadius &&
                             OgreEntityLiveness::Available();
            if (!g_apiAvailable)
                LogShimA(LogLevel::Warn, kComponent, "[LOCALDMG] Ogre exports missing; scorch disabled");
            return g_apiAvailable;
        }

        bool GatePasses()
        {
            return RenderProfiles::Exports::GetActiveBackend() ==
                       static_cast<uint32_t>(RenderProfiles::ActiveBackend::DX11) &&
                   RenderProfiles::Exports::GetEffectiveRenderProfile() == RenderProfiles::Abi::kProfileEnhanced &&
                   RenderProfiles::IdentifyActiveRenderSystem() == 1;
        }

        void WriteParameters(void* entity, const float values[Policy::kParameterCount][4])
        {
            const unsigned count = g_ogre.subEntityCount(entity);
            for (unsigned i = 0; i < count && i < 256; ++i)
            {
                void* const sub = g_ogre.subEntityAt(entity, i);
                if (!sub)
                    continue;
                // SubEntity's Renderable base sits at offset 0.
                for (int k = 0; k < Policy::kParameterCount; ++k)
                    g_ogre.setCustomParameter(sub, static_cast<size_t>(Policy::kMarkParameterBase + k), values[k]);
            }
        }

        void WriteKey(void* entity, const float key[4])
        {
            const unsigned count = g_ogre.subEntityCount(entity);
            for (unsigned i = 0; i < count && i < 256; ++i)
                if (void* const sub = g_ogre.subEntityAt(entity, i))
                    g_ogre.setCustomParameter(sub, static_cast<size_t>(Policy::kKeyParameter), key);
        }

        void ZeroEntity(void* entity)
        {
            static const float zero[Policy::kParameterCount][4] = {};
            static const float noKey[4] = {};
            WriteParameters(entity, zero);
            WriteKey(entity, noKey);
            ++g_stats.zeroed;
        }

        // The Entity a GameObject's marks go on: the first bridge root whose
        // Entity passes the RTTI check and, unless it is `known` (proven in
        // an earlier frame) outside a prove pass, the SceneManager proof.
        // Null when no candidate is a live Entity.
        void* ResolveEntity(void* sceneManager, void* obj76, bool provePass, void* known)
        {
            void* directRoot = nullptr;
            void* ownerRoot = nullptr;
            OgreEntityLiveness::ReadBridgeRoots(static_cast<const uint8_t*>(obj76), directRoot, ownerRoot);
            void* const candidates[] = {
                g_rootProbes.Resolve(directRoot, g_frame, provePass),
                g_rootProbes.Resolve(ownerRoot, g_frame, provePass),
            };
            g_stage = "entity";
            for (void* entity : candidates)
            {
                if (!entity || !OgreEntityLiveness::IsOgreEntityObject(entity))
                    continue;
                if ((entity == known && !provePass) || OgreEntityLiveness::EntityProvenLive(sceneManager, entity))
                    return entity;
            }
            return nullptr;
        }

        void* ResolveObjectEntity(void* sceneManager, void* object, bool provePass, void* known)
        {
            void* obj76 = nullptr;
            if (!Hooks::TryGetGameObjectObj76(object, obj76) || !obj76)
                return nullptr;
            return ResolveEntity(sceneManager, obj76, provePass, known);
        }

        struct NodePose
        {
            float position[3];
            float q[4];  // w, x, y, z
            float scale[3];
        };

        // The Entity's parent SceneNode, the space the shader's
        // surfaceViewToLocal reconstructs.
        bool ReadNodePose(void* entity, NodePose& pose)
        {
            void* const node = g_ogre.parentSceneNode(entity);
            if (!node)
                return false;
            std::memcpy(pose.position, g_ogre.derivedPosition(node), sizeof(pose.position));
            std::memcpy(pose.q, g_ogre.derivedOrientation(node), sizeof(pose.q));
            std::memcpy(pose.scale, g_ogre.derivedScale(node), sizeof(pose.scale));
            return true;
        }

        bool EntityLocalHit(void* entity, const HitEvent& event, float local[3], float& localPerMetre)
        {
            float origin[3] = {};
            const uintptr_t originAddr = Hooks::WorldRenderOriginAddr();
            if (!originAddr)
                return false;
            std::memcpy(origin, reinterpret_cast<const void*>(originAddr), sizeof(origin));
            NodePose pose;
            if (!ReadNodePose(entity, pose))
                return false;

            float renderPoint[3], renderDirection[3], localPoint[3], localDirection[3];
            static const float kZero[3] = {};
            Policy::SimToRender(event.point, origin, renderPoint);
            Policy::SimDirectionToRender(event.direction, renderDirection);
            if (!Policy::ToLocal(renderPoint, pose.position, pose.q, pose.scale, localPoint) ||
                !Policy::ToLocal(renderDirection, kZero, pose.q, pose.scale, localDirection))
                return false;
            localPerMetre = Policy::LocalPerMetre(pose.scale);
            // Entity::getBoundingRadius is the mesh's own sphere (local
            // units, unscaled); the metre fallback is converted. It only
            // pulls in far points (splash centres): the sim's hit point
            // sits on its collision box, off the hull, and the shader's
            // radial-cylinder test makes that depth error harmless.
            float hull = g_ogre.boundingRadius(entity);
            hull = (std::isfinite(hull) && hull > 0.0f) ? hull * Policy::kHullFraction
                                                        : Policy::kFallbackHullRadius * localPerMetre;
            return Policy::PlaceOnHull(localPoint, localDirection, hull, local);
        }

        int FindOrCreateUnit(void* object, int handle)
        {
            const auto found = g_unitByObject.find(object);
            if (found != g_unitByObject.end())
            {
                Unit& unit = g_units[found->second];
                if (unit.handle == handle)
                    return found->second;
                unit.marks.Clear();
                unit.handle = handle;
                unit.dirty = true;
                return found->second;
            }
            for (int i = 0; i < Policy::kMaxUnits; ++i)
            {
                if (g_units[i].used)
                    continue;
                g_units[i] = Unit{};
                g_units[i].used = true;
                g_units[i].object = object;
                g_units[i].handle = handle;
                g_unitByObject[object] = i;
                ++g_unitCount;
                return i;
            }
            return -1;
        }

        // A released unit's Entity is zeroed only while the live scene still
        // owns it; one that is gone is forgotten without being touched.
        void ReleaseUnit(int index, void* sceneManager)
        {
            Unit& unit = g_units[index];
            if (sceneManager && unit.entity && unit.marks.Any() &&
                OgreEntityLiveness::IsOgreEntityObject(unit.entity) &&
                OgreEntityLiveness::EntityProvenLive(sceneManager, unit.entity))
                ZeroEntity(unit.entity);
            g_unitByObject.erase(unit.object);
            unit = Unit{};
            --g_unitCount;
        }

        float FrameSeconds()
        {
            LARGE_INTEGER now{}, frequency{};
            QueryPerformanceCounter(&now);
            QueryPerformanceFrequency(&frequency);
            float seconds = 0.0f;
            if (g_lastCounter.QuadPart && frequency.QuadPart)
                seconds = static_cast<float>(static_cast<double>(now.QuadPart - g_lastCounter.QuadPart) /
                                             static_cast<double>(frequency.QuadPart));
            g_lastCounter = now;
            return seconds < 0.0f ? 0.0f : (seconds > kMaxFrameSeconds ? kMaxFrameSeconds : seconds);
        }

        void RenderFrame()
        {
            g_stage = "drain";
            static HitEvent s_events[kQueueCapacity];
            size_t eventCount = 0;
            AcquireSRWLockExclusive(&g_queueLock);
            eventCount = g_queueCount;
            std::memcpy(s_events, g_queue, eventCount * sizeof(HitEvent));
            g_queueCount = 0;
            g_stats.dropped += g_queueDropped;
            g_queueDropped = 0;
            ReleaseSRWLockExclusive(&g_queueLock);

            const float dt = FrameSeconds();
            if (g_unitCount == 0 && eventCount == 0)
                return;
            // Entities are proven against this scene before they are touched;
            // without one the frame is skipped (the events with it).
            void* const sceneManager = Hooks::GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;

            ++g_frame;
            const bool provePass = (g_frame % kProveIntervalFrames) == 0;

            // Marked units: drop the dead, re-resolve the rest. An Entity
            // seen before skips the SceneManager proof except on prove passes.
            g_stage = "units";
            for (int i = 0; i < Policy::kMaxUnits; ++i)
            {
                Unit& unit = g_units[i];
                if (!unit.used)
                    continue;
                if (GameObjectFromHandleGog(unit.handle) != unit.object)
                {
                    ReleaseUnit(i, sceneManager);
                    continue;
                }
                void* const entity = ResolveObjectEntity(sceneManager, unit.object, provePass, unit.entity);
                if (!entity)
                {
                    unit.entity = nullptr;
                    continue;
                }
                const unsigned count = g_ogre.subEntityCount(entity);
                void* const first = count ? g_ogre.subEntityAt(entity, 0) : nullptr;
                // A new Entity, or new sub-entities, carry none of the marks.
                if (entity != unit.entity || count != unit.subCount || first != unit.firstSub)
                    unit.dirty = true;
                unit.entity = entity;
                unit.entityFrame = g_frame;
                unit.subCount = count;
                unit.firstSub = first;
            }

            // This frame's hits: one resolve per struck object.
            g_stage = "events";
            static void* s_eventEntity[kQueueCapacity];
            for (size_t i = 0; i < eventCount; ++i)
            {
                const HitEvent& event = s_events[i];
                s_eventEntity[i] = nullptr;
                if (GameObjectFromHandleGog(event.handle) != event.object)
                    continue;
                bool reused = false;
                for (size_t j = 0; j < i && !reused; ++j)
                    if (s_events[j].object == event.object && s_events[j].handle == event.handle &&
                        s_eventEntity[j])
                    {
                        s_eventEntity[i] = s_eventEntity[j];
                        reused = true;
                    }
                if (reused)
                    continue;
                const auto known = g_unitByObject.find(event.object);
                const Unit* const unit = known != g_unitByObject.end() ? &g_units[known->second] : nullptr;
                if (unit && unit->entity && unit->entityFrame == g_frame)
                    s_eventEntity[i] = unit->entity;
                else
                    s_eventEntity[i] = ResolveObjectEntity(sceneManager, event.object, provePass, nullptr);
            }
            g_rootProbes.PruneUnseen(g_frame);

            g_stage = "hits";
            for (size_t i = 0; i < eventCount; ++i)
            {
                const HitEvent& event = s_events[i];
                void* const entity = s_eventEntity[i];
                if (!entity)
                    continue;
                float local[3];
                float localPerMetre = 1.0f;
                if (!EntityLocalHit(entity, event, local, localPerMetre))
                    continue;
                const int slot = FindOrCreateUnit(event.object, event.handle);
                if (slot < 0)
                {
                    ++g_stats.dropped;
                    continue;
                }
                Unit& unit = g_units[slot];
                if (unit.entity != entity || unit.entityFrame != g_frame)
                {
                    unit.entity = entity;
                    unit.entityFrame = g_frame;
                    unit.subCount = g_ogre.subEntityCount(entity);
                    unit.firstSub = unit.subCount ? g_ogre.subEntityAt(entity, 0) : nullptr;
                }
                unit.lastHealth = event.after;
                unit.localPerMetre = localPerMetre;
                if (Policy::AddMark(unit.marks, local, event.radius, g_maxMarks, localPerMetre))
                    ++g_stats.merged;
                ++g_stats.hits;
                unit.dirty = true;
            }

            g_stage = "write";
            for (int i = 0; i < Policy::kMaxUnits; ++i)
            {
                Unit& unit = g_units[i];
                if (!unit.used)
                    continue;
                const float health = ReadHealthRatio(unit.object);
                if (Policy::RepairClears(unit.lastHealth, health))
                {
                    unit.marks.Clear();
                    unit.dirty = true;
                }
                if (std::isfinite(health))
                    unit.lastHealth = health;
                if (Policy::DecayHeat(unit.marks, dt, g_emberSeconds))
                    unit.dirty = true;
                if (!unit.entity || unit.entityFrame != g_frame)
                    continue;
                if (unit.dirty)
                {
                    float values[Policy::kParameterCount][4];
                    Policy::PackParameters(unit.marks, g_maxMarks, values, unit.localPerMetre);
                    WriteParameters(unit.entity, values);
                    unit.dirty = false;
                }
                // Repaired: the zeros are written, nothing is left to track.
                if (!unit.marks.Any())
                {
                    g_unitByObject.erase(unit.object);
                    unit = Unit{};
                    --g_unitCount;
                }
            }
            g_stage = "idle";
        }

        void ReleaseMissionState()
        {
            // The scene's Entities are going or gone: forget them, never touch.
            for (Unit& unit : g_units)
                unit = Unit{};
            g_unitByObject.clear();
            g_unitCount = 0;
            g_rootProbes.Clear();
            g_lastCounter.QuadPart = 0;
            ClearQueue();
        }

        void LogMissionSummary()
        {
            if (g_stats.hits || g_stats.dropped)
                LogShimA(LogLevel::Info, kComponent,
                    "[LOCALDMG] mission: hits=%u merged=%u dropped=%u entities-zeroed=%u",
                    g_stats.hits, g_stats.merged, g_stats.dropped, g_stats.zeroed);
        }

        // osMarkKey for every unit that has a mark: the main view camera in
        // its Entity's local space. Called from the world render-queue hook,
        // after the frame's node and camera updates and before the draws, so
        // it matches what surfaceViewToLocal gives the shader. Once per frame
        // unless the camera moved in between.
        uint32_t g_keyFrame = 0;
        float g_keyCamera[3] = {};

        void WriteKeys()
        {
            float camera[3] = {};
            float fovY = 0.0f;
            if (!Hooks::TryGetMainViewCamera(camera, &fovY))
                return;
            if (g_keyFrame == g_frame && std::memcmp(camera, g_keyCamera, sizeof(camera)) == 0)
                return;
            g_keyFrame = g_frame;
            std::memcpy(g_keyCamera, camera, sizeof(camera));
            g_stage = "key";
            for (Unit& unit : g_units)
            {
                if (!unit.used || !unit.entity || !unit.marks.Any())
                    continue;
                // Resolved and RTTI-checked at this frame's frameStarted;
                // Entities are destroyed by the sim, never inside the render.
                if (unit.entityFrame != g_frame)
                    continue;
                NodePose pose;
                if (!ReadNodePose(unit.entity, pose))
                    continue;
                float key[4] = {0.0f, 0.0f, 0.0f, 1.0f};
                if (!Policy::ToLocal(camera, pose.position, pose.q, pose.scale, key))
                    key[0] = key[1] = key[2] = key[3] = 0.0f;
                WriteKey(unit.entity, key);
            }
            g_stage = "idle";
        }

        // Belt and braces at mission end and on Disable: zero the Entities
        // that carry marks, each proven against the live scene first.
        void ZeroMarkedEntities()
        {
            void* const sceneManager = Hooks::GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;
            g_stage = "zero-marked";
            for (Unit& unit : g_units)
            {
                if (!unit.used || !unit.entity || !unit.marks.Any() ||
                    !OgreEntityLiveness::IsOgreEntityObject(unit.entity) ||
                    !OgreEntityLiveness::EntityProvenLive(sceneManager, unit.entity))
                    continue;
                ZeroEntity(unit.entity);
                unit.marks.Clear();
            }
            g_stage = "idle";
        }

        bool RunCxx(void (*work)())
        {
            try
            {
                work();
                return true;
            }
            catch (...)
            {
                strcpy_s(g_faultDetail, "C++ exception");
                return false;
            }
        }

        int RecordSehFault(EXCEPTION_POINTERS* info)
        {
            const EXCEPTION_RECORD* const record = info ? info->ExceptionRecord : nullptr;
            _snprintf_s(g_faultDetail, sizeof(g_faultDetail), _TRUNCATE, "SEH 0x%08lX at 0x%08X",
                record ? record->ExceptionCode : 0ul,
                static_cast<unsigned>(reinterpret_cast<uintptr_t>(record ? record->ExceptionAddress : nullptr)));
            return EXCEPTION_EXECUTE_HANDLER;
        }

        // No destructible locals: SEH and C++ unwinding do not mix in one frame.
        bool RunSeh(void (*work)())
        {
            bool ok = false;
            __try
            {
                ok = RunCxx(work);
            }
            __except (RecordSehFault(GetExceptionInformation()))
            {
                ok = false;
                if (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW)
                    _resetstkoflw();
            }
            return ok;
        }

        void Disable(const char* why)
        {
            g_failed.store(true, std::memory_order_release);
            g_active.store(false, std::memory_order_release);
            g_enabled.store(false, std::memory_order_release);
            LogShimA(LogLevel::Error, kComponent, "[LOCALDMG] disabled for this session: %s", why);
            // Once only: a fault inside the zeroing itself is just logged.
            static bool s_zeroing = false;
            if (s_zeroing)
                return;
            s_zeroing = true;
            if (!RunSeh(ZeroMarkedEntities))
                LogShimA(LogLevel::Error, kComponent, "[LOCALDMG] fault zeroing marks on disable: %s", g_faultDetail);
        }

        void RunGuarded(void (*work)(), const char* what)
        {
            if (RunSeh(work))
                return;
            LogShimA(LogLevel::Error, kComponent, "[LOCALDMG] %s fault: stage=%s %s", what, g_stage,
                g_faultDetail[0] ? g_faultDetail : "(no detail)");
            Disable(what);
        }

        void RenderFrameGuarded()
        {
            RunGuarded(RenderFrame, "frame update");
        }

        // Ogre::FrameListener, laid out to its vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor.
        class FrameListener
        {
        public:
            virtual bool frameStarted(const void*)
            {
                if (g_active.load(std::memory_order_acquire) && !g_failed.load(std::memory_order_acquire))
                    RenderFrameGuarded();
                return true;
            }
            virtual bool frameRenderingQueued(const void*) { return true; }
            virtual bool frameEnded(const void*) { return true; }
            virtual ~FrameListener() = default;
        };
        FrameListener g_listener;
    }

    namespace LocalDamage
    {
        bool WantsDamage()
        {
            if (!g_configRead)
                ReloadConfig();
            // No adapters for a renderer that cannot show the marks.
            return g_enabled.load(std::memory_order_acquire) && GatePasses();
        }

        void RequestReload()
        {
            g_reloadRequested.store(true, std::memory_order_release);
        }

        CraftCapture BeforeCraftDamage(void* receiver, void* damage, uint32_t argument, uintptr_t returnAddress) noexcept
        {
            CraftCapture capture;
            if (!g_active.load(std::memory_order_acquire) || !receiver || !damage || !g_GameObjectGetHandleAddr)
                return capture;
            uint8_t kind = 0;
            if (returnAddress == g_bulletReturn)
                kind = 1;
            else if (returnAddress == g_splashReturn)
                kind = 2;
            if (!kind)
                return capture;
            void* const object = static_cast<uint8_t*>(receiver) - 0x18;
            if (!ReadHit(kind, damage, argument, capture.point, capture.direction))
                return capture;
            __try
            {
                capture.handle = reinterpret_cast<GetHandle>(g_GameObjectGetHandleAddr)(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return CraftCapture{};
            }
            if (!capture.handle || GameObjectFromHandleGog(capture.handle) != object)
                return CraftCapture{};
            capture.before = ReadHealthRatio(object);
            if (!std::isfinite(capture.before))
                return CraftCapture{};
            capture.object = object;
            capture.kind = kind;
            return capture;
        }

        void AfterCraftDamage(const CraftCapture& capture) noexcept
        {
            if (!capture.object || !g_active.load(std::memory_order_acquire))
                return;
            // A kill frees nothing inside DamageAlloc, but the handle check
            // keeps this to the same lifetime regardless.
            if (GameObjectFromHandleGog(capture.handle) != capture.object)
                return;
            const float after = ReadHealthRatio(capture.object);
            const float lost = capture.before - after;
            if (!std::isfinite(lost) || lost <= 0.0f)
                return;
            HitEvent event{};
            event.object = capture.object;
            event.handle = capture.handle;
            for (int i = 0; i < 3; ++i)
            {
                event.point[i] = capture.point[i];
                event.direction[i] = capture.direction[i];
            }
            event.radius = RadiusFromHealthLost(lost);
            event.after = after;
            Push(event);
        }
    }

    void LocalDamageSetSceneTeardownSeam(bool installed)
    {
        g_teardownSeam = installed;
    }

    void LocalDamageNotifySceneEntitiesDestroyed()
    {
        g_awaitTeardown = false;
        g_missionEvaluated = false;
        if (!g_active.exchange(false))
            return;
        try
        {
            LogMissionSummary();
            ReleaseMissionState();
        }
        catch (...)
        {
            Disable("fault releasing mission state at scene teardown");
        }
    }

    void LocalDamageNotifyMissionRunStateChanged(bool running)
    {
        if (!running)
        {
            g_missionEvaluated = false;
            if (!g_active.exchange(false))
                return;
            g_awaitTeardown = g_teardownSeam;
            g_awaitStartedFrames = 0;
            // The debrief still renders this world: take the marks off it.
            RunGuarded(ZeroMarkedEntities, "mission-end zeroing");
            try
            {
                LogMissionSummary();
                ReleaseMissionState();
            }
            catch (...)
            {
                Disable("fault releasing mission state at mission end");
            }
            return;
        }

        g_missionEvaluated = true;
        ReloadConfig();
        if (g_failed.load(std::memory_order_acquire) || !g_enabled.load(std::memory_order_acquire))
            return;
        if (!GatePasses())
        {
            LogShimA(LogLevel::Info, kComponent, "[LOCALDMG] enabled but render profile is not DX11 Enhanced; no scorch");
            return;
        }
        if (!ResolveApi())
            return;
        g_stats = {};
        ReleaseMissionState();
        g_active.store(true, std::memory_order_release);
        LogShimA(LogLevel::Info, kComponent, "[LOCALDMG] active (max marks %d, ember %.1fs)", g_maxMarks, g_emberSeconds);
    }

    namespace
    {
        // Render thread. Off: stop capture first, then take the marks off the
        // scene. On: let the tick below re-run the mission-start evaluation.
        void ApplyLiveToggle()
        {
            const bool wasEnabled = g_enabled.load(std::memory_order_acquire);
            ReloadConfig();
            // Other live rows request a reload too; act only on a real flip.
            if (g_enabled.load(std::memory_order_acquire) == wasEnabled)
                return;
            if (!g_enabled.load(std::memory_order_acquire))
            {
                if (!g_active.exchange(false))
                    return;
                RunGuarded(ZeroMarkedEntities, "toggle-off zeroing");
                try
                {
                    LogMissionSummary();
                    ReleaseMissionState();
                }
                catch (...)
                {
                    Disable("fault releasing mission state on toggle off");
                }
                return;
            }
            if (!g_active.load(std::memory_order_acquire) && !g_awaitTeardown)
                g_missionEvaluated = false;
        }
    }

    void LocalDamageRenderFrameTick()
    {
        if (g_reloadRequested.exchange(false, std::memory_order_acq_rel))
            ApplyLiveToggle();
        // Started at the first world render of a mission, as GPU skinning.
        if (g_awaitTeardown)
        {
            int state = Hooks::kBzrRunStateUnknown;
            if (Hooks::TryReadBzrRunState(state) && state == Hooks::kBzrRunStateStarted &&
                ++g_awaitStartedFrames >= kAwaitTeardownFrameLimit)
                g_awaitTeardown = false;
        }
        if (!g_missionEvaluated && !g_awaitTeardown)
            LocalDamageNotifyMissionRunStateChanged(true);
        if (!g_active.load(std::memory_order_acquire) || g_failed.load(std::memory_order_acquire))
            return;
        void* const root = g_ogre.rootSingleton ? g_ogre.rootSingleton() : nullptr;
        if (!root)
        {
            Disable("Ogre Root unavailable");
            return;
        }
        if (root != g_listenerRoot)
        {
            g_listenerRoot = root;
            g_ogre.addFrameListener(root, &g_listener);
            LogShimA(LogLevel::Info, kComponent, "[LOCALDMG] frame listener installed");
        }
        if (g_unitCount > 0)
            RunGuarded(WriteKeys, "key update");
    }
}
