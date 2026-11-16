# Offensive unit slot cap (10 units) — RE and feasibility

Status: research only, nothing implemented. Question: can the player command
more than 10 offensive units, for example through a second page of the
Offensive (key 2) menu?

Answer: widening the slot ranges natively is not worth it. A second page is
feasible as an OpenShim feature (option B below).

Sources: the 1.5 decompile with PDB in the private `Battlezone_Source`
repository (`BZ1/1.5/functions/...`, `BZ1/1.5/all_decompiled.c`,
`BZ1/derived/bz15_pdb/raw/types.txt`). GOG facts come from the GOG
best-effort decompile (`BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/
ghidrecomp/.../decomps/FUN_<addr>.c`) and the GOG exe bytes. A GOG address
listed here still needs a live-PID byte check before a patch relies on it.

## Where the cap comes from

The cap is the team slot table, not the menu drawing.

| Fact | Evidence |
|---|---|
| `Team::teamSlot` is a fixed array at `Team+0`; `GameObject::teamSlot` (int, `+364` in 1.5) is the object's index into it. | `types.txt:57021`, `types.txt:54714` |
| Slot ranges are packed: player 0, recycler 1, factory 2, armory 3, constructor 4, offense 5-14, defense 15-24, utility 25-34, beacon 35-44, power 45-54, comm 55-59, repair 60-64, supply 65-69, silo 70-74, barracks 75-79, gun tower 80-89, `MAX_TEAMMATES` 90. | `types.txt:52145-52173` |
| GOG Redux keeps these values: the Lua `TeamSlot` {value, name} table at file offset `0x4E664C` holds 5 → `MIN_OFFENSE` (string `0x0087C010`) and 14 → `MAX_OFFENSE`, through 89 → `MAX_GUNTOWER`. | GOG exe bytes, file offsets `0x4E6624`-`0x4E66F4` (file-offset dump of the shipping GOG exe) |
| `Team::FirstEmptySlot(min, max)` returns the first null slot in the range, or -1. GOG: `0x005E0F90`. | 1.5 `004b1c2e_Team_FirstEmptySlot.c:17`; GOG `FUN_005e0f90.c` |
| A new object takes its class's range (`categoryMin/Max`); when the range is full it gets `teamSlot = -1`. It still exists, but no menu entry shows it (and `Craft::Simulate` retries the slot every tick, see option B). | 1.5 `00496c94_GameObject_Init.c:25-30`, `all_decompiled.c:156844-156853` |
| Build gate: the Producer greys out a unit whose range is full. GOG `Producer::UpdateModeList` `0x005AE660` reads the range from the class at `+0x13C/+0x140` and calls `0x005E0F90`. | 1.5 `004aaefc_Producer_UpdateModeList.c:116`; GOG `FUN_005ae660.c:69-74` |
| `TeamHasFreeSlot` applies the same gate to pilots taking empty vehicles and to Barracks. | 1.5 `00406886_TeamHasFreeSlot.c:21`, `004068d8_GetEmptyVehicle.c:48`, `00482670_Barracks_Simulate.c:70` |
| The unit panel lists `teamSlot[minSlot..maxSlot]` from the `MENU_ITEM` table (9 entries of 16 bytes) and maps keys 1-0 through `BUTTON_MAP`. There are 10 key sprites (`NUM_KEY`, 0x50 bytes). | 1.5 `004c4998_ControlPanel_Render.c:555`, `:906-918`, `:286`; `004c3afe_ControlPanel_Init.c:50,56` |
| Nav-beacon code hard-codes the beacon range (`teamSlot - 0x23 < 10`; GOG `< 0x23 || > 0x2c`). | 1.5 `004c4998_ControlPanel_Render.c:400`; GOG `FUN_004a08e0.c:548` |
| F-groups have no 10-unit cap: GOG `ControlPanel` (global `0x00978E20`) holds `groupNum[10]` at `+0xFC4` and `groupList[10][91]` at `+0x18C` (0xE38 bytes; 1.5 used 90). | GOG `FUN_004a7440.c` (Save), `FUN_004a0020.c` (Init); 1.5 `004c3afe_ControlPanel_Init.c:25`; global address as used in `src/patches/group_strip.cpp` |
| GameObject cleanup frees the slot (`SetSlot(..., null)`, `teamSlot = -1`). | 1.5 `all_decompiled.c:182163-182167` |

UNVERIFIED:
- Where each class's `categoryMin/Max` is first set. 1.5 only shows it
  copied from the base class (`all_decompiled.c:189591-189592`).
- That `GameObject::Save` stores no slot, so slots are reassigned in object
  order on load. A grep of 1.5 `GameObject::Save`
  (`all_decompiled.c:182953+`) found no slot field.
- That `SetTeam` re-slots the object through `Cleanup` and `Init`. It calls
  two vtable entries (`all_decompiled.c:182094-182098`).
- The GOG address of `MENU_ITEM`.
- That rewriting `teamSlot` during a page swap keeps `FlushLists` and
  `Cleanup` consistent, and what Lua `GetTeamSlot` returns for a unit with
  slot -1.

## Options

### C: widen the ranges natively (for example 20 per category). Not recommended.

