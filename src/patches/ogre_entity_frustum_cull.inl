// SPDX-License-Identifier: MIT
//
// Copyright (C) 2026 BZR Open Shim contributors
//
// Craft visibility: restoring finite Ogre bounds, and the superseded private
// frustum test kept beside it as a fallback.
//
// The defect
// ----------
// Battlezone 98 Redux gives craft meshes an infinite Ogre bounding box at
// runtime. Measured, from the opt-in census below:
//
//     type=Ogre::Entity extent=2 meshExtent=2 sampleMesh=avtank.mesh
//
// `extent=2` is `AxisAlignedBox::EXTENT_INFINITE`, and `meshExtent=2` places it
// on `Mesh::getBounds()` itself rather than on an attachment. The shipped asset
// is fine -- `avtank.mesh` declares min=(-3.16,-0.06,-3.74) max=(3.16,2.76,2.96)
// in its M_MESH_BOUNDS chunk -- so something overwrites those bounds after load.
// Terrain entities keep finite bounds (`RenderableTileCluster_*`, extent=1).
//
// That "something" is now known exactly, and the block comment above
// MeshSetBoundsHook carries the full call-site derivation: Redux's first-person
// view entity builder at 0x0067E5A0 writes an unconditional never-cull box onto
// the mesh it is given, and for craft that ship no dedicated cockpit model it is
// given the craft's *own* mesh name. Ogre::Mesh is a shared resource, so a
// cockpit's "always visible" policy lands on the mesh every world instance of
// that craft renders from.
//
// Ogre's frustum test short-circuits on an infinite box ("Infinite boxes always
// visible"), and `SceneNode::_updateBounds` merges object boxes into the node's,
// so an infinitely bounded object also makes its scene node infinite. Both the
// node-level test in `SceneNode::_findVisibleObjects` and any per-object test
// therefore always pass. Redux additionally runs `DefaultSceneManager`, whose
// `RenderQueue::processVisibleObject` performs no frustum test of its own.
//
// Measured consequence, static camera, DX11, 20 tanks, profiler enabled:
//
//     orientation=facing (all 20 in view)   avtank00 high-pssm  20.6 submits/f
//     orientation=away   (all 20 BEHIND)    avtank00 high-pssm  20.6 submits/f
//
// Identical. Every craft in the mission is submitted to the main camera every
// frame no matter where the camera points, and every craft is submitted to every
// PSSM cascade as well.
//
// Two repairs live in this file
// -----------------------------
// 1. RESTORED BOUNDS (`OPENSHIM_RESTORE_CRAFT_BOUNDS=1`) -- the current
//    architecture. `Mesh::_setBounds` substitutes a finite box, derived from the
//    serializer's own M_MESH_BOUNDS box, on exactly the meshes that were handed
//    an infinite one. Ogre's native visibility traversal then works normally.
//    Nothing else is patched: with this path alone, `processVisibleObject` and
//    `Entity::_updateRenderQueue` keep their stock instruction stream.
//
// 2. PRIVATE FRUSTUM CULL (on by default, `OPENSHIM_DISABLE_ENTITY_FRUSTUM_
//    CULLING=1` to disable) -- the first repair experiment, retained as a
//    fallback. It modifies no Ogre state: the last finite box each mesh was
//    given is remembered, inflated by a margin, transformed by the entity's node
//    transform, and tested with Ogre's own `Camera::isVisible`; an entity that
//    fails is suppressed by making `Entity::_updateRenderQueue` a no-op for that
//    one object.
//
// Enabling restoration stands the private cull down, so the two never overlap
// unless `OPENSHIM_FRUSTUM_CULL_WITH_RESTORE=1` asks for both.
//
// Why restoration is preferred, measured on identical workloads:
//
//   * the two reach *identical* main-view decisions -- 21.0 craft submitted by
//     both with everything on screen, 1.0 by both with the camera turned away;
//   * only restoration fixes shadow traversal, which the private cull cannot
//     touch without reimplementing PSSM cascade fitting. Per-cascade craft
//     submissions at idle 20 go from 63/63/63 to 3/60/14.3, using Ogre's own
//     cascade volumes and intersection test;
//   * total submissions fall 23-73% against stock depending on workload, versus
//     0-26% for the private cull.
//
// An earlier version of this file justified *not* restoring the bounds on the
// grounds that Redux might depend on infinite craft bounds for scene queries
// such as targeting or picking. That justification was wrong and is withdrawn.
// Ogre is the renderer; the legacy Battlezone engine owns physics, collision,
// AI, targeting and weapons. The executable imports no Ogre scene-query factory,
// and -- since SceneManager's factories are virtual and could have been reached
// through the vtable without an import -- the five factory slots were located in
// OgreMain's SceneManager vtable (0x354 createAABBQuery, 0x358 createSphereQuery,
// 0x35C createPlaneBoundedVolumeQuery, 0x360 createRayQuery, 0x364
// createIntersectionQuery) and every one of the executable's 171,727 decoded
// instructions was checked: no instruction anywhere references any of those five
// displacements on any register. No Ogre scene query is ever created, so an Ogre
// bounding box cannot feed a gameplay decision.
//
// Deliberate scope limits on the private cull, unchanged:
//
//   * Main-camera traversals only (`onlyShadowCasters == false`). Shadow passes
//     are counted but never culled, so every cascade, every caster and every
//     cascade transition is bit-identical to stock.
//   * Entities only. Particle systems, billboard sets and manual objects keep
//     their exact stock submission behaviour.
//   * Suppression runs while the original `processVisibleObject` runs in full,
//     so the `visibleBounds->merge()` bookkeeping that feeds PSSM cascade
//     fitting is bit-identical by construction rather than replicated.
//
// Skipping `Entity::_updateRenderQueue` also skips the `updateAnimation()` call
// at its tail. That is correct rather than incidental: an entity animates iff it
// is submitted to at least one camera, and shadow passes never cull here, so any
// entity that casts a shadow still animates.
//
// Fail-safe throughout: unresolved exports or a byte-guard mismatch stand both
// features down permanently; a null box, an infinite box with no remembered
// asset bounds, a missing node transform, a mesh with no recorded asset box, or
// a fault anywhere in either decision all fall through to exactly what Redux
// asked for.
//
// Controls:
//   OPENSHIM_RESTORE_CRAFT_BOUNDS=1             restore finite bounds
//   OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE=<k>     centre inflation, default 2.0
//   OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE=all     do not exempt *_c/*_fp/*_cockpit
//   OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE=observe  decide and trace, change nothing
//   OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE=infinite substitute infinite writes only
//   OPENSHIM_BOUNDS_TRACE=1                     bounded per-mesh call-site trace
//   OPENSHIM_FRUSTUM_CULL_WITH_RESTORE=1        run both mechanisms
//   OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1   disable the private cull
//   OPENSHIM_FRUSTUM_CULL_MARGIN=<float>        private-cull half-extent margin
//                                               (default 0.25 = 25%)
//   OPENSHIM_FRUSTUM_CULL_CENSUS=1              per-type bounds census at 1 Hz

// ---------------------------------------------------------------- state -----

static bool g_EntityFrustumCullEnabled = false;
static bool g_EntityFrustumCullInstalled = false;
static bool g_EntityFrustumCullStoodDown = false;
static bool g_FrustumCullCensusEnabled = false;
static float g_FrustumCullMargin = 0.25f;

// ------------------------------------------------ restored craft bounds -----
//
// Independent, opt-in experiment: instead of emulating culling privately,
// repair the renderer state that made culling impossible. See the block comment
// above MeshSetBoundsHook for the located call site and the reasoning.
static bool g_RestoreCraftBoundsEnabled = false;
static float g_RestoreCraftBoundsScale = 2.0f;
static bool g_RestoreCraftBoundsAllMeshes = false;
static bool g_RestoreCraftBoundsPin = true;
// Observe-only: run the whole decision and trace it, but hand Ogre exactly what
// Redux asked for. This is how the stock call site was characterised without
// perturbing the behaviour being characterised.
static bool g_RestoreCraftBoundsObserveOnly = false;
static bool g_BoundsTraceEnabled = false;

// Set only while the original processVisibleObject runs for an object this pass
// decided to cull. Thread-local because Ogre's render traversal is not
// contractually single-threaded even though Redux drives it from one thread.
static thread_local bool t_EntityFrustumCullSuppress = false;

using FnOgreProcessVisibleObject =
    void(__thiscall*)(void*, void*, void*, bool, void*);
