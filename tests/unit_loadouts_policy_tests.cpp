// UnitLoadouts' engine-independent logic: the cost-caller split, the
// surcharge gate and sum, the stock fallback rules, the refund of the frozen
// quote, the edit lock, the swap gate, the weapon page layout and the labels.
#include "unit_loadouts_policy.h"
#include "test_check.h"

#include <cstring>

using namespace BZROpenShim::UnitLoadoutsPolicy;
using OpenShimTest::Check;

namespace
{
    constexpr uint32_t kStartRet = 0x005AECDF;
    constexpr uint32_t kRefundRet = 0x005AEDC5;

    void CallerTests()
    {
        Check(ClassifyCaller(kStartRet, kStartRet, kRefundRet) == CostCaller::StartBuild, "StartBuild return is the charge");
        Check(ClassifyCaller(kRefundRet, kStartRet, kRefundRet) == CostCaller::Refund, "refund return is the refund");
        Check(ClassifyCaller(0x004A0D00, kStartRet, kRefundRet) == CostCaller::Other, "render caller is other");
        Check(ClassifyCaller(0, 0, 0) == CostCaller::Other, "unbound rows never match a zero return");
    }

    void GateTests()
    {
        Check(SurchargeApplies(true, true, true, true), "all gates open: surcharge");
        Check(!SurchargeApplies(false, true, true, true), "inactive: no surcharge");
        Check(!SurchargeApplies(true, false, true, true), "network game: no surcharge");
        Check(!SurchargeApplies(true, true, false, true), "AI team: no surcharge");
        Check(!SurchargeApplies(true, true, true, false), "no loadout: no surcharge");
    }

    void FallbackTests()
    {
        Check(ResolveChoice(false, true, true, true) == ChoiceVerdict::Stock, "nothing chosen: stock");
        Check(ResolveChoice(true, false, false, false) == ChoiceVerdict::NoArmory, "no Armory: stock");
        Check(ResolveChoice(true, true, false, true) == ChoiceVerdict::NotOffered, "not offered: stock");
        Check(ResolveChoice(true, true, true, false) == ChoiceVerdict::WrongCategory, "wrong hardpoint type: stock");
        Check(ResolveChoice(true, true, true, true) == ChoiceVerdict::Chosen, "offered and fits: chosen");
        Check(std::strcmp(VerdictName(ChoiceVerdict::NoArmory), "stock (no Armory)") == 0, "verdict name");
    }

    void SurchargeTests()
    {
        const ChoiceVerdict v[kMaxSlots] = {ChoiceVerdict::Chosen, ChoiceVerdict::Stock, ChoiceVerdict::Chosen,
                                            ChoiceVerdict::NotOffered, ChoiceVerdict::NoArmory};
        const int prices[kMaxSlots] = {15, 99, 20, 40, 50};
        Check(Surcharge(v, prices, kMaxSlots) == 35, "full price of each chosen slot only");
        const ChoiceVerdict none[kMaxSlots] = {};
        Check(Surcharge(none, prices, kMaxSlots) == 0, "all stock: no surcharge");
        const int negative[kMaxSlots] = {-5, 0, 10, 0, 0};
        Check(Surcharge(v, negative, kMaxSlots) == 10, "a negative price counts as 0");
        const int huge[kMaxSlots] = {0x7FFFFFFF, 0, 0x7FFFFFFF, 0, 0};
        Check(Surcharge(v, huge, kMaxSlots) == kMaxSurcharge, "sum is capped");
        Check(Surcharge(v, prices, 1) == 15, "count limits the slots read");
        Check(QuotedCost(40, 35) == 75, "base plus surcharge");
        Check(QuotedCost(40, 0) == 40, "no surcharge: base");
        Check(QuotedCost(40, -3) == 40, "negative surcharge ignored");
        Check(QuotedCost(0x7FFFFFF0, 0x100) == 0x7FFFFFFF, "quote saturates");
    }

    void RefundTests()
    {
        Check(RefundSurcharge(true, 0x1000, 0x1000, 0x1000, 25) == 25, "refund of the frozen build returns its surcharge");
        Check(RefundSurcharge(false, 0x1000, 0x1000, 0x1000, 25) == 0, "no frozen quote: base only");
        Check(RefundSurcharge(true, 0x2000, 0x1000, 0x1000, 25) == 0, "quote for another class: base only");
        Check(RefundSurcharge(true, 0x1000, 0x1000, 0x2000, 25) == 0, "producer builds another class: base only");
        Check(RefundSurcharge(true, 0, 0, 0, 25) == 0, "empty quote: base only");
        Check(RefundSurcharge(true, 0x1000, 0x1000, 0x1000, -1) == 0, "negative surcharge never refunds");
    }

    void LockTests()
    {
        const uint32_t building[3] = {0x1000, 0, 0x3000};
        Check(EditLocked(0x1000, building, 3), "a producer builds this unit: locked");
        Check(EditLocked(0x3000, building, 3), "any producer building it locks");
        Check(!EditLocked(0x2000, building, 3), "other units stay editable");
        Check(!EditLocked(0, building, 3), "null class never locks");
        Check(!EditLocked(0x1000, building, 0), "no producers: unlocked");
    }

