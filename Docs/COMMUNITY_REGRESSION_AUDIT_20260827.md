# Battlezone 98 Redux Community Regression Audit

**Date:** 2026-08-27  
**Scope:** OpenShim / Extra Utilities / BZRNet preservation work  
**Primary compatibility reference:** Battlezone 1.5 behavior where a historical comparison is required

## Purpose

This document converts a detailed long-running community bug report into a durable regression backlog for OpenShim. The goal is not to treat every criticism as automatically correct; the goal is to preserve the exact reported symptom, separate it from later reverse-engineering conclusions, and define a reproducible acceptance test for anything that is not already closed.

The immediate source was the detailed technical grievance list supplied on 2026-08-27 from Scott/Herp's correspondence about his Battlezone 98 Redux review. Only the technical bug descriptions and public-facing references are captured here. The unrelated personal/off-record portions of that correspondence are intentionally **not** copied into the repository.

Public references supplied with the report:

- Steam review: https://steamcommunity.com/id/herpmcderperson/recommended/301650/
- Historical Pastebin mirror/context: https://pastebin.com/FvtY5eZW
- Destruction comparison videos:
  - https://youtu.be/Rt7EmTzTC-4?t=84
  - https://youtu.be/zVrRj4_pNxc?t=182
- Day Wrecker multiplayer demonstration: https://youtu.be/dhyWp3TDe-k
- Historical Lua workaround for `Inst4XMission`: https://pastebin.com/ue5Z8sbq

This file is the status/triage document. Detailed native findings remain in the relevant `reverse_engineering/` reports and feature-specific `Docs/` files.

## Status legend

| Status | Meaning |
| --- | --- |
| **FIXED** | Reproduced/understood sufficiently and a production-path compatibility fix exists. |
| **FIXED / CONFIGURABLE** | Fixed with a user/mission policy switch where preserving both behaviors is useful. |
| **PARTIAL** | Major contributing defects are fixed or understood, but the historical complaint is too broad to declare fully closed. |
| **OPEN - REPRO NEEDED** | Report is specific enough to test, but the failing native path has not yet been captured. |
| **OPEN - RE NEEDED** | Reproduction is understood, but the native producer/consumer still needs reverse engineering. |
| **TODO - FEATURE RESTORATION** | Missing 1.5 functionality rather than a crash/correctness regression. |
| **CONTENT FOLLOW-UP** | Mission/content issue is real enough to track but belongs primarily in a campaign/content repository unless an engine cause is found. |

---

# 1. Regression status matrix

