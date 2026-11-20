# Mobile repair unit (`classLabel = "mru"`)

Doc of record for the "Nightingale" class. Research, decisions and the full
plan: `Docs/NIGHTINGALE_RESEARCH.md` (sections 4a, 5, 6, 7). This build
covers plan steps 1-6:

1. the `mru` class alias with the `[MruClass]` key parse;
2. three command-menu entries (Drop Repair, Drop Ammo, Deploy);
3. a native pod drop with a cooldown, paid from the MRU's ammo gauge;
4. Deploy / Undeploy with a native deployed flag; a deployed MRU holds
   position;
5. a per-MRU radius service tick (repair and reload), single player only;
6. Drop Repair / Drop Ammo wired to step 3.

Step 7 (converting Resurgence's `avmru`/`svmru`) is out of scope: they stay
unchanged (research section 7.2). Test ODFs are below.

**Options.**
- The class alias has no ini option. An ODF without `classLabel = "mru"` is
  untouched. Kill switch `OPENSHIM_DISABLE_MRU_CLASS=1`: `mru` is then an
  unknown classLabel, as in stock Redux.
- The menu entries and all gameplay need `[SinglePlayer] MruGameplay = 1`
  (default 0, read once at install) and a single-player session. Kill switch
  `OPENSHIM_DISABLE_MRU_GAMEPLAY=1`. Off, an MRU is a plain hover craft with
  the stock menu and no service (this replaces the step 1-2 probe, which drew
  the entries without an option).

Status: implemented, not live-tested. Every behaviour below that needs the
game is UNVERIFIED until the live checklist at the end passes.

## ODF

```ini
[GameObjectClass]
classLabel = "mru"
maxAmmo = 2000            ; the gauge every cost below is paid from
; everything else as for a hover craft

[HoverCraftClass]
; the stock hover keys

[MruClass]
; all optional
serviceRadius = 60.0      ; metres; 0 = no service (default 0)
serviceInterval = 1.0     ; seconds per service tick (default 1.0, floor 0.05)
repairPerTick = 100       ; health per unit per tick (default 100)
reloadPerTick = 50        ; ammo per unit per tick (default 50)
ammoPerRepair = 1         ; gauge cost per health point, 0 = free (default 1)
ammoPerReload = 1         ; gauge cost per ammo point, 0 = free (default 1)
serviceSelf = 0           ; may it repair itself (default 0)
serviceDeployed = 1       ; service only while deployed (default 1)
podCooldown = 30.0        ; seconds between pod drops (default 30)
repairPodClass = "repamine" ; pod ODF for Drop Repair (default unset)
ammoPodClass = "ammomine"   ; pod ODF for Drop Ammo (default unset)
ammoPerRepairPod = 0      ; gauge cost per pod, 0 = free (default 0)
ammoPerAmmoPod = 0
```

Parse rules (include/mru_class_policy.h, tested by
tests/mru_class_policy_tests.cpp):

- **Section present** = at least one of the keys above has a value. The
  ParameterDB has no section lookup, so an `[MruClass]` header with no known
  key reads as absent. Without the section the unit is a plain hover with
  the label `mru`: stock menu, no gameplay.
- Numbers must be finite and not negative, else the default stands;
  `serviceInterval` is floored at 0.05 s. Booleans are integers (0 off).
- Pod class names: quotes optional; longer than 15 characters is dropped
  with a warning.
- Not inherited: the keys are read from the ODF file itself, as tracked's
  `[TrackedClass]`.

## Menu

After the stock `HoverCraft::UpdateModeList` (0x004EBD60) fill, an MRU
object's menu gets:

| Slot | Entry | Mode id reused | Stock name of that id | Enabled when |
|---|---|---|---|---|
| 7 | Drop Repair | 0xB | Go To Geyser | pod named, pod class found, cooldown over, gauge >= pod cost |
| 8 | Drop Ammo | 0xF | Lay Mines | same, for the ammo pod |
| 9 | Deploy / Undeploy | 0x4 | Drop Off | always |

The ids are ones the hover menu never shows. They are below 0x1B, so
`ControlPanel::Render` draws their label. None of them opens a submenu: only
10, 0xE and 0x11 do (FUN_004a08e0.c lines 1359-1371). Deploy (4) sits in
slot 9, so it never shares a slot with the Howitzer's slot-7 Drop Off.
Craft::Simulate calls UpdateModeList every frame for a unit on the user's
team (`obj+0x174 == [0x00917B00]`, FUN_004ab380.c lines 326-328), so the
enabled bits follow the cooldown and the gauge.

Labels come from `ModeLabelDecide` (rts_commands.cpp, the `ModeLabelThunk`
redirect at 0x004A57BE) via `ShimText("openshim_ui:mru_drop_repair_label" /
"mru_drop_ammo_label" / "mru_deploy_label" / "mru_undeploy_label")`, only
while the selection holds an MRU unit. Deploy reads **Undeploy** when every
MRU in the selection is deployed.

A pick goes through `DispatchHook` (0x004A512A), which calls
`NoteMruMenuPick` for every selected commandable unit. A pick of one of the
three ids that sits in its MRU slot is **consumed**, enabled or not, so its
reused id never reaches the stock `DispatchMode`:

- **Deploy** on an undeployed MRU sets the deployed flag and gives
  `GameObject::SetCommand(CMD_STOP)` (row `GameObjectSetCommand`,
  0x004DBCE0: what at +0xCC, FUN_004dbce0). On a deployed MRU it clears the
  flag (Undeploy); the unit keeps its Stop until given an order.
- **Drop Repair / Drop Ammo**, when the drop could go now, queue it for the
  unit's next Simulate (as `Dispenser::Trigger` arms and
  `Dispenser::Simulate` builds); otherwise the pick is logged with the
  reason and does nothing.

