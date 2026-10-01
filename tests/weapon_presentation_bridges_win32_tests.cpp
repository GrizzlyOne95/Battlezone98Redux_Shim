#include "weapon_presentation_call_bridges.h"

#include <cstdio>
#include <cstdlib>

namespace Bridges = BZROpenShim::WeaponPresentation::NativeBridges;
using Matrix = BZROpenShim::WeaponPresentation::Matrix;
using Bridges::CannonOrdnanceCallBridge;
using Bridges::WeaponClassScopePopBridge;
using Bridges::CraftClassScopePopBridge;

namespace
{
    void* g_ExpectedClass = nullptr;
    void* g_ExpectedWeapon = nullptr;
    void* g_ExpectedOwner = nullptr;
    const Matrix* g_ExpectedPose = nullptr;
    void* g_Result = nullptr;
    void* g_ExpectedScope = nullptr;
    unsigned g_Order = 0;
    unsigned g_PopCalls = 0;
    unsigned g_WeaponClassCalls = 0;
    unsigned g_CraftClassCalls = 0;
    int g_RegistersPreserved = 0;

    void Require(bool condition, const char* message) noexcept
    {
        if (!condition) { std::fprintf(stderr, "%s\n", message); std::abort(); }
    }

    void* __fastcall Factory(void* objectClass, void*, const Matrix* pose, void* owner)
    {
        Require(g_Order++ == 0, "factory order changed");
        Require(objectClass == g_ExpectedClass && pose == g_ExpectedPose && owner == g_ExpectedOwner,
            "factory ECX or stack arguments changed");
        return g_Result;
    }

    void __cdecl Shot(void* weapon, const Matrix* pose, void* owner, void* result) noexcept
    {
        Require(g_Order++ == 1, "observer ran before factory");
        Require(weapon == g_ExpectedWeapon && pose == g_ExpectedPose && owner == g_ExpectedOwner &&
            result == g_Result, "shot observer recovered wrong frame/arguments");
        __asm { mov eax, 11223344h }
        __asm { mov ecx, 55667788h }
        __asm { mov edx, 12345678h }
    }

    void __cdecl WeaponClass(void* scope, void* objectClass) noexcept
    {
        Require(scope == g_ExpectedScope && objectClass == g_ExpectedClass && g_PopCalls == 0,
            "weapon config read wrong frame or expired scope");
        ++g_WeaponClassCalls;
        __asm { mov ecx, 55667788h }
    }

    void __cdecl CraftClass(void* scope, void* objectClass) noexcept
    {
        Require(scope == g_ExpectedScope && objectClass == g_ExpectedClass && g_PopCalls == 1,
            "craft config read wrong frame or expired scope");
        ++g_CraftClassCalls;
        __asm { mov ecx, 55667788h }
    }

    void __fastcall Pop(void* scope, void*)
    {
        Require(scope == g_ExpectedScope, "scope ECX was not restored");
        ++g_PopCalls;
    }

    // Synthetic stock frames have the exact qualified frame slots. These call
    // the production bridges, so wrong RET/stack cleanup or preservation is an
    // actual process failure, rather than a mock of the bridge's logic.
    __declspec(naked) void* __cdecl InvokeCannon(void*, void*, const Matrix*, void*)
    {
        __asm
        {
            push ebp
            mov ebp, esp
            push ebx
            push esi
            push edi
            sub esp, 190h
            mov eax, dword ptr [ebp+8]
            mov dword ptr [ebp-190h], eax
            mov ebx, 12345678h
            mov esi, 23456789h
            mov edi, 3456789Ah
            mov ecx, dword ptr [ebp+0Ch]
            push dword ptr [ebp+14h]
            push dword ptr [ebp+10h]
            call CannonOrdnanceCallBridge
            mov dword ptr [g_RegistersPreserved], 0
            cmp ebx, 12345678h
            jne failed
            cmp esi, 23456789h
            jne failed
            cmp edi, 3456789Ah
            jne failed
            lea edx, [ebp-19Ch]
            cmp esp, edx
            jne failed
            mov dword ptr [g_RegistersPreserved], 1
        failed:
            lea esp, [ebp-0Ch]
            pop edi
            pop esi
            pop ebx
            pop ebp
            ret
        }
    }

    __declspec(naked) void __cdecl InvokeWeaponScope(void*, void*)
    {
        __asm
        {
            push ebp
            mov ebp, esp
            sub esp, 40h
            mov eax, dword ptr [ebp+0Ch]
            mov dword ptr [ebp-3Ch], eax
            mov ecx, dword ptr [ebp+8]
            call WeaponClassScopePopBridge
            mov esp, ebp
            pop ebp
            ret
        }
    }

    __declspec(naked) void __cdecl InvokeCraftScope(void*, void*)
    {
        __asm
        {
            push ebp
            mov ebp, esp
            sub esp, 50h
            mov eax, dword ptr [ebp+0Ch]
            mov dword ptr [ebp-4Ch], eax
            mov ecx, dword ptr [ebp+8]
            call CraftClassScopePopBridge
            mov esp, ebp
            pop ebp
            ret
        }
    }
}

int main()
{
    int weapon = 1, objectClass = 2, owner = 3, ordnance = 4, scope = 5;
    const Matrix pose = BZROpenShim::WeaponConvergence::Identity();
    g_ExpectedWeapon = &weapon; g_ExpectedClass = &objectClass; g_ExpectedOwner = &owner;
    g_ExpectedPose = &pose; g_ExpectedScope = &scope;
    Bridges::Configure(reinterpret_cast<Bridges::Factory>(Factory),
        reinterpret_cast<Bridges::PopScope>(Pop), Shot, WeaponClass, CraftClass);
    for (void* result : { static_cast<void*>(&ordnance), static_cast<void*>(nullptr) })
    {
        g_Order = 0; g_Result = result;
        Require(InvokeCannon(&weapon, &objectClass, &pose, &owner) == result,
            "observer clobbered native factory EAX");
        Require(g_Order == 2 && g_RegistersPreserved == 1, "callee cleanup or nonvolatile registers changed");
    }
    InvokeWeaponScope(&scope, &objectClass);
    InvokeCraftScope(&scope, &objectClass);
    Require(g_PopCalls == 2 && g_WeaponClassCalls == 1 && g_CraftClassCalls == 1, "scope calls duplicated/skipped");
    std::puts("weapon_presentation_bridges_win32_tests: all checks passed");
}
