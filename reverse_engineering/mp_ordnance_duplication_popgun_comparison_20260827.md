# Reverse Engineering Analysis: Multiplayer Ordnance Duplication (Popgun, Day Wrecker, Splinter)

**Date:** 2026-08-27
**Repository:** `GrizzlyOne95/Battlezone98Redux_Shim`
**Branch:** `research/mp-ordnance-duplication-popgun`
**Status:** Popper authority pattern verified / Splinter high-confidence candidate / Day Wrecker root cause reopened

---

## Executive Summary

This document investigates multiplayer secondary-ordnance duplication using the final Redux Popper/Popgun authority pattern as a structural lead.

The original revision overgraded several conclusions as **PROVEN**. An independent repo audit on 2026-08-27 found two material problems:

1. the report transferred the advisory PDB name `_Ordnance_SendNew` directly onto current-binary `FUN_00586ff0` without sufficient mapping evidence; and
2. it identified `FUN_004b0420` as `DayWrecker::Simulate` / explosion logic, but the retained decompile shows that function is a **DayWrecker constructor/initializer**, not simulation or explosion code.

The corrected evidence grades are:

- **Popper authority pattern — VERIFIED IN FINAL REDUX:** `FUN_005a6460` contains `!IsNetGame() || objectTeam == LocalTeam()` immediately around its secondary creation path.
- **Historical claim that this exact gate was introduced in 2.0.131 — NOT YET PROVEN:** the repository does not contain a 2.0.131 executable for a direct pre/post binary comparison.
- **Splinter missing caller-side gate — VERIFIED STATIC FACT:** `FUN_005da6e0` calls `FUN_00586ff0` from its payload loop with no adjacent Popper-style net/team gate.
- **Splinter 2x multiplayer duplication mechanism — HIGH-CONFIDENCE HYPOTHESIS, NOT YET RUNTIME PROVEN:** peer execution, authority, replication, and duplicate object identity must be observed on two PCs.
- **Day Wrecker source-site mechanism — REOPENED / UNPROVEN:** the function identity used as key proof was wrong. The true simulate/collision/explode and Armory launch-create paths must be mapped before proposing a patch.

No production patch should be implemented from this report until the two-PC authority trace closes the relevant decision gates.

---

## 1. Binary and Symbol Provenance

### Repo-tracked artifacts

| Artifact | Role |
| --- | --- |
| `reverse_engineering/repo_corpora/bzr_gog_best_effort/` | portable GOG 2.2.301 best-effort decompile corpus |
| `.../ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/` | current-binary decomp functions |
| `.../pdb_reference/public_functions.csv` | advisory PDB function export |
| `reverse_engineering/prerelease_2016/exes/` | early Redux executables |

### Missing evidence

A Redux **2.0.131 executable is not present** in the tracked corpus. Therefore the documented 2.0.131 Popgun patch-note entry can be used as a historical clue, but the repository cannot presently prove that a specific conditional in final Redux was the exact code change made in that release.

This distinction matters: final-state structure can be proven; exact historical diff attribution cannot.

---

## 2. Popper Final-State Authority Pattern — Directly Verified

Current GOG corpus function:

```text
FUN_005a6460 @ VA 0x005A6460
```

The relevant block is visible directly in the retained decompile:

```c
iVar9 = FUN_00572a70();
if ((iVar9 == 0) ||
   (sVar1 = *(short *)(local_d4 + 0x7c),
    sVar3 = FUN_00572d90(),
    sVar1 == sVar3)) {
    local_d8 = FUN_00586ff0(local_90, *(undefined4 *)(local_d4 + 0xd8));
    ...
}

*(uint *)(*(int *)(local_d4 + 0x14) + 0x14) |= 0x200;
```

The project has previously identified:

- `FUN_00572a70` as the net-game predicate;
- `FUN_00572d90` as local-team retrieval;
- object team at `+0x7C` for this subobject layout.

### What this proves

