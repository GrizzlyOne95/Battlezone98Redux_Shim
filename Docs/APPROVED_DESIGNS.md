# Approved feature designs

These are the designs the user approved in chat. Each one is the record that builders follow. A builder must not depart from a design here. If a design cannot be built as written, stop and report.

## Queue order (2026-11-19)

Builds run one Opus at a time:

1. Daywrecker AI defence v1 (item 14a): built, in review.
2. MRU full pipeline (item 13).
3. Unit loadouts (item 18).
4. Lobby Briefing overlay (item 15).
5. Database screen (item 16).

## Item 14a: Daywrecker AI defence

The full plan is in `Docs/DAYWRECKER_AI_DEFENCE_RESEARCH.md` (PR #913 plus the build branch). User decisions:

- **Colour:** the bomb keeps its yellow PowerUp colour, with no colour hook. Dropping ammo or repair pods with the Daywrecker as a distraction is a valid tactic.
- **Attack order:** the player can order Attack on a falling Daywrecker.
- **AI detection:** AI sees the bomb the way it sees a pilot on foot. That means peripheral vision with proximity, not an instant radar contact. The rule is within 70 m horizontally and in front of the unit.

## Item 13: MRU (mobile repair unit)

- **Goal:** build the full design pipeline from `Docs/NIGHTINGALE_RESEARCH.md` (PR #912), with the code verified by CI, review and log checks.
- **Base:** it builds on the class alias and menu probe in PR #915.
- **Pipeline:**
  - service tick
  - ammo gauge
  - Drop Repair and Drop Ammo pods with a cooldown
  - Deploy
  - AI use

## Item 18: Unit loadouts

The user's spec, modelled on BZ2's FactoryPanel:

- **Scope:** settings are per buildable unit, keyed by the unit's ODF. A loadout applies wherever that unit is built, recycler or factory.
- **Entry point:** a submenu in the producer's build menu (PRODMENU). The candidate key is Alt+pick, because Shift+pick queues a build and Ctrl clears the queue. The submenu goes from unit to slot to weapon.
- **Weapon choices:** only weapons the player's current Armory offers.
- **No Armory, or weapon not offered:** the unit is built with its stock weapon.
- **Cost:**
  - The surcharge raises the unit's own build cost by the full Armory price of each changed slot.
  - The surcharge goes through the stock cost function, so the menu display, the charge and the refund all agree.
  - Loadouts cannot be edited while that unit is being built.
- **Weapon swap:** happens when the producer finishes the build, through the existing slot-42 hook chain.
- **Saving:** saved with the mission save only, in a sidecar file `<save>.loadout`. There is no native save block, so saves still load without OpenShim. Players configure it per mission.
- **Mode:** single player only.
- **Milestones:**
  - M1: menu, surcharge and swap.
  - M2: save sidecar.
- **Rejected:** an earlier design built without approval (an Esc-menu button with an Armory build/drop queue). Do not reuse its UX.

## Item 15: Co-op briefing (lobby Briefing overlay)

- **Entry:** a **Briefing** button on the multiplayer lobby screen, for host and clients.
- **Overlay:**
  - It shows the selected mission's pages: `<mission>.des`, then `_2.des` to `_9.des`, plus `<mission>_N.png` images. This is the same layout as CR's PDA INTEL page.
  - Arrows or the page keys turn pages.
  - Close or Esc returns to the lobby with its state untouched.
- **Missions with no `.des` file:** the button is greyed out.
- **Implementation:**
  - The overlay is a native OpenShim panel, because no mission Lua runs in the lobby.
  - It follows the precedent of the existing shell screens (`bans_screen.cpp`, `lan_screen.cpp`).
- **In mission:** CR's PDA INTEL page stays as the briefing.
- **Out of scope:**
  - syncing which page each player has open
  - the single-player briefing screen
- **First step:** find where the lobby stores the selected mission name. This is not yet verified.

## Item 16: Database (single-player bestiary)

- **Entry:** a **DATABASE** button on the stock Single Player screen. It goes in an empty spot at the middle top or bottom, chosen from a screenshot.
- **Screen:**
  - A native shell screen built like the Career screen (`career_screen.cpp`, `shell_screens.cpp`), with painted panel art. Back or Esc returns.
  - Left side: faction tabs (NSDF, CCA, Black Dogs, Fury, plus Briefings), with a scrolling list under each.
  - Right side: the selected entry's details.
- **Contents (v1):** units only. The data format and the tabs must allow more categories later (relics, personnel and so on) without a redesign.
- **Unit entry:**
  - full model name and codename
  - class
  - stats read live from the unit ODF: scrap cost, armor/health, ammo, speed, weapons by slot
  - a lore paragraph and the unit's icon
- **Unit list:** a content file listing the unit ODFs per faction. OpenShim ships the stock list, and CR can override it.
- **Lore text rule (user, strict):**
  - Use only text validated against stock sources: verified VO transcripts, briefings, debriefings, or the game's unit description `.inf`/`.des` files.
  - Nothing inferred or invented.
  - Every lore line must cite the stock file it came from.
  - A unit with no stock text gets an empty lore field.
  - Full model names come from the same sources. Example from the user: a training briefing names the `avturr` model (the "M173 Badger" turret).
  - **Base game only.** The bundled community packs (`addon\BzE Map Pack`, `addon\Legacy Instant Action`, other `addon\` folders) are not sources (user, 2026-11-19).
  - Source location:
    - The user's dump of the stock ZFS archives is at `C:\Users\iestu\Documents\BZR_moved_out_20261112\StockODFFiles` (6081 files, flat).
    - Fall back to `bzone_en.zfs` in the game folder for anything missing.
    - **Use the existing stock-lore reference first:** `C:\Users\iestu\Documents\BZR_moved_out_20261112\docs_reference\stock_lore`.
      - Start with its `AGENT_GUIDE.md`.
      - Search with `python search.py <entity> --scope base`.
      - It indexes stock archive text, `.inf` inspection lore, briefings and debriefs, and GoombaBZ's manual VO transcripts, with filename and line citations. It excludes addon lore.
    - VO transcripts: GoombaBZ's CSVs (`campaigns.csv` holds campaign, briefing and training lines; `units.csv` holds unit chatter) are in CR at `Tools/TranscriptSources/GoombaBZ`. Cite the WAV filename and speaker.
    - The official Red Odyssey expansion counts as a source (user, 2026-11-19). Search it with `--scope red_odyssey`, and label its entries as Red Odyssey.
    - Verified examples: `tran02.des` (training briefing: "M173 Badger turret") and `avturr.inf` (unit description). Unit `.inf` files exist per ODF (`avturr.inf`, `bvturr.inf`, `avtump.inf` and others).
- **Briefings tab:** each campaign's missions with their `.des` pages and images. It reuses the lobby Briefing overlay's reader (item 15), so build item 15 first.
- **Out of scope:** unlocks, the in-game PDA, 3D model previews, multiplayer.
- **First step:** inventory the stock text sources (which unit `.inf`/`.des` files exist, and the VO transcript and debriefing locations) before writing any lore.

---

# Proposed designs (awaiting the user's approval; do not build)

## Item 17: Custom tank skins (PROPOSED)

**What already exists (verified 2026-11-19):**
- CR's co-op team paint (`Scripts/CRTeamSkins.lua` on CR main) already paints one craft without touching other units of the same model.
  - It clones the unit's `<src>_tm` material to `<src>@crteam_<key>` and writes a `teamPaint` value to the clone.
  - `teamPaint` selects either camo (the pattern is baked into the unit's mask RGB) or a solid tint, keeping the hull's own shading.
  - It runs through EXU's material API (CloneMaterial, SetSubEntityMaterial, SetMaterialShaderVector).
- Assets and shader support:
  - CR ships 114 `crteam_*_d.dds` masks and `Materials/CR_TeamSkins.material`, generated by `Tools/TexturesAndSky/Build-TeamSkins.py`.
  - The shader side is `TEAM_PAINT_ENABLED` in OpenShim's `openshim_enhanced_base-sm4.hlsl:473-490`.
- Limits:
  - Only the high-quality enhanced techniques (`en-high*`) paint; other quality levels show stock paint.
  - Today the host gets green digital camo and guest teams get solid tints. Co-op only, and nothing is sent over the network.
- Precedent: no player skin picker was found in BZ2 or BZCC. BZCC has a `TeamColor` shader constant, which is team colour, not a picker. This rests on a quick string search only.

**Proposed design:**
- **Scope:** single player. The skin goes on the player's own ship only, re-applied when the player hops into another craft. AI units and other team units keep their paint.
- **Picker:** a **Paint** row in OpenShim's native Options (or Career) screen.
  - Choices: Stock, the existing green digital camo, and a few solid tints (the colours co-op guests already use).
  - The setting is stored in `openshim.ini`.
- **Applying it:** CR's `CRTeamSkins.lua` gains an SP rule: read the setting and paint the player's current ship with the existing clone path. OpenShim exposes the setting to Lua through a getter.
- **Without CR:** stock paint. The masks and the shader wrapper live in CR.
- **Out of scope:**
  - multiplayer replication (co-op keeps its current rule)
  - new camo patterns: each new pattern needs a new set of per-unit masks from `Build-TeamSkins.py`
  - medium/low quality and stock DX9/DX11 renderers

**Open questions for the user:**
- Where should the picker go (Options vs Career vs Single Player screen)?
- Should co-op use the player's choice instead of the fixed host and guest colours?
- Are new camo patterns (desert, arctic, urban) wanted in v1? Each is an art pass over 114 masks.
