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
