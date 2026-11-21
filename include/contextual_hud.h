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

    // Render scope on the same slot and wrapper, for a consumer that must
    // change engine state the stock render reads and put it back after.
    // `before` runs on the frame thread just before the stock render
    // (outside the fade scope, also while EXU owns the presentation) and
    // returns true when it changed something; `after` then runs from the
    // wrapper's __finally, so also when a fault unwinds through the stock
    // render. Both run inside SEH. One consumer; same return rules as
    // RegisterCommandPanelPostDraw.
    using CommandPanelBeforeRender = bool (*)(void* controlPanel);
    using CommandPanelAfterRender = void (*)(void* controlPanel);
    bool RegisterCommandPanelRenderScope(CommandPanelBeforeRender before, CommandPanelAfterRender after);

    // Post-draw seam on the stock cockpit radar, same shape as the command
    // one. This file owns the radar render slot (HudFadeRadarRenderSlot) for
    // every feature: the wrapper goes in when the radar fade or a registered
    // callback needs it, and only while the slot holds the stock renderer. The
    // callback runs on the frame thread right after the stock render (inside
    // the fade scope when the fade is on; `opacity` is then the fade opacity,
    // else 1) and inside SEH. It is skipped while the radar is hidden, in the
    // alternate layout, or while EXU owns the radar presentation. `radar` is
    // the CockpitRadar. One consumer; same return rules as
    // RegisterCommandPanelPostDraw.
    using RadarPostDraw = void (*)(void* radar, float opacity);
    bool RegisterRadarPostDraw(RadarPostDraw callback);

    // Passive observer on the stock weapon-list backdrop submit
    // (HudFadeWeaponPlate). It shares the WeaponPlate adapter the fade uses,
    // so installing it here and from Install() is idempotent, and with fading
    // off the adapter forwards the stock call unchanged. Frame thread only.
    bool InstallWeaponListAnchor();
    // The backdrop's last submitted screen rectangle (x, y, width, height)
    // when it was drawn within maxAgeMs; false otherwise.
    bool WeaponListRect(uint64_t maxAgeMs, int& x, int& y, int& w, int& h) noexcept;

    // Producer-damage wake for the command fade. True while the command fade
    // is on and the producer rows bound; HudFeedback then keeps its damage
    // adapters installed. NoteDamage takes the complete victim object before
    // the native damage call; it only reads, and returns at once when off.
    bool WantsProductionDamage() noexcept;
    void NoteDamage(const void* victim) noexcept;
}
