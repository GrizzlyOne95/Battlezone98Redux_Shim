#include "weapon_presentation.h"
#include "test_check.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace WP = BZROpenShim::WeaponPresentation;
namespace WC = BZROpenShim::WeaponConvergence;
using OpenShimTest::Require;

namespace
{
    const WP::Identity owner = { 0x10000, 1 };
    const WP::Identity node = { 0x20000, 1 };

    void Near(double value, double expected, const char* message)
    {
        Require(std::fabs(value - expected) < 0.00001, message);
    }

    struct FakeBackend final : WP::Backend
    {
        struct Renderer
        {
            void** backReference = nullptr;
            WP::Matrix pose = WC::Identity();
            bool detached = false;
        };
        std::deque<Renderer> renderers;
        std::vector<WP::Matrix> recoilPoses;
        std::string lastEffect;
        int creates = 0;
        int updates = 0;
        int detaches = 0;
        bool failDetach = false;
        bool failCreate = false;
        bool failUpdate = false;
        bool failRecoil = false;

        bool CreateFlash(std::string_view effect, const WP::Matrix& pose,
            void*& storage) noexcept override
        {
            ++creates;
            lastEffect = effect;
            renderers.push_back({ &storage, pose, false });
            storage = &renderers.back();
            return !failCreate; // test failure AFTER native pointer assignment
        }

        bool UpdateFlash(void* renderer, const WP::Matrix& pose) noexcept override
        {
            ++updates;
            if (failUpdate)
                return false;
            static_cast<Renderer*>(renderer)->pose = pose;
            return true;
        }

        bool DetachFlash(void*& storage) noexcept override
        {
            ++detaches;
            if (failDetach)
                return false;
            auto* renderer = static_cast<Renderer*>(storage);
            Require(renderer->backReference == &storage,
                "native back-reference address changed while attached");
            renderer->backReference = nullptr;
            renderer->detached = true;
            storage = nullptr;
            return true;
        }

        bool ApplyRecoil(const WP::Identity&, const WP::Identity&,
            const WP::Matrix& pose) noexcept override
        {
            if (failRecoil)
                return false;
            recoilPoses.push_back(pose);
            return true;
        }

        void SelfExpire(size_t index)
        {
            auto& renderer = renderers[index];
            Require(renderer.backReference != nullptr, "expiry missing native back-reference");
            *renderer.backReference = nullptr;
            renderer.backReference = nullptr;
        }
    };

    WP::BindRequest Request(uintptr_t weapon = 0x30000, uint64_t lifetime = 1)
    {
        WP::BindRequest request;
        request.owner = owner;
        request.weapon = { weapon, lifetime };
        request.flash = { "fxdemo.Flash", 0.05f };
        WP::Matrix rest = WC::Identity();
        rest.positionX = 4.0;
        rest.positionY = 5.0;
        rest.positionZ = 6.0;
        request.recoil = WP::RecoilBinding{ node, rest };
        return request;
    }

    void Start(WP::Runtime& runtime, bool flash = true, bool recoil = true)
    {
        runtime.Configure({ flash, recoil });
        runtime.SetSession(true, true);
    }

    WP::BindingToken Bind(WP::Runtime& runtime, const WP::BindRequest& request = Request())
    {
        const auto result = runtime.Bind(request);
        Require(result.has_value(), "expected weapon binding to succeed");
        return *result;
    }

