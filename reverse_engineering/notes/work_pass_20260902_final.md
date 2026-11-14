# BZR OpenShim — Six-Target Execution/Qualification Pass 2026-09-02

**Workspace:** `BZR-OpenShim` (reuse `lcbench` + fixtures from prior pass). Scope locked to the six required targets — Editor session 2 and 32-bit VA lifecycle are out of scope for this pass; long-duration AIP is secondary only.

**Executable baseline:** GOG Battlezone 98 Redux 2.2.301 `battlezone98redux.exe` 5,425,152 bytes SHA-256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`. GOG is acceptable for static RE unless a concrete Steam divergence is found (settling delay accounted).

**Harness discipline:** `reverse_engineering/BZRHarness.ps1` + `BZR_FORCE_WINDOWED=1` + `Stop-BZRGame -Id` only; no `Stop-Process -Force`. `BZR_FORCE_WINDOWED` only for correctness runs — windowed vs fullscreen FPS not comparable. All runners back up `addon/lcbench` and restore in `finally`.

**Lua discipline:** 5.1 only, no `goto`/`::continue::`, no `io`/`os`/`debug`, no `ObjectiveObjects()`, `print` for SP debugging, `GetPositionNear` for multi-spawn, 8-char `*.ODF` and Lua-referenced assets, sanitize `GetOdf()`/`GetPilotClass()`/`GetWeaponClass()`/`GetClassSig()`/`GetBase()` NUL padding before compare.

---

Target| Runtime repro| Root cause| Production patch| Qualification| Confidence
Pilot hardpoint crash| Reproduced before patch (pcrft 3/3 new dumps), no crash after guard — valid pilot still functional | Person+0x1A0 null carrier deref in `Person::Simulate @0x0059D340 -> call 0x0059D76C -> Carrier::GetSelected @0x00417F90 mov eax,[eax+0x30]` when weaponHard keys outside [GameObjectClass] | Active `Pilot Carrier Null Guard` at `0x0059D76D` (pattern `8B 95 C0 FC FF FF 8B 8A A0 01 00 00 E8 ?? ?? ?? ??`) via `PersonCarrierGetSelectedGuard` returning mask 0, log once per Person | `run_lcroad_pilot.ps1` matrix pctl/pcrft/paftr/prevs/ppart before/after; pctl 3/3 RESULT, pcrft 3/3 crash->3/3 RESULT after, ppart still RESULT | High for fault and guard identity; inherited-vs-Redux unproven but no longer blocks safety
Mixed stock/custom AIP| Reproduced and localized: custom ODFs (mxfigh/mxturr/mxrecy) never built by any AIP account even alone (allc 0 vs alls 6), but same producer builds them on direct `Build()` 3/3 at T+50/68/86 | AIP construction program never asks for custom ODF name — ODF loader, producer build-list, and construction path all excluded; discriminating state is ODF-name/class-table lookup in AIP account->ODF resolution (producer classification, namespace, iteration, availability flag still competing hypotheses for exact comparison) | None — responsible AIP resolution routine not yet independently identified with call-site/xref identity | Fifteen-arm `rmaip.lua` matrix + `alls` vs `allc` whole-file test + direct-Build controls (`blds`/`bldc`); ccak 4+20-unit control proves harness drives production; Build-while-IsBusy pitfall documented | High for localization and harness gates; medium for exact divergent comparison (needs native selection logger)
Neutral attack asymmetry| Re-run confirms Lua/native `Attack` works both ways (n2p ammo 1.0->0.907, player hp 1.0->0.44, shot-by-neutral; a2n ammo 0.949, neutral hp 0.663) while UI order cannot target neutral — stock 1.5 parity | Single `ControlPanel::Render` target-list call to `Team::EnemyP @0x005E1350` (thiscall, `ret 4`, rejects targetTeam<=0 vs bit test `1<<team & +0x17C`). That predicate excludes team 0 so at-most-10 attack list never contains neutral; click never emits `CMD_ATTACK` | Narrow opt-in hook at that call site `0x004A3FD7` preserving stock enemies and only adding team 0 when `[Gameplay] AllowNeutralAttackOrders=1`, no global redefinition | Four directed `rmneut.lua` arms (n2p/a2n/a2e/a2f) + enemy/friendly controls; `luac -p` and config presets pass; MP host/client UI-order qualification still to capture | Very high for predicate and task path; MP UI qualification remains
Walker cockpit jitter| Harness ready; native trace wired (`walker_cockpit_trace.cpp` + `rmwlk.lua` 14-case matrix); initial `stat`/`fwd`/`slope`/`switch` avwalk vs avtank runs show world-vs-_c asset delta proven, earliest divergent writer not yet isolated in this pass — first locus still to be pinned per-frame | Asset topology proven distinct: `avwalk 28b (AGe11POV/age21hed child of age11hed)` vs `avwalk_c 26b/15tracks re-rooted`; `svwalk 15b -> svwalk_c 16b + svwalk00/01`; mesh verts `5260/88/153` vs `4177/88/153`. Cause hypotheses (stale/double-parent, animation order, interpolation, camera attachment, loop) remain open until per-frame worldNode->cockpitParent->POV->FPCam chain is compared | None — no generic smoothing; specific writer patch only after divergence proven | `rmwlk.lua` 10Hz POLL/DELTA + `walker_cockpit_trace.cpp` 60Hz Ogre enumeration (hasSkeleton strict promotion `avwalk_c/svwalk_c`, SceneNode derived pos/quat, AnimationState dt 500ms throttling, caller RVA+inMain, View_Record.MainCam) on `stat,fwd,slope,switch` walker vs `avtank` control; `luac -p` passes, 8-char audit passes; native build still to wire via CMake | Proven asset delta; speculative cause until first divergent node/RVA captured
MP freecam| Static 1.5 contract reconstructed and validated; live Redux writer still to be pinned — no speculative hook at rejected `0x00554EE0` | 1.5: `Set_Free_Eye_View @0x0047B4E7` + `Apply_Free_Eye_View @0x0047B8D2` driving `View_Record.{Pitch,Yaw,Dist,Dist0,Pitch0,Yaw0,Q,Q0,MainCam,Current_View,Update_Camera,Camera_Owner}` via `(eye_controls.track_* , zoom_*)` and terrain clamp, dispatched via `(*Update_Camera)()`; Redux `FUN_00554C80` proven not free-eye (serialization). Multiplayer gate is `Net::IsNetGame @0x004DD3ED` family plus player/spectator/dead/editor state — exact Redux predicate still to locate alongside the real Update_Camera writer | Log-only gate `freecam_gate.cpp` (fail-closed, no per-frame force-back; intended reject-at-transition) — production block remains disabled until View_Record writer resolved with one `[RESOLVE]` line and SP/editor/spectator states located | 1.5 decompile + `function_index` + prior rejection of `00554EE0`; Redux live capture planned: SP/editor/MP active player + legitimate spectator/observer contexts with caller `_ReturnAddress`/RVA, `IsNetGame`, local player team/IsPerson/health; matrix proposed SP allowed / Editor allowed / MP active blocked / MP spectator preserve-intended | High for 1.5 camera path; open for Redux RVA/predicate until instrumented run
All Nations| Dormant UI artifact proven; live rule byte not yet re-enabled but both chains recovered for 1.5 and traced to Redux edges | 1.5: `UI bool -> Net::bNations (offset 0x11 in 20-byte GameInfo) -> SendGameInfoData @0x004DE670 (TimeLimit 0,Kill 4,Flag 8,Lives 0xC,bSniper 0x10,bNations 0x11, dpSetPlayerData 0x14) -> HandleGameInfoData @0x004DE6F3 (param+0x11) -> consumers (nation check at faction filter, vehicle list)`. Redux: `AnyNationButton @0x00796880 +0x68 (string 0x0089E90C) -> hide/disable; callback 0x00795D70 -> 0x00417C60 nullsub; loader 0x00742090 (SyncJoin/CommSat/Barracks/Sniper/Splinter, dup Barracks) + launch 0x00799D70 + logger 0x005740A0 contain no Nation; vehicle lists 0x0045DD40/0x00766900 default only `netveh.odf`, no `netveh1.odf` literal — retains shell, not live contract | Restore `all_nations_restore.cpp` (re-enable row, replace callback to write existing `Net::bNations` byte reused, not new protocol) — code present and fail-closed (no write until `Net::bNations`/`bSniper` resolved via `HookEngine::ResolveNamedAddress` with identity from SendGameInfoData shape); no new field/version invented | 1.5 chain proven by decompile (`bNations` at +0x11 verified in Send/Handle); Redux shell/loader/launch/list proven absent; restore is code-complete and comments document dormant-rule reuse, but OFF/ON two-client lobby receive + all-nation list qualification (6+1 steps) still to run after resolves pin the exact bool VA | High for shell + 1.5 wire; inconclusive (D) vs removed (C) vs preserved (A/B) for Redux until `bNations` VA and consumer xref proven

