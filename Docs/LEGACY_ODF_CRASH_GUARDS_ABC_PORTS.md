# Legacy ODF crash inputs: ABC/TRO instant-action ports (Sept 2026)

Findings from porting four TRO-era instant-action missions to
`addon/IAMP_*` format and debugging three successive crashes in
`abc_fort` (`IAMP_FortressOfFear`). Written so the crash classes can be
turned into OpenShim ODF guards. Nothing below is speculative unless it
says so.

Reference build: GOG `battlezone98redux.exe` 2.2.301
(`sha256=8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`
per openshim.log). Expected PDB sig `04FFCABE-6837-4AB9-9D42-E5B9DF4C7CBA`
(age 1); no matching PDB was available, so all RE below is
disassembly/Ghidra-decomp level, corroborated against `BZ1_Source`
(1.5) and `ODF_REFERENCE.md`.

Missions: `abc_fort` (Fortress of Fear), `abc_leap` (Quantum Leap),
`red_tide` (Red Tide), `warlords` (Warlords). Sources are BZ1 1.x/TRO
packages; two sibling folders (`Vertigo`, `veteran`) were already ported
and did not need these fixes.

## 1. Load quit: legacy `[GameObject]` header (FIXED, guardable)

Log (`BZLogger.txt`):

```
(Fighter) is loading (obj #0)
GameObject "svgekr.odf" uses unknown class label ""
Quiting Game because failed to load game files
```

19 ODFs across the four ports used the BZ1 1.0 header `[GameObject]`
instead of `[GameObjectClass]`. With that header the loader never parses
`classLabel`, so the class resolves to `""` and the mission quits at
load. `[GameObject]` is absent from `Edit/odfHeaderList.txt`.

Affected files: fort `svgech/svgecl/svgekr/svgekt/svgekw/svwalk/svwals/
svwasp`; leap `cvkmdo` plus the same `sv*` set; red_tide
`svrt02/svrt03/svrt07`. Fix was a header rename to `[GameObjectClass]`;
post-fix structure matches working ports (e.g.
`IAMP_BombTheBass/bossdude.odf`).

Guard proposal: report any `[GameObjectClass]` or `[OrdnanceClass]`
section with no `classLabel` key. That is the load-quit class. Note
`odf_compat.cpp` already remaps `gameobject`->`GameObjectClass` in
`kLegacyMap`, so shimmed loads tolerate the header; the guard still has
value for reporting and for unshimmed loads.

## 2. Sim AV in the weapon fire path (FIXED trigger, mechanism traced)

Second run: sim started, crashed ~61s in during Gecko combat.

```
eip=0x005E01F3  cmp eax,[edx+4Ch]   ; edx == 0
edx = [ecx+0xC4], ecx = this
```

The call immediately before is `call 0x00417C80`. Redux decomp
(`BZ1_Source/Redux/Raw .C/FUN_005dfcb0-005dfcb0.c:125`) reproduces the
sequence exactly:

```c
(iVar3 = FUN_00417c80(), *(int *)(*(int *)(local_2dc + 0xc4) + 0x4c) <= iVar3)
```

and `FUN_00417c80` (`FUN_00417c80-00417c80.c`) is:

```c
return *(uint *)(param_1 + 0x210) ^ 0x33333333;   /* Carrier curAmmo */
```

(the `^ 0x33333333` matches 1.5 `TargetingGun_Simulate`, which reads
`carrier->curAmmo ^ 0x33333333U`). So the fault is
`weapon->ordnanceClass(+0xC4)->ammoCost(+0x4C)` dereferenced with
`ordnanceClass == NULL`, where `+0xD0` is the owning Carrier.
`ODF_REFERENCE.md` documents the precondition (`WeaponClass` table):
"missing `ordName` -> ordnanceClass NULL; **no load-time guard**".

Two triggers were fixed for this:

- `abc_tag1.odf` (TAG Cannon, clone of stock `gtaggun.odf`) was missing
  `classLabel = "targeting"` in its `[OrdnanceClass]` section. Stock has
  it. The engine logged `Ordnance "abc_tag1.odf" uses unknown class
  label ""` and the first TAG shot (Geckos `svgekt`/`svgekw` mount
  `abc_tag1` on weapons 2/3/4) killed the sim. Fix: add the line.
- Typo'd building-impact refs: `abc_lzm2`/`abc_lzr2` (fort + leap)
  pointed `xplBuilding` at `xmlasbld`, leap `abc_lzg2` at `xmlagbld`.
  Neither exists anywhere (log: `Explosion "xmlasbld.odf" not found`).
  `xlasgnd`/`xlascar` in the same files are valid stock. All three were
  remapped to stock `xlasbld`. No file copies needed.

Guard proposals (both structural, both need a resolver against the
stock corpus + sibling folder files, case-insensitive):

- `[WeaponClass]` with no `ordName` key at all -> warn (ordnanceClass
  NULL is a verified downstream AV; see decomp reference above).
- `ordName` / `weaponNameN` / `xplGround|Vehicle|Building` naming a
  file that exists nowhere -> report (fire-time null). Skip `NULL` and
  empty `weaponNameN` (guarded slots per `ODF_REFERENCE.md`), but note
  the mask check below.

## 3. Heap corruption ~2 min into combat (UNRESOLVED)

Two post-fix runs died with heap failure, same mission phase (Gecko
combat), different endpoints:

