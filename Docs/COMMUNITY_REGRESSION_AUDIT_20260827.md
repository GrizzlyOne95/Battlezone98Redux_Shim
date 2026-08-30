# Battlezone 98 Redux Community Regression Audit

**Date:** 2026-08-27  
**Scope:** OpenShim / Extra Utilities / BZRNet preservation work  
**Primary compatibility reference:** Battlezone 1.5 behavior where historical parity is required

## Purpose

This document turns a detailed long-running community bug report into a durable regression backlog for OpenShim. It preserves the exact reported symptom, separates reports from later reverse-engineering conclusions, and defines a reproducible acceptance test for anything not already closed.

The immediate community source is **Scott ("Herp")** — the same person behind the Herp McDerperson Steam review, later forum/workshop reports, and the detailed technical grievance correspondence supplied on 2026-08-27. Those are one source stream, not independent corroboration.

Only technical bug descriptions and public-facing references are retained here. Personal/off-record material from the correspondence is intentionally not committed.

Public references:

- Steam review: https://steamcommunity.com/id/herpmcderperson/recommended/301650/
- Historical Pastebin mirror/context: https://pastebin.com/FvtY5eZW
- Destruction comparison videos:
  - https://youtu.be/Rt7EmTzTC-4?t=84
  - https://youtu.be/zVrRj4_pNxc?t=182
- Day Wrecker multiplayer demonstration: https://youtu.be/dhyWp3TDe-k
- Historical `Inst4XMission` Lua workaround: https://pastebin.com/ue5Z8sbq
- Public CCA mission 7 / perceived-team discussion: https://steamcommunity.com/app/301650/discussions/0/2292842508246127032/

A broader official-patch/community-source sweep is maintained separately in:

`Docs/REDUX_HISTORICAL_REGRESSION_SWEEP_20260827.md`

That file adds official launch known issues, historical patch invariants, the old Popgun MP duplication fix, Great Pyramid smoothing history, and additional regression candidates.

## Status legend

| Status | Meaning |
| --- | --- |
| **FIXED** | Reproduced/understood sufficiently and a production compatibility fix exists. |
| **FIXED / CONFIGURABLE** | Fixed with an explicit policy switch where preserving both behaviors is useful. |
| **PARTIAL** | Major contributing defects are fixed/understood but the broad historical complaint cannot be declared fully closed. |
| **OPEN - REPRO NEEDED** | Specific enough to test; failing native path not yet captured. |
| **OPEN - RE NEEDED** | Reproduction is understood; producer/consumer still needs reverse engineering. |
| **TODO - FEATURE RESTORATION** | Missing 1.5 functionality rather than a crash/correctness regression. |
| **CONTENT FOLLOW-UP** | Mission/asset/content issue unless a native engine cause is proven. |

---

# 1. Regression status matrix

