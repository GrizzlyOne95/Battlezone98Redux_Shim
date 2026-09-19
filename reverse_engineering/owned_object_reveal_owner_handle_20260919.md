# Owned-object perceivedTeam reveal: the owner handle was the wrong field — 2026-09-19

**Scope:** the confirmed Splinter repro only. This does not reopen the
`perceivedTeam` victim-retaliation research, whose conclusions
(`perceivedteam_victim_retaliation_root_cause_20260831.md`) still stand.

**Target:** `battlezone98redux.exe` GOG 2.2.301, SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`, disassembled
from the locally installed copy with `pefile` + `capstone`. Every address below
was read out of that image in this pass; none is carried over from the advisory
PDB.

---

## 0. Headline

**The owned-object reveal shipped with a four-byte error and has therefore never
once worked.** `kGameObjectOwnerHandleOffset` was `0x220`; the engine's owner
field is `0x224`. `0x220` is a live field in the tug/cargo path, so the defect
had two effects, not one:

1. `RevealOwnedObjectChainAfterDamage` read a non-owner field, so the walk
   terminated at depth 1 on every object and no craft was ever revealed.
2. `PreserveSprayEmitterOwner` **wrote** a craft handle into that engine field on
   every deployed Splinter emitter, and suppressed the engine's own lazy
   initialization of it.

This exactly matches the reported repro: the Splinter's children damage the
former team, and the firing craft keeps `perceivedTeam = 2`.

Separately, and worth stating plainly: **the underlying behaviour is stock.**
BZ 1.5 severs the same chain in the same place. Fixing it is an enhancement, not
a parity restoration, which is why it stays behind an INI switch.

---

## 1. What was already correct and needs no further work

| Prior claim | Status |
| --- | --- |
| `+0x174` actual team / `+0x180` perceived team | Correct, and already corrected in-tree on 2026-08-17 |
| The `+0x174 -> +0x180` fix is still required | **No.** It landed a year-month before this repro and is current |
| `RevealProcessOwnerPerceivedTeam` is the mechanism to repair | **No.** Wrong helper — see §2 |
| `kOrdnanceOwnerObjOffset = 0xD8` | Correct: `Ordnance::Init` `0x00585292 mov [edx+0xD8],eax` from `[ebp+0xC]`; paired handle `+0xDC` zeroed at `0x005852A4` |
| SprayBomb `this` at `SprayBomb::Hit` `[ebp-0x1B0]` | Correct: `0x005DB095 mov [ebp-0x1B0],ecx` |
| Build call site `0x005DB380` rel32, target `0x004E1190` | Correct: `0x005DB37F e8 0c5ef0ff`, result stored `0x005DB384 mov [ebp-0x1D0],eax` |

## 2. Two different helpers, only one of which is relevant

`RevealProcessOwnerPerceivedTeam` is **not** the Splinter mechanism. It detours
`OffensiveProcess` / `GunTowerProcess` / `TurretTankProcess` `DoSubTask` and
reveals on AI *engagement*. A player craft runs none of those processes, and a
`SprayBuilding` has no AI process at all, so it could never have fired for this
repro whatever field it wrote. It remains quarantined
(`AttackRevealPerceivedTeam`, default off) and this work does not disturb it.

The relevant mechanism is the one added by PR #170 (`ad9ed75f`, merged
2026-09-13), default **on** at `FeatureTier::SinglePlayer`:

- `PreserveSprayEmitterOwner` — relinks the deployed emitter to the firing craft.
- `RevealOwnedObjectChainAfterDamage` — walks `ownerHandle` after stock
  `SetDamageFlags` and applies the stock reveal operation to each owner.

Its design is sound. Only the offset was wrong.

## 3. The Splinter ownership chain

Shipped ODFs:

```
gsplint.odf   [WeaponClass]        classLabel "mortar",    ordName "splintbm"
splintbm.odf  [OrdnanceClass]      classLabel "spraybomb", deployName "splintb2"
splintb2.odf  [SprayBuildingClass] payloadName "splinter"
splinter.odf  [OrdnanceClass]      classLabel "tracer",    damageBallistic 40
```

Shipped code:

| Step | Address | What happens to ownership |
| --- | --- | --- |
| Craft fires `splintbm` | `Ordnance::Init` `0x00585292` | `ordnance+0xD8 = craft obj76`; `damage.damager` is that obj76 |
| Bomb settles | `SprayBomb::Hit` `0x005DB080`, build at `0x005DB37F` | `GameObjectClass::Build(transform, team, 0, -1, NULL)` — takes a **team and no owner**, never calls `SetOwner`. Emitter `ownerHandle` stays 0. **Chain severed here.** |
| Emitter fires payload | `SprayBuilding::Simulate` `0x005DA6E0`, `0x005DAB62`/`0x005DAB73` | `OrdnanceClass::Build(mat, emitter->obj76)` — every child records the **emitter** as `damage.damager`; `0x005DAB84` forces `bSend = 0` |
| Child lands | `SetDamageFlags` `0x004DC130` | reveal target is `damage.damager->gameObj` (`obj76+0x8C`) = the emitter. The craft is never reached. |

BZ 1.5 is identical modulo the `+0xC` struct shift: `SprayBomb::Hit @0x0053ABBF`
calls `GameObjectClass::Build @0x00498D9C` with `(matrix, team, 0, -1, NULL)`,
and `SprayBuilding::Simulate @0x0053A779` passes `this->obj` as the payload
owner then sets `bSend = 0`.

Stock **does** reveal the shooter for direct fire — `SetDamageFlags`' tail is
`damager->SetPerceivedTeam(damager->GetTeam())` in both builds. Splinter escapes
that only because `damager` is the emitter.

## 4. The owner field

`GameObject::SetOwner` and `GameObject::GetOwner`, reached from the Lua bindings:

```
.rdata 0x0087C4E4 "SetOwner"   entry 0 of table 0x00871D28 -> 0x00500820
.rdata 0x0087C4F0 "GetOwner"   entry 1 of table 0x00871D28 -> 0x00500860
0x00500820 -> handle-level 0x005C89D0 -> GameObject::SetOwner 0x0046FC40
0x00500860 -> handle-level 0x005C8A10 -> GameObject::GetOwner 0x004B0400
```

```asm
; GameObject::SetOwner 0x0046FC40
0046FC47  cmp  dword ptr [ebp+8], 0
0046FC4B  je   0046FC60
0046FC50  call 00462380                  ; GetHandle(argument)
0046FC58  mov  dword ptr [ecx+0x224], eax
0046FC5E  jmp  0046FC6D
0046FC60  mov  edx, dword ptr [ebp-4]
0046FC63  mov  dword ptr [edx+0x224], 0  ; null owner clears it
0046FC70  ret  4

