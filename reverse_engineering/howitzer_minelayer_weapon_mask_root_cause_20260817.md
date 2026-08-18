# Howitzer / Minelayer Weapon-Mask Selection — Reverse-Engineering Report

Date: 2026-08-17
Binaries:

- Legacy reference: `bzone.exe` (BZ 1.5, 3,495,936 bytes) + `bzint.pdb` (exact match),
  via `C:\Users\iestu\Documents\GIT\BZ1_Source\1.5\Battlezone_Install\bzone.exe`
  and the imported-symbol Ghidra corpus at
  `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/`.
- Patch target: GOG `battlezone98redux.exe` (5,425,152 bytes, unencrypted),
  `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\`, plus the
  shipped-exe Ghidra corpus (31,947 functions) at
  `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.

All Redux addresses below were re-derived from the shipped GOG image. The
mismatched `battlezone98redux.pdb` was not used for any offset.

---

## 0. Headline result

**Neither symptom is a Redux regression. Both behaviours are exactly what
Battlezone 1.5 does, reproduced faithfully in Redux.**

- BZ 1.5 `ArtilleryProcess::DoAttack` selects **the first existant weapon in
  slots 0..4** and never reads `weaponMask`.
- BZ 1.5 `LayMinesTask::DoArrived` **hard-codes slot 0 and selected-mask 1** and
  never reads `weaponMask`.
- Redux does the same two things, in the same order, with the same literals.

The 1.5 decompile was supposed to be the behavioural reference for a
restoration. It is instead the disproof: there is nothing to restore. Any change
here is a **deliberate enhancement over stock Battlezone**, not a bug fix, and
that reframing is the single most important output of this investigation.

The two symptoms are also **not a shared defect**. They are two independent
hard-codings in two unrelated functions, using two different mechanisms. The
hoped-for shared `weapon = weapons[0]` helper does not exist. `Carrier::GetWeapon`
*is* shared, and it is correct and generic in both builds.

---

## 1. Legacy (BZ 1.5) behaviour — verified

### 1.1 Where `weaponMask` comes from

`GameObjectClass::weaponMask` is the ODF field, stored as a **decimal digit
string read as an integer** (`11111`, `00010`, …). Default is `0x2B67` = decimal
`11111` (`GameObjectClass::GameObjectClass`, `0x00499D37`).

`GameObject::GameObject` (`0x004988AA`) decodes those digits into a real 5-bit
bitmask:

```c
iVar9 = pGVar3->weaponMask;      /* class value, e.g. 11111 */
uVar10 = 0;
this->weaponMask = 0;
param_1 = (_OBJ76 *)0x5;
do {
  uVar11 = (iVar9 % 10 < 1) ? 0 : 0x10;   /* digit -> bit 4 */
  uVar10 = (int)uVar10 >> 1 | uVar11;     /* shift down each pass */
  ...
  iVar9 = iVar9 / 10;
} while (param_1 != 0);
this->weaponMask = uVar10;
```

The ones digit is consumed first and ends at bit 0 after five shifts, so the
**rightmost decimal digit is hardpoint 0**:

| ODF `weaponMask` | decoded `GameObject::weaponMask` |
| --- | --- |
| `00001` | `0x01` (slot 0) |
| `00010` | `0x02` (slot 1) |
| `00100` | `0x04` (slot 2) |
| `11111` (default) | `0x1F` (all five) |

`GameObject::weaponMask` lives at **+0x210**, confirmed by disassembly, not by
PDB type data:

```
0046ca41  8b4314           mov eax, [ebx + 0x14]     ; UnitTask::me
0046ca44  8b8010020000     mov eax, [eax + 0x210]    ; me->weaponMask
```

It is stored **plain** — there is no obfuscation on this field in 1.5.

### 1.2 Who consumes it

Across the entire 1.5 image, `GameObject::weaponMask` is read by exactly two
gameplay paths:

