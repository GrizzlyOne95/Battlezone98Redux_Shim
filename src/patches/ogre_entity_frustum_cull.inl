// SPDX-License-Identifier: MIT
//
// Copyright (C) 2026 BZR Open Shim contributors
//
// Main-view frustum culling for craft whose Ogre bounds were made infinite.
//
// The defect
// ----------
// Battlezone 98 Redux gives every craft mesh an infinite Ogre bounding box at
// runtime. Measured, from the opt-in census below:
//
//     type=Ogre::Entity extent=2 meshExtent=2 sampleMesh=avtank.mesh
//
// `extent=2` is `AxisAlignedBox::EXTENT_INFINITE`, and `meshExtent=2` places it
// on `Mesh::getBounds()` itself rather than on an attachment. The shipped asset
// is fine -- `avtank.mesh` declares min=(-3.16,-0.06,-3.74) max=(3.16,2.76,2.96)
// radius=4.27 in its M_MESH_BOUNDS chunk -- so something overwrites those bounds
// after load. Terrain entities keep finite bounds (`RenderableTileCluster_*`,
// extent=1), so this is specific to craft, not global.
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
// frame no matter where the camera points. This is also why an earlier profiling
// pass found vehicle submissions unchanged at 50 m, 250 m and 1000 m.
//
// What this does
// --------------
// It does not modify any Ogre state. `Mesh::_setBounds` is observed, not
// altered: the last *finite* box each mesh was given -- which is the box the
// mesh serializer set from the asset -- is remembered in a fixed-size table.
// When an entity would otherwise be untestable because its world box is
// infinite, that remembered local box is inflated by a safety margin,
// transformed by the entity's own node transform, and tested against the
// camera's frustum with Ogre's own `Camera::isVisible`.
//
// Restoring the finite bounds globally was considered and rejected: Redux may
// depend on infinite craft bounds for scene queries such as targeting or
// picking, and this optimization must not change gameplay behaviour to buy
// frame time. Keeping the recovered box private to the cull decision means the
// only observable delta is which renderables reach the render queue.
//
// Scope, deliberately narrow for a first implementation:
//
//   * Main-camera traversals only (`onlyShadowCasters == false`). Shadow passes
//     are counted but never culled, so every cascade, every caster and every
//     cascade transition is bit-identical to stock. The shadow half is left for
//     separate work with its own validation.
//   * Entities only. Particle systems, billboard sets and manual objects keep
//     their exact stock submission behaviour.
//   * Suppression is done by making `Entity::_updateRenderQueue` a no-op for the
//     one object being processed, while the original `processVisibleObject` runs
//     in full. The `visibleBounds->merge()` bookkeeping that feeds PSSM cascade
//     fitting is therefore bit-identical by construction rather than replicated.
//
// Skipping `Entity::_updateRenderQueue` also skips the `updateAnimation()` call
// at its tail. That is correct rather than incidental: an entity animates iff it
// is submitted to at least one camera, and shadow passes never cull here, so any
// entity that casts a shadow still animates.
//
// Fail-safe throughout: unresolved exports or a byte-guard mismatch stand the
// feature down permanently; a null box, an infinite box with no remembered
// asset bounds, a missing node transform, or a fault anywhere in the decision
// all submit the object.
//
// Opt-outs:
//   OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1   disable entirely
//   OPENSHIM_FRUSTUM_CULL_MARGIN=<float>        half-extent safety margin
//                                               (default 0.25 = 25%)
//   OPENSHIM_FRUSTUM_CULL_CENSUS=1              per-type bounds census at 1 Hz

// ---------------------------------------------------------------- state -----

static bool g_EntityFrustumCullEnabled = false;
static bool g_EntityFrustumCullInstalled = false;
static bool g_EntityFrustumCullStoodDown = false;
static bool g_FrustumCullCensusEnabled = false;
static float g_FrustumCullMargin = 0.25f;

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

// --------------------------------------------- remembered asset bounds ------
//
// Fixed capacity, no allocation on any hot path, no unbounded growth. A mesh
// that does not fit simply never gets a recovered box, so its entities are
// submitted exactly as they are today.

struct RememberedMeshBounds
{
    const void* mesh = nullptr;
    float minimum[3] = {};
    float maximum[3] = {};
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
            "seen=%llu recovered=%llu culled=%llu",
            slot.typeName[0] ? slot.typeName : "<unknown>",
            slot.extentKind,
            slot.sampleMeshExtent,
            slot.sampleMesh[0] ? slot.sampleMesh : "<none>",
            static_cast<unsigned long long>(slot.seen),
            static_cast<unsigned long long>(slot.recovered),
            static_cast<unsigned long long>(slot.culled));
        slot.seen = 0;
        slot.culled = 0;
        slot.recovered = 0;
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

static void __fastcall MeshSetBoundsHook(
    void* mesh, void* /*unusedEdx*/, const void* bounds, bool pad)
{
    // Observe only. The asset's finite box is captured on its way past so the
    // cull decision has something to fall back on once Redux replaces it with
    // an infinite one; Ogre's own state is left exactly as Redux wants it.
    if (bounds)
    {
        __try
        {
            const auto* box = static_cast<const float*>(bounds);
            uint32_t extent = 0;
            std::memcpy(&extent, box + 6, sizeof(extent));
            if (extent == 1u)
                RememberMeshBounds(mesh, box);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    if (g_OgreFn_MeshSetBoundsOriginal)
        g_OgreFn_MeshSetBoundsOriginal(mesh, bounds, pad);
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
    if (g_EntityFrustumCullInstalled || !g_EntityFrustumCullEnabled)
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

    if (!processVisibleObjectBody || !entityUpdateRenderQueueBody ||
        !meshSetBoundsBody || !g_OgreFn_CameraIsVisibleBox ||
        !g_OgreFn_MovableGetWorldBoundingBox || !g_OgreFn_MovableGetFullTransform ||
        !g_OgreFn_EntityGetMeshPtr)
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
    const DetourRequest requests[] =
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

    for (const DetourRequest& request : requests)
    {
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
    g_OgreFn_EntityUpdateRenderQueueOriginal =
        reinterpret_cast<FnOgreEntityUpdateRenderQueueBody>(
            g_EntityUpdateRenderQueueDetour.trampoline);
    g_OgreFn_ProcessVisibleObjectOriginal =
        reinterpret_cast<FnOgreProcessVisibleObject>(
            g_ProcessVisibleObjectDetour.trampoline);

    LogShimA(
        LogLevel::Info,
        "frustumcull",
        "[FRUSTUMCULL] main-view Entity frustum culling installed margin=%.2f "
        "processVisibleObject=0x%p entityUpdateRenderQueue=0x%p meshSetBounds=0x%p "
        "optOut=OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING",
        g_FrustumCullMargin,
        processVisibleObjectBody,
        entityUpdateRenderQueueBody,
        meshSetBoundsBody);
}
