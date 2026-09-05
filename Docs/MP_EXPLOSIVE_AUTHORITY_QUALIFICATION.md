# Multiplayer explosive authority qualification

Date: 2026-09-04. Branch: `agent/mp-explosive-authority`.

**Released-Redux correction:** the later section "Redux receiver replay findings"
supersedes the historical-reference Daywrecker same-object guard conclusions.
Redux 2.2.301 has a shared consumed byte in both detonation bodies. The new
receiver replay findings below are current-binary evidence; 1.5 networking is
not used as proof of Redux network behavior.

## Splinter — no authority patch

**HIGH confidence: the proposed payload duplication chain is contradicted.**
The pre-existing staged `MPAUTH_SPLINTER_STATIC_ANALYSIS.md` records this correction;
this pass checked the decisive statements against targeted function files, without
repeating the original investigation.

| Question | Static conclusion |
| --- | --- |
| Does the other peer simulate the deployed producer? | Yes, under the reference reconstruction path, but it is a directly built, unowned producer, not necessarily an `IsRemote` distributed replica. |
| Does the payload loop build ordnance? | Yes; local construction/map identity does not imply network transmission. |
| Does `SendNew` send that payload? | No: immediately after `Build`, `SprayBuilding::Simulate` writes `payload->bSend = 0`. `SendNew` processes only nonzero `bSend`. |
| Does the receiver obtain an owner's replacement payload? | No replacement follows through this send path. `Receive` reconstructs the parent `SprayBomb`, with sender identity and `bSend = 0`. |
| Should the other peer skip the payload loop? | No. Removing its stream would require a transport/damage redesign, outside this task. |
| What else must remain? | Spin/transform updates, terrain-floor/altitude adjustment, shot timing, GAS presentation, ammo accounting, and removal/cleanup. |
| Is `SprayBomb::Hit -> Build(SprayBuilding)` owner-only? | No such guard is established. The parent is ordnance; direct deployed construction on each peer does not call `SetLocal`/`SetRemote`. |

Decisive evidence in sibling `GrizzlyOne95/BZ1_Source`, whose local origin was
verified: `1.5/functions/0053/0053a779_SprayBuilding_Simulate.c` explicitly writes
`bSend = 0`; `00533c82_Ordnance_SendNew.c` checks nonzero `bSend`;
`00534666_Ordnance_Receive.c` builds and assigns the received identity;
`0053abbf_SprayBomb_Hit.c` directly builds the producer. The prior constructor /
`IsLocal` / `IsRemote` analysis establishes unowned type 0 (local 1, remote 2).
`0049/00498d9c_GameObjectClass_Build.c` does not establish ownership.

Redux corroboration: retained GOG decompile
`reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_005da6e0-005da6e0.c`,
lines 137–138: `FUN_00586ff0(...)` followed immediately by a zero store to
payload `+0x80`. Existing RTTI/vtable mapping identifies this as
`SprayBuilding::Simulate` (`?AVSprayBuilding@@`, slot `0x00888228`).
This is static corroboration, not a fresh live-runtime capture.

Popper is not an equivalent control: the reference `00536268_Popper_Control.c`
copies source/ordid and conditionally enables child `bSend`; Splinter disables it
unconditionally. Reference Craft/Building `DamageAlloc` guards health mutation
with `!IsRemote(target)`, supporting local payload simulation for local targets.

**Patch boundary evaluated:** only the `OrdnanceClass::Build` payload loop.
**Implementation:** none; the owner-build/send/remote-receive gate fails.
`SprayBomb::Hit` and `SPLINTER_UNDEAD` are untouched. The latter still routes dead
objects to base `Building::Simulate` only when its existing single-player gate is
active; its multiplayer behavior has not been enabled or otherwise changed.

## Daywrecker — no authority patch

Smallest useful lifecycle graph from the targeted 1.5 reference:

```text
PowerUp::Simulate: owner/non-remote death/removal checks; physics on both peers
  ground contact clears vehicle flag 4
RegCollision: may ignore launcher while flags 4+8 set;
  otherwise optional contact DamageAlloc while flag 4 set, then clear flag 4
    -> next DayWrecker::Simulate, flag 4 clear:
       set object remove flag 0x200; set vehicle flag 0x20; remove light
       -> MakeCrater -> removal virtual -> configured ExplosionClass::Build
separate DayWrecker::Explode:
  set object remove flag 0x200 -> xplBuilding Build -> glare/particles
  -> removal virtual; no direct MakeCrater
DistributedObject::Destroy: publish deletion state / remember deleted local ID
RemoteDelete (non-local): set 0x280; clear ownership; erase remote map entry;
  send deletion bookkeeping -> Destroy -> final virtual only for class 0x53435250
```

