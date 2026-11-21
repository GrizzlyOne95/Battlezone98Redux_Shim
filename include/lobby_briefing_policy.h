#pragma once

// Engine-independent rules for the multiplayer lobby Briefing overlay
// (Docs/LOBBY_BRIEFING.md). Page 1 is <stem>.des, pages 2..9 are <stem>_N.des
// (BriefingPagesPolicy), and page N's image is <stem>_N.png.
#include "briefing_pages_policy.h"
#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim::LobbyBriefingPolicy
{
    namespace Pages = BriefingPagesPolicy;

    // The text block keeps its text in a 0x2800-byte buffer filled by
    // _snprintf, which leaves no terminator when it truncates; the "%<n>"
    // colour prefix takes two bytes of it.
    constexpr size_t kMaxPageTextChars = 0x2700;

    enum class KeyAction
    {
        None,
        Close,
        Prev,
        Next,
        ScrollUp,
        ScrollDown,
    };

    // The lobby record names the map file ("name.bzn"); the stem is the file
    // name without its folder, cut at the first '.' as the .des loader
    // (DescriptionFileLoad) and BriefingPagesPolicy::MissionBaseFromDesArg do.
    inline std::string MissionStemFromMapFile(const std::string& file)
    {
        std::string stem = file;
        const size_t slash = stem.find_last_of("/\\");
        if (slash != std::string::npos)
            stem.erase(0, slash + 1);
        const size_t dot = stem.find('.');
        if (dot != std::string::npos)
            stem.resize(dot);
        return stem;
    }

    inline std::string PageOneFileName(const std::string& stem)
    {
        return stem + ".des";
    }

    inline bool HasBriefing(const std::string& stem, const Pages::ExistsFn& exists)
    {
        const std::string first = PageOneFileName(stem);
        return !stem.empty() && first.size() <= Pages::kMaxNameLength && exists && exists(first);
    }

    // 0 when the map has no <stem>.des; otherwise 1 + the consecutive
    // <stem>_N.des pages (BriefingPagesPolicy::CountPages).
    inline int CountPages(const std::string& stem, const Pages::ExistsFn& exists)
    {
        if (!HasBriefing(stem, exists))
            return 0;
        return Pages::CountPages(stem, exists);
    }

    inline std::string PageTextFileName(const std::string& stem, int page)
    {
        return page <= 1 ? PageOneFileName(stem) : Pages::PageFileName(stem, page, ".des");
    }

    inline std::string PageImageFileName(const std::string& stem, int page)
    {
        return Pages::PageFileName(stem, page, ".png");
    }

    inline std::string ClipPageText(const std::string& text)
    {
        return text.size() <= kMaxPageTextChars ? text : text.substr(0, kMaxPageTextChars);
    }

    // Esc closes; Left/PgUp and Right/PgDn turn pages (as the SP briefing
    // pages); Up/Down scroll the text.
    inline KeyAction ActionForKey(uint32_t vk)
    {
        if (vk == 0x1B) // VK_ESCAPE
            return KeyAction::Close;
        if (vk == 0x26) // VK_UP
            return KeyAction::ScrollUp;
        if (vk == 0x28) // VK_DOWN
            return KeyAction::ScrollDown;
        const int step = Pages::StepForKey(vk);
        if (step < 0)
            return KeyAction::Prev;
        if (step > 0)
            return KeyAction::Next;
        return KeyAction::None;
    }
}
