// Pins the kill ticker's verification rules, feed timing, placement and ODF
// name parsing (include/kill_ticker_policy.h).

#include "kill_ticker_policy.h"

#include "test_check.h"

#include <cmath>
#include <cstring>
#include <limits>
#include <string>

using OpenShimTest::Check;
using namespace BZROpenShim::KillTicker;

namespace
{
    KillSample Lethal()
    {
        KillSample s;
        s.victim = 0x1234;
        s.attacker = 0x5678;
        s.before = 0.25f;
        s.after = -0.1f;
        s.sameLifetime = true;
        s.localAttacker = true;
        s.kind = DamageKind::Craft;
        return s;
    }

    void ExactRule()
    {
        Check(ConfirmsKill(Lethal()), "player's killing blow on a live craft counts");
        KillSample s = Lethal();
        s.kind = DamageKind::Building;
        Check(ConfirmsKill(s), "buildings count");
        s.kind = DamageKind::Person;
        Check(ConfirmsKill(s), "pilots count");
        s.kind = DamageKind::Powerup;
        Check(!ConfirmsKill(s), "depleting a powerup is not a kill");

        s = Lethal(); s.localAttacker = false;
        Check(!ConfirmsKill(s), "someone else's killing blow does not count");
        s = Lethal(); s.before = -0.05f;
        Check(!ConfirmsKill(s), "hitting an already-dead object does not steal the kill");
        s = Lethal(); s.after = 0.0f;
        Check(!ConfirmsKill(s), "exactly zero is alive, like the engine's own test");
        s = Lethal(); s.before = 0.0f;
        Check(ConfirmsKill(s), "zero-health victim pushed below zero counts");
        s = Lethal(); s.after = 0.1f;
        Check(!ConfirmsKill(s), "non-lethal hit does not count");
        s = Lethal(); s.sameLifetime = false;
        Check(!ConfirmsKill(s), "a recycled handle never counts");
        s = Lethal(); s.alliedVictim = true;
        Check(!ConfirmsKill(s), "allied and own-team victims are not shown");
        s = Lethal(); s.attacker = s.victim;
        Check(!ConfirmsKill(s), "self damage does not count");
        s = Lethal(); s.victim = 0;
        Check(!ConfirmsKill(s), "unknown victim does not count");
        s = Lethal(); s.after = std::numeric_limits<float>::quiet_NaN();
        Check(!ConfirmsKill(s), "non-finite health fails closed");
        s = Lethal(); s.before = std::numeric_limits<float>::infinity();
        Check(!ConfirmsKill(s), "infinite health fails closed");
    }

    struct FixedProbe
    {
        Probe state;
        Probe operator()(int) const { return state; }
    };

    KillSample RemoteHit(int victim, bool local)
    {
        KillSample s;
        s.victim = victim;
        s.attacker = local ? 7 : 9;
        s.before = 0.6f;
        s.after = 0.6f; // health does not move on a peer that does not own the victim
        s.sameLifetime = true;
        s.localAttacker = local;
        return s;
    }

