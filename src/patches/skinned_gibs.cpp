// skinned_gibs.cpp
// BZR Open Shim - SkinnedGibs: when a person (pilot, soldier, zombie; RTTI
// .?AVPerson@@) is fully fragmented, replace its legacy body chunks with
// rigid per-limb gibs cut from the live skinned mesh, posed exactly where each
// limb was on the frame of death, and simulated here with the legacy chunk
// launch math tuned for flesh.
//
// Purely additive. The engine's ChunkEffect state and chunk objects are never
// written: the legacy chunks for the body still simulate (and smoke and pop)
// as before, the proxy renderer is only told not to draw the ones this death
// created. Vehicles, buildings and powerups never reach the gib path, the gib
// pool is separate from the chunk proxy slots, and [General] SkinnedGibs = 0
// leaves every entry point below a no-op.
//
// Split: NativeChunks::ExtractGibs (runtime, cached under
// openshim/cache/chunks/gibs/v1/<hash>/), or an authored gibs.txt payload from
// scripts/export_gib_payloads.py. Rendering: shim-owned entities on the chunk
// payload resource group, submitted from the world render-queue hook like the
// chunk proxies. Simulation: ChunkEffect::Simulate's dt.

#include "bzr_hooks_internal.h"
#include "game_state.h"
#include "hook_engine.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            // ---- Tuning ----------------------------------------------------
            // Launch values are the legacy engine's own; the ground response
            // is new (legacy chunks explode on first terrain contact), tuned so
            // limbs thud, slide a little and lie still instead of bouncing.
            struct GibTuning
            {
                // ChunkEffect::CreateChunk (BZ 1.5 0x004BE555): each axis gets
                // Pseudo_Rand() * 10 plus the fragment velocity, and +5 up;
                // omega = Pseudo_Rand() * 5 rad/s per axis.
                float launchRandom = 10.0f;
                float launchUp = 5.0f;
                float spin = 5.0f;
                // ChunkEffect::FullFragmentObject (0x004BF08B): every piece is
                // kicked away from the fragment root's world position by
                // (p - origin) * (2, 1, 2).
                float kickHorizontal = 2.0f;
                float kickVertical = 1.0f;
                // ChunkEffect::Simulate: veloc.y -= dt * 9.8.
                float gravity = 9.8f;
                // Flesh ground response (not legacy).
                float restitution = 0.15f;  // normal speed kept per bounce
                float friction = 0.55f;     // tangential speed lost per bounce
                float spinDamp = 0.5f;      // omega kept per bounce
                float settleSpeed = 0.6f;   // below this after a bounce: at rest
                float contactRadius = 0.35f; // fraction of radius kept above ground
                float heavyRadius = 0.3f;   // larger pieces spin at half rate
                float sinkDepth = 0.4f;
                float sinkSeconds = 2.0f;
                float maxLifetime = 20.0f;
                float maxStep = 0.1f;
            };
            constexpr GibTuning kTuning = {};

            constexpr const char* kPersonRtti = ".?AVPerson@@";
            constexpr size_t kGameObjectRenderBridgeOffset = 0x0F0;
            constexpr size_t kRenderBridgeWorldEntityOffset = 0x094;
            constexpr size_t kRenderBridgeWorldNodeOffset = 0x098;
            constexpr uint16_t kMaxCapturedBones = 256;
            constexpr size_t kMaxSuppressedChunks = 4096;
            constexpr const char* kFleshMaterialFile = "openshim_gib_flesh.material";
            constexpr const char* kFleshMaterialMarker = "// OpenShim SkinnedGibs default flesh material";

            // ---- Config ----------------------------------------------------
            struct GibConfig
            {
                bool initialized = false;
                bool enabled = true;
                bool trace = false;
                size_t maxGibs = 160;
                float linger = 8.0f;
                float force = 1.0f;
            };
            GibConfig g_Config;

            bool ReadEnvNumber(const char* name, double& out)
            {
                char buffer[64] = {};
                const DWORD length = GetEnvironmentVariableA(name, buffer, static_cast<DWORD>(sizeof(buffer)));
                if (length == 0 || length >= sizeof(buffer))
                    return false;
                char* end = nullptr;
                const double value = std::strtod(buffer, &end);
                while (end && (*end == ' ' || *end == '\t'))
                    ++end;
                if (!end || end == buffer || *end || !std::isfinite(value))
                    return false;
                out = value;
                return true;
            }

            void InitializeConfig()
            {
                if (g_Config.initialized)
                    return;
                g_Config.initialized = true;
                // [General] SkinnedGibs (default ON) arrives inverted through
                // the env mapping, like ChunkMeshes.
                g_Config.enabled = !EnvFlagEnabled("OPENSHIM_DISABLE_SKINNED_GIBS");
                g_Config.trace = EnvFlagEnabled("OPENSHIM_TRACE_SKINNED_GIBS");
                double value = 0.0;
                if (ReadEnvNumber("OPENSHIM_SKINNED_GIBS_MAX", value))
                    g_Config.maxGibs = static_cast<size_t>(std::clamp(value, 12.0, 1024.0));
                if (ReadEnvNumber("OPENSHIM_SKINNED_GIBS_LINGER", value))
                    g_Config.linger = static_cast<float>(std::clamp(value, 0.0, 60.0));
                if (ReadEnvNumber("OPENSHIM_SKINNED_GIBS_FORCE", value))
                    g_Config.force = static_cast<float>(std::clamp(value, 0.0, 5.0));
                LogChunkDiagnostic(
                    "skinnedgibs",
                    L"[SKINNEDGIBS] config enabled=%u max=%zu linger=%.2f force=%.2f trace=%u\n",
                    g_Config.enabled ? 1u : 0u,
                    g_Config.maxGibs,
                    static_cast<double>(g_Config.linger),
                    static_cast<double>(g_Config.force),
                    g_Config.trace ? 1u : 0u);
            }

            // Budgeted: a battle can kill dozens of pilots.
            volatile LONG g_LogBudget = 96;
            bool AcquireGibLogSlot()
            {
                return g_Config.trace || InterlockedDecrement(&g_LogBudget) >= 0;
            }

            // ---- Small math (Ogre quaternions are w, x, y, z) ---------------
            struct Vec3
            {
                float x, y, z;
            };
            struct Quat
            {
                float w, x, y, z;
            };
            Vec3 Add(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
            Vec3 Sub(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
            Vec3 Scale(Vec3 a, float s) { return {a.x * s, a.y * s, a.z * s}; }
            Vec3 Mul(Vec3 a, Vec3 b) { return {a.x * b.x, a.y * b.y, a.z * b.z}; }
            float Dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
            Vec3 Cross(Vec3 a, Vec3 b)
            {
                return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
            }
            float Length(Vec3 a) { return std::sqrt(Dot(a, a)); }
            Quat QMul(Quat a, Quat b)
            {
                return {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
                        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
            }
            Quat QNormalize(Quat q)
            {
                const float n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
                if (!(n > 1e-8f) || !std::isfinite(n))
                    return {1, 0, 0, 0};
                return {q.w / n, q.x / n, q.y / n, q.z / n};
            }
            Vec3 Rotate(Quat q, Vec3 v)
            {
                const Quat r = QMul(QMul(q, {0, v.x, v.y, v.z}), {q.w, -q.x, -q.y, -q.z});
                return {r.x, r.y, r.z};
            }
            bool Finite(Vec3 v) { return std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z); }

            // Legacy Pseudo_Rand reads a 256-entry table of values in [-1, 1]
            // clustered around zero; the mean of two uniforms has that shape.
            struct GibRandom
            {
                uint32_t state = 1;
                float Uniform()
                {
                    state = state * 1664525u + 1013904223u;
                    return static_cast<float>(state >> 8) * (1.0f / 16777216.0f);
                }
                float Legacy() { return (Uniform() * 2.0f - 1.0f + Uniform() * 2.0f - 1.0f) * 0.5f; }
            };

            // ---- Death capture -----------------------------------------------
            struct BoneSample
            {
                char name[64];
                Vec3 position;
                Quat orientation;
                Vec3 bindInversePosition;
                Quat bindInverseOrientation;
                bool valid;
            };
            struct DeathCapture
            {
                bool active = false;
                void* entity = nullptr;
                void* chunkEffect = nullptr;
                uint32_t chunkCountBefore = 0;
                char meshName[260] = {};
                char group[128] = {};
                Vec3 nodePosition = {};
                Quat nodeOrientation = {1, 0, 0, 0};
                Vec3 nodeScale = {1, 1, 1};
                Vec3 velocity = {};
                uint16_t boneCount = 0;
                BoneSample bones[kMaxCapturedBones] = {};
                SkinnedGibModelInfo model;
            };
            DeathCapture g_Capture;

            struct OgreDeathApi
            {
                FnOgreEntityGetSkeleton getSkeleton = nullptr;
                FnOgreEntityU16Query getNumBones = nullptr;
                FnOgreSkeletonGetBoneByIndex getBone = nullptr;
                const std::string*(__thiscall* getNodeName)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedPosition)(void*) = nullptr;
                const OgreQuaternion*(__thiscall* derivedOrientation)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedScale)(void*) = nullptr;
                const OgreVector3*(__thiscall* bindInversePosition)(void*) = nullptr;
                const OgreQuaternion*(__thiscall* bindInverseOrientation)(void*) = nullptr;
                void*(__thiscall* parentSceneNode)(void*) = nullptr;
                FnOgreSetVisible setVisible = nullptr;
                bool usable = false;
            };
            const OgreDeathApi& GetDeathApi()
            {
                static OgreDeathApi api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.getSkeleton = ResolveOgreProc<FnOgreEntityGetSkeleton>(
                    "?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ");
                api.getNumBones = ResolveOgreProc<FnOgreEntityU16Query>("?getNumBones@Skeleton@Ogre@@UBEGXZ");
                api.getBone = ResolveOgreProc<FnOgreSkeletonGetBoneByIndex>("?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z");
                api.getNodeName = ResolveOgreProc<decltype(api.getNodeName)>(
                    "?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                api.derivedPosition = ResolveOgreProc<decltype(api.derivedPosition)>(
                    "?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ");
                api.derivedOrientation = ResolveOgreProc<decltype(api.derivedOrientation)>(
                    "?_getDerivedOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ");
                api.derivedScale = ResolveOgreProc<decltype(api.derivedScale)>(
                    "?_getDerivedScale@Node@Ogre@@UBEABVVector3@2@XZ");
                api.bindInversePosition = ResolveOgreProc<decltype(api.bindInversePosition)>(
                    "?_getBindingPoseInversePosition@Bone@Ogre@@QBEABVVector3@2@XZ");
                api.bindInverseOrientation = ResolveOgreProc<decltype(api.bindInverseOrientation)>(
                    "?_getBindingPoseInverseOrientation@Bone@Ogre@@QBEABVQuaternion@2@XZ");
                api.parentSceneNode = ResolveOgreProc<decltype(api.parentSceneNode)>(
                    "?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ");
                api.setVisible = ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
                api.usable = api.getSkeleton && api.getNumBones && api.getBone && api.getNodeName &&
                             api.derivedPosition && api.derivedOrientation && api.bindInversePosition &&
                             api.bindInverseOrientation && api.setVisible;
                return api;
            }

            bool ReadPointerSafe(const void* base, size_t offset, void*& out)
            {
                out = nullptr;
                if (!base)
                    return false;
                __try
                {
                    out = *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(base) + offset);
                    return out != nullptr;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out = nullptr;
                    return false;
                }
            }

            bool ReadVelocitySafe(const float* velocity, Vec3& out)
            {
                out = {};
                if (!velocity)
                    return false;
                __try
                {
                    out = {velocity[0], velocity[1], velocity[2]};
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out = {};
                    return false;
                }
                if (!Finite(out) || Length(out) > 500.0f)
                {
                    out = {};
                    return false;
                }
                return true;
            }

            // Every raw Ogre read for the pose in one SEH frame, POD only. The
            // entity is never touched again after the fragment hook returns.
            bool CaptureNodeSafe(const OgreDeathApi& api, void* node, DeathCapture& capture)
            {
                __try
                {
                    const OgreVector3* position = api.derivedPosition(node);
                    const OgreQuaternion* orientation = api.derivedOrientation(node);
                    if (!position || !orientation)
                        return false;
                    capture.nodePosition = {position->x, position->y, position->z};
                    capture.nodeOrientation = QNormalize({orientation->w, orientation->x, orientation->y, orientation->z});
                    capture.nodeScale = {1, 1, 1};
                    if (api.derivedScale)
                    {
                        const OgreVector3* scale = api.derivedScale(node);
                        if (scale)
                            capture.nodeScale = {scale->x, scale->y, scale->z};
                    }
                    return Finite(capture.nodePosition) && Finite(capture.nodeScale);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool CaptureBoneSafe(const OgreDeathApi& api, void* skeleton, uint16_t index, BoneSample& out)
            {
                out.valid = false;
                out.name[0] = '\0';
                __try
                {
                    void* const bone = api.getBone(skeleton, index);
                    if (!bone)
                        return false;
                    const std::string* name = api.getNodeName(bone);
                    if (name)
                    {
                        const size_t length = name->size();
                        if (length < sizeof(out.name))
                        {
                            std::memcpy(out.name, name->c_str(), length);
                            out.name[length] = '\0';
                        }
                    }
                    const OgreVector3* position = api.derivedPosition(bone);
                    const OgreQuaternion* orientation = api.derivedOrientation(bone);
                    const OgreVector3* bindPosition = api.bindInversePosition(bone);
                    const OgreQuaternion* bindOrientation = api.bindInverseOrientation(bone);
                    if (!position || !orientation || !bindPosition || !bindOrientation)
                        return false;
                    out.position = {position->x, position->y, position->z};
                    out.orientation = {orientation->w, orientation->x, orientation->y, orientation->z};
                    out.bindInversePosition = {bindPosition->x, bindPosition->y, bindPosition->z};
                    out.bindInverseOrientation = {bindOrientation->w, bindOrientation->x, bindOrientation->y,
                                                  bindOrientation->z};
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                out.orientation = QNormalize(out.orientation);
                out.bindInverseOrientation = QNormalize(out.bindInverseOrientation);
                out.valid = Finite(out.position) && Finite(out.bindInversePosition);
                return out.valid;
            }

            bool CaptureSkeletonSafe(const OgreDeathApi& api, void* entity, void*& outSkeleton, uint16_t& outCount)
            {
                outSkeleton = nullptr;
                outCount = 0;
                __try
                {
                    outSkeleton = api.getSkeleton(entity);
                    if (!outSkeleton)
                        return false;
                    outCount = api.getNumBones(outSkeleton);
                    return outCount > 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    outSkeleton = nullptr;
                    outCount = 0;
                    return false;
                }
            }

            void* ParentSceneNodeSafe(const OgreDeathApi& api, void* entity)
            {
                if (!api.parentSceneNode)
                    return nullptr;
                __try
                {
                    return api.parentSceneNode(entity);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            void HideEntitySafe(const OgreDeathApi& api, void* entity)
            {
                if (!LooksLikeOgreObject(entity))
                    return;
                __try
                {
                    api.setVisible(entity, false);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            // ---- Suppressed legacy chunks -------------------------------------
            struct SuppressedChunk
            {
                const uint8_t* object;
                const void* geom;
            };
            std::vector<SuppressedChunk> g_Suppressed;

            // ---- Gib pool -------------------------------------------------------
            struct GibSlot
            {
                void* sceneManager = nullptr;
                void* node = nullptr;
                void* entity = nullptr;
                std::string mesh;
                bool active = false;
                bool settled = false;
                bool sinking = false;
                bool impacted = false;
                bool hasGround = true;
                Vec3 position = {};
                Vec3 velocity = {};
                Vec3 omega = {};
                Quat orientation = {1, 0, 0, 0};
                Vec3 scale = {1, 1, 1};
                float radius = 0.0f;
                float age = 0.0f;
                float settledAge = 0.0f;
                float sinkElapsed = 0.0f;
                uint64_t serial = 0;
            };
            std::vector<GibSlot> g_Slots;
            // Meshes Ogre refused to instantiate this mission: not retried per
            // death, so a broken payload cannot leak a node every time.
            std::vector<std::string> g_FailedMeshes;
            uint64_t g_SpawnSerial = 0;
            size_t g_ActiveCount = 0;
            bool g_ResourcePrimeAttempted = false;

            void ForgetSlot(GibSlot& slot)
            {
                if (slot.active && g_ActiveCount)
                    --g_ActiveCount;
                slot = GibSlot{};
            }

            void ReleaseSlot(GibSlot& slot)
            {
                // Hidden, not destroyed: the entity is reused by the next gib
                // of the same mesh, or replaced between frames when recycled.
                if (slot.active && g_ActiveCount)
                    --g_ActiveCount;
                slot.active = false;
                HideShimOwnedObject(slot.node, slot.entity);
            }

            // The scene a slot was built in is the only one it may touch.
            bool SceneMatches(const GibSlot& slot, void* sceneManager)
            {
                return slot.sceneManager && slot.sceneManager == sceneManager;
            }

            void ForgetAll(const wchar_t* reason)
            {
                size_t forgotten = 0;
                for (GibSlot& slot : g_Slots)
                    if (slot.node || slot.entity)
                        ++forgotten;
                g_Slots.clear();
                g_ActiveCount = 0;
                g_Suppressed.clear();
                g_Capture.active = false;
                if (forgotten)
                {
                    LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] forgot %zu gib object(s) (%ls)\n", forgotten,
                                       reason ? reason : L"unspecified");
                }
            }

            // ---- Terrain ------------------------------------------------------
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
                    {
                        LogChunkDiagnostic("skinnedgibs",
                            L"[SKINNEDGIBS] Terrain::HeightAt unresolved; gibs fall without ground contact\n");
                    }
                }
                return fn;
            }

            bool TerrainHeightSafe(FnTerrainHeightAt fn, float x, float z, float& out)
            {
                if (!fn)
                    return false;
                double height = 0.0;
                __try
                {
                    height = fn(static_cast<double>(x), static_cast<double>(z));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                if (!std::isfinite(height) || std::abs(height) > 1.0e6)
                    return false;
                out = static_cast<float>(height);
                return true;
            }

            Vec3 GroundNormal(FnTerrainHeightAt fn, float x, float z)
            {
                constexpr float kStep = 0.25f;
                float hx0 = 0, hx1 = 0, hz0 = 0, hz1 = 0;
                if (!TerrainHeightSafe(fn, x - kStep, z, hx0) || !TerrainHeightSafe(fn, x + kStep, z, hx1) ||
                    !TerrainHeightSafe(fn, x, z - kStep, hz0) || !TerrainHeightSafe(fn, x, z + kStep, hz1))
                {
                    return {0, 1, 0};
                }
                Vec3 n = {hx0 - hx1, 2.0f * kStep, hz0 - hz1};
                const float length = Length(n);
                return length > 1e-6f ? Scale(n, 1.0f / length) : Vec3{0, 1, 0};
            }

            // TODO(SkinnedGibs): blood. A splat or puff belongs here, once an
            // explosion/decal entry point is verified on this build
            // (ExplosionClass::Find is not); do not guess one.
            void OnGibFirstImpact(const Vec3& position)
            {
                (void)position;
            }

            // ---- Spawning -----------------------------------------------------
            int FindBone(const DeathCapture& capture, const SkinnedGibPieceInfo& piece)
            {
                if (piece.bone < capture.boneCount && capture.bones[piece.bone].valid &&
                    (piece.boneName.empty() || _stricmp(capture.bones[piece.bone].name, piece.boneName.c_str()) == 0))
                {
                    return piece.bone;
                }
                if (piece.boneName.empty())
                    return -1;
                for (uint16_t i = 0; i < capture.boneCount; ++i)
                    if (capture.bones[i].valid && _stricmp(capture.bones[i].name, piece.boneName.c_str()) == 0)
                        return i;
                return -1;
            }

            GibSlot* AcquireSlot(const std::string& mesh, void* sceneManager)
            {
                const size_t limit = std::max<size_t>(g_Config.maxGibs, 1);
                GibSlot* sameMesh = nullptr;
                GibSlot* anyFree = nullptr;
                for (GibSlot& slot : g_Slots)
                {
                    if (slot.active || !SceneMatches(slot, sceneManager))
                        continue;
                    if (slot.mesh == mesh && slot.entity)
                    {
                        sameMesh = &slot;
                        break;
                    }
                    if (!anyFree)
                        anyFree = &slot;
                }
                if (sameMesh)
                    return sameMesh;
                if (g_Slots.size() < limit)
                {
                    g_Slots.emplace_back();
                    return &g_Slots.back();
                }
                if (anyFree)
                    return anyFree;
                // Full: recycle the oldest gib already at rest, else the oldest.
                GibSlot* oldestSettled = nullptr;
                GibSlot* oldest = nullptr;
                for (GibSlot& slot : g_Slots)
                {
                    if (!slot.active)
                        continue;
                    if (slot.settled && (!oldestSettled || slot.serial < oldestSettled->serial))
                        oldestSettled = &slot;
                    if (!oldest || slot.serial < oldest->serial)
                        oldest = &slot;
                }
                GibSlot* victim = oldestSettled ? oldestSettled : oldest;
                if (victim)
                    ReleaseSlot(*victim);
                return victim;
            }

            bool PrepareSlotEntity(GibSlot& slot, const std::string& mesh, void* sceneManager)
            {
                if (slot.entity && slot.mesh == mesh && SceneMatches(slot, sceneManager))
                    return true;
                if (slot.node && SceneMatches(slot, sceneManager))
                {
                    void* entity = slot.entity;
                    if (ReplaceShimOwnedMeshEntity(sceneManager, slot.node, entity, mesh.c_str()))
                    {
                        slot.entity = entity;
                        slot.mesh = mesh;
                        return true;
                    }
                    // The node stays attached and empty; Ogre owns it.
                    slot = GibSlot{};
                }
                void* createdScene = nullptr;
                void* node = nullptr;
                void* entity = nullptr;
                if (!CreateShimOwnedMeshObject(mesh.c_str(), createdScene, node, entity))
                    return false;
                slot.sceneManager = createdScene;
                slot.node = node;
                slot.entity = entity;
                slot.mesh = mesh;
                return true;
            }

            size_t SpawnFromCapture()
            {
                const DeathCapture& capture = g_Capture;
                void* const sceneManager = GetOgreSceneManagerRuntime();
                if (!sceneManager)
                    return 0;
                if (!g_Slots.empty() && g_Slots.front().sceneManager && g_Slots.front().sceneManager != sceneManager)
                    ForgetAll(L"scene manager changed");

                GibRandom random;
                random.state = static_cast<uint32_t>(GetTickCount()) ^
                               static_cast<uint32_t>(reinterpret_cast<uintptr_t>(capture.entity)) ^
                               static_cast<uint32_t>(g_SpawnSerial * 2654435761ull);
                const Vec3 origin = capture.nodePosition;
                size_t spawned = 0;
                size_t failed = 0;
                for (const SkinnedGibPieceInfo& piece : capture.model.pieces)
                {
                    const int boneIndex = FindBone(capture, piece);
                    if (boneIndex < 0)
                    {
                        ++failed;
                        continue;
                    }
                    const BoneSample& bone = capture.bones[boneIndex];
                    const Vec3 offset = {piece.offset[0], piece.offset[1], piece.offset[2]};
                    Vec3 local;
                    Quat localOrientation;
                    if (capture.model.authored)
                    {
                        // Model-space piece: the bone's skinning transform,
                        // derived * inverse(bind), applied to the pivot.
                        localOrientation = QNormalize(QMul(bone.orientation, bone.bindInverseOrientation));
                        const Vec3 skinPosition =
                            Add(bone.position, Rotate(localOrientation, bone.bindInversePosition));
                        local = Add(skinPosition, Rotate(localOrientation, offset));
                    }
                    else
                    {
                        // Bone-frame piece: the bone's current derived pose.
                        localOrientation = bone.orientation;
                        local = Add(bone.position, Rotate(bone.orientation, offset));
                    }
                    const Vec3 world =
                        Add(capture.nodePosition, Rotate(capture.nodeOrientation, Mul(capture.nodeScale, local)));
                    const Quat orientation = QNormalize(QMul(capture.nodeOrientation, localOrientation));
                    if (!Finite(world))
                    {
                        ++failed;
                        continue;
                    }

                    if (std::find(g_FailedMeshes.begin(), g_FailedMeshes.end(), piece.resource) !=
                        g_FailedMeshes.end())
                    {
                        ++failed;
                        continue;
                    }
                    GibSlot* slot = AcquireSlot(piece.resource, sceneManager);
                    if (!slot || !PrepareSlotEntity(*slot, piece.resource, sceneManager))
                    {
                        if (slot && !slot->node)
                        {
                            // A fresh slot that never got objects: drop it again.
                            for (auto it = g_Slots.begin(); it != g_Slots.end(); ++it)
                                if (&*it == slot)
                                {
                                    g_Slots.erase(it);
                                    break;
                                }
                        }
                        if (g_FailedMeshes.size() < 256)
                            g_FailedMeshes.push_back(piece.resource);
                        LogChunkDiagnostic("skinnedgibs",
                                           L"[SKINNEDGIBS] entity creation failed mesh=%hs (not retried)\n",
                                           piece.resource.c_str());
                        ++failed;
                        continue;
                    }

                    const float radius = std::max(piece.radius, 0.02f);
                    const float spinScale = radius > kTuning.heavyRadius ? 0.5f : 1.0f;
                    const Vec3 kick = Mul(Sub(world, origin),
                                          {kTuning.kickHorizontal, kTuning.kickVertical, kTuning.kickHorizontal});
                    Vec3 velocity = {random.Legacy() * kTuning.launchRandom * g_Config.force,
                                     random.Legacy() * kTuning.launchRandom * g_Config.force + kTuning.launchUp,
                                     random.Legacy() * kTuning.launchRandom * g_Config.force};
                    velocity = Add(Add(velocity, kick), capture.velocity);
                    const Vec3 omega = {random.Legacy() * kTuning.spin * spinScale,
                                        random.Legacy() * kTuning.spin * spinScale,
                                        random.Legacy() * kTuning.spin * spinScale};

                    slot->position = world;
                    slot->orientation = orientation;
                    slot->velocity = Finite(velocity) ? velocity : Vec3{0, kTuning.launchUp, 0};
                    slot->omega = omega;
                    slot->scale = capture.nodeScale;
                    slot->radius = radius;
                    slot->age = 0.0f;
                    slot->settledAge = 0.0f;
                    slot->sinkElapsed = 0.0f;
                    slot->settled = false;
                    slot->sinking = false;
                    slot->impacted = false;
                    slot->hasGround = true;
                    slot->serial = ++g_SpawnSerial;
                    const float position[3] = {world.x, world.y, world.z};
                    const float quat[4] = {orientation.w, orientation.x, orientation.y, orientation.z};
                    const float scale[3] = {slot->scale.x, slot->scale.y, slot->scale.z};
                    if (!SetShimOwnedObjectTransform(slot->node, slot->entity, position, quat, scale))
                    {
                        // The objects faulted: never touch them again.
                        *slot = GibSlot{};
                        ++failed;
                        continue;
                    }
                    slot->active = true;
                    ++g_ActiveCount;
                    ++spawned;
                    if (g_Config.trace)
                    {
                        LogChunkDiagnostic(
                            "skinnedgibs",
                            L"[SKINNEDGIBS]   gib mesh=%hs bone=%hs pos=(%.2f, %.2f, %.2f) vel=(%.2f, %.2f, %.2f) r=%.3f\n",
                            piece.resource.c_str(), bone.name, static_cast<double>(world.x),
                            static_cast<double>(world.y), static_cast<double>(world.z),
                            static_cast<double>(slot->velocity.x), static_cast<double>(slot->velocity.y),
                            static_cast<double>(slot->velocity.z), static_cast<double>(radius));
                    }
                }
                if (AcquireGibLogSlot())
                {
                    LogChunkDiagnostic(
                        "skinnedgibs",
                        L"[SKINNEDGIBS] person mesh=%hs %hs spawned=%zu failed=%zu bones=%u active=%zu pool=%zu at (%.1f, %.1f, %.1f)\n",
                        capture.meshName, capture.model.authored ? "authored" : "runtime", spawned, failed,
                        static_cast<unsigned>(capture.boneCount), g_ActiveCount, g_Slots.size(),
                        static_cast<double>(origin.x), static_cast<double>(origin.y), static_cast<double>(origin.z));
                }
                return spawned;
            }

            // ---- Simulation ---------------------------------------------------
            // Returns false when the gib is finished and should be released.
            bool StepGib(GibSlot& slot, float dt, FnTerrainHeightAt terrain)
            {
                slot.age += dt;
                if (slot.age >= kTuning.maxLifetime + kTuning.sinkSeconds)
                    return false;

                if (slot.sinking)
                {
                    slot.sinkElapsed += dt;
                    slot.position.y -= kTuning.sinkDepth / kTuning.sinkSeconds * dt;
                    return slot.sinkElapsed < kTuning.sinkSeconds;
                }
                if (slot.settled)
                {
                    slot.settledAge += dt;
                    if (slot.settledAge >= g_Config.linger || slot.age >= kTuning.maxLifetime - kTuning.sinkSeconds)
                        slot.sinking = true;
                    return true;
                }
                if (slot.age >= kTuning.maxLifetime)
                    return false; // still airborne (no ground below): just retire

                slot.velocity.y -= kTuning.gravity * dt;
                slot.position = Add(slot.position, Scale(slot.velocity, dt));
                const Quat spin = {0, slot.omega.x, slot.omega.y, slot.omega.z};
                const Quat delta = QMul(spin, slot.orientation);
                slot.orientation = QNormalize({slot.orientation.w + 0.5f * dt * delta.w,
                                               slot.orientation.x + 0.5f * dt * delta.x,
                                               slot.orientation.y + 0.5f * dt * delta.y,
                                               slot.orientation.z + 0.5f * dt * delta.z});

                float ground = 0.0f;
                if (!slot.hasGround || !TerrainHeightSafe(terrain, slot.position.x, slot.position.z, ground))
                {
                    // No terrain: the ground is -infinity; fall, then expire.
                    slot.hasGround = false;
                    return Finite(slot.position);
                }
                const float lift = slot.radius * kTuning.contactRadius;
                if (slot.position.y - lift < ground)
                {
                    slot.position.y = ground + lift;
                    const Vec3 normal = GroundNormal(terrain, slot.position.x, slot.position.z);
                    const float normalSpeed = Dot(slot.velocity, normal);
                    if (normalSpeed < 0.0f)
                    {
                        const Vec3 normalPart = Scale(normal, normalSpeed);
                        const Vec3 tangentPart = Sub(slot.velocity, normalPart);
                        slot.velocity = Sub(Scale(tangentPart, 1.0f - kTuning.friction),
                                            Scale(normalPart, kTuning.restitution));
                        slot.omega = Scale(slot.omega, kTuning.spinDamp);
                        if (!slot.impacted)
                        {
                            slot.impacted = true;
                            OnGibFirstImpact(slot.position);
                        }
                        if (Length(slot.velocity) < kTuning.settleSpeed)
                        {
                            slot.settled = true;
                            slot.velocity = {};
                            slot.omega = {};
                        }
                    }
                }
                return Finite(slot.position);
            }

            // Drops entries whose chunk has retired, or whose address now holds
            // a different geometry (the object pool recycled it), so a later
            // vehicle chunk at the same address is never withheld.
            void PruneSuppressed(void* chunkEffect)
            {
                if (g_Suppressed.empty() || !chunkEffect)
                    return;
                const auto* bytes = reinterpret_cast<const uint8_t*>(chunkEffect);
                uint32_t count = 0;
                if (!TryReadChunkEffectCount(bytes, count) || count > 0x400)
                    return;
                static std::vector<const uint8_t*> live;
                live.clear();
                for (uint32_t index = 0; index < count; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (TryReadChunkEffectEntry(bytes, index, entry) && entry.objectBytes)
                        live.push_back(entry.objectBytes);
                }
                std::sort(live.begin(), live.end());
                g_Suppressed.erase(
                    std::remove_if(g_Suppressed.begin(), g_Suppressed.end(),
                                   [&](const SuppressedChunk& chunk) {
                                       if (!std::binary_search(live.begin(), live.end(), chunk.object))
                                           return true;
                                       const void* geom = nullptr;
                                       return !TryReadChunkGeomIdentity(chunk.object, geom, nullptr, 0) ||
                                              geom != chunk.geom;
                                   }),
                    g_Suppressed.end());
            }
        } // namespace

        bool IsSkinnedGibsEnabled()
        {
            InitializeConfig();
            return g_Config.enabled;
        }

        bool IsSkinnedGibSuppressedChunk(const uint8_t* objectBytes, const void* geomRef)
        {
            if (!objectBytes || g_Suppressed.empty())
                return false;
            for (const SuppressedChunk& chunk : g_Suppressed)
                if (chunk.object == objectBytes && chunk.geom == geomRef)
                    return true;
            return false;
        }

        bool SkinnedGibsBeginFullFragment(void* chunkEffect, void* obj76, const float* velocity)
        {
            g_Capture.active = false;
            if (!obj76 || !chunkEffect || !IsSkinnedGibsEnabled())
                return false;

            // Persons only, and only their whole body: the root handed to
            // FullFragmentObject must be the person's own object tree.
            void* gameObject = nullptr;
            if (!TryGetGameObjectFromObj76(obj76, gameObject) || !gameObject)
                return false;
            char className[64] = {};
            if (std::strcmp(TryGetRttiClassName(gameObject, className, sizeof(className)), kPersonRtti) != 0)
                return false;
            void* liveObj76 = nullptr;
            if (!TryGetGameObjectObj76(gameObject, liveObj76) || liveObj76 != obj76)
                return false;

            const OgreDeathApi& api = GetDeathApi();
            void* bridge = nullptr;
            void* entity = nullptr;
            if (!api.usable || !ReadPointerSafe(gameObject, kGameObjectRenderBridgeOffset, bridge) ||
                !ReadPointerSafe(bridge, kRenderBridgeWorldEntityOffset, entity) || !LooksLikeOgreObject(entity))
            {
                return false;
            }

            DeathCapture& capture = g_Capture;
            capture.entity = entity;
            capture.chunkEffect = chunkEffect;
            if (!TryCaptureEntityMeshIdentity(entity, capture.meshName, sizeof(capture.meshName), capture.group,
                                              sizeof(capture.group)))
            {
                return false;
            }

            void* node = ParentSceneNodeSafe(api, entity);
            if (!LooksLikeOgreObject(node))
            {
                node = nullptr;
                ReadPointerSafe(bridge, kRenderBridgeWorldNodeOffset, node);
            }
            if (!LooksLikeOgreObject(node) || !CaptureNodeSafe(api, node, capture))
                return false;

            void* skeleton = nullptr;
            uint16_t boneCount = 0;
            if (!CaptureSkeletonSafe(api, entity, skeleton, boneCount))
                return false;
            capture.boneCount = std::min<uint16_t>(boneCount, kMaxCapturedBones);
            uint16_t valid = 0;
            for (uint16_t index = 0; index < capture.boneCount; ++index)
                if (CaptureBoneSafe(api, skeleton, index, capture.bones[index]))
                    ++valid;
            if (!valid)
                return false;
            ReadVelocitySafe(velocity, capture.velocity);

            // The split is cached per model; the first death of a new model
            // pays for it here, once.
            if (!PrepareSkinnedGibPayloads(capture.meshName, capture.group, capture.model) ||
                capture.model.pieces.empty())
            {
                return false;
            }

            capture.chunkCountBefore = 0;
            TryReadChunkEffectCount(reinterpret_cast<const uint8_t*>(chunkEffect), capture.chunkCountBefore);
            capture.active = true;
            return true;
        }

        void SkinnedGibsEndFullFragment(void* chunkEffect)
        {
            DeathCapture& capture = g_Capture;
            if (!capture.active || chunkEffect != capture.chunkEffect)
            {
                capture.active = false;
                return;
            }
            capture.active = false;

            const size_t spawned = SpawnFromCapture();
            if (!spawned)
                return;

            // The legacy chunks this call created for the body keep running in
            // the engine; only their proxy rendering is withheld.
            const auto* bytes = reinterpret_cast<const uint8_t*>(chunkEffect);
            uint32_t countAfter = capture.chunkCountBefore;
            size_t suppressed = 0;
            if (TryReadChunkEffectCount(bytes, countAfter) && countAfter > capture.chunkCountBefore &&
                countAfter <= 0x400)
            {
                for (uint32_t index = capture.chunkCountBefore; index < countAfter; ++index)
                {
                    ChunkEffectActiveEntry entry = {};
                    if (!TryReadChunkEffectEntry(bytes, index, entry) || !entry.objectBytes)
                        continue;
                    const void* geom = nullptr;
                    TryReadChunkGeomIdentity(entry.objectBytes, geom, nullptr, 0);
                    if (g_Suppressed.size() < kMaxSuppressedChunks)
                    {
                        g_Suppressed.push_back({entry.objectBytes, geom});
                        ++suppressed;
                    }
                }
            }
            HideEntitySafe(GetDeathApi(), capture.entity);
            capture.entity = nullptr;
            if (g_Config.trace)
            {
                LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS]   body hidden, %zu legacy chunk(s) left undrawn\n",
                                   suppressed);
            }
        }

        void TickSkinnedGibs(void* chunkEffect, float dt)
        {
            if (!IsSkinnedGibsEnabled())
                return;
            PruneSuppressed(chunkEffect);
            if (!g_ActiveCount)
                return;
            if (IsPauseMenuOpen())
                return;
            if (!std::isfinite(dt))
                return;
            dt = std::clamp(dt, 0.0f, kTuning.maxStep);
            if (dt <= 0.0f)
                return;

            void* const sceneManager = GetOgreSceneManagerRuntime();
            const FnTerrainHeightAt terrain = ResolveTerrainHeight();
            for (GibSlot& slot : g_Slots)
            {
                if (!slot.active)
                    continue;
                if (!SceneMatches(slot, sceneManager))
                {
                    ForgetSlot(slot);
                    continue;
                }
                const bool wasResting = slot.settled && !slot.sinking;
                if (!StepGib(slot, dt, terrain))
                {
                    ReleaseSlot(slot);
                    continue;
                }
                if (wasResting && slot.settled && !slot.sinking)
                    continue; // nothing moved
                const float position[3] = {slot.position.x, slot.position.y, slot.position.z};
                const float quat[4] = {slot.orientation.w, slot.orientation.x, slot.orientation.y, slot.orientation.z};
                if (!SetShimOwnedObjectTransform(slot.node, slot.entity, position, quat, nullptr))
                    ForgetSlot(slot);
            }
        }

        namespace
        {
            // ---- Render probe (TraceSkinnedGibs only) -------------------------
            // Once a second, report what Ogre itself thinks of one live gib:
            // visibility, scene membership, queue group, and per sub-entity
            // whether its material has a technique for the active scheme. Read
            // only; every call is SEH-guarded.
            struct GibProbeApi
            {
                bool(__thiscall* isVisible)(void*) = nullptr;
                bool(__thiscall* isInScene)(void*) = nullptr;
                uint8_t(__thiscall* queueGroup)(void*) = nullptr;
                uint32_t(__thiscall* visibilityFlags)(void*) = nullptr;
                void*(__thiscall* parentNode)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedPosition)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedScale)(void*) = nullptr;
                unsigned(__thiscall* numSubEntities)(void*) = nullptr;
                void*(__thiscall* subEntity)(void*, unsigned) = nullptr;
                bool(__thiscall* subVisible)(void*) = nullptr;
                const std::string*(__thiscall* subMaterialName)(void*) = nullptr;
                void* const*(__thiscall* subMaterial)(void*) = nullptr; // SharedPtr: rep first
                bool(__thiscall* resourceLoaded)(void*) = nullptr;
                void*(__thiscall* bestTechnique)(void*, unsigned short, const void*) = nullptr;
            };

            const GibProbeApi& GetGibProbeApi()
            {
                static GibProbeApi api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.isVisible = ResolveOgreProc<decltype(api.isVisible)>("?isVisible@MovableObject@Ogre@@UBE_NXZ");
                api.isInScene = ResolveOgreProc<decltype(api.isInScene)>("?isInScene@MovableObject@Ogre@@UBE_NXZ");
                api.queueGroup =
                    ResolveOgreProc<decltype(api.queueGroup)>("?getRenderQueueGroup@MovableObject@Ogre@@UBEEXZ");
                api.visibilityFlags =
                    ResolveOgreProc<decltype(api.visibilityFlags)>("?getVisibilityFlags@MovableObject@Ogre@@UBEIXZ");
                api.parentNode = ResolveOgreProc<decltype(api.parentNode)>(
                    "?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ");
                api.derivedPosition =
                    ResolveOgreProc<decltype(api.derivedPosition)>("?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ");
                api.derivedScale =
                    ResolveOgreProc<decltype(api.derivedScale)>("?_getDerivedScale@Node@Ogre@@UBEABVVector3@2@XZ");
                api.numSubEntities =
                    ResolveOgreProc<decltype(api.numSubEntities)>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
                api.subEntity =
                    ResolveOgreProc<decltype(api.subEntity)>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
                api.subVisible = ResolveOgreProc<decltype(api.subVisible)>("?isVisible@SubEntity@Ogre@@UBE_NXZ");
                api.subMaterialName = ResolveOgreProc<decltype(api.subMaterialName)>(
                    "?getMaterialName@SubEntity@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                api.subMaterial = ResolveOgreProc<decltype(api.subMaterial)>(
                    "?getMaterial@SubEntity@Ogre@@UBEABV?$SharedPtr@VMaterial@Ogre@@@2@XZ");
                api.resourceLoaded = ResolveOgreProc<decltype(api.resourceLoaded)>("?isLoaded@Resource@Ogre@@UBE_NXZ");
                api.bestTechnique = ResolveOgreProc<decltype(api.bestTechnique)>(
                    "?getBestTechnique@Material@Ogre@@QAEPAVTechnique@2@GPBVRenderable@2@@Z");
                return api;
            }

            struct GibProbeSub
            {
                char material[64] = {};
                int visible = -1;
                int hasMaterial = -1;
                int loaded = -1;
                int hasTechnique = -1;
            };

            struct GibProbeResult
            {
                int visible = -1;
                int inScene = -1;
                int queueGroup = -1;
                uint32_t flags = 0;
                int hasNode = -1;
                float position[3] = {};
                float scale[3] = {};
                unsigned subCount = 0;
                GibProbeSub subs[4];
                bool faulted = false;
            };

            void ProbeGibEntitySeh(void* entity, const GibProbeApi& api, GibProbeResult& out)
            {
                __try
                {
                    if (api.isVisible)
                        out.visible = api.isVisible(entity) ? 1 : 0;
                    if (api.isInScene)
                        out.inScene = api.isInScene(entity) ? 1 : 0;
                    if (api.queueGroup)
                        out.queueGroup = api.queueGroup(entity);
                    if (api.visibilityFlags)
                        out.flags = api.visibilityFlags(entity);
                    void* node = api.parentNode ? api.parentNode(entity) : nullptr;
                    out.hasNode = node ? 1 : 0;
                    if (node && api.derivedPosition)
                    {
                        const OgreVector3* p = api.derivedPosition(node);
                        out.position[0] = p->x;
                        out.position[1] = p->y;
                        out.position[2] = p->z;
                    }
                    if (node && api.derivedScale)
                    {
                        const OgreVector3* v = api.derivedScale(node);
                        out.scale[0] = v->x;
                        out.scale[1] = v->y;
                        out.scale[2] = v->z;
                    }
                    if (!api.numSubEntities || !api.subEntity)
                        return;
                    out.subCount = api.numSubEntities(entity);
                    for (unsigned i = 0; i < out.subCount && i < 4; ++i)
                    {
                        void* sub = api.subEntity(entity, i);
                        GibProbeSub& r = out.subs[i];
                        if (!sub)
                            continue;
                        if (api.subVisible)
                            r.visible = api.subVisible(sub) ? 1 : 0;
                        if (api.subMaterialName)
                            strncpy_s(r.material, api.subMaterialName(sub)->c_str(), _TRUNCATE);
                        void* material = nullptr;
                        if (api.subMaterial)
                        {
                            void* const* ptr = api.subMaterial(sub);
                            material = ptr ? *ptr : nullptr;
                            r.hasMaterial = material ? 1 : 0;
                        }
                        if (material && api.resourceLoaded)
                            r.loaded = api.resourceLoaded(material) ? 1 : 0;
                        if (material && api.bestTechnique)
                            r.hasTechnique = api.bestTechnique(material, 0, sub) ? 1 : 0;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out.faulted = true;
                }
            }

            uint32_t g_LastProbeTick = 0;
            uint32_t g_SubmitCalls = 0;
            uint32_t g_SubmitEntities = 0;

            void MaybeProbeGibRendering(const GibSlot& slot)
            {
                const uint32_t now = GetTickCount();
                if (now - g_LastProbeTick < 1000)
                    return;
                g_LastProbeTick = now;
                GibProbeResult r;
                ProbeGibEntitySeh(slot.entity, GetGibProbeApi(), r);
                LogChunkDiagnostic(
                    "skinnedgibs",
                    L"[SKINNEDGIBS] probe mesh=%hs visible=%d inScene=%d group=%d flags=0x%08X node=%d "
                    L"nodePos=(%.2f, %.2f, %.2f) nodeScale=(%.2f, %.2f, %.2f) subs=%u submits/s=%u entities/s=%u fault=%u\n",
                    slot.mesh.c_str(), r.visible, r.inScene, r.queueGroup, r.flags, r.hasNode,
                    static_cast<double>(r.position[0]), static_cast<double>(r.position[1]),
                    static_cast<double>(r.position[2]), static_cast<double>(r.scale[0]),
                    static_cast<double>(r.scale[1]), static_cast<double>(r.scale[2]), r.subCount, g_SubmitCalls,
                    g_SubmitEntities, r.faulted ? 1u : 0u);
                for (unsigned i = 0; i < r.subCount && i < 4; ++i)
                {
                    const GibProbeSub& sub = r.subs[i];
                    LogChunkDiagnostic("skinnedgibs",
                                       L"[SKINNEDGIBS] probe   sub%u material=%hs visible=%d hasMaterial=%d loaded=%d "
                                       L"bestTechnique=%d\n",
                                       i, sub.material, sub.visible, sub.hasMaterial, sub.loaded, sub.hasTechnique);
                }
                g_SubmitCalls = 0;
                g_SubmitEntities = 0;
            }
        }

        void SubmitSkinnedGibsToRenderQueue(void* renderQueue)
        {
            if (!renderQueue || !IsSkinnedGibsEnabled())
                return;
            if (!g_ResourcePrimeAttempted && !g_IsSteamExe)
            {
                // Register the payload group before the first death so that
                // death does not also pay for resource-group initialisation.
                g_ResourcePrimeAttempted = true;
                const bool ready = EnsureSkinnedGibResourceLocations();
                LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] payload resources ready=%u\n", ready ? 1u : 0u);
            }
            if (!g_ActiveCount)
                return;
            void* const sceneManager = GetOgreSceneManagerRuntime();
            ++g_SubmitCalls;
            bool probed = false;
            for (GibSlot& slot : g_Slots)
            {
                if (!slot.active || !slot.entity || !SceneMatches(slot, sceneManager))
                    continue;
                ++g_SubmitEntities;
                if (g_Config.trace && !probed)
                {
                    probed = true;
                    MaybeProbeGibRendering(slot);
                }
                if (!SubmitShimOwnedEntityToRenderQueue(slot.sceneManager, slot.entity, renderQueue))
                {
                    if (AcquireGibLogSlot())
                    {
                        LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] dropped faulting gib entity=0x%08X mesh=%hs\n",
                                           static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                                           slot.mesh.c_str());
                    }
                    ForgetSlot(slot);
                }
            }
        }

        void ForgetSkinnedGibSceneResources(const wchar_t* reason)
        {
            ForgetAll(reason);
        }

        void DeactivateSkinnedGibs(const wchar_t* reason)
        {
            // Mission left simulation: the scene is still alive, so hide every
            // gib (keeping the objects for reuse, as chunk proxies do) and drop
            // the per-mission payload map and suppression list.
            size_t hidden = 0;
            for (GibSlot& slot : g_Slots)
            {
                if (slot.active)
                {
                    ReleaseSlot(slot);
                    ++hidden;
                }
            }
            g_ActiveCount = 0;
            g_Suppressed.clear();
            g_Capture.active = false;
            g_FailedMeshes.clear();
            ResetSkinnedGibPayloads();
            if (hidden)
            {
                LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] hid %zu gib(s) (%ls)\n", hidden,
                                   reason ? reason : L"unspecified");
            }
        }

        void EnsureSkinnedGibFleshMaterial(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories)
        {
            if (!IsSkinnedGibsEnabled() || cacheRoot.empty())
                return;
            try
            {
                std::error_code ec;
                const auto ours = cacheRoot / kFleshMaterialFile;
                // An asset pack overrides the default by shipping the same
                // material file at the top of any chunk payload directory.
                // Both in the one resource group would be a duplicate
                // definition, so ours steps aside (and is removed if it was
                // written by an earlier run).
                for (const auto& directory : payloadDirectories)
                {
                    if (std::filesystem::equivalent(directory, cacheRoot, ec) && !ec)
                        continue;
                    ec.clear();
                    if (std::filesystem::is_regular_file(directory / kFleshMaterialFile, ec) && !ec)
                    {
                        std::ifstream existing(ours);
                        std::string first;
                        if (existing && std::getline(existing, first) && first.rfind(kFleshMaterialMarker, 0) == 0)
                        {
                            existing.close();
                            std::filesystem::remove(ours, ec);
                        }
                        static bool logged = false;
                        if (!logged)
                        {
                            logged = true;
                            LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] flesh material overridden by %hs\n",
                                               (directory / kFleshMaterialFile).string().c_str());
                        }
                        return;
                    }
                    ec.clear();
                }
                if (std::filesystem::exists(ours, ec))
                    return;
                std::filesystem::create_directories(cacheRoot, ec);
                std::ofstream output(ours, std::ios::binary | std::ios::trunc);
                output << kFleshMaterialMarker << " (generated; do not edit).\n"
                       << "// Override it with an openshim_gib_flesh.material at the top of a chunk payload\n"
                       << "// directory (<mod>/chunkMeshes/ or BZ_ASSETS/common/models/OpenShimChunkPayloads/).\n"
                       << "material openshim_gib_flesh\n"
                       << "{\n"
                       << "    technique\n"
                       << "    {\n"
                       << "        pass\n"
                       << "        {\n"
                       << "            ambient 0.35 0.02 0.02\n"
                       << "            diffuse 0.55 0.04 0.04\n"
                       << "            specular 0.6 0.3 0.3 24\n"
                       << "            cull_hardware none\n"
                       << "        }\n"
                       << "    }\n"
                       << "}\n";
                output.close();
                LogChunkDiagnostic("skinnedgibs", L"[SKINNEDGIBS] wrote default flesh material %hs ok=%u\n",
                                   ours.string().c_str(), output ? 1u : 0u);
            }
            catch (...)
            {
                // Optional: a missing material renders as BaseWhite.
            }
        }
    }
}
