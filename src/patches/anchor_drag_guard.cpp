// anchor_drag_guard.cpp -- AnchorRocket drag cannot write NaN or fling units.
//
// Sites (AnchorRocket::Simulate 0x0046D8C0, vtable 0x008756A0 slot 4, GOG
// Redux 2.2.301; FUN_0046d8c0.c lines 69-108), each 17 bytes:
//   linear 0x0046D9C3  movss xmm0,[ebp-0x90] (speed)
//                      comiss xmm0,[ebp-0x94] (drag = accelDrag * dt)
//                      jbe 0x0046DA4A (v = 0), else fall through to 0x0046D9D4
//                      (v *= 1 - [ebp-0x94] / [ebp-0x90])
//   spin   0x0046DAF5  movss xmm0,[ebp-0x98] (|omega|)
//                      comiss xmm0,[ebp-0x8C] (drag = alphaDrag * dt)
//                      jbe 0x0046DB76, else fall through to 0x0046DB06
// Each site becomes jmp <thunk> + 12 NOPs. No branch in the function lands
// inside either range. The thunk calls AnchorDrag::Decide, which may rewrite
// the drag local (read again only by the divide below), then jumps to the
// stock zero or scale branch. Both branches reload eax/ecx/edx/xmm0/xmm1
// before use, so the thunk may clobber them.
//
// Multiplayer: the result differs from stock only where stock wrote NaN or
// applied a negative-drag boost (custom ODFs); an unpatched peer diverges in
// exactly those cases.

