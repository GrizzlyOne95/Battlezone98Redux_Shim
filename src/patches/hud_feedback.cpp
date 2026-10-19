#include "hud_feedback.h"
#include "hud_feedback_policy.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "game_state.h"
#include "hook_engine.h"
#include "openshim_events.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <string>

namespace BZROpenShim::HudFeedback
{
    namespace
    {
        using namespace Hooks;
        using Sprite = void(__cdecl*)(void*, int, int, int, uint32_t, float);
        using Fill = void(__cdecl*)(void*, int, int, int, int, uint32_t, int);
        using Scale = uint64_t(__cdecl*)();
        using Damage = uint32_t(__thiscall*)(void*, void*, uint32_t);
        using GetHandle = int(__thiscall*)(void*);

        SRWLOCK g_stateLock = SRWLOCK_INIT;
        Settings g_settings;
        Pulse g_pulse;
        bool g_configRead = false; // game/UI thread only
        bool g_subscribed = false;
        bool g_drawReady = false;
        uint64_t g_nextInstall = 0;
        std::atomic<bool> g_hitsEnabled{false};
        std::atomic<bool> g_needsDraw{false};
        std::atomic<bool> g_damageReady{false};
        uint32_t g_sprite = 0, g_fill = 0, g_scale = 0, g_drawCall = 0, g_reticle = 0;
        uint32_t g_damageSites[4] = {};
        InlineDetour32 g_damageDetours[4] = {};
        std::atomic<uintptr_t> g_originalDamage[4] = {};
        LONG g_drawLog = 1;
        LONG g_hitLogBudget = 8;

        Settings ReadSettings(Pulse* pulse = nullptr)
        {
            AcquireSRWLockShared(&g_stateLock);
            const Settings settings = g_settings;
            if (pulse) *pulse = g_pulse;
            ReleaseSRWLockShared(&g_stateLock);
            return settings;
        }

        int ReadInteger(const char* key, int fallback, int low, int high)
        {
            std::string text;
            if (!TryGetUserConfigString("Display", key, text)) return fallback;
            char* end = nullptr;
            const long value = std::strtol(text.c_str(), &end, 10);
            if (end == text.c_str() || *end != '\0' || value < low || value > high) return fallback;
            return static_cast<int>(value);
        }

        // Called at the one stock main-reticle sprite submission. Its x/y are
        // the engine's projected aim point, not a guessed screen center.
        void __cdecl DrawReticle(void* viewport, int sprite, int x, int y, uint32_t flags, float scale)
        {
            const int stockX = x, stockY = y;
            const auto original = reinterpret_cast<Sprite>(g_sprite);
            Pulse pulse;
            const Settings settings = ReadSettings(&pulse);
            const ShellUiState ui = ReadShellUiState();
            if (!settings.NeedsDraw() || !ui.readable || ui.wrapperActive || ui.screenPresent)
            {
                original(viewport, sprite, x, y, flags, scale);
                return;
            }

            Rect clip;
            float sx = 0, sy = 0;
            bool contact = false;
            bool valid = false;
            __try
            {
                const auto* pane = static_cast<const int*>(viewport);
                clip = {pane[2], pane[3], pane[4], pane[5], 0};
                bool coordinatesValid = true;
                // The stock flags include pane-relative coordinates.
                if ((flags & 0x200000u) != 0)
                {
                    const int64_t px = static_cast<int64_t>(x) + clip.left;
                    const int64_t py = static_cast<int64_t>(y) + clip.top;
                    if (px < -65535 || px > 65535 || py < -65535 || py > 65535)
                    {
                        coordinatesValid = false;
                    }
                    else { x = static_cast<int>(px); y = static_cast<int>(py); }
                }
                const uint64_t pair = reinterpret_cast<Scale>(g_scale)();
                const uint32_t bitsX = static_cast<uint32_t>(pair);
                const uint32_t bitsY = static_cast<uint32_t>(pair >> 32);
                std::memcpy(&sx, &bitsX, sizeof(sx));
                std::memcpy(&sy, &bitsY, sizeof(sy));
                contact = *reinterpret_cast<void* const*>(g_reticle + 0xAC) != nullptr;
                valid = coordinatesValid;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}

            const bool singlePlayer = IsSinglePlayerSession();
            Settings effective = settings;
            effective.reactive = effective.reactive && singlePlayer;
            const float strength = settings.hits && singlePlayer
                ? pulse.Strength(GetTickCount64(), settings.hitDurationMs) : 0.0f;
            const DrawPlan plan = valid ? MakeDrawPlan(effective, x, y, sx, sy, clip, contact, strength) : DrawPlan{};
            if (!plan.replacesStock) original(viewport, sprite, stockX, stockY, flags, scale);
            for (size_t i = 0; i < plan.count; ++i)
            {
                const auto& r = plan.rects[i];
                reinterpret_cast<Fill>(g_fill)(viewport, r.left, r.top, r.right, r.bottom, r.color, 0);
            }
            if (plan.count && InterlockedExchange(&g_drawLog, 0))
                Log(L"[HUDFEEDBACK] Draw at stock aim point (%d,%d), scale=(%.2f,%.2f), rects=%zu\n",
                    x, y, sx, sy, plan.count);
        }

