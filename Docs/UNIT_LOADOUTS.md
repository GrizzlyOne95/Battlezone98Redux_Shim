# Unit loadouts (`[Gameplay] UnitLoadouts`)

Default **off**, single player only. Milestone **M1** of `Docs/APPROVED_DESIGNS.md` item 18
(branch `docs/approved-designs`): the menu, the surcharge and the swap.

- Source: `src/patches/unit_loadouts.cpp`.
- Rules: `include/unit_loadouts_policy.h`, tested by `tests/unit_loadouts_policy_tests.cpp`.
- Kill switch: `OPENSHIM_DISABLE_UNIT_LOADOUTS=1` keeps it off whatever the ini says.
- Needs `[ProducerBuildMenus] Enabled = 1` (in `openshim_producer_build_menus.ini`). Without it, the
  Settings page marks the option "Unavailable: needs [ProducerBuildMenus] Enabled = 1".

**M2 (the save sidecar `<save>.loadout`) is not built.** Loadouts live in memory for the mission
only. They are dropped at mission end and on any load, saved games included.

## What it does

- **Opening the pages.** Alt+pick a unit in the player's own deployed Recycler or Factory build menu
  to open that unit's loadout pages inside the same PRODMENU panel. Only Alt opens them: Shift
  (RtsBuildQueue remove) and Ctrl keep their stock and queue meanings.
- **Slot page.** It has one button per configurable weapon slot, labelled `N: <weapon>`.
  - A slot is configurable when the class has a `weaponHard` name and a stock weapon in it.
  - The label shows the chosen weapon with `*` when the slot is changed, or the stock weapon.
- **Weapon page** (picking a slot). It lists `Stock`, then every weapon the player's **current
  Armory** offers that is compatible with the slot.
  - Compatible means the same hardpoint category as the slot's stock weapon. The stock weapon itself
    is not listed again.
  - The current choice carries `*`.
  - Each weapon button shows its Armory price.
  - When there are more than 8 entries, each page shows 7 plus `More`, which pages on and wraps.
  - Picking an entry stores it and returns to the slot page.
- **Back** (position 9) goes from the weapon page to the slot page, then back to the build list.
  Deselecting the producer also closes the pages.
- **Scope of a loadout.** It is keyed by the unit's ODF (class +0x30). It applies wherever that unit
  is built, by the Recycler or the Factory.
- **Surcharge.** The unit's scrap cost rises by the **full Armory price** of every changed slot whose
  weapon the Armory offers right now.
  - The price is the weapon powerup class's cost from the same cost function the Armory uses.
  - The menu figure, the enable gate, the RtsBuildQueue afford test, the charge and the cancel refund
    all come from that one function, so they agree.
- **Fallback.** With no live Armory, or when the Armory does not offer the chosen weapon (or its
  category no longer fits), that slot is not charged and the unit gets its stock weapon.
  - Availability is decided **when the build starts**: the charge freezes the quote, and the swap
    and refund use that frozen quote.
- **Lock.** A unit's loadout cannot be edited while that unit is building. Its weapon buttons are
  greyed, and a pick plays `mnu_buzz.wav` and logs `refused`.
  - "Building" means any of the player's Recycler, Factory or tracked producers has that class in
    +0x300.
- **Swap.** When the unit is built, each frozen choice is fitted on its slot through the engine's
  give-weapon function, replacing the stock weapon.

## How it is built

### Cost: entry detour on BuildScrapCost 0x004E1B90

The detour is installed only once the option is on, so a game with the option off never patches
the function.

- `InstallInlineDetour32` steals 6 bytes `55 8B EC 83 EC 0C`, guarded by the `BuildScrapCost` row
  bytes.
- The naked `CostEntryThunk` calls `CostImpl(return address, team, class, caller ebp)`. The
  original runs through the trampoline.

The cost function is the single source for every figure:

