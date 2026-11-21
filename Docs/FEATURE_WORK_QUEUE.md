# BZR OpenShim work queue (recorded 2026-11-17, updated 2026-11-18)

Standing: merge as you go (squash + auto-merge after local CI, a live test for native/gameplay changes, and a fresh-eyes review). New options default OFF.

Live tests still owed: `Docs/LIVE_TEST_BACKLOG.md`.

## Done
- **5. Build queue** (`[Gameplay] RtsBuildQueue`). Branch `agent/rts-build-queue`, worktree `GIT\BZR-OpenShim-buildqueue`, commit 87ffa19a9 (amended), rebased on main 153c9bae6.
  - PR #898, MERGED.
- **12. Remove the name/flag panels from the MP lobby:** PR #896, MERGED.

## In review
- **6. Follow camera** (`[Gameplay] RtsFollowCamera`, Shift+C in satellite). Branch `agent/follow-camera`, PR #900, built in a cloud session: Linux CTest green, both engine rows byte-checked against the GOG 2.2.301 exe, Win32 build left to CI. **Needs the live test** (`Docs/RTS_COMMANDS.md`, checklist 11b) before merge.

## Waiting (in order)
7. **Map pings on orders.**
8. **FPS quick-commands:** research.
9. **Loadout presets:** research. Handed to Copilot, see `Docs/COPILOT_BRIEF_LOADOUT_PRESETS.md`.
10. **Tread texture scroll.**
11. **Walker free-turning head:** research and plan first.

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

## Cleanup still owed
- Worktree folders:
  - `GIT\BZR-OpenShim-orderqueue`: its branch is deleted, but the folder was locked by an open handle. Unlink `third_party\ogre-1.10.0-bzr\_work` first.
  - `GIT\BZR-OpenShim-buildqueue`: its PR has merged, so remove it.
  - `GIT\BZR-OpenShim-oc-research`: OpenCode trial; removal was permission denied.
- Delete the merged local branches, and prune the session scratchpad.
