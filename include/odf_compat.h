#pragma once

// odf_compat.h
// BZR Open Shim - Battlezone 98 Redux ODF legacy-section compatibility core.
//
// Pure, portable text layer (no Win32, no engine linkage) so it stays
// unit-testable in isolation. The runtime hook layer (odf_item_hooks.*)
// feeds it ODF bytes intercepted at the engine item loader and applies the
// returned text.
//
// Background (BZ1_Source research/odf_loader_schema.json, redux_crosscheck):
// 1.5 resolved ODF keys across sections (file-global fallback); Redux
// requires section-exact matches. Legacy stock sections that 1.5 tolerated
// ([MagnetClass], [FlareBuildingClass], [ScavengerCraftClass],
// [SprayBuildngClass], bare [GameObject]/[SprayBomb]) are dead in Redux and
// yield prototype defaults or NULLs, which crash downstream (notably a NULL
// FlareMine payload). This layer renames such headers to canonical form,
// reports section headers seen nowhere in the retail corpus or loader set,
// and clamps ODF values that crash verified engine code paths.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace BZROpenShim
{
namespace OdfCompat
{

// Mirrors openshim.ini [ODF] keys. All default off (Redux-strict stock).
struct Options
{
    bool remapLegacySections = false;
    bool logUnknownSections = false;
    bool guardCrashValues = false;
};

struct SectionEvent
{
    std::string file;
    int line = 0; // 1-based
    std::string name; // header spelling found in the file
    std::string mappedTo; // canonical spelling (remaps only)
};

struct ValueEvent
{
    std::string file;
    int line = 0;
    std::string section; // canonical section holding the key
    std::string key; // key spelling found in the file
    std::string value; // original value token
    std::string action; // what was done, e.g. "clamped to 20.0"
};

struct ProcessResult
{
    std::string text; // output bytes; equals input when !changed
    std::vector<SectionEvent> remaps;
    std::vector<SectionEvent> unknowns; // deduplicated per (file, section)
    std::vector<ValueEvent> guards;
    bool changed = false;
};

// Case-insensitive ".odf" suffix test. Null-safe.
bool IsOdfFileName(const char* name);

// True for every section the 1.5/Redux loaders read plus every section
// spelling observed in the retail GOG StockODFFiles corpus (case-insensitive).
// Anything else is reported as unknown when logging is enabled.
bool IsKnownSection(std::string_view name);

// Legacy header spelling -> canonical loader section, or nullptr.
// Case-insensitive; covers the seven headers 1.5 tolerated and Redux drops.
const char* CanonicalSectionFor(std::string_view name);

// Scans one ODF document. Never throws. Output preserves the input
// byte-for-byte except for replacements the enabled options request
// (legacy header renames, crash-value clamps), including original CRLF/LF.
ProcessResult ProcessOdfText(const char* fileName, const char* data, size_t size, const Options& opt);

} // namespace OdfCompat
} // namespace BZROpenShim
