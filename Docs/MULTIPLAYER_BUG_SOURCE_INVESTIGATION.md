# Multiplayer Bug Source Investigation — Battlezone 98 / Redux

> **2026-09-04 correction — Splinter and Daywrecker:** The qualification in
> [MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md](MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md)
> supersedes this report's explosive-authority conclusions, confidence grades,
> proposed guards, and before/after diagrams (including executive-summary rows 2–5).
> Splinter payload `Build` immediately sets `bSend = 0` in both the 1.5 reference
> and Redux: the claimed owner-payload send plus receiver-payload duplication is
> contradicted. `SprayBomb` is ordnance; its deployed producer is reconstructed
> per peer. An owner-only payload/deployment guard is not justified.
> One crater call on each of two peers does not mutate either peer's buffer twice.
> `DayWrecker::Explode` has no direct `MakeCrater` call; `Destroy` sends state,
> and `RemoteDelete`'s final virtual call is class-conditional, not an unconditional
> Daywrecker explosion. Repeated same-peer terrain mutation and the claimed spire
> mechanism remain unproven. `GetNormalPtr` byte shifts alone do not establish a
> height-buffer mutation. Do not implement the remote crater suppression or whole
> `Simulate` returns proposed below. The historical body is retained for provenance;
> unrelated investigations are unchanged.

**Date:** 2026-09-04  
**Scope:** Source-archaeology + network-authority investigation across BZ1 source variants, Redux decompilation, and OpenShim / community patches.  
**Goal:** Evidence-backed root-cause mapping for ten longstanding multiplayer bugs; not a broad implementation PR.  
**Repositories examined:** `GrizzlyOne95/BZ1_Source` (1.4 / 1.5 / TRO1.3 / decomp1.4 / diff_14_15 / Redux/Raw .C), `GrizzlyOne95/Battlezone98Redux_Shim` (OpenShim) + `battlezone-netcode-patch`, local 1.5 PDB-matched decomp corpus at `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/all_decompiled.c` (15045/15070), GOG best-effort corpus at `reverse_engineering/repo_corpora/bzr_gog_best_effort/`.

> **Method:** All addresses below are VA = image-base 0x400000 + RVA. 1.5 addresses are IMPORTED from `bzint.pdb` (exact-match 3,495,936 B exe) and are therefore exact. Redux addresses are from the 31,948-file `Redux/Raw .C` Ghidra dump and the GOG 2.2.301 best-effort corpus; they carry advisory / best-effort confidence unless cross-validated by RTTI/vtable/strings. Confidence grades are explicit per finding.

---

## Executive Summary

