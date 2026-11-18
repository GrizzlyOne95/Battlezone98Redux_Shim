#include "rts_commands_policy.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::RtsCommandsPolicy;

namespace
{
    constexpr unsigned kBothSmart = kSmartCommandMenu | kSmartRepairReload;

    ModeList MakeList(const int (&modes)[kModeSlots], uint32_t enabled)
    {
        ModeList list;
        for (int i = 0; i < kModeSlots; ++i)
            list.modes[i] = modes[i];
        list.enabled = enabled;
        list.active = -1;
        return list;
    }

    uint32_t Bits(std::initializer_list<int> slots)
    {
        uint32_t mask = 0;
        for (int s : slots)
            mask |= 1u << s;
        return mask;
    }

    // HoverCraft::UpdateModeList (0x004EBD60) slots, then the class
    // overrides: Wingman (0x00613630) 7 Hunt, 8 Follow Close, 9 Defend;
    // APC (0x00470A90) slot 3 Attack only with ammo; Howitzer (0x004F0FD0)
    // slot 7 Drop Off/deploy while undeployed. Get Repair/Reload are present
    // with the enabled bit set only on a unit that needs it.
    ModeList Wingman(bool needsRepair, bool needsReload)
    {
        const int modes[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 13, 16, 17, 8 };
        uint32_t on = Bits({ 0, 1, 2, 3, 4, 7, 8, 9, 10 });
        if (needsRepair)
            on |= Bits({ 5 });
        if (needsReload)
            on |= Bits({ 6 });
        return MakeList(modes, on);
    }

    ModeList Walker(bool needsRepair, bool needsReload)
    {
        const int modes[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 0, 0, 0, 8 };
        uint32_t on = Bits({ 0, 1, 2, 3, 4, 10 });
        if (needsRepair)
            on |= Bits({ 5 });
        if (needsReload)
            on |= Bits({ 6 });
        return MakeList(modes, on);
    }

    ModeList Apc()
    {
        const int modes[kModeSlots] = { 1, 2, 10, 0, 7, 5, 6, 0, 0, 0, 8 };
        return MakeList(modes, Bits({ 0, 1, 2, 4, 10 }));
    }

    ModeList Howitzer()
    {
        const int modes[kModeSlots] = { 1, 2, 10, 14, 7, 5, 6, 4, 0, 0, 8 };
        return MakeList(modes, Bits({ 0, 1, 2, 3, 4, 7, 10 }));
    }

    void TestStockIntersectMatchesEngine()
    {
        ModeList a = Wingman(false, false);
        const ModeList b = Walker(false, false);
        StockIntersect(a, b);
        Check(a.modes[7] == 0 && a.modes[8] == 0 && a.modes[9] == 0, "stock drops Hunt/Follow Close/Defend");
        Check(a.modes[0] == kModeGoTo && SlotEnabled(a, 0), "stock keeps a shared enabled mode");
        Check(!SlotEnabled(a, 7), "stock ANDs the enabled bits");

        ModeList c = Wingman(false, false);
        ModeList d = Wingman(false, false);
        c.active = 3;
        d.active = 3;
        StockIntersect(c, d);
        Check(c.active == 3, "same active slot naming a mode survives");
        ModeList e = Wingman(false, false);
        ModeList f = Walker(false, false);
        e.active = 7;
        f.active = 7;
        StockIntersect(e, f);
        Check(e.active == -1, "active slot whose mode was dropped is cleared");
        Check(MergeSelection(nullptr, 0, kBothSmart).active == -1, "empty selection: empty list");
    }

