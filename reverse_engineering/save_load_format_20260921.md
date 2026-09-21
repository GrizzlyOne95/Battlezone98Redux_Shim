# Game Save/Load Format — Engine Reference (1.5 vs Redux) + OpenShim/EXU Behavior

Date: 2026-09-21
Scope: exact `.sav` write/read structure, value list, Redux validation diffs,
OpenShim vs EXU autosave mechanics. Repository-specific behavior is a snapshot
of the 2026-09-21 code state; the recovered engine format is the durable reference.

## Sources and trust

- `BZ1_Source/1.5/` — Ghidra decomp of `bzone.exe 1.5.2.27` with exact-match
  `bzint.pdb` (`manifest.json`). Behavioral source of truth for legacy layout.
  Key files: `functions/0054/0054b217_SaveGame.c`,
  `functions/0054/0054ad8c_LoadGame.c`,
  `functions/0054/0054a639_SaveShellGame.c`,
  `functions/0054/0054a708_LoadShellGame.c`,
  `functions/0054/0054b42d_save_bzone_game.c`,
  `functions/0054/0054b55d_PromptSaveGame.c`,
  `functions/0054/0054b60b_AutoSaveGame.c`,
  `functions/0054/0054b689_PromptSaveMission.c`,
  `functions/0054/0054a984_GetSaveDesc.c`,
  `functions/0052/00523c79_SaveZoneFiles.c`,
  `functions/0049/00497c77_GameObject_SaveAll.c`,
  `functions/0049/0049598b_GameObject_LoadAll.c`,
  `functions/0049/00495c05_WriteObject.c`,
  `functions/004b/004b1ec7_Team_SaveAll.c`,
  `functions/0040/00401aee_AiMission_SaveMission.c`,
  `functions/0045/0045e9e9_SaveScriptUtils.c`,
  `out_*` (`00547a4f`-`0054822a`), `in_*` (`00548450`-`00548f8b`),
  `00548346_in_open.c`, `0054908d_out_ptr.c`, `005490d4_in_sptr.c`.
- `BZ1_Source/Redux/Raw .C` — best-effort GOG Redux decomp, mismatched beta PDB.
  `FUN_<rva>` names only; PDB names NOT trusted. Validated by behavior/strings.
  Key: `FUN_004fd190-004fd190.c` (SaveGame), `FUN_004fc490-004fc490.c` (LoadGame,
  826 lines), `FUN_004fd7e0-004fd7e0.c` (SaveShellGame),
  `FUN_004fd900-004fd900.c` (LoadShellGame), `FUN_004fdc80-004fdc80.c`
  (save_bzone_game), `FUN_004fbe90-004fbe90.c` (PromptSaveMission),
  `FUN_004fdab0-004fdab0.c` (auto.sav helper), `FUN_004fdc20-004fdc20.c`
  (auto2.sav helper), `FUN_004fdfe0-004fdfe0.c` (header preview),
  `FUN_004fd090-004fd090.c` (PostLoadGame), `FUN_00786c80-00786c80.c`
  (SaveZoneFiles), `FUN_005e0da0-005e0da0.c` (Team Save),
  `FUN_005e0bd0-005e0bd0.c` (Team Load), `FUN_004dd1c0-004dd1c0.c`
  (GameObject SaveAll), `FUN_004dc710-004dc710.c` (WriteObject),
  `FUN_004fbc80-004fbc80.c` (legacy side-name map),
  `FUN_004fc020-004fc020.c` (LoadDefaultGame candidate),
  `FUN_004fbd50-004fbd50.c` (bookmark save).
- `BZR-OpenShim`: `src/patches/autosave.cpp`, `src/patches/bzr_hooks.cpp`,
  `src/patches/file_io_hooks.cpp`, `docs/autosave.md`,
  `docs/BZN_SAVE_SOURCE.md:71-80`, `reverse_engineering/native_save_notes.md`,
  `reverse_engineering/repo_corpora/bzr_gog_best_effort/` (functions.csv,
  binary_strings/ascii_strings.csv).
