// build_overlay.cpp
// BZR Open Shim - selecting the patches.json entries for the running exe build.
// See build_overlay.h.
#include "build_overlay.h"

#include <cstdlib>

namespace BZROpenShim::BuildOverlay
{
    namespace
    {
        // Arrays whose entries are keyed "<section>/<name>" in an overlay.
        constexpr const char* kSections[] = {
            "patches", "resolves", "engine_addresses", "globals", "static_pointers",
        };
        // Single objects keyed by their own section name.
        constexpr const char* kObjects[] = { "audio_gas_pattern" };

        bool ParseStamp(const nlohmann::json& value, uint32_t& out)
        {
            if (!value.is_string()) return false;
            const std::string text = value.get<std::string>();
            if (text.size() < 3 || text[0] != '0' || (text[1] != 'x' && text[1] != 'X')) return false;
            char* end = nullptr;
            const unsigned long parsed = std::strtoul(text.c_str() + 2, &end, 16);
            if (!end || *end != '\0' || parsed > 0xFFFFFFFFul) return false;
            out = static_cast<uint32_t>(parsed);
            return true;
        }

        // True when block names exeStamp. Appends a message for a malformed block.
        bool Describes(const nlohmann::json& block, uint32_t exeStamp, std::string& label, std::string& error)
        {
            if (!block.is_object())
            {
                error += "build block is not an object; ";
                return false;
            }
            label = block.contains("label") && block["label"].is_string()
                ? block["label"].get<std::string>() : std::string("(unlabelled)");
            const auto stamps = block.find("time_date_stamps");
            if (stamps == block.end() || !stamps->is_array() || stamps->empty())
            {
                error += "build '" + label + "' has no time_date_stamps; ";
                return false;
            }
            bool match = false;
            for (const auto& s : *stamps)
            {
                uint32_t stamp = 0;
                if (!ParseStamp(s, stamp))
                {
                    error += "build '" + label + "' has a time_date_stamp that is not 0x-hex; ";
                    continue;
                }
                match = match || stamp == exeStamp;
            }
            return match;
        }

        void ApplyOverlay(nlohmann::json& doc, const nlohmann::json& entries, Selection& sel)
        {
            const bool haveEntries = entries.is_object();
            for (const char* section : kSections)
            {
                const auto it = doc.find(section);
                if (it == doc.end() || !it->is_array()) continue;
                nlohmann::json kept = nlohmann::json::array();
                for (const auto& entry : *it)
                {
                    const std::string name = entry.is_object() && entry.contains("name") && entry["name"].is_string()
                        ? entry["name"].get<std::string>() : std::string();
                    const std::string key = std::string(section) + "/" + name;
                    const auto over = haveEntries ? entries.find(key) : entries.end();
                    if (name.empty() || !haveEntries || over == entries.end() || !over->is_object())
                    {
                        ++sel.dropped;
                        continue;
                    }
                    nlohmann::json merged = entry;
                    for (const auto& field : over->items())
                        merged[field.key()] = field.value();
                    merged["name"] = name;
                    kept.push_back(std::move(merged));
                    ++sel.replaced;
                }
                *it = std::move(kept);
            }
            for (const char* object : kObjects)
            {
                const auto it = doc.find(object);
                if (it == doc.end()) continue;
                const auto over = haveEntries ? entries.find(object) : entries.end();
                if (!haveEntries || over == entries.end() || !over->is_object() || !it->is_object())
                {
                    doc.erase(it);
                    ++sel.dropped;
                    continue;
                }
                for (const auto& field : over->items())
                    (*it)[field.key()] = field.value();
                ++sel.replaced;
            }
        }
    }

    Selection Apply(nlohmann::json& doc, uint32_t exeStamp)
    {
        Selection sel;
        try
        {
            if (!doc.is_object()) return sel;
            const auto base = doc.find("build");
            if (base == doc.end())
            {
                doc.erase("build_overlays");
                return sel; // Unversioned: the caller keeps its own version check
            }

            std::string label;
            const bool isBase = Describes(*base, exeStamp, label, sel.error);
            sel.known.push_back(label);
            if (isBase)
            {
                sel.match = Match::Base;
                sel.label = label;
            }

            const nlohmann::json* chosen = nullptr;
            const auto overlays = doc.find("build_overlays");
            if (overlays != doc.end() && overlays->is_array())
            {
                for (const auto& overlay : *overlays)
                {
                    std::string olabel;
                    const bool hit = overlay.is_object() && overlay.contains("build") &&
                        Describes(overlay["build"], exeStamp, olabel, sel.error);
                    if (!overlay.is_object() || !overlay.contains("build"))
                        sel.error += "build_overlays entry has no build block; ";
                    else
                        sel.known.push_back(olabel);
                    if (hit && sel.match != Match::Base && !chosen)
                    {
                        chosen = &overlay;
                        sel.match = Match::Overlay;
                        sel.label = olabel;
                    }
                }
            }
            else if (overlays != doc.end())
            {
                sel.error += "build_overlays is not an array; ";
            }

            if (sel.match == Match::Overlay)
            {
                const nlohmann::json entries = chosen->contains("entries")
                    ? (*chosen)["entries"] : nlohmann::json();
                ApplyOverlay(doc, entries, sel);
            }
            else if (sel.match != Match::Base)
            {
                // Nothing in the file is known to hold for this exe. Data rows
                // carry no guard bytes, so leaving the base entries visible
                // would let any reader outside the patcher's gate bind them.
                sel.match = Match::Unknown;
                ApplyOverlay(doc, nlohmann::json(), sel);
            }
            doc.erase("build_overlays");
        }
        catch (const std::exception& e)
        {
            sel.match = Match::Unknown;
            sel.error += std::string("build selection failed: ") + e.what();
        }
        return sel;
    }

    const char* MatchName(Match match)
    {
        switch (match)
        {
        case Match::Base: return "base";
        case Match::Overlay: return "overlay";
        case Match::Unknown: return "unknown";
        default: return "unversioned";
        }
    }
}
