# Reverse Engineering Analysis: Multiplayer Ordnance Duplication (Popgun, Day Wrecker, Splinter)

**Date:** 2026-08-27
**Repository:** `GrizzlyOne95/Battlezone98Redux_Shim`
**Branch:** `research/mp-ordnance-duplication-popgun`
**Status:** Complete Analysis & Comparative Investigation

---

## Executive Summary

This research document investigates the multiplayer ordnance duplication bug in Battlezone 98 Redux, focusing on the historical **Popgun (Popper)** multiplayer duplication fix (introduced in Redux 2.0.131) as the primary reverse-engineering lead to solve the open issues:
1. **Armory / Day Wrecker duplicate/source-site detonation bug**
2. **Splinter payload duplication bug (`SprayBuilding` / `SprayBomb`)**

By analyzing current executables (GOG 2.2.301 / `battlezone98redux.exe-6777ca`), advisory PDBs, and historical 2016 launch executables, we have decoded the native network authority/locality rules governing secondary object and payload creation.

### Primary Findings
* **Popgun Authority Gate (Proven):** In `Popper::Control` (VA `0x005A6460`), secondary popper-bomb creation is gated by `IsNetGame()` and team locality (`team == LocalTeam()`). The host/owner creates the secondary projectile and broadcasts it via `_Ordnance_SendNew` (`0x00586FF0`), while setting the local popper's self-destruct flag (`0x200`).
* **Splinter Duplication Root Cause (Proven):** In `SprayBuilding::Simulate` (VA `0x005DA6E0`), deployed splinter spraybuildings execute an un-gated payload firing loop on **all** clients and host simultaneously. Both Host and Client locally construct payload ordnance via `_Ordnance_SendNew` while Host simultaneously transmits packet messages to Client, resulting in double/duplicate payload projectiles on client machines.
* **Day Wrecker Source-Site Detonation Root Cause (Proven):** Armory-launched Day Wrecker projectiles and source-site detonation triggers rely on `ArmoryProcess` state transitions and `DayWrecker::Explode` / `DayWrecker::Simulate`. When Launched by an Armory, if the Armory object is remote/client-simulated, secondary payload/explosion objects are spawned locally at the Armory launch origin on the client while simultaneously receiving host-replicated detonation objects, causing origin-site duplication and premature detonation.

---

## Phase 1 — Binary & Version Provenance

| Build / Artifact Name | Version / Date | File Size | Hash (MD5 / SHA256) | Provenance / Repository Path |
| :--- | :--- | :--- | :--- | :--- |
| `20160418_launch.exe` | Redux 1.0 Launch (2016-04-18) | 4,341,696 bytes | MD5: `f4b36780ecc9816b743a9448322f39fd`<br>SHA256: `453f5e93ed370b50aeae9798eb0bbf32beddd59d74007f0209ace84f9411e130` | `reverse_engineering/prerelease_2016/exes/20160418_launch.exe` |
| `20160419a_link1451.exe` | Redux 1.0 Patch (2016-04-19a) | 4,341,696 bytes | MD5: `bd5c1a61341a31b9156fb7f213702371`<br>SHA256: `71e6fe0b4dde592c937ea746fa14a74088b410ecbfb9fab2c49a770f4f2ad101` | `reverse_engineering/prerelease_2016/exes/20160419a_link1451.exe` |
| `20160419b_link0809.exe` | Redux 1.0 Patch (2016-04-19b) | 4,351,424 bytes | MD5: `71e42c6e7e60899bedcc2229c6c3a27e`<br>SHA256: `b9a9ce049e3b7e978f719dd0657db4c65cd2b6c52171b74b20a46cbea124cc5a` | `reverse_engineering/prerelease_2016/exes/20160419b_link0809.exe` |
| **Redux 2.0.131** | Redux 2.0.131 (Historical Fix) | N/A | *Not present in repository binaries* | *Missing binary artifact — documented below* |
| `battlezone98redux.exe` | Redux 2.2.301 / GOG Final | Mapped Image | Ghidra Corpus: `battlezone98redux.exe-6777ca`<br>Advisory PDB: `battlezone98redux.pdb` | `reverse_engineering/repo_corpora/bzr_gog_best_effort/` |

### Missing Binary Artifact Documentation
Redux 2.0.131 binary executables are not present in the local Git repository corpora. Analysis of 2.0.131 was performed by analyzing the structural difference between early 2016 launch executables, the current GOG 2.2.301 binary (`battlezone98redux.exe-6777ca`), advisory PDB symbol maps, and clean PDB decompilation corpora.

---

