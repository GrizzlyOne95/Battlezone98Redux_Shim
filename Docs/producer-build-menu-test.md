# Producer nested build-menu live test

This is the smallest useful runtime test for the existing producer `BuildItem` bridge.

The goal is to answer one question before adding more hooks:

> Can the current `Producer::UpdateModeList` bridge expose Redux's native recursive `[Builder]` tree and carry a selected leaf into the stock producer build path?

## Current implementation

Current `main` already contains the experimental bridge:

- the runtime patch is named `Producer Build Menu Root Hook`
- the hook calls `MaybeApplyProducerBuildMenu` before the original producer helper
- the selected root is loaded with Redux's native `InitBuildItem` / `CleanupBuildItem`
- producer-specific ODF configuration is checked before generic producer-type configuration
- `[ProducerClass] buildMenuRoot = ...` and `buildMenu = ...` are both recognized
- `*_mp.odf` is checked before `.odf`
- the root value is normalized to Redux's native eight-character Builder token
- the runtime patch is enabled by the producer INI; no process environment variable is required

The bridge is still experimental and currently disabled on Steam by the producer-menu config loader. Use the GOG executable for this test.

## 1. Enable the producer-menu config

Copy:

```text
openshim_producer_build_menus.ini.example
```

to:

```text
openshim_producer_build_menus.ini
```

beside the game executable.

The example is already enabled for testing:

```ini
[ProducerBuildMenus]
Enabled=1
Factory=build
```

No environment variable or command-line setup is required. Set `Enabled=0` to opt out completely.

`Factory=build` is a stock fallback for factories without an ODF-local override. It also ensures the experimental config path is enabled before a producer ODF is examined.

## 2. Add an ODF-local root to a test Factory

In the Factory ODF used by the test map/mod, add this line to its existing `[ProducerClass]` section:

```ini
[ProducerClass]
buildMenuRoot = b_amcmbt
```

Do not quote `b_amcmbt` for this first test.

The bridge resolves the selected producer's ODF token, searches the active campaign/mod ODF candidate directories and `Edit\stock`, prefers `<producer>_mp.odf`, and reads `buildMenuRoot` or `buildMenu` from `[ProducerClass]`.

You can use another native Builder root later, such as:

```ini
buildMenuRoot = b_ambldg
```

or:

```ini
buildMenuRoot = b_amprod
```

## 3. Expected result

Enter a mission with that Factory and select the Factory.

OpenShim should log records similar to:

```text
[PRODMENU] Builder bridge: GOG ready
[PRODMENU] Config ... enabled=true ... factory=build ...
[PRODMENU] ODF root producer=<factory odf> root=b_amcmbt path=<resolved odf path>
[PRODMENU] Applied Factory root=b_amcmbt producer=... odf=<factory odf>
```

The producer menu should then expose the native recursive tree rooted at `b_amcmbt` instead of only the Factory's normal flat `buildItem1..10` list.

The stock American combat Builder tree includes leaves/subentries such as:

- `b_amscout`
- `b_amrazr`
- `b_amscrap`
- `b_amhraz`
- `b_amtank`
- `b_ammisl`
- `b_ambmbr`

The important test is not only whether these entries appear. Select a leaf, confirm that normal build progress starts, and confirm the expected unit is actually produced.

## 4. Regression checks

After the first successful menu display:

1. leave the Factory and reselect it
2. select a Recycler or other producer, then return to the Factory
3. if two Factories exist, alternate between them
4. build at least two different leaves
5. cancel a build if the normal UI supports it
6. leave the mission normally and check for shutdown errors/crashes

## Failure interpretation

### No `[PRODMENU]` hook/config records

Confirm `openshim_producer_build_menus.ini` is beside the executable, `Enabled=1`, and the GOG executable is being used. There is no longer an environment-variable prerequisite.

### Config loads, but no `ODF root` record

The selected producer ODF was not found in the filesystem candidates or the field was not found in its `[ProducerClass]` section. Confirm the actual producer ODF token shown by the `Applied`/diagnostic logging and the mod's ODF location.

### `ODF root` and `Applied` log correctly, but the menu stays flat

The current `UpdateModeList` seam is too early/late or the producer UI is rebuilding its flat mode list after the root swap. The next RE target is the mode-list population/navigation path rather than ODF parsing.

### Nested entries appear, but selecting a leaf does not build the unit

This is the most useful failure. It means native recursive navigation works and the missing bridge is the leaf handoff. The next implementation should hook/bridge `Producer::SetActiveMode` and/or `Producer::StartBuild` so the selected `BuildItem` leaf becomes the stock producer build selection.

### One producer's root leaks into another producer

The global `buildMenu` lifetime is the problem. Move the bridge toward per-producer/per-root state or restore/rebuild the root at every producer selection boundary.

### Crash while switching producers or changing missions

Treat this as a `BuildItem` ownership/lifetime bug. The current global-root cleanup/reinitialization must not be promoted until the transition is understood.

## Global smoke test without editing an ODF

To separate ODF discovery from the menu bridge itself, temporarily use:

```ini
[ProducerBuildMenus]
Enabled=1
Factory=b_amcmbt
```

If the global mapping works but the ODF-local test does not, the submenu bridge itself is alive and the remaining issue is producer ODF discovery/parsing.

## Success criterion for the next development step

The experiment graduates from "root-swap probe" once all of the following are true in one session:

- the ODF-local `buildMenuRoot` is recognized
- native nested entries render and navigate
- at least two leaf units build correctly through the normal Factory queue
- switching between producer types does not leak roots
- mission exit is clean

At that point the remaining work becomes hardening/per-instance ownership and Steam validation rather than proving the feature concept.