There are still only 10 buttons and 10 key sprites, so units 11-20 would
still need a page UI. What this adds over B is correctness: Lua
`GetTeamSlot`, mission "units left" checks (`FirstFilledSlot(MIN_OFFENSE,
MAX_OFFENSE)`, e.g. `MissionSourceCode/Inst04Mission.cpp:201`), the pilot and
Barracks gates and multiplayer would all see every unit natively.

Cost: about 175 slots instead of 90, which means:
- relocating `Team::teamSlot`;
- resizing the ControlPanel select and group arrays, which are fixed at 91;
- renumbering the Lua `TeamSlot` table, `MENU_ITEM`, every class range and
  every hard-coded range number (such as the beacon checks above);
- breaking scripts that use slot numbers instead of names, and possibly
  saves.

Weeks of work with crash risk.

### A: lift the build cap, and overflow units go to F-groups (~1 day)

- Let `Producer::UpdateModeList` (`producer_build_menu.cpp` already replaces
  it) and `TeamHasFreeSlot` allow offense builds up to a configurable total
  N.
- Extra units get the stock `teamSlot = -1`.
- `AutoGroupNewUnits` already files new units into F-groups, which have no
  10-unit cap (`src/patches/auto_group_new_units.cpp`;
  `Docs/PRODUCER_RALLY_POINTS.md:428-505`). It is off by default and single
  player only.

Gap: extra units are missing from the key-2 menu.

### B: A plus an Offensive page 2 (~3-5 days plus live tests). Recommended if wanted.

1. OpenShim keeps a list of the local user team's offense units that have no
   slot. A post-hook on `GameObject::Init` adds a unit when it ends with
   `teamSlot == -1` and an offense range. A `GameObject::Cleanup` hook drops
   dead units.
2. A page key swaps the list into `teamSlot[5..14]` and rewrites each
   object's `teamSlot` field, so `Cleanup` and `FlushLists` stay consistent.
   The stock panel then draws page 2 with no render change.
3. A "Page 2/2" label uses the HUD text primitives in `hud_gauge_overlay`.

Rules and risks:
- Keep page 1 full before filling page 2, so stock "no offensive units left"
  checks still work.
- Lua `GetTeamSlot` sees only the page on screen. EXU could add an
  all-offense query.
- Slots are not only UI state. `Craft::Simulate` re-claims a free slot every
  tick for any craft of a team with `teamSlot == -1` whose class range is
  above 4 (`FirstEmptySlot` then `SetSlot`; 1.5 `all_decompiled.c:156844-156853`).
  So a unit swapped out to -1 grabs the next empty slot by itself, and holes
  on page 1 refill from overflow on their own. The swap must suppress this
  (hook that path, or keep swapped-out units on a non-negative virtual slot).
  This runs in the sim, so it affects multiplayer determinism.
- Other `FirstEmptySlot` callers in 1.5: `UserProcess::Execute`
  (`all_decompiled.c:122299`), `Armory::UpdateModeList` (`:143560`),
  `ConstructionRig::UpdateModeList` (`:154056`), `PowerUp::Init` (`:214304`),
  plus the Producer, `Dispenser` and `ObjectLobber` paths.
- Ship it for single player first; multiplayer needs its own test.

## How BZ2/BZCC does it, and the recommended design (D)

Source: the PDB-less BZCC decompile in `Battlezone_Source/BZ2/_analysis/
global_decompile/bzcc_battlezone2_20190509/`. Its function names come from
the BZ2 1.3 PDB by call-graph matching, so they are strong inference, not
proof.

BZCC has no per-category cap on owned units. The cap is the F-group panel:
- 10 groups per team, each holding at most 10 units, built plus queued
  (`Init-005a40e7.c:33-34`; `FirstMatchGroup-005a4e03.c`).
- A new unit joins the first group of the same class with room, otherwise
  the first empty group (`SetBestGroup-004da8b0.c:19-23`). The group is
  chosen when the build is queued and applied when it finishes
  (`QueueBuild-0054d683.c:67`, `FinishBuild-0054c610.c:42`).
- When no group can take the unit, the factory refuses the build for a
  human team. AI teams build ungrouped (`QueueBuild-0054d683.c:66-72`).
- The HUD shows each group's icon and 10 lights coloured by unit health,
  with grey lights for queued builds (`UpdateStatus-005a356a.c`).

D: the same model on top of BZR's existing pieces (~1-2 days):
1. Lift the offense build gate (option A) up to a configurable total.
   Overflow units get `teamSlot = -1`.
2. Use the BZCC rule for the gate: a build is allowed while
   `AutoGroupNewUnits` can place it (same-ODF group with room, else an empty
   group). The cap then follows from groups x group size, so no separate
   number is needed.
3. Turn `AutoGroupNewUnits` on whenever the cap is lifted. `GroupStrip`
   already draws the groups.
4. Keep the stock key-2 menu as "first 10". `Craft::Simulate` re-claims free
   slots every tick (option B), so when a listed unit dies an overflow unit
   takes its place with no OpenShim code, and stock "units left" checks keep
   working.

Single player first. The build gate runs in the sim, so multiplayer needs
every machine to run the same rule.

UNVERIFIED: what BZCC's class key `objClass+0x61c` is (ODF identity or
category); BZCC hop-in grouping.