Stock entries (Follow, Go To Nav, Attack, ...) are logged and dispatched as
stock.

## Gameplay

All of it runs in the MRU vtable copy's Simulate (slot 15), after the stock
Simulate, single player and `MruGameplay = 1` only. In order:

1. **Cooldown.** `cooldownLeft -= dt`, floored at 0. It starts at 0 (ready)
   for a new object. One cooldown is shared by both pod types.
2. **Queued drop.** Re-checked (pod named, found, cooldown, gauge), then:
   - `GameObjectClass` by name (row `GameObjectClassFindByName`, 0x004FF060:
     StringToPrjID then `GameObjectClass::Find`, FUN_004ff060.c lines 7-8;
     it loads the ODF if needed, as Lua BuildObject, FUN_005c82b0.c lines
     11-34). A miss marks that pod failed for the class (its entry stays
     disabled, one warning).
   - The MRU's 64-byte transform (obj76 +0x20) with the posit moved 6 m
     back along the front axis, then `GameObjectClass::Build(matrix, team,
     0, -1, 0)` (resolve `GameObjectClass::Build`, 0x004E1190), team = the
     MRU's team (+0x174). Dispenser passes the same trailing arguments
     (0x004B5FF4-0x004B6017, FUN_004b5da0.c line 79).
   - Unless the pod's class_id (+0x1C) is 2, 7 or 5: `SetVelocity(pod,
     mru+0x12C)` (row `GameObjectSetVelocity`, 0x0046FB20; FUN_004b5da0.c
     lines 80-83).
   - `AiMission::GetCurrent()` (row `AiMissionGetCurrent`, 0x0045CA50)
     vtable +0x1C(pod) (FUN_004b5da0.c lines 85-86).
   - `SetOwner(pod, mru)` (row `GameObjectSetOwner`, 0x0046FC40; line 89).
   - The pod cost through `AddAmmo(mru, -cost)`; the cooldown restarts at
     `podCooldown`.
3. **Deploy hold.** A deployed MRU packs (flag cleared, logged) as soon as
   its pending order `what` (+0xCC) is not CMD_NONE/SELECT/STOP, or its
   current order `what` (+0xAC) leaves that set after having been seen
   idle once since the deploy (the Stop needs a frame to land).
4. **AI deploy hook point** (`AiDeployHook`). Returns "no change": no AI
   rule is built (see "AI deploy" below).
5. **Service tick**, when `serviceRadius > 0` and (deployed, or
   `serviceDeployed = 0`), once per `serviceInterval` (at most one tick per
   frame; a long frame does not queue ticks):
   - Scans the engine object vector (`GameObject::objectList`, at most 4096
     entries) for up to 32 targets: class_id 1 or 6 (helicopter, vehicle:
     the unit test Craft::GetCommand uses, FUN_004ae110.c lines 30-45),
     team > 0 and the MRU's team or an ally (`GameObject::IsAlly`, row
     `RtsPowerIsAlly`, 0x004DB510), inside the 3D radius (obj76 posit
     doubles), health > 0. Itself only with `serviceSelf = 1`. Any order,
     moving or not (research 7.3).
   - Repair: `min(repairPerTick, gauge / ammoPerRepair)` through the Lua
     `AddHealth(handle, float)` worker (row `MruAddHealthByHandle`,
     0x005CCFD0, which calls GameObject::AddHealth 0x004DC030; it clamps to
     max, FUN_004dc030.c lines 8-17). Health is read before and after
     (`MruGetCurHealthByHandle`, 0x005CCF10), so only what was served is
     charged.
   - Reload (not itself): whole ammo, `min(reloadPerTick, gauge /
     ammoPerReload)`, through `AddAmmo(handle, long)` (row
     `MruAddAmmoByHandle`, 0x005CD100, calling GameObject::AddAmmo
     0x004DC0D0: clamps, ignores maxAmmo <= 0, FUN_004dc0d0.c lines 29-37).
     Ammo is read before and after (`MruGetCurAmmoByHandle`, 0x005CD040).
     Ammo is never written raw: it is stored XOR 0x33333333.
   - Drain: `served * cost` accumulates in a fractional carry; whole points
     are taken from the MRU through `AddAmmo(mru, -n)`, capped at the gauge.
     Cost 0 is free and drains nothing.

Player and AI MRUs run the same tick; an AI MRU services only while
deployed (no AI rule deploys it yet) or with `serviceDeployed = 0`.

## How it works

- **Alias.** The `GameObjectClass::Find` label-compare hook
  (pond_class_label.cpp) calls `MatchMruClassLabel` after tracked's match:
  registered `hover` vs ODF `mru` returns equal and arms a thread-local flag.
  The `HoverCraftClass::BuildClass` detour (owned by tracked_vehicle_class.cpp)
  takes the flag before the stock constructor and, afterwards, stamps the
  label pointer "mru" at class +0x18. The 4CC 'HOVR' and the rank stay. It
  then reads `[MruClass]` through the ODF's ParameterDB scope
  (`ParameterDB::OpenScope`, `WeaponPresentation::RawGet`/`PopScope`, the
  resolves tracked uses).
- **Vtable copy.** The `HoverCraftClass::Build` detour gives each object of
  an mru class with the section an OpenShim copy of the 42-slot
  `HoverCraftVtable` (0x0087ABE4). Every slot is a `jmp [stock slot]` thunk,
  so in-place rewrites of the stock table still chain, except:

  | Slot | Stock | Wrapper | Does |
  |---|---|---|---|
  | 0 | 0x004E9EC0 scalar deleting destructor, thiscall(flags) ret 4 | `MruDestructorHook` | erases the per-object state, then the thunk |
  | 15 | 0x004EBFD0 Simulate, thiscall(float dt) ret 4 (GameObject::Simulate calls vtable +0x3C, FUN_004deec0.c lines 71, 103) | `MruSimulateHook` | the thunk, then the gameplay above |
  | 23 | 0x004EBD60 UpdateModeList, thiscall() | `MruUpdateModeListHook` | the thunk, then slots 7-9 via `ModeList::SetMode` (0x0046FA60) |

  The stock hover, APC, Minelayer, Wingman and Tug vtables are never
  written; tracked wraps the same slots in its own, separate copy. An object
  is an MRU by that vptr.
- **State.** Per object (deployed, cooldown, service accumulator, drain
  carry, queued drop), in a map keyed by the object pointer under an SRW
  lock, erased by the slot 0 wrapper. Per class: the parsed config and the
  "pod class not found" flags.
- **Install.** `InstallMruClassIfPossible` runs from the deferred-hook retry
  loop after tracked. It needs tracked installed, the
  `HoverCraftUpdateModeList` and `ModeListSetMode` rows, the three
  ParameterDB resolves, and a live `HoverCraftVtable` whose slot 23 is
  0x004EBD60. Any miss logs one `classLabel=mru not installed` warning and
  leaves `mru` unknown. Gameplay then also needs the option, the rows
  `MruAddHealthByHandle`, `MruAddAmmoByHandle`, `MruGetCurHealthByHandle`,
  `MruGetCurAmmoByHandle`, `GameObjectClassFindByName`,
  `AiMissionGetCurrent`, `GameObjectSetVelocity`, `GameObjectSetOwner`,
  `GameObjectSetCommand`, `RtsPowerIsAlly` (guard bytes checked), the
  resolves `GameObjectClass::Build` and `GameObject::objectList`, and
  `GameObject::GetHandle`; a miss logs `gameplay off: ...` and leaves the
  plain hover menu.
- **Fail closed.** Every engine read, write and call is under SEH, in small
  helpers with no C++ objects inside `__try`. A fault in the slot 7-9 fill
  leaves the stock fill. A class that cannot be stamped stays a plain hover.
  An object whose vptr is not the stock hover table keeps its vptr.

## Decision log

Every gate that decides without a visible effect logs (tag `[MRU]`).
Change-only unless marked "budgeted" (256 lines per process per kind):

- `installed classLabel=mru (...); gameplay on|off (...)`,
  `classLabel=mru not installed: <why>`, `classLabel=mru off
  (OPENSHIM_DISABLE_MRU_CLASS set)`.
- `gameplay off ([SinglePlayer] MruGameplay = 0)`, `gameplay off
  (OPENSHIM_DISABLE_MRU_GAMEPLAY set)`, `gameplay off: an engine row did not
  bind` / `...unresolved`.
- `built ODF <name> as mru class=<p> [MruClass] present|absent ...` (once
  per class build, with every parsed value and the gameplay state).
- `class <p>: objects get the MRU vtable copy ...` / `... no [MruClass]
  section; objects stay plain hover`.
- `menu on (single player)` / `menu and gameplay off (network game)` (when
  the session kind changes).
- `menu probe: obj=.. slot 7 holds stock Cloak/Decloak ...; MRU entry ..
  skipped` (once).
- `menu pick mode=0x.. (<entry>) on mru obj=.. handle=.. pendingWhat=..:
  consumed, deployed|undeployed|already deployed|drop queued ...|<refusal reason>` or `stock
  dispatch` (budgeted). Refusal reasons: `no pod class in [MruClass]`, `pod
  class not found`, `cooldown`, `gauge too low`.
- `obj=.. <entry> refused at drop time: <reason>` (budgeted).
- `obj=.. <entry>: pod "<name>" built|Build returned null|Build
  faulted|built, a follow-up call faulted team=.. at (x, y, z) cost=..`
  (budgeted).
- `class <p>: pod class "<name>" not found; Drop Repair|Ammo stays
  disabled` (warning, once per class and pod).
- `obj=.. deployed (menu|AI rule); Stop order given|faulted`, `obj=..
  undeployed (menu|given a move order|AI rule)` (budgeted).
- `obj=.. service on|off (radius .., serviceRadius 0|deployed|not
  deployed|serviceDeployed 0)` (per object, change-only).
- `obj=.. gauge empty: costed service stops` / `gauge refilled: service
  resumes` (per object, change-only).
- `obj=.. service tick: N unit(s) in range, healed=.. reloaded=..
  drained=.. gauge=..` (budgeted, only when something was served).

## AI deploy

**Decision (user, 2026-11-19): commands only.** An MRU never deploys on its
own. It deploys when ordered to (by the player's Deploy pick), and otherwise
it sits and responds to orders such as move and the pod drops. So there is
no autonomous AI deploy rule. `AiDeployHook` in mru_class.cpp always returns
"no change". It stays as the single place where a rule could go later; a
rule there would have to skip player-team MRUs and keep its own unit's
orders still, or the deploy hold packs it at once.

## Unit panel category

MRUs are listed under **Utility** (team slots 25-34), not Offense (user,
2026-11-19). The class setup writes the class's slot range (+0x13C/+0x140)
right after the hover craft constructor, which copied Offense from its
prototype (1.5 `all_decompiled.c` 189591-189592). The build gate and the unit
panel read that range (GOG `FUN_005ae660.c` lines 69-74). As with other
Utility units, an MRU can't be built while all 10 Utility slots are taken.

Live check: build an MRU and confirm it appears under Utility (F3, keys 1-0),
not Offense, and that Ctrl+Offense does not select it.

## Limits

- Not saved: after a save load an MRU is undeployed with its cooldown ready
  (the per-object state is keyed by the object pointer). The drain carry
  (under one point) is lost too.
- The deploy hold is the Stop order plus "pack on any move order". A
  player piloting a deployed MRU can still drive it; it stays deployed
  (orders, not physics, decide). UNVERIFIED whether the APC/RocketTank AI
  process re-orders a stopped AI MRU and so packs it at once.
- A pod spawns 6 m behind the MRU, at its height (no terrain snap). Whether
  the pod falls, sits or floats, and whether the owner collects its own pod,
  is UNVERIFIED (research 4a(a)).
- The pod is built from inside the MRU's Simulate, the same frame phase as
  Dispenser::Simulate builds from (a weapon's Simulate under its carrier).
  Object-list safety of that is the engine's own pattern, UNVERIFIED for a
  hover's Simulate.
- Service targets are helicopters and vehicles only: not pilots, not
  structures, not powerups. At most 32 per tick, in object-list order.
- Health and ammo of the target are clamped by the engine; a full target is
  scanned but costs nothing.
- The gauge is the MRU's own ammo. An MRU with `maxAmmo = 0` and a
  non-zero cost services nothing. On the player's MRU with an unlimited-ammo
  cheat the engine ignores the negative AddAmmo (FUN_004dc0d0.c lines
  29-37), so the drain is free.
- Single-unit selection is the target. Two MRUs selected together share the
  entries; a pick acts on each. Deploy acts on the selection as one: it
  packs only when every selected MRU is deployed (the label then reads
  Undeploy), otherwise it deploys the packed ones and leaves the rest. A
  mixed selection loses the entries in the stock `Intersect`; if a reused id
  (Go To Geyser 0xB, Lay Mines 0xF, Drop Off 0x4) is picked there, the
  non-MRU units whose menu holds it still get it, and every MRU pick ends
  that unit's RTS order queue.
- Cloak-capable MRUs: the stock fill puts Cloak/Decloak (0x18/0x19) in slot
  7 (FUN_004aefa0(7)); the shim leaves it there and skips Drop Repair on
  that craft (logged once).
- The MRU vtable is a different pointer from `HoverCraftVtable`, so code
  that recognises hover craft by that exact vtable does not see MRUs.
  `satellite_visibility.cpp` (exe-image vtables only) skips them, as it
  skips tracked objects.
- `ModeList::SetMode` clears the active slot when a slot's mode changes; the
  stock fill writes 0 to slots 8-9 and the shim writes the MRU ids every
  call, so an active slot of 7-9 is reset each frame. The entries are
  instant actions, so this is expected to be invisible (UNVERIFIED).
- The thread-local pending flag (set at the label match, taken in
  BuildClass) can leak to the next hover class built on that thread if Find
  bails in between; tracked has the same pattern. Accepted.
- Depends on tracked: if `classLabel=tracked` fails to install, `mru` does
  too.

## Test ODF (live)

`svmruprb.odf`, a copy of Resurgence's `svmru.odf`
(`addon\Resurgence\svmru.odf`). Changes: `classLabel = "mru"`, the AI
names, the stale `[MineLayerClass]` block removed, and an `[MruClass]`
section added. The AI is the `RocketTankFriend`/`RocketTankEnemy` pair that
stock-label `hover` units ship with (`addon\ISDF Chronicles\hdrone.odf`).
Resurgence's `APCFriend`/`APCEnemy` was written for a Tug object, and
whether the APC process copes with a plain HoverCraft object is UNVERIFIED
(NIGHTINGALE_RESEARCH.md section 3). Swap it back in as a second
configuration once the menu checks pass. It must sit where the mission can load
it, with the Resurgence assets it uses (`grepa`, `gammo`, the svmru
geometry) available.

```ini
[GameObjectClass]
baseName = "svmru"
classLabel = "mru"
scrapValue = 6
scrapCost = 8
buildTime = 8
maxHealth = 3000
maxAmmo = 2000
unitName = "MRU probe"
aiName = "RocketTankFriend"
aiName2 = "RocketTankEnemy"
heatSignature = 1.0
imageSignature = 2.0
radarSignature = 0.1

