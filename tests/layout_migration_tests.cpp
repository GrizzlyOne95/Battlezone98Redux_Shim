// Layout migration rules for patches.json (include/openshim_layout.h).
//
// ReplaceIfOldPatchesNewer takes explicit paths, so it runs against a temp
// folder instead of the game root.

#include "openshim_layout.h"
#include "test_check.h"

#include <fstream>
#include <iterator>

namespace
{
    namespace fs = std::filesystem;

    void Write(const fs::path& path, const char* text)
    {
        fs::create_directories(path.parent_path());
        std::ofstream(path, std::ios::binary | std::ios::trunc) << text;
    }

    std::string Read(const fs::path& path)
    {
        std::ifstream in(path, std::ios::binary);
        return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }

    void SetAge(const fs::path& path, int secondsAgo)
    {
        fs::last_write_time(path, fs::file_time_type::clock::now() - std::chrono::seconds(secondsAgo));
    }

    bool LogHas(const char* needle, bool drain = true)
    {
        bool found = false;
        BZROpenShim::Layout::DrainMigrationLog([&](const char* line)
        {
            if (std::string(line).find(needle) != std::string::npos)
                found = true;
        });
        (void)drain;
        return found;
    }
}

int main()
{
    using namespace BZROpenShim;
    using namespace OpenShimTest;
    const fs::path root = fs::temp_directory_path() / L"openshim_layout_migration_tests";
    std::error_code ec;
    fs::remove_all(root, ec);

    const fs::path oldJson = root / L"scripts" / L"patches.json";
    const fs::path newJson = root / L"openshim" / L"patches.json";
    const fs::path superseded = root / L"openshim" / L"patches.json.superseded";

    // Old copy newer: it wins, the current file is kept as .superseded, and an
    // earlier .superseded is overwritten.
    Write(newJson, "current");
    Write(superseded, "earlier");
    Write(oldJson, "fresh");
    SetAge(newJson, 3600);
    SetAge(oldJson, 10);
    Layout::ReplaceIfOldPatchesNewer(oldJson, newJson);
    Check(Read(newJson) == "fresh", "newer old patches.json replaces the current one");
    Check(Read(superseded) == "current", "the replaced file is kept as .superseded over an earlier one");
    Check(!fs::exists(oldJson), "the old patches.json was moved, not copied");
    Check(LogHas("[LAYOUT]"), "the replacement is logged");

    // Old copy older: nothing changes (MigrateEntry then keeps the new one).
    fs::remove_all(root, ec);
    Write(newJson, "current");
    Write(oldJson, "stale");
    SetAge(oldJson, 3600);
    SetAge(newJson, 10);
    Layout::ReplaceIfOldPatchesNewer(oldJson, newJson);
    Check(Read(newJson) == "current", "older old patches.json leaves the current one alone");
    Check(!fs::exists(superseded), "no .superseded is written when the old copy is older");
    Check(Read(oldJson) == "stale", "the older old copy is left for MigrateEntry");
    (void)LogHas("");

    // Only one side present: nothing to do.
    fs::remove_all(root, ec);
    Write(oldJson, "only-old");
    Layout::ReplaceIfOldPatchesNewer(oldJson, newJson);
    Check(!fs::exists(newJson) && Read(oldJson) == "only-old", "a lone old copy is untouched here");

    fs::remove_all(root, ec);
    return ExitCode();
}