| Function | Address | Use |
| --- | --- | --- |
| `FireAt(me, him)` | `0x0045F8F4` | `Carrier::SetSelected(carrier, me->weaponMask)` then `TriggerSelected` |
| `UnitTask::UpdateWeapon` | `0x0046C63E` | `SetSelected(carrier, weaponMask & ~(1 << specialSlot))` at `0x0046CA59` |

Plus non-combat readers: the ctor above, `GameObjectClass` ODF load, and
`WeaponPowerup::GiveWeapon` (`0x004B91FF`), which sets/clears one bit when a
weapon is added or removed.

**`ArtilleryProcess::DoAttack` and `LayMinesTask::DoArrived` are not on that
list.** That is the whole finding.

### 1.3 Artillery — `ArtilleryProcess::DoAttack` @ `0x0040D498`

```
0040d5b3  xor edi, edi              ; selected = NULL
0040d5b5  mov [ebp+0x64], edi
0040d5b8  mov ecx, [ebp+0x70]       ; carrier
0040d5bb  push ebx                  ; slot index, starts at 0
0040d5bc  call 0x4059d0             ; Carrier::GetWeapon
0040d5c1  test eax, eax
0040d5c3  jne 0x40d5cd              ; first non-null wins
0040d5c5  inc ebx
0040d5c6  cmp ebx, 5
0040d5c9  jl  0x40d5b8
```

First existant weapon in slots 0..4. The chosen weapon is then fired **directly**
through its own vtable slot +8 (`Trigger`) — artillery never goes through
`Carrier::SetSelected` / `TriggerSelected`, so `selected` and `enabled` are
irrelevant to it.

### 1.4 Minelayer — `LayMinesTask::DoArrived` @ `0x0041D5B2`

```
0041d5b2  mov eax, [ecx + 0x14]     ; task->me
0041d5b6  mov esi, [eax + 0x198]    ; me->carrier
0041d5bc  test esi, esi
0041d5be  je  0x41d5ea
0041d5c0  push 0                    ; <-- literal hardpoint 0
0041d5c2  mov ecx, esi
0041d5c4  call 0x4059d0             ; Carrier::GetWeapon(carrier, 0)
0041d5c9  test eax, eax
0041d5cb  je  0x41d5da
0041d5cd  mov edx, [eax]
0041d5d1  call dword ptr [edx + 0x30]   ; weapon ready?
0041d5d4  test al, al
0041d5d6  jne 0x41d5da
0041d5d8  pop esi
0041d5d9  ret                       ; not ready -> wait
0041d5da  push 1                    ; <-- literal selected mask 1
0041d5dc  mov ecx, esi
0041d5de  call 0x41d314             ; Carrier::SetSelected(carrier, 1)
0041d5e3  mov ecx, esi
0041d5e5  call 0x41d365             ; Carrier::TriggerSelected(carrier)
```

Two independent literals, both slot 0.

### 1.5 Supporting primitives (1.5)

| Function | Address | Semantics |
| --- | --- | --- |
| `Carrier::GetWeapon` | `0x004059D0` | `(existant & (1<<i)) ? weapon[i] : NULL` |
| `Carrier::SetSelected` | `0x0041D314` | `selected = mask & existant`; edge-triggers weapon vtable +0x1C / +0x20 |
| `Carrier::TriggerSelected` | `0x0041D365` | fires every weapon in `enabled & selected` via vtable +8 |
| `GameObject::GetWeaponMask` | `0x00405B1B` | plain load of +0x210 |
| `GameObject::SetWeaponMask` | `0x0045E596` | plain store to +0x210 |
| global `SetWeaponMask(handle, mask)` | `0x0045F862` | resolves handle, plain store |
| Lua `SetWeaponMask` | `0x00418268` | Lua binding onto the above |

`Craft::SetActiveMode`, `Minelayer::SetActiveMode` (`0x0049FA41`) and
`TurretTank::SetActiveMode` are thin command-mapping wrappers. **None of them
touch `weaponMask`.** The earlier note's suspicion that the class activation path
forces the slot is disproved.

