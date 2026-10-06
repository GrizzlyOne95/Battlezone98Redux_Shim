// weapon_convergence_hooks.cpp
// BZR Open Shim - weapon convergence, player reticle convergence and the
// smart reticle range redirect (SinglePlayer tier), with their bridge
// accessors, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "memory_access.h"
#include "patcher.h"
#include "shim_log.h"
#include "weapon_convergence.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace BZROpenShim
{
    using FnUpdateWeaponAim = void(__thiscall*)(void* craft, float dt);

    using FnRefreshWeaponTransform = void(__cdecl*)(void* weaponObject, void* transform);

    using FnObjRelParentMatrix = void* (__cdecl*)(void* outMatrix, void* object, void* parent);

    using FnGameObjectGetTarget = void* (__thiscall*)(void* craft);

    using FnDistributedGetPosition = const float* (__thiscall*)(void* distributedSubobject);

    namespace Hooks
    {
        // Global convergence improvements formerly owned by EXU. Each class
        // keeps its own stock UpdateWeaponAim implementation authoritative; the
        // wrappers below add only the shared exact-Walker hardpoint convergence
        // stage after native aiming has finished.
        //
        // UpdateWeaponAim is slot 38 (+0x98) of each class's primary vtable.
        // The vtables are engine_addresses rows checked by RTTI name; the slot
        // owner guard below verifies that a slot still holds the stock
        // function before replacing it, so derived consumers stay fail-closed.
        //
        // Redux RTTI/inventory identifies TurretCraftUpdateWeaponAim as
        // TurretCraft::UpdateWeaponAim, not HoverCraft::UpdateWeaponAim.
        // TurretCraftClass is the native implementation behind
        // classLabel="turret". TurretTank::UpdateWeaponAim has two released
        // consumers: TurretTank itself and Howitzer, which inherits it.
        constexpr size_t kUpdateWeaponAimVtableIndex = 0x98 / sizeof(void*);

        struct ConvergenceVtable
        {
            const char* row;
            const char* rttiName;
            uint32_t address;
        };

        static ConvergenceVtable g_WingmanVtable = { "WingmanVtable", ".?AVWingman@@", 0 };

        static ConvergenceVtable g_TurretCraftVtable = { "TurretCraftVtable", ".?AVTurretCraft@@", 0 };

        static ConvergenceVtable g_TurretTankVtables[] = {
            { "HowitzerVtable", ".?AVHowitzer@@", 0 },
            { "TurretTankVtable", ".?AVTurretTank@@", 0 },
        };

        static uint32_t g_WingmanUpdateWeaponAimAddr = 0;

        static uint32_t g_TurretCraftUpdateWeaponAimAddr = 0;

        static uint32_t g_TurretTankUpdateWeaponAimAddr = 0;

        static uint32_t g_CarrierGetWeaponAddr = 0;

        static uint32_t g_RefreshWeaponTransformAddr = 0;

        // The global Reticle (row ReticleGlobal; its ctor is called with that
        // `this` from the startup code). Member offsets below come from the
        // class layout; nothing references them absolutely from inside Reticle
        // itself because member access goes through its own `this`.
        //
        // Reticle::Simulate resolves the crosshair in a strict
        // order, and convergence has to follow the same one:
        //   selectObj = FindReticleObject(...)      ; object under the crosshair
        //   if (selectObj == 0)                     ; ONLY THEN
        //       groundPos = FindGroundPos()         ; terrain hit, writes gPos
        //   else
        //       groundPos = 0
        // So gPos is stale whenever the crosshair is sitting on something, and
        // reading it unconditionally aims at wherever the ground last was.
        //
        // Reticle::FindGroundPos only writes gPos when its ray
        // actually hits terrain:
        //
        //   if (TerrainRaycast(...) != 0) {
        //       this->gPos = origin + t * direction;   ; +0xCC..+0xD4
        //   }
        //   return hit;                                ; stored to this->+0xA8
        //
        // So +0xA8 is the per-frame "the crosshair is on the ground" flag, and
        // gPos keeps the last hit forever once the crosshair leaves the
        // terrain. Convergence has to consult the flag, not just gPos, or
        // aiming at the sky keeps firing at wherever the ground last was.
        static uint32_t g_ReticleGlobalAddr = 0;

        constexpr size_t kReticleGroundHitOffset = 0xA8;

        constexpr size_t kReticleSelectObjectOffset = 0xAC;

        constexpr size_t kReticlePositionOffset = 0xCC; // gPos

        // SmartReticlePooledRange is NOT a reticle range variable: it is a pooled read-only
        // 200.0f literal in .rdata that 112 unrelated .text sites also load
        // (comparisons, field initializers, arithmetic all over the game).
        // Writing it moves the reticle range and 107 other things with it, so
        // it is only ever read here as a byte guard, never written. The five
        // reticle loads are redirected to g_SmartReticleRangeCell instead:
        //
        //   Reticle::FindReticleObject
        //     SmartReticleRangeRadiusLoad  F3 0F 10 05 [pooled] movss  ; radius = range*0.5
        //     SmartReticleRangeCenterXMul  F3 0F 59 05 [pooled] mulss  ; search center x
        //     SmartReticleRangeCenterZMul  F3 0F 59 05 [pooled] mulss  ; search center z
        //     SmartReticleRangeDepthCull   0F 2F 05    [pooled] comiss ; depth cull
        //   Reticle::FindGroundPos
        //     SmartReticleRangeGroundRay   F3 0F 10 05 [pooled] movss  ; terrain ray length
        //
        // The last one is what player reticle convergence ultimately aims at,
        // since it caps how far down the sight gPos can land. The site rows
        // are bound into instructionAddr; the pooled literal is its own row.
        static uint32_t g_SmartReticleRangePooledLiteralAddr = 0;

        static SmartReticleRangeSite g_SmartReticleRangeSites[] = {
            { 0, { 0xF3, 0x0F, 0x10, 0x05 }, 4 },
            { 0, { 0xF3, 0x0F, 0x59, 0x05 }, 4 },
            { 0, { 0xF3, 0x0F, 0x59, 0x05 }, 4 },
            { 0, { 0x0F, 0x2F, 0x05, 0x00 }, 3 },
            { 0, { 0xF3, 0x0F, 0x10, 0x05 }, 4 },
        };

        static const char* const kSmartReticleRangeSiteRows[] = {
            "SmartReticleRangeRadiusLoad",
            "SmartReticleRangeCenterXMul",
            "SmartReticleRangeCenterZMul",
            "SmartReticleRangeDepthCull",
            "SmartReticleRangeGroundRay",
        };
        static_assert(std::size(kSmartReticleRangeSiteRows) == std::size(g_SmartReticleRangeSites));

        constexpr float kSmartReticleRangeMin = 1.0f;

        constexpr float kSmartReticleRangeMax = 10000.0f;

        // Craft layout taken from the stock aim updates themselves: all three
        // UpdateWeaponAim bodies load the Carrier* from +0x1A0 right before
        // calling Carrier::GetWeapon (each `mov ecx,[this+0x1A0]` /
        // `call CarrierGetWeapon`).
        constexpr size_t kCraftCarrierOffset = 0x1A0;

        constexpr size_t kWeaponObjectOffset = 0x10;

        constexpr size_t kWeaponHardpointOffset = 0x14;

        // The weapon's _OBJ76 carries its MAT_3D at kObj76TransformOffset, not
        // at the object head. Stock pushes obj+0x20 into RefreshWeaponTransform
        // at 0x005F0A38.
        //
        // That MAT_3D is NOT a world transform. Weapon::Control (Redux
        // 0x00611610) recomputes, every frame:
        //
        //   this->M = MountWorldMatrix(this)            ; weapon+0x28
        //   this->I = Matrix_Inverse(this->M)           ; weapon+0x68
        //
        // where MountWorldMatrix (0x006116A0) is
        // obj_rel_parent_matrix(this->hard /*weapon+0x14*/, nullptr) with its
        // position replaced by the muzzle offset at weapon+0x1C pushed through
        // that matrix. So M is the muzzle frame in world space.
        //
        // Every firing site in the exe then spawns ordnance from
        //
        //   fireMatrix = Matrix_Multiply(weapon->obj->mat /*obj+0x20*/, M)
        //
        // (0x005B1E10, 0x005B2010, 0x005B8FF0, 0x005D6330, 0x005DFCB0,
        // 0x005E1EA0, 0x004F2210, 0x00582190, ... all share the shape
        // `FUN_0081fe60(out, *(weapon+0x10)+0x20, weapon+0x28)`), and
        // Matrix_Multiply (0x0081FE60) is row-vector `inner * outer`.
        //
        // The consequence for convergence: obj+0x20 is the weapon's transform
        // *in the mount frame*, so a world-space basis written there is wrong
        // by the whole mount transform, and its position field is a mount-local
        // offset that stock deliberately preserves (Hovercraft::UpdateWeaponAim
        // saves it at 0x005F0930 and restores it after RefreshWeaponTransform).
        constexpr int kConvergenceWeaponSlotCount = 5;

        // The Wingman wrapper is shared by both convergence features. Keep its
        // ownership state separate from the user-facing feature states so
        // enabling PlayerReticleConvergence alone does not make
        // WeaponConvergence report itself as active.
        static bool g_WingmanWeaponAimWrapperActive = false;

        static bool g_TurretCraftWeaponAimWrapperActive = false;

        static bool g_TurretTankWeaponAimWrapperActive[2] = { false, false };

        static bool g_PlayerReticleConvergenceLayoutFaultLogged = false;

        static bool g_PlayerReticleConvergenceSkyStandDownLogged = false;

        static constexpr int kPlayerReticleConvergenceLogLimit = 6;

        static constexpr ULONGLONG kPlayerReticleConvergenceLogIntervalMs = 10000;

        static int g_PlayerReticleConvergenceLogCount = 0;

        static ULONGLONG g_PlayerReticleConvergenceLastLogTick = 0;

        static bool g_ShotConvergencePatchActive = false;

        static bool g_PlayerReticleShotConvergencePatchActive = false;

        // The reticle reads its range straight out of this cell once the
        // redirect is installed, so it must live for the process lifetime --
        // its absolute address is written into the instruction stream. It
        // starts at the stock value, so installing the redirect on its own
        // changes nothing.
        static float g_SmartReticleRangeCell = kSmartReticleRangeStock;

        static bool g_SmartReticleRangeRedirectActive = false;

        static bool g_SmartReticleRangeRedirectFaultLogged = false;

        // The coordinate-space math lives in include/weapon_convergence.h so it
        // can be exercised on the host by tests/weapon_convergence_tests.cpp
        // without dragging in Windows or the live game layout.
        using ConvergenceVec3 = WeaponConvergence::Vec3;
        using ConvergenceMatrix = WeaponConvergence::Matrix;

        // One breadcrumb per session the first time the crosshair leaves the
        // terrain, proving the stale-gPos guard is live rather than silently
        // never taken.
        static void LogPlayerConvergenceSkyStandDownOnce()
        {
            if (g_PlayerReticleConvergenceSkyStandDownLogged)
                return;
            g_PlayerReticleConvergenceSkyStandDownLogged = true;
            Log(L"[CONVERGE] player reticle convergence stood down: no object and no ground hit "
                L"(Reticle+0xA8 == 0), so gPos is stale; stock aim retained\n");
        }

        // UAF guard for the indirect GetPosition call below. The smart-reticle
        // selectObject global is read as a raw pointer; when the unit under
        // the crosshair dies in the same frame the global dangles, the freed
        // block gets recycled, and vtable[3] becomes arbitrary. A valid-looking
        // but wrong target raises FAST_FAIL (e.g. via the CRT's abort), which
        // bypasses __try/__except by design, so the vtable is validated BEFORE
        // the call: it must be committed MEM_IMAGE owned by
        // battlezone98redux.exe, and slot 3 must point at executable code in
        // that same image. A recycled heap block fails the image/protect
        // checks and the shot stands down instead of crashing.
        // POD-only: called from inside __try below, so no C++ unwindables.
        static bool IsExecutableMainImageAddress(const void* address)
        {
            if (!address)
                return false;
            const uintptr_t mainBase = GetMainModuleBase();
            if (mainBase == 0)
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT || mbi.Type != MEM_IMAGE)
                return false;
            if (reinterpret_cast<uintptr_t>(mbi.AllocationBase) != mainBase)
                return false;
            return BZROpenShim::MemoryAccess::ProtectionAllows(
                mbi.Protect, BZROpenShim::MemoryAccess::Access::Execute);
        }

        // Exact position source used by Walker::UpdateWeaponAim:
        // GameObject+0x18 is the DistributedObject interface, and vtable slot
        // 3 (+0x0C) is GetPosition(). BZ1 1.5's imported signature confirms
        // this virtual returns VECTOR_3D*. Calling through the interface keeps
        // convergence range semantics aligned with stock instead of assuming
        // the root OBJ76 translation is always interchangeable.
        static bool TryGetWalkerGameObjectPosition(
            void* gameObject,
            float (&outPosition)[3])
        {
            outPosition[0] = 0.0f;
            outPosition[1] = 0.0f;
            outPosition[2] = 0.0f;
            if (!gameObject)
                return false;

            // Positive GameObject-family identification first: slot 1 must be
            // the known GameObject::GetTeam. Rejects abstract/_purecall tables
            // and foreign objects without invoking anything through them.
            if (!IsLikelyGameObjectEntry(gameObject))
                return false;

            __try
            {
                void* distributedSubobject =
                    reinterpret_cast<uint8_t*>(gameObject) +
                    kGameObjectDistributedObjectOffset;
                void** vtable =
                    *reinterpret_cast<void***>(distributedSubobject);
                if (!vtable)
                    return false;

                // Re-check the vtable mapping inside the guard: the entry check
                // above ran before this read, and the object may have died
                // between the two. A recycled heap block is MEM_PRIVATE, not
                // MEM_IMAGE owned by the exe, so it fails here.
                MEMORY_BASIC_INFORMATION vtableInfo = {};
                if (VirtualQuery(vtable, &vtableInfo, sizeof(vtableInfo)) != sizeof(vtableInfo))
                    return false;
                if (vtableInfo.State != MEM_COMMIT || vtableInfo.Type != MEM_IMAGE)
                    return false;
                if (reinterpret_cast<uintptr_t>(vtableInfo.AllocationBase) != GetMainModuleBase())
                    return false;
                if (!BZROpenShim::MemoryAccess::ProtectionAllows(vtableInfo.Protect, BZROpenShim::MemoryAccess::Access::Read))
                    return false;

                // Slot 1 re-verified against the rebased expectation, then
                // slot 3 must be executable exe code before the call.
                const uintptr_t expectedGetTeam = ExpectedGameObjectGetTeamAddr();
                if (reinterpret_cast<uintptr_t>(vtable[kGameObjectGetTeamVtableOffset / sizeof(void*)]) != expectedGetTeam)
                    return false;

                void* getPositionTarget = vtable[3];
                if (!getPositionTarget || !IsExecutableMainImageAddress(getPositionTarget))
                    return false;

                auto getPosition =
                    reinterpret_cast<FnDistributedGetPosition>(getPositionTarget);
                const float* position = getPosition(distributedSubobject);
                if (!position ||
                    !std::isfinite(position[0]) ||
                    !std::isfinite(position[1]) ||
                    !std::isfinite(position[2]))
                {
                    return false;
                }

                outPosition[0] = position[0];
                outPosition[1] = position[1];
                outPosition[2] = position[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outPosition[0] = 0.0f;
                outPosition[1] = 0.0f;
                outPosition[2] = 0.0f;
                return false;
            }
        }

        struct ConvergenceRangeSample
        {
            float range = 0.0f;
            ConvergenceVec3 reference = {};
            const char* source = "unknown";
        };

        static bool TryBuildConvergenceRangeSample(
            void* craft,
            const ConvergenceVec3& reference,
            const char* source,
            ConvergenceRangeSample& outSample)
        {
            if (!craft ||
                !std::isfinite(reference.x) ||
                !std::isfinite(reference.y) ||
                !std::isfinite(reference.z))
            {
                return false;
            }

            float shooterRaw[3] = {};
            if (!TryGetWalkerGameObjectPosition(craft, shooterRaw))
                return false;

            const float dx = reference.x - shooterRaw[0];
            const float dy = reference.y - shooterRaw[1];
            const float dz = reference.z - shooterRaw[2];
            const float distanceSquared = dx * dx + dy * dy + dz * dz;
            if (!std::isfinite(distanceSquared) || distanceSquared < 0.0f)
                return false;

            const float range = std::sqrt(distanceSquared);
            if (!std::isfinite(range))
                return false;

            outSample.range = range;
            outSample.reference = reference;
            outSample.source = source ? source : "unknown";
            return true;
        }

        static bool TryGetExplicitTargetConvergenceRange(
            void* craft,
            ConvergenceRangeSample& outSample)
        {
            if (!craft)
                return false;

            static FnGameObjectGetTarget gameObjectGetTarget = nullptr;
            if (!gameObjectGetTarget)
            {
                const uint32_t address =
                    HookEngine::ResolveNamedAddress("GameObject::GetTarget");
                if (address == 0)
                    return false;
                gameObjectGetTarget =
                    reinterpret_cast<FnGameObjectGetTarget>(address);
            }

            __try
            {
                void* target = gameObjectGetTarget(craft);
                if (!target)
                    return false;

                float targetPosition[3] = {};
                if (!TryGetWalkerGameObjectPosition(target, targetPosition))
                    return false;

                return TryBuildConvergenceRangeSample(
                    craft,
                    { targetPosition[0], targetPosition[1], targetPosition[2] },
                    "target",
                    outSample);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryGetReticleConvergenceRange(
            void* craft,
            ConvergenceRangeSample& outSample)
        {
            if (!craft)
                return false;

            __try
            {
                auto* const userObjectSlot =
                    reinterpret_cast<void* const*>(EngineGlobals::UserObjectSlot());
                if (!userObjectSlot || *userObjectSlot != craft)
                    return false;

                void* selectObject =
                    *reinterpret_cast<void* const*>(g_ReticleGlobalAddr + kReticleSelectObjectOffset);
                if (selectObject)
                {
                    float objectPosition[3] = {};
                    if (!TryGetWalkerGameObjectPosition(selectObject, objectPosition))
                        return false;

                    return TryBuildConvergenceRangeSample(
                        craft,
                        { objectPosition[0], objectPosition[1], objectPosition[2] },
                        "reticle-object",
                        outSample);
                }

                // No object under the crosshair and no ground hit this frame
                // means gPos is stale. Stand down rather than reuse an old range.
                if (*reinterpret_cast<const int*>(g_ReticleGlobalAddr + kReticleGroundHitOffset) == 0)
                {
                    LogPlayerConvergenceSkyStandDownOnce();
                    return false;
                }

                return TryBuildConvergenceRangeSample(
                    craft,
                    *reinterpret_cast<const ConvergenceVec3*>(
                        g_ReticleGlobalAddr + kReticlePositionOffset),
                    "reticle-ground",
                    outSample);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Shared exact-Walker hardpoint post-pass.
        //
        // This is the convergence mechanism for both public features. The only
        // intended distinction is the provider of ConvergenceRangeSample:
        //
        //   Weapon Convergence  -> explicit GameObject target range
        //   Reticle Convergence -> smart-reticle object/ground range
        //
        // Stock class-specific UpdateWeaponAim runs before this function. The
        // post-pass then reproduces only Walker's proven convergence stage.
        static int ApplyWalkerConvergencePostPass(
            void* craft,
            const ConvergenceRangeSample& sample,
            bool logReticleApplication)
        {
            if (!craft || !std::isfinite(sample.range))
                return 0;

            auto carrierGetWeapon =
                reinterpret_cast<FnCarrierGetWeapon>(g_CarrierGetWeaponAddr);
            auto refreshWeaponTransform =
                reinterpret_cast<FnRefreshWeaponTransform>(g_RefreshWeaponTransformAddr);

            static FnObjRelParentMatrix objRelParentMatrix = nullptr;
            if (!objRelParentMatrix)
            {
                const uint32_t address =
                    HookEngine::ResolveNamedAddress("obj_rel_parent_matrix");
                if (address == 0)
                    return 0;
                objRelParentMatrix =
                    reinterpret_cast<FnObjRelParentMatrix>(address);
            }

            int converged = 0;
            float lastHardpointX = 0.0f;
            float lastHardpointZ = 0.0f;

            __try
            {
                void* carrier = *reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(craft) + kCraftCarrierOffset);
                void* craftObject = *reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(craft) + kGameObjectObjOffset);
                if (!carrier || !craftObject)
                    return 0;

                for (int slot = 0; slot < kConvergenceWeaponSlotCount; ++slot)
                {
                    void* weapon = carrierGetWeapon(carrier, slot);
                    if (!weapon)
                        continue;

                    void* weaponObject = *reinterpret_cast<void**>(
                        reinterpret_cast<uint8_t*>(weapon) + kWeaponObjectOffset);
                    void* hardpoint = *reinterpret_cast<void**>(
                        reinterpret_cast<uint8_t*>(weapon) + kWeaponHardpointOffset);
                    if (!weaponObject || !hardpoint)
                        continue;

                    ConvergenceMatrix hardpointRelative = {};
                    objRelParentMatrix(
                        &hardpointRelative,
                        hardpoint,
                        craftObject);

                    const float hardpointX =
                        static_cast<float>(hardpointRelative.positionX);
                    const float hardpointZ =
                        static_cast<float>(hardpointRelative.positionZ);
                    if (!std::isfinite(hardpointX) ||
                        !std::isfinite(hardpointZ))
                    {
                        continue;
                    }

                    auto* transform = reinterpret_cast<ConvergenceMatrix*>(
                        reinterpret_cast<uint8_t*>(weaponObject) +
                        kObj76TransformOffset);

                    WeaponConvergence::Solution solution = {};
                    if (WeaponConvergence::SolveWalkerStyleRange(
                            *transform,
                            hardpointX,
                            hardpointZ,
                            sample.range,
                            solution) !=
                        WeaponConvergence::SolveResult::Converged)
                    {
                        continue;
                    }

                    *transform = solution.mountLocal;
                    refreshWeaponTransform(weaponObject, transform);
                    lastHardpointX = hardpointX;
                    lastHardpointZ = hardpointZ;
                    ++converged;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_PlayerReticleConvergenceLayoutFaultLogged)
                {
                    Log(L"[CONVERGE] shared Walker post-pass faulted while reading craft/carrier/weapon layout "
                        L"(craft=0x%p carrierOffset=0x%X)\n",
                        craft,
                        static_cast<uint32_t>(kCraftCarrierOffset));
                    g_PlayerReticleConvergenceLayoutFaultLogged = true;
                }
                return 0;
            }

            if (logReticleApplication &&
                converged > 0 &&
                g_PlayerReticleConvergenceLogCount <
                    kPlayerReticleConvergenceLogLimit)
            {
                const ULONGLONG now = GetTickCount64();
                if (g_PlayerReticleConvergenceLastLogTick == 0 ||
                    now - g_PlayerReticleConvergenceLastLogTick >=
                        kPlayerReticleConvergenceLogIntervalMs)
                {
                    g_PlayerReticleConvergenceLastLogTick = now;
                    ++g_PlayerReticleConvergenceLogCount;
                    Log(L"[CONVERGE] shared exact-Walker post-pass applied to %d hardpoint(s) "
                        L"rangeSource=%hs rangeReference=(%.1f, %.1f, %.1f) "
                        L"range=%.1f lastHardpointXZ=(%.3f, %.3f)\n",
                        converged,
                        sample.source,
                        static_cast<double>(sample.reference.x),
                        static_cast<double>(sample.reference.y),
                        static_cast<double>(sample.reference.z),
                        static_cast<double>(sample.range),
                        static_cast<double>(lastHardpointX),
                        static_cast<double>(lastHardpointZ));
                }
            }

            return converged;
        }

        static void ApplyLocalPlayerReticleConvergence(void* craft)
        {
            ConvergenceRangeSample sample = {};
            if (!TryGetReticleConvergenceRange(craft, sample))
                return;
            ApplyWalkerConvergencePostPass(craft, sample, true);
        }

        static void ApplyExplicitTargetWeaponConvergence(void* craft)
        {
            ConvergenceRangeSample sample = {};
            if (!TryGetExplicitTargetConvergenceRange(craft, sample))
                return;
            ApplyWalkerConvergencePostPass(craft, sample, false);
        }

        static void __fastcall TurretCraftUpdateWeaponAimWithConvergence(
            void* craft,
            void* /*edx*/,
            float dt)
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;

            // Work Order 4: TurretCraft owns classLabel="turret". Preserve its
            // native turret articulation / weapon transform construction, then
            // add only Walker's hardpoint convergence stage by range.
            reinterpret_cast<FnUpdateWeaponAim>(g_TurretCraftUpdateWeaponAimAddr)(craft, dt);

            if (g_ShotConvergenceEnabled && singlePlayer)
                ApplyExplicitTargetWeaponConvergence(craft);

            if (g_PlayerReticleShotConvergenceEnabled && singlePlayer)
                ApplyLocalPlayerReticleConvergence(craft);
        }

        static void __fastcall WingmanUpdateWeaponAimWithConvergence(
            void* craft,
            void* /*edx*/,
            float dt)
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;

            // Work Order 3: keep Wingman's class-specific stock aim setup, then
            // apply only Walker's convergence stage through the common post-pass.
            // The audit in PR #241 proved Wingman and Walker are identical up to
            // the point where Walker adds that stage.
            reinterpret_cast<FnUpdateWeaponAim>(g_WingmanUpdateWeaponAimAddr)(craft, dt);

            if (g_ShotConvergenceEnabled && singlePlayer)
                ApplyExplicitTargetWeaponConvergence(craft);

            // Preserve the existing ordering when both features are enabled:
            // the reticle pass follows explicit-target convergence. Interaction
            // policy is intentionally left for the later matrix work order.
            if (g_PlayerReticleShotConvergenceEnabled && singlePlayer)
                ApplyLocalPlayerReticleConvergence(craft);
        }

        static void __fastcall TurretTankUpdateWeaponAimWithConvergence(
            void* craft,
            void* /*edx*/,
            float dt)
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;

            // Work Order 4: never substitute Walker::UpdateWeaponAim here.
            // TurretTank's own yaw/pitch mechanics and weapon transform setup
            // remain authoritative; convergence is strictly a post-pass.
            reinterpret_cast<FnUpdateWeaponAim>(g_TurretTankUpdateWeaponAimAddr)(craft, dt);

            if (g_ShotConvergenceEnabled && singlePlayer)
                ApplyExplicitTargetWeaponConvergence(craft);

            if (g_PlayerReticleShotConvergenceEnabled && singlePlayer)
                ApplyLocalPlayerReticleConvergence(craft);
        }

        static bool TryReadPointerValue(uintptr_t address, void*& outValue)
        {
            outValue = nullptr;
            __try
            {
                outValue = *reinterpret_cast<void**>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool RefreshConvergenceVtableSlot(
            uintptr_t slotAddress,
            uintptr_t stockAddress,
            void* enabledValue,
            bool wantEnabled,
            bool& activeState,
            const wchar_t* label)
        {
            void* current = nullptr;
            if (!TryReadPointerValue(slotAddress, current))
            {
                activeState = false;
                return false;
            }

            void* stockValue = reinterpret_cast<void*>(stockAddress);
            void* desiredValue = wantEnabled ? enabledValue : stockValue;
            if (current == desiredValue)
            {
                activeState = wantEnabled;
                return true;
            }

            if (current != stockValue && current != enabledValue)
            {
                static std::unordered_set<uintptr_t> loggedSlots;
                if (loggedSlots.insert(slotAddress).second)
                {
                    Log(L"[CONVERGE] %ls vtable ownership mismatch slot=0x%08X current=0x%08X; left untouched\n",
                        label,
                        static_cast<uint32_t>(slotAddress),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)));
                }
                activeState = false;
                return false;
            }

            if (!WritePointerValue(slotAddress, desiredValue))
            {
                activeState = false;
                return false;
            }

            activeState = wantEnabled;
            Log(L"[CONVERGE] %ls %ls slot=0x%08X target=0x%08X\n",
                label,
                wantEnabled ? L"enabled" : L"disabled",
                static_cast<uint32_t>(slotAddress),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(desiredValue)));
            return true;
        }

        static uintptr_t UpdateWeaponAimSlot(const ConvergenceVtable& vtable)
        {
            return vtable.address + kUpdateWeaponAimVtableIndex * sizeof(void*);
        }

        static bool ShotConvergenceAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { g_WingmanVtable.row, &g_WingmanVtable.address },
                    { g_TurretCraftVtable.row, &g_TurretCraftVtable.address },
                    { g_TurretTankVtables[0].row, &g_TurretTankVtables[0].address },
                    { g_TurretTankVtables[1].row, &g_TurretTankVtables[1].address },
                    { "WingmanUpdateWeaponAim", &g_WingmanUpdateWeaponAimAddr },
                    { "TurretCraftUpdateWeaponAim", &g_TurretCraftUpdateWeaponAimAddr },
                    { "TurretTankUpdateWeaponAim", &g_TurretTankUpdateWeaponAimAddr },
                    { "CarrierGetWeapon", &g_CarrierGetWeaponAddr },
                    { "RefreshWeaponTransform", &g_RefreshWeaponTransformAddr },
                    { "ReticleGlobal", &g_ReticleGlobalAddr },
                };
                if (!HookEngine::BindEngineRows("Shot convergence", rows))
                    return false;
                const ConvergenceVtable* vtables[] = {
                    &g_WingmanVtable, &g_TurretCraftVtable,
                    &g_TurretTankVtables[0], &g_TurretTankVtables[1],
                };
                for (const ConvergenceVtable* vtable : vtables)
                {
                    if (VtableTypeNameMatches(vtable->address, vtable->rttiName))
                        continue;
                    Log(L"[CONVERGE] %hs RTTI mismatch vtable=0x%08X; convergence stands down\n",
                        vtable->row, vtable->address);
                    return false;
                }
                return true;
            }();
            return bound;
        }

        void RefreshShotConvergencePatchState()
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;
            const bool wantConvergenceWrapper =
                singlePlayer &&
                (g_ShotConvergenceEnabled || g_PlayerReticleShotConvergenceEnabled);

            // Nothing installed and nothing wanted: the slots are stock, and a
            // build without the rows has no reason to report a stand-down.
            const bool anyWrapperActive =
                g_WingmanWeaponAimWrapperActive || g_TurretCraftWeaponAimWrapperActive ||
                g_TurretTankWeaponAimWrapperActive[0] || g_TurretTankWeaponAimWrapperActive[1];
            if ((!wantConvergenceWrapper && !anyWrapperActive) || !ShotConvergenceAddressesBound())
            {
                g_ShotConvergencePatchActive = false;
                g_PlayerReticleShotConvergencePatchActive = false;
                return;
            }

            RefreshConvergenceVtableSlot(
                UpdateWeaponAimSlot(g_WingmanVtable),
                g_WingmanUpdateWeaponAimAddr,
                reinterpret_cast<void*>(WingmanUpdateWeaponAimWithConvergence),
                wantConvergenceWrapper,
                g_WingmanWeaponAimWrapperActive,
                L"wingman convergence dispatcher");
            RefreshConvergenceVtableSlot(
                UpdateWeaponAimSlot(g_TurretCraftVtable),
                g_TurretCraftUpdateWeaponAimAddr,
                reinterpret_cast<void*>(TurretCraftUpdateWeaponAimWithConvergence),
                wantConvergenceWrapper,
                g_TurretCraftWeaponAimWrapperActive,
                L"turret convergence dispatcher");
            for (size_t index = 0;
                 index < std::size(g_TurretTankVtables);
                 ++index)
            {
                RefreshConvergenceVtableSlot(
                    UpdateWeaponAimSlot(g_TurretTankVtables[index]),
                    g_TurretTankUpdateWeaponAimAddr,
                    reinterpret_cast<void*>(TurretTankUpdateWeaponAimWithConvergence),
                    wantConvergenceWrapper,
                    g_TurretTankWeaponAimWrapperActive[index],
                    index == 0
                        ? L"turrettank convergence dispatcher A"
                        : L"turrettank convergence dispatcher B");
            }

            // Feature state is reported independently even though the Wingman
            // dispatcher is shared. For normal player craft, the Wingman slot
            // is the required dispatch path; the Hovercraft hook only extends
            // coverage to direct base-derived craft.
            g_ShotConvergencePatchActive =
                g_ShotConvergenceEnabled &&
                singlePlayer &&
                g_WingmanWeaponAimWrapperActive;
            g_PlayerReticleShotConvergencePatchActive =
                g_PlayerReticleShotConvergenceEnabled &&
                singlePlayer &&
                g_WingmanWeaponAimWrapperActive;
        }

        float ClampSmartReticleRange(float range)
        {
            return (std::clamp)(range, kSmartReticleRangeMin, kSmartReticleRangeMax);
        }

        // Builds the full stock instruction (opcode + the pooled literal's
        // address as the disp32) so the guard anchors on the instruction rather
        // than on the operand alone.
        static void BuildSmartReticleRangeSiteBytes(
            const SmartReticleRangeSite& site,
            uint8_t (&outBytes)[8])
        {
            const uint32_t pooled = g_SmartReticleRangePooledLiteralAddr;
            std::memcpy(outBytes, site.opcode, site.opcodeLen);
            std::memcpy(outBytes + site.opcodeLen, &pooled, sizeof(pooled));
        }

        // Points all five reticle range loads at our own cell. Either every
        // site moves or none does -- a partial redirect would leave the reticle
        // taking its range from two different places.
        static bool SmartReticleRangeAddressesBound()
        {
            static const bool bound = [] {
                uint32_t sites[std::size(g_SmartReticleRangeSites)] = {};
                HookEngine::EngineRow rows[std::size(g_SmartReticleRangeSites) + 1] = {
                    { "SmartReticlePooledRange", &g_SmartReticleRangePooledLiteralAddr },
                };
                for (size_t index = 0; index < std::size(sites); ++index)
                    rows[index + 1] = { kSmartReticleRangeSiteRows[index], &sites[index] };
                if (!HookEngine::BindEngineRows("Smart-reticle range", rows))
                    return false;
                for (size_t index = 0; index < std::size(sites); ++index)
                    g_SmartReticleRangeSites[index].instructionAddr = sites[index];
                return true;
            }();
            return bound;
        }

        static bool EnsureSmartReticleRangeRedirect()
        {
            if (g_SmartReticleRangeRedirectActive)
                return true;
            if (!SmartReticleRangeAddressesBound())
                return false;

            for (const auto& site : g_SmartReticleRangeSites)
            {
                uint8_t expected[8] = {};
                BuildSmartReticleRangeSiteBytes(site, expected);
                if (ExpectedBytesMatchAt(site.instructionAddr, expected, site.opcodeLen + 4u))
                    continue;

                if (!g_SmartReticleRangeRedirectFaultLogged)
                {
                    Log(L"[RETICLE] Smart-reticle range redirect stood down: site 0x%08X does not hold the stock load; leaving the shared 200.0 literal alone\n",
                        static_cast<uint32_t>(site.instructionAddr));
                    g_SmartReticleRangeRedirectFaultLogged = true;
                }
                return false;
            }

            const uint32_t cellAddr =
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_SmartReticleRangeCell));
            size_t written = 0;
            for (const auto& site : g_SmartReticleRangeSites)
            {
                if (!WritePatchBytes(
                        site.instructionAddr + site.opcodeLen,
                        reinterpret_cast<const uint8_t*>(&cellAddr),
                        sizeof(cellAddr)))
                {
                    break;
                }
                ++written;
            }

            if (written != std::size(g_SmartReticleRangeSites))
            {
                // Put back whatever landed so the reticle stays wholly stock.
                for (size_t index = 0; index < written; ++index)
                {
                    const auto& site = g_SmartReticleRangeSites[index];
                    const uint32_t pooled = g_SmartReticleRangePooledLiteralAddr;
                    WritePatchBytes(
                        site.instructionAddr + site.opcodeLen,
                        reinterpret_cast<const uint8_t*>(&pooled),
                        sizeof(pooled));
                }
                if (!g_SmartReticleRangeRedirectFaultLogged)
                {
                    Log(L"[RETICLE] Smart-reticle range redirect failed to write (%zu of %zu sites); rolled back\n",
                        written,
                        std::size(g_SmartReticleRangeSites));
                    g_SmartReticleRangeRedirectFaultLogged = true;
                }
                return false;
            }

            g_SmartReticleRangeRedirectActive = true;
            Log(L"[RETICLE] Smart-reticle range redirected to 0x%08X across %zu site(s); shared 200.0 literal at 0x%08X left untouched\n",
                cellAddr,
                std::size(g_SmartReticleRangeSites),
                g_SmartReticleRangePooledLiteralAddr);
            return true;
        }

        // Put the five loads back on the pooled 200.0 literal. Used when
        // OpenShim is not the authority for the range (network game with no
        // EXU/Lua setter, or an explicit stock request) so a mod that writes
        // the literal -- or simply wants Redux's own 200 -- is not stuck on
        // OpenShim's cell.
        static void RestoreSmartReticleRangeRedirect()
        {
            if (!g_SmartReticleRangeRedirectActive)
                return;

            const uint32_t pooled = g_SmartReticleRangePooledLiteralAddr;
            size_t restored = 0;
            for (const auto& site : g_SmartReticleRangeSites)
            {
                if (!WritePatchBytes(
                        site.instructionAddr + site.opcodeLen,
                        reinterpret_cast<const uint8_t*>(&pooled),
                        sizeof(pooled)))
                {
                    break;
                }
                ++restored;
            }

            if (restored != std::size(g_SmartReticleRangeSites))
            {
                if (!g_SmartReticleRangeRedirectFaultLogged)
                {
                    Log(L"[RETICLE] Smart-reticle range restore failed (%zu of %zu sites)\n",
                        restored,
                        std::size(g_SmartReticleRangeSites));
                    g_SmartReticleRangeRedirectFaultLogged = true;
                }
                return;
            }

            g_SmartReticleRangeRedirectActive = false;
            g_SmartReticleRangeCell = kSmartReticleRangeStock;
            Log(L"[RETICLE] Smart-reticle range redirect restored to shared 200.0 literal at 0x%08X\n",
                pooled);
        }

        static bool TryReadSmartReticleRange(float& outRange)
        {
            if (!g_SmartReticleRangeRedirectActive)
                return false;
            outRange = g_SmartReticleRangeCell;
            return std::isfinite(outRange);
        }

        void RefreshSmartReticleRangeState()
        {
            const bool networkGame = ReadLocalPlayerNetIdValue() != 0;
            float desired = kSmartReticleRangeStock;
            bool claimRange = false;

            if (g_SmartReticleRangeOwnedByBridge)
            {
                // Matched-mod path (BZP/BZP-T, Reloaded, any EXU SetReticleRange
                // caller). The setter is the authority in SP and MP.
                desired = g_SmartReticleRange;
                claimRange = true;
            }
            else if (!networkGame)
            {
                desired = g_SmartReticleRange;
                claimRange = desired != kSmartReticleRangeStock;
            }

            if (!claimRange)
            {
                RestoreSmartReticleRangeRedirect();
                return;
            }

            // Without the redirect the only place left to put the value is the
            // shared literal, which is what this feature must not touch. Stand
            // down and leave the reticle at its stock range.
            if (!EnsureSmartReticleRangeRedirect())
                return;

            if (g_SmartReticleRangeCell == desired)
                return;

            g_SmartReticleRangeCell = desired;
            Log(L"[RETICLE] Smart-reticle range=%.3f (%hs)\n",
                static_cast<double>(desired),
                g_SmartReticleRangeOwnedByBridge
                    ? "exu/lua"
                    : (networkGame ? "stock/network" : "single-player"));
        }

        void RevertShotConvergenceToBaseline()
        {
            g_ShotConvergenceEnabled = g_ShotConvergenceBaselineEnabled;
            g_PlayerReticleShotConvergenceEnabled =
                g_PlayerReticleShotConvergenceBaselineEnabled;
            RefreshShotConvergencePatchState();
        }

        void RevertSmartReticleRangeToBaseline()
        {
            g_SmartReticleRangeOwnedByBridge = false;
            g_SmartReticleRange = g_SmartReticleRangeBaseline;
            RefreshSmartReticleRangeState();
        }
    }

    using namespace Hooks;

    bool GetShotConvergenceFromBridge()
    {
        return g_ShotConvergenceEnabled;
    }

    bool SetShotConvergenceFromBridge(bool enabled)
    {
        g_ShotConvergenceEnabled = enabled;
        RefreshShotConvergencePatchState();
        Log(L"[MISSIONHOOK] all-craft weapon convergence %hs patch=%hs\n",
            enabled ? "enabled" : "disabled",
            g_ShotConvergencePatchActive ? "active" : "inactive");
        return !enabled || g_ShotConvergencePatchActive;
    }

    bool GetPlayerReticleShotConvergenceFromBridge()
    {
        return g_PlayerReticleShotConvergenceEnabled;
    }

    bool SetPlayerReticleShotConvergenceFromBridge(bool enabled)
    {
        g_PlayerReticleShotConvergenceEnabled = enabled;
        RefreshShotConvergencePatchState();
        Log(L"[MISSIONHOOK] player smart-reticle convergence %hs patch=%hs\n",
            enabled ? "enabled" : "disabled",
            g_PlayerReticleShotConvergencePatchActive ? "active" : "inactive");
        return !enabled || g_PlayerReticleShotConvergencePatchActive;
    }

    float GetSmartReticleRangeFromBridge()
    {
        float range = 0.0f;
        if (TryReadSmartReticleRange(range))
            return range;
        return g_SmartReticleRangeOwnedByBridge
            ? g_SmartReticleRange
            : kSmartReticleRangeStock;
    }

    bool SetSmartReticleRangeFromBridge(float range)
    {
        if (!std::isfinite(range))
            return false;

        const float clamped = ClampSmartReticleRange(range);
        g_SmartReticleRangeOwnedByBridge = true;
        g_SmartReticleRange = clamped;
        RefreshSmartReticleRangeState();
        Log(L"[MISSIONHOOK] smart-reticle range requested=%.3f applied=%.3f (exu/lua, mp-honored)\n",
            static_cast<double>(range),
            static_cast<double>(clamped));
        float effective = 0.0f;
        return TryReadSmartReticleRange(effective) && effective == clamped;
    }
}
