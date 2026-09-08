# Multiplayer Authority: Splinter Static Analysis

**Date:** 2026-09-04  
**Scope:** `SprayBomb`, `SprayBuilding`, its payload ordnance, and the existing `SPLINTER_UNDEAD` hook.  
**Evidence base:** exact-match BZ 1.5 PDB decompilation in the sibling `GrizzlyOne95/BZ1_Source` checkout, the retained Redux GOG 2.2.301 decompile, and the current GOG Ghidra project.  
**Production behavior changed:** none.

## Decision

**Do not add a multiplayer authority gate to `SprayBomb::Hit` or the `SprayBuilding::Simulate` payload loop.** The exact source disproves the proposed owner-build/send/remote-receive model:

```text
OWNER PEER                                      RECEIVER PEER
-----------                                     -------------
Build networked SprayBomb ordnance              Ordnance_Receive builds SprayBomb
  source = local player id                        source = sender player id
  ordid = next local id                           ordid = transmitted id
  bSend = 1                                       bSend = 0
        |                                                |
        +------ Ordnance_SendNew (SprayBomb only) ------+
        |                                                |
SprayBomb::Hit                                  SprayBomb::Hit
  GameObjectClass::Build(SprayBuilding)           GameObjectClass::Build(SprayBuilding)
  no SetLocal / no network create                 no SetRemote / no network receive
  object_type = 0                                 object_type = 0
        |                                                |
SprayBuilding::Simulate                         SprayBuilding::Simulate
  payload Build = N                               payload Build = N
  payload bSend forced to 0                       payload bSend forced to 0
  Ordnance_SendNew(payload) = 0                   Ordnance_SendNew(payload) = 0
  Ordnance_Receive(payload) = 0                   Ordnance_Receive(payload) = 0
```

The deployed `SprayBuilding` and its payload are intentionally reconstructed per peer from the replicated parent `SprayBomb`. They are not a replicated `SprayBuilding` followed by replicated payload ordnance. The current `Docs/MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md` claims that the payload is broadcast and that a remote `SprayBuilding` creates a second stream in addition to received payload. Those claims are contradicted by direct source and must not be used at the synthesis gate.

### Confidence terms

- **CONFIRMED:** directly visible in exact 1.5 source and independently preserved in current Redux where cited.
- **HIGH:** direct exact-source result whose current-Redux preservation is strongly corroborated but not fully symbolized end to end.
- **MEDIUM:** plausible interpretation with at least one unresolved semantic edge.
- **LOW:** weak inference.
- **UNKNOWN:** evidence is insufficient.

## Proven invariants

| Invariant | Grade | Evidence |
| --- | --- | --- |
| `SprayBomb` is an `Ordnance`, not a `DistributedObject` game object. | CONFIRMED | `SprayBombClass::Build @ 0x0053AB77` returns `Ordnance *`; its constructor calls `Grenade`, which is in the ordnance hierarchy. |
| The initial `SprayBomb` is replicated by the ordnance `RO` stream. | CONFIRMED (1.5), HIGH (Redux) | `Ordnance::Init @ 0x00534AAC`, `Ordnance_SendNew @ 0x00533C82`, and `Ordnance_Receive @ 0x00534666`. |
| `SprayBomb::Hit` builds `SprayBuilding` independently on each peer after the locally simulated bomb settles on terrain. | HIGH | `SprayBomb::Hit @ 0x0053ABBF` calls `GameObjectClass::Build` without `SetLocal`; the received parent ordnance is also present in `ordnanceList` and simulated by `Ordnance_ControlAll`. Two-PC observation remains appropriate for final Redux timing. |
| A directly built `SprayBuilding` is unowned (`object_type == 0`), not local (`1`) or remote (`2`). | CONFIRMED (1.5), HIGH (Redux) | `GameObjectClass::Build @ 0x00498D9C` does not call `SetLocal`; `GameObject` constructs its `DistributedObject` base, whose ctor sets `object_type = 0`. Only `DistributedObject::Create` follows `Build` with `SetRemote`, and that path is not used here. |
| Each payload ordnance is explicitly excluded from `Ordnance_SendNew`. | CONFIRMED | Exact `SprayBuilding::Simulate @ 0x0053A779` calls `OrdnanceClass::Build` and immediately assigns `pOVar10->bSend = 0`. Current Redux `SprayBuilding::Simulate @ 0x005DA6E0` performs the same store, `*(payload + 0x80) = 0`. `Ordnance_SendNew` serializes only entries whose `bSend != 0`. |
| A remote peer does not receive the payload ordnance through `Ordnance_Receive`. | HIGH | No payload is serialized after the explicit `bSend = 0`; `Ordnance_Receive` is used for the parent `SprayBomb`, not its locally generated children. |
| `source` is a network player id, not a team number. | CONFIRMED | `Ordnance::Init` writes `Net_GetMyPlayerID()` to `source`; `Ordnance_Receive` overwrites it with sender id (`param_3`). The Popper control compares `source` against `Net_GetMyPlayerID`, not `LocalTeam`. Team attribution is carried separately in damage bits 6-9. |
| Damage-origin flags are deliberately propagated across the deterministic reconstruction. | CONFIRMED | `Ordnance::Init` sets damage bit 4 from owner flags and bit 5 from owner `DistributedObject::IsRemote`; `SprayBomb::Hit` copies them to `SprayBuilding::dmg_player/dmg_remote`; `SprayBuilding::Simulate` copies them to every payload. |
| Remote `Craft` and `Building` replicas do not apply health damage. | CONFIRMED | `Craft::DamageAlloc @ 0x004877BF` and `Building::DamageAlloc @ 0x00482E4A` perform the health mutation only when `!DistributedObject::IsRemote(target)`. This is strong evidence that local deterministic ordnance is needed on each peer for that peer's authoritative targets. |

