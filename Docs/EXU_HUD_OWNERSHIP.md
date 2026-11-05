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
hull=1, ammo=2, weapons=4, scrap=8 and radar=16. Zero releases all areas. Unknown
bits, unsupported game builds or unavailable draw adapters retain the preceding
mask. Calls that install adapters must run on the mission update/frame thread.
This is a single-consumer EXU contract, not a general multi-plugin arbiter.

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
- Engine readback PNGs were captured, but the disconnected desktop clamped
  their width to 604 pixels despite larger requested Ogre modes. These are
  runtime evidence, not full-resolution visual acceptance. Constructor placement,
  mission transitions and the Steam/Proton/Wine matrix remain to be qualified.
