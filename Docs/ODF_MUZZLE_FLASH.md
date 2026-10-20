# Custom ODF muzzle flashes (trial)

The `agent/odf-recoil-trial` branches in OpenShim and EXU let a weapon select a
3D muzzle flash without a mission-specific shot handler. OpenShim supplies the
accepted cannon shot and muzzle pose; EXU uses the same mesh pool, owner-follow
logic, render-space conversion and pause-aware lifetime as `exu.flash.Spawn`.

This remains an explicit GOG 2.2.301 single-player cannon trial. It needs both
matching DLLs, EXU loaded by the mission (usually `require("exu")`), and
`OPENSHIM_TRIAL_ODF_FLASH=1` in the game's launch environment. The existing
`OPENSHIM_TRIAL_ODF_RECOIL=1` is independent; set both to test both effects.
Normal activation remains disabled. The older native ParticleRender flash
candidate stays excluded from this trial.

## Minimal setup

Supply a flash `.mesh` and its material/texture in the mod's normal resources.
Add just this to the weapon ODF:

```ini
[WeaponClass]
flashMesh = "my_muzzle.mesh"
```

It uses the mesh's own material, a 0.08-second lifetime and scale 1. Every craft
using that weapon gets the same appearance at its actual committed muzzle.
Recoil settings remain on the ship and are not required for flashes.

For customization, the complete set is:

```ini
[WeaponClass]
flashMesh = "my_muzzle.mesh"
flashMaterial = "MyMod/MuzzleFlash"
flashDuration = 0.08
flashScale = 1.5
flashEndScale = 0.25
flashOffset = "0 0 0.15"
flashRoll = 0
```

| Key | Meaning |
| --- | --- |
| `flashMesh` | Opt-in Ogre mesh resource; exact case. Empty explicitly disables an inherited flash. |
| `flashMaterial` | Optional override. Empty restores the mesh's own material. Use the material to choose the texture, tint and blend appearance. |
| `flashDuration` | Seconds of simulation time, 0.005..5; default 0.08. Pausing freezes it. |
| `flashScale` | Uniform scale at spawn, 0..100. Also sets the end scale unless `flashEndScale` overrides it. |
| `flashEndScale` | Uniform scale at expiry, 0..100. Zero shrinks it away; both scales zero disables it. |
| `flashOffset` | Right/up/forward metres in the shot's local axes; each within -20..20. Default `"0 0 0"`. This changes only the flash. |
| `flashRoll` | Fixed rotation about the barrel, degrees -360..360; default zero. |

Missing values inherit from a mesh-configured parent weapon. Present malformed
values disable the affected flash rather than silently selecting another
effect. Mesh/material resource names are printable ASCII, at most 127 bytes;
case is preserved for Proton/Wine content paths. Materials should support the
intended renderer: an unlit additive, two-sided material with depth writes off
is a useful starting point for crossed cards or cones. The EXU mesh convention
points down local -Z after its simulation-to-render conversion, as documented
by `Definitions/Flash.lua` in EXU. This feature does not create art or convert
legacy `draw_geom` assets automatically.

EXU's `examples/odf_cannon_flash` now supplies original texture-free artwork:
`exu_small_flash.mesh` (0.85 m long, 0.24 m maximum gas radius) replaces the
BZ2-style mesh selection for small ordnance; `exu_heavy_flash.mesh` (2.35 m,
0.88 m) supplies a larger flash. Both use the same additive HLSL material with
hot-core colour, soft gas sheets and static turbulence. Select Amber or Blue
with `flashMaterial`; mesh, timing, start/end scale, offset and roll are ODF
controls. Brightness, colour and turbulence remain material parameters, and
the authored shape remains in the mesh. See EXU's example README for setup and
the shared-Toolbox mesh generator. Replace the ODF mesh selection rather than
overwriting BZ2 artwork.

The avtank/gatstab visual preset uses `flashOffset = "0.20 0.10 2.41"` to reach
the stock model's visible barrel tip from its native weapon hardpoint. This
is craft-specific and must be measured for another model. Existing stock
projectile geometry/effects remain visible and are not replaced by `flashMesh`.