using FnOgreEntityUpdateRenderQueueBody = void(__thiscall*)(void*, void*);
using FnOgreMeshSetBounds = void(__thiscall*)(void*, const void*, bool);
using FnOgreCameraIsVisibleBox = bool(__thiscall*)(void*, const void*, void*);
using FnOgreMovableGetWorldBoundingBox = const void*(__thiscall*)(void*, bool);
using FnOgreMovableGetFullTransform = const void*(__thiscall*)(const void*);
using FnOgreEntityGetMeshPtr = const void*(__thiscall*)(const void*);
using FnOgreMeshGetBoundsQuery = const void*(__thiscall*)(const void*);
using FnOgreResourceGetName = const std::string&(__thiscall*)(const void*);
using FnOgreAabbCtor6 =
    void*(__thiscall*)(void*, float, float, float, float, float, float);
using FnOgreMovableGetParentSceneNode = const void*(__thiscall*)(const void*);
using FnOgreNodeGetParent = const void*(__thiscall*)(const void*);
using FnOgreSceneNodeGetWorldAabb = const void*(__thiscall*)(const void*);

static InlineDetour32 g_ProcessVisibleObjectDetour;
static InlineDetour32 g_EntityUpdateRenderQueueDetour;
static InlineDetour32 g_MeshSetBoundsDetour;
static FnOgreProcessVisibleObject g_OgreFn_ProcessVisibleObjectOriginal = nullptr;
static FnOgreEntityUpdateRenderQueueBody g_OgreFn_EntityUpdateRenderQueueOriginal = nullptr;
static FnOgreMeshSetBounds g_OgreFn_MeshSetBoundsOriginal = nullptr;
static FnOgreCameraIsVisibleBox g_OgreFn_CameraIsVisibleBox = nullptr;
static FnOgreMovableGetWorldBoundingBox g_OgreFn_MovableGetWorldBoundingBox = nullptr;
static FnOgreMovableGetFullTransform g_OgreFn_MovableGetFullTransform = nullptr;
static FnOgreEntityGetMeshPtr g_OgreFn_EntityGetMeshPtr = nullptr;
static FnOgreMeshGetBoundsQuery g_OgreFn_MeshGetBounds = nullptr;
static FnOgreResourceGetName g_OgreFn_ResourceGetName = nullptr;
static FnOgreAabbCtor6 g_OgreFn_AabbCtor6 = nullptr;
static FnOgreMovableGetParentSceneNode g_OgreFn_MovableGetParentSceneNode = nullptr;
static FnOgreNodeGetParent g_OgreFn_NodeGetParent = nullptr;
static FnOgreSceneNodeGetWorldAabb g_OgreFn_SceneNodeGetWorldAabb = nullptr;

// Bounded 1 Hz telemetry.
static uint64_t g_FrustumCullTested = 0;
static uint64_t g_FrustumCullCulled = 0;
static uint64_t g_FrustumCullRecovered = 0;
static uint64_t g_FrustumCullUnrecoverable = 0;
static uint64_t g_FrustumCullShadowSkipped = 0;
static uint64_t g_FrustumCullNonEntity = 0;
static uint64_t g_FrustumCullNonEntityAtLastLog = 0;
static uint64_t g_FrustumCullTestedAtLastLog = 0;
static uint64_t g_FrustumCullCulledAtLastLog = 0;
static uint64_t g_FrustumCullRecoveredAtLastLog = 0;
static uint64_t g_FrustumCullUnrecoverableAtLastLog = 0;
static uint64_t g_FrustumCullShadowSkippedAtLastLog = 0;
static DWORD g_FrustumCullLogTick = 0;

// Restored-bounds telemetry. Bounded: the trace stops after a fixed number of
// lines and the aggregate is folded into the existing 1 Hz report.
static uint64_t g_RestoreBoundsSubstituted = 0;
static uint64_t g_RestoreBoundsPinned = 0;
static uint64_t g_RestoreBoundsExcluded = 0;
static uint64_t g_RestoreBoundsUnknownAsset = 0;
static uint64_t g_RestoreBoundsSubstitutedAtLastLog = 0;
static uint64_t g_RestoreBoundsPinnedAtLastLog = 0;
static uint32_t g_BoundsTraceFiniteEmitted = 0;
static uint32_t g_BoundsTraceInfiniteEmitted = 0;
// Separate budgets so a flood of ordinary finite writes cannot starve the
// infinite ones, which are the whole point of the instrument.
constexpr uint32_t kBoundsTraceFiniteLimit = 64;
constexpr uint32_t kBoundsTraceInfiniteLimit = 64;
constexpr uint8_t kBoundsTracePerMeshLimit = 3;

// --------------------------------------------- remembered asset bounds ------
//
// Fixed capacity, no allocation on any hot path, no unbounded growth. A mesh
// that does not fit simply never gets a recovered box, so its entities are
// submitted exactly as they are today.

struct RememberedMeshBounds
{
    const void* mesh = nullptr;
    // The most recent finite box the mesh was given. Redux rewrites this on
    // every spawn (see the asset box below), so it is a working value and not a
    // statement about the asset.
    float minimum[3] = {};
    float maximum[3] = {};
    // The *first* finite box the mesh was given, which is the one
    // MeshSerializerImpl::readBoundsInfo set straight out of M_MESH_BOUNDS.
    // Every restored-bounds policy is derived from this and never from the
    // working value, because Redux's own per-spawn scale(2,2,2) compounds.
    float assetMinimum[3] = {};
    float assetMaximum[3] = {};
    bool haveAsset = false;
    // Cached "is this mesh only ever a first-person view model" verdict, so the
    // name test runs once per mesh rather than once per _setBounds call.
    bool restoreClassified = false;
    bool restoreExcluded = false;
    // Per-mesh trace budget. Without it a 16x16 terrain grid spends the whole
    // global budget before a single craft has spawned.
    uint8_t tracedFinite = 0;
    uint8_t tracedInfinite = 0;
    // Set the first time this mesh is handed an EXTENT_INFINITE box. Nothing is
    // repaired until that has happened, so meshes the defect never touched --
    // terrain clusters, buildings, ordnance, effects -- keep bit-identical
    // bounds and cannot be culled differently than they are today.
    bool sawInfinite = false;
};

// Open-addressed, power-of-two, linear probe. A linear scan was measured to
// cost real frame time once a mission has a few hundred meshes loaded: the
// lookup runs for every infinitely-bounded entity on every camera traversal.
constexpr uint32_t kRememberedMeshBoundsCapacity = 1024;   // must stay a power of two
static_assert(
    (kRememberedMeshBoundsCapacity & (kRememberedMeshBoundsCapacity - 1)) == 0,
    "remembered-bounds table must be a power of two");

static RememberedMeshBounds g_RememberedMeshBounds[kRememberedMeshBoundsCapacity];
static uint32_t g_RememberedMeshBoundsUsed = 0;
static uint64_t g_RememberedMeshBoundsDropped = 0;

static uint32_t RememberedMeshBoundsSlot(const void* mesh)
{
    // Mesh pointers are allocator-aligned, so the low bits carry no entropy.
    uint32_t hash = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mesh) >> 4);
    hash *= 2654435761u;
    return hash & (kRememberedMeshBoundsCapacity - 1);
}

static const RememberedMeshBounds* FindRememberedMeshBounds(const void* mesh)
{
    uint32_t slot = RememberedMeshBoundsSlot(mesh);
    for (uint32_t probe = 0; probe < kRememberedMeshBoundsCapacity; ++probe)
    {
        const RememberedMeshBounds& candidate = g_RememberedMeshBounds[slot];
        if (!candidate.mesh)
            return nullptr;
        if (candidate.mesh == mesh)
            return &candidate;
        slot = (slot + 1) & (kRememberedMeshBoundsCapacity - 1);
    }
    return nullptr;
}

static RememberedMeshBounds* FindRememberedMeshBoundsMutable(const void* mesh)
{
    return const_cast<RememberedMeshBounds*>(FindRememberedMeshBounds(mesh));
}

static void RememberMeshBounds(const void* mesh, const float* box)
{
    if (!mesh)
        return;
    // Leave headroom so probing always terminates on an empty slot.
    if (g_RememberedMeshBoundsUsed >= (kRememberedMeshBoundsCapacity * 3) / 4)
    {
        ++g_RememberedMeshBoundsDropped;
        return;
    }
    uint32_t slot = RememberedMeshBoundsSlot(mesh);
    for (uint32_t probe = 0; probe < kRememberedMeshBoundsCapacity; ++probe)
    {
        RememberedMeshBounds& candidate = g_RememberedMeshBounds[slot];
        if (!candidate.mesh)
        {
            candidate.mesh = mesh;
            ++g_RememberedMeshBoundsUsed;
        }
        if (candidate.mesh == mesh)
        {
            std::memcpy(candidate.minimum, box, sizeof(float) * 3);
            std::memcpy(candidate.maximum, box + 3, sizeof(float) * 3);
            if (!candidate.haveAsset)
            {
                std::memcpy(candidate.assetMinimum, box, sizeof(float) * 3);
                std::memcpy(candidate.assetMaximum, box + 3, sizeof(float) * 3);
                candidate.haveAsset = true;
            }
            return;
        }
        slot = (slot + 1) & (kRememberedMeshBoundsCapacity - 1);
    }
    ++g_RememberedMeshBoundsDropped;
}