In the shipped final Redux Popper path, the call to `FUN_00586ff0` occurs only when:

```text
not multiplayer
OR
Popper team == local team
```

This is a concrete native precedent for **caller-side authority/locality gating of a secondary creation path**.

### What this does not prove

It does not, by itself, prove:

- that pre-2.0.131 Popper lacked this exact condition;
- that this exact condition was the 2.0.131 fix;
- that `team == LocalTeam()` is the universal correct authority test for every class;
- that all other secondary-ordnance producers should copy the condition verbatim.

Given known Redux multiplayer locality behavior, authority must be established per object/class rather than generalized from one weapon.

---

## 3. `FUN_00586ff0` — Corrected Identity and Semantics

The original report labelled:

```text
FUN_00586ff0 @ VA 0x00586FF0
```

as `_Ordnance_SendNew` and stated that it directly creates an ordnance object and, in multiplayer, packages/transmits the network packet.

The retained decompile supports only part of that statement.

### Directly visible behavior

`FUN_00586ff0`:

- allocates/initializes an object/class descriptor path;
- obtains/builds an ordnance-like object via `FUN_00583d90` and related calls;
- invokes a virtual method on the resulting object with the supplied parameters;
- returns the created/resolved object pointer.

There is **no explicit `IsNetGame()` test or plainly identifiable packet-send operation in this function body**.

### Advisory PDB mismatch

The advisory PDB export contains a symbol named `_Ordnance_SendNew`, but its advisory RVA does not directly coincide with current-binary RVA `0x00186FF0`. Because the PDB is from a different/advisory build, symbol names must be transferred only through a validated mapping/call-graph match.

Therefore this report now refers to `FUN_00586ff0` as:

> **the current-binary secondary/ordnance creation helper reached by Popper and SprayBuilding**

until its exact network-facing symbol identity is proven.

### Required follow-up

Identify separately:

1. the local object-construction path;
2. the actual network new-ordnance send path;
3. the receive/reconstruction path on a remote peer;
4. whether the virtual call inside `FUN_00586ff0` bridges into one of those network paths.

---

## 4. Splinter / SprayBuilding — Strong Static Candidate

Current GOG corpus function:

```text
FUN_005da6e0 @ VA 0x005DA6E0
```

The retained decompile shows a payload loop that ultimately executes:

```c
local_1d8 = FUN_00586ff0(local_48, local_1d4[0x3d]);
*(undefined4 *)(local_1d8 + 0x80) = 0;
...
local_1d4[0x90] =
    (int)((float)local_1d4[0x90] - *(float *)(local_1d4[0x3e] + 0x178));
```

No adjacent `IsNetGame()` / local-team gate comparable to `FUN_005a6460` is present around that creation call.

### Static fact

**Verified:** the inspected SprayBuilding payload producer has an unconditional caller-side path to `FUN_00586ff0` once its firing-loop conditions are satisfied.

### Why this is suspicious

If remote SprayBuilding instances execute this same firing loop and if authoritative payload objects are also replicated from another peer, then the missing caller-side authority gate is exactly the kind of structure that can produce duplicate secondary gameplay objects.

That is strongly analogous to the final Popper pattern, but analogy is not runtime proof.

### What remains unproven

The repo decompile alone does not establish all of the following:

1. a remote SprayBuilding copy executes the firing loop on the client;
2. that client-created result is a damaging gameplay object rather than a locally expected representation;
3. another peer independently creates the same logical payload;
4. that payload is replicated to the client through a separate network path;
5. both instances coexist and correspond to the observed 2x Splinter symptom.

Therefore the correct classification is:

> **HIGH-CONFIDENCE ROOT-CAUSE CANDIDATE — TWO-PC AUTHORITY TRACE REQUIRED**

not `PROVEN`.

---

## 5. Day Wrecker — Previous Root-Cause Claim Withdrawn

The original report identified:

```text
FUN_004b0420 @ VA 0x004B0420
```