| Historical complaint | Current status | OpenShim assessment / evidence |
| --- | --- | --- |
| Destroyed ships still fragment but the physical chunks are invisible | **FIXED** | OpenShim restored physical destruction-chunk rendering and later hardened/optimized the chunk proxy/batching path. The current roadmap already lists restored physical destruction chunks as established baseline behavior. |
| Jump-sniping is easier/exploitable because holding jump with the sniper deployed no longer reproduces the 1.5 landing restriction | **FIXED / CONFIGURABLE** | 1.5-style jump-snipe crouch/landing behavior is implemented. Keep it configurable for single-player compatibility/policy rather than forcing one global gameplay preference. |
| Satellite/SkyEye visually reveals enemy objects outside radar/illumination coverage | **FIXED / CONFIGURABLE** | Root cause was identified: Redux lost the 1.5 overview submission illumination gate. OpenShim restores the illumination/visibility gate and preserves independently-owned hidden states. See `Docs/SATELLITE_VISIBILITY_FIX_PLAN.md` and the satellite RE reports. |
| Multiplayer Armory/SLF Day Wrecker can create an extra damaging detonation at the source Armory for other peers | **OPEN - RE NEEDED; HIGH PRIORITY** | The roadmap mentions the duplicate detonation, but the full asymmetric report and two-PC validation matrix are recorded below. Do not conflate this with the separate Day Wrecker terrain-spire issue. |
| AI-controlled captured/disguised units with `perceivedTeam` set to the attacker may fail to break cover or defend themselves when fired upon | **OPEN - REPRO/RE NEEDED; REOPENED** | Existing RE proved that capture/disguise `perceivedTeam` writers match 1.5. It did **not** prove parity in the incoming-damage -> aggression/retaliation path. The prior conclusion that the whole report was settled was too broad. Details below. |
| The Red Odyssey port contains mission-specific regressions (reported BDMISN08, BDMISN11, CHMISN05) | **CONTENT FOLLOW-UP** | The supplied report does not contain enough technical detail to attribute these to OpenShim. Audit the named missions/workshop fixes separately and promote any native engine cause back into this list. |
| Multiplayer lacks 1.5 `All Nations` host option | **TODO - FEATURE RESTORATION** | Already on the roadmap. Restore only after tracing the actual 1.5 rule path; do not implement this as a cosmetic UI-only switch. |
| Multiplayer lacks 1.5 `Cloak Disabled` host option | **TODO - FEATURE RESTORATION** | Already on the roadmap. Same rule: restore underlying game/network state first, then expose the shell control. |
| Steam multiplayer map list jumps/resets to the top when selecting/browsing maps | **FIXED** | Steam map-list selection preservation/refresh path was repaired, including the SteamStub timing case that could leave the selection helper unresolved. |
| Redux multiplayer disconnects too easily / netcode performs substantially worse than 1.5 | **PARTIAL** | OpenShim now writes the full live `[Net]` block, hardens the bandwidth governor path, adds outbound telemetry, and has much stronger relay/protocol diagnostics. Dedicated-server/BZRNet work has progressed substantially. Historical network instability is too broad to declare universally fixed until two-PC loss/reorder recovery qualification is complete. |
| No TCP/IP/LAN path means multiplayer depends on Rebellion BZRNet availability | **PARTIAL / ACTIVE PRESERVATION PROJECT** | The community BZRNet replacement/dedicated-server project now implements a much larger stock-compatible service/relay surface. Player-facing service selection/failover and an integrated local/private hosting path remain future work. |
| Random segfaults/crashes occur at a high rate | **PARTIAL / ONGOING** | Many individual stock/shim crash signatures have been reproduced and fixed, including loader races, mission lifecycle faults, map-list faults, save/load faults, and stale Ogre references. This complaint must remain signature-based rather than being marked globally fixed. |
| Native `Inst4XMission` save/load can crash frequently, forcing mission authors to replace it with Lua | **FIXED** | Save/load lifecycle hardening closes the reproduced `Inst4XMission` stale-handle/object-pool failure without requiring mission conversion. Unscripted Instant Action AutoSave initialization was also restored. |
| CLI argument parser fails for options that require more than one parameter because delimiters are consumed incorrectly | **OPEN - RE NEEDED** | The full report finally defines the symptom. OpenShim independently proved that Redux destructively tokenizes the process command-line buffer with `strtok()`, which makes this complaint plausible, but the exact multi-parameter failure has not yet been proven. Investigation plan below. |
| Legacy HGT import smoothing is default-on, alters original terrain, and can damage AI/pathing; stock converted maps were affected | **OPEN - COMPATIBILITY RESTORATION** | Existing roadmap already tracks the smoothing default. The new plan is to separate future legacy HGT conversion policy from correcting already-ported stock terrain. Details below. |

---

# 2. Closed items that should remain in the regression suite

A bug being fixed does not mean it should disappear from documentation. These should stay as permanent smoke/regression cases because each represents behavior Redux diverged from and OpenShim now intentionally restores.

## 2.1 Physical destruction chunks

Historical symptom:

- The native destruction system continued simulating fragment/chunk objects.
- Secondary impacts/explosions still occurred.
- The actual model pieces were invisible in Redux.
- A Grizzly, for example, should visibly break into multiple authored pieces instead of appearing to explode as one intact render object plus unexplained secondary impacts.

Current state: **FIXED.**

Regression acceptance:

1. Destroy stock multi-piece craft/buildings with OpenShim enabled.
2. Confirm native fragment trajectories still drive the render proxies.
3. Confirm custom/authored chunk payloads do not regress to generic debris incorrectly.
4. Repeat across in-process mission changes to catch stale proxy/resource lifetime faults.

## 2.2 Jump-sniping

Historical behavior to preserve as the compatibility reference:

