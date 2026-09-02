# BZ 1.4 legacy AI — OpenShim integration design (2026-09-01)

**Goal:** expose reconstructed 1.4 combat behavior as an **opt-in, per-unit, data-selectable compatibility mode** inside Redux/OpenShim, with stock Redux unchanged when not selected. Companion to `bz_aiName_dispatch_reconstruction_20260901.md` and `bz14_ai_nonvirtual_mapping_20260901.md`.

## 1. Recommended architecture — Hybrid B+C (factory extension + per-unit semantic flag)

**Conceptual model (names provisional, proven legal):**

```
TankFriend          → stock Redux / 1.5 behavior (RtimeClass "TankFriend")
TankEnemy           → stock Redux / 1.5 behavior (RtimeClass "TankEnemy")
TankLegacyFriend    → OpenShim 1.4-compatible behavior (new RtimeClass)
TankLegacyEnemy     → OpenShim 1.4-compatible behavior (new RtimeClass)
```

Both legacy names fit `char[32]` at `GameObjectClass+0x8C/+0xAC` (proven). The 8-char ODF limit applies only to `%.8s.odf` resource filenames, not to `aiName` (see dispatch doc). `TankLegacy*` are therefore valid internal identifiers; an 8-char file-safe fallback like `TnkLgFr`/`TnkLgEn` can be offered for completeness but is not required.

**Why not pure factory (A) or pure flag (B)?**

* **A (new factory entries alone)** would duplicate the entire `AiProcess` + `AttackTask` + `UnitTask` helper chain for each legacy unit, requiring 500+ bytes of transplanted machine code. The kit shows most helpers are behaviorally identical and reusable (DoSlide table identical, constants shared, deltas are control flow).
* **B (existing class + global flag)** would require a global `if (legacyAI)` that is unsafe: `AttackTask` is shared by six classes (`TankFriend/TankEnemy/ScoutFriend/ScoutEnemy/BomberFriend/BomberEnemy` — Scout overrides only slot 57, bombers differ but use same AttackTask). An ungated patch changes six classes at once.
* **Hybrid C (preferred):**
  - Register **two new RtimeClass entries** `TankLegacyFriend` / `TankLegacyEnemy` whose factories instantiate the **same** `TankFriend`/`TankEnemy` `AiProcess` vtables but with a **per-instance legacy flag** (`legacy14 = true`) stored in the `AiProcess` or its `AttackTask` (prefer non-serialized context: derive from `RtimeClass` name at `Init`/`CreateObject`, no save-format change).
  - Inside the *existing* Redux bodies, gate the **four proven deltas D1–D4** (evasive doc §7, §11) on that flag. All four are branch sites inside `AttackTask::DoState` at `0x478A50` (Proven hook point `kGogAttackTaskDoStateEntryAddr` via `ExpectedBytesMatchAt`). Each site can be toggled independently, so partial enablement is config, not a fork.
  - Reuse Redux helpers where behaviorally equivalent: `IsStuck`, `DoSlide` (identical), `SidewaysAndClose`, `AbleToHit`, `MayHitFriends`, `UpdateWeapon` FourCC gate (live) — per kit recommendation “reconstruct semantics, reuse infrastructure”.

**Least-invasive, narrow hooks:**

1. **Chase-routing site D1** — state 2 `AbleToHit` branch: `if (legacy14) next=7 (slide) else next=10 (blast)` (1.4 `0x40D190: call AbleToHit; je …; mov [esi+0x10],7` vs 1.5 `LAB_0040F59D: state=10`).
2. **Slide-exit predicate D2** — state 7: replace `IsBuilding(target) || now>start+10.0` with `enemyTaskState in {2,5,7} → 10 else SidewaysAndClose → 8 else stay`, uncapped. Requires resolving enemy task: `enemyHandle at Task+0x1C → object → vtbl+0x30 → state at +0xAC` (1.4 pattern at 0x40CFA3). Use Redux offsets (`curState+0x8`/`nextState+0xC` etc; see evasive doc S11 table: craft damage +0x1E0/+0x1EC vs 1.4 +0x1DC/+0x1E8).
3. **State-8 expiry D4** — `now>start+8.0` writes `next=7` (rotate) if legacy else `next=9` (flee) and `fleeFrom=GetHandle(him)`.
4. **Flee bound D3** — suppress `start+3.0 → 10` re-evaluation in state 9; keep distance/gone/stuck exits and `5625`/`75²` gate.

These four deltas fully parameterize the observable 1.4-vs-1.5 combat rhythm change. Every other constant (5625, 8s, 3s, 15s, formation/range, slide quadrants) is verbatim.

