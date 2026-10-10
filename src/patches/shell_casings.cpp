// shell_casings.cpp
// BZR Open Shim - ShellCasings: when a cannon-like weapon fires, a small
// casing is ejected from its breech, tumbles under gravity, clatters off the
// terrain, the firing hull and nearby objects, then lies, lingers and sinks
// away. Purely cosmetic and fully shim-owned: no engine object is created, and
// the stock shot is never altered.
//
// Fire seam: the OrdnanceClass factory call inside Cannon::Simulate (shared by
// the Cannon, Mortar and SniperGun vtables) and MachineGun::Simulate, both
// REL32-redirected through ShellCasingShotBridge (scripts/patches.json "Shell
// Casings ... Shot Call"). The bridge forwards to the factory first and only
// then hands the weapon, the final muzzle matrix and the owner to the observer,
// which copies POD into a small queue. Casings are spawned and stepped from
// ChunkEffect::Simulate's dt and drawn from the world render-queue hook, the
// same seams SkinnedGibs uses.
//
// Coordinates: casings live in Ogre render space. Redux draws around a
// per-map origin with Z mirrored, so the muzzle matrix and shooter velocity
// are converted once per shot, and only terrain samples convert back. Object
// contact uses each nearby GameObject's Ogre entity bounds placed by its scene
// node (an oriented box), found through the engine's collision grid.
//
// [General] ShellCasings = 0 removes the two call patches at startup and
// leaves every entry point below inert.

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "game_state.h"
#include "hook_engine.h"
#include "native_chunk_mesh.h"
#include "shell_casing_physics.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <unordered_map>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error ShellCasings' shot bridge requires MSVC x86
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace SC = ShellCasings;
            using SC::Quat;
            using SC::Vec3;

            // ---- Tuning ------------------------------------------------------
            struct CasingTuning
            {
                // ChunkEffect::Simulate's gravity, and a scaled-down share of
                // the legacy launch noise (CreateChunk: Pseudo_Rand() * 10 per
                // axis) on top of the directed ejection.
                float gravity = 9.8f;
                float legacyNoise = 1.2f;
                // Legacy chunk omega is Pseudo_Rand() * 5 rad/s per axis; a
                // casing also tumbles end over end about the ejection side axis.
                float spin = 5.0f;
                float tumble = 14.0f;
                SC::ContactResponse ground = {0.35f, 0.35f, 0.6f};
                SC::ContactResponse object = {0.3f, 0.25f, 0.7f};
                float settleSpeed = 0.45f;     // below this after a ground bounce: at rest
                float restingSpeed = 0.25f;    // contact speeds below this are resting contact
                float radiusOfLength = 0.21f;  // body radius as a fraction of length
                float shooterGrace = 0.05f;    // seconds the firing hull is ignored
                float sinkSeconds = 1.5f;
                float maxLifetime = 25.0f;
                float maxStep = 0.05f;
                float spawnCullDistance = 300.0f; // no casing farther than this from the camera
                float objectQueryPadding = 4.0f;
            };
            constexpr CasingTuning kTuning = {};

            constexpr const char* kCasingMeshResource = "casings/v1/openshim_casing.mesh";
            constexpr const char* kCasingMeshRelative = "casings/v1/openshim_casing.mesh";
            constexpr unsigned kCasingSides = 10;
            constexpr const char* kCasingMaterialFile = "openshim_casing.material";
            constexpr const char* kCasingMaterialMarker = "// OpenShim ShellCasings default casing materials";

            // Released-layout contracts (GOG Redux 2.2.301). Weapon: +0x08
            // WeaponClass, +0x0C OrdnanceClass, +0x18 owner OBJ76 (Cannon::
            // Simulate 0x0048EFE0 reads all three around its factory call).
            // WeaponClass ctor 0x00611AA0 copies "<cfg>.odf" to +0x20 (16
            // bytes); OrdnanceClass +0x4C is the ammo cost Simulate subtracts.
            constexpr size_t kWeaponClassOffset = 0x08;
            constexpr size_t kWeaponOrdnanceClassOffset = 0x0C;
            constexpr size_t kWeaponClassOdfOffset = 0x20;
            constexpr size_t kOrdnanceClassAmmoCostOffset = 0x4C;
            constexpr size_t kGameObjectRenderBridgeOffset = 0x0F0;
            constexpr size_t kRenderBridgeWorldEntityOffset = 0x094;
            constexpr size_t kGameObjectFlagsOffset = 0x14; // obj76 flags; 0x200 = dead
            constexpr uint32_t kObj76DeadFlag = 0x200;

            constexpr size_t kMaxPendingShots = 64;
            constexpr size_t kMaxNearbyObjects = 24;

            // ---- Config ------------------------------------------------------
            struct CasingConfig
            {
                bool initialized = false;
                bool enabled = true;
                bool trace = false;
                size_t maxCasings = 48;
                float linger = 6.0f;
                SC::ClassFilter filter;
                std::string classes;
            };
            CasingConfig g_Config;

            bool ReadEnvString(const char* name, std::string& out)
            {
                char buffer[512] = {};
                const DWORD length = GetEnvironmentVariableA(name, buffer, static_cast<DWORD>(sizeof(buffer)));
                if (length == 0 || length >= sizeof(buffer))
                    return false;
                out.assign(buffer, length);
                return true;
            }

            bool ReadEnvNumber(const char* name, double& out)
            {
                std::string text;
                if (!ReadEnvString(name, text))
                    return false;
                char* end = nullptr;
                const double value = std::strtod(text.c_str(), &end);
                while (end && (*end == ' ' || *end == '\t'))
                    ++end;
                if (!end || end == text.c_str() || *end || !std::isfinite(value))
                    return false;
                out = value;
                return true;
            }

            void InitializeConfig()
            {
                if (g_Config.initialized)
                    return;
                g_Config.initialized = true;
                // [General] ShellCasings (default ON) arrives inverted through
                // the env mapping, like SkinnedGibs.
                g_Config.enabled = !EnvFlagEnabled("OPENSHIM_DISABLE_SHELL_CASINGS") &&
                                   !EnvFlagEnabled("BZR_DISABLE_SHELL_CASINGS");
                g_Config.trace = EnvFlagEnabled("OPENSHIM_TRACE_SHELL_CASINGS");
                double value = 0.0;
                if (ReadEnvNumber("OPENSHIM_SHELL_CASINGS_MAX", value))
                    g_Config.maxCasings = static_cast<size_t>(std::clamp(value, 4.0, 512.0));
                if (ReadEnvNumber("OPENSHIM_SHELL_CASINGS_LINGER", value))
                    g_Config.linger = static_cast<float>(std::clamp(value, 0.0, 120.0));
                std::string classes;
                if (!ReadEnvString("OPENSHIM_SHELL_CASINGS_CLASSES", classes))
                    classes = SC::DefaultClassList();
                try
                {
                    g_Config.filter = SC::ParseClassFilter(classes);
                    g_Config.classes = classes;
                }
                catch (...)
                {
                    g_Config.filter = {};
                }
                LogChunkDiagnostic(
                    "shellcasings",
                    L"[SHELLCASINGS] config enabled=%u max=%zu linger=%.2f classes=\"%hs\" trace=%u\n",
                    g_Config.enabled ? 1u : 0u, g_Config.maxCasings, static_cast<double>(g_Config.linger),
                    g_Config.classes.c_str(), g_Config.trace ? 1u : 0u);
            }

            volatile LONG g_LogBudget = 64;
            bool AcquireLogSlot()
            {
                return g_Config.trace || InterlockedDecrement(&g_LogBudget) >= 0;
            }

            // Uniform in [-1, 1].
            struct CasingRandom
            {
                uint32_t state = 0x9E3779B9u;
                float Signed()
                {
                    state = state * 1664525u + 1013904223u;
                    return static_cast<float>(state >> 8) * (2.0f / 16777216.0f) - 1.0f;
                }
            };
            CasingRandom g_Random;

            // ---- Render origin (sim <-> render) ------------------------------
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

            // ---- Shot capture (engine thread, inside Weapon::Simulate) -------
            struct PendingShot
            {
                LegacyMat3 matrix;
                Vec3 shooterVelocity; // sim space
                int shooterHandle;
                SC::WeaponKind kind;
                int ammoCost;
                char odf[20];
            };
            std::array<PendingShot, kMaxPendingShots> g_Pending;
            size_t g_PendingCount = 0;
            uint32_t g_DroppedShots = 0;

            struct KindCacheEntry
            {
                const void* vtable;
                SC::WeaponKind kind;
            };
            std::array<KindCacheEntry, 16> g_KindCache = {};

            bool ReadWeaponFieldsSeh(void* weapon, const void*& vtable, void*& weaponClass, char (&odf)[20],
                                     int& ammoCost)
            {
                vtable = nullptr;
                weaponClass = nullptr;
                odf[0] = '\0';
                ammoCost = 0;
                __try
                {
                    const uint8_t* bytes = static_cast<const uint8_t*>(weapon);
                    vtable = *reinterpret_cast<const void* const*>(bytes);
                    weaponClass = *reinterpret_cast<void* const*>(bytes + kWeaponClassOffset);
                    const void* ordnanceClass = *reinterpret_cast<const void* const*>(bytes + kWeaponOrdnanceClassOffset);
                    if (weaponClass)
                    {
                        const char* name = static_cast<const char*>(weaponClass) + kWeaponClassOdfOffset;
                        size_t i = 0;
                        for (; i < 16 && name[i] >= 0x20 && name[i] < 0x7F; ++i)
                            odf[i] = name[i];
                        odf[i] = '\0';
                    }
                    if (ordnanceClass)
                        ammoCost = *reinterpret_cast<const int*>(static_cast<const uint8_t*>(ordnanceClass) +
                                                                kOrdnanceClassAmmoCostOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return vtable != nullptr;
            }

            bool CopyMatrixSeh(const void* matrix, LegacyMat3& out)
            {
                __try
                {
                    std::memcpy(&out, matrix, sizeof(out));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out.posit_x) && std::isfinite(out.posit_y) && std::isfinite(out.posit_z) &&
                       std::isfinite(out.front_x) && std::isfinite(out.front_y) && std::isfinite(out.front_z);
            }

            bool ReadVec3Seh(const void* base, size_t offset, Vec3& out)
            {
                __try
                {
                    const float* v = reinterpret_cast<const float*>(static_cast<const uint8_t*>(base) + offset);
                    out = {v[0], v[1], v[2]};
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out = {0, 0, 0};
                    return false;
                }
                if (!SC::Finite(out) || SC::Length(out) > 500.0f)
                {
                    out = {0, 0, 0};
                    return false;
                }
                return true;
            }

            SC::WeaponKind KindForVtable(const void* weapon, const void* vtable)
            {
                for (const KindCacheEntry& entry : g_KindCache)
                    if (entry.vtable == vtable)
                        return entry.kind;
                char name[64] = {};
                const SC::WeaponKind kind = SC::WeaponKindFromRtti(TryGetRttiClassName(weapon, name, sizeof(name)));
                for (KindCacheEntry& entry : g_KindCache)
                    if (!entry.vtable)
                    {
                        entry = {vtable, kind};
                        break;
                    }
                return kind;
            }

            // ---- Ogre access ---------------------------------------------------
            struct OgreCasingApi
            {
                const void*(__thiscall* entityBounds)(void*) = nullptr;
                void*(__thiscall* parentSceneNode)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedPosition)(void*) = nullptr;
                const OgreQuaternion*(__thiscall* derivedOrientation)(void*) = nullptr;
                const OgreVector3*(__thiscall* derivedScale)(void*) = nullptr;
                void*(__thiscall* currentViewport)(void*) = nullptr;
                void*(__thiscall* viewportCamera)(void*) = nullptr;
                const OgreVector3*(__thiscall* cameraDerivedPosition)(void*) = nullptr;
                void*(__cdecl* resourceGroupManager)() = nullptr;
                bool(__thiscall* resourceExistsInAnyGroup)(void*, const std::string&) = nullptr;
                bool objects = false;
                bool camera = false;
            };

            const OgreCasingApi& GetOgreApi()
            {
                static OgreCasingApi api;
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
                api.currentViewport = ResolveOgreProc<decltype(api.currentViewport)>(
                    "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
                api.viewportCamera =
                    ResolveOgreProc<decltype(api.viewportCamera)>("?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ");
                api.cameraDerivedPosition = ResolveOgreProc<decltype(api.cameraDerivedPosition)>(
                    "?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ");
                api.resourceGroupManager = ResolveOgreProc<decltype(api.resourceGroupManager)>(
                    "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
                api.resourceExistsInAnyGroup = ResolveOgreProc<decltype(api.resourceExistsInAnyGroup)>(
                    "?resourceExistsInAnyGroup@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                api.objects = api.entityBounds && api.parentSceneNode && api.derivedPosition &&
                              api.derivedOrientation && api.derivedScale;
                api.camera = api.currentViewport && api.viewportCamera && api.cameraDerivedPosition;
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

            bool ReadEntityObbSeh(const OgreCasingApi& api, void* entity, SC::Obb& out)
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
                return SC::Finite(out.center) && SC::Finite(out.half) && out.half.x < 500.0f && out.half.y < 500.0f &&
                       out.half.z < 500.0f;
            }

            bool ReadCameraPositionSeh(const OgreCasingApi& api, void* sceneManager, Vec3& out)
            {
                __try
                {
                    void* viewport = api.currentViewport(sceneManager);
                    void* camera = viewport ? api.viewportCamera(viewport) : nullptr;
                    const OgreVector3* p = camera ? api.cameraDerivedPosition(camera) : nullptr;
                    if (!p)
                        return false;
                    out = {p->x, p->y, p->z};
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return SC::Finite(out);
            }

            bool ResourceExistsSeh(const OgreCasingApi& api, void* manager, const std::string& name, bool& exists)
            {
                __try
                {
                    exists = api.resourceExistsInAnyGroup(manager, name);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return true;
            }

            void* ResourceGroupManagerSeh(const OgreCasingApi& api)
            {
                __try
                {
                    return api.resourceGroupManager();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            Vec3 g_CameraRender = {0, 0, 0};
            bool g_HaveCamera = false;

            // ---- Mesh choice ---------------------------------------------------
            // "<weapon>_casing.mesh" in any resource group overrides the
            // generated shell for that weapon. Checked once per weapon name.
            std::unordered_map<std::string, std::string> g_MeshForWeapon;
            std::vector<std::string> g_FailedMeshes;

            const std::string& MeshForWeapon(const char* odf)
            {
                static const std::string generated = kCasingMeshResource;
                std::string base = SC::NormalizeToken(odf ? odf : "");
                if (base.empty())
                    return generated;
                auto found = g_MeshForWeapon.find(base);
                if (found != g_MeshForWeapon.end())
                    return found->second;
                std::string chosen = generated;
                const OgreCasingApi& api = GetOgreApi();
                if (api.resourceGroupManager && api.resourceExistsInAnyGroup)
                {
                    void* manager = ResourceGroupManagerSeh(api);
                    bool exists = false;
                    const std::string candidate = base + "_casing.mesh";
                    if (manager && ResourceExistsSeh(api, manager, candidate, exists) && exists)
                        chosen = candidate;
                }
                if (AcquireLogSlot())
                {
                    LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] weapon=%hs mesh=%hs\n", base.c_str(),
                                       chosen.c_str());
                }
                if (g_MeshForWeapon.size() > 512)
                    g_MeshForWeapon.clear();
                return g_MeshForWeapon.emplace(std::move(base), std::move(chosen)).first->second;
            }

            // ---- Pool ------------------------------------------------------------
            struct CasingSlot
            {
                void* sceneManager = nullptr;
                void* node = nullptr;
                void* entity = nullptr;
                std::string mesh;
                bool active = false;
                bool settled = false;
                bool sinking = false;
                bool hasGround = true;
                bool clearOfShooter = false;
                Vec3 position = {0, 0, 0};
                Vec3 velocity = {0, 0, 0};
                Vec3 omega = {0, 0, 0};
                Quat orientation = {1, 0, 0, 0};
                float length = 0.25f;
                float radius = 0.05f; // collision sphere
                float lift = 0.05f;   // centre height when lying on the ground
                float age = 0.0f;
                float settledAge = 0.0f;
                float sinkElapsed = 0.0f;
                int shooterHandle = 0;
                uint32_t bounces = 0;
                uint64_t serial = 0;
            };
            std::vector<CasingSlot> g_Slots;
            size_t g_ActiveCount = 0;
            uint64_t g_SpawnSerial = 0;
            bool g_ResourcePrimeAttempted = false;

            // Trace counters, reported once a second.
            uint32_t g_StatSpawned = 0;
            uint32_t g_StatFiltered = 0;
            uint32_t g_StatCulled = 0;
            uint32_t g_StatGroundHits = 0;
            uint32_t g_StatObjectHits = 0;
            uint32_t g_StatSubmits = 0;
            uint32_t g_StatLastTick = 0;

            bool SceneMatches(const CasingSlot& slot, void* sceneManager)
            {
                return slot.sceneManager && slot.sceneManager == sceneManager;
            }

            void ForgetSlot(CasingSlot& slot)
            {
                if (slot.active && g_ActiveCount)
                    --g_ActiveCount;
                slot = CasingSlot{};
            }

            void ReleaseSlot(CasingSlot& slot)
            {
                if (slot.active && g_ActiveCount)
                    --g_ActiveCount;
                slot.active = false;
                HideShimOwnedObject(slot.node, slot.entity);
            }

            void ForgetAll(const wchar_t* reason)
            {
                size_t forgotten = 0;
                for (const CasingSlot& slot : g_Slots)
                    if (slot.node || slot.entity)
                        ++forgotten;
                g_Slots.clear();
                g_ActiveCount = 0;
                g_PendingCount = 0;
                if (forgotten)
                {
                    LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] forgot %zu casing object(s) (%ls)\n", forgotten,
                                       reason ? reason : L"unspecified");
                }
            }

            CasingSlot* AcquireSlot(const std::string& mesh, void* sceneManager)
            {
                const size_t limit = std::max<size_t>(g_Config.maxCasings, 1);
                CasingSlot* sameMesh = nullptr;
                CasingSlot* anyFree = nullptr;
                for (CasingSlot& slot : g_Slots)
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
                // Full: recycle the oldest casing already at rest (preferring
                // one using the same mesh), else the oldest.
                CasingSlot* oldestSettled = nullptr;
                CasingSlot* oldest = nullptr;
                for (CasingSlot& slot : g_Slots)
                {
                    if (!slot.active)
                        continue;
                    if ((slot.settled || slot.sinking) &&
                        (!oldestSettled || slot.serial < oldestSettled->serial))
                        oldestSettled = &slot;
                    if (!oldest || slot.serial < oldest->serial)
                        oldest = &slot;
                }
                CasingSlot* victim = oldestSettled ? oldestSettled : oldest;
                if (victim)
                    ReleaseSlot(*victim);
                return victim;
            }

            bool PrepareSlotEntity(CasingSlot& slot, const std::string& mesh, void* sceneManager)
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
                    slot = CasingSlot{};
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

            void DropFreshSlot(CasingSlot* slot)
            {
                if (!slot || slot->node)
                    return;
                for (auto it = g_Slots.begin(); it != g_Slots.end(); ++it)
                    if (&*it == slot)
                    {
                        g_Slots.erase(it);
                        return;
                    }
            }

            // ---- Terrain -----------------------------------------------------------
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
                        LogChunkDiagnostic("shellcasings",
                            L"[SHELLCASINGS] Terrain::HeightAt unresolved; casings fall without ground contact\n");
                    }
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

            // Render-space ground height under a render-space point.
            struct TerrainView
            {
                FnTerrainHeightAt fn = nullptr;
                Vec3 origin = {0, 0, 0};
                bool usable = false;

                bool HeightAt(float x, float z, float& out) const
                {
                    if (!usable)
                        return false;
                    const Vec3 sim = SC::RenderToSimPoint({x, 0.0f, z}, origin);
                    double height = 0.0;
                    if (!TerrainHeightSimSeh(fn, sim.x, sim.z, height))
                        return false;
                    out = static_cast<float>(height) - origin.y;
                    return true;
                }

                Vec3 NormalAt(float x, float z) const
                {
                    constexpr float kStep = 0.25f;
                    float hx0 = 0, hx1 = 0, hz0 = 0, hz1 = 0;
                    if (!HeightAt(x - kStep, z, hx0) || !HeightAt(x + kStep, z, hx1) || !HeightAt(x, z - kStep, hz0) ||
                        !HeightAt(x, z + kStep, hz1))
                    {
                        return {0, 1, 0};
                    }
                    return SC::GroundNormalFromHeights(hx0, hx1, hz0, hz1, kStep);
                }
            };

            // ---- Nearby objects --------------------------------------------------
            struct NearbyObject
            {
                SC::Obb box;
                Vec3 velocity; // render space
                int handle;
            };
            std::vector<NearbyObject> g_Nearby;

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
                LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] object grid usable=%u global=0x%08X query=0x%08X next=0x%08X\n",
                                   api.usable ? 1u : 0u,
                                   static_cast<uint32_t>(reinterpret_cast<uintptr_t>(api.gridGlobal)),
                                   static_cast<uint32_t>(reinterpret_cast<uintptr_t>(api.query)),
                                   static_cast<uint32_t>(reinterpret_cast<uintptr_t>(api.next)));
                return api;
            }

            // The grid's own results record: 44 bytes on the stack in every
            // stock caller (e.g. FUN_00480F40), plain data with no destructor.
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

            // A vtable inside OgreMain, without VirtualQuery: this runs for
            // every nearby object each tick (see the chunk-proxy FPS note in
            // chunk_proxy_render.cpp); the guarded read covers unmapped pages.
            bool LooksLikeOgreObjectInPlace(const void* candidate)
            {
                const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
                if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                    return false;
                uintptr_t ogreBase = 0;
                uintptr_t ogreEnd = 0;
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

            bool ReadObjectRenderEntitySeh(void* gameObject, void*& entity, uint32_t& obj76Flags)
            {
                entity = nullptr;
                obj76Flags = 0;
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
                void* obj76 = nullptr;
                if (TryGetGameObjectObj76(gameObject, obj76) && obj76)
                {
                    __try
                    {
                        obj76Flags = *reinterpret_cast<const uint32_t*>(static_cast<const uint8_t*>(obj76) +
                                                                        kGameObjectFlagsOffset);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        obj76Flags = kObj76DeadFlag;
                    }
                }
                return entity != nullptr;
            }

            void RefreshNearbyObjects(const Vec3& lo, const Vec3& hi, const Vec3& origin)
            {
                g_Nearby.clear();
                const GridApi& grid = GetGridApi();
                const OgreCasingApi& ogre = GetOgreApi();
                if (!grid.usable || !ogre.objects)
                    return;
                // Render AABB -> sim x/z range (z mirrors, so min and max swap).
                const Vec3 a = SC::RenderToSimPoint(lo, origin);
                const Vec3 b = SC::RenderToSimPoint(hi, origin);
                const double pad = kTuning.objectQueryPadding;
                int handles[kMaxNearbyObjects * 2] = {};
                const size_t found = QueryGridSeh(grid, std::min(a.x, b.x) - pad, std::min(a.z, b.z) - pad,
                                                  std::max(a.x, b.x) + pad, std::max(a.z, b.z) + pad, handles,
                                                  kMaxNearbyObjects * 2);
                for (size_t i = 0; i < found && g_Nearby.size() < kMaxNearbyObjects; ++i)
                {
                    void* object = GameObjectFromHandleGog(handles[i]);
                    if (!object)
                        continue;
                    void* entity = nullptr;
                    uint32_t flags = 0;
                    if (!ReadObjectRenderEntitySeh(object, entity, flags) || (flags & kObj76DeadFlag) ||
                        !LooksLikeOgreObjectInPlace(entity))
                        continue;
                    NearbyObject nearby = {};
                    if (!ReadEntityObbSeh(ogre, entity, nearby.box))
                        continue;
                    Vec3 simVelocity = {0, 0, 0};
                    ReadVec3Seh(object, kGameObjectVelocityOffset, simVelocity);
                    nearby.velocity = SC::SimToRenderDir(simVelocity);
                    nearby.handle = handles[i];
                    g_Nearby.push_back(nearby);
                }
            }

            // ---- Spawning ------------------------------------------------------------
            void SpawnShot(const PendingShot& shot, void* sceneManager, const Vec3& origin)
            {
                const LegacyMat3& m = shot.matrix;
                SC::MuzzleFrame frame;
                frame.position = SC::SimToRenderPoint(
                    {static_cast<float>(m.posit_x), static_cast<float>(m.posit_y), static_cast<float>(m.posit_z)},
                    origin);
                frame.right = SC::SimToRenderDir({m.right_x, m.right_y, m.right_z});
                frame.up = SC::SimToRenderDir({m.up_x, m.up_y, m.up_z});
                frame.front = SC::SimToRenderDir({m.front_x, m.front_y, m.front_z});
                if (!SC::Finite(frame.position))
                    return;
                if (g_HaveCamera &&
                    SC::Length(SC::Sub(frame.position, g_CameraRender)) > kTuning.spawnCullDistance)
                {
                    ++g_StatCulled;
                    return;
                }

                const std::string& mesh = MeshForWeapon(shot.odf);
                if (std::find(g_FailedMeshes.begin(), g_FailedMeshes.end(), mesh) != g_FailedMeshes.end())
                    return;
                CasingSlot* slot = AcquireSlot(mesh, sceneManager);
                if (!slot || !PrepareSlotEntity(*slot, mesh, sceneManager))
                {
                    DropFreshSlot(slot);
                    if (g_FailedMeshes.size() < 64)
                        g_FailedMeshes.push_back(mesh);
                    LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] entity creation failed mesh=%hs (not retried)\n",
                                       mesh.c_str());
                    return;
                }

                const SC::KindDefaults defaults = SC::DefaultsFor(shot.kind);
                const float length = SC::CasingLength(shot.kind, shot.ammoCost);
                SC::EjectParams params;
                params.barrelLength = defaults.barrelLength;
                params.speed = defaults.speed;
                params.portUp = 0.5f * length;
                const SC::EjectState eject = SC::ComputeEject(frame, params, SC::SimToRenderDir(shot.shooterVelocity),
                                                              g_Random.Signed(), g_Random.Signed(), g_Random.Signed());
                const Vec3 noise = {g_Random.Signed() * kTuning.legacyNoise, g_Random.Signed() * kTuning.legacyNoise,
                                    g_Random.Signed() * kTuning.legacyNoise};
                // Tumble end over end about the axis across the ejection.
                const Vec3 tumbleAxis = SC::Normalize(SC::Cross(eject.direction, frame.front), frame.up);
                const Vec3 omega = SC::Add(SC::Scale(tumbleAxis, kTuning.tumble * (0.7f + 0.3f * g_Random.Signed())),
                                           {g_Random.Signed() * kTuning.spin, g_Random.Signed() * kTuning.spin,
                                            g_Random.Signed() * kTuning.spin});

                slot->position = eject.position;
                slot->velocity = SC::Add(eject.velocity, noise);
                slot->omega = omega;
                slot->orientation = SC::OrientAlong(frame.front, frame.up);
                slot->length = length;
                slot->radius = std::max(0.02f, length * 0.3f);
                slot->lift = std::max(0.01f, length * kTuning.radiusOfLength);
                slot->age = 0.0f;
                slot->settledAge = 0.0f;
                slot->sinkElapsed = 0.0f;
                slot->settled = false;
                slot->sinking = false;
                slot->hasGround = true;
                slot->clearOfShooter = false;
                slot->bounces = 0;
                slot->shooterHandle = shot.shooterHandle;
                slot->serial = ++g_SpawnSerial;
                const float position[3] = {slot->position.x, slot->position.y, slot->position.z};
                const float quat[4] = {slot->orientation.w, slot->orientation.x, slot->orientation.y,
                                       slot->orientation.z};
                const float scale[3] = {length, length, length};
                if (!SetShimOwnedObjectTransform(slot->node, slot->entity, position, quat, scale))
                {
                    *slot = CasingSlot{};
                    return;
                }
                slot->active = true;
                ++g_ActiveCount;
                ++g_StatSpawned;
                if (g_Config.trace && AcquireLogSlot())
                {
                    LogChunkDiagnostic(
                        "shellcasings",
                        L"[SHELLCASINGS]   spawn weapon=%hs kind=%hs ammoCost=%d len=%.3f mesh=%hs pos=(%.2f, %.2f, %.2f) vel=(%.2f, %.2f, %.2f) shooter=0x%08X active=%zu\n",
                        shot.odf, SC::WeaponKindLabel(shot.kind), shot.ammoCost, static_cast<double>(length),
                        mesh.c_str(), static_cast<double>(slot->position.x), static_cast<double>(slot->position.y),
                        static_cast<double>(slot->position.z), static_cast<double>(slot->velocity.x),
                        static_cast<double>(slot->velocity.y), static_cast<double>(slot->velocity.z),
                        static_cast<uint32_t>(shot.shooterHandle), g_ActiveCount);
                }
            }

            // ---- Simulation -------------------------------------------------------------
            void LieFlat(CasingSlot& slot, Vec3 normal)
            {
                // Keep the casing's heading, laid along the surface.
                const Vec3 axis = SC::Rotate(slot.orientation, {0, 0, 1});
                Vec3 along = SC::Sub(axis, SC::Scale(normal, SC::Dot(axis, normal)));
                along = SC::Normalize(along, SC::Normalize(SC::Cross(normal, {1, 0, 0}), {0, 0, 1}));
                slot.orientation = SC::OrientAlong(along, normal);
            }

            void CollideObjects(CasingSlot& slot)
            {
                for (const NearbyObject& object : g_Nearby)
                {
                    const bool shooter = object.handle != 0 && object.handle == slot.shooterHandle;
                    if (shooter)
                    {
                        // The casing is born inside or against its own hull:
                        // ignore that hull until the grace period is over and
                        // the casing has been outside it once.
                        if (slot.age < kTuning.shooterGrace)
                            continue;
                        if (!slot.clearOfShooter)
                        {
                            if (!SC::PointInsideObb(slot.position, object.box, slot.radius))
                                slot.clearOfShooter = true;
                            continue;
                        }
                    }
                    const SC::Contact contact = SC::SphereVsObb(slot.position, slot.radius, object.box);
                    if (!contact.hit)
                        continue;
                    slot.position = SC::Add(slot.position, SC::Scale(contact.normal, contact.depth));
                    const float impact =
                        SC::Bounce(slot.velocity, slot.omega, contact.normal, object.velocity, kTuning.object);
                    if (impact > 0.0f)
                    {
                        ++slot.bounces;
                        ++g_StatObjectHits;
                        if (impact < kTuning.restingSpeed)
                        {
                            // Resting on the hull: carried along by it, sliding
                            // off only under gravity.
                            const Vec3 relative = SC::Sub(slot.velocity, object.velocity);
                            slot.velocity = SC::Sub(slot.velocity, SC::Scale(contact.normal, SC::Dot(relative, contact.normal)));
                        }
                    }
                }
            }

            // Returns false when the casing is finished and should be released.
            bool StepCasing(CasingSlot& slot, float dt, const TerrainView& terrain)
            {
                slot.age += dt;
                if (slot.age >= kTuning.maxLifetime + kTuning.sinkSeconds)
                    return false;
                if (slot.sinking)
                {
                    slot.sinkElapsed += dt;
                    slot.position.y -= slot.lift * 2.0f / kTuning.sinkSeconds * dt;
                    return slot.sinkElapsed < kTuning.sinkSeconds;
                }
                if (slot.settled)
                {
                    slot.settledAge += dt;
                    if (slot.settledAge >= g_Config.linger || slot.age >= kTuning.maxLifetime)
                        slot.sinking = true;
                    return true;
                }
                if (slot.age >= kTuning.maxLifetime)
                {
                    // Still moving (on a hull, or no ground below): sink in place.
                    slot.sinking = true;
                    return true;
                }

                slot.velocity.y -= kTuning.gravity * dt;
                slot.position = SC::Add(slot.position, SC::Scale(slot.velocity, dt));
                slot.orientation = SC::IntegrateSpin(slot.orientation, slot.omega, dt);
                if (!g_Nearby.empty())
                    CollideObjects(slot);

                float ground = 0.0f;
                if (!slot.hasGround || !terrain.HeightAt(slot.position.x, slot.position.z, ground))
                {
                    slot.hasGround = false;
                    return SC::Finite(slot.position);
                }
                if (slot.position.y - slot.lift < ground)
                {
                    slot.position.y = ground + slot.lift;
                    const Vec3 normal = terrain.NormalAt(slot.position.x, slot.position.z);
                    const float impact = SC::Bounce(slot.velocity, slot.omega, normal, {0, 0, 0}, kTuning.ground);
                    if (impact > 0.0f)
                    {
                        ++slot.bounces;
                        ++g_StatGroundHits;
                        if (SC::Length(slot.velocity) < kTuning.settleSpeed)
                        {
                            slot.settled = true;
                            slot.velocity = {0, 0, 0};
                            slot.omega = {0, 0, 0};
                            LieFlat(slot, normal);
                        }
                    }
                }
                return SC::Finite(slot.position);
            }

            void MaybeLogStats()
            {
                if (!g_Config.trace)
                    return;
                const uint32_t now = GetTickCount();
                if (now - g_StatLastTick < 1000)
                    return;
                g_StatLastTick = now;
                if (!g_StatSpawned && !g_ActiveCount && !g_StatFiltered && !g_StatCulled)
                    return;
                size_t moving = 0;
                for (const CasingSlot& slot : g_Slots)
                    if (slot.active && !slot.settled && !slot.sinking)
                        ++moving;
                LogChunkDiagnostic(
                    "shellcasings",
                    L"[SHELLCASINGS] stats spawned/s=%u filtered/s=%u culled/s=%u dropped=%u active=%zu moving=%zu pool=%zu nearby=%zu groundHits/s=%u objectHits/s=%u submits/s=%u\n",
                    g_StatSpawned, g_StatFiltered, g_StatCulled, g_DroppedShots, g_ActiveCount, moving, g_Slots.size(),
                    g_Nearby.size(), g_StatGroundHits, g_StatObjectHits, g_StatSubmits);
                g_StatSpawned = g_StatFiltered = g_StatCulled = 0;
                g_StatGroundHits = g_StatObjectHits = g_StatSubmits = 0;
            }

            // ---- Shot bridge ----------------------------------------------------------
            void* g_ShellCasingFactory = nullptr;
            void* g_ShellCasingObserver = nullptr;
            volatile LONG g_FirstShotLogged = 0;

            void __cdecl ObserveShellCasingShot(void* weapon, const void* matrix, void* ownerObj76,
                                                void* ordnance) noexcept
            {
                if (!weapon || !matrix || !ordnance || !g_Config.initialized || !g_Config.enabled)
                    return;
                if (g_PendingCount >= g_Pending.size())
                {
                    ++g_DroppedShots;
                    return;
                }
                const void* vtable = nullptr;
                void* weaponClass = nullptr;
                PendingShot& shot = g_Pending[g_PendingCount];
                if (!ReadWeaponFieldsSeh(weapon, vtable, weaponClass, shot.odf, shot.ammoCost))
                    return;
                shot.kind = KindForVtable(weapon, vtable);
                bool allowed = false;
                try
                {
                    allowed = SC::FilterAllows(g_Config.filter, SC::WeaponKindLabel(shot.kind), shot.odf);
                }
                catch (...)
                {
                    allowed = false;
                }
                if (InterlockedExchange(&g_FirstShotLogged, 1) == 0)
                {
                    LogChunkDiagnostic("shellcasings",
                                       L"[SHELLCASINGS] first observed shot weapon=%hs kind=%hs ammoCost=%d allowed=%u\n",
                                       shot.odf, SC::WeaponKindLabel(shot.kind), shot.ammoCost, allowed ? 1u : 0u);
                }
                if (!allowed)
                {
                    ++g_StatFiltered;
                    return;
                }
                if (!CopyMatrixSeh(matrix, shot.matrix))
                    return;
                shot.shooterHandle = 0;
                shot.shooterVelocity = {0, 0, 0};
                void* shooter = nullptr;
                if (ownerObj76 && TryGetGameObjectFromObj76(ownerObj76, shooter) && shooter)
                {
                    TryGetGameObjectHandleValue(shooter, shot.shooterHandle);
                    ReadVec3Seh(shooter, kGameObjectVelocityOffset, shot.shooterVelocity);
                }
                ++g_PendingCount;
            }

            // Replaces the E8 to the OrdnanceClass factory at both shot sites.
            // Both callers keep the weapon (their ECX) at [EBP-250h] and pass
            // the final Matrix* and owner OBJ76 on the stack; the factory is
            // thiscall on the OrdnanceClass in ECX and returns with RET 8.
            // The factory runs first and its EAX is returned untouched.
            __declspec(naked) void ShellCasingShotBridgeImpl()
            {
                __asm
                {
                    push ebp
                    mov ebp, esp
                    push ebx
                    push esi
                    push edi
                    mov esi, dword ptr [ebp]
                    mov esi, dword ptr [esi - 250h]
                    mov edi, dword ptr [ebp + 8]
                    mov ebx, dword ptr [ebp + 0Ch]
                    push ebx
                    push edi
                    call dword ptr [g_ShellCasingFactory]
                    push eax
                    push eax
                    push ebx
                    push edi
                    push esi
                    call dword ptr [g_ShellCasingObserver]
                    add esp, 10h
                    pop eax
                    pop edi
                    pop esi
                    pop ebx
                    mov esp, ebp
                    pop ebp
                    ret 8
                }
            }
        } // namespace

        bool IsShellCasingsEnabled()
        {
            InitializeConfig();
            return g_Config.enabled;
        }

        void SubmitShellCasingsToRenderQueue(void* renderQueue)
        {
            if (!renderQueue || !g_Config.initialized || !g_Config.enabled)
                return;
            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return;
            if (!g_ResourcePrimeAttempted && !g_IsSteamExe)
            {
                g_ResourcePrimeAttempted = true;
                const bool ready = EnsureSkinnedGibResourceLocations();
                LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] casing resources ready=%u\n", ready ? 1u : 0u);
            }
            const OgreCasingApi& api = GetOgreApi();
            Vec3 camera = {0, 0, 0};
            if (api.camera && ReadCameraPositionSeh(api, sceneManager, camera))
            {
                g_CameraRender = camera;
                g_HaveCamera = true;
            }
            if (!g_ActiveCount)
                return;
            for (CasingSlot& slot : g_Slots)
            {
                if (!slot.active || !slot.entity || !SceneMatches(slot, sceneManager))
                    continue;
                ++g_StatSubmits;
                if (!SubmitShimOwnedEntityToRenderQueue(slot.sceneManager, slot.entity, renderQueue))
                {
                    if (AcquireLogSlot())
                    {
                        LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] dropped faulting casing entity=0x%08X mesh=%hs\n",
                                           static_cast<uint32_t>(reinterpret_cast<uintptr_t>(slot.entity)),
                                           slot.mesh.c_str());
                    }
                    ForgetSlot(slot);
                }
            }
        }

        void TickShellCasings(float dt)
        {
            if (!g_Config.initialized || !g_Config.enabled)
                return;
            if (!g_PendingCount && !g_ActiveCount)
            {
                MaybeLogStats();
                return;
            }
            if (IsPauseMenuOpen() || !std::isfinite(dt))
                return;
            void* const sceneManager = GetOgreSceneManagerRuntime();
            Vec3 origin = {0, 0, 0};
            if (!sceneManager || !ReadRenderOrigin(origin))
            {
                g_PendingCount = 0;
                return;
            }
            if (!g_Slots.empty() && g_Slots.front().sceneManager && g_Slots.front().sceneManager != sceneManager)
                ForgetAll(L"scene manager changed");

            try
            {
                for (size_t i = 0; i < g_PendingCount; ++i)
                    SpawnShot(g_Pending[i], sceneManager, origin);
            }
            catch (...)
            {
            }
            g_PendingCount = 0;

            dt = std::clamp(dt, 0.0f, 0.25f);
            if (dt <= 0.0f || !g_ActiveCount)
            {
                MaybeLogStats();
                return;
            }

            TerrainView terrain;
            terrain.fn = ResolveTerrainHeight();
            terrain.origin = origin;
            terrain.usable = terrain.fn != nullptr;

            // One grid query per tick around every moving casing.
            Vec3 lo = {1e30f, 1e30f, 1e30f};
            Vec3 hi = {-1e30f, -1e30f, -1e30f};
            bool anyMoving = false;
            for (const CasingSlot& slot : g_Slots)
            {
                if (!slot.active || slot.settled || slot.sinking || !SceneMatches(slot, sceneManager))
                    continue;
                anyMoving = true;
                lo = {std::min(lo.x, slot.position.x), std::min(lo.y, slot.position.y), std::min(lo.z, slot.position.z)};
                hi = {std::max(hi.x, slot.position.x), std::max(hi.y, slot.position.y), std::max(hi.z, slot.position.z)};
            }
            g_Nearby.clear();
            if (anyMoving && hi.x - lo.x < 400.0f && hi.z - lo.z < 400.0f)
            {
                try
                {
                    RefreshNearbyObjects(lo, hi, origin);
                }
                catch (...)
                {
                    g_Nearby.clear();
                }
            }

            for (CasingSlot& slot : g_Slots)
            {
                if (!slot.active)
                    continue;
                if (!SceneMatches(slot, sceneManager))
                {
                    ForgetSlot(slot);
                    continue;
                }
                const bool wasResting = slot.settled && !slot.sinking;
                bool alive = true;
                // Substeps keep a fast casing from tunnelling through a hull.
                float remaining = dt;
                while (alive && remaining > 0.0f)
                {
                    const float step = std::min(remaining, kTuning.maxStep);
                    alive = StepCasing(slot, step, terrain);
                    remaining -= step;
                    if (slot.settled)
                        break;
                }
                if (!alive)
                {
                    ReleaseSlot(slot);
                    continue;
                }
                if (wasResting && slot.settled && !slot.sinking)
                    continue; // nothing moved
                const float position[3] = {slot.position.x, slot.position.y, slot.position.z};
                const float quat[4] = {slot.orientation.w, slot.orientation.x, slot.orientation.y, slot.orientation.z};
                const float size = slot.length * (slot.sinking ? SC::SinkScale(slot.sinkElapsed, kTuning.sinkSeconds) : 1.0f);
                const float scale[3] = {std::max(size, 1e-4f), std::max(size, 1e-4f), std::max(size, 1e-4f)};
                if (!SetShimOwnedObjectTransform(slot.node, slot.entity, position, quat, slot.sinking ? scale : nullptr))
                    ForgetSlot(slot);
            }
            MaybeLogStats();
        }

        void ForgetShellCasingSceneResources(const wchar_t* reason)
        {
            ForgetAll(reason);
            g_Nearby.clear();
        }

        void DeactivateShellCasings(const wchar_t* reason)
        {
            size_t hidden = 0;
            for (CasingSlot& slot : g_Slots)
            {
                if (slot.active)
                {
                    ReleaseSlot(slot);
                    ++hidden;
                }
            }
            g_ActiveCount = 0;
            g_PendingCount = 0;
            g_Nearby.clear();
            g_FailedMeshes.clear();
            g_MeshForWeapon.clear();
            if (hidden)
            {
                LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] hid %zu casing(s) (%ls)\n", hidden,
                                   reason ? reason : L"unspecified");
            }
        }

        void SetShellCasingFactoryOriginal(void* factory)
        {
            InitializeConfig();
            g_ShellCasingFactory = factory;
            g_ShellCasingObserver = reinterpret_cast<void*>(&ObserveShellCasingShot);
        }

        void* GetShellCasingShotBridgeAddress()
        {
            return reinterpret_cast<void*>(&ShellCasingShotBridgeImpl);
        }

        void EnsureShellCasingAssets(
            const std::filesystem::path& cacheRoot,
            const std::vector<std::filesystem::path>& payloadDirectories)
        {
            if (!IsShellCasingsEnabled() || cacheRoot.empty())
                return;
            try
            {
                std::error_code ec;
                // The generated mesh: rewritten only when its bytes differ.
                const NativeChunks::Piece piece = NativeChunks::CasingMesh(kCasingSides);
                const auto meshPath = cacheRoot / std::filesystem::path(kCasingMeshRelative);
                bool current = false;
                if (std::filesystem::file_size(meshPath, ec) == piece.mesh.size() && !ec)
                {
                    std::ifstream existing(meshPath, std::ios::binary);
                    std::vector<uint8_t> bytes(piece.mesh.size());
                    current = existing.read(reinterpret_cast<char*>(bytes.data()),
                                            static_cast<std::streamsize>(bytes.size())) &&
                              bytes == piece.mesh;
                }
                ec.clear();
                if (!current && !piece.mesh.empty())
                {
                    std::filesystem::create_directories(meshPath.parent_path(), ec);
                    std::ofstream output(meshPath, std::ios::binary | std::ios::trunc);
                    output.write(reinterpret_cast<const char*>(piece.mesh.data()),
                                 static_cast<std::streamsize>(piece.mesh.size()));
                    output.close();
                    LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] wrote casing mesh %hs triangles=%u ok=%u\n",
                                       meshPath.string().c_str(), piece.triangles, output ? 1u : 0u);
                }

                // Materials: an asset pack overrides both by shipping the same
                // file at the top of a chunk payload directory (same rule as
                // the SkinnedGibs flesh material).
                const auto ours = cacheRoot / kCasingMaterialFile;
                for (const auto& directory : payloadDirectories)
                {
                    if (std::filesystem::equivalent(directory, cacheRoot, ec) && !ec)
                        continue;
                    ec.clear();
                    if (std::filesystem::is_regular_file(directory / kCasingMaterialFile, ec) && !ec)
                    {
                        std::ifstream existing(ours);
                        std::string first;
                        if (existing && std::getline(existing, first) && first.rfind(kCasingMaterialMarker, 0) == 0)
                        {
                            existing.close();
                            std::filesystem::remove(ours, ec);
                        }
                        LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] casing materials overridden by %hs\n",
                                           (directory / kCasingMaterialFile).string().c_str());
                        return;
                    }
                    ec.clear();
                }
                if (std::filesystem::exists(ours, ec))
                    return;
                std::filesystem::create_directories(cacheRoot, ec);
                std::ofstream output(ours, std::ios::binary | std::ios::trunc);
                output << kCasingMaterialMarker << " (generated; do not edit).\n"
                       << "// Override it with an openshim_casing.material at the top of a chunk payload\n"
                       << "// directory (<mod>/chunkMeshes/ or BZ_ASSETS/common/models/OpenShimChunkPayloads/).\n"
                       << "material openshim_casing_brass\n"
                       << "{\n"
                       << "    technique\n"
                       << "    {\n"
                       << "        pass\n"
                       << "        {\n"
                       << "            ambient 0.45 0.34 0.12\n"
                       << "            diffuse 0.85 0.64 0.24\n"
                       << "            specular 0.9 0.8 0.5 48\n"
                       << "            normalise_normals on\n"
                       << "        }\n"
                       << "    }\n"
                       << "}\n"
                       << "material openshim_casing_rim\n"
                       << "{\n"
                       << "    technique\n"
                       << "    {\n"
                       << "        pass\n"
                       << "        {\n"
                       << "            ambient 0.2 0.14 0.06\n"
                       << "            diffuse 0.38 0.27 0.11\n"
                       << "            specular 0.4 0.35 0.25 24\n"
                       << "            normalise_normals on\n"
                       << "        }\n"
                       << "    }\n"
                       << "}\n";
                output.close();
                LogChunkDiagnostic("shellcasings", L"[SHELLCASINGS] wrote default casing materials %hs ok=%u\n",
                                   ours.string().c_str(), output ? 1u : 0u);
            }
            catch (...)
            {
                // Optional: a missing material renders as BaseWhite.
            }
        }
    }
}
