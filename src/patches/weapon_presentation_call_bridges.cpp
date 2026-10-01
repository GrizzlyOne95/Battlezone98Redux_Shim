#include "weapon_presentation_call_bridges.h"

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error Weapon presentation call bridges require MSVC x86
#endif

namespace BZROpenShim::WeaponPresentation::NativeBridges
{
    namespace
    {
        Factory g_Factory = nullptr;
        PopScope g_PopScope = nullptr;
        ObserveShot g_Shot = nullptr;
        ObserveClass g_WeaponClass = nullptr;
        ObserveClass g_CraftClass = nullptr;
    }

    void Configure(Factory factory, PopScope popScope, ObserveShot shot,
        ObserveClass weaponClass, ObserveClass craftClass) noexcept
    {
        g_Factory = factory;
        g_PopScope = popScope;
        g_Shot = shot;
        g_WeaponClass = weaponClass;
        g_CraftClass = craftClass;
    }

    // Original caller frame: weapon at [ebp-190h]. Original factory ABI:
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
            mov esi, dword ptr [esi-190h]
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
            call dword ptr [g_Shot]
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
