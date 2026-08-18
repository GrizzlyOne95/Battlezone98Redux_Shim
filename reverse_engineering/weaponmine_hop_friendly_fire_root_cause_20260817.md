# WeaponMine hop-out friendly-fire: root-cause investigation (2026-08-17)

Supersedes `weaponmine_hop_friendly_fire_20260714.md`, whose central claim is
disproved below.

## 0. Headline

**There is no Redux regression in the WeaponMine hostility path.** Every link in
the chain — mine target acquisition, the hostility predicate, the pilot-exit
transition, the damage classifier, and the under-attack alert — is semantically
identical between Battlezone 1.5 and the shipped Redux executable.

Two specific corrections to the prior investigation:

1. **The mine does not read `perceivedTeam`.** In both builds the hostility test
   resolves to the *actual* team field. `Craft::AbandonPilot`'s
   `SetPerceivedTeam(craft, 0)` is therefore invisible to WeaponMine. The
   2026-07-14 note assumed virtual slot 1 was the perceived-team getter; it is
   `GameObject::GetTeam`, which reads a different field.
2. **The hop-out beep is fully explained without any hostility bug**, and it is
   stock behaviour present in 1.5. It is the cockpit radar's "a friendly is
   under attack" alert, which suppresses itself only for the object the player
   currently *is*. Hopping out changes that object, unmasking the craft you just
   left for one beep.

Consequence: the shipped OpenShim patch **WeaponMine Hop-Out Friendly-Fire Fix**
guards a mechanism that does not exist. See §7.

## 1. Corpora and provenance

| Role | Artefact |
| --- | --- |
| Behavioural reference | `bzone.exe` + exact-match `bzint.pdb` (15,070 symbols), `C:\Program Files (x86)\Battlezone` |
| Authoritative target | `battlezone98redux.exe`, GOG, SHA-256 `8d71f56c…3377413` |
| Support | `repo_corpora/bzr_gog_best_effort` decomps (31,948 functions) |

All Redux addresses below were read from the shipped executable with
`pefile`+`capstone`, not from the advisory PDB.

## 2. Verified field layout

Redux `GameObject` is 1.5's layout shifted by **+0x0C**. Three independent
derivations agree:

| Field | 1.5 (base-rel) | Redux (base-rel) | How proven (Redux) |
| --- | --- | --- | --- |
| team (actual) | +0x168 | **+0x174** | virtual `GetTeam` reads subobj+0x15C; subobj is base+0x18 |
| group index | +0x16C | +0x178 | positional |
| `teamList` (`Team*`) | +0x170 | **+0x17C** | `FriendP(int)` reads `[this+0x17C]` at `0x004DB56C` |
| `perceivedTeam` | +0x174 | **+0x180** | save walker pushes literal `"perceivedTeam"` beside `add ecx, 0x180` at `0x004DE7DF` |
| `enemyShot` | — | **+0x1E8** | save walker literal `"enemyShot"`; getter `0x0046D040` is `fld [eax+0x1E8]` |
| `who_shot_JR` | — | +0x1F4 | `SetDamageFlags` at `0x004DC273` |

The multiple-inheritance detail that the prior note missed: the
`DistributedObject` subobject sits at **base+0x20 in 1.5** and **base+0x18 in
Redux**. Virtual team accessors are called on that subobject, so their operand
offsets must be re-based before comparison with non-virtual accessors.

## 3. The hostility predicate — identical in both builds

```
WeaponMine::Simulate
  └─ for each craft in Craft::craftList
       └─ GameObject::FriendP(mine, craft)
            └─ craft->vtbl[1]()            ; GameObject::GetTeam  → ACTUAL team
                 └─ mine->teamList->FriendP(thatTeam)
                      └─ Team::FriendP
```

| | 1.5 | Redux |
| --- | --- | --- |
| `WeaponMine::Simulate` | `0x0053F9CF` | `0x00612950` |
| `GameObject::FriendP(GameObject*)` | `0x00496C40` | `0x004DB510` |
| `GameObject::FriendP(int)` | `0x00495321` | `0x004DB560` |
| `Team::FriendP` | `0x004B1CBD` | `0x005E1310` |
| virtual slot 1 = `GetTeam` | `0x0047BD02` → `[subobj+0x148]` | `0x00462450` → `[subobj+0x15C]` |

`Team::FriendP` in both builds:

```c
if (teamNum < 1 || (this->dwAllies & (1 << (teamNum & 0x1f))) == 0) return false;
return true;
```

**Team 0 is never anyone's friend, by explicit design, in both builds.** This
directly answers the brief's constraint: 1.5 does *not* demonstrate an
allied-owner exclusion for neutral craft, so adding one is a divergence from
legacy, not a restoration of it.

