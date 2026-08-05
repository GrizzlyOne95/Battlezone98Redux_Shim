#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace BZROpenShim
{
    // Pure ini-document helpers shared by the settings UI and the openshim.ini
    // writer. No engine or Win32 dependencies beyond <filesystem>, so the
    // lossless-update logic is unit-testable in isolation
    // (scripts/run_ini_tests.ps1 builds tests/ini_writer_tests.cpp against
    // this translation unit).

    bool IniLineIsSectionHeader(const std::string& line, std::string& outName);
    bool IniLineMatchesKey(const std::string& line, const char* key);

    // Applies "key = value" losslessly to the document lines: only the matched
    // line changes; comments, blank lines, ordering, and unrelated keys
    // survive verbatim. The key is matched case-insensitively, first under its
    // canonical name and then under any legacy alias, within the named section
    // only. A missing key appends at the end of its section (before trailing
    // blank lines); a missing section is created at the end of the document.
    void UpdateIniDocumentValueLossless(std::vector<std::string>& lines,
                                        const char* section,
                                        const char* key,
                                        const char* const* altKeys,
                                        size_t altKeyCount,
                                        const char* value);

    // Reads a text file into lines with trailing CR/LF stripped. A missing or
    // unreadable file yields an empty vector.
    std::vector<std::string> ReadTextFileLines(const std::filesystem::path& path);
}
