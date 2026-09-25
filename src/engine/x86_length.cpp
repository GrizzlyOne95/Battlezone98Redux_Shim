#include "x86_length.h"

namespace BZROpenShim
{
    namespace
    {
        enum OpClass : uint8_t
        {
            kInvalid = 0,
            kNone,        // opcode only
            kModrm,       // opcode + ModRM
            kModrmImm8,   // opcode + ModRM + imm8
            kModrmImmZ,   // opcode + ModRM + imm16/32
            kImm8,
            kImm16,
            kImmZ,
            kRel8,
            kRelZ,
            kEnter,       // imm16 + imm8
            kMoffs,       // 16/32-bit absolute address (addr-size dependent)
            kFarPtr,      // ptr16:16/32
            kGroup3,      // F6/F7: ModRM, imm only for /0 and /1
            kPrefix,      // a legacy prefix byte
        };

        OpClass OneByteClass(uint8_t op)
        {
            switch (op)
            {
            case 0x26: case 0x2E: case 0x36: case 0x3E: case 0x64: case 0x65:
            case 0x66: case 0x67: case 0xF0: case 0xF2: case 0xF3:
                return kPrefix;
            case 0x0F:
                return kInvalid;  // two-byte map, handled by the caller
            case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C:
            case 0x34: case 0x3C: case 0x6A: case 0xA8: case 0xCD: case 0xD4:
            case 0xD5: case 0xE4: case 0xE5: case 0xE6: case 0xE7:
                return kImm8;
            case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D:
            case 0x35: case 0x3D: case 0x68: case 0xA9:
                return kImmZ;
            case 0x69: case 0x81: case 0xC7:
                return kModrmImmZ;
            case 0x6B: case 0x80: case 0x82: case 0x83: case 0xC0: case 0xC1:
            case 0xC6:
                return kModrmImm8;
            case 0xC2: case 0xCA:
                return kImm16;
            case 0xC8:
                return kEnter;
            case 0xA0: case 0xA1: case 0xA2: case 0xA3:
                return kMoffs;
            case 0x9A: case 0xEA:
                return kFarPtr;
            case 0xE8: case 0xE9:
                return kRelZ;
            case 0xE0: case 0xE1: case 0xE2: case 0xE3: case 0xEB:
                return kRel8;
            case 0xF6: case 0xF7:
                return kGroup3;
            case 0xD6:  // SALC: undocumented, never emitted by the compiler
                return kInvalid;
            default:
                break;
            }
            if (op >= 0x70 && op <= 0x7F) return kRel8;
            if (op >= 0xB0 && op <= 0xB7) return kImm8;
            if (op >= 0xB8 && op <= 0xBF) return kImmZ;
            // ALU op r/m,reg and reg,r/m rows: xx0-xx3 and xx8-xxB for 00-3F.
            if (op < 0x40 && (op & 0x07) < 4) return kModrm;
            if (op >= 0x40 && op <= 0x5F) return kNone;     // inc/dec/push/pop reg
            if (op == 0x62 || op == 0x63) return kModrm;    // bound / arpl
            if (op >= 0x84 && op <= 0x8F) return kModrm;    // test/xchg/mov/lea/pop
            if (op == 0xC4 || op == 0xC5) return kModrm;    // les / lds (VEX rejected below)
            if (op >= 0xD0 && op <= 0xD3) return kModrm;    // shift groups
            if (op >= 0xD8 && op <= 0xDF) return kModrm;    // x87 escape
            if (op == 0xFE || op == 0xFF) return kModrm;    // inc/dec/call/jmp/push groups
            return kNone;  // remaining one-byte opcodes carry no operand bytes
        }

        // 0F xx opcodes that take no ModRM byte.
        bool TwoByteHasNoModrm(uint8_t op)
        {
            switch (op)
            {
            case 0x05: case 0x06: case 0x07: case 0x08: case 0x09: case 0x0B:
            case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35:
            case 0x37: case 0x77: case 0xA0: case 0xA1: case 0xA2: case 0xA8:
            case 0xA9: case 0xAA:
                return true;
            default:
                return op >= 0xC8 && op <= 0xCF;  // bswap reg
            }
        }

        // 0F xx opcodes that take ModRM followed by imm8.
        bool TwoByteHasImm8(uint8_t op)
        {
            switch (op)
            {
            case 0x70: case 0x71: case 0x72: case 0x73: case 0xA4: case 0xAC:
            case 0xBA: case 0xC2: case 0xC4: case 0xC5: case 0xC6:
                return true;
            default:
                return false;
            }
        }

        // 0F xx opcodes that are undefined, or 3DNow!/system encodings this
        // decoder deliberately refuses.
        bool TwoByteIsInvalid(uint8_t op)
        {
            switch (op)
            {
            case 0x04: case 0x0A: case 0x0C: case 0x0E: case 0x0F:
            case 0x24: case 0x25: case 0x26: case 0x27: case 0x36:
            case 0x39: case 0x3B: case 0x3C: case 0x3D: case 0x3E: case 0x3F:
            case 0x7A: case 0x7B: case 0xA6: case 0xA7: case 0xFF:
                return true;
            default:
                return false;
            }
        }

        // Returns the number of bytes in the ModRM/SIB/displacement group that
        // starts at code[0], or 0 when it does not fit in `size`.
        size_t ModrmLength(const uint8_t* code, size_t size, bool addr16)
        {
            if (size < 1) return 0;
            const uint8_t modrm = code[0];
            const uint8_t mod = static_cast<uint8_t>(modrm >> 6);
            const uint8_t rm = static_cast<uint8_t>(modrm & 7);
            size_t len = 1;
            if (mod == 3)
                return len;
            if (addr16)
            {
                if (mod == 0) len += (rm == 6) ? 2 : 0;
                else if (mod == 1) len += 1;
                else len += 2;
                return len <= size ? len : 0;
            }
            if (rm == 4)
            {
                if (size < 2) return 0;
                const uint8_t sib = code[1];
                len += 1;
                if (mod == 0 && (sib & 7) == 5) len += 4;
            }
            if (mod == 0 && rm == 5) len += 4;
            else if (mod == 1) len += 1;
            else if (mod == 2) len += 4;
            return len <= size ? len : 0;
        }

