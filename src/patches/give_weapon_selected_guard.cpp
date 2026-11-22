// give_weapon_selected_guard.cpp -- GiveWeapon(h, nil, slot) also clears the
// slot's selected bit, and GiveWeapon rejects slots outside 0..4.
//
// See include/give_weapon_selected_guard.h for the two defects.
//
// Mechanism (GOG Redux 2.2.301, rows in scripts/patches.json):
//   GiveWeaponNilArmObjectMaskCall 0x0061304C, the nil arm's last call:
//     50              push eax          ; object mask & ~bit
//     8B 4D 08        mov ecx,[ebp+8]   ; GameObject
//     E8 rel32        call 0x005C7450   ; GameObject::SetWeaponMask (+0x218)
//   followed by the join at 0x00613055 (8B 4D FC, mov ecx,[ebp-4]) that both
//   arms reach. The 9 bytes become jmp NilArmThunk + 4 NOPs. Nothing branches
//   into them: the arm is entered at 0x00613013 and the non-nil arm jumps to
//   0x00613055. Entry contract at the site: ebp is GiveWeapon's frame,
//   [ebp+8] = GameObject*, [ebp+10h] = slot, [ebp-4] = Carrier* (non-null,
//   tested at 0x00612F41), eax = the mask argument. The thunk runs the stolen
//   push/mov/call first, then the cleanup, then jumps to 0x00613055, which
//   reloads ecx itself; eax/ecx/edx/flags are dead there.
//
//   GiveWeaponSlotRangeCheck 0x00612F23: the jcc at +4 becomes jl reject.
//
// Both writes are all-or-nothing; any byte-guard miss leaves the engine stock.

#include "give_weapon_selected_guard.h"
#include "give_weapon_selected_guard_install.h"

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
    namespace GiveWeaponSelected
    {
        namespace
        {
            constexpr const char* kComponent = "GIVEWEAPONSEL";

            // Site bytes: the 9 bytes that are replaced, as pinned by the row.
            constexpr uint32_t kNilArmPatchLength = 9;
            const uint8_t kNilArmStock[kNilArmPatchLength] = { 0x50, 0x8B, 0x4D, 0x08, 0xE8,
                                                               0xFB, 0x43, 0xFB, 0xFF };

            std::atomic<bool> g_Done{ false };
            volatile long g_LogBudget = 16;

            using FnSetSelected = void(__fastcall*)(void* carrier, void* edx, uint32_t mask);

            uint32_t g_SetObjectMask = 0;   // 0x005C7450
            uint32_t g_Resume = 0;          // 0x00613055
            FnSetSelected g_SetSelected = nullptr;  // 0x004D9880

            bool ReadSelected(void* carrier, uint32_t& selected)
            {
                selected = 0;
                __try
                {
                    selected = *reinterpret_cast<const volatile uint32_t*>(static_cast<const uint8_t*>(carrier) +
                                                                           kCarrierSelectedOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    selected = 0;
                    return false;
                }
            }

            void __cdecl ClearStaleSelected(void* carrier, int slot)
            {
                if (!carrier || !g_SetSelected)
                    return;
                uint32_t selected = 0;
                if (!ReadSelected(carrier, selected))
                    return;
                uint32_t next = 0;
                if (!SelectedMaskAfterNilGive(selected, slot, next))
                    return;
                g_SetSelected(carrier, nullptr, next);
                if (InterlockedDecrement(&g_LogBudget) >= 0)
                    LogShimA(LogLevel::Info, kComponent,
                             "GiveWeapon(nil) emptied selected slot %d on carrier %p: selected 0x%X -> 0x%X",
                             slot, carrier, selected, next);
            }

            __declspec(naked) void NilArmThunk()
            {
                __asm
                {
                    push eax                        // stolen: mask argument
                    mov ecx, dword ptr [ebp + 8]    // stolen: GameObject*
                    call dword ptr [g_SetObjectMask]
                    push dword ptr [ebp + 0x10]     // slot
                    push dword ptr [ebp - 4]        // Carrier*
                    call ClearStaleSelected
                    add esp, 8
                    jmp dword ptr [g_Resume]
                }
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock GiveWeapon", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_GIVE_WEAPON_NIL_CLEARS_SELECTED",
                      "BZR_DISABLE_GIVE_WEAPON_NIL_CLEARS_SELECTED" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t rangeSite = 0, nilSite = 0, setObjectMask = 0, setSelected = 0;
                const HookEngine::EngineRow rows[] = {
                    { "GiveWeaponSlotRangeCheck", &rangeSite },
                    { "GiveWeaponNilArmObjectMaskCall", &nilSite },
                    { "GiveWeaponSetObjectMask", &setObjectMask },
                    { "GiveWeaponCarrierSetSelected", &setSelected },
                };
                if (!HookEngine::BindEngineRows("GiveWeapon selected guard", rows))
                    return Fail("a GiveWeapon row failed its byte guard");

                // The stolen call must reach the SetWeaponMask row.
                int32_t rel = 0;
                std::memcpy(&rel, kNilArmStock + 5, sizeof(rel));
                const uint32_t callTarget = nilSite + kNilArmPatchLength + static_cast<uint32_t>(rel);
                if (callTarget != setObjectMask)
                    return Fail("the nil arm's call does not reach GameObject::SetWeaponMask");

                g_SetObjectMask = setObjectMask;
                g_Resume = nilSite + kNilArmPatchLength;
                g_SetSelected = reinterpret_cast<FnSetSelected>(static_cast<uintptr_t>(setSelected));

                uint8_t jump[kNilArmPatchLength];
                std::memset(jump, 0x90, sizeof(jump));
                jump[0] = 0xE9;
                const int32_t jumpRel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(&NilArmThunk) -
                                                             (static_cast<uintptr_t>(nilSite) + 5));
                std::memcpy(jump + 1, &jumpRel, sizeof(jumpRel));

                if (!HookEngine::WriteMemory(rangeSite + kRangeCheckJccOffset, kRangeCheckFixedJcc,
                                             sizeof(kRangeCheckFixedJcc)))
                    return Fail("the slot range check could not be written");
                if (!HookEngine::WriteMemory(nilSite, jump, sizeof(jump)))
                {
                    HookEngine::WriteMemory(rangeSite + kRangeCheckJccOffset, kRangeCheckStockJcc,
                                            sizeof(kRangeCheckStockJcc));
                    return Fail("the nil arm could not be written (range check restored)");
                }

                LogShimA(LogLevel::Info, kComponent,
                         "installed: range=0x%08X nilArm=0x%08X resume=0x%08X setSelected=0x%08X",
                         rangeSite, nilSite, g_Resume, setSelected);
                return true;
            }
        }

        void InstallGiveWeaponSelectedGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] GiveWeaponNilClearsSelected = 0)");
                return;
            }
            DoInstall();
        }
    }
}
