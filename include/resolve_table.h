#pragma once
// resolve_table.h
// BZR Open Shim - declarative address resolution table.
//
// scripts/patches.json already describes patch *sites*: places the shim
// overwrites bytes. A second kind of target has always existed alongside them
// and had no declarative home - addresses the shim only wants to *call* or
// read, resolved from a signature instead of patched. Those lived as
// hand-written uint8_t pattern/mask array pairs inside feature code, with two
// different mask conventions and a parallel mask array to keep in sync by eye.
//
// The "resolves" array in patches.json is that home. Entries are parsed here,
// away from <Windows.h>, so the mapping from JSON to target is testable on the
// host; hook_engine.cpp owns the scan that turns a target into an address.
//
// A signature is never identity on its own: a unique byte string can belong to
// a function you did not mean. Every entry therefore carries an `identity`
// note recording the independent proof (a call site, an xref, a decompile) and
// that note is echoed in the resolution log line.
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim
{
    // How the matched pattern maps to the address the name stands for.
    enum class ResolveMode : uint8_t
    {
        // The anchor itself is the address (function entry, call site, global).
        Address,
        // The anchor is an E8 CALL rel32; the address is its call target.
        Rel32Target,
    };

    // Which source wins when a scan and a fallback constant are both usable.
    // Data-driven so a signature that misfires on a live build can be demoted
    // by editing patches.json, with no rebuild.
    enum class ResolvePreference : uint8_t
    {
        Scan,
        Fallback,
    };

    struct ResolveTarget
    {
        std::string name;
        // IDA-style pattern text, e.g. "8B 45 08 50 E8 ?? ?? ?? ??". Kept as
        // text here; hook_engine parses it with the same ParseIdaPattern the
        // "patches" array uses.
        std::string ida_pattern;
        // Signed: an anchor may legitimately sit before the match, as it does
        // for a function whose prologue is too generic to carry in a pattern.
        int32_t offset = 0;
        ResolveMode mode = ResolveMode::Address;
        ResolvePreference preference = ResolvePreference::Scan;
        // When set, a pattern matching more than once resolves to nothing
        // rather than silently taking the first hit.
        bool require_unique = false;
        // Known-good constant for the shipped build; 0 when absent.
        uint32_t fallback_addr = 0;
        // Why this pattern is the thing it claims to be. Documentation that
        // reaches the log, not an input to matching.
        std::string identity;
    };

    // Parses the "resolves" array out of patches.json text. Returns the
    // entries that parsed; on malformed input, appends a human-readable reason
    // to `error` (when non-null) and skips the offending entry rather than
    // failing the whole table - one bad entry must not disarm the others.
    std::vector<ResolveTarget> ParseResolveTable(const std::string& jsonText,
                                                 std::string* error = nullptr);

    // Shared IDA-pattern parser. 0x100 marks a wildcard byte; a token that is
    // neither "?"/"??" nor a hex byte yields an empty result, so a typo fails
    // the whole pattern closed instead of matching something shorter.
    std::vector<uint16_t> ParseIdaPatternText(const std::string& hex);
}