| Caller | Line | What it does with the cost |
| --- | --- | --- |
| `ControlPanel::Render` | `FUN_004a08e0.c` line 1424 | Menu figure |
| `Producer::UpdateModeList` | `FUN_005ae660.c` line 65 | Enable gate |
| `Producer::StartBuild` | `FUN_005aecb0.c` lines 11-18 | Compares with the team's scrap, then subtracts it |
| Refund | `FUN_005aed80.c` lines 9-16 | Adds it back while +0x300 is still set, then clears +0x300 |

`CostImpl` tells the callers apart by the return address:

- **Charge** (`0x005AECDF` = row `UnitLoadoutStartBuildCostCall` + 0x29).
  - Read the producer from the caller's `[ebp-4]`. StartBuild stores `this` there with
    `mov [ebp-4],ecx`, which the row's guard bytes pin.
  - For the player's live Recycler/Factory, compute the live quote and freeze it per producer.
    Every player build is tracked, even with no surcharge, so the lock and the swap see it.
  - Return base + surcharge.
- **Refund** (`0x005AEDC5` = row `UnitLoadoutRefundCostCall` + 0x3F).
  - Return base + the frozen surcharge only when the frozen class, the refunded class and the
    producer's +0x300 all agree (`RefundSurcharge`).
  - Then drop the quote.
  - This is honoured even after the option is turned off, because the player paid it.
- **Anything else** (display, enable gate, build queue, Armory): base + the live surcharge.
- **A loadout weapon button** (a stub pointer): the cost of the mapped powerup, so the button shows
  the Armory price.

The surcharge applies only when all of these hold (`SurchargeApplies`):

- the team argument is the local player's team;
- the session is single player;
- the feature is active;
- the unit ODF has at least one choice.

AI teams always pay stock.

### Menu (PRODMENU vtable hooks, chained, no new vtable writes)

- `ProducerSetActiveModeHook` (slot 11, `producer_build_menu.cpp`) calls
  `UnitLoadoutsOnSetActiveMode` first.
  - That function handles loadout buttons, Back while a page is open, and Alt+pick (held-key dword
    `InputHeldModifierKeys` bit `0x1000000`, set in `FUN_00434bf0` for scancodes 0x38/0x71).
  - It returns true, so the hook returns false and the panel stays open.
- `ProducerUpdateModeListHook` (slot 23) calls `UnitLoadoutsUpdateModeList` first.
  - With a page open, it runs the stock `Producer::UpdateModeList` over an empty build page
    (`RunProducerUpdateModeListEmptyPage`, the same class-list swap PRODMENU uses). This clears
    slots 1..9 and keeps the stock slot 10.
  - It then lays its buttons over 1..8 and Back (0x16) at 9.
  - Stock `UpdateModeList` state 2 writes `SetMode(i,0,0)` for null entries
    (`FUN_005ae660.c` lines 60-63).
  - RtsBuildQueue's re-enable pass is not run on a loadout page.
- `ProducerDeselectHook` (slot 9) calls `UnitLoadoutsForgetProducer`.
- **Buttons.** There are 15 class-shaped stubs (0x200 bytes, label at +0x64, +0x13C/+0x140 = -1),
  allocated once and never freed.
  - Slot, Stock and More buttons hide their "00" cost through PRODMENU's existing sprintf thunk
    (`HideProducerMenuButtonCost`).
  - Weapon buttons show their price through the cost detour.
- **Rows these hooks rely on.** Slots 11/23/9 are PRODMENU's existing rows:
  - `Recycler/Factory UpdateModeList VTable Hook`
  - `Recycler/Factory SetActiveMode VTable Hook`
  - `Recycler/Factory Deselect VTable Hook`

  `PartsReady` checks that both vtables hold the PRODMENU hooks.

### Swap: FinishBuild slot 42, chained

The FinishBuild hook is `ProducerFinishBuildHook` in `producer_rally_points.cpp`, which owns
slot 42. It is installed through `EnsureProducerFinishBuildHook`, never patched twice:

- Recycler vtable 0x00886454: slot 42 at 0x008864FC.
- Factory vtable 0x00879388: slot 42 at 0x00879430.

The chain after the stock `Producer::FinishBuild` 0x005AF160 runs in this order: rally,
AutoGroupNewUnits, `UnitLoadoutsOnUnitBuilt(producer, built)`.

