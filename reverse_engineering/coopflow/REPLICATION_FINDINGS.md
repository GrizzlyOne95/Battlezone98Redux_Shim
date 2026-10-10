# Stock Redux Lua replication: measured cases

Measured 2026-10-07 on GOG Redux 2.2.301 with two real clients on one PC
(BZRCoopSession instances, private loopback server.py, relay transport),
mission misn03 from Campaign Reimagined `858bddc`. Host = player 1, team 1
(campaign authority); guest = player 2, team 2.

Produced by `coopflow/scenarios/replication-cases.ps1` (run
`cr-misn03-repl-4`; raw evidence in `C:\BZRCoop\runs\cr-misn03-repl-4\replication-findings.jsonl`).
Each case uses its own fresh object and is only classified while that object
is alive on both peers. Observation window 6 s unless noted.

Input for the higher-level replication API: these are the per-case facts it
has to be built on.

## Results

| Case | Who acts | Operation | Result | What was observed |
|---|---|---|---|---|
| A1 | host | `BuildObject` craft (team 5 AI) | **replicated** | appears on the guest within 0.2 s |
| A2 | host | `BuildObject` building (team 1) | **replicated** | appears on the guest within 0.2 s |
| A3 | guest | `BuildObject` craft (own team 2) | **local-only** | exists only on the guest, and `IsLocal()` is false even there; never appears on the host |
| A4 | guest | `BuildObject` building (own team) | **local-only** | same as A3 |
| B1 | host | `RemoveObject` host-owned building | **replicated** | gone on the guest within 0.2 s |
| B2 | guest | `RemoveObject` host-owned building | **diverged** | removed on the guest only; the host keeps it and never sends it back, so the guest stays wrong |
| C1 | host | `Send(handle)` of a host-owned object | **replicated** | the guest receives the same object (`h == findNear(...)`) |
| C2 | guest | `Send(me())` | **replicated** | equals the host's tracked handle for that player |
| D1 | host | `SetObjectiveName` / `SetName` | **local-only** | the guest keeps the ODF name ("S-Power") |
| F1 | host | `Damage` host-owned building | **replicated** | the guest sees health drop (1.0 -> 0.75) within 0.2 s |
| F2 | guest | `Damage` host-owned building | **none** | no effect even on the guest's own copy; the host is unchanged |
| F3 | host | `SetMaxHealth`/`SetCurHealth` x3 | **local-only** | the host has max 4500, the guest keeps 1500; health fraction still syncs |
| G1 | host | `SetPosition` host-owned building | **local-only** | the guest still sees the building at the old spot |
| G2 | guest | `SetPosition` host-owned building | **reverted** | moves on the guest, snapped back within 2 s; the host never moves |
| H1 | host | `SetTeamNum` host-owned building | **local-only** | the host has team 5, the guest still team 1 |
| I1 | guest | `GiveWeapon` on its own craft | **local-only** | the host's view of the guest craft keeps the old weapon |
| I2 | host | `GiveWeapon` on the guest's craft | **local-only** | only the host's copy changes; the guest's own craft is untouched |
| J1 | host | `Send(0, ...)` numbers, booleans, 30/31/127-byte strings | **replicated** | all values and lengths intact |
| J2 | guest | `Send(0, ...)` | **replicated** | reaches the host |
| J3 | host | `Send(0, ...)` 128-byte string | **crash** | the guest crashes within seconds (access violation in `luaS_newlstr`) |

G1 covers a building only; craft positions have not been measured yet.

## Send() string limit: 127 bytes (receiver crash above that)

Ghidra, `battlezone98redux.exe` 2.2.301:

- `Send` (`0x5060f0`) packs arguments into a 1150-byte stack buffer and logs
  `Lua Send packet full at arg %d` when an argument does not fit.
- The string encoder (`0x5058d0`) stores lengths 0-30 in the low 5 bits of the
  type byte. Longer strings write `0x1f` there plus one length byte `(char)len`,
  with no check that `len < 256`, then copy all `len` bytes.
- The receiver's decoder (`0x5059b0`, called from `Receive` dispatch `0x50b310`)
  reads that length byte as a **signed** `char`.

Consequences:

- 128-255 bytes: the length sign-extends to ~4 GB on the receiver. `lua_pushlstring`
  then reads past the packet and the receiver crashes (`0x8309f4`). Seen live in
  runs `cr-misn03-repl-2` (200 bytes) and `cr-misn03-repl-4` (128 bytes).
- 256 bytes or more: the length byte wraps (`len % 256`) while all bytes are
  copied, so every later argument is misparsed (and it crashes too when
  `len % 256 >= 128`).
- The sender is never affected, so a host can crash every guest without
  seeing an error itself.

Shipped CR co-op only sends short strings (op names, `.otf`/`.wav` file names,
objective labels), so it is not exposed today. A replication API that carries
text (objective text, names, serialized state) must cap each string argument
at 127 bytes, or split longer text across arguments or messages.

## Smaller observations from the play tests

- `RemoveObject` relayed in CR's presentation stream arrives on the guest as
  `RemoveObject(nil)`. The host queues the event and then deletes the object
  immediately, so the handle is dead before it is sent. Harmless (B1: the
  owner's deletion replicates by itself) but redundant.
- Health fractions sync while custom maximums do not (F3), so a script that
  raises max health on the host shows different absolute values on each peer.
  CR's `SetMaxHealth` presentation op already works around this.
- `SetLabel` is local-only as well: labels the host assigns (e.g.
  `misn02b_bscav`) show as the ODF default (`avscav2_scavenger`) on the guest.
  Compare objects across peers by ODF/position, never by label.
- `CameraFinish()` with no camera pushed logs `Fsm error: Camera Stack
  0verfow`, opens an in-game alert, and **aborts the calling Lua chunk without
  a Lua error**: statements after it never run. In misn02b this skipped
  `M.coopResult = true`, so the result was queued twice. The guest applied it
  twice (two alerts) and then hung in BZRNet shutdown on exit. Guard every
  `CameraFinish` with the peer's own camera state. Fixed in CR
  `agent/misn02b-coop-start`.
- A skip releases only the skipping player's camera, whether the host or a
  guest skips (misn03 and misn02b, both directions). The host's camera
  snapshots keep the other player's film running.
- An unattended misn03 is lost at about t=77 s: the two first-wave fighters
  destroy the Command Tower, and the loss reaches both clients identically
  (`FailMission(87.4, misn03f1.des)`).

## Implications for a host-authoritative API

- **Spawning and removal:** do both on the host only (A1/A2/B1 replicate; A3/A4/B2 do not).
  A guest that needs an object must ask the host by message.
- **Ownership-sensitive ops:** `Damage`, `SetPosition` and `RemoveObject` on an object
  another peer owns either do nothing (F2), are reverted (G2) or leave that
  peer wrong (B2). Route them to the owner.
- **Engine-unsynced state:** names, objective names, max health, team and
  weapons do not replicate even from the owner (D1, F3, H1, I1, I2). These need
  an explicit host event applied on every peer, as CR does for objectives.
- **Handles:** they survive `Send` both ways for live objects (C1/C2), but not
  once the sender has removed the object.
- **Strings:** at most 127 bytes per `Send` argument.