; GameObject::GetOwner 0x004B0400
004B040A  mov  ecx, dword ptr [eax+0x224]
004B0411  call 004DA060                  ; GetObj
```

**Complete-object relative**, so it shares a base with `perceivedTeam` and needs
no subobject rebasing. Proven at the call site:

```asm
005AA91C  mov  ecx, dword ptr [ebp-0xC]  ; interface `this`
005AA91F  sub  ecx, 0x18                 ; -> complete object
005AA922  call 004B0400                  ; GetOwner
005AA930  mov  ecx, dword ptr [ebp-4]    ; returned owner
005AA933  add  ecx, 0x18                 ; -> its interface
```

### What `+0x220` actually is

A tug/cargo claim handle, not an owner:

```asm
004A8229  cmp  dword ptr [ecx+0x220], 0     ; already claimed?
004A8238  cmp  dword ptr [edx+0xFC], 0      ; carrier slot empty?
004A8250  call eax                          ; this->GetHandle()  -- its OWN handle
004A8255  mov  dword ptr [ecx+0x220], eax
...
004A827E  cmp  dword ptr [edx+0x14], 0x54554700   ; carrier class == 'TUG '
004A828A  mov  dword ptr [eax+0x220], 0           ; not a tug -> clear
```

Writing a foreign handle there both fails to record an owner and makes the
`+0x220 == 0` test above false, skipping the engine's own initialization. The
previous citation for `0x220` pointed at two inline stores of this kind
(`0x004A8255`, `0x004AB3E1`) that store the object's **own** handle; they
resemble `SetOwner` but are not it.

## 5. Everything that populates `ownerHandle`

From the 1.5 corpus, the `GameObject::SetOwner` call sites are:
`APC::Simulate` (deployed soldiers), `Producer::FinishBuild` (built structures),
`Dispenser::Simulate`, `ObjectLobber::Simulate`, `RadarLauncher::Simulate`,
`PowerUp::UnPackPermState`, and the Lua `SetOwner` binding. `SprayBomb::Hit` is
**not** among them, which is the severed link this fix restores.

So with the offset corrected, the owner walk becomes live for those topologies
too, where it had previously been inert:

| Case | Behaviour after the fix |
| --- | --- |
| Direct weapon damage | Unchanged. Craft `ownerHandle` is 0, walk stops at depth 1, stock reveal already applied |
| Splinter parent bomb hitting a craft directly | Unchanged — `damager` is the craft, stock reveals it |
| Splinter child | **Fixed** — emitter relinked, walk reaches the craft |
| APC-deployed soldier landing a hit | Now reveals the APC as well as the soldier |
| Producer-built structure landing a hit | Now reveals the producer; a no-op unless the producer is itself disguised |
| Friendly fire | Revealed, matching stock, which reveals `damager` on the whole shot branch regardless of `EnemyP` |
| Already revealed | No write; `previous != actual` guard |
| No owning craft / destroyed owner | `ownerHandle == 0`, or `GameObjectFromHandleGog` rejects the stale handle by round-tripping `GetHandle` |
| Ownership loop or corrupt handle | Depth bound 8 plus a visited set |

The APC and producer rows are genuine behaviour changes beyond the repro. They
are the same "act on the root owner when the hit lands" rule, and they are what
"owned Soldiers" in the brief asks for, but they should be watched in the live
matrix rather than assumed harmless.

## 6. Multiplayer authority

The reveal is **not** made authoritative-peer-only, and should not be.

`Craft::DamageAlloc @0x004877BF` (and `Building::DamageAlloc @0x00482E4A`) calls
`GameObject::SetDamageFlags` **unconditionally**, before and outside the
`DistributedObject::IsRemote` gate that guards the health mutation. Stock's own
`perceivedTeam` reveal therefore already runs on every peer, on local and remote
replicas alike. It is a convergent deterministic write: the value is
`attacker.actualTeam`, which is replicated and identical everywhere.

The Splinter payload inherits the same model deliberately. Per
`docs/MPAUTH_SPLINTER_STATIC_ANALYSIS.md`, the emitter is reconstructed
independently on every peer from the replicated parent bomb, and the children
set `bSend = 0` so they are never sent or received. Every peer therefore runs the
same reveal for the same reason.

The one detail that makes this safe to extend is that the relink stores the
**craft's** handle, which is a replicated identity. The emitter's own handle
comes from `find_empty_seqno` and may differ per peer; it is never transmitted
or compared.

So the structurally correct gate is "write where stock writes, with stock's
value, on every peer" — no `SetLocal`, no `team == LocalTeam()`, no
elect-one-peer scheme. That said, `perceivedTeam` is carried in
`DistributedObject` perm state, so a non-owner peer that reveals a frame early
can be briefly overwritten by the owner's next perm update before converging.
**That last point is argued, not measured.** Until a two-PC run confirms it, the
feature stays `FeatureTier::SinglePlayer`, which is where it already is.

## 7. Change made

- `kGameObjectOwnerHandleOffset` `0x220` -> `0x224`, with the evidence above in
  the comment.
- New `include/bzr_object_layout.h` holding the layout constants with their
  citations, including `kGameObjectTugCargoClaim = 0x220` named explicitly so
  the confusion cannot recur silently. `bzr_hooks.cpp` `static_assert`s its own
  copies against it, so drift on either side is a build break.
- New `tests/object_layout_tests.cpp` pinning each offset and the adjacency
  invariants (`owner == tugClaim + 4`, `perceived == actual + 0xC`).
- Traced the previously silent bail-outs in `PreserveSprayEmitterOwner` and the
  first hop of the owner walk, so a live run can tell "patch not installed" from
  "installed and declined" — the distinction the old offset bug hid.
- New lcbench fixture
  `reverse_engineering/test_missions/lcbench_ownreveal/rmownrev.lua`.

No trampoline, patch site, INI key, feature tier or default was changed.

## 8. Live validation still owed

Not yet run; the static work above does not close it.

1. Deploy `bin/Release/winmm.dll` **and** `scripts/patches.json` to the game
   root. They deploy separately, and a stale root `patches.json` skips the
   `Splinter Emitter Owner Propagation` site entirely — which produces exactly
   the same symptom as the offset bug.
2. `set OPENSHIM_TRACE_OWNED_OBJECT_REVEAL=1`, deploy `rmownrev.lua` as
   `addon/lcbench/lcbench.lua`, delete `logs\BZOgreLogfile.log`, launch
   `battlezone98redux.exe lcbench.bzn`.
3. Expected: `action=link kind=splinter-emitter` once per Splinter, then
   `action=write kind=damage-owner ... pt=2->1` on the first landed child hit,
   and `RESULT PASS`.
4. Re-run with `DRY_FIRE_ONLY = true`: expect no `write`, and `RESULT PASS
   stayed disguised without landed damage`.
5. Confirm the direct-hit arm is unchanged from stock, and watch the APC and
   producer rows in §5.
6. Two-PC run before considering any tier change.

## References

- `reverse_engineering/perceivedteam_victim_retaliation_root_cause_20260831.md`
- `docs/MPAUTH_SPLINTER_STATIC_ANALYSIS.md`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0053/0053abbf_SprayBomb_Hit.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0053/0053a779_SprayBuilding_Simulate.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0049/00496da9_GameObject_SetDamageFlags.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0048/004877bf_Craft_DamageAlloc.c`