// ------------------------------------------------------------- resolving ----

// OgreMain exports reach their bodies through incremental-link thunks: the
// exported address is a bare `E9 rel32`. A detour has to patch the body, not
// the thunk, or an internal direct call would bypass it.
static void* ResolveOgreExportBody(const char* mangledName)
{
    HMODULE ogre = GetModuleHandleA("OgreMain.dll");
    if (!ogre || !mangledName)
        return nullptr;
    auto* address = reinterpret_cast<uint8_t*>(GetProcAddress(ogre, mangledName));
    if (!address)
        return nullptr;
    if (address[0] == 0xE9)
    {
        int32_t relative = 0;
        std::memcpy(&relative, address + 1, sizeof(relative));
        return address + 5 + relative;
    }
    return address;
}

// Returns the Mesh* behind an Entity, or null. Safe to call on any object:
// callers gate on the RTTI type or on a failed lookup rather than on this.
static const void* TryGetEntityMesh(const void* entity)
{
    if (!g_OgreFn_EntityGetMeshPtr)
        return nullptr;
    __try
    {
        const void* sharedPtr = g_OgreFn_EntityGetMeshPtr(entity);
        return sharedPtr ? *reinterpret_cast<void* const*>(sharedPtr) : nullptr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return nullptr;
    }
}

// ------------------------------------------------- entity classification ----
//
// Only Ogre::Entity can ever be culled here, because suppression works through
// Entity::_updateRenderQueue. Testing anything else is pure overhead, and the
// scene sends plenty of it: an early census counted roughly 105 Ogre::Light
// visits per frame, every one of which reports a null box and can never be
// culled. Classify once per vtable and cache the verdict.

constexpr uint32_t kEntityVtableCacheCapacity = 256;   // must stay a power of two
static_assert(
    (kEntityVtableCacheCapacity & (kEntityVtableCacheCapacity - 1)) == 0,
    "entity vtable cache must be a power of two");

struct EntityVtableCacheSlot
{
    const void* vtable = nullptr;
    bool isEntity = false;
};

static EntityVtableCacheSlot g_EntityVtableCache[kEntityVtableCacheCapacity];
static uint32_t g_EntityVtableCacheUsed = 0;

static void CopyFrustumCullTypeName(char* destination, size_t capacity, const void* object);

static bool IsOgreEntityObject(const void* object)
{
    const void* vtable = nullptr;
    __try
    {
        vtable = *reinterpret_cast<void* const*>(object);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
    if (!vtable)
        return false;

    uint32_t hash = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(vtable) >> 4);
    hash *= 2654435761u;
    uint32_t slot = hash & (kEntityVtableCacheCapacity - 1);
    for (uint32_t probe = 0; probe < kEntityVtableCacheCapacity; ++probe)
    {
        EntityVtableCacheSlot& candidate = g_EntityVtableCache[slot];
        if (candidate.vtable == vtable)
            return candidate.isEntity;
        if (!candidate.vtable)
        {
            // Leave headroom so probing always terminates on an empty slot. A
            // full cache simply stops classifying, which submits everything.
            if (g_EntityVtableCacheUsed >= (kEntityVtableCacheCapacity * 3) / 4)
                return false;
            char typeName[96] = {};
            CopyFrustumCullTypeName(typeName, sizeof(typeName), object);
            candidate.vtable = vtable;
            // MSVC RTTI decorates Ogre::Entity as ".?AVEntity@Ogre@@". Match the
            // exact decorated name so SubEntity, InstancedEntity and any game
            // type merely containing "Entity" are not swept in.
            candidate.isEntity = std::strcmp(typeName, ".?AVEntity@Ogre@@") == 0;
            ++g_EntityVtableCacheUsed;
            return candidate.isEntity;
        }
        slot = (slot + 1) & (kEntityVtableCacheCapacity - 1);
    }
    return false;
}

// ------------------------------------------------------------- census -------
//
// Opt-in. Answers "which object types reach processVisibleObject and what does
// each report for bounds" from a fixed 24-slot table keyed on vtable and extent
// kind, dumped once per second. This is the instrument that located the defect.

struct FrustumCullCensusSlot
{
    const void* vtable = nullptr;
    int extentKind = -1;
    char typeName[96] = {};
    char sampleMesh[96] = {};
    int sampleMeshExtent = -1;
    uint64_t seen = 0;
    uint64_t culled = 0;
    uint64_t recovered = 0;
    // Bitmask of AxisAlignedBox::Extent values observed on the object's own
    // SceneNode and on that node's parent: bit 0 null, bit 1 finite,
    // bit 2 infinite. This is what answers whether one pathological child can
    // still drag an ancestor's world box to infinite.
    uint8_t nodeExtentMask = 0;
    uint8_t parentNodeExtentMask = 0;
};

static FrustumCullCensusSlot g_FrustumCullCensus[24];
static uint32_t g_FrustumCullCensusUsed = 0;
static uint64_t g_FrustumCullCensusDropped = 0;

static void CopyFrustumCullTypeName(char* destination, size_t capacity, const void* object)
{
    destination[0] = 0;
    struct CompleteObjectLocator32
    {
        uint32_t signature;
        uint32_t offset;
        uint32_t constructorDisplacement;
        const void* typeDescriptor;
        const void* classDescriptor;
    };
    __try
    {
        void* const* vtable = *reinterpret_cast<void* const* const*>(object);
        const auto* locator = vtable
            ? reinterpret_cast<const CompleteObjectLocator32*>(vtable[-1])
            : nullptr;
        const char* name = locator && locator->typeDescriptor
            ? static_cast<const char*>(locator->typeDescriptor) + 8
            : nullptr;
        if (!name)
            return;
        size_t length = 0;
        while (length + 1 < capacity && name[length])
            ++length;
        if (length)
            std::memcpy(destination, name, length);
        destination[length] = 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        destination[0] = 0;
    }
}