Evidence: `0052d029`, `0052d12b`, `0052d234`, `004a9a91`, `0048f72d`,
`0048ffb7`, and `0051f74c` named function files in the same reference corpus.
Immediate `ExplosionClass::Build` (`0052e811`) dispatches initialization;
`Explosion::Init` (`0052e472`) initializes configured damage and searches targets
for `DamageAlloc`. Thus neither explosion class may simply be assumed cosmetic.

The inspected collision/deployed paths have no source ownership guard, so a
remote copy can reach the decision. Flag 4 records deployment, not a consumed
detonation. Flags `0x200` / `0x20` request removal/state change; the deployed branch
does not check them before effects. Whether scheduling/removal permits another
entry for the same object remains unresolved. The existence of two explosion
paths does not prove both execute for one lifetime, nor that their effects are
equivalent. `Destroy` does not itself call `Explode`; the `RemoteDelete` tail is
not an unconditional Daywrecker callback.

**No HIGH-confidence owner-only source boundary established.** Target health
authority is evidenced for Craft/Building; terrain and presentation require
per-peer consideration. `MakeCrater` shifts bytes returned by `GetNormalPtr` and
is non-idempotent when repeated on the same buffer, but those operations alone
do not prove height deformation or the reported terrain-spire cause. One call on
host plus one on client is not two calls on either buffer.

**Implementation:** none. The released Redux lifecycle/removal ordering and
same-peer repeat-effect boundary require two-peer evidence. No broad Redux
remapping, production hook, authority predicate, or instrumentation was added.

## Focused follow-up: parent topology and same-object re-entry

This follow-up uses the existing findings and targeted 1.5 function exports only;
the retained Redux payload decompile remains corroboration, not end-to-end Redux
lifecycle proof. No broad corpus search, sibling audit, runtime run, or patch.

### Splinter parent topology

**B for the traced deployment: independently/local-only reconstructed per peer.**
`SprayBomb::Hit` (`0053abbf`) has one deployed `GameObjectClass::Build` call in
the terrain-contact, reflected-speed-below-5 branch. It then marks the bomb's
object `0x200` and returns. `SprayBuildingClass::Build` (`0053a737`) allocates one
producer; its constructor (`0053a468`) does not promote ownership. The previously
established base construction leaves `object_type = 0`. No deployment call to
`SetLocal`, assignment of a network `dwLocalID`, or creation publication occurs.
Do not describe the unassigned ID as necessarily zero: the inspected
`DistributedObject` constructor (`0048ed50`) does not initialize that field.

The contrasting generic route is `SetLocal` (`0048f80b`): type 0 becomes type 1,
receives a player/counter ID, enters the local map, and calls `UpdatePermState`
(`0048b07d`). `DistributedObject::Create` (`0048e9e4`) can reconstruct a class
named in a creation record, then installs the transmitted identity and calls
`SetRemote`. That generic capability is not evidence of a creation record for
this deployment. `SprayBuilding::Simulate` does not publish one either.

**More than one producer on one peer for one logical deployment is not proven.**
One invocation of the planting branch builds one producer. `Ordnance_ControlAll`
(`00533a92`) skips Control and dispatches cleanup when object flag `0x200` is
already set on its next visit. However, `Hit` itself does not test a consumed or
removal flag before Build. The scoped evidence does not establish all possible
same-Control collision callbacks or a whole-lifetime one-build invariant. Thus
B describes the creation topology, not a proof that every duplicate scenario is
impossible. No reachable second Build, owner-plus-replica creation chain (C), or
HIGH-confidence defective creation boundary has been established. **No patch.**

### Splinter child payload semantics