---

## 1. Pilot hardpoint ODF ordering crash

**Evidence (this pass + prior 3/3 matrix):**
- Fixture: `reverse_engineering/test_missions/lcbench_roadmap/{pctl,pcrft,paftr,prevs,ppart}.odf` + `rmpilot.lua` + `rmpcfg.odf`; runner `run_lcroad_pilot.ps1`.
- Reproduction: `pctl` stock-valid ([GameObjectClass] hardpoint+weapon) 3/3 `RESULT valid=true person=true` no dump; closest malformed `pcrft` ([CraftClass] hardpair before PersonClass) 3/3 early exit no RESULT + new minidump; `paftr`/`prevs` same fault, `ppart` (hardpoint only) survives — immediate cause is null carrier, not missing weaponName.
- Crash trace/minidump (GOG 2.2.301): `C0000005 read 0x00000030` at `EIP 0x00417F9A` RVA `0x17F9A` (`FUN_00417F90 mov eax,[eax+0x30]`), `EAX=0`, caller return `0x0059D771` inside `Person::Simulate FUN_0059D340`. Call site:
  ```
  0059d760 mov edx,[ebp-340]    ; this Person
  0059d766 mov ecx,[edx+1a0]    ; carrier* (Person+0x1A0)
  0059d76c call 00417f90        ; Carrier::GetSelected -> reads [ecx+0x30]
  0059d771 mov [ebp-500],eax
  ```
  Reached via `Person::Simulate -> Carrier::GetSelected` as required. See `lcbench_runtime_roadmap_pass_20260901.md` for the five dumps that share this exact signature.

**Root cause:**
- `GameObject::GameObject` clears carrier to null and allocates it only when `weaponHard` in `[GameObjectClass]` is non-empty. Misplacing `weaponHard1`/`weaponName1` into `CraftClass` or after `PersonClass` leaves the keys valid-looking but unallocated — `Person+0x1A0` stays null.
- `Person::Simulate` then consumes it unconditionally to classify the on-foot animation (selectedMask). Same unguarded pattern exists in static 1.5 source — not a Redux-unique divergence, but the crash is reachable via trivial authoring and BuildObject succeeds, so the guard is safety not legacy change.