as `DayWrecker::Simulate` and later treated it as an explosion instrumentation target.

That identification is incorrect.

The retained decompile is:

```c
undefined4 * __thiscall FUN_004b0420(
    undefined4 *param_1,
    undefined4 param_2,
    undefined4 param_3)
{
    FUN_005a79f0(param_2, param_3);
    *param_1 = DayWrecker::vftable;
    param_1[6] = DayWrecker::vftable;
    *(undefined1 *)(param_1 + 0x8c) = 0;
    return param_1;
}
```

This is a **constructor/initializer-style function**: it invokes a base/init routine, installs DayWrecker vtable pointers, initializes a field, and returns `this`.

It is not evidence for:

- simulation cadence;
- collision handling;
- detonation position;
- remote/client launch behavior;
- source-site explosion creation.

### Consequence

The prior Day Wrecker chain:

```text
remote Armory simulates launch
 -> local DayWrecker created at source
 -> frame-0 collision
 -> DayWrecker::Explode at Armory
 -> host-replicated second instance/explosion
```

remains a plausible hypothesis consistent with the observed symptom, but **the repository evidence cited in the original report does not prove it**.

### Required re-trace before any patch

Map the actual current-binary functions for:

1. `DayWrecker` constructor;
2. `DayWreckerClass::Build`;
3. `DayWrecker::Simulate` / control path;
4. collision / hit path;
5. explosion/detonation path;
6. Armory launch-state creation call;
7. object locality/remote tests around that call;
8. network send/receive path for the created object.

Only then should a source-site root cause or hook site be named.

---

## 6. Historical Popgun Fix — Correct Evidence Grade

The Redux historical notes identify a multiplayer Popgun duplication fix in 2.0.131. The final Redux binary contains a caller-side authority gate in Popper.

Those facts are **consistent** with the gate being part of that historical fix.

However, without a 2.0.131 binary or a directly comparable before/after function body, this repository cannot currently state:

> "Before 2.0.131 `Popper::Control` lacked this exact gate."

Correct wording:

> The final Popper authority pattern is a strong structural analogue for investigating other secondary-ordnance duplication defects and is consistent with the documented historical Popgun fix.

If a 2.0.131 executable is recovered, compare the Popper function directly and upgrade/downgrade the historical attribution accordingly.

---

## 7. Corrected Comparison Matrix

| Question | Popper final path | Splinter `SprayBuilding` | Day Wrecker / Armory |
| --- | --- | --- | --- |
| caller-side authority gate directly seen? | **Yes** | **No adjacent Popper-style gate** | **Not yet mapped correctly** |
| secondary creation helper identified? | `FUN_00586ff0` call seen | `FUN_00586ff0` call seen | must re-trace |
| exact helper network semantics proven? | **No** | **No** | **No** |
| both peers shown creating same logical payload? | not required for final-state observation | **Not yet** | **Not yet** |
| duplicate runtime object pair observed? | historical symptom/fix context | **Not yet instrumented** | **Not yet instrumented** |
| root cause classification | native authority precedent | **high-confidence candidate** | **open / re-trace required** |

---

## 8. Two-PC Instrumentation Plan

### Phase A — Identify creation vs network functions

Instrument `FUN_00586ff0` as an **unknown-exact-name creation helper**, logging:

```text
[ORDCREATE]
peer role / local player team
caller return address
source object handle
source actual team
source locality/remote state if available
created object pointer/handle
created class/ODF if safely retrievable
spawn position
frame/time
```

Separately identify and instrument the actual network new-ordnance send and receive functions. Do not assume `FUN_00586ff0` itself is the packet sender until the call graph proves it.

### Phase B — Splinter

On host and client, capture one controlled Splinter deployment.

Decision evidence:

- Does `FUN_005da6e0` call the creation helper on both peers for the same source object/tick?
- Which peer emits the network create?
- Which peer receives it?
- How many resulting payload handles exist on each peer?
- Are two client payloads correlated to one logical firing event?
- Which instance applies authoritative damage?

