// trn_codec.cpp

#include "trn_codec.h"

#include <algorithm>
#include <array>
#include <cstddef>

namespace BZROpenShim
{
    namespace
    {
        bool LooksLikeUtf16WithoutBom(const std::vector<uint8_t>& input)
        {
            if (input.size() < 4)
                return false;

            size_t evenNuls = 0;
            size_t oddNuls = 0;
            for (size_t i = 0; i < input.size(); ++i)
            {
                if (input[i] != 0)
                    continue;
                if ((i & 1u) == 0)
                    ++evenNuls;
                else
                    ++oddNuls;
            }

            const size_t pairs = input.size() / 2;
            return pairs > 0 && (evenNuls * 4 >= pairs * 3 || oddNuls * 4 >= pairs * 3);
        }

        bool DecodeUtf8(const uint8_t* bytes, size_t length, std::vector<uint32_t>& outCodePoints)
        {
            outCodePoints.clear();
            outCodePoints.reserve(length);

            for (size_t i = 0; i < length;)
            {
                const uint8_t first = bytes[i++];
                if (first < 0x80)
                {
                    outCodePoints.push_back(first);
                    continue;
                }

                uint32_t codePoint = 0;
                size_t continuationCount = 0;
                uint32_t minimum = 0;
                if ((first & 0xE0) == 0xC0)
                {
                    codePoint = first & 0x1F;
                    continuationCount = 1;
                    minimum = 0x80;
                }
                else if ((first & 0xF0) == 0xE0)
                {
                    codePoint = first & 0x0F;
                    continuationCount = 2;
                    minimum = 0x800;
                }
                else if ((first & 0xF8) == 0xF0)
                {
                    codePoint = first & 0x07;
                    continuationCount = 3;
                    minimum = 0x10000;
                }
                else
                {
                    return false;
                }

                if (continuationCount > length - i)
                    return false;
                for (size_t j = 0; j < continuationCount; ++j)
                {
                    const uint8_t next = bytes[i++];
                    if ((next & 0xC0) != 0x80)
                        return false;
                    codePoint = (codePoint << 6) | (next & 0x3F);
                }

                if (codePoint < minimum || codePoint > 0x10FFFF ||
                    (codePoint >= 0xD800 && codePoint <= 0xDFFF))
                {
                    return false;
                }
                outCodePoints.push_back(codePoint);
            }
            return true;
        }

        bool EncodeWindows1252(const std::vector<uint32_t>& codePoints, std::vector<uint8_t>& output)
        {
            struct Mapping
            {
                uint32_t codePoint;
                uint8_t byte;
            };
            static constexpr std::array<Mapping, 27> kMappings = {{
                {0x20AC, 0x80}, {0x201A, 0x82}, {0x0192, 0x83}, {0x201E, 0x84},
                {0x2026, 0x85}, {0x2020, 0x86}, {0x2021, 0x87}, {0x02C6, 0x88},
                {0x2030, 0x89}, {0x0160, 0x8A}, {0x2039, 0x8B}, {0x0152, 0x8C},
                {0x017D, 0x8E}, {0x2018, 0x91}, {0x2019, 0x92}, {0x201C, 0x93},
                {0x201D, 0x94}, {0x2022, 0x95}, {0x2013, 0x96}, {0x2014, 0x97},
                {0x02DC, 0x98}, {0x2122, 0x99}, {0x0161, 0x9A}, {0x203A, 0x9B},
                {0x0153, 0x9C}, {0x017E, 0x9E}, {0x0178, 0x9F},
            }};

            output.clear();
            output.reserve(codePoints.size());
            for (const uint32_t codePoint : codePoints)
            {
                if (codePoint <= 0x7F || (codePoint >= 0xA0 && codePoint <= 0xFF))
                {
                    output.push_back(static_cast<uint8_t>(codePoint));
                    continue;
                }

                const auto match = std::find_if(kMappings.begin(), kMappings.end(),
                    [codePoint](const Mapping& mapping) { return mapping.codePoint == codePoint; });
                if (match == kMappings.end())
                    return false;
                output.push_back(match->byte);
            }
            return true;
        }

