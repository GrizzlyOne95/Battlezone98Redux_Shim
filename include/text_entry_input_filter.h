#pragma once

// Character policy for the OpenShim-owned lobby text entries (nicknames and
// the pre-lobby Custom server box). Stock cUI_TextEntry::AppendChar
// (0x007CFA70) handles Enter and Backspace, drops Tab, and appends every other
// byte to its std::string, control codes included. A Ctrl+V (0x16) stored that
// way is invisible in the entry but makes the server host invalid.
// Pure functions so the host tests can cover them.

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

namespace BZROpenShim
{
namespace TextEntryInput
{
    enum class CharAction
    {
        Pass,   // hand to stock AppendChar
        Drop,   // a control code: never reaches the entry
        Paste,  // Ctrl+V: feed the clipboard text instead
    };

    constexpr uint8_t kCtrlV = 0x16;

    // Upper bound on characters fed from one paste. The entries' own input
    // limits (80 for the server box) still apply through stock AppendChar.
    constexpr size_t kMaxPasteChars = 256;

    inline CharAction Classify(uint8_t c)
    {
        if (c == kCtrlV)
            return CharAction::Paste;
        if (c == 0x08 || c == '\r' || c == '\n')
            return CharAction::Pass;
        if (c < 0x20 || c == 0x7F)
            return CharAction::Drop;
        return CharAction::Pass;
    }

    inline bool IsPastableChar(uint32_t c)
    {
        return c >= 0x20 && c <= 0x7E;
    }

    // The characters a paste feeds, in order: printable ASCII only, up to the
    // first line break (a pasted multi-line block never sends Enter). Works
    // for CF_TEXT (char) and CF_UNICODETEXT (wchar_t); anything outside
    // 0x20-0x7E is skipped.
    template <typename CharT>
    std::string PastableText(const CharT* text, size_t maxChars = kMaxPasteChars)
    {
        std::string out;
        if (!text)
            return out;
        for (; *text && out.size() < maxChars; ++text)
        {
            const uint32_t c = static_cast<uint32_t>(
                static_cast<typename std::make_unsigned<CharT>::type>(*text));
            if (c == '\r' || c == '\n')
                break;
            if (IsPastableChar(c))
                out.push_back(static_cast<char>(c));
        }
        return out;
    }
}
}