    void TestMixedGroupFixture()
    {
        // Ctrl+1 style group: a wingman needing repair, a walker needing
        // reload, an APC and an undeployed howitzer.
        const ModeList units[4] = { Wingman(true, false), Walker(false, true), Apc(), Howitzer() };

        const ModeList stock = MergeSelection(units, 4, 0);
        Check(stock.modes[7] == 0 && stock.modes[8] == 0 && stock.modes[9] == 0,
              "fixture, stock: Hunt, Follow Close and Defend are gone");
        Check(!SlotEnabled(stock, 5) && !SlotEnabled(stock, 6), "fixture, stock: Repair/Reload greyed");

        const ModeList smart = MergeSelection(units, 4, kBothSmart);
        Check(smart.modes[7] == kModeHunt && SlotEnabled(smart, 7), "fixture: Hunt stays");
        Check(smart.modes[8] == kModeFollowClose && SlotEnabled(smart, 8), "fixture: Follow Close (Formation) stays");
        Check(smart.modes[9] == kModeDefend && SlotEnabled(smart, 9), "fixture: Defend stays");
        Check(smart.modes[5] == kModeGetRepair && SlotEnabled(smart, 5), "fixture: Get Repair shown (one needs it)");
        Check(smart.modes[6] == kModeGetReload && SlotEnabled(smart, 6), "fixture: Get Reload shown (one needs it)");
        Check(smart.modes[0] == kModeGoTo && SlotEnabled(smart, 0), "fixture: Go To unchanged");
        Check(smart.modes[3] == 0, "fixture: Attack (APC has none) follows the stock rule");
        Check(smart.modes[10] == 8 && SlotEnabled(smart, 10), "fixture: Recycle unchanged");

        // Smart skip: each order goes only to the units that hold it.
        Check(SendModeToUnit(kModeHunt, units[0], kBothSmart), "Hunt -> wingman");
        Check(!SendModeToUnit(kModeHunt, units[1], kBothSmart), "Hunt skips the walker");
        Check(!SendModeToUnit(kModeHunt, units[2], kBothSmart), "Hunt skips the APC");
        Check(!SendModeToUnit(kModeHunt, units[3], kBothSmart), "Hunt skips the howitzer");
        Check(SendModeToUnit(kModeFollowClose, units[0], kBothSmart), "Follow Close -> wingman");
        Check(!SendModeToUnit(kModeFollowClose, units[3], kBothSmart), "Follow Close skips the howitzer");
        Check(SendModeToUnit(kModeDefend, units[0], kBothSmart), "Defend -> wingman");
        Check(!SendModeToUnit(kModeDefend, units[2], kBothSmart), "Defend skips the APC");
        Check(SendModeToUnit(kModeGetRepair, units[0], kBothSmart), "Repair -> the wingman that needs it");
        Check(!SendModeToUnit(kModeGetRepair, units[1], kBothSmart), "Repair skips the healthy walker");
        Check(!SendModeToUnit(kModeGetReload, units[0], kBothSmart), "Reload skips the full wingman");
        Check(SendModeToUnit(kModeGetReload, units[1], kBothSmart), "Reload -> the walker that needs it");
        Check(SendModeToUnit(kModeGoTo, units[2], kBothSmart), "a non-smart mode goes to everyone (stock)");
    }

    void TestSmartParts()
    {
        const ModeList units[2] = { Wingman(true, false), Walker(false, true) };
        const ModeList menuOnly = MergeSelection(units, 2, kSmartCommandMenu);
        Check(menuOnly.modes[7] == kModeHunt, "menu part alone keeps Hunt");
        Check(!SlotEnabled(menuOnly, 5) && !SlotEnabled(menuOnly, 6), "menu part alone: Repair/Reload stock (AND)");
        Check(SendModeToUnit(kModeGetRepair, units[1], kSmartCommandMenu), "menu part alone: Repair goes to all");

        const ModeList repairOnly = MergeSelection(units, 2, kSmartRepairReload);
        Check(repairOnly.modes[7] == 0, "repair part alone: Hunt stock (dropped)");
        Check(SlotEnabled(repairOnly, 5) && SlotEnabled(repairOnly, 6), "repair part alone: Repair/Reload shown");
        Check(SendModeToUnit(kModeHunt, units[1], kSmartRepairReload), "repair part alone: Hunt goes to all");

        // Same-type selections are exactly stock.
        const ModeList same[3] = { Wingman(false, false), Wingman(false, false), Wingman(false, false) };
        const ModeList s1 = MergeSelection(same, 3, kBothSmart);
        const ModeList s0 = MergeSelection(same, 3, 0);
        bool equal = s1.enabled == s0.enabled && s1.active == s0.active;
        for (int i = 0; i < kModeSlots; ++i)
            equal = equal && s1.modes[i] == s0.modes[i];
        Check(equal, "identical units merge exactly as stock");

        // Two different smart modes in one slot fall back to stock.
        ModeList a = Wingman(false, false);
        ModeList b = Wingman(false, false);
        b.modes[7] = kModeDefend;
        SmartIntersect(a, b, kBothSmart);
        Check(a.modes[7] == 0, "two different smart modes in a slot: stock (dropped)");

        // A smart mode that is disabled on its only holder stays disabled.
        ModeList w = Wingman(false, false);
        ModeList k = Walker(false, false);
        SmartIntersect(w, k, kBothSmart);
        Check(w.modes[5] == kModeGetRepair && !SlotEnabled(w, 5), "nobody needs repair: entry greyed");
        Check(!UnitTakesMode(Walker(false, false), kModeNone), "mode 0 is never taken");
    }