**Changes:**
- `scripts/patches.json` `Pilot Carrier Null Guard` at `fallback 0x0059D76D` offset 13 pattern `8B 95 C0 FC FF FF 8B 8A A0 01 00 00 E8 ?? ?? ?? ??`, `require_unique`, and `resolves Carrier::GetSelected @0x00417F90` (17-byte leaf `55 8B EC 51 89 4D FC 8B 45 FC 8B 40 30` returns `[this+0x30]`, both sides must agree before hook). `src/patches/bzr_hooks.cpp` `PersonCarrierGetSelectedGuard` — now headed with a production comment explaining what malformed/partially-initialized state is possible, why the guard is required, and why mask 0 is preferable to crashing (selectedMask only classifies on-foot anim; missing carrier == "no weapon selected", continue Simulate unchanged; first trip logs `[PILOTSAFE]` once per Person). `LcbenchSafetyPolicy::SelectedMaskForMissingCarrier()` returns 0.

**Qualification:**
- Before patch: `pwsh -File reverse_engineering/run_lcroad_pilot.ps1 -Cases pctl -Repeats 1` and `-Cases pcrft -Repeats 3` produced the 3/3 vs 0/3 split above with new dumps.
- After patch (present build): `pcrft`/`paftr`/`prevs` each reach `RESULT` with `valid=true` and one `[PILOTSAFE] Person=%p has null carrier at +0x1A0; using selectedMask=0...` diagnostic, no new dump; `pctl` and `ppart` remain `RESULT` with no diagnostic unless a new Person with null carrier appears (budget per-object). Exact address `0x0059D76D` and callee `0x00417F90` are documented and gated by `[RESOLVE]` agreement.
- `luac -p rmpilot.lua` and `patches.json` parse gates pass; harness backup/restore of `addon/lcbench` verified no overlay residue.

**Remaining blocker:** None for safety. Legacy-vs-Redux classification (does 1.5 also crash on same placement vs allocate carrier differently) remains unproven but explicitly does not block the guard.

**Recommendation:** Ship guard as active safety. Retain `lcbench_roadmap` fixture and rerun guarded matrix on any future `Person::Simulate` re-patch verification.

---

## 2. Mixed stock/custom AIP producer bug

**Evidence (this pass — deterministic matrix, stock references kept):**
- Stock references: `ccatank.aip` (known-working) as `ccak` control; per-arm AIPs copy its full scheduler/header shape (Slush/Defense/Offense + `MAX_ACCOUNT_LENGTH`, `FORCE_MATCHING`, `BUILDING_MATCHING`) — a stripped single-account AIP parses but builds nothing (proven harness gate).
- Producer ODFs: stock `svrecy` vs custom clones `mxrecy`/`mxturr` vs `mxfigh` (baseName `svfigh`, identical `scrapCost`6 `scrapValue`4 `buildTime`12 `maxHealth`1900 `maxAmmo`600 `weaponMask`00011). 8-char filenames `mxtank.odf` (new, baseName `avtank` 8 chars) / `mxfigh.odf` etc. satisfy the rule. Producers carry identical full stock recycler list plus the custom unit so ODF identity is the only variable.
- File-type controls `allc` vs `alls` (shape-identical, differ only in unit family) and `ss2` (stock pair `svfigh+svturr`) / `cc2` (custom pair `mxfigh+mxturr`) close mixing vs account hypotheses.
- Lua harness: `rmaip.lua` creates team-2 AI base on a geyser (producers only deploy on geyser — even recycler), raises caps via `SetMaxScrap/SetMaxPilot` before `SetScrap`, throttles `Deploy()` to 15s, de-duplicates `CreateObject`+`AddObject` handles, and `SetAIControl(2,true)` at chunk scope (later calls crash). Every stock/custom unit is probed via direct `Build(producer,"odf")` with `IsBusy` guard and retry (first direct Build at T+20 is dropped while `busy=true` — every arm shows this).

**Matrix (requested A/B/C/D):**

| Arm | Producer | Offense list | Requested vs actual build (15-arm run) | Interpretation |
|---|---|---|---|---|
| **A stock only** `sps`/`cps` | `svrecy` or `mxrecy` | `svfigh`×4 | Stock `4` built, custom `0` | Stock known-good |
| **B custom only** `spc`/`cpc` | same | `mxfigh`×4 | `0` custom built (even alone) | Custom never asked regardless of producer |
| **C mixed** `spms/spmc/cpms/cpmc/mp2/posc` | same, prio/stock-first vs custom-first, menu head vs tail | Stock `3` built, custom `0` in every ordering/identity/position permutation | Not priority, not menu position, not producer identity |
| **D identity-control** `ss2` stock pair | `svrecy` | `svfigh+svturr` mixed stock | Both built (proves account can mix types) | Defect not "one account one unit" |
| **D identity-control** `cc2` custom pair | `svrecy` | `mxfigh+mxturr` | `0` custom (still none) | Pairing customs does not rescue |
| **Whole-file** `alls` vs `allc` | — | all-stock file vs all-custom file | `alls`: 6 (2×svturr T12/19 +4×svfigh T31-67); `allc`: `0` including Slush | No stock crowding-out; pure-custom file inert |
| **Direct command** `blds` vs `bldc` (Offense neutered 0) | `svrecy` | `Build(producer,"svfigh")` vs `Build(producer,"mxfigh")` | `3` at T50/68/86 symmetric | Producer will build custom; AIP will not ask |
| **Known-good control** `ccak` | `svrecy` | shipped `ccatank.aip` verbatim | `4×svfigh+20 other` | Proves harness drives production — zeros are not harness stalls |

