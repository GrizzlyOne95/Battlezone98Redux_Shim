# Shared firing observer and per-weapon casings

2026-10-21 development checkpoint. Live game testing remains pending.

The registry now owns the two existing Cannon/MachineGun factory call patches
for shell casings, muzzle flashes and recoil. They retain their historical
`Shell Casings ... Shot Call` catalog names. The patches are requested when any
of the three existing switches is enabled. With all three off, neither call is
changed. No default setting or executable address was added.

Both qualified call sites use the same production x86 bridge. It invokes the
native factory once, then sends a successful result to each registered cosmetic
observer. A null factory result emits neither effect. EAX, nonvolatile registers
and the original RET 8 contract are preserved. Presentation installs after the
registry commits the calls and validates that their actual destination is our
bridge; it does not rescan or overwrite an already modified call signature.
Unknown foreign hooks and failed registry writes cannot be adopted as our sites.

The casing ODF observer installs independently of flash renderer/lifecycle
readiness. Casings alone need only the WeaponClass scope callback, not the five
presentation entry detours or craft scope hook. It reads Redux's live ParameterDB
before PopScope, including packed/mod ODFs, rather than searching loose files or
guessing the active mod. Configurations are cached by class pointer plus its
copied filename, with replacement on class reload. The table is bounded at 512;
overflow disables uncached fallbacks rather than losing an explicit opt-out.
No ODF parsing or file I/O was added to firing or per-frame callbacks.

## Content contract

Under `[WeaponClass]`, use `casingType = "none"`, `"small"`, `"medium"` or
`"large"`. Types select lengths of 0, 0.12, 0.24 and 0.40 respectively in the
existing cosmetic mesh scale. Invalid values disable casings. Missing values
use a small explicit stock ballistic allowlist; unknown weapons emit nothing.
The value is per definition; a missing child value uses that child's stock
fallback rather than a new shim-specific inheritance rule.

The existing ShellCasings master switch, class/ODF filter, object pool, culling,
physics, lifetime/sinking, resource guards and `<weapon>_casing.mesh` override
remain in effect. The filter cannot force brass onto a weapon marked `none`.
The old class/ammo-cost size inference is replaced by the explicit type.

Optional `casingMesh = "MyMod/Brass.mesh"` selects an Ogre mesh resource from
the already loaded mod/resource groups. Preserve filename case. Ship the mesh
and its referenced materials/textures. This key is read at the same exact-GOG
ODF scope seam as casingType. A missing/empty key tries `<weapon>_casing.mesh`,
then the generated case. An explicit missing resource suppresses that casing;
malformed paths, traversal, absolute filenames, non-`.mesh` names and names
over 120 characters are rejected. A changed class/mesh choice gets a separate
resource cache key. Resolution happens outside the firing hook, once per choice.

Author one rigid case centred at the origin, unit length 1 along local +Z,
base at Z=-0.5 and mouth at Z=+0.5. The type uniformly scales the entire mesh
by 0.12/0.24/0.40; collision still uses the existing approximate casing sphere.
The mesh supplies its material names; there is no separate casingMaterial key.
CR's `ODF/gminigun.odf` includes a commented, regeneration-safe example.

## Brass finish

The default now inherits stock `BZBase`, following the existing generated gib
material path for DX9/DX11 shader selection. The previous material was a plain
fixed-function pass with solid colours. The default's 256x128 diffuse/specular
atlas adds longitudinal brushing, fine scratches, annealed neck discolouration,
machined rim marks, a pale primer with a firing-pin mark, and low-specular soot.
Highlights respond to view/light direction through the stock shader; no glow,
reflection capture, overlay pass, per-casing texture or per-frame synthesis was
added. Two shared RGB textures total 192 KiB of pixel data before mipmaps.

The mesh now has a hollow mouth and inset primer with correctly oriented inner
walls: 200 triangles at ten sides, up from 120, retaining two submeshes. Texture
atlas V regions are body .02..48, rim .62, soot .76, primer .90. A custom mesh
may supply its own UVs and materials instead.

Marked generated materials/textures refresh on the next resource setup if their
bytes differ, fixing the previous keep-existing-file behavior. Unmarked custom
files remain untouched; a pack material override removes only owned generated
copies so the pack wins resource lookup. No installed game files were deployed.

An offline Blender study uses the actual exported mesh and diffuse texture with
an approximate metallic material. It is useful for inspecting form/UV/colour;
it is not an Ogre capture or in-game acceptance evidence.

Ejection still uses the native muzzle matrix and the existing estimated breech
offset, shooter velocity and tumble. It follows the firing mount of each craft;
this change does not author model-specific ejection ports or barrel-tip fits.
Casings are local cosmetic entities and send no network messages.

## Qualification and limits

- Per-weapon ODF reads use the existing exact GOG 2.2.301 scope seam. Other
  builds retain the conservative stock allowlist; custom ODF types are not
  claimed supported there. No new store/OS paths or loading dependencies exist.
- Flash/recoil activation retains its existing exact-GOG, single-player and
  authored-asset guards. This does not qualify CR co-op flashes.
- The real x86 bridge test covers all four casing/flash enable combinations,
  failed factory returns, argument recovery, factory count, return value,
  nonvolatile registers and stack cleanup. Scope callbacks still run before
  the native PopScope. The policy test covers invalid values, filename
  normalization, ballistic sizes and energy/launcher/unknown suppression.
- Release Win32 DLL build and 138 Win32 CTests passed. The stock executable static check passed 15 named
  resolves, four call destinations and five complete instruction steals.
- Independent Toolbox decode verified every generated triangle's winding against
  its normals, no degenerate faces, valid atlas UVs and inward hollow-mouth walls.
- Live visual placement, resource loading, pause, scene replacement, save/load,
  sustained-fire performance, co-op and Proton/Wine remain pending.

CR owns the matching 100 explicit choices and generated ODF blocks in its
`agent/weapon-casings` workstream, stacked on `agent/weapon-presentation`.
