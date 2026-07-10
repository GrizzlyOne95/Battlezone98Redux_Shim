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

## 2026-07-08 follow-up: recovered patch surface

The recovered decompile gives a concrete menu-time patch target.

### Key recovered functions

- `FUN_0076a240` behaves as `cWorkshop::buildMPResources`.
- `FUN_0076b350` behaves as `cWorkshop::buildSingleMPResource`.
- `FUN_007c7ad0` is the shell/screen factory that creates menu screens.
- `FUN_0076e6c0` is on the launch/selection path and calls
  `FUN_0076b350`.

### What `buildMPResources` does

`FUN_0076a240` is the dangerous broad preload path:

1. Checks `DAT_00915568 == 0` and `this+0x8c != 2`.
2. Sets `this+0x8c = 2`.
3. Logs `buildMPResources started`.
4. Iterates the MP map/mod list.
5. For each entry, stages the entry into resource priority/group state through
   calls including `FUN_00820e00(...)` and `FUN_006679c0(10, entry+0x84)`.
6. Clears Ogre resource group `Modable`.
7. Initializes Ogre resource group `Modable`.
8. Logs `buildMPResources complete`.

That matches the reported crash model: entering an MP screen exposes all
subscribed MP-map resources to the shared Ogre `Modable` group, so duplicate
material names collide before the player selects a specific map.

### What `buildSingleMPResource` does

`FUN_0076b350` is the deferred/single-selection path:

1. Checks `DAT_00915568 == 0`.
2. Avoids rebuilding if `this+0x8c == 0` and the stored selection at
   `this+0x90` already matches `mapDef+0x84`.
3. Sets `this+0x8c = 0`.
4. Logs `buildSingleMPResource for %s started`.
5. Stages only `mapDef+0x84`, plus explicitly marked safe mods from its
   associated mod list.
6. Clears and initializes Ogre resource group `Modable`.
7. Logs `buildSingleMPResource for %s complete`.

This is exactly the behavior wanted by the issue report: load assets when the
selected map/mod is being launched, not while the menu list is opened.

### Menu-time callers to suppress

`FUN_007c7ad0` calls `FUN_0076a240` while constructing two MP-related screens:

- screen type `0x0e`
- screen type `0x0f`

Initial decompile-only call-return guesses landed on nearby `operator new`
calls. A live attach to a manually launched, working Steam process on
2026-07-08 corrected the settled call sites:

- `0x007C84D2`: live bytes `E8 69 1D FA FF`
  (`CALL FUN_0076a240`)
- `0x007C855B`: live bytes `E8 E0 1C FA FF`
  (`CALL FUN_0076a240`)

The previously listed `0x007C84DD` and `0x007C8566` addresses are the following
`operator new` call sites, not the workshop preload calls.

The simplest experimental patch is to NOP those two five-byte calls. This keeps
the MP screen construction intact while skipping the broad `buildMPResources`
stage.

### Why not patch `buildMPResources` itself first

Patching the entry of `FUN_0076a240` to return immediately is broader than
needed. The function can also be called through `FUN_007681d0` depending on the
workshop state field at `this+0x8c`. Suppressing only the two screen-factory
calls is easier to reason about and should leave any non-menu maintenance path
alone.

### Validation requirements

The local Steam executable (`D298782F...B61CC90D`) stores protected/pre-settle
bytes at these addresses. Static disassembly and direct debugger launch can show
non-code bytes until Redux is launched correctly through Steam and reaches the
real game window.

Before enabling an OpenShim patch, validate in a real working game session:

1. Let Redux reach the main menu, then read the two call sites.
2. Confirm the settled bytes match:
   - `0x007C84D2 = E8 69 1D FA FF`
   - `0x007C855B = E8 E0 1C FA FF`
3. NOP both calls.
4. Enter the Multiplayer screen with conflicting subscribed MP map mods.
5. Confirm the menu opens without parsing all conflicting materials.
6. Launch one selected workshop MP map and confirm `buildSingleMPResource` still
   runs and the selected map's assets are available.
7. Check refresh behavior and map previews; if previews require staged assets,
   add a selected-row-only preview loader instead of restoring broad preload.

### Likely OpenShim shape

Add two guarded five-byte patches for the `FUN_007c7ad0` call sites:

