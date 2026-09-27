#pragma once

// The on/off words OpenShim accepts in openshim.ini values and OPENSHIM_*
// environment variables.
//
//   true:  1  true  on   yes  enabled
//   false: 0  false off  no   disabled
//
// Matching ignores case and surrounding ASCII whitespace. Anything else is
// unrecognized, and each caller decides what that means (usually its default).
//
// Nine files used to spell this list out, and three had drifted (audit P2-3):
// two did not know enabled/disabled, and two dropped whitespace inside the
// word as well as around it. Callers that accept extra words (unit VO's
// "reduced", the HUD layout's "legacy") check those first and fall back here.
//
// Header-only and free of Windows calls so the tests can include it.

#include <cstddef>
#include <cstring>
#include <string>

namespace BZROpenShim
{
namespace BoolToken
{
    namespace Detail
    {
        inline bool IsAsciiSpace(char c)
        {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f';
        }

        inline char ToLowerAscii(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        inline bool EqualsWord(const char* lower, size_t length, const char* word)
        {
            return std::strlen(word) == length && std::memcmp(lower, word, length) == 0;
        }
    }

    // Sets `out` and returns true when the text is one of the words above.
    // Leaves `out` untouched and returns false otherwise.
    inline bool TryParse(const char* text, size_t length, bool& out)
    {
        if (!text)
            return false;

        size_t begin = 0;
        size_t end = length;
        while (begin < end && Detail::IsAsciiSpace(text[begin]))
            ++begin;
        while (end > begin && Detail::IsAsciiSpace(text[end - 1]))
            --end;

        // The longest word is "disabled".
        char lower[8];
        const size_t size = end - begin;
        if (size == 0 || size > sizeof(lower))
            return false;
        for (size_t i = 0; i < size; ++i)
            lower[i] = Detail::ToLowerAscii(text[begin + i]);

        static const char* const kTrueWords[] = {"1", "true", "on", "yes", "enabled"};
        static const char* const kFalseWords[] = {"0", "false", "off", "no", "disabled"};
        for (const char* word : kTrueWords)
        {
            if (Detail::EqualsWord(lower, size, word))
            {
                out = true;
                return true;
            }
        }
        for (const char* word : kFalseWords)
        {
            if (Detail::EqualsWord(lower, size, word))
            {
                out = false;
                return true;
            }
        }
        return false;
    }

    inline bool TryParse(const char* text, bool& out)
    {
        return text != nullptr && TryParse(text, std::strlen(text), out);
    }

    inline bool TryParse(const std::string& text, bool& out)
    {
        return TryParse(text.data(), text.size(), out);
    }
}
}