- `ExtraUtilities`: `src/Util/OS.cpp`, `src/Util/OS.h:30`,
  `src/luaexport.cpp:835`, `Definitions/ExtraUtils.lua:2057-2068`,
  `src/Game/ContinuityApi.h`, `src/Game/game_state.cpp`.

Confidence: header order/tags/sizes — high (both builds, string-evidence backed).
Body order/count — high (7-call chain both builds). Per-class GameObject
subclass fields — high for base + representative wrappers, not exhaustively
re-verified per vehicle. Redux shell break + version stamp — high (direct decomp
reads). Redux zone-gating inversion — medium (decomp observation, see §8).
`FUN_004fdc80` runType arg — low (decomp drops second arg; flagged below).

## 1. Entry points

1.5 (exact PDB names):

```text
int SaveGame(char *filename, int runType)        0x0054b217
int LoadGame(char *path)                         0x0054ad8c
int SaveShellGame(_iobuf*, int runType)          0x0054a639
int LoadShellGame(_iobuf*, int runType)          0x0054a708
int save_bzone_game(int runType,int slot,char*)  0x0054b42d
int PromptSaveGame(int runType)                  0x0054b55d
int AutoSaveGame(void)                           0x0054b60b
int PromptSaveMission(void)                      0x0054b689
int GetSaveDesc(int slot, ShellButton*)          0x0054a984
int SaveZoneFiles(char *savPath)                 0x00523c79
int PostLoadGame(void)                           0x0054b78b
```

Redux (behavioral mapping, PDB advisory only):

```text
SaveGame            0x004FD190  bool FUN_004fd190(char*, runType)
LoadGame            0x004FC490  FUN_004fc490(char*, int suppressFlag) — 2 args, not 1
SaveShellGame       0x004FD7E0  FUN_004fd7e0
LoadShellGame       0x004FD900  FUN_004fd900
save_bzone_game     0x004FDC80  FUN_004fdc80(slot, desc) — decomp shows 1 call arg lost
PromptSaveMission   0x004FBE90  FUN_004fbe90 (missionSave=1, dialog, SaveGame(path,0))
_load_bzone_game    0x004FDFE0  FUN_004fdfe0(path, outName, outLen) — header preview only
PostLoadGame        0x004FD090  FUN_004fd090 (0x5350574e/0x4745495a check intact)
SaveZoneFiles       0x00786C80  FUN_00786c80
auto.sav helper     0x004FDAB0  FUN_004fdab0
auto2.sav helper    0x004FDC20  FUN_004fdc20
```

Native signature shared by OpenShim/EXU scanners (both repos, identical):

```text
55 8B EC 81 EC 94 00 00 00 C6 45 FF 01 E8 ??*4
89 85 78 FF FF FF 68 ??*4 E8 ??*4 83 C4 04
0F B6 05 ??*4 85 C0 0F 84 ??*4 6A 2E
```

## 2. Serialization primitives

17 `out` / 17 `in` overloads. `binarySave:bool` selects encoding per file.
`missionSave:bool` selects game-save vs mission-save (field inclusion).
`BinarySave:int` config selects `binarySave = BinarySave != 0` before each
`SaveGame`, restored to `false` after. Cmdline `asciisave` → 0, `binarysave` → 1.
Stock saves are text.

- Binary: `out_data(type,size)` = `fwrite(type,4)+fwrite(bytes,size)`;
  `in_data` validates `type + u16 size`.
- Text: `tag = value\r\n` or `tag [count] =\r\n` + one value/line; blobs as
  `%02x` hex; bools `true/false`; `%d/%ld/%lx/%g/%hd/%hu/%c/%.8s/%p`.
  Section markers (`[GameObject]`, `[AOIs]`, `[AiPaths]`, `[AiTasks]`, `[AOI]`,
  `[AiPath]`, `[AiMission]`) must match byte-for-byte.
