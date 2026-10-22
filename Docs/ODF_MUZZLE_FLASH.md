# Custom ODF muzzle flashes (trial)

2026-10-21 follow-up: the authored ODF producer now also observes the separately
qualified MachineGun factory call, covering minigun/chaingun configuration with
the same tested bridge ABI. Cannon's existing simulation path includes Mortar
and SniperGun. This extends source coverage, not live qualification: machinegun
installation/visual behavior remains pending. Exact-GOG/SP/settings guards are
unchanged. Beam/charge/launcher/detonator/popper producers are not supplied by
this extension. CR's first 100-weapon inventory and 74 authored selections are
documented in CR `Docs/WEAPON_PRESENTATION_ROLLOUT.md`.

The machinegun call uses the existing Shell Casings-qualified site and is
checked for its original OrdnanceFactory callee before any hook is installed.
Like the existing cannon trial, this fails closed if another producer already
owns either call; it does not chain or overwrite a foreign Shell Casings hook.
Both options should not be treated as qualified together.

The `agent/odf-recoil-trial` branches in OpenShim and EXU let a weapon select a
3D muzzle flash without a mission-specific shot handler. OpenShim supplies the
accepted cannon shot and muzzle pose; EXU uses the same mesh pool, owner-follow
logic, render-space conversion and pause-aware lifetime as `exu.flash.Spawn`.

This remains an experimental GOG 2.2.301 single-player cannon feature.
In OpenShim Settings > Video, **Muzzle Flashes** is the master switch for both
the mesh flash and companion muzzle render effects. **Muzzle Recoil** controls
recoil independently. Both default OFF and require a game restart. Their INI
keys remain `[SinglePlayer] MuzzleFlash` and `MeshRecoil`.

Turning a switch on grants permission to use authored ODF configuration; it
does not add a generic effect to stock weapons. Mesh flashes need matching
OpenShim/EXU DLLs, EXU loaded by the mission (usually `require("exu")`), and
the referenced mesh/material assets. Native `muzzleRender` effects need
OpenShim and an authored engine render definition. Old developer environment
flags no longer enable effects or override an OFF setting. The exact-build,
byte, SP and mission guards remain enforced. Legacy `flashName` activation
and broader native qualification remain closed.

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

### Per-craft flash offset

A shared weapon ODF cannot know how deep each model's hardpoint sits inside its
barrel. A craft ODF may override the flash placement per weapon slot:

```ini
[CraftClass]
flashOffset1 = "0.20 0.10 2.41"
```

`flashOffset<N>` (N = 1..5, the weapon slot, same suffix as `recoilName<N>`)
takes the same `"right up forward"` metres as `flashOffset`, each within
-20..20. When present and valid for the slot that fires, it replaces the
weapon's mesh-flash offset for that craft's shots. It also replaces the
`muzzleRender` offset when that offset was defaulted from `flashOffset`; an
explicit `muzzleRenderOffset` on the weapon wins. A malformed value logs one
`flashOffset<N> rejected` warning and the weapon's own offset is used. Absent
keys change nothing. The effective offset is shown in the `presentation bound`
log line (`flashOffset=x,y,z`).

The avtank/gatstab visual preset uses `flashOffset = "0.20 0.10 2.41"` to reach
the stock model's visible barrel tip from its native weapon hardpoint. This
is craft-specific and must be measured for another model. Existing stock
projectile geometry/effects remain visible and are not replaced by `flashMesh`.

The new `flashMesh` takes precedence over legacy `flashName` in the OpenShim
trial. Existing ISDFC Lua flash/recoil profiles are not migrated automatically;
disable the corresponding Lua flash producer when moving an already scripted
weapon to native ODF ownership. Existing ordnance effects are not stripped.

## Companion smoke, light and render layers

Put these keys in the **weapon** ODF's `[WeaponClass]`, alongside `flashMesh`:

```ini
muzzleRender = "oshmuzz.render"
muzzleRenderDuration = 0.09
muzzleRenderOffset = "0.20 0.10 2.41"
```

`muzzleRender` names an engine render resource (`file.section`), not an Ogre
material or mesh. The optional original `examples/odf_muzzle_render/oshmuzz.odf`
combines `draw_twirl_trail` smoke and `draw_light` using `draw_multi`. Copy it
into the mod's normal ODF resources to use the example. Author another definition
to change smoke density/velocity, colours, textures, light or layer count.
Nothing installs this example on every weapon.

The emission attachment lasts `muzzleRenderDuration` seconds of simulation
time (default 0.08; 0.005..5). Individual emitted smoke particles use the render
definition's `emitLife`; they can linger after attachment detaches. Pause does
not advance the controller's deadline. The render is updated at the followed
muzzle while attached, then detached through stock renderer ownership; it does
not use EXU's mesh pool. Native renderer/particle timing remains engine-owned.

`muzzleRenderOffset` uses right/up/forward metres, each within -20..20. For a
new configuration it defaults to the resolved `flashOffset` (zero for a
render-only weapon). An inherited render configuration keeps its authored
offset until explicitly overridden. The identifier preserves case and is
1..63 printable ASCII characters without spaces or quotes. Absent render
fields inherit; `muzzleRender = ""` disables that channel. Malformed fields
disable only the render channel. Mesh scale, material and roll do not change
native render properties; configure those in the render definition.

Render-only weapons are supported. Mesh and native render channels have
independent simulation deadlines: an active smoke emitter does not block the
next short flash, and a failed mesh does not suppress the render effect or
recoil. A still-active render channel is not restarted by repeated shots.
Failed detach retains the stable pointer slot for native cleanup retries,
including through scene teardown. Effects are never created from rejected or
duplicate shot notifications. These controls require the Muzzle Flashes master
switch; they never alter projectile matrices or gameplay values.

## gatstab preparation helper

To prepare a complete weapon override from the locally extracted stock ODF:

```powershell
./reverse_engineering/Prepare-OdfMuzzleFlashTrial.ps1 `
  -Weapon gatstab -Mesh "my_muzzle.mesh" -Material "MyMod/MuzzleFlash" `
  -Scale 1.5 -EndScale 0.25 -Offset 0,0,0.15 `
  -MuzzleRender "oshmuzz.render" -MuzzleRenderDuration 0.09
```

Preview is the default and prints the generated ODF path. Add `-Install` to
write `addon/gatstab.odf` with a restore receipt; use `-RestoreReceipt <path>`
to undo it. Existing authored flash keys are refused instead of duplicated.
The helper preserves weapon gameplay values and formats numbers independently
of the host locale. It does not copy meshes/materials or replace any DLLs.
Omit `-Mesh` and supply `-MuzzleRender` to prepare a render-only override;
`-MuzzleRenderOffset` overrides the helper's default of using `-Offset` for
both channels. Existing render keys are refused along with existing flash keys.

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
its existing behavior. These master switches control OpenShim's ODF producers;
a mission's separate Lua effect producer retains its own policy.

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

The weapon `muzzleRender` extension and master-switch follow-up pass the Win32
Release build, 120 Windows CTests, INI writer/migration/default checks and
GCC/WSL runtime/policy checks with warnings treated as errors. Coverage includes
both channels together, separate deadlines/offsets, pending expiry, pause,
partial factory failure, detach retries through scene loss, render-only weapons,
all four master-switch combinations and enabled settings without authored data.
The helper passed mesh+render and render-only install/restore, UTF-16 preservation,
invariant formatting and malformed/duplicate key refusal. The new smoke/light
and settings UI live check is deferred while the user's Instance6 co-op game is
running; the earlier mesh/node evidence does not qualify this native render path.
Steam, DX9 runtime, Proton/Wine and broader lifecycle qualification remain open.
