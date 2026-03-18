# Live Nickname Notes

Date: 2026-03-17

## Scope

Goal: determine whether Battlezone 98 Redux Steam can change the local
multiplayer nickname live, without restarting the game, and identify the safest
implementation path for EXU/OpenShim.

## Confirmed Steam-Build Facts

- The Steam executable accepts `/nickname=<name>` or `-nickname=<name>` style
  startup overrides. The parser string `nickname=` is present in the local
  Steam EXE.
- `BZLogger.txt` from the local Steam install shows the current authenticated
  BZRNet identity payload:
  - `name="GrizzlyOne95"`
  - `realname="GrizzlyOne95"`
- The same Steam EXE also contains BZRNet/auth strings including:
  - `OnAuthorization`
  - `Authorization`
  - `realname`
  - `galaxy::api::User()->SignIn(steamAppTicket, steamAppTicketLength, personaName);`
- EXU already exposes `exu.GetSteam64()`, which is sufficient to identify the
  local user from Lua, but it does not expose the editable nickname buffer.

## New Steam Runtime Findings

These were revalidated directly against the live Steam process on 2026-03-17,
not just the on-disk EXE.

- The Steam runtime `.text` does not match the on-disk `.text` byte-for-byte in
  useful RE areas. For nickname/auth work, trust live-process disassembly and
  xrefs over disk-only xrefs.
- The CLI nickname override writes into a fixed 128-byte buffer at
  `0x009453E0`.
  - Runtime parser anchor: `0x007D591C` (`push 0x8A0DE4` for `nickname=`),
    followed by the copy into `0x009453E0`.
  - In the inspected live session that buffer was empty, which matches launching
    without a nickname override.
- The outbound auth builder has a clean Steam runtime branch that distinguishes
  `name` from `realname`.
  - Runtime anchor: around `0x006C7D33`.
  - It always emits `realname` from a session/profile object field at `+0x304`.
  - It checks `0x009453E0[0]`; if non-zero, it emits `name=<nickname buffer>`.
  - If the nickname buffer is empty, it falls back to `name=realname`.
- That means `/nickname=` is a startup-only auth payload override path, not the
  live nickname source itself.
  - Current evidence says it affects the outbound `Authorization.name` field.
  - It does not directly change the `realname` field.
- The Steam64 global still lives at `0x0260B1D0` in the inspected build.
  - Runtime helper anchor: `0x0074D0D0` copies a 16-byte identity block into
    globals ending at `0x0260B1D0`.
- Live-memory scan for the current nickname found many raw string copies, but
  only three clear VC2013 inline `std::string` objects for `GrizzlyOne95`:
  - `0x07A0135C`
  - `0x1FC80010`
  - `0x264ABC9C`
- The strongest candidate for the current long-lived user object is still the
  first one:
  - `0x07A01338` object base candidate
  - `0x07A0135C` inline string object at `+0x24`
  - that still matches the advisory corpus note that `cUser::name` sits at
    offset `0x24`
- The live `OnAuthorization` parser also reuses the same `+0x304` field on its
  long-lived auth/session object, which reinforces that this field matters for
  the auth identity pipeline even though it is probably not the editable live
  nickname field itself.

## Practical Meaning Of The New Findings

- The old note was too coarse in one important way: Steam clearly treats
  `name` and `realname` as separate auth payload fields.
- A safe live rename probably does **not** mean "change only one shared name
  string everywhere."
- A more realistic Steam live path is now:
  1. update the live/displayed nickname field (`name`)
  2. propagate it through the Steam/BZRNet lobby metadata path
  3. leave `realname` alone unless we prove the game expects both to move
     together
- The startup nickname buffer at `0x009453E0` is still useful, but mainly as:
  - proof of how Steam expects `Authorization.name` to be overridden
  - a candidate stepping stone if we later find a safe re-auth / resend path

## Layout/RE Facts From The PDB-Class Corpus

The promoted Redux PDB/decompile corpus is still useful for structure identity,
even though it is not trustworthy for direct Steam VA reuse.

### Relevant class fields

- `cUser::name` at offset `0x24`
- `cLobby::users` at offset `0xbc`
- `NetPlayer::playerIdNew` at offset `0x154`
- `NetPlayer::playerName` at offset `0x15c`
- `NetPlayer::bIsMe` at offset `0x175`