`bSend = 0` excludes creation transmission, not simulation or gameplay.
`Ordnance_ControlAll` dispatches Control without testing `bSend`; only removal
flag `0x200` selects cleanup. Collision/Hit behavior depends on the configured
payload subclass: the base `Ordnance::Control`/`Hit` are empty, so do not infer
effects from those base methods. Concrete `Bullet::Hit` (`0052bbf9`) calls target
damage virtual `+0x38`, writes `hitOrdClass`, builds the configured impact
explosion, and marks removal, with no `bSend` gate. `Grenade::Hit` (`0052fde6`)
can additionally call `MakeCrater` before `Bullet::Hit`. Existing
`ExplosionClass::Build -> Init` evidence establishes configured area damage.
These are capability evidence, not a claim that every configured Splinter
payload is a Grenade or produces a crater. Collision, damage, explosions,
gameplay state mutation, and presentation are all compatible with `bSend = 0`;
the child is **not presentation-only**. Existing target authority guards still
apply to health changes.

### Daywrecker same-object graph

Keep the two flag stores separate: **V4** is vehicle `flags & 4`; **O200** is
object `flags & 0x200`. Neither is an established common consumed-effect flag.

| Entry / condition | Flags before | Irreversible effects | Flags changed / removal | Subsequent entry evidence |
| --- | --- | --- | --- | --- |
| `Simulate`, V4 clear | O200 unchecked | `MakeCrater` unless TerrainEdit; configured explosion Build after removal virtual | O200 set before effects; vehicle `0x20` set; V4 stays clear; light removed; DistributedObject-subobject virtual `+0x10` | No direct `Explode` call. Another Simulate would repeat this branch **if dispatched**, but a subsequent dispatch before deletion is unproven. |
| `Simulate`, V4 set -> `PowerUp::Simulate` | Non-remote object: death `0x1000000` checked before O200 | Death branch dispatches `+0x14` explosion virtual and returns; O200-only branch dispatches `+0x10` removal virtual and returns | Ordinary ground contact can clear V4; neither early-return branch falls into the deployed branch during this call | After landing, a later Daywrecker Simulate selects the deployed branch. After deployed effects, V4 remains clear, so this inherited death branch is not reached through ordinary subsequent Simulate. |
| `RegCollision`, launcher exception | V4 and vehicle `8` set; collided object equals launcher | None | Returns false, flags unchanged | No effect call. |
| Other `RegCollision` | O200 unchecked; contact damage requires V4, nonzero configured damage, and target object | Target damage virtual `+0x38` before V4 clear | Clears V4; returns true; no Destroy/delete | Does not call Explode. After deployed Simulate, V4 is already clear, so this contact-damage branch is skipped. |
| `Explode` | No V4 or O200 guard in body | `xplBuilding` Build, conditional glare, particles; no MakeCrater | Sets O200 first; does not change V4; DistributedObject-subobject virtual `+0x10` at end | No direct second effect callback. A later dispatch remains unproven; O200 alone does not make this body idempotent. |
| `DistributedObject::Remove` (`00490328`) | Local type 1, or remote type 2 with ID <= 0xffff, reaches Destroy; others return | Deletion bookkeeping via Destroy | No physical delete or Explode in this body | Does not establish when the scheduler frees the object. |
| `Destroy` | No V4/O200 test | Network deletion state and deleted-ID bookkeeping when dp exists | No V4/O200 change or physical delete | Queried virtuals obtain object/state; no direct Explode or Simulate edge. |
| `RemoteDelete` | Type != 1; no O200 exclusion | Deletion bookkeeping/send, then Destroy | Sets object `0x280`, clears ownership, erases remote map ID | Tail `+0x10` virtual requires class signature `0x53435250` (SCRP), not Daywrecker WRCK. No Daywrecker explosion edge. |

The exports use a DistributedObject subobject at complete-object `+0x20`:
`Simulate` addresses its vtable there, while `Explode` uses the adjusted `this`
and fields shifted by `0x20`. Do not mistake those for different objects.
The `+0x10`/`+0x14` call-site roles above follow the existing removal/explosion
analysis; the constructor export names vtables but does not expose their slot
contents. An exact released-Redux slot target and scheduler ordering are not
newly proven by these files.

One additional blocked feedback edge is explicit: `PowerUp::DamageAlloc`
(`004a94a4`) requires O200 clear before any damage handling. Both Daywrecker
effect bodies set O200 before explosion construction, preventing that inherited
damage route from damaging the same pending-removal object and scheduling a
fresh death through this handler.