        bool InstallDraw()
        {
            if (g_drawReady) return true;
            const HookEngine::EngineRow rows[] = {
                {"HudFeedbackReticleCall", &g_drawCall}, {"HudFeedbackSprite", &g_sprite},
                {"HudFillRect", &g_fill}, {"HudFeedbackScale", &g_scale}, {"ReticleGlobal", &g_reticle},
            };
            if (!HookEngine::BindEngineRows("HUD feedback draw", rows)) return false;
            g_drawReady = RedirectCallTarget(g_drawCall, g_sprite, reinterpret_cast<uintptr_t>(DrawReticle));
            if (g_drawReady) Log(L"[HUDFEEDBACK] Stock main-reticle draw adapter installed\n");
            return g_drawReady;
        }

        struct DamageContext { DamageSample sample; void* object = nullptr; };

        DamageContext BeforeDamage(void* receiver, void* damage) noexcept
        {
            DamageContext context;
            if (!g_damageReady.load(std::memory_order_acquire) ||
                !g_hitsEnabled.load(std::memory_order_relaxed) || !IsSinglePlayerSession() ||
                !receiver || !damage || !g_GameObjectGetHandleAddr ||
                !g_BzrFn_GetPlayerHandle || !g_BzrFn_ResolveObj76GameObject)
                return context;
            __try
            {
                // All four qualified DamageAlloc entries receive the
                // distributedObject subobject, +0x18 from the complete object.
                context.object = static_cast<uint8_t*>(receiver) - 0x18;
                auto* const* fields = static_cast<void* const*>(damage);
                if (!fields[0] || !fields[1] || fields[0] == fields[1]) return {};
                void* attacker = g_BzrFn_ResolveObj76GameObject(fields[0]);
                if (!attacker) return {};
                const auto get = reinterpret_cast<GetHandle>(g_GameObjectGetHandleAddr);
                context.sample.attacker = get(attacker);
                context.sample.localAttacker = context.sample.attacker == g_BzrFn_GetPlayerHandle();
                if (!context.sample.localAttacker || context.sample.attacker == 0) return {};
                context.sample.victim = get(context.object);
                context.sample.before = *reinterpret_cast<const float*>(static_cast<const uint8_t*>(context.object) + 0x200);
                context.sample.weaponSource = true;
                context.sample.singlePlayer = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return {}; }
            return context;
        }

        void AfterDamage(DamageContext context) noexcept
        {
            if (!context.sample.localAttacker || !context.object) return;
            __try
            {
                context.sample.sameLifetime = GameObjectFromHandleGog(context.sample.victim) == context.object;
                if (!context.sample.sameLifetime) return;
                context.sample.after = *reinterpret_cast<const float*>(static_cast<const uint8_t*>(context.object) + 0x200);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return; }
            if (ConfirmsHit(context.sample))
                PublishSimEvent(OpenShimEventType::SimDamageApplied, context.sample.victim, context.sample.attacker, 0, 1);
        }

        template<size_t Index>
        uint32_t __fastcall DamageHook(void* receiver, void*, void* damage, uint32_t argument)
        {
            auto address = g_originalDamage[Index].load(std::memory_order_acquire);
            while (!address) { YieldProcessor(); address = g_originalDamage[Index].load(std::memory_order_acquire); }
            const auto original = reinterpret_cast<Damage>(address);
            const DamageContext context = BeforeDamage(receiver, damage);
            const uint32_t result = original(receiver, damage, argument);
            AfterDamage(context);
            return result;
        }

        bool InstallDamage()
        {
            if (g_damageReady.load(std::memory_order_acquire)) return true;
            ResolveLocalPlayerLookupForVerifiedGogBuild();
            const HookEngine::EngineRow rows[] = {
                {"HudFeedbackBuildingDamage", &g_damageSites[0]}, {"HudFeedbackCraftDamage", &g_damageSites[1]},
                {"HudFeedbackPersonDamage", &g_damageSites[2]}, {"HudFeedbackPowerupDamage", &g_damageSites[3]},
            };
            if (!g_GameObjectGetHandleAddr || !g_BzrFn_GetPlayerHandle || !g_BzrFn_ResolveObj76GameObject ||
                !HookEngine::BindEngineRows("HUD damage confirmation", rows)) return false;
            void* const hooks[] = {reinterpret_cast<void*>(DamageHook<0>), reinterpret_cast<void*>(DamageHook<1>),
                reinterpret_cast<void*>(DamageHook<2>), reinterpret_cast<void*>(DamageHook<3>)};
            static const uint8_t expected[4][9] = {
                {0x55,0x8B,0xEC,0x81,0xEC,0xE0,0,0,0}, {0x55,0x8B,0xEC,0x81,0xEC,0xB4,1,0,0},
                {0x55,0x8B,0xEC,0x81,0xEC,0x80,0,0,0}, {0x55,0x8B,0xEC,0x81,0xEC,0xD8,0,0,0},
            };
            for (size_t i = 0; i < 4; ++i)
            {
                if (!InstallInlineDetour32(g_damageDetours[i], g_damageSites[i], hooks[i], 9, expected[i], 9)) return false;
                g_originalDamage[i].store(reinterpret_cast<uintptr_t>(g_damageDetours[i].trampoline), std::memory_order_release);
            }
            g_damageReady.store(true, std::memory_order_release);
            Log(L"[HUDFEEDBACK] Post-damage confirmation adapters installed (single player only)\n");
            return true;
        }

