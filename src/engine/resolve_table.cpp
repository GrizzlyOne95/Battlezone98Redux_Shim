// resolve_table.cpp
// BZR Open Shim - parsing for the "resolves" array in scripts/patches.json.
//
// Deliberately free of <Windows.h> so the JSON-to-target mapping can be
// exercised by tests/resolve_table_tests.cpp on the host.
#include "resolve_table.h"

#include <cstdlib>
#include <sstream>

#include <nlohmann/json.hpp>

namespace BZROpenShim
{
    namespace
    {
        // Accepts what the "patches" array has always accepted - bare hex
        // bytes, optionally 0x-prefixed - but reports failure instead of
        // throwing, so a typo in one token cannot escape as an exception from
        // inside a scan.
        bool ParseHexByte(const std::string& token, uint16_t& out)
        {
            if (token.empty())
                return false;

            char* end = nullptr;
            const unsigned long value = std::strtoul(token.c_str(), &end, 16);
            if (end == token.c_str() || (end != nullptr && *end != '\0'))
                return false;
            if (value > 0xFFul)
                return false;

            out = static_cast<uint16_t>(value);
            return true;
        }

        uint32_t ParseHexAddress(const std::string& text, bool& ok)
        {
            ok = false;
            if (text.empty())
                return 0;

            char* end = nullptr;
            const unsigned long long value = std::strtoull(text.c_str(), &end, 16);
            if (end == text.c_str() || (end != nullptr && *end != '\0'))
                return 0;
            if (value > 0xFFFFFFFFull)
                return 0;

            ok = true;
            return static_cast<uint32_t>(value);
        }

        void AppendError(std::string* error, const std::string& message)
        {
            if (!error)
                return;
            if (!error->empty())
                error->push_back('\n');
            error->append(message);
        }
    }

    std::vector<uint16_t> ParseIdaPatternText(const std::string& hex)
    {
        std::vector<uint16_t> pattern;
        std::istringstream stream(hex);
        std::string token;
        while (stream >> token)
        {
            if (token == "?" || token == "??")
            {
                pattern.push_back(0x100);
                continue;
            }

            uint16_t value = 0;
            if (!ParseHexByte(token, value))
            {
                // Fail the whole pattern rather than silently matching on the
                // prefix that happened to parse.
                return {};
            }
            pattern.push_back(value);
        }
        return pattern;
    }

    std::vector<ResolveTarget> ParseResolveTable(const std::string& jsonText,
                                                 std::string* error)
    {
        std::vector<ResolveTarget> targets;

        nlohmann::json root;
        try
        {
            root = nlohmann::json::parse(jsonText);
        }
        catch (const std::exception& e)
        {
            AppendError(error, std::string("patches.json did not parse: ") + e.what());
            return targets;
        }

        if (!root.is_object() || !root.contains("resolves"))
            return targets;

        const nlohmann::json& resolves = root["resolves"];
        if (!resolves.is_array())
        {
            AppendError(error, "\"resolves\" must be an array");
            return targets;
        }

        size_t index = 0;
        for (const auto& entry : resolves)
        {
            const std::string where = "resolves[" + std::to_string(index++) + "]";

            if (!entry.is_object())
            {
                AppendError(error, where + " is not an object");
                continue;
            }

            ResolveTarget target;

            if (!entry.contains("name") || !entry["name"].is_string() ||
                entry["name"].get<std::string>().empty())
            {
                AppendError(error, where + " has no \"name\"");
                continue;
            }
            target.name = entry["name"].get<std::string>();

            if (!entry.contains("pattern") || !entry["pattern"].is_string())
            {
                AppendError(error, where + " (" + target.name + ") has no \"pattern\"");
                continue;
            }
            target.ida_pattern = entry["pattern"].get<std::string>();
            if (ParseIdaPatternText(target.ida_pattern).empty())
            {
                AppendError(error, where + " (" + target.name + ") has an unparseable pattern");
                continue;
            }

            // An identity note is mandatory: a signature that nobody can trace
            // back to independent evidence is the failure mode this table
            // exists to make visible, not a shortcut it should permit.
            if (!entry.contains("identity") || !entry["identity"].is_string() ||
                entry["identity"].get<std::string>().empty())
            {
                AppendError(error, where + " (" + target.name + ") has no \"identity\" note");
                continue;
            }
            target.identity = entry["identity"].get<std::string>();

            if (entry.contains("offset"))
            {
                if (!entry["offset"].is_number_integer())
                {
                    AppendError(error, where + " (" + target.name + ") has a non-integer offset");
                    continue;
                }
                target.offset = entry["offset"].get<int32_t>();
            }

            if (entry.contains("mode"))
            {
                const std::string mode = entry["mode"].is_string()
                    ? entry["mode"].get<std::string>()
                    : std::string();
                if (mode == "address")
                    target.mode = ResolveMode::Address;
                else if (mode == "rel32_target")
                    target.mode = ResolveMode::Rel32Target;
                else
                {
                    AppendError(error, where + " (" + target.name + ") has an unknown mode");
                    continue;
                }
            }

            if (entry.contains("prefer"))
            {
                const std::string prefer = entry["prefer"].is_string()
                    ? entry["prefer"].get<std::string>()
                    : std::string();
                if (prefer == "scan")
                    target.preference = ResolvePreference::Scan;
                else if (prefer == "fallback")
                    target.preference = ResolvePreference::Fallback;
                else
                {
                    AppendError(error, where + " (" + target.name + ") has an unknown prefer");
                    continue;
                }
            }

            if (entry.contains("require_unique") && entry["require_unique"].is_boolean())
                target.require_unique = entry["require_unique"].get<bool>();

            if (entry.contains("fallback"))
            {
                if (!entry["fallback"].is_string())
                {
                    AppendError(error, where + " (" + target.name + ") has a non-string fallback");
                    continue;
                }
                bool ok = false;
                const uint32_t address = ParseHexAddress(entry["fallback"].get<std::string>(), ok);
                if (!ok)
                {
                    AppendError(error, where + " (" + target.name + ") has an unparseable fallback");
                    continue;
                }
                target.fallback_addr = address;
            }

            if (target.preference == ResolvePreference::Fallback && target.fallback_addr == 0)
            {
                AppendError(error, where + " (" + target.name + ") prefers a fallback it does not have");
                continue;
            }

            targets.push_back(std::move(target));
        }

        return targets;
    }
}
