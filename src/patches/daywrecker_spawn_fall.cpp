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
// Rules: include/daywrecker_spawn_policy.h. Evidence and live checklist:
// Docs/DAYWRECKER_FALL_ON_SPAWN.md.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
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

            using FnCtor = void*(__thiscall*)(void* self, uint32_t a, uint32_t b);
            using FnOpenScope = void*(__thiscall*)(void*, const char*);
            using FnRawGet = const char*(__thiscall*)(void*, uint32_t, uint32_t);
            using FnPopScope = void(__thiscall*)(void*);

            bool g_Installed = false;
            uint32_t g_CtorAddr = 0;
            FnOpenScope g_OpenScope = nullptr;
            FnRawGet g_RawGet = nullptr;
            FnPopScope g_PopScope = nullptr;

            // Game thread only (object construction).
            Policy::ClassCache<32> g_Cache;
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

            // Reads [DayWreckerClass] fallOnSpawn from the class's ODF.
            // False when the scope cannot be opened or the key is absent.
            bool ReadKey(const char* odfFile)
            {
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
                char raw[32] = {};
                __try
                {
                    const char* value = g_RawGet(&scope, TrackedPhysics::OdfHash(Policy::kSection),
                                                 TrackedPhysics::OdfHash(Policy::kKey));
                    for (size_t i = 0; value && i + 1 < sizeof(raw) && value[i]; ++i)
                        raw[i] = value[i];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    raw[0] = 0;
                }
                __try
                {
                    g_PopScope(&scope);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                return Policy::ParseKey(raw);
            }

            bool ClassWantsFall(void* cls)
            {
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
                bool on = false;
                if (g_Cache.Find(key, on))
                    return on;

                char name[9] = {};
                std::memcpy(name, &key.nameLo, sizeof(key.nameLo));
                std::memcpy(name + 4, &key.nameHi, sizeof(key.nameHi));
                char odfFile[16] = {};
                std::snprintf(odfFile, sizeof(odfFile), "%.8s.odf", name);
                on = ReadKey(odfFile);
                g_Cache.Put(key, on);
                if (on)
                    LogBudgeted(L"[DAYWRECKER] %hs: fallOnSpawn on\n", name);
                return on;
            }

            // Runs after the stock constructor, on the object it returned.
            void ArmIfWanted(void* obj)
            {
                if (!obj || !IsSinglePlayerSession())
                    return;
                void* cls = nullptr;
                uint32_t* flags = nullptr;
                __try
                {
                    const uint8_t* bytes = static_cast<const uint8_t*>(obj);
                    // Identity: the constructor just installed DayWrecker's vtable.
                    const uintptr_t vtable = *reinterpret_cast<const uintptr_t*>(bytes);
                    if (!VtableTypeNameMatches(vtable, ".?AVDayWrecker@@"))
                        return;
                    cls = *reinterpret_cast<void* const*>(bytes + kGameObjectClassOffset);
                    uint8_t* state = *reinterpret_cast<uint8_t* const*>(bytes + kPowerUpStateOffset);
                    if (state)
                        flags = reinterpret_cast<uint32_t*>(state + kPowerUpFlagsOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return;
                }
                if (!cls || !flags)
                    return;
                const bool keyOn = ClassWantsFall(cls);
                __try
                {
                    const uint32_t before = *flags;
                    if (!Policy::ShouldArm(true, keyOn, before))
                        return;
                    *flags = Policy::ArmedFlags(before);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    LogBudgeted(L"[DAYWRECKER] could not set the airborne flag on %p\n", obj);
                }
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

        void InstallDayWreckerSpawnFallIfPossible()
        {
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
            g_OpenScope = reinterpret_cast<FnOpenScope>(HookEngine::ResolveNamedAddress("ParameterDB::OpenScope"));
            g_RawGet = reinterpret_cast<FnRawGet>(HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet"));
            g_PopScope = reinterpret_cast<FnPopScope>(HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope"));
            if (!g_OpenScope || !g_RawGet || !g_PopScope)
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
