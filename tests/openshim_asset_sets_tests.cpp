#include "openshim_asset_sets.h"

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim;
namespace fs = std::filesystem;

namespace
{
    const std::string kHexA(64, 'a');

    std::string Replace(std::string text, const std::string& from, const std::string& to)
    {
        const size_t at = text.find(from);
        Check(at != std::string::npos, "test fixture must contain the text being replaced");
        if (at != std::string::npos)
            text.replace(at, from.size(), to);
        return text;
    }

    void Put(const fs::path& path, const std::string& content)
    {
        fs::create_directories(path.parent_path());
        std::ofstream output(path, std::ios::binary | std::ios::trunc);
        output << content;
    }

    std::string Get(const fs::path& path)
    {
        std::ifstream input(path, std::ios::binary);
        return std::string((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    }

    struct TempDir
    {
        fs::path path;
        TempDir()
        {
            path = fs::temp_directory_path() /
                ("openshim_asset_sets_tests_" +
                 std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
            fs::create_directories(path);
        }
        ~TempDir()
        {
            std::error_code ec;
            fs::remove_all(path, ec);
        }
    };

    // Writes the files under itemDir/<source> and returns the matching set.
    OpenShimAssetSet MakeSet(const std::string& name,
                             const std::string& source,
                             const std::string& destination,
                             const fs::path& itemDir,
                             const std::vector<std::pair<std::string, std::string>>& files)
    {
        OpenShimAssetSet set;
        set.name = name;
        set.source = source;
        set.destination = destination;
        for (const auto& file : files)
        {
            Put(itemDir / fs::path(source) / file.first, file.second);
            OpenShimAssetFile entry;
            entry.path = file.first;
            entry.sha256 = Sha256Hex(file.second.data(), file.second.size());
            entry.size = file.second.size();
            set.entries.push_back(entry);
        }
        set.files = static_cast<uint32_t>(set.entries.size());
        set.sha256 = ComputeOpenShimAssetSetHash(set.entries);
        return set;
    }

    bool VersionIsThree(const fs::path& dir, std::string& problem)
    {
        if (Get(dir / "resources.version") != "3")
        {
            problem = "resources.version mismatch";
            return false;
        }
        return true;
    }

    const char* const kSample = R"LUA(
return {
    assetSets = {
        renderer = { source = "openshim\\renderer\\enhanced", destination = "openshim\\renderer\\enhanced", sha256 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", files = 2 },
        customWidgets = { source = "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets", destination = "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets", sha256 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", files = 1 },
        futureSet = { source = "x", destination = "y", sha256 = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc", files = 9 },
    },
    assetFiles = {
        { set = "renderer", path = "resources.version", sha256 = "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", size = 1 },
        { set = "renderer", path = "sub\\Shader-1.glsl", sha256 = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee", size = 20 },
        { set = "customWidgets", path = "osh_x.png", sha256 = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", size = 3 },
        { set = "futureSet", path = "..\\evil", sha256 = "not even hex", size = 1 },
    },
}
)LUA";

    void TestSha256AndSetHash()
    {
        Check(Sha256Hex("abc", 3) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
              "SHA-256 of abc");
        Check(Sha256Hex("", 0) == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
              "SHA-256 of the empty string");
        const std::string longText(1000, 'x');
        Check(Sha256Hex(longText.data(), longText.size()).size() == 64, "multi-block SHA-256 completes");

        std::vector<OpenShimAssetFile> entries = {
            { "B.txt", kHexA, 5 }, { "a.txt", std::string(64, 'B'), 7 }, { "sub\\c.txt", kHexA, 0 } };
        const std::string hash = ComputeOpenShimAssetSetHash(entries);
        Check(hash.size() == 64, "set hash is 64 hex characters");
        Check(hash == ComputeOpenShimAssetSetHash(entries), "set hash is deterministic");
        std::vector<OpenShimAssetFile> reordered = { entries[2], entries[0], entries[1] };
        reordered[0].path = "SUB\\C.TXT";
        Check(hash == ComputeOpenShimAssetSetHash(reordered),
              "set hash ignores entry order and path/hash case");
        std::vector<OpenShimAssetFile> resized = entries;
        resized[0].size = 6;
        Check(hash != ComputeOpenShimAssetSetHash(resized), "set hash depends on sizes");

        // Pin the textual definition: sorted lowercased lines joined as-is.
        const std::string expectedText = "a.txt|" + std::string(64, 'b') + "|7\n" +
                                         "b.txt|" + kHexA + "|5\n" +
                                         "sub\\c.txt|" + kHexA + "|0\n";
        Check(hash == Sha256Hex(expectedText.data(), expectedText.size()),
              "set hash matches the documented line format");
    }

    void TestParse()
    {
        OpenShimAssetSets sets;
        std::string error;
        Check(ParseOpenShimAssetSets(kSample, sets, error), std::string("sample sections parse: ") + error);
        Check(sets.sets.size() == 2, "two recognised sets");
        Check(sets.ignored.size() == 1 && sets.ignored[0] == "futureSet", "unknown set is reported as ignored");
        if (sets.sets.size() == 2)
        {
            Check(sets.sets[0].name == "renderer" && sets.sets[0].files == 2 &&
                  sets.sets[0].entries.size() == 2, "renderer set shape");
            Check(sets.sets[0].source == "openshim\\renderer\\enhanced", "backslashes are unescaped once");
            Check(sets.sets[0].sha256 == std::string(64, 'a'), "set hash is lowercased");
            Check(sets.sets[0].entries[1].path == "sub\\Shader-1.glsl" && sets.sets[0].entries[1].size == 20,
                  "file entry fields");
            Check(sets.sets[1].name == "customWidgets" && sets.sets[1].entries.size() == 1,
                  "customWidgets set shape");
        }

        Check(ParseOpenShimAssetSets("return { formatVersion = 3 }", sets, error) && sets.sets.empty(),
              "absent sections are success with no sets");

        const struct { const char* from; const char* to; const char* what; } rejects[] = {
            { "sub\\\\Shader-1.glsl", "sub\\\\..\\\\Shader.glsl", "dotdot component" },
            { "sub\\\\Shader-1.glsl", "sub\\\\Shader 1.glsl", "space in path" },
            { "sub\\\\Shader-1.glsl", "C:\\\\Shader.glsl", "drive colon" },
            { "sub\\\\Shader-1.glsl", "\\\\Shader.glsl", "leading separator" },
            { "sub\\\\Shader-1.glsl", "sub\\Shader.glsl", "single-backslash escape" },
            { "destination = \"openshim\\\\renderer\\\\enhanced\"", "destination = \"..\\\\enhanced\"", "dotdot destination" },
            { "files = 2", "files = 3", "count mismatch" },
            { "path = \"resources.version\", sha256 = \"dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\"",
              "path = \"resources.version\", sha256 = \"dddd\"", "short hash" },
            { "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
              "gAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "non-hex set hash" },
            { "{ set = \"customWidgets\", path = \"osh_x.png\"", "{ set = \"renderer\", path = \"resources.version\"", "duplicate path" },
            { "    assetFiles = {", "    assetFiles = {\n        junk line,", "junk entry" },
        };
        for (const auto& reject : rejects)
        {
            OpenShimAssetSets rejected;
            Check(!ParseOpenShimAssetSets(Replace(kSample, reject.from, reject.to), rejected, error) &&
                  rejected.sets.empty(), std::string("parse must reject: ") + reject.what);
        }

        std::string unclosed = kSample;
        unclosed.erase(unclosed.find("    assetFiles"));
        Check(!ParseOpenShimAssetSets(unclosed + "    assetFiles = {\n", sets, error), "unclosed section is rejected");
    }

    void TestRendererSync()
    {
        TempDir temp;
        const fs::path item = temp.path / "item";
        const fs::path game = temp.path / "game";
        const OpenShimAssetSet set = MakeSet("renderer", "openshim\\renderer\\enhanced",
            "openshim\\renderer\\enhanced", item,
            { { "resources.version", "3" }, { "a.glsl", "void main(){}" }, { "sub\\b.dds", "dds" } });
        const fs::path live = game / "openshim" / "renderer" / "enhanced";

        // No live directory yet.
        auto outcome = SyncOpenShimAssetSet(item, game, set, VersionIsThree);
        Check(outcome.result == OpenShimAssetSyncResult::Installed && outcome.filesInstalled == 3,
              std::string("renderer installs into an absent destination: ") + outcome.detail);
        Check(Get(live / "sub" / "b.dds") == "dds" && Get(live / "openshim_set.sha256") == set.sha256 + "\n",
              "files and marker are in place");
        Check(!fs::exists(live.parent_path() / "enhanced.pending") && !fs::exists(live.parent_path() / "enhanced.old"),
              "no pending or old directory is left behind");

        // Marker fast path: even a broken source is not looked at.
        Put(item / "openshim" / "renderer" / "enhanced" / "a.glsl", "tampered");
        outcome = SyncOpenShimAssetSet(item, game, set, VersionIsThree);
        Check(outcome.result == OpenShimAssetSyncResult::Current, "matching marker skips the set");
        Check(Get(live / "a.glsl") == "void main(){}", "skipped set leaves the live files alone");

        // Source corrupted and marker stale: refuse, destination untouched.
        fs::remove(live / "openshim_set.sha256");
        Put(live / "stale.txt", "old");
        outcome = SyncOpenShimAssetSet(item, game, set, VersionIsThree);
        Check(outcome.result == OpenShimAssetSyncResult::Refused, "source hash mismatch is refused");
        Check(fs::exists(live / "stale.txt") && Get(live / "a.glsl") == "void main(){}",
              "refused sync leaves the destination untouched");
        Check(!fs::exists(live.parent_path() / "enhanced.pending"), "refusal removes the pending directory");

        // Repaired source: the swap replaces the stale directory wholesale.
        Put(item / "openshim" / "renderer" / "enhanced" / "a.glsl", "void main(){}");
        outcome = SyncOpenShimAssetSet(item, game, set, VersionIsThree);
        Check(outcome.result == OpenShimAssetSyncResult::Installed, std::string("repaired source installs: ") + outcome.detail);
        Check(!fs::exists(live / "stale.txt"), "files outside the set are dropped by the directory swap");
        Check(!fs::exists(live.parent_path() / "enhanced.old"), "old directory is removed after the swap");

        // Validator failure on the source refuses and leaves the live copy.
        const OpenShimAssetSet bad = MakeSet("renderer", "openshim\\renderer\\enhanced",
            "openshim\\renderer\\enhanced", item,
            { { "resources.version", "2" }, { "a.glsl", "x" } });
        outcome = SyncOpenShimAssetSet(item, game, bad,
            [](const fs::path& dir, std::string& problem) { return VersionIsThree(dir, problem); });
        Check(outcome.result == OpenShimAssetSyncResult::Refused, "validator failure refuses the set");
        Check(Get(live / "resources.version") == "3" && Get(live / "a.glsl") == "void main(){}",
              "validator refusal leaves the live copy");

        // Declared hash that does not describe the file list.
        OpenShimAssetSet lying = set;
        lying.sha256 = kHexA;
        fs::remove(live / "openshim_set.sha256");
        outcome = SyncOpenShimAssetSet(item, game, lying, VersionIsThree);
        Check(outcome.result == OpenShimAssetSyncResult::Refused, "set hash that differs from its file list is refused");
    }

    void TestWidgetsSync()
    {
        TempDir temp;
        const fs::path item = temp.path / "item";
        const fs::path game = temp.path / "game";
        const OpenShimAssetSet set = MakeSet("customWidgets", "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets",
            "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets", item,
            { { "osh_a.png", "new-a" }, { "uiline.png", "new-line" } });
        const fs::path live = game / "BZ_ASSETS_CORE" / "common" / "ui" / "CustomWidgets";

        // Corrupt source with an empty destination: nothing is created.
        Put(item / "BZ_ASSETS_CORE" / "common" / "ui" / "CustomWidgets" / "osh_a.png", "tampered");
        auto outcome = SyncOpenShimAssetSet(item, game, set, nullptr);
        Check(outcome.result == OpenShimAssetSyncResult::Refused, "corrupt widget source is refused");
        Check(!fs::exists(live), "refusal does not create the destination");
        Put(item / "BZ_ASSETS_CORE" / "common" / "ui" / "CustomWidgets" / "osh_a.png", "new-a");

        Put(live / "foreign.png", "players own");
        Put(live / "uiline.png", "stale");
        outcome = SyncOpenShimAssetSet(item, game, set, nullptr);
        Check(outcome.result == OpenShimAssetSyncResult::Installed && outcome.filesInstalled == 2,
              std::string("widgets install both files: ") + outcome.detail);
        Check(Get(live / "uiline.png") == "new-line" && Get(live / "osh_a.png") == "new-a", "widget files replaced");
        Check(Get(live / "foreign.png") == "players own", "foreign files are kept");
        Check(Get(live / "openshim_widgets.sha256") == set.sha256 + "\n", "widgets marker written");
        Check(!fs::exists(live / "uiline.png.tmp") && !fs::exists(live / "osh_a.png.tmp"), "no temporary files remain");

        outcome = SyncOpenShimAssetSet(item, game, set, nullptr);
        Check(outcome.result == OpenShimAssetSyncResult::Current, "second run is a marker skip");

        // Marker lost but files already right: marker is rewritten, nothing copied.
        fs::remove(live / "openshim_widgets.sha256");
        outcome = SyncOpenShimAssetSet(item, game, set, nullptr);
        Check(outcome.result == OpenShimAssetSyncResult::Installed && outcome.filesInstalled == 0,
              "matching files are not rewritten");
    }
}

int main()
{
    TestSha256AndSetHash();
    TestParse();
    TestRendererSync();
    TestWidgetsSync();

    if (OpenShimTest::FailureCount() == 0)
        std::puts("openshim_asset_sets_tests: PASS");
    return OpenShimTest::ExitCode();
}
