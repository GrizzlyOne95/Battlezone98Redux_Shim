# Mobile repair unit (`classLabel = "mru"`)

Doc of record for the "Nightingale" class. Research, decisions and the full
plan: `Docs/NIGHTINGALE_RESEARCH.md`. This build covers plan steps 1-2 only:

1. the `mru` class alias with the `[MruClass]` key parse, and
2. a **log-only menu probe**: three extra command-menu entries (Drop Repair,
   Drop Ammo, Deploy) that are drawn, relabelled and logged when picked, but
   do nothing.

There is no openshim.ini option. An ODF without `classLabel = "mru"` is
untouched. Kill switch: set the environment variable
`OPENSHIM_DISABLE_MRU_CLASS=1`; `mru` is then an unknown classLabel, as in
stock Redux.

Status: implemented, not live-tested. Every behaviour below that needs the
game is UNVERIFIED until the live checklist at the end passes.

## ODF

```ini
[GameObjectClass]
classLabel = "mru"
; everything else as for a hover craft

[HoverCraftClass]
; the stock hover keys

[MruClass]
; all optional; nothing below is used yet (parsed and logged only)
serviceRadius = 60.0      ; metres; 0 = no service (default 0)
serviceInterval = 1.0     ; seconds per service tick (default 1.0, floor 0.05)
repairPerTick = 100       ; health per unit per tick (default 100)
reloadPerTick = 50        ; ammo per unit per tick (default 50)
ammoPerRepair = 1         ; gauge cost per health point, 0 = free (default 1)
ammoPerReload = 1         ; gauge cost per ammo point, 0 = free (default 1)
serviceSelf = 0           ; may it service itself (default 0)
serviceDeployed = 1       ; service only while deployed (default 1)
podCooldown = 30.0        ; seconds between pod drops (default 30)
repairPodClass = "repamine" ; pod ODF for Drop Repair (default unset)
ammoPodClass = "ammomine"   ; pod ODF for Drop Ammo (default unset)
ammoPerRepairPod = 0      ; gauge cost per pod, 0 = free (default 0)
ammoPerAmmoPod = 0
```

Rules (include/mru_class_policy.h, tested by tests/mru_class_policy_tests.cpp):

- **Section present** = at least one of the keys above has a value. The
  ParameterDB has no section lookup, so an `[MruClass]` header with no known
  key reads as absent. Without the section the unit is a plain hover with
  the label `mru`: stock menu, no probe.
- Numbers must be finite and not negative, else the default stands;
  `serviceInterval` is floored at 0.05 s. Booleans are integers (0 off).
- Pod class names: quotes optional; longer than 15 characters is dropped
  with a warning.
- Not inherited: the keys are read from the ODF file itself, as tracked's
  `[TrackedClass]`.

## Menu probe

After the stock `HoverCraft::UpdateModeList` (0x004EBD60) fill, an MRU
object's menu gets:

| Slot | Entry | Mode id reused | Stock name of that id |
|---|---|---|---|
| 7 | Drop Repair | 0xB | Go To Geyser |
| 8 | Drop Ammo | 0xF | Lay Mines |
| 9 | Deploy | 0x4 | Drop Off |

All three are enabled for the probe. The ids are ones the hover menu never
shows. They are below 0x1B, so `ControlPanel::Render` draws their label.
None of them opens a submenu: only 10, 0xE and 0x11 do (FUN_004a08e0.c lines
1359-1371). Deploy (4) sits in slot 9, so it never shares a slot with the
Howitzer's slot-7 Drop Off. The labels come from `ModeLabelDecide`
(rts_commands.cpp, the `ModeLabelThunk` redirect at 0x004A57BE) via
`ShimText("openshim_ui:mru_drop_repair_label" / "mru_drop_ammo_label" /
"mru_deploy_label")`, only while the selection holds an MRU unit.

A pick goes through `DispatchHook` (0x004A512A). For every selected
commandable MRU unit, the shim logs one `[MRU] menu pick` line with the
mode, the unit and its pending order `what` (+0xCC). A pick of one of the
three MRU entries that is offered in its slot is **consumed**: the hook
returns true without calling the stock `DispatchMode`, so no `ExecuteMode`,
no order and no command ping. The selection clears, as after a stock pick.
Stock entries (Follow, Go To Nav, Attack, ...) are logged and then dispatched
as stock.

Single player only. In a network game the vtable copy's slot 23 runs the
stock fill only (stock hover menu), labels are stock, and picks are not
logged.

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
  `HoverCraftVtable` (0x0087ABE4). Every slot is a `jmp [stock slot]` thunk
  except slot 23 (UpdateModeList), which runs the stock slot through its
  thunk and then calls `ModeList::SetMode` (0x0046FA60) for slots 7-9. The
  stock hover, APC, Minelayer, Wingman and Tug vtables are never written.
  An object is an MRU by that vptr. No per-object state, so no destructor
  hook.
