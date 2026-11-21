// nan_transform_guard.cpp -- a NaN or infinite transform or motion is
// repaired at the object step instead of spreading.
//
// Hook: entry detour on GameObject::Simulate (0x004DEEC0, void __cdecl(obj76*),
// plain `ret`; FUN_004deec0.c). Layout in nan_transform_guard.h.
//   PRE   go = obj76+0x8C (FUN_00479f30). If go's speed/velocity/omega is not
//         finite, zero all three. Snapshot the 0x40-byte transform obj76+0x20.
//   STEP  the stock function (or the next detour in the chain).
//   POST  unless the object was flagged deleted (obj76+0x14 & 0x200, stock
//         returns early on it too), if the transform is not finite: restore
//         the snapshot, or failing that reset a bad rotation to identity;
//         zero the motion; and copy the repaired transform into the
//         GameObject's true transform (go+0x28) when that is not finite
//         either, since the remote path copies it back into obj76+0x20 at
//         the start of every step.
// The good path is the exponent tests and one 64-byte copy, nothing else.
//
// Chaining: [Network] RemoteSmoothingMs entry-detours the same function
// (remote_object_smoothing.cpp, 9-byte steal). This installer runs after it;
// when the entry already holds a jmp rel32 it steals exactly those 5 bytes
// (the trampoline re-bases the rel32), so both hooks run.
//
// Multiplayer: the guard only changes state that is already NaN or infinite,
// which would desync (and usually wreck) the session anyway.