## Required function and event-boundary reports

### 1. `OrdnanceClass::Build` / `Ordnance::Init` — initial `SprayBomb`

**Function:** `OrdnanceClass::Build @ 0x00534DF9`; `Ordnance::Init @ 0x00534AAC`  
**Subsystem:** Parent projectile construction / ordnance network lifecycle  
**Owner peer executes?:** Yes; the firing peer builds the initial `SprayBomb`.  
**Remote peer executes?:** Yes, but through `Ordnance_Receive`, which calls the same `Build`/`Init` machinery before rewriting network identity.  
**How remote object is created:** `Ordnance_Receive` decodes the `RO` record, resolves the owner object by transmitted `dwLocalID`, and calls `OrdnanceClass::Build`.  
**Network-created side effects:** `Init` inserts a provisional `(source, ordid)` into `netOrdnanceMap`; receive removes that provisional key, decrements `g_next_ordid`, installs `(sender, wire ordid)`, and forces `bSend = 0`.  
**Damage side effects:** None at construction. Damage source, team, player-origin, and remote-origin metadata are initialized.  
**Terrain side effects:** None.  
**Presentation side effects:** Optional shot GAS starts in `Ordnance::Init`.  
**Lifecycle/state-transition side effects:** Adds the projectile to `ordnanceList` and the spatial tree; initializes lifetime and `dt`.  
**Existing authority predicate:** `Net_IsNetGame()` controls source/ordid/map enrollment. The initial sender defaults to `bSend = 1`; receive later sets `bSend = 0`.  
**Relevant object_type behavior:** Not applicable. `Ordnance` has its own lifecycle and is not a `DistributedObject`.  
**dwLocalID / activnet_id relevance:** The packet carries the owner's `DistributedObject::dwLocalID` so the receiver can resolve `Ordnance::owner`. Ordnance identity itself is `(source, ordid)`, with `source = activnet player id`.  
**Sibling precedent:** All ordinary networked ordnance uses the same `bSend` and `(source, ordid)` protocol.  
**Classification:** OWNER_ONLY for the original build/send; REMOTE_ONLY for receive reconstruction.  
**Confidence:** CONFIRMED for 1.5; HIGH that Redux retains this protocol.  
**Evidence:** `00534df9_OrdnanceClass_Build.c`, `00534aac_Ordnance_Init.c`, `00534666_Ordnance_Receive.c`.  
**Candidate patch boundary:** None.  
**Risks:** Treating this as a `DistributedObject` path selects the wrong ownership predicate and wrong identity fields.  
**DO_NOT_PATCH_IF:** The proposed change assumes `object_type`, `IsLocal`, or `IsRemote` exists on the parent ordnance.

### 2. `Ordnance_SendNew` — parent `SprayBomb` send