`UnitLoadoutsOnUnitBuilt` takes the producer's frozen quote, then checks:

- The built unit's class (+0xF8) must equal the frozen class.
- For each chosen slot `i` (`PlanSwap`):
  - the slot must be 0..4;
  - carrier slot `i` must hold the class's stock weapon;
  - the slot's hardpoint type (+0x84) must equal the chosen WeaponClass category (+0x74).

When all of that holds, it calls `FUN_00612F10(unit, WeaponClass*, i)` under SEH.

**Credit for unfitted weapons** (`UnfittedCredit`). A chosen slot counts as fitted only when the
give-weapon call ran and returned true. Every chosen slot that was not fitted is credited back at its
frozen Armory price: the verdict was not Swap, the call faulted, or it returned false. When the built
unit is not the frozen class, the whole frozen surcharge is credited. The credit never exceeds the
surcharge paid. It is paid in single player only, through `Team::AddScrap` `FUN_005E1010` (under
SEH) on the producer's Team at +0x17C, the same call the stock refund makes.

**Stale records.** Frozen quotes are keyed by producer address, and each record keeps the
producer's handle. A record is honoured only while `GetObj(handle)` is still that producer:

- StartBuild drops any old record for the producer before its gates run.
- Refund and FinishBuild ignore and drop a stale record.
- The edit lock prunes stale records as it scans.

**Mission change.** `ResetUnitLoadouts` clears the loadouts and frozen quotes. It runs on leaving
the simulation (`lifecycle_seams.cpp`, next to `ResetProducerRallyPoints`), on the mission-hook
reset bridge (`mission_hook_bridges.cpp`), and on the SinglePlayer tier reset.

## Engine facts (GOG Redux 2.2.301)

| Fact | Evidence |
| --- | --- |
| GameObjectClass `weaponHard[i]` char[4] at +0xE4+i*4, `weaponClass[i]` WeaponClass* at +0xF8+i*4, i = 0..4 | `FUN_004e0450.c` lines 169-191 (dword indexes 0x39 and 0x3e of the class) |
| Class slot i is carrier slot i | `FUN_004da0b0.c` lines 220-221 (`FUN_00472420(i, hardpoint)`, `FUN_004a77a0(i, weapon)`) |
| Carrier = GameObject +0x1A0; hardpoint i = `[carrier+4+i*4]`; weapon i = `[carrier+0x18+i*4]` when mask `[carrier+0x2C]` has bit i | `FUN_00417ca0.c`, `FUN_00417f40.c` line 5, `FUN_00417f60.c` lines 14-18 |
| A weapon's WeaponClass* at +0x08 | `FUN_00611aa0.c` line 29 (WeaponClass parent); weapon side reused from the loadout-presets research (`FUN_00500060`), **UNVERIFIED in this pass** |
| WeaponClass ODF token at +0x18 (8 chars), display name at +0x38, category at +0x74 (0x47 cannon, 0x48 rocket, 0x49 mortar, 0x4A special, 0x46 other) | `FUN_00611aa0.c` lines 36-38, 67, 84-107 |
| Hardpoint type +0x84 is matched against WeaponClass +0x74 | `FUN_00472da0.c` lines 115-128 |
| Weapon powerup: sig `'WEPN'` at +0x14, WeaponClass* at +0x170 | `FUN_00472da0.c` lines 115, 121 |
| Armory class lists at +0x608 (5), +0x660, +0x684, +0x6A8, +0x6CC (9 each) | `FUN_00472780.c` lines 44-68 |
| Team slot object = `*(Team + slot*4)`; Recycler 1, Factory 2, Armory 3 | `FUN_005e0f70.c` line 5; Lua GetRecyclerHandle/GetFactoryHandle/GetArmoryHandle 0x004FFDB0/0x004FFE20/0x004FFE90 |
| Give weapon `FUN_00612F10(obj, WeaponClass*, slot)` replaces the slot's weapon and sets the mask bits; its range test never rejects | `FUN_00612f10.c` lines 15, 19-50; called by `FUN_005cb0d0.c` line 20 |
| StartBuild charges the cost once, before setting +0x300 | `FUN_005aecb0.c` lines 11-18 |
| Refund reads the cost while +0x300 is set | `FUN_005aed80.c` lines 9-16 |
| `FUN_005E1010` is `Team::AddScrap(Team*, int)`, `__thiscall`, `ret 4`; it adds the amount and clamps to the cap at Team+0x170 | `FUN_005e1010.c` lines 2, 8-14; `ret 4` at 0x005E10A4 |
| A producer's Team* is at +0x17C | `FUN_005aecb0.c` line 16 and `FUN_005aed80.c` line 14 call `FUN_005e1010`; the disassembly loads `ecx` with `mov ecx,[ecx+0x17C]` at 0x005AED01 and 0x005AEDF1 (the decompile omits `this`) |