If the client both locally creates a gameplay payload from `FUN_005da6e0` **and** receives an equivalent authoritative payload, the duplication mechanism becomes runtime-proven.

### Phase C — Day Wrecker

Do not instrument `0x004B0420` as Explode; that address is wrong for that purpose.

First resolve the real launch/simulate/collision/explode sites. Then log on both peers:

```text
[DWCREATE] source Armory, caller, locality, spawn transform, velocity
[DWHIT]    object handle, collision target, position, frame
[DWBOOM]   object handle, position, locality, frame
[DWNET]    send/receive identity for the same logical projectile
```

The specific source-site hypothesis is proven only if a remote/non-authoritative peer creates or detonates an extra Day Wrecker at/near the Armory while a separate authoritative projectile also exists.

---

## 9. Patch Decision Gates

### Splinter

Do **not** ship a gate yet.

If two-PC evidence proves that remote SprayBuilding simulation creates a duplicate gameplay payload, then test the smallest caller-side suppression that preserves:

- singleplayer payload generation;
- authoritative multiplayer generation;
- remote visual representation;
- AI-controlled units on the correct authority peer;
- damage count and projectile count;
- cleanup/destruction sequencing.

The final Popper condition is a **candidate precedent**, not automatically the correct universal predicate.

### Day Wrecker

No patch candidate is currently justified. Re-identify the correct functions and first divergence before choosing a hook or authority predicate.

### `SetLocal`

Do not use `SetLocal` as a generic fix. Project multiplayer testing has already shown that changing locality of remote AI can break AI ownership/control and can create asymmetric object behavior.

---

## 10. Regression Matrix for Future Runtime Work

| Scenario | SP | MP authoritative peer | MP remote peer | Required result |
| --- | --- | --- | --- | --- |
| stock Popper | one secondary payload | one logical payload path | one replicated representation | preserve final Redux behavior |
| Splinter | one payload stream | one logical payload stream | no duplicate gameplay stream | prove before patch, then preserve |
| Armory Day Wrecker | one projectile/detonation | one authoritative projectile | no source-site duplicate | root cause still open |
| remote AI secondary ordnance | normal | correct owner simulates | remote AI remains functional | mandatory locality regression check |

Count object handles and damage events; visual similarity alone is insufficient.

---

## 11. Final Evidence Classification

| Claim | Classification |
| --- | --- |
| final `FUN_005a6460` Popper path has `!net || team == localTeam` gate | **Directly verified** |
| that exact gate was definitely introduced in Redux 2.0.131 | **Not proven; 2.0.131 binary missing** |
| `FUN_005da6e0` calls `FUN_00586ff0` without adjacent Popper-style authority gate | **Directly verified** |
| Splinter duplicates because both peers execute that call and also replicate the same payload | **High-confidence hypothesis; two-PC proof required** |
| `FUN_00586ff0` is definitively `_Ordnance_SendNew` and directly transmits packets | **Not established by current decompile/PDB mapping** |
| `FUN_004b0420` is `DayWrecker::Simulate` or `DayWrecker::Explode` | **Incorrect; it is constructor/initializer-style code** |
| Day Wrecker source-site root cause in the original report is proven | **Withdrawn / open** |
| `team == LocalTeam()` should be applied universally to secondary ordnance | **Not established; authority is class/path specific** |

---

## 12. Next Steps

1. Preserve the Popper final-state gate as a known-good **reference pattern**, not a universal rule.
2. Resolve the exact current-binary identity/network semantics of `FUN_00586ff0` and the true send/receive functions.
3. Run the Splinter two-PC creation/send/receive/object-count trace.
4. Re-map Day Wrecker and Armory launch functions from vtables/PDB/call graph before further claims.
5. Run the Day Wrecker two-PC source/impact trace using the corrected function identities.
6. Implement no production hook until the first divergent/non-authoritative creation site is observed.
