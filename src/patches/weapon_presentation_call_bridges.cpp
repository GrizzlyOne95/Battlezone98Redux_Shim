#include "weapon_presentation_call_bridges.h"
#include <atomic>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error Weapon presentation call bridges require MSVC x86
#endif

namespace BZROpenShim::WeaponPresentation::NativeBridges
{
    namespace
    {
        Factory g_Factory = nullptr;
        PopScope g_PopScope = nullptr;
        std::atomic<ObserveShot> g_Shot{ nullptr };
        std::atomic<ObserveShot> g_Casings{ nullptr };
        uint32_t g_Sites[2] = {};

        void __cdecl DispatchShot(void* weapon, const Matrix* pose, void* owner, void* result) noexcept
        {
            // A failed factory produces no accepted shot for either effect.
            if (!result) return;
            if (const auto observer = g_Casings.load()) observer(weapon, pose, owner, result);
            if (const auto observer = g_Shot.load()) observer(weapon, pose, owner, result);
        }
        ObserveClass g_WeaponClass = nullptr;
        ObserveClass g_CraftClass = nullptr;
    }

    void Configure(Factory factory, PopScope popScope, ObserveShot shot,
        ObserveClass weaponClass, ObserveClass craftClass) noexcept
    {
        if (!g_Factory && factory) g_Factory = factory;
        if (!g_PopScope) g_PopScope = popScope;
        g_Shot.store(shot);
        if (!g_WeaponClass) g_WeaponClass = weaponClass;
        if (!g_CraftClass) g_CraftClass = craftClass;
    }

    void ConfigureShotFactory(Factory factory, ObserveShot casings) noexcept
    {
        g_Factory = factory;
        g_Casings.store(casings);
    }

    void RecordShotSite(bool machineGun, uint32_t site) noexcept { g_Sites[machineGun ? 1 : 0] = site; }
    uint32_t ShotSite(bool machineGun) noexcept { return g_Sites[machineGun ? 1 : 0]; }

    // Cannon and MachineGun caller frame: weapon at [ebp-250h]. Original factory ABI:
    // ECX=OrdnanceClass; [esp+4]=final Matrix; [esp+8]=owner OBJ; RET 8.
    // Observe after factory return, preserving its EAX and nonvolatile regs.
    __declspec(naked) void CannonOrdnanceCallBridge()
    {
        __asm
        {
            push ebp
            mov ebp, esp
            push ebx
            push esi
            push edi
            mov esi, dword ptr [ebp]
            mov esi, dword ptr [esi-250h]
            mov edi, dword ptr [ebp+8]
            mov ebx, dword ptr [ebp+0Ch]
            push ebx
            push edi
            call dword ptr [g_Factory]
            push eax
            push eax
            push ebx
            push edi
            push esi
            call DispatchShot
            add esp, 10h
            pop eax
            pop edi
            pop esi
            pop ebx
            mov esp, ebp
            pop ebp
            ret 8
        }
    }

    // Scope ECX must stay live until the original PopODF runs. The newly
    // constructed class is saved in the enclosing caller frame, not in EAX.
    __declspec(naked) void WeaponClassScopePopBridge()
    {
        __asm
        {
            push ebp
            mov ebp, esp
            pushfd
            pushad
            mov eax, dword ptr [ebp]
            push dword ptr [eax-3Ch]
            push ecx
            call dword ptr [g_WeaponClass]
            add esp, 8
            popad
            popfd
            pop ebp
            jmp dword ptr [g_PopScope]
        }
    }

    __declspec(naked) void CraftClassScopePopBridge()
    {
        __asm
        {
            push ebp
            mov ebp, esp
            pushfd
            pushad
            mov eax, dword ptr [ebp]
            push dword ptr [eax-4Ch]
            push ecx
            call dword ptr [g_CraftClass]
            add esp, 8
            popad
            popfd
            pop ebp
            jmp dword ptr [g_PopScope]
        }
    }
}
