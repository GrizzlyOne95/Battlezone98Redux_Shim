# RTS range rings

Native ground rings and text labels for the units you have selected: direct-fire weapon reach, radar scan range and the trigger radius of your team's proximity mines. They sit on the same ring pool as the other RTS markers (`Docs/RTS_MARKERS.md`).

## Gate and options

Each kind has its own on/off key in `[Gameplay]` and its own row in Options > Controls > RTS Commands. All apply live (the rows are `ShimSettingApplyGroup::GlobalImprovement`; `ReloadRtsMarkersConfig` re-reads them), so flipping one mid-mission adds or removes its rings on the next tick.

| Key | Options row | Default | Draws |
|---|---|---|---|
| `RtsWeaponRange` | Weapon Range | off | orange ring at the direct-fire reach |
| `RtsRadarRange` | Radar Range | off | mint ring at `[CraftClass] rangeScan` |
| `RtsMineRange` | Mine Range | off | lime ring per own-team proximity mine near a selected unit |
| `RtsRangeLabels` | Range Labels | off | the ring names, for every kind (also the artillery ring) |

`RtsArtilleryRange` (light blue) is unchanged. The label row only matters while a ring row is on: with every ring off no label is drawn, so Reset to Stock (all ring rows reset to off, `RtsRangeLabels` kept) leaves no ring and no label.

When shown:

- Only for your own selected units, for as long as they are selected. No hold key.
- Never for the vehicle you pilot (same as the artillery ring).
- Hidden with the HUD (Ctrl+=). The labels also wait for a main camera view (the camera record the rally label reads).
- At most 16 weapon, 16 radar and 24 mine rings (slots `kFirstWeaponRingSlot`, `kFirstRadarRingSlot`, `kFirstMineRingSlot` in `include/rts_markers_policy.h`; `kSlotCount` 167 -> 223). A ring needs a radius of 5-1500 m.

Multiplayer: local draw only. No game object is created, no network message is sent, nothing is saved. Every read is in a `__try` helper. A client's object list may not hold every remote friendly mine (UNVERIFIED); a missing mine simply has no ring.

## Colours

Alpha is low so terrain shows through. The mine colour was chosen against the existing ones: gold is taken by the power ring and the neutral ping (`kPowerColour`, `kNeutralColour`, g >= 0.86, b ~ 0.3), so the mine ring is lime-yellow `{0.78, 1.0, 0.2}`, not amber. Direct fire orange `{1.0, 0.55, 0.25}` is close in hue to the order-queue amber `{1.0, 0.55, 0.05}` (`RtsOrderQueuePolicy::kQueueColour`): they differ in form (wide translucent ring against thin lines) and the queue is only drawn after Shift-queued orders. If live testing shows confusion, change `kDirectFireColour`.

| Ring | Colour (r, g, b, a) |
|---|---|
| Artillery (unchanged) | 0.55, 0.85, 1.0, 0.50 |
| Direct fire | 1.0, 0.55, 0.25, 0.45 |
| Radar | 0.35, 1.0, 0.65, 0.40 |
| Mine trigger | 0.78, 1.0, 0.20, 0.50 |

## Data sources

- **Selection:** `ControlPanel` handles at +0x1C, count at +0x188 (`rts_markers.cpp`, `GatherSelectedOwnUnits`): own team, not the piloted object, at most 16.
- **Direct fire:** the artillery ring's live weapon read: `Carrier::GetWeapon(slot)`, weapon +0x08 class, +0x0C ordnance class, ordnance +0x54 `shotSpeed`, +0x50 `lifeSpan` (`ReadDirectFireSeh`, as `ReadArtillerySeh`). Reach = `shotSpeed * lifeSpan - 1`, the formula `ai_odf_tuning.cpp:3174-3215` uses. v1 takes a weapon only when its class signature is `CANN` (`LaserSight::kWeaponSigCannon`) and its ordnance is not a gravity shell (those are the artillery ring's). Homing and guided weapons are other classes and are skipped; so is every other class (mortar, dispenser, launchers, beams).
- **Radar:** `[CraftClass] rangeScan` of the unit's ODF, read through the shared ODF path (`TryGetObjectOdfToken` + `TryResolveOdfFilePath`) and cached per ODF. Stock values: avrecy 500, avturr 200, avscav 200, avfigh 300 (StockODFFiles). Any unit with `rangeScan > 0` gets a ring (no `periodScan` condition). If the ODF cannot be resolved, the runtime `CraftClass +0x150` is read instead (`reverse_engineering/bsim/out/object_model/core_object_model.md`, "CraftClass"), accepted only when finite and 10-5000.
- **Mines:** `ProximityMine` objects of the vtable row `ProximityMineVtable` (0x00886278, RTTI `.?AVProximityMine@@`, as `team_filter_mines.cpp:403`); own team via `SameTeam`; radius = class +0x168 (`team_filter_mines.cpp:177`, the `searchRadius` key; stock proxmine 30 m); position = object +0x108 (`team_filter_mines.cpp:183`). A mine shows when a selected unit is within `searchRadius + 20 m`; the nearest 24 are kept. The scan reads the shared 100 ms `GameObject::objectList` snapshot (`SharedSnapshot`, also used by the attack marks): one pass over at most 4096 pointers, no second scan. MagnetMine is a separate class and is not drawn. The blast radius (`xminxpl` `damageRadius` 100) is a different number and is not drawn.