**Function:** `Ordnance_SendNew @ 0x00533C82`  
**Subsystem:** Ordnance network lifecycle  
**Owner peer executes?:** Yes.  
**Remote peer executes?:** The function runs globally on every peer, but it skips received ordnance because receive forces their `bSend` to zero.  
**How remote object is created:** The emitted `RO` record is decoded by `Ordnance_Receive`.  
**Network-created side effects:** Serializes only `ordnanceList` entries with `bSend != 0`, including class id, reduced matrix, `ordid`, owner `dwLocalID`, initial time, and class-specific bytes; then calls `Net_BroadCastOrdnance`.  
**Damage side effects:** None.  
**Terrain side effects:** None.  
**Presentation side effects:** None.  
**Lifecycle/state-transition side effects:** Advances a serialized object's `bSend` to `2`; does not construct or destroy it.  
**Existing authority predicate:** `bSend != 0`.  
**Relevant object_type behavior:** Owner lookup may read a `DistributedObject::dwLocalID`, but ordnance itself has no `object_type`.  
**dwLocalID / activnet_id relevance:** Owner `dwLocalID` is transmitted; `source` is supplied by the network sender context rather than encoded as team.  
**Sibling precedent:** This is the common send path for the initial `SprayBomb` and other ordinary ordnance.  
**Classification:** OWNER_ONLY.  
**Confidence:** CONFIRMED.  
**Evidence:** The only record-building branch in `00533c82_Ordnance_SendNew.c` is guarded by `(*ppOVar4)->bSend != 0`.  
**Candidate patch boundary:** None.  
**Risks:** Conflating the creation helper with `Ordnance_SendNew` hides the explicit `bSend` exclusion used by Splinter payloads.  
**DO_NOT_PATCH_IF:** The child has already been assigned `bSend = 0`.

### 3. `Ordnance_Receive` — remote parent reconstruction

**Function:** `Ordnance_Receive @ 0x00534666`  
**Subsystem:** Ordnance network lifecycle  
**Owner peer executes?:** Not for its own broadcast record.  
**Remote peer executes?:** Yes.  
**How remote object is created:** Looks up `(param_3 sender, wire ordid)` in `netOrdnanceMap`; if absent, calls `OrdnanceClass::Build`, replaces provisional local identity with sender identity, and inserts the result under the transmitted key.  
**Network-created side effects:** Creates or updates one remote representation and back-simulates it to account for packet age.  
**Damage side effects:** No direct damage; owner resolution affects damage-origin metadata used later.  
**Terrain side effects:** None.  
**Presentation side effects:** Construction may start ordnance sound; back-simulation may advance visible state.  
**Lifecycle/state-transition side effects:** Adds a new remote ordnance or updates an existing one, then forces `bSend = 0`.  
**Existing authority predicate:** Deduplication by `(source, ordid)` in `netOrdnanceMap`.  
**Relevant object_type behavior:** Not applicable to the ordnance. Its resolved owner game object may be `IsRemote` on this peer.  
**dwLocalID / activnet_id relevance:** Owner `dwLocalID` resolves the local owner representation; `param_3` becomes ordnance `source`.  
**Sibling precedent:** Standard remote reconstruction for all `RO` ordnance records.  
**Classification:** REMOTE_ONLY.  
**Confidence:** CONFIRMED.  
**Evidence:** `00534666_Ordnance_Receive.c`.  
**Candidate patch boundary:** None.  
**Risks:** Counting the provisional local identity created inside `Build` as a second lasting projectile is incorrect; receive erases that map key and reuses the same object.  
**DO_NOT_PATCH_IF:** The apparent duplicate is only the provisional-key rewrite inside one receive operation.

### 4. `SprayBomb::Hit` — terrain settle and deployed-object build

