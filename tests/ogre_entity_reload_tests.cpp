#include "ogre_entity_reload.h"
#include "test_check.h"
#include <cstdio>
#include <stdexcept>
#include <vector>

using namespace BZROpenShim::OgreEntityReload;
using OpenShimTest::Require;

namespace
{
    struct CpuObject { bool alive = true; };
    struct Fixture
    {
        CpuObject skeleton, animations, matrices, worldMatrices;
        CpuObject newSkeleton, newAnimations, newMatrices, newWorldMatrices;
        std::uint32_t frame = 42, newFrame = 123;
        AnimationOwnership live{&skeleton, &animations, &matrices, &worldMatrices, &frame, 3};
        std::vector<void*> freed;
        bool initialised = true;
        unsigned hardwareRebuilds = 0;

        void Destroy(const AnimationOwnership& state)
        {
            for (void* object : {state.skeleton, state.animationStates,
                               state.boneMatrices, state.boneWorldMatrices})
            {
                if (!object) continue;
                auto* cpu = static_cast<CpuObject*>(object);
                Require(cpu->alive, "CPU object was destroyed twice");
                cpu->alive = false;
                freed.push_back(object);
            }
            if (state.frameBonesLastUpdated) freed.push_back(state.frameBonesLastUpdated);
        }

        template<class Rebuild> void Preserve(Rebuild rebuild)
        {
            RebuildPreservingAnimation([this] { return live; },
                [this](const AnimationOwnership& state) { live = state; },
                rebuild, [this](const AnimationOwnership& state) { Destroy(state); });
        }

        void CheckRetained() const
        {
            Require(skeleton.alive && animations.alive && matrices.alive && worldMatrices.alive,
                "BZR cached CPU objects must survive the rebuild");
            Require(live.skeleton == &skeleton && live.animationStates == &animations &&
                live.boneMatrices == &matrices && live.boneWorldMatrices == &worldMatrices &&
                live.frameBonesLastUpdated == &frame && live.numBoneMatrices == 3,
                "all retained CPU ownership must return to the entity");
            Require(frame == UINT32_MAX, "retained matrices must be refreshed on the next frame");
        }

        void StockRebuild()
        {
            // Model _deinitialise deleting whatever ownership it sees. This
            // would kill BZR's cached pointers without the transaction.
            Destroy(live);
            ++hardwareRebuilds;
            live = {&newSkeleton, &newAnimations, &newMatrices, &newWorldMatrices, &newFrame, 3};
        }
    };

    void TestSuccessfulReload()
    {
        Fixture f;
        f.Preserve([&f] { f.StockRebuild(); });
        f.CheckRetained();
        Require(f.hardwareRebuilds == 1, "stock hardware/subentity rebuilding must still run");
        Require(!f.newSkeleton.alive && !f.newAnimations.alive && !f.newMatrices.alive &&
            !f.newWorldMatrices.alive && f.freed.size() == 5,
            "temporary CPU allocations must be disposed exactly once");
        f.Destroy(f.live); // eventual normal entity destruction
        Require(!f.skeleton.alive && !f.animations.alive && f.freed.size() == 10,
            "normal teardown must still own and destroy retained CPU state");
    }

    void TestExceptionUnwind()
    {
        Fixture f;
        bool propagated = false;
        try
        {
            f.Preserve([&f]
            {
                f.initialised = false;
                f.live.skeleton = &f.newSkeleton; // partial _initialise
                throw std::runtime_error("resource load failed");
            });
        }
        catch (const std::runtime_error&) { propagated = true; }
        Require(propagated && !f.initialised, "stock rebuild errors must propagate unchanged");
        f.CheckRetained();
        Require(!f.newSkeleton.alive && f.freed.size() == 1,
            "partial CPU allocation must be released on unwind");
    }

    void TestRepeatedSuccessfulReload()
    {
        Fixture f;
        for (unsigned n = 0; n != 600; ++n)
        {
            // Simulate fresh allocations reusing the same freed addresses.
            f.newSkeleton.alive = f.newAnimations.alive = true;
            f.newMatrices.alive = f.newWorldMatrices.alive = true;
            f.Preserve([&f] { f.StockRebuild(); });
            f.CheckRetained();
        }
        Require(f.hardwareRebuilds == 600 && f.freed.size() == 3000,
            "repeated successful restores must release every replacement allocation");
        f.Destroy(f.live);
        Require(!f.skeleton.alive && !f.animations.alive,
            "normal teardown must still work after repeated restores");
    }

    void TestDeferredRetryAndRepeatedRestore()
    {
        Fixture f;
        for (unsigned n = 0; n != 600; ++n)
        {
            f.Preserve([&f] { f.initialised = false; }); // mesh load deferred
            f.CheckRetained();
            Require(f.freed.empty(), "deferred load must not free retained ownership");
        }
        f.Preserve([&f] { f.StockRebuild(); f.initialised = true; });
        f.CheckRetained();
        Require(f.initialised && f.freed.size() == 5, "deferred retry must rebuild normally");
    }

    void TestEligibility()
    {
        Fixture f;
        CpuObject master, otherMaster;
        auto allowed = [&](bool force, bool init, bool shared, bool attached,
                           const void* meshMaster, std::uint16_t instanceCount, std::uint16_t masterCount)
        {
            return CanPreserve(force, init, f.live, shared, attached,
                &master, meshMaster, instanceCount, masterCount);
        };
        Require(allowed(true, true, false, false, &master, 3, 3), "ordinary restore must qualify");
        Require(allowed(false, false, false, false, &master, 3, 3), "retained deferred retry must qualify");
        Require(!allowed(false, true, false, false, &master, 3, 3), "normal no-op init must pass through");
        Require(!allowed(true, true, true, false, &master, 3, 3), "shared ownership must stand down");
        Require(!allowed(true, true, false, true, &master, 3, 3), "TagPoint attachments must stand down");
        Require(!allowed(true, true, false, false, &otherMaster, 3, 3), "different master must stand down");
        Require(!allowed(true, true, false, false, &master, 3, 4), "changed skeleton bone count must stand down");
        Require(!allowed(true, true, false, false, &master, 4, 4), "matrix count mismatch must stand down");
        f.live.frameBonesLastUpdated = nullptr;
        Require(!allowed(true, true, false, false, &master, 3, 3), "incomplete CPU ownership must stand down");
        f.live = {};
        Require(!allowed(true, false, false, false, &master, 3, 3), "first creation must pass through");
    }
}

int main()
{
    TestSuccessfulReload();
    TestExceptionUnwind();
    TestRepeatedSuccessfulReload();
    TestDeferredRetryAndRepeatedRestore();
    TestEligibility();
    std::puts("Ogre entity reload ownership tests passed.");
}
