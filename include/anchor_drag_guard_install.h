#pragma once
// Installer for the AnchorRocket drag guard. See anchor_drag_guard.h.

namespace BZROpenShim
{
    namespace AnchorDrag
    {
        // Redirects the two drag compares in AnchorRocket::Simulate to
        // guarded thunks. Fail-closed: any byte-guard mismatch leaves the
        // engine untouched. Safe to call repeatedly.
        void InstallAnchorDragGuardIfPossible();
    }
}
