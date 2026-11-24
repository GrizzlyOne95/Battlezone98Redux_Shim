# BZR OpenShim work queue (recorded 2026-11-17, updated 2026-11-18)

Standing: merge as you go (squash + auto-merge after local CI, a live test for native/gameplay changes, and a fresh-eyes review). New options default OFF.

Live tests still owed: `Docs/LIVE_TEST_BACKLOG.md`.

## Done
- **5. Build queue** (`[Gameplay] RtsBuildQueue`). Branch `agent/rts-build-queue`, worktree `GIT\BZR-OpenShim-buildqueue`, commit 87ffa19a9 (amended), rebased on main 153c9bae6.
  - PR #898, MERGED.
- **12. Remove the name/flag panels from the MP lobby:** PR #896, MERGED.

## In review
- **6. Follow camera** (`[Gameplay] RtsFollowCamera`, Shift+C in satellite). Branch `agent/follow-camera`, PR #900, built in a cloud session: Linux CTest green, both engine rows byte-checked against the GOG 2.2.301 exe, Win32 build left to CI. **Needs the live test** (`Docs/RTS_COMMANDS.md`, checklist 11b) before merge.
- **7. Radar order pings** (`[Gameplay] RtsRadarPings`). Branch `agent/radar-order-pings`, stacked on #900. Needs the live test (`Docs/RTS_MARKERS.md`).
8. **FPS quick-commands** (`[Gameplay] RtsQuickCommands`, Numpad 1/2/3/5). Branch `agent/fps-quick-commands`, stacked on #903. Needs the live test (`Docs/RTS_COMMANDS.md`).

## Waiting (in order)
9. **Loadout presets:** research. Handed to Copilot, see `Docs/COPILOT_BRIEF_LOADOUT_PRESETS.md`.
10. **Tread texture scroll.**
11. **Walker free-turning head:** M0 done, M1 implemented (`Docs/WALKER_FREE_HEAD.md`); next the M1 live test, then M2 (leg pose, relaxation, shared helpers).

## New ideas (added 2026-11-18, not yet scoped)

Scoping notes are first impressions only; each needs its own research pass before it is ordered into the list above.

13. **Nightingale repair vehicle class.** Choose to drop ammo or repair separately; moves so it does not use its own pods; native UI. Possibly a deploy mode that services vehicles in a radius, as described in the ROTBD interview. Open design question: infinite supply, or a finite ammo/repair pool. *Scope:* a new vehicle class (like the tracked-vehicle work in `Docs/TRACKED_VEHICLES.md`) plus a command-menu or native UI entry; needs ODF keys and research on the stock pod/APC drop paths.
14. **Daywrecker counterplay.**
    - Own AI can defend against an incoming DW. Today, ordering units onto one gives "Go To" or "Defend", and even a direct attack order on a falling DW does not fire effectively.
    - Find why AI cannot hit vertically falling targets (lead/aim solve, pitch limits, or target filtering) and see whether it can be improved.
    - Enemy AI reacts to a DW in a radius, like person-class detection, so the player cannot freely drop DWs on it.
    - ODF key for the pod drop rate (for example, faster-falling DWs).
    - Hook the DW class so Lua (or other code) can spawn one without it exploding at once. Today an Armory deploy is the only natural way into the world, and it falls to its target.
    *Scope:* several separate pieces. Prior work: `Docs/Archive/2026/MP_DAYWRECKER_ARMORY_COLLISION_20261027.md` and `DAYWRECKER_RECEIVER_LIFETIME_INVESTIGATION_20261007.md`. Aim research overlaps `TurretAimPitch` and the cannon-lead work. AI changes are balance-changing, so they are single player only.
15. **Co-op briefing.** Some way to pull up the briefing after a co-op map has loaded: a native pause-style screen before mission simulation starts. *Scope:* builds on `Docs/BRIEFING_PAGES.md` (SP pre-launch screen) and the MP pre-lobby work (`Docs/MP_PRELOBBY_DESIGN.md`); the hold-before-sim part needs MP sync research.
16. **BZ lore tabs.** Units and relics, unlocked to match campaign progress; native UI menu. *Scope:* mostly content plus native UI (`Docs/NATIVE_UI_FRAMEWORK.md`); unlock state from campaign progress needs a source (career stats or CR's campaign manifest, `Docs/CAMPAIGN_MANIFEST_ID.md`). The lore text likely belongs in CR.
17. **Custom tank skins.** Assign camo patterns to the player's tank. *Scope:* renderer/material work; check the enhanced material ownership rules (`Docs/ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md`) and how a per-entity material clone would replicate (local-only first).
18. **Unit loadout presets: native UI.** For example, offered when selecting the Recycler/Factory or the Armory. *Scope:* follows item 9's research (`Docs/LOADOUT_PRESETS_RESEARCH.md`): Lua can own the preset table, the native part adds the UI.

## Fixes found in the 1.0.0.81 release (added 2026-11-23)

Do these before the "Waiting (in order)" list.

19. **DONE (CR #591, Workshop hotfix 2026-11-23).** The writer was CR's `OpenShimInstaller.lua`. It checked only the old ini and patches paths, so migrated installs read as UPDATE_REQUIRED, re-staged the suite every session, and copied the default ini payload to the root. Original note: **Find what writes a default root `openshim.ini`.** On GOG, a complete 410-key file holding only default values appeared in the game root at 21:37 on 2026-11-23. That was after 1.0.0.81 had moved the real file to `openshim\openshim.ini`. Suspects: the release stress harness (before the fix in CR #590), or a game code path that still writes the root file (EnvConfig fallback, the updater, the options writer). Find the writer from the `[LAYOUT]` log lines and a clean upgrade from 1.0.0.80. If it is the game, make it write only `Layout::OpenShimIniPath()`.
20. **Merge, don't ignore, a root ini when both files exist** (`include/openshim_layout.h`). Today the root file is ignored: `MigrateEntry` logs a `[LAYOUT] WARNING` only when the sizes differ, else a plain `kept` line. Put the merge in the `OpenShimIniPath()` path or a new helper, not in `MigrateEntry`, which also moves `patches.json` and other files. Copy into `openshim\openshim.ini` only the keys it lacks (never overwrite an existing value), then move the root file to `openshim\openshim.ini.root-merged` so it is merged once and nothing is left in the root. Log each copied key. Unit-test both-exist, sub-only and root-only.
21. **`/bzrserver` + Continue saves `Server=Custom` to the ini.** A one-off launch option becomes permanent. Decide whether that is intended. If not, keep the launch value for that session only.
22. **Community-server live fixture.** It must set `[Network] Server=Custom` before launch (the Steam Custom arm first contacted Rebellion's server because of a saved `Server=Rebellion`), and refuse to run unless the platform is signed in (Steam, or Galaxy for GOG).
23. **Re-run the GOG community-server arms** (Custom and `/bzrserver`) with Galaxy signed in. Only the Steam arms passed for 1.0.0.81.

## Cleanup still owed
- Worktree folders:
  - `GIT\BZR-OpenShim-orderqueue`: its branch is deleted, but the folder was locked by an open handle. Unlink `third_party\ogre-1.10.0-bzr\_work` first.
  - `GIT\BZR-OpenShim-buildqueue`: its PR has merged, so remove it.
  - `GIT\BZR-OpenShim-oc-research`: OpenCode trial; removal was permission denied.
- Delete the merged local branches, and prune the session scratchpad.
