// mp_daywrecker_armory_collision.cpp -- keep a receiver's copy of an
// Armory-launched Daywrecker from detonating at the Armory.
//
// Every peer runs the Armory's ObjectLobber (0x00582190) only for its own
// launches; the other peers get the bomb as a network create. That path
// (0x004B7F20 marks it remote) builds the copy with vehicle flags 0 at
// *(bomb+0x228)+0x114; the first state through the PowerUp unpack
// (0x005AACF0, __thiscall on the Distributed interface at bomb+0x18,
// (packet, int* remaining), ret 8) sets flags 4|8 (in flight, launched).
// DayWrecker::Simulate (0x004B0460, __thiscall(this, float), ret 4)
// detonates whenever bit 4 is clear.
//
// 1. A remote copy can run one Simulate between its create and its first
//    state. With flags 0 it detonates at its spawn point, inside the Armory,
//    on that peer only, and later state rebuilds it. The Simulate entry of the
//    DayWrecker vtable is replaced: a remote copy (mode byte 2) with no state
//    applied yet runs PowerUp::Simulate (0x005A7D70) instead, which is what
//    the in-flight path does. The unpack hook records which copies have state.
// 2. A copy that was rebuilt anyway has the flags but no owner (+0x224 = 0),
//    so DayWrecker::RegCollision (0x004B0610, __thiscall(this, _OBJ76*
//    other, CLSN_INFO*, CLSN_INFO*), ret 0xC, bool in AL) no longer ignores
//    the Armory it is still inside. The hook returns false (collision ignored,
//    flags kept) for an in-flight bomb with owner 0 whose collider is an
//    Armory ('ARMR').

#include "mp_daywrecker_armory_collision_install.h"