- In 1.5, moving with the sniper rifle deployed required bunny-hopping and retracting/undeploying before landing to avoid becoming fixed in place.
- Redux allowed the player to continue holding jump with the sniper deployed indefinitely, removing the old constraint and making the technique substantially easier to exploit.

Current state: **FIXED / CONFIGURABLE IN SINGLE PLAYER.**

Regression acceptance:

- Compatibility mode must reproduce the 1.5 landing/crouch constraint.
- Disabling the compatibility behavior must remain possible where the user deliberately prefers Redux behavior.
- Multiplayer policy must remain conservative and explicitly qualified; do not silently introduce a client-side competitive rule divergence.

## 2.3 Satellite/SkyEye fog of war

Historical symptom:

- Enemy objects outside radar/illumination range were not necessarily targetable or present on radar, but their Ogre geometry was still visually rendered in satellite view.
- This effectively defeated the visual fog-of-war function of SkyEye.

Current state: **FIXED / CONFIGURABLE.**

The decisive RE finding was that 1.5 has an overview-only submission gate based on illumination while Redux routes satellite through the ordinary ungated submission path. OpenShim restores equivalent visual gating at the Ogre entity layer while respecting hidden states owned by other systems.

Keep the existing dedicated satellite fixture as the acceptance test:

- friendly/near -> visible
- detected/near enemy -> visible
- undetected/far enemy -> hidden
- pre-hidden entity -> remains hidden
- entity revealed while satellite remains open -> becomes visible
- object created/destroyed while satellite is open -> no stale visibility state

See `Docs/SATELLITE_VISIBILITY_FIX_PLAN.md`.

## 2.4 Steam multiplayer map-list reset

Historical symptom:

- Selecting a Steam Workshop map caused the map list to jump/reset to the top, making large mod libraries extremely painful to browse.

Current state: **FIXED.**

Keep a Steam-specific regression with a sufficiently long subscribed map list and repeatedly inspect/select entries far from index zero. This must exercise the SteamStub/deferred-resolution path, not only GOG.

## 2.5 `Inst4XMission` save/load

Historical symptom:

- Classic non-scripted Instant Action missions using the native `Inst4XMission` path could crash during save load often enough that community authors replaced the mission class with Lua as a workaround.

Current state: **FIXED.**

OpenShim's current lifecycle hardening rejects stale/invalid GameObject handles and allows stock recovery instead of dereferencing dead object-pool state. The production fix should remain mission-format agnostic: users should not need to patch every old mission to Lua.

---

# 3. High-priority open investigation: multiplayer Armory / Day Wrecker duplicate detonation

## 3.1 Exact reported symptom

The Armory / Supply Launch Facility can launch the Day Wrecker powerup for 20 scrap. In multiplayer, the launching machine and observing machines can disagree:

**Launching player:**

- sees the legitimate launched Day Wrecker;
- may not see any extra explosion at the Armory;
- receives no damage from the alleged source-site phantom detonation.

**Other player(s):**

- see/receive the legitimate Day Wrecker behavior;
- can additionally receive a damaging Day Wrecker-class explosion at or near the source Armory;
- that extra damage can destroy units/pilots even though the launcher is unaffected by it.

The report also describes intentionally launching a Day Wrecker at the Armory, waiting briefly, and launching another. The two legitimate projectiles may collide above the Armory for double damage; if the phantom source detonation occurs during one or both launches, remote players can observe triple/quadruple effective damage.

This is a **network authority/replication correctness bug until proven otherwise**, not a damage-balance bug.

## 3.2 Questions that must be answered before patching

1. Does the remote peer create a **second Day Wrecker ordnance object**, or only a second explosion/damage event?
2. Which machine believes it owns the launched ordnance?
3. Does the source Armory locally create a transient projectile/effect that is incorrectly replicated or destroyed?
4. Is the duplicate produced by object creation, ordnance initialization, collision, destruction, or explosion damage allocation?
5. Does the fault depend on host/client direction, peer locality, packet timing, or Armory team?
6. Is the duplicated damage represented by the same owner/source IDs as the legitimate projectile?
7. Is the custom-scripted AI Armory problem the same defect or a separate authority/command issue? The supplied report says at least one additional AI-Armory bug exists but does not specify it enough to merge them.

