#include "weapon_presentation.h"
#include "weapon_presentation_native_policy.h"
#include "odf_flash_bridge.h"
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
        struct AnimationCall { float time; bool active; };
        std::vector<AnimationCall> animationCalls;
        bool failAnimation = false;
        int meshCreates = 0, meshCancels = 0;
        bool failMeshCreate = false, failMeshCancel = false;
        WP::FlashConfig meshConfig;
        WP::Matrix meshPose = WC::Identity();
        float meshLifetime = 0;
        bool CreateMeshFlash(const WP::FlashConfig& config, const WP::Identity& flashOwner,
            const WP::Matrix& pose, float lifetime, WP::MeshFlashToken& token) noexcept override
        {
            Require(flashOwner == owner, "wrong mesh flash owner");
            ++meshCreates; meshConfig = config; meshPose = pose; meshLifetime = lifetime;
            token = {static_cast<uint32_t>(100 + meshCreates), static_cast<uint64_t>(meshCreates)};
            return !failMeshCreate;
        }
        bool CancelMeshFlash(WP::MeshFlashToken& token) noexcept override
        {
            Require(token.id >= 101 && token.cookie != 0, "invalid pool token cancelled");
            ++meshCancels;
            if (failMeshCancel) return false;
            token = {}; return true;
        }
        bool ApplyAnimation(const WP::Identity&, const WP::AnimationBinding&,
            float time, bool active) noexcept override
        {
            animationCalls.push_back({time, active});
            return !failAnimation;
        }

        bool CreateFlash(std::string_view effect, const WP::Matrix& pose,
            void*& storage) noexcept override
        {
            ++creates;
            lastEffect = effect;
            renderers.push_back({ &storage, pose, false });
            storage = &renderers.back();
            return !failCreate; // test failure AFTER native pointer assignment
        }

        bool UpdateFlash(void*& renderer, const WP::Matrix& pose) noexcept override
        {
            ++updates;
            Require(static_cast<Renderer*>(renderer)->backReference == &renderer,
                "native update was passed a temporary attachment slot");
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

    void TestMeshFlashPolicyAndRuntime()
    {
        Require(BzrOdfFlashBridge::Matches(1, 42, 1, 42), "owned pool ID refused");
        Require(!BzrOdfFlashBridge::Matches(1, 43, 1, 42), "old mission cookie cancelled a reused pool ID");
        Require(!BzrOdfFlashBridge::Matches(1, 0, 1, 42), "native cancellation could target a Lua flash");
        Require(!BzrOdfFlashBridge::Matches(1, 0, 1, 0), "zero cookie claimed ownership");
        namespace Policy = WP::NativePolicy;
        Policy::MeshFlashFields fields;
        fields.mesh = "\"MyFlash.mesh\"";
        auto config = Policy::ResolveMeshFlashConfig({}, fields);
        Require(config.Valid() && config.mesh == "MyFlash.mesh" && config.material.empty(), "mesh-only defaults failed");
        Near(config.duration, 0.08, "default flash lifetime wrong");
        fields.material = "\"Custom/Flash\"";
        fields.scale = "2"; fields.endScale = "0"; fields.offset = "\"1 2 3\""; fields.roll = "-45";
        config = Policy::ResolveMeshFlashConfig({}, fields);
        Require(config.Valid() && config.material == "Custom/Flash", "custom mesh config refused");
        Near(config.finishScale, 0, "shrink-to-zero refused");
        auto inherited = Policy::ResolveMeshFlashConfig(config, {});
        Require(inherited.mesh == config.mesh && inherited.material == config.material && inherited.offset.z == 3,
            "mesh settings not inherited");
        Policy::MeshFlashFields override;
        override.material = "\"\"";
        Require(Policy::ResolveMeshFlashConfig(config, override).material.empty(), "mesh material not explicitly cleared");
        override.mesh = "\"\"";
        Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "empty mesh did not opt out");
        override = {}; override.offset = "1 2 3 4";
        Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "extra offset component accepted");
        for (const auto bad : {"1 2", "1,2,3", "1 2 NaN", "21 0 0", "1 2 3suffix", "\"bad"})
        {
            override.offset = bad;
            Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "invalid flash offset accepted");
        }
        override = {};
        for (const auto bad : {"0", "-1", "5.01", "nan", "0.1suffix"})
        {
            override.duration = bad;
            Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "invalid flash lifetime accepted");
        }
        override = {}; override.scale = "101";
        Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "oversized mesh flash accepted");
        override = {}; override.roll = "361";
        Require(!Policy::ResolveMeshFlashConfig(config, override).Valid(), "unbounded flash roll accepted");

        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime, true, false);
        auto request = Request(); request.recoil.reset(); request.flash = config;
        auto token = Bind(runtime, request);
        auto pose = WC::Identity();
        pose.rightX = 0; pose.rightZ = -1; pose.frontX = 1; pose.frontZ = 0;
        pose.positionX = 10; pose.positionY = 20; pose.positionZ = 30;
        const auto original = pose;
        Require(runtime.Fire(token, 1, pose).flashStarted, "mesh flash shot ignored");
        runtime.SetMuzzlePose(token, pose); // native refresh must retain the authored offset
        runtime.BeginSimulationStep(1, 0.02f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.meshCreates == 1 && backend.creates == 0, "mesh flash used legacy native renderer");
        Near(backend.meshLifetime, 0.06, "pending mesh flash lifetime restarted at render");
        Near(backend.meshPose.positionX, 13, "offset did not follow muzzle front");
        Near(backend.meshPose.positionY, 22, "offset did not follow muzzle up");
        Near(backend.meshPose.positionZ, 29, "offset did not follow muzzle right");
        Require(std::memcmp(&pose, &original, sizeof(pose)) == 0, "flash offset changed projectile pose");
        Require(!runtime.Fire(token, 2, pose).flashStarted, "active mesh flash restarted");
        runtime.BeginSimulationStep(2, 0);
        runtime.SynchronizeVisuals(backend);
        Require(backend.meshCreates == 1, "paused frame duplicated mesh flash");
        backend.failMeshCancel = true;
        runtime.SetSession(false, true);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().meshFlashAttachments == 1, "failed cancellation lost its pool id");
        backend.failMeshCancel = false;
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().meshFlashAttachments == 0 && runtime.Inspect().bindings == 0,
            "mesh flash not cancelled on MP departure");
        runtime.InvalidateResources();

        WP::Runtime delayed;
        Start(delayed, true, false);
        token = Bind(delayed, request);
        delayed.Fire(token, 1, pose);
        delayed.BeginSimulationStep(1, 0.2f);
        delayed.SynchronizeVisuals(backend);
        Require(backend.meshCreates == 1, "expired pending mesh flash appeared late");
        Finish(delayed, backend);

        WP::Runtime independent;
        Start(independent, true, true);
        request = Request(); request.flash = config;
        token = Bind(independent, request);
        backend.failMeshCreate = true;
        const auto shot = independent.Fire(token, 1, pose);
        independent.SynchronizeVisuals(backend);
        Require(shot.recoilReset && !backend.recoilPoses.empty(), "flash failure suppressed independent recoil");
        independent.SynchronizeVisuals(backend); // retire partial backend state
        Require(independent.Inspect().meshFlashAttachments == 0, "failed mesh spawn id leaked");
        Finish(independent, backend);
    }

    void TestCraftFlashOffsetOverride()
    {
        namespace Policy = WP::NativePolicy;
        const auto base = Policy::ResolveMeshFlashConfig({}, {"\"Small.mesh\"", {}, "0.05", {}, {}, "\"0 0 0\"", {}});
        Require(base.IsMesh(), "craft offset base mesh invalid");
        const auto parsed = Policy::Offset("\"0.20 0.10 2.41\"");
        Require(parsed && parsed->z == 2.41f, "craft flashOffset did not parse");
        for (const auto bad : {"1 2", "21 0 0", "1 2 3 4", "NaN 0 0", "0 0 -20.5"})
            Require(!Policy::Offset(bad), "invalid craft flashOffset accepted");

        // Defaulted render offset follows the craft override.
        auto defaulted = base;
        defaulted.muzzleRender = Policy::ResolveMuzzleRenderConfig({}, {"\"R.render\"", {}, {}}, base.offset);
        Policy::ApplyCraftFlashOffset(defaulted, true, *parsed);
        Require(defaulted.offset.z == 2.41f && defaulted.muzzleRender.offset.z == 2.41f, "craft offset missed defaulted render");

        // Explicit muzzleRenderOffset wins.
        auto explicitRender = base;
        explicitRender.muzzleRender = Policy::ResolveMuzzleRenderConfig({}, {"\"R.render\"", {}, "\"1 2 3\""}, base.offset);
        Policy::ApplyCraftFlashOffset(explicitRender, false, *parsed);
        Require(explicitRender.offset.z == 2.41f && explicitRender.muzzleRender.offset.z == 3, "craft offset overrode explicit render offset");

        // Render-only weapon: the mesh channel stays absent.
        WP::FlashConfig renderOnly;
        renderOnly.muzzleRender = Policy::ResolveMuzzleRenderConfig({}, {"\"R.render\"", {}, {}}, {});
        Policy::ApplyCraftFlashOffset(renderOnly, true, *parsed);
        Require(!renderOnly.IsMesh() && renderOnly.muzzleRender.offset.z == 2.41f, "render-only craft offset wrong");

        // The override reaches the placed flash.
        FakeBackend backend;
        WP::Runtime runtime; Start(runtime);
        auto request = Request();
        request.flash = base;
        Policy::ApplyCraftFlashOffset(request.flash, false, *parsed);
        const auto token = Bind(runtime, request);
        auto pose = WC::Identity();
        Require(runtime.Fire(token, 1, pose).flashStarted, "craft offset shot ignored");
        runtime.BeginSimulationStep(1, .02f);
        runtime.SynchronizeVisuals(backend);
        Near(backend.meshPose.positionZ, 2.41, "craft forward offset not applied to mesh flash");
        Finish(runtime, backend);
    }

    void TestMuzzleRenderAlongsideMesh()
    {
        namespace Policy = WP::NativePolicy;
        const auto render = Policy::ResolveMuzzleRenderConfig({}, {"\"MyGun.render\"", "0.20", std::nullopt}, {1, 2, 3});
        Require(render.Valid() && render.effect == "MyGun.render" && render.offset.z == 3, "render defaults/offset failed");
        Require(Policy::ResolveMuzzleRenderConfig(render, {}, {}).effect == render.effect, "render did not inherit");
        Require(!Policy::ResolveMuzzleRenderConfig(render, {"\"\"", {}, {}}, {}).Valid(), "render explicit off ignored");
        for (const auto bad : {"NaN", "0", "5.01", "0.1suffix"})
            Require(!Policy::ResolveMuzzleRenderConfig(render, {{}, bad, {}}, {}).Valid(), "bad render duration inherited");
        for (const auto bad : {"1 2", "21 0 0", "1 2 3 4", "NaN 0 0"})
            Require(!Policy::ResolveMuzzleRenderConfig(render, {{}, {}, bad}, {}).Valid(), "bad render offset inherited");
        for (const auto bad : {"\"bad", "two names", "a\nb"})
            Require(!Policy::ResolveMuzzleRenderConfig(render, {bad, {}, {}}, {}).Valid(), "bad render name accepted");

        FakeBackend backend;
        WP::Runtime runtime; Start(runtime);
        auto request = Request();
        request.flash = Policy::ResolveMeshFlashConfig({}, {"\"Small.mesh\"", {}, "0.05", {}, {}, "\"0 0 4\"", {}});
        request.flash.muzzleRender = render;
        const auto token = Bind(runtime, request);
        auto pose = WC::Identity();
        pose.rightX = 0; pose.rightZ = -1; pose.frontX = 1; pose.frontZ = 0;
        pose.positionX = 10; pose.positionY = 20; pose.positionZ = 30;
        const auto original = pose;
        Require(runtime.Fire(token, 1, pose).flashStarted, "combined shot ignored");
        runtime.BeginSimulationStep(1, .02f);
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 1 && backend.meshCreates == 1, "render and mesh did not coexist");
        Near(backend.meshLifetime, .03, "pending mesh timer restarted");
        Near(backend.meshPose.positionX, 14, "mesh offset wrong");
        Near(backend.renderers[0].pose.positionX, 13, "render forward offset wrong");
        Near(backend.renderers[0].pose.positionY, 22, "render up offset wrong");
        Near(backend.renderers[0].pose.positionZ, 29, "render right offset wrong");
        Require(std::memcmp(&pose, &original, sizeof(pose)) == 0, "render offset changed firing matrix");
        Require(!runtime.Fire(token, 1, pose).observed, "duplicate shot spawned effects");
        runtime.BeginSimulationStep(2, .04f);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 1 && runtime.Inspect().meshFlashAttachments == 0,
            "short flash cancelled longer render effect");
        Require(runtime.Fire(token, 2, pose).flashStarted, "active render blocked next short mesh flash");
        runtime.SynchronizeVisuals(backend);
        Require(backend.creates == 1 && backend.meshCreates == 2, "active render restarted with next mesh flash");
        pose.positionX = 20;
        runtime.SetMuzzlePose(token, pose);
        runtime.BeginSimulationStep(3, 0);
        runtime.SynchronizeVisuals(backend);
        Near(backend.renderers[0].pose.positionX, 23, "render did not follow refreshed muzzle");
        Require(backend.creates == 1, "pause duplicated render effect");
        backend.failDetach = true;
        runtime.BeginSimulationStep(4, .15f);
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().nativeAttachments == 1, "failed render detach freed stable slot");
        runtime.Release(token);
        runtime.BeginSceneTeardown(); runtime.EndSceneTeardown();
        Require(runtime.Inspect().retiredBindings == 1, "scene loss discarded native back-reference");
        backend.failDetach = false;
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().retiredBindings == 0, "combined cleanup failed");
        Finish(runtime, backend);

        // Render-only weapons and independent partial-failure cleanup.
        for (bool failMesh : {false, true})
        {
            WP::Runtime isolated; FakeBackend failures; Start(isolated);
            failures.failMeshCreate = failMesh; failures.failCreate = !failMesh;
            request.flash.muzzleRender = render;
            const auto bound = Bind(isolated, request);
            const auto shot = isolated.Fire(bound, 1, WC::Identity());
            Require(shot.flashStarted && shot.recoilReset, "effect failure disabled recoil");
            isolated.SynchronizeVisuals(failures);
            Require(failures.creates == 1 && failures.meshCreates == 1, "one failed effect suppressed the other");
            Finish(isolated, failures);
        }
        WP::Runtime renderOnly; FakeBackend alone; Start(renderOnly, true, false);
        request.recoil.reset(); request.flash = {}; request.flash.muzzleRender = render;
        const auto only = Bind(renderOnly, request);
        renderOnly.Fire(only, 1, WC::Identity());
        renderOnly.BeginSimulationStep(1, .21f);
        renderOnly.SynchronizeVisuals(alone);
        Require(alone.creates == 0 && alone.meshCreates == 0, "expired pending render created late");
        renderOnly.Fire(only, 2, WC::Identity()); renderOnly.SynchronizeVisuals(alone);
        Require(alone.creates == 1 && alone.meshCreates == 0, "render-only weapon failed");
        renderOnly.Configure({false, true}); renderOnly.SynchronizeVisuals(alone);
        Require(renderOnly.Inspect().nativeAttachments == 0, "settings disable retained render effect");
        Finish(renderOnly, alone);

        for (bool flashes : {false, true}) for (bool recoil : {false, true})
        {
            WP::Runtime gated; FakeBackend controlled; Start(gated, flashes, recoil);
            auto configured = Request(); configured.flash = request.flash;
            configured.flash.mesh = "Small.mesh"; configured.flash.duration = .08f;
            const auto bound = gated.Bind(configured);
            Require(bound.has_value() == (flashes || recoil), "master settings did not gate binding");
            if (bound)
            {
                const auto shot = gated.Fire(*bound, 1, WC::Identity());
                Require(shot.flashStarted == flashes && shot.recoilReset == recoil, "master settings channels crossed");
                gated.SynchronizeVisuals(controlled);
                Require(controlled.creates == (flashes ? 1 : 0) && controlled.meshCreates == (flashes ? 1 : 0),
                    "flash master switch did not gate both render channels");
                Require(controlled.recoilPoses.empty() == !recoil, "recoil master switch ignored");
            }
            Finish(gated, controlled);
        }
        WP::Runtime unauthored; Start(unauthored);
        auto stock = Request(); stock.flash = {}; stock.recoil.reset();
        Require(!unauthored.Bind(stock), "enabled settings synthesized a generic stock effect");
    }

    void TestAnimationRecoil()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime, false, true);
        auto request = Request();
        request.animation = WP::AnimationBinding{"recoil", 0.3f, 2.0f, true};
        const auto token = Bind(runtime, request);
        const auto shared = Bind(runtime, [&] { auto r = request; r.weapon.address++; return r; }());
        Require(runtime.Fire(token, 1, WC::Identity()).recoilReset, "clip shot not accepted");
        Require(!runtime.Fire(token, 1, WC::Identity()).observed, "duplicate logical shot restarted clip");
        runtime.SynchronizeVisuals(backend);
        Require(backend.animationCalls.size() == 1 && backend.animationCalls.back().active,
            "clip not started");
        Require(backend.recoilPoses.empty(), "clip and node slide both applied");
        runtime.BeginSimulationStep(1, 0.05f);
        runtime.SynchronizeVisuals(backend);
        Near(backend.animationCalls.back().time, 0.1, "clip speed or shared timing wrong");
        runtime.BeginSimulationStep(1, 0.05f);
        runtime.BeginSimulationStep(2, 0);
        runtime.SynchronizeVisuals(backend);
        Near(backend.animationCalls.back().time, 0.1, "pause/duplicate step advanced clip");
        runtime.Fire(shared, 1, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        Near(backend.animationCalls.back().time, 0, "second slot did not restart shared clip");
        runtime.BeginSimulationStep(3, 0.2f);
        runtime.SynchronizeVisuals(backend);
        Require(!backend.animationCalls.back().active, "finished clip not restored");
        runtime.Fire(token, 2, WC::Identity());
        runtime.SynchronizeVisuals(backend);
        backend.failAnimation = true;
        runtime.SetSession(false, true);
        runtime.SynchronizeVisuals(backend);
        Require(!backend.animationCalls.back().active, "MP transition did not request restoration");
        const auto attempts = backend.animationCalls.size();
        backend.failAnimation = false;
        runtime.SynchronizeVisuals(backend);
        Require(backend.animationCalls.size() == attempts + 1, "failed clip restoration not retried");
        runtime.SynchronizeVisuals(backend);
        Require(backend.animationCalls.size() == attempts + 1, "restored clip still retained");
        Require(runtime.Inspect().sharedAnimationClips == 0, "restored clip leaked a controller");
        runtime.InvalidateResources();

        WP::Runtime invalid;
        Start(invalid, false, true);
        for (float rate : {0.0f, -1.0f, 51.0f, std::numeric_limits<float>::quiet_NaN()})
        {
            request.animation->playbackRate = rate;
            Require(!invalid.Bind(request), "invalid clip fell back to node slide");
        }
        request.animation.reset();
        request.recoil->distance = 0.25f;
        request.recoil->returnSpeed = 0.5f;
        const auto slide = Bind(invalid, request);
        invalid.Fire(slide, 1, WC::Identity());
        Near(invalid.RecoilDisplacement(owner, node), -0.25, "custom distance ignored");
        invalid.BeginSimulationStep(1, 0.25f);
        Near(invalid.RecoilDisplacement(owner, node), -0.125, "custom return speed ignored");
        Finish(invalid, backend);

        WP::Runtime partial;
        Start(partial, false, true);
        request.animation = WP::AnimationBinding{"recoil", 0.3f, 1, false};
        const auto partialToken = Bind(partial, request);
        backend.failAnimation = true;
        partial.Fire(partialToken, 1, WC::Identity());
        partial.SynchronizeVisuals(backend);
        partial.Release(partialToken);
        partial.SynchronizeVisuals(backend);
        Require(!backend.animationCalls.back().active, "partial application lost restoration responsibility");
        backend.failAnimation = false;
        partial.SynchronizeVisuals(backend);
        Require(partial.Inspect().sharedAnimationClips == 0, "partial application restoration leaked");
        partial.InvalidateResources();
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

    void TestFailedRecoilRestorationRemainsBounded()
    {
        FakeBackend backend;
        WP::Runtime runtime;
        Start(runtime, false, true);
        std::vector<WP::BindingToken> tokens;
        tokens.reserve(WP::kMaxBindings);
        for (size_t i = 0; i < WP::kMaxBindings; ++i)
        {
            auto request = Request(0x100000 + i * 16);
            request.recoil->node = { 0x200000 + i * 16, 1 };
            const auto token = Bind(runtime, request);
            Require(runtime.Fire(token, 1, WC::Identity()).recoilReset,
                "capacity fixture did not request recoil");
            tokens.push_back(token);
        }
        runtime.SynchronizeVisuals(backend);
        backend.failRecoil = true;
        for (const auto token : tokens)
            Require(runtime.Release(token), "capacity fixture release failed");
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().bindings == 0 &&
            runtime.Inspect().sharedRecoilNodes == WP::kMaxBindings,
            "failed restorations did not outlive their weapon bindings");

        auto replacement = Request(0x400000);
        replacement.recoil->node = { 0x300000, 1 };
        Require(!runtime.Bind(replacement),
            "failed restoration records grew past the shared-controller cap");
        Require(runtime.Inspect().bindings == 0 &&
            runtime.Inspect().sharedRecoilNodes == WP::kMaxBindings,
            "rejected binding changed retained restoration state");
        backend.failRecoil = false;
        runtime.SynchronizeVisuals(backend);
        Require(runtime.Inspect().sharedRecoilNodes == 0,
            "successful restoration did not reclaim controller capacity");
        const auto rebound = Bind(runtime, replacement);
        Require(runtime.Fire(rebound, 1, WC::Identity()).recoilReset,
            "reclaimed controller capacity did not admit a new binding");
        runtime.SynchronizeVisuals(backend);
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
    TestMeshFlashPolicyAndRuntime();
    TestMuzzleRenderAlongsideMesh();
    TestCraftFlashOffsetOverride();
    TestAnimationRecoil();
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
    TestFailedRecoilRestorationRemainsBounded();
    TestInvalidRecoilDoesNotDisableValidFlash();
    std::puts("weapon_presentation_tests: all checks passed");
    return 0;
}