#include "nan_transform_guard.h"
#include "nan_transform_guard_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace NanTransform
    {
        namespace
        {
            constexpr const char* kComponent = "NANTRANSFORM";
            constexpr uint32_t kObjFlagsOffset = 0x14;
            constexpr uint32_t kObjFlagDeleted = 0x200;
            constexpr uint32_t kObjTransformOffset = 0x20;
            constexpr uint32_t kObjGameObjectOffset = 0x8C;
            constexpr uint32_t kGoPhysicsOffset = 0x114;
            constexpr uint32_t kGoTrueTransformOffset = 0x28;

            // push ebp; mov ebp,esp; sub esp,0x1A8 (no relative operands).
            const uint8_t kPrologue[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xA8, 0x01, 0x00, 0x00 };
            const uint8_t kChainedEntry[1] = { 0xE9 };

            using FnSimulate = void(__cdecl*)(void* obj);

            std::atomic<bool> g_Done{ false };
            InlineDetour32 g_Detour = {};
            FnSimulate volatile g_Orig = nullptr;
            using FnUpdatePosition = void(__thiscall*)(void* go);
            FnUpdatePosition g_UpdatePosition = nullptr;  // GameObject::UpdatePosition 0x004DB100
            volatile long g_MotionLogBudget = 16;
            volatile long g_TransformLogBudget = 16;

            uint8_t* GameObjectOf(uint8_t* obj)
            {
                return *reinterpret_cast<uint8_t**>(obj + kObjGameObjectOffset);
            }

            __declspec(noinline) void RepairMotionBeforeStep(uint8_t* obj, uint8_t* go)
            {
                ZeroMotion(go + kGoPhysicsOffset);
                if (InterlockedDecrement(&g_MotionLogBudget) >= 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "object 0x%08X (GameObject 0x%08X): speed/velocity/omega not finite before the "
                             "step; zeroed",
                             static_cast<unsigned>(reinterpret_cast<uintptr_t>(obj)),
                             static_cast<unsigned>(reinterpret_cast<uintptr_t>(go)));
            }

            __declspec(noinline) void RepairAfterStep(uint8_t* obj, const uint8_t* snapshot)
            {
                uint8_t* transform = obj + kObjTransformOffset;
                const Repair r = RepairTransform(transform, snapshot);
                uint8_t* go = GameObjectOf(obj);
                if (go)
                {
                    ZeroMotion(go + kGoPhysicsOffset);
                    uint8_t* trueTransform = go + kGoTrueTransformOffset;
                    if (!TransformFinite(trueTransform) && TransformFinite(transform))
                        std::memcpy(trueTransform, transform, kTransformBytes);
                    // The stock step already ran UpdatePosition on the bad
                    // transform; rerun it so the cached position and bounds
                    // are finite before collision/AI read them this frame.
                    if (g_UpdatePosition && TransformFinite(transform))
                        g_UpdatePosition(go);
                }
                if (InterlockedDecrement(&g_TransformLogBudget) >= 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "object 0x%08X (GameObject 0x%08X): transform not finite after the step; %s; "
                             "motion zeroed",
                             static_cast<unsigned>(reinterpret_cast<uintptr_t>(obj)),
                             static_cast<unsigned>(reinterpret_cast<uintptr_t>(go)), RepairName(r));
            }

            void __cdecl SimulateHook(void* objArg)
            {
                uint8_t* obj = static_cast<uint8_t*>(objArg);
                if (!obj)
                {
                    g_Orig(objArg);
                    return;
                }
                uint8_t* go = GameObjectOf(obj);
                if (go && !MotionFinite(go + kGoPhysicsOffset))
                    RepairMotionBeforeStep(obj, go);

                uint8_t snapshot[kTransformBytes];
                std::memcpy(snapshot, obj + kObjTransformOffset, kTransformBytes);

                g_Orig(objArg);

                if ((*reinterpret_cast<const uint32_t*>(obj + kObjFlagsOffset) & kObjFlagDeleted) != 0)
                    return;
                if (!TransformFinite(obj + kObjTransformOffset))
                    RepairAfterStep(obj, snapshot);
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock GameObject::Simulate", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_NAN_TRANSFORM_GUARD", "BZR_DISABLE_NAN_TRANSFORM_GUARD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t simulate = 0, remoteCopy = 0, updatePosition = 0;
                // The remote-copy row pins the obj76+0x20 / GO+0x28 layout this
                // file relies on; the entry row is bound (and cached) before
                // RemoteSmoothing detours it, so it still binds afterwards.
                const HookEngine::EngineRow rows[] = {
                    { "GameObjectSimulate", &simulate },
                    { "GameObjectSimulateRemoteCopy", &remoteCopy },
                    { "GameObjectUpdatePosition", &updatePosition },
                };
                if (!HookEngine::BindEngineRows("NaN transform guard", rows))
                    return Fail("GameObject::Simulate failed its byte guard");
                g_UpdatePosition = reinterpret_cast<FnUpdatePosition>(static_cast<uintptr_t>(updatePosition));

                uint8_t entry[sizeof(kPrologue)] = {};
                if (!HookEngine::ReadMemory(simulate, entry, sizeof(entry)))
                    return Fail("the entry bytes are unreadable");

                const bool stock = std::memcmp(entry, kPrologue, sizeof(kPrologue)) == 0;
                const bool chained = entry[0] == kChainedEntry[0];
                if (!stock && !chained)
                    return Fail("the entry is neither the stock prologue nor an earlier jmp detour");

                const bool ok = stock ? InstallInlineDetour32(g_Detour, simulate, reinterpret_cast<void*>(&SimulateHook),
                                                              sizeof(kPrologue), kPrologue, sizeof(kPrologue),
                                                              reinterpret_cast<void* volatile*>(&g_Orig))
                                      : InstallInlineDetour32(g_Detour, simulate, reinterpret_cast<void*>(&SimulateHook),
                                                              5, kChainedEntry, sizeof(kChainedEntry),
                                                              reinterpret_cast<void* volatile*>(&g_Orig));
                if (!ok)
                    return Fail("the entry detour could not be installed");

                LogShimA(LogLevel::Info, kComponent, "installed: simulate=0x%08X trampoline=0x%08X (%s)", simulate,
                         static_cast<unsigned>(reinterpret_cast<uintptr_t>(g_Orig)),
                         stock ? "stock entry" : "chained over an earlier detour");
                return true;
            }
        }

        void InstallNanTransformGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] NaNTransformGuard = 0)");
                return;
            }
            DoInstall();
        }
    }
}