**Function:** `SprayBomb::Hit @ 0x0053ABBF`  
**Subsystem:** Projectile collision, deterministic deployment, and presentation  
**Owner peer executes?:** Yes, when the locally simulated bomb hits terrain.  
**Remote peer executes?:** Yes, when the received bomb representation hits terrain. `Ordnance_ControlAll` controls all entries in `ordnanceList`; it does not skip `bSend == 0` objects.  
**How remote object is created:** The remote **parent** is created by `Ordnance_Receive`. The deployed `SprayBuilding` is then built locally on that peer, not network-created.  
**Network-created side effects:** None in the planting branch. The high-speed terrain-bounce branch quantizes its matrix only when networked and `source == Net_GetMyPlayerID`; this is not a creation/send gate.  
**Damage side effects:** No immediate damage. It copies parent damage bits 4 and 5 into the new `SprayBuilding` when the class signature is `SBMB`.  
**Terrain side effects:** None.  
**Presentation side effects:** Bounce sound and reflected velocity/orientation on non-planting paths.  
**Lifecycle/state-transition side effects:** On terrain contact (`param_1 == null`) and post-bounce speed below `5.0`, builds `SprayBuilding` with the parent object's matrix/team and flags the parent `0x200` for removal. Collision with a building follows a different bounce/base-hit path.  
**Existing authority predicate:** No authority predicate around `GameObjectClass::Build`; that absence matches deterministic per-peer construction. The bounce quantization sub-block uses `Net_IsNetGame() && source == Net_GetMyPlayerID()`.  
**Relevant object_type behavior:** Parent is not a `DistributedObject`. Newly built `SprayBuilding` remains `object_type = 0`.  
**dwLocalID / activnet_id relevance:** No `dwLocalID` is assigned to the deployed building. Parent `source` is an activnet player id and is used for the bounce-owner test.  
**Sibling precedent:** Deterministic child creation is corroborated by the child's forced `bSend = 0`; Popper is not equivalent because it explicitly creates a network-sent child.  
**Classification:** BOTH_BY_DESIGN.  
**Confidence:** HIGH.  
**Evidence:** `0053abbf_SprayBomb_Hit.c`, `00533a92_Ordnance_ControlAll.c`, `00498d9c_GameObjectClass_Build.c`, and `0048ed50_DistributedObject_DistributedObject.c`.  
**Candidate patch boundary:** None. Do not gate the deployed-object `Build` on `source`, team, `IsLocal`, or `IsRemote`.  
**Risks:** Gating the receiver-side build removes its entire local deployed object and therefore its local payload, presentation, collision, and cleanup.  
**DO_NOT_PATCH_IF:** The deployed object is unowned and its child ordnance is intentionally unsent, as the exact source shows.

### 5. `SprayBuilding` construction / `GameObjectClass::Build`

**Function:** `GameObjectClass::Build @ 0x00498D9C`; `SprayBuildingClass::Build @ 0x0053A737`; `SprayBuilding::SprayBuilding @ 0x0053A468`  
**Subsystem:** Deterministic deployed-object lifecycle  
**Owner peer executes?:** Yes, but it does not produce an owner-tagged deployed object.  
**Remote peer executes?:** Yes, producing an equivalent unowned local object.  
**How remote object is created:** Direct local `GameObjectClass::Build` from the received parent's `Hit`, not `DistributedObject::Create`.  
**Network-created side effects:** None. `SetLocal`, `SetRemote`, and `UpdatePermState` are absent.  
**Damage side effects:** Initializes normal building health and sets `dmg_player = false`, `dmg_remote = false` before `Hit` copies the parent flags.  
**Terrain side effects:** None.  
**Presentation side effects:** Loads/creates the structure entity and initializes ordinary building state.  
**Lifecycle/state-transition side effects:** Initializes `shotTimer = -triggerDelay`, sound pointer null, and adds the object to ordinary game-object/distributed-object lists without assigning network ownership.  
**Existing authority predicate:** None required for this deterministic build.  
**Relevant object_type behavior:** `object_type == 0`; therefore `IsLocal() == false` and `IsRemote() == false` on every peer.  
**dwLocalID / activnet_id relevance:** No meaningful network identity is assigned to this deployed instance.  
**Sibling precedent:** `DistributedObject::Create` demonstrates the contrasting replicated path: it calls the same `Build`, writes the transmitted id/player information, and then calls `SetRemote`.  
**Classification:** BOTH_BY_DESIGN.  
**Confidence:** CONFIRMED in 1.5; HIGH for Redux preservation.  
**Evidence:** The constructor chain `SprayBuilding -> Building -> GameObject -> DistributedObject`, plus the absence of a post-build `SetLocal` in `SprayBomb::Hit`.  
**Candidate patch boundary:** None.  
**Risks:** An `IsRemote` payload gate cannot suppress a receiver-side deterministic copy because it is not remote. An `IsLocal`-required gate suppresses every deployed copy.  
**DO_NOT_PATCH_IF:** The proposed predicate has not accounted for `object_type == 0`.

### 6. `SprayBuilding::Simulate` — spin, floor alignment, and sound