| Historical complaint | Current status | Current assessment |
| --- | --- | --- |
| Destroyed ships still fragment physically but chunks are invisible | **FIXED** | OpenShim restored physical destruction-chunk rendering and later hardened/optimized the proxy/batching/lifetime path. |
| Jump-sniping is easier/exploitable because holding jump with sniper deployed bypasses the 1.5 landing restriction | **FIXED / CONFIGURABLE** | 1.5-style jump-snipe landing/crouch behavior is implemented; single-player policy remains configurable. |
| Satellite/SkyEye visually reveals enemies outside radar/illumination coverage | **FIXED / CONFIGURABLE** | Redux lost the 1.5 overview illumination gate; OpenShim restores it while preserving independent hidden-state owners. |
| Multiplayer Armory/SLF Day Wrecker can create extra damaging source-site detonations for remote peers | **OPEN - RE NEEDED; HIGH PRIORITY** | Exact host/client asymmetry and two-PC matrix below. Historical 2.0.131 Popgun duplication fix is now a research lead. |
| AI-controlled captured/disguised units with `perceivedTeam` matching the attacker may fail to break cover/defend themselves | **OPEN - REPRO/RE NEEDED; REOPENED** | Capture/disguise writer parity is proven. Victim-side incoming-damage -> aggression/retaliation parity is not. |
| Red Odyssey port contains mission-specific regressions (`BDMISN08`, `BDMISN11`, `CHMISN05`) | **CONTENT FOLLOW-UP** | Audit Scott/Herp's public mission fixes and promote only proven native causes. |
| Multiplayer lacks 1.5 `All Nations` host option | **TODO - FEATURE RESTORATION** | Restore actual match rule/network state before UI. |
| Multiplayer lacks 1.5 `Cloak Disabled` host option | **TODO - FEATURE RESTORATION** | Restore actual match rule/network state before UI. |
| Steam MP map list jumps/resets while browsing | **FIXED** | Steam-specific map-list selection/refresh path repaired. |
| Redux netcode disconnects/rate-collapses more easily than 1.5 | **PARTIAL** | Full live `[Net]` writes, telemetry, governor hardening, relay/protocol RE, and dedicated-server work exist; controlled loss/reorder qualification still required. |
| No independent direct/LAN service path if Rebellion BZRNet disappears | **PARTIAL / ACTIVE PRESERVATION** | Community BZRNet replacement is advanced; player-facing service selection/failover/local-host UX remains. |
| Random crashes/segfaults occur frequently | **PARTIAL / ONGOING** | Many signatures fixed; keep crash work signature-based rather than claiming a global fix. |
| Native `Inst4XMission` save-load crashes frequently | **FIXED** | Save/load lifecycle hardening closes the reproduced stale-handle/object-pool failure without mission Lua conversion. |
| CLI options requiring more than one parameter break due to delimiter parsing | **OPEN - RE NEEDED** | Early destructive Redux tokenization is proven; exact multi-parameter failure still needs parser/handler parity trace. |
| Default HGT smoothing alters terrain/pathing, including stock converted maps | **OPEN - COMPATIBILITY RESTORATION** | Split into future HGT conversion policy and reconstruction/validation of already-shipped stock HG2. Great Pyramid is now the canonical first control. |

---

# 2. Closed items that remain permanent regression tests

## 2.1 Physical destruction chunks

Historical symptom:

- native fragment objects continued to simulate;
- secondary impacts/explosions still occurred;
- rendered model pieces were missing;
- stock craft such as the Grizzly should visibly break into authored pieces.

Acceptance:

1. Destroy stock multi-piece craft/buildings.
2. Verify fragment render proxies follow native trajectories.
3. Verify custom/authored chunk payload selection remains correct.
4. Repeat across in-process mission changes to catch stale Ogre resource/proxy state.

## 2.2 Jump-sniping

Compatibility acceptance:

- 1.5 mode reproduces the landing/fixed-in-place constraint;
- disabling compatibility remains possible in single-player where explicitly desired;
- multiplayer must not silently create client-side competitive rule divergence.

## 2.3 Satellite/SkyEye fog of war

Keep the dedicated satellite fixture:

- friendly/near -> visible;
- detected/illuminated enemy -> visible;
- undetected/unilluminated enemy -> hidden;
- pre-hidden entity -> remains hidden;
- reveal while satellite remains open -> becomes visible;
- create/destroy while satellite open -> no stale state.

See `Docs/SATELLITE_VISIBILITY_FIX_PLAN.md`.

## 2.4 Steam map-list reset

Keep a long Workshop map list and repeatedly select/preview entries far from index zero. Exercise the Steam-specific delayed-resolution path, not only GOG.

## 2.5 `Inst4XMission` save/load

Repeatedly save/load classic non-Lua Instant Action missions without stale-handle crashes. Mission authors must not need to replace native mission classes with Lua merely for save reliability.

---

# 3. High-priority open investigation: Armory / Day Wrecker MP duplication

## 3.1 Reported symptom

Launching machine:

- sees the legitimate launched Day Wrecker;
- may not see any extra source-site explosion;
- receives no damage from the phantom source-site detonation.

Remote machine(s):

