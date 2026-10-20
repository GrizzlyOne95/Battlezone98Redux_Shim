#include "hud_palette.h"
#include "contextual_hud.h"
#include "BZROpenShim.h"
#include "hud_palette_policy.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "bzr_object_layout.h"
#include "hook_engine.h"
#include "game_state.h"
#include "patcher.h"
#include "shim_log.h"
#include <Windows.h>
#include <atomic>
#include <cstdlib>

namespace BZROpenShim::HudPalette
{
    namespace
    {
        using namespace Hooks;
        using Sprite = void(__cdecl*)(void*, void*, int, int, int, int, int, uint32_t, float);
        using Grid = void(__cdecl*)(void*, void*);
        using Gauge = void(__cdecl*)(void*, float, const int*, uint32_t, uint32_t);
        using Hull = uint32_t(__cdecl*)(float);
        using Contact = uint32_t(__thiscall*)(void*);
        using Relation = bool(__thiscall*)(void*, int);
        SRWLOCK g_lock = SRWLOCK_INIT;
        Settings g_settings;
        bool g_read = false, g_ready = false;
        std::atomic<bool> g_active{false};
        uint64_t g_retry = 0;
        uint32_t g_sprite = 0, g_grid = 0, g_gauge = 0, g_hull = 0, g_contact = 0;
        uint32_t g_tint = 0, g_spriteTable = 0, g_spriteCount = 0, g_spritePalette = 0;
        uint32_t g_friend = 0, g_enemy = 0, g_flash = 0;
        uint32_t g_ammoSites[2]{};
        bool g_ammoReady = false;

        Settings Read()
        {
            AcquireSRWLockShared(&g_lock);
            const Settings s = g_settings;
            ReleaseSRWLockShared(&g_lock);
            return s;
        }

        uint32_t __cdecl HullColor(float ratio)
        {
            const uint32_t stock = reinterpret_cast<Hull>(g_hull)(ratio);
            return Health(Read(), ratio, stock);
        }