## Labels

Each ring carries its name in the ring's colour: WEAPON RANGE, RADAR RANGE, MINE TRIGGER, and ARTILLERY RANGE on the artillery ring (trivial: one more kind). The texts are localised strings (`openshim_ui:rts_range_label_*`).

- Drawn by a HUD painter (`HudGaugeOverlay::Slot::RangeLabels`, `src/patches/rts_range_labels.cpp`) with the same stock HUD text call as the producer rally label and badges (font colour set from ARGB). Not a 3D object.
- 64 world points are sampled around each ring at terrain height + `kLift`, published once per tick by `rts_markers.cpp` (cached until the ring moves). Each frame the painter projects them with the stock camera record (`ProducerRallyPolicy::ProjectToScreen`, the camera read of `producer_badges.cpp`).
- Letters are placed one at a time along the projected arc, spaced by the measured glyph width (plus 1 px) in screen pixels, centred on the ring point lowest on the screen (the side facing the camera), reading left to right. Glyphs stay upright. The text is drawn just below the arc (0.6 x text height) so it sits outside the ring on its near side.
- Hidden when: the projected circumference is under twice the text width plus 12 px; every point is behind the camera or the span the text needs runs through one; the span runs off screen (12 px margin).
- At most 24 labels a frame, nearest rings first (smallest view depth of the ring centre).
- The maths (`PlaceArcText`, `WalkArc`, `BottomAnchor`, `KeepNearest`) is pure and tested in `tests/rts_range_rings_policy_tests.cpp`.
- Labels hide with the HUD and with `RtsRangeLabels` off, and clear when no range ring is wanted.

## Log lines

All in `openshim.log`, change-only:

- `[RTSRANGE] config weapon=%d radar=%d mine=%d labels=%d` on every option change.
- `[RTSRANGE] radar odf=<odf> range=<m> source=odf|runtime(+0x150, UNVERIFIED)|none`, once per ODF (budget 64 per mission). A `runtime` line means the ODF could not be read; confirm the value (recycler 500).
- `[RTSRANGE] mine rings shown=<n> (selected units=<m>)` when the shown count changes.
- `[RTSRANGE] labels installed` / `labels unavailable ...` once, when the HUD overlay and camera rows bind.

## UNVERIFIED

- `CraftClass +0x150` on GOG 2.2.301 (only used when the ODF cannot be resolved).
- Selection (`ControlPanel +0x1C/+0x188`) populating in plain cockpit view (the other selection-based rings share this doubt).
- Which unit ODFs resolve through `TryResolveOdfFilePath` for stock (packed) units.
- The class signature `CANN` covers every direct-fire cannon, and that none of them is homing; rocket and machine-gun class signatures are not known, so those weapons get no ring in v1.
- Remote friendly mines in a client's object list.
- Label legibility (stock font colour call, placement just below the ring) at near and far zoom, on DX9 and DX11.
- Whether the orange and queue amber are too close.

## Live checklist (not yet run)

Single player:

1. Select a Recycler with `RtsRadarRange` on: a mint ring at 500 m, label RADAR RANGE on the near side. The log shows `radar odf=avrecy range=500.0 source=odf` (or the runtime line).
2. Select an `avturr` and an `avscav`: 200 m rings. A unit without radar (e.g. a plain tank with `rangeScan` 0): none.
3. Select a tank with a direct-fire cannon: an orange WEAPON RANGE ring at about `shotSpeed * lifeSpan - 1`. Select a howitzer: only the light-blue artillery ring (ARTILLERY RANGE), no orange one.
4. Rings follow hills and the moving unit; they vanish on deselect, death, mission end and while piloting (no ring for the piloted unit).
5. Lay mines with a minelayer, select a unit within about 50 m: 30 m lime rings, label MINE TRIGGER; move the unit away: they go. More than 24 mines: only the nearest 24.
6. Flip each of the four options mid-mission (Options > Controls > RTS Commands): `RtsWeaponRange`, `RtsRadarRange`, `RtsMineRange` make their rings appear and disappear on the next tick; `RtsRangeLabels` removes and restores every label while the rings stay.
7. Reset to Stock: no ring and no label is drawn afterwards.
8. Hide the HUD (Ctrl+=): rings and labels hide together.
9. Label legibility: at near zoom and at far zoom (cockpit, chase, satellite), the letters are readable, upright, evenly spaced along the arc, on the camera-facing side. A ring too small or too far for its text shows no label. A ring partly off screen: the label hides rather than drawing off the arc. Turn the camera so a ring is behind you: no stray label.
10. Both DX9 and DX11.

Two-player LAN (host and client, each repeats 1-9):

11. Each player sees rings and labels only for their own selection; none for the other player's units, mines or enemies.
12. No change in network traffic or desync over a 10 minute game with all rings on.
13. Does the client see the host's friendly (own team) mines in the mine rings? Record the answer (UNVERIFIED).
14. Allied (not own-team) units and mines: none.
