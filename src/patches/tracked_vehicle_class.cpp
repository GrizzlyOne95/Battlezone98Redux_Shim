#include "tracked_vehicle_class.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "mru_class.h"
#include "net_tag_dispatch.h"
#include "pond_class_label.h"
#include "shim_log.h"
#include "tracked_vehicle_net.h"
#include "tracked_vehicle_physics.h"
#include "tracked_vehicle_treads.h"
#include "tracked_vehicle_turret.h"

#include <Windows.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>

// classLabel = "tracked" (Docs/TRACKED_VEHICLES.md).
//
// A tracked ODF is built by the stock HoverCraftClass (4CC 'HOVR' and rank
// kept, label stamped "tracked") and each object it builds gets an OpenShim
// copy of the HoverCraft vtable whose Simulate slot runs the contact model in
// tracked_vehicle_physics.h instead of the hover force model. Every other
// slot is a jmp through the stock vtable entry, so in-place rewrites of the
// stock table (the slot-38 shot-convergence wrapper) still apply.
//
// GOG Redux 2.2.301 layout used below, all read from the shipping exe:
// HoverCraft::Simulate (0x004EBFD0) reads the control block through +0x230,
// the class through +0xF8, the pilot at +0xFC, obj76 at +0xF4 (flags +0x14,
// matrix +0x20, posit doubles +0x48) and the drive keys at class
// +0x328..+0x344, and ends by integrating the EULER block (speed +0x11C,
// veloc +0x12C, omega +0x138, accel +0x144, alpha +0x150), setting the aim
// pitch at +0x280 and calling Craft::Simulate. TrackedSimulate repeats that
// tail exactly.
//
// Treads (phase 2): the PostSimulate slot runs the stock HoverCraft
// PostSimulate first, then drives the entity's "tread_L"/"tread_R" skeleton
// clips and an ODF treadSound loop from the commanded tread speeds the
// contact model returns. The stock vehicle shaders (base.program) bind no
// texture matrix, so a UV scroll would not show; a per-Entity
// AnimationState also never touches the shared mesh or material. Slots 0, 3
// and 4 release the loop, as the stock HoverCraft cleanup (0x004EE8F0) does
// from slots 3 and 4.
//
// Turret (phase 2b): with [TrackedClass] turretName set, the object's root
// transform is the turret and the hull is a counter-rotated child pose
// (tracked_vehicle_turret.h). Camera, reticle, stock weapon aim
// (HoverCraft::UpdateWeaponAim 0x004EB590 poses each weapon node against
// the root) and the stock AI steering then all act on the turret. Simulate
// slews the turret from the steer control, runs the contact model on the
// hull frame from strafe/throttle (player) or from the AI's move intent,
// and re-poses the root's direct children and the turret node through the
// model-node sync 0x00681A00, as the stock TurretTank Simulate does.
//
// Multiplayer (phase 3): the owner runs everything above. On a remote
// replica (network game and DistributedObject::IsRemote) the stock
// GameObject::Simulate 0x004DEEC0 calls slot 15 in up to five net-dt
// sub-steps from the last received pose; there the contact model and the
// hull rule are skipped, accel and alpha are zeroed and the stock tail
// integrates the replicated veloc/omega (dead reckoning). Tread speeds come
// from that motion on the hull frame. The turret angle is not replicated by
// the engine: the owner queues it per object (PostSimulate, frame dt) and
// broadcasts one 'T','Y' batch per frame, records keyed by the stock
// dwLocalID (tracked_vehicle_net.h); a replica slews its displayed angle
// toward the received one.