**Sequence verdicts:** `Simulate -> MakeCrater -> later Explode` is unresolved,
not an internal call chain. Inserting `RegCollision` does not supply the missing
Explode edge. `Explode -> removal/Destroy -> another effect callback` is not
established: Destroy supplies no such callback. `RemoteDelete -> Destroy` can
process an already-marked object, but supplies no Daywrecker effect path, whether
or not effects ran earlier. Repeated Simulate or explicit Explode dispatch could
repeat effects at the function-body level; reachable same-object scheduling is
the missing proof. **No HIGH-confidence missing one-shot/authority boundary;
Daywrecker remains unpatched.** This question needs same-machine lifetime/order
evidence; it does not inherently require two PCs or further terrain-sync work.

Validation for this follow-up: documentation diff/whitespace review only; the
build/test results below belong to the prior pass. No implementation changed.

## Redux receiver replay findings

User clarification: the second Daywrecker event includes damage, visuals, and
sound, without a visible second bomb. The **launcher** sees one; other players
can see two. This is receiver/launcher asymmetry, not necessarily host/guest
authority. The symptom is user-reported, not captured in this pass.

Evidence: Ghidra MCP `search_symbols_by_name`, `read_bytes`,
`list_cross_references`, and `decompile_function` against only
`/battlezone98redux.exe-007c64`, GOG Redux **2.2.301**, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`
(project metadata). No live process/PID, Steam remapping, or transport-wide
audit. Identities below follow imported RTTI vtables, exact call edges and
function bodies; advisory USER_DEFINED labels at other addresses are not used.

### Daywrecker: existing guard, possible recreated lifetime

**HIGH-confidence current-binary correction:** constructor `004b0420` installs
RTTI vtables `00878508` and `00878574` at complete-object offsets 0 and `0x18`,
and zeroes byte `this+0x230`. First vtable slot `+0x3c` points to Simulate
`004b0460`; the DistributedObject vtable `+0x14` points to Explode `004b07d0`.
Simulate checks/sets `this+0x230` before crater or explosion work. Explode
checks/sets adjusted-this `+0x218`: **the same byte** because its this-pointer
is complete-object `+0x18`. Both bodies set it before irreversible effects.
Explode also calls the crater helper in Redux, unlike the 1.5 reference.
Thus ordinary repeated calls to these two bodies on the same intact lifetime
do not explain two detonations. The earlier missing-common-guard hypothesis is
contradicted for this released build.

There is instead a specific receiver reconstruction route:

1. Either detonation body calls DistributedObject vtable `+0x10`, concretely
   GameObject removal `004dae70`. Its `004b7ab0` removal-bookkeeping call only
   reaches `004b7bd0` (Destroy/deleted-ID recording) for local type 1 or remote
   type 2 with ID below `0x10000`. A remote dynamic ID at/above that threshold
   takes the return path without that deleted-ID record.
2. Destruction proceeds through PowerUp/GameObject cleanup (`005a7bf0`,
   `004dab60`) to DistributedObject destructor `004b79f0`, which erases the
   ownership-map entry but does not call the deleted-ID recorder.
3. Received ordinary state in `004b8590`, subtype `(record[1]&3)==0`, looks up
   the ID. If missing, its deleted-ID rejection only applies **when a deletion
   record exists**, with the timestamp comparison shown in that body. Otherwise
   it calls Create `004b9350`, then installs/unpacks the state.
4. Create builds a fresh class instance via `004e1190`, assigns the wire ID,
   and calls SetRemote `004b7f20`. The Daywrecker constructor resets the consumed
   byte for this new lifetime. PowerUp state unpack `005aacf0` reconstructs
   vehicle flags (including deployment flag 4), not the Daywrecker consumed byte.
   The new instance can therefore enter its first detonation normally.

There is a second relevant acceptance difference: permanent-state reader
`004b8fa0` calls Create for a missing ID and ordinary state without the timed
deleted-ID test present in `004b8590`. Create itself logs **"Reviving id %08x"**,
erases an existing deleted-ID entry if found, and continues construction. This
proves revival is supported; it does not prove which receive route caused the
reported event or that all revival is erroneous.

**Static capability HIGH; attribution to the reported match remains unverified.**
The concrete conditional trigger is a late ordinary state for an already
locally-detonated, removed remote dynamic bomb, accepted as a new lifetime.
The launcher's local removal takes the deleted-ID-recording branch; the receiver
has the distinct local-prediction/removal window above. No packet loss or
duplicate datagram is required by this hypothesis: a delayed pre-detonation
state suffices if it reaches that window and passes the surrounding checks.
This can explain launcher/receiver asymmetry without bypassing the one-shot
byte. An invisible second bomb would additionally require its recreated
lifetime to detonate before a visible render; render ordering is **not proven**.
The narrow candidate boundary is retirement/recreation of a consumed remote
Daywrecker ID, not an owner-only gate on crater/explosion simulation.

### Splinter: replay into a consumed bomb

Redux RTTI SprayBomb vtable `008881c4` maps Simulate `+0x10` to `004e7d30`
(Grenade) and Hit `+0x14` to `005db080`. The simulation call chain is
`004e7d30 -> 005bd060 -> 00480470` (Grenade -> Rocket -> Bullet).
Bullet simulation reaches the terrain Hit virtual without an entry removal
test. SprayBomb Hit can build via `004e1190`, then sets object `0x200`; it
has no consumed/removal guard before the deployed Build.

Current Redux ordnance receiver `00584620`, independently identified by its
Build call, `(source, ordid)` assignment and dispatches from `00570500` (RO and
bundled ordnance), contains this ordering:

```text
find existing ordnance or Build it
existing: overwrite transform/velocity, unpack class state
recompute catch-up dt from packet time
while dt > 0.05:
    subtract 0.05
    Control virtual
    Simulate virtual
    only now test removal via 00583dc0 (object flags & 0x200)
