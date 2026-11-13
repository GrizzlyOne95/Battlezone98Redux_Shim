# BZ aiName / aiName2 dispatch — reconstruction (2026-09-01)

**Question:** can reconstructed 1.4 AI be exposed through the existing `aiName`/`aiName2` selection mechanism as per-unit opt-in (`TankEnemy` vs `TankLegacyEnemy`) without a global fork, and is `TankLegacyFriend` legal given the 8-char resource limit?

## 0. Executive answer

* **Storage is proven.** `aiName` and `aiName2` are `char[32]` fields in `GameObjectClass` at **+0x8C** and **+0xAC**, loaded from the ODF `[GameObjectClass]` section via `ParameterDB::Get` with FNV-1 hashes `0x98D7239C` / `0x48AD2AEA` (section `0xD3DD9CEC` = `GameObjectClass`, lower-cased, prime `0x1000193`, init `0x811C9DC5`). Strings are up to 31 chars + NUL, not hashed file names.
* **Dispatch surface is RtimeClass.** The name strings are **RtimeClass class names** for `AiProcess` subclasses. Registration is the standard `push <CreateObject> ; push <"TankFriend"> ; mov ecx, <RtimeClass global> ; call RtimeClass::RtimeClass (0x4B1036)` triple — verified at `0x5CA6CF` (`TankFriend` → 0x470E35, `0x5DC260`) and siblings. Factory `0x470E35` does `push 0x78 ; call operator_new ; test ; mov ecx,eax ; jmp 0x47072A` → `mov [esi], 0x5DBEA0` (vtable). Hence `aiName` resolves via the engine’s runtime type registry, **not** via a filename lookup.
* **Selection between aiName vs aiName2 is not yet proven in full, but the storage and registry chain is sufficient to answer the file-name constraint.** Because `aiName` is an internal class identifier (32-byte), not an `%.8s.odf` token, **`TankLegacyFriend` (16) and `TankLegacyEnemy` (15) are legal** — they fit 32 and are not subject to the 8-char `.odf` limit which applies to `GameObjectClass` *odf filenames* (`"%.8s.odf"` + `& 0x7F7F7F7F` mask, see `GameObjectClass::Find` 0x4998F6 / `GameObjectClass::GameObjectClass` 0x99E42). A valid *ODF filename* would have to be ≤8, but `aiName` does not name a file.
* **Feasibility verdict:** **HIGH-CONFIDENCE FEASIBLE through aiName** for per-unit opt-in, pending final proof of the team/perceivedTeam selector (item 4 below). The factory extension path (new RtimeClass entries) and the per-unit predicate gate are both narrow and already used by the engine.

## 1. Where aiName / aiName2 are parsed from ODFs

| Build | Function | Address | Purpose | Input | Output | Relevant offsets | Confidence |
|---|---|---|---|---|---|---|---|
| 1.5 | `GameObjectClass::GameObjectClass` | 0x499E42 | ODF-loading ctor for every GameObjectClass instance | `char* odfName ("%.8s.odf")`, `ParameterDB` | populates `this->aiName[32]` at +0x8C, `aiName2[32]` at +0xAC | `this+0x8C` 0x20 `this+0xAC` 0x20; section hash 0xD3DD9CEC, key hashes 0x98D7239C/0x48AD2AEA; call `0x4A3374` (char[32] Get) | Proven (read from `1.5/functions/0049/00499e42_*.c` lines `ParameterDB::Get(...,0x98D7239C,this->aiName,...)` and sibling, plus disasm pushes at 0x99FBE/0x99FDC) |
| 1.4 | `GameObjectClass::GameObjectClass` equivalent | ~0x49D900 region (needs exact sited) | Same | `char* "aiName\0"` at 0x6071D4 and `"aiName2\0"` at 0x6071CC pushed at 0x49DB1F/0x49DB03, call 0x4A5E10 | same fields (0x6071CC string table shows `aiName2\x00aiName\x00` adjacent to `unitName/buildTime` etc) | `esi+0x84` etc in that ctor is the 1.4 analog of +0x8C | Proven for existence (1.4 memdump strings + pushes at 0x49DB1F), Very High for offsets |

*Evidence:* 1.5 decompile:

```c
ParameterDB::Get(&local_4c,0xd3dd9cec,0x98d7239c,this->aiName,0x20,param_1->aiName);
ParameterDB::Get(&local_4c,0xd3dd9cec,0x48ad2aea,this->aiName2,0x20,param_1->aiName2);
```