    void TestFamilies()
    {
        Check(ClassifyFamily(".?AVWingman@@") == Family::Combat, "wingman is combat");
        Check(ClassifyFamily(".?AVAPC@@") == Family::Combat, "APC is combat");
        Check(ClassifyFamily(".?AVWalker@@") == Family::Combat, "walker is combat");
        Check(ClassifyFamily(".?AVTurretTank@@") == Family::TurretTank, "turret tank");
        Check(ClassifyFamily(".?AVHowitzer@@") == Family::Howitzer, "howitzer, not turret tank");
        Check(ClassifyFamily(".?AVMinelayer@@") == Family::Minelayer, "minelayer");
        Check(ClassifyFamily(".?AVScavenger@@") == Family::Scavenger, "scavenger");
        Check(ClassifyFamily(".?AVTug@@") == Family::Tug, "tug");
        Check(ClassifyFamily(".?AVConstructionRig@@") == Family::ConstructionRig, "construction rig");
        Check(std::string(FamilyName(Family::ConstructionRig)) == "construction rig", "rig family name");
        Check(ClassifyFamily(".?AVRecycler@@") == Family::None, "recycler has no family");
        Check(ClassifyFamily(".?AVHoverCraft@@") == Family::None, "plain hovercraft has no family");
        Check(ClassifyFamily(nullptr) == Family::None, "null name");

        Check(IsBaseStructure(true, ".?AVPowerPlant@@"), "a Building is a base structure");
        Check(IsBaseStructure(false, ".?AVRecycler@@"), "recycler counts");
        Check(IsBaseStructure(false, ".?AVFactory@@"), "factory counts");
        Check(IsBaseStructure(false, ".?AVArmory@@"), "armory counts");
        Check(!IsBaseStructure(false, ".?AVConstructionRig@@"), "construction rig does not");
        Check(!IsBaseStructure(false, ".?AVWingman@@"), "units do not");
    }

    void TestCycles()
    {
        uint32_t handles[] = { 0x00100005u, 0x00200009u, 0x00300001u, 0x00000007u };
        SortNewestFirst(handles, 4);
        Check(handles[0] == 0x00200009u && handles[1] == 0x00000007u && handles[2] == 0x00100005u &&
                  handles[3] == 0x00300001u,
              "newest first by the low 20-bit sequence");

        const uint32_t list[] = { 11, 22, 33 };
        Check(NextInCycle(list, 3, 0) == 11, "no target: first");
        Check(NextInCycle(list, 3, 99) == 11, "target not in the list: first");
        Check(NextInCycle(list, 3, 11) == 22, "advances");
        Check(NextInCycle(list, 3, 33) == 11, "wraps");
        Check(NextInCycle(list, 1, 11) == 11, "single entry stays");
        Check(NextInCycle(list, 0, 11) == 0, "empty list: 0");
    }

    void TestAreaSelect()
    {
        const float centre[3] = { 0.0f, 50.0f, 0.0f };
        const float near[3] = { 60.0f, -40.0f, 60.0f }; // 84.9 m horizontally; height ignored
        const float far[3] = { 150.0f, 0.0f, 0.0f };
        Check(WithinRadius(centre, near, kAreaRadius), "84.9 m is inside 100 m");
        Check(!WithinRadius(centre, far, kAreaRadius), "150 m is outside 100 m");
        Check(WithinRadius(centre, far, kAreaRadiusWide), "150 m is inside 200 m");
        Check(!WithinRadius(centre, near, 0.0f), "zero radius selects nothing");

        AreaCandidate c[6];
        c[0] = { 1, Family::Combat, { 10, 0, 0 }, true };
        c[1] = { 2, Family::Combat, { 90, 0, 0 }, true };
        c[2] = { 3, Family::Scavenger, { 5, 0, 0 }, true };   // other family
        c[3] = { 4, Family::Combat, { 20, 0, 0 }, false };    // enemy / not commandable
        c[4] = { 5, Family::Combat, { 150, 0, 0 }, true };    // outside 100 m
        c[5] = { 6, Family::Combat, { 30, 0, 0 }, true };     // already selected
        const uint32_t selected[] = { 6 };
        uint32_t out[kSelectCapacity] = {};
        int n = PlanAreaAdd(selected, 1, c, 6, Family::Combat, centre, kAreaRadius, out, kSelectCapacity);
        Check(n == 2 && out[0] == 1 && out[1] == 2, "own same-family units in range, nearest first, no repeats");
        n = PlanAreaAdd(selected, 1, c, 6, Family::Combat, centre, kAreaRadiusWide, out, kSelectCapacity);
        Check(n == 3 && out[2] == 5, "Shift radius reaches 150 m");
        n = PlanAreaAdd(selected, 1, c, 6, Family::None, centre, kAreaRadius, out, kSelectCapacity);
        Check(n == 0, "no family: nothing");

        // A nearly full selection keeps only the nearest that fit.
        uint32_t full[kSelectCapacity] = {};
        for (int i = 0; i < kSelectCapacity - 1; ++i)
            full[i] = 1000u + static_cast<uint32_t>(i);
        n = PlanAreaAdd(full, kSelectCapacity - 1, c, 6, Family::Combat, centre, kAreaRadiusWide, out,
                        kSelectCapacity);
        Check(n == 1 && out[0] == 1, "one free slot: only the nearest is added");
        n = PlanAreaAdd(full, kSelectCapacity, c, 6, Family::Combat, centre, kAreaRadiusWide, out, kSelectCapacity);
        Check(n == 0, "full selection: nothing added");

        // Candidates arriving far-to-near still end nearest first.
        AreaCandidate r[3];
        r[0] = { 7, Family::Tug, { 80, 0, 0 }, true };
        r[1] = { 8, Family::Tug, { 40, 0, 0 }, true };
        r[2] = { 9, Family::Tug, { 5, 0, 0 }, true };
        n = PlanAreaAdd(nullptr, 0, r, 3, Family::Tug, centre, kAreaRadius, out, 2);
        Check(n == 2 && out[0] == 9 && out[1] == 8, "capped output keeps the two nearest");
    }

