# WeaponMine hop-out friendly-fire: root-cause investigation (2026-08-17)

Supersedes `weaponmine_hop_friendly_fire_20260714.md`, whose central WeaponMine claim is disproved below.

> **Scope correction, 2026-08-27:** this report proves the WeaponMine hostility
> path, the hop-out radar alert, capture-side `perceivedTeam` lifecycle, and the
> inspected attacker-reveal writers. It does **not** prove parity in the separate
> victim-AI response to incoming fire while disguised. Scott ("Herp") reported
> that an AI-controlled captured craft, `turrettank`, or `turret` can fail to
> break cover/retaliate when attacked by the team it is perceived as belonging
> to, while sniper aggression behaves differently. That victim retaliation path
> remains open and is tracked in `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md`.

## 0. Headline

**There is no Redux regression in the WeaponMine hostility path examined here.**
Mine target acquisition, the mine hostility predicate, the pilot-exit transition,
and the under-attack radar alert are semantically identical between Battlezone
1.5 and the shipped Redux executable.

Two corrections to the older investigation are firm:

1. **WeaponMine does not read `perceivedTeam`.** In both builds its hostility
   test resolves to the target's *actual* team through virtual slot 1
   (`GameObject::GetTeam`). `Craft::AbandonPilot` writing
   `SetPerceivedTeam(craft, 0)` cannot alter that predicate.
2. **The hop-out beep does not prove friendly-mine hostility.** It is the stock
   cockpit radar "friendly under attack" alert. Hopping out changes
   `userObject`, making the craft you just left eligible to replay its most
   recent `enemyShot` timestamp once. The same logic exists in 1.5.

The former OpenShim **WeaponMine Hop-Out Friendly-Fire Fix** was therefore based
on a disproved mechanism and was removed. This conclusion does not settle the
separate AI-retaliation complaint described above.

## 1. Corpora and provenance

| Role | Artefact |
| --- | --- |
| Behavioural reference | `bzone.exe` + exact-match `bzint.pdb` (15,070 symbols), `C:\Program Files (x86)\Battlezone` |
| Authoritative target | `battlezone98redux.exe`, GOG, SHA-256 `8d71f56c…3377413` |
| Support | `repo_corpora/bzr_gog_best_effort` decomps (31,948 functions) |

Redux addresses were read from the shipped executable with `pefile` +
`capstone`, not trusted from the advisory PDB.

## 2. Verified relevant field layout

Redux `GameObject` is 1.5's relevant layout shifted by **+0x0C**.

| Field | 1.5 | Redux | Redux evidence |
| --- | --- | --- | --- |
| team (actual) | +0x168 | **+0x174** | virtual `GetTeam` rebased from subobject+0x15C |
| group index | +0x16C | +0x178 | positional |
| `teamList` | +0x170 | **+0x17C** | `FriendP(int)` |
| `perceivedTeam` | +0x174 | **+0x180** | save walker + `SetPerceivedTeam` |
| `enemyShot` | — | **+0x1E8** | save walker/getter |

The multiple-inheritance detail that caused the older mistake is important:
`DistributedObject` sits at base+0x20 in 1.5 and base+0x18 in Redux. Virtual
team accessors operate on that subobject, so their operand offsets must be
rebased before comparison with non-virtual accessors.

## 3. WeaponMine hostility predicate

```text
WeaponMine::Simulate
  -> for each craft
     -> GameObject::FriendP(mine, craft)
        -> craft->vtbl[1]()                 ; GameObject::GetTeam -> ACTUAL team
        -> mine->teamList->FriendP(team)
```

| Function | 1.5 | Redux |
| --- | --- | --- |
| `WeaponMine::Simulate` | `0x0053F9CF` | `0x00612950` |
| `GameObject::FriendP(GameObject*)` | `0x00496C40` | `0x004DB510` |
| `GameObject::FriendP(int)` | `0x00495321` | `0x004DB560` |
| `Team::FriendP` | `0x004B1CBD` | `0x005E1310` |
| virtual slot 1 = `GetTeam` | `0x0047BD02` | `0x00462450` |

`GameObject::GetPerceivedTeam` (Redux `0x004625B0`, base+0x180) is non-virtual
and is not reached by this mine predicate.

`Team::FriendP` rejects team 0 in both builds. Therefore the former patch's
special treatment of team-0 craft was a legacy divergence, not a restoration.

## 4. Pilot exit does not alter the mine relation

`Craft::AbandonPilot` was read in full in both builds. Both clear/release pilot
state, build the on-foot pilot, and finally set the abandoned craft's
`perceivedTeam` to 0. Neither build writes the craft's actual team or `teamList`
and neither calls `SetTeam` on the abandoned craft.

Therefore WeaponMine's actual-team relation is unchanged across hop-out in both
1.5 and Redux.

## 5. Hop-out radar alert

