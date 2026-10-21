#pragma once

#include "weapon_presentation.h"

// GOG cannon call-site and live ParameterDB scope bridges. Kept independent
// of the installer/backend so the real x86 bridges can run in the Win32 ABI
// harness. No release addresses or native object ownership live here.
namespace BZROpenShim::WeaponPresentation::NativeBridges
{
    using Factory = void* (__thiscall*)(void*, const Matrix*, void*);
    using PopScope = void (__thiscall*)(void*);
    using ObserveShot = void (__cdecl*)(void*, const Matrix*, void*, void*) noexcept;
    using ObserveClass = void (__cdecl*)(void*, void*) noexcept;

    // Null factory retains the shared factory for the ODF-only installation.
    void Configure(Factory factory, PopScope popScope, ObserveShot shot,
        ObserveClass weaponClass, ObserveClass craftClass) noexcept;

    // One factory call shared by casings and presentation. Registration occurs
    // under the startup code-patch lock, before gameplay begins.
    void ConfigureShotFactory(Factory factory, ObserveShot casings) noexcept;
    void RecordShotSite(bool machineGun, uint32_t site) noexcept;
    uint32_t ShotSite(bool machineGun) noexcept;

    // These are only addressed as machine-code targets. Factory bridge pops
    // the original two stack arguments; scope bridges tail-call the original.
    void CannonOrdnanceCallBridge();
    void WeaponClassScopePopBridge();
    void CraftClassScopePopBridge();
}