`Carrier::owner` is written by `Carrier::Carrier` (`0x0049503F`) and **never read
anywhere in the 1.5 image** — relevant below, because it means the field cannot
be trusted as a back-pointer.

---

## 2. Redux equivalents — verified

### 2.1 Function map

| Role | 1.5 | Redux (GOG) | Verified by |
| --- | --- | --- | --- |
| `ArtilleryProcess::DoAttack` | `0x0040D498` | **`0x00475B30`** | both `MORT` FourCC tests in the same order + identical slot loop |
| `LayMinesTask::DoArrived` | `0x0041D5B2` | **`0x005128D0`** | identical shape: `GetWeapon(0)` → ready → `SetSelected(1)` → `TriggerSelected` |
| `UnitTask::UpdateWeapon` | `0x0046C63E` | `0x00604130` | mask & ~specialSlot → `SetSelected` |
| `UnitTask` weapon init | — | `0x005FEDD0` | same mask & ~specialSlot |
| `FireAt` | `0x0045F8F4` | `0x005CB140` | `GetWeaponMask` → `SetSelected` → `TriggerSelected` → `SetTarget` |
| `Carrier::GetWeapon` | `0x004059D0` | `0x00417F60` | `(existant & 1<<i) ? weapon[i] : 0` |
| `Carrier::SetWeapon` | `0x0048697C` | `0x004A77A0` | writes `weapon[i]`, maintains `existant` |
| `Carrier::SetSelected` | `0x0041D314` | `0x004D9880` | `selected = mask & existant` |
| `Carrier::TriggerSelected` | `0x0041D365` | `0x00511FC0` | fires `selected & enabled` |
| `Carrier::GetHardpoint` | `0x0047E894` | `0x00417F40` | returns `+4 + i*4` |
| `Carrier::GetSelected` | `0x0046F86F` | `0x00417F90` | returns `+0x30` |
| `Carrier::GetEnabled` | `0x004128BE` | `0x00417FB0` | returns `+0x34` |
| `Carrier::SetEnabled` | `0x0049506C` | `0x004D9950` | `enabled = v & existant` |
| `GameObject::GetCarrier` | — | `0x00417CA0` | returns `+0x1A0` |
| `GameObject::GetWeaponMask` | `0x00405B1B` | **`0x00462510`** | returns `+0x218`, no xor |
| `GameObject::SetWeaponMask` | `0x0045E596` | **`0x005C7450`** | stores `+0x218` |
| `GameObject::GameObject` | `0x004988AA` | `0x004DA0B0` | digit decode into `+0x218` |
| `WeaponPowerup::GiveWeapon` | `0x004B91FF` | `0x00612F10` | sets/clears one mask bit |
| weapon-set hash | — | `0x005FED30` | XOR over mask-selected weapons |
| best-weapon pick | `0x00407B2C` | `0x00466BE0` | iterates mask bits, scores |
| `WeaponCheck` | `0x0046B40F` | `0x004182D0` | iterates mask bits |

### 2.2 Verified structure offsets

`GameObject` (complete object):

| Field | 1.5 | Redux |
| --- | --- | --- |
| `carrier` | `+0x198` | **`+0x1A0`** |
| `curCmd.what` | — | `+0xAC` |
| `weaponMask` (decoded 5-bit) | `+0x210` | **`+0x218`** |
| deploy/control block ptr | `+0x228` | `+0x230` |

`GameObjectClass::weaponMask` (ODF digits) is at `+0xC4` in Redux.

`Carrier` (Redux, from `GetWeapon` / `SetWeapon` / `SetSelected` / `SetEnabled`):

| Field | Offset |
| --- | --- |
| `owner` (write-only, never read) | `+0x00` |
| `hardpoint[5]` | `+0x04` |
| `weapon[5]` | `+0x18` |
| `existant` | `+0x2C` |
| `selected` | `+0x30` |
| `enabled` | `+0x34` |
| `special` | `+0x38` |