    void TestHoldLabel()
    {
        Check(ShowHoldLabel(true, true, kModeDefend), "Shift on Defend: Hold");
        Check(!ShowHoldLabel(true, false, kModeDefend), "no Shift: Defend");
        Check(!ShowHoldLabel(false, true, kModeDefend), "alternate off: Defend");
        Check(!ShowHoldLabel(true, true, kModeHunt), "only the Defend entry");
        Check(HoldAvailable(true, true, true), "hold: on, hooked, single player");
        Check(!HoldAvailable(true, true, false), "hold is single player only");
        Check(!HoldAvailable(true, false, true), "hold needs the native hold hooks");
        Check(ClampHoldMode(5) == kHoldKeyAndShiftMenu && ClampHoldMode(-1) == kHoldOff, "hold mode clamps");
    }

    void TestKeys()
    {
        using BZROpenShim::QuickSaveKeyPolicy::Chord;
        const Chord save{ true, false, false, 0x24, true };
        const Chord load{ true, false, false, 0x23, true };
        const Key rally{ 0x56, false };
        Key keys[kKeyCount] = {};
        for (int i = 0; i < kKeyCount; ++i)
        {
            const KeyId id = static_cast<KeyId>(i);
            Key k;
            Check(CheckKeyText(id, GetKeyDef(id).defaultText, keys, rally, save, load, k) == nullptr,
                  std::string("default key accepted: ") + GetKeyDef(id).iniKey);
            keys[i] = k;
        }
        Check(keys[0].vk == 'T' && keys[1].vk == 'B' && keys[2].vk == 'X' && keys[3].vk == 'Z' && keys[4].vk == 'J' &&
                  keys[5].vk == 'C',
              "defaults T B X Z J C");
        const KeyDef& followDef = GetKeyDef(KeyId::FollowCamera);
        Check(std::string(followDef.iniKey) == "RtsFollowCameraKey" &&
                  std::string(followDef.rowCommand) == "OpenShim:RtsFollowCameraKey" &&
                  std::string(followDef.defaultText) == "C" && followDef.needsShift && !followDef.shiftVariant,
              "follow camera key row: Shift+C only");
        const KeyDef& idleDef = GetKeyDef(KeyId::IdleUnit);
        Check(std::string(idleDef.iniKey) == "RtsIdleUnitKey" &&
                  std::string(idleDef.rowCommand) == "OpenShim:RtsIdleUnitKey" &&
                  std::string(idleDef.defaultText) == "J" && !idleDef.needsShift && idleDef.shiftVariant,
              "idle unit key row");

        Key k;
        Check(CheckKeyText(KeyId::Hold, "V", keys, rally, save, load, k) != nullptr, "the rally key is refused");
        Check(CheckKeyText(KeyId::Hold, "X", keys, rally, save, load, k) != nullptr, "another RTS key is refused");
        Check(CheckKeyText(KeyId::Hold, "Z", keys, rally, save, load, k) == nullptr, "its own key is fine");
        Check(CheckKeyText(KeyId::Hold, "5", keys, rally, save, load, k) != nullptr, "digits refused");
        Check(CheckKeyText(KeyId::Hold, "F3", keys, rally, save, load, k) != nullptr, "group keys refused");
        Check(CheckKeyText(KeyId::Hold, "Shift+J", keys, rally, save, load, k) != nullptr, "modifiers refused");
        Check(CheckKeyText(KeyId::Hold, "bogus", keys, rally, save, load, k) != nullptr, "junk refused");
        Check(CheckKeyText(KeyId::Hold, "J", keys, rally, save, load, k) != nullptr, "the idle unit key is refused");
        Check(CheckKeyText(KeyId::IdleUnit, "J", keys, rally, save, load, k) == nullptr, "idle unit: its own key");
        Check(CheckKeyText(KeyId::Hold, "Q", keys, rally, save, load, k) == nullptr && k.vk == 'Q', "Q accepted");
        const Chord shiftQ{ false, true, false, 'Q', false };
        Check(CheckKeyText(KeyId::AreaSelect, "Q", keys, rally, shiftQ, load, k) != nullptr,
              "Shift+key action refuses a Shift-only QuickSave chord on that key");
        Check(CheckKeyText(KeyId::IdleUnit, "Q", keys, rally, shiftQ, load, k) != nullptr,
              "idle unit (Shift variant) refuses a Shift-only QuickSave chord");
        Check(CheckKeyText(KeyId::Hold, "Q", keys, rally, shiftQ, load, k) == nullptr,
              "plain-only action ignores a Shift QuickSave chord");
    }

