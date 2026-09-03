#pragma once

// Preset migration for openshim.ini player defaults.
//
//   Revision 1: initial player preset introduced in e81d8b0a (2026-08-27)
//              never merged to main / never released / never workshop-shipped,
//              but retained as the historical bad baseline for the migration
//              framework. Contains:
//                 SinglePlayer/AttackRevealPerceivedTeam = 1
//                 Display/ScrapPilotHud = Legacy
//              SHA-256 of the exact payload as committed in e81d8b0a is
//              documented below as kLegacyRevision1Sha256. Because no public
//              preset has been proven to have shipped (see git history,
//              tags, releases, and Campaign Reimagined manifest in the commit
//              notes), this hash is a framework test vector rather than a
//              publicly-shipped artifact hash. If a future problematic preset
//              ships, its hash should be added here with provenance notes.
//
//   Revision 2: corrected, conservative opt-in preset prepared on this branch:
//                 AttackRevealPerceivedTeam = 0
//                 ScrapPilotHud = Stock
//                 feature/diagnostic switches OFF by default
//                 RawMouseInput remains available as an explicit opt-in
//                 "; OpenShimPresetRevision = 2" marker near top
//
//   Revision 3: reopens the doors to the settings.
//                 General/SettingsUi     = 1  (was 0)
//                 General/CustomBindsUi  = 1  (was 0)
//
//              Why this needs its own revision. 97aa4799 ("make OpenShim
//              features opt-in by default", 2026-08-30) applied the opt-in
//              policy to EVERY key, including the two that are not features
//              but the interface through which every other feature is
//              reached. With SettingsUi = 0 the OpenShim Settings page does
//              not exist in Redux Options, so a player cannot turn anything
//              on -- including SettingsUi itself -- without hand-editing
//              openshim.ini, which is exactly what the page exists to avoid.
//
//              7c4e2b4d and 96c54075 (2026-08-31) restored both keys to 1 in
//              the shipped preset, but kCurrentPresetRevision stayed at 2 the
//              whole time. Migration returns early when the file already
//              carries the current revision, so every install stamped
//              revision 2 during that window kept SettingsUi = 0 permanently
//              and no later release could correct it. Bumping to 3 is what
//              lets those installs be repaired.
//
//              The absent-key default was always ON (see the SettingsUi read
//              in bzr_options_ui.cpp and the env-config mapping), so this
//              only ever affects files carrying an explicit 0.
//
// Migration policy is implemented here so it works for:
//   - Campaign Reimagined Workshop users
//   - standalone OpenShim releases
//   - manually installed OpenShim
//   - other mods bundling the DLL
// and does NOT depend exclusively on Campaign Lua.

#include <filesystem>
#include <string>
#include <vector>

namespace BZROpenShim
{

    constexpr int kCurrentPresetRevision = 3;
    constexpr int kLegacyBadPresetRevision = 1;

    // SHA-256 of the exact e81d8b0a player preset (151 lines, LF, no BOM).
    // Computed with:  Get-FileHash -Algorithm SHA256
    // This is the "known bad" payload that the migration framework recognizes
    // for full-replacement (Case A). It is NOT a publicly shipped Workshop
    // or release hash – the file was never on main – but it is the only bad
    // revision that has existed in git history, so it is kept as a
    // deterministic test vector and as documentation of what would have
    // shipped had the PR merged without correction.
    //
    // If no bad preset has ever been publicly distributed, this array may
    // remain the sole entry and Case A will simply never fire in the wild;
    // that is intentional. Do not invent fake legacy hashes.
    inline constexpr const char* kLegacyRevision1Sha256 =
        "455b1750e4095891e1d784fe1b25bc33954507dd2622c3e208f0ffa5f9a4ec86";

    // Canonical player preset filename.
    inline constexpr const char* kPlayerPresetFileName = "openshim.ini";

    // Backup naming that does not collide with Settings UI's ".openshim.bak".
    // Example: openshim.ini.premigrate-r1.bak
    std::string BuildPremigrateBackupFileName(int fromRevision);

