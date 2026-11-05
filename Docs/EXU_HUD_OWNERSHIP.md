# EXU HUD ownership

EXU can replace selected HUD areas while OpenShim continues providing native
layout and engine services. OpenShim's stock draws, palette overrides and idle
fading yield only the areas explicitly claimed by EXU. User preferences are not
rewritten. Command controls and the pilot readout remain native.

The optional provider exports live on the loaded `openshim.dll` plugin, not on
the stable loader SDK table:

```cpp
uint32_t __cdecl OpenShimSetExternalHudOwnership(uint32_t mask);
uint32_t __cdecl OpenShimGetExternalHudOwnership();
```

The setter accepts a complete mask and returns the resulting mask. Bits are
hull=1, ammo=2, weapons=4, scrap=8, radar=16 and commands=32. Zero releases all areas. Unknown
bits, unsupported game builds or unavailable draw adapters retain the preceding
mask. Calls that install adapters must run on the mission update/frame thread.
This is a single-consumer EXU contract, not a general multi-plugin arbiter.

Command ownership yields palette overrides and fading while retaining the native
command renderer, input, labels and menu sounds. EXU owns the replacement drawing
and animation. OpenShim contains no BZ2 command/target renderer. The command bit
is additive; older consumers using masks through 31 keep their existing behavior.

EXU probes both the root bridge and actual provider capability. Older providers
retain EXU's expected-byte-checked fallback. The coordinated path uses OpenShim's
existing verified draw adapters instead of EXU overwriting their CALLs. Scrap
also uses EXU's checked complete-block suppression to hide the stock sprite.
Radar ownership keeps native contacts/compass/layout services; OpenShim yields
its background, colors and fade while EXU provides presentation.

EXU releases ownership when disabling each replacement and on Lua-state close,
including the exception cleanup path. OpenShim also releases when EXU disappears.
The hooks remain installed as pass-through adapters after release, so stock HUD
settings resume without reinstalling or tearing down another module's patches.

## Validation on 2026-11-05

- Release Win32 complete solution built; complete chain deployed using
  `scripts/Deploy-OpenShim.ps1`.
- All 172 existing CTests passed. The new policy test passed after correcting
  its Release-build assertions (173 tests total).
- Native GOG 2.2.301 `isdfms06` logged independent acquisition through mask 0x1F
  and release to zero on exit. Read-only native tracing confirmed hull, ammo
  and weapon CALLs enter this provider's adapters while mask 0x1F is active.
- A disconnected desktop initially clamped PNG widths to 604 pixels despite
  larger requested modes. The opt-in `OPENSHIM_FRAME_CAPTURE_SIZE` fix now produces
  verified 2560x1440 native PNGs without camera/controller changes. The source rim
  border follows the blue perimeter and stock status draws are absent behind
  the EXU status ring. Its bounded parser has a separate host test (174 total).
- Constructor placement, mission transitions and the Steam/Proton/Wine matrix
  remain to be qualified.