    void TestChordClashes()
    {
        Key keys[kKeyCount] = {};
        for (int i = 0; i < kKeyCount; ++i)
            keys[i] = Key{ static_cast<unsigned>(GetKeyDef(static_cast<KeyId>(i)).defaultText[0]), false };
        // Remote target (T) takes only Shift+T: plain T stays frontal_target.
        Check(ActionTakingChord(keys, 'T', false, true, false, false) == KeyId::RemoteTarget, "Shift+T is ours");
        Check(ActionTakingChord(keys, 'T', false, false, false, false) == KeyId::Count, "plain T is stock");
        // Area select (X) takes X and Shift+X.
        Check(ActionTakingChord(keys, 'X', false, false, false, false) == KeyId::AreaSelect, "X is ours");
        Check(ActionTakingChord(keys, 'X', false, true, false, false) == KeyId::AreaSelect, "Shift+X is ours");
        // Hold (Z) and building cycle (B) take only the plain key.
        Check(ActionTakingChord(keys, 'Z', false, false, false, false) == KeyId::Hold, "Z is ours");
        Check(ActionTakingChord(keys, 'Z', false, true, false, false) == KeyId::Count, "Shift+Z is stock");
        Check(ActionTakingChord(keys, 'B', false, false, true, false) == KeyId::Count, "Ctrl+B (eject) is stock");
        Check(ActionTakingChord(keys, 'X', false, false, false, true) == KeyId::Count, "Alt chords are stock");
        Check(ActionTakingChord(keys, 'X', true, false, false, false) == KeyId::Count, "extended bit must match");
        // Idle unit (J) takes J and Shift+J.
        Check(ActionTakingChord(keys, 'J', false, false, false, false) == KeyId::IdleUnit, "J is ours");
        Check(ActionTakingChord(keys, 'J', false, true, false, false) == KeyId::IdleUnit, "Shift+J is ours");
        // Follow camera (C) takes only Shift+C: plain C stays center_player.
        Check(ActionTakingChord(keys, 'C', false, true, false, false) == KeyId::FollowCamera, "Shift+C is ours");
        Check(ActionTakingChord(keys, 'C', false, false, false, false) == KeyId::Count, "plain C is stock");
        Check(ActionTakingChord(keys, 'C', false, true, true, false) == KeyId::Count, "Ctrl+Shift+C is stock");
        Check(ActionTakingChord(keys, 'Q', false, false, false, false) == KeyId::Count, "unbound key");
        Check(ActionUsingKey(keys, 'T', false) == KeyId::RemoteTarget, "the rally key may not be T");
        Check(ActionUsingKey(keys, 'V', false) == KeyId::Count, "V is free for the rally key");
        Check(ActionTakingChord(nullptr, 'X', false, false, false, false) == KeyId::Count, "no keys");
    }

    void TestFollowCamera()
    {
        // A press: a new selected unit wins, the same one stops, nothing
        // selected follows the player (or stops while following).
        Check(FollowKeyTarget(0x11, 0x99, 0) == 0x11, "follow the first selected unit");
        Check(FollowKeyTarget(0x22, 0x99, 0x11) == 0x22, "a different selected unit switches");
        Check(FollowKeyTarget(0x11, 0x99, 0x11) == 0, "the same unit again stops");
        Check(FollowKeyTarget(0, 0x99, 0x11) == 0, "no selection while following stops");
        Check(FollowKeyTarget(0, 0x99, 0) == 0x99, "no selection follows the player");
        Check(FollowKeyTarget(0, 0, 0) == 0, "no selection and no player: nothing");
        Check(FollowKeyTarget(0, 0x99, 0x99) == 0, "second press on the player stops");

        // A tick: stops outrank the hold, the hold outranks the recentre.
        Check(ClassifyFollowTick(true, true, true, true) == FollowTick::Recenter, "recentre");
        Check(ClassifyFollowTick(true, true, false, true) == FollowTick::Hold, "pause holds the follow");
        Check(ClassifyFollowTick(false, true, true, true) == FollowTick::StopDisabled, "option off stops");
        Check(ClassifyFollowTick(true, false, true, true) == FollowTick::StopLeftSatellite, "leaving satellite stops");
        Check(ClassifyFollowTick(true, false, false, true) == FollowTick::StopLeftSatellite,
              "leaving satellite stops even when paused");
        Check(ClassifyFollowTick(true, true, true, false) == FollowTick::StopTargetGone, "a dead unit stops");
        Check(ClassifyFollowTick(true, true, false, false) == FollowTick::StopTargetGone,
              "a dead unit stops even when paused");
        Check(std::string(FollowTickName(FollowTick::StopTargetGone)) == "unit gone", "tick names");
    }