    // Try to compute lower-hex SHA-256 of the file at path. Returns false on
    // any I/O or crypto failure. Reuses no third-party library; uses Windows
    // CNG / BCrypt where available. Empty file hashes as SHA256("").
    bool TryComputeFileSha256Hex(const std::filesystem::path& path,
                                 std::string& outLowerHex);

    // Parse "; OpenShimPresetRevision = <int>" from the document lines.
    // Accepts optional whitespace and case-insensitive key, and requires the
    // leading ';' (metadata, not a runtime key). Returns false when absent
    // or unparseable, not an error.
    bool TryParsePresetRevisionFromLines(const std::vector<std::string>& lines,
                                         int& outRevision);

    // Lightweight typed values for the surgical migration table.
    enum class MigrationAction
    {
        None,               // No change, not our concern.
        FullReplaced,       // Exact known bad hash replaced wholesale.
        SurgicalFixed,      // Modified old preset: narrow value fixup.
        CustomUnrecognized, // Unknown/custom file: left alone.
        Failed,             // Detected but could not be written safely.
    };

    struct MigrationResult
    {
        MigrationAction action = MigrationAction::None;
        int fromRevision = 0;
        int toRevision = kCurrentPresetRevision;
        bool backupCreated = false;
        bool wroteNewFile = false;
        std::string backupPath;
        std::string logMessage;
        bool shouldLogCustomUnrecognized = false;
    };

    // Perform migration on the file at existingPath, using canonicalPath as
    // the source for "corrected preset" bytes when a full replacement is
    // needed. canonicalPath should normally be the on-disk openshim.ini that
    // the DLL would ship, but for tests it may be any file containing the
    // current revision content.
    //
    // Preconditions:
    //   - caller has verified existingPath exists; if it does not, this
    //     returns action=None and does nothing (creation-from-preset is
    //     handled elsewhere).
    //   - no frame-rate sensitive work; called once at startup.
    //
    // Guarantees:
    //   - never truncates or corrupts the source file on failure;
    //   - atomic replace via temp sibling + MoveFileEx where possible;
    //   - does not overwrite an existing premigrate backup without reason;
    //   - preserves comments/unknown keys/ordering where practical for
    //     surgical edits via the existing lossless writer;
    //   - revision marker is added/updated as metadata.
    MigrationResult MigratePresetFileIfNeeded(
        const std::filesystem::path& existingPath,
        const std::filesystem::path& canonicalPresetPath);

    // Startup entry point: locate the user file beside the game executable
    // (the same directory GetUserConfigPath uses), locate the canonical
    // preset that ships with this build (adjacent to winmm.dll / embedded
    // fallback), run migration if needed, and log once. Safe to call multiple
    // times; second call is no-op once revision == current. Returns result;
    // caller may use it to decide whether to reload config before using
    // values.
    //
    // Migration must happen before normal player configuration is fully
    // applied, or the loader must explicitly reload the migrated file before
    // using its values. This function documents that ordering in code and
    // should be invoked early enough that corrected values are used for the
    // current startup where practical (patcher or early bzr_hooks init).
    MigrationResult TryMigratePlayerPresetOnStartup();

    // Test helper: render the canonical preset lines (for idempotency checks).
    // In production this reads the embedded/adjacent canonical file; in tests
    // it reads canonicalPresetPath.
    std::vector<std::string> LoadCanonicalPresetLines(
        const std::filesystem::path& canonicalPresetPath);

    // Returns true when the document's first-class setting set exactly matches
    // the reference set (excluding the revision metadata and raw
    // compatibility keys). Used by tests to guard preset completeness.
    bool PresetHasCompleteFirstClassSet(
        const std::vector<std::string>& presetLines,
        const std::vector<std::string>& referenceLines,
        std::string& outDetail);

    // When a problematic preset is detected but the game directory cannot be
    // written (read-only install, locked file), runtime must still fail closed
    // for quarantined settings. This helper reports whether the current
    // process ever saw a bad preset that could not be migrated on disk, so
    // config readers can force safe defaults for this boot even though the
    // on-disk file still contains the old value.
    bool MigrationRequiresSafeFallbackForAttackReveal();

} // namespace BZROpenShim
