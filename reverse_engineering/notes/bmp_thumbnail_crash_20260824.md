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
swallow path now re-runs the guarded stock body under the substitute name
`"UI"`:

- with `name = "UI"` the stock exists-check finds the parsed base material and
  takes FUN_007D3FF0's own already-exists branch, which returns that loaded
  material without applying any texture and without any decode step - it
  cannot throw, so every consumer receives a valid pointer through the normal
  contract;
- the slot therefore holds exactly the reference semantics the caller expects;
  visually the entry shows the plain UI look instead of a thumbnail;
- if the retry itself ever throws the same C++ exception class, the guard
  degrades to the original cleared-slot behaviour and logs it; a hardware
  fault inside the retry is deliberately not converted - it propagates and
  crashes loudly (see the narrow-scope invariant above).

An intermediate attempt bound the exported
`Ogre::MaterialManager::getByName` directly; live testing showed it falling
back (`material cleared to blank`). Root cause of that failure: the name
parameter of FUN_007D3FF0 is a `const char*` (its string ctor helper at
`0x00416EF0` is the char* overload), and the "UI" constant at `0x0087908C`
is raw character data in a C-string pool - not a std::string object - so the
exported getByName received an invalid String reference. The retry approach
avoids cross-ABI string construction entirely.

The half-created clone left registered under the real name by the aborted
attempt is removed again on the swallow path (exported
`ResourceManager::remove` on the `MaterialManager` singleton, same mechanism
proven live by the material collision listener in `src/patches/trampolines.cpp`;
no-op for absent names, and "UI" itself is never removed). Earlier reasoning
treated that leftover as a stability feature - repeat selections take
FUN_007D3FF0's exists-branch and return it without loading. Review of that
contract found it unsound: the exists-branch hands consumers an *unloaded*
material whose texture unit still names the undecodable image (untextured
rendering instead of the UI substitute), and any unrelated future load() of
that material would rethrow the decode failure outside this guard. Removing
the entry makes every repeat selection re-run the fully guarded build path and
deterministically receive the UI substitute again.

### Repeat-selection contract (guard invariant)

After any swallowed decode failure, for every subsequent selection of the same
entry:

1. no crash and no terminate (the only handled exception class stays
   `0xE06D7363`; AVs/corruption remain loud);
2. the caller receives either the loaded stock "UI" material or a cleared
   slot - never the half-loaded leftover;
3. other thumbnails are unaffected (the removal targets exactly one manager
   entry by name).

Manual validation recipe driving all six required transitions: place the
malformed BMP as `<map/campaign folder>\<name>.bmp`, then (1) open the map or
campaign list, (2) select the malformed entry, (3) navigate away, (4) reselect
it, (5) close and reopen the list, (6) reselect it again. Expected at every
step: `[BMPFIX] Rejected undecodable thumbnail image; substituted stock UI
material ...` (bounded to 8 lines/session) and the plain UI look; no second
decode attempt may ever escape the guard.

## Validation

- Release|Win32 build clean (only pre-existing C4505 warnings).
- Live install verified: `[BMPFIX] Installed thumbnail decode guard
  site=0x007D3FF0 trampoline=... uiFallback=ready` in `openshim.log`; multiple gameplay and
  mission-load sessions since deployment show zero `[BMPFIX]` rejection lines
  on valid content (guard silent during ordinary play).
- Real-world fault path exercised twice by the user against a V5-header BMP
  campaign thumbnail: first run proved the exception interception (clean
  `[BMPFIX]` swallow, no terminate), exposed the null-material consumer gap,
  and drove the plan B revision; the second run exposed the invalid-String
  pitfall in the first substitution attempt (log line
  `material cleared to blank`) and drove the current retry-based mechanism.
  Retest with the retry deployed is pending user confirmation.
- Deterministic fault-path recipe: place a 24-bit BI_RGB BMP saved with
  BITMAPV5HEADER as `<map/campaign folder>\<name>.bmp` thumbnail, open the
  campaign/map list that shows it. Expected pre-patch: process exit with
  `unhandled E06D7363`; post-patch: `[BMPFIX] Rejected undecodable thumbnail
  image; substituted stock UI material ...` and the entry renders with the
  plain UI material.

Remaining uncertainty / follow-up experiments:

1. Confirm the campaign-screen click survives with the retry substitution
   active.
2. If any consumer rejects the substituted "UI" material in a new way, the
   `[BMPFIX]` log line plus the dump will identify it directly.