    KeyEvent Down(unsigned vk, bool shift = false, bool ctrl = false)
    {
        KeyEvent e;
        e.msg = kWmKeyDown;
        e.vk = vk;
        e.shift = shift;
        e.ctrl = ctrl;
        return e;
    }

    KeyEvent Up(unsigned vk)
    {
        KeyEvent e;
        e.msg = kWmKeyUp;
        e.vk = vk;
        return e;
    }

    void TestKeyMessages()
    {
        const Key t{ 'T', false };
        KeyLatch latch;
        KeyDecision d = ClassifyKey(Down('T'), KeyId::RemoteTarget, t, true, latch);
        Check(!d.swallow && !d.act, "plain T stays the stock frontal_target");
        d = ClassifyKey(Down('T', true), KeyId::RemoteTarget, t, true, latch);
        Check(d.swallow && d.act, "Shift+T is ours (stock T would clear the target)");
        KeyEvent repeat = Down('T', true);
        repeat.lParam = kLParamPreviousStateBit;
        d = ClassifyKey(repeat, KeyId::RemoteTarget, t, true, latch);
        Check(d.swallow && !d.act, "autorepeat hidden, no second action");
        d = ClassifyKey(Up('T'), KeyId::RemoteTarget, t, true, latch);
        Check(d.swallow && !latch.downSwallowed, "keyup of a swallowed press hidden");
        d = ClassifyKey(Up('T'), KeyId::RemoteTarget, t, true, latch);
        Check(!d.swallow, "keyup of a stock press passes");
        d = ClassifyKey(Down('T', true), KeyId::RemoteTarget, t, false, latch);
        Check(!d.swallow && !d.act, "gate closed: stock");

        const Key x{ 'X', false };
        d = ClassifyKey(Down('X'), KeyId::AreaSelect, x, true, latch);
        Check(d.act && !d.shift, "X: 100 m");
        latch = {};
        d = ClassifyKey(Down('X', true), KeyId::AreaSelect, x, true, latch);
        Check(d.act && d.shift, "Shift+X: 200 m");
        latch = {};
        d = ClassifyKey(Down('X', false, true), KeyId::AreaSelect, x, true, latch);
        Check(!d.swallow, "Ctrl+X passes");

        const Key b{ 'B', false };
        latch = {};
        d = ClassifyKey(Down('B', false, true), KeyId::BuildingCycle, b, true, latch);
        Check(!d.swallow, "Ctrl+B stays the stock eject");
        d = ClassifyKey(Down('B', true), KeyId::BuildingCycle, b, true, latch);
        Check(!d.swallow, "Shift+B passes");
        d = ClassifyKey(Down('B'), KeyId::BuildingCycle, b, true, latch);
        Check(d.act, "B cycles");
        d = ClassifyKey(Down('Z'), KeyId::BuildingCycle, b, true, latch);
        Check(!d.swallow, "another key is not ours");
    }

    // A Construction Rig's ModeList while a building is picked: HoverCraft's
    // slots 0-2 (Go, Follow Me, Go To Nav, as in the Wingman fixture), the
    // class pointer in a build slot (3..9; the 0x0049D550 UpdateModeList
    // address is UNVERIFIED) and active.
    RigPick PickedRig(uint32_t cls)
    {
        RigPick rig;
        rig.isRig = true;
        rig.ownTeam = true;
        rig.replica = false;
        rig.busy = 0;
        const int modes[kModeSlots] = { 1, 2, kModeGoToNav, static_cast<int>(cls), 0, 0, 0, 0, 0, 0, 0 };
        rig.modes = MakeList(modes, Bits({ 0, 1, 2, 3 }));
        rig.modes.active = 3;
        rig.dropClass = cls;
        return rig;
    }

