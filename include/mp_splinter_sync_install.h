#pragma once

namespace BZROpenShim
{
    namespace SplinterSync
    {
        void InstallSplinterSyncIfPossible();

        // True once installed and enabled. Hooks that need a network game
        // to behave like single player (the SplinterUndead gate) read this.
        bool IsActive();

        // SprayBomb::Hit's GameObjectClass::Build call (0x005DB37F), reached
        // through the Splinter Emitter Owner Propagation wrapper.
        // callerFrame is SprayBomb::Hit's EBP; the SprayBomb is at
        // callerFrame - 0x1B0. All three are cdecl, SEH-safe, and return at
        // once when sync is inactive.
        void __cdecl BeforeDeployBuild(void* matrix, void* callerFrame);
        void __cdecl AfterDeployBuild(void* building, void* callerFrame);

        // A deployed SprayBuilding is dead from damage (flags & 0x01000000).
        // Broadcasts the kill once per building.
        void __cdecl OnSplinterDead(void* sprayBuilding);
    }
}