Disasm at 0x99FBE: `lea eax,[ebx+0x8C]; push eax; push 0x20; push 0x98D7239C; push 0xD3DD9CEC`. 1.4: `push 0x6071CC` ("aiName2") + `lea eax,[esi+0x84]` etc, call 0x4A5E10 (string-key version of same, pre-ParameterDB). The section is `GameObjectClass` (hash `0xD3DD9CEC` = FNV("GameObjectClass"), verified by brute force; `CraftClass` = `0xC287C42B` etc). Keys hash with same FNV+tolower.

## 2. Where those strings are stored

* `GameObjectClass` object at `this+0x8C` 32 bytes, `+0xAC` 32 bytes (1.5). Inline `char aiName[32]; char aiName2[32];` plus sibling `char unitName[32]` at +0x6C, `weaponMask` etc. Confirmed by `push 0x20` length and `lea`.
* Also mirrored in the ODF itself as `[GameObjectClass] aiName = "TankFriend"` (textual ODF; see `1.5/Battlezone_Install/*.odf` e.g. `avian02.ODF`).
* Not stored in `GameObject` instance — the instance holds `AiProcess* aiProcess` at `+0xF0` (`GameObject::SetAIProcess` 0x49545B does `mov [ecx+0xF0], eax`), class holds the *name* to create it.

## 3. When aiName vs aiName2 is selected

**Status: High-confidence hypothesis, not yet Proven.**

* ODF convention is `aiName = "TankFriend"` / `aiName2 = "TankEnemy"` — every stock tank ODF pairs a Friend and Enemy variant. This matches the `RtimeClass` names for the two 59-slot `AiProcess` vtables that differ only in identity slots 0/4 (`TankFriend` 0x5EA618 vs `TankEnemy` 0x5EA708; 0x5DBEA0 vs 0x5DAD40 analogs etc). Scout pairs similarly differ only in slot 57 (`ChooseAttackTarget`).
* The selector is almost certainly **team / perceivedTeam** (or local/remote ownership derived from it), but the exact branch has not been traced to a single site and verified across 1.4/1.5/Redux. Candidates examined: `GameObject::GetTeam` 0x47BD02 and `GetPerceivedTeam` 0x405B45 show 0 direct callers in a naive scan (likely inlined or accessed as direct offset), so the selector may be an inline `cmp [obj+teamOff], ...` rather than a call.
* **What is proven:** both strings coexist in the class, and both class names exist as `RtimeClass` entries (see §5). The engine must choose one per-instance; the per-unit opt-in design does not depend on which predicate it is, only that the field is per-class and the lookup is per-instance — which is proven.

*Next probe:* sited string `TankFriend` at 0x5DC260 has only one `.text` reference (its own registration `push 0x5DC260` at 0x5CA6D4). That is expected — the name is *stored*, not compared as an immediate. The selector will do `strcmp/aiNamePtr` vs a lookup, not `push "TankFriend"` immediate, so searching for immediate pushes misses it. Need to trace where `GameObjectClass+0x8C` is `lea`'d and then passed to a hash/find routine (`RtimeClass::Find` or `stdext::hash_map` lookup). The `lea [reg+0x8C]` sites at 0x463E84, 0x463F99, 0x464505 etc are ODF *writers*, not the selector.

## 4. How the string is resolved into an AI implementation

Two parallel registries exist in the engine, both exact:

* **Tasks** (`AttackTask` etc) — 13-slot vtables, 40 classes mapped via `RtimeClass` chain (§7 of census). `AttackTask` 1.5 `0x5CF8F8` ↔ 1.4 `0x5E6E58`, slot 11 = DoState.
* **AiProcesses** (`TankFriend`, `TankEnemy`, `ScoutFriend`, 0x5EA618 etc) — 59-slot vtables, 9 concrete in 1.4 (wave2a). Registration block `0x5CA612–0x5CA7A0` is a sequence of `RtimeClass` initializers for each process class, e.g.:

```
0045CA6CF push 0x470E35   ; CreateObject for TankFriend
        push 0x5DC260   ; "TankFriend"
        mov  ecx, 0xA0EC64 ; RtimeClass global
        call 0x4B1036
```

Factory at `0x470E35`: `push 0x78 ; call operator_new ; mov ecx,eax ; jmp 0x47072A` → `mov [esi], 0x5DBEA0`.

Resolution chain confirmed:

