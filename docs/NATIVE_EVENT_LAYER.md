# OpenShim Native Event Layer

Status: implemented (dispatch layer, simulation event sources, career-stats
consumer, `[Career] StatsTracking` toggle). Not yet runtime-validated in game.

This is the OpenShim half of the "native event/callback system" roadmap item.
It gives OpenShim, and eventually EXU, a way to be *told* about simulation
events instead of polling for them, and it is what makes engine-level career
statistics work in all single-player and multiplayer content without any
mission ever implementing tracking.

---

## 1. What already existed

Two pieces were already in the tree and are worth naming, because neither was
replaced.

**SDK v2 event queue** (`include/BZROpenShim.h`, `src/engine/openshim_sdk_v2.cpp`).
An ABI-stable `OpenShimEvent` record, a bounded ring, and `ApiPollEvent` in the
v2 function table so a companion DLL can *poll* events. Its event types were
shim lifecycle only: `ShimInitialized`, `CompatibilityChanged`,
`PatchingCompleted`, `ShutdownStarted`, `DeveloperSnapshotCaptured`,
`NativeUiAction`. Nothing about the game world, and no way for OpenShim's own
code to subscribe.

**EXU's `BulletHit` patch** (`ExtraUtilities/src/Patches/BulletHitCallback.cpp`,
hook at `0x00480771`). A real ordnance-impact event with shooter, hit object,
transform and ordnance class — but it calls `lua_pcall` from inside the hook,
which is exactly the pattern the roadmap item says not to build on.

## 2. What this adds

### 2.1 In-process dispatch

`include/openshim_events.h` / `src/patches/openshim_events.cpp`.

`PublishOpenShimEvent` now also copies each record into a second, in-process
dispatch ring. `DispatchPendingEvents()` drains that ring on a known-safe
per-frame point and hands each record to registered sinks.

The SDK polling queue is untouched, so a companion polling it and a shim
subsystem subscribing here both see the same events.

Producer contract (`PublishSimEvent`): `noexcept`, no allocation, no file I/O,
one SRW lock held for the length of a struct copy, drops rather than stalls
when the ring is full. Safe from any engine hook context.

Consumer contract (sinks): run on the drain, on the main thread, with no lock
held. May allocate and do file I/O. A sink that publishes queues for the *next*
drain — the drain copies its batch out before invoking anything, so
re-entrancy can neither deadlock nor livelock inside one frame.

The drain point is `TickOpenShimEventLayer()` in
`LegacyWorldUpdateRenderQueueHook`, beside `TickMpGateReconcile()`. That Ogre
world-queue callback runs every rendered frame a world exists, and is already
the shim's designated safe per-frame driver.

### 2.2 Simulation events

Appended to `OpenShimEventType` (append-only; the numbering is wire-stable for
companions):

| Type | slot0 | slot1 | slot2 | slot3 |
|---|---|---|---|---|
| `SimSessionStarted` | 1 = network game | — | — | — |
| `SimSessionEnded` | 1 = network game | — | — | — |
| `SimDamage` | victim handle | damager handle | victim is local player | damager is local player |
| `SimKill` | victim handle | damager handle | victim is local player | damager is local player |
| `SimTeamDeath` | killed team | killer team | — | — |

The four `int32` slots are packed into the record's `arg0`/`arg1` by
`PublishSimEvent` and unpacked by `SimEventArg`.

`SimDamage` is delivered to in-process sinks **only**. It fires per damage
application; letting it into the 256-entry polling queue would evict the
lifecycle events companions actually poll for.

## 3. Event sources, and the evidence for them

### 3.1 Damage — the four existing probe sites

OpenShim already replaces the four rel32 calls to `GameObject::SetDamageFlags`
(`0x004DC130`) as `Damage Reveal Probe 1..4/4` in `scripts/patches.json`:
`0x0047EFA0`, `0x004AA678`, `0x005A0CE2`, `0x005AA372`. Those are the engine's
four damage handlers, not net code, so they run in single player and network
games alike.

`DamageRevealProbeHook` reads `DAMAGE[0]` (damager obj76) and `DAMAGE[1]`
(dmg_source obj76) — the only two fields `SetDamageFlags` itself reads — and
resolves obj76 → GameObject with the engine's own accessor at `0x00479F30`.
No struct offset is assumed on this path.

### 3.2 Kill — derived, not hooked

