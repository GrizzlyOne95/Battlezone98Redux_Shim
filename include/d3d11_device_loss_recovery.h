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

    // How many devices have replaced a removed one this process. Features
    // that hold raw D3D11 objects (views, shader identities) compare it per
    // frame and rebuild when it moves. Stays 0 when recovery is off.
    unsigned D3D11DeviceRecoveryCount();

    // Ends the game because device-loss recovery cannot give it a working
    // renderer: logs "[DX11 Recovery] FAIL-CLOSED: <reason>" to the shim log
    // and the crash log, then terminates the process without running DLL
    // teardown over the broken renderer. See d3d11_recovery_policy.h.
    [[noreturn]] void D3D11RecoveryFailClosed(const char* reason);
}