        void NormalizeToLogicalLf(const std::vector<uint8_t>& input, std::vector<uint8_t>& output)
        {
            output.clear();
            output.reserve(input.size() + 1);
            for (size_t i = 0; i < input.size(); ++i)
            {
                if (input[i] == '\r')
                {
                    size_t runEnd = i + 1;
                    while (runEnd < input.size() && input[runEnd] == '\r')
                        ++runEnd;

                    if (runEnd < input.size() && input[runEnd] == '\n')
                    {
                        // CRCRLF is one text-mode-corrupted terminator, not a
                        // blank logical record. Consume the whole run and LF.
                        output.push_back('\n');
                        i = runEnd;
                    }
                    else
                    {
                        // Genuine CR-only input remains capable of expressing
                        // multiple logical records, including blank records.
                        output.insert(output.end(), runEnd - i, static_cast<uint8_t>('\n'));
                        i = runEnd - 1;
                    }
                }
                else
                {
                    output.push_back(input[i]);
                }
            }

            if (!output.empty())
            {
                while (!output.empty() && output.back() == '\n')
                    output.pop_back();
                output.push_back('\n');
            }
        }

        void SerializeCrLf(const std::vector<uint8_t>& logicalLf, std::vector<uint8_t>& output)
        {
            output.clear();
            output.reserve(logicalLf.size() + 32);
            for (const uint8_t byte : logicalLf)
            {
                if (byte == '\n')
                    output.push_back('\r');
                output.push_back(byte);
            }
        }
    }

    TrnCanonicalResult CanonicalizeTrnBytes(const std::vector<uint8_t>& input)
    {
        TrnCanonicalResult result;
        if ((input.size() >= 2 && input[0] == 0xFF && input[1] == 0xFE) ||
            (input.size() >= 2 && input[0] == 0xFE && input[1] == 0xFF) ||
            LooksLikeUtf16WithoutBom(input))
        {
            result.status = TrnCodecStatus::UnsupportedUtf16;
            result.sourceEncoding = TrnSourceEncoding::Utf16;
            return result;
        }

        const bool hasUtf8Bom = input.size() >= 3 &&
            input[0] == 0xEF && input[1] == 0xBB && input[2] == 0xBF;
        const size_t utf8Offset = hasUtf8Bom ? 3 : 0;
        std::vector<uint32_t> codePoints;
        const uint8_t* utf8Bytes = input.empty() ? nullptr : input.data() + utf8Offset;
        const bool validUtf8 = DecodeUtf8(utf8Bytes, input.size() - utf8Offset, codePoints);

        std::vector<uint8_t> decodedBytes;
        if (hasUtf8Bom && !validUtf8)
        {
            result.status = TrnCodecStatus::InvalidUtf8Bom;
            result.sourceEncoding = TrnSourceEncoding::Utf8Bom;
            return result;
        }

        if (validUtf8)
        {
            result.sourceEncoding = hasUtf8Bom ? TrnSourceEncoding::Utf8Bom : TrnSourceEncoding::Utf8;
            if (!EncodeWindows1252(codePoints, decodedBytes))
            {
                result.status = TrnCodecStatus::UnrepresentableWindows1252;
                return result;
            }
        }
        else
        {
            result.sourceEncoding = TrnSourceEncoding::Windows1252;
            decodedBytes = input;
        }

        NormalizeToLogicalLf(decodedBytes, result.logicalLf);
        SerializeCrLf(result.logicalLf, result.serializedCrLf);
        result.changed = result.serializedCrLf != input;
        return result;
    }

    const char* TrnCodecStatusName(TrnCodecStatus status)
    {
        switch (status)
        {
        case TrnCodecStatus::Ok: return "ok";
        case TrnCodecStatus::UnsupportedUtf16: return "unsupported-utf16";
        case TrnCodecStatus::InvalidUtf8Bom: return "invalid-utf8-bom";
        case TrnCodecStatus::UnrepresentableWindows1252: return "unrepresentable-windows-1252";
        }
        return "unknown";
    }

    const char* TrnSourceEncodingName(TrnSourceEncoding encoding)
    {
        switch (encoding)
        {
        case TrnSourceEncoding::Windows1252: return "windows-1252";
        case TrnSourceEncoding::Utf8: return "utf-8";
        case TrnSourceEncoding::Utf8Bom: return "utf-8-bom";
        case TrnSourceEncoding::Utf16: return "utf-16";
        }
        return "unknown";
    }
}
