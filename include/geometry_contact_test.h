#pragma once
#include <Windows.h>

// Local, opt-in GOG experiment. Each pair uses one legacy GEO contact target;
// the other vehicle retains its normal COLP body. No terrain/projectile changes.
namespace BZROpenShim::GeometryContactTest
{
    DWORD Capabilities();
    void InitializeGlobal(); // Startup INI request; defaults off, restart to apply.
    void Tick(); // Main-thread retirement of removed/replaced craft.
    BOOL Set(DWORD handle, BOOL enabled);
    BOOL Clear();
    BOOL Stats(DWORD handle, DWORD* enabled, DWORD* parts, DWORD* faces,
               DWORD* checks, DWORD* hits, DWORD* fallbacks);
}
