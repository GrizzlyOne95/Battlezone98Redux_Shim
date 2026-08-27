# Battlezone 98 Redux Historical Patch / Bug Regression Sweep

**Date:** 2026-08-27  
**Target:** Battlezone 98 Redux 2.2.301 + OpenShim/EXU/community-server stack  
**Purpose:** turn surviving official patch notes, known-issue posts, community reports, and later technical guides into explicit regression candidates.

This is a **source audit**, not a claim that every historical report still reproduces. Items are classified by evidence strength and whether they deserve a current OpenShim regression test, reverse-engineering pass, content audit, or no action.

Scott ("Herp") is one person. His Steam review, later forum posts, workshop fixes, and the detailed technical grievance correspondence are treated as one community source stream, not independent corroboration.

## Evidence classes

- **OFFICIAL** — Rebellion/Big Boat patch notes, developer posts, or Steam news.
- **OFFICIAL-ARCHIVE** — official changelog preserved by a third-party/store mirror when a first-party page was not found.
- **COMMUNITY-TECHNICAL** — specific reproduction from experienced community/modding sources.
- **COMMUNITY-GENERAL** — player symptom report; useful lead but insufficient by itself for implementation.

A historical `Fixed ...` line is especially valuable as a **stock invariant**: OpenShim should avoid reintroducing it while touching adjacent engine paths.

---

# 1. Primary sources

## 1.1 Official launch known-issues thread — 2016-04-18

Source:  
https://steamcommunity.com/app/301650/discussions/0/368542844485325802/

Rebellion explicitly listed these launch-era defects:

- process can remain running as a **phantom program after shutdown**;
- changing windowed/fullscreen + resolution can make edge clicks minimize the game;
- switching to unsupported fullscreen resolution can leave the game unresponsive;
- Xbox One controller mapping can be wrong on some PCs;
- intro movie can overlay the MP lobby when an invite is accepted immediately after launch;
- MP can fail to launch with **wait on host**, particularly after repeatedly entering/leaving lobbies;
- multiplayer-lobby audio can deteriorate;
- Big Picture / Steam Controller launch could crash unless Steam Overlay was disabled (developer reply in the same thread);
- additional reports include black-screen rendering, severe input lag, reticle jitter, choppy audio, and startup/overlay interactions.

### Current action

Treat the first six as explicit historical lifecycle/network/input regression candidates. Several OpenShim systems now touch exactly these areas: shutdown/detach, fullscreen/activation behavior, raw input, renderer startup, multiplayer lobby/network state, and service integration.

Priority additions:

1. **Shutdown phantom-process regression test.** Close from menu and from gameplay after renderer/network activity; verify process exits and OpenShim threads/handles are gone.
2. **Fullscreen/resolution activation matrix.** DX9/DX11; windowed/fullscreen; Alt+Tab/Alt+Enter; supported/invalid resolution fallback; custom-campaign mission-end focus transition.
3. **Lobby state churn.** Repeated create/join/leave before launch must not leave a `wait on host` or stale lobby-state dead end.
4. **Invite-during-startup** should not allow movie/shell/network state to overlap incorrectly.

---

## 1.2 Patch 2.0.117 — 2016-04-19

Source class: **OFFICIAL-ARCHIVE**. English changelog preserved at:  
https://mip.ali213.net/patch/55715.html

High-value historical fixes/invariants:

- failing a mission could incorrectly allow progression to the next mission;
- controller insertion during loading could crash;
- default key bindings could not be reassigned even after being freed;
- `PathDisplay` build menu could break after restarting a mission;
- mission text encoding fixes;
- producer terrain flattening was corrected to mark terrain changed;
- cockpit HUD clipping fixes;
- dynamic explosion geometry binding churn was reduced;
- known MP crash when a client Alt+Tabbed during load;
- known controller-removal crash in MP;
- intro movie/lobby overlap acknowledged.

### Current action

Add/retain regression coverage for:

- **campaign progression state:** mission failure must never increment/unlock progression;
- **mission restart UI lifecycle:** build/path display reconstructs correctly after restart;
- **terrain-change notification after producer/building flattening:** particularly relevant to AI pathing and HGT/HG2 work;
- **input hotplug during loading/gameplay** where feasible;
- **client Alt+Tab while MP map is loading**, because renderer/network lifetime work could expose this class again.

