#pragma once

namespace BZROpenShim
{
    // Turns the options screen's resolution cycle control into a dropdown
    // (src/patches/resolution_dropdown.cpp). On by default:
    //
    //   [Graphics]
    //   ResolutionDropdown = 1
    //
    // OPENSHIM_DISABLE_RESOLUTION_DROPDOWN=1 turns it off.
    void InitializeResolutionDropdown();
}
