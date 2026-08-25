# BMP Thumbnail Hard Crash - Root Cause and Repair

Date: 2026-08-24
Build: GOG `battlezone98redux.exe` 2.2.301 (5,425,152 bytes,
GUID `04ffcabe-6837-4ab9-9d42-e5b9df4c7cba`, age 1). Steam builds have matched
GOG after settling per `AGENTS.md`; addresses below were derived against the
GOG image only.

Evidence corpus:

- User-supplied full-memory dump: `C:\BZDumps\battlezone98redux.exe.30140.dmp`
  (PID 30140, crashed 2026-08-24 18:36 local).
- `logs\BZOgreLogfile.log` from the same session.
- Shipped-exe Ghidra corpus
  `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp` (31,947
  functions). The mismatched `battlezone98redux.pdb` was not used for any
  address (its GUID does not match the shipped exe).

## Reproduction

Not synthetically re-triggered end-to-end (the failing content is a user mod
thumbnail); root cause is proven from a real crash dump plus matching engine
log lines from the exact process:

```
18:36:50: FreeImage error: 'unknown bmp subtype with id 124' when loading format BMP
18:36:50: OGRE EXCEPTION(7:InternalErrorException): Error decoding image in
          FreeImageCodec::decode at D:\code\ogre\OgreMain\src\OgreFreeImageCodec.cpp (line 413)
```

Historical guidance ("24-bit BMP, avoid color-space information") matches:
subtype id 124 is `BITMAPV5HEADER` (`bV5Size == 124`), produced when an author
writes color-space metadata. The shipped OgreMain bundles **FreeImage 3.15.3**
(log line: `FreeImage version: 3.15.3`), whose BMP loader rejects that DIB
header, and `Ogre::FreeImageCodec::decode` converts the failure into an Ogre
exception.

## Debugger result

Dump exception record: unhandled `0xE06D7363` (Microsoft C++ exception) ->
`msvcr120!terminate` -> `abort` -> `int 29h` (`FAST_FAIL_FATAL_APP_EXIT`).
Stack (module+offset, exe base 0x400000):

```
KERNELBASE!RaiseException
msvcr120!CxxThrowException
OgreMain+0x46db8e                       ; throw site (FreeImageCodec::decode)
...
battlezone98redux+0x3D429E              ; return into FUN_007D3FF0
  caller chain: FUN_007D2870 / FUN_007CA970 / FUN_007D26C0 ...
  ... cUI_Multiplayer_Create::GameSettingButtonClicked (PDB naming oracle)
user32 dispatch <- WM_LBUTTONUP         ; menu click
```

The click ran the multiplayer create screen; rendering the selected entry's
thumbnail threw, no handler existed anywhere up the UI stack, and the CRT
terminated the process. A second spontaneous occurrence with identical
signature (`unhandled code=0xE06D7363`, 2026-08-22 21:46:50) exists in
`openshim_crash.log`, confirming this is a recurring user-facing failure.

## Native function

`FUN_007D3FF0` - shared thumbnail-material builder used by every map/mod list
screen (callers `FUN_007C2E80`, `FUN_007C2F10`, `FUN_007C3900`,
`FUN_007C3990`, `FUN_007D2870`). ABI: `__thiscall`, two stack arguments -
caller-provided 8-byte `SharedPtr<Material>` slot at `[ebp+8]` (also returned
in eax via `mov eax,[ebp+8]`) and the texture/material name at `[ebp+0xC]`.
Body:

1. existence probe through MaterialManager vtable `+0x54`;
2. clone of the stock `"UI"` material (SSSO string object at `DAT_0087908C`);
3. `TextureUnitState::setTextureName(name, TEX_TYPE_2D)` (import);
4. virtual `Material::load` call at `0x007D429C` (vtable `+0x38`, arg 0) -
   synchronously decodes the image through FreeImage and throws.

## Root cause

A thumbnail BMP the bundled FreeImage cannot decode (observed:
BITMAPV5HEADER; generally: any variant outside its supported set) makes
`Material::load` throw `InternalErrorException`. Nothing between the throw and
the UI message loop catches C++ exceptions, so one bad image file kills the
whole game from a routine menu interaction. This is a stock defect: the game
has no decode-failure path for thumbnails at all.

## Patch

OpenShim entry detour on `0x007D3FF0` (`src/patches/bzr_hooks.cpp`):

- 5-byte `jmp` over prologue bytes `55 8B EC 6A FF`
  (`push ebp; mov ebp,esp; push -1`), validated with
  `ExpectedBytesMatchAt` before patching; trampoline = stolen bytes + jump
  back to `0x007D3FF5`.
- Naked stub forwards `(this, outSlot, name)` unchanged to a C++ helper that
  invokes the trampoline inside `__try`.
- The SEH filter returns `EXCEPTION_EXECUTE_HANDLER` only for exception code
  `0xE06D7363` and only while the guard is enabled; every other fault
  (notably access violations) keeps default behaviour so memory corruption
  stays loud.
- On a swallowed decode failure the helper clears the caller's out slot to a
  null `SharedPtr` representation `{NULL, NULL}` and returns the slot pointer,
  exactly mirroring the stock return contract. Downstream
  `SharedPtr<Material>::operator=` (`0x00449910`) handles a null source
  without dereferencing, leaving the entry with no thumbnail material - the
  same visible outcome as a missing image.
- Bounded `[BMPFIX]` logging identifies which guard fired (budget 8 lines per
  session); opt-out `OPENSHIM_DISABLE_BMP_GUARD` / `BZR_DISABLE_BMP_GUARD`.

Why this behaviour is correct: stock has two outcomes today - "file missing"
(blank entry, no crash) and "file present but undecodable" (process exit).
The guard moves the second case onto the first case's path without
reinterpreting or resaving any image data.

## Validation

- Release|Win32 build clean (only pre-existing C4505 warnings).
- Live install verified: `[BMPFIX] Installed thumbnail decode guard
  site=0x007D3FF0 trampoline=...` in `openshim.log`; multiple gameplay and
  mission-load sessions since deployment show zero `[BMPFIX]` rejection lines
  (guard silent on valid content).
- Deterministic fault-path exercise inside a live menu still requires
  clicking a map/mod whose folder contains a V5-header BMP; recipe below.

Remaining uncertainty / follow-up experiments:

1. Full-menu repro recipe: place a 24-bit BI_RGB BMP saved with
   BITMAPV5HEADER as `<map folder>\<mapname>.bmp` thumbnail, open the
   multiplayer create screen, select the map. Expected pre-patch: process
   exit with `unhandled E06D7363` in `openshim_crash.log`; post-patch:
   `[BMPFIX] Rejected undecodable thumbnail image ...` and the entry renders
   blank.
2. If a future report shows a non-C++ fault escaping through
   `0x007D3FF0`, revisit the filter scope.
