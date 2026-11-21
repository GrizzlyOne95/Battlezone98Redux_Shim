# BZR OpenShim work queue (recorded 2026-11-17)

Standing: merge as you go (squash + auto-merge after local CI, a live test for native/gameplay changes, and a fresh-eyes review). New options default OFF.

Live tests still owed: `Docs/LIVE_TEST_BACKLOG.md`.

## Done
- **5. Build queue** (`[Gameplay] RtsBuildQueue`). Branch `agent/rts-build-queue`, worktree `GIT\BZR-OpenShim-buildqueue`, commit 87ffa19a9 (amended), rebased on main 153c9bae6.
  - PR #898, MERGED.
- **12. Remove the name/flag panels from the MP lobby:** PR #896, MERGED.

## Waiting (in order)
6. **Follow camera.** Ghidra research is done. Shift+C, satellite only: call FUN_00588970(0x009C9170, obj) each tick.
7. **Map pings on orders.**
8. **FPS quick-commands:** research.
9. **Loadout presets:** research. Handed to Copilot, see `Docs/COPILOT_BRIEF_LOADOUT_PRESETS.md`.
10. **Tread texture scroll.**
11. **Walker free-turning head:** research and plan first.

## Cleanup still owed
- Worktree folders:
  - `GIT\BZR-OpenShim-orderqueue`: its branch is deleted, but the folder was locked by an open handle. Unlink `third_party\ogre-1.10.0-bzr\_work` first.
  - `GIT\BZR-OpenShim-buildqueue`: its PR has merged, so remove it.
  - `GIT\BZR-OpenShim-oc-research`: OpenCode trial; removal was permission denied.
- Delete the merged local branches, and prune the session scratchpad.
