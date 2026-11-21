#pragma once

// Engine-independent rules for the single-player Database screen
// (Docs/DATABASE_SCREEN.md): the content file format, the override merge, the
// unit .inf header, and the unit stat text read from the ODF.
//
// Content file (resources/database/oshdb.cfg, embedded in the DLL; a mod such
// as Campaign Reimagined ships its own oshdb.cfg to override it):
//
//   ; comment            (# also starts a comment; a ` ;` or ` #` after
//                        whitespace also ends a value or a header, unless
//                        inside quotes; `a|b;c` keeps its `;`)
//   [tab nsdf]           a left-hand tab, in file order
//   label = NSDF
//
//   [unit avtank]        an entry; the kind names how the screen shows it
//   tab = nsdf
//   name = ...           optional; else the role from avtank.inf line 1
//   model = ...          optional; else the model from avtank.inf line 1
//   designation = M60A7 Grizzly | BZ98 Redux manual p10   (repeatable)
//   icon = LoadingScreen avtank_v1.png                     (optional)
//   lore =               (kept empty until stock lore is cited)
//
//   [campaign nsdf]      a Briefings-tab entry: missions with .des pages
//   tab = briefings
//   label = NSDF
//   missions = misn01 misn02 ...                           (repeatable)
//
// Kinds other than tab/unit/campaign parse and merge like any section, so a
// later kind (relic, personnel) needs no format change. The override merges
// per (kind, id): each key it names replaces every value of that key in the
// stock section (a repeated key is replaced as a whole list), `remove = 1`
// drops the section, and a section the stock file lacks is appended.
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim::DatabasePolicy
{
    constexpr const char* kContentFileName = "oshdb.cfg";
    constexpr const char* kKindTab = "tab";
    constexpr const char* kKindUnit = "unit";
    constexpr const char* kKindCampaign = "campaign";
    // ODF weapon slots read: weaponName1 .. weaponName<kMaxWeaponSlots>.
    constexpr int kMaxWeaponSlots = 8;

    inline std::string Trim(const std::string& text)
    {
        size_t start = 0;
        size_t end = text.size();
        while (start < end && std::isspace(static_cast<unsigned char>(text[start])))
            ++start;
        while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])))
            --end;
        return text.substr(start, end - start);
    }

    inline std::string Lower(std::string text)
    {
        for (char& c : text)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return text;
    }

    // Splits on CRLF, LF or a lone CR (stock .inf/.des files mix them).
    inline std::vector<std::string> SplitLines(const std::string& text)
    {
        std::vector<std::string> lines;
        std::string line;
        for (size_t i = 0; i < text.size(); ++i)
        {
            const char c = text[i];
            if (c == '\r' || c == '\n')
            {
                lines.push_back(line);
                line.clear();
                if (c == '\r' && i + 1 < text.size() && text[i + 1] == '\n')
                    ++i;
                continue;
            }
            line.push_back(c);
        }
        if (!line.empty())
            lines.push_back(line);
        return lines;
    }

    // ---- content file ----------------------------------------------------

    struct Section
    {
        std::string kind;  // lower case
        std::string id;    // lower case
        std::vector<std::pair<std::string, std::string>> values;  // key lower case, in file order

        // The last value of `key`, or `fallback` when absent.
        std::string Get(const std::string& key, const std::string& fallback = std::string()) const
        {
            for (size_t i = values.size(); i > 0; --i)
                if (values[i - 1].first == key)
                    return values[i - 1].second;
            return fallback;
        }

        std::vector<std::string> GetAll(const std::string& key) const
        {
            std::vector<std::string> out;
            for (const auto& value : values)
                if (value.first == key)
                    out.push_back(value.second);
            return out;
        }

        bool Has(const std::string& key) const
        {
            for (const auto& value : values)
                if (value.first == key)
                    return true;
            return false;
        }
    };

    struct Content
    {
        std::vector<Section> sections;

        const Section* Find(const std::string& kind, const std::string& id) const
        {
            for (const Section& s : sections)
                if (s.kind == kind && s.id == id)
                    return &s;
            return nullptr;
        }

        std::vector<const Section*> OfKind(const std::string& kind) const
        {
            std::vector<const Section*> out;
            for (const Section& s : sections)
                if (s.kind == kind)
                    out.push_back(&s);
            return out;
        }

        // Entries (any kind but tab) whose `tab` is `tabId`, in file order.
        std::vector<const Section*> InTab(const std::string& tabId) const
        {
            std::vector<const Section*> out;
            for (const Section& s : sections)
                if (s.kind != kKindTab && Lower(s.Get("tab")) == tabId)
                    out.push_back(&s);
            return out;
        }
    };

    inline bool IsTrue(const std::string& value)
    {
        const std::string v = Lower(Trim(value));
        return v == "1" || v == "true" || v == "yes" || v == "on";
    }

    // Parses `text`. Bad lines are skipped and described in `errors`
    // ("line N: ..."); the rest still loads. A repeated [kind id] header
    // continues the earlier section.
    // Removes a trailing " ; x" / " # x" comment: the marker must follow
    // whitespace (or open the text) and sit outside double quotes.
    inline std::string StripValueComment(const std::string& text)
    {
        bool quoted = false;
        for (size_t i = 0; i < text.size(); ++i)
        {
            const char c = text[i];
            if (c == '"')
                quoted = !quoted;
            else if (!quoted && (c == ';' || c == '#') && (i == 0 || std::isspace(static_cast<unsigned char>(text[i - 1]))))
                return Trim(text.substr(0, i));
        }
        return Trim(text);
    }

    // Drops a leading UTF-8 byte order mark.
    inline std::string StripBom(const std::string& text)
    {
        if (text.size() >= 3 && static_cast<unsigned char>(text[0]) == 0xEF &&
            static_cast<unsigned char>(text[1]) == 0xBB && static_cast<unsigned char>(text[2]) == 0xBF)
            return text.substr(3);
        return text;
    }

    inline Content ParseContent(const std::string& text, std::vector<std::string>* errors = nullptr)
    {
        Content content;
        Section* current = nullptr;
        const auto fail = [errors](size_t line, const char* why) {
            if (errors)
                errors->push_back("line " + std::to_string(line) + ": " + why);
        };
        const std::vector<std::string> lines = SplitLines(text);
        for (size_t n = 0; n < lines.size(); ++n)
        {
            std::string line = Trim(lines[n]);
            if (n == 0)
                line = Trim(StripBom(line));
            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;
            if (line[0] == '[')
            {
                current = nullptr;
                const size_t close = line.find(']');
                const std::string after = close == std::string::npos ? std::string() : Trim(line.substr(close + 1));
                if (close == std::string::npos || (!after.empty() && after[0] != ';' && after[0] != '#'))
                {
                    fail(n + 1, "bad section header");
                    continue;
                }
                const std::string inner = Trim(line.substr(1, close - 1));
                const size_t space = inner.find_first_of(" \t");
                if (space == std::string::npos)
                {
                    fail(n + 1, "section header needs a kind and an id");
                    continue;
                }
                const std::string kind = Lower(inner.substr(0, space));
                const std::string id = Lower(Trim(inner.substr(space + 1)));
                if (id.empty() || id.find_first_of(" \t") != std::string::npos)
                {
                    fail(n + 1, "section id must be one word");
                    continue;
                }
                for (Section& s : content.sections)
                    if (s.kind == kind && s.id == id)
                        current = &s;
                if (!current)
                {
                    content.sections.push_back(Section{ kind, id, {} });
                    current = &content.sections.back();
                }
                continue;
            }
            const size_t equals = line.find('=');
            if (equals == std::string::npos || equals == 0)
            {
                fail(n + 1, "expected key = value");
                continue;
            }
            if (!current)
            {
                fail(n + 1, "value outside a section");
                continue;
            }
            current->values.emplace_back(Lower(Trim(line.substr(0, equals))), StripValueComment(line.substr(equals + 1)));
        }
        return content;
    }

    // Stock content with `override` merged over it (see the header comment).
    // `warnings` (optional) gets one line per tab a mod removed that still
    // has entries pointing at it; those entries no longer show anywhere.
    inline Content MergeContent(const Content& stock, const Content& override,
                                std::vector<std::string>* warnings = nullptr)
    {
        Content merged = stock;
        for (const Section& over : override.sections)
        {
            Section* target = nullptr;
            size_t index = 0;
            for (size_t i = 0; i < merged.sections.size(); ++i)
                if (merged.sections[i].kind == over.kind && merged.sections[i].id == over.id)
                {
                    target = &merged.sections[i];
                    index = i;
                }
            const bool remove = IsTrue(over.Get("remove"));
            if (remove)
            {
                if (target)
                    merged.sections.erase(merged.sections.begin() + static_cast<std::ptrdiff_t>(index));
                continue;
            }
            if (!target)
            {
                merged.sections.push_back(over);
                continue;
            }
            std::vector<std::string> replaced;
            for (const auto& value : over.values)
            {
                bool seen = false;
                for (const std::string& key : replaced)
                    seen = seen || key == value.first;
                if (!seen)
                {
                    replaced.push_back(value.first);
                    auto& list = target->values;
                    for (size_t i = list.size(); i > 0; --i)
                        if (list[i - 1].first == value.first)
                            list.erase(list.begin() + static_cast<std::ptrdiff_t>(i - 1));
                }
                target->values.push_back(value);
            }
        }
        if (warnings)
            for (const Section* tab : stock.OfKind(kKindTab))
            {
                if (merged.Find(kKindTab, tab->id))
                    continue;
                const size_t orphans = merged.InTab(tab->id).size();
                if (orphans > 0)
                    warnings->push_back("tab '" + tab->id + "' was removed but " + std::to_string(orphans) +
                                        " entries still point at it; they are not shown");
            }
        return merged;
    }

    // "M60A7 Grizzly | BZ98 Redux manual p10" -> text and citation.
    struct Designation
    {
        std::string text;
        std::string citation;
    };

    inline Designation ParseDesignation(const std::string& value)
    {
        const size_t bar = value.find('|');
        if (bar == std::string::npos)
            return { Trim(value), std::string() };
        return { Trim(value.substr(0, bar)), Trim(value.substr(bar + 1)) };
    }

    // "misn01 misn02, misn03" -> each mission stem, lower case.
    inline std::vector<std::string> SplitList(const std::string& value)
    {
        std::vector<std::string> out;
        std::string item;
        for (char c : value)
        {
            if (c == ',' || std::isspace(static_cast<unsigned char>(c)))
            {
                if (!item.empty())
                    out.push_back(Lower(item));
                item.clear();
                continue;
            }
            item.push_back(c);
        }
        if (!item.empty())
            out.push_back(Lower(item));
        return out;
    }

    // ---- unit .inf header --------------------------------------------------

    struct InfHeader
    {
        std::string model;  // "GRIZZLY"; empty when the header names none
        std::string role;   // "MEDIUM TANK"
    };

    // Stock .inf files open with "MODEL - ROLE:", "ROLE:" alone, or the
    // Fury form "Name: Fury" then "Function: Sentient Fighter".
    inline InfHeader ParseInfHeader(const std::string& text)
    {
        InfHeader header;
        const std::vector<std::string> lines = SplitLines(StripBom(text));
        size_t first = 0;
        while (first < lines.size() && Trim(lines[first]).empty())
            ++first;
        if (first >= lines.size())
            return header;
        const std::string line = Trim(lines[first]);
        if (Lower(line).rfind("name:", 0) == 0)
        {
            header.model = Trim(line.substr(5));
            if (first + 1 < lines.size())
            {
                const std::string next = Trim(lines[first + 1]);
                if (Lower(next).rfind("function:", 0) == 0)
                    header.role = Trim(next.substr(9));
            }
            return header;
        }
        std::string body = line;
        if (!body.empty() && body.back() == ':')
            body.pop_back();
        const size_t dash = body.find(" - ");
        if (dash == std::string::npos)
        {
            header.role = Trim(body);
            return header;
        }
        header.model = Trim(body.substr(0, dash));
        header.role = Trim(body.substr(dash + 3));
        return header;
    }

    // ---- ODF -------------------------------------------------------------

    // One ODF as [section] key = value, comments and quotes stripped.
    struct Odf
    {
        struct Entry
        {
            std::string section;  // lower case
            std::string key;      // lower case
            std::string value;
        };
        std::vector<Entry> entries;

        // First value of `key` in `section` (any section when empty).
        std::string Get(const std::string& section, const std::string& key) const
        {
            const std::string s = Lower(section);
            const std::string k = Lower(key);
            for (const Entry& e : entries)
                if (e.key == k && (s.empty() || e.section == s))
                    return e.value;
            return std::string();
        }
    };

    inline Odf ParseOdf(const std::string& text)
    {
        Odf odf;
        std::string section;
        for (const std::string& raw : SplitLines(text))
        {
            std::string line = raw;
            bool quoted = false;
            for (size_t i = 0; i < line.size(); ++i)
            {
                if (line[i] == '"')
                    quoted = !quoted;
                else if (!quoted && (line[i] == ';' || (line[i] == '/' && i + 1 < line.size() && line[i + 1] == '/')))
                {
                    line.resize(i);
                    break;
                }
            }
            line = Trim(line);
            if (line.empty())
                continue;
            if (line[0] == '[')
            {
                const size_t close = line.find(']');
                section = Lower(Trim(line.substr(1, close == std::string::npos ? std::string::npos : close - 1)));
                continue;
            }
            const size_t equals = line.find('=');
            if (equals == std::string::npos)
                continue;
            std::string value = Trim(line.substr(equals + 1));
            if (value.size() >= 2 && value.front() == '"')
            {
                const size_t endQuote = value.find('"', 1);
                value = value.substr(1, endQuote == std::string::npos ? std::string::npos : endQuote - 1);
            }
            odf.entries.push_back({ section, Lower(Trim(line.substr(0, equals))), value });
        }
        return odf;
    }

    // "20.0" -> "20", "400.0f" -> "400", "1.25" -> "1.25"; text that is not a
    // number comes back as written; empty -> "-".
    inline std::string FormatNumber(const std::string& raw)
    {
        std::string text = Trim(raw);
        if (text.empty())
            return "-";
        std::string number = text;
        if (number.back() == 'f' || number.back() == 'F')
            number.pop_back();
        char* end = nullptr;
        const double value = std::strtod(number.c_str(), &end);
        if (number.empty() || !end || *end != '\0')
            return text;
        char buffer[32] = {};
        std::snprintf(buffer, sizeof(buffer), "%.2f", value);
        std::string out = buffer;
        while (!out.empty() && out.back() == '0')
            out.pop_back();
        if (!out.empty() && out.back() == '.')
            out.pop_back();
        return out == "-0" ? "0" : out;
    }

    struct WeaponSlot
    {
        int slot = 0;
        std::string odf;   // weapon ODF stem, as weaponName<slot> names it
        std::string name;  // [WeaponClass] wpnName of that ODF; empty when unread
    };

    struct UnitStats
    {
        std::string unitName;  // [GameObjectClass] unitName
        std::string scrapCost;
        std::string health;
        std::string ammo;
        std::string speed;
        std::vector<WeaponSlot> weapons;
    };

    // Weapon ODF stem -> its wpnName (empty when it cannot be read).
    using WeaponNameFn = std::function<std::string(const std::string& weaponOdf)>;

    inline UnitStats ReadStats(const Odf& odf, const WeaponNameFn& weaponName)
    {
        UnitStats stats;
        stats.unitName = odf.Get("GameObjectClass", "unitName");
        stats.scrapCost = odf.Get("GameObjectClass", "scrapCost");
        stats.health = odf.Get("GameObjectClass", "maxHealth");
        stats.ammo = odf.Get("GameObjectClass", "maxAmmo");
        // Craft movement sits in the class section (HoverCraftClass,
        // WalkerClass, ...), so take the first velocForward anywhere.
        stats.speed = odf.Get("", "velocForward");
        for (int slot = 1; slot <= kMaxWeaponSlots; ++slot)
        {
            const std::string stem = odf.Get("GameObjectClass", "weaponName" + std::to_string(slot));
            if (stem.empty())
                continue;
            WeaponSlot weapon;
            weapon.slot = slot;
            weapon.odf = stem;
            weapon.name = weaponName ? weaponName(stem) : std::string();
            stats.weapons.push_back(weapon);
        }
        return stats;
    }

    // The detail-pane captions, English by default; the screen passes the
    // localized ones.
    struct Labels
    {
        std::string role = "Role";
        std::string model = "Model";
        std::string designations = "Model numbers";
        std::string scrapCost = "Scrap cost";
        std::string armor = "Armor";
        std::string ammo = "Ammo";
        std::string speed = "Speed";
        std::string speedUnit = "m/s";
        std::string weapons = "Weapons";
        std::string slot = "Slot";
        std::string noWeapons = "none";
        std::string odf = "ODF";
        std::string noOdf = "ODF not found";
        std::string lore = "Notes";
    };

    struct UnitDetail
    {
        std::string odf;
        std::string role;
        std::string model;
        std::vector<Designation> designations;
        bool odfFound = false;
        UnitStats stats;
        std::string lore;
    };

    // The unit's detail text for the scrolling text block, one fact per line.
    inline std::string FormatUnitDetail(const UnitDetail& unit, const Labels& labels)
    {
        std::string out;
        const auto line = [&out](const std::string& caption, const std::string& value) {
            out += caption + ": " + value + "\n";
        };
        if (!unit.role.empty())
            line(labels.role, unit.role);
        if (!unit.model.empty())
            line(labels.model, unit.model);
        std::vector<Designation> shown;
        for (const Designation& d : unit.designations)
            if (!d.text.empty())
                shown.push_back(d);
        if (!shown.empty())
        {
            out += labels.designations + ":\n";
            for (const Designation& d : shown)
                out += "  " + d.text + (d.citation.empty() ? std::string() : "  (" + d.citation + ")") + "\n";
        }
        out += "\n";
        if (!unit.odfFound)
        {
            out += labels.noOdf + " (" + unit.odf + ".odf)\n";
        }
        else
        {
            line(labels.scrapCost, FormatNumber(unit.stats.scrapCost));
            line(labels.armor, FormatNumber(unit.stats.health));
            line(labels.ammo, FormatNumber(unit.stats.ammo));
            const std::string speed = FormatNumber(unit.stats.speed);
            line(labels.speed, speed == "-" ? speed : speed + " " + labels.speedUnit);
            if (unit.stats.weapons.empty())
            {
                line(labels.weapons, labels.noWeapons);
            }
            else
            {
                out += labels.weapons + ":\n";
                for (const WeaponSlot& w : unit.stats.weapons)
                {
                    const std::string name = w.name.empty() ? w.odf : w.name + " (" + w.odf + ")";
                    out += "  " + labels.slot + " " + std::to_string(w.slot) + ": " + name + "\n";
                }
            }
        }
        line(labels.odf, unit.odf);
        if (!Trim(unit.lore).empty())
            out += "\n" + labels.lore + ":\n" + Trim(unit.lore) + "\n";
        return out;
    }

    // List caption for a unit: the model when the .inf names one, else the
    // role, else the ODF's unitName, else the ODF stem.
    inline std::string UnitCaption(const std::string& model, const std::string& role,
                                   const std::string& unitName, const std::string& odf)
    {
        if (!model.empty())
            return model;
        if (!role.empty())
            return role;
        if (!unitName.empty())
            return unitName;
        return odf;
    }

    // ---- list paging -----------------------------------------------------

    inline size_t PageCount(size_t items, size_t perPage)
    {
        return perPage == 0 || items == 0 ? 1 : (items + perPage - 1) / perPage;
    }

    // ---- 3D preview --------------------------------------------------------

    // The mesh stem the stock MP vehicle picker builds for an ODF
    // (FUN_007AA560 lines 114-152): [GameObjectClass] baseName (the key
    // hashes 0xD3DD9CEC / 0x794B13B are FNV-1a of "gameobjectclass" /
    // "basename"), cut to 8 characters, then cut at the first '.'. Stock
    // ODFs mostly have no baseName; the ODF stem, cut the same way, is the
    // fallback. baseName is taken from any section: some mod ODFs head the
    // class block [GameObject].
    inline std::string PreviewMeshStem(const Odf& odf, const std::string& odfStem)
    {
        std::string stem = odf.Get("GameObjectClass", "baseName");
        if (Trim(stem).empty())
            stem = odf.Get("", "baseName");
        if (Trim(stem).empty())
            stem = odfStem;
        stem = Trim(stem).substr(0, 8);
        const size_t dot = stem.find('.');
        if (dot != std::string::npos)
            stem.resize(dot);
        return stem;
    }

    // Camera fit for the spinning preview model. The stock camera sits at
    // (0, cameraY, distance) looking down -Z with a square viewport, and the
    // model spins about its node's Y axis. `minimum` / `maximum` are the
    // entity's local bounding box (node scale 1). The node is lifted so the
    // box's vertical centre is at camera height. The distance is the nearest
    // at which the spin cylinder (radius = the box's farthest XZ corner from
    // the axis) fits with `margin`: across, its tangent lines from the camera
    // must stay inside the half FOV (d = r * sqrt(1 + (margin / tan)^2));
    // up and down, the half height must fit at the cylinder's nearest depth
    // (d = r + margin * h / tan).
    struct PreviewFit
    {
        bool ok = false;
        float distance = 0.0f;
        float nodeY = 0.0f;
    };

    inline PreviewFit FitPreview(const float minimum[3], const float maximum[3], float fovY,
                                 float cameraY = 1.0f, float margin = 1.05f)
    {
        PreviewFit fit;
        const auto finite = [](float v) { return v == v && v > -1.0e6f && v < 1.0e6f; };
        for (int i = 0; i < 3; ++i)
            if (!finite(minimum[i]) || !finite(maximum[i]) || maximum[i] < minimum[i])
                return fit;
        if (!(fovY > 0.1f && fovY < 3.0f))
            return fit;
        const float x = std::fmax(std::fabs(minimum[0]), std::fabs(maximum[0]));
        const float z = std::fmax(std::fabs(minimum[2]), std::fabs(maximum[2]));
        const float radius = std::sqrt(x * x + z * z);
        const float halfHeight = (maximum[1] - minimum[1]) * 0.5f;
        if (std::fmax(radius, halfHeight) < 0.01f)
            return fit;
        const float slope = margin / std::tan(fovY * 0.5f);
        fit.distance = std::fmax(radius * std::sqrt(1.0f + slope * slope), radius + halfHeight * slope);
        fit.nodeY = cameraY - (minimum[1] + maximum[1]) * 0.5f;
        fit.ok = true;
        return fit;
    }
}
