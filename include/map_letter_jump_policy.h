#pragma once

// Ctrl+letter "quick jump" in the multiplayer Create Game map list, as pure
// rules with no Windows or engine dependency so the tests can drive them. The
// engine side lives in src/patches/mp_map_filter_extras.cpp.

#include <cstddef>

namespace BZROpenShim
{
namespace MapLetterJump
{
    // Ctrl+A..Ctrl+Z arrive as the control codes 0x01..0x1A. Returns the
    // lower-case letter, or 0 for any other character. The caller must also
    // check that Ctrl is held: Backspace, Tab, Ctrl+Enter and Enter produce
    // 0x08, 0x09, 0x0A and 0x0D as well.
    inline char LetterFromControlCode(unsigned char character)
    {
        return (character >= 0x01 && character <= 0x1A) ? static_cast<char>('a' + character - 1) : 0;
    }

    namespace Detail
    {
        inline char Lower(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }
    }

    // Index of the next title whose first character is `letter` (ASCII,
    // case-insensitive), searching from the row after `current` and wrapping.
    // The current row is tried last, so it is returned only when it is the
    // sole match. A `current` outside [0, count) means no usable selection:
    // the search starts at the top. Returns -1 for no match, an empty list, a
    // zero letter or a null array; null titles never match.
    inline int FindNextByLetter(const char* const* titles, size_t count, int current, char letter)
    {
        if (!titles || count == 0 || letter == 0)
            return -1;
        const bool haveCurrent = current >= 0 && static_cast<size_t>(current) < count;
        const size_t start = haveCurrent ? static_cast<size_t>(current) + 1 : 0;
        const char wanted = Detail::Lower(letter);
        for (size_t step = 0; step < count; ++step)
        {
            const size_t index = (start + step) % count;
            const char* title = titles[index];
            if (title && title[0] != '\0' && Detail::Lower(title[0]) == wanted)
                return static_cast<int>(index);
        }
        return -1;
    }
}
}
