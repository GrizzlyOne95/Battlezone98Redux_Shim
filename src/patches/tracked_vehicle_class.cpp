#include "tracked_vehicle_class.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "pond_class_label.h"
#include "shim_log.h"
#include "tracked_vehicle_physics.h"

#include <Windows.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

namespace BZROpenShim
{
    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
    }

    namespace
    {
        namespace TP = TrackedPhysics;

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

        // HoverCraft object.
        constexpr size_t kObjInterface = 0x18;
        constexpr size_t kObjFloorIgnore = 0xF0;  // passed to the floor query as "not me"
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

        // obj76.
        constexpr size_t kObj76Flags = 0x14;
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
        };

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
            }
            else
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: [TrackedClass] could not be read; using defaults", odfName);
            }
            data.config = TP::Sanitize(data.config);
            data.footprint = TP::FootprintFromBox(boxMin, boxMax);

            AcquireSRWLockExclusive(&g_ClassDataLock);
            g_ClassData[reinterpret_cast<uintptr_t>(objectClass)] = data;
            ReleaseSRWLockExclusive(&g_ClassDataLock);

            LogShimA(LogLevel::Info, kComponent,
                "built ODF %.8s as tracked class=%p stiffness=%.1f damping=%.1f contactsPerSide=%d "
                "lateralFriction=%.2f maxSlope=%.1f footprint x=%.2f+-%.2f z=%.2f..%.2f y=%.2f",
                odfName, objectClass,
                data.config.stiffness, data.config.damping, data.config.contactsPerSide,
                data.config.lateralFriction, data.config.maxSlopeDeg,
                data.footprint.centerX, data.footprint.halfWidth,
                data.footprint.backZ, data.footprint.frontZ, data.footprint.bottomY);
        }

        void* __fastcall HoverBuildClassHook(void* thisPtr, void* /*edx*/, uint32_t odfNameLo, uint32_t odfNameHi)
        {
            // Armed by the label compare that immediately precedes this call
            // in GameObjectClass::Find; cleared before the stock constructor
            // so nested class lookups stay ordinary.
            const bool tracked = g_TrackedBuildPending;
            g_TrackedBuildPending = false;

            void* objectClass = g_OriginalBuildClass(thisPtr, odfNameLo, odfNameHi);
            if (tracked && objectClass)
                ConfigureTrackedClass(objectClass, odfNameLo, odfNameHi);
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

        void* __fastcall HoverBuildHook(void* objectClass, void* /*edx*/, void* arg)
        {
            void* object = g_OriginalBuild(objectClass, arg);
            if (object && IsTrackedClass(objectClass) && !SwapToTrackedVtable(object))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "tracked class %p built object %p without the HoverCraft vtable; left as hover",
                    objectClass, object);
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
        };

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
        bool ComputeTrackedForces(uint8_t* self, float dt, const TrackedClassData& data, TraceSample& trace)
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

                void* floorContext = reinterpret_cast<void*>(
                    static_cast<intptr_t>(*reinterpret_cast<const int*>(self + kObjFloorIgnore)));
                const float floorOffset = *reinterpret_cast<const float*>(obj76 + kObj76FloorOffset);
                TP::Footprint footprint = data.footprint;
                footprint.bottomY = TP::ContactBottom(floorOffset, data.footprint.bottomY, data.config);

                const TP::Result result = TP::Step(data.config, footprint, drive, body, inputs, dt,
                                                   &FloorAt, floorContext);
                WriteVec(self, kObjVeloc, result.veloc);
                WriteVec(self, kObjAccel, result.accel);
                WriteVec(self, kObjAlpha, result.alpha);
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

        void __fastcall TrackedSimulateHook(void* thisPtr, void* /*edx*/, float dt)
        {
            auto* self = static_cast<uint8_t*>(thisPtr);
            TrackedClassData data{};
            TraceSample trace{};
            if (!LookupClassData(self, data) || !ComputeTrackedForces(self, dt, data, trace))
            {
                g_StockSimulate(thisPtr, dt);
                return;
            }

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

        // ---- install ---------------------------------------------------------

        bool BuildTrackedVtable(uintptr_t stockVtable)
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

        if (!BuildTrackedVtable(hoverVtable))
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

        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
            "installed classLabel=tracked (HoverCraftClass alias, Simulate slot %u replaced)",
            static_cast<unsigned>(kSimulateSlot));
    }

    bool IsTrackedVehicleClassInstalled()
    {
        return g_Installed;
    }
}