Two damage/audio mechanisms were distinguished:

- `BettyVoice::AttackWarning`, reached from `SetDamageFlags` on current enemy
  damage;
- the cockpit radar alert, which scans friendly objects and warns when an
  object's stored `enemyShot` timestamp is newer than the alert cooldown and the
  object is not the current `userObject`.

The latter explains the reported one-time hop-out growl:

```text
player drives craft C           -> userObject == C -> C excluded
C takes enemy damage at time T  -> enemyShot = T
player hops out                 -> userObject becomes pilot
next radar frame                -> C now eligible -> one warning
```

This behavior is present in 1.5 and Redux.

## 6. Former WeaponMine guard

The former `WeaponMineFriendPGuard` redirected the mine's `FriendP` call and was
premised on vtable slot 1 returning perceived team. It actually returned actual
team.

Its effective extra behavior was only to spare some team-0 craft. That behavior
contradicted the demonstrated stock `Team::FriendP` rule and did not affect the
reported abandoned allied craft case.

The guard was removed on 2026-08-17. No replacement mine patch is warranted for
this path.

## 7. `perceivedTeam` lifecycle findings

Capture itself is a deliberate disguise in both builds:

```text
oldTeam = craft->GetTeam()
craft->SetTeam(person->team)
...attach pilot / AI...
craft->SetPerceivedTeam(oldTeam)
```

A stolen craft is supposed to continue looking like the previous owner's team
until stock reveal rules change that state.

The inspected writer set matches between 1.5 and Redux:

| Writer | 1.5 | Redux |
| --- | --- | --- |
| `Craft::AbandonPilot` -> 0 | `0x00488EA3` | `FUN_004ADF20` |
| `Craft::ExplodePilot` | `0x00488BDB` | `FUN_004AD700` |
| capture -> old team | `0x004A6F1F` | `FUN_005A1550` |
| `SetDamageFlags` -> damager actual team | direct store | `0x004DC29F` |
| `OffensiveProcess::DoSubTask` | `0x0044DFA1` | `0x00583690` |
| `TurretTankProcess::DoSubTask` | `0x00467B88` | `0x005F7143` |
| Lua/global setter | `0x0045EEF9` | `FUN_005C88B0` |

The two inspected DoSubTask sites reveal `GameObject::userObject` rather than
establishing a generic "reveal the attacking AI owner when it engages" rule.
The inspected stock path that reveals the *damager* is `SetDamageFlags`, which
requires landed damage.

This is why OpenShim's experimental "reveal process owner on engagement" hook
was correctly reclassified as an **enhancement**, not a demonstrated 1.5
compatibility restoration. Those attack-reveal hooks are quarantined/removed
from production registration.

## 8. What this report proves — and what it does not

**Proven here:**

- WeaponMine hostility consumes actual team, not `perceivedTeam`;
- hop-out does not alter the actual-team relation used by WeaponMine;
- the one-time hop-out radar warning exists in 1.5 and Redux;
- capture-side disguise semantics and the inspected `perceivedTeam` writer set
  match between the compared builds;
- the former WeaponMine guard was not a valid compatibility fix.

**Not proven here:**

- whether a disguised AI victim correctly classifies incoming damage;
- whether that victim acquires/retains a target after normal cannon fire;
- whether `OffensiveProcess`, `TurretTankProcess`, or gun-tower retaliation
  transitions differ between 1.5 and Redux on the *victim* side;
- why sniper aggression reportedly breaks the bad state;
- whether the CCA mission 7 gun-tower symptom has the same first divergence as
  stolen AI craft.

Those are now a dedicated regression investigation. See
`Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md`.

## 9. Regression requirements for future mine/team changes

Preserve all of the following unless separate legacy evidence proves otherwise:

- WeaponMine relation remains based on actual team;
- capture and `SetTeamNum` update actual-team relation independently of
  `SetPerceivedTeam`;
- multiplayer remote mine instances do not become accidental authorities;
- Lua `SetTeamNum` and `SetPerceivedTeam` remain semantically distinct;
- no attack-reveal enhancement is presented as a 1.5 compatibility fix without
  a proven legacy consumer.

## 10. Confidence

| Claim | Confidence | Basis |
| --- | --- | --- |
| Mine hostility reads actual team in both builds | **Very high** | Both chains disassembled end-to-end |
| `AbandonPilot` leaves actual craft team unchanged | **Very high** | Full function read in both builds |
| Hop-out beep is radar `userObject` masking and exists in 1.5 | **High** | Guard/getter/initialiser traced |
| Former WeaponMine guard was inert in the reported hop-out case | **High** | Follows from predicate + exit transition |
| Capture-side `perceivedTeam` writer set matches | **High** | Compared writers in both builds |
| Victim AI retaliation while disguised matches 1.5 | **Not established** | Separate consumer/path; dedicated trace required |
