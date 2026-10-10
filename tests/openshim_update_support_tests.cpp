#include "openshim_update_support.h"
#include "test_check.h"
#include <chrono>
#include <fstream>
#include <iterator>

using namespace BZROpenShim;
using OpenShimTest::Check;
namespace fs = std::filesystem;

namespace
{
    void Put(const fs::path& path, const std::string& contents)
    {
        fs::create_directories(path.parent_path());
        std::ofstream(path, std::ios::binary) << contents;
    }
    std::string Read(const fs::path& path)
    {
        std::ifstream input(path, std::ios::binary);
        return { std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
    }
}

int main()
{
    const auto root = fs::temp_directory_path() / ("openshim_support_" +
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto workshop = root / "workshop";
    const auto game = root / "game";
    fs::create_directories(game);
    const auto config = game / "openshim.ini";
    const auto assets = game / "openshim" / "OpenShimAssets.ini";
    OpenShimUpdateManifest manifest;
    // The production verifier uses SHA-256; this fixture verifies exact bytes.
    manifest.playerConfig.sha256 = "default settings";
    manifest.assetManifest.sha256 = "compatible manifest";
    const auto verify = [](const fs::path& path, const OpenShimUpdatePayloadManifest& payload,
                           std::string& error)
    {
        if (Read(path) == payload.sha256) return true;
        error = "payload bytes differ";
        return false;
    };
    Put(workshop / "openshim.ini.payload", manifest.playerConfig.sha256);
    Put(workshop / "OpenShimAssets.ini.payload", manifest.assetManifest.sha256);
    Put(config, "player choices");
    bool changed = false;
    std::string error;
    Check(RepairOpenShimUpdateSupport(workshop, game, manifest, verify, changed, error) && changed,
          "current native suite must still repair a missing asset manifest");
    Check(Read(config) == "player choices", "custom settings are preserved byte for byte");
    Check(Read(assets) == manifest.assetManifest.sha256, "manifest installed below openshim");
    Check(RepairOpenShimUpdateSupport(workshop, game, manifest, verify, changed, error) && !changed,
          "an already repaired install is unchanged");
    Put(assets, "stale manifest");
    Check(RepairOpenShimUpdateSupport(workshop, game, manifest, verify, changed, error) && changed,
          "stale manifest is repaired at the same native version");
    fs::remove(config);
    Check(RepairOpenShimUpdateSupport(workshop, game, manifest, verify, changed, error) && changed,
          "missing player config is installed");
    Check(Read(config) == manifest.playerConfig.sha256, "installed defaults are verified");

    fs::remove(config);
    Put(workshop / "OpenShimAssets.ini.payload", "corrupt download");
    Check(!RepairOpenShimUpdateSupport(workshop, game, manifest, verify, changed, error) && !changed,
          "corrupt asset source rejects repair before any settings write");
    Check(!fs::exists(config), "failed validation does not create settings");
    Put(config, "player choices");
    Put(workshop / "OpenShimAssets.ini.payload", manifest.assetManifest.sha256);
    Put(assets, "old installed manifest");
    const auto rejectStaged = [&](const fs::path& path, const OpenShimUpdatePayloadManifest& payload,
                                  std::string& reason)
    {
        if (path.extension() == ".pending") { reason = "staged hash mismatch"; return false; }
        return verify(path, payload, reason);
    };
    Check(!RepairOpenShimUpdateSupport(workshop, game, manifest, rejectStaged, changed, error),
          "a corrupted staged copy is never promoted");
    Check(Read(assets) == "old installed manifest" && Read(config) == "player choices",
          "failed promotion preserves the installed files");
    Check(!fs::exists(fs::path(assets.wstring() + L".pending")), "failed staged copy is removed");

    fs::remove_all(root);
    return OpenShimTest::ExitCode();
}
