#pragma once

#include <cstdint>
#include <string>

namespace BZROpenShim
{
    struct OpenShimUpdatePayloadManifest
    {
        std::string source;
        std::string destination;
        std::string sha256;
        uint64_t size = 0;
        std::string version;
        std::string architecture;
    };

    struct OpenShimUpdateManifest
    {
        uint32_t formatVersion = 0;
        std::string version;
        std::string sha256;
        uint64_t size = 0;
        std::string architecture;
        OpenShimUpdatePayloadManifest winmm;
        OpenShimUpdatePayloadManifest network;
        OpenShimUpdatePayloadManifest patches;
    };

    // Parses the generated OpenShimManifest.lua data-only format. This is not
    // a Lua evaluator: only the exact scalar fields and payload table shape
    // emitted by Campaign Reimagined's packaging tool are accepted.
    bool ParseOpenShimUpdateManifest(const std::string& text,
                                     OpenShimUpdateManifest& manifest,
                                     std::string& error);
}