bSend = 0
```

Thus a correction received while an already-planted bomb is still in the
ordnance map can dispatch another simulation step despite its removal flag.
If the corrected step contacts terrain at planting speed, Hit builds another
SprayBuilding for that logical bomb. The first producer is not undone by the
transform correction. This is a concrete **conditional** duplicate-parent path,
not owner producer plus network-replicated producer or transmitted child payload.
Its trigger still needs a trace showing the marked bomb remains mapped when
the later record arrives, dt exceeds 0.05, and the second Hit plants. A duplicate
stream once per peer is not established by this path; one independent producer
on each peer alone does not multiply the streams seen on a single machine.

**Decision:** no code change. Both receiver paths are materially stronger
explanations than the rejected payload-broadcast/common-guard hypotheses, but
neither packet/lifetime sequence has been observed in the reported match. The
decisive Daywrecker trace is repeated wire ID with a new construction/lifetime
and consumed-byte reset; the decisive Splinter trace is a second planting Hit
for the same `(source, ordid)` during receive catch-up. These are different
transport paths and are not yet one proven shared defect.

## Remaining two-PC qualification

- Splinter: correlate parent `(source, ordid)` send/receive, one deployed producer
  per peer, child build counts and `bSend`, and verify zero child send/receive
  records. Compare target ownership and health deltas; distinguish dead-producer
  behavior from timing/random-state/collision divergence.
- Daywrecker: correlate each object lifetime, local ID, peer and event sequence
  across contact, deployed simulation, explosion, removal and received deletion.
  Measure crater calls and buffer before/after **within each peer**. Determine
  whether repeated simulation or a later lifecycle event actually repeats effects,
  and which configured explosion applies damage. Preserve one required terrain /
  presentation update per peer.
- No two-PC run or runtime launch was performed. Windows/GOG, Windows/Steam,
  Linux/Steam/Proton and Linux/GOG/Wine behavior remains unverified for these
  hypotheses. Obtain tester validation before any future authority release.

## Instrumentation — MPAUTH receiver replay traces (2026-09-04 implementation)

Branch `agent/mp-explosive-authority` now includes opt-in diagnostic hooks that
emit `MPAUTH_*` lines without gameplay change. No authority patch is shipped;
these traces make the next occurrence self-proving.

**Enable (opt-in, cheap enough to leave enabled during qualification):**
```ini
[Diagnostics]
TraceMpauth=1          ; or TraceMpauthDw=1 / TraceMpauthSpl=1
; budgets (default 256, max 4096)
; TraceMpauthDwBudget=256
; TraceMpauthSplBudget=256
```
Env overrides: `OPENSHIM_TRACE_MPAUTH=1` / `BZR_TRACE_MPAUTH=1` (and
`_DW` / `_SPL` suffixes), plus `*_BUDGET` variants. Hooks validate expected
prologue bytes at `0x004B0460`, `0x004B07D0`, `0x004DAE70`, `0x004B7F20`,
`0x00584620`, `0x005DB080`, `0x004E7D30`, `0x004B8590`, `0x004B8FA0` before
installing; mismatch logs and fails closed. **Binary coverage:** GOG Redux
2.2.301 (`8d71f56c...`) is qualified; Steam addresses are identical after
SteamStub `.bind` decrypts `.text` in place for the listed sites, but have not
been re-validated in this pass — treat Steam as `not yet qualified` and rely
on fail-closed prologue checks.

**Daywrecker (wire-ID lifetime):**
```text
[MPAUTH_DW_DETONATE] sim/explode  peer=host|client netId=0xXXXX id=0xXXXXXXXX ptr=0xXXXXXXXX consumed_before=0|1 type=...
MPAUTH_DW_DETONATE peer=host id=0xXXXXXXXX ptr=0xXXXXXXXX consumed_before=0
[MPAUTH_DW_REMOVE]  peer=... netId=... id=... ptr=... type=... act=... deleted_record=0|1
MPAUTH_DW_REMOVE peer=... id=... ptr=... deleted_record=0
[MPAUTH_DW_RX]      peer=... netId=... id=... ptr=... lookup=MISS deleted_record=0|1 route=ordinary|permanent
MPAUTH_DW_RX peer=... id=... lookup=MISS deleted_record=0 route=ordinary
[MPAUTH_DW_CREATE]  peer=... netId=... id=... ptr=... type=...->... revived=0|1
MPAUTH_DW_CREATE peer=... id=... ptr=... revived=1
```
`deleted_record` is 1 for local type 1 or remote type 2 with `id < 0x10000`
(the `004B7BD0` path). `revived` is 1 when a `CREATE` reuses an ID that was
recently `REMOVE`d (within the same map). `MPAUTH_DW_RX` is emitted from the
Redux ordinary-state reader `0x004B8590` (`route=ordinary`) and permanent-state
reader `0x004B8FA0` (`route=permanent`) only when the incoming ID matches a
recently removed Daywrecker — proving which receiver path caused the recreation.
Without `RX`, `REMOVE -> CREATE` still proves same-ID new lifetime (very
strong), but `RX` makes the receive edge indisputable. The decisive Daywrecker
trace is:
`detonate X/ptr A -> remove X -> RX X lookup=MISS route=ordinary -> create X/ptr B revived=1 -> detonate X/ptr B`.

**Splinter (ordnance (source,ordid)):**
```text
[MPAUTH_SPL_RX]  peer=... netId=... sender=... packet=... len=... found=existing|new|unknown
MPAUTH_SPL_RX peer=... source=... ordid=... ptr=... flags=... dt=... found=existing
[MPAUTH_SPL_SIM] peer=... netId=... source=... ordid=... ptr=... flags_before=... dt=... bSend=...
MPAUTH_SPL_SIM peer=... source=... ordid=... ptr=... flags_before=...
[MPAUTH_SPL_HIT] peer=... netId=... source=... ordid=... ptr=... flags=... bSend=... dt=... build_count=N inRecv=0|1
MPAUTH_SPL_HIT peer=... source=... ordid=... ptr=... build_count=2
```
`SIM` is emitted only when `g_MpauthInOrdnanceReceive` is true (catch-up loop
inside `00584620`). `HIT` counts per `(source,ordid)` key with `ptr` included
for disambiguation; `build_count=2` for the same key during `inRecv=1` is the
decisive Splinter trace:
`Hit(A,42)->producer#1 ... receive(A,42) flags=O200 found=existing ... catch-up Simulate -> Hit(A,42)->producer#2`.
`RX` now exposes `found=existing|new` (heuristic via `g_MpauthSplHitCounts`;
`unknown` if no prior Hit). `ptr` in `HIT` makes `(source,ordid)` reuse over a
very long session diagnosable. Hit map is cleared on session/map reset
(`ResolveBzrHooks`) and bounded at 1024 entries (clears with log) to avoid
unbounded growth.