**Function:** `SprayBuilding::Simulate @ 0x0053A779` (1.5); Redux `0x005DA6E0`  
**Subsystem:** Presentation and deterministic per-peer state  
**Owner peer executes?:** Yes, on its unowned deterministic copy.  
**Remote peer executes?:** Yes, on its separate unowned deterministic copy.  
**How remote object is created:** From remote parent `SprayBomb::Hit`, not from a `SprayBuilding` network packet.  
**Network-created side effects:** None in this region.  
**Damage side effects:** None.  
**Terrain side effects:** Reads `Terrain_FindFloor`; does not mutate terrain.  
**Presentation side effects:** Spin/orientation update, height interpolation, and one looping fire GAS event.  
**Lifecycle/state-transition side effects:** Advances `shotTimer` and updates transform.  
**Existing authority predicate:** None.  
**Relevant object_type behavior:** Unowned `0`, so remote/local ownership predicates are not meaningful here.  
**dwLocalID / activnet_id relevance:** None.  
**Sibling precedent:** Per-peer projectile and presentation simulation is normal; `Ordnance_Receive` also back-simulates remote ordnance locally.  
**Classification:** BOTH_BY_DESIGN.  
**Confidence:** CONFIRMED.  
**Evidence:** Exact and current Redux decompiles show the same spin, floor-read, timer, and GAS sequence before the payload build.  
**Candidate patch boundary:** None.  
**Risks:** Whole-function return loses transform/floor alignment, sound, timer advancement, payload, ammo exhaustion, and cleanup.  
**DO_NOT_PATCH_IF:** The patch returns before this presentation/state work on a peer that still owns authoritative local targets.

### 7. `SprayBuilding::Simulate` — payload loop

**Function:** `SprayBuilding::Simulate @ 0x0053A779` (1.5); Redux `0x005DA6E0`  
**Subsystem:** Deterministic gameplay ordnance and lifecycle  
**Owner peer executes?:** Yes.  
**Remote peer executes?:** Yes, but "remote" refers to the peer, not to `SprayBuilding::object_type`; the object is unowned.  
**How remote object is created:** Each peer's payload is built locally from that peer's deterministic `SprayBuilding`. No payload is network-created.  
**Network-created side effects:** `Ordnance::Init` provisionally assigns local `(source, ordid)` and inserts the object in `netOrdnanceMap`, but the caller immediately forces `bSend = 0`; no `RO` creation record is emitted.  
**Damage side effects:** Creates damaging gameplay ordnance and copies `dmg_player`, `dmg_remote`, and team bits into it. The payload can collide locally; actual target health application is guarded by target ownership in `Craft::DamageAlloc`/`Building::DamageAlloc`.  
**Terrain side effects:** None in the producer loop.  
**Presentation side effects:** Payload geometry/sound and pseudo-random pitch are locally produced.  
**Lifecycle/state-transition side effects:** Backdates payload `dt`, subtracts `shotDelay`, consumes ammo, and eventually flags/removes the deployed object when payload class is missing or ammo is insufficient.  
**Existing authority predicate:** `payload->bSend = 0` is the network-authority policy. Target-side `!IsRemote(target)` is the damage-authority policy.  
**Relevant object_type behavior:** Producer is unowned; payload is not a `DistributedObject`.  
**dwLocalID / activnet_id relevance:** Payload `source`/`ordid` are local ordnance-map identity only because `bSend = 0`; team comes from the producer object's team and is copied into damage bits.  
**Sibling precedent:** Popper is deliberately different. In exact 1.5 it copies the parent `(source, ordid+1)` and sets child `bSend` according to whether `source == Net_GetMyPlayerID`; current Redux wraps that network-sent child creation in the same source-player predicate. It does **not** compare against `LocalTeam`.  
**Classification:** BOTH_BY_DESIGN.  
**Confidence:** CONFIRMED that both per-peer construction and no-send are intended structural companions; two-PC validation is still required before calling every observed visual double a non-bug.  
**Evidence:** `0053a779_SprayBuilding_Simulate.c` sets `pOVar10->bSend = 0`; current GOG Ghidra at `0x005DA6E0` stores zero to payload `+0x80`; `00533c82_Ordnance_SendNew.c` skips it.  
**Candidate patch boundary:** **IMPLEMENT = NO.** Instrument only.  
**Risks:** Suppressing this loop on the receiver peer can starve damage to receiver-owned craft/buildings, because no network payload arrives to replace it. It also freezes ammo/timer cleanup if suppression is an early return.  
**DO_NOT_PATCH_IF:** `bSend` remains zero, payload `Receive` count remains zero, or target-side authority remains the only health-mutation guard.

