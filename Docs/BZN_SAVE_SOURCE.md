# World Builder source-folder saves

Status: implemented, opt-in, with Win32 integration tests and live GOG hook-site
verification. The editor round-trip and remaining supported runtimes still need
qualification before release. No game DLL or user map was replaced for this work.

## Behavior

Loading `addon/pilot/pilot.bzn` and selecting `pilot.bzn` in the editor saves back
to the observed source folder. The same applies to TRN. If only a same-named BZN
was observed, a new TRN can use that BZN's folder (and conversely). An ambiguous
exact filename never falls back to another extension.

Routing happens after the native filename dialog but before it reports success
to `PromptSaveMission`. The confirmed path replaces the caller's filename buffer,
so native `SaveGame` and `SaveZoneFiles` derive all their outputs from that path:

- BZN: selected BZN, plus TRN/HG2/MAT if the engine saves changed terrain.
- TRN: selected TRN and its HG2/MAT companions; no BZN is written.

A confirmation displays the **actual destination**, and lists existing files
that may be overwritten. For BZN it conservatively includes terrain companions,
even when the terrain is unchanged. Cancel is the default button. Cancel, closing
the prompt, or a prompt failure returns false through the editor's normal cancel
branch, before any native serializer or terrain-state mutation. A read-only,
directory, or inaccessible target also cancels the entire save before writing.
The original filename dialog may retain its own confirmation; the added prompt
is authoritative for the redirected destination.

There is no longer any BZN/TRN write redirection in the generic CreateFile hooks.
Those hooks only observe successful source reads and perform existing log/TRN
normalization duties. Ordinary savegames, autosaves and non-editor file writes
therefore do not acquire new routing or prompts.

## Enable for qualification

```ini
[Environment]
BZR_BZN_SAVE_SOURCE=1
```

Only the exact value `1` enables this feature. Restart to change it; default is
off. Use backed-up test maps. Ship the matching `scripts/patches.json` with the
DLL. A missing/ambiguous call-site signature or unexpected native dialog target
leaves the native call unchanged; no low-level write-routing fallback exists.

## Boundaries

- Source reads include resource scans. Different paths with the same filename
  disable routing for that filename until restart. The registry is conservative,
  not a claim that every observed read was an active editor mission load.
- Save As to a new filename stays at the requested destination. Explicit paths
  outside root addon stay explicit. A same-name root-addon selection can still
  select the observed source, but the user sees and must approve the final path.
- Workshop downloaded sources are excluded from redirection. A rejected or
  failed save is never retried silently into root addon.
- Existing path case and UNC roots are preserved for source selection. The
  native terrain writer continues to derive its own lowercase extensions.
- ANSI conversion must be lossless and fit the caller's 4096-byte buffer;
  otherwise saving is cancelled rather than writing to a different path.
- Attribute checks do not prove ACL write permission or prevent another process
  changing files after confirmation. Native write errors still apply. This is
  not an atomic multi-file save transaction. Conservative BZN preflight also
  rejects a read-only terrain companion even if terrain would be unchanged.

## Evidence and validation (2026-09-07)

GOG executable SHA-256:
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.

Ghidra decompile and disassembly independently establish:

- `PromptSaveMission` at `0x004FBE90` supplies a 4096-byte name buffer, sets
  `missionSave=1`, and calls `GetSaveName` at `0x004FBEE8`.
- The native dialog at `0x0056AD10` takes `this` in ECX and two stack arguments,
  returns success in AL, and ends with `RET 8` at `0x0056AE0B`.
- AL=false takes the cleanup branch before `SaveGame` at `0x004FBF48`.
- `SaveGame` at `0x004FD190` calls `SaveZoneFiles` at `0x00786C80` before BZN
  writing. TRN selects the terrain-only branch. `SaveZoneFiles` derives TRN,
  HG2 and MAT names from its filename argument.

A harness-controlled windowed GOG process, PID **430832**, reproduced the static
caller, dialog entry, and epilogue bytes. Commands used the Redux debugger's
explicit-PID native reader: `bzr-redux-debug.cmd read 0x004fbed3 --length 35
--pid 430832`, plus 32 bytes at `0x0056ad10` and `0x0056adf0`. The process was
stopped through `Stop-BZRGame` and its Ogre configuration restored. This was
hook-site validation, not a claim that an editor save was executed.

The catalog records a unique full-context CALL signature and an independent
`WorldBuilder::GetSaveName` resolver identity. Check its actual `[RESOLVE]` line
and successful patch-install log during the next opt-in editor qualification.
Earlier service labels at `0x00481ED0` / `0x00482900` were not used.

The user's `addon/pilot/pilot.bzn` still identifies `lcbench.bzn` / `lcbench`
internally. Source association uses the opened disk path. The file was read only.

Validation:

- Release Win32 DLL: built successfully (existing unrelated project warnings).
- `bzn_save_path_tests`: BZN/TRN selection, extension fallback, ambiguity,
  companion planning, overwrite preflight and Workshop exclusion.
- `editor_save_dialog_win32_tests`: includes production dialog/file-hook code,
  real Win32 temporary files, and scripted UI answers. Verifies ANSI and wide
  source observation, actual-target prompt text, BZN and TRN accept/cancel,
  native-dialog cancellation, new Save As, explicit paths, read-only companion
  rejection, and 100 repeated thiscall invocations for stack/ABI correctness.
  The native serializer itself is not invoked by this test.
- `resolve_table_tests`: shipped catalog checks.
- Linux host unit test: previously unavailable because WSL lacks `g++`.
- Windows/GOG full editor save/reload, Windows/Steam, Linux/Steam Proton and
  Linux/GOG Wine/Proton: **unverified**. Obtain those tester lanes before release.