- receive the legitimate projectile/explosion behavior;
- can additionally receive a Day Wrecker-class explosion at/near the source Armory;
- that extra damage can destroy remote units/pilots while the launcher is unaffected.

Two launches aimed at the Armory can create legitimate projectile collision plus one or more erroneous remote-only source detonations, producing reported triple/quadruple effective damage.

Treat this as **authority/replication correctness until proven otherwise**, not balance.

## 3.2 Historical lead: Popgun duplication

Patch 2.0.131 explicitly fixed **Popgun duplicating in multiplayer**. See:

https://patch.ali213.net/showpatch/56329.html

This is the strongest new lead from the historical sweep. If pre-2.0.131 and 2.0.131 executables/depots can be obtained, diff the Popper/secondary-ordnance/network-create path before inventing a new authority scheme for Day Wrecker or Splinter.

## 3.3 Required two-PC matrix

| Case | Launcher | Target | Purpose |
| --- | --- | --- | --- |
| DW-1 | Host | distant ground | host-authority baseline |
| DW-2 | Client | distant ground | remote-owner baseline |
| DW-3 | Host | own Armory | source-site/collision stress |
| DW-4 | Client | own Armory | remote-owner + source-site stress |
| DW-5 | Host | own Armory, two timed launches | legitimate double collision vs phantom damage |
| DW-6 | Client | own Armory, two timed launches | worst-case remote duplication |

Repeat enough times to measure the inconsistent trigger.

## 3.4 Instrumentation minimum

On both machines record:

- monotonic timestamp/frame;
- host/client role;
- object handle/distributed identity;
- ODF/class;
- actual/perceived team;
- locality/ownership;
- creator/source;
- initial transform/velocity;
- destruction reason;
- explosion class/position;
- damager/source/victim/damage amount;
- relevant network message/opcode/sequence when available.

Do **not** use `SetLocal` as an investigative shortcut; it can itself change/break multiplayer AI/ownership behavior.

Acceptance: one launch must produce one authoritative projectile/explosion chain and damage parity on all peers in both host- and client-launch cases.

---

# 4. Reopened: `perceivedTeam` victim AI retaliation / break-cover

## 4.1 What existing RE actually proved

`reverse_engineering/weaponmine_hop_friendly_fire_root_cause_20260817.md` proves:

- captured craft intentionally retain the previous owner's `perceivedTeam`;
- inspected capture-side writers match 1.5;
- `SetTeam` and `SetPerceivedTeam` are distinct;
- WeaponMine hostility uses actual team, not `perceivedTeam`;
- the hop-out radar growl is not evidence of mine friendly fire;
- inspected attacker reveal on landed damage exists in both builds.

It does **not** prove the victim-side AI retaliation path.

## 4.2 Exact open complaint

Scott ("Herp") reports that an AI-controlled captured/disguised craft can be attacked by the team it is perceived as belonging to and fail to defend itself unless directly ordered where possible. The same behavior reportedly affects:

- ordinary AI-piloted captured craft;
- `turrettank` deployable turrets such as Badger/PAK;
- `turret` gun-tower buildings;
- the non-critical CCA mission 7 (`Reclaim Our Base`) tower behavior.

Sniper aggression reportedly breaks the bad state even when ordinary incoming fire does not.

## 4.3 Reproduction matrix

Construct in both 1.5 and Redux:

```text
victim.actualTeam    = 1
victim.perceivedTeam = 2
attacker.actualTeam  = 2
```

Test each victim class with:

- normal projectile hit;
- normal projectile fired/missed;
- sniper attack without successful snipe;
- explicit Attack order where class supports it;
- captured craft exit/re-enter transition.

Trace on the **victim**:

- `SetDamageFlags` classification;
- friend/enemy relation result against damager/owner;
- target assignment;
- process/task transition;
- defend/attack/retaliation branch;
- actual/perceived team before/after damage;
- sniper-specific aggression branch.

Implementation gate: **do not patch until the first 1.5-vs-Redux victim-side behavioral divergence is identified.**

