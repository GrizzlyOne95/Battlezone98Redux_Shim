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

Validation: Release Win32 build and all 110 CTest regressions pass. Native run `misn15-final7-20261015` passes nine assisted progression steps and
24 checks on the configured local server with two isolated GOG 2.2.301 DX11
Enhanced clients. Both clients survive validation with no caught rendering,
Lua or unresolved-label errors; all 94 presentation operations match.
OpenShimEnhanced parses before CR_static_ibl.program, with zero missing Enhanced
source errors. Existing flat.dds texture warnings are separate from this repair.
The run qualifies this exercised path, not final visual quality or other stores
and compatibility runtimes. Private evidence is under
`C:\BZRCoop\runs\misn15-final7-20261015`; stage and load-chain hashes are in
`C:\BZRCoop\misn15-20261015\provenance-final7.json`.

## Four-client cold-start regression, 16 October

The first Mission 12 four-client control reproduced a remaining race on the
fourth client. Its CR wrappers compiled before the patch worker reached renderer
profile initialization. Installing the resource hook before Modable parsing is
insufficient if the hook itself is installed after that first parsing pass.

The patch worker now arms the import-only resource bootstrap before its other
initializers and expensive patch sweep. The existing exact import/export
identity check and atomic replacement remain in place. Repeated installation
recognizes its own hook. Payload registration still runs exclusively from the
later Ogre caller thread, not the worker or loader lock. Full profile and
address-dependent scheme initialization retain their existing ordering.

Release Win32 and all 110 CTest checks pass. The private four-client rerun and
campaign matrix live under `C:\BZRCoop\qualification-20261016`. The original
failed rendering control remains recorded. The rerun
`misn12-four-smoke-v2-20261016` passes four steps / 38 checks with four native
clients. All four register OpenShimEnhanced before the CR wrappers load; no
missing Enhanced sources or caught rendering exceptions remain. Roster,
directional alliances, audio, script/label health and native network diagnostics
pass. This is a cold-start/rendering regression, not Mission 12 progression.
