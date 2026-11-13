#pragma once
#include "contextual_hud_policy.h"

namespace BZROpenShim::ContextualHud
{
    bool ReloadConfig();
    const char* UnavailableReason();
    void Tick();
    void ResetMission() noexcept;
    bool ResourceDrawAdaptersNeeded() noexcept;
    float BeginDraw(Group group) noexcept;
    void EndDraw(float previous) noexcept;
    // Direct radar grid geometry bypasses the normal sprite/fill color helpers.
    float RadarDrawOpacity() noexcept;
    // External presentation lease. Adapters suppress only the claimed native
    // draws and bypass OpenShim styling/fading, while command input stays native.
    uint32_t ExternalOwnership() noexcept;
    bool ExternallyOwned(Group group) noexcept;
    uint32_t SetExternalOwnership(uint32_t mask);

    // Post-draw seam on the stock command panel. This file owns its render
    // slot (HudFadeCommandRenderSlot, 0x00877E68) for every feature: the
    // wrapper goes in only when the command fade, an EXU command claim or a
    // registered callback needs it, and only while the slot holds the stock
    // renderer. The callback runs on the frame thread right after the stock
    // render, inside the fade scope (native sprite/fill/text colours are
    // already scaled by `opacity`) and inside SEH; it is not called while EXU
    // owns the command presentation. One consumer. Returns true once the
    // wrapper is in the slot; false (and the callback is not kept) when the
    // build or slot ownership does not match or another callback holds it.
    using CommandPanelPostDraw = void (*)(void* controlPanel, float opacity);
    bool RegisterCommandPanelPostDraw(CommandPanelPostDraw callback);

    // Passive observer on the stock weapon-list backdrop submit
    // (HudFadeWeaponPlate). It shares the WeaponPlate adapter the fade uses,
    // so installing it here and from Install() is idempotent, and with fading
    // off the adapter forwards the stock call unchanged. Frame thread only.
    bool InstallWeaponListAnchor();
    // The backdrop's last submitted screen rectangle (x, y, width, height)
    // when it was drawn within maxAgeMs; false otherwise.
    bool WeaponListRect(uint64_t maxAgeMs, int& x, int& y, int& w, int& h) noexcept;
}