- Type codes: 0 blob, 1 bool, 2 uchar/char, 3 short/ushort, 4 int/long/ulong,
  5 float, 6 double, 7 long64 (PrjID/classnames), 8 ptr, 9 VECTOR_3D,
  10 VECTOR_2D, 0xB MAT_3D. EULER is composite (mass/mass_inv/v_mag/v/omega/Accel).
- `out_ptr` (type 8, `%p` in text) + `in_ptr` (enqueues `Addr` fixup) /
  `in_sptr` (raw, no fixup). Pointer swizzle resolved by
  `Addr::PartialCleanup()` / `Addr::Cleanup()` + `OldNew` list on load.

## 3. Pre-step: SaveZoneFiles (sidecars, NOT in .sav)

1.5 `SaveGame:22-57`: only if `runType==0`. `.TRN` ext → terrain-only branch
(copy basename, `SaveZoneFiles`, return without `.sav`). Else if
`zoneDataChanged==0` skip to `.sav`; else `SaveZoneFiles` then continue.

1.5 sidecars (`SaveZoneFiles`): `missionName` bytes → `<base>.TRN`
(`0x4E52542E`); `ZoneFileMap` → `<base>.GHT` (`0x5447482E`); `MZoneFileMap` →
`<base>.MAT` (`0x54414D2E`). `CreateFileA/WriteFile`. Clears
`zoneDataChanged`. Set by `EditTerrain::PushUndoTile/Grid`.