        void __cdecl GridDraw(void* viewport, void* grid)
        {
            const auto color = Read()[Role::RadarGrid];
            uint32_t* slot = nullptr;
            uint32_t saved = 0;
            bool changed = false;
            __try
            {
                // The native radar passes its current projected grid. The
                // released grid submitter reads its color at +0x20018.
                if (color && grid)
                {
                    slot = reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(grid) + 0x20018);
                    saved = *slot;
                    *slot = KeepAlpha(saved, *color);
                    changed = true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            __try { reinterpret_cast<Grid>(g_grid)(viewport, grid); }
            __finally { if (changed) *slot = saved; }
        }

        void TintedSprite(void* viewport, void* material, int id, int x, int y, int w, int h,
                          uint32_t flags, float z, std::optional<uint32_t> color)
        {
            auto* tint = reinterpret_cast<uint32_t*>(g_tint);
            const uint32_t saved = *tint;
            if (color) { *tint = *color; flags = (flags & ~7u) | 5u; }
            __try { reinterpret_cast<Sprite>(g_sprite)(viewport, material, id, x, y, w, h, flags, z); }
            __finally { *tint = saved; }
        }

        void __cdecl AmmoSprite(void* v, void* m, int id, int x, int y, int w, int h, uint32_t f, float z)
        {
            const float previous = ContextualHud::BeginDraw(ContextualHud::Group::Ammo);
            __try { TintedSprite(v, m, id, x, y, w, h, f, z, Read()[Role::Ammo]); }
            __finally { ContextualHud::EndDraw(previous); }
        }

        void __cdecl BackgroundSprite(void* v, void* m, int id, int x, int y, int w, int h, uint32_t f, float z)
        {
            const int opacity = Read().radarBackgroundOpacity;
            std::optional<uint32_t> color;
            __try
            {
                const int count = *reinterpret_cast<const int*>(g_spriteCount);
                if (opacity >= 0 && id >= 0 && id < count && count <= 4096)
                {
                    // Same palette lookup as the stock sized-sprite submitter.
                    const auto record = g_spriteTable + static_cast<uint32_t>(id) * 0x24;
                    const uint32_t index = *reinterpret_cast<const uint32_t*>(record + 0x18) & 15u;
                    const uint32_t rgb = reinterpret_cast<const uint32_t*>(g_spritePalette)[index] & 0xFFFFFFu;
                    color = rgb | (static_cast<uint32_t>(opacity * 255 / 100) << 24);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            TintedSprite(v, m, id, x, y, w, h, f, z, color);
        }

        uint32_t __fastcall ContactColor(void* object, void*)
        {
            const uint32_t stock = reinterpret_cast<Contact>(g_contact)(object);
            const Settings s = Read();
            if (!s[Role::RadarFriendly] && !s[Role::RadarEnemy] && !s[Role::RadarNeutral]) return stock;
            uint32_t result = stock;
            __try
            {
                const auto* bytes = static_cast<const uint8_t*>(object);
                const int team = *reinterpret_cast<const int*>(bytes + ObjectLayout::kGameObjectActualTeam);
                const int perceived = *reinterpret_cast<const int*>(bytes + ObjectLayout::kGameObjectPerceivedTeam);
                // Retain native colors when identity is disguised/ambiguous.
                // Never use a hidden actual team to reveal a radar contact.
                if (team >= 0 && team < 16 && team == perceived)
                {
                    void* player = g_BzrFn_GetPlayerHandle ? GameObjectFromHandleGog(g_BzrFn_GetPlayerHandle()) : nullptr;
                    if (player)
                    {
                        Role role = Role::RadarNeutral;
                        if (reinterpret_cast<Relation>(g_enemy)(player, team)) role = Role::RadarEnemy;
                        else if (reinterpret_cast<Relation>(g_friend)(player, team)) role = Role::RadarFriendly;
                        if (s[role]) result = ContactTint(stock, *s[role]);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            return result;
        }

        template<bool UnitHealth>
        void __cdecl UnitGauge(void* v, float ratio, const int* rect, uint32_t foreground, uint32_t empty)
        {
            const Settings s = Read();
            if (std::isfinite(ratio) && ratio >= 0)
            {
                if constexpr (UnitHealth)
                {
                    // The command renderer temporarily uses a bright red
                    // damage flash instead of its normal health-state color.
                    if (foreground != *reinterpret_cast<const uint32_t*>(g_flash))
                        foreground = Health(s, ratio, foreground, true);
                }
                else foreground = s[Role::UnitAmmo].value_or(foreground);
                empty = s[Role::UnitEmpty].value_or(empty);
            }
            reinterpret_cast<Gauge>(g_gauge)(v, ratio, rect, foreground, empty);
        }

        bool Install();
    }

    bool BindAmmoDrawAdapters()
    {
        static int bound = 0;
        if (!bound)
        {
            const HookEngine::EngineRow rows[] = {
                {"HudPaletteSizedSprite",&g_sprite}, {"HudPaletteSpriteTint",&g_tint},
                {"HudPaletteAmmoLabelCall",&g_ammoSites[0]}, {"HudPaletteAmmoFillCall",&g_ammoSites[1]},
            };
            bound = HookEngine::BindEngineRows("Cockpit ammo draws",rows) ? 1 : -1;
        }
        return bound > 0;
    }
    bool InstallAmmoDrawAdapters()
    {
        if (g_ammoReady) return true;
        if (!BindAmmoDrawAdapters()) return false;
        g_ammoReady = RedirectCallTarget(g_ammoSites[0],g_sprite,reinterpret_cast<uintptr_t>(AmmoSprite)) &&
            RedirectCallTarget(g_ammoSites[1],g_sprite,reinterpret_cast<uintptr_t>(AmmoSprite));
        return g_ammoReady;
    }

    const char* UnavailableReason()
    {
        return g_IsSteamExe || !IsCompatibleGameVersion()
            ? "Unavailable: HUD colors currently require qualified GOG 2.2.301." : nullptr;
    }

    bool ReloadConfig()
    {
        std::string text;
        Settings s;
        if (TryGetUserConfigString("Display", "HudColorPreset", text)) s = Preset(text);
        for (size_t i = 0; i < Count; ++i)
            if (TryGetUserConfigString("Display", Keys[i], text))
                if (const auto color = HudColors::Parse(text)) s.colors[i] = color;
        if (TryGetUserConfigString("Display", "RadarBackgroundOpacity", text))
        {
            char* end = nullptr;
            const long value = std::strtol(text.c_str(), &end, 10);
            if (end != text.c_str() && *end == '\0' && value >= 0 && value <= 100)
                s.radarBackgroundOpacity = static_cast<int>(value);
        }
        AcquireSRWLockExclusive(&g_lock);
        g_settings = s;
        ReleaseSRWLockExclusive(&g_lock);
        g_read = true;
        g_active.store(s.Active(), std::memory_order_relaxed);
        return !s.Active() || (!UnavailableReason() && Install());
    }

    void Tick()
    {
        if (!g_read) { ReloadConfig(); return; }
        if (!g_active.load(std::memory_order_relaxed) || g_ready || UnavailableReason()) return;
        const uint64_t now = GetTickCount64();
        if (now < g_retry) return;
        g_retry = now + 1000;
        Install();
    }
    namespace
    {
        bool Install()
        {
            if (g_ready) return true;
            ResolveLocalPlayerLookupForVerifiedGogBuild();
            if (!g_BzrFn_GetPlayerHandle || !g_GameObjectGetHandleAddr) return false;
            static uint32_t sites[23] = {};
            static int bound = 0;
            if (!bound)
            {
                const HookEngine::EngineRow rows[] = {
                    {"HudPaletteGridSubmit", &g_grid},
                    {"HudPaletteGaugeSubmit", &g_gauge},
                    {"HudPaletteHullColor", &g_hull},
                    {"HudPaletteContactColor", &g_contact},
                    {"HudPaletteFriendTeam", &g_friend},
                    {"HudPaletteEnemyTeam", &g_enemy},
                    {"HudPaletteSizedSprite", &g_sprite},
                    {"HudPaletteSpriteTint", &g_tint},
                    {"HudPaletteSpriteColors", &g_spritePalette},
                    {"HudPaletteDamageFlash", &g_flash},
                    {"HudSpriteRectTable", &g_spriteTable},
                    {"HudSpriteNameCount", &g_spriteCount},
                    {"HudPaletteGridCall", &sites[0]},
                    {"HudPaletteBackgroundCall", &sites[1]},
                    {"HudPaletteContactCall", &sites[2]},
                    {"HudPaletteHullCall", &sites[3]},
                    {"HudPaletteUnitGauge00", &sites[6]},
                    {"HudPaletteUnitGauge01", &sites[7]},
                    {"HudPaletteUnitGauge02", &sites[8]},
                    {"HudPaletteUnitGauge03", &sites[9]},
                    {"HudPaletteUnitGauge04", &sites[10]},
                    {"HudPaletteUnitGauge05", &sites[11]},
                    {"HudPaletteUnitGauge06", &sites[12]},
                    {"HudPaletteUnitGauge07", &sites[13]},
                    {"HudPaletteUnitGauge08", &sites[14]},
                    {"HudPaletteUnitGauge09", &sites[15]},
                    {"HudPaletteUnitGauge10", &sites[16]},
                    {"HudPaletteUnitGauge11", &sites[17]},
                    {"HudPaletteUnitGauge12", &sites[18]},
                    {"HudPaletteUnitGauge13", &sites[19]},
                    {"HudPaletteUnitGauge14", &sites[20]},
                    {"HudPaletteUnitGauge15", &sites[21]},
                    {"HudPaletteUnitGauge16", &sites[22]},
                };
                bound = HookEngine::BindEngineRows("HUD palette", rows) ? 1 : -1;
            }
            if (bound < 0 || !BindAmmoDrawAdapters()) return false;
            bool ok = InstallAmmoDrawAdapters();
            ok = RedirectCallTarget(sites[0], g_grid, reinterpret_cast<uintptr_t>(GridDraw)) && ok;
            ok = RedirectCallTarget(sites[1], g_sprite, reinterpret_cast<uintptr_t>(BackgroundSprite)) && ok;
            ok = RedirectCallTarget(sites[2], g_contact, reinterpret_cast<uintptr_t>(ContactColor)) && ok;
            ok = RedirectCallTarget(sites[3], g_hull, reinterpret_cast<uintptr_t>(HullColor)) && ok;
            ok = RedirectCallTarget(sites[6], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[7], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[8], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[9], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[10], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[11], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[12], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[13], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[14], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[15], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[16], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[17], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[18], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[19], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[20], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<true>)) && ok;
            ok = RedirectCallTarget(sites[21], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            ok = RedirectCallTarget(sites[22], g_gauge, reinterpret_cast<uintptr_t>(UnitGauge<false>)) && ok;
            g_ready = ok;
            if (ok) Log(L"[HUDCOLORS] Radar, cockpit and command gauge adapters installed\n");
            return ok;
        }
    }

}
