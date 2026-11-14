# Loose-file resolution rule (addon\ / mods\ / stock)

Evidence for `scripts/Find-ShadowedModFiles.ps1`. GOG Redux 2.2.301 exe, read from
the private decompile corpus (addresses only here; nothing is copied from it).

## Rule

Engine files (ODF, GEO, SDF, BZN, TRN, HG2, MAT, LGT, DES ...) are opened through one
flat index, not by path.

| Claim | Evidence | Confidence |
|---|---|---|
| Key = lower-cased file name cut to 16 characters, extension included; folders are not part of it | name normaliser 0x00827640, used by build 0x008283E0 and lookup 0x00828850 | confirmed |
| Each name keeps up to 7 source indices, ascending; lookup returns the first in range, so the lowest source index wins | index build 0x008283E0, comparator 0x00828180, lookup 0x00828850, loose open 0x00828DC0 | confirmed |
| Source 0 is `<game>\addon` (root only, not its subfolders) | FS bring-up 0x00820F10; `\addon` built in main 0x00618FF0 | confirmed |
| Sources 1..n are the folders registered by the current cWorkshop::build*Resource call, in registration order, then the stock sources from the zix index | register 0x00820E00, clear 0x00820DD0, rebuild 0x00434440 -> 0x00820EC0 -> 0x00820F10; build* at 0x0076A030, 0x0076A240, 0x0076A430, 0x0076A600, 0x0076AB20, 0x0076AE60, 0x0076B350 | confirmed |
| The registered folders are the enabled mods (modEnabled.dat) plus the launched mission's own folder, registered last | buildSingleIAResource 0x0076A600; modEnabled.dat read 0x0076BFE0; runtime logs (CR session registers `mods\3686673790` as the mission folder with CR not in modEnabled.dat) | strong inference |
| An `addon\<subfolder>` that is neither enabled nor the mission's folder is not a source | no code path adds it; mod `.ini` discovery in `ISDF Chronicles` is root-only (20 of 22 `.ini` found) | strong inference |
| Ogre resources (material, program, mesh, skeleton, textures) come from the `Modable` group: `BZ_ASSETS` at priority -1 plus the same registered folders as overlays (0x00667700 ctor, 0x006679C0 add overlay). `addon\` root is not an overlay | Ogre log shows only `BZ_ASSETS` / `BZ_ASSETS_CORE` as locations; mod scripts appear with flat names | strong inference |
| Overlay priority: enabled mods count down from 100+n in registration order, the mission folder gets 10; a higher number is assumed to win | 0x0076A600 | inferred (direction not read) |
| Lua `require`: `mods\<id>` is on `package.path`; a `mods\` copy beats an `addon\<map>` copy | prior session notes (ExtraUtils.lua/exu.dll incident) | observed |

The 16-character cut means two long engine names with the same first 16 characters
are one key. The script reports those as `prefix16` and does not fail on them.

## Consequences

* A loose file directly in `addon\` overrides every mod and the mission folder.
* An enabled addon mod (e.g. `addon\stock_terrain_hd`) overrides the mission's own
  folder, which is where Campaign Reimagined sits when it is launched but not
  enabled.
* A subfolder such as `addon\ISDF Chronicles` only matters when it is enabled or a
  mission is launched from it.

## Not established

* Whether the registered-folder walk is recursive for engine files (ini discovery is
  not).
* Overlay priority direction for Ogre resources.
* The order of registration when the mission folder is also in modEnabled.dat.
* The `OpenShim` HD-terrain discovery (`src/engine/openshim_assets.cpp`) has its own
  order: every `addon\*` subfolder first (sorted), then `mods\*`, `packaged_mods\*`,
  Workshop items. That is a separate channel from the engine rule above.
