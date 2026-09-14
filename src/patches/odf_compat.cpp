// odf_compat.cpp
// BZR Open Shim - ODF legacy-section compatibility core (portable layer).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "odf_compat.h"

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
namespace OdfCompat
{
namespace
{

char ToLowerAscii(char c)
{
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
}

bool EqualsLower(std::string_view a, std::string_view b)
{
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (ToLowerAscii(a[i]) != ToLowerAscii(b[i]))
            return false;
    }
    return true;
}

// Every section the 1.5/Redux loaders read (lowercase), plus the family roots
// and every other section spelling observed in the retail GOG StockODFFiles
// corpus (2026-09-14 census, 127 spellings). Anything outside this set is
// reported as unknown. Zero-key loader classes are included so their (empty)
// sections never log.
const char* const kKnownSections[] = {
    "ammopowerupclass", "anchorrocketclass", "apcclass", "animbuildingclass",
    "armoryclass", "artifactclass", "barracksclass", "beam", "beamclass",
    "beamgunclass", "boltclass", "bouncebombclass", "builder", "buildingclass",
    "bulletclass", "camerapodclass", "cannonclass", "chargegunclass", "chunk",
    "chunkeffect", "cloud", "cloudemit", "cloudl", "cloudr", "commtowerclass",
    "constructionblob", "constructionrigclass", "core", "craftclass",
    "daywreckerclass", "dispenserclass", "dmgvhcl1", "dmgvhcl2", "dmgvhcl3",
    "dmgvhcl4", "dust", "dusteffect", "engineflame", "enginesplash", "explosion",
    "explosionclass", "explosioncore", "factoryclass", "fireballeffect", "flame",
    "flamecenter", "flameemitter", "flamepuffclass", "flare", "flare1", "flare2",
    "flare3", "flare4", "flareemit1", "flareemit2", "flareemit3", "flareemit4",
    "flaremineclass", "fringe1", "fringe2", "gameobject", "gameobjectclass",
    "gas", "geizerclass", "geyserclass", "grenadeclass", "groundblastclass",
    "healthpowerupclass", "hovercraftclass", "howitzerclass", "imagelauncherclass",
    "imagemissileclass", "imagerefractclass", "launcherclass", "leaderroundclass",
    "light", "light1", "light2", "light3", "light4", "lightemit1", "lightemit2",
    "lightemit3", "lightemit4", "lightemitter", "machinegunclass", "magnetmineclass",
    "mineclass", "minelayerclass", "missileclass", "mortarclass", "objectlobberclass",
    "ordnanceclass", "particleeffect", "personclass", "planarexplosionclass",
    "popperclass", "poppergunclass", "portalblob", "portalclass", "powerplantclass",
    "powerupclass", "producerclass", "prodsmok", "proximitymineclass", "puff",
    "quakeblastclass", "radardamperclass", "radarlauncherclass", "recyclerclass",
    "remotedetonatorclass", "render", "repairdepotclass", "rocketclass", "savclass",
    "scavengerclass", "scorch", "scrapclass", "scrapdropoffclass", "scrapfieldclass",
    "scrapsiloclass", "seismicwaveclass", "shieldtowerclass", "shockblastclass",
    "smoke", "smoke2", "smokecenter", "smokeeffect", "smokeemit", "smokeemitter",
    "snipergunclass", "snipershellclass", "spawnbuoyclass", "specialitemclass",
    "spark", "sparkemitter", "spraybombclass", "spraybuildingclass", "steam1",
    "steam2", "supplydepotclass", "targetinggunclass", "teamswitcherclass",
    "terrainexposeclass", "thermallauncherclass", "thermalmissileclass",
    "torpedoclass", "tracerclass", "trail", "tugclass", "turretcraftclass",
    "turrettankclass", "walkerclass", "weaponclass", "weaponmineclass",
    "weaponpowerupclass", "wingmanclass",
};

struct LegacyMapEntry
{
    const char* legacy;
    const char* canonical;
};

// Headers the 1.5 fallback tolerated and Redux drops (BZ1_Source
// research/odf_loader_schema.json dead_sections_and_keys). [Explosion] is
// deliberately absent: it is the live dispatch root (classLabel), and
// renaming it would break Find dispatch.
const LegacyMapEntry kLegacyMap[] = {
    {"flarebuildingclass", "FlareMineClass"},
    {"gameobject", "GameObjectClass"},
    {"magnetclass", "MagnetMineClass"},
    {"scavengercraftclass", "ScavengerClass"},
    {"spraybomb", "SprayBombClass"},
    {"spraybuildngclass", "SprayBuildingClass"},
};

struct GuardRule
{
    const char* section; // lowercase canonical section
    const char* key; // lowercase key
    const char* canonicalKey; // key spelling used in reports
};

// (section, key) pairs whose ODF values crash verified engine paths.
const GuardRule kGuardRules[] = {
    {"magnetmineclass", "fieldradius", "fieldRadius"},
    {"chargegunclass", "ordnancecount", "ordnanceCount"},
    {"launcherclass", "targetcount", "targetCount"},
};

bool IsSpaceTab(char c)
{
    return c == ' ' || c == '\t';
}

// Locale-independent ASCII number scan over [first, last). Returns true when
// a full floating value was consumed; out receives it. Accepts forms like
// 0, -12, 3.5, .5, 1e30, -2E-3. Rejects hex, nan/inf spellings, and empties.
bool ParseAsciiDouble(const char* first, const char* last, double& out)
{
    const char* p = first;
    bool neg = false;
    if (p != last && (*p == '+' || *p == '-'))
    {
        neg = (*p == '-');
        ++p;
    }
    double intPart = 0.0;
    bool anyDigits = false;
    while (p != last && *p >= '0' && *p <= '9')
    {
        anyDigits = true;
        intPart = intPart * 10.0 + (*p - '0');
        ++p;
    }
    double frac = 0.0;
    double fracScale = 1.0;
    if (p != last && *p == '.')
    {
        ++p;
        while (p != last && *p >= '0' && *p <= '9')
        {
            anyDigits = true;
            frac = frac * 10.0 + (*p - '0');
            fracScale *= 10.0;
            ++p;
        }
    }
    if (!anyDigits)
        return false;
    double value = intPart + frac / fracScale;
    if (p != last && (*p == 'e' || *p == 'E'))
    {
        const char* e = p + 1;
        bool eNeg = false;
        if (e != last && (*e == '+' || *e == '-'))
        {
            eNeg = (*e == '-');
            ++e;
        }
        int exp = 0;
        bool anyExp = false;
        while (e != last && *e >= '0' && *e <= '9')
        {
            anyExp = true;
            exp = exp * 10 + (*e - '0');
            ++e;
        }
        if (!anyExp)
            return false;
        double mult = 1.0;
        for (int i = 0; i < exp; ++i)
            mult *= 10.0;
        value = eNeg ? value / mult : value * mult;
        p = e;
    }
    if (p != last)
        return false;
    out = neg ? -value : value;
    return std::isfinite(out);
}

std::string LowerOf(std::string_view v)
{
    std::string out;
    out.reserve(v.size());
    for (char c : v)
        out.push_back(ToLowerAscii(c));
    return out;
}

} // namespace