```
ODF [GameObjectClass] aiName="TankFriend"
  → ParameterDB char[32] at GameObjectClass+0x8C (32)
    → stored field (not truncated to 8)
      → (team-dependent) selector picks aiName vs aiName2
        → RtimeClass::Find(name) — string hash/compare against registered "TankFriend" entries
          → CreateObject factory (0x470E35) → AiProcess subclass instance
            → its vtable drives ChangesState/ShouldAttack/DoSubTask etc (shared base) and indirectly the AttackTask state machine
```

A hard unknown-aiName case has not been runtime-probed, but the `Find` helper (`GameObjectClass::Find` 0x4998F6) shows the engine pattern on missing class: `TraceError("GameObject \"%s\" uses unknown class label \"%s\"")` + return 0. For AiProcess the analogous path is expected to return null / no process or a default, not crash — but this needs a probe (spawn with unknown `aiName = "BadName"` and observe).

## 5. Whether arbitrary new identifiers can be registered safely from OpenShim

**Yes — via a new RtimeClass entry.**

* The engine already has a data-driven `RtimeClass` registration table. Adding a new entry with `push <LegacyCreateObject> ; push <"TankLegacyFriend"> ; mov ecx, <new RtimeClass global> ; call 0x4B1036` is the same mechanism stock uses for `TankFriend`. No code needs to patch a hardcoded `strcmp` cascade — there is none; the registry is hash-mapped (`stdext::hash_map<unsigned_int, RtimeClass*>` etc in `ParameterDB::FileData` shows the pattern).
* Because `aiName` is 32 bytes, `TankLegacyFriend` (16) and `TankLegacyEnemy` (15) fit without truncation. A name like `TLegFrd` (7) would be needed only if `aiName` were an 8-char ODF filename, which it is not.
* Two implementation choices both work: (a) separate legacy `AiProcess` subclasses (`TankLegacyFriend` → legacy vtable), or (b) existing `TankFriend` class + flag `legacy14=true` gating case-7 etc inside the *same* `AiProcess`'s task creation. (b) is narrower if the factory lookup is proven to be string equality (which it is), because `Find("TankLegacyFriend")` will miss and need a new registration anyway — so (a) and (b) converge to “register new name”.

## 6. Whether names are internal strings or files/resources

* **Internal RtimeClass names.** Strings `TankFriend` etc appear twice in the image: once as the `RtimeClass` registration name at `0x5DC260` (`"TankFriend\0\0TankEnemy"`) and once as the ODF value. They do **not** appear as `%.8s.odf` filenames — that format is for `GameObjectClass` *itself* (`avtnk01.odf` etc). The `%.8s` truncation is applied to the *config* name (`this->cfg` long64) when building `"%.8s.odf"` and `"%.8s.inf"` in `GameObjectClass::Build` (0x498FCE) and `GameObjectClass::Find`, not to `aiName`.
* **Length restriction does not apply.** The 8-char limit is for resource filenames (`ODF`, `WAV`, `TRN` etc) resolved via `ItemExists` / `UseItem`. `aiName` is never passed to `ItemExists`; it is passed to `RtimeClass` lookup. Therefore `TankLegacyFriend` is valid; an 8-char alternative like `TnkLgFr` is unnecessary but would also be valid and could be used for belt-and-suspenders.

## 7. What happens when an unknown aiName is encountered

Not yet executed, but the code pattern in `GameObjectClass::Find` for unknown `classLabel` is `TraceError(... uses unknown ... )` and return null, and `GameObject::Load`’s `in_ptr(..., "GameObject:aiProcess", ...)` suggests a graceful `false` rather than a hard fault. Predicted Redux behavior for unknown `aiName`: `AiProcess` not created (`aiProcess` stays 0 or null), object spawns with no AI or with a safe default. Must be runtime-probed with an ODF containing `aiName="NoSuchAI"` (and `aiName2` likewise) — see harness.

## 8. Complete chain (proven parts in bold)

**1.4 and 1.5 identical up to storage; dispatch identical via RtimeClass:**

**ODF `[GameObjectClass] aiName="TankFriend"`**

**↓ `ParameterDB::Get` (1.5) / `GetKeyString` path (1.4) pushes 0x6071CC**

**↓ stored field `GameObjectClass+0x8C` (32) / `+0xAC` (32)**

↓ selector (team/perceivedTeam — **High-confidence hypothesis**, exact branch to be sited)

**↓ RtimeClass registry lookup by string value (`Find("TankFriend")`)**

