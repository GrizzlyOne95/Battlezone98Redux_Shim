# Ghidra GOG EXE + PDB RE Notes

This note summarizes the current reverse engineering status for:

- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`

The reproducible workflow lives in:

- `scripts/ghidra_extract_gog_exe_summary.py`

Generated output from the current GOG sample is stored at:

- `reverse_engineering/workshop/3362534335/ghidra_gog_exe_summary.md`

## PDB match status

The supplied PDB is from the same codebase family, but it does not match the GOG executable's
embedded RSDS record.

- EXE expects:
  - GUID `04ffcabe-6837-4ab9-9d42-e5b9df4c7cba`
  - age `1`
  - path `D:\code\BattleZoneTest\build\bin\Release\battlezone\battlezone98redux.pdb`
- Provided PDB contains:
  - GUID `37614db0-6577-4506-8ad6-0e6a72f6fd2f`
  - age `1`

Implication:

- Ghidra will not auto-apply that PDB to the EXE
- the PDB should be treated as a naming oracle, not as an address-accurate symbol file

## What the mismatched PDB still gives us

The PDB still exposes high-value object names and symbol names from the `BattleZoneTest`
release tree, including:

- map UI and filter paths
  - `UI_Multiplayer_Create.obj`
  - `UI_Multiplayer_MapSelect.obj`
  - `filters.obj`
  - `cUI_Multiplayer_MapSelect::FilterMaps`
  - `cMapManager::BuildFilteredMapList`
  - `cUI_Multiplayer_Create::FilterSelected`
  - `cUI_Multiplayer_Create::MapFilterToggle`

- lobby and chat systems
  - `lobby.obj`
  - `chat.obj`
  - `CSteamLobby::OnLobbyChatUpdate`
  - `CSteamLobby::OnChatMessage`
  - `CSteamLobby::KickUser`
  - `CSteamLobby::OnLobbyKicked`
  - `NetPlayer::NotifyLeftLobby`

- user bar UI
  - `UI_UserBar.obj`
  - `cUI_UserBar::cUI_UserBar`
  - `cUI_UserBar::msgCB`
  - `cUI_UserBar::muteCB`
  - `gClick_UserBar_Msg`
  - `gClick_UserBar_Mute`
  - `gClick_UserBar_Kick`

- slash-command plumbing
  - `Net_MutePlayer`
  - `Net_UnmutePlayer`
  - `Net_KickPlayer`
  - `Net_LockGame`
  - `Net_UnlockGame`

That is enough to label subsystems confidently even though the addresses are not directly
portable from the PDB to the shipped EXE.

## What Ghidra confirmed in the GOG EXE

Headless Ghidra analysis of the GOG executable lines up cleanly with the PDB naming evidence:

- `0x00796880`
  - sets `cUI_Multiplayer_Create::vftable`
  - acts as the main create-screen setup root containing several patch sites used by `_bzcp.dll`

- `0x00752A50`
  - compares the active filter string against `All Maps`, `Strategy`, `Death Match`, and
    player-count filters
  - this is the strongest feature-level match for the `FilterMaps` / `BuildFilteredMapList`
    neighborhood

- `0x007A3160`
  - rebuilds filter entries including `All Maps`, `Strategy`, `Death Match`, and player-count
    labels
  - this is the filter-menu rebuild path touched by the hop-fix scroll logic

- `0x007997A0`, `0x00799880`, `0x007CAFA0`, `0x007CB500`, `0x007CB540`
  - together implement the visible map-list state machine:
  - toggle visible controls
  - reselect the target entry
  - adjust the scroll offset up or down

- `0x007D0770`
  - constructs buttons labeled `Whisper User` and `Mute User`
  - matches the `UI_UserBar.obj` and `cUI_UserBar::*` symbols from the PDB

- `0x006247A0`
  - implements `/help`, `/mute`, `/unmute`, `/kick`, `/lock`, and `/unlock`
  - aligns with the `Net_*` symbol set exposed by the PDB

- `0x0073EEB0`
  - logs `CNetGameLobby::OnLobbyChatUpdate called ...`
  - strongly supports the nearby PDB symbol `CSteamLobby::OnLobbyChatUpdate`

## Practical use

For this project, the current PDB is useful for:

- naming subsystems
- interpreting decompiled functions
- narrowing which GOG EXE functions correspond to workshop patch sites

It is not reliable for:

- blind symbol import
- exact RVA recovery
- automatic renaming without manual validation

Use the GOG EXE for code recovery, and use the mismatched PDB only as supporting semantic
evidence.
