#define CINTERFACE
#define D3D11_NO_HELPERS
#include <d3d11.h>
#include <cstddef>
#include "terrain_height_texture.h"
// Prove the hook ordinal against the installed Windows SDK's public COM ABI.
static_assert(offsetof(ID3D11DeviceContextVtbl, DSSetShader) ==
    sizeof(void*) * BZROpenShim::TerrainHeight::kDomainShaderSetterSlot);
int main() { return 0; }
