// trn_codec.h
// Deterministic Battlezone Redux TRN text normalization and serialization.

#pragma once

#include <cstdint>
#include <vector>

namespace BZROpenShim
{
    enum class TrnCodecStatus : uint8_t
    {
        Ok,
        UnsupportedUtf16,
        InvalidUtf8Bom,
        UnrepresentableWindows1252,
    };

    enum class TrnSourceEncoding : uint8_t
    {
        Windows1252,
        Utf8,
        Utf8Bom,
        Utf16,
    };

    struct TrnCanonicalResult
    {
        TrnCodecStatus status = TrnCodecStatus::Ok;
        TrnSourceEncoding sourceEncoding = TrnSourceEncoding::Windows1252;
        std::vector<uint8_t> logicalLf;
        std::vector<uint8_t> serializedCrLf;
        bool changed = false;
    };

    // Redux's parser treats LF as the only record delimiter. This decoder
    // makes that contract explicit, accepts historical CP1252 and UTF-8, and
    // collapses a corrupt CR run followed by LF to one logical terminator.
    TrnCanonicalResult CanonicalizeTrnBytes(const std::vector<uint8_t>& input);

    const char* TrnCodecStatusName(TrnCodecStatus status);
    const char* TrnSourceEncodingName(TrnSourceEncoding encoding);
}
