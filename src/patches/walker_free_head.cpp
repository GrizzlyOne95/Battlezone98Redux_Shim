#include "walker_free_head.h"

#include "hook_engine.h"
#include "shim_log.h"
#include "walker_free_head_math.h"

#include <Windows.h>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

// Walker free-turning head, milestone M1 (Docs/WALKER_FREE_HEAD.md,
// design and RE in Docs/WALKER_FREE_HEAD_RESEARCH.md sections 4 and 5a).
//
// Frame swap: the walker's root transform (obj76) is the head, so camera,
// reticle, stock weapon aim and ordnance follow the head unchanged. The
// Walker vtable's Simulate slot (15) is wrapped in place: for an opted-in
// ([WalkerClass] torsoName), player-driven walker in single player it
//   1. reads the head command from the raw analog steer axis (mouse only)
//      and the legs command from the steer arrows and A/D strafe keys,
//   2. slews the head (tracked turret math),
//   3. writes ctrl.steer = legs command and ctrl.strafe = 0 (sidestep is
//      off while twisting; steer assist is not applied to the head),
//   4. turns the root to the legs frame (the head yawed by -delta),
//   5. runs the stock Walker::Simulate (locomotion, walk clip, legs turn),
//   6. measures the legs' turn, sets delta, turns the root back to the head
//      frame, restores the controls and re-runs slot 38 UpdateWeaponAim,
//      which the stock tail ran while the root was the legs frame.
// The PostSimulate slot (16) is wrapped too; M1 only logs that it is reached
// (M2 re-poses the leg nodes there, after the walk clip has written them).
// M1 does not pose the legs: the legs mesh stays in the head frame.
//
// Not user-driven, dead, or not single player: the stock call runs and
// delta snaps to 0 (M2 relaxes it). delta is not saved; a loaded game starts
// at 0. Per-object state is keyed by the object pointer and reset when the
// object's obj76 differs (address reuse); entries are bounded by the
// GameObject pool and only exist for opted-in classes.

