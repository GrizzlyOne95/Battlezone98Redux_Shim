// Pure logic of [Diagnostics] FpTrapLog (include/fp_trap_log_policy.h): mask
// bit math, trap classification, the handler gate, the x87 decode/rewrite used
// by the recovery stub, the EBP walk and the unique-site table.
#include "fp_trap_log_policy.h"

#include <cstdio>
#include <cstring>
#include <map>

#include "test_check.h"

namespace
{
    using namespace BZROpenShim::FpTrap;

    void TestUnmaskAndMask()
    {
        ControlState stock; // Redux: everything masked (0x037F, 0x1F80)
        stock.x87Status = 0x0021; // stale PE|IE flags
        stock.mxcsr = 0x1F80 | 0x8040 | 0x0021; // FTZ|DAZ, stale PE|IE
        const ControlState u = Unmasked(stock);
        CHECK(u.x87Control == (0x037F & ~kX87ZeroDivide));
        CHECK((u.x87Control & kX87Invalid) != 0); // x87 IM stays masked by policy
        CHECK(u.x87Status == 0);                   // FNCLEX
        CHECK((u.mxcsr & 0x0280) == 0);            // IM, ZM unmasked
        CHECK((u.mxcsr & 0x0005) == 0);            // IE, ZE flags cleared
        CHECK((u.mxcsr & 0x0020) != 0);            // other sticky flags kept
        CHECK((u.mxcsr & 0x8040) == 0x8040);       // FTZ/DAZ untouched
        CHECK((u.mxcsr & 0x1D00) == 0x1D00);       // other masks untouched
        const ControlState m = Masked(u);
        CHECK(m.x87Control == 0x037F);
        CHECK((m.mxcsr & 0x1F80) == 0x1F80);
    }

    void TestClassify()
    {
        uint32_t bits = 0;
        ControlState s = Unmasked(ControlState());
        CHECK(Classify(s, bits) == Kind::None);

        ControlState x87 = s;
        x87.x87Status = static_cast<uint16_t>(kX87ZeroDivide | kX87ErrorSummary | kX87Busy);
        CHECK(Classify(x87, bits) == Kind::X87);
        CHECK(bits == kX87ZeroDivide);

        // A masked flag with ES clear is not pending.
        ControlState masked = s;
        masked.x87Status = kX87Invalid;
        CHECK(Classify(masked, bits) == Kind::None);

        ControlState sse = s;
        sse.mxcsr |= kMxcsrInvalid | 0x20; // PE is masked, IE is not
        CHECK(Classify(sse, bits) == Kind::Sse);
        CHECK(bits == kMxcsrInvalid);
    }

    void TestRecoveryState()
    {
        ControlState s = Unmasked(ControlState());
        s.x87Status = static_cast<uint16_t>(kX87ZeroDivide | kX87ErrorSummary | kX87Busy | 0x20);
        s.mxcsr |= 0x20;
        const ControlState r = RecoveryState(s);
        CHECK(r.x87Status == 0x20); // pending ZE, ES, B cleared; PE kept
        CHECK((r.x87Control & kX87TrapBits) == kX87TrapBits);
        CHECK((r.mxcsr & 0x0280) == 0x0280);
        CHECK((r.mxcsr & 0x20) != 0);
        uint32_t bits = 0;
        CHECK(Classify(r, bits) == Kind::None);

        ControlState sse = Unmasked(ControlState());
        sse.mxcsr |= kMxcsrZeroDivide;
        const ControlState rs = RecoveryState(sse);
        CHECK((rs.mxcsr & kMxcsrZeroDivide) == 0);
        CHECK((rs.mxcsr & 0x0280) == 0x0280);

        // A third party's unmasked overflow: the pending OE is masked too, so
        // the re-run cannot fault again (it would loop forever).
        ControlState oe = Unmasked(ControlState());
        oe.x87Control = static_cast<uint16_t>(oe.x87Control & ~0x0008);
        oe.x87Status = static_cast<uint16_t>(0x0008 | kX87ErrorSummary);
        oe.mxcsr = (oe.mxcsr & ~(0x0008u << kMxcsrMaskShift)) | 0x0008u;
        const ControlState ro = RecoveryState(oe);
        CHECK((ro.x87Control & 0x0008) != 0);
        CHECK((ro.mxcsr & (0x0008u << kMxcsrMaskShift)) != 0);
        CHECK((ro.mxcsr & 0x0008u) == 0);
        CHECK(Classify(ro, bits) == Kind::None);

        // An IE stack fault also clears SF.
        ControlState stackFault;
        stackFault.x87Control = 0x037E;
        stackFault.x87Status = static_cast<uint16_t>(kX87Invalid | kX87StackFault | kX87ErrorSummary);
        CHECK((RecoveryState(stackFault).x87Status & (kX87StackFault | kX87Invalid)) == 0);
    }

