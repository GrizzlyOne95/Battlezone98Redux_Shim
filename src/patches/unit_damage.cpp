// Per-receiver effective damage, after difficulty adjustment and before health
// and death. Never alter the shared DAMAGE record (blast victims reuse it).
#include "bzr_hooks_internal.h"
#include "patcher.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "unit_damage_policy.h"
#include "unit_damage.h"
#include "BZROpenShim.h"

namespace
{
    BZROpenShim::UnitDamage::Policy g_Policy;
    BZROpenShim::InlineDetour32 g_Detour;
    void* g_Resume = nullptr;
    uintptr_t g_GetHandle = 0;

    bool Identity(void* object, uint32_t handle) noexcept
    {
        if (!object || !handle || !g_GetHandle) return false;
        __try
        {
            using GetHandle = uint32_t(__thiscall*)(void*);
            return reinterpret_cast<GetHandle>(g_GetHandle)(object) == handle &&
                BZROpenShim::GameObjectFromHandleGog(static_cast<int>(handle)) == object;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    uint32_t CurrentHandle(void* object) noexcept
    {
        __try
        {
            using GetHandle = uint32_t(__thiscall*)(void*);
            return reinterpret_cast<GetHandle>(g_GetHandle)(object);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
    }

    void __cdecl ApplyDamage(void* frame) noexcept
    {
        if (g_Policy.Empty()) return;
        // PROVEN on the qualified GOG Craft::DamageAlloc frame: this is the
        // distributedObject subobject (+0x18), not the full GameObject.
        auto* bytes = static_cast<uint8_t*>(frame);
        auto* object = *reinterpret_cast<uint8_t**>(bytes - 0xF8) - 0x18;
        auto* damage = reinterpret_cast<float*>(bytes - 0xFC);
        *damage = g_Policy.Apply(reinterpret_cast<uintptr_t>(object), CurrentHandle(object), *damage);
    }

    __declspec(naked) void DamageThunk()
    {
        __asm
        {
            pushfd
            pushad
            mov eax, esp
            sub esp, 528
            and esp, -16
            mov [esp+512], eax
            fxsave [esp]
            push ebp
            call ApplyDamage
            add esp, 4
            fxrstor [esp]
            mov esp, [esp+512]
            popad
            popfd
            jmp dword ptr [g_Resume]
        }
    }

    bool EnsureHook()
    {
        if (g_Resume) return true;
        if (BZROpenShim::g_IsSteamExe || !BZROpenShim::IsCompatibleGameVersion()) return false;
        const auto site = HookEngine::ResolveNamedAddress("Craft::EffectiveDamageResistanceSite");
        g_GetHandle = HookEngine::ResolveNamedAddress("GameObject::GetHandle");
        if (!site || !g_GetHandle) return false;
        uint8_t expected[8] = {};
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(site), expected, sizeof(expected), &read) ||
            read != sizeof(expected) || expected[0] != 0xF3 || expected[1] != 0x0F ||
            expected[2] != 0x10 || expected[3] != 0x05) return false;
        if (!BZROpenShim::InstallInlineDetour32(g_Detour, site, DamageThunk, sizeof(expected), expected, sizeof(expected))) return false;
        g_Resume = g_Detour.trampoline; // replays MOVSS xmm0,[stock zero], resumes COMISS
        BZROpenShim::Log(L"[UNITDAMAGE] Craft effective-damage hook installed site=0x%08X trampoline=%p\n", site, g_Resume);
        return true;
    }
}

extern "C" BOOL WINAPI OpenShimImpl_HasNativeDamageResistance()
{
    return EnsureHook() ? TRUE : FALSE;
}
extern "C" BOOL WINAPI OpenShimImpl_SetUnitDamageMultiplier(void* object, DWORD handle, float multiplier)
{
    if (!EnsureHook() || !Identity(object, handle)) return FALSE;
    try { return g_Policy.Set(reinterpret_cast<uintptr_t>(object), handle, multiplier) ? TRUE : FALSE; }
    catch (...) { return FALSE; }
}
extern "C" BOOL WINAPI OpenShimImpl_ClearUnitDamageMultiplier(DWORD handle)
{
    g_Policy.Clear(handle);
    return TRUE;
}
extern "C" BOOL WINAPI OpenShimImpl_ResetUnitDamageMultipliers()
{
    BZROpenShim::UnitDamage::ResetMissionState();
    return TRUE;
}
void BZROpenShim::UnitDamage::ResetMissionState() noexcept
{
    g_Policy.Reset();
}