The new `flashMesh` takes precedence over legacy `flashName` in the OpenShim
trial. Existing ISDFC Lua flash/recoil profiles are not migrated automatically;
disable the corresponding Lua flash producer when moving an already scripted
weapon to native ODF ownership. Existing ordnance effects are not stripped.

## gatstab preparation helper

To prepare a complete weapon override from the locally extracted stock ODF:

```powershell
./reverse_engineering/Prepare-OdfMuzzleFlashTrial.ps1 `
  -Weapon gatstab -Mesh "my_muzzle.mesh" -Material "MyMod/MuzzleFlash" `
  -Scale 1.5 -EndScale 0.25 -Offset 0,0,0.15
```

Preview is the default and prints the generated ODF path. Add `-Install` to
write `addon/gatstab.odf` with a restore receipt; use `-RestoreReceipt <path>`
to undo it. Existing authored flash keys are refused instead of duplicated.
The helper preserves weapon gameplay values and formats numbers independently
of the host locale. It does not copy meshes/materials or replace any DLLs.

Deploy the complete OpenShim chain with `scripts/Deploy-OpenShim.ps1` and the
matching EXU to the mod's existing EXU location before a live test. Use the
shared BZRHarness launch lock, `BZR_FORCE_WINDOWED=1`, and graceful shutdown.

## Scope and validation

Only successful cannon-shot observations produce a flash. Multiple pellets or
repeated notifications cannot restart an already active flash; an expired
pending flash is never created late. The original shot/gameplay matrix is not
modified. EXU carries the short-lived flash relative to the firing craft;
continuing turret motion after the shot is not a separately tracked attachment.
Flash failure or missing EXU leaves node recoil and stock firing independent.

EXU owns bounded pool IDs with caller lifetime cookies (so stale cleanup cannot
cancel a reused ID or a Lua-owned flash); OpenShim retains no Ogre pointers. Expiry, settings
disable, weapon replacement and SP departure cancel only this controller's
IDs. EXU's existing Lua-state and scene cleanup handles resource loss/unload.
The Lua `exu.flash.Spawn` API uses the same refactored spawn operation and keeps
its existing behavior.

Host coverage includes defaults/inheritance/opt-out, invalid fields, local-axis
offsets without projectile mutation, pending lifetime, pause, no restarts,
cancel retries and independent recoil after a flash failure. Native and visual
acceptance, repeated lifecycle transitions, other weapon families and
Steam/Proton/Wine remain separate qualification gates. No publication is claimed.

Current checkpoint: OpenShim/EXU Release Win32 builds and 120/120 Windows CTests
pass, as do EXU hardening validation and HardeningSmoke. Helper preview/install/
restore was checked with invariant decimal formatting and UTF-16 preservation.
The 2026-10-20 windowed GOG/DX11 avtank/gatstab smoke test loaded the matching
EXU and authored `isdfc_sflash.mesh`/`isdfc_sflash`, 0.12 s, scale 2 -> 0.25,
and offset `0 0 0.15` through the weapon ODF. No Lua flash producer was used.
Screenshots show the flash; EXU counted 210 spawns, zero failures/orphans and
zero live flashes at shutdown. Recoil simultaneously travelled 0.30 m and
returned to rest. A bounded instrumented sample checked 33 completed firing
matrices unchanged after the native presentation bridge. The load chain,
resources, EXU placement and temporary mission/weapon files were restored.
This proves the GOG smoke path only; the wider qualification gates above remain.

The subsequent original-art checks used EXU's small/Amber (81 flashes),
heavy/Amber (82) and heavy/Blue (82) meshes/materials on GOG/DX11. Each reported
zero failed/orphaned effects and zero live flashes at shutdown; the resources
loaded without DX11 shader/uniform/material parse errors. Captures show the
small and heavy bursts, and the final heavy/Amber run confirms the barrel-tip
preset above. Meshes round-trip through the shared Toolbox codec, regenerate
byte-identically and have finite vertices/nondegenerate triangles. Both shader
stages compile for DX11 and DX9; DX9 runtime remains unverified. Temporary game
files/configuration were restored. EXU's example README records the material
controls, shader-cache versioning and local BZ2/BZCC reference findings.