weaponHard1 = "GS1"
weaponName1 = "grepa"
weaponHard2 = "GS2"
weaponName2 = "gammo"
weaponMask = 00011

[CraftClass]
rangeScan = 200.0
periodScan = 0.0
velocJam = 0.0

selectWaitMsg = "vhosmoa.wav"
selectUser1Msg = "vhossea.wav"
selectGoMsg = "vhosmoe.wav"
selectOtherMsg = "vhosmoa.wav"
selectUser2Msg = "vhossea.wav"

user1Msg = "vhossec.wav"
followMsg = "vhosmob.wav"
followMeMsg = "vhosmob.wav"
repairMsg = "vhossea.wav"
reloadMsg = "vhossea.wav"
rescueMsg = "vhosseb.wav"
recycleMsg = "vhossec.wav"
otherMsg = "vhossee.wav"

user2Msg = "svminevb.wav"
diedMsg = "sbetty2.wav"

[HoverCraftClass]
setAltitude = 1.0
accelDragStop = 4.0
accelDragFull = 1.0
alphaTrack = 10.0
alphaDamp = 3.0
pitchPitch = 0.01
pitchThrust = 0.01
rollStrafe = 0.05
rollSteer = 0.05

velocForward = 15.0
velocReverse = 15.0
velocStrafe = 15.0
accelThrust = 50.0
accelBrake = 50.0
omegaSpin = 3.75
omegaTurn = 2.75
alphaSteer = 7.0
accelJump = 0.0