    void TestGate()
    {
        CHECK(IsFloatExceptionCode(0xC000008Eu)); // divide by zero
        CHECK(IsFloatExceptionCode(0xC0000090u)); // invalid operation
        CHECK(IsFloatExceptionCode(0xC0000092u)); // stack check
        CHECK(IsFloatExceptionCode(0xC00002B4u)); // multiple faults
        CHECK(IsFloatExceptionCode(0xC00002B5u)); // multiple traps (SSE on WOW64)
        CHECK(!IsFloatExceptionCode(0xC0000005u));
        CHECK(!IsFloatExceptionCode(0xC0000094u)); // integer divide
        CHECK(ShouldConsider(0xC000008Eu, 7, 7));
        CHECK(!ShouldConsider(0xC000008Eu, 8, 7));
        CHECK(!ShouldConsider(0xC000008Eu, 0, 0));
        CHECK(!ShouldConsider(0xC0000005u, 7, 7));
    }

    void TestRaised()
    {
        CHECK(FlagsFromCode(0xC000008Eu) == kX87ZeroDivide);
        CHECK(FlagsFromCode(0xC0000090u) == kX87Invalid);
        CHECK(FlagsFromCode(0xC0000092u) == kX87Invalid);
        CHECK(FlagsFromCode(0xC00002B5u) == 0);
    }

    void TestBelowStack()
    {
        // stack limit 0x1000, esp 0x2000
        CHECK(OverlapsBelowStack(0x1FF8, 4, 0x1000, 0x2000));
        CHECK(OverlapsBelowStack(0x1000, 4, 0x1000, 0x2000));
        CHECK(OverlapsBelowStack(0x1FFE, 4, 0x1000, 0x2000)); // straddles esp
        CHECK(OverlapsBelowStack(0x0FFE, 4, 0x1000, 0x2000)); // straddles the limit
        CHECK(!OverlapsBelowStack(0x2000, 4, 0x1000, 0x2000)); // at esp: live frame
        CHECK(!OverlapsBelowStack(0x0FF0, 4, 0x1000, 0x2000));
        CHECK(!OverlapsBelowStack(0x00401000, 8, 0x1000, 0x2000));
        CHECK(!OverlapsBelowStack(0x1800, 0, 0x1000, 0x2000));
        CHECK(!OverlapsBelowStack(0x1800, 4, 0x2000, 0x1000)); // bad bounds
        CHECK(!OverlapsBelowStack(0xFFFFFFFEu, 4, 0x1000, 0x2000)); // no wrap
    }

    void TestOperandSizes()
    {
        CHECK(X87MemoryOperand(0xD8, 0x36).size == 4 && !X87MemoryOperand(0xD8, 0x36).store);
        CHECK(X87MemoryOperand(0xDC, 0x36).size == 8);
        CHECK(X87MemoryOperand(0xDA, 0x36).size == 4);
        CHECK(X87MemoryOperand(0xDE, 0x36).size == 2);
        CHECK(X87MemoryOperand(0xD9, 0x00).size == 4 && !X87MemoryOperand(0xD9, 0x00).store); // fld m32
        CHECK(X87MemoryOperand(0xD9, 0x18).size == 4 && X87MemoryOperand(0xD9, 0x18).store);  // fstp m32
        CHECK(X87MemoryOperand(0xD9, 0x08).size == 0);                                          // undefined
        CHECK(X87MemoryOperand(0xDB, 0x28).size == 10 && !X87MemoryOperand(0xDB, 0x28).store); // fld m80
        CHECK(X87MemoryOperand(0xDB, 0x38).size == 10 && X87MemoryOperand(0xDB, 0x38).store);  // fstp m80
        CHECK(X87MemoryOperand(0xDB, 0x18).size == 4 && X87MemoryOperand(0xDB, 0x18).store);   // fistp m32
        CHECK(X87MemoryOperand(0xDB, 0x20).size == 0);
        CHECK(X87MemoryOperand(0xDD, 0x18).size == 8 && X87MemoryOperand(0xDD, 0x18).store);  // fstp m64
        CHECK(X87MemoryOperand(0xDD, 0x28).size == 0);
        CHECK(X87MemoryOperand(0xDF, 0x28).size == 8 && !X87MemoryOperand(0xDF, 0x28).store); // fild m64
        CHECK(X87MemoryOperand(0xDF, 0x38).size == 8 && X87MemoryOperand(0xDF, 0x38).store);  // fistp m64
        CHECK(X87MemoryOperand(0xDF, 0x20).size == 10 && !X87MemoryOperand(0xDF, 0x20).store); // fbld
        CHECK(X87MemoryOperand(0xDF, 0x30).size == 10 && X87MemoryOperand(0xDF, 0x30).store);  // fbstp
        CHECK(X87MemoryOperand(0xDF, 0x10).size == 2 && X87MemoryOperand(0xDF, 0x10).store);   // fist m16
        CHECK(X87MemoryOperand(0x90, 0x00).size == 0);

        const uint8_t fdiv[] = {0xDC, 0x36};
        const X87Decoded d = DecodeX87(fdiv, sizeof(fdiv));
        CHECK(d.ok && d.operandSize == 8 && !d.store);
        const uint8_t undefined[] = {0xD9, 0x08}; // D9 /1 memory: undefined
        CHECK(!DecodeX87(undefined, sizeof(undefined)).ok);
    }

