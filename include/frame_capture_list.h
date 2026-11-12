#pragma once
#include <algorithm>
#include <charconv>
#include <cstdint>
#include <string_view>
#include <vector>

namespace BZROpenShim::FrameCapture
{
    // Upper bound on the frames one OPENSHIM_FRAME_CAPTURE list can expand to,
    // so a typo such as "1-4000000000" is rejected instead of allocating.
    constexpr size_t kMaxListedFrames = 100000;

    // Parses "600,1200" or "150-899,1200" (items separated by commas or
    // spaces, ranges inclusive) into sorted, unique frame numbers. Any
    // malformed item, a reversed range or an oversized expansion rejects the
    // whole list: returns false and leaves `frames` empty.
    inline bool ParseFrameList(std::string_view text, std::vector<uint32_t>& frames)
    {
        frames.clear();
        const char* p=text.data();
        const char* const end=p+text.size();
        auto isSep=[](char c){ return c==',' || c==' ' || c=='\t'; };
        size_t total=0;
        while (p<end)
        {
            if (isSep(*p)) { ++p; continue; }
            uint32_t first=0, last=0;
            auto r=std::from_chars(p,end,first);
            if (r.ec!=std::errc{}) { frames.clear(); return false; }
            p=r.ptr;
            last=first;
            if (p<end && *p=='-')
            {
                r=std::from_chars(p+1,end,last);
                if (r.ec!=std::errc{} || last<first) { frames.clear(); return false; }
                p=r.ptr;
            }
            if (p<end && !isSep(*p)) { frames.clear(); return false; }
            // Compared before adding so a full 32-bit range cannot wrap size_t.
            if (static_cast<size_t>(last-first)>=kMaxListedFrames-total) { frames.clear(); return false; }
            total+=static_cast<size_t>(last-first)+1;
            for (uint32_t f=first;; ++f)
            {
                frames.push_back(f);
                if (f==last) break;
            }
        }
        std::sort(frames.begin(),frames.end());
        frames.erase(std::unique(frames.begin(),frames.end()),frames.end());
        return !frames.empty();
    }
}