soundThrust = "avminee0.wav"
soundTurbo = "cvcnste0.wav"

[MruClass]
serviceRadius = 60.0
podCooldown = 30.0
repairPodClass = "repamine"
ammoPodClass = "ammomine"
```

A second copy with the `[MruClass]` section removed (`svmruprn.odf`) checks
the "absent" path.

## Live checklist

Preconditions (a failed precondition is a fixture failure, not a FAIL):

- SP mission; the branch DLL, `scripts\patches.json` and
  `openshim\localization` CSV deployed and hash-checked; `MruGameplay = 1`
  in `[SinglePlayer]`.
- Log shows `[MRU] installed classLabel=mru (...); gameplay on`.
- An own `svmruprb` unit (Lua `BuildObject("svmruprb", 1, ...)` or a
  mission placement); for the drop steps, the pod ODFs `repamine` and
  `ammomine` loadable by the mission (else step 5 checks the "not found"
  path instead).

Steps:

1. Log shows `built ODF svmruprb as mru ... [MruClass] present` with
   serviceRadius=60.0, podCooldown=30.0, repairPodClass=repamine,
   ammoPodClass=ammomine, the rest defaults, `gameplay ... on`; then `class
   ...: objects get the MRU vtable copy`.
2. The unit moves and hovers like svmru.
3. Select the MRU alone: the stock hover entries plus **Drop Repair** (7),
   **Drop Ammo** (8), **Deploy** (9), all enabled at spawn. `[MRU] menu on
   (single player)` once.
4. Order Follow, then pick Drop Repair (mouse, then key 7 after the
   cooldown): one click, no submenu, the selection clears, the unit keeps
   following, `menu pick ... consumed, drop queued`, then `pod "repamine"
   built team=1 at (...)` about 6 m behind the MRU. Drop Repair and Drop
   Ammo grey out for 30 s, then re-enable. A pick during the cooldown logs
   `consumed, cooldown` and does nothing. Note whether the pod falls, sits or
   floats, and whether the MRU picks up its own pod.
5. Drop Ammo: as step 4 with `ammomine`. If the pod ODF is missing: one
   `pod class "ammomine" not found; Drop Ammo stays disabled` warning and the
   entry stays grey.
6. Pick Deploy: `deployed (menu); Stop order given`, the unit stops, the
   entry now reads **Undeploy**, `service on (radius 60.0, deployed)`.
7. Damage two own units (and empty some ammo), bring them within 60 m of the
   deployed MRU, one moving: each second `service tick: N unit(s) ...
   healed=.. reloaded=.. drained=..`; their health and ammo bars rise to max;
   the MRU's ammo bar falls by the served amount. A unit at 61 m+ and an
   enemy unit are not serviced. A pilot on foot is not serviced.
8. Give the deployed MRU a Go To: `undeployed (given a move order)`,
   `service off`, the label reads Deploy again. Deploy again, then pick
   Undeploy: `undeployed (menu)`.
9. Gauge: let the service run until the MRU's ammo is 0: `gauge empty:
   costed service stops`, no more healing. Reload the MRU at a supply point:
   `gauge refilled`.
10. Free service: an ODF copy with `ammoPerRepair = 0`, `ammoPerReload = 0`:
    the MRU's ammo does not move while servicing.
11. AI MRU: an enemy-team `svmruprb` with `serviceDeployed = 0` services its
    own team's units in range while moving; with the default it services
    nothing (no AI deploy rule). Note whether its AI process keeps
    re-ordering it.
12. Save, then load: the MRU is undeployed, the drops are ready, no crash.
    Destroy a deployed MRU: no crash; the next MRU built works.
13. Select a stock Minelayer: its menu still reads Lay Mines (not Drop Ammo),
    and laying mines works. A Howitzer's slot 7 still reads Drop Off.
14. Select the MRU together with a scout: the MRU entries are gone (stock
    Intersect), and the rest of the menu works.
15. `svmruprn` (no section): `[MruClass] absent`, `no [MruClass] section`,
    stock hover menu, no service.
16. `MruGameplay = 0`: `gameplay off ([SinglePlayer] MruGameplay = 0)`;
    `svmruprb` has the stock hover menu, no service, and its picks are not
    logged. Same with `OPENSHIM_DISABLE_MRU_GAMEPLAY=1`.
17. With `OPENSHIM_DISABLE_MRU_CLASS=1`: `classLabel=mru off`, and
    `svmruprb` behaves as an unknown classLabel does in stock Redux.

UNVERIFIED until this runs: the entries draw and click without a submenu,
the labels, a consumed pick leaves other orders alone, the pod spawn and its
pickup, the deploy hold under the hover AI process, the service amounts, the
gauge drain, save/load, and that loading an `mru` ODF without the shim fails
like any unknown label.
