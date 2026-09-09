# Master Feedback and QA Backlog — 2026-09-09

This document consolidates the current live-playtest, UX, Campaign Reimagined, ExtraUtilities, and OpenShim feedback captured during the September 9 review pass. The OpenShim repository is the master tracking location even where implementation ownership belongs to Campaign Reimagined or ExtraUtilities.

## Status legend

- **ACTION** — implementation work is expected.
- **VERIFY** — source state looks improved or fixed, but current runtime proof is still required.
- **CLOSED / REFERENCE** — captured for historical context; no current implementation action unless reproduced.
- **OPTIONAL** — useful follow-up after the core pass.

---

# 1. Native OpenShim Settings UI

## 1.1 Context-sensitive hover help — ACTION

The native OpenShim Settings screen should explain both the setting and the action the player is about to perform.

Required behavior:

- Hovering the **setting name** shows a concise description of what the setting does.
- Hovering the **current value / toggle** shows the exact action clicking it will perform, for example:
  - `Click to change Scrap/Pilot HUD from Stock to Legacy.`
  - `Click to change Target Popup from Default to Legacy.`
- Moving the pointer away restores the normal page-level OpenShim help/status text.
- Prefer a fixed help/status strip rather than floating tooltips so help text does not cover settings or feel foreign to the BZ UI.
- Consider highlighting the whole hovered row to make name/value association clearer.

The setting metadata should be data-driven so descriptions and value-action strings stay beside the setting definition rather than being hard-coded throughout the renderer.

## 1.2 Settings-screen readability and backing — ACTION

Some labels, especially toward the lower-left edge of the native settings UI, are harder to read because they sit over the live game/cockpit background.

Required cleanup:

- Extend the dark backing panel behind the full settings table rather than changing the Battlezone-style green text unnecessarily.
- Move text slightly inward where needed so labels do not sit directly on high-contrast game geometry.
- Preserve the native BZ visual language while improving contrast.

## 1.3 Header / diagnostic noise — ACTION

The current header presents too much low-level diagnostic text and has shown duplicated/truncated asset-pack information.

Preferred direction:

- Keep the top line compact, e.g. runtime state, OpenShim version, game distribution/build.
- Reduce asset state to one concise line such as `Assets: Full`, `Assets: Partial`, or `Assets: DLL-only`.
- Move detailed resource/capability diagnostics to contextual help or a dedicated diagnostics surface.
- Eliminate duplicated `OpenShim Asset Pack: Not Detected` text and any truncated compatibility line.

## 1.4 Restart marker explanation — ACTION

If `*` means a setting requires a Battlezone restart, make that explicit on-screen, for example:

`* Takes effect after restarting Battlezone.`

Do not leave the marker unexplained.

## 1.5 Player headlight brightness control — ACTION

Add a user-facing **Player Headlight Brightness** setting to native OpenShim settings.

Design requirements:

- Player craft only unless a separate AI-light setting explicitly says otherwise.
- Apply immediately at runtime so the player can judge the result visually.
- Persist through OpenShim configuration.
- Scale the actual emitted player-headlight light intensity rather than faking brightness through unrelated ambient/material changes.
- Feed every supported player-headlight render path from the same underlying scalar so `100%` has consistent meaning.
- Clamp manually edited values to a sane range.

Suggested UI presets for initial implementation:

`50% -> 75% -> 100% -> 125% -> 150%`

A float scalar internally leaves room for finer control later.

---

# 2. ExtraUtilities input / hotkey interference

## 2.1 Disable EXU convenience hotkeys — ACTION

Ensure EXU gameplay convenience hotkeys, including headlight-related hotkeys and similar direct feature toggles, are disabled by default and preferably removed where the feature is now controlled through OpenShim/PDA UI.

Reason: these bindings have interfered with macros, cheat-code entry, and normal game input sequences.

Acceptance requirements:

- Disabled bindings must not consume the keystroke.
- Audit the input-hook path, not only the visible UI.
- Remove stale PDA labels that advertise hotkeys once those hotkeys are no longer active.
- Regression-test cheat-code entry and common macro sequences with OpenShim + EXU loaded.

Current PDA code still advertises several convenience keys for items such as player light, light color, AI lights, beam, wingman repair, and scavenger assist. Those labels should disappear with the hotkey cleanup.

---

# 3. Campaign Reimagined — misn02b playtest feedback

## 3.1 `Get inside a vehicle` objective completion state — ACTION / VERIFY

