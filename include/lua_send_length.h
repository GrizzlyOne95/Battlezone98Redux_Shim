// lua_send_length.h -- pure, host-testable half of the Lua Send string-length
// fix. Design, evidence and failure modes: Docs/LUA_SEND_STRING_LENGTH_20261018.md.
//
// The Lua network packet codec stores a string length (or table count) in the
// low five bits of the type byte, with 31 meaning "one extension byte follows".
// Stock decoders read that byte with MOVSX, so 128..255 become negative and the
// receiver faults. Stock encoders store the low byte of any length, so 256+
// wraps and desyncs the receiver. This header owns the byte-level facts and the
// builders for the encoder guard; lua_send_length.cpp owns the writes.

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace BZROpenShim
{
    namespace LuaSendLength
    {
        // Largest length/count the one-byte extension can carry.
        constexpr uint32_t kMaxWireLength = 0xFF;

        // movsx edx, byte [ecx]  ->  movzx edx, byte [ecx]: only byte 1 changes.
        constexpr uint8_t kDecoderOriginal[3] = { 0x0F, 0xBE, 0x11 };
        constexpr uint8_t kDecoderMovzxOpcode = 0xB6;
        constexpr size_t kDecoderFlipOffset = 1;

        inline bool DecoderSiteIsStock(const uint8_t* bytes)
        {
            return bytes[0] == kDecoderOriginal[0] && bytes[1] == kDecoderOriginal[1] &&
                   bytes[2] == kDecoderOriginal[2];
        }

        inline bool DecoderSiteIsPatched(const uint8_t* bytes)
        {
            return bytes[0] == kDecoderOriginal[0] && bytes[1] == kDecoderMovzxOpcode &&
                   bytes[2] == kDecoderOriginal[2];
        }

        // One encoder buffer-room check. The detour overwrites the first
        // `replayLen` bytes (whole instructions, no relative operands); the
        // stub replays them and resumes at site + replayLen. `failOffset` is
        // the stock `xor al,al / jmp epilogue` the room check already uses,
        // so a rejected length takes the same rollback-and-log path in Send
        // as an argument that does not fit the packet.
        struct EncoderSite
        {
            const char* resolveName;
            const uint8_t* expected;   // stock bytes from the site, verified before any write
            size_t expectedLen;
            size_t replayLen;
            size_t failOffset;
            int8_t countFrameOffset;   // [ebp + off] holding the length/count
        };

        // String encoder FUN_005058D0 @ 0x00505944:
        //   mov edx,[ebp+8] / mov eax,[edx] / mov ecx,[ebp-4] / lea edx,[eax+ecx+1]
        //   cmp edx,[ebp+0xC] / jb +4 / xor al,al / jmp short
        constexpr uint8_t kStringEncoderExpected[] = {
            0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x4D, 0xFC, 0x8D, 0x54, 0x08, 0x01,
            0x3B, 0x55, 0x0C, 0x72, 0x04, 0x32, 0xC0, 0xEB,
        };

        // Table encoder FUN_00505A10 @ 0x00505A7A:
        //   mov eax,[ebp+8] / mov ecx,[eax] / add ecx,1
        //   cmp ecx,[ebp+0xC] / jb +7 / xor al,al / jmp near
        constexpr uint8_t kTableEncoderExpected[] = {
            0x8B, 0x45, 0x08, 0x8B, 0x08, 0x83, 0xC1, 0x01,
            0x3B, 0x4D, 0x0C, 0x72, 0x07, 0x32, 0xC0, 0xE9,
        };

        constexpr EncoderSite kStringEncoder = {
            "Lua::PackString length room check", kStringEncoderExpected, sizeof(kStringEncoderExpected),
            12, 0x11, -4 };
        constexpr EncoderSite kTableEncoder = {
            "Lua::PackTable count room check", kTableEncoderExpected, sizeof(kTableEncoderExpected),
            8, 0x0D, -4 };

        constexpr const char* kStringDecoderName = "Lua::UnpackString length extension load";
        constexpr const char* kTableDecoderName = "Lua::UnpackTable count extension load";

        inline void PutRel32(std::vector<uint8_t>& out, uint32_t from, uint32_t to)
        {
            const uint32_t rel = to - from;
            for (int i = 0; i < 4; ++i)
                out.push_back(static_cast<uint8_t>(rel >> (8 * i)));
        }

        // Guard stub placed at stubAddr:
        //   cmp dword [ebp+off], 0xFF
        //   ja  site + failOffset
        //   <replayLen original bytes>
        //   jmp site + replayLen
        inline std::vector<uint8_t> BuildGuardStub(const EncoderSite& site, uint32_t siteAddr, uint32_t stubAddr)
        {
            std::vector<uint8_t> out;
            out.reserve(7 + 6 + site.replayLen + 5);
            const uint8_t cmp[] = { 0x81, 0x7D, static_cast<uint8_t>(site.countFrameOffset),
                                    static_cast<uint8_t>(kMaxWireLength), 0x00, 0x00, 0x00 };
            out.insert(out.end(), cmp, cmp + sizeof(cmp));
            out.push_back(0x0F);
            out.push_back(0x87);
            PutRel32(out, stubAddr + static_cast<uint32_t>(out.size()) + 4, siteAddr + static_cast<uint32_t>(site.failOffset));
            out.insert(out.end(), site.expected, site.expected + site.replayLen);
            out.push_back(0xE9);
            PutRel32(out, stubAddr + static_cast<uint32_t>(out.size()) + 4, siteAddr + static_cast<uint32_t>(site.replayLen));
            return out;
        }

        // jmp stub, padded with NOPs to the replayed length so the overwritten
        // range never holds a torn instruction.
        inline std::vector<uint8_t> BuildDetour(const EncoderSite& site, uint32_t siteAddr, uint32_t stubAddr)
        {
            std::vector<uint8_t> out;
            out.push_back(0xE9);
            PutRel32(out, siteAddr + 5, stubAddr);
            while (out.size() < site.replayLen)
                out.push_back(0x90);
            return out;
        }
    }
}
