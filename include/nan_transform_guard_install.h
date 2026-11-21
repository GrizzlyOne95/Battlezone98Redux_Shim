#pragma once
// Installer for the NaN transform guard. See nan_transform_guard.h.

namespace BZROpenShim
{
    namespace NanTransform
    {
        // Entry-detours GameObject::Simulate (0x004DEEC0). Chains over an
        // earlier OpenShim entry detour (RemoteSmoothing), so it must be
        // installed after InitializeRemoteObjectSmoothing. Fail-closed: any
        // byte-guard mismatch leaves the engine untouched. Safe to call
        // repeatedly.
        void InstallNanTransformGuardIfPossible();
    }
}
