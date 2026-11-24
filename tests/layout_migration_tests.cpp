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

    // Root ini merge.
    const fs::path rootIni = root / L"openshim.ini";
    const fs::path subIni = root / L"openshim" / L"openshim.ini";
    const fs::path mergedIni = root / L"openshim" / L"openshim.ini.root-merged";

    // Both exist: missing keys copied (case-insensitive names), existing values,
    // comments and CRLF endings untouched, new section appended.
    fs::remove_all(root, ec);
    Write(subIni, "; keep me\r\n[Video]\r\nFoo = 1\r\n\r\n[Audio]\r\nVol=5\r\n");
    Write(rootIni, "[video]\n foo = 99\nBar=2\n[Extra]\nZed=3\n[Audio]\nVol=9\nMute=1\n");
    Check(Layout::MergeRootIni(rootIni, subIni), "merge succeeds when both exist");
    Check(Read(subIni) ==
          "; keep me\r\n[Video]\r\nFoo = 1\r\nBar=2\r\n\r\n[Audio]\r\nVol=5\r\nMute=1\r\n\r\n[Extra]\r\nZed=3\r\n",
          "missing keys are copied into place, existing values and text are untouched");
    Check(!fs::exists(rootIni) && Read(mergedIni).find("foo = 99") != std::string::npos,
          "the root file is moved to .root-merged");
    Check(LogHas("merged [Extra] Zed"), "each copied key is logged");

    // Second run: nothing left in the root, nothing changes.
    const std::string after = Read(subIni);
    Check(!Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == after, "the merge runs once");

    // Name collision: .root-merged already exists, a numbered name is used.
    Write(rootIni, "[Video]\nBaz=4\n");
    Check(Layout::MergeRootIni(rootIni, subIni), "merge succeeds with an existing .root-merged");
    Check(Read(mergedIni).find("foo = 99") != std::string::npos, "the earlier .root-merged is not clobbered");
    Check(Read(fs::path(mergedIni).concat(L".1")) == "[Video]\nBaz=4\n", "the collision gets a numbered name");
    Check(Read(subIni).find("Baz=4") != std::string::npos, "the key is merged");
    (void)LogHas("");

    // Sub-only: nothing to do.
    fs::remove_all(root, ec);
    Write(subIni, "[A]\nk=1\n");
    Check(!Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == "[A]\nk=1\n", "sub-only is untouched");

    // Root-only: not merged here; MigrateEntry keeps the move behaviour.
    fs::remove_all(root, ec);
    Write(rootIni, "[A]\nk=1\n");
    Check(!Layout::MergeRootIni(rootIni, subIni) && fs::exists(rootIni) && !fs::exists(subIni),
          "root-only is left for MigrateEntry");
    Check(Layout::MigrateEntry(rootIni, subIni) && Read(subIni) == "[A]\nk=1\n" && !fs::exists(rootIni),
          "root-only still moves");
    (void)LogHas("");

    // Real rollback: the root file is held open without delete sharing, so the
    // move fails with the root still present; the destination returns to its
    // original bytes and the root is untouched.
    fs::remove_all(root, ec);
    Write(subIni, "[A]\r\nk=1\r\n");
    Write(rootIni, "[A]\r\nnew=2\r\n");
    {
        HANDLE hold = CreateFileW(rootIni.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        Check(hold != INVALID_HANDLE_VALUE, "fixture: root held open");
        Check(!Layout::MergeRootIni(rootIni, subIni), "a failed move reports failure");
        if (hold != INVALID_HANDLE_VALUE)
            CloseHandle(hold);
    }
    Check(Read(subIni) == "[A]\r\nk=1\r\n", "a failed move rolls the destination back");
    Check(fs::exists(rootIni) && !fs::exists(mergedIni), "a failed move leaves the root file alone");
    (void)LogHas("");

    // UTF-8 BOM in root and destination: correct section, destination BOM kept.
    fs::remove_all(root, ec);
    Write(subIni, "\xEF\xBB\xBF[Video]\r\nFoo=1\r\n");
    Write(rootIni, "\xEF\xBB\xBF[video]\r\nFoo=9\r\nBar=2\r\n");
    Check(Layout::MergeRootIni(rootIni, subIni), "BOM merge succeeds");
    Check(Read(subIni) == "\xEF\xBB\xBF[Video]\r\nFoo=1\r\nBar=2\r\n", "BOM kept, key added to the right section");

    // Root BOM only, destination without one: no BOM appears, first section matches.
    fs::remove_all(root, ec);
    Write(subIni, "[Video]\nFoo=1\n");
    Write(rootIni, "\xEF\xBB\xBF[Video]\nBar=2\n");
    Check(Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == "[Video]\nFoo=1\nBar=2\n",
          "a root BOM does not hide its first section header");

    // UTF-16 destination (or root) is left untouched.
    fs::remove_all(root, ec);
    {
        std::ofstream(subIni, std::ios::binary | std::ios::trunc).write("\xFF\xFE[\0A\0]\0\r\0\n\0", 12);
    }
    const std::string utf16 = Read(subIni);
    Write(rootIni, "[A]\nk=1\n");
    Check(!Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == utf16 && fs::exists(rootIni),
          "a UTF-16 destination is not merged");
    (void)LogHas("");

    // LF-only destination without a trailing newline keeps LF and stays without one.
    fs::remove_all(root, ec);
    Write(subIni, "[A]\nk=1");
    Write(rootIni, "[A]\nm=2\n");
    Check(Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == "[A]\nk=1\nm=2",
          "LF endings and a missing final newline are preserved");

    // Root comments are not keys; keys before any section are skipped.
    fs::remove_all(root, ec);
    Write(subIni, "[A]\nk=1\n");
    Write(rootIni, "Orphan=1\n[A]\n; Foo=1\n# Baz=2\nreal=3\n");
    Check(Layout::MergeRootIni(rootIni, subIni) && Read(subIni) == "[A]\nk=1\nreal=3\n",
          "commented keys and section-less keys are not copied");

    // OpenShimIniPath()-style flow: merge, then MigrateEntry finds nothing left.
    fs::remove_all(root, ec);
    Write(subIni, "[A]\nk=1\n");
    Write(rootIni, "[A]\nm=2\n");
    (void)Layout::MergeRootIni(rootIni, subIni);
    Check(Layout::MigrateEntry(rootIni, subIni) && Read(subIni) == "[A]\nk=1\nm=2\n" && !fs::exists(rootIni),
          "after the merge MigrateEntry is a no-op and the new path is the config");
    (void)LogHas("");

    fs::remove_all(root, ec);
    return ExitCode();
}
