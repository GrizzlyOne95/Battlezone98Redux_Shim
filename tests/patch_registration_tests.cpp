// patch_registration_tests.cpp
// Cross-checks the places a patch has to be registered, in both directions.
//
// WHY THIS EXISTS
// ===============
//
// A patch is only live when two files agree, and one direction of disagreement
// is completely silent:
//
//   include/patches.h      the patch list the patcher actually walks
//   scripts/patches.json   where that entry gets its address, from either the
//                          "patches" array (signature scan) or the "globals"
//                          array (direct address)
//
// A name in patches.json but NOT in patches.h is never walked, so it produces
// no [PATCH-SCAN] line, no [OK], no [SKIP] and no [STALE-CONFIG] -- nothing at
// all. On 2026-09-07 a null-carrier guard was added that way and looked exactly
// like a signature that had failed to match; it cost a build-and-run cycle to
// notice the patch had never been attempted.
//
// The reverse -- a name in patches.h with no patches.json entry -- resolves to
// address 0 and IS reported at runtime as [STALE-CONFIG], because that is the
// shape a stale deployed patches.json takes. Catching it here too makes it a
// build failure instead of something found on someone's machine.
//
// The "globals" array has the silent direction too: a direct-address entry is
// applied only to a patch-list entry of the same name, so a global that
// patches.h never lists is read, parsed and then dropped without a line in the
// log. Eleven were in that state when the check was added (the map filter
// port and three superseded version-notice sites). An entry that is meant to
// sit unwalked says so with a "parked" key giving the reason; one that is
// parked AND listed is a stale marker and fails as well.
//
// The "resolves" array has the same hazard from a different direction:
// HookEngine::ResolveNamedAddress takes a string, so a typo or a missing entry
// shows up only as a silent fallback at runtime. Every file under src/ is
// scanned for calls, since a hand-kept list of callers is itself the thing
// that goes stale: the three shell names in ui_performance_hooks.cpp had no
// entry for as long as that file was not on the list.
//
// These are text checks over the repository's own sources rather than anything
// clever. That is deliberate: the failure being prevented is a name present in
// one file and absent from another, so comparing the names as text is exactly
// the right shape.

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    int g_Failures = 0;

    void Fail(const std::string& what)
    {
        std::fprintf(stderr, "FAIL: %s\n", what.c_str());
        ++g_Failures;
    }

    void Check(bool condition, const std::string& what)
    {
        if (!condition) Fail(what);
    }

    std::string ReadFile(const char* path, bool& ok)
    {
        std::ifstream f(path, std::ios::binary);
        ok = f.is_open();
        if (!ok) return {};
        std::ostringstream buf;
        buf << f.rdbuf();
        return buf.str();
    }

    // Extracts one top-level array by key, matching brackets so a nested array
    // inside an entry cannot end the section early.
    std::string JsonArraySection(const std::string& text, const std::string& key, bool& found)
    {
        found = false;
        const std::string needle = "\"" + key + "\"";
        const size_t at = text.find(needle);
        if (at == std::string::npos) return {};
        const size_t open = text.find('[', at);
        if (open == std::string::npos) return {};

        int depth = 0;
        bool inString = false;
        bool escaped = false;
        for (size_t i = open; i < text.size(); ++i)
        {
            const char c = text[i];
            if (inString)
            {
                if (escaped)            escaped = false;
                else if (c == '\\')     escaped = true;
                else if (c == '"')      inString = false;
                continue;
            }
            if (c == '"') { inString = true; continue; }
            if (c == '[') ++depth;
            else if (c == ']')
            {
                if (--depth == 0)
                {
                    found = true;
                    return text.substr(open, i - open + 1);
                }
            }
        }
        return {};
    }

    // Every `"name": "value"` in one array section, in file order.
    std::set<std::string> NameValues(const std::string& section)
    {
        std::set<std::string> out;
        const std::string needle = "\"name\"";
        size_t pos = 0;
        while ((pos = section.find(needle, pos)) != std::string::npos)
        {
            const size_t colon = section.find(':', pos + needle.size());
            if (colon == std::string::npos) break;
            const size_t open = section.find('"', colon);
            if (open == std::string::npos) break;
            const size_t close = section.find('"', open + 1);
            if (close == std::string::npos) break;
            out.insert(section.substr(open + 1, close - open - 1));
            pos = close;
        }
        return out;
    }

    // Names from the patch list in include/patches.h. Every entry is written as
    //     { 0, HookEngine::PatchType::XXX, {}, "Name", false, {} },
    // so the name is the first string literal after the empty payload braces.
    std::set<std::string> PatchListNames(const std::string& header)
    {
        std::set<std::string> names;
        std::istringstream lines(header);
        std::string line;
        while (std::getline(lines, line))
        {
            const size_t type = line.find("HookEngine::PatchType::");
            if (type == std::string::npos) continue;
            const size_t open = line.find('"', type);
            if (open == std::string::npos) continue;
            const size_t close = line.find('"', open + 1);
            if (close == std::string::npos) continue;
            names.insert(line.substr(open + 1, close - open - 1));
        }
        return names;
    }

    // The index one past the ')' that closes the '(' at `open`, skipping string
    // and character literals; npos when the text ends first.
    size_t MatchingParen(const std::string& text, size_t open)
    {
        int depth = 0;
        char quote = 0;
        bool escaped = false;
        for (size_t i = open; i < text.size(); ++i)
        {
            const char c = text[i];
            if (quote)
            {
                if (escaped)            escaped = false;
                else if (c == '\\')     escaped = true;
                else if (c == quote)    quote = 0;
                continue;
            }
            if (c == '"' || c == '\'') { quote = c; continue; }
            if (c == '(') ++depth;
            else if (c == ')' && --depth == 0) return i + 1;
        }
        return std::string::npos;
    }

    // Every string literal in a stretch of source, without its quotes.
    std::vector<std::string> StringLiterals(const std::string& text)
    {
        std::vector<std::string> out;
        size_t pos = 0;
        while ((pos = text.find('"', pos)) != std::string::npos)
        {
            std::string value;
            size_t i = pos + 1;
            for (; i < text.size() && text[i] != '"'; ++i)
            {
                if (text[i] == '\\' && i + 1 < text.size()) ++i;
                value += text[i];
            }
            out.push_back(value);
            pos = i + 1;
        }
        return out;
    }

    struct SourceFile
    {
        std::string path;   // relative to src/, forward slashes
        std::string text;
    };

    // Every C++ source and header under `root`, in a stable order.
    std::vector<SourceFile> SourceTree(const std::filesystem::path& root, bool& ok)
    {
        std::vector<SourceFile> files;
        std::error_code ec;
        ok = std::filesystem::is_directory(root, ec);
        if (!ok) return files;
        for (std::filesystem::recursive_directory_iterator it(root, ec), end; !ec && it != end; it.increment(ec))
        {
            if (!it->is_regular_file(ec)) continue;
            const std::string ext = it->path().extension().string();
            if (ext != ".cpp" && ext != ".h" && ext != ".hpp" && ext != ".inl") continue;
            bool readOk = false;
            SourceFile file;
            file.path = std::filesystem::relative(it->path(), root, ec).generic_string();
            file.text = ReadFile(it->path().string().c_str(), readOk);
            if (!readOk) { ok = false; continue; }
            files.push_back(std::move(file));
        }
        if (ec) ok = false;
        std::sort(files.begin(), files.end(),
                  [](const SourceFile& a, const SourceFile& b) { return a.path < b.path; });
        return files;
    }

    // Every name handed to HookEngine::ResolveNamedAddress anywhere in the
    // tree. The argument is read up to its closing parenthesis, so a call
    // split across lines and a conditional choosing between two names both
    // count. A call whose argument holds no literal cannot be checked here
    // and its file lands in `unchecked`; only the function's own signature
    // may take a variable.
    std::set<std::string> ResolveNamedAddressCallSites(const std::vector<SourceFile>& files,
                                                       std::set<std::string>& callers,
                                                       std::set<std::string>& unchecked)
    {
        std::set<std::string> names;
        const std::string needle = "ResolveNamedAddress(";
        for (const SourceFile& file : files)
        {
            size_t pos = 0;
            while ((pos = file.text.find(needle, pos)) != std::string::npos)
            {
                const size_t open = pos + needle.size() - 1;
                const size_t close = MatchingParen(file.text, open);
                if (close == std::string::npos) break;
                const std::string argument = file.text.substr(open + 1, close - open - 2);
                pos = close;
                if (argument.find("const char*") != std::string::npos) continue;   // the signature itself
                const std::vector<std::string> literals = StringLiterals(argument);
                if (literals.empty()) { unchecked.insert(file.path); continue; }
                callers.insert(file.path);
                names.insert(literals.begin(), literals.end());
            }
        }
        return names;
    }

    // Each top-level object of one array section, braces included.
    std::vector<std::string> ArrayObjects(const std::string& section)
    {
        std::vector<std::string> out;
        int depth = 0;
        bool inString = false;
        bool escaped = false;
        size_t start = 0;
        for (size_t i = 0; i < section.size(); ++i)
        {
            const char c = section[i];
            if (inString)
            {
                if (escaped)            escaped = false;
                else if (c == '\\')     escaped = true;
                else if (c == '"')      inString = false;
                continue;
            }
            if (c == '"') { inString = true; continue; }
            if (c == '{') { if (depth++ == 0) start = i; }
            else if (c == '}' && --depth == 0) out.push_back(section.substr(start, i - start + 1));
        }
        return out;
    }

    std::string Join(const std::set<std::string>& values)
    {
        std::string out;
        for (const std::string& v : values)
        {
            if (!out.empty()) out += ", ";
            out += v;
        }
        return out;
    }
}