`SetDamageFlags` runs *before* the damage is applied, so it cannot report a
kill. Each of the four handlers then applies damage and tests:

```c
if (healthRatio <= 0.0 && healthRatio != 0.0 &&
    (objectState->flags & 0x200) == 0) {
    objectState->flags |= 0x200;              // unconditional
    if (isNetGame() && GetTeam() != 0) {
        RecordDeath(...); NotifyScore(...);   // network only
    }
}
```

The latch write is outside the network gate. So instead of adding three or four
new inline patch sites, the layer records the damage association at
`SetDamageFlags` time and resolves the death on the next safe tick. That is the
same pending-victim design Campaign Reimagined's `Scripts/CareerStats.lua`
already validated in Lua (`PendingVictims` / `PendingTimeout`), lifted into the
engine layer.

Resolution re-resolves by **handle**, never by the stored pointer: the object
arena is a fixed slot table, so a freed slot is reused at the same address by
the next object, and only the handle's generation bits distinguish them.

Field evidence:

| Field | Offset | How it was established |
|---|---|---|
| `healthRatio` | complete + `0x200`, float | `GameObject::Save` (`0x004DE110`) emits `::out(file, this + 0x200, 4, "healthRatio")`; the four damage handlers test the same float |
| object state | complete + `0xF4`, pointer | already read at the same offset by `GameObjectHandleGetObjHardened` |
| death latch | objectState + `0x14`, bit `0x200` | set exactly once per object, by the block above |

The engine's test is `<= 0.0 && != 0.0`, i.e. strictly less than zero — exactly
`0.0` is not death. The layer mirrors that rather than "fixing" it, and treats
the latch as the primary signal.

### 3.3 Team death — network only, and structurally so

`NetPlayer::RecordDeath` (`0x00577290`) has exactly one caller, the score-notify
helper `0x004B9BA0`, and every one of that helper's call sites is guarded by
`0x00572A70` → `0x00571C40`, whose entire body is `return DAT_00917F7B` — the
`isNetGame` global (the same address EXU's catalog lists as
`Multiplayer.isNetGame`).

So this path can never produce a single-player statistic. That is why it is not
the basis for the general career tracker, and why it remains in use for network
games: it is the engine's own authoritative scoring path.

### 3.4 Session lifecycle

Published from the same world-liveness predicate the satellite fix uses
(`SatelliteWorldIsLive()`), so single player and network games share one
session model.

Ordering consequence, by design: the driver stops running when the world goes
away, so a `SimSessionEnded` queued on the last frame is delivered on the
*first* frame of the next world, immediately before that world's
`SimSessionStarted`. Consumers see the right order, just late; nothing in the
sink depends on the dead world, and the pending-victim table is also cleared
synchronously at the transition.

## 4. The career-statistics consumer

`career_stats.cfg`, next to the game executable, keyed by profile and mission.

* **Single player** uses the damage-derived path: per-object attribution
  against the local player.
* **Network games** keep using `RecordDeath`.

They do not double-count: `CareerRecordDerivedKill` returns early unless
`IsSinglePlayerSession()`, and the `SimTeamDeath` case is the only writer in a
network game. A client's local damage simulation is not authority, so counting
both would inflate every match.

**Local-player identity is sampled at damage time, not at kill time.** The
player handle moves the instant the player's craft dies — a destroyed craft
ejects a pilot and `GetPlayerHandle` then names the pilot — so comparing
handles after the fact would miss every one of the player's own deaths. The two
flags ride in `SimDamage`/`SimKill` slots 2 and 3 and are sticky.

`RecordDeathHook` no longer persists inline. It previously loaded and rewrote
`career_stats.cfg` synchronously on every death, holding an SRW lock across a
disk write from inside a detour. It now publishes; the sink does the same work
on the next drain. The direct call survives only as a fallback for a full
dispatch ring, so a queue overflow cannot silently lose a multiplayer death.

Keys written:

```
profile.<key>.career.totalKills / totalDeaths
profile.<key>.career.spKills / spDeaths / mpKills / mpDeaths
profile.<key>.career.missionsPlayed / spMissionsPlayed / mpMatchesPlayed
profile.<key>.mission.<mission>.kills / deaths / plays
```

Campaign Reimagined's `CareerStats.lua` writes the same file with the same key
layout, so totals add rather than conflict. Installations that want exactly one
writer should turn one of the two off.

