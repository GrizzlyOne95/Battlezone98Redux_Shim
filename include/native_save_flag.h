#pragma once

// Byte-level decoding of Redux's missionSave global out of the already-qualified
// SaveGame prolog.
//
// Kept free of Windows and of the game's memory layout so the decode and, more
// importantly, every way it must fail closed can be exercised on the host by
// tests/native_save_flag_tests.cpp. autosave.cpp wraps the calls below in SEH
// and does the actual pointer dereference.
//
// Why this matters: a direct SaveGame call must temporarily run with missionSave=0,
// then restore the prior byte so an outer native mission-save operation keeps its state. When the
// flag is set, FUN_004fd190 skips runType, saveGameDesc, the mission-status
// block (FUN_004fd7e0), start_time and the whole [AiTasks] section
// (FUN_00461d90), and the matching load path skips the post-load handle remap in
// FUN_005c7a50. FUN_004fbe90 (the mission/terrain-template save) sets the flag
// and never clears it, so any caller that does not establish its own value
// inherits whatever the last mission save left behind.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::NativeSaveFlag
{
    // The qualified SaveGame signature pins `movzx eax, byte ptr [missionSave]`
    // at entry +37, with the four-byte absolute operand immediately after the
    // 0F B6 05 opcode. The offset is not a guess: bytes 37..39 are literals in
    // the signature itself, so a signature match already proves the opcode is
    // there. Verified against GOG 2.2.301, where the operand reads 0x009173B7.
    inline constexpr std::size_t kOpcodeOffset = 37;
    inline constexpr std::size_t kOperandOffset = kOpcodeOffset + 3;
    inline constexpr std::size_t kProbeSize = kOperandOffset + sizeof(uint32_t);

    // Returns the absolute address of the missionSave byte, or 0 when the prolog
    // does not match. Zero always means "fail closed", never a usable address.
    inline uint32_t ReadFlagAddress(const uint8_t* entry) noexcept
    {
        if (entry == nullptr)
            return 0;

        if (entry[kOpcodeOffset] != 0x0F ||
            entry[kOpcodeOffset + 1] != 0xB6 ||
            entry[kOpcodeOffset + 2] != 0x05)
            return 0;

        uint32_t address = 0;
        std::memcpy(&address, entry + kOperandOffset, sizeof(address));
        return address;
    }

    // missionSave is a bool byte; the engine only ever stores 0 or 1. Anything
    // else means the operand did not land on the flag.
    inline bool IsPlausibleValue(uint8_t value) noexcept
    {
        return value <= 1;
    }
}
