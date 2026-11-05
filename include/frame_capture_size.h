#pragma once
#include <charconv>
#include <string_view>

namespace BZROpenShim::FrameCapture
{
    struct Size { int width=0, height=0; };
    inline Size ParseSize(std::string_view text)
    {
        const auto split=text.find('x');
        if (split==std::string_view::npos) return {};
        Size size;
        const auto end=text.data()+text.size();
        const auto w=std::from_chars(text.data(),text.data()+split,size.width);
        const auto h=std::from_chars(text.data()+split+1,end,size.height);
        if (w.ec!=std::errc{} || h.ec!=std::errc{} || w.ptr!=text.data()+split || h.ptr!=end ||
            size.width<320 || size.width>7680 || size.height<200 || size.height>4320) return {};
        return size;
    }
}
