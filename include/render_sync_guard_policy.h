#pragma once
// Pure decision for the render-sync vtable guard (render_sync_guard.cpp).
//
// Stock FUN_00680BD0 (render-node sync, void __cdecl(renderData*)) reads the
// SceneNode at renderData+0x98 and the Ogre::Entity at renderData+0x94. When
// the node is non-null it calls node->setOrientation (+0x24) and
// node->setPosition (+0x2C), then entity->setVisibilityFlags (+0xC8) with no
// check on the entity. A destroyed Entity keeps its ShadowCaster base vtable
// after the destructor runs, so slot 0xC8 lands on data and the game crashes.
//
// The guard calls the stock function only when the objects it is about to
// call are what they should be. With a null node the stock function either
// does nothing or builds a fresh entity and node (renderData+0x74 set), so a
// null node always goes to the stock path.

#include <cstdint>

namespace BZROpenShim
{
    namespace RenderSyncGuard
    {
        enum class Verdict : uint8_t
        {
            CallStock,
            SkipUnreadable, // renderData or one of its vptrs could not be read
            SkipNullEntity, // node set, entity null: stock would call through null
            SkipDeadEntity, // entity vptrs are not Ogre::Entity's
            SkipDeadNode,   // node vptr is not Ogre::SceneNode's
        };

        struct Observed
        {
            bool readOk = false;     // renderData +0x94/+0x98 and the vptrs read without a fault
            uintptr_t node = 0;      // renderData+0x98
            uintptr_t entity = 0;    // renderData+0x94
            bool nodeLive = false;   // node vptr is SceneNode's (or a SceneNode subclass)
            bool entityLive = false; // entity primary vptr is Ogre::Entity's (exact)
        };

        inline Verdict Decide(const Observed& o)
        {
            if (!o.readOk)
                return Verdict::SkipUnreadable;
            if (o.node == 0)
                return Verdict::CallStock;
            if (!o.nodeLive)
                return Verdict::SkipDeadNode;
            if (o.entity == 0)
                return Verdict::SkipNullEntity;
            if (!o.entityLive)
                return Verdict::SkipDeadEntity;
            return Verdict::CallStock;
        }

        inline const char* VerdictName(Verdict v)
        {
            switch (v)
            {
            case Verdict::CallStock: return "call-stock";
            case Verdict::SkipUnreadable: return "unreadable";
            case Verdict::SkipNullEntity: return "null-entity";
            case Verdict::SkipDeadEntity: return "dead-entity";
            case Verdict::SkipDeadNode: return "dead-node";
            }
            return "?";
        }

        // Small set of render-data pointers already logged, so a dead object
        // that is synced every frame logs once. Fixed size; when full, the
        // caller stops logging (the total budget runs out first anyway).
        template <unsigned N>
        struct SeenSet
        {
            uintptr_t items[N] = {};
            unsigned count = 0;

            // True the first time `p` is offered (and records it).
            bool FirstTime(uintptr_t p)
            {
                for (unsigned i = 0; i < count; ++i)
                    if (items[i] == p)
                        return false;
                if (count >= N)
                    return false;
                items[count++] = p;
                return true;
            }
        };
    }
}