## 3.3 Required two-PC matrix

Run every cell with deterministic starting geometry and fresh logs:

| Case | Launcher | Target | Expected capture purpose |
| --- | --- | --- | --- |
| DW-1 | Host | distant ground | baseline host-authority launch |
| DW-2 | Client | distant ground | remote-owner launch |
| DW-3 | Host | own Armory | collision/source-site stress |
| DW-4 | Client | own Armory | remote-owner + source-site stress |
| DW-5 | Host | own Armory, two timed launches | legitimate double-collision vs phantom extra damage |
| DW-6 | Client | own Armory, two timed launches | worst-case remote duplication path |

Repeat enough times to measure the reported inconsistency rather than accepting one clean run.

## 3.4 Instrumentation minimum

For every relevant creation/destruction/damage event on both machines record:

- monotonic timestamp and frame/tick
- machine role: host/client
- object handle / distributed identity if available
- object class/ODF
- actual team and perceived team
- locality/ownership state
- creator/source object
- initial position/transform
- initial velocity
- destruction reason
- explosion ODF/type
- explosion position
- damage owner/damager/dmg_source
- victim and damage amount
- corresponding network message/opcode when available

Do **not** use `SetLocal` as an investigative shortcut on the target object: current multiplayer knowledge shows that changing locality can itself break AI/ownership behavior and would contaminate this reproduction.

## 3.5 Acceptance condition

A fix is complete only when one Day Wrecker launch produces one authoritative projectile/explosion chain on every peer, with damage parity between peers, across both host-launch and client-launch cases.

---

# 4. Reopened investigation: `perceivedTeam` AI retaliation / break-cover behavior

## 4.1 Important correction to earlier RE

Existing work in `reverse_engineering/weaponmine_hop_friendly_fire_root_cause_20260817.md` proved several useful facts:

- capture deliberately keeps the previous owner's team in `perceivedTeam`;
- 1.5 and Redux have matching capture-side `perceivedTeam` writers;
- `SetTeam` and `SetPerceivedTeam` are distinct;
- stock reveal-on-damage behavior is not the same thing as revealing an AI process owner when it merely begins attacking.

Those findings are still valid.

What was **not** established is the actual bug described in the full community report:

> An AI-controlled captured/disguised craft, turret tank, or gun tower whose `perceivedTeam` makes the attacking side appear friendly may fail to defend itself when that side fires on it. Normal incoming fire may not break the disguise/aggression state; a sniper attack is reported to aggro the unit.

Therefore the previous statement that the reported scenario was fully answered is too broad. The **capture/disguise mechanism** was answered; the **incoming-damage -> target/aggression/retaliation behavior** remains open.

## 4.2 Why the quarantined attack-reveal hook is not a valid substitute

OpenShim previously experimented with revealing an AI process owner when it engaged. Later RE correctly classified that as an **enhancement**, not a proven 1.5 compatibility restoration, because stock reveal semantics depend on different events. Those hooks are now quarantined/removed from production registration.

Do not re-enable that feature merely to make this symptom disappear. First prove where 1.5 and Redux diverge in the victim's response to being attacked while disguised.

## 4.3 Reproduction matrix

Construct the same semantic state in both 1.5 and Redux:

```text
victim.actualTeam    = 1
victim.perceivedTeam = 2
attacker.actualTeam  = 2
```

Test victim classes separately:

- ordinary mobile craft with AI pilot
- `turrettank` deployable turret (Badger/PAK style)
- `turret` gun-tower building

For each victim class:

| Stimulus | Observe |
| --- | --- |
| Normal cannon/projectile hits victim | Does target acquisition occur? Does victim attack/return fire? Does perceivedTeam change? |
| Normal cannon/projectile fires but misses | Does threat/attack state change? |
| Sniper shot attacks but does not successfully snipe | Does the reported special-case aggro occur? |
| Direct explicit Attack order where the class supports it | Can command forcing bypass the failure? |
| Exit/re-enter captured craft | Does the disguise clear as reported? |

Also reproduce the reported CCA mission 7 (`Reclaim Our Base`) non-critical gun-tower case if the original mission state can be isolated without a community Lua workaround.