int main()
{
#if !defined(BZR_PATCHES_JSON) || !defined(BZR_PATCHES_H) || !defined(BZR_SRC_DIR)
    std::printf("patch_registration_tests: source paths not configured; skipped\n");
    return 0;
#else
    bool ok = false;
    const std::string json = ReadFile(BZR_PATCHES_JSON, ok);
    Check(ok, "scripts/patches.json must be readable at " BZR_PATCHES_JSON);
    bool headerOk = false;
    const std::string header = ReadFile(BZR_PATCHES_H, headerOk);
    Check(headerOk, "include/patches.h must be readable at " BZR_PATCHES_H);
    bool treeOk = false;
    const std::vector<SourceFile> sources = SourceTree(BZR_SRC_DIR, treeOk);
    Check(treeOk, "every source under src/ must be readable at " BZR_SRC_DIR);

    if (g_Failures)
    {
        std::fprintf(stderr, "patch_registration_tests: %d failure(s)\n", g_Failures);
        return 1;
    }

    bool hasPatches = false, hasResolves = false, hasGlobals = false;
    const std::string patchesSection = JsonArraySection(json, "patches", hasPatches);
    const std::string resolvesSection = JsonArraySection(json, "resolves", hasResolves);
    const std::string globalsSection = JsonArraySection(json, "globals", hasGlobals);
    Check(hasPatches, "patches.json must contain a \"patches\" array");
    Check(hasResolves, "patches.json must contain a \"resolves\" array");
    Check(hasGlobals, "patches.json must contain a \"globals\" array");
    if (g_Failures)
    {
        std::fprintf(stderr, "patch_registration_tests: %d failure(s)\n", g_Failures);
        return 1;
    }

    const std::set<std::string> jsonPatches = NameValues(patchesSection);
    const std::set<std::string> jsonResolves = NameValues(resolvesSection);
    const std::set<std::string> jsonGlobals = NameValues(globalsSection);
    const std::set<std::string> listed = PatchListNames(header);

    // A patch-list entry takes its address from either array: "patches" for a
    // signature scan, "globals" for a direct address.
    std::set<std::string> addressable = jsonPatches;
    addressable.insert(jsonGlobals.begin(), jsonGlobals.end());

    Check(!jsonPatches.empty(), "patches.json must define at least one signature-scanned patch");
    Check(!jsonGlobals.empty(), "patches.json must define at least one global");
    Check(!jsonResolves.empty(), "patches.json must define at least one resolve");
    Check(!listed.empty(), "include/patches.h must list at least one patch");

    // --- a signature nobody walks -------------------------------------------
    // The silent direction, and the one that cost a build-and-run cycle.
    {
        std::set<std::string> orphaned;
        for (const std::string& name : jsonPatches)
            if (listed.find(name) == listed.end()) orphaned.insert(name);
        if (!orphaned.empty())
        {
            Fail("scripts/patches.json defines signature patches that include/patches.h never "
                 "lists, so they are never attempted and log nothing at all: " + Join(orphaned) +
                 " -- add each to the patch list in include/patches.h");
        }
    }

    // --- a patch with no address source ---------------------------------------
    // Reported at runtime as [STALE-CONFIG]; failing here makes it a build error.
    {
        std::set<std::string> unaddressable;
        for (const std::string& name : listed)
            if (addressable.find(name) == addressable.end()) unaddressable.insert(name);
        if (!unaddressable.empty())
        {
            Fail("include/patches.h lists patches that scripts/patches.json gives no address, so "
                 "they resolve to 0 and are skipped: " + Join(unaddressable) +
                 " -- add an entry to the \"patches\" or \"globals\" array");
        }
    }

    // --- a global nobody walks ------------------------------------------------
    // A "globals" address is applied only to a patch-list entry of the same
    // name, so an unlisted one is dropped without a log line.
    size_t parkedCount = 0;
    {
        std::set<std::string> orphaned, staleParked;
        for (const std::string& entry : ArrayObjects(globalsSection))
        {
            const std::set<std::string> names = NameValues(entry);
            if (names.empty()) continue;
            const std::string& name = *names.begin();
            const bool parked = entry.find("\"parked\"") != std::string::npos;
            const bool isListed = listed.find(name) != listed.end();
            if (parked) ++parkedCount;
            if (!parked && !isListed) orphaned.insert(name);
            if (parked && isListed) staleParked.insert(name);
        }
        if (!orphaned.empty())
        {
            Fail("scripts/patches.json defines globals that include/patches.h never lists, so "
                 "their addresses are read and then dropped without a log line: " + Join(orphaned) +
                 " -- list each in include/patches.h, or give the entry a \"parked\" key saying "
                 "why it is kept unwalked");
        }
        if (!staleParked.empty())
        {
            Fail("scripts/patches.json marks globals \"parked\" that include/patches.h lists and "
                 "the patcher therefore applies: " + Join(staleParked) +
                 " -- drop the \"parked\" key");
        }
    }

    // --- a resolve name with no definition -----------------------------------
    std::set<std::string> resolveCallers;
    {
        std::set<std::string> unchecked;
        const std::set<std::string> used = ResolveNamedAddressCallSites(sources, resolveCallers, unchecked);
        // An empty result means the walk or the parse broke, not that nothing
        // resolves: the patcher alone resolves the AI names.
        Check(!used.empty(), "no ResolveNamedAddress call with a literal name was found under src/");
        std::set<std::string> undefined;
        for (const std::string& name : used)
            if (jsonResolves.find(name) == jsonResolves.end()) undefined.insert(name);
        if (!undefined.empty())
        {
            Fail("ResolveNamedAddress is called with names that scripts/patches.json does not "
                 "define, so they silently fall back: " + Join(undefined) +
                 " -- add each to the \"resolves\" array");
        }
        if (!unchecked.empty())
        {
            Fail("ResolveNamedAddress is called without a literal name in: " + Join(unchecked) +
                 " -- pass the name as a string literal so this test can check it");
        }
    }

    if (g_Failures == 0)
    {
        std::printf("patch_registration_tests: %zu patch-list entries cross-checked "
                    "(%zu signature, %zu global, %zu global(s) parked), %zu resolves used from "
                    "%zu of %zu source file(s)\n",
                    listed.size(), jsonPatches.size(), jsonGlobals.size(), parkedCount,
                    jsonResolves.size(), resolveCallers.size(), sources.size());
        return 0;
    }
    std::fprintf(stderr, "patch_registration_tests: %d failure(s)\n", g_Failures);
    return 1;
#endif
}
