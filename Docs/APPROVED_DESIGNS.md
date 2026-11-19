# Approved feature designs

These are the designs the user approved in chat. Each one is the record that builders follow. A builder must not depart from a design here. If a design cannot be built as written, stop and report.

## Queue order (2026-11-19)

Builds run one Opus at a time:

1. Daywrecker AI defence v1 (item 14a): built, in review.
2. MRU full pipeline (item 13).
3. Unit loadouts (item 18).
4. Lobby Briefing overlay (item 15).

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