---

## 1.3 Patch 2.0.131 — 2016-05-03

Source class: **OFFICIAL-ARCHIVE**. English changelog preserved at:  
https://patch.ali213.net/showpatch/56329.html

Important fixes/invariants:

### Multiplayer/network/shell

- crash entering lobby when selected map triggered a conflict message;
- vehicle-selection error after restarting an MP game;
- failed-connect crashes;
- MP pause incorrectly opening game-over with no return to play;
- infinite loop when losing MPI;
- crash when client tabs out during MP load;
- various game-lobby crashes;
- friend invite problems, including invite immediately after game launch;
- Steam Workshop reliability improvements;
- MP map ability to override stock items without CRC conflicts when the map is not in use.

### Replication/gameplay

- **Popgun duplicating in multiplayer was fixed.** This is a particularly important historical analogue for current Splinter and Day Wrecker duplication investigations.
- Crossroads buildings not neutral was fixed.
- pilots ejecting from drone turrets in Training 1 was fixed.

### Rendering/input/animation

- game minimizing at certain resolutions;
- DirectX-assets crash while tabbed out;
- controller-related crashes;
- sniper/nav camera always forcing High graphics mode;
- pilot gun animation speed made frame-rate independent;
- pilot jump/fall/bail animations fixed;
- first-person jump horizon jolt fixed;
- HUD scaling/cockpit clipping fixes.

### AI/pathing

- A* pathfinding improved.

### Current action

**Promote these to current regression work:**

1. **Study the old Popgun MP duplication fix before patching Splinter/Day Wrecker.** Search the 2.0.131-vs-prior executable delta if binaries are available. It may reveal the exact authority/locality pattern the original developers used to solve a similar secondary-ordnance duplication bug.
2. **MP map/resource CRC isolation** belongs beside current mod-isolation work. Test that inactive map overrides cannot poison stock/other MP content.
3. **Camera quality-state preservation.** Sniper/nav/satellite cameras should not silently force a more expensive graphics tier or leave render state behind.
4. **Frame-rate-independent pilot animation** should be part of the current FP/world animation work acceptance suite.
5. **MP restart/lobby churn** should verify map list, vehicle selection, chat/status state, and lobby object lifecycle.

---

## 1.4 The Red Odyssey patch / 2.1.201 — 2016-08-24

Official Steam discussion:  
https://steamcommunity.com/app/301650/discussions/0/361798516965091211/

Also mirrored in the GOG changelog thread:  
https://www.gog.com/forum/battlezone_98_redux/new_patch_21201/post6

Mission fixes/tuning included:

- CH02 unlimited hunter spawning;
- CH03 howitzers/minefield behavior;
- CH04 retreat state;
- CH08 final VO timing;
- CH09 cover/wave/turret tuning;
- BD02/03/04/06 difficulty/spawn/startup changes;
- vehicle/cockpit/audio/model fixes;
- point-light / reverse-shadow fix;
- hauling behavior that allowed levitation.

### Current action

The detailed Scott ("Herp") report separately names later/unresolved problems in `BDMISN08`, `BDMISN11`, and `CHMISN05`. Do not assume the 2.1.201 mission pass solved all TRO regressions. Audit the public workshop patches for those three mission names and classify each as:

- bad Redux port/content;
- mission-script/data error;
- native engine regression;
- already fixed by current campaign work.

Also retain **reverse-lighting/point-light direction** as a graphics invariant because OpenShim now owns more lighting behavior.

---

## 1.5 Final 2.2.301 patch / "Big patch"

Official community patch thread/fix list:  
https://steamcommunity.com/app/301650/discussions/0/154644705026213561/

GOG 2.2.301 changelog mirror:  
https://www.gog.com/forum/battlezone_98_redux/new_patch_21201/post6

Steam News announced the substantial final PC patch and its multiplayer/mod/shader changes:  
https://steamcommunity.com/app/301650/allnews/

High-value stock fixes/invariants:

### AI / gameplay

- **AI wandering off-map when interrupted by a sub-task while following a path**;
- units de-cloak in all cases where they lose a pilot;
- AI team crash when team 2 has a null AIP;
- craft bumper/contact alignment reduced spurious ground hits on large vehicles;
- repeat hopping animation corrected;
- mission-specific pilot/recycler/portal lifecycle fixes.

