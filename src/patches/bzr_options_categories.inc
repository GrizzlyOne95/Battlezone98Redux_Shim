// Included inside BZROpenShim::Hooks (bzr_options_ui.cpp) and by
// tests/options_ui_l10n_tests.cpp: pure data, so the host test sees the same
// category lists the screens show. Labels and descriptions are the English fallback for
// resources/localization/openshim_localization.csv; keep them in sync with
// scripts/sync_options_localization.py.

// Rows that are not openshim.ini settings: they run something.
constexpr const char* kShimRowUpdateCheck = "OpenShim Updates";
constexpr const char* kShimRowKeyBindings = "Key Bindings";
constexpr const char* kShimRowReticle = "Reticle & Hits";
constexpr const char* kShimRowPalette = "HUD Colors";
constexpr const char* kShimRowDamage = "Damage Indicators";
constexpr const char* kShimRowFading = "HUD Fading";
constexpr const char* kShimRowMeters = "Meter Fading";
constexpr const char* kShimRowRadar = "Radar Fading";
constexpr const char* kShimRowMenuTheme = "Menu Colors";
constexpr const char* kShimRowEffects = "Visual Effects";

static const char* const kShimCategoryVideo[] = {
    "Renderer", "Render Profile", "Field of View", "DX11 FXAA", "DX11 Local Lights", "DX11 Flip Model",
    "Shadow Distance", "HD Terrain Tiles", "Terrain Micro Detail", "GPU Skinning",
    kShimRowEffects, kShimRowMenuTheme };
static const char* const kShimCategoryEffects[] = {
    "Jet Flames", "Emissive Pulse", "Star Twinkle", "Death Chunk Meshes",
    "Muzzle Flashes", "Muzzle Recoil", "Shell Casings", "Skinned Gibs" };
static const char* const kShimCategoryLighting[] = {
    "Player Headlight", "Headlight Brightness", "Headlight Color", "Headlight Beam",
    "AI Headlights", "Pilot Flashlight", "Pilot Light Color", "Pilot Light Beam",
    "Explosion Flash", "Sun Flashbang", "Empty Craft Lights" };
static const char* const kShimCategoryAudio[] = {
    "Sound Channels", "Background Music", "Unit Voices", "Attack Alert", "Hop-Out Alert Fix" };
static const char* const kShimCategoryHud[] = {
    "Scrap/Pilot HUD", "Scrap Color", "Pilot Color", "Radar Size", "Target Popup",
    "MP Vehicle Flags", "Show Own MP Flag", kShimRowReticle, kShimRowPalette, kShimRowDamage, kShimRowFading, kShimRowMeters, kShimRowRadar };
static const char* const kShimCategoryRadar[] = {
    "Radar Fade", "Radar Idle", "Radar Delay", "Radar Speed", "Keep Compass" };
static const char* const kShimCategoryMeters[] = {
    "Hull Fade", "Hull Idle", "Hull Delay", "Hull Speed",
    "Ammo Fade", "Ammo Idle", "Ammo Delay", "Ammo Speed" };
static const char* const kShimCategoryFading[] = {
    "Weapon Fade", "Weapon Idle", "Weapon Delay", "Weapon Speed",
    "Scrap Fade", "Scrap Idle", "Scrap Delay", "Scrap Speed",
    "Pilot Fade", "Pilot Idle", "Pilot Delay", "Pilot Speed",
    "Cmd Fade", "Cmd Idle", "Cmd Delay", "Cmd Speed" };
static const char* const kShimCategoryDamage[] = {
    "Incoming Damage", "Damage Color", "Damage Size", "Damage Opacity", "Damage Duration",
    "Damage Flash" };
static const char* const kShimCategoryReticle[] = {
    "Reticle Style", "Reticle Color", "Reticle Size", "Reticle Thickness", "Reticle Outline",
    "Reticle Opacity", "Reactive Reticle", "Hit Markers", "Marker Duration",
    "Marker Color", "Marker Size", "Marker Opacity", "Stock Shader" };
static const char* const kShimCategoryPalette[] = {
    "Base Palette", "Radar Lines", "Radar Backdrop", "Friendly Blips", "Enemy Blips", "Neutral Blips",
    "Hull Healthy", "Hull Damaged", "Hull Critical", "Cockpit Ammo", "Unit Healthy", "Unit Damaged",
    "Unit Critical", "Unit Ammo", "Empty Bars" };
static const char* const kShimCategoryControls[] = {
    kShimRowKeyBindings, "Custom Keybinds", "Raw Mouse Input", "Unsmoothed Controls",
    "Satellite Zoom Out", "Satellite Pan Speed", "Editor Placement", "Background Mouse",
    "Run in Background" };
