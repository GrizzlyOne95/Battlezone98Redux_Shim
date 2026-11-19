// Tests for the classLabel=mru rules (include/mru_class_policy.h): the
// [MruClass] key parse and defaults, and the menu probe's slot/mode mapping.

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
    if (OpenShimTest::ExitCode() == 0)
        std::printf("mru_class_policy_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