- **Install.** `InstallMruClassIfPossible` runs from the deferred-hook retry
  loop after tracked. It needs tracked installed (it shares tracked's detours
  and pond's compare hook), the `HoverCraftUpdateModeList` and
  `ModeListSetMode` engine rows (guard bytes checked), the three ParameterDB
  resolves, and a live `HoverCraftVtable` whose slot 23 is 0x004EBD60. Any
  miss logs one `classLabel=mru not installed` warning and leaves `mru`
  unknown.
- **Fail closed.** Every engine read and write is under SEH. A fault in the
  slot 7-9 fill leaves the stock fill. A class that cannot be stamped stays
  a plain hover. An object whose vptr is not the stock hover table keeps
  its vptr.

Log lines (tag `[MRU]`), all change-only except the per-pick line (capped at
256 per process):

- `installed classLabel=mru (...)` / `classLabel=mru not installed: <why>` /
  `classLabel=mru off (OPENSHIM_DISABLE_MRU_CLASS set)`
- `built ODF <name> as mru class=<p> [MruClass] present|absent ...` (once
  per class build, with every parsed value)
- `class <p>: objects get the MRU vtable copy ...` or `... no [MruClass]
  section; objects stay plain hover` (when the decision for that class
  changes)
- `menu probe on (single player)` / `menu probe off (network game)` (when
  the session kind changes)
- `menu pick mode=0x.. (Drop Repair|Drop Ammo|Deploy|stock entry) on mru
  obj=.. handle=.. pendingWhat=..: probe only, consumed ... | stock dispatch`

## Limits (this step)

- Picks do nothing: no pod, no deploy flag, no service tick (plan steps 3-6).
- Slot 7 is Cloak/Decloak on a cloak-capable craft (`FUN_004aefa0`, modes
  0x18/0x19). On an MRU the probe overwrites it, so an MRU loses that toggle.
- Single-unit selection is the target. Two MRUs selected together share the
  entries (same ids in the same slots), and a pick is logged and consumed
  for each. A mixed selection loses the entries in the stock `Intersect`.
- The MRU vtable is a different pointer from `HoverCraftVtable`, so code
  that recognises hover craft by that exact vtable (as tracked objects
  already are) does not see MRUs.
- `ModeList::SetMode` clears the active slot when a slot's mode changes. The
  stock fill writes 0 to slots 8-9 and our fill writes the MRU ids, so an
  active slot of 7-9 is reset every UpdateModeList. The probe sets no
  active slot, so this is expected to be invisible (UNVERIFIED).
- How often the engine calls UpdateModeList: UNVERIFIED.
- Depends on tracked: if `classLabel=tracked` fails to install, `mru` does
  too.

- Cloak-capable MRUs: the stock fill puts Cloak/Decloak (0x18/0x19) in slot 7 (GOG
  HoverCraft::UpdateModeList 0x004EBD60 via FUN_004aefa0(7)). The probe leaves it there and skips Drop
  Repair on that craft (logged once). A final layout for cloak MRUs is a later decision.
- The thread-local pending flag (set at the label match, taken in BuildClass) can leak to the next
  hover class built on that thread if Find bails in between; tracked has the same pattern. Accepted.
- The MRU vptr points into the DLL, so `satellite_visibility.cpp` (which trusts only exe-image vtables)
  skips MRU objects, as it does tracked objects.
- The consumed pick skips the stock `DispatchMode`; whether stock dispatch has other side effects
  (sound, menu close) is checked in live step 4 (UNVERIFIED).

## Test ODF (live probe)

`svmruprb.odf`, a copy of Resurgence's `svmru.odf`
(`addon\Resurgence\svmru.odf`). Changes: `classLabel = "mru"`, the AI
names, the stale `[MineLayerClass]` block removed, and an `[MruClass]`
section added. The AI is the `RocketTankFriend`/`RocketTankEnemy` pair that
stock-label `hover` units ship with (`addon\ISDF Chronicles\hdrone.odf`).
Resurgence's `APCFriend`/`APCEnemy` was written for a Tug object, and
whether the APC process copes with a plain HoverCraft object is UNVERIFIED
(NIGHTINGALE_RESEARCH.md section 3). Swap it back in as a second
configuration once the probe passes. It must sit where the mission can load
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

Preconditions: SP mission, the branch DLL and `scripts\patches.json`
deployed and hash-checked, `[MRU] installed classLabel=mru` in the log, an
own `svmruprb` unit spawned (Lua `BuildObject("svmruprb", 1, ...)` or a
mission placement). A failed precondition is a fixture failure, not a FAIL.

1. Log shows `built ODF svmruprb as mru ... [MruClass] present` with
   serviceRadius=60.0, podCooldown=30.0, repairPodClass=repamine,
   ammoPodClass=ammomine, the rest defaults; then `class ...: objects get
   the MRU vtable copy`.
2. The unit moves and hovers like svmru.
3. Select the MRU alone: the menu shows the stock hover entries (Go To,
   Follow, Go To Nav, Attack, ..., Recycle) plus **Drop Repair** (7),
   **Drop Ammo** (8), **Deploy** (9), all enabled. `[MRU] menu probe on
   (single player)` once.
4. Order Follow (stock), then pick Drop Repair, Drop Ammo and Deploy (mouse
   and number keys 7/8/9). For each: one click sound, no submenu, the
   selection clears, the unit keeps following, one `[MRU] menu pick ...
   consumed` line, and `pendingWhat` stays the Follow order's value.
5. Pick Follow and Go To Nav on the MRU: they work as stock, with `stock
   dispatch` log lines.
6. Select a stock Minelayer: its menu still reads Lay Mines (not Drop Ammo),
   and laying mines works. Select a Howitzer: its slot 7 still reads Drop
   Off. A scout and an APC have no slots 7-9 entries.
7. Select the MRU together with a scout: the MRU entries are gone (stock
   Intersect), and the rest of the menu works.
8. `svmruprn` (no section): `[MruClass] absent`, `no [MruClass] section`,
   stock hover menu, no pick log.
9. With `OPENSHIM_DISABLE_MRU_CLASS=1`: `classLabel=mru off` in the log, and
   `svmruprb` behaves as an unknown classLabel does in stock Redux.

UNVERIFIED until this runs: that the three entries draw and click without a
submenu, the labels, that a consumed pick leaves the order alone, the
UpdateModeList call rate, whether the APC process copes with a HoverCraft
object, and that loading an `mru` ODF without the shim fails like any
unknown label.
