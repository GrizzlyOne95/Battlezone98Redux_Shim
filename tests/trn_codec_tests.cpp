#include "trn_codec.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    int g_failures = 0;

    std::vector<uint8_t> Bytes(const char* text)
    {
        const auto* begin = reinterpret_cast<const uint8_t*>(text);
        return std::vector<uint8_t>(begin, begin + std::char_traits<char>::length(text));
    }

    void Expect(bool condition, const char* message)
    {
        if (condition)
            return;
        ++g_failures;
        std::cerr << "FAIL: " << message << '\n';
    }

    void ExpectCanonical(const std::vector<uint8_t>& input, const std::vector<uint8_t>& expected,
        const char* label)
    {
        const BZROpenShim::TrnCanonicalResult result = BZROpenShim::CanonicalizeTrnBytes(input);
        Expect(result.status == BZROpenShim::TrnCodecStatus::Ok, label);
        Expect(result.serializedCrLf == expected, label);

        const BZROpenShim::TrnCanonicalResult repeated =
            BZROpenShim::CanonicalizeTrnBytes(result.serializedCrLf);
        Expect(repeated.status == BZROpenShim::TrnCodecStatus::Ok, "repeated status");
        Expect(repeated.serializedCrLf == result.serializedCrLf, "repeated save byte identity");
        Expect(!repeated.changed, "canonical repeated save reports unchanged");
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
    Expect(cp1252.status == BZROpenShim::TrnCodecStatus::Ok, "CP1252 accepted");
    Expect(cp1252.sourceEncoding == BZROpenShim::TrnSourceEncoding::Windows1252,
        "CP1252 detected after invalid UTF-8 fallback");
    Expect(cp1252.serializedCrLf == cp1252Expected, "CP1252 preserved deterministically");

    const std::vector<uint8_t> utf16Le = { 0xFF, 0xFE, '[', 0, 'A', 0, ']', 0, '\r', 0, '\n', 0 };
    const std::vector<uint8_t> utf16Be = { 0xFE, 0xFF, 0, '[', 0, 'A', 0, ']', 0, '\r', 0, '\n' };
    const std::vector<uint8_t> utf16NoBom = { '[', 0, 'A', 0, ']', 0, '\n', 0 };
    Expect(BZROpenShim::CanonicalizeTrnBytes(utf16Le).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "UTF-16LE rejected explicitly");
    Expect(BZROpenShim::CanonicalizeTrnBytes(utf16Be).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "UTF-16BE rejected explicitly");
    Expect(BZROpenShim::CanonicalizeTrnBytes(utf16NoBom).status ==
        BZROpenShim::TrnCodecStatus::UnsupportedUtf16, "unmarked UTF-16 rejected explicitly");

    const auto corrupt = BZROpenShim::CanonicalizeTrnBytes(Bytes("A=1\r\r\nB=2\r\n"));
    Expect(corrupt.logicalLf == Bytes("A=1\nB=2\n"),
        "one corrupted terminator does not create a blank logical record");

    if (g_failures != 0)
        return EXIT_FAILURE;
    std::cout << "TRN codec regression matrix passed\n";
    return EXIT_SUCCESS;
}
