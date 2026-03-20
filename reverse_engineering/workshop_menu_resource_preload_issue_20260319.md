# Workshop Menu Resource Preload Issue

Question: when Redux enters a workshop-backed menu such as multiplayer map
selection, is the crash from an unavoidable Ogre behavior, or from Redux
choosing to preload too many files too early?

## Bottom line

This looks tweakable, but the right seam is the Redux workshop/resource-builder
layer, not Ogre itself.

- Redux has an explicit `cWorkshop` subsystem with separate functions for:
  - `parseWorkshop`
  - `buildModResources`
  - `buildMPResources`
  - `buildIAResources`
  - `buildSingleMPResource`
  - `buildSingleIAResource`
  - `listDir`
- The runtime log shows Redux accepts a workshop whitelist wider than just
  metadata:
  - `*.ini`
  - `*.des`
  - `*.dds`
  - `*.png`
  - `*mod.material`
- Ogre only shows one general-purpose mod resource group, `Modable`, pointed at
  `./BZ_ASSETS`, and then parses material scripts from that shared group.

So the likely failure model is:

1. Redux workshop parsing discovers all subscribed mods for the menu category.
2. Redux resource-building stages or exposes whitelisted files for those mods.
3. Ogre parses the shared `Modable` resource group.
4. Duplicate material names collide in the global material namespace and the menu
   can crash before map launch.

That is not "Ogre randomly loading all files on its own." It is much more
likely "Redux asked Ogre to see a broad staged asset set too early."

## Evidence

### 1. Redux has dedicated workshop build phases

From the PDB exports:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/pdb_reference/public_functions.csv`
  includes:
  - `?parseWorkshop@cWorkshop@@SAXXZ`
  - `?buildModResources@cWorkshop@@SAXXZ`
  - `?buildMPResources@cWorkshop@@SAXXZ`
  - `?buildIAResources@cWorkshop@@SAXXZ`
  - `?buildSingleMPResource@cWorkshop@@SAXAAUcMapDef@@@Z`
  - `?buildSingleIAResource@cWorkshop@@SAXAAVcPathing@@@Z`
  - `?listDir@cWorkshop@@CAXPBD0@Z`

The `llvm/pretty_funcs.txt` export also shows these as substantial real
functions, for example:

- `cWorkshop::parseWorkshop()` size about `6148`
- `cWorkshop::listDir(...)` size about `2578`
- `cWorkshop::buildModResources()` size about `823`
- `cWorkshop::buildMPResources()` size about `764`
- `cWorkshop::buildSingleMPResource()` size about `582`

That is strong evidence Redux has explicit menu/workshop staging logic rather
than relying on Ogre to discover mods by itself.

### 2. The live logger shows a broad whitelist

`BZLogger.txt` recorded:

- `OnWhitelistUpdated`
- whitelist entries:
  - `*.wav`
  - `*.ogg`
  - `*.ini`
  - `*.inf`
  - `*.jpg`
  - `*.txt`
  - `*.stb`
  - `*.des`
  - `*.dds`
  - `*.png`
  - `*.sta`
  - `*mod.material`

That directly contradicts the desired behavior in the issue report. Redux is
not limiting menu-time workshop handling to just `INI/DES/etc`.

### 3. The logger discovers many mods up front

`BZLogger.txt` shows many `MOD FOUND ...` lines for addon and workshop content
before gameplay load, including workshop and packaged mods.

That matches the issue description that simply entering a menu causes broad mod
discovery and setup.

### 4. Ogre is using a shared mod resource group

`BZOgreLogfile.log` shows:

- resource group `Modable` is created
- `./BZ_ASSETS` is attached to that group
- Ogre parses scripts for resource group `Modable`
- Ogre then creates resources for that same group

This matters because Ogre material names are effectively global once their
scripts are parsed into the manager. If Redux stages multiple mods' material
files into the same shared resource set before a specific map is launched,
duplicate names are an expected collision risk.

## Likely patch direction

The clean fix is probably in `cWorkshop`, not in Ogre:

1. Keep menu-time workshop parsing focused on metadata only.
2. Do not stage `*.dds`, `*.png`, or `*mod.material` during menu list
   population.
3. Delay `buildSingleMPResource` style asset staging until the selected map is
   actually being launched.

If menu previews absolutely require some art, the safer compromise is:

- allow only explicitly needed preview assets for the selected row
- keep them isolated per selected mod
- unload them immediately when selection changes

## Less attractive Ogre-side fallback

An Ogre-side mitigation would be to isolate each mod into its own resource group
and avoid globally parsing every subscribed mod's materials at once.

That may reduce collisions, but it is likely the wrong primary fix because:

- the broad file whitelist is already chosen before Ogre gets involved
- the workshop system appears to have explicit "build resources" phases
- menu list population should not need full material registration for every
  subscribed multiplayer map pack

## Practical conclusion

Yes, this looks potentially tweakable.

The highest-value target is a Redux workshop patch that narrows menu-time mod
resource staging and postpones real asset registration until launch of the
selected map. Ogre is mostly the collision surface here, not the root policy
decision.
