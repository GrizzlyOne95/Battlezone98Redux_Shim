// objective_cap_guard.cpp -- the objective list never grows past 10 entries.
//
// Mechanism: a 5-byte inline detour on the objective list Add (0x004F39B0,
// __thiscall(this, name, color, float duration, text), callee pops 16 bytes;
// stolen bytes 55 8B EC 6A FF). The hook reads count at this+0x08 (SEH
// guarded) and decides through objective_cap_guard.h:
//   count 0..9   -> stock Add through the trampoline
//   count == 10  -> engine Remove (0x004F3E70) with a local 17-byte NUL-terminated
//                   copy of entry 0's name, then stock Add
//   count < 0 or > 10 -> already corrupt: log, do not add
// Remove frees the entry text with the engine's CRT; OpenShim never frees
// engine memory itself.
//
// Why: stock Add writes entry[count] without a bounds check, so the 11th
// objective (a Lua AddObjective, a mission DLL or a save with 11+ entries)
// overwrites the "display until" float at +0xFC and whatever follows it.

#include "objective_cap_guard.h"
#include "objective_cap_guard_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace ObjectiveCap
    {
        namespace
        {
            constexpr const char* kComponent = "OBJECTIVECAP";

            // Prologue of Add; the patches.json row pins 24 bytes, the detour
            // steals the first 5 (push ebp / mov ebp,esp / push -1).
            const uint8_t kAddPrologue[5] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };

            std::atomic<bool> g_Done{ false };
            volatile long g_DropLogBudget = 16;
            volatile long g_RejectLogBudget = 16;

            using FnAdd = void(__fastcall*)(void* self, void* edx, const char* name, uint32_t color, float duration,
                                            const char* text);
            using FnRemove = void(__fastcall*)(void* self, void* edx, const char* name);

            InlineDetour32 g_AddDetour = {};
            FnAdd volatile g_OrigAdd = nullptr;
            FnRemove g_Remove = nullptr;

            bool ReadCount(void* self, int32_t& count)
            {
                count = 0;
                __try
                {
                    count = *reinterpret_cast<const volatile int32_t*>(static_cast<const uint8_t*>(self) + kCountOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    count = 0;
                    return false;
                }
            }

            bool ReadOldestName(void* self, char (&out)[kNameLength])
            {
                __try
                {
                    const volatile char* src =
                        reinterpret_cast<const volatile char*>(static_cast<const uint8_t*>(self) + kEntriesOffset);
                    for (uint32_t i = 0; i < kNameLength; ++i)
                        out[i] = src[i];
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out[0] = '\0';
                    return false;
                }
            }

            void CallRemove(void* self, const char* name) { g_Remove(self, nullptr, name); }

            void CallAdd(void* self, const char* name, uint32_t color, float duration, const char* text)
            {
                g_OrigAdd(self, nullptr, name, color, duration, text);
            }

            // The new name comes from a script or a save; copy it bounded so
            // a bad pointer cannot fault the log line.
            void SafeName(const char* name, char (&out)[kNameLength])
            {
                out[0] = '\0';
                if (!name)
                    return;
                __try
                {
                    for (uint32_t i = 0; i < kNameLength; ++i)
                    {
                        out[i] = name[i];
                        if (name[i] == '\0')
                            break;
                    }
                    out[kNameLength - 1] = '\0';
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out[0] = '\0';
                }
            }

            void OnDrop(const char* dropped, const char* added)
            {
                if (InterlockedDecrement(&g_DropLogBudget) < 0)
                    return;
                char addedName[kNameLength];
                SafeName(added, addedName);
                LogShimA(LogLevel::Warn, kComponent,
                         "objective list full (%d entries): dropped the oldest \"%s\" to add \"%s\"",
                         static_cast<int>(kCapacity), dropped, addedName);
            }

            void OnReject(int32_t count, const char* added, const char* why)
            {
                if (InterlockedDecrement(&g_RejectLogBudget) < 0)
                    return;
                char addedName[kNameLength];
                SafeName(added, addedName);
                LogShimA(LogLevel::Warn, kComponent,
                         "objective \"%s\" not added: %s (count=%d); the stock Add would write past the list",
                         addedName, why, static_cast<int>(count));
            }

            // __thiscall Add as __fastcall: ecx = this, edx unused, 16 bytes
            // of arguments popped by the callee in both conventions.
            void __fastcall AddHook(void* self, void* edx, const char* name, uint32_t color, float duration,
                                    const char* text)
            {
                (void)edx;
                static const Engine engine = { ReadCount, ReadOldestName, CallRemove, CallAdd, OnDrop, OnReject };
                Run(engine, self, name, color, duration, text);
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock objective list Add", what);
                return false;
            }

            bool Bind(const char* name, uint32_t& address)
            {
                const HookEngine::EngineAddressStatus status = HookEngine::ResolveEngineAddress(name, address);
                if (status == HookEngine::EngineAddressStatus::Bound && address != 0)
                    return true;
                LogShimA(LogLevel::Warn, kComponent,
                         "engine address \"%s\" not verified (status=%d)", name, static_cast<int>(status));
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_OBJECTIVE_CAP_GUARD", "BZR_DISABLE_OBJECTIVE_CAP_GUARD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t add = 0, remove = 0;
                if (!Bind("ObjectiveListAdd", add) || !Bind("ObjectiveListRemove", remove))
                    return Fail("a required engine function failed its byte guard");

                g_Remove = reinterpret_cast<FnRemove>(static_cast<uintptr_t>(remove));
                if (!InstallInlineDetour32(g_AddDetour, add, reinterpret_cast<void*>(&AddHook), sizeof(kAddPrologue),
                                           kAddPrologue, sizeof(kAddPrologue),
                                           reinterpret_cast<void* volatile*>(&g_OrigAdd)))
                    return Fail("the Add detour could not be installed");

                LogShimA(LogLevel::Info, kComponent,
                         "installed: add=0x%08X remove=0x%08X trampoline=0x%08X capacity=%d",
                         add, remove, static_cast<unsigned>(reinterpret_cast<uintptr_t>(g_OrigAdd)),
                         static_cast<int>(kCapacity));
                return true;
            }
        }

        void InstallObjectiveCapGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] ObjectiveCapGuard = 0)");
                return;
            }
            DoInstall();
        }
    }
}