`UnitProcess::me` is at **`process + 0x34`** in Redux (1.5: `+0x2C`), confirmed at
`0x00475B5F` (`mov ecx, [eax+0x34]`). `LayMinesTask::me` is at `+0x10` (1.5: `+0x14`).
`UnitTask::specialSlot` is at `+0xBC`.

The recurring `+8` delta on `GameObject` (`0x198→0x1A0`, `0x210→0x218`,
`0x228→0x230`) and on `UnitProcess` (`0x2C→0x34`) is consistent, and cross-checks
against the satellite work, where `illumination` sits at `+0xDC` in *both* builds
— the eight inserted bytes land between `0xDC` and `0x198`.

`GameObject::weaponMask = +0x218` is confirmed **three independent ways**: the
getter (`0x00462510`), the setter (`0x005C7450`), and the ODF digit-decode loop in
the constructor (`0x004DA0B0`, writing element `0x86` of an int array = byte 0x218).

### 2.3 Redux artillery selection — `0x00475B30`

```
00475db6  mov ecx, [ebp-0x274]     ; i
00475dbc  add ecx, 1
00475dbf  mov [ebp-0x274], ecx
00475dc5  cmp dword ptr [ebp-0x274], 5
00475dcc  jge 0x475dff
00475dce  mov edx, [ebp-0x274]
00475dd4  push edx                 ; slot
00475dd5  mov ecx, [ebp-0x2f0]     ; carrier
00475ddb  call 0x417f60            ; Carrier::GetWeapon   <-- sole patch surface
00475de0  mov [ebp-0x284], eax
00475de6  cmp dword ptr [ebp-0x284], 0
00475ded  je  0x475dfd
00475def  mov eax, [ebp-0x284]
00475df5  mov [ebp-0x254], eax     ; chosen weapon
00475dfb  jmp 0x475dff
00475dfd  jmp 0x475db6             ; next slot
```

Semantically identical to 1.5. `[ebp-0x250]` holds the `ArtilleryProcess*`
(stored at `0x00475B45`), so the craft is reachable as
`*(*(uint32_t*)(ebp-0x250) + 0x34)` at the patch site.

### 2.4 Redux minelayer selection — `0x005128D0`

```
005128f1  push 0                   ; <-- literal hardpoint 0
005128f3  mov ecx, [ebp-4]         ; carrier
005128f6  call 0x417f60            ; Carrier::GetWeapon(carrier, 0)
005128fb  mov [ebp-8], eax
005128fe  cmp dword ptr [ebp-8], 0
00512902  je  0x51291c
...
0051290c  mov eax, [edx+0x30]
0051290f  call eax                 ; weapon ready?
00512916  jne 0x51291c
00512918  xor al, al
0051291a  jmp 0x512930             ; not ready -> wait
0051291c  push 1                   ; <-- literal selected mask 1
0051291e  mov ecx, [ebp-4]
        + call 0x4d9880            ; Carrier::SetSelected(carrier, 1)
        + call 0x511fc0            ; Carrier::TriggerSelected(carrier)
```

Semantically identical to 1.5.

### 2.5 Divergences that do exist (all benign)

- Redux `Carrier::SetSelected` adds a `weapon[i] != NULL` guard before the
  edge-trigger vtable calls that 1.5 lacks. Defensive hardening, not a behaviour
  change.
- Redux `Carrier::TriggerSelected` does not set the
  `fWeaponTriggerTillTime`/`Net::fWeaponTriggerHoldTime` field that 1.5 sets;
  that bookkeeping moved elsewhere. Unrelated to selection.

Neither touches weapon-mask semantics.

---

## 3. Hypotheses, tested individually