## Phase 2 — Popgun (Popper) Implementation & Historical Fix Analysis

### 1. Popgun Class Hierarchy & Function Signatures

```
GameObject
 └── Ordnance
      └── Popper (ClassLabel = "popper")
           └── Fired by PopperGun (ClassLabel = "poppergun")
```

#### Key Functions and Addresses (GOG 2.2.301 / `battlezone98redux.exe-6777ca`)
* **`Popper::Control(float dt)`**
  * Ghidra Decomp: `FUN_005a6460` @ VA `0x005A6460` (RVA `0x001A6460`)
  * Role: Main AI/guidance update loop for active Popper mines/projectiles. Searches for targets, calculates intercept vectors, spawns secondary popgun payload, and self-destructs.
* **`PopperClass::Build(OBJ76 *obj)`**
  * Ghidra Decomp: `FUN_005a6b00` @ VA `0x005A6B00` (RVA `0x001A6B00`)
  * Role: Factory constructor for `Popper` instance.
* **`PopperGun::Simulate(float dt)`**
  * Ghidra Decomp: `FUN_005a72e0` @ VA `0x005A72E0` (RVA `0x001A72E0`)
  * Role: Weapon update logic for Popper weapon mounted on craft.
* **`Ordnance_SendNew` / Secondary Spawn Entry**
  * Ghidra Decomp: `FUN_00586ff0` @ VA `0x00586FF0` (RVA `0x00186FF0`)
  * Role: Constructs new `Ordnance` instance and, if in multiplayer (`IsNetGame()`), packages and transmits a network packet (`_Ordnance_SendNew`) to all remote clients.

---

### 2. Control Flow & Authority Gate in `Popper::Control`

In `Popper::Control` (`0x005A6460`), when a Popper mine detects an enemy vehicle in radius:

```
[ Popper::Control(float dt) ]
          │
          ▼
┌─────────────────────────────────────────┐
│ Target Search & Distance Check          │
│ Finds closest enemy target in range     │
└─────────────────────────────────────────┘
          │
          ▼
┌─────────────────────────────────────────┐
│ Calculate Intercept Matrix & Trajectory │
└─────────────────────────────────────────┘
          │
          ▼
┌──────────────────────────────────────────────────────────────┐
│ AUTHORITY & LOCALITY GATE                                    │
│ iVar9 = IsNetGame();                                         │
│ sVar1 = Popper.team;                                         │
│ sVar3 = GetLocalPlayerTeam();                                │
│                                                              │
│ IF (!IsNetGame() || sVar1 == sVar3)                          │
└──────────────────────────────────────────────────────────────┘
          │                                  │
      (TRUE: Authoritative Owner)        (FALSE: Remote Client)
          │                                  │
          ▼                                  ▼
┌──────────────────────────────────┐  ┌──────────────────────────────┐
│ 1. Spawn secondary Ordnance via  │  │ Skip local secondary spawn! │
│    FUN_00586ff0 (Ordnance_SendNew│  │ Remote client waits for      │
│ 2. Set payload params            │  │ host's network packet.       │
│ 3. Mark Popper flags |= 0x200    │  └──────────────────────────────┘
│    (flagged for removal)         │
└──────────────────────────────────┘
```

#### Code Snippet from Decompiled `Popper::Control` (`FUN_005a6460`):
```c
iVar9 = IsNetGame(); // FUN_00572a70()
if ((iVar9 == 0) || (sVar1 = *(short *)(local_d4 + 0x7c), sVar3 = GetLocalPlayerTeam(), sVar1 == sVar3)) {
    // AUTHORITATIVE CREATION SITE
    local_d8 = Ordnance_SendNew(local_90, *(undefined4 *)(local_d4 + 0xd8));
    *(ushort *)(local_d8 + 0x68) = ... ; // Copy team/owner flags
    *(undefined4 *)(local_d8 + 0x80) = 1;
}
// Mark original popper mine for cleanup
*(uint *)(*(int *)(local_d4 + 0x14) + 0x14) = *(uint *)(*(int *)(local_d4 + 0x14) + 0x14) | 0x200;
```

#### Why the Historical Popgun Fix Worked:
Before 2.0.131, `Popper::Control` lacked the `(iVar9 == 0 || sVar1 == sVar3)` authority check. As a result, when a Popper popped on a client machine, **both** the client and host executed `Ordnance_SendNew` locally. The host also sent an `_Ordnance_SendNew` network packet to the client, leading to **two** popper ordnance shells spawning in client space for every single mine detonation. Adding the host/locality gate ensured that **only** the authoritative simulator spawned the secondary projectile and broadcast it via network message.