- name: `Workshop MP Menu Deferred Load 1/2`
- fallback: `0x007C84D2`
- expected original: `E8 69 1D FA FF`
- payload: `90 90 90 90 90`

- name: `Workshop MP Menu Deferred Load 2/2`
- fallback: `0x007C855B`
- expected original: `E8 E0 1C FA FF`
- payload: `90 90 90 90 90`

Implemented as an opt-in OpenShim feature under
`features.workshop_mp_deferred_load` in `scripts/patches.json`, with
`OPENSHIM_ENABLE_WORKSHOP_MP_DEFERRED_LOAD` / `BZR_ENABLE_WORKSHOP_MP_DEFERRED_LOAD`
as explicit environment overrides and matching `*_DISABLE_*` overrides for
emergency rollback. This is a behavior change to menu loading, so the default
config remains disabled until verified with workshop entries that include custom
materials, textures, and safe-mod metadata.

For remote launch/probe work, use
`reverse_engineering/launch_redux_steam_probe.ps1 -ClickLauncherPlay -ProbeDefaultSites`.
Steam launches into a rendered launcher first; `-ClickLauncherPlay` advances it
to the actual game path before probing.

### 2026-07-08 first crash after default-on deployment

User crash dump: `C:\BZDumps\battlezone98redux.exe.12204.dmp`.

Findings:

- The shim log confirmed all three initial MP deferred-load controls were active
  before the crash, including both NOPs at `0x007C84D2` and `0x007C855B`.
- Exception: access violation at `0x00416299`, reading address `0x00000000`.
- The crashing function is `FUN_00416290`, the game/std-library C-string length
  helper.
- Exception context: `EAX=0`, `EIP=0x00416299`, `ESP=0x001AF50C`,
  `EBP=0x001AF520`.
- Stack unwound into `FUN_00796880`, the multiplayer-create screen constructor,
  at return site `0x0079931F`.
- The immediate source was:
  - `0x00799311: call FUN_007cb0c0`
  - `0x00799316: push eax`
  - `0x0079931A: call std::string ctor/assign from C-string`
- `FUN_007cb0c0` returns `NULL` when the selected list row at `this+0x14C` is
  negative. With broad MP resource loading deferred, the create screen can enter
  this path before a valid selected map row exists.

Follow-up patch:

- name: `Workshop MP Menu Selected Text Empty Fallback`
- fallback: `0x007CB0F2`
- expected original: `EB 02 33 C0 8B E5 5D C3 CC CC CC`
- payload: `EB 05 B8 9D 7F 87 00 8B E5 5D C3`

This changes the invalid-selection branch in `FUN_007cb0c0` from returning
`NULL` to returning an existing static empty C-string at `0x00877F9D`. It is
gated with `features.workshop_mp_deferred_load`, so disabling the feature rolls
back the two preload NOPs and this selected-text fallback together.

Important correction: the stock valid-selection path at `0x007CB0F2` jumps to
`0x007CB0F6`, so patching only `0x007CB0F4` leaves that jump landing inside
the replacement `mov eax, imm32`. The safe patch starts at `0x007CB0F2` and
changes the valid path to jump to the shared epilogue at `0x007CB0F9`.

### 2026-07-08 second crash: call-site skip was too broad

User crash dump: `C:\BZDumps\battlezone98redux.exe.16144.dmp`.

The second deployment reached the MP menu, then crashed in `FUN_00753280`:

- exception: access violation at `0x007532C8`, reading through a null vector
  backing pointer.
- context: `EIP=0x007532C8`, `EAX=0`, `ECX=0`, `ESP=0x001ADA44`,
  `EBP=0x001ADA54`.
- stack data included a real MP map name, `nachisa.bzn`.

The crash path goes through `FUN_007a3f80` and `FUN_00752d30` while resolving
the current MP selection. This means the earlier two-call skip suppressed more
than the dangerous material/resource parse. It also prevented enough
menu/list-resource bookkeeping that later selection code observed an empty
container.

Revised patch shape:

- let `FUN_0076a240` run, preserving MP map list/resource bookkeeping.
- skip only the late Ogre `Modable` group clear/init calls that parse broad
  menu-time MP resources and expose duplicate material names.

New guarded patch sites:

