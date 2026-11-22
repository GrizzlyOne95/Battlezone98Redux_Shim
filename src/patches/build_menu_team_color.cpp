// build_menu_team_color.cpp -- the build menu team colour index stays inside
// its 3-entry array.
//
// See include/build_menu_team_color.h. Rows (GOG Redux 2.2.301):
//   BuildMenuTeamColorArray 0x0059B649: the three colour stores to [ebp-10h],
//     [ebp-0Ch], [ebp-8] (pins the array size; [ebp-4] is the stack cookie).
//   BuildMenuTeamColorClamp 0x0059B6F6: push 3 / push 0 / push team /
//     call Clamp / add esp,0Ch / mov ecx,[ebp+eax*4-10h]. Only the imm8 of
//     push 3 changes, to 2.

#include "build_menu_team_color.h"
#include "build_menu_team_color_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace BuildMenuTeamColor
    {
        namespace
        {
            constexpr const char* kComponent = "BUILDMENUCOLOR";
            std::atomic<bool> g_Done{ false };

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock build menu colours", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_BUILD_MENU_TEAM_COLOR_CLAMP", "BZR_DISABLE_BUILD_MENU_TEAM_COLOR_CLAMP" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t array = 0, clamp = 0;
                const HookEngine::EngineRow rows[] = {
                    { "BuildMenuTeamColorArray", &array },
                    { "BuildMenuTeamColorClamp", &clamp },
                };
                if (!HookEngine::BindEngineRows("Build menu team colour", rows))
                    return Fail("a build menu row failed its byte guard");

                const uint8_t imm = kFixedClampMax;
                if (!HookEngine::WriteMemory(clamp + kClampMaxImmOffset, &imm, 1))
                    return Fail("the clamp maximum could not be written");

                LogShimA(LogLevel::Info, kComponent, "installed: clamp=0x%08X max %u -> %u (array 0x%08X)", clamp,
                         static_cast<unsigned>(kStockClampMax), static_cast<unsigned>(kFixedClampMax), array);
                return true;
            }
        }

        void InstallBuildMenuTeamColorIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] BuildMenuTeamColorClamp = 0)");
                return;
            }
            DoInstall();
        }
    }
}