static const char* const kShimCategoryGameplay[] = {
    "Weapon Convergence", "Reticle Convergence", "Reticle Range", "Ordnance Velocity",
    "Jump-Snipe Crouch", "Global Turbo", "Satellite Fog Of War", "Attack Neutrals",
    "Smart Scavengers", "Turret AA Pitch", "Bomber AI Range", "AI Howitzer Volley",
    "AI Mine Volley", "Vehicle Geometry" };
static const char* const kShimCategoryFixes[] = {
    "AI Multi-Producer", "APC Allied Deploy", "Splinter Undead Fix", "Howitzer Deploy Fix",
    "Tug Cargo Deploy", "Recycle Release Fix", "Constructor Cleanup", "Material Guard" };
static const char* const kShimCategoryNetwork[] = {
    "Net Route", "UDP Port", "Net Improvements", "Net Tuning", "Stock Factions", "Map List Fixes",
    "Map Filters+", "Lobby Ban Button", "Lobby Readouts", "Persistent Mutes", "Live Nickname",
    "MP Setup Screen" };
static const char* const kShimCategorySystem[] = {
    kShimRowUpdateCheck, "Auto-Install Updates", "Career Stats", "Reset Career Stats",
    "AutoSave", "AutoSave Interval", "AutoSave Backups" };

struct ShimSettingsCategory
{
    const char* name;   // tile caption
    const char* title;  // screen title
    const char* blurb;  // hub hover text
    const char* const* rows;
    size_t rowCount;
};

#define BZR_SHIM_CATEGORY(name, title, blurb, rows) \
    { name, title, blurb, rows, sizeof(rows) / sizeof(rows[0]) }
static const ShimSettingsCategory kShimSettingsCategories[] =
{
    BZR_SHIM_CATEGORY("Video", "VIDEO",
        "Renderer, render profile, the DX11 Enhanced passes, shadows and terrain; visual effects open from here.", kShimCategoryVideo),
    BZR_SHIM_CATEGORY("Lighting", "LIGHTING",
        "Headlights, the pilot flashlight, explosion and sun flashes, and empty-craft lights.", kShimCategoryLighting),
    BZR_SHIM_CATEGORY("Audio", "AUDIO",
        "Sound channels, background music, unit voices and alerts.", kShimCategoryAudio),
    BZR_SHIM_CATEGORY("HUD", "HUD",
        "Scrap and pilot readout, radar size, target popup and vehicle flags.", kShimCategoryHud),
    BZR_SHIM_CATEGORY("Controls", "CONTROLS",
        "Key bindings, raw mouse input, control smoothing and the satellite view.",
        kShimCategoryControls),
    BZR_SHIM_CATEGORY("Gameplay", "GAMEPLAY",
        "Single-player aiming, AI behaviour and turbo.", kShimCategoryGameplay),
    BZR_SHIM_CATEGORY("Fixes", "FIXES",
        "Switches for confirmed Redux engine defects. Leave these on unless "
        "you are chasing a regression.", kShimCategoryFixes),
    BZR_SHIM_CATEGORY("Network", "NETWORK",
        "Connection route, the socket layer, lobby features and map lists.",
        kShimCategoryNetwork),
    BZR_SHIM_CATEGORY("System", "SYSTEM",
        "OpenShim updates, career statistics and AutoSave.", kShimCategorySystem),
    // Subpage reached from HUD; the existing nine-tile hub stays intact.
    BZR_SHIM_CATEGORY("Reticle", "RETICLE / HIT FEEDBACK",
        "Custom reticle appearance and single-player feedback.", kShimCategoryReticle),
    BZR_SHIM_CATEGORY("HUD Colors", "HUD COLORS",
        "Radar, cockpit meters and unit-bar colors. Default rows follow the base palette.", kShimCategoryPalette),
    BZR_SHIM_CATEGORY("Damage", "DAMAGE INDICATORS",
        "Directional feedback for incoming weapon damage in single player.", kShimCategoryDamage),
    BZR_SHIM_CATEGORY("Fading", "CONTEXTUAL HUD",
        "Independent idle opacity and timing for weapons, resources and the command interface.", kShimCategoryFading),
    BZR_SHIM_CATEGORY("Meter Fading", "METER FADING",
        "Independent cockpit hull and ammo fading; critical warnings stay visible.", kShimCategoryMeters),
    BZR_SHIM_CATEGORY("Radar Fading", "RADAR FADING",
        "Cockpit radar opacity and timing, with an independent compass exception.", kShimCategoryRadar),
    BZR_SHIM_CATEGORY("Effects", "VISUAL EFFECTS",
        "Jet flames, emissive pulse, star twinkle, death chunks, muzzle effects, shell casings and skinned gibs.",
        kShimCategoryEffects),
};
#undef BZR_SHIM_CATEGORY