### 8. `Ordnance_SendNew` / `Ordnance_Receive` — payload boundary

**Function:** `Ordnance_SendNew @ 0x00533C82`; `Ordnance_Receive @ 0x00534666`  
**Subsystem:** Payload network-lifecycle negative control  
**Owner peer executes?:** Send/receive functions run as global network work, but neither processes these payloads as new records.  
**Remote peer executes?:** Same.  
**How remote object is created:** It is not. Each peer already created its own local payload.  
**Network-created side effects:** None for payload objects because `bSend == 0`.  
**Damage side effects:** None directly.  
**Terrain side effects:** None.  
**Presentation side effects:** None directly.  
**Lifecycle/state-transition side effects:** Payload stays in local `ordnanceList`/`netOrdnanceMap` until normal cleanup; `Ordnance::~Ordnance` erases its local key.  
**Existing authority predicate:** `bSend != 0` at send; `(source, ordid)` lookup at receive.  
**Relevant object_type behavior:** Not applicable.  
**dwLocalID / activnet_id relevance:** No owner `dwLocalID` is transmitted for these unsent payloads. The locally assigned `source` equals that peer's player id and is not a team id.  
**Sibling precedent:** Popper's child explicitly sets `bSend` true only for the source player; Splinter explicitly sets it false everywhere.  
**Classification:** BOTH_BY_DESIGN (local-only negative control).  
**Confidence:** CONFIRMED.  
**Evidence:** Direct dataflow from child `Build` to `bSend = 0` to send's `bSend != 0` filter.  
**Candidate patch boundary:** None.  
**Risks:** Instrumentation that logs every `OrdnanceClass::Build` as a network send will report a false duplicate. Send and receive must be logged separately.  
**DO_NOT_PATCH_IF:** No matching child record is observed at `Ordnance_SendNew` and `Ordnance_Receive`.

### 9. `SprayBuilding` exhaustion and destruction

**Function:** Tail of `SprayBuilding::Simulate`; `SprayBuilding::~SprayBuilding @ 0x0053A4B0`; base `Building`/`GameObject`/`DistributedObject` teardown  
**Subsystem:** Deterministic per-peer lifecycle  
**Owner peer executes?:** Yes, on its unowned copy.  
**Remote peer executes?:** Yes, on its own unowned copy.  
**How remote object is created:** Direct deterministic build, as above.  
**Network-created side effects:** No shared deployed-object creation identity was established. No valid remote `SprayBuilding` counterpart exists for `RemoteDelete` to target by `dwLocalID`.  
**Damage side effects:** When the deployed object is damaged, `Building::DamageAlloc` mutates health because `object_type == 0` is not remote; on death it marks destroyed/remove flags.  
**Terrain side effects:** None.  
**Presentation side effects:** Base building explosion/removal may produce local presentation when invoked.  
**Lifecycle/state-transition side effects:** Missing payload class or insufficient ammo sets `0x200` and immediately dispatches the removal virtual. Damage death sets `0x01000200`, but stock `SprayBuilding::Simulate` fails to honor it and continues firing—the separate undead defect. Destructors stop/remove ordinary object state and erase map entries only when `object_type` is local or remote.  
**Existing authority predicate:** Ammo/timer are local deterministic state. `Building::DamageAlloc` uses `!IsRemote`; for an unowned building this evaluates true.  
**Relevant object_type behavior:** `0` means `DistributedObject::~DistributedObject` removes it from the all-object vector but from neither local nor remote network map.  
**dwLocalID / activnet_id relevance:** No shared deployed-object id was proven; do not use `RemoteDelete` as its normal lifecycle explanation.  
**Sibling precedent:** Locally reconstructed transient effects clean themselves up on each peer.  
**Classification:** BOTH_BY_DESIGN for normal exhaustion/removal; OWNER_ONLY is not supported.  
**Confidence:** HIGH.  
**Evidence:** `SprayBuilding::Simulate`, `Building::DamageAlloc`, and `DistributedObject::~DistributedObject`.  
**Candidate patch boundary:** None for multiplayer authority. The existing dead-flag correction is a distinct issue.  
**Risks:** Suppressing child construction without preserving shot-delay, ammo, and removal transitions can create a permanent deployed object.  
**DO_NOT_PATCH_IF:** The replacement path does not prove identical cleanup on every deterministic copy.

