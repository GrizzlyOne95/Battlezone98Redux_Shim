# Battlezone Co-op Campaign Netcode Notes

Purpose: document the concrete behavior found while tracing Battlezone mission multiplayer behavior, the working co-op references, the EXU multiplayer helpers, and the implications for converting `misn02b` into a reliable co-op mission.

This note prefers direct code or Lua sources. When a point is a deduction from those sources rather than a direct statement, it is marked as `Inference`.

## Primary Source Set

- Stock mission API notes: [ScriptingGuide.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/ScriptingGuide.txt#L41)
- Stock script stubs: [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1974)
- Current co-op template: [coop_template.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/coop_template.lua#L17)
- Current single-player target mission: [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L268)
- Workshop co-op example: [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L215)
- Reloaded co-op mission framework: [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L78)
- Reloaded mission wrapper: [rl_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_mission.lua#L165)
- Reloaded NSDF co-op mission: [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L167)
- EXU function docs: [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L174) and [ExtraUtils.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/ExtraUtils.lua#L1072)
- Legacy engine decomp for mission netcode: [Send-00419760.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Send-00419760.c#L30), [Receive-0041ca92.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Receive-0041ca92.c#L2)

## High-Level Conclusions

- Stock Battlezone mission multiplayer is not a single unified sync system.
- Object existence and some world state ride the distributed object layer, but mission UI and camera state do not.
- Reliable mission synchronization requires explicit script messaging or a higher-level framework.
- The one proven workshop example works by host authority plus client-side reconstruction, not by a clean fully synchronized mission state machine.
- Reloaded's co-op framework is the cleanest reference because it wraps state changes, mission variables, victory or loss, and client barriers explicitly.
- `Inference`: a separate multiplayer `.bzn` is the safer path for co-op `misn02b`, because every working reference found ships as a dedicated multiplayer mission package with its own map assets.

## Engine-Level Facts From Decomp

### `Send` and `Receive` are the mission-level RPC mechanism

- The Lua `Send` binding packs arbitrary supported Lua values with `PackValue` and calls `Net::Send` in [Send-00419760.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Send-00419760.c#L35) and [Send-00419760.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Send-00419760.c#L48).
- The Lua mission receive path unpacks those values with `UnpackValue` and calls script `Receive(...)` in [Receive-0041ca92.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Receive-0041ca92.c#L12) and [Receive-0041ca92.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Receive-0041ca92.c#L23).
- Practical rule: if a piece of mission state is not obviously part of distributed object simulation, `Send` and `Receive` is the stock way to move it across machines.

### `AddObjective` and `ClearObjectives` are local UI calls

- `AddObjective` calls `InfoDisplay::AddObjective` in [AddObjective-00415e0d.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AddObjective-00415e0d.c#L5).
- `ClearObjectives` calls `InfoDisplay::ClearObjectives` in [ClearObjectives-00415e03.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ClearObjectives-00415e03.c#L5).
- Practical rule: objective text and color changes must be replayed on every machine. They do not become synchronized just because mission objects are synchronized.

### `CameraPath` is local camera state

- Native `CameraPath` is a camera motion helper in [CameraPath-0046091a.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/CameraPath-0046091a.c#L2).
- There is no evidence in this function of mission packet broadcasting.
- Practical rule: cinematics must be coordinated explicitly. A local `CameraPath` call is not enough for co-op sync.

### `SetObjectiveOn` is not an explicit mission packet send

- Lua `SetObjectiveOn` forwards to native code in [SetObjectiveOn-00417a3d.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/SetObjectiveOn-00417a3d.c#L2).
- Native `SetObjectiveOn` gets the object and calls `GameObject::SetObjective(this, true)` in [SetObjectiveOn-0045f3e5.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/SetObjectiveOn-0045f3e5.c#L7) and [SetObjectiveOn-0045f3e5.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/SetObjectiveOn-0045f3e5.c#L9).
- This lines up with the observed note in [ScriptingGuide.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/ScriptingGuide.txt#L71): objective markers are not synced by default.
- Practical rule: treat objective markers as unreliable unless the mission framework explicitly replays them or the object sync path happens to carry enough state in that case.

### `GetPlayerHandle(team)` is a real engine query, but observed Redux behavior is still suspect

- The legacy engine function resolves through `GetTeamSlot(TEAM_SLOT_PLAYER, team)` in [GetPlayerHandle-00460ac4.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/GetPlayerHandle-00460ac4.c#L7).
- The Lua binding exists in [GetPlayerHandle-00416d5c.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/GetPlayerHandle-00416d5c.c).
- But the observed note in [ScriptingGuide.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/ScriptingGuide.txt#L85) says passing a team number returns `nil` for remote players in practice.
- Practical rule: do not build a co-op mission around remote `GetPlayerHandle(team)` working correctly. Synchronize the relevant handles or labels yourself.

### `SetLocal` is the ownership override, not a universal fix

- Native `SetLocal` calls `DistributedObject::SetLocal` in [SetLocal-0045ee6f.c](C:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/SetLocal-0045ee6f.c#L9).
- The practical warning in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1980) says calling `SetLocal` on a remote object can irreversibly break their AI.
- The mission notes in [ScriptingGuide.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/ScriptingGuide.txt#L58) say both machines may need to cooperate for hiding behavior, and careless usage creates split-brain behavior.
- Practical rule: for co-op campaign work, prefer host authority and synchronized object creation over trying to rescue an object later with `SetLocal`.

## Stock Script API Facts

- The stock API exposes `IsHosting()` in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1976), not `IsHost()`.
- The stock API exposes `Send(...)` in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L2033).
- The stock API exposes `SetObjectiveOn`, `ClearObjectives`, `AddObjective`, `GetPlayerHandle`, and `CameraPath` in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L678), [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1319), [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1326), [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1001), and [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1894).

## Workshop Mission `multmp17` Findings

- Host-only object creation happens in [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L215).
- The mission sets tower objective names and objective markers immediately on the host in [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L236).
- Clients do not trust local state initially. They poll the host for counts and cutscene flags in [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L282).
- Clients then scan `AllObjects()`, rebuild handle tables, sort by label-derived numeric suffix, and locally reapply objective names and markers in [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L261) and [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L276).
- The mission `Receive` function only handles host replies for counts and cutscene completion data in [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua#L400).
- Practical rule: this script proves that co-op campaign can work, but it is a reconstruction model, not a seamless deterministic state-sync model.

## Reloaded Co-op Framework Findings

### Synchronized state changes

- Reloaded wraps state changes so the host broadcasts a transition and waits for acknowledgements in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L62), [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L70), and [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L80).
- Clients request a host-broadcasted change rather than mutating mission state independently in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L93).

### Synchronized mission and state variables

- Mission-scoped sync uses `sync_mission_var` in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L178) and [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L210).
- Per-state sync uses `sync_state_var` in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L191) and [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L244).
- Practical rule: co-op missions should treat phase variables, critical handles, and readiness flags as explicitly synchronized data.

### Synchronized victory or loss

- Reloaded wraps success and failure with `wait_for_all_clients` and then broadcasts `SucceedMission` or `FailMission` in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L273) and [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L282).
- Practical rule: do not let each machine independently call mission end conditions.

### Host-only synchronized building

- Base mission building routes through `exu.BuildSyncObject` in [rl_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_mission.lua#L165).
- Co-op missions override single-object building so only the host creates the object in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L133).
- Practical rule: synchronized object creation plus host-only authority is the cleanest spawn model found.

### Example: Reloaded co-op `misn02b` equivalent

- The closest concrete pattern for `misn02b` is Reloaded's NSDF co-op mission in [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L124).
- The first scavenger transition waits for all clients after the event listener fires in [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L167) and [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L174).
- The second scavenger is built through the co-op mission object builder and only the host retains the handle locally in [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L293).
- The script comment in [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua#L298) states that `SetObjectiveOn(scav)` propagates in that setup.
- `Inference`: the propagation works because of the framework and synchronized object ownership model, not because raw stock `SetObjectiveOn` is globally reliable on its own.

## EXU Multiplayer Functions

### EXU surface area

- EXU documents `BuildAsyncObject`, `BuildSyncObject`, `GetLives`, `SetLives`, `GetMyNetID`, and `DisableStartingRecycler` as multiplayer-only helpers in [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L174).
- The Lua surface also exists in [ExtraUtils.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/ExtraUtils.lua#L1076), [ExtraUtils.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/ExtraUtils.lua#L1080), and [ExtraUtils.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/ExtraUtils.lua#L1106).

### Meaning of the build helpers

- `BuildAsyncObject` is documented as "always asynchronous regardless of hosting status" in [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L177).
- `BuildSyncObject` is documented as "always synchronized regardless of hosting status" in [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L180).
- Reloaded uses `BuildSyncObject` for normal mission object creation in [rl_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_mission.lua#L167).
- Reloaded uses `BuildAsyncObject` for per-player helper objects like the shared satellite scaffolding in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L289).
- Practical rule: `BuildSyncObject` is the better default for mission-critical co-op actors. `BuildAsyncObject` looks suited to player-local or intentionally unsynchronized support objects.

### EXU net identity and lives

- EXU exposes `GetMyNetID()` in [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L189).
- Reloaded uses `exu.GetMyNetID()` to avoid messaging the current player during state broadcast in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L64).
- EXU exposes `SetLives` in [EXU_Functions.txt](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Config/EXU_Functions.txt#L186), and Reloaded wires it into multiplayer via `vsp.net.set_function("set_remote_lives", exu.SetLives)` in [rl_coop_mission.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Scripts/rl_coop_mission.lua#L117).
- Practical rule: EXU gives useful multiplayer helpers, but the authoritative sync model still comes from the mission framework on top of them.

## `misn02b.lua` Conversion Blockers

- The current mission still behaves as a single-player mission that happens to use modern QoL helpers.
- The intro cameras are local and keyed off local audio or cancel state in [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L492) and [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L516).
- The mission directly adds and clears objectives locally in [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L547), [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L589), [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L600), and [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L656).
- The second scavenger is built inline during update logic in [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L615), and enemy waves are also built directly in [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L553), [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L582), and [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L648).
- Failure and victory are local direct calls in [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L608) and [misn02b.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/misn02b.lua#L667).
- Practical rule: `misn02b` needs a host-authoritative phase machine, not just small sync patches.

## Current Template Issues

- The template uses `IsHost()` in [coop_template.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/coop_template.lua#L17), but the stock API exposes `IsHosting()` in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L1976).
- The template comments already admit player-handle sync is unfinished in [coop_template.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/coop_template.lua#L22).
- The template's `Receive` stub is not using stock `Send` semantics correctly for the documented one-character type string path in [scriptutils.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/External/Defs/scriptutils.lua#L2007) and [coop_template.lua](C:/Users/istuart/Documents/GIT/Battlezone98Redux_CampaignReimagined-1/Scripts/coop_template.lua#L110).

## Separate Multiplayer `.bzn` Evidence

- The workshop co-op mission ships as a dedicated multiplayer asset pack: [multmp17.bzn](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.bzn), [multmp17.trn](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.trn), and [multmp17.lua](C:/steamcmd/steamapps/workshop/content/301650/1660494958/multmp17.lua).
- Reloaded co-op NSDF missions also ship as dedicated multiplayer mission packages: [nsdf01c.bzn](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.bzn), [nsdf01c.trn](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.trn), and [nsdf01c.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/Multiplayer/Campaigns/NSDF%20Coop/Missions/NSDF01%20-%20Red%20Arrival/nsdf01c.lua).
- Stock single-player `misn02b` is its own SP mission package: [misn02b.bzn](C:/Users/istuart/Documents/Battlezone-Reloaded/References/BZ1_mission_source/bz1/base/bz1_lua_from_GBD/misn02b.bzn) and [misn02b.lua](C:/Users/istuart/Documents/Battlezone-Reloaded/References/BZ1_mission_source/bz1/base/bz1_lua_from_GBD/misn02b.lua).
- `Inference`: a co-op `misn02b` should probably be a separate multiplayer map package rather than trying to force the SP `.bzn` to behave like a multiplayer mission. The evidence is consistent across every working example found.
- `Inference`: the separate MP `.bzn` likely matters for spawn layout, player slots, recycler behavior, and multiplayer-specific mission startup assumptions even before Lua runs.

## Practical Rules For A Reliable Co-op `misn02b`

- Use a dedicated multiplayer mission package with its own `.bzn`, `.trn`, and `.lua`.
- Make the host authoritative for mission phase, object creation, wave timing, and win or loss.
- Use `Send` and `Receive` or a framework wrapper to broadcast phase changes, readiness, and UI updates.
- Replay objective text and camera phase changes on every machine.
- Prefer `exu.BuildSyncObject` for mission-critical units and buildings.
- Use `BuildAsyncObject` only when you intentionally want asynchronous or player-local support objects.
- Do not rely on remote `GetPlayerHandle(team)` as your primary identity mechanism.
- Treat `SetObjectiveOn` as framework-dependent, not universally reliable by itself.
- Treat `SetLocal` as a dangerous ownership tool, not a generic multiplayer synchronization patch.

## Suggested Next Implementation Step

- Create a `misn02c` or similarly named multiplayer mission package with a dedicated `.bzn`.
- Build a small reusable co-op mission shim for campaign missions.
- The shim should provide host-authoritative phase changes.
- The shim should provide synchronized mission variable broadcast.
- The shim should provide client-ready barriers for cinematics and objective transitions.
- The shim should provide synchronized succeed or fail wrappers.

That shim can then be used to port `misn02b` one phase at a time instead of trying to retrofit full co-op behavior into the current single-player mission script.