The quarantined OpenShim "reveal process owner on engagement" hook is not a valid substitute; that was an enhancement, not proven 1.5 behavior.

---

# 5. CLI parser multi-parameter regression

Reported symptom: Redux options taking more than one parameter fail because delimiters are consumed incorrectly.

Existing evidence: renderer-backend work proved Redux destructively tokenizes the process command-line buffer early enough that OpenShim had to snapshot it during process attach.

Research plan:

1. Enumerate 1.5 and Redux option tables.
2. Identify every multi-value handler/format.
3. Choose at least two visibly testable commands.
4. Test comma-separated, whitespace variants where historically valid, `:`/`=` forms, quoting, and option ordering.
5. Capture pristine command line, tokenizer output, and handler input.
6. Compare 1.5 vs Redux.
7. Patch the earliest proven divergence only.

Use known single-value controls such as renderer selection and final-patch `-disablemods` as parser baselines.

If confirmed, prefer repairing affected values from OpenShim's already-owned immutable command-line snapshot over replacing the whole stock parser.

---

# 6. HGT smoothing / HG2 legacy restoration

## 6.1 Evidence is stronger than a community preference

Official Rebellion dev blog:

https://store.steampowered.com/news/posts/?appids=301650&enddate=1460732810

Redux explicitly advertised automatic **upscaling and smoothing** of old maps.

The final 2.2.301 patch later explicitly **removed smoothing from Great Pyramid (`multdm29`) to restore its original stair-step terrain**:

https://steamcommunity.com/app/301650/discussions/0/154644705026213561/

That makes no-smoothing a demonstrated legacy-preservation requirement for at least one stock map.

## 6.2 Future/community HGT imports

Goal: legacy-compatible conversion preserves original HGT control points unless smoothing is explicitly requested.

Research:

1. locate HGT -> HG2 conversion and smoothing branch;
2. confirm existing no-smoothing control and scope;
3. convert representative HGT both ways;
4. compare geometry/control-point heights;
5. run AI navigation on authored sharp ridges/steps;
6. expose a safe OpenShim policy only after parity is understood.

## 6.3 Stock maps already shipped as smoothed HG2

Changing the future converter cannot undo already-converted terrain.

Proposed restoration:

```text
original BZ98/1.5 stock HGT
 -> Redux HGT-to-HG2 conversion
 -> smoothing explicitly disabled
 -> corrected stock-name HG2
 -> controlled compatibility asset override
```

Start with **Great Pyramid** because first-party patch history already identifies it as needing unsmoothed geometry.

For every candidate compare:

- maximum/mean/median height deviation;
- count of changed original HGT control points;
- slope/normal changes;
- AI pathing;
- BZN object grounding/building placement;
- nav points/triggers/camera paths;
- required terrain-lighting data.

Acceptance target: regenerated compatibility terrain preserves original authored HGT heights at original sample points; added HG2 samples must not move the legacy control lattice.

---

# 7. Multiplayer shell restoration: All Nations / Cloak Disabled

## All Nations

Recover:

1. 1.5 shell control storage;
2. faction-selection validation consumer;
3. network/lobby serialization;
4. whether Redux retains dormant rule support.

Restore rule state first, UI second. Verify all peers enforce the same faction policy.

## Cloak Disabled

Recover:

1. 1.5 match setting;
2. cloak availability/activation consumers;
3. lobby/network serialization;
4. interaction with individual craft cloak/pilot-loss state.

Important new invariant from the final 2.2.301 patch: **units must de-cloak in all intended pilot-loss paths.** Keep match-wide cloak policy separate from per-craft pilot-loss cleanup.

---

# 8. Netcode / BZRNet preservation

Keep two problems distinct.

## In-match transport stability

Current progress:

- full live `[Net]` tunable application;
- bandwidth governor/floor instrumentation;
- send-rate telemetry;
- relay/control/datagram traces;
- packet/reliability archaeology;
- dedicated-server protocol contract and parity tests.

