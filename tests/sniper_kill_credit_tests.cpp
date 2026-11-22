#include "sniper_kill_credit.h"

#include <cstdint>
#include <cstring>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::SniperKillCredit;

    Inputs CreditCase()
    {
        Inputs in;
        in.victimLocal = true;
        in.netGame = true;
        in.readOk = true;
        in.haveShooter = true;
        in.recordFlags = 0;
        return in;
    }

    void TestRemoteVictimIsStock()
    {
        // Remote victims are credited by the victim owner's receive handler.
        Inputs in = CreditCase();
        in.victimLocal = false;
        CHECK(Decide(in) == Decision::Stock);
        in.netGame = false;
        CHECK(Decide(in) == Decision::Stock);
    }

    void TestSinglePlayerUnchanged()
    {
        Inputs in = CreditCase();
        in.netGame = false;
        CHECK(Decide(in) == Decision::NotNetGame);
        // Single player stays a no-op even when the reads would have failed.
        in.readOk = false;
        CHECK(Decide(in) == Decision::NotNetGame);
    }

    void TestLocalVictimCredited()
    {
        CHECK(Decide(CreditCase()) == Decision::Credit);
        // Other record bits do not block the credit.
        Inputs in = CreditCase();
        in.recordFlags = 0x1u | 0x2u | 0x200u;
        CHECK(Decide(in) == Decision::Credit);
    }

    void TestAlreadyRecordedNotDoubled()
    {
        Inputs in = CreditCase();
        in.recordFlags = kDeathRecordedFlag;
        CHECK(Decide(in) == Decision::AlreadyRecorded);
        in.recordFlags = kDeathRecordedFlag | 0x1u;
        CHECK(Decide(in) == Decision::AlreadyRecorded);
    }

    void TestNoShooterOrUnreadableFailsClosed()
    {
        Inputs in = CreditCase();
        in.haveShooter = false;
        CHECK(Decide(in) == Decision::NoShooter);
        in = CreditCase();
        in.readOk = false;
        CHECK(Decide(in) == Decision::Unreadable);
        // Unreadable wins over a shooter flag that could not be trusted.
        in.haveShooter = false;
        CHECK(Decide(in) == Decision::Unreadable);
    }

    void TestSecondHitOnSameRecord()
    {
        // The credit sets flag 4; a later hit on the same record is refused.
        Inputs in = CreditCase();
        CHECK(Decide(in) == Decision::Credit);
        in.recordFlags |= kDeathRecordedFlag;
        CHECK(Decide(in) == Decision::AlreadyRecorded);
    }

    void TestLayoutConstants()
    {
        CHECK(kDistributedObjectOffset == 0x18u);
        CHECK(kShellOwnerObjOffset == 0xD8u);
        CHECK(kObjGameObjectOffset == 0x8Cu);
        CHECK(kDoVtblGetTeam == 0x04u);
        CHECK(kDoVtblGetRecord == 0x30u);
        CHECK(kRecordFlagsOffset == 0x14u);
        CHECK(kDeathRecordedFlag == 0x4u);
        CHECK(kSnipeKillType == 0x53);
    }

    void TestDecisionNames()
    {
        CHECK(std::strcmp(DecisionName(Decision::Credit), "credit") == 0);
        CHECK(std::strcmp(DecisionName(Decision::AlreadyRecorded), "already-recorded") == 0);
        CHECK(std::strcmp(DecisionName(Decision::Stock), "stock") == 0);
        CHECK(std::strcmp(DecisionName(Decision::NotNetGame), "not-net-game") == 0);
        CHECK(std::strcmp(DecisionName(Decision::NoShooter), "no-shooter") == 0);
        CHECK(std::strcmp(DecisionName(Decision::Unreadable), "unreadable") == 0);
    }
}

int main()
{
    TestRemoteVictimIsStock();
    TestSinglePlayerUnchanged();
    TestLocalVictimCredited();
    TestAlreadyRecordedNotDoubled();
    TestNoShooterOrUnreadableFailsClosed();
    TestSecondHitOnSameRecord();
    TestLayoutConstants();
    TestDecisionNames();
    return OpenShimTest::ExitCode();
}
