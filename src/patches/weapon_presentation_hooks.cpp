#include "weapon_presentation_hooks.h"
#include "weapon_presentation_native.h"
#include "bzr_hooks_internal.h"

#include <memory>

namespace BZROpenShim::Hooks
{
    namespace
    {
        std::unique_ptr<WeaponPresentation::Runtime> g_Runtime;
        WeaponPresentation::Backend* g_Backend = nullptr;

        void RefreshSessionGate() noexcept
        {
            if (!g_Runtime)
                return;
            int state = kBzrRunStateUnknown;
            const bool running = g_MissionSeamInstalled &&
                TryReadBzrRunState(state) && state == kBzrRunStateStarted;
            g_Runtime->SetSession(IsSinglePlayerSession(), running);
        }
    }

    bool RegisterQualifiedWeaponPresentationBackend(
        WeaponPresentation::Backend& backend, WeaponPresentation::Settings settings)
    {
        if (g_Runtime || (!settings.muzzleFlash && !settings.meshRecoil))
            return false;
        // Allocate only on explicit registration, never for stock content in
        // the frame/lifecycle seams. Native producer hooks must catch allocation
        // failures during binding; Fire itself copies into preallocated state.
        g_Runtime = std::make_unique<WeaponPresentation::Runtime>();
        g_Backend = &backend;
        g_Runtime->Configure(settings);
        RefreshSessionGate();
        return true;
    }

    WeaponPresentation::Runtime* TryGetSingleplayerWeaponPresentationRuntime() noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return nullptr;
        // Recheck the existing fail-closed MP gate on every producer entry,
        // rather than relying only on a cached per-render reconcile verdict.
        RefreshSessionGate();
        return g_Runtime && g_Runtime->AcceptingBindings() ? g_Runtime.get() : nullptr;
    }

    void RefreshWeaponPresentationState() noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return;
        RefreshWeaponPresentationNativePoses();
        if (!g_Runtime || !g_Backend)
            return;
        RefreshSessionGate();
        // Renderer synchronization only. dt comes from the simulation adapter.
        g_Runtime->SynchronizeVisuals(*g_Backend);
    }

    void WeaponPresentationMissionRunStateChanged(bool running) noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return;
        if (!running) RetireWeaponPresentationNativeBindings();
        if (!g_Runtime)
            return;
        g_Runtime->SetSession(IsSinglePlayerSession(), running);
        if (!running && g_Backend)
            g_Runtime->SynchronizeVisuals(*g_Backend);
    }

    void WeaponPresentationSceneTeardownBegin() noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return;
        WeaponPresentationNativeSceneBegin();
        RetireWeaponPresentationNativeBindings();
        if (!g_Runtime)
            return;
        g_Runtime->BeginSceneTeardown();
        if (g_Backend)
            g_Runtime->SynchronizeVisuals(*g_Backend);
    }

    void WeaponPresentationSceneTeardownComplete() noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return;
        if (g_Runtime)
            g_Runtime->EndSceneTeardown();
        WeaponPresentationNativeSceneComplete();
    }

    void ResetWeaponPresentationState() noexcept
    {
        if (!WeaponPresentationNativeThreadAllowed()) return;
        RetireWeaponPresentationNativeBindings();
        if (!g_Runtime)
            return;
        g_Runtime->SetSession(false, false);
        if (g_Backend)
            g_Runtime->SynchronizeVisuals(*g_Backend);
        // Keep the stable attachment slots and backend alive until cleanup is
        // acknowledged. A hook reset is not proof of native scene destruction.
    }
}
