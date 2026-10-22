#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Translated text for the OpenShim options screens.
//
// The table has the same shape as the game's own localization_table.csv:
// tilde-separated, a `Key~English~French~German~Spanish~Italian~Russian~Portuguese`
// header, ANSI bytes (cp1252, cp1251 in the Russian column), and lines that
// are empty or start with '~' are spacers. OpenShim reads it itself rather
// than through the engine, because the engine loads exactly one
// localization_table.csv (an addon's copy replaces stock) and shows
// "{ ns | key }" for a miss instead of English. See
// Docs/OPTIONS_UI_LOCALIZATION.md.
//
// Pure std code: tests/options_ui_l10n_tests.cpp links it on the host.
namespace BZROpenShim::OptionsL10n
{
    // The engine's language numbers (FUN_0081DEE0 in the GOG exe): the
    // play_options language, falling back to the system LCID. The engine
    // swaps the file's last two columns on load, so 6 is Portuguese and 7 is
    // Russian (the one that loads the cp1251 font sheet).
    enum Language : int
    {
        English = 1,
        French = 2,
        German = 3,
        Spanish = 4,
        Italian = 5,
        Portuguese = 6,
        Russian = 7,
    };
    constexpr int kLanguageCount = 7;

    // Header names, indexed by Language - 1.
    extern const char* const kLanguageColumnNames[kLanguageCount];

    class Table
    {
    public:
        // Replaces the contents. False (with a reason) when the header is
        // missing or lacks the English column; rows are kept either way.
        bool Parse(std::string_view text, std::string* error = nullptr);

        // The cell for `key` in `language`, or null when the key, the column
        // or the text is missing. Never an empty string.
        const char* Find(std::string_view key, int language) const;

        bool Has(std::string_view key) const { return m_Rows.count(std::string(key)) != 0; }
        size_t Size() const { return m_Rows.size(); }
        // Keys in file order; duplicates are listed each time they appear.
        const std::vector<std::string>& KeysInOrder() const { return m_Order; }

    private:
        std::unordered_map<std::string, std::vector<std::string>> m_Rows; // cells by Language - 1
        std::vector<std::string> m_Order;
    };

    // The first non-empty translation of `keys` in order, else `english`.
    // English (or an unknown language) always returns `english`, so the
    // compiled strings stay the authority and nothing can render blank.
    const char* Pick(const Table& table, int language, const std::string* keys, size_t keyCount,
                     const char* english);

    // ASCII letters and digits only: "Reticle & Hits" -> "ReticleHits".
    std::string Slug(const char* text);

    // Key builders. A settings row is named by its openshim.ini key (never
    // renamed); a row without one (an action row) by the slug of its English
    // label. Value labels are named by the ini value they write, so
    // reordering a ladder cannot shift translations.
    std::string RowKey(const char* iniKey, const char* label, const char* field); // field: label|desc
    std::string RowValueKey(const char* iniKey, const char* label, const char* value);
    // Shared wording for value labels ("On", "Stock", "50%"): translated once
    // and used by every row whose own value key is untranslated.
    std::string CommonValueKey(const char* english);
    std::string CategoryKey(const char* name, const char* field); // field: name|title|blurb
}