namespace BZROpenShim
{
    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
        void* ResolveOgreProcRaw(const char* name);
    }

    namespace
    {
        namespace TP = TrackedPhysics;
        namespace TT = TrackedTreads;
        namespace TU = TrackedTurret;
        namespace TN = TrackedNet;

        constexpr char kTrackedClassLabel[] = "tracked";
        constexpr char kHoverClassLabel[] = "hover";
        constexpr char kComponent[] = "TRACKED";

        // GameObjectClass.
        constexpr size_t kClassLabelOffset = 0x18;
        constexpr size_t kClassPackedNameOffset = 0x30;
        constexpr size_t kClassBoxMinOffset = 0x10C;
        constexpr size_t kClassBoxMaxOffset = 0x118;
        // HoverCraftClass drive keys.
        constexpr size_t kClassVelocForward = 0x328;
        constexpr size_t kClassVelocReverse = 0x32C;
        constexpr size_t kClassAccelThrust = 0x334;
        constexpr size_t kClassAccelBrake = 0x338;
        constexpr size_t kClassOmegaSpin = 0x33C;
        constexpr size_t kClassOmegaTurn = 0x340;
        constexpr size_t kClassAlphaSteer = 0x344;
        // HoverCraftClass soundThrust/soundTurbo/soundFly, char[16] each
        // (HoverCraft::UpdateSounds 0x004EEA20 passes them to Sound::Find
        // and PlayGlobalSound).
        constexpr size_t kClassSoundThrust = 0x5A0;
        constexpr size_t kClassSoundTurbo = 0x5B0;
        constexpr size_t kClassSoundFly = 0x5C0;
        constexpr size_t kSoundNameBytes = 16;

        // HoverCraft object.
        constexpr size_t kObjInterface = 0x18;
        // Render root: passed to the floor query as "not me", and its +0x94
        // is the Ogre::Entity (satellite_visibility.cpp, from EXU's
        // GameObject::GetOgreEntity).
        constexpr size_t kObjFloorIgnore = 0xF0;
        constexpr size_t kRenderRootEntity = 0x94;
        constexpr size_t kObjObj76 = 0xF4;
        constexpr size_t kObjClass = 0xF8;
        constexpr size_t kObjPilot = 0xFC;
        constexpr size_t kObjSpeed = 0x11C;
        constexpr size_t kObjVeloc = 0x12C;
        constexpr size_t kObjOmega = 0x138;
        constexpr size_t kObjAccel = 0x144;
        constexpr size_t kObjAlpha = 0x150;
        constexpr size_t kObjHealthRatio = 0x200;
        constexpr size_t kObjControls = 0x230;
        constexpr size_t kObjAimPitch = 0x280;
        constexpr size_t kObjThrustRatio = 0x2B0;
        constexpr size_t kObjThrottleVisual = 0x2B4;
        constexpr size_t kObjAirborne = 0x2B8;

        // obj76. Model nodes share the layout: name char[8] at +0x08,
        // local MAT_3D at +0x20 (posit doubles at +0x48), parent +0x78, next
        // sibling +0x7C, first child +0x80 (TurretTank::FindTurret
        // 0x005F2130 walks the same links).
        constexpr size_t kObj76Name = 0x08;
        constexpr size_t kObj76NameBytes = 8;
        constexpr size_t kObj76Parent = 0x78;
        constexpr size_t kObj76Sibling = 0x7C;
        constexpr size_t kObj76Child = 0x80;
        constexpr size_t kObj76Flags = 0x14;
        // Set on the user's craft: the aim-pitch gate, and UpdateSounds
        // starts that craft's loops at priority 0x41 instead of 0x2D.
        constexpr uint32_t kObj76FlagAimGate = 0x10;
        constexpr uint32_t kObj76FlagDead = 0x200;
        constexpr size_t kObj76Right = 0x20;
        constexpr size_t kObj76Up = 0x2C;
        constexpr size_t kObj76Front = 0x38;
        constexpr size_t kObj76Posit = 0x48;
        // Collision box min y. The engine's terrain collision (0x004AA1D0)
        // probes the box face centres from obj76+0xB0..+0xC4, the bottom one
        // at (0, +0xB4, 0); stock hover clearance is +0xB4 + posit.y - 0.2 - floor.
        constexpr size_t kObj76FloorOffset = 0xB4;

        // Control block.
        constexpr size_t kCtrlSteer = 0xC4;
        constexpr size_t kCtrlPitch = 0xC8;
        constexpr size_t kCtrlStrafe = 0xCC;  // +1 moves right
        constexpr size_t kCtrlThrottle = 0xD0;
        constexpr size_t kCtrlEyepoint = 0xFC;
        constexpr size_t kCtrlFlags = 0x114;
        constexpr uint32_t kCtrlFlagAimGate = 0x1000;

        // HoverCraftVtable (0x0087ABE4) has 42 slots; the next dword is the
        // "trundepl.wav" string. Slot 15 Simulate, 16 PostSimulate. Slot 39
        // (0x004A8AB0, __thiscall(this, float dt), ret 4) moves the posit by
        // veloc * dt and resolves collisions; the stock tail skips its second
        // half-step when it returns nonzero.
        constexpr size_t kHoverVtableSlots = 42;
        constexpr size_t kSimulateSlot = 15;
        constexpr size_t kIntegrateSlot = 39;
        constexpr size_t kThunkStride = 8;
        // Slot 0 (0x004E9EC0) is the scalar deleting destructor,
        // __thiscall(this, flags), ret 4. Slots 3 (0x004EA2B0) and 4
        // (0x004EA2E0) are __thiscall(this), ret, and both run the stock
        // sound cleanup 0x004EE8F0. Slot 16 (0x004EE780) is PostSimulate,
        // __thiscall(this, float dt), ret 4: past 150 m from the camera it
        // runs that cleanup, else UpdateGimbals 0x004EA300 and UpdateSounds
        // 0x004EEA20, then Craft::PostSimulate.
        constexpr size_t kDestructorSlot = 0;
        constexpr size_t kCleanupSlotA = 3;
        constexpr size_t kCleanupSlotB = 4;
        constexpr size_t kPostSimulateSlot = 16;

        // Stock PostSimulate's sound cutoff: camera posit doubles at
        // GetCameraRecord()+0x160, 150 m (22500.0f at 0x008A2E2C).
        constexpr size_t kCameraPositOffset = 0x160;
        constexpr double kSoundCutoffSq = 22500.0;

        // GAS start blocks as UpdateSounds fills them (0x004EEBA5..): control
        // flags 0x4001 at +0x10; prep priority at +0x04, loop mode 1 at +0x0C.
        constexpr size_t kSoundControlBytes = 0x2C;
        constexpr size_t kSoundPrepBytes = 0x1C;
        constexpr size_t kSoundControlFlags = 0x10;
        constexpr uint32_t kSoundControlLoopFlags = 0x4001;
        constexpr size_t kSoundPrepPriority = 0x04;
        constexpr size_t kSoundPrepLoopMode = 0x0C;
        constexpr uint32_t kSoundPriorityUser = 0x41;
        constexpr uint32_t kSoundPriorityOther = 0x2D;
        constexpr int kSoundUnchanged = -2;
        // PostSimulate calls to wait after PlayGlobalSound returns null.
        constexpr uint32_t kSoundRetryFrames = 60;
        // Seconds under the gate before a playing loop stops (muted meanwhile).
        constexpr float kSoundHoldSeconds = 1.5f;

        constexpr size_t kDetourLength = 5;
        const uint8_t kDetourPrologue[kDetourLength] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };

        using FnBuildClass = void* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnBuild = void* (__thiscall*)(void*, void*);
        using FnSimulate = void (__thiscall*)(void*, float);
        using FnByteThis = uint8_t (__thiscall*)(void*);
        using FnIntegrate = uint8_t (__thiscall*)(void*, float);
        using FnIntVoid = int (__cdecl*)();
        using FnOpenScope = void* (__thiscall*)(void*, const char*);
        using FnRawGet = const char* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnPopScope = void (__thiscall*)(void*);
        using FnFloorQuery = void (__cdecl*)(int ignore, double x, double y, double z,
                                             float* floorY, TP::Vec3* normal, int* floorObject);
        using FnDestructor = void* (__thiscall*)(void*, unsigned int);
        using FnThisVoid = void (__thiscall*)(void*);

        using FnSoundInit = void (__cdecl*)(void* block);
        using FnSoundPlay = void* (__cdecl*)(const char* name, void* owner, void* control, void* prep);
        using FnSoundSetParams = int (__cdecl*)(void* sound, int volume, int pan, int rate);
        using FnSoundStop = void (__cdecl*)(void* sound);
        using FnSoundFind = void* (__cdecl*)(const char* name, void* owner);
        using FnCameraRecord = const uint8_t* (__cdecl*)();
        // Obj76::SyncNode 0x00681A00: copies a node's local MAT_3D to its
        // Ogre bone/node pair at +0xC8/+0xCC.
        using FnSyncNode = void (__cdecl*)(void* node, void* local);

        using FnEntityHasAnimation = bool (__thiscall*)(void*, const std::string&);
        using FnEntityGetAnimation = void* (__thiscall*)(void*, const std::string&);
        using FnAnimFloat = float (__thiscall*)(void*);
        using FnAnimAddTime = void (__thiscall*)(void*, float);
        using FnAnimSetBool = void (__thiscall*)(void*, bool);
        using FnAnimGetBool = bool (__thiscall*)(void*);
        using FnEntityGetSkeleton = void* (__thiscall*)(void*);
        using FnSkeletonGetBlend = int (__thiscall*)(void*);
        using FnSkeletonSetBlend = void (__thiscall*)(void*, int);

        // Multiplayer. DistributedObject::IsRemote 0x004B9830 and
        // DistributedObject::GetLocalID 0x004B9A90 are __thiscall on the
        // DistributedObject subobject (GameObject + 0x18). Net::BroadcastSend
        // 0x00575890 is called (buf, len, 1, 1) as mp_splinter_sync.cpp does.
        using FnIdThis = uint32_t (__thiscall*)(void*);
        using FnBroadcastSend = char (__cdecl*)(const void* buf, unsigned len, int p3, char p4);

        InlineDetour32 g_BuildClassDetour;
        InlineDetour32 g_BuildDetour;
        FnBuildClass g_OriginalBuildClass = nullptr;
        FnBuild g_OriginalBuild = nullptr;
        FnSimulate g_StockSimulate = nullptr;
        FnSimulate g_CraftSimulate = nullptr;
        FnSimulate g_UpdateEyepoint = nullptr;
        FnIntVoid g_AimGlobalGate = nullptr;
        FnByteThis g_AimModeGate = nullptr;
        FnOpenScope g_OpenScope = nullptr;
        FnRawGet g_RawGet = nullptr;
        FnPopScope g_PopScope = nullptr;
        FnFloorQuery g_FloorQuery = nullptr;
        FnSyncNode g_SyncNode = nullptr;  // null: turretName is ignored

        // Treads: all bound or none (g_TreadsReady).
        FnSoundInit g_SoundInitControl = nullptr;
        FnSoundInit g_SoundInitPrep = nullptr;
        FnSoundPlay g_SoundPlay = nullptr;
        FnSoundSetParams g_SoundSetParams = nullptr;
        FnSoundStop g_SoundStop = nullptr;
        FnSoundFind g_SoundFind = nullptr;
        FnCameraRecord g_CameraRecord = nullptr;
        FnEntityHasAnimation g_EntityHasAnimation = nullptr;
        FnEntityGetAnimation g_EntityGetAnimation = nullptr;
        FnAnimFloat g_AnimGetLength = nullptr;
        FnAnimFloat g_AnimGetTime = nullptr;
        FnAnimAddTime g_AnimAddTime = nullptr;
        FnAnimSetBool g_AnimSetEnabled = nullptr;
        FnAnimSetBool g_AnimSetLoop = nullptr;
        FnAnimGetBool g_AnimGetEnabled = nullptr;
        FnEntityGetSkeleton g_EntityGetSkeleton = nullptr;
        FnSkeletonGetBlend g_SkeletonGetBlend = nullptr;
        FnSkeletonSetBlend g_SkeletonSetBlend = nullptr;
        uintptr_t g_OgreEntityVtable = 0;
        bool g_TreadsReady = false;
        volatile long g_TreadFaultLogged = 0;

        // Remote gate: both or none (g_RemoteGateReady); without it every
        // object runs the owner model, as before phase 3.
        FnByteThis g_IsRemote = nullptr;
        uintptr_t g_NetGameFlag = 0;
        bool g_RemoteGateReady = false;
        // Turret sync: needs the remote gate, Obj76::SyncNode, the id
        // accessor, the send and the 'T','Y' receive handler.
        FnIdThis g_GetLocalId = nullptr;
        FnBroadcastSend g_BroadcastSend = nullptr;
        bool g_TurretSyncReady = false;
        volatile long g_NetLogBudget = 200;
        volatile long g_ReplicaTraceBudget = 400;
        volatile long g_ReplicaTraceCounter = 0;

        // Clip names follow BZCC's tread_L / tread_R (Ogre names are
        // case-sensitive). Globals: the __try callers cannot hold objects
        // that unwind.
        const std::string g_ClipLeft("tread_L");
        const std::string g_ClipRight("tread_R");

        uintptr_t g_HoverVtable = 0;
        // [0] is the stock RTTI locator, so the copy still reads as
        // .?AVHoverCraft@@; the object's vptr points at [1].
        void* g_TrackedVtable[kHoverVtableSlots + 1] = {};
        uint8_t* g_Thunks = nullptr;
        bool g_Installed = false;
        bool g_InstallFailureLogged = false;

        thread_local bool g_TrackedBuildPending = false;

        struct TrackedClassData
        {
            TP::Config config;
            TP::Footprint footprint;
            char treadSound[kSoundNameBytes] = {};
            float treadCycleLength = TT::kDefaultCycleLength;
            char turretName[kObj76NameBytes + 1] = {};  // empty: no turret
            TU::Config turret;
        };

        // Per object, keyed by the object pointer: reset at Build, erased
        // by the destructor slot.
        struct TreadState
        {
            float commandLeft = 0.0f;   // contact model's commanded tread speeds
            float commandRight = 0.0f;
            float left = 0.0f;          // visual tread speeds
            float right = 0.0f;
            void* entity = nullptr;     // entity the clip lookup last saw
            int clips = -1;             // clips found on it: bit 0 L, bit 1 R; -1 unseen
            void* sound = nullptr;
            void* soundOwner = nullptr;
            char soundName[kSoundNameBytes] = {};
            uint32_t soundRetry = 0;
            float soundQuiet = 0.0f;    // seconds in a row under the sound gate
        };

        SRWLOCK g_TreadLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, TreadState> g_Treads;

        // Turret: per object, keyed by the object pointer; reset at Build,
        // erased by the destructor slot. Not saved: a loaded game starts
        // with the hull under the turret (delta 0).
        constexpr int kMaxRootChildren = 16;
        constexpr int kMaxModelNodes = 512;
        constexpr int kTurretUnseen = -1;
        constexpr int kTurretMissing = 0;
        constexpr int kTurretFound = 1;

        struct NodePose
        {
            TU::Mat3 rot;
            double pos[3];
        };

        struct TurretState
        {
            float delta = 0.0f;   // turret yaw relative to the hull, + left
            float rate = 0.0f;    // its slew rate, rad/s
            TN::SendState send;   // owner: last 'T','Y' broadcast
            bool netApplied = false;  // replica: a received angle was used
            float applied = 0.0f; // delta the nodes were last posed at
            bool posed = false;
            int status = kTurretUnseen;
            uint8_t* root = nullptr;
            uint8_t* turret = nullptr;
            bool direct = false;  // turret is a direct child of the root
            int childCount = 0;
            uint8_t* children[kMaxRootChildren] = {};
            NodePose childRest[kMaxRootChildren] = {};
            NodePose turretRest = {};
            TU::Mat3 parentRest;  // turret's parent chain to the root, at rest
        };

        SRWLOCK g_TurretLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, TurretState> g_Turrets;
        volatile long g_TurretLogBudget = 200;

        volatile long g_TreadLogBudget = 200;
        volatile long g_TreadTraceBudget = 1500;
        constexpr long kTreadTraceEvery = 23;  // prime, so several tracked units alternate
        volatile long g_TreadTraceCounter = 0;

        // Keyed by class pointer. An entry is only used while that class
        // still carries the "tracked" label pointer, so a stale entry for a
        // freed class whose address is reused by another class is ignored;
        // a reused address that is tracked again is overwritten at BuildClass.
        SRWLOCK g_ClassDataLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, TrackedClassData> g_ClassData;

        volatile long g_TraceBudget = 400;
        volatile long g_TraceCounter = 0;
        constexpr long kTraceEvery = 21;  // odd, so several tracked units alternate

        bool IsExecutableAddress(uintptr_t address)
        {
            MEMORY_BASIC_INFORMATION info = {};
            if (!address || VirtualQuery(reinterpret_cast<const void*>(address), &info, sizeof(info)) != sizeof(info))
                return false;
            if (info.State != MEM_COMMIT)
                return false;
            const DWORD protect = info.Protect & 0xFF;
            return protect == PAGE_EXECUTE || protect == PAGE_EXECUTE_READ ||
                protect == PAGE_EXECUTE_READWRITE || protect == PAGE_EXECUTE_WRITECOPY;
        }

        bool IsTrackedClass(const void* objectClass)
        {
            if (!objectClass)
                return false;
            __try
            {
                return *reinterpret_cast<const char* const*>(
                    reinterpret_cast<const uint8_t*>(objectClass) + kClassLabelOffset) == kTrackedClassLabel;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // context carries the object's obj+0xF0 value, as the stock hover
        // passes it, so the craft never stands on itself.
        bool FloorAt(void* context, double x, double y, double z, double& height, TP::Vec3& normal)
        {
            if (!g_FloorQuery)
                return false;
            float floorY = 0.0f;
            TP::Vec3 n{ 0.0f, 1.0f, 0.0f };
            int floorObject = 0;
            __try
            {
                g_FloorQuery(static_cast<int>(reinterpret_cast<intptr_t>(context)), x, y, z, &floorY, &n, &floorObject);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!std::isfinite(floorY) || std::fabs(floorY) >= 1.0e6f || !TP::Finite(n))
                return false;
            height = floorY;
            normal = n;
            return true;
        }

        // ---- class construction --------------------------------------------

        constexpr size_t kRawValueBytes = 32;
        struct RawTrackedKeys
        {
            char stiffness[kRawValueBytes];
            char damping[kRawValueBytes];
            char contactsPerSide[kRawValueBytes];
            char lateralFriction[kRawValueBytes];
            char maxSlope[kRawValueBytes];
            char treadSound[kRawValueBytes];
            char treadCycleLength[kRawValueBytes];
            char turretName[kRawValueBytes];
            char yawRate[kRawValueBytes];
            char omegaTurret[kRawValueBytes];
            char yawAlpha[kRawValueBytes];
            char alphaTurret[kRawValueBytes];
            char yawMin[kRawValueBytes];
            char yawMax[kRawValueBytes];
        };

        void CopyRaw(const char* value, char (&out)[kRawValueBytes])
        {
            out[0] = 0;
            if (!value)
                return;
            for (size_t i = 0; i + 1 < kRawValueBytes; ++i)
            {
                out[i] = value[i];
                if (!value[i])
                    return;
            }
            out[kRawValueBytes - 1] = 0;
        }

        // Opens the ODF's ParameterDB scope (a cache hit: GameObjectClass::Find
        // holds its own scope on the same file across BuildClass) and copies
        // the [TrackedClass] values out before popping it.
        bool ReadTrackedKeys(const char* odfFile, RawTrackedKeys& keys)
        {
            std::memset(&keys, 0, sizeof(keys));
            void* scope = nullptr;
            __try
            {
                g_OpenScope(&scope, odfFile);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!scope)
                return false;

            bool ok = true;
            __try
            {
                constexpr uint32_t section = TP::OdfHash("TrackedClass");
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("stiffness")), keys.stiffness);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("damping")), keys.damping);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("contactsPerSide")), keys.contactsPerSide);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("lateralFriction")), keys.lateralFriction);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("maxSlope")), keys.maxSlope);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("treadSound")), keys.treadSound);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("treadCycleLength")), keys.treadCycleLength);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("turretName")), keys.turretName);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawRate")), keys.yawRate);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("omegaTurret")), keys.omegaTurret);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawAlpha")), keys.yawAlpha);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("alphaTurret")), keys.alphaTurret);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawMin")), keys.yawMin);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawMax")), keys.yawMax);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            __try
            {
                g_PopScope(&scope);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            return ok;
        }

        void ParseFloatKey(const char* raw, float& value)
        {
            if (!raw || !*raw)
                return;
            char* end = nullptr;
            const float parsed = std::strtof(raw, &end);
            if (end != raw && std::isfinite(parsed))
                value = parsed;
        }

        void ParseIntKey(const char* raw, int& value)
        {
            if (!raw || !*raw)
                return;
            char* end = nullptr;
            const long parsed = std::strtol(raw, &end, 10);
            if (end != raw)
                value = static_cast<int>(parsed);
        }

        // treadSound = "name.wav", turretName = "node": the quotes are
        // optional. False when the name does not fit out (the char[16] the
        // stock sound names use, the char[8] of a model node name).
        template<size_t N>
        bool ParseNameKey(const char* raw, char (&out)[N])
        {
            out[0] = 0;
            if (!raw)
                return true;
            while (*raw == ' ' || *raw == '\t' || *raw == '"')
                ++raw;
            size_t n = 0;
            while (raw[n] && raw[n] != '"' && raw[n] != ' ' && raw[n] != '\t' && raw[n] != '\r' && raw[n] != '\n')
            {
                if (n + 1 >= N)
                {
                    out[0] = 0;
                    return false;
                }
                out[n] = raw[n];
                ++n;
            }
            out[n] = 0;
            return true;
        }

        // The stock cleanup and turbo stop find their loops by (name, owner),
        // so a treadSound equal to one of them would be stopped by the stock
        // code, and ours would stop theirs.
        bool SoundNameClashes(const void* objectClass, const char* name, const char*& clash)
        {
            static constexpr size_t kOffsets[] = { kClassSoundThrust, kClassSoundTurbo, kClassSoundFly };
            static const char* const kKeys[] = { "soundThrust", "soundTurbo", "soundFly" };
            for (size_t i = 0; i < 3; ++i)
            {
                char stock[kSoundNameBytes] = {};
                __try
                {
                    std::memcpy(stock, reinterpret_cast<const uint8_t*>(objectClass) + kOffsets[i], sizeof(stock));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    clash = "unreadable class";
                    return true;
                }
                stock[kSoundNameBytes - 1] = 0;
                if (_stricmp(stock, name) == 0)
                {
                    clash = kKeys[i];
                    return true;
                }
            }
            return false;
        }

        bool StampTrackedClass(void* objectClass, uint32_t& odfLo, uint32_t& odfHi,
                               TP::Vec3& boxMin, TP::Vec3& boxMax)
        {
            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectClass);
                *reinterpret_cast<const char**>(bytes + kClassLabelOffset) = kTrackedClassLabel;
                std::memcpy(&odfLo, bytes + kClassPackedNameOffset, sizeof(odfLo));
                std::memcpy(&odfHi, bytes + kClassPackedNameOffset + 4, sizeof(odfHi));
                std::memcpy(&boxMin, bytes + kClassBoxMinOffset, sizeof(boxMin));
                std::memcpy(&boxMax, bytes + kClassBoxMaxOffset, sizeof(boxMax));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void ConfigureTrackedClass(void* objectClass, uint32_t nameLo, uint32_t nameHi)
        {
            uint32_t odfLo = nameLo;
            uint32_t odfHi = nameHi;
            TP::Vec3 boxMin{ 0.0f, 0.0f, 0.0f };
            TP::Vec3 boxMax{ 0.0f, 0.0f, 0.0f };
            if (!StampTrackedClass(objectClass, odfLo, odfHi, boxMin, boxMax))
            {
                LogShimA(LogLevel::Warn, kComponent, "HoverCraftClass returned an unreadable class object");
                return;
            }

            char odfName[9] = {};
            std::memcpy(odfName, &nameLo, sizeof(nameLo));
            std::memcpy(odfName + 4, &nameHi, sizeof(nameHi));
            char odfFile[16] = {};
            std::snprintf(odfFile, sizeof(odfFile), "%.8s.odf", odfName);

            TrackedClassData data{};
            RawTrackedKeys keys{};
            if (ReadTrackedKeys(odfFile, keys))
            {
                ParseFloatKey(keys.stiffness, data.config.stiffness);
                ParseFloatKey(keys.damping, data.config.damping);
                ParseIntKey(keys.contactsPerSide, data.config.contactsPerSide);
                ParseFloatKey(keys.lateralFriction, data.config.lateralFriction);
                ParseFloatKey(keys.maxSlope, data.config.maxSlopeDeg);
                ParseFloatKey(keys.treadCycleLength, data.treadCycleLength);
                if (!ParseNameKey(keys.treadSound, data.treadSound))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "ODF %.8s: treadSound longer than %u characters; no tread sound",
                        odfName, static_cast<unsigned>(kSoundNameBytes - 1));
                }
                const char* clash = nullptr;
                if (data.treadSound[0] && SoundNameClashes(objectClass, data.treadSound, clash))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "ODF %.8s: treadSound %s is also %s; no tread sound", odfName, data.treadSound, clash);
                    data.treadSound[0] = 0;
                }
                if (!ParseNameKey(keys.turretName, data.turretName))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "ODF %.8s: turretName longer than %u characters; no turret",
                        odfName, static_cast<unsigned>(kObj76NameBytes));
                }
                // BZCC AssaultTankClass names, with the BZ1 TurretTankClass
                // omegaTurret/alphaTurret as fallbacks.
                ParseFloatKey(keys.omegaTurret, data.turret.yawRate);
                ParseFloatKey(keys.yawRate, data.turret.yawRate);
                ParseFloatKey(keys.alphaTurret, data.turret.yawAlpha);
                ParseFloatKey(keys.yawAlpha, data.turret.yawAlpha);
                ParseFloatKey(keys.yawMin, data.turret.yawMin);
                ParseFloatKey(keys.yawMax, data.turret.yawMax);
            }
            else
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: [TrackedClass] could not be read; using defaults", odfName);
            }
            data.config = TP::Sanitize(data.config);
            data.footprint = TP::FootprintFromBox(boxMin, boxMax);
            data.treadCycleLength = TT::SanitizeCycleLength(data.treadCycleLength);
            const bool limitKeySet = (std::isfinite(data.turret.yawMin) && data.turret.yawMin > -1.0e29f) ||
                                     (std::isfinite(data.turret.yawMax) && data.turret.yawMax < 1.0e29f);
            data.turret = TU::Sanitize(data.turret);
            if (data.turretName[0] && limitKeySet && !data.turret.limited)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: yawMin/yawMax ignored; they are radians with yawMin <= 0 <= yawMax inside +-pi",
                    odfName);
            }
            if (data.turretName[0] && !g_SyncNode)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: turretName ignored (Obj76::SyncNode did not resolve); plain tracked", odfName);
                data.turretName[0] = 0;
            }

            AcquireSRWLockExclusive(&g_ClassDataLock);
            g_ClassData[reinterpret_cast<uintptr_t>(objectClass)] = data;
            ReleaseSRWLockExclusive(&g_ClassDataLock);

            LogShimA(LogLevel::Info, kComponent,
                "built ODF %.8s as tracked class=%p stiffness=%.1f damping=%.1f contactsPerSide=%d "
                "lateralFriction=%.2f maxSlope=%.1f footprint x=%.2f+-%.2f z=%.2f..%.2f y=%.2f "
                "treadSound=%s treadCycleLength=%.2f",
                odfName, objectClass,
                data.config.stiffness, data.config.damping, data.config.contactsPerSide,
                data.config.lateralFriction, data.config.maxSlopeDeg,
                data.footprint.centerX, data.footprint.halfWidth,
                data.footprint.backZ, data.footprint.frontZ, data.footprint.bottomY,
                data.treadSound[0] ? data.treadSound : "-", data.treadCycleLength);
            if (data.turretName[0])
            {
                LogShimA(LogLevel::Info, kComponent,
                    "ODF %.8s: turret node %s yawRate=%.2f yawAlpha=%.2f limits=%s%.2f..%.2f",
                    odfName, data.turretName, data.turret.yawRate, data.turret.yawAlpha,
                    data.turret.limited ? "" : "none ", data.turret.yawMin, data.turret.yawMax);
            }
        }

        void* __fastcall HoverBuildClassHook(void* thisPtr, void* /*edx*/, uint32_t odfNameLo, uint32_t odfNameHi)
        {
            // Armed by the label compare that immediately precedes this call
            // in GameObjectClass::Find; cleared before the stock constructor
            // so nested class lookups stay ordinary.
            const bool tracked = g_TrackedBuildPending;
            g_TrackedBuildPending = false;
            // classLabel = mru rides on the same detour (mru_class.cpp).
            const bool mru = TakeMruBuildPending();

            void* objectClass = g_OriginalBuildClass(thisPtr, odfNameLo, odfNameHi);
            if (tracked && objectClass)
                ConfigureTrackedClass(objectClass, odfNameLo, odfNameHi);
            else if (mru && objectClass)
                ConfigureMruClass(objectClass, odfNameLo, odfNameHi);
            return objectClass;
        }

        bool SwapToTrackedVtable(void* object)
        {
            __try
            {
                auto* vptr = reinterpret_cast<uintptr_t*>(object);
                if (*vptr != g_HoverVtable)
                    return false;
                *vptr = reinterpret_cast<uintptr_t>(&g_TrackedVtable[1]);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void ReleaseTreads(const void* object, bool erase);

        void ResetTreadState(const void* object)
        {
            // A stale entry at a reused address may still own a loop.
            ReleaseTreads(object, true);
            AcquireSRWLockExclusive(&g_TreadLock);
            g_Treads[reinterpret_cast<uintptr_t>(object)] = TreadState{};
            ReleaseSRWLockExclusive(&g_TreadLock);
        }

        void ReleaseTurret(const void* object)
        {
            AcquireSRWLockExclusive(&g_TurretLock);
            g_Turrets.erase(reinterpret_cast<uintptr_t>(object));
            ReleaseSRWLockExclusive(&g_TurretLock);
        }

        void* __fastcall HoverBuildHook(void* objectClass, void* /*edx*/, void* arg)
        {
            void* object = g_OriginalBuild(objectClass, arg);
            if (object && IsTrackedClass(objectClass))
            {
                if (!SwapToTrackedVtable(object))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "tracked class %p built object %p without the HoverCraft vtable; left as hover",
                        objectClass, object);
                }
                else
                {
                    // A stale entry at a reused address would carry its delta.
                    ReleaseTurret(object);
                    if (g_TreadsReady)
                        ResetTreadState(object);
                }
            }
            else if (object)
            {
                OnHoverObjectBuilt(objectClass, object);
            }
            return object;
        }

        // ---- simulation ------------------------------------------------------

        struct TraceSample
        {
            float floorOffset;  // obj76+0xB4
            float originFloor;  // posit.y - floor under the origin
            TP::Vec3 floorNormal;
            TP::Vec3 groundNormal;
            double pyBefore;
            float clearance;
            float speed;
            float forward;
            TP::Vec3 omega;
            float slope;
            float traction;
            int grounded;
            float leftTread;
            float rightTread;
            // Turret objects only.
            float hullSteer;
            float hullThrottle;
            float turretCommand;
            float rootYaw;  // degrees, world: atan2(front.x, front.z)
            float hullYaw;
        };

        // One turret step: Simulate fills the inputs from TurretState,
        // ComputeTrackedForces the outputs.
        struct TurretStep
        {
            TU::Config config;
            float delta = 0.0f;
            float rate = 0.0f;
            float newDelta = 0.0f;
            float newRate = 0.0f;
        };

        float YawDegrees(TP::Vec3 front)
        {
            return std::atan2(front.x, front.z) * (180.0f / TU::kPi);
        }

        TP::Vec3 ReadVec(const uint8_t* base, size_t offset)
        {
            TP::Vec3 v;
            std::memcpy(&v, base + offset, sizeof(v));
            return v;
        }

        void WriteVec(uint8_t* base, size_t offset, TP::Vec3 v)
        {
            std::memcpy(base + offset, &v, sizeof(v));
        }

        // Replaces the hover force model: reads the inputs and body state,
        // runs the contact step, writes accel/alpha and the hover visuals.
        // turret: null for a plain tracked object. With it the root frame is
        // the turret's and the contact model runs on the hull frame.
        bool ComputeTrackedForces(uint8_t* self, float dt, const TrackedClassData& data, TraceSample& trace,
                                  TurretStep* turret)
        {
            __try
            {
                uint8_t* obj76 = *reinterpret_cast<uint8_t**>(self + kObjObj76);
                const uint8_t* cls = *reinterpret_cast<uint8_t**>(self + kObjClass);
                uint8_t* ctrl = *reinterpret_cast<uint8_t**>(self + kObjControls);
                if (!obj76 || !cls || !ctrl)
                    return false;

                const bool dead = (*reinterpret_cast<const uint32_t*>(obj76 + kObj76Flags) & kObj76FlagDead) != 0;
                const bool piloted = *reinterpret_cast<void* const*>(self + kObjPilot) != nullptr;
                TP::Inputs inputs{};
                if (!piloted || dead)
                {
                    // Stock hover clears steer..jump for an empty, live craft.
                    if (!dead)
                        std::memset(ctrl + kCtrlSteer, 0, 6 * sizeof(uint32_t));
                }
                else
                {
                    inputs.throttle = *reinterpret_cast<const float*>(ctrl + kCtrlThrottle);
                    inputs.steer = *reinterpret_cast<const float*>(ctrl + kCtrlSteer);
                    if (!TP::Finite(inputs.throttle)) inputs.throttle = 0.0f;
                    if (!TP::Finite(inputs.steer)) inputs.steer = 0.0f;
                    if (turret)
                    {
                        // Steer slews the turret. The user's strafe keys turn
                        // the hull; an AI pilot's throttle/strafe is a move
                        // intent in the turret frame that the hull follows.
                        float strafe = *reinterpret_cast<const float*>(ctrl + kCtrlStrafe);
                        if (!TP::Finite(strafe)) strafe = 0.0f;
                        const bool user = (*reinterpret_cast<const uint32_t*>(obj76 + kObj76Flags) &
                                           kObj76FlagAimGate) != 0;
                        trace.turretCommand = inputs.steer;
                        const TU::HullCommand hull = user ? TU::PlayerHull(inputs.throttle, strafe)
                                                          : TU::AiHull(inputs.throttle, strafe, turret->delta);
                        inputs.throttle = hull.throttle;
                        inputs.steer = hull.steer;
                    }
                }

                const float perf = TP::PerformanceScale(*reinterpret_cast<const float*>(self + kObjHealthRatio));
                TP::Drive drive;
                drive.velocForward = perf * *reinterpret_cast<const float*>(cls + kClassVelocForward);
                drive.velocReverse = perf * *reinterpret_cast<const float*>(cls + kClassVelocReverse);
                drive.accelThrust = perf * *reinterpret_cast<const float*>(cls + kClassAccelThrust);
                drive.accelBrake = perf * *reinterpret_cast<const float*>(cls + kClassAccelBrake);
                drive.omegaSpin = perf * *reinterpret_cast<const float*>(cls + kClassOmegaSpin);
                drive.omegaTurn = perf * *reinterpret_cast<const float*>(cls + kClassOmegaTurn);
                drive.alphaSteer = perf * *reinterpret_cast<const float*>(cls + kClassAlphaSteer);

                TP::Body body;
                body.right = ReadVec(obj76, kObj76Right);
                body.up = ReadVec(obj76, kObj76Up);
                body.front = ReadVec(obj76, kObj76Front);
                const double* posit = reinterpret_cast<const double*>(obj76 + kObj76Posit);
                body.px = posit[0];
                body.py = posit[1];
                body.pz = posit[2];
                body.veloc = ReadVec(self, kObjVeloc);
                body.omega = ReadVec(self, kObjOmega);
                if (turret)
                {
                    trace.rootYaw = YawDegrees(body.front);
                    TU::HullAxes(body.right, body.front, turret->delta, body.right, body.front);
                    body.omega = TU::RootToHullOmega(body.omega, turret->delta, turret->rate);
                    turret->newRate = TU::SlewRate(turret->config, turret->rate, trace.turretCommand,
                                                   turret->delta, dt);
                    // Trapezoid: the root yaws by the mid-step omega.
                    turret->newDelta = TU::AdvanceDelta(turret->config, turret->delta,
                                                        0.5f * (turret->rate + turret->newRate), dt);
                    trace.hullYaw = YawDegrees(body.front);
                    trace.hullSteer = inputs.steer;
                    trace.hullThrottle = inputs.throttle;
                }

                void* floorContext = reinterpret_cast<void*>(
                    static_cast<intptr_t>(*reinterpret_cast<const int*>(self + kObjFloorIgnore)));
                const float floorOffset = *reinterpret_cast<const float*>(obj76 + kObj76FloorOffset);
                TP::Footprint footprint = data.footprint;
                footprint.bottomY = TP::ContactBottom(floorOffset, data.footprint.bottomY, data.config);

                const TP::Result result = TP::Step(data.config, footprint, drive, body, inputs, dt,
                                                   &FloorAt, floorContext);
                WriteVec(self, kObjVeloc, result.veloc);
                WriteVec(self, kObjAccel, result.accel);
                WriteVec(self, kObjAlpha, turret
                    ? TU::HullToRootAlpha(result.alpha, turret->delta, turret->newRate - turret->rate, dt)
                    : result.alpha);
                *reinterpret_cast<float*>(self + kObjThrustRatio) = 1.0f;
                *reinterpret_cast<float*>(self + kObjThrottleVisual) =
                    inputs.steer * inputs.steer * 0.5f + std::fabs(inputs.throttle);
                *reinterpret_cast<float*>(self + kObjAirborne) = 1.0f - result.groundedFraction;

                double ground = 0.0;
                TP::Vec3 groundNormal{ NAN, NAN, NAN };
                // Trace-only floor query: skip it once the trace budget is spent.
                const bool haveFloor = g_TraceBudget > 0 &&
                    FloorAt(floorContext, body.px, body.py, body.pz, ground, groundNormal);
                trace.floorOffset = floorOffset;
                trace.originFloor = haveFloor ? static_cast<float>(body.py - ground) : NAN;
                trace.floorNormal = groundNormal;
                trace.groundNormal = result.groundNormal;
                trace.pyBefore = body.py;
                trace.clearance = haveFloor ? static_cast<float>(body.py + footprint.bottomY - ground) : NAN;
                trace.speed = TP::Length(body.veloc);
                trace.forward = TP::Dot(body.veloc, body.front);
                trace.omega = body.omega;
                trace.slope = result.slopeDeg;
                trace.traction = result.traction;
                trace.grounded = result.groundedContacts;
                trace.leftTread = result.leftTread;
                trace.rightTread = result.rightTread;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The stock HoverCraft::Simulate tail, from 0x004EE68B: finish the
        // half-step integration, update the eyepoint and aim pitch, then
        // run Craft::Simulate.
        void FinishSimulate(uint8_t* self, float dt)
        {
            const float half = dt * 0.5f;
            TP::Vec3 veloc = ReadVec(self, kObjVeloc);
            TP::Vec3 omega = ReadVec(self, kObjOmega);
            const TP::Vec3 accel = ReadVec(self, kObjAccel);
            const TP::Vec3 alpha = ReadVec(self, kObjAlpha);
            veloc = TP::Add(veloc, TP::Scale(accel, half));
            omega = TP::Add(omega, TP::Scale(alpha, half));
            WriteVec(self, kObjVeloc, veloc);
            WriteVec(self, kObjOmega, omega);

            void** vtable = *reinterpret_cast<void***>(self);
            if (reinterpret_cast<FnIntegrate>(vtable[kIntegrateSlot])(self, dt) == 0)
            {
                // Re-read: the collision pass may have changed them.
                veloc = ReadVec(self, kObjVeloc);
                omega = ReadVec(self, kObjOmega);
                veloc = TP::Add(veloc, TP::Scale(accel, half));
                omega = TP::Add(omega, TP::Scale(alpha, half));
                WriteVec(self, kObjVeloc, veloc);
                WriteVec(self, kObjOmega, omega);
                *reinterpret_cast<float*>(self + kObjSpeed) = TP::Length(veloc);
            }

            uint8_t* ctrl = *reinterpret_cast<uint8_t**>(self + kObjControls);
            const uint8_t* obj76 = *reinterpret_cast<uint8_t**>(self + kObjObj76);
            if (*reinterpret_cast<const uint32_t*>(ctrl + kCtrlEyepoint) != 0)
                g_UpdateEyepoint(self, dt);

            *reinterpret_cast<float*>(self + kObjAimPitch) = *reinterpret_cast<const float*>(ctrl + kCtrlPitch) * 0.5f;
            if (((*reinterpret_cast<const uint32_t*>(obj76 + kObj76Flags) & kObj76FlagAimGate) != 0 &&
                 g_AimGlobalGate() != 0) ||
                (g_AimModeGate(self + kObjInterface) != 0 &&
                 (*reinterpret_cast<const uint32_t*>(ctrl + kCtrlFlags) & kCtrlFlagAimGate) != 0))
            {
                *reinterpret_cast<float*>(self + kObjAimPitch) -=
                    *reinterpret_cast<const float*>(obj76 + kObj76Front + 4);
            }

            g_CraftSimulate(self, dt);
        }

        uintptr_t ReadObjectClass(const uint8_t* self)
        {
            __try
            {
                return *reinterpret_cast<const uintptr_t*>(self + kObjClass);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool LookupClassData(const uint8_t* self, TrackedClassData& out)
        {
            const uintptr_t cls = ReadObjectClass(self);
            if (!IsTrackedClass(reinterpret_cast<const void*>(cls)))
                return false;
            bool found = false;
            AcquireSRWLockShared(&g_ClassDataLock);
            const auto it = g_ClassData.find(cls);
            if (it != g_ClassData.end())
            {
                out = it->second;
                found = true;
            }
            ReleaseSRWLockShared(&g_ClassDataLock);
            if (!found)
                out = TrackedClassData{};
            return true;
        }

        void SetTreadCommand(const void* object, float left, float right)
        {
            AcquireSRWLockExclusive(&g_TreadLock);
            TreadState& state = g_Treads[reinterpret_cast<uintptr_t>(object)];
            state.commandLeft = left;
            state.commandRight = right;
            ReleaseSRWLockExclusive(&g_TreadLock);
        }

        // ---- turret nodes ------------------------------------------------------

        uint8_t* NodeLink(const uint8_t* node, size_t offset)
        {
            return *reinterpret_cast<uint8_t* const*>(node + offset);
        }

        void NodeName(const uint8_t* node, char (&out)[kObj76NameBytes + 1])
        {
            std::memcpy(out, node + kObj76Name, kObj76NameBytes);
            out[kObj76NameBytes] = 0;
        }

        NodePose ReadPose(const uint8_t* node)
        {
            NodePose pose;
            std::memcpy(&pose.rot, node + kObj76Right, sizeof(pose.rot));
            std::memcpy(pose.pos, node + kObj76Posit, sizeof(pose.pos));
            return pose;
        }

        void WritePose(uint8_t* node, const NodePose& pose)
        {
            std::memcpy(node + kObj76Right, &pose.rot, sizeof(pose.rot));
            std::memcpy(node + kObj76Posit, pose.pos, sizeof(pose.pos));
            g_SyncNode(node, node + kObj76Right);
        }

        // Finds the turret node under root and records the root's direct
        // children and the rest poses. Leaves state.status at kTurretFound
        // or kTurretMissing; why names the failure.
        void FindTurretNodes(uint8_t* root, const char* name, TurretState& state, const char*& why)
        {
            const float delta = state.delta;
            const float rate = state.rate;
            const TN::SendState send = state.send;
            const bool netApplied = state.netApplied;
            state = TurretState{};
            state.delta = delta;
            state.rate = rate;
            state.send = send;
            state.netApplied = netApplied;
            state.root = root;
            state.status = kTurretMissing;
            why = "node not in the model";
            __try
            {
                uint8_t* stack[kMaxModelNodes];
                int top = 0;
                int visited = 0;
                uint8_t* first = NodeLink(root, kObj76Child);
                if (first)
                    stack[top++] = first;
                while (top > 0 && !state.turret)
                {
                    uint8_t* node = stack[--top];
                    if (++visited > kMaxModelNodes)
                    {
                        why = "model has too many nodes";
                        return;
                    }
                    char nodeName[kObj76NameBytes + 1];
                    NodeName(node, nodeName);
                    if (_stricmp(nodeName, name) == 0)
                    {
                        state.turret = node;
                        break;
                    }
                    uint8_t* sibling = NodeLink(node, kObj76Sibling);
                    uint8_t* child = NodeLink(node, kObj76Child);
                    if (sibling && top < kMaxModelNodes)
                        stack[top++] = sibling;
                    if (child && top < kMaxModelNodes)
                        stack[top++] = child;
                }
                if (!state.turret)
                    return;

                for (uint8_t* child = NodeLink(root, kObj76Child); child; child = NodeLink(child, kObj76Sibling))
                {
                    if (state.childCount >= kMaxRootChildren)
                    {
                        why = "model root has too many children";
                        state.turret = nullptr;
                        return;
                    }
                    state.children[state.childCount] = child;
                    state.childRest[state.childCount] = ReadPose(child);
                    ++state.childCount;
                }

                uint8_t* parent = NodeLink(state.turret, kObj76Parent);
                state.direct = parent == root;
                state.turretRest = ReadPose(state.turret);
                // Parent chain to the root at rest: parent * grandparent * ...
                TU::Mat3 chain;
                int depth = 0;
                for (uint8_t* n = parent; n != root; n = NodeLink(n, kObj76Parent))
                {
                    if (!n || ++depth > kMaxModelNodes)
                    {
                        why = "turret node parent links do not reach the root";
                        state.turret = nullptr;
                        return;
                    }
                    chain = TU::Mul(chain, ReadPose(n).rot);
                }
                state.parentRest = chain;
                state.status = kTurretFound;
                why = nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                state.turret = nullptr;
                state.status = kTurretMissing;
                why = "model nodes unreadable";
            }
        }

        // Hull under the root yawed by delta; the turret kept at its rest
        // heading relative to the root (the turret frame).
        bool PoseTurret(TurretState& state)
        {
            const float delta = state.delta;
            if (state.posed && state.applied == delta)
                return true;
            __try
            {
                const TU::Mat3 yaw = TU::Yaw(delta);
                for (int i = 0; i < state.childCount; ++i)
                {
                    const NodePose& rest = state.childRest[i];
                    NodePose pose;
                    // A direct-child turret keeps its rest heading (root = turret
                    // frame) but rides the hull's ring, so only its position turns.
                    pose.rot = state.direct && state.children[i] == state.turret
                        ? rest.rot
                        : TU::HullChildRotation(rest.rot, delta);
                    pose.pos[0] = rest.pos[0] * yaw.right.x + rest.pos[2] * yaw.front.x;
                    pose.pos[1] = rest.pos[1];
                    pose.pos[2] = rest.pos[0] * yaw.right.z + rest.pos[2] * yaw.front.z;
                    WritePose(state.children[i], pose);
                }
                if (!state.direct)
                {
                    NodePose pose = state.turretRest;
                    pose.rot = TU::TurretRotation(state.turretRest.rot, state.parentRest, delta);
                    WritePose(state.turret, pose);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            state.applied = delta;
            state.posed = true;
            return true;
        }

        void StoreTurret(const uint8_t* self, const TurretState& state);

        bool TakeTurretLogLine()
        {
            return g_TurretLogBudget > 0 && InterlockedDecrement(&g_TurretLogBudget) >= 0;
        }

        // Copies this object's turret state out, finding its nodes on first
        // use and again when the model root changes. Logs each change of
        // outcome once. False: run as plain tracked.
        bool LoadTurret(const uint8_t* self, const char* name, TurretState& state)
        {
            uint8_t* root = nullptr;
            __try
            {
                root = *reinterpret_cast<uint8_t* const*>(self + kObjObj76);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!root)
                return false;

            AcquireSRWLockExclusive(&g_TurretLock);
            state = g_Turrets[reinterpret_cast<uintptr_t>(self)];
            ReleaseSRWLockExclusive(&g_TurretLock);
            if (state.status != kTurretUnseen && state.root == root)
                return state.status == kTurretFound;

            const int before = state.status;
            const char* why = nullptr;
            FindTurretNodes(root, name, state, why);
            if (state.status != before && TakeTurretLogLine())
            {
                if (state.status == kTurretFound)
                {
                    char parentName[kObj76NameBytes + 1] = {};
                    __try
                    {
                        NodeName(NodeLink(state.turret, kObj76Parent), parentName);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        parentName[0] = 0;
                    }
                    LogShimA(LogLevel::Info, kComponent,
                        "obj=%p turret node %s found (parent %s, %s child of the root, %d root children); "
                        "the root frame is the turret",
                        self, name, parentName, state.direct ? "direct" : "nested", state.childCount);
                }
                else
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "obj=%p turret node %s not used: %s; plain tracked", self, name, why ? why : "?");
                }
            }
            StoreTurret(self, state);
            return state.status == kTurretFound;
        }

        void StoreTurret(const uint8_t* self, const TurretState& state)
        {
            AcquireSRWLockExclusive(&g_TurretLock);
            g_Turrets[reinterpret_cast<uintptr_t>(self)] = state;
            ReleaseSRWLockExclusive(&g_TurretLock);
        }

        // ---- multiplayer -------------------------------------------------------

        bool TakeNetLogLine()
        {
            return g_NetLogBudget > 0 && InterlockedDecrement(&g_NetLogBudget) >= 0;
        }

        bool IsNetGame()
        {
            if (!g_RemoteGateReady)
                return false;
            __try
            {
                return *reinterpret_cast<const volatile uint8_t*>(g_NetGameFlag) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // A replica another peer owns. False (the owner model) when the gate
        // did not resolve or the call faults. Trade-off: a fault makes a
        // replica run the owner model (contact physics on stale input, and a
        // turret broadcast under the owner's id) for that frame, rather than
        // leaving it unsimulated; the replicated pose still corrects it.
        bool IsRemoteReplica(uint8_t* self)
        {
            if (!IsNetGame())
                return false;
            __try
            {
                return g_IsRemote(self + kObjInterface) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The stock dwLocalID, the key a Lua handle crosses the network with
        // (lua_handle_sync.cpp): the owner's local map and every replica's
        // remote map hold the object under it. 0: none, or a fault.
        uint32_t ObjectNetId(uint8_t* self)
        {
            if (!g_GetLocalId)
                return 0;
            __try
            {
                return g_GetLocalId(self + kObjInterface);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        bool SafeBroadcast(const uint8_t* packet, unsigned len)
        {
            __try
            {
                g_BroadcastSend(packet, len, 1, 1);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Received turret angles by object id. Filled on the Net::Receive
        // thread and read by the replica's PostSimulate, so the receive side
        // never touches an engine object. A fixed table: storing never
        // allocates, so nothing can throw while the lock is held.
        SRWLOCK g_NetTurretLock = SRWLOCK_INIT;
        TN::ReceivedTable g_NetTurrets;
        bool g_WasNetGame = false;  // main thread: the flag at the last tracked frame

        void StoreNetTurret(uint32_t id, float delta, float rate, uint64_t now)
        {
            AcquireSRWLockExclusive(&g_NetTurretLock);
            g_NetTurrets.Store(id, delta, rate, now);
            ReleaseSRWLockExclusive(&g_NetTurretLock);
        }

        bool LookupNetTurret(uint32_t id, uint64_t now, uint64_t maxAgeMs, TN::ReceivedTurret& out)
        {
            AcquireSRWLockShared(&g_NetTurretLock);
            const bool found = g_NetTurrets.Lookup(id, now, maxAgeMs, out);
            ReleaseSRWLockShared(&g_NetTurretLock);
            return found;
        }

        // Outgoing batch, main thread only (PostSimulate).
        TN::SendBatch g_SendBatch;

        void FlushSendRecords()
        {
            if (g_SendBatch.count == 0)
                return;
            uint8_t buf[TN::kMaxPacketLen];
            const unsigned len = TN::Pack(g_SendBatch.records, g_SendBatch.count, buf);
            const unsigned count = g_SendBatch.count;
            g_SendBatch.ClearRecords();
            if (len && !SafeBroadcast(buf, len) && TakeNetLogLine())
                LogShimA(LogLevel::Warn, kComponent, "turret batch send faulted (%u records)", count);
        }

        // Called at every tracked PostSimulate. When the network-game flag
        // drops (the session ended) the received angles and any unsent batch
        // are dropped, so a later session cannot read them. With no tracked
        // frame between two sessions, the kStaleMs age gate covers it: a
        // mission load takes longer than that.
        void NoteNetGame(bool net)
        {
            if (g_WasNetGame && !net)
            {
                AcquireSRWLockExclusive(&g_NetTurretLock);
                g_NetTurrets.Clear();
                ReleaseSRWLockExclusive(&g_NetTurretLock);
                g_SendBatch.Reset();
            }
            g_WasNetGame = net;
        }

        bool OnTurretMessage(unsigned senderId, const unsigned char* buf, unsigned len)
        {
            TN::TurretBatch batch;
            const TN::UnpackResult result = TN::Unpack(buf, len, batch);
            if (result == TN::UnpackResult::NotOurs)
                return false;
            if (result == TN::UnpackResult::Invalid || batch.rejected)
            {
                if (TakeNetLogLine())
                    LogShimA(LogLevel::Warn, kComponent, "turret message from player %u: %s ignored",
                             senderId & 0xFFFF,
                             result == TN::UnpackResult::Invalid ? "bad header," : "records with a bad value");
                if (result == TN::UnpackResult::Invalid)
                    return true;
            }
            if (g_TurretSyncReady)
            {
                const uint64_t now = GetTickCount64();
                for (unsigned i = 0; i < batch.count; ++i)
                    StoreNetTurret(batch.records[i].id, batch.records[i].delta, batch.records[i].rate, now);
            }
            return true;
        }

        // Replica Simulate: the stock tail on the replicated veloc/omega with
        // no force, and tread speeds from that motion. False on a fault.
        bool PrepareReplica(uint8_t* self, const TrackedClassData& data, float delta, float turretRate,
                            TN::TreadSpeeds& treads)
        {
            __try
            {
                const uint8_t* obj76 = *reinterpret_cast<uint8_t* const*>(self + kObjObj76);
                if (!obj76 || !*reinterpret_cast<void* const*>(self + kObjControls))
                    return false;
                const TP::Vec3 zero{ 0.0f, 0.0f, 0.0f };
                WriteVec(self, kObjAccel, zero);
                WriteVec(self, kObjAlpha, zero);
                treads = TN::ReplicaTreadSpeeds(ReadVec(self, kObjVeloc), ReadVec(obj76, kObj76Right),
                                                ReadVec(obj76, kObj76Front), ReadVec(self, kObjOmega).y,
                                                delta, turretRate, data.footprint.halfWidth);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void SimulateReplica(void* thisPtr, float dt, const TrackedClassData& data)
        {
            auto* self = static_cast<uint8_t*>(thisPtr);
            float delta = 0.0f;
            float turretRate = 0.0f;
            if (data.turretName[0])
            {
                TurretState state;
                if (LoadTurret(self, data.turretName, state))
                    delta = state.delta;
                // The owner's slew rate, not the replica's catch-up rate: the
                // catch-up is display only and must not read as hull turn.
                TN::ReceivedTurret received;
                if (g_TurretSyncReady &&
                    LookupNetTurret(ObjectNetId(self), GetTickCount64(), TN::kRateMaxAgeMs, received))
                {
                    turretRate = received.rate;
                }
            }
            TN::TreadSpeeds treads;
            if (!PrepareReplica(self, data, delta, turretRate, treads))
            {
                if (g_TreadsReady)
                    SetTreadCommand(self, 0.0f, 0.0f);
                g_StockSimulate(thisPtr, dt);
                return;
            }
            if (g_TreadsReady)
                SetTreadCommand(self, treads.left, treads.right);
            FinishSimulate(self, dt);

            if (g_ReplicaTraceBudget > 0 &&
                (InterlockedIncrement(&g_ReplicaTraceCounter) % kTraceEvery) == 1 &&
                InterlockedDecrement(&g_ReplicaTraceBudget) >= 0)
            {
                LogShimA(LogLevel::Debug, kComponent,
                    "replica obj=%p id=0x%08X dt=%.4f treads=(%.2f,%.2f) delta=%.3f",
                    thisPtr, ObjectNetId(self), dt, treads.left, treads.right, delta);
            }
        }

        // Once per frame (PostSimulate, frame dt) for a turret object in a
        // network game: the owner broadcasts its angle; a replica slews its
        // displayed angle toward the last one received and poses the nodes.
        void TurretNetFrame(uint8_t* self, float dt)
        {
            const bool net = IsNetGame();
            NoteNetGame(net);
            if (!g_TurretSyncReady || !net)
                return;
            TrackedClassData data{};
            if (!LookupClassData(self, data) || !data.turretName[0])
                return;
            const uint32_t id = ObjectNetId(self);
            if (!id)
                return;  // not networked: every peer runs its own copy
            TurretState state;
            if (!LoadTurret(self, data.turretName, state))
                return;
            const uint64_t now = GetTickCount64();

            if (!IsRemoteReplica(self))
            {
                // A second visit since the last flush is a new frame: send
                // what the previous frame queued, one message for all.
                if (g_SendBatch.NoteVisit(self))
                {
                    FlushSendRecords();
                    g_SendBatch.Reset();
                    g_SendBatch.NoteVisit(self);
                }
                if (!TN::ShouldSend(state.send, state.delta, state.rate, now))
                    return;
                TN::TurretRecord record;
                record.id = id;
                record.delta = state.delta;
                record.rate = state.rate;
                if (!g_SendBatch.Add(record))
                {
                    FlushSendRecords();
                    g_SendBatch.Add(record);
                }
                if (!state.send.sent && TakeNetLogLine())
                    LogShimA(LogLevel::Info, kComponent, "obj=%p id=0x%08X first turret angle queued delta=%.3f",
                             self, id, state.delta);
                TN::MarkSent(state.send, state.delta, state.rate, now);
                StoreTurret(self, state);
                return;
            }

            TN::ReceivedTurret target;
            const float before = state.delta;
            if (LookupNetTurret(id, now, TN::kStaleMs, target))
            {
                const float age = static_cast<float>(now - target.tickMs) / 1000.0f;
                const float goal = TN::ReplicaTarget(data.turret, target.delta, target.rate, age);
                state.delta = TN::SlewToward(data.turret, state.delta, goal, dt);
                if (!state.netApplied)
                {
                    state.netApplied = true;
                    if (TakeNetLogLine())
                        LogShimA(LogLevel::Info, kComponent,
                                 "obj=%p id=0x%08X replica turret follows the owner (received delta=%.3f)",
                                 self, id, target.delta);
                }
            }
            state.rate = dt > 0.0f ? TU::WrapAngle(state.delta - before) / dt : 0.0f;
            if (!PoseTurret(state))
            {
                state.status = kTurretMissing;
                state.delta = 0.0f;
                state.rate = 0.0f;
                if (TakeTurretLogLine())
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "obj=%p turret node %s could not be posed; plain tracked", self, data.turretName);
                }
            }
            StoreTurret(self, state);
        }

        volatile long g_TurretTraceBudget = 4000;
        volatile long g_TurretTraceCounter = 0;
        constexpr long kTurretTraceEvery = 7;

        void __fastcall TrackedSimulateHook(void* thisPtr, void* /*edx*/, float dt)
        {
            auto* self = static_cast<uint8_t*>(thisPtr);
            TrackedClassData data{};
            TraceSample trace{};
            TurretState turretState;
            TurretStep step;
            bool turret = false;
            const bool tracked = LookupClassData(self, data);
            if (tracked && IsRemoteReplica(self))
            {
                SimulateReplica(thisPtr, dt, data);
                return;
            }
            if (tracked && data.turretName[0])
            {
                turret = LoadTurret(self, data.turretName, turretState);
                step.config = data.turret;
                step.delta = turretState.delta;
                step.rate = turretState.rate;
            }
            if (!tracked ||
                !ComputeTrackedForces(self, dt, data, trace, turret ? &step : nullptr))
            {
                if (g_TreadsReady)
                    SetTreadCommand(self, 0.0f, 0.0f);
                g_StockSimulate(thisPtr, dt);
                return;
            }
            if (turret)
            {
                turretState.delta = step.newDelta;
                turretState.rate = step.newRate;
                if (!PoseTurret(turretState))
                {
                    turretState.status = kTurretMissing;
                    turretState.delta = 0.0f;
                    turretState.rate = 0.0f;
                    if (TakeTurretLogLine())
                    {
                        LogShimA(LogLevel::Warn, kComponent,
                            "obj=%p turret node %s could not be posed; plain tracked", self, data.turretName);
                    }
                }
                StoreTurret(self, turretState);
                if (g_TurretTraceBudget > 0 &&
                    (InterlockedIncrement(&g_TurretTraceCounter) % kTurretTraceEvery) == 1 &&
                    InterlockedDecrement(&g_TurretTraceBudget) >= 0)
                {
                    LogShimA(LogLevel::Debug, kComponent,
                        "obj=%p turret delta=%.3f rate=%.3f cmd=%.2f rootYaw=%.1f hullYaw=%.1f "
                        "hullSteer=%.2f hullThrottle=%.2f",
                        thisPtr, turretState.delta, turretState.rate, trace.turretCommand,
                        trace.rootYaw, trace.hullYaw, trace.hullSteer, trace.hullThrottle);
                }
            }
            if (g_TreadsReady)
                SetTreadCommand(self, trace.leftTread, trace.rightTread);

            const bool logThis = g_TraceBudget > 0 && (InterlockedIncrement(&g_TraceCounter) % kTraceEvery) == 1 &&
                InterlockedDecrement(&g_TraceBudget) >= 0;

            FinishSimulate(self, dt);

            if (logThis)
            {
                LogShimA(LogLevel::Debug, kComponent,
                    "obj=%p clearance=%.3f speed=%.2f forward=%.2f omega=(%.3f,%.3f,%.3f) "
                    "grounded=%d slope=%.1f traction=%.2f dt=%.4f b4=%.3f originFloor=%.3f "
                    "floorN=(%.3f,%.3f,%.3f) planeN=(%.3f,%.3f,%.3f) py=%.4f",
                    thisPtr, trace.clearance, trace.speed, trace.forward,
                    trace.omega.x, trace.omega.y, trace.omega.z,
                    trace.grounded, trace.slope, trace.traction, dt,
                    trace.floorOffset, trace.originFloor,
                    trace.floorNormal.x, trace.floorNormal.y, trace.floorNormal.z,
                    trace.groundNormal.x, trace.groundNormal.y, trace.groundNormal.z,
                    trace.pyBefore);
            }
        }

        // ---- treads -----------------------------------------------------------

        struct TreadContext
        {
            void* obj76 = nullptr;
            bool dead = false;
            bool user = false;
            bool nearCamera = false;
            void* entity = nullptr;
            float velocForward = 0.0f;
            float accelThrust = 0.0f;
            float accelBrake = 0.0f;
        };

        bool ReadTreadContext(const uint8_t* self, TreadContext& ctx)
        {
            __try
            {
                uint8_t* obj76 = *reinterpret_cast<uint8_t* const*>(self + kObjObj76);
                const uint8_t* cls = *reinterpret_cast<const uint8_t* const*>(self + kObjClass);
                if (!obj76 || !cls)
                    return false;
                const uint32_t flags = *reinterpret_cast<const uint32_t*>(obj76 + kObj76Flags);
                ctx.obj76 = obj76;
                ctx.dead = (flags & kObj76FlagDead) != 0;
                ctx.user = (flags & kObj76FlagAimGate) != 0;

                const float perf = TP::PerformanceScale(*reinterpret_cast<const float*>(self + kObjHealthRatio));
                ctx.velocForward = *reinterpret_cast<const float*>(cls + kClassVelocForward);
                ctx.accelThrust = perf * *reinterpret_cast<const float*>(cls + kClassAccelThrust);
                ctx.accelBrake = perf * *reinterpret_cast<const float*>(cls + kClassAccelBrake);

                const uint8_t* camera = g_CameraRecord();
                if (camera)
                {
                    const double* eye = reinterpret_cast<const double*>(camera + kCameraPositOffset);
                    const double* posit = reinterpret_cast<const double*>(obj76 + kObj76Posit);
                    const double dx = posit[0] - eye[0];
                    const double dy = posit[1] - eye[1];
                    const double dz = posit[2] - eye[2];
                    ctx.nearCamera = dx * dx + dy * dy + dz * dz < kSoundCutoffSq;
                }

                const uint8_t* root = *reinterpret_cast<const uint8_t* const*>(self + kObjFloorIgnore);
                if (root)
                {
                    void* entity = *reinterpret_cast<void* const*>(root + kRenderRootEntity);
                    if (entity && *reinterpret_cast<const uintptr_t*>(entity) == g_OgreEntityVtable)
                        ctx.entity = entity;
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // 1 = clip driven, 0 = the entity has no such clip, -1 = fault.
        // getAnimationState throws for a missing name, so has() goes first.
        int DriveClip(void* entity, const std::string& name, float speed, float dt, float cycleLength,
                      float& timePosition)
        {
            __try
            {
                if (!g_EntityHasAnimation(entity, name))
                    return 0;
                void* state = g_EntityGetAnimation(entity, name);
                if (!state)
                    return 0;
                if (!g_AnimGetEnabled(state))
                {
                    g_AnimSetLoop(state, true);
                    g_AnimSetEnabled(state, true);
                }
                const float advance = TT::ClipAdvance(speed, dt, g_AnimGetLength(state), cycleLength);
                if (advance != 0.0f)
                    g_AnimAddTime(state, advance);
                timePosition = g_AnimGetTime(state);
                return 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // Ogre's default ANIMBLEND_AVERAGE (0) scales every enabled clip by
        // 1/total weight once the total passes 1 (Skeleton::setAnimationState
        // reads the mode at SkeletonInstance+0xD4, OgreMain 0x10443345), so
        // tread_L and tread_R at weight 1 would each pose at half strength.
        // ANIMBLEND_CUMULATIVE (1) applies each at full weight. The mode is
        // per SkeletonInstance: Entity::getSkeleton returns the entity's own
        // instance and SkeletonInstance::loadImpl copies the master's mode
        // into it (0x10444C4A), so other entities using the mesh keep theirs.
        constexpr int kBlendCumulative = 1;

        // Returns the mode found before the call, -2 without a skeleton, -1
        // on a fault.
        int MakeBlendCumulative(void* entity)
        {
            __try
            {
                void* skeleton = g_EntityGetSkeleton(entity);
                if (!skeleton)
                    return -2;
                const int mode = g_SkeletonGetBlend(skeleton);
                if (mode != kBlendCumulative)
                    g_SkeletonSetBlend(skeleton, kBlendCumulative);
                return mode;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        bool SoundAlive(const char* name, void* owner, void* sound)
        {
            __try
            {
                return g_SoundFind(name, owner) == sound;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Stops the loop only while the sound list still holds it: a load or
        // a global stop may already have freed the record.
        void StopSoundLoop(const char* name, void* owner, void* sound)
        {
            __try
            {
                if (g_SoundFind(name, owner) == sound)
                    g_SoundStop(sound);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void* StartSoundLoop(const char* name, void* owner, bool user)
        {
            __try
            {
                alignas(8) uint8_t control[kSoundControlBytes] = {};
                alignas(8) uint8_t prep[kSoundPrepBytes] = {};
                g_SoundInitControl(control);
                *reinterpret_cast<uint32_t*>(control + kSoundControlFlags) = kSoundControlLoopFlags;
                g_SoundInitPrep(prep);
                *reinterpret_cast<uint32_t*>(prep + kSoundPrepPriority) =
                    user ? kSoundPriorityUser : kSoundPriorityOther;
                *reinterpret_cast<uint32_t*>(prep + kSoundPrepLoopMode) = 1;
                return g_SoundPlay(name, owner, control, prep);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        void SetSoundLevel(void* sound, int volume, int rate)
        {
            __try
            {
                g_SoundSetParams(sound, volume, kSoundUnchanged, rate);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool TakeTreadLogLine()
        {
            return g_TreadLogBudget > 0 && InterlockedDecrement(&g_TreadLogBudget) >= 0;
        }

        void UpdateTreadSound(const void* self, TreadState& state, const TrackedClassData& data,
                              const TreadContext& ctx, const TT::SoundLevel& level, float dt)
        {
            if (state.sound && (state.soundOwner != ctx.obj76 || _stricmp(state.soundName, data.treadSound) != 0))
            {
                StopSoundLoop(state.soundName, state.soundOwner, state.sound);
                state.sound = nullptr;
            }
            if (state.sound && !SoundAlive(state.soundName, state.soundOwner, state.sound))
            {
                if (TakeTreadLogLine())
                    LogShimA(LogLevel::Info, kComponent, "obj=%p tread sound %s released by the engine", self,
                             state.soundName);
                state.sound = nullptr;
            }

            const bool keep = TT::KeepLoop(level.play, state.soundQuiet, dt, kSoundHoldSeconds);
            const bool want = data.treadSound[0] && !ctx.dead && ctx.nearCamera && keep;
            if (!want)
            {
                if (state.sound)
                {
                    StopSoundLoop(state.soundName, state.soundOwner, state.sound);
                    if (TakeTreadLogLine())
                        LogShimA(LogLevel::Info, kComponent, "obj=%p tread sound %s stopped (%s)", self,
                                 state.soundName, ctx.dead ? "dead" : !ctx.nearCamera ? "past 150 m" : "slow");
                    state.sound = nullptr;
                }
                return;
            }

            if (!state.sound && !level.play)
                return;  // held quiet: never start a loop below the gate
            if (!state.sound)
            {
                if (state.soundRetry)
                {
                    --state.soundRetry;
                    return;
                }
                void* sound = StartSoundLoop(data.treadSound, ctx.obj76, ctx.user);
                if (!sound)
                {
                    state.soundRetry = kSoundRetryFrames;
                    if (TakeTreadLogLine())
                        LogShimA(LogLevel::Info, kComponent, "obj=%p tread sound %s did not start", self,
                                 data.treadSound);
                    return;
                }
                state.sound = sound;
                state.soundOwner = ctx.obj76;
                std::memcpy(state.soundName, data.treadSound, sizeof(state.soundName));
                if (TakeTreadLogLine())
                    LogShimA(LogLevel::Info, kComponent, "obj=%p tread sound %s started sound=%p user=%d", self,
                             state.soundName, sound, ctx.user ? 1 : 0);
            }
            if (level.play)
                SetSoundLevel(state.sound, level.volume, level.rate);
            else
                SetSoundLevel(state.sound, 0, kSoundUnchanged);
        }

        void UpdateTreads(const uint8_t* self, float dt)
        {
            TrackedClassData data{};
            TreadContext ctx{};
            if (!LookupClassData(self, data) || !ReadTreadContext(self, ctx))
                return;

            const uintptr_t key = reinterpret_cast<uintptr_t>(self);
            TreadState state;
            AcquireSRWLockExclusive(&g_TreadLock);
            state = g_Treads[key];
            ReleaseSRWLockExclusive(&g_TreadLock);

            state.left = TT::StepTreadSpeed(state.left, state.commandLeft, ctx.accelThrust, ctx.accelBrake, dt);
            state.right = TT::StepTreadSpeed(state.right, state.commandRight, ctx.accelThrust, ctx.accelBrake, dt);

            float timeLeft = NAN;
            float timeRight = NAN;
            if (ctx.entity && g_TreadFaultLogged == 0)
            {
                const int l = DriveClip(ctx.entity, g_ClipLeft, state.left, dt, data.treadCycleLength, timeLeft);
                const int r = DriveClip(ctx.entity, g_ClipRight, state.right, dt, data.treadCycleLength, timeRight);
                if (l < 0 || r < 0)
                {
                    // Fail closed: one fault stops tread clips for the session.
                    if (InterlockedExchange(&g_TreadFaultLogged, 1) == 0)
                        LogShimA(LogLevel::Warn, kComponent,
                            "tread clip call faulted on entity %p; tread clips off for this session", ctx.entity);
                }
                const int clips = (l > 0 ? 1 : 0) | (r > 0 ? 2 : 0);
                // Only entities that carry a tread clip are switched; checked
                // every step because a skeleton reload copies the master's
                // mode back.
                const int blend = clips ? MakeBlendCumulative(ctx.entity) : kBlendCumulative;
                if (blend == -1 && InterlockedExchange(&g_TreadFaultLogged, 1) == 0)
                    LogShimA(LogLevel::Warn, kComponent,
                        "skeleton blend call faulted on entity %p; tread clips off for this session", ctx.entity);
                if (ctx.entity != state.entity || clips != state.clips)
                {
                    if (TakeTreadLogLine())
                        LogShimA(LogLevel::Info, kComponent,
                                 "obj=%p entity=%p tread clips: tread_L=%s tread_R=%s blend=%s (was %d)",
                                 self, ctx.entity, (clips & 1) ? "driven" : "absent", (clips & 2) ? "driven" : "absent",
                                 clips ? "cumulative" : "untouched", blend);
                    state.entity = ctx.entity;
                    state.clips = clips;
                }
            }

            const float fraction = TT::SpeedFraction(state.left, state.right, ctx.velocForward);
            const TT::SoundLevel level = TT::TreadSound(fraction, ctx.user);
            UpdateTreadSound(self, state, data, ctx, level, dt);

            AcquireSRWLockExclusive(&g_TreadLock);
            TreadState& stored = g_Treads[key];
            state.commandLeft = stored.commandLeft;
            state.commandRight = stored.commandRight;
            stored = state;
            ReleaseSRWLockExclusive(&g_TreadLock);

            const bool logThis = g_TreadTraceBudget > 0 &&
                (InterlockedIncrement(&g_TreadTraceCounter) % kTreadTraceEvery) == 1 &&
                InterlockedDecrement(&g_TreadTraceBudget) >= 0;
            if (logThis)
            {
                LogShimA(LogLevel::Debug, kComponent,
                    "treads obj=%p cmd=(%.2f,%.2f) vis=(%.2f,%.2f) clipT=(%.3f,%.3f) clips=%d "
                    "sound=%p vol=%d rate=%d near=%d dead=%d",
                    self, state.commandLeft, state.commandRight, state.left, state.right,
                    timeLeft, timeRight, state.clips, state.sound,
                    state.sound ? level.volume : 0, state.sound ? level.rate : 0,
                    ctx.nearCamera ? 1 : 0, ctx.dead ? 1 : 0);
            }
        }

        // Stops this object's loop; erase drops its state (destructor).
        void ReleaseTreads(const void* object, bool erase)
        {
            TreadState state;
            bool found = false;
            AcquireSRWLockExclusive(&g_TreadLock);
            const auto it = g_Treads.find(reinterpret_cast<uintptr_t>(object));
            if (it != g_Treads.end())
            {
                state = it->second;
                found = true;
                if (erase)
                    g_Treads.erase(it);
                else
                    it->second.sound = nullptr;
            }
            ReleaseSRWLockExclusive(&g_TreadLock);
            if (found && state.sound)
            {
                StopSoundLoop(state.soundName, state.soundOwner, state.sound);
                if (TakeTreadLogLine())
                    LogShimA(LogLevel::Info, kComponent, "obj=%p tread sound %s released (%s)", object,
                             state.soundName, erase ? "destructor" : "cleanup");
            }
        }

        template<size_t Slot>
        FnThisVoid StockThisVoid()
        {
            return reinterpret_cast<FnThisVoid>(g_Thunks + Slot * kThunkStride);
        }

        // Hooked when treads or the turret are available; each part checks
        // its own readiness.
        void __fastcall TrackedPostSimulateHook(void* thisPtr, void* /*edx*/, float dt)
        {
            TurretNetFrame(static_cast<uint8_t*>(thisPtr), dt);
            reinterpret_cast<FnSimulate>(g_Thunks + kPostSimulateSlot * kThunkStride)(thisPtr, dt);
            if (g_TreadsReady)
                UpdateTreads(static_cast<const uint8_t*>(thisPtr), dt);
        }

        void __fastcall TrackedCleanupHookA(void* thisPtr, void* /*edx*/)
        {
            ReleaseTreads(thisPtr, false);
            StockThisVoid<kCleanupSlotA>()(thisPtr);
        }

        void __fastcall TrackedCleanupHookB(void* thisPtr, void* /*edx*/)
        {
            ReleaseTreads(thisPtr, false);
            StockThisVoid<kCleanupSlotB>()(thisPtr);
        }

        void* __fastcall TrackedDestructorHook(void* thisPtr, void* /*edx*/, unsigned int flags)
        {
            ReleaseTurret(thisPtr);
            ReleaseTreads(thisPtr, true);
            return reinterpret_cast<FnDestructor>(g_Thunks + kDestructorSlot * kThunkStride)(thisPtr, flags);
        }

        // All-or-nothing: with any piece missing the tread slots stay plain
        // thunks and the phase 1 class runs unchanged.
        bool ResolveTreads(const char*& missing)
        {
            struct Named { const char* name; uintptr_t address; };
            const Named sound[] = {
                { "Sound::InitControl", HookEngine::ResolveNamedAddress("Sound::InitControl") },
                { "Sound::InitPrep", HookEngine::ResolveNamedAddress("Sound::InitPrep") },
                { "PlayGlobalSound", HookEngine::ResolveNamedAddress("PlayGlobalSound") },
                { "Sound::SetParams", HookEngine::ResolveNamedAddress("Sound::SetParams") },
                { "Sound::Stop", HookEngine::ResolveNamedAddress("Sound::Stop") },
                { "Sound::Find", HookEngine::ResolveNamedAddress("Sound::Find") },
                { "GetCameraRecord", HookEngine::EngineAddress("GetCameraRecord") },
            };
            for (const Named& n : sound)
            {
                if (!n.address)
                {
                    missing = n.name;
                    return false;
                }
            }

            static constexpr const char* kOgre[] = {
                "?hasAnimationState@Entity@Ogre@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
                "?getAnimationState@Entity@Ogre@@QBEPAVAnimationState@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
                "?getLength@AnimationState@Ogre@@QBEMXZ",
                "?getTimePosition@AnimationState@Ogre@@QBEMXZ",
                "?addTime@AnimationState@Ogre@@QAEXM@Z",
                "?setEnabled@AnimationState@Ogre@@QAEX_N@Z",
                "?setLoop@AnimationState@Ogre@@QAEX_N@Z",
                "?getEnabled@AnimationState@Ogre@@QBE_NXZ",
                "?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ",
                "?getBlendMode@Skeleton@Ogre@@UBE?AW4SkeletonAnimationBlendMode@2@XZ",
                "?setBlendMode@Skeleton@Ogre@@UAEXW4SkeletonAnimationBlendMode@2@@Z",
                // The vptr at offset 0; terrain_geometry_entities.inl checks the same one.
                "??_7Entity@Ogre@@6BShadowCaster@1@@",
            };
            void* ogre[sizeof(kOgre) / sizeof(kOgre[0])] = {};
            for (size_t i = 0; i < sizeof(kOgre) / sizeof(kOgre[0]); ++i)
            {
                ogre[i] = Hooks::ResolveOgreProcRaw(kOgre[i]);
                if (!ogre[i])
                {
                    missing = kOgre[i];
                    return false;
                }
            }

            g_SoundInitControl = reinterpret_cast<FnSoundInit>(sound[0].address);
            g_SoundInitPrep = reinterpret_cast<FnSoundInit>(sound[1].address);
            g_SoundPlay = reinterpret_cast<FnSoundPlay>(sound[2].address);
            g_SoundSetParams = reinterpret_cast<FnSoundSetParams>(sound[3].address);
            g_SoundStop = reinterpret_cast<FnSoundStop>(sound[4].address);
            g_SoundFind = reinterpret_cast<FnSoundFind>(sound[5].address);
            g_CameraRecord = reinterpret_cast<FnCameraRecord>(sound[6].address);
            g_EntityHasAnimation = reinterpret_cast<FnEntityHasAnimation>(ogre[0]);
            g_EntityGetAnimation = reinterpret_cast<FnEntityGetAnimation>(ogre[1]);
            g_AnimGetLength = reinterpret_cast<FnAnimFloat>(ogre[2]);
            g_AnimGetTime = reinterpret_cast<FnAnimFloat>(ogre[3]);
            g_AnimAddTime = reinterpret_cast<FnAnimAddTime>(ogre[4]);
            g_AnimSetEnabled = reinterpret_cast<FnAnimSetBool>(ogre[5]);
            g_AnimSetLoop = reinterpret_cast<FnAnimSetBool>(ogre[6]);
            g_AnimGetEnabled = reinterpret_cast<FnAnimGetBool>(ogre[7]);
            g_EntityGetSkeleton = reinterpret_cast<FnEntityGetSkeleton>(ogre[8]);
            g_SkeletonGetBlend = reinterpret_cast<FnSkeletonGetBlend>(ogre[9]);
            g_SkeletonSetBlend = reinterpret_cast<FnSkeletonSetBlend>(ogre[10]);
            g_OgreEntityVtable = reinterpret_cast<uintptr_t>(ogre[11]);
            return true;
        }

        // ---- install ---------------------------------------------------------

        // postSimulate: hook slot 16 (treads, or the multiplayer turret sync).
        bool BuildTrackedVtable(uintptr_t stockVtable, bool treads, bool postSimulate)
        {
            void* stock[kHoverVtableSlots + 2] = {};
            if (!HookEngine::ReadMemory(static_cast<uint32_t>(stockVtable - sizeof(void*)), stock, sizeof(stock)))
                return false;
            // stock[0] is the RTTI locator, stock[1 + i] slot i, and
            // stock[1 + 42] must not be code: that pins the slot count.
            for (size_t i = 0; i < kHoverVtableSlots; ++i)
            {
                if (!IsExecutableAddress(reinterpret_cast<uintptr_t>(stock[1 + i])))
                    return false;
            }
            if (IsExecutableAddress(reinterpret_cast<uintptr_t>(stock[1 + kHoverVtableSlots])))
                return false;
            if (reinterpret_cast<uintptr_t>(stock[1 + kSimulateSlot]) != reinterpret_cast<uintptr_t>(g_StockSimulate))
                return false;

            if (!g_Thunks)
            {
                g_Thunks = static_cast<uint8_t*>(VirtualAlloc(nullptr, kHoverVtableSlots * kThunkStride,
                                                              MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
                if (!g_Thunks)
                    return false;
                for (size_t i = 0; i < kHoverVtableSlots; ++i)
                {
                    // jmp dword ptr [stockVtable + 4*i]; int3; int3
                    uint8_t* thunk = g_Thunks + i * kThunkStride;
                    const uint32_t slotAddress = static_cast<uint32_t>(stockVtable + i * sizeof(void*));
                    thunk[0] = 0xFF;
                    thunk[1] = 0x25;
                    std::memcpy(thunk + 2, &slotAddress, sizeof(slotAddress));
                    thunk[6] = 0xCC;
                    thunk[7] = 0xCC;
                }
                DWORD oldProtect = 0;
                if (!VirtualProtect(g_Thunks, kHoverVtableSlots * kThunkStride, PAGE_EXECUTE_READ, &oldProtect))
                {
                    VirtualFree(g_Thunks, 0, MEM_RELEASE);
                    g_Thunks = nullptr;
                    return false;
                }
                FlushInstructionCache(GetCurrentProcess(), g_Thunks, kHoverVtableSlots * kThunkStride);
            }

            g_TrackedVtable[0] = stock[0];
            for (size_t i = 0; i < kHoverVtableSlots; ++i)
                g_TrackedVtable[1 + i] = g_Thunks + i * kThunkStride;
            g_TrackedVtable[1 + kSimulateSlot] = reinterpret_cast<void*>(&TrackedSimulateHook);
            // Drops the per-object turret (and tread) state.
            g_TrackedVtable[1 + kDestructorSlot] = reinterpret_cast<void*>(&TrackedDestructorHook);
            if (treads)
            {
                g_TrackedVtable[1 + kCleanupSlotA] = reinterpret_cast<void*>(&TrackedCleanupHookA);
                g_TrackedVtable[1 + kCleanupSlotB] = reinterpret_cast<void*>(&TrackedCleanupHookB);
            }
            if (postSimulate)
                g_TrackedVtable[1 + kPostSimulateSlot] = reinterpret_cast<void*>(&TrackedPostSimulateHook);
            return true;
        }

        void LogInstallFailure(const char* what)
        {
            if (g_InstallFailureLogged)
                return;
            g_InstallFailureLogged = true;
            LogShimA(LogLevel::Warn, kComponent, "classLabel=tracked not installed: %s", what);
        }
    }

    bool MatchTrackedClassLabel(const char* registeredLabel,
                                const char* odfLabel,
                                int (__cdecl* stricmp)(const char*, const char*))
    {
        if (!g_Installed || !registeredLabel || !odfLabel || !stricmp)
            return false;
        if (stricmp(registeredLabel, kHoverClassLabel) != 0 || stricmp(odfLabel, kTrackedClassLabel) != 0)
            return false;
        g_TrackedBuildPending = true;
        return true;
    }

    void InstallTrackedVehicleClassIfPossible()
    {
        if (g_Installed)
            return;
        // The alias rides on the Find label-compare call site pond patches.
        if (!IsPondClassLabelSupportInstalled())
            return;

        const uintptr_t buildClass = HookEngine::ResolveNamedAddress("HoverCraftClass::BuildClass");
        const uintptr_t build = HookEngine::ResolveNamedAddress("HoverCraftClass::Build");
        const uintptr_t simulate = HookEngine::ResolveNamedAddress("HoverCraft::Simulate");
        const uintptr_t craftSimulate = HookEngine::ResolveNamedAddress("Craft::Simulate");
        const uintptr_t eyepoint = HookEngine::ResolveNamedAddress("HoverCraft::UpdateEyepoint");
        const uintptr_t aimGlobal = HookEngine::ResolveNamedAddress("HoverCraft::AimPitchGlobalGate");
        const uintptr_t aimMode = HookEngine::ResolveNamedAddress("HoverCraft::AimPitchModeGate");
        const uintptr_t openScope = HookEngine::ResolveNamedAddress("ParameterDB::OpenScope");
        const uintptr_t rawGet = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
        const uintptr_t popScope = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
        const uintptr_t floorQuery = HookEngine::ResolveNamedAddress("Terrain::FloorQuery");
        if (!buildClass || !build || !simulate || !craftSimulate || !eyepoint || !aimGlobal ||
            !aimMode || !openScope || !rawGet || !popScope || !floorQuery)
        {
            LogInstallFailure("one or more patches.json resolves missing");
            return;
        }

        const uintptr_t hoverVtable = HookEngine::EngineAddress("HoverCraftVtable");
        if (!hoverVtable || !Hooks::VtableTypeNameMatches(hoverVtable, ".?AVHoverCraft@@"))
        {
            LogInstallFailure("HoverCraftVtable row missing or not .?AVHoverCraft@@");
            return;
        }

        g_StockSimulate = reinterpret_cast<FnSimulate>(simulate);
        g_CraftSimulate = reinterpret_cast<FnSimulate>(craftSimulate);
        g_UpdateEyepoint = reinterpret_cast<FnSimulate>(eyepoint);
        g_AimGlobalGate = reinterpret_cast<FnIntVoid>(aimGlobal);
        g_AimModeGate = reinterpret_cast<FnByteThis>(aimMode);
        g_OpenScope = reinterpret_cast<FnOpenScope>(openScope);
        g_RawGet = reinterpret_cast<FnRawGet>(rawGet);
        g_PopScope = reinterpret_cast<FnPopScope>(popScope);
        g_FloorQuery = reinterpret_cast<FnFloorQuery>(floorQuery);
        g_HoverVtable = hoverVtable;

        // Optional: without it a turretName is ignored (logged per class).
        g_SyncNode = reinterpret_cast<FnSyncNode>(HookEngine::ResolveNamedAddress("Obj76::SyncNode"));
        if (!g_SyncNode)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "rotating turret off (Obj76::SyncNode did not resolve); tracked physics unaffected");
        }

        const char* treadMissing = nullptr;
        const bool treads = ResolveTreads(treadMissing);
        if (!treads)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "tread clips and sound off (%s did not resolve); tracked physics unaffected", treadMissing);
        }

        // Multiplayer, optional. Without the remote gate every object runs
        // the owner model (as before phase 3); without the rest, replicas
        // dead-reckon with the turret held at delta 0.
        const uintptr_t isRemote = HookEngine::EngineAddress("DistributedObjectIsRemote");
        const uintptr_t netGameFlag = HookEngine::EngineAddress("IsNetGameFlag");
        const uintptr_t getLocalId = HookEngine::ResolveNamedAddress("DistributedObject::GetLocalID");
        const uintptr_t broadcastSend = HookEngine::ResolveNamedAddress("Net::BroadcastSend");
        const bool remoteGate = isRemote && netGameFlag;
        const bool turretSync = remoteGate && g_SyncNode && getLocalId && broadcastSend;
        if (!remoteGate)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "multiplayer replicas off (DistributedObjectIsRemote or IsNetGameFlag did not resolve); "
                "every tracked object runs the owner model");
        }
        else if (g_SyncNode && !turretSync)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "multiplayer turret sync off (%s did not resolve); replica turrets stay at delta 0",
                !getLocalId ? "DistributedObject::GetLocalID" : "Net::BroadcastSend");
        }

        if (!BuildTrackedVtable(hoverVtable, treads, treads || turretSync))
        {
            LogInstallFailure("HoverCraftVtable is not the expected 42-slot table with Simulate in slot 15");
            return;
        }

        if (!g_BuildClassDetour.trampoline &&
            !InstallInlineDetour32(g_BuildClassDetour, buildClass,
                                   reinterpret_cast<void*>(&HoverBuildClassHook),
                                   kDetourLength, kDetourPrologue, sizeof(kDetourPrologue)))
        {
            LogInstallFailure("HoverCraftClass::BuildClass detour failed");
            return;
        }
        g_OriginalBuildClass = reinterpret_cast<FnBuildClass>(g_BuildClassDetour.trampoline);

        if (!g_BuildDetour.trampoline &&
            !InstallInlineDetour32(g_BuildDetour, build,
                                   reinterpret_cast<void*>(&HoverBuildHook),
                                   kDetourLength, kDetourPrologue, sizeof(kDetourPrologue)))
        {
            LogInstallFailure("HoverCraftClass::Build detour failed");
            return;
        }
        g_OriginalBuild = reinterpret_cast<FnBuild>(g_BuildDetour.trampoline);

        if (remoteGate)
        {
            g_IsRemote = reinterpret_cast<FnByteThis>(isRemote);
            g_NetGameFlag = netGameFlag;
            g_RemoteGateReady = true;
        }
        if (turretSync)
        {
            g_GetLocalId = reinterpret_cast<FnIdThis>(getLocalId);
            g_BroadcastSend = reinterpret_cast<FnBroadcastSend>(broadcastSend);
            // Registered once: g_Installed stops any later retry.
            if (NetTagDispatch::RegisterNetTagHandler(TN::kTagTurret, &OnTurretMessage))
            {
                g_TurretSyncReady = true;
            }
            else
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "multiplayer turret sync off ('T','Y' receive handler not registered); "
                    "replica turrets stay at delta 0");
            }
        }

        g_TreadsReady = treads;
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
            "installed classLabel=tracked (HoverCraftClass alias, Simulate slot %u replaced)",
            static_cast<unsigned>(kSimulateSlot));
        if (treads)
        {
            LogShimA(LogLevel::Info, kComponent,
                "tread clips (tread_L/tread_R) and treadSound installed: PostSimulate slot %u, "
                "release in slots %u/%u/%u",
                static_cast<unsigned>(kPostSimulateSlot), static_cast<unsigned>(kDestructorSlot),
                static_cast<unsigned>(kCleanupSlotA), static_cast<unsigned>(kCleanupSlotB));
        }
        LogShimA(LogLevel::Info, kComponent, "multiplayer: replica dead reckoning %s, turret sync %s",
            g_RemoteGateReady ? "on" : "off", g_TurretSyncReady ? "on ('T','Y')" : "off");
    }

    bool IsTrackedVehicleClassInstalled()
    {
        return g_Installed;
    }
}