    void TestDecodeRegisterForm()
    {
        const uint8_t fdivp[] = {0xDE, 0xF9, 0x90};
        const X87Decoded d = DecodeX87(fdivp, sizeof(fdivp));
        CHECK(d.ok && d.length == 2 && !d.memory);
        CHECK(MatchesFop(d, 0x06F9));
        CHECK(!MatchesFop(d, 0x0601));
        CHECK(MatchesFop(d, 0)); // not recorded
        uint8_t out[16] = {};
        CHECK(BuildAbsoluteX87(fdivp, d, 0x12345678u, out, sizeof(out)) == 2);
        CHECK(out[0] == 0xDE && out[1] == 0xF9);
    }

    void TestDecodeMemoryForms()
    {
        uint8_t out[16] = {};
        // fdiv dword ptr [esi]
        const uint8_t a[] = {0xD8, 0x36};
        X87Decoded d = DecodeX87(a, sizeof(a));
        CHECK(d.ok && d.length == 2 && d.memory);
        CHECK(BuildAbsoluteX87(a, d, 0x00401000u, out, sizeof(out)) == 6);
        const uint8_t expectA[] = {0xD8, 0x35, 0x00, 0x10, 0x40, 0x00};
        CHECK(std::memcmp(out, expectA, sizeof(expectA)) == 0);

        // fdiv dword ptr [edx+ecx*4+4]: ModRM 74, SIB 8A, disp8
        const uint8_t b[] = {0xD8, 0x74, 0x8A, 0x04};
        d = DecodeX87(b, sizeof(b));
        CHECK(d.ok && d.length == 4 && d.memory);
        // fdiv qword ptr [ebp-0x1000]: disp32
        const uint8_t c[] = {0xDC, 0xB5, 0x00, 0xF0, 0xFF, 0xFF};
        d = DecodeX87(c, sizeof(c));
        CHECK(d.ok && d.length == 6);
        // fidiv dword ptr [0x00700000]: mod 0 rm 5
        const uint8_t e[] = {0xDA, 0x35, 0x00, 0x00, 0x70, 0x00};
        d = DecodeX87(e, sizeof(e));
        CHECK(d.ok && d.length == 6);
        // SIB with no base: [ecx*4+disp32]
        const uint8_t f[] = {0xD8, 0x34, 0x8D, 0x00, 0x00, 0x70, 0x00};
        d = DecodeX87(f, sizeof(f));
        CHECK(d.ok && d.length == 7);
        // fs: prefix is kept in the stub form
        const uint8_t g[] = {0x64, 0xD8, 0x30};
        d = DecodeX87(g, sizeof(g));
        CHECK(d.ok && d.length == 3 && d.prefixCount == 1);
        CHECK(BuildAbsoluteX87(g, d, 0x10u, out, sizeof(out)) == 7);
        CHECK(out[0] == 0x64 && out[1] == 0xD8 && out[2] == 0x35 && out[3] == 0x10);
        // capacity too small
        CHECK(BuildAbsoluteX87(g, d, 0x10u, out, 6) == 0);
    }

    void TestDecodeRejects()
    {
        const uint8_t notX87[] = {0x0F, 0x5E, 0xC1};
        CHECK(!DecodeX87(notX87, sizeof(notX87)).ok);
        const uint8_t opsize[] = {0x66, 0xD8, 0xF1};
        CHECK(!DecodeX87(opsize, sizeof(opsize)).ok);
        const uint8_t fnstsw[] = {0xDF, 0xE0};
        CHECK(!DecodeX87(fnstsw, sizeof(fnstsw)).ok);
        const uint8_t fnclex[] = {0xDB, 0xE2};
        CHECK(!DecodeX87(fnclex, sizeof(fnclex)).ok);
        const uint8_t fldcw[] = {0xD9, 0x2D, 0, 0, 0, 0};
        CHECK(!DecodeX87(fldcw, sizeof(fldcw)).ok);
        const uint8_t fnsave[] = {0xDD, 0x30};
        CHECK(!DecodeX87(fnsave, sizeof(fnsave)).ok);
        const uint8_t truncated[] = {0xD8, 0xB5, 0x00};
        CHECK(!DecodeX87(truncated, sizeof(truncated)).ok);
        const uint8_t one[] = {0xD8};
        CHECK(!DecodeX87(one, sizeof(one)).ok);
    }