- name: `Workshop MP Resource Init Skip Clear`
- fallback: `0x0076A3B2`
- expected original: `FF 15 0C 99 86 00`
- payload: `90 90 90 90 90 90`

- name: `Workshop MP Resource Init Skip Initialise`
- fallback: `0x0076A3E7`
- expected original: `FF 15 10 99 86 00`
- payload: `90 90 90 90 90 90`

The selected-text empty fallback remains under the same feature gate as a
defensive guard, but the two menu-factory call-site NOPs were retired.

### 2026-07-08 third crash: same selected-list dereference

User crash dump: `C:\BZDumps\battlezone98redux.exe.10400.dmp`.

The targeted Ogre clear/init skip applied correctly, but the game still crashed
at the same selected map-list dereference:

- exception: access violation at `0x007532C8`.
- cause: null backing pointer while resolving selected MP map name.
- current stack again flows through `FUN_007a41c0 -> FUN_007a3f80 ->
  FUN_00752d30 -> FUN_00752ef0 -> FUN_00753280`.

Follow-up patch:

- name: `Workshop MP Selection Bounds Guard`
- fallback: `0x007A4202`
- expected original: `E8 79 FD FF FF`
- payload: JMP5 to `Trampoline_WorkshopMPSelectionGuard`

The trampoline replaces the stock call to `FUN_007a3f80` during MP selection
refresh. It validates:

1. screen pointer is non-null.
2. selected index at `this+0x38` is non-negative.
3. map-list pointer at `this+0x18` is non-null.
4. selected index is less than `FUN_004170C0(this+0x18)`.

If validation fails, it marks `this+0x38 = -1` and returns to the stock
continuation at `0x007A4207`, avoiding the invalid map-list dereference while
leaving valid selections on the original path.

### 2026-07-08 fourth test: no crash, but map list empty

The targeted `clearResourceGroup` / `initialiseResourceGroup` NOP test stopped
the crash, but the MP menu had no maps. That means the menu needs
`ResourceGroupManager::initialiseResourceGroup("Modable")` for broad map/file
discovery, even though broad script parsing is the likely duplicate-material
collision surface.

Revised patch:

- restore the stock `clearResourceGroup` call.
- replace only the MP menu `initialiseResourceGroup` call with a wrapper.
- wrapper temporarily unregisters Ogre's `ScriptCompilerManager` script loader,
  calls `ResourceGroupManager::initialiseResourceGroup`, then re-registers the
  script loader.

Ogre 1.10 `ScriptCompilerManager` registers the patterns:

- `*.program`
- `*.material`
- `*.particle`
- `*.compositor`
- `*.os`

So this wrapper allows the resource group to initialise and discover files while
deferring all Ogre script parsing, including material scripts, until the selected
map launch path calls the stock single-map resource loader.

Superseded wrapper patch:

- name: `Workshop MP Init Without Scripts`
- fallback: `0x0076A3E7`
- expected original: `FF 15 10 99 86 00`
- payload: six-byte JMP to `Trampoline_WorkshopMPInitWithoutScripts`
- continuation: `0x0076A3ED`

### 2026-07-08 fifth test: script suppression broke UI materials

The script-loader suppression build restored map enumeration behavior but caused
UI text/material fallout in the MP menu. That makes full script suppression too
broad, even though it avoided the duplicate-material crash surface.

Better patch shape:

- allow normal `ResourceGroupManager::initialiseResourceGroup("Modable")`.
- install a temporary `ResourceLoadingListener` only around the broad MP menu
  initialise call.
- in `resourceCollision`, remove the previously registered resource with the
  same name through `ResourceManager::remove(name)`, then return `true` so
  Ogre's existing retry path inserts the new declaration.
- restore the previous loading listener after the initialise call, including
  exception cleanup.

This keeps UI/material scripts parsing normally. The menu-time tradeoff becomes
duplicate resources using "last declaration wins" rather than crashing. Launch
of a selected map still uses the stock single-map resource path, which clears
and initialises `Modable` for the selected map only.

Active wrapper patch renamed:

- name: `Workshop MP Init Collision Guard`
- fallback: `0x0076A3E7`
- expected original: `FF 15 10 99 86 00`
- payload: six-byte JMP to `Trampoline_WorkshopMPInitCollisionGuard`
- continuation: `0x0076A3ED`