#include "bzr_options_ui.h"
#include "com_vtable_patch.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace DaywreckerArmory
    {
        namespace
        {
            constexpr const char* kComponent = "DWARMORY";

            constexpr uintptr_t kOwnerHandleOffset = 0x224;
            constexpr uintptr_t kVehiclePtrOffset = 0x228;
            constexpr uintptr_t kFlagsOffset = 0x114;
            constexpr uint32_t kFlagsInFlightLaunched = 0x4 | 0x8;
            constexpr uint32_t kArmorySignature = 0x41524D52; // 'ARMR'
            constexpr uintptr_t kDistributedOffset = 0x18;
            constexpr uintptr_t kNetIdOffset = 0x64;
            constexpr uintptr_t kNetModeOffset = 0x68;
            constexpr uint8_t kNetModeRemote = 2;
            constexpr size_t kSimulateSlot = 15;
            constexpr size_t kStateSeenSlots = 64;
            constexpr long kLogBudget = 8;

            using FnRegCollision = bool(__thiscall*)(void* self, void* other, void* c1, void* c2);
            using FnUnpackState = void(__thiscall*)(void* dist, void* packet, int* remaining);
            using FnFromObj76 = void*(__cdecl*)(void* obj76);
            using FnSimulate = void(__thiscall*)(void* self, float dt);

            struct StateSeen
            {
                void* bomb;
                uint32_t id;
            };

            constexpr uint8_t kStolen[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x2C };
            constexpr uint8_t kUnpackStolen[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x44 };

            std::atomic<bool> g_Done{ false };
            InlineDetour32 g_Detour = {};
            void* volatile g_Original = nullptr;
            InlineDetour32 g_UnpackDetour = {};
            void* volatile g_UnpackOriginal = nullptr;
            uint32_t g_DayWreckerVtable = 0;
            FnFromObj76 g_FromObj76 = nullptr;
            void* g_SimulateOriginal = nullptr;
            FnSimulate g_PowerUpSimulate = nullptr;
            StateSeen g_StateSeen[kStateSeenSlots] = {};
            size_t g_StateNext = 0;
            volatile long g_LogLeft = kLogBudget;
            volatile long g_SimLogLeft = kLogBudget;

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_MP_DAYWRECKER_ARMORY_COLLISION",
                      "BZR_DISABLE_MP_DAYWRECKER_ARMORY_COLLISION" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            // Class signature as in unit_behavior_fixes.cpp: interface at
            // obj+0x18, vtable[0] returns the class, signature at class+0x14.
            // Caller holds the SEH frame.
            bool ClassSignature(void* object, uint32_t& sig)
            {
                using FnGetClass = void*(__thiscall*)(void* iface);
                void* iface = reinterpret_cast<uint8_t*>(object) + 0x18;
                void** vtable = *reinterpret_cast<void***>(iface);
                if (!vtable || !vtable[0])
                    return false;
                void* cls = reinterpret_cast<FnGetClass>(vtable[0])(iface);
                if (!cls)
                    return false;
                sig = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(cls) + 0x14);
                return true;
            }

            bool ShouldIgnore(void* self, void* other, int& owner)
            {
                __try
                {
                    uint8_t* bomb = static_cast<uint8_t*>(self);
                    owner = *reinterpret_cast<int*>(bomb + kOwnerHandleOffset);
                    if (owner != 0 || !other)
                        return false;
                    uint8_t* vehicle = *reinterpret_cast<uint8_t**>(bomb + kVehiclePtrOffset);
                    if (!vehicle)
                        return false;
                    const uint32_t flags = *reinterpret_cast<uint32_t*>(vehicle + kFlagsOffset);
                    if ((flags & kFlagsInFlightLaunched) != kFlagsInFlightLaunched)
                        return false;
                    void* go = g_FromObj76(other);
                    uint32_t sig = 0;
                    return go && ClassSignature(go, sig) && sig == kArmorySignature;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool __fastcall RegCollisionHook(void* self, void* /*edx*/, void* other, void* c1, void* c2)
            {
                int owner = 0;
                if (ShouldIgnore(self, other, owner))
                {
                    if (InterlockedDecrement(&g_LogLeft) >= 0)
                        LogShimA(LogLevel::Info, kComponent,
                                 "ignored Armory collision: bomb=0x%08X owner=0x%08X collider=0x%08X",
                                 static_cast<uint32_t>(reinterpret_cast<uintptr_t>(self)),
                                 static_cast<uint32_t>(owner),
                                 static_cast<uint32_t>(reinterpret_cast<uintptr_t>(other)));
                    return false;
                }
                return reinterpret_cast<FnRegCollision>(g_Original)(self, other, c1, c2);
            }

            bool IsDayWrecker(void* complete)
            {
                __try
                {
                    return *reinterpret_cast<uint32_t*>(complete) == g_DayWreckerVtable;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // Network identity on the Distributed interface: id at +0x64, mode
            // byte at +0x68 (2 = remote, set by 0x004B7F20).
            bool ReadIdentity(void* complete, uint32_t& id, uint8_t& mode)
            {
                __try
                {
                    const uint8_t* dist = static_cast<uint8_t*>(complete) + kDistributedOffset;
                    id = *reinterpret_cast<const uint32_t*>(dist + kNetIdOffset);
                    mode = dist[kNetModeOffset];
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // Bombs that have had state applied, keyed by pointer and network id
            // so a reused allocation starts over. The sim and the network unpack
            // both run on the game thread.
            bool HasState(void* complete, uint32_t id)
            {
                for (const StateSeen& seen : g_StateSeen)
                    if (seen.bomb == complete && seen.id == id)
                        return true;
                return false;
            }

            void __fastcall UnpackStateHook(void* dist, void* /*edx*/, void* packet, int* remaining)
            {
                reinterpret_cast<FnUnpackState>(g_UnpackOriginal)(dist, packet, remaining);
                void* complete = static_cast<uint8_t*>(dist) - kDistributedOffset;
                uint32_t id = 0;
                uint8_t mode = 0;
                if (!IsDayWrecker(complete) || !ReadIdentity(complete, id, mode) || HasState(complete, id))
                    return;
                g_StateSeen[g_StateNext] = { complete, id };
                g_StateNext = (g_StateNext + 1) % kStateSeenSlots;
            }

            // A remote copy built from a create message starts with flags 0 and
            // can get a Simulate before its first state arrives; with bit 4 clear
            // that Simulate detonates it at its spawn point. Until state arrives
            // it runs the PowerUp base Simulate, as an in-flight bomb does.
            void __fastcall SimulateHook(void* self, void* /*edx*/, float dt)
            {
                uint32_t id = 0;
                uint8_t mode = 0;
                if (ReadIdentity(self, id, mode) && mode == kNetModeRemote && !HasState(self, id))
                {
                    if (InterlockedDecrement(&g_SimLogLeft) >= 0)
                        LogShimA(LogLevel::Info, kComponent,
                                 "held remote bomb=0x%08X id=0x%08X until its first state",
                                 static_cast<uint32_t>(reinterpret_cast<uintptr_t>(self)), id);
                    g_PowerUpSimulate(self, dt);
                    return;
                }
                reinterpret_cast<FnSimulate>(g_SimulateOriginal)(self, dt);
            }

            bool DoInstall()
            {
                const uint32_t fromObj76 = HookEngine::ResolveNamedAddress("GameObject::FromObj76");
                uint32_t regAddr = 0;
                uint32_t unpackAddr = 0;
                uint32_t powerUpSimAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "DayWreckerRegCollision", &regAddr },
                    { "PowerUpUnpackState", &unpackAddr },
                    { "PowerUpSimulate", &powerUpSimAddr },
                    { "DayWreckerVtable", &g_DayWreckerVtable },
                };
                if (!fromObj76 || !HookEngine::BindEngineRows("DaywreckerArmoryCollision", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; fix not installed");
                    return false;
                }
                g_FromObj76 = reinterpret_cast<FnFromObj76>(fromObj76);
                g_PowerUpSimulate = reinterpret_cast<FnSimulate>(powerUpSimAddr);
                if (!InstallInlineDetour32(g_Detour, regAddr, reinterpret_cast<void*>(RegCollisionHook),
                                           sizeof(kStolen), kStolen, sizeof(kStolen), &g_Original))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "DayWrecker::RegCollision at 0x%08X failed its byte guard; fix not installed", regAddr);
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: DayWrecker::RegCollision 0x%08X", regAddr);
                if (!InstallInlineDetour32(g_UnpackDetour, unpackAddr, reinterpret_cast<void*>(UnpackStateHook),
                                           sizeof(kUnpackStolen), kUnpackStolen, sizeof(kUnpackStolen), &g_UnpackOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "PowerUp state unpack at 0x%08X failed its byte guard; detonation hold not installed", unpackAddr);
                    return false;
                }
                // Simulate is replaced in the class vtable rather than detoured
                // inline, so it chains with the MPAUTH trace's detour on 0x004B0460.
                void* vtableHolder = &g_DayWreckerVtable;
                const ComVtablePatch::Result patched = ComVtablePatch::PatchEntry(
                    vtableHolder, kSimulateSlot, reinterpret_cast<void*>(&SimulateHook), g_SimulateOriginal,
                    ComVtablePatch::OnForeignWrapper::Refuse);
                if (!ComVtablePatch::Succeeded(patched) || !g_SimulateOriginal)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "DayWrecker vtable 0x%08X Simulate slot not patched (%d); detonation hold not installed",
                             g_DayWreckerVtable, static_cast<int>(patched));
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: PowerUp state unpack 0x%08X, Simulate slot (was 0x%08X)",
                         unpackAddr, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_SimulateOriginal)));
                return true;
            }
        }

        void InstallDaywreckerArmoryCollisionIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] DaywreckerArmoryCollision = 0)");
                return;
            }
            DoInstall();
        }
    }
}
