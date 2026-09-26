// weapon_convergence_hooks.cpp
// BZR Open Shim - weapon convergence, player reticle convergence and the
// smart reticle range redirect (SinglePlayer tier), with their bridge
// accessors, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
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
        constexpr uintptr_t kWingmanWeaponAimVtableSlotAddr = 0x0088A4FC;

        // Redux RTTI/inventory identifies 0x005F0930 as
        // TurretCraft::UpdateWeaponAim, not HoverCraft::UpdateWeaponAim. The
        // second TurretCraft vtable begins at 0x00889380 and its +0x98
        // UpdateWeaponAim slot is 0x00889418. TurretCraftClass is the native
        // implementation behind classLabel="turret".
        constexpr uintptr_t kTurretCraftWeaponAimVtableSlotAddr = 0x00889418;

        // TurretTank::UpdateWeaponAim has two released consumers. The owner
        // guard below verifies that a candidate slot still contains 0x005F27B0
        // before replacing it, so derived consumers remain fail-closed.
        constexpr uintptr_t kTurretTankWeaponAimVtableSlotAddrs[] = {
            0x0087AE08,
            0x00889530,
        };

        constexpr uintptr_t kWingmanWeaponAimStockAddr = 0x004EB590;

        constexpr uintptr_t kTurretCraftUpdateWeaponAimAddr = 0x005F0930;

        constexpr uintptr_t kTurretTankUpdateWeaponAimAddr = 0x005F27B0;

        constexpr uintptr_t kCarrierGetWeaponAddr = 0x00417F60;

        constexpr uintptr_t kRefreshWeaponTransformAddr = 0x00681A00;

        // The global Reticle lives at 0x025CE6D0 (its ctor at 0x005BA170 is
        // called with that `this` from 0x0040B013). Member addresses below come
        // from the class layout; nothing references them absolutely from inside
        // Reticle itself because member access goes through its own `this`.
        //
        // Reticle::Simulate (0x005BA560) resolves the crosshair in a strict
        // order, and convergence has to follow the same one:
        //   selectObj = FindReticleObject(...)      ; object under the crosshair
        //   if (selectObj == 0)                     ; ONLY THEN
        //       groundPos = FindGroundPos()         ; terrain hit, writes gPos
        //   else
        //       groundPos = 0
        // So gPos is stale whenever the crosshair is sitting on something, and
        // reading it unconditionally aims at wherever the ground last was.
        //
        // Reticle::FindGroundPos (0x005BCCA0) only writes gPos when its ray
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
        constexpr uintptr_t kSmartReticleGroundHitAddr = 0x025CE778;     // +0xA8

        constexpr uintptr_t kSmartReticleSelectObjectAddr = 0x025CE77C;  // +0xAC

        constexpr uintptr_t kSmartReticlePositionAddr = 0x025CE79C;      // +0xCC gPos

        // 0x00886B20 is NOT a reticle range variable: it is a pooled read-only
        // 200.0f literal in .rdata that 112 unrelated .text sites also load
        // (comparisons, field initializers, arithmetic all over the game).
        // Writing it moves the reticle range and 107 other things with it, so
        // it is only ever read here as a byte guard, never written. The five
        // reticle loads are redirected to g_SmartReticleRangeCell instead:
        //
        //   Reticle::FindReticleObject (0x005BC640)
        //     0x005BC6CF F3 0F 10 05 [20 6B 88 00] movss  ; radius = range*0.5
        //     0x005BC6F6 F3 0F 59 05 [20 6B 88 00] mulss  ; search center x
        //     0x005BC728 F3 0F 59 05 [20 6B 88 00] mulss  ; search center z
        //     0x005BC8BD 0F 2F 05    [20 6B 88 00] comiss ; depth cull
        //   Reticle::FindGroundPos (0x005BCCA0)
        //     0x005BCCB3 F3 0F 10 05 [20 6B 88 00] movss  ; terrain ray length
        //
        // The last one is what player reticle convergence ultimately aims at,
        // since it caps how far down the sight gPos can land.
        constexpr uintptr_t kSmartReticleRangePooledLiteralAddr = 0x00886B20;

        constexpr SmartReticleRangeSite kSmartReticleRangeSites[] = {
            { 0x005BC6CF, { 0xF3, 0x0F, 0x10, 0x05 }, 4 },
            { 0x005BC6F6, { 0xF3, 0x0F, 0x59, 0x05 }, 4 },
            { 0x005BC728, { 0xF3, 0x0F, 0x59, 0x05 }, 4 },
            { 0x005BC8BD, { 0x0F, 0x2F, 0x05, 0x00 }, 3 },
            { 0x005BCCB3, { 0xF3, 0x0F, 0x10, 0x05 }, 4 },
        };

        constexpr float kSmartReticleRangeMin = 1.0f;

        constexpr float kSmartReticleRangeMax = 10000.0f;

        // Craft layout taken from the stock aim updates themselves: all three
        // UpdateWeaponAim bodies load the Carrier* from +0x1A0 right before
        // calling Carrier::GetWeapon (0x005F0993, 0x004EB62C, 0x0060F3BC each
        // `mov ecx,[this+0x1A0]` / `call 0x00417F60`).
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
            if ((mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) != 0)
                return false;

            const DWORD protect = mbi.Protect & 0xFFu;
            return protect == PAGE_EXECUTE ||
                protect == PAGE_EXECUTE_READ ||
                protect == PAGE_EXECUTE_READWRITE ||
                protect == PAGE_EXECUTE_WRITECOPY;
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
                if (!IsReadableDataProtect(vtableInfo.Protect))
                    return false;

                // Slot 1 re-verified against the rebased expectation, then
                // slot 3 must be executable exe code before the call.
                const uintptr_t mainBase = GetMainModuleBase();
                const uintptr_t expectedGetTeam = mainBase
                    ? mainBase + (kGogGameObjectGetTeamAddr - kGogPreferredImageBase)
                    : kGogGameObjectGetTeamAddr;
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
                    *reinterpret_cast<void* const*>(kSmartReticleSelectObjectAddr);
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
                if (*reinterpret_cast<const int*>(kSmartReticleGroundHitAddr) == 0)
                {
                    LogPlayerConvergenceSkyStandDownOnce();
                    return false;
                }

                return TryBuildConvergenceRangeSample(
                    craft,
                    *reinterpret_cast<const ConvergenceVec3*>(
                        kSmartReticlePositionAddr),
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
                reinterpret_cast<FnCarrierGetWeapon>(kCarrierGetWeaponAddr);
            auto refreshWeaponTransform =
                reinterpret_cast<FnRefreshWeaponTransform>(kRefreshWeaponTransformAddr);

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
            reinterpret_cast<FnUpdateWeaponAim>(kTurretCraftUpdateWeaponAimAddr)(craft, dt);

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
            reinterpret_cast<FnUpdateWeaponAim>(kWingmanWeaponAimStockAddr)(craft, dt);

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
            reinterpret_cast<FnUpdateWeaponAim>(kTurretTankUpdateWeaponAimAddr)(craft, dt);

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

        void RefreshShotConvergencePatchState()
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;
            const bool wantConvergenceWrapper =
                singlePlayer &&
                (g_ShotConvergenceEnabled || g_PlayerReticleShotConvergenceEnabled);

            RefreshConvergenceVtableSlot(
                kWingmanWeaponAimVtableSlotAddr,
                kWingmanWeaponAimStockAddr,
                reinterpret_cast<void*>(WingmanUpdateWeaponAimWithConvergence),
                wantConvergenceWrapper,
                g_WingmanWeaponAimWrapperActive,
                L"wingman convergence dispatcher");
            RefreshConvergenceVtableSlot(
                kTurretCraftWeaponAimVtableSlotAddr,
                kTurretCraftUpdateWeaponAimAddr,
                reinterpret_cast<void*>(TurretCraftUpdateWeaponAimWithConvergence),
                wantConvergenceWrapper,
                g_TurretCraftWeaponAimWrapperActive,
                L"turret convergence dispatcher");
            for (size_t index = 0;
                 index < std::size(kTurretTankWeaponAimVtableSlotAddrs);
                 ++index)
            {
                RefreshConvergenceVtableSlot(
                    kTurretTankWeaponAimVtableSlotAddrs[index],
                    kTurretTankUpdateWeaponAimAddr,
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
            const uint32_t pooled = static_cast<uint32_t>(kSmartReticleRangePooledLiteralAddr);
            std::memcpy(outBytes, site.opcode, site.opcodeLen);
            std::memcpy(outBytes + site.opcodeLen, &pooled, sizeof(pooled));
        }

        // Points all five reticle range loads at our own cell. Either every
        // site moves or none does -- a partial redirect would leave the reticle
        // taking its range from two different places.
        static bool EnsureSmartReticleRangeRedirect()
        {
            if (g_SmartReticleRangeRedirectActive)
                return true;

            for (const auto& site : kSmartReticleRangeSites)
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
            for (const auto& site : kSmartReticleRangeSites)
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

            if (written != std::size(kSmartReticleRangeSites))
            {
                // Put back whatever landed so the reticle stays wholly stock.
                for (size_t index = 0; index < written; ++index)
                {
                    const auto& site = kSmartReticleRangeSites[index];
                    const uint32_t pooled =
                        static_cast<uint32_t>(kSmartReticleRangePooledLiteralAddr);
                    WritePatchBytes(
                        site.instructionAddr + site.opcodeLen,
                        reinterpret_cast<const uint8_t*>(&pooled),
                        sizeof(pooled));
                }
                if (!g_SmartReticleRangeRedirectFaultLogged)
                {
                    Log(L"[RETICLE] Smart-reticle range redirect failed to write (%zu of %zu sites); rolled back\n",
                        written,
                        std::size(kSmartReticleRangeSites));
                    g_SmartReticleRangeRedirectFaultLogged = true;
                }
                return false;
            }

            g_SmartReticleRangeRedirectActive = true;
            Log(L"[RETICLE] Smart-reticle range redirected to 0x%08X across %zu site(s); shared 200.0 literal at 0x%08X left untouched\n",
                cellAddr,
                std::size(kSmartReticleRangeSites),
                static_cast<uint32_t>(kSmartReticleRangePooledLiteralAddr));
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

            const uint32_t pooled =
                static_cast<uint32_t>(kSmartReticleRangePooledLiteralAddr);
            size_t restored = 0;
            for (const auto& site : kSmartReticleRangeSites)
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

            if (restored != std::size(kSmartReticleRangeSites))
            {
                if (!g_SmartReticleRangeRedirectFaultLogged)
                {
                    Log(L"[RETICLE] Smart-reticle range restore failed (%zu of %zu sites)\n",
                        restored,
                        std::size(kSmartReticleRangeSites));
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
