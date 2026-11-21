#pragma once
// fp_trap_log_policy.h
// BZR Open Shim - the pure half of [Diagnostics] FpTrapLog
// (src/patches/fp_trap_log.cpp, include/fp_trap_recovery.h).
//
// Redux masks every floating-point exception, so a NaN or an infinity is
// produced silently and only noticed frames later. FpTrapLog unmasks
// divide-by-zero and invalid-operation on the main thread once per frame,
// catches the first trap in a vectored handler, records the faulting
// instruction, re-runs it masked (so it produces the stock NaN/inf) and leaves
// the thread masked until the next frame.
//
// Which bits are unmasked, and why x87 invalid-operation stays masked:
//
//   SSE (MXCSR) IM and ZM. An SSE exception is a precise fault: EIP is the
//   faulting instruction and nothing was written, so re-running it masked is
//   exactly the stock result. The game code is SSE2 (comiss/divss/cvttss2si).
//
//   x87 ZM only. An x87 exception is deferred: it is reported at the next
//   waiting x87 instruction, and every integer instruction in between has
//   already run. For divide-by-zero that is invisible, because the result only
//   lives in an x87 register until an x87 instruction reads it. For invalid
//   operation it is not: FCOM/FCOMP on a NaN followed by the non-waiting
//   FNSTSW AX branches on stale condition codes, FIST/FISTP leaves memory
//   unwritten while integer code reads it, and FCOMI's EFLAGS feed a Jcc
//   before the trap. OpenShim itself is built /arch:IA32 and compares with
//   FCOMP + FNSTSW, so unmasking x87 IM would change branches. kX87TrapBits
//   is the one place to change that decision.
//
// No <Windows.h>: the Linux host lane compiles and tests this file.

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
namespace FpTrap
{
    // x87 control-word mask bits and status-word flag bits share positions.
    constexpr uint16_t kX87Invalid = 0x0001;       // IM / IE
    constexpr uint16_t kX87ZeroDivide = 0x0004;    // ZM / ZE
    constexpr uint16_t kX87ExceptionBits = 0x003F; // IE DE ZE OE UE PE
    constexpr uint16_t kX87StackFault = 0x0040;    // SF (with IE)
    constexpr uint16_t kX87ErrorSummary = 0x0080;  // ES
    constexpr uint16_t kX87Busy = 0x8000;          // B

    // MXCSR: flags in bits 0..5, the matching masks seven bits higher.
    constexpr uint32_t kMxcsrInvalid = 0x0001;
    constexpr uint32_t kMxcsrZeroDivide = 0x0004;
    constexpr uint32_t kMxcsrFlagBits = 0x003F;
    constexpr unsigned kMxcsrMaskShift = 7;

    // What the frame tick unmasks (see the header comment).
    constexpr uint16_t kX87TrapBits = kX87ZeroDivide;
    constexpr uint32_t kSseTrapBits = kMxcsrInvalid | kMxcsrZeroDivide;

    // FXSAVE image offsets (CONTEXT.ExtendedRegisters on x86).
    constexpr size_t kFxsaveFcwOffset = 0;
    constexpr size_t kFxsaveFswOffset = 2;
    constexpr size_t kFxsaveFopOffset = 6;
    constexpr size_t kFxsaveMxcsrOffset = 24;

    struct ControlState
    {
        uint16_t x87Control = 0x037F;
        uint16_t x87Status = 0;
        uint32_t mxcsr = 0x1F80;
    };

    enum class Kind : uint8_t
    {
        None,
        X87,
        Sse,
        // Raised in software: no pending flag in the saved state. The MSVC CRT
        // math-error path (log(0), pow(0,-1), ...) checks the control word,
        // clears the status flags and calls RaiseException itself when the
        // matching exception is unmasked.
        Raised,
    };

    // x87 exceptions waiting for the next waiting instruction: ES set and a
    // flag whose mask bit is clear.
    inline uint16_t PendingX87(const ControlState& s)
    {
        if ((s.x87Status & kX87ErrorSummary) == 0)
            return 0;
        return static_cast<uint16_t>(s.x87Status & ~s.x87Control & kX87ExceptionBits);
    }