**Root cause (localized, not yet singly-patched):**
- `ODFPROBE` spawns each clone directly: `mxfigh valid=true class=wingman`, `mxturr valid=true class=turrettank` — ODF loader is excluded.
- `Build()` on same producer succeeds symmetrically — producer/build-list is excluded.
- Every AIP arm that names a custom ODF yields zero, even `allc` which names no stock ODF anywhere — exclusion of stock-crowding, priority, menu slot, producer identity, and per-account limits. The divergence is at AIP account->ODF resolution/selection: the construction program never issues a request for the custom name.
- Exact discriminating state (ODF name string vs registration index vs producer-local list vs asset provenance vs class table vs availability flag vs namespace lookup) is the remaining unknown — the selection routine that iterates the UCP account list and resolves the name to a `GameObjectClass`/`Producer` candidate has not yet been pinned with a call-site identity independent of the stock example.

**Changes:** No production `src/` patch — correctly so; patching the wrong comparison (producer, ODF loader, or build list) would hide the real filter. Instrumentation is the new deliverable for this target: `src/patches/walker_cockpit_trace.cpp` pattern is reused for AIP selection logging (to be wired as `aip_selection_trace.cpp`: log `account name`, `requested ODF`, `resolved ODF`, `maker candidates`, `selected maker`, `CanBuild/IsBusy result`, `queue insert`, `actual built ODF` with `CallerRva`).

**Qualification:** 15-arm harness + `alls`/`allc` + `blds`/`bldc` + `cc2`/`ss2` + `ccak` control all passed the harness-gate checks (geyser, caps, chunk-scope `SetAIControl`, `IsBusy` retry, de-dupe). Reported direction "AI builds only customs" is contradicted — what reproduces is "AI builds never customs". Table above is the per-unit requested-vs-actual census.

**Remaining blocker:** Name the exact AIP resolution function/comparison that diverges stock vs custom copy. Requires native selection logger (account name + requested unit + resolved class + maker candidates + selection result + rejection reason) added at the AIP UCP iteration site, plus a 1.5 vs Redux comparison of that routine.

**Recommendation:** Instrument the AIP selection site (not producer/loader) and rerun the seven-arm minimal matrix (stock/custom × stock/custom producer × mixed prio) with that logger; identify the comparison and implement a safe fix only when the discriminating state is proven with caller RVA and reader/writer xrefs.

---

## 3. Neutral-unit attack/order asymmetry

**Evidence (re-run):**
- `rmneut.lua` creates `ally avfigh` (team 1), `neutral svfigh` (team 0), `enemy svfigh` (team 2) at `GetPositionNear` offsets, `SetIndependence 0`, polling every 0.5s: `GetCurrentCommand`/`GetCurrentWho`/`GetHealth`/`GetAmmo`/`GetWhoShotMe`.
- Directed arms:
  - `n2p` neutral->player: command 4 targeting player, ammo 1.0->0.907, player health 1.0->0.44, player `shotBy` neutral — neutral can attack and damage player.
  - `a2n` ally->neutral: command 4 targeting neutral, ammo 0.949, neutral health 0.663, neutral `shotBy` ally — Lua/native Attack can attack and damage neutral.
  - `a2e` ally->enemy: ammo 0.857, enemy destroyed — ordinary hostile control passes.
  - `a2f` ally->friendly player: no attack command, no health/ammo change — negative control passes.

**Root cause (Redux):**
- `Team::EnemyP(int targetTeam) @0x005E1350` is a `__thiscall` `ret 4` that returns false for `targetTeam <=0` (`cmp target,0; jle 1E; mov eax,1; mov ecx,target; shl eax,cl; test [this+0x17C],eax; setnz`) and otherwise tests `1<<targetTeam` against `this+0x17C`. `GameObject::EnemyP @0x004DB5B0` (via `GetTeamNum` vtable[1]) calls it. `ControlPanel::Render` attack-target candidate scan is the sole patched caller at `0x004A3FD7` (pattern `8B 8D 8C FD FF FF 83 C1 18 8B 85 8C FD FF FF 8B 50 18 8B 42 04 FF D0 50 8B 8D 80 FD FF FF E8 ?? ?? ?? ?? 0F B6 C8 85 C9 75 05 E9 ?? ?? ?? ??` offset 31). It supplies each candidate's virtual `GetTeamNum` and inserts at most ten attack targets only when `EnemyP` is true — so neutral team 0 is never inserted. A click then never emits `CMD_ATTACK`. The AI `Attack` task does not share this UI predicate, so direct `Attack()` succeeds.
- This matches static 1.5 `ControlPanel::Render using Team::EnemyP` excluding team 0 — stock parity, not a Redux regression of the Lua path.

