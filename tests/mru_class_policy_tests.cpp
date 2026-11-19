// Tests for the classLabel=mru rules (include/mru_class_policy.h): the
// [MruClass] key parse and defaults, the menu slot/mode mapping, and the
// gameplay rules (pod drop, service tick, deploy hold).

#include "mru_class_policy.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::MruClassPolicy;

    bool Near(float a, float b)
    {
        return std::fabs(a - b) <= 1e-5f;
    }

    void TestDefaultsMatchTheResearchTable()
    {
        const Config c;
        Check(Near(c.serviceRadius, 0.0f), "serviceRadius defaults to 0 (no service)");
        Check(Near(c.serviceInterval, 1.0f), "serviceInterval defaults to 1 s");
        Check(Near(c.repairPerTick, 100.0f), "repairPerTick defaults to 100");
        Check(Near(c.reloadPerTick, 50.0f), "reloadPerTick defaults to 50");
        Check(Near(c.ammoPerRepair, 1.0f) && Near(c.ammoPerReload, 1.0f), "gauge cost per point defaults to 1");
        Check(!c.serviceSelf, "serviceSelf defaults to off");
        Check(c.serviceDeployed, "serviceDeployed defaults to on");
        Check(Near(c.podCooldown, 30.0f), "podCooldown defaults to 30 s");
        Check(c.repairPodClass[0] == 0 && c.ammoPodClass[0] == 0, "pod classes default to unset");
        Check(Near(c.ammoPerRepairPod, 0.0f) && Near(c.ammoPerAmmoPod, 0.0f), "pod cost defaults to free");
    }

    void TestKeyNamesAreTheOdfKeys()
    {
        Check(std::strcmp(KeyName(kKeyServiceRadius), "serviceRadius") == 0, "first key");
        Check(std::strcmp(KeyName(kKeyPodCooldown), "podCooldown") == 0, "podCooldown key");
        Check(std::strcmp(KeyName(kKeyAmmoPerAmmoPod), "ammoPerAmmoPod") == 0, "last key");
        Check(KeyName(kKeyCount)[0] == 0 && KeyName(-1)[0] == 0, "out of range is empty");
        for (int i = 0; i < kKeyCount; ++i)
            Check(KeyName(i)[0] != 0, "every key has a name");
    }

    void TestMissingSectionIsAbsentWithDefaults()
    {
        const RawKeys raw;
        const ParseResult r = ParseConfig(raw);
        Check(!r.sectionPresent, "no key: section absent");
        Check(Near(r.config.podCooldown, 30.0f) && Near(r.config.serviceRadius, 0.0f), "no key: defaults");
        RawKeys empty;
        empty.values[kKeyServiceRadius] = "";
        Check(!ParseConfig(empty).sectionPresent, "an empty value does not make the section present");
    }

    void TestFullSectionParses()
    {
        RawKeys raw;
        raw.values[kKeyServiceRadius] = "60.0";
        raw.values[kKeyServiceInterval] = "2";
        raw.values[kKeyRepairPerTick] = "150";
        raw.values[kKeyReloadPerTick] = "25.5";
        raw.values[kKeyAmmoPerRepair] = "0";
        raw.values[kKeyAmmoPerReload] = "0.5";
        raw.values[kKeyServiceSelf] = "1";
        raw.values[kKeyServiceDeployed] = "0";
        raw.values[kKeyPodCooldown] = "12";
        raw.values[kKeyRepairPodClass] = "\"repamine\"";
        raw.values[kKeyAmmoPodClass] = "ammomine";
        raw.values[kKeyAmmoPerRepairPod] = "40";
        raw.values[kKeyAmmoPerAmmoPod] = "20";
        const ParseResult r = ParseConfig(raw);
        const Config& c = r.config;
        Check(r.sectionPresent, "section present");
        Check(Near(c.serviceRadius, 60.0f), "serviceRadius");
        Check(Near(c.serviceInterval, 2.0f), "serviceInterval");
        Check(Near(c.repairPerTick, 150.0f), "repairPerTick");
        Check(Near(c.reloadPerTick, 25.5f), "reloadPerTick");
        Check(Near(c.ammoPerRepair, 0.0f), "ammoPerRepair 0 = free");
        Check(Near(c.ammoPerReload, 0.5f), "ammoPerReload");
        Check(c.serviceSelf, "serviceSelf");
        Check(!c.serviceDeployed, "serviceDeployed");
        Check(Near(c.podCooldown, 12.0f), "podCooldown");
        Check(std::strcmp(c.repairPodClass, "repamine") == 0, "repairPodClass, quotes stripped");
        Check(std::strcmp(c.ammoPodClass, "ammomine") == 0, "ammoPodClass, no quotes");
        Check(Near(c.ammoPerRepairPod, 40.0f) && Near(c.ammoPerAmmoPod, 20.0f), "pod costs");
        Check(!r.repairPodNameTooLong && !r.ammoPodNameTooLong, "names fit");
    }

    void TestOneKeyMakesTheSectionPresent()
    {
        RawKeys raw;
        raw.values[kKeyPodCooldown] = "30";
        const ParseResult r = ParseConfig(raw);
        Check(r.sectionPresent, "one key: section present");
        Check(Near(r.config.repairPerTick, 100.0f), "other keys keep defaults");
    }

    void TestBadValuesFallBack()
    {
        RawKeys raw;
        raw.values[kKeyServiceRadius] = "-5";
        raw.values[kKeyServiceInterval] = "0";
        raw.values[kKeyRepairPerTick] = "abc";
        raw.values[kKeyReloadPerTick] = "nan";
        raw.values[kKeyPodCooldown] = "-1";
        raw.values[kKeyServiceSelf] = "yes";
        raw.values[kKeyRepairPodClass] = "averyveryverylongname";
        const ParseResult r = ParseConfig(raw);
        const Config& c = r.config;
        Check(Near(c.serviceRadius, 0.0f), "negative radius falls back to 0");
        Check(Near(c.serviceInterval, kMinServiceInterval), "interval is floored");
        Check(Near(c.repairPerTick, 100.0f), "non-number keeps the default");
        Check(Near(c.reloadPerTick, 50.0f), "nan keeps the default");
        Check(Near(c.podCooldown, 30.0f), "negative cooldown falls back");
        Check(!c.serviceSelf, "non-integer bool keeps the default");
        Check(r.repairPodNameTooLong && c.repairPodClass[0] == 0, "too long a pod name is dropped");
    }

    void TestMenuMapping()
    {
        Check(kMenuEntryCount == 3, "three entries");
        Check(kMenuEntries[0].slot == 7 && kMenuEntries[0].mode == 0xB &&
                  kMenuEntries[0].action == Action::DropRepair,
              "slot 7 Drop Repair on Go To Geyser's id");
        Check(kMenuEntries[1].slot == 8 && kMenuEntries[1].mode == 0xF &&
                  kMenuEntries[1].action == Action::DropAmmo,
              "slot 8 Drop Ammo on Lay Mines' id");
        Check(kMenuEntries[2].slot == 9 && kMenuEntries[2].mode == 0x4 &&
                  kMenuEntries[2].action == Action::Deploy,
              "slot 9 Deploy on Drop Off's id");
        // Never a submenu id (10 Go To Nav, 0xE Attack, 0x11 Defend), never
        // an id the stock hover fill shows (1, 2, 10, 0xE, 7, 5, 6, 8, and
        // Cloak/Decloak 0x18/0x19), and drawable (< 0x1B).
        const int forbidden[] = { 0, 1, 2, 5, 6, 7, 8, 10, 0xE, 0x11, 0x18, 0x19 };
        for (int i = 0; i < kMenuEntryCount; ++i)
        {
            Check(kMenuEntries[i].mode < 0x1B, "label drawable");
            for (int f : forbidden)
                Check(kMenuEntries[i].mode != f, "not a stock hover or submenu id");
        }
        Check(ActionForMode(0xB) == Action::DropRepair, "0xB -> Drop Repair");
        Check(ActionForMode(0xF) == Action::DropAmmo, "0xF -> Drop Ammo");
        Check(ActionForMode(4) == Action::Deploy, "4 -> Deploy");
        Check(ActionForMode(2) == Action::None && ActionForMode(0) == Action::None, "stock ids -> None");
        Check(std::strcmp(ActionName(Action::Deploy), "Deploy") == 0, "action name");
    }

    void TestUnitOffersAction()
    {
        // The stock hover fill, then the MRU fill of slots 7-9.
        int32_t modes[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 0xB, 0xF, 4, 8 };
        uint32_t enabled = 0x7FFu;
        Check(UnitOffersAction(modes, enabled, 0xB), "Drop Repair offered");
        Check(UnitOffersAction(modes, enabled, 0xF), "Drop Ammo offered");
        Check(UnitOffersAction(modes, enabled, 4), "Deploy offered");
        Check(!UnitOffersAction(modes, enabled, 2), "a stock id is not an MRU action");
        Check(!UnitOffersAction(modes, enabled & ~(1u << 8), 0xF), "disabled slot is not offered");
        // A Minelayer has Lay Mines (0xF) in slot 3: not the MRU slot.
        int32_t minelayer[kModeSlots] = { 1, 2, 10, 0xF, 7, 5, 6, 0, 0, 0, 8 };
        Check(!UnitOffersAction(minelayer, enabled, 0xF), "Lay Mines in slot 3 is not Drop Ammo");
        // A Howitzer has Drop Off (4) in slot 7: not the MRU Deploy slot.
        int32_t howitzer[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 4, 0, 0, 8 };
        Check(!UnitOffersAction(howitzer, enabled, 4), "Howitzer Drop Off is not Deploy");
    }

    Config PodConfig()
    {
        Config c;
        ParseName("aprepa", c.repairPodClass);
        ParseName("apammo", c.ammoPodClass);
        c.ammoPerRepairPod = 40.0f;
        c.ammoPerAmmoPod = 19.5f;
        return c;
    }

    void TestPodRules()
    {
        const Config c = PodConfig();
        Check(std::strcmp(PodClass(c, Action::DropRepair), "aprepa") == 0, "repair pod class");
        Check(std::strcmp(PodClass(c, Action::DropAmmo), "apammo") == 0, "ammo pod class");
        Check(PodClass(c, Action::Deploy)[0] == 0, "deploy has no pod");
        Check(PodCost(c, Action::DropRepair) == 40, "repair pod cost");
        Check(PodCost(c, Action::DropAmmo) == 20, "fractional cost rounds up");
        Check(PodCost(Config(), Action::DropAmmo) == 0, "default cost is free");

        Check(CanDrop(c, Action::DropRepair, 0.0f, 40, false), "ready, gauge exact");
        Check(!CanDrop(c, Action::DropRepair, 0.0f, 39, false), "gauge short");
        Check(!CanDrop(c, Action::DropRepair, 0.5f, 400, false), "cooldown running");
        Check(!CanDrop(c, Action::DropRepair, 0.0f, 400, true), "pod class not found");
        Check(!CanDrop(Config(), Action::DropRepair, 0.0f, 400, false), "no pod configured");
        Check(!CanDrop(c, Action::Deploy, 0.0f, 400, false), "deploy is not a drop");
        Check(CanDrop(Config(), Action::DropAmmo, 0.0f, 0, false) == false, "empty name never drops");
        Config freePod = PodConfig();
        freePod.ammoPerAmmoPod = 0.0f;
        Check(CanDrop(freePod, Action::DropAmmo, 0.0f, 0, false), "free pod drops on an empty gauge");

        Check(WhyNoDrop(c, Action::DropRepair, 1.0f, 0, true) == DropBlock::PodNotFound,
              "a missing pod class is reported before the cooldown");
        Check(WhyNoDrop(c, Action::DropRepair, 1.0f, 0, false) == DropBlock::Cooldown, "cooldown reason");
        Check(WhyNoDrop(c, Action::DropRepair, 0.0f, 0, false) == DropBlock::Gauge, "gauge reason");
        Check(WhyNoDrop(Config(), Action::DropRepair, 0.0f, 0, false) == DropBlock::NoPodClass,
              "no pod reason");
        Check(std::strcmp(DropBlockName(DropBlock::Cooldown), "cooldown") == 0, "reason name");

        int32_t modes[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 0xB, 0xF, 4, 8 };
        Check(EntryInItsSlot(modes, 0xB) && EntryInItsSlot(modes, 0xF) && EntryInItsSlot(modes, 4),
              "entries in their slots, enabled or not");
        int32_t minelayer[kModeSlots] = { 1, 2, 10, 0xF, 7, 5, 6, 0, 0, 0, 8 };
        Check(!EntryInItsSlot(minelayer, 0xF), "Lay Mines elsewhere is not the MRU entry");
        Check(!EntryInItsSlot(modes, 2), "stock id is never an MRU entry");

        Check(Near(TickCooldown(30.0f, 0.5f), 29.5f), "cooldown ticks down");
        Check(Near(TickCooldown(0.2f, 0.5f), 0.0f), "cooldown floors at 0");
        Check(Near(TickCooldown(3.0f, -1.0f), 3.0f), "negative dt ignored");
    }

    void TestServiceRules()
    {
        Config c;
        Check(!ServiceActive(c, true), "radius 0: no service");
        c.serviceRadius = 50.0f;
        Check(ServiceActive(c, true), "deployed: service");
        Check(!ServiceActive(c, false), "undeployed with serviceDeployed: none");
        c.serviceDeployed = false;
        Check(ServiceActive(c, false), "serviceDeployed 0: service while moving");

        float acc = 0.0f;
        Check(!ConsumeTick(acc, 0.5f, 1.0f), "half an interval: no tick");
        Check(ConsumeTick(acc, 0.6f, 1.0f), "past the interval: tick");
        Check(Near(acc, 0.1f), "remainder kept");
        acc = 0.0f;
        Check(ConsumeTick(acc, 10.0f, 1.0f), "long frame: one tick");
        Check(Near(acc, 1.0f), "long frame remainder capped at one interval");
        Check(ConsumeTick(acc, 0.0f, 1.0f), "capped remainder yields one more tick");
        Check(!ConsumeTick(acc, 0.0f, 1.0f), "then none");

        Check(Near(RepairGrant(100.0f, 0.0f, 0.0f), 100.0f), "free repair ignores the gauge");
        Check(Near(RepairGrant(100.0f, 1.0f, 30.0f), 30.0f), "gauge caps the grant");
        Check(Near(RepairGrant(100.0f, 0.5f, 500.0f), 100.0f), "per-tick caps the grant");
        Check(Near(RepairGrant(100.0f, 1.0f, 0.0f), 0.0f), "empty gauge: nothing");
        Check(Near(RepairGrant(0.0f, 1.0f, 50.0f), 0.0f), "perTick 0: nothing");
        Check(ReloadGrant(50.0f, 2.0f, 41.0f) == 20, "reload grant is whole ammo");
        Check(ReloadGrant(50.0f, 2.0f, 1.0f) == 0, "under one ammo: nothing");
        Check(ReloadGrant(25.5f, 0.0f, 0.0f) == 25, "free reload floors");

        float carry = 0.0f;
        Check(TakeDrain(carry, 0.5f, 1.0f, 100) == 0 && Near(carry, 0.5f), "fraction carried");
        Check(TakeDrain(carry, 0.7f, 1.0f, 100) == 1 && Near(carry, 0.2f), "whole point drained");
        carry = 0.0f;
        Check(TakeDrain(carry, 100.0f, 1.0f, 30) == 30 && Near(carry, 0.0f),
              "drain capped at the gauge, excess dropped");
        carry = 0.0f;
        Check(TakeDrain(carry, 100.0f, 0.0f, 30) == 0 && Near(carry, 0.0f), "free service drains nothing");
        carry = 5.0f;
        Check(TakeDrain(carry, 0.0f, 1.0f, 0) == 0 && Near(carry, 0.0f), "empty gauge clears the carry");
    }

    void TestDeployRules()
    {
        bool saw = false;
        Check(KeepsDeploy(kWhatNone, 3, saw) && !saw, "Stop not landed yet: keep");
        Check(KeepsDeploy(kWhatNone, kWhatStop, saw) && saw, "current idle: keep, seen");
        Check(!KeepsDeploy(kWhatNone, 3, saw), "current moves after idle: pack");
        saw = false;
        Check(!KeepsDeploy(3, kWhatStop, saw), "Go pending: pack");
        Check(!KeepsDeploy(4, kWhatNone, saw), "Attack pending: pack");
        saw = false;
        Check(KeepsDeploy(kWhatSelect, kWhatSelect, saw), "select: keep");
    }

    void TestTargetRules()
    {
        Check(IsServiceClassId(1) && IsServiceClassId(6), "helicopter and vehicle");
        Check(!IsServiceClassId(2) && !IsServiceClassId(3) && !IsServiceClassId(4) &&
                  !IsServiceClassId(10),
              "structures, powerups and pilots are not serviced");
        Check(IsFriendlyTeam(1, 1, false), "same team");
        Check(IsFriendlyTeam(1, 2, true), "ally");
        Check(!IsFriendlyTeam(1, 2, false), "enemy");
        Check(!IsFriendlyTeam(1, 0, true), "neutral never");
        Check(!IsFriendlyTeam(0, 0, false), "team 0 MRU never");
        Check(InRadius(30.0, 0.0, 40.0, 50.0f), "on the radius");
        Check(!InRadius(30.0, 0.1, 40.0, 50.0f), "just outside");
        Check(!InRadius(0.0, 0.0, 0.0, 0.0f), "radius 0 never");

        const double posit[3] = { 100.0, 10.0, -50.0 };
        const float front[3] = { 0.0f, 0.0f, 1.0f };
        double out[3] = {};
        DropPosition(posit, front, kPodDropBackOffset, out);
        Check(out[0] == 100.0 && out[1] == 10.0 && out[2] == -56.0, "pod drops behind the MRU");
    }
}

int main()
{
    TestDefaultsMatchTheResearchTable();
    TestKeyNamesAreTheOdfKeys();
    TestMissingSectionIsAbsentWithDefaults();
    TestFullSectionParses();
    TestOneKeyMakesTheSectionPresent();
    TestBadValuesFallBack();
    TestMenuMapping();
    TestUnitOffersAction();
    TestPodRules();
    TestServiceRules();
    TestDeployRules();
    TestTargetRules();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("mru_class_policy_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