### Relevant native functions/classes

- `CSteamLobby::GetCurrentUser()`
- `CSteamLobby::GetCurrentLobby()`
- `CSteamLobby::SetPlayerMetadata(std::string const&, std::string const&)`
- `CSteamLobby::UpdatePlayerRecord(bool force)`
- `NetPlayer::NotifyNameChanged(CSteamID, std::string const&)`
- `NetPlayer::netPlayerMap`

### Useful behavioral clue

The GOG decomp body for `CSteamLobby::GetCurrentUser()` resolves to a fixed
global `cUser` instance. That strongly suggests the live rename path does not
need to locate a complex lobby singleton just to update the local user's
primary profile name.

## Current Best Hypothesis For A Correct Live Rename

A proper live rename on Steam likely needs to update more than one place:

1. The local lobby/auth user record:
   - mutate `cUser::name`
   - push/update the lobby-side metadata through
     `CSteamLobby::SetPlayerMetadata(...)`
   - flush it with `CSteamLobby::UpdatePlayerRecord(true)` or equivalent
2. The in-match/live net-player record:
   - find the local `NetPlayer` by `bIsMe` or matching `playerIdNew` against
     `exu.GetSteam64()`
   - update `NetPlayer::playerName`
   - trigger native propagation via `NetPlayer::NotifyNameChanged(...)` if
     required

Using only one of those paths is likely incomplete:

- only changing `cUser::name` risks the lobby list or peer-visible metadata not
  updating
- only changing `NetPlayer::playerName` risks BZRNet/lobby auth state staying
  stale

## Why This Is Not Yet Shipped

The missing piece is Steam-specific address resolution for the live build.

- The local repo has a useful Redux PDB/decompile corpus, but it is not a
  direct Steam address map.
- A local Steam Ghidra project exists at
  `C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe_ghidra`,
  but automated `pyghidra` inventory export timed out in this environment
  before producing a usable symbol dump.
- Direct live-process probing has now recovered useful Steam runtime anchors for
  the auth builder, the startup nickname buffer, and the Steam64 write path.
- What is still missing is the safe callable path for one of these:
  - resend / rebuild of the `Authorization` payload after changing `name`
  - `CSteamLobby::SetPlayerMetadata(...)`
  - `CSteamLobby::UpdatePlayerRecord(...)`
  - `NetPlayer::NotifyNameChanged(...)`

Because of that, hardcoding a native live-rename patch right now would be a
blind Steam address guess, which is not acceptable.

## Recommended Next Step

Do this as a Steam signature-scan implementation in EXU, not as a hardcoded
address guess.

Suggested order:

1. Use the new runtime anchors to recover the callable Steam resend/update path:
   - the auth builder path around `0x006C7D33`
   - whatever caller triggers that builder on connect/re-auth
   - or, failing that, the original lobby metadata helpers:
     `CSteamLobby::SetPlayerMetadata` and
     `CSteamLobby::UpdatePlayerRecord`
2. Keep signature-scan resolution as the shipping standard rather than fixed
   Steam addresses.
3. Add EXU exports:
   - `exu.GetMultiplayerNickname()`
   - `exu.SetMultiplayerNickname(name)`
4. Keep the Lua/shell UI work separate from the native setter so the UI can
   land after the native path is trustworthy.

## New Helper Script

To recheck these anchors quickly against a running Steam build, use:

`python reverse_engineering/probe_nickname_runtime.py --pid <PID> --nickname <CurrentName> --dump-candidate-context`

That script currently verifies:

- runtime xrefs to `realname`, `name`, `nickname=`, the nickname buffer, and
  the Steam64 global
- the current contents of `0x009453E0`
- inline `std::string` candidates for the live nickname text

## Timed Watcher Workflow

There is now a bounded timeline recorder at:

`python reverse_engineering/watch_nickname_flow.py --duration 120`

What it captures in one JSONL timeline:

- Frida hits on the live Steam nickname/auth anchors:
  - `0x006C7D33`
  - `0x006BF5E7`
  - `0x0074D0D0`
  - `0x007D591C`
