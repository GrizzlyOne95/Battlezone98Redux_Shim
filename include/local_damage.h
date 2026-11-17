#pragma once
// Localized damage scorch ([LocalDamage] in openshim.ini, Docs/LOCAL_DAMAGE.md).
// Render-only: weapon hits on craft leave char and cooling embers on the
// hull, drawn by the DX11 Enhanced object shader through Ogre Renderable
// custom parameters 1400..1410. Never writes gameplay, sim or network state.
#include <cstdint>

namespace BZROpenShim::LocalDamage
{
    // Copied out of the craft DamageAlloc call before the original runs.
    // Values only once AfterCraftDamage returns; no pointer is kept.
    struct CraftCapture
    {
        void* object = nullptr;  // complete GameObject; null = nothing to record
        int handle = 0;
        uint8_t kind = 0;        // 1 bullet (Ordnance::Hit), 2 explosion splash
        double point[3] = {};    // sim world
        float direction[3] = {}; // sim world, toward the target
        float before = 0.0f;     // health ratio (complete+0x200)
    };

    // [LocalDamage] Enabled, read once and again at each mission start.
    // HudFeedback installs the shared DamageAlloc adapters while this holds.
    bool WantsDamage();

    // Craft DamageAlloc adapter (hud_feedback.cpp DamageHook<1>), sim thread.
    // Fixed storage only: no heap, no Ogre calls.
    CraftCapture BeforeCraftDamage(void* receiver, void* damage, uint32_t argument, uintptr_t returnAddress) noexcept;
    void AfterCraftDamage(const CraftCapture& capture) noexcept;
}

namespace BZROpenShim
{
    // World render-queue hook (bzr_hooks.cpp): starts the feature at the
    // first world render of a mission and installs its frame listener once.
    void LocalDamageRenderFrameTick();
    void LocalDamageNotifyMissionRunStateChanged(bool running);
    void LocalDamageNotifySceneEntitiesDestroyed();
    void LocalDamageSetSceneTeardownSeam(bool installed);
}