    // SSE flags whose mask bit is clear. The frame tick clears the flags it
    // unmasks, so a set unmasked flag means the instruction at EIP faulted.
    inline uint32_t PendingSse(const ControlState& s)
    {
        const uint32_t flags = s.mxcsr & kMxcsrFlagBits;
        const uint32_t masks = (s.mxcsr >> kMxcsrMaskShift) & kMxcsrFlagBits;
        return flags & ~masks;
    }

    // x87 first: a pending x87 exception surfaces at an x87 instruction, and
    // an SSE fault cannot be raised while one is pending on that instruction.
    inline Kind Classify(const ControlState& s, uint32_t& pendingBits)
    {
        pendingBits = PendingX87(s);
        if (pendingBits != 0)
            return Kind::X87;
        pendingBits = PendingSse(s);
        if (pendingBits != 0)
            return Kind::Sse;
        return Kind::None;
    }

    // The frame tick's state: FNCLEX (every x87 flag, ES and B cleared, so an
    // old sticky flag cannot become pending the moment its mask is cleared),
    // the trap bits unmasked, and the matching SSE flags cleared.
    inline ControlState Unmasked(ControlState s)
    {
        s.x87Status = static_cast<uint16_t>(
            s.x87Status & ~(kX87ExceptionBits | kX87StackFault | kX87ErrorSummary | kX87Busy));
        s.x87Control = static_cast<uint16_t>(s.x87Control & ~kX87TrapBits);
        s.mxcsr &= ~kSseTrapBits;
        s.mxcsr &= ~(kSseTrapBits << kMxcsrMaskShift);
        return s;
    }

    // Back to stock masking for the trap bits; every other bit as it was.
    inline ControlState Masked(ControlState s)
    {
        s.x87Control = static_cast<uint16_t>(s.x87Control | kX87TrapBits);
        s.mxcsr |= kSseTrapBits << kMxcsrMaskShift;
        return s;
    }

    // The state the faulting instruction re-runs under: both units masked,
    // the pending flags (and ES/B, and SF with IE) cleared so the masked
    // re-run sets them again exactly as stock would. Other sticky flags stay.
    inline ControlState RecoveryState(ControlState s)
    {
        const uint16_t x87Pending = PendingX87(s);
        const uint32_t ssePending = PendingSse(s);
        uint16_t clear = static_cast<uint16_t>(x87Pending | kX87ErrorSummary | kX87Busy);
        if (x87Pending & kX87Invalid)
            clear = static_cast<uint16_t>(clear | kX87StackFault);
        s.x87Status = static_cast<uint16_t>(s.x87Status & ~clear);
        s.mxcsr &= ~ssePending;
        // Also mask every pending bit, not only the trap bits: if a third
        // party unmasked another exception (OE/UE/DE), the masked re-run
        // would otherwise fault again at the same instruction forever.
        s.x87Control = static_cast<uint16_t>(s.x87Control | x87Pending);
        s.mxcsr |= ssePending << kMxcsrMaskShift;
        return Masked(s);
    }

    // STATUS_FLOAT_* codes. Windows reports an x87 stack fault as
    // STATUS_FLOAT_STACK_CHECK and an SSE fault as MULTIPLE_TRAPS/FAULTS (or a
    // specific code), so the whole family is accepted and the saved FPU state,
    // not the code, decides whether the trap is ours.
    inline bool IsFloatExceptionCode(uint32_t code)
    {
        return (code >= 0xC000008Du && code <= 0xC0000093u) || code == 0xC00002B4u ||
               code == 0xC00002B5u;
    }

    // The vectored handler's first gate: the code is a float trap and it was
    // raised on the thread the logger unmasks. Deliberately not gated on the
    // unmask still being live: code that saves and restores the control word
    // around a call (the CRT does) can leave the thread unmasked after the
    // handler masked it, and a trap the handler declines crashes the game.
    inline bool ShouldConsider(uint32_t code, uint32_t threadId, uint32_t targetThreadId)
    {
        return targetThreadId != 0 && threadId == targetThreadId && IsFloatExceptionCode(code);
    }

