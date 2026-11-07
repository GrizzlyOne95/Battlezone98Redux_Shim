// script_scheme_prune.h
// BZR Open Shim - which imported techniques a material parse may skip
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Every material that imports a base (BZBase, CR_BZBase, ...) clones all of
// the base's techniques: one per quality tier x shadow mode x family (plain,
// en-, og-) x lod, about 100 for BZBase. Only one tier is ever drawn, so the
// MP game room's 2077-material rebuild spent most of its 20-30 s cloning
// techniques nobody renders. The import detour in ogre_script_import_cache.cpp
// therefore turns the tokens of an imported technique whose scheme names a
// tier the engine never set into newline tokens (which the parser skips)
// before the import is parsed. Pure policy, unit tested.
//
// Kept: every scheme without a tier token (glow, Default, custom), and in
// each family (plain, en-, og-) the engine has drawn with, every shadow mode
// of a tier it has set plus low-noshadow, which it hard-codes for secondary
// viewports. A tier or family picked later only reaches materials parsed
// after it; ResolveBaseSchemeTechnique (ogre_render_profile.cpp) serves
// already loaded ones the same scheme from a family that was kept, or the
// same shadow mode from a tier that was kept. An unseen family's technique is
// pruned only when the object has the same scheme in a seen family.

#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace BZROpenShim::SchemePrune
{
    // Kill switch: =1 parses every imported technique.
    constexpr const char* kDisableSwitch = "OPENSHIM_DISABLE_SCHEME_PRUNE";

    // The engine creates its secondary viewports with this scheme whatever the
    // quality setting, so it never counts as the player's tier and is always kept.
    constexpr std::string_view kSecondaryViewportScheme = "low-noshadow";

    constexpr uint32_t kTierHigh = 1u << 0;
    constexpr uint32_t kTierMedium = 1u << 1;
    constexpr uint32_t kTierLow = 1u << 2;
    constexpr uint32_t kTierLowest = 1u << 3;

    // Ogre 1.10 ScriptLexer token ids (OgreScriptLexer.h).
    constexpr uint32_t kTidLBracket = 0;
    constexpr uint32_t kTidRBracket = 1;
    constexpr uint32_t kTidColon = 2;
    constexpr uint32_t kTidWord = 4;
    constexpr uint32_t kTidQuote = 5;
    constexpr uint32_t kTidNewline = 6;
    constexpr uint32_t kTidEnd = 8;

    inline std::string_view StripFamily(std::string_view scheme)
    {
        if (scheme.size() > 3 && (scheme.substr(0, 3) == "en-" || scheme.substr(0, 3) == "og-"))
            scheme.remove_prefix(3);
        return scheme;
    }

    // The tier bit a scheme names (high, high-pssm, en-medium-noshadow ...), or
    // 0 for a scheme without one (glow, Default, a mod's own).
    inline uint32_t TierBit(std::string_view scheme)
    {
        scheme = StripFamily(scheme);
        const std::string_view tier = scheme.substr(0, scheme.find('-'));
        const std::string_view rest = scheme.substr(tier.size());
        if (!(rest.empty() || rest == "-pssm" || rest == "-noshadow"))
            return 0;
        if (tier == "high")
            return kTierHigh;
        if (tier == "medium")
            return kTierMedium;
        if (tier == "low")
            return kTierLow;
        if (tier == "lowest")
            return kTierLowest;
        return 0;
    }

    // What an engine setMaterialScheme call adds to the set of tiers in use.
    inline uint32_t TierBitFromEngineScheme(std::string_view scheme)
    {
        return StripFamily(scheme) == kSecondaryViewportScheme ? 0 : TierBit(scheme);
    }

    // Scheme families: the engine's plain names and our en-/og- prefixes.
    constexpr uint32_t kFamilyPlain = 1u << 0;
    constexpr uint32_t kFamilyEnhanced = 1u << 1;
    constexpr uint32_t kFamilyRetro = 1u << 2;

    inline uint32_t FamilyBit(std::string_view scheme)
    {
        if (scheme.size() > 3 && scheme.substr(0, 3) == "en-")
            return kFamilyEnhanced;
        if (scheme.size() > 3 && scheme.substr(0, 3) == "og-")
            return kFamilyRetro;
        return kFamilyPlain;
    }

    // seenTiers == 0 (no engine scheme yet) keeps everything; seenFamilies == 0
    // keeps every family. Every shadow mode of a kept tier stays: a viewport
    // without shadow setup drawing a -pssm technique renders black on DX11.
    inline bool KeepScheme(std::string_view scheme, uint32_t seenTiers, uint32_t seenFamilies)
    {
        const uint32_t bit = TierBit(scheme);
        if (seenTiers == 0 || bit == 0)
            return true;
        if (seenFamilies != 0 && (FamilyBit(scheme) & seenFamilies) == 0)
            return false;
        return (bit & seenTiers) != 0 || StripFamily(scheme) == kSecondaryViewportScheme;
    }

    struct Token
    {
        uint32_t type = 0;
        std::string_view lexeme;
    };

    struct Range
    {
        size_t first = 0;   // the `technique` word
        size_t last = 0;    // its closing bracket, inclusive
    };

    // Whole `technique { ... }` statements whose scheme the player never
    // draws. A technique with a name, an inheritance colon, `abstract` in front
    // or anything malformed is kept, and so are all of an object's techniques
    // when none of them would survive.
    inline std::vector<Range> PrunableTechniques(const Token* tokens, size_t count, uint32_t seenTiers,
                                                 uint32_t seenFamilies)
    {
        std::vector<Range> out;
        if (seenTiers == 0)
            return out;

        struct Candidate
        {
            Range range;
            size_t parent;
            bool prune;
            std::string_view scheme;
        };
        std::vector<Candidate> found;
        std::vector<size_t> open;   // indices of unmatched `{`

        for (size_t i = 0; i < count; ++i)
        {
            const Token& t = tokens[i];
            if (t.type == kTidLBracket)
            {
                open.push_back(i);
                continue;
            }
            if (t.type == kTidRBracket)
            {
                if (open.empty())
                    return {};   // unbalanced: leave the file alone
                open.pop_back();
                continue;
            }
            if (t.type != kTidWord || t.lexeme != "technique" || open.empty())
                continue;
            // Statement start only: after a newline or a bracket.
            if (i == 0)
                continue;
            const uint32_t before = tokens[i - 1].type;
            if (before != kTidNewline && before != kTidLBracket && before != kTidRBracket)
                continue;

            size_t j = i + 1;
            while (j < count && tokens[j].type == kTidNewline)
                ++j;
            if (j >= count || tokens[j].type != kTidLBracket)
                continue;   // named, inherited or malformed: keep

            // Match the body; read a direct `scheme <value>`.
            size_t depth = 0, end = count;
            std::string_view scheme;
            for (size_t k = j; k < count; ++k)
            {
                if (tokens[k].type == kTidLBracket)
                    ++depth;
                else if (tokens[k].type == kTidRBracket && --depth == 0)
                {
                    end = k;
                    break;
                }
                else if (depth == 1 && tokens[k].type == kTidWord && tokens[k].lexeme == "scheme" &&
                         k + 1 < count && (tokens[k + 1].type == kTidWord || tokens[k + 1].type == kTidQuote))
                    scheme = tokens[k + 1].lexeme;
            }
            if (end == count)
                return {};   // unbalanced
            if (scheme.size() >= 2 && scheme.front() == '"' && scheme.back() == '"')
                scheme = scheme.substr(1, scheme.size() - 2);

            // Tier prune here; the family prune waits until the siblings are known.
            found.push_back({ { i, end }, open.back(), !scheme.empty() && !KeepScheme(scheme, seenTiers, 0), scheme });
            i = end;   // techniques do not nest
        }
        if (!open.empty())
            return {};

        for (size_t a = 0; a < found.size();)
        {
            size_t b = a;
            while (b < found.size() && found[b].parent == found[a].parent)
                ++b;
            // An unseen family's technique goes only when this object has the
            // same scheme in a seen family (en-high-pssm for high-pssm): an
            // object with no twin keeps its plain techniques, so the engine's
            // cross-family fallback still finds them.
            if (seenFamilies != 0)
                for (size_t c = a; c < b; ++c)
                {
                    Candidate& f = found[c];
                    if (f.prune || f.scheme.empty() || KeepScheme(f.scheme, seenTiers, seenFamilies))
                        continue;
                    for (size_t d = a; d < b && !f.prune; ++d)
                        f.prune = d != c && !found[d].prune && !found[d].scheme.empty() &&
                                  StripFamily(found[d].scheme) == StripFamily(f.scheme) &&
                                  KeepScheme(found[d].scheme, seenTiers, seenFamilies);
                }
            bool anyKept = false;
            for (size_t c = a; c < b; ++c)
                anyKept |= !found[c].prune;
            for (size_t c = a; c < b; ++c)
                if (found[c].prune && anyKept)
                    out.push_back(found[c].range);
            a = b;
        }
        return out;
    }
}
