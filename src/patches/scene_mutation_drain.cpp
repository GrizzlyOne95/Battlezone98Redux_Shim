// scene_mutation_drain.cpp
// BZR Open Shim - the once-per-frame point where scene objects that the world
// render-queue hook asked for are created and destroyed. The rationale and the
// pure gate are in include/scene_mutation_drain_policy.h.
#include "scene_mutation_drain.h"
#include "scene_mutation_drain_policy.h"
#include "bzr_hooks_internal.h"
#include "shim_log.h"
#include "fp_trap_log.h"

namespace BZROpenShim::Hooks
{
    namespace
    {
        constexpr const char* kComponent = "scenedrain";
        // Root is created long before a world renders; a few retries cover an
        // unexpected early call, after which the hook stays on the inline path
        // (the pre-drain behaviour; logged).
        constexpr int kRootAttempts = 16;

        SceneMutationDrain::Gate g_Gate;
        int g_RenderQueueHookDepth = 0;

        // Ogre::FrameListener, laid out to its 1.10 vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor (same shape as
        // gpu_skinning.cpp and ogre_render_profile.cpp). Root fires
        // frameStarted from renderOneFrame before _updateAllRenderTargets, so
        // no scene traversal is in progress.
        class SceneMutationDrainListener
        {
        public:
            virtual bool frameStarted(const void*)
            {
                // Once per frame on the main thread: the opt-in FP trap
                // logger re-arms here. One branch when it is off.
                FpTrapLogFrameTick();
                if (g_Gate.OnFrameStarted())
                    RunDeferredSceneMutations();
                return true;
            }
            virtual bool frameRenderingQueued(const void*) { return true; }
            virtual bool frameEnded(const void*) { return true; }
            virtual ~SceneMutationDrainListener() = default;
        };
        SceneMutationDrainListener g_Listener;

        void TryInstall()
        {
            static int s_attemptsLeft = kRootAttempts;
            using FnRootSingleton = void*(__cdecl*)();
            using FnAddFrameListener = void(__thiscall*)(void*, void*);
            static const auto getRoot =
                ResolveOgreProc<FnRootSingleton>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            static const auto addFrameListener = ResolveOgreProc<FnAddFrameListener>(
                "?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
            const auto unavailable = [](const char* why) {
                g_Gate.NoteUnavailable();
                LogShimA(LogLevel::Warn, kComponent,
                         "[SCENEDRAIN] frameStarted drain unavailable (%s); render-queue features keep "
                         "creating and destroying scene objects inside the traversal",
                         why);
            };
            if (!getRoot || !addFrameListener)
            {
                unavailable("Ogre Root exports missing");
                return;
            }
            void* const root = getRoot();
            if (!root)
            {
                if (--s_attemptsLeft <= 0)
                    unavailable("Ogre Root unavailable");
                return;
            }
            // Root::addFrameListener only records the listener in its pending
            // set, so this is safe from inside the traversal.
            addFrameListener(root, &g_Listener);
            g_Gate.NoteInstalled();
            LogShimA(LogLevel::Info, kComponent,
                     "[SCENEDRAIN] installed: render-queue scene mutations run at frameStarted");
        }
    }

    bool BeginRenderQueueSceneAccess() noexcept
    {
        if (g_Gate.InstallState() == SceneMutationDrain::Gate::Install::Pending)
            TryInstall();
        const SceneMutationDrain::RenderQueueDecision decision = g_Gate.OnRenderQueue();
        if (decision.reportStall)
            LogShimA(LogLevel::Warn, kComponent,
                     "[SCENEDRAIN] no frameStarted for %u render-queue calls; still deferring, the "
                     "simulation tick drains until frameStarted resumes",
                     SceneMutationDrain::kStallRenderQueueCalls);
        return decision.defer;
    }

    RenderQueueHookScope::RenderQueueHookScope() noexcept { ++g_RenderQueueHookDepth; }
    RenderQueueHookScope::~RenderQueueHookScope() { --g_RenderQueueHookDepth; }

    bool InsideRenderQueueHookWithDeferral() noexcept
    {
        return g_RenderQueueHookDepth > 0 && g_Gate.Deferring();
    }

    void NoteSceneMutationRequested() noexcept
    {
        g_Gate.OnRequest();
    }

    void RunSceneMutationFallbackDrain() noexcept
    {
        if (g_RenderQueueHookDepth == 0 && g_Gate.OnSimTick())
            RunDeferredSceneMutations();
    }

    void SceneMutationDrainSceneTeardown() noexcept
    {
        g_Gate.OnSceneTeardown();
    }
}