### Rows (`scripts/patches.json`, `engine_addresses`)

| Row | Address | Use |
| --- | --- | --- |
| `BuildScrapCost` (existing) | 0x004E1B90 | Detour target; prologue guard |
| `UnitLoadoutStartBuildCostCall` (new) | 0x005AECB6 | StartBuild +6 .. end of the cost call; return 0x005AECDF |
| `UnitLoadoutRefundCostCall` (new) | 0x005AED86 | Refund +6 .. end of the cost call; return 0x005AEDC5 |
| `UnitLoadoutGiveWeapon` (new) | 0x00612F10 | Give weapon |
| `UnitLoadoutTeamAddScrap` (new) | 0x005E1010 | Credit for unfitted weapons |
| `InputHeldModifierKeys`, `RecyclerVtable`, `FactoryVtable`, `ArmoryVtable`, `GameObjectHandleGetObj` (existing) | | Alt bit, producer and Armory identity, handle checks |

The two call-site rows start at +6 because `TraceAIBuildLedger` may detour StartBuild's first
6 bytes. All four new rows were read from the shipping exe on 2026-11-19.

## Decision log lines (`[LOADOUT]`)

Silent gates log only when their text for that key changes (`LogDecision`). The other lines are
budgeted (200 per mission).

| Key / line | Meaning |
| --- | --- |
| `active=N (option, hooks, single player)` | Feature gate changed |
| `alt-pick: passed to stock: feature inactive / not the player's live Recycler/Factory / producer not deployed / no button memory` | Alt+pick did not open pages |
| `alt-pick: opens loadout pages` and `opened <odf> at producer 0x...` | Pages opened |
| `refused <odf>: the unit has no weapon slots` | Alt+pick on a weaponless unit (buzz; the pick is swallowed) |
| `page: closed: <why>` | An open page was dropped: inactive, not the player's producer, team changed, not deployed, stock mode list failed |
| `button: swallowed: no open loadout page` | A stale loadout button was picked |
| `lock: weapon choices greyed: unit is building` / `weapon choices editable` | Lock state on the weapon page |
| `refused <odf>: loadout is locked while this unit is building` | Edit refused (buzz) |
| `<odf> slot N set to <weapon> (<name>)` / `set to stock` | Edit stored |
| `quote <odf>: slotN=<weapon> <verdict> +price ...; surcharge S` | Live quote changed: `chosen`, `stock (no Armory)`, `stock (not offered by the Armory)`, `stock (hardpoint type differs)` |
| `surcharge <odf>: not applied (inactive / not single player)` | Loadout exists but the gate is closed |
| `charge <odf> at producer 0x...: base + surcharge S` | StartBuild charged a surcharge |
| `refund <odf>: base + surcharge S` | Cancel refunded a surcharge |
| `swap <odf>: skipped: built unit is another class / nothing was built` | Swap gate |
| `swap <odf> slotN: skipped: <reason>` / `fitted` / `give-weapon returned false` / `give-weapon faulted` | Per-slot swap verdict |
| `built <odf>: slot N <weapon> fitted` | A weapon was fitted |
| `swap: skipped: stale frozen quote (producer handle no longer matches)` | FinishBuild found a record from a dead producer |
| `credit <odf> at producer 0x...: N scrap for unfitted weapons` (`FAILED (...)` suffix on a fault) | Unfitted weapons credited back |
| `credit <odf>: not credited (not single player)` | Credit gate closed |
| `mission reset: N loadout(s), M frozen quote(s) dropped (no save sidecar in M1)` | Mission end or load |
| `OPENSHIM_DISABLE_UNIT_LOADOUTS is set; unit loadouts stay off` | Kill switch |

