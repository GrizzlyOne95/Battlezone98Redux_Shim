// BZLoader catalog/metadata validation tests.
//
// These deliberately do not use assert(): CI configures and runs this suite as
// Release, NDEBUG is defined, and every assert() would compile out to nothing
// while the test still reported success.

#include "bzloader_catalog.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* expression, int line)
    {
        if (condition) return;
        std::printf("FAIL line %d: %s\n", line, expression);
        ++g_Failures;
    }

#define CHECK(c) Check((c), #c, __LINE__)

    // A fixed digest the fake host reports, so an exact-image gate can be
    // exercised without touching the filesystem.
    const char* const kHostSha =
        "1111111111111111111111111111111111111111111111111111111111111111";

    const char* BZLOADER_CALL FakeSha256() { return kHostSha; }
    const char* BZLOADER_CALL UnavailableSha256() { return nullptr; }

    BZHostApi Host()
    {
        BZHostApi host = {};
        host.structSize = sizeof(BZHostApi);
        host.abiVersion = BZLOADER_ABI_VERSION;
        host.loaderVersion = BZLOADER_VERSION;
        host.gameId = BZ_GAME_BATTLEZONE_98_REDUX;
        host.loaderDirectory = L"C:\\Game";
        host.executablePath = L"C:\\Game\\Battlezone98Redux.exe";
        host.executableBuildHint = "pe-12345678-01000000";
        host.log = nullptr;
        host.executableTimeDateStamp = 0x12345678u;
        host.executableSizeOfImage = 0x01000000u;
        host.getExecutableSha256 = FakeSha256;
        return host;
    }

    BZPluginInfo Plugin()
    {
        BZPluginInfo plugin = {};
        plugin.structSize = sizeof(BZPluginInfo);
        plugin.requiredLoaderAbi = BZLOADER_ABI_VERSION;
        plugin.pluginId = "org.example.plugin";
        plugin.pluginName = "Example";
        plugin.pluginVersion = "1.2.3";
        plugin.supportedGameMask = BZ_GAME_MASK_BATTLEZONE_98_REDUX;
        return plugin;
    }

    BZLoader::MetadataStatus Validate(const BZHostApi& host, const BZPluginInfo& plugin)
    {
        std::string reason;
        const auto status = BZLoader::ValidateMetadata(host, plugin, reason);
        // Every rejection has to explain itself; a silent skip is unreadable
        // in a user's log.
        Check(status == BZLoader::MetadataStatus::Ok ? reason.empty() : !reason.empty(),
              "rejection carries a reason", __LINE__);
        return status;
    }
}

