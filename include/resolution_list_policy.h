#pragma once

#include <cmath>
#include <cstddef>

namespace BZROpenShim
{
    // Keep/skip policy for the options screen's resolution cycle list
    // (src/patches/resolution_list_filter.cpp). Pure, so it is unit tested.
    namespace ResolutionList
    {
        struct ModeSize
        {
            int w;
            int h;
        };

        inline constexpr ModeSize kCommonSizes[] = {
            {1280, 720},  {1366, 768},  {1600, 900},  {1920, 1080}, {2560, 1440}, {3840, 2160},
            {1280, 800},  {1440, 900},  {1680, 1050}, {1920, 1200}, {2560, 1600}, {2560, 1080},
            {3440, 1440}, {1024, 768},  {1280, 1024}, {1600, 1200},
        };
        inline constexpr double kAspectTolerance = 0.02;

        // Parses the leading "<w> x <h>" of an Ogre "Video Mode" string such as
        // "1920 x 1080 @ 32-bit colour". False means "could not tell".
        inline bool ParseModeSize(const char* text, int& w, int& h)
        {
            if (!text)
                return false;
            const char* p = text;
            const auto number = [&p](int& out) {
                if (*p < '0' || *p > '9')
                    return false;
                long value = 0;
                int digits = 0;
                while (*p >= '0' && *p <= '9')
                {
                    if (++digits > 5)
                        return false;
                    value = value * 10 + (*p - '0');
                    ++p;
                }
                out = static_cast<int>(value);
                return true;
            };
            const auto spaces = [&p]() {
                while (*p == ' ')
                    ++p;
            };
            spaces();
            if (!number(w))
                return false;
            spaces();
            if (*p != 'x' && *p != 'X')
                return false;
            ++p;
            spaces();
            return number(h) && w > 0 && h > 0;
        }

        inline bool IsCommonSize(int w, int h)
        {
            for (const ModeSize& size : kCommonSizes)
                if (size.w == w && size.h == h)
                    return true;
            return false;
        }

        // WxH pairs already added to the list being built.
        struct SeenSizes
        {
            static constexpr size_t kCapacity = 64;
            ModeSize sizes[kCapacity];
            size_t count = 0;

            void Clear() { count = 0; }
            bool Contains(int w, int h) const
            {
                for (size_t i = 0; i < count; ++i)
                    if (sizes[i].w == w && sizes[i].h == h)
                        return true;
                return false;
            }
            // A full table stops recording, so later duplicates are kept
            // (stock behaviour) rather than dropped wrongly.
            void Add(int w, int h)
            {
                if (count < kCapacity)
                    sizes[count++] = ModeSize{w, h};
            }
        };

        // Decides one mode. desktopW/H <= 0 means the desktop size is unknown:
        // the common-size and aspect test is then skipped (the mode is kept).
        inline bool ShouldKeep(int w, int h, int desktopW, int desktopH, bool isCurrent, SeenSizes& seen)
        {
            bool keep;
            if (isCurrent)
                keep = true;
            else if (seen.Contains(w, h))
                keep = false;
            else if (desktopW <= 0 || desktopH <= 0)
                keep = true;
            else if (w == desktopW && h == desktopH)
                keep = true;
            else
                keep = IsCommonSize(w, h) &&
                       std::fabs(static_cast<double>(w) / h - static_cast<double>(desktopW) / desktopH) <=
                           kAspectTolerance;
            if (keep && !seen.Contains(w, h))
                seen.Add(w, h);
            return keep;
        }
    }
}
