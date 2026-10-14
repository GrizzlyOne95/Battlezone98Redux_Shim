# Custom planet video qualification 2026 10 14

This is a local development qualification, not a release or a maximum video
resolution/performance guarantee. The tested feature is described in
[CUSTOM_PLANET_VIDEOS.md](CUSTOM_PLANET_VIDEOS.md).

## Build and regression checks

- Release Win32 solution and final OpenShim plugin builds passed with MSVC v143.
- All 106 CTest checks passed, including the new policy and catalog tests.
- Final tested `plugins/openshim.dll` SHA-256:
  `8077b99595dd4824eeaa7b9ee7ea31ecf45b5f06a242b1e5926bdc16fa4f2948`.
- `git diff --check` passed.

## Native GOG DX11 run

The released GOG executable, SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`,
ran in a private test copy through BZRHarness. Its executable base was
0x00400000 and the final feature run used PID 43532. The full load chain and
catalog were deployed together using Deploy-OpenShim.ps1. The game ran
windowed and did not activate the desktop window or capture the real mouse.

Live catalog diagnostics showed one match for the custom call site and every
one of its seven required bindings, all selected from scanning with zero
fallback addresses. The live call operand pointed into the OpenShim plugin.
Read-only Frida observers recorded the native loop wrapper, decoder seeks,
intro-sound call and sound-stop call. Per-window captures confirmed rendered
output. Runtime logs and captures remain in the ignored local
`build/planet-video` directory and private test copy; no game binaries or
decompiler corpus are part of this change.

| Case | Result |
| --- | --- |
| HQ Moon, 1440x1080 at 15 fps; loop start 6.4 s | Engine loop frame 96; intro WAV called once, followed by five observed frame-96 loop seeks without replaying the WAV |
| Same movie, StartAtLoop=1 | Immediate seek to 96 and loop playback; intro WAV suppressed |
| Synthetic Theora, 2048x1536 at 60 fps; loop start 1 s | Rendered in the actual campaign panel; frame 60 selected and repeated across multiple loops; intro WAV called once |
| Loop start 999 s in a 2 s video | Warning and normal whole-file playback, with no custom loop call |
| Sidecar absent | Normal custom-video playback rendered without a feature error or custom loop/audio call |
| Back and reopen | Stock mission sound-stop method invoked; subsequent screen used fresh sidecar settings |
| Stock NSDF Moon presentation | Original emspin.ogv, frame 96 and emspin.wav behavior observed; no sidecar override applied |
| Exit | Owned test process closed gracefully; crash log remained empty |

The high-resolution test used moving synthetic imagery, not a rerender of the
planet art. It proves accepted format, rendering and loop timing in this lane.
It does not prove that every 60 fps frame was displayed, sustained performance
on other systems, or a resolution ceiling.

## Corrections established during qualification

The address resolver's `rel32_target` offset names the E8 instruction, whereas
the patched REL32 offset names its four-byte operand. The catalog test now
checks that distinction and rejects nonzero fallbacks on required bindings.

The mission constructor plays its movie before attaching it to Middle_Overlay.
A completed-child-tree ownership check therefore cannot gate this call. The
entry thunk passes the constructor's saved owner in EDX, and the handler
requires that owner to equal the current mission-screen singleton. The
released constructor frame slot is independently included in the singleton
binding's signature. No screen or clip pointer is retained across calls.

## Remaining lanes

DX9, Windows Steam, Proton and Wine remain unverified. They require their own
qualification before release; the patch is currently restricted to the GOG
distribution. Fresh 30/60 fps planet art, loop-seam review and sustained frame
pacing remain content/integration work. The main game installation and
Campaign Reimagined content were not changed by this workstream.