    void TestWalk()
    {
        std::map<uint32_t, uint32_t> mem;
        // 0x1000 -> 0x1010 -> 0x1020 -> 0x0FF0 (goes down: stop)
        mem[0x1000] = 0x1010; mem[0x1004] = 0x00401111;
        mem[0x1010] = 0x1020; mem[0x1014] = 0x00402222;
        mem[0x1020] = 0x0FF0; mem[0x1024] = 0x00403333;
        auto read = [&](uint32_t a, uint32_t& v) {
            auto it = mem.find(a);
            if (it == mem.end())
                return false;
            v = it->second;
            return true;
        };
        uint32_t out[kStackDepth] = {};
        CHECK(WalkEbpFrames(0x1000, 0x0F00, 0x2000, read, out, kStackDepth) == 3);
        CHECK(out[0] == 0x00401111 && out[1] == 0x00402222 && out[2] == 0x00403333);
        CHECK(WalkEbpFrames(0x1000, 0x0F00, 0x2000, read, out, 2) == 2);
        CHECK(WalkEbpFrames(0x1002, 0x0F00, 0x2000, read, out, kStackDepth) == 0); // misaligned
        CHECK(WalkEbpFrames(0x3000, 0x0F00, 0x2000, read, out, kStackDepth) == 0); // off stack
        CHECK(WalkEbpFrames(0x1010, 0x1010, 0x1018, read, out, kStackDepth) == 1); // top bound
    }

    void TestFirstCallerOutside()
    {
        const uint32_t stack[] = {0x75A40010u, 0x76001234u, 0x00401111u, 0x00402222u};
        auto system = [](uint32_t a) { return a >= 0x70000000u; };
        CHECK(FirstCallerOutside(stack, 4, system) == 0x00401111u);
        CHECK(FirstCallerOutside(stack, 2, system) == 0x75A40010u); // all system: first frame
        CHECK(FirstCallerOutside(stack, 0, system) == 0u);
        auto none = [](uint32_t) { return false; };
        CHECK(FirstCallerOutside(stack, 4, none) == 0x75A40010u);
    }

    void TestTable()
    {
        TrapTable<3> table;
        bool isNew = false;
        TrapSite* a = table.Record(0x100, Kind::Sse, isNew);
        CHECK(a != nullptr && isNew && a->count == 1);
        CHECK(table.Record(0x100, Kind::Sse, isNew) == a && !isNew && a->count == 2);
        TrapSite* b = table.Record(0x100, Kind::X87, isNew); // same address, other unit
        CHECK(b != nullptr && b != a && isNew);
        TrapSite* c = table.Record(0x200, Kind::Sse, isNew);
        CHECK(c != nullptr && isNew);
        table.Record(0x200, Kind::Sse, isNew);
        table.Record(0x200, Kind::Sse, isNew);
        CHECK(table.Record(0x300, Kind::Sse, isNew) == nullptr && !isNew);
        CHECK(table.Size() == 3);
        CHECK(table.Dropped() == 1);
        CHECK(table.Total() == 7);
        uint16_t order[3] = {};
        CHECK(table.SortedByCount(order, 3) == 3);
        CHECK(order[0] == 2 && order[1] == 0 && order[2] == 1);
    }

    void TestNames()
    {
        CHECK(std::strcmp(FlagsName(0x01), "IE") == 0);
        CHECK(std::strcmp(FlagsName(0x04), "ZE") == 0);
        CHECK(std::strcmp(FlagsName(0x05), "IE|ZE") == 0);
        CHECK(std::strcmp(FlagsName(0x20), "other") == 0);
        CHECK(std::strcmp(KindName(Kind::X87), "x87") == 0);
        CHECK(std::strcmp(KindName(Kind::Raised), "raised") == 0);
    }
}

int main()
{
    TestUnmaskAndMask();
    TestClassify();
    TestRecoveryState();
    TestGate();
    TestRaised();
    TestBelowStack();
    TestOperandSizes();
    TestDecodeRegisterForm();
    TestDecodeMemoryForms();
    TestDecodeRejects();
    TestWalk();
    TestFirstCallerOutside();
    TestTable();
    TestNames();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("fp_trap_log_policy_tests passed\n");
    return OpenShimTest::ExitCode();
}
