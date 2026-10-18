#pragma once

namespace BZROpenShim
{
    // Caches the per-draw GpuProgramParameters::getConstantDefinition lookups
    // in D3D11HLSLProgram::getConstantBuffer. Safe to call repeatedly; does
    // nothing until RenderSystem_Direct3D11.dll is loaded, then installs once
    // or stands down for the process.
    void InstallD3D11ConstantLookupCacheIfPossible();
}
