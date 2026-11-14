# Multiplayer mission end sync (2026-10-27)

`[Fixes] MissionEndSync` (default on; `OPENSHIM_DISABLE_MP_MISSION_END_SYNC` / `BZR_DISABLE_MP_MISSION_END_SYNC` force it off). Source: `src/patches/mp_mission_end_sync.cpp`.

## Defect

Lua `SucceedMission` / `FailMission` both call `AiMission::End` (0x0045DAF0, `__thiscall(this, float shutdownTime, const char* name, char failed)`). No stock net message carries a mission end, so when only the host's script ends the mission, guests keep running it.

## Fix

Two inline detours, installed together or not at all (each guarded by its first 9 bytes):

* `AiMission::End` (host): after the original runs, an in-game session whose `IsHost()` is true broadcasts `'M' 'E' version=1 failed float(shutdownTime) name[13]` (21 bytes) through the engine send (0x00575890, reliable broadcast as Lua Send uses it).
* Net dispatcher 0x00570500 (guest): a 21-byte-or-longer message with tag `0x454D` and version 1 is consumed; it is applied by calling the original `End` only if the sender is the host (0x0056FC40), not this machine, and the current mission exists and is not already done. Other tags reach the stock dispatcher unchanged.

Stock peers treat the unknown tag as a silent fall-through, so mixed sessions are safe; only patched guests end.

All addresses are named rows in `scripts/patches.json` (`AiMission::End`, `Net::Receive`, `Net::BroadcastSend`, `Net::Session`, `Net::IsPlayerHost`, plus the existing `GetLocalPlayerNetId`, `IsHost`, `CurrentAiMission`), each verified unique in the GOG image on 2026-10-27.

## Verification

Co-op harness, two clients on the private server (`reverse_engineering/Run-BZRMpBugs.ps1 -Case MissionEnd -Expect Fixed`), each 19 checks, 0 failed:

* `mpbugs-me-fixed-2`: host calls `SucceedMission`. Both peers leave with `RUN_WAS_SUCCESS`.
* `mpbugs-me-fixed-fail-host-2` (`-ScenarioArgs @{ Result = 'fail' }`): host broadcasts `failed=1`; both peers leave with `RUN_WAS_FAILURE`.
* `mpbugs-me-fixed-all-1` (`Caller = 'all'`): every peer calls it. The host's message reaches the guest before the guest's own call, so the guest applies it; its own later call rewrites the same fields and does not rebroadcast.

The send's return value is not a delivery flag (it was 0 on every run above, and the guest still applied the message). `-Expect Stock` turns this fix off in each instance's ini, so the stock defect stays reproducible on a fixed build.
