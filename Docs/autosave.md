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
- After each successful save, shows "Game autosaved." on the HUD for about three seconds: a translucent black panel (16% of the viewport wide, 3% above the bottom edge) with centred light-green text in the stock HUD font, drawn with the stock HUD primitives (no EXU, no Ogre overlay). It is drawn after the stock scrap/pilot gauge each gameplay frame (`FUN_005c6f70`, text `FUN_004c0100`, fill `FUN_0068afb0`; rows in `scripts/patches.json`), through the shared gauge-draw overlay in `src/patches/hud_gauge_overlay.cpp`, which also hosts the kill ticker. A failed save shows nothing; if any engine row fails to bind the notice is skipped and logged once, and the save is unaffected. Code: `src/patches/autosave_notice.cpp`.
- Before OpenShim overwrites an existing `auto.sav`, it preserves the pre-existing file once at:
  - `Save\AutoSaveBackups\auto.pre_autosave.sav`
- If EXU or mission scripting updates `Save\auto.sav`, OpenShim notices the file timestamp change and resets its own interval instead of immediately writing another duplicate autosave.

The default schedule matches the existing Campaign Reimagined autosave behavior: an initial save becomes eligible 10 seconds after live single-player gameplay is detected, then every 120 seconds.

## Configuration

The in-game **OpenShim Options → System** screen exposes the player-facing controls:

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

## QuickSave / QuickLoad

- **Ctrl+F5** saves the running single-player mission to `Save\quick.sav` and writes `Save\quick.label.txt` (`<mission> - QuickSave`, same format as the AutoSave label). It never touches `game1.sav`-`game10.sav` or `auto.sav`. On success the HUD shows "Game quicksaved." with the AutoSave notice. Outside a live mission or with the pause/shell UI open the request is only logged; with the mission live but no AiMission yet the HUD shows "QuickSave not available yet.", and a failed SaveGame shows "QuickSave failed.".
- **Ctrl+F9** loads `Save\quick.sav` when a single-player mission is live and no pause/shell UI is open; with no file it shows "No quicksave.". It mirrors the stock load-game handler `FUN_004fbd50` (reached from command dispatch `FUN_0061dc10` case `0xE`, single player only): the save path goes into the queued-load path buffer `DAT_00945708` (`QueuedLoadPathBuffer` in `scripts/patches.json`) and `SetShellState(8)` (`FUN_00434170`, row `SetShellState`) runs the stock load state, which loads that path in `FUN_006170a0`. The stock handler also clears `DAT_009467b4`; OpenShim does not, because that is a sim-startup flag `FUN_00617110` sets on entry (line 13) and always clears before returning (line 23), so it is already `0` while a mission runs.
- Saving uses the AutoSave service: the same gate (`AutoSaveGate::Evaluate`), AiMission check, SaveGame fault latch and `missionSave` handling (`InvokeNativeNormalSaveGame`), through `SaveMissionNow` in `src/patches/autosave.cpp`. Loading uses the same gate without the fault latch, so a mission whose save faulted can still be quick-loaded. QuickSave works with `[AutoSave] Enabled=0`: the main-thread hook and SaveGame resolution are installed when either feature is on.
- Only the exact chord is taken: plain F5 (`group_select_4`), plain F9 (`weapon_select_1`) and Shift+F5/Shift+F9 keep their stock actions, and Ctrl+Alt or Ctrl+Shift chords pass through. A swallowed press has its repeats and key-up swallowed too, even if Ctrl is released first. Keys are only taken while the world is updating (not in the shell or on the loading screen). The decision is the pure `include/quicksave_key_policy.h`, tested by `tests/quicksave_key_policy_tests.cpp`.
- Input evidence: keyboard input is message-driven. The main WndProc `FUN_00619340` hands `WM_KEYDOWN`/`WM_KEYUP` (`0x100`/`0x101`) to `FUN_00619be0`, which feeds `FUN_00434bf0(scancode, down)`; raw input is only used for the mouse, and Ctrl is read with `GetKeyState(VK_CONTROL)` (`FUN_00619f60`). `FUN_00619be0` then drains the remaining queued keyboard messages itself with `PeekMessageA(0x100..0x109, PM_REMOVE)` (its decompile line 58), so those never reach a window procedure. OpenShim therefore filters in two places that share one swallow state: a subclass of the game window and the exe's `PeekMessageA` import (the drain loop and the main pump `FUN_006192b0` both call it). Both are installed lazily from the main-thread tick and chain to whatever was there before (`background_run.cpp` and `ui_performance_hooks.cpp` use the same import).
- The load screen gets a 12th button, "QuickSave" (label from `quick.label.txt`), directly below the injected AutoSave button (Y = 180 + 11 * 68), shown only while `quick.sav` exists. Both buttons are built by the same code in `src/patches/autosave_restart.cpp`, which sets both the click (`+0x154`) and hover (`+0x150`) callback slots.
- Setting: `[QuickSave] QuickSaveEnabled=1` (default on; the key is not `Enabled` because Options rows need unique ini keys), and the **QuickSave Keys** row on **OpenShim Options → System**, next to the AutoSave rows. It applies immediately. The keys are fixed.

## EXU coexistence

EXU is not required. Its public C API does not currently expose the native save function, so OpenShim resolves the already-reverse-engineered BZR serializer directly rather than depending on Lua or `exu.dll`.

Campaign Reimagined no longer ships its EXU-backed `AutoSave.lua`; OpenShim's schedule and notice cover stock campaigns, expansion/single-player missions, Instant Action, and custom single-player missions that support BZR's normal save/load serialization. If an older mod still runs a Lua autosave, both target the same `Save\auto.sav`; `RespectExternalAutoSave=1` makes OpenShim treat an external update of that file as the latest autosave and defer its own next write. Such a Lua autosave draws its own notice, if any.

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
11. QuickSave: with `[AutoSave] Enabled=0`, press Ctrl+F5 in a mission; confirm `Save\quick.sav`, `quick.label.txt`, the "Game quicksaved." notice, and that unit group 4 was not selected. Hold Ctrl first for a second (Ctrl autorepeat) and repeat.
12. Press Ctrl+F9; confirm the mission reloads from `quick.sav` and weapon 1 was not selected. Plain F5/F9 and Shift+F5/F9 still do their stock actions.
13. Open the Load screen; confirm the QuickSave button sits below the AutoSave button, shows the label, loads, and that opening the screen does not crash.
