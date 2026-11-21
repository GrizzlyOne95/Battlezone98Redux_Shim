# Nightingale repair vehicle (class label "mru"): research

Feature queue item 13 (Docs/FEATURE_WORK_QUEUE.md). Research only; no code, no live test. Date 2026-11-19, GOG Redux 2.2.301.
Evidence tags: **1.5** = `Battlezone_Source\BZ1\1.5\functions\<hi4>\<addr>_<name>.c` (PDB-named BZ1 1.5 decompile, addresses differ from GOG);
**GOG** = `...\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps\FUN_<addr>.c`;
**odf** = `<game>\addon\Resurgence\`; **BZ2** = `Battlezone_Source\BZ2\_analysis\global_decompile\bzone_b131p_best_effort\results\bins\bzone.exe-6f4367\decomps\<name>.c` (PDB-matched BZ2 1.3 beta). Anything without a citation is UNVERIFIED.

## Executive conclusion
- **Prior art exists.** The Resurgence addon ships the MRU-47 "Nightingale" (`avmru`, `svmru`): `avmru.inf:1` reads `MRU-47 "Nightingale" - Mobile Repair Unit`, and `avmru.inf:3-8` says it drops repair and supply pods every 30 seconds, only on a follow command. They are `classLabel = "tug"` hovercraft with two stock dispenser weapons (`weaponName1 = "grepa"`, `weaponName2 = "gammo"`, `svmru.odf`). Related Resurgence utility units: `avcarri` "mobile repair bay" (`utility.odf:7`), `ammobot` (`:9`), `wvscout` "cca service vehicle" (`:12`).
- **Decision (user, 2026-11-19): v1 is a native class `classLabel = "mru"`** that services every friendly unit in a radius while deployed, for player and AI alike, SP only. The stock pod path (Armory builds pods, units drive to them) cannot do this; BZ2's ServiceTruck can, and is the design reference (section 4).
- **Commands are in v1 scope (user, 2026-11-19):** Follow, Go to Nav, Drop Ammo, Drop Repair, Deploy, plus the other hover commands. The undeployed drop is a native cooldown action, not a stock order. **Riskiest unknown: adding three menu entries to an aliased hover class (section 4a).** Probe it first with a log-only experiment before any service code.
- Registration is cheap: alias the hover descriptor like `tracked` (section 2). The service tick itself is new code (M).
- Pool: a finite ammo gauge drawn from the MRU's own ammo, with an ODF value 0 meaning infinite.

## 1. How stock service works (BZ98)
**Pods.** Repair and ammo pods are powerups: `classLabel = "repairkit"` / `"ammopack"`, `aiName = "PowerUpProcess"`, `healthUp = 1000`, `ammoUp = 500`, `scrapCost = 1` (odf `repamine.odf`, `ammomine.odf`). GOG labels: FUN_004e92f0.c ("repairkit"), FUN_0046d280.c ("ammopack"), FUN_005ab2c0.c ("powerup"). AI class 4CCs: `'RKIT'` 0x524B4954, `'AMMO'` 0x414D4D4F (1.5 `0047ecd6_Armory_GetCommand.c`). `PowerUpProcess::Execute` steers a pod toward its target (1.5 `004585ef_PowerUpProcess_Execute.c`).

**The Armory builds them.** `Armory` has `repairItem`/`reloadItem` (1.5 `0040c623`, `0040c62a`); `CanSendRepair/Reload` need an idle, deployed Armory and `Team::GetScrap >= AdjustedScrapCost(item)` (1.5 `0047e830`, `0047e7eb`). `ArmoryProcess::ChangesState` turns `CMD_GET_REPAIR/RELOAD` into `classtobuild` and the LAUNCH state (1.5 `0040ca51`). Cost: team scrap per pod. The LAUNCH spawn body: UNVERIFIED.

**Who services a unit on GetRepair/GetReload (modes 5 and 6).** `Craft::SetActiveMode` maps mode 5 to `CMD_GET_REPAIR` and `param_1 != 6` is the reload branch (1.5 `0048605a_Craft_SetActiveMode.c:26-30`; ids in include/rts_commands_policy.h:41-42). The unit's process (1.5 `00469853_UnitProcess_ChangesState.c:72-98`) commands team slot 3 (the Armory) to send a pod, else `UnitProcess::DoRepair` drives it to the nearest `'RKIT'` pod within 30 m via `GoGet` (1.5 `00469f68_UnitProcess_DoRepair.c`; same in `TugProcess::DoRepair` `004667b6`). No stock BZ98 unit services in place. APC "reload" refills soldiers, not ammo (1.5 `0040bf32_APCProcess_DoReload.c`). No `ServiceTruck` in BZ98 (absent from `BZ1\1.5\function_index.tsv`).

**Dispenser weapon** (the only stock pod dropper). `DispenserClass` label "dispenser", keys `objectClass`, `shotDelay` (1.5 `0052d5e5`, `0052d61e`; GOG FUN_004b5910.c). `Dispenser::Simulate` (1.5 `0052d7cb`) needs `curAmmo >= objectClass.maxAmmo` (ammo stored XOR 0x33333333), spends it, builds at the weapon matrix, `SetOwner(carrier)`; in net games only the local owner builds. Resurgence pods have `maxAmmo = 0`, so those drops are free.

## 2. OpenShim building blocks
- **Class alias (tracked pattern).** `GameObjectClass::Find`'s label compare is already hooked by pond (`src/patches/pond_class_label.cpp:370-391`), which calls `MatchTrackedClassLabel` (`tracked_vehicle_class.cpp:2201-2212`: registered `hover` vs ODF `tracked`, sets a pending flag). A `HoverCraftClass::BuildClass` detour builds the stock class, then `StampTrackedClass` writes the label pointer at class `+0x18` (`:623`, const `:92`, hook `:739-747`, install `:2301-2309`); objects are recognised by that pointer (`:423`); ODF keys are read from `[TrackedClass]` during BuildClass (`:491-492`, `:695`); install gates on pond support (`:2218`). Stock hover subclasses share one vtable (`Docs/TRACKED_VEHICLE_SCOPE.md` section 2), so a hover alias needs no new vtable unless Simulate is replaced.
- **Menu.** `RtsCommands` rewrites the unit menu: 11-slot `ModeList` (include/rts_commands_policy.h:28-36), `MergeHook` (`rts_commands.cpp:645`), `DispatchHook` at 0x004A512A (`:702-707`), smart modes 5/6 (`rts_commands_policy.h:56-80`). New mode ids need a `Craft::SetActiveMode` mapping (1.5 `0048605a`): UNVERIFIED. `Docs/NATIVE_UI_FRAMEWORK.md` covers shell screens only. v1 now needs three new entries (section 4a).
- **Heal/ammo primitives.** `GameObject::AddHealth` (1.5 `00495842`), `GameObject::AddAmmo` (`00496d57`), BZ2 uses `Weapon::AddLocalAmmo` per weapon (BZ2 `Simulate-0050eac3.c`). Authority on remote copies: UNVERIFIED (SP only in v1). `armory_repair_pick.cpp:4-9` notes a guest's remote health `+0x204` stays at max, relevant later for MP.
- **Pods in OpenShim:** `mp_daywrecker_armory_collision.cpp` (PowerUp unpack/Simulate, `:7-17`, `:233-246`) only; no pod spawner. Not needed for v1.

## 3. Class base: "mru" aliases hover, not tug
Resurgence MRUs are `classLabel = "tug"` and carry `[HoverCraftClass]` plus a `[MineLayerClass]` block (`svmru.odf:70-72`, `avmru.odf:69`). `TugClass` itself derives from `HoverCraftClass` (ctor calls it, 4CC 0x54554700, label "tug": 1.5 `004b3a36_TugClass_TugClass.c`; object `Tug::Tug` calls `HoverCraft::HoverCraft`, 1.5 `004b2f72`). So the hover keys work under both labels. The `[MineLayerClass]` block looks like a copy-paste leftover (`TugClass`'s ODF ctor reads its own section: 1.5 `004b3ac9`; that it ignores `[MineLayerClass]` is UNVERIFIED). Consequences: (1) aliasing `hover` gives the same movement/physics as the Resurgence units; (2) it drops the tug cargo/pickup logic and `TugProcess`, which an MRU does not need; (3) the Resurgence ODFs would need `classLabel = "mru"` and `aiName` changes to migrate. AI names: Resurgence uses `aiName = "APCFriend"`, `aiName2 = "APCEnemy"` (`svmru.odf:10-11`, `avmru.odf:10-11`), i.e. the APC process, not tug AI, so the MRU is already driven by APC-style AI. Whether the APC process copes with an MRU that deploys and idles: UNVERIFIED.

## 4. BZ2 ServiceTruck as design reference (b131p decompile, UNVERIFIED for BZCC)
- Classes `ServiceTruck` ("CLASS_SERVICE") and `ServiceTruckH` ("CLASS_SERVICEH") (ScriptUtils.h:1521-1522 in `BZ2_1.3.7_a130DLLSource`; `ServiceTruckClass::Build` BZ2 `Build-0050f4f1.c`). Class overrides: `Simulate-0050eac3.c`, `GetCommand-0050f1cc.c`, `SetActiveMode-0050f2ab.c`, `UpdateModeList-0050f2c4.c`, `CouldService-0050f473.c`.
- **One target at a time, continuous service.** `Simulate` keeps a target handle (`+0x530`), checks distance to a nozzle point (class `+0x37a0` offset along the truck's heading) against `+0x37a4` plus the target's radius, and only then heals/reloads (`Simulate-0050eac3.c:101-122`). Amounts per tick are class rates (`+0x37a8`, `+0x37ac`, `+0x37b0`) times `dt`, scaled by the target's missing health fraction, then `GameObject::AddHealth` and `Weapon::AddLocalAmmo` on each of 5 weapon slots (`:123-146`). A GAS sound/effect plays while serving (`:158-170`, effect name at class `+0x37b8`). Which key is health vs ammo: UNVERIFIED (hashed names).
- **No pool seen.** No decrement of the truck's own supply appears in the Simulate body read, so BZ2 service is effectively infinite; finite pool is a new rule for OpenShim.
- **Target choice.** `ServiceProcess::ChooseServiceTarget` (`ChooseServiceTarget-0048cf83.c:55-110`) runs only in states 3 or 8, searches `GameObjectRange` within class radius `+0x37b4`, requires same team unless a class flag (`+0x3845`) allows others, and uses class flags `+0x3840..0x3844` through `CouldService` (`CouldService-0050f473.c`) to say what may be serviced (health/ammo/etc.; flag meaning UNVERIFIED). The best candidate maximises a score: (health term + ammo term) * distance term, where the distance term is `1 - dist^2/range^2` (`ChooseServiceTarget-0048cf83.c:92-97`), the health term is `1 - ratio^2` (only if the class health rate `+0x37a8` is non-zero), the ammo term is the mean of `1 - (cur/max)^2` over the 5 weapons (rate `+0x37b0`), and the highest score wins (`:132-136`). So BZ2 favours near and badly damaged or empty units; a radius pulse that serves all is a simplification.
- **Command/UI.** Servicing is order-driven: `CMD` 0x1d clears after `DoService` completes (`DoService-00492efc.c`), and a "Service" panel button is enabled by `CommandPanel::CanService` for friendly targets (`CanService-0052aa19.c`). BZ2 has no deploy gate: the truck serves while parked next to a target.
- Take-away for OpenShim: a radius pulse that heals/reloads every unit in range is a simplification of BZ2 (one target, order-driven); acceptable for v1 since the user asked for automatic service when deployed.

## 4a. Commands, pod drops and coexistence (user requirement 2026-11-19)
Requirement: the MRU drops pods on the fly, undeployed, on a cooldown; menu = Follow, Go to Nav, Drop Ammo, Drop Repair, Deploy, plus the other native hover commands.

**(a) Undeployed drop on a cooldown.** Stock model to copy: `Dispenser::Simulate` (1.5 `0052d7cb`): a per-weapon `shotTimer` advanced by `dt` and reduced by `shotDelay` after a shot (`shotDelay` is a [DispenserClass] key, 1.5 `0052d61e`); it requires `curAmmo >= objectClass.maxAmmo`, subtracts that through the carrier's AddAmmo (vtable +0x18, negative amount), builds the pod with `GameObjectClass::Build(class, matrix, team, ...)`, then `SetVelocity` from the carrier and `SetOwner(carrier)`. A weapon drop (Resurgence) is fired through `Dispenser::Trigger` (1.5 `0052d6fa`) from the fire control or AI attack, not from a menu. So for a menu order reuse the **logic**, not the weapon: a native drop function (cooldown check, gauge check, `GameObjectClass::Build` at an offset behind the hull, `SetOwner`). GOG address of `GameObjectClass::Build`: UNVERIFIED (look up before coding). The cooldown lives in a new `[MruClass] podCooldown` (proposal 30 s, from `avmru.inf:3-8`). The drop draws from the same finite ammo gauge (keys in section 5). Whether the owner collects its own pods: UNVERIFIED, live-test.

**(b) Menu entries.**
- The unit menu is the 11-slot ModeList (`GameObject +0x1A4`); `ModeList::SetMode(slot, mode, enabled)` writes an id and an enabled bit (1.5 `0047dcbf_ModeList_SetMode.c`, slot < 0xb).
- Stock hover (`HoverCraft::UpdateModeList`, 1.5 `0049db6c`): slot 0 = mode 1, slot 1 = 2 (Follow), slot 2 = 10 (Go to Nav), slot 3 = 0xe, slot 4 = 7, slot 5 = 5 (Get Repair), slot 6 = 6 (Get Reload), **slots 7, 8, 9 = mode 0, disabled (free)**, slot 10 = 8 (Recycle). APC and Tug use the same layout (1.5 `0047dd60`, `004b31eb`). A class adds an order by overriding `SetActiveMode`: Minelayer puts 0xf in slot 3 and maps it to `CMD_LAY_MINES` (1.5 `0049fa75:18`, `0049fa41`), Tug maps mode 4 to `CMD_DROPOFF` (1.5 `004b30ab`). `Craft::SetActiveMode` ignores unknown ids and returns true (1.5 `0048605a`).
- Rule for "mru": after the stock hover fill, set slots 7, 8, 9 (Drop Repair, Drop Ammo, Deploy), each enabled bit from native state (cooldown over, gauge enough, not deployed). This needs an `UpdateModeList` wrapper on a **per-object vtable copy** for "mru" objects (tracked copies the hover vtable per object, `tracked_vehicle_class.cpp:26-30`); patching the shared hover slot would also hit APC/Minelayer/Tug. Who calls the virtual `UpdateModeList` and how often: UNVERIFIED.
- Label and click: the label is `UiLocalize("names", modeName[mode])` at 0x004A57BE, already redirected by `ModeLabelThunk` (Docs/RTS_COMMANDS.md:188-196) so the shim can show "Drop Repair" etc. via `ShimText`. Picks go through `ControlPanel::DispatchMode` at 0x004A512A, replaced by `DispatchHook` (`rts_commands.cpp:707`), which runs each unit's `ExecuteMode`. Precedent for adding entries without displacing stock ones: Hold (mode 17) and Build at Nav (mode 10) are relabelled, "never displaced" (RTS_COMMANDS.md:226-245).
- **Custom ids vs reuse.** Unknown: whether ids outside the known set index `modeName[mode]` safely, and which ids `ControlPanel::Render`'s click switch treats specially (modes 10 and 0x11 open submenus, FUN_004a08e0.c ~1359-1396). Safer plan: reuse ids the hover menu never shows and that open no submenu, relabelled by the shim (candidates 0xb Go To Geyser, 0xf Lay Mines, 4 Dropoff; both strings exist in the GOG table, `binary_strings/ascii_strings.csv`). For "mru" objects the shim's dispatch treats those ids as drop/deploy actions and consumes them (instant actions, no `AiCommand`, like Hold's key path), so Follow and Go to Nav stay stock and a drop does not cancel the current order. Mixed selections lose them in `Intersect` (1.5 `004c3eae`) unless a smart set is added (as `kSmartRepairReload`, `rts_commands_policy.h:56-80`); v1: single-unit selection only.
- Other hover commands (Attack, Rescue, Recycle, Get Repair/Reload): inherited, no work.

**(c) Coexistence.** One flag `deployed` per MRU. Deploy sets it and (proposal) issues Stop so the unit holds; any move order clears it. Radius service ticks only while deployed; pod drops work in both states and do not touch the flag. Both draw from the one ammo gauge, so heavy service starves drops and the reverse. Cooldown is independent of deployment. AI has no menu: proposal is that an AI MRU deploys itself after N s stationary and packs on a move order; AI pod drops are not in v1 (how to trigger: UNVERIFIED).

## 5. Decisions (user, 2026-11-19)
1. New class `classLabel = "mru"` (mobile repair unit); "Nightingale" is the unit name (`avmru.inf:1`).
2. Derive from the stock hover class by alias, as `tracked` does (section 3); ODF section `[MruClass]`.
3. Recognition: extend the `Find` label-compare hook with a `MatchMruClassLabel` (`hover` registered vs `mru` ODF); BuildClass detour stamps label "mru" at class +0x18; objects recognised by that pointer (`tracked_vehicle_class.cpp:423,623`). Loading the ODF without the shim: UNVERIFIED.
4. **v1 is the native class with a deployed radius service**, not ODF-only.
5. **Pool is a finite ammo gauge drawn from the MRU's own ammo; ODF value 0 = infinite.**
6. **Player and AI MRUs both service automatically when deployed.**
7. **SP only in v1.**
8. Radius/tick: defaults proposed below.
9. **The MRU drops pods on the fly without deploying, on a cooldown.** Menu: Follow, Go to Nav, Drop Ammo, Drop Repair, Deploy, plus the other native hover commands (section 4a). Commands are v1 scope.

Proposed `[MruClass]` keys (all optional; missing section = no service, stock hover):
| Key | Default | Meaning |
|---|---|---|
| `serviceRadius` | 0 (off) | metres; proposed value 60 (BZ98 pods are collected within 30 m, `00469f68`) |
| `serviceInterval` | 1.0 s | tick period |
| `repairPerTick` | 100 | health added per unit per tick |
| `reloadPerTick` | 50 | ammo added per unit per tick (fractions of each unit's max are an option) |
| `ammoPerRepair` / `ammoPerReload` | 1 / 1 | gauge cost per point served; 0 = free (infinite) |
| `serviceSelf` | 0 | may it service itself |
| `serviceDeployed` | 1 | require the deployed state |
| `podCooldown` | 30 s | cooldown between pod drops (`avmru.inf:3-8`) |
| `repairPodClass` / `ammoPodClass` | unset | pod ODFs to drop (e.g. `repamine`, `ammomine`) |
| `ammoPerRepairPod` / `ammoPerAmmoPod` | 0 | gauge cost per pod; 0 = free |
Numbers are proposals to tune, not measured.

## 6. Effort, risks, recommendation
| Piece | Effort | Notes |
|---|---|---|
| `mru` label alias + `[MruClass]` parse | S-M | copy of the tracked registration, no Simulate override |
| Service tick: radius scan, AddHealth/AddAmmo, gauge drain, AI and player alike | M | runs from an object update or a global per-frame loop; friend/foe test and "needs service" test |
| Deploy state | M, unknown | stock deploy handling is Armory/Producer-based (1.5 `0040cf28`); a hover MRU has no stock deploy state, so Deploy is a native flag set from the new menu entry (section 4a); no stationary-time substitute (section 7.1). Whether the entry can be added: see the probe |
| Pool gauge | S | the carrier ammo already has a gauge (`Tug::GetAmmoGauge` exists, 1.5 `004b2ff6`); MRU gauge reuse UNVERIFIED |
| Effects/sound | S | optional, reuse GAS events |
| Save/load of tick timer | S-M | decide whether timers persist; tracked class is the precedent (`tracked_vehicle_class.cpp`) |
| MP (later) | M-L | authority on target owners; guest health quirk |
| Menu probe (log-only: slots 7-9 on an "mru" object, relabel, dispatch log) | S-M | do first; answers the riskiest unknown |
| Menu entries Drop Ammo / Drop Repair / Deploy (per-object vtable copy, relabel, dispatch) | M-L | after the probe; single-unit selection only |
| Native pod drop (cooldown, gauge, `GameObjectClass::Build`, `SetOwner`) | M | copy of `Dispenser::Simulate` logic |
| Deploy flag + hold, AI auto-deploy | M | new state; AI rule is a proposal |

Risks: deploy state; AI (APC process) may not hold position to be a deployed MRU; ammo of units stored XOR-obfuscated (1.5 `0052d7a6`), use the engine's `AddAmmo` not raw writes; servicing every unit each tick must stay cheap (BZ2 uses a bounded range search, `ChooseServiceTarget-0048cf83.c`).

**Riskiest unknown and first probe.** Can an aliased hover object show three extra menu entries (slots 7-9) that the shim relabels and handles? Probe before any gameplay code: alias `mru`, wrap `UpdateModeList` on the per-object vtable copy to fill slots 7-9 enabled with reused ids, relabel through `ModeLabelThunk`, and log every `DispatchHook` pick; check in one SP mission that the three entries draw, click without opening a submenu, and leave the unit's order alone. If ids outside the stock set or the vtable copy fail, the fallback is key binds (as Hold's Z key) with no menu entry.

**Recommended v1 plan:** (1) the menu probe above; (2) alias `mru` + `[MruClass]`; (3) native pod drop with cooldown and gauge; (4) the Deploy menu entry with its deployed flag; (5) the per-MRU service tick, SP only; (6) the remaining menu entries (Drop Ammo, Drop Repair); (7) migrate `avmru`/`svmru` to `classLabel = "mru"` as test units; (8) live test: heal and reload a damaged group, AI MRU, gauge empty, `ammoPer* = 0`. The older pod-dropping design stays available as the ODF dispenser route (Resurgence).

## 7. Decisions on the former open questions (user, 2026-11-19)
1. Deploy is an explicit Deploy menu entry (required, section 4a); no "stationary for N seconds" substitute.
2. Resurgence's `avmru`/`svmru` are left unchanged; only new or converted ODFs opt in to `mru`.
3. Any friendly unit inside the radius is serviced, whatever its orders, including while moving.
4. The section 5 key set stands as proposed (separate repair and reload rates, gauge cost per point, 30 s pod cooldown, 60 m radius); the numbers are tuned in the live test.

No open questions remain; the next step is the menu probe (section 6).