| Hypothesis | Verdict |
| --- | --- |
| Redux hard-codes slot/hardpoint 0 | **Minelayer: yes** — literal `0` and literal `1`. **But 1.5 does the same.** Artillery: no, it scans 0..4. |
| Converts a mask to a single index incorrectly | **No.** Neither path converts a mask at all. |
| Reads the wrong mask field | **No.** `GetWeaponMask` reads `+0x218`, which is provably the decoded mask. |
| Drops the mask on entering `ArtilleryProcess` / minelayer task state | **No.** The mask is never read on either path, in either build. |
| Uses a generic weapon helper whose semantics changed | **No.** `Carrier::GetWeapon` is byte-for-byte equivalent between builds. |
| First-valid-weapon search that never advances past slot 0 | **Artillery: yes, by design** — it advances only when the earlier slot is empty. Identical in 1.5. |
| Shared root cause between Howitzer and Minelayer | **No.** Two independent hard-codings; artillery never even calls `SetSelected`. |

---

## 4. Audit of the existing OpenShim / prior experiments

### 4.1 The `0x0042AF10` "ArtilleryProcess::DoAttack" detour was aimed at the wrong function

`src/patches/bzr_hooks.cpp:792` defines
`kGogArtilleryDoAttackEntryAddr = 0x0042AF10` and guards it with the byte
signature `55 8B EC 6A FF 68 B0 56 84 00`.

That signature **does** match the bytes at `0x0042AF10`:

```
0042af10  push ebp
0042af11  mov ebp, esp
0042af13  push -1
0042af15  push 0x8456b0        ; SEH handler
0042af1a  mov eax, fs:[0]
```

but that is an **SEH-framed MSVC function**, and its body is an STL red-black-tree
insertion that returns `param_1` and delegates to `FUN_0042F020`. The real
`ArtilleryProcess::DoAttack` is at `0x00475B30` and has a completely different
`/GS` security-cookie prologue:

```
00475b30  push ebp
00475b31  mov ebp, esp
00475b33  sub esp, 0x438
00475b39  mov eax, [0x8e7000]     ; __security_cookie
00475b3e  xor eax, ebp
```

This is the root cause of the historical crashes. The "four stack words, first
used as a hidden result destination, `ret 0x10`" ABI that the earlier notes
described and carefully mirrored is simply the **sret `std::pair<iterator,bool>`
return of a map insert**. Mirroring it faithfully made the shim call into the
tree helper with fabricated arguments; dumps `12908`/`13852`/`22488`/`29888` are
all consistent with that. Signature verification passed because the bytes were
genuinely unique — uniqueness proved the *address* was stable, never that the
*function* was the right one.

The same reasoning invalidates the `0x0042BB1A` `[ARTYMASK]` trace call-site: it
is an internal call inside that STL routine, not inside artillery code.

### 4.2 The carrier-bias helper uses 1.5 offsets against Redux

`src/patches/bzr_hooks.cpp:25294-25295`:

```cpp
constexpr size_t kGameObjectCarrierOffset = 0x198;   // 1.5 value; Redux is 0x1A0
constexpr size_t kGameObjectWeaponMaskOffset = 0x210; // 1.5 value; Redux is 0x218
```

Three separate defects follow:

1. **Carrier pointer read from `+0x198`.** `ApplyWeaponMaskCarrierBiasForCraft`
   then *writes* through that pointer (`std::swap` of `hardpoint[]`/`weapon[]`
   plus three bit swaps, lines 25467-25471). A wrong-but-mapped pointer will not
   fault, so the `__try/__except` gives no protection — it would silently corrupt
   whatever object actually lives there.
2. **Mask read from `+0x210`.** In Redux that offset holds a *different*,
   genuinely obfuscated field (`FUN_00417C80` returns `*(uint*)(this+0x210) ^ 0x33333333`,
   and `FUN_00470F40` serialises it as a 0..3 enum). It is not the weapon mask.
3. **`rawMask ^ 0x33333333` (line 25330).** Redux's weapon mask is **not**
   obfuscated — `GetWeaponMask` is a plain load. The XOR was inferred from the
   `+0x210` field in defect 2 and is spurious.

`kUnitProcessMeOffset = 44` (line 25296) is likewise the 1.5 value; Redux is
`0x34`. Note that other, working parts of the same file already use the correct
`0x1A0` (`kPersonCarrierOffset` line 806, `kCraftCarrierOffset` line 936) — the
weapon-mask code is internally inconsistent with the rest of the shim.