## 5. Configuration

`openshim.ini`:

```ini
[Career]
StatsTracking = 1
```

Default is ON, which is what an absent key does and what the native tracker has
always done. Also exposed as the **Career Stats** row on the native Settings
page, and disableable through `OPENSHIM_DISABLE_CAREER_STATS`.

Registered in the feature registry as `Display` tier: observational, writes only
its own file, and must keep running in network games.

Turning it off unsubscribes the sink. Every simulation event source is gated on
`HasEventSubscribers()`, not on the career flag, so "career stats off and
nothing else listening" collapses to a single interlocked read on the damage
path — and a future subscriber gets the events without being wired into a
career-specific predicate.

### 5.1 Reset Career Stats

A second Settings row, **Reset Career Stats**, clears the record. It is the
first *action row* on that page: `ShimSettingApplyGroup::CareerStatsReset` with
a null section and key, so nothing in the ini read or lossless-write path
treats it as a setting, and clicking runs something instead of cycling a value.

It takes **two clicks**. The first arms the row and repaints its value cell to
`Confirm?`; the second commits. Clicking any other row, stepping pages, or
leaving the page disarms it. A destructive action must not happen on a single
click of a row the player was only trying to read.

The previous contents are copied to `career_stats.cfg.openshim.bak` before the
file is rewritten, so one accidental wipe of a long campaign record is
recoverable. A backup that cannot be written is reported to the log but does
not abort the reset — the reset is still what was asked for.

The reset deliberately does **not** touch the tracking toggle. "Reset my stats"
is not "stop recording", and a reset that also disabled tracking would silently
stop counting from that point on.

The bridge entry point is `ResetCareerStatsFromBridge()`, returning
`Cleared` / `AlreadyEmpty` / `Failed`. A file holding only `meta.version` counts
as already empty — that is what a previous reset leaves behind.

## 6. What is not done yet

* **Runtime validation.** Nothing here has been exercised in game. The
  falsifiable claims are listed in §7.
* **The rest of the roadmap item's event list.** `OnTargetChanged`,
  `OnPilotEnter`/`OnPilotExit`, `OnCommand`, `OnBuildSelection`,
  `OnWeaponFired`, `OnPlayerJoined`/`OnPlayerLeft` are not implemented. The
  layer is now the place to add them: each is one producer plus one enum value.
* **The EXU-facing Lua surface.** Companions can already poll the new
  simulation events through the existing v2 function table, but EXU does not yet
  expose them to Lua, and EXU's `BulletHit` still calls Lua from inside its
  hook. Migrating that to a producer here is the natural follow-up.
* **Per-object kill feed for multiplayer career stats.** `SimKill` is published
  in network games too and is available to consumers; it is deliberately not
  counted into the career file there, pending an authority model.

## 7. Runtime validation checklist

1. Start a single-player mission. Expect one `[CAREER] Recorded single-player
   mission start` line, and `spMissionsPlayed` incrementing once per mission
   entry — not once per frame, and not on the shell.
2. Kill an enemy craft. Expect `career.spKills` and
   `mission.<name>.kills` to increment by exactly one.
3. Die. Expect `career.spDeaths` +1 — this is the case that fails if the
   local-player flags are ever moved back to kill time.
4. Verify no kill is credited for an ally that dies of something else within
   two seconds of the player last damaging it.
5. Play a network match. Expect `mpKills`/`mpDeaths` to move via `SimTeamDeath`
   and `spKills`/`spDeaths` not to move at all.
6. Watch for `[EVENTS] Dispatch ring full` during a large battle. If it appears,
   the 256-entry ring or the per-damage publish rate needs revisiting.
7. Set `[Career] StatsTracking = 0`, restart, confirm `[EVENTS] Unsubscribed` /
   no `[CAREER]` writes, and that `career_stats.cfg` stops changing.
8. Confirm a companion DLL polling the v2 queue still receives the lifecycle
   events, and now also receives `SimSessionStarted` / `SimKill`.
9. Click **Reset Career Stats** once and confirm the cell reads `Confirm?` and
   nothing is written; click a different row and confirm it disarms. Then click
   it twice: `career_stats.cfg` should hold only `meta.version`, a
   `career_stats.cfg.openshim.bak` should appear beside it, and the **Career
   Stats** toggle should be unchanged. Clicking it twice again should report
   "already empty" rather than overwriting the backup with an empty file.
