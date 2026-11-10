// Imported-technique scheme prune policy tests. Pure logic: no engine, no game.
// Also runs the pruner over the checked-in Enhanced stock base.

#include "script_scheme_prune.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim::SchemePrune;

namespace
{
    // Just enough of Ogre's ScriptLexer for these scripts: words, brackets,
    // colons, quotes, one newline token per run of newlines, `//` comments.
    std::vector<std::string> g_Store;

    std::vector<Token> Lex(const std::string& s)
    {
        g_Store.clear();
        g_Store.reserve(s.size());
        std::vector<std::pair<uint32_t, size_t>> raw;
        for (size_t i = 0; i < s.size();)
        {
            const char c = s[i];
            if (c == '/' && i + 1 < s.size() && s[i + 1] == '/')
            {
                while (i < s.size() && s[i] != '\n')
                    ++i;
                continue;
            }
            if (c == '\n' || c == '\r')
            {
                if (raw.empty() || raw.back().first != kTidNewline)
                {
                    g_Store.emplace_back("\n");
                    raw.push_back({ kTidNewline, g_Store.size() - 1 });
                }
                ++i;
                continue;
            }
            if (c == ' ' || c == '\t')
            {
                ++i;
                continue;
            }
            if (c == '{' || c == '}' || c == ':')
            {
                g_Store.emplace_back(1, c);
                raw.push_back({ c == '{' ? kTidLBracket : c == '}' ? kTidRBracket : kTidColon, g_Store.size() - 1 });
                ++i;
                continue;
            }
            size_t j = i;
            uint32_t type = kTidWord;
            if (c == '"')
            {
                type = kTidQuote;
                j = s.find('"', i + 1) + 1;
            }
            else
                while (j < s.size() && !std::strchr(" \t\r\n{}:", s[j]))
                    ++j;
            g_Store.emplace_back(s.substr(i, j - i));
            raw.push_back({ type, g_Store.size() - 1 });
            i = j;
        }
        std::vector<Token> out;
        for (auto& r : raw)
            out.push_back({ r.first, g_Store[r.second] });
        return out;
    }

    std::vector<std::string> SurvivingSchemes(const std::string& script, uint32_t tiers, uint32_t families = 0)
    {
        const std::vector<Token> tokens = Lex(script);
        std::vector<bool> dead(tokens.size(), false);
        for (const Range& r : PrunableTechniques(tokens.data(), tokens.size(), tiers, families))
            for (size_t i = r.first; i <= r.last; ++i)
                dead[i] = true;
        std::vector<std::string> out;
        for (size_t i = 0; i + 1 < tokens.size(); ++i)
            if (!dead[i] && tokens[i].type == kTidWord && tokens[i].lexeme == "scheme")
                out.emplace_back(tokens[i + 1].lexeme);
        return out;
    }

    std::string Join(const std::vector<std::string>& v)
    {
        std::string s;
        for (auto& x : v)
            s += (s.empty() ? "" : ",") + x;
        return s;
    }

    const char* kBase = R"(
abstract pass P
{
}
material Base
{
    lod_values 250 300
    technique
    {
        scheme high-pssm
        pass : P
        {
        }
    }
    technique
    {
        scheme medium
        pass : P {}
    }
    technique
    {
        scheme en-lowest-noshadow
    }
    technique
    {
        scheme low-noshadow
    }
    technique { scheme glow }
    technique
    {
        pass : P {}
    }
}
)";
}

void TestTierBits()
{
    std::printf("TestTierBits\n");
    Check(TierBit("high") == kTierHigh, "high");
    Check(TierBit("high-pssm") == kTierHigh, "high-pssm");
    Check(TierBit("en-medium-noshadow") == kTierMedium, "en- medium");
    Check(TierBit("og-lowest") == kTierLowest, "og- lowest");
    Check(TierBit("low-pssm") == kTierLow, "low");
    Check(TierBit("glow") == 0, "glow has no tier");
    Check(TierBit("Default") == 0, "Default");
    Check(TierBit("high-detail") == 0, "unknown suffix is a custom scheme");
    Check(TierBit("highest") == 0, "not a tier");
    Check(TierBitFromEngineScheme("low-noshadow") == 0, "secondary viewport scheme is not the player's tier");
    Check(TierBitFromEngineScheme("high-pssm") == kTierHigh, "player tier");
}