namespace BZROpenShim
{
    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
        bool WritePointerValue(uintptr_t address, void* value);
        bool IsSinglePlayerSession();
    }

    namespace
    {
        namespace TP = TrackedPhysics;
        namespace TU = TrackedTurret;
        namespace WH = WalkerFreeHead;
        using Vec3 = TP::Vec3;

        constexpr char kComponent[] = "WALKHEAD";

        // GameObjectClass.
        constexpr size_t kClassPackedNameOffset = 0x30;

        // Walker object (Craft layout, as tracked_vehicle_class.cpp).
        constexpr size_t kObjObj76 = 0xF4;
        constexpr size_t kObjClass = 0xF8;
        constexpr size_t kObjVeloc = 0x12C;       // world velocity
        constexpr size_t kObjWeaponList = 0x1A0;  // the Craft tail calls slot 38 when set
        constexpr size_t kObjControls = 0x230;

        // obj76 and model nodes.
        constexpr size_t kObj76Name = 0x08;
        constexpr size_t kObj76NameBytes = 8;
        constexpr size_t kObj76Flags = 0x14;
        constexpr size_t kObj76Right = 0x20;
        constexpr size_t kObj76Up = 0x2C;
        constexpr size_t kObj76Front = 0x38;
        constexpr size_t kObj76Sibling = 0x7C;
        constexpr size_t kObj76Child = 0x80;
        constexpr uint32_t kObj76FlagUser = 0x10;   // aim gate, set on the user's craft
        constexpr uint32_t kObj76FlagDead = 0x200;

        // Control block.
        constexpr size_t kCtrlSteer = 0xC4;   // +1 turns left
        constexpr size_t kCtrlStrafe = 0xCC;  // +1 moves right

        // WalkerVtable 0x0088A0BC (42 slots, research doc section 5a Q1).
        constexpr size_t kSimulateSlot = 15;
        constexpr size_t kPostSimulateSlot = 16;
        constexpr size_t kUpdateWeaponAimSlot = 38;
        constexpr int kMaxRootChildren = 16;

        using FnSimulate = void (__thiscall*)(void*, float);
        using FnOpenScope = void* (__thiscall*)(void*, const char*);
        using FnRawGet = const char* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnPopScope = void (__thiscall*)(void*);

        FnSimulate g_StockSimulate = nullptr;
        FnSimulate g_StockPostSimulate = nullptr;
        FnOpenScope g_OpenScope = nullptr;
        FnRawGet g_RawGet = nullptr;
        FnPopScope g_PopScope = nullptr;
        const volatile int32_t* g_SteerAxis = nullptr;   // 0x009198B0
        const volatile int8_t* g_SteerLeft = nullptr;    // 0x009198B5
        const volatile int8_t* g_SteerRight = nullptr;   // 0x009198B4
        bool g_Installed = false;
        bool g_GaveUp = false;
        bool g_InstallFailureLogged = false;

        // ---- per class: [WalkerClass] keys --------------------------------

        struct WalkerClassData
        {
            bool optedIn = false;
            char torsoName[kObj76NameBytes + 1] = {};
            TU::Config head = WH::DefaultConfig();
        };

        // Keyed by the packed eight-character ODF name (pond_class_label.cpp
        // does the same), so no class pointer is kept across missions.
        SRWLOCK g_ClassLock = SRWLOCK_INIT;
        std::unordered_map<uint64_t, WalkerClassData> g_Classes;

        constexpr size_t kRawValueBytes = 32;
        struct RawWalkerKeys
        {
            char torsoName[kRawValueBytes];
            char yawRate[kRawValueBytes];
            char yawAlpha[kRawValueBytes];
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

        // As tracked_vehicle_class.cpp ReadTrackedKeys. Outside BuildClass
        // the scope open loads the ODF (once per class: the result is cached).
        bool ReadWalkerKeys(const char* odfFile, RawWalkerKeys& keys)
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
                constexpr uint32_t section = TP::OdfHash("WalkerClass");
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("torsoName")), keys.torsoName);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawRate")), keys.yawRate);
                CopyRaw(g_RawGet(&scope, section, TP::OdfHash("yawAlpha")), keys.yawAlpha);
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

        // torsoName = "AGE11TY1": quotes optional. False when it does not fit
        // a model node name (char[8]).
        bool ParseNodeName(const char* raw, char (&out)[kObj76NameBytes + 1])
        {
            out[0] = 0;
            while (*raw == ' ' || *raw == '\t' || *raw == '"')
                ++raw;
            size_t n = 0;
            while (raw[n] && raw[n] != '"' && raw[n] != ' ' && raw[n] != '\t' && raw[n] != '\r' && raw[n] != '\n')
            {
                if (n >= kObj76NameBytes)
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

        bool ReadPackedClassName(const void* self, uint64_t& packed)
        {
            __try
            {
                const uint8_t* cls = *reinterpret_cast<uint8_t* const*>(
                    reinterpret_cast<const uint8_t*>(self) + kObjClass);
                if (!cls)
                    return false;
                std::memcpy(&packed, cls + kClassPackedNameOffset, sizeof(packed));
                return packed != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        WalkerClassData BuildClassData(uint64_t packed)
        {
            char odfName[kObj76NameBytes + 1] = {};
            std::memcpy(odfName, &packed, sizeof(packed));
            char odfFile[16] = {};
            std::snprintf(odfFile, sizeof(odfFile), "%.8s.odf", odfName);

            WalkerClassData data{};
            RawWalkerKeys keys{};
            if (!ReadWalkerKeys(odfFile, keys))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: [WalkerClass] could not be read; stock walker", odfName);
                return data;
            }
            if (!keys.torsoName[0])
            {
                LogShimA(LogLevel::Info, kComponent,
                    "ODF %.8s: no [WalkerClass] torsoName; stock walker", odfName);
                return data;
            }
            if (!ParseNodeName(keys.torsoName, data.torsoName) || !data.torsoName[0])
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: torsoName empty or longer than %u characters; stock walker",
                    odfName, static_cast<unsigned>(kObj76NameBytes));
                return data;
            }
            TU::Config head = WH::DefaultConfig();
            ParseFloatKey(keys.yawRate, head.yawRate);
            ParseFloatKey(keys.yawAlpha, head.yawAlpha);
            ParseFloatKey(keys.yawMin, head.yawMin);
            ParseFloatKey(keys.yawMax, head.yawMax);
            const bool limitKeySet = keys.yawMin[0] != 0 || keys.yawMax[0] != 0;
            data.head = WH::SanitizeConfig(head);
            if (limitKeySet && !data.head.limited)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "ODF %.8s: yawMin/yawMax ignored; they are radians with yawMin <= 0 <= yawMax inside +-pi",
                    odfName);
            }
            data.optedIn = true;
            LogShimA(LogLevel::Info, kComponent,
                "ODF %.8s: free head on (M1, legs not posed) torso=%s yawRate=%.2f yawAlpha=%.2f limits=%s%.2f..%.2f",
                odfName, data.torsoName, data.head.yawRate, data.head.yawAlpha,
                data.head.limited ? "" : "none ", data.head.yawMin, data.head.yawMax);
            return data;
        }

        bool LookupClass(const void* self, WalkerClassData& out)
        {
            uint64_t packed = 0;
            if (!ReadPackedClassName(self, packed))
                return false;
            AcquireSRWLockShared(&g_ClassLock);
            const auto it = g_Classes.find(packed);
            const bool found = it != g_Classes.end();
            if (found)
                out = it->second;
            ReleaseSRWLockShared(&g_ClassLock);
            if (found)
                return true;

            // Once per ODF name: the read and its log line.
            out = BuildClassData(packed);
            AcquireSRWLockExclusive(&g_ClassLock);
            g_Classes[packed] = out;
            ReleaseSRWLockExclusive(&g_ClassLock);
            return true;
        }

        // ---- per object ---------------------------------------------------

        enum class Gate
        {
            Unseen,
            Twist,
            NotSinglePlayer,
            NotUser,
            Dead,
            TorsoMissing,
            Unreadable,
            Fault,
        };

        const char* GateName(Gate gate)
        {
            switch (gate)
            {
            case Gate::Twist: return "twist";
            case Gate::NotSinglePlayer: return "stock (not single player)";
            case Gate::NotUser: return "stock (not the user's craft)";
            case Gate::Dead: return "stock (dead)";
            case Gate::TorsoMissing: return "stock (torso node not a root child)";
            case Gate::Unreadable: return "stock (object unreadable)";
            case Gate::Fault: return "stock (fault during the swap)";
            default: return "unseen";
            }
        }

        constexpr int kTorsoUnseen = -1;
        constexpr int kTorsoMissing = 0;
        constexpr int kTorsoFound = 1;

        struct HeadState
        {
            const void* obj76 = nullptr;  // identity check against address reuse
            float delta = 0.0f;           // head yaw relative to the legs, + left
            float rate = 0.0f;            // head slew rate, rad/s
            Gate gate = Gate::Unseen;
            int torso = kTorsoUnseen;
            bool aimRerunLogged = false;
            bool postSimLogged = false;
            int traceDeltaBucket = INT_MIN;
            int traceTurnSign = INT_MIN;
            int traceMoving = INT_MIN;
        };

        SRWLOCK g_StateLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, HeadState> g_States;

        HeadState LoadState(const void* self, const void* obj76)
        {
            HeadState state;
            AcquireSRWLockShared(&g_StateLock);
            const auto it = g_States.find(reinterpret_cast<uintptr_t>(self));
            if (it != g_States.end() && it->second.obj76 == obj76)
                state = it->second;
            ReleaseSRWLockShared(&g_StateLock);
            state.obj76 = obj76;
            return state;
        }

        void StoreState(const void* self, const HeadState& state)
        {
            AcquireSRWLockExclusive(&g_StateLock);
            g_States[reinterpret_cast<uintptr_t>(self)] = state;
            ReleaseSRWLockExclusive(&g_StateLock);
        }

        volatile long g_GateLogBudget = 400;
        volatile long g_InputLogBudget = 600;
        volatile long g_TraceLogBudget = 600;

        bool TakeBudget(volatile long& budget)
        {
            return InterlockedDecrement(&budget) >= 0;
        }

        bool ReadRoot(const void* self, uint8_t*& obj76, uint32_t& flags)
        {
            __try
            {
                obj76 = *reinterpret_cast<uint8_t* const*>(reinterpret_cast<const uint8_t*>(self) + kObjObj76);
                if (!obj76)
                    return false;
                flags = *reinterpret_cast<const uint32_t*>(obj76 + kObj76Flags);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Torso = a direct child of the root named torsoName (8 chars,
        // case-insensitive). More than kMaxRootChildren children fails closed.
        int FindTorso(const uint8_t* root, const char* torsoName)
        {
            __try
            {
                const uint8_t* child = *reinterpret_cast<const uint8_t* const*>(root + kObj76Child);
                for (int i = 0; child; ++i)
                {
                    if (i >= kMaxRootChildren)
                        return kTorsoMissing;
                    char name[kObj76NameBytes + 1] = {};
                    std::memcpy(name, child + kObj76Name, kObj76NameBytes);
                    if (_strnicmp(name, torsoName, kObj76NameBytes) == 0)
                        return kTorsoFound;
                    child = *reinterpret_cast<const uint8_t* const*>(child + kObj76Sibling);
                }
                return kTorsoMissing;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kTorsoMissing;
            }
        }

        Vec3 ReadVec(const uint8_t* base, size_t offset)
        {
            Vec3 v;
            std::memcpy(&v, base + offset, sizeof(v));
            return v;
        }

        void WriteVec(uint8_t* base, size_t offset, Vec3 v)
        {
            std::memcpy(base + offset, &v, sizeof(v));
        }

        float YawDegrees(Vec3 front)
        {
            return std::atan2(front.x, front.z) * (180.0f / TU::kPi);
        }

        // Steps 1-4: everything read first, then the writes.
        struct TwistFrame
        {
            uint8_t* obj76 = nullptr;
            uint8_t* ctrl = nullptr;
            float steer = 0.0f;   // original ctrl.steer (UserProcess's value this frame)
            float strafe = 0.0f;  // original ctrl.strafe
            int rawAxis = 0;
            int steerLeft = 0;
            int steerRight = 0;
            float mouse = 0.0f;
            float legsCommand = 0.0f;
            float newRate = 0.0f;
            float headStep = 0.0f;
            Vec3 headFront{};
            Vec3 legsFront{};
        };

        bool PrepareTwist(uint8_t* self, float dt, const TU::Config& config, const HeadState& state,
                          uint8_t* obj76, TwistFrame& f)
        {
            __try
            {
                uint8_t* ctrl = *reinterpret_cast<uint8_t**>(self + kObjControls);
                if (!ctrl)
                    return false;
                f.obj76 = obj76;
                f.ctrl = ctrl;
                f.steer = *reinterpret_cast<const float*>(ctrl + kCtrlSteer);
                f.strafe = *reinterpret_cast<const float*>(ctrl + kCtrlStrafe);
                f.rawAxis = *g_SteerAxis;
                f.steerLeft = *g_SteerLeft;
                f.steerRight = *g_SteerRight;
                const Vec3 right = ReadVec(obj76, kObj76Right);
                const Vec3 front = ReadVec(obj76, kObj76Front);
                if (!TP::Finite(right) || !TP::Finite(front))
                    return false;

                f.mouse = WH::MouseCommand(f.rawAxis);
                f.legsCommand = WH::LegTurnCommand(f.steerLeft, f.steerRight, f.strafe);
                f.newRate = TU::SlewRate(config, state.rate, f.mouse, state.delta, dt);
                // Trapezoid, as the tracked turret.
                f.headStep = 0.5f * (state.rate + f.newRate) * dt;

                Vec3 legsRight, legsFront;
                WH::LegsAxes(right, front, state.delta, legsRight, legsFront);
                f.headFront = front;
                f.legsFront = legsFront;

                *reinterpret_cast<float*>(ctrl + kCtrlSteer) = f.legsCommand;
                *reinterpret_cast<float*>(ctrl + kCtrlStrafe) = 0.0f;
                WriteVec(obj76, kObj76Right, legsRight);
                WriteVec(obj76, kObj76Front, legsFront);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct TwistResult
        {
            float delta = 0.0f;
            float legsTurn = 0.0f;
            Vec3 legsFront{};
            Vec3 headFront{};
            Vec3 veloc{};
            FnSimulate updateWeaponAim = nullptr;  // null: no weapon list
        };

        // Step 6, all but the slot 38 call (made by the caller outside SEH).
        bool FinishTwist(uint8_t* self, const TU::Config& config, const HeadState& state,
                         const TwistFrame& f, TwistResult& r)
        {
            __try
            {
                uint8_t* obj76 = f.obj76;
                const Vec3 right = ReadVec(obj76, kObj76Right);
                const Vec3 up = ReadVec(obj76, kObj76Up);
                const Vec3 front = ReadVec(obj76, kObj76Front);
                const bool finite = TP::Finite(right) && TP::Finite(up) && TP::Finite(front);
                r.legsTurn = finite ? WH::YawChangeLeft(f.legsFront, front, up) : 0.0f;
                r.delta = WH::NextDelta(config, state.delta, f.headStep, r.legsTurn);
                if (finite)
                {
                    Vec3 headRight, headFront;
                    WH::HeadAxes(right, front, r.delta, headRight, headFront);
                    WriteVec(obj76, kObj76Right, headRight);
                    WriteVec(obj76, kObj76Front, headFront);
                    r.headFront = headFront;
                }
                else
                {
                    r.delta = 0.0f;  // leave the stock result; the root becomes the head
                    r.headFront = front;
                }
                r.legsFront = front;
                r.veloc = ReadVec(self, kObjVeloc);

                *reinterpret_cast<float*>(f.ctrl + kCtrlSteer) = f.steer;
                *reinterpret_cast<float*>(f.ctrl + kCtrlStrafe) = f.strafe;

                if (*reinterpret_cast<void* const*>(self + kObjWeaponList))
                {
                    void* const* vtable = *reinterpret_cast<void* const* const*>(self);
                    r.updateWeaponAim = reinterpret_cast<FnSimulate>(vtable[kUpdateWeaponAimSlot]);
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Puts the root back in the head frame and restores the controls after a
        // fault in the stock Simulate. Guarded: it runs during an unwind, where a
        // second fault would be a hard crash.
        void RestoreAfterFault(const TwistFrame& f, float delta)
        {
            __try
            {
                uint8_t* obj76 = f.obj76;
                Vec3 headRight, headFront;
                WH::HeadAxes(ReadVec(obj76, kObj76Right), ReadVec(obj76, kObj76Front), delta, headRight, headFront);
                WriteVec(obj76, kObj76Right, headRight);
                WriteVec(obj76, kObj76Front, headFront);
                *reinterpret_cast<float*>(f.ctrl + kCtrlSteer) = f.steer;
                *reinterpret_cast<float*>(f.ctrl + kCtrlStrafe) = f.strafe;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // Runs the stock Simulate with the root in the legs frame. If it raises and
        // something up the stack catches it, restore the head frame and controls, so
        // the next frame does not apply -delta twice.
        void CallStockInLegsFrame(FnSimulate stock, void* self, float dt, const TwistFrame& f, float delta)
        {
            __try
            {
                stock(self, dt);
            }
            __finally
            {
                if (AbnormalTermination())
                    RestoreAfterFault(f, delta);
            }
        }

        // ---- change-only decision logs --------------------------------------

        void LogGateChange(const void* self, HeadState& state, Gate gate)
        {
            if (gate == state.gate)
                return;
            if (TakeBudget(g_GateLogBudget))
            {
                LogShimA(LogLevel::Info, kComponent, "walker %p: %s -> %s (delta %.1f deg)",
                    self, GateName(state.gate), GateName(gate), state.delta * (180.0f / TU::kPi));
            }
            state.gate = gate;
        }

        // Research doc section 4 step 1: the raw axis read in Simulate must
        // track ctrl.steer under mouse-only input. One line whenever the
        // quantised inputs change, with running counts of mouse-only frames
        // and of those that tracked.
        struct InputKey
        {
            int mouse = INT_MIN;
            int steer = INT_MIN;
            int arrows = INT_MIN;
            int strafe = INT_MIN;
        };
        InputKey g_LastInput;
        unsigned long g_MouseOnlyFrames = 0;
        unsigned long g_TrackedFrames = 0;

        int Quantise(float v)
        {
            return std::isfinite(v) ? static_cast<int>(std::lround(v * 4.0f)) : INT_MAX;
        }

        void LogInputs(const TwistFrame& f)
        {
            const float rawSteer = static_cast<float>(f.rawAxis) * WH::kAxisScale;
            const bool mouseOnly = f.steerLeft == 0 && f.steerRight == 0 && std::fabs(f.strafe) < 0.05f;
            const bool tracks = WH::SteerTracksMouse(rawSteer, f.steer);
            if (mouseOnly)
            {
                ++g_MouseOnlyFrames;
                if (tracks)
                    ++g_TrackedFrames;
            }
            InputKey key;
            key.mouse = Quantise(rawSteer);
            key.steer = Quantise(f.steer);
            key.arrows = f.steerLeft - f.steerRight;
            key.strafe = Quantise(f.strafe);
            if (key.mouse == g_LastInput.mouse && key.steer == g_LastInput.steer &&
                key.arrows == g_LastInput.arrows && key.strafe == g_LastInput.strafe)
                return;
            g_LastInput = key;
            if (!TakeBudget(g_InputLogBudget))
                return;
            LogShimA(LogLevel::Info, kComponent,
                "inputs raw axis 0x%08X (%.2f) ctrl.steer=%.2f arrows L%d R%d ctrl.strafe=%.2f -> head %.2f legs %.2f; "
                "%s%s (mouse-only frames %lu, tracked %lu)",
                static_cast<unsigned>(f.rawAxis), rawSteer, f.steer, f.steerLeft, f.steerRight, f.strafe,
                f.mouse, f.legsCommand,
                mouseOnly ? "mouse-only " : "keys ",
                mouseOnly ? (tracks ? "tracks" : "DOES NOT TRACK") : "-",
                g_MouseOnlyFrames, g_TrackedFrames);
        }

        // One line when the 5-degree delta bucket, the legs' turn direction
        // or moving/still changes. Root yaw before/after shows the root is
        // the head (it moves only by the head step); the velocity along the
        // legs' axes shows the legs heading drives locomotion.
        void LogSwap(const void* self, HeadState& state, const TwistFrame& f, const TwistResult& r)
        {
            constexpr float kDeg = 180.0f / TU::kPi;
            const int bucket = static_cast<int>(std::lround(r.delta * kDeg / 5.0f));
            const int turnSign = r.legsTurn > 1.0e-4f ? 1 : (r.legsTurn < -1.0e-4f ? -1 : 0);
            const int moving = TP::Length(r.veloc) > 0.5f ? 1 : 0;
            if (bucket == state.traceDeltaBucket && turnSign == state.traceTurnSign && moving == state.traceMoving)
                return;
            state.traceDeltaBucket = bucket;
            state.traceTurnSign = turnSign;
            state.traceMoving = moving;
            if (!TakeBudget(g_TraceLogBudget))
                return;
            const Vec3 legsRight = TP::Cross(Vec3{ 0.0f, 1.0f, 0.0f }, r.legsFront);
            LogShimA(LogLevel::Info, kComponent,
                "walker %p swap: delta %.1f deg (head step %.2f, legs turn %.2f) root/head yaw %.1f -> %.1f "
                "legs yaw %.1f; veloc legs fwd %.2f right %.2f, head fwd %.2f",
                self, r.delta * kDeg, f.headStep * kDeg, r.legsTurn * kDeg,
                YawDegrees(f.headFront), YawDegrees(r.headFront), YawDegrees(r.legsFront),
                TP::Dot(r.veloc, r.legsFront), TP::Dot(r.veloc, legsRight), TP::Dot(r.veloc, r.headFront));
        }

        // ---- hooks ------------------------------------------------------------

        void __fastcall WalkerSimulateHook(void* self, void* /*edx*/, float dt)
        {
            WalkerClassData cls;
            if (!LookupClass(self, cls) || !cls.optedIn)
            {
                g_StockSimulate(self, dt);
                return;
            }

            uint8_t* obj76 = nullptr;
            uint32_t flags = 0;
            const bool readable = ReadRoot(self, obj76, flags);
            HeadState state = LoadState(self, obj76);

            Gate gate = Gate::Twist;
            if (!readable)
                gate = Gate::Unreadable;
            else if (!Hooks::IsSinglePlayerSession())
                gate = Gate::NotSinglePlayer;
            else if (flags & kObj76FlagDead)
                gate = Gate::Dead;
            else if (!(flags & kObj76FlagUser))
                gate = Gate::NotUser;
            else
            {
                if (state.torso == kTorsoUnseen)
                    state.torso = FindTorso(obj76, cls.torsoName);
                if (state.torso != kTorsoFound)
                    gate = Gate::TorsoMissing;
            }
            LogGateChange(self, state, gate);

            if (gate != Gate::Twist)
            {
                state.delta = 0.0f;
                state.rate = 0.0f;
                StoreState(self, state);
                g_StockSimulate(self, dt);
                return;
            }

            auto* bytes = static_cast<uint8_t*>(self);
            TwistFrame frame;
            if (!PrepareTwist(bytes, dt, cls.head, state, obj76, frame))
            {
                LogGateChange(self, state, Gate::Fault);
                state.delta = 0.0f;
                state.rate = 0.0f;
                StoreState(self, state);
                g_StockSimulate(self, dt);
                return;
            }
            LogInputs(frame);

            CallStockInLegsFrame(g_StockSimulate, self, dt, frame, state.delta);

            TwistResult result;
            if (!FinishTwist(bytes, cls.head, state, frame, result))
            {
                LogGateChange(self, state, Gate::Fault);
                state.delta = 0.0f;
                state.rate = 0.0f;
                StoreState(self, state);
                return;
            }
            state.delta = result.delta;
            state.rate = frame.newRate;

            // The stock tail aimed the weapons with the root in the legs
            // frame; aim again along the head.
            if (result.updateWeaponAim)
            {
                result.updateWeaponAim(self, dt);
                if (!state.aimRerunLogged)
                {
                    state.aimRerunLogged = true;
                    LogShimA(LogLevel::Info, kComponent,
                        "walker %p: UpdateWeaponAim (slot %u) re-run after swap-back, target %p",
                        self, static_cast<unsigned>(kUpdateWeaponAimSlot),
                        reinterpret_cast<void*>(result.updateWeaponAim));
                }
            }
            LogSwap(self, state, frame, result);
            StoreState(self, state);
        }

        void __fastcall WalkerPostSimulateHook(void* self, void* /*edx*/, float dt)
        {
            g_StockPostSimulate(self, dt);

            // M1: confirm the hook point for the leg re-pose (research doc
            // section 5a Q3), once per twisting object.
            bool log = false;
            float delta = 0.0f;
            AcquireSRWLockExclusive(&g_StateLock);
            const auto it = g_States.find(reinterpret_cast<uintptr_t>(self));
            if (it != g_States.end() && it->second.gate == Gate::Twist && !it->second.postSimLogged)
            {
                it->second.postSimLogged = true;
                delta = it->second.delta;
                log = true;
            }
            ReleaseSRWLockExclusive(&g_StateLock);
            if (log)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "walker %p: PostSimulate (slot %u) reached while twisting, delta %.1f deg",
                    self, static_cast<unsigned>(kPostSimulateSlot), delta * (180.0f / TU::kPi));
            }
        }

        // ---- install ------------------------------------------------------------

        void LogInstallFailure(const char* what)
        {
            if (g_InstallFailureLogged)
                return;
            g_InstallFailureLogged = true;
            LogShimA(LogLevel::Warn, kComponent, "walker free head not installed: %s", what);
        }

        void GiveUp(const char* what)
        {
            g_GaveUp = true;
            LogInstallFailure(what);
        }

        bool ReadSlot(uintptr_t slot, void*& value)
        {
            __try
            {
                value = *reinterpret_cast<void* const*>(slot);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
    }

    void InstallWalkerFreeHeadIfPossible()
    {
        if (g_Installed || g_GaveUp)
            return;

        // Signature resolves first (they miss until the image is readable),
        // so the one engine-row bind below runs on a settled image.
        const uintptr_t openScope = HookEngine::ResolveNamedAddress("ParameterDB::OpenScope");
        const uintptr_t rawGet = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
        const uintptr_t popScope = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
        const uintptr_t steerAxis = HookEngine::ResolveNamedAddress("UserInput::SteerAxis");
        const uintptr_t steerLeft = HookEngine::ResolveNamedAddress("UserInput::SteerLeft");
        const uintptr_t steerRight = HookEngine::ResolveNamedAddress("UserInput::SteerRight");
        if (!openScope || !rawGet || !popScope || !steerAxis || !steerLeft || !steerRight)
        {
            LogInstallFailure("one or more patches.json resolves missing");
            return;
        }

        uint32_t walkerVtable = 0;
        uint32_t walkerSimulate = 0;
        uint32_t craftPostSimulate = 0;
        const HookEngine::EngineRow rows[] = {
            { "WalkerVtable", &walkerVtable },
            { "WalkerSimulate", &walkerSimulate },
            { "CraftPostSimulate", &craftPostSimulate },
        };
        if (!HookEngine::BindEngineRows("Walker free head", rows))
        {
            GiveUp("WalkerVtable/WalkerSimulate/CraftPostSimulate rows did not bind");
            return;
        }
        if (!Hooks::VtableTypeNameMatches(walkerVtable, ".?AVWalker@@"))
        {
            GiveUp("WalkerVtable is not .?AVWalker@@");
            return;
        }

        const uintptr_t simulateSlot = walkerVtable + kSimulateSlot * sizeof(void*);
        const uintptr_t postSimulateSlot = walkerVtable + kPostSimulateSlot * sizeof(void*);
        void* simulateCurrent = nullptr;
        void* postSimulateCurrent = nullptr;
        if (!ReadSlot(simulateSlot, simulateCurrent) || !ReadSlot(postSimulateSlot, postSimulateCurrent))
        {
            GiveUp("WalkerVtable slots unreadable");
            return;
        }
        void* const simulateHook = reinterpret_cast<void*>(&WalkerSimulateHook);
        void* const postSimulateHook = reinterpret_cast<void*>(&WalkerPostSimulateHook);
        if ((simulateCurrent != reinterpret_cast<void*>(static_cast<uintptr_t>(walkerSimulate)) &&
             simulateCurrent != simulateHook) ||
            (postSimulateCurrent != reinterpret_cast<void*>(static_cast<uintptr_t>(craftPostSimulate)) &&
             postSimulateCurrent != postSimulateHook))
        {
            char what[160] = {};
            std::snprintf(what, sizeof(what),
                "WalkerVtable slot owner mismatch (slot 15 = %p, slot 16 = %p); left untouched",
                simulateCurrent, postSimulateCurrent);
            GiveUp(what);
            return;
        }

        g_OpenScope = reinterpret_cast<FnOpenScope>(openScope);
        g_RawGet = reinterpret_cast<FnRawGet>(rawGet);
        g_PopScope = reinterpret_cast<FnPopScope>(popScope);
        g_SteerAxis = reinterpret_cast<const volatile int32_t*>(steerAxis);
        g_SteerLeft = reinterpret_cast<const volatile int8_t*>(steerLeft);
        g_SteerRight = reinterpret_cast<const volatile int8_t*>(steerRight);
        g_StockSimulate = reinterpret_cast<FnSimulate>(static_cast<uintptr_t>(walkerSimulate));
        g_StockPostSimulate = reinterpret_cast<FnSimulate>(static_cast<uintptr_t>(craftPostSimulate));

        // PostSimulate first: on its own it only logs.
        if (postSimulateCurrent != postSimulateHook && !Hooks::WritePointerValue(postSimulateSlot, postSimulateHook))
        {
            GiveUp("WalkerVtable slot 16 write failed");
            return;
        }
        if (simulateCurrent != simulateHook && !Hooks::WritePointerValue(simulateSlot, simulateHook))
        {
            GiveUp("WalkerVtable slot 15 write failed");
            return;
        }

        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
            "installed (M1): WalkerVtable 0x%08X slot 15 Simulate and slot 16 PostSimulate wrapped; "
            "opt-in per ODF ([WalkerClass] torsoName), user's walker, single player only",
            walkerVtable);
    }

    bool IsWalkerFreeHeadInstalled()
    {
        return g_Installed;
    }
}
