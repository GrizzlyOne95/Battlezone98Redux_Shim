# Live Nickname Notes

Date: 2026-03-17

## Scope

Goal: determine whether Battlezone 98 Redux Steam can change the local
multiplayer nickname live, without restarting the game, and identify the safest
implementation path for EXU/OpenShim.

## Confirmed Steam-Build Facts

- The Steam executable accepts `/nickname=<name>` or `-nickname=<name>` style
  startup overrides. The parser string `nickname=` is present in the local
  Steam EXE at `C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe`.
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
- Static string/xref work on the Steam EXE confirmed the relevant auth strings
  and parser strings, but did not yet recover clean Steam call addresses for
  the lobby/name helpers above.

Because of that, hardcoding a native live-rename patch right now would be a
blind Steam address guess, which is not acceptable.

## Recommended Next Step

Do this as a Steam signature-scan implementation in EXU, not as a hardcoded
address guess.

Suggested order:

1. Recover Steam signatures or addresses for:
   - `CSteamLobby::GetCurrentUser`
   - `CSteamLobby::GetCurrentLobby`
   - `CSteamLobby::SetPlayerMetadata`
   - `CSteamLobby::UpdatePlayerRecord`
   - `NetPlayer::NotifyNameChanged`
   - `NetPlayer::netPlayerMap`
2. Add EXU exports:
   - `exu.GetMultiplayerNickname()`
   - `exu.SetMultiplayerNickname(name)`
3. Keep the Lua/shell UI work separate from the native setter so the UI can
   land after the native path is trustworthy.

## Practical Lua-Side Fallbacks Already Available

- `exu.GetSteam64()` can identify the local player
- Campaign Reimagined already falls back to parsing `BZLogger.txt` when it
  needs the current Steam ID/name for greeting logic

Those are enough for display-only aliasing, but not enough for a true live
native multiplayer rename.