The `CarrierView` struct itself (lines 25282-25292) is **correct** for Redux;
only the offset used to reach the carrier is wrong.

`kWeaponIndexOffset = 0xAC` — the assumption that a `Weapon` stores its own
hardpoint index — is **unverified**. `Carrier::SetWeapon` (`0x004A77A0`) writes
`weapon[i]` and maintains `existant` but does **not** write any slot index back
into the weapon object, so nothing on that path establishes the field.

### 4.3 Current state: dormant, so nothing is corrupting memory today

- `include/patches.h:133-134` — both bias patches have address `0` and
  `verified = false`, so `FillJmp5Payloads` skips them and they are never
  installed.
- `kWeaponMaskCarrierBiasEnabledDefault = false` (line 1945).
- `InstallArtilleryDoAttackHookIfPossible()` is declared and defined but **never
  called** (only the declaration at line 395 and the definition at line 25595).
- The bridge entry point logs
  `"howitzer volley override requested but unavailable; unsafe ArtilleryProcess::DoAttack replay remains disabled"`.

So the feature is inert. The correct disposition is to **delete or correct** the
dead constants rather than leave 1.5 offsets sitting in the tree looking
authoritative.

### 4.4 Why the carrier-reordering approach is wrong even with correct offsets

Reordering `Carrier::weapon[]`, `hardpoint[]`, `existant`, `selected` and
`enabled` mutates **simulation state** that many other subsystems read:
`UpdateWeaponAim`, `GetRank`, the HUD/reticle/status displays, save/load, and
`FUN_005FED30`, which XORs weapon pointers and class signatures **in slot order**
to produce a synchronisation hash. Permuting slots changes that hash and would
create host/client divergence. Snapshot-and-restore does not help, because the
state is observable by anything that runs between the swap and the restore.

The correct layer changes *which weapon the AI picks*, without ever writing to
the carrier.

---

## 5. Recommended patch design (specified, not implemented)

Because this is an enhancement rather than a restoration, it is specified here in
full and left for an explicit decision.

### 5.1 The selection rule

```
desired = weaponMask & carrier->existant
slot    = (desired != 0) ? lowest_set_bit(desired)
                         : <stock behaviour>
```

The key safety property: **with the default ODF mask `11111` (`0x1F`),
`lowest_set_bit(0x1F & existant)` is exactly the first existant slot — which is
precisely what stock picks, in both builds.** The patch is therefore a bit-exact
no-op for every unit that does not carry an explicit non-default mask, which
satisfies "preserve stock behaviour when the mask genuinely selects only
weapon 0".

### 5.2 Artillery — one 5-byte `call rel32` redirect

Patch site: **`0x00475DDB`** (`call 0x417F60` inside the slot loop).
Redirect to `ShimArtillerySelectWeapon(carrier /*ecx*/, slot /*stack*/)`:

- On `slot == 0`: compute `desired`; if non-zero, return
  `Carrier::GetWeapon(carrier, lowest_set_bit(desired))` so the loop breaks
  immediately on the mask-preferred weapon. If zero, tail-call the stock
  `GetWeapon(carrier, 0)`.
- On `slot != 0`: tail-call stock `GetWeapon(carrier, slot)` unchanged.

The mask is reached from the frame, not from the dead `Carrier::owner` field:
`craft = *(uint32_t*)(*(uint32_t*)(ebp - 0x250) + 0x34)`, then
`mask = *(uint32_t*)(craft + 0x218)`. A naked thunk (OpenShim already uses this
pattern in `trampolines.cpp`) captures `ebp` before the call.

Everything downstream — lead solution, terrain clearance, aim, the direct
`weapon->vtbl[8]` trigger — receives a genuine `Weapon*` from the same carrier, so
no other assumption is disturbed. Artillery never calls `SetSelected`, so
`selected`/`enabled` need not be touched at all.

### 5.3 Minelayer — two 5-byte `call rel32` redirects

Both inside `0x005128D0`:

- **`0x005128F6`** (`call GetWeapon`) → helper that ignores the pushed `0` and
  uses `lowest_set_bit(desired)`, falling back to `0`.
- the `call 0x4D9880` immediately after `0x0051291E` → helper that ignores the
  pushed `1` and passes `1 << lowest_set_bit(desired)`, falling back to `1`.

Selecting a *single* bit rather than the full `desired` mask is deliberate: stock
never lays more than one mine per arrival, and passing a multi-bit mask to
`SetSelected` would make `TriggerSelected` fire several hardpoints at once — a
behaviour that has no legacy precedent.

### 5.4 Properties

- Three `REL32` patches total, which is an existing OpenShim patch type with
  signature verification and fail-closed behaviour already implemented.
- No writes to any simulation state. No carrier mutation. No ABI reconstruction.
- Scoped exactly to the two AI paths, because the redirects are at those two call
  sites — `Carrier::GetWeapon` itself is untouched, so player weapon cycling,
  `FireAt`, `UnitTask::UpdateWeapon`, sniper retaliation, deploy logic and normal
  multi-weapon AI are all unaffected by construction.
- Same VA on Steam: the Steam image is the same build wrapped in SteamStub, whose
  `.text` decrypts in place — the convention already relied on elsewhere in
  `bzr_hooks.cpp`. Verify at runtime rather than statically.
- Multiplayer: this changes which ordnance AI fires, so it is simulation-
  affecting and **every player must run the same shim build**, exactly like other
  gameplay patches. It does not change `weaponMask` itself, so the
  `FUN_005FED30` weapon-set hash is unaffected.

---

## 6. Validation matrix

Prerequisite: build a test craft with distinct, visually distinguishable ordnance
on hardpoints 0/1/2 so the fired weapon is identifiable.

### 6.1 Howitzer / artillery

| # | ODF `weaponMask` | Hardpoints filled | Expected stock | Expected patched |
| --- | --- | --- | --- | --- |
| 1 | `00001` | 0,1,2 | slot 0 | slot 0 (no change) |
| 2 | `00010` | 0,1,2 | slot 0 | slot 1 |
| 3 | `00100` | 0,1,2 | slot 0 | slot 2 |
| 4 | `11111` (default) | 0,1,2 | slot 0 | slot 0 (no change) |
| 5 | `00110` (multi-bit) | 0,1,2 | slot 0 | slot 1 (lowest set) |
| 6 | `00010` | 0,2 only | slot 0 | slot 0 (mask ∩ existant = ∅ → stock) |
| 7 | `00000` | 0,1,2 | slot 0 | slot 0 (stock) |
| 8 | `00100` | 0,1 only | slot 0 | slot 0 (fallback) |
| 9 | `00010` | 0,1,2 | — | deployed: as row 2 |
| 10 | `00010` | 0,1,2 | — | undeployed: as row 2 |
| 11 | `00010` | 0,1,2 | — | under follow / go / attack: as row 2 |
| 12 | `00010`, slot 1 = non-ordnance | 0,1,2 | slot 0 | slot 1 selected; confirm no crash and graceful aim degradation |

### 6.2 Minelayer

| # | ODF `weaponMask` | Hardpoints filled | Expected stock | Expected patched |
| --- | --- | --- | --- | --- |
| 13 | `00001` | 0,1 | mine slot 0 | slot 0 (no change) |
| 14 | `00010` | 0,1 | mine slot 0 | slot 1 |
| 15 | `11111` (default) | 0,1 | mine slot 0 | slot 0 (no change) |
| 16 | `00011` (multi-bit) | 0,1 | mine slot 0 | slot 1 only — **not** both |
| 17 | `00010` | 0 only | mine slot 0 | slot 0 (fallback) |
| 18 | `00000` | 0,1 | mine slot 0 | slot 0 (stock) |
| 19 | Lua `SetWeaponMask(h, 2)` at runtime | 0,1 | mine slot 0 | slot 1 — proves the runtime setter path |
| 20 | `00010`, slot 1 weapon not ready | 0,1 | waits on slot 0 | waits on slot 1 |