    void TestIdleUnits()
    {
        Check(IsIdle(0, 0) && IsIdle(2, 0) && IsIdle(0, 2) && IsIdle(2, 2), "0/0, 2/0, 0/2, 2/2 are idle");
        Check(!IsIdle(3, 0) && !IsIdle(0, 3) && !IsIdle(19, 0), "3/0, 0/3, 19/0 are busy");
        Check(!IsIdle(0, 19) && !IsIdle(4, 4), "any live order is busy");
        Check(IsIdle(0, 1) && IsIdle(1, 0), "a selection (CMD_SELECT) is not an order");
        Check(IdleTracksFamily(Family::Combat) && IdleTracksFamily(Family::Tug) &&
                  IdleTracksFamily(Family::ConstructionRig) && IdleTracksFamily(Family::Scavenger),
              "every unit family is tracked");
        Check(!IdleTracksFamily(Family::None), "non-units are not");
        Check(ScavengerGathering(4, true, 0) && ScavengerGathering(4, true, 1) && ScavengerGathering(4, true, 2) &&
                  ScavengerGathering(4, true, 3) && ScavengerGathering(4, true, 4),
              "RECYCLE new, searching, to scrap, to drop-off, to repair is gathering");
        Check(!ScavengerGathering(4, true, 5) && !ScavengerGathering(4, true, 6) && !ScavengerGathering(4, true, 7),
              "waiting, done and stuck are idle");
        Check(!ScavengerGathering(1, true, 2), "a stale task outside RECYCLE is idle");
        Check(!ScavengerGathering(1, false, -1) && !ScavengerGathering(0, false, -1),
              "WAIT and START are idle");
        Check(!ScavengerGathering(4, false, 2), "no RecycleTask: idle");

        uint32_t list[5] = { 0x30, 0x10, 0x50, 0x20, 0x40 };
        SortHandlesAscending(list, 5);
        Check(list[0] == 0x10 && list[1] == 0x20 && list[2] == 0x30 && list[3] == 0x40 && list[4] == 0x50,
              "idle handles sort ascending");
        Check(NextIdleIndex(list, 5, 0) == 0, "no last pick: the first");
        Check(NextIdleIndex(list, 5, 0x10) == 1, "after the first: the second");
        Check(NextIdleIndex(list, 5, 0x50) == 0, "after the last: wraps to the first");
        Check(NextIdleIndex(list, 5, 0x35) == 0, "a last handle that is gone restarts at 0");
        Check(NextIdleIndex(list, 1, 0x10) == 0, "a single unit cycles onto itself");
        Check(NextIdleIndex(list, 0, 0x10) == -1 && NextIdleIndex(nullptr, 3, 0) == -1, "empty list: -1");

        uint32_t out[kSelectCapacity] = {};
        Check(PlanIdleSelect(list, 5, 0x20, false, out, kSelectCapacity) == 1 && out[0] == 0x30,
              "one press picks the next unit");
        Check(PlanIdleSelect(list, 5, 0, true, out, kSelectCapacity) == 5 && out[0] == 0x10 && out[4] == 0x50,
              "Shift picks them all");
        Check(PlanIdleSelect(list, 5, 0, true, out, 3) == 3, "Shift stops at the output capacity");
        Check(PlanIdleSelect(list, 0, 0, true, out, kSelectCapacity) == 0, "nothing idle: nothing picked");
        uint32_t many[kSelectCapacity + 20];
        for (int i = 0; i < kSelectCapacity + 20; ++i)
            many[i] = static_cast<uint32_t>(i + 1);
        uint32_t big[kSelectCapacity + 20] = {};
        Check(PlanIdleSelect(many, kSelectCapacity + 20, 0, true, big, kSelectCapacity + 20) == kSelectCapacity,
              "Shift stops at the selection capacity");

        // Alert policy: busy->idle only, never a first sighting, 5 s apart.
        IdleTracker t;
        t.BeginPass();
        IdleObservation o = t.Observe(1, true, 1000);
        Check(o.first && !o.changed && !o.alert, "a unit first seen idle never alerts");
        o = t.Observe(2, false, 1000);
        Check(o.first && !o.alert, "a unit first seen busy does not alert");
        t.EndPass();
        Check(t.Count() == 2, "two tracked");

        t.BeginPass();
        o = t.Observe(1, false, 1500);
        Check(o.changed && !o.alert && !o.idle, "idle->busy does not alert");
        o = t.Observe(2, true, 1500);
        Check(o.changed && o.idle && o.alert, "busy->idle alerts");
        t.EndPass();

        t.BeginPass();
        o = t.Observe(1, true, 3000);
        Check(o.changed && !o.alert, "a second alert inside 5 s is suppressed");
        o = t.Observe(2, true, 3000);
        Check(!o.changed && !o.alert, "no change, no alert");
        t.EndPass();

        t.BeginPass();
        o = t.Observe(1, false, 4000);
        t.EndPass();
        t.BeginPass();
        o = t.Observe(1, true, 1500 + kIdleAlertIntervalMs - 1);
        Check(o.changed && !o.alert, "one ms short of the interval is still suppressed");
        t.EndPass();
        t.BeginPass();
        o = t.Observe(1, false, 7000);
        t.EndPass();
        t.BeginPass();
        o = t.Observe(1, true, 1500 + kIdleAlertIntervalMs);
        Check(o.changed && o.alert, "exactly the interval later alerts again");
        t.EndPass();

        // Entries not observed in a pass are dropped.
        t.BeginPass();
        t.Observe(1, true, 9000);
        t.EndPass();
        Check(t.Count() == 1, "an unobserved unit is dropped");
        t.BeginPass();
        o = t.Observe(2, true, 9000);
        Check(o.first && !o.alert, "a dropped unit that returns is a first sighting");
        t.EndPass();

        // A full table ignores new units instead of overflowing.
        IdleTracker full;
        full.BeginPass();
        for (int i = 1; i <= kIdleTrackCapacity + 5; ++i)
            full.Observe(static_cast<uint32_t>(i), true, 0);
        full.EndPass();
        Check(full.Count() == kIdleTrackCapacity, "the table is fixed size");
        t.Clear();
        Check(t.Count() == 0, "Clear empties the table");
    }

