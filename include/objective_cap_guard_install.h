#pragma once
// Installer for the objective list capacity guard. See objective_cap_guard.h.

namespace BZROpenShim
{
    namespace ObjectiveCap
    {
        // Inline-detours the objective list Add (0x004F39B0) so an 11th
        // objective drops the oldest one instead of writing past the array.
        // Fail-closed: any byte-guard mismatch leaves the engine untouched.
        // Safe to call repeatedly.
        void InstallObjectiveCapGuardIfPossible();
    }
}
