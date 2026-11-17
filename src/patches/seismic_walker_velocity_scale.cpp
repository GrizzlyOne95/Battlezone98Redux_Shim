// seismic_walker_velocity_scale.cpp
// BZR Open Shim - per-ODF walkerVelocityScale for SeismicWave ordnance.
//
// Stock walkerScale ([SeismicWaveClass]) scales only the angular kick a
// Thumper wave gives a walker. The linear kick is added to every mobile
// target alike, so walkers get launched like hover craft. This adds one
// optional key to the ordnance ODF:
//   [SeismicWaveClass]
//   walkerVelocityScale = 0.0   ; default 1.0 (stock); 0 = no launch
// It scales the whole linear velocity vector the wave adds to targets whose
// class signature is 'WALK'. Angular kick and damage stay stock.
//
// Addresses and frame offsets are GOG 2.2.301 (SHA256 8D71F56C...3377413),
// read from the shipping exe's disassembly; see patches.json rows
// SeismicWaveClassBuildingScaleRead and SeismicWaveSimulateAddVelocityCall.
//   - SeismicWaveClass ctor (0x005CEA80) reads its ODF keys through
//     ParameterDB::GetFloat (0x00589800, __thiscall(section, key, float* out,
//     float default), returns found in AL, ret 0x10) with ecx = its local
//     ParameterDB scope [ebp-0x14]. Its last read is buildingScale (section
//     0x7FF8E41B "seismicwaveclass", key 0x02168F61) into this+0xC0, at the
//     call 0x005CEE0A. That call is redirected so the scope is still live
//     when walkerVelocityScale (0xEB72A482) is read; the class is out-0xC0.
//   - SeismicWave Simulate (0x005CF510) stores its this at [ebp-0x254] once
//     in the prologue; the wave's class is [this+0xC]. For mobile targets it
//     calls GameObject::AddVelocity (0x004A75B0, __thiscall(const float*),
//     ret 4) at 0x005D08E1 with ecx = target [ebp-0x258] and the velocity
//     delta [ebp-0x34] pushed. That call is redirected to a thunk that adds
//     the wave this (from the caller frame) as the fastcall edx argument.
// MP: deterministic only when every peer runs an OpenShim build with this
// patch; a stock or older peer applies the full kick and diverges.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>
#include <unordered_map>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            constexpr uint32_t kSeismicWaveClassSectionHash = 0x7FF8E41Bu;
            constexpr uint32_t kBuildingScaleKeyHash = 0x02168F61u;
            constexpr uint32_t kWalkerVelocityScaleKeyHash = 0xEB72A482u; // "walkervelocityscale"
            constexpr size_t kClassBuildingScaleOffset = 0xC0;
            constexpr size_t kWaveClassOffset = 0xC;
            constexpr size_t kGameObjectInterfaceOffset = 0x18;
            constexpr size_t kClassSignatureOffset = 0x14;
            constexpr uint32_t kWalkerSignature = 0x57414C4Bu; // 'WALK'

            // Offsets of the E8 call inside each guarded row window.
            constexpr uint32_t kCtorCallOffset = 0x27;
            constexpr uint32_t kSimulateCallOffset = 0x25;

            using FnParameterDbGetFloat = bool(__thiscall*)(void*, uint32_t, uint32_t, float*, float);
            using FnAddVelocity = void(__thiscall*)(void*, const float*);
            using FnGetObjectClass = void*(__thiscall*)(void*);

            FnParameterDbGetFloat g_GetFloat = nullptr;
            FnAddVelocity g_AddVelocity = nullptr;
            bool g_Initialized = false;

            // Class pointer -> scale, only for classes whose ODF sets a value
            // other than 1.0. Every SeismicWaveClass build rewrites its own
            // entry, so a reused class address never keeps a stale value.
            SRWLOCK g_ScaleLock = SRWLOCK_INIT;
            std::unordered_map<const void*, float> g_ClassScales;
            volatile long g_ClassScaleCount = 0;
            // First few scaled walker kicks per session, as evidence the hook fires.
            constexpr long kWalkerKickLogLimit = 8;
            volatile long g_WalkerKickLogCount = 0;

            void SetClassScale(const void* cls, float scale)
            {
                AcquireSRWLockExclusive(&g_ScaleLock);
                if (scale == 1.0f)
                    g_ClassScales.erase(cls);
                else
                    g_ClassScales[cls] = scale;
                InterlockedExchange(&g_ClassScaleCount, static_cast<long>(g_ClassScales.size()));
                ReleaseSRWLockExclusive(&g_ScaleLock);
            }

            bool TryGetClassScale(const void* cls, float& scale)
            {
                AcquireSRWLockShared(&g_ScaleLock);
                const auto it = g_ClassScales.find(cls);
                const bool found = it != g_ClassScales.end();
                if (found)
                    scale = it->second;
                ReleaseSRWLockShared(&g_ScaleLock);
                return found;
            }

            bool IsWalker(void* target)
            {
                __try
                {
                    void* iface = static_cast<uint8_t*>(target) + kGameObjectInterfaceOffset;
                    void** vtable = *reinterpret_cast<void***>(iface);
                    if (!vtable || !vtable[0])
                        return false;
                    const void* cls = reinterpret_cast<FnGetObjectClass>(vtable[0])(iface);
                    return cls &&
                        *reinterpret_cast<const uint32_t*>(
                            static_cast<const uint8_t*>(cls) + kClassSignatureOffset) == kWalkerSignature;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // Replaces the buildingScale GetFloat call in the class ctor.
            bool __fastcall SeismicClassGetFloatHook(void* parameterDb, void* /*edx*/,
                                                     uint32_t sectionHash, uint32_t keyHash,
                                                     float* outValue, float defaultValue)
            {
                const bool found = g_GetFloat(parameterDb, sectionHash, keyHash, outValue, defaultValue);
                if (sectionHash == kSeismicWaveClassSectionHash && keyHash == kBuildingScaleKeyHash &&
                    parameterDb && outValue)
                {
                    float scale = 1.0f;
                    const bool explicitKey = g_GetFloat(parameterDb, kSeismicWaveClassSectionHash,
                                                        kWalkerVelocityScaleKeyHash, &scale, 1.0f);
                    if (!std::isfinite(scale))
                        scale = 1.0f; // reject nan/inf so no NaN reaches physics
                    // Not inherited from a parent ODF: an absent key means 1.0.
                    const void* cls = reinterpret_cast<uint8_t*>(outValue) - kClassBuildingScaleOffset;
                    SetClassScale(cls, scale);
                    if (explicitKey)
                        LogShimA(LogLevel::Info, "SEISMIC",
                                 "SeismicWaveClass %p walkerVelocityScale=%.3f", cls, scale);
                }
                return found;
            }

            void __fastcall SeismicAddVelocityHook(void* target, void* wave, const float* velocity)
            {
                if (g_ClassScaleCount > 0 && wave && velocity && target)
                {
                    const void* cls = nullptr;
                    __try
                    {
                        cls = *reinterpret_cast<void* const*>(static_cast<uint8_t*>(wave) + kWaveClassOffset);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        cls = nullptr;
                    }
                    float scale = 1.0f;
                    if (cls && TryGetClassScale(cls, scale) && IsWalker(target))
                    {
                        const float scaled[3] = { velocity[0] * scale, velocity[1] * scale,
                                                  velocity[2] * scale };
                        // Zero kicks (wave ramp-up) are skipped so the budget
                        // lands on real ones.
                        const float len = std::sqrt(velocity[0] * velocity[0] +
                            velocity[1] * velocity[1] + velocity[2] * velocity[2]);
                        if (len > 0.01f && g_WalkerKickLogCount < kWalkerKickLogLimit &&
                            InterlockedIncrement(&g_WalkerKickLogCount) <= kWalkerKickLogLimit)
                        {
                            LogShimA(LogLevel::Info, "SEISMIC",
                                     "walker kick y=%.2f scaled=%.2f len=%.2f scaledLen=%.2f (scale %.3f)",
                                     velocity[1], scaled[1], len, len * std::fabs(scale), scale);
                        }
                        g_AddVelocity(target, scaled);
                        return;
                    }
                }
                g_AddVelocity(target, velocity);
            }

#if defined(_M_IX86)
            // Entered by the redirected call: ecx = target, [esp+4] = velocity,
            // ebp = Simulate's frame. Passing the wave this in edx makes the
            // stack match __fastcall(target, wave, velocity), which pops 4
            // bytes like the stock __thiscall AddVelocity.
            __declspec(naked) void SeismicAddVelocityThunk()
            {
                __asm
                {
                    mov edx, dword ptr [ebp - 0x254]
                    jmp SeismicAddVelocityHook
                }
            }
#endif

            uint32_t Rel32Target(uint32_t callSite)
            {
                int32_t rel = 0;
                if (!HookEngine::ReadMemory(callSite + 1, &rel, sizeof(rel)))
                    return 0;
                return callSite + 5 + static_cast<uint32_t>(rel);
            }

            bool RedirectCall(uint32_t callSite, void* hook)
            {
                uint8_t patch[5] = { 0xE8, 0, 0, 0, 0 };
                const int64_t displacement = static_cast<int64_t>(reinterpret_cast<uintptr_t>(hook)) -
                    static_cast<int64_t>(callSite + 5);
                if (displacement < std::numeric_limits<int32_t>::min() ||
                    displacement > std::numeric_limits<int32_t>::max())
                    return false;
                const int32_t rel32 = static_cast<int32_t>(displacement);
                std::memcpy(patch + 1, &rel32, sizeof(rel32));
                return HookEngine::WriteMemory(callSite, patch, sizeof(patch));
            }
        }

        void InitializeSeismicWalkerVelocityScale()
        {
#if defined(_M_IX86)
            if (g_Initialized)
                return;
            g_Initialized = true;

            uint32_t ctorRow = 0;
            uint32_t simulateRow = 0;
            const HookEngine::EngineRow rows[] = {
                { "SeismicWaveClassBuildingScaleRead", &ctorRow },
                { "SeismicWaveSimulateAddVelocityCall", &simulateRow },
            };
            if (!HookEngine::BindEngineRows("SeismicWave walkerVelocityScale", rows))
                return;

            // The guarded windows end in these E8 calls; their rel32 targets
            // are part of the guard, so the decoded targets are the stock ones.
            const uint32_t ctorCall = ctorRow + kCtorCallOffset;
            const uint32_t simulateCall = simulateRow + kSimulateCallOffset;
            const uint32_t getFloat = Rel32Target(ctorCall);
            const uint32_t addVelocity = Rel32Target(simulateCall);
            if (!getFloat || !addVelocity)
            {
                Log(L"[SEISMIC] walkerVelocityScale call targets unreadable; standing down\n");
                return;
            }
            g_GetFloat = reinterpret_cast<FnParameterDbGetFloat>(getFloat);
            g_AddVelocity = reinterpret_cast<FnAddVelocity>(addVelocity);

            if (!RedirectCall(simulateCall, reinterpret_cast<void*>(&SeismicAddVelocityThunk)))
            {
                Log(L"[SEISMIC] Failed patching Simulate AddVelocity call at 0x%08X\n", simulateCall);
                return;
            }
            if (!RedirectCall(ctorCall, reinterpret_cast<void*>(&SeismicClassGetFloatHook)))
            {
                // The Simulate thunk is a pass-through while no class has a
                // scale, so leaving it in place keeps stock behaviour.
                Log(L"[SEISMIC] Failed patching SeismicWaveClass GetFloat call at 0x%08X\n", ctorCall);
                return;
            }
            Log(L"[SEISMIC] walkerVelocityScale installed (ctor 0x%08X, simulate 0x%08X)\n",
                ctorCall, simulateCall);
#endif
        }
    }
}