static void CopyFrustumCullMeshSample(FrustumCullCensusSlot* slot, const void* entity)
{
    __try
    {
        const void* mesh = TryGetEntityMesh(entity);
        if (!mesh)
            return;
        if (g_OgreFn_ResourceGetName)
        {
            const std::string& name = g_OgreFn_ResourceGetName(mesh);
            const size_t length = (std::min)(name.size(), sizeof(slot->sampleMesh) - 1);
            if (length)
                std::memcpy(slot->sampleMesh, name.c_str(), length);
            slot->sampleMesh[length] = 0;
        }
        if (g_OgreFn_MeshGetBounds)
        {
            const auto* box = static_cast<const float*>(g_OgreFn_MeshGetBounds(mesh));
            if (box)
            {
                uint32_t extent = 0;
                std::memcpy(&extent, box + 6, sizeof(extent));
                slot->sampleMeshExtent = static_cast<int>(extent);
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

static void RecordFrustumCullCensus(
    const void* object, int extentKind, bool culled, bool recovered)
{
    const void* vtable = nullptr;
    __try
    {
        vtable = *reinterpret_cast<void* const*>(object);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return;
    }
    FrustumCullCensusSlot* slot = nullptr;
    for (uint32_t index = 0; index < g_FrustumCullCensusUsed; ++index)
    {
        if (g_FrustumCullCensus[index].vtable == vtable &&
            g_FrustumCullCensus[index].extentKind == extentKind)
        {
            slot = &g_FrustumCullCensus[index];
            break;
        }
    }
    if (!slot)
    {
        if (g_FrustumCullCensusUsed >= std::size(g_FrustumCullCensus))
        {
            ++g_FrustumCullCensusDropped;
            return;
        }
        slot = &g_FrustumCullCensus[g_FrustumCullCensusUsed++];
        slot->vtable = vtable;
        slot->extentKind = extentKind;
        CopyFrustumCullTypeName(slot->typeName, sizeof(slot->typeName), object);
        if (std::strstr(slot->typeName, "Entity"))
            CopyFrustumCullMeshSample(slot, object);
    }
    ++slot->seen;
    if (culled)
        ++slot->culled;
    if (recovered)
        ++slot->recovered;

    // Node-chain sampling. Opt-in with the census, so the extra pair of virtual
    // calls per visit never runs in a normal session.
    if (g_OgreFn_MovableGetParentSceneNode && g_OgreFn_SceneNodeGetWorldAabb)
    {
        __try
        {
            const void* node = g_OgreFn_MovableGetParentSceneNode(object);
            if (node)
            {
                const auto* box =
                    static_cast<const float*>(g_OgreFn_SceneNodeGetWorldAabb(node));
                if (box)
                {
                    uint32_t extent = 0;
                    std::memcpy(&extent, box + 6, sizeof(extent));
                    if (extent < 3u)
                        slot->nodeExtentMask |= static_cast<uint8_t>(1u << extent);
                }
                if (g_OgreFn_NodeGetParent)
                {
                    const void* parent = g_OgreFn_NodeGetParent(node);
                    if (parent)
                    {
                        const auto* parentBox = static_cast<const float*>(
                            g_OgreFn_SceneNodeGetWorldAabb(parent));
                        if (parentBox)
                        {
                            uint32_t extent = 0;
                            std::memcpy(&extent, parentBox + 6, sizeof(extent));
                            if (extent < 3u)
                            {
                                slot->parentNodeExtentMask |=
                                    static_cast<uint8_t>(1u << extent);
                            }
                        }
                    }
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
}

static const char* DescribeExtentMask(uint8_t mask)
{
    switch (mask & 0x7u)
    {
    case 0: return "-";
    case 1: return "null";
    case 2: return "finite";
    case 3: return "null|finite";
    case 4: return "INFINITE";
    case 5: return "null|INFINITE";
    case 6: return "finite|INFINITE";
    default: return "null|finite|INFINITE";
    }
}

static void DumpFrustumCullCensus()
{
    for (uint32_t index = 0; index < g_FrustumCullCensusUsed; ++index)
    {
        FrustumCullCensusSlot& slot = g_FrustumCullCensus[index];
        LogShimA(
            LogLevel::Info,
            "frustumcull",
            "[FRUSTUMCULL][census] type=%s extent=%d meshExtent=%d sampleMesh=%s "
            "nodeExtents=%s parentNodeExtents=%s seen=%llu recovered=%llu culled=%llu",
            slot.typeName[0] ? slot.typeName : "<unknown>",
            slot.extentKind,
            slot.sampleMeshExtent,
            slot.sampleMesh[0] ? slot.sampleMesh : "<none>",
            DescribeExtentMask(slot.nodeExtentMask),
            DescribeExtentMask(slot.parentNodeExtentMask),
            static_cast<unsigned long long>(slot.seen),
            static_cast<unsigned long long>(slot.recovered),
            static_cast<unsigned long long>(slot.culled));
        slot.seen = 0;
        slot.culled = 0;
        slot.recovered = 0;
        slot.nodeExtentMask = 0;
        slot.parentNodeExtentMask = 0;
    }
    if (g_FrustumCullCensusDropped)
    {
        LogShimA(
            LogLevel::Info,
            "frustumcull",
            "[FRUSTUMCULL][census] dropped=%llu (table full)",
            static_cast<unsigned long long>(g_FrustumCullCensusDropped));
    }
}

// --------------------------------------------------------- cull decision ----

enum class FrustumCullOutcome
{
    Submit,        // visible, or no basis for a decision
    Cull,          // entirely outside the camera frustum
    Ineligible,    // null or unrecoverable bounds -- never culled
};

// Ogre's AxisAlignedBox is { Vector3 mMinimum; Vector3 mMaximum; Extent mExtent;
// mutable Vector3* mCorners; }. Camera::isVisible(AABB) reads only the first
// three, through inline accessors, so a stack-built box is safe to pass.
struct ScratchAxisAlignedBox
{
    float minimum[3];
    float maximum[3];
    uint32_t extent;
    const void* corners;
};

// Equivalent to AxisAlignedBox::transformAffine(Matrix4): transform the centre
// and take the absolute-value matrix times the half size. Ogre's Matrix4 is
// Real m[4][4] in row-major order with translation in column 3.
static void TransformLocalBoxAffine(
    const float* matrix, const float* localMin, const float* localMax,
    float safetyMargin, ScratchAxisAlignedBox& out)
{
    float centre[3];
    float halfSize[3];
    for (int axis = 0; axis < 3; ++axis)
    {
        centre[axis] = (localMin[axis] + localMax[axis]) * 0.5f;
        halfSize[axis] = (localMax[axis] - localMin[axis]) * 0.5f;
        // Skeletal animation can carry geometry a little outside the bind-pose
        // bounds the exporter recorded, so the recovered box is inflated before
        // it is trusted. This is a deliberate over-estimate: it can only cause
        // an object to be submitted that could have been culled, never the
        // reverse.
        halfSize[axis] += halfSize[axis] * safetyMargin;
    }

    float newCentre[3];
    float newHalfSize[3];
    for (int row = 0; row < 3; ++row)
    {
        const float* r = matrix + row * 4;
        newCentre[row] = r[0] * centre[0] + r[1] * centre[1] + r[2] * centre[2] + r[3];
        newHalfSize[row] =
            std::fabs(r[0]) * halfSize[0] +
            std::fabs(r[1]) * halfSize[1] +
            std::fabs(r[2]) * halfSize[2];
    }
    for (int axis = 0; axis < 3; ++axis)
    {
        out.minimum[axis] = newCentre[axis] - newHalfSize[axis];
        out.maximum[axis] = newCentre[axis] + newHalfSize[axis];
    }
    out.extent = 1u;  // EXTENT_FINITE
    out.corners = nullptr;
}

// Kept in its own function so the __try/__except does not sit in a scope that
// requires object unwinding.
static FrustumCullOutcome DecideFrustumCull(
    void* movableObject, void* camera, int& extentKind, bool& recovered)
{
    extentKind = -1;
    recovered = false;
    __try
    {
        // MovableObject::getWorldBoundingBox is called non-virtually on
        // purpose. Entity overrides it only to force its child objects to
        // derive their own boxes first; the attachment merge itself happens
        // inside the *virtual* getBoundingBox() that the base implementation
        // calls, so weapons, exhausts and other tag-point children are already
        // included in the box this returns.
        const auto* const worldBox = static_cast<const float*>(
            g_OgreFn_MovableGetWorldBoundingBox(movableObject, true));
        if (!worldBox)
            return FrustumCullOutcome::Ineligible;

        uint32_t extent = 0;
        std::memcpy(&extent, worldBox + 6, sizeof(extent));
        extentKind = static_cast<int>(extent);

        if (extent == 1u)
        {
            return g_OgreFn_CameraIsVisibleBox(camera, worldBox, nullptr)
                ? FrustumCullOutcome::Submit
                : FrustumCullOutcome::Cull;
        }
        if (extent != 2u)
        {
            // EXTENT_NULL: the object has no geometry to bound yet. Ogre would
            // treat this as invisible; this pass declines to make that call.
            return FrustumCullOutcome::Ineligible;
        }

        // Infinite. Try to recover the asset's own bounds for this mesh.
        if (!g_OgreFn_MovableGetFullTransform)
            return FrustumCullOutcome::Ineligible;
        const void* const mesh = TryGetEntityMesh(movableObject);
        if (!mesh)
            return FrustumCullOutcome::Ineligible;
        const RememberedMeshBounds* const remembered = FindRememberedMeshBounds(mesh);
        if (!remembered)
            return FrustumCullOutcome::Ineligible;
        const auto* const transform = static_cast<const float*>(
            g_OgreFn_MovableGetFullTransform(movableObject));
        if (!transform)
            return FrustumCullOutcome::Ineligible;

        ScratchAxisAlignedBox scratch = {};
        TransformLocalBoxAffine(
            transform, remembered->minimum, remembered->maximum,
            g_FrustumCullMargin, scratch);
        recovered = true;
        return g_OgreFn_CameraIsVisibleBox(camera, &scratch, nullptr)
            ? FrustumCullOutcome::Submit
            : FrustumCullOutcome::Cull;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // Any fault anywhere in the decision means this object is submitted.
        return FrustumCullOutcome::Submit;
    }
}

// --------------------------------------------------------------- hooks ------

// ------------------------------------------- restored-bounds decision -------
//
// Located call site (battlezone98redux.exe 2.2.301, GOG, ImageBase 0x00400000).
// `Mesh::_setBounds` is imported once, at IAT 0x0086979C, and reached from four
// places in `.text`:
//
//   0x0067E76F  <- the only infinite one; see below
//   0x0067F860  bounds = Entity::getBoundingBox() scaled by 2 -- but the whole
//               block is behind an inlined strcmp against "abspow"
//               (0x00878A48) at 0x0067F6EE..0x0067F776, so it runs for that one
//               object and for no craft. An earlier revision of this comment
//               claimed it scaled every craft on every spawn and compounded;
//               that was inferred from the block's contents without reading its
//               guard, and a 20-walker observe run recorded zero such writes.
//   0x0077945F  procedural geometry, finite AABB(min,max) ctor
//   0x00779B05  procedural geometry, finite AABB(min,max) ctor
//
// `??0AxisAlignedBox@Ogre@@QAE@W4Extent@01@@Z` -- the only way this binary can
// name an extent kind directly -- is called exactly once, at 0x0067E744, with
// `push 2` (EXTENT_INFINITE), and its result goes straight into the
// `_setBounds` at 0x0067E76F. So there is one infinite-bounds assignment in the
// whole executable, and it is unconditional within its function.
//
// That function, 0x0067E5A0, builds the *first-person view* entity:
//
//     sprintf(name, "%.*s.mesh", 26, requestedName)
//     entity = sceneManager->createEntity(...)
//     entity->setCastShadows(false)
//     ... store entity/skeleton into the caller's view state ...
//     mesh->_setBounds(AxisAlignedBox(EXTENT_INFINITE), true)
//
// `setCastShadows(false)` plus an unconditional never-cull box is a coherent
// "always draw the cockpit I am sitting in" policy, and for a mesh used only as
// a first-person model it is harmless.
//
// The defect is which mesh it lands on. Its single caller, 0x0067F480, picks the
// first-person mesh name in three ways:
//
//   * a 15-entry table at 0x008ED2E8 -> 0x008ED308 mapping craft to a dedicated
//     model: avartl->avartl_c, avturr->avturr_c, avwalk->avwalk_c, ...,
//     aspilo->aspilo_fp, bsheav->bsheav_fp;
//   * "<name>_cockpit" when that resource exists;
//   * otherwise, at 0x0067FDE8, the craft's *own* mesh name -- taken when the
//     skeleton carries a bone whose fourth character is '2' (the AGR2* group;
//     avtank.skeleton has AGR21bga/agr21bda).
//
// `Ogre::Mesh` is a shared resource. On that third path the never-cull policy is
// written onto the same Mesh every world instance of the craft renders from, so
// an ordinary hovertank standing in the desert inherits a cockpit's
// "always visible" flag. That is the whole of the missing-culling defect, and it
// is renderer state only: Battlezone's own engine owns physics, collision, AI,
// targeting and weapons, and never consults an Ogre bounding box for any of it.
//
// Two consequences drive the policy below.
//
//  1. The repair must be scoped by *mesh*, not by call site. Leaving `*_c`,
//     `*_fp` and `*_cockpit` meshes infinite keeps the intended behaviour for
//     models that really are only ever drawn from inside the cockpit, and
//     repairs exactly the shared craft meshes.
//  2. The policy must be derived from the *asset* box rather than from whatever
//     finite box the mesh happens to be holding when the infinite write lands.
//     For stock craft those are the same value, but the serializer's box is the
//     only one with a defined provenance, so using it keeps the repair
//     idempotent regardless of what else rewrote the bounds first.

static bool MeshIsFirstPersonOnly(const void* mesh)
{
    if (!g_OgreFn_ResourceGetName)
        return false;
    char lowered[128] = {};
    const std::string& name = g_OgreFn_ResourceGetName(mesh);
    const size_t length = (std::min)(name.size(), sizeof(lowered) - 1);
    for (size_t i = 0; i < length; ++i)
        lowered[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(name[i])));
    lowered[length] = 0;

    // Compare on the stem so both "avwalk_c" and "avwalk_c.mesh" match.
    size_t stem = length;
    if (stem >= 5 && std::strcmp(lowered + stem - 5, ".mesh") == 0)
        stem -= 5;

    static const char* const kFirstPersonSuffixes[] = { "_c", "_fp", "_cockpit" };
    for (const char* suffix : kFirstPersonSuffixes)
    {
        const size_t suffixLength = std::strlen(suffix);
        if (stem >= suffixLength &&
            std::strncmp(lowered + stem - suffixLength, suffix, suffixLength) == 0)
        {
            return true;
        }
    }
    return false;
}

static void CopyMeshNameForTrace(char* destination, size_t capacity, const void* mesh)
{
    destination[0] = 0;
    if (!g_OgreFn_ResourceGetName)
        return;
    __try
    {
        const std::string& name = g_OgreFn_ResourceGetName(mesh);
        const size_t length = (std::min)(name.size(), capacity - 1);
        if (length)
            std::memcpy(destination, name.c_str(), length);
        destination[length] = 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        destination[0] = 0;
    }
}

static float AssetBoxRadius(const RememberedMeshBounds& entry)
{
    const float dx = entry.assetMaximum[0] - entry.assetMinimum[0];
    const float dy = entry.assetMaximum[1] - entry.assetMinimum[1];
    const float dz = entry.assetMaximum[2] - entry.assetMinimum[2];
    return 0.5f * std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Bounded: at most kBoundsTraceLimit lines for the whole process lifetime, so a
// mission with hundreds of spawns cannot turn this into per-frame logging.
static void TraceBoundsDecision(
    const void* mesh,
    const char* action,
    uint32_t incomingExtent,
    const float* incoming,
    RememberedMeshBounds& entry,
    const float* substitute,
    const void* callSite)
{
    if (!g_BoundsTraceEnabled)
        return;
    const bool infinite = (incomingExtent == 2u);
    uint8_t& perMesh = infinite ? entry.tracedInfinite : entry.tracedFinite;
    uint32_t& emitted =
        infinite ? g_BoundsTraceInfiniteEmitted : g_BoundsTraceFiniteEmitted;
    const uint32_t limit =
        infinite ? kBoundsTraceInfiniteLimit : kBoundsTraceFiniteLimit;
    if (perMesh >= kBoundsTracePerMeshLimit || emitted >= limit)
        return;
    ++perMesh;
    ++emitted;
    const uint32_t sequence = emitted;

    char meshName[96] = {};
    CopyMeshNameForTrace(meshName, sizeof(meshName), mesh);

    uintptr_t callOffset = 0;
    char callModule[MAX_PATH] = "?";
    HMODULE owner = nullptr;
    if (GetModuleHandleExA(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            static_cast<LPCSTR>(callSite),
            &owner) &&
        owner)
    {
        char modulePath[MAX_PATH] = {};
        if (GetModuleFileNameA(owner, modulePath, MAX_PATH))
        {
            const char* slash = std::strrchr(modulePath, '\\');
            const char* leaf = slash ? slash + 1 : modulePath;
            std::strncpy(callModule, leaf, sizeof(callModule) - 1);
            callModule[sizeof(callModule) - 1] = 0;
        }
        callOffset =
            reinterpret_cast<uintptr_t>(callSite) - reinterpret_cast<uintptr_t>(owner);
    }

    const bool incomingFinite = (incomingExtent == 1u);
    const char* incomingKind =
        incomingExtent == 0u ? "NULL" : (incomingFinite ? "FINITE" : "INFINITE");

    LogShimA(
        LogLevel::Info,
        "frustumcull",
        "[BOUNDSTRACE] #%u mesh=%s action=%s incoming=%s "
        "incomingMin=(%.2f,%.2f,%.2f) incomingMax=(%.2f,%.2f,%.2f) "
        "assetMin=(%.2f,%.2f,%.2f) assetMax=(%.2f,%.2f,%.2f) assetRadius=%.2f "
        "newMin=(%.2f,%.2f,%.2f) newMax=(%.2f,%.2f,%.2f) callSite=%s+0x%IX tid=%lu",
        sequence,
        meshName[0] ? meshName : "<unnamed>",
        action,
        incomingKind,
        incomingFinite ? incoming[0] : 0.0f,
        incomingFinite ? incoming[1] : 0.0f,
        incomingFinite ? incoming[2] : 0.0f,
        incomingFinite ? incoming[3] : 0.0f,
        incomingFinite ? incoming[4] : 0.0f,
        incomingFinite ? incoming[5] : 0.0f,
        entry.assetMinimum[0], entry.assetMinimum[1], entry.assetMinimum[2],
        entry.assetMaximum[0], entry.assetMaximum[1], entry.assetMaximum[2],
        AssetBoxRadius(entry),
        substitute ? substitute[0] : 0.0f,
        substitute ? substitute[1] : 0.0f,
        substitute ? substitute[2] : 0.0f,
        substitute ? substitute[3] : 0.0f,
        substitute ? substitute[4] : 0.0f,
        substitute ? substitute[5] : 0.0f,
        callModule,
        callOffset,
        GetCurrentThreadId());
}

// Fills `out` with min[3],max[3] and returns true when this _setBounds call
// should be replaced. Runs inside the caller's __try.
static bool DecideRestoredBounds(
    const void* mesh,
    const float* box,
    uint32_t extent,
    float* out,
    const void* callSite)
{
    if (extent != 1u && extent != 2u)
        return false;

    RememberedMeshBounds* entry = FindRememberedMeshBoundsMutable(mesh);
    if (!entry || !entry->haveAsset)
    {
        // No serializer box on record, so there is nothing trustworthy to
        // restore. Stock behaviour, including an infinite box, is preserved.
        if (extent == 2u)
            ++g_RestoreBoundsUnknownAsset;
        return false;
    }

    if (!entry->restoreClassified)
    {
        entry->restoreClassified = true;
        entry->restoreExcluded =
            !g_RestoreCraftBoundsAllMeshes && MeshIsFirstPersonOnly(mesh);
    }
    if (entry->restoreExcluded)
    {
        if (extent == 2u)
            ++g_RestoreBoundsExcluded;
        return false;
    }

    if (extent != 2u && !entry->sawInfinite && !g_RestoreCraftBoundsObserveOnly)
    {
        // This mesh has never been given an infinite box, so there is nothing
        // here to repair and no reason to touch its bounds. Observe mode is
        // exempt because it changes nothing and this gate would otherwise hide
        // any post-load rewrite on exactly the meshes worth measuring: craft
        // that own a dedicated cockpit model never go infinite, so their world
        // mesh is the one nothing else would ever report on.
        return false;
    }

    float policy[6];
    for (int axis = 0; axis < 3; ++axis)
    {
        // Inflate about the box centre, not about the origin. Ogre's
        // AxisAlignedBox::scale(), which 0x0067F860 uses, scales about the
        // origin and is *not* containment-preserving: apammo.mesh has
        // assetMin.y = 0.29, so scaling by 2 lifts the floor of the box to 0.58
        // and leaves real geometry outside it. Centre inflation always contains
        // the asset box.
        const float centre =
            0.5f * (entry->assetMinimum[axis] + entry->assetMaximum[axis]);
        const float half =
            0.5f * (entry->assetMaximum[axis] - entry->assetMinimum[axis]) *
            g_RestoreCraftBoundsScale;
        policy[axis] = centre - half;
        policy[3 + axis] = centre + half;
    }

    if (extent == 2u)
    {
        entry->sawInfinite = true;
        std::memcpy(out, policy, sizeof(policy));
        if (g_RestoreCraftBoundsObserveOnly)
        {
            TraceBoundsDecision(mesh, "observed", extent, box, *entry, out, callSite);
            return false;
        }
        ++g_RestoreBoundsSubstituted;
        TraceBoundsDecision(mesh, "restored", extent, box, *entry, out, callSite);
        return true;
    }

    // A finite write to a mesh the defect *did* touch, landing outside the
    // policy box. No stock path is known to produce one -- the only scale-by-2
    // in the executable is guarded on the name "abspow", which never goes
    // infinite -- so in practice this clamp does not fire; a 20-walker observe
    // run recorded zero. It is kept because it costs nothing and it pins the
    // mesh to one deterministic box if a mod or a future build does rewrite
    // bounds after the infinite write.
    // Only oversized writes are traced; ordinary load-time writes would swamp
    // the budget.
    bool oversized = false;
    for (int axis = 0; axis < 3; ++axis)
    {
        const float tolerance =
            0.02f * std::fabs(policy[3 + axis] - policy[axis]) + 1.0e-3f;
        if (box[axis] < policy[axis] - tolerance ||
            box[3 + axis] > policy[3 + axis] + tolerance)
        {
            oversized = true;
            break;
        }
    }
    if (!oversized)
        return false;

    std::memcpy(out, policy, sizeof(policy));
    if (g_RestoreCraftBoundsObserveOnly)
    {
        TraceBoundsDecision(mesh, "observed-oversized", extent, box, *entry, out, callSite);
        return false;
    }
    if (!g_RestoreCraftBoundsPin)
    {
        TraceBoundsDecision(mesh, "left-oversized", extent, box, *entry, out, callSite);
        return false;
    }

    ++g_RestoreBoundsPinned;
    TraceBoundsDecision(mesh, "pinned", extent, box, *entry, out, callSite);
    return true;
}

// Reported per event rather than on a timer. Bounds writes only happen when a
// craft is created, so the rate is naturally low, and a 1 Hz aggregate loses
// the tail: nothing calls _setBounds again after the last spawn, so the final
// state would never be logged. The hard cap keeps a long mission with heavy
// respawning bounded.
static uint32_t g_RestoreBoundsReportsEmitted = 0;
constexpr uint32_t kRestoreBoundsReportLimit = 256;

static void ReportRestoreBoundsIfDue()
{
    if (!g_RestoreCraftBoundsEnabled)
        return;
    if (g_RestoreBoundsSubstituted == g_RestoreBoundsSubstitutedAtLastLog &&
        g_RestoreBoundsPinned == g_RestoreBoundsPinnedAtLastLog)
    {
        return;
    }
    g_RestoreBoundsSubstitutedAtLastLog = g_RestoreBoundsSubstituted;
    g_RestoreBoundsPinnedAtLastLog = g_RestoreBoundsPinned;
    if (g_RestoreBoundsReportsEmitted >= kRestoreBoundsReportLimit)
        return;
    ++g_RestoreBoundsReportsEmitted;

    LogShimA(
        LogLevel::Info,
        "frustumcull",
        "[RESTOREBOUNDS] restored=%llu pinned=%llu firstPersonLeftInfinite=%llu "
        "noAssetBox=%llu knownMeshes=%u scale=%.2f scope=%s mode=%s",
        static_cast<unsigned long long>(g_RestoreBoundsSubstituted),
        static_cast<unsigned long long>(g_RestoreBoundsPinned),
        static_cast<unsigned long long>(g_RestoreBoundsExcluded),
        static_cast<unsigned long long>(g_RestoreBoundsUnknownAsset),
        g_RememberedMeshBoundsUsed,
        g_RestoreCraftBoundsScale,
        g_RestoreCraftBoundsAllMeshes ? "all" : "shared",
        g_RestoreCraftBoundsObserveOnly
            ? "observe"
            : (g_RestoreCraftBoundsPin ? "pin" : "infinite"));
}

static void __fastcall MeshSetBoundsHook(
    void* mesh, void* /*unusedEdx*/, const void* bounds, bool pad)
{
    const void* const callSite = _ReturnAddress();

    // With OPENSHIM_RESTORE_CRAFT_BOUNDS off this is observe-only, exactly as
    // the first repair experiment shipped it: the asset's finite box is
    // captured on its way past so the private cull has something to fall back
    // on, and Ogre's own state is left exactly as Redux wants it.
    float substitute[6] = {};
    bool haveSubstitute = false;

    if (bounds)
    {
        __try
        {
            const auto* box = static_cast<const float*>(bounds);
            uint32_t extent = 0;
            std::memcpy(&extent, box + 6, sizeof(extent));
            if (extent == 1u)
                RememberMeshBounds(mesh, box);
            if (g_RestoreCraftBoundsEnabled)
            {
                haveSubstitute =
                    DecideRestoredBounds(mesh, box, extent, substitute, callSite);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            haveSubstitute = false;
        }
    }

    if (haveSubstitute && g_OgreFn_AabbCtor6 && g_OgreFn_MeshSetBoundsOriginal)
    {
        // Build the replacement with Ogre's own constructor rather than by
        // writing a hand-laid struct, so the object is correct for whatever
        // AxisAlignedBox layout this OgreMain build actually uses.
        __try
        {
            alignas(16) unsigned char storage[64] = {};
            g_OgreFn_AabbCtor6(
                storage,
                substitute[0], substitute[1], substitute[2],
                substitute[3], substitute[4], substitute[5]);
            g_OgreFn_MeshSetBoundsOriginal(mesh, storage, pad);
            ReportRestoreBoundsIfDue();
            return;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // Fall through and let the stock call happen.
        }
    }

    if (g_OgreFn_MeshSetBoundsOriginal)
        g_OgreFn_MeshSetBoundsOriginal(mesh, bounds, pad);
    ReportRestoreBoundsIfDue();
}

static void __fastcall EntityUpdateRenderQueueHook(
    void* entity, void* /*unusedEdx*/, void* renderQueue)
{
    if (t_EntityFrustumCullSuppress)
    {
        // This entity's world bounds were tested against the current camera and
        // found entirely outside it. Submitting nothing is the whole point.
        return;
    }
    if (g_OgreFn_EntityUpdateRenderQueueOriginal)
        g_OgreFn_EntityUpdateRenderQueueOriginal(entity, renderQueue);
}

static void ReportFrustumCullIntervalIfDue()
{
    const DWORD now = GetTickCount();
    if (g_FrustumCullLogTick == 0)
    {
        g_FrustumCullLogTick = now;
        return;
    }
    const DWORD windowMs = static_cast<DWORD>(now - g_FrustumCullLogTick);
    if (windowMs < 1000)
        return;

    const uint64_t tested = g_FrustumCullTested - g_FrustumCullTestedAtLastLog;
    const uint64_t culled = g_FrustumCullCulled - g_FrustumCullCulledAtLastLog;
    const uint64_t recovered = g_FrustumCullRecovered - g_FrustumCullRecoveredAtLastLog;
    const uint64_t unrecoverable =
        g_FrustumCullUnrecoverable - g_FrustumCullUnrecoverableAtLastLog;
    const uint64_t shadowSkipped =
        g_FrustumCullShadowSkipped - g_FrustumCullShadowSkippedAtLastLog;
    const uint64_t nonEntity = g_FrustumCullNonEntity - g_FrustumCullNonEntityAtLastLog;
    g_FrustumCullLogTick = now;
    g_FrustumCullTestedAtLastLog = g_FrustumCullTested;
    g_FrustumCullCulledAtLastLog = g_FrustumCullCulled;
    g_FrustumCullRecoveredAtLastLog = g_FrustumCullRecovered;
    g_FrustumCullUnrecoverableAtLastLog = g_FrustumCullUnrecoverable;
    g_FrustumCullShadowSkippedAtLastLog = g_FrustumCullShadowSkipped;
    g_FrustumCullNonEntityAtLastLog = g_FrustumCullNonEntity;

    LogShimA(
        LogLevel::Info,
        "frustumcull",
        "[FRUSTUMCULL] windowMs=%lu tested=%llu culled=%llu (%.1f%%) "
        "recoveredBounds=%llu ineligible=%llu nonEntity=%llu shadowPassSkipped=%llu "
        "rememberedMeshes=%u margin=%.2f",
        static_cast<unsigned long>(windowMs),
        static_cast<unsigned long long>(tested),
        static_cast<unsigned long long>(culled),
        tested ? (100.0 * static_cast<double>(culled) / static_cast<double>(tested)) : 0.0,
        static_cast<unsigned long long>(recovered),
        static_cast<unsigned long long>(unrecoverable),
        static_cast<unsigned long long>(nonEntity),
        static_cast<unsigned long long>(shadowSkipped),
        g_RememberedMeshBoundsUsed,
        g_FrustumCullMargin);

    if (g_FrustumCullCensusEnabled)
        DumpFrustumCullCensus();
}

static void __fastcall ProcessVisibleObjectHook(
    void* renderQueue,
    void* /*unusedEdx*/,
    void* movableObject,
    void* camera,
    bool onlyShadowCasters,
    void* visibleBounds)
{
    bool cull = false;
    int extentKind = -1;
    bool recovered = false;

    if (g_EntityFrustumCullEnabled && !g_EntityFrustumCullStoodDown &&
        movableObject && camera &&
        g_OgreFn_CameraIsVisibleBox && g_OgreFn_MovableGetWorldBoundingBox)
    {
        if (onlyShadowCasters)
        {
            // Shadow-caster traversal. Deliberately untouched in this version so
            // every cascade, caster and cascade transition stays bit-identical.
            ++g_FrustumCullShadowSkipped;
        }
        else if (!IsOgreEntityObject(movableObject))
        {
            // Not an Entity, so suppression could not take effect even if the
            // object were outside the frustum. Skip the test entirely.
            ++g_FrustumCullNonEntity;
        }
        else
        {
            switch (DecideFrustumCull(movableObject, camera, extentKind, recovered))
            {
            case FrustumCullOutcome::Cull:
                ++g_FrustumCullTested;
                ++g_FrustumCullCulled;
                cull = true;
                break;
            case FrustumCullOutcome::Submit:
                ++g_FrustumCullTested;
                break;
            case FrustumCullOutcome::Ineligible:
                ++g_FrustumCullUnrecoverable;
                break;
            }
            if (recovered)
                ++g_FrustumCullRecovered;
            if (g_FrustumCullCensusEnabled)
                RecordFrustumCullCensus(movableObject, extentKind, cull, recovered);
        }
    }

    // The original always runs, so _notifyCurrentCamera and the visibleBounds
    // bookkeeping that feeds PSSM cascade fitting are unchanged. Only
    // Entity::_updateRenderQueue is suppressed, and only for this object.
    const bool previous = t_EntityFrustumCullSuppress;
    t_EntityFrustumCullSuppress = cull;
    if (g_OgreFn_ProcessVisibleObjectOriginal)
    {
        g_OgreFn_ProcessVisibleObjectOriginal(
            renderQueue, movableObject, camera, onlyShadowCasters, visibleBounds);
    }
    t_EntityFrustumCullSuppress = previous;

    ReportFrustumCullIntervalIfDue();
}

// -------------------------------------------------------------- install -----

static void InstallEntityFrustumCullingIfEnabled()
{
    if (g_EntityFrustumCullInstalled)
        return;
    if (!g_EntityFrustumCullEnabled && !g_RestoreCraftBoundsEnabled)
        return;
    if (!GetModuleHandleA("OgreMain.dll"))
        return;
    g_EntityFrustumCullInstalled = true;

    if (const char* marginText = std::getenv("OPENSHIM_FRUSTUM_CULL_MARGIN"))
    {
        const double parsed = std::atof(marginText);
        if (parsed >= 0.0 && parsed <= 4.0)
            g_FrustumCullMargin = static_cast<float>(parsed);
    }
    if (const char* scaleText = std::getenv("OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE"))
    {
        // 1.0 is the asset's own box; 2.0 reproduces Redux's own scale(2,2,2).
        const double parsed = std::atof(scaleText);
        if (parsed >= 1.0 && parsed <= 8.0)
            g_RestoreCraftBoundsScale = static_cast<float>(parsed);
    }
    if (const char* scopeText = std::getenv("OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE"))
    {
        // "shared" (default) leaves dedicated first-person models infinite;
        // "all" repairs every mesh whose serializer box was observed.
        g_RestoreCraftBoundsAllMeshes = (std::strcmp(scopeText, "all") == 0);
    }
    if (const char* modeText = std::getenv("OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE"))
    {
        // "pin" (default) also clamps Redux's per-spawn doubling; "infinite"
        // touches nothing but the EXTENT_INFINITE write itself; "observe"
        // changes nothing at all and only traces.
        g_RestoreCraftBoundsObserveOnly = (std::strcmp(modeText, "observe") == 0);
        g_RestoreCraftBoundsPin =
            (std::strcmp(modeText, "infinite") != 0) && !g_RestoreCraftBoundsObserveOnly;
    }

    void* const processVisibleObjectBody = ResolveOgreExportBody(
        "?processVisibleObject@RenderQueue@Ogre@@QAEXPAVMovableObject@2@PAVCamera@2@_NPAUVisibleObjectsBoundsInfo@2@@Z");
    void* const entityUpdateRenderQueueBody = ResolveOgreExportBody(
        "?_updateRenderQueue@Entity@Ogre@@UAEXPAVRenderQueue@2@@Z");
    void* const meshSetBoundsBody = ResolveOgreExportBody(
        "?_setBounds@Mesh@Ogre@@QAEXABVAxisAlignedBox@2@_N@Z");
    g_OgreFn_CameraIsVisibleBox = reinterpret_cast<FnOgreCameraIsVisibleBox>(
        ResolveOgreExportBody(
            "?isVisible@Camera@Ogre@@UBE_NABVAxisAlignedBox@2@PAW4FrustumPlane@2@@Z"));
    g_OgreFn_MovableGetWorldBoundingBox =
        reinterpret_cast<FnOgreMovableGetWorldBoundingBox>(ResolveOgreExportBody(
            "?getWorldBoundingBox@MovableObject@Ogre@@UBEABVAxisAlignedBox@2@_N@Z"));
    g_OgreFn_MovableGetFullTransform =
        reinterpret_cast<FnOgreMovableGetFullTransform>(ResolveOgreExportBody(
            "?_getParentNodeFullTransform@MovableObject@Ogre@@UBEABVMatrix4@2@XZ"));
    g_OgreFn_EntityGetMeshPtr = reinterpret_cast<FnOgreEntityGetMeshPtr>(
        ResolveOgreExportBody("?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ"));
    g_OgreFn_MeshGetBounds = reinterpret_cast<FnOgreMeshGetBoundsQuery>(
        ResolveOgreExportBody("?getBounds@Mesh@Ogre@@QBEABVAxisAlignedBox@2@XZ"));
    g_OgreFn_ResourceGetName = reinterpret_cast<FnOgreResourceGetName>(
        ResolveOgreExportBody(
            "?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
    g_OgreFn_AabbCtor6 = reinterpret_cast<FnOgreAabbCtor6>(
        ResolveOgreExportBody("??0AxisAlignedBox@Ogre@@QAE@MMMMMM@Z"));
    g_OgreFn_MovableGetParentSceneNode =
        reinterpret_cast<FnOgreMovableGetParentSceneNode>(ResolveOgreExportBody(
            "?getParentSceneNode@MovableObject@Ogre@@UBEPAVSceneNode@2@XZ"));
    g_OgreFn_NodeGetParent = reinterpret_cast<FnOgreNodeGetParent>(
        ResolveOgreExportBody("?getParent@Node@Ogre@@UBEPAV12@XZ"));
    g_OgreFn_SceneNodeGetWorldAabb = reinterpret_cast<FnOgreSceneNodeGetWorldAabb>(
        ResolveOgreExportBody("?_getWorldAABB@SceneNode@Ogre@@UBEABVAxisAlignedBox@2@XZ"));

    const bool cullExportsReady =
        processVisibleObjectBody && entityUpdateRenderQueueBody &&
        g_OgreFn_CameraIsVisibleBox && g_OgreFn_MovableGetWorldBoundingBox &&
        g_OgreFn_MovableGetFullTransform && g_OgreFn_EntityGetMeshPtr;
    const bool restoreExportsReady =
        meshSetBoundsBody && g_OgreFn_AabbCtor6 && g_OgreFn_ResourceGetName;

    if (g_RestoreCraftBoundsEnabled && !restoreExportsReady)
    {
        g_RestoreCraftBoundsEnabled = false;
        LogShimA(
            LogLevel::Warn,
            "frustumcull",
            "[RESTOREBOUNDS] required Ogre exports unavailable (setBounds=%s "
            "aabbCtor=%s resourceName=%s); bounds restoration stood down",
            meshSetBoundsBody ? "yes" : "no",
            g_OgreFn_AabbCtor6 ? "yes" : "no",
            g_OgreFn_ResourceGetName ? "yes" : "no");
    }
    if (!g_EntityFrustumCullEnabled && !g_RestoreCraftBoundsEnabled)
    {
        g_EntityFrustumCullStoodDown = true;
        return;
    }
    if (!meshSetBoundsBody || (g_EntityFrustumCullEnabled && !cullExportsReady))
    {
        g_EntityFrustumCullStoodDown = true;
        LogShimA(
            LogLevel::Warn,
            "frustumcull",
            "[FRUSTUMCULL] required Ogre exports unavailable (process=%s entityRq=%s "
            "setBounds=%s isVisible=%s worldAabb=%s transform=%s getMesh=%s); "
            "culling stood down",
            processVisibleObjectBody ? "yes" : "no",
            entityUpdateRenderQueueBody ? "yes" : "no",
            meshSetBoundsBody ? "yes" : "no",
            g_OgreFn_CameraIsVisibleBox ? "yes" : "no",
            g_OgreFn_MovableGetWorldBoundingBox ? "yes" : "no",
            g_OgreFn_MovableGetFullTransform ? "yes" : "no",
            g_OgreFn_EntityGetMeshPtr ? "yes" : "no");
        return;
    }

    // Byte guards anchor on whole instructions at the function body, not on an
    // operand, so a different OgreMain build stands the feature down instead of
    // corrupting a mid-instruction boundary.
    //
    // push ebp; mov ebp,esp; push esi; mov esi,[ebp+8]   -- 7 bytes
    static const uint8_t kExpectedProcessVisibleObject[] =
    {
        0x55, 0x8B, 0xEC, 0x56, 0x8B, 0x75, 0x08
    };
    // push ebp; mov ebp,esp; sub esp,0x10                -- 6 bytes
    static const uint8_t kExpectedEntityUpdateRenderQueue[] =
    {
        0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10
    };
    // push ebp; mov ebp,esp; mov edx,[ebp+8]             -- 6 bytes
    static const uint8_t kExpectedMeshSetBounds[] =
    {
        0x55, 0x8B, 0xEC, 0x8B, 0x55, 0x08
    };

    struct DetourRequest
    {
        const char* name;
        InlineDetour32* detour;
        void* body;
        void* hook;
        const uint8_t* expected;
        size_t expectedLength;
    };
    // Mesh::_setBounds is needed by both features. The other two exist only
    // to suppress submissions, so with restoration alone they are not patched
    // and the render traversal keeps its stock instruction stream.
    const DetourRequest allRequests[] =
    {
        { "Mesh::_setBounds", &g_MeshSetBoundsDetour, meshSetBoundsBody,
          reinterpret_cast<void*>(MeshSetBoundsHook),
          kExpectedMeshSetBounds, sizeof(kExpectedMeshSetBounds) },
        { "Entity::_updateRenderQueue", &g_EntityUpdateRenderQueueDetour,
          entityUpdateRenderQueueBody,
          reinterpret_cast<void*>(EntityUpdateRenderQueueHook),
          kExpectedEntityUpdateRenderQueue, sizeof(kExpectedEntityUpdateRenderQueue) },
        { "RenderQueue::processVisibleObject", &g_ProcessVisibleObjectDetour,
          processVisibleObjectBody,
          reinterpret_cast<void*>(ProcessVisibleObjectHook),
          kExpectedProcessVisibleObject, sizeof(kExpectedProcessVisibleObject) },
    };
    const size_t requestCount = g_EntityFrustumCullEnabled ? 3u : 1u;

    for (size_t index = 0; index < requestCount; ++index)
    {
        const DetourRequest& request = allRequests[index];
        if (InstallInlineDetour32(
                *request.detour,
                reinterpret_cast<uintptr_t>(request.body),
                request.hook,
                request.expectedLength,
                request.expected,
                request.expectedLength))
        {
            continue;
        }
        // Any hook that did install stays installed but is inert: with no
        // processVisibleObject hook nothing ever sets the suppression flag, and
        // remembering asset bounds has no effect on its own.
        g_EntityFrustumCullStoodDown = true;
        g_RestoreCraftBoundsEnabled = false;
        LogShimA(
            LogLevel::Warn,
            "frustumcull",
            "[FRUSTUMCULL] %s guard mismatch at 0x%p; culling stood down",
            request.name,
            request.body);
        return;
    }

    g_OgreFn_MeshSetBoundsOriginal = reinterpret_cast<FnOgreMeshSetBounds>(
        g_MeshSetBoundsDetour.trampoline);
    if (g_EntityFrustumCullEnabled)
    {
        g_OgreFn_EntityUpdateRenderQueueOriginal =
            reinterpret_cast<FnOgreEntityUpdateRenderQueueBody>(
                g_EntityUpdateRenderQueueDetour.trampoline);
        g_OgreFn_ProcessVisibleObjectOriginal =
            reinterpret_cast<FnOgreProcessVisibleObject>(
                g_ProcessVisibleObjectDetour.trampoline);
    }

    LogShimA(
        LogLevel::Info,
        "frustumcull",
        "[FRUSTUMCULL] installed privateCull=%s restoreBounds=%s margin=%.2f "
        "restoreScale=%.2f restoreScope=%s restoreMode=%s trace=%s "
        "processVisibleObject=0x%p entityUpdateRenderQueue=0x%p meshSetBounds=0x%p "
        "optOut=OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING",
        g_EntityFrustumCullEnabled ? "on" : "off",
        g_RestoreCraftBoundsEnabled ? "on" : "off",
        g_FrustumCullMargin,
        g_RestoreCraftBoundsScale,
        g_RestoreCraftBoundsAllMeshes ? "all" : "shared",
        g_RestoreCraftBoundsObserveOnly
            ? "observe"
            : (g_RestoreCraftBoundsPin ? "pin" : "infinite"),
        g_BoundsTraceEnabled ? "on" : "off",
        g_EntityFrustumCullEnabled ? processVisibleObjectBody : nullptr,
        g_EntityFrustumCullEnabled ? entityUpdateRenderQueueBody : nullptr,
        meshSetBoundsBody);
}