| Bug | Best current explanation | Key function / path | Confidence | Redux affected? | Likely Shim-fixable? |
|---|---|---|---|---|---|
| 1. Packet-loss / traffic-storm recovery | No reliable retransmit / no out-of-order buffering; rigid sequential discard at `dp`/Ordnance layer; bandwidth governor walks to floor and never recovers; Ordanance `RO` packet loss is silently dropped | `Ordnance_SendNew @00533c82` / `Ordnance_Receive @00534666` / `Ordnance_ControlAll @00533a92` / `Net::AdjustBandwidth @004ddd94` / `battlezone-netcode-patch` write-up | MEDIUM | Yes | Yes (net_optimizer.cpp already partially: socket buffers + 45 ms reorder) |
| 2. Armory / Daywrecker duplicate detonation | `DayWrecker::Simulate @0052d029` checks `flags &4 ==0` (deployed state) not `IsLocal/IsRemote`; calls `MakeCrater` + `ExplosionClass::Build` without authority guard; remote replica therefore executes gameplay side-effects | `DayWrecker::Simulate`, `PowerUp::Simulate @004a9a91` (has `IsRemote` guard), `MakeCrater @0051f74c`, `DayWrecker::Explode @0052d234` | HIGH | Yes | Yes, narrow |
| 3. Daywrecker terrain-spire corruption | Duplicate detonation × N peers ⇒ `MakeCrater` / `GetNormalPtr` bitwise shifts executed N times on same 9 texels; operation is non-idempotent (`>>1`, `>>2`, `=0`), so second application is not a no-op — same deformation applied twice = spire/height corruption | `MakeCrater` + `GetNormalPtr` | HIGH (mechanism) / MEDIUM (visible spire = repeated shift) | Yes | Yes (same gate as #2) |
| 4. Splinter multiplayer payload duplication | `SprayBuilding::Simulate @0053a779` (deployed splinter) calls `OrdnanceClass::Build` / `FUN_00586ff0`-equivalent creation helper in an unconditional loop with **no** `!IsNetGame \|\| team==LocalTeam` gate; contrast `Popper @005a6460` which *does* gate. Remote peer therefore locally spawns authoritative ordnance that is also replicated. | `SprayBuilding::Simulate`, `SprayBomb::Hit @0053abbf`, Popper reference `FUN_005a6460` | HIGH | Yes | Yes, narrow (caller-side gate) |
| 5. Splinter deployed collision response | `SprayBomb::Hit` converts bomb→`SprayBuilding`; `SprayBuilding` inherits `Building` authority pattern but `SprayBuilding::Simulate` never checks destroyed-flag / `DistributedObject::IsRemote` before firing loop; remote physics/collision therefore drives payload creation | `SprayBomb::Hit`, `SprayBuilding::Simulate`, `Building::Simulate @00482??` | MEDIUM-HIGH | Yes (stock legacy) | Yes (already shipped as `SPLINTER_UNDEAD` fix; extends to authority) |
| 6. Password-lobby friend invites | Invite payload carries lobby ID via `DoP2PConnect` / WebSocket `DoJoinLobby` but omits `password`; normal join path prompts + validates via `dp` session password; invite path bypasses prompt and fails `dp` validation | `bzrnet_server/server.py` : `DoP2PConnect`, `DoJoinLobby`; `Net::Send`/session password handling | MEDIUM | Yes | Yes (prompt-on-invite, do not transmit plaintext) |
| 7. MPI host-leaving bug | No host migration; host owns `AiMission`, `DistributedObject` lifetime, score; `DistributedObject::TakeOwnershipFromPlayer` exists but mission authority is not reassigned; disconnect triggers `RemoteDelete` on remote objects then stall vs clean termination race | `DistributedObject::TakeOwnershipFromPlayer @0049007a`, `RemoteDelete @0048ffb7`, `AiMission::End @00401b11` | MEDIUM | Yes | Partial (graceful termination + ownership handoff for non-mission objects) |
| 8. SucceedMission / FailMission MP transport failure | `AiMission::End @00401b11`, `FailMission @004015db`, `SucceedMission @004015f5` write local `done/shutdownTime/failed/resultName` only; no `Net::Send` / no `Send(…)` RPC; Lua bindings `FailMission(lua) @004183db` / `SucceedMission(lua) @00418410` same; mission end never becomes a network event | `AiMission::End`, `Manage_AI @0040160f`, `coop_campaign_netcode_notes.md` | CONFIRMED | Yes (since 1.4) | Yes (Reloaded pattern: `Send` + `Receive`) |
| 9. Host sniper kills missing from scoreboard | Sniper path `Net::SendSnipe @004de74f` → `Net::HandleSnipe @004df3ba` → `RecordDeath → SendKill → HandleKill`. Local loop `GameObject::UpdatePosition`/kill for host uses direct `RecordDeath` without `HandleSnipe` broadcast? Host path bypasses `HandleSnipe`’s `DistributedObject::RecordDeath` if victim is local and `bSniper` packet not sent (victim locality short-circuit). Remote sniper kill *does* go via packet → `HandleSnipe` → scoreboard. | `Net::SendSnipe`, `Net::HandleSnipe`, `NetPlayer::RecordDeath @004e0cc5`, `DistributedObject::RecordDeath @0048a256/0048a281` | MEDIUM-HIGH | Yes | Yes |
| 10. Multiplayer freecam exploit | Camera mode transition has no `Net::IsNetGame() && IsNormalParticipatingPlayer && IsAlive && !IsSpectator` guard; freecam is SP/editor/cinematic legitimate but reachable while alive in MP | `*Camera*` modes, `View_Record`, `SniperInterface` as precedent; no MP guard found in examined traces | MEDIUM (existence) / LOW (exact predicate) | Yes | Yes, narrow |

---

## Critical Multiplayer Model — Authority Mapping

### Actual symbols (1.5 PDB exact)

| Concept | Real symbol | Location | Semantics |
|---|---|---|---|
| “Is network game?” | `Net::IsNetGame()` / `Net_IsNetGame()` | `all_decompiled.c:1499, 5515` | global `dp != NULL` and `Net::dp` established |
| Distributed object | `DistributedObject` | `0048ed50` ctor, `0048f80b` `SetLocal`, `0048e988` `SetRemote` | mix-in at `GameObject +0x20` (second base) |
| Local vs Remote | `DistributedObject::IsLocal` (`0048a248`), `IsRemote` (`0048a23e`) | `this->object_type == 1` vs `2`; `0`=unowned | authoritative |
| Network ID | `dwLocalID : ulong` (`GetID @0048a252`), `activnet_id : ushort` (`GetPlayerID @0048a206`) | high 16 bits = `activnet_id`, low 16 = `dwLocalIDCounter++` in `SetLocal` | globally unique while local |
| Object creation replication | `DistributedObject::Create @0048e9e4` (receives `param_2` packet with `dwLocalID`, class bytes, `RMAT` matrix) | verifies not already in `localDistributedObjectMap` / `remoteDistributedObjectMap` before `GameObjectClass::Build` | reliable create path (permanent state) |
| Destruction | `DistributedObject::Destroy @0048f72d` / `RemoteDelete @0048ffb7` / `Explode @0048ff56` | `Destroy` sets packet byte `6`, flags `flags\|0x280`, erases `remoteDistributedObjectMap`, enqueues `delLocalIDMap`, calls `dpSetPlayerData`; `RemoteDelete` adds `PO` packet send `Net::Send(..., packet_buffer, 0xc)` before `Destroy` | |
| Ordnance (separate subsystem) | `Ordnance`, `OrdnanceClass`, `Ordnance_SendNew @00533c82`, `Ordnance_Receive @00534666`, `Ordnance_ControlAll @00533a92` | ordnanceList + `netOrdnanceMap : map<pair<sourceTeam,ordid>, Ordnance*>` | NOT DistributedObject; its own unreliable `RO` datagram |
| Score | `NetPlayer::RecordDeath @004e0cc5`, `HandleKill @004e0d59`, `SendKill @004ddb79`, `HandleSnipe @004df3ba` | `netPlayerByTeam[team]` array; `Increment_Player_Kills/Deaths` + `SendKill(myId, victimId, team)` | team-indexed, not player-indexed directly |

**Ownership vs Host:**

- `host` (the peer that created the `dp` session, `hosting == true`, `IsHost()`) is distinct from `object owner` (`activnet_id` encoded in `dwLocalID`, or `Ordnance::source`).
- Weapons / projectiles **inherit** ownership from firing craft via `Ordnance::source = Net_GetMyPlayerID()` in `Ordnance_Receive`’s creation path? No — actually `Ordnance::source` is set to `param_3` (sender’s playerID) in `Ordnance_Receive: pOVar11->source = param_3`, and `ordid = *(ushort*)local_c[1]`. The sender’s `Ordnance_SendNew` encodes `source = owner`? Trace shows `Ordnance_Receive` reading `source` from `DistributedObject::GetGameObject` for owner object; ordnance packets carry `source + ordid`. The **firing craft’s** `activnet_id` becomes ordnance `source`.
- Host leaving != owner leaving. Host departure kills session; per-object ownership transfer exists (`TakeOwnershipFromPlayer`) but **mission authority** (`AiMission`, `mission->done`, `Team` state) is never migrated — see bug #7.

### Reusable side-effect classification (A/B/C)

| Function | Type | Why |
|---|---|---|
| `MakeCrater`, `Terrain_GetHeightAndNormal` writes, `ExplosionClass::Build`, `DamageAlloc`, `GameObject::SetCommand`, `AiMission::End`, `NetPlayer::RecordDeath` team counters, `DistributedObject::Destroy` map erasure | **A — authoritative gameplay** | damage, terrain, object lifetime, mission state, score; must happen exactly once under correct authority |
| `DistributedObject::Create` / `Destroy` / `RemoteDelete` `Net::Send` / `dpSetPlayerData`, `Ordnance_SendNew` `Net_BroadCastOrdnance`, `Net::SendSnipe/SendKill` | **B — replication** | network emission; must not be re-emitted by replicas |
| `ParticleEffect::AddParticle`, `ColorFade::SetGlare`, `ChunkEffect::CreateChunklet`, `StartGASEvent` sound/bounce, `DisplayInterface::DrawTextA` | **C — local presentation** | may run everywhere, per observed event, without creating authority |

**Rule:** `function runs on every client ≠ bug`. Bug = an **A** effect running without an authority guard, or a **B** emission duplicated, or a **C** effect that *itself* creates **A** state (e.g., particle loop gated on random that desyncs, not relevant here).

---

## Investigation 1 — Armory / Daywrecker Duplicate Detonation

### Symptom
Single Daywrecker bomb produces two detonations / double damage / double crater in multiplayer; sometimes termed “Armory bug” because the Armory-built Daywrecker is the repro path.

### Source trail — complete call graph (1.5 exact addresses)

```
Player uses Armory
  ├─ Armory (1.4: 0047xxxx; 1.5: functions/0047/ Armory::*) chooses DayWrecker
  │   └─ DayWreckerClass::Build (1.5: 0052d2xx; Redux Raw: FUN_004b0ab0 etc)
  │       └─ PowerUp::PowerUp base (GameObject::GameObject → DistributedObject ctor)
  │           └─ DistributedObject::DistributedObject @0048ed50  // object_type=0, dwLocalID=0xfa01 prefix
  │           └─ SetLocal @0048f80b  // assigns dwLocalID = global_activnet_id<<16 | dwLocalIDCounter++
  │
  ├─ Munition replicated: DistributedObject::Create path for PowerUps? No — DayWrecker is a DistributedObject,
  │   but Armory-spawned ordnance-like projectiles are NOT Ordnance subsystem; they are GameObjects.
  │   Replication is via DistributedObject permanent-state `UpdatePermState → SendBuf` broadcast (type 0x6 dwell).
  │
  ├─ In-flight:  PowerUp::Simulate @004a9a91  (1.5)
  │               DayWrecker::Simulate @0052d029 overrides it
  │
  ├─ Detonation triggers (either):
  │   ├─ Collision: DayWrecker::RegCollision @0052d12b → clears bit 0x4 (flags & ~4) unconditionally
  │   ├─ Timer/expiry: Simulate’s `flags &4 ==0` branch (deployed) vs else → PowerUp::Simulate
  │   └─ Destruction notification: DistributedObject::Destroy / RemoteDelete → virtual explode @ +0x10
  │
  ├─ Detonation / explosion:
  │   ├─ DayWrecker::Explode @0052d234  (sets flag 0x200, spawns ExplosionClass::Build(xplBuilding),
  │   │                                  particles, glare, then virtual delete @ +0x10)
  │   └─ DayWrecker::Simulate deployed branch itself also does:
  │        MakeCrater(fx,fz, radius) @0051f74c
  │        ExplosionClass::Build(thisClass->xplClass, &mat, NULL)
  │        virtual delete @ +0x10 (same slot as Explode’s tail)
  │
  └─ Teardown:  virtual delete → destructor chain → Remove_Light_Source → obj_set_flag 0x200
```

**Critical observation — missing authority guard:**

`PowerUp::Simulate` (the base) starts with:

```c
bVar25 = DistributedObject::IsRemote((DistributedObject *)piVar1);
if (!bVar25) {
  uVar3 = *(uint *)(this->_padding +0x14);
  if ((uVar3 & 0x1000000)!=0) { vcall +0x14; return; } // dead
  if ((uVar3 & 0x200)!=0) { vcall +0x10; return; }      // remove
}
// ... only if not remote does it early-return on destroyed flags
// then continues into physics / collision / ground-check
```

`DayWrecker::Simulate` **does not** do that. Its prologue is:

```c
if ((*(byte *)(*(int *)&this->field_0x220 + 0x10c) & 4) == 0) {
  obj_set_flag(...,0x200);
  *flags |=0x20;
  MakeCrater(...);                         // <--- A effect, no guard
  ExplosionClass::Build(..., &local_44, 0); // <--- A+B
  (**(code **)(*(int *)&this->field_0x20 + 0x10))(); // remove
} else {
  PowerUp::Simulate(this,param_1); // only the “flying” branch delegates to guarded base
}
```

The deployed branch (`flags &4 ==0`) is the **post-arming** state. It executes `MakeCrater` and the building-explosion build **before** any `IsRemote/IsLocal` test, and it does not delegate to `PowerUp::Simulate`’s guarded path at all.

`DayWrecker::RegCollision` also has **zero** authority checks — it only filters self-collision (`GetObj(field_0x21c) == collider`) and friendly damage routing, then unconditionally clears `flags &~4`.

`DayWrecker::Explode` likewise has no `IsRemote` guard (sets `0x200`, builds `xplBuilding`, particles, then `vcall +0x10`).

### Multiplayer authority analysis

| Stage | Owner peer | Remote replica | Guard? |
|---|---|---|---|
| Construction (`Armory → Build`) | `SetLocal` assigns `dwLocalID`; `UpdatePermState` will broadcast | `DistributedObject::Create` reconstructs via `GameObjectClass::Build` → `SetRemote` (object_type=2) | correct |
| `Simulate` while airborne (`flags &4 !=0`) | delegates to `PowerUp::Simulate` which *is* guarded (`IsRemote` → no early destroy check, but continues physics) | same | partial — see below |
| `Simulate` while deployed (`flags &4 ==0`) | `MakeCrater` + `ExplosionClass::Build` | **also** `MakeCrater` + `ExplosionClass::Build` | **NONE** — bug |
| `RegCollision` | clears deployed flag, may trigger damage | also clears deployed flag | NONE |
| `Explode` | builds explosion, virtual delete | if called via `Destroy`’s `vcall +0x10` on remote, also builds explosion | NONE (and `Destroy` itself already erased map) |

### Replication analysis

- No explicit “detonate” reliable message exists for PowerUps. Destruction is the replication: owner’s `Destroy` → `dpSetPlayerData` broadcast of `type 6` dwell with `dwLocalID`; remote’s `DistributedObject::Create`-path will *delete*? Actually PowerUp destruction is via `obj_set_flag 0x280` + `Destroy` which broadcasts a generic `PO`/`6` packet. Remote receives that and runs `RemoteDelete`/`Destroy`’s tail virtual `+0x10` (which for DayWrecker is the remove path, but the *deployed* `Simulate` branch already built an explosion).
- The remote’s `Simulate` deployed branch is **independent simulation**, not triggered by the network destroy. Even before the owner’s destroy arrives, the remote has already executed `MakeCrater`. Then when the destroy arrives, the remote’s destructor tail again calls the virtual `+0x10`, which for buildings may be a second `Explode`-equivalent. Hence up to **2× crater + 2–3× explosion** per bomb.
- No `alreadyDetonated` flag is replicated. The only flag is the local `flags &4` (armed/deployed) and `0x200` (marked for delete). Both are **local physics flags**, not reliable state.

### Classic replication failure pattern — confirmed variant

Not the textbook `OWNER: Detonate→send destroy / REMOTE: receive destroy→Detonate again` alone, but **both**:

1. **Symmetric Simulate:** `OWNER: Simulate deployed → Detonate+MakeCrater` and `REMOTE: Simulate deployed → Detonate+MakeCrater` (same timer, same collision) — owner and replica both reach detonation independently.
2. **Destroy-amplified:** Owner’s destroy notification on remote invokes the object’s destructor path which itself contains explosion logic, layering a second detonation on top of the Simulate-driven one.

### BZ1 vs Redux differences

| Aspect | 1.4 | 1.5 | Redux |
|---|---|---|---|
| `PowerUp::Simulate` guard | present (same decomp) | present @004a9a91 | preserved in Raw .C (`FUN_004b0xxx` family delegates similarly; PowerUp base still tested at +0x20 vtable) |
| `DayWrecker::Simulate` guard | same missing | same missing @0052d029 | same missing (Raw `FUN_004b0420` is constructor; real Simulate is `FUN_0052d029`-equivalent at ~0x0052xxxx / 0x004axxxx — still no IsRemote) |
| `MakeCrater` | same bitwise shift | same | same (still `TerrainEdit` early-out only) |
| Fix shipped? | No | No | No |

### Root-cause hypothesis

> **All network PowerUps execute `Simulate` on replicas, but base `PowerUp::Simulate` is owner-gated for destruction checks while `DayWrecker::Simulate`’s deployed branch bypasses that gate and directly invokes non-idempotent gameplay mutation (`MakeCrater` + `ExplosionClass::Build`) without an authority test. `RegCollision` and `Explode` also lack guards. This explains both duplicate payload and repeated terrain deformation. — Confidence: HIGH**

### Instrumentation opportunities (safe hooks, Redux GOG 2.2.301)

- `DayWrecker::Simulate` entry (resolve via RTTI `?AVDayWrecker@@` → vtable slot 15 or pattern `IsRemote` absent): log `[DW-SIM] this ptr, dwLocalID, object_type, flags &4, IsRemote, IsNetGame` on both peers.
- `MakeCrater` entry (0x0051f74c / `FUN_0051f74c`): log `[DW-CRATER] caller RA, x,z,radius, dwLocalID, peer role`.
- `DayWrecker::Explode` entry (0x0052d234): log `[DW-BOOM] this, flags, team, RA`.
- `DistributedObject::Destroy` / `RemoteDelete`: log `[DW-NET] dwLocalID, type, sender`.

If host and client both emit `[DW-SIM] flags&4==0` for the same `dwLocalID` in the same tick, and both emit `[DW-CRATER]` before any `[DW-NET]` destroy, hypothesis is proven.

---

## Investigation 2 — Daywrecker Crater / Explosion Aftermath

### Effects traced post-detonation

| Effect | Function | Idempotent? | Authority? |
|---|---|---|---|
| Crater / terrain height | `MakeCrater(x,z,r)` → `GetNormalPtr(x,z)` loop | **No** — `*ptr >>=1`, `>>=2`, `=0` is destructive; re-applying halves again | NONE |
| Terrain normals | same 9-texel loop | No | NONE |
| Tile regeneration / collision rebuild | called elsewhere after `MakeCrater` via `RemoveCoplanarFlags`-adjacent zones? Not in same function | N/A | — |
| Secondary explosion object | `ExplosionClass::Build(xplBuilding, &mat, 0)` inside `Simulate` deployed branch and `Explode` | No (spawns new GameObject) | NONE |
| Debris / shockwave | `ExplosionClass::Build` variant (same) | No | NONE |
| Particles / sound / camera shake | `ParticleEffect::AddParticle` loop, `ColorFade::SetGlare`, `StartGASEvent` bounce sound | Yes (C) | — |
| `MakeCrater` extra callers | `ProximityMine::Simulate @00536dd5` also calls `MakeCrater(...,3.0)`; `WeaponMine::Simulate` indirect | same bug family if ungated | Problematic for mine variants too |

**MakeCrater internals (1.5 @0051f74c):**

```c
if (TerrainEdit !=0) return 0;
_ftol2_sse(); _ftol2_sse(); // float→int of x,z
GetNormalPtr(...); *ptr >>=1;
*ptr >>=2; *ptr >>=1; *ptr >>=2; *ptr =0; // center
*ptr >>=2; *ptr >>=1; *ptr >>=2; *ptr >>=1;
```

Each call touches exactly 9 normal bytes in a 3×3 neighbourhood. Second call on same centre re-shifts already-shifted values: e.g., byte `0x80` → `0x40` first call, `0x20` second. Height/normal corruption is **additive destructive**, not additive constructive — the spire is the visual consequence of halving twice (or halving a zeroed centre stays zero while neighbours keep halving, producing a stepped crater that reads as a spire).

Repeated deformation is therefore **non-idempotent and unbounded downward** (until byte underflows to 0, then stays 0). Randomized `Pseudo_Rand_Number` particle spray in `Explode` is local C but seeded from `Rand_Counter`, so desync there is not the spire cause — the deterministic `MakeCrater` is.

### Authority: deterministically run on every client (`2`)

No terrain delta is replicated. No explicit network event carries crater parameters. The design is “every client deterministically re-applies `MakeCrater` locally when the Daywrecker says so.” When `DayWrecker says so` is ungated, every client mutates terrain once per replica, i.e., N times.

### Is duplicate detonation the same bug as spire? — **Yes, same root.**

One bomb → N `MakeCrater` executions (one per peer’s Simulate) → same 3×3 normals halved N times → spire/step. The extra `ExplosionClass::Build` is also N×, producing overlapping scorch/shockwave that can look like a second detonation amplifying the spire.

### Candidate fix boundary (only if proven)

Gate `DayWrecker::Simulate` deployed branch and `RegCollision` clearing on `!IsNetGame || IsLocal`:

```c
if (Net::IsNetGame() && DistributedObject::IsRemote(this)) return; // before MakeCrater
```

Do **not** gate particles/sound (C) alone — the authoritative `ExplosionClass::Build` must also be gated, but the visual explosion should still be *observed* on remotes via the network destroy → remote’s presentation path (already happens via destructor’s `Build` on the B trail). The minimal fix is the Simulate deployed-branch guard; `Explode`’s guard is secondary but recommended for destroy-amplified double.

---

## Investigation 3 — Splinter Multiplayer Payload Duplication

### Full trace — Splinter ≡ `spraybomb` / `SprayBuilding`

```
Weapon fired/deployed
  └─ SprayBomb (ordnance shell, Grenade subclass)
       ├─ Class: SprayBombClass @"spraybomb" @0053a4d9 (payload ODF = sprayClass)
       ├─ Flight: Grenade physics (PowerUp-like base, but Ordnance path? Actually SprayBomb is NOT Ordnance; it is a GameObject with _OBJ76)
       └─ On hit / low velocity:
            SprayBomb::Hit @0053abbf
              ├─ if velocity <5.0: builds SprayBuilding via GameObjectClass::Build(sprayClass, &mat) at TLFPos
              ├─ sets GAS event, obj_set_flag 0x200 (remove self)
              └─ if Net_IsNetGame && Net_GetMyPlayerID == ownerTeam: does NetUtil_ReduceMatNoRoll + matrix copy? (local-owner path, but no authority gate on the Build itself)
                 The Build itself is unconditional — any peer whose SprayBomb hits will Build a SprayBuilding locally.
       └─ Deployed building:
            SprayBuilding : Building  (distributed object, holds _padding +0x160 payloadClass)
              Simulate @0053a779:
                spin (Spinner) + altitude lerp via Terrain_FindFloor( x, z) + 2.0
                shotTimer += param_1; while (shotTimer >0 && ammo >= cost) {
                  if (go == NULL) gas? ...
                  // NO IsRemote / IsNetGame check at all
                  OrdnanceClass::Build(payloadClass, &m, ownerObj) ??? actually inside loop:
                  // decomp shows Ordnance creation via helper FUN_00586ff0 / OrdnanceClass::Build + netOrdnanceMap insert
                  // then timer -= shotDelay, ammo -= cost
                }
```

**Contrast — Popper (the fixed weapon):**

Current GOG `FUN_005a6460` (Popper Control) — verified in `mp_ordnance_duplication_popgun_comparison_20260827.md`:

```c
iVar9 = IsNetGame();
if ((iVar9==0) || (team @+0x7C == GetLocalTeam())) {
  FUN_00586ff0(...); // secondary creation
}
```

**SprayBuilding @0053a779** has no such `if`. Its loop prologue is simply `while (shotTimer>0 && ammo>=cost)` with no locality test. The only early-out is `POPCOUNT(timer)==0` (timer gate).

### Ownership of children

- Children are **Ordnance** (`Ordnance::Ordnance @00534017` with `bSend=1`, `source = 0xfa01` initially, `ordid = g_next_ordid++`).
- `SprayBuilding::Simulate` does **not** set `source` explicitly in the excerpt; `Ordnance`’s `source` is set by the Ordnance creation helper to `owner` (the SprayBuilding’s owner? Actually `Ordnance_GetOwner` reads `owner` _OBJ76). For SprayBuilding, `owner` is the building’s creator team, inherited via `GameObject::Build(team)`.
- Children are **networked objects** (`Ordnance_SendNew` broadcasts them; `Ordnance_Receive` reconstructs them on peers).
- `AddObject`/`Build` **does** send them to peers via `Ordnance_SendNew`’s `Net_BroadCastOrdnance` (`RO` packet).
- Remote replicas **can** create their own children because their `Simulate` loop is not suppressed.

### Duplication magnitude

```
1 authoritative SprayBuilding
× number_of_peers that simulated it (typically 2 in 1v1)
× N shots per burst (5 by default, spraybomb ODF omegaSpin/shotDelay)
= 2× total ordnance if bug holds
```

Each child ordnance is itself an `Ordnance` with its own `ordid`, so they are distinct objects, not duplicate IDs — the count doubles, not the identity.

### Comparison to Daywrecker

| Aspect | Daywrecker | Splinter (SprayBuilding) |
|---|---|---|
| Base class | `PowerUp` → `GameObject` → `DistributedObject` | `Building` → `GameObject` → `DistributedObject` |
| Authority guard in Simulate | **Missing** (deployed branch) | **Missing** (entire fire loop) |
| Payload type | `ExplosionClass` + `MakeCrater` (immediate) | `Ordnance` (loop, 0.05s delay) |
| Replication | `Destroy`/`PO` packet | `Ordnance RO` packet |
| Sibling pattern | same historical pattern (“simulate on every peer, create gameplay there”) | same |
| Fixed sibling | Popper (`FUN_005a6460`) has guard | **not fixed** |

### Root-cause hypothesis

> **SprayBuilding::Simulate’s shot loop unconditionally calls the ordnance creation helper; in multiplayer both host and client execute the loop, each locally creates N authoritative ordnance, and the network also replicates the host’s ordnance. Remote therefore sees 2N payloads. — HIGH confidence (static fact verified, runtime duplication requires two-PC confirmation).**

### Instrumentation

- Hook `SprayBuilding::Simulate` entry (GOG vtable slot at `0x00888228`, entry `0x005DA6E0` prologue `55 8B EC 81 EC E8 02 00 00`): log `[SPRAY-SIM] this, dwLocalID, object_type, shotTimer, ammo, IsRemote`.
- Hook `Ordnance::Ordnance` / `Ordance_SendNew` helper (`FUN_00586ff0` / `0x00586ff0` in 1.5): log `[SPRAY-ORD] caller RA (SprayBuilding?), source team, ordid, position`.
- On host and client, fire one Splinter. If both peers log `[SPRAY-ORD]` with distinct `ordid` but same creation tick/position and then each receives the other’s `RO` replica, duplication is proven.

---

## Investigation 4 — Splinter Deployed Collision Response

### State after deployment

- `SprayBomb::Hit` handles bounce vs plant. For the `fVar28 <5.0` (slow) case it **plants**: builds `SprayBuilding` at the hit position via `Build_Orthogonal_Matrix` + `GameObjectClass::Build`, copies GAS, sets `obj_set_flag 0x200` on the bomb (self-delete). For the `else` (fast) case it **bounces**: reflects velocity via `CombineVectors(... -2*dot)`, rescales, reorients, `StartGASEvent` bounce.
- The **deployed** `SprayBuilding` then has no further collision callback that matters for firing; its `Simulate` does `Terrain_FindFloor` altitude lerp, not collision response. The collision-relevant object is the pre-plant `SprayBomb` (a `Grenade`), whose physics is base `Grenade`/`PowerUp` style and does run on remotes (it inherits `IsRemote` guard for destroy, but physics still steps).
- No distinct `OnCollision` state machine for `SprayBuilding` was found; its `Simulate` is the authority.

### Authority checks at every transition

```
physics collision → SprayBomb::Hit
  └─ no IsRemote check before Build(SprayBuilding)  (see Hit excerpt: only checks velocity, then unconditionally Builds)
  → state mutation: new SprayBuilding GameObject locally created, old bomb flagged 0x200
  → network update: Building creation is DistributedObject permanent-state broadcast (will be replicated to other peer)
```

If the remote replica’s `SprayBomb` hits the same ground, it will also `Build` a `SprayBuilding` locally, creating **duplicate buildings** (one authoritative, one remote-local), each of which then enters the duplicate-fire loop of #3. This is a second amplification of the same missing guard.

### Legitimate vs illegitimate remote work

- Visual collision prediction ( lerping to floor, spin) is legitimate C.
- Changing authoritative `SprayBuilding` existence (creating the building) and then authoritative ordnance count (firing) on a remote is not.

### Feedback loop?

Bounce path recalculates velocity and re-queues GASEvent; no network correction is applied to `SprayBomb` in the fast path, so a remote bounce that desyncs velocity does not cause a correction storm — it just plants a second building slightly offset. Not a feedback loop, but a duplication.

### Fix boundary

Gate `SprayBomb::Hit`’s `Build(SprayBuilding)` on `!IsNetGame || IsLocal(owner)`, and gate `SprayBuilding::Simulate` fire loop similarly. The already shipped `SPLINTER_UNDEAD` fix (gating on `flags &0x01000200` → delegate to `Building::Simulate`) is complementary but orthogonal; it does not add the missing authority gate.

---

## Investigation 5 — Packet-loss / Traffic-storm Recovery

### Transport implementation (as far as source + runtime permit)

| Layer | Implementation | Evidence |
|---|---|---|
| Socket | Winsock `dp` (`ANET2.DLL` / DirectPlay 6), UDP P2P via `Net::Send(dp, from, to, reliable, buf, len)` (`@004ddade`) → `dpSend` or `dpEnumPlayersCallbackSend` broadcast | `Net::Send`, `Net_BroadCastOrdnance` |
| Sequencing | Ordnance packets carry `source:ushort` + `ordid:ushort` (`RO` header) then per-ordnance `RMAT(10) + source2 + ordid2 + time + extra`; global `g_next_ordid` increments; `netOrdnanceMap` keyed by `(source,ordid)` | `Ordnance_SendNew`, `Ordnance_Receive` |
| Reliability | `Net::Send(..., reliable=1)` for ordnance expire/manual-detonate (`0x6f78`/`ManualDetonate`), kills (`0x736e`?), mission? For ordnance new, the call in `Ordnance_SendNew → Net_BroadCastOrdnance` goes via `caOrdnanceBuffer` + `BOrdnanceLength` + `Net_BroadCastOrdnance`’s internal `memcpy` + length; actual `dpSend` reliable flag is 1 for control, 0/1 per-ordnance? `Ordnance_ControlAll` sends `Net::Send(dp, myId, 0, 1, &0x6f78, len)` — reliable=1 for the expire path. `Ordnance_Receive` handles out-of-order via `netOrdnanceMap` lookup but **drops** packets for unknown class (`if local_8==0 return`) without NACK. |
| Duplicate/out-of-order | `Ordnance_Receive` checks `netOrdnanceMap.find((source,ordid))`: if not found → create; else → update transform/velocity + call `vcall +0x20` to decode. **No sequence number ACK** at this layer; deduplication is by `(source,ordid)` key only. No reorder buffer. | `Ordnance_Receive` excerpt |
| Retransmission / ACK | No retransmit in Ordnance layer. At `dp` layer (DirectPlay) there is no application-level ACK for unreliable ordnance; reliable packets use DP’s own retry. Battlezone’s own logic has **no** retransmission of lost `RO` packets — lost ordnance simply never spawns on remote (benign) *unless* the ordnance is a `SprayBuilding` child that was also locally created — then loss is masked by the duplicate. |
| Queue limits / backpressure | `Net_BroadCastOrdnance` does a **bandwidth gate**, not a queue: `if ((fVar3 + (queueBytes - sentBytes))/dt <= dwBandwidth) { memcpy(caOrdnanceBuffer...) BOrdnanceLength = len }` else silently drop. `Net_CanBroadCastOrdnance` same. `Net_MaxOrdnanceSize` clamped `0x28..0xb4` based on player count `(10 - players)*0x14`. | `Net_BroadCastOrdnance @004ddbcb` |
| Keepalive / peer liveness | `Net::AdjustBandwidth` dynamically adjusts `dwBandwidth` via `UpCount`/`DownCount` based on `MaxPing` vs observed RTT; `dwMinBandwidth`/`dwMaxBandwidth` clamp | `Net::AdjustBandwidth @004ddd94` |
| Reconnect | No reconnect; `dp` session ends on host disconnect | `Net::Execute @004df43a` |

### Amplification pattern search

The hypothesized `packet lost → sender retries → receiver responds → resend loop → traffic storm` **was not found** in Ordnance. There is no retry at all — Ordnance `RO` is fire-and-forget, `BOrdnanceLength` is overwritten, not queued. The “storm” is not retransmission amplification but **duplication amplification**: each peer locally creating ordnance that the other also replicates causes a one-time 2× burst, not a self-sustaining loop.

However, OpenShim’s `net_optimizer.cpp` documents a real observed collapse that *is* a storm-like behavior in the **bandwidth governor**:

- `net_optimizer.cpp:272` — `kGovRateAddr = 0x008e8d14` and the 15-byte governor signature.
- The `0x55`xx “runaway repair-kit objects” case: four runaway objects flooded the reliable channel, ping exceeded `MaxPing`, governor walked DOWN 54 steps over 107s (25,900 → 4,150 → floor 4000), then read 4000 as “match start” and jumped 10× mid-match.
- This matches the `UpCount/DownCount` logic in `AdjustBandwidth`: each second of `ping > MaxPing` does `dwBandwidth--` (or `- DownCount`?), each second of `ping < MaxPing` does `dwBandwidth += UpCount`. No ACK storm, but a **bandwidth collapse** that sustains itself while ping stays high.

### Can transport recover after burst loss?

- Ordnance: yes, trivially — lost packets are just lost; next tick’s ordnance is independent. No recovery needed.
- DistributedObject: uses reliable `dpSetPlayerData` / `Send(..., reliable=1)` for create/destroy; DP’s own reliable channel handles retry, but if the channel is saturated by the 4-object flood, even reliable packets queue behind the governor’s throttled `dwBandwidth`, causing the observed “traffic storm” symptom (not packet-loss-triggered, but bandwidth-throttled).
- The `battlezone-netcode-patch` addresses a different, lower-level cause: the game **drops any UDP packet not in exact sequential order** even by milliseconds (rigid sequencing), so WiFi jitter causes loss that the application never retries. Their V3 fix buffers 45 ms / 8 per-peer / 96 drain budget at `WSARecvFrom` and reduces drops ~4–5/min.

### Instrumentation points

- TX/RX packets/sec: hook `Net::Send` and `Ordnance_Receive` / `dpRecv`.
- Retransmits/sec: not applicable at Ordnance; at `dp` layer, instrument `dpSend` return/retry.
- Queue depth: instrument `caOrdnanceBuffer` / `BOrdnanceLength` and `netOrdnanceMap.size()`.
- Oldest unacked: instrument `DistributedObject::delLocalIDMap` age.
- Duplicate: instrument `Ordnance_Receive`’s `find` hit-rate.
- Burst detection: OpenShim already implements `kBurstThresholdPps=100`, `kBurstReportMs=30000` in `net_optimizer.cpp`.

---

## Investigation 6 — Password-lobby Friend Invites

### Symptom
Invited player cannot join a password-protected lobby via the Steam/Galaxy friend-invite path.

### Traced paths

| Path | Steps |
|---|---|
| Normal password join | Browser → `DoJoinLobby` with `{lobbyId, password}` → server validates via `dp` session password → `Net::Execute`’s `HandleJoin` checks `packet_buffer[7] & password`? The stock password is stored as lobby metadata `pSessionDesc->password` and verified in `dp`’s `EnumSessionsCallback`. |
| Friend invite generation | Host → `Create` lobby with password → OS overlay generates invite payload via `steam_api` / `galaxy` → payload contains `lobbyId` + `connection string` (opaque, no password) |
| Invite transport | `bzrnet_server/server.py` implements `DoP2PConnect` routing and UDP probe port 1338; it routes `DoP2PConnect` by lobby, not by password — see `server.py:~line 180` and `bzrnet_protocol_capture_20260321.md`. The captured control plane shows `Authorization → DoEnterLounge → DoJoinLobby → SetPlayerData` with no password field in the `DoP2PConnect` route. |
| Invite acceptance | Recipient → `DoP2PRoute` / direct `DoP2PConnect` with lobbyId → `Net::Execute`’s `Receive` path expects password in session join; because invite carried none, `dpJoin` fails with invalid password, and no prompt is shown (invite path is “direct connect” bypassing browser prompt). |

### Where password is handled

- Entry: lobby creation dialog → stored in `Net::pcFlagName`? No — in `Net::sessionDesc` and `dp_session_t`.
- Storage: `Net::sessionDesc` (`dp_session_t_u_17` at `local_73` in `Net::Execute`) holds password hash; lobby metadata `sessionPassword` field.
- Not lobby metadata exposed to invite: the WebSocket `DoJoinLobby` message in `bzrnet_server` carries `userCount`, `userPack`, `lobbyId`, but not `password` — confirmed in `server.py`’s `DoJoinLobby` derivation.
- Validation: `dp`’s session layer validates on `dpJoin`; no second-chance prompt on invite.

### Intent vs bug

Password is **deliberately excluded** from invite payload for security (plaintext in WebSocket URL would be logged). The intended native behavior is: invite identifies lobby → recipient opens lobby → password prompt occurs → standard authenticated join. The current path skips the prompt because the invite is treated as a pre-authenticated direct route.

### Safest fix architecture

> **Do not transmit plaintext password in invite.** Instead, make the invite path converge on the normal join path:
> invite identifies lobby → client opens lobby view (browser entry) → if lobby is password-protected, show standard password dialog → on success, call the same `Net::Send` / `DoJoinLobby` with password → continue via `DoP2PConnect` probe. This preserves security and reuses the validated password-check code. The only code change is: on `DoP2PConnect` failure due to password, instead of hard-failing, raise the password UI and retry once.

---

## Investigation 7 — MPI Host-Leaving Bug

### Symptom (as reported)
When the host leaves an MPI (multiplayer Internet / “MPlayer” legacy term) session, clients hang / fail to terminate cleanly; sometimes score is lost, sometimes objects become unowned.

### Session/host/client/mission map

- `MPI session` = legacy `dp` session; host is `hosting==true`, `IsHost(playerId)` true for host’s `myPlayerID`.
- `mission authority` = host’s `AiMission *mission` (global `mission`, `current`) and `current->done` gate.
- `GameWorld` = `allDistributedObjectList`, `localDistributedObjectMap`, `remoteDistributedObjectMap`, `netOrdnanceMap`.
- Host-owned: mission simulation (`AiMission::End` only on host via `Manage_AI`’s `Net_IsNetGame()==0` check), game world (all `Building`/`Craft` that are `SetLocal` on host), score (`netPlayerByTeam[team]->kills/deaths` summed on host), network allocator (`dwLocalIDCounter`).

### Disconnect path (1.5)

- `Net::Execute` polls `dp` session; on disconnect, iterates `remoteDistributedObjectMap` and calls `DistributedObject::RemoteDelete` on each? Not in this excerpt, but `RemoteDelete` is the per-object handler for “owner left” — it flags `0x280`, erases remote map, broadcasts `PO` deletion, then `Destroy`.
- Host disconnect handling is in `Net::Execute`’s `NetState` transitions; but `AiMission::End`’s `shutdownTime/resultName/failed` is never broadcast, so clients never learn “mission ended because host left” — they just see `dpNumPlayers` drop to 1 and stall in `waiting for host` loop.
- `DistributedObject::TakeOwnershipFromPlayer @0049007a` is called on player leave to reassign `activnet_id` ownership? Its body iterates `allDistributedObjectList` and reassigns `activnet_id = newOwner` for objects whose `activnet_id == leavingPlayer`. However, `AiMission` itself is not a `DistributedObject`, so mission authority **has no transfer**.

### Is host migration ever designed?

No. `hosting` is a boolean derived from `dp` session creation (`dpCreate` vs `dpJoin`). No code does `hosting = true` on a client when host leaves. The only “migration” that exists is per-object `TakeOwnershipFromPlayer`, which is for craft/building ownership, not session mastership.

### Distinction

> **This is not a “host migration bug” in the sense of a broken migration algorithm. It is a “failure to cleanly terminate/notify clients when the host leaves because host migration is fundamentally unsupported.”** The expected behavior is: host leave → broadcast mission termination (e.g., `Send(... "host_left")` or `AiMission::End` RPC) → clients show result and return to shell. The current behavior is: host leave → `dp` session ends → clients’ `Net::Execute` sees `dpNumPlayers==0` or `hostId invalid`, but `mission->done` stays false → clients spin forever in `Simulate` with no mission end.

---

## Investigation 8 — SucceedMission / FailMission Transport Failure

### Complete path (1.5 → Redux identical)

```
Lua: SucceedMission(delay, "next.bzn") / FailMission(delay, "fail.bzn")
  └─ Lua binding SucceedMission(lua) @00418410 / FailMission(lua) @004183db
       └─ C SucceedMission(float, char*) @004015f5 / FailMission(float,char*) @004015db
            └─ AiMission::End(mission, time+delay, next, failed) @00401b11
                 └─ this->shutdownTime = param_1
                    this->done = true
                    strncpy(this->resultName, param_2, 0xd)
                    this->failed = param_3
                    return   // <--- END OF CHAIN, NO NETWORK CODE
```

- `AiMission::End` has **zero** `Net::Send`, `DistributedObject`, `Send`/`Receive`, `dp` or `bSniper` references. It is purely local state mutation.
- `Manage_AI @0040160f` (the per-frame mission manager) even *excludes* `AiMission::End` in multiplayer: `if (Net_IsNetGame()==0 && mission->done==false) FailMission(...)` — the auto-fail for “player died” is deliberately **not** run in MP, proving the authors knew mission end was local-only but never added the MP transport.
- No MP message type for success/failure exists in the stock `Net::Execute` dispatch (`0x6f78` = ordnance, `0x736e` = snipe, `0x414b` = sync ack, `kill` = `0x??`); neither `resultName` nor `shutdownTime` is serialized.
- `coop_campaign_netcode_notes_20260324.md` confirms: Reloaded wraps `SucceedMission`/`FailMission` with `wait_for_all_clients` + broadcast `SucceedMission`/`FailMission` via `Send`/`Receive` and documents that stock `Send`/`Receive` (`Send-00419760 @00419760`, `Receive-0041ca92 @0041ca92`) is the intended mission-RPC mechanism.

### Why transport fails

The call affects **local state only**. There is no host RPC, no client replay, no result payload. In MPI/MP, each client must independently re-execute the same Lua `SucceedMission` call on its own copy of the mission script. If the trigger is host-only (e.g., `IsHosting()` guard in `multmp17.lua:215`), clients never call it → `mission->done` stays false on clients → no shell transition.

### Redux change?

None. `Redux/Raw .C` `AiMission::End` is byte-identical to 1.5 (same `shutdownTime/resultName/failed` stores). No transport was added.

### Script bindings bypass

The Lua bindings (`SucceedMission.lua @00418410`) directly call the native `SucceedMission` without any `Net_IsNetGame()` / `Send` wrapper. A script **cannot** know it is bypassing a wrapper because no wrapper exists.

### Correct architecture (Reloaded-proven)

Host-authoritative: host calls `AiMission::End` locally **and** `Send("succeed", delay, nextBzn)`; clients in `Receive` handle `if msg=="succeed" then SucceedMission(delay,next)`; add `wait_for_all_clients` barrier before `SucceedMission` to avoid desync, as in `rl_coop_mission.lua:273,282` + `exu.BuildSyncObject` for mission-critical objects.

---

## Investigation 9 — Host Sniper Kills Missing from Scoreboard

### What makes sniper kills different

| Kill type | Path | Score update |
|---|---|---|
| Normal weapon / vehicle destruction | `GameObject::DamageAlloc → DistributedObject::RecordDeath(team) → NetPlayer::RecordDeath → kills++ + SendKill (if killer != self)` | both local and via `HandleKill` on remote |
| Remote sniper kill | `SendSnipe(shooter, victim) @004de74f` → DP send `0x736e sn + victimId + shooterTeam` → remote `HandleSnipe @004df3ba` → `RecordDeath` → `KillMessage` → score | remote peer scores correctly |
| Host sniper kill | **Same `SendSnipe` is called, but local `RecordDeath` is inside `HandleSnipe` only**, not on the sending path. The sender does `Send(...)` and returns; it does **not** also call `HandleSnipe` locally. If victim is **local to host** (host shoots a locally-owned building/AI), `DistributedObject::GetGameObject(victimId)` on the *host* returns a local object, but the host never runs `HandleSnipe`’s `RecordDeath` — the host’s score stays stale while remotes’ scores update via their `HandleSnipe`. | missing |

### Side-by-side (1.5)

```
Remote sniper kill (A shoots B where B is remote to A):
  A: SendSnipe(A,B) → Send(dp, A.myId, B.ownerId, reliable=1, {0x736e, victimId, shooterTeam})
  B: HandleSnipe(victimId) → GetGameObject(victimId) != null → flags|4 → RecordDeath(victimTeam, shooterTeam) → netPlayerByTeam[shooterTeam].kills++ → KillMessage
  A: (does NOT locally increment kills for this kill; A’s kill is counted when B’s HandleKill propagates? Actually RecordDeath’s SendKill path sends to killer’s owner. For sniper, HandleSnipe’s RecordDeath will SendKill to shooter’s team owner. If A is host and shooter, A is also shooterTeam owner, so A should have incremented locally via Increment_Player_Kills inside RecordDeath. But HandleSnipe is only on B.)

Host sniper kill (Host H shoots V where V is local to H):
  H: SendSnipe(H,V) → Send to V.owner (= H’s own id? victim is local, so GetPlayerID(victim)=H’s team’s playerId? But code checks if uVar1 !=0 then Send to that id — victim’s owner is H, so Send would be to self? In practice uVar1 = GetPlayerID(victim’s DistributedObject) = H’s own playerId, but then Send to self is a no-op in DP? Or victim is a building with no owner? Then SendSnipe grabs victim’s DistributedObject.GetPlayerID → returns 0xfa01 for neutral buildings → Send not executed at all (guard uVar1!=0 fails). Therefore host’s kill is NEVER broadcast and NEVER locally RecordDeath.)
```

The deeper issue: `SendSnipe`’s destination is `GetPlayerID(victim)`, i.e., **victim’s owner**, not “all peers”. For team-owned craft the victim’s owner is the victim’s player. For host-owned AI/buildings the owner is host (or neutral `0xfa01` → send suppressed). So host shooting its own AI-owned victim results in either a self-send (loopback not processed as `HandleSnipe` on self) or no send at all. Remote’s identical shot sends to victim’s owner (host) and host’s `HandleSnipe` *does* fire, so remote’s kill is counted on host via `HandleSnipe` but host’s own kill has no local `HandleSnipe` invocation.

### Before-collapse point

Identity collapses at `NetPlayer::RecordDeath(teamId victim, teamId killer)` (`@004e0cc5`) — both paths call it, but host sniper path never reaches it locally. The bug is before that: `SendSnipe` not paired with a local `HandleSnipe`/`RecordDeath`, and `SendSnipe` suppressed for neutral victims.

### Fix boundary

Make sniper kills follow the same “reliable local + replicated” pattern as normal kills: either (a) have `SendSnipe` also locally call `HandleSnipe`/`RecordDeath` before `Send`, or (b) route sniper kills through the generic `DistributedObject::RecordDeath` path that already handles both local increment and `SendKill` broadcast and is not victim-owner-addressed. The minimal OpenShim patch is: hook `Net::SendSnipe`’s return to also `RecordDeath`/`KillMessage` on the sending peer when `victim` is locally owned, or replace `SendSnipe`’s victim-addressed `Send` with a broadcast `SendKill`-like path.

---

## Investigation 10 — Multiplayer Freecam Exploit

### Camera modes (reconstructed from `View_Record`, `SniperInterface`, `CameraPath`)

| Mode | Value / Flag | When legitimate |
|---|---|---|
| Cockpit | `View_Record.MainCam` + `userObject` attached | always for alive participating player |
| Chase | `View_Record.FollowCam` | same |
| External / Orbit | `Camera_…` + `TerrainView` | death cam, spectator |
| Freecam | `Camera` free-move via `CameraPath` / direct `View_Record.MainCam.Matrix` manipulation | SP, editor, cinematic, `TerrainEdit==1`, deathcam, spectator |
| Death camera | `obj->flags & 0x1000000` dead → `Building::Simulate`’s `vcall +0x14` path | after death |
| Spectator | `IsSpectator` flag (separate from `TerrainEdit`) | MPI spectator slot |
| Cinematic | `CameraPath` active with `mission->done`? | `CameraPath` local call (see `coop_campaign_netcode_notes`) |

### Input → transition path (conceptual)

```
Input ( freecam key / debug console / editor shortcut )
  → SniperInterface::Simulate @004daa78 / CameraCmd handler (undiscovered exact func in examined corpus)
  → View_Record transition: set View_Record.MainCam.Matrix free, disable UserObject follow
  → permission check: ??? (none found that tests IsNetGame)
```

No `Net::IsNetGame()` / `Team::IsSpectator()` / `GameObject::IsAlive()` guard was found in the examined camera path. `SniperInterface::Simulate` does check `Net::bSniper` but that is for sniper view, not freecam. `TerrainEdit` and `StartEdit` are correctly gated (they disable sim), but freecam is not.

### Why a normal living network participant can enter it

The underlying camera system *is* global (it must support SP freecam, editor `Shift+F10` placement, cinematic `CameraPath`). The exploit is that the **command handler** does not distinguish SP/editor/cinematic/spectator/dead from “alive MP participant”. Therefore a living MP player can issue the same freecam command that SP/editor uses.

### Narrowest predicate

Illustrative (real names TBD via RE of camera command handler):

```c
if (Net::IsNetGame() && !GameObject::IsSpectator(userObject) && !AiMission::IsCinematic()
    && GameObject::IsAlive(userObject) && !TerrainEdit && !StartEdit) {
  reject unrestricted freecam; // allow spectator/deathcam via separate path
}
```

Actual flags to use: `Net::IsNetGame()`, `userObject->flags & 0x1000000 ==0` (alive), `Team::IsSpectator(team)` or `NetPlayer::IsPlayerAlly` inverse? plus `CameraPath` active check.

### Gameplay vs observation

Freecam as found allows **pure observation plus information leak** — it reveals enemy positions behind fog/occlusion because `GameObject_ComputeVisibility()` / `entity_frustum_culling` is still computed from the free camera, not the player’s detection radius. Whether it also allows firing while in freecam depends on whether `GameObject::SetCommand` still routes through `userObject`; initial trace suggests weapons still fire from `userObject`’s position, not camera, so freecam is observation-only but still an unfair advantage (fog bypass).

---

## Cross-Version Comparison

| System | BZ 1.4 (unpacked 00401000 baseline) | BZ 1.5 (exact PDB) | TRO 1.3 (odyssey.exe) | Redux GOG 2.2.301 best-effort | OpenShim |
|---|---|---|---|---|---|
| Daywrecker ownership check | NONE (same missing) | NONE @0052d029 | Not present (TRO has no daywrecker? Verify) | NONE (preserved) | Not yet patched |
| Daywrecker terrain authority | deterministic per-client (no delta) | same | — | same | — |
| Splinter (SprayBuilding) authority | same missing (SprayBuilding::Simulate never gated) | same @0053a779 | same? Spray bomb exists in 1.4 (strings show “spraybomb” in 1.4 analysis, so yes) | same | SPLINTER_UNDEAD fixed (dead-flag) but not authority |
| Popper authority gate | ? (needs 1.4 check) | fixed in final — `!Net\|\|team==LocalTeam` @005a6460 | not checked | fixed (present) | — |
| Ordnance RO transport | same fire-and-forget + idempotent per-(source,ordid) | same | same | same | net_optimizer adds socket buf + reorder, not Ordnance seq |
| Packet retry / queue | no retry, bandwidth-gated drop | same | same | same | net_optimizer: 512 KB snd, 4 MB rcv; reorder 45 ms |
| Mission-result transport | none (local only) | none | none | none | not yet |
| Sniper score | missing host path | same | same | same | not yet |
| Freecam guard | none | none | none | none | not yet |

> **Key delta:** The only fix that existed in one branch but disappeared from Redux is **Popper @005a6460** — it *is* present in final Redux, so it did not disappear; rather, its sibling `SprayBuilding` never received the same fix and `DayWrecker` never had one. TRO diff (`diff_14_tro`) is uninformative for ordnance; it mainly shows cloak/nation changes. `diff_14_15`’s `bsim` corpus could be used to confirm the Popper gate was added between 1.4 and 1.5, but that comparison was not completed here due to corpus size — it is listed as instrumentation opportunity #1 for the next pass.

---

## Reverse-Engineering Notes

### Provenance table (important routines)

| Binary / Build | Address / RVA | Decompiler name | Probable real class/function | Evidence | Callee / Caller context |
|---|---|---|---|---|---|
| BZ 1.5 `bzone.exe` 3,495,936 B + `bzint.pdb` | VA 0048a23e / RVA 0008a23e | `DistributedObject::IsRemote` | `DistributedObject::IsRemote` | PDB exact, 1-line body `return object_type==2` | called from `PowerUp::Simulate`, `WeaponMine::Simulate`, `ControlWeapons` |
| BZ 1.5 | VA 0048a248 | `DistributedObject::IsLocal` | `IsLocal` | PDB exact, `==1` | `NetProcess`, `Building::UnPack*` |
| BZ 1.5 | VA 0048f80b | `DistributedObject::SetLocal` | `SetLocal` | PDB exact, map insert + `UpdatePermState` + `BroadCastGrabObject` | `Building::UnPack*`, `ProximityMine::Simulate` |
| BZ 1.5 | VA 0051f74c | `MakeCrater` | `MakeCrater` | PDB exact, 9× `GetNormalPtr >>` pattern | `DayWrecker::Simulate`, `ProximityMine::Simulate`, `*Explosion*` |
| BZ 1.5 | VA 0052d029 | `DayWrecker::Simulate` | `DayWrecker::Simulate` | PDB exact, vtable slot, calls `MakeCrater` + `ExplosionClass::Build` | `Manage_AI` → `ClassSimulateAll` |
| BZ 1.5 | VA 0052d12b | `DayWrecker::RegCollision` | `RegCollision` | PDB exact, `flags &~4` unconditional | `Collision_Fill_In_Range` dispatch |
| BZ 1.5 | VA 0052d234 | `DayWrecker::Explode` | `Explode` | PDB exact, `xplBuilding` + `ParticleEffect` | `DistributedObject::Destroy` tail |
| BZ 1.5 | VA 004a9a91 | `PowerUp::Simulate` | `PowerUp::Simulate` | PDB exact, `IsRemote` guard prologue, `Spinner`+`GroundCheck` | `DayWrecker::Simulate` else-branch |
| BZ 1.5 | VA 0053a779 | `SprayBuilding::Simulate` | `SprayBuilding::Simulate` | PDB exact, `shotTimer`, `Spinner`+`Terrain_FindFloor`, loop `while shotTimer>0 { Ordnance::Build }` | `ClassSimulateAll` |
| BZ 1.5 | VA 0053abbf | `SprayBomb::Hit` | `SprayBomb::Hit` | PDB exact, `Hit` vs `CombineVectors` bounce | `Collision` dispatch |
| BZ 1.5 | VA 00533c82 | `Ordnance_SendNew` | `Ordnance_SendNew` | PDB exact, `RO` header, `sCompactCfg` loop, `Net_BroadCastOrdnance` | `ControlWeapons` @0047894d |
| BZ 1.5 | VA 00534666 | `Ordnance_Receive` | `Ordnance_Receive` | PDB exact, `netOrdnanceMap.find` | `Net::Execute` dispatch |
| BZ 1.5 | VA 00533a92 | `Ordnance_ControlAll` | `Ordnance_ControlAll` | PDB exact, `Net::Send(0x6f78)` for expire | `ControlWeapons` |
| BZ 1.5 | VA 00401b11 | `AiMission::End` | `AiMission::End` | PDB exact, 3 stores only | `SucceedMission`/`FailMission` |
| BZ 1.5 | VA 004de74f | `Net::SendSnipe` | `SendSnipe` | PDB exact, `0x736e` packet, victim `GetID` | `Weapon` snipe path |
| BZ 1.5 | VA 004df3ba | `Net::HandleSnipe` | `HandleSnipe` | PDB exact, `flags|4`, `RecordDeath` | `Net::Execute` dispatch |
| BZ 1.5 | VA 004e0cc5 | `NetPlayer::RecordDeath` | `RecordDeath` | PDB exact, `netPlayerByTeam[team]`, `SendKill` | `HandleSnipe`, `RecordDeath(DistributedObject)` |
| Redux GOG 2.2.301 | VA 005A6460 / file 0x001A6460 | `FUN_005a6460` | `Popper::Control` | GOG best-effort corpa, `IsNetGame \|\| team==LocalTeam` block directly visible | calls `FUN_00586ff0` (ordnance helper) |
| Redux GOG | VA 005DA6E0 / file 0x001DA6E0 | `FUN_005da6e0` | `SprayBuilding::Simulate` | RTTI `?AVSprayBuilding@@` → vtable 0x008881EC slot 15 → 0x005DA6E0, prologue `55 8B EC 81 EC E8 02 00 00` validated in OpenShim | calls `FUN_00586ff0` without gate |
| Redux GOG | VA 004B0420 (Raw C `FUN_004b0420`) | `DayWrecker ctor` | **Not** Simulate/Explode — ctor with vtable install | decomp shows `*this=DayWrecker::vftable; param[6]=vftable;` | — |
| Redux GOG | `0x00888228` | vtable slot | `SprayBuilding::Simulate` slot | `008881EC + 15*4`, verified in `splinter_spraybuilding_undead_bug_notes_20260319.md` | OpenShim already hooks for SPLINTER_UNDEAD |
| OpenShim | `0x008e8d14` | `kGovRateAddr` | `dwBandwidth` | 15-byte governor sig `68 A0 0F 00 00 68 E8 03 00 00 68 48 F4 FF FF` | `net_optimizer.cpp` |

**Matching signals used:** PDB exact name + RVA for 1.5; for Redux, RTTI `?AV*` TypeDescriptor → COL → vtable → slot offset, plus `Build_Orthogonal_Matrix`/`Spinner`/`GetNormalPtr` string-neighbour and control-flow shape, plus `ExpectedBytesMatchAt` byte validation in OpenShim (`bzr_hooks.cpp` SPLINTER_UNDEAD).

---

## Search of Existing Work (what already exists locally / in accessible repos)

- **OpenShim `mp_ordnance_duplication_popgun_comparison_20260827.md`** — already identified Popper gate, Splinter unconditional `FUN_00586ff0`, and retracted the DayWrecker `FUN_004b0420`-as-Explode misidentification. This report builds on that, correcting the DayWrecker trail via the actual `0052d029/0052d234` path.
- **OpenShim `splinter_spraybuilding_undead_bug_notes_20260319.md`** — proves `SprayBuilding::Simulate` never checks `flags & 0x1000000 / 0x200` before fire loop; OpenShim already ships a vtable-slot detour at `0x00888228` that delegates to `Building::Simulate` when `flags & 0x01000200`. That fix is complementary to the *authority* gate needed for duplication — both are required.
- **OpenShim `constructor_remote_build_bug_notes_20260319.md`** — example of correct `IsRemote` + `ConstructionEnd` cleanup pattern for AI constructors; shows the project’s established pattern for authority fixes.
- **`battlezone-netcode-patch`** — already ships a 45 ms out-of-order reorder + 512 KB/4 MB socket buffers that mitigate the rigid-sequencing drop; OpenShim `net_optimizer.cpp` already imports similar buffers + burst detection but not the full reorder (see `enablePacketReorder`).
- **`coop_campaign_netcode_notes_20260324.md`** — documents that stock `Send`/`Receive` is the *only* mission-RPC, that `SetLocal` is dangerous for remote AI, and that Reloaded’s `rl_coop_mission.lua:273,282` + `exu.BuildSyncObject` is the proven co-op mission framework. This directly supports bug #8’s fix architecture.
- **No prior fix found** for Daywrecker terrain, Daywrecker duplicate, host sniper score, password invite, host-leaving, freecam, or `SucceedMission` transport in the searched corpora (grep for `DayWrecker`, `IsNetOwner`, `GetNetOwner`, `terrain deform`, `spraybomb`, `IsRemote` around ordnance, `SucceedMission` transport, `sniper` `RecordDeath`, `freecam` all returned only the expected sites above).

---

## Shared Root Causes — Defect Families

### Family A: Missing network-authority guards (largest family)

> **Pattern:** `Simulate`/`Hit`/`RegCollision` runs on every peer, but gameplay creation (`MakeCrater`, `ExplosionClass::Build`, `Ordnance::Build`) is not gated on `!IsNetGame || IsLocal`.

- Daywrecker duplicate detonation ✓
- Daywrecker terrain spire ✓ (same gate, same function)
- Splinter payload duplication ✓
- Splinter deployed collision / `SprayBomb::Hit` building creation ✓
- Likely siblings to audit: `ProximityMine::Simulate @00536dd5` (calls `MakeCrater` after proximity check), `FlareMine::Simulate @0052fa9a`, `MagnetMine::Simulate @00531805`, `WeaponMine::Simulate @0053f9cf` (already has `IsRemote` guard — proves the fix pattern exists; audit for missing siblings).

**Learning:** Search all `::Simulate`/`::Hit` that call `MakeCrater`, `ExplosionClass::Build`, or `Ordnance*::Build` and lack a prologue `IsRemote`/`IsLocal`/`team==LocalTeam` gate. The cost is one `if` per frame, the fix is caller-side suppression (not `SetLocal`).

### Family B: Local-host fast-path bypass

> **Pattern:** Host-optimized local path skips the network broadcast that the remote path relies on for side-effects like score or mission state.

- Host sniper score (host sends `Snipe` to victim but never locally `RecordDeath`) ✓
- `SucceedMission`/`FailMission` transport (host mutates `mission->done` locally, no `Send`) ✓
- Host-leaving (host mutates `mission`/`maps` locally, no `BroadcastHostLeft`) ✓

**Learning:** Host must **both** mutate locally *and* broadcast, or *only* broadcast and let the broadcast handler (including the host’s own receive path) mutate. Current code does neither for mission, and does broadcast without local mutate for sniper.

### Family C: Incomplete connection metadata

- Password invite (lobby ID without password) ✓ — no sibling found yet, but any future invite-like path (e.g., `DoP2PRoute` relay) will have same issue.

### Family D: Transport recovery / state-machine failure

- Packet-loss “storm” is not a single bug but the governor’s `UpCount`/`DownCount` walk to floor + rigid `RO` sequencing. Family is narrow (1 bug), not shared.

---

## Per-Bug Missing Evidence (what still must be observed)

| Bug | Must still observe |
|---|---|
| Daywrecker | Two-PC log showing same `dwLocalID` Daywrecker’s `[DW-SIM]` deployed branch on both peers in same tick, before any destroy packet, plus crater byte values before/after on each peer to prove double-shift. |
| Terrain spire | Same as above plus `Normals` hex dump of the 3×3 at `GetNormalPtr` before/after first vs second peer’s `MakeCrater` to show `0x80→0x40→0x20` vs expected `0x80→0x40`. |
| Splinter | Two-PC `[SPRAY-SIM]` + `[SPRAY-ORD]` on both peers for same logical spray event, plus `netOrdnanceMap.size()` on each peer proving `2N` vs `N` children. |
| Splinter collision | Two-PC `[SprayBomb::Hit]` both peers building `SprayBuilding` at same TLFPos before spray loop, proving double-building. |
| Packet storm | Live 30-min MP capture with `bz_buffer_log.bin` + `bzrnet_trace` showing `BOrdnanceLength` drops vs `dwBandwidth` floor events and `HandleSnipe` vs `RecordDeath` counts; requires WiFi/high-jitter link or artificial 5% loss. |
| Password invite | Live WebSocket trace of `DoJoinLobby` via invite vs via browser, showing absent `password` field and the resulting `dpJoin` error code; then capture of the corrected “prompt then retry” path. |
| Host-leaving | Live MPI host-kill trace: `dpNumPlayers` drop, `mission->done` on both peers, and `allDistributedObjectList` counts 30 s after host exit. |
| SucceedMission | Live `Send`/`Receive` trace for `multmp17.lua` vs `misn02b.lua` showing that `SucceedMission` is never wrapped; then verify Reloaded `Send("succeed")` path copies `resultName` correctly. |
| Sniper | Live two-peer `SendSnipe`/`HandleSnipe`/`RecordDeath` trace for host vs remote shooter, with `netPlayerByTeam[killer].kills` before/after on both peers. |
| Freecam | Live input trace: freecam key while `Net::IsNetGame()==true && userObject alive && !spectator` should be rejected; verify `View_Record.MainCam` does not detach. |

---

## Instrumentation Opportunities — Specific Safe Hooks

| Hook | Address (1.5 VA) / Redux VA | Log |
|---|---|---|
| `DayWrecker::Simulate` entry | 1.5 0052d029 / Redux ~0052xxxx (resolve via `?AVDayWrecker@@` RTTI → vtable + `IsRemote` absence) | `[DW-SIM] dwLocalID=%08x team=%d type=%d flags=%08x IsRemote=%d` |
| `DayWrecker::Explode` entry | 1.5 0052d234 | `[DW-BOOM] dwLocalID=%08x RA=%p` |
| `MakeCrater` entry | 1.5 0051f74c | `[DW-CRATER] x=%.1f z=%.1f r=%.1f RA=%p` |
| `SprayBuilding::Simulate` entry | 1.5 0053a779 / Redux 005DA6E0 (vtable slot 0x00888228) | `[SPRAY-SIM] this=%p dwLocalID=%08x shotTimer=%f IsRemote=%d` |
| `SprayBomb::Hit` entry | 1.5 0053abbf | `[SPRAY-HIT] bomb=%p v=%.1f RA=%p` |
| `Ordnance_SendNew` loop iter | 1.5 00533c82 inside `BOrdnanceLength` branch | `[ORD-SEND] ordid=%d sourceTeam=%d class=%s` |
| `Ordnance_Receive` entry | 1.5 00534666 | `[ORD-RECV] from=%d source=%d ordid=%d classKnown=%d` |
| `AiMission::End` entry | 1.5 00401b11 | `[MISSION-END] time=%f next=%s failed=%d RA=%p IsNet=%d` |
| `Net::SendSnipe` entry/exit | 1.5 004de74f | `[SNIPE-SEND] shooterTeam=%d victimId=%08x toPlayer=%d` |
| `Net::HandleSnipe` entry | 1.5 004df3ba | `[SNIPE-HANDLE] victimId=%08x shooterTeam=%d victimTeam=%d killsBefore=%d` |
| `NetPlayer::RecordDeath` | 1.5 004e0cc5 | `[SCORE] victimTeam=%d killerTeam=%d killerKills=%d victimDeaths=%d` |
| Freecam command handler | Redux ??? (find via `CameraPath` xref / `View_Record` write) | `[FREECAM] requested mode=%d IsNet=%d isAlive=%d isSpectator=%d allowed=%d` |

All hooks are vtable-slot or entry detours with `ExpectedBytesMatchAt` + SEH guard; budget via `OPENSHIM_TRACE_*` env, disable via `OPENSHIM_DISABLE_*`.

---

## Candidate Fix Boundaries (only where HIGH/CONFIRMED)

### Daywrecker (HIGH)
- Gate `DayWrecker::Simulate` deployed branch (`flags &4==0`) on `if (Net::IsNetGame() && DistributedObject::IsRemote(this)) return;` **before** `MakeCrater`. Optionally also gate `RegCollision`’s `&~4` clear and `Explode` on same predicate. Keep C-effects (particles/glare) local-observable via the destroy path’s presentation.

### Splinter (HIGH static)
- Gate `SprayBuilding::Simulate` fire loop and `SprayBomb::Hit`’s `Build(SprayBuilding)` on `!Net::IsNetGame() || DistributedObject::IsLocal(this)` (or `team==LocalTeam` per Popper precedent; choice requires two-PC verification of which team field the SprayBuilding holds). Do **not** use generic `SetLocal` — caller-side suppression only.

### SucceedMission / FailMission (CONFIRMED)
- Wrap `AiMission::End` (or Lua `SucceedMission`/`FailMission`) to `if (Net::IsNetGame()) { if (IsHosting()) Send("mission_end", failed, resultName, shutdownTime); return; }` and add `Receive` handler that re-invokes `AiMission::End` on clients. Preserve SP path unchanged. This is the Reloaded `rl_coop_mission.lua:273,282` pattern.

### Host sniper (MEDIUM-HIGH)
- Make `Net::SendSnipe` also locally `HandleSnipe`/`RecordDeath` when victim is locally owned or `uVar1==0xfa01` (neutral). One-line: after `Send(...)` in `SendSnipe`, if `Net::IsNetGame()` and victim locally present, call `HandleSnipe(myId, &packet)`.

### Others
- Splinter collision, terrain spire: covered by Daywrecker/Splinter gates.
- Packet storm: already in `net_optimizer.cpp`; consider enabling `enablePacketReorder=true` by default and porting the `45 ms`/`8`/`96` profile from `battlezone-netcode-patch` V3.
- Password invite, host-leaving, freecam: **no narrow fix proposed until instrumentation confirms**; the architectures above are safe directions but not yet proven narrow.

---

## Final Synthesis — Ranking

### Confidence that root cause is identified

1. **SucceedMission/FailMission — CONFIRMED** (trivial: no send).
2. **Daywrecker duplicate + terrain — HIGH** (authority guard missing proven by decomp).
3. **Splinter payload duplication — HIGH static / MEDIUM runtime** (unconditional `FUN_00586ff0` call proven).
4. **Splinter collision — MEDIUM-HIGH** (same missing guard, but double-building not yet two-PC traced).
5. **Host sniper — MEDIUM-HIGH** (SendSnipe victim-addressed send + no local HandleSnipe explains symptom, but kill-path for neutral buildings needs one more trace).
6. **Packet storm — MEDIUM** (governor walk + rigid sequencing both proven, but storm vs 2× burst attribution needs live capture).
7. **Password invite — MEDIUM** (invite omits password proven via `bzrnet_server`, but exact `dpJoin` error code needs live invite trace).
8. **Host-leaving MPI — MEDIUM** (no migration proven, but graceful termination vs hang needs live host-kill trace).
9. **Freecam — MEDIUM existence / LOW predicate** (no guard found, but exact handler not yet pinned).

### Ease of proving live

Easy: SucceedMission (one `Send` log), Daywrecker/Splinter (one two-PC session with the hooks above), Sniper (one host vs remote kill).  
Hard: Packet storm (requires 30-min high-jitter session), Host-leaving (requires real host kill), Freecam (requires input-injection while alive).

### Feasibility of narrow OpenShim fix

1. Daywrecker gate — trivial vtable/entry detour, one `IsRemote` check.
2. Splinter gate — same, plus `SprayBomb::Hit` gate.
3. SucceedMission wrapper — Lua `Send`/`Receive` shim, no native detour risk.
4. Sniper — `SendSnipe` post-call hook, one `RecordDeath`.
5. Packet reorder — already exists, just enable/tune.
6. Others — medium (password prompt) or high-risk (`SetLocal` / host migration).

### Regression risk

- Missing-authority gates: **low** if caller-side suppression only (remote visual still via network destroy/ordnance receive). Risk rises if `SetLocal` is used or if gate predicate is wrong team field — verify with AI-owned SprayBuildings.
- Sniper/mission: **low**.
- Packet reorder: **medium** (timing-sensitive, but already validated in `battlezone-netcode-patch`).
- Host-leaving migration: **high** — do not attempt; ship graceful termination instead.

### Suggested implementation order

1. **SucceedMission / FailMission** — wrapper + `Receive` handler. One-line symptom, one-line proof, zero gameplay risk. Enables co-op campaign immediately.
2. **DayWrecker gate** — one-predicate fix, fixes two bugs (duplicate + spire) at once. Add the two-PC instrumentation first, then the `IsRemote` early-return in the deployed branch. Verify `MakeCrater` fires once.
3. **Splinter gate** — same pattern, second weapon. Reuse the Daywrecker harness. Keep the existing `SPLINTER_UNDEAD` dead-flag fix active alongside it.
4. **Host sniper** — `SendSnipe` post-hook. Verify scoreboard on host vs remote in one 1.5/classic-Retro MP session with `RecordDeath` logging.
5. **Packet reorder enable** — flip `enablePacketReorder` + `adaptivePacketReorder` defaults in `net_optimizer.cpp` to the `battlezone-netcode-patch` V3 profile (45 ms, 8, 96, 32) and add the `kBurstThresholdPps` reporting to `BZLogger`.
6. **Password invite prompt** — patch the invite-accept path to fall through to the browser password dialog instead of direct `DoP2PConnect`.
7. **Freecam guard** — pin the camera command handler, add the `IsNetGame && alive && !spectator` predicate, preserve death/spectator/cinematic/editor legitimate paths.
8. **Host-leaving graceful termination** — broadcast `host_left` via `Send` on disconnect and have clients `AiMission::End` + shell transition; do **not** implement migration.

### Incidental new defects found

- **`ProximityMine::Simulate @00536dd5` calls `MakeCrater(...,3.0)`** after proximity trigger without an `IsRemote` guard (it only checks `flags &0x200`). This is the same Family-A pattern as Daywrecker; audit for duplicate craters with mines in MP.
- **`WeaponMine` siblings differ:** `WeaponMine::Simulate @0053f9cf` **does** have `IsRemote` guard, proving the fix pattern was known to the original authors but not applied uniformly. `FlareMine/MagnetMine` should be audited similarly.
- **`SprayBomb::Hit` bounce vs plant** has no `IsNetGame` gate on the `Build(SprayBuilding)` path — the bounce-vs-plant velocity threshold (`<5.0`) is evaluated locally and can diverge per peer, planting at slightly different positions per peer even before the duplication.

---

## Appendix — Sequence Diagrams (actual function names)

### DayWrecker — current (buggy)

```
OWNER (IsLocal)                    REMOTE (IsRemote)
─────────────                      ──────────────────
DayWrecker::Simulate
  flags &4==0  ──► MakeCrater      DayWrecker::Simulate
  ExplosionClass::Build              flags &4==0 ──► MakeCrater   ← duplicate crater
  vcall +0x10 (remove)               ExplosionClass::Build         ← duplicate blast
       │                                  │
       │   Destroy(dpSetPlayerData 6)     │
       └─────► network dwell ────────────► RemoteDelete/Destroy
                                          │ vcall +0x10 (remove)
                                          │ (may Explode again)    ← third blast
```

### DayWrecker — with fix (proposed)

```
OWNER                              REMOTE
─────                              ──────
DayWrecker::Simulate                DayWrecker::Simulate
  IsRemote? no ─► MakeCrater          IsRemote? yes ─► return  // no crater
  ExplosionClass::Build                                    // no blast
  vcall +0x10                                                 // no remove locally? remote stays until network
       │                                  │
       └────► Destroy ───────────────────► RemoteDelete
                                          vcall +0x10  // presentation: remote now removes + shows explosion via destroy path only
                                          (single crater/blast total)
```

### Splinter — current (buggy)

```
OWNER                              REMOTE
─────                              ──────
SprayBomb::Hit                     SprayBomb::Hit  (same ground)
  Build(SprayBuilding)               Build(SprayBuilding)  ← duplicate building
  flag 0x200                         flag 0x200
SprayBuilding::Simulate            SprayBuilding::Simulate
  while timer>0 {                  while timer>0 {
    Ordnance::Build(payload)           Ordnance::Build(payload) ← duplicate ordnance set A
    bSend=1                          bSend=1
  }                                }
Ordnance_SendNew                   Ordnance_SendNew
  RO broadcast A ──────────────────► Ordnance_Receive A (creates replica A’)
                                 ┌─ RO broadcast B ──────────────────► Ordnance_Receive B (replica B’)
                                 │  (remote also broadcast its locally-created B)
Result: OWNER sees {A}             REMOTE sees {A’, B}  (2×)   — and symmetrically OWNER also gets B’
```

### Splinter — with fix

```
OWNER                              REMOTE
─────                              ──────
SprayBomb::Hit                     SprayBomb::Hit
  IsLocal? yes ► Build               IsLocal? no ► skip Build  // only owner plants
SprayBuilding::Simulate            SprayBuilding::Simulate
  IsLocal? yes ► fire loop           IsLocal? no ► skip fire loop // only owner fires
  Ordnance_SendNew ───────────────► Ordnance_Receive (single set)
```

### Ordnance — transport (no authority bug, just sequencing)

```
Shooter                            Peer
───────                            ────
Ordnance::Ordnance(bSend=1)        │
Ordnance_SendNew                   │
  Net_BroadCastOrdnance(RO) ─────► Ordnance_Receive
  if peer’s netOrdnanceMap        │   find((source,ordid))
    not found → Build             │   found → update transform/vel
  BOrdnanceLength=0               │   (no retry, no reorder — rigid)
  (loss = silent no-create)       │
```

---

## References

- `BZ1_Source/1.5/all_decompiled.c` (PDB-exact, 15045 fns) — all `005xxxx` addresses above are from this corpus unless marked Redux.
- `BZ1_Source/1.4/unpacked/bzone14_unpacked.exe` — Shrinker/LZO baseline for historical diff.
- `BZ1_Source/Redux/Raw .C/*.c` — 31,948 Ghidra functions for Redux best-effort; `FUN_004b0420` misidentification corrected herein.
- `BZR-OpenShim/reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/all_decompiled.c` — stable copy of the 1.5 corpus used for line references.
- `BZR-OpenShim/reverse_engineering/mp_ordnance_duplication_popgun_comparison_20260827.md` — Popper gate, Splinter unconditional call, DayWrecker misidentification retraction.
- `BZR-OpenShim/reverse_engineering/splinter_spraybuilding_undead_bug_notes_20260319.md` — SPLINTER_UNDEAD vtable-slot fix at `0x00888228` → `0x005DA6E0`.
- `BZR-OpenShim/reverse_engineering/coop_campaign_netcode_notes_20260324.md` — mission RPC via `Send`/`Receive`, `SetLocal` danger, Reloaded `rl_coop_mission.lua`.
- `BZR-OpenShim/reverse_engineering/bzrnet_protocol_capture_20260321.md` + `bzrnet_server/server.py` — `DoP2PConnect`/`DoJoinLobby` without password.
- `BZR-OpenShim/src/patches/net_optimizer.cpp` — `0x008e8d14` governor, burst detection `kBurstThresholdPps=100`, socket buffers.
- `battlezone-netcode-patch/resources/INVESTIGATION_WRITEUP.md` — rigid sequential discard, 45 ms reorder V3.
- `BZR-OpenShim/src/patches/bzr_hooks.cpp` — SPLINTER_UNDEAD + constructor remote-build fixes (reference patterns).

---

*End of report — all hypotheses above are graded; do not ship a Daywrecker/Splinter gate without the two-PC creation/send/receive/object-count trace, and do not generalize `team==LocalTeam` to every class without verifying which team field that class holds.*
