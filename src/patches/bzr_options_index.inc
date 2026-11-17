// Included right after bzr_options_registry.inc, inside BZROpenShim::Hooks
// (bzr_options_ui.cpp) and by tests/options_ui_l10n_tests.cpp. Kept out of the
// registry file because scripts/sync_options_localization.py tokenizes that
// file as pure data.

// Index of the row value an ini string selects (case-insensitive, ignoring
// spaces, underscores and hyphens, like the feature parsers). Boolean words
// are accepted on rows that are plain on/off, inverted on/off or unit-VO.
// Unrecognized text selects the row's default.
static size_t ShimSettingIndexFromText(const ShimSettingDescriptor& setting, const std::string& value)
{
    std::string normalized;
    normalized.reserve(value.size());
    for (char ch : value)
    {
        if (ch == ' ' || ch == '\t' || ch == '_' || ch == '-')
            continue;
        normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }

    for (size_t index = 0; index < setting.valueCount; ++index)
    {
        std::string candidate;
        for (const char* cursor = setting.values[index]; *cursor; ++cursor)
        {
            if (*cursor == ' ' || *cursor == '_' || *cursor == '-')
                continue;
            candidate.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(*cursor))));
        }
        if (normalized == candidate)
            return index;
    }

    bool token = false;
    if (setting.values == kShimSettingsOnOffValues && BZROpenShim::BoolToken::TryParse(normalized, token))
        return token ? 0 : 1;
    // The key disables the feature, so a true word means the row's Off.
    if (setting.values == kShimSettingsInvertedOnOffValues && BZROpenShim::BoolToken::TryParse(normalized, token))
        return token ? 1 : 0;
    if (setting.values == kShimSettingsUnitVoValues && BZROpenShim::BoolToken::TryParse(normalized, token))
        return token ? 0 : 2;
    // LegacyTankAi was a bool: old true/false values read as All teams/Off.
    if (setting.values == kShimSettingsLegacyTankAiValues && BZROpenShim::BoolToken::TryParse(normalized, token))
        return token ? 1 : 0;
    // Turbo was a bool too: true/false read as All teams/Off.
    if (setting.values == kShimSettingsTurboValues && BZROpenShim::BoolToken::TryParse(normalized, token))
        return token ? 1 : 0;

    return setting.defaultIndex;
}