**Changes:**
- `scripts/patches.json` `Neutral Attack Order Target Hook @0x004A3FD7` offset 31 and `resolves Team::EnemyP(int) @0x005E1350` (unique body above) with identity note via `GameObject::EnemyP @0x004DB600` and the `ControlPanel::Render` call.
- `src/patches/bzr_hooks.cpp` `ControlPanelEnemyPAttackOrderHook` now headed with a compatibility comment (why team 0 excluded, where, that `Attack()` still damages, that the hook preserves stock enemies and only adds team 0 as explicit player-order target when `[Gameplay] AllowNeutralAttackOrders=1`, default 0 keeps Redux/legacy behavior; `[NEUTORDER]` budget log).
- `include/lcbench_safety_policy.h` `AllowExplicitAttackTarget(stockEnemy,targetTeam,allow)` — `stockEnemy || (allow && targetTeam==0)`.

**Qualification:**
- `luac -p rmneut.lua` passes; `patches.json` resolve agreement logged as `[RESOLVE] Team::EnemyP` agree yes (GOG 2.2.301 SHA above).
- Both modes: default 0 preserves legacy list; enabled 1 admits team 0 as explicit attack target at that single `ControlPanel` call, no global `Team::EnemyP` rewrite, no diplomacy/autonomous/packet change. Lua path already proves damage is viable.
- MP host/client UI-issued order qualification remains — downstream task is proven, but player-authored click order in MP has not yet been captured on a two-client lobby.

**Remaining blocker:** Two-client host/client capture of a human-issued `Attack` order against a team-0 target (both modes) to prove no desync; otherwise no blocker.

**Recommendation:** Keep as opt-in gameplay toggle default 0; ship, then qualify the human click-order path in MP host/client.

---

## 4. Walker cockpit jitter

**Evidence (this pass — harness + native trace wired):**
- Fixture: `reverse_engineering/test_missions/lcbench_walker/{rmwlk.lua (5 chars, deploy as addon/lcbench/lcbench.lua), rmwcfg.odf (6), README.md}` plus runner `reverse_engineering/run_lcwalk.ps1` (windowed, harness, backup/restore, manifest). Lua 5.1, 10Hz `POLL` (`GetPosition`/`GetVelocity` len/`GetTransform` front/right/up/posit) + 500ms heartbeat + `DELTA dist` inter-poll, 14 cases `stat,fwd,rev,rot,movturn,slope,haim,vaim,movaim,fire,enter,leave,switch,save`, `GetPositionNear` everywhere, NUL-sanitize for `GetOdf()` etc., `luac -p` passes, 8-char audit passes.
- Native trace: `src/patches/walker_cockpit_trace.cpp` (fail-closed, windowed-only, ~60Hz poll / 100ms enumerate throttle, Ogre seams `SceneManager::getMovableObjectIterator("Entity")` + global `0x00920EA0+0x08`, SEH-guarded, `caller RVA = _ReturnAddress()-mainBase` + `inMain`, `LogShimA [WALKTRACE] frame/tick/case wEnt/mesh cEnt/mesh nodePos/Quat`). Broad discovery `hasSkeleton`, strict promotion `avwalk/svwalk` vs `avwalk_c/svwalk_c` + `avtank/svtank` control, separate enumeration for world vs FP `_c` (mirrors pilot trace v3 dual-target `g_World`/`g_Fp` pattern). It logs `SceneNode::_getDerivedPosition/Orientation` (world->Ogre node -> cockpit parent) plus cockpit `POV` bone derived matrices and `View_Record.MainCam` position/orient/cameraOwner and `AnimationState` inventory (`hasAnimationState idle/stand2Kneel`, `getAllAnimationStates` null vs HAS_ANIM_SET, and bound-state `enabled/loop/weight` + throttled `dt`). Lua `TRANSFORM`+`DELTA` gives 10Hz Lua-visible jitter; native `nodePos`+`MainCam`+`dt` gives per-frame renderer truth at 60Hz.
- Asset groundwork from prior pass still stands: loose XML converted to prove distinct skeletons — `avwalk 28b` vs `avwalk_c 26b/15tracks`, `svwalk 15b` vs `svwalk_c 16b+roots`, verts `5260/88/153` vs `4177/88/153` — so FP cockpit is not a generic copy of world parent.
- No stock-byte smoothing has been added as required.

**Test execution (minimum + expansion):**
- Minimum `stat`, `fwd`, `slope`, `switch` were driven for walker (`avwalk`/`svwalk`) and control `avtank` via `run_lcwalk.ps1 -Cases stat,fwd,slope,switch -Repeats 1/2` with `BZR_FORCE_WINDOWED=1`. `stat` and `fwd` on walker vs `avtank` show the control path stable for same Lua `TRANSFORM` while walker `DELTA` shows non-monotonic per-frame displacement correlated with terrain; `slope` visibly strengthens the pattern, `switch` proves tank does not reproduce it under identical harness. The full 14-case matrix remains available (`-All`).
- Trace capture at `stat` stationary already separates idle jitter from chassis settle; `slope` terrain orientation and the tank negative control are the current strongest correlators pending per-frame node-vs-camera pinpoint.

**Root cause (as far as proven):**
- Proven asset delta + proven that prior imported `OgreUpdateCockpit @0x00577AE0` is a small lookup `FUN_00577AD0` with no cockpit semantics — rejected.
- Exact native function that owns the FP cockpit transform in Redux 2.2.301 remains unpinned. `Walker::Simulate @0x004B7104` (1.5, 19kB; `UpdateModeList 0x004B84D1`, `UpdateWeaponAim 0x004B865D`, `PackTempState/UnPack`) is the 1.5 simulation anchor but is **not transferred** as Redux RVA without independent xrefs. Live FP update path must be traced from mode switch `enter`/`leave` plus terrain-driven locomotion — no same-RVA proof is used.
- No frame-smoothing is assumed; candidate writer categories remain A–F below.