void TestKeep()
{
    std::printf("TestKeep\n");
    Check(KeepScheme("medium", 0, 0), "nothing seen keeps all");
    Check(KeepScheme("en-high-noshadow", kTierHigh, 0), "every shadow mode and family of the tier");
    Check(!KeepScheme("medium-pssm", kTierHigh, 0), "other tier");
    Check(KeepScheme("low-noshadow", kTierHigh, 0), "secondary viewport scheme");
    Check(KeepScheme("en-low-noshadow", kTierHigh, 0), "secondary viewport scheme, Enhanced");
    Check(!KeepScheme("low-pssm", kTierHigh, 0), "other low modes");
    Check(KeepScheme("glow", kTierHigh, 0), "glow");
    Check(KeepScheme("medium", kTierHigh | kTierMedium, 0), "a later tier joins");

    const uint32_t en = kFamilyEnhanced;
    Check(KeepScheme("en-high-noshadow", kTierHigh, en), "every shadow mode of the seen family");
    Check(KeepScheme("en-high", kTierHigh, en), "shadows-off mode of the seen family");
    Check(!KeepScheme("high-pssm", kTierHigh, en), "unseen plain family");
    Check(!KeepScheme("og-high-pssm", kTierHigh, en), "unseen og- family");
    Check(KeepScheme("en-low-noshadow", kTierHigh, en), "secondary viewport, seen family");
    Check(!KeepScheme("low-noshadow", kTierHigh, en), "secondary viewport, unseen family");
    Check(KeepScheme("glow", kTierHigh, en), "untiered ignores family");
    Check(KeepScheme("high-pssm", kTierHigh, en | kFamilyPlain), "a later family joins");
    Check(FamilyBit("en-high") == kFamilyEnhanced && FamilyBit("og-low") == kFamilyRetro &&
              FamilyBit("high-pssm") == kFamilyPlain && FamilyBit("en-") == kFamilyPlain,
          "family bits");
}

void TestPruneScript()
{
    std::printf("TestPruneScript\n");
    Check(Join(SurvivingSchemes(kBase, kTierHigh)) == "high-pssm,low-noshadow,glow", "high");
    Check(Join(SurvivingSchemes(kBase, kTierMedium)) == "medium,low-noshadow,glow", "medium");
    Check(Join(SurvivingSchemes(kBase, 0)) ==
              "high-pssm,medium,en-lowest-noshadow,low-noshadow,glow", "unknown tier keeps all");
    Check(Join(SurvivingSchemes(kBase, kTierHigh, kFamilyPlain)) == "high-pssm,low-noshadow,glow", "plain family");
    // low-noshadow has no en- twin here, so it stays.
    Check(Join(SurvivingSchemes(kBase, kTierLowest, kFamilyEnhanced)) == "en-lowest-noshadow,low-noshadow,glow",
          "en- family drops only twinned plain");
}

void TestKeepsWhatItCannotProve()
{
    std::printf("TestKeepsWhatItCannotProve\n");
    Check(Join(SurvivingSchemes("material M\n{\n technique T\n {\n scheme medium\n }\n}\n", kTierHigh)) == "medium",
          "named technique kept (a child may override it)");
    Check(Join(SurvivingSchemes("material M\n{\n technique : B\n {\n scheme medium\n }\n}\n", kTierHigh)) == "medium",
          "inherited technique kept");
    Check(Join(SurvivingSchemes("abstract technique\n{\n scheme medium\n}\n", kTierHigh)) == "medium",
          "top level / abstract kept");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n scheme medium\n }\n technique\n {\n scheme lowest\n }\n}\n",
                                kTierHigh)) == "medium,lowest",
          "an object never loses every technique");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n scheme medium\n }\n", kTierHigh)) == "medium",
          "unbalanced file untouched");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n scheme \"medium\"\n }\n technique\n {\n scheme high\n }\n}\n",
                                kTierHigh)) == "high",
          "quoted scheme");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n scheme high-pssm\n }\n technique\n {\n scheme glow\n }\n}\n",
                                kTierHigh, kFamilyEnhanced)) == "high-pssm,glow",
          "plain technique without an en- twin survives the en- family");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n scheme high-pssm\n }\n technique\n {\n scheme en-high-pssm\n }\n}\n",
                                kTierHigh, kFamilyEnhanced)) == "en-high-pssm",
          "plain technique with an en- twin goes");
    Check(Join(SurvivingSchemes("material M\n{\n technique\n {\n pass\n {\n scheme medium\n }\n }\n technique\n {\n scheme high\n }\n}\n",
                                kTierHigh)) == "medium,high",
          "scheme below the technique body is not the technique's");
    Check(SurvivingSchemes("", kTierHigh).empty() && PrunableTechniques(nullptr, 0, kTierHigh, 0).empty(), "empty input");
}