**Why per-unit is safe:**
* Stock units are untouched because the difference is a **branch taken per AiProcess/Task instance**, not a detour installed globally.
* Scope is **Tank/Scout family only** (59-slot vtables; Scout inherits movement, rocketTank is out-of-scope — see behaviour spec §0). Gate on class family; bomber inherits same AttackTask but is logically separate — gate explicitly, no `legacy14` for bomber unless measured.
* Redux helpers remain on hot path for both modes; legacy mode only changes decision predicates.

## 2. Alternative considered — Option B alone (flag only)

If factory registration proves difficult (e.g., anti-cheat signature of `RtimeClass` table), fall back to reusing the *existing* `TankFriend` class and driving legacy via **non-serialized ODF context** (read `aiName` string at `GameObjectClass+0x8C` hashes in `TryReadAiTuningFromOdfFile`; if `bomberAiRole` precedent, add `legacyAiRole` flag there). This still needs the string, but no new RtimeClass — the flag is set from ODF content, not from RtimeClass name. Downside: cannot have both modes in same mission with same ODF unless two ODFs exist; factory extension is cleaner for coexistence.

## 3. File / hook locations

* `src/patches/bzr_hooks.cpp:1029` — `kGogAttackTaskDoStateEntryAddr = 0x00478A50` (byte-validated). Primary hook for D1/D2/D3/D4. Add `LegacyGate` check there.
* `GameObjectClass+0x8C/+0xAC` reads at `0x99FBE`/`0x99FDC` (ctor) — add `legacy14` derivation at `AiProcess::Init` or `AttackTask::Init` (create time), not at load.
* `UnitTask::DoStuck` 0x6EC? Actually `FUN_006029B0` (Redux) — if legacy stuck recovery desired, replace the linear `Range_Search_Results` path with the 7-state machine gated on `legacy14` (bounded: 1 detect+4 directional+2 fallback, 2s window, 3 control outputs; see spec §4). This is a **subsystem restoration**, not a gate — defer until DoSlide/DoFlee gating is validated.
* `openshim.ini` — add `[SinglePlayer] Legacy14AI = 0` or `[Ai] legacy14 = auto` plus per-ODF override; default OFF. Use the preset-migration pattern from `openshim.ini` rev 2.

## 4. Integration steps

1. **Prove registration:** add `RtimeClass` entries for `TankLegacyFriend`/`TankLegacyEnemy` (push legacy factory, push string, mov ecx, call `0x4B1036`-equivalent in Redux; address will differ — sited via Redux PDB or `build_legacy_to_redux_symbol_map.py`). Verify via `ExpectedBytesMatchAt` and runtime spawn with `aiName="TankLegacyFriend"` (ODF with `aiName = "TankLegacyFriend"`); log factory hit.
2. **Gate D1–D4:** insert `if (isLegacy(task))` branches at the four sites in `FUN_00478A50`. Reuse `IsBuilding`, `IsStuck`, `DoSlide`, `SidewaysAndClose` etc; for D2 read enemy task state at Redux offsets (task state field at `+0xAC` in 1.4 → +? in Redux — sited via `build_re_brief.py` or manual `+0xC` vs `+0x8` shift table in evasive doc S14).
3. **IsStuck gating:** for legacy units, bypass `flags &4` exemption and skip `0x20000` clear (spec §3 — smallest delta, test first).
4. **Validate with harness:** run the qualification mission (next section) with matrix `TankEnemy` vs `TankLegacyEnemy`; measure stickiness (time in state 7 vs 10, SidewaysAndClose events, flee duration capped vs uncapped).

## 5. Test harness — controlled legacy-vs-Redux (local GOG/lcbench framework)

**Goal:** spawn otherwise-identical units differing only in `aiName`, on identical terrain/orientation/distance, and log behavioral deltas.

**Matrix (per mission):**

```
TankFriend          vs TankLegacyFriend   (friendly feel)
TankEnemy           vs TankLegacyEnemy    (enemy feel)
TankEnemy           vs TankEnemy          (baseline Redux reproducibility)
TankLegacyEnemy     vs TankLegacyEnemy    (legacy reproducibility)
TankEnemy           vs TankLegacyEnemy    (cross — AIs react to each other’s states; F1 predicts mutual slide interaction)
TankLegacyEnemy     vs TankEnemy          (inverse)
```

Use identical `ODF` (e.g., `avtnk` Light Tank), same `weaponName1/2`, `maxHealth`, `skill`, starting `transform` via `GetPositionNear` (not stacked), same `terrain`/`TRN`, same `engagementDistance`. Only `aiName` differs per spawned `GameObject` (set via ODF variant: `avtnk_legacy.odf` with `aiName="TankLegacyEnemy"` copying `avtnk.odf`).