### 10. Existing `SPLINTER_UNDEAD` hook

**Function:** OpenShim `RunSprayBuildingSimulateWithDeadGate` / `SprayBuildingSimulateUndeadFixHook`  
**Subsystem:** Existing lifecycle repair  
**Owner peer executes?:** In current code, the hook is installed but its behavioral gate is active only in a single-player session.  
**Remote peer executes?:** In a network game `g_SplinterUndeadFixActive == false`, so it delegates directly to stock `SprayBuilding::Simulate` on every peer.  
**How remote object is created:** Not affected by this hook.  
**Network-created side effects:** None.  
**Damage side effects:** None directly.  
**Terrain side effects:** None.  
**Presentation side effects:** When active and dead/remove flags are set, it routes through base `Building::Simulate`, which performs stock explosion/removal dispatch instead of more payload firing.  
**Lifecycle/state-transition side effects:** Restores the base class dead/remove gate omitted by the override.  
**Existing authority predicate:** `g_SplinterUndeadFixActive && flags & 0x01000200`; active is currently `enabled && IsSinglePlayerSession()`.  
**Relevant object_type behavior:** In single player the unowned `SprayBuilding` is not remote, so `Building::Simulate` performs its dead/remove dispatch. The present hook makes no multiplayer ownership claim.  
**dwLocalID / activnet_id relevance:** None.  
**Sibling precedent:** Directly restores the behavior of `Building::Simulate`.  
**Classification:** BOTH_BY_DESIGN as a per-copy lifecycle correction, but currently single-player-only by OpenShim feature policy.  
**Confidence:** CONFIRMED.  
**Evidence:** `src/patches/bzr_hooks.cpp`: `RefreshSplinterUndeadFixState`, `RunSprayBuildingSimulateWithDeadGate`, and `InstallSplinterUndeadFixIfPossible`.  
**Candidate patch boundary:** No authority change. If multiplayer enablement of `SPLINTER_UNDEAD` is revisited, qualify it separately as a negotiated deterministic-simulation change.  
**Risks:** Combining an authority gate with this hook can bypass the base dead/remove route or make only one deterministic copy clean up.  
**DO_NOT_PATCH_IF:** The proposed authority work changes this existing dead-state contract without separate proof and multiplayer compatibility qualification.

## Side-effect classification

| Operation | Category | Required peers | Reason |
| --- | --- | --- | --- |
| Spin and orientation update | A. PRESENTATION / B. DETERMINISTIC PER-PEER STATE | Both | Keeps each locally constructed deployed object aligned and visible. |
| `Terrain_FindFloor` height interpolation | B. DETERMINISTIC PER-PEER STATE | Both | Reads local terrain; performs no terrain mutation. |
| Fire GAS event | A. PRESENTATION | Both | Local sound for the locally reconstructed event. |
| `OrdnanceClass::Build` payload | C. AUTHORITATIVE GAMEPLAY, implemented as per-peer target-authority simulation | Both | No payload replication exists; target `DamageAlloc` owns the health mutation. |
| `payload->bSend = 0` | D. NETWORK LIFECYCLE | Both | Explicitly prevents secondary replication. |
| Damage flag propagation | C. AUTHORITATIVE GAMEPLAY metadata | Both | Preserves player/remote/team attribution across deterministic reconstruction. |
| Timer/ammo decrement and self-remove | B. DETERMINISTIC PER-PEER STATE | Both | Each unowned deployed copy owns its own local lifecycle. |
| `SPLINTER_UNDEAD` dead/remove routing | B/C lifecycle correction | Each peer whose copy is enabled | Prevents a dead local copy from continuing payload production. |

## Strong candidate invariant: disproved

The requested candidate was:

```text
OWNER SprayBuilding: payload Build = N, Ordnance_SendNew = N
REMOTE SprayBuilding: payload Build = 0, Ordnance_Receive = N
```

Static evidence instead establishes:

```text
FIRING PEER'S UNOWNED SprayBuilding:
  payload Build = N
  payload Ordnance_SendNew = 0
  payload Ordnance_Receive = 0

OTHER PEER'S UNOWNED SprayBuilding:
  payload Build = N
  payload Ordnance_SendNew = 0
  payload Ordnance_Receive = 0
```

The only `SendNew = 1 / Receive = 1` relationship is for the **parent `SprayBomb`**, not its payload.

## Patch decision

