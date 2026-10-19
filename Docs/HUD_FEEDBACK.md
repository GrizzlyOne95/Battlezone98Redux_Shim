# Reticle and hit feedback

Experimental, opt-in native feedback for the released GOG 2.2.301 executable.
OpenShim Options → HUD contains the controls. Stock style, reactive feedback
off and hit markers off are the shipped defaults; this combination installs
none of the new adapters.

## Player controls

All controls apply live and persist in `[Display]` in `openshim.ini`.

| Key | Menu choices | INI default |
| --- | --- | --- |
| `ReticleStyle` | Stock, Cross, Dot, CrossDot | Stock |
| `ReticleColor` | White, Green, Cyan, Amber | White |
| `ReticleSize` | Small (75), Normal (100), Large (150) | 100 |
| `ReticleThickness` | Thin (1), Normal (2), Thick (3) | 2 |
| `ReticleOutline` | Off, On | 0 |
| `ReticleOpacity` | 50, 75, 100 percent | 100 |
| `ReactiveReticle` | Off, On | 0 |
| `HitMarkers` | Off, On | 0 |
| `HitMarkerDuration` | 80, 120, 180, 250 ms | 120 |

The INI also accepts size 50–200, opacity 25–100 and duration 60–400.
Unknown styles preserve Stock; unknown colors use White. Styling affects the
custom geometry and feedback, leaving the Stock sprite's appearance alone.
The reticle follows the engine's projected aim point and UI scale. It does
not change weapon spread, aim, projectile behavior or convergence.

Reactive feedback contracts the custom cross's gap and adds two side brackets
when the stock reticle already has an object. Brackets also work with Stock
art. This is generic contact feedback, without friend/enemy classification.

Hit feedback adds short white diagonal ticks, holding for half the configured
duration and fading for the remainder. A successive hit refreshes one pulse.
It requires verified health loss from the local player's weapon against
another live object. Immune/zero damage, healing, collision/environmental
damage, self damage, AI damage and stale object identities do not qualify.
There is no separate kill marker, hit sound or damage number.

Reactive feedback and hit confirmation are disabled in network sessions;
custom static reticle styles remain cosmetic. Unreadable session state fails
closed. Steam, Proton and Wine are not qualified; the initial adapter is
disabled for Steam executables and the Options rows explain that restriction.

## Native boundaries

`hud_feedback_policy.h` owns portable drawing, clipping, hit eligibility and
pulse timing. `hud_feedback.cpp` owns the guarded native adapter. Every engine
site is a named `engine_addresses` row in `scripts/patches.json`.

Only the first main sprite call in the released Reticle HUD callback is
redirected. The later weapon lock side markers and the 3D reticle are left to
the engine. Drawing uses the current pane, original aim coordinates and
native filled rectangles, with bounded storage and clipping. Invalid panes,
scales or coordinates retain the original submission. Shell screens suppress
custom drawing and feedback.

Hit confirmation wraps the four Building/Craft/Person/Powerup DamageAlloc
entries. Released instructions establish a distributedObject receiver at
complete-object +0x18 and two stack arguments (`RET 8`); wrappers preserve both
arguments and EAX. The producer resolves the damager through the existing
obj76 accessor, checks the local player's handle, samples normalized health
at complete-object +0x200 around the original call, and verifies the same full
handle still resolves to that object afterwards. Missing evidence skips the
confirmation. The source and damager must both exist and differ, excluding
the stock collision path.

`SimDamageApplied` is an optional in-process event, produced only while hit
markers are enabled. It never enters the SDK polling queue. The hook does no
rendering, allocation or logging; its consumer runs at the existing safe
event drain and rejects expired events before starting a pulse. Mission
transitions, resets and configuration changes clear the pulse. Career stats
need not be enabled. All four entry guards must bind before installation;
partial detour installation forwards stock calls without publishing hits.

## Qualification, 2026-10-19

Released GOG executable SHA-256:
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
Static analysis was checked against live released bytes in PID 50980.
Reticle submission observed sprite 415, flags 0x250004 and UI scale 2/2.

- Release Win32 solution build passed. All 113 Windows and 92 Linux host
  tests passed; INI shipping-policy, writer and migration checks passed.
- GOG DX11 windowed fixture, PID 37744: local player fired at a stationary
  craft, then native damage resistance held health unchanged, then resistance
  cleared, then health was reduced for a lethal shot. Frida observed 109
  damage callbacks, including 32 unchanged-health callbacks. White feedback
  submissions appeared during actual damage, disappeared during immunity,
  resumed after immunity cleared and stopped after depletion. Cyan custom
  reticle submissions continued throughout. The lethal health transition was
  observed; it does not establish a separate kill-notification contract.
- Stock/Off fresh launch, PID 36000: original main reticle visibly restored;
  all four damage entries and the main draw CALL retained their original
  bytes before instrumentation. Custom CrossDot/contact art was also
  inspected in a separate live mission.
- Frontend Options, PID 4404: HUD category contains all 14 rows. Selecting a
  custom style writes the INI and installs the draw adapter without restarting.
  The style control cycles Cross → Dot → CrossDot → Stock, reporting each as
  applied.
- Guard refusal, PID 45196: deliberately mismatching only the catalog's main
  reticle CALL guard logs a stand-down. The live CALL and all four damage
  entries retain their original bytes. The deployed catalog was restored and
  its SHA-256 matched the source afterwards.
- All-class follow-up, PID 1864: sequential stationary `absilo`, elevated
  `aspilo` and `apammo` targets exercised the Building, Person and Powerup
  adapters. The captured callback sample contains 24 building, 48 person and
  48 powerup calls; health decreases and white feedback submissions were
  observed for each class. PID 528 independently exercised the powerup path.
  These fixtures use repeated local cannon fire and establish narrow adapter
  coverage, not general weapon or damage-source acceptance.
- `verify_windows.ps1` accepted deployed catalog identity, load chain and the
  absence of stale configuration. Its overall result remains FAIL because
  the development build and installed suite both report 1.0.0.53: the suite
  updater can overwrite this build. No release version was changed. The final
  DLL/catalog were redeployed and their source/deployed hashes compared.

Remaining acceptance: broad weapon/source coverage; long mission/restart/save/load
sessions; other view modes, resolutions and renderers; live multiplayer
suppression; Steam/Proton/Wine qualification. A narrow local portrait window
crops the existing two-column Options layout, and the local direct-mission
pause menu rendered black with both feedback enabled and Stock/Off. These
observations do not qualify the full Options layout or pause-menu path.

Raw probes and fixture output are local scratch under ignored
`bin/hud-feedback/`; no decompiler output, game binaries or private symbols
are part of this feature.
