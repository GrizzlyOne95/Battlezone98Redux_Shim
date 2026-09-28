// global_feature_config.cpp
// BZR Open Shim - global feature configuration: the openshim.ini
// preference load (InitializeGlobalImprovementConfig), the per-feature
// single-player gate reconcilers and baseline reverts, and the feature
// registry that drives the multiplayer gate, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool g_BomberAiRangeBaselineEnabled = kBomberAiRangeEnabledDefault;
        bool g_BomberAiRangeEnabled = kBomberAiRangeEnabledDefault;
        // Configured value AND'd with the single-player gate, same contract as
        // g_AiOdfGameplayTuningActive below. This feature changes stock content
        // (it raises bomber engagement range from the craft's own weapon ODFs),
        // so it must never reach a network game.
        bool g_BomberAiRangeActive = false;
        bool g_HowitzerUndeployedRetaliationFixEnabled =
            kHowitzerUndeployedRetaliationFixEnabledDefault;
        bool g_AiOdfGameplayTuningEnabled = kAiOdfGameplayTuningEnabledDefault;
        bool g_TurretAimPitchEnabled = kTurretAimPitchEnabledDefault;

        bool g_ShotConvergenceEnabled = true;

        bool g_ShotConvergenceBaselineEnabled = true;

        bool g_PlayerReticleShotConvergenceEnabled = true;

        bool g_PlayerReticleShotConvergenceBaselineEnabled = true;

        float g_SmartReticleRange = kSmartReticleRangeDefault;

        float g_SmartReticleRangeBaseline = kSmartReticleRangeDefault;

        // EXU/Lua (BZP, Reloaded, etc.) own the range when they call the
        // exported setter. The MP gate must not then force stock 200 over that
        // value -- those mods apply the longer reticle in network games on
        // purpose, and every peer in a matched lobby is doing the same.
        bool g_SmartReticleRangeOwnedByBridge = false;

        bool g_SmartScavengerPathingEnabled = true;

        static bool g_TurretAimPitchBaselineEnabled = true;

        bool g_ScrapPilotHudLegacyLayoutEnabled = true;

        ULONGLONG g_ScrapPilotHudLastRefreshTick = 0;

        // [Fixes] multiplayer gate. Each of these seven corrects a confirmed
        // Redux defect, but all seven change simulation behaviour, and none of
        // them is negotiated with peers -- so in a lobby that mixes OpenShim and
        // stock clients the two machines would run different code for the same
        // object. The `Enabled` flag above stays the user's openshim.ini answer
        // and still decides whether the hook/patch is installed at all; the
        // `Active` flag below is that answer reconciled against the live net id
        // by the feature registry, and it is what each hook body tests. Install
        // is deliberately NOT gated on Active: the hook has to already be in
        // place when a mission goes from single-player to a network game.
        bool g_TugCargoPostLoadFixActive = true;

        bool g_ConstructorRecycleStaleTargetFixActive = true;

        bool g_SplinterUndeadFixActive = kSplinterUndeadFixEnabledDefault;

        bool g_ConstructorRemoteBuildFixActive = kConstructorRemoteBuildFixEnabledDefault;

        // Global single-player improvement. The exact-byte and live-net-id
        // guards still keep it off unsupported builds and multiplayer.
        static constexpr bool kJumpSnipeCrouchEnabledDefault = true;

        // Enhancement rather than a defect fix, and it changes projectile
        // physics for every shot in the world, so it ships OFF under the
        // [SinglePlayer] policy and is hard-disabled in network games.
        static constexpr bool kOrdnanceVelocityInheritanceDefault = false;

        bool g_AllowNeutralAttackOrders = kAllowNeutralAttackOrdersDefault;

        bool g_AipResolveTraceEnabled = kAipResolveTraceDefault;

        bool g_AiMultiProducerMakersEnabled = kAiMultiProducerMakersDefault;

        // See the [Fixes] multiplayer gate note above.
        bool g_HowitzerUndeployedRetaliationFixActive =
            kHowitzerUndeployedRetaliationFixEnabledDefault;

        bool g_AiWeaponMaskArtilleryEnabled = kAiWeaponMaskArtilleryEnabledDefault;

        bool g_AiWeaponMaskMinelayerEnabled = kAiWeaponMaskMinelayerEnabledDefault;

        static bool g_AiOdfGameplayTuningBaselineEnabled = kAiOdfGameplayTuningEnabledDefault;

        bool g_AiOdfGameplayTuningActive = false;

        static float ClampTurretAimPitchMultiplier(float value)
        {
            if (value < 0.0f)
                return 0.0f;
            if (value > 1.25f)
                return 1.25f;
            return value;
        }

        // --- Global user preferences (openshim.ini) ----------------------------
        // A single user-editable INI carrying global preferences applied to ALL
        // single-player content (the stock campaign, Instant Action, and any
        // mission that does not script the setting itself). Two sections encode
        // the multiplayer-safety rule directly in the file layout:
        //   [Display]      cosmetic/local settings; applied everywhere, incl. MP.
        //   [SinglePlayer] sim/gameplay settings; applied in SP only, never MP.
        // Precedence per feature: engine default -> this file (user baseline) ->
        // mission script (EXU bridge) wins. A scripted override reverts to the
        // baseline captured from this file, not the hardcoded default, when the
        // mission ends (ResetMissionHookOverrides).
        static constexpr char kUserConfigGameplaySection[] = "Gameplay";

        static constexpr char kUserConfigDiagnosticsSection[] = "Diagnostics";

        void RefreshTurretAimPitchState()
        {
            const bool active = g_TurretAimPitchEnabled && ReadLocalPlayerNetIdValue() == 0;
            g_TurretAimPitchMultiplier = active ? g_TurretAimPitchMultiplierEnhanced : 0.5f;
        }

        void RefreshAiOdfGameplayTuningState()
        {
            g_AiOdfGameplayTuningActive =
                g_AiOdfGameplayTuningEnabled && ReadLocalPlayerNetIdValue() == 0;
        }

        static void RevertAiOdfGameplayTuningToBaseline()
        {
            g_AiOdfGameplayTuningEnabled = g_AiOdfGameplayTuningBaselineEnabled;
            RefreshAiOdfGameplayTuningState();
        }

        void RefreshBomberAiRangeState()
        {
            g_BomberAiRangeActive =
                g_BomberAiRangeEnabled && IsSinglePlayerSession();
        }

        static void RevertBomberAiRangeToBaseline()
        {
            g_BomberAiRangeEnabled = g_BomberAiRangeBaselineEnabled;
            RefreshBomberAiRangeState();
        }

        // --- [Fixes] multiplayer gate reconcilers ------------------------------
        // Six of the seven are plain flag tests inside an already-installed
        // hook, so reconciling them is just the net-id AND. The APC fix rewrites
        // two branch displacements and needs its bytes put back, so it gets its
        // own reconciler next to the writer (declared below, defined with the
        // installer).
        void RefreshSplinterUndeadFixState()
        {
            g_SplinterUndeadFixActive =
                g_SplinterUndeadFixEnabled && IsSinglePlayerSession();
        }

        void RefreshTugCargoPostLoadFixState()
        {
            g_TugCargoPostLoadFixActive =
                g_TugCargoPostLoadFixEnabled && IsSinglePlayerSession();
        }

        void RefreshConstructorRecycleStaleTargetFixState()
        {
            g_ConstructorRecycleStaleTargetFixActive =
                g_ConstructorRecycleStaleTargetFixEnabled && IsSinglePlayerSession();
        }

        void RefreshHowitzerUndeployedRetaliationFixState()
        {
            g_HowitzerUndeployedRetaliationFixActive =
                g_HowitzerUndeployedRetaliationFixEnabled && IsSinglePlayerSession();
        }

        void RefreshConstructorRemoteBuildFixState()
        {
            g_ConstructorRemoteBuildFixActive =
                g_ConstructorRemoteBuildFixEnabled && IsSinglePlayerSession();
        }


        void InitializeGlobalImprovementConfig()
        {
            bool value = true;

            g_ScrapPilotHudLegacyLayoutEnabled = true;
            std::string layout;
            if (TryGetUserConfigString(kUserConfigDisplaySection, "ScrapPilotHud", layout))
            {
                std::transform(layout.begin(), layout.end(), layout.begin(),
                    [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
                if (layout == "stock" || layout == "default" || layout == "0" ||
                    layout == "off" || layout == "false")
                {
                    g_ScrapPilotHudLegacyLayoutEnabled = false;
                }
                else if (layout == "legacy" || layout == "compact" || layout == "1" ||
                         layout == "on" || layout == "true")
                {
                    g_ScrapPilotHudLegacyLayoutEnabled = true;
                }
                else
                {
                    Log(L"[HUD] Ignoring invalid ScrapPilotHud=%hs\n", layout.c_str());
                }
            }

            g_ShotConvergenceBaselineEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "WeaponConvergence", value))
                g_ShotConvergenceBaselineEnabled = value;
            g_ShotConvergenceEnabled = g_ShotConvergenceBaselineEnabled;

            g_PlayerReticleShotConvergenceBaselineEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "PlayerReticleConvergence", value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection, "SmartReticleConvergence", value))
            {
                g_PlayerReticleShotConvergenceBaselineEnabled = value;
            }
            g_PlayerReticleShotConvergenceEnabled =
                g_PlayerReticleShotConvergenceBaselineEnabled;

            g_SmartReticleRangeBaseline = kSmartReticleRangeDefault;
            std::string reticleRangeText;
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "SmartReticleRange",
                    reticleRangeText) ||
                TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "ReticleRange",
                    reticleRangeText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(reticleRangeText.c_str(), &end);
                if (end != reticleRangeText.c_str() && *end == '\0' && std::isfinite(parsed))
                {
                    g_SmartReticleRangeBaseline = ClampSmartReticleRange(parsed);
                }
                else
                {
                    Log(L"[RETICLE] Ignoring invalid SmartReticleRange=%hs\n",
                        reticleRangeText.c_str());
                }
            }
            g_SmartReticleRangeOwnedByBridge = false;
            g_SmartReticleRange = g_SmartReticleRangeBaseline;

            g_SmartScavengerPathingEnabled = true;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "SmartScavengerPathing", value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection, "ScavengerPathing", value))
            {
                g_SmartScavengerPathingEnabled = value;
            }

            g_JumpSnipeCrouchBaselineEnabled = kJumpSnipeCrouchEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "JumpSnipeCrouch", value))
                g_JumpSnipeCrouchBaselineEnabled = value;
            g_JumpSnipeCrouchEnabled = g_JumpSnipeCrouchBaselineEnabled;

            g_OrdnanceVelocityInheritanceBaselineEnabled =
                kOrdnanceVelocityInheritanceDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection,
                                     "OrdnanceVelocityInheritance",
                                     value) ||
                TryGetUserConfigBool(kUserConfigSinglePlayerSection,
                                     "OrdnanceVelocInheritance",
                                     value))
            {
                g_OrdnanceVelocityInheritanceBaselineEnabled = value;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_ORDNANCE_VELOCITY_INHERITANCE"))
                g_OrdnanceVelocityInheritanceBaselineEnabled = false;
            g_OrdnanceVelocityInheritanceEnabled =
                g_OrdnanceVelocityInheritanceBaselineEnabled;

            g_RadarSizeScaleBaseline = 1.0f;
            std::string radarScaleText;
            if (TryGetUserConfigString(kUserConfigDisplaySection,
                                       "RadarSizeScale",
                                       radarScaleText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(radarScaleText.c_str(), &end);
                if (end != radarScaleText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_RadarSizeScaleBaseline = ClampRadarSizeScaleSetting(parsed);
                else
                    Log(L"[RADAR] Ignoring invalid RadarSizeScale=%hs\n",
                        radarScaleText.c_str());
            }
            g_RadarSizeScale = g_RadarSizeScaleBaseline;

            g_SatelliteZoomOutMultiplierBaseline = 1.0f;
            std::string satelliteText;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection,
                                       "SatelliteZoomOut",
                                       satelliteText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(satelliteText.c_str(), &end);
                if (end != satelliteText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_SatelliteZoomOutMultiplierBaseline = ClampSatelliteMultiplier(parsed);
                else
                    Log(L"[SATELLITE] Ignoring invalid SatelliteZoomOut=%hs\n",
                        satelliteText.c_str());
            }
            g_SatelliteZoomOutMultiplier = g_SatelliteZoomOutMultiplierBaseline;

            g_SatellitePanSpeedMultiplierBaseline = 1.0f;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection,
                                       "SatellitePanSpeed",
                                       satelliteText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(satelliteText.c_str(), &end);
                if (end != satelliteText.c_str() && *end == '\0' && std::isfinite(parsed))
                    g_SatellitePanSpeedMultiplierBaseline = ClampSatelliteMultiplier(parsed);
                else
                    Log(L"[SATELLITE] Ignoring invalid SatellitePanSpeed=%hs\n",
                        satelliteText.c_str());
            }
            g_SatellitePanSpeedMultiplier = g_SatellitePanSpeedMultiplierBaseline;

            g_AllowNeutralAttackOrders = kAllowNeutralAttackOrdersDefault;
            if (TryGetUserConfigBool(
                    kUserConfigGameplaySection,
                    "AllowNeutralAttackOrders",
                    value))
            {
                g_AllowNeutralAttackOrders = value;
            }

            g_AipResolveTraceEnabled = kAipResolveTraceDefault;
            if (TryGetUserConfigBool(
                    kUserConfigDiagnosticsSection,
                    "AipResolveTrace",
                    value))
            {
                g_AipResolveTraceEnabled = value;
            }

            g_AiMultiProducerMakersEnabled = kAiMultiProducerMakersDefault;
            if (TryGetUserConfigBool(
                    kUserConfigFixesSection,
                    "AiMultiProducerMakers",
                    value))
            {
                g_AiMultiProducerMakersEnabled = value;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_AI_MULTI_PRODUCER_MAKERS"))
                g_AiMultiProducerMakersEnabled = false;

            g_TurretAimPitchBaselineEnabled = kTurretAimPitchEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "TurretAimPitch", value))
                g_TurretAimPitchBaselineEnabled = value;
            g_TurretAimPitchEnabled = g_TurretAimPitchBaselineEnabled;

            // AiWeaponMaskSelection is the retired single key. It is still
            // honoured as the starting value for both halves so an existing
            // config keeps working, and either specific key then overrides it.
            g_AiWeaponMaskArtilleryEnabled = kAiWeaponMaskArtilleryEnabledDefault;
            g_AiWeaponMaskMinelayerEnabled = kAiWeaponMaskMinelayerEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskSelection", value))
            {
                g_AiWeaponMaskArtilleryEnabled = value;
                g_AiWeaponMaskMinelayerEnabled = value;
            }
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskArtillery", value))
                g_AiWeaponMaskArtilleryEnabled = value;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiWeaponMaskMinelayer", value))
                g_AiWeaponMaskMinelayerEnabled = value;

            g_BomberAiRangeBaselineEnabled = kBomberAiRangeEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "BomberAiRange", value))
                g_BomberAiRangeBaselineEnabled = value;
            g_BomberAiRangeEnabled = g_BomberAiRangeBaselineEnabled;
            RefreshBomberAiRangeState();

            g_AiOdfGameplayTuningBaselineEnabled = kAiOdfGameplayTuningEnabledDefault;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "AiOdfGameplayTuning", value))
                g_AiOdfGameplayTuningBaselineEnabled = value;
            g_AiOdfGameplayTuningEnabled = g_AiOdfGameplayTuningBaselineEnabled;

            float configuredMultiplier = 0.95f;
            std::string multiplierText;
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection,
                    "TurretAimPitchMultiplier",
                    multiplierText))
            {
                char* end = nullptr;
                const float parsed = std::strtof(multiplierText.c_str(), &end);
                if (end != multiplierText.c_str() && *end == '\0' && std::isfinite(parsed))
                    configuredMultiplier = parsed;
                else
                    Log(L"[TURRET] Ignoring invalid TurretAimPitchMultiplier=%hs\n",
                        multiplierText.c_str());
            }

            // Environment variables remain the highest-priority compatibility
            // override for existing installs and automation.
            if (TryGetEnvFloat("OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER", configuredMultiplier) ||
                TryGetEnvFloat("OPENSHIM_TURRET_PITCH_MULTIPLIER", configuredMultiplier))
            {
            }
            g_TurretAimPitchMultiplierEnhanced =
                ClampTurretAimPitchMultiplier(configuredMultiplier);

            g_ScrapPilotHudLastRefreshTick = 0;
            RefreshTurretAimPitchState();
            RefreshAiWeaponMaskArtilleryState();
            RefreshAiWeaponMaskMinelayerState();
            RefreshAiOdfGameplayTuningState();
            RefreshJumpSnipeCrouchPatchState();
            RefreshOrdnanceVelocityInheritanceState();
            RefreshRadarSizeScaleState();
            RefreshSatelliteViewState();
            RefreshShotConvergencePatchState();
            RefreshSmartReticleRangeState();
            RefreshScrapPilotHudLayout();

            Log(L"[GLOBAL] scrapPilotHud=%hs weaponConvergence=%hs playerReticleConvergence=%hs smartReticleRange=%.3f smartScavengerPathing=%hs jumpSnipeCrouch=%hs neutralAttackOrders=%hs turretAim=%hs multiplier=%.3f aiOdfTuning=%hs (SinglePlayer features remain SP-only)\n",
                g_ScrapPilotHudLegacyLayoutEnabled ? "legacy" : "stock",
                BoolText(g_ShotConvergenceBaselineEnabled),
                BoolText(g_PlayerReticleShotConvergenceBaselineEnabled),
                static_cast<double>(g_SmartReticleRangeBaseline),
                BoolText(g_SmartScavengerPathingEnabled),
                BoolText(g_JumpSnipeCrouchBaselineEnabled),
                BoolText(g_AllowNeutralAttackOrders),
                BoolText(g_TurretAimPitchBaselineEnabled),
                static_cast<double>(g_TurretAimPitchMultiplierEnhanced),
                BoolText(g_AiOdfGameplayTuningBaselineEnabled));
        }

        static void RevertTurretAimPitchToBaseline()
        {
            g_TurretAimPitchEnabled = g_TurretAimPitchBaselineEnabled;
            RefreshTurretAimPitchState();
        }

        // --- Global feature registry -------------------------------------------
        // One coordination point for the user-config / EXU-bridge driven features.
        // Each feature keeps its own apply/parse/baseline internals; the registry
        // only centralizes the two cross-cutting lifecycle actions so new features
        // are a single appended row instead of another open-coded call at every
        // reset/tick site:
        //   revertToBaseline  restore the post-mission resting state — the user's
        //                     openshim.ini baseline for Display features, the build
        //                     default for gameplay features. Called on mission end.
        //   refreshMpGate     reconcile a SinglePlayer-tier feature against the
        //                     live net id so it can never touch a network game.
        //                     Called on mission end and from the periodic sim tick.
        // Tier is advisory metadata today (it documents the [Display] vs
        // [SinglePlayer] openshim.ini section and whether refreshMpGate is required)
        // and is the hook future native features will read to auto-gate themselves.
        enum class FeatureTier
        {
            Display,       // cosmetic/local; applied everywhere, including MP.
            SinglePlayer,  // sim/gameplay; applied in SP only, hard-off in MP.
        };

        struct FeatureDescriptor
        {
            const char* name;
            FeatureTier tier;
            void (*revertToBaseline)();  // nullptr = nothing to revert
            void (*refreshMpGate)();     // nullptr = not multiplayer-gated
        };

        static const FeatureDescriptor g_FeatureRegistry[] = {
            { "UnderAttackAlert", FeatureTier::Display,
              &RevertUnderAttackAlertToBaseline, nullptr },
            { "TargetReticle", FeatureTier::Display,
              &RevertTargetReticlePopupToBaseline, nullptr },
            { "UnitVoFeedback", FeatureTier::Display,
              &RevertUnitVoToBaseline, nullptr },
            { "ScrapPilotHud", FeatureTier::Display,
              &RevertScrapPilotHudToBaseline, &RefreshScrapPilotHudLayout },
            { "WeaponConvergence", FeatureTier::SinglePlayer,
              &RevertShotConvergenceToBaseline, &RefreshShotConvergencePatchState },
            { "SmartReticleRange", FeatureTier::SinglePlayer,
              &RevertSmartReticleRangeToBaseline, &RefreshSmartReticleRangeState },
            { "TurretAimPitch", FeatureTier::SinglePlayer,
              &RevertTurretAimPitchToBaseline, &RefreshTurretAimPitchState },
            { "JumpSnipeCrouch", FeatureTier::SinglePlayer,
              &RevertJumpSnipeCrouchToBaseline, &RefreshJumpSnipeCrouchPatchState },
            { "OrdnanceVelocityInheritance", FeatureTier::SinglePlayer,
              &RevertOrdnanceVelocityInheritanceToBaseline,
              &RefreshOrdnanceVelocityInheritanceState },
            // Local HUD geometry; applied everywhere, including MP.
            { "RadarSizeScale", FeatureTier::Display,
              &RevertRadarSizeScaleToBaseline, nullptr },
            { "SatelliteView", FeatureTier::SinglePlayer,
              &RevertSatelliteViewToBaseline, &RefreshSatelliteViewState },
            { "GlobalTurbo", FeatureTier::SinglePlayer,
              &RevertGlobalTurboToBaseline, &RefreshGlobalTurboPatchState },
            { "Headlights", FeatureTier::SinglePlayer,
              &RevertHeadlightsToBaseline, &RefreshHeadlightState },
            { "PilotFlashlight", FeatureTier::SinglePlayer,
              &RevertPilotFlashlightToBaseline, &RefreshPilotFlashlightState },
            { "PilotTeamRestore", FeatureTier::SinglePlayer,
              &RevertPilotTeamRestoreToBaseline, &RefreshPilotTeamRestoreState },
            { "AiWeaponMaskArtillery", FeatureTier::SinglePlayer,
              &RevertAiWeaponMaskArtilleryToBaseline, &RefreshAiWeaponMaskArtilleryState },
            { "AiWeaponMaskMinelayer", FeatureTier::SinglePlayer,
              &RevertAiWeaponMaskMinelayerToBaseline, &RefreshAiWeaponMaskMinelayerState },
            { "AiOdfGameplayTuning", FeatureTier::SinglePlayer,
              &RevertAiOdfGameplayTuningToBaseline, &RefreshAiOdfGameplayTuningState },
            { "BomberAiRange", FeatureTier::SinglePlayer,
              &RevertBomberAiRangeToBaseline, &RefreshBomberAiRangeState },
            { "AttackRevealPerceivedTeam", FeatureTier::SinglePlayer,
              &RevertAttackRevealToBaseline, &RefreshAttackRevealState },
            // Display tier: purely observational, writes only its own config
            // file, and must keep running in network games.
            { "CareerStats", FeatureTier::Display,
              &RevertCareerStatsToBaseline, nullptr },
            // Client-side only, so it cannot desync -- but it is documented
            // under [SinglePlayer], and standing it down online is what keeps
            // a shim player's satellite view equivalent to a stock peer's.
            { "SatelliteVisibilityFix", FeatureTier::SinglePlayer,
              nullptr, &RefreshSatelliteVisibilityFixState },
            // [Fixes] engine-defect corrections. They are bug fixes rather than
            // enhancements and stay on for normal single-player play, but every
            // one of them changes simulation behaviour and none is negotiated
            // with peers, so they stand down for the duration of a network game
            // and a mixed OpenShim/stock lobby stays behaviourally identical.
            // There is no baseline to revert: the openshim.ini answer is read
            // once at startup and never scripted, so the gate is all they need.
            { "ApcAlliedTargetDeploy", FeatureTier::SinglePlayer,
              nullptr, &RefreshApcAlliedTargetDeployFixState },
            { "SplinterUndead", FeatureTier::SinglePlayer,
              nullptr, &RefreshSplinterUndeadFixState },
            { "HowitzerUndeployedRetaliation", FeatureTier::SinglePlayer,
              nullptr, &RefreshHowitzerUndeployedRetaliationFixState },
            { "OwnedObjectReveal", FeatureTier::SinglePlayer,
              nullptr, &RefreshOwnedObjectRevealFixState },
            { "TugCargoPostLoad", FeatureTier::SinglePlayer,
              nullptr, &RefreshTugCargoPostLoadFixState },
            { "ConstructorRecycleStaleTarget", FeatureTier::SinglePlayer,
              nullptr, &RefreshConstructorRecycleStaleTargetFixState },
            { "ConstructorRemoteBuild", FeatureTier::SinglePlayer,
              nullptr, &RefreshConstructorRemoteBuildFixState },
        };

        // Restore every registered feature to its resting state (mission end).
        void RevertRegisteredFeaturesToBaseline()
        {
            for (const auto& feature : g_FeatureRegistry)
            {
                if (feature.revertToBaseline)
                    feature.revertToBaseline();
            }
        }

        // Reconcile every multiplayer-gated feature against the current net id.
        static void RefreshRegisteredMpGatedFeatures()
        {
            for (const auto& feature : g_FeatureRegistry)
            {
                if (feature.refreshMpGate)
                    feature.refreshMpGate();
            }
        }

        // Slow re-assert cadence for the gate. A net id change reconciles
        // immediately regardless; this only bounds how long a patch site the
        // engine rewrote underneath us can stay out of sync.
        constexpr ULONGLONG kMpGateReassertMs = 250;

        // The gate's driver. Until now the only caller of
        // RefreshRegisteredMpGatedFeatures was ChunkEffectSimulateHook, which
        // runs only while debris is simulating -- so a byte-patched
        // SinglePlayer feature armed before a network game started stayed armed
        // until that match's first explosion. This is called from the Ogre
        // world-queue update as well, which runs every rendered frame whether or
        // not anything has blown up, and reconciles the instant the net id moves.
        void TickMpGateReconcile()
        {
            static uint16_t s_LastNetId = 0;
            static ULONGLONG s_LastReconcileTick = 0;

            // Only reconcile while a mission world exists. Some registry
            // entries write executable bytes (the crouch branch, the turbo
            // hooks), and this must not pull those writes earlier than the
            // chunk-effect driver already did: on Steam a .text write before
            // the runtime has settled trips SteamStub's integrity check. The
            // net id is deliberately NOT sampled into s_LastNetId here, so a
            // change that happened in the shell still reconciles on the first
            // frame of the mission that follows.
            if (!SatelliteWorldIsLive())
                return;

            const uint16_t netId = ReadLocalPlayerNetIdValue();
            const ULONGLONG now = GetTickCount64();
            const bool netIdChanged = netId != s_LastNetId;

            if (!netIdChanged &&
                s_LastReconcileTick != 0 &&
                now - s_LastReconcileTick < kMpGateReassertMs)
            {
                return;
            }

            if (netIdChanged)
            {
                Log(L"[MPGATE] net id %u -> %u; reconciling SinglePlayer-tier features (%hs)\n",
                    static_cast<unsigned>(s_LastNetId),
                    static_cast<unsigned>(netId),
                    netId == 0 ? "single-player" : "network game");
            }

            s_LastNetId = netId;
            s_LastReconcileTick = now;
            RefreshRegisteredMpGatedFeatures();
        }
    }

    using namespace Hooks;

    // Re-apply the feature behind a settings row from the freshly written
    // ini. Latched initializers get their latch cleared and re-run, which
    // deliberately preserves the documented precedence chain (legacy cfg and
    // env overrides still win over the ini baseline).
    void ApplyShimSettingLive(ShimSettingApplyGroup group)
    {
        switch (group)
        {
        case ShimSettingApplyGroup::GlobalImprovement:
            InitializeGlobalImprovementConfig();
            break;
        case ShimSettingApplyGroup::UnderAttackAlert:
            g_UnderAttackAlertConfigInitialized = false;
            InitializeUnderAttackAlertConfig();
            break;
        case ShimSettingApplyGroup::TargetReticle:
            g_TargetReticlePopupConfigInitialized = false;
            InitializeTargetReticlePopupConfig();
            break;
        case ShimSettingApplyGroup::JetFlames:
            g_JetFlamesConfigInitialized = false;
            InitializeJetFlamesConfig();
            break;
        case ShimSettingApplyGroup::UnitVo:
            g_UnitVoConfigInitialized = false;
            InitializeUnitVoConfig();
            break;
        case ShimSettingApplyGroup::GlobalTurbo:
            g_GlobalTurboConfigInitialized = false;
            InitializeGlobalTurboConfig();
            break;
        case ShimSettingApplyGroup::Headlights:
            ReapplyHeadlightConfigFromUserConfig();
            break;
        case ShimSettingApplyGroup::PilotFlashlight:
            g_PilotFlashlightConfigInitialized = false;
            InitializePilotFlashlightConfig();
            break;
        case ShimSettingApplyGroup::BzrNetRoute:
            // Only the route preference re-applies live; the port is latched on
            // the first pass because the engine overwrites that variable with
            // the port it actually bound.
            InitializeBzrNetConfig();
            break;
        case ShimSettingApplyGroup::RenderProfile:
            RenderProfiles::ReloadRenderProfileConfig();
            break;
        case ShimSettingApplyGroup::LiveEngineToggle:
            InitializeHopOutAttackAlertConfig();
            InitializeSatelliteVisibilityFixConfig(false);
            SunFlash::ReloadConfig();
            break;
        case ShimSettingApplyGroup::ReadOnNextUse:
        case ShimSettingApplyGroup::RestartRequired:
            break;
        }
    }
}