### 6.3 Non-regression

| # | Check |
| --- | --- |
| 21 | Player-controlled weapon cycling unchanged for both classes |
| 22 | Non-artillery AI (`UnitTask::UpdateWeapon`) still honours mask minus special slot |
| 23 | Undeployed-howitzer sniper-retaliation fix in `OffensiveProcess::DoSubTask` still behaves — separate code, must not move |
| 24 | Save / load round-trip of a mid-mission howitzer and minelayer |
| 25 | Two-client MP session, both on the same shim build: no desync over a full artillery engagement |

---

## 7. Confidence and remaining uncertainty

**Static confidence: High** for every claim in sections 1-4.

- Both 1.5 behaviours are confirmed at instruction level in the shipped
  `bzone.exe`, not merely in decompiler output.
- Both Redux functions are identified by structural fingerprints unique enough to
  be conclusive (paired `MORT` tests in order; the exact `GetWeapon(0)` → ready →
  `SetSelected(1)` → `TriggerSelected` chain).
- `weaponMask = +0x218` has three independent confirmations.
- The `0x0042AF10` misidentification is demonstrated directly from the two
  prologues.

**Not established:**

1. **Nothing is runtime-validated.** No live session was run for this
   investigation. The offsets and addresses are derivations from the shipped
   image.
2. **The Steam image is assumed to share these VAs.** Consistent with existing
   OpenShim convention but not statically verifiable through SteamStub.
3. **`Weapon + 0xAC` as a slot-index field remains unverified** — the proposed
   design does not use it, which is one more reason to prefer it.
4. Whether the artillery path is reachable for a *deployed* howitzer through some
   other process (a deployed howitzer may run a different AI class); rows 9-10
   exist to settle this empirically.

**The single runtime observation that would resolve the most:** attach to a live
mission with a howitzer whose ODF mask is `00010`, breakpoint `0x00475DDB`, and
confirm (a) the breakpoint is hit at all, (b) `ecx` is a plausible `Carrier*` with
`existant` at `+0x2C` matching the fitted hardpoints, and (c)
`*(*(uint32_t*)(ebp-0x250) + 0x34) + 0x218` reads `0x02`. That one stop validates
the function identity, the carrier layout, the process→craft offset and the mask
offset simultaneously.

---

## 8. Conclusion

**ROOT CAUSE** — There is no Redux regression. BZ 1.5 `ArtilleryProcess::DoAttack`
selects the first existant hardpoint and never consults `weaponMask`; BZ 1.5
`LayMinesTask::DoArrived` hard-codes hardpoint 0 and selected-mask 1. Redux
reproduces both faithfully at `0x00475B30` and `0x005128D0`. The reported
behaviour is original Battlezone behaviour.

**SHARED OR INDEPENDENT** — Independent. Two unrelated functions, two different
mechanisms; artillery does not even use the `SetSelected`/`TriggerSelected` path
the minelayer uses. There is no common defective helper, and a global
weapon-selection patch is not justified.

**BEST PATCH LAYER** — If the behaviour is wanted as an enhancement: three
`call rel32` redirects — `0x00475DDB` for artillery, `0x005128F6` and the
`SetSelected` call after `0x0051291E` for the minelayer — using
`lowest_set_bit(weaponMask & existant)` with fallback to stock. No simulation
state is written, and the default ODF mask `11111` makes the change a bit-exact
no-op for stock units.

**CONFIDENCE** — High for the static analysis and for the negative result;
Medium-High for the proposed patch, pending the single runtime observation in §7.

**WHY** — The 1.5 corpus was intended as the restoration reference and instead
falsifies the premise. The prior patch attempt failed not because the approach
was too timid but because it targeted an STL tree-insert routine that happened to
carry a unique byte signature; byte-uniqueness authenticated the address while
saying nothing about the function's identity, and the "unusual artillery ABI"
that was carefully reproduced was an sret `std::pair` return.