    // IE/ZE bit for a raised code (the saved status words hold none).
    inline uint8_t FlagsFromCode(uint32_t code)
    {
        if (code == 0xC000008Eu)
            return static_cast<uint8_t>(kX87ZeroDivide);
        if (code == 0xC0000090u || code == 0xC0000092u)
            return static_cast<uint8_t>(kX87Invalid);
        return 0;
    }

    // True when [address, address + size) overlaps [stackLimit, esp): stack
    // below the trapped ESP, which exception dispatch has since overwritten.
    inline bool OverlapsBelowStack(uint32_t address, uint32_t size, uint32_t stackLimit, uint32_t esp)
    {
        if (size == 0 || stackLimit >= esp)
            return false;
        const uint64_t end = static_cast<uint64_t>(address) + size;
        return end > stackLimit && address < esp;
    }

    // ---- x87 instruction decode -------------------------------------------
    //
    // The x87 recovery re-runs the faulting instruction in a stub. Its memory
    // operand (if any) is rewritten to the absolute address the FPU recorded
    // (FPU data pointer), because the registers its ModRM used may have changed
    // in the integer code that ran before the trap surfaced.

    struct X87Decoded
    {
        bool ok = false;
        uint8_t length = 0;      // whole instruction, prefixes included
        uint8_t prefixCount = 0; // segment overrides only
        uint8_t opcode = 0;      // 0xD8..0xDF
        uint8_t modrm = 0;
        bool memory = false;
        uint8_t operandSize = 0; // memory forms: bytes accessed
        bool store = false;      // memory forms: writes the operand
    };

    struct X87Operand
    {
        uint8_t size = 0; // 0: no valid memory form
        bool store = false;
    };

    // Size and direction of an x87 memory operand (Intel SDM vol. 2, x87
    // opcode map). Control forms and undefined encodings give size 0.
    inline X87Operand X87MemoryOperand(uint8_t opcode, uint8_t modrm)
    {
        const uint8_t reg = static_cast<uint8_t>((modrm >> 3) & 7);
        X87Operand o;
        switch (opcode)
        {
        case 0xD8: o.size = 4; break; // m32fp arithmetic
        case 0xDA: o.size = 4; break; // m32int arithmetic
        case 0xDC: o.size = 8; break; // m64fp arithmetic
        case 0xDE: o.size = 2; break; // m16int arithmetic
        case 0xD9:                    // fld / fst / fstp m32fp
            if (reg == 0 || reg == 2 || reg == 3)
                o.size = 4;
            o.store = reg != 0;
            break;
        case 0xDB:
            if (reg <= 3) // fild / fisttp / fist / fistp m32int
                o.size = 4;
            else if (reg == 5 || reg == 7) // fld / fstp m80fp
                o.size = 10;
            o.store = reg != 0 && reg != 5;
            break;
        case 0xDD:
            if (reg <= 3) // fld / fisttp / fst / fstp m64
                o.size = 8;
            o.store = reg != 0;
            break;
        case 0xDF:
            if (reg <= 3) // fild / fisttp / fist / fistp m16int
                o.size = 2;
            else if (reg == 4 || reg == 6) // fbld / fbstp m80bcd
                o.size = 10;
            else // fild / fistp m64int
                o.size = 8;
            o.store = reg != 0 && reg != 4 && reg != 5;
            break;
        default: break;
        }
        if (o.size == 0)
            o.store = false;
        return o;
    }

    inline bool IsSegmentPrefix(uint8_t b)
    {
        return b == 0x26 || b == 0x2E || b == 0x36 || b == 0x3E || b == 0x64 || b == 0x65;
    }

    // Control instructions never update the FPU instruction pointer, so the
    // recorded address cannot name one; refuse them anyway (fail closed).
    inline bool IsX87ControlForm(uint8_t opcode, uint8_t modrm)
    {
        const uint8_t mod = static_cast<uint8_t>(modrm >> 6);
        const uint8_t reg = static_cast<uint8_t>((modrm >> 3) & 7);
        if (mod != 3)
        {
            if (opcode == 0xD9 && reg >= 4) // fldenv fldcw fnstenv fnstcw
                return true;
            if (opcode == 0xDD && (reg == 4 || reg == 6 || reg == 7)) // frstor fnsave fnstsw
                return true;
            return false;
        }
        if (opcode == 0xDB && modrm >= 0xE0 && modrm <= 0xE7) // feni fdisi fnclex fninit fsetpm
            return true;
        if (opcode == 0xDF && modrm == 0xE0) // fnstsw ax
            return true;
        return false;
    }

