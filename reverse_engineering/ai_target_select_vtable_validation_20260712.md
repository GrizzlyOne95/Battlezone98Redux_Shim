# AI ChooseAttackTarget vtable validation

Date: 2026-07-12
Target: GOG `battlezone98redux.exe` (image base 0x00400000)

## Purpose

Validate the ownership point for a native `OnAiTargetSelect` callback before
installing any hook, per the address-drift lesson (advisory-PDB VAs can be
stale; virtuals must be confirmed against live vtables, not trusted from the
symbol join).

## Method

`UnitProcess::ChooseAttackTarget(float* rangeLimit) -> GameObject*` is a
virtual. Rather than detour instructions, we hook the vtable slot. Verified by:

1. RTTI: for each process vtable, read the CompleteObjectLocator at `vft-4`,
   its TypeDescriptor at `+0x0C`, and the decorated name at `+8`.
2. Slot identity: dumped 59 slots per vtable, diffed ScoutProcess and
   RocketTankProcess against WingmanProcess to locate the overridden slot.
3. Disassembly: confirmed both implementation bodies.

Static analysis: `reverse_engineering` scratch probe (capstone). Confirmed
against the **live** process by reading the same slots from process memory
after launch (RESULT: OK, all five slots at their expected originals).

## Findings

- **Slot 57 (+0xE4)** is `ChooseAttackTarget` for the wingman family.
- Four of five share `OffensiveProcess::ChooseAttackTarget` at **0x00583500**:
  - WingmanProcess vft 0x0088A6EC
  - RocketTankProcess vft 0x0088A5C0
  - TankProcess vft 0x0088AB9C
  - BomberProcess vft 0x0088B178
- ScoutProcess vft 0x0088AF98 overrides slot 57 with
  `ScoutProcess::ChooseAttackTarget` at **0x00614020**.

Verified disassembly (both bodies identical shape):

```
0x00583500 OffensiveProcess::ChooseAttackTarget
  push ebp; mov ebp,esp; push ecx
  mov [ebp-4],ecx
  mov eax,[ebp+8]        ; rangeLimit
  push eax
  mov ecx,[ebp-4]
  mov edx,[ecx+0x34]     ; searching GameObject (process owner)
  push edx
  call 0x463240          ; GetClosestEnemyWithin
  add esp,8; ret 4
0x00614020 ScoutProcess::ChooseAttackTarget
  ... mov edx,[ecx+0x34]; call 0x4637f0 (GetClosestEnemyOrMineWithin); ret 4
```

Process-owner GameObject is at process `+0x34` in both — used by the hook to
identify the acting unit.

## Slot diff summary

- Scout vs Wingman differ only at slot 0 (vector-deleting dtor) and slot 57
  (ChooseAttackTarget). Confirms 57 is the sole target-selection override.
- RocketTank vs Wingman differ at slots 0, 24, 48 (its known InitAttack /
  InitSubAttack specialization) but **not** 57 — rocket tanks use the shared
  OffensiveProcess target selection.
- Tank and Bomber differ from Wingman only at slot 0.

## Implementation

`ExtraUtilities/src/Patches/AiTargetSelect.cpp` swaps slot 57 in all five
vtables (shared impl -> HookShared, scout -> HookScout). Every slot is
RTTI-checked and its current value compared to the expected impl before the
write; any mismatch aborts that slot. Dispatch is gated by
`exu.SetAiTargetSelectEnabled(true)` and only fires when a Lua
`exu.AiTargetSelect` handler is present. Legacy anchors in
`ai_process_uniqueness_feasibility_20260319.md` are consistent with these
findings.
