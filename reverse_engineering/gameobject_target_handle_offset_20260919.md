# GameObject::targetHandle is +0x21C, and +0x214 is obfuscated maxAmmo — 2026-09-19

**Scope:** the one constant `kGameObjectTargetHandleOffset` and its single
consumer. Follow-up to
[`owned_object_reveal_owner_handle_20260919.md`](owned_object_reveal_owner_handle_20260919.md),
which corrected the owner handle in the same three-field neighbourhood and left
this one deliberately alone.

**Target:** `battlezone98redux.exe` GOG 2.2.301, SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`, ImageBase
`0x00400000`, disassembled from the locally installed copy with `pefile` +
`capstone`.

---

## 0. Headline

`kGameObjectTargetHandleOffset` was `0x214`. The field is at **`0x21C`**.

`0x214` is not a near-miss into padding. It is **BZ 1.5's** offset for
`targetHandle`, carried across without applying the Redux shift — and in Redux
that address holds **`maxAmmo`, XOR-obfuscated with `0x33333333`**. So the
`[SATVIS]` diagnostic's `target` column has been printing a scrambled ammo count
since it was added.

The constant's own comment marked it `UNVERIFIED` and said to treat the column
as advisory, so nothing was ever concluded from it. **Nothing downstream needs
revisiting** — see §4.

## 1. The accessor pair

Found the same way the owner pair was, through the Lua bindings rather than by
pattern-matching stores:

```
.rdata 0x0087C4CC "SetTarget"   table 0x00871D18 -> 0x005007A0
.rdata 0x0087C4D8 "GetTarget"   table 0x00871D20 -> 0x005007E0
```

Those are the two slots immediately above `SetOwner`/`GetOwner` at
`0x00871D28`/`0x00871D30`. They tail into the handle-level pair
`0x005C8950`/`0x005C8990`, which sit immediately below the owner pair's
`0x005C89D0`/`0x005C8A10`, and those call:

```asm
; GameObject::SetTarget 0x0049F450
0049F459  cmp  dword ptr [ebp+8], 0
0049F45D  je   0049F46C
0049F45F  mov  ecx, dword ptr [ebp+8]
0049F462  call 00462380                  ; GetHandle(argument)
0049F467  mov  dword ptr [ebp-4], eax
0049F46A  jmp  0049F473
0049F46C  mov  dword ptr [ebp-4], 0      ; null target -> handle 0
0049F473  mov  eax, dword ptr [ebp-8]
0049F479  mov  dword ptr [eax+0x21C], ecx
0049F482  ret  4

; GameObject::GetTarget 0x00462610
0046261A  mov  ecx, dword ptr [eax+0x21C]
00462621  call 004DA060                  ; GetObj
```

Structurally identical to `SetOwner 0x0046FC40` / `GetOwner 0x004B0400`.

**Complete-object relative**, proven at the call site — and note this is the
same function that proves it for `GetOwner`, 0x2F bytes earlier:

```asm
005AA94B  mov  ecx, dword ptr [ebp-0xC]  ; interface `this`
005AA94E  sub  ecx, 0x18                 ; -> complete object
005AA951  call 00462610                  ; GetTarget
005AA95F  mov  ecx, dword ptr [ebp-4]    ; returned target
005AA962  add  ecx, 0x18                 ; -> its interface
```

**Non-virtual.** Neither `0x00462610` nor `0x0049F450` has a single `.rdata`
reference, while the virtual `GameObject::GetTeam 0x00462450` has twenty-plus
vtable slots. Same shape as `GetPerceivedTeam 0x004625B0`.

## 2. What +0x214 actually is

```asm
; GameObject::GetMaxAmmo 0x0046D060
0046D06A  mov  eax, dword ptr [eax+0x214]
0046D070  xor  eax, 0x33333333
0046D078  ret
```

Reached from Lua `GetMaxAmmo` (`.rdata 0x0087CC84`, table `0x008721A8` ->
`0x00504F50` -> handle-level `0x005CD070`). `SprayBuilding::Simulate` performs
the same unscramble inline when it compares the emitter's ammo against
`ammoCost`, so the obfuscation is the live representation, not a one-off.

An obfuscated integer is exactly the kind of value that looks like a plausible
handle in a hex log and never resolves to anything.

## 3. BZ 1.5 cross-check, and why the shift is the trap

The 1.5 PDB struct (`decompilation_from_1.5_exe-pdb/1.5/bsim/out/object_model/`)
gives the tail of `GameObject` exactly:

```
+0x20C  maxAmmo        long
+0x210  weaponMask     long
+0x214  targetHandle   int
+0x218  hitch          _OBJ76 *
+0x21C  ownerHandle    int
        (struct size 0x220)