    inline X87Decoded DecodeX87(const uint8_t* code, size_t size)
    {
        X87Decoded d;
        size_t at = 0;
        while (at < size && at < 4 && IsSegmentPrefix(code[at]))
            ++at;
        if (at + 2 > size || code[at] < 0xD8 || code[at] > 0xDF)
            return d;
        d.prefixCount = static_cast<uint8_t>(at);
        d.opcode = code[at];
        d.modrm = code[at + 1];
        if (IsX87ControlForm(d.opcode, d.modrm))
            return d;
        size_t length = at + 2;
        const uint8_t mod = static_cast<uint8_t>(d.modrm >> 6);
        const uint8_t rm = static_cast<uint8_t>(d.modrm & 7);
        if (mod != 3)
        {
            d.memory = true;
            const X87Operand operand = X87MemoryOperand(d.opcode, d.modrm);
            if (operand.size == 0)
                return d;
            d.operandSize = operand.size;
            d.store = operand.store;
            if (rm == 4)
            {
                if (length >= size)
                    return d;
                const uint8_t base = static_cast<uint8_t>(code[length] & 7);
                ++length;
                if (mod == 0 && base == 5)
                    length += 4;
            }
            else if (mod == 0 && rm == 5)
            {
                length += 4;
            }
            if (mod == 1)
                length += 1;
            else if (mod == 2)
                length += 4;
        }
        if (length > size || length > 15)
            return d;
        d.length = static_cast<uint8_t>(length);
        d.ok = true;
        return d;
    }

    // The FXSAVE FOP field: the low three opcode bits and the ModRM byte.
    // Zero means the processor did not record one (no check possible).
    inline bool MatchesFop(const X87Decoded& d, uint16_t fop)
    {
        fop = static_cast<uint16_t>(fop & 0x07FF);
        if (fop == 0)
            return true;
        return fop == static_cast<uint16_t>(((d.opcode & 7u) << 8) | d.modrm);
    }

    // Writes the stub form of the instruction to out: the same prefixes and
    // opcode, a memory operand rewritten to [disp32 = dataOffset], a register
    // form copied verbatim. Returns its length, or 0.
    inline size_t BuildAbsoluteX87(const uint8_t* code, const X87Decoded& d, uint32_t dataOffset,
                                   uint8_t* out, size_t capacity)
    {
        if (!d.ok)
            return 0;
        const size_t needed = static_cast<size_t>(d.prefixCount) + (d.memory ? 6u : 2u);
        if (capacity < needed)
            return 0;
        size_t at = 0;
        for (; at < d.prefixCount; ++at)
            out[at] = code[at];
        out[at++] = d.opcode;
        if (!d.memory)
        {
            out[at++] = d.modrm;
            return at;
        }
        out[at++] = static_cast<uint8_t>((d.modrm & 0x38) | 0x05); // mod=00 rm=101: [disp32]
        out[at++] = static_cast<uint8_t>(dataOffset);
        out[at++] = static_cast<uint8_t>(dataOffset >> 8);
        out[at++] = static_cast<uint8_t>(dataOffset >> 16);
        out[at++] = static_cast<uint8_t>(dataOffset >> 24);
        return at;
    }

    // ---- EBP frame walk ---------------------------------------------------

    constexpr size_t kStackDepth = 8;

    // Walks saved-EBP frames: [ebp] = caller's ebp, [ebp+4] = return address.
    // `read(address, value)` reads one 32-bit word and returns false when it
    // cannot. Frames must stay inside [stackLow, stackHigh), be 4-aligned and
    // strictly increase. Returns the number of return addresses written.
    template <typename Reader>
    size_t WalkEbpFrames(uint32_t ebp, uint32_t stackLow, uint32_t stackHigh, Reader&& read, uint32_t* out,
                         size_t capacity)
    {
        size_t count = 0;
        uint32_t frame = ebp;
        while (count < capacity)
        {
            if ((frame & 3u) != 0 || frame < stackLow || stackHigh < 8u || frame > stackHigh - 8u)
                break;
            uint32_t next = 0;
            uint32_t ret = 0;
            if (!read(frame, next) || !read(frame + 4u, ret))
                break;
            if (ret == 0)
                break;
            out[count++] = ret;
            if (next <= frame)
                break;
            frame = next;
        }
        return count;
    }

