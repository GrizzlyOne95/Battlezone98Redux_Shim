// Included inside BZROpenShim::Hooks (bzr_options_ui.cpp) and by
// tests/options_ui_l10n_tests.cpp: pure data, so the host test sees the same
// rows the screens show. Labels and descriptions are the English fallback for
// resources/localization/openshim_localization.csv; keep them in sync with
// scripts/sync_options_localization.py.

struct ShimSettingDescriptor
{
    const char* label;         // row label in the UI
    const char* section;       // openshim.ini section
    const char* key;           // canonical ini key
    const char* const* altKeys;  // legacy key aliases replaced in-place
    size_t altKeyCount;
    const char* const* values;      // ini value written per option
    const char* const* valueLabels; // display text per option
    size_t valueCount;
    size_t defaultIndex;       // shown when the key is absent/invalid
    ShimSettingApplyGroup applyGroup;
    const char* description;   // one sentence shown in the status label on hover
};

static const char* const kShimSettingsOnOffValues[] = { "1", "0" };
// Action-row "values" are confirmation states, not settings. Index 0 is
// the resting cell, index 1 is what an armed row shows.
static const char* const kShimSettingsActionValues[] = { "Reset", "Confirm?" };
static const char* const kShimSettingsOnOffLabels[] = { "On", "Off" };
static const char* const kShimSettingsAutoSaveIntervalValues[] = { "60", "120", "180", "300", "600" };
static const char* const kShimSettingsAutoSaveIntervalLabels[] = { "1 min", "2 min", "3 min", "5 min", "10 min" };
static const char* const kShimSettingsUnderAttackValues[] = { "Normal", "Minimal", "None" };
static const char* const kShimSettingsUnitVoValues[] = { "Normal", "Reduced", "None" };
static const char* const kShimSettingsTargetPolicyValues[] = { "Default", "NeutralOnly", "ExplicitOnly" };
static const char* const kShimSettingsTargetPolicyLabels[] = { "Default", "Neutral Only", "Explicit Only" };
static const char* const kShimSettingsScrapHudValues[] = { "Legacy", "Stock" };
static const char* const kShimSettingsRadarScaleValues[] =
    { "1.0", "1.25", "1.5", "1.75", "2.0" };
static const char* const kShimSettingsRadarScaleLabels[] =
    { "Stock", "125%", "150%", "175%", "200%" };
static const char* const kShimSettingsSatelliteValues[] =
    { "1.0", "1.5", "2.0", "3.0" };
static const char* const kShimSettingsSatelliteLabels[] =
    { "Stock", "1.5x", "2x", "3x" };
static const char* const kShimSettingsHeadlightColorValues[] =
{
    "Stock", "White", "Red", "Green", "Blue", "Yellow",
    "Cyan", "Magenta", "Orange", "Purple", "Teal", "Rainbow"
};
static const char* const kShimSettingsHeadlightBeamValues[] = { "Stock", "Focused", "Wide" };
static const char* const kShimSettingsHeadlightBrightnessValues[] =
    { "0.50", "0.75", "1.00", "1.25", "1.50" };
static const char* const kShimSettingsHeadlightBrightnessLabels[] =
    { "50%", "75%", "100%", "125%", "150%" };
static const char* const kShimSettingsNetRouteValues[] = { "Stock", "Direct", "Relay" };
static const char* const kShimSettingsGovernorTuningValues[] = { "OpenShim", "Stock" };
static const char* const kShimSettingsNetRouteLabels[] = { "Stock", "Prefer Direct", "Force Relay" };
static const char* const kShimSettingsTargetPolicyAltKeys[] = { "TargetReticle" };
static const char* const kShimSettingsReticleConvAltKeys[] = { "SmartReticleConvergence" };
static const char* const kShimSettingsScavengerAltKeys[] = { "ScavengerPathing" };
static const char* const kShimSettingsBindsUiAltKeys[] = { "CustomBindingUi" };
static const char* const kShimSettingsRenderProfileValues[] = { "Retro", "Redux", "Enhanced" };
static const char* const kShimSettingsFovValues[] = { "0", "60", "70", "80", "90", "100", "110", "120" };
static const char* const kShimSettingsFovLabels[] = { "Stock (80)", "60", "70", "80", "90", "100", "110", "120" };
static const char* const kShimReticleStyles[] = { "Stock", "Cross", "Dot", "CrossDot" };
static const char* const kShimReticleStyleLabels[] = { "Stock", "Cross", "Dot", "Cross + Dot" };
static const char* const kShimReticleColors[] = { "White", "Green", "Cyan", "Amber" };
static const char* const kShimMeterColors[] = { "Default", "White", "Blue", "Green", "Cyan", "Amber", "Magenta", "Red", "Yellow" };
static const char* const kShimPaletteColors[] = { "Default", "White", "Blue", "Green", "Cyan", "Amber", "Magenta", "Red", "Yellow" };
static const char* const kShimPalettePresets[] = { "Stock", "Classic", "HighContrast" };
static const char* const kShimPalettePresetLabels[] = { "Stock", "Classic", "High Contrast" };
static const char* const kShimBackgroundOpacity[] = { "Default", "0", "25", "50", "75", "100" };
static const char* const kShimReticleSizes[] = { "75", "100", "150" };
static const char* const kShimReticleSizeLabels[] = { "Small", "Normal", "Large" };
static const char* const kShimReticleThickness[] = { "1", "2", "3" };
static const char* const kShimReticleThicknessLabels[] = { "Thin", "Normal", "Thick" };
static const char* const kShimReticleOpacity[] = { "50", "75", "100" };
static const char* const kShimReticleOpacityLabels[] = { "50%", "75%", "100%" };
static const char* const kShimDamageColors[] = { "Red", "Amber", "White", "Cyan", "Magenta", "Green", "Blue", "Yellow" };
static const char* const kShimFadeOpacities[] = { "0", "25", "50", "75" };
static const char* const kShimFadeOpacityLabels[] = { "Hidden", "25%", "50%", "75%" };
static const char* const kShimFadeDelays[] = { "1000", "2500", "5000" };
static const char* const kShimFadeDelayLabels[] = { "1 s", "2.5 s", "5 s" };
static const char* const kShimFadeDurations[] = { "0", "200", "500", "1000" };
static const char* const kShimFadeDurationLabels[] = { "Instant", "Fast", "Normal", "Slow" };
static const char* const kShimDamageDurations[] = { "300", "600", "1000" };
static const char* const kShimDamageDurationLabels[] = { "Short", "Normal", "Long" };
static const char* const kShimHitDurations[] = { "80", "120", "180", "250" };
static const char* const kShimHitDurationLabels[] = { "80 ms", "120 ms", "180 ms", "250 ms" };
// 0 disables the override and leaves the stock engine limit alone; the
// runtime clamps anything above 256, so 256 is the top of the ladder.
static const char* const kShimSettingsSoundChannelValues[] = { "0", "64", "128", "192", "256" };
static const char* const kShimSettingsSoundChannelLabels[] = { "Stock", "64", "128", "192", "256" };
// Redux ships 200. The runtime accepts any finite value in 1..10000
// from a hand-edited ini; these are the presets the page cycles.
static const char* const kShimSettingsReticleRangeValues[] = { "200", "300", "400", "500" };
static const char* const kShimSettingsReticleRangeLabels[] = { "Stock", "300", "400", "500" };