### Terrain / rendering

- Great Pyramid (`multdm29`) grey lightning fixed;
- TRN lightning color fixed;
- PSSM/shadow system rewritten;
- low/medium shadow jitter fixed;
- cockpit shadows deliberately disabled to fix "wonky" cockpit shadows;
- **smoothing explicitly removed from Great Pyramid to restore the original stair-stepped terrain**.

### Multiplayer / mod loading

- custom server and low-level netcode introduced;
- password protected games;
- locked/launched/full games visible;
- `-disablemods` command-line option added;
- network connection issues/crashes addressed.

### Current action

These should become explicit invariants around current work:

1. **Path + subtask interruption:** build an lcbench AI fixture that follows a path, receives a temporary subtask/attack, then resumes without leaving playable terrain.
2. **Pilot-loss decloak:** snipe/eject/remove pilot from cloaked craft and verify cloak state on all relevant ownership paths, including MP.
3. **Null AIP team safety:** malformed/missing AIP assignment must fail safely rather than crash.
4. **Large-craft ground contact:** Recycler/large craft movement and placement should not regain false ground strikes after physics/position changes.
5. **Cockpit shadow policy:** current Enhanced/shadow work must not accidentally re-enable problematic cockpit self-shadowing unless deliberately requalified.
6. **Great Pyramid terrain:** use `multdm29` as a canonical no-smoothing regression map.
7. **`-disablemods` baseline:** preserve this while researching the broader CLI parser; it is a useful control case.

---

## 1.6 Official terrain design statement

Official Rebellion dev blog, 2016-04-07:  
https://store.steampowered.com/news/posts/?appids=301650&enddate=1460732810

The producer explicitly described Redux legacy-map conversion as automatically **upscaling and smoothing** old maps. The same post claimed the converted terrain retained the original terrain's size and shape.

The final patch later removed smoothing from Great Pyramid specifically to restore its original stair-step geometry.

### Current action

This materially strengthens the HGT/HG2 restoration case:

- smoothing was intentional policy, not accidental file corruption;
- the developers themselves later recognized at least one stock map where smoothing damaged intended geometry enough to remove it;
- compatibility mode should therefore treat no-smoothing conversion as a legitimate legacy-preservation target, not merely a user preference.

Use Great Pyramid as the first stock quantitative HGT-vs-HG2 comparison.

---

# 2. Current community technical sources

## 2.1 Scott ("Herp") review and detailed reports

Steam review:  
https://steamcommunity.com/id/herpmcderperson/recommended/301650/

Key items are tracked in `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md`:

- destruction chunks — fixed by OpenShim;
- jump-sniping — fixed/configurable;
- satellite fog of war — fixed/configurable;
- Day Wrecker remote duplicate/source detonation — open/high priority;
- `perceivedTeam` victim retaliation/break-cover — reopened;
- TRO named mission regressions — content audit;
- missing All Nations / Cloak Disabled — restoration TODO;
- Steam MP map-list behavior — fixed;
- netcode/disconnect behavior — partial/ongoing;
- no direct LAN/TCP-IP service path — community BZRNet project;
- stock crash rate — signature-based ongoing work;
- `Inst4XMission` save/load — fixed;
- multi-parameter CLI parser — open RE;
- HGT smoothing — compatibility restoration.

CCA mission 7 / gun-tower corroborating discussion:  
https://steamcommunity.com/app/301650/discussions/0/2292842508246127032/

This is the same Scott/Herp source stream, but it provides a public concrete mission reproduction for the retaliation problem.

---

## 2.2 Current comprehensive modding/known-issues guide

Source:  
https://steamcommunity.com/sharedfiles/filedetails/?id=3538294667

This guide is a valuable **candidate index**, but its entries must be checked against current OpenShim because several are now fixed.

### Already fixed / intentionally covered by OpenShim

- renderCount allocation crash;
- MagnetClass zero-range divide-by-zero;
- TRN line-ending/serialization problems;
- fixed-width/null-padded Lua strings;
- `ObjectiveObjects()` iterator wrapper/repair in EXU;
- jump-sniping;
- satellite visibility;
- satellite/F9 stale target camera;
- Earthquake/Dayquake save replay;
- cinematic FOV/zoom after satellite;
- Howitzer undeployed sniper retaliation;
- APC deploy with allied target;
- constructor remote-build-after-death;
- tug cargo save/load/start-state;
- Steam map-list refresh/jump;
- `Inst4XMission` save/load;
- destruction chunks.

