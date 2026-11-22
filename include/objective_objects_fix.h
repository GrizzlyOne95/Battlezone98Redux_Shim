// objective_objects_fix.h -- pure, host-testable half of the ObjectiveObjects()
// iterator fix. objective_objects_fix.cpp owns the write.
//
// Stock Redux's iterator step (ObjectiveObjectsNext, GOG 0x00502760) keeps the
// list index in upvalue 1 and never advances it: both skip paths jump back to
// the loop head with the same index, and the match path stores the matched
// index back as the next start. So the first listed objective comes back on
// every call (a `for` loop never ends), and a null or flag-0x200 first slot
// spins forever in native code.
//
// The fix rewrites the whole step body in place (0xA4 bytes, padded with
// int3). Its only reference is the closure push in the ObjectiveObjects
// binding, and no branch from outside lands inside it, so nothing else sees
// the change. The new step walks the list from the top down:
//
//   n = min(count, 32)  (unsigned; the list has 32 slots)
//   upvalue 0 (fresh)   -> start at n-1
//   upvalue u (u < 0)   -> start at -2-u, clamped to n-1
//   for i = start .. 0: skip a null slot or a class with flag 0x200
//   on a match at i     -> upvalue = -1-i (never 0), return the handle
//   none left           -> return nil
//
// Downward order keeps the stock-safe idiom
// `for h in ObjectiveObjects() do SetObjectiveOff(h) end` clearing everything:
// SetObjectiveOff swap-removes (slot[i] = last), and the moved object came
// from above i, which is already visited. Objectives added during the loop
// land above the start and are not listed. Removing a not-yet-visited object
// (a lower slot) moves the top object into it, so that one can repeat.
//
// The flag test is `test byte [eax+0x15],2`, the same bit as stock
// `mov ecx,[eax+0x14] / and ecx,0x200` (bit 9 = bit 1 of byte +0x15).
//
// Call targets and globals are read from the stock body and re-encoded, so
// the build rewritten is the build that was verified.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace ObjectiveObjectsFix
    {
        constexpr size_t kBodyLen = 0xA4;

        // The objective list holds 32 slots and the count sits right after
        // them (list + 0x80). The new body clamps the count it reads to this,
        // so a list the engine overflowed (a 33rd SetObjectiveOn writes a
        // pointer over the count) cannot send it out of bounds.
        constexpr uint32_t kListSlots = 32;

        // What the body calls and reads. Absolute addresses.
        struct Operands
        {
            uint32_t toInteger;   // lua_tointeger
            uint32_t count;       // objective count global
            uint32_t list;        // objective slot array
            uint32_t pushInteger; // lua_pushinteger
            uint32_t replace;     // lua_replace
            uint32_t getHandle;   // GameObject::GetHandle (thiscall, ecx = object)
            uint32_t pushHandle;  // push a handle onto the Lua stack
        };

        // Offsets of the 4 operand bytes. Calls are E8 rel32.
        struct OperandLayout
        {
            size_t toInteger, count, list, pushInteger, replace, getHandle, pushHandle;
        };
        constexpr OperandLayout kStockLayout = { 0x10, 0x1F, 0x2B, 0x65, 0x76, 0x81, 0x8B };
        constexpr OperandLayout kPatchedLayout = { 0x0E, 0x17, 0x41, 0x65, 0x75, 0x7F, 0x88 };

        // Stock step body; operand bytes are zero here and never compared.
        //   55 8B EC 83 EC 0C               prologue, 3 locals
        //   68 ED D8 FF FF ... E8           lua_tointeger(L, upvalue 1) -> [ebp-8]
        //   8B 4D F8 3B 0D <count> 7D 79    loop: index >= count -> return 0
        //   8B 55 F8 8B 04 95 <list>        slot = list[index]
        //   ... 74 61                       null slot -> back to loop, same index
        //   ... FF D2                       class = slot vcall +0x30
        //   81 E1 00 02 00 00 74 02 EB BE   flag 0x200 -> back to loop
        //   ... pushinteger / replace       upvalue = index (unchanged)
        //   ... GetHandle / PushHandle      return 1
        constexpr uint8_t kStockBody[kBodyLen] = {
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x68, 0xED, 0xD8, 0xFF, 0xFF, 0x8B,
            0x45, 0x08, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x89,
            0x45, 0xF8, 0x8B, 0x4D, 0xF8, 0x3B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x7D,
            0x79, 0x8B, 0x55, 0xF8, 0x8B, 0x04, 0x95, 0x00, 0x00, 0x00, 0x00, 0x89,
            0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x61, 0x8B, 0x4D, 0xFC, 0x83,
            0xC1, 0x18, 0x8B, 0x55, 0xFC, 0x8B, 0x42, 0x18, 0x8B, 0x50, 0x30, 0xFF,
            0xD2, 0x89, 0x45, 0xF4, 0x8B, 0x45, 0xF4, 0x8B, 0x48, 0x14, 0x81, 0xE1,
            0x00, 0x02, 0x00, 0x00, 0x74, 0x02, 0xEB, 0xBE, 0x8B, 0x55, 0xF8, 0x52,
            0x8B, 0x45, 0x08, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08,
            0x68, 0xED, 0xD8, 0xFF, 0xFF, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0x00, 0x00,
            0x00, 0x00, 0x83, 0xC4, 0x08, 0x8B, 0x4D, 0xFC, 0xE8, 0x00, 0x00, 0x00,
            0x00, 0x50, 0x8B, 0x55, 0x08, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83,
            0xC4, 0x08, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xE9, 0x7C, 0xFF,
            0xFF, 0xFF, 0x33, 0xC0, 0x8B, 0xE5, 0x5D, 0xC3,
        };

        // Replacement body; operand bytes are zero here and filled by
        // BuildPatchedBody. The tail after `ret` is int3 padding.
        //   55 8B EC 56 57                      push ebp / mov ebp,esp / push esi / push edi
        //   68 ED D8 FF FF FF 75 08 E8 ..       eax = lua_tointeger(L, upvalue 1)
        //   8B 0D <count>                       ecx = count
        //   83 F9 20 76 05 B9 20 00 00 00       if (ecx > 32, unsigned) ecx = 32
        //   8D 71 FF                            esi = ecx-1
        //   85 C0 74 07 BE FE FF FF FF 2B F0    if (eax) esi = -2-eax
        //   3B F1 7C 03 8D 71 FF                if (esi >= ecx) esi = ecx-1
        // loop:
        //   85 F6 7C 58                         esi < 0 -> nil
        //   8B 3C B5 <list> 4E                  edi = list[esi--]
        //   85 FF 74 F0                         null -> loop
        //   8D 4F 18 8B 47 18 FF 50 30          eax = class, same vcall as stock
        //   F6 40 15 02 75 E1                   flag 0x200 -> loop
        //   B8 FE FF FF FF 2B C6 50 .. E8 ..    lua_pushinteger(L, -2-esi)
        //   68 ED D8 FF FF .. E8 ..             lua_replace(L, upvalue 1)
        //   8B CF E8 .. 50 .. E8 ..             PushHandle(L, GetHandle(edi))
        //   B8 01 00 00 00 EB 02                return 1
        // nil:
        //   33 C0                               return 0
        //   5F 5E 5D C3                         pop edi / pop esi / pop ebp / ret
        constexpr uint8_t kPatchedBody[kBodyLen] = {
            0x55, 0x8B, 0xEC, 0x56, 0x57, 0x68, 0xED, 0xD8, 0xFF, 0xFF, 0xFF, 0x75,
            0x08, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x8B, 0x0D, 0x00,
            0x00, 0x00, 0x00, 0x83, 0xF9, 0x20, 0x76, 0x05, 0xB9, 0x20, 0x00, 0x00,
            0x00, 0x8D, 0x71, 0xFF, 0x85, 0xC0, 0x74, 0x07, 0xBE, 0xFE, 0xFF, 0xFF,
            0xFF, 0x2B, 0xF0, 0x3B, 0xF1, 0x7C, 0x03, 0x8D, 0x71, 0xFF, 0x85, 0xF6,
            0x7C, 0x58, 0x8B, 0x3C, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x4E, 0x85, 0xFF,
            0x74, 0xF0, 0x8D, 0x4F, 0x18, 0x8B, 0x47, 0x18, 0xFF, 0x50, 0x30, 0xF6,
            0x40, 0x15, 0x02, 0x75, 0xE1, 0xB8, 0xFE, 0xFF, 0xFF, 0xFF, 0x2B, 0xC6,
            0x50, 0xFF, 0x75, 0x08, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08,
            0x68, 0xED, 0xD8, 0xFF, 0xFF, 0xFF, 0x75, 0x08, 0xE8, 0x00, 0x00, 0x00,
            0x00, 0x83, 0xC4, 0x08, 0x8B, 0xCF, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x50,
            0xFF, 0x75, 0x08, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08, 0xB8,
            0x01, 0x00, 0x00, 0x00, 0xEB, 0x02, 0x33, 0xC0, 0x5F, 0x5E, 0x5D, 0xC3,
            0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
        };

        enum class BodyState
        {
            Stock,
            Patched,
            Unknown,
        };

        inline bool IsOperandByte(const OperandLayout& l, size_t i)
        {
            const size_t at[] = { l.toInteger, l.count, l.list, l.pushInteger, l.replace, l.getHandle, l.pushHandle };
            for (size_t a : at)
            {
                if (i >= a && i < a + 4)
                    return true;
            }
            return false;
        }

        inline bool MatchesMasked(const uint8_t* body, const uint8_t* table, const OperandLayout& l)
        {
            for (size_t i = 0; i < kBodyLen; ++i)
            {
                if (!IsOperandByte(l, i) && body[i] != table[i])
                    return false;
            }
            return true;
        }

        // `body` is kBodyLen bytes read from the resolved step entry.
        inline BodyState Classify(const uint8_t* body)
        {
            if (MatchesMasked(body, kStockBody, kStockLayout))
                return BodyState::Stock;
            if (MatchesMasked(body, kPatchedBody, kPatchedLayout))
                return BodyState::Patched;
            return BodyState::Unknown;
        }

        inline uint32_t ReadU32(const uint8_t* p)
        {
            uint32_t v;
            std::memcpy(&v, p, sizeof(v));
            return v;
        }

        inline void WriteU32(uint8_t* p, uint32_t v)
        {
            std::memcpy(p, &v, sizeof(v));
        }

        // rel32 at `at` in a body loaded at `base`: target = base + at + 4 + rel.
        inline uint32_t RelTarget(const uint8_t* body, uint32_t base, size_t at)
        {
            return base + static_cast<uint32_t>(at) + 4u + ReadU32(body + at);
        }

        inline uint32_t RelTo(uint32_t base, size_t at, uint32_t target)
        {
            return target - (base + static_cast<uint32_t>(at) + 4u);
        }

        // The count must sit right after the 32 list slots, as on GOG; the
        // clamp in the new body depends on it.
        inline bool LayoutMatches(const Operands& o)
        {
            return o.count == o.list + kListSlots * 4u;
        }

        // Only meaningful for a body Classify() called Stock.
        inline Operands ExtractStockOperands(const uint8_t* body, uint32_t base)
        {
            const OperandLayout& l = kStockLayout;
            Operands o;
            o.toInteger = RelTarget(body, base, l.toInteger);
            o.count = ReadU32(body + l.count);
            o.list = ReadU32(body + l.list);
            o.pushInteger = RelTarget(body, base, l.pushInteger);
            o.replace = RelTarget(body, base, l.replace);
            o.getHandle = RelTarget(body, base, l.getHandle);
            o.pushHandle = RelTarget(body, base, l.pushHandle);
            return o;
        }

        // Writes the kBodyLen-byte replacement for a body loaded at `base`.
        inline void BuildPatchedBody(const Operands& o, uint32_t base, uint8_t* out)
        {
            const OperandLayout& l = kPatchedLayout;
            std::memcpy(out, kPatchedBody, kBodyLen);
            WriteU32(out + l.toInteger, RelTo(base, l.toInteger, o.toInteger));
            WriteU32(out + l.count, o.count);
            WriteU32(out + l.list, o.list);
            WriteU32(out + l.pushInteger, RelTo(base, l.pushInteger, o.pushInteger));
            WriteU32(out + l.replace, RelTo(base, l.replace, o.replace));
            WriteU32(out + l.getHandle, RelTo(base, l.getHandle, o.getHandle));
            WriteU32(out + l.pushHandle, RelTo(base, l.pushHandle, o.pushHandle));
        }
    }
}
