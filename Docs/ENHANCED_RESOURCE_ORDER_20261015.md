# Enhanced resource order in multiplayer previews

The multiplayer lobby can parse CR's `Modable` shader wrappers before any
viewport-scheme reassertion occurs. Those wrappers compile the canonical
OpenShim HLSL sources. Previously the payload group was registered only when
installing the scheme fallback listener, so first-use previews could compile
with missing sources and repeatedly attempt shaderless DX11 draws.

The renderer now intercepts the executable's named Ogre
`ResourceGroupManager::initialiseResourceGroup` import. Immediately before
`Modable` is initialized, it bootstraps the existing verified Enhanced payload.
It uses the existing Ogre exports and group policy, on the caller's thread.
The import must still equal the resolved DLL export before an atomic pointer
replacement is permitted. Missing or changed imports leave the existing
viewport bootstrap in place. No build addresses, new INI options, shader copies,
exception suppression, or renderer switch are introduced.

The hook calls Ogre's export directly; initializing OpenShimEnhanced cannot
re-enter the executable import hook. Group registration remains once per
process. This uses the same Win32 game/Ogre ABI on all store/runtime lanes;
Windows GOG evidence does not qualify Steam, Proton or Wine.

Validation: Release Win32 build and all 110 CTest regressions pass. Native
Mission 15 two-client DX11 Enhanced qualification is recorded in the CR handoff;
the first corrected lobby observed zero rendering exceptions and zero missing
Enhanced sources, with OpenShimEnhanced parsed before CR_static_ibl.program.