## 4.4 Trace points

The useful trace is on the **victim** side:

- `SetDamageFlags` / damage allocation
- enemy/friend relation result against damager and owner
- target assignment
- AI process/task transitions
- attack/defend/retaliation decision
- `perceivedTeam` before and after damage
- actual team before and after damage
- sniper-specific aggression path

The decision gate for implementation is simple:

**Do not patch until the first 1.5-vs-Redux behavioral divergence in this chain is identified.**

---

# 5. CLI parser: multi-parameter argument regression

## 5.1 Reported symptom

The full report states that Redux command-line options requiring more than one parameter do not work correctly because of delimiter parsing. This primarily affects content/modding workflows.

This is now a concrete bug class instead of the vague roadmap phrase "CLI parser broken."

## 5.2 Existing evidence

OpenShim's renderer-backend work independently established that Redux's stock startup parser uses destructive tokenization against the process command-line buffer (`strtok()` behavior). OpenShim had to snapshot the command line very early because later readers can see tokens already destroyed by stock parsing.

That fact makes the report plausible, but it does **not** by itself prove which delimiter or handler breaks multi-parameter options.

## 5.3 Research plan

1. Enumerate the complete 1.5 and Redux command option tables.
2. Identify every handler/format containing more than one conversion/parameter (for example comma-separated coordinate/dimension forms).
3. Pick at least two options whose result can be observed without relying on a mod author interpretation.
4. Run an input matrix containing:
   - one-parameter controls;
   - two comma-separated parameters;
   - whitespace-separated variants if supported historically;
   - `:` and `=` option separators where Redux accepts both styles;
   - quoted paths/values where applicable.
5. Capture the command buffer before parsing and at the failing handler.
6. Compare 1.5 tokenization, Redux tokenization, and the handler's expected `sscanf`/conversion input.
7. Patch only the earliest proven divergence.

Potential high-value candidates mentioned elsewhere in Battlezone documentation include multi-value map/editor/shell options such as `largemap`/shell-map dimension forms. The exact acceptance commands should be selected from the recovered option tables, not guessed from memory.

## 5.4 Preferred architecture if the report is confirmed

OpenShim already owns an early immutable snapshot of the original process command line for renderer selection. If stock Redux destroys information before a legacy-compatible handler receives it, use that early snapshot to repair only affected options rather than replacing every CLI behavior wholesale.

Requirements:

- stock single-parameter options remain byte/behavior compatible;
- last-wins/ordering behavior must match the legacy/reference parser where known;
- no global parser rewrite until all shell/editor startup consumers are mapped;
- Steam/GOG startup qualification remains intact.

---

# 6. Legacy HGT smoothing / HG2 compatibility restoration

## 6.1 Reported symptom

Redux supports finer terrain granularity than the original HGT format. Its legacy-map conversion path defaults to smoothing old heightmaps while producing Redux terrain. The report states that this:

- changes authored terrain shape;
- affects stock maps that were ported through the same path;
- can significantly worsen AI pathing;
- should have been opt-in rather than opt-out.

The current roadmap already tracks `Heightmap smoothing default behavior`, but the remediation needs to be split into two separate problems.

## 6.2 Problem A: future/community HGT imports

Goal: make legacy-compatibility conversion preserve the original HGT sample lattice by default unless the content author explicitly asks for smoothing.

Research/implementation sequence:

1. Locate the exact HGT -> HG2 conversion entry point and smoothing branch.
2. Confirm the existing stock `no smoothing` control and its scope.
3. Convert the same representative HGT both ways and compare output.
4. Verify AI navigation/pathing behavior on terrain with sharp authored steps/ridges.
5. If safe, expose an OpenShim compatibility policy similar to:

```ini
[Terrain]
LegacyHgtSmoothing=0
```

where `0` means preserve legacy terrain by default and `1` explicitly requests Redux smoothing.

The final option name/polarity should follow existing OpenShim configuration conventions; the above is only the intended policy.

## 6.3 Problem B: stock maps already shipped as smoothed HG2

Changing the converter default cannot repair terrain that was already converted and shipped.

Proposed restoration path:

