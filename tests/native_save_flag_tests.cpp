// native_save_flag_tests.cpp
// Host-side checks for the missionSave operand decode used by OpenShim autosave.
//
// Copyright (C) 2025-2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// An autosave must run with missionSave=0 or the engine skips runType,
// saveGameDesc, the mission-status block, start_time and the whole [AiTasks]
// section, and the matching load path skips its post-load handle remap. The
// address of that flag is decoded out of the qualified SaveGame prolog rather
// than hard-coded, so these checks pin the decode and every way it must fail
// closed when a build drifts out from under the signature.

#include "native_save_flag.h"

#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace BZROpenShim::NativeSaveFlag;

namespace
{
    int g_failures = 0;

    void Expect(bool condition, const std::string& what)
    {
        if (!condition)
        {
            ++g_failures;
            std::cerr << "FAIL: " << what << '\n';
        }
    }

    // The real bytes at battlezone98redux.exe VA 0x004FD190 (GOG 2.2.301),
    // truncated to the region the decode reads. Byte 37 begins 0F B6 05 and the
    // operand that follows is 0x009173B7, the missionSave global.
    std::array<uint8_t, kProbeSize> RealPrologue()
    {
        return {
            0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x94, 0x00, 0x00, 0x00, 0xC6, 0x45, 0xFF,
            0x01, 0xE8, 0xDE, 0xCA, 0xFD, 0xFF, 0x89, 0x85, 0x78, 0xFF, 0xFF, 0xFF,
            0x68, 0xE0, 0xEF, 0xCE, 0x02, 0xE8, 0x4E, 0x16, 0x00, 0x00, 0x83, 0xC4,
            0x04, 0x0F, 0xB6, 0x05, 0xB7, 0x73, 0x91, 0x00,
        };
    }

    void TestDecodesTheShippingPrologue()
    {
        const auto prologue = RealPrologue();
        Expect(
            ReadFlagAddress(prologue.data()) == 0x009173B7u,
            "the shipping SaveGame prolog decodes to the missionSave global");
    }

    void TestOpcodeOffsetIsWhereTheSignaturePinsIt()
    {
        const auto prologue = RealPrologue();
        Expect(kOpcodeOffset == 37, "the movzx sits at entry +37");
        Expect(prologue[37] == 0x0F, "entry +37 is 0F");
        Expect(prologue[38] == 0xB6, "entry +38 is B6");
        Expect(prologue[39] == 0x05, "entry +39 is 05");
        Expect(kOperandOffset == 40, "the operand starts at entry +40");
    }

    void TestNullEntryFailsClosed()
    {
        Expect(ReadFlagAddress(nullptr) == 0, "a null entry decodes to 0");
    }

    // Each of these is a build drifting out from under the signature. None may
    // produce an address: a wrong one would be written to during every autosave.
    void TestDriftedOpcodeFailsClosed()
    {
        for (std::size_t byte = 0; byte < 3; ++byte)
        {
            auto prologue = RealPrologue();
            prologue[kOpcodeOffset + byte] ^= 0xFF;
            Expect(
                ReadFlagAddress(prologue.data()) == 0,
                "a corrupted movzx opcode byte " + std::to_string(byte) + " decodes to 0");
        }
    }

    void TestShiftedPrologueFailsClosed()
    {
        // A one-byte shift is the shape a recompiled prolog takes, and it leaves
        // the operand reading plausible-but-wrong bytes if the opcode is not
        // checked first.
        const auto real = RealPrologue();
        std::array<uint8_t, kProbeSize> shifted{};
        std::memcpy(shifted.data() + 1, real.data(), shifted.size() - 1);
        Expect(
            ReadFlagAddress(shifted.data()) == 0,
            "a prolog shifted by one byte decodes to 0");
    }

    void TestZeroOperandIsIndistinguishableFromFailure()
    {
        auto prologue = RealPrologue();
        std::memset(prologue.data() + kOperandOffset, 0, sizeof(uint32_t));
        Expect(
            ReadFlagAddress(prologue.data()) == 0,
            "a null operand decodes to 0 so callers treat it as failure");
    }

    void TestOperandIsReadLittleEndian()
    {
        auto prologue = RealPrologue();
        prologue[kOperandOffset + 0] = 0x78;
        prologue[kOperandOffset + 1] = 0x56;
        prologue[kOperandOffset + 2] = 0x34;
        prologue[kOperandOffset + 3] = 0x12;
        Expect(
            ReadFlagAddress(prologue.data()) == 0x12345678u,
            "the absolute operand is decoded little-endian");
    }

    void TestOnlyBooleanFlagValuesAreAccepted()
    {
        Expect(IsPlausibleValue(0), "missionSave=0 is plausible");
        Expect(IsPlausibleValue(1), "missionSave=1 is plausible");
        Expect(!IsPlausibleValue(2), "missionSave=2 is rejected");
        Expect(!IsPlausibleValue(0xCD), "uninitialised fill is rejected");
        Expect(!IsPlausibleValue(0xFF), "missionSave=0xFF is rejected");
    }
}

int main()
{
    TestDecodesTheShippingPrologue();
    TestOpcodeOffsetIsWhereTheSignaturePinsIt();
    TestNullEntryFailsClosed();
    TestDriftedOpcodeFailsClosed();
    TestShiftedPrologueFailsClosed();
    TestZeroOperandIsIndistinguishableFromFailure();
    TestOperandIsReadLittleEndian();
    TestOnlyBooleanFlagValuesAreAccepted();

    if (g_failures != 0)
    {
        std::cerr << g_failures << " missionSave decode check(s) failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "All missionSave decode checks passed.\n";
    return EXIT_SUCCESS;
}