`GameObject::GetPerceivedTeam` (Redux `0x004625B0`, reads base+0x180) appears in
**no vtable** — it is non-virtual and is never reached from the mine. Scanning
`.rdata`, twelve class vtables share the slot layout
`[0]=GetClass [1]=GetTeam(0x00462450) [2]=SetTeam(0x004DB4B0) [3]=GetPosition`,
so slot 1 is `GetTeam` for every craft type a mine can scan.

`ProximityMine::Simulate` (1.5 `0x00536DD5`) uses the same
`GameObject::FriendP(this, craft)`. `MagnetMine::Simulate` and
`FlareMine::Simulate` contain no relation test at all — magnet mines are
indiscriminate in stock 1.5.

## 4. The pilot-exit transition

`Craft::AbandonPilot` — 1.5 `0x00488DB8`, Redux `0x004ADF20` — read in full in
both builds. Ordered writes:

| Step | 1.5 | Redux |
| --- | --- | --- |
| clear pilot class | `this->[pilotClass] = 0` | `[+0xEC] = 0` |
| release attachment | virtual call, then null | `[+0xFC]` virtual call, then null |
| zero controls | 9 floats | `memset([+0x230]+0xC4, 0, 0x2C)` |
| carrier untrigger | `Carrier::UnTriggerAll` | `FUN_004A7800` |
| build pilot | `Craft::BuildPilot` | `FUN_004ADB00` |
| pilot velocity | `SetVelocity` | inline |
| pilot back-ref | `pilot->abandoned = GetHandle(craft)` | `[pilot+0x22C] = GetHandle(craft)` |
| **perceived team** | `SetPerceivedTeam(craft, 0)` | `FUN_004DB4F0(craft, 0)` = same |
| audio | `DoAudioNew("jump.wav", …)` | `FUN_004376C0("jump.wav", …)` |

**Neither build writes the actual team (+0x174), `teamList` (+0x17C), or calls
`SetTeam`/`Init` on the craft.** The empty craft keeps its real team, so the
mine's predicate result is unchanged across the transition — in both builds.

The new pilot is built by `GameObjectClass::Build(class, matrix, craft->team, …)`,
i.e. with the correct team supplied at construction. There is no observable
intermediate state: the engine is single-threaded and `Build` returns fully
initialised, so no mine `Simulate` can run mid-construction.

`Craft::BuildPilot` is 1.5 `0x004866C9`; the pilot also gets
`DistributedObject::SetLocal` under `Net_IsNetGame`, and `AiProcess::Attach`,
in both builds.

## 5. Why the beep happens — and what it proves

Two distinct producers exist. Neither is the mine.

**(a) `BettyVoice::AttackWarning`**, called from `GameObject::SetDamageFlags`
(1.5 `0x00496DA9`, Redux `0x004DC130`) only on the branch that already
classified the hit as enemy damage. Requires damage *at that instant*.

**(b) The cockpit radar alert — this is the hop-out beep.**
1.5 `CockpitRadar::Render`, Redux `FUN_00493EC0` (call site `0x00494D45`,
string `cgrowl.wav` at `0x00877220`):

```c
// 1.5
if ((local_5 != 0) && (this_00 != this->userObj) && (nextBeep < this_00->enemyShot)) {
    StartGASEvent("cgrowl.wav", …);
    nextBeep = this_00->enemyShot + 1.0;
}
```

Redux is the same three conditions, verified term by term:
`local_135 = (obj->vtbl[1]() == radar->myTeam)` (friendly),
`local_134 != *(int**)(local_12c + 0xc)` (`obj != userObj`),
`_DAT_009173D0 < local_1bc` where `local_1bc = FUN_0046D040()` = `[obj+0x1E8]`
= `enemyShot`.

The mechanism:

```
player is driving craft C      → userObj == C → C is excluded from the alert
C is shot by an enemy at time T→ SetDamageFlags: enemyShot = T  (only if EnemyP)
player hops out                → userObj becomes the PILOT
next radar frame               → C is friendly, C != userObj, nextBeep < T
                               → one beep; nextBeep = T + 1.0 suppresses repeats
```

`enemyShot` is initialised to `-1e+30` and is written **only** in the
`EnemyP(this, shooterTeamNibble)` branch of `SetDamageFlags`, so a friendly
mine's damage sets `friendShot`, never `enemyShot`.

Therefore the warning proves **an enemy-attributed damage event occurred on that
object at some earlier moment**, not that damage is occurring now, not that a
target was acquired, and not that any hostility test involving the mine fired.

This behaviour is present in 1.5 verbatim. It is not a regression, and the audio
path is not the defect — consistent with the brief's instruction not to patch it.

## 6. Hypotheses, adjudicated

