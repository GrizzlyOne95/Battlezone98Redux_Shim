# Mission Briefing OGV Loop Notes 2026-07-12

## Result

The mission-briefing planet videos use an explicit sub-loop measured in video
frames. The behavior is not derived from a fixed number of seconds and is not
tied to the game's render framerate.

The game-side `cUI_View::PlayVideoWithSubLoop(int frame, bool seekFirst)` path:

1. sets the Theora clip playback speed to `1.0`
2. optionally seeks to `frame` immediately when `seekFirst` is true
3. calls `OgreTheoraVideoClip::playAndReplayFromFrame(frame)`

The Theora Ogre plugin disables libtheoraplayer's ordinary auto-restart, stores
the supplied frame as its replay frame, and starts playback. During the
plugin's per-frame update, when `VideoClip::isDone()` becomes true, it calls
`seekToFrame(replayFrame)` and `play()`.

Thus the sequence is:

```text
first presentation: frame 0 -> EOF
later repetitions: replayFrame -> EOF -> replayFrame -> EOF ...
```

## Stock Loop Points

The GOG baseline's mission briefing constructor passes only two replay frames:

- frame `76`: `elspin.ogv`, `mrspin.ogv`, `vnspin.ogv`
- frame `96`: `emspin.ogv`, `jespin.ogv`, `jgspin.ogv`, `jispin.ogv`,
  `stspin.ogv`, `uraspin.ogv`

All stock clips are 320x240 at 15 FPS. Their observed frame counts and timing
are:

| File | Frames | Total | Replay frame | Intro before replay point | Repeated tail |
|---|---:|---:|---:|---:|---:|
| `elspin.ogv` | 133 | 8.87 s | 76 | 5.07 s | 3.80 s |
| `emspin.ogv` | 154 | 10.27 s | 96 | 6.40 s | 3.87 s |
| `jespin.ogv` | 154 | 10.27 s | 96 | 6.40 s | 3.87 s |
| `jgspin.ogv` | 153 | 10.20 s | 96 | 6.40 s | 3.80 s |
| `jispin.ogv` | 154 | 10.27 s | 96 | 6.40 s | 3.87 s |
| `mrspin.ogv` | 134 | 8.93 s | 76 | 5.07 s | 3.87 s |
| `stspin.ogv` | 154 | 10.27 s | 96 | 6.40 s | 3.87 s |
| `uraspin.ogv` | 154 | 10.27 s | 96 | 6.40 s | 3.87 s |
| `vnspin.ogv` | 134 | 8.93 s | 76 | 5.07 s | 3.87 s |

The apparent longer playback is the same approximately 3.8-second tail being
repeated while the briefing remains open.

The stock spin OGVs contain a Theora video stream and no Vorbis audio stream.
The briefing code triggers separate sound resources such as `emspin.wav` and
`mspin.wav`; replacing an OGV therefore does not replace that accompanying
sound behavior.

## Custom Video Requirements

To preserve stock timing, encode replacements at 15 FPS and retain the stock
filename. The end of each clip should cut seamlessly back to its assigned
replay frame.

Changing the encoded FPS changes the loop timing because the frame number stays
fixed. For example, replay frame `96` occurs at 6.4 seconds at 15 FPS, but at
3.2 seconds in a 30 FPS replacement. Resolution does not define the loop point;
the plugin obtains the dimensions from the decoded clip and uploads each frame
to its Ogre texture.

## Evidence

- Game wrapper: unpacked GOG `0x007D3E00`
  (`cUI_View::PlayVideoWithSubLoop` from the advisory PDB)
- Mission briefing call sites: unpacked GOG `0x007901E8` through `0x0079092A`
- Plugin sub-loop setup: `Plugin_TheoraVideoSystem.dll` RVA `0x7570`
  (`OgreTheoraVideoClip::playAndReplayFromFrame`)
- Plugin EOF replay: `Plugin_TheoraVideoSystem.dll` RVA `0x7770`
  (`OgreTheoraVideoClip::update`)