    void Finish(WP::Runtime& runtime, FakeBackend& backend)
    {
        runtime.SetSession(false, false);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 0, "test left a native attachment alive");
        runtime.InvalidateResources();
    }

    void TestConfigurationAndIds()
    {
        const WP::FlashConfig parent = { "CaseSensitive/Flash", 0.07f };
        const auto inherited = WP::ResolveFlashConfig(parent, std::nullopt, std::nullopt);
        Require(inherited.Valid() && inherited.effect == parent.effect,
            "inheritance lost case-sensitive effect reference");
        Near(inherited.duration, 0.07, "inheritance lost flash duration");
        const auto changed = WP::ResolveFlashConfig(parent, "other.Flash", std::nullopt);
        Require(changed.effect == "other.Flash", "explicit name override was ignored");
        Near(changed.duration, 0.07, "name override lost inherited duration");
        Require(!WP::ResolveFlashConfig(parent, "", std::nullopt).Valid(),
            "empty effect did not explicitly disable flash");
        Require(!WP::ResolveFlashConfig(parent, std::string_view{}, std::nullopt).Valid(),
            "empty default string view did not disable flash");
        for (float duration : { 0.0f, -1.0f, std::numeric_limits<float>::infinity(),
            std::numeric_limits<float>::quiet_NaN() })
        {
            Require(!WP::ResolveFlashConfig(parent, std::nullopt, duration).Valid(),
                "invalid duration silently inherited an enabled flash");
        }
        Require(!WP::ResolveFlashConfig({}, "fxdemo.Flash", std::nullopt).Valid(),
            "invented a missing root flash duration");
        Require(!WP::FlashConfig{ std::string("a\0b", 3), 0.1f }.Valid(),
            "embedded null was accepted as an effect reference");
        Require(WP::ParseMeshId("recoil1").has_value(), "valid mesh ID rejected");
        Require(WP::ParseMeshId("12345678").has_value(), "eight-byte ID rejected");
        for (const auto value : { "", "recoil_test", "bad id", "bad\n" })
            Require(!WP::ParseMeshId(value).has_value(), "invalid mesh ID truncated/accepted");
    }

    bool ReadNode(uintptr_t address, WP::MeshNodeView& result, void* user)
    {
        const auto& graph = *static_cast<std::map<uintptr_t, WP::MeshNodeView>*>(user);
        const auto it = graph.find(address);
        if (it == graph.end())
            return false;
        result = it->second;
        return true;
    }

    void TestBoundedMeshLookup()
    {
        const auto wanted = *WP::ParseMeshId("recoil1");
        std::map<uintptr_t, WP::MeshNodeView> graph = {
            { 1, { *WP::ParseMeshId("root"), 2, 0 } },
            { 2, { wanted, 0, 3 } },
            { 3, { *WP::ParseMeshId("turret"), 0, 0 } }
        };
        const auto found = WP::FindMeshNode(1, wanted, ReadNode, &graph);
        Require(found.status == WP::MeshLookupStatus::Found && found.node == 2,
            "mesh lookup missed child/sibling hierarchy");
        Require(WP::FindMeshNode(1, wanted, ReadNode, &graph, 2).status ==
            WP::MeshLookupStatus::LimitExceeded, "accepted a partial bounded graph");
        graph[3].id = wanted;
        Require(WP::FindMeshNode(1, wanted, ReadNode, &graph).status ==
            WP::MeshLookupStatus::Ambiguous, "duplicate mesh IDs selected arbitrary node");
        graph[3].id = *WP::ParseMeshId("turret");
        graph[3].child = 1;
        Require(WP::FindMeshNode(1, wanted, ReadNode, &graph).status ==
            WP::MeshLookupStatus::InvalidGraph, "cyclic graph did not fail closed");
        graph[3].child = 99;
        Require(WP::FindMeshNode(1, wanted, ReadNode, &graph).status ==
            WP::MeshLookupStatus::InvalidGraph, "unreadable graph accepted early match");
    }

    void TestOptInAndSessionGates()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        runtime.SetSession(true, true);
        Require(!runtime.Bind(Request()), "default settings enabled presentation");
        runtime.Configure({ true, true });
        auto unconfigured = Request();
        unconfigured.flash = {};
        unconfigured.recoil.reset();
        Require(!runtime.Bind(unconfigured), "stock content with no effect configuration was bound");
        runtime.SetSession(false, true);
        Require(!runtime.Bind(Request()), "network/unknown session permitted binding");
        runtime.SetSession(true, false);
        Require(!runtime.Bind(Request()), "inactive mission permitted binding");
        runtime.SetSession(true, true);
        const auto token = Bind(runtime);
        Require(runtime.Fire(token, 1, WC::Identity()).observed, "SP shot not observed");
        runtime.SynchronizeVisuals(backend);
        runtime.SetSession(false, true);
        Require(!runtime.Fire(token, 2, WC::Identity()).observed, "MP transition admitted shot");
        Require(!runtime.BeginSimulationStep(1, 0.01f), "MP transition admitted simulation");
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().bindings == 0 && runtime.Inspect().nativeAttachments == 0,
            "MP transition retained active visuals");
        runtime.SetSession(true, true);
        Require(!runtime.Fire(token, 3, WC::Identity()).observed, "old epoch token revived in SP");
        Finish(runtime, backend);
    }

    void TestAcceptedShotPoseAndDeduplication()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        WP::Matrix actualShot = WC::Identity();
        actualShot.positionX = 123.0;
        actualShot.positionY = -6.0;
        actualShot.positionZ = 789.0;
        const WP::Matrix preservedShot = actualShot;
        Require(runtime.BeginSimulationStep(1, 0.02f), "simulation entry rejected");
        const auto shot = runtime.Fire(token, 10, actualShot);
        Require(shot.observed && shot.flashStarted && shot.recoilReset,
            "accepted shot did not schedule effects");
        Require(backend.creates == 0 && backend.recoilPoses.empty(),
            "native renderer called inside firing context");
        Require(!runtime.Fire(token, 10, actualShot).observed,
            "same logical shot/pellet was observed twice");
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 1, "render phase did not create flash");
        Require(std::memcmp(&backend.renderers[0].pose, &actualShot, sizeof(actualShot)) == 0,
            "flash lost final factory pose/pitch composition");
        Require(std::memcmp(&actualShot, &preservedShot, sizeof(actualShot)) == 0,
            "presentation changed the gameplay firing matrix");
        WP::Matrix invalid = actualShot;
        invalid.positionX = std::numeric_limits<double>::quiet_NaN();
        Require(!runtime.Fire(token, 11, invalid).observed, "nonfinite shot matrix accepted");
        Require(runtime.Fire(token, 11, actualShot).observed,
            "invalid shot consumed the logical serial");
        // Tick-entry-before-Fire preserves the newly accepted duration.
        runtime.BeginSimulationStep(2, 0.04f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.detaches == 0, "new flash lost a dt from before its firing event");
        runtime.BeginSimulationStep(3, 0.011f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.detaches == 1, "flash did not expire at simulation deadline");
        Finish(runtime, backend);
    }

    void TestNoFlashRestartAndFollowPose()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        runtime.BeginSimulationStep(1, 0.03f);
        Require(!runtime.Fire(token, 2, WC::Identity()).flashStarted,
            "active flash restarted on rapid fire");
        WP::Matrix followed = WC::Identity();
        followed.positionZ = 42.0;
        Require(runtime.SetMuzzlePose(token, followed), "moving muzzle pose rejected");
        runtime.SynchronizeVisuals(backend);
        Near(backend.renderers[0].pose.positionZ, 42.0, "active flash did not follow muzzle");
        runtime.BeginSimulationStep(2, 0.021f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.detaches == 1 && backend.creates == 1,
            "rapid fire extended lifetime or allocated overlapping renderer");
        Require(runtime.Fire(token, 3, followed).flashStarted,
            "new shot after expiry could not create flash");
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 2, "next flash missing after expiry");
        Finish(runtime, backend);
    }

    void TestPendingFlashCannotRestartOrOutliveSimulation()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.BeginSimulationStep(1, 0.03f);
        Require(!runtime.Fire(token, 2, WC::Identity()).flashStarted,
            "render latency let pending flash reset its deadline");
        runtime.BeginSimulationStep(2, 0.03f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 0, "expired pending flash appeared late");
        Finish(runtime, backend);
    }

    void TestSharedRecoilAndLiveLocalAxis()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        auto request = Request();
        const auto left = Bind(runtime, request);
        request.weapon.address += 8;
        const auto right = Bind(runtime, request);
        Require(runtime.Inspect().sharedRecoilNodes == 1, "linked slots duplicated recoil controller");
        runtime.Fire(left, 1, WC::Identity());
        runtime.Fire(right, 1, WC::Identity());
        Near(runtime.RecoilDisplacement(owner, node), -0.6, "linked shots accumulated kick");
        runtime.BeginSimulationStep(1, 0.05f);
        Require(!runtime.BeginSimulationStep(1, 0.05f), "duplicate pass advanced state twice");
        Near(runtime.RecoilDisplacement(owner, node), -0.45, "shared node recovered per weapon");

        WP::Matrix rotated = request.recoil->unrecoiledPose;
        rotated.rightX = 0.0f;
        rotated.rightZ = -1.0f;
        rotated.frontX = 1.0f;
        rotated.frontZ = 0.0f;
        const WP::Matrix nativePose = rotated;
        Require(runtime.SetRecoilPose(owner, node, rotated), "valid live local rotation rejected");
        runtime.SynchronizeVisuals(backend);
        Near(backend.recoilPoses.back().positionX, 3.55, "recoil used captured/world axis");
        Near(backend.recoilPoses.back().positionY, 5.0, "recoil moved orthogonal axis");
        Near(backend.recoilPoses.back().positionZ, 6.0, "recoil moved world Z instead of local axis");
        Require(std::memcmp(&rotated, &nativePose, sizeof(rotated)) == 0,
            "recoil mutated gameplay node matrix");
        rotated.positionX -= 0.45;
        Require(!runtime.SetRecoilPose(owner, node, rotated), "displaced pose recaptured as baseline");

        runtime.Release(left);
        Require(runtime.Inspect().sharedRecoilNodes == 1, "released one slot destroyed shared node");
        runtime.Fire(right, 2, WC::Identity());
        runtime.BeginSimulationStep(2, 1.0f);
        runtime.SynchronizeVisuals(backend);
        Near(runtime.RecoilDisplacement(owner, node), 0.0, "large dt overshot rest");
        Near(backend.recoilPoses.back().positionX, 4.0, "recoil did not restore baseline");
        Finish(runtime, backend);
    }

    void TestFrameRateAndPauseIndependence()
    {
        for (int renderFrames : { 1, 4, 12 })
        {
            FakeBackend backend;
            WP::Runtime runtime;
            Start(runtime);
            const auto token = Bind(runtime);
            runtime.Fire(token, 1, WC::Identity());
            runtime.SynchronizeVisuals(backend);
            for (int step = 1; step <= 10; ++step)
            {
                runtime.BeginSimulationStep(static_cast<uint64_t>(step), 0.02f);
                for (int frame = 0; frame < renderFrames; ++frame)
                    runtime.SynchronizeVisuals(backend);
                if (step == 1)
                {
                    // Hundreds of rendered frames during a paused simulation
                    // cannot alter remaining seconds or recoil displacement.
                    const float pausedDisplacement = runtime.RecoilDisplacement(owner, node);
                    for (int frame = 0; frame < 200; ++frame)
                        runtime.SynchronizeVisuals(backend);
                    Near(runtime.RecoilDisplacement(owner, node), pausedDisplacement,
                        "render frames advanced paused recoil");
                    Require(backend.detaches == 0, "render frames expired paused flash");
                    Require(!runtime.BeginSimulationStep(99, -0.1f), "negative dt accepted");
                    Require(!runtime.BeginSimulationStep(99,
                        std::numeric_limits<float>::quiet_NaN()), "NaN dt accepted");
                }
            }
            Near(runtime.RecoilDisplacement(owner, node), 0.0, "return time depended on render FPS");
            Require(backend.creates == 1 && backend.detaches == 1,
                "flash lifetime depended on render FPS");
            Finish(runtime, backend);
        }
    }

    void TestStableBackReferenceAndFailedDetach()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        void** const nativeSlot = backend.renderers[0].backReference;
        for (uintptr_t i = 1; i <= 128; ++i)
            Bind(runtime, Request(0x30000 + i * 8));
        Require(backend.renderers[0].backReference == nativeSlot && *nativeSlot,
            "growing binding table relocated native renderer pointer slot");

        backend.failDetach = true;
        runtime.Release(token);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().retiredBindings == 1 && *nativeSlot,
            "failed detach freed/forgot live native pointer storage");
        backend.SelfExpire(0);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().retiredBindings == 0,
            "native self-expiry did not release retained pointer storage");
        backend.failDetach = false;
        Finish(runtime, backend);
    }

    void TestSelfExpiryAndFactoryFailure()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        backend.SelfExpire(0);
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 1 && backend.detaches == 0,
            "self-expired native renderer was recreated or detached through stale pointer");
        runtime.Fire(token, 2, WC::Identity());
        backend.failCreate = true;
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 1, "partial factory failure lost back-reference");
        runtime.SynchronizeVisuals(backend);
        Require(backend.detaches == 1 && runtime.Inspect().nativeAttachments == 0,
            "partial factory failure did not queue safe detach");
        backend.failCreate = false;
        runtime.Fire(token, 3, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        backend.failUpdate = true;
        runtime.SetMuzzlePose(token, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 0, "failed pose update retained active renderer");
        Finish(runtime, backend);
    }

    void TestPointerReuseReplacementAndRestorationRetry()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime, false, true);
        const auto old = Bind(runtime);
        Require(!runtime.Bind(Request(0x30000, 2)),
            "new lifetime reused an address while old binding was still active");
        runtime.Fire(old, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        runtime.Release(old);
        backend.failRecoil = true;
        runtime.SynchronizeVisuals(backend);
        Require(!runtime.Bind(Request(0x30000, 2)), "rebound node before visual restoration succeeded");
        backend.failRecoil = false;
        runtime.SynchronizeVisuals(backend);
        const auto replacement = Bind(runtime, Request(0x30000, 2));
        Require(!runtime.Fire(old, 2, WC::Identity()).observed, "recycled address accepted old binding token");
        Require(runtime.Fire(replacement, 1, WC::Identity()).recoilReset,
            "replacement inherited old shot serial or failed to bind");
        Finish(runtime, backend);
    }

    void TestNestedSceneLossAndSettingsDisable()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        runtime.Configure({ false, false });
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 0, "disabling settings did not detach flash");
        Near(backend.recoilPoses.back().positionZ, 6.0, "disabling settings did not restore recoil");
        runtime.Configure({ true, true });
        Require(!runtime.Fire(token, 2, WC::Identity()).observed,
            "disabling all presentation settings did not retire binding tokens");
        const auto rebound = Bind(runtime);
        runtime.Fire(rebound, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        backend.failDetach = true;
        void** const slot = backend.renderers.back().backReference;
        runtime.BeginSceneTeardown();
        runtime.SynchronizeVisuals(backend);
        runtime.BeginSceneTeardown();
        runtime.SynchronizeVisuals(backend);
        runtime.EndSceneTeardown();
        Require(runtime.Inspect().nativeAttachments == 1 && *slot,
            "nested scene teardown freed pointer storage before outer native return");
        Require(!runtime.Bind(Request(0x40000)), "scene destruction admitted binding");
        // Native destruction invalidates the renderer before the outer return.
        backend.SelfExpire(backend.renderers.size() - 1);
        runtime.EndSceneTeardown();
        const auto clean = runtime.Inspect();
        Require(clean.bindings == 0 && clean.retiredBindings == 0 && clean.sharedRecoilNodes == 0,
            "outer scene completion retained stale presentation identities");
        Require(!runtime.Fire(token, 3, WC::Identity()).observed, "scene-loss epoch did not reject stale shot");
        backend.failDetach = false;
        Finish(runtime, backend);
    }

    void TestOgreSceneLossDoesNotEndNativeBackReferences()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        const auto token = Bind(runtime);
        runtime.Fire(token, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        void** const slot = backend.renderers[0].backReference;
        backend.failDetach = true;
        runtime.BeginSceneTeardown();
        runtime.SynchronizeVisuals(backend);
        runtime.EndSceneTeardown();
        Require(runtime.Inspect().nativeAttachments == 1 && *slot,
            "Ogre teardown assumed native ParticleRender back-reference ended");
        Require(runtime.Inspect().sharedRecoilNodes == 0,
            "destroyed scene retained obsolete presentation pose restoration");
        // A later native destructor still has a live, stable address to clear.
        backend.SelfExpire(0);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().retiredBindings == 0,
            "late native destructor did not release retained slot");
        backend.failDetach = false;
        Finish(runtime, backend);
    }

    void TestInvalidRecoilDoesNotDisableValidFlash()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime);
        auto request = Request();
        request.recoil->unrecoiledPose.frontX = 1.0f;
        request.recoil->unrecoiledPose.frontZ = 0.0f; // duplicate right row
        const auto token = Bind(runtime, request);
        const auto shot = runtime.Fire(token, 1, WC::Identity());
        Require(shot.flashStarted && !shot.recoilReset,
            "invalid recoil node suppressed independent valid flash or was accepted");
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 1 && backend.recoilPoses.empty(),
            "invalid recoil fallback invoked incorrect backend calls");
        Finish(runtime, backend);
    }
}

int main()
{
    TestConfigurationAndIds();
    TestBoundedMeshLookup();
    TestOptInAndSessionGates();
    TestAcceptedShotPoseAndDeduplication();
    TestNoFlashRestartAndFollowPose();
    TestPendingFlashCannotRestartOrOutliveSimulation();
    TestSharedRecoilAndLiveLocalAxis();
    TestFrameRateAndPauseIndependence();
    TestStableBackReferenceAndFailedDetach();
    TestSelfExpiryAndFactoryFailure();
    TestPointerReuseReplacementAndRestorationRetry();
    TestNestedSceneLossAndSettingsDisable();
    TestOgreSceneLossDoesNotEndNativeBackReferences();
    TestInvalidRecoilDoesNotDisableValidFlash();
    std::puts("weapon_presentation_tests: all checks passed");
    return 0;
}
