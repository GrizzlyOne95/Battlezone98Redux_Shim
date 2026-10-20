#include "hud_feedback.h"
#include "hud_feedback_policy.h"
#include "hud_color_policy.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_object_layout.h"
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
        using TeamRelation = bool(__thiscall*)(void*, int);

        SRWLOCK g_stateLock = SRWLOCK_INIT;
        Settings g_settings;
        Pulse g_pulse;
        DamageIndicatorSettings g_incomingSettings;
        IncomingPulses g_incoming;
        bool g_configRead = false; // game/UI thread only
        bool g_subscribed = false;
        bool g_drawReady = false;
        uint64_t g_nextInstall = 0;
        std::atomic<bool> g_hitsEnabled{false};
        std::atomic<bool> g_incomingEnabled{false};
        std::atomic<bool> g_needsDraw{false};
        std::atomic<bool> g_damageReady{false};
        uint32_t g_sprite = 0, g_fill = 0, g_scale = 0, g_drawCall = 0, g_reticle = 0;
        uint32_t g_cameraRecord = 0, g_viewRecord = 0;
        bool g_cameraReady = false;
        uint32_t g_friendTeam = 0, g_enemyTeam = 0;
        bool g_relationReady = false;
        int g_indicatorPlayer = 0; // safe-frame thread only
        uint32_t g_damageSites[4] = {};
        InlineDetour32 g_damageDetours[4] = {};
        std::atomic<uintptr_t> g_originalDamage[4] = {};
        LONG g_drawLog = 1;
        LONG g_hitLogBudget = 8;

        bool NeedsDamage(const Settings& settings)
        {
            return settings.hits || g_incomingEnabled.load(std::memory_order_relaxed);
        }

        bool InstallCamera()
        {
            if (g_cameraReady) return true;
            const HookEngine::EngineRow rows[] = {
                {"GetCameraRecord", &g_cameraRecord}, {"ViewRecord", &g_viewRecord},
            };
            g_cameraReady = HookEngine::BindEngineRows("Damage indicator camera", rows);
            if (g_cameraReady) Log(L"[HUDFEEDBACK] Incoming damage uses main-view inverse rotation (cockpit/chase only)\n");
            return g_cameraReady;
        }

        bool ReadView(std::array<float, 9>& inverse, int& player) noexcept
        {
            if (!g_cameraReady || !g_BzrFn_GetPlayerHandle) return false;
            __try
            {
                const int mode = *reinterpret_cast<const int*>(g_viewRecord + 8);
                // Cockpit and chase only; auxiliary/cinematic/overview panes
                // must not display another view's incoming-damage information.
                if (mode != 0 && mode != 1) return false;
                player = g_BzrFn_GetPlayerHandle();
                if (!player || !GameObjectFromHandleGog(player)) return false;
                using CameraRecord = const uint8_t*(__cdecl*)();
                const auto* record = reinterpret_cast<CameraRecord>(g_cameraRecord)();
                if (!record) return false;
                std::memcpy(inverse.data(), record + 0x40, sizeof(float) * inverse.size());
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

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

        // Classifies the stock reticle's current object against the local
        // player, using the same native team policy and disguise rule as the
        // radar palette. Any doubt returns None, which keeps the base color.
        Relation ClassifyContact(void* object) noexcept
        {
            if (!g_relationReady || !object || !g_GameObjectGetHandleAddr || !g_BzrFn_GetPlayerHandle) return Relation::None;
            __try
            {
                // Released code treats Reticle+0xAC as a complete GameObject;
                // require its handle to round-trip before reading any field.
                const int handle = reinterpret_cast<GetHandle>(g_GameObjectGetHandleAddr)(object);
                if (!handle || GameObjectFromHandleGog(handle) != object) return Relation::None;
                const int playerHandle = g_BzrFn_GetPlayerHandle();
                void* player = playerHandle ? GameObjectFromHandleGog(playerHandle) : nullptr;
                if (!player || player == object) return Relation::None;
                const auto* bytes = static_cast<const uint8_t*>(object);
                const int team = *reinterpret_cast<const int*>(bytes + ObjectLayout::kGameObjectActualTeam);
                const int perceived = *reinterpret_cast<const int*>(bytes + ObjectLayout::kGameObjectPerceivedTeam);
                // Never reveal a disguised object's real team.
                if (team < 0 || team >= 16 || team != perceived) return Relation::None;
                if (team == 0) return Relation::Neutral;
                if (reinterpret_cast<TeamRelation>(g_enemyTeam)(player, team)) return Relation::Enemy;
                if (reinterpret_cast<TeamRelation>(g_friendTeam)(player, team)) return Relation::Friend;
                return Relation::Neutral;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return Relation::None; }
        }

        // Called at the one stock main-reticle sprite submission. Its x/y are
        // the engine's projected aim point, not a guessed screen center.
        void __cdecl DrawReticle(void* viewport, int sprite, int x, int y, uint32_t flags, float scale)
        {
            const int stockX = x, stockY = y;
            const auto original = reinterpret_cast<Sprite>(g_sprite);
            Pulse pulse;
            const Settings settings = ReadSettings(&pulse);
            DamageIndicatorSettings incomingSettings;
            IncomingPulses incoming;
            AcquireSRWLockShared(&g_stateLock);
            incomingSettings = g_incomingSettings;
            incoming = g_incoming;
            ReleaseSRWLockShared(&g_stateLock);
            const ShellUiState ui = ReadShellUiState();
            if ((!settings.NeedsDraw() && !incomingSettings.enabled) || !ui.readable || ui.wrapperActive || ui.screenPresent)
            {
                original(viewport, sprite, x, y, flags, scale);
                return;
            }

            Rect clip;
            float sx = 0, sy = 0;
            bool contact = false;
            void* contactObject = nullptr;
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
                contactObject = *reinterpret_cast<void* const*>(g_reticle + 0xAC);
                contact = contactObject != nullptr;
                valid = coordinatesValid;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}

            const bool singlePlayer = IsSinglePlayerSession();
            Settings effective = settings;
            effective.reactive = effective.reactive && singlePlayer;
            const uint64_t frameNow = GetTickCount64();
            const bool hitsOn = settings.hits && singlePlayer;
            const float strength = hitsOn ? pulse.Strength(frameNow, settings.hitDurationMs) : 0.0f;
            const float kick = hitsOn ? pulse.Kick(frameNow, settings.hitDurationMs) : 0.0f;
            const int targets = hitsOn ? pulse.Targets(frameNow, settings.hitDurationMs) : 1;
            const Relation relation = valid && effective.reactive && contact ? ClassifyContact(contactObject) : Relation::None;
            const DrawPlan plan = valid
                ? MakeDrawPlan(effective, x, y, sx, sy, clip, contact, strength, relation, kick, targets) : DrawPlan{};
            if (!plan.replacesStock) original(viewport, sprite, stockX, stockY, flags, scale);
            for (size_t i = 0; i < plan.count; ++i)
            {
                const auto& r = plan.rects[i];
                reinterpret_cast<Fill>(g_fill)(viewport, r.left, r.top, r.right, r.bottom, r.color, 0);
            }
            std::array<float, 9> inverse{};
            int player = 0;
            if (valid && singlePlayer && incomingSettings.enabled && ReadView(inverse, player))
            {
                const auto now = GetTickCount64();
                const auto groups = GroupIncomingArcs(incoming, now, incomingSettings.durationMs, player, inverse);
                for (size_t group = 0; group < groups.count; ++group)
                {
                    const auto& entry = groups.entries[group];
                    const auto arcs = MakeDamageIndicatorPlan(incomingSettings, x, y, sx, sy, clip,
                        entry.angle, entry.strength, entry.severity, entry.owners, entry.kick, groups.attackers);
                    for (size_t i = 0; i < arcs.count; ++i)
                    {
                        const auto& r = arcs.rects[i];
                        reinterpret_cast<Fill>(g_fill)(viewport, r.left, r.top, r.right, r.bottom, r.color, 0);
                    }
                }
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
            // Optional: team tint stands down alone if these rows fail.
            const HookEngine::EngineRow relationRows[] = {
                {"HudPaletteFriendTeam", &g_friendTeam}, {"HudPaletteEnemyTeam", &g_enemyTeam},
            };
            g_relationReady = HookEngine::BindEngineRows("Reticle team tint", relationRows);
            g_drawReady = RedirectCallTarget(g_drawCall, g_sprite, reinterpret_cast<uintptr_t>(DrawReticle));
            if (g_drawReady) Log(L"[HUDFEEDBACK] Stock main-reticle draw adapter installed (team tint %ls)\n",
                g_relationReady ? L"ready" : L"unavailable");
            return g_drawReady;
        }

        struct DamageContext
        {
            DamageSample sample;
            void* object = nullptr;
            bool localVictim = false;
            bool hasDirection = false;
            Direction direction;
        };

        DamageContext BeforeDamage(void* receiver, void* damage) noexcept
        {
            DamageContext context;
            if (!g_damageReady.load(std::memory_order_acquire) ||
                (!g_hitsEnabled.load(std::memory_order_relaxed) && !g_incomingEnabled.load(std::memory_order_relaxed)) || !IsSinglePlayerSession() ||
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
                const int player = g_BzrFn_GetPlayerHandle();
                context.sample.localAttacker = context.sample.attacker == player;
                context.sample.victim = get(context.object);
                context.localVictim = player != 0 && context.sample.victim == player;
                if (!context.sample.attacker || (!context.sample.localAttacker && !context.localVictim) ||
                    GameObjectFromHandleGog(context.sample.attacker) != attacker ||
                    GameObjectFromHandleGog(context.sample.victim) != context.object) return {};
                if (context.localVictim && g_incomingEnabled.load(std::memory_order_relaxed))
                {
                    float source[3]{}, victim[3]{};
                    if (TryGetGameObjectWorldPosition(attacker, source) && TryGetGameObjectWorldPosition(context.object, victim))
                    {
                        context.direction = {source[0] - victim[0], source[1] - victim[1], source[2] - victim[2]};
                        context.hasDirection = Normalize(context.direction);
                    }
                }
                context.sample.before = *reinterpret_cast<const float*>(static_cast<const uint8_t*>(context.object) + 0x200);
                context.sample.weaponSource = true;
                context.sample.singlePlayer = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return {}; }
            return context;
        }

        void AfterDamage(DamageContext context) noexcept
        {
            if ((!context.sample.localAttacker && !context.localVictim) || !context.object) return;
            __try
            {
                context.sample.sameLifetime = GameObjectFromHandleGog(context.sample.victim) == context.object;
                if (!context.sample.sameLifetime) return;
                context.sample.after = *reinterpret_cast<const float*>(static_cast<const uint8_t*>(context.object) + 0x200);
                context.localVictim = context.localVictim && g_BzrFn_GetPlayerHandle &&
                    context.sample.victim == g_BzrFn_GetPlayerHandle();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return; }
            if (g_hitsEnabled.load(std::memory_order_relaxed) && ConfirmsHit(context.sample))
                PublishSimEvent(OpenShimEventType::SimDamageApplied, context.sample.victim, context.sample.attacker, 0, 1);
            if (g_incomingEnabled.load(std::memory_order_relaxed) && context.hasDirection &&
                IsSinglePlayerSession() && ConfirmsIncoming(context.sample, context.localVictim))
            {
                // Copy values only; no object pointer survives this callback.
                // Fixed storage, no allocation and no rendering in the hook.
                AcquireSRWLockExclusive(&g_stateLock);
                if (g_incomingSettings.enabled)
                    g_incoming.Add(GetTickCount64(), g_incomingSettings.durationMs,
                        context.sample.victim, context.sample.attacker, context.direction, context.sample.before - context.sample.after);
                ReleaseSRWLockExclusive(&g_stateLock);
            }
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
            g_pulse.Start(event.tickMs, SimEventArg(event, 0));
            ReleaseSRWLockExclusive(&g_stateLock);
            if (InterlockedDecrement(&g_hitLogBudget) >= 0)
                Log(L"[HUDFEEDBACK] Confirmed player hit victim=%d attacker=%d\n", SimEventArg(event, 0), SimEventArg(event, 1));
        }
    }

    Settings PreviewSettings() { return ReadSettings(); }

    DamageIndicatorSettings PreviewDamageSettings()
    {
        AcquireSRWLockShared(&g_stateLock);
        const auto settings = g_incomingSettings;
        ReleaseSRWLockShared(&g_stateLock);
        return settings;
    }

    bool ReloadConfig()
    {
        // The HUD and damage sites run on the frame thread only.
        HookEngine::FrameThreadSitesScope frameSites;
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
        DamageIndicatorSettings incoming;
        TryGetUserConfigBool("Display", "DamageIndicators", incoming.enabled);
        if (TryGetUserConfigString("Display", "DamageIndicatorColor", text))
            if (const auto color = HudColors::Parse(text)) incoming.color = *color;
        incoming.sizePercent = ReadInteger("DamageIndicatorSize", 100, 50, 200);
        incoming.opacity = ReadInteger("DamageIndicatorOpacity", 75, 25, 100);
        incoming.durationMs = ReadInteger("DamageIndicatorDuration", 600, 150, 2000);
        AcquireSRWLockExclusive(&g_stateLock);
        g_settings = settings;
        g_pulse.Reset();
        g_incomingSettings = incoming;
        g_incoming.Reset();
        ReleaseSRWLockExclusive(&g_stateLock);
        g_hitsEnabled.store(settings.hits, std::memory_order_relaxed);
        g_incomingEnabled.store(incoming.enabled, std::memory_order_relaxed);
        g_needsDraw.store(settings.NeedsDraw() || incoming.enabled, std::memory_order_relaxed);
        g_configRead = true;
        InterlockedExchange(&g_drawLog, 1);
        if (NeedsDamage(settings) && !g_subscribed) g_subscribed = SubscribeEvents(EventSink, nullptr);
        if (!NeedsDamage(settings) && g_subscribed) { UnsubscribeEvents(EventSink, nullptr); g_subscribed = false; }
        if (!settings.NeedsDraw() && !incoming.enabled) return true;
        // This first adapter is deliberately GOG-only until the other native
        // ABIs have independent runtime qualification. No new dependencies.
        if (g_IsSteamExe || !IsCompatibleGameVersion()) return false;
        return (!incoming.enabled || InstallCamera()) && InstallDraw() &&
            (!NeedsDamage(settings) || (g_subscribed && InstallDamage()));
    }

    const char* UnavailableReason()
    {
        return g_IsSteamExe || !IsCompatibleGameVersion()
            ? "Unavailable: reticle feedback currently requires qualified GOG 2.2.301." : nullptr;
    }

    void Tick()
    {
        // The HUD and damage sites run on the frame thread only.
        HookEngine::FrameThreadSitesScope frameSites;
        if (!g_configRead) { ReloadConfig(); return; }
        if (!g_needsDraw.load(std::memory_order_relaxed)) return;
        const Settings settings = ReadSettings();
        if (g_IsSteamExe || !IsCompatibleGameVersion()) return;
        if (g_incomingEnabled.load(std::memory_order_relaxed))
        {
            std::array<float, 9> inverse{};
            int player = 0;
            if (!IsSinglePlayerSession() || !ReadView(inverse, player)) player = 0;
            if (player != g_indicatorPlayer || !player)
            {
                AcquireSRWLockExclusive(&g_stateLock);
                g_incoming.Reset();
                ReleaseSRWLockExclusive(&g_stateLock);
                g_indicatorPlayer = player;
            }
        }
        if (g_drawReady && (!g_incomingEnabled.load(std::memory_order_relaxed) || g_cameraReady) &&
            (!NeedsDamage(settings) || g_damageReady.load(std::memory_order_acquire))) return;
        const uint64_t now = GetTickCount64();
        if (now < g_nextInstall) return;
        g_nextInstall = now + 1000;
        if (g_incomingEnabled.load(std::memory_order_relaxed) && !InstallCamera()) return;
        if (InstallDraw() && NeedsDamage(settings) && g_subscribed) InstallDamage();
    }

    void ResetMission() noexcept
    {
        AcquireSRWLockExclusive(&g_stateLock);
        g_pulse.Reset();
        g_incoming.Reset();
        ReleaseSRWLockExclusive(&g_stateLock);
        InterlockedExchange(&g_hitLogBudget, 8);
    }
}