All hooks use `__try/__except` and `InterlockedDecrement` budgets; they never
change simulation, terrain, or network traffic. `BZRHarness.ps1` can grep for
`MPAUTH_*` and correlate `id` / `(source,ordid)` across host/client logs.

## Validation

- `msbuild BZROpenShim.sln /p:Configuration=Release /p:Platform=Win32`: passed (2026-09-04 rebuild with MPAUTH instrumentation, warnings only for unused helper).
- Normal Win32 CMake configuration is blocked by pre-existing duplicate
  `player_kill_trace_tests` target/test declarations in `tests/CMakeLists.txt`
  (lines 258 and 267). Left unchanged, per task scope.
- Fresh Release Win32 `resolve_table_tests` and `bzrnet_protocol_tests`: 2/2
  passed, compiled with `/W4 /WX`; both PE machine fields verified as `0x014C`.
  A scratch CMake project selected only the existing test/source files and defined
  `BZR_PATCHES_JSON` to the shipped file, bypassing the unrelated configuration
  failure without modifying the repository harness. No new tests were written.
- Existing x64 `resolve_table_tests` and `bzrnet_protocol_tests`: 2/2 passed;
  these pre-existing binaries are not counted as Win32 validation.
- No gameplay authority or shipped patterns changed. Pre-existing player-kill changes
  and staged Splinter research were preserved; MPAUTH instrumentation is opt-in
  and fails closed on byte mismatch. No deployment or publication.

