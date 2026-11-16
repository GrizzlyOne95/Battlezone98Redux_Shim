// ogre_entity_liveness.h
//
// Shared engine-memory walk from a GameObject's OBJ76 to its root
// Ogre::Entity, and the proof that the live SceneManager still owns that
// Entity. Moved verbatim out of gpu_skinning.cpp so the localized damage
// scorch (local_damage.cpp) walks the same roots under the same proofs.
// The pure decisions stay in live_object_gate.h (host-tested); this layer
// does the guarded reads and the OgreMain calls.
#pragma once

#include <cstdint>
#include <unordered_map>

namespace BZROpenShim::OgreEntityLiveness
{
    // Resolves the three OgreMain exports the liveness proof calls
    // (MovableObject::getName, SceneManager::hasEntity/getEntity). Idempotent.
    bool Available();

    // The direct bridge root at OBJ76+0xF0, and the legacy owner (+0x8C)'s
    // +0xF0; either may come back null.
    void ReadBridgeRoots(const uint8_t* obj76, void*& directRoot, void*& ownerRoot);

    // Whether a pointer read out of engine memory is an Ogre::Entity, checked
    // so that junk raises no fault (vtable, COL and TypeDescriptor all in
    // OgreMain, RTTI name ".?AVEntity@Ogre@@").
    bool IsOgreEntityObject(const void* entity);

    // An Entity pointer read out of engine memory is acted on only while the
    // live SceneManager maps its name back to it.
    bool EntityProvenLive(void* sceneManager, void* entity);

    // Bridge root -> proof verdict, one cache per feature. Only a proven root
    // (its +0x94 held an Ogre::Entity) is read every frame, under SEH alone;
    // an unproven root is proven when first seen and on prove passes
    // (LiveObjectGate::BridgeRootAction). PruneUnseen drops roots not
    // resolved in `frame`.
    class RootEntityCache
    {
    public:
        void* Resolve(void* root, uint32_t frame, bool provePass);
        void PruneUnseen(uint32_t frame);
        void Clear() { m_probes.clear(); }

    private:
        struct RootProbe
        {
            bool proven = false;
            uint32_t seenFrame = 0;
        };
        std::unordered_map<void*, RootProbe> m_probes;
    };
}
