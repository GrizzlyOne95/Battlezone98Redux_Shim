#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace HookEngine
{
    enum class PatchType : uint8_t
    {
        JMP5,       // 5-byte relative JMP:  E9 rel32
        REL32,      // 4-byte relative operand (CALL/JMP rel32)
        DWORD,      // 4-byte DWORD overwrite
        BYTE1,      // 1-byte overwrite
        BYTES,      // raw byte array
    };

    struct PatchDef
    {
        uint32_t address;
        PatchType type;
        std::vector<uint8_t> payload;
        std::string name;
        bool verified;
        std::vector<uint8_t> expected_original;
    };

    struct ScanTarget {
        std::string name;
        std::string ida_pattern;
        uint32_t offset;
        uint32_t expected_size;
        uint32_t fallback_addr;
        bool require_unique = false;
    };

    // Core Memory Utilities
    bool ApplyPatch(const PatchDef& patch);
    bool WriteMemory(uint32_t address, const void* data, size_t len);
    bool ReadMemory(uint32_t address, void* buffer, size_t len);

    // Pattern Scanning
    void ScanForPatterns(const std::string& moduleName, std::vector<PatchDef>& patches, const std::vector<ScanTarget>& targets);
    std::vector<uint8_t> ParseHexPattern(const std::string& hex);
    std::vector<uint16_t> ParseIdaPattern(const std::string& hex);

    // Helpers
    void* ResolveRelCallTarget(uint32_t instrAddr);
    void* ResolveRelCallTargetWithRetry(uint32_t instrAddr, int maxAttempts, uint32_t delayMs);
    std::vector<uint8_t> MakeJmp5Payload(uint32_t src, uint32_t dst, size_t total_len = 5);
}