    void RemoteRule()
    {
        ConfirmedKill out[8];
        RemoteCandidates table;
        table.NoteDamage(RemoteHit(100, true), "svtank", 1000);
        Check(table.Active() == 1, "local hit on a remote victim becomes a candidate");
        Check(table.Resolve(1100, FixedProbe{Probe::Alive}, out, 8) == 0, "alive victim is not credited");
        Check(table.Active() == 1, "alive victim stays pending");
        Check(table.Resolve(1200, FixedProbe{Probe::Dead}, out, 8) == 1, "observed death credits the kill");
        Check(out[0].victim == 100 && std::strcmp(out[0].odf, "svtank") == 0, "credit copies victim and ODF");
        Check(table.Active() == 0, "credited candidate is dropped");

        table.NoteDamage(RemoteHit(101, true), "svfigh", 1000);
        table.NoteDamage(RemoteHit(101, false), "", 1050);
        Check(table.Resolve(1100, FixedProbe{Probe::Dead}, out, 8) == 0, "another attacker's later hit takes the credit");

        table.NoteDamage(RemoteHit(102, true), "svfigh", 1000);
        Check(table.Resolve(1100, FixedProbe{Probe::Gone}, out, 8) == 0, "disappearing is not dying");
        Check(table.Active() == 0, "vanished candidate is dropped");

        table.NoteDamage(RemoteHit(103, true), "svfigh", 1000);
        Check(table.Resolve(1000 + kRemoteWindowMs + 1, FixedProbe{Probe::Dead}, out, 8) == 0,
              "death after the window is not credited");

        KillSample local = RemoteHit(104, true);
        local.after = 0.3f;
        table.NoteDamage(RemoteHit(104, true), "svtank", 1000);
        table.NoteDamage(local, "svtank", 1010);
        Check(table.Active() == 0, "a hit that moves health locally hands the victim to the exact rule");

        table.NoteDamage(RemoteHit(105, true), "svtank", 1000);
        KillSample corpse = RemoteHit(105, false);
        corpse.before = corpse.after = -0.2f;
        table.NoteDamage(corpse, "", 1010);
        Check(table.Resolve(1020, FixedProbe{Probe::Dead}, out, 8) == 1, "hits on the dead replica change nothing");

        table.NoteDamage(RemoteHit(106, false), "", 1000);
        KillSample late = RemoteHit(106, true);
        late.before = late.after = -0.2f;
        table.NoteDamage(late, "svtank", 1010);
        Check(table.Active() == 0, "shooting a corpse earns no credit");

        KillSample ally = RemoteHit(107, true);
        ally.alliedVictim = true;
        table.NoteDamage(ally, "avtank", 1000);
        Check(table.Active() == 0, "allied victims never become candidates");

        table.NoteDamage(RemoteHit(108, true), "svtank", 1000);
        table.Forget(108);
        Check(table.Active() == 0, "exact credit removes the candidate");

        for (int i = 0; i < static_cast<int>(kRemoteCapacity) + 4; ++i)
            table.NoteDamage(RemoteHit(200 + i, true), "svtank", 1000 + static_cast<uint64_t>(i));
        Check(table.Active() == kRemoteCapacity, "table stays bounded");
        Check(table.Resolve(1100, FixedProbe{Probe::Dead}, out, 2) == 2, "resolve honours output capacity");
        Check(table.Active() == kRemoteCapacity - 2, "candidates past capacity wait for the next frame");
        table.Reset();
        Check(table.Active() == 0, "reset clears candidates");
    }

    std::string Text(const Line& line)
    {
        char buffer[64] = {};
        FormatLine(line, buffer, sizeof(buffer));
        return buffer;
    }

    void FeedRules()
    {
        Feed feed;
        feed.Push("Tank", 1000);
        Check(feed.Count() == 1 && Text(feed.At(0)) == "-Tank", "first kill is -Tank");
        feed.Push("tank", 1500);
        Check(feed.Count() == 1 && Text(feed.At(0)) == "-Tank x2", "same type soon after coalesces");
        feed.Push("Scout", 1600);
        Check(feed.Count() == 2 && Text(feed.At(1)) == "-Scout", "a different type gets its own line");
        feed.Push("Tank", 1700);
        Check(feed.Count() == 3, "coalescing only joins the newest line");

        feed.Reset();
        for (int i = 0; i < 6; ++i) feed.Push(i % 2 ? "Scout" : "Tank", 1000);
        Check(feed.Count() == kMaxLines, "at most four lines");
        Check(Text(feed.At(kMaxLines - 1)) == "-Scout", "newest line is kept when full");

        feed.Reset();
        feed.Push("Tank", 1000);
        feed.Expire(1000 + kMaxPendingMs - 1);
        Check(feed.Count() == 1, "an undrawn line waits for the HUD");
        feed.Expire(1000 + kMaxPendingMs);
        Check(feed.Count() == 0, "an undrawn line is eventually dropped");

        feed.Push("Tank", 2000);
        feed.MarkShown(3000);
        Check(Feed::Opacity(feed.At(0), 3000) == 1.0f, "fully opaque when first shown");
        Check(Feed::Opacity(feed.At(0), 3000 + kShowMs - kFadeMs) == 1.0f, "holds until the fade");
        const float mid = Feed::Opacity(feed.At(0), 3000 + kShowMs - kFadeMs / 2);
        Check(mid > 0.4f && mid < 0.6f, "fades linearly");
        feed.Expire(3000 + kShowMs - 1);
        Check(feed.Count() == 1, "visible for the full show time");
        feed.Expire(3000 + kShowMs);
        Check(feed.Count() == 0, "gone after the show time");

        feed.Push("Tank", 10000);
        feed.MarkShown(10000);
        feed.Push("Tank", 10000 + kCoalesceMs);
        Check(feed.Count() == 2, "an old line does not absorb a new kill");

        feed.Reset();
        for (int i = 0; i < 150; ++i) feed.Push("Tank", 1000);
        Check(Text(feed.At(0)) == "-Tank x99", "count is capped");

        feed.Reset();
        feed.Push("", 1000);
        Check(feed.Count() == 0, "empty names are ignored");
        feed.Push(std::string(80, 'A'), 1000);
        Check(std::strlen(feed.At(0).name) == kNameChars, "long names are capped");

        Check(WithOpacity(0x8C000000u, 1.0f) == 0x8C000000u, "full opacity keeps alpha");
        Check(WithOpacity(0xFFFFD27Au, 0.5f) == 0x80FFD27Au, "half opacity halves alpha");
        Check(WithOpacity(0xFFFFD27Au, 0.0f) == 0x00FFD27Au, "zero opacity clears alpha");
    }