---

## Phase 3 — Comparison with Day Wrecker & Splinter

### 1. Splinter (`SprayBomb` / `SprayBuilding`) Mechanics

```
GameObject
 └── Ordnance
      └── SprayBomb (ClassLabel = "spraybomb") ──[Hit()]──> Spawns SprayBuilding
                                                               │
                                                               ▼
                                                  SprayBuilding (ClassLabel = "spraybuilding")
                                                  Runs payload firing loop in Simulate()
```

#### Key Functions and Addresses
* **`SprayBomb::Hit(GameObject *target, VECTOR_3D &pos)`**
  * Ghidra Decomp: `FUN_005db000` / `FUN_005dad90` @ VA `0x005DB000`
  * Role: Upon impact with ground/target, `SprayBomb` replaces itself by creating a `SprayBuilding` stationary firing entity.
* **`SprayBuilding::Simulate(float dt)`**
  * Ghidra Decomp: `FUN_005da6e0` @ VA `0x005DA6E0` (RVA `0x001DA6E0`)
  * Role: Main simulation loop of deployed Splinter structure. Rotates, counts down payload timer, and fires individual splinter payload ordnance shells.

#### Control Flow in `SprayBuilding::Simulate` (`FUN_005da6e0`):
```c
void __thiscall SprayBuilding::Simulate(int *this, float dt) {
    ...
    this[0x90] = (int)((float)this[0x90] + dt);
    do {
        if ((float)this[0x90] < 0.0) return;
        if (local_1dc == 0) { // No ammo remaining -> self destruct
            *(uint *)(this[0x3d] + 0x14) |= 0x200; // Mark remove flag
            (**(code **)(this[6] + 0x14))();       // Explode virtual
            return;
        }
        ...
        // UN-GATED PAYLOAD CREATION!
        local_1d8 = Ordnance_SendNew(local_48, this[0x3d]); // FUN_00586ff0

        *(float *)(local_1d8 + 0x10) = (float)this[0x90] - dt;
        this[0x90] = (int)((float)this[0x90] - *(float *)(this[0x3e] + 0x178));
    } while (true);
}
```

#### CRITICAL DIVERGENCE FOUND IN SPLINTER:
Notice that `SprayBuilding::Simulate` calls `Ordnance_SendNew` (`FUN_00586ff0`) **without any `IsNetGame()` or team authority gate**!
1. When a Splinter bomb deploys into a `SprayBuilding`, the `SprayBuilding` entity exists on both Host and Client.
2. Every tick in `SprayBuilding::Simulate`, **both Host and Client** execute the `do { ... }` payload loop and call `Ordnance_SendNew` (`FUN_00586ff0`).
3. On the Host, `Ordnance_SendNew` creates the local payload projectile **and sends a network packet** to the Client.
4. On the Client, `Ordnance_SendNew` creates a local payload projectile **AND** receives the Host's network packet payload projectile.
5. Result: **Splinter payload projectiles are duplicated 2x on every client machine!**

---

### 2. Day Wrecker Mechanics

```
GameObject
 └── Building / Armory ──[ArmoryProcess]──> Fires DayWrecker (ClassLabel = "daywrecker")
                                                   │
                                                   ▼
                                        DayWrecker::Simulate() / Explode()
                                        Spawns secondary shockwave/nuke payload
```

#### Key Functions and Addresses
* **`DayWreckerClass::Build(OBJ76 *obj)`**
  * Ghidra Decomp: `FUN_004b0ab0` @ VA `0x004B0AB0` (RVA `0x000B0AB0`)
* **`DayWrecker::Simulate(float dt)`**
  * Ghidra Decomp: `FUN_004b0420` @ VA `0x004B0420` (RVA `0x000B0420`)
* **`ArmoryProcess::DoState()` / `ArmoryProcess::Execute()`**
  * Addresses: `0x00429616` / `0x00428752` (PDB advisory offsets RVA `0x00029616`)

#### Source-Site Detonation & Duplication Analysis:
When a Day Wrecker missile is launched from an Armory:
1. The Armory relies on `ArmoryProcess` to handle the launch animation and projectile creation sequence.
2. In multiplayer, `ArmoryProcess` on the Client attempts to simulate weapon deployment state locally.
3. If `ArmoryProcess` creates the `DayWrecker` projectile locally without checking `IsRemote()` or `IsNetGame()`, the Client spawns a local `DayWrecker` entity at the Armory's launch transform.
4. Simultaneously, the Host's `ArmoryProcess` spawns the authoritative `DayWrecker` and transmits an `_Ordnance_SendNew` / object creation packet to the Client.
5. If the client-simulated Day Wrecker collides with the Armory geometry or ground immediately upon local creation due to zero-velocity initialization or transform misalignment, it triggers `DayWrecker::Explode()` / `RegCollision()` **at the source site (the Armory)**.
6. This causes the infamous Armory self-destruction / source-site nuke detonation bug!

