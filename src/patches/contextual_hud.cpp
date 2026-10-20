#include "contextual_hud.h"
#include "hud_palette.h"
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
#include <cstring>
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
        using CommandRender = void(__thiscall*)(void*);
        using Health = float(__thiscall*)(void*);
        using Fill = void(__cdecl*)(void*, int, int, int, int, uint32_t, uint32_t);
        constexpr size_t kSafeFrameGroups = static_cast<size_t>(Group::Commands);
        constexpr size_t kCommands = static_cast<size_t>(Group::Commands);

        SRWLOCK g_lock = SRWLOCK_INIT;
        Settings g_settings;
        State g_state;
        bool g_read = false;
        std::atomic<bool> g_ready{false}, g_resources{false}, g_commandsReady{false}, g_metersReady{false};
        std::atomic<float> g_opacity[kGroups] = {1,1,1,1,1,1};
        thread_local float g_drawOpacity = 1;
        uint64_t g_retry = 0;
        uint32_t g_color[2]{}, g_text = 0, g_font = 0, g_sprite = 0, g_sizedSprite = 0;
        uint32_t g_getTeam = 0, g_getPlayer = 0, g_values[4]{}, g_carrier = 0, g_selected = 0, g_linkable = 0, g_ammo = 0, g_weapon = 0;
        uint32_t g_sites[7]{};
        InlineDetour32 g_detours[2]{};
        std::atomic<uintptr_t> g_originalColor[2]{};
        uint32_t g_commandRender = 0, g_commandSlot = 0, g_commandBindings = 0;
        uint32_t g_commandInputs = 0, g_commandMouse = 0, g_commandRects = 0, g_commandAlt = 0;
        uintptr_t g_commandInstance = 0; // Identity only; never dereferenced after a draw.
        int g_commandBound = 0;
        uint32_t g_meterRender = 0, g_meterSites[6]{}, g_maxAmmo = 0, g_health = 0, g_maxHealth = 0, g_equipped = 0, g_fill = 0;
        int g_meterBound = 0;
        struct MeterSample { bool readable = false, hullWarning = false, ammoWarning = false; uint64_t hull = 0, ammo = 0; };

        MeterSample SampleMeters(void* player, void* carrier, uint64_t weaponState, uint32_t ammo) noexcept
        {
            MeterSample sample;
            if (!g_metersReady.load(std::memory_order_acquire)) return sample;
            __try
            {
                const float health = reinterpret_cast<Health>(g_health)(player);
                const float maximum = reinterpret_cast<Health>(g_maxHealth)(player);
                const uint32_t capacity = reinterpret_cast<Value>(g_maxAmmo)(player);
                if (!std::isfinite(health) || !std::isfinite(maximum) || health < 0 || maximum <= 0 ||
                    health > 100000000 || maximum > 100000000 || ammo > 100000000u || capacity > 100000000u)
                    return sample;
                uint32_t healthBits = 0, maximumBits = 0;
                std::memcpy(&healthBits,&health,sizeof(health));
                std::memcpy(&maximumBits,&maximum,sizeof(maximum));
                sample.hull = (static_cast<uint64_t>(healthBits) << 32) | maximumBits;
                sample.hullWarning = HullWarning(health,maximum);
                std::array<uint32_t,5> costs{};
                uint32_t available = 0;
                sample.ammo = (weaponState ^ capacity) * 1099511628211ull;
                if (carrier)
                {
                    available = reinterpret_cast<Value>(g_linkable)(carrier);
                    if (available & ~31u) return {};
                    for (int slot = 0; slot < 5; ++slot)
                    {
                        void* weapon = reinterpret_cast<Weapon>(g_equipped)(carrier,slot);
                        // Same released weapon instance/cost field used by the
                        // guarded status renderer. No pointer survives the sample.
                        if (weapon) costs[slot] = *reinterpret_cast<const uint32_t*>(static_cast<const uint8_t*>(weapon) + 0xB0);
                        if (costs[slot] > 100000000u) return {};
                        sample.ammo = (sample.ammo ^ costs[slot]) * 1099511628211ull;
                    }
                }
                sample.ammoWarning = AmmoWarning(ammo,available,costs);
                sample.readable = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return {}; }
            return sample;
        }

        bool BindMeters()
        {
            if (!g_meterBound)
            {
                const HookEngine::EngineRow rows[] = {
                    {"HudFadeMeterRender",&g_meterRender},
                    {"HudFadeHullLabel",&g_meterSites[0]}, {"HudFadeHullFill",&g_meterSites[1]},
                    {"HudFadeAmmoText",&g_meterSites[2]}, {"HudFadeAmmoMark0",&g_meterSites[3]},
                    {"HudFadeAmmoMark1",&g_meterSites[4]}, {"HudFadeAmmoMark2",&g_meterSites[5]},
                    {"HudFadeMaxAmmo",&g_maxAmmo}, {"HudFadeHealth",&g_health},
                    {"HudFadeMaxHealth",&g_maxHealth}, {"HudFadeEquippedWeapon",&g_equipped}, {"HudFadeMeterFillRect",&g_fill},
                };
                g_meterBound = HookEngine::BindEngineRows("Hull/ammo HUD fading",rows) && HudPalette::BindAmmoDrawAdapters() ? 1 : -1;
            }
            return g_meterBound > 0;
        }

        struct CommandSample { uint64_t value = 0; bool interacting = false; };
        bool ReadCommandSample(void* self, CommandSample& sample) noexcept
        {
            __try
            {
                const auto* bytes = static_cast<const uint8_t*>(self);
                // The released class's render slot identifies this instance.
                // Other OpenShim features own different slots in this vtable.
                if (!self || *reinterpret_cast<const uintptr_t*>(self) + 6 * sizeof(uintptr_t) != g_commandSlot)
                    return false;
                // Touch/alternate layout uses a different interaction path;
                // leave it fully visible until that path is qualified.
                if (*reinterpret_cast<const uint8_t*>(g_commandAlt)) return false;
                const int selected = *reinterpret_cast<const int*>(bytes + 0x188);
                const int category = *reinterpret_cast<const int*>(bytes + 0x117C);
                const int navigation = *reinterpret_cast<const int*>(bytes + 0x119C);
                if (selected < 0 || selected > 91 || category < -1 || category > 10 || navigation < 0 || navigation > 3)
                    return false;
                const auto node = *reinterpret_cast<const uintptr_t*>(bytes + 0x1180);
                const bool nested = node && *reinterpret_cast<const uintptr_t*>(node) != 0;
                sample.interacting = selected > 0 || category >= 0 || navigation != 0 || nested;
                uint64_t value = static_cast<uint32_t>(category);
                const auto mix = [&](uintptr_t next) { value = (value ^ next) * 1099511628211ull; };
                mix(selected); mix(navigation); mix(node);
                for (int i = 0; i < selected; ++i)
                    mix(*reinterpret_cast<const uint32_t*>(bytes + 0x1C + i * sizeof(uint32_t)));
                sample.value = value;

                // Native action bytes cover rebinding/controller inputs too.
                // These are the thirteen row actions and ten unit-group actions
                // read by the released renderer, not physical Windows keys.
                const auto* inputs = reinterpret_cast<const uint8_t*>(g_commandInputs);
                for (size_t i = 0; i < 13; ++i)
                    sample.interacting = sample.interacting ||
                        **reinterpret_cast<const uint8_t* const*>(g_commandBindings + i * sizeof(uintptr_t)) != 0;
                for (size_t i = 0; i < 10; ++i)
                    sample.interacting = sample.interacting || inputs[0x20 + i] != 0;
                sample.interacting = sample.interacting || inputs[0x1D] != 0;

                // A world click or firing alone must not reveal the panel.
                // The native pointer action counts only inside its own rows.
                if (inputs[0])
                {
                    const auto* mouse = reinterpret_cast<const int*>(g_commandMouse);
                    const auto* rows = reinterpret_cast<const int*>(g_commandRects);
                    for (size_t i = 0; i < 13; ++i)
                        if (mouse[0] >= rows[i*4] && mouse[0] <= rows[i*4+2] &&
                            mouse[1] >= rows[i*4+1] && mouse[1] <= rows[i*4+3])
                            sample.interacting = true;
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        void UpdateCommandOpacity(void* self)
        {
            CommandSample sample;
            const bool readable = ReadCommandSample(self,sample);
            const uint64_t now = GetTickCount64();
            float opacity = 1;
            AcquireSRWLockExclusive(&g_lock);
            auto& activity = g_state.groups[kCommands];
            if (!readable || !g_state.owner || !g_settings.groups[kCommands].enabled)
            {
                activity = {};
                g_commandInstance = 0;
            }
            else
            {
                const uintptr_t instance = reinterpret_cast<uintptr_t>(self);
                if (instance != g_commandInstance) { activity = {}; g_commandInstance = instance; }
                activity.Observe(sample.value,now,sample.interacting);
                opacity = activity.Opacity(g_settings.groups[kCommands],now);
            }
            ReleaseSRWLockExclusive(&g_lock);
            g_opacity[kCommands].store(opacity,std::memory_order_relaxed);
        }

        void __fastcall CommandDraw(void* self, void*)
        {
            if (g_commandsReady.load(std::memory_order_acquire)) UpdateCommandOpacity(self);
            const float previous = BeginDraw(Group::Commands);
            // Rendering also processes native command input, selection and
            // menu sounds. Always execute it, including when alpha is zero.
            __try { reinterpret_cast<CommandRender>(g_commandRender)(self); }
            __finally { EndDraw(previous); }
        }

        bool BindCommand()
        {
            if (!g_commandBound)
            {
                const HookEngine::EngineRow rows[] = {
                    {"HudFadeCommandRender",&g_commandRender}, {"HudFadeCommandRenderSlot",&g_commandSlot},
                    {"HudFadeCommandBindings",&g_commandBindings}, {"HudFadeCommandInputs",&g_commandInputs},
                    {"HudFadeCommandMouse",&g_commandMouse}, {"CommandMenuRowRects",&g_commandRects},
                    {"CommandMenuAltLayoutFlag",&g_commandAlt},
                };
                g_commandBound = HookEngine::BindEngineRows("Command HUD fading",rows) ? 1 : -1;
                if (g_commandBound > 0)
                {
                    uint32_t target = 0;
                    SIZE_T read = 0;
                    if (!ReadProcessMemory(GetCurrentProcess(),reinterpret_cast<const void*>(g_commandSlot),
                        &target,sizeof(target),&read) || read != sizeof(target) || target != g_commandRender)
                    {
                        g_commandBound = -1;
                        Log(L"[HUDFADE] Command interface stands down: render slot ownership differs\n");
                    }
                }
            }
            return g_commandBound > 0;
        }

        bool InstallCommand()
        {
            if (g_commandsReady.load(std::memory_order_acquire)) return true;
            if (!BindCommand()) return false;
            HookEngine::CodePatchLock lock;
            const uint32_t hook = reinterpret_cast<uint32_t>(CommandDraw);
            uint32_t current = 0;
            SIZE_T read = 0;
            if (!ReadProcessMemory(GetCurrentProcess(),reinterpret_cast<const void*>(g_commandSlot),
                &current,sizeof(current),&read) || read != sizeof(current) || current != g_commandRender)
                return false;
            if (!WritePatchBytes(g_commandSlot,reinterpret_cast<const uint8_t*>(&hook),sizeof(hook))) return false;
            g_commandsReady.store(true,std::memory_order_release);
            Log(L"[HUDFADE] Command interface sprite/text scope installed\n");
            return true;
        }

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

        void __cdecl HullSprite(void* v, void* material, int id, int x, int y, int w, int h, uint32_t flags, float z)
        {
            const float previous = BeginDraw(Group::Hull);
            __try { reinterpret_cast<SizedSprite>(g_sizedSprite)(v,material,id,x,y,w,h,flags,z); }
            __finally { EndDraw(previous); }
        }
        void __cdecl AmmoText(void* font, void* v, int x, int y, const char* text)
        {
            const float previous = BeginDraw(Group::Ammo);
            __try { reinterpret_cast<Font>(g_font)(font,v,x,y,text); }
            __finally { EndDraw(previous); }
        }
        void __cdecl AmmoMark(void* v, int x1, int y1, int x2, int y2, uint32_t color, uint32_t mode)
        {
            const float previous = BeginDraw(Group::Ammo);
            __try { reinterpret_cast<Fill>(g_fill)(v,x1,y1,x2,y2,color,mode); }
            __finally { EndDraw(previous); }
        }
        bool InstallMeters()
        {
            if (g_metersReady.load(std::memory_order_acquire)) return true;
            if (!BindMeters()) return false;
            bool ok = HudPalette::InstallAmmoDrawAdapters();
            ok = RedirectCallTarget(g_meterSites[0],g_sizedSprite,reinterpret_cast<uintptr_t>(HullSprite)) && ok;
            ok = RedirectCallTarget(g_meterSites[1],g_sizedSprite,reinterpret_cast<uintptr_t>(HullSprite)) && ok;
            ok = RedirectCallTarget(g_meterSites[2],g_font,reinterpret_cast<uintptr_t>(AmmoText)) && ok;
            for (size_t i = 3; i < 6; ++i)
                ok = RedirectCallTarget(g_meterSites[i],g_fill,reinterpret_cast<uintptr_t>(AmmoMark)) && ok;
            g_metersReady.store(ok,std::memory_order_release);
            if (ok) Log(L"[HUDFADE] Hull/ammo sprite, shots-text and cost-marker scopes installed\n");
            return ok;
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

        bool InstallForSettings(const Settings& settings)
        {
            const bool commands = settings.groups[kCommands].enabled;
            const bool meters = settings.groups[static_cast<size_t>(Group::Hull)].enabled || settings.groups[static_cast<size_t>(Group::Ammo)].enabled;
            // Qualify the command-specific region before installing shared
            // helpers for a command-only configuration. A refused command
            // adapter must not disable the other independently enabled groups.
            const bool commandBound = !commands || BindCommand();
            const bool meterBound = !meters || BindMeters();
            bool otherGroups = false;
            for (size_t i = 0; i < kSafeFrameGroups; ++i)
                otherGroups = otherGroups || settings.groups[i].enabled;
            if (!otherGroups && !(commands && commandBound) && !(meters && meterBound)) return false;
            if (!Install()) return false;
            const bool commandOk = commandBound && (!commands || InstallCommand());
            const bool meterOk = meterBound && (!meters || InstallMeters());
            return commandOk && meterOk;
        }

        bool Snapshot(uint64_t& identity, std::array<uint64_t,kGroups>& values, MeterSample& meters) noexcept
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
                meters = SampleMeters(player,carrier,weaponState,ammo);
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
        const bool meter = group == Group::Hull || group == Group::Ammo;
        if (g_ready.load(std::memory_order_acquire) && (!meter || g_metersReady.load(std::memory_order_acquire)) && static_cast<size_t>(group) < kGroups)
            g_drawOpacity *= g_opacity[static_cast<size_t>(group)].load(std::memory_order_relaxed);
        return previous;
    }
    void EndDraw(float previous) noexcept { g_drawOpacity = previous; }
    void ResetMission() noexcept
    {
        AcquireSRWLockExclusive(&g_lock); g_state.Reset(); g_commandInstance = 0; ReleaseSRWLockExclusive(&g_lock);
        for (auto& opacity : g_opacity) opacity.store(1,std::memory_order_relaxed);
    }
    bool ReloadConfig()
    {
        Settings settings;
        const char* prefixes[] = {"WeaponList", "ScrapHud", "PilotHud", "CommandHud", "HullHud", "AmmoHud"};
        for (size_t i = 0; i < kGroups; ++i)
        {
            auto& group = settings.groups[i];
            const std::string prefix = prefixes[i];
            TryGetUserConfigBool("Display",(prefix + "Fade").c_str(),group.enabled);
            group.idlePercent = Integer(prefix + "IdleOpacity",i == kCommands ? 0 : 25,0,100);
            group.delayMs = Integer(prefix + "FadeDelay",2500,0,30000);
            group.fadeMs = Integer(prefix + "FadeDuration",500,0,5000);
        }
        AcquireSRWLockExclusive(&g_lock); g_settings = settings; g_state.Reset(); g_commandInstance = 0; ReleaseSRWLockExclusive(&g_lock);
        for (auto& opacity : g_opacity) opacity.store(1,std::memory_order_relaxed);
        g_read = true;
        g_resources.store(settings.groups[1].enabled || settings.groups[2].enabled,std::memory_order_relaxed);
        if (!settings.Active()) { RefreshScrapPilotHudLayout(); return true; }
        if (g_IsSteamExe || !IsCompatibleGameVersion()) return false;
        const bool installed = InstallForSettings(settings);
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
        if (!g_ready.load(std::memory_order_acquire) ||
            (settings.groups[kCommands].enabled && !g_commandsReady.load(std::memory_order_acquire)) ||
            ((settings.groups[static_cast<size_t>(Group::Hull)].enabled || settings.groups[static_cast<size_t>(Group::Ammo)].enabled) &&
             !g_metersReady.load(std::memory_order_acquire)))
        {
            if (now >= g_retry)
            {
                g_retry = now + 1000;
                InstallForSettings(settings);
                RefreshScrapPilotHudLayout();
            }
            if (!g_ready.load(std::memory_order_acquire)) return;
        }
        uint64_t owner = 0;
        std::array<uint64_t,kGroups> values{};
        MeterSample meters;
        const auto ui = ReadShellUiState();
        if (!ui.readable || ui.wrapperActive || ui.screenPresent || !Snapshot(owner,values,meters)) { ResetMission(); return; }
        AcquireSRWLockExclusive(&g_lock);
        // The command renderer owns its own activity sample; stable resource
        // observations must not overwrite input/menu activity recorded there.
        g_state.Observe(owner,values,now,kSafeFrameGroups);
        for (size_t i = 0; i < kSafeFrameGroups; ++i)
            g_opacity[i].store(g_state.groups[i].Opacity(settings.groups[i],now),std::memory_order_relaxed);
        for (size_t i = static_cast<size_t>(Group::Hull); i <= static_cast<size_t>(Group::Ammo); ++i)
        {
            auto& activity = g_state.groups[i];
            if (meters.readable)
                activity.Observe(i == static_cast<size_t>(Group::Hull) ? meters.hull : meters.ammo,now,
                    i == static_cast<size_t>(Group::Hull) ? meters.hullWarning : meters.ammoWarning);
            else activity = {};
            g_opacity[i].store(activity.Opacity(settings.groups[i],now),std::memory_order_relaxed);
        }
        ReleaseSRWLockExclusive(&g_lock);
    }
}