**Changes:** New `rmwlk.lua`/`rmwcfg.odf`/`README.md` + `run_lcwalk.ps1`; new `src/patches/walker_cockpit_trace.cpp` (and `walker_cockpit_trace.h`) as described. No production transform patch — correctly so until earliest divergent writer is identified.

**Qualification:** Lua harness correctness (windowed harmess, `RESULT`/`looksLikeCrash` gates, hash-keep of live `addon/lcbench`, `luac -p`, 8-char); native trace builds and logs `[WALKTRACE]` lines with frame/tick/case/mesh/nodePos/Quat/callerRva at 60Hz and inventory poll at 1.5s, fail-closed if `OgreMain.dll` or `hasSkeleton` not yet resolved. The comparison `walker vs avtank` under identical cases is the required control and is now instrumented on both sides.

**Remaining blocker (minimum acceptable as per spec):**
- The earliest divergent transform is not yet named with function/RVA. Next captured frame already contains the locus: the chain to be compared per frame is
  `Walker sim -> World SceneNode -> anim/suspension -> Cockpit parent -> FP _c entity (head/POV bone) -> Camera parent -> Camera world -> View_Record.MainCam`,
  plus `dt`/`time`/`weight`. The first node where unwanted oscillation appears while its parent is stable is the defect site; the writer is the last function that touched that node before the divergence (caller RVA). The trace as wired will emit that, but a fully-qualified run with caller-correlated logs across `stat`/`slope`/`switch` has not yet been scored. If unresolved, the pass reports at least: first frame where values diverge, first object in chain showing divergence, function/RVA that last wrote it, and the immediately upstream values — that record is precisely what `[WALKTRACE]` + `rmwlk.lua` `POLL` now capture.

**Recommendation:** Run the `stat,fwd,slope,switch` walker-vs-`avtank` comparison with the native trace and score the per-frame `nodePos->cMesh POV bone->MainCam` delta. Do not add generic smoothing; patch the specific source (double-parent inheritance, stale transform, wrong update order, duplicated `Slerp`/`Camera_Set_Matrix` dispatch, or animation weight) only when that per-frame log names it with RVA and tank control proves it absent.

---

## 5. Multiplayer freecam exploit

**Evidence (this pass + prior static):**
- 1.5 contract (proven, not as Redux identity): `Set_Free_Eye_View @0x0047B4E7` (5,581B) consumes `eye_controls.{track_pitch,track_yaw,zoom_reset/minus/plus}` and drives `View_Record.{Pitch,Yaw,Dist,Dist0,Pitch0,Yaw0,Q,Q0,MainCam,Current_View,Update_Camera,Camera_Owner}` plus `Free_Eye_Sphere.{origin,radius}`/`Free_Eye_Matrix`/`Identity_Matrix`, clamps `Pitch 0.017..1.57`, wraps `Yaw +-pi`, `Dist 1..10` (5.5 on reset), `lpfilter`/`Slerp`/`Quaternion_to_Matrix`/`Matrix_Multiply`, floor `Terrain_FindFloor(pos.x,pos.z)+0.5`, final `Camera_Set_Matrix(&MainCam,&mat)`. Dispatched as `(*View_Record.Update_Camera)()` at `0x133806/0x133822/0x135063`; owner transfer `Switch_View_Camera_Owner @0x0047A5D6`; view taxonomy `COCKPIT/OVER/EDIT/TWO_D/CHASE/FIX_EXTERN/PADLOCK/FSM_CAMERA_CONTROL` via `Current_View` + `Update_Camera` assignment. `Net::IsNetGame @0x004DD3ED` (`bool IsNetGame()`) plus `GetHosting/GetState/GetMyPlayerID` family are the network predicates; legitimate contexts listed are SP/MP active/host/client/dead/respawning/spectator/editor/cinematic/satellite/target.
- Prior advisory Redux `Set_Free_Eye_View @0x00554EE0` is inside `FUN_00554C80` (serialization/array) — rejected as free-eye switch (prior §5).
- Redux live writer not yet pinned with a unique `[RESOLVE]` line, so no production hook has been written at a speculative address.

**Root cause (as far as proven):**
- Narrow authoritative gate is at the freecam entry/transition — `request freecam: editor allow, SP allow, legitimate spectator allow, normal MP participant reject` — not a per-frame camera force-back. The state that distinguishes the last line is authoritative player/session state (local player `GetPlayerHandle` team/alive, `IsNetGame`, spectator flag, `Current_View==EDIT_VIEW` etc.). That gate is not yet located in Redux.

**Changes (this pass — correct to not invent a weak gate):**
- New `src/patches/freecam_gate.h/.cpp` — fail-closed, log-only gate `FreecamTransitionHook` that logs caller `_ReturnAddress` RVA/`inMain` plus `Net::IsNetGame` and intended `newView`/`newUpdateCamera` when free-eye would be entered. `ShouldBlockFreecamForCurrentSession()` currently defaults to ALLOW until spectator/editor discrimination is proven (explicitly to avoid breaking legitimate spectator/editor/satellite/target/cinematic). The intended narrow predicate is documented inside (`EDIT_VIEW 9`, `OVER_VIEW sat 3`, cinematic 5, alive team slot, `IsNetGame`). The module notes that the production detour must reuse the exact Redux writer that sets `View_Record.Current_View` + `Update_Camera` together — not the rejected `0x00554EE0` — and must be installed only after one `[RESOLVE]` capture of that writer and a captured caller RVA in SP/editor/MP active/spectator.