```

Three adjacent fields in the same order as Redux, uniformly `+0x8`:

| field | 1.5 | Redux | how Redux was proven |
|---|---|---|---|
| `maxAmmo` | `0x20C` | `0x214` | `GetMaxAmmo 0x0046D060` |
| `targetHandle` | `0x214` | `0x21C` | `SetTarget 0x0049F450` / `GetTarget 0x00462610` |
| `hitch` | `0x218` | `0x220` | `'TUG '` maintenance at `0x004A8229`–`0x004A828A` |
| `ownerHandle` | `0x21C` | `0x224` | `SetOwner 0x0046FC40` / `GetOwner 0x004B0400` |

**The "+0xC" rule is wrong here.** Redux is commonly described as the 1.5 layout
shifted by `+0xC`, and that holds through `perceivedTeam` (`0x174` -> `0x180`),
but past it the shift narrows to `+0x8`:

```
teamNumber     0x168 -> 0x174   +0xC
teamList       0x170 -> 0x17C   +0xC
perceivedTeam  0x174 -> 0x180   +0xC
---- narrows somewhere in 0x178..0x184 ----
isVisible      0x184 -> 0x18C   +0x8
seen           0x188 -> 0x190   +0x8
enemyShot      0x1E0 -> 0x1E8   +0x8
who_shot_JR    0x1EC -> 0x1F4   +0x8
maxAmmo        0x20C -> 0x214   +0x8
targetHandle   0x214 -> 0x21C   +0x8
```

1.5's `nameIndex`/`name` at `0x178`/`0x17C` are where the four bytes go; Redux's
`isObjective` lands at `0x189` rather than the `0x18C` a uniform `+0xC` would
predict.

`hitch` is also a satisfying independent confirmation of the *other* correction:
BZ 1.5 names the field between target and owner `hitch`, typed `_OBJ76*`, which
is precisely the tow attachment the Redux `'TUG '` logic at `+0x220` maintains.

## 4. Blast radius

`kGameObjectTargetHandleOffset` has exactly one consumer: `outEntry.targetHandle`
in the satellite/visibility sampler, printed as the `target=0x%08X` field of the
`[SATVIS]` line. It is read-only; nothing branches on it.

Searched for anything that parses or reasons from that column:

- `reverse_engineering/run_satellite_visibility_validation.ps1` — no reference
  (its only "target" hit is an unrelated `SendInput` comment).
- `docs/SATELLITE_VISIBILITY_FIX_PLAN.md` — no reference.
- `reverse_engineering/satellite_fow_root_cause_20260817.md` — one occurrence,
  and it is a *format template* with the value elided (`target=0x…`), not a
  capture. That document already records at §11.1 that the probe was reading the
  wrong memory and that every SATVIS sample predating its correction is
  invalidated.

So no captured value, conclusion or downstream artifact depends on this column.
Nothing to retract; the column simply becomes meaningful from here.

## 5. Change made

- `kGameObjectTargetHandleOffset` `0x214` -> `0x21C`, with the evidence above,
  and no longer marked UNVERIFIED.
- `include/bzr_object_layout.h`: `kGameObjectTargetHandle` promoted from a
  "deliberately not tied together" note to a real pinned constant with a
  `static_assert` in `bzr_hooks.cpp`; added
  `kGameObjectMaxAmmoObfuscated = 0x214` and `kGameObjectAmmoObfuscationKey`
  so the wrong value is named rather than merely absent; renamed
  `kGameObjectTugCargoClaim` to `kGameObjectHitch` now that 1.5 gives its real
  name; added the non-uniform-shift table to the file header.
- `tests/object_layout_tests.cpp`: pins the two new constants and adds the
  adjacency invariants `hitch == target + 4` and `target == maxAmmo + 8`.
  Verified negatively — reintroducing `0x214` fails four checks, naming the
  instruction that disproves it.

No behaviour outside the diagnostic changes. `winmm.dll` builds clean
Release/Win32; 36/36 host tests pass.

## References

- `reverse_engineering/owned_object_reveal_owner_handle_20260919.md`
- `reverse_engineering/satellite_fow_root_cause_20260817.md` (§11.1)
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0040/00405c42_GameObject_GetTarget.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0045/0045a033_GameObject_SetTarget.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/object_model/object_model.json`
