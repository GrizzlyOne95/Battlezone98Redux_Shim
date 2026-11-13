# Turret attack orders

`[SinglePlayer] TurretAttackOrders` (default ON). Source:
`src/patches/turret_attack_orders.cpp`. Log tag `[TURRETATK]`.

Status: static analysis only. **UNVERIFIED at runtime** — not live-tested yet.
Addresses were read from the shipping GOG 2.2.301 exe in Ghidra; function
bytes and vtable slot contents were re-checked against the same exe with
`scripts/audit_vtable_hooks.py`'s PE reader.

## Problem

A stock turret tank (class TurretTank, e.g. avturr/svturr) cannot be ordered
to attack:

- `TurretTank::GetCommand` (0x005F5D10) has no enemy -> CMD_ATTACK branch, so
  the reticle over an enemy offers no command.
- `TurretTank::UpdateModeList` (0x005F5A50) sets ModeList slot 3 to 0 (empty),
  so the unit menu has no Targets/Attack.
- `TurretTankProcess::InitAttack` (0x005F7710) deploys at once, and a deployed
  turret cannot move, so a target beyond weapon range is never engaged.

## Addresses (GOG 2.2.301)

| Item | Address | Notes |
|---|---|---|
| TurretTankVtable | 0x00889498 | slot 13 GetCommand, 23 UpdateModeList, 24 Deploy, 25 Packup |
| TurretTank::GetCommand | 0x005F5D10 | thiscall(target), ret 4 |
| TurretTank::UpdateModeList | 0x005F5A50 | thiscall |
| HoverCraftVtable | 0x0087ABE4 | slot 13 = Craft::GetCommand, slot 23 = HoverCraft::UpdateModeList 0x004EBD60 |
| Craft::GetCommand | 0x004AE110 | returns 4 when EnemyP(this,target) and [this+0x1A0] != 0 |
| Craft::Deploy | 0x004AE2B0 | state [this+0x228] 0 or 3 -> [[this+0x230]+0xE0] = 1, else 0 |
| Craft::Packup | 0x004AE330 | state 2 or 1 -> [[this+0x230]+0xE0] = 1, else 0 |
| ModeList::SetMode | 0x0046FA60 | thiscall(slot, mode, enabled) on craft+0x1A4 |
| TurretTankProcess / Friend / Enemy vtables | 0x00889710 / 0x008895EC / 0x008897F8 | slot 24 InitAttack, slot 26 DoAttack |
| TurretTankProcess::InitAttack | 0x005F7710 | only in the three TurretTank process vtables |
| DoAttack | 0x005F77C0 | shared: slot 26 of every unit process vtable; hooked on the three TurretTank ones only |

Craft deploy state +0x228: 0 undeployed, 1 deploying, 2 deployed, 3
undeploying. Process: +0x20 state, +0x34 craft, +0x38 task (TurretAttack),
+0x3C target handle, +0x6C weapon range squared. TurretAttack task: +0x08
state, +0x0C next state (1 = choose), +0x10 craft, +0x14 target handle.

## Behaviour

All hooks are vtable-slot replacements, RTTI-checked, and installed all or
nothing (every slot must hold the stock function first). They pass straight
through when the feature is off or in a network game.

- **GetCommand** (TurretTank slot 13): if stock returns 0 and
  `Craft::GetCommand` returns CMD_ATTACK, return CMD_ATTACK.
- **UpdateModeList** (TurretTank slot 23): after stock,
  `SetMode(3, 0xE, weapon != 0)` — the hovercraft Targets/Attack slot.
- **InitAttack** (process slot 24): after stock, for a player-team turret
  whose target is beyond range, call Packup, which cancels the deploy stock
  just requested.
- **DoAttack** (process slot 26): before stock, for a player-team turret
  (distances are 3D, matching the stock range test):
  - undeployed and within 0.9 x range: Deploy;
  - undeployed and within 1.0 x range for 1 s of game time: Deploy (the stock
    blast state can park the craft between 0.9x and 1.0x);
  - once our deploy completes: set task next state to 1 once (re-choose
    into blast);
  - deploying or deployed and beyond range for 1.5 s of game time:
    Packup and set task next state to 1 so it drives. A deployed turret out
    of range never fires, so it must not sit there.

Deploy and Packup are only called after the craft's own vtable slot 24/25 is
checked to hold the stock Craft method. AI teams are never touched. The gate is
the craft's team, not who gave the order, so a mission script's ATTACK order
on a player-team turret gets the same close-in behaviour. Per-process
tracking is reset when the process's task or target changes, after 2 s without
a tick, at mission end, and in a network game.

## Open questions (UNVERIFIED)

- That TurretAttack's DoState drives toward the target while undeployed and
  re-deploys nothing on its own (the static reading this design relies on).
- That selecting menu mode 0xE on a turret is dispatched by
  `TurretTank::SetActiveMode` (0x005F5CE0, not hooked) the way it is for a
  hovercraft.