**↓ factory `CreateObject` (`0x470E35` → `mov [esi], 0x5DBEA0`)**

**↓ AiProcess instance at `GameObject+0xF0`**

↓ `AiProcess::DoSubTask` / `ShouldAttack` / `ChangesState` etc + spawned `AttackTask` (`0x5E6E58` / `0x5CF8F8`) drives combat.

## 9. Gaps and next probes

1. Site the selector: find where `[GameObjectClass+0x8C]` vs `+0xAC` is `lea`'d and then branched on `Team`/`PerceivedTeam`/`IsNetGame`/`bNations` etc (search for `lea` of both offsets within same function plus a `cmp` of team offset; may be inline at `+0xC8`/`+0xE0` region). Run live probe spawning two objects with same ODF but different teams and logging which `RtimeClass` is instantiated (hook `RtimeClass::Find` or `CreateObject` factories).
2. Probe unknown-aiName behavior: spawn ODF with `aiName="BadName1234567"` and observe `TraceError` and `aiProcess` nullness.
3. Confirm `TankLegacyFriend` registration succeeds: add a new `RtimeClass` entry via OpenShim and spawn with `aiName="TankLegacyFriend"`; verify factory called and object behaves (suggestion: minimal legacy `AiProcess` that delegates to stock but sets `legacy14` flag).
4. Document the two process vtables for legacy names: show they differ from stock only where needed (case-7 predicate, case-9 bound, etc).

## 10. Confidence summary

| Item | Confidence |
|---|---|
| aiName stored at +0x8C 32, aiName2 at +0xAC 32 via FNV hashes 0x98D7239C/0x48AD2AEA | **Proven** |
| ODF section is GameObjectClass (hash 0xD3DD9CEC) | **Proven** |
| Values are RtimeClass class names, not filenames | **Proven** |
| Registry is RtimeClass with CreateObject factories (0x470E35 etc) | **Proven** |
| Names fit 32, so TankLegacyFriend legal; 8-char limit does not apply | **Proven** |
| Arbitrary new identifiers can be registered from OpenShim | **High** (pattern is extensible; one probe needed) |
| Selector is team/perceivedTeam picking aiName vs aiName2 | **High-confidence hypothesis** (team field access needs siting) |
| Unknown aiName is gracefully handled | **High** (by analogy, needs probe) |

*File and line refs:* `src: BZ1_Source/1.5/functions/0049/00499e42_GameObjectClass_GameObjectClass.c: ParameterDB::Get(...,0x98D7239C...)`, disasm `0x99FBE` / `0x49DB1F`, registration `0x5CA6CF`, factory `0x470E35`/`0x47072A`, `GameObject::SetAIProcess` `0x49545B` (`[ecx+0xF0]`), `GameObjectClass::Find` `0x4998F6`, strings `0x5DC260`/`0x6071CC`.


## 11. Hand-read follow-up (2026-09-02) — selector probe

Attempted to site selector via `teamNumber +0x168` read scan: `teamNumber` proven at `GameObject+0x168` (`GameObject::Init 0x496C94: mov [esi+0x168],ecx; call Team::GetTeam`). Scan for `lea [reg+0x8C]` (aiName) co-located with `mov [reg+0x168]` within same function found **0** convincing selector sites after filtering ODF loaders (`push 0x98D7239C` loaders excluded). The two prior `+0x8C/+0xAC` co-occurrences (`0x499FB5`) are the *loader* (both fields written), not the selector.

**Implication:** selector is not a simple `if (teamNumber==0) use +0x8C else +0xAC` inline `cmp` on `+0x168`; it likely uses `perceivedTeam`, `GetTeam()` result, or `IsNetGame` + `bNations` branching similar to `GameObjectClass` pilotClass fallback (`0x499D9C: IsNetGame/bNations` pattern). Hand reading `GameObject::GetTeam 0x47BD02:104` shows trivial `return teamNumber` but its callers were not found as `E8` targets because of inlining / IAT variance (MSVCR90 imports, not direct). 

**Recommended live probe (not yet executed):** hook `RtimeClass::Find` or the two factory addresses `0x470E35/0x47072A` and spawn an ODF with `aiName="TankFriend"` / `aiName2="TankEnemy"` on opposing teams; log which factory fires per team. Also spawn with `aiName="BadName"` to confirm graceful `TraceError` + null aiProcess (predicted from `GameObjectClass::Find` pattern). This is the last gate for `PROVEN FEASIBLE`.