| Boundary | Classification | Confidence | Implement? | Reason |
| --- | --- | --- | --- | --- |
| `SprayBomb::Hit` deployed `Build` | BOTH_BY_DESIGN | HIGH | **NO** | This creates the receiver peer's local, unowned deterministic producer. |
| Whole `SprayBuilding::Simulate` | BOTH_BY_DESIGN | CONFIRMED | **NO** | Would remove presentation, local physics/state, payload, and cleanup. |
| `SprayBuilding` payload `Build` | BOTH_BY_DESIGN | CONFIRMED | **NO** | Child is explicitly unsent; no received replacement exists. |
| Payload `bSend = 0` | BOTH_BY_DESIGN network negative control | CONFIRMED | **NO** | This is the mechanism preventing true replication duplication. |
| Existing `SPLINTER_UNDEAD` gate | Separate lifecycle defect | CONFIRMED | **NO authority change** | Preserve the existing hook; multiplayer activation is a separate compatibility decision. |

No boundary meets the synthesis criteria for an owner-only authority patch. In particular:

- `IsRemote(SprayBuilding)` is false on both peers, so it cannot select the receiver-side copy.
- `IsLocal(SprayBuilding)` is also false on both peers, so requiring it suppresses all payload.
- `team == LocalTeam` is not the Popper convention and is insufficient for player/object authority.
- `source == Net_GetMyPlayerID` is the Popper/ordnance convention, but `SprayBuilding` is not ordnance and does not retain the parent source as an authority field.
- even if a peer-selection predicate were available, selecting one producer would starve target-authoritative damage on the other peer unless payload networking were redesigned, which is outside the narrow task and would be a major semantic change.

## What still requires two-PC qualification

Static analysis determines the intended transport/lifecycle shape, but it does not prove that the visible bug report is imaginary. A two-PC trace should test for a divergence elsewhere:

1. Log parent `SprayBomb` `Build`, `Ordnance_SendNew`, and `Ordnance_Receive` using `(source, ordid)`.
2. Log `SprayBomb::Hit` on both peers and record whether each builds exactly one unowned `SprayBuilding`.
3. Log each payload `Build` and its immediate `bSend` transition `1 -> 0`.
4. Log `Ordnance_SendNew` records and prove that none has a payload pointer/caller from `SprayBuilding::Simulate`.
5. Log `Ordnance_Receive` and prove that only the parent, not the payload, arrives.
6. Log payload collision plus target `object_type` and actual health before/after. Expected: a remote target replica may show presentation/collision but only the non-remote target applies health damage.
7. Compare payload count, transform, pseudo-random pitch, and damage on both peers. A real defect may still exist in deterministic timing/random-state/collision divergence, but it is not the hypothesized `Build + SendNew + Receive` duplication.
8. Separately test a deployed splinter killed before ammo exhaustion. Current OpenShim deliberately disables `SPLINTER_UNDEAD` in network games, so stock undead behavior remains expected there and must not be mistaken for an authority-patch regression.

## Final confidence summary

### PROVEN

- Parent `SprayBomb` is network ordnance.
- `SprayBuilding` is directly and independently built by `SprayBomb::Hit` without `SetLocal`/`SetRemote`.
- The deployed instance is unowned (`object_type == 0`) on both peers under the exact-source path.
- The payload is built locally on each peer and immediately forced to `bSend = 0` in both exact 1.5 and current Redux.
- `Ordnance_SendNew` excludes `bSend == 0`; the hypothesized payload send/receive duplication chain is false.
- `source` is activnet player identity, not team identity.
- Payload damage-origin bits are propagated, and target health mutation is guarded against remote targets.
- The existing `SPLINTER_UNDEAD` hook is orthogonal and currently inactive in multiplayer.

### STRONGLY SUSPECTED BUT NOT PATCHED

- Reported "double" Splinter visuals/projectiles may reflect the intended per-peer reconstruction model, or a separate divergence in timing, random pitch, collision, or damage observation. Static evidence does not justify removing either peer's stream.

### REQUIRES TWO-PC QUALIFICATION

- Exactly one parent send/receive, exactly one deployed build per peer, zero payload send/receive records, local/remote target collision behavior, and whether any genuine duplicate damage remains after correlating by target ownership.

### IMPLEMENTATION RESULT

**No production patch is justified.** The safe synthesis result for Splinter payload authority is `IMPLEMENT = NO` unless runtime evidence disproves the explicit `bSend = 0` / deterministic-per-peer design.