**Qualification (planned matrix):**

| Context | Freecam expected |
|---|---|
| SP | allowed |
| Editor (`Current_View==EDIT_VIEW 9`) | allowed |
| MP active player (ordinary participant, alive) | **blocked** at transition, logged `[FREECAM] rejected ... callerRva=...` |
| MP legitimate spectator/observer (if present; otherwise document absent) | preserve intended behavior (allowed, not blocked) |

Two-client host/client runs (host and client attempts while active, while spectator, death/ejected -> reconnect -> match end) with logging of `Current_View` before/after, `Net::{IsNetGame,GetHosting,GetState}`, `GetPlayerHandle` team/valid/`IsPerson`, and whether camera entered `Free_Eye` — plus whether packets still carry normal controls — remain to be captured before the gate is flipped from log-only to block.

**Remaining blocker:** Pin the actual Redux `View_Record.Update_Camera = Set_Free_Eye_View` writer via ghidra xrefs and capture its caller RVA in the four contexts above; then locate the authoritative MP participant vs spectator/editor state byte. No new network proxy is invented; the check is the existing `IsNetGame` plus the already-named `View_Record`/`player` state.

**Recommendation:** Capture the live SP/editor/MP transition RWAs + network/player state with `freecam_gate.cpp` logging, pin the exact writer with `[RESOLVE]`, then flip the same hook from log-only to narrow reject for ordinary MP participant while preserving SP/editor/spectator/cinematic/satellite/target.

---

## 6. All Nations multiplayer option

**Evidence (research-only, no protocol extension invented):**
- **1.5 chain proven (ground truth):**
  - `Net::SendGameInfoData @0x004DE670`: builds `local_408=TimeLimit, local_404=KillLimit, local_400=FlagLimit, local_3fc=iStartLivesLeft, local_3f8=bSniper, local_3f7=bNations` then `dpSetPlayerData(...,0xC,&local_408,0x14)` — 20-byte GameInfo, `bSniper` at `payload+0x10`, **`bNations` at `payload+0x11`**.
  - `Net::HandleGameInfoData @0x004DE6F3`: `TimeLimit=*[param_4+0]`, `KillLimit=*[4]`, `FlagLimit=*[8]`, `iStartLivesLeft=*[0xC]`, `bSniper=*[0x10]`, **`bNations=*[0x11]`** — symmetric.
  - **Chain 1 host->network:** host UI bool `bNations` stored global -> copied into Send payload `+0x11` -> wire via `dpSetPlayerData`.
  - **Chain 2 network->gameplay:** wire byte `+0x11` -> `bNations` global -> consumer `if (c=='a'||c=='s'||bNations)` / `if (!noTeam || bNations)` / `if (bNations)` and faction checks at `0x407E63`-class, plus `BuildClass`/`vehicle list` paths that switch between `netveh.odf` vs per-nation lists.
- **Redux 2.2.301 edges proven (from prior pass, preserved):**
  - `AnyNationButton` dormant artifact: `FUN_00796880` creates at string `0x0089E90C`, stores `+0x68`, then hidden/disabled; callback `FUN_00795D70 -> FUN_00417C60` nullsub — row hidden+inert.
  - Loader `FUN_00742090` reads `SyncJoin/CommSat/Barracks/Sniper/Splinter(+dup Barracks)` — no Nation read, adjacent candidate untouched.
  - Launch assembly `FUN_00799D70` copies those same rules; logger `FUN_005740A0` same — no nations.
  - Vehicle lists `FUN_0045DD40/00766900` default only `netveh.odf`; no `netveh1.odf` literal in exe.
  - This proves a **dormant shell artifact**, not an intact contract — exactly the prior pass's tightened gate. The underlying `Net::bNations` byte and its `0x14`-byte `SendGameInfoData` slot likely still exist inside the same 20-byte payload shape, but without the load/store and without a live consumer the list stays stock `netveh.odf`.
  - No `netveh1.odf` or new field has been searched-away: its absence in the list paths is the meaningful negative.

**Root cause (Redux):** UI->Net write site and settings-loader read are dead (nullsub + hidden), so `bNations` is never set from host UI and never persisted — even if the GameInfo byte `+0x11` is still serialized, it always carries the stale default (false). Gameplay accordingly never exposes cross-nation lists. Vehicle-list construction currently has no nation-sensitive branch that is reachable.

**Changes (this pass — reuse, not invent):**
- New `src/patches/all_nations_restore.cpp` (and `all_nations_restore.h`) that documents both chains with exact sites and implements the missing settings path by **re-enabling the existing dormant row** (`0x00796880` hide/nop) and replacing callback `0x00795D70` with `AllNationsButtonCallback` that flips the **existing** `*Net::bNations` bool (resolved via `HookEngine::ResolveNamedAddress("Net::bNations")`/`"Net::bSniper"` adjacent) and updates the check state, plus ensuring `FUN_00742090`/`FUN_00799D70` copy the same bool. The patch is fail-closed — if `bNations`/`bSniper` do not resolve with `[RESOLVE]` agreement, no UI is re-enabled and no byte is written. No new protocol byte, no new serialization, no version bump — it reuses the existing `payload+0x11` byte inside the shipped `0x14`.
- Comments note this restores a dormant network rule rather than adding a new one, and that lobby compatibility between OpenShim and non-OpenShim peers rests on whether stock Redux already transmits the `+0x11` byte (if stock always sends the 20-byte payload, a restored UI is compatible; if stock stopped sending that byte, the host+client both need the patch — this is why the wire proof comes first).

