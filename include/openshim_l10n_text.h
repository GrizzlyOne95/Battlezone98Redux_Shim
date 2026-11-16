// openshim_l10n_text.h
// BZR Open Shim - the localized-text lookup for OpenShim's own screens.
// Implemented in src/patches/bzr_options_ui.cpp over the options-page table;
// see Docs/OPTIONS_UI_LOCALIZATION.md. Main thread only. Screens
// add `using BZROpenShim::L10n::ShimText;` (and ShimFormat) after their includes. Write each call with
// its key and English as literals on one line: scripts/sync_options_localization.py
// collects them.
#pragma once

#include <string>

namespace BZROpenShim
{
namespace L10n
{
    // The text for the game's language, or `english` when there is no cell.
    // The returned pointer is valid for the life of the process.
    const char* ShimText(const char* key, const char* english);

    // ShimText with one %s replaced by `arg` (appended when the cell has no %s).
    std::string ShimFormat(const char* key, const char* english, const std::string& arg);
}
}
