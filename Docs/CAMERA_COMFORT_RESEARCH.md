# Camera comfort investigation

2026-10-19, released GOG Redux 2.2.301. This is research, not an installed
camera-shake setting. Stock camera and simulation behavior remain unchanged.

## Findings

The existing quake replay-fade fix in `src/patches/ui_camera_fixes.cpp` is a
save/load repair, not a general visual-intensity control. Its native sites
already live in the catalog as `EarthQuakeStartQuake`, `EarthQuakeUpdateQuake`,
`EarthQuakeStopQuake` and `EarthQuakeSimulate`.

Released static analysis establishes that StartQuake stores scale at +0x28
and starts the looping `gquak01.wav`; UpdateQuake changes both that scale and
the loop's gain. Simulate iterates craft, derives terrain-relative attenuation,
generates random vectors, changes the object's transform and passes an
additional motion vector into the craft path. The latter accumulates fields
at +0x12C/+0x130/+0x134 and updates a vector magnitude and reciprocal. These
are simulation writes, beyond a final local view transform.

Consequently, multiplying the quake scale or skipping Simulate is not a
qualified cosmetic implementation of Reduced/Off. Stopping quake audio is
also outside the proposed camera-comfort control. The existing replay-fade
repair must retain its lifecycle and script-ownership behavior.

## Recommended next implementation boundary

Investigate the final local player camera pose after stock simulation and
before its render-camera submission. Separate at least:

- explosion/earthquake-induced view motion;
- cockpit or walking bob;
- weapon presentation recoil;
- intentional scripted/cinematic camera motion.

Suggested eventual player choices: Stock (100%), Reduced (50%) and Off,
default Stock. Only a proven visual component should be scaled. A generic
low-pass filter on the whole camera would add aim latency and alter intended
turning, so it is not an acceptable substitute.

Qualification needs locked-input A/B recordings showing identical player and
AI motion, aim and projectile behavior, damage, quake audio and mission
scripts. Test cockpit/chase/on-foot, save/load, restart, cinematics and the
network-session gate. Live tracing must establish the released call site,
argument ownership and view lifetime before adding any native patch row or
player-facing setting. Steam/Proton/Wine remain separate runtime lanes.

No new shake hook or user option is introduced by this investigation.
