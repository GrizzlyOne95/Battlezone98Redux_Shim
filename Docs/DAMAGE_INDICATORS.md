# Directional incoming-damage indicators

Experimental, default-off feedback for the released GOG 2.2.301 executable.
OpenShim Options → HUD → Damage Indicators contains a separate five-control
page and front/right/rear appearance samples. Stock and Legacy scrap/pilot
layouts, native HUD scaling and outgoing hit-marker styling remain independent.

## Controls

All values are in `[Display]` and apply live.

| Key | Menu choices | Default | INI range |
| --- | --- | --- | --- |
| `DamageIndicators` | Off, On | 0 | boolean |
| `DamageIndicatorColor` | Red, Amber, White, Cyan, Magenta, Green, Blue, Yellow | Red | presets, #RRGGBB, 0xAARRGGBB |
| `DamageIndicatorSize` | Small, Normal, Large | 100 | 50–200 percent |
| `DamageIndicatorOpacity` | 50%, 75%, 100% | 75 | 25–100 percent |
| `DamageIndicatorDuration` | Short, Normal, Long | 600 | 150–2000 milliseconds |

Menu size choices are 75/100/150; duration choices are 300/600/1000 ms.
Color uses RGB; the separate opacity and fade determine alpha. Invalid values
use the defaults. Preview samples appear even when the feature is off and
never generate simulation events.

Arcs sit around the stock projected aim point. A horizontal bearing ahead of
the current camera appears above it, right appears to the right, and behind
appears below it. The source-minus-victim direction is captured at impact;
the arc rotates as the camera turns during its short lifetime. It does not
track an attacker after impact or indicate a projectile's eventual position.
An exactly vertical source has no horizontal bearing and produces no arc.

Only a weapon callback with a verified health decrease on the same live local
player object qualifies. Self damage, collisions, environment damage, healing,
immunity, missing sources and stale handles are excluded. The firing object's
position supplies bearing; this initial adapter does not claim the explosion
center or an exact ballistic arrival vector. Health loss as a fraction of
maximum health controls thickness and brightness, saturating at 20 percent.
The first half of the configured duration holds; the second half fades.
Eight bounded pulses support multiple directions, refreshing nearby bearings
and replacing the oldest when full.

Feedback is limited to single-player cockpit/chase views. Other views,
unreadable session state and multiplayer suppress drawing; safe-frame cleanup
also clears stored pulses when the player changes or a qualified view/session
is left. Shell screens suppress all feedback. Mission lifecycle and config
changes reset pulses. This does not change native damage, AI or weapon behavior.

## Native boundaries

The implementation extends the existing four guarded DamageAlloc wrappers in
`hud_feedback.cpp`; it adds no detour sites or native addresses. Those wrappers
preserve arguments and return values and already qualify the complete object
at receiver minus 0x18 and normalized health at complete object plus 0x200.
Both source and victim handles must round-trip before the stock call; the
victim must still round-trip afterward. The damager and damage-source fields
must exist and differ, matching the existing outgoing weapon-hit eligibility.

Incoming hooks copy only the source-minus-victim vector, victim handle, loss
and tick into fixed storage under the feature lock. No object pointer is kept;
there is no allocation, rendering or logging in the hook. Existing in-process
`SimDamageApplied` events remain outgoing-hit events and are produced only
when hit markers are enabled. Incoming damage does not enter an SDK event queue.

`GetCameraRecord` and `ViewRecord` are existing guarded catalog entries. Released
camera update code calls the record getter and passes a 64-byte MAT_3D to the
record update. The update stores its inverse at record +0x40; the released
inverse and vector-transform routines establish column-major rotation. The
adapter copies nine floats per draw, verifies finite orthonormal axes and
projects the captured direction onto camera right/forward. View modes 0 and 1
are cockpit/chase. Invalid data skips drawing.

The existing guarded main-reticle CALL and filled-rectangle helper draw clipped
owned geometry without replacing Stock art. Each arc uses 16 edge quads and
16 foreground quads. All outlines precede their fills. Native UI scale applies
to radius and thickness; size and opacity do not reuse reticle settings.
The five-control page reuses the existing preview artwork/quads and layout,
keeping the nine-tile hub intact. No new game asset or runtime dependency is
introduced. Fresh defaults install none of the feedback adapters. Once installed,
disabled adapters forward stock behavior until restart.

## Qualification

Exact released GOG executable SHA-256:
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.

- Release Win32 solution build and all 117 Windows tests pass. INI completeness
  (233 settings), conservative-default policy, writer (23) and migration (67)
  checks pass. The new portable policy test also passes GCC under WSL with
  `-std=c++17 -Wall -Wextra -Werror`.
- Stock/Off PID 50288: native `ReadProcessMemory` matched the original main
  reticle CALL, all four DamageAlloc entry guards and the camera getter.
- Static camera semantics were inspected in the released image using Ghidra;
  no leaked PDB addresses or layouts supply this implementation.
- GOG DX11 cockpit PID 28444: repeated enemy tank cannon fire reduced the
  local player's health with outgoing hit markers disabled. Frida observed
  120 post-damage samples and 606 red native filled-rectangle submissions.
  Front/right/left directions and a rightward camera turn were exercised;
  visual inspection showed the arc rotate left when facing right.
- PID 13972: Frida recorded 222 weapon callbacks, including 182 health
  decreases and 40 unchanged-health callbacks during native damage immunity.
  No arc fills occurred during the immune interval after the previous fade
  expired (7.6 seconds of unchanged-health callbacks). Normal damage and arc
  drawing resumed after clearing immunity. An idle interval reached 15.5
  seconds without arc submissions. Native fill alpha decayed before expiry.
- Camera guard refusal, PID 41088: deliberately mismatch only the deployed
  `GetCameraRecord` guard. OpenShim logs a stand-down; native
  `ReadProcessMemory` matches the original reticle CALL, all four damage
  entries and the camera getter. The catalog was restored afterward.
- Frontend PID 51708: compact 584×540 client area, five rows and three preview
  samples fit. Red → Amber changes the previews immediately; Off → On, size
  100 → 150, opacity 75 → 100 and duration 600 → 1000 persist and report live
  application. Escape returns to HUD, retaining Stock/Legacy and its other
  controls. Samples remain visible with incoming feedback disabled.
- Rear-bearing follow-up, PID 20964: the player turns 180 degrees while the
  firing source remains at its previously qualified world position. Frida
  captured 40 health-loss samples with the camera inverse forward axis facing
  backward, and 150 red fill samples below the aim point during that interval.
  This qualifies camera-relative rear placement without claiming that every
  weapon can hit from every physical approach direction.

Broad weapon/source coverage, long mission/restart/save/load,
eject/re-enter, view/resolution/HUD-scale combinations, actual multiplayer
suppression and other renderers remain unqualified. Steam is disabled by the
existing executable gate; Steam/Proton/Wine acceptance is unverified.

Local probes and logs live under ignored `bin/damage-indicators/`. No game
binaries, private symbols or decompiler output are committed.
