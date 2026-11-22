// build_menu_team_color.cpp -- the build menu team colour index stays inside
// its 3-entry array.
//
// See include/build_menu_team_color.h. Rows (GOG Redux 2.2.301):
//   BuildMenuTeamColorArray 0x0059B649: the three colour stores to [ebp-10h],
//     [ebp-0Ch], [ebp-8] (pins the array size; [ebp-4] is the stack cookie).
//   BuildMenuTeamColorClamp 0x0059B6F6: push 3 / push 0 / push team /
//     call Clamp / add esp,0Ch / mov ecx,[ebp+eax*4-10h]. Only the imm8 of
//     push 3 changes, to 2.
//   ControlPanelItemColorInit 0x004A16CD: the one-time fill of the static
//     itemColor table (white, green, red to 0x02CC2B8C..0x02CC2B94); pins the
//     3-entry size and gives the table address.
//   ControlPanelTitleColorRead 0x004A1742: mov edx,[ecx+14h] (team) /
//     mov eax,[edx*4+itemColor] / push eax (font colour).
//   ControlPanelChildColorRead 0x004A1A4E: mov edx,[ecx+14h] (team) /
//     imul eax,[ebp-248h],18h / mov ecx,[ebp-244h] /
//     mov edx,[edx*4+itemColor] / mov [ecx+eax+1030h],edx (button colour).
//   Entry contract at both loads: edx = the raw team, nothing else is read
//   from flags before the next flag-setting instruction (push/mov/call after
//   the title load; mov/jmp after the child load). No branch lands inside
//   either 7-byte load (checked over 0x004A08E0..0x004A6400).

#include "build_menu_team_color.h"
#include "build_menu_team_color_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace BuildMenuTeamColor
    {
        namespace
        {
            constexpr const char* kComponent = "BUILDMENUCOLOR";
            std::atomic<bool> g_Done{ false };

            uint32_t g_ItemColorTable = 0;  // 0x02CC2B8C
            uint32_t g_TitleResume = 0;     // 0x004A174C
            uint32_t g_ChildResume = 0;     // 0x004A1A65

            // Both thunks clamp the team (edx) to 0..2, then do the stolen load.
            // The title thunk clamps a copy in ecx so edx keeps the raw team,
            // as stock; the child load overwrites edx itself.
            __declspec(naked) void TitleColorThunk()
            {
                __asm
                {
                    push ecx
                    mov ecx, edx                        // edx = raw team
                    cmp ecx, 0
                    jge title_low_ok
                    xor ecx, ecx
                title_low_ok:
                    cmp ecx, 2
                    jle title_high_ok
                    mov ecx, 2
                title_high_ok:
                    mov eax, dword ptr [g_ItemColorTable]
                    mov eax, dword ptr [eax + ecx * 4]   // stolen load, clamped index
                    pop ecx
                    jmp dword ptr [g_TitleResume]
                }
            }

            __declspec(naked) void ChildColorThunk()
            {
                __asm
                {
                    cmp edx, 0                          // edx = raw team
                    jge child_low_ok
                    xor edx, edx
                child_low_ok:
                    cmp edx, 2
                    jle child_high_ok
                    mov edx, 2
                child_high_ok:
                    push eax
                    mov eax, dword ptr [g_ItemColorTable]
                    mov edx, dword ptr [eax + edx * 4]   // stolen load, clamped index
                    pop eax
                    jmp dword ptr [g_ChildResume]
                }
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock colours there", what);
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

            bool InstallDrawBuildMenu()
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

            uint32_t ReadDisp(uint32_t address)
            {
                uint32_t value = 0;
                std::memcpy(&value, reinterpret_cast<const void*>(static_cast<uintptr_t>(address)), sizeof(value));
                return value;
            }

            bool JumpTo(uint32_t site, void (*thunk)())
            {
                uint8_t jump[kColorLoadLength];
                std::memset(jump, 0x90, sizeof(jump));
                jump[0] = 0xE9;
                const int32_t rel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(thunk) -
                                                         (static_cast<uintptr_t>(site) + 5));
                std::memcpy(jump + 1, &rel, sizeof(rel));
                return HookEngine::WriteMemory(site, jump, sizeof(jump));
            }

            bool InstallControlPanel()
            {
                uint32_t init = 0, title = 0, child = 0;
                const HookEngine::EngineRow rows[] = {
                    { "ControlPanelItemColorInit", &init },
                    { "ControlPanelTitleColorRead", &title },
                    { "ControlPanelChildColorRead", &child },
                };
                if (!HookEngine::BindEngineRows("Control panel item colour", rows))
                    return Fail("a control panel row failed its byte guard");

                const uint32_t titleLoad = title + kTitleLoadOffset;
                const uint32_t childLoad = child + kChildLoadOffset;
                const uint32_t table = ReadDisp(init + kInitTableStoreOffset);
                if (ReadDisp(titleLoad + kLoadTableDispOffset) != table ||
                    ReadDisp(childLoad + kLoadTableDispOffset) != table)
                    return Fail("the control panel loads do not read the itemColor table");

                g_ItemColorTable = table;
                g_TitleResume = titleLoad + kColorLoadLength;
                g_ChildResume = childLoad + kColorLoadLength;

                uint8_t titleStock[kColorLoadLength];
                std::memcpy(titleStock, reinterpret_cast<const void*>(static_cast<uintptr_t>(titleLoad)),
                            sizeof(titleStock));
                if (!JumpTo(titleLoad, &TitleColorThunk))
                    return Fail("the control panel title load could not be written");
                if (!JumpTo(childLoad, &ChildColorThunk))
                {
                    if (HookEngine::WriteMemory(titleLoad, titleStock, sizeof(titleStock)))
                        return Fail("the control panel child load could not be written (title load restored)");
                    return Fail("the control panel child load could not be written and the title load "
                                "could not be restored");
                }

                LogShimA(LogLevel::Info, kComponent, "installed: control panel title=0x%08X child=0x%08X table=0x%08X",
                         titleLoad, childLoad, table);
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
            // Independent sites: a guard mismatch at one leaves the other in place.
            InstallDrawBuildMenu();
            InstallControlPanel();
        }
    }
}
