#pragma once

namespace BZROpenShim
{
    // Direct3D 11 device-loss recovery (src/patches/d3d11_device_loss_recovery.cpp).
    // After a GPU reset, Ogre's device recreation waits until the hardware
    // adapter has settled and never falls back to WARP while that adapter is
    // coming back. On by default:
    //
    //   [Graphics]
    //   D3D11DeviceLossRecovery = 1
    //
    // OPENSHIM_DISABLE_D3D11_DEVICE_LOSS_RECOVERY=1 turns it off. DX9 is
    // untouched: discovery ends without hooks when the D3D11 renderer never
    // loads.
    void InitializeD3D11DeviceLossRecovery();
}
