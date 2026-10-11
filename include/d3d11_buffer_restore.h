#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace BZROpenShim
{
    // Keeps a CPU copy of every D3D11 vertex and index buffer so a recreated
    // device gets them back in place, and skips the mesh reload that would
    // otherwise free the skeletons the game holds bones of. Called by the
    // device-loss recovery once RenderSystem_Direct3D11.dll is loaded, before
    // it creates a device. Returns true when every hook is in place; on any
    // other result the renderer is left exactly as shipped.
    bool InstallD3D11BufferRestore(HMODULE renderer);
}
