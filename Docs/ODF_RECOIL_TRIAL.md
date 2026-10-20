# ODF recoil trial

2026-10-20: experimental source on `agent/odf-recoil-trial` in OpenShim and
EXU. This is a GOG 2.2.301 single-player cannon trial, not a release-qualified
feature. Normal installation remains disabled. Live firing, visual, model
reload and scene-lifetime acceptance are pending.

OpenShim owns accepted cannon shots, slot selection and the simulation clock.
Node slides need only OpenShim. Authored clips additionally need the companion
EXU branch loaded by the mission (normally `require("exu")`). That bridge reuses
EXU's existing `exu.animation` world/cockpit resolver and the guarded Ogre
operations used by its FPS controllers; it does not replace the pilot FSM or
install another EXU animation clock.

## Authoring

In the ship's `[CraftClass]`, suffixes 1..5 select weapon slots 1..5:

```ini
// Generated slide on a native model node (exact case, at most 8 bytes).
recoilName1 = "AGR11BGA"
recoilDistance1 = 0.30
recoilReturn1 = 2.5
```

Distance is metres; return is metres/second. Defaults are 0.6 and 3.0.
The kick is along the node's negative local forward axis. This first adapter
requires a static translation and retains live aiming orientation. It stages
the visual pose through the existing native-to-Ogre writer; it does not write
the supplied gameplay matrix. Node mode currently targets the named world
node, not a separate cockpit node or an arbitrary Ogre-only bone.

Alternatively, use an animation already authored into the model:

```ini
recoilAnimation1 = "recoil"
recoilPlaybackRate1 = 1.0
recoilCockpit1 = true
```

The clip starts at its kicked pose at time zero and ends at rest, matching
ISDFC's authored recoil clips. Its real length comes from EXU/Ogre. Playback
is non-looping, weight one, and uses simulation time. A new accepted shot
restarts it. The cockpit copy is optional and is resolved again when drawn.
Missing cockpit art does not suppress world playback.

A present `recoilAnimationN` wins over `recoilNameN`. An empty, malformed or
unavailable explicit clip does not silently fall back to moving a node. Clips
already enabled by another controller are refused on acquisition. Remove the
legacy ISDFC recoil profile for that craft when testing ODF ownership; this
trial does not migrate those profiles automatically. Missing EXU disables only
the animation path. Shared clips/nodes recover once per simulation step;
conflicting settings for a shared controller are refused.

Accepted bounds: clip name 1..63 printable non-space ASCII characters, clip
length at most 60 seconds, playback rate greater than zero and at most 50,
distance greater than zero and at most 10, return greater than zero and at
most 100. Malformed values disable the affected path. This trial reads ship
slot settings; it does not yet supply weapon-level recoil defaults.
Weapon ODF mesh flashes are now described in [ODF_MUZZLE_FLASH.md](ODF_MUZZLE_FLASH.md).

## avtank / gatstab setup

The stock avtank ODF has `weaponName1="gatstab"`, a cannon with a 0.30-second
shot delay. The shared Toolbox `read_vdf` reader identifies its world barrel
as `AGR11BGA`, under `AGR11TUR`, with muzzle `AGR11GC1` beneath it. The prepared
override uses 0.30 m travel / 2.5 m/s return (0.12 seconds). This is a starting
value, not a visual tuning result. It follows slot one if the weapon is swapped.
The stock model is not claimed to have an authored `recoil` clip.

```powershell
# Preview only, without changing the game:
./reverse_engineering/Prepare-AvtankRecoilTrial.ps1
# Install a reversible addon/avtank.odf override:
./reverse_engineering/Prepare-AvtankRecoilTrial.ps1 -Install
# Restore using the printed receipt; refuses to overwrite a changed ODF:
./reverse_engineering/Prepare-AvtankRecoilTrial.ps1 -RestoreReceipt <receipt.json>
```

The helper reads the local extracted stock ODF or an existing loose override;
it does not distribute stock game assets or modify gatstab/model files.

Build/deploy the complete OpenShim chain with `scripts/Deploy-OpenShim.ps1`.
For clip tests also deploy the matching EXU build to the mod's EXU location.
Launch through `BZRHarness.ps1` with `BZR_FORCE_WINDOWED=1` and the explicit
environment variable `OPENSHIM_TRIAL_ODF_RECOIL=1`. This enables only the
exact-build, byte-guarded SP cannon recoil candidate. The separate
`OPENSHIM_TRIAL_ODF_FLASH=1` opts into EXU-rendered ODF mesh flashes; the old
native ParticleRender flash backend remains excluded. `kNativePresentationLiveQualified` remains false for normal use.
Stop only the owned PID through `Stop-BZRGame -Id`; preserve other agents'
running games. See the existing weapon-presentation live qualification guide
for byte/ABI evidence collection before running the candidate.

## Checks and remaining work

Win32 OpenShim/EXU Release builds, 120/120 Windows CTests, EXU hardening
validation and its native HardeningSmoke pass. New runtime checks cover clip
priority, shared-clip timing, repeated shots, playback rate, pause and duplicate
steps, invalid clips, generated slide settings, multiplayer departure and
restoration retries after partial backend failures. These are host checks.

On 2026-10-20 an owned windowed GOG/DX11 avtank/gatstab smoke test bound
`AGR11BGA` and rendered EXU mesh flashes during normal AI cannon fire. The live
trace exposed the earlier misidentified cannon site; the corrected call and
caller frame are documented in the implementation/qualification guides.
A complete bounded baseline trace passed with no read errors or event cap.
An instrumented effects run observed 820 barrel pose writes, 0..0.300000012 m
of visual travel relative to the unchanged native node pose, and 33 completed
shots whose 64-byte firing matrices were unchanged after the bridge returned.
EXU reported 210 spawned flashes, zero failures/orphans, and zero live effects
at shutdown. Screenshots show the flash. These are smoke-test observations,
not general lifetime or descendant-motion acceptance; the normal gate stays false.

The authored fixture is
`reverse_engineering/test_missions/weapon_presentation/avtank_odf_trial.lua`.
Use it temporarily as `lcbench.lua` with the prepared ODFs, EXU on the mission's
Lua DLL search path, and locally supplied flash resources; restore those files
and the complete deployed load chain after testing. The fixture uses stock
`Attack`, not Lua `FireAt`, and contains no Lua flash producer.

Remaining checks include an existing ISDFC clip on world/cockpit targets with
its Lua recoil profile disabled, descendant motion, weapon swaps, pause, destruction,
save/load, model replacement, mission/scene transitions and SP/MP gates.
Steam, Proton and Wine remain unqualified and the exact GOG image guard
rejects other executable identities. No publication is included.