Observed behavior: the objective text turns green as soon as the player gets into a vehicle.

Check whether that completed-state presentation is intended. Confirm that the objective then clears or advances correctly and does not remain as stale completed text longer than desired.

## 3.2 Initial fighter spawn pop-in — ACTION

The first fighter spawns are visibly appearing out of nowhere.

Preferred fix:

- Spawn the fighters off-map or otherwise out of sight at mission start.
- Hold them inert until the intended arrival window.
- Move/order them into their approach positions instead of creating them visibly in front of the player.

Qualification:

- Pre-spawned fighters must not engage, be targeted/detected, trigger mission state, or otherwise interfere before their intended entrance.

## 3.3 Turret retaliation / reaction speed — ACTION

Turrets are still not returning fire quickly and reliably enough. An engine-level retaliation issue was already partially addressed, but mission/unit tuning should not depend on slow inherited/default AI reaction values.

Action:

- Audit relevant turret/defense ODFs.
- Add explicit AI reaction-time values.
- Tune toward fast defensive response without making tracking/fire cadence unnaturally perfect.
- Verify initial acquisition after being attacked.
- Verify reacquisition/retaliation after target or perceived-team state changes.
- Distinguish slow-but-correct ODF tuning from a remaining engine bug where the turret never enters the correct combat state.

---

# 4. PDA architecture cleanup

The current PDA is functionally rich but visually noisy. Pages should have one clear purpose rather than mixing craft state, weapon state, target state, navigation chrome, and settings subcategories on the same screen.

The recommended end state is eight distinct functional pages.

## 4.1 VEHICLE — ACTION

Purpose: **How is my current craft doing?**

Show only current-craft state:

- Vehicle/craft display name.
- Hull current/max and percentage.
- Ammo current/max and percentage.
- Current speed.
- Heading as compass direction plus degrees, e.g. `SW 233°`.

Heading implementation:

- Normalize to `0–359°`.
- Derive eight compass sectors: N, NE, E, SE, S, SW, W, NW.
- Verify BZR world-axis / north convention before assigning `0° = N`; do not assume the usual X/Z convention without runtime proof.

Do not put weapon-detail browsing or target-detail telemetry on this page.

## 4.2 WEAPONS — ACTION

Purpose: **What can my weapons do right now?**

Show:

- Installed weapon slots.
- Active firing-group membership.
- Currently inspected/selected weapon.
- Damage.
- DPS.
- Effective range.
- Whether the current target/aim point is reachable or in range.
- Ammo cost / shots remaining where meaningful.
- Splash radius.
- Charge level / charge-state information for charge weapons.

Most of this telemetry already exists in PersistentConfig/PDA code; the task is primarily to reorganize it into one dedicated weapon page.

## 4.3 TARGET — ACTION

Purpose: **What am I aiming at?**

Show:

- Target source/mode such as target lock, smart reticle, ground reticle.
- Target unit name and class/type.
- Range.
- Target speed.
- Closure / ETA where meaningful.
- Target hull and ammo.
- Terrain aim-point information when the reticle is on terrain rather than an object.

Do not duplicate the full weapon-stat list here. Weapon reachability belongs on WEAPONS; target telemetry belongs here.

## 4.4 BASE — ACTION

Purpose: **What is the condition of my base?**

Show:

- Key structure counts.
- Power warnings / unpowered structures.
- Relevant producer/base condition.

Avoid production-queue controls here; those belong on QUEUE.

## 4.5 QUEUE — ACTION

Purpose: **What is being produced?**

Show only current production state:

- Producer.
- Queued unit/item.
- Quantity.
- Queue enabled/disabled or locked/unlocked state.

## 4.6 LOADOUT — ACTION

Purpose: **How will future units be equipped?**

Show:

- Armory availability.
- Producer and unit selection.
- Hardpoint/loadout slots.
- Selected upgrade.
- Surcharge.
- Comparison against stock, including DPS, range, and delay changes.

## 4.7 CAREER — ACTION

Purpose: **Player records and mission statistics.**

Keep current-mission and career totals here. Do not mix configuration or live vehicle telemetry into this page.

## 4.8 OPTIONS — ACTION

Purpose: **Campaign Reimagined-specific preferences only.**

The current settings page has internal categories that behave like mini-pages. There are now few enough CR-owned options that they should fit on one page.

Recommended CR-owned options:

### PDA

- PDA size.
- PDA opacity.
- PDA theme.
- PDA / Weapon HUD enabled.