#include "anchor_drag_guard.h"
#include "anchor_drag_guard_install.h"

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
    namespace AnchorDrag
    {
        namespace
        {
            constexpr const char* kComponent = "ANCHORDRAG";
            constexpr uint32_t kSiteLength = 17;

            const uint8_t kLinearSite[kSiteLength] = { 0xF3, 0x0F, 0x10, 0x85, 0x70, 0xFF, 0xFF, 0xFF, 0x0F,
                                                       0x2F, 0x85, 0x6C, 0xFF, 0xFF, 0xFF, 0x76, 0x76 };
            const uint8_t kSpinSite[kSiteLength] = { 0xF3, 0x0F, 0x10, 0x85, 0x68, 0xFF, 0xFF, 0xFF, 0x0F,
                                                     0x2F, 0x85, 0x74, 0xFF, 0xFF, 0xFF, 0x76, 0x70 };

            std::atomic<bool> g_Done{ false };
            volatile long g_LogBudget = 16;

            uint32_t g_LinearScale = 0;  // 0x0046D9D4
            uint32_t g_LinearZero = 0;   // 0x0046DA4A
            uint32_t g_SpinScale = 0;    // 0x0046DB06
            uint32_t g_SpinZero = 0;     // 0x0046DB76

            void LogChange(const char* which, float speed, float drag, const Decision& d)
            {
                if (InterlockedDecrement(&g_LogBudget) < 0)
                    return;
                if (d.zero)
                    LogShimA(LogLevel::Warn, kComponent,
                             "%s drag %.6g on speed %.6g: no usable factor, target stopped instead of NaN",
                             which, static_cast<double>(drag), static_cast<double>(speed));
                else
                    LogShimA(LogLevel::Warn, kComponent,
                             "%s drag %.6g on speed %.6g: boost capped (drag now %.6g)", which,
                             static_cast<double>(drag), static_cast<double>(speed), static_cast<double>(d.drag));
            }

            // Returns 1 for the zero branch. Writes the (possibly capped) drag.
            int DecideAndLog(const char* which, float speed, float* drag, float cap)
            {
                const float stockDrag = *drag;
                const Decision d = Decide(speed, stockDrag, cap);
                const bool stockZero = !(speed > stockDrag);
                // The zero branch never changes drag; the scale branch only
                // runs with an ordered (non-NaN) drag, so != is safe there.
                if (d.zero != stockZero || (!d.zero && d.drag != stockDrag))
                    LogChange(which, speed, stockDrag, d);
                *drag = d.drag;
                return d.zero ? 1 : 0;
            }

            int __cdecl DecideLinear(float speed, float* drag)
            {
                return DecideAndLog("linear", speed, drag, kLinearBoostCap);
            }

            int __cdecl DecideSpin(float speed, float* drag)
            {
                return DecideAndLog("spin", speed, drag, kAngularBoostCap);
            }

            __declspec(naked) void LinearThunk()
            {
                __asm
                {
                    lea eax, [ebp - 0x94]
                    push eax                        // &drag
                    push dword ptr [ebp - 0x90]     // speed
                    call DecideLinear
                    add esp, 8
                    test eax, eax
                    jnz linear_zero
                    jmp dword ptr [g_LinearScale]
                linear_zero:
                    jmp dword ptr [g_LinearZero]
                }
            }

            __declspec(naked) void SpinThunk()
            {
                __asm
                {
                    lea eax, [ebp - 0x8C]
                    push eax                        // &drag
                    push dword ptr [ebp - 0x98]     // |omega|
                    call DecideSpin
                    add esp, 8
                    test eax, eax
                    jnz spin_zero
                    jmp dword ptr [g_SpinScale]
                spin_zero:
                    jmp dword ptr [g_SpinZero]
                }
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock AnchorRocket drag", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_ANCHOR_DRAG_GUARD", "BZR_DISABLE_ANCHOR_DRAG_GUARD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            // The site's own bytes give both branch targets: the fall-through
            // after the jbe and the jbe's rel8 destination.
            void Targets(uint32_t site, const uint8_t (&bytes)[kSiteLength], uint32_t& scale, uint32_t& zero)
            {
                scale = site + kSiteLength;
                zero = scale + static_cast<uint32_t>(static_cast<int8_t>(bytes[kSiteLength - 1]));
            }

            bool WriteJump(uint32_t site, void* thunk)
            {
                uint8_t patch[kSiteLength];
                std::memset(patch, 0x90, sizeof(patch));
                patch[0] = 0xE9;
                const int32_t rel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(thunk) - (site + 5));
                std::memcpy(patch + 1, &rel, sizeof(rel));
                return HookEngine::WriteMemory(site, patch, sizeof(patch));
            }

            bool DoInstall()
            {
                uint32_t linear = 0, spin = 0;
                const HookEngine::EngineRow rows[] = {
                    { "AnchorRocketLinearDragCompare", &linear },
                    { "AnchorRocketSpinDragCompare", &spin },
                };
                if (!HookEngine::BindEngineRows("AnchorRocket drag guard", rows))
                    return Fail("a drag compare site failed its byte guard");

                Targets(linear, kLinearSite, g_LinearScale, g_LinearZero);
                Targets(spin, kSpinSite, g_SpinScale, g_SpinZero);

                if (!WriteJump(linear, reinterpret_cast<void*>(&LinearThunk)))
                    return Fail("the linear site could not be written");
                if (!WriteJump(spin, reinterpret_cast<void*>(&SpinThunk)))
                {
                    HookEngine::WriteMemory(linear, kLinearSite, sizeof(kLinearSite));
                    return Fail("the spin site could not be written (linear site restored)");
                }

                LogShimA(LogLevel::Info, kComponent,
                         "installed: linear=0x%08X (scale 0x%08X, zero 0x%08X) spin=0x%08X (scale 0x%08X, "
                         "zero 0x%08X) minSpeed=%g caps=%g m/s, %g rad/s",
                         linear, g_LinearScale, g_LinearZero, spin, g_SpinScale, g_SpinZero,
                         static_cast<double>(kMinSpeed), static_cast<double>(kLinearBoostCap),
                         static_cast<double>(kAngularBoostCap));
                return true;
            }
        }

        void InstallAnchorDragGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] AnchorDragGuard = 0)");
                return;
            }
            DoInstall();
        }
    }
}