```text
original Battlezone 1998 / 1.5 stock HGT
        -> Redux HGT-to-HG2 conversion
        -> smoothing explicitly disabled
        -> corrected stock-name HG2
        -> controlled OpenShim / compatibility asset override
```

Do not modify original mission geometry blindly. Validate every candidate map before shipping a replacement.

## 6.4 Quantitative validation

For each stock terrain candidate:

1. Recover/reference the original HGT sample lattice.
2. Generate:
   - shipped Redux HG2;
   - no-smoothing regenerated HG2.
3. Sample both outputs at every original HGT control point.
4. Report:
   - maximum height deviation;
   - mean/median deviation;
   - number of original control points changed;
   - slope/normal changes around sharp boundaries.
5. Run AI pathing cases across the affected terrain.
6. Verify BZN object grounding, building placement, nav points, mission triggers, and camera paths.
7. Regenerate/validate associated terrain-lighting data where the format/path requires it.

Acceptance target for a compatibility reconstruction is that the regenerated terrain preserves the original authored HGT heights at the original sample points; any additional HG2 samples between those points must not move the legacy control lattice.

---

# 7. Multiplayer shell feature restoration: All Nations / Cloak Disabled

These are missing 1.5 host options rather than newly crashing code, but they affect practical multiplayer balance and belong beside the regression backlog.

## 7.1 All Nations

Reported 1.5 semantics:

- despite the historical naming, the host option could restrict faction selection so players were not free to choose CRA/Black Dogs and were effectively constrained to the intended NSDF/CCA set for that match policy;
- the purpose was to prevent faction/content advantages that were not balanced for ordinary competitive play.

Required work:

1. Trace the 1.5 shell control to its stored game-setting bit/value.
2. Trace the faction validation/selection consumer.
3. Determine whether Redux retains the gameplay/network rule but only removed the UI, or removed both.
4. Restore rule state first; UI second.
5. Verify all peers receive/enforce the same selection policy.

## 7.2 Cloak Disabled

Reported 1.5 semantics:

- CRA could remain selectable while cloaking was disabled for the match.

Required work:

1. Recover the 1.5 game-setting representation.
2. Trace cloak availability/activation consumers.
3. Determine whether Redux retains dormant support.
4. Validate host/client rule agreement and save/lobby serialization.
5. Only then expose the native Redux shell control.

These items are already listed in `Docs/STEAM_ROADMAP_BBCODE.txt`; this document adds the acceptance criteria.

---

# 8. Netcode / BZRNet / LAN preservation status

The historical complaint combines two different issues and should stay split:

## 8.1 In-match netcode stability

Reported symptom: healthy connections can still experience severe rate collapse/disconnect behavior compared with 1.5.

Current OpenShim progress includes:

- full live `[Net]` tunable application rather than trusting `net.ini` to load;
- governor floor/collapse instrumentation;
- send-rate telemetry;
- socket/buffer work;
- relay/control/datagram diagnostics;
- native packet/reliability archaeology.

Remaining acceptance gate:

**controlled two-PC impairment testing** with a clean impairment-OFF control before each loss/reorder case, measuring whether recovery matches the intended stock/client contract rather than merely extending timeouts until the symptom disappears.

See `Docs/NETCODE_UPSTREAM_PARITY.md` and the dedicated-server protocol/interop documentation.

## 8.2 Dependency on Rebellion's online service

The lack of an old-style direct TCP/IP/LAN path means the stock Redux multiplayer experience depends on the external BZRNet service.

Current project direction:

- preserve the BZRNet protocol/service contract;
- provide a community-compatible replacement;
- support opaque relay where required;
- eventually add OpenShim service selection/failover;
- provide a straightforward local/private host path for LAN/private groups without requiring hosts-file tricks.

The eventual goal is resilience, not a second incompatible multiplayer protocol.

---

# 9. Crash/stability handling

The report's broad "random segfaults" complaint must never be closed as one checkbox.

OpenShim policy remains:

```text
reproduction
 -> crash signature / module + RVA
 -> native root cause
 -> narrowly-scoped guarded patch
 -> runtime regression test
```

The community report is useful historical evidence that stability was poor; it is not sufficient evidence that any new crash has the same root cause as an old one.

