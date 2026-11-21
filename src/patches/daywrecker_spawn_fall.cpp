// daywrecker_spawn_fall.cpp
// BZR Open Shim - Daywrecker fall-on-spawn: the ODF key
// [DayWreckerClass] fallOnSpawn = 1 makes a Daywrecker that is created
// outside the Armory (Lua BuildObject, a map object) fall under gravity and
// detonate where it lands, instead of exploding the tick it is made.
//
// Why it explodes in stock (GOG 2.2.301): DayWrecker::Simulate (0x004B0460)
// detonates on its first tick unless the PowerUp state flags
// ([obj+0x228]+0x114) have bit 0x4 (airborne). Only the Armory's
// ObjectLobber (0x00582190) sets it, |= 0xC, after FUN_004E1190 builds the
// object and before its first Simulate. With 0x4 set, PowerUp::Simulate
// (0x005A7D70) runs the airborne step and clears 0x4 when the object reaches
// the terrain; DayWrecker::Simulate then detonates, as an Armory drop does.
//
// Hook: DayWreckerClass's object factory (0x004B0D40) has the only call to
// the DayWrecker constructor (0x004B0420, thiscall this, a, b; returns this),
// at 0x004B0D90. That call is redirected (DayWreckerBuildCtorCall row); after
// the stock constructor returns, a Daywrecker whose class ODF sets the key
// gets bit 0x4, in single player only. Every creation path passes here, so
// the key also covers map objects; the Armory path ORs 0xC afterwards, so an
// Armory drop ends exactly as stock.
//
// Multiplayer: a remote replica is built by the same constructor from the
// network create path, so arming there could make a replica fall on its own;
// the key stands down in a network game (DayWreckerSpawnPolicy::ShouldArm).
//
// [DayWreckerClass] dropRate = k (0.25..3, default 1) fast-forwards an
// airborne Daywrecker: the DayWrecker vtable's Simulate slot (+0x3C, the slot
// the Armory's lobber calls for the launch tick) is replaced by a wrapper
// that hands the stock Simulate dt * k while the airborne bit is set. Same
// arc and landing point, flight time / k. Single player only.
//
// Rules: include/daywrecker_spawn_policy.h. Evidence and live checklists:
// Docs/DAYWRECKER_FALL_ON_SPAWN.md, Docs/DAYWRECKER_DROP_RATE.md.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "com_vtable_patch.h"
#include "daywrecker_spawn_policy.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"
#include "tracked_vehicle_physics.h"