## Completion pass (2026-09-05)

The instrumentation above was left mid-flight. This pass finished it and
qualified it for shipping; it did **not** revisit any authority conclusion.
Splinter and Daywrecker still carry no patch, for the reasons recorded above.

### Defects found and fixed

| # | Defect | Effect |
| --- | --- | --- |
| 1 | `player_kill_trace_tests` was declared twice in `tests/CMakeLists.txt` | CMake configure failed outright, so the Linux CI job and every local Win32 test configure were dead. Recorded above as "left unchanged, per task scope". |
| 2 | `GetNetPlayerIdForTeam` read the id at `+312` | Wrong offset. `DumpMultiplayerFlagDiagnosticsOnce` has always read this field at `+0x28`, and the source comment was an unresolved note asking which to use. Every `netPlayerId` was garbage, so `human-by-activnet` -- the hypothesis the whole trace exists to test -- could essentially never fire. |
| 3 | Research fields were populated only under `HasEventSubscribers()` | With the trace on but no event subscriber, `victimTeam`, `damagerTeam` and `damageSequence` stayed zero, so correlation degraded to `likely`/`absent` for every death. The trace is now its own consumer. |
| 4 | Multi-attacker detection counted the wrong rows | It counted pending entries sharing the victim's *team* while excluding the victim -- i.e. other victims. Any teammate taking fire within 2 s downgraded a clean attribution to `ambiguous-multi`. The table holds one slot per victim, so the intended signal was not derivable from it at all; the slot now counts damager changeovers directly. |
| 5 | `TraceNetPlayerRecordDeath` decremented the trace budget, then `LogAuthoritativeDeathResearch` decremented it again | That path burned the 256-record budget at twice the rate, truncating captures early. |
| 6 | `[Diagnostics] TracePlayerKills` was read but never shipped in `openshim.ini` | The code comment says it mirrors `TraceDamageReveal`; the ini entry was missing, so the documented way to enable it did not exist. |
| 7 | Dead code | `sourceHandle` was declared and never assigned; `victimClass`/`killerClass` were always `nullptr` and printed `?`; `kMpauthObjFlagsOffset` was unused; `kMpauthOrdnanceObjOffset` and `kObjFlagsOffset` duplicated `kOrdnanceObjOffset` and the existing `kObjStateFlagsOffset`. The record now carries `dmgSeq`, which the table already tracked and nothing reported. |

The `0x009180E8` NetPlayer table was also being written as a bare literal in
two new call sites while `kNetPlayerByTeamAddr` already held it.

### Test posture

The two pure decisions -- controller classification and damage->death
correlation -- moved into `include/player_kill_trace.h`, so the trace and its
tests read one implementation instead of two copies.

The previous `tests/player_kill_trace_tests.cpp` was **vacuous under CI**: it
asserted through `<cassert>`, and both CI test jobs build `--config Release`,
which defines `NDEBUG` and compiles every assertion away. Several of its cases
also asserted on locally declared literals that never touched product code. It
now follows the `Require`-and-count convention the rest of the suite uses, and
was verified to fail: reintroducing defect 4's ordering mistake in the header
produced 2 failures and a non-zero exit.

