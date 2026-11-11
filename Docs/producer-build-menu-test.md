# Producer nested build-menu live test

PRODMENU gives a Recycler, Factory or Constructor nested build pages taken from
a native `[Builder]` tree. It replaces the producers' `UpdateModeList`,
`SetActiveMode` and `Deselect` vtable slots and hooks ControlPanel
PostLoad/Cleanup. See "Hook sites" and "Submenu cost" in
`reverse_engineering/producer_build_menu_notes.md`.

The feature is on by default and needs no configuration file. A producer only
gets pages when its ODF names a menu root; every other producer keeps its stock
flat list. GOG and Steam run the same code.

## 1. Name a menu root in the producer ODF

Add one line to the producer's existing `[ProducerClass]` section:

```ini
[ProducerClass]
buildMenuRoot = b_amcmbt
```

`buildMenu = ...` is accepted as an alias. The value is the native
eight-character `[Builder]` token, unquoted. OpenShim reads
`<producer>_mp.odf` before `<producer>.odf`, from the active campaign/mod ODF
roots and `Edit\stock`.

## 2. Optional: `openshim_producer_build_menus.ini`

The file is not needed. Copy `openshim_producer_build_menus.ini.example` beside
the game executable only to:

- turn the feature off: `[ProducerBuildMenus] Enabled=0`;
- give every producer of a type a root with no ODF edit
  (`Recycler=`, `Factory=`, `ConstructionRig=`);
- override one producer ODF's root from outside the mod.

Root precedence: the ODF's own `buildMenuRoot`, then a per-ODF INI override,
then the type mapping.

## 3. Expected result

Enter a mission with that producer and select it. `openshim.log` shows lines
like:

```text
[PRODMENU] No ...\openshim_producer_build_menus.ini; enabled for producer ODFs that name buildMenuRoot
[PRODMENU] Mission menus open
[PRODMENU] ODF root producer=<odf> root=b_amcmbt path=<resolved odf path>
[PRODMENU] Menu root b_amcmbt loaded: N buildable, M submenus, depth D
[PRODMENU] <odf> uses menu root b_amcmbt
[PRODMENU] Submenu cost hidden: call 0x004A5300 -> thunk, sprintf slot 0x00869498
```

The last line appears once per game process, when the first submenu is built.

On screen:

- submenu buttons show their label and **no** scrap cost;
- real build items still show their scrap (and pilot, when nonzero) cost;
- Back shows no cost (the engine never draws one for named modes);
- selecting a submenu opens it, Back returns one level, and a leaf builds the
  unit through the normal queue.

## 4. Regression checks

1. Deselect and reselect the producer; the page resets to the root.
2. Switch between producer types and between two producers of the same type.
3. Build at least two different leaves.
4. Select a producer whose ODF has no `buildMenuRoot`: its list is stock.
5. Leave the mission normally and check for shutdown errors.

## Failure interpretation

### No `ODF root` line

The producer ODF was not found, or the key is not in `[ProducerClass]`. Check
the ODF token the producer actually uses and where the mod keeps it.

### `Mission menus stay closed`

The ControlPanel Cleanup slot is not hooked, so the trees cannot be released
safely and the menus stay off. Check the patch status lines at startup.

### Submenus show "00"

Look for `Submenu cost site not found` or `is not call [IAT]`. The engine row
`ControlPanelModeScrapCostFormat` no longer matches this build; the menus still
work, with a "00" on submenu buttons.

### Menus do nothing with `Enabled=0`

Expected: that is the opt-out. Delete the file or set `Enabled=1`.
