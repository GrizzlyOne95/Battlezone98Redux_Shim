#include "openshim_update_manifest.h"

#include <algorithm>
#include <cctype>
#include <regex>

namespace BZROpenShim
{
    namespace
    {
        bool IsSha256(const std::string& value)
        {
            return value.size() == 64 &&
                std::all_of(value.begin(), value.end(), [](unsigned char ch)
                {
                    return std::isxdigit(ch) != 0;
                });
        }

        std::string Lower(std::string value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch)
            {
                return static_cast<char>(std::tolower(ch));
            });
            return value;
        }

        bool ReadUnsigned(const std::string& text,
                          const char* key,
                          uint64_t& value)
        {
            const std::regex expression(
                std::string("(?:^|[\\r\\n])\\s*") + key + R"(\s*=\s*([0-9]+)\s*,?)");
            std::smatch match;
            if (!std::regex_search(text, match, expression))
                return false;

            try
            {
                value = std::stoull(match[1].str());
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        std::string UnescapeLuaString(const std::string& value)
        {
            std::string decoded;
            decoded.reserve(value.size());
            for (size_t index = 0; index < value.size(); ++index)
            {
                if (value[index] == '\\' && index + 1 < value.size())
                {
                    const char next = value[index + 1];
                    switch (next)
                    {
                    case '\\': decoded.push_back('\\'); ++index; break;
                    case '"': decoded.push_back('"'); ++index; break;
                    case 39: decoded.push_back('\''); ++index; break;
                    case 'n': decoded.push_back('\n'); ++index; break;
                    case 'r': decoded.push_back('\r'); ++index; break;
                    case 't': decoded.push_back('\t'); ++index; break;
                    case 'a': decoded.push_back('\a'); ++index; break;
                    case 'b': decoded.push_back('\b'); ++index; break;
                    case 'f': decoded.push_back('\f'); ++index; break;
                    case 'v': decoded.push_back('\v'); ++index; break;
                    default: decoded.push_back(value[index]); break;
                    }
                }
                else
                {
                    decoded.push_back(value[index]);
                }
            }
            return decoded;
        }

        bool ReadQuoted(const std::string& text,
                        const char* key,
                        std::string& value)
        {
            const std::regex expression(
                std::string("(?:^|[\\r\\n])\\s*") + key + R"MANIFEST(\s*=\s*"([^"]*)"\s*,?)MANIFEST");
            std::smatch match;
            if (!std::regex_search(text, match, expression))
                return false;
            value = UnescapeLuaString(match[1].str());
            return true;
        }

        bool ReadPayload(const std::string& text,
                         const char* name,
                         OpenShimUpdatePayloadManifest& payload)
        {
            const std::string pattern =
                std::string("(?:^|[\\r\\n])\\s*") + name +
                R"MANIFEST(\s*=\s*\{\s*source\s*=\s*"([^"]+)"\s*,\s*destination\s*=\s*"([^"]+)"\s*,\s*sha256\s*=\s*"([0-9A-Fa-f]{64})"\s*,\s*size\s*=\s*([0-9]+)(?:\s*,\s*version\s*=\s*"([^"]+)")?(?:\s*,\s*architecture\s*=\s*"([^"]+)")?\s*\}\s*,?)MANIFEST";
            std::smatch match;
            if (!std::regex_search(text, match, std::regex(pattern)))
                return false;

            payload.source = UnescapeLuaString(match[1].str());
            payload.destination = UnescapeLuaString(match[2].str());
            payload.sha256 = Lower(UnescapeLuaString(match[3].str()));
            try
            {
                payload.size = std::stoull(match[4].str());
            }
            catch (...)
            {
                return false;
            }
            payload.version = match[5].matched ? UnescapeLuaString(match[5].str()) : std::string();
            payload.architecture = match[6].matched ? UnescapeLuaString(match[6].str()) : std::string();
            return true;
        }
    }

    bool ParseOpenShimUpdateManifest(const std::string& text,
                                     OpenShimUpdateManifest& manifest,
                                     std::string& error)
    {
        manifest = {};
        error.clear();

        uint64_t formatVersion = 0;
        if (!ReadUnsigned(text, "formatVersion", formatVersion) || formatVersion != 2)
        {
            error = "unsupported or missing manifest formatVersion";
            return false;
        }
        manifest.formatVersion = static_cast<uint32_t>(formatVersion);

        if (!ReadQuoted(text, "version", manifest.version) || manifest.version.empty() ||
            !ReadQuoted(text, "sha256", manifest.sha256) ||
            !ReadUnsigned(text, "size", manifest.size) ||
            !ReadQuoted(text, "architecture", manifest.architecture) ||
            !ReadPayload(text, "winmm", manifest.winmm) ||
            !ReadPayload(text, "network", manifest.network) ||
            !ReadPayload(text, "patches", manifest.patches))
        {
            error = "manifest is missing a required field or payload";
            return false;
        }

        manifest.sha256 = Lower(manifest.sha256);
        if (!IsSha256(manifest.sha256) || manifest.architecture != "x86" ||
            manifest.winmm.source != "winmm.dll" ||
            manifest.winmm.destination != "winmm.dll" ||
            manifest.network.source != "openshim_net.ini.payload" ||
            manifest.network.destination != "net.ini" ||
            manifest.patches.source != "openshim_patches.json.payload" ||
            manifest.patches.destination != "scripts\\patches.json" ||
            manifest.winmm.sha256 != manifest.sha256 ||
            manifest.winmm.size != manifest.size ||
            manifest.winmm.version != manifest.version ||
            manifest.winmm.architecture != "x86" ||
            !IsSha256(manifest.network.sha256) ||
            !IsSha256(manifest.patches.sha256))
        {
            error = "manifest identity or payload metadata is invalid";
            return false;
        }

        return true;
    }
}
