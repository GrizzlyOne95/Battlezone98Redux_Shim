# Scoping: feature ideas added 2026-11-18 (work queue items 13–18)

First-pass scoping of the six ideas added to `Docs/FEATURE_WORK_QUEUE.md`.
Each entry covers what is known, where it lives, the risks, and how much can
be built and checked without a live game ("cloud-buildable"). The sources are
the released GOG 2.2.301 decompile (private corpus) and BZ 1.5 named
functions. Claims not read from code are marked UNVERIFIED.

## Ranking

| # | Idea | Size | Cloud-buildable | Next step |
| --- | --- | --- | --- | --- |
| 14b | Daywrecker: spawn without exploding (Lua/map) | S | **Yes**, one call redirect + one flag bit, static-verified | **Built:** `Docs/DAYWRECKER_FALL_ON_SPAWN.md` |
| 14c | Daywrecker: drop speed (ODF) | S–M | Partly: an ODF override of the lobber's launch-speed cap | Research the 0x00581F80 arc solve (high/low arc) |
| 18 | Loadout presets: native UI | M | Partly: the UI shell; the data path is Lua-owned | Wait for item 9's Copilot research to land |
| 15 | Co-op briefing before sim start | M–L | No: MP timing needs live peers | Research the MP pre-sim hold |
| 14a | Daywrecker: AI defence and reaction | L | No: AI targeting needs live tuning | Research target filters for PowerUp class |
| 16 | BZ lore tabs (units, relics, campaign unlocks) | L | Partly: native UI page plus content | Design doc; the content belongs in CR |
| 17 | Custom tank skins / camo | M–L | No: renderer and material work needs visual checks | Research per-entity material clone |
| 13 | Nightingale repair class | L | No: new vehicle class, AI and UI | Design decision: finite or infinite supply |

## 13. Nightingale repair vehicle class

- **Idea.** A support vehicle that drops ammo or repair on demand, as
  separate choices, and moves without using its own pods. Possibly a deploy
  mode that services vehicles in a radius (the ROTBD interview).
- **Known.** The stock pod drop goes through the PowerUp/ObjectLobber path
  above (Armory FinishBuild 0x004732C0 → ObjectLobber 0x00582190). A new
  vehicle class has precedent in `Docs/TRACKED_VEHICLES.md` (BuildClass hook,
  per-class ODF section, vtable-slot overrides).
- **Shape.** A `[NightingaleClass]` ODF section on a hover base, with two
  command-menu entries (Drop Repair, Drop Ammo) through the RTS command
  plumbing (`rts_commands.cpp`), and a deploy mode that ticks a radius heal
  and reload.
- **Decision needed.** With an infinite supply it is a pure command feature.
  With a finite pool it needs a resource model, a HUD gauge and
  save/load.
- **Risk.** Balance-changing, so single player only. The radius service
  needs per-target cooldowns; AI use of the class is extra work.

## 14. Daywrecker counterplay

### 14a. AI defends against, and reacts to, incoming Daywreckers
- **Observed.** Ordering units onto a falling DW gives "Go To" or "Defend",
  and a direct attack order does not hit it.
- **Lead.** A DW is a PowerUp (`DayWreckerClass` derives from `PowerUpClass`,
  BZ 1.5 0x0052D3A9). The command menu's order for an object depends on its
  class. A PowerUp is probably not an attack target at all, which would
  explain "Go To". UNVERIFIED: read the menu's per-class order choice
  (`ControlPanel` mode list) and the AI target filters.
- **Aim.** Hitting a near-vertical target touches the turret pitch limits
  (`TurretAimPitch`) and the cannon-lead solve (`CannonLeadVelocitySite`,
  `ordnance velocity` work), so there is prior art there. Whether AI weapons
  can track the drop speed at all is UNVERIFIED.
- **Enemy reaction.** Needs a "threat in radius" hook like the person-class
  detection. This is AI behaviour, so it is single player only and needs
  live tuning.

### 14b. Spawn a Daywrecker without it exploding (Lua or map)
**Built**: see `Docs/DAYWRECKER_FALL_ON_SPAWN.md`.

### 14c. Drop speed from an ODF key
- **Known.** The Armory does not "drop" a DW: ObjectLobber lobs it on a
  ballistic arc. Launch speed is `sqrt(distance * 9.8) + 20`, capped by the
  weapon class's speed field (+0x84, an existing ODF value), aimed by
  0x00581F80. Gravity is the airborne step's 9.8 (FUN_005A7D70).
- **Shape.** An ODF override for that cap or the `+20` margin gives a
  flatter, faster shot. A literal faster fall needs a per-class gravity
  scale inside the airborne step, which is a bigger hook.
- **Next.** Read 0x00581F80 to see which arc it picks, then decide.

## 15. Co-op briefing after the map loads
- **Idea.** Let players bring the briefing back up once the co-op map has
  loaded: a native pause-style screen before simulation starts.
- **Known.** `Docs/BRIEFING_PAGES.md` covers the single-player pre-launch
  screen. `Docs/MP_PRELOBBY_DESIGN.md` covers the pre-lobby.
  `Docs/NATIVE_UI_FRAMEWORK.md` can draw the overlay.
- **Risk.** "Before simulation starts" in a network game means every peer
  must agree to hold. A local-only overlay that does not pause is much
  smaller: the briefing text over the first seconds, dismissable.
- **Next.** Decide local overlay versus a synced hold. The synced hold needs
  MP research and two-PC live tests.

## 16. BZ lore tabs
- **Idea.** Unit and relic entries that unlock with campaign progress, in a
  native UI menu.
- **Known.** The native UI framework exists. Campaign identity comes from
  `Docs/CAMPAIGN_MANIFEST_ID.md`; career progress is in `career_stats.cpp`.
- **Shape.** OpenShim provides a data-driven page (entries from a content
  file) with an unlock predicate. CR owns the text and art and the unlock
  table.
- **Next.** A design doc and the content file format. The UI itself needs
  visual checks.

## 17. Custom tank skins
- **Idea.** Assign a camo pattern to the player's tank.
- **Known.** Material ownership rules are in
  `Docs/ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md`. A per-entity material
  clone is needed so other units of the same ODF keep the stock skin.
- **Risk.** Renderer path differences (DX11 enhanced or stock). Multiplayer
  visibility would need replication, so it starts as local-only.
- **Next.** Research the per-entity material clone for the player's entity.

## 18. Unit loadout presets: native UI
- **Known.** `Docs/LOADOUT_PRESETS_RESEARCH.md` concludes no new weapon hook
  is needed: read the installed weapons, then reapply them through Armory
  Build/Dropoff. Item 9 is with Copilot (`COPILOT_BRIEF_LOADOUT_PRESETS.md`).
- **Shape.** An entry in the Recycler/Factory or Armory build menu (the
  `producer_build_menu.cpp` plumbing) that lists presets. Lua owns the
  preset table.
- **Next.** Wait for item 9, then design the menu entry.