void TestCheckedInStockBase()
{
    std::printf("TestCheckedInStockBase\n");
    std::ifstream in(OPENSHIM_ENHANCED_PAYLOAD_DIR "/openshim_stock_bzbase.import", std::ios::binary);
    Check(in.good(), "payload readable");
    std::stringstream ss;
    ss << in.rdbuf();
    const std::vector<std::string> all = SurvivingSchemes(ss.str(), 0);
    const std::vector<std::string> high = SurvivingSchemes(ss.str(), kTierHigh);
    const std::vector<std::string> enHighOnly = SurvivingSchemes(ss.str(), kTierHigh, kFamilyEnhanced);
    std::printf("  en- family on high keeps %zu\n", enHighOnly.size());
    bool enPssm = false, enNoshadow = false, enPlain = false;
    size_t foreign = 0;
    for (auto& s : enHighOnly)
    {
        enPssm |= s == "en-high-pssm";
        enNoshadow |= s == "en-high-noshadow";
        enPlain |= s == "en-high";
        foreign += TierBit(s) != 0 && FamilyBit(s) != kFamilyEnhanced;
    }
    // BZBaseDebug has only plain `high` techniques (3 lods), kept so it is never empty.
    Check(enPssm && enNoshadow && enPlain && foreign == 3, "en- high keeps all three en- shadow modes, no other family");
    Check(enHighOnly.size() < high.size(), "family prune drops more");
    std::printf("  %zu techniques, %zu kept on high\n", all.size(), high.size());
    Check(all.size() >= 90, "the base has its ~100 techniques");
    Check(high.size() * 2 < all.size(), "high drops more than half");
    bool glow = false, secondary = false, enHigh = false, other = false;
    for (auto& s : high)
    {
        glow |= s == "glow";
        secondary |= s == "low-noshadow";
        enHigh |= s == "en-high-pssm";
        other |= TierBit(s) != 0 && TierBit(s) != kTierHigh && StripFamily(s) != "low-noshadow";
    }
    Check(glow && secondary && enHigh && !other, "keeps glow, low-noshadow, en-high; nothing else tiered");

    // The Enhanced base shader scales the emissive map by the pass emissive, so a pass without
    // `emissive 1 1 1` renders its emissive map black.
    const std::string text = ss.str();
    const std::string marker = "abstract pass OSEPassScheme";
    size_t blocks = 0;
    for (size_t at = text.find(marker); at != std::string::npos; at = text.find(marker, at + 1))
    {
        size_t end = std::min(text.find("abstract pass ", at + 1), text.find("\nmaterial ", at + 1));
        const std::string block = text.substr(at, end == std::string::npos ? std::string::npos : end - at);
        bool hasEmissive = false;
        std::istringstream lines(block);
        for (std::string line; std::getline(lines, line);)
        {
            const size_t s = line.find_first_not_of(" \t");
            hasEmissive |= s != std::string::npos && line.compare(s, 14, "emissive 1 1 1") == 0;
        }
        Check(hasEmissive, "every OSEPassScheme pass declares emissive 1 1 1");
        ++blocks;
    }
    Check(blocks >= 13, "found the OSEPassScheme passes");
}

int main()
{
    TestTierBits();
    TestKeep();
    TestPruneScript();
    TestKeepsWhatItCannotProve();
    TestCheckedInStockBase();

    if (OpenShimTest::FailureCount() != 0)
    {
        std::printf("\nscript_scheme_prune_tests FAILED (%d)\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("\nscript_scheme_prune_tests passed\n");
    return 0;
}
