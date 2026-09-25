// patch_config_parse.h
// Non-throwing readers for the scripts/patches.json document.
//
// The patcher reads patches.json on the patch thread, and a C++ exception
// escaping that thread is std::terminate: the game dies at launch with no log
// line naming the cause. nlohmann's typed accessors throw on a type mismatch,
// std::stoul throws on a bad hex string, and const operator[] on a missing
// key is undefined behaviour (it dereferences end() in a release build), so
// a hand-edited or half-deployed file could take the process down.
//
// Every reader here treats a malformed node as absent and says why in
// `error`, so the patcher can log the entry and continue with its in-code
// default. Nothing in this header touches Windows, so the readers run under
// the Linux host test lane against the shipped patches.json.

#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace BZROpenShim::PatchConfig
{
    enum class LookupStatus : uint8_t
    {
        Found,     // `out` holds the value
        Absent,    // no such entry; use the default silently
        Malformed, // an entry exists but is unusable; `error` says how
    };

    // "0x00494D35" or "494D35", with optional surrounding whitespace. Rejects
    // an empty digit run, non-hex characters, trailing text and values that
    // do not fit 32 bits. Never throws.
    bool ParseHexAddress32(const std::string& text, uint32_t& out);

    // The array at root[key], or nullptr when root is not an object, has no
    // such key, or the value is not an array.
    const nlohmann::json* ArraySection(const nlohmann::json& root, const char* key);

    // The string "name" of one array element, or "" when it has none.
    std::string EntryName(const nlohmann::json& node);

    // static_pointers[] { "name", "address": "0x..." }
    LookupStatus ReadStaticPointer(const nlohmann::json& root, const std::string& name,
                                   uint32_t& out, std::string& error);

    // features { name: bool }, then a top-level boolean of the same name.
    LookupStatus ReadFeatureBool(const nlohmann::json& root, const std::string& name,
                                 bool& out, std::string& error);

    // root[section].pattern, e.g. audio_gas_pattern.pattern.
    LookupStatus ReadSectionPattern(const nlohmann::json& root, const char* section,
                                    std::string& out, std::string& error);

    // One element of the "patches" array: a signature scan target.
    struct ScanEntry
    {
        std::string name;
        std::string pattern;
        uint32_t offset = 0;
        uint32_t expectedSize = 0;
        uint32_t fallback = 0;
        bool requireUnique = false;
    };

    // name, pattern, offset, expected_size and fallback are required;
    // require_unique is optional but must be a boolean when present.
    bool ParseScanEntry(const nlohmann::json& node, ScanEntry& out, std::string& error);

    // One element of the "globals" array: a direct address with a byte guard.
    struct GlobalEntry
    {
        std::string name;
        uint32_t fallback = 0;          // 0 when the entry names no address for this distribution
        std::string expectedOriginal;   // IDA-style byte pattern, parsed by the caller
    };

    // name and expected_original are required. The address comes from
    // fallback_steam (Steam) or fallback_gog (GOG) when present and non-zero,
    // otherwise from fallback; any of them that is present must be valid hex.
    bool ParseGlobalEntry(const nlohmann::json& node, bool isSteam, GlobalEntry& out, std::string& error);

    // Fills `out` with `length` bytes read at `address`; false when the memory
    // cannot be read. The patcher passes HookEngine::ReadMemory, the host
    // tests a fake image.
    using MemoryReader = std::function<bool(uint32_t address, size_t length, std::vector<uint8_t>& out)>;

    // The byte guard for a "patches" entry that takes its fallback address
    // because the signature scan found nothing.
    //
    // The fallback is trusted only when the entry's own pattern (wildcards
    // encoded as values >= 0x100, as ParseIdaPatternText emits them) is
    // present at fallback - offset, i.e. the recorded address really is the
    // site the signature describes. The guard is then the expected_size
    // bytes observed at the fallback address, exactly as the scan path
    // records them, so a wildcard in that window (a rel32 operand, say) is
    // guarded by the bytes this build has there rather than by a demand for
    // 0x00. Returns false with the reason in `error` when the fallback is 0,
    // the pattern is empty, expected_size is 0, offset reaches below address
    // 0, the window runs past the address space, the bytes cannot be read, or
    // a literal pattern byte differs from the byte at the site. Never throws.
    bool VerifyFallbackSite(const std::vector<uint16_t>& pattern, uint32_t fallback, uint32_t offset,
                            uint32_t expectedSize, const MemoryReader& read,
                            std::vector<uint8_t>& guard, std::string& error);
}
