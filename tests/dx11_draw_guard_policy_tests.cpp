// DX11 draw-time shaderless guard bookkeeping tests. Pure logic: no engine,
// no game. Covers include/dx11_draw_guard_policy.h.

#include "dx11_draw_guard_policy.h"

#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim::RenderProfiles::Dx11Compat;

namespace
{
    DrawGuardKey Key(uint64_t handle, uint32_t stateCount)
    {
        DrawGuardKey key;
        key.handle = handle;
        key.stateCount = stateCount;
        return key;
    }
}

void TestSkipDecision()
{
    std::printf("TestSkipDecision\n");
    Check(!DrawGuardShouldSkip(true, true), "both programs draw");
    Check(DrawGuardShouldSkip(false, true), "missing vertex program skips");
    Check(DrawGuardShouldSkip(true, false), "missing fragment program skips");
    Check(DrawGuardShouldSkip(false, false), "fixed-function pass skips");

    Check(std::strcmp(DrawGuardMissingPrograms(false, false), "vs+ps") == 0, "both missing");
    Check(std::strcmp(DrawGuardMissingPrograms(false, true), "vs") == 0, "vs missing");
    Check(std::strcmp(DrawGuardMissingPrograms(true, false), "ps") == 0, "ps missing");
    Check(std::strcmp(DrawGuardMissingPrograms(true, true), "none") == 0, "none missing");
}

void TestOncePerKey()
{
    std::printf("TestOncePerKey\n");
    DrawGuardLedger ledger;
    const DrawGuardDecision first = ledger.NoteSkip(Key(7, 3));
    Check(first.isNew && first.log && !first.logCapReached, "first skip is new and logged");
    for (int i = 0; i < 100; ++i)
    {
        const DrawGuardDecision again = ledger.NoteSkip(Key(7, 3));
        Check(!again.isNew && !again.log && !again.logCapReached, "repeat skip is silent");
    }
    Check(ledger.TrackedKeys() == 1, "one key tracked");
    Check(ledger.LogLines() == 1, "one line logged");
    Check(ledger.SkippedDraws() == 101, "every skipped draw counted");
    Check(ledger.IsKnown(Key(7, 3)), "key is known");
}

void TestReloadIsNewKey()
{
    std::printf("TestReloadIsNewKey\n");
    DrawGuardLedger ledger;
    Check(ledger.NoteSkip(Key(7, 3)).isNew, "original load");
    // Same material reloaded in place: state count moves on.
    Check(ledger.NoteSkip(Key(7, 4)).isNew, "reload is a fresh attempt");
    // Removed and re-parsed: Ogre hands out a new handle.
    Check(ledger.NoteSkip(Key(8, 1)).isNew, "re-parse is a fresh attempt");
    // A handle above 32 bits must not alias a small one.
    Check(ledger.NoteSkip(Key(7ull | (1ull << 40), 3)).isNew, "64-bit handle kept whole");
    Check(!ledger.NoteSkip(Key(7, 4)).isNew, "reloaded key still once only");
    Check(ledger.TrackedKeys() == 4, "four distinct keys");
}

void TestLogCap()
{
    std::printf("TestLogCap\n");
    DrawGuardLedger ledger(100, 3);
    int logged = 0;
    int notices = 0;
    int fresh = 0;
    for (uint64_t handle = 1; handle <= 10; ++handle)
    {
        const DrawGuardDecision d = ledger.NoteSkip(Key(handle, 1));
        logged += d.log ? 1 : 0;
        notices += d.logCapReached ? 1 : 0;
        fresh += d.isNew ? 1 : 0;
    }
    Check(logged == 3, "log lines capped");
    Check(notices == 1, "one cap notice");
    Check(fresh == 10, "keys past the log cap still get their one attempt");
    Check(ledger.LogLines() == 3, "ledger reports the cap");
}

void TestKeyCap()
{
    std::printf("TestKeyCap\n");
    DrawGuardLedger ledger(4, 64);
    for (uint64_t handle = 1; handle <= 4; ++handle)
        Check(ledger.NoteSkip(Key(handle, 1)).isNew, "within key cap");
    const DrawGuardDecision overflow = ledger.NoteSkip(Key(99, 1));
    Check(!overflow.isNew && !overflow.log, "past key cap: no attempt, no line");
    Check(overflow.logCapReached, "past key cap: one notice");
    const DrawGuardDecision overflowAgain = ledger.NoteSkip(Key(100, 1));
    Check(!overflowAgain.isNew && !overflowAgain.log && !overflowAgain.logCapReached,
          "notice only once");
    Check(ledger.TrackedKeys() == 4, "table bounded");
    Check(ledger.UntrackedDraws() == 2, "overflow draws counted");
    Check(!ledger.NoteSkip(Key(1, 1)).isNew, "known key stays known");
}

void TestKeyCapAfterLogCapNoticeOnce()
{
    std::printf("TestKeyCapAfterLogCapNoticeOnce\n");
    DrawGuardLedger ledger(2, 1);
    int notices = 0;
    for (uint64_t handle = 1; handle <= 5; ++handle)
        notices += ledger.NoteSkip(Key(handle, 1)).logCapReached ? 1 : 0;
    Check(notices == 1, "log cap and key cap share one notice");
}

void TestTransientRetry()
{
    std::printf("TestTransientRetry\n");
    Check(DrawGuardShouldRetry("renderer-resources-unavailable", 1), "resources not ready: retry");
    Check(DrawGuardShouldRetry("abi-unavailable", 1), "abi not ready: retry");
    Check(!DrawGuardShouldRetry("renderer-resources-unavailable",
                                kDrawGuardMaxTransientAttempts),
          "retry budget is bounded");
    Check(DrawGuardShouldRetry("renderer-resources-unavailable",
                               kDrawGuardMaxTransientAttempts - 1),
          "last retry still allowed");
    Check(!DrawGuardShouldRetry("compat-disabled", 1), "config decline is final");
    Check(!DrawGuardShouldRetry("material-gone-or-reloaded", 1), "gone is final");
    Check(!DrawGuardShouldRetry("no-fully-shaderless-technique", 1), "policy decline is final");
}

int main()
{
    TestTransientRetry();
    TestSkipDecision();
    TestOncePerKey();
    TestReloadIsNewKey();
    TestLogCap();
    TestKeyCap();
    TestKeyCapAfterLogCapNoticeOnce();
    return OpenShimTest::ExitCode();
}