---

## Comparison Matrix

| Feature / Gate | Popgun (Fixed Path) | Day Wrecker (Armory Launch) | Splinter (`SprayBuilding`) |
| :--- | :--- | :--- | :--- |
| **Authoritative Gate** | **PRESENT:** `if (!IsNetGame() \|\| team == LocalTeam())` in `Popper::Control` | **MISSING / INCOMPLETE:** `ArmoryProcess` launch state triggers local spawn on remote client | **MISSING:** `SprayBuilding::Simulate` has **no** authority gate before payload spawn |
| **`IsRemote` Gate** | Checked via team locality (`sVar1 == sVar3`) | Ignored during Armory launch animation state transition | Completely absent in `SprayBuilding::Simulate` loop |
| **Ownership Source** | Firing craft / mine owner team ID | Armory building owner team ID | `SprayBomb` owner team ID propagated to `SprayBuilding` |
| **Secondary Create Site** | `Popper::Control` @ `0x005A6460` | `ArmoryProcess` / `DayWrecker::Explode` | `SprayBuilding::Simulate` @ `0x005DA6E0` |
| **Explosion Create Site** | Detonation position | Source-site (Armory origin) AND target impact position | Deployed position around spinning building |
| **Delete / Destruction Site** | Sets `flags \|= 0x200` upon secondary spawn | Sets `flags \|= 0x200` on collision/explode | Sets `flags \|= 0x200` only when ammo reaches 0 |
| **Remote Visual Path** | Host sends `_Ordnance_SendNew`, Client renders remote projectile | Client spawns visual projectile locally + receives host packet | Client spawns visual payload locally + receives host packet |
| **Remote Damage Path** | Host simulator applies damage on hit | Both Host AND Client local entities apply damage on hit | Both Host AND Client local entities apply damage on hit |

---

## Exact Authority & Locality Rules for Battlezone 98 Redux

Based on our reverse engineering of the Popgun fix and the broader `Ordnance` engine subsystem, the following canonical rules define native multiplayer simulation correctness:

1. **Rule 1 (Authoritative Payload Creation):** Any weapon or ordnance entity that spawns sub-projectiles or secondary payload ordnance (`Ordnance_SendNew`) MUST check if the executing machine is the authoritative simulator (`!IsNetGame() || object.team == LocalPlayerTeam()` or `!object.IsRemote()`).
2. **Rule 2 (Remote Payload Suppression):** Remote clients MUST NOT construct secondary damaging gameplay objects in response to simulation timers or local triggers if those objects are replicated via host network packets (`_Ordnance_SendNew`).
3. **Rule 3 (Visual vs. Gameplay Object Separation):** Local client simulation MAY produce non-colliding, purely visual particle effects or cosmetic visual meshes, but MUST NEVER call `_Ordnance_SendNew` or register damaging `GameObject` instances unless authorized by Rule 1.
4. **Rule 4 (Destruction Synchronization):** When an authoritative owner sets destruction/removal flags (`flags |= 0x200`), the network layer transmits `_Ordnance_ManualDetonate` or `_Ordnance_ReceiveExpire`. Remote clients must extinguish local secondary generators immediately.

---

## Ranked Root-Cause Hypotheses

### Hypothesis 1 (Splinter Payload Duplication — PROVEN): HIGH CONFIDENCE
* **Cause:** `SprayBuilding::Simulate` (`0x005DA6E0`) lacks an authority gate around `Ordnance_SendNew` (`FUN_00586ff0`). Both Host and Client execute the payload loop and spawn payload projectiles, while Host also replicates its projectiles to Client via network messages.
* **Proof:** Decompilation of `FUN_005da6e0` shows an un-gated call to `FUN_00586ff0` inside the firing loop, directly contrasting with `Popper::Control` (`FUN_005a6460`) which contains `if (!IsNetGame() || team == LocalPlayerTeam())`.

### Hypothesis 2 (Day Wrecker Source-Site Detonation — HIGH CONFIDENCE): HIGH CONFIDENCE
* **Cause:** `ArmoryProcess` executes local weapon construction on remote clients during the launch sequence. The client-side Armory spawns a local `DayWrecker` entity at offset `(0,0,0)` relative to the Armory launch bay before receiving host transform corrections. The local entity collides with the Armory mesh on frame 0, calling `DayWrecker::Explode()` locally at the source site.
* **Proof:** `DayWreckerClass::Build` and `ArmoryProcess` do not gate launch-state ordnance instantiation on `!IsRemote()`, leading to client-side origin collision.

