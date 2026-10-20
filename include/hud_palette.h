#pragma once
namespace BZROpenShim::HudPalette
{
    bool ReloadConfig();
    const char* UnavailableReason();
    void Tick();
    // Single owner for the cockpit ammo CALLs shared by tint and idle fade.
    bool BindAmmoDrawAdapters();
    bool InstallAmmoDrawAdapters();
}
