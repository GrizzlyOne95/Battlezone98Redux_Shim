#pragma once

// Engine-independent rules for multi-page mission briefings
// (docs/BRIEFING_PAGES.md). The pre-launch briefing screen shows page 1 from
// the stock files; page N >= 2 of mission <m> is <m>_N.des, with optional
// <m>_Np.des (sidebar), <m>_N.ogv or <m>_N.png (media) and <m>_N.wav.
#include <cstdint>
#include <functional>
#include <string>

namespace BZROpenShim::BriefingPagesPolicy
{
    constexpr int kMaxPages = 9;
    // Longest resource name the game's lookup is trusted with (the game copies
    // names into a 0x14-byte local before indexing; see the RE note).
    constexpr size_t kMaxNameLength = 15;
    // Longest suffix appended to the base: "_9p.des".
    constexpr size_t kLongestSuffix = 7;

    enum class MediaKind
    {
        Inherit, // no page media: keep page 1's display
        Image,
        Video,
    };

    struct PageFiles
    {
        std::string des;
        std::string sidebar; // empty: keep page 1's sidebar
        std::string media;   // empty: keep page 1's display
        MediaKind mediaKind = MediaKind::Inherit;
        std::string wav;     // empty: silence
    };

    using ExistsFn = std::function<bool(const std::string&)>;

    // The description loader is handed "<m>.des" (or "<m>.bzn"); it cuts the
    // name at the first '.', so the base is the same cut.
    inline std::string MissionBaseFromDesArg(const char* name)
    {
        if (!name)
            return {};
        std::string base(name);
        const size_t dot = base.find('.');
        if (dot != std::string::npos)
            base.resize(dot);
        return base;
    }

    // suffix is one of ".des", "p.des", ".png", ".ogv", ".wav".
    inline std::string PageFileName(const std::string& base, int page, const char* suffix)
    {
        std::string name = base;
        name += '_';
        name += static_cast<char>('0' + page);
        name += suffix;
        return name;
    }

    inline bool NamesFit(const std::string& base)
    {
        return !base.empty() && base.size() + kLongestSuffix <= kMaxNameLength;
    }

    // Page 1 always exists; pages 2..kMaxPages count while <m>_N.des exists.
    inline int CountPages(const std::string& base, const ExistsFn& exists)
    {
        if (!NamesFit(base) || !exists)
            return 1;
        int count = 1;
        for (int page = 2; page <= kMaxPages; ++page)
        {
            if (!exists(PageFileName(base, page, ".des")))
                break;
            count = page;
        }
        return count;
    }

    inline PageFiles ResolvePage(const std::string& base, int page, const ExistsFn& exists)
    {
        PageFiles files;
        files.des = PageFileName(base, page, ".des");
        const std::string sidebar = PageFileName(base, page, "p.des");
        if (exists(sidebar))
            files.sidebar = sidebar;
        const std::string ogv = PageFileName(base, page, ".ogv");
        const std::string png = PageFileName(base, page, ".png");
        if (exists(ogv))
        {
            files.media = ogv;
            files.mediaKind = MediaKind::Video;
        }
        else if (exists(png))
        {
            files.media = png;
            files.mediaKind = MediaKind::Image;
        }
        const std::string wav = PageFileName(base, page, ".wav");
        if (exists(wav))
            files.wav = wav;
        return files;
    }

    // No wraparound.
    inline int ClampPage(int page, int count)
    {
        if (count < 1)
            count = 1;
        return page < 1 ? 1 : (page > count ? count : page);
    }

    // VK_LEFT/VK_PRIOR go back, VK_RIGHT/VK_NEXT go forward; others are not ours.
    inline int StepForKey(uint32_t vk)
    {
        switch (vk)
        {
        case 0x25: // VK_LEFT
        case 0x21: // VK_PRIOR
            return -1;
        case 0x27: // VK_RIGHT
        case 0x22: // VK_NEXT
            return 1;
        default:
            return 0;
        }
    }

    // The text block stores its text as "%<colour index><text>". The game's
    // colour indexes are 0..4, always one digit, so a page that itself starts
    // with a digit is not misread. Returns false when the prefix is absent,
    // leaving the output untouched.
    inline bool ParseColourPrefix(const char* stored, int& colourIndex)
    {
        if (!stored || stored[0] != '%' || stored[1] < '0' || stored[1] > '9')
            return false;
        colourIndex = stored[1] - '0';
        return true;
    }
}