    // The site of a software raise: the first walked return address that
    // `isSystem` (CRT / KernelBase / ntdll) rejects, so log(0) from two game
    // functions gives two sites. When every frame is a system one -- a static
    // CRT lives in the exe itself and is not recognised -- the first frame.
    template <typename IsSystem>
    uint32_t FirstCallerOutside(const uint32_t* stack, size_t depth, IsSystem&& isSystem)
    {
        for (size_t i = 0; i < depth; ++i)
        {
            if (!isSystem(stack[i]))
                return stack[i];
        }
        return depth > 0 ? stack[0] : 0;
    }

    // ---- unique-site table --------------------------------------------------

    struct TrapSite
    {
        uint32_t address = 0;  // faulting instruction (x87: FPU instruction pointer)
        uint32_t count = 0;    // saturates
        uint32_t firstEip = 0; // where it was reported (x87: the next x87 instruction)
        uint32_t firstFrame = 0;
        uint32_t stack[kStackDepth] = {};
        uint8_t stackDepth = 0;
        Kind kind = Kind::None;
        uint8_t flags = 0;     // pending exception bits (IE/ZE positions)
        bool adjacent = false; // x87: nothing ran between the fault and the report
        bool logged = false;
    };

    // Fixed-size, allocation-free: the vectored handler records into it. One
    // thread writes it (the trapped main thread) and the same thread reads it.
    template <size_t N>
    class TrapTable
    {
    public:
        // The site for (address, kind), created on first sight. Null when the
        // table is full; the trap is then only counted in Dropped().
        TrapSite* Record(uint32_t address, Kind kind, bool& isNew)
        {
            isNew = false;
            if (m_Total != UINT32_MAX)
                ++m_Total;
            for (size_t i = 0; i < m_Used; ++i)
            {
                TrapSite& site = m_Sites[i];
                if (site.address == address && site.kind == kind)
                {
                    if (site.count != UINT32_MAX)
                        ++site.count;
                    return &site;
                }
            }
            if (m_Used == N)
            {
                if (m_Dropped != UINT32_MAX)
                    ++m_Dropped;
                return nullptr;
            }
            TrapSite& site = m_Sites[m_Used++];
            site = TrapSite();
            site.address = address;
            site.kind = kind;
            site.count = 1;
            isNew = true;
            return &site;
        }

        size_t Size() const { return m_Used; }
        uint32_t Total() const { return m_Total; }
        uint32_t Dropped() const { return m_Dropped; }
        TrapSite& At(size_t i) { return m_Sites[i]; }
        const TrapSite& At(size_t i) const { return m_Sites[i]; }

        // Site indices by descending count, ties in first-seen order.
        size_t SortedByCount(uint16_t* out, size_t capacity) const
        {
            const size_t n = m_Used < capacity ? m_Used : capacity;
            for (size_t i = 0; i < n; ++i)
            {
                size_t j = i;
                const uint16_t value = static_cast<uint16_t>(i);
                while (j > 0 && m_Sites[out[j - 1]].count < m_Sites[value].count)
                {
                    out[j] = out[j - 1];
                    --j;
                }
                out[j] = value;
            }
            return n;
        }

    private:
        TrapSite m_Sites[N];
        size_t m_Used = 0;
        uint32_t m_Total = 0;
        uint32_t m_Dropped = 0;
    };

    inline const char* KindName(Kind kind)
    {
        return kind == Kind::X87 ? "x87" : kind == Kind::Sse ? "sse" : kind == Kind::Raised ? "raised" : "none";
    }

    // "IE", "ZE", "IE|ZE" or "other" for the pending bits.
    inline const char* FlagsName(uint32_t bits)
    {
        const bool invalid = (bits & 0x01u) != 0;
        const bool zero = (bits & 0x04u) != 0;
        if (invalid && zero)
            return "IE|ZE";
        if (invalid)
            return "IE";
        if (zero)
            return "ZE";
        return "other";
    }
}
}