### Already tracked as open / partial

- `weaponMask=00000` Follow crash;
- pilot hardpoint ODF ordering crash;
- custom campaign BMP crash;
- second editor-session crash;
- Shift-F9 editor task-mode crash;
- Shift-F10 placement regression;
- AIP custom/stock producer bug;
- minelayer first-hardpoint Lay Mines behavior;
- howitzer weaponMask behavior;
- neutral attack/order asymmetry;
- rare sniper/reticle misalignment;
- walker cockpit jitter;
- DX11 lifetime/render faults;
- terrain type-0/orientation deformation;
- animation looping/rate behavior;
- Splinter duplication/collision;
- Day Wrecker terrain-spire + duplicate detonation;
- MPI host leave;
- password invite;
- MP freecam;
- unrelated mod resource loading/duplicate materials.

### Additional candidates not to lose

These are mostly lower priority/content-facing, but should not disappear:

- stock NSDF Hangar animation behavior;
- unit hardpoint parenting/misalignment on moving geometry;
- CCA Golem reticle/hardpoint sway;
- NSDF Razor dim material;
- missing stock `bbcom2_n.dds` normal map;
- inconsistent/missing headlights and lamp bones;
- turret cockpit rotation inheritance issues.

Default classification: **content/asset audit first**, promote to OpenShim only if a native transform/material consumer is proven wrong.

---

# 3. Post-final-patch crash evidence

## 3.1 Ogre duplicate-resource crash after 2.2.301

GOG report dated 2017-05-25:  
https://www.gog.com/forum/battlezone_98_redux/new_patch_21201/post6

Reported Ogre exception:

`Resource with the name TI_2_DETAIL_ATLAS already exists`

The current community guide also documents duplicate material/resource names from unrelated mods causing crashes because Redux can load resources before the selected content actually launches.

### Current action

This supports the existing **resource isolation** roadmap item and should be a concrete acceptance case:

- install two inactive/selected mods with colliding Ogre material/texture/template names;
- navigate menus/categories that enumerate those mods;
- ensure unrelated resources are not initialized into one global namespace prematurely;
- fail closed with useful diagnostics rather than Ogre `ItemIdentityException`.

OpenShim material-conflict guards are mitigation, not proof that the underlying resource-loading scope is solved.

---

# 4. Historical bug-fix invariants worth adding to automated/manual regression

The following were easy to miss because stock Redux itself fixed them before 2.2.301. They should nevertheless be preserved while OpenShim modifies adjacent systems.

| Invariant | Why it matters now | Suggested fixture |
| --- | --- | --- |
| Failed mission does not unlock next mission | campaign/progression work | fail a stock mission intentionally; inspect progress state |
| Restarted mission reconstructs PathDisplay/build UI | lifecycle/UI patches | restart mission after build menu usage |
| Producer terrain flattening invalidates terrain/path data | HGT/pathing work | build on uneven terrain; issue AI path through changed cells |
| Popgun MP does not duplicate | current Splinter/Day Wrecker duplication | two-PC host/client Popgun baseline + distributed identity trace |
| MP map inactive stock overrides do not create CRC conflicts | mod isolation/MP | map A overrides stock ODF, host map B |
| MP pause returns to active gameplay | shell/network state | pause/unpause host/client |
| Losing MPI does not infinite-loop | MPI ownership/lifecycle | deterministic loss/host exit cases |
| Client Alt+Tab during load does not crash | DX11/lifetime | repeat Steam/GOG renderer matrix |
| Sniper/nav camera preserves intended graphics tier | render profile/camera | compare profile before/after camera activation |
| Pilot animation timing independent of FPS | new animation APIs | lock 30/60/120+ FPS and compare clip phase/time |
| AI resumes path after subtask without leaving map | AI tuning/resolver work | controlled path + temporary attack/subtask |
| Pilot loss always clears cloak where stock intends | cloak restoration work | snipe/eject/kill pilot, SP + MP |
| Null/missing AIP team does not crash | AIP extensions | team 2 nil AIP fixture |
| Cockpit shadow policy remains intentional | Enhanced PSSM work | first-person cockpit under PSSM, stock/Enhanced comparison |
| Great Pyramid keeps stair-step terrain in compatibility mode | HGT/HG2 work | `multdm29` HGT/HG2 quantitative comparison |
| Shutdown does not leave phantom process | loader/thread/lifetime work | repeated start/exit loop after network + renderer use |