Redux diffs (validated in `FUN_00786c80`): `.trn` lowercase (`0x6e72742e`),
`.hg2` (`0x3267682e`, replaces `.GHT`), `.mat` lowercase (`0x74616d2e`,
replaces `.MAT`); `fopen/fwrite` + `Can't create/open/write file`; both `\`
and `/` separators; empty-path default `sprintf("%s%s%s",...)` vs `Addon\%s`;
refcount bump on entry. Zone gating observed as `missionSave!=0 &&
(isTRN || dirty)` rather than 1.5 `runType==0` — treat as decomp observation,
not proven design (see §8).

## 4. .sav header — exact order

Write 1.5 `0054b217:62-80` ≡ Redux `FUN_004fd190:219-396`.

| # | Field | Size | Tag | Condition |
|---|-------|------|-----|-----------|
| 1 | `version` | 4 | `version` | always. Written `0x415` (1045) in 1.5, `0x7E0` (2016) in Redux |
| 2 | `binarySave` | 1 | `binarySave` | always written; read only if `version>0x3FE` (1022) |
| 3 | `msn_filename` | 16 (`0x10`) | `msn_filename` | always written; read only if `version>0x3FF` (1023) |
| 4 | `seq_count` | 4 | `seq_count` | always (`GetSeqCount()` / `FUN_004d9c80()`) |
| 5 | `missionSave` | 1 | `missionSave` | always written; `version<0x3F8` (1016) forces `false` on read |
| 6 | `runType` | 4 | `runType` | only if `!missionSave`, `version>=0x407` (1031) |
| 7 | `saveGameDesc` | 256 (`0x100`) | `saveGameDesc` | only if `!missionSave`, `version>0x409` (1033) |
| 8 | shell block | 24 (1.5) / 58 (Redux new) | see §5 | only if `!missionSave`, `version>=0x407` |
| 9 | `TerrainName` | 100 decimal | `TerrainName` | always written; read only if `version>0x3EE` (1006) |
| 10 | `start_time` | 4 | `start_time` | only if `!missionSave`, `version>0x3EA` (1002); `(float)Get_Time()` bits |

`runType`: 0 = plain snapshot, 1 = campaign-progression. `AutoSaveGame`
passes 1; `PromptSaveMission` passes 0; `SaveDlgProc nType=param_4` flows
through `save_bzone_game(nType,slot,desc)`; `LoadDlgProc nType=(param_4!=0xB)`.
`SaveShellGame`: if `nMissionStatus==2 && runType==1 && nOldMissionMode==0`,
increment the current-side mission index. `LoadShellGame`: if `runType==1`,
`SetRunning(2)`.

Load fail gate: `version<0x407 && !missionSave && version<=0x40B` (1035) →
`Old Saved Games are not backwards compatible`, return 0. Mission-saves bypass.

## 5. Shell block

1.5 (24 bytes): `nUsaMissionIndex, nUssrMissionIndex, nTrnMissionIndex,
nPlayerSide(int), nMissionStatus` + `nOldMissionMode` (only `version>0x40A`).

Redux (58 bytes on new saves): `nPlayerSide` 50 (`0x32`) string (from
`FUN_0041f870`) + `nMissionStatus` 4 + `nOldMissionMode` 4. No
`nUsa/Ussr/Trn` counters on write. Load (`FUN_004fd900`) handles both:
`version<0x7DF` (2015) → legacy `runType 4 + FUN_004fbc80(runType)` mapping
1..5 to campaign strings (`DAT_0094ffe0/fea8/fef8/fe78/fe90`, else
`DAT_008a1ad8`); `>=0x7DF` → 50-byte string path. Then `nMissionStatus`,
plus `nOldMissionMode` if `version>0x40A` (gate unchanged).

## 6. Body — exact order (both builds, 7 calls)

```text
GameObject::SaveAll()   Redux FUN_004dd1c0
Team::SaveAll()         Redux FUN_005e0da0
AiMission::SaveMission()=RtimeClass::Save(current)
AOI::SaveAll()
AiPath::SaveAll()
if(!missionSave) AiTask::SaveAll()   Redux FUN_00461d90 / load FUN_00461d10
SaveScriptUtils()       Redux FUN_005c7b90 / load FUN_005c7510
```

Load mirrors with terrain rebuild in between (`Close_Terrain_Texture_Info →
TerrainSaveName → CreateTerrainTextureNames → Init_Zone_Manager →
Terrain_Create → Set_Terrain_Texture_Info → DisplayInterface_LoadColors →
InitPathing`), then `LoadAll` chain, `Addr::PartialCleanup()`,
`AiTask::LoadAll + LoadScriptUtils`, `Addr::Cleanup()`,
`SetSeqCount(saved)`, `Set_Game_Start_Time(start)+Pause()` if not net,
`PostLoadMission / PostLoadAll / Team::PostLoadAll / AiTask::PostLoadAll /
PostLoadScriptUtils`.

### GameObject

`SaveAll`: `count 4 "size"` (`objectList.size − DontSave`), then
`WriteObject(userObject)` first, then each non-user passing `DontSave`.
Per object (`WriteObject`): `[GameObject]`, `PrjID` 8, `seqno` 2 (ushort),
`pos` 12 (VECTOR_3D from transform.posit), `team` 4, `label` 40 (`0x28`,
synth `%.8s%d_%s`), `isUser` 4, `out_ptr obj_addr` 4, `transform` MAT_3D 64
(`0x40`), then virtual `Save`. Load inverts; `obj_addr` is raw `in` if
`version<0x3EA` else `in_sptr`; old transform = Identity+pos; then
`Find→Build + OldNew`, virtual `Load`, `isUser→userObject+Set_User_Entity`,
orthogonalize + `UpdatePosition`.

Base `GameObject::Save` fields: `illumination` 4, `pos` 12, `euler` 72
(`0x48`), `seqNo` 4, `name` 32 (`0x20`, only `version>0x406`), `isObjective` 1,
`isSelected` 1, `isVisible` 4, `seen` 4, if `!missionSave`: 6×4 combat counters,
`healthRatio` 4f, `curHealth` 4, `maxHealth` 4, `ammoRatio` 4,
`curAmmo^0x33333333` 4, `maxAmmo^0x33333333` 4, `AiCmdInfo cur+next` (each
20 = priority/what/who/where/param) + `out_ptr aiProcess` (else single Cmd +
`aiProcess!=0` 1), `isCargo` 1 (`>0x3EF`), `independence` 4 + `curPilot` 8
(`>0x3F8`; 1-byte flag form `<0x406`), `perceivedTeam` 4 (`>0x407`),
if `!missionSave && >=0x409`: 5× weapon pair 8 + `enabled` 4 + `selected` 4.
Subclasses (`Building/Craft/HoverCraft/Walker/PowerUp/Producer/Recycler/…`)
prepend own fields then chain base.

### Team

No marker/count on disk. Per team 20 bytes: `curScrap^0x33333333` 4,
`maxScrap` 4, `curPilot` 4, `maxPilot` 4, `dwAllies` 4. Save loops 16 while
`!missionSave`. Load: `!missionSave && version>0x400`, count 8
(`0x401–0x40F`) or 16 (`>0x40F`); Redux load gate reads `<0x401/<0x410`,
logically identical. Redux XOR hidden in `FUN_005e10b0/005e10d0` pair.

### AiMission / Rtime / AOI / AiPath / AiTask / ScriptUtils

- Rtime envelope: `classname` 40 + `out_ptr sObject` 4 + virtual Save/Load.
  `AiMission` object (`!missionSave` only): `[AiMission]`, `count` 4, Rtime per
  process, `done` 1, `shutdownTime` 4, `failed` 1, `resultName` 14.
  `AiProcess` base: `out_ptr fMission/fOwner` + `exited` 4.
- AOI: `[AOIs]` + `count` 4; per AOI `[AOI]`, `out_ptr this` 4, `team` 4,
  `interesting` 1, `inside` 1, `value` 4, `force` 4 (load swizzles into `path`).
- AiPath: `[AiPaths]` + `count` 4; per path `[AiPath]`, `old_ptr` 4,
  `label_len` 4 + label, `pointCount` 4 + `points` 8 each (VECTOR_2D),
  `pathType` 4 (`ONE_WAY` if `version<0x3F6`).
- AiTask: `[AiTasks]` + `count` 4 + Rtime per task. Base Save/Load = 0 bytes.
- ScriptUtils (`!missionSave` else 0 bytes): audio mgr (`count` 4 min(n,10) +
  per-msg `seqNo` 4 + `msg` 14 + `lastMsg` 16), active-AIP `count` 4 + per-slot
  `slot` 4 + `name` 14, `difficultySetting` 4, `cameraReady` 1,
  `cameraCallCount` 4, `quakeMag` 4 (skip `<=0x40C`; legacy single-AIP 14B form
  `<0x411`; audio skipped `<=0x3FF`), `CockpitTimer` (4×4+3×1), `InfoDisplay`
  (`objectiveCount` 4 + 14+4 each + `objectiveLast` 4), `ControlPanel`
  (`groupNum` 40 + `groupList` 3600).

## 7. Load algorithm (full saves, `param_2==0` in Redux)

1. Reset `dwLocalIDCounter=1`. Derive `TerrainName`/`msn_filename` from path;
   `.TRN` or `NobodyHome/DAT_0091836c` → `LoadDefaultGame` fallback.
2. Whole-file `fread` → `in_open`. `in version`; version gates (§4) for
   `binarySave/msn_filename/seq/missionSave/runType/saveGameDesc/shell`.
3. Redux-only: reject `0x7DC/0x7DD`; reject `>=0x7E1` (future guard).
   Reject `!missionSave && version<0x40C` (1036) for game-saves.
4. `in TerrainName` (`>0x3EE`), terrain rebuild, `in start_time`
   (`>0x3EA && !missionSave`).
5. `LoadAll` chain + `PartialCleanup` + `AiTask::LoadAll + LoadScriptUtils` +
   `Cleanup` + `SetSeqCount` + `Set_Game_Start_Time/Pause` (SP) + `PostLoad*`.
6. `GetSaveDesc`/preview path reads header only through `saveGameDesc`
   (`version>0x409` required, else `Old version save game` label).

## 8. Redux validation diffs (vs 1.5)

1. **Stamp `0x7E0` vs `0x415`.** Redux writes 2016; 1.5 writes 1045.
   Redux files do NOT load in 1.5 (no upper bound → parses new 58-byte shell
   as old 24-byte → misalign).
2. **Shell break at `0x7DF`.** New = 50-byte side string; old = runType +
   index map. Loader handles both; saver emits only new.
3. **Load guards added.** Reject `0x7DC/0x7DD` and `>=0x7E1`. 1.5 has neither.
   Legacy `0x3xx` gates otherwise intact.
4. **LoadGame takes 2 args.** `(path, suppressFlag)`: nonzero = header-only,
   warnings suppressed. 1.5 took path only. Preview helper `0x004FDFE0`
   is header-only by design.
5. **Sidecars renamed.** `.TRN→.trn`, `.GHT→.hg2`, `.MAT→.mat`; `fopen/fwrite`
   vs Win32 API; `/` separators accepted.
6. **Zone gating observed different.** Redux SaveGame gates zone on
   `missionSave!=0`; 1.5 gated on `runType==0`. Slot saves (`missionSave=0`)
   therefore skip zone in Redux; mission saves do it. Medium confidence —
   decomp control-flow reading, needs live-save test to promote.
7. **Decomp limitation.** `FUN_004fdc80` (save_bzone_game) drops the runType
   arg in decomp (`FUN_004fd190(path)` with one visible arg). Do not cite
   Redux slot-saves as single-arg; native signature keeps `(char*,int)`.
8. **Unchanged.** Header order/tags/sizes, 7-call body order, Team/GameObject
   envelopes, `PostLoadGame` sentinels, `saveGameDesc`/`binarySave`/`msn_filename`
   globals and tags, `auto.sav`+`auto2.sav` helpers, slot range 1-10.

## 9. OpenShim vs EXU autosave — different things

OpenShim (`src/patches/autosave.cpp`, `docs/autosave.md`): automatic
engine-level service. Main-thread vtable hook, `SaveGame(path,0)` with
`saveType` hardcoded 0, timer 10s initial / 120s interval / 15s retry
(`[AutoSave]` INI), SP-only gate (no net, no pause/options/save/load/restart
shell; editMode diagnostic only), `Save\auto.sav` + `auto.label.txt` +
`AutoSaveBackups\auto.pre_autosave.sav`, external-mtime deferral
(`RespectExternalAutoSave`), SEH fault budget 3/process, injected load button
(`bzr_hooks.cpp:42138`, queued path `0x00945708/0x00915540` + `SetShellState(8)`).

EXU (`src/Util/OS.cpp:676`, `Definitions/ExtraUtils.lua:2057`): no autosave
service (zero `AutoSave` hits under `ExtraUtilities/src`). Only on-demand
`exu.SaveGame(slotOrPath,saveType|description,description)` for mission Lua to
call on its own timer. Same native `SaveGame` signature plus Redux-only
`SaveShellGame(slot,desc)` fast path; slot 1-10 → `Save\game{slot}.sav` else
arbitrary path; description rewritten inside the `.sav` (`saveGameDesc` line,
hex-aware) rather than sidecar label; returns `boolean,pathOrError`.
`ContinuityApi.h:1070` explicitly `nativeSaveParsing=false` — continuity
snapshots are Lua-captured, not `.sav` parsing.

Legacy third path (historical): CR `AutoSave.lua` synthesized files in script
+ mission `Save()` callback only, not the engine serializer
(`native_save_notes.md:17`). OpenShim schedule matches its timing but replaces
it engine-side; coexistence is via timestamp deferral.

## 10. Filenames / slots

Stock: `save\game1.sav`…`save\game10.sav` (`save_bzone_game`/`GetSaveDesc`),
`save\autosave.sav` (`AutoSaveGame`). OpenShim: `Save\auto.sav` (+`auto2.sav`
accepted on load), `.label.txt`, backups. EXU slots 1-10 → same
`Save\game{slot}.sav` shape under exe dir, else caller path.
