#include "contextual_hud.h"
#include "BZROpenShim.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "game_state.h"
#include "patcher.h"
#include "shim_log.h"
#include <Windows.h>
#include <atomic>
#include <cstdlib>
#include <string>

namespace BZROpenShim::ContextualHud
{
    namespace
    {
        using namespace Hooks;
        using Color = uint32_t(__cdecl*)(uint32_t, uint32_t);
        using Text = void(__cdecl*)(void*, int, int, float*, float*, const char*, void*, uint32_t, int, int, int, int);
        using Font = void(__cdecl*)(void*, void*, int, int, const char*);
        using Sprite = void(__cdecl*)(void*, int, int, int, uint32_t, float);
        using SizedSprite = void(__cdecl*)(void*, void*, int, int, int, int, int, uint32_t, float);
        using Current = void*(__cdecl*)();
        using Value = uint32_t(__thiscall*)(void*);
        using Pointer = void*(__thiscall*)(void*);
        using Weapon = void*(__thiscall*)(void*, int);
        using Handle = int(__thiscall*)(void*);

        SRWLOCK g_lock = SRWLOCK_INIT;
        Settings g_settings;
        State g_state;
        bool g_read = false;
        std::atomic<bool> g_ready{false}, g_resources{false};
        std::atomic<float> g_opacity[kGroups] = {1,1,1};
        thread_local float g_drawOpacity = 1;
        uint64_t g_retry = 0;
        uint32_t g_color[2]{}, g_text = 0, g_font = 0, g_sprite = 0, g_sizedSprite = 0;
        uint32_t g_getTeam = 0, g_getPlayer = 0, g_values[4]{}, g_carrier = 0, g_selected = 0, g_linkable = 0, g_ammo = 0, g_weapon = 0;
        uint32_t g_sites[7]{};
        InlineDetour32 g_detours[2]{};
        std::atomic<uintptr_t> g_originalColor[2]{};

        template<size_t Index>
        uint32_t __cdecl ColorHook(uint32_t a, uint32_t b)
        {
            auto address = g_originalColor[Index].load(std::memory_order_acquire);
            while (!address) { YieldProcessor(); address = g_originalColor[Index].load(std::memory_order_acquire); }
            return ScaleAlpha(reinterpret_cast<Color>(address)(a,b), g_drawOpacity);
        }

        template<Group Role>
        void __cdecl TextDraw(void* v, int x, int y, float* w, float* h, const char* text,
            void* font, uint32_t color, int background, int mode, int alignX, int alignY)
        {
            const float previous = BeginDraw(Role);
            __try { reinterpret_cast<Text>(g_text)(v,x,y,w,h,text,font,color,background,mode,alignX,alignY); }
            __finally { EndDraw(previous); }
        }
        void __cdecl WeaponText(void* font, void* v, int x, int y, const char* text)
        {
            const float previous = BeginDraw(Group::Weapons);
            __try { reinterpret_cast<Font>(g_font)(font,v,x,y,text); }
            __finally { EndDraw(previous); }
        }
        void __cdecl WeaponIcon(void* v, int id, int x, int y, uint32_t flags, float scale)
        {
            const float previous = BeginDraw(Group::Weapons);
            __try { reinterpret_cast<Sprite>(g_sprite)(v,id,x,y,flags,scale); }
            __finally { EndDraw(previous); }
        }
        void __cdecl WeaponPlate(void* v, void* material, int id, int x, int y, int w, int h, uint32_t flags, float z)
        {
            const float previous = BeginDraw(Group::Weapons);
            __try { reinterpret_cast<SizedSprite>(g_sizedSprite)(v,material,id,x,y,w,h,flags,z); }
            __finally { EndDraw(previous); }
        }