### Subtitles

- Subtitles enabled.
- Subtitle size.
- Subtitle opacity.

### Gameplay assistance

- Wingman auto-repair.
- Building auto-repair.
- Scavenger Assist.
- Pilot Mode.

### System

- Reset CR settings.

`Team Color` should remain only if CR is confirmed to own it. If it is global/OpenShim-owned, remove it from the CR PDA as well.

---

# 5. CR vs OpenShim settings ownership

## 5.1 Keep CR settings strictly CR-specific — ACTION

Campaign Reimagined's PDA must not remain a second configuration surface for game-wide OpenShim behavior.

Remove from the CR PDA any OpenShim-owned/general-purpose setting, including:

- Render / Lighting Profile.
- Player headlight visibility.
- Headlight color.
- Headlight beam mode.
- Headlight brightness once added.
- AI headlights.
- Empty-craft lights.
- Emissive pulse.
- Star twinkle.
- Dynamic faction flames.
- Scrap/Pilot HUD layout.
- Radar size.
- Unit Voices.
- AutoSave.
- AutoSave interval.
- Native target/alert policy and similar OpenShim behavior.

OpenShim now owns faction flames as well; remove the CR-facing faction-flame setting.

For backward compatibility, CR may continue reading legacy keys during migration where necessary, but the PDA should not present independently owned duplicates. The long-term direction should also stop writing obsolete OpenShim-owned values from the CR config once migration is safe.

---

# 6. PDA visual hierarchy and navigation cleanup

## 6.1 Stronger page/section hierarchy — ACTION

Categories, headings, labels, values, selected rows, footers, and warnings should not all have the same visual weight.

Use semantic presentation roles:

- Page title — highest emphasis.
- Section heading — strong accent.
- Normal label — subdued relative to the value.
- Value — brighter/high-contrast.
- Selected row/value — dedicated theme accent.
- Footer/navigation hints — dimmer.
- Warning — reserved warning color.
- Critical state — reserved critical color.

Examples include `STATUS`, `MOTION`, `WEAPONS`, `TARGET`, `POWER WARNINGS`, etc. as visually distinct section headings.

The current overlay separates title/tabs/body/footer, but much of the body is still one text caption. If per-row/per-section colors cannot be expressed cleanly with the existing text blob, evolve the PDA body toward structured overlay rows/elements instead of relying only on ASCII separators and `>` markers.

## 6.2 Simplify navigation chrome — ACTION

The PDA currently communicates navigation through several layers at once. Reduce persistent navigation noise so the content dominates.

Preferred direction:

- One clear page title.
- Optional page number such as `2/8`.
- Minimal footer with the keys relevant to the current page.
- Avoid always displaying every category and every destination if bracket navigation already cycles pages.

Example:

```text
BATTLEZONE PDA                  2/8
WEAPONS

...page content...

[ / ] Page   Up/Down Weapon   Y Close
```

---

# 7. PDA theme system

## 7.1 Replace simple color tint with named themes — ACTION

Replace the current simple PDA color preset with a full theme preset that assigns colors by semantic UI role rather than tinting everything uniformly.

Theme roles should include at minimum:

- Backdrop.
- Header/backdrop.
- Border.
- Page title.
- Section heading.
- Normal label.
- Value.
- Selected/highlighted row.
- Footer/inactive text.
- Meter fill / meter empty.
- Warning.
- Critical.

Initial themes:

### Classic BZ

- Very dark green backdrop.
- Medium/dark green normal UI.
- Neon/bright green selections and highlights.
- Closest to the classic Battlezone visual identity.

### Dark BZ

- Near-black or super-dark green presentation.
- Muted green normal text.
- Bright green only for values/selections.
- Lower visual intensity than Classic BZ.

### Cyberzone

- Dark orange / burnt-orange or warm brown-black base.
- Amber/orange normal UI.
- Cyan or bright yellow highlight/accent.
- More industrial/tech presentation.

### BZ2

- Deep navy / blue-black base.
- Cool blue normal UI.
- Cyan/electric-cyan highlight.
- Battlezone II-inspired presentation.

Optional later themes: Terminal and High Contrast, provided they do not distract from the initial four and the semantic color system remains consistent.

Theme selection should also drive range state, selected weapon row, active firing-group indicator, powered/unpowered state, low-health warnings, etc., while keeping warning/critical semantics understandable across themes.

---

# 8. KFK log findings — current verification backlog