## Limits

- **Not saved (M1).** Loadouts are lost at mission end and on any load. M2's sidecar is not built.
- **Alt+pick is UNVERIFIED live.** Alt may be eaten by Windows (system menu) or by the game's own
  Alt command labels (`RtsOrderQueue` mentions Space and Alt command labels). Number-key picks with
  Alt held are also untested.
- **Greyed entries.** A greyed (unaffordable, or busy producer) build entry probably cannot be picked
  at all, so Alt+pick may need the entry enabled. UNVERIFIED.
- **Category check at menu time.** Compatibility in the menu uses the stock weapon's category as a
  stand-in for the slot's hardpoint type. The swap re-checks the real hardpoint (+0x84) and skips a
  mismatch with a log line. That slot's Armory price is then credited back (see the credit above).
- **Other producers.** Only the player's Recycler and Factory charge and fit. Another producer
  (Armory, Construction Rig) that lists the same unit ODF would show the surcharge in its menu figure
  but charge stock.
- **Changed slot labels.** A changed slot whose weapon the Armory no longer offers still shows `*`
  on the slot page. The quote log shows it falls back to stock.
- **Refund mismatch on toggle.** Turning the option off keeps frozen quotes, so refunds and swaps of
  builds started while it was on still match. Turning it on mid-build does not surcharge or fit that
  build.

## Live test checklist (not yet run)

Setup:

1. `[Gameplay] UnitLoadouts = 1` and `[ProducerBuildMenus] Enabled = 1`, single player, a mission
   with a Recycler or Factory, an Armory and scrap.
2. `openshim.log` shows `[LOADOUT] install complete` and `active=1`.

Checks (precondition failures are fixture failures, not product FAILs):

1. Deployed Factory selected: Alt+click a tank. The slot page shows `1: <stock weapon>` ... and Back.
   Log: `alt-pick: opens loadout pages`. If nothing happens, record whether Alt reached the game
   (fixture finding).
2. Pick a slot. The weapon page lists Stock plus Armory weapons of that category, each with its
   Armory price, and More when there are more than 8 entries. Back returns to the slot page.
3. Pick a weapon. The slot shows `*`, and the build list figure for the tank rises by exactly that
   weapon's Armory figure.
4. Build it. Scrap drops by the shown figure, and the log shows `charge`. The built tank has the
   chosen weapon in that slot (check the HUD weapon list) and the log shows `built ... fitted`.
5. Start another and cancel it. The refund equals the charge (scrap back to the start value), and the
   log shows `refund`.
6. While a tank is building: Alt+pick the tank. The weapon buttons are greyed, and a pick buzzes with
   `refused ... locked`.
7. Destroy or remove the Armory, then build. There is no surcharge, the stock weapon is fitted, and
   the quote log shows `stock (no Armory)`.
8. Set a slot back to Stock. The figure returns to stock.
9. Save and load. The loadouts are gone (M1), and the log shows `mission reset`.
10. With the option off or in multiplayer: Alt+pick builds as stock and costs are stock.
11. Credit: build with a chosen weapon that the swap skips (look for `swap <odf> slotN: skipped`,
    for example `hardpoint type differs`). Removing the Armory after StartBuild does not cause a
    skip, because the frozen quote is used. When the unit is built, scrap rises by
    that slot's price and the log shows `credit ... N scrap for unfitted weapons`. When every slot is
    fitted, there is no credit line.
12. Mission change without EXU: set a loadout, quit to the shell or load another mission. The log
    shows `mission reset`. Then start a mission that has the same unit: the slot page shows stock
    with no `*`, and the build figure is the stock figure.
