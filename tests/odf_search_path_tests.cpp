// odf_search_path_tests.cpp
// Unit tests for ODF search-path construction and lookup, including mods
// that ship flat (all files at the mod root).

#include "odf_search_path.h"

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include "test_check.h"

namespace fs = std::filesystem;
using namespace BZROpenShim::OdfSearchPath;

namespace
{
void Touch(const fs::path& p)
{
    fs::create_directories(p.parent_path());
    std::ofstream(p) << "[x]\n";
}

bool Same(const fs::path& a, const fs::path& b)
{
    std::error_code ec;
    return fs::equivalent(a, b, ec) && !ec;
}
}

int main()
{
    const fs::path base = fs::weakly_canonical(fs::temp_directory_path()) /
        ("odf_search_path_tests_" +
         std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    fs::create_directories(base);

    const fs::path flat = base / "mods" / "flatmod";
    const fs::path structured = base / "addon" / "structmod";
    Touch(flat / "sxshield.odf");
    Touch(structured / "ODF" / "dup.odf");
    Touch(structured / "dup.odf");           // flat copy in the same mod
    Touch(structured / "mpfirst_mp.odf");
    Touch(structured / "mpfirst.odf");
    Touch(base / "Edit" / "stock" / "stockonly.odf");

    const auto dirs = BuildOdfDirectoryCandidates({structured, flat}, base);

    // Root itself is a candidate, after its structured subfolders; stock last.
    CHECK(dirs.back() == base / "Edit" / "stock");
    const auto posOdf = std::find(dirs.begin(), dirs.end(), structured / "ODF");
    const auto posRoot = std::find(dirs.begin(), dirs.end(), structured);
    CHECK(posOdf != dirs.end() && posRoot != dirs.end() && posOdf < posRoot);
    CHECK(std::find(dirs.begin(), dirs.end(), flat) != dirs.end());

    fs::path out;
    // Flat mod root resolves.
    CHECK(FindOdfFile(dirs, "sxshield", out));
    CHECK(Same(out, flat / "sxshield.odf"));

    // Structured ODF/ wins over the flat copy in the same mod.
    CHECK(FindOdfFile(dirs, "dup", out));
    CHECK(Same(out, structured / "ODF" / "dup.odf"));

    // _mp.odf preferred over .odf in the same directory.
    CHECK(FindOdfFile(dirs, "mpfirst", out));
    CHECK(Same(out, structured / "mpfirst_mp.odf"));

    // Edit/stock fallback and miss.
    CHECK(FindOdfFile(dirs, "stockonly", out));
    CHECK(Same(out, base / "Edit" / "stock" / "stockonly.odf"));
    CHECK(!FindOdfFile(dirs, "nothere", out));
    CHECK(out.empty());

    // The index answers exactly what the stat-based lookup answers.
    Touch(flat / "readme.txt");
    Touch(flat / "UPPER.ODF");
    const OdfDirectoryIndex index = BuildOdfDirectoryIndex(dirs);
    CHECK(index.directories.size() == dirs.size());
    for (const char* token : {"sxshield", "dup", "mpfirst", "stockonly", "nothere", "readme"})
    {
        fs::path statPath;
        fs::path indexPath;
        const bool statFound = FindOdfFile(dirs, token, statPath);
        CHECK(FindOdfFileInIndex(index, token, indexPath) == statFound);
        CHECK(statFound ? Same(statPath, indexPath) : indexPath.empty());
    }

    // Names fold to lower case, as Windows resolves them.
    CHECK(FindOdfFileInIndex(index, "upper", out));
    CHECK(Same(out, flat / "UPPER.ODF"));
    CHECK(FindOdfFileInIndex(index, "SXShield", out));
    CHECK(Same(out, flat / "sxshield.odf"));

    std::error_code ec;
    fs::remove_all(base, ec);
    return ::OpenShimTest::ExitCode();
}