### Validation

- `msbuild BZROpenShim.sln /p:Configuration=Release /p:Platform=Win32`: succeeded, no new warnings in the trace region.
- `cmake -S tests -B build/pktests -A Win32` now configures (defect 1).
- Full CTest suite, Release Win32: **22/22 passed**, including the rewritten `player_kill_trace_tests`.
- `tools/validate-network-baseline.ps1`: passed.
- `scripts/run_ini_tests.ps1`: passed, 127 settings, conservative defaults intact.

### Shipping posture

Off by default. `InstallDistributedRecordDeathIntHookIfPossible`,
`InstallSetAsUserHooksIfPossible` and `InstallMpauthHooksIfPossible` all return
early unless the feature is enabled, so with the key absent no detour is
written at any address. Byte-signature validation still fails closed.

The one change on an always-live path is the pending-victim slot now counting
damager changeovers. Last-damager-wins attribution is byte-for-byte unchanged;
career statistics and scoring are untouched.

**Still not qualified:** no live two-peer capture has been taken, so the
`activnet_id == NetPlayer id` hypothesis remains untested against real
multiplayer traffic. That is what the instrument is for, and it is the next
step -- not something this pass claims to have settled.

### Defect 8: the SetAsUser / SetAsNotUser probe could never install

Found by validating the byte guards against the shipped GOG executable
instead of trusting them, after the primary hook was confirmed good.

| Address | Bytes in the shipped exe | Verdict |
| --- | --- | --- |
| `0x006796D0` `DistributedObject::RecordDeath(int)` | `55 8B EC 51 89 4D FC 8B` | **matches** the expected `55 8B EC` prologue; this hook installs |
| `0x00495468` `SetAsUser` | `FD FF FF C7 85 7C FE FF` | not a function entry |
| `0x004954D7` `SetAsNotUser` | `FE FF FF 01 00 00 00 EB` | not a function entry |

Both SetAsUser addresses land mid-instruction. `FD FF FF` is the tail of a
negative displacement, and what follows at `0x00495468` decodes as
`mov dword ptr [ebp-0x184], 0` -- a local-variable store deep inside some
larger routine. Scanning backwards from each address finds no `55 8B EC`
preceded by padding or a return within `0x800` bytes, so neither is near a
function entry at all. They have the shape of a `.text` reference scan that
landed on an operand rather than on the instruction that owns it.

The prologue guard did its job and refused to detour, so nothing crashed.
But the caller re-invoked the installer from the sim tick on every frame for
as long as the trace was on, because the retry had no latch: each frame paid
two `ExpectedBytesMatchAt` calls, two guarded `memcpy`s and two log lines,
forever. That is the same shape as the lazy-resolve-in-a-per-frame-loop
defect that previously cost a large slice of the main thread.

The probe was removed rather than latched. Latching would have left a
permanently inert code path that reads as working, and the addresses cannot
be repaired by inspection -- recovering the real entry points is genuine RE
work, not an off-by-a-few-bytes correction. The intent (observe the moment an
object becomes, or stops being, the local user) is worth reviving once the
functions are actually identified; identify them from the function body, not
from a byte signature, since a unique prologue is not proof of identity.

What remains is the part that was verified against the real binary: the
`RecordDeath(int)` death trace and the controller/correlation classification.

### Live smoke test (GOG, 2026-09-05)

1.0.0.15 deployed to the GOG install and launched three times.

- Default (trace absent): loads to the main menu, OpenShim initialises, renderer resources verify, **zero** `ERROR`/`WARN`, **zero** `PKTRACE` lines -- confirming no hook is written when the feature is off.
- With `OPENSHIM_TRACE_PLAYER_KILLS=1`: arms and reports `[PKTRACE] Player-kill trace enabled budget=256`. The death hooks install from the sim tick, so a main-menu run cannot exercise them; the byte-guard table above is what stands in for that until a mission run is captured.
- The first run surfaced two `RESOLVE` warnings for `MPVehicleList::LoadCallSite*`. That was a stale `scripts/patches.json` in the game root (19 KB, dated 2026-08-31) rather than a code defect -- the repository and the shipped payload both carry the current 30 KB file. Refreshing the test install cleared it, and the final run is clean.