---

# 5. New investigation leads from the sweep

## P0 / P1

### A. Popgun duplication archaeology

The strongest newly surfaced lead. Patch 2.0.131 explicitly fixed **Popgun duplicating in multiplayer**. Current OpenShim work is investigating Splinter and Day Wrecker duplication under multiplayer authority.

**Plan:** obtain a pre-2.0.131 executable and 2.0.131 executable if available, diff the Popper/secondary-ordnance/network create path, and identify the exact authority/locality change. Even if class layouts moved, strings/vtables/call-shape should help locate the producer.

### B. Shutdown phantom-process qualification

Official launch issue; directly relevant to current DllMain/thread-handle/shutdown hardening.

**Plan:** automated repeated launch -> enter mission -> enter/leave MP shell -> exit; assert process termination and collect any surviving thread/handle signature when it fails.

### C. Great Pyramid as canonical HGT smoothing control

Final patch itself removed smoothing on `multdm29` to restore the original geometry.

**Plan:** start the stock HGT/HG2 reconstruction study with this map because there is first-party evidence of intended stair-step preservation.

## P2

### D. 2.0.131 MP map CRC isolation regression

Current mod dependency/resource isolation work could accidentally change old MP override semantics. Add a deterministic inactive-map override test.

### E. AI subtask/path resumption

The final patch fixed off-map wandering after path-follow interruption. New AI tuning must preserve the corrected state transition.

### F. Decloak-on-pilot-loss

Especially important before exposing the old Cloak Disabled match switch. Prove individual craft cloak state and match-wide cloak policy separately.

### G. Pilot animation frame-rate invariance

Now directly relevant to the new FP/world animation API and recent proof that first-person/world pilots are separate render entities.

---

# 6. Items reviewed but not promoted without stronger evidence

These appear in reviews/discussions but are too subjective, hardware-dependent, or non-specific to patch directly:

- general "AI is dumb" / campaign difficulty complaints;
- generic low-FPS complaints without a stable workload;
- broad claims that graphics/art direction are worse;
- toxicity/community-management complaints;
- isolated target-lead complaints contradicted by other users in the same thread;
- general controller discomfort without a reproducible input-state failure.

They can still generate test ideas, but they are not bugs until a deterministic engine divergence is demonstrated.

---

# 7. Source-quality caveats

- The 2.0.117 and 2.0.131 English changelogs were located on a third-party patch archive rather than a surviving first-party announcement. They are therefore marked **OFFICIAL-ARCHIVE** and should be cross-checked against historical binaries/Steam depots before relying on exact wording for reverse engineering.
- The final 2.2.301 fixes have stronger first-party/community-thread and GOG changelog preservation.
- The Steam community known-issues guide is maintained community documentation and contains both historical and current claims; current OpenShim state supersedes its entries where we have direct runtime/RE evidence.
- Multiple posts by Scott/"Herp" are one source, not independent corroboration. Their value is the technical specificity and reproducibility of the reports.

---

# 8. Recommended next regression work order from this sweep

1. **Day Wrecker + Popgun historical authority comparison** — use the known 2.0.131 Popgun fix as a guide.
2. **`perceivedTeam` victim retaliation parity** — 1.5 vs Redux, cannon hit/miss/sniper, craft/`turrettank`/`turret`.
3. **CLI multi-parameter parser parity** — preserve `-disablemods` and known renderer switches as controls.
4. **Great Pyramid HGT/HG2 no-smoothing study**, then expand to other stock maps.
5. **Shutdown phantom-process repeated qualification**.
6. **AI path/subtask resumption regression** around new tuning.
7. **Pilot-loss decloak + future Cloak Disabled rule separation**.
8. **MP map CRC/resource isolation regression**.
9. Continue existing crash-signature, DX11 lifetime, Splinter, editor, and content-specific tracks.

When a candidate is proven fixed or disproven, update this file and the community audit rather than deleting the historical entry. The goal is to retain the provenance and the acceptance test that prevents the same bug class from returning.
