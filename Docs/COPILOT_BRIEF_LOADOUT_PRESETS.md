# Copilot brief: loadout presets (research only, no code)

## Goal
Find out whether BZR OpenShim can add **loadout presets**: save a vehicle's weapon set (the Armory / weapon-slot choices) under a name, and re-apply it in one action. Write a short plan. Don't implement anything.

## Repo
`C:\Users\iestu\Documents\GIT\BZR-OpenShim`. Work on a new branch off `origin/main`, named `research/loadout-presets`, and commit **only** the new doc.

## Read first
- `AGENT_TOOLING.md` and `Docs/ACTIVE_PATCHES.md`.
- Grep `Docs/` and `src/patches/` for anything that already exists:
  - `Armory`, `weapon`, `hardpoint`, `ReplaceWeapon`, `GiveWeapon`, `SetWeapon`, `loadout`;
  - `producer_build_menu.cpp` (the Armory category pages);
  - EXU's Lua API, `ExtraUtils.lua` in the ExtraUtilities repo. Check it before saying Lua can't do something.
- Decompile corpus: `C:\Users\iestu\Documents\GIT\Battlezone_Source`. The shipping exe is GOG Redux 2.2.301. Cite the decompile line for each engine claim, and mark any unchecked claim UNVERIFIED.

## Answer these
1. How does a vehicle's weapon set change today? Cover the Armory power-up drop, the weapon slots at the Recycler/Factory, and Lua `GiveWeapon`. Which engine function or field holds the current weapons?
2. Could a preset be applied by calling existing functions (EXU Lua or an existing OpenShim hook), with no new native hook?
3. What does a preset need to store, and where? (An ini section? Per ODF?)
4. Is it single-player only, or does it work in multiplayer? Stay inside the game's own rules: no spawning weapons for free. A preset still costs scrap and still needs the Armory.
5. Name the smallest useful version: one key or menu action, its UI, and the risks.

## Deliverable
`Docs/LOADOUT_PRESETS_RESEARCH.md`, under about 150 lines. Push the branch and open a **draft** PR titled "Research: loadout presets". No code, ini or patches.json changes.
