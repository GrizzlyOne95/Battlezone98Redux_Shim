// lua_formation_fix.cpp -- repair the stock Lua Formation(me, him, priority)
// binding. Design, evidence and failure modes: Docs/LUA_FORMATION_BINDING_20261014.md.
//
// Mechanism: the Lua registration table row for "Formation" (0x00872370,
// { "Formation" 0x0087CF64, 0x005079B0 }) has its function pointer swapped for
// an OpenShim lua_CFunction. No code byte is rewritten; the stock binding
// stays intact and a restore is one pointer write.

#include "lua_formation_fix.h"
#include "lua_formation_fix_install.h"

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
    namespace LuaFormation
    {
        namespace
        {
            constexpr const char* kComponent = "LUAFORMATION";
            constexpr uint32_t kFormationNameString = 0x0087CF64; // "Formation"
            constexpr long kLogBudget = 12;

            std::atomic<bool> g_Installed{ false };
            std::atomic<bool> g_Done{ false };
            volatile long g_CallLogBudget = kLogBudget;

            using FnGetHandle = int32_t(__cdecl*)(void* L, int index);
            using FnLuaType = int(__cdecl*)(void* L, int index);
            using FnOptInteger = int32_t(__cdecl*)(void* L, int index, int32_t def);
            using FnFormation = void(__cdecl*)(int32_t me, int32_t him, int32_t priority);

            FnGetHandle g_GetHandle = nullptr;
            FnLuaType g_LuaType = nullptr;
            FnOptInteger g_OptInteger = nullptr;
            FnFormation g_Formation = nullptr;

            // The Engine table takes plain function pointers; __cdecl is the
            // default calling convention for these on x86 MSVC, so thin
            // forwarders keep the header free of calling-convention syntax.
            int32_t FwdGetHandle(void* L, int i) { return g_GetHandle(L, i); }
            int FwdLuaType(void* L, int i) { return g_LuaType(L, i); }
            int32_t FwdOptInteger(void* L, int i, int32_t d) { return g_OptInteger(L, i, d); }
            void FwdFormation(int32_t a, int32_t b, int32_t c) { g_Formation(a, b, c); }

            // lua_CFunction: int (*)(lua_State*), cdecl, caller pops.
            int __cdecl FormationBinding(void* L)
            {
                static const Engine engine = { FwdGetHandle, FwdLuaType, FwdOptInteger, FwdFormation };
                if (InterlockedDecrement(&g_CallLogBudget) >= 0)
                    LogShimA(LogLevel::Info, kComponent, "Formation called (argument 2 type %d)", g_LuaType(L, 2));
                return Run(L, engine);
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock Formation binding", what);
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
                      "OPENSHIM_DISABLE_LUA_FORMATION_FIX", "BZR_DISABLE_LUA_FORMATION_FIX" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t binding = 0, getHandle = 0, luaType = 0, optInteger = 0, formation = 0, slotRow = 0;
                if (!Bind("LuaFormationBinding", binding) || !Bind("LuaGetHandle", getHandle) ||
                    !Bind("LuaType", luaType) || !Bind("LuaOptInteger", optInteger) ||
                    !Bind("GameFormation", formation))
                    return Fail("a required engine function failed its byte guard");

                if (HookEngine::ResolveEngineAddress("LuaFormationRegistration", slotRow) !=
                        HookEngine::EngineAddressStatus::BoundData || slotRow == 0)
                    return Fail("the registration row address is not pinned for this build");

                // The row is { const char* name; lua_CFunction fn; }. Both
                // halves must be what this build's analysis saw, and the name
                // must really read "Formation".
                uint32_t row[2] = {};
                char name[16] = {};
                if (!HookEngine::ReadMemory(slotRow, row, sizeof(row)) ||
                    !HookEngine::ReadMemory(row[0], name, sizeof(name) - 1))
                    return Fail("the registration row is unreadable");
                if (row[0] != kFormationNameString || std::strcmp(name, "Formation") != 0)
                    return Fail("the registration row does not name \"Formation\"");
                if (row[1] != binding)
                    return Fail("the registration row does not hold the stock binding");

                g_GetHandle = reinterpret_cast<FnGetHandle>(static_cast<uintptr_t>(getHandle));
                g_LuaType = reinterpret_cast<FnLuaType>(static_cast<uintptr_t>(luaType));
                g_OptInteger = reinterpret_cast<FnOptInteger>(static_cast<uintptr_t>(optInteger));
                g_Formation = reinterpret_cast<FnFormation>(static_cast<uintptr_t>(formation));

                const uint32_t replacement = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&FormationBinding));
                if (!HookEngine::WriteMemory(slotRow + 4, &replacement, sizeof(replacement)))
                    return Fail("the registration row could not be rewritten");

                LogShimA(LogLevel::Info, kComponent,
                         "installed: row=0x%08X stock=0x%08X now=0x%08X getHandle=0x%08X luaType=0x%08X "
                         "optInteger=0x%08X native=0x%08X",
                         slotRow, binding, replacement, getHandle, luaType, optInteger, formation);
                return true;
            }
        }

        void InstallLuaFormationFixIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] LuaFormationBinding = 0)");
                return;
            }
            g_Installed.store(DoInstall());
        }
    }
}
