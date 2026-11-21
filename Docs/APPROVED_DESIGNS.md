# Approved feature designs

These are the designs the user approved in chat. Each one is the record that builders follow. A builder must not depart from a design here. If a design cannot be built as written, stop and report.

## Queue order (2026-11-19)

Builds run one Opus at a time:

1. Daywrecker AI defence v1 (item 14a): built, in review.
2. MRU full pipeline (item 13).
3. Unit loadouts (item 18).
4. Lobby Briefing overlay (item 15).
5. Database screen (item 16).
6. Custom tank skins (item 17).

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
  - AI use: commands only (user, 2026-11-19). An MRU deploys only when ordered; otherwise it sits and responds to move orders and pod drops. No autonomous deploy rule.
- **Faction models (user, 2026-11-20), art direction only, no build yet:**
  - NSDF and Black Dogs share the existing avmru model, with a texture swap for bvmru.
  - CCA (svmru): a new model of our own, using the Battlezone Classic "Hors" (workshop 2319157982) as reference only. Its model is not used directly.
  - CRA (cvmru): a new model of our own, using the Total Command kvserv service truck as reference. The Battlezone Classic "Xunsu Fu" was rejected because it reads as a battle tank.
  - Reference renders: `scratchpad\mru_renders` (session 2026-11-20); search report `mru_reference_search.md`.
- **Non-combat (user, 2026-11-20):** pure utility, like the Tug or Scavenger. The MRU has no Attack order and no combat AI: it never picks attack targets, whatever its ODF's AI process or weapons say. It stays a hovercraft in the Utility category, with move/follow, pod drops and Deploy.

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
- **Implementation (option A, user, 2026-11-19):**
  - The overlay is a native OpenShim panel, because no mission Lua runs in the lobby.
  - It is drawn **inside the lobby screen** (cUI_Multiplayer_Create, shell id 0xF), not as a separate shell screen. The shell deletes the current screen on navigation, which would drop launch and kick handling and rebuild the lobby on return.
  - The parts:
    - A post-build observer for stock id 0xF.
    - The z-order setter, so the panel draws above the lobby.
    - Click blocking: the panel sits at the front of the child list.
    - A slot-4 KeyPressed patch for Esc and paging.
    - A scrolling text block for the page text.
  - Known limits: typed characters may still reach the hidden chat entry, the map-filter box may still take clicks, and an alert could draw under the panel.
- **Mission name:** the std::string at record+0xDC, where record = FUN_0056F900([screen+0x1BC]). Verified in the shipping exe (2026-11-19).
- **In mission:** CR's PDA INTEL page stays as the briefing.
- **Out of scope:**
  - syncing which page each player has open
  - the single-player briefing screen


## Item 16: Database (single-player bestiary)

- **Entry:** a **DATABASE** button on the stock Single Player screen. It goes in an empty spot at the middle top or bottom, chosen from a screenshot.
- **Screen:**
  - A native shell screen built like the Career screen (`career_screen.cpp`, `shell_screens.cpp`), with painted panel art. Back or Esc returns.
  - Left side: faction tabs (NSDF, CCA, Black Dogs, Fury, plus Briefings), with a scrolling list under each.
  - Right side: the selected entry's details.
- **Contents (v1):** units only. The data format and the tabs must allow more categories later (relics, personnel and so on) without a redesign.
- **Unit entry (v1, user 2026-11-20):**
  - unit name (the role, e.g. "Medium Tank")
  - model name (e.g. Grizzly, Bobcat)
  - model number, where stock text gives one (e.g. "M173 Badger"), with every cited variant
  - stock stats read live from the unit ODF: scrap cost, armor/health, ammo, speed, weapons by slot
  - the unit's icon
  - **Lore paragraph: deferred.** It is added later if more stock lore turns up. The data format keeps an empty lore field ready for it.
