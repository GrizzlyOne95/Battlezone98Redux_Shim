# Custom campaign planet videos

Development feature: opt-in intro and loop timing for custom campaign OGVs.
The initial hook is restricted to the released GOG Redux 2.2.301 executable.
Steam, Proton, and Wine qualification remains pending. This is not a release.

Keep the standard campaign INI fields:

```ini
[MISSION1]
missionName = "Example mission"
missionBZN = "example.bzn"
planet = "custom"
planetDisplay = "crmoon.ogv"
planetDesc = "moon.des"
```

Place an INI-format `crmoon.pvi` next to `crmoon.ogv` in the mounted campaign
content. The video basename determines the sidecar name. Keep names flat and
case-correct; eight-character basenames are recommended for legacy resources.

```ini
[PlanetVideo]
LoopStartSeconds = 6.4
IntroSound = "emspin.wav"
StartAtLoop = 0
```

`LoopStartSeconds` is required. Playback starts at the beginning, plays the
intro once, then repeats from this time through the end of the video. The time
is converted to the nearest frame using the decoded clip's actual FPS: 6.4
seconds is frame 96 at 15 fps, 192 at 30 fps, or 384 at 60 fps. The selected
frame must precede the end of the clip. There is no separate loop end; author
the end of the file at the intended end of the rotation.

`IntroSound` is an optional flat WAV resource name. It plays once when this
mission screen opens, using the stock mission-screen sound handle and its
completion/cleanup behavior. It does not repeat when the video loops. Omit
it or use an empty string for silence. Embedded video audio follows the video
loop, so avoid baking a one-shot transition sound into the looped segment.

`StartAtLoop = 1` skips the intro, seeks to the loop frame immediately, and
suppresses `IntroSound`. The default is 0. Opening a fresh mission screen
starts a fresh presentation; this feature does not persist an intro-seen flag
across screens or sessions.

For a spin-only video use `LoopStartSeconds = 0`. For new renders, 2048x1536
at 30 fps is a practical initial target; real 60 fps renders need campaign
frame-pacing qualification. Use Theora OGV, 8-bit SDR yuv420p, preserve 4:3,
and keep a lossless source master.

## Fallback and ownership

Missing sidecars retain normal whole-file custom-video looping. Malformed
sidecars, duplicate/unknown keys in `[PlanetVideo]`, invalid sound names,
non-finite or negative times, and out-of-range loop frames also retain normal
playback. Invalid sidecars are reported under `planet-video` in the shim log.
Other INI sections are ignored. Files are bounded to 16 KiB and read through
the game's existing mounted-resource item API, with paired lock/release.

Only the custom planet's play call is redirected. Stock planet enums, stock
movies, other videos, and campaigns without sidecars retain their behavior.
The game and its Theora plugin own clips, looping, sound handles, and screen
cleanup. OpenShim retains no screen or video pointer between calls.

Build-specific signatures and engine bindings live in `scripts/patches.json`.
Every signature is unique and required; the hook is withheld unless the
original call target and all bindings resolve. The saved constructor owner must match the current mission-screen singleton
before its sidecar can change playback. The movie is attached to the screen
only after the play call, so checking the completed child tree here would
incorrectly reject every custom video.

## Validation

The engine-independent tests cover 15/30/60 and fractional FPS conversion,
EOF rejection, invalid numbers, traversal/non-WAV names, duplicate keys,
binary/oversized sidecars, case handling, and atomic fallback on parse errors.
Patch-registration tests check the call-site and named bindings.

Runtime acceptance must cover intro once across multiple loops, sound cleanup
on Back/mission change, StartAtLoop, missing/invalid sidecars, stock planets,
and scaling/frame pacing on the supported renderers. A successful build alone
does not qualify these behaviors or the other platforms.

Local GOG DX11 results, including a rendered 2048x1536/60 fps input and stock
fallback checks, are recorded in
[the qualification report](CUSTOM_PLANET_VIDEO_QUALIFICATION_20261014.md).
