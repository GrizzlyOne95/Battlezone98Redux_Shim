#pragma once

namespace BZROpenShim
{
    namespace SplinterPayloadLocal
    {
        void InstallSplinterPayloadLocalIfPossible();

        // True when `bomb` is a recorded payload: a SprayBomb, BounceBomb or
        // Popper this peer's own SprayBuilding fired in a network game (or the
        // child of such a Popper) and still under the key and owner it was
        // built with. Always false while the fix is not installed. Game thread.
        bool IsLocalPayload(const void* bomb);
    }
}
