# Optional weapon muzzle smoke/light

Copy `oshmuzz.odf` into a mod's normal ODF resources. Enable OpenShim Settings >
Video > Muzzle Flashes and restart, then configure the **weapon** ODF:

```ini
[WeaponClass]
flashMesh = "exu_small_flash.mesh"
flashMaterial = "EXU/CannonFlash/Amber"
flashDuration = 0.08
flashScale = 1
flashEndScale = 0.15
flashOffset = "0.20 0.10 2.41"
muzzleRender = "oshmuzz.render"
muzzleRenderDuration = 0.09
muzzleRenderOffset = "0.20 0.10 2.41"
```

The offset is specific to stock avtank/gatstab; measure the visible muzzle for
other models. The mesh/material come from EXU's `examples/odf_cannon_flash` and
need matching EXU loaded by the mission. Omit the `flash*` keys for native
render-only smoke/light; that path needs OpenShim without EXU.

This original example combines smoke and a brief light in `draw_multi`.
It references stock `smoke2.tga`; no game texture is redistributed. Change
`renderCount`/`renderNameN` to combine other engine render layers. Smoke
`emitDelay`, `emitVelocity`, `emitVariance`, `emitLife`, colour, radius and
texture remain normal render-definition properties. `muzzleRenderDuration`
controls how long the emitter is attached; emitted smoke has its own lifetime.
The native renderer owns particle advancement and cleanup after detach.

Both OpenShim master switches default OFF. Muzzle Recoil independently gates
craft-authored nodes/clips. Neither switch supplies assets or configures stock
weapons automatically. Legacy developer environment flags cannot override an
OFF setting. The current implementation is experimental, exact-GOG 2.2.301,
single-player cannon only. See `Docs/ODF_MUZZLE_FLASH.md` for inheritance,
validation bounds, failure isolation and remaining qualification.
