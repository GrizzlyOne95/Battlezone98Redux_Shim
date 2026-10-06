#pragma once
#include <Windows.h>

// Local, opt-in GOG experiment. One vehicle's legacy GEO is a contact target;
// the other vehicle retains its normal COLP body. No terrain/projectile changes.
namespace BZROpenShim::GeometryContactTest
{
    DWORD Capabilities();
    BOOL Set(DWORD handle, BOOL enabled);
    BOOL Clear();
    BOOL Stats(DWORD handle, DWORD* enabled, DWORD* parts, DWORD* faces,
               DWORD* checks, DWORD* hits, DWORD* fallbacks);
}
