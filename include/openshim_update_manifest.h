#pragma once

#include <cstdint>
#include <string>
#include <vector>

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
        // The replacement helper the updater launches from the Workshop item.
        // It is not installed anywhere, so only source, sha256 and size are
        // attested; destination stays empty.
        OpenShimUpdatePayloadManifest helper;
    };

    // Parses the generated OpenShimManifest.lua data-only format. This is not
    // a Lua evaluator: only the exact scalar fields and payload table shape
    // emitted by Campaign Reimagined's packaging tool are accepted.
    bool ParseOpenShimUpdateManifest(const std::string& text,
                                     OpenShimUpdateManifest& manifest,
                                     std::string& error);

    // Dotted numeric versions only ("1.0.0.33"). Anything else, including an
    // empty string, a suffix or a stray separator, is a parse failure rather
    // than a zero, so a caller can refuse to compare instead of guessing.
    bool ParseOpenShimVersion(const std::string& text, std::vector<uint32_t>& parts);

    // Missing trailing components compare as zero ("1.0" == "1.0.0.0").
    // Returns false, leaving order untouched, when either side fails to parse.
    bool CompareOpenShimVersions(const std::string& left,
                                 const std::string& right,
                                 int& order);
}
