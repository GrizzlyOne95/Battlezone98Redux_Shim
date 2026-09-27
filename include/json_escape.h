#pragma once

// Escape text for use inside a JSON string literal.
//
// Three copies used to exist (audit P2-3). The BZRNet structured trace and the
// DX11 colorspace probe wrote control bytes as \u00XX; the BZRNet
// instrumentation wrote them as '?', which lost the byte and disagreed with
// the trace it feeds. This is the \u00XX form.
//
// Bytes at or above 0x80 pass through unchanged, so UTF-8 text stays UTF-8.

#include <string>

namespace BZROpenShim
{
    inline std::string EscapeJsonString(const std::string& input)
    {
        static const char kHex[] = "0123456789abcdef";
        std::string out;
        out.reserve(input.size() + 8);
        for (const unsigned char c : input)
        {
            switch (c)
            {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\b': out += "\\b"; break;
            case '\f': out += "\\f"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20)
                {
                    out += "\\u00";
                    out.push_back(kHex[c >> 4]);
                    out.push_back(kHex[c & 0x0F]);
                }
                else
                {
                    out.push_back(static_cast<char>(c));
                }
                break;
            }
        }
        return out;
    }
}