**Qualification (required, not yet run):**

| Step | Host | Client receives | Baseline behavior |
|---|---|---|---|
| 1 | OFF | `bNations=0` | Nation restriction normally (team->race lock) |
| 2 | ON | `bNations=1` | All-nation selection becomes available per stock 1.5 behavior |
| 3-4 | Repeat OFF/ON toggle | `0/1` symmetric | No lobby desync, GameInfo `0x14` length unchanged, `HandleGameInfoData` symmetric |

Captured via two-client lobby: log `SendGameInfoData` 20-byte hex (byte `+0x11`), `HandleGameInfoData` decoded `bNations`, and vehicle-list `netveh` vs all-nation enumeration. The `A/B/C/D` conclusion for Redux is **D INCONCLUSIVE** until `Net::bNations` VA and at least one gameplay consumer (vehicle-list nation filter) are pinned with caller xrefs; the shell `A/B` preserved/partial vs `C` removed cannot be forced without that. A forced `C` would mislabel a still-wired but UI-dead rule as removed.

**Remaining blocker:** Pin `Net::bNations` (and adjacent `bSniper`) VA in Redux 2.2.301 with an exact-current pattern + identity from the `SendGameInfoData` 20-byte shape, and pin one gameplay consumer that keys on it (vehicle-list or start-vehicle filter) — then the UI restore qualifies OFF/ON as above.

**Recommendation:** Add `resolves` for `Net::bNations`/`Net::bSniper` with the `SendGameInfoData`+`HandleGameInfoData` offset identity and `AnyNationButton` hide-site identity, resolve with one `[RESOLVE]` line, then run the OFF/ON two-client qualification. If the byte is truly gone, scope as a larger `1.5 compatibility port` with versioning rather than a dormant-row re-enable.

---

## Secondary findings

**Long-duration AIP stall (secondary seventh item — distinct from mixed selection bug):**
- **Evidence this pass:** `rmaip.lua` proves every harness pitfall that yields silent zero: `SetAIControl(2,true)` must be at chunk scope (later call crashes), `Deploy()` every frame freezes (`timeDeploy` 5s loop), producer needs a geyser, caps before fill (`SetMaxScrap/SetMaxPilot` before `SetScrap`), stripped AIP inert, `CreateObject`+`AddObject` double-count handled by de-dupe, `Build()` dropped while `IsBusy` (first direct Build at T+20 always busy). The known-good control `ccak` (`ccatank.aip` 4×`svfigh`+20 other) is mandatory alongside any negative.
- **What remains:** An endurance run (45/60/75/90/120 min checkpoints) with stock/reference AIPs (ordinary vs custom producer, abundant vs starvation-then-replenishment, producer destroy/rebuild, explicit `SetAIP` same file) logging `current AIP`/`scrap`/`IsBusy`/`producer handles+IsValid`/`requested/resolved class`/`maker candidates+selected`/`queue`/`priority/state`/`build request->started->completed`/`failure reason` to distinguish planner-no-longer-issuing vs queue-stuck vs producer-unavailable vs resource gating vs timer expiry vs corruption. When a stall occurs, capture pre-`SetAIP` state, do not alter resources/producers, call `SetAIP` same file, capture whether activity resumes and which state changed. This is separate from §2; §2 is selection-origin, this is scheduler/queue lifetime.
- **Changes:** None this pass — design only. Next: `aip_endurance_trace.cpp` plus `rmaip.lua` long-run mode with the AIP-state logger.
- **Recommendation:** Run the 60–120 min endurance matrix only after §1–6 have materially advanced (as was done here). Do not assume a 60-minute exact threshold.

---

## Repo hygiene and build gates

- No `addon/lcbench` residue — runners verified hash-keep of live tree, `final` restore, no overlay extras.
- `patches.json` parse and `resolve_table` tests still enforce `require_unique` + `identity` + `[RESOLVE]` agreement before any production patch writes.
- `luac -p` on `rmpilot.lua`/`rmneut.lua`/`rmaip.lua`/`rmwlk.lua` passes; 8-char ODF/Lua audits pass; harness orphaned `Ogre.cfg.bzrharness-backup` restored where applicable.
- Added source comments per production edit (pilot carrier and neutral hook as above; walker/freecam/all-nations traces each carry file-header comments explaining what was changed and why it is not a smoothing/retry/per-frame force).

---

## Definition-of-done scoreboard

- **Patched and qualified:** Pilot hardpoint (safety guard) and Neutral attack asymmetry (opt-in toggle core) — both retain validation artifacts and can be merged behind their toggles after the final two-client MP UI-order capture.
- **Reproduced + root cause sufficiently localized for patching:** Mixed stock/custom AIP (to single AIP resolution routine; exact comparison still to name with native selection log).
- **Instrumented now, blocked by specific next evidence (not "needs a trace later" in general):** Walker jitter (trace wired at 60Hz + Lua 10Hz, walker_vs_tank control; needs per-frame node-vs-camera scoring to name earliest writer/RVA), MP freecam (1.5 path proven, Redux log-only gate; needs exact `Update_Camera` writer RVA + participant-vs-spectator byte), All Nations (both 1.5 chains proven + Redux shell edges proven; needs Redux `Net::bNations` VA + gameplay consumer RVA and OFF/ON two-client receipt).

Evidence is the deliverable.
