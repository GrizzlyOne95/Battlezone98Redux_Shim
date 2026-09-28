#include "trn_codec.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    std::vector<uint8_t> Bytes(const char* text)
    {
        const auto* begin = reinterpret_cast<const uint8_t*>(text);
        return std::vector<uint8_t>(begin, begin + std::char_traits<char>::length(text));
    }

    void ExpectCanonical(const std::vector<uint8_t>& input, const std::vector<uint8_t>& expected,
        const char* label)
    {
        const BZROpenShim::TrnCanonicalResult result = BZROpenShim::CanonicalizeTrnBytes(input);
        Check(result.status == BZROpenShim::TrnCodecStatus::Ok, label);
        Check(result.serializedCrLf == expected, label);

        const BZROpenShim::TrnCanonicalResult repeated =
            BZROpenShim::CanonicalizeTrnBytes(result.serializedCrLf);
        Check(repeated.status == BZROpenShim::TrnCodecStatus::Ok, "repeated status");
        Check(repeated.serializedCrLf == result.serializedCrLf, "repeated save byte identity");
        Check(!repeated.changed, "canonical repeated save reports unchanged");
    }
}

int main()
{
    const std::vector<uint8_t> canonical = Bytes("[A]\r\nX=1\r\nY=2\r\n");
    ExpectCanonical(Bytes("[A]\nX=1\nY=2\n"), canonical, "LF input");
    ExpectCanonical(Bytes("[A]\r\nX=1\r\nY=2\r\n"), canonical, "CRLF input");
    ExpectCanonical(Bytes("[A]\rX=1\rY=2\r"), canonical, "CR-only input");
    ExpectCanonical(Bytes("[A]\r\r\nX=1\r\r\r\nY=2\r\r\n"), canonical, "CRCRLF input");
    ExpectCanonical(Bytes("[A]\nX=1\nY=2"), canonical, "no final newline");

    std::vector<uint8_t> utf8Bom = { 0xEF, 0xBB, 0xBF };
    const std::vector<uint8_t> utf8Body = {
        '[', 'A', ']', '\n', 'N', 'A', 'M', 'E', '=', 'c', 'a', 'f', 0xC3, 0xA9, '\n'
    };
    utf8Bom.insert(utf8Bom.end(), utf8Body.begin(), utf8Body.end());
    const std::vector<uint8_t> cp1252Expected = {
        '[', 'A', ']', '\r', '\n', 'N', 'A', 'M', 'E', '=', 'c', 'a', 'f', 0xE9, '\r', '\n'
    };
    ExpectCanonical(utf8Bom, cp1252Expected, "UTF-8 BOM input");
    ExpectCanonical(utf8Body, cp1252Expected, "UTF-8 no-BOM input");

    const std::vector<uint8_t> cp1252Input = {
        '[', 'A', ']', '\r', '\n', 'N', 'A', 'M', 'E', '=', 'c', 'a', 'f', 0xE9, '\r', '\n'
    };
    const auto cp1252 = BZROpenShim::CanonicalizeTrnBytes(cp1252Input);
    Check(cp1252.status == BZROpenShim::TrnCodecStatus::Ok, "CP1252 accepted");
    Check(cp1252.sourceEncoding == BZROpenShim::TrnSourceEncoding::Windows1252,
        "CP1252 detected after invalid UTF-8 fallback");
    Check(cp1252.serializedCrLf == cp1252Expected, "CP1252 preserved deterministically");

    const std::vector<uint8_t> utf16Le = { 0xFF, 0xFE, '[', 0, 'A', 0, ']', 0, '\r', 0, '\n', 0 };
    const std::vector<uint8_t> utf16Be = { 0xFE, 0xFF, 0, '[', 0, 'A', 0, ']', 0, '\r', 0, '\n' };
    const std::vector<uint8_t> utf16NoBom = { '[', 0, 'A', 0, ']', 0, '\n', 0 };
    Check(BZROpenShim::CanonicalizeTrnBytes(utf16Le).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "UTF-16LE rejected explicitly");
    Check(BZROpenShim::CanonicalizeTrnBytes(utf16Be).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "UTF-16BE rejected explicitly");
    Check(BZROpenShim::CanonicalizeTrnBytes(utf16NoBom).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "unmarked UTF-16 rejected explicitly");

    const auto corrupt = BZROpenShim::CanonicalizeTrnBytes(Bytes("A=1\r\r\nB=2\r\n"));
    Check(corrupt.logicalLf == Bytes("A=1\nB=2\n"),
        "one corrupted terminator does not create a blank logical record");

    // The codec is a whole-file transform, not a chunk filter. The producer
    // hook in redux_compatibility.cpp applies it per fwrite only because the
    // game's TRN writer issues exactly one fwrite per file; this pins why that
    // proof matters, so a writer that splits a file is never paired with this
    // codec unchanged. Splitting inside a CRLF adds a blank record; splitting
    // inside a line splits the key from its value.
    {
        const std::vector<uint8_t> whole = Bytes("[A]\r\nX=1\r\nY=2\r\n");
        const auto canonicalizeSplit = [&whole](size_t at)
        {
            const std::vector<uint8_t> head(whole.begin(), whole.begin() + static_cast<std::ptrdiff_t>(at));
            const std::vector<uint8_t> tail(whole.begin() + static_cast<std::ptrdiff_t>(at), whole.end());
            std::vector<uint8_t> joined = BZROpenShim::CanonicalizeTrnBytes(head).serializedCrLf;
            const std::vector<uint8_t> rest = BZROpenShim::CanonicalizeTrnBytes(tail).serializedCrLf;
            joined.insert(joined.end(), rest.begin(), rest.end());
            return joined;
        };
        Check(BZROpenShim::CanonicalizeTrnBytes(whole).serializedCrLf == whole,
            "the whole sample is already canonical");
        Check(canonicalizeSplit(4) == Bytes("[A]\r\n\r\nX=1\r\nY=2\r\n"),
            "chunking inside a CRLF yields a blank record: the codec is whole-file only");
        Check(canonicalizeSplit(7) == Bytes("[A]\r\nX=\r\n1\r\nY=2\r\n"),
            "chunking inside a line splits the key: the codec is whole-file only");
    }

    if (OpenShimTest::FailureCount() != 0)
        return EXIT_FAILURE;
    std::cout << "TRN codec regression matrix passed\n";
    return EXIT_SUCCESS;
}