| Hypothesis | Verdict |
| --- | --- |
| Redux temporarily changes the empty vehicle's team | **False** — no write to +0x174/+0x17C in either build |
| `perceivedTeam` briefly becomes neutral | **True but irrelevant** — both builds do it; nothing in the mine path reads it |
| WeaponMine uses `perceivedTeam` where 1.5 used actual team | **False** — both use actual team via vtable slot 1 |
| Firing-owner relation lost when pilot leaves | **False** — mine relation is mine-team vs candidate-team; no owner link involved |
| Owned-object relation not updated atomically | **Not applicable** — single-threaded; `Build` returns fully initialised |
| Mine retains a stale target and fails to revalidate | **False** — the craft list is rescanned every tick and `SetTarget` is recomputed from scratch |
| Redux changed when target scanning occurs | **False** — both scan inside `WeaponMine::Simulate`, tail-calling `Mine::Simulate` |
| Same defect as the repaired `perceivedTeam`/attacker-reveal behaviour | **False** — `SetDamageFlags` tail sets `damager->SetPerceivedTeam(damager->GetTeam())` in *both* builds. Verified from the disassembly that `ecx` is the damager (`[ebp-8]`), not the victim, at Redux `0x004DC29C` |
| 1.5 has an extra allied-owner exclusion Redux lost | **False, and inverted** — `Team::FriendP` explicitly rejects team 0 in both builds |

## 7. The shipped OpenShim patch

`WeaponMineFriendPGuard` (`src/patches/bzr_hooks.cpp:25630`), installed as a
REL32 redirect of the mine's `FriendP` call at `0x00612A52`, is premised on the
disproved claim. Its comment says it reads "perceived team" via `vtable[1]`;
that call actually returns the **actual** team.

Its real semantics are:

```
stock FriendP(mine, target) ? spare
                            : spare iff target->GetTeam() == 0 && FriendP(target, mine)
```

* In the reported hop-out scenario it is **inert** — the abandoned craft retains
  a non-zero real team, so the added clause never evaluates true.
* Where it is not inert, it spares genuinely team-0 craft that count the mine's
  team as an ally. `Team::FriendP` rejecting `teamNum < 1` is deliberate stock
  behaviour in both builds, so this is a divergence from legacy, which is
  exactly what the brief asked to avoid absent proof that 1.5 intended it.

It is also unconditional: no INI gate, and `patcher.cpp` exempts it from the
usual Steam byte-wait filter.

**Recommendation: remove it.** It cannot fix the reported symptom, and its only
non-inert effect contradicts demonstrated 1.5 behaviour. Removal is a two-line
change (drop the `patches.h`/`patches.json` entries and the `FillRel32Payloads`
branch); the guard function can stay dead or be deleted with it.

No replacement patch is proposed, because no defect was found.

## 8. Discriminating test (no code required)

The §5 model makes a falsifiable prediction. Run both halves:

| Scenario | Prediction |
| --- | --- |
| Start a mission, take **no** enemy fire, hop out | **No beep** (`enemyShot` still `-1e+30`) |
| Take enemy fire, wait for the shooting to stop, then hop out | **Exactly one beep**, immediately on exit |
| Hop out again right away without being shot again | **No beep** (`nextBeep` now exceeds `enemyShot`) |
| Repeat with **no** WeaponMine anywhere on the map | **Beep still occurs** — proves the mine is not involved |

The last row is the decisive one. If the beep survives with no mine present, the
mine hypothesis is dead by observation as well as by static analysis.

If the first row beeps, or the fourth does not, the model is wrong and a probe
is warranted — log `team`, `perceivedTeam`, `enemyShot`, and the global
`nextBeep` (`0x009173D0`) for the craft across the hop, which is four reads at
one site rather than instrumenting the object system.

## 9. Regression matrix (for any future change here)

Preserve: enemy craft targetable; captured/`SetTeamNum` craft become hostile;
mines still fire after their owner dies (the relation is mine-team based, not
owner based, so this is unaffected by construction); MP ownership — remote
instances skip `WeaponMine::Simulate` via `DistributedObject::IsRemote` at the
top of the function, so only the authoritative side matters; Lua `SetTeamNum`
and `SetPerceivedTeam` remain distinct and only the former can affect mines.

## 10. Confidence

| Claim | Confidence | Basis |
| --- | --- | --- |
| Mine hostility reads actual team, not `perceivedTeam`, in both builds | **Very high** | Disassembled both chains end to end; three independent offset derivations |
| `AbandonPilot` does not alter the actual team in either build | **Very high** | Full function read in both builds |
| Beep is the radar `userObj`-masking alert, identical in 1.5 | **High** | Guard verified term by term; `enemyShot` getter and initialiser confirmed |
| The user's specific observed beep is that alert | **Medium-high** | Static model fits the symptom exactly; not yet confirmed live — see §8 |
| Shipped patch is inert in the hop-out case | **High** | Follows from the first two claims |
| Lua swap converges on the same fact | **Medium** | Lua exposes `SetTeamNum` and `SetPerceivedTeam` separately; only the former reaches the mine. Individual swap scripts not audited |

## 11. Not established

* No live/runtime validation was performed.
* Steam-build VAs assumed to match GOG, per existing OpenShim convention.
* Specific community Lua swap scripts were not read; the claim is about which
  engine API can affect mine hostility, not about what any given script does.