    void TestBuildAtNav()
    {
        const uint32_t cls = 0x0A1B2C30u;
        RigPick rig = PickedRig(cls);
        Check(PickedBuildClass(rig) == cls, "a picked building is the active class mode");
        Check(PickedSlotEnabled(rig), "the picked entry is enabled");

        RigPick r = rig;
        r.modes.active = -1;
        Check(PickedBuildClass(r) == 0, "no active slot: nothing picked");
        r = rig;
        r.modes.active = kModeSlots;
        Check(PickedBuildClass(r) == 0, "out-of-range active slot: nothing picked");
        r = rig;
        r.modes.active = 0;
        Check(PickedBuildClass(r) == 0, "Go (mode 1) is not a building");
        r = rig;
        r.modes.modes[3] = static_cast<int>(kLastFixedMode);
        r.dropClass = kLastFixedMode;
        Check(PickedBuildClass(r) == 0, "0x1A is a fixed mode, not a class");
        r = rig;
        r.dropClass = 0x0B000000u;
        Check(PickedBuildClass(r) == 0, "a stale drop class (or a PRODMENU stub) does not count");
        r = rig;
        r.busy = 1;
        Check(PickedBuildClass(r) == 0, "+0x228 set: GetCommand refuses, so not picked");
        r = rig;
        r.isRig = false;
        Check(PickedBuildClass(r) == 0, "only Construction Rigs");
        r = rig;
        r.ownTeam = false;
        Check(PickedBuildClass(r) == 0, "only the player's team");
        r = rig;
        r.replica = true;
        Check(PickedBuildClass(r) == 0, "a remote replica is never ordered here");
        r = rig;
        r.modes.enabled &= ~(1u << 3);
        Check(PickedBuildClass(r) == cls && !PickedSlotEnabled(r), "a disabled pick still labels, but is refused");

        Check(ShowBuildAtNavLabel(true, kModeGoToNav, true), "Go To Nav reads Build at Nav");
        Check(!ShowBuildAtNavLabel(false, kModeGoToNav, true), "option off: stock label");
        Check(!ShowBuildAtNavLabel(true, kModeGoToNav, false), "no picked rig: stock label");
        Check(!ShowBuildAtNavLabel(true, kModeDefend, true), "only the Go To Nav entry");

        Check(DecideBuildAtNav(true, true, true, kCmdDropoff) == BuildAtNavVerdict::Build, "8: build");
        Check(DecideBuildAtNav(true, true, true, 9) == BuildAtNavVerdict::BadSpot, "9 (no dropoff): refused");
        Check(DecideBuildAtNav(true, true, true, 0) == BuildAtNavVerdict::BadSpot, "0: refused");
        Check(DecideBuildAtNav(true, true, false, kCmdDropoff) == BuildAtNavVerdict::BadSpot,
              "a faulted query is refused");
        Check(DecideBuildAtNav(true, false, true, kCmdDropoff) == BuildAtNavVerdict::NoPosition,
              "no nav position: refused");
        Check(DecideBuildAtNav(false, true, true, kCmdDropoff) == BuildAtNavVerdict::NotAffordable,
              "a disabled entry is refused first");

        Check(KeepSelectionAfterNavPick(0, 0, 1), "all refused: selection kept");
        Check(!KeepSelectionAfterNavPick(1, 0, 1), "one rig built: stock deselect");
        Check(!KeepSelectionAfterNavPick(0, 2, 1), "others went: stock deselect");
        Check(!KeepSelectionAfterNavPick(0, 0, 0), "nothing refused: stock deselect");
    }
}

int main()
{
    TestStockIntersectMatchesEngine();
    TestMixedGroupFixture();
    TestSmartParts();
    TestFamilies();
    TestCycles();
    TestAreaSelect();
    TestHoldLabel();
    TestKeys();
    TestChordClashes();
    TestFollowCamera();
    TestKeyMessages();
    TestIdleUnits();
    TestBuildAtNav();
    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "rts_commands_policy_tests: %d check(s) failed\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("rts_commands_policy_tests: all checks passed\n");
    return 0;
}
