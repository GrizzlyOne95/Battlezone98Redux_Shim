# Engine-Level AutoSave

OpenShim can own single-player autosaving without requiring EXU or mission Lua.

## Behavior

- Enabled by default for active single-player gameplay.
- Disabled automatically for network games.
- Does not save while the pause/options/save/load/restart UI is active or while another cursor-driven shell screen is active. Terrain edit mode (`0x009454B8`) is **not** treated as a hard no-save condition: unscripted single-player / Instant Action missions can carry that flag while still allowing a manual SaveGame, so OpenShim only logs its state as diagnostic and leaves the save eligible. Dump `battlezone98redux.exe.38660.dmp` was taken with `editMode=1`, `wrapperActive=1`, `screenType=1` and showed the previous gate would have permanently suppressed the timer that had been armed at `09:38:20.698` with `initialDelay=10000ms`.
- Uses BZR's native `SaveGame(char*, int)` serializer on the game/main thread.
- Establishes the stock normal-save state (`missionSave=0`) around each direct
  serializer call, including the exception path, then restores the flag's prior
  value. `missionSave` lives at `0x009173B7`, decoded at runtime from the
  `movzx eax, byte ptr [missionSave]` at `SaveGame` entry `+37` rather than
  hard-coded, so an unrecognised build fails closed instead of writing to a
  wrong address. The decode and its drift-rejection cases are covered by
  `tests/native_save_flag_tests.cpp`.

  This matters because `FUN_004fbe90`, Redux's mission/terrain-template save,
  sets that global and never clears it. While it is set, `SaveGame` omits
  `runType`, `saveGameDesc`, the mission-status block (`FUN_004fd7e0`),
  `start_time` and the entire `[AiTasks]` section (`FUN_00461d90`), and the
  matching load path skips the post-load handle remap in `FUN_005c7a50` — so an
  autosave taken in that state restores without valid object handles.

  The prior value is restored rather than forced to `0` because `FUN_004fbe90`
  sets the flag and *then* opens a modal dialog
  (`FUN_0056ad10` → `FUN_005d48c0` → `FUN_005d4690`, which runs its own event
  loop). An autosave landing inside that window would otherwise clear a flag the
  engine is still relying on and silently downgrade the user's mission save to a
  normal one. The gate cannot be relied on to exclude that window on its own: it
  reads `uiWrapperActive` at `0x00918324`, which only `FUN_005d42e0` sets, not
  the mission-save dialog path.
- Writes the established autosave path used by Campaign Reimagined and OpenShim's injected load button:
  - `Save\auto.sav`
  - `Save\auto.label.txt`
- Before OpenShim overwrites an existing `auto.sav`, it preserves the pre-existing file once at:
  - `Save\AutoSaveBackups\auto.pre_autosave.sav`
- If EXU or mission scripting updates `Save\auto.sav`, OpenShim notices the file timestamp change and resets its own interval instead of immediately writing another duplicate autosave.

The default schedule matches the existing Campaign Reimagined autosave behavior: an initial save becomes eligible 10 seconds after live single-player gameplay is detected, then every 120 seconds.

## Configuration

The in-game **OpenShim Settings** page exposes the two player-facing controls:

- **AutoSave** - On/Off. Applies immediately.
- **AutoSave Interval** - 1, 2, 3, 5, or 10 minutes. Applies immediately and restarts the current interval from the time it is changed.

The 10-second initial grace period, retry timing, migration backup, and EXU/legacy coexistence controls remain advanced INI-only settings.

The same values are stored in `<BZR game directory>\openshim.ini`:

```ini
[AutoSave]
Enabled=1
IntervalSeconds=120
InitialDelaySeconds=10
RetrySeconds=15
BackupExisting=1
RespectExternalAutoSave=1
```

`IntervalSeconds` is clamped to 10-3600 seconds. `InitialDelaySeconds` is clamped to 0-600 seconds. `RetrySeconds` is clamped to 5-120 seconds.

Set `Enabled=0` to retain OpenShim's AutoSave load-button support while disabling engine-level automatic save creation. The in-game AutoSave toggle writes this same key.

## EXU coexistence

EXU is not required. Its public C API does not currently expose the native save function, so OpenShim resolves the already-reverse-engineered BZR serializer directly rather than depending on Lua or `exu.dll`.

If a mission still runs the older EXU-backed `AutoSave.lua`, both systems target the same `Save\auto.sav`. `RespectExternalAutoSave=1` makes OpenShim treat an external update of that file as the latest autosave and defer its own next write. Once mission-local autosave calls are removed, OpenShim continues the same schedule globally for stock campaigns, expansion/single-player missions, Instant Action, and custom single-player missions that support BZR's normal save/load serialization.

## Runtime validation checklist

Before merging/releasing, test at minimum:

1. Start a stock campaign mission and confirm `Save\auto.sav` appears after the initial delay.
2. Load the generated save through OpenShim's injected AutoSave load button.
3. Remain in live play through at least two intervals and verify the file timestamp advances.
4. Pause across an expired deadline and verify the save occurs after returning to live play, not in the pause menu.
5. Enter save/load/options screens around a deadline and verify no save is issued until gameplay resumes.
6. Transition between missions and verify the initial-delay timer resets.
7. Run Instant Action and verify the same behavior without any mission Lua changes.
8. Join/host multiplayer and verify no `auto.sav` writes are generated by OpenShim.
9. Repeat a Campaign Reimagined mission with EXU/legacy `AutoSave.lua` still active and confirm OpenShim logs an external autosave update rather than issuing a near-duplicate save.
10. Verify `logs\openshim.log` contains `autosave` initialization/save entries and no native-save exceptions.
