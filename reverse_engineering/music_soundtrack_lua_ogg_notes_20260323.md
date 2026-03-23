# Lua Soundtrack / OGG Notes

Investigated on 2026-03-23 against:

- current Redux GOG install under `%USERPROFILE%\Documents\Battlezone 98 Redux`
- current EXU repo
- current Campaign Reimagined addon scripts
- current OpenShim repo
- working local `ghidra` MCP against `battlezone98redux.exe-330a2b`

## Question

Feature 17 asks for either:

- letting Lua play formats other than `.wav`, especially `.ogg`, or
- exposing the native soundtrack system to Lua so missions can control music directly instead of faking it with `StartSound`.

## Confirmed Static Findings

### Current Lua Mission Audio Is WAV-Only

Campaign Reimagined's shipped stock-Lua docs still describe the relevant mission-audio APIs as WAV-only:

- [`scriptutils.lua`](/c:/Users/istuart/Documents/Battlezone%2098%20Redux/addon/campaignReimagined/_Source/Scripts/scriptutils.lua#L274)
  - `AudioMessage(filename)` says the file must be an uncompressed RIFF WAVE.
- [`scriptutils.lua`](/c:/Users/istuart/Documents/Battlezone%2098%20Redux/addon/campaignReimagined/_Source/Scripts/scriptutils.lua#L300)
  - `StartSound(filename, ...)` says the file must be an uncompressed RIFF WAVE.

This matches current modder experience: mission music hacks still go through WAV conversion plus `StartSound` / `StopAudioMessage`.

### EXU Does Not Yet Expose Music Playback Control

The only music-facing EXU export found in the current tree is music-slider inspection:

- [`luaexport.cpp`](/c:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/luaexport.cpp#L792)
  - exports `GetMusicVolume`
- [`SoundOptions.h`](/c:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/SoundOptions.h#L30)
  - reads a scanner-backed `musicVolume`
- [`SoundOptions.cpp`](/c:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/SoundOptions.cpp#L23)
  - `GetMusicVolume` just returns the current display value

There is no current EXU API for:

- set current soundtrack track
- stop or pause native music
- resume native music
- override track filename or playlist

### Native OGG Music Support Definitely Exists In Redux

The executable and install both show a dedicated OGG music path:

- shipped music assets:
  - `music\\02.ogg` through `music\\27.ogg`
- shipped decoder DLLs:
  - `libogg.dll`
  - `libvorbis.dll`
  - `libvorbisfile.dll`
- EXE strings in `battlezone98redux.exe`:
  - `%02d.ogg`
  - `Initializing music handler`
  - `Stopping Music Playback Index %d During Music Shutdown`
  - `Starting Music Playback Index %d`
  - `OggManager::Setup - ov_open_callbacks failed. Requested audio will not play :(`
  - `Couldn't create a streaming ogg!`
  - `OggManager::Play index %d ...`
  - `CStreamingOggSound`
- imported vorbis functions seen through Ghidra:
  - `ov_open_callbacks`
  - `ov_clear`
  - `ov_raw_seek`
  - `ov_info`
  - `ov_read`

The game logger also confirms that a separate native music system is active:

- [`BZLogger.txt`](/c:/Users/istuart/Documents/Battlezone%2098%20Redux/BZLogger.txt)
  - `Initializing music handler`
  - `Starting Music Playback Index 0`

### `.TRN` Still Only Selects A Numeric Music Track

The mission-side data still looks like a numeric selector, not a filename or playlist declaration:

- stock and addon `.trn` files use `MusicTrack=<number>`

This strongly suggests the stock mission format chooses a track index and leaves filename resolution to native code, likely through the `%02d.ogg` path.

## Current Technical Read

The clean architecture is:

1. `AudioMessage` / `StartSound` are one path.
   They are Lua-facing, mission-audio-oriented, and documented as WAV-only.
2. Native music / soundtrack playback is a different path.
   It is OGG-backed, track-index-based, and uses its own manager plus streaming sound objects.

That means the lower-risk feature is not "teach `StartSound` to accept `.ogg` first".
It is "expose the existing soundtrack system to Lua first".

## Best First API Surface

The best first EXU or OpenShim-facing API set looks like:

- `exu.SetMusicTrack(index)`
- `exu.StopMusic()`
- `exu.PauseMusic()`
- `exu.ResumeMusic()`
- `exu.GetMusicTrack()`

Useful follow-up APIs:

- `exu.SetMusicEnabled(enabled)`
- `exu.SetMusicTrackOverride(index, filename)`
- `exu.ClearMusicTrackOverride(index)`
- `exu.SetMusicPlaylist({ ... })`

This keeps modders on the stock music mixer, stock music volume path, and stock streaming behavior instead of forcing OGG through the more effect-oriented sound API.

## Best Implementation Direction

### Preferred

Expose the stock soundtrack manager to Lua and let Lua choose or stop tracks by index.

Why this is best:

- matches the stock `.trn` model
- already uses OGG streaming
- already respects the music volume slider
- avoids reimplementing long-stream decode/playback in the mission sound path

### Second Step

Allow filename or playlist override behind the same manager.

Example:

- keep `SetMusicTrack(4)`
- but make track `4` resolve to `addon\\mycampaign\\music\\boss_theme.ogg`

This would preserve track-based mission logic while freeing mods from the hardcoded stock `music\\%02d.ogg` naming scheme.

### Higher-Risk Alternative

Patch `StartSound` / `AudioMessage` to accept `.ogg`.

This is riskier because that API family is not just "play background music":

- it has attachment/3D semantics
- it has effect priority semantics
- it has loop/rate/volume expectations that may not match the streaming music code
- it may bypass the stock music-volume channel entirely

## What I Could Not Finish On This Machine

I confirmed the subsystem exists, but I did not finish mapping exact caller functions and hook sites.

Reasons:

- Ghidra MCP is now working again, but this binary's music-string xrefs were sparse or not surfaced cleanly through the current automated path.
- Raw string and import evidence is strong, but function-boundary recovery for the music manager still needs a cleaner pass.
- A runtime breakpoint pass would have been the fastest way to finish mapping `OggManager` entry points, but this machine is not available for live launch/debug validation.

## Resume Plan On Another Machine

The next pass should be runtime-first, then static tidy-up.

### Runtime

Break or trace:

- `libvorbisfile!ov_open_callbacks`
- `libvorbisfile!ov_info`
- `libvorbisfile!ov_read`
- `DSOUND!DirectSoundCreate`

Goal:

- capture the caller return addresses inside `battlezone98redux.exe`
- map those callers to the music manager setup/play path
- identify the function that takes the track index and formats `%02d.ogg`

### Static Follow-Up

Once the runtime caller addresses are known:

- decompile the containing functions in Ghidra
- identify:
  - manager singleton or global
  - play-by-index entry point
  - stop/pause/resume entry points
  - any filename-resolution helper
  - any `MusicTrack` mission-load handoff

### Patch Shape To Look For

Ideal hook targets:

- the native "play track by index" entry point
- the native filename formatter / resolver around `%02d.ogg`

Those two hooks would support:

- immediate Lua track control
- later filename override or playlist override

## Bottom Line

This feature still looks feasible.

The recommended implementation target is:

- Lua control over the native soundtrack system first

not:

- generic `.ogg` support through the stock WAV mission-audio APIs first

That recommendation is based on confirmed static evidence, not just guesswork.