**Metrics (log via `print` — not `DisplayMessage` — for offline/single-player; Lua 5.1, no goto, no ObjectiveObjects iterator):**

* time to first engagement, first-shot range
* distance maintained from target (histogram)
* state transitions (`curState`/`nextState` at `+0x8`/`+0xC` in Redux, logged via shim probe)
* slide/strafe events (DoSlide entry)
* flee/retreat transitions (state 9 entry/exit, dist >5625 vs time+3s)
* target switches (DoSubTask hijack 3s), weapon switches (UpdateWeapon FourCC gate)
* stuck recovery (state 3 entry, `this+0x84` value, blocked probe)
* time pursuing vs disengaged, damage dealt/received, survival time, position over time (sampled every 0.5s)

**Lua notes:** `GetOdf()` etc return fixed-length strings with trailing `\0`; normalize via `string.gmatch(str,"\0")` or `str:match("^[^%z]*")` before equality. Use `GetPositionNear` for second spawn.

**Offline validation:** run under `run_misn06_auto_capture.ps1` style harness, capture `tmp_runtime_strings` and hooks hit budget (`InterlockedDecrement` budget pattern in `bzr_hooks.cpp` AI range traces). Compare median `timeInSlide`, `fleeDurationMax`, `sidewaysCloseCount`.

## 6. Risks and mitigations

* **Blast radius:** AttackTask shared by 6 classes — mandatory per-craft gate; never global. Gate on `legacy14` derived from `RtimeClass` name or ODF token at `Task::Init`, not on `openshim.ini` alone for mixed missions.
* **Stun-lock exploit:** faithfully porting D3 reproduces the repeated-hit stun-lock (states 8/10 freshen `craft+1DC > task+0xD4` → flee). Intentionally preserved; D3 bound is the mitigation toggle — keep it independent.
* **Save/net desync:** deltas are AI-local decision timing; outputs are vehicle controls/weapon triggers, not serialized sim state. Prefer non-persisted `legacy14` (derived, not saved) to avoid save-format drift (Hypothesis, needs writer check).
* **Revert:** single gate constant disables D1–D4 and restores stock flow; byte-validation at `0x478A50` guards patched region.

## 7. Remaining reconstruction queue (ranked by behavioral importance)

1. **AbleToHit / UpdateWeapon split** — must separate `0x46E530` host into two 1.4 addresses (weaponRangeSq+LOS vs MayHitFriends+FourCC+cooldown). Blocks faithful fire-gate port (F3b/c were deleted; F3a survives relocated).
2. **DoStand / DoBlast** — stand-fire ≤8s vs blast-hold; building vs vehicle branches.
3. **DoFollow / GoTowards** — flank-follow logic (10000/2500/225 vs 22500/136900/102400).
4. **UnitProcess::ChangesState / WingmanProcess::ChangeState** — group-level 3s/15s hijacks already proven, but additional deltas at `0x470E10` etc (51 vs 20 lines) may hide further cross-agent coupling.
5. **DefendTask::InitState / DoState, SAV/Rescue tasks** — cases differ (Y) but lower priority than core Tank loop.
6. **ScavengerProcess::Execute / TugProcess::Execute** — 81 vs 36 / 56 vs 31 lines — resource AI, not combat rhythm.

## 8. Proven file / address refs

* ODF: `GameObjectClass` `aiName` at `+0x8C` (`0x98D7239C`), `aiName2` at `+0xAC` (`0x48AD2AEA`), section `0xD3DD9CEC` — `1.5/functions/0049/00499e42_*.c`.
* Registration: `0x5CA6CF` (`TankFriend` → `0x470E35` → `0x5DBEA0`); factories `0x470E35/0x47072A` etc.
* Hook: `bzr_hooks.cpp:1029` `0x478A50`; `bzr_hooks.cpp:24732` `aiName` ODF reader (bomber precedent).
* Deltas: `AttackTask::DoState` 1.4 `0x40CDE0` case 7 at `0x40CFA3` (`mov eax,[eax+0xAC]; sub cmp {2,5,7}`) vs 1.5 `0x40F25B`; D1 site `0x40D190`, F1 site `0x40CF97`, `SidewaysAndClose` `0x414340` / `0x41516C` / Redux `0x488D0`.
* Constants shared: flee exit `5625.0` (`75²`) at `0x5E6EA4`, stand cap `-8.0`, `3.0`/`15.0`/`50.0` abeam, slide table `0x604CD0`/`0x6267C0` (320 floats, identical).
* Specs: `bz14_evasive_ai_investigation_20260823.md` §7 D1-D4, §11 port design; `bz14_ai_behaviour_spec_20260901.md` §0-4; `bz14_vs_bz15_ai_census_20260901.md` §2-5.