#include <windows.h>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace Policy = DayWreckerSpawnPolicy;

            // E8 of the constructor call, from the DayWreckerBuildCtorCall row.
            constexpr uintptr_t kCtorCallOffset = 0x0B;
            // PowerUp state block pointer (PowerUp ctor 0x005A79F0 stores it at
            // +0x228; DayWrecker::Simulate and the lobber read +0x114 off it).
            constexpr size_t kPowerUpStateOffset = 0x228;
            constexpr size_t kPowerUpFlagsOffset = 0x114;
            // GameObjectClass packed 8-character ODF name (FUN_004E1190 formats
            // it with "%.8s"; tracked_vehicle_class.cpp reads the same field).
            constexpr size_t kClassPackedNameOffset = 0x30;

            // DayWrecker vtable slot 15: Simulate(float dt).
            constexpr size_t kSimulateSlot = 15;

            using FnCtor = void*(__thiscall*)(void* self, uint32_t a, uint32_t b);
            using FnSimulate = void(__thiscall*)(void* self, float dt);
            using FnOpenScope = void*(__thiscall*)(void*, const char*);
            using FnRawGet = const char*(__thiscall*)(void*, uint32_t, uint32_t);
            using FnPopScope = void(__thiscall*)(void*);

            bool g_Installed = false;
            bool g_RateInstalled = false;
            bool g_ScopeReady = false;
            uint32_t g_CtorAddr = 0;
            uint32_t g_DayWreckerVtable = 0;
            // What the Simulate slot held when the wrapper went in: the stock
            // DayWrecker::Simulate, or another OpenShim wrapper on the same
            // slot (the MP Armory-collision hold); the wrapper forwards to it.
            void* g_SimulateNext = nullptr;
            FnOpenScope g_OpenScope = nullptr;
            FnRawGet g_RawGet = nullptr;
            FnPopScope g_PopScope = nullptr;

            // Game thread only (object construction).
            Policy::ClassCache<32, Policy::ClassSettings> g_Cache;
            volatile long g_LogBudget = 24;

            void LogBudgeted(const wchar_t* fmt, ...)
            {
                if (InterlockedDecrement(&g_LogBudget) < 0)
                    return;
                wchar_t buffer[256];
                va_list args;
                va_start(args, fmt);
                _vsnwprintf_s(buffer, _TRUNCATE, fmt, args);
                va_end(args);
                Log(L"%ls", buffer);
            }

            // Copies one [DayWreckerClass] value out of an open scope.
            // Empty when the key is absent or the read faults.
            void RawValue(void** scope, const char* key, char (&raw)[32])
            {
                raw[0] = 0;
                __try
                {
                    const char* value = g_RawGet(scope, TrackedPhysics::OdfHash(Policy::kSection),
                                                 TrackedPhysics::OdfHash(key));
                    size_t i = 0;
                    for (; value && i + 1 < sizeof(raw) && value[i]; ++i)
                        raw[i] = value[i];
                    raw[i] = 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    raw[0] = 0;
                }
            }

            // Reads the class's [DayWreckerClass] keys. Stock settings when
            // the scope cannot be opened.
            Policy::ClassSettings ReadSettings(const char* odfFile)
            {
                Policy::ClassSettings settings;
                void* scope = nullptr;
                __try
                {
                    g_OpenScope(&scope, odfFile);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return settings;
                }
                if (!scope)
                    return settings;
                char raw[32] = {};
                RawValue(&scope, Policy::kKey, raw);
                settings.fallOnSpawn = Policy::ParseKey(raw);
                RawValue(&scope, Policy::kDropRateKey, raw);
                settings.dropRate = Policy::ParseDropRate(raw);
                __try
                {
                    g_PopScope(&scope);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                return settings;
            }

            // False when the class cannot be read; settings stay stock.
            bool ClassSettingsFor(void* cls, Policy::ClassSettings& out)
            {
                out = Policy::ClassSettings{};
                Policy::ClassKey key;
                key.cls = cls;
                __try
                {
                    const uint8_t* bytes = static_cast<const uint8_t*>(cls);
                    std::memcpy(&key.nameLo, bytes + kClassPackedNameOffset, sizeof(key.nameLo));
                    std::memcpy(&key.nameHi, bytes + kClassPackedNameOffset + 4, sizeof(key.nameHi));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                if (g_Cache.Find(key, out))
                    return true;

                char name[9] = {};
                std::memcpy(name, &key.nameLo, sizeof(key.nameLo));
                std::memcpy(name + 4, &key.nameHi, sizeof(key.nameHi));
                char odfFile[16] = {};
                std::snprintf(odfFile, sizeof(odfFile), "%.8s.odf", name);
                out = ReadSettings(odfFile);
                g_Cache.Put(key, out);
                if (out.fallOnSpawn)
                    LogBudgeted(L"[DAYWRECKER] %hs: fallOnSpawn on\n", name);
                if (out.dropRate != Policy::kDropRateStock)
                    LogBudgeted(L"[DAYWRECKER] %hs: dropRate %.2f\n", name, static_cast<double>(out.dropRate));
                return true;
            }

            // Reads the class pointer and the PowerUp flags address of a
            // Daywrecker. False when obj is not one or the read faults.
            bool ReadDayWrecker(void* obj, void*& cls, uint32_t*& flags)
            {
                cls = nullptr;
                flags = nullptr;
                __try
                {
                    const uint8_t* bytes = static_cast<const uint8_t*>(obj);
                    const uintptr_t vtable = *reinterpret_cast<const uintptr_t*>(bytes);
                    if (!VtableTypeNameMatches(vtable, ".?AVDayWrecker@@"))
                        return false;
                    cls = *reinterpret_cast<void* const*>(bytes + kGameObjectClassOffset);
                    uint8_t* state = *reinterpret_cast<uint8_t* const*>(bytes + kPowerUpStateOffset);
                    if (state)
                        flags = reinterpret_cast<uint32_t*>(state + kPowerUpFlagsOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return cls != nullptr && flags != nullptr;
            }

            // Runs after the stock constructor, on the object it returned.
            void ArmIfWanted(void* obj)
            {
                if (!obj || !IsSinglePlayerSession())
                    return;
                void* cls = nullptr;
                uint32_t* flags = nullptr;
                if (!ReadDayWrecker(obj, cls, flags))
                    return;
                Policy::ClassSettings settings;
                if (!ClassSettingsFor(cls, settings))
                    return;
                __try
                {
                    const uint32_t before = *flags;
                    if (!Policy::ShouldArm(true, settings.fallOnSpawn, before))
                        return;
                    *flags = Policy::ArmedFlags(before);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    LogBudgeted(L"[DAYWRECKER] could not set the airborne flag on %p\n", obj);
                }
            }

            // The dt the stock Simulate gets: dt * dropRate while airborne.
            float StepFor(void* obj, float dt)
            {
                if (!obj || !IsSinglePlayerSession())
                    return dt;
                void* cls = nullptr;
                uint32_t* flags = nullptr;
                if (!ReadDayWrecker(obj, cls, flags))
                    return dt;
                Policy::ClassSettings settings;
                if (!ClassSettingsFor(cls, settings) || settings.dropRate == Policy::kDropRateStock)
                    return dt;
                uint32_t current = 0;
                __try
                {
                    current = *flags;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return dt;
                }
                return Policy::ScaledStep(true, settings.dropRate, current, dt);
            }

            // DayWrecker vtable slot 15 (thiscall this, float dt; RET 4).
            // __fastcall gives the same contract: ecx = this, edx unused, the
            // float popped by the callee. Only reads happen before the stock
            // call: a grounded tick detonates, and nothing touches obj after.
            void __fastcall SimulateHook(void* self, void* /*edx*/, float dt)
            {
                const float step = StepFor(self, dt);
                reinterpret_cast<FnSimulate>(g_SimulateNext)(self, step);
            }

            // In place of `call DayWrecker::DayWrecker` (thiscall, two stack
            // arguments, callee cleans; returns this). __fastcall gives the
            // same contract: ecx = this, edx unused, the two arguments popped.
            void* __fastcall CtorHook(void* self, void* /*edx*/, uint32_t a, uint32_t b)
            {
                void* const obj = reinterpret_cast<FnCtor>(static_cast<uintptr_t>(g_CtorAddr))(self, a, b);
                ArmIfWanted(obj);
                return obj;
            }
        }

        namespace
        {
            bool InThisModule(const void* address)
            {
                HMODULE owner = nullptr;
                HMODULE self = nullptr;
                const DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
                if (!address ||
                    !GetModuleHandleExW(flags, static_cast<LPCWSTR>(address), &owner) ||
                    !GetModuleHandleExW(flags, reinterpret_cast<LPCWSTR>(&InThisModule), &self))
                    return false;
                return owner == self;
            }

            bool ResolveScope()
            {
                if (g_ScopeReady)
                    return true;
                g_OpenScope = reinterpret_cast<FnOpenScope>(HookEngine::ResolveNamedAddress("ParameterDB::OpenScope"));
                g_RawGet = reinterpret_cast<FnRawGet>(HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet"));
                g_PopScope = reinterpret_cast<FnPopScope>(HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope"));
                g_ScopeReady = g_OpenScope && g_RawGet && g_PopScope;
                return g_ScopeReady;
            }

            void InstallDropRate()
            {
                if (g_RateInstalled)
                    return;
                if (EnvFlagEnabled("OPENSHIM_DISABLE_DAYWRECKER_DROP_RATE"))
                {
                    Log(L"[DAYWRECKER] dropRate disabled by environment\n");
                    return;
                }
                uint32_t simulateAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "DayWreckerVtable", &g_DayWreckerVtable },
                    { "DayWreckerSimulate", &simulateAddr },
                };
                if (!HookEngine::BindEngineRows("Daywrecker drop rate", rows))
                    return;
                if (!ResolveScope())
                {
                    Log(L"[DAYWRECKER] ODF scope resolves missing; dropRate not installed\n");
                    return;
                }
                if (!VtableTypeNameMatches(g_DayWreckerVtable, ".?AVDayWrecker@@"))
                {
                    Log(L"[DAYWRECKER] vtable 0x%08X is not DayWrecker's; dropRate not installed\n",
                        g_DayWreckerVtable);
                    return;
                }
                const uintptr_t slot = g_DayWreckerVtable + kSimulateSlot * sizeof(void*);
                void* current = nullptr;
                __try
                {
                    current = *reinterpret_cast<void**>(slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    current = nullptr;
                }
                // The slot may already hold another OpenShim wrapper (the MP
                // Armory-collision hold patches the same slot and forwards to
                // what it found); chain onto that. Anything else fails closed.
                if (current != reinterpret_cast<void*>(static_cast<uintptr_t>(simulateAddr)) &&
                    !InThisModule(current))
                {
                    Log(L"[DAYWRECKER] Simulate slot 0x%08X holds 0x%08X, neither 0x%08X nor an OpenShim "
                        L"wrapper; dropRate not installed\n",
                        static_cast<uint32_t>(slot), static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                        simulateAddr);
                    return;
                }
                void* vtableHolder = &g_DayWreckerVtable;
                const ComVtablePatch::Result patched = ComVtablePatch::PatchEntry(
                    vtableHolder, kSimulateSlot, reinterpret_cast<void*>(&SimulateHook), g_SimulateNext,
                    ComVtablePatch::OnForeignWrapper::Refuse);
                if (!ComVtablePatch::Succeeded(patched) || !g_SimulateNext)
                {
                    Log(L"[DAYWRECKER] Simulate slot 0x%08X not patched (%d); dropRate not installed\n",
                        static_cast<uint32_t>(slot), static_cast<int>(patched));
                    return;
                }
                g_RateInstalled = true;
                Log(L"[DAYWRECKER] dropRate installed ([DayWreckerClass] dropRate = k fast-forwards an airborne "
                    L"Daywrecker by k; single player only)\n");
            }
        }

        void InstallDayWreckerSpawnFallIfPossible()
        {
            // Independent hooks: either can fail closed without the other.
            InstallDropRate();
            if (g_Installed)
                return;
            if (EnvFlagEnabled("OPENSHIM_DISABLE_DAYWRECKER_FALL_ON_SPAWN"))
            {
                Log(L"[DAYWRECKER] fallOnSpawn disabled by environment\n");
                return;
            }
            uint32_t callRow = 0;
            const HookEngine::EngineRow rows[] = {
                { "DayWreckerBuildCtorCall", &callRow },
                { "DayWreckerCtor", &g_CtorAddr },
            };
            if (!HookEngine::BindEngineRows("Daywrecker fall-on-spawn", rows))
                return;
            if (!ResolveScope())
            {
                Log(L"[DAYWRECKER] ODF scope resolves missing; fallOnSpawn not installed\n");
                return;
            }
            if (!RedirectCallTarget(callRow + kCtorCallOffset, g_CtorAddr, reinterpret_cast<uintptr_t>(&CtorHook)))
            {
                Log(L"[DAYWRECKER] constructor call at 0x%08X not redirected; fallOnSpawn not installed\n",
                    callRow + static_cast<uint32_t>(kCtorCallOffset));
                return;
            }
            g_Installed = true;
            Log(L"[DAYWRECKER] fallOnSpawn installed ([DayWreckerClass] fallOnSpawn = 1 arms a non-Armory "
                L"Daywrecker to fall; single player only)\n");
        }
    }
}
