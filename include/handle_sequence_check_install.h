#pragma once
// Installer and per-render-queue-update driver for the handle sequence check. See
// handle_sequence_check.h.

namespace BZROpenShim
{
    namespace HandleSequence
    {
        // Binds the byte-guarded sequence counter. Writes nothing to the
        // engine; any guard mismatch leaves the check off. Safe to call
        // repeatedly.
        void InstallHandleSequenceCheckIfPossible();

        // One counter read per call; logs only on a level crossing. A no-op
        // until the install succeeded. Render thread only.
        void TickHandleSequenceCheck();
    }
}