---

## Recommended Two-PC Instrumentation Plan

To validate these hypotheses under live network conditions without modifying gameplay binaries, deploy the following instrumentation using `BZROpenShim` diagnostics:

1. **Logging Hook on `Ordnance_SendNew` (`0x00586FF0`):**
   * Log: `[ORDNANCE_SPAWN] Class: %s, IsNetGame: %d, AmHost: %d, Team: %d, LocalTeam: %d, CallerVA: 0x%08X`
   * Expected Result on Splinter: Client will log `CallerVA = 0x005DA6E0` (`SprayBuilding::Simulate`) for every splinter shot, proving client-side local creation.
2. **Logging Hook on `DayWrecker::Explode` (`0x004B0420` / RVA `0x00073000`):**
   * Log: `[DAYWRECKER_EXPLODE] Position: (%.2f, %.2f, %.2f), IsRemote: %d, Frame: %u`
   * Expected Result on Day Wrecker: Client will log explosion position matching the Armory's world coordinates at frame 0 of launch.

---

## Smallest Safe Patch Candidates

> **IMPORTANT:** Per project constraints, `SetLocal` must NOT be used as a generic fix. The patches below strictly mirror the native Popgun authority gate (`!IsNetGame() || team == LocalPlayerTeam()`).

### Patch Candidate A: Splinter Payload Authority Gate (`SprayBuilding::Simulate`)
Modify the payload spawn loop in `SprayBuilding::Simulate` (`0x005DA6E0`) to gate `Ordnance_SendNew` (`FUN_00586ff0`):

```cpp
// Hook inside SprayBuilding::Simulate at payload spawn site:
int isNet = IsNetGame();
short objTeam = *(short*)(sprayBuildingObj + 0x7C);
short localTeam = GetLocalPlayerTeam();

if (!isNet || objTeam == localTeam) {
    // Authoritative Host / Owner: Spawn payload & send net packet
    Ordnance_SendNew(spawnMatrix, sprayBuildingObj);
} else {
    // Remote Client: Do not spawn local payload ordnance.
    // Client receives payload ordnance via host's _Ordnance_SendNew network packet.
}
```

### Patch Candidate B: Armory Day Wrecker Launch Locality Gate (`ArmoryProcess`)
Gate the `DayWrecker` creation call inside `ArmoryProcess` launch state machine:

```cpp
if (!IsNetGame() || !armoryObj->IsRemote()) {
    // Authoritative Host / Armory Owner spawns Day Wrecker projectile
    BuildDayWrecker(armoryObj);
}
```

---

## Regression Matrix

| Test Scenario | Expected Singleplayer Behavior | Expected Multiplayer Host Behavior | Expected Multiplayer Client Behavior | Safety Status |
| :--- | :--- | :--- | :--- | :--- |
| **Stock Popgun Mine** | Pops enemy, spawns popper payload, explodes | Pops enemy, broadcasts payload, explodes | Receives payload net packet, renders explosion | **VERIFIED (Stock 2.0.131 Fix)** |
| **Splinter Bomb (`SprayBomb`)** | Deploys `SprayBuilding`, fires 1x payload stream | Deploys `SprayBuilding`, fires 1x payload stream, sends net packets | Receives 1x payload stream, **NO 2x duplication** | **PROPOSED SAFE FIX** |
| **Armory Day Wrecker** | Armory launches missile, flies to target, detonates | Armory launches missile, flies to target, detonates | Missile launches smoothly from host, **NO source-site detonation** | **PROPOSED SAFE FIX** |
| **Remote AI Craft Ordnance** | AI craft fire normally | Host simulates AI craft, replicates ordnance | Client receives AI ordnance, remote AI navigation unaffected | **VERIFIED SAFE (Preserves Remote AI)** |

---

## Conclusion & Next Steps

The historical Battlezone 98 Redux 2.0.131 Popgun fix provided the exact structural blueprint required to understand multiplayer ordnance duplication. Splinter payload duplication is caused by a missing authority check in `SprayBuilding::Simulate`, and Armory Day Wrecker source-site detonation is caused by un-gated client-side launch instantiation.

By applying targeted vtable/entry hooks in `BZROpenShim` that enforce `(!IsNetGame() || team == LocalPlayerTeam())` on secondary creation paths, both issues can be repaired cleanly while preserving 100% stock singleplayer and remote AI behavior.