- `c0000005` null read in `OgreMain!...operator delete`; the deleted
  object carries three vptrs `008A0790/008A074C/008A0768`, and the third
  table contains `00417C60/004178A0`, flanking the known Carrier site
  `00417C80` (openshim "Decoded Weapon Mask Carrier Bias Hook"). The
  deleted object is a **Carrier**. Partial stack:
  `... 0x22BB46 -> 0x22BC28 -> 0xDE9BC -> 0xDAE04 -> 0x19CEED ->
  0x1A37A5 -> 0x19CF56(Person::vftable writer, i.e. Person ctor path) ->
  ... -> operator delete`.
- `c0000374` (`RtlReportFatalFailure`) at the `call [0x00869B64]`
  (`PTR_addRenderable_00869B64` per the Ghidra inventory) in
  `LAB_006795C3+0x38`. `!heap -s`: `HEAP_FAILURE_MULTIPLE_ENTRIES_
  CORRUPTION`, valid blocks at `...8240`/`...0248`, error at
  `0x49639F88`, followed by a long zeroed run. Smells like an overrun
  or a wild memset, not a single bad free.

An unrelated same-day render-teardown crash (Ogre/D3D9 scene
destruction, `ProcessVisibleObjectHook` on stack) was also observed and
is explicitly out of scope here.

Needed next step: a PageHeap run to catch the corrupting write with a
clean stack (registry recipe in section 6). Static sweeps are
exhausted; see section 4.

## 4. Investigated and cleared (do NOT guard on these)

- `salvoCount = 50` in `abc_tag1` (stock's only value is 10 in
  `gtaggun`). 1.5 `TargetingGun_Simulate` keeps a single `leaderObj`
  and treats `salvoCount` as a plain counter (`salvoCount + -1`), so 50
  is not an array overrun. Reverted to the authored value at the
  mission owner's request; do not clamp.
- `weaponHard5` (`svgekr`, leap `cvkmdo`; stock max is `weaponHard4`
  across 403 refs). 1.5 `GameObjectClass` declares `weaponHard[5]` and
  `weaponClass[5]`; 1.5 `Carrier::Carrier` zeroes a 10-pointer weapon
  area; Redux `GetWeapon` (`slots[index]` at `+0x18+i*4`, mask at
  `+0x2C`) fits 5 slots exactly (`0x18+5*4 == 0x2C`). Structurally
  in-bounds; suspect only by association with the Carrier delete.
- `weaponMask` strings are binary numbers, bit N -> slot N+1
  (verified: `01001`=slots 1,4 on `svwals`; `00110`=slots 2,3;
  `01111`=slots 1-4; `00111`=slots 1-3). All four ports are coherent;
  no enabled-but-empty slot exists under this decoding.
- `[PortalClass]` (`sbport.odf`) and `[SmokeEffect]` (`smoke.odf`)
  are absent from `Edit/odfHeaderList.txt` but used by stock
  (`cbport.odf`, `smoke.odf`). The header list is outdated, not the
  ODFs.
- Beam values (`segmentRadius 0.1-0.3`, `segmentLength 1-3`) sit inside
  stock ranges. `xlasgnd`/`xlascar` are valid stock files.

## 5. Watch items (leap, untested in-game)

- `abc_bfg1.odf`: `ordnanceCount = 18`; stock max is 7 (`gmaggun`).
  `chargegunclass/ordnancecount` is already in `kGuardRules` (negative
  clamp only). Left at the authored value pending a leap test run;
  first suspect if leap crashes in combat.
- Same file line 23: `wpnReticle1 "gmaggun.0"` is missing `=`
  (authored typo, parser-tolerated). Left as-is per owner request.

## 6. Repro recipe (heap crashes)

```
:: elevated; one crashing run, then remove
reg add "HKLM\...\Image File Execution Options\battlezone98redux.exe" /v GlobalFlag /t REG_DWORD /d 0x02000000 /f
reg add "HKLM\...\Image File Execution Options\battlezone98redux.exe" /v PageHeapFlags /t REG_SZ /d 0x3 /f
:: play abc_fort ~2-3 min into Gecko combat; expect slower run, large dump
reg delete "HKLM\...\Image File Execution Options\battlezone98redux.exe" /f
```

Analyze with `!heap -p -a <addr>` / `!analyze -v` on the resulting
dump. Useful known addresses: fire-path AV `0x005E01F3`
(`FUN_005DFCB0` + line-125 pattern), Carrier bias `0x00417C80`,
addRenderable `call [0x00869B64]`, curAmmo obfuscation `^ 0x33333333`.

## 7. Benign log noise (not crash causes)

`AnimObj_Start ... has no animation at index N` (legacy geos),
`Couldn't find file "flyby1.wav"` (non-fatal), `GotoTask ... path=NULL`
(common), `unknown mapType 'NONE'` in unrelated `desktop.ini`/
`isdfmsff.ini`.

## 8. Port-format reference (what "same format" meant here)

Per-mission `addon/IAMP_*` folder: source files minus
`*.lnk/*.bat/*.txt/*.ial`; TRN gains `[Atlases] MaterialName =
el_detail_atlas` (stock Elysium atlas; CRLF); `.hg2` converted
unsmoothed (HeightmapGen `convert_legacy_hgt.py`); `.ini`
(`instant_action` + `BZ1 port, legacy, instant action`); `<mission>.des`
copied from `<mission>.otf` (veteran-batch pattern); 512px
`_preview.jpg` + 108x89 `.bmp` (WorldBuilder `map_preview.py`);
`CREDITS.txt` with author/version/source.
