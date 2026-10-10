# Individual multiplayer Lua replication probes

This is a Lua 5.1 module to integrate into a **disposable multiplayer test map**.
It is not a multiplayer mission package and does not replace the mission's
callbacks. Do not integrate it into a live campaign for qualification.

Read `docs/MP_LUA_REPLICATION_QUALIFICATION.md` for exact-build evidence and
remaining unknowns. No two-client result has been collected yet.

## Wire it into the test mission

Copy `mprep.lua` beside the test mission script on both peers. Reserve its single
message type byte (`~` by default), choose a clear test area, and leave room for
one more objective within the engine's ten-objective limit. Compose these hooks
with the mission's existing callbacks:

```lua
local Probe = require("mprep").new({
    -- Optional: pass an already loaded, supported EXU module for sync/async tests.
    exu = exu,
    messageType = "~",
    -- Leave false until the isolated ownership-claim experiment.
    allowOwnershipClaim = false,
})

-- In existing CreatePlayer/AddPlayer callbacks:
-- Probe.AllowPeer(id)
-- In existing DeletePlayer callback:
-- Probe.DeletePlayer(id)
-- In existing Update callback:
-- Probe.Update()
-- At the beginning of existing Receive(from, kind, ...):
-- if Probe.Receive(from, kind, ...) then return true end
```

For an already connected peer whose callback was missed, explicitly register its
verified callback/net ID with `Probe.AllowPeer(id)` on the receiving machine.
Team numbers and network IDs are different namespaces. The probe does not
discover the host ID or assume that a callback replay occurs. Keep these
invocations in the disposable mission's own test controls or scripted stages.

## Test one operation at a time

1. Record both exe hashes, OpenShim/EXU versions, map, player IDs/teams, host,
   object ODF/class, elapsed time, and log paths in `results_template.csv`.
2. On the selected creator, create a fresh disposable subject:
   `h = Probe.Spawn("stock", "avtank", 1, "probe_spawn")`. Use a verified path
   that actually exists on the test map. Repeat with `sync` and `async` only
   when EXU capability is present. Run creator-host and creator-client cases.
3. Log and watch the local subject with `Probe.Watch("case01", h)`; announce it
   to the other peer with `Probe.Announce(otherNetId, "case01", h)`. On receipt,
   the other peer's remapped local handle is `Probe.watches.case01.h`.
4. Confirm both peers have a valid subject before mutations. A received nil is
   a real pending-reference result. Reannounce the same subject at recorded
   times after spawn; do not build a replacement on the receiver. Record
   creator-only/local-only subjects as such if they never resolve.
5. Announce/watch the baseline on both peers, then invoke exactly one local
   mutation on the intended executor, e.g.
   `Probe.Run("SetName", h, "case01_renamed")`. The observer watches for ten
   seconds. Record immediate and subsequent values plus UI/AI observations.
6. With a fresh subject per condition, compare owner-only, remote-only, and
   explicit local application on both peers. Do not count applying twice as
   evidence of automatic stock replication. For remove, establish peer watches
   before removal; invalid/stale handles are sampled without mutation afterward.
7. Test entering/leaving the craft, owner departure, late join and reconnect
   separately. Fresh mission sessions are preferable for ownership tests.

Supported local operations:

```lua
Probe.Run("RemoveObject", h)
Probe.Run("SetName", h, "name")
Probe.Run("SetObjectiveName", h, "objective_name")
Probe.Run("SetObjectiveOn", h)
Probe.Run("SetObjectiveOff", h)
Probe.Run("GiveWeapon", h, "gspstab", 0) -- verify compatible ODF/hardpoint
Probe.Run("GiveWeapon", h, nil, 0)       -- explicit removal of one slot
Probe.Run("SetTeamNum", h, 2)
Probe.Run("SetPosition", h, GetPosition("probe_destination"))
Probe.Run("SetVelocity", h, SetVector(0, 0, 1))
```

Names, markers, objective text and firing/ammo need visual/gameplay observations
on each peer as well as logs. `GetWeaponClass` reads all five slots, but a matching
class is not proof of matching ammo, active weapon mask or actual remote firing.
Samples include validity, locality, team, name, label, position and current AI
command where getters are available.

Objective text is an independent local experiment:

```lua
Probe.Objective("add", "Probe objective on this peer")
Probe.Objective("update", "Updated on this peer")
Probe.Objective("remove")
```

For an ownership claim, construct a separate probe with
`allowOwnershipClaim = true`, watch one disposable AI subject created by the
other peer, then explicitly call `Probe.Run("SetLocal", remappedHandle)` on the
single designated claimant. Do not claim a player object or run this call on
both peers. Record command execution/AI behavior before and after. The module
has no automated transfer logic and no claim of a safe transfer contract.

## Transport, state and event experiments

```lua
Probe.Payload(otherNetId, "state", "phase", 3, true, nil)
Probe.Payload(0, "event", "wave_started", 1)
```

Receive logs sender ID, tag, monotonically increasing sender sequence, scalar
types and values. It does not apply received values to mission variables or run
event handlers. First confirm that an ordinary Lua variable assigned only on
the host remains unchanged on the other VM, then compare explicit payload
receipt. Compare unicast with broadcast and record whether the sender receives
its own broadcast. Repeat controlled events to measure duplicates and ordering;
do not interpret the send boolean as an acknowledgement.

Valid scalar strings are capped at 127 bytes and estimated packets at 200 bytes.
Use lengths 0, 30, 31, 126, 127 only for live boundary tests. Do not send 128-byte
strings, oversized tables, recursive tables or invalid weapon slots: the exact
binary already exposes unsafe decoding/indexing for those inputs. Longer text
will need a separately designed and qualified chunked protocol.

No automatically scheduled workload, game launch, or existing map edit is
included. Any future launch harness must dot-source `BZRHarness.ps1`, use
`BZR_FORCE_WINDOWED=1`, and stop its own saved PID through `Stop-BZRGame -Id`.

## Offline validation

Run `mock_test.lua` with Lua 5.1 from this directory. The 51 assertions verify
probe controls and routing only; they do not substitute for two game clients.
On the development machine the tests were run with Lupa's `lupa.lua51` runtime
installed only under the ignored/local game log evidence directory.