    void Placement()
    {
        LineRect r;
        Anchor anchor;
        anchor.valid = true;
        anchor.x = 1600; anchor.y = 860; anchor.w = 300; anchor.h = 200;
        Check(ComputeLine(1920, 1080, anchor, 60.0f, 16.0f, 0, r), "anchored line");
        Check(r.x2 == 1899, "right edge matches the weapon list");
        Check(r.y2 < 860, "sits above the weapon list");
        Check(r.textLeft > r.x1 && r.textLeft + 60 <= r.x2 + 1, "text inside the panel");
        Check(r.textTop > r.y1 && r.textTop + 16 <= r.y2 + 1, "text vertically inside the panel");
        LineRect above;
        Check(ComputeLine(1920, 1080, anchor, 60.0f, 16.0f, 1, above), "second line");
        Check(above.y2 < r.y1, "older lines stack upward without overlap");

        Anchor wrong = anchor;
        wrong.x = 10; wrong.y = 10;
        Check(!PlausibleAnchor(wrong, 1920, 1080), "an upper-left rectangle is not the weapon list");
        Check(ComputeLine(1920, 1080, wrong, 60.0f, 16.0f, 0, r), "implausible anchor uses fallback");
        Check(r.x2 == 1920 - 38 - 1, "fallback hugs the right edge");
        Check(r.y2 == static_cast<int>(std::lround(1080 * kFallbackBottomFraction)) - 1, "fallback bottom");

        Anchor off = anchor;
        off.w = 400;
        Check(!PlausibleAnchor(off, 1920, 1080), "off-screen rectangle is refused");
        Anchor none;
        Check(ComputeLine(1280, 720, none, 50.0f, 14.0f, 0, r), "no anchor uses fallback");

        Check(!ComputeLine(0, 1080, none, 50.0f, 14.0f, 0, r), "zero viewport refused");
        Check(!ComputeLine(1920, 1080, none, 0.0f, 14.0f, 0, r), "zero text width refused");
        Check(!ComputeLine(1920, 1080, none, std::numeric_limits<float>::infinity(), 14.0f, 0, r), "infinite text refused");
        Check(!ComputeLine(1920, 1080, anchor, 60.0f, 16.0f, 200, r), "lines past the top are refused");
    }

    void Names()
    {
        const char* odf =
            "\xEF\xBB\xBF[GameObjectClass]\r\n"
            "geometryName = \"avtank00.xsi\"\r\n"
            "unitName = \"Tank\" // comment\r\n"
            "[CraftClass]\r\n"
            "unitName = \"Wrong\"\r\n";
        Check(ParseUnitName(odf) == "Tank", "unitName from GameObjectClass");

        Check(ParseUnitName("[CraftClass]\nunitName = \"Wrong\"\n[GameObjectClass]\nunitName=Scout\n") == "Scout",
              "section order and unquoted values");
        Check(ParseUnitName("[gameobjectclass]\nUNITNAME = \"Gun Tower\" ; x\n") == "Gun Tower", "case-insensitive keys");
        Check(ParseUnitName("[GameObjectClass]\nunitName = \"A // B\"\n") == "A // B", "comment markers inside quotes stay");
        Check(ParseUnitName("[GameObjectClass]\nunitName = \"\"\n").empty(), "blank name is empty");
        Check(ParseUnitName("[GameObjectClass]\nclassLabel = \"wingman\"\n").empty(), "missing name is empty");
        Check(ParseUnitName("[GameObjectClass]\nunitName = \"  Big\t  Tank  \"\n") == "Big Tank", "whitespace collapses");
        Check(ParseUnitName("[GameObjectClass]\nunitName = \"A\x01" "B\"\n") == "AB", "control bytes dropped");

        Check(DisplayName("Tank", "avtank") == "Tank", "unitName wins");
        Check(DisplayName("", "avtank") == "avtank", "ODF name is the fallback");
        Check(DisplayName("", "").empty(), "nothing to show");
    }
}

int main()
{
    ExactRule();
    RemoteRule();
    FeedRules();
    Placement();
    Names();
    return OpenShimTest::ExitCode();
}