        bool Install()
        {
            if (g_ready.load(std::memory_order_acquire)) return true;
            static int bound = 0;
            if (!bound)
            {
                const HookEngine::EngineRow rows[] = {
                    {"HudFadeColorSprite",&g_color[0]}, {"HudFadeColorFill",&g_color[1]},
                    {"HudFadeText",&g_text}, {"HudFadeFont",&g_font},
                    {"HudFeedbackSprite",&g_sprite}, {"HudSpriteSubmit",&g_sizedSprite},
                    {"HudFadeGetTeam",&g_getTeam}, {"HudFadeGetPlayer",&g_getPlayer},
                    {"HudFadeGetScrap",&g_values[0]}, {"HudFadeGetMaxScrap",&g_values[1]},
                    {"HudFadeGetPilots",&g_values[2]}, {"HudFadeGetMaxPilots",&g_values[3]},
                    {"HudFadeGetCarrier",&g_carrier}, {"HudFadeGetSelected",&g_selected},
                    {"HudFadeGetLinkable",&g_linkable}, {"HudFadeGetAmmo",&g_ammo}, {"HudFadeGetWeapon",&g_weapon},
                    {"HudFadeScrapTitle",&g_sites[0]}, {"HudFadeScrapValue",&g_sites[1]},
                    {"HudFadePilotTitle",&g_sites[2]}, {"HudFadePilotValue",&g_sites[3]},
                    {"HudFadeWeaponPlate",&g_sites[4]}, {"HudFadeWeaponIcon",&g_sites[5]}, {"HudFadeWeaponText",&g_sites[6]},
                };
                bound = HookEngine::BindEngineRows("Contextual HUD", rows) ? 1 : -1;
            }
            if (bound < 0) return false;
            ResolveLocalPlayerLookupForVerifiedGogBuild();
            if (!g_GameObjectGetHandleAddr || !g_BzrFn_GetPlayerHandle) return false;
            // Both native mode-to-ARGB helpers start with ten whole, relocatable
            // bytes. Context lives only around the seven owned draw calls and
            // existing scrap/pilot plate adapters. All other draws pass through.
            static const uint8_t expected[2][10] = {
                {0x55,0x8B,0xEC,0x51,0x8B,0x45,0x08,0x83,0xE0,0x07},
                {0x55,0x8B,0xEC,0x51,0x8B,0x45,0x0C,0x83,0xE0,0x07},
            };
            void* const hooks[] = {reinterpret_cast<void*>(ColorHook<0>), reinterpret_cast<void*>(ColorHook<1>)};
            for (size_t i = 0; i < 2; ++i)
            {
                if (!InstallInlineDetour32(g_detours[i],g_color[i],hooks[i],10,expected[i],10)) return false;
                g_originalColor[i].store(reinterpret_cast<uintptr_t>(g_detours[i].trampoline),std::memory_order_release);
            }
            bool ok = true;
            ok = RedirectCallTarget(g_sites[0],g_text,reinterpret_cast<uintptr_t>(TextDraw<Group::Scrap>)) && ok;
            ok = RedirectCallTarget(g_sites[1],g_text,reinterpret_cast<uintptr_t>(TextDraw<Group::Scrap>)) && ok;
            ok = RedirectCallTarget(g_sites[2],g_text,reinterpret_cast<uintptr_t>(TextDraw<Group::Pilots>)) && ok;
            ok = RedirectCallTarget(g_sites[3],g_text,reinterpret_cast<uintptr_t>(TextDraw<Group::Pilots>)) && ok;
            ok = RedirectCallTarget(g_sites[4],g_sizedSprite,reinterpret_cast<uintptr_t>(WeaponPlate)) && ok;
            ok = RedirectCallTarget(g_sites[5],g_sprite,reinterpret_cast<uintptr_t>(WeaponIcon)) && ok;
            ok = RedirectCallTarget(g_sites[6],g_font,reinterpret_cast<uintptr_t>(WeaponText)) && ok;
            g_ready.store(ok,std::memory_order_release);
            if (ok) Log(L"[HUDFADE] Scoped weapon-list and scrap/pilot draw adapters installed\n");
            return ok;
        }

