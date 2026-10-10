#pragma once

#include <cstdint>

namespace BZROpenShim::OgreEntityReload
{
    // CPU ownership only. Vertex data, subentities and hardware buffers remain
    // entirely under Entity::_initialise/_deinitialise's control.
    struct AnimationOwnership
    {
        void* skeleton = nullptr;
        void* animationStates = nullptr;
        void* boneMatrices = nullptr;
        void* boneWorldMatrices = nullptr;
        std::uint32_t* frameBonesLastUpdated = nullptr;
        std::uint16_t numBoneMatrices = 0;
    };

    inline bool CanPreserve(bool force, bool initialised,
                            const AnimationOwnership& state,
                            bool sharedSkeleton, bool attachedObjects,
                            const void* instanceMaster, const void* meshMaster,
                            std::uint16_t instanceBones, std::uint16_t masterBones)
    {
        // A normal already-initialised call is Ogre's no-op. A deferred/failed
        // rebuild may have retained this ownership while initialised is false.
        return (force || !initialised) && state.skeleton &&
            state.animationStates && state.boneMatrices &&
            state.frameBonesLastUpdated && !sharedSkeleton && !attachedObjects &&
            instanceMaster && instanceMaster == meshMaster && instanceBones != 0 &&
            instanceBones == masterBones && instanceBones == state.numBoneMatrices;
    }

    // read/write/destroy must not throw. Restore ownership during C++ exception
    // unwinding as well as normal and deferred-load returns. Never catch an AV
    // and continue with an entity whose rebuild may be half complete.
    template<class Read, class Write, class Rebuild, class Destroy>
    void RebuildPreservingAnimation(Read read, Write write,
                                   Rebuild rebuild, Destroy destroy)
    {
        const AnimationOwnership saved = read();
        struct Restore
        {
            Read& read;
            Write& write;
            Destroy& destroy;
            const AnimationOwnership& saved;
            ~Restore() noexcept
            {
                destroy(read());
                write(saved);
                *saved.frameBonesLastUpdated = UINT32_MAX;
            }
        } restore{read, write, destroy, saved};
        write(AnimationOwnership{});
        rebuild();
    }
}