Only findings that are not conclusively closed should remain actionable.

## 8.1 EXU -> OpenShim bridge qualification — VERIFY

Current source/export state appears to contain the previously missing bridge families, but this still needs a fresh runtime qualification with current versions of all three components.

Test with:

- current OpenShim;
- current ExtraUtilities;
- current Campaign Reimagined.

Acceptance: no unexpected `OpenShim ... bridge unavailable` messages during a normal CR mission startup/run.

If any remain, investigate deployment/version skew and whether EXU resolves the intended OpenShim module before assuming a missing export.

## 8.2 Steam `EditorOverheadPlacementOrder` parity — VERIFY / ACTION

The old Steam run produced an overhead-editor placement guard mismatch. Current implementation still needs Steam-specific qualification.

Action if reproduced:

- Resolve/validate the Steam sites rather than relying only on GOG-fixed expected bytes/addresses.
- Preserve the pairwise fail-closed behavior so only one side of the priority swap can never land.

## 8.3 Steam `ChunkShadowPolicy` parity — VERIFY / ACTION

The current implementation has historically been gated to the validated GOG 2.2.301 executable/Ogre identity.

Required decision:

- Qualify and enable the equivalent Steam path, or
- explicitly document the policy as intentionally GOG-only if parity is not safe.

## 8.4 Enhanced asset-pack / resource detection — VERIFY

The asset detection system has been substantially improved, including explicit asset-pack identity and resource probing, but the old user log should not be considered fully closed until a known-good full CR/OpenShim install is tested.

Acceptance:

- Native OpenShim Settings correctly reports full/partial/DLL-only asset state.
- Enhanced resources supplied through active CR Workshop content are detected correctly.
- No duplicated or contradictory asset status text appears in the settings UI.

---

# 9. KFK log findings already closed or superseded

These are retained as reference so they are not accidentally reopened without new evidence.

## 9.1 Stale `patches.json` / seven unregistered runtime patches — CLOSED / REFERENCE

The previously missing patch registrations have been added and current build validation cross-checks patch registration so header/JSON drift becomes a build-time failure rather than a silent runtime omission.

## 9.2 Repeated updater promotion of an already-current suite — CLOSED / REFERENCE

Current updater logic checks the installed payload hashes/sizes and reports UpToDate when all suite payloads already match. Reopen only if a current build reproduces repeated unnecessary staging/replacement.

## 9.3 Provisional Steam patch scans logged as scary WARNs — CLOSED / REFERENCE

Current scanner distinguishes provisional pre-settle misses from final failed-closed misses and should log the provisional state as informational rather than warning-level failure.

## 9.4 BZRNet reconnect/spam pattern in the reviewed log set — CLOSED / REFERENCE

The reviewed capture did not show a reconnect loop, repeated lobby socket creation, or control-channel spam. No action from that specific capture unless a current reproduction supplies new evidence.

---

# 10. Recommended actionable-pass order

1. Remove/disable EXU convenience hotkeys and regression-test macros/cheats.
2. Fix misn02b presentation/AI issues: objective completion behavior, fighter entrance, turret reaction tuning.
3. Finish native OpenShim Settings UX polish: hover help, background/readability, compact diagnostics, restart marker, headlight brightness.
4. Clean CR/OpenShim settings ownership so the CR PDA only exposes CR-specific controls.
5. Refactor PDA page responsibilities into VEHICLE / WEAPONS / TARGET / BASE / QUEUE / LOADOUT / CAREER / OPTIONS.
6. Add compass heading telemetry to VEHICLE.
7. Implement PDA semantic styling and named visual themes.
8. Run current-version runtime qualification for EXU bridges, Steam editor placement, Steam chunk-shadow policy, and asset detection.

---

# 11. Qualification matrix for the final pass

At minimum, validate:

- Steam 2.2.301 current build.
- GOG 2.2.301 current build where relevant.
- Current OpenShim + current EXU + current CR together.
- Full CR/OpenShim asset pack.
- DLL-only/partial-asset behavior where applicable.
- misn02b mission flow from start through initial fighter engagement and vehicle-entry objective.
- Turret attack/reacquisition behavior.
- Cheat-code entry and macros with EXU loaded.
- Native OpenShim Settings mouse hover/name/value behavior.
- All PDA pages at common UI scales/aspect ratios.
- All initial PDA themes for readability and warning-state clarity.

This file is intended to remain the master checklist for the next coordinated polish/QA implementation pass.