- Lounge-side websocket traffic using the same public BZRNet message model that
  `Battlezone_LobbyMonitor` uses:
  - `Authorization`
  - `DoEnterLounge`
  - `GetLobbyList`
  - inbound `OnAuthorization`
  - inbound `OnLobbyListChanged`
  - plus any later `OnUserDataChanged`, `OnLobbyDataChanged`,
    `OnLobbyMemberListChanged`, `OnLobbyChanged`, etc. that occur during the
    trace window

Useful modes:

- Full combined trace:
  - `python reverse_engineering/watch_nickname_flow.py --duration 120`
- Frida-only:
  - `python reverse_engineering/watch_nickname_flow.py --duration 120 --disable-ws`
- Lounge/websocket only:
  - `python reverse_engineering/watch_nickname_flow.py --duration 120 --disable-frida`

The short validation run on 2026-03-17 succeeded against the live Steam process
and the public lobby endpoint `ws://battlezone98mp.webdev.rebellion.co.uk:1337`.
The generated capture showed:

- the Steam auth-builder hooks firing in the same session
- successful sidecar `OnAuthorization`
- `OnLobbyListChanged` exposing the live Steam user as
  `id = S76561199524026756`
  with `name = "BZ98er"`
  and `authType = "steam"`

That makes this watcher a good fit for user-driven timed walkthroughs of:

- main menu -> multiplayer -> lounge
- create/join/leave lobby
- launch to game and return
- any attempted nickname mutation once a native setter exists

## Full Walkthrough Findings From 2026-03-17

The full user-driven walkthrough capture at
`reverse_engineering/snapshots/nickname_flow_20260317_210031.jsonl`
showed:

- Frida-side:
  - the startup nickname/auth builder anchors still only fired once
  - the `OnAuthorization` parser anchor at `0x006BF5E7` fired many times during
    lobby traffic, so it is broader/noisier than a pure auth-only hook
- Sidecar websocket view:
  - many `OnLobbyChanged` messages
  - no `OnUserDataChanged` / `OnLobbyDataChanged` in the sidecar capture
- Native verbose logger view from `BZLogger.txt`:
  - the game itself absolutely did receive `OnLobbyDataChanged` and
    `OnUserDataChanged` repeatedly during the same walkthrough
  - the game also logged its own outbound `SetLobbyData` / `SetPlayerData`
    messages verbatim

That means `BZLogger.txt` is currently the best source for the real in-process
network story. The sidecar watcher is still useful for an external timeline, but
it is not a complete substitute for the game's own websocket log.

### Concrete traffic confirmed by `BZLogger.txt`

The native log now gives a reliable state-machine outline for Steam lobby/game
transitions:

- Initial auth still sends:
  - `Authorization { name: "GrizzlyOne95", realname: "GrizzlyOne95", ... }`
- Chat-lobby creation sends:
  - `CreateLobby`
  - `SetLobbyData("name", "~chat~pub~~...")`
  - `SetLobbyData("gameType", "1")`
  - `SetLobbyData("gameSettings", "*")`
  - `SetLobbyData("GameVersion", "2.2.301 + OpenShim")`
  - `SetLobbyData("userCount", "1")`
  - `SetLobbyData("userPack", "GrizzlyOne95                    ")`
  - `SetPlayerData("friendID", "S76561198241259700")`
- Game-lobby creation sends:
  - `SetLobbyData("name", "~game~pub~~test")`
  - `SetLobbyData("gameType", "1")`
  - `SetLobbyData("nextmid", "2")`
  - `SetPlayerData("miniid", "1")`
  - `SetPlayerData("team", "1")`
  - `SetPlayerData("knownPlayers", "S76561198241259700,1,1,")`
  - `SetPlayerData("friendID", "S76561198241259700")`
  - `SetPlayerData("vehicle", "bvtump")`
  - `SetLobbyData("gameSettings", "...")`
  - `SetLobbyData("GameVersion", "2.2.301 + OpenShim")`
- Ready/launch transition sends:
  - `SetPlayerData("ready", "...")`
  - `SetLobbyData("launched", "1")`
  - `SetPlayerData("launched", "1")`

Most importantly for nickname work:

- this walkthrough never logged any outbound
  - `SetPlayerData("name", ...)`
  - `SetPlayerData("playerName", ...)`
