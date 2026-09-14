# Persistent Player Mute

This document tracks the implementation of a persistent, client-side player mute facility for OpenShim.

## Intended behavior

- Mute is a local presentation preference, not a network or host-authority action.
- Muted players remain connected and visible to matchmaking/gameplay systems.
- Chat and whisper text from muted identities is suppressed before presentation.
- Mutes should persist across sessions and use stable player/network identity where available; nicknames are display metadata only.
- No automatic replies, disconnects, kicks, bans, or other retaliatory behavior are triggered by mute.

## UX targets

1. Reuse the existing multiplayer player-selection plumbing used by the Ban User control to add a Mute/Unmute action.
2. Add command fallback support for `/mute` and `/unmute` where sender/player resolution is reliable.
3. If the chat feed exposes a stable sender object or identity at render time, add a click/right-click mute action as a follow-up without changing chat packet semantics.

## Qualification requirements

- Normal lobby chat from unmuted users remains unchanged.
- Whispers from an explicitly muted identity do not appear in the local chat feed.
- Muting does not disconnect, reject, or alter sender/network state.
- Rename/reconnect does not bypass a mute when a stable identity is available.
- Unmute restores normal chat immediately.
- Persistence survives game restart.

## Configuration

Persistence is optional; the mute itself is not. Redux's own per-process mute
is what silences a player, and it keeps working regardless of this setting —
what the setting decides is whether that mute outlives the process.

    openshim.ini   [Network] PersistentPlayerMute = 1
    environment    OPENSHIM_DISABLE_PERSISTENT_PLAYER_MUTE=1
    in-game        OpenShim Settings -> Persistent Mutes

| Value | Behaviour |
|---|---|
| `1` (default, and what an absent key does) | A mute is written to `mutes.cfg` beside the shim, keyed by the same `G<uid>`/`S<uid>` stable identity bans use, and reapplied whenever that player is seen again — through reconnects, lobby changes and renames. |
| `0` | Session only, i.e. stock. Nothing is written and `mutes.cfg` is never read, so a mute ends with the process. |

Notes:

- `/unmute` clears the stored entry in **both** modes. Turning persistence off
  stops the list growing; it never means "unmute means less than it says".
- Turning it off does not delete an existing `mutes.cfg`. The file is left
  alone and is honoured again the moment the setting goes back on.
- The setting is re-read at each mute and each lobby join rather than latched
  at startup, so no restart is required either way.
- It changes nothing on the wire: no host, and no muted player, is told.