Keep current crash/lifetime items in the roadmap and continue classifying by signature.

---

# 10. The Red Odyssey mission-specific reports

The supplied correspondence names workshop fixes related to:

- `BDMISN08`
- `BDMISN11`
- `CHMISN05`

but deliberately does not explain the individual failures. No engine root cause can be inferred from that source alone.

Action:

1. Find the relevant public workshop fixes/descriptions.
2. Compare each affected Redux mission with the original TRO behavior and current Campaign Reimagined/content state.
3. Classify each as:
   - stock Redux mission/data port defect;
   - Lua/mission logic defect;
   - engine regression that belongs in OpenShim;
   - already fixed elsewhere.
4. Keep mission-content patches in the campaign/content repository unless native evidence points back to OpenShim.

---

# 11. Priority order from this audit

This ordering applies specifically to the newly clarified items. Crash signatures and active BZRNet qualification continue to run in parallel when evidence is available.

1. **Multiplayer Day Wrecker duplicate/source detonation** - severe remote-only damage/authority bug with a concrete two-PC reproduction.
2. **`perceivedTeam` victim retaliation/break-cover parity** - potentially wide AI consequence, affects captured craft and defensive unit classes, and may explain a stock campaign behavior regression.
3. **CLI multi-parameter parser parity** - likely bounded and high-value for modding/tool workflows; OpenShim already owns an early command-line snapshot.
4. **Legacy HGT no-smoothing policy + stock HG2 reconstruction study** - strong compatibility/restoration value and measurable acceptance criteria.
5. **All Nations / Cloak Disabled restoration** - important multiplayer shell/rule parity once the underlying 1.5 game-setting consumers are traced.
6. **TRO named-mission audit** - content-first triage, promote only proven native causes into OpenShim.

---

# 12. Regression acceptance suite derived from the review

Treat this community report as a permanent compatibility checklist:

- [ ] Destruction chunks visibly render and follow native fragment motion.
- [ ] Jump-snipe compatibility mode reproduces the 1.5 landing constraint.
- [ ] Satellite hides undetected/unilluminated enemies and preserves pre-hidden state.
- [ ] One multiplayer Day Wrecker launch produces one authoritative projectile/explosion chain on every peer.
- [ ] Disguised AI victims defend themselves exactly as 1.5 does for cannon hit/miss and sniper aggression cases.
- [ ] All supported multi-parameter CLI options receive their complete parameter list.
- [ ] Legacy HGT compatibility conversion can preserve original control-point heights without smoothing.
- [ ] Any corrected stock HG2 replacement is quantitatively closer to the original HGT and passes mission/pathing regression.
- [ ] Steam map browsing preserves list position across selection/preview.
- [ ] Native `Inst4XMission` saves load repeatedly without stale-handle crashes.
- [ ] Multiplayer loss/reorder tests recover without rate-collapse/disconnect regressions beyond the proven protocol contract.
- [ ] Community BZRNet replacement remains stock-client compatible and OpenShim can eventually select/fail over to it cleanly.
- [ ] All Nations and Cloak Disabled, if restored, are enforced by shared match state rather than only local UI.

---

# 13. Documentation corrections / follow-up

The following existing statements should be interpreted in light of this audit:

1. `reverse_engineering/weaponmine_hop_friendly_fire_root_cause_20260817.md` section 12 correctly settles capture/disguise writer parity, but its statement that this completely answers the stolen-vehicle report is **too broad**. Incoming-fire retaliation parity remains open.
2. Any roadmap/baseline wording that describes the old `perceivedTeam`/owned-attacker reveal hook as a completed production fix is stale. The experimental attack-reveal hooks are quarantined; they must not be treated as the compatibility solution to the retaliation report.
3. `Docs/STEAM_ROADMAP_BBCODE.txt` already tracks Day Wrecker duplication, HGT smoothing, All Nations, and Cloak Disabled. This audit supplies the detailed reproduction and acceptance criteria those short roadmap entries intentionally omit.

When the individual open investigations close, update this matrix rather than deleting the historical symptom. The point is to keep a durable record of what Redux did, what 1.5 did, what OpenShim changed, and how future changes prove they did not regress it again.
