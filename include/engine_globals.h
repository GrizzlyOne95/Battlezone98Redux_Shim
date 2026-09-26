#pragma once
// engine_globals.h
// BZR Open Shim - engine data globals, resolved through scripts/patches.json.
//
// Each accessor returns the live address of one engine global, found by the
// matching "resolves" entry (mode abs32_operand: the address is read out of a
// code site known to use the global), or 0 when it cannot be resolved. Callers
// stand down on 0. A successful lookup is kept for the process; a failed one is
// retried at most once a second, so a per-frame caller never rescans.
#include <cstdint>

namespace BZROpenShim
{
    namespace EngineGlobals
    {
        // First slot of the GameObject pool: 0x1000 slots of 0x400 bytes;
        // slot = handle >> 20. patches.json "GameObject::Arena".
        uintptr_t GameObjectArena();

        // GameObject::userObject, the local player's GameObject* slot.
        // patches.json "GameObject::userObject".
        uintptr_t UserObjectSlot();

        // The renderer's globals pointer slot; the structure it points at
        // carries the SceneManager at +0x08 and the Ogre log at +0x28.
        // patches.json "RenderGlobals".
        uintptr_t RenderGlobals();

        // The current TRN path, a char array the terrain loader fills.
        // patches.json "CurrentTrnName".
        uintptr_t CurrentTrnName();
    }
}
