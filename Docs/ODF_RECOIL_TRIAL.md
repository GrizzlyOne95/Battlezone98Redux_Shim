# ODF recoil trial

2026-10-20: experimental source on `agent/odf-recoil-trial` in OpenShim and
EXU. This is a GOG 2.2.301 single-player cannon trial, not a release-qualified
feature. OpenShim Settings > Video > Muzzle Recoil (INI `[SinglePlayer]
MeshRecoil`) is the master switch, default OFF; restart required. Enabling it
requires authored craft ODF nodes/clips and compatible model assets. It supplies
no generic animation. Model reload and scene-lifetime acceptance remain pending.

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

### Authored clip on the stock tank

`Prepare-AvtankAnimationTrial.py` authors `osh_recoil` into a local copy of
the stock avtank skeleton. The stock `Take_001` has no animation tracks.
The helper uses the sibling Modding Toolbox skeleton codec, first requiring
a byte-identical stock round trip. It inserts identity animation-only parents
above `AGR11BGA` (world) and `AGR21bga` (cockpit); existing bone transforms,
mesh bytes and vertex weights stay intact. Both new tracks start 0.30 m back
and ease monotonically to rest over 0.12 s. `--distance` and `--duration`
customize the authored motion; the ODF playback rate scales its timing.

```powershell
python ./reverse_engineering/Prepare-AvtankAnimationTrial.py `
  --output "$env:TEMP\avtank-animation-trial"
```

The output directory must be new. It contains `avtank.mesh`, `avtank.skeleton`,
an `avtank.odf` selecting `osh_recoil` with cockpit playback, and a hash manifest.
No game files are installed by this helper. For a later live trial, temporarily
mount the matched mesh/skeleton in the test mod and use the generated ship ODF;
back up and restore every override. Do not commit the generated game assets.

Offline inspection confirmed two monotonic tracks with correct kick/rest
endpoints, preserved original clips/bone transforms, and 113 existing weighted
vertices on each barrel bone. Live clip playback, aiming coexistence and cockpit
resolution remain unverified: the user requested leaving the active co-op game
running, so the authored-clip launch was deferred. The node-slide smoke result
below does not qualify these newly authored animation tracks.

Build/deploy the complete OpenShim chain with `scripts/Deploy-OpenShim.ps1`.
For clip tests also deploy the matching EXU build to the mod's EXU location.
Enable Muzzle Recoil before launching through `BZRHarness.ps1` with
`BZR_FORCE_WINDOWED=1`. This permits only the exact-build, byte-guarded GOG/SP
cannon ODF path. Muzzle Flashes is the separate master switch for weapon-authored
mesh flashes and `muzzleRender` smoke/light. Old developer environment flags no
longer bypass either master switch. `kNativePresentationLiveQualified` remains
false for broader/legacy activation; this bounded path requires explicit ODF
configuration and opt-in settings.
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
not general lifetime or descendant-motion acceptance; broader qualification remains open.

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
