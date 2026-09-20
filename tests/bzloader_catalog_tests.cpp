#include "bzloader_catalog.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    BZHostApi Host()
    {
        return {sizeof(BZHostApi), BZLOADER_ABI_VERSION, BZLOADER_VERSION,
                BZ_GAME_BATTLEZONE_98_REDUX, L"C:\\Game", L"C:\\Game\\Battlezone98Redux.exe",
                "pe-12345678-01000000", nullptr};
    }

    BZPluginInfo Plugin()
    {
        return {sizeof(BZPluginInfo), BZLOADER_ABI_VERSION, "org.example.plugin",
                "Example", "1.2.3", BZ_GAME_MASK_BATTLEZONE_98_REDUX,
                nullptr, nullptr, nullptr, 0, 0};
    }
}

int main()
{
    std::string reason;
    auto host = Host();
    auto plugin = Plugin();
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::Ok);

    plugin.requiredLoaderAbi = BZLOADER_ABI_VERSION + 1;
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::AbiMismatch);
    plugin = Plugin();
    plugin.pluginId = "bad plugin id";
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::InvalidPluginId);
    plugin = Plugin();
    plugin.supportedGameMask = BZ_GAME_MASK_BATTLEZONE_15;
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::UnsupportedGame);
    plugin = Plugin();
    plugin.supportedBuildId = "pe-AAAAAAAA-BBBBBBBB";
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::UnsupportedBuild);
    plugin = Plugin();
    plugin.structSize = 1;
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::PluginTooSmall);
    plugin = Plugin();
    host.structSize = 1;
    assert(BZLoader::ValidateMetadata(host, plugin, reason) == BZLoader::MetadataStatus::HostTooSmall);

    std::vector<BZLoader::CatalogEntry> catalog = {
        {L"C:\\Game\\plugins\\z.dll", "org.example.z", 10},
        {L"C:\\Game\\plugins\\b.dll", "org.example.b", -5},
        {L"C:\\Game\\plugins\\a.dll", "org.example.a", 10}};
    std::sort(catalog.begin(), catalog.end(), BZLoader::CatalogLess);
    assert(catalog[0].pluginId == "org.example.b");
    assert(catalog[1].pluginId == "org.example.a");
    assert(catalog[2].pluginId == "org.example.z");
    assert(BZLoader::HasDuplicatePluginId(catalog, "ORG.EXAMPLE.A"));
    assert(!BZLoader::HasDuplicatePluginId(catalog, "org.example.missing"));
    assert(BZLoader::GetPluginDirectory(L"C:\\Game\\bzloader.dll") == L"C:\\Game\\plugins");
    assert(BZLoader::GetPluginDirectory(L"bzloader.dll") == L"plugins");

    std::cout << "bzloader catalog tests passed\n";
    return 0;
}