- **Unit list:** a content file listing the unit ODFs per faction. OpenShim ships the stock list, and CR can override it.
- **Lore text rule (user, strict):**
  - Use only text validated against stock sources: verified VO transcripts, briefings, debriefings, or the game's unit description `.inf`/`.des` files.
  - Nothing inferred or invented.
  - Every lore line must cite the stock file it came from.
  - A unit with no stock text gets an empty lore field.
  - Manuals (user, 2026-11-20): the BZ98 Redux manual and the 1998 Brady "Official Strategy Guide" are sources, labelled as such. Copyrighted text is paraphrased, never copied, and a paraphrase must not change any fact. Paraphrased descriptive text is allowed when it adds information about that specific unit (user, 2026-11-20: the user owns what ships). General narrative not about the unit (prologues, character letters, mission walkthroughs) stays out.
  - Conflicting names (user, 2026-11-20): show every variant, each with its citation. Example: the Badger is "M173 Badger" in `tran02.des:1` and `misn03.des:7`, but "T-4 Badger" (`campaigns.csv:57`) and "T-7 Badger" (`campaigns.csv:64,76`) in VO. See `Docs/DATABASE_TEXT_INVENTORY.md`.
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

## Item 17: Custom tank skins (approved 2026-11-19)

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

**Design:**
- **Scope:** single player. The skin goes on the player's own ship only, re-applied when the player hops into another craft. AI units and other team units keep their paint.
- **Co-op:** the setting never overrides co-op's fixed host and guest paint, to avoid confusion (user). In network games the SP rule is off.
- **Picker:** a **Paint** row in OpenShim's native **Options** screen (user).
  - Choices: Stock plus the solid tints co-op guests already use (camo dropped for v1, user 2026-11-20).
  - The setting is stored in `openshim.ini`.
- **Applying it (revised by the user, 2026-11-20):** native, inside OpenShim. EXU runs only when mission Lua loads it, so global skins cannot depend on EXU or CR Lua.
  - OpenShim clones the player ship's material, sets the tint uniform, and re-applies it when the player changes ship.
  - v1 is **tints only** (the option B mask set: alpha-only masks, no camo RGB). The variant list must be a data table so camo and new patterns can be added later without a redesign.
  - The shader path (`TEAM_PAINT_ENABLED`) must compile in OpenShim's own en-high passes, not only CR's wrappers.
  - Masks ship with OpenShim.
- **Without CR:** works the same (native).
- **Out of scope:**
  - multiplayer replication (co-op keeps its current rule)
  - new camo patterns: each new pattern needs a new set of per-unit masks from `Build-TeamSkins.py`
  - medium/low quality and stock DX9/DX11 renderers
- **Work split (2026-11-20):** OpenShim only (PR #920 grows to hold it). No CR PR. The Lua getter is dropped unless something still needs it.

## Item 18: Hitmarker kill flash (approved 2026-11-20)

- A confirmed player hit that takes the victim's health from above 0 to 0 or below is a killshot.
- That marker and its ghost ripple draw red (255 50 40), using `HitMarkerOpacity`, instead of `HitMarkerColor`, for the normal `HitMarkerDuration`.
- A later non-kill hit does not override the red while it shows.
- No new INI option. The kill flag travels in the existing hit event (`SimDamageApplied`, arg 2).

## Item 19: CR NSDF/Black Dog gun tower stabber (approved 2026-11-20)

- Today `abtowe` → `gspstabn` → `rocket3n` borrows the CRA green `rocket3a.render` (light 150 255 50).
- `rocket3n` gets its own flare and light render, and a muzzle flash tint, in blue-white (light 150 200 255). That colour differs from stock orange (255 150 50) and CRA green.
- The Black Dog tower `bbtowe` switches from `gblastb` (Blue Blast Cannon) to the same stabber variant.

## Queue note: MP "Not Ready" with IPv6 (research 2026-11-20, no design yet)

- Readiness needs the BZRNet websocket to reach state 3 (`reverse_engineering/notes/mp_not_ready_readiness_chain.md`).
- The likely IPv6 link is a getaddrinfo or connect stall on a broken IPv6 DNS path (confidence about 45%). The matchmaking host has only an A record.
- Candidate fix: in the existing `Hook_getaddrinfo` (`src/patches/net_optimizer.cpp`), force AF_INET for BZRNet names. It needs an affected player's `[MPREADY]` log first.
