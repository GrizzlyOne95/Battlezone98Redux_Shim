#include "objective_objects_fix.h"

#include <cstdint>
#include <cstring>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::ObjectiveObjectsFix;

    constexpr uint32_t kGogBase = 0x00502760; // scripts/patches.json fallback

    // GOG Redux 2.2.301 step body at kGogBase, and the replacement the
    // builder must produce for it (checked with a disassembler when written).
    constexpr uint8_t kGogStock[kBodyLen] = {
        0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x68, 0xED, 0xD8, 0xFF, 0xFF, 0x8B,
        0x45, 0x08, 0x50, 0xE8, 0xC4, 0xAB, 0x32, 0x00, 0x83, 0xC4, 0x08, 0x89,
        0x45, 0xF8, 0x8B, 0x4D, 0xF8, 0x3B, 0x0D, 0xF8, 0x7A, 0x91, 0x00, 0x7D,
        0x79, 0x8B, 0x55, 0xF8, 0x8B, 0x04, 0x95, 0x78, 0x7A, 0x91, 0x00, 0x89,
        0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x61, 0x8B, 0x4D, 0xFC, 0x83,
        0xC1, 0x18, 0x8B, 0x55, 0xFC, 0x8B, 0x42, 0x18, 0x8B, 0x50, 0x30, 0xFF,
        0xD2, 0x89, 0x45, 0xF4, 0x8B, 0x45, 0xF4, 0x8B, 0x48, 0x14, 0x81, 0xE1,
        0x00, 0x02, 0x00, 0x00, 0x74, 0x02, 0xEB, 0xBE, 0x8B, 0x55, 0xF8, 0x52,
        0x8B, 0x45, 0x08, 0x50, 0xE8, 0x01, 0xA5, 0x32, 0x00, 0x83, 0xC4, 0x08,
        0x68, 0xED, 0xD8, 0xFF, 0xFF, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0xFE, 0xA7,
        0x32, 0x00, 0x83, 0xC4, 0x08, 0x8B, 0x4D, 0xFC, 0xE8, 0x9B, 0xFB, 0xF5,
        0xFF, 0x50, 0x8B, 0x55, 0x08, 0x52, 0xE8, 0x81, 0xCF, 0xFF, 0xFF, 0x83,
        0xC4, 0x08, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xE9, 0x7C, 0xFF,
        0xFF, 0xFF, 0x33, 0xC0, 0x8B, 0xE5, 0x5D, 0xC3,
    };
    constexpr uint8_t kGogPatched[kBodyLen] = {
        0x55, 0x8B, 0xEC, 0x56, 0x57, 0x68, 0xED, 0xD8, 0xFF, 0xFF, 0xFF, 0x75,
        0x08, 0xE8, 0xC6, 0xAB, 0x32, 0x00, 0x83, 0xC4, 0x08, 0x8B, 0x0D, 0xF8,
        0x7A, 0x91, 0x00, 0x83, 0xF9, 0x20, 0x76, 0x05, 0xB9, 0x20, 0x00, 0x00,
        0x00, 0x8D, 0x71, 0xFF, 0x85, 0xC0, 0x74, 0x07, 0xBE, 0xFE, 0xFF, 0xFF,
        0xFF, 0x2B, 0xF0, 0x3B, 0xF1, 0x7C, 0x03, 0x8D, 0x71, 0xFF, 0x85, 0xF6,
        0x7C, 0x58, 0x8B, 0x3C, 0xB5, 0x78, 0x7A, 0x91, 0x00, 0x4E, 0x85, 0xFF,
        0x74, 0xF0, 0x8D, 0x4F, 0x18, 0x8B, 0x47, 0x18, 0xFF, 0x50, 0x30, 0xF6,
        0x40, 0x15, 0x02, 0x75, 0xE1, 0xB8, 0xFE, 0xFF, 0xFF, 0xFF, 0x2B, 0xC6,
        0x50, 0xFF, 0x75, 0x08, 0xE8, 0x01, 0xA5, 0x32, 0x00, 0x83, 0xC4, 0x08,
        0x68, 0xED, 0xD8, 0xFF, 0xFF, 0xFF, 0x75, 0x08, 0xE8, 0xFF, 0xA7, 0x32,
        0x00, 0x83, 0xC4, 0x08, 0x8B, 0xCF, 0xE8, 0x9D, 0xFB, 0xF5, 0xFF, 0x50,
        0xFF, 0x75, 0x08, 0xE8, 0x84, 0xCF, 0xFF, 0xFF, 0x83, 0xC4, 0x08, 0xB8,
        0x01, 0x00, 0x00, 0x00, 0xEB, 0x02, 0x33, 0xC0, 0x5F, 0x5E, 0x5D, 0xC3,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    };

    void TestTables()
    {
        // The masked stock table agrees with the GOG bytes everywhere but the
        // operands, and the same holds for the replacement.
        for (size_t i = 0; i < kBodyLen; ++i)
        {
            if (!IsOperandByte(kStockLayout, i))
                CHECK(kStockBody[i] == kGogStock[i]);
            if (!IsOperandByte(kPatchedLayout, i))
                CHECK(kPatchedBody[i] == kGogPatched[i]);
        }
        // Each call operand follows an E8; the globals follow their opcodes.
        const size_t stockCalls[] = { kStockLayout.toInteger, kStockLayout.pushInteger, kStockLayout.replace,
                                      kStockLayout.getHandle, kStockLayout.pushHandle };
        for (size_t at : stockCalls)
            CHECK(kStockBody[at - 1] == 0xE8);
        const size_t patchedCalls[] = { kPatchedLayout.toInteger, kPatchedLayout.pushInteger, kPatchedLayout.replace,
                                        kPatchedLayout.getHandle, kPatchedLayout.pushHandle };
        for (size_t at : patchedCalls)
            CHECK(kPatchedBody[at - 1] == 0xE8);
        CHECK(kStockBody[kStockLayout.count - 2] == 0x3B && kStockBody[kStockLayout.count - 1] == 0x0D);
        CHECK(kStockBody[kStockLayout.list - 1] == 0x95);
        CHECK(kPatchedBody[kPatchedLayout.count - 2] == 0x8B && kPatchedBody[kPatchedLayout.count - 1] == 0x0D);
        CHECK(kPatchedBody[kPatchedLayout.list - 1] == 0xB5);
        // Same length, ends in a ret then int3 padding.
        CHECK(kGogStock[kBodyLen - 1] == 0xC3);
        CHECK(kGogPatched[0x9B] == 0xC3);
        for (size_t i = 0x9C; i < kBodyLen; ++i)
            CHECK(kGogPatched[i] == 0xCC);
        // Flag test: `and ecx,0x200` on dword +0x14 == `test byte [eax+0x15],2`.
        for (uint32_t bit = 0; bit < 32; ++bit)
        {
            const uint32_t flags = 1u << bit;
            uint8_t bytes[4];
            std::memcpy(bytes, &flags, sizeof(bytes));
            CHECK(((flags & 0x200u) != 0) == ((bytes[1] & 0x02u) != 0));
        }
    }

    void TestClassify()
    {
        CHECK(Classify(kGogStock) == BodyState::Stock);
        CHECK(Classify(kGogPatched) == BodyState::Patched);

        // Moved addresses still classify (operands are masked).
        uint8_t moved[kBodyLen];
        std::memcpy(moved, kGogStock, sizeof(moved));
        moved[kStockLayout.count] ^= 0x10;
        moved[kStockLayout.getHandle + 1] ^= 0x20;
        CHECK(Classify(moved) == BodyState::Stock);

        // Any change outside the operands stands down.
        for (size_t i = 0; i < kBodyLen; ++i)
        {
            if (IsOperandByte(kStockLayout, i))
                continue;
            uint8_t b[kBodyLen];
            std::memcpy(b, kGogStock, sizeof(b));
            b[i] ^= 0x01;
            CHECK(Classify(b) == BodyState::Unknown);
        }

        // A half-written body is neither stock nor patched.
        uint8_t half[kBodyLen];
        std::memcpy(half, kGogStock, sizeof(half));
        std::memcpy(half, kGogPatched, 0x40);
        CHECK(Classify(half) == BodyState::Unknown);
    }

    void TestBuild()
    {
        const Operands o = ExtractStockOperands(kGogStock, kGogBase);
        CHECK(o.toInteger == 0x0082D338);
        CHECK(o.count == 0x00917AF8);
        CHECK(o.list == 0x00917A78);
        CHECK(o.pushInteger == 0x0082CCCA);
        CHECK(o.replace == 0x0082CFD8);
        CHECK(o.getHandle == 0x00462380);
        CHECK(o.pushHandle == 0x004FF770);
        CHECK(LayoutMatches(o));
        Operands bad = o;
        bad.count += 4;
        CHECK(!LayoutMatches(bad));

        uint8_t out[kBodyLen] = {};
        BuildPatchedBody(o, kGogBase, out);
        CHECK(std::memcmp(out, kGogPatched, sizeof(out)) == 0);

        // Same function loaded elsewhere: same targets, new rel32s.
        const uint32_t other = kGogBase + 0x1000;
        BuildPatchedBody(o, other, out);
        CHECK(RelTarget(out, other, kPatchedLayout.toInteger) == o.toInteger);
        CHECK(RelTarget(out, other, kPatchedLayout.pushHandle) == o.pushHandle);
        CHECK(Classify(out) == BodyState::Patched);
    }

    // Engine list model: slots[0..count), 0 = null, skip[] = class flag 0x200.
    // SetObjectiveOff swap-removes like the engine: count--, slot[i] = slot[count].
    struct List
    {
        std::vector<int> slots;
        std::vector<int> flagged;

        bool Skipped(int obj) const
        {
            for (int f : flagged)
            {
                if (f == obj)
                    return true;
            }
            return false;
        }

        void Remove(int obj)
        {
            for (size_t i = 0; i < slots.size(); ++i)
            {
                if (slots[i] == obj)
                {
                    slots[i] = slots.back();
                    slots.pop_back();
                    return;
                }
            }
        }
    };

    // Stock step: returns the object, 0 for nil, -1 if it would spin.
    int StockStep(const List& l, int& up)
    {
        const int index = up;
        for (int guard = 0; guard < 1000; ++guard)
        {
            if (index >= static_cast<int>(l.slots.size()))
                return 0;
            const int obj = l.slots[index];
            if (obj == 0 || l.Skipped(obj))
                continue; // same index again
            up = index;
            return obj;
        }
        return -1;
    }

    // Fixed step, following the replacement body's register logic.
    int FixedStep(const List& l, int& up)
    {
        int count = static_cast<int>(l.slots.size());
        if (count > static_cast<int>(kListSlots))
            count = static_cast<int>(kListSlots);
        int esi = count - 1;
        if (up != 0)
            esi = -2 - up;
        if (esi >= count)
            esi = count - 1;
        while (esi >= 0)
        {
            const int obj = l.slots[esi];
            --esi;
            if (obj == 0 || l.Skipped(obj))
                continue;
            up = -2 - esi;
            CHECK(up != 0);
            return obj;
        }
        return 0;
    }

    std::vector<int> Walk(List& l, bool clearEach, int removeOnFirst = 0)
    {
        std::vector<int> seen;
        int up = 0;
        for (int i = 0; i < 100; ++i)
        {
            const int obj = FixedStep(l, up);
            if (obj == 0)
                return seen;
            seen.push_back(obj);
            if (clearEach)
                l.Remove(obj);
            if (removeOnFirst && seen.size() == 1)
                l.Remove(removeOnFirst);
        }
        CHECK(false); // did not end
        return seen;
    }

    void TestIteratorModel()
    {
        // Stock: the first object every time; a skipped first slot spins.
        {
            List l{ { 11, 22, 33 }, {} };
            int up = 0;
            for (int i = 0; i < 5; ++i)
                CHECK(StockStep(l, up) == 11);
            List s{ { 11, 22, 33 }, { 11 } };
            up = 0;
            CHECK(StockStep(s, up) == -1);
        }
        // Fixed: each once, top down; nulls and flagged classes skipped.
        {
            List l{ { 11, 22, 33 }, {} };
            CHECK((Walk(l, false) == std::vector<int>{ 33, 22, 11 }));
            List s{ { 11, 0, 22, 33 }, { 33, 11 } };
            CHECK((Walk(s, false) == std::vector<int>{ 22 }));
            List e{ {}, {} };
            CHECK(Walk(e, false).empty());
            List one{ { 11 }, {} };
            CHECK((Walk(one, false) == std::vector<int>{ 11 }));
        }
        // Clear-all idiom: SetObjectiveOff on each one clears the whole list.
        {
            List l{ { 11, 22, 33, 44, 55 }, {} };
            CHECK((Walk(l, true) == std::vector<int>{ 55, 44, 33, 22, 11 }));
            CHECK(l.slots.empty());
        }
        // Documented caveat: removing a not-yet-visited object moves the top
        // object down into its slot, so that object is listed again.
        {
            List l{ { 11, 22, 33 }, {} };
            CHECK((Walk(l, false, 11) == std::vector<int>{ 33, 22, 33 }));
        }
        // An overflowed list (count past 32) reads only the 32 slots.
        {
            List l{ std::vector<int>(40, 7), {} };
            CHECK(Walk(l, false).size() == kListSlots);
        }
        // A list that shrank between calls is clamped, not overrun.
        {
            List l{ { 11, 22, 33, 44 }, {} };
            int up = 0;
            CHECK(FixedStep(l, up) == 44);
            l.slots = { 11 };
            CHECK(FixedStep(l, up) == 11);
            CHECK(FixedStep(l, up) == 0);
        }
    }
}

int main()
{
    TestTables();
    TestClassify();
    TestBuild();
    TestIteratorModel();
    return OpenShimTest::ExitCode();
}