- the visible Steam player name in all logged lobby/game updates remained
  `GrizzlyOne95`

So the normal create/join/launch flow does update a lot of player metadata, but
it does **not** naturally resend nickname fields after the initial
`Authorization`.

That sharply narrows the live-rename problem:

1. either we need to recover the explicit native/user-data sender for
   `name` / `playerName`
2. or we need to re-enter the auth/name resend path after mutating the live name
   source
3. and in either case we still need to check whether local `NetPlayer` state
   must move separately

### Practical implication for future probes

For the next agent pass, treat these as the highest-value logging sources in
order:

1. `BZLogger.txt` for the game's actual websocket sends/receives
2. `watch_nickname_flow.py` for correlating native hook timing against that log
3. external sidecars like `Battlezone_LobbyMonitor` for protocol shape reference
   only

## Battlezone_LobbyMonitor Reuse Notes

`C:\Users\iestu\Documents\GIT\Battlezone_LobbyMonitor` is useful as a protocol
reference for the public BZRNet side.

Important confirmed message shapes from that repo:

- websocket endpoint default:
  - `battlezone98mp.webdev.rebellion.co.uk:1337`
- initial auth:
  - `Authorization { authtype, key, id, apiVer, clientVersion, name, playerName }`
- explicit user metadata writes:
  - `SetPlayerData { key: "name", value: ... }`
  - `SetPlayerData { key: "playerName", value: ... }`
- lobby metadata writes:
  - `SetLobbyData { key: "name", value: ... }`

This does **not** directly solve the native Steam rename path, but it does give
an external truth source for whether the server is observing any user/lobby data
changes after a local experiment.

## Agent Handoff Checklist

If another agent picks this up later, the highest-value next probes are:

1. Find the caller that uses the auth builder around `0x006C7D33` and check
   whether it can be safely re-entered after startup.
2. Recover a Steam-safe signature for the object whose field at `+0x304` feeds
   both the outbound auth builder and the `OnAuthorization` parser path.
3. Resolve the live `name` write path separately from `realname`.
   - Current evidence says `name` is the field we want to change for nickname
     UI / lobby display.
   - Do not assume `realname` should move with it.
4. Recover `CSteamLobby::SetPlayerMetadata(...)` and
   `CSteamLobby::UpdatePlayerRecord(...)` from the Steam build and compare them
   against whatever re-auth path is found first.
5. Recover the local `NetPlayer` update path:
   - locate `NetPlayer::playerIdNew`, `playerName`, and `bIsMe`
   - test whether `NotifyNameChanged(...)` is still required once lobby/auth
     metadata is updated
6. Keep all shipping work on signature scans or robust runtime resolution.
   - The live Steam `.text` already proved that disk-only xrefs are not enough.
7. Use `watch_nickname_flow.py` during any timed walkthrough so the Steam-side
   hook hits and the lounge-side BZRNet events end up in one capture.
8. Use `Battlezone_LobbyMonitor` as the public protocol reference for message
   names and payload shapes rather than re-deriving them from scratch.
9. During future walkthroughs, always preserve `BZLogger.txt` as the primary
   record of the in-process websocket traffic.
10. Focus the next native hunt on the sender for
    `SetPlayerData("name", ...)` / `SetPlayerData("playerName", ...)`, because
    the ordinary Steam lobby/game flow does not emit those fields after auth.

## Concrete Anchors To Reuse

- Startup nickname parser: `0x007D591C`
- Startup nickname buffer: `0x009453E0`
- Auth builder branch that distinguishes `name` vs `realname`: around
  `0x006C7D33`
- Steam64 global: `0x0260B1D0`
- Steam64 block writer: `0x0074D0D0`
- Strong `cUser::name` candidate:
  - object base candidate `0x07A01338`
  - inline string object `0x07A0135C`
- Other inline `std::string` nickname copies seen in the live session:
  - `0x1FC80010`
  - `0x264ABC9C`

## Practical Lua-Side Fallbacks Already Available

- `exu.GetSteam64()` can identify the local player
- Campaign Reimagined already falls back to parsing `BZLogger.txt` when it
  needs the current Steam ID/name for greeting logic

Those are enough for display-only aliasing, but not enough for a true live
native multiplayer rename.