        void EventSink(const OpenShimEvent& event, void*)
        {
            const auto type = static_cast<OpenShimEventType>(event.type);
            if (type == OpenShimEventType::SimSessionStarted || type == OpenShimEventType::SimSessionEnded)
                ResetMission();
            if (type != OpenShimEventType::SimDamageApplied || !g_hitsEnabled.load(std::memory_order_relaxed) ||
                !IsSinglePlayerSession() || SimEventArg(event, 3) == 0) return;
            const Settings settings = ReadSettings();
            const uint64_t now = GetTickCount64();
            if (now < event.tickMs || now - event.tickMs >= static_cast<uint64_t>(settings.hitDurationMs)) return;
            const auto ui = ReadShellUiState();
            if (!ui.readable || ui.wrapperActive || ui.screenPresent) return;
            AcquireSRWLockExclusive(&g_stateLock);
            g_pulse.Start(event.tickMs);
            ReleaseSRWLockExclusive(&g_stateLock);
            if (InterlockedDecrement(&g_hitLogBudget) >= 0)
                Log(L"[HUDFEEDBACK] Confirmed player hit victim=%d attacker=%d\n", SimEventArg(event, 0), SimEventArg(event, 1));
        }
    }

    Settings PreviewSettings() { return ReadSettings(); }

    bool ReloadConfig()
    {
        Settings settings;
        std::string text;
        if (TryGetUserConfigString("Display", "ReticleStyle", text)) settings.style = ParseStyle(text);
        if (TryGetUserConfigString("Display", "ReticleColor", text)) settings.color = ParseColor(text);
        if (TryGetUserConfigString("Display", "HitMarkerColor", text)) settings.hitColor = ParseColor(text);
        settings.hitSizePercent = ReadInteger("HitMarkerSize", 100, 50, 200);
        settings.hitOpacity = ReadInteger("HitMarkerOpacity", 100, 25, 100);
        settings.sizePercent = ReadInteger("ReticleSize", 100, 50, 200);
        settings.thickness = ReadInteger("ReticleThickness", 2, 1, 3);
        settings.opacity = ReadInteger("ReticleOpacity", 100, 25, 100);
        settings.hitDurationMs = ReadInteger("HitMarkerDuration", 120, 60, 400);
        TryGetUserConfigBool("Display", "ReticleOutline", settings.outline);
        TryGetUserConfigBool("Display", "ReactiveReticle", settings.reactive);
        TryGetUserConfigBool("Display", "HitMarkers", settings.hits);
        AcquireSRWLockExclusive(&g_stateLock);
        g_settings = settings;
        g_pulse.Reset();
        ReleaseSRWLockExclusive(&g_stateLock);
        g_hitsEnabled.store(settings.hits, std::memory_order_relaxed);
        g_needsDraw.store(settings.NeedsDraw(), std::memory_order_relaxed);
        g_configRead = true;
        InterlockedExchange(&g_drawLog, 1);
        if (settings.hits && !g_subscribed) g_subscribed = SubscribeEvents(EventSink, nullptr);
        if (!settings.hits && g_subscribed) { UnsubscribeEvents(EventSink, nullptr); g_subscribed = false; }
        if (!settings.NeedsDraw()) return true;
        // This first adapter is deliberately GOG-only until the other native
        // ABIs have independent runtime qualification. No new dependencies.
        if (g_IsSteamExe || !IsCompatibleGameVersion()) return false;
        return InstallDraw() && (!settings.hits || (g_subscribed && InstallDamage()));
    }

    const char* UnavailableReason()
    {
        return g_IsSteamExe || !IsCompatibleGameVersion()
            ? "Unavailable: reticle feedback currently requires qualified GOG 2.2.301." : nullptr;
    }

    void Tick()
    {
        if (!g_configRead) { ReloadConfig(); return; }
        if (!g_needsDraw.load(std::memory_order_relaxed)) return;
        const Settings settings = ReadSettings();
        if (!settings.NeedsDraw() || g_IsSteamExe || !IsCompatibleGameVersion()) return;
        if (g_drawReady && (!settings.hits || g_damageReady.load(std::memory_order_acquire))) return;
        const uint64_t now = GetTickCount64();
        if (now < g_nextInstall) return;
        g_nextInstall = now + 1000;
        if (InstallDraw() && settings.hits && g_subscribed) InstallDamage();
    }

    void ResetMission() noexcept
    {
        AcquireSRWLockExclusive(&g_stateLock);
        g_pulse.Reset();
        ReleaseSRWLockExclusive(&g_stateLock);
        InterlockedExchange(&g_hitLogBudget, 8);
    }
}
