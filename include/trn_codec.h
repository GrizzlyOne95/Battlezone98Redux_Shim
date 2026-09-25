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
    //
    // Whole-file only: the encoding is decided from the complete byte
    // sequence and the result carries exactly one trailing LF. Feeding it a
    // chunk of a file yields a blank record or a split key at the chunk
    // boundary, so a streaming producer must accumulate until the file is
    // complete. The Redux producer hook relies on the game's writer issuing
    // one fwrite per file (see redux_compatibility.cpp).
    TrnCanonicalResult CanonicalizeTrnBytes(const std::vector<uint8_t>& input);

    const char* TrnCodecStatusName(TrnCodecStatus status);
    const char* TrnSourceEncodingName(TrnSourceEncoding encoding);
}
