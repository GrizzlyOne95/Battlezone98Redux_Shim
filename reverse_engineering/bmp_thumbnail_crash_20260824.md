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
- On a swallowed decode failure the helper fills the caller's out slot with
  the stock `"UI"` base material and returns the slot pointer, exactly
  mirroring the stock return contract.
- Bounded `[BMPFIX]` logging identifies which guard fired (budget 8 lines per
  session); opt-out `OPENSHIM_DISABLE_BMP_GUARD` / `BZR_DISABLE_BMP_GUARD`.

Why this behaviour is correct: stock has two outcomes today - "file missing"
(blank entry, no crash) and "file present but undecodable" (process exit).
The guard moves the second case onto a safe blank-thumbnail outcome without
reinterpreting or resaving any image data.

### Field revision (plan B): substitute the "UI" material, do not clear

First live validation (user clicked Rise of the Black Dogs under
Single Player > Custom Campaign; dump `battlezone98redux.exe.28692.dmp`)
proved the initial null-clear fallback insufficient for one caller:

- `[BMPFIX] Rejected undecodable thumbnail image ...` fired as designed, then
- unhandled AV at `0x007D2CA6` inside `FUN_007D2B70` (`read=0x00000000`,
  ecx=0): that consumer fetches the raw material pointer from the slot via
  `0x00416400` and dereferences its vtable without a null check while
  building the preview ManualObject.

So at least one consumer requires a *valid* material, not a cleared slot. The
swallow path now substitutes the stock `"UI"` base material - the exact
object FUN_007D3FF0 clones from on every successful thumbnail:

- `Ogre::MaterialManager::getSingleton` and
  `Ogre::MaterialManager::getByName(const String&, const String&)` are real
  OgreMain exports (mangled names bound via GetProcAddress at install;
  startup log reports `uiFallback=ready|unavailable`);
- the name argument is the game's own std::string object at `0x0087908C`
  ("UI") - the identical object stock passes to getByName - so no
  cross-CRT string construction is attempted;
- the group argument is Ogre's own `DEFAULT_RESOURCE_GROUP_NAME` /
  `AUTODETECT_RESOURCE_GROUP_NAME` data exports;
- getByName returns a fresh owning reference, which is precisely the
  reference semantics the caller expects the slot to hold (caller copies,
  then releases the temporary);
- if the exports are unavailable or lookup fails, the guard degrades to the
  original cleared-slot behaviour and logs it.

The half-created clone left registered under the real name by the aborted
attempt also makes repeat selections stable: subsequent calls take FUN_007D3FF0's
exists-branch, which returns the material without touching textures or loading.

## Validation

- Release|Win32 build clean (only pre-existing C4505 warnings).
- Live install verified: `[BMPFIX] Installed thumbnail decode guard
  site=0x007D3FF0 trampoline=... uiFallback=ready` in `openshim.log`; multiple gameplay and
  mission-load sessions since deployment show zero `[BMPFIX]` rejection lines
  on valid content (guard silent during ordinary play).
- Real-world fault path exercised twice by the user against a V5-header BMP
  campaign thumbnail: first run proved the exception interception (clean
  `[BMPFIX]` swallow, no terminate), exposed the null-material consumer gap,
  and drove the plan B revision above; retest with `uiFallback=ready`
  deployed is pending user confirmation.
- Deterministic fault-path recipe: place a 24-bit BI_RGB BMP saved with
  BITMAPV5HEADER as `<map/campaign folder>\<name>.bmp` thumbnail, open the
  campaign/map list that shows it. Expected pre-patch: process exit with
  `unhandled E06D7363`; post-patch: `[BMPFIX] Rejected undecodable thumbnail
  image; substituted stock UI material ...` and the entry renders with the
  plain UI material.

Remaining uncertainty / follow-up experiments:

1. Confirm the campaign-screen click survives with the substitution active.
2. If any consumer rejects the substituted "UI" material in a new way, the
   `[BMPFIX]` log line plus the dump will identify it directly.