static const ShimSettingDescriptor g_ShimSettingsRegistry[] =
{
    { "Radar Fade", "Display", "RadarHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade the cockpit radar as one group: backdrop, terrain lines, compass, contacts and command links. Native radar activity reveals it. Applies live." },
    { "Radar Idle", "Display", "RadarHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Radar opacity when idle. Hidden keeps native visibility, alerts and ping/audio handling active." },
    { "Radar Delay", "Display", "RadarHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "Hold after radar range/mode or target changes, a newly native-visible contact, active commands or native-visible recent-hit alerts." },
    { "Radar Speed", "Display", "RadarHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration for all cockpit radar layers, preserving selected tints and native alpha." },
    { "Keep Compass", "Display", "RadarCompassAlwaysVisible", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Keep the four compass letters at native opacity while the rest of the radar fades. Off fades the compass with the radar." },
    { "Hull Fade", "Display", "HullHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade the cockpit hull meter and its labels when idle. Relevant value changes reveal it; native critical warnings keep it visible. Applies live." },
    { "Hull Idle", "Display", "HullHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Idle opacity for the cockpit hull group. Hidden keeps native status and warning handling active." },
    { "Hull Delay", "Display", "HullHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "Full-opacity hold after hull activity or a critical warning clears." },
    { "Hull Speed", "Display", "HullHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration for cockpit hull artwork and labels; relevant activity reveals them immediately." },
    { "Ammo Fade", "Display", "AmmoHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade the cockpit ammo meter and its labels when idle. Relevant value changes reveal it; native critical warnings keep it visible. Applies live." },
    { "Ammo Idle", "Display", "AmmoHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Idle opacity for the cockpit ammo group. Hidden keeps native status and warning handling active." },
    { "Ammo Delay", "Display", "AmmoHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "Full-opacity hold after ammo activity or a critical warning clears." },
    { "Ammo Speed", "Display", "AmmoHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration for cockpit ammo artwork and labels; relevant activity reveals them immediately." },
    { "Cmd Fade", "Display", "CommandHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade the whole command interface: frame, icons, text and bars. Command input reveals it; an active selection or submenu keeps it visible. Applies live." },
    { "Cmd Idle", "Display", "CommandHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 0, ShimSettingApplyGroup::ContextualHud,
      "Command interface opacity when idle. Hidden removes its visuals until you use it again; its native input handling stays active." },
    { "Cmd Delay", "Display", "CommandHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "How long the command interface remains fully visible after command activity or closing a selection/submenu." },
    { "Cmd Speed", "Display", "CommandHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Command interface fade duration. Sprite artwork and text use the same smooth opacity; command activity restores full opacity immediately." },
    { "Weapon Fade", "Display", "WeaponListFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade the weapon list when idle; selection, loadout or ammo changes reveal it. Preserves native colors and layout. Applies live." },
    { "Weapon Idle", "Display", "WeaponListIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Opacity while this group is idle. Hidden reveals it again on relevant changes. Applies only when its Fade option is on." },
    { "Weapon Delay", "Display", "WeaponListFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "How long this group stays fully visible after activity, before fading toward its idle opacity." },
    { "Weapon Speed", "Display", "WeaponListFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration: Instant, Fast (200 ms), Normal (500 ms), Slow (1000 ms). Activity restores full opacity immediately." },
    { "Scrap Fade", "Display", "ScrapHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade this meter when idle; current or maximum resource changes reveal it. Preserves native colors and layout. Applies live." },
    { "Scrap Idle", "Display", "ScrapHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Opacity while this group is idle. Hidden reveals it again on relevant changes. Applies only when its Fade option is on." },
    { "Scrap Delay", "Display", "ScrapHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "How long this group stays fully visible after activity, before fading toward its idle opacity." },
    { "Scrap Speed", "Display", "ScrapHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration: Instant, Fast (200 ms), Normal (500 ms), Slow (1000 ms). Activity restores full opacity immediately." },
    { "Pilot Fade", "Display", "PilotHudFade", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::ContextualHud,
      "Fade this meter when idle; current or maximum resource changes reveal it. Preserves native colors and layout. Applies live." },
    { "Pilot Idle", "Display", "PilotHudIdleOpacity", nullptr, 0,
      kShimFadeOpacities, kShimFadeOpacityLabels, 4, 1, ShimSettingApplyGroup::ContextualHud,
      "Opacity while this group is idle. Hidden reveals it again on relevant changes. Applies only when its Fade option is on." },
    { "Pilot Delay", "Display", "PilotHudFadeDelay", nullptr, 0,
      kShimFadeDelays, kShimFadeDelayLabels, 3, 1, ShimSettingApplyGroup::ContextualHud,
      "How long this group stays fully visible after activity, before fading toward its idle opacity." },
    { "Pilot Speed", "Display", "PilotHudFadeDuration", nullptr, 0,
      kShimFadeDurations, kShimFadeDurationLabels, 4, 2, ShimSettingApplyGroup::ContextualHud,
      "Smooth fade duration: Instant, Fast (200 ms), Normal (500 ms), Slow (1000 ms). Activity restores full opacity immediately." },
    { "Incoming Damage", "Display", "DamageIndicators", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::HudFeedback,
      "Arcs toward incoming weapon damage. One tick per recent attacker; repeated hits refresh its tick. Up to eight attackers. Single-player cockpit/chase." },
    { "Damage Color", "Display", "DamageIndicatorColor", nullptr, 0,
      kShimDamageColors, kShimDamageColors, 8, 0, ShimSettingApplyGroup::HudFeedback,
      "Incoming-damage arc color, independent of reticle and hit-marker colors. Applies live." },
    { "Damage Size", "Display", "DamageIndicatorSize", nullptr, 0,
      kShimReticleSizes, kShimReticleSizeLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Arc radius and thickness. Follows the game's native HUD scale. Applies live." },
    { "Damage Opacity", "Display", "DamageIndicatorOpacity", nullptr, 0,
      kShimReticleOpacity, kShimReticleOpacityLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Maximum incoming-damage arc opacity. Smaller hits are softer; larger hits are brighter and thicker." },
    { "Damage Duration", "Display", "DamageIndicatorDuration", nullptr, 0,
      kShimDamageDurations, kShimDamageDurationLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Hold then fade over 300, 600 or 1000 milliseconds. Arcs rotate with your view and disappear when changing units." },
    { "Reticle Style", "Display", "ReticleStyle", nullptr, 0,
      kShimReticleStyles, kShimReticleStyleLabels, 4, 0, ShimSettingApplyGroup::HudFeedback,
      "Stock artwork, cross, dot, or cross plus dot at the stock aim point. Applies live. GOG 2.2.301." },
    { "Reticle Color", "Display", "ReticleColor", nullptr, 0,
      kShimReticleColors, kShimReticleColors, 4, 0, ShimSettingApplyGroup::HudFeedback,
      "Color of custom reticles and target-contact brackets; stock artwork keeps its own colors." },
    { "Reticle Size", "Display", "ReticleSize", nullptr, 0,
      kShimReticleSizes, kShimReticleSizeLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Scale custom reticles and feedback with the game's current UI scale. Applies live." },
    { "Reticle Thickness", "Display", "ReticleThickness", nullptr, 0,
      kShimReticleThickness, kShimReticleThicknessLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Line thickness for custom reticles and feedback. Applies live." },
    { "Reticle Outline", "Display", "ReticleOutline", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::HudFeedback,
      "Dark outline for custom reticles and feedback, for contrast on bright terrain. Applies live." },
    { "Reticle Opacity", "Display", "ReticleOpacity", nullptr, 0,
      kShimReticleOpacity, kShimReticleOpacityLabels, 3, 2, ShimSettingApplyGroup::HudFeedback,
      "Opacity of custom reticles and feedback. Stock artwork is unchanged." },
    { "Reactive Reticle", "Display", "ReactiveReticle", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::HudFeedback,
      "Over a target, contract a custom cross, add brackets and tint red for enemies or green for allies. "
      "Visual only; disguised units stay untinted. Single player only." },
    { "Hit Markers", "Display", "HitMarkers", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1, ShimSettingApplyGroup::HudFeedback,
      "Ticks pop out when your weapon actually reduces health; hitting several targets at once enlarges them. "
      "No marker for blocked/zero damage, collisions, self hits or AI shots. Single player only." },
    { "Marker Duration", "Display", "HitMarkerDuration", nullptr, 0,
      kShimHitDurations, kShimHitDurationLabels, 4, 1, ShimSettingApplyGroup::HudFeedback,
      "How long confirmed-hit ticks remain visible before fading. Applies live." },
    { "Marker Color", "Display", "HitMarkerColor", nullptr, 0,
      kShimReticleColors, kShimReticleColors, 4, 0, ShimSettingApplyGroup::HudFeedback,
      "Hit tick color, independent of reticle color. Applies live." },
    { "Marker Size", "Display", "HitMarkerSize", nullptr, 0,
      kShimReticleSizes, kShimReticleSizeLabels, 3, 1, ShimSettingApplyGroup::HudFeedback,
      "Hit tick scale, independent of reticle size. Applies live." },
    { "Marker Opacity", "Display", "HitMarkerOpacity", nullptr, 0,
      kShimReticleOpacity, kShimReticleOpacityLabels, 3, 2, ShimSettingApplyGroup::HudFeedback,
      "Hit tick opacity, independent of reticle opacity. Applies live." },
    { "Stock Shader", "Display", "StockReticleShader", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0, ShimSettingApplyGroup::HudFeedback,
      "Stock artwork on DX11: tint it red/green with Reactive Reticle and ripple its own art on hits. "
      "Off keeps stock colors with a sprite-only ripple. Applies live." },
    { "Scrap Color", "Display", "ScrapHudColor", nullptr, 0,
      kShimMeterColors, kShimMeterColors, 9, 0, ShimSettingApplyGroup::GlobalImprovement,
      "Scrap title/value color. Default preserves the selected Stock/Legacy palette. Layout and plates stay as selected." },
    { "Pilot Color", "Display", "PilotHudColor", nullptr, 0,
      kShimMeterColors, kShimMeterColors, 9, 0, ShimSettingApplyGroup::GlobalImprovement,
      "Pilot title/value color. Default preserves the selected Stock/Legacy palette. Independent of scrap color." },
    { "Base Palette", "Display", "HudColorPreset", nullptr, 0,
      kShimPalettePresets, kShimPalettePresetLabels, 3, 0, ShimSettingApplyGroup::HudPalette,
      "Base colors for Default rows: Stock, Classic or High Contrast. Explicit color choices stay independent. Scrap/pilot and reticle settings are separate." },
    { "Radar Backdrop", "Display", "RadarBackgroundOpacity", nullptr, 0,
      kShimBackgroundOpacity, kShimBackgroundOpacity, 6, 0, ShimSettingApplyGroup::HudPalette,
      "Radar backdrop opacity (percent). Default follows the base palette. Terrain lines and contacts remain visible independently." },
    { "Radar Lines", "Display", "RadarGridColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Terrain grid tint. Native line opacity, radar geometry and contacts remain unchanged. Default follows the base palette." },
    { "Friendly Blips", "Display", "RadarFriendlyColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Normal friendly radar contact tint. Native dimming and alpha animation remain; disguised or ambiguous identities retain native colors. Default follows the base palette." },
    { "Enemy Blips", "Display", "RadarEnemyColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Normal enemy radar contact tint. Special alert markers retain their stock appearance. Default follows the base palette." },
    { "Neutral Blips", "Display", "RadarNeutralColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Normal neutral radar contact tint. Contacts are only recolored when native identity is unambiguous. Default follows the base palette." },
    { "Hull Healthy", "Display", "HullHighColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Cockpit health color at 50 percent or more. Native smoothing, fill and warnings remain. Default follows the base palette." },
    { "Hull Damaged", "Display", "HullMediumColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Cockpit health color from 25 to below 50 percent. Thresholds remain native. Default follows the base palette." },
    { "Hull Critical", "Display", "HullLowColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Cockpit health color below 25 percent. Thresholds remain native. Default follows the base palette." },
    { "Cockpit Ammo", "Display", "AmmoHudColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Cockpit ammo bar and label tint. Shot-cost ticks and remaining-shots text keep their native colors. Default follows the base palette." },
    { "Unit Healthy", "Display", "UnitHealthHighColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Command and selection health bars at 50 percent or more. Native recent-damage flashes remain. Default follows the base palette." },
    { "Unit Damaged", "Display", "UnitHealthMediumColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Command and selection health bars from 25 to below 50 percent. Native recent-damage flashes remain. Default follows the base palette." },
    { "Unit Critical", "Display", "UnitHealthLowColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Command and selection health bars below 25 percent. Native recent-damage flashes remain. Default follows the base palette." },
    { "Unit Ammo", "Display", "UnitAmmoColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Command and selection ammo-bar fill color, independent of cockpit ammo. Default follows the base palette." },
    { "Empty Bars", "Display", "UnitEmptyColor", nullptr, 0,
      kShimPaletteColors, kShimPaletteColors, 9, 0, ShimSettingApplyGroup::HudPalette,
      "Unfilled portions of command and selection health/ammo bars. Does not affect cockpit textures. Default follows the base palette." },
    { "Field of View", "Display", "FieldOfView", nullptr, 0,
      kShimSettingsFovValues, kShimSettingsFovLabels, 8, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Cockpit and chase base FOV in degrees (4:3 reference); widescreen expands horizontally. "
      "Stock is 80. Satellite and target cameras keep their own angles. Restart required." },
    // Deliberately NO Renderer (DX9/DX11) row: the runtime only parses
    // the [Graphics] Renderer preference and reports requested-vs-
    // effective divergence; it does not yet steer which render system
    // the game starts on. Exposing it as a restart-required selector
    // would promise a control that cannot deliver, so the row stays
    // hidden until startup renderer selection is actually implemented
    // (hand-edited openshim.ini values remain parsed and reported).
    { "Render Profile", "Graphics", "RenderProfile", nullptr, 0,
      kShimSettingsRenderProfileValues, kShimSettingsRenderProfileValues, 3, 1,
      ShimSettingApplyGroup::RenderProfile,
      "Visual rendering policy: Redux (stock baseline), Enhanced, or Retro. Applies live." },
    // [DX11Enhanced] is the experimental DX11 pipeline. Both rows fail
    // closed when the key is absent, which is what keeps an install
    // that never opted into this ini on the stock path; the shipped
    // openshim.ini opts in explicitly.
    { "DX11 FXAA", "DX11Enhanced", "FXAA", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "FXAA 3.11 anti-aliasing pass on the DX11 Enhanced pipeline. DX11 only. Restart required." },
    { "DX11 Local Lights", "DX11Enhanced", "EnhancedLightSelectionV2", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Contribution-ranked per-object local-light ordering. DX11 only. Restart required." },
    { "HD Terrain Tiles", "Terrain", "TerrainHdEnabled", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Full-resolution authored terrain tiles, with optional normal/specular maps. "
      "Requires a compatible pack and DX11 Enhanced; other profiles keep the original atlas. Restart required." },
    { "Terrain Micro Detail", "Terrain", "TerrainMicroRelief", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Experimental shallow ground relief. Visual only; collision is unchanged. "
      "DX11 only. Increases GPU cost. Restart required." },
    { "Sun Flashbang", "Display", "SunFlashbang", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::LiveEngineToggle,
      "On is stock: looking near the sun paints a fullscreen white flash. Off suppresses only that flash." },
    { "Attack Alert", "Display", "UnderAttackAlert", nullptr, 0,
      kShimSettingsUnderAttackValues, kShimSettingsUnderAttackValues, 3, 0,
      ShimSettingApplyGroup::UnderAttackAlert,
      "Under-attack warning style: Normal, Minimal (quieter), or None." },
    { "Hop-Out Alert Fix", "General", "SuppressHopOutAttackAlert", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::LiveEngineToggle,
      "Suppress the stale under-attack growl that fires the instant you hop out. Audio only." },
    { "Target Popup", "Display", "TargetPolicy",
      kShimSettingsTargetPolicyAltKeys, 1,
      kShimSettingsTargetPolicyValues, kShimSettingsTargetPolicyLabels, 3, 0,
      ShimSettingApplyGroup::TargetReticle,
      "When the reticle target popup appears: always, neutral objects only, or explicit targets only." },
    { "Scrap/Pilot HUD", "Display", "ScrapPilotHud", nullptr, 0,
      kShimSettingsScrapHudValues, kShimSettingsScrapHudValues, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Legacy BZ98-style scrap and pilot readout, or the stock Redux HUD." },
    // Local HUD geometry, so this one is not single-player only.
    { "Radar Size", "Display", "RadarSizeScale", nullptr, 0,
      kShimSettingsRadarScaleValues, kShimSettingsRadarScaleLabels, 5, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Scale the cockpit radar. The projection re-anchors to the backdrop so the "
      "mesh and its underlay stay concentric." },
    { "Satellite Zoom Out", "SinglePlayer", "SatelliteZoomOut", nullptr, 0,
      kShimSettingsSatelliteValues, kShimSettingsSatelliteLabels, 4, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "How much further than stock the satellite view can pull out. Single player only." },
    { "Satellite Pan Speed", "SinglePlayer", "SatellitePanSpeed", nullptr, 0,
      kShimSettingsSatelliteValues, kShimSettingsSatelliteLabels, 4, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Satellite view pan speed, as a multiple of stock. Single player only." },
    { "Jet Flames", "Display", "JetFlames", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::JetFlames,
      "Faction-colored engine flames on jets and thrusters." },
    { "Empty Craft Lights", "Display", "EmptyCraftLights", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::LiveEngineToggle,
      "Keep emissive running lights lit on craft that have no pilot." },
    { "Emissive Pulse", "Display", "EmissivePulse", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::LiveEngineToggle,
      "Vary occupied-craft emissive brightness with asynchronous organic pulses." },
    { "Star Twinkle", "Display", "StarTwinkle", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::LiveEngineToggle,
      "Animate brightness variation in compatible star-sky materials." },
    { "Unit Voices", "Display", "UnitVoFeedback", nullptr, 0,
      kShimSettingsUnitVoValues, kShimSettingsUnitVoValues, 3, 0,
      ShimSettingApplyGroup::UnitVo,
      "Unit voice feedback: Normal, Reduced chatter, or None." },
    { "MP Vehicle Flags", "Display", "MultiplayerFlags", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Multiplayer vehicle flags: the selection screen and the in-match renderer. "
      "Leave off for BZP/BZP-T; their waiting room is faction-only. Restart required." },
    { "Show Own MP Flag", "Display", "MultiplayerFlagShowOwnCraft", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Also draw your own flag over your own craft; stock draws only other players'. Restart required." },
    { "Death Chunk Meshes", "General", "ChunkMeshes", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Generate destruction pieces from the model's mesh and skeleton. Restart required." },
    { "Fast Menu Transitions", "General", "FastMenuTransitions", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Instant Action, Multiplayer and Custom Campaigns open and close without reloading every material; content loads once, before the mission or in the multiplayer game room. Restart required." },
    { "Sound Channels", "General", "SoundChannels", nullptr, 0,
      kShimSettingsSoundChannelValues, kShimSettingsSoundChannelLabels, 5, 4,
      ShimSettingApplyGroup::RestartRequired,
      "Simultaneous sound objects. Stock leaves the engine limit alone; 256 is the ceiling. Restart required." },
    { "Background Music", "General", "MusicGlobalFocus", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Keep the soundtrack playing and fed while the game is not the foreground window. Restart required." },
    { "Custom Keybinds", "General", "CustomBindsUi",
      kShimSettingsBindsUiAltKeys, 1,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Key-binding editor on the Input options page. Restart required." },
    { "Raw Mouse Input", "General", "RawMouseInput", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Reads the mouse as raw input, bypassing Windows pointer acceleration. Does not remove aim smoothing; see Unsmoothed Controls. Restart required." },
    { "Unsmoothed Controls", "General", "DisableControlSmoothing", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Steer, aim, throttle and strafe follow input directly instead of easing toward it, like BZ2's Control Smoothing Off. Affects mouse, keys and joystick. Restart required." },
    { "Per-Frame Mouse", "Experimental", "MouseEveryFrame", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Experimental. Apply mouse steer and aim every frame instead of 60 times a second, so aim keeps up with high refresh rates. Sensitivity is unchanged. Single player only. Restart required." },
    { "Material Guard", "General", "OgreMaterialCollisionGuard", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Survive duplicate Ogre material declarations that otherwise terminate the game. Restart required." },
    { "Map List Fixes", "General", "MapRefreshFixes", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Multiplayer map-list refresh and selection-preservation fixes. Restart required." },
    { "Map Filters+", "General", "MapFilterExtras", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Create Game map list: 5+ Players and Stock Maps filters, plus a search box. Restart required." },
    { "Editor Placement", "General", "EditorOverheadPlacementOrder", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "BZ 1.5 view order so object placement works in the running overhead view. Needs /edit. Restart required." },
    { "AutoSave", "AutoSave", "Enabled", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::AutoSave,
      "Rolling recovery save for single-player missions; manual saves remain your checkpoints." },
    { "AutoSave Interval", "AutoSave", "IntervalSeconds", nullptr, 0,
      kShimSettingsAutoSaveIntervalValues, kShimSettingsAutoSaveIntervalLabels, 5, 1,
      ShimSettingApplyGroup::AutoSave,
      "How often OpenShim refreshes the rolling AutoSave recovery slot." },
    { "Weapon Convergence", "SinglePlayer", "WeaponConvergence", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Walker-style convergence on an explicitly targeted craft. Single player only." },
    { "Muzzle Flashes", "SinglePlayer", "MuzzleFlash", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Enable authored weapon ODF mesh flashes and muzzle render effects (smoke/light). Requires mod assets and ODF configuration; no generic fallback. Experimental GOG single-player cannons. Restart required." },
    { "Muzzle Recoil", "SinglePlayer", "MeshRecoil", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Enable authored craft ODF barrel-node or animation recoil. Requires model nodes/clips and ODF configuration; no generic fallback. Clips need EXU. Experimental GOG single-player cannons. Restart required." },
    // Absent key = on, so defaultIndex 0 selects "1" (On).
    { "GPU Skinning", "Experimental", "GpuSkinning", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::ReadOnNextUse,
      "DX11 only: animate craft on the GPU instead of the CPU, which "
      "frees CPU time with many craft on screen. Edges may differ from stock by a "
      "fraction of a pixel. Takes effect on the next mission load." },
    { "Reticle Convergence", "SinglePlayer", "PlayerReticleConvergence",
      kShimSettingsReticleConvAltKeys, 1,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Same convergence, but toward the smart-reticle world point; no target lock required. Single player only." },
    { "Reticle Range", "SinglePlayer", "SmartReticleRange", nullptr, 0,
      kShimSettingsReticleRangeValues, kShimSettingsReticleRangeLabels, 4, 3,
      ShimSettingApplyGroup::GlobalImprovement,
      "Smart-reticle targeting distance; Stock is Redux's 200. OpenShim's own "
      "value is single-player only. A mission that calls EXU SetReticleRange "
      "(BZP, Reloaded) is honored in network games too." },
    { "Smart Scavengers", "SinglePlayer", "SmartScavengerPathing",
      kShimSettingsScavengerAltKeys, 1,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Smarter scavenger pathing to scrap. Single player only." },
    { "Turret AA Pitch", "SinglePlayer", "TurretAimPitch", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Turrets pitch up to engage air targets. Single player only." },
    { "Jump-Snipe Crouch", "SinglePlayer", "JumpSnipeCrouch", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "Classic crouch while sniping mid-jump. Single player only." },
    // Ships off, so the default index is "Off" (1) -- what an absent
    // key does -- not what any preset happens to write.
    { "Ordnance Velocity", "SinglePlayer", "OrdnanceVelocityInheritance", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalImprovement,
      "Shots inherit the shooter's velocity, and cannon lead compensates for it. "
      "Single player only." },
    // AI behaviour switches that change stock content without any
    // mission script, so they belong on the page rather than staying
    // ini-only. Each default index is what an ABSENT key does, which
    // is not the same as what a preset happens to ship.
    { "Bomber AI Range", "SinglePlayer", "BomberAiRange", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalImprovement,
      "Bombers engage at the range their own weapon ODFs declare. Single player only." },
    { "AI Howitzer Volley", "SinglePlayer", "AiWeaponMaskArtillery", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalImprovement,
      "Artillery AI fires every fitted hardpoint as one volley instead of the first. "
      "A stock howitzer fires four rounds per cycle. Single player only." },
    { "AI Mine Volley", "SinglePlayer", "AiWeaponMaskMinelayer", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalImprovement,
      "Minelayer AI honours weaponMask instead of hard-coding hardpoint 0. "
      "Single player only." },
    // [Fixes] rather than [SinglePlayer], and it ships ON, so the
    // default index is "On" (0).
    { "AI Multi-Producer", "Fixes", "AiMultiProducerMakers", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::GlobalImprovement,
      "A built class gets every producer that can make it, not just the first one found. "
      "Single player only." },
    { "Neutral Attack Orders", "Gameplay", "AllowNeutralAttackOrders", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalImprovement,
      "Allow explicit player attack orders against team-0 neutral objects. "
      "Diplomacy and autonomous targeting remain stock." },
    { "Global Turbo", "SinglePlayer", "Turbo", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::GlobalTurbo,
      "Turbo available on all drivable units. Single player only." },
    { "Satellite Fog Of War", "SinglePlayer", "SatelliteVisibilityFix", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::LiveEngineToggle,
      "Restore the BZ 1.5 satellite gate so unilluminated enemies stay hidden. Single player only." },
    { "Player Headlight", "SinglePlayer", "Headlights", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::Headlights,
      "Headlight on your vehicle. Single player only." },
    { "Headlight Brightness", "SinglePlayer", "HeadlightBrightness", nullptr, 0,
      kShimSettingsHeadlightBrightnessValues, kShimSettingsHeadlightBrightnessLabels, 5, 2,
      ShimSettingApplyGroup::Headlights,
      "Player-vehicle headlight intensity relative to stock. Applies live; single player only." },
    { "AI Headlights", "SinglePlayer", "OtherHeadlights", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::Headlights,
      "AI vehicles run headlights too. Single player only." },
    { "Headlight Color", "SinglePlayer", "HeadlightColor", nullptr, 0,
      kShimSettingsHeadlightColorValues, kShimSettingsHeadlightColorValues, 12, 0,
      ShimSettingApplyGroup::Headlights,
      "Headlight beam color; Rainbow cycles through colors." },
    { "Headlight Beam", "SinglePlayer", "HeadlightBeam", nullptr, 0,
      kShimSettingsHeadlightBeamValues, kShimSettingsHeadlightBeamValues, 3, 0,
      ShimSettingApplyGroup::Headlights,
      "Headlight beam shape: Stock, Focused (narrow), or Wide." },
    // Pilot flashlight. Not a stock light: no pilot skeleton has an
    // hlgt bone, so OpenShim creates this one on the pilot's own scene
    // node and destroys it when the player boards or the world ends.
    // Default off, so the default index is "Off" (1), matching what an
    // absent key does.
    { "Pilot Flashlight", "SinglePlayer", "PilotFlashlight", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::PilotFlashlight,
      "Flashlight on your pilot while on foot. Single player only." },
    { "Pilot Light Color", "SinglePlayer", "PilotFlashlightColor", nullptr, 0,
      kShimSettingsHeadlightColorValues, kShimSettingsHeadlightColorValues, 12, 0,
      ShimSettingApplyGroup::PilotFlashlight,
      "Pilot flashlight color; Rainbow cycles through colors." },
    { "Pilot Light Beam", "SinglePlayer", "PilotFlashlightBeam", nullptr, 0,
      kShimSettingsHeadlightBeamValues, kShimSettingsHeadlightBeamValues, 3, 0,
      ShimSettingApplyGroup::PilotFlashlight,
      "Pilot flashlight beam shape: Stock, Focused (narrow), or Wide." },
    // [Fixes]: confirmed Redux engine defects. All seven default ON and
    // normal single-player play wants them on -- they are switches so a
    // suspected regression is bisectable. Each one changes simulation
    // behaviour and none is negotiated with peers, so all seven stand
    // down for the duration of a network game and a mixed OpenShim /
    // stock lobby stays behaviourally identical.
    { "Background Mouse", "Fixes", "UnfocusedMouseRelease", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Stop Redux clipping and re-centring the mouse while it is minimized or in the background. Restart required." },
    { "Thread Scheduling", "Fixes", "ThreadScheduling", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Give the frame thread MMCSS Games priority and opt out of Windows power throttling. Restart required." },
    { "Vehicle Geometry", "SinglePlayer", "VehicleGeometryContact", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Experimental vehicle contact against legacy hull geometry. All supported vehicles; single player, GOG only. Restart required." },
    { "APC Allied Deploy", "Fixes", "ApcAlliedTargetDeploy", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Let APC AI accept allied deploy targets. Single player only. Restart required." },
    { "Splinter Undead Fix", "Fixes", "SplinterUndead", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Stop a destroyed splinter from spawning payload ordnance. Single player only. Restart required." },
    { "Howitzer Deploy Fix", "Fixes", "HowitzerUndeployedRetaliation", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Stop an undeployed howitzer counter-sniping its attacker. Single player only. Restart required." },
    { "Tug Cargo Deploy", "Fixes", "TugCargoPostLoad", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Arm the stock deploy transition after a tug loads cargo. Single player only. Restart required." },
    { "Recycle Release Fix", "Fixes", "ConstructorRecycleStaleTarget", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Free a constructor left deployed when another recycles its target first. Single player only. Restart required." },
    { "Precise Timestep", "Fixes", "PreciseTimestep", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Step the simulation by the measured frame time, not whole milliseconds. Single player only. Restart required." },
    { "Music Track Start", "Fixes", "MusicSingleFill", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Decode a new music track's first buffer once instead of twice, shortening the hitch at each track change. Restart required." },
    { "Constructor Cleanup", "Fixes", "ConstructorRemoteBuild", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Clear a dead constructor's remote build state. Single player only. Restart required." },
    { "Craft Culling", "Fixes", "RestoreCraftBounds", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Give craft their real bounding boxes so off-screen and distant craft are "
      "skipped by the camera and shadows. Rendering only. Restart required." },
    { "Effect Batching", "Fixes", "DynamicGeometryPieceReuse", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Add smoke, fire and tracer sprites to the current batch when they would be "
      "merged into it anyway, instead of opening a new one. Same pixels, less CPU. Restart required." },
    { "Effect Sort", "Fixes", "DynamicGeometryFastSort", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Sort effect-sprite batches without calling into Ogre for every compare. "
      "Same order, same pixels. Restart required." },
    { "Net Route", "Network", "RoutePreference", nullptr, 0,
      kShimSettingsNetRouteValues, kShimSettingsNetRouteLabels, 3, 0,
      ShimSettingApplyGroup::BzrNetRoute,
      "Preferred peer path: try LAN then direct WAN, or force the BZRNet relay. "
      "Does not add LAN or direct-IP hosting." },
    { "Net Improvements", "Network", "NetImprovements", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "OpenShim's socket layer as a whole. Off gives stock networking; "
      "turn it off to rule the shim out of a connection problem." },
    { "Net Tuning", "Network", "GovernorTuning", nullptr, 0,
      kShimSettingsGovernorTuningValues, kShimSettingsGovernorTuningValues, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Bandwidth governor and host auto-kick. Stock matches players who "
      "are not running OpenShim; net.ini still overrides per value." },
    // defaultIndex 1 selects "0", which is what an absent key does.
    // RestartRequired here means "no live apply step": the hook re-reads
    // the ini every time the multiplayer vehicle list is built, so the
    // change lands on the next list load without a relaunch.
    { "Stock Factions", "Network", "StockFactionsOnly", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Restrict multiplayer starting vehicles to NSDF and CCA, as 1.5 did with "
      "Any Nation off. Local only, and it never adds craft the map withheld. "
      "Applies next time a vehicle list loads." },
    { "Lobby Ban Button", "Network", "LobbyBanButton", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::RestartRequired,
      "Ban User button on the multiplayer waiting room. Off leaves BZP/BZP-T's "
      "faction picker alone; /ban still works. Restart required." },
    // defaultIndex 0 selects "1": an absent key persists, which is what
    // the feature did before it had a key at all.
    { "Persistent Mutes", "Network", "PersistentPlayerMute", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::ReadOnNextUse,
      "Remember muted players across sessions, by stable identity, so a rename "
      "or reconnect does not undo it. Off is stock: the mute lasts the session. "
      "Local only; /mute works either way and your mute list is kept." },
    { "Lobby Readouts", "Network", "LobbyReadouts", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Nickname field and route readout in the waiting-room left column. "
      "Does not cover BZP's faction picker. Restart required." },
    // Re-read on every nickname apply; no process restart is required
    // for the next OK / /nickname to take the new value.
    { "Live Nickname", "Network", "ReauthOnNicknameChange", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::ReadOnNextUse,
      "Experimental: recycle the lounge BZRNet connection after a nickname "
      "edit so stock reconnects and authorizes the new name. Expect a brief "
      "lounge drop / possible Not Ready flicker. In-match remains persist-only." },
    // Absent key = off, so defaultIndex 1 selects "0" (Off).
    { "MP Setup Screen", "Network", "PreLobby", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
      ShimSettingApplyGroup::ReadOnNextUse,
      "Multiplayer opens a setup screen first (nickname, flag, matchmaking "
      "server: Rebellion or Custom) instead of going straight to the lobby. "
      "While on, the nickname and flag pickers move to that screen and are "
      "no longer built in the lobby. Read when Multiplayer is clicked." },
    // defaultIndex 0 selects "1", matching an absent key (default on).
    { "Auto-Install Updates", "Updater", "AutoStage", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::ReadOnNextUse,
      "Check the Steam Workshop once when the main menu first appears and stage a newer OpenShim "
      "to install when you quit. Never runs in multiplayer." },
    // defaultIndex 0 selects "1", which is what an absent key does: the
    // native tracker has always run, and turning the row off must be a
    // deliberate choice rather than the effect of a missing ini key.
    { "Career Stats", "Career", "StatsTracking", nullptr, 0,
      kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
      ShimSettingApplyGroup::RestartRequired,
      "Record kills, deaths and missions played to career_stats.cfg across "
      "single player and multiplayer. Local file only; nothing is uploaded, "
      "and no mission script is required." },
    // Action row: no ini key, no cycling. Section/key stay null so the
    // settings reader and the lossless ini writer never touch it.
    { "Reset Career Stats", nullptr, nullptr, nullptr, 0,
      kShimSettingsActionValues, kShimSettingsActionValues, 2, 0,
      ShimSettingApplyGroup::CareerStatsReset,
      "Clear every recorded kill, death and mission play. Takes two clicks, "
      "and keeps the previous record as career_stats.cfg.openshim.bak. "
      "Does not turn tracking off." },
};