    void SwapTests()
    {
        Check(PlanSwap(true, true, 2, true, true) == SwapVerdict::Swap, "all checks pass: swap");
        Check(PlanSwap(false, true, 2, true, true) == SwapVerdict::NoQuote, "no frozen quote: no swap");
        Check(PlanSwap(true, false, 2, true, true) == SwapVerdict::NotChosen, "stock slot: no swap");
        Check(PlanSwap(true, true, 5, true, true) == SwapVerdict::SlotOutOfRange, "slot 5 rejected");
        Check(PlanSwap(true, true, -1, true, true) == SwapVerdict::SlotOutOfRange, "slot -1 rejected");
        Check(PlanSwap(true, true, 0, false, true) == SwapVerdict::NotStock, "slot changed since build: no swap");
        Check(PlanSwap(true, true, 0, true, false) == SwapVerdict::HardpointDiffers, "hardpoint type differs: no swap");
    }

    void CreditTests()
    {
        const ChoiceVerdict v[kMaxSlots] = { ChoiceVerdict::Chosen, ChoiceVerdict::Stock, ChoiceVerdict::Chosen,
                                             ChoiceVerdict::NotOffered, ChoiceVerdict::Chosen };
        const int prices[kMaxSlots] = { 10, 99, 20, 99, 30 };
        const bool allFitted[kMaxSlots] = { true, false, true, false, true };
        const bool oneMissed[kMaxSlots] = { true, false, false, false, true };
        const bool noneFitted[kMaxSlots] = {};
        Check(UnfittedCredit(true, 60, v, prices, allFitted, kMaxSlots) == 0, "everything fitted: no credit");
        Check(UnfittedCredit(true, 60, v, prices, oneMissed, kMaxSlots) == 20, "one chosen slot missed: its price");
        Check(UnfittedCredit(true, 60, v, prices, noneFitted, kMaxSlots) == 60, "nothing fitted: chosen prices only");
        Check(UnfittedCredit(false, 60, v, prices, allFitted, kMaxSlots) == 60, "another class built: whole surcharge");
        Check(UnfittedCredit(true, 0, v, prices, noneFitted, kMaxSlots) == 0, "no surcharge paid: no credit");
        Check(UnfittedCredit(false, -5, v, prices, noneFitted, kMaxSlots) == 0, "negative surcharge: no credit");
        Check(UnfittedCredit(true, 15, v, prices, noneFitted, kMaxSlots) == 15, "credit capped at the surcharge paid");
    }

    void PageTests()
    {
        PageLayout p = LayoutPage(0, 0);
        Check(p.count == 0 && !p.more, "empty page");
        p = LayoutPage(5, 0);
        Check(p.first == 0 && p.count == 5 && !p.more, "five entries fit");
        p = LayoutPage(kPagePositions, 0);
        Check(p.count == kPagePositions && !p.more, "exactly eight fit without More");
        p = LayoutPage(9, 0);
        Check(p.first == 0 && p.count == 7 && p.more && p.nextOffset == 7, "nine: seven and More");
        p = LayoutPage(9, 7);
        Check(p.first == 7 && p.count == 2 && p.more && p.nextOffset == 0, "second page wraps");
        p = LayoutPage(9, 20);
        Check(p.first == 0 && p.count == 7, "stale offset resets");
        p = LayoutPage(9, 8);
        Check(p.first == 7, "offset snaps to the page start");
        p = LayoutPage(15, 7);
        Check(p.first == 7 && p.count == 7 && p.nextOffset == 14, "middle page");
        p = LayoutPage(15, 14);
        Check(p.first == 14 && p.count == 1 && p.nextOffset == 0, "last page");
    }

    void LabelTests()
    {
        char out[kLabelChars];
        Check(FormatSlotLabel(0, "AT-Stabber", false, out, sizeof(out)) && std::strcmp(out, "1: AT-Stabber") == 0,
              "slot label");
        Check(FormatSlotLabel(3, "Minigun", true, out, sizeof(out)) && std::strcmp(out, "4: Minigun*") == 0,
              "changed slot label");
        Check(FormatSlotLabel(1, "", false, out, sizeof(out)) && std::strcmp(out, "2: ?") == 0, "unnamed weapon");
        Check(!FormatSlotLabel(5, "X", false, out, sizeof(out)), "slot out of range");
        Check(FormatSlotLabel(0, "A-very-long-weapon-name-beyond-thirty-one", false, out, sizeof(out)) &&
                  std::strlen(out) == kLabelChars - 1,
              "label truncates to the stub buffer");
        Check(FormatChoiceLabel("Stock", true, out, sizeof(out)) && std::strcmp(out, "Stock*") == 0, "current choice");
        Check(FormatChoiceLabel("Hornet", false, out, sizeof(out)) && std::strcmp(out, "Hornet") == 0, "choice");
        Check(!FormatChoiceLabel("", false, out, sizeof(out)), "empty choice refused");
    }

    void OdfTests()
    {
        Check(SameWeaponOdf("gminigun", "GMINIGUN"), "case-insensitive");
        Check(SameWeaponOdf("gatstab", "gatstab"), "equal");
        Check(!SameWeaponOdf("gatstab", "gatstab2"), "prefix differs in length");
        Check(SameWeaponOdf("gminigunX", "gminigunY"), "only eight characters compare");
        Check(!SameWeaponOdf("", ""), "empty never matches");
        Check(!SameWeaponOdf(nullptr, "a"), "null never matches");
    }
}

int main()
{
    CallerTests();
    GateTests();
    FallbackTests();
    SurchargeTests();
    RefundTests();
    LockTests();
    SwapTests();
    CreditTests();
    PageTests();
    LabelTests();
    OdfTests();
    return OpenShimTest::ExitCode();
}