        struct Decoded
        {
            size_t length = 0;
            size_t rel32Offset = 0;   // offset of the rel32 field, or 0
            bool rel8 = false;
            bool rel16 = false;
        };

        Decoded Decode(const uint8_t* code, size_t size)
        {
            Decoded d;
            size_t i = 0;
            bool opsize16 = false;
            bool addr16 = false;
            while (i < size && i < 4)
            {
                const uint8_t b = code[i];
                if (b == 0x66) opsize16 = true;
                else if (b == 0x67) addr16 = true;
                else if (OneByteClass(b) != kPrefix) break;
                ++i;
            }
            if (i >= size) return d;
            const size_t immZ = opsize16 ? 2 : 4;
            uint8_t op = code[i++];
            bool needModrm = false;
            size_t imm = 0;
            size_t rel32Offset = 0;

            if (op == 0x0F)
            {
                if (i >= size) return d;
                op = code[i++];
                if (TwoByteIsInvalid(op)) return d;
                if (op == 0x38 || op == 0x3A)
                {
                    if (i >= size) return d;
                    ++i;  // third opcode byte
                    needModrm = true;
                    imm = (op == 0x3A) ? 1 : 0;
                }
                else if (op >= 0x80 && op <= 0x8F)
                {
                    if (opsize16) { d.rel16 = true; return d; }
                    rel32Offset = i;
                    imm = 4;
                }
                else if (TwoByteHasNoModrm(op)) {}
                else
                {
                    needModrm = true;
                    if (TwoByteHasImm8(op)) imm = 1;
                }
            }
            else
            {
                switch (OneByteClass(op))
                {
                case kInvalid: case kPrefix: return d;
                case kNone: break;
                case kModrm:
                    needModrm = true;
                    // C4/C5 with mod==11 is a VEX prefix, not les/lds; refuse.
                    if ((op == 0xC4 || op == 0xC5) && i < size && (code[i] >> 6) == 3) return d;
                    // 62 with mod==11 would be EVEX; refuse the same way.
                    if (op == 0x62 && i < size && (code[i] >> 6) == 3) return d;
                    break;
                case kModrmImm8: needModrm = true; imm = 1; break;
                case kModrmImmZ: needModrm = true; imm = immZ; break;
                case kImm8: imm = 1; break;
                case kImm16: imm = 2; break;
                case kImmZ: imm = immZ; break;
                case kRel8: d.rel8 = true; imm = 1; break;
                case kRelZ:
                    if (opsize16) { d.rel16 = true; return d; }
                    rel32Offset = i;
                    imm = 4;
                    break;
                case kEnter: imm = 3; break;
                case kMoffs: imm = addr16 ? 2 : 4; break;
                case kFarPtr: imm = 2 + immZ; break;
                case kGroup3:
                    needModrm = true;
                    if (i < size && ((code[i] >> 3) & 7) < 2)
                        imm = (op == 0xF6) ? 1 : immZ;
                    break;
                }
            }

            if (needModrm)
            {
                const size_t m = ModrmLength(code + i, size - i, addr16);
                if (m == 0) return d;
                i += m;
            }
            if (i + imm > size) return d;
            d.length = i + imm;
            d.rel32Offset = rel32Offset;
            return d;
        }
    }

    size_t X86InstructionLength32(const uint8_t* code, size_t size)
    {
        if (!code) return 0;
        return Decode(code, size).length;
    }

    X86StealPlan PlanDetourSteal32(const uint8_t* code, size_t size, size_t patchLen)
    {
        X86StealPlan plan;
        if (!code || patchLen == 0 || patchLen > size)
        {
            plan.status = X86StealStatus::Undecodable;
            return plan;
        }
        size_t off = 0;
        while (off < patchLen)
        {
            const Decoded d = Decode(code + off, size - off);
            plan.failOffset = off;
            if (d.rel8)   { plan.status = X86StealStatus::ShortBranch; return plan; }
            if (d.rel16)  { plan.status = X86StealStatus::Rel16Branch; return plan; }
            if (d.length == 0) { plan.status = X86StealStatus::Undecodable; return plan; }
            if (d.rel32Offset)
            {
                if (plan.rel32Count >= X86StealPlan::kMaxRel32)
                {
                    plan.status = X86StealStatus::TooManyRel32;
                    return plan;
                }
                plan.rel32Offsets[plan.rel32Count++] = off + d.rel32Offset;
            }
            off += d.length;
            ++plan.instructionCount;
            plan.boundary = off;
        }
        plan.failOffset = 0;
        plan.status = (off == patchLen) ? X86StealStatus::Ok : X86StealStatus::NotOnBoundary;
        return plan;
    }

    const char* X86StealStatusName(X86StealStatus status)
    {
        switch (status)
        {
        case X86StealStatus::Ok: return "ok";
        case X86StealStatus::Undecodable: return "undecodable";
        case X86StealStatus::NotOnBoundary: return "not-on-boundary";
        case X86StealStatus::ShortBranch: return "rel8-branch";
        case X86StealStatus::Rel16Branch: return "rel16-branch";
        case X86StealStatus::TooManyRel32: return "too-many-rel32";
        }
        return "unknown";
    }
}
