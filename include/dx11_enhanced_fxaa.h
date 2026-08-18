#pragma once

namespace BZROpenShim
{
    // Starts the opt-in DX11 Enhanced presentation-stage FXAA path.
    //
    // Activation is deliberately explicit and defaults OFF:
    //
    //   [DX11Enhanced]
    //   FXAA = 1
    //
    // or OPENSHIM_DX11_ENHANCED_FXAA=1.
    //
    // The implementation only watches RenderSystem_Direct3D11.dll and leaves
    // DX9 and ordinary/default-off DX11 execution untouched.
    void InitializeDx11EnhancedFxaa();

    // Stops the short-lived renderer-discovery worker. Installed COM/IAT hooks
    // remain process-lifetime and become pass-through once shutdown is set.
    void ShutdownDx11EnhancedFxaa();
}
