// Unit tests for the chunk cache pruner (include/native_chunk_prune.h): the
// pure victim selection, plus a temp-directory run of the scanner/deleter.
#include "native_chunk_prune.h"
#include "test_check.h"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <vector>

using namespace BZROpenShim::NativeChunks;
using OpenShimTest::Check;
namespace fs = std::filesystem;

namespace
{
constexpr int64_t kDay = 24 * 3600;
constexpr uint64_t kMB = 1024 * 1024;
constexpr int64_t kNow = 100 * kDay;

PruneEntry Entry(const char *path, PruneKind kind, int64_t ageDays, uint64_t mb)
{
    PruneEntry e;
    e.path = path;
    e.kind = kind;
    e.lastUse = kNow - ageDays * kDay;
    e.bytes = mb * kMB;
    return e;
}

bool Has(const std::vector<std::string> &v, const char *path)
{
    return std::find(v.begin(), v.end(), std::string(path)) != v.end();
}

void TestObsolete()
{
    const std::vector<PruneEntry> entries = {Entry("native/v3", PruneKind::ObsoleteTree, 0, 50),
                                             Entry("native/v4/aaaa", PruneKind::ModelFolder, 1, 1)};
    PrunePolicy off; // everything disabled
    const auto v = SelectPruneVictims(entries, kNow, off);
    Check(Has(v, "native/v3"), "obsolete version tree is removed even with age and size limits disabled");
    Check(!Has(v, "native/v4/aaaa"), "current model folder survives with limits disabled");
    Check(v.size() == 1, "nothing else is selected");
}

void TestAge()
{
    const std::vector<PruneEntry> entries = {Entry("native/v4/old", PruneKind::ModelFolder, 40, 1),
                                             Entry("native/v4/new", PruneKind::ModelFolder, 5, 1),
                                             Entry("gibs/v1/old", PruneKind::ModelFolder, 31, 1),
                                             Entry("native/v4/edge", PruneKind::ModelFolder, 30, 1)};
    PrunePolicy policy;
    policy.maxAgeSeconds = 30 * kDay;
    const auto v = SelectPruneVictims(entries, kNow, policy);
    Check(Has(v, "native/v4/old") && Has(v, "gibs/v1/old"), "folders older than the limit expire in both trees");
    Check(!Has(v, "native/v4/new"), "recent folder is kept");
    Check(!Has(v, "native/v4/edge"), "a folder exactly at the limit is kept");

    std::vector<PruneEntry> future = {Entry("native/v4/future", PruneKind::ModelFolder, -5, 1)};
    Check(SelectPruneVictims(future, kNow, policy).empty(), "a last-use time in the future never expires");
}

void TestLru()
{
    const std::vector<PruneEntry> entries = {Entry("native/v4/a", PruneKind::ModelFolder, 10, 40),
                                             Entry("native/v4/b", PruneKind::ModelFolder, 3, 40),
                                             Entry("gibs/v1/c", PruneKind::ModelFolder, 20, 40),
                                             Entry("gibs/v1/d", PruneKind::ModelFolder, 1, 40)};
    PrunePolicy policy;
    policy.maxBytes = 100 * kMB; // 160 MB total
    const auto v = SelectPruneVictims(entries, kNow, policy);
    Check(v.size() == 2, "evicts just enough folders to get under the cap");
    Check(Has(v, "gibs/v1/c") && Has(v, "native/v4/a"), "least recently used folders go first, across trees");

    PrunePolicy exact;
    exact.maxBytes = 160 * kMB;
    Check(SelectPruneVictims(entries, kNow, exact).empty(), "a total equal to the cap evicts nothing");
}

void TestProtectedAndUnknown()
{
    const std::vector<PruneEntry> entries = {Entry("fallback/v1", PruneKind::Protected, 90, 1),
                                             Entry("casings/v1", PruneKind::Protected, 90, 1),
                                             Entry("openshim_casing.material", PruneKind::Protected, 90, 0),
                                             Entry("notes.txt", PruneKind::Unknown, 90, 1),
                                             Entry("native/v4/m", PruneKind::ModelFolder, 1, 10)};
    PrunePolicy policy;
    policy.maxAgeSeconds = 30 * kDay;
    policy.maxBytes = 1; // impossible to satisfy: only the model folder is a candidate
    const auto v = SelectPruneVictims(entries, kNow, policy);
    Check(v.size() == 1 && Has(v, "native/v4/m"), "protected and unknown entries are never evicted, even over the cap");
}

void TestUnprotectedBytesCountTowardCap()
{
    const std::vector<PruneEntry> entries = {Entry("fallback/v1", PruneKind::Protected, 0, 30),
                                             Entry("native/v4/a", PruneKind::ModelFolder, 2, 30),
                                             Entry("native/v4/b", PruneKind::ModelFolder, 1, 30)};
    PrunePolicy policy;
    policy.maxBytes = 70 * kMB;
    const auto v = SelectPruneVictims(entries, kNow, policy);
    Check(v.size() == 1 && Has(v, "native/v4/a"), "protected bytes count toward the total");
}

void TestZeroDisables()
{
    const std::vector<PruneEntry> entries = {Entry("native/v4/a", PruneKind::ModelFolder, 5000, 5000)};
    PrunePolicy zero;
    Check(SelectPruneVictims(entries, kNow, zero).empty(), "zero age and zero size mean no limit");
    PrunePolicy ageOnly;
    ageOnly.maxAgeSeconds = kDay;
    Check(SelectPruneVictims(entries, kNow, ageOnly).size() == 1, "age limit alone still applies");
}

void Write(const fs::path &file, const std::string &text)
{
    fs::create_directories(file.parent_path());
    std::ofstream(file, std::ios::binary) << text;
}

void Age(const fs::path &folder, int days)
{
    std::error_code ec;
    fs::last_write_time(folder, fs::file_time_type::clock::now() - std::chrono::hours(24 * days), ec);
}

void TestFilesystem()
{
    std::error_code ec;
    const fs::path base = fs::temp_directory_path() / "openshim_chunk_prune_test";
    fs::remove_all(base, ec);
    const fs::path root = base / "chunks";
    const std::string native = std::string(OPENSHIM_CHUNK_CACHE_NATIVE_DIR);
    const std::string gibs = std::string(OPENSHIM_CHUNK_CACHE_GIBS_DIR);
    const std::string fallback = std::string(OPENSHIM_CHUNK_CACHE_FALLBACK_DIR);
    const std::string casings = std::string(OPENSHIM_CHUNK_CACHE_CASINGS_DIR);
    Write(root / "native/v0/abc/pieces.cache", "stale");
    Write(root / "gibs/v0/abc/gibs.cache", "stale");
    Write(root / "fallback/v0/stock_chunk1.mesh", "stale");
    Write(root / "casings/v0/openshim_casing.mesh", "stale");
    Write(root / native / "0123abcd/pieces.cache", "fresh");
    Write(root / native / "deadbeef/pieces.cache", "old");
    Write(root / native / "not-a-model/pieces.cache", "unknown");
    Write(root / gibs / "feedface/gibs.cache", "fresh");
    Write(root / fallback / "stock_chunk1.mesh", "keep");
    Write(root / casings / "openshim_casing.mesh", "keep");
    Write(root / "openshim_gib_flesh.material", "keep");
    Write(root / "readme.txt", "keep");
    Age(root / native / "deadbeef", 90);
    Age(root / native / "not-a-model", 90);

    PrunePolicy policy;
    policy.maxAgeSeconds = 30 * kDay;
    policy.maxBytes = 256 * kMB;
    const auto result = PruneChunkCache(root, policy);
    Check(result.scanned, "existing root is scanned");
    Check(!fs::exists(root / "native/v0") && !fs::exists(root / "gibs/v0") && !fs::exists(root / "fallback/v0") &&
              !fs::exists(root / "casings/v0"),
          "all obsolete version trees are deleted");
    Check(result.obsoleteTrees.size() == 4, "each obsolete tree is reported");
    Check(!fs::exists(root / native / "deadbeef"), "expired model folder is deleted");
    Check(fs::exists(root / native / "0123abcd") && fs::exists(root / gibs / "feedface"), "fresh folders survive");
    Check(fs::exists(root / native / "not-a-model"), "a folder that is not a fingerprint name is left alone");
    Check(fs::exists(root / fallback / "stock_chunk1.mesh") && fs::exists(root / casings / "openshim_casing.mesh"),
          "current fallback and casing shapes survive");
    Check(fs::exists(root / "openshim_gib_flesh.material") && fs::exists(root / "readme.txt"),
          "loose files survive");
    Check(result.keptModels == 2, "kept model count excludes unknown and removed folders");

    // The expired folder, once touched, is a fresh use.
    Age(root / native / "0123abcd", 90);
    TouchCacheFolder(root / native / "0123abcd");
    TouchCacheFolder(root / native / "0123abcd"); // second call is a no-op
    const auto again = PruneChunkCache(root, policy);
    Check(fs::exists(root / native / "0123abcd") && again.removed == 0, "touching a folder renews its last use");

    const auto missing = PruneChunkCache(base / "does-not-exist", policy);
    Check(!missing.scanned && missing.removed == 0, "a missing root is a no-op");
    fs::remove_all(base, ec);
}
} // namespace

int main()
{
    TestObsolete();
    TestAge();
    TestLru();
    TestProtectedAndUnknown();
    TestUnprotectedBytesCountTowardCap();
    TestZeroDisables();
    TestFilesystem();
    return OpenShimTest::ExitCode();
}
