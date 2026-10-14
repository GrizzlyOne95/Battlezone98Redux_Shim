#pragma once
#include <cstdint>

namespace BZROpenShim
{
    // Called only for the custom-planet play(bool) CALL operand. Returns null
    // unless the original target and all required engine bindings agree.
    void* PrepareCustomPlanetVideoHook(uint32_t callAddress);
}