        bool Snapshot(uint64_t& identity, std::array<uint64_t,kGroups>& values) noexcept
        {
            __try
            {
                void* player = reinterpret_cast<Current>(g_getPlayer)();
                void* team = reinterpret_cast<Current>(g_getTeam)();
                if (!player || !team) return false;
                const int handle = reinterpret_cast<Handle>(g_GameObjectGetHandleAddr)(player);
                if (!handle || g_BzrFn_GetPlayerHandle() != handle || GameObjectFromHandleGog(handle) != player) return false;
                const int number = *reinterpret_cast<const int*>(static_cast<const uint8_t*>(player) + ObjectLayout::kGameObjectActualTeam);
                if (number < 0 || number >= 16) return false;
                identity = (static_cast<uint64_t>(static_cast<uint32_t>(handle)) << 32) | static_cast<uint32_t>(number + 1);
                uint32_t resources[4]{};
                for (size_t i = 0; i < 4; ++i)
                {
                    resources[i] = reinterpret_cast<Value>(g_values[i])(team);
                    if (resources[i] > 100000000u) return false;
                }
                values[1] = (static_cast<uint64_t>(resources[0]) << 32) | resources[1];
                values[2] = (static_cast<uint64_t>(resources[2]) << 32) | resources[3];
                void* carrier = reinterpret_cast<Pointer>(g_carrier)(player);
                const uint32_t ammo = reinterpret_cast<Value>(g_ammo)(player);
                // Hash copied loadout identities only; never retain or later
                // dereference a weapon/carrier pointer from a preceding frame.
                uint64_t weaponState = ammo;
                const auto mix = [&](uintptr_t value) { weaponState = (weaponState ^ value) * 1099511628211ull; };
                if (carrier)
                {
                    mix(reinterpret_cast<Value>(g_selected)(carrier));
                    mix(reinterpret_cast<Value>(g_linkable)(carrier));
                    for (int slot = 0; slot < 5; ++slot)
                        mix(reinterpret_cast<uintptr_t>(reinterpret_cast<Weapon>(g_weapon)(carrier,slot)));
                }
                values[0] = weaponState;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        int Integer(const std::string& key, int fallback, int low, int high)
        {
            std::string value;
            if (!TryGetUserConfigString("Display",key.c_str(),value)) return fallback;
            char* end = nullptr;
            const long number = std::strtol(value.c_str(),&end,10);
            return end == value.c_str() || *end || number < low || number > high ? fallback : static_cast<int>(number);
        }
    }

    bool ResourceDrawAdaptersNeeded() noexcept { return g_ready.load(std::memory_order_acquire) && g_resources.load(std::memory_order_relaxed); }
    float BeginDraw(Group group) noexcept
    {
        const float previous = g_drawOpacity;
        if (g_ready.load(std::memory_order_acquire) && static_cast<size_t>(group) < kGroups)
            g_drawOpacity *= g_opacity[static_cast<size_t>(group)].load(std::memory_order_relaxed);
        return previous;
    }
    void EndDraw(float previous) noexcept { g_drawOpacity = previous; }
    void ResetMission() noexcept
    {
        AcquireSRWLockExclusive(&g_lock); g_state.Reset(); ReleaseSRWLockExclusive(&g_lock);
        for (auto& opacity : g_opacity) opacity.store(1,std::memory_order_relaxed);
    }
    bool ReloadConfig()
    {
        Settings settings;
        const char* prefixes[] = {"WeaponList", "ScrapHud", "PilotHud"};
        for (size_t i = 0; i < kGroups; ++i)
        {
            auto& group = settings.groups[i];
            const std::string prefix = prefixes[i];
            TryGetUserConfigBool("Display",(prefix + "Fade").c_str(),group.enabled);
            group.idlePercent = Integer(prefix + "IdleOpacity",25,0,100);
            group.delayMs = Integer(prefix + "FadeDelay",2500,0,30000);
            group.fadeMs = Integer(prefix + "FadeDuration",500,0,5000);
        }
        AcquireSRWLockExclusive(&g_lock); g_settings = settings; g_state.Reset(); ReleaseSRWLockExclusive(&g_lock);
        for (auto& opacity : g_opacity) opacity.store(1,std::memory_order_relaxed);
        g_read = true;
        g_resources.store(settings.groups[1].enabled || settings.groups[2].enabled,std::memory_order_relaxed);
        if (!settings.Active()) { RefreshScrapPilotHudLayout(); return true; }
        if (g_IsSteamExe || !IsCompatibleGameVersion()) return false;
        const bool installed = Install();
        RefreshScrapPilotHudLayout();
        return installed;
    }
    const char* UnavailableReason()
    {
        return g_IsSteamExe || !IsCompatibleGameVersion() ? "Unavailable: HUD fading currently requires qualified GOG 2.2.301." : nullptr;
    }
    void Tick()
    {
        if (!g_read) { ReloadConfig(); return; }
        Settings settings;
        AcquireSRWLockShared(&g_lock); settings = g_settings; ReleaseSRWLockShared(&g_lock);
        if (!settings.Active() || g_IsSteamExe || !IsCompatibleGameVersion()) return;
        const uint64_t now = GetTickCount64();
        if (!g_ready.load(std::memory_order_acquire))
        {
            if (now < g_retry) return;
            g_retry = now + 1000;
            if (!Install()) return;
            RefreshScrapPilotHudLayout();
        }
        uint64_t owner = 0;
        std::array<uint64_t,kGroups> values{};
        const auto ui = ReadShellUiState();
        if (!ui.readable || ui.wrapperActive || ui.screenPresent || !Snapshot(owner,values)) { ResetMission(); return; }
        AcquireSRWLockExclusive(&g_lock);
        g_state.Observe(owner,values,now);
        for (size_t i = 0; i < kGroups; ++i)
            g_opacity[i].store(g_state.groups[i].Opacity(settings.groups[i],now),std::memory_order_relaxed);
        ReleaseSRWLockExclusive(&g_lock);
    }
}