int main()
{
    using Status = BZLoader::MetadataStatus;

    auto host = Host();
    auto plugin = Plugin();
    CHECK(Validate(host, plugin) == Status::Ok);

    // ---- ABI and identity -------------------------------------------------
    plugin = Plugin();
    plugin.requiredLoaderAbi = BZLOADER_ABI_VERSION + 1;
    CHECK(Validate(host, plugin) == Status::AbiMismatch);

    plugin = Plugin();
    plugin.pluginId = "bad plugin id";
    CHECK(Validate(host, plugin) == Status::InvalidPluginId);

    plugin = Plugin();
    plugin.pluginName = "";
    CHECK(Validate(host, plugin) == Status::MissingIdentity);

    // ---- game gating is fail-closed ---------------------------------------
    plugin = Plugin();
    plugin.supportedGameMask = BZ_GAME_MASK_BATTLEZONE_15;
    CHECK(Validate(host, plugin) == Status::UnsupportedGame);

    // The regression the review asked for: an unrecognised executable must not
    // become a wildcard that lets a game-specific plugin in.
    auto unknownHost = Host();
    unknownHost.gameId = BZ_GAME_UNKNOWN;
    unknownHost.executablePath = L"C:\\Elsewhere\\SomethingElse.exe";
    plugin = Plugin();
    plugin.supportedGameMask = BZ_GAME_MASK_BATTLEZONE_98_REDUX;
    CHECK(Validate(unknownHost, plugin) == Status::UnsupportedGame);

    plugin = Plugin();
    plugin.supportedGameMask = BZ_GAME_MASK_BATTLEZONE_15;
    CHECK(Validate(unknownHost, plugin) == Status::UnsupportedGame);

    // Enumerating both known games is still an enumeration, not a wildcard.
    plugin = Plugin();
    plugin.supportedGameMask =
        BZ_GAME_MASK_BATTLEZONE_15 | BZ_GAME_MASK_BATTLEZONE_98_REDUX;
    CHECK(Validate(unknownHost, plugin) == Status::UnsupportedGame);
    CHECK(Validate(host, plugin) == Status::Ok);

    // Only an explicit "runs anywhere" survives an unrecognised host.
    plugin = Plugin();
    plugin.supportedGameMask = BZ_GAME_MASK_ANY;
    CHECK(Validate(unknownHost, plugin) == Status::Ok);

    // ---- build hint (coarse) ----------------------------------------------
    plugin = Plugin();
    plugin.supportedBuildHint = "pe-AAAAAAAA-BBBBBBBB";
    CHECK(Validate(host, plugin) == Status::UnsupportedBuild);

    plugin = Plugin();
    plugin.supportedBuildHint = "pe-12345678-01000000";
    CHECK(Validate(host, plugin) == Status::Ok);

    // ---- exact image SHA-256 (authoritative) ------------------------------
    plugin = Plugin();
    plugin.supportedExecutableSha256 = kHostSha;
    CHECK(Validate(host, plugin) == Status::Ok);

    plugin = Plugin();
    plugin.supportedExecutableSha256 =
        "2222222222222222222222222222222222222222222222222222222222222222";
    CHECK(Validate(host, plugin) == Status::UnsupportedBuild);

    // Fails closed when the digest cannot be produced at all.
    auto noShaHost = Host();
    noShaHost.getExecutableSha256 = UnavailableSha256;
    plugin = Plugin();
    plugin.supportedExecutableSha256 = kHostSha;
    CHECK(Validate(noShaHost, plugin) == Status::ExecutableIdentityUnavailable);

    // ...and when the host is too old to offer the field at all.
    auto v1Host = Host();
    v1Host.structSize = BZLOADER_HOST_API_V1_SIZE;
    plugin = Plugin();
    plugin.supportedExecutableSha256 = kHostSha;
    CHECK(Validate(v1Host, plugin) == Status::ExecutableIdentityUnavailable);
    CHECK(BZLoader::HostExecutableSha256Fn(v1Host) == nullptr);
    CHECK(BZLoader::HostExecutableSha256Fn(host) == FakeSha256);

    // ---- append-only structSize semantics ---------------------------------
    // A plugin that only fills the mandatory v1 prefix is valid, and none of
    // its absent tail fields may be read out of the host's buffer.
    BZPluginInfo v1Plugin = Plugin();
    v1Plugin.supportedBuildHint = "pe-AAAAAAAA-BBBBBBBB";  // would reject, if read
    v1Plugin.supportedExecutableSha256 = "deadbeef";       // would reject, if read
    v1Plugin.loadPriority = 4321;
    v1Plugin.flags = 0xFFu;
    v1Plugin.dependencies = "org.example.other";
    v1Plugin.conflicts = "org.example.rival";
    v1Plugin.structSize = BZLOADER_PLUGIN_INFO_V1_SIZE;
    CHECK(Validate(host, v1Plugin) == Status::Ok);
    CHECK(BZLoader::PluginBuildHint(v1Plugin) == nullptr);
    CHECK(BZLoader::PluginExecutableSha256(v1Plugin) == nullptr);
    CHECK(BZLoader::PluginDependencies(v1Plugin) == nullptr);
    CHECK(BZLoader::PluginConflicts(v1Plugin) == nullptr);
    CHECK(BZLoader::PluginLoadPriority(v1Plugin) == 0);
    CHECK(BZLoader::PluginFlags(v1Plugin) == 0u);

    // A plugin sized to include loadPriority but nothing beyond it gets that
    // field and only that field.
    BZPluginInfo midPlugin = Plugin();
    midPlugin.loadPriority = -17;
    midPlugin.flags = 0xFFu;
    midPlugin.structSize = BZLOADER_FIELD_END(BZPluginInfo, loadPriority);
    CHECK(Validate(host, midPlugin) == Status::Ok);
    CHECK(BZLoader::PluginLoadPriority(midPlugin) == -17);
    CHECK(BZLoader::PluginFlags(midPlugin) == 0u);

    // Full-size plugins still read every field.
    BZPluginInfo fullPlugin = Plugin();
    fullPlugin.loadPriority = 99;
    fullPlugin.flags = 7u;
    fullPlugin.dependencies = "org.example.other";
    CHECK(BZLoader::PluginLoadPriority(fullPlugin) == 99);
    CHECK(BZLoader::PluginFlags(fullPlugin) == 7u);
    CHECK(std::strcmp(BZLoader::PluginDependencies(fullPlugin), "org.example.other") == 0);

    // Under the prefix on either side is a hard reject.
    plugin = Plugin();
    plugin.structSize = BZLOADER_PLUGIN_INFO_V1_SIZE - 1;
    CHECK(Validate(host, plugin) == Status::PluginTooSmall);

    plugin = Plugin();
    auto smallHost = Host();
    smallHost.structSize = BZLOADER_HOST_API_V1_SIZE - 1;
    CHECK(Validate(smallHost, plugin) == Status::HostTooSmall);

    // A plugin must never claim it wrote more than the host's buffer holds.
    plugin = Plugin();
    plugin.structSize = sizeof(BZPluginInfo) + 8u;
    CHECK(Validate(host, plugin) == Status::PluginTooLarge);

    // The v1 prefix must stay a prefix: these bounds are the ABI promise.
    CHECK(BZLOADER_PLUGIN_INFO_V1_SIZE <= sizeof(BZPluginInfo));
    CHECK(BZLOADER_HOST_API_V1_SIZE <= sizeof(BZHostApi));
    CHECK(BZLOADER_PLUGIN_INFO_V1_SIZE ==
          BZLOADER_FIELD_END(BZPluginInfo, supportedGameMask));
    CHECK(BZLOADER_HOST_API_V1_SIZE == BZLOADER_FIELD_END(BZHostApi, log));

    // ---- ordering and discovery -------------------------------------------
    std::vector<BZLoader::CatalogEntry> catalog = {
        {L"C:\\Game\\plugins\\z.dll", "org.example.z", 10},
        {L"C:\\Game\\plugins\\b.dll", "org.example.b", -5},
        {L"C:\\Game\\plugins\\a.dll", "org.example.a", 10}};
    std::sort(catalog.begin(), catalog.end(), BZLoader::CatalogLess);
    CHECK(catalog[0].pluginId == "org.example.b");
    CHECK(catalog[1].pluginId == "org.example.a");
    CHECK(catalog[2].pluginId == "org.example.z");
    CHECK(BZLoader::HasDuplicatePluginId(catalog, "ORG.EXAMPLE.A"));
    CHECK(!BZLoader::HasDuplicatePluginId(catalog, "org.example.missing"));
    CHECK(BZLoader::GetPluginDirectory(L"C:\\Game\\bzloader.dll") == L"C:\\Game\\plugins");
    CHECK(BZLoader::GetPluginDirectory(L"bzloader.dll") == L"plugins");

    if (g_Failures != 0)
    {
        std::printf("bzloader catalog tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("bzloader catalog tests passed\n");
    return 0;
}