Remaining acceptance gate: controlled two-PC impairment runs with an immediately preceding impairment-OFF relay control, then loss/reorder cases with forensic traces. Do not hide broken recovery by merely extending timeouts.

## External service dependency

Stock Redux still lacks a user-facing independent direct-connect/LAN service mode comparable to old flows. Community server work should preserve the stock client/service contract and eventually provide OpenShim service selection/failover/local-private hosting without inventing an incompatible second game protocol.

Historical note: developers said P2P game traffic worked across LAN when players were signed into Steam, but service/lobby availability remained an external dependency.

---

# 9. Crash/stability policy

Never close "random crashes" as one checkbox.

```text
reproduction
 -> signature / module + RVA
 -> native root cause
 -> narrowly scoped guarded patch
 -> runtime regression
```

The historical source sweep adds one worthwhile lifecycle case: the official launch known-issues thread documented Redux remaining as a **phantom process after shutdown**. Given current DllMain/thread/lifetime work, repeated clean process termination should be explicitly qualified.

See `Docs/REDUX_HISTORICAL_REGRESSION_SWEEP_20260827.md`.

---

# 10. Red Odyssey named mission audit

Scott ("Herp") specifically identified public fixes around:

- `BDMISN08`;
- `BDMISN11`;
- `CHMISN05`.

The supplied correspondence intentionally did not spell out each failure, so do not infer an engine root cause from names alone.

For each:

1. find the public workshop fix/description;
2. compare Redux behavior with original TRO;
3. classify as content/data/script/native;
4. keep content repairs in campaign/content repo unless native evidence points to OpenShim.

---

# 11. Priority order

1. **Day Wrecker duplicate/source detonation + historical Popgun duplication diff**.
2. **`perceivedTeam` victim retaliation/break-cover parity**.
3. **CLI multi-parameter parser parity**.
4. **Great Pyramid HGT/HG2 no-smoothing study**, then broader stock terrain reconstruction.
5. **Shutdown phantom-process qualification**.
6. **AI path/subtask resumption regression** from final-patch invariant.
7. **All Nations / Cloak Disabled restoration**, preserving pilot-loss decloak behavior.
8. **TRO named mission audit**.
9. Continue crash signatures, BZRNet impairment work, Splinter/editor/render/resource tracks in parallel.

---

# 12. Permanent compatibility checklist

- [ ] Destruction chunks visibly render and follow native fragment motion.
- [ ] Jump-snipe compatibility reproduces 1.5 landing behavior.
- [ ] Satellite hides undetected/unilluminated enemies and preserves pre-hidden state.
- [ ] One Day Wrecker launch yields one authoritative projectile/explosion chain per peer.
- [ ] Popgun remains non-duplicating in MP as fixed historically.
- [ ] Disguised AI victim response matches 1.5 for cannon hit/miss/sniper cases.
- [ ] Multi-parameter CLI handlers receive complete values.
- [ ] `-disablemods` and renderer CLI controls remain functional baselines.
- [ ] Legacy HGT compatibility conversion can preserve original control-point heights.
- [ ] Great Pyramid retains intended stair-step compatibility geometry.
- [ ] Steam map browsing preserves selection/list position.
- [ ] `Inst4XMission` saves load repeatedly without stale-handle faults.
- [ ] MP impairment tests recover within the proven protocol contract.
- [ ] AI following a path resumes correctly after subtask interruption without leaving map.
- [ ] Pilot-loss paths clear cloak where stock intends.
- [ ] Failed mission never incorrectly advances campaign progression.
- [ ] Restarted mission reconstructs build/path UI.
- [ ] Client Alt+Tab during MP load does not crash qualified renderers.
- [ ] Pilot animation timing remains frame-rate independent.
- [ ] Shutdown leaves no phantom Battlezone/OpenShim process/thread state.
- [ ] All Nations / Cloak Disabled, if restored, are shared match rules rather than local UI-only switches.

Keep historical symptoms in this file after closure. Update status/evidence and retain the acceptance test so future work cannot silently reintroduce the same class of regression.