bool IsOdfFileName(const char* name)
{
    if (!name)
        return false;
    size_t len = std::strlen(name);
    if (len < 5)
        return false;
    return ToLowerAscii(name[len - 4]) == '.' && ToLowerAscii(name[len - 3]) == 'o' &&
           ToLowerAscii(name[len - 2]) == 'd' && ToLowerAscii(name[len - 1]) == 'f';
}

bool IsKnownSection(std::string_view name)
{
    for (const char* known : kKnownSections)
    {
        if (EqualsLower(name, known))
            return true;
    }
    return false;
}

const char* CanonicalSectionFor(std::string_view name)
{
    for (const LegacyMapEntry& e : kLegacyMap)
    {
        if (EqualsLower(name, e.legacy))
            return e.canonical;
    }
    return nullptr;
}

ProcessResult ProcessOdfText(const char* fileName, const char* data, size_t size, const Options& opt)
{
    ProcessResult result;
    const std::string file = fileName ? fileName : "";
    if (!data || size == 0)
    {
        result.text.assign(data ? data : "", size);
        return result;
    }

    std::string out;
    out.reserve(size + 64);

    std::string currentSection; // lowercase, canonicalized when remapped
    std::string currentCanonical; // canonical spelling for reports
    bool sectionHasPayloadName = false;
    bool sectionPayloadChecked = false;
    int payloadCheckLine = 0;
    std::vector<std::pair<std::string, int>> seenUnknown; // (lowername, line) for dedup

    auto flushPayloadCheck = [&](int endLine) {
        (void)endLine;
        if (sectionPayloadChecked || !opt.guardCrashValues)
        {
            sectionPayloadChecked = true;
            return;
        }
        sectionPayloadChecked = true;
        if ((currentSection == "flaremineclass" || currentSection == "spraybuildingclass") &&
            !sectionHasPayloadName)
        {
            ValueEvent ev;
            ev.file = file;
            ev.line = payloadCheckLine;
            ev.section = currentCanonical;
            ev.key = "payloadName";
            ev.value = "";
            ev.action = "missing payloadName (Redux: NULL payload reference, crash when fired)";
            result.guards.push_back(ev);
        }
    };

    size_t pos = 0;
    int lineNo = 0;
    while (pos < size)
    {
        size_t lineEnd = pos;
        while (lineEnd < size && data[lineEnd] != '\n' && data[lineEnd] != '\r')
            ++lineEnd;
        size_t eolEnd = lineEnd;
        if (eolEnd < size && data[eolEnd] == '\r')
            ++eolEnd;
        if (eolEnd < size && data[eolEnd] == '\n')
            ++eolEnd;
        ++lineNo;

        std::string_view line(data + pos, lineEnd - pos);
        std::string_view eol(data + lineEnd, eolEnd - lineEnd);

        // Find first non-blank.
        size_t i = 0;
        while (i < line.size() && IsSpaceTab(line[i]))
            ++i;

        bool isHeader = (i < line.size() && line[i] == '[');
        if (isHeader)
        {
            flushPayloadCheck(lineNo);
            size_t nameBegin = i + 1;
            size_t nameEnd = nameBegin;
            while (nameEnd < line.size() && line[nameEnd] != ']')
                ++nameEnd;
            // Trim trailing blanks inside the brackets.
            size_t trimEnd = nameEnd;
            while (trimEnd > nameBegin && IsSpaceTab(line[trimEnd - 1]))
                --trimEnd;
            std::string_view rawName(line.data() + nameBegin, trimEnd - nameBegin);
            std::string lower = LowerOf(rawName);

            const char* canonical = CanonicalSectionFor(lower);
            if (canonical && opt.remapLegacySections)
            {
                SectionEvent ev;
                ev.file = file;
                ev.line = lineNo;
                ev.name = std::string(rawName);
                ev.mappedTo = canonical;
                result.remaps.push_back(ev);
                // Rebuild: prefix + canonical + suffix (suffix keeps a
                // missing ']' exactly as-is; lexical defects are tolerated
                // by both engines and must not be "fixed" here).
                out.append(line.substr(0, nameBegin));
                out.append(canonical);
                out.append(line.substr(trimEnd));
                currentSection = LowerOf(canonical);
                currentCanonical = canonical;
                result.changed = true;
            }
            else
            {
                out.append(line);
                if (!IsKnownSection(lower))
                {
                    bool seen = false;
                    for (const auto& s : seenUnknown)
                    {
                        if (s.first == lower)
                        {
                            seen = true;
                            break;
                        }
                    }
                    if (!seen)
                    {
                        seenUnknown.emplace_back(lower, lineNo);
                        if (opt.logUnknownSections)
                        {
                            SectionEvent ev;
                            ev.file = file;
                            ev.line = lineNo;
                            ev.name = std::string(rawName);
                            result.unknowns.push_back(ev);
                        }
                    }
                }
                currentSection = lower;
                currentCanonical = std::string(rawName);
            }
            sectionHasPayloadName = false;
            sectionPayloadChecked = false;
            payloadCheckLine = lineNo;
            out.append(eol);
            pos = eolEnd;
            continue;
        }

        // Key line handling for crash-value guards (and payloadName watch).
        bool lineRewritten = false;
        if (opt.guardCrashValues && !currentSection.empty())
        {
            // key = value  (key: [A-Za-z0-9_]+)
            size_t k = i;
            size_t kEnd = k;
            while (kEnd < line.size() &&
                   (std::isalnum(static_cast<unsigned char>(line[kEnd])) || line[kEnd] == '_'))
                ++kEnd;
            if (kEnd > k)
            {
                size_t e = kEnd;
                while (e < line.size() && IsSpaceTab(line[e]))
                    ++e;
                if (e < line.size() && line[e] == '=')
                {
                    std::string keyLower = LowerOf(std::string_view(line.data() + k, kEnd - k));
                    if (keyLower == "payloadname")
                        sectionHasPayloadName = true;
                    // value token (skip blanks; allow one pair of quotes)
                    size_t v = e + 1;
                    while (v < line.size() && IsSpaceTab(line[v]))
                        ++v;
                    bool quoted = (v < line.size() && (line[v] == '"' || line[v] == '\''));
                    size_t vTok = quoted ? v + 1 : v;
                    size_t vEnd = vTok;
                    while (vEnd < line.size() && !IsSpaceTab(line[vEnd]) && line[vEnd] != '"' &&
                           line[vEnd] != '\'')
                        ++vEnd;
                    std::string_view token(line.data() + vTok, vEnd - vTok);
                    for (const GuardRule& rule : kGuardRules)
                    {
                        if (currentSection == rule.section && keyLower == rule.key)
                        {
                            double number = 0.0;
                            if (ParseAsciiDouble(token.data(), token.data() + token.size(), number))
                            {
                                const char* replacement = nullptr;
                                char repBuf[16];
                                if (keyLower == "fieldradius")
                                {
                                    if (number == 0.0 || !std::isfinite(number))
                                        replacement = "20.0";
                                }
                                else
                                {
                                    if (number < 0.0)
                                    {
                                        std::snprintf(repBuf, sizeof(repBuf), "0");
                                        replacement = repBuf;
                                    }
                                }
                                if (replacement)
                                {
                                    ValueEvent ev;
                                    ev.file = file;
                                    ev.line = lineNo;
                                    ev.section = currentCanonical;
                                    ev.key = std::string(line.data() + k, kEnd - k);
                                    ev.value = std::string(token);
                                    ev.action = std::string("clamped to ") + replacement +
                                                " (verified engine crash input)";
                                    result.guards.push_back(ev);
                                    out.append(line.substr(0, vTok));
                                    out.append(replacement);
                                    out.append(line.substr(vEnd));
                                    result.changed = true;
                                    lineRewritten = true;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (!lineRewritten)
            out.append(line);
        out.append(eol);
        pos = eolEnd;
    }
    flushPayloadCheck(lineNo + 1);

    result.text = std::move(out);
    return result;
}

} // namespace OdfCompat
} // namespace BZROpenShim